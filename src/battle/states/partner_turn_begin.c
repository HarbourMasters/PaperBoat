#include "states.h"
#include "effects.h"

enum {
    // BTL_SUBSTATE_INIT                = 0,
    BTL_SUBSTATE_AWAIT_RECOVER_DONE     = 1,
    BTL_SUBSTATE_EXEC_TURN_SCRIPT       = 8,
    BTL_SUBSTATE_AWAIT_TURN_SCRIPT      = 9,
    BTL_SUBSTATE_END_DELAY              = 10,
    BTL_SUBSTATE_RESET_STATE            = 100,
};

void btl_state_update_begin_partner_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* partner = battleStatus->partnerActor;
    Actor* enemy;
    Evt* script;
    s32 i;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        if (partner == nullptr) {
            BattleSkipActorTurn = true;
            gBattleSubState = BTL_SUBSTATE_END_DELAY;
        } else if ((battleStatus->flags2 & (BS_FLAGS2_PARTNER_TURN_USED | BS_FLAGS2_PLAYER_TURN_USED)) == (BS_FLAGS2_PARTNER_TURN_USED | BS_FLAGS2_PLAYER_TURN_USED)) {
            btl_set_state(BATTLE_STATE_TRANSFER_TURN);
            return;
        } else if (partner->flags & ACTOR_FLAG_NO_ATTACK) {
            btl_set_state(BATTLE_STATE_TRANSFER_TURN);
            return;
        } else {
            btl_cam_use_preset(BTL_CAM_DEFAULT);
            btl_cam_move(5);
            gBattleSubState = BTL_SUBSTATE_RESET_STATE;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_RESET_STATE) {
        if (btl_cam_is_moving_done()) {
            BattleStatusUpdateDelay = 0;
            reset_actor_turn_info();
            partner = battleStatus->partnerActor;
            battleStatus->actionResult = ACTION_RESULT_NONE;
            battleStatus->blockResult = BLOCK_RESULT_NONE;
            BattleSkipActorTurn = false;
            gBattleStatus.flags1 |= BS_FLAGS1_PARTNER_ACTING;
            {
                s32 inFront = !(gBattleStatus.flags1 & BS_FLAGS1_PLAYER_IN_BACK);
                CALL_EVENT(OnTurnOrder, TURN_ORDER_PLAYER_IN_FRONT, &inFront);
                if (inFront) {
                    gBattleStatus.flags1 &= ~BS_FLAGS1_PLAYER_IN_BACK;
                } else {
                    gBattleStatus.flags1 |= BS_FLAGS1_PLAYER_IN_BACK;
                }
            }
            gBattleStatus.flags2 |= BS_FLAGS1_PLAYER_IN_BACK;
            partner->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;

            if (partner->koStatus != 0) {
                CALL_CANCELLABLE_EVENT(OnStatusTick, partner, STATUS_PHASE_PARTNER_TURN) {
                    partner->koDuration--;
                    BattleSkipActorTurn = true;
                    BattleStatusUpdateDelay = 20;
                    if (partner->koDuration > 0) {
                        partner->disableEffect->data.disableX->koDuration = partner->koDuration;
                    } else {
                        partner->koStatus = 0;
                        dispatch_event_partner(EVENT_RECOVER_FROM_KO);
                        partner->disableEffect->data.disableX->koDuration = 0;
                        gBattleStatus.flags2 |= BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
                    }
                }
            }
            {
                s32 skipTurn = BattleSkipActorTurn;
                CALL_EVENT(OnTurnOrder, TURN_ORDER_SKIP_PARTNER_TURN, &skipTurn);
                BattleSkipActorTurn = skipTurn;
            }

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != nullptr) {
                    enemy->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
                }
            }
            gBattleSubState = BTL_SUBSTATE_AWAIT_RECOVER_DONE;
        }
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_AWAIT_RECOVER_DONE:
            if (partner != nullptr) {
                if (partner->handleEventScript != nullptr && does_script_exist(partner->handleEventScriptID)) {
                    break;
                }
                partner->handleEventScript = nullptr;
            }

            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
            if (btl_check_player_defeated() || btl_check_enemies_defeated()) {
                return;
            }
            gBattleSubState = BTL_SUBSTATE_EXEC_TURN_SCRIPT;
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_EXEC_TURN_SCRIPT) {
        if (partner->handlePhaseSource != nullptr) {
            battleStatus->battlePhase = PHASE_ENEMY_BEGIN;
            script = start_script(partner->handlePhaseSource, EVT_PRIORITY_A, 0);
            partner->handlePhaseScript = script;
            partner->handlePhaseScriptID = script->id;
            script->owner1.actorID = ACTOR_PARTNER;
        }
        gBattleSubState = BTL_SUBSTATE_AWAIT_TURN_SCRIPT;
    }

    if (gBattleSubState == BTL_SUBSTATE_AWAIT_TURN_SCRIPT) {
        if (partner->handlePhaseSource == nullptr || !does_script_exist(partner->handlePhaseScriptID)) {
            gBattleSubState = BTL_SUBSTATE_END_DELAY;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_END_DELAY) {
        if (BattleStatusUpdateDelay != 0) {
            BattleStatusUpdateDelay--;
            return;
        }
        gBattleStatus.flags2 &= ~BS_FLAGS2_NO_PLAYER_PAL_ADJUST;
        if (BattleSkipActorTurn) {
            gBattleStatus.flags2 |= BS_FLAGS2_PARTNER_TURN_USED;
            btl_set_state(BATTLE_STATE_TRANSFER_TURN);
        } else {
            btl_set_state(BATTLE_STATE_SWITCH_TO_PARTNER);
        }
    }
}

void btl_state_draw_begin_partner_turn(void) {
}
