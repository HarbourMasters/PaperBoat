#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

#include "common.h"
#include "nu/nusys.h"
#include "port/patches/Patches.h"

extern "C" {

// Port replacement for appendGfx_darkness_stencil (src/screen_render_util.c).

#define DARKNESS_STENCIL_W 64
#define DARKNESS_STENCIL_R 32

static u8 sDarknessStencil[DARKNESS_STENCIL_W * DARKNESS_STENCIL_W] ALIGNED(8);
static bool sDarknessStencilReady = false;

static void port_buildDarknessStencil(void) {
    if (sDarknessStencilReady) {
        return;
    }
    for (s32 y = 0; y < DARKNESS_STENCIL_W; y++) {
        for (s32 x = 0; x < DARKNESS_STENCIL_W; x++) {
            f32 dx = (f32) x - 31.5f;
            f32 dy = (f32) y - 31.5f;
            f32 d = sqrtf(dx * dx + dy * dy);
            f32 t = 1.0f - d / (f32) DARKNESS_STENCIL_R;
            if (t < 0.0f)
                t = 0.0f;
            if (t > 1.0f)
                t = 1.0f;
            // Soft falloff (smoothstep-ish) - squaring sharpens the edge.
            t = t * t * (3.0f - 2.0f * t);
            sDarknessStencil[y * DARKNESS_STENCIL_W + x] = (u8) (t * 255.0f);
        }
    }
    sDarknessStencilReady = true;
}

void port_appendGfx_darkness_stencil(b32 isWorld, s32 posX, s32 posY, f32 alpha, f32 progress) {
    Camera* camera = &gCameras[gCurrentCameraID];
    f32 texScale;
    f32 primA, envA;
    s32 sStart, tStart;
    s32 dsdx;
    s32 scissorLeft, scissorRight;
    s32 rectLeft, rectRight;

    if (alpha == 0.0f || progress == 0.0f) {
        return;
    }

    port_buildDarknessStencil();

    if (!isWorld) {
        texScale = (255.0f - alpha) * 10.0f / 255.0f + 0.14f;
    } else {
        texScale = 0.5f + (255.0f - alpha) * 9.5f / 255.0f;
        posX += (camera->viewportW / 2 - posX) * (255.0f - alpha) / 255.0f;
        posY += (camera->viewportH / 2 - posY) * (255.0f - alpha) / 255.0f;
    }

    primA = alpha * 0.25f * progress / 255.0f;
    envA = progress - primA;
    if (primA < 0.0f)
        primA = 0.0f;
    if (primA > 255.0f)
        primA = 255.0f;
    if (envA < 0.0f)
        envA = 0.0f;
    if (envA > 255.0f)
        envA = 255.0f;

    // Reuses the original's hardcoded centering constants (9, 32 for world;
    // 12, 19 for battle)
    dsdx = (s32) (1024.0f / texScale);
    if (!isWorld) {
        sStart = (s32) ((12.0f - (f32) posX) * 32.0f / texScale + 16.0f + 1024.0f);
        tStart = (s32) ((19.0f - (f32) posY) * 32.0f / texScale + 16.0f + 1024.0f);
    } else {
        sStart = (s32) ((9.0f - (f32) posX) * 32.0f / texScale + 1024.0f);
        tStart = (s32) ((32.0f - (f32) posY) * 32.0f / texScale + 1024.0f);
    }

    gDPPipeSync(gMainGfxPos++);

    get_cam_scissor_x(gCurrentCameraID, &scissorLeft, &scissorRight);
    gDPSetScissor(
        gMainGfxPos++, G_SC_NON_INTERLACE, scissorLeft, camera->viewportStartY, scissorRight,
        camera->viewportStartY + camera->viewportH
    );
    gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
    gDPSetTexturePersp(gMainGfxPos++, G_TP_NONE);
    gDPSetTextureFilter(gMainGfxPos++, G_TF_BILERP);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
    gDPSetTextureDetail(gMainGfxPos++, G_TD_CLAMP);
    gDPSetTextureLOD(gMainGfxPos++, G_TL_TILE);
    gDPSetColorDither(gMainGfxPos++, G_CD_MAGICSQ);
    gDPSetAlphaDither(gMainGfxPos++, G_AD_PATTERN);
    gDPSetRenderMode(gMainGfxPos++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
    gSPTexture(gMainGfxPos++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

    gDPLoadTextureTile(
        gMainGfxPos++, sDarknessStencil, G_IM_FMT_I, G_IM_SIZ_8b, DARKNESS_STENCIL_W, DARKNESS_STENCIL_W, 0, 0,
        DARKNESS_STENCIL_W - 1, DARKNESS_STENCIL_W - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 6, 6,
        G_TX_NOLOD, G_TX_NOLOD
    );

    // Color: forced black. Alpha: (1 - TEXEL0) * ENV + PRIM. With our mask
    // (bright at center, dark at edges), this gives near-PRIM at the center
    // (Mario barely darkened) and ENV+PRIM at the edges (corners saturate to
    // fully black when ENV is near 230).
    gDPSetCombineLERP(
        gMainGfxPos++, 0, 0, 0, 0, 1, TEXEL0, ENVIRONMENT, PRIMITIVE, 0, 0, 0, 0, 1, TEXEL0, ENVIRONMENT, PRIMITIVE
    );
    gDPSetPrimColor(gMainGfxPos++, 0, 0, 0, 0, 0, (u8) primA);
    gDPSetEnvColor(gMainGfxPos++, 0, 0, 0, (u8) envA);

    rectLeft = camera->viewportStartX;
    rectRight = camera->viewportStartX + camera->viewportW;
    if (gCurrentCameraID == CAM_DEFAULT || gCurrentCameraID == CAM_BATTLE) {
        rectLeft = OTRGetRectDimensionFromLeftEdge(0);
        rectRight = OTRGetRectDimensionFromRightEdge(0);
        // s advances 32/texScale per pixel, so re-anchor it for the new left edge and the
        // pattern stays put over Mario instead of sliding as the rect grows sideways
        sStart += (s32) ((rectLeft - camera->viewportStartX) * 32.0f / texScale);
    }

    gSPWideTextureRectangle(
        gMainGfxPos++, rectLeft * 4, camera->viewportStartY * 4, rectRight * 4,
        (camera->viewportStartY + camera->viewportH) * 4, G_TX_RENDERTILE, sStart, tStart, dsdx, dsdx
    );
    gDPPipeSync(gMainGfxPos++);
}

}
