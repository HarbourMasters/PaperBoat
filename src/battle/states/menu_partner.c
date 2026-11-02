#include "states.h"
#include "inventory.h"
#include "battle/battle.h"
#include "battle/battle_menu.h"

#include "sprite/npc/Goompa.h"
#include "sprite/npc/BattleGoombario.h"
#include "sprite/npc/BattleKooper.h"
#include "sprite/npc/BattleBombette.h"
#include "sprite/npc/BattleParakarry.h"
#include "sprite/npc/BattleBow.h"
#include "sprite/npc/BattleWatt.h"
#include "sprite/npc/BattleSushie.h"
#include "sprite/npc/BattleLakilester.h"

enum {
    // BTL_SUBSTATE_INIT                                = 0,

    // Main menu
    BTL_SUBSTATE_MAIN_BEGIN                             = 2,
    BTL_SUBSTATE_MAIN_CHOOSING                          = 3,
    // these states would be used to select targets from main menu choices, but none of the main menu options
    // actually trigger these, so they are unused
    BTL_SUBSTATE_MAIN_HANDOVER                          = 4,
    BTL_SUBSTATE_MAIN_REOPEN_MENU                       = 5,
    BTL_SUBSTATE_MAIN_TARGET_CANCEL                     = 6,
    BTL_SUBSTATE_MAIN_TARGET_CHOSEN                     = 7,
    BTL_SUBSTATE_MAIN_SHOW_CANT_SWAP                    = 8,
    BTL_SUBSTATE_MAIN_AWAIT_CANT_SWAP                   = 9,
    // Abilities
    BTL_SUBSTATE_ABILITIES_BUILD_MENU                   = 10,
    BTL_SUBSTATE_ABILITIES_CHOOSING                     = 11,
    BTL_SUBSTATE_ABILITIES_HANDOVER                     = 12,
    BTL_SUBSTATE_ABILITIES_REOPEN_MENU                  = 13,
    BTL_SUBSTATE_ABILITIES_TARGET_CANCEL                = 14,
    BTL_SUBSTATE_ABILITIES_TARGET_CHOSEN                = 15,
    BTL_SUBSTATE_ABILITIES_SHOW_ERROR                   = 16,
    // Unknown, referenced only in btl_state_draw_partner_menu
    // Matches up with the Double/Triple dip states in menu_player.
    BTL_SUBSTATE_UNKNOWN_1                              = 20,
    BTL_SUBSTATE_UNKNOWN_2                              = 21,
    BTL_SUBSTATE_UNKNOWN_3                              = 22,
    BTL_SUBSTATE_UNKNOWN_4                              = 23,
    BTL_SUBSTATE_UNKNOWN_5                              = 24,
    // Change Partner
    BTL_SUBSTATE_CHANGE_PARTNER_BUILD_MENU              = 30,
    BTL_SUBSTATE_CHANGE_PARTNER_CHOOSING                = 31,
    BTL_SUBSTATE_CHANGE_PARTNER_HANDOVER                = 32, // handle switch to change partner state
    BTL_SUBSTATE_CHANGE_PARTNER_REOPEN_MENU             = 33,
    BTL_SUBSTATE_CHANGE_PARTNER_TARGET_CANCEL           = 34,
    BTL_SUBSTATE_CHANGE_PARTNER_TARGET_CHOSEN           = 35,
    BTL_SUBSTATE_CHANGE_PARTNER_ERROR                   = 36,
    // Items
    BTL_SUBSTATE_ITEMS_BUILD_MENU                       = 40,
    BTL_SUBSTATE_ITEMS_CHOOSING                         = 41,
    BTL_SUBSTATE_ITEMS_HANDOVER                         = 42, // handle switch to target selection state
    BTL_SUBSTATE_ITEMS_REOPEN_MENU                      = 43,
    BTL_SUBSTATE_ITEMS_TARGET_CANCEL                    = 44,
    BTL_SUBSTATE_ITEMS_TARGET_CHOSEN                    = 45,
    // Switch partner (from main menu?) (unused)
    // At one point in development, Switch Partner would have been a top-level menu option.
    // These are the states corresponding to that.
    BTL_SUBSTATE_UNUSED_CHANGE_BUILD_MENU               = 50,
    BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_CHOOSING         = 51,
    BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_HANDOVER         = 52,
    BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_REOPEN_MENU      = 53,
    BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_TARGET_CANCEL    = 54,
    BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_TARGET_CHOSEN    = 55,
    BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_SHOW_ERROR       = 56,
    // Focus
    BTL_SUBSTATE_FOCUS_BUILD_MENU                       = 60,
    BTL_SUBSTATE_FOCUS_CHOOSING                         = 61,
    BTL_SUBSTATE_FOCUS_HANDOVER                         = 62,
    BTL_SUBSTATE_FOCUS_REOPEN_MENU                      = 63,
    BTL_SUBSTATE_FOCUS_CANCELED                         = 64,
    BTL_SUBSTATE_FOCUS_SELECTED                         = 65,
    // Strategies
    BTL_SUBSTATE_STRATEGIES_BUILD_MENU                  = 200,
    BTL_SUBSTATE_STRATEGIES_CHOOSING                    = 201,
    BTL_SUBSTATE_STRATEGIES_HANDOVER                    = 202,
    BTL_SUBSTATE_STRATEGIES_REOPEN_MENU                 = 203,
    BTL_SUBSTATE_STRATEGIES_TARGET_CANCEL               = 204,
    BTL_SUBSTATE_STRATEGIES_TARGET_CHOSEN               = 205,
    BTL_SUBSTATE_STRATEGIES_SHOW_ERROR                  = 207,
    // initialize
    BTL_SUBSTATE_PERFORM_SWAP                           = 301,
    BTL_SUBSTATE_CREATE_MAIN_MENU                       = 302,
};

AnimID PartnerThinkAnims[] = {
    [PARTNER_GOOMBARIO]  ANIM_BattleGoombario_Think,
    [PARTNER_KOOPER]     ANIM_BattleKooper_Think,
    [PARTNER_BOMBETTE]   ANIM_BattleBombette_Think,
    [PARTNER_PARAKARRY]  ANIM_BattleParakarry_Think,
    [PARTNER_GOOMPA]     ANIM_Goompa_Idle,
    [PARTNER_WATT]       ANIM_BattleWatt_Think,
    [PARTNER_SUSHIE]     ANIM_BattleSushie_Think,
    [PARTNER_LAKILESTER] ANIM_BattleLakilester_Run,
    [PARTNER_BOW]        ANIM_BattleBow_Still,
    [PARTNER_GOOMBARIA]  0,
    [PARTNER_TWINK]      0,
};

AnimID PartnerIdleAnims[] = {
    [PARTNER_GOOMBARIO]  ANIM_BattleGoombario_Walk,
    [PARTNER_KOOPER]     ANIM_BattleKooper_Walk,
    [PARTNER_BOMBETTE]   ANIM_BattleBombette_Walk,
    [PARTNER_PARAKARRY]  ANIM_BattleParakarry_Walk,
    [PARTNER_GOOMPA]     ANIM_Goompa_Walk,
    [PARTNER_WATT]       ANIM_BattleWatt_Walk,
    [PARTNER_SUSHIE]     ANIM_BattleSushie_Walk,
    [PARTNER_LAKILESTER] ANIM_BattleLakilester_Walk,
    [PARTNER_BOW]        ANIM_BattleBow_Walk,
    [PARTNER_GOOMBARIA]  0,
    [PARTNER_TWINK]      0,
};

