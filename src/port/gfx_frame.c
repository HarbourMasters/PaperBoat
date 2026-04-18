/**
 * gfx_frame.c - Starship Architecture Frame Orchestration
 *
 * Consolidates all display list building and submission into a single frame.
 * This eliminates flickering caused by multiple buffer swaps per frame.
 */

#include "common.h"
#include "gfx_pool.h"
#include "port/patches/Patches.h"

// Double-buffered graphics pools
GfxPool gGfxPools[2];
GfxPool *gGfxPool;
Gfx *gMasterDisp;
u32 gSysFrameCount = 0;

// External references to existing game functions/data
extern DisplayContext DisplayContexts[2];
extern s32 gCurrentDisplayContextIndex;
extern void step_game_loop(void);
extern void gfx_task_background(void);
extern void gfx_draw_frame(void);

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
  gfx_task_background();

  // Build main frame display list (no submission)
  gfx_draw_frame();

  // Now create master display list that links both
  DisplayContext *ctx = &DisplayContexts[gCurrentDisplayContextIndex];

  // Link background display list
  gSPDisplayList(gMasterDisp++, ctx->backgroundGfx);

  // Link main display list
  gSPDisplayList(gMasterDisp++, ctx->mainGfx);

  // GPU-side prev-frame mirror: emit gDPCopyFB(main -> prevFb) when an
  // overlay/effect has requested capture. Implementation in
  // src/port/patches/FramebufferPatches.c.
  port_emitCaptureCurrentFrameIfRequested(&gMasterDisp);

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
