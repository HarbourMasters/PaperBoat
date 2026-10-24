#include "states.h"
#include "script_api/battle.h"

enum {
    // BTL_SUBSTATE_INIT        = 0,
    BTL_SUBSTATE_AWAIT          = 1,
};

void btl_state_update_defend(void) {
    Actor* player = gBattleStatus.playerActor;
    Evt* script;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            gBattleStatus.stateFreezeCount = 0;

            // prompt player to handle PHASE_USE_DEFEND
            gBattleStatus.battlePhase = PHASE_USE_DEFEND;
            player->takeTurnScript = script = start_script(&EVS_Mario_HandlePhase, EVT_PRIORITY_A, 0);
            player->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PLAYER;
            gBattleSubState = BTL_SUBSTATE_AWAIT;
            {
                CALL_EVENT(OnBattleDefendBegin, script);
            }
            break;
        case BTL_SUBSTATE_AWAIT:
            // wait for PHASE_USE_DEFEND event to complete
            if (does_script_exist(player->takeTurnScriptID) || gBattleStatus.stateFreezeCount != 0) {
                break;
            }

            // done waiting for the script
            CALL_CANCELLABLE_EVENT(OnBattleDefendEnd) {
                btl_set_state(BATTLE_STATE_END_PLAYER_TURN);
            }
            break;
    }
}

void btl_state_draw_defend(void) {
}
