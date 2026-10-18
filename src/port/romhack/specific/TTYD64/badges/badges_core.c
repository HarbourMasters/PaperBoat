#include "common.h"
#include "script_api/battle.h"
#include "badges_internal.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_symbols.h"
#include "battle/battle_menu.h"
#include "port/modding/Abilities.h"

extern s32 pause_get_total_equipped_bp_cost(void);
extern void add_star_power(s32 amt);

u32 TTYD64_bs_DupTable[TTYD64_BS_DUP_SLOTS];
u32 TTYD64_bs_DupTableCopy[TTYD64_BS_DUP_SLOTS];

s32 TTYD64_IsBadgeActivated_Stack(s32 badgeID) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gPlayerData.equippedBadges); i++) {
        if ((u32) (u16) gPlayerData.equippedBadges[i] == (u32) badgeID) {
            count++;
        }
    }
    return count;
}

s32 TTYD64_BadgeCount(s32 itemID) {
    return TTYD64_IsBadgeActivated_Stack(itemID);
}

s32 TTYD64_bs_GetSameBadgeAmount(u32 badgeID) {
    s32 count = 0;
    s32 i;

    if (badgeID == 0) {
        return 0;
    }
    for (i = 0; i < ARRAY_COUNT(gPlayerData.badges); i++) {
        if ((u32) (u16) gPlayerData.badges[i] == badgeID) {
            count++;
        }
    }
    return count;
}

s32 TTYD64_bs_GetBadgeInventoryPosition(u32 badgeID) {
    s32 i;

    if (badgeID == 0) {
        return -1;
    }
    for (i = 0; i < ARRAY_COUNT(gPlayerData.badges); i++) {
        if ((u32) (u16) gPlayerData.badges[i] == badgeID) {
            return i;
        }
    }
    return -1;
}

s32 TTYD64_bs_GetBadgeListFirstPos(const s16* badgeList, u32 badgeID) {
    s32 i;

    for (i = 0; i < 64; i++) {
        if ((u32) (u16) badgeList[i] == badgeID) {
            return i;
        }
    }
    return -1;
}

void TTYD64_bs_DupClear(void) {
    s32 i;

    for (i = 0; i < TTYD64_BS_DUP_SLOTS; i++) {
        TTYD64_bs_DupTable[i] = 0;
    }
}

void TTYD64_bs_DupBackupClear(void) {
    s32 i;

    for (i = 0; i < TTYD64_BS_DUP_SLOTS; i++) {
        TTYD64_bs_DupTableCopy[i] = 0;
    }
}

void TTYD64_bs_DupInit(void) {
    u32 slot = 0;
    u32 counter = 0;

    TTYD64_bs_DupClear();
    do {
        u32 badgeID = (u16) gPlayerData.equippedBadges[slot];

        if (TTYD64_bs_GetSameBadgeAmount(badgeID) < 2) {
            slot++;
            counter++;
        } else {
            u32 active = TTYD64_IsBadgeActivated_Stack(badgeID);
            u32 next = 0;
            u32 entry;

            while (next < TTYD64_BS_DUP_SLOTS && TTYD64_bs_DupTable[next] != 0) {
                next++;
            }
            entry = badgeID << 16;
            do {
                if (next < TTYD64_BS_DUP_SLOTS) {
                    TTYD64_bs_DupTable[next] = entry;
                }
                next++;
                entry++;
            } while ((entry & 0xFFFF) < active);
            counter += active;
            slot += active;
        }
    } while (counter < 64);
}

void TTYD64_bs_DupReorder(void) {
    u32 i;

    for (i = 0; i < TTYD64_BS_DUP_SLOTS; i++) {
        if (TTYD64_bs_DupTable[i] == 0) {
            u32 j = i;
            u32 found;

            do {
                j++;
                if (j >= TTYD64_BS_DUP_SLOTS) {
                    return;
                }
                found = TTYD64_bs_DupTable[j];
            } while (found == 0);
            TTYD64_bs_DupTable[i] = found;
            TTYD64_bs_DupTable[j] = 0;
        }
    }
}

void TTYD64_bs_DupBackup(void) {
    s32 i;

    for (i = 0; i < TTYD64_BS_DUP_SLOTS; i++) {
        TTYD64_bs_DupTableCopy[i] = TTYD64_bs_DupTable[i];
    }
}

s32 TTYD64_bs_IsEquippedDup(u32 badgeID, u32 copyID) {
    u32 key = (badgeID << 16) + copyID;
    s32 i;

    for (i = 0; i < TTYD64_BS_DUP_SLOTS; i++) {
        if (TTYD64_bs_DupTable[i] == key) {
            return 1;
        }
    }
    return 0;
}

