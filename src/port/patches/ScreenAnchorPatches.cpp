#include "common.h"
#include "port/patches/Patches.h"

extern "C" {

// Shop prices and message popups etc are placed once per game frame, so as texture rectangles they
// lag the interpolated world. Inside an anchor, rectangles become quads under a matrix that interpolation
// can move.

static bool sAnchorOpen;
static s32 sAnchorX;
static s32 sAnchorY;
static Vp sAnchorViewport = { { { SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, G_MAXZ / 2, 0 },
                                { SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, G_MAXZ / 2, 0 } } };

void port_rect_anchor_begin(const void* key, uintptr_t index, s32 x, s32 y) {
    FrameInterpolation_RecordOpenChild(key, index);

    guOrtho(&gDisplayContext->matrixStack[gMatrixListPos], 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f, 1.0f);
    gSPMatrix(
        gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION
    );
    guTranslate(&gDisplayContext->matrixStack[gMatrixListPos], x, y, 0.0f);
    gSPMatrix(
        gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW
    );
    gSPViewport(gMainGfxPos++, &sAnchorViewport);
    gSPLoadGeometryMode(gMainGfxPos++, 0);
    gSPTexture(gMainGfxPos++, -1, -1, 0, G_TX_RENDERTILE, G_ON);

    sAnchorOpen = true;
    sAnchorX = x;
    sAnchorY = y;
}

void port_rect_anchor_end(void) {
    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    FrameInterpolation_RecordCloseChild();
    sAnchorOpen = false;
}

// Takes gSPWideTextureRectangle's arguments
void port_wide_texture_rectangle(s32 ulx, s32 uly, s32 lrx, s32 lry, s32 tile, s32 s, s32 t, s32 dsdx, s32 dtdy) {
    if (!sAnchorOpen) {
        gSPWideTextureRectangle(gMainGfxPos++, ulx, uly, lrx, lry, tile, s, t, dsdx, dtdy);
        return;
    }

    const s32 slots = (4 * sizeof(Vtx) + sizeof(Gfx) - 1) / sizeof(Gfx);
    Vtx* vtx = (Vtx*) (gMainGfxPos + 1);
    gSPBranchList(gMainGfxPos, gMainGfxPos + 1 + slots);
    gMainGfxPos += 1 + slots;

    const s16 x0 = (ulx >> 2) - sAnchorX;
    const s16 y0 = (uly >> 2) - sAnchorY;
    const s16 x1 = (lrx >> 2) - sAnchorX;
    const s16 y1 = (lry >> 2) - sAnchorY;
    const s16 s0 = s;
    const s16 t0 = t;
    const s16 s1 = ((s << 7) + dsdx * (lrx - ulx)) >> 7;
    const s16 t1 = ((t << 7) + dtdy * (lry - uly)) >> 7;
    const s16 corners[4][4] = { { x0, y0, s0, t0 }, { x1, y0, s1, t0 }, { x1, y1, s1, t1 }, { x0, y1, s0, t1 } };
    for (s32 i = 0; i < 4; i++) {
        vtx[i].v.ob[0] = corners[i][0];
        vtx[i].v.ob[1] = corners[i][1];
        vtx[i].v.ob[2] = 0;
        vtx[i].v.flag = 0;
        vtx[i].v.tc[0] = corners[i][2];
        vtx[i].v.tc[1] = corners[i][3];
        vtx[i].v.cn[0] = vtx[i].v.cn[1] = vtx[i].v.cn[2] = vtx[i].v.cn[3] = 255;
    }

    gSPVertex(gMainGfxPos++, vtx, 4, 0);
    gSP2Triangles(gMainGfxPos++, 0, 3, 1, 0, 3, 2, 1, 0);
}

} // extern "C"
