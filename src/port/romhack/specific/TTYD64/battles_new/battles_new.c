#include "common.h"
#include "battle/battle.h"
#include "inventory.h"
#include "model.h"
#include "port/Engine.h"
#include "../TTYD64.h"
#include "../include/ttyd64_api.h"
#include "battles_new.h"

#define N64_PLAYER_DATA   0x8010F290
#define N64_PLAYER_BADGES (N64_PLAYER_DATA + 0xB4)

static s16* find_badge_slot(s16* list, s32 count, s32 badgeID) {
    s32 i;

    if (badgeID == 0) {
        return NULL;
    }
    for (i = 0; i < count; i++) {
        if ((u32) (u16) list[i] == (u32) badgeID) {
            return &list[i];
        }
    }
    return NULL;
}

API_CALLABLE(TTYD64_BattlesNew_AddBadge) {
    Bytecode* args = script->ptrReadPos;
    s32 badgeID = evt_get_variable(script, *args++);
    Bytecode outVar = *args++;

    evt_set_variable(script, outVar, add_item(badgeID));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_BattlesNew_ReadN64PlayerBadge) {
    Bytecode* args = script->ptrReadPos;
    u32 addr = (u32) evt_get_variable(script, *args++);
    Bytecode outVar = *args++;
    u32 offset = addr - N64_PLAYER_BADGES;
    u32 value = 0;

    if (offset < sizeof(gPlayerData.badges) && (offset & 1) == 0) {
        value = (u16) gPlayerData.badges[offset / 2];
    } else {
        GameEngine_LogWarn("TTYD64: badge read outside gPlayerData.badges (%08X)", addr);
    }
    evt_set_variable(script, outVar, value);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_imp_BadgeBandit_Function_ActivateBadge) {
    s32 badgeID = evt_get_variable(script, *script->ptrReadPos);
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gPlayerData.equippedBadges); i++) {
        if (gPlayerData.equippedBadges[i] == ITEM_NONE) {
            gPlayerData.equippedBadges[i] = badgeID;
            break;
        }
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_imp_BadgeBandit_Function_RemoveAndUnequipBadge) {
    Bytecode* args = script->ptrReadPos;
    s32 badgeID = evt_get_variable(script, args[0]);
    s16* slot;

    if (TTYD64_IsBadgeActivated_Stack(badgeID) != 0) {
        evt_set_variable(script, script->ptrReadPos[1], true);
        slot = find_badge_slot(gPlayerData.equippedBadges, ARRAY_COUNT(gPlayerData.equippedBadges), badgeID);
        if (slot != NULL) {
            *slot = ITEM_NONE;
        }
    } else {
        evt_set_variable(script, script->ptrReadPos[1], false);
    }
    slot = find_badge_slot(gPlayerData.badges, ARRAY_COUNT(gPlayerData.badges), badgeID);
    if (slot != NULL) {
        *slot = ITEM_NONE;
    }
    return ApiStatus_DONE2;
}

static ApiStatus update_stolen_item_pos(Evt* script) {
    Actor* actor = get_actor(script->owner1.actorID);
    ActorPart* part;
    ItemEntity* item;

    if (actor == NULL) {
        return ApiStatus_DONE2;
    }
    if (actor->state.varTable[4] == -1) {
        return ApiStatus_BLOCK;
    }
    part = get_actor_part(actor, 2);
    item = get_item_entity(actor->state.varTable[4]);
    if (part == NULL || item == NULL) {
        return ApiStatus_BLOCK;
    }
    item->pos.x = part->curPos.x;
    item->pos.y = part->curPos.y;
    item->pos.z = part->curPos.z;
    return ApiStatus_BLOCK;
}

API_CALLABLE(TTYD64_imp_BadgeBandit_Function_UpdateBadgePos) {
    return update_stolen_item_pos(script);
}

API_CALLABLE(TTYD64_imp_BigBandit_Function_UpdateItemPos) {
    return update_stolen_item_pos(script);
}

API_CALLABLE(TTYD64_imp_BigBandit_Function_GetItemByIndex) {
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, args[0]);
    s32 capacity = get_consumables_capacity();
    s32 itemID = ITEM_NONE;
    s32 i;

    for (i = 0; i < capacity && itemID == ITEM_NONE; i++) {
        if (gPlayerData.invItems[i] != ITEM_NONE && index-- == 0) {
            itemID = gPlayerData.invItems[i];
        }
    }
    for (i = 0; i < ARRAY_COUNT(gPlayerData.storedItems) && itemID == ITEM_NONE; i++) {
        if (gPlayerData.storedItems[i] != ITEM_NONE && index-- == 0) {
            itemID = gPlayerData.storedItems[i];
        }
    }
    evt_set_variable(script, args[1], itemID);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_imp_BigBandit_Function_GetAmountOfItems) {
    script->varTable[0] = get_consumables_count();
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_imp_BigBandit_Function_GetFreeItemSlots) {
    script->varTable[0] = get_consumables_empty();
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_imp_FlowerFuzzy_Function_UpdateBGColor_Darker) {
    if (isInitialCall) {
        mdl_set_all_tint_type(ENV_TINT_SHROUD);
        *gBackgroundTintModePtr = ENV_TINT_SHROUD;
        mdl_set_shroud_tint_params(0, 0, 0, 0);
        script->functionTemp[0] = 20;
    }

    mdl_set_shroud_tint_params(0, 0, 0, ((20 - script->functionTemp[0]) * 10) & 254);
    script->functionTemp[0]--;

    if (script->functionTemp[0] == 0) {
        return ApiStatus_DONE2;
    }
    return ApiStatus_BLOCK;
}

void TTYD64_InstallBattlesNew(void) {
    TTYD64_InstallBattles_pit_part_1();
    TTYD64_InstallBattles_pit_part_2();
    TTYD64_InstallBattles_pit_part_3();
    TTYD64_InstallBattles_pit_part_4();
    TTYD64_InstallBattles_pit_part_5();
    TTYD64_InstallBattles_pit_part_6();
    TTYD64_InstallBattles_pit_part_7();
    TTYD64_InstallBattles_pit_part_8();
    TTYD64_InstallBattles_pit_part_9();
    TTYD64_InstallBattles_pit_part_10();
    TTYD64_InstallBattles_pit_part_11();
    TTYD64_InstallBattles_tyd_part_1();
    TTYD64_InstallBattles_tyd_part_2();
    TTYD64_InstallBattles_tyd_part_3();
}
