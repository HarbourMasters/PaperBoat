#ifdef ENABLE_SCRIPTING

#include "port/api/item.h"

#include "port/ShipInit.hpp"
#include "port/api/ModOwner.hpp"
#include "port/api/SizedDef.hpp"
#include "port/api/StableIds.hpp"

#include "common.h"

#include <algorithm>
#include <array>
#include <string>
#include <vector>

static_assert(C_ITEM_FIRST == NUM_ITEMS, "mod items start right after the game's own");
static_assert(C_MOVE_FIRST == NUM_MOVES, "mod moves start right after the game's own");

namespace {

constexpr int kItemCount = C_ITEM_LAST + 1;
constexpr int kMoveCount = C_MOVE_LAST + 1;
constexpr int kCustomItems = C_ITEM_LAST - C_ITEM_FIRST + 1;
constexpr int kCustomMoves = C_MOVE_LAST - C_MOVE_FIRST + 1;

struct CustomItem {
    bool used = false;
    std::string id;
    std::string owner;
    std::string iconRaster;
    std::string iconPalette;
};

struct CustomMove {
    bool used = false;
    std::string id;
    std::string owner;
};

// The game reads these through gItemTable and friends once Grow() has pointed them here. Each is sized once, so
// the pointers never move while the game runs.
std::vector<ItemData> sItemTable;
std::vector<intptr_t*> sEntityScripts;
std::vector<intptr_t> sIconRasters;
std::vector<intptr_t> sIconPalettes;
std::vector<IconHudScriptPair> sHudScripts;
std::vector<MoveData> sMoveTable;
int sHudFirst = 0;

std::array<CustomItem, kCustomItems> sItems;
std::array<CustomMove, kCustomMoves> sMoves;
StableIds sItemNumbers("items", C_ITEM_FIRST, C_ITEM_LAST);
StableIds sMoveNumbers("moves", C_MOVE_FIRST, C_MOVE_LAST);

// Copies the game's tables into ones with room for mod content and points the game at them. Done the first time a
// mod registers something, so a game without mods keeps reading its own arrays.
void Grow() {
    if (!sItemTable.empty()) {
        return;
    }

    sItemTable.assign(kItemCount, gItemTable[ITEM_NONE]);
    std::copy_n(gItemTable, gItemTableVanillaCount, sItemTable.begin());

    sEntityScripts.assign(std::max(kItemCount, (int) gItemEntityScriptsVanillaCount), gItemEntityScripts[ITEM_NONE]);
    std::copy_n(gItemEntityScripts, gItemEntityScriptsVanillaCount, sEntityScripts.begin());

    sIconRasters.assign(kItemCount, gItemIconRasterOffsets[ITEM_NONE]);
    sIconPalettes.assign(kItemCount, gItemIconPaletteOffsets[ITEM_NONE]);
    std::copy_n(gItemIconRasterOffsets, gItemIconRasterOffsetsVanillaCount, sIconRasters.begin());
    std::copy_n(gItemIconPaletteOffsets, gItemIconRasterOffsetsVanillaCount, sIconPalettes.begin());

    // A mod item's menu icon lives at a fixed slot after the game's own, so re-registering never uses up more.
    sHudFirst = gItemHudScriptsVanillaCount;
    sHudScripts.assign(sHudFirst + kCustomItems, gItemHudScripts[gItemTable[ITEM_NONE].hudElemID]);
    std::copy_n(gItemHudScripts, sHudFirst, sHudScripts.begin());

    sMoveTable.assign(kMoveCount, gMoveTable[MOVE_NONE]);
    std::copy_n(gMoveTable, gMoveTableVanillaCount, sMoveTable.begin());

    gItemTable = sItemTable.data();
    gItemEntityScripts = sEntityScripts.data();
    gItemIconRasterOffsets = sIconRasters.data();
    gItemIconPaletteOffsets = sIconPalettes.data();
    gItemHudScripts = sHudScripts.data();
    gMoveTable = sMoveTable.data();
}

template <typename T> void Override(T& field, T value) {
    if (value != 0) {
        field = value;
    }
}

CustomItem* FindItem(int item) {
    const int slot = item - C_ITEM_FIRST;
    return slot >= 0 && slot < kCustomItems && sItems[slot].used ? &sItems[slot] : nullptr;
}

CustomMove* FindMove(int move) {
    const int slot = move - C_MOVE_FIRST;
    return slot >= 0 && slot < kCustomMoves && sMoves[slot].used ? &sMoves[slot] : nullptr;
}

void InitItemApi() {
    ModOwner::AddReleaser([](const std::string& mod) {
        for (int slot = 0; slot < kCustomItems; slot++) {
            if (sItems[slot].used && sItems[slot].owner == mod) {
                C_UnregisterItem((int16_t) (C_ITEM_FIRST + slot));
            }
        }
        for (int slot = 0; slot < kCustomMoves; slot++) {
            if (sMoves[slot].used && sMoves[slot].owner == mod) {
                C_UnregisterMove((int16_t) (C_MOVE_FIRST + slot));
            }
        }
    });
}

RegisterShipInitFunc sInitItemApi(InitItemApi);

} // namespace

