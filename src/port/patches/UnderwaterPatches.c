#include "common.h"
#include "effects_internal.h"
#include "nu/nusys.h"
#include "port/Engine.h"
#include "port/patches/Patches.h"

// Port-side reimplementation of underwater_appendGfx (src/effects/underwater.c).

#define UW_COLS 18
#define UW_ROWS 12
#define UW_CELL 16

#define UW_ORIGIN_X 16
#define UW_ORIGIN_Y 24

// Full 0,0,320,240 viewport, as msg.c's D_8014C280.
static Vp sUnderwaterFullVp = { .vp = {
                                    .vscale = { 640, 480, 511, 0 },
                                    .vtrans = { 640, 480, 511, 0 },
                                } };

// Double-buffered: the display list is submitted at end of frame, so the
// vertices it points at must outlive the build pass.
static Vtx sUnderwaterVtx[2][UW_COLS * UW_ROWS * 4];

// DEPRECATES underwater_appendGfx
void port_underwater_appendGfx(void* effect) {
    UnderwaterFXData* data = ((EffectInstance*) effect)->data.underwater;
    s32 alpha = data->waterColor.a;
    u16* mirror = port_getSceneMirrorSentinel();
    Vtx* vtxBuf = sUnderwaterVtx[gCurrentDisplayContextIndex];

    s32 visLeft = OTRGetRectDimensionFromLeftEdge(0);
    s32 visRight = OTRGetRectDimensionFromRightEdge(0);

    Matrix4f mtx;
    s32 i, j;
    s32 vtxPos = 0;

    gDPPipeSync(gMainGfxPos++);

    port_emitSceneMirrorCapture(&gMainGfxPos);

    gDPSetPrimColor(gMainGfxPos++, 0, 0, data->waterColor.r, data->waterColor.g, data->waterColor.b, alpha >> 1);
    gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
    gDPSetCombineMode(gMainGfxPos++, PM_CC_48, PM_CC_48);
    gDPSetRenderMode(
        gMainGfxPos++, CVG_DST_SAVE | ZMODE_OPA | FORCE_BL | G_RM_PASS,
        CVG_DST_SAVE | ZMODE_OPA | FORCE_BL | GBL_c2(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)
    );
    gDPSetTexturePersp(gMainGfxPos++, G_TP_NONE);
    gDPSetTextureFilter(gMainGfxPos++, G_TF_BILERP);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
    gDPSetTextureDetail(gMainGfxPos++, G_TD_CLAMP);
    gDPSetTextureLOD(gMainGfxPos++, G_TL_TILE);
    gSPTexture(gMainGfxPos++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

    // Tile dimensions are what normalises the UVs, and a registered FB texture
    // ignores the sub-rect, so we declare the whole frame.
    gDPLoadTextureTile(
        gMainGfxPos++, osVirtualToPhysical(mirror), G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0,
        SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
    );

    // Absolute screen coordinates, so bypass the battle camera's 12,20,296,200
    // viewport. Restored at the end.
    gSPViewport(gMainGfxPos++, &sUnderwaterFullVp);

    // Screen-space ortho in 10.2 units, keeping the wave offsets' sub-pixel
    // precision. bottom > top so +y runs downward.
    guOrthoF(mtx, 0.0f, SCREEN_WIDTH * 4.0f, SCREEN_HEIGHT * 4.0f, 0.0f, -500.0f, 500.0f, 1.0f);
    guMtxF2L(mtx, &gDisplayContext->matrixStack[gMatrixListPos]);
    gSPMatrix(
        gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION
    );

    guMtxIdentF(mtx);
    guMtxF2L(mtx, &gDisplayContext->matrixStack[gMatrixListPos]);
    gSPMatrix(
        gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW
    );

    gSPClearGeometryMode(gMainGfxPos++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gMainGfxPos++, G_SHADE | G_SHADING_SMOOTH);

    for (j = 0; j < UW_ROWS; j++) {
        s32 y = j * UW_CELL + UW_ORIGIN_Y;

        for (i = 0; i < UW_COLS; i++) {
            s32 x = i * UW_CELL + UW_ORIGIN_X;

            // Edge cells run out to the screen edge instead of the hardware's 4px
            // overhang. Seamless because underwater_update only writes
            // unk_23[1..17][1..11], leaving the outer ring undisplaced.
            s32 srcLeft = (i == 0) ? visLeft : x;
            s32 srcRight = (i == UW_COLS - 1) ? visRight : x + UW_CELL;
            s32 srcTop = (j == 0) ? 0 : y;
            s32 srcBottom = (j == UW_ROWS - 1) ? SCREEN_HEIGHT : y + UW_CELL;

            // 10.2, displaced vertically by the wave.
            s32 dstLeft = srcLeft * 4;
            s32 dstRight = srcRight * 4;
            s32 dstTopL = srcTop * 4 + data->unk_23[i][j];
            s32 dstTopR = srcTop * 4 + data->unk_23[i + 1][j];
            s32 dstBotL = srcBottom * 4 + data->unk_23[i][j + 1];
            s32 dstBotR = srcBottom * 4 + data->unk_23[i + 1][j + 1];

            s32 uLeft = port_fbMirrorS(srcLeft);
            s32 uRight = port_fbMirrorS(srcRight);
            s32 vTop = srcTop * 32;
            s32 vBottom = srcBottom * 32;

            Vtx* v = &vtxBuf[vtxPos];

            v[0].v.ob[0] = dstLeft;
            v[0].v.ob[1] = dstTopL;
            v[0].v.ob[2] = 0;
            v[0].v.tc[0] = uLeft;
            v[0].v.tc[1] = vTop;
            v[1].v.ob[0] = dstRight;
            v[1].v.ob[1] = dstTopR;
            v[1].v.ob[2] = 0;
            v[1].v.tc[0] = uRight;
            v[1].v.tc[1] = vTop;
            v[2].v.ob[0] = dstLeft;
            v[2].v.ob[1] = dstBotL;
            v[2].v.ob[2] = 0;
            v[2].v.tc[0] = uLeft;
            v[2].v.tc[1] = vBottom;
            v[3].v.ob[0] = dstRight;
            v[3].v.ob[1] = dstBotR;
            v[3].v.ob[2] = 0;
            v[3].v.tc[0] = uRight;
            v[3].v.tc[1] = vBottom;

            // PM_CC_48 reads SHADE for alpha only, the tint is all prim color.
            for (s32 k = 0; k < 4; k++) {
                v[k].v.flag = 0;
                v[k].v.cn[0] = 0;
                v[k].v.cn[1] = 0;
                v[k].v.cn[2] = 0;
                v[k].v.cn[3] = 255;
            }

            gSPVertex(gMainGfxPos++, v, 4, 0);
            gSP2Triangles(gMainGfxPos++, 0, 3, 1, 0, 0, 2, 3, 0);
            vtxPos += 4;
        }
    }

    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    gDPPipeSync(gMainGfxPos++);
    gSPViewport(gMainGfxPos++, &gCameras[gCurrentCameraID].vp);
    gSPMatrix(
        gMainGfxPos++, &gDisplayContext->camPerspMatrix[gCurrentCameraID], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION
    );
    gDPPipeSync(gMainGfxPos++);
}
