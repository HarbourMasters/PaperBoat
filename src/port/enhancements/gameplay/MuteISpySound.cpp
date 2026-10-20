#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"
#include "port/ShipInit.hpp"

extern "C" {
#include "common_structs.h"
#include "enums.h"
}

void RegisterMuteISpySound_Init() {
    REGISTER_LISTENER(OnISpySoundPlay, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnISpySoundPlay* ev = (OnISpySoundPlay*) event;
        if (!CVarGetInteger(CVAR_ENHANCEMENT("MuteISpySound"), 0)) {
            *ev->SoundPlay = true;
            return;
        }
        *ev->SoundPlay = false;
    });
}

static RegisterShipInitFunc initMuteISpySound(RegisterMuteISpySound_Init);
