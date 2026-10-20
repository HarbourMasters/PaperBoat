#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"
#include "port/ShipInit.hpp"

extern "C" {
#include "common_structs.h"
#include "enums.h"


}

void RegisterAlwaysChuckQuizmo_Init() {
    REGISTER_LISTENER(OnChuckQuizmoMapSet, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnChuckQuizmoMapSet* ev = (OnChuckQuizmoMapSet*) event;
        if (!CVarGetInteger(CVAR_ENHANCEMENT("AlwaysChuckQuizmo"), 0)) {
            return;
        }


        //zeroing out the variables seems to cause quizmo to appear in every room he can appear in
        *ev->locTown = 0;
        *ev->curTown1 = *ev->locTown;
        *ev->curTown2 = 0;
        *ev->hasLocation = true;
        *ev->curMap = 0;
        *ev->locMap = 0;
        *ev->shouldSetVar = true;
        *ev->changedLocation = false;
    });
}

static RegisterShipInitFunc initAlwaysChuckQuizmo(RegisterAlwaysChuckQuizmo_Init);
