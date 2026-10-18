#include "common.h"
#include "battle/battle.h"
#include "battle/battle_menu.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/modding/Mod.h"
#include "badges_internal.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_items.h"
#include "../include/ttyd64_symbols.h"
#include "inventory.h"

static s32 sFocusType;
static s32 sChargeType;
static s32 sDefendType;

static void bs_on_battle_menu_open(IEvent* event) {
    OnBattleMenuOpen* ev = (OnBattleMenuOpen*) event;

    if (ev->who == ACTOR_PLAYER) {
        TTYD64_ActorRec(ACTOR_PLAYER)->defendStack = 0;
    } else {
        TTYD64BattleRec* rec = TTYD64_CurPartnerRec();

        if (rec != nullptr) {
            rec->defendStack = 0;
        }
    }
}

static void bs_on_badge_menu_entry(IEvent* event) {
    OnBattleBadgeMenuEntry* ev = (OnBattleBadgeMenuEntry*) event;

    switch (ev->submenu) {
        case BTL_MENU_TYPE_JUMP:
        case BTL_MENU_TYPE_SMASH:
            if (TTYD64_bs_IsBadgeInSubMenu((u16) *ev->badgeID, ev->entryCount)) {
                *ev->badgeID = 0;
            }
            break;
        case BTL_MENU_TYPE_ITEMS:
            *ev->badgeID = TTYD64_bs_DipBadge(*ev->badgeID, ev->entryCount);
            break;
    }
}

static void bs_strats_pick_focus(const BattleMenuContext* ctx, const BattleMenuEntry* entry) {
    BattleStatus* battleStatus = &gBattleStatus;

    battleStatus->moveCategory = BTL_MENU_TYPE_STAR_POWERS;
    battleStatus->moveArgument = 0;
    battleStatus->selectedMoveID = MOVE_FOCUS;
    btl_set_state(ctx->who == ACTOR_PLAYER ? BATTLE_STATE_PLAYER_MOVE : BATTLE_STATE_PARTNER_MOVE);
}

static void bs_strats_pick_charge(const BattleMenuContext* ctx, const BattleMenuEntry* entry) {
    gBattleStatus.selectedMoveID = 1;
    btl_set_state(BATTLE_STATE_DEFEND);
}

static void bs_strats_pick_defend(const BattleMenuContext* ctx, const BattleMenuEntry* entry) {
    gBattleStatus.selectedMoveID = 0;
    btl_set_state(BATTLE_STATE_DEFEND);
}

