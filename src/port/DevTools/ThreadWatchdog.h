#ifndef PORT_THREAD_WATCHDOG_H
#define PORT_THREAD_WATCHDOG_H

#include <stdint.h>

// Heartbeat watchdog over the revived decomp threads.
//
// Every serviced loop beats once per iteration and a watcher thread samples the
// counters. When a thread that has already proven alive stops beating while the
// wall clock keeps moving, the watcher logs the pipeline state: nusys's task
// spool and queue depths, who is parked on which queue, and the stalled
// thread's stack.

#ifdef __cplusplus
extern "C" {
#endif

typedef enum WatchdogThread {
    WATCHDOG_MAIN_LOOP = 0, // window thread: event pump + RCP service (Game.cpp)
    WATCHDOG_AUDIO_MANAGER, // decomp audio thread (audio/core/system.c)
    WATCHDOG_VI_TICKER,     // 60Hz VI retrace source (os/VI.cpp); paces the scheduler and the game loop
    WATCHDOG_GAME_TICK,     // nusys graphics thread: gfxRetrace_Callback (main.c) via gfx_frame.c
    WATCHDOG_SI_MANAGER,    // nusys SI manager (nusimgr.c): the rumble manager's callbacks
    WATCHDOG_NUM_THREADS
} WatchdogThread;

// Called once per loop iteration; one relaxed atomic increment.
void ThreadWatchdog_Beat(WatchdogThread id);

// Started once the decomp threads exist, stopped before shutdown teardown.
void ThreadWatchdog_Start(void);
void ThreadWatchdog_Stop(void);

// Log the pipeline state immediately, stalled or not.
void ThreadWatchdog_DumpNow(void);

// Bracket a section that blocks a serviced thread on purpose.
void ThreadWatchdog_BeginExpectedStall(const char* reason);
void ThreadWatchdog_EndExpectedStall(void);

// Whether the watcher currently considers this thread stalled. The gui only
// draws inside serviced frames, so the main loop uses this to keep drawing
// while the tick is down instead of freezing ImGui along with it.
int ThreadWatchdog_IsStalled(WatchdogThread id);

typedef struct NusysWatchdogState {
    int32_t taskSpool;   // nuGfxTaskSpool: tasks handed over and not yet retired
    int32_t retraceQ;    // nusched.retraceMQ depth (VI events waiting for the scheduler)
    int32_t rspQ;        // nusched.rspMQ
    int32_t rdpQ;        // nusched.rdpMQ
    int32_t gfxRequestQ; // nusched.graphicsRequestMQ (tasks waiting for the RCP)
    int32_t waitQ;       // nusched.waitMQ
    int32_t gfxMesgQ;    // nuGfxMesgQ (retraces waiting for the game loop)
    int32_t taskMgrQ;    // task manager queue (finished tasks waiting to be retired)
    int32_t areaID;
    int32_t mapID;
} NusysWatchdogState;
void Graphics_GetWatchdogState(NusysWatchdogState* out);

const char* Graphics_QueueName(const void* mq);
const char* Graphics_QueueFedBy(const void* mq);

#ifdef __cplusplus
}

namespace Paperboat {
class ExpectedStall {
public:
    explicit ExpectedStall(const char* reason) {
        ThreadWatchdog_BeginExpectedStall(reason);
    }
    ~ExpectedStall() {
        ThreadWatchdog_EndExpectedStall();
    }
    ExpectedStall(const ExpectedStall&) = delete;
    ExpectedStall& operator=(const ExpectedStall&) = delete;
};
} // namespace Paperboat
#endif

#endif // PORT_THREAD_WATCHDOG_H
