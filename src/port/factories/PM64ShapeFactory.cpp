#include "PM64ShapeFactory.h"
#include "Companion.h"
#include "utils/Decompressor.h"
#include "spdlog/spdlog.h"
#include <ship/utils/binarytools/endianness.h>
#include <unordered_set>
#include <sstream>
#include "n64/CommandMacros.h"
#include "factories/DisplayListOverrides.h"
#include "n64/gbi-otr.h"
#include "strhash64/StrHash64.h"

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

// Vertex table offset in shape file - used for converting G_VTX offsets to vertex-table-relative
static uint32_t gVertexTableOffset = 0;

// Track visited offsets to prevent infinite recursion from cycles and to exclude from vertex byte-swapping
static std::unordered_set<uint32_t> gVisitedNodes;
static std::unordered_set<uint32_t> gVisitedGroups;
static std::unordered_set<uint32_t> gVisitedDisplayLists;
static std::unordered_set<uint32_t> gVisitedDisplayData;

// Collected display lists during parsing
static std::vector<PM64DisplayListInfo>* gCollectedDisplayLists = nullptr;

// Convert N64 virtual address to file offset
static uint32_t N64AddrToOffset(uint32_t addr) {
    if (addr == 0) return 0;

    // Check if it looks like an N64 virtual address (segment in high byte)
    if (addr >= 0x80000000) {
        // It's an N64 address - convert using base
        if (gShapeBaseAddr == 0) {
            // Fallback: mask off the segment and use as offset
            return addr & 0x00FFFFFF;
        }
        if (addr >= gShapeBaseAddr) {
            return addr - gShapeBaseAddr;
        }
        // Address is below base - might be in a different segment, try masking
        return addr & 0x00FFFFFF;
    }

    // Small value - assume it's already a file offset
    return addr;
}

static bool IsValidOffset(uint32_t offset, size_t size) {
    return offset > 0 && offset < size;
}

// F3DEX2 GBI opcodes used in shape display lists
#define F3DEX2_G_ENDDL   0xDF
#define F3DEX2_G_VTX     0x01
#define F3DEX2_G_DL      0xDE
#define F3DEX2_G_SETTIMG 0xFD

