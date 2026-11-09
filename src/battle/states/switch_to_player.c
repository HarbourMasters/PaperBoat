#include "states.h"

void btl_state_update_switch_to_player(void) {
    Actor* player = gBattleStatus.playerActor;
    Actor* partner = gBattleStatus.partnerActor;
    s32 i;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        {
            s32 who = ACTOR_CLASS_PLAYER;
            CALL_EVENT(OnTurnOrder, TURN_ORDER_WHO_ACTS_FIRST, &who);
            if (who == ACTOR_CLASS_PARTNER && partner != nullptr) {
                gBattleStatus.flags1 |= BS_FLAGS1_PARTNER_ACTING;
            } else {
                gBattleStatus.flags1 &= ~BS_FLAGS1_PARTNER_ACTING;
            }
        }
        {
            s32 inFront = !(gBattleStatus.flags1 & BS_FLAGS1_PLAYER_IN_BACK);
            CALL_EVENT(OnTurnOrder, TURN_ORDER_PLAYER_IN_FRONT, &inFront);
            if (inFront) {
                gBattleStatus.flags1 &= ~BS_FLAGS1_PLAYER_IN_BACK;
            } else {
                gBattleStatus.flags1 |= BS_FLAGS1_PLAYER_IN_BACK;
            }
        }
        reset_actor_turn_info();
        gBattleStatus.selectedMoveID = MOVE_NONE;
        gBattleStatus.actionResult = ACTION_RESULT_NONE;
        gBattleStatus.blockResult = BLOCK_RESULT_NONE;
        gBattleStatus.flags1 |= BS_FLAGS1_SHOW_PLAYER_DECORATIONS;
        player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
        if (partner != nullptr) {
            partner->flags |= (ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM);
        }

        for (i = 0; i < ARRAY_COUNT(gBattleStatus.enemyActors); i++) {
            Actor* enemy = gBattleStatus.enemyActors[i];

            if (enemy != nullptr) {
                enemy->flags |= ACTOR_FLAG_HEALTH_BAR_HIDDEN;
                enemy->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
            }
        }

        btl_set_state(BATTLE_STATE_PREPARE_MENU);
    }
}

void btl_state_draw_switch_to_player(void) {
}
