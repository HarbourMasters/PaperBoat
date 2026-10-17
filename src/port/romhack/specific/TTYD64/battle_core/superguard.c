#include "bc_internal.h"
#include "bc_natives.h"
#include "battle/action_cmd.h"
#include "port/modding/Mod.h"

TTYD64GuardState TTYD64_Guard;

extern EvtScript EVS_Enemy_ShockHit;
extern EvtScript EVS_Player_HandleEvent;

API_CALLABLE(TTYD64_bc_PlayTextPopup) {
    Actor* actor = get_actor(script->owner1.actorID);

    show_action_rating(script->ptrReadPos[0], actor, actor->curPos.x, actor->curPos.y + 2.0f, actor->curPos.z);
    script->varTable[0] = 0;
    if ((u32) ((u8) actor->debuff - 3) < 6) {
        script->varTable[0] = 1;
    }
    return ApiStatus_DONE2;
}

b32 TTYD64_SuperguardedHit(Actor* target) {
    return TTYD64_Guard.superguarded && (gBattleStatus.flags1 & BS_FLAGS1_ATK_BLOCKED)
        && (target->actorID & ACTOR_CLASS_MASK) != ACTOR_CLASS_ENEMY;
}

static s32 sg_check_superguard_input(void) {
    PlayerData* playerData = &gPlayerData;
    ActionCommandStatus* acs = &gActionCommandStatus;
    u16 hitsTaken = playerData->hitsTaken;
    b16 hitsTakenIsMax = acs->hitsTakenIsMax;
    s8 blockResult = gBattleStatus.blockResult;
    s32 block = check_block_input(BUTTON_B);

    playerData->hitsTaken = hitsTaken;
    acs->hitsTakenIsMax = hitsTakenIsMax;
    gBattleStatus.blockResult = blockResult;
    return block;
}

static void sg_on_guard_input(IEvent* event) {
    OnGuardInput* ev = (OnGuardInput*) event;
    Actor* target = ev->target;

    TTYD64_Guard.superguarded = false;
    if (*ev->result != GUARD_RESULT_NONE) {
        return;
    }
    if (gBattleStatus.curAttackElement & TTYD64_DAMAGE_TYPE_NO_SUPERGUARD) {
        return;
    }
    if (target->actorID == ACTOR_PARTNER && gPlayerData.curPartner == PARTNER_KOOPER
        && TTYD64_PartnerRec(PARTNER_KOOPER)->flipped != 0)
    {
        return;
    }
    if (sg_check_superguard_input()) {
        TTYD64_Guard.superguarded = true;
        *ev->result = GUARD_RESULT_SUPERGUARD;
    }
}

static void sg_on_damage_event_dispatch(IEvent* event) {
    OnDamageEventDispatch* ev = (OnDamageEventDispatch*) event;
    Actor* target = ev->target;

    if (ev->source != HP_SOURCE_ENEMY_ATTACK) {
        return;
    }
    if (!TTYD64_SuperguardedHit(target)) {
        TTYD64_Guard.superguarded = false;
    }
    if (TTYD64_Guard.superguarded) {
        *ev->event = TTYD64_EVENT_SUPERGUARD;
        return;
    }
    if ((target->actorID & ACTOR_CLASS_MASK) != ACTOR_CLASS_PARTNER) {
        return;
    }
    if (gPlayerData.curPartner != PARTNER_KOOPER) {
        return;
    }
    if (gBattleStatus.flags1 & BS_FLAGS1_ATK_BLOCKED) {
        return;
    }
    if (gBattleStatus.curAttackElement & (DAMAGE_TYPE_JUMP | DAMAGE_TYPE_POW | DAMAGE_TYPE_QUAKE)) {
        *ev->event = EVENT_FLIP_TRIGGER;
    }
}

static void sg_on_contact_counter(IEvent* event) {
    OnContactCounter* ev = (OnContactCounter*) event;

    if (TTYD64_SuperguardedHit(ev->target)) {
        *ev->counter = CONTACT_COUNTER_GUARD;
    }
}

static void sg_on_block_window_check(IEvent* event) {
    OnBlockWindowCheck* ev = (OnBlockWindowCheck*) event;

    if (ev->buttonMask == BUTTON_B) {
        *ev->blockWindow = 1;
    }
}

static void sg_on_battle_state_changed(IEvent* event) {
    OnBattleStateChanged* ev = (OnBattleStateChanged*) event;

    if (ev->next == BATTLE_STATE_NEXT_ENEMY) {
        TTYD64_Guard.superguarded = false;
    }
}

void TTYD64_InstallBattleCoreSuperguard(void) {
    REGISTER_LISTENER(OnGuardInput, EVENT_PRIORITY_LOW, sg_on_guard_input);
    REGISTER_LISTENER(OnDamageEventDispatch, EVENT_PRIORITY_LOW, sg_on_damage_event_dispatch);
    REGISTER_LISTENER(OnContactCounter, EVENT_PRIORITY_LOW, sg_on_contact_counter);
    REGISTER_LISTENER(OnBlockWindowCheck, EVENT_PRIORITY_LOW, sg_on_block_window_check);
    REGISTER_LISTENER(OnBattleStateChanged, EVENT_PRIORITY_NORMAL, sg_on_battle_state_changed);
    Mod_ReplaceScript("TTYD64", &EVS_Enemy_ShockHit, &TTYD64_bc_EVS_Enemy_ShockHit);
    Mod_ReplaceScript("TTYD64", &EVS_Player_HandleEvent, &TTYD64_bc_EVS_Player_HandleEvent);
}
