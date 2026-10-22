#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"
#include "port/ShipInit.hpp"

extern "C" {
#include "common_structs.h"
#include "enums.h"
}

void RegisterAlwaysChuckQuizmo_Init() {
    REGISTER_LISTENER(OnQuizmoShouldAppear, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnQuizmoShouldAppear* ev = (OnQuizmoShouldAppear*) event;
        if (!CVarGetInteger(CVAR_ENHANCEMENT("AlwaysChuckQuizmo"), 0)) {
            return;
        }

        *ev->forceAppear = true;
    });
}

static RegisterShipInitFunc initAlwaysChuckQuizmo(RegisterAlwaysChuckQuizmo_Init);
