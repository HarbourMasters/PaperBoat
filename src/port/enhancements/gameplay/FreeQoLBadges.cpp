#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"
#include "port/ShipInit.hpp"

extern "C" {
#include "common_structs.h"
#include "enums.h"

extern MoveData gMoveTable[];
}

static const s32 sFreeQoLBadgeMoves[] = { MOVE_SPEEDY_SPIN, MOVE_I_SPY, MOVE_PEEKABOO };

void RegisterFreeQoLBadges_Init() {
    static s8 vanillaCostBP[ARRAY_COUNT(sFreeQoLBadgeMoves)];
    static bool applied = false;
    bool enabled = CVarGetInteger(CVAR_ENHANCEMENT("FreeQoLBadges"), 0);

    if (enabled == applied) {
        return;
    }

    for (s32 i = 0; i < ARRAY_COUNT(sFreeQoLBadgeMoves); i++) {
        MoveData* move = &gMoveTable[sFreeQoLBadgeMoves[i]];

        if (enabled) {
            vanillaCostBP[i] = move->costBP;
            move->costBP = 0;
        } else {
            move->costBP = vanillaCostBP[i];
        }
    }

    applied = enabled;
}

static RegisterShipInitFunc initFreeQoLBadgesFunc(RegisterFreeQoLBadges_Init, { CVAR_ENHANCEMENT("FreeQoLBadges") });
