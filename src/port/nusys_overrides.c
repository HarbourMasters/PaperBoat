/**
 * nusys_overrides.c
 *
 * Port-compatible replacements for N64 NuSystem functions.
 * These stubs allow the Paper Mario decomp to run with libultraship
 * instead of actual N64 hardware.
 */

#include "Engine.h"
#include "common.h"
#include "nu/nusys.h"
#include "port/os/OS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Undefine macros so we can provide function implementations
#undef nuGfxInit

// ============================================================================
// Global Variables (needed by game code)
// ============================================================================

// Frame buffers (stubs - libultraship manages actual buffers)
static u16 gFrameBufDummy[320 * 240];
static u16 gZBufferDummy[320 * 240];
u16* FrameBuf[3] = { gFrameBufDummy, gFrameBufDummy, gFrameBufDummy };

static u64 dummy_ucode[16];
static u64 dummy_ucode_data[16];
NUUcode nugfx_ucode = { dummy_ucode, dummy_ucode_data };

// RDP state init display list (minimal for port)
Gfx rdpstateinit_dl[] = {
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

void osInitialize(void) {
}

// ============================================================================
// PI (Parallel Interface) Functions
// ============================================================================

void nuPiInit(void) {
    // No-op - no N64 PI hardware
}

void nuPiReadRom(u32 romAddr, void* ramAddr, u32 len) {
    return;
}

// ============================================================================
// Graphics Functions
// ============================================================================

void nuGfxInit(void) {
    nuGfxThreadStart();
    nuGfxSetCfb(FrameBuf, NU_GFX_FRAMEBUFFER_NUM);
    //  nuGfxSetZBuffer((u16*) NU_GFX_ZBUFFER_ADDR);
    nuGfxSetZBuffer(gZBufferDummy);
    nuGfxSwapCfbFuncSet(nuGfxSwapCfb);
    nuGfxUcode = &nugfx_ucode;
    nuGfxTaskMgrInit();
}

void nuGfxInitEX2(void) {
    nuGfxInit();
}

void nuGfxSetUcodeFifo(void* fifoBufPtr, s32 size) {
    // No-op - FIFO managed by libultraship
}

// ============================================================================
// Controller Functions
// ============================================================================

OSPfs nuContPfs[NU_CONT_MAXCONTROLLERS];
u8 nuContInit(void) {
    nuSiMgrInit();
    nuContMgrInit();
    nuContPakMgrInit();
    nuContRmbMgrInit();
    return 1;
}

void nuContPakMgrInit(void) {
    // No-op - no controller pak support yet
}

// The snapshot the window thread took; SDL input and the touch overlay live there.
void nuPiReadRomOverlay(NUPiOverlaySegment* seg) {
    // No-op - overlays loaded via OTR
}

// ============================================================================
// Audio Interface Functions
// ============================================================================

s32 osAiSetFrequency(u32 frequency) {
    return (s32) frequency;
}

// ASP microcode data (stubs)
u8 n_aspMainTextStart[1];
u8 n_aspMainDataStart[1];
u64 n_aspMain_text_bin[1];
u64 n_aspMain_data_bin[1];

// N64 OS stubs (used by dx/profiling.c)
u32 __osDisableInt(void) {
    return 0;
}
void __osRestoreInt(u32 saved) {
    (void) saved;
}

// N64 trig tables
#include "../os/sintable.inc.c"

s16 sins(u16 x) {
    /* 0 <= x < 0x10000  ==>  0 <= x < 2PI */
    s16 val;

    x >>= 4; /* Now range 0 <= x < 0x1000 */

    if (x & 0x400) {
        val = sintable[0x3ff - (x & 0x3ff)];
    } else {
        val = sintable[x & 0x3ff];
    }

    if (x & 0x800) {
        return -val;
    } else {
        return val;
    }
}

s16 coss(u16 angle) {
    return sins(angle + 0x4000);
}

// N64 PI cart handle — stub for port (DMA functions are no-ops)
OSPiHandle* nuPiCartHandle = NULL;

// ============================================================================
// Effect Function Stubs
// ============================================================================

void* fx_small_gold_sparkle(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    return NULL;
}

void* fx_sun_undeclared(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    return NULL;
}

// ============================================================================
// OS Functions (stubs for N64 libultra functions not provided by libultraship)
// ============================================================================

s32 osTvType = 1;
OSViMode osViModeNtscLan1 = { 0 };
OSViMode osViModeMpalLan1 = { 0 };
OSViMode osViModeTable[40] = { 0 }; // nuScCreateScheduler indexes this; the modes are inert here
u32 osMemSize = 0;

OSThread* __osGetActiveQueue(void) {
    return NULL;
}

void osUnmapTLBAll(void) {
}

void osCreateThread(OSThread* thread, OSId id, void (*entry)(void*), void* arg, void* sp, OSPri pri) {
    OS_CreateThread(thread, id, entry, arg, sp, pri);
}

void osStartThread(OSThread* thread) {
    OS_StartThread(thread);
}

void osStopThread(OSThread* thread) {
    OS_StopThread(thread);
}

void osSetThreadPri(OSThread* thread, OSPri pri) {
    OS_SetThreadPri(thread, pri);
}

s32 osAfterPreNMI(void) {
    return 0;
}

s32 osEPiReadIo(OSPiHandle* handle, u32 devAddr, u32* data) {
    (void) handle;
    (void) devAddr;
    if (data != NULL) {
        *data = 0;
    }
    return 0;
}

s32 osEPiWriteIo(OSPiHandle* handle, u32 devAddr, u32 data) {
    (void) handle;
    (void) devAddr;
    (void) data;
    return 0;
}

s32 osPfsInitPak(OSMesgQueue* mq, OSPfs* pfs, int channel) {
    (void) mq;
    (void) pfs;
    (void) channel;
    return 0;
}

void __osInitialize_common(void) {
}

void __osInitialize_autodetect(void) {
}

s32 osContStartQuery(OSMesgQueue* mq) {
    (void) mq;
    return 0;
}

void osContGetQuery(OSContStatus* data) {
    (void) data;
}

uintptr_t osVirtualToPhysical(void* addr) {
    // libultraship interprets address 1 as "main framebuffer"
    // (see background_gfx.c:50 for existing usage of this pattern)
    if (addr == gFrameBufDummy) {
        return 1;
    }
    if (addr == gZBufferDummy) {
        return (uintptr_t) GFX_DEPTH_IMAGE_SENTINEL;
    }
    // PORT: Return 1 for NULL to prevent rendering to address 0 (which breaks
    // display)
    if (addr == NULL) {
        return 1;
    }
    return (uintptr_t) addr;
}

void osUnmapTLB(s32 index) {
    (void) index;
}

OSPiHandle* osCartRomInit(void) {
    return NULL;
}

s32 osEPiStartDma(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction) {
    return 0;
}

void osMapTLB(s32 index, OSPageMask pagemask, void* vaddr, u32 odd, u32 even, s32 asid) {
}

// ============================================================================
// Flash
// ============================================================================

OSPiHandle* osFlashInit(void) {
    return NULL;
}

s32 osFlashSectorErase(u32 page_num) {
    (void) page_num;
    return 0;
}

s32 osFlashReadArray(OSIoMesg* mb, s32 priority, u32 page_num, void* dramAddr, u32 n_pages, OSMesgQueue* mq) {
    (void) mb;
    (void) priority;
    (void) page_num;
    (void) mq;
    memset(dramAddr, 0, n_pages * 128);
    return 0;
}

s32 osFlashWriteBuffer(OSIoMesg* mb, s32 priority, void* dramAddr, OSMesgQueue* mq) {
    (void) mb;
    (void) priority;
    (void) dramAddr;
    (void) mq;
    return 0;
}

s32 osFlashWriteArray(u32 page_num) {
    (void) page_num;
    return 0;
}

s32 osPfsRepairId(OSPfs* pfs) {
    (void) pfs;
    return 0;
}

s32 osPfsAllocateFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName, int size, s32* fileNo) {
    (void) pfs;
    (void) companyCode;
    (void) gameCode;
    (void) gameName;
    (void) extName;
    (void) size;
    if (fileNo != NULL) {
        *fileNo = 0;
    }
    return 0;
}

