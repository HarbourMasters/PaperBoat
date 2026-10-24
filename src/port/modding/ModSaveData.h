#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct SaveData;

#define MOD_N64_SAVE_SIZE 0x1380

typedef void (*ModSaveImportFn)(struct SaveData* save, const uint8_t* n64Save);

void Mod_RegisterSaveImport(const char* owner, ModSaveImportFn fixup);

#ifdef __cplusplus
}
#endif

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
bool HasSaveImports();
void RunSaveImports(SaveData* save, const uint8_t* n64Save);

} // namespace Mod

#endif
