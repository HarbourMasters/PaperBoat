#include "port/hooks/Events.h"
#include "port/patches/Patches.h"
#include "port/ShipInit.hpp"

static void RegisterFramebufferPatches_Init() {
    REGISTER_LISTENER(BackgroundPreDraw, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        auto* ev = (BackgroundPreDraw*) event;

        if (ev->bgRenderState == 0) {
            return;
        }

        port_appendGfx_pause_background(ev->bgRenderState);
        ev->Event.Cancelled = true;
    });
}

static RegisterShipInitFunc initFunc(RegisterFramebufferPatches_Init);
