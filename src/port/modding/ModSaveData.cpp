#include "ModSaveData.h"

#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <spdlog/spdlog.h>

#include "ModInternal.h"

namespace {

constexpr const char* kModDataKey = "modData";

struct Entry {
    std::string owner;
    std::string key;
    ModSaveDataHandlers handlers;
};

std::vector<Entry>& Entries() {
    static std::vector<Entry> sEntries;
    return sEntries;
}

struct ImportEntry {
    std::string owner;
    ModSaveImportFn fixup;
};

std::vector<ImportEntry>& ImportEntries() {
    static std::vector<ImportEntry> sImports;
    return sImports;
}

nlohmann::json& UnclaimedData() {
    static nlohmann::json sUnclaimed = nlohmann::json::object();
    return sUnclaimed;
}

} // namespace

void Mod_RegisterSaveData(const char* owner, const char* key, ModSaveDataHandlers handlers) {
    const std::string name = Mod::OwnerName(owner);
    if (key == nullptr || key[0] == '\0' || !handlers.save || !handlers.load || !handlers.clear) {
        SPDLOG_ERROR("Mod: {} registered incomplete save data", name);
        return;
    }
    auto& entries = Entries();
    for (Entry& entry : entries) {
        if (entry.owner == name && entry.key == key) {
            entry.handlers = std::move(handlers);
            return;
        }
    }
    entries.push_back({ name, key, std::move(handlers) });
    entries.back().handlers.clear();
}

extern "C" void Mod_RegisterSaveImport(const char* owner, ModSaveImportFn fixup) {
    const std::string name = Mod::OwnerName(owner);
    auto& imports = ImportEntries();
    imports.erase(
        std::remove_if(imports.begin(), imports.end(), [&](const ImportEntry& entry) { return entry.owner == name; }),
        imports.end()
    );
    if (fixup != nullptr) {
        imports.push_back({ name, fixup });
    }
}

namespace Mod {

void WriteSaveData(nlohmann::ordered_json& jsonSave) {
    nlohmann::ordered_json modData = nlohmann::ordered_json::object();
    for (const auto& [owner, values] : UnclaimedData().items()) {
        modData[owner] = values;
    }
    for (const Entry& entry : Entries()) {
        modData[entry.owner][entry.key] = entry.handlers.save();
    }
    if (!modData.empty()) {
        jsonSave[kModDataKey] = modData;
    }
}

void ReadSaveData(const nlohmann::json& jsonSave) {
    nlohmann::json modData = nlohmann::json::object();
    const auto found = jsonSave.find(kModDataKey);
    if (found != jsonSave.end() && found->is_object()) {
        modData = *found;
    }
    for (const Entry& entry : Entries()) {
        const auto owner = modData.find(entry.owner);
        if (owner != modData.end() && owner->is_object() && owner->contains(entry.key)) {
            entry.handlers.load((*owner)[entry.key]);
            owner->erase(entry.key);
            if (owner->empty()) {
                modData.erase(owner);
            }
        } else {
            entry.handlers.clear();
        }
    }
    UnclaimedData() = modData;
}

void ClearSaveData() {
    for (const Entry& entry : Entries()) {
        entry.handlers.clear();
    }
    UnclaimedData() = nlohmann::json::object();
}

bool HasSaveImports() {
    return !ImportEntries().empty();
}

void RunSaveImports(SaveData* save, const uint8_t* n64Save) {
    for (const ImportEntry& entry : ImportEntries()) {
        entry.fixup(save, n64Save);
    }
}

void UnregisterSaveImports(const std::string& owner) {
    Mod_RegisterSaveImport(owner.c_str(), nullptr);
}

void UnregisterSaveData(const std::string& owner) {
    auto& entries = Entries();
    entries.erase(
        std::remove_if(entries.begin(), entries.end(), [&](const Entry& entry) { return entry.owner == owner; }),
        entries.end()
    );
}

} // namespace Mod
