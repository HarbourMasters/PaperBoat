#include "states.h"

enum {
    // BTL_SUBSTATE_INIT                        = 0,
    BTL_SUBSTATE_EXECUTE_MOVE                   = 2,
    BTL_SUBSTATE_HANDLE_RESULTS                 = 3,
    BTL_SUBSTATE_AWAIT_PARTNER_STATUS_POPUP     = 11,
    BTL_SUBSTATE_POST_PARTNER_STATUS_POPUP      = 12,
    BTL_SUBSTATE_CHECK_ENEMY_STATUS             = 20,
    BTL_SUBSTATE_AWAIT_ENEMY_STATUS_POPUP       = 21,
    BTL_SUBSTATE_POST_ENEMY_STATUS_POPUP        = 22,
    BTL_SUBSTATE_DONE                           = 30,
};

void btl_state_update_partner_move(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Actor* enemyActor;
    Evt* script;
    s32 enemyFound;
    s32 messageIndex;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            if (partner == nullptr) {
                btl_set_state(BATTLE_STATE_TRANSFER_TURN);
                break;
            }
            battleStatus->stateFreezeCount = 0;
            battleStatus->actionResult = ACTION_RESULT_NONE;
            battleStatus->blockResult = BLOCK_RESULT_NONE;
            battleStatus->curDamageSource = DMG_SRC_DEFAULT;
            gBattleStatus.flags1 &= ~BS_FLAGS1_AUTO_SUCCEED_ACTION;
            gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;
            reset_actor_turn_info();
            partner->statusAfflicted = 0;
            partner->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            player->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            deduct_current_move_fp();
            btl_cam_target_actor(ACTOR_PARTNER);
            gBattleStatus.flags2 |= BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;
            gBattleStatus.flags1 &= ~BS_FLAGS1_YIELD_TURN;

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemyActor = battleStatus->enemyActors[i];
                if (enemyActor != nullptr) {
                    enemyActor->statusAfflicted = 0;
                }
            }
            btl_cam_use_preset(BTL_CAM_DEFAULT);
            gBattleSubState = BTL_SUBSTATE_EXECUTE_MOVE;
            break;
        case BTL_SUBSTATE_EXECUTE_MOVE:
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemyActor = battleStatus->enemyActors[i];
                if (enemyActor != nullptr) {
                    enemyActor->flags &= ~ACTOR_FLAG_HEALTH_BAR_HIDDEN;
                    enemyActor->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
                }
            }

            increment_status_bar_disabled();
            gBattleStatus.flags1 |= BS_FLAGS1_EXECUTING_MOVE;
            reset_actor_turn_info();
            reset_all_actor_sounds(partner);
            battleStatus->battlePhase = PHASE_EXECUTE_ACTION;
            script = start_script(partner->takeTurnSource, EVT_PRIORITY_A, 0);
            partner->takeTurnScript = script;
            partner->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PARTNER;
            gBattleSubState = BTL_SUBSTATE_HANDLE_RESULTS;
            break;
        case BTL_SUBSTATE_HANDLE_RESULTS:
            if (!(gBattleStatus.flags1 & BS_FLAGS1_YIELD_TURN)) {
                if (partner->takeTurnScript != nullptr && does_script_exist(partner->takeTurnScriptID)) {
                    break;
                }
                partner->takeTurnScript = nullptr;
            }
            gBattleStatus.flags1 &= ~BS_FLAGS1_EXECUTING_MOVE;

            if (partner->handleEventScript != nullptr && does_script_exist(partner->handleEventScriptID)) {
                break;
            }
            partner->handleEventScript = nullptr;

            if (player->handleEventScript != nullptr && does_script_exist(player->handleEventScriptID)) {
                break;
            }
            player->handleEventScript = nullptr;

            enemyFound = false;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemyActor = battleStatus->enemyActors[i];
                if (enemyActor != nullptr && enemyActor->takeTurnScript != nullptr) {
                    if (does_script_exist(enemyActor->takeTurnScriptID)) {
                        enemyFound = true;
                    } else {
                        enemyActor->takeTurnScript = nullptr;
                    }
                }
            }
            if (enemyFound) {
                break;
            }

            enemyFound = false;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemyActor = battleStatus->enemyActors[i];
                if (enemyActor != nullptr && enemyActor->handleEventScript != nullptr) {
                    if (does_script_exist(enemyActor->handleEventScriptID)) {
                        enemyFound = true;
                    } else {
                        enemyActor->handleEventScript = nullptr;
                    }
                }
            }
            if (enemyFound) {
                break;
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemyActor = battleStatus->enemyActors[i];
                if (enemyActor != nullptr) {
                    enemyActor->flags &= ~ACTOR_FLAG_HEALTH_BAR_HIDDEN;
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
            if (playerData->curPartner == PARTNER_GOOMBARIO
                    && battleStatus->moveCategory == BTL_MENU_TYPE_CHANGE_PARTNER
                    && battleStatus->selectedMoveID != MOVE_CHARGE) {
                partner->isGlowing = false;
                gBattleStatus.flags1 &= ~BS_FLAGS1_GOOMBARIO_CHARGED;
            }
            if (btl_check_player_defeated()) {
                return;
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemyActor = battleStatus->enemyActors[i];
                if (enemyActor != nullptr) {
                    if (!(enemyActor->flags & ACTOR_FLAG_NO_DMG_APPLY)) {
                        enemyActor->flags |= (ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM);
                    }
                }
            }

            btl_update_ko_status();

            if (partner->statusAfflicted == STATUS_KEY_KO && !btl_are_all_enemies_defeated()) {
                btl_cam_use_preset(BTL_CAM_PARTNER_INJURED);
                btl_show_battle_message(BTL_MSG_PARTNER_INJURED, 60);
                partner->statusAfflicted = 0;
                partner->disableDismissTimer = 0;
                gBattleSubState = BTL_SUBSTATE_AWAIT_PARTNER_STATUS_POPUP;
                partner->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
            } else {
                gBattleSubState = BTL_SUBSTATE_CHECK_ENEMY_STATUS;
            }
            break;
        case BTL_SUBSTATE_AWAIT_PARTNER_STATUS_POPUP:
            if (btl_is_popup_displayed()) {
                break;
            }
            btl_cam_use_preset(BTL_CAM_DEFAULT);
            btl_cam_move(15);
            BattleSubstateDelay = 10;
            gBattleSubState = BTL_SUBSTATE_POST_PARTNER_STATUS_POPUP;
            break;
        case BTL_SUBSTATE_POST_PARTNER_STATUS_POPUP:
            if (BattleSubstateDelay != 0) {
                BattleSubstateDelay--;
            } else {
                gBattleSubState = BTL_SUBSTATE_CHECK_ENEMY_STATUS;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_CHECK_ENEMY_STATUS:
            enemyFound = false;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemyActor = battleStatus->enemyActors[i];
                if (enemyActor != nullptr) {
                    if (enemyActor->statusAfflicted != 0) {
                        enemyFound = true;
                        break;
                    }
                }
            }
            if (!enemyFound) {
                gBattleSubState = BTL_SUBSTATE_DONE;
                break;
            }

            btl_cam_use_preset(BTL_CAM_VIEW_ENEMIES);
            switch (enemyActor->statusAfflicted) {
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
                    gBattleSubState = BTL_SUBSTATE_CHECK_ENEMY_STATUS;
                    break;
            }

            sfx_play_sound(SOUND_INFLICT_KO);
            btl_show_battle_message(messageIndex, 60);

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemyActor = battleStatus->enemyActors[i];
                if (enemyActor != nullptr) {
                    enemyActor->statusAfflicted = 0;
                }
            }
            gBattleSubState = BTL_SUBSTATE_AWAIT_ENEMY_STATUS_POPUP;
            break;
        case BTL_SUBSTATE_AWAIT_ENEMY_STATUS_POPUP:
            if (btl_is_popup_displayed() == false) {
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
                gBattleSubState = BTL_SUBSTATE_DONE;
            }
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_DONE) {
        if (partner->takeTurnScript != nullptr && does_script_exist(partner->takeTurnScriptID)) {
            return;
        }
        partner->takeTurnScript = nullptr;
        CALL_EVENT(OnStatusTick, partner, STATUS_PHASE_ACTION_END);
        btl_set_state(BATTLE_STATE_END_PARTNER_TURN);
    }
}

void btl_state_draw_partner_move(void) {
}