IconHudScriptPair PartnerMoveHudScripts[][5] = {
    [PARTNER_GOOMBARIO] {
        {&HES_Goombario, &HES_GoombarioDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_KOOPER] {
        {&HES_Kooper, &HES_KooperDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_BOMBETTE] {
        {&HES_Bombette, &HES_BombetteDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_PARAKARRY]  {
        {&HES_Parakarry, &HES_ParakarryDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_GOOMPA] {
        {&HES_Partner0, &HES_Partner0Disabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_WATT] {
        {&HES_Watt, &HES_WattDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_SUSHIE] {
        {&HES_Sushie, &HES_SushieDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_LAKILESTER] {
        {&HES_Lakilester, &HES_LakilesterDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
    [PARTNER_BOW] {
        {&HES_Bow, &HES_BowDisabled},
        {&HES_MoveDiamond, &HES_MoveDiamond_disabled},
        {&HES_MoveBlueOrb, &HES_MoveBlueOrbDisabled},
        {&HES_MoveGreenOrb, &HES_MoveGreenOrbDisabled},
        {&HES_MoveRedOrb, &HES_MoveRedOrbDisabled}
    },
};

s32 PartnerNameMessages[] = {
    MSG_NONE,
    MSG_Menus_Party_Goombario,
    MSG_Menus_Party_Kooper,
    MSG_Menus_Party_Bombette,
    MSG_Menus_Party_Parakarry,
    MSG_Menus_Party_Goompa,
    MSG_Menus_Party_Watt,
    MSG_Menus_Party_Sushie,
    MSG_Menus_Party_Lakilester,
    MSG_Menus_Party_Bow,
    MSG_Menus_Party_Goombaria,
    MSG_Menus_Party_Twink,
    MSG_Menus_Party_Peach,
    MSG_NONE
};

void btl_init_menu_partner(void) {
    PlayerData* playerData = &gPlayerData;
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    s32 fpCost;
    s32 i;
    s32 hasAnyBadgeMoves;

    for (i = 0; i < ARRAY_COUNT(battleStatus->submenuMoves); i++) {
        battleStatus->submenuMoves[i] = MOVE_NONE;
    }

    // In the move table (enum MoveIDs), partners get move IDs set up like this:
    //
    //  Move ID offset | Description          | Goombario example
    // ----------------+----------------------+-------------------
    //  0              | No rank only         | Headbonk
    //  1              | Super rank only      | Headbonk (2)
    //  2              | Ultra rank only      | Headbonk (3)
    //  3              | Always unlocked      | Tattle
    //  4              | Unlocked after super | Charge
    //  5              | Unlocked after ultra | Multibonk

    battleStatus->submenuMoveCount = partner->actorBlueprint->level + 2;

    // Select rank-appropriate basic move from offsets 0, 1, or 2
    battleStatus->submenuMoves[0] =
        (playerData->curPartner - 1) * 6
        + MOVE_HEADBONK1
        + partner->actorBlueprint->level;

    // Add rank-unlocked special moves from offsets 3, 4, and 5
    for (i = 1; i < battleStatus->submenuMoveCount; i++) {
        battleStatus->submenuMoves[i] =
            (playerData->curPartner - 1) * 6
            + MOVE_TATTLE
            + (i - 1);
    }

    hasAnyBadgeMoves = false;
    for (i = 0; i < battleStatus->submenuMoveCount; i++){
        MoveData* move = &gMoveTable[battleStatus->submenuMoves[i]];

        fpCost = move->costFP;
        if (fpCost != 0) {
            fpCost -= player_team_is_ability_active(player, ABILITY_FLOWER_SAVER);
            fpCost -= player_team_is_ability_active(player, ABILITY_FLOWER_FANATIC) * 2;
            if (fpCost < 1) {
                fpCost = 1;
            }
        }
        {
            CALL_EVENT(OnMoveFPCost, partner, battleStatus->submenuMoves[i], i, MOVE_FP_ENABLE, &fpCost);
        }

        battleStatus->moveCategory = BTL_MENU_TYPE_CHANGE_PARTNER;
        battleStatus->moveArgument = partner->actorBlueprint->level;
        battleStatus->curTargetListFlags = move->flags;
        create_current_pos_target_list(partner);

        if (partner->targetListLength != 0){
            hasAnyBadgeMoves = true;
            battleStatus->submenuStatus[i] = BATTLE_SUBMENU_STATUS_ENABLED;
        }

        if (partner->targetListLength == 0) {
            battleStatus->submenuStatus[i] = BATTLE_SUBMENU_STATUS_NO_TARGETS_2;
        }

        if (playerData->curFP < fpCost) {
            battleStatus->submenuStatus[i] = BATTLE_SUBMENU_STATUS_NOT_ENOUGH_FP;
        }
        if (gBattleStatus.flags2 & BS_FLAGS2_NO_TARGET_AVAILABLE) {
            battleStatus->submenuStatus[i] = BATTLE_SUBMENU_STATUS_NO_TARGETS;
        }
    }

    if (!hasAnyBadgeMoves) {
        battleStatus->menuStatus[3] = -1;
    } else {
        battleStatus->menuStatus[3] = 1;
    }
}

void btl_state_update_partner_menu(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    Actor* playerActor = battleStatus->playerActor;
    Actor* partnerActor = battleStatus->partnerActor;
    PopupMenu* popupMenu = &BattlePopupMenu;
    s32 entryIdx;
    s32 i;
    s32 popupIndex;
    s32 initialPos;
    MoveData* moveData;
    PartnerPopupProperties* popupProps;
    s32 invCapacity;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        CALL_EVENT(OnBattleMenuOpen, ACTOR_PARTNER);
        battleStatus->moveCategory = BTL_MENU_TYPE_INVALID;
        battleStatus->selectedMoveID = MOVE_NONE;
        battleStatus->curAttackElement = 0;
        if (!btl_partner_can_act()) {
            btl_set_state(BATTLE_STATE_TRANSFER_TURN);
        } else {
            btl_cam_use_preset(BTL_CAM_DEFAULT);
            battleStatus->flags1 |= BS_FLAGS1_MENU_OPEN;
            playerActor->flags &= ~(ACTOR_FLAG_USING_IDLE_ANIM | ACTOR_FLAG_SHOW_STATUS_ICONS);
            partnerActor->flags &= ~(ACTOR_FLAG_USING_IDLE_ANIM | ACTOR_FLAG_SHOW_STATUS_ICONS);
            if (battleStatus->flags1 & BS_FLAGS1_PLAYER_IN_BACK) {
                gBattleSubState = BTL_SUBSTATE_CREATE_MAIN_MENU;
            } else {
                s32 inFront = false;
                CALL_EVENT(OnTurnOrder, TURN_ORDER_PLAYER_IN_FRONT, &inFront);
                if (inFront) {
                    gBattleSubState = BTL_SUBSTATE_CREATE_MAIN_MENU;
                } else {
                    gBattleSubState = BTL_SUBSTATE_PERFORM_SWAP;
                    partnerActor->state.curPos.x = partnerActor->homePos.x;
                    partnerActor->state.curPos.z = partnerActor->homePos.z;
                    partnerActor->state.goalPos.x = playerActor->homePos.x;
                    partnerActor->state.goalPos.z = playerActor->homePos.z;
                    partnerActor->state.moveTime = 4;
                    partnerActor->state.angle = 0.0f;
                }
            }
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_PERFORM_SWAP) {
        if (partnerActor->state.moveTime != 0) {
            partnerActor->curPos.x += (partnerActor->state.goalPos.x - partnerActor->curPos.x) / partnerActor->state.moveTime;
            partnerActor->curPos.z += (partnerActor->state.goalPos.z - partnerActor->curPos.z) / partnerActor->state.moveTime;
            playerActor->curPos.x += (partnerActor->state.curPos.x - playerActor->curPos.x) / partnerActor->state.moveTime;
            playerActor->curPos.z += (partnerActor->state.curPos.z - playerActor->curPos.z) / partnerActor->state.moveTime;
        }
        partnerActor->curPos.z += sin_rad(DEG_TO_RAD(partnerActor->state.angle)) * 16.0f;
        partnerActor->yaw = clamp_angle(-partnerActor->state.angle);
        playerActor->curPos.z -= sin_rad(DEG_TO_RAD(partnerActor->state.angle)) * 16.0f;
        playerActor->yaw = clamp_angle(-partnerActor->state.angle);
        partnerActor->state.angle += 90.0f;
        if (partnerActor->state.moveTime != 0) {
            partnerActor->state.moveTime--;
        } else {
            gBattleSubState = BTL_SUBSTATE_CREATE_MAIN_MENU;
            partnerActor->curPos.x = partnerActor->state.goalPos.x;
            partnerActor->curPos.z = partnerActor->state.goalPos.z;
            playerActor->curPos.x = partnerActor->state.curPos.x;
            playerActor->curPos.z = partnerActor->state.curPos.z;
            partnerActor->homePos.x = partnerActor->curPos.x;
            partnerActor->homePos.z = partnerActor->curPos.z;
            playerActor->homePos.x = playerActor->curPos.x;
            playerActor->homePos.z = playerActor->curPos.z;
            gBattleStatus.flags1 |= BS_FLAGS1_PLAYER_IN_BACK;
        }
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_CREATE_MAIN_MENU:
            partnerActor->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
            partnerActor->flags &= ~ACTOR_FLAG_USING_IDLE_ANIM;
            playerActor->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
            playerActor->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
            btl_init_menu_items();
            btl_check_can_change_partner();

            // default menu position is section option: abilities
            // will be overridden by most recently selected option, if one exists
            initialPos = 1;
            entryIdx = 0;

            if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_MAIN] < 0) {
                battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_MAIN] = BTL_MENU_TYPE_ABILITY;
            }
            btl_init_menu_partner();
            btl_check_can_change_partner();

            // strategies menu category
            WheelOptionSubmenu[entryIdx] = BTL_MENU_TYPE_STRATEGIES;
            WheelOptionEnabled[entryIdx] = true;
            WheelOptionError[entryIdx] = 0;
            WheelOptionHudScript[entryIdx] = StrategiesHudScripts.enabled;
            WheelOptionName[entryIdx] = CenteredBattleMessages[BTL_MENU_TYPE_STRATEGIES];
            if (!(battleStatus->enabledMenusFlags & BTL_MENU_ENABLED_STRATEGIES)) {
                WheelOptionEnabled[entryIdx] = false;
                WheelOptionError[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
                WheelOptionHudScript[entryIdx] = StrategiesHudScripts.disabled;
            }
            if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_MAIN] == BTL_MENU_TYPE_STRATEGIES) {
                initialPos = entryIdx;
            }
            entryIdx++;

            // abilities menu category
            WheelOptionHudScript[entryIdx] = PartnerMoveHudScripts[playerData->curPartner][0].enabled;
            WheelOptionSubmenu[entryIdx] = BTL_MENU_TYPE_ABILITY;
            WheelOptionEnabled[entryIdx] = true;
            WheelOptionName[entryIdx] = CenteredBattleMessages[BTL_MENU_TYPE_ABILITY];
            if (battleStatus->menuStatus[3] <= 0) {
                WheelOptionHudScript[entryIdx] = PartnerMoveHudScripts[playerData->curPartner][0].disabled;
                WheelOptionEnabled[entryIdx] = false;
                WheelOptionError[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
            }
            if (!(battleStatus->enabledMenusFlags & BTL_MENU_ENABLED_ABILITIES)) {
                WheelOptionHudScript[entryIdx] = PartnerMoveHudScripts[playerData->curPartner][0].disabled;
                WheelOptionEnabled[entryIdx] = false;
                WheelOptionError[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
            }
            if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_MAIN] == BTL_MENU_TYPE_ABILITY) {
                initialPos = entryIdx;
            }
            entryIdx++;

            // focus menu category
            if (playerData->maxStarPower != 0 && is_ability_active(ABILITY_GROUP_FOCUS)) {
                WheelOptionSubmenu[entryIdx] = BTL_MENU_TYPE_PARTNER_FOCUS;
                WheelOptionEnabled[entryIdx] = true;
                WheelOptionError[entryIdx] = 0;
                WheelOptionHudScript[entryIdx] = StarPowersHudScripts.enabled;
                WheelOptionName[entryIdx] = CenteredBattleMessages[BTL_MENU_TYPE_PARTNER_FOCUS];
                if (!(battleStatus->enabledMenusFlags & BTL_MENU_ENABLED_PARTNER_FOCUS)) {
                    WheelOptionEnabled[entryIdx] = false;
                    WheelOptionError[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
                    WheelOptionHudScript[entryIdx] = StarPowersHudScripts.disabled;
                }
                if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_MAIN] == BTL_MENU_TYPE_PARTNER_FOCUS) {
                    initialPos = entryIdx;
                }
                entryIdx++;
            }
            {
                CALL_EVENT(OnBattleMenuBuilt, BATTLE_MENU_WHEEL, ACTOR_PARTNER, -1, &entryIdx, &initialPos);
                if (entryIdx > ARRAY_COUNT(WheelOptionSubmenu)) {
                    entryIdx = ARRAY_COUNT(WheelOptionSubmenu);
                } else if (entryIdx < 0) {
                    entryIdx = 0;
                }
                if (initialPos < 0) {
                    initialPos = 0;
                } else if (entryIdx > 0 && initialPos >= entryIdx) {
                    initialPos = entryIdx - 1;
                }
            }

            WheelOptionCount = entryIdx;
            BattleMenu_PrevSelected = initialPos;
            BattleMenu_WheelBase = 2 - initialPos;
            if (btl_player_can_act()) {
                BattleMenu_ShowSwapIcons = true;
            } else {
                BattleMenu_ShowSwapIcons = false;
            }
            btl_main_menu_init();
            BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
            BattleMenu_SwapDelay = 0;
            gBattleSubState = BTL_SUBSTATE_MAIN_BEGIN;
            return;
        case BTL_SUBSTATE_MAIN_BEGIN: {
            s32 anim = PartnerThinkAnims[playerData->curPartner];
            CALL_EVENT(OnPartnerAnim, PARTNER_ANIM_CONTEXT_BATTLE_MENU_THINK, playerData->curPartner, &anim);
            set_actor_anim(ACTOR_PARTNER, 0, anim);
            gBattleSubState = BTL_SUBSTATE_MAIN_CHOOSING;
        }
            // fall through
        case BTL_SUBSTATE_MAIN_CHOOSING:
            entryIdx = btl_main_menu_update();

            if (BattleMenu_SwapDelay != 0) {
                BattleMenu_SwapDelay--;
            } else if (!(gBattleStatus.flags1 & BS_FLAGS1_TUTORIAL_BATTLE) && (gGameStatusPtr->pressedButtons[0] & BUTTON_Z)) {
                if (btl_player_can_act()) {
                    sfx_play_sound(SOUND_PARTNER_SWAP_BATTLE_POS);
                    battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_MAIN] = WheelOptionSubmenu[BattleMenu_CurPos + BattleMenu_HomePos];
                    btl_main_menu_destroy();
                    btl_set_state(BATTLE_STATE_SWITCH_TO_PLAYER);
                } else {
                    sfx_play_sound(SOUND_MENU_ERROR);
                    gBattleSubState = BTL_SUBSTATE_MAIN_SHOW_CANT_SWAP;
                }
                break;
            }

            if (BattleMenu_ChooseDelay != 0) {
                BattleMenu_ChooseDelay--;
                break;
            }

            if (entryIdx != 0) {
                s32 anim = PartnerIdleAnims[playerData->curPartner];
                CALL_EVENT(OnPartnerAnim, PARTNER_ANIM_CONTEXT_BATTLE_MENU_CHOSEN, playerData->curPartner, &anim);
                set_actor_anim(ACTOR_PARTNER, 0, anim);
                battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_MAIN] = battleStatus->curPartnerSubmenu = WheelOptionSubmenu[entryIdx - 1];
                {
                    CALL_EVENT(OnBattleMenuSelect, BATTLE_MENU_WHEEL, ACTOR_PARTNER, entryIdx - 1);
                }
                switch (battleStatus->curPartnerSubmenu) {
                    case BTL_MENU_TYPE_STRATEGIES:
                        gBattleSubState = BTL_SUBSTATE_STRATEGIES_BUILD_MENU;
                        btl_state_update_partner_menu();
                        btl_state_update_partner_menu();
                        break;
                    case BTL_MENU_TYPE_ABILITY:
                        gBattleSubState = BTL_SUBSTATE_ABILITIES_BUILD_MENU;
                        btl_state_update_partner_menu();
                        btl_state_update_partner_menu();
                        break;
                    case BTL_MENU_TYPE_STAR_POWERS:
                        gBattleSubState = BTL_SUBSTATE_FOCUS_BUILD_MENU;
                        btl_state_update_partner_menu();
                        btl_state_update_partner_menu();
                        break;
                    case BTL_MENU_TYPE_ITEMS:
                        gBattleSubState = BTL_SUBSTATE_ITEMS_BUILD_MENU;
                        btl_state_update_partner_menu();
                        btl_state_update_partner_menu();
                        break;
                    case BTL_MENU_TYPE_CHANGE_PARTNER:
                        gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_BUILD_MENU;
                        btl_state_update_partner_menu();
                        btl_state_update_partner_menu();
                        break;
                    default:
                        battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_MAIN_TARGET_CANCEL;
                        battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_MAIN_TARGET_CHOSEN;
                        btl_main_menu_hide();
                        gBattleSubState = BTL_SUBSTATE_MAIN_HANDOVER;
                        break;
                }
            }
            break;
    case BTL_SUBSTATE_MAIN_HANDOVER:
        entryIdx = btl_main_menu_update();
        if ((battleStatus->curButtonsPressed & BUTTON_B) && entryIdx == 0) {
            btl_main_menu_restore_choose();
            gBattleSubState = BTL_SUBSTATE_MAIN_REOPEN_MENU;
            return;
        }
        if (entryIdx != 0) {
            battleStatus->moveCategory = BTL_MENU_TYPE_STAR_POWERS;
            battleStatus->selectedMoveID = MOVE_FOCUS;
            battleStatus->moveArgument = 0;
            battleStatus->curTargetListFlags = gMoveTable[MOVE_FOCUS].flags;
            btl_set_state(BATTLE_STATE_SELECT_TARGET);
            return;
        }
        break;
    case BTL_SUBSTATE_MAIN_REOPEN_MENU:
        if (btl_main_menu_update() != 0) {
            BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
            BattleMenu_SwapDelay = 4;
            gBattleSubState = BTL_SUBSTATE_MAIN_BEGIN;
        }
        break;
    case BTL_SUBSTATE_MAIN_TARGET_CANCEL:
        btl_main_menu_restore_choose();
        gBattleSubState = BTL_SUBSTATE_MAIN_REOPEN_MENU;
        break;
    case BTL_SUBSTATE_MAIN_TARGET_CHOSEN:
        btl_main_menu_destroy();
        break;
    case BTL_SUBSTATE_MAIN_SHOW_CANT_SWAP:
        if (!btl_player_can_act()) {
            btl_show_variable_battle_message(BTL_MSG_CANT_MOVE, 60, 0);
        } else {
            btl_show_variable_battle_message(BTL_MSG_CANT_SWITCH, 60, 0);
        }
        ShowingErrorMessage = true;
        gBattleSubState = BTL_SUBSTATE_MAIN_AWAIT_CANT_SWAP;
        break;
    case BTL_SUBSTATE_MAIN_AWAIT_CANT_SWAP:
        if (btl_is_popup_displayed()) {
            break;
        }
        ShowingErrorMessage = false;
        BattleMenu_ChooseDelay = 0;
        BattleMenu_SwapDelay = 4;
        gBattleSubState = BTL_SUBSTATE_MAIN_BEGIN;
        break;
    case BTL_SUBSTATE_ABILITIES_BUILD_MENU:
        for (i = 0; i < battleStatus->submenuMoveCount; i++) {
            moveData = &gMoveTable[battleStatus->submenuMoves[i]];

            MovesOptionError[i] = 0;
            if (battleStatus->submenuStatus[i] == 0) {
                MovesOptionError[i] = 0;
            }
            if (battleStatus->submenuStatus[i] == -1) {
                battleStatus->submenuStatus[i] = 0;
                MovesOptionError[i] = BTL_MSG_CANT_SELECT_NOW;
            }
            if (battleStatus->submenuStatus[i] == -2) {
                battleStatus->submenuStatus[i] = 0;
                MovesOptionError[i] = BTL_MSG_CANT_SELECT_NOW;
            }
            MovesOptionHudScripts[i] = PartnerMoveHudScripts[playerData->curPartner][i + 1].enabled;
            if (battleStatus->submenuStatus[i] == 0) {
                MovesOptionHudScripts[i] = PartnerMoveHudScripts[playerData->curPartner][i + 1].disabled;
            }
            MovesOptionIndices[i] = battleStatus->submenuMoves[i];
            MovesOptionEnabled[i] = battleStatus->submenuStatus[i];
            MovesOptionNames[i] = moveData->nameMsg;
            MovesOptionDesc[i] = moveData->shortDescMsg;
            MovesOptionDisplayCosts[i] = moveData->costFP;
            MovesOptionBPCosts[i] = moveData->costBP;
            MovesOptionSortPriority[i] = i;

            MovesOptionDiscounts[i] = 0;
            MovesOptionDiscountColors[i] = 0;
            if (player_team_is_ability_active(playerActor, ABILITY_FLOWER_SAVER)) {
                MovesOptionDiscounts[i] += player_team_is_ability_active(playerActor, ABILITY_FLOWER_SAVER);
                MovesOptionDiscountColors[i] = 1;
            }
            if (player_team_is_ability_active(playerActor, ABILITY_FLOWER_FANATIC)) {
                MovesOptionDiscounts[i] += player_team_is_ability_active(playerActor, ABILITY_FLOWER_FANATIC) * 2;
                MovesOptionDiscountColors[i] = 2;
            }
            {
                CALL_EVENT(OnMoveCostDisplay, partnerActor, battleStatus->submenuMoves[i], i, &MovesOptionDisplayCosts[i],
                           &MovesOptionDiscounts[i], &MovesOptionDiscountColors[i]);
            }
        }
        if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_ABILITY] < 0) {
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_ABILITY] = 0;
        }
        UsingSpiritsSubmenu = false;
        MovesOptionCount = battleStatus->submenuMoveCount;
        initialPos = battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_ABILITY];
        {
            CALL_EVENT(OnBattleMenuBuilt, BATTLE_MENU_MOVES, ACTOR_PARTNER, BTL_MENU_TYPE_ABILITY, &MovesOptionCount, &initialPos);
            if (MovesOptionCount > ARRAY_COUNT(MovesOptionIndices)) {
                MovesOptionCount = ARRAY_COUNT(MovesOptionIndices);
            } else if (MovesOptionCount < 0) {
                MovesOptionCount = 0;
            }
            if (initialPos < 0) {
                initialPos = 0;
            }
        }
        MovesPrevSelected = initialPos;
        btl_submenu_moves_init();
        gBattleSubState = BTL_SUBSTATE_ABILITIES_CHOOSING;
        break;
    case BTL_SUBSTATE_ABILITIES_CHOOSING:
        entryIdx = btl_submenu_moves_update();
        switch (entryIdx) {
            case POPUP_RESULT_CHOOSING:
                // do nothing while player is choosing from popup menu
                break;
            case POPUP_RESULT_INVALID:
                gBattleSubState = BTL_SUBSTATE_ABILITIES_SHOW_ERROR;
                break;
            case POPUP_RESULT_CANCEL:
                btl_main_menu_resume_choose();
                BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
                BattleMenu_SwapDelay = 4;
                gBattleSubState = BTL_SUBSTATE_MAIN_BEGIN;
                btl_state_update_partner_menu();
                btl_state_update_partner_menu();
                break;
            default:
                battleStatus->lastPartnerPowerSelection = entryIdx - 1;
                btl_submenu_moves_hide();
                btl_main_menu_hide();
                gBattleSubState = BTL_SUBSTATE_ABILITIES_HANDOVER;
                break;
        }
        break;
    case BTL_SUBSTATE_ABILITIES_HANDOVER:
        entryIdx = btl_submenu_moves_update();
        if ((battleStatus->curButtonsPressed & BUTTON_B) && entryIdx == 0) {
            btl_submenu_moves_restore_choose();
            btl_main_menu_restore_submenu();
            gBattleSubState = BTL_SUBSTATE_ABILITIES_REOPEN_MENU;
        } else if (btl_main_menu_update() != 0) {
            battleStatus->moveCategory = BTL_MENU_TYPE_ABILITY;
            battleStatus->selectedMoveID = MovesOptionIndices[battleStatus->lastPartnerPowerSelection];
            battleStatus->curTargetListFlags = gMoveTable[battleStatus->selectedMoveID].flags;
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_ABILITY] = SelectedMovesIndex;
            battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_ABILITIES_TARGET_CANCEL;
            battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_ABILITIES_TARGET_CHOSEN;
            btl_set_state(BATTLE_STATE_SELECT_TARGET);
        }
        break;
    case BTL_SUBSTATE_ABILITIES_REOPEN_MENU:
        btl_submenu_moves_update();
        if (btl_main_menu_update() != 0) {
            gBattleSubState = BTL_SUBSTATE_ABILITIES_CHOOSING;
        }
        break;
    case BTL_SUBSTATE_ABILITIES_TARGET_CANCEL:
        btl_submenu_moves_restore_choose();
        btl_main_menu_restore_submenu();
        gBattleSubState = BTL_SUBSTATE_ABILITIES_REOPEN_MENU;
        break;
    case BTL_SUBSTATE_ABILITIES_TARGET_CHOSEN:
        btl_submenu_moves_destroy();
        btl_main_menu_destroy();
        break;
    case BTL_SUBSTATE_ABILITIES_SHOW_ERROR:
        if (btl_submenu_moves_update() != -1) {
            gBattleSubState = BTL_SUBSTATE_ABILITIES_CHOOSING;
        }
        break;
    case BTL_SUBSTATE_ITEMS_BUILD_MENU:
        popupIndex = 0;
        invCapacity = get_consumables_capacity();
        for (i = 0; i < invCapacity; i++) {
            ItemData* item;
            HudScript** hudScript;
            if (playerData->invItems[i] == ITEM_NONE) {
                continue;
            }
            item = &gItemTable[playerData->invItems[i]];
            hudScript = &gItemHudScripts[item->hudElemID].enabled;

            if (!(item->typeFlags & ITEM_TYPE_FLAG_BATTLE_USABLE)) {
                continue;
            }
            popupMenu->ptrIcon[popupIndex] = hudScript[0];
            popupMenu->userIndex[popupIndex] = playerData->invItems[i];
            popupMenu->enabled[popupIndex] = true;
            popupMenu->nameMsg[popupIndex] = item->nameMsg;
            popupMenu->descMsg[popupIndex] = item->shortDescMsg;
            popupIndex++;
        }
        if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER_ITEM] < 0) {
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER_ITEM] = 0;
        }
        popupMenu->popupType = POPUP_MENU_USE_ITEM;
        popupMenu->numEntries = popupIndex;
        popupMenu->dipMode = 0;
        popupMenu->titleNumber = 0;
        initialPos = battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER_ITEM];
        popupMenu->initialPos = initialPos;
        create_battle_popup_menu(popupMenu);
        flush_popup_menu();
        gBattleSubState = BTL_SUBSTATE_ITEMS_CHOOSING;
        break;
    case BTL_SUBSTATE_ITEMS_CHOOSING:
        switch (popupMenu->result) {
            case POPUP_RESULT_CHOOSING:
                // do nothing while player is choosing from menu
                break;
            case POPUP_RESULT_CANCEL:
                btl_main_menu_resume_choose();
                BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
                BattleMenu_SwapDelay = 4;
                gBattleSubState = BTL_SUBSTATE_MAIN_BEGIN;
                btl_state_update_partner_menu();
                btl_state_update_partner_menu();
                break;
            default: // something has been selected
                battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_ITEMS_TARGET_CANCEL;
                battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_ITEMS_TARGET_CHOSEN;
                battleStatus->lastSelectedItem = popupMenu->userIndex[popupMenu->result - 1];
                battleStatus->moveCategory = BTL_MENU_TYPE_ITEMS;
                battleStatus->moveArgument = battleStatus->lastSelectedItem;
                battleStatus->curTargetListFlags = gItemTable[battleStatus->moveArgument].targetFlags | TARGET_FLAG_PRIMARY_ONLY;
                battleStatus->curAttackElement = 0;
                battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER_ITEM] = popupMenu->result - 1;
                hide_popup_menu();
                btl_main_menu_hide();
                gBattleSubState = BTL_SUBSTATE_ITEMS_HANDOVER;
                break;
        }
        break;
    case BTL_SUBSTATE_ITEMS_REOPEN_MENU:
        if (btl_main_menu_update() != 0) {
            gBattleSubState = BTL_SUBSTATE_ITEMS_CHOOSING;
        }
        break;
    case BTL_SUBSTATE_ITEMS_HANDOVER:
        if ((battleStatus->curButtonsPressed & BUTTON_B) && popupMenu->result == POPUP_RESULT_CHOOSING) {
            show_popup_menu();
            btl_main_menu_restore_submenu();
            gBattleSubState = BTL_SUBSTATE_ITEMS_REOPEN_MENU;
        } else if (btl_main_menu_update() != 0) {
            btl_set_state(BATTLE_STATE_SELECT_TARGET);
        }
        break;
    case BTL_SUBSTATE_ITEMS_TARGET_CANCEL:
        show_popup_menu();
        btl_main_menu_restore_submenu();
        gBattleSubState = BTL_SUBSTATE_ITEMS_REOPEN_MENU;
        break;
    case BTL_SUBSTATE_ITEMS_TARGET_CHOSEN:
        destroy_popup_menu();
        btl_main_menu_destroy();
        break;
    case BTL_SUBSTATE_UNUSED_CHANGE_BUILD_MENU:
        popupIndex = 0;
        for (i = 1; i < ARRAY_COUNT(PartnerIDFromMenuIndex); i++) {
            s32 partnerId = PartnerIDFromMenuIndex[i];
            if (playerData->partners[partnerId].enabled) {
                popupProps = &gPartnerPopupProperties[partnerId];
                popupMenu->ptrIcon[popupIndex] = PartnerHudScripts[partnerId].enabled;
                popupMenu->enabled[popupIndex] = true;
                popupMenu->userIndex[popupIndex] = partnerId;
                popupMenu->nameMsg[popupIndex] = popupProps->nameMsg;
                popupMenu->descMsg[popupIndex] = popupProps->battleDescMsg;
                popupMenu->value[popupIndex] = playerData->partners[partnerId].level;
                if (playerData->curPartner == partnerId) {
                    popupMenu->ptrIcon[popupIndex] = PartnerHudScripts[partnerId].disabled;
                    popupMenu->enabled[popupIndex] = false;
                }
                popupIndex++;
            }
        }
        if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER] < 0) {
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER] = 0;
        }
        popupMenu->popupType = POPUP_MENU_SWITCH_PARTNER;
        popupMenu->numEntries = popupIndex;
        popupMenu->initialPos = MenuIndexFromPartnerID[playerData->curPartner] - 1;
        popupMenu->dipMode = 0;
        popupMenu->titleNumber = 0;
        create_battle_popup_menu(popupMenu);
        flush_popup_menu();
        gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_CHOOSING;
        break;
    case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_CHOOSING:
        switch (popupMenu->result) {
            case POPUP_RESULT_CHOOSING:
                // do nothing while player is choosing from popup menu
                break;
            case POPUP_RESULT_INVALID:
                gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_SHOW_ERROR;
                break;
            case POPUP_RESULT_CANCEL:
                btl_main_menu_resume_choose();
                BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
                BattleMenu_SwapDelay = 4;
                gBattleSubState = BTL_SUBSTATE_MAIN_BEGIN;
                btl_state_update_partner_menu();
                btl_state_update_partner_menu();
                break;
            default:
                battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_TARGET_CANCEL;
                battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_TARGET_CHOSEN;
                battleStatus->lastSelectedPartner = popupMenu->userIndex[popupMenu->result - 1];
                battleStatus->moveCategory = BTL_MENU_TYPE_CHANGE_PARTNER;
                battleStatus->selectedMoveID = MOVE_CHANGE_PARTNER;
                battleStatus->curTargetListFlags = TARGET_FLAG_2;
                battleStatus->moveArgument = battleStatus->lastSelectedPartner;
                battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER] = popupMenu->result - 1;
                hide_popup_menu();
                btl_main_menu_hide();
                gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_HANDOVER;
                break;
        }
        break;
    case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_HANDOVER:
        if ((battleStatus->curButtonsPressed & BUTTON_B) && (popupMenu->result == POPUP_RESULT_CHOOSING)) {
            show_popup_menu();
            btl_main_menu_restore_submenu();
            gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_REOPEN_MENU;
        } else if (btl_main_menu_update() != 0) {
            gBattleSubState = battleStatus->acceptTargetMenuSubstate;
            btl_state_update_partner_menu();
            btl_set_state(BATTLE_STATE_CHANGE_PARTNER);
        }
        break;
    case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_REOPEN_MENU:
        if (btl_main_menu_update() != 0) {
            gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_CHOOSING;
        }
        break;
    case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_TARGET_CANCEL:
        show_popup_menu();
        btl_main_menu_restore_submenu();
        gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_REOPEN_MENU;
        break;
    case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_TARGET_CHOSEN:
        destroy_popup_menu();
        btl_main_menu_destroy();
        break;
    case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_SHOW_ERROR:
        if (popupMenu->result != POPUP_RESULT_INVALID) {
            gBattleSubState = BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_CHOOSING;
        }
        break;
    case BTL_SUBSTATE_FOCUS_BUILD_MENU:
        entryIdx = 1;
        battleStatus->submenuMoveCount = entryIdx;
        battleStatus->submenuMoves[0] = MOVE_FOCUS;
        battleStatus->submenuIcons[0] = ITEM_PARTNER_ATTACK;
        battleStatus->submenuStatus[0] = 1;
        for (i = 0; i < battleStatus->submenuMoveCount; i++) {
            moveData = &gMoveTable[battleStatus->submenuMoves[i]];
            MovesOptionHudScripts[i] = StarPowerMovesHudScripts[STAR_POWER_INDEX(battleStatus->submenuMoves[i])].enabled;
            if (battleStatus->submenuStatus[i] == 0) {
                MovesOptionHudScripts[i] = StarPowerMovesHudScripts[STAR_POWER_INDEX(battleStatus->submenuMoves[i])].disabled;
            }
            MovesOptionDisplayCosts[i] = moveData->costFP;
            MovesOptionBPCosts[i] = moveData->costBP;
            MovesOptionIndices[i] = i;
            MovesOptionSortPriority[i] = i;
            MovesOptionEnabled[i] = battleStatus->submenuStatus[i];
            MovesOptionNames[i] = moveData->nameMsg;
            MovesOptionDesc[i] = moveData->shortDescMsg;
            MovesOptionDiscounts[i] = 0;
            MovesOptionDiscountColors[i] = 0;
        }
        if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STAR_POWER] < 0) {
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STAR_POWER] = 0;
        }
        UsingSpiritsSubmenu = true;
        MovesOptionCount = battleStatus->submenuMoveCount;
        initialPos = battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STAR_POWER];
        {
            CALL_EVENT(OnBattleMenuBuilt, BATTLE_MENU_MOVES, ACTOR_PARTNER, BTL_MENU_TYPE_PARTNER_FOCUS, &MovesOptionCount, &initialPos);
            if (MovesOptionCount > ARRAY_COUNT(MovesOptionIndices)) {
                MovesOptionCount = ARRAY_COUNT(MovesOptionIndices);
            } else if (MovesOptionCount < 0) {
                MovesOptionCount = 0;
            }
            if (initialPos < 0) {
                initialPos = 0;
            }
        }
        MovesPrevSelected = initialPos;
        btl_submenu_moves_init();
        gBattleSubState = BTL_SUBSTATE_FOCUS_CHOOSING;
        break;
    case BTL_SUBSTATE_FOCUS_CHOOSING:
        entryIdx = btl_submenu_moves_update();
        switch (entryIdx) {
            case POPUP_RESULT_CHOOSING:
                // do nothing while player is choosing from popup menu
                break;
            case POPUP_RESULT_CANCEL:
                btl_main_menu_resume_choose();
                BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
                BattleMenu_SwapDelay = 4;
                gBattleSubState = BTL_SUBSTATE_MAIN_BEGIN;
                btl_state_update_partner_menu();
                btl_state_update_partner_menu();
                break;
            default:
                battleStatus->lastPartnerPowerSelection = MovesOptionIndices[entryIdx - 1];
                btl_submenu_moves_hide();
                btl_main_menu_hide();
                gBattleSubState = BTL_SUBSTATE_FOCUS_HANDOVER;
                break;
        }
        break;
    case BTL_SUBSTATE_FOCUS_HANDOVER:
        entryIdx = btl_submenu_moves_update();
        if ((battleStatus->curButtonsPressed & BUTTON_B) && (entryIdx == 0)) {
            btl_submenu_moves_restore_choose();
            btl_main_menu_restore_submenu();
            gBattleSubState = BTL_SUBSTATE_FOCUS_REOPEN_MENU;
        } else if (btl_main_menu_update() != 0) {
            battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_FOCUS_CANCELED;
            battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_FOCUS_SELECTED;
            battleStatus->moveCategory = BTL_MENU_TYPE_STAR_POWERS;
            battleStatus->selectedMoveID = battleStatus->submenuMoves[battleStatus->lastPartnerPowerSelection];
            battleStatus->curTargetListFlags = gMoveTable[battleStatus->submenuMoves[battleStatus->lastPartnerPowerSelection]].flags;
            battleStatus->moveArgument = battleStatus->lastPartnerPowerSelection;
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STAR_POWER] = SelectedMovesIndex;
            btl_set_state(BATTLE_STATE_SELECT_TARGET);
        }
        break;
    case BTL_SUBSTATE_FOCUS_REOPEN_MENU:
        btl_submenu_moves_update();
        if (btl_main_menu_update() != 0) {
            gBattleSubState = BTL_SUBSTATE_FOCUS_CHOOSING;
        }
        break;
    case BTL_SUBSTATE_FOCUS_CANCELED:
        btl_submenu_moves_restore_choose();
        btl_main_menu_restore_submenu();
        gBattleSubState = BTL_SUBSTATE_FOCUS_REOPEN_MENU;
        break;
    case BTL_SUBSTATE_FOCUS_SELECTED:
        btl_submenu_moves_destroy();
        btl_main_menu_destroy();
        break;
    case BTL_SUBSTATE_STRATEGIES_BUILD_MENU:
        popupIndex = 0;
        btl_check_can_change_partner();

        // add 'Change Member' command
        if (battleStatus->changePartnerAllowed >= 0) {
            StratsOptionMenuTypes[popupIndex] = BTL_MENU_TYPE_CHANGE_PARTNER;
            StratsOptionNames[popupIndex] = LeftJustMenuMessages[BTL_MENU_TYPE_CHANGE_PARTNER];
            StratsOptionHudScripts[popupIndex] = PartnerHudScripts[playerData->curPartner].enabled;
            StratsOptionMessage[popupIndex] = MSG_Menus_Action_ChangePartner;
            StratsOptionEnabled[popupIndex] = true;
            if (battleStatus->changePartnerAllowed <= 0) {
                StratsOptionHudScripts[popupIndex] = PartnerHudScripts[playerData->curPartner].disabled;
                StratsOptionEnabled[popupIndex] = false;
                StratsOptionError[popupIndex] = 0;
            }
            popupIndex++;
        }

        // add 'Do Nothing' command
        StratsOptionMenuTypes[popupIndex] = BTL_MENU_TYPE_DO_NOTHING;
        StratsOptionNames[popupIndex] = LeftJustMenuMessages[BTL_MENU_TYPE_DO_NOTHING];
        StratsOptionHudScripts[popupIndex] = DoNothingHudScripts.enabled;
        StratsOptionMessage[popupIndex] = MSG_Menus_Action_DoNothing;
        StratsOptionEnabled[popupIndex] = true;
        popupIndex++;

        if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STRATEGY] < 0) {
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STRATEGY] = 0;
        }
        initialPos = battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STRATEGY];
        {
            CALL_EVENT(OnBattleMenuBuilt, BATTLE_MENU_STRATEGIES, ACTOR_PARTNER, -1, &popupIndex, &initialPos);
            if (popupIndex > ARRAY_COUNT(StratsOptionMenuTypes)) {
                popupIndex = ARRAY_COUNT(StratsOptionMenuTypes);
            } else if (popupIndex < 0) {
                popupIndex = 0;
            }
            if (initialPos < 0) {
                initialPos = 0;
            } else if (popupIndex > 0 && initialPos >= popupIndex) {
                initialPos = popupIndex - 1;
            }
        }
        StratsOptionCount = popupIndex;
        StratsPrevSelected = initialPos;
        btl_menu_strats_init();
        gBattleSubState = BTL_SUBSTATE_STRATEGIES_CHOOSING;
        break;
    case BTL_SUBSTATE_STRATEGIES_CHOOSING:
        entryIdx = btl_submenu_strats_update();
        switch (entryIdx) {
            case POPUP_RESULT_CHOOSING:
                // do nothing while player is selecting an entry
                break;
            case POPUP_RESULT_INVALID:
                gBattleSubState = BTL_SUBSTATE_STRATEGIES_SHOW_ERROR;
                break;
            case POPUP_RESULT_CANCEL:
                btl_main_menu_resume_choose();
                BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
                BattleMenu_SwapDelay = 4;
                gBattleSubState = BTL_SUBSTATE_MAIN_BEGIN;
                btl_state_update_partner_menu();
                btl_state_update_partner_menu();
                break;
            default:
                battleStatus->curPartnerSubmenu = StratsOptionMenuTypes[entryIdx - 1];
                battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STRATEGY] = entryIdx - 1;
                if (battleStatus->curPartnerSubmenu == BTL_MENU_TYPE_CHANGE_PARTNER) {
                    gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_BUILD_MENU;
                    btl_state_update_partner_menu();
                    btl_state_update_partner_menu();
                } else {
                    btl_submenu_strats_hide();
                    btl_main_menu_hide();
                    gBattleSubState = BTL_SUBSTATE_STRATEGIES_HANDOVER;
                }
                break;
        }
        break;
    case BTL_SUBSTATE_STRATEGIES_HANDOVER:
        entryIdx = btl_submenu_strats_update();
        if ((battleStatus->curButtonsPressed & BUTTON_B) && entryIdx == POPUP_RESULT_CHOOSING) {
            btl_submenu_strats_restore_choose();
            btl_main_menu_restore_submenu();
            gBattleSubState = BTL_SUBSTATE_STRATEGIES_REOPEN_MENU;
        } else if (btl_main_menu_update() != 0) {
            battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_STRATEGIES_TARGET_CANCEL;
            battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_STRATEGIES_TARGET_CHOSEN;
            switch (battleStatus->curPartnerSubmenu) {
                case BTL_MENU_TYPE_DO_NOTHING:
                    gBattleSubState = BTL_SUBSTATE_STRATEGIES_TARGET_CHOSEN;
                    btl_state_update_partner_menu();
                    btl_set_state(BATTLE_STATE_END_PARTNER_TURN);
                    break;
                case BTL_MENU_TYPE_RUN_AWAY:
                    gBattleSubState = BTL_SUBSTATE_STRATEGIES_TARGET_CHOSEN;
                    btl_state_update_partner_menu();
                    battleStatus->moveCategory = BTL_MENU_TYPE_RUN_AWAY;
                    battleStatus->selectedMoveID = MOVE_RUN_AWAY;
                    btl_set_state(BATTLE_STATE_RUN_AWAY);
                    break;
                case BTL_MENU_TYPE_ACT_LATER:
                    gBattleSubState = BTL_SUBSTATE_STRATEGIES_TARGET_CHOSEN;
                    btl_state_update_partner_menu();
                    btl_set_state(BATTLE_STATE_SWITCH_TO_PLAYER);
                    break;
                default:
                    gBattleSubState = BTL_SUBSTATE_STRATEGIES_TARGET_CHOSEN;
                    btl_state_update_partner_menu();
                    {
                        CALL_CANCELLABLE_EVENT(OnBattleMenuSelect, BATTLE_MENU_STRATEGIES, ACTOR_PARTNER,
                                               battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_STRATEGY]) {
                            btl_set_state(BATTLE_STATE_PARTNER_MENU);
                        }
                    }
                    break;
            }
        }
        break;
    case BTL_SUBSTATE_STRATEGIES_REOPEN_MENU:
        btl_submenu_strats_update();
        if (btl_main_menu_update() != 0) {
            BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
            BattleMenu_SwapDelay = 4;
            gBattleSubState = BTL_SUBSTATE_MAIN_BEGIN;
        }
        break;
    case BTL_SUBSTATE_STRATEGIES_TARGET_CANCEL:
        btl_submenu_strats_restore_choose();
        btl_main_menu_restore_submenu();
        gBattleSubState = BTL_SUBSTATE_STRATEGIES_REOPEN_MENU;
        break;
    case BTL_SUBSTATE_STRATEGIES_TARGET_CHOSEN:
        btl_submenu_strats_destroy();
        btl_main_menu_destroy();
        break;
    case BTL_SUBSTATE_STRATEGIES_SHOW_ERROR:
        if (btl_submenu_strats_update() != POPUP_RESULT_INVALID) {
            gBattleSubState = BTL_SUBSTATE_STRATEGIES_CHOOSING;
        }
        break;
    case BTL_SUBSTATE_CHANGE_PARTNER_BUILD_MENU:
        popupIndex = 0;
        for (i = 1; i < ARRAY_COUNT(PartnerIDFromMenuIndex); i++) {
            s32 partnerId = PartnerIDFromMenuIndex[i];
            if (playerData->partners[partnerId].enabled) {
                popupProps = &gPartnerPopupProperties[partnerId];
                popupMenu->ptrIcon[popupIndex] = PartnerHudScripts[partnerId].enabled;
                popupMenu->enabled[popupIndex] = true;
                popupMenu->userIndex[popupIndex] = partnerId;
                popupMenu->nameMsg[popupIndex] = popupProps->nameMsg;
                popupMenu->descMsg[popupIndex] = popupProps->battleDescMsg;
                popupMenu->value[popupIndex] = playerData->partners[partnerId].level;
                if (playerData->curPartner == partnerId) {
                    popupMenu->ptrIcon[popupIndex] = PartnerHudScripts[partnerId].disabled;
                    popupMenu->enabled[popupIndex] = false;
                }
                popupIndex++;
            }
        }
        if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER] < 0) {
            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER] = 0;
        }
        initialPos = MenuIndexFromPartnerID[playerData->curPartner] - 1;
        {
            CALL_EVENT(OnBattleMenuBuilt, BATTLE_MENU_PARTNER_LIST, ACTOR_PARTNER, -1, &popupIndex, &initialPos);
            if (popupIndex > ARRAY_COUNT(popupMenu->ptrIcon)) {
                popupIndex = ARRAY_COUNT(popupMenu->ptrIcon);
            } else if (popupIndex < 0) {
                popupIndex = 0;
            }
            if (initialPos < 0) {
                initialPos = 0;
            }
        }
        popupMenu->popupType = POPUP_MENU_SWITCH_PARTNER;
        popupMenu->numEntries = popupIndex;
        popupMenu->initialPos = initialPos;
        popupMenu->dipMode = 0;
        popupMenu->titleNumber = 0;
        create_battle_popup_menu(popupMenu);
        flush_popup_menu();
        gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_CHOOSING;
        break;
    case BTL_SUBSTATE_CHANGE_PARTNER_CHOOSING:
        switch (popupMenu->result) {
            case POPUP_RESULT_CHOOSING:
                // do nothing while player is choosing from popup menu
                break;
            case POPUP_RESULT_INVALID:
                gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_ERROR;
                break;
            case POPUP_RESULT_CANCEL:
                btl_submenu_strats_resume_choose();
                gBattleSubState = BTL_SUBSTATE_STRATEGIES_CHOOSING;
                btl_state_update_partner_menu();
                btl_state_update_partner_menu();
                break;
            default:
                battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_CHANGE_PARTNER_TARGET_CANCEL;
                battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_CHANGE_PARTNER_TARGET_CHOSEN;
                battleStatus->lastSelectedPartner = popupMenu->userIndex[popupMenu->result - 1];
                battleStatus->moveCategory = BTL_MENU_TYPE_CHANGE_PARTNER;
                battleStatus->selectedMoveID = MOVE_CHANGE_PARTNER;
                battleStatus->curTargetListFlags = TARGET_FLAG_2;
                battleStatus->moveArgument = battleStatus->lastSelectedPartner;
                battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_PARTNER] = popupMenu->result - 1;
                hide_popup_menu();
                btl_submenu_strats_hide();
                btl_main_menu_hide();
                gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_HANDOVER;
                break;
        }
        break;
    case BTL_SUBSTATE_CHANGE_PARTNER_HANDOVER:
        if ((battleStatus->curButtonsPressed & BUTTON_B) && popupMenu->result == POPUP_RESULT_CHOOSING) {
            show_popup_menu();
            btl_submenu_strats_restore_locked();
            btl_main_menu_restore_submenu();
            gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_REOPEN_MENU;
        } else {
            btl_submenu_strats_update();
            if (btl_main_menu_update() != 0) {
                gBattleSubState = battleStatus->acceptTargetMenuSubstate;
                btl_state_update_partner_menu();
                btl_set_state(BATTLE_STATE_CHANGE_PARTNER);
            }
        }
        break;
    case BTL_SUBSTATE_CHANGE_PARTNER_REOPEN_MENU:
        btl_submenu_strats_update();
        if (btl_main_menu_update() != 0) {
            gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_CHOOSING;
        }
        break;
    case BTL_SUBSTATE_CHANGE_PARTNER_TARGET_CANCEL:
        show_popup_menu();
        btl_submenu_strats_restore_locked();
        btl_main_menu_restore_submenu();
        gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_REOPEN_MENU;
        break;
    case BTL_SUBSTATE_CHANGE_PARTNER_TARGET_CHOSEN:
        destroy_popup_menu();
        btl_submenu_strats_destroy();
        btl_main_menu_destroy();
        break;
    case BTL_SUBSTATE_CHANGE_PARTNER_ERROR:
        set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_HIDE);
        set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_HIDE);
        if (popupMenu->result != POPUP_RESULT_INVALID) {
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_9);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_9);
            gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_CHOOSING;
        }
        break;
    }
}

