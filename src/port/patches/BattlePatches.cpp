#include "effects.h"
#include "port/hooks/Events.h"
#include "port/ShipInit.hpp"

extern "C" EffectInstance* gDamageCountEffects[24];

extern "C" void port_stat_change_fx(s32 stat, s32 amount, f32 x, f32 y, f32 z) {
    const bool attack = stat == ACTOR_STAT_BOOST_ATTACK;
    const s32 index = attack ? amount - 1 : amount + 5;
    if (index >= 0 && index < 10) {
        fx_stat_change(index, x, y, z, 1.0f, 60);
        return;
    }
    const s32 baseIndex = amount < 0 ? 3 : (attack ? 0 : 6);
    EffectInstance* effect = fx_stat_change(baseIndex, x, y, z, 1.0f, 60);
    effect->data.statChange->arrowValue = amount;
}

static void RegisterBattlePatches_Init() {
    REGISTER_LISTENER(OnBattleEffectsRemoved, EVENT_PRIORITY_NORMAL, [](IEvent*) {
        for (EffectInstance*& effect : gDamageCountEffects) {
            effect = nullptr;
        }
    });
}

static RegisterShipInitFunc initFunc(RegisterBattlePatches_Init);
