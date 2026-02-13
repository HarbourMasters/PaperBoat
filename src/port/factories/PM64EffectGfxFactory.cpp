#include "PM64EffectGfxFactory.h"
#include "Companion.h"
#include "spdlog/spdlog.h"
#include <ship/utils/binarytools/endianness.h>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include "n64/gbi-otr.h"
#include "strhash64/StrHash64.h"

// F3DEX2 GBI opcodes
#define F3DEX2_G_ENDDL   0xDF
#define F3DEX2_G_VTX     0x01
#define F3DEX2_G_DL      0xDE
#define F3DEX2_G_SETTIMG 0xFD
#define F3DEX2_G_MOVEMEM 0xDC

// Walk a display list at the given offset, byte-swap commands from BE to native,
// collect them, and recursively process nested display lists.
// Buffer is const — overlapping display lists (e.g. fire_breath dlist_B88/BA8)
// share tail commands, so we must never modify the shared ROM data.
static void WalkDisplayList(const uint8_t* data, uint32_t offset, size_t bufferSize,
                            std::unordered_set<uint32_t>& visited,
                            std::vector<PM64EffectDisplayListInfo>& collected) {
    if (offset >= bufferSize - 8) return;
    if (visited.count(offset)) return;
    visited.insert(offset);

    const uint8_t* ptr = data + offset;
    const uint8_t* endPtr = data + bufferSize;

    PM64EffectDisplayListInfo dlInfo;
    dlInfo.offset = offset;

    while (ptr + 8 <= endPtr) {
        const uint32_t* words = reinterpret_cast<const uint32_t*>(ptr);
        uint32_t w0 = BSWAP32(words[0]);
        uint32_t w1 = BSWAP32(words[1]);
        uint8_t opcode = (w0 >> 24) & 0xFF;

        // G_VTX: w1 is a segment 9 address, convert to segment-relative offset
        if (opcode == F3DEX2_G_VTX) {
            w1 = w1 & 0x00FFFFFF;  // Strip segment byte to get offset within effect data
        }

        // G_SETTIMG: w1 is a segment 9 address, convert to offset
        if (opcode == F3DEX2_G_SETTIMG) {
            w1 = w1 & 0x00FFFFFF;
        }

        // G_MOVEMEM: w1 is a segment 9 address pointing to light/viewport data
        if (opcode == F3DEX2_G_MOVEMEM) {
            w1 = w1 & 0x00FFFFFF;
        }

        // G_DL: w1 is a segment 9 address, convert and recurse
        if (opcode == F3DEX2_G_DL) {
            uint32_t nestedOffset = w1 & 0x00FFFFFF;
            w1 = nestedOffset;
            WalkDisplayList(data, nestedOffset, bufferSize, visited, collected);
        }

        dlInfo.commands.push_back(w0);
        dlInfo.commands.push_back(w1);

        if (opcode == F3DEX2_G_ENDDL) {
            break;
        }
        ptr += 8;
    }

    if (!dlInfo.commands.empty()) {
        collected.push_back(std::move(dlInfo));
    }
}

std::optional<std::shared_ptr<IParsedData>> PM64EffectGfxFactory::parse(std::vector<uint8_t>& buffer, YAML::Node& node) {
    auto offset = GetSafeNode<uint32_t>(node, "offset");
    auto size = GetSafeNode<uint32_t>(node, "size");
    auto dlistsNode = node["dlists"];

    if (offset + size > buffer.size()) {
        SPDLOG_ERROR("PM64:EFFECT_GFX: Data at offset 0x{:X} exceeds buffer (need {}, have {})",
                     offset, size, buffer.size() - offset);
        return std::nullopt;
    }

    // Copy effect graphics data from ROM
    std::vector<uint8_t> effectData(buffer.data() + offset, buffer.data() + offset + size);

    // Walk each display list specified in the YAML
    std::unordered_set<uint32_t> visited;
    std::vector<PM64EffectDisplayListInfo> collectedDLs;

    if (dlistsNode && dlistsNode.IsSequence()) {
        for (size_t i = 0; i < dlistsNode.size(); i++) {
            uint32_t dlOffset = dlistsNode[i].as<uint32_t>();
            if (dlOffset < size) {
                WalkDisplayList(effectData.data(), dlOffset, effectData.size(), visited, collectedDLs);
            }
        }
    }

    SPDLOG_INFO("PM64:EFFECT_GFX: Parsed at 0x{:X}, size=0x{:X}, {} display lists",
                offset, size, collectedDLs.size());

    return std::make_shared<PM64EffectGfxData>(std::move(effectData), std::move(collectedDLs));
}

