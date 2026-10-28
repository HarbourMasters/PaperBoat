#include "states.h"
#include "script_api/battle.h"

enum {
    // BTL_SUBSTATE_INIT                    = 0,
    BTL_SUBSTATE_CHECK_LIFE_SHROOM          = 1,
    BTL_SUBSTATE_AWAIT_LIFE_SHROOM          = 2,
    BTL_SUBSTATE_DONE                       = 10,
};

void btl_state_update_defeat(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Evt* script;

    CALL_CANCELLABLE_RETURN_EVENT(OnBattleStateUpdate, BATTLE_STATE_DEFEAT);

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            battleStatus->flags1 &= ~BS_FLAGS1_SHOW_PLAYER_DECORATIONS;
            gBattleStatus.flags2 &= ~BS_FLAGS2_PLAYER_TURN_USED;
            gBattleStatus.flags2 &= ~BS_FLAGS2_PARTNER_TURN_USED;
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;
            battleStatus->stateFreezeCount = 0;

            // clear player debuffs
            if (player->debuff != 0) {
                if (player->debuff == STATUS_KEY_FROZEN) {
                    sfx_play_sound(SOUND_FROZEN_SHATTER);
                    player->icePillarEffect->flags |= FX_INSTANCE_FLAG_DISMISS;
                    player->icePillarEffect = nullptr;
                }
                player->debuff = 0;
                player->debuffDuration = 0;
                remove_status_debuff(player->hudElementDataIndex);
                player->koStatus = 0;
                player->koDuration = 0;
                player->disableEffect->data.disableX->koDuration = 0;
            }

            btl_cam_use_preset(BTL_CAM_PLAYER_FLEE);
            btl_cam_target_actor(ACTOR_PLAYER);

            // prompt player to handle PHASE_DEATH
            battleStatus->battlePhase = PHASE_DEATH;
            script = start_script(&EVS_Mario_HandlePhase, EVT_PRIORITY_A, 0);
            player->takeTurnScript = script;
            player->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PLAYER;

            // prompt partner to handle PHASE_DEATH
            if (partner != nullptr) {
                script = start_script(partner->takeTurnSource, EVT_PRIORITY_A, 0);
                partner->takeTurnScript = script;
                partner->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PARTNER;
            }
            gBattleSubState = BTL_SUBSTATE_CHECK_LIFE_SHROOM;
            break;
        case BTL_SUBSTATE_CHECK_LIFE_SHROOM:
            // wait for player PHASE_DEATH event to complete (ignore partner script)
            if (does_script_exist(player->takeTurnScriptID) || battleStatus->stateFreezeCount != 0) {
                break;
            }
            if (find_item(ITEM_LIFE_SHROOM) >= 0) {
                // prompt player to handle PHASE_USE_LIFE_SHROOM
                battleStatus->battlePhase = PHASE_USE_LIFE_SHROOM;
                script = start_script(&EVS_Mario_HandlePhase, EVT_PRIORITY_A, 0);
                player->takeTurnScript = script;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
                gBattleSubState = BTL_SUBSTATE_AWAIT_LIFE_SHROOM;
            } else {
                gBattleSubState = BTL_SUBSTATE_DONE;
            }
            break;
        case BTL_SUBSTATE_AWAIT_LIFE_SHROOM:
            // wait for player PHASE_USE_LIFE_SHROOM event to complete
            if (does_script_exist(player->takeTurnScriptID) || battleStatus->stateFreezeCount != 0) {
                break;
            }
            // never reached if life shroom is successful. its item script calls RestorePreDefeatState,
            // resetting the state to BATTLE_STATE_ENEMY_MOVE (based on the value of gDefeatedBattleState)
            gBattleSubState = BTL_SUBSTATE_DONE;
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_DONE) {
        gCurrentEncounter.battleOutcome = OUTCOME_PLAYER_LOST;
        if (!(gBattleStatus.flags2 & BS_FLAGS2_DONT_STOP_MUSIC)) {
            bgm_set_song(0, -1, 0, 1500, 8);
        }
        btl_set_state(BATTLE_STATE_END_BATTLE);
    }
}

void btl_state_draw_defeat(void) {
}
