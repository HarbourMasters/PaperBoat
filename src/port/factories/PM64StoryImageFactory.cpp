#include "PM64StoryImageFactory.h"
#include "Companion.h"
#include "spdlog/spdlog.h"
#include <ship/utils/binarytools/endianness.h>

// PM64 story image factory for intro sequence graphics
// Handles CI8 images with palettes and IA8 images without palettes
//
// Data layout for CI8 (has_palette=true):
//   - Image data: width * height bytes (CI8 indexed)
//   - Palette: 256 colors * 2 bytes = 512 bytes (RGBA5551)
//
// Data layout for IA8 (has_palette=false):
//   - Image data: width * height bytes (IA8)
//
// Output format: [image data][palette if CI8]
// NOTE: Palette is kept in big-endian format because libultraship's Fast3D
// interpreter reads palette data as big-endian (see interpreter.cpp line 749, 785-786)

std::optional<std::shared_ptr<IParsedData>> PM64StoryImageFactory::parse(std::vector<uint8_t>& buffer, YAML::Node& node) {
    auto offset = GetSafeNode<uint32_t>(node, "offset");
    auto width = GetSafeNode<uint32_t>(node, "width");
    auto height = GetSafeNode<uint32_t>(node, "height");
    auto hasPalette = GetSafeNode<bool>(node, "has_palette");

    size_t imageSize = width * height;  // CI8 or IA8 = 1 byte per pixel
    size_t paletteSize = hasPalette ? 512 : 0;  // 256 colors * 2 bytes
    size_t totalSize = imageSize + paletteSize;

    if (offset + totalSize > buffer.size()) {
        SPDLOG_ERROR("PM64:STORY_IMAGE: Data at offset 0x{:X} exceeds buffer size (need {} bytes, have {})",
                     offset, totalSize, buffer.size() - offset);
        return std::nullopt;
    }

    std::vector<uint8_t> result(totalSize);

    // Copy image data and palette directly (no byte swapping)
    // CI8/IA8 image data is byte-based so endianness doesn't matter
    // Palette is kept big-endian as the interpreter expects it that way
    std::memcpy(result.data(), buffer.data() + offset, totalSize);

    SPDLOG_INFO("PM64:STORY_IMAGE parsed at 0x{:X}, {}x{}, has_palette={}, size={}",
                offset, width, height, hasPalette, totalSize);

    return std::make_shared<RawBuffer>(result);
}

ExportResult PM64StoryImageBinaryExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    auto writer = LUS::BinaryWriter();
    auto data = std::static_pointer_cast<RawBuffer>(raw)->mBuffer;

    // Write as Blob type - game loads as raw binary
    WriteHeader(writer, Torch::ResourceType::Blob, 0);
    writer.Write(static_cast<uint32_t>(data.size()));
    writer.Write(reinterpret_cast<char*>(data.data()), data.size());
    writer.Finish(write);

    return std::nullopt;
}

ExportResult PM64StoryImageHeaderExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    const auto symbol = GetSafeNode(node, "symbol", entryName);

    if (Companion::Instance->IsOTRMode()) {
        write << "static const ALIGN_ASSET(2) char " << symbol << "[] = \"__OTR__" << (*replacement) << "\";\n\n";
        return std::nullopt;
    }

    write << "extern u8 " << symbol << "[];\n";
    return std::nullopt;
}