void btl_state_draw_partner_menu(void) {
    switch (gBattleSubState) {
        case BTL_SUBSTATE_MAIN_BEGIN:
        case BTL_SUBSTATE_MAIN_CHOOSING:
        case BTL_SUBSTATE_MAIN_HANDOVER:
        case BTL_SUBSTATE_MAIN_REOPEN_MENU:
        case BTL_SUBSTATE_MAIN_TARGET_CANCEL:
        case BTL_SUBSTATE_ABILITIES_BUILD_MENU:
        case BTL_SUBSTATE_ABILITIES_CHOOSING:
        case BTL_SUBSTATE_ABILITIES_HANDOVER:
        case BTL_SUBSTATE_ABILITIES_REOPEN_MENU:
        case BTL_SUBSTATE_ABILITIES_TARGET_CANCEL:
        case BTL_SUBSTATE_UNKNOWN_1:
        case BTL_SUBSTATE_UNKNOWN_2:
        case BTL_SUBSTATE_UNKNOWN_3:
        case BTL_SUBSTATE_UNKNOWN_4:
        case BTL_SUBSTATE_UNKNOWN_5:
        case BTL_SUBSTATE_CHANGE_PARTNER_BUILD_MENU:
        case BTL_SUBSTATE_CHANGE_PARTNER_CHOOSING:
        case BTL_SUBSTATE_CHANGE_PARTNER_HANDOVER:
        case BTL_SUBSTATE_CHANGE_PARTNER_REOPEN_MENU:
        case BTL_SUBSTATE_CHANGE_PARTNER_TARGET_CANCEL:
        case BTL_SUBSTATE_ITEMS_BUILD_MENU:
        case BTL_SUBSTATE_ITEMS_CHOOSING:
        case BTL_SUBSTATE_ITEMS_HANDOVER:
        case BTL_SUBSTATE_ITEMS_REOPEN_MENU:
        case BTL_SUBSTATE_ITEMS_TARGET_CANCEL:
        case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_CHOOSING:
        case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_HANDOVER:
        case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_REOPEN_MENU:
        case BTL_SUBSTATE_UNUSED_CHANGE_PARTNER_TARGET_CANCEL:
        case BTL_SUBSTATE_FOCUS_CHOOSING:
        case BTL_SUBSTATE_FOCUS_HANDOVER:
        case BTL_SUBSTATE_FOCUS_REOPEN_MENU:
        case BTL_SUBSTATE_FOCUS_CANCELED:
        case BTL_SUBSTATE_FOCUS_SELECTED:
        case BTL_SUBSTATE_STRATEGIES_BUILD_MENU:
        case BTL_SUBSTATE_STRATEGIES_CHOOSING:
        case BTL_SUBSTATE_STRATEGIES_HANDOVER:
        case BTL_SUBSTATE_STRATEGIES_REOPEN_MENU:
        case BTL_SUBSTATE_STRATEGIES_TARGET_CANCEL:
        case BTL_SUBSTATE_STRATEGIES_TARGET_CHOSEN:
            btl_main_menu_draw();
            break;
    }
}
