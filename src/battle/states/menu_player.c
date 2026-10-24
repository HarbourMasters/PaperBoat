#include "states.h"
#include "inventory.h"
#include "battle/battle.h"
#include "battle/battle_menu.h"
#include "battle/action_cmd.h"

#include "sprite/player.h"

s32 get_player_anim_for_status(s32 animID);

enum {
    // BTL_SUBSTATE_INIT                                = 0,

    // Main menu
    BTL_SUBSTATE_MAIN_CHOOSING                          = 1,
    // selecting options from jump, hammer, or outermost items submenus
    BTL_SUBSTATE_ABILITIES_CHOOSING                     = 2,
    BTL_SUBSTATE_ABILITIES_HANDOVER                     = 3,
    BTL_SUBSTATE_ABILITIES_REOPEN_MENU                  = 4,
    BTL_SUBSTATE_ABILITIES_TARGET_CANCEL                = 5,
    BTL_SUBSTATE_ABILITIES_TARGET_CHOSEN                = 6,
    BTL_SUBSTATE_ABILITIES_SHOW_ERROR                   = 7,
    BTL_SUBSTATE_MAIN_SHOW_CANT_SWAP                    = 8,
    BTL_SUBSTATE_MAIN_AWAIT_CANT_SWAP                   = 9,
    // states for target selection when there is no submenu after main
    // this occurs when there are no additional options for Jump/Hammer apart from the base move
    BTL_SUBSTATE_NOSUBMENU_SHOW                         = 10,
    BTL_SUBSTATE_NOSUBMENU_HANDOVER                     = 11,
    BTL_SUBSTATE_NOSUBMENU_RETURN_MAIN                  = 12,
    BTL_SUBSTATE_NOSUBMENU_TARGET_CANCEL                = 13,
    BTL_SUBSTATE_NOSUBMENU_TARGET_CHOSEN                = 14,
    // Initial selection and use for Double/Triple dip
    BTL_SUBSTATE_DIPPING_BUILD_MENU                     = 20,
    BTL_SUBSTATE_DIPPING_CHOOSING                       = 21, // choosing double dip item
    BTL_SUBSTATE_DIPPING_HANDOVER                       = 22, // selecting target
    BTL_SUBSTATE_DIPPING_REOPEN_MENU                    = 23,
    BTL_SUBSTATE_DIPPING_TARGET_CANCEL                  = 24,
    BTL_SUBSTATE_DIPPING_TARGET_CHOSEN                  = 25,
    // Change Partner
    BTL_SUBSTATE_CHANGE_PARTNER_BUILD_MENU              = 30,
    BTL_SUBSTATE_CHANGE_PARTNER_CHOOSING                = 31,
    BTL_SUBSTATE_CHANGE_PARTNER_HANDOVER                = 32,
    BTL_SUBSTATE_CHANGE_PARTNER_REOPEN_MENU             = 33,
    BTL_SUBSTATE_CHANGE_PARTNER_TARGET_CANCEL           = 34,
    BTL_SUBSTATE_CHANGE_PARTNER_TARGET_CHOSEN           = 35,
    BTL_SUBSTATE_CHANGE_PARTNER_ERROR                   = 36,
    // Items
    BTL_SUBSTATE_ITEMS_BUILD_MENU                       = 40,
    BTL_SUBSTATE_ITEMS_CHOOSING                         = 41,
    BTL_SUBSTATE_ITEMS_HANDOVER                         = 42,
    BTL_SUBSTATE_ITEMS_REOPEN_MENU                      = 43,
    BTL_SUBSTATE_ITEMS_TARGET_CANCEL                    = 44,
    BTL_SUBSTATE_ITEMS_TARGET_CHOSEN                    = 45,
    // Star Spirits
    BTL_SUBSTATE_STAR_SPIRITS_BUILD_MENU                = 60,
    BTL_SUBSTATE_STAR_SPIRITS_CHOOSING                  = 61,
    BTL_SUBSTATE_STAR_SPIRITS_HANDOVER                  = 62,
    BTL_SUBSTATE_STAR_SPIRITS_REOPEN_MENU               = 63,
    BTL_SUBSTATE_STAR_SPIRITS_TARGET_CANCEL             = 64,
    BTL_SUBSTATE_STAR_SPIRITS_TARGET_CHOSEN             = 65,
    BTL_SUBSTATE_STAR_SPIRITS_SHOW_ERROR                = 66,
    // additional item use from Double/Triple dip
    BTL_SUBSTATE_NEXT_DIP_BUILD_MENU                    = BTL_SUBSTATE_PLAYER_CONTINUE_DIP,
    BTL_SUBSTATE_NEXT_DIP_CHOOSING                      = 71,
    BTL_SUBSTATE_NEXT_DIP_HANDOVER                      = 72,
    BTL_SUBSTATE_NEXT_DIP_REOPEN_MENU                   = 73,
    BTL_SUBSTATE_NEXT_DIP_TARGET_CANCEL                 = 74,
    BTL_SUBSTATE_NEXT_DIP_TARGET_CHOSEN                 = 75,
    // Berserker
    BTL_SUBSTATE_BERSERKER_CHOOSE                       = 100,
    // Strategies
    BTL_SUBSTATE_STRATEGIES_BUILD_MENU                  = 200,
    BTL_SUBSTATE_STRATEGIES_CHOOSING                    = 201,
    BTL_SUBSTATE_STRATEGIES_HANDOVER                    = 202,
    BTL_SUBSTATE_STRATEGIES_REOPEN_MENU                 = 203,
    BTL_SUBSTATE_STRATEGIES_TARGET_CANCEL               = 204,
    BTL_SUBSTATE_STRATEGIES_TARGET_CHOSEN               = 205,
    BTL_SUBSTATE_STRATEGIES_SHOW_ERROR                  = 207,
    // initialize
    BTL_SUBSTATE_PERFORM_SWAP                           = 300,
    BTL_SUBSTATE_CREATE_MAIN_MENU                       = 302,
};

s32 BattleMenu_CategoryForSubmenu[] = {
    [BTL_MENU_TYPE_JUMP]            MOVE_TYPE_JUMP,
    [BTL_MENU_TYPE_SMASH]           MOVE_TYPE_HAMMER,
    [BTL_MENU_TYPE_ITEMS]           MOVE_TYPE_ITEMS,
    [BTL_MENU_TYPE_RUN_AWAY]        MOVE_TYPE_6,
    [BTL_MENU_TYPE_DEFEND]          MOVE_TYPE_3,
    [BTL_MENU_TYPE_CHANGE_PARTNER]  MOVE_TYPE_SWITCH,
    [BTL_MENU_TYPE_ABILITY]         0x1A,
    [BTL_MENU_TYPE_STRATEGIES]      MOVE_TYPE_3,
    [BTL_MENU_TYPE_STAR_POWERS]     MOVE_ITEMS, // ???
    [BTL_MENU_TYPE_DO_NOTHING]      0x39,
    [BTL_MENU_TYPE_ACT_LATER]       0x31,
    [BTL_MENU_TYPE_PARTNER_FOCUS]   0x37,
};

IconHudScriptPair BootsHudScripts[] = {
    { &HES_MenuBoots1Disabled, &HES_MenuBoots1Disabled },
    { &HES_MenuBoots1, &HES_MenuBoots1Disabled },
    { &HES_MenuBoots2, &HES_MenuBoots2Disabled },
    { &HES_MenuBoots3, &HES_MenuBoots3Disabled },
};

IconHudScriptPair HammerHudScripts[] = {
    { &HES_MenuHammer1Disabled, &HES_MenuHammer1Disabled },
    { &HES_MenuHammer1, &HES_MenuHammer1Disabled },
    { &HES_MenuHammer2, &HES_MenuHammer2Disabled },
    { &HES_MenuHammer3, &HES_MenuHammer3Disabled  },
};

void btl_init_menu_boots(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    Actor* player = battleStatus->playerActor;
    MoveData* move;
    s32 i;
    s32 moveCount;
    s32 hasAnyBadgeMoves;
    s32 fpCost;

    // If you don't have boots equipped, disable this menu
    if (playerData->bootsLevel == GEAR_RANK_NONE) {
        battleStatus->menuStatus[1] = 0;
        return;
    }

    for (i = 0; i < ARRAY_COUNT(battleStatus->submenuMoves); i++) {
        battleStatus->submenuMoves[i] = MOVE_NONE;
    }

    // Standard jump move
    moveCount = 1;
    battleStatus->submenuMoves[0] = MOVE_JUMP1 + playerData->bootsLevel;
    battleStatus->submenuIcons[0] = ITEM_PARTNER_ATTACK;

    // Jump badges
    for (i = 0; i < ARRAY_COUNT(playerData->equippedBadges); i++) {
        s16 badge = playerData->equippedBadges[i];

        if (badge != ITEM_NONE) {
            s32 badgeID = badge;
            CALL_EVENT(OnBattleBadgeMenuEntry, BTL_MENU_TYPE_JUMP, moveCount, &badgeID);
            badge = badgeID;
        }
        if (badge != ITEM_NONE) {
            MoveData* moveTable = gMoveTable;
            u8 moveID = gItemTable[badge].moveID;

            move = &moveTable[moveID];
            if (move->category == MOVE_TYPE_JUMP) {
                battleStatus->submenuMoves[moveCount] = moveID;
                battleStatus->submenuIcons[moveCount] = badge;
                moveCount++;
            }
        }
    }

    battleStatus->submenuMoveCount = moveCount;

    hasAnyBadgeMoves = false;
    for (i = 0; i < battleStatus->submenuMoveCount; i++) {
        move = &gMoveTable[battleStatus->submenuMoves[i]];

        // Calculate FP cost
        fpCost = move->costFP;
        if (fpCost != 0) {
            fpCost -= player_team_is_ability_active(player, ABILITY_FLOWER_SAVER);
            fpCost -= player_team_is_ability_active(player, ABILITY_FLOWER_FANATIC) * 2;
            if (fpCost < 1) {
                fpCost = 1;
            }
        }
        {
            CALL_EVENT(OnMoveFPCost, player, battleStatus->submenuMoves[i], i, MOVE_FP_ENABLE, &fpCost);
        }

        // See if there are any targets for this move
        battleStatus->moveCategory = BTL_MENU_TYPE_JUMP;
        battleStatus->moveArgument = playerData->bootsLevel;
        battleStatus->curTargetListFlags = move->flags; // Controls target filters
        create_current_pos_target_list(player);

        // If there are targets, enable the move
        if (player->targetListLength != 0) {
            hasAnyBadgeMoves = true;
            battleStatus->submenuStatus[i] = BATTLE_SUBMENU_STATUS_ENABLED;
        }

        // If you don't have enough FP, disable the move
        if (playerData->curFP < fpCost) {
            battleStatus->submenuStatus[i] = BATTLE_SUBMENU_STATUS_NOT_ENOUGH_FP;
        }

        // If there are no targets available, disable the move
        if (player->targetListLength == 0) {
            battleStatus->submenuStatus[i] = BATTLE_SUBMENU_STATUS_NO_TARGETS_2;
        }
        if (gBattleStatus.flags2 & BS_FLAGS2_NO_TARGET_AVAILABLE) {
            battleStatus->submenuStatus[moveCount] = BATTLE_SUBMENU_STATUS_NO_TARGETS;
        }
    }

    if (!hasAnyBadgeMoves) {
        // Only the standard jump is available - no badge moves.
        // Selecting this submenu should immediately pick the standard jump move
        battleStatus->menuStatus[1] = -1;
    } else {
        // Enable this submenu
        battleStatus->menuStatus[1] = 1;
    }
}