extern "C" int16_t C_RegisterItemSized(const C_ItemDef* itemDef, uint32_t size) {
    const SizedDef<C_ItemDef> sized(itemDef, size);
    const C_ItemDef* def = sized.get();
    if (def == nullptr || def->id == nullptr || def->id[0] == '\0') {
        return ITEM_NONE;
    }
    if (def->copy_from < 0 || def->copy_from >= NUM_ITEMS) {
        SPDLOG_ERROR("Item {}: copy_from {} is not one of the game's items", def->id, def->copy_from);
        return ITEM_NONE;
    }

    Grow();
    const std::string owner = ModOwner::Current();
    const int number = sItemNumbers.Register(def->id, owner);
    if (number < 0) {
        return ITEM_NONE;
    }

    CustomItem& item = sItems[number - C_ITEM_FIRST];
    item.used = true;
    item.id = def->id;
    item.owner = owner;

    ItemData data = sItemTable[def->copy_from];
    Override(data.nameMsg, def->name_msg);
    Override(data.fullDescMsg, def->full_desc_msg);
    Override(data.shortDescMsg, def->short_desc_msg);
    Override(data.typeFlags, def->type_flags);
    Override(data.sortValue, def->sort_value);
    Override(data.targetFlags, def->target_flags);
    Override(data.sellValue, def->sell_value);
    Override(data.moveID, def->move_id);
    Override(data.potencyA, def->potency_a);
    Override(data.potencyB, def->potency_b);

    if (def->hud_enabled != nullptr) {
        const int hud = sHudFirst + (number - C_ITEM_FIRST);
        HudScript* enabled = (HudScript*) def->hud_enabled;
        sHudScripts[hud] = { enabled, def->hud_disabled != nullptr ? (HudScript*) def->hud_disabled : enabled };
        data.hudElemID = (s16) hud;
    }
    sItemTable[number] = data;

    sEntityScripts[number] =
        def->entity_script != nullptr ? (intptr_t*) def->entity_script : sEntityScripts[def->copy_from];

    item.iconRaster = def->icon_raster != nullptr ? def->icon_raster : "";
    item.iconPalette = def->icon_palette != nullptr ? def->icon_palette : "";
    sIconRasters[number] = item.iconRaster.empty() ? sIconRasters[def->copy_from] : (intptr_t) item.iconRaster.c_str();
    sIconPalettes[number] =
        item.iconPalette.empty() ? sIconPalettes[def->copy_from] : (intptr_t) item.iconPalette.c_str();

    return (int16_t) number;
}

extern "C" void C_UnregisterItem(int16_t number) {
    CustomItem* item = FindItem(number);
    if (item == nullptr) {
        return;
    }
    item->used = false;
    sItemNumbers.Unregister(number);
    // The scripts may live in the mod's code, which is about to be freed.
    sItemTable[number] = sItemTable[ITEM_NONE];
    sEntityScripts[number] = sEntityScripts[ITEM_NONE];
    sIconRasters[number] = sIconRasters[ITEM_NONE];
    sIconPalettes[number] = sIconPalettes[ITEM_NONE];
    sHudScripts[sHudFirst + (number - C_ITEM_FIRST)] = sHudScripts[sItemTable[ITEM_NONE].hudElemID];
}

extern "C" int16_t C_FindItem(const char* id) {
    if (id == nullptr) {
        return ITEM_NONE;
    }
    const int number = sItemNumbers.Find(id);
    return FindItem(number) != nullptr ? (int16_t) number : ITEM_NONE;
}

extern "C" const char* C_GetItemId(int16_t number) {
    const CustomItem* item = FindItem(number);
    return item != nullptr ? item->id.c_str() : nullptr;
}

extern "C" int16_t C_RegisterMoveSized(const C_MoveDef* moveDef, uint32_t size) {
    const SizedDef<C_MoveDef> sized(moveDef, size);
    const C_MoveDef* def = sized.get();
    if (def == nullptr || def->id == nullptr || def->id[0] == '\0') {
        return MOVE_NONE;
    }
    if (def->copy_from < 0 || def->copy_from >= NUM_MOVES) {
        SPDLOG_ERROR("Move {}: copy_from {} is not one of the game's moves", def->id, def->copy_from);
        return MOVE_NONE;
    }

    Grow();
    const std::string owner = ModOwner::Current();
    const int number = sMoveNumbers.Register(def->id, owner);
    if (number < 0) {
        return MOVE_NONE;
    }

    CustomMove& move = sMoves[number - C_MOVE_FIRST];
    move.used = true;
    move.id = def->id;
    move.owner = owner;

    MoveData data = sMoveTable[def->copy_from];
    Override(data.nameMsg, def->name_msg);
    Override(data.shortDescMsg, def->short_desc_msg);
    Override(data.fullDescMsg, def->full_desc_msg);
    Override(data.flags, def->flags);
    Override(data.category, def->category);
    Override(data.costFP, def->cost_fp);
    Override(data.costBP, def->cost_bp);
    Override(data.actionTip, def->action_tip);
    sMoveTable[number] = data;

    return (int16_t) number;
}

extern "C" void C_UnregisterMove(int16_t number) {
    CustomMove* move = FindMove(number);
    if (move == nullptr) {
        return;
    }
    move->used = false;
    sMoveNumbers.Unregister(number);
    sMoveTable[number] = sMoveTable[MOVE_NONE];
}

extern "C" int16_t C_FindMove(const char* id) {
    if (id == nullptr) {
        return MOVE_NONE;
    }
    const int number = sMoveNumbers.Find(id);
    return FindMove(number) != nullptr ? (int16_t) number : MOVE_NONE;
}

#endif
