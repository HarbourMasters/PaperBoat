#include "PM64BackgroundFactory.h"
#include "Companion.h"
#include "utils/Decompressor.h"
#include "spdlog/spdlog.h"
#include <ship/utils/binarytools/endianness.h>

// PM64 background file structure (N64 ROM format):
// BackgroundHeader (0x10 bytes):
//   0x00: rasterOffset (u32) - offset from start of data to CI8 raster
//   0x04: paletteOffset (u32) - offset from start of data to RGBA16 palette
//   0x08: startX (u16)
//   0x0A: startY (u16)
//   0x0C: width (u16)
//   0x0E: height (u16)
//
// Followed by:
//   - Raster data: width * height bytes (CI8 indexed color, no swap needed)
//   - Palette data: 256 * 2 bytes (RGBA16, needs u16 swap)

static void ByteSwapBackgroundData(uint8_t* data, size_t size) {
    if (size < 0x10) {
        SPDLOG_WARN("Background data too small: {}", size);
        return;
    }

    // Byte-swap header fields at fixed offsets
    uint32_t* header32 = reinterpret_cast<uint32_t*>(data);
    uint16_t* header16 = reinterpret_cast<uint16_t*>(data);

    // Swap 32-bit offset fields
    uint32_t rasterOffset = BSWAP32(header32[0]);
    uint32_t paletteOffset = BSWAP32(header32[1]);
    header32[0] = rasterOffset;
    header32[1] = paletteOffset;

    // Swap 16-bit dimension fields
    header16[4] = BSWAP16(header16[4]);  // startX at offset 0x08
    header16[5] = BSWAP16(header16[5]);  // startY at offset 0x0A
    header16[6] = BSWAP16(header16[6]);  // width at offset 0x0C
    header16[7] = BSWAP16(header16[7]);  // height at offset 0x0E

    SPDLOG_DEBUG("Background header: rasterOffset=0x{:X}, paletteOffset=0x{:X}, startX={}, startY={}, width={}, height={}",
                 rasterOffset, paletteOffset,
                 header16[4], header16[5], header16[6], header16[7]);

    // Byte-swap palette data (256 x u16 RGBA16)
    if (paletteOffset > 0 && paletteOffset + 512 <= size) {
        uint16_t* palette = reinterpret_cast<uint16_t*>(data + paletteOffset);
        for (int i = 0; i < 256; i++) {
            palette[i] = BSWAP16(palette[i]);
        }
        SPDLOG_DEBUG("Byte-swapped 256 palette entries at offset 0x{:X}", paletteOffset);
    }

    // Raster data is CI8 (byte indices) - no swap needed
}

std::optional<std::shared_ptr<IParsedData>> PM64BackgroundFactory::parse(std::vector<uint8_t>& buffer, YAML::Node& node) {
    auto offset = GetSafeNode<uint32_t>(node, "offset");

    // Check if compressed (YAY0)
    auto compressionType = Decompressor::GetCompressionType(buffer, offset);

    if (compressionType == CompressionType::YAY0) {
        auto decoded = Decompressor::Decode(buffer, offset, CompressionType::YAY0);
        if (!decoded || decoded->size == 0) {
            SPDLOG_ERROR("Failed to decompress YAY0 background data at offset 0x{:X}", offset);
            return std::nullopt;
        }

        std::vector<uint8_t> bgData(decoded->data, decoded->data + decoded->size);
        ByteSwapBackgroundData(bgData.data(), bgData.size());

        SPDLOG_INFO("PM64:BACKGROUND parsed at 0x{:X}, decompressed size: {}", offset, bgData.size());

        return std::make_shared<RawBuffer>(bgData);
    } else {
        // Uncompressed - read raw data with size from YAML
        auto size = GetSafeNode<size_t>(node, "size");
        auto [_, segment] = Decompressor::AutoDecode(node, buffer, size);

        std::vector<uint8_t> bgData(segment.data, segment.data + segment.size);
        ByteSwapBackgroundData(bgData.data(), bgData.size());

        return std::make_shared<RawBuffer>(bgData);
    }
}

ExportResult PM64BackgroundBinaryExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    auto writer = LUS::BinaryWriter();
    auto data = std::static_pointer_cast<RawBuffer>(raw)->mBuffer;

    // Write as Blob type - game loads as raw binary
    WriteHeader(writer, Torch::ResourceType::Blob, 0);
    writer.Write(static_cast<uint32_t>(data.size()));
    writer.Write(reinterpret_cast<char*>(data.data()), data.size());
    writer.Finish(write);

    return std::nullopt;
}

ExportResult PM64BackgroundHeaderExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    const auto symbol = GetSafeNode(node, "symbol", entryName);

    if (Companion::Instance->IsOTRMode()) {
        write << "static const ALIGN_ASSET(2) char " << symbol << "[] = \"__OTR__" << (*replacement) << "\";\n\n";
        return std::nullopt;
    }

    write << "extern u8 " << symbol << "[];\n";
    return std::nullopt;
}
