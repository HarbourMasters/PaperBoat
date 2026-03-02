#include "PM64CollisionFactory.h"
#include "Companion.h"
#include "utils/Decompressor.h"
#include "spdlog/spdlog.h"
#include <ship/utils/binarytools/endianness.h>

// PM64 collision file structure (N64 ROM format):
//
// HitFile header (8 bytes):
//   0x00: collisionOffset (u32) - offset to collision HitFileHeader
//   0x04: zoneOffset (u32) - offset to zone HitFileHeader
//
// HitFileHeader (0x18 bytes) at collisionOffset and zoneOffset:
//   0x00: numColliders (s16)
//   0x02: pad (2 bytes)
//   0x04: collidersOffset (s32) - offset to HitAssetCollider array
//   0x08: numVertices (s16)
//   0x0A: pad (2 bytes)
//   0x0C: verticesOffset (s32) - offset to Vec3s array
//   0x10: boundingBoxesDataSize (s16)
//   0x12: pad (2 bytes)
//   0x14: boundingBoxesOffset (s32) - offset to bounding box data
//
// HitAssetCollider (0x0C bytes) - array of numColliders entries:
//   0x00: boundingBoxOffset (s16)
//   0x02: nextSibling (s16)
//   0x04: firstChild (s16)
//   0x06: numTriangles (s16)
//   0x08: trianglesOffset (s32) - offset to packed triangle data
//
// Vertices: Vec3s array (6 bytes each) - numVertices entries
//   Each x, y, z is s16
//
// Triangles: s32 array - packed vertex indices + flags
//   bits 0-9: v1, 10-19: v2, 20-29: v3, 30: oneSided

static void ByteSwapHitFileHeader(uint8_t* data, uint32_t headerOffset, size_t totalSize) {
    if (headerOffset == 0 || headerOffset + 0x18 > totalSize) {
        return;
    }

    uint8_t* header = data + headerOffset;

    // numColliders at 0x00 (s16)
    uint16_t* numColliders = reinterpret_cast<uint16_t*>(header);
    *numColliders = BSWAP16(*numColliders);

    // collidersOffset at 0x04 (s32)
    uint32_t* collidersOffset = reinterpret_cast<uint32_t*>(header + 0x04);
    *collidersOffset = BSWAP32(*collidersOffset);

    // numVertices at 0x08 (s16)
    uint16_t* numVertices = reinterpret_cast<uint16_t*>(header + 0x08);
    *numVertices = BSWAP16(*numVertices);

    // verticesOffset at 0x0C (s32)
    uint32_t* verticesOffset = reinterpret_cast<uint32_t*>(header + 0x0C);
    *verticesOffset = BSWAP32(*verticesOffset);

    // boundingBoxesDataSize at 0x10 (s16)
    uint16_t* boundingBoxesDataSize = reinterpret_cast<uint16_t*>(header + 0x10);
    *boundingBoxesDataSize = BSWAP16(*boundingBoxesDataSize);

    // boundingBoxesOffset at 0x14 (s32)
    uint32_t* boundingBoxesOffset = reinterpret_cast<uint32_t*>(header + 0x14);
    *boundingBoxesOffset = BSWAP32(*boundingBoxesOffset);

    SPDLOG_DEBUG("HitFileHeader at 0x{:X}: numColliders={}, collidersOffset=0x{:X}, numVertices={}, verticesOffset=0x{:X}, bbSize={}, bbOffset=0x{:X}",
                 headerOffset, *numColliders, *collidersOffset, *numVertices, *verticesOffset,
                 *boundingBoxesDataSize, *boundingBoxesOffset);

    // Byte-swap colliders array (HitAssetCollider, 0x0C bytes each)
    uint32_t collOffset = *collidersOffset;
    uint16_t numColl = *numColliders;
    if (collOffset > 0 && collOffset + numColl * 0x0C <= totalSize) {
        for (uint16_t i = 0; i < numColl; i++) {
            uint8_t* collider = data + collOffset + i * 0x0C;
            uint16_t* s16Fields = reinterpret_cast<uint16_t*>(collider);
            s16Fields[0] = BSWAP16(s16Fields[0]); // boundingBoxOffset
            s16Fields[1] = BSWAP16(s16Fields[1]); // nextSibling
            s16Fields[2] = BSWAP16(s16Fields[2]); // firstChild
            s16Fields[3] = BSWAP16(s16Fields[3]); // numTriangles
            uint32_t* trianglesOffset = reinterpret_cast<uint32_t*>(collider + 0x08);
            *trianglesOffset = BSWAP32(*trianglesOffset);

            // Byte-swap triangles array for this collider (s32 each)
            uint16_t numTris = s16Fields[3];
            uint32_t trisOffset = *trianglesOffset;
            if (numTris > 0 && trisOffset > 0 && trisOffset + numTris * 4 <= totalSize) {
                uint32_t* triangles = reinterpret_cast<uint32_t*>(data + trisOffset);
                for (uint16_t t = 0; t < numTris; t++) {
                    triangles[t] = BSWAP32(triangles[t]);
                }
            }
        }
    }

    // Byte-swap vertices array (Vec3s, 6 bytes each - 3 x s16)
    uint32_t vertOffset = *verticesOffset;
    uint16_t numVerts = *numVertices;
    if (vertOffset > 0 && vertOffset + numVerts * 6 <= totalSize) {
        uint16_t* vertices = reinterpret_cast<uint16_t*>(data + vertOffset);
        for (uint16_t i = 0; i < numVerts * 3; i++) {
            vertices[i] = BSWAP16(vertices[i]);
        }
    }

    // Byte-swap bounding boxes data (u32 array)
    uint32_t bbOffset = *boundingBoxesOffset;
    uint16_t bbSize = *boundingBoxesDataSize;
    if (bbOffset > 0 && bbSize > 0 && bbOffset + bbSize * 4 <= totalSize) {
        uint32_t* bboxes = reinterpret_cast<uint32_t*>(data + bbOffset);
        for (uint16_t i = 0; i < bbSize; i++) {
            bboxes[i] = BSWAP32(bboxes[i]);
        }
    }
}

