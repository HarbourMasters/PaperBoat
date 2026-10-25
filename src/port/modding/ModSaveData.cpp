#include "ModSaveData.h"

#include <algorithm>
#include <exception>
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
            try {
                entry.handlers.load((*owner)[entry.key]);
            } catch (const std::exception& e) {
                SPDLOG_ERROR(
                    "Mod: {} save data '{}' could not be loaded, clearing it: {}", entry.owner, entry.key, e.what()
                );
                entry.handlers.clear();
            }
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

void UnregisterSaveData(const std::string& owner) {
    auto& entries = Entries();
    entries.erase(
        std::remove_if(entries.begin(), entries.end(), [&](const Entry& entry) { return entry.owner == owner; }),
        entries.end()
    );
}

} // namespace Mod