// Export a display list as an OTR DisplayList resource
static void ExportEffectDisplayList(const std::string& effectName, const PM64EffectDisplayListInfo& dlInfo) {
    char pathBuf[256];
    snprintf(pathBuf, sizeof(pathBuf), "%s/dlist_%X", effectName.c_str(), dlInfo.offset);
    std::string path = pathBuf;
    std::string fullPath = Companion::Instance->RelativePath(path);

    auto writer = LUS::BinaryWriter();
    BaseExporter::WriteHeader(writer, Torch::ResourceType::DisplayList, 0);

    // GBI version byte (F3DEX2)
    writer.Write(static_cast<int8_t>(GBIVersion::f3dex2));

    // Pad to 8-byte alignment
    while (writer.GetBaseAddress() % 8 != 0)
        writer.Write(static_cast<int8_t>(0xFF));

    // G_MARKER with resource hash
    uint64_t hash = CRC64(fullPath.c_str());
    writer.Write(static_cast<uint32_t>(G_MARKER << 24));
    writer.Write(static_cast<uint32_t>(0xBEEFBEEF));
    writer.Write(static_cast<uint32_t>(hash >> 32));
    writer.Write(static_cast<uint32_t>(hash & 0xFFFFFFFF));

    // Write commands, converting to OTR format
    for (size_t i = 0; i < dlInfo.commands.size(); i += 2) {
        uint32_t w0 = dlInfo.commands[i];
        uint32_t w1 = dlInfo.commands[i + 1];
        uint8_t opcode = (w0 >> 24) & 0xFF;

        if (opcode == F3DEX2_G_SETTIMG) {
            // Convert G_SETTIMG to G_SETTIMG_OTR_HASH
            // Build texture resource path from the offset in w1
            char texPath[256];
            snprintf(texPath, sizeof(texPath), "%s/tex_%X", effectName.c_str(), w1);
            std::string fullTexPath = Companion::Instance->RelativePath(texPath);
            uint64_t texHash = CRC64(fullTexPath.c_str());

            // Replace opcode, keep format/size/width bits
            uint32_t newW0 = (G_SETTIMG_OTR_HASH << 24) | (w0 & 0x00FFFFFF);
            writer.Write(newW0);
            writer.Write(static_cast<uint32_t>(0));  // w1 unused for OTR hash variant
            // Extra 8 bytes: hash
            writer.Write(static_cast<uint32_t>(texHash >> 32));
            writer.Write(static_cast<uint32_t>(texHash & 0xFFFFFFFF));
        } else if (opcode == F3DEX2_G_VTX) {
            // Convert G_VTX to G_VTX_OTR_HASH
            // w1 contains the offset within effect data; build vtx resource path
            char vtxPath[256];
            snprintf(vtxPath, sizeof(vtxPath), "%s/vtx_%X", effectName.c_str(), w1);
            std::string fullVtxPath = Companion::Instance->RelativePath(vtxPath);
            uint64_t vtxHash = CRC64(fullVtxPath.c_str());

            uint32_t newW0 = (G_VTX_OTR_HASH << 24) | (w0 & 0x00FFFFFF);
            writer.Write(newW0);
            // w1 = 0: each vertex resource already starts at the correct offset,
            // and the interpreter adds w1 as an offset to the resource pointer
            writer.Write(static_cast<uint32_t>(0));
            writer.Write(static_cast<uint32_t>(vtxHash >> 32));
            writer.Write(static_cast<uint32_t>(vtxHash & 0xFFFFFFFF));
        } else if (opcode == F3DEX2_G_MOVEMEM) {
            // Convert G_MOVEMEM to G_MOVEMEM_OTR_HASH
            char mmPath[256];
            snprintf(mmPath, sizeof(mmPath), "%s/mm_%X", effectName.c_str(), w1);
            std::string fullMmPath = Companion::Instance->RelativePath(mmPath);
            uint64_t mmHash = CRC64(fullMmPath.c_str());

            // Extract index and compute actual offset from N64 command encoding
            uint8_t index = w0 & 0xFF;
            uint8_t offset = ((w0 >> 8) & 0xFF) * 8;

            writer.Write(static_cast<uint32_t>(G_MOVEMEM_OTR_HASH << 24));
            writer.Write(static_cast<uint32_t>((index << 24) | (offset << 16)));
            writer.Write(static_cast<uint32_t>(mmHash >> 32));
            writer.Write(static_cast<uint32_t>(mmHash & 0xFFFFFFFF));
        } else if (opcode == F3DEX2_G_DL) {
            // Convert G_DL to G_DL_OTR_HASH
            char nestedPath[256];
            snprintf(nestedPath, sizeof(nestedPath), "%s/dlist_%X", effectName.c_str(), w1);
            std::string fullNestedPath = Companion::Instance->RelativePath(nestedPath);
            uint64_t nestedHash = CRC64(fullNestedPath.c_str());

            // Determine push/nopush from original w0 bits
            // G_DL_OTR_HASH=0x31, G_DL_PUSH=0, G_DL_NOPUSH=1
            uint8_t pushFlag = (w0 >> 16) & 0x01;
            uint32_t otrW0 = (0x31u << 24) | (pushFlag << 16);
            writer.Write(otrW0);
            writer.Write(static_cast<uint32_t>(0));
            writer.Write(static_cast<uint32_t>(nestedHash >> 32));
            writer.Write(static_cast<uint32_t>(nestedHash & 0xFFFFFFFF));
        } else {
            // Standard 8-byte command
            writer.Write(w0);
            writer.Write(w1);
        }
    }

    std::stringstream ss;
    writer.Finish(ss);
    std::string str = ss.str();
    std::vector<char> data(str.begin(), str.end());
    Companion::Instance->RegisterCompanionFile(path, data);
}

