#include "common.h"
#include "port/Engine.h"
#include "port/patches/Patches.h"

extern int gfx_create_framebuffer(unsigned int width, unsigned int height,
                                  unsigned int native_width, unsigned int native_height,
                                  unsigned char resize, unsigned char forceFixedAspect);
extern void gfx_register_fb_texture(const void* cpuAddr, int fbId);

// GPU framebuffer plus a registered CPU sentinel, so binding the sentinel as a
// texture binds the FB directly. Consumers must declare the full frame as the
// tile and use absolute screen-space UVs: a registered FB texture ignores the
// tile's uls/ult sub-rect.
static void ensureMirror(s32* fbId, const u16* sentinel) {
    if (*fbId < 0) {
        *fbId = gfx_create_framebuffer(SCREEN_WIDTH, SCREEN_HEIGHT,
                                       SCREEN_WIDTH, SCREEN_HEIGHT, 1, 0);
        gfx_register_fb_texture(sentinel, *fbId);
    }
}

// Screen X (320-space) -> S in S10.5 for a full-frame mirror tile. Renormalised
// against the visible range because at wide aspect the mirror spans the whole
// visible width, not 320.
s32 port_fbMirrorS(s32 screenX) {
    s32 visLeft = OTRGetRectDimensionFromLeftEdge(0);
    s32 visWidth = OTRGetRectDimensionFromRightEdge(0) - visLeft;

    if (visWidth < 1) {
        visWidth = SCREEN_WIDTH;
    }
    return (s32) (32.0f * SCREEN_WIDTH * (screenX - visLeft) / visWidth);
}

// Prev-frame mirror: captured at end of frame (gfx_frame.c), so consumers sample
// the frame before the one they are drawing into.

static u16 s_prevFrameSentinel[SCREEN_WIDTH * SCREEN_HEIGHT];

static s32 s_prevFrameFbId = -1;
static s32 s_prevFrameCaptureReq = 0;

static void ensurePrevFrameMirror(void) {
    ensureMirror(&s_prevFrameFbId, s_prevFrameSentinel);
}

u16* port_getPrevFrameSentinel(void) {
    ensurePrevFrameMirror();
    return s_prevFrameSentinel;
}

void port_requestPrevFrameCapture(void) {
    ensurePrevFrameMirror();
    // Two-frame window so capture persists for one frame after the last
    // request, smoothing the moment an overlay deactivates. Down from the
    // old CPU-readback path's 3 frames: GPU gDPCopyFB is same-frame reliable,
    // so one fewer frame of tolerance is needed.
    s_prevFrameCaptureReq = 2;
}

void port_emitCaptureCurrentFrameIfRequested(Gfx** gfxP) {
    if (s_prevFrameCaptureReq <= 0 || s_prevFrameFbId < 0) {
        return;
    }
    gDPCopyFB((*gfxP)++, s_prevFrameFbId, 0, false, NULL);
    s_prevFrameCaptureReq--;
}

// Scene mirror: captured inline mid-display-list, replacing the hardware trick of
// blitting the CFB through the z-buffer (which the port cannot honour --
// GfxDpSetColorImage only records the address, and nuGfxZBuffer is a zeroed dummy).
//
// Separate from the prev-frame mirror on purpose: its consumers redraw the region
// they sampled, so an end-of-frame capture would feed their own output back in and
// compound every frame.

static u16 s_sceneMirrorSentinel[SCREEN_WIDTH * SCREEN_HEIGHT];
static s32 s_sceneMirrorFbId = -1;

u16* port_getSceneMirrorSentinel(void) {
    ensureMirror(&s_sceneMirrorFbId, s_sceneMirrorSentinel);
    return s_sceneMirrorSentinel;
}

void port_emitSceneMirrorCapture(Gfx** gfxP) {
    ensureMirror(&s_sceneMirrorFbId, s_sceneMirrorSentinel);
    gDPCopyFB((*gfxP)++, s_sceneMirrorFbId, 0, false, NULL);
}

void port_appendGfx_draw_prev_frame_buffer(s32 x1, s32 y1, s32 x2, s32 y2, f32 alpha) {
    u16* prevGfxCfb = port_getPrevFrameSentinel();
    s32 visLeft = OTRGetRectDimensionFromLeftEdge(0);
    s32 visRight = OTRGetRectDimensionFromRightEdge(0);
    s32 visWidth = visRight - visLeft;
    s32 dstLeft;
    s32 dstRight;

    port_requestPrevFrameCapture();

    // round the x positions, as the original did
    x1 = x1 - (x1 % 4);
    x2 = x2 - (x2 % 4) + 4;

    if (visWidth < 1) {
        visWidth = SCREEN_WIDTH;
    }

    dstLeft = visLeft + x1;
    dstRight = visRight - (SCREEN_WIDTH - x2);

    gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
    gDPSetCombineMode(gMainGfxPos++, PM_CC_10, PM_CC_10);
    gDPSetRenderMode(gMainGfxPos++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
    gDPSetColorDither(gMainGfxPos++, G_CD_DISABLE);
    gDPSetAlphaDither(gMainGfxPos++, G_AD_NOISE);
    gDPSetTextureFilter(gMainGfxPos++, G_TF_POINT);
    gDPSetTexturePersp(gMainGfxPos++, G_TP_NONE);
    gSPTexture(gMainGfxPos++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
    gDPSetTextureDetail(gMainGfxPos++, G_TD_CLAMP);
    gDPSetTextureLOD(gMainGfxPos++, G_TL_TILE);
    gDPSetPrimColor(gMainGfxPos++, 0, 0, 255, 255, 255, alpha);

    // Tile dimensions are what the UV normalization divides by, so declare the full frame
    gDPLoadTextureTile(gMainGfxPos++, osVirtualToPhysical(prevGfxCfb), G_IM_FMT_RGBA, G_IM_SIZ_16b,
                       SCREEN_WIDTH, SCREEN_HEIGHT,
                       0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0,
                       G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    // dstLeft can be negative at wide aspect, hence the wide texrect
    gSPWideTextureRectangle(gMainGfxPos++, dstLeft * 4, y1 * 4, dstRight * 4, y2 * 4,
                        G_TX_RENDERTILE,
                        port_fbMirrorS(dstLeft), y1 * 32,
                        (s32) (1024.0f * SCREEN_WIDTH / visWidth), 1024);
}
