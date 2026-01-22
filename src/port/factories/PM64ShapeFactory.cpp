#include "PM64ShapeFactory.h"
#include "Companion.h"
#include "utils/Decompressor.h"
#include "spdlog/spdlog.h"
#include <ship/utils/binarytools/endianness.h>
#include <unordered_set>

// PM64 shape file structures (matching model.h):
// ShapeFileHeader (0x20 bytes):
//   0x00: root (ModelNode*)
//   0x04: vertexTable (Vtx_t*)
//   0x08: modelNames (char**)
//   0x0C: colliderNames (char**)
//   0x10: zoneNames (char**)
//   0x14: pad[0xC]
//
// ModelNode (0x14 bytes):
//   0x00: type (s32)
//   0x04: displayData (ModelDisplayData*)
//   0x08: numProperties (s32)
//   0x0C: propertyList (ModelNodeProperty*)
//   0x10: groupData (ModelGroupData*)
//
// ModelGroupData (0x14 bytes):
//   0x00: transformMatrix (Mtx*)
//   0x04: lightingGroup (Lightsn*)
//   0x08: numLights (s32)
//   0x0C: numChildren (s32)
//   0x10: childList (ModelNode**)
//
// ModelDisplayData (0x08 bytes):
//   0x00: displayList (Gfx*)
//   0x04: unk_04 (4 bytes)
//
// ModelNodeProperty (0x0C bytes):
//   0x00: key (s32)
//   0x04: dataType (s32)
//   0x08: data (union: s32/f32/void*)

// Base address used for N64 virtual address to offset conversion
// This is computed from the header's root pointer assuming root is at offset 0x20
static uint32_t gShapeBaseAddr = 0;

// Track visited offsets to prevent infinite recursion from cycles
static std::unordered_set<uint32_t> gVisitedNodes;
static std::unordered_set<uint32_t> gVisitedGroups;

// Convert N64 virtual address to file offset
static uint32_t N64AddrToOffset(uint32_t addr) {
    if (addr == 0) return 0;
    if (gShapeBaseAddr == 0) return addr; // fallback if not initialized
    if (addr < gShapeBaseAddr) return 0; // invalid
    return addr - gShapeBaseAddr;
}

static bool IsValidOffset(uint32_t offset, size_t size) {
    return offset > 0 && offset < size;
}

// Property key for texture names - these store N64 addresses to strings
#define MODEL_PROP_KEY_TEXTURE_NAME 0x5E

static void ByteSwapModelNodeProperty(uint8_t* data, uint32_t offset, size_t size) {
    if (!IsValidOffset(offset, size - 0xC)) return;

    uint32_t* prop = reinterpret_cast<uint32_t*>(data + offset);
    int32_t key = static_cast<int32_t>(BSWAP32(prop[0]));
    prop[0] = static_cast<uint32_t>(key);
    prop[1] = BSWAP32(prop[1]); // dataType

    // For texture name properties, convert N64 address to file offset
    if (key == MODEL_PROP_KEY_TEXTURE_NAME) {
        uint32_t dataAddr = BSWAP32(prop[2]);
        prop[2] = N64AddrToOffset(dataAddr);
    } else {
        prop[2] = BSWAP32(prop[2]); // data (scalar value)
    }
}

static void ByteSwapModelDisplayData(uint8_t* data, uint32_t offset, size_t size) {
    if (!IsValidOffset(offset, size - 0x8)) return;

    uint32_t* display = reinterpret_cast<uint32_t*>(data + offset);
    // displayList is a pointer - convert N64 address to offset
    uint32_t dlAddr = BSWAP32(display[0]);
    display[0] = N64AddrToOffset(dlAddr);
    display[1] = BSWAP32(display[1]); // unk_04
}

static void ByteSwapModelGroupData(uint8_t* data, uint32_t offset, size_t size);
static void ByteSwapModelNode(uint8_t* data, uint32_t offset, size_t size);

