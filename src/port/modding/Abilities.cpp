#include "Abilities.h"

#include <string>
#include <vector>

#include <spdlog/spdlog.h>

#include "ModInternal.h"
#include "port/hooks/Events.h"

#include "common.h"

namespace {

struct Ability {
    std::string owner;
    int32_t moveID;
    int32_t holder;
};

std::vector<Ability>& RegisteredAbilities() {
    static std::vector<Ability> sAbilities;
    return sAbilities;
}

int32_t CountEquippedMove(int32_t moveID) {
    int32_t count = 0;
    for (int32_t i = 0; i < ARRAY_COUNT(gPlayerData.equippedBadges); i++) {
        const int32_t itemID = gPlayerData.equippedBadges[i];
        if (itemID == ITEM_NONE || !(gItemTable[itemID].typeFlags & ITEM_TYPE_FLAG_BADGE)) {
            continue;
        }
        if (gItemTable[itemID].moveID == moveID) {
            count++;
        }
    }
    return count;
}

void OnAbilityCountListener(IEvent* event) {
    OnAbilityCount* ev = (OnAbilityCount*) event;
    const int32_t index = ev->ability - MOD_ABILITY_BASE;
    auto& abilities = RegisteredAbilities();

    if (index < 0 || index >= (int32_t) abilities.size() || abilities[index].owner.empty()) {
        return;
    }
    if (gGameStatusPtr->peachFlags & PEACH_FLAG_IS_PEACH) {
        return;
    }
    const Ability& ability = abilities[index];
    const int32_t actorClass = ev->actor != nullptr ? ev->actor->actorID & ACTOR_CLASS_MASK : ACTOR_CLASS_PLAYER;
    const int32_t holderClass = ability.holder == MOD_ABILITY_HOLDER_PARTNER ? ACTOR_CLASS_PARTNER : ACTOR_CLASS_PLAYER;
    if (actorClass == holderClass) {
        *ev->count = CountEquippedMove(ability.moveID);
    }
}

} // namespace

extern "C" int32_t Mod_RegisterAbility(const char* owner, int32_t moveID, int32_t holder) {
    static bool sListening = false;
    const std::string name = Mod::OwnerName(owner);
    auto& abilities = RegisteredAbilities();
    int32_t freeIndex = -1;

    if (moveID <= MOVE_NONE || moveID >= NUM_MOVES) {
        SPDLOG_ERROR("Mod: {} registered an ability for move {}, out of range", name, moveID);
        return -1;
    }
    if (holder != MOD_ABILITY_HOLDER_PLAYER && holder != MOD_ABILITY_HOLDER_PARTNER) {
        SPDLOG_ERROR("Mod: {} registered an ability with holder {}", name, holder);
        return -1;
    }
    if (!sListening) {
        sListening = true;
        REGISTER_LISTENER(OnAbilityCount, EVENT_PRIORITY_LOW, OnAbilityCountListener);
    }
    for (size_t i = 0; i < abilities.size(); i++) {
        const Ability& ability = abilities[i];
        if (ability.owner == name && ability.moveID == moveID && ability.holder == holder) {
            return MOD_ABILITY_BASE + (int32_t) i;
        }
        if (ability.owner.empty() && freeIndex < 0) {
            freeIndex = (int32_t) i;
        }
    }
    if (freeIndex < 0) {
        abilities.push_back({ name, moveID, holder });
        return MOD_ABILITY_BASE + (int32_t) abilities.size() - 1;
    }
    abilities[freeIndex] = { name, moveID, holder };
    return MOD_ABILITY_BASE + freeIndex;
}

extern "C" int32_t Mod_GetBadgeBPCost(int32_t itemID) {
    int32_t cost = gMoveTable[gItemTable[itemID].moveID].costBP;
    CALL_EVENT(OnBadgeBPCost, itemID, &cost);
    return cost;
}

void Mod::UnregisterAbilities(const std::string& owner) {
    for (Ability& ability : RegisteredAbilities()) {
        if (ability.owner == owner) {
            ability = { "", MOVE_NONE, MOD_ABILITY_HOLDER_PLAYER };
        }
    }
}
