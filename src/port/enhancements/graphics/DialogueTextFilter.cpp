#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"

#include "common.h"

static ListenerID sFilterSetListener = -1;

void RegisterDialogueTextFilter_Init() {
    UNREGISTER_LISTENER(MessageTextFilterSet, sFilterSetListener);
    sFilterSetListener = -1;

    if (!CVarGetInteger(CVAR_DIALOGUE_TEXT_FILTER, 0)) {
        return;
    }

    sFilterSetListener = REGISTER_LISTENER(MessageTextFilterSet, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        gDPSetTextureFilter(gMainGfxPos++, G_TF_POINT);
    });
}

static RegisterShipInitFunc initDialogueTextFilterFunc(RegisterDialogueTextFilter_Init, { CVAR_DIALOGUE_TEXT_FILTER });
