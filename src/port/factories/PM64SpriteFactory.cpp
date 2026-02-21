#include "PM64SpriteFactory.h"
#include "Companion.h"
#include "utils/Decompressor.h"
#include "spdlog/spdlog.h"
#include <ship/utils/binarytools/endianness.h>
#include <unordered_set>

// PM64 sprite structure (decompressed, before byte-swap):
// 0x00: rastersOffset (u32)
// 0x04: palettesOffset (u32)
// 0x08: maxComponents (s32)
// 0x0C: colorVariations (s32)
// 0x10+: animListStart[] - variable length, -1 terminated

static void ByteSwapSpriteData(uint8_t* data, size_t size) {
    if (size < 16) {
        SPDLOG_WARN("Sprite data too small: {}", size);
        return;
    }

    // Byte-swap the header fields (first 4 u32s)
    uint32_t* header = reinterpret_cast<uint32_t*>(data);
    uint32_t rastersOffset = BSWAP32(header[0]);
    uint32_t palettesOffset = BSWAP32(header[1]);

    header[0] = rastersOffset;
    header[1] = palettesOffset;
    header[2] = BSWAP32(header[2]); // maxComponents
    header[3] = BSWAP32(header[3]); // colorVariations

    // Byte-swap animListStart array (starts at offset 0x10)
    // Each entry is a u32 offset, terminated by -1 (0xFFFFFFFF)
    uint32_t* animList = reinterpret_cast<uint32_t*>(data + 0x10);
    while (reinterpret_cast<uint8_t*>(animList) < data + size) {
        uint32_t val = BSWAP32(*animList);
        *animList = val;
        if (val == 0xFFFFFFFF) {
            break;
        }
        animList++;
    }

    // Byte-swap raster array entries
    // Each raster pointer entry is a u32 offset, terminated by -1
    if (rastersOffset > 0 && rastersOffset < size) {
        uint32_t* rasterList = reinterpret_cast<uint32_t*>(data + rastersOffset);
        while (reinterpret_cast<uint8_t*>(rasterList) < data + size) {
            uint32_t val = BSWAP32(*rasterList);
            *rasterList = val;
            if (val == 0xFFFFFFFF) {
                break;
            }

            // Each raster entry (SpriteRasterCacheEntry) at the pointed offset:
            // 0x00: image offset (u32)
            // 0x04: width (u8), height (u8), palette (s8), quadCacheIndex (s8)
            // Only the image offset (u32) needs byte-swap
            if (val > 0 && val < size - 4) {
                uint32_t* rasterEntry = reinterpret_cast<uint32_t*>(data + val);
                *rasterEntry = BSWAP32(*rasterEntry);
            }

            rasterList++;
        }
    }

    // Byte-swap palette array entries
    // Each palette pointer entry is a u32 offset, terminated by -1
    if (palettesOffset > 0 && palettesOffset < size) {
        uint32_t* paletteList = reinterpret_cast<uint32_t*>(data + palettesOffset);
        while (reinterpret_cast<uint8_t*>(paletteList) < data + size) {
            uint32_t val = BSWAP32(*paletteList);
            *paletteList = val;
            if (val == 0xFFFFFFFF) {
                break;
            }
            paletteList++;
        }
    }

    // Byte-swap animation component lists and commands
    // Walk through each animation in animListStart
    // IMPORTANT: PM64 sprites share data extensively - multiple animations can reference
    // the same component list, component structure, or command list. Track processed
    // offsets to prevent double-swapping (which would revert data to big-endian).
    std::unordered_set<uint32_t> processedAnimLists;
    std::unordered_set<uint32_t> processedComps;
    std::unordered_set<uint32_t> processedCmdLists;

    uint32_t* animListPtr = reinterpret_cast<uint32_t*>(data + 0x10);
    while (reinterpret_cast<uint8_t*>(animListPtr) < data + size) {
        uint32_t animOffset = *animListPtr;
        if (animOffset == 0xFFFFFFFF) {
            break;
        }

        if (animOffset > 0 && animOffset < size && !processedAnimLists.count(animOffset)) {
            processedAnimLists.insert(animOffset);

            // Each animation is a list of SpriteAnimComponent pointers, -1 terminated
            uint32_t* compList = reinterpret_cast<uint32_t*>(data + animOffset);
            while (reinterpret_cast<uint8_t*>(compList) < data + size) {
                uint32_t compOffset = BSWAP32(*compList);
                *compList = compOffset;
                if (compOffset == 0xFFFFFFFF) {
                    break;
                }

                if (compOffset > 0 && compOffset < size - 12 && !processedComps.count(compOffset)) {
                    processedComps.insert(compOffset);

                    // SpriteAnimComponent structure:
                    // 0x00: cmdList offset (u32)
                    // 0x04: cmdListSize (s16)
                    // 0x06: compOffset Vec3s (3 x s16)
                    uint32_t* compData = reinterpret_cast<uint32_t*>(data + compOffset);
                    uint32_t cmdListOffset = BSWAP32(compData[0]);
                    compData[0] = cmdListOffset;

                    uint16_t* compData16 = reinterpret_cast<uint16_t*>(data + compOffset + 4);
                    int16_t cmdListSize = static_cast<int16_t>(BSWAP16(compData16[0]));
                    compData16[0] = cmdListSize;
                    compData16[1] = BSWAP16(compData16[1]); // compOffset.x
                    compData16[2] = BSWAP16(compData16[2]); // compOffset.y
                    compData16[3] = BSWAP16(compData16[3]); // compOffset.z

                    // Byte-swap command list (array of u16)
                    if (cmdListOffset > 0 && cmdListOffset < size && cmdListSize > 0 && !processedCmdLists.count(cmdListOffset)) {
                        processedCmdLists.insert(cmdListOffset);

                        uint16_t* cmdList = reinterpret_cast<uint16_t*>(data + cmdListOffset);
                        int numCmds = cmdListSize / 2;
                        for (int i = 0; i < numCmds && reinterpret_cast<uint8_t*>(&cmdList[i]) < data + size; i++) {
                            cmdList[i] = BSWAP16(cmdList[i]);
                        }
                    }
                }
                compList++;
            }
        }
        animListPtr++;
    }

    // Palette pixel data (RGBA5551) is NOT byte-swapped.
    // The Fast3D interpreter reads palette bytes as big-endian:
    //   col16 = (palette[idx*2] << 8) | palette[idx*2+1]
    // so the raw ROM byte order must be preserved.
}

