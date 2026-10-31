#include "states.h"

enum {
    BTL_SUBSTATE_EXECUTE                        = 0,
    BTL_SUBSTATE_UNUSED_1                       = 1,
    BTL_SUBSTATE_AWAIT_SCRIPTS                  = 2,
    BTL_SUBSTATE_AWAIT_PLAYER_POPUP_DONE        = 11, // wait for popups regarding player status to finish
    BTL_SUBSTATE_POST_PLAYER_POPUP_DELAY        = 12, // a brief delay after the popup vanishes
    BTL_SUBSTATE_CHECK_PARTNER                  = 20,
    BTL_SUBSTATE_AWAIT_PARTNER_POPUP_DONE       = 21, // wait for popups regarding partner status to finish
    BTL_SUBSTATE_POST_PARTNER_POPUP_DELAY       = 22, // a brief delay after the popup vanishes
    BTL_SUBSTATE_DONE                           = 30,
};

void btl_state_update_enemy_move(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = gBattleStatus.playerActor;
    Actor* partner = gBattleStatus.partnerActor;
    Actor* enemy;
    s32 i;

    Evt* script;
    s32 messageIndex;
    s32 waitingForEnemyScript;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_EXECUTE:
        case BTL_SUBSTATE_UNUSED_1:
            gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;
            gBattleStatus.flags1 &= ~BS_FLAGS1_YIELD_TURN;
            player->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            if (partner != nullptr) {
                partner->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            }
            battleStatus->stateFreezeCount = 0;
            battleStatus->lastAttackDamage = 0;
            battleStatus->actionQuality = 0;
            battleStatus->actionResult = ACTION_RESULT_NONE;
            battleStatus->blockResult = BLOCK_RESULT_NONE;
            battleStatus->curDamageSource = DMG_SRC_DEFAULT;
            reset_actor_turn_info();
            gBattleStatus.flags1 |= BS_FLAGS1_EXECUTING_MOVE;
            player->statusAfflicted = 0;
            if (partner != nullptr) {
                partner->statusAfflicted = 0;
            }

            gBattleStatus.flags2 |= BS_FLAGS2_IGNORE_DARKNESS;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != nullptr) {
                    enemy->flags &= ~ACTOR_FLAG_HEALTH_BAR_HIDDEN;
                }
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != nullptr) {
                    if (!(enemy->flags & ACTOR_FLAG_NO_DMG_APPLY)) {
                        enemy->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
                    }
                }
            }

            enemy = battleStatus->curTurnEnemy;
            if (!(enemy->flags & ACTOR_FLAG_NO_ATTACK)) {
                reset_all_actor_sounds(enemy);
                battleStatus->battlePhase = PHASE_EXECUTE_ACTION;
                EvtScript* takeTurnSource = enemy->takeTurnSource;
                CALL_EVENT(OnEnemyTakeTurnScript, enemy, &takeTurnSource);
                script = start_script(takeTurnSource, EVT_PRIORITY_A, 0);
                enemy->takeTurnScript = script;
                enemy->takeTurnScriptID = script->id;
                script->owner1.actorID = battleStatus->activeEnemyActorID;
            }
            gBattleSubState = BTL_SUBSTATE_AWAIT_SCRIPTS;
            break;
        case BTL_SUBSTATE_AWAIT_SCRIPTS:
            if (player->takeTurnScript != nullptr && does_script_exist(player->takeTurnScriptID)) {
                break;
            }
            player->takeTurnScript = nullptr;

            if (player->handleEventScript != nullptr && does_script_exist(player->handleEventScriptID)) {
                break;
            }
            player->handleEventScript = nullptr;

            if (partner != nullptr) {
                if (partner->handleEventScript != nullptr && does_script_exist(partner->handleEventScriptID)) {
                    break;
                }
                partner->handleEventScript = nullptr;
            }

            waitingForEnemyScript = false;
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != nullptr && enemy->handleEventScript != nullptr) {
                    if (does_script_exist(enemy->handleEventScriptID)) {
                        waitingForEnemyScript = true;
                    } else {
                        enemy->handleEventScript = nullptr;
                    }
                }
            }

            if (waitingForEnemyScript) {
                break;
            }

            if (btl_check_player_defeated()) {
                return;
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != nullptr && enemy->takeTurnScript != nullptr) {
                    if (does_script_exist(enemy->takeTurnScriptID)) {
                        waitingForEnemyScript = true;
                    } else {
                        enemy->takeTurnScript = nullptr;
                    }
                }
            }

            if (waitingForEnemyScript && !(gBattleStatus.flags1 & BS_FLAGS1_YIELD_TURN)) {
                break;
            }

            gBattleStatus.flags1 &= ~BS_FLAGS1_EXECUTING_MOVE;
            gBattleStatus.flags2 &= ~BS_FLAGS2_IGNORE_DARKNESS;
            if (btl_check_enemies_defeated()) {
                return;
            }

            if (battleStatus->stateFreezeCount != 0) {
                break;
            }

            if (gGameStatusPtr->demoBattleFlags & DEMO_BTL_FLAG_ENABLED) {
                btl_set_state(BATTLE_STATE_END_DEMO_BATTLE);
            } else {
                btl_update_ko_status();
                s32 afflictedStatus = player->statusAfflicted;
                s32 camPreset = BTL_CAM_PLAYER_STATUS_AFFLICTED;
                CALL_EVENT(OnStatusAfflictedNotice, player, partner, &afflictedStatus, &camPreset);
                if (camPreset < BTL_CAM_RESET || camPreset > BTL_CAM_STAR_SPIRIT) {
                    camPreset = BTL_CAM_PLAYER_STATUS_AFFLICTED;
                }
                if (afflictedStatus != 0) {
                    player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
                    if (partner != nullptr) {
                        partner->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
                    }
                    btl_cam_use_preset(camPreset);

                    switch (afflictedStatus) {
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
                        default:
                            messageIndex = 0;
                            gBattleSubState = BTL_SUBSTATE_CHECK_PARTNER;
                            break;
                    }
                    btl_show_battle_message(messageIndex, 60);
                    player->statusAfflicted = 0;
                    gBattleSubState = BTL_SUBSTATE_AWAIT_PLAYER_POPUP_DONE;
                    break;
                } else {
                    gBattleSubState = BTL_SUBSTATE_CHECK_PARTNER;
                    break;
                }
            }
            break;
        case BTL_SUBSTATE_AWAIT_PLAYER_POPUP_DONE:
            if (!btl_is_popup_displayed()) {
                btl_cam_use_preset(BTL_CAM_DEFAULT);
                btl_cam_move(15);
                BattleSubstateDelay = 10;
                gBattleSubState = BTL_SUBSTATE_POST_PLAYER_POPUP_DELAY;
            }
            break;
        case BTL_SUBSTATE_POST_PLAYER_POPUP_DELAY:
            if (BattleSubstateDelay != 0) {
                BattleSubstateDelay--;
            } else {
                gBattleSubState = BTL_SUBSTATE_CHECK_PARTNER;
                break;
            }
            break;
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_CHECK_PARTNER:
            if (partner != nullptr) {
                if (partner->statusAfflicted == STATUS_KEY_KO) {
                    player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
                    partner->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
                    btl_cam_use_preset(BTL_CAM_PARTNER_INJURED);
                    btl_show_battle_message(BTL_MSG_PARTNER_INJURED, 60);
                    partner->statusAfflicted = 0;
                    gBattleSubState = BTL_SUBSTATE_AWAIT_PARTNER_POPUP_DONE;
                } else {
                    gBattleSubState = BTL_SUBSTATE_DONE;
                }
            } else {
                gBattleSubState = BTL_SUBSTATE_DONE;
            }
            break;
        case BTL_SUBSTATE_AWAIT_PARTNER_POPUP_DONE:
            if (!btl_is_popup_displayed()) {
                btl_cam_use_preset(BTL_CAM_DEFAULT);
                btl_cam_move(15);
                BattleSubstateDelay = 10;
                gBattleSubState = BTL_SUBSTATE_POST_PARTNER_POPUP_DELAY;
            }
            break;
        case BTL_SUBSTATE_POST_PARTNER_POPUP_DELAY:
            if (BattleSubstateDelay != 0) {
                BattleSubstateDelay--;
            } else {
                gBattleSubState = BTL_SUBSTATE_DONE;
            }
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_DONE) {
        enemy = get_actor(battleStatus->activeEnemyActorID);
        if (enemy != nullptr) {
            CALL_EVENT(OnStatusTick, enemy, STATUS_PHASE_ACTION_END);
        }
        btl_set_state(BATTLE_STATE_NEXT_ENEMY);
    }
}

void btl_state_draw_enemy_move(void) {
}