// Export vertex data as a Blob resource at a specific offset
static void ExportVertexBlob(const std::string& effectName, const uint8_t* data,
                              uint32_t offset, uint32_t size, uint32_t totalSize) {
    // Byte-swap vertex data: Vtx_t is 16 bytes
    // ob[3] (3×s16), flag (u16), tc[2] (2×s16), cn[4] (4×u8)
    // We need a mutable copy for swapping
    std::vector<uint8_t> vtxData(data + offset, data + offset + size);

    for (uint32_t i = 0; i + 16 <= size; i += 16) {
        uint16_t* v = reinterpret_cast<uint16_t*>(vtxData.data() + i);
        v[0] = BSWAP16(v[0]); // ob[0]
        v[1] = BSWAP16(v[1]); // ob[1]
        v[2] = BSWAP16(v[2]); // ob[2]
        v[3] = BSWAP16(v[3]); // flag
        v[4] = BSWAP16(v[4]); // tc[0]
        v[5] = BSWAP16(v[5]); // tc[1]
        // cn[4] are bytes, no swap
    }

    char pathBuf[256];
    snprintf(pathBuf, sizeof(pathBuf), "%s/vtx_%X", effectName.c_str(), offset);
    std::string path = pathBuf;

    auto writer = LUS::BinaryWriter();
    BaseExporter::WriteHeader(writer, Torch::ResourceType::Blob, 0);
    writer.Write(static_cast<uint32_t>(size));
    writer.Write(reinterpret_cast<char*>(vtxData.data()), size);

    std::stringstream ss;
    writer.Finish(ss);
    std::string str = ss.str();
    std::vector<char> fileData(str.begin(), str.end());
    Companion::Instance->RegisterCompanionFile(path, fileData);
}

