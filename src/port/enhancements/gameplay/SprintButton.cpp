#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"
#include "port/ShipInit.hpp"

extern "C" {
#include "common_structs.h"
#include "enums.h"

extern PlayerStatus gPlayerStatus;

// Default player speeds
extern f32 DefaultWalkSpeed;
extern f32 DefaultRunSpeed;
}

#define SPRINT_MULTIPLIER 2.0f

static bool sSprintApplied = false;

void RegisterSprintButton_Init() {
    REGISTER_LISTENER(OnPlayerSpeedUpdate, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnPlayerSpeedUpdate* ev = (OnPlayerSpeedUpdate*) event;
        f32 multiplier = SPRINT_MULTIPLIER;

        if (!CVarGetInteger(CVAR_ENHANCEMENT("SprintButton"), 0)) {
            multiplier = 1.0f;
        } else if (gPlayerStatus.flags & PS_FLAG_CUTSCENE_MOVEMENT) {
            multiplier = 1.0f;
        } else if (!(gPlayerStatus.curButtons & BUTTON_R)) {
            multiplier = 1.0f;
        }

        if (multiplier == 1.0f) {
            if (!sSprintApplied) {
                return;
            }

            sSprintApplied = false;
        } else {
            sSprintApplied = true;
        }

        *ev->walkSpeed = DefaultWalkSpeed * multiplier;
        *ev->runSpeed = DefaultRunSpeed * multiplier;
    });
}

static RegisterShipInitFunc initSprintButtonFunc(RegisterSprintButton_Init);
