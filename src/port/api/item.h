#pragma once

#include <stdint.h>

#include "api.h"

// Mod items take the numbers after the game's own 365 (ITEM_NONE to ITEM_MENU_ITEMS).
#define C_ITEM_FIRST 0x16D
#define C_ITEM_LAST  (C_ITEM_FIRST + 1023)

// Mod moves take the numbers after the game's own 185 (MOVE_NONE to the last star power).
#define C_MOVE_FIRST 0xB9
#define C_MOVE_LAST  (C_MOVE_FIRST + 255)

typedef struct C_ItemDef_s {
    const char* id;            // stable unique key, e.g. "mymod.mega_mushroom". Saves store items by it.
    int16_t copy_from;         // game item to start from, e.g. 0x8A (ITEM_MUSHROOM). Fields left at 0 keep its values
    int32_t name_msg;          // message ID of the name
    int32_t full_desc_msg;     // message ID of the description in the pause menu
    int32_t short_desc_msg;    // message ID of the one-line description in battle and shops
    int16_t type_flags;        // ITEM_TYPE_FLAG_*: consumable, badge, key item and where it can be used
    int16_t sort_value;        // position when the player sorts the item list
    int32_t target_flags;      // TARGET_FLAG_* for consumables used in battle
    int16_t sell_value;        // coins a shop pays for it
    int16_t move_id;           // for badges, the move it grants: a game MOVE_* or a number from C_RegisterMove
    int8_t potency_a;          // HP a consumable restores, or its strength
    int8_t potency_b;          // FP a consumable restores
    const void* hud_enabled;   // HudScript of the menu icon
    const void* hud_disabled;  // HudScript of the greyed-out menu icon, hud_enabled when NULL
    const void* entity_script; // item entity script used when the item lies in the world
    const char* icon_raster;   // icon drawn inside messages, an asset path such as "__OTR__icon/..."
    const char* icon_palette;  // palette of icon_raster
} C_ItemDef;

// Registers an item from ModInit. Returns its item number for this session, or 0 (ITEM_NONE) when it can't. A mod
// registering the same id again gets the same number.
#define C_RegisterItem(def) C_RegisterItemSized((def), sizeof(*(def)))
PB_API int16_t C_RegisterItemSized(const C_ItemDef* def, uint32_t size);
// Unregisters an item. Copies the player still has show as nothing until it is registered again.
PB_API void C_UnregisterItem(int16_t item);
// Number of the registered item with this id, or 0.
PB_API int16_t C_FindItem(const char* id);
// Id of a mod item, or NULL for the game's own items and free numbers.
PB_API const char* C_GetItemId(int16_t item);

typedef struct C_MoveDef_s {
    const char* id;         // stable unique key, e.g. "mymod.triple_jump"
    int16_t copy_from;      // game move to start from, e.g. 0x2B (MOVE_POWER_JUMP). Fields left at 0 keep its values
    int32_t name_msg;       // message ID of the name
    int32_t short_desc_msg; // message ID of the description in the battle menu
    int32_t full_desc_msg;  // message ID of the long description
    int32_t flags;          // TARGET_FLAG_* of who the move can target
    int8_t category;        // MOVE_TYPE_*
    int8_t cost_fp;         // FP the move costs in battle
    int8_t cost_bp;         // BP its badge costs to equip
    uint8_t action_tip;     // tip shown before the action command: BTL_MSG_ACTION_TIP_* - BTL_MSG_FIRST_ACTION_TIP,
                            // 255 for none
} C_MoveDef;

// Registers a move from ModInit. Returns its move number for this session, or 0 (MOVE_NONE).
#define C_RegisterMove(def) C_RegisterMoveSized((def), sizeof(*(def)))
PB_API int16_t C_RegisterMoveSized(const C_MoveDef* def, uint32_t size);
// Unregisters a move. Badges granting it grant nothing until it is registered again.
PB_API void C_UnregisterMove(int16_t move);
// Number of the registered move with this id, or 0.
PB_API int16_t C_FindMove(const char* id);
