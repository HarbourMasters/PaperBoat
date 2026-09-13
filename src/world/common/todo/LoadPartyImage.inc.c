#include "common.h"
#include "npc.h"
#include "port/Engine.h"
#include "port/patches/Patches.h"

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

    // Drawn by name where the archive has the portrait as a texture
    image.palette = (PAL_BIN*)port_named_image(imgPath, "_img_tlut", LOAD_ASSET(palPath));
    image.raster = (IMG_BIN*)port_named_image(imgPath, "_img", LOAD_ASSET(imgPath));
    image.width = PARTY_IMAGE_WIDTH;
    image.height = PARTY_IMAGE_HEIGHT;
    image.format = G_IM_FMT_CI;
    image.bitDepth = G_IM_SIZ_8b;
    set_message_images(&image);
    return ApiStatus_DONE2;
}

#undef PARTY_IMAGE
