#include "common.h"
#include "port/patches/Patches.h"

extern int gfx_create_framebuffer(unsigned int width, unsigned int height,
                                  unsigned int native_width, unsigned int native_height,
                                  unsigned char resize);
extern void gfx_register_fb_texture(const void* cpuAddr, int fbId);

static u16 s_prevFrameSentinel[SCREEN_WIDTH * SCREEN_HEIGHT];

static s32 s_prevFrameFbId = -1;
static s32 s_prevFrameCaptureReq = 0;

static void ensurePrevFrameMirror(void) {
    if (s_prevFrameFbId < 0) {
        s_prevFrameFbId = gfx_create_framebuffer(SCREEN_WIDTH, SCREEN_HEIGHT,
                                                 SCREEN_WIDTH, SCREEN_HEIGHT, 1);
        gfx_register_fb_texture(s_prevFrameSentinel, s_prevFrameFbId);
    }
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
