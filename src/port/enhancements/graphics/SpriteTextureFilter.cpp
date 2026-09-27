#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"

#include "common.h"

static ListenerID sComponentListener = -1;
static ListenerID sShadingListener = -1;

void RegisterSpriteTextureFilter_Init() {
    UNREGISTER_LISTENER(SpriteComponentPreDraw, sComponentListener);
    UNREGISTER_LISTENER(SpriteShadingPreDraw, sShadingListener);
    sComponentListener = -1;
    sShadingListener = -1;

    if (!CVarGetInteger(CVAR_2D_TEXTURE_FILTER, 0)) {
        return;
    }

    sComponentListener = REGISTER_LISTENER(SpriteComponentPreDraw, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        SpriteComponentPreDraw* ev = (SpriteComponentPreDraw*) event;

        gDPSetTextureFilter(gMainGfxPos++, G_TF_POINT);
        *ev->imgfxFlags |= IMGFX_FLAG_NO_FILTERING;
    });

    sShadingListener = REGISTER_LISTENER(SpriteShadingPreDraw, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        gDPSetTextureFilter(gMainGfxPos++, G_TF_POINT);
    });
}

static RegisterShipInitFunc initSpriteTextureFilterFunc(RegisterSpriteTextureFilter_Init, { CVAR_2D_TEXTURE_FILTER });
