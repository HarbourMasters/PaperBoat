#pragma once

#include <stdint.h>

#ifdef __cplusplus

#include <functional>

#include <nlohmann/json.hpp>

struct ModSaveDataHandlers {
    std::function<nlohmann::json()> save;
    std::function<void(const nlohmann::json&)> load;
    std::function<void()> clear;
};

void Mod_RegisterSaveData(const char* owner, const char* key, ModSaveDataHandlers handlers);

namespace Mod {

void WriteSaveData(nlohmann::ordered_json& jsonSave);
void ReadSaveData(const nlohmann::json& jsonSave);
void ClearSaveData();

} // namespace Mod

#endif
