#ifndef PORT_THREAD_WATCHDOG_H
#define PORT_THREAD_WATCHDOG_H

#include <stdint.h>

// Heartbeat watchdog over the revived decomp threads.
//
// Every serviced loop beats once per iteration and a watcher thread samples the
// counters. When a thread that has already proven alive stops beating while the
// wall clock keeps moving, the watcher logs the pipeline state: thread5's flag
// words and task rings, every queue depth, who is parked where, and the stalled
// thread's stack.

#ifdef __cplusplus
extern "C" {
#endif

typedef enum WatchdogThread {
    WATCHDOG_AUDIO_TICKER = 0, // 60Hz retrace source (os/Audio.cpp); paces the audio manager
    WATCHDOG_MAIN_LOOP,        // window thread: event pump, game logic, render (gfx_frame.c)
    WATCHDOG_AUDIO_MANAGER,    // decomp audio thread (audio/core/system.c)
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
