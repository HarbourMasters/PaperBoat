#include "states.h"
#include "script_api/battle.h"

enum {
    BTL_SUBSTATE_EXEC_SCRIPT            = BTL_SUBSTATE_INIT,
    BTL_SUBSTATE_AWAIT_SCRIPT           = 2,
    BTL_SUBSTATE_EXEC_POST_FAILURE      = 3,
    BTL_SUBSTATE_AWAIT_POST_FAILURE     = 4,
    BTL_SUBSTATE_GIVE_STAR_POINTS       = 10,
    BTL_SUBSTATE_DONE                   = 11,
};

BSS s32 RunAwayRewardStep;
BSS s32 RunAwayRewardTotal;
BSS s32 RunAwayRewardIncrement;

void btl_state_update_run_away(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    EncounterStatus* currentEncounter = &gCurrentEncounter;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Actor* enemy;
    s32 enemyCount;
    f32 totalEscapeChance;
    Evt* script;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_EXEC_SCRIPT:
            battleStatus->stateFreezeCount = 0;
            gBattleStatus.flags1 &= ~BS_FLAGS1_BATTLE_FLED;
            {
                s32 skipPartner = false;
                CALL_EVENT(OnTurnOrder, TURN_ORDER_SKIP_PARTNER_TURN, &skipPartner);
                s32 wasInFront = !(gBattleStatus.flags1 & BS_FLAGS1_PLAYER_IN_BACK);
                s32 endsTeamTurn = true;
                {
                    CALL_EVENT(OnTurnOrder, TURN_ORDER_FLEE_ENDS_TEAM_TURN, &endsTeamTurn);
                }
                s32 inFront = wasInFront;
                {
                    CALL_EVENT(OnTurnOrder, TURN_ORDER_PLAYER_IN_FRONT, &inFront);
                }
                if (!skipPartner) {
                    gBattleStatus.flags2 |= BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;
                }
                gBattleStatus.flags2 |= BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
                if (endsTeamTurn || !wasInFront) {
                    gBattleStatus.flags2 |= BS_FLAGS2_PARTNER_TURN_USED;
                }
                if (endsTeamTurn || wasInFront) {
                    gBattleStatus.flags2 |= BS_FLAGS2_PLAYER_TURN_USED;
                }
                if (inFront) {
                    gBattleStatus.flags1 &= ~BS_FLAGS1_PLAYER_IN_BACK;
                } else {
                    gBattleStatus.flags1 |= BS_FLAGS1_PLAYER_IN_BACK;
                }
            }

            playerData->fleeAttempts++;
            btl_cam_use_preset(BTL_CAM_PLAYER_FLEE);
            btl_cam_target_actor(ACTOR_PLAYER);

            // calculate average escape chance
            enemyCount = 0;
            totalEscapeChance = 0.0f;

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != nullptr) {
                    if (!(enemy->flags & ACTOR_FLAG_TARGET_ONLY)) {
                        if (!(enemy->flags & ACTOR_FLAG_NO_DMG_APPLY)) {
                            f32 escapeChance = enemy->actorBlueprint->escapeChance;

                            if (enemy->debuff == STATUS_KEY_UNUSED ||
                                enemy->debuff == STATUS_KEY_DIZZY ||
                                enemy->debuff == STATUS_KEY_PARALYZE ||
                                enemy->debuff == STATUS_KEY_SLEEP ||
                                enemy->debuff == STATUS_KEY_FROZEN ||
                                enemy->debuff == STATUS_KEY_STOP)
                            {
                                escapeChance = 100.0f;
                            }
                            totalEscapeChance += escapeChance;
                            enemyCount++;
                        }
                    }
                }
            }
            player->state.varTable[0] = totalEscapeChance / enemyCount;

            if (gGameStatusPtr->debugEnemyContact == DEBUG_CONTACT_AUTO_FLEE) {
                player->state.varTable[0] = 100;
            }

            battleStatus->battlePhase = PHASE_RUN_AWAY_START;
            script = start_script(&EVS_Mario_HandlePhase, EVT_PRIORITY_A, 0);
            player->takeTurnScript = script;
            player->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PLAYER;
            if (partner != nullptr && partner->koStatus == 0) {
                script = start_script(partner->takeTurnSource, EVT_PRIORITY_A, 0);
                partner->takeTurnScript = script;
                partner->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PARTNER;
            }
            gBattleSubState = BTL_SUBSTATE_AWAIT_SCRIPT;
            break;
        case BTL_SUBSTATE_AWAIT_SCRIPT:
            if (does_script_exist(player->takeTurnScriptID) || battleStatus->stateFreezeCount != 0) {
                break;
            }
            if (!(gBattleStatus.flags1 & BS_FLAGS1_BATTLE_FLED)) {
                gBattleSubState = BTL_SUBSTATE_EXEC_POST_FAILURE;
            } else {
                currentEncounter->battleOutcome = OUTCOME_PLAYER_FLED;
                if (!is_ability_active(ABILITY_RUNAWAY_PAY)) {
                    gBattleSubState = BTL_SUBSTATE_DONE;
                } else {
                    status_bar_start_blinking_starpoints();
                    btl_start_blinking_starpoints();
                    BattleScreenFadeAmt = 0;
                    // divide reward into 20 increments
                    RunAwayRewardTotal = battleStatus->totalStarPoints * 100;
                    RunAwayRewardStep = 20;
                    RunAwayRewardIncrement = RunAwayRewardTotal / RunAwayRewardStep;
                    gBattleSubState = BTL_SUBSTATE_GIVE_STAR_POINTS;
                }
            }
            break;
    }

    if (gBattleSubState == BTL_SUBSTATE_GIVE_STAR_POINTS) {
        if (battleStatus->totalStarPoints != 0) {
            s32 deltaSP;
            s32 prevSP;

            RunAwayRewardTotal -= RunAwayRewardIncrement;
            prevSP = battleStatus->totalStarPoints;
            battleStatus->totalStarPoints = RunAwayRewardTotal / 100;
            deltaSP = prevSP - battleStatus->totalStarPoints;

            if (deltaSP > 0) {
                sfx_play_sound(SOUND_COIN_PICKUP);
            }
            playerData->starPoints += deltaSP;
            BattleScreenFadeAmt++;
            if (RunAwayRewardStep == 0 && battleStatus->totalStarPoints != 0) {
                playerData->starPoints++;
            }
        }
        if (playerData->starPoints >= 99) {
            playerData->starPoints = 99;
        }
        if (battleStatus->totalStarPoints == 0) {
            if (RunAwayRewardStep != 0) {
                RunAwayRewardStep--;
            } else {
                status_bar_stop_blinking_starpoints();
                btl_stop_blinking_starpoints();
                gBattleSubState = BTL_SUBSTATE_DONE;
            }
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_DONE) {
        playerData->battlesFled++;
        if (!(gBattleStatus.flags2 & BS_FLAGS2_DONT_STOP_MUSIC)) {
            bgm_set_song(0, -1, 0, 1500, 8);
        }
        btl_set_state(BATTLE_STATE_END_BATTLE);
    }

    switch (gBattleSubState) {
        case BTL_SUBSTATE_EXEC_POST_FAILURE:
            battleStatus->battlePhase = PHASE_RUN_AWAY_FAIL;
            script = start_script(&EVS_Mario_HandlePhase, EVT_PRIORITY_A, 0);
            player->takeTurnScript = script;
            player->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PLAYER;
            if (partner != nullptr && partner->koStatus == 0) {
                script = start_script(partner->takeTurnSource, EVT_PRIORITY_A, 0);
                partner->takeTurnScript = script;
                partner->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PARTNER;
            }
            gBattleSubState = BTL_SUBSTATE_AWAIT_POST_FAILURE;
            break;
        case BTL_SUBSTATE_AWAIT_POST_FAILURE:
            if (BattleSubstateDelay != 0) {
                BattleSubstateDelay--;
                return;
            }
            if (!does_script_exist(player->takeTurnScriptID)
                && (partner == nullptr || !does_script_exist(partner->takeTurnScriptID))
                && battleStatus->stateFreezeCount == 0
            ) {
                btl_set_state(BATTLE_STATE_TRANSFER_TURN);
            }
            break;
    }
}

void btl_state_draw_run_away(void) {
}