static void ByteSwapModelGroupData(uint8_t* data, uint32_t offset, size_t size) {
    if (!IsValidOffset(offset, size - 0x14)) return;
    if (gVisitedGroups.count(offset)) return;  // Already processed
    gVisitedGroups.insert(offset);

    uint32_t* group = reinterpret_cast<uint32_t*>(data + offset);

    // Read and convert N64 addresses to offsets
    uint32_t transformMatrixAddr = BSWAP32(group[0]);
    uint32_t lightingGroupAddr = BSWAP32(group[1]);
    int32_t numLights = static_cast<int32_t>(BSWAP32(group[2]));
    int32_t numChildren = static_cast<int32_t>(BSWAP32(group[3]));
    uint32_t childListAddr = BSWAP32(group[4]);

    // Convert N64 addresses to file offsets
    uint32_t transformMatrix = N64AddrToOffset(transformMatrixAddr);
    uint32_t lightingGroup = N64AddrToOffset(lightingGroupAddr);
    uint32_t childList = N64AddrToOffset(childListAddr);

    group[0] = transformMatrix;
    group[1] = lightingGroup;
    group[2] = static_cast<uint32_t>(numLights);
    group[3] = static_cast<uint32_t>(numChildren);
    group[4] = childList;

    // Byte-swap transform matrix (16 x s32 fixed-point values)
    if (IsValidOffset(transformMatrix, size - 0x40)) {
        uint32_t* mtx = reinterpret_cast<uint32_t*>(data + transformMatrix);
        for (int i = 0; i < 16; i++) {
            mtx[i] = BSWAP32(mtx[i]);
        }
    }

    // Byte-swap child list and recurse into child nodes
    // Sanity check: numChildren should be reasonable (< 1000)
    if (numChildren > 0 && numChildren < 1000 && IsValidOffset(childList, size - (numChildren * 4))) {
        uint32_t* children = reinterpret_cast<uint32_t*>(data + childList);
        for (int i = 0; i < numChildren; i++) {
            uint32_t childAddr = BSWAP32(children[i]);
            uint32_t childOffset = N64AddrToOffset(childAddr);
            children[i] = childOffset;
            ByteSwapModelNode(data, childOffset, size);
        }
    }
}

static void ByteSwapModelNode(uint8_t* data, uint32_t offset, size_t size) {
    if (!IsValidOffset(offset, size - 0x14)) return;
    if (gVisitedNodes.count(offset)) return;  // Already processed
    gVisitedNodes.insert(offset);

    uint32_t* node = reinterpret_cast<uint32_t*>(data + offset);

    // Read and convert N64 addresses
    int32_t type = static_cast<int32_t>(BSWAP32(node[0]));
    uint32_t displayDataAddr = BSWAP32(node[1]);
    int32_t numProperties = static_cast<int32_t>(BSWAP32(node[2]));
    uint32_t propertyListAddr = BSWAP32(node[3]);
    uint32_t groupDataAddr = BSWAP32(node[4]);

    // Convert N64 addresses to file offsets
    uint32_t displayData = N64AddrToOffset(displayDataAddr);
    uint32_t propertyList = N64AddrToOffset(propertyListAddr);
    uint32_t groupData = N64AddrToOffset(groupDataAddr);

    node[0] = static_cast<uint32_t>(type);
    node[1] = displayData;
    node[2] = static_cast<uint32_t>(numProperties);
    node[3] = propertyList;
    node[4] = groupData;

    // Byte-swap display data
    if (IsValidOffset(displayData, size)) {
        ByteSwapModelDisplayData(data, displayData, size);
    }

    // Byte-swap properties
    if (numProperties > 0 && IsValidOffset(propertyList, size)) {
        for (int i = 0; i < numProperties; i++) {
            ByteSwapModelNodeProperty(data, propertyList + (i * 0xC), size);
        }
    }

    // Byte-swap group data (which recursively handles children)
    if (IsValidOffset(groupData, size)) {
        ByteSwapModelGroupData(data, groupData, size);
    }
}

