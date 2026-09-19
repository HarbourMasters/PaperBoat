#include "effects.h"
#include "port/hooks/Events.h"
#include "port/ShipInit.hpp"

extern "C" EffectInstance* gDamageCountEffects[24];

static void RegisterBattlePatches_Init() {
    REGISTER_LISTENER(OnBattleEffectsRemoved, EVENT_PRIORITY_NORMAL, [](IEvent*) {
        for (EffectInstance*& effect : gDamageCountEffects) {
            effect = nullptr;
        }
    });
}

static RegisterShipInitFunc initFunc(RegisterBattlePatches_Init);
