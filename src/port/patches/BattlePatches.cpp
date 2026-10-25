#include "effects.h"
#include "port/hooks/Events.h"
#include "port/ShipInit.hpp"

extern "C" EffectInstance* gDamageCountEffects[24];

extern "C" void port_stat_change_fx(s32 stat, s32 amount, f32 x, f32 y, f32 z) {
    constexpr s32 kArrowTypeDefDown = 3;
    const bool attack = stat == ACTOR_STAT_BOOST_ATTACK;
    s32 index = -1;
    if (attack && amount >= 1 && amount <= 3) {
        index = amount - 1;
    } else if (attack && amount >= -3 && amount <= -1) {
        index = 2 - amount;
    } else if (!attack && amount >= 1 && amount <= 3) {
        index = amount + 5;
    }
    if (index >= 0) {
        fx_stat_change(index, x, y, z, 1.0f, 60);
        return;
    }
    const s32 baseIndex = attack ? (amount < 0 ? 3 : 0) : 6;
    EffectInstance* effect = fx_stat_change(baseIndex, x, y, z, 1.0f, 60);
    effect->data.statChange->arrowValue = amount;
    if (!attack && amount < 0) {
        effect->data.statChange->arrowType = kArrowTypeDefDown;
    }
}

static void RegisterBattlePatches_Init() {
    REGISTER_LISTENER(OnBattleEffectsRemoved, EVENT_PRIORITY_NORMAL, [](IEvent*) {
        for (EffectInstance*& effect : gDamageCountEffects) {
            effect = nullptr;
        }
    });
}

static RegisterShipInitFunc initFunc(RegisterBattlePatches_Init);
