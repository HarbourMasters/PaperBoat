#include "SaveEditorLists.h"

#include <algorithm>
#include <array>

#include <spdlog/spdlog.h>

#include "ModInternal.h"
#include "port/hooks/Events.h"
#include "port/romhack/Romhack.h"

namespace {

constexpr int32_t kVanillaStarPieceCount = 160;
constexpr int32_t kMaxStarPowerBars = 7;
constexpr int32_t kMaxStarPoints = 99;
constexpr int32_t kMaxCoins = 999;

struct OwnedEntry {
    std::string owner;
    Mod::SaveEditorEntry entry;
};

struct OwnedKey {
    std::string owner;
    int32_t key;
};

struct OwnedClear {
    std::string owner;
};

struct ListEdits {
    std::vector<OwnedEntry> added;
    std::vector<OwnedKey> hidden;
    std::vector<OwnedClear> cleared;
};

std::array<ListEdits, MOD_SAVE_EDITOR_LIST_COUNT>& Lists() {
    static std::array<ListEdits, MOD_SAVE_EDITOR_LIST_COUNT> sLists;
    return sLists;
}

std::array<Mod::OwnerStack<int32_t>, MOD_SAVE_EDITOR_LIMIT_COUNT>& Limits() {
    static std::array<Mod::OwnerStack<int32_t>, MOD_SAVE_EDITOR_LIMIT_COUNT> sLimits;
    return sLimits;
}

std::vector<Mod::SaveEditorTracker>& Trackers() {
    static std::vector<Mod::SaveEditorTracker> sTrackers;
    return sTrackers;
}

std::vector<Mod::SaveEditorSection>& Sections() {
    static std::vector<Mod::SaveEditorSection> sSections;
    return sSections;
}

Mod::SaveEditorEntry CopyEntry(const ModSaveEditorEntry& entry) {
    return { entry.name != nullptr ? entry.name : "", entry.detail != nullptr ? entry.detail : "", entry.id, entry.flag,
             entry.option };
}

bool ValidList(const std::string& owner, int32_t list) {
    if (list < 0 || list >= MOD_SAVE_EDITOR_LIST_COUNT) {
        SPDLOG_ERROR("Mod: {} edited save editor list {}, out of range", owner, list);
        return false;
    }
    return true;
}

template <typename T> void RemoveOwner(std::vector<T>& entries, const std::string& owner) {
    entries.erase(
        std::remove_if(entries.begin(), entries.end(), [&](const T& e) { return e.owner == owner; }), entries.end()
    );
}

} // namespace

extern "C" void Mod_SaveEditorAdd(const char* owner, int32_t list, const ModSaveEditorEntry* entries, int32_t count) {
    const std::string name = Mod::OwnerName(owner);
    if (!ValidList(name, list) || entries == nullptr) {
        return;
    }
    auto& added = Lists()[list].added;
    for (int32_t i = 0; i < count; i++) {
        added.push_back({ name, CopyEntry(entries[i]) });
    }
}

extern "C" void Mod_SaveEditorHide(const char* owner, int32_t list, int32_t key) {
    const std::string name = Mod::OwnerName(owner);
    if (!ValidList(name, list)) {
        return;
    }
    Lists()[list].hidden.push_back({ name, key });
}

extern "C" void Mod_SaveEditorClear(const char* owner, int32_t list) {
    const std::string name = Mod::OwnerName(owner);
    if (!ValidList(name, list)) {
        return;
    }
    Lists()[list].cleared.push_back({ name });
}

extern "C" void Mod_SaveEditorSetLimit(const char* owner, int32_t limit, int32_t max) {
    const std::string name = Mod::OwnerName(owner);
    if (limit < 0 || limit >= MOD_SAVE_EDITOR_LIMIT_COUNT) {
        SPDLOG_ERROR("Mod: {} set save editor limit {}, out of range", name, limit);
        return;
    }
    if (const std::string* previous = Limits()[limit].Push(name, max)) {
        SPDLOG_WARN("Mod: {} sets save editor limit {} already set by {}", name, limit, *previous);
    }
}

extern "C" void Mod_SaveEditorAddTracker(const char* owner, const ModSaveEditorTracker* tracker) {
    const std::string name = Mod::OwnerName(owner);
    if (tracker == nullptr || tracker->title == nullptr) {
        SPDLOG_ERROR("Mod: {} added a save editor tracker without a title", name);
        return;
    }
    Mod::SaveEditorTracker copy { name, tracker->title, tracker->description != nullptr ? tracker->description : "" };
    for (int32_t i = 0; i < tracker->entryCount; i++) {
        copy.entries.push_back(CopyEntry(tracker->entries[i]));
    }
    for (int32_t i = 0; i < tracker->counterCount; i++) {
        const ModSaveEditorCounter& counter = tracker->counters[i];
        if (counter.get == nullptr || counter.set == nullptr) {
            SPDLOG_ERROR("Mod: {} tracker {} has a counter without get/set", name, copy.title);
            continue;
        }
        copy.counters.push_back(
            { counter.label != nullptr ? counter.label : "", counter.get, counter.set, counter.max }
        );
    }
    Trackers().push_back(std::move(copy));
}

extern "C" void Mod_SaveEditorAddSection(const char* owner, const char* title, void (*draw)(void)) {
    const std::string name = Mod::OwnerName(owner);
    if (title == nullptr || draw == nullptr) {
        SPDLOG_ERROR("Mod: {} added a save editor section without a title or draw", name);
        return;
    }
    Sections().push_back({ name, title, draw });
}

