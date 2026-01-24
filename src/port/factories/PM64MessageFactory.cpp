#include "PM64MessageFactory.h"
#include "Companion.h"
#include "spdlog/spdlog.h"

// PM64 message data is stored as raw big-endian bytes (no byte-swapping at extraction).
//
// The blob interleaves u32 offset tables and raw byte strings in a layout that
// makes bulk pre-swapping impractical. Instead, dma_load_msg() in msg.c swaps
// the three u32 values it reads per message load at runtime.
//
// TODO: revisit — could split into separate index-table and string assets in the
// YAML so the factory can byte-swap index tables cleanly at extraction time.

std::optional<std::shared_ptr<IParsedData>> PM64MessageFactory::parse(std::vector<uint8_t>& buffer, YAML::Node& node) {
    auto offset = GetSafeNode<uint32_t>(node, "offset");
    auto size = GetSafeNode<size_t>(node, "size");

    if (offset + size > buffer.size()) {
        SPDLOG_ERROR("PM64:MESSAGE offset 0x{:X} + size 0x{:X} exceeds buffer size 0x{:X}", offset, size, buffer.size());
        return std::nullopt;
    }

    std::vector<uint8_t> msgData(buffer.begin() + offset, buffer.begin() + offset + size);

    SPDLOG_INFO("PM64:MESSAGE parsed at 0x{:X}, size: {}", offset, msgData.size());

    return std::make_shared<RawBuffer>(msgData);
}

ExportResult PM64MessageBinaryExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    auto writer = LUS::BinaryWriter();
    auto data = std::static_pointer_cast<RawBuffer>(raw)->mBuffer;

    WriteHeader(writer, Torch::ResourceType::Blob, 0);
    writer.Write(static_cast<uint32_t>(data.size()));
    writer.Write(reinterpret_cast<char*>(data.data()), data.size());
    writer.Finish(write);

    return std::nullopt;
}

ExportResult PM64MessageHeaderExporter::Export(std::ostream& write, std::shared_ptr<IParsedData> raw, std::string& entryName, YAML::Node& node, std::string* replacement) {
    const auto symbol = GetSafeNode(node, "symbol", entryName);

    if (Companion::Instance->IsOTRMode()) {
        write << "static const ALIGN_ASSET(2) char " << symbol << "[] = \"__OTR__" << (*replacement) << "\";\n\n";
        return std::nullopt;
    }

    write << "extern u8 " << symbol << "[];\n";
    return std::nullopt;
}
