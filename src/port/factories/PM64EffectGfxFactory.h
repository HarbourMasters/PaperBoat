#pragma once

#include "factories/BaseFactory.h"
#include "types/RawBuffer.h"
#include <vector>

struct PM64EffectDisplayListInfo {
    uint32_t offset;
    std::vector<uint32_t> commands;
};

class PM64EffectGfxData : public IParsedData {
public:
    std::vector<uint8_t> mBuffer;
    std::vector<PM64EffectDisplayListInfo> mDisplayLists;

    PM64EffectGfxData(std::vector<uint8_t>&& buffer, std::vector<PM64EffectDisplayListInfo>&& displayLists)
        : mBuffer(std::move(buffer)), mDisplayLists(std::move(displayLists)) {
    }
};

class PM64EffectGfxBinaryExporter : public BaseExporter {
    ExportResult Export(std::ostream& write, std::shared_ptr<IParsedData> data, std::string& entryName, YAML::Node& node, std::string* replacement) override;
};

class PM64EffectGfxHeaderExporter : public BaseExporter {
    ExportResult Export(std::ostream& write, std::shared_ptr<IParsedData> data, std::string& entryName, YAML::Node& node, std::string* replacement) override;
};

class PM64EffectGfxFactory : public BaseFactory {
public:
    std::optional<std::shared_ptr<IParsedData>> parse(std::vector<uint8_t>& buffer, YAML::Node& data) override;
    inline std::unordered_map<ExportType, std::shared_ptr<BaseExporter>> GetExporters() override {
        return {
            REGISTER(Header, PM64EffectGfxHeaderExporter)
            REGISTER(Binary, PM64EffectGfxBinaryExporter)
        };
    }
};