static void ByteSwapCollisionData(uint8_t* data, size_t size) {
    if (size < 8) {
        SPDLOG_WARN("Collision data too small: {}", size);
        return;
    }

    // Byte-swap HitFile header
    uint32_t* header = reinterpret_cast<uint32_t*>(data);
    uint32_t collisionOffset = BSWAP32(header[0]);
    uint32_t zoneOffset = BSWAP32(header[1]);
    header[0] = collisionOffset;
    header[1] = zoneOffset;

    SPDLOG_DEBUG("HitFile: collisionOffset=0x{:X}, zoneOffset=0x{:X}", collisionOffset, zoneOffset);

    // Byte-swap collision HitFileHeader and its data
    ByteSwapHitFileHeader(data, collisionOffset, size);

    // Byte-swap zone HitFileHeader and its data
    ByteSwapHitFileHeader(data, zoneOffset, size);
}

std::optional<std::shared_ptr<IParsedData>> PM64CollisionFactory::parse(std::vector<uint8_t>& buffer, YAML::Node& node) {
    auto offset = GetSafeNode<uint32_t>(node, "offset");

    // Check if compressed (YAY0)
    auto compressionType = Decompressor::GetCompressionType(buffer, offset);

    if (compressionType == CompressionType::YAY0) {
        auto decoded = Decompressor::Decode(buffer, offset, CompressionType::YAY0);
        if (!decoded || decoded->size == 0) {
            SPDLOG_ERROR("Failed to decompress YAY0 collision data at offset 0x{:X}", offset);
            return std::nullopt;
        }

        std::vector<uint8_t> colData(decoded->data, decoded->data + decoded->size);
        ByteSwapCollisionData(colData.data(), colData.size());

        return std::make_shared<RawBuffer>(colData);
    } else {
        // Uncompressed - read raw data with size from YAML
        auto size = GetSafeNode<size_t>(node, "size");
        auto [_, segment] = Decompressor::AutoDecode(node, buffer, size);

        std::vector<uint8_t> colData(segment.data, segment.data + segment.size);
        ByteSwapCollisionData(colData.data(), colData.size());

        return std::make_shared<RawBuffer>(colData);
    }
}

ExportResult PM64CollisionBinaryExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    auto writer = LUS::BinaryWriter();
    auto data = std::static_pointer_cast<RawBuffer>(raw)->mBuffer;

    // Write as Blob type - game loads as raw binary
    WriteHeader(writer, Torch::ResourceType::Blob, 0);
    writer.Write(static_cast<uint32_t>(data.size()));
    writer.Write(reinterpret_cast<char*>(data.data()), data.size());
    writer.Finish(write);

    return std::nullopt;
}

ExportResult PM64CollisionHeaderExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    const auto symbol = GetSafeNode(node, "symbol", entryName);

    if (Companion::Instance->IsOTRMode()) {
        write << "static const ALIGN_ASSET(2) char " << symbol << "[] = \"__OTR__" << (*replacement) << "\";\n\n";
        return std::nullopt;
    }

    write << "extern u8 " << symbol << "[];\n";
    return std::nullopt;
}
