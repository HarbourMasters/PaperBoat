#include "states.h"
#include "battle/battle.h"

void btl_merlee_on_start_turn(void);

enum {
    // BTL_SUBSTATE_INIT                    = 0,
    BTL_SUBSTATE_AWAIT_ENEMY_SCRIPTS        = 5,
    BTL_SUBSTATE_AWAIT_ENEMY_DEATH          = 10,
};

void btl_state_update_begin_turn(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* partner = battleStatus->partnerActor;
    Actor* player = battleStatus->playerActor;
    Actor* enemy;
    Actor* enemy1;
    Actor* enemy2;
    Evt* script;
    b32 awaiting;
    u16 id1;
    u16 id2;
    s32 numEnemyActors;
    s32 i;
    s32 j;
    s16* enemyIDs;

    if (gBattleSubState == BTL_SUBSTATE_INIT) {
        battleStatus->flags2 &= ~BS_FLAGS2_PLAYER_TURN_USED;
        {
            s32 skipPartner = false;
            CALL_EVENT(OnTurnOrder, TURN_ORDER_SKIP_PARTNER_TURN, &skipPartner);
            if (!skipPartner) {
                battleStatus->flags2 &= ~BS_FLAGS2_PARTNER_TURN_USED;
            }
        }
        battleStatus->flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
        battleStatus->flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;
        battleStatus->merleeAttackBoost = 0;
        battleStatus->merleeDefenseBoost = 0;
        battleStatus->flags2 &= ~BS_FLAGS2_IS_FIRST_STRIKE;

        player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
        player->disableDismissTimer = 0;
        if (partner != nullptr) {
            player->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
            partner->disableDismissTimer = 0;
        }

        if (battleStatus->hustleTurns != 0) {
            gBattleStatus.flags1 |= BS_FLAGS1_HUSTLED;
        }

        numEnemyActors = 0;
        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            enemy = battleStatus->enemyActors[i];
            if (enemy != nullptr) {
                battleStatus->enemyIDs[numEnemyActors] = i | ACTOR_ENEMY0;
                numEnemyActors++;
            }
        }
        battleStatus->numEnemyActors = numEnemyActors;

        // sort enemies by x-position or turn priority
        enemyIDs = battleStatus->enemyIDs;
        for (i = 0; i < numEnemyActors - 1; i++) {
            for (j = i + 1; j < numEnemyActors; j++) {
                id1 = enemyIDs[i];
                id2 = enemyIDs[j];
                enemy1 = battleStatus->enemyActors[id1 & 0xFF];
                enemy2 = battleStatus->enemyActors[id2 & 0xFF];
                if (gBattleStatus.flags1 & BS_FLAGS1_SORT_ENEMIES_BY_POSX) {
                    if (enemy1->homePos.x > enemy2->homePos.x) {
                        enemyIDs[i] = id2;
                        enemyIDs[j] = id1;
                    }
                } else if (enemy1->turnPriority < enemy2->turnPriority) {
                    enemyIDs[i] = id2;
                    enemyIDs[j] = id1;
                }
            }
        }
        battleStatus->nextEnemyIndex = 0;

        btl_merlee_on_start_turn();

        // clear rush flags to initialize
        battleStatus->rushFlags = RUSH_FLAG_NONE;
        gBattleStatus.flags2 &= ~BS_FLAGS2_HAS_RUSH;

        // set rush flags based on danger/peril status
        if (!(gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE)) {
            if (gPlayerData.curHP <= PERIL_THRESHOLD && is_ability_active(ABILITY_MEGA_RUSH)) {
                gBattleStatus.flags2 |= BS_FLAGS2_HAS_RUSH;
                battleStatus->rushFlags |= RUSH_FLAG_MEGA;
            }
            if (gPlayerData.curHP <= DANGER_THRESHOLD && is_ability_active(ABILITY_POWER_RUSH)) {
                if (!(battleStatus->rushFlags & RUSH_FLAG_MEGA)) {
                    gBattleStatus.flags2 |= BS_FLAGS2_HAS_RUSH;
                    battleStatus->rushFlags |= RUSH_FLAG_POWER;
                }
            }
        }

        if (!(gBattleStatus.flags1 & BS_FLAGS1_JUMP_CHARGED)) {
            battleStatus->jumpCharge = 0;
        }

        if (!(gBattleStatus.flags1 & BS_FLAGS1_HAMMER_CHARGED)) {
            battleStatus->hammerCharge = 0;
        }

        if (gGameStatusPtr->debugEnemyContact == DEBUG_CONTACT_AUTO_FLEE) {
            btl_set_state(BATTLE_STATE_RUN_AWAY);
            return;
        }

        if (gGameStatusPtr->debugEnemyContact == DEBUG_CONTACT_DIE_IN_BATTLE) {
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != nullptr && enemy->handleEventSource != nullptr) {
                    Evt* script = start_script(enemy->handleEventSource, EVT_PRIORITY_A, 0);

                    enemy->handleEventScript = script;
                    script->owner1.actorID = i | ACTOR_ENEMY0;
                    enemy->handleEventScriptID = script->id;
                    enemy->lastEventType = EVENT_DEATH;
                }
            }
            gBattleSubState = BTL_SUBSTATE_AWAIT_ENEMY_DEATH;
        } else {
            for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
                enemy = battleStatus->enemyActors[i];
                if (enemy != nullptr && enemy->handlePhaseSource != nullptr) {
                    battleStatus->battlePhase = PHASE_PLAYER_BEGIN;
                    script = start_script(enemy->handlePhaseSource, EVT_PRIORITY_A, 0);
                    enemy->handlePhaseScript = script;
                    enemy->handlePhaseScriptID = script->id;
                    script->owner1.actorID = i | ACTOR_ENEMY0;
                }
            }

            partner = battleStatus->partnerActor;
            if (partner != nullptr && partner->handlePhaseSource != nullptr) {
                battleStatus->battlePhase = PHASE_PLAYER_BEGIN;
                script = start_script(partner->handlePhaseSource, EVT_PRIORITY_A, 0);
                partner->handlePhaseScript = script;
                partner->handlePhaseScriptID = script->id;
                script->owner1.actorID = ACTOR_PARTNER;
            }
            gBattleSubState = BTL_SUBSTATE_AWAIT_ENEMY_SCRIPTS;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_AWAIT_ENEMY_SCRIPTS) {
        awaiting = false;
        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            enemy = battleStatus->enemyActors[i];
            if (enemy != nullptr && enemy->handlePhaseSource != nullptr && does_script_exist(enemy->handlePhaseScriptID)) {
                awaiting = true;
            }
        }
        if (partner != nullptr && partner->handlePhaseSource != nullptr && does_script_exist(partner->handlePhaseScriptID)) {
            awaiting = true;
        }

        if (!awaiting) {
            if (!btl_check_enemies_defeated()) {
                btl_set_state(BATTLE_STATE_BEGIN_PLAYER_TURN);
            }
            return;
        }
    }

    if (gBattleSubState == BTL_SUBSTATE_AWAIT_ENEMY_DEATH) {
        awaiting = false;
        for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
            enemy = battleStatus->enemyActors[i];
            if (enemy != nullptr && enemy->handleEventSource != nullptr && does_script_exist(enemy->handleEventScriptID)) {
                awaiting = true;
            }
        }

        if (!awaiting) {
            if (!btl_check_enemies_defeated()) {
                btl_set_state(BATTLE_STATE_BEGIN_PLAYER_TURN);
            }
        }
    }
}

void btl_state_draw_begin_turn(void) {
}
