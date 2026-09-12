#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"
#include "port/ShipInit.hpp"

void RegisterCheats_Init() {
    REGISTER_LISTENER(OnPlayerDamageReceived, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnPlayerDamageReceived* ev = (OnPlayerDamageReceived*) event;

        if (!CVarGetInteger(CVAR_CHEAT("InfiniteHealth"), 0)) {
            return;
        }

        *ev->damage = 0;
    });

    REGISTER_LISTENER(OnPlayerFPChange, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnPlayerFPChange* ev = (OnPlayerFPChange*) event;

        if (!CVarGetInteger(CVAR_CHEAT("InfiniteFlowerPoints"), 0)) {
            return;
        }

        event->Cancelled = true;
    });

    REGISTER_LISTENER(OnPlayerSPChange, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnPlayerSPChange* ev = (OnPlayerSPChange*) event;

        if (!CVarGetInteger(CVAR_CHEAT("MaxStarPower"), 0)) {
            return;
        }

        event->Cancelled = true;
    });

    REGISTER_LISTENER(OnPlayerBPCostCheck, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnPlayerBPCostCheck* ev = (OnPlayerBPCostCheck*) event;

        if (!CVarGetInteger(CVAR_CHEAT("NoBPCost"), 0)) {
            return;
        }

        event->Cancelled = true;
    });
}

static RegisterShipInitFunc initCheatsFunc(RegisterCheats_Init);
