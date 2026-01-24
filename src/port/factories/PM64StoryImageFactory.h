#pragma once

#include "factories/BaseFactory.h"
#include "types/RawBuffer.h"

class PM64StoryImageBinaryExporter : public BaseExporter {
    ExportResult Export(std::ostream& write, std::shared_ptr<IParsedData> data, std::string& entryName, YAML::Node& node, std::string* replacement) override;
};

class PM64StoryImageHeaderExporter : public BaseExporter {
    ExportResult Export(std::ostream& write, std::shared_ptr<IParsedData> data, std::string& entryName, YAML::Node& node, std::string* replacement) override;
};

class PM64StoryImageFactory : public BaseFactory {
public:
    std::optional<std::shared_ptr<IParsedData>> parse(std::vector<uint8_t>& buffer, YAML::Node& data) override;
    inline std::unordered_map<ExportType, std::shared_ptr<BaseExporter>> GetExporters() override {
        return {
            REGISTER(Header, PM64StoryImageHeaderExporter)
            REGISTER(Binary, PM64StoryImageBinaryExporter)
        };
    }
};
