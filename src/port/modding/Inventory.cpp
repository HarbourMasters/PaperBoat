#include "Inventory.h"

#include <algorithm>

#include <spdlog/spdlog.h>

#include "ModInternal.h"

#include "common.h"

namespace {

constexpr int32_t kVanillaCapacity = 10;

Mod::OwnerStack<ModItemCapacityFn>& Providers() {
    static Mod::OwnerStack<ModItemCapacityFn> sProviders;
    return sProviders;
}

} // namespace

extern "C" void Mod_SetItemCapacity(const char* owner, ModItemCapacityFn capacity) {
    const std::string name = Mod::OwnerName(owner);
    if (capacity == nullptr) {
        Providers().Remove(name);
        return;
    }
    if (const std::string* previous = Providers().Push(name, capacity)) {
        SPDLOG_WARN("Mod: {} sets the item capacity already set by {}", name, *previous);
    }
}

extern "C" s32 get_consumables_capacity(void) {
    const int32_t capacity = Providers().Empty() ? kVanillaCapacity : Providers().Top()();
    return std::clamp<int32_t>(capacity, 1, ARRAY_COUNT(gPlayerData.invItems));
}

void Mod::UnregisterItemCapacity(const std::string& owner) {
    Providers().Remove(owner);
}
