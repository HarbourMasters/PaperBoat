#include "BattleOverrides.h"

#include <iterator>
#include <unordered_map>

#include <spdlog/spdlog.h>

#include "ModInternal.h"
#include "port/hooks/Events.h"

extern "C" {
#include "common.h"
#include "battle/battle.h"
}

template <typename T> struct FieldOverride {
    bool saved = false;
    T original {};
    Mod::OwnerStack<T> stack;
};

struct AreaOverrides {
    FieldOverride<BattleList*> battles;
    FieldOverride<StageList*> stages;
    FieldOverride<DmaTable*> dmaTable;
};

static std::unordered_map<int32_t, AreaOverrides>& BattleAreaOverrides() {
    static std::unordered_map<int32_t, AreaOverrides> sOverrides;
    return sOverrides;
}

static bool ValidBattleArea(int32_t area) {
    if (area < 0 || area >= ARRAY_COUNT(gBattleAreas)) {
        SPDLOG_ERROR("Mod: battle area {} is out of range", area);
        return false;
    }
    return true;
}

template <typename T>
static void SetAreaField(
    const char* owner,
    int32_t area,
    const char* kind,
    FieldOverride<T> AreaOverrides::* slot,
    T BattleArea::* field,
    T value
) {
    if (!ValidBattleArea(area)) {
        return;
    }
    const std::string name = Mod::OwnerName(owner);
    FieldOverride<T>& slotOverride = BattleAreaOverrides()[area].*slot;
    if (!slotOverride.saved) {
        slotOverride.original = gBattleAreas[area].*field;
        slotOverride.saved = true;
    }
    if (const std::string* previous = slotOverride.stack.Push(name, value)) {
        SPDLOG_WARN("Mod: {} replaces the {} of battle area {} set by {}", name, kind, area, *previous);
    }
    gBattleAreas[area].*field = value;
}

template <typename T>
static void
RestoreAreaField(const std::string& owner, int32_t area, FieldOverride<T>& slotOverride, T BattleArea::* field) {
    if (!slotOverride.saved || !slotOverride.stack.Remove(owner)) {
        return;
    }
    gBattleAreas[area].*field = slotOverride.stack.Empty() ? slotOverride.original : slotOverride.stack.Top();
}

extern "C" void Mod_SetBattleList(const char* owner, int32_t area, Battle* battles) {
    SetAreaField<BattleList*>(
        owner, area, "battle list", &AreaOverrides::battles, &BattleArea::battles, (BattleList*) battles
    );
}

extern "C" void Mod_SetStageList(const char* owner, int32_t area, StageListRow* stages) {
    SetAreaField<StageList*>(
        owner, area, "stage list", &AreaOverrides::stages, &BattleArea::stages, (StageList*) stages
    );
}

extern "C" void Mod_SetBattleDmaTable(const char* owner, int32_t area, DmaTable* table) {
    SetAreaField<DmaTable*>(owner, area, "dma table", &AreaOverrides::dmaTable, &BattleArea::dmaTable, table);
}

static std::unordered_map<const ActorBlueprint*, Mod::OwnerStack<ActorBlueprint*>>& BlueprintReplacements() {
    static std::unordered_map<const ActorBlueprint*, Mod::OwnerStack<ActorBlueprint*>> sReplacements;
    return sReplacements;
}

void Mod::ListenBattleOverrides() {
    REGISTER_LISTENER(OnActorBlueprintLoad, EVENT_PRIORITY_LOW, [](IEvent* event) {
        OnActorBlueprintLoad* ev = (OnActorBlueprintLoad*) event;
        auto& map = BlueprintReplacements();
        auto it = map.find(*ev->blueprint);
        if (it != map.end()) {
            *ev->blueprint = it->second.Top();
        }
    });
}

extern "C" void
Mod_ReplaceActorBlueprint(const char* owner, const ActorBlueprint* original, ActorBlueprint* replacement) {
    if (original == nullptr || replacement == nullptr || original == replacement) {
        return;
    }
    const std::string name = Mod::OwnerName(owner);
    if (const std::string* previous = BlueprintReplacements()[original].Push(name, replacement)) {
        SPDLOG_WARN(
            "Mod: {} replaces actor blueprint {} already replaced by {}", name, (const void*) original, *previous
        );
    }
}

void Mod::UnregisterBattleOverrides(const std::string& owner) {
    for (auto& [area, overrides] : BattleAreaOverrides()) {
        RestoreAreaField(owner, area, overrides.battles, &BattleArea::battles);
        RestoreAreaField(owner, area, overrides.stages, &BattleArea::stages);
        RestoreAreaField(owner, area, overrides.dmaTable, &BattleArea::dmaTable);
    }
    auto& blueprints = BlueprintReplacements();
    for (auto it = blueprints.begin(); it != blueprints.end();) {
        it->second.Remove(owner);
        it = it->second.Empty() ? blueprints.erase(it) : std::next(it);
    }
}