s32 TTYD64_bs_IsEquippedDupByIndex(u32 badgeID, u32 copyIndex) {
    u32 seen = 0;
    s32 i;

    for (i = 0; i < TTYD64_BS_DUP_SLOTS; i++) {
        if ((TTYD64_bs_DupTableCopy[i] >> 16) == badgeID) {
            u32 match = (copyIndex == seen);

            seen++;
            if (match) {
                return TTYD64_bs_DupTable[i] != 0;
            }
        }
    }
    return 0;
}

void TTYD64_bs_DupEquip(u32 badgeID, u32 copyID) {
    u32 key = (badgeID << 16) + copyID;
    s32 i;

    for (i = 0; i < TTYD64_BS_DUP_SLOTS; i++) {
        if (TTYD64_bs_DupTable[i] == 0) {
            TTYD64_bs_DupTable[i] = key;
            return;
        }
    }
}

void TTYD64_bs_DupEquipByIndex(u32 badgeID, u32 copyIndex) {
    u32 seen = 0;
    s32 i;

    for (i = 0; i < TTYD64_BS_DUP_SLOTS; i++) {
        if ((TTYD64_bs_DupTableCopy[i] >> 16) == badgeID) {
            u32 match = (copyIndex == seen);

            seen++;
            if (match) {
                TTYD64_bs_DupTable[i] = TTYD64_bs_DupTableCopy[i];
                return;
            }
        }
    }
}

void TTYD64_bs_DupUnequip(u32 badgeID, u32 copyID) {
    u32 key = (badgeID << 16) + copyID;
    s32 i;

    for (i = 0; i < TTYD64_BS_DUP_SLOTS; i++) {
        if (TTYD64_bs_DupTable[i] == key) {
            TTYD64_bs_DupTable[i] = 0;
            return;
        }
    }
}

void TTYD64_bs_DupUnequipByIndex(u32 badgeID, u32 copyIndex) {
    u32 seen = 0;
    s32 i;

    for (i = 0; i < TTYD64_BS_DUP_SLOTS; i++) {
        if ((TTYD64_bs_DupTableCopy[i] >> 16) == badgeID) {
            u32 match = (copyIndex == seen);

            seen++;
            if (match) {
                TTYD64_bs_DupTable[i] = 0;
                return;
            }
        }
    }
}

void TTYD64_bs_SortCopies(s16* list, s32 endIndex, s32 readable) {
    s32 i;

    for (i = 0; i < TTYD64_BS_DUP_SLOTS; i++) {
        u32 entry = TTYD64_bs_DupTable[i];
        u16 badgeID;
        u16 copyID;
        s32 orig;
        s32 copy;
        s32 seen;
        s32 dest;
        s32 pos;

        if (entry == 0) {
            continue;
        }
        badgeID = entry >> 16;
        copyID = entry & 0xFFFF;
        if (copyID == 0) {
            continue;
        }

        orig = 0;
        while (true) {
            u16 value;

            if (orig >= readable) {
                goto next;
            }
            value = list[orig];
            orig++;
            if (orig == endIndex) {
                goto next;
            }
            if (value == badgeID) {
                break;
            }
        }
        orig--;

        copy = orig;
        seen = 0;
        while (true) {
            u16 value;

            if (copy >= readable) {
                goto next;
            }
            value = list[copy];
            copy++;
            if (copy == endIndex) {
                goto next;
            }
            if (value != badgeID) {
                continue;
            }
            if (seen != copyID) {
                seen++;
                continue;
            }
            break;
        }
        copy--;

        dest = orig + copyID;
        pos = copy;
        if ((u16) list[pos - 1] == badgeID) {
            goto next;
        }
        list[copy] = 0;
        do {
            pos--;
            list[pos + 1] = list[pos];
        } while (dest != pos && pos > 0);
        list[pos] = badgeID;
    next:;
    }
}

s32 TTYD64_bs_CanThisBadgeBeEquipped(u32 badgeID) {
    PlayerData* playerData = &gPlayerData;
    s32 totalCost = pause_get_total_equipped_bp_cost();
    s16 id = (s16) badgeID;
    s32 i;

    if (id != 0) {
        if (playerData->maxBP < totalCost + Mod_GetBadgeBPCost(id)) {
            return 0;
        }
    }
    for (i = 0; i < ARRAY_COUNT(playerData->equippedBadges); i++) {
        if (playerData->equippedBadges[i] == 0) {
            break;
        }
    }
    if (i == ARRAY_COUNT(playerData->equippedBadges)) {
        return 0;
    }
    return 1;
}