// Map N64 fmt/siz to Torch TextureType enum value
// TextureType: Error=0, RGBA32=1, RGBA16=2, CI4=3, CI8=4, I4=5, I8=6, IA4=7, IA8=8, IA16=9
static uint32_t N64FmtSizToTextureType(uint32_t fmt, uint32_t siz) {
    switch (fmt) {
        case 0: // G_IM_FMT_RGBA
            return (siz == 3) ? 1 : 2;  // RGBA32bpp or RGBA16bpp
        case 2: // G_IM_FMT_CI
            return (siz == 0) ? 3 : 4;  // Palette4bpp or Palette8bpp
        case 4: // G_IM_FMT_I
            return (siz == 0) ? 5 : 6;  // Grayscale4bpp or Grayscale8bpp
        case 3: // G_IM_FMT_IA
            if (siz == 0) return 7;      // GrayscaleAlpha4bpp
            if (siz == 1) return 8;      // GrayscaleAlpha8bpp
            return 9;                    // GrayscaleAlpha16bpp
        default:
            return 2;  // Default to RGBA16bpp
    }
}

// Export texture/palette data as a Texture resource (V1 format with TEX_FLAG_LOAD_AS_RAW)
// The F3D renderer's G_SETTIMG_OTR_HASH handler loads resources as Fast::Texture,
// so we must export in Texture format, not Blob.
static void ExportTextureResource(const std::string& effectName, const uint8_t* data,
                                   uint32_t offset, uint32_t size, const char* prefix,
                                   uint32_t settimgW0) {
    if (offset + size > 0x100000) return;  // Sanity check

    char pathBuf[256];
    snprintf(pathBuf, sizeof(pathBuf), "%s/%s_%X", effectName.c_str(), prefix, offset);
    std::string path = pathBuf;

    // Extract format info from the G_SETTIMG w0 word
    uint32_t fmt = (settimgW0 >> 21) & 0x7;
    uint32_t siz = (settimgW0 >> 19) & 0x3;
    uint32_t width = (settimgW0 & 0xFFF) + 1;

    // Compute height from data size and pixel format
    uint32_t bitsPerPixel;
    switch (siz) {
        case 0: bitsPerPixel = 4; break;
        case 1: bitsPerPixel = 8; break;
        case 2: bitsPerPixel = 16; break;
        case 3: bitsPerPixel = 32; break;
        default: bitsPerPixel = 16; break;
    }
    uint32_t bytesPerRow = (width * bitsPerPixel + 7) / 8;
    uint32_t height = (bytesPerRow > 0) ? (size / bytesPerRow) : 1;
    if (height == 0) height = 1;

    auto writer = LUS::BinaryWriter();
    // V1 format includes Flags, HByteScale, VPixelScale
    BaseExporter::WriteHeader(writer, Torch::ResourceType::Texture, 1);
    writer.Write(N64FmtSizToTextureType(fmt, siz));   // Type
    writer.Write(width);                               // Width
    writer.Write(height);                              // Height
    writer.Write(static_cast<uint32_t>(0));            // Flags: none (use tile format for conversion)
    writer.Write(1.0f);                                // HByteScale
    writer.Write(1.0f);                                // VPixelScale
    writer.Write(static_cast<uint32_t>(size));         // ImageDataSize
    writer.Write(const_cast<char*>(reinterpret_cast<const char*>(data + offset)), size);

    std::stringstream ss;
    writer.Finish(ss);
    std::string str = ss.str();
    std::vector<char> fileData(str.begin(), str.end());
    Companion::Instance->RegisterCompanionFile(path, fileData);
}

