#pragma once

#include "factories/DisplayListFactory.h"

class PM64EffectDListBinaryExporter : public BaseExporter {
    ExportResult Export(std::ostream& write, std::shared_ptr<IParsedData> data, std::string& entryName, YAML::Node& node, std::string* replacement) override;
};

class PM64EffectDListFactory : public DListFactory {
public:
    // Override parse to skip auto-discovery of sub-DL/VTX/light assets.
    // DListFactory::parse auto-discovers G_DL references and registers them as "GFX" type,
    // which overwrites YAML-defined "PM64:EFFECT_DL" entries and causes sub-DLs to be
    // exported by the standard DListBinaryExporter (with the width-subtraction bug).
    // All effect assets are already defined in the YAML, so no auto-discovery is needed.
    std::optional<std::shared_ptr<IParsedData>> parse(std::vector<uint8_t>& buffer, YAML::Node& data) override;

    std::unordered_map<ExportType, std::shared_ptr<BaseExporter>> GetExporters() override {
        return {
            REGISTER(Header, DListHeaderExporter)
            REGISTER(Binary, PM64EffectDListBinaryExporter)
        };
    }
};
