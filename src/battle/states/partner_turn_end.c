#include "states.h"

void btl_state_update_end_partner_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        battleStatus->flags2 |= BS_FLAGS2_PARTNER_TURN_USED;
        CALL_CANCELLABLE_EVENT(OnStatusTick, battleStatus->partnerActor, STATUS_PHASE_PARTNER_TURN_END) {
            if (btl_check_enemies_defeated()) {
                return;
            }
            battleStatus->flags1 &= ~BS_FLAGS1_PARTNER_ACTING;
            {
                s32 inFront = !(battleStatus->flags1 & BS_FLAGS1_PLAYER_IN_BACK);
                CALL_EVENT(OnTurnOrder, TURN_ORDER_PLAYER_IN_FRONT, &inFront);
                if (inFront) {
                    battleStatus->flags1 &= ~BS_FLAGS1_PLAYER_IN_BACK;
                } else {
                    battleStatus->flags1 |= BS_FLAGS1_PLAYER_IN_BACK;
                }
            }
            battleStatus->flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;

            if (battleStatus->cancelTurnMode < 0) {
                battleStatus->cancelTurnMode = 0;
                btl_set_state(BATTLE_STATE_END_TURN);
            } else {
                btl_set_state(BATTLE_STATE_TRANSFER_TURN);
            }
        }
    }
}

void btl_state_draw_end_partner_turn(void) {
}
