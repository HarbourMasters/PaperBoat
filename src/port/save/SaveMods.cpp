#include "port/save/SaveMods.h"

#include "port/api/ItemTables.hpp"
#include "port/api/item.h"
#include "port/ui/Notification.h"

#include "common.h"

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

void SaveMods::Load(const json& file, PlayerData* player) {
    const json* mods = Find(file, "mods");
    const json* data = mods != nullptr ? Find(*mods, "data") : nullptr;
    const json* ids = mods != nullptr ? Find(*mods, "ids") : nullptr;
    const json* items = ids != nullptr ? Find(*ids, "items") : nullptr;

    sData = data != nullptr && data->is_object() ? *data : json::object();
    sItemMods.clear();

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
}

void SaveMods::Store(ordered_json& file, const PlayerData* player) {
    ordered_json items = ordered_json::object();
    ForEachItem(const_cast<PlayerData*>(player), [&](s16& item) {
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
          .suffix = "Their items show as nothing until they are installed again.",
          .suffixColor = ImVec4(0.7f, 0.7f, 0.7f, 1.0f),
          .remainingTime = 12.0f }
    );
}

json& SaveMods::Data() {
    return sData;
}
