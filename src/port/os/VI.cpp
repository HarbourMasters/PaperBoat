#include "OS.h"

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "port/DevTools/ThreadWatchdog.h"

extern "C" {
#include "libultraship/libultra/types.h"
#include "libultraship/libultra/vi.h"
}

namespace {

using Clock = std::chrono::steady_clock;

constexpr std::chrono::nanoseconds kVi(16666667); // NTSC 60Hz
constexpr double kSlaveTolerance = 0.12;
constexpr double kPresentGrace = 0.4;

std::thread sTicker;
std::atomic<bool> sTickerRun { false };

std::mutex sPresentMutex;
std::condition_variable sPresentCv;
bool sPresented = false;
Clock::time_point sLastPresent {};
int sPresentsPerVi = 0;
double sPresentIntervalNs = 0.0;

std::atomic<void*> sNextFramebuffer { nullptr };
std::atomic<void*> sCurrentFramebuffer { nullptr };
std::atomic<bool> sBlack { false };

void Retrace() {
    sCurrentFramebuffer.store(sNextFramebuffer.load(std::memory_order_acquire), std::memory_order_release);
    ThreadWatchdog_Beat(WATCHDOG_VI_TICKER);
    OS_SendEventMesg(OS_EVENT_VI);
}

int SlaveDivisor(double intervalNs) {
    const double vi = (double) kVi.count();
    if (intervalNs > vi * (1.0 - kSlaveTolerance) && intervalNs < vi * (1.0 + kSlaveTolerance)) {
        return 1;
    }
    if (intervalNs > 2.0 * vi * (1.0 - kSlaveTolerance) && intervalNs < 2.0 * vi * (1.0 + kSlaveTolerance)) {
        return 2;
    }
    return 0;
}

void TickerMain() {
    auto next = Clock::now() + kVi;
    auto lastRetrace = Clock::now();
    bool halfPending = false;

    while (sTickerRun.load(std::memory_order_relaxed)) {
        bool presented = false;
        int divisor = 0;
        {
            std::unique_lock<std::mutex> lock(sPresentMutex);
            sPresentCv.wait_until(lock, next, [] { return sPresented || !sTickerRun.load(std::memory_order_relaxed); });
            if (!sTickerRun.load(std::memory_order_relaxed)) {
                break;
            }
            presented = sPresented;
            sPresented = false;
            divisor = sPresentsPerVi;
        }
        const auto now = Clock::now();

        if (presented) {
            if (divisor == 0 || now - lastRetrace < kVi / 2) {
                continue;
            }
            Retrace();
            lastRetrace = now;
            halfPending = (divisor == 2);
            next = now + (halfPending ? kVi : kVi + std::chrono::duration_cast<Clock::duration>(kVi * kPresentGrace));
            continue;
        }

        if (halfPending) {
            halfPending = false;
            Retrace();
            lastRetrace = now;
            next = now + kVi + std::chrono::duration_cast<Clock::duration>(kVi * kPresentGrace);
            continue;
        }
        Retrace();
        lastRetrace = now;
        next += kVi;
        if (now - next > std::chrono::milliseconds(100)) {
            next = now + kVi;
        }
    }
}

} // namespace

extern "C" void osCreateViManager(OSPri pri) {
    (void) pri;
    if (sTickerRun.exchange(true)) {
        return;
    }
    sTicker = std::thread(TickerMain);
}

extern "C" void OS_StopViTicker(void) {
    if (!sTickerRun.exchange(false)) {
        return;
    }
    sPresentCv.notify_all();
    if (sTicker.joinable()) {
        sTicker.join();
    }
}

extern "C" void OS_ViNotifyPresent(void) {
    const auto now = Clock::now();
    {
        std::lock_guard<std::mutex> lock(sPresentMutex);
        if (sLastPresent != Clock::time_point {}) {
            const double interval =
                (double) std::chrono::duration_cast<std::chrono::nanoseconds>(now - sLastPresent).count();
            if (interval > 4.0 * (double) kVi.count()) {
                sPresentIntervalNs = 0.0;
            } else {
                sPresentIntervalNs = sPresentIntervalNs == 0.0 ? interval : sPresentIntervalNs * 0.8 + interval * 0.2;
            }
        }
        sLastPresent = now;
        sPresentsPerVi = sPresentIntervalNs == 0.0 ? 0 : SlaveDivisor(sPresentIntervalNs);
        sPresented = true;
    }
    sPresentCv.notify_one();
}

extern "C" void osViSetEvent(OSMesgQueue* queue, OSMesg mesg, u32 retraceCount) {
    (void) retraceCount;
    osSetEventMesg(OS_EVENT_VI, queue, mesg);
}

extern "C" void osViSwapBuffer(void* framebuffer) {
    sNextFramebuffer.store(framebuffer, std::memory_order_release);
}

extern "C" void* osViGetNextFramebuffer(void) {
    return sNextFramebuffer.load(std::memory_order_acquire);
}

extern "C" void* osViGetCurrentFramebuffer(void) {
    return sCurrentFramebuffer.load(std::memory_order_acquire);
}

extern "C" void osViSetMode(OSViMode* mode) {
    (void) mode;
}

extern "C" void osViSetSpecialFeatures(u32 features) {
    (void) features;
}

extern "C" void osViBlack(u8 active) {
    sBlack.store(active != 0, std::memory_order_release);
}

extern "C" int OS_ViBlackActive(void) {
    return sBlack.load(std::memory_order_acquire) ? 1 : 0;
}

extern "C" void osViSetXScale(f32 scale) {
    (void) scale;
}

extern "C" void osViSetYScale(f32 scale) {
    (void) scale;
}

extern "C" void osViRepeatLine(u8 repeat) {
    (void) repeat;
}
