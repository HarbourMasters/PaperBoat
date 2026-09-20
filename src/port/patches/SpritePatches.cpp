#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

#include "common.h"
#include "sprite.h"
#include "port/patches/Patches.h"

extern "C" {

// The component's own palette, which the two-tone one is built from.
static PAL_PTR sShadingSourcePalette;

// One palette per shaded component: the display list is built now and run later, so a
// single buffer would leave every component drawing with the last one written.
#define SHADING_PALETTE_COUNT 512
static PAL_BIN sShadingPalettes[SHADING_PALETTE_COUNT][16];
static s32 sShadingPaletteIdx;

void port_set_shading_source_palette(PAL_PTR palette) {
    sShadingSourcePalette = palette;
}

void port_appendGfx_shading_palette(
    Matrix4f mtx,
    s32 uls,
    s32 ult,
    s32 lrs,
    s32 lrt,
    s32 alpha,
    f32 shadowX,
    f32 shadowY,
    f32 shadowZ,
    s32 shadowR,
    s32 shadowG,
    s32 shadowB,
    s32 highlightR,
    s32 highlightG,
    s32 highlightB,
    s32 ambientPower,
    s32 renderMode
) {
    Camera* camera = &gCameras[gCurrentCameraID];
    f32 mtx01, mtx11, mtx21;
    f32 offsetX, offsetY;
    f32 shadowMag;
    f32 var_f12_2;
    f32 shadowXZ;
    f32 facingDir;
    f32 pm02, pm22;

    shadowMag = SQ(shadowX) + SQ(shadowY) + SQ(shadowZ);

    if (shadowMag < 1.0) {
        ambientPower *= shadowMag;
    }
    if (shadowMag != 0.0f) {
        shadowMag = 1.0f / sqrtf(shadowMag);
    }
    shadowX *= shadowMag;
    shadowY *= shadowMag;
    shadowZ *= shadowMag;

    if (((-mtx[0][2] * camera->mtxPerspective[0][2]) + (mtx[2][2] * camera->mtxPerspective[2][2])) < 0.0f) {
        facingDir = 1.0f;
    } else {
        facingDir = -1.0f;
    }

    pm02 = camera->mtxPerspective[0][2];
    pm22 = camera->mtxPerspective[2][2];

    offsetX = ambientPower * ((shadowX * -pm22) + (shadowZ * pm02));

    shadowXZ = SQ(shadowX) + SQ(shadowZ);
    if (shadowXZ != 0.0f) {
        shadowXZ = sqrtf(shadowXZ);
    }
    mtx01 = mtx[0][1];
    mtx11 = mtx[1][1];
    mtx21 = mtx[2][1];
    var_f12_2 = SQ(mtx01) + SQ(mtx21);
    if (var_f12_2 != 0.0f) {
        var_f12_2 = sqrtf(var_f12_2);
    }
    offsetY = -((shadowXZ * var_f12_2) + (shadowY * mtx11)) * ambientPower;

    // Per-channel clamp to 8-bit.
    if (shadowR > 255) {
        shadowR = 255;
    }
    if (shadowG > 255) {
        shadowG = 255;
    }
    if (shadowB > 255) {
        shadowB = 255;
    }
    if (highlightR > 255) {
        highlightR = 255;
    }
    if (highlightG > 255) {
        highlightG = 255;
    }
    if (highlightB > 255) {
        highlightB = 255;
    }

    // [port] The N64 built this palette by drawing a 16x2 rectangle and reading it back, which
    // stalled the GPU once per shaded component. PM_CC_55 over a 1-bit alpha only selects
    // between two colours, so fill it directly: opaque entries take the shadow tone.
    PAL_BIN* palette = sShadingPalettes[sShadingPaletteIdx];
    sShadingPaletteIdx = (sShadingPaletteIdx + 1) % SHADING_PALETTE_COUNT;
    s32 opaque = 0;
    s32 transparent = 0;
    {
        const u8* source = (const u8*) port_sprite_palette_data(sShadingSourcePalette);
        u8* out = (u8*) palette;
        const u16 shadow = ((shadowR >> 3) << 11) | ((shadowG >> 3) << 6) | ((shadowB >> 3) << 1) | 1;
        const u16 highlight = ((highlightR >> 3) << 11) | ((highlightG >> 3) << 6) | ((highlightB >> 3) << 1) | 1;
        s32 i;
        for (i = 0; i < 16; i++) {
            const b32 isOpaque = source != NULL && (source[i * 2 + 1] & 1);
            const u16 entry = isOpaque ? shadow : highlight;
            out[i * 2 + 0] = entry >> 8;
            out[i * 2 + 1] = entry & 0xFF;
            if (isOpaque) {
                opaque = i;
            } else {
                transparent = i;
            }
        }
    }

    // HD art is then shaded by its own silhouette rather than the raster's
    gDPPaletteMask(gMainGfxPos++, palette, opaque, transparent);
    gDPLoadTLUT_pal16(gMainGfxPos++, 1, palette);
    // Drop textures cached against this palette address: the ring comes back to it later.
    gDPInvalTexByPalette(gMainGfxPos++, palette);

    gSPSetOtherMode(
        gMainGfxPos++, G_SETOTHERMODE_H, 4, 18,
        G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP
            | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE
    );

    gDPSetRenderMode(gMainGfxPos++, G_RM_PASS, renderMode);
    gDPSetEnvColor(gMainGfxPos++, 100, 100, 100, 255);

    if (alpha == 255) {
        gDPSetCombineMode(gMainGfxPos++, PM_CC_50, PM_CC_52);
    } else {
        gDPSetCombineMode(gMainGfxPos++, PM_CC_51, PM_CC_52);
    }

    gDPSetTileSize(
        gMainGfxPos++,
        0,
        ((uls + 0x100) << 2) + (s32) (offsetX * facingDir),
        ((ult + 0x100) << 2) + (s32) offsetY,
        ((lrs + 0x100 - 1) << 2) + (s32) (offsetX * facingDir),
        ((lrt + 0x100 - 1) << 2) + (s32) offsetY
    );
}

}