s32 TTYD64_bs_IsBadgeInSubMenu(u32 badgeID, s32 count) {
    s32 i;

    for (i = 0; i < count && i < ARRAY_COUNT(gBattleStatus.submenuIcons); i++) {
        if ((u32) (u16) gBattleStatus.submenuIcons[i] == badgeID) {
            return 1;
        }
    }
    return 0;
}

API_CALLABLE(TTYD64_bs_IsBadgeActivated_Stack_API) {
    Bytecode* args = script->ptrReadPos;
    s32 badgeID = evt_get_variable(script, args[0]);

    evt_set_variable(script, args[1], TTYD64_IsBadgeActivated_Stack(badgeID));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetStackBoost) {
    Bytecode* args = script->ptrReadPos;
    s32 boost = evt_get_variable(script, args[1]);
    s32 badgeID = evt_get_variable(script, args[0]);
    s32 total = (s32) ((u32) (TTYD64_IsBadgeActivated_Stack(badgeID) - 1) * (u32) boost);

    evt_set_variable(script, args[2], total);
    evt_set_variable(script, args[3], total);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetStackBoostDebuff) {
    Bytecode* args = script->ptrReadPos;
    u32 debuffKey = evt_get_variable(script, args[1]);
    s32 boost = evt_get_variable(script, args[2]);
    s32 badgeID = evt_get_variable(script, args[0]);
    u32 turns;

    boost = (s32) ((u32) (TTYD64_IsBadgeActivated_Stack(badgeID) - 1) * (u32) boost);
    turns = ((debuffKey << 20) >> 28) + (u32) boost;
    if (turns >= 10) {
        turns = 9;
    }
    debuffKey = (debuffKey & 0xFFFFF0FF) | (turns << 8);
    evt_set_variable(script, args[3], debuffKey);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_PartnerFocus) {
    PlayerData* playerData = &gPlayerData;

    script->varTable[0] = 0;
    if (!(playerData->starPower < (playerData->maxStarPower << 8))) {
        script->varTable[0] = 1;
        return ApiStatus_DONE2;
    }
    add_star_power((s32) ((u32) 0x40 * (u32) TTYD64_IsBadgeActivated_Stack(0x143)) + 0x80);
    if (playerData->starPower != (playerData->maxStarPower << 8)) {
        return ApiStatus_DONE2;
    }
    script->varTable[0] = 2;
    return ApiStatus_DONE2;
}

s32 TTYD64_EnemyCalcDamage_Defense(Actor* attacker, s32 damage) {
    u16 targetID = attacker->targetActorID;

    if (targetID == 0) {
        if (TTYD64_ActorRec(ACTOR_PLAYER)->defendStack != 0) {
            damage--;
        }
    } else if (targetID == 0x100) {
        TTYD64BattleRec* rec = TTYD64_CurPartnerRec();

        if (rec != NULL && rec->defendStack != 0) {
            damage--;
        }
    }
    return damage;
}

void TTYD64_bs_PauseInitHook(void) {
    TTYD64_bs_DupInit();
    TTYD64_bs_SortCopies(gPlayerData.equippedBadges, TTYD64_BS_INIT_SORT_END, ARRAY_COUNT(gPlayerData.equippedBadges));
    TTYD64_bs_SortCopies(
        gPlayerData.equippedBadges, ARRAY_COUNT(gPlayerData.equippedBadges), ARRAY_COUNT(gPlayerData.equippedBadges)
    );
    TTYD64_bs_DupClear();
    TTYD64_bs_DupInit();
}

void TTYD64_bs_PauseLoadHook(void) {
    TTYD64_bs_DupReorder();
    TTYD64_bs_DupBackupClear();
    TTYD64_bs_DupBackup();
}

void TTYD64_bs_PauseTabSwitchHook(s16* badgeList, s32 badgeListCount, s32 tab) {
    if ((u8) tab != 1) {
        return;
    }
    TTYD64_bs_SortCopies(
        gPlayerData.equippedBadges, ARRAY_COUNT(gPlayerData.equippedBadges), ARRAY_COUNT(gPlayerData.equippedBadges)
    );
    TTYD64_bs_SortCopies(badgeList, TTYD64_BS_BADGE_LIST_SORT_END, badgeListCount);
}

