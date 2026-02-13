#include "PM64MapTextureFactory.h"
#include "Companion.h"
#include "utils/Decompressor.h"
#include "spdlog/spdlog.h"
#include <ship/utils/binarytools/endianness.h>

// PM64 TextureHeader structure (0x30 bytes):
//   0x00: name[32] - texture name string
//   0x20: auxW (u16)
//   0x22: mainW (u16)
//   0x24: auxH (u16)
//   0x26: mainH (u16)
//   0x28: isVariant (u8)
//   0x29: extraTiles (u8)
//   0x2A: auxCombineType:6, auxCombineSubType:2 (u8)
//   0x2B: auxFmt:4, mainFmt:4 (u8)
//   0x2C: auxBitDepth:4, mainBitDepth:4 (u8)
//   0x2D: auxWrapW:4, mainWrapW:4 (u8)
//   0x2E: auxWrapH:4, mainWrapH:4 (u8)
//   0x2F: filtering (u8)

static constexpr size_t TEXTURE_HEADER_SIZE = 0x30;

// Image format/bit depth constants (matching N64 GBI)
enum ImgFmt {
    G_IM_FMT_RGBA = 0,
    G_IM_FMT_YUV = 1,
    G_IM_FMT_CI = 2,
    G_IM_FMT_IA = 3,
    G_IM_FMT_I = 4,
};

enum ImgSiz {
    G_IM_SIZ_4b = 0,
    G_IM_SIZ_8b = 1,
    G_IM_SIZ_16b = 2,
    G_IM_SIZ_32b = 3,
};

enum ExtraTiles {
    EXTRA_TILE_NONE = 0,
    EXTRA_TILE_MIPMAPS = 1,
    EXTRA_TILE_AUX_SAME_AS_MAIN = 2,
    EXTRA_TILE_AUX_INDEPENDENT = 3,
};

static void ByteSwapTextureHeader(uint8_t* headerPtr) {
    // Byte-swap u16 fields at offsets 0x20, 0x22, 0x24, 0x26
    uint16_t* auxW = reinterpret_cast<uint16_t*>(headerPtr + 0x20);
    uint16_t* mainW = reinterpret_cast<uint16_t*>(headerPtr + 0x22);
    uint16_t* auxH = reinterpret_cast<uint16_t*>(headerPtr + 0x24);
    uint16_t* mainH = reinterpret_cast<uint16_t*>(headerPtr + 0x26);

    *auxW = BSWAP16(*auxW);
    *mainW = BSWAP16(*mainW);
    *auxH = BSWAP16(*auxH);
    *mainH = BSWAP16(*mainH);

    // Fix bitfield byte layout for little-endian.
    // On N64 (big-endian), GCC lays out the first-declared bitfield in the UPPER bits.
    // On LE (ARM64/x86), the first-declared bitfield occupies the LOWER bits.
    // The TextureHeader struct has paired bitfields within single bytes:
    //   0x2A: auxCombineType:6, auxCombineSubType:2
    //   0x2B: auxFmt:4, mainFmt:4
    //   0x2C: auxBitDepth:4, mainBitDepth:4
    //   0x2D: auxWrapW:4, mainWrapW:4
    //   0x2E: auxWrapH:4, mainWrapH:4
    // Without rearranging, the LE struct reads mainFmt where auxFmt should be (and vice versa).

    // 0x2A: 6:2 split — N64 byte = (combineType << 2) | combineSubType
    // LE needs: combineType | (combineSubType << 6)
    uint8_t b = headerPtr[0x2A];
    headerPtr[0x2A] = ((b >> 2) & 0x3F) | ((b & 0x03) << 6);

    // 0x2B-0x2E: 4:4 splits — swap nibbles
    for (int i = 0x2B; i <= 0x2E; i++) {
        b = headerPtr[i];
        headerPtr[i] = ((b & 0x0F) << 4) | ((b >> 4) & 0x0F);
    }
}

// Calculate raster size for a texture (including mipmaps if present)
static uint32_t CalculateRasterSize(uint16_t width, uint16_t height, uint8_t bitDepth, uint8_t extraTiles) {
    uint32_t rasterSize = width * height;

    // Compute mipmaps size if present
    if (extraTiles == EXTRA_TILE_MIPMAPS) {
        if (bitDepth == G_IM_SIZ_4b) {
            int d = 2;
            while (width / d >= 16 && height / d > 0) {
                rasterSize += (width / d) * (height / d);
                d *= 2;
            }
        } else if (bitDepth == G_IM_SIZ_8b) {
            int d = 2;
            while (width / d >= 8 && height / d > 0) {
                rasterSize += (width / d) * (height / d);
                d *= 2;
            }
        } else if (bitDepth == G_IM_SIZ_16b) {
            int d = 2;
            while (width / d >= 4 && height / d > 0) {
                rasterSize += (width / d) * (height / d);
                d *= 2;
            }
        } else if (bitDepth == G_IM_SIZ_32b) {
            int d = 2;
            while (width / d >= 2 && height / d > 0) {
                rasterSize += (width / d) * (height / d);
                d *= 2;
            }
        }
    }

    // Scale by bit depth
    if (bitDepth == G_IM_SIZ_4b) {
        rasterSize /= 2;
    } else if (bitDepth == G_IM_SIZ_16b) {
        rasterSize *= 2;
    } else if (bitDepth == G_IM_SIZ_32b) {
        rasterSize *= 4;
    }

    return rasterSize;
}

