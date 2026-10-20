#include "port/save/SaveMods.h"

#include "port/api/ItemTables.hpp"
#include "port/api/WorldTables.hpp"
#include "port/api/item.h"
#include "port/ui/Notification.h"

#include "common.h"

extern "C" {
#include "dx/versioning.h"
}

#include <spdlog/spdlog.h>

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using nlohmann::json;
using nlohmann::ordered_json;

namespace {

json sData = json::object();
// Mod that registered each mod item of the current file, by id.
std::map<std::string, std::string> sItemMods;
// Mod map the current file was saved in when it isn't loaded.
std::string sMissingMap;

// Every item number a file keeps: the inventory, stored items, key items and badges.
template <typename F> void ForEachItem(PlayerData* player, F&& visit) {
    for (s16& item : player->keyItems) {
        visit(item);
    }
    for (s16& item : player->badges) {
        visit(item);
    }
    for (s16& item : player->invItems) {
        visit(item);
    }
    for (s16& item : player->storedItems) {
        visit(item);
    }
    for (s16& item : player->equippedBadges) {
        visit(item);
    }
}

const json* Find(const json& object, const char* key) {
    if (!object.is_object()) {
        return nullptr;
    }
    auto it = object.find(key);
    return it != object.end() ? &*it : nullptr;
}

} // namespace

void SaveMods::Load(const json& file, SaveData* save) {
    PlayerData* player = &save->player;
    const json* mods = Find(file, "mods");
    const json* data = mods != nullptr ? Find(*mods, "data") : nullptr;
    const json* ids = mods != nullptr ? Find(*mods, "ids") : nullptr;
    const json* items = ids != nullptr ? Find(*ids, "items") : nullptr;

    sData = data != nullptr && data->is_object() ? *data : json::object();
    sItemMods.clear();
    sMissingMap.clear();

    const json* map = mods != nullptr ? Find(*mods, "map") : nullptr;
    const bool knownArea = save->areaID >= 0 && save->areaID < ARRAY_COUNT(gAreas) && gAreas[save->areaID].maps;
    s16 areaID = -1;
    s16 mapID = -1;
    if (map != nullptr && map->is_string()
        && get_map_IDs_by_name(map->get_ref<const std::string&>().c_str(), &areaID, &mapID))
    {
        save->areaID = areaID;
        save->mapID = mapID;
    } else if (map != nullptr || !knownArea || save->mapID >= gAreas[save->areaID].mapCount) {
        sMissingMap = map != nullptr && map->is_string() ? map->get<std::string>() : "an unknown map";
        SPDLOG_WARN(
            "save: the file was saved in {}, which isn't loaded; it continues from the area's first map", sMissingMap
        );
        if (!knownArea) {
            save->areaID = 0;
        }
        save->mapID = 0;
        save->entryID = 0;
    }

    std::unordered_map<int, int> numbers;
    if (items != nullptr && items->is_object()) {
        for (const auto& [id, entry] : items->items()) {
            const int saved = entry.is_object() ? entry.value("number", -1) : -1;
            if (saved < C_ITEM_FIRST || saved > C_ITEM_LAST) {
                continue;
            }
            const std::string mod = entry.value("mod", std::string());
            const int number = ItemTables::Number(id, saved, mod);
            if (number < 0) {
                SPDLOG_ERROR("save: no item number left for {}, it is dropped", id);
            }
            numbers[saved] = number < 0 ? ITEM_NONE : number;
            sItemMods[id] = mod;
        }
    }

    int renumbered = 0;
    int dropped = 0;
    ForEachItem(player, [&](s16& item) {
        if (item < C_ITEM_FIRST) {
            return;
        }
        auto it = numbers.find(item);
        if (it == numbers.end()) {
            item = ITEM_NONE;
            dropped++;
        } else if (it->second != item) {
            item = (s16) it->second;
            renumbered++;
        }
    });
    if (renumbered > 0) {
        SPDLOG_INFO("save: renumbered {} mod items to the numbers of this session", renumbered);
    }
    if (dropped > 0) {
        SPDLOG_WARN("save: dropped {} items the file doesn't name", dropped);
    }
}

void SaveMods::Reset() {
    sData = json::object();
    sItemMods.clear();
    sMissingMap.clear();
}

void SaveMods::Store(ordered_json& file, const SaveData* save) {
    ordered_json items = ordered_json::object();
    ForEachItem(const_cast<PlayerData*>(&save->player), [&](s16& item) {
        if (item < C_ITEM_FIRST) {
            return;
        }
        if (const std::string* id = ItemTables::IdOf(item)) {
            items[*id] = { { "number", item }, { "mod", ItemTables::Owner(*id) } };
        }
    });

    ordered_json mods = ordered_json::object();
    if (!items.empty()) {
        mods["ids"]["items"] = std::move(items);
    }
    if (WorldTables::IsModMap(save->areaID, save->mapID)) {
        mods["map"] = gAreas[save->areaID].maps[save->mapID].id;
    }
    if (!sData.empty()) {
        mods["data"] = ordered_json::parse(sData.dump());
    }
    if (!mods.empty()) {
        file["mods"] = std::move(mods);
    }
}

void SaveMods::CheckMissing() {
    std::map<std::string, std::vector<std::string>> missing;
    for (const auto& [id, mod] : sItemMods) {
        const int number = ItemTables::Number(id, -1, mod);
        if (number < 0 || !ItemTables::IsRegistered(number)) {
            missing[mod].push_back(id);
        }
    }
    if (!sMissingMap.empty()) {
        missing[""].push_back(sMissingMap);
    }
    if (missing.empty()) {
        return;
    }

    std::string mods;
    for (const auto& [mod, ids] : missing) {
        std::string list;
        for (const std::string& id : ids) {
            list += (list.empty() ? "" : ", ") + id;
        }
        const std::string name = mod.empty() ? "unknown mods" : mod;
        SPDLOG_WARN("save: this file has items from {} that no loaded mod registers: {}", name, list);
        mods += (mods.empty() ? "" : ", ") + name;
    }
    Notification::Emit(
        { .prefix = "Missing mods:",
          .message = mods,
          .messageColor = ImVec4(1.0f, 0.5f, 0.5f, 1.0f),
          .suffix = "Their items show as nothing and their maps are skipped until they are back.",
          .suffixColor = ImVec4(0.7f, 0.7f, 0.7f, 1.0f),
          .remainingTime = 12.0f }
    );
}

json& SaveMods::Data() {
    return sData;
}
