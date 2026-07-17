#include "states.h"
#include "battle/battle.h"
#include "game_modes.h"

extern s16 DemoBattleBeginDelay;
extern StageListRow* gCurrentStagePtr;

enum {
    // BTL_SUBSTATE_INIT                    = 0,
    BTL_SUBSTATE_FADE_OUT                   = 1,
    BTL_SUBSTATE_EXEC_STAGE_SCRIPT          = 2,
    BTL_SUBSTATE_AWAIT_STAGE_SCRIPT         = 3,
    BTL_SUBSTATE_CLEANUP                    = 4,
};

void btl_state_update_end_demo_battle(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Battle* battle = gCurrentBattlePtr;
    Stage* stage;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            BattleScreenFadeAmt = 0;
            if (EndDemoWhiteOut == -1) {
                if (DemoBattleBeginDelay != 0) {
                    DemoBattleBeginDelay--;
                    break;
                }
            }
            gBattleSubState = BTL_SUBSTATE_FADE_OUT;
            break;
        case BTL_SUBSTATE_FADE_OUT:
            switch (EndDemoWhiteOut) {
                case 255:
                    gBattleSubState = BTL_SUBSTATE_EXEC_STAGE_SCRIPT;
                    return;
                case -1:
                    if (BattleScreenFadeAmt == 255) {
                        gBattleSubState = BTL_SUBSTATE_EXEC_STAGE_SCRIPT;
                        return;
                    }
                    BattleScreenFadeAmt += 50;
                    if (BattleScreenFadeAmt > 255) {
                        BattleScreenFadeAmt = 255;
                    }
                    return;
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
            } else {
                battleStatus->controlScript = start_script(stage->postBattle, EVT_PRIORITY_A, 0);
                battleStatus->controlScriptID = battleStatus->controlScript->id;
                gBattleSubState = BTL_SUBSTATE_AWAIT_STAGE_SCRIPT;
            }
            break;
        case BTL_SUBSTATE_AWAIT_STAGE_SCRIPT:
            if (does_script_exist(battleStatus->controlScriptID)) {
                break;
            }
            gBattleSubState = BTL_SUBSTATE_CLEANUP;
            //fallthrough
        case BTL_SUBSTATE_CLEANUP:
            kill_all_scripts();

            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                Actor* enemy = battleStatus->enemyActors[i];

                if (enemy != nullptr) {
                    btl_delete_actor(enemy);
                }
            }

            if (battleStatus->partnerActor != nullptr) {
                btl_delete_actor(battleStatus->partnerActor);
            }

            if (battleStatus->playerActor != nullptr) {
                btl_delete_player_actor(battleStatus->playerActor);
            }

            remove_all_effects();
            set_windows_visible(WINDOW_GROUP_ALL);

            if (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE) {
                decrement_status_bar_disabled();
            }

            if (EndDemoWhiteOut != -1) {
                gGameStatusPtr->nextDemoScene = LAST_DEMO_SCENE_IDX;
            }

            btl_set_state(BATTLE_STATE_NONE);
            gLastDrawBattleState = gBattleState;
            set_game_mode(GAME_MODE_END_BATTLE);
            break;
    }
}

void btl_state_draw_end_demo_battle(void) {
    if (EndDemoWhiteOut == -1) {
        set_screen_overlay_color(SCREEN_LAYER_FRONT, 0, 0, 0);
        set_screen_overlay_params_front(OVERLAY_SCREEN_COLOR, BattleScreenFadeAmt);
    }
}
