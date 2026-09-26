#include "OS.h"

#include <atomic>

extern "C" {
#include "libultraship/libultra/types.h"
#include "libultraship/libultra/sptask.h"
}

namespace {
std::atomic<OSTask*> sPendingTask { nullptr };
std::atomic<bool> sYieldPending { false };  // yield requested, not yet observed
std::atomic<bool> sResumePending { false }; // next gfx StartGo is the resume
} // namespace

extern "C" void osSpTaskYield(void) {
    sYieldPending.store(true, std::memory_order_release);
    OS_JamEventMesg(OS_EVENT_SP);
}

extern "C" OSYieldResult osSpTaskYielded(OSTask* task) {
    (void) task;
    if (sYieldPending.exchange(false, std::memory_order_acq_rel)) {
        sResumePending.store(true, std::memory_order_release);
        return 1;
    }
    return 0;
}

extern "C" void osSpTaskLoad(OSTask* task) {
    (void) task; // no DMEM to load; StartGo carries the pointer
}

extern "C" void osSpTaskStartGo(OSTask* task) {
    if (task->t.type == M_AUDTASK) {
        OS_JamEventMesg(OS_EVENT_SP);
        return;
    }

    if (sResumePending.exchange(false, std::memory_order_acq_rel)) {
        return;
    }
    sPendingTask.store(task, std::memory_order_release);
}

extern "C" OSTask* OS_SpTakePendingTask(void) {
    return sPendingTask.exchange(nullptr, std::memory_order_acq_rel);
}

extern "C" OSTask* OS_SpPeekPendingTask(void) {
    return sPendingTask.load(std::memory_order_acquire);
}
