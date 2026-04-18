#ifndef PORT_PATCHES_H
#define PORT_PATCHES_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

void port_appendGfx_shading_palette(
    Matrix4f mtx, s32 uls, s32 ult, s32 lrs, s32 lrt, s32 alpha,
    f32 shadowX, f32 shadowY, f32 shadowZ,
    s32 shadowR, s32 shadowG, s32 shadowB,
    s32 highlightR, s32 highlightG, s32 highlightB,
    s32 ambientPower, s32 renderMode);

// Framebuffer (FramebufferPatches.c)
u16* port_getPrevFrameSentinel(void);
void port_requestPrevFrameCapture(void);
void port_emitCaptureCurrentFrameIfRequested(Gfx** gfxP);

// Static Gfx[] with VTXs
void port_patch_dl(Gfx* dl);

#ifdef __cplusplus
}
#endif

#endif  // PORT_PATCHES_H
