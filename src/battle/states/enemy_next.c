#include "states.h"

enum {
    // BTL_SUBSTATE_INIT        = 0,
    BTL_SUBSTATE_UNUSED_1       = 1,
    BTL_SUBSTATE_DONE           = 2, // enemy has been found
};

BSS u8 NextEnemyWaitingOrdinal;

void btl_state_update_next_enemy(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = gBattleStatus.playerActor;
    Actor* partner = gBattleStatus.partnerActor;
    Actor* enemy;
    s32 skipEnemy;
    s32 i;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
        case BTL_SUBSTATE_UNUSED_1:
            i = battleStatus->nextEnemyIndex;
            if (i >= battleStatus->numEnemyActors) {
                // all enemies have been exhausted
                battleStatus->nextEnemyIndex = 0;
                btl_set_state(BATTLE_STATE_END_TURN);
                return;
            }

            // find the next eligible enemy
            while (true) {
                if (battleStatus->enemyIDs[i] >= 0) {
                    u16 enemyID = battleStatus->enemyIDs[i];

                    enemy = battleStatus->enemyActors[enemyID & 0xFF];
                    if (enemy != nullptr) {
                        if (!(enemy->flags & (ACTOR_FLAG_NO_ATTACK | ACTOR_FLAG_TARGET_ONLY))) {
                            break;
                        }
                    }
                }
                i++;
                if (i >= battleStatus->numEnemyActors) {
                    i = 0;
                }
                if (i == 0) {
                    battleStatus->nextEnemyIndex = 0;
                    btl_set_state(BATTLE_STATE_END_TURN);
                    return;
                }
            }

            battleStatus->activeEnemyActorID = battleStatus->enemyIDs[i++];
            battleStatus->curTurnEnemy = enemy;
            battleStatus->nextEnemyIndex = i;

            skipEnemy = false;

            if (enemy->debuff == STATUS_KEY_SLEEP) {
                skipEnemy = true;
            }
            if (enemy->debuff == STATUS_KEY_UNUSED) {
                skipEnemy = true;
            }
            if (enemy->debuff == STATUS_KEY_DIZZY) {
                skipEnemy = true;
            }
            if (enemy->debuff == STATUS_KEY_PARALYZE) {
                skipEnemy = true;
            }
            if (enemy->debuff == STATUS_KEY_FROZEN) {
                skipEnemy = true;
            }
            if (enemy->debuff == STATUS_KEY_STOP) {
                skipEnemy = true;
            }
            if (enemy->stoneStatus == STATUS_KEY_STONE) {
                skipEnemy = true;
            }
            if (enemy->flags & ACTOR_FLAG_SKIP_TURN) {
                skipEnemy = true;
            }

            if (skipEnemy) {
                // reset state to fetch next enemy
                gBattleSubState = BTL_SUBSTATE_INIT;
                return;
            }

            battleStatus->stateFreezeCount = 0;
            gBattleStatus.flags1 &= ~BS_FLAGS1_MENU_OPEN;
            gBattleStatus.flags1 &= ~BS_FLAGS1_BATTLE_FLED;
            gBattleStatus.flags1 &= ~BS_FLAGS1_AUTO_SUCCEED_ACTION;
            gBattleStatus.flags1 &= ~BS_FLAGS1_PARTNER_ACTING;

            player->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
            player->flags |= ACTOR_FLAG_USING_IDLE_ANIM;

            if (partner != nullptr) {
                partner->flags &= ~ACTOR_FLAG_SHOW_STATUS_ICONS;
                partner->flags |= ACTOR_FLAG_USING_IDLE_ANIM;
            }

            gBattleStatus.flags2 &= ~BS_FLAGS2_PLAYER_TURN_USED;
            {
                s32 skipPartner = false;
                CALL_EVENT(OnTurnOrder, TURN_ORDER_SKIP_PARTNER_TURN, &skipPartner);
                if (!skipPartner) {
                    gBattleStatus.flags2 &= ~BS_FLAGS2_PARTNER_TURN_USED;
                }
            }
            gBattleStatus.flags2 |= BS_FLAGS2_HIDE_BUFF_COUNTERS;

            NextEnemyWaitingOrdinal = enemy->ordinal;
            if (enemy->handlePhaseSource != nullptr) {
                Evt* onTurnChanceScript;

                battleStatus->battlePhase = PHASE_ENEMY_BEGIN;
                onTurnChanceScript = start_script(enemy->handlePhaseSource, EVT_PRIORITY_A, 0);
                enemy->handlePhaseScript = onTurnChanceScript;
                enemy->handlePhaseScriptID = onTurnChanceScript->id;
                onTurnChanceScript->owner1.actorID = battleStatus->activeEnemyActorID;
            }
            gBattleSubState = BTL_SUBSTATE_DONE;
            break;
        case BTL_SUBSTATE_DONE:
            if (battleStatus->stateFreezeCount == 0) {
                enemy = get_actor(battleStatus->activeEnemyActorID);

                if (enemy == nullptr || enemy->ordinal != NextEnemyWaitingOrdinal) {
                    btl_set_state(BATTLE_STATE_NEXT_ENEMY);
                } else {
                    if (enemy->handlePhaseSource == nullptr || !does_script_exist(enemy->handlePhaseScriptID)) {
                        if (battleStatus->cancelTurnMode < 0) {
                            battleStatus->cancelTurnMode = 0;
                            btl_set_state(BATTLE_STATE_END_TURN);
                        } else {
                            btl_set_state(BATTLE_STATE_ENEMY_MOVE);
                        }
                    }
                }
            }
            break;
    }
}

void btl_state_draw_next_enemy(void) {
}
