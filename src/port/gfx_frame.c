#include "common.h"
#include "nu/nusys.h"
#include "port/Engine.h"
#include "port/audio/AudioVolume.h"
#include "port/DevTools/ThreadWatchdog.h"
#include "port/interpolation/FrameInterpolation.h"
#include "port/os/OS.h"
#include "port/patches/Patches.h"

extern void gfxRetrace_Callback(s32 gfxTaskNum);
extern void gfxPreNMI_Callback(void);
extern void gfx_task_end_callback(void* unk);

extern OSMesgQueue nuGfxMesgQ;       // nugfxthread.c
extern OSMesgQueue D_800DAC90;       // nugfxtaskmgr.c: the task manager's queue
extern OSMesgQueue nuSiMgrMesgQ;     // nusimgr.c
extern OSMesgQueue nuContDataMutexQ; // nucontmgr.c

extern void nuScEventHandler(void);
extern void nuScExecuteGraphics(void);
extern void gfxThread(void* data);
extern void nuGfxTaskMgr(void* data);

static Gfx sMasterList[8];

// audioRequestMQ stays non-blocking: nothing drains it.
void Graphics_EnableNusysThreads(void) {
    OS_SetQueueBlocking(&nusched.retraceMQ, 1);
    OS_SetQueueBlocking(&nusched.rspMQ, 1);
    OS_SetQueueBlocking(&nusched.rdpMQ, 1);
    OS_SetQueueBlocking(&nusched.graphicsRequestMQ, 1);
    OS_SetQueueBlocking(&nusched.waitMQ, 1);
    OS_SetQueueBlocking(&nuGfxMesgQ, 1);
    OS_SetQueueBlocking(&D_800DAC90, 1);

    OS_EnableThreadEntry((void*) nuScEventHandler);
    OS_EnableThreadEntry((void*) nuScExecuteGraphics);
    OS_EnableThreadEntry((void*) gfxThread);
    OS_EnableThreadEntry((void*) nuGfxTaskMgr);
}

static void Graphics_Retrace(u32 gfxTaskNum) {
    ThreadWatchdog_Beat(WATCHDOG_GAME_TICK);
    AudioVolume_Update();
    FrameInterpolation_StartRecord();
    FrameInterpolation_RecordOpenChild("game_logic", 0);
    gfxRetrace_Callback((s32) gfxTaskNum);
    FrameInterpolation_RecordCloseChild();
}

// The tail of boot_main.
void Graphics_Start(void) {
    nuGfxFuncSet(Graphics_Retrace);
    nuGfxPreNMIFuncSet(gfxPreNMI_Callback);
    nuGfxTaskEndFunc = gfx_task_end_callback;
    nuGfxDisplayOn();
}

void* Graphics_TaskFromList(const void* osTask) {
    return (void*) ((const char*) osTask - offsetof(NUScTask, list));
}

u32 Graphics_TaskFlags(const void* nuTask) {
    return ((const NUScTask*) nuTask)->flags;
}

// The pause background draws from the mirror, so the capture freezes while it is up.
s32 Graphics_ShouldCapturePrevFrame(void) {
    return !port_isPauseBackgroundActive();
}

void Graphics_DrawFrame(Gfx* backgroundList, Gfx* mainList, s32 capturePrevFrame) {
    Gfx* g = sMasterList;

    if (backgroundList != NULL) {
        gSPDisplayList(g++, backgroundList);
    }
    gSPDisplayList(g++, mainList);

    if (capturePrevFrame) {
        port_emitPrevFrameCapture(&g);
    }

    gDPFullSync(g++);
    gSPEndDisplayList(g++);

    GameEngine_ProcessGfxCommands(sMasterList);
}

void Graphics_GetWatchdogState(NusysWatchdogState* out) {
    out->taskSpool = (s32) nuGfxTaskSpool;
    out->retraceQ = nusched.retraceMQ.validCount;
    out->rspQ = nusched.rspMQ.validCount;
    out->rdpQ = nusched.rdpMQ.validCount;
    out->gfxRequestQ = nusched.graphicsRequestMQ.validCount;
    out->waitQ = nusched.waitMQ.validCount;
    out->gfxMesgQ = nuGfxMesgQ.validCount;
    out->taskMgrQ = D_800DAC90.validCount;
    out->areaID = gGameStatusPtr != NULL ? gGameStatusPtr->areaID : -1;
    out->mapID = gGameStatusPtr != NULL ? gGameStatusPtr->mapID : -1;
}

static const struct {
    const OSMesgQueue* mq;
    const char* name;
    const char* fedBy;
} sQueueInfo[] = {
    { &nusched.retraceMQ, "nusched.retraceMQ (nusched.c)", "VI ticker via OS_EVENT_VI (os/VI.cpp)" },
    { &nusched.rspMQ, "nusched.rspMQ (nusched.c)", "OS_EVENT_SP from ServiceRcp (Game.cpp) after the task is drawn" },
    { &nusched.rdpMQ, "nusched.rdpMQ (nusched.c)", "OS_EVENT_DP from ServiceRcp (Game.cpp) after the task is drawn" },
    { &nusched.graphicsRequestMQ, "nusched.graphicsRequestMQ (nusched.c)",
      "nuGfxTaskStart from gfx_task_background / gfx_draw_frame (main_loop.c)" },
    { &nusched.audioRequestMQ, "nusched.audioRequestMQ (nusched.c)", "nuAuMgr (audio/core/system.c)" },
    { &nusched.waitMQ, "nusched.waitMQ (nusched.c)", "nuScExecuteAudio (not revived: never)" },
    { &nuGfxMesgQ, "nuGfxMesgQ (nugfxthread.c)", "nuScEventBroadcast retrace (nusched.c) from nuScEventHandler" },
    { &D_800DAC90, "D_800DAC90 task manager queue (nugfxtaskmgr.c)",
      "nuScExecuteGraphics (nusched.c) once SP and DP have been raised" },
    { &nuSiMgrMesgQ, "nuSiMgrMesgQ (nusimgr.c)", "nuScEventBroadcast retrace; nuSiSendMesg from the game" },
    { &nuContDataMutexQ, "nuContDataMutexQ (nucontmgr.c)", "nuContDataClose/Open on the SI thread and the game" },
};

const char* Graphics_QueueName(const void* mq) {
    for (u32 i = 0; i < ARRAY_COUNT(sQueueInfo); i++) {
        if (sQueueInfo[i].mq == mq) {
            return sQueueInfo[i].name;
        }
    }
    return NULL;
}

const char* Graphics_QueueFedBy(const void* mq) {
    for (u32 i = 0; i < ARRAY_COUNT(sQueueInfo); i++) {
        if (sQueueInfo[i].mq == mq) {
            return sQueueInfo[i].fedBy;
        }
    }
    return NULL;
}
