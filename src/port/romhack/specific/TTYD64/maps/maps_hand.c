#include "common.h"
#include "effects.h"
#include "model.h"
#include "vars_access.h"
#include "npc.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/maps/maps.h"

s32 TTYD64_mac_02_TayceT_ItemChoiceList[TTYD64_MAC_02_ITEM_CHOICE_COUNT];

API_CALLABLE(TTYD64_kkj_25_Function_FullyHeal) {
    PlayerData* playerData = &gPlayerData;

    TTYD64_Function_HealPartners();
    playerData->starBeamLevel = 2;
    playerData->curHP = playerData->curMaxHP;
    playerData->curFP = playerData->curMaxFP;
    playerData->starPower = playerData->maxStarPower << 8;
    sync_status_bar();
    return ApiStatus_DONE2;
}

static s32 sTTYD64_iwa_11_TattleID;

s32 TTYD64_iwa_11_Function_GetTattle(void) {
    return sTTYD64_iwa_11_TattleID;
}

void TTYD64_maps_InstallHand(void) {
    sTTYD64_iwa_11_TattleID = Mod_RegisterInlineMessage("TTYD64", TTYD64_iwa_11_String_Tattle);
}

API_CALLABLE(TTYD64_mac_04_AdjustStatMaxima) {
    PlayerData* playerData = &gPlayerData;
    s32 bp = 0;
    s32 fp = 0;
    s32 hp = 0;

    switch (script->varTable[10]) {
        case 0:
            hp = 10;
            fp = -5;
            bp = -3;
            break;
        case 1:
            hp = -5;
            fp = 10;
            bp = -3;
            break;
        case 2:
            hp = -5;
            fp = -5;
            bp = 6;
            break;
    }

    playerData->hardMaxHP += hp;
    playerData->curMaxHP += hp;
    if (playerData->curMaxHP > 99) {
        playerData->curMaxHP = 99;
    }
    if (playerData->curHP > playerData->curMaxHP) {
        playerData->curHP = playerData->curMaxHP;
    }
    playerData->hardMaxFP += fp;
    playerData->curMaxFP += fp;
    if (playerData->curMaxFP > 99) {
        playerData->curMaxFP = 99;
    }
    if (playerData->curFP > playerData->curMaxFP) {
        playerData->curFP = playerData->curMaxFP;
    }
    playerData->maxBP += bp;
    if (playerData->maxBP > 99) {
        playerData->maxBP = 99;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_mac_05_Function_Bartender_FreezeEmoteFX) {
    EffectInstance* effect = (EffectInstance*) evt_get_variable(script, MapVar(0));

    if (effect != NULL) {
        effect->data.emote->unk_2C = 99;
        return ApiStatus_BLOCK;
    }
    effect = (EffectInstance*) evt_get_variable(script, MapVar(1));
    effect->data.emote->unk_2C = 1;
    evt_set_variable(script, MapVar(1), 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_omo_05_Function_GetItemFlavor) {
    s32 itemID = evt_get_variable(script, *script->ptrReadPos);

    if (itemID == 0xC1 || itemID == 0xD2 || itemID == 0x1B7 || itemID == 0xB7) {
        script->varTable[9] = 2;
    } else if ((u16) gItemTable[itemID].typeFlags & 0x80) {
        script->varTable[9] = 1;
    } else {
        script->varTable[9] = 0;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_nok_13_Function_UpdateCaneAxis_Cane2) {
    Bytecode outVar = *script->ptrReadPos;
    PlayerStatus* playerStatus = &gPlayerStatus;

    evt_set_variable(script, outVar, (s32) atan2(-283.0f, -205.0f, playerStatus->pos.x, playerStatus->pos.z));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_nok_13_Function_UpdateCaneAxis_Cane3) {
    Bytecode outVar = *script->ptrReadPos;
    PlayerStatus* playerStatus = &gPlayerStatus;

    evt_set_variable(script, outVar, (s32) atan2(-157.0f, -99.0f, playerStatus->pos.x, playerStatus->pos.z));
    return ApiStatus_DONE2;
}

void TTYD64_nok_13_Function_UpdateReward(PlayerOrbitState* orbit, s32 event) {
    if (event == PLAYER_ORBIT_COMPLETE_ROTATION) {
        if (!get_global_flag(TTYD64_NOK_13_REWARD_FLAG)) {
            set_global_flag(TTYD64_NOK_13_REWARD_FLAG);
            start_script(&TTYD64_nok_13_Script_SpawnPipe, TTYD64_NOK_13_SPAWN_PIPE_PRIORITY, 0);
        }
    }
}

API_CALLABLE(TTYD64_mac_02_SetRecipeDiscovered) {
    s32 itemID = evt_get_variable(script, *script->ptrReadPos);
    s32* ids = TTYD64_mac_02_RecipesDiscovedIDs;
    s32* flags = TTYD64_mac_02_RecipesDiscovedFlags;

    while (true) {
        if (*ids == itemID) {
            evt_set_variable(NULL, *flags, 1);
            break;
        }
        ids++;
        flags++;
        if (*flags == 0) {
            break;
        }
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_mac_02_TayceT_MakeItemList) {
    s32 i;

    for (i = 0; i < TTYD64_MAC_02_ITEM_CHOICE_COUNT - 1; i++) {
        TTYD64_mac_02_TayceT_ItemChoiceList[i] = 6 + i;
    }
    TTYD64_mac_02_TayceT_ItemChoiceList[TTYD64_MAC_02_ITEM_CHOICE_COUNT - 1] = 0;
    return ApiStatus_DONE2;
}

static s32 TTYD64_mac_02_FindUnusedRecipeItem(void) {
    s32* flags = TTYD64_mac_02_RecipesDiscovedFlags;

    while (*flags != 0) {
        if (evt_get_variable(NULL, *flags) == 0) {
            return TTYD64_mac_02_RecipesDiscovedIDs[flags - TTYD64_mac_02_RecipesDiscovedFlags];
        }
        flags++;
    }
    return -1;
}

API_CALLABLE(TTYD64_mac_02_Function_UnusedItem) {
    Bytecode* args = script->ptrReadPos;
    s32 result = TTYD64_mac_02_FindUnusedRecipeItem();

    evt_set_variable(script, *args, result);
    return ApiStatus_DONE2;
}