// Export G_MOVEMEM data (lights, viewports) as a Blob resource
static void ExportMovememBlob(const std::string& effectName, const uint8_t* data,
                               uint32_t offset, uint32_t size, uint8_t index) {
    std::vector<uint8_t> mmData(data + offset, data + offset + size);

    // Viewport data has s16 fields that need byte-swap
    if (index == 0x08) { // G_MV_VIEWPORT
        for (uint32_t i = 0; i + 2 <= size; i += 2) {
            uint16_t* v = reinterpret_cast<uint16_t*>(mmData.data() + i);
            *v = BSWAP16(*v);
        }
    }
    // Light data is all u8/s8 fields, no swap needed

    char pathBuf[256];
    snprintf(pathBuf, sizeof(pathBuf), "%s/mm_%X", effectName.c_str(), offset);
    std::string path = pathBuf;

    auto writer = LUS::BinaryWriter();
    BaseExporter::WriteHeader(writer, Torch::ResourceType::Blob, 0);
    writer.Write(static_cast<uint32_t>(size));
    writer.Write(reinterpret_cast<char*>(mmData.data()), size);

    std::stringstream ss;
    writer.Finish(ss);
    std::string str = ss.str();
    std::vector<char> fileData(str.begin(), str.end());
    Companion::Instance->RegisterCompanionFile(path, fileData);
}

