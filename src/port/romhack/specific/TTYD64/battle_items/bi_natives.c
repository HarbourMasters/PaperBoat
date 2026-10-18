#include "bi_internal.h"

API_CALLABLE(TTYD64_Function_GetActorDefense) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID = evt_get_variable(script, args[0]);
    s32 partIndex = evt_get_variable(script, args[1]);
    s32 element = evt_get_variable(script, args[2]);
    Bytecode outVar = args[3];
    Actor* actor = get_actor(actorID);
    ActorPart* part = get_actor_part(actor, partIndex);

    evt_set_variable(script, outVar, lookup_defense((s32*) part->defenseTable, element));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_bi_Function_IceStorm_ChangeBreathColor) {
    Bytecode* args = script->ptrReadPos;
    EffectInstance* effect = (EffectInstance*) evt_get_variable(script, *args++);

    effect->data.huffPuffBreath->primCol.r = 248;
    effect->data.huffPuffBreath->primCol.g = 248;
    effect->data.huffPuffBreath->primCol.b = 255;
    effect->data.huffPuffBreath->envCol.r = 128;
    effect->data.huffPuffBreath->envCol.g = 224;
    effect->data.huffPuffBreath->envCol.b = 255;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_bi_Function_IceStorm_Rumble) {
    Bytecode* args = script->ptrReadPos;
    s32 intensity = evt_get_variable(script, *args++);
    s32 duration = evt_get_variable(script, *args++);

    start_rumble(intensity, duration);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_bi_Function_802A123C_Projectile) {
    Bytecode* args = script->ptrReadPos;
    s32 x = evt_get_variable(script, *args++);
    s32 y = evt_get_variable(script, *args++);
    s32 z = evt_get_variable(script, *args++);

    fx_smoke_ring(0, x, y, z);
    fx_explosion(0, x, y + 20, z);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_bi_Function_ClearDebuffs) {
    s32 actorID = evt_get_variable(script, *script->ptrReadPos);
    Actor* actor = get_actor(actorID);
    s32 actorClass = actor->actorID & ACTOR_CLASS_MASK;

    if (actor->debuff != 0) {
        actor->debuffDuration = 0;
        actor->debuff = 0;
        remove_status_debuff(actor->hudElementDataIndex);
    }

    if (actor->koStatus != 0) {
        actor->koDuration = 0;
        actor->koStatus = 0;

        if (actorClass == ACTOR_CLASS_PARTNER) {
            TTYD64BattleRec* rec = TTYD64_CurPartnerRec();

            if (rec != nullptr) {
                rec->debuffKey = 0;
                rec->debuffTurns = 0;
            }
            dispatch_event_partner(EVENT_RECOVER_STATUS);
        }

        actor->disableEffect->data.disableX->koDuration = 0;
    }

    btl_update_ko_status();
    return ApiStatus_DONE2;
}
