#pragma once

#include "factories/BaseFactory.h"
#include "types/RawBuffer.h"
#include <vector>

// Display list info collected during parsing
struct PM64DisplayListInfo {
    uint32_t offset;           // Offset in shape file
    std::vector<uint32_t> commands;  // N64 display list commands (pairs of w0, w1)
};

// Custom parsed data that holds both shape buffer and display list info
class PM64ShapeData : public IParsedData {
public:
    std::vector<uint8_t> mBuffer;
    std::vector<PM64DisplayListInfo> mDisplayLists;
    uint32_t mVertexTableOffset;  // Offset of vertex table in shape blob
    uint32_t mVertexDataSize;     // Size of vertex data in bytes

    PM64ShapeData(std::vector<uint8_t>&& buffer, std::vector<PM64DisplayListInfo>&& displayLists,
                  uint32_t vtxTableOffset, uint32_t vtxDataSize)
        : mBuffer(std::move(buffer)), mDisplayLists(std::move(displayLists)),
          mVertexTableOffset(vtxTableOffset), mVertexDataSize(vtxDataSize) {
    }
};

class PM64ShapeBinaryExporter : public BaseExporter {
    ExportResult Export(std::ostream& write, std::shared_ptr<IParsedData> data, std::string& entryName, YAML::Node& node, std::string* replacement) override;
};

class PM64ShapeHeaderExporter : public BaseExporter {
    ExportResult Export(std::ostream& write, std::shared_ptr<IParsedData> data, std::string& entryName, YAML::Node& node, std::string* replacement) override;
};

class PM64ShapeFactory : public BaseFactory {
public:
    std::optional<std::shared_ptr<IParsedData>> parse(std::vector<uint8_t>& buffer, YAML::Node& data) override;
    inline std::unordered_map<ExportType, std::shared_ptr<BaseExporter>> GetExporters() override {
        return {
            REGISTER(Header, PM64ShapeHeaderExporter)
            REGISTER(Binary, PM64ShapeBinaryExporter)
        };
    }
};
