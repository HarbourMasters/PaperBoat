#include "states.h"
#include "script_api/battle.h"
#include "game_modes.h"

extern StageListRow* gCurrentStagePtr;

enum {
    // BTL_SUBSTATE_INIT                    = 0,
    BTL_SUBSTATE_FADE_OUT                   = 1,
    BTL_SUBSTATE_EXEC_STAGE_SCRIPT          = BTL_SUBSTATE_END_BATTLE_EXEC_STAGE_SCRIPT,
    BTL_SUBSTATE_AWAIT_STAGE_SCRIPT         = 3,
    BTL_SUBSTATE_CLEANUP                    = 4,
};

void btl_state_update_end_battle(void) {
    EncounterStatus* encounterStatus = &gCurrentEncounter;
    BattleStatus* battleStatus = &gBattleStatus;
    Battle* battle = gCurrentBattlePtr;
    Stage* stage;
    Evt* script;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            BattleScreenFadeAmt = 0;
            if (gGameStatusPtr->debugEnemyContact == DEBUG_CONTACT_DIE_ON_TOUCH) {
                BattleScreenFadeAmt = 255;
            }
            if (encounterStatus->battleOutcome == OUTCOME_PLAYER_LOST && !(gBattleStatus.flags1 & BS_FLAGS1_NO_GAME_OVER)) {
                btl_cam_unfreeze();
                btl_cam_use_preset(BTL_CAM_INTERRUPT);
                set_screen_overlay_color(SCREEN_LAYER_FRONT, 0, 0, 0);
                set_screen_overlay_center(SCREEN_LAYER_FRONT, 0, 160, 120);
            }
            gBattleSubState = BTL_SUBSTATE_FADE_OUT;
            break;
        case BTL_SUBSTATE_FADE_OUT:
            if (BattleScreenFadeAmt == 255) {
                gBattleSubState = BTL_SUBSTATE_EXEC_STAGE_SCRIPT;
                break;
            }
            BattleScreenFadeAmt += battleStatus->endBattleFadeOutRate;
            if (BattleScreenFadeAmt > 255) {
                BattleScreenFadeAmt = 255;
            }
            break;
        case BTL_SUBSTATE_EXEC_STAGE_SCRIPT:
            BattleScreenFadeAmt = 255;
            gBattleStatus.flags1 &= ~BS_FLAGS1_ACTORS_VISIBLE;
            if (gCurrentStagePtr == nullptr) {
                stage = battle->stage;
            } else {
                stage = gCurrentStagePtr->stage;
            }
            if (stage->postBattle == nullptr) {
                gBattleSubState = BTL_SUBSTATE_CLEANUP;
                return;
            }
            script = start_script(stage->postBattle, EVT_PRIORITY_A, 0);
            battleStatus->controlScript = script;
            battleStatus->controlScriptID = script->id;
            gBattleSubState = BTL_SUBSTATE_AWAIT_STAGE_SCRIPT;
            break;
        case BTL_SUBSTATE_AWAIT_STAGE_SCRIPT:
            if (does_script_exist(battleStatus->controlScriptID)) {
                break;
            }
            gBattleSubState = BTL_SUBSTATE_CLEANUP;
            // fallthrough
        case BTL_SUBSTATE_CLEANUP:
            kill_all_scripts();
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                if (battleStatus->enemyActors[i] != nullptr) {
                    btl_delete_actor(battleStatus->enemyActors[i]);
                }
            }
            if (battleStatus->partnerActor != nullptr) {
                btl_delete_actor(battleStatus->partnerActor);
            }

            btl_delete_player_actor(battleStatus->playerActor);
            CALL_EVENT(OnBattleCleanup);

            if (battleStatus->nextMerleeSpellType == MERLEE_SPELL_COIN_BOOST) {
                encounterStatus->hasMerleeCoinBonus = true;
                battleStatus->nextMerleeSpellType = MERLEE_SPELL_NONE;
            }

            encounterStatus->damageTaken = battleStatus->damageTaken;

            if (gBattleStatus.flags2 & BS_FLAGS2_DROP_WHACKA_BUMP) {
                encounterStatus->dropWhackaBump = true;
            }

            remove_all_effects();
            set_windows_visible(0);

            if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                decrement_status_bar_disabled();
            }

            if (encounterStatus->battleOutcome == OUTCOME_PLAYER_LOST &&
                !(gBattleStatus.flags1 & BS_FLAGS1_NO_GAME_OVER))
            {
                s16 areaID;
                s16 mapID;

                btl_set_state(BATTLE_STATE_NONE);
                gLastDrawBattleState = gBattleState;
                get_map_IDs_by_name_checked("gv_01", &areaID, &mapID);
                gGameStatusPtr->areaID = areaID;
                gGameStatusPtr->mapID = mapID;
                gGameStatusPtr->entryID = gv_01_ENTRY_0;
                set_game_mode(GAME_MODE_GAME_OVER);
            } else {
                btl_set_state(BATTLE_STATE_NONE);
                gLastDrawBattleState = gBattleState;
                func_8003E514(1);
                set_game_mode(GAME_MODE_END_BATTLE);
            }
            break;
    }
}

void btl_state_draw_end_battle(void) {
    Camera* camera = &gCameras[gCurrentCameraID];

    if (gCurrentEncounter.battleOutcome == OUTCOME_PLAYER_LOST && !(gBattleStatus.flags1 & BS_FLAGS1_NO_GAME_OVER)) {
        camera->params.basic.offsetY += 256;
        set_screen_overlay_params_front(OVERLAY_SCREEN_MARIO, BattleScreenFadeAmt);
    } else {
        set_screen_overlay_params_front(OVERLAY_SCREEN_COLOR, BattleScreenFadeAmt);
    }
}
