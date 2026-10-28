#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"
#include "port/ShipInit.hpp"

#include <algorithm>

extern "C" {
#include "common_structs.h"

extern BattleStatus gBattleStatus;
}

void RegisterCheats_Init() {
    REGISTER_LISTENER(OnPlayerDamageReceived, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnPlayerDamageReceived* ev = (OnPlayerDamageReceived*) event;

        if (!Port_FeatureInt("cheats.infinite_health", 0)) {
            return;
        }

        *ev->damage = 0;
    });

    REGISTER_LISTENER(OnPlayerFPChange, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnPlayerFPChange* ev = (OnPlayerFPChange*) event;

        if (!Port_FeatureInt("cheats.infinite_fp", 0)) {
            return;
        }

        event->Cancelled = true;
    });

    REGISTER_LISTENER(OnPlayerSPChange, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnPlayerSPChange* ev = (OnPlayerSPChange*) event;

        if (!Port_FeatureInt("cheats.max_star_power", 0)) {
            return;
        }

        event->Cancelled = true;
    });

    REGISTER_LISTENER(OnPlayerBPCostCheck, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnPlayerBPCostCheck* ev = (OnPlayerBPCostCheck*) event;

        if (!Port_FeatureInt("cheats.no_bp_cost", 0)) {
            return;
        }

        event->Cancelled = true;
    });

    REGISTER_LISTENER(OnPowerBounceChance, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnPowerBounceChance* ev = (OnPowerBounceChance*) event;

        if (!Port_FeatureInt("cheats.max_power_bounce", 0) || ev->targetChance == 0) {
            return;
        }

        *ev->hitChance = 200;
    });

    REGISTER_LISTENER(OnStarPointDrop, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnStarPointDrop* ev = (OnStarPointDrop*) event;

        if (!Port_FeatureInt("cheats.double_rewards", 0)) {
            return;
        }

        int32_t room = 100 - gBattleStatus.totalStarPoints - gBattleStatus.pendingStarPoints;
        *ev->count = (std::max) (0, (std::min) (*ev->count * 2, room));
    });

    REGISTER_LISTENER(OnCoinDrop, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnCoinDrop* ev = (OnCoinDrop*) event;

        if (!Port_FeatureInt("cheats.double_rewards", 0)) {
            return;
        }

        *ev->count *= 2;
    });
}

static RegisterShipInitFunc initCheatsFunc(RegisterCheats_Init);
