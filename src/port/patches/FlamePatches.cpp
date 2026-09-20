#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

#include "common.h"
#include "effects_internal.h"
#include "assets/effects.h"
#include "nu/nusys.h"
#include "port/patches/Patches.h"
#include <string.h>

extern "C" {

// Port-side reimplementation of flame_appendGfx (src/effects/flame.c).
//
// Pipeline (once per game frame, gated by LastFlameRenderFrame):
//   1. GPU clear of sFbBlend (PM_CC_CONST_ALPHA_1).
//   2. GPU blend of two noise textures into sFbBlend (PM_CC_36/37).
//   3. gDPReadFBToI8: queue readback of sFbBlend into sFlameBlendCpu,
//      converting RGBA5551 -> I8 in place.
//   4. Three CPU iterations of flame_distort_cpu producing sFlameReadbackB
//      from sFlameBlendCpu, with UV offsets (+1,0), (-1,0), (0,+1).
//   5. GameEngine_InvalidateTextureCache(sFlameReadbackB) so the per-particle
//      draw re-uploads the freshly written bytes.
//
// Per particle: emit sFlameDrawDL (loads sFlameReadbackB as I8, sets up the
// 2-cycle combiner PM_CC_34/35) and apply per-preset key/prim/env color and
// the model matrix.
//
// LUS extensions this relies on:
//   - gDPReadFBToI8: queued FB readback with RGBA5551 -> I8 conversion.
//   - gDPSetKeyR / gDPSetKeyGB: chroma-key combiner inputs (CENTER/SCALE).


// Mirrors the layout of flame.c's local FlamePreset struct.
typedef struct FlamePreset {
    /* 0x00 */ Color_RGB8 colorScale;
    /* 0x03 */ s8 keyCenter;
    /* 0x04 */ Color_RGB8 envColor;
    /* 0x07 */ s8 primIntensity;
    /* 0x08 */ u8 sizeScale;
    /* 0x0C */ Gfx* dlist;
} FlamePreset;
extern FlamePreset FlamePresets[];
extern s32 LastFlameRenderFrame;

#define FLAME_TEX_W 32
#define FLAME_TEX_H 64

static s32 sFbBlend = -1;

// sFlameBlendCpu is sized for u16 because gDPReadFBToI8 writes w*h RGBA5551
// values into it before compacting in place to w*h I8 in the first half.
static u16 sFlameBlendCpu[FLAME_TEX_W * FLAME_TEX_H];
// sFlameReadbackB holds the CPU distort output (I8); sampled by sFlameDrawDL.
static u16 sFlameReadbackB[FLAME_TEX_W * FLAME_TEX_H];

// Scratch buffers for ping-ponging the 3 distort iterations.
static u8 sFlameWorkA[FLAME_TEX_W * FLAME_TEX_H];
static u8 sFlameWorkB[FLAME_TEX_W * FLAME_TEX_H];

// Static sub-DL: clear + two-noise blend into the currently bound FB.
static Gfx sFlameRttPass12[] = {
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, FLAME_TEX_W, FLAME_TEX_H),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_PASS, G_RM_CLD_SURF2),
    // Pass 1: clear
    gsDPSetCombineMode(PM_CC_CONST_ALPHA_1, PM_CC_CONST_ALPHA_1),
    gsSPTextureRectangle(0, 0, 0x0080, 0x0100, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400),
    gsDPPipeSync(),
    // Pass 2: blend the two noise textures loaded on tiles 0/1
    gsDPSetCombineMode(PM_CC_36, PM_CC_37),
    gsSPTextureRectangle(0, 0, 0x0080, 0x0100, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// Per-particle draw DL. Loads sFlameReadbackB as an I8 texture (alpha =
// intensity) and applies the chroma-key combiner.
static Gfx sFlameDrawDL[] = {
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetAlphaDither(G_AD_PATTERN),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_CLD_SURF2),
    gsDPLoadTextureTile(
        sFlameReadbackB,
        G_IM_FMT_I,
        G_IM_SIZ_8b,
        FLAME_TEX_W,
        0,
        0,
        0,
        31,
        63,
        0,
        G_TX_NOMIRROR | G_TX_CLAMP,
        G_TX_NOMIRROR | G_TX_CLAMP,
        5,
        6,
        G_TX_NOLOD,
        G_TX_NOLOD
    ),
    gsDPSetCombineMode(PM_CC_34, PM_CC_35),
    gsSPClearGeometryMode(G_CULL_BOTH | G_LIGHTING),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

static inline u8 flame_sat8(s32 v) {
    if (v < 0)
        return 0;
    if (v > 255)
        return 255;
    return (u8) v;
}

// CPU evaluation of one two-cycle combiner pass with constants K4=92,
// primA=0x78, envA=0xA4:
//   c1 = T0 + (T1 - K4) * primA / 255
//   a1 = clamp(envA + (T0 - T1) * envA / 255, 0, 255)
//   c2 = c1 + (T1 - K4) * a1 / 255
// T1 is sampled at (x+dx, y+dy): H wraps, V clamps.
static void flame_distort_cpu(u8* dst, const u8* t0_src, const u8* t1_src, s32 dx, s32 dy) {
    const s32 K4 = 92;
    const s32 PRIMA = 0x78;
    const s32 ENVA = 0xA4;
    for (s32 y = 0; y < FLAME_TEX_H; y++) {
        for (s32 x = 0; x < FLAME_TEX_W; x++) {
            s32 t0 = t0_src[y * FLAME_TEX_W + x];
            s32 sx = (x + dx) & (FLAME_TEX_W - 1);
            s32 sy = y + dy;
            if (sy < 0) {
                sy = 0;
            } else if (sy >= FLAME_TEX_H) {
                sy = FLAME_TEX_H - 1;
            }
            s32 t1 = t1_src[sy * FLAME_TEX_W + sx];
            s32 c1 = t0 + ((t1 - K4) * PRIMA) / 255;
            s32 a1 = ENVA + ((t0 - t1) * ENVA) / 255;
            if (a1 < 0) {
                a1 = 0;
            } else if (a1 > 255) {
                a1 = 255;
            }
            s32 c2 = c1 + ((t1 - K4) * a1) / 255;
            dst[y * FLAME_TEX_W + x] = flame_sat8(c2);
        }
    }
}

void port_flame_appendGfx(void* effect) {
    FlameFXData* data = ((EffectInstance*) effect)->data.flame;
    Camera* camera = &gCameras[gCurrentCameraID];
    s32 type = data->type;
    s32 uls = data->unk_1C * 4.0f;
    s32 ult = data->unk_24 * 4.0f;
    FlamePreset* preset;
    Matrix4f sp18, sp58, sp98;
    u8* readback = (u8*) sFlameReadbackB;
    u8* blendCpu = (u8*) sFlameBlendCpu;
    s32 scissorLeft, scissorRight;

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*) effect)->shared->graphics));

    if (LastFlameRenderFrame != gGameStatusPtr->frameCounter) {
        LastFlameRenderFrame = gGameStatusPtr->frameCounter;

        if (sFbBlend < 0) {
            sFbBlend = gfx_create_framebuffer(FLAME_TEX_W, FLAME_TEX_H, FLAME_TEX_W, FLAME_TEX_H, 0, 0);
        }

        // Tile 0/1: two noise textures from the original effect DL.
        gSPDisplayList(gMainGfxPos++, D_09000918_3544C8);
        gDPSetTileSize(gMainGfxPos++, 1, uls, ult, uls + 128, ult + 256);

        gsSPSetFB(gMainGfxPos++, sFbBlend);
        gSPDisplayList(gMainGfxPos++, sFlameRttPass12);
        gsSPResetFB(gMainGfxPos++);

        // Queue readback of sFbBlend into sFlameBlendCpu; the renderer
        // executes it after this callback returns, populating the buffer
        // for next frame's CPU distort.
        gDPReadFBToI8(gMainGfxPos++, sFbBlend, sFlameBlendCpu, 0, 0, FLAME_TEX_W, FLAME_TEX_H, 0);

        gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, VIRTUAL_TO_PHYSICAL(nuGfxCfb_ptr));

        get_cam_scissor_x(gCurrentCameraID, &scissorLeft, &scissorRight);
        gDPSetScissorFrac(
            gMainGfxPos++, G_SC_NON_INTERLACE, scissorLeft * 4.0f, camera->viewportStartY * 4.0f, scissorRight * 4.0f,
            (camera->viewportStartY + camera->viewportH) * 4.0f
        );

        // CPU passes 3-5 on LAST FRAME's blend bytes. T0 is the blend
        // (constant across iterations); T1 is the previous iteration's
        // output. UV offsets and combiner constants match the original.
        flame_distort_cpu(sFlameWorkA, blendCpu, blendCpu, +1, 0);
        flame_distort_cpu(sFlameWorkB, blendCpu, sFlameWorkA, -1, 0);
        flame_distort_cpu(readback, blendCpu, sFlameWorkB, 0, +1);

        GameEngine_InvalidateTextureCache(sFlameReadbackB);
    }

    preset = &FlamePresets[type];

    gSPDisplayList(gMainGfxPos++, sFlameDrawDL);
    gDPSetKeyR(gMainGfxPos++, preset->keyCenter, preset->colorScale.r, 0);
    gDPSetKeyGB(gMainGfxPos++, preset->keyCenter, preset->colorScale.g, 0, preset->keyCenter, preset->colorScale.b, 0);
    gDPSetPrimColor(gMainGfxPos++, 0, 0, preset->primIntensity, preset->primIntensity, preset->primIntensity, 0);
    gDPSetEnvColor(gMainGfxPos++, preset->envColor.r, preset->envColor.g, preset->envColor.b, 0);

    guTranslateF(sp18, data->pos.x, data->pos.y, data->pos.z);
    guRotateF(sp58, -gCameras[gCurrentCameraID].curYaw, 0.0f, 1.0f, 0.0f);
    guMtxCatF(sp58, sp18, sp98);
    guScaleF(sp58, data->baseScale * data->scaleW, data->baseScale * data->scaleH, data->baseScale);
    guMtxCatF(sp58, sp98, sp98);
    guMtxF2L(sp98, &gDisplayContext->matrixStack[gMatrixListPos]);

    gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPDisplayList(gMainGfxPos++, D_090008F8_3544A8);
    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    gDPPipeSync(gMainGfxPos++);
}

}
