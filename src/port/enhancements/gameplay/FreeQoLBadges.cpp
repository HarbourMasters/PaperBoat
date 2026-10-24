#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"
#include "port/ShipInit.hpp"

extern "C" {
#include "common_structs.h"
#include "enums.h"

extern ItemData gItemTable[];
}

static const s32 sFreeQoLBadgeMoves[] = { MOVE_SPEEDY_SPIN, MOVE_I_SPY, MOVE_PEEKABOO };
static ListenerID sBadgeBPCostListener = -1;

void RegisterFreeQoLBadges_Init() {
    UNREGISTER_LISTENER(OnBadgeBPCost, sBadgeBPCostListener);
    sBadgeBPCostListener = -1;

    if (!CVarGetInteger(CVAR_ENHANCEMENT("FreeQoLBadges"), 0)) {
        return;
    }

    sBadgeBPCostListener = REGISTER_LISTENER(OnBadgeBPCost, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnBadgeBPCost* ev = (OnBadgeBPCost*) event;
        s32 moveID = gItemTable[ev->badgeID].moveID;

        for (s32 i = 0; i < ARRAY_COUNT(sFreeQoLBadgeMoves); i++) {
            if (moveID == sFreeQoLBadgeMoves[i]) {
                *ev->cost = 0;
                return;
            }
        }
    });
}

static RegisterShipInitFunc initFreeQoLBadgesFunc(RegisterFreeQoLBadges_Init, { CVAR_ENHANCEMENT("FreeQoLBadges") });
