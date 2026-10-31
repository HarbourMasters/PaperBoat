#include "states.h"
#include "script_api/battle.h"

enum {
    // BTL_SUBSTATE_INIT            = 0,
    BTL_SUBSTATE_AWAIT_RECOVER      = 5,
    BTL_SUBSTATE_AWAIT_SWAP         = 6,
    BTL_SUBSTATE_DONE               = 10,
};

void btl_substate_try_hpfp_recovery(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Evt* script;

    s32 drainRecovery = 0;
    s32 hpRecovery = 0;
    s32 fpRecovery = 0;

    if (battleStatus->moveCategory == BTL_MENU_TYPE_ITEMS && battleStatus->itemUsesLeft >= 2) {
        return;
    }

    if (player->stoneStatus == STATUS_KEY_STONE || battleStatus->outtaSightActive) {
        return;
    }

    if (gBattleStatus.flags2 & BS_FLAGS2_HAS_DRAINED_HP) {
        drainRecovery = battleStatus->hpDrainCount;
        CALL_EVENT(OnAbilityEffect, player, ABILITY_HP_DRAIN, &drainRecovery);
        battleStatus->hpDrainCount = 0;
    }
    gBattleStatus.flags2 &= ~BS_FLAGS2_HAS_DRAINED_HP;

    if (rand_int(100) < 50) {
        hpRecovery += is_ability_active(ABILITY_CRAZY_HEART) * 3;
    }
    if (rand_int(100) < 50) {
        hpRecovery += is_ability_active(ABILITY_HAPPY_HEART);
    }
    if (rand_int(100) < 50) {
        fpRecovery += is_ability_active(ABILITY_HAPPY_FLOWER);
    }
    CALL_EVENT(OnTurnEndRecovery, player, &drainRecovery, &hpRecovery, &fpRecovery);
    if (drainRecovery + hpRecovery + fpRecovery == 0) {
        return;
    }

    battleStatus->battlePhase = PHASE_PLAYER_HAPPY;
    script = start_script(&EVS_Mario_HandlePhase, EVT_PRIORITY_A, 0);
    player->takeTurnScript = script;
    player->takeTurnScriptID = script->id;
    script->owner1.actorID = ACTOR_PLAYER;

    script->varTable[10] = drainRecovery;
    script->varTable[11] = hpRecovery;
    script->varTable[12] = fpRecovery;

    if (script->varTable[10] > 99) {
        script->varTable[10] = 99;
    }
    if (script->varTable[11] > 99) {
        script->varTable[11] = 99;
    }
    if (script->varTable[12] > 99) {
        script->varTable[12] = 99;
    }
}

