#include "WindowStyles.h"

#include <array>
#include <string>

#include <spdlog/spdlog.h>

#include "ModInternal.h"
#include "port/ShipInit.hpp"
#include "port/hooks/Events.h"

#include "common.h"
#include "draw_box.h"

static_assert(MOD_WINDOW_STYLE_FIRST == WINDOW_STYLE_MAX + 1);
static_assert(MOD_WINDOW_STYLE_LAST == WINDOW_STYLE_REGISTERED_MAX);

namespace {

constexpr int32_t kStyleCount = MOD_WINDOW_STYLE_LAST - MOD_WINDOW_STYLE_FIRST + 1;

struct Slot {
    std::string owner;
    DefaultWindowStyle style;
};

std::array<Slot, kStyleCount>& Slots() {
    static std::array<Slot, kStyleCount> sSlots;
    return sSlots;
}

void OnWindowStyleListener(IEvent* event) {
    auto* ev = (OnWindowStyle*) event;
    const int32_t slot = ev->styleID - MOD_WINDOW_STYLE_FIRST;

    if (*ev->style != nullptr || slot < 0 || slot >= kStyleCount || Slots()[slot].owner.empty()) {
        return;
    }
    *ev->style = &Slots()[slot].style;
}

void Listen() {
    REGISTER_LISTENER(OnWindowStyle, EVENT_PRIORITY_NORMAL, OnWindowStyleListener);
}

RegisterShipInitFunc sWindowStylesInit(Listen);

} // namespace

extern "C" int32_t Mod_RegisterWindowStyles(const char* owner, const DefaultWindowStyle* styles, int32_t count) {
    const std::string name = Mod::OwnerName(owner);
    auto& slots = Slots();

    if (styles == nullptr || count <= 0 || count > kStyleCount) {
        SPDLOG_ERROR("Mod: {} registered {} window styles", name, count);
        return -1;
    }
    for (int32_t first = 0; first + count <= kStyleCount; first++) {
        bool free = true;
        for (int32_t i = 0; i < count && free; i++) {
            free = slots[first + i].owner.empty() || slots[first + i].owner == name;
        }
        if (!free) {
            continue;
        }
        for (int32_t i = 0; i < count; i++) {
            slots[first + i] = { name, styles[i] };
        }
        return MOD_WINDOW_STYLE_FIRST + first;
    }
    SPDLOG_ERROR("Mod: {} registered {} window styles, no contiguous block is free", name, count);
    return -1;
}

void Mod::UnregisterWindowStyles(const std::string& owner) {
    for (Slot& slot : Slots()) {
        if (slot.owner == owner) {
            slot.owner.clear();
        }
    }
}