// Calculate palette size for a texture
static uint32_t CalculatePaletteSize(uint8_t fmt, uint8_t bitDepth) {
    if (fmt == G_IM_FMT_CI) {
        return (bitDepth == G_IM_SIZ_8b) ? 0x200 : 0x20;
    }
    return 0;
}

static void ByteSwapAllTextureHeaders(uint8_t* data, size_t size) {
    size_t offset = 0;

    while (offset + TEXTURE_HEADER_SIZE <= size) {
        uint8_t* headerPtr = data + offset;

        // Check if this looks like a valid texture header (name should be ASCII)
        bool validName = true;
        for (int i = 0; i < 32 && headerPtr[i] != 0; i++) {
            if (headerPtr[i] < 0x20 || headerPtr[i] > 0x7E) {
                validName = false;
                break;
            }
        }

        if (!validName) {
            // End of texture list or invalid data
            break;
        }

        // Read header fields (still in big-endian at this point)
        uint16_t mainW = (headerPtr[0x22] << 8) | headerPtr[0x23];
        uint16_t mainH = (headerPtr[0x26] << 8) | headerPtr[0x27];
        uint16_t auxW = (headerPtr[0x20] << 8) | headerPtr[0x21];
        uint16_t auxH = (headerPtr[0x24] << 8) | headerPtr[0x25];
        uint8_t extraTiles = headerPtr[0x29];
        uint8_t mainBitDepth = headerPtr[0x2C] & 0x0F;
        uint8_t mainFmt = headerPtr[0x2B] & 0x0F;
        uint8_t auxBitDepth = (headerPtr[0x2C] >> 4) & 0x0F;
        uint8_t auxFmt = (headerPtr[0x2B] >> 4) & 0x0F;

        // Validate dimensions
        if (mainW == 0 || mainH == 0 || mainW > 1024 || mainH > 1024) {
            break;
        }

        // Byte-swap this header
        ByteSwapTextureHeader(headerPtr);

        // Calculate texture data size to skip to next header
        uint32_t rasterSize = CalculateRasterSize(mainW, mainH, mainBitDepth, extraTiles);
        uint32_t paletteSize = CalculatePaletteSize(mainFmt, mainBitDepth);

        uint32_t auxRasterSize = 0;
        uint32_t auxPaletteSize = 0;
        if (extraTiles == EXTRA_TILE_AUX_INDEPENDENT) {
            auxRasterSize = CalculateRasterSize(auxW, auxH, auxBitDepth, EXTRA_TILE_NONE);
            auxPaletteSize = CalculatePaletteSize(auxFmt, auxBitDepth);
        }

        // Move to next texture entry
        offset += TEXTURE_HEADER_SIZE + rasterSize + paletteSize + auxRasterSize + auxPaletteSize;
    }

    SPDLOG_DEBUG("Byte-swapped texture headers up to offset 0x{:X}", offset);
}

std::optional<std::shared_ptr<IParsedData>> PM64MapTextureFactory::parse(std::vector<uint8_t>& buffer, YAML::Node& node) {
    auto offset = GetSafeNode<uint32_t>(node, "offset");

    // Check if compressed (YAY0)
    auto compressionType = Decompressor::GetCompressionType(buffer, offset);

    std::vector<uint8_t> textureData;

    if (compressionType == CompressionType::YAY0) {
        auto decoded = Decompressor::Decode(buffer, offset, CompressionType::YAY0);
        if (!decoded || decoded->size == 0) {
            SPDLOG_ERROR("Failed to decompress YAY0 map texture data at offset 0x{:X}", offset);
            return std::nullopt;
        }

        textureData.assign(decoded->data, decoded->data + decoded->size);
        SPDLOG_INFO("PM64:MAP_TEXTURE decompressed from YAY0 at 0x{:X}, size: {}", offset, textureData.size());
    } else {
        // Uncompressed - read raw data
        // For uncompressed textures, we need to determine the size from somewhere
        // Usually specified in YAML or we read until we hit invalid data
        auto sizeOpt = GetSafeNode<size_t>(node, "size", 0);
        size_t size = sizeOpt;

        if (size == 0) {
            // Try to auto-detect size by scanning for valid texture headers
            // This is a fallback - normally size should be in YAML
            size = 0x40000; // Max reasonable size
        }

        if (offset + size > buffer.size()) {
            size = buffer.size() - offset;
        }

        textureData.assign(buffer.begin() + offset, buffer.begin() + offset + size);
        SPDLOG_INFO("PM64:MAP_TEXTURE raw at 0x{:X}, size: {}", offset, textureData.size());
    }

    // Byte-swap all texture headers in the data
    ByteSwapAllTextureHeaders(textureData.data(), textureData.size());

    return std::make_shared<RawBuffer>(textureData);
}

ExportResult PM64MapTextureBinaryExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    auto writer = LUS::BinaryWriter();
    auto data = std::static_pointer_cast<RawBuffer>(raw)->mBuffer;

    // Write as Blob type - game loads as raw binary
    WriteHeader(writer, Torch::ResourceType::Blob, 0);
    writer.Write(static_cast<uint32_t>(data.size()));
    writer.Write(reinterpret_cast<char*>(data.data()), data.size());
    writer.Finish(write);

    return std::nullopt;
}

ExportResult PM64MapTextureHeaderExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    const auto symbol = GetSafeNode(node, "symbol", entryName);

    if (Companion::Instance->IsOTRMode()) {
        write << "static const ALIGN_ASSET(2) char " << symbol << "[] = \"__OTR__" << (*replacement) << "\";\n\n";
        return std::nullopt;
    }

    write << "extern u8 " << symbol << "[];\n";
    return std::nullopt;
}
