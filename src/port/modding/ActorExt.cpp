#include "ActorExt.h"

#include <algorithm>
#include <string>
#include <vector>

#include <spdlog/spdlog.h>

#include "ModInternal.h"
#include "port/hooks/Events.h"

#include "common.h"

namespace {

constexpr int32_t kActorSlots = 2 + 24;
constexpr int32_t kPartnerSlots = 12;

struct Store {
    std::string owner;
    int32_t size;
    std::vector<uint8_t> actors;
    std::vector<uint8_t> partners;
};

std::vector<Store>& Stores() {
    static std::vector<Store> sStores;
    return sStores;
}

int32_t ActorSlot(int32_t actorID) {
    switch (actorID & ACTOR_CLASS_MASK) {
        case ACTOR_CLASS_PLAYER:
            return actorID == ACTOR_PLAYER ? 0 : -1;
        case ACTOR_CLASS_PARTNER:
            return actorID == ACTOR_PARTNER ? 1 : -1;
        case ACTOR_CLASS_ENEMY: {
            const int32_t index = actorID & 0xFF;
            return index < kActorSlots - 2 ? 2 + index : -1;
        }
    }
    return -1;
}

void ClearActorSlot(int32_t slot) {
    for (Store& store : Stores()) {
        std::fill_n(store.actors.begin() + slot * store.size, store.size, 0);
    }
}

void Listen() {
    static bool sListening = false;
    if (sListening) {
        return;
    }
    sListening = true;
    REGISTER_LISTENER(OnBattleInit, EVENT_PRIORITY_LOW, [](IEvent* event) {
        if (((OnBattleInit*) event)->stage != BATTLE_INIT_BEGIN) {
            return;
        }
        for (Store& store : Stores()) {
            std::fill(store.actors.begin(), store.actors.end(), 0);
            std::fill(store.partners.begin(), store.partners.end(), 0);
        }
    });
    REGISTER_LISTENER(OnActorCreated, EVENT_PRIORITY_LOW, [](IEvent* event) {
        const int32_t slot = ActorSlot(((OnActorCreated*) event)->actor->actorID);
        if (slot >= 0) {
            ClearActorSlot(slot);
        }
    });
}

} // namespace

extern "C" int32_t Mod_RegisterActorExt(const char* owner, int32_t size) {
    const std::string name = Mod::OwnerName(owner);
    if (size <= 0) {
        SPDLOG_ERROR("Mod: {} registered an empty actor extension", name);
        return -1;
    }
    Listen();
    auto& stores = Stores();
    for (size_t i = 0; i < stores.size(); i++) {
        if (stores[i].owner == name) {
            stores[i] = { name, size, std::vector<uint8_t>(kActorSlots * size),
                          std::vector<uint8_t>(kPartnerSlots * size) };
            return (int32_t) i;
        }
    }
    stores.push_back(
        { name, size, std::vector<uint8_t>(kActorSlots * size), std::vector<uint8_t>(kPartnerSlots * size) }
    );
    return (int32_t) stores.size() - 1;
}

extern "C" void* Mod_ActorExt(int32_t handle, int32_t actorID) {
    auto& stores = Stores();
    if (handle < 0 || handle >= (int32_t) stores.size() || stores[handle].size == 0) {
        return nullptr;
    }
    const int32_t slot = ActorSlot(actorID);
    if (slot < 0) {
        return nullptr;
    }
    Store& store = stores[handle];
    return store.actors.data() + slot * store.size;
}

extern "C" void* Mod_PartnerExt(int32_t handle, int32_t partnerID) {
    auto& stores = Stores();
    if (handle < 0 || handle >= (int32_t) stores.size() || stores[handle].size == 0) {
        return nullptr;
    }
    if (partnerID <= PARTNER_NONE || partnerID >= kPartnerSlots) {
        return nullptr;
    }
    Store& store = stores[handle];
    return store.partners.data() + partnerID * store.size;
}

namespace Mod {

void UnregisterActorExt(const std::string& owner) {
    for (Store& store : Stores()) {
        if (store.owner == owner) {
            store = { owner, 0, {}, {} };
        }
    }
}

} // namespace Mod
