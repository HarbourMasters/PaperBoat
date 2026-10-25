#include "common.h"
#include "hud_element.h"
#include "model.h"
#include "npc.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "script_api/macros.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/world/tp.h"

#define TTYD64_TP_NPCS_TABLE_MAX 16

extern IconHudScriptPair gItemHudScripts[];

static TTYD64_PitNpcsEntry* sNpcsTables[TTYD64_TP_NPCS_TABLE_MAX];
static s32 sNpcsTableCounts[TTYD64_TP_NPCS_TABLE_MAX];
static s32 sNpcsTableCount;

void TTYD64_tp_BindMessage(Bytecode* script, const u8* msg) {
    const Bytecode id = Mod_RegisterInlineMessage("TTYD64", msg);
    Bytecode* cmd = script;

    while (true) {
        const Bytecode op = cmd[0];
        const Bytecode argc = cmd[1];

        for (Bytecode i = 0; i < argc; i++) {
            if (cmd[2 + i] == (Bytecode) msg) {
                cmd[2 + i] = id;
            }
        }
        if (op == EVT_OP_END) {
            break;
        }
        cmd += 2 + argc;
    }
}

void TTYD64_tp_RegisterNpcsTable(TTYD64_PitNpcsEntry* table, s32 count) {
    for (s32 i = 0; i < sNpcsTableCount; i++) {
        if (sNpcsTables[i] == table) {
            return;
        }
    }
    if (sNpcsTableCount >= TTYD64_TP_NPCS_TABLE_MAX) {
        GameEngine_LogInfo("TTYD64: too many pit NPC tables");
        return;
    }
    sNpcsTables[sNpcsTableCount] = table;
    sNpcsTableCounts[sNpcsTableCount] = count;
    sNpcsTableCount++;
}

s32 TTYD64_tp_PitTattle(s32* msgs) {
    u32 floor = evt_get_variable(NULL, AreaByte(0));

    if (floor < 50) {
        return msgs[0];
    }
    if (floor < 80) {
        return msgs[1];
    }
    return msgs[2];
}