void btl_init_menu_hammer(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    Actor* player = battleStatus->playerActor;
    MoveData* move;
    s32 i;
    s32 moveCount;
    s32 hasAnyBadgeMoves;
    s32 fpCost;

    // If you don't have a hammer, disable this menu
    if (playerData->hammerLevel == -1) {
        battleStatus->menuStatus[2] = 0;
        return;
    }

    for (i = 0; i < ARRAY_COUNT(battleStatus->submenuMoves); i++) {
        battleStatus->submenuMoves[i] = MOVE_NONE;
    }

    // Standard hammer move
    moveCount = 1;
    battleStatus->submenuMoves[0] = MOVE_HAMMER1 + playerData->hammerLevel;
    battleStatus->submenuIcons[0] = ITEM_PARTNER_ATTACK;

    // Hammer badges
    for (i = 0; i < ARRAY_COUNT(playerData->equippedBadges); i++) {
        s16 badge = playerData->equippedBadges[i];
        if (badge != MOVE_NONE) {
            s32 badgeID = badge;
            CALL_EVENT(OnBattleBadgeMenuEntry, BTL_MENU_TYPE_SMASH, moveCount, &badgeID);
            badge = badgeID;
        }
        if (badge != MOVE_NONE) {
            MoveData* moveTable = gMoveTable;
            u8 moveID = gItemTable[badge].moveID;
            move = &moveTable[moveID];
            if (move->category == MOVE_TYPE_HAMMER) {
                battleStatus->submenuMoves[moveCount] = moveID;
                battleStatus->submenuIcons[moveCount] = badge;
                moveCount++;
            }
        }
    }

    battleStatus->submenuMoveCount = moveCount;

    hasAnyBadgeMoves = false;
    for (i = 0; i < battleStatus->submenuMoveCount; i++) {
        move = &gMoveTable[battleStatus->submenuMoves[i]];

        // Calculate FP cost
        fpCost = move->costFP;
        if (fpCost != 0) {
            fpCost -= player_team_is_ability_active(player, ABILITY_FLOWER_SAVER);
            fpCost -= player_team_is_ability_active(player, ABILITY_FLOWER_FANATIC) * 2;
            if (fpCost < 1) {
                fpCost = 1;
            }
        }
        {
            CALL_EVENT(OnMoveFPCost, player, battleStatus->submenuMoves[i], i, MOVE_FP_ENABLE, &fpCost);
        }

        // See if there are any targets for this move
        battleStatus->moveCategory = BTL_MENU_TYPE_SMASH;
        battleStatus->moveArgument = playerData->hammerLevel;
        battleStatus->curTargetListFlags = move->flags;
        create_current_pos_target_list(player);

        // If there are targets, enable the move
        if (player->targetListLength != 0) {
            hasAnyBadgeMoves = true;
            battleStatus->submenuStatus[i] = 1;
        }

        // If you don't have enough FP, disable the move
        if (playerData->curFP < fpCost) {
            battleStatus->submenuStatus[i] = 0;
        }

        // If there are no targets available, disable the move
        if (player->targetListLength == 0) {
            battleStatus->submenuStatus[i] = BATTLE_SUBMENU_STATUS_NO_TARGETS_2;
        }
        if (gBattleStatus.flags2 & BS_FLAGS2_NO_TARGET_AVAILABLE) {
            battleStatus->submenuStatus[moveCount] = BATTLE_SUBMENU_STATUS_NO_TARGETS;
        }
    }

    if (!hasAnyBadgeMoves) {
        // Only the standard hammer is available - no badge moves.
        // Selecting this submenu should immediately pick the standard hammer move
        battleStatus->menuStatus[2] = -1;
    } else {
        // Enable this submenu
        battleStatus->menuStatus[2] = 1;
    }
}

