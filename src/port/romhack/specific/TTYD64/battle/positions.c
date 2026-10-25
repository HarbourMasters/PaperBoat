#include "port/romhack/specific/TTYD64/battle/bc_internal.h"

b8 TTYD64_MarioInFront;
u8 TTYD64_EnemiesTurnEnded[4];

API_CALLABLE(TTYD64_SetTargetActorInFront) {
    s32 actorID = evt_get_variable(script, *script->ptrReadPos);
    s32 targetID;
    Actor* actor;

    if (actorID == ACTOR_SELF) {
        actorID = script->owner1.actorID;
    }
    targetID = TTYD64_MarioInFront == 0 ? ACTOR_PARTNER : ACTOR_PLAYER;
    actor = get_actor(actorID);
    actor->targetActorID = targetID;
    actor->targetPartID = 1;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetTargetActorInTheBack) {
    s32 actorID = evt_get_variable(script, *script->ptrReadPos);
    s32 targetID = ACTOR_PLAYER;
    Actor* actor;

    if (actorID == ACTOR_SELF) {
        actorID = script->owner1.actorID;
    }
    if (TTYD64_MarioInFront != 0) {
        targetID = ACTOR_PARTNER;
        if (TTYD64_GetPartnerHP() <= 0) {
            targetID = ACTOR_PLAYER;
        }
    }
    actor = get_actor(actorID);
    actor->targetActorID = targetID;
    actor->targetPartID = 1;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetMarioPos) {
    evt_set_variable(script, *script->ptrReadPos, TTYD64_MarioInFront);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetMarioInFront) {
    TTYD64_MarioInFront = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

static void toggle_mario_pos(void) {
    TTYD64_MarioInFront = !TTYD64_MarioInFront;
}

static b32 sPartnerLeadsFromFront;

static void who_acts_first_after_enemies(s32* who) {
    TTYD64BattleRec* rec;
    s32 status;

    sPartnerLeadsFromFront = false;
    if (TTYD64_EnemiesTurnEnded[0] == 0) {
        return;
    }
    TTYD64_EnemiesTurnEnded[0] = 0;
    if (TTYD64_MarioInFront != 0 || (gBattleStatus.flags2 & BS_FLAGS2_PARTNER_TURN_USED)) {
        return;
    }
    rec = TTYD64_CurPartnerRec();
    status = rec != nullptr ? rec->debuffKey : 0;
    if (status == STATUS_KEY_POISON || status == STATUS_KEY_SHRINK || status == 0) {
        *who = ACTOR_CLASS_PARTNER;
        sPartnerLeadsFromFront = true;
    }
}

static void bc_on_turn_order(IEvent* event) {
    OnTurnOrder* ev = (OnTurnOrder*) event;

    switch (ev->decision) {
        case TURN_ORDER_WHO_ACTS_FIRST:
            if (gBattleState == BATTLE_STATE_SWITCH_TO_PLAYER) {
                who_acts_first_after_enemies(ev->value);
            } else if (gBattleState == BATTLE_STATE_END_PLAYER_TURN) {
                if (!(gBattleStatus.flags1 & BS_FLAGS1_HUSTLED)) {
                    gBattleStatus.hustleTurns = (u8) gBattleStatus.hustleTurns - 1;
                }
                *ev->value = ACTOR_CLASS_PLAYER;
            }
            break;
        case TURN_ORDER_PLAYER_IN_FRONT:
            switch (gBattleState) {
                case BATTLE_STATE_SWITCH_TO_PLAYER:
                    if (sPartnerLeadsFromFront) {
                        sPartnerLeadsFromFront = false;
                        *ev->value = false;
                    }
                    break;
                case BATTLE_STATE_BEGIN_PARTNER_TURN: {
                    u8 debuff = gBattleStatus.partnerActor->debuff;

                    if (TTYD64_GetPartnerHP() <= 0 || debuff == 0 || debuff == STATUS_KEY_POISON
                        || debuff == STATUS_KEY_SHRINK)
                    {
                        *ev->value = false;
                    }
                    break;
                }
                case BATTLE_STATE_END_PARTNER_TURN:
                    *ev->value = true;
                    break;
                case BATTLE_STATE_TRANSFER_TURN:
                    *ev->value = false;
                    break;
                case BATTLE_STATE_END_PLAYER_TURN:
                    if (gGameStatusPtr->peachFlags != 0) {
                        *ev->value = true;
                    }
                    break;
                case BATTLE_STATE_PLAYER_MENU:
                case BATTLE_STATE_PARTNER_MENU:
                    toggle_mario_pos();
                    break;
            }
            break;
        case TURN_ORDER_CAN_SWAP:
            *ev->value = true;
            break;
    }
}

s32 TTYD64_RequestedBattleState(s32 battleState) {
    if (!(gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE)) {
        return battleState;
    }
    switch (battleState) {
        case BATTLE_STATE_TWINK_MENU:
            return BATTLE_STATE_PARTNER_MENU;
        case BATTLE_STATE_PEACH_MENU:
            return BATTLE_STATE_PLAYER_MENU;
        case BATTLE_STATE_BEGIN_PARTNER_TURN:
            return BATTLE_STATE_BEGIN_PLAYER_TURN;
        case BATTLE_STATE_BEGIN_PLAYER_TURN:
            return BATTLE_STATE_BEGIN_PARTNER_TURN;
    }
    return battleState;
}

static void bc_on_battle_state_changed(IEvent* event) {
    OnBattleStateChanged* ev = (OnBattleStateChanged*) event;
    s32 newState = TTYD64_RequestedBattleState(ev->next);

    if (ev->prev == BATTLE_STATE_RUN_AWAY && newState == BATTLE_STATE_TRANSFER_TURN) {
        gBattleStatus.flags2 &= ~(BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER | BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER);
    }
    if (ev->prev == BATTLE_STATE_BEGIN_PLAYER_TURN && newState == BATTLE_STATE_SWITCH_TO_PLAYER) {
        TTYD64_EnemiesTurnEnded[0] = 1;
    }
    if (newState == BATTLE_STATE_VICTORY) {
        Actor* partner;

        gBattleStatus.flags2 &= ~(BS_FLAGS2_PLAYER_TURN_USED | BS_FLAGS2_PARTNER_TURN_USED);
        TTYD64_bc_ClearPlayerStatusData();
        partner = gBattleStatus.partnerActor;
        if (partner != nullptr) {
            partner->rot.x = 0.0f;
            TTYD64_ClearPartnerStatusData();
        }
    }
}

static void bc_on_battle_init_section(IEvent* event) {
    OnBattleInit* ev = (OnBattleInit*) event;

    if (ev->stage == BATTLE_INIT_SECTION_LOADED) {
        TTYD64_MarioInFront = 1;
    }
}

void TTYD64_InstallBattleCorePositions(void) {
    REGISTER_LISTENER(OnTurnOrder, EVENT_PRIORITY_NORMAL, bc_on_turn_order);
    REGISTER_LISTENER(OnBattleStateChanged, EVENT_PRIORITY_NORMAL, bc_on_battle_state_changed);
    REGISTER_LISTENER(OnBattleInit, EVENT_PRIORITY_NORMAL, bc_on_battle_init_section);
}
