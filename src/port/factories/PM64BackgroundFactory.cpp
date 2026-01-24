#include "PM64BackgroundFactory.h"
#include "Companion.h"
#include "utils/Decompressor.h"
#include "spdlog/spdlog.h"
#include <ship/utils/binarytools/endianness.h>

// PM64 background file structure (N64 ROM format):
// BackgroundHeader (0x10 bytes):
//   0x00: rasterAddr (u32) - N64 VRAM address (e.g., 0x80200210) - NOT a file offset!
//   0x04: paletteAddr (u32) - N64 VRAM address (e.g., 0x80200010) - NOT a file offset!
//   0x08: startX (u16)
//   0x0A: startY (u16)
//   0x0C: width (u16)
//   0x0E: height (u16)
//
// The decompressed data has a FIXED layout:
//   0x0000: Header (16 bytes)
//   0x0010: Palette (256 colors * 2 bytes = 512 bytes, RGBA16)
//   0x0210: Raster (width * height bytes, CI8 indexed)
//
// The N64 VRAM addresses in the header are meaningless on PC - we use fixed offsets.

static void ByteSwapBackgroundData(uint8_t* data, size_t size) {
    if (size < 0x10) {
        SPDLOG_WARN("Background data too small: {}", size);
        return;
    }

    uint32_t* header32 = reinterpret_cast<uint32_t*>(data);
    uint16_t* header16 = reinterpret_cast<uint16_t*>(data);

    // Swap 16-bit dimension fields first (we need these for validation)
    header16[4] = BSWAP16(header16[4]);  // startX at offset 0x08
    header16[5] = BSWAP16(header16[5]);  // startY at offset 0x0A
    header16[6] = BSWAP16(header16[6]);  // width at offset 0x0C
    header16[7] = BSWAP16(header16[7]);  // height at offset 0x0E

    // The N64 header contains absolute VRAM addresses (0x802xxxxx) that cannot be
    // converted to file offsets. The background data has a fixed layout:
    //   - Palette at offset 0x10 (right after 16-byte header)
    //   - Raster at offset 0x210 (after header + 512-byte palette)
    // We ignore the N64 addresses and write the correct fixed offsets.
    constexpr uint32_t paletteOffset = 0x10;   // Right after 16-byte header
    constexpr uint32_t rasterOffset = 0x210;   // After header (16) + palette (512)

    header32[0] = rasterOffset;
    header32[1] = paletteOffset;

    SPDLOG_INFO("Background header: using fixed offsets rasterOffset=0x{:X}, paletteOffset=0x{:X}, startX={}, startY={}, width={}, height={}",
                rasterOffset, paletteOffset,
                header16[4], header16[5], header16[6], header16[7]);

    // Background palettes are swapped internally by libultraship, no need to swap them here
    // Also, Raster data is CI8 (byte indices) - no swap needed
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
