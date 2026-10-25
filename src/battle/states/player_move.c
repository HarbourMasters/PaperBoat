
#include "states.h"
#include "script_api/battle.h"

enum {
    // BTL_SUBSTATE_INIT                        = 0,
    BTL_SUBSTATE_BEGIN_SHOW_TIP                 = 1,
    BTL_SUBSTATE_SHOW_TIP_DELAY                 = 2,
    BTL_SUBSTATE_EXECUTE_MOVE                   = 3,
    BTL_SUBSTATE_HANDLE_RESULTS                 = 4,
    BTL_SUBSTATE_AWAIT_ENEMY_STATUS_POPUP       = 11,
    BTL_SUBSTATE_POST_ENEMY_STATUS_POPUP        = 12,
    BTL_SUBSTATE_CHECK_PLAYER_STATUS            = 20,
    BTL_SUBSTATE_AWAIT_PLAYER_STATUS_POPUP      = 21,
    BTL_SUBSTATE_POST_PLAYER_STATUS_POPUP       = 22,
    BTL_SUBSTATE_AWAIT_DONE                     = 30,
};

void btl_state_update_player_move(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    s32 messageIndex;
    Actor* actor;
    Evt* script;
    s32 enemyNotDone;
    s8 tipIndex;
    s32 i;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        battleStatus->stateFreezeCount = 0;
        battleStatus->actionResult = ACTION_RESULT_NONE;
        battleStatus->blockResult = BLOCK_RESULT_NONE;
        battleStatus->lastAttackDamage = 0;
        battleStatus->curDamageSource = DMG_SRC_DEFAULT;
        gBattleStatus.flags1 &= ~BS_FLAGS1_AUTO_SUCCEED_ACTION;
        gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;
        reset_actor_turn_info();
        player->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
        if (partner != nullptr) {
            partner->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
        }
        btl_cam_target_actor(ACTOR_PLAYER);
        gBattleStatus.flags1 &= ~BS_FLAGS1_SHOW_PLAYER_DECORATIONS;
        player->statusAfflicted = 0;
        gBattleStatus.flags2 |= BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
        gBattleStatus.flags1 &= ~BS_FLAGS1_YIELD_TURN;

        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != nullptr) {
                actor->statusAfflicted = 0;
            }
        }

        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != nullptr) {
                actor->flags &= ~ACTOR_FLAG_HEALTH_BAR_HIDDEN;
                actor->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            }
        }

        if (battleStatus->moveCategory == BTL_MENU_TYPE_JUMP || battleStatus->moveCategory == BTL_MENU_TYPE_SMASH) {
            if (battleStatus->nextMerleeSpellType == MERLEE_SPELL_ATK_BOOST) {
                battleStatus->merleeAttackBoost = 3;
                battleStatus->nextMerleeSpellType = MERLEE_SPELL_NONE;
                battleStatus->battlePhase = PHASE_MERLEE_ATTACK_BONUS;
                script = start_script(&EVS_Mario_HandlePhase, EVT_PRIORITY_A, 0);
                player->takeTurnScript = script;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
                gBattleStatus.flags1 |= BS_FLAGS1_10000;
                close_action_command_instruction_popup();
                gBattleSubState = BTL_SUBSTATE_BEGIN_SHOW_TIP;
            } else {
                gBattleSubState = BTL_SUBSTATE_EXECUTE_MOVE;
                gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;
            }
        } else {
            gBattleSubState = BTL_SUBSTATE_EXECUTE_MOVE;
            gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;
        }
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_BEGIN_SHOW_TIP:
            if (player->takeTurnScript != nullptr && does_script_exist(player->takeTurnScriptID)) {
                break;
            }
            player->takeTurnScript = nullptr;
            if (!is_ability_active(ABILITY_BERSERKER)) {
                if (battleStatus->selectedMoveID != MOVE_NONE) {
                    tipIndex = gMoveTable[battleStatus->selectedMoveID].actionTip;
                    if (tipIndex >= 0) {
                        btl_show_battle_message(BTL_MSG_FIRST_ACTION_TIP + tipIndex, 60);
                    }
                }
            }
            BattleSubstateDelay = 2;
            gBattleSubState = BTL_SUBSTATE_SHOW_TIP_DELAY;
            break;
        case BTL_SUBSTATE_SHOW_TIP_DELAY:
            if (BattleSubstateDelay != 0) {
                BattleSubstateDelay--;
            } else {
                gBattleSubState = BTL_SUBSTATE_EXECUTE_MOVE;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_EXECUTE_MOVE:
            gBattleStatus.flags1 &= ~BS_FLAGS1_4000;
            gBattleStatus.flags1 &= ~BS_FLAGS1_10000;
            increment_status_bar_disabled();
            gBattleStatus.flags1 |= BS_FLAGS1_EXECUTING_MOVE;
            reset_all_actor_sounds(player);
            battleStatus->battlePhase = PHASE_EXECUTE_ACTION;
            CALL_EVENT(OnBattleMoveStart, player, battleStatus->moveCategory, battleStatus->selectedMoveID,
                       battleStatus->moveArgument, player->targetActorID, player->targetPartID);
            if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                script = start_script(&EVS_Peach_HandlePhase, EVT_PRIORITY_A, 0);
            } else {
                script = start_script(&EVS_Mario_HandlePhase, EVT_PRIORITY_A, 0);
            }
            player->takeTurnScript = script;
            gBattleSubState = BTL_SUBSTATE_HANDLE_RESULTS;
            player->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PLAYER;
            break;
        case BTL_SUBSTATE_HANDLE_RESULTS:
            // wait for player battle phase script to finish
            if (!(gBattleStatus.flags1 & BS_FLAGS1_YIELD_TURN)) {
                if (player->takeTurnScript != nullptr && does_script_exist(player->takeTurnScriptID)) {
                    break;
                }
                player->takeTurnScript = nullptr;
            }

            gBattleStatus.flags1 &= ~BS_FLAGS1_EXECUTING_MOVE;

             // wait for player battle event script to finish
            if (player->handleEventScript != nullptr && does_script_exist(player->handleEventScriptID)) {
                break;
            }
            player->handleEventScript = nullptr;

            // wait for partner battle event script to finish
            if (partner != nullptr) {
                if (partner->handleEventScript != nullptr && does_script_exist(partner->handleEventScriptID)) {
                    break;
                }
                partner->handleEventScript = nullptr;
            }

            // wait for all enemy battle phase scripts to finish
            enemyNotDone = false;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != nullptr && actor->takeTurnScript != nullptr) {
                    if (does_script_exist(actor->takeTurnScriptID)) {
                        enemyNotDone = true;
                    } else {
                        actor->takeTurnScript = nullptr;
                    }
                }
            }
            if (enemyNotDone) {
                break;
            }

            // wait for all enemy battle event scripts to finish
            enemyNotDone = false;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != nullptr && actor->handleEventScript != nullptr) {
                    if (does_script_exist(actor->handleEventScriptID)) {
                        enemyNotDone = true;
                    } else {
                        actor->handleEventScript = nullptr;
                    }
                }
            }
            if (enemyNotDone) {
                break;
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != nullptr) {
                    actor->flags &= ~ACTOR_FLAG_HEALTH_BAR_HIDDEN;
                }
            }

            if (battleStatus->stateFreezeCount != 0) {
                break;
            }

            if (gGameStatusPtr->demoBattleFlags & DEMO_BTL_FLAG_ENABLED) {
                btl_set_state(BATTLE_STATE_END_DEMO_BATTLE);
                break;
            }

            decrement_status_bar_disabled();
            gBattleStatus.flags1 |= BS_FLAGS1_SHOW_PLAYER_DECORATIONS;
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
            if (btl_check_player_defeated()) {
                return;
            }

            if ((battleStatus->moveCategory == BTL_MENU_TYPE_SMASH)
                && (battleStatus->selectedMoveID != MOVE_SMASH_CHARGE0)
                && (battleStatus->selectedMoveID != MOVE_SMASH_CHARGE)
                && (battleStatus->selectedMoveID != MOVE_SUPER_SMASH_CHARGE)
            ) {
                gBattleStatus.flags1 &= ~BS_FLAGS1_HAMMER_CHARGED;
            }

            if ((battleStatus->moveCategory == BTL_MENU_TYPE_JUMP)
                && (battleStatus->selectedMoveID != MOVE_JUMP_CHARGE0)
                && (battleStatus->selectedMoveID != MOVE_JUMP_CHARGE)
                && (battleStatus->selectedMoveID != MOVE_SUPER_JUMP_CHARGE)
            ) {
                gBattleStatus.flags1 &= ~BS_FLAGS1_JUMP_CHARGED;
            }

            if (!(gBattleStatus.flags1 & BS_FLAGS1_JUMP_CHARGED)) {
                battleStatus->jumpCharge = 0;
            }
            if (!(gBattleStatus.flags1 & BS_FLAGS1_HAMMER_CHARGED)) {
                battleStatus->hammerCharge = 0;
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != nullptr && !(actor->flags & ACTOR_FLAG_NO_DMG_APPLY)) {
                    actor->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
                }
            }

            btl_update_ko_status();

            enemyNotDone = false;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != nullptr) {
                    if (actor->statusAfflicted != 0) {
                        enemyNotDone = true;
                        break;
                    }
                }
            }

            if (!enemyNotDone) {
                gBattleSubState = BTL_SUBSTATE_CHECK_PLAYER_STATUS;
            } else {
                btl_cam_use_preset(BTL_CAM_VIEW_ENEMIES);
                switch (actor->statusAfflicted) {
                    case STATUS_KEY_DIZZY:
                        messageIndex = BTL_MSG_ENEMY_DAZED;
                        break;
                    case STATUS_KEY_SLEEP:
                        messageIndex = BTL_MSG_ENEMY_ASLEEP;
                        break;
                    case STATUS_KEY_FROZEN:
                        messageIndex = BTL_MSG_ENEMY_FROZEN;
                        break;
                    case STATUS_KEY_POISON:
                        messageIndex = BTL_MSG_ENEMY_POISONED;
                        break;
                    case STATUS_KEY_SHRINK:
                        messageIndex = BTL_MSG_ENEMY_SHRUNK;
                        break;
                    case STATUS_KEY_PARALYZE:
                        messageIndex = BTL_MSG_ENEMY_PARALYZED;
                        break;
                    case STATUS_KEY_STATIC:
                        messageIndex = BTL_MSG_ENEMY_ELECTRIFIED;
                        break;
                    case STATUS_KEY_STOP:
                        messageIndex = BTL_MSG_ENEMY_CANT_MOVE;
                        break;
                    default:
                        messageIndex = 0;
                        gBattleSubState = BTL_SUBSTATE_CHECK_PLAYER_STATUS;
                        break;
                }
                sfx_play_sound(SOUND_INFLICT_KO);
                btl_show_battle_message(messageIndex, 60);
                for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                    actor = battleStatus->enemyActors[i];
                    if (actor != nullptr) {
                        actor->statusAfflicted = 0;
                    }
                }
                gBattleSubState = BTL_SUBSTATE_AWAIT_ENEMY_STATUS_POPUP;
            }
            break;
        case BTL_SUBSTATE_AWAIT_ENEMY_STATUS_POPUP:
            if (!btl_is_popup_displayed()) {
                btl_cam_use_preset(BTL_CAM_DEFAULT);
                btl_cam_move(15);
                BattleSubstateDelay = 10;
                gBattleSubState = BTL_SUBSTATE_POST_ENEMY_STATUS_POPUP;
            }
            break;
        case BTL_SUBSTATE_POST_ENEMY_STATUS_POPUP:
            if (BattleSubstateDelay != 0) {
                BattleSubstateDelay--;
            } else {
                gBattleSubState = BTL_SUBSTATE_CHECK_PLAYER_STATUS;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_CHECK_PLAYER_STATUS:
            if (player->statusAfflicted != 0) {
                btl_cam_use_preset(BTL_CAM_PLAYER_STATUS_AFFLICTED);
                switch (player->statusAfflicted) {
                    case STATUS_KEY_DIZZY:
                        messageIndex = BTL_MSG_PLAYER_DAZED;
                        break;
                    case STATUS_KEY_SLEEP:
                        messageIndex = BTL_MSG_PLAYER_ASLEEP;
                        break;
                    case STATUS_KEY_FROZEN:
                        messageIndex = BTL_MSG_PLAYER_FROZEN;
                        break;
                    case STATUS_KEY_POISON:
                        messageIndex = BTL_MSG_PLAYER_POISONED;
                        break;
                    case STATUS_KEY_SHRINK:
                        messageIndex = BTL_MSG_PLAYER_SHRUNK;
                        break;
                    case STATUS_KEY_PARALYZE:
                        messageIndex = BTL_MSG_PLAYER_PARALYZED;
                        break;
                    case STATUS_KEY_STATIC:
                        messageIndex = BTL_MSG_PLAYER_CHARGED;
                        break;
                    default:
                        messageIndex = 0;
                        gBattleSubState = BTL_SUBSTATE_AWAIT_DONE;
                        break;
                }
                btl_show_battle_message(messageIndex, 60);
                player->statusAfflicted = 0;
                player->disableDismissTimer = 0;
                player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
                gBattleSubState = BTL_SUBSTATE_AWAIT_PLAYER_STATUS_POPUP;

            } else {
                gBattleSubState = BTL_SUBSTATE_AWAIT_DONE;
            }
            break;
        case BTL_SUBSTATE_AWAIT_PLAYER_STATUS_POPUP:
            if (!btl_is_popup_displayed()) {
                btl_cam_use_preset(BTL_CAM_DEFAULT);
                btl_cam_move(15);
                BattleSubstateDelay = 10;
                gBattleSubState = BTL_SUBSTATE_POST_PLAYER_STATUS_POPUP;
            }
            break;
        case BTL_SUBSTATE_POST_PLAYER_STATUS_POPUP:
            if (BattleSubstateDelay != 0) {
                BattleSubstateDelay--;
            } else {
                gBattleSubState = BTL_SUBSTATE_AWAIT_DONE;
            }
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_AWAIT_DONE) {
        if (player->takeTurnScript == nullptr || !does_script_exist(player->takeTurnScriptID)) {
            player->takeTurnScript = nullptr;
            CALL_EVENT(OnStatusTick, player, STATUS_PHASE_ACTION_END);
            CALL_EVENT(OnBattleMoveEnd, player);
            btl_set_state(BATTLE_STATE_END_PLAYER_TURN);
        }
    }
}

void btl_state_draw_player_move(void) {
}
