/**
 * gfx_frame.c - Starship Architecture Frame Orchestration
 *
 * Consolidates all display list building and submission into a single frame.
 * This eliminates flickering caused by multiple buffer swaps per frame.
 */

#include "common.h"
#include "gfx_pool.h"
#include "port/Engine.h"
#include "port/interpolation/FrameInterpolation.h"
#include "port/patches/Patches.h"
#include "port/os/OS.h"
#include "port/DevTools/ThreadWatchdog.h"
#include "port/audio/AudioVolume.h"

// Double-buffered graphics pools
GfxPool gGfxPools[2];
GfxPool* gGfxPool;
Gfx* gMasterDisp;
u32 gSysFrameCount = 0;

// External references to existing game functions/data
extern DisplayContext DisplayContexts[2];
extern s32 gCurrentDisplayContextIndex;
extern void step_game_loop(void);
extern void gfx_task_background(void);
extern void gfx_draw_frame(void);

// C++ bridge function - defined in Game.cpp
extern void Graphics_PushFrame(Gfx* displayList);

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

    ThreadWatchdog_Beat(WATCHDOG_MAIN_LOOP);
    AudioVolume_Update();

    // Run game logic
    FrameInterpolation_RecordOpenChild("game_logic", 0);
    step_game_loop();
    FrameInterpolation_RecordCloseChild();

    // Build background display list (no submission)
    gfx_task_background();

    // Build main frame display list (no submission)
    gfx_draw_frame();

    // Now create master display list that links both
    DisplayContext* ctx = &DisplayContexts[gCurrentDisplayContextIndex];

    // Link background display list
    gSPDisplayList(gMasterDisp++, ctx->backgroundGfx);

    // Link main display list
    gSPDisplayList(gMasterDisp++, ctx->mainGfx);

    // GPU-side prev-frame mirror: gDPCopyFB(main -> prevFb) every frame
    port_emitPrevFrameCapture(&gMasterDisp);

    // Finalize master display list
    gDPFullSync(gMasterDisp++);
    gSPEndDisplayList(gMasterDisp++);

    // Toggle display context for next frame (moved from gfx_draw_frame)
    gCurrentDisplayContextIndex ^= 1;

    // Handle GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME, which means "hold the last image on screen"
    // while the game tears down and rebuilds state (state transitions, demo
    // scene changes, map loads).
    if (gOverrideFlags & GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME) {
        GameEngine_HoldFrame();
        return;
    }

    // Submit ONCE to libultraship
    Graphics_PushFrame(gGfxPool->masterDL);
}