static void ByteSwapShapeData(uint8_t* data, size_t size) {
    if (size < 0x20) {
        SPDLOG_WARN("Shape data too small: {}", size);
        return;
    }

    // Clear visited sets for this shape file
    gVisitedNodes.clear();
    gVisitedGroups.clear();

    // Read header values (N64 virtual addresses, big-endian)
    uint32_t* header = reinterpret_cast<uint32_t*>(data);
    uint32_t rootAddr = BSWAP32(header[0]);
    uint32_t vertexTableAddr = BSWAP32(header[1]);
    uint32_t modelNamesAddr = BSWAP32(header[2]);
    uint32_t colliderNamesAddr = BSWAP32(header[3]);
    uint32_t zoneNamesAddr = BSWAP32(header[4]);

    SPDLOG_INFO("Shape header N64 addresses: root=0x{:X}, vtx=0x{:X}, modelNames=0x{:X}, colliderNames=0x{:X}, zoneNames=0x{:X}",
                 rootAddr, vertexTableAddr, modelNamesAddr, colliderNamesAddr, zoneNamesAddr);

    // Calculate base address for N64 address to offset conversion
    // Find the minimum non-zero N64 address - this corresponds to offset 0x20 (right after header)
    uint32_t minAddr = UINT32_MAX;
    if (rootAddr > 0x80000000 && rootAddr < minAddr) minAddr = rootAddr;
    if (vertexTableAddr > 0x80000000 && vertexTableAddr < minAddr) minAddr = vertexTableAddr;
    if (modelNamesAddr > 0x80000000 && modelNamesAddr < minAddr) minAddr = modelNamesAddr;
    if (colliderNamesAddr > 0x80000000 && colliderNamesAddr < minAddr) minAddr = colliderNamesAddr;
    if (zoneNamesAddr > 0x80000000 && zoneNamesAddr < minAddr) minAddr = zoneNamesAddr;

    if (minAddr != UINT32_MAX && minAddr > 0x20) {
        gShapeBaseAddr = minAddr - 0x20;
    } else {
        // If addresses look like they're already offsets, don't convert
        gShapeBaseAddr = 0;
    }

    SPDLOG_INFO("Computed shape base address: 0x{:X} (from min addr 0x{:X})", gShapeBaseAddr, minAddr);

    // Convert N64 addresses to file offsets
    uint32_t root = N64AddrToOffset(rootAddr);
    uint32_t vertexTable = N64AddrToOffset(vertexTableAddr);
    uint32_t modelNames = N64AddrToOffset(modelNamesAddr);
    uint32_t colliderNames = N64AddrToOffset(colliderNamesAddr);
    uint32_t zoneNames = N64AddrToOffset(zoneNamesAddr);

    SPDLOG_INFO("Converted offsets: root=0x{:X}, vtx=0x{:X}, modelNames=0x{:X}, colliderNames=0x{:X}, zoneNames=0x{:X}",
                 root, vertexTable, modelNames, colliderNames, zoneNames);

    // Store converted offsets back to header
    header[0] = root;
    header[1] = vertexTable;
    header[2] = modelNames;
    header[3] = colliderNames;
    header[4] = zoneNames;

    // Byte-swap the root ModelNode tree recursively
    if (IsValidOffset(root, size)) {
        ByteSwapModelNode(data, root, size);
    } else {
        SPDLOG_WARN("Root offset 0x{:X} is invalid for size {}", root, size);
    }

    // Byte-swap vertex table
    // Vtx_t structure (16 bytes):
    //   0x00: ob[3] (3 x s16) - position
    //   0x06: flag (u16)
    //   0x08: tc[2] (2 x s16) - texture coords
    //   0x0C: cn[4] (4 x u8) - color/normal (no swap needed)
    if (IsValidOffset(vertexTable, size)) {
        uint8_t* vtxPtr = data + vertexTable;
        uint8_t* endPtr = data + size;

        // Estimate vertex count by checking how much space is between vertexTable and other structures
        uint32_t vtxEnd = size;
        if (modelNames > vertexTable && modelNames < vtxEnd) vtxEnd = modelNames;
        if (colliderNames > vertexTable && colliderNames < vtxEnd) vtxEnd = colliderNames;
        if (zoneNames > vertexTable && zoneNames < vtxEnd) vtxEnd = zoneNames;

        size_t vtxSize = vtxEnd - vertexTable;
        size_t numVertices = vtxSize / 16;

        for (size_t i = 0; i < numVertices && vtxPtr + 16 <= endPtr; i++) {
            uint16_t* v = reinterpret_cast<uint16_t*>(vtxPtr);
            v[0] = BSWAP16(v[0]); // ob[0]
            v[1] = BSWAP16(v[1]); // ob[1]
            v[2] = BSWAP16(v[2]); // ob[2]
            v[3] = BSWAP16(v[3]); // flag
            v[4] = BSWAP16(v[4]); // tc[0]
            v[5] = BSWAP16(v[5]); // tc[1]
            // cn[4] are bytes, no swap needed
            vtxPtr += 16;
        }
    }

    // Byte-swap name table pointers (arrays of char* terminated by null)
    // Also convert N64 addresses to offsets
    auto swapNameTable = [&](uint32_t tableOffset) {
        if (!IsValidOffset(tableOffset, size - 4)) return;

        uint32_t* names = reinterpret_cast<uint32_t*>(data + tableOffset);
        while (reinterpret_cast<uint8_t*>(names) < data + size - 4) {
            uint32_t nameAddr = BSWAP32(*names);
            uint32_t nameOffset = N64AddrToOffset(nameAddr);
            *names = nameOffset;
            if (nameAddr == 0) break;
            names++;
        }
    };

    swapNameTable(modelNames);
    swapNameTable(colliderNames);
    swapNameTable(zoneNames);
}

