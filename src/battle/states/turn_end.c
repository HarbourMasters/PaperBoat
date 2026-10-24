#include "states.h"

enum {
    // BTL_SUBSTATE_INIT                    = 0,
    BTL_SUBSTATE_CHECK_FOR_SWAP             = 1,
    BTL_SUBSTATE_AWAIT_SCRIPTS              = 2,
    BTL_SUBSTATE_BEGIN_NEXT                 = 3,
    BTL_SUBSTATE_UNUSED_4                   = 4,
    BTL_SUBSTATE_PERFORM_SWAP               = 11,
    BTL_SUBSTATE_START_SCRIPTS              = 12,
};

void btl_state_update_end_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Actor* actor;
    Evt* script;
    s32 i;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        s32 cond = false;

        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != nullptr && actor->handleEventScript != nullptr) {
                if (does_script_exist(actor->handleEventScriptID)) {
                    cond = true;
                } else {
                    actor->handleEventScript = nullptr;
                }
            }
        }

        if (!cond) {
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                actor = battleStatus->enemyActors[i];
                if (actor != nullptr && actor->takeTurnScript != nullptr) {
                    if (does_script_exist(actor->takeTurnScriptID)) {
                        cond = true;
                    } else {
                        actor->takeTurnScript = nullptr;
                    }
                }
            }

            if (!cond) {
                btl_cam_use_preset(BTL_CAM_DEFAULT);
                gBattleSubState = BTL_SUBSTATE_CHECK_FOR_SWAP;
            }
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_CHECK_FOR_SWAP) {
        if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
            gBattleSubState = BTL_SUBSTATE_START_SCRIPTS;
        } else if (!(gBattleStatus.flags1 & BS_FLAGS1_PLAYER_IN_BACK)) {
            gBattleSubState = BTL_SUBSTATE_START_SCRIPTS;
        } else {
            player->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            partner->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            player->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
            partner->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
            partner->state.curPos.x = partner->homePos.x;
            partner->state.curPos.z = partner->homePos.z;
            partner->state.goalPos.x = player->homePos.x;
            partner->state.goalPos.z = player->homePos.z;
            partner->state.moveTime = 4;
            partner->state.angle = 0.0f;
            gBattleSubState = BTL_SUBSTATE_PERFORM_SWAP;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_PERFORM_SWAP) {
        if (partner->state.moveTime != 0) {
            partner->curPos.x += (partner->state.goalPos.x - partner->curPos.x) / partner->state.moveTime;
            partner->curPos.z += (partner->state.goalPos.z - partner->curPos.z) / partner->state.moveTime;
            player->curPos.x += (partner->state.curPos.x - player->curPos.x) / partner->state.moveTime;
            player->curPos.z += (partner->state.curPos.z - player->curPos.z) / partner->state.moveTime;
        }
        partner->curPos.z -= sin_rad(DEG_TO_RAD(partner->state.angle)) * 16.0f;
        partner->yaw = clamp_angle(partner->state.angle);
        player->curPos.z += sin_rad(DEG_TO_RAD(partner->state.angle)) * 16.0f;
        player->yaw = clamp_angle(partner->state.angle);
        partner->state.angle += 90.0f;
        if (partner->state.moveTime != 0) {
            partner->state.moveTime--;
        } else {
            partner->curPos.x = partner->state.goalPos.x;
            partner->curPos.z = partner->state.goalPos.z;
            player->curPos.x = partner->state.curPos.x;
            player->curPos.z = partner->state.curPos.z;
            partner->homePos.x = partner->curPos.x;
            partner->homePos.z = partner->curPos.z;
            player->homePos.x = player->curPos.x;
            player->homePos.z = player->curPos.z;
            player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
            partner->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
            if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                gBattleStatus.flags1 |= BS_FLAGS1_PLAYER_IN_BACK;
            } else {
                gBattleStatus.flags1 &= ~BS_FLAGS1_PLAYER_IN_BACK;
            }
            gBattleSubState = BTL_SUBSTATE_START_SCRIPTS;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_START_SCRIPTS) {
        gBattleStatus.flags2 &= ~BS_FLAGS2_HIDE_BUFF_COUNTERS;
        {
            CALL_CANCELLABLE_EVENT(OnStatusTick, player, STATUS_PHASE_TURN_END) {
                player->disableDismissTimer = 0;
                player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
            }
        }
        if (partner != nullptr) {
            CALL_CANCELLABLE_EVENT(OnStatusTick, partner, STATUS_PHASE_TURN_END) {
                player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
                partner->disableDismissTimer = 0;
            }
        }

        btl_set_player_idle_anims();
        gBattleStatus.flags1 &= ~BS_FLAGS1_PLAYER_DEFENDING;
        s32 starPowerRegen = SP_PER_SEG;
        CALL_CANCELLABLE_EVENT(OnStarPowerRegen, &starPowerRegen) {
            playerData->starPower += starPowerRegen;
            if (playerData->starPower > playerData->maxStarPower * SP_PER_BAR) {
                playerData->starPower = playerData->maxStarPower * SP_PER_BAR;
            }
        }

        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != nullptr && actor->handlePhaseSource != nullptr) {
                battleStatus->battlePhase = PHASE_ENEMY_END;
                script = start_script(actor->handlePhaseSource, EVT_PRIORITY_A, 0);
                actor->handlePhaseScript = script;
                actor->handlePhaseScriptID = script->id;
                script->owner1.enemyID = i | ACTOR_ENEMY0;
            }
        }

        if (partner != nullptr && partner->handlePhaseSource != nullptr) {
            battleStatus->battlePhase = PHASE_ENEMY_END;
            script = start_script(partner->handlePhaseSource, EVT_PRIORITY_A, 0);
            partner->handlePhaseScript = script;
            partner->handlePhaseScriptID = script->id;
            script->owner1.actorID = ACTOR_PARTNER;
        }
        gBattleSubState = BTL_SUBSTATE_AWAIT_SCRIPTS;
    }

    // wait for all end turn scripts to finish executing
    if (gBattleSubState == BTL_SUBSTATE_AWAIT_SCRIPTS) {
        s32 waitingForScript = false;

        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != nullptr && actor->handlePhaseSource != nullptr && does_script_exist(actor->handlePhaseScriptID)) {
                waitingForScript = true;
            }
        }

        if (partner != nullptr && partner->handlePhaseSource != nullptr && does_script_exist(partner->handlePhaseScriptID)) {
            waitingForScript = true;
        }

        if (!waitingForScript) {
            btl_cam_use_preset(BTL_CAM_DEFAULT);
            gBattleSubState = BTL_SUBSTATE_BEGIN_NEXT;
        }
    }

    // proceed to next turn
    switch (gBattleSubState) {
        case BTL_SUBSTATE_BEGIN_NEXT:
        case BTL_SUBSTATE_UNUSED_4:
            btl_set_state(BATTLE_STATE_BEGIN_TURN);
            break;
    }
}

void btl_state_draw_end_turn(void) {
}