ExportResult PM64EffectGfxBinaryExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    auto effectData = std::static_pointer_cast<PM64EffectGfxData>(raw);

    // Extract effect name from entry path
    std::string effectName = entryName;
    size_t lastSlash = entryName.rfind('/');
    if (lastSlash != std::string::npos) {
        effectName = entryName.substr(lastSlash + 1);
    }

    // Collect all vertex offsets and texture offsets referenced by display lists
    std::unordered_set<uint32_t> vtxOffsets;
    std::unordered_map<uint32_t, uint32_t> texInfo;  // offset → G_SETTIMG w0

    for (const auto& dl : effectData->mDisplayLists) {
        for (size_t i = 0; i < dl.commands.size(); i += 2) {
            uint32_t w0 = dl.commands[i];
            uint32_t w1 = dl.commands[i + 1];
            uint8_t opcode = (w0 >> 24) & 0xFF;

            if (opcode == F3DEX2_G_VTX) {
                vtxOffsets.insert(w1);
            } else if (opcode == F3DEX2_G_SETTIMG) {
                if (texInfo.find(w1) == texInfo.end()) {
                    texInfo[w1] = w0;  // Store w0 for format/size/width info
                }
            } else if (opcode == F3DEX2_G_MOVEMEM) {
                // Collect movemem references (lights, viewports)
                // Will be exported as blob resources
            }
        }
    }

    // Export vertex blobs
    // For each vertex offset, compute a reasonable size
    // Sort offsets and use gaps between them, or fall back to a default
    std::vector<uint32_t> sortedVtxOffsets(vtxOffsets.begin(), vtxOffsets.end());
    std::sort(sortedVtxOffsets.begin(), sortedVtxOffsets.end());

    for (size_t i = 0; i < sortedVtxOffsets.size(); i++) {
        uint32_t vtxOff = sortedVtxOffsets[i];
        // Extract N count from the G_VTX command that references this offset
        // to compute exact size. For now, find the command that uses this offset.
        uint32_t vtxSize = 0;
        for (const auto& dl : effectData->mDisplayLists) {
            for (size_t j = 0; j < dl.commands.size(); j += 2) {
                uint32_t w0 = dl.commands[j];
                uint32_t w1 = dl.commands[j + 1];
                uint8_t op = (w0 >> 24) & 0xFF;
                if (op == F3DEX2_G_VTX && w1 == vtxOff) {
                    uint32_t n = (w0 >> 12) & 0xFF;
                    uint32_t candidateSize = n * 16;
                    if (candidateSize > vtxSize) vtxSize = candidateSize;
                }
            }
        }
        if (vtxSize == 0) vtxSize = 256;  // Fallback
        if (vtxOff + vtxSize <= effectData->mBuffer.size()) {
            ExportVertexBlob(effectName, effectData->mBuffer.data(), vtxOff, vtxSize, effectData->mBuffer.size());
        }
    }

    // Export texture resources
    // Texture size is harder to determine without parsing G_LOADBLOCK/G_LOADTILE.
    // We'll use the gap between consecutive texture offsets, or a default.
    std::vector<uint32_t> sortedTexOffsets;
    for (const auto& [off, w0] : texInfo) {
        sortedTexOffsets.push_back(off);
    }
    std::sort(sortedTexOffsets.begin(), sortedTexOffsets.end());

    for (size_t i = 0; i < sortedTexOffsets.size(); i++) {
        uint32_t texOff = sortedTexOffsets[i];
        uint32_t texSize;
        if (i + 1 < sortedTexOffsets.size()) {
            texSize = sortedTexOffsets[i + 1] - texOff;
        } else {
            // Last texture - estimate size. Use distance to next known structure or default.
            // Look for the minimum dlist/vtx offset that's after this texture
            uint32_t nextOff = effectData->mBuffer.size();
            for (const auto& dl : effectData->mDisplayLists) {
                if (dl.offset > texOff && dl.offset < nextOff) {
                    nextOff = dl.offset;
                }
            }
            for (uint32_t vo : sortedVtxOffsets) {
                if (vo > texOff && vo < nextOff) {
                    nextOff = vo;
                }
            }
            texSize = nextOff - texOff;
        }
        if (texOff + texSize <= effectData->mBuffer.size()) {
            ExportTextureResource(effectName, effectData->mBuffer.data(), texOff, texSize, "tex", texInfo[texOff]);
        }
    }

    // Export movemem data blobs (lights, viewports)
    std::unordered_map<uint32_t, uint32_t> mmInfo;  // offset → w0
    for (const auto& dl : effectData->mDisplayLists) {
        for (size_t i = 0; i < dl.commands.size(); i += 2) {
            uint32_t w0 = dl.commands[i];
            uint32_t w1 = dl.commands[i + 1];
            uint8_t opcode = (w0 >> 24) & 0xFF;
            if (opcode == F3DEX2_G_MOVEMEM) {
                if (mmInfo.find(w1) == mmInfo.end()) {
                    mmInfo[w1] = w0;
                }
            }
        }
    }
    for (const auto& [mmOff, mmW0] : mmInfo) {
        uint8_t index = mmW0 & 0xFF;
        uint32_t sizeField = (mmW0 >> 19) & 0x1F;
        uint32_t dataSize = (sizeField + 1) * 8;
        if (mmOff + dataSize <= effectData->mBuffer.size()) {
            ExportMovememBlob(effectName, effectData->mBuffer.data(), mmOff, dataSize, index);
        }
    }

    // Export each display list
    for (const auto& dl : effectData->mDisplayLists) {
        ExportEffectDisplayList(effectName, dl);
    }

    // Write main blob (entire effect data for any direct references)
    auto writer = LUS::BinaryWriter();
    WriteHeader(writer, Torch::ResourceType::Blob, 0);
    writer.Write(static_cast<uint32_t>(effectData->mBuffer.size()));
    writer.Write(reinterpret_cast<char*>(effectData->mBuffer.data()), effectData->mBuffer.size());
    writer.Finish(write);

    return std::nullopt;
}

ExportResult PM64EffectGfxHeaderExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    // Header generation is handled by the Python script (include/assets/effects.h)
    // This exporter is a no-op
    return std::nullopt;
}