API_CALLABLE(TTYD64_tp_AddKeyItem) {
    Bytecode* args = script->ptrReadPos;
    Bytecode value = *args++;
    PlayerData* playerData = &gPlayerData;
    s32 itemID = evt_get_variable(script, value);
    s32 i;

    if (itemID == ITEM_KOOPA_FORTRESS_KEY) {
        TTYD64_FortressKeys++;
        return ApiStatus_DONE2;
    }

    for (i = 0; i < ARRAY_COUNT(playerData->keyItems); i++) {
        if (playerData->keyItems[i] == ITEM_NONE) {
            break;
        }
    }

    if (i < ARRAY_COUNT(playerData->keyItems)) {
        playerData->keyItems[i] = itemID;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_tp_AddBadge) {
    Bytecode* args = script->ptrReadPos;
    s32 badgeID = evt_get_variable(script, *args++);
    Bytecode outBadgeIdx = *args++;

    evt_set_variable(script, outBadgeIdx, add_item(badgeID));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_tp_GetReminderFromDiv) {
    Bytecode* args = script->ptrReadPos;
    s32 amount = evt_get_variable(script, args[0]);
    s32 div = evt_get_variable(script, args[1]);
    s32 rem;

    if (div == 0) {
        rem = amount;
    } else if (div == -1) {
        rem = 0;
    } else {
        rem = amount % div;
    }
    evt_set_variable(script, args[2], rem);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_tp_SwitchPartners) {
    Bytecode* args = script->ptrReadPos;
    s32 newPartner = evt_get_variable(script, args[0]);

    evt_set_variable(script, args[1], (u8) gPlayerData.curPartner);
    switch_to_partner(newPartner);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_tp_GetFreeItemSlots) {
    script->varTable[0] = get_consumables_empty();
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_tp_GetVarFromVar) {
    Bytecode* args = script->ptrReadPos;
    Bytecode var = evt_get_variable(script, args[0]);

    evt_set_variable(script, args[1], evt_get_variable(script, var));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_tp_SetVarFromVar) {
    Bytecode* args = script->ptrReadPos;
    Bytecode var = evt_get_variable(script, args[0]);
    s32 value = evt_get_variable(script, args[1]);

    evt_set_variable(script, var, value);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_tp_TerritoryWrite) {
    Bytecode* args = script->ptrReadPos;
    EnemyTerritory* territory = (EnemyTerritory*) evt_get_variable(script, args[0]);
    s32 value = evt_get_variable(script, args[2]);
    s32 offset = evt_get_variable(script, args[3]);

    if (territory == NULL) {
        return ApiStatus_DONE2;
    }
    switch (offset) {
        case 0x0:
            territory->wander.centerPos.x = value;
            break;
        case 0x8:
            territory->wander.centerPos.z = value;
            break;
        case 0x1C:
            territory->wander.detectPos.x = value;
            break;
        case 0x24:
            territory->wander.detectPos.z = value;
            break;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_tp_PitNpcsRead) {
    Bytecode* args = script->ptrReadPos;
    u8* ptr = (u8*) evt_get_variable(script, args[0]);
    s32 offset = evt_get_variable(script, args[3]);
    Bytecode value = 0;

    for (s32 i = 0; i < sNpcsTableCount; i++) {
        u8* base = (u8*) sNpcsTables[i];
        intptr_t rel = ptr - base;

        if (rel >= 0 && rel % 8 == 0 && rel / 8 < sNpcsTableCounts[i]) {
            TTYD64_PitNpcsEntry* entry = &sNpcsTables[i][rel / 8];
            value = offset == 0 ? entry->first : entry->second;
            break;
        }
    }
    evt_set_variable(script, args[2], value);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_tp_PitGroupWrite) {
    Bytecode* args = script->ptrReadPos;
    NpcGroup* group = (NpcGroup*) evt_get_variable(script, args[0]);
    Bytecode value = evt_get_variable(script, args[2]);
    s32 offset = evt_get_variable(script, args[3]);

    if (group == NULL) {
        return ApiStatus_DONE2;
    }
    switch (offset) {
        case 0x0:
            group->npcCount = value;
            break;
        case 0x4:
            group->npcs = (NpcData*) value;
            break;
        case 0x8:
            group->battle = (s16) ((group->battle & 0x00FF) | ((value & 0xFF) << 8));
            break;
        case 0x9:
            group->battle = (s16) ((group->battle & 0xFF00) | (value & 0xFF));
            break;
    }
    return ApiStatus_DONE2;
}

static void TTYD64_tp_foliage_setup_shear_mtx(Matrix4f mtx, f32 scale, f32 xAmount, f32 zAmount) {
    guMtxIdentF(mtx);
    mtx[1][0] = scale * xAmount;
    mtx[1][1] = 1.0f;
    mtx[1][2] = scale * zAmount;
}

API_CALLABLE(TTYD64_tp_TransformFoliage) {
    Bytecode* args = script->ptrReadPos;
    s32 modelListIndex = get_model_list_index_from_tree_index(evt_get_variable(script, *args++));
    f32 scale = evt_get_float_variable(script, *args++);
    f32 dx = evt_get_float_variable(script, *args++);
    f32 dy = evt_get_float_variable(script, *args++);
    f32 dz = evt_get_float_variable(script, *args++);
    Model* model = get_model_from_list_index(modelListIndex);
    Matrix4f mtx;

    if (!(model->flags & MODEL_FLAG_HAS_TRANSFORM)) {
        guTranslateF(model->userTransformMtx, 0.0f, dy, 0.0f);
        TTYD64_tp_foliage_setup_shear_mtx(mtx, scale, dx, dz);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        guTranslateF(mtx, 0.0f, -dy, 0.0f);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        model->flags |= (MODEL_FLAG_HAS_TRANSFORM | MODEL_FLAG_MATRIX_DIRTY);
    } else {
        guTranslateF(mtx, 0.0f, dy, 0.0f);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        TTYD64_tp_foliage_setup_shear_mtx(mtx, scale, dx, dz);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        guTranslateF(mtx, 0.0f, -dy, 0.0f);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_tp_SetNextFloorDigit) {
    Bytecode* args = script->ptrReadPos;
    char* name = (char*) evt_get_variable(script, *args++);
    s32 digit = evt_get_variable(script, *args++);
    s32 ascii = evt_get_variable(script, *args++);

    switch (digit) {
        case TTYD64_TP_FLOOR_TENS:
            name[4] = ascii;
            break;
        case TTYD64_TP_FLOOR_ONES:
            name[5] = ascii;
            break;
    }
    return ApiStatus_DONE2;
}

static ShopItemData* tp_shop_row(ShopItemData* table, s32 index) {
    if (index < 0 || index >= TTYD64_TP_SHOP_ROWS) {
        return nullptr;
    }
    return &table[index];
}

API_CALLABLE(TTYD64_tp_GetShopBasePrice) {
    Bytecode* args = script->ptrReadPos;
    ShopItemData* row = tp_shop_row(TTYD64_pit_11_Shop_Inventory, evt_get_variable(script, *args++));

    evt_set_variable(script, *args++, row != nullptr ? row->price : -1);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_tp_GetShopPrice) {
    Bytecode* args = script->ptrReadPos;
    ShopItemData* row = tp_shop_row(TTYD64_pit_11_Shop_Inventory_Updated, evt_get_variable(script, *args++));

    evt_set_variable(script, *args++, row != nullptr ? row->price : -1);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_tp_SetShopPrice) {
    Bytecode* args = script->ptrReadPos;
    ShopItemData* row = tp_shop_row(TTYD64_pit_11_Shop_Inventory_Updated, evt_get_variable(script, *args++));
    s32 price = evt_get_variable(script, *args++);

    if (row != nullptr) {
        row->price = price;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_tp_ShowShopInventory) {
    PopupMenu* menu;
    s32 menuPos;
    s32 i;

    if (isInitialCall) {
        script->functionTempPtr[2] = heap_malloc(sizeof(*menu));
        menu = script->functionTempPtr[2];
        menuPos = 0;
        for (i = 0; i < 6; i++) {
            s32 itemID = TTYD64_pit_11_Shop_Inventory_Updated[i].itemID;
            s32 price = TTYD64_pit_11_Shop_Inventory_Updated[i].price;
            ItemData* item = &gItemTable[itemID];
            IconHudScriptPair* itemHudScripts = &gItemHudScripts[item->hudElemID];
            s32 coins = (u16) gPlayerData.coins;

            menu->userIndex[i] = i;
            menu->nameMsg[i] = item->nameMsg;
            menu->ptrIcon[i] = itemHudScripts->enabled;
            menu->enabled[i] = !(coins < price);
            if (coins < price) {
                menu->ptrIcon[i] = itemHudScripts->disabled;
                menu->enabled[i] = false;
            }
            menu->descMsg[i] = TTYD64_pit_11_Shop_Inventory_Updated[i].descMsg;
            menu->value[i] = price;
            menuPos++;
        }
        menu->popupType = 5;
        menu->numEntries = menuPos;
        menu->initialPos = 0;
        create_standard_popup_menu(menu);
        script->functionTemp[0] = 0;
    }

    menu = script->functionTempPtr[2];
    if (script->functionTemp[0] == 0) {
        script->functionTemp[1] = menu->result;
        if (script->functionTemp[1] == 0) {
            return ApiStatus_BLOCK;
        }
        hide_popup_menu();
    }
    script->functionTemp[0]++;
    if (script->functionTemp[0] < 20) {
        return ApiStatus_BLOCK;
    }

    destroy_popup_menu();
    if (script->functionTemp[1] != 0xFF) {
        s32 index = menu->userIndex[script->functionTemp[1] - 1];
        s32 itemID = TTYD64_pit_11_Shop_Inventory_Updated[index].itemID;

        script->varTable[0] = itemID;
        script->varTable[2] = index;
        script->varTable[1] = TTYD64_pit_11_Shop_Inventory_Updated[index].price;
        script->varTable[4] = gItemTable[itemID].nameMsg;
        script->varTable[5] = gMoveTable[gItemTable[itemID].moveID].costBP;
    } else {
        script->varTable[0] = -1;
    }
    heap_free(script->functionTempPtr[2]);
    return ApiStatus_DONE2;
}
