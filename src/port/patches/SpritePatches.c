#include "common.h"
#include "sprite.h"
#include "port/patches/Patches.h"
#include "port/Engine.h"

extern int gfx_create_framebuffer(unsigned int width, unsigned int height,
                                  unsigned int native_width, unsigned int native_height,
                                  unsigned char resize);

extern u16 SpriteShadingPalette[16];

static s32 sShadingFbId = -1;


void port_appendGfx_shading_palette(
    Matrix4f mtx, s32 uls, s32 ult, s32 lrs, s32 lrt, s32 alpha,
    f32 shadowX, f32 shadowY, f32 shadowZ,
    s32 shadowR, s32 shadowG, s32 shadowB,
    s32 highlightR, s32 highlightG, s32 highlightB,
    s32 ambientPower, s32 renderMode)
{
    Camera* camera = &gCameras[gCurrentCameraID];
    f32 mtx01, mtx11, mtx21;
    f32 offsetX, offsetY;
    f32 shadowMag;
    f32 var_f12_2;
    f32 shadowXZ;
    f32 facingDir;
    f32 ex, ey, ez;
    f32 pm02, pm12, pm22;

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

    if (facingDir < 0.0f) {
        ex = mtx[0][2];
        ey = mtx[1][2];
        ez = -mtx[2][2];
    } else {
        ex = -mtx[0][2];
        ey = mtx[1][2];
        ez = mtx[2][2];
    }

    pm02 = camera->mtxPerspective[0][2];
    pm12 = camera->mtxPerspective[1][2];
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

    // Decomp per-channel clamp.
    if (shadowR > 255) { shadowR = 255; }
    if (shadowG > 255) { shadowG = 255; }
    if (shadowB > 255) { shadowB = 255; }
    if (highlightR > 255) { highlightR = 255; }
    if (highlightG > 255) { highlightG = 255; }
    if (highlightB > 255) { highlightB = 255; }

    // Create the GPU FB on first use.
    if (sShadingFbId < 0) {
        sShadingFbId = gfx_create_framebuffer(16, 2, 16, 2, 0);
    }

    gDPSetPrimColor(gMainGfxPos++, 0, 0, shadowR, shadowG, shadowB, alpha);
    gDPSetCombineMode(gMainGfxPos++, PM_CC_53, PM_CC_54);

    // Sample palette TMEM via custom gDPSetTextureImagePal (replaces the
    // decomp's N64 TMEM trick).
    gDPSetTextureImagePal(gMainGfxPos++, 2, 0);
    gDPSetTile(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0x100, 2,
               0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPSetTileSize(gMainGfxPos++, 2, 0, 0, (16 - 1) << 2, 0);

    // Render target is the shading FB (replaces decomp's gDPSetColorImage
    // that pointed directly at SpriteShadingPalette RAM).
    gsSPSetFB(gMainGfxPos++, sShadingFbId);
    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 16, 2);

    gDPPipeSync(gMainGfxPos++);
    gSPSetOtherMode(gMainGfxPos++, G_SETOTHERMODE_H, 4, 18,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                    G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE);
    gDPSetRenderMode(gMainGfxPos++, G_RM_OPA_SURF, G_RM_OPA_SURF2);

    gDPSetPrimColor(gMainGfxPos++, 0, 0, shadowR, shadowG, shadowB, alpha);
    gDPSetEnvColor(gMainGfxPos++, highlightR, highlightG, highlightB, 0);
    gDPSetCombineMode(gMainGfxPos++, PM_CC_55, PM_CC_55);
    gSPTextureRectangle(gMainGfxPos++, 0, 0, 16 << 2, 2 << 2, 2, 0, 0, 1 << 10, 1 << 10);
    gDPPipeSync(gMainGfxPos++);

    gsSPResetFB(gMainGfxPos++);

    gDPSetScissor(
        gMainGfxPos++, 0,
        camera->viewportStartX,
        camera->viewportStartY,
        camera->viewportStartX + camera->viewportW,
        camera->viewportStartY + camera->viewportH
    );

    // readback FB into SpriteShadingPalette RAM and load TLUT from it
    gDPReadFB(gMainGfxPos++, sShadingFbId, SpriteShadingPalette, 0, 0, 16, 1, 1);
    gDPLoadTLUT_pal16(gMainGfxPos++, 1, SpriteShadingPalette);
    // SpriteShadingPalette is a shared BSS buffer reused by every sprite. The
    // texture cache keys CI4 entries on {CI4 addr, palette dram addr}; without
    // this invalidate, a later sprite that shares a CI4 with an earlier sprite
    // (e.g. two Koopatrols) hits the earlier sprite's cached GPU texture with
    // baked-in palette content. Clearing entries keyed on this palette addr
    // forces per-sprite re-upload with the freshly-loaded palette.
    gDPInvalTexByPalette(gMainGfxPos++, SpriteShadingPalette);

    gSPSetOtherMode(gMainGfxPos++, G_SETOTHERMODE_H, 4, 18,
                    G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                    G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE);

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
        ((uls + 0x100) << 2) + (s32)(offsetX * facingDir),
        ((ult + 0x100) << 2) + (s32)offsetY,
        ((lrs + 0x100 - 1) << 2) + (s32)(offsetX * facingDir),
        ((lrt + 0x100 - 1) << 2) + (s32)offsetY
    );
}

