/**
 * nusys_overrides.c
 *
 * Port-compatible replacements for N64 NuSystem functions.
 * These stubs allow the Paper Mario decomp to run with libultraship
 * instead of actual N64 hardware.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <execinfo.h>
#include "common.h"
#include "nu/nusys.h"
#include "Engine.h"

// Undefine macros so we can provide function implementations
#undef nuGfxInit
#undef nuGfxSetZBuffer

// ============================================================================
// Global Variables (needed by game code)
// ============================================================================

// Frame buffers (stubs - libultraship manages actual buffers)
static u16 gFrameBufDummy[320 * 240];
u16* FrameBuf[3] = { gFrameBufDummy, gFrameBufDummy, gFrameBufDummy };

// Graphics globals
// NOTE: nuGfxCfb_ptr and nuGfxCfb are defined in main_pre_bss.c
// They are initialized by nuGfxInit() called from Game.cpp
u32 nuGfxCfbNum = 3;
u32 nuGfxCfbCounter = 0;
u32 nuGfxDisplay = NU_GFX_DISPLAY_ON;
volatile u32 nuGfxTaskSpool = 0;
NUUcode* nuGfxUcode = NULL;
NUGfxSwapCfbFunc nuGfxSwapCfbFunc = NULL;
NUGfxTaskEndFunc nuGfxTaskEndFunc = NULL;
NUGfxFunc nuGfxFunc = NULL;
NUGfxPreNMIFunc nuGfxPreNMIFunc = NULL;

// Scheduler
NUSched nusched;

// Main stack
u64 nuMainStack[NU_SC_STACK_SIZE / sizeof(u64)];

// Idle function pointer
void (*nuIdleFunc)(void) = NULL;

// Task structures
NUScTask nuGfxTask[NU_GFX_TASK_NUM];

// Buffers
s32 D_800B91D0[NU_GFX_RDP_OUTPUTBUFF_SIZE / sizeof(u32)] ALIGNED(16);
u64 D_800DA040[0x400 / sizeof(u64)] ALIGNED(16);

// RSP boot ucode buffer
u8 rspbootUcodeBuffer[0x100] ALIGNED(16);

// Microcode reference
static u64 dummy_ucode[16];
static u64 dummy_ucode_data[16];
NUUcode nugfx_ucode = { dummy_ucode, dummy_ucode_data };

// RDP state init display list (minimal for port)
Gfx rdpstateinit_dl[] = {
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// ============================================================================
// Boot Functions
// ============================================================================

void nuBoot(void) {
    // No-op - libultraship handles initialization
}

void boot_idle(void* data) {
    // No-op - libultraship handles idle
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
// Scheduler Functions
// ============================================================================

void nuScCreateScheduler(u8 mode, u8 numFields) {
    nusched.retraceCount = 1;  // NTSC: audio runs every VI retrace (60 Hz)
}

// ============================================================================
// Graphics Functions
// ============================================================================

void nuGfxInit(void) {
    // Initialize framebuffer pointer so osVirtualToPhysical(nuGfxCfb_ptr) returns valid address
    // NOTE: Do NOT set nuGfxDisplay here - let game code control via nuGfxDisplayOn/Off
    // (N64 boot_main calls nuGfxDisplayOff before nuGfxInit, then nuGfxDisplayOn later)
    nuGfxCfb_ptr = gFrameBufDummy;
    nuGfxCfb = FrameBuf;
    GameEngine_LogInfo("nuGfxInit: nuGfxCfb_ptr=%p, gFrameBufDummy=%p", (void*)nuGfxCfb_ptr, (void*)gFrameBufDummy);
}

void nuGfxInitEX2(void) {
    // Initialize framebuffer pointer so osVirtualToPhysical(nuGfxCfb_ptr) returns valid address
    // NOTE: Do NOT set nuGfxDisplay here - let game code control via nuGfxDisplayOn/Off
    nuGfxCfb_ptr = gFrameBufDummy;
    nuGfxCfb = FrameBuf;
    GameEngine_LogInfo("nuGfxInitEX2: nuGfxCfb_ptr=%p, gFrameBufDummy=%p", (void*)nuGfxCfb_ptr, (void*)gFrameBufDummy);
}

void nuGfxThreadStart(void) {
    // No-op - no separate graphics thread in port
}

void nuGfxTaskMgrInit(void) {
    // No-op - task management handled by libultraship
}

void nuGfxTaskStart(Gfx* gfxList_ptr, u32 gfxListSize, u32 ucode, u32 flag) {
    // No-op: Display list submission now handled by Graphics_ThreadUpdate
    // Kept for compatibility with any remaining calls
    (void)gfxList_ptr;
    (void)gfxListSize;
    (void)ucode;
    (void)flag;
}

void nuGfxTaskAllEndWait(void) {
    // No-op - rendering is synchronous in port
}

void nuGfxDisplayOn(void) {
    nuGfxDisplay = NU_GFX_DISPLAY_ON;
}

void nuGfxDisplayOff(void) {
    nuGfxDisplay = NU_GFX_DISPLAY_OFF;
}

void nuGfxFuncSet(NUGfxFunc func) {
    nuGfxFunc = func;
    // Callback stored but not used - main loop calls directly
}

void nuGfxPreNMIFuncSet(NUGfxPreNMIFunc func) {
    nuGfxPreNMIFunc = func;
}

void nuGfxSwapCfbFuncSet(NUGfxSwapCfbFunc func) {
    nuGfxSwapCfbFunc = func;
}

void nuGfxTaskEndFuncSet(NUGfxTaskEndFunc func) {
    nuGfxTaskEndFunc = func;
}

void nuGfxSetCfb(u16** framebuf, u32 framebufnum) {
    nuGfxCfb = framebuf;
    nuGfxCfbNum = framebufnum;
    if (framebuf != NULL) {
        nuGfxCfb_ptr = framebuf[0];
    }
}

void nuGfxSetZBuffer(u16* zbuffer) {
    // No-op - Z buffer managed by libultraship
}

void nuGfxSwapCfb(void* framebuffer) {
    // No-op - buffer swapping handled by libultraship
}

void nuGfxRetraceWait(u32 count) {
    // No-op - timing handled by libultraship
}

void nuGfxSetUcodeFifo(void* fifoBufPtr, s32 size) {
    // No-op - FIFO managed by libultraship
}

// ============================================================================
// Controller Functions
// ============================================================================

u8 nuContInit(void) {
    // Return 1 controller connected
    // libultraship ControlDeck handles actual input
    return 1;
}

u8 nuSiMgrInit(void) {
    // Return 1 controller detected
    return 1;
}

u8 nuContMgrInit(void) {
    // No-op - controller management via libultraship
    return 1;
}

void nuContPakMgrInit(void) {
    // No-op - no controller pak support yet
}

void nuContRmbMgrInit(void) {
    // No-op - rumble via libultraship
}

void nuContRmbForceStop(void) {
    // TODO: Call libultraship rumble stop
}

void nuContRmbForceStopEnd(void) {
    // No-op
}

s32 nuContRmbCheck(u32 port) {
    // No-op
    return 0;
}

void nuContRmbModeSet(u32 port, u8 mode) {
    // No-op
}

void nuContRmbStart(u32 port, u16 freq, u16 frame) {
    // TODO: Call libultraship rumble start
}

void nuContDataGet(OSContPad* contdata, u32 padno) {
    // TODO: Read from libultraship ControlDeck
    contdata->button = 0;
    contdata->stick_x = 0;
    contdata->stick_y = 0;
    contdata->err_no = 0;
}

void nuContDataGetAll(OSContPad* contdata) {
    for (int i = 0; i < 4; i++) {
        nuContDataGet(&contdata[i], i);
    }
}

void nuContDataGetEx(NUContData* contdata, u32 padno) {
    // TODO: Read from libultraship ControlDeck
    contdata->button = 0;
    contdata->stick_x = 0;
    contdata->stick_y = 0;
    contdata->trigger = 0;
    contdata->errno = 0;
}

void nuContDataGetExAll(NUContData* contdata) {
    for (int i = 0; i < 4; i++) {
        nuContDataGetEx(&contdata[i], i);
    }
}

void nuContDataLock(void) {
    return;
}

void nuContDataUnlock(void) {
    // No-op
}

void nuContQueryRead(void) {
    // No-op
}

// ============================================================================
// SI (Serial Interface) Manager
// ============================================================================

void nuSiCallBackAdd(NUCallBackList* mesg) {
    // No-op
}

void nuSiCallBackRemove(NUCallBackList* mesg) {
    // No-op
}

void nuScAddClient(NUScClient* c, OSMesgQueue* mq, NUScMsg msgType) {
    // No-op - scheduler handled by libultraship
}

void nuPiReadRomOverlay(NUPiOverlaySegment* seg) {
    // No-op - overlays loaded via OTR
}

// ============================================================================
// Audio Interface Functions
// ============================================================================

u32 osAiGetStatus(void) {
    return 0;
}

s32 osAiSetFrequency(u32 frequency) {
    return (s32)frequency;
}

// ASP microcode data (stubs)
u8 n_aspMainTextStart[1];
u8 n_aspMainDataStart[1];

// ============================================================================
// ImgFX Animation Headers (stubs - data loaded from assets)
// ============================================================================

u8 shock_header[1];
u8 shiver_header[1];
u8 vertical_pipe_curl_header[1];
u8 horizontal_pipe_curl_header[1];
u8 startle_header[1];
u8 flutter_down_header[1];
u8 unfurl_header[1];
u8 get_in_bed_header[1];
u8 spirit_capture_header[1];
u8 unused_1_header[1];
u8 unused_2_header[1];
u8 unused_3_header[1];
u8 tutankoopa_gather_header[1];
u8 tutankoopa_swirl_2_header[1];
u8 tutankoopa_swirl_1_header[1];
u8 shuffle_cards_header[1];
u8 flip_card_1_header[1];
u8 flip_card_2_header[1];
u8 flip_card_3_header[1];
u8 cymbal_crush_header[1];

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
u32 osMemSize = 0;

void osViRepeatLine(u8 repeat) {
    (void)repeat;
}

OSThread* __osGetActiveQueue(void) {
    return NULL;
}

void osUnmapTLBAll(void) {
}

s32 osFlashSectorErase(u32 page) {
    (void)page;
    return 0;
}

void osCreateViManager(OSPri pri) {
    (void)pri;
}

void osViSetMode(OSViMode* mode) {
    (void)mode;
}

void osViSetSpecialFeatures(u32 features) {
    (void)features;
}

void osViBlack(u8 black) {
    (void)black;
}

void osViSetEvent(OSMesgQueue* mq, OSMesg msg, u32 retraceCount) {
    (void)mq;
    (void)msg;
    (void)retraceCount;
}

void osCreateThread(OSThread* thread, OSId id, void (*entry)(void*),
                    void* arg, void* sp, OSPri pri) {
    (void)thread;
    (void)id;
    (void)entry;
    (void)arg;
    (void)sp;
    (void)pri;
}

void osStartThread(OSThread* thread) {
    (void)thread;
}

void osStopThread(OSThread* thread) {
    (void)thread;
}

void osSetThreadPri(OSThread* thread, OSPri pri) {
    (void)thread;
    (void)pri;
}

void osWritebackDCacheAll(void) {
}

void osSpTaskYield(void) {
}

OSYieldResult osSpTaskYielded(OSTask* tp) {
    (void)tp;
    return 0;
}

void osSpTaskLoad(OSTask* tp) {
    (void)tp;
}

void osSpTaskStartGo(OSTask* tp) {
    (void)tp;
}

s32 osAfterPreNMI(void) {
    return 0;
}

void osViSetYScale(f32 scale) {
    (void)scale;
}

u32 osSetIntMask(u32 mask) {
    (void)mask;
    return 0;
}

void osInvalICache(void* vaddr, s32 size) {
    (void)vaddr;
    (void)size;
}

void osInvalDCache(void* vaddr, s32 size) {
    (void)vaddr;
    (void)size;
}

void osWritebackDCache(void* vaddr, s32 size) {
    (void)vaddr;
    (void)size;
}

s32 osEPiReadIo(OSPiHandle* handle, u32 devAddr, u32* data) {
    (void)handle;
    (void)devAddr;
    if (data != NULL) {
        *data = 0;
    }
    return 0;
}

s32 osEPiWriteIo(OSPiHandle* handle, u32 devAddr, u32 data) {
    (void)handle;
    (void)devAddr;
    (void)data;
    return 0;
}

void* osViGetCurrentFramebuffer(void) {
    return NULL;
}

void* osViGetNextFramebuffer(void) {
    return NULL;
}

void osViSwapBuffer(void* frameBufPtr) {
    (void)frameBufPtr;
}

void osCreatePiManager(OSPri pri, OSMesgQueue* cmdQ, OSMesg* cmdBuf, s32 cmdMsgCnt) {
    (void)pri;
    (void)cmdQ;
    (void)cmdBuf;
    (void)cmdMsgCnt;
}

s32 osPfsInitPak(OSMesgQueue* mq, OSPfs* pfs, int channel) {
    (void)mq;
    (void)pfs;
    (void)channel;
    return 0;
}

void __osInitialize_common(void) {
}

void __osInitialize_autodetect(void) {
}

s32 osContStartQuery(OSMesgQueue* mq) {
    (void)mq;
    return 0;
}

void osContGetQuery(OSContStatus* data) {
    (void)data;
}

uintptr_t osVirtualToPhysical(void* addr) {
    // libultraship interprets address 1 as "main framebuffer"
    // (see background_gfx.c:50 for existing usage of this pattern)
    if (addr == gFrameBufDummy) {
        return 1;
    }
    // PORT: Return 1 for NULL to prevent rendering to address 0 (which breaks display)
    if (addr == NULL) {
        return 1;
    }
    return (uintptr_t)addr;
}

void osMapTLB(s32 index, OSPageMask pm, void* vaddr, u32 paddr, u32 paddr_end, s32 asid) {
    (void)index;
    (void)pm;
    (void)vaddr;
    (void)paddr;
    (void)paddr_end;
    (void)asid;
}

void osUnmapTLB(s32 index) {
    (void)index;
}

OSPiHandle* osFlashInit(void) {
    return NULL;
}

s32 osFlashReadArray(OSIoMesg* mb, s32 priority, u32 page_num, void* dramAddr, u32 size) {
    (void)mb;
    (void)priority;
    (void)page_num;
    (void)dramAddr;
    (void)size;
    return 0;
}

s32 osFlashWriteBuffer(OSIoMesg* mb, s32 priority, void* dramAddr, u32 size, u32 offset) {
    (void)mb;
    (void)priority;
    (void)dramAddr;
    (void)size;
    (void)offset;
    return 0;
}

s32 osFlashWriteArray(u32 page_num) {
    (void)page_num;
    return 0;
}

s32 osPfsRepairId(OSPfs* pfs) {
    (void)pfs;
    return 0;
}

s32 osPfsAllocateFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName, int size, s32* fileNo) {
    (void)pfs;
    (void)companyCode;
    (void)gameCode;
    (void)gameName;
    (void)extName;
    (void)size;
    if (fileNo != NULL) {
        *fileNo = 0;
    }
    return 0;
}

s32 osPfsFindFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName, s32* fileNo) {
    (void)pfs;
    (void)companyCode;
    (void)gameCode;
    (void)gameName;
    (void)extName;
    if (fileNo != NULL) {
        *fileNo = 0;
    }
    return 0;
}

s32 osPfsDeleteFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName) {
    (void)pfs;
    (void)companyCode;
    (void)gameCode;
    (void)gameName;
    (void)extName;
    return 0;
}

s32 osPfsReadWriteFile(OSPfs* pfs, s32 fileNo, u8 flag, int offset, int size, u8* data) {
    (void)pfs;
    (void)fileNo;
    (void)flag;
    (void)offset;
    (void)size;
    (void)data;
    return 0;
}

s32 osPfsFileState(OSPfs* pfs, s32 fileNo, OSPfsState* state) {
    (void)pfs;
    (void)fileNo;
    (void)state;
    return 0;
}

s32 osPfsFreeBlocks(OSPfs* pfs, s32* bytes) {
    (void)pfs;
    if (bytes != NULL) {
        *bytes = 0;
    }
    return 0;
}

s32 osPfsNumFiles(OSPfs* pfs, s32* maxFiles, s32* filesUsed) {
    (void)pfs;
    if (maxFiles != NULL) {
        *maxFiles = 0;
    }
    if (filesUsed != NULL) {
        *filesUsed = 0;
    }
    return 0;
}