void btl_state_update_end_player_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        btl_substate_try_hpfp_recovery();
        gBattleSubState = BTL_SUBSTATE_AWAIT_RECOVER;
    }

    if (gBattleSubState == BTL_SUBSTATE_AWAIT_RECOVER) {
        // if a script is running from 'Happy!', wait for it to complete
        if (player->takeTurnScript != nullptr && does_script_exist(player->takeTurnScriptID)) {
            return;
        }
        player->takeTurnScript = nullptr;

        // force peach to back position after turn end
        s32 doSwap = (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) && !(gBattleStatus.flags1 & BS_FLAGS1_PLAYER_IN_BACK);
        if (doSwap) {
            s32 inFront = false;
            CALL_EVENT(OnTurnOrder, TURN_ORDER_PLAYER_IN_FRONT, &inFront);
            doSwap = !inFront;
        }
        if (doSwap) {
            player->state.curPos.x = player->homePos.x;
            player->state.curPos.z = player->homePos.z;
            player->state.goalPos.x = partner->homePos.x;
            player->state.goalPos.z = partner->homePos.z;
            player->state.moveTime = 4;
            player->state.angle = 0.0f;
            gBattleSubState = BTL_SUBSTATE_AWAIT_SWAP;
        } else {
            gBattleSubState = BTL_SUBSTATE_DONE;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_AWAIT_SWAP) {
        if (player->state.moveTime != 0) {
            player->curPos.x += (player->state.goalPos.x - player->curPos.x) / player->state.moveTime;
            player->curPos.z += (player->state.goalPos.z - player->curPos.z) / player->state.moveTime;
            partner->curPos.x += (player->state.curPos.x - partner->curPos.x) / player->state.moveTime;
            partner->curPos.z += (player->state.curPos.z - partner->curPos.z) / player->state.moveTime;
        }
        player->curPos.z += sin_rad(DEG_TO_RAD(player->state.angle)) * 16.0f;
        player->yaw = clamp_angle(-player->state.angle);
        partner->curPos.z -= sin_rad(DEG_TO_RAD(player->state.angle)) * 16.0f;
        partner->yaw = clamp_angle(-player->state.angle);
        player->state.angle += 90.0f;

        if (player->state.moveTime != 0) {
            player->state.moveTime--;
        } else {
            player->curPos.x = player->state.goalPos.x;
            player->curPos.z = player->state.goalPos.z;
            partner->curPos.x = player->state.curPos.x;
            partner->curPos.z = player->state.curPos.z;
            player->homePos.x = player->curPos.x;
            player->homePos.z = player->curPos.z;
            partner->homePos.x = partner->curPos.x;
            partner->homePos.z = partner->curPos.z;
            gBattleStatus.flags1 |= BS_FLAGS1_PLAYER_IN_BACK;
            gBattleSubState = BTL_SUBSTATE_DONE;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_DONE) {
        // dont bother with command loss if all enemies are defeated
        if(btl_check_enemies_defeated()) {
            return;
        }

        if (battleStatus->moveCategory == BTL_MENU_TYPE_ITEMS && battleStatus->itemUsesLeft >= 2) {
            btl_cam_use_preset(BTL_CAM_DEFAULT);
            btl_cam_move(10);
            gBattleStatus.flags2 &= ~BS_FLAGS2_PLAYER_TURN_USED;
        } else {
            gBattleStatus.flags2 |= BS_FLAGS2_PLAYER_TURN_USED;
        }

        // if the rest of the turn was canceled, proceed immediately to END_TURN
        if (battleStatus->cancelTurnMode < 0) {
            battleStatus->cancelTurnMode = 0;
            battleStatus->itemUsesLeft = 0;
            btl_set_state(BATTLE_STATE_END_TURN);
            return;
        }

        if (battleStatus->itemUsesLeft != 0) {
            battleStatus->itemUsesLeft--;
            if (battleStatus->itemUsesLeft != 0) {
                // double or triple dip has not run out yet, let the player choose another item
                btl_set_state(BATTLE_STATE_PREPARE_MENU);
                gBattleSubState = BTL_SUBSTATE_PLAYER_CONTINUE_DIP;
                return;
            }

            if (gBattleStatus.flags1 & BS_FLAGS1_HUSTLED) {
                if (battleStatus->hustleTurns != 0) {
                    battleStatus->hustleTurns--;
                }
            }

            if (battleStatus->hustleTurns != 0 && (gBattleStatus.flags1 & BS_FLAGS1_HUSTLED)) {
                gBattleStatus.flags2 &= ~BS_FLAGS2_PLAYER_TURN_USED;
                btl_set_state(BATTLE_STATE_PREPARE_MENU);
                return;
            } else {
                gBattleStatus.flags1 &= ~BS_FLAGS1_HUSTLED;
                btl_set_state(BATTLE_STATE_BEGIN_PARTNER_TURN);
                return;
            }
        }

        if (gBattleStatus.flags1 & BS_FLAGS1_HUSTLED) {
            if (battleStatus->hustleTurns != 0) {
                battleStatus->hustleTurns--;
            }
        }

        s32 reopenMenu = false;
        if (battleStatus->hustleTurns != 0) {
            s32 who = (gBattleStatus.flags1 & BS_FLAGS1_HUSTLED) ? ACTOR_CLASS_PLAYER : ACTOR_CLASS_PARTNER;
            CALL_EVENT(OnTurnOrder, TURN_ORDER_WHO_ACTS_FIRST, &who);
            reopenMenu = who == ACTOR_CLASS_PLAYER;
        }

        if (reopenMenu) {
            gBattleStatus.flags2 &= ~BS_FLAGS2_PLAYER_TURN_USED;
            btl_set_state(BATTLE_STATE_PREPARE_MENU);
        } else {
            gBattleStatus.flags1 &= ~BS_FLAGS2_HAS_DRAINED_HP;
            if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                btl_set_state(BATTLE_STATE_TRANSFER_TURN);
            } else {
                btl_set_state(BATTLE_STATE_BEGIN_PARTNER_TURN);
            }
        }
    }
}

void btl_state_draw_end_player_turn(void) {
}
