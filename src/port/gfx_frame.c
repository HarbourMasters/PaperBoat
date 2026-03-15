/**
 * gfx_frame.c - Starship Architecture Frame Orchestration
 *
 * Consolidates all display list building and submission into a single frame.
 * This eliminates flickering caused by multiple buffer swaps per frame.
 */

#include "common.h"
#include "gfx_pool.h"

// Double-buffered graphics pools
GfxPool gGfxPools[2];
GfxPool *gGfxPool;
Gfx *gMasterDisp;
u32 gSysFrameCount = 0;

// Framebuffer capture buffer for appendGfx_draw_prev_frame_buffer.
// Only captured when requested — per-frame GPU readback causes Metal
// "kIOGPUCommandBufferCallbackErrorSubmissionsIgnored" errors.
static u16 gPrevFramePixels[SCREEN_WIDTH * SCREEN_HEIGHT]; // RGBA16, ~153KB
static s32 gPrevFrameCaptureRequest = 0; // >0 = capture this frame

u16 *GetPrevFramePixels(void) { return gPrevFramePixels; }

// Call from game code to request framebuffer capture.
// The capture persists for 2 extra frames after the last request to handle
// effects that read the buffer on the same frame they start.
void RequestPrevFrameCapture(void) { gPrevFrameCaptureRequest = 3; }

// External references to existing game functions/data
extern DisplayContext D_80164000[2];
extern s32 gCurrentDisplayContextIndex;
extern void step_game_loop(void);
extern void gfx_task_background_build(void);
extern void gfx_draw_frame_build(void);

// Audio frame hooks from Engine.cpp
extern void GameEngine_StartAudioFrame(void);
extern void GameEngine_EndAudioFrame(void);

// C++ bridge function - defined in Game.cpp
extern void Graphics_PushFrame(Gfx *displayList);

void Graphics_InitializeTask(void) {
  // Select pool based on frame parity (double-buffering)
  gGfxPool = &gGfxPools[gSysFrameCount % 2];

  // Initialize master display list write pointer
  gMasterDisp = gGfxPool->masterDL;
}

void Graphics_ThreadUpdate(void) {
  gSysFrameCount++;

  // Initialize frame pointers
  Graphics_InitializeTask();

  // Start audio generation in parallel
  GameEngine_StartAudioFrame();

  // Run game logic
  step_game_loop();

  // Build background display list (no submission)
  gfx_task_background_build();

  // Build main frame display list (no submission)
  gfx_draw_frame_build();

  // Now create master display list that links both
  DisplayContext *ctx = &D_80164000[gCurrentDisplayContextIndex];

  // Link background display list
  gSPDisplayList(gMasterDisp++, ctx->backgroundGfx);

  // Link main display list
  gSPDisplayList(gMasterDisp++, ctx->mainGfx);

  // Capture framebuffer only when requested by prev-frame effects.
  // Unconditional capture causes Metal GPU errors
  // (kIOGPUCommandBufferCallbackErrorSubmissionsIgnored).
  if (gPrevFrameCaptureRequest > 0) {
    gDPReadFB(gMasterDisp++, 0, gPrevFramePixels, 0, 0, SCREEN_WIDTH,
              SCREEN_HEIGHT, 1);
    gPrevFrameCaptureRequest--;
  }

  // Finalize master display list
  gDPFullSync(gMasterDisp++);
  gSPEndDisplayList(gMasterDisp++);

  // Toggle display context for next frame (moved from gfx_draw_frame)
  gCurrentDisplayContextIndex ^= 1;

  // Wait for audio frame to complete
  GameEngine_EndAudioFrame();

  // Submit ONCE to libultraship
  Graphics_PushFrame(gGfxPool->masterDL);
}
