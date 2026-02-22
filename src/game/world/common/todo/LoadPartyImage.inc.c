#include "common.h"
#include "npc.h"
#include "port/Engine.h"

#ifndef PARTY_IMAGE
#error "Define PARTY_IMAGE to the asset name to use LoadPartyImage."
#endif

#define PARTY_IMAGE_WIDTH 150
#define PARTY_IMAGE_HEIGHT 105

API_CALLABLE(N(LoadPartyImage)) {
    static MessageImageData image;

    char palPath[64];
    char imgPath[64];
    snprintf(palPath, sizeof(palPath), "__OTR__party/%s_pal", PARTY_IMAGE);
    snprintf(imgPath, sizeof(imgPath), "__OTR__party/%s", PARTY_IMAGE);

    image.palette = (PAL_BIN*)LOAD_ASSET(palPath);
    image.raster = (IMG_BIN*)LOAD_ASSET(imgPath);
    image.width = PARTY_IMAGE_WIDTH;
    image.height = PARTY_IMAGE_HEIGHT;
    image.format = G_IM_FMT_CI;
    image.bitDepth = G_IM_SIZ_8b;
    set_message_images(&image);
    return ApiStatus_DONE2;
}

#undef PARTY_IMAGE