void btl_state_update_player_menu(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    Actor* playerActor = battleStatus->playerActor;
    Actor* partnerActor = battleStatus->partnerActor;
    PopupMenu* popup = &BattlePopupMenu;
    MoveData* moveData;
    s32 entryIdx, initialPos;
    s32 i;
    s32 submenuResult;
    s32 jumpTargetCount, hammerTargetCount, jumpChance;
    ItemData* itemData;
    s32 starBeamLevel;
    s32 currentSubmenu;
    s32 currentSubmenu2;
    IconHudScriptPair* hudScriptPair;
    PartnerPopupProperties* prop;
    s32 invCapacity;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            {
                CALL_EVENT(OnBattleMenuOpen, ACTOR_PLAYER);
            }
            battleStatus->moveCategory = BTL_MENU_TYPE_INVALID;
            battleStatus->selectedMoveID = 0;
            battleStatus->curAttackElement = 0;
            if (!btl_player_can_act()) {
                btl_set_state(BATTLE_STATE_END_PLAYER_TURN);
                return;
            }
            btl_cam_use_preset(BTL_CAM_DEFAULT);
            btl_cam_move(10);
            if (!(battleStatus->flags1 & BS_FLAGS1_PLAYER_IN_BACK)) {
                gBattleSubState = BTL_SUBSTATE_CREATE_MAIN_MENU;
            } else {
                s32 inFront = true;
                CALL_EVENT(OnTurnOrder, TURN_ORDER_PLAYER_IN_FRONT, &inFront);
                if (!inFront) {
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
            break;
        case BTL_SUBSTATE_PERFORM_SWAP:
            if (partnerActor->state.moveTime != 0) {
                partnerActor->curPos.x += (partnerActor->state.goalPos.x - partnerActor->curPos.x) / partnerActor->state.moveTime;
                partnerActor->curPos.z += (partnerActor->state.goalPos.z - partnerActor->curPos.z) / partnerActor->state.moveTime;
                playerActor->curPos.x += (partnerActor->state.curPos.x - playerActor->curPos.x) / partnerActor->state.moveTime;
                playerActor->curPos.z += (partnerActor->state.curPos.z - playerActor->curPos.z) / partnerActor->state.moveTime;
            }
            partnerActor->curPos.z -= sin_rad(DEG_TO_RAD(partnerActor->state.angle)) * 16.0f;
            partnerActor->yaw = clamp_angle(-partnerActor->state.angle);
            playerActor->curPos.z += sin_rad(DEG_TO_RAD(partnerActor->state.angle)) * 16.0f;
            playerActor->yaw = clamp_angle(-partnerActor->state.angle);
            partnerActor->state.angle += 90.0f;
            if (partnerActor->state.moveTime != 0) {
                partnerActor->state.moveTime--;
            } else {
                partnerActor->curPos.x = partnerActor->state.goalPos.x;
                partnerActor->curPos.z = partnerActor->state.goalPos.z;
                playerActor->curPos.x = partnerActor->state.curPos.x;
                playerActor->curPos.z = partnerActor->state.curPos.z;
                partnerActor->homePos.x = partnerActor->curPos.x;
                partnerActor->homePos.z = partnerActor->curPos.z;
                playerActor->homePos.x = playerActor->curPos.x;
                playerActor->homePos.z = playerActor->curPos.z;
                gBattleSubState = BTL_SUBSTATE_CREATE_MAIN_MENU;
                battleStatus->flags1 &= ~BS_FLAGS1_PLAYER_IN_BACK;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_CREATE_MAIN_MENU:
            gBattleStatus.flags1 |= BS_FLAGS1_MENU_OPEN;
            playerActor->flags &= ~ACTOR_FLAG_USING_IDLE_ANIM;
            playerActor->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
            if (partnerActor != nullptr) {
                partnerActor->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
                partnerActor->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
            }
            btl_check_can_change_partner();
            btl_init_menu_items();
            btl_init_menu_boots();
            btl_init_menu_hammer();
            if (player_team_is_ability_active(playerActor, ABILITY_BERSERKER)) {
                gBattleSubState = BTL_SUBSTATE_BERSERKER_CHOOSE;
                break;
            }

            entryIdx = 0;
            initialPos = 2;
            if (battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_MAIN] < 0) {
                battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_MAIN] = 0;
            }

            // strategies menu category
            WheelOptionSubmenu[entryIdx] = BTL_MENU_TYPE_STRATEGIES;
            WheelOptionEnabled[entryIdx] = true;
            WheelOptionHudScript[entryIdx] = StrategiesHudScripts.enabled;
            WheelOptionName[entryIdx] = CenteredBattleMessages[BTL_MENU_TYPE_STRATEGIES];
            if (battleStatus->actionCommandMode == AC_MODE_TUTORIAL || gBattleStatus.flags1 & BS_FLAGS1_TUTORIAL_BATTLE) {
                WheelOptionName[entryIdx] = MSG_Menus_EndTraining_Centered;
            }
            WheelOptionError[entryIdx] = 0;
            if (!(battleStatus->enabledMenusFlags & BTL_MENU_ENABLED_STRATEGIES)) {
                WheelOptionHudScript[entryIdx] = StrategiesHudScripts.disabled;
                WheelOptionEnabled[entryIdx] = false;
                WheelOptionError[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
            }
            if (battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_MAIN] == BTL_MENU_TYPE_STRATEGIES) {
                initialPos = entryIdx;
            }
            entryIdx++;

            // items menu category
            if (battleStatus->menuStatus[0] >= 0) {
                WheelOptionHudScript[entryIdx] = ItemsHudScripts.enabled;
                WheelOptionSubmenu[entryIdx] = BTL_MENU_TYPE_ITEMS;
                WheelOptionEnabled[entryIdx] = true;
                WheelOptionName[entryIdx] = CenteredBattleMessages[BTL_MENU_TYPE_ITEMS];

                if(battleStatus->menuStatus[0] == 0) {
                    WheelOptionHudScript[entryIdx] = ItemsHudScripts.disabled;
                    WheelOptionEnabled[entryIdx] = false;
                    WheelOptionError[entryIdx] = BTL_MSG_NO_ITEM_TARGET;
                }

                if (!(battleStatus->enabledMenusFlags & BTL_MENU_ENABLED_ITEMS)) {
                    WheelOptionHudScript[entryIdx] = ItemsHudScripts.disabled;
                    WheelOptionEnabled[entryIdx] = false;
                    WheelOptionError[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
                }

                if (battleStatus->itemLossTurns >= 0) {
                    WheelOptionHudScript[entryIdx] = ItemsHudScripts.disabled;
                    WheelOptionEnabled[entryIdx] = false;
                    WheelOptionError[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
                }

                if (battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_MAIN] == BTL_MENU_TYPE_ITEMS) {
                    initialPos = entryIdx;
                }

                entryIdx++;
            }

            // jump menu category
            WheelOptionHudScript[entryIdx] = BootsHudScripts[playerData->bootsLevel + 1].enabled;
            WheelOptionSubmenu[entryIdx] = BTL_MENU_TYPE_JUMP;
            WheelOptionEnabled[entryIdx] = true;
            WheelOptionName[entryIdx] = CenteredBattleMessages[BTL_MENU_TYPE_JUMP];

            if (battleStatus->menuStatus[1] <= 0) {
                WheelOptionHudScript[entryIdx] = BootsHudScripts[0].enabled;
                WheelOptionEnabled[entryIdx] = false;
                WheelOptionError[entryIdx] = BTL_MSG_NO_JUMP_TARGET;
            }
            if (!(battleStatus->enabledMenusFlags & BTL_MENU_ENABLED_JUMP)) {
                WheelOptionHudScript[entryIdx] = BootsHudScripts[0].disabled;
                WheelOptionEnabled[entryIdx] = false;
                WheelOptionError[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
            }
            if (battleStatus->jumpLossTurns >= 0) {
                WheelOptionHudScript[entryIdx] = BootsHudScripts[0].disabled;
                WheelOptionEnabled[entryIdx] = false;
                WheelOptionError[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
            }
            if (battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_MAIN] == BTL_MENU_TYPE_JUMP) {
                initialPos = entryIdx;
            }
            entryIdx++;

            // hammer menu category
            if (playerData->hammerLevel >= 0) {
                WheelOptionHudScript[entryIdx] = HammerHudScripts[playerData->hammerLevel + 1].enabled;
                WheelOptionSubmenu[entryIdx] = BTL_MENU_TYPE_SMASH;
                WheelOptionEnabled[entryIdx] = true;
                WheelOptionName[entryIdx] = CenteredBattleMessages[BTL_MENU_TYPE_SMASH];
                if (battleStatus->menuStatus[2] <= 0) {
                    WheelOptionHudScript[entryIdx] = HammerHudScripts[0].enabled;
                    WheelOptionEnabled[entryIdx] = false;
                    WheelOptionError[entryIdx] = BTL_MSG_NO_HAMMER_TARGET;
                }
                if (!(battleStatus->enabledMenusFlags & BTL_MENU_ENABLED_SMASH)) {
                    WheelOptionHudScript[entryIdx] = HammerHudScripts[0].disabled;
                    WheelOptionEnabled[entryIdx] = false;
                    WheelOptionError[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
                }
                if (battleStatus->hammerLossTurns >= 0) {
                    WheelOptionHudScript[entryIdx] = HammerHudScripts[0].disabled;
                    WheelOptionEnabled[entryIdx] = false;
                    WheelOptionError[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
                }
                if (battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_MAIN] == BTL_MENU_TYPE_SMASH) {
                    initialPos = entryIdx;
                }
                entryIdx++;
            }

            // star powers menu category
            if (playerData->maxStarPower != 0) {
                WheelOptionHudScript[entryIdx] = StarPowersHudScripts.enabled;
                WheelOptionSubmenu[entryIdx] = BTL_MENU_TYPE_STAR_POWERS;
                WheelOptionEnabled[entryIdx] = true;
                WheelOptionName[entryIdx] = CenteredBattleMessages[BTL_MENU_TYPE_STAR_POWERS];
                WheelOptionError[entryIdx] = 0;
                if (!(battleStatus->enabledMenusFlags & BTL_MENU_ENABLED_STAR_POWERS)) {
                    WheelOptionHudScript[entryIdx] = StarPowersHudScripts.disabled;
                    WheelOptionEnabled[entryIdx] = false;
                    WheelOptionError[entryIdx] = BTL_MSG_CANT_SELECT_NOW;
                }
                if (battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_MAIN] == BTL_MENU_TYPE_STAR_POWERS) {
                    initialPos = entryIdx;
                }
                entryIdx++;
            }

            {
                CALL_EVENT(OnBattleMenuBuilt, BATTLE_MENU_WHEEL, ACTOR_PLAYER, -1, &entryIdx, &initialPos);
                if (entryIdx > ARRAY_COUNT(WheelOptionSubmenu)) {
                    entryIdx = ARRAY_COUNT(WheelOptionSubmenu);
                }
            }
            WheelOptionCount = entryIdx;
            BattleMenu_PrevSelected = initialPos;
            BattleMenu_WheelBase = 2 - initialPos;
            if (btl_partner_can_act()) {
                BattleMenu_ShowSwapIcons = true;
            } else {
                BattleMenu_ShowSwapIcons = false;
            }
            btl_main_menu_init();
            BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
            BattleMenu_SwapDelay = 0;
            gBattleSubState = BTL_SUBSTATE_MAIN_CHOOSING;
            break;
        case BTL_SUBSTATE_MAIN_CHOOSING:
            if (battleStatus->hustleTurns != 0) {
                set_actor_anim(ACTOR_PLAYER, 0, ANIM_Mario1_ThinkingRun);
            } else {
                set_actor_anim(ACTOR_PLAYER, 0, get_player_anim_for_status(STATUS_KEY_THINKING));
            }
            submenuResult = btl_main_menu_update();
            if (BattleMenu_SwapDelay != 0) {
                BattleMenu_SwapDelay--;
            } else if (!(gBattleStatus.flags1 & BS_FLAGS1_TUTORIAL_BATTLE) && (gGameStatusPtr->pressedButtons[0] & BUTTON_Z)) {
                s32 swapAllowed = false;
                if (btl_partner_can_act()) {
                    swapAllowed = battleStatus->hustleTurns != 1;
                    CALL_EVENT(OnTurnOrder, TURN_ORDER_CAN_SWAP, &swapAllowed);
                }
                if (swapAllowed) {
                    sfx_play_sound(SOUND_PARTNER_SWAP_BATTLE_POS);
                    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_MAIN] = WheelOptionSubmenu[BattleMenu_CurPos + BattleMenu_HomePos];
                    btl_main_menu_destroy();
                    btl_set_state(BATTLE_STATE_SWITCH_TO_PARTNER);
                } else if (partnerActor != nullptr && !(partnerActor->flags & BS_FLAGS1_YIELD_TURN) && battleStatus->hustleTurns != 1) {
                    sfx_play_sound(SOUND_MENU_ERROR);
                    gBattleSubState = BTL_SUBSTATE_MAIN_SHOW_CANT_SWAP;
                }
                break;
            }

            if (BattleMenu_ChooseDelay != 0) {
                BattleMenu_ChooseDelay--;
                break;
            }

            if (submenuResult == 0) {
                break;
            }

            set_actor_anim(ACTOR_PLAYER, 0, ANIM_Mario1_Walk);
            battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_MAIN] = battleStatus->curSubmenu = WheelOptionSubmenu[submenuResult - 1];
            {
                CALL_EVENT(OnBattleMenuSelect, BATTLE_MENU_WHEEL, ACTOR_PLAYER, submenuResult - 1);
            }
            for (i = 0; i < ARRAY_COUNT(battleStatus->submenuMoves); i++) {
                battleStatus->submenuMoves[i] = MOVE_NONE;
                battleStatus->submenuIcons[i] = ITEM_NONE;
                battleStatus->submenuStatus[i] = 0;
            }

            switch (battleStatus->curSubmenu) {
                case BTL_MENU_TYPE_ITEMS:
                    battleStatus->submenuMoves[0] = MOVE_ITEMS;
                    battleStatus->submenuIcons[0] = ITEM_PARTNER_ATTACK;
                    battleStatus->submenuStatus[0] = 1;
                    invCapacity = get_consumables_capacity();
                    for (i = 0; i < invCapacity; i++) {
                        if (playerData->invItems[i] == ITEM_NONE) {
                            continue;
                        }
                        itemData = &gItemTable[playerData->invItems[i]];

                        battleStatus->moveCategory = BTL_MENU_TYPE_ITEMS;
                        battleStatus->moveArgument = playerData->invItems[i];
                        battleStatus->curTargetListFlags = itemData->targetFlags;
                        create_current_pos_target_list(playerActor);
                    }
                    entryIdx = 1;
                    for (i = 0; i < ARRAY_COUNT(playerData->equippedBadges); i++) {
                        s32 badgeID = playerData->equippedBadges[i];
                        if (badgeID != 0) {
                            CALL_EVENT(OnBattleBadgeMenuEntry, BTL_MENU_TYPE_ITEMS, entryIdx, &badgeID);
                        }
                        if (badgeID != 0) {
                            s32 moveID = gItemTable[badgeID].moveID;
                            moveData = &gMoveTable[moveID];
                            if (moveData->category == BattleMenu_CategoryForSubmenu[battleStatus->curSubmenu]) {
                                s32 cost = moveData->costFP;
                                battleStatus->submenuMoves[entryIdx] = moveID;
                                battleStatus->submenuIcons[entryIdx] = badgeID;
                                battleStatus->submenuStatus[entryIdx] = 1;

                                cost -= player_team_is_ability_active(playerActor, ABILITY_FLOWER_SAVER);
                                cost -= 2 * player_team_is_ability_active(playerActor, ABILITY_FLOWER_FANATIC);

                                {
                                    CALL_EVENT(OnMoveFPCost, playerActor, moveID, entryIdx, MOVE_FP_ENABLE, &cost);
                                }
                                if (playerData->curFP < cost) {
                                    battleStatus->submenuStatus[entryIdx] = 0;
                                }
                                entryIdx++;
                            }
                        }
                    }
                    battleStatus->submenuMoveCount = entryIdx;
                    if (entryIdx == 1) {
                        battleStatus->submenuMoveCount = 0;
                    }
                    break;
                case BTL_MENU_TYPE_SMASH:
                    btl_init_menu_hammer();
                    if (battleStatus->submenuMoveCount == 1) {
                        battleStatus->submenuMoveCount = 0;
                    }
                    if (battleStatus->actionCommandMode == AC_MODE_TUTORIAL) {
                        battleStatus->submenuMoveCount = 0;
                    }
                    break;
                case BTL_MENU_TYPE_JUMP:
                    btl_init_menu_boots();
                    if (battleStatus->submenuMoveCount == 1) {
                        battleStatus->submenuMoveCount = 0;
                    }
                    if (battleStatus->actionCommandMode == AC_MODE_TUTORIAL) {
                        battleStatus->submenuMoveCount = 0;
                    }
                    break;
                case BTL_MENU_TYPE_STAR_POWERS:
                    battleStatus->submenuMoves[0] = MOVE_FOCUS;
                    battleStatus->submenuIcons[0] = ITEM_PARTNER_ATTACK;
                    battleStatus->submenuStatus[0] = 1;
                    entryIdx = 1;
                    initialPos = 8;
                    for (i = 0; i < playerData->maxStarPower; i++) {
                        moveData = &gMoveTable[MOVE_REFRESH + i];
                        battleStatus->submenuMoves[entryIdx] = MOVE_REFRESH + i;
                        battleStatus->submenuIcons[entryIdx] = ITEM_NONE;
                        battleStatus->moveCategory = BTL_MENU_TYPE_STAR_POWERS;
                        battleStatus->moveArgument = MOVE_REFRESH + i;
                        battleStatus->curTargetListFlags = moveData->flags;
                        create_current_pos_target_list(playerActor);
                        battleStatus->submenuStatus[entryIdx] = 1;
                        if (playerActor->targetListLength == 0) {
                            battleStatus->submenuStatus[entryIdx] = -2;
                        }
                        if (playerData->starPower / SP_PER_BAR < moveData->costFP) {
                            battleStatus->submenuStatus[entryIdx] = 0;
                        }
                        if (gBattleStatus.flags2 & BS_FLAGS2_NO_TARGET_AVAILABLE) {
                            battleStatus->submenuStatus[entryIdx] = -1;
                        }
                        entryIdx++;
                    }
                    starBeamLevel = playerData->starBeamLevel;
                    if (starBeamLevel == 1) {
                        moveData = &gMoveTable[MOVE_STAR_BEAM];
                        battleStatus->submenuMoves[entryIdx] = MOVE_STAR_BEAM;
                        battleStatus->submenuIcons[entryIdx] = 0;
                        battleStatus->moveCategory = BTL_MENU_TYPE_STAR_POWERS;
                        battleStatus->moveArgument = MOVE_REFRESH + i;
                        battleStatus->curTargetListFlags = moveData->flags;
                        create_current_pos_target_list(playerActor);
                        battleStatus->submenuStatus[entryIdx] = starBeamLevel;
                        if (playerActor->targetListLength == 0) {
                            battleStatus->submenuStatus[entryIdx] = -2;
                        }
                        if (playerData->starPower / SP_PER_BAR < moveData->costFP) {
                            battleStatus->submenuStatus[entryIdx] = 0;
                        }
                        if (gBattleStatus.flags2 & BS_FLAGS2_NO_TARGET_AVAILABLE) {
                            battleStatus->submenuStatus[entryIdx] = -1;
                        }
                        entryIdx++;
                    }
                    if (playerData->starBeamLevel == 2) {
                        moveData = &gMoveTable[MOVE_PEACH_BEAM];
                        battleStatus->submenuMoves[entryIdx] = MOVE_PEACH_BEAM;
                        battleStatus->submenuIcons[entryIdx] = ITEM_NONE;
                        battleStatus->moveCategory = BTL_MENU_TYPE_STAR_POWERS;
                        battleStatus->moveArgument = MOVE_REFRESH + i;
                        battleStatus->curTargetListFlags = moveData->flags;
                        create_current_pos_target_list(playerActor);
                        battleStatus->submenuStatus[entryIdx] = 1;
                        if (playerActor->targetListLength == 0) {
                            battleStatus->submenuStatus[entryIdx] = -2;
                        }
                        if (playerData->starPower / SP_PER_BAR < moveData->costFP) {
                            battleStatus->submenuStatus[entryIdx] = 0;
                        }
                        if (gBattleStatus.flags2 & BS_FLAGS2_NO_TARGET_AVAILABLE) {
                            battleStatus->submenuStatus[entryIdx] = -1;
                        }
                        entryIdx++;
                    }
                    battleStatus->submenuMoveCount = entryIdx;
                    break;
            }

            currentSubmenu = battleStatus->curSubmenu;

            if (currentSubmenu == BTL_MENU_TYPE_STAR_POWERS) {
                gBattleSubState = BTL_SUBSTATE_STAR_SPIRITS_BUILD_MENU;
                btl_state_update_player_menu();
                btl_state_update_player_menu();
                break;
            }

            if (currentSubmenu == BTL_MENU_TYPE_STRATEGIES) {
                if (battleStatus->actionCommandMode != AC_MODE_TUTORIAL && !(gBattleStatus.flags1 & BS_FLAGS1_TUTORIAL_BATTLE)) {
                    gBattleSubState = BTL_SUBSTATE_STRATEGIES_BUILD_MENU;
                    btl_state_update_player_menu();
                    btl_state_update_player_menu();
                } else {
                    btl_main_menu_destroy();
                    battleStatus->moveCategory = currentSubmenu;
                    battleStatus->moveArgument = 0;
                    battleStatus->selectedMoveID = 0;
                    btl_set_state(BATTLE_STATE_PLAYER_MOVE);
                }
                break;
            }

            // handle menus without multiple options (skipping submenu)
            if (battleStatus->submenuMoveCount == 0) {
                if (currentSubmenu != BTL_MENU_TYPE_ITEMS) {
                    gBattleSubState = BTL_SUBSTATE_NOSUBMENU_SHOW;
                } else {
                    gBattleSubState = BTL_SUBSTATE_ITEMS_BUILD_MENU;
                    btl_state_update_player_menu();
                    btl_state_update_player_menu();
                }
                break;
            }

            initialPos = 0;
            if (currentSubmenu == BTL_MENU_TYPE_JUMP) {
                if (battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_JUMP] < 0) {
                    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_JUMP] = 0;
                }
                initialPos = battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_JUMP];
            }
            if (battleStatus->curSubmenu == BTL_MENU_TYPE_SMASH) {
                if (battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_SMASH] < 0) {
                    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_SMASH] = 0;
                }
                initialPos = battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_SMASH];
            }
            if (battleStatus->curSubmenu == BTL_MENU_TYPE_ITEMS) {
                if (battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_ITEMS] < 0) {
                    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_ITEMS] = 0;
                }
                initialPos = battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_ITEMS];
            }

            for (i = 0; i < battleStatus->submenuMoveCount; i++) {
                moveData = &gMoveTable[battleStatus->submenuMoves[i]];
                itemData = &gItemTable[battleStatus->submenuIcons[i]];
                hudScriptPair = &gItemHudScripts[itemData->hudElemID];

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
                if (battleStatus->submenuStatus[i] == -3) {
                    battleStatus->submenuStatus[i] = 0;
                    MovesOptionError[i] = BTL_MSG_CANT_SELECT_NOW_ALT;
                }
                MovesOptionHudScripts[i] = hudScriptPair->enabled;
                if (battleStatus->submenuStatus[i] == 0) {
                    MovesOptionHudScripts[i] = hudScriptPair->disabled;
                }

                MovesOptionDisplayCosts[i] = moveData->costFP;
                MovesOptionBPCosts[i] = moveData->costBP;
                MovesOptionSortPriority[i] = 0;
                MovesOptionDiscounts[i] = 0;
                MovesOptionDiscountColors[i] = 0;

                if (player_team_is_ability_active(playerActor, ABILITY_FLOWER_SAVER)) {
                    MovesOptionDiscounts[i] += player_team_is_ability_active(playerActor, ABILITY_FLOWER_SAVER);
                    MovesOptionDiscountColors[i] = 1;
                }
                if (player_team_is_ability_active(playerActor, ABILITY_FLOWER_FANATIC)) {
                    MovesOptionDiscounts[i] += 2 * player_team_is_ability_active(playerActor, ABILITY_FLOWER_FANATIC);
                    MovesOptionDiscountColors[i] = 2;
                }
                {
                    CALL_EVENT(OnMoveCostDisplay, playerActor, battleStatus->submenuMoves[i], i, &MovesOptionDisplayCosts[i],
                               &MovesOptionDiscounts[i], &MovesOptionDiscountColors[i]);
                }

                MovesOptionIndices[i] = i;
                MovesOptionEnabled[i] = battleStatus->submenuStatus[i];
                MovesOptionNames[i] = moveData->nameMsg;
                MovesOptionDesc[i] = moveData->shortDescMsg;

            }
            UsingSpiritsSubmenu = false;
            MovesOptionCount = battleStatus->submenuMoveCount;
            {
                CALL_EVENT(OnBattleMenuBuilt, BATTLE_MENU_MOVES, ACTOR_PLAYER, battleStatus->curSubmenu, &MovesOptionCount, &initialPos);
                if (MovesOptionCount > ARRAY_COUNT(MovesOptionIndices)) {
                    MovesOptionCount = ARRAY_COUNT(MovesOptionIndices);
                }
            }
            MovesPrevSelected = initialPos;
            btl_submenu_moves_init();
            gBattleSubState = BTL_SUBSTATE_ABILITIES_CHOOSING;
            break;
        case BTL_SUBSTATE_ABILITIES_CHOOSING:
            submenuResult = btl_submenu_moves_update();
            switch (submenuResult) {
                case POPUP_RESULT_CHOOSING:
                    // do nothing while player is choosing from menu
                    break;
                case POPUP_RESULT_INVALID:
                    gBattleSubState = BTL_SUBSTATE_ABILITIES_SHOW_ERROR;
                    break;
                case POPUP_RESULT_CANCEL:
                    btl_main_menu_resume_choose();
                    BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
                    BattleMenu_SwapDelay = 4;
                    gBattleSubState = BTL_SUBSTATE_MAIN_CHOOSING;
                    btl_state_update_player_menu();
                    btl_state_update_player_menu();
                    break;
                default: // something has been selected
                    battleStatus->lastSelectedAbility = MovesOptionIndices[submenuResult - 1];
                    battleStatus->selectedMoveID = battleStatus->submenuMoves[battleStatus->lastSelectedAbility];
                    if (battleStatus->curSubmenu == BTL_MENU_TYPE_JUMP) {
                        battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_JUMP] = SelectedMovesIndex;
                    }
                    if (battleStatus->curSubmenu == BTL_MENU_TYPE_SMASH) {
                        battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_SMASH] = SelectedMovesIndex;
                    }
                    currentSubmenu2 = battleStatus->curSubmenu;
                    if (battleStatus->curSubmenu == BTL_MENU_TYPE_ITEMS) {
                        battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_ITEMS] = SelectedMovesIndex;
                        if (battleStatus->curSubmenu == currentSubmenu2) {
                            gBattleSubState = BTL_SUBSTATE_DIPPING_BUILD_MENU;
                            btl_state_update_player_menu();
                            btl_state_update_player_menu();
                            break;
                        }
                    }
                    btl_submenu_moves_hide();
                    btl_main_menu_hide();
                    gBattleSubState = BTL_SUBSTATE_ABILITIES_HANDOVER;
                    break;
            }
            break;
        case BTL_SUBSTATE_ABILITIES_HANDOVER:
            submenuResult = btl_submenu_moves_update();
            if ((battleStatus->curButtonsPressed & BUTTON_B) && submenuResult == 0) {
                btl_submenu_moves_restore_choose();
                btl_main_menu_restore_submenu();
                gBattleSubState = BTL_SUBSTATE_ABILITIES_REOPEN_MENU;
                break;
            }
            if (btl_main_menu_update() == 0) {
                break;
            }
            battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_ABILITIES_TARGET_CANCEL;
            battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_ABILITIES_TARGET_CHOSEN;
            battleStatus->selectedMoveID = battleStatus->submenuMoves[battleStatus->lastSelectedAbility];
            battleStatus->curTargetListFlags = gMoveTable[battleStatus->submenuMoves[battleStatus->lastSelectedAbility]].flags;
            currentSubmenu = battleStatus->curSubmenu;
            switch (currentSubmenu) {
                case BTL_MENU_TYPE_JUMP:
                    battleStatus->moveCategory = BTL_MENU_TYPE_JUMP;
                    battleStatus->moveArgument = playerData->bootsLevel;
                    btl_set_state(BATTLE_STATE_SELECT_TARGET);
                    break;
                case BTL_MENU_TYPE_SMASH:
                    battleStatus->moveCategory = BTL_MENU_TYPE_SMASH;
                    battleStatus->moveArgument = playerData->hammerLevel;
                    btl_set_state(BATTLE_STATE_SELECT_TARGET);
                    break;
                case BTL_MENU_TYPE_DEFEND:
                    gBattleSubState = battleStatus->acceptTargetMenuSubstate;
                    btl_state_update_player_menu();
                    battleStatus->moveCategory = BTL_MENU_TYPE_DEFEND;
                    btl_set_state(BATTLE_STATE_DEFEND);
                    break;
            }
            break;
        case BTL_SUBSTATE_ABILITIES_REOPEN_MENU:
            btl_submenu_moves_update();
            if (btl_main_menu_update() == 0) {
                break;
            }
            gBattleSubState = BTL_SUBSTATE_ABILITIES_CHOOSING;
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
        case BTL_SUBSTATE_MAIN_SHOW_CANT_SWAP: {
            s32 msgIndex;
            s32 msgArg;
            if (gBattleStatus.flags2 & BS_FLAGS2_PARTNER_TURN_USED) {
                msgIndex = BTL_MSG_CANT_SWITCH;
                msgArg = 0;
            } else {
                msgIndex = BTL_MSG_CANT_MOVE;
                msgArg = playerData->curPartner;
            }
            CALL_EVENT(OnSwapRefused, &msgIndex, &msgArg);
            btl_show_variable_battle_message(msgIndex, 60, msgArg);
            ShowingErrorMessage = true;
            gBattleSubState = BTL_SUBSTATE_MAIN_AWAIT_CANT_SWAP;
            break;
        }
        case BTL_SUBSTATE_MAIN_AWAIT_CANT_SWAP:
            if (btl_is_popup_displayed()) {
                break;
            }
            ShowingErrorMessage = false;
            BattleMenu_ChooseDelay = 0;
            BattleMenu_SwapDelay = 4;
            gBattleSubState = BTL_SUBSTATE_MAIN_CHOOSING;
            break;
        case BTL_SUBSTATE_NOSUBMENU_SHOW:
            btl_main_menu_hide();
            gBattleSubState = BTL_SUBSTATE_NOSUBMENU_HANDOVER;
            break;
        case BTL_SUBSTATE_NOSUBMENU_HANDOVER:
            submenuResult = btl_main_menu_update();

            if (submenuResult == 0) {
                if (battleStatus->curButtonsPressed & BUTTON_B) {
                    btl_main_menu_restore_choose();
                    gBattleSubState = BTL_SUBSTATE_NOSUBMENU_RETURN_MAIN;
                }
                break;
            }

            battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_NOSUBMENU_TARGET_CANCEL;
            battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_NOSUBMENU_TARGET_CHOSEN;
            switch (battleStatus->curSubmenu) {
                case BTL_MENU_TYPE_JUMP:
                    battleStatus->moveCategory = BTL_MENU_TYPE_JUMP;
                    battleStatus->moveArgument = playerData->bootsLevel;
                    battleStatus->selectedMoveID = playerData->bootsLevel + MOVE_JUMP1;
                    battleStatus->curTargetListFlags = gMoveTable[battleStatus->selectedMoveID].flags;
                    btl_set_state(BATTLE_STATE_SELECT_TARGET);
                    break;
                case BTL_MENU_TYPE_SMASH:
                    battleStatus->moveCategory = BTL_MENU_TYPE_SMASH;
                    battleStatus->moveArgument = playerData->hammerLevel;
                    battleStatus->selectedMoveID = playerData->hammerLevel + MOVE_HAMMER1;
                    battleStatus->curTargetListFlags = gMoveTable[battleStatus->selectedMoveID].flags;
                    btl_set_state(BATTLE_STATE_SELECT_TARGET);
                    break;
            }
            if (gBattleState == BATTLE_STATE_SELECT_TARGET) {
                break;
            }
            // fallthrough
        case BTL_SUBSTATE_NOSUBMENU_RETURN_MAIN:
            if (btl_main_menu_update() == 0) {
                break;
            }
            BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
            BattleMenu_SwapDelay = 4;
            gBattleSubState = BTL_SUBSTATE_MAIN_CHOOSING;
            break;
        case BTL_SUBSTATE_NOSUBMENU_TARGET_CANCEL:
            btl_main_menu_restore_choose();
            gBattleSubState = BTL_SUBSTATE_NOSUBMENU_RETURN_MAIN;
            break;
        case BTL_SUBSTATE_NOSUBMENU_TARGET_CHOSEN:
            btl_main_menu_destroy();
            break;
        case BTL_SUBSTATE_DIPPING_BUILD_MENU:
            if (battleStatus->selectedMoveID == MOVE_DOUBLE_DIP) {
                battleStatus->itemUsesLeft = 2;
            }
            if (battleStatus->selectedMoveID == MOVE_TRIPLE_DIP) {
                battleStatus->itemUsesLeft = 3;
            }
            entryIdx = 0;
            invCapacity = get_consumables_capacity();
            for (i = 0; i < invCapacity; i++) {
                if (playerData->invItems[i] == ITEM_NONE) {
                    continue;
                }
                itemData = &gItemTable[playerData->invItems[i]];
                hudScriptPair = &gItemHudScripts[itemData->hudElemID];
                if (!(itemData->typeFlags & ITEM_TYPE_FLAG_BATTLE_USABLE)) {
                    continue;
                }
                battleStatus->moveCategory = BTL_MENU_TYPE_ITEMS;
                battleStatus->moveArgument = playerData->invItems[i];
                battleStatus->curTargetListFlags = itemData->targetFlags;
                create_current_pos_target_list(playerActor);
                popup->ptrIcon[entryIdx] = hudScriptPair->enabled;
                popup->userIndex[entryIdx] = playerData->invItems[i];
                popup->enabled[entryIdx] = true;
                popup->nameMsg[entryIdx] = itemData->nameMsg;
                popup->descMsg[entryIdx] = itemData->shortDescMsg;
                if (playerActor->targetListLength == 0) {
                    popup->ptrIcon[entryIdx] = hudScriptPair->disabled;
                    popup->enabled[entryIdx] = 0;
                }
                entryIdx++;
            }
            popup->dipMode = 0;
            popup->titleNumber = 0;
            if (battleStatus->selectedMoveID == MOVE_DOUBLE_DIP) {
                popup->dipMode = 1;
                popup->titleNumber = battleStatus->itemUsesLeft;
            }
            if (battleStatus->selectedMoveID == MOVE_TRIPLE_DIP) {
                popup->dipMode = 2;
                popup->titleNumber = battleStatus->itemUsesLeft;
            }
            if (battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_DIP] < 0) {
                battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_DIP] = 0;
            }
            popup->popupType = POPUP_MENU_USE_ITEM;
            popup->numEntries = entryIdx;
            initialPos = battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_DIP];
            popup->initialPos = initialPos;
            create_battle_popup_menu(popup);
            flush_popup_menu();
            gBattleSubState = BTL_SUBSTATE_DIPPING_CHOOSING;
            break;
        case BTL_SUBSTATE_DIPPING_CHOOSING:
            switch (popup->result) {
                case POPUP_RESULT_CHOOSING:
                    // do nothing while player is choosing from popup menu
                    break;
                case POPUP_RESULT_CANCEL:
                    btl_submenu_moves_resume_choose();
                    battleStatus->selectedMoveID = 0;
                    battleStatus->itemUsesLeft = 0;
                    gBattleSubState = BTL_SUBSTATE_ABILITIES_CHOOSING;
                    btl_state_update_player_menu();
                    btl_state_update_player_menu();
                    break;
                default:
                    battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_DIPPING_TARGET_CANCEL;
                    battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_DIPPING_TARGET_CHOSEN;
                    battleStatus->lastSelectedItem = popup->userIndex[popup->result - 1];
                    battleStatus->moveCategory = BTL_MENU_TYPE_ITEMS;
                    battleStatus->moveArgument = battleStatus->lastSelectedItem;
                    battleStatus->curTargetListFlags = gItemTable[battleStatus->moveArgument].targetFlags | TARGET_FLAG_PRIMARY_ONLY;
                    battleStatus->curAttackElement = 0;
                    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_DIP] = popup->result - 1;
                    hide_popup_menu();
                    btl_submenu_moves_hide();
                    btl_main_menu_hide();
                    gBattleSubState = BTL_SUBSTATE_DIPPING_HANDOVER;
                    break;
            }
            break;
        case BTL_SUBSTATE_DIPPING_HANDOVER:
            if ((battleStatus->curButtonsPressed & BUTTON_B) && popup->result == POPUP_RESULT_CHOOSING) {
                show_popup_menu();
                btl_submenu_moves_restore_locked();
                btl_main_menu_restore_submenu();
                battleStatus->selectedMoveID = 0;
                gBattleSubState = BTL_SUBSTATE_DIPPING_REOPEN_MENU;
            } else {
                btl_submenu_moves_update();
                if (btl_main_menu_update()) {
                    btl_set_state(BATTLE_STATE_SELECT_TARGET);
                }
            }
            break;
        case BTL_SUBSTATE_DIPPING_REOPEN_MENU:
            btl_submenu_moves_update();
            if (btl_main_menu_update() != 0) {
                gBattleSubState = BTL_SUBSTATE_DIPPING_CHOOSING;
            }
            break;
        case BTL_SUBSTATE_DIPPING_TARGET_CANCEL:
            show_popup_menu();
            btl_submenu_moves_restore_locked();
            btl_main_menu_restore_submenu();
            btl_submenu_moves_update();
            gBattleSubState = BTL_SUBSTATE_DIPPING_REOPEN_MENU;
            break;
        case BTL_SUBSTATE_DIPPING_TARGET_CHOSEN:
            destroy_popup_menu();
            btl_submenu_moves_destroy();
            btl_main_menu_destroy();
            break;
        case BTL_SUBSTATE_ITEMS_BUILD_MENU:
            entryIdx = 0;
            invCapacity = get_consumables_capacity();
            for (i = 0; i < invCapacity; i++) {
                if (playerData->invItems[i] == ITEM_NONE) {
                    continue;
                }
                itemData = &gItemTable[playerData->invItems[i]];
                hudScriptPair = &gItemHudScripts[itemData->hudElemID];
                if (!(itemData->typeFlags & ITEM_TYPE_FLAG_BATTLE_USABLE)) {
                    continue;
                }
                battleStatus->moveCategory = BTL_MENU_TYPE_ITEMS;
                battleStatus->moveArgument = playerData->invItems[i];
                battleStatus->curTargetListFlags = itemData->targetFlags;
                create_current_pos_target_list(playerActor);
                popup->ptrIcon[entryIdx] = hudScriptPair->enabled;

                popup->userIndex[entryIdx] = playerData->invItems[i];
                popup->enabled[entryIdx] = true;
                popup->nameMsg[entryIdx] = itemData->nameMsg;
                popup->descMsg[entryIdx] = itemData->shortDescMsg;
                if (playerActor->targetListLength == 0) {
                    popup->ptrIcon[entryIdx] = hudScriptPair->disabled;
                    popup->enabled[entryIdx] = 0;
                }
                entryIdx++;
            }
            if (battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_DIP] < 0) {
                battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_DIP] = 0;
            }
            initialPos = battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_DIP];
            popup->popupType = POPUP_MENU_USE_ITEM;
            popup->numEntries = entryIdx;
            popup->dipMode = 0;
            popup->titleNumber = 0;
            popup->initialPos = initialPos;
            create_battle_popup_menu(popup);
            flush_popup_menu();
            gBattleSubState = BTL_SUBSTATE_ITEMS_CHOOSING;
            break;
        case BTL_SUBSTATE_ITEMS_CHOOSING:
            switch(popup->result) {
                case POPUP_RESULT_CHOOSING:
                    // do nothing while player is choosing from popup menu
                    break;
                case POPUP_RESULT_CANCEL:
                    btl_main_menu_resume_choose();
                    BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
                    BattleMenu_SwapDelay = 4;
                    gBattleSubState = BTL_SUBSTATE_MAIN_CHOOSING;
                    btl_state_update_player_menu();
                    btl_state_update_player_menu();
                    break;
                default:
                    battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_ITEMS_TARGET_CANCEL;
                    battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_ITEMS_TARGET_CHOSEN;
                    battleStatus->lastSelectedItem = popup->userIndex[popup->result - 1];
                    battleStatus->moveCategory = BTL_MENU_TYPE_ITEMS;
                    battleStatus->moveArgument = battleStatus->lastSelectedItem;
                    battleStatus->selectedMoveID = MOVE_ITEMS;
                    battleStatus->curTargetListFlags = gItemTable[battleStatus->moveArgument].targetFlags | TARGET_FLAG_PRIMARY_ONLY;
                    battleStatus->curAttackElement = 0;
                    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_DIP] = popup->result - 1;
                    hide_popup_menu();
                    btl_main_menu_hide();
                    gBattleSubState = BTL_SUBSTATE_ITEMS_HANDOVER;
                    break;
            }
            break;
        case BTL_SUBSTATE_ITEMS_HANDOVER:
            if ((battleStatus->curButtonsPressed & BUTTON_B) && popup->result == POPUP_RESULT_CHOOSING) {
                show_popup_menu();
                btl_main_menu_restore_submenu();
                gBattleSubState = BTL_SUBSTATE_ITEMS_REOPEN_MENU;
            } else {
                if (btl_main_menu_update() != 0) {
                    btl_set_state(BATTLE_STATE_SELECT_TARGET);
                }
            }
            break;
        case BTL_SUBSTATE_ITEMS_REOPEN_MENU:
            if (btl_main_menu_update() != 0) {
                gBattleSubState = BTL_SUBSTATE_ITEMS_CHOOSING;
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
        case BTL_SUBSTATE_STAR_SPIRITS_BUILD_MENU:
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
                if (!(battleStatus->enabledStarPowersFlags & (1 << i))) {
                    battleStatus->submenuStatus[i] = 0;
                    MovesOptionError[i] = BTL_MSG_CANT_SELECT_NOW;
                }

                MovesOptionHudScripts[i] = StarPowerMovesHudScripts[STAR_POWER_INDEX(battleStatus->submenuMoves[i])].enabled;
                if (battleStatus->submenuStatus[i] == 0) {
                    MovesOptionHudScripts[i] = StarPowerMovesHudScripts[STAR_POWER_INDEX(battleStatus->submenuMoves[i])].disabled;
                }
                MovesOptionDisplayCosts[i] = moveData->costFP;
                MovesOptionBPCosts[i] = moveData->costBP;
                MovesOptionSortPriority[i] = 0;
                MovesOptionIndices[i] = i;
                MovesOptionEnabled[i] = battleStatus->submenuStatus[i];
                MovesOptionNames[i] = moveData->nameMsg;
                MovesOptionDesc[i] = moveData->shortDescMsg;
                MovesOptionDiscounts[i] = 0;
                MovesOptionDiscountColors[i] = 0;
            }
            if (battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_STAR_POWER] < 0) {
                battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_STAR_POWER] = 0;
            }
            UsingSpiritsSubmenu = true;
            MovesOptionCount = battleStatus->submenuMoveCount;
            initialPos = battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_STAR_POWER];
            {
                CALL_EVENT(OnBattleMenuBuilt, BATTLE_MENU_MOVES, ACTOR_PLAYER, BTL_MENU_TYPE_STAR_POWERS, &MovesOptionCount, &initialPos);
                if (MovesOptionCount > ARRAY_COUNT(MovesOptionIndices)) {
                    MovesOptionCount = ARRAY_COUNT(MovesOptionIndices);
                }
            }
            MovesPrevSelected = initialPos;
            btl_submenu_moves_init();
            gBattleSubState = BTL_SUBSTATE_STAR_SPIRITS_CHOOSING;
            break;
        case BTL_SUBSTATE_STAR_SPIRITS_CHOOSING:
            submenuResult = btl_submenu_moves_update();
            switch(submenuResult) {
                case POPUP_RESULT_CHOOSING:
                    // do nothing while player is choosing from menu
                    break;
                case POPUP_RESULT_INVALID:
                    gBattleSubState = BTL_SUBSTATE_STAR_SPIRITS_SHOW_ERROR;
                    break;
                case POPUP_RESULT_CANCEL:
                    btl_main_menu_resume_choose();
                    BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
                    BattleMenu_SwapDelay = 4;
                    gBattleSubState = BTL_SUBSTATE_MAIN_CHOOSING;
                    btl_state_update_player_menu();
                    btl_state_update_player_menu();
                    break;
                default:
                    battleStatus->lastSelectedAbility = MovesOptionIndices[submenuResult - 1];
                    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_STAR_POWER] = SelectedMovesIndex;
                    btl_submenu_moves_hide();
                    btl_main_menu_hide();
                    gBattleSubState = BTL_SUBSTATE_STAR_SPIRITS_HANDOVER;
                    break;
            }
            break;
        case BTL_SUBSTATE_STAR_SPIRITS_HANDOVER:
            submenuResult = btl_submenu_moves_update();
            if ((battleStatus->curButtonsPressed & BUTTON_B) && submenuResult == 0) {
                btl_submenu_moves_restore_choose();
                btl_main_menu_restore_submenu();
                gBattleSubState = BTL_SUBSTATE_STAR_SPIRITS_REOPEN_MENU;
            } else if (btl_main_menu_update() != 0) {
                battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_STAR_SPIRITS_TARGET_CANCEL;
                battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_STAR_SPIRITS_TARGET_CHOSEN;
                battleStatus->moveCategory = BTL_MENU_TYPE_STAR_POWERS;
                battleStatus->selectedMoveID = battleStatus->submenuMoves[battleStatus->lastSelectedAbility];
                battleStatus->curTargetListFlags = gMoveTable[battleStatus->submenuMoves[battleStatus->lastSelectedAbility]].flags;
                battleStatus->moveArgument = battleStatus->lastSelectedAbility;
                if (playerData->starBeamLevel == 2 && battleStatus->moveArgument == 8) {
                    battleStatus->moveArgument++;
                }
                btl_set_state(BATTLE_STATE_SELECT_TARGET);
            }
            break;
        case BTL_SUBSTATE_STAR_SPIRITS_REOPEN_MENU:
            btl_submenu_moves_update();
            if (btl_main_menu_update() != 0) {
                gBattleSubState = BTL_SUBSTATE_STAR_SPIRITS_CHOOSING;
            }
            break;
        case BTL_SUBSTATE_STAR_SPIRITS_TARGET_CANCEL:
            btl_submenu_moves_restore_choose();
            btl_main_menu_restore_submenu();
            gBattleSubState = BTL_SUBSTATE_STAR_SPIRITS_REOPEN_MENU;
            break;
        case BTL_SUBSTATE_STAR_SPIRITS_TARGET_CHOSEN:
            btl_submenu_moves_destroy();
            btl_main_menu_destroy();
            break;
        case BTL_SUBSTATE_STAR_SPIRITS_SHOW_ERROR:
            if (btl_submenu_moves_update() != POPUP_RESULT_INVALID) {
                gBattleSubState = BTL_SUBSTATE_STAR_SPIRITS_CHOOSING;
            }
            break;
        case BTL_SUBSTATE_NEXT_DIP_BUILD_MENU:
            if (!btl_player_can_act()) {
                battleStatus->itemUsesLeft = 1;
                btl_set_state(BATTLE_STATE_END_PLAYER_TURN);
            } else {
                entryIdx = 0;
                invCapacity = get_consumables_capacity();
                for (i = 0; i < invCapacity; i++) {
                    if (playerData->invItems[i] == ITEM_NONE) {
                        continue;
                    }
                    itemData = &gItemTable[playerData->invItems[i]];
                    hudScriptPair = &gItemHudScripts[itemData->hudElemID];
                    if (!(itemData->typeFlags & ITEM_TYPE_FLAG_BATTLE_USABLE)) {
                        continue;
                    }

                    battleStatus->moveCategory = BTL_MENU_TYPE_ITEMS;
                    battleStatus->moveArgument = playerData->invItems[i];
                    battleStatus->curTargetListFlags = itemData->targetFlags;
                    create_current_pos_target_list(playerActor);
                    popup->ptrIcon[entryIdx] = hudScriptPair->enabled;
                    popup->userIndex[entryIdx] = playerData->invItems[i];
                    popup->enabled[entryIdx] = true;
                    popup->nameMsg[entryIdx] = itemData->nameMsg;
                    popup->descMsg[entryIdx] = itemData->shortDescMsg;
                    if (playerActor->targetListLength == 0) {
                        popup->ptrIcon[entryIdx] = hudScriptPair->disabled;
                        popup->enabled[entryIdx] = false;
                    }
                    entryIdx++;
                }
                if (entryIdx == 0) {
                    battleStatus->itemUsesLeft = 1;
                    btl_set_state(BATTLE_STATE_END_PLAYER_TURN);
                } else {
                    popup->popupType = POPUP_MENU_USE_ITEM;
                    if (battleStatus->selectedMoveID == MOVE_DOUBLE_DIP) {
                        popup->popupType += POPUP_MENU_DOUBLE_DIP;
                        popup->dipMode = 1;
                        popup->titleNumber = battleStatus->itemUsesLeft;
                    }
                    if (battleStatus->selectedMoveID == MOVE_TRIPLE_DIP) {
                        popup->popupType += POPUP_MENU_TRIPLE_DIP;
                        popup->dipMode = 2;
                        popup->titleNumber = battleStatus->itemUsesLeft;
                    }
                    if (battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_DIP] < 0) {
                        battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_DIP] = 0;
                    }
                    popup->numEntries = entryIdx;
                    initialPos = battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_DIP];
                    popup->initialPos = initialPos;
                    create_battle_popup_menu(popup);
                    flush_popup_menu();
                    gBattleSubState = BTL_SUBSTATE_NEXT_DIP_CHOOSING;
                }
            }
            break;
        case BTL_SUBSTATE_NEXT_DIP_CHOOSING:
            switch(popup->result) {
                case POPUP_RESULT_CHOOSING:
                    // do nothing while player is choosing from menu
                    break;
                case POPUP_RESULT_CANCEL:
                    battleStatus->itemUsesLeft = 1;
                    btl_set_state(BATTLE_STATE_END_PLAYER_TURN);
                    break;
                default:
                    battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_NEXT_DIP_TARGET_CANCEL;
                    battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_NEXT_DIP_TARGET_CHOSEN;
                    battleStatus->lastSelectedItem = popup->userIndex[popup->result - 1];
                    battleStatus->moveCategory = BTL_MENU_TYPE_ITEMS;
                    battleStatus->moveArgument = battleStatus->lastSelectedItem;
                    battleStatus->curTargetListFlags = gItemTable[battleStatus->moveArgument].targetFlags | TARGET_FLAG_PRIMARY_ONLY;
                    battleStatus->curAttackElement = 0;
                    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_DIP] = popup->result - 1;
                    hide_popup_menu();
                    BattleMenu_ChooseDelay = MENU_DIPPING_DELAY;
                    gBattleSubState = BTL_SUBSTATE_NEXT_DIP_HANDOVER;
                    break;
            }
            break;
        case BTL_SUBSTATE_NEXT_DIP_HANDOVER:
            if (BattleMenu_ChooseDelay != 0) {
                BattleMenu_ChooseDelay--;
            } else {
                btl_set_state(BATTLE_STATE_SELECT_TARGET);
            }
            break;
        case BTL_SUBSTATE_NEXT_DIP_REOPEN_MENU:
            if (BattleMenu_ChooseDelay != 0) {
                BattleMenu_ChooseDelay--;
            } else {
                gBattleSubState = BTL_SUBSTATE_NEXT_DIP_CHOOSING;
            }
            break;
        case BTL_SUBSTATE_NEXT_DIP_TARGET_CANCEL:
            show_popup_menu();
            BattleMenu_ChooseDelay = MENU_DIPPING_DELAY;
            gBattleSubState = BTL_SUBSTATE_NEXT_DIP_REOPEN_MENU;
            break;
        case BTL_SUBSTATE_NEXT_DIP_TARGET_CHOSEN:
            destroy_popup_menu();
            break;
        case BTL_SUBSTATE_BERSERKER_CHOOSE:
            if (playerData->bootsLevel > GEAR_RANK_NONE) {
                battleStatus->curTargetListFlags = gMoveTable[MOVE_BERSERKER_JUMP].flags;
                create_current_pos_target_list(playerActor);
                jumpTargetCount = playerActor->targetListLength;
            } else {
                jumpTargetCount = 0;
            }

            if (playerData->hammerLevel > GEAR_RANK_NONE) {
                battleStatus->curTargetListFlags = gMoveTable[MOVE_BERSERKER_HAMMER].flags;
                create_current_pos_target_list(playerActor);
                hammerTargetCount = playerActor->targetListLength;
            } else {
                hammerTargetCount = 0;
            }

            if (jumpTargetCount <= 0 && hammerTargetCount <= 0) {
                battleStatus->moveCategory = BTL_MENU_TYPE_DO_NOTHING;
                battleStatus->waitForState = BATTLE_STATE_NONE;
                btl_set_state(BATTLE_STATE_END_PLAYER_TURN);
            } else {
                jumpChance = 50;
                if (jumpTargetCount <= 0) {
                    jumpChance = 0;
                }
                if (hammerTargetCount <= 0) {
                    jumpChance = 101;
                }
                if (rand_int(100) < jumpChance) {
                    battleStatus->selectedMoveID = MOVE_BERSERKER_JUMP;
                    battleStatus->moveCategory = BTL_MENU_TYPE_JUMP;
                    battleStatus->curTargetListFlags = gMoveTable[MOVE_BERSERKER_JUMP].flags;
                    battleStatus->moveArgument = playerData->bootsLevel;
                    create_current_pos_target_list(playerActor);
                } else {
                    battleStatus->selectedMoveID = MOVE_BERSERKER_HAMMER;
                    battleStatus->moveCategory = BTL_MENU_TYPE_SMASH;
                    battleStatus->curTargetListFlags = gMoveTable[MOVE_BERSERKER_HAMMER].flags;
                    battleStatus->moveArgument = playerData->hammerLevel;
                    create_current_pos_target_list(playerActor);
                }
                btl_set_state(BATTLE_STATE_PLAYER_MOVE);
            }
            break;
        case BTL_SUBSTATE_STRATEGIES_BUILD_MENU:
            entryIdx = 0;
            btl_check_can_change_partner();

            // add 'Change Member' command
            if (battleStatus->changePartnerAllowed >= 0) {
                StratsOptionMenuTypes[entryIdx] = BTL_MENU_TYPE_CHANGE_PARTNER;
                StratsOptionNames[entryIdx] = LeftJustMenuMessages[BTL_MENU_TYPE_CHANGE_PARTNER];
                StratsOptionHudScripts[entryIdx] = PartnerHudScripts[playerData->curPartner].enabled;
                StratsOptionEnabled[entryIdx] = true;
                StratsOptionMessage[entryIdx] = MSG_Menus_Action_ChangePartner;
                if (battleStatus->changePartnerAllowed <= 0) {
                    StratsOptionHudScripts[entryIdx] = PartnerHudScripts[playerData->curPartner].disabled;
                    StratsOptionEnabled[entryIdx] = false;
                    StratsOptionError[entryIdx] = 0;
                }
                entryIdx++;
            }

            // add 'Do Nothing' command
            StratsOptionHudScripts[entryIdx] = DoNothingHudScripts.enabled;
            StratsOptionMenuTypes[entryIdx] = BTL_MENU_TYPE_DO_NOTHING;
            StratsOptionEnabled[entryIdx] = true;
            StratsOptionNames[entryIdx] = LeftJustMenuMessages[BTL_MENU_TYPE_DO_NOTHING];
            StratsOptionMessage[entryIdx] = MSG_Menus_Action_DoNothing;
            entryIdx++;

            // add 'Run Away' command
            StratsOptionHudScripts[entryIdx] = FleeHudScripts.enabled;
            StratsOptionMenuTypes[entryIdx] = BTL_MENU_TYPE_RUN_AWAY;
            StratsOptionEnabled[entryIdx] = true;
            StratsOptionNames[entryIdx] = LeftJustMenuMessages[BTL_MENU_TYPE_RUN_AWAY];
            StratsOptionMessage[entryIdx] = MSG_Menus_Action_RunAway;
            if (!(gBattleStatus.flags2 & BS_FLAGS2_CAN_FLEE)) {
                StratsOptionHudScripts[entryIdx] = FleeHudScripts.disabled;
                StratsOptionEnabled[entryIdx] = false;
                StratsOptionError[entryIdx] = 1;
            }
            entryIdx++;

            if (battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_STRATEGY] < 0) {
                battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_STRATEGY] = 0;
            }
            initialPos = battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_STRATEGY];
            {
                CALL_EVENT(OnBattleMenuBuilt, BATTLE_MENU_STRATEGIES, ACTOR_PLAYER, -1, &entryIdx, &initialPos);
                if (entryIdx > ARRAY_COUNT(StratsOptionMenuTypes)) {
                    entryIdx = ARRAY_COUNT(StratsOptionMenuTypes);
                }
            }
            StratsOptionCount = entryIdx;
            StratsPrevSelected = initialPos;
            btl_menu_strats_init();
            gBattleSubState = BTL_SUBSTATE_STRATEGIES_CHOOSING;
            break;
        case BTL_SUBSTATE_STRATEGIES_CHOOSING:
            submenuResult = btl_submenu_strats_update();
            switch(submenuResult) {
                case POPUP_RESULT_CHOOSING:
                    // do nothing while player is choosing from menu
                    break;
                case POPUP_RESULT_INVALID:
                    gBattleSubState = BTL_SUBSTATE_STRATEGIES_SHOW_ERROR;
                    break;
                case POPUP_RESULT_CANCEL:
                    btl_main_menu_resume_choose();
                    BattleMenu_ChooseDelay = MENU_CHANGE_DELAY;
                    BattleMenu_SwapDelay = 4;
                    gBattleSubState = BTL_SUBSTATE_MAIN_CHOOSING;
                    btl_state_update_player_menu();
                    btl_state_update_player_menu();
                    break;
                default:
                    battleStatus->curSubmenu = StratsOptionMenuTypes[submenuResult - 1];
                    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_STRATEGY] = submenuResult - 1;
                    if (battleStatus->curSubmenu == BTL_MENU_TYPE_CHANGE_PARTNER) {
                        gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_BUILD_MENU;
                        btl_state_update_player_menu();
                        btl_state_update_player_menu();
                    } else {
                        btl_submenu_strats_hide();
                        btl_main_menu_hide();
                        gBattleSubState = BTL_SUBSTATE_STRATEGIES_HANDOVER;
                    }
                    break;
                }
            break;
        case BTL_SUBSTATE_STRATEGIES_HANDOVER:
            submenuResult = btl_submenu_strats_update();
            if ((battleStatus->curButtonsPressed & BUTTON_B) && submenuResult == 0) {
                btl_submenu_strats_restore_choose();
                btl_main_menu_restore_submenu();
                gBattleSubState = BTL_SUBSTATE_STRATEGIES_REOPEN_MENU;
            } else if (btl_main_menu_update() != 0) {
                battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_STRATEGIES_TARGET_CANCEL;
                battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_STRATEGIES_TARGET_CHOSEN;
                switch (battleStatus->curSubmenu) {
                    case BTL_MENU_TYPE_RUN_AWAY:
                        gBattleSubState = BTL_SUBSTATE_STRATEGIES_TARGET_CHOSEN;
                        btl_state_update_player_menu();
                        battleStatus->moveCategory = BTL_MENU_TYPE_RUN_AWAY;
                        battleStatus->selectedMoveID = MOVE_RUN_AWAY;
                        btl_set_state(BATTLE_STATE_RUN_AWAY);
                        break;
                    case BTL_MENU_TYPE_DO_NOTHING:
                        battleStatus->hustleTurns = 0;
                        gBattleStatus.flags1 &= ~BS_FLAGS1_HUSTLED;
                        gBattleSubState = battleStatus->acceptTargetMenuSubstate;
                        btl_state_update_player_menu();
                        btl_set_state(BATTLE_STATE_END_PLAYER_TURN);
                        break;
                    case BTL_MENU_TYPE_DEFEND:
                        gBattleSubState = BTL_SUBSTATE_STRATEGIES_TARGET_CHOSEN;
                        btl_state_update_player_menu();
                        battleStatus->moveCategory = BTL_MENU_TYPE_DEFEND;
                        battleStatus->selectedMoveID = MOVE_DEFEND;
                        btl_set_state(BATTLE_STATE_DEFEND);
                        break;
                    case BTL_MENU_TYPE_ACT_LATER:
                        gBattleSubState = BTL_SUBSTATE_STRATEGIES_TARGET_CHOSEN;
                        btl_state_update_player_menu();
                        btl_set_state(BATTLE_STATE_SWITCH_TO_PARTNER);
                        break;
                    default:
                        gBattleSubState = BTL_SUBSTATE_STRATEGIES_TARGET_CHOSEN;
                        btl_state_update_player_menu();
                        {
                            CALL_EVENT(OnBattleMenuSelect, BATTLE_MENU_STRATEGIES, ACTOR_PLAYER,
                                       battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_STRATEGY]);
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
                gBattleSubState = BTL_SUBSTATE_MAIN_CHOOSING;
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
            if (btl_submenu_strats_update() != -1) {
                gBattleSubState = BTL_SUBSTATE_STRATEGIES_CHOOSING;
            }
            break;
        case BTL_SUBSTATE_CHANGE_PARTNER_BUILD_MENU:
            entryIdx = 0;
            for (i = 1; i < ARRAY_COUNT(playerData->partners); i++) {
                s32 partnerId = PartnerIDFromMenuIndex[i];
                if (playerData->partners[partnerId].enabled) {
                    prop = &gPartnerPopupProperties[partnerId];
                    popup->ptrIcon[entryIdx] = PartnerHudScripts[partnerId].enabled;
                    popup->enabled[entryIdx] = true;
                    popup->userIndex[entryIdx] = partnerId;
                    popup->nameMsg[entryIdx] = prop->nameMsg;
                    popup->descMsg[entryIdx] = prop->battleDescMsg;
                    popup->value[entryIdx] = playerData->partners[partnerId].level;
                    if (playerData->curPartner == partnerId) {
                        popup->ptrIcon[entryIdx] = PartnerHudScripts[partnerId].disabled;
                        popup->enabled[entryIdx] = false;
                    }
                    entryIdx++;
                }
            }
            if (battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_PARTNER] < 0) {
                battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_PARTNER] = 0;
            }
            initialPos = MenuIndexFromPartnerID[playerData->curPartner] - 1;
            {
                CALL_EVENT(OnBattleMenuBuilt, BATTLE_MENU_PARTNER_LIST, ACTOR_PLAYER, -1, &entryIdx, &initialPos);
                if (entryIdx > ARRAY_COUNT(popup->ptrIcon)) {
                    entryIdx = ARRAY_COUNT(popup->ptrIcon);
                }
            }
            popup->popupType = POPUP_MENU_SWITCH_PARTNER;
            popup->numEntries = entryIdx;
            popup->initialPos = initialPos;
            popup->dipMode = 0;
            popup->titleNumber = 0;
            create_battle_popup_menu(popup);
            flush_popup_menu();
            gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_CHOOSING;
            break;
        case BTL_SUBSTATE_CHANGE_PARTNER_CHOOSING:
            switch(popup->result) {
                case POPUP_RESULT_CHOOSING:
                    // do nothing while player is choosing from menu
                    break;
                case POPUP_RESULT_INVALID:
                    gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_ERROR;
                    break;
                case POPUP_RESULT_CANCEL:
                    btl_submenu_strats_resume_choose();
                    gBattleSubState = BTL_SUBSTATE_STRATEGIES_CHOOSING;
                    btl_state_update_player_menu();
                    btl_state_update_player_menu();
                    break;
                default:
                    battleStatus->cancelTargetMenuSubstate = BTL_SUBSTATE_CHANGE_PARTNER_TARGET_CANCEL;
                    battleStatus->acceptTargetMenuSubstate = BTL_SUBSTATE_CHANGE_PARTNER_TARGET_CHOSEN;
                    battleStatus->lastSelectedPartner = popup->userIndex[popup->result - 1];
                    battleStatus->moveCategory = BTL_MENU_TYPE_CHANGE_PARTNER;
                    battleStatus->selectedMoveID = MOVE_CHANGE_PARTNER;
                    battleStatus->curTargetListFlags = TARGET_FLAG_2;
                    battleStatus->moveArgument = battleStatus->lastSelectedPartner;
                    battleStatus->lastPlayerMenuSelection[BTL_MENU_IDX_PARTNER] = popup->result - 1;
                    hide_popup_menu();
                    btl_submenu_strats_hide();
                    btl_main_menu_hide();
                    gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_HANDOVER;
                    break;
            }
            break;
        case BTL_SUBSTATE_CHANGE_PARTNER_HANDOVER:
            if ((battleStatus->curButtonsPressed & BUTTON_B) && popup->result == POPUP_RESULT_CHOOSING) {
                show_popup_menu();
                btl_submenu_strats_restore_locked();
                btl_main_menu_restore_submenu();
                gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_REOPEN_MENU;
            } else {
                btl_submenu_strats_update();
                if (btl_main_menu_update() != 0) {
                    gBattleSubState = battleStatus->acceptTargetMenuSubstate;
                    btl_state_update_player_menu();
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
            if (popup->result != POPUP_RESULT_INVALID) {
                set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_9);
                set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_9);
                gBattleSubState = BTL_SUBSTATE_CHANGE_PARTNER_CHOOSING;
            }
            break;
    }
}

