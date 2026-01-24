#ifndef GFX_POOL_H
#define GFX_POOL_H

#include "common.h"

// Master display list for linking sub-DLs
// Kept small - just links to the actual rendering DLs
#define MASTER_DL_SIZE 32

typedef struct {
    Gfx masterDL[MASTER_DL_SIZE];
} GfxPool;

// Double-buffered pools
extern GfxPool gGfxPools[2];
extern GfxPool* gGfxPool;
extern Gfx* gMasterDisp;  // Write pointer for master DL

// Frame counter for double-buffering
extern u32 gSysFrameCount;

// Frame orchestration functions
void Graphics_InitializeTask(void);
void Graphics_ThreadUpdate(void);

#endif
