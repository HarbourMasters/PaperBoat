#include "bc_internal.h"
#include "port/modding/Mod.h"

static int32_t sRecHandle = -1;

void TTYD64_InstallActorRecords(void) {
    sRecHandle = Mod_RegisterActorExt("TTYD64", sizeof(TTYD64BattleRec));
}

TTYD64BattleRec* TTYD64_PartnerRec(s32 partnerID) {
    return (TTYD64BattleRec*) Mod_PartnerExt(sRecHandle, partnerID);
}

TTYD64BattleRec* TTYD64_CurPartnerRec(void) {
    s32 partnerID = gPlayerData.curPartner;

    if (partnerID == 0) {
        return nullptr;
    }
    if (TTYD64_GetPartnerHP() < 0) {
        return nullptr;
    }
    return TTYD64_PartnerRec(partnerID);
}

TTYD64BattleRec* TTYD64_ActorRec(s32 actorID) {
    if (actorID == ACTOR_PARTNER) {
        return TTYD64_CurPartnerRec();
    }
    return (TTYD64BattleRec*) Mod_ActorExt(sRecHandle, actorID);
}

TTYD64CounterUI* TTYD64_bc_ActorCounters(s32 actorID) {
    TTYD64BattleRec* rec = (TTYD64BattleRec*) Mod_ActorExt(sRecHandle, actorID);

    return rec != nullptr ? rec->counters : nullptr;
}

static u8* rec_row_field(TTYD64BattleRec* rec, s32 offset) {
    switch (offset) {
        case 0x0:
            return &rec->debuffKey;
        case 0x1:
            return &rec->debuffTurns;
        case 0x2:
            return &rec->staticTurns;
        case 0x3:
            return &rec->transparentTurns;
        case 0x4:
        case 0x6:
        case 0x8:
        case 0xA:
            return (u8*) &rec->buffs[(offset - 4) / 2].amount;
        case 0x5:
        case 0x7:
        case 0x9:
        case 0xB:
            return &rec->buffs[(offset - 4) / 2].turns;
        case 0xC:
            return &rec->flipped;
        case 0xD:
            return &rec->flipCountdown;
        case 0xE:
            return &rec->defendStack;
        case 0xF:
            return &rec->charge;
    }
    return nullptr;
}

u8 TTYD64_bc_GetRecField(TTYD64BattleRec* rec, s32 offset) {
    u8* field;

    if (rec == nullptr) {
        return 0;
    }
    field = rec_row_field(rec, offset);
    return field != nullptr ? *field : 0;
}

void TTYD64_bc_SetRecField(TTYD64BattleRec* rec, s32 offset, s32 value) {
    u8* field;

    if (rec == nullptr) {
        return;
    }
    field = rec_row_field(rec, offset);
    if (field != nullptr) {
        *field = value;
    }
}

API_CALLABLE(TTYD64_SetActorExtraData) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID = evt_get_variable(script, args[0]);
    TTYD64BattleRec* rec;
    s32 offset;
    s32 value;

    if (actorID == ACTOR_SELF) {
        actorID = script->owner1.actorID;
    }
    rec = TTYD64_ActorRec(actorID);
    offset = evt_get_variable(script, args[1]);
    value = evt_get_variable(script, args[2]);
    TTYD64_bc_SetRecField(rec, offset, value);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetActorExtraData) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID = evt_get_variable(script, args[0]);
    TTYD64BattleRec* rec;
    s32 offset;

    if (actorID == ACTOR_SELF) {
        actorID = script->owner1.actorID;
    }
    rec = TTYD64_ActorRec(actorID);
    offset = evt_get_variable(script, args[1]);
    evt_set_variable(script, args[2], (s8) TTYD64_bc_GetRecField(rec, offset));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetPartnerExtraBattleData_API) {
    Bytecode* args = script->ptrReadPos;
    s32 offset = evt_get_variable(script, args[0]);

    evt_set_variable(script, args[1], TTYD64_bc_GetRecField(TTYD64_CurPartnerRec(), offset));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetPartnerExtraBattleData_API) {
    Bytecode* args = script->ptrReadPos;
    s32 offset = evt_get_variable(script, args[0]);
    s32 value = evt_get_variable(script, args[1]);

    TTYD64_bc_SetRecField(TTYD64_CurPartnerRec(), offset, value);
    return ApiStatus_DONE2;
}

void TTYD64_ClearPartnerExtraData(void) {
    TTYD64BattleRec* rec = TTYD64_CurPartnerRec();

    if (rec != nullptr) {
        memset(rec, 0, sizeof(*rec));
    }
}

