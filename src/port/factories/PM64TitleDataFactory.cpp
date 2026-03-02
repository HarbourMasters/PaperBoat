#include "PM64TitleDataFactory.h"
#include "Companion.h"
#include "utils/Decompressor.h"
#include "spdlog/spdlog.h"

// PM64 title data factory
// Decompresses the Yay0-compressed "title_data" blob and extracts a sub-image
// at the specified sub_offset with the specified size.
//
// Sub-images are byte-addressed (IA8 = 1 byte/pixel, RGBA32 = 4 bytes/pixel)
// so no byte-swapping is needed.

std::optional<std::shared_ptr<IParsedData>> PM64TitleDataFactory::parse(std::vector<uint8_t>& buffer, YAML::Node& node) {
    auto offset = GetSafeNode<uint32_t>(node, "offset");
    auto subOffset = GetSafeNode<uint32_t>(node, "sub_offset");
    auto size = GetSafeNode<uint32_t>(node, "size");

    // Decompress Yay0
    auto decoded = Decompressor::Decode(buffer, offset, CompressionType::YAY0);
    if (!decoded || decoded->size == 0) {
        SPDLOG_ERROR("PM64:TITLE_DATA: Failed to decompress YAY0 at offset 0x{:X}", offset);
        return std::nullopt;
    }

    if (subOffset + size > decoded->size) {
        SPDLOG_ERROR("PM64:TITLE_DATA: Sub-image at 0x{:X} + {} exceeds decompressed size {}",
                     subOffset, size, decoded->size);
        return std::nullopt;
    }

    // Extract the sub-image (no byte-swap needed for IA8/RGBA32)
    std::vector<uint8_t> result(size);
    std::memcpy(result.data(), decoded->data + subOffset, size);

    return std::make_shared<RawBuffer>(result);
}

ExportResult PM64TitleDataBinaryExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    auto writer = LUS::BinaryWriter();
    auto data = std::static_pointer_cast<RawBuffer>(raw)->mBuffer;

    WriteHeader(writer, Torch::ResourceType::Blob, 0);
    writer.Write(static_cast<uint32_t>(data.size()));
    writer.Write(reinterpret_cast<char*>(data.data()), data.size());
    writer.Finish(write);

    return std::nullopt;
}

ExportResult PM64TitleDataHeaderExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    const auto symbol = GetSafeNode(node, "symbol", entryName);

    if (Companion::Instance->IsOTRMode()) {
        write << "static const ALIGN_ASSET(2) char " << symbol << "[] = \"__OTR__" << (*replacement) << "\";\n\n";
        return std::nullopt;
    }

    write << "extern u8 " << symbol << "[];\n";
    return std::nullopt;
}