std::optional<std::shared_ptr<IParsedData>> PM64ShapeFactory::parse(std::vector<uint8_t>& buffer, YAML::Node& node) {
    auto offset = GetSafeNode<uint32_t>(node, "offset");

    // Check if compressed (YAY0)
    auto compressionType = Decompressor::GetCompressionType(buffer, offset);

    if (compressionType == CompressionType::YAY0) {
        auto decoded = Decompressor::Decode(buffer, offset, CompressionType::YAY0);
        if (!decoded || decoded->size == 0) {
            SPDLOG_ERROR("Failed to decompress YAY0 shape data at offset 0x{:X}", offset);
            return std::nullopt;
        }

        std::vector<uint8_t> shapeData(decoded->data, decoded->data + decoded->size);
        ByteSwapShapeData(shapeData.data(), shapeData.size());

        SPDLOG_INFO("PM64:SHAPE parsed at 0x{:X}, decompressed size: {}", offset, shapeData.size());

        return std::make_shared<RawBuffer>(shapeData);
    } else {
        // Uncompressed - read raw data with size from YAML
        auto size = GetSafeNode<size_t>(node, "size");
        auto [_, segment] = Decompressor::AutoDecode(node, buffer, size);

        std::vector<uint8_t> shapeData(segment.data, segment.data + segment.size);
        ByteSwapShapeData(shapeData.data(), shapeData.size());

        return std::make_shared<RawBuffer>(shapeData);
    }
}

ExportResult PM64ShapeBinaryExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    auto writer = LUS::BinaryWriter();
    auto data = std::static_pointer_cast<RawBuffer>(raw)->mBuffer;

    // Write as Blob type - game loads as raw binary
    WriteHeader(writer, Torch::ResourceType::Blob, 0);
    writer.Write(static_cast<uint32_t>(data.size()));
    writer.Write(reinterpret_cast<char*>(data.data()), data.size());
    writer.Finish(write);

    return std::nullopt;
}

ExportResult PM64ShapeHeaderExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    const auto symbol = GetSafeNode(node, "symbol", entryName);

    if (Companion::Instance->IsOTRMode()) {
        write << "static const ALIGN_ASSET(2) char " << symbol << "[] = \"__OTR__" << (*replacement) << "\";\n\n";
        return std::nullopt;
    }

    write << "extern u8 " << symbol << "[];\n";
    return std::nullopt;
}