static void clear_actor_status_data(Actor* actor) {
    TTYD64BattleRec* rec;

    if (actor->debuff != 0 || actor->debuffDuration != 0) {
        actor->debuff = 0;
        actor->debuffDuration = 0;
        remove_status_debuff((u16) actor->hudElementDataIndex);
        actor->disableEffect->data.disableX->koDuration = 0;
    }
    if (actor->staticStatus != 0 || actor->staticDuration != 0) {
        actor->staticStatus = 0;
        actor->staticDuration = 0;
        remove_status_static((u16) actor->hudElementDataIndex);
    } else {
        actor->staticStatus = 0;
        actor->staticDuration = 0;
    }
    actor->koStatus = 0;
    actor->koDuration = 0;
    if (actor->transparentStatus != 0 || actor->transparentDuration != 0) {
        actor->transparentStatus = 0;
        actor->transparentDuration = 0;
        remove_status_transparent((u16) actor->hudElementDataIndex);
    } else {
        actor->transparentStatus = 0;
        actor->transparentDuration = 0;
    }
    actor->statusAfflicted = 0;
    actor->isGlowing = 0;
    actor->attackBoost = 0;
    actor->defenseBoost = 0;
    actor->chillOutAmount = 0;
    rec = TTYD64_ActorRec((u16) actor->actorID);
    if (rec != nullptr) {
        rec->giant = false;
        rec->tiny = false;
    }
}

void TTYD64_ClearPartnerStatusData(void) {
    Actor* partner = gBattleStatus.partnerActor;

    if (partner == nullptr) {
        return;
    }
    clear_actor_status_data(partner);
    TTYD64_bc_RemoveBuffs_Partner();
}

API_CALLABLE(TTYD64_ClearPartnerExtraData_API) {
    TTYD64_ClearPartnerExtraData();
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_ClearPartnerStatusData_API) {
    TTYD64_ClearPartnerStatusData();
    return ApiStatus_DONE2;
}

void TTYD64_bc_ClearPlayerStatusData(void) {
    Actor* player = gBattleStatus.playerActor;

    if (player == nullptr) {
        return;
    }
    clear_actor_status_data(player);
    TTYD64_Function_RemoveBuffs_ActorID(ACTOR_PLAYER);
}

static void advance_partner_buff_turns(u8* turns) {
    s32 left = *turns;

    if (left != 0) {
        left--;
        if (left == 0) {
            BattleStatusUpdateDelay = TTYD64_BC_BATTLE_WAIT_TIMER_EXPIRED;
        }
    }
    *turns = left;
}

void TTYD64_bc_AdvancePartnersExtraData(void) {
    TTYD64BattleRec* rec;
    TTYD64BattleRec* kooper;
    s32 left;
    s32 i;

    if (TTYD64_GetPartnerHP() < 0) {
        return;
    }
    rec = TTYD64_CurPartnerRec();
    left = rec->debuffTurns;
    if (left != 0) {
        left--;
    }
    rec->debuffTurns = left;
    for (i = 0; i < TTYD64_BUFF_COUNT; i++) {
        advance_partner_buff_turns(&rec->buffs[i].turns);
    }
    if (gPlayerData.curPartner == PARTNER_KOOPER) {
        return;
    }
    kooper = TTYD64_PartnerRec(PARTNER_KOOPER);
    if (kooper->flipped == 0 || kooper->flipCountdown == 0) {
        return;
    }
    kooper->flipCountdown--;
}

static void bc_on_damage_event_dispatch(IEvent* event) {
    OnDamageEventDispatch* ev = (OnDamageEventDispatch*) event;
    TTYD64BattleRec* rec;

    if (*ev->event != EVENT_FLIP_TRIGGER) {
        return;
    }
    switch (ev->source) {
        case HP_SOURCE_PLAYER_ATTACK:
        case HP_SOURCE_PARTNER_ATTACK:
        case HP_SOURCE_ITEM:
            if ((ev->target->actorID & ACTOR_CLASS_MASK) != ACTOR_CLASS_ENEMY) {
                return;
            }
            break;
        case HP_SOURCE_SCRIPT_EVENT:
            break;
        default:
            return;
    }
    rec = TTYD64_ActorRec((u16) ev->target->actorID);
    if (rec != nullptr) {
        rec->flipped = 1;
    }
}

static void bc_on_battle_init(IEvent* event) {
    OnBattleInit* ev = (OnBattleInit*) event;

    if (ev->stage != BATTLE_INIT_BEGIN) {
        return;
    }
    TTYD64_EnemyItemTable_ClearAllData();
    TTYD64_FPDrainByte[0] = 0;
}

void TTYD64_InstallBattleCoreActorData(void) {
    REGISTER_LISTENER(OnDamageEventDispatch, EVENT_PRIORITY_HIGH, bc_on_damage_event_dispatch);
    REGISTER_LISTENER(OnBattleInit, EVENT_PRIORITY_NORMAL, bc_on_battle_init);
}