// Byte-swap display list commands, convert embedded N64 addresses to file offsets,
// and collect the display list for separate resource export
static void ByteSwapDisplayList(uint8_t* data, uint32_t offset, size_t size) {
    if (!IsValidOffset(offset, size - 8)) return;
    if (gVisitedDisplayLists.count(offset)) return;  // Already processed
    gVisitedDisplayLists.insert(offset);

    uint8_t* ptr = data + offset;
    uint8_t* endPtr = data + size;

    // Collect this display list's commands
    PM64DisplayListInfo dlInfo;
    dlInfo.offset = offset;

    while (ptr + 8 <= endPtr) {
        uint32_t* words = reinterpret_cast<uint32_t*>(ptr);

        // Read big-endian words
        uint32_t w0 = BSWAP32(words[0]);
        uint32_t w1 = BSWAP32(words[1]);

        uint8_t opcode = (w0 >> 24) & 0xFF;

        // Handle G_VTX - convert vertex address to vertex-table-relative offset
        if (opcode == F3DEX2_G_VTX) {
            // w1 contains the N64 vertex address - convert to file offset first
            uint32_t vtxFileOffset = N64AddrToOffset(w1);
            // Then convert to vertex-table-relative offset
            if (gVertexTableOffset > 0 && vtxFileOffset >= gVertexTableOffset) {
                w1 = vtxFileOffset - gVertexTableOffset;
            } else {
                w1 = vtxFileOffset;
            }
        }

        // Handle G_SETTIMG - convert texture address to file offset
        // Note: Shape textures may be loaded separately, but we convert anyway for safety
        if (opcode == F3DEX2_G_SETTIMG) {
            // w1 contains the N64 texture address
            w1 = N64AddrToOffset(w1);
        }

        // Handle G_DL - convert display list address to file offset and recurse
        if (opcode == F3DEX2_G_DL) {
            uint32_t dlOffset = N64AddrToOffset(w1);
            w1 = dlOffset;
            // Recursively process the referenced display list
            ByteSwapDisplayList(data, dlOffset, size);
        }

        // Write the byte-swapped (now little-endian) words back
        words[0] = w0;
        words[1] = w1;

        // Collect the command for OTR export
        dlInfo.commands.push_back(w0);
        dlInfo.commands.push_back(w1);

        // Stop at G_ENDDL
        if (opcode == F3DEX2_G_ENDDL) {
            break;
        }

        ptr += 8;  // Move to next Gfx command (8 bytes each)
    }

    // Add to collected display lists
    if (gCollectedDisplayLists && !dlInfo.commands.empty()) {
        gCollectedDisplayLists->push_back(std::move(dlInfo));
    }
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

    // Track this offset so vertex byte-swapping skips it
    gVisitedDisplayData.insert(offset);

    uint32_t* display = reinterpret_cast<uint32_t*>(data + offset);
    // displayList is a pointer - convert N64 address to offset
    uint32_t dlAddr = BSWAP32(display[0]);
    uint32_t dlOffset = N64AddrToOffset(dlAddr);

    display[0] = dlOffset;
    display[1] = BSWAP32(display[1]); // unk_04

    // Byte-swap the display list commands themselves and collect for export
    if (IsValidOffset(dlOffset, size)) {
        ByteSwapDisplayList(data, dlOffset, size);
    }
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

// Find the ROOT node (type=7) by scanning the shape data
// Returns the file offset of the ROOT node, or 0 if not found
static uint32_t FindRootNodeOffset(uint8_t* data, size_t size) {
    for (uint32_t offset = 0x20; offset < size - 0x14; offset += 4) {
        int32_t type = static_cast<int32_t>(BSWAP32(*reinterpret_cast<uint32_t*>(data + offset)));

        if (type == 7) {  // SHAPE_TYPE_ROOT
            // Validate surrounding fields look like a ModelNode
            uint32_t displayAddr = BSWAP32(*reinterpret_cast<uint32_t*>(data + offset + 0x04));
            int32_t numProps = static_cast<int32_t>(BSWAP32(*reinterpret_cast<uint32_t*>(data + offset + 0x08)));
            uint32_t groupAddr = BSWAP32(*reinterpret_cast<uint32_t*>(data + offset + 0x10));

            bool valid = (displayAddr == 0 || displayAddr > 0x80000000);
            valid = valid && (groupAddr == 0 || groupAddr > 0x80000000);
            valid = valid && (numProps >= 0 && numProps <= 100);

            if (valid) {
                return offset;
            }
        }
    }

    SPDLOG_WARN("Could not find ROOT node in shape data");
    return 0;
}

static void ByteSwapShapeData(uint8_t* data, size_t size, std::vector<PM64DisplayListInfo>& collectedDLs,
                               uint32_t& outVtxTableOffset, uint32_t& outVtxDataSize) {
    outVtxTableOffset = 0;
    outVtxDataSize = 0;

    if (size < 0x20) {
        SPDLOG_WARN("Shape data too small: {}", size);
        return;
    }

    // Clear visited sets for this shape file
    gVisitedNodes.clear();
    gVisitedGroups.clear();
    gVisitedDisplayLists.clear();
    gVisitedDisplayData.clear();

    // Set up collection target
    gCollectedDisplayLists = &collectedDLs;

    // Read header values (N64 virtual addresses, big-endian)
    uint32_t* header = reinterpret_cast<uint32_t*>(data);
    uint32_t rootAddr = BSWAP32(header[0]);
    uint32_t vertexTableAddr = BSWAP32(header[1]);
    uint32_t modelNamesAddr = BSWAP32(header[2]);
    uint32_t colliderNamesAddr = BSWAP32(header[3]);
    uint32_t zoneNamesAddr = BSWAP32(header[4]);

    // Find the ROOT node by scanning the data to compute correct base address
    uint32_t rootFileOffset = FindRootNodeOffset(data, size);

    if (rootFileOffset > 0 && rootAddr > 0x80000000) {
        // Compute base from actual ROOT node location: base = rootAddr - rootFileOffset
        gShapeBaseAddr = rootAddr - rootFileOffset;
        SPDLOG_INFO("Computed shape base address: 0x{:X} (from ROOT at offset 0x{:X}, addr 0x{:X})",
                    gShapeBaseAddr, rootFileOffset, rootAddr);
    } else {
        // Fallback to known PM64 base (verified across all tested shapes)
        gShapeBaseAddr = 0x80210000;
        SPDLOG_WARN("Using fallback base address: 0x{:X}", gShapeBaseAddr);
    }

    // Convert N64 addresses to file offsets
    uint32_t root = N64AddrToOffset(rootAddr);
    uint32_t vertexTable = N64AddrToOffset(vertexTableAddr);
    uint32_t modelNames = N64AddrToOffset(modelNamesAddr);
    uint32_t colliderNames = N64AddrToOffset(colliderNamesAddr);
    uint32_t zoneNames = N64AddrToOffset(zoneNamesAddr);

    // Validate root offset is within bounds
    if (root >= size) {
        SPDLOG_ERROR("Root offset 0x{:X} exceeds file size {}!", root, size);
        return;
    }

    // Set vertex table offset global BEFORE processing display lists
    // This allows ByteSwapDisplayList to convert G_VTX offsets to vertex-table-relative
    gVertexTableOffset = vertexTable;
    outVtxTableOffset = vertexTable;

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

        // Find the minimum offset among all visited model structures
        // This marks where non-vertex data begins (display lists, model nodes, etc.)
        uint32_t minVisitedOffset = size;
        for (uint32_t off : gVisitedNodes) {
            if (off > vertexTable && off < minVisitedOffset) minVisitedOffset = off;
        }
        for (uint32_t off : gVisitedGroups) {
            if (off > vertexTable && off < minVisitedOffset) minVisitedOffset = off;
        }
        for (uint32_t off : gVisitedDisplayLists) {
            if (off > vertexTable && off < minVisitedOffset) minVisitedOffset = off;
        }
        for (uint32_t off : gVisitedDisplayData) {
            if (off > vertexTable && off < minVisitedOffset) minVisitedOffset = off;
        }

        // Also check name tables and header structures
        uint32_t vtxEnd = minVisitedOffset;
        if (root > vertexTable && root < vtxEnd) vtxEnd = root;
        if (modelNames > vertexTable && modelNames < vtxEnd) vtxEnd = modelNames;
        if (colliderNames > vertexTable && colliderNames < vtxEnd) vtxEnd = colliderNames;
        if (zoneNames > vertexTable && zoneNames < vtxEnd) vtxEnd = zoneNames;

        size_t vtxSize = vtxEnd - vertexTable;
        size_t numVertices = vtxSize / 16;

        // Store vertex data size for export
        outVtxDataSize = static_cast<uint32_t>(vtxSize);

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

    // Clear the collection pointer
    gCollectedDisplayLists = nullptr;
}

std::optional<std::shared_ptr<IParsedData>> PM64ShapeFactory::parse(std::vector<uint8_t>& buffer, YAML::Node& node) {
    auto offset = GetSafeNode<uint32_t>(node, "offset");

    std::vector<PM64DisplayListInfo> collectedDLs;
    uint32_t vtxTableOffset = 0;
    uint32_t vtxDataSize = 0;

    // Check if compressed (YAY0)
    auto compressionType = Decompressor::GetCompressionType(buffer, offset);

    if (compressionType == CompressionType::YAY0) {
        auto decoded = Decompressor::Decode(buffer, offset, CompressionType::YAY0);
        if (!decoded || decoded->size == 0) {
            SPDLOG_ERROR("Failed to decompress YAY0 shape data at offset 0x{:X}", offset);
            return std::nullopt;
        }

        std::vector<uint8_t> shapeData(decoded->data, decoded->data + decoded->size);
        ByteSwapShapeData(shapeData.data(), shapeData.size(), collectedDLs, vtxTableOffset, vtxDataSize);

        return std::make_shared<PM64ShapeData>(std::move(shapeData), std::move(collectedDLs), vtxTableOffset, vtxDataSize);
    } else {
        // Uncompressed - read raw data with size from YAML
        auto size = GetSafeNode<size_t>(node, "size");
        auto [_, segment] = Decompressor::AutoDecode(node, buffer, size);

        std::vector<uint8_t> shapeData(segment.data, segment.data + segment.size);
        ByteSwapShapeData(shapeData.data(), shapeData.size(), collectedDLs, vtxTableOffset, vtxDataSize);

        return std::make_shared<PM64ShapeData>(std::move(shapeData), std::move(collectedDLs), vtxTableOffset, vtxDataSize);
    }
}

// Export vertex data as a separate OTR Blob resource
// Returns the resource path used for hashing in G_VTX_OTR_HASH commands
static std::string ExportVertexResource(const std::string& shapeName, const uint8_t* shapeData,
                                         uint32_t vtxTableOffset, uint32_t vtxDataSize) {
    if (vtxDataSize == 0) {
        SPDLOG_WARN("No vertex data to export for shape {}", shapeName);
        return "";
    }

    // Build resource path
    std::string path = shapeName + "/vtx";
    auto writer = LUS::BinaryWriter();

    // Write Blob resource header
    BaseExporter::WriteHeader(writer, Torch::ResourceType::Blob, 0);

    // Write vertex data size followed by raw bytes
    writer.Write(static_cast<uint32_t>(vtxDataSize));
    writer.Write(const_cast<char*>(reinterpret_cast<const char*>(shapeData + vtxTableOffset)), vtxDataSize);

    // Finish writing and register as companion file
    std::stringstream ss;
    writer.Finish(ss);
    std::string str = ss.str();
    std::vector<char> data(str.begin(), str.end());

    Companion::Instance->RegisterCompanionFile(path, data);

    return path;
}

// Export a single display list as an OTR resource
static void ExportDisplayListResource(const std::string& shapeName, const PM64DisplayListInfo& dlInfo) {
    // Build the resource path
    char pathBuf[256];
    snprintf(pathBuf, sizeof(pathBuf), "%s/dlist_%X", shapeName.c_str(), dlInfo.offset);
    std::string path = pathBuf;

    // Get full OTR path for hash calculation (gCurrentDirectory + path)
    std::string fullPath = Companion::Instance->RelativePath(path);

    auto writer = LUS::BinaryWriter();

    // Write DisplayList resource header
    BaseExporter::WriteHeader(writer, Torch::ResourceType::DisplayList, 0);

    // Write GBI version byte (F3DEX2 for PM64)
    writer.Write(static_cast<int8_t>(GBIVersion::f3dex2));

    // Pad to 8-byte alignment
    while (writer.GetBaseAddress() % 8 != 0)
        writer.Write(static_cast<int8_t>(0xFF));

    // Write G_MARKER with resource hash (using full OTR path)
    uint64_t hash = CRC64(fullPath.c_str());
    writer.Write(static_cast<uint32_t>(G_MARKER << 24));
    writer.Write(static_cast<uint32_t>(0xBEEFBEEF));
    writer.Write(static_cast<uint32_t>(hash >> 32));
    writer.Write(static_cast<uint32_t>(hash & 0xFFFFFFFF));

    // Write commands in OTR format
    // IMPORTANT: libultraship DisplayListFactory expects:
    // - Standard commands: 8 bytes (w0, w1)
    // - OTR-expanded commands: 16 bytes (w0, w1, extra 8 bytes)
    // Expanded opcodes: G_SETTIMG_OTR_HASH, G_DL_OTR_HASH, G_VTX_OTR_HASH,
    //                   G_BRANCH_Z_OTR, G_MARKER, G_MTX_OTR, G_MOVEMEM_OTR
    for (size_t i = 0; i < dlInfo.commands.size(); i += 2) {
        uint32_t w0 = dlInfo.commands[i];
        uint32_t w1 = dlInfo.commands[i + 1];
        uint8_t opcode = (w0 >> 24) & 0xFF;

        if (opcode == F3DEX2_G_SETTIMG) {
            // Replace G_SETTIMG with G_NOOP - PM64 textures are loaded via texture handle system
            // G_NOOP is a standard 8-byte command
            SPDLOG_INFO("Converting G_SETTIMG to G_NOOP in {}/dlist_{:X} (w0=0x{:08X}, w1=0x{:08X})",
                        shapeName, dlInfo.offset, w0, w1);
            writer.Write(static_cast<uint32_t>(0x00 << 24));  // G_NOOP
            writer.Write(static_cast<uint32_t>(0));
            // NO PADDING - standard command is 8 bytes
        } else if (opcode == F3DEX2_G_VTX) {
            // Emit G_VTX_OTR_HASH - an expanded 16-byte command
            // w0 format: opcode[31:24] | n[19:12] | (v0+n)[7:1]
            // The n and v0+n encoding is preserved from original G_VTX
            char vtxPath[256];
            snprintf(vtxPath, sizeof(vtxPath), "%s/vtx", shapeName.c_str());
            // Use RelativePath to get full OTR path (gCurrentDirectory + vtxPath)
            std::string fullVtxPath = Companion::Instance->RelativePath(vtxPath);
            uint64_t vtxHash = CRC64(fullVtxPath.c_str());

            // Replace opcode with G_VTX_OTR_HASH, keep n and v0 encoding
            uint32_t newW0 = (G_VTX_OTR_HASH << 24) | (w0 & 0x00FFFFFF);
            writer.Write(newW0);
            writer.Write(w1);  // w1 is vertex-table-relative offset

            // Write hash (extra 8 bytes for expanded command)
            writer.Write(static_cast<uint32_t>(vtxHash >> 32));
            writer.Write(static_cast<uint32_t>(vtxHash & 0xFFFFFFFF));
        } else if (opcode == F3DEX2_G_DL) {
            // Nested display list - build path for it and write hash
            // G_DL_OTR_HASH is an expanded 16-byte command
            char nestedPath[256];
            snprintf(nestedPath, sizeof(nestedPath), "%s/dlist_%X", shapeName.c_str(), w1);
            // Use RelativePath to get full OTR path (gCurrentDirectory + nestedPath)
            std::string fullNestedPath = Companion::Instance->RelativePath(nestedPath);
            uint64_t nestedHash = CRC64(fullNestedPath.c_str());

            // Write G_DL_OTR_HASH opcode (expanded command - 16 bytes total)
            N64Gfx value = gsSPDisplayListOTRHash(0);
            writer.Write(value.words.w0);
            writer.Write(value.words.w1);
            // Write the hash of the nested display list (extra 8 bytes for expanded command)
            writer.Write(static_cast<uint32_t>(nestedHash >> 32));
            writer.Write(static_cast<uint32_t>(nestedHash & 0xFFFFFFFF));
        } else {
            // Standard command - 8 bytes only
            writer.Write(w0);
            writer.Write(w1);
            // NO PADDING - standard commands are 8 bytes
        }
    }

    // Finish writing and register as companion file
    std::stringstream ss;
    writer.Finish(ss);
    std::string str = ss.str();
    std::vector<char> data(str.begin(), str.end());

    Companion::Instance->RegisterCompanionFile(path, data);
}

ExportResult PM64ShapeBinaryExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    auto shapeData = std::static_pointer_cast<PM64ShapeData>(raw);
    auto writer = LUS::BinaryWriter();

    // Extract shape name from entry name (e.g., "shapes/kmr_02_shape" -> "kmr_02_shape")
    std::string shapeName = entryName;
    size_t lastSlash = entryName.rfind('/');
    if (lastSlash != std::string::npos) {
        shapeName = entryName.substr(lastSlash + 1);
    }

    // Export vertex data as a separate OTR resource
    ExportVertexResource(shapeName, shapeData->mBuffer.data(),
                         shapeData->mVertexTableOffset, shapeData->mVertexDataSize);

    // Export each display list as a separate OTR resource
    for (const auto& dlInfo : shapeData->mDisplayLists) {
        ExportDisplayListResource(shapeName, dlInfo);
    }

    // Write shape blob as before
    WriteHeader(writer, Torch::ResourceType::Blob, 0);
    writer.Write(static_cast<uint32_t>(shapeData->mBuffer.size()));
    writer.Write(reinterpret_cast<char*>(shapeData->mBuffer.data()), shapeData->mBuffer.size());
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
