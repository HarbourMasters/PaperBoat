#pragma once

#include "factories/BaseFactory.h"
#include "types/RawBuffer.h"
#include <vector>

struct PM64EntityDisplayListInfo {
    uint32_t offset;
    std::vector<uint32_t> commands;
};

class PM64EntityGfxData : public IParsedData {
public:
    std::vector<uint8_t> mBuffer;
    std::vector<PM64EntityDisplayListInfo> mDisplayLists;
    std::vector<uint32_t> mStandaloneMtx;  // Mtx offsets not reachable by DL walking

    PM64EntityGfxData(std::vector<uint8_t>&& buffer, std::vector<PM64EntityDisplayListInfo>&& displayLists)
        : mBuffer(std::move(buffer)), mDisplayLists(std::move(displayLists)) {
    }
};

class PM64EntityGfxBinaryExporter : public BaseExporter {
    ExportResult Export(std::ostream& write, std::shared_ptr<IParsedData> data, std::string& entryName, YAML::Node& node, std::string* replacement) override;
};

class PM64EntityGfxHeaderExporter : public BaseExporter {
    ExportResult Export(std::ostream& write, std::shared_ptr<IParsedData> data, std::string& entryName, YAML::Node& node, std::string* replacement) override;
};

class PM64EntityGfxFactory : public BaseFactory {
public:
    std::optional<std::shared_ptr<IParsedData>> parse(std::vector<uint8_t>& buffer, YAML::Node& data) override;
    inline std::unordered_map<ExportType, std::shared_ptr<BaseExporter>> GetExporters() override {
        return {
            REGISTER(Header, PM64EntityGfxHeaderExporter)
            REGISTER(Binary, PM64EntityGfxBinaryExporter)
        };
    }
};