int32_t Mod::SaveEditorEntryKey(int32_t list, const SaveEditorEntry& entry) {
    return list == MOD_SAVE_EDITOR_STAR_PIECES ? entry.flag : entry.id;
}

std::vector<Mod::SaveEditorEntry> Mod::SaveEditorList(int32_t list, const std::vector<SaveEditorEntry>& defaults) {
    if (list < 0 || list >= MOD_SAVE_EDITOR_LIST_COUNT) {
        return defaults;
    }
    const ListEdits& edits = Lists()[list];
    auto isHidden = [&](const SaveEditorEntry& entry) {
        const int32_t key = SaveEditorEntryKey(list, entry);
        return std::any_of(edits.hidden.begin(), edits.hidden.end(), [&](const OwnedKey& h) { return h.key == key; });
    };

    auto findDefault = [&](int32_t key) {
        return std::find_if(defaults.begin(), defaults.end(), [&](const SaveEditorEntry& e) {
            return SaveEditorEntryKey(list, e) == key;
        });
    };

    std::vector<SaveEditorEntry> result;
    if (edits.cleared.empty()) {
        for (const SaveEditorEntry& entry : defaults) {
            if (!isHidden(entry)) {
                result.push_back(entry);
            }
        }
    }
    for (const OwnedEntry& added : edits.added) {
        if (isHidden(added.entry)) {
            continue;
        }
        const int32_t key = SaveEditorEntryKey(list, added.entry);
        SaveEditorEntry entry = added.entry;
        const auto original = findDefault(key);
        entry.owner = original != defaults.end() ? original->owner : added.owner;

        auto existing = std::find_if(result.begin(), result.end(), [&](const SaveEditorEntry& e) {
            return SaveEditorEntryKey(list, e) == key;
        });
        if (existing != result.end()) {
            *existing = entry;
        } else {
            result.push_back(entry);
        }
    }
    return result;
}

std::vector<Mod::SaveEditorEntry> Mod::SaveEditorRemoved(int32_t list, const std::vector<SaveEditorEntry>& defaults) {
    std::vector<SaveEditorEntry> removed;
    if (list < 0 || list >= MOD_SAVE_EDITOR_LIST_COUNT) {
        return removed;
    }
    const ListEdits& edits = Lists()[list];
    for (const SaveEditorEntry& entry : defaults) {
        const int32_t key = SaveEditorEntryKey(list, entry);
        const auto hidden =
            std::find_if(edits.hidden.begin(), edits.hidden.end(), [&](const OwnedKey& h) { return h.key == key; });
        const bool readded = std::any_of(edits.added.begin(), edits.added.end(), [&](const OwnedEntry& a) {
            return SaveEditorEntryKey(list, a.entry) == key;
        });
        SaveEditorEntry copy = entry;
        if (hidden != edits.hidden.end()) {
            copy.owner = hidden->owner;
        } else if (!edits.cleared.empty() && !readded) {
            copy.owner = edits.cleared.front().owner;
        } else {
            continue;
        }
        removed.push_back(copy);
    }
    return removed;
}

std::string Mod::SaveEditorOwnerName(const std::string& owner) {
    const char* id = Romhack_GetId();
    if (id != nullptr && owner == id) {
        return Romhack_GetModName();
    }
    return owner;
}

int32_t Mod::SaveEditorLimit(int32_t limit) {
    if (limit >= 0 && limit < MOD_SAVE_EDITOR_LIMIT_COUNT && !Limits()[limit].Empty()) {
        return Limits()[limit].Top();
    }

    StatLimits stats = STAT_LIMITS_VANILLA;
    CALL_EVENT(OnStatLimits, &stats);
    switch (limit) {
        case MOD_SAVE_EDITOR_LIMIT_LEVEL:
            return stats.levelCap;
        case MOD_SAVE_EDITOR_LIMIT_MAX_HP:
        case MOD_SAVE_EDITOR_LIMIT_MAX_FP:
            return stats.levelUpHpFpCap;
        case MOD_SAVE_EDITOR_LIMIT_MAX_BP:
            return stats.bpCap;
        case MOD_SAVE_EDITOR_LIMIT_STAR_PIECES:
            return kVanillaStarPieceCount;
        case MOD_SAVE_EDITOR_LIMIT_STAR_POWER:
            return kMaxStarPowerBars;
        case MOD_SAVE_EDITOR_LIMIT_STAR_POINTS:
            return kMaxStarPoints;
        case MOD_SAVE_EDITOR_LIMIT_COINS:
            return kMaxCoins;
        default:
            return 0;
    }
}

const std::vector<Mod::SaveEditorTracker>& Mod::SaveEditorTrackers() {
    return Trackers();
}

const std::vector<Mod::SaveEditorSection>& Mod::SaveEditorSections() {
    return Sections();
}

void Mod::UnregisterSaveEditor(const std::string& owner) {
    for (ListEdits& edits : Lists()) {
        RemoveOwner(edits.added, owner);
        RemoveOwner(edits.hidden, owner);
        RemoveOwner(edits.cleared, owner);
    }
    for (auto& limit : Limits()) {
        limit.Remove(owner);
    }
    RemoveOwner(Trackers(), owner);
    RemoveOwner(Sections(), owner);
}
