#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

#include "common.h"
#include "nu/nusys.h"
#include "port/patches/Patches.h"

extern "C" {

extern s32 gPauseBackgroundFade;

extern void gfx_register_fb_texture(const void* cpuAddr, int fbId);

// GPU framebuffer plus a registered CPU sentinel, so binding the sentinel as a
// texture binds the FB directly. Consumers must declare the full frame as the
// tile and use absolute screen-space UVs.
static void ensureMirror(s32* fbId, const u16* sentinel) {
    if (*fbId < 0) {
        *fbId = gfx_create_framebuffer(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 0);
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

static u16 s_prevFrameSentinel[SCREEN_WIDTH * SCREEN_HEIGHT];

static s32 s_prevFrameFbId = -1;

u16* port_getPrevFrameSentinel(void) {
    ensureMirror(&s_prevFrameFbId, s_prevFrameSentinel);
    return s_prevFrameSentinel;
}

void port_emitPrevFrameCapture(Gfx** gfxP) {
    ensureMirror(&s_prevFrameFbId, s_prevFrameSentinel);
    gDPCopyFB((*gfxP)++, s_prevFrameFbId, 0, false, NULL);
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
    gDPLoadTextureTile(
        gMainGfxPos++, osVirtualToPhysical(prevGfxCfb), G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0,
        SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
    );

    // dstLeft can be negative at wide aspect, hence the wide texrect
    gSPWideTextureRectangle(
        gMainGfxPos++, dstLeft * 4, y1 * 4, dstRight * 4, y2 * 4, G_TX_RENDERTILE, port_fbMirrorS(dstLeft), y1 * 32,
        (s32) (1024.0f * SCREEN_WIDTH / visWidth), 1024
    );
}

// Pause background fb
void port_appendGfx_pause_background(s32 bgRenderState) {
    u16* mirror;
    s32 visLeft;
    s32 visRight;
    s32 visWidth;

    switch (bgRenderState) {
        case BACKGROUND_RENDER_STATE_BEGIN_PAUSED:
            gGameStatusPtr->backgroundFlags &= ~BACKGROUND_RENDER_STATE_MASK;
            gGameStatusPtr->backgroundFlags |= BACKGROUND_RENDER_STATE_FILTER_PAUSED;
            gPauseBackgroundFade = 0;
            return;
        case BACKGROUND_RENDER_STATE_FILTER_PAUSED:
            gGameStatusPtr->backgroundFlags &= ~BACKGROUND_RENDER_STATE_MASK;
            gGameStatusPtr->backgroundFlags |= BACKGROUND_RENDER_STATE_SHOW_PAUSED;
            gPauseBackgroundFade = 0;
            break;
    }

    gPauseBackgroundFade += 16;
    if (gPauseBackgroundFade > 128) {
        gPauseBackgroundFade = 128;
    }

    mirror = port_getPrevFrameSentinel();
    visLeft = OTRGetRectDimensionFromLeftEdge(0);
    visRight = OTRGetRectDimensionFromRightEdge(0);
    visWidth = visRight - visLeft;
    if (visWidth < 1) {
        visWidth = SCREEN_WIDTH;
    }

    gDPPipeSync(gMainGfxPos++);
    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gDPSetCycleType(gMainGfxPos++, G_CYC_FILL);
    gDPSetRenderMode(gMainGfxPos++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(nuGfxCfb_ptr));
    gDPSetFillColor(gMainGfxPos++, PACK_FILL_COLOR(0, 0, 0, 1));
    gDPFillWideRectangle(gMainGfxPos++, visLeft, 0, visRight - 1, SCREEN_HEIGHT - 1);
    gDPPipeSync(gMainGfxPos++);

    gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
    // The ROM pairs PM_CC_43 with PM_CC_44 and compensates for the resulting
    // one-pixel texel offset with a -1 shift on S; neither is needed here.
    gDPSetCombineMode(gMainGfxPos++, PM_CC_43, PM_CC_43);
    gDPSetRenderMode(gMainGfxPos++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetColorDither(gMainGfxPos++, G_CD_DISABLE);
    gDPSetTextureFilter(gMainGfxPos++, G_TF_POINT);
    gDPSetTexturePersp(gMainGfxPos++, G_TP_NONE);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
    gDPSetTextureDetail(gMainGfxPos++, G_TD_CLAMP);
    gDPSetTextureLOD(gMainGfxPos++, G_TL_TILE);
    gSPTexture(gMainGfxPos++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetPrimColor(gMainGfxPos++, 0, 0, 40, 40, 40, gPauseBackgroundFade);

    gDPLoadTextureTile(
        gMainGfxPos++, osVirtualToPhysical(mirror), G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0,
        SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
    );

    gSPWideTextureRectangle(
        gMainGfxPos++, visLeft * 4, 0, visRight * 4, SCREEN_HEIGHT * 4, G_TX_RENDERTILE, port_fbMirrorS(visLeft), 0,
        (s32) (1024.0f * SCREEN_WIDTH / visWidth), 1024
    );
    gDPPipeSync(gMainGfxPos++);
}

b32 port_isPauseBackgroundActive(void) {
    return (gGameStatusPtr->backgroundFlags & BACKGROUND_RENDER_STATE_MASK) != 0;
}
}

static void RegisterFramebufferPatches_Init() {
    REGISTER_LISTENER(BackgroundPreDraw, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        auto* ev = (BackgroundPreDraw*) event;

        if (ev->bgRenderState == 0) {
            return;
        }

        port_appendGfx_pause_background(ev->bgRenderState);
        ev->Event.Cancelled = true;
    });
}

static RegisterShipInitFunc initFunc(RegisterFramebufferPatches_Init);