static void bs_strats_provider(const BattleMenuContext* ctx, BattleMenuList* list) {
    s32 chargeCost = TTYD64_IsBadgeActivated_Stack(ctx->who == ACTOR_PLAYER ? 0x16D : 0x17D);
    b32 chargeShort = (u32) (u8) gPlayerData.curFP < (u32) chargeCost;
    b32 canFlee = (gBattleStatus.flags2 & BS_FLAGS2_CAN_FLEE) != 0;
    BattleMenuEntry* entry;
    s32 runAway;
    s32 index;

    index = BattleMenu_FindType(list, BTL_MENU_TYPE_DO_NOTHING);
    if (index >= 0) {
        BattleMenu_Remove(list, index);
    }
    if ((u32) TTYD64_Function_GetPartnersUnlocked() < 2) {
        index = BattleMenu_FindType(list, BTL_MENU_TYPE_CHANGE_PARTNER);
        if (index >= 0) {
            BattleMenu_Remove(list, index);
        }
    }

    runAway = BattleMenu_FindType(list, BTL_MENU_TYPE_RUN_AWAY);
    if (runAway < 0) {
        runAway = BattleMenu_Count(list);
        entry = BattleMenu_Insert(list, runAway);
        if (entry == nullptr) {
            return;
        }
        entry->menuType = BTL_MENU_TYPE_RUN_AWAY;
    }
    entry = BattleMenu_At(list, runAway);
    entry->nameMsg = 0x1D003B;
    entry->descMsg = 0x1D00A3;
    entry->enabled = canFlee;
    entry->icon = canFlee ? &TTYD64_IconScript_RunAway : &TTYD64_IconScript_RunAwayBW;
    entry->errorMsg = MSG_Menus_Battle_CantRunAway;

    if ((u8) gPlayerData.maxStarPower != 0) {
        entry = BattleMenu_Insert(list, runAway++);
        if (entry != nullptr) {
            entry->menuType = sFocusType;
            entry->nameMsg = 0x1D0048;
            entry->descMsg = 0x1D0020;
            entry->icon = &TTYD64_IconScript_Focus;
            entry->onSelect = bs_strats_pick_focus;
        }
    }
    if (chargeCost != 0) {
        entry = BattleMenu_Insert(list, runAway++);
        if (entry != nullptr) {
            entry->menuType = sChargeType;
            entry->nameMsg = 0x2A0002;
            entry->descMsg = TTYD64_bs_MsgChargeDesc;
            entry->icon = chargeShort ? &TTYD64_IconScript_ChargeCommandBW : &TTYD64_IconScript_ChargeCommand;
            entry->enabled = !chargeShort;
            entry->errorMsg = 0x1D009F;
            entry->cost = chargeCost;
            entry->onSelect = bs_strats_pick_charge;
        }
    }
    entry = BattleMenu_Insert(list, runAway++);
    if (entry != nullptr) {
        entry->menuType = sDefendType;
        entry->nameMsg = 0x1D0044;
        entry->descMsg = TTYD64_bs_MsgDefenseDesc;
        entry->icon = &TTYD64_IconScript_Defense;
        entry->onSelect = bs_strats_pick_defend;
    }

    BattleMenu_SetInitial(list, 0);
    gBattleStatus.lastPartnerMenuSelection[BTL_MENU_IDX_STRATEGY] = 0;
    gBattleStatus.selectedMoveID = 0;
}

static void
bs_strats_draw_entry(const BattleMenuContext* ctx, s32 index, const BattleMenuEntry* entry, s32 x, s32 y, s32 alpha) {
    if (entry != nullptr && entry->menuType == sChargeType) {
        TTYD64_bs_DrawChargeCost(x, y);
    }
}

static void bs_moves_cost_palette_provider(const BattleMenuContext* ctx, BattleMenuList* list) {
    s32 palette = find_item(TTYD64_ITEM_STRANGESACK) >= 0 ? 20 : 10;
    s32 i;

    for (i = 0; i < BattleMenu_Count(list); i++) {
        BattleMenu_At(list, i)->costPalette = palette;
    }
}

void TTYD64_InstallBadgesStratsMenu(void) {
    static const BattleMenuHud sStratsHud = { nullptr, nullptr, bs_strats_draw_entry };

    sFocusType = Mod_AllocBattleMenuType(TTYD64_BS_OWNER);
    sChargeType = Mod_AllocBattleMenuType(TTYD64_BS_OWNER);
    sDefendType = Mod_AllocBattleMenuType(TTYD64_BS_OWNER);
    Mod_AddBattleMenuEntries(TTYD64_BS_OWNER, BATTLE_MENU_STRATEGIES, bs_strats_provider);
    Mod_AddBattleMenuHud(TTYD64_BS_OWNER, BATTLE_MENU_STRATEGIES, &sStratsHud);
    Mod_AddBattleMenuEntries(TTYD64_BS_OWNER, BATTLE_MENU_MOVES, bs_moves_cost_palette_provider);
    REGISTER_LISTENER(OnBattleMenuOpen, EVENT_PRIORITY_NORMAL, bs_on_battle_menu_open);
    REGISTER_LISTENER(OnBattleBadgeMenuEntry, EVENT_PRIORITY_NORMAL, bs_on_badge_menu_entry);
}