std::optional<std::shared_ptr<IParsedData>> PM64SpriteFactory::parse(std::vector<uint8_t>& buffer, YAML::Node& node) {
    // Get the offset from YAML
    auto offset = GetSafeNode<uint32_t>(node, "offset");

    // Check if this is compressed (YAY0)
    auto compressionType = Decompressor::GetCompressionType(buffer, offset);

    if (compressionType == CompressionType::YAY0) {
        // Decompress YAY0 data
        auto decoded = Decompressor::Decode(buffer, offset, CompressionType::YAY0);
        if (!decoded || decoded->size == 0) {
            SPDLOG_ERROR("Failed to decompress YAY0 sprite data at offset 0x{:X}", offset);
            return std::nullopt;
        }

        // Create a copy of decompressed data for byte-swapping
        std::vector<uint8_t> spriteData(decoded->data, decoded->data + decoded->size);

        // Byte-swap for little-endian
        ByteSwapSpriteData(spriteData.data(), spriteData.size());

        SPDLOG_DEBUG("PM64:SPRITE parsed at 0x{:X}, decompressed size: {}", offset, spriteData.size());

        return std::make_shared<RawBuffer>(spriteData);
    } else {
        // Uncompressed - just read raw data with size from YAML
        auto size = GetSafeNode<size_t>(node, "size");
        auto [_, segment] = Decompressor::AutoDecode(node, buffer, size);

        std::vector<uint8_t> spriteData(segment.data, segment.data + segment.size);
        ByteSwapSpriteData(spriteData.data(), spriteData.size());

        return std::make_shared<RawBuffer>(spriteData);
    }
}

ExportResult PM64SpriteBinaryExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    auto writer = LUS::BinaryWriter();
    auto data = std::static_pointer_cast<RawBuffer>(raw)->mBuffer;

    // Write as Blob type for now - game will load as raw binary
    WriteHeader(writer, Torch::ResourceType::Blob, 0);
    writer.Write(static_cast<uint32_t>(data.size()));
    writer.Write(reinterpret_cast<char*>(data.data()), data.size());
    writer.Finish(write);

    return std::nullopt;
}

ExportResult PM64SpriteHeaderExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    const auto symbol = GetSafeNode(node, "symbol", entryName);

    if (Companion::Instance->IsOTRMode()) {
        write << "static const ALIGN_ASSET(2) char " << symbol << "[] = \"__OTR__" << (*replacement) << "\";\n\n";
        return std::nullopt;
    }

    write << "extern u8 " << symbol << "[];\n";
    return std::nullopt;
}
