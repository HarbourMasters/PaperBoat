#include "Items.h"

#include <iterator>
#include <map>
#include <string>

#include <spdlog/spdlog.h>

#include "ModInternal.h"
#include "port/hooks/Events.h"

#include "common.h"
#include "hud_element.h"

extern "C" {
extern IconHudScriptPair gItemHudScripts[];
extern intptr_t* gItemEntityScripts[];
extern intptr_t gItemIconRasterOffsets[];
extern intptr_t gItemIconPaletteOffsets[];
}

namespace {

struct ItemIcon {
    HudScript* enabled;
    HudScript* disabled;
    intptr_t* entityScript;
    intptr_t raster;
    intptr_t palette;
};

struct ItemSlot {
    bool saved = false;
    ItemData data {};
    intptr_t* entityScript = nullptr;
    intptr_t raster = 0;
    intptr_t palette = 0;
    Mod::OwnerStack<ItemData> dataStack;
    Mod::OwnerStack<ItemIcon> iconStack;
};

std::map<int32_t, ItemSlot>& ItemSlots() {
    static std::map<int32_t, ItemSlot> sSlots;
    return sSlots;
}

std::map<int32_t, IconHudScriptPair>& HudOriginals() {
    static std::map<int32_t, IconHudScriptPair> sOriginals;
    return sOriginals;
}

bool ValidItem(int32_t itemID) {
    if (itemID <= 0 || itemID >= ITEM_TABLE_CAPACITY) {
        SPDLOG_ERROR("Mod: item {} is out of range", itemID);
        return false;
    }
    return true;
}

void ApplyItems() {
    auto& slots = ItemSlots();
    auto& hudOriginals = HudOriginals();

    for (const auto& [index, pair] : hudOriginals) {
        gItemHudScripts[index] = pair;
    }
    hudOriginals.clear();
    for (auto& [itemID, slot] : slots) {
        if (slot.saved) {
            gItemTable[itemID] = slot.data;
            gItemEntityScripts[itemID] = slot.entityScript;
            gItemIconRasterOffsets[itemID] = slot.raster;
            gItemIconPaletteOffsets[itemID] = slot.palette;
            slot.saved = false;
        }
    }

    s32 count = NUM_ITEMS;
    for (auto it = slots.begin(); it != slots.end();) {
        const int32_t itemID = it->first;
        ItemSlot& slot = it->second;
        if (slot.dataStack.Empty() && slot.iconStack.Empty()) {
            it = slots.erase(it);
            continue;
        }

        slot.data = gItemTable[itemID];
        slot.entityScript = gItemEntityScripts[itemID];
        slot.raster = gItemIconRasterOffsets[itemID];
        slot.palette = gItemIconPaletteOffsets[itemID];
        slot.saved = true;

        if (!slot.dataStack.Empty()) {
            ItemData data = slot.dataStack.Top();
            data.hudElemID = itemID < NUM_ITEMS ? slot.data.hudElemID : itemID;
            gItemTable[itemID] = data;
            count = std::max<s32>(count, itemID + 1);
        }
        if (!slot.iconStack.Empty()) {
            const ItemIcon& icon = slot.iconStack.Top();
            const int32_t hudIndex = itemID < NUM_ITEMS || !slot.dataStack.Empty() ? gItemTable[itemID].hudElemID : -1;
            if (hudIndex >= 0 && hudIndex < ITEM_TABLE_CAPACITY) {
                hudOriginals.emplace(hudIndex, gItemHudScripts[hudIndex]);
                gItemHudScripts[hudIndex].enabled = icon.enabled;
                gItemHudScripts[hudIndex].disabled = icon.disabled;
            }
            gItemEntityScripts[itemID] = icon.entityScript;
            gItemIconRasterOffsets[itemID] = icon.raster;
            gItemIconPaletteOffsets[itemID] = icon.palette;
        }
        it = std::next(it);
    }
    gItemCount = count;
}

void PushIcon(
    const std::string& owner,
    int32_t itemID,
    const intptr_t (*enabled)[],
    const intptr_t (*disabled)[],
    intptr_t (*entityScript)[],
    const char* raster,
    const char* palette
) {
    const ItemIcon icon = {
        (HudScript*) enabled, (HudScript*) disabled, entityScript != nullptr ? *entityScript : nullptr,
        (intptr_t) raster,    (intptr_t) palette,
    };
    if (const std::string* previous = ItemSlots()[itemID].iconStack.Push(owner, icon)) {
        SPDLOG_WARN("Mod: {} replaces the icon of item {} set by {}", owner, itemID, *previous);
    }
}

} // namespace

extern "C" void Mod_RegisterItem(
    const char* owner,
    int32_t itemID,
    const ItemData* data,
    const intptr_t (*enabled)[],
    const intptr_t (*disabled)[],
    intptr_t (*entityScript)[],
    const char* raster,
    const char* palette
) {
    if (!ValidItem(itemID) || data == nullptr) {
        return;
    }
    const std::string name = Mod::OwnerName(owner);
    if (const std::string* previous = ItemSlots()[itemID].dataStack.Push(name, *data)) {
        SPDLOG_WARN("Mod: {} replaces item {} registered by {}", name, itemID, *previous);
    }
    if (enabled != nullptr || disabled != nullptr || entityScript != nullptr || raster != nullptr || palette != nullptr)
    {
        PushIcon(name, itemID, enabled, disabled, entityScript, raster, palette);
    }
    ApplyItems();
}

extern "C" void Mod_SetItemIcon(
    const char* owner,
    int32_t itemID,
    const intptr_t (*enabled)[],
    const intptr_t (*disabled)[],
    intptr_t (*entityScript)[],
    const char* raster,
    const char* palette
) {
    if (!ValidItem(itemID)) {
        return;
    }
    PushIcon(Mod::OwnerName(owner), itemID, enabled, disabled, entityScript, raster, palette);
    ApplyItems();
}

void Mod::UnregisterItems(const std::string& owner) {
    bool changed = false;
    for (auto& [itemID, slot] : ItemSlots()) {
        changed |= slot.dataStack.Remove(owner);
        changed |= slot.iconStack.Remove(owner);
    }
    if (changed) {
        ApplyItems();
    }
}
