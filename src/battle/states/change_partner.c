#include "states.h"
#include "script_api/battle.h"

enum {
    // BTL_SUBSTATE_INIT                     = 0,
    BTL_SUBSTATE_EXEC_PUT_AWAY               = 2,
    BTL_SUBSTATE_LOAD_NEW_PARTNER            = 3,
    BTL_SUBSTATE_EXEC_BRING_OUT              = 4,
    BTL_SUBSTATE_EXEC_PHASE                  = 5,
    BTL_SUBSTATE_AWAIT_PHASE                 = 6,
    BTL_SUBSTATE_DONE                        = 7,
};

API_CALLABLE(EnablePartnerBlur) {
    enable_partner_blur();
    return ApiStatus_DONE2;
}

API_CALLABLE(DisablePartnerBlur) {
    disable_partner_blur();
    return ApiStatus_DONE2;
}

EvtScript EVS_BtlPutPartnerAway = {
    Call(DispatchEvent, ACTOR_PARTNER, EVENT_PUT_PARTNER_AWAY)
    ChildThread
        SetF(LVar0, Float(1.0))
        Loop(10)
            Call(SetActorScale, ACTOR_PARTNER, LVar0, LVar0, Float(1.0))
            SubF(LVar0, Float(0.1))
            Wait(1)
        EndLoop
    EndChildThread
    Call(EnablePartnerBlur)
    Call(PlaySoundAtActor, 0, SOUND_PARTNER_GET_OUT)
    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
    Add(LVar1, 25)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.0))
    Call(SetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_PARTNER, 10, 0, 0, 1)
    Call(DisablePartnerBlur)
    Return
    End
};

EvtScript EVS_BtlBringPartnerOut = {
    ChildThread
        SetF(LVar0, Float(0.1))
        Loop(20)
            Call(SetActorScale, ACTOR_PARTNER, LVar0, LVar0, Float(1.0))
            AddF(LVar0, Float(0.05))
            Wait(1)
        EndLoop
        Call(SetActorScale, ACTOR_PARTNER, Float(1.0), Float(1.0), Float(1.0))
    EndChildThread
    Call(PlaySoundAtActor, 0, SOUND_PARTNER_PUT_AWAY)
    Call(GetGoalPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, ACTOR_PARTNER, Float(1.0))
    Call(JumpToGoal, ACTOR_PARTNER, 20, 0, 0, 1)
    Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
    Return
    End
};

