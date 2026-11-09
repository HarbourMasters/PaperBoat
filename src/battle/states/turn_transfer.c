#include "states.h"
#include "effects.h"
#include "script_api/battle.h"

enum {
    // BTL_SUBSTATE_INIT                = 0,
    BTL_SUBSTATE_RESET_ENEMIES          = 1,
    BTL_SUBSTATE_AWAIT_ALL              = 2,
    BTL_SUBSTATE_RESET_POSITIONS        = 3,
    BTL_SUBSTATE_TRY_MERLEE_DEF         = 4,
    BTL_SUBSTATE_NOTIFY_ENEMY_PHASE     = 5,
    BTL_SUBSTATE_AWAIT_ENEMY_PHASE      = 6,
    BTL_SUBSTATE_DONE                   = 7,
};

void btl_state_update_transfer_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Actor* actor;
    ActorState* state;
    Evt* script;
    s32 waitingForScript;
    s32 i;

    s32 oldKoDuration;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        if (!(gBattleStatus.flags2 & BS_FLAGS2_PLAYER_TURN_USED)) {
            btl_set_state(BATTLE_STATE_SWITCH_TO_PLAYER);
            return;
        }

        if (partner != nullptr) {
            if (!(gBattleStatus.flags2 & BS_FLAGS2_PARTNER_TURN_USED) && !(partner->flags & ACTOR_FLAG_NO_ATTACK)) {
                btl_set_state(BATTLE_STATE_SWITCH_TO_PARTNER);
                return;
            }
        }

        player->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
        player->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
        if (partner != nullptr) {
            partner->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            partner->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
        }

        gBattleSubState = BTL_SUBSTATE_RESET_ENEMIES;
        BattleStatusUpdateDelay = 0;
        gBattleStatus.flags2 &= ~BS_FLAGS2_PLAYER_TURN_USED;
        {
            s32 skipPartner = false;
            CALL_EVENT(OnTurnOrder, TURN_ORDER_SKIP_PARTNER_TURN, &skipPartner);
            if (!skipPartner) {
                gBattleStatus.flags2 &= ~BS_FLAGS2_PARTNER_TURN_USED;
            }
        }
        gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
        gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;
    }

    if (gBattleSubState == BTL_SUBSTATE_RESET_ENEMIES) {
        // await all enemy event scripts
        waitingForScript = false;
        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != nullptr && actor->handleEventScript != nullptr) {
                if (does_script_exist(actor->handleEventScriptID)) {
                    waitingForScript = true;
                } else {
                    actor->handleEventScript = nullptr;
                }
            }
        }
        if (waitingForScript) {
            return;
        }

        reset_actor_turn_info();

        // prepare each enemy actor for the coming turn
        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];

            if (actor == nullptr) {
                continue;
            }

            CALL_CANCELLABLE_EVENT(OnStatusTick, actor, STATUS_PHASE_ENEMY_TURN) {
                actor->flags |= ACTOR_FLAG_USING_IDLE_ANIM | ACTOR_FLAG_SHOW_STATUS_ICONS;
                actor->flags &= ~ACTOR_FLAG_SKIP_TURN;

                if (actor->debuff != 0) {
                    if (actor->debuff == STATUS_KEY_UNUSED
                        || actor->debuff == STATUS_KEY_DIZZY
                        || actor->debuff == STATUS_KEY_PARALYZE
                        || actor->debuff == STATUS_KEY_SLEEP
                        || actor->debuff == STATUS_KEY_FROZEN
                        || actor->debuff == STATUS_KEY_STOP
                    ) {
                        actor->flags |= ACTOR_FLAG_SKIP_TURN;
                    }
                    actor->debuffDuration--;
                    if (actor->debuffDuration <= 0) {
                        actor->debuff = 0;
                        remove_status_debuff(actor->hudElementDataIndex);
                        dispatch_event_actor(actor, EVENT_RECOVER_STATUS);
                        BattleStatusUpdateDelay = 20;
                    }
                }

                if (actor->staticStatus != 0) {
                    actor->staticDuration--;
                    if (actor->staticDuration <= 0) {
                        actor->staticStatus = 0;
                        remove_status_static(actor->hudElementDataIndex);
                        BattleStatusUpdateDelay = 20;
                    }
                }

                if (actor->transparentStatus != 0) {
                    actor->transparentDuration--;
                    if (actor->transparentDuration <= 0) {
                        actor->transparentStatus = 0;
                        remove_status_transparent(actor->hudElementDataIndex);
                        BattleStatusUpdateDelay = 20;
                    }
                }

                if (actor->stoneStatus != 0) {
                    actor->stoneDuration--;
                    if (actor->stoneDuration <= 0) {
                        actor->stoneStatus = 0;
                        BattleStatusUpdateDelay = 20;
                    }
                }

                oldKoDuration = actor->koDuration;
                actor->koDuration = actor->debuffDuration;
                if (actor->koDuration > 0) {
                    actor->koStatus = STATUS_KEY_KO;
                    actor->disableEffect->data.disableX->koDuration = actor->koDuration;
                } else if (oldKoDuration != actor->koDuration) {
                    actor->koStatus = 0;
                    actor->disableEffect->data.disableX->koDuration = 0;
                }
                if (actor->debuff == STATUS_KEY_POISON) {
                    gBattleStatus.flags1 |= BS_FLAGS1_TRIGGER_EVENTS;
                    dispatch_damage_event_actor_0(actor, 1, EVENT_HIT);
                    BattleStatusUpdateDelay = 20;
                }
            }
        }
        gBattleSubState = BTL_SUBSTATE_AWAIT_ALL;
    }

    if (gBattleSubState == BTL_SUBSTATE_AWAIT_ALL) {
        // wait for player HandleEvent script to finish
        if(player->handleEventScript != nullptr) {
            if (does_script_exist(player->handleEventScriptID)) {
                return;
            } else {
                player->handleEventScript = nullptr;
            }
        }

        // wait for partner HandleEvent script to finish
        if (partner != nullptr) {
            if (partner->handleEventScript != nullptr) {
                if (does_script_exist(partner->handleEventScriptID)) {
                    return;
                } else {
                    partner->handleEventScript = nullptr;
                }
            }
        }

        // wait for all enemy HandleEvent scripts to finish
        waitingForScript = false;
        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != nullptr && actor->handleEventScript != nullptr) {
                if (does_script_exist(actor->handleEventScriptID)) {
                    waitingForScript = true;
                } else {
                    actor->handleEventScript = nullptr;
                }
            }
        }
        if (waitingForScript) {
            return;
        }

        if (btl_check_player_defeated() || btl_check_enemies_defeated()) {
            return;
        }

        btl_cam_use_preset(BTL_CAM_DEFAULT);

        s32 swapToFront = partner != nullptr && (gBattleStatus.flags1 & BS_FLAGS1_PLAYER_IN_BACK)
            && !(gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE);
        if (swapToFront) {
            CALL_EVENT(OnTurnOrder, TURN_ORDER_PLAYER_IN_FRONT, &swapToFront);
        }
        if (!swapToFront) {
            gBattleSubState = BTL_SUBSTATE_TRY_MERLEE_DEF;
        } else {
            player->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            partner->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            player->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
            partner->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
            state = &partner->state;
            if (!battleStatus->outtaSightActive) {
                partner->state.curPos.x = partner->homePos.x;
                partner->state.curPos.z = partner->homePos.z;
                partner->state.goalPos.x = player->homePos.x;
                partner->state.goalPos.z = player->homePos.z;
            } else {
                partner->state.curPos.x = partner->homePos.x;
                partner->state.curPos.z = partner->homePos.z;
                partner->state.goalPos.x = partner->homePos.x;
                partner->state.goalPos.z = partner->homePos.z + 5.0f;
                partner->homePos.x = player->homePos.x;
                partner->homePos.z = player->homePos.z;
            }
            state->moveTime = 4;
            state->angle = 0.0f;
            gBattleSubState = BTL_SUBSTATE_RESET_POSITIONS;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_RESET_POSITIONS) {
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
            if (!battleStatus->outtaSightActive) {
                partner->homePos.x = partner->curPos.x;
                partner->homePos.z = partner->curPos.z;
                player->homePos.x = player->curPos.x;
                player->homePos.z = player->curPos.z;
            } else {
                player->homePos.x = player->curPos.x;
                player->homePos.z = player->curPos.z;
            }
            gBattleSubState = BTL_SUBSTATE_TRY_MERLEE_DEF;
            gBattleStatus.flags1 &= ~BS_FLAGS1_PLAYER_IN_BACK;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_TRY_MERLEE_DEF) {
        if (BattleStatusUpdateDelay != 0) {
            BattleStatusUpdateDelay--;
            return;
        }

        if (battleStatus->nextMerleeSpellType == MERLEE_SPELL_DEF_BOOST) {
            battleStatus->merleeDefenseBoost = 3;
            battleStatus->nextMerleeSpellType = MERLEE_SPELL_NONE;
            battleStatus->battlePhase = PHASE_MERLEE_DEFENSE_BONUS;
            script = start_script(&EVS_Mario_HandlePhase, EVT_PRIORITY_A, 0);
            player->takeTurnScript = script;
            player->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PLAYER;
        }
        gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;
        player->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
        player->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
        if (partner != nullptr) {
            partner->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            partner->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
        }
        gBattleSubState = BTL_SUBSTATE_NOTIFY_ENEMY_PHASE;
        gBattleStatus.flags2 &= ~BS_FLAGS2_PLAYER_TURN_USED;
        {
            s32 skipPartner = false;
            CALL_EVENT(OnTurnOrder, TURN_ORDER_SKIP_PARTNER_TURN, &skipPartner);
            if (!skipPartner) {
                gBattleStatus.flags2 &= ~BS_FLAGS2_PARTNER_TURN_USED;
            }
        }
        gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
        gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;
    }

    if (gBattleSubState == BTL_SUBSTATE_NOTIFY_ENEMY_PHASE) {
        // potentially wait for the merlee script to end
        if (player->takeTurnScript != nullptr) {
            if (does_script_exist(player->takeTurnScriptID)) {
                return;
            } else {
                player->takeTurnScript = nullptr;
            }
        }

        // initiate all enemy PHASE_PLAYER_END scripts
        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            if (actor != nullptr && actor->handlePhaseSource != nullptr) {
                battleStatus->battlePhase = PHASE_PLAYER_END;
                script = start_script(actor->handlePhaseSource, EVT_PRIORITY_A, 0);
                actor->handlePhaseScript = script;
                actor->handlePhaseScriptID = script->id;
                script->owner1.enemyID = i | ACTOR_CLASS_ENEMY;
            }
        }

        gBattleSubState = BTL_SUBSTATE_AWAIT_ENEMY_PHASE;
    }

    if (gBattleSubState == BTL_SUBSTATE_AWAIT_ENEMY_PHASE) {
        // await all the enemy PHASE_PLAYER_END scripts
        waitingForScript = false;
        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            actor = battleStatus->enemyActors[i];
            // interesting: this condition checks for handlePhaseSource instead of handlePhaseScript,
            // which is the expected pattern. result: handlePhaseScript is never nullptr'd. minor bug?
            if (actor != nullptr && actor->handlePhaseSource != nullptr) {
                if (does_script_exist(actor->handlePhaseScriptID)) {
                    waitingForScript = true;
                }
            }
        }
        if (waitingForScript) {
            return;
        }

        gBattleSubState = BTL_SUBSTATE_DONE;
    }

    if (gBattleSubState == BTL_SUBSTATE_DONE) {
        btl_set_state(BATTLE_STATE_NEXT_ENEMY);
    }
}

void btl_state_draw_transfer_turn(void) {
}