s32 TTYD64_bs_DrawItemDecision(u32 badgeID, s32 pagePlusOne, u32 rowOffset, s32 tab, const s16* badgeList) {
    s32 firstPos;
    u32 position;
    u32 copyID;

    if (TTYD64_bs_GetSameBadgeAmount(badgeID) < 2) {
        return -1;
    }
    if ((u8) tab == 0) {
        firstPos = TTYD64_bs_GetBadgeInventoryPosition(badgeID);
    } else {
        firstPos = TTYD64_bs_GetBadgeListFirstPos(badgeList, badgeID);
    }
    position = (rowOffset >> 4) + (u32) (pagePlusOne - 1) * 8;
    copyID = position - (u32) firstPos;
    if ((u8) tab == 0) {
        return TTYD64_bs_IsEquippedDup(badgeID, copyID) != 0;
    }
    return TTYD64_bs_IsEquippedDupByIndex(badgeID, copyID) != 0;
}

s32 TTYD64_bs_TryEquipDecision(s32 badgeID, s32 selectedItem, s32 tab, const s16* badgeList) {
    s32 i;
    u32 copyID;

    for (i = 0; i < ARRAY_COUNT(gPlayerData.equippedBadges); i++) {
        if (gPlayerData.equippedBadges[i] == badgeID) {
            if (TTYD64_bs_GetSameBadgeAmount(badgeID) < 2) {
                return 1;
            }
            goto copies;
        }
    }
    if (TTYD64_bs_GetSameBadgeAmount(badgeID) < 2) {
        return 0;
    }
copies:
    if ((u8) tab == 0) {
        copyID = (u32) selectedItem - (u32) TTYD64_bs_GetBadgeInventoryPosition(badgeID);
        if (TTYD64_bs_IsEquippedDup(badgeID, copyID)) {
            TTYD64_bs_DupUnequip(badgeID, copyID);
            return 1;
        }
        if (TTYD64_bs_CanThisBadgeBeEquipped(badgeID)) {
            TTYD64_bs_DupEquip(badgeID, copyID);
        }
        return 0;
    }
    copyID = (u32) selectedItem - (u32) TTYD64_bs_GetBadgeListFirstPos(badgeList, badgeID);
    if (TTYD64_bs_IsEquippedDupByIndex(badgeID, copyID)) {
        TTYD64_bs_DupUnequipByIndex(badgeID, copyID);
        return 1;
    }
    TTYD64_bs_DupEquipByIndex(badgeID, copyID);
    return 0;
}

s32 TTYD64_bs_DrawItemDecisionPos(u32 badgeID, u32 position, s32 tab, const s16* badgeList) {
    s32 firstPos;
    u32 copyID;

    if (TTYD64_bs_GetSameBadgeAmount(badgeID) < 2) {
        return -1;
    }
    if ((u8) tab == 0) {
        firstPos = TTYD64_bs_GetBadgeInventoryPosition(badgeID);
    } else {
        firstPos = TTYD64_bs_GetBadgeListFirstPos(badgeList, badgeID);
    }
    copyID = position - (u32) firstPos;
    if ((u8) tab == 0) {
        return TTYD64_bs_IsEquippedDup(badgeID, copyID) != 0;
    }
    return TTYD64_bs_IsEquippedDupByIndex(badgeID, copyID) != 0;
}

s32 TTYD64_bs_RemoveBadge(s32 badgeID) {
    s32 i;
    s32 j;

    for (i = 0; i < ARRAY_COUNT(gPlayerData.badges); i++) {
        if ((u32) (u16) gPlayerData.badges[i] == (u32) badgeID) {
            break;
        }
    }
    if (i == ARRAY_COUNT(gPlayerData.badges)) {
        return -1;
    }
    gPlayerData.badges[i] = ITEM_NONE;
    for (j = 0; j < ARRAY_COUNT(gPlayerData.equippedBadges); j++) {
        if ((u32) (u16) gPlayerData.equippedBadges[j] == (u32) badgeID) {
            gPlayerData.equippedBadges[j] = ITEM_NONE;
            break;
        }
    }
    return i;
}

void TTYD64_dispatch_event_actor_dontKillScripts(Actor* actor, s32 event) {
    Evt* script;

    if (actor->handleEventSource == nullptr) {
        return;
    }
    actor->lastEventType = event;
    script = start_script(&TTYD64_Script_DispatchActorHandleEvent, EVT_PRIORITY_A, EVT_FLAG_RUN_IMMEDIATELY);
    script->varTable[0] = (Bytecode) actor->handleEventSource;
    actor->handleEventScript = script;
    actor->handleEventScriptID = script->id;
    script->owner1.actorID = actor->actorID;
}
