#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"
#include "port/ShipInit.hpp"

void RegisterPartnerlessCrashProtection_Init() {
    REGISTER_LISTENER(OnPartnerlessCrashProtectionCheck, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnPartnerlessCrashProtectionCheck* ev = (OnPartnerlessCrashProtectionCheck*) event;
        *ev->enabled = CVarGetInteger(CVAR_ENHANCEMENT("PartnerlessCrashProtection"), 0) != 0;
    });
}

static RegisterShipInitFunc initPartnerlessCrashProtection(RegisterPartnerlessCrashProtection_Init);