void btl_state_draw_player_menu(void) {
    switch (gBattleSubState) {
        case BTL_SUBSTATE_MAIN_CHOOSING:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_ABILITIES_CHOOSING:
        case BTL_SUBSTATE_ABILITIES_HANDOVER:
        case BTL_SUBSTATE_ABILITIES_REOPEN_MENU:
        case BTL_SUBSTATE_ABILITIES_TARGET_CANCEL:
        case BTL_SUBSTATE_NOSUBMENU_SHOW:
        case BTL_SUBSTATE_NOSUBMENU_HANDOVER:
        case BTL_SUBSTATE_NOSUBMENU_RETURN_MAIN:
        case BTL_SUBSTATE_NOSUBMENU_TARGET_CANCEL:
        case BTL_SUBSTATE_DIPPING_BUILD_MENU:
        case BTL_SUBSTATE_DIPPING_CHOOSING:
        case BTL_SUBSTATE_DIPPING_HANDOVER:
        case BTL_SUBSTATE_DIPPING_REOPEN_MENU:
        case BTL_SUBSTATE_DIPPING_TARGET_CANCEL:
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
        case BTL_SUBSTATE_STAR_SPIRITS_CHOOSING:
        case BTL_SUBSTATE_STAR_SPIRITS_HANDOVER:
        case BTL_SUBSTATE_STAR_SPIRITS_REOPEN_MENU:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_STAR_SPIRITS_TARGET_CANCEL:
        case BTL_SUBSTATE_STAR_SPIRITS_TARGET_CHOSEN:
        case BTL_SUBSTATE_STRATEGIES_BUILD_MENU:
        case BTL_SUBSTATE_STRATEGIES_CHOOSING:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_STRATEGIES_HANDOVER:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_STRATEGIES_REOPEN_MENU:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_STRATEGIES_TARGET_CANCEL:
            btl_main_menu_draw();
            break;
        case BTL_SUBSTATE_STRATEGIES_TARGET_CHOSEN:
            btl_main_menu_draw();
            break;
    }
}