void btl_state_update_change_partner(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Actor* enemyActor;
    Evt* script;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            {
                CALL_EVENT(OnPartnerChange, PARTNER_CHANGE_LEAVE, gPlayerData.curPartner);
            }
            player->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            partner->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            battleStatus->stateFreezeCount = 0;
            gBattleStatus.flags2 |= BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;
            btl_cam_use_preset(BTL_CAM_REPOSITION);
            btl_cam_set_target_pos(-89.0, 40.0, -99.0);
            btl_cam_set_zoom(372);
            btl_cam_set_zoffset(0);
            gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemyActor = battleStatus->enemyActors[i];
                if (enemyActor != nullptr) {
                    enemyActor->flags &= ~ACTOR_FLAG_HEALTH_BAR_HIDDEN;
                    enemyActor->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
                }
            }

            battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_MAIN] = -1;
            BattleSubstateDelay = 10;
            gBattleSubState = BTL_SUBSTATE_EXEC_PUT_AWAY;

            // fallthrough
        case BTL_SUBSTATE_EXEC_PUT_AWAY:
            if (BattleSubstateDelay != 0) {
                BattleSubstateDelay--;
                break;
            }
            deduct_current_move_fp();
            script = start_script(&EVS_BtlPutPartnerAway, EVT_PRIORITY_A, 0);
            battleStatus->controlScript = script;
            battleStatus->controlScriptID = script->id;
            script->owner1.actorID = ACTOR_PARTNER;
            player->state.unk_18.x = partner->curPos.x;
            player->state.unk_18.y = 0.0f;
            player->state.unk_18.z = partner->curPos.z;
            gBattleSubState = BTL_SUBSTATE_LOAD_NEW_PARTNER;
            break;
        case BTL_SUBSTATE_LOAD_NEW_PARTNER:
            if (does_script_exist(battleStatus->controlScriptID)) {
                break;
            }
            btl_delete_actor(partner);
            gPlayerData.curPartner = battleStatus->lastSelectedPartner;
            load_partner_actor();
            partner = battleStatus->partnerActor;
            partner->scale.x = 0.1f;
            partner->scale.y = 0.1f;
            partner->scale.z = 0.1f;
            partner->state.goalPos.x = player->state.unk_18.x;
            partner->state.goalPos.y = partner->curPos.y;
            partner->state.goalPos.z = player->state.unk_18.z;
            partner->curPos.x = player->curPos.x;
            partner->curPos.y = player->curPos.y + 25.0f;
            partner->curPos.z = player->curPos.z;
            gBattleSubState = BTL_SUBSTATE_EXEC_BRING_OUT;
            break;
        case BTL_SUBSTATE_EXEC_BRING_OUT:
            partner = battleStatus->partnerActor;
            if (partner != nullptr) {
                if (does_script_exist(partner->takeTurnScriptID)) {
                    break;
                }
                partner->takeTurnScript = nullptr;
            }

            script = start_script(&EVS_BtlBringPartnerOut, EVT_PRIORITY_A, 0);
            battleStatus->controlScript = script;
            battleStatus->controlScriptID = script->id;
            script->owner1.actorID = ACTOR_PARTNER;
            gBattleSubState = BTL_SUBSTATE_EXEC_PHASE;
            {
                CALL_EVENT(OnPartnerChange, PARTNER_CHANGE_ENTER, gPlayerData.curPartner);
            }
            break;
        case BTL_SUBSTATE_EXEC_PHASE:
            if (does_script_exist(battleStatus->controlScriptID)) {
                break;
            }
            partner = battleStatus->partnerActor;
            if (partner != nullptr) {
                if (partner->handlePhaseSource != nullptr) {
                    battleStatus->battlePhase = PHASE_PLAYER_BEGIN;
                    script = start_script(partner->handlePhaseSource, EVT_PRIORITY_A, 0);
                    partner->handlePhaseScript = script;
                    partner->handlePhaseScriptID = script->id;
                    script->owner1.actorID = ACTOR_PARTNER;
                }
            }
            gBattleSubState = BTL_SUBSTATE_AWAIT_PHASE;
            break;
        case BTL_SUBSTATE_AWAIT_PHASE:
            partner = battleStatus->partnerActor;
            if (partner != nullptr) {
                if (partner->handlePhaseSource != nullptr && does_script_exist(partner->handlePhaseScriptID)) {
                    break;
                }
            }
            btl_cam_use_preset(BTL_CAM_DEFAULT);
            gBattleSubState = BTL_SUBSTATE_DONE;
            break;
        case BTL_SUBSTATE_DONE:
            if (battleStatus->stateFreezeCount != 0) {
                break;
            }
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;
            {
                s32 inFront = !(gBattleStatus.flags1 & BS_FLAGS1_PLAYER_IN_BACK);
                CALL_EVENT(OnTurnOrder, TURN_ORDER_PLAYER_IN_FRONT, &inFront);
                if (inFront) {
                    gBattleStatus.flags1 &= ~BS_FLAGS1_PLAYER_IN_BACK;
                } else {
                    gBattleStatus.flags1 |= BS_FLAGS1_PLAYER_IN_BACK;
                }
            }
            if (gBattleStatus.flags1 & BS_FLAGS1_PARTNER_ACTING) {
                if (player_team_is_ability_active(player, ABILITY_QUICK_CHANGE)) {
                    btl_set_state(BATTLE_STATE_PREPARE_MENU);
                } else {
                    btl_set_state(BATTLE_STATE_END_PARTNER_TURN);
                }
            } else {
                if (player_team_is_ability_active(player, ABILITY_QUICK_CHANGE)) {
                    btl_set_state(BATTLE_STATE_PREPARE_MENU);
                } else {
                    btl_set_state(BATTLE_STATE_END_PLAYER_TURN);
                }
            }
            break;
    }
}

void btl_state_draw_change_partner(void) {
}
