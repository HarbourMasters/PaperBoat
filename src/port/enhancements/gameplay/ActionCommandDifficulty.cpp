#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"
#include "port/ShipInit.hpp"

void RegisterActionCommandDifficulty_Init() {
    REGISTER_LISTENER(OnActionCommandDifficulty, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnActionCommandDifficulty* ev = (OnActionCommandDifficulty*) event;

        int32_t levels = CVarGetInteger(CVAR_ENHANCEMENT("ActionCommandDifficulty"), 0);

        if (levels <= 0) {
            return;
        }

        *ev->difficultyLevel -= levels;
    });
}

static RegisterShipInitFunc initActionCommandDifficultyFunc(RegisterActionCommandDifficulty_Init);