s32 osPfsFindFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName, s32* fileNo) {
    (void) pfs;
    (void) companyCode;
    (void) gameCode;
    (void) gameName;
    (void) extName;
    if (fileNo != NULL) {
        *fileNo = 0;
    }
    return 0;
}

s32 osPfsDeleteFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName) {
    (void) pfs;
    (void) companyCode;
    (void) gameCode;
    (void) gameName;
    (void) extName;
    return 0;
}

s32 osPfsReadWriteFile(OSPfs* pfs, s32 fileNo, u8 flag, int offset, int size, u8* data) {
    (void) pfs;
    (void) fileNo;
    (void) flag;
    (void) offset;
    (void) size;
    (void) data;
    return 0;
}

s32 osPfsFileState(OSPfs* pfs, s32 fileNo, OSPfsState* state) {
    (void) pfs;
    (void) fileNo;
    (void) state;
    return 0;
}

s32 osPfsFreeBlocks(OSPfs* pfs, s32* bytes) {
    (void) pfs;
    if (bytes != NULL) {
        *bytes = 0;
    }
    return 0;
}

s32 osPfsNumFiles(OSPfs* pfs, s32* maxFiles, s32* filesUsed) {
    (void) pfs;
    if (maxFiles != NULL) {
        *maxFiles = 0;
    }
    if (filesUsed != NULL) {
        *filesUsed = 0;
    }
    return 0;
}
