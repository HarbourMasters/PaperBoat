#include "OS.h"

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <thread>
#include <vector>

#include <spdlog/spdlog.h>

#include "port/audio/AudioVolume.h"
#include "port/DevTools/ThreadWatchdog.h"

extern "C" {
extern int32_t AlFrameSize;

int32_t AudioPlayerBuffered(void);
int32_t AudioPlayerGetDesiredBuffered(void);
void AudioPlayerPlayFrame(const uint8_t* buf, size_t len);
}

#define AI_STATUS_FIFO_FULL (1u << 31)
#define NU_SC_RETRACE_MSG   0x0001

namespace {

constexpr int kMaxPendingTicks = 32;
constexpr int kBackendCapacityFrames = 6000;

std::mutex& TickMutex() {
    static std::mutex* m = new std::mutex();
    return *m;
}

std::condition_variable& TickCv() {
    static std::condition_variable* cv = new std::condition_variable();
    return *cv;
}

int sPendingTicks = 0;

std::thread sTicker;
std::atomic<bool> sTickerRunning { false };

std::atomic<bool> sBackendGone { false };

bool BackendGone() {
    return sBackendGone.load(std::memory_order_acquire);
}

short sRetraceMsg = NU_SC_RETRACE_MSG;

std::recursive_mutex& BgmMutex() {
    static std::recursive_mutex* m = new std::recursive_mutex();
    return *m;
}

int CatchupTicks() {
    if (BackendGone()) {
        return 1;
    }
    const int32_t frameSize = AlFrameSize > 0 ? AlFrameSize : 1;
    const int32_t deficit = AudioPlayerGetDesiredBuffered() - (AudioPlayerBuffered() + frameSize);
    if (deficit <= 0) {
        return 1;
    }
    return 1 + (deficit + frameSize - 1) / frameSize;
}

void TickerMain() {
    using clock = std::chrono::steady_clock;
    const auto period = std::chrono::duration_cast<clock::duration>(std::chrono::duration<double>(1.0 / 60.0));

    auto next = clock::now() + period;

    while (sTickerRunning.load(std::memory_order_acquire)) {
        std::this_thread::sleep_until(next);

        ThreadWatchdog_Beat(WATCHDOG_AUDIO_TICKER);

        const auto now = clock::now();
        next += period;
        if (next < now) {
            next = now + period;
        }

        if (!sTickerRunning.load(std::memory_order_acquire) || OS_ThreadShouldExit()) {
            break;
        }

        const int ticks = CatchupTicks();

        {
            std::lock_guard<std::mutex> lock(TickMutex());
            if (sPendingTicks < ticks) {
                sPendingTicks = ticks;
            }
            if (sPendingTicks > kMaxPendingTicks) {
                sPendingTicks = kMaxPendingTicks;
            }
        }
        TickCv().notify_one();
    }

    TickCv().notify_all();
}

} // namespace

extern "C" void port_auBgmLock(void) {
    BgmMutex().lock();
}

extern "C" void port_auBgmUnlock(void) {
    BgmMutex().unlock();
}

extern "C" int port_auBgmTryLock(void) {
    return BgmMutex().try_lock() ? 1 : 0;
}

extern "C" void port_auReleaseFence(void) {
    std::atomic_thread_fence(std::memory_order_release);
}

extern "C" void port_auAcquireFence(void) {
    std::atomic_thread_fence(std::memory_order_acquire);
}

extern "C" void port_auWaitRetrace(short** outMsg) {
    std::unique_lock<std::mutex> lock(TickMutex());
    TickCv().wait(lock, [] { return sPendingTicks > 0 || OS_ThreadShouldExit(); });

    if (sPendingTicks > 0) {
        sPendingTicks--;
    }
    *outMsg = &sRetraceMsg;
}

extern "C" void port_auStartTicker(void) {
    if (sTickerRunning.exchange(true, std::memory_order_acq_rel)) {
        return;
    }
    sTicker = std::thread(TickerMain);
}

extern "C" void port_auStopTicker(void) {
    const bool wasRunning = sTickerRunning.exchange(false, std::memory_order_acq_rel);

    {
        std::lock_guard<std::mutex> lock(TickMutex());
    }
    TickCv().notify_all();

    if (wasRunning && sTicker.joinable()) {
        sTicker.join();
    }
}

extern "C" void port_auBackendGone(void) {
    sBackendGone.store(true, std::memory_order_release);
}

extern "C" uint32_t port_aiGetLength(void) {
    if (BackendGone()) {
        return 0;
    }
    const int32_t excess = AudioPlayerBuffered() - AudioPlayerGetDesiredBuffered();
    return excess > 0 ? (uint32_t) excess * 4 : 0;
}

extern "C" int32_t port_aiSetNextBuffer(void* buf, uint32_t size) {
    if (BackendGone()) {
        return 0;
    }

    static std::atomic<bool> sLoggedFirst { false };
    if (!sLoggedFirst.exchange(true)) {
        SPDLOG_INFO("nuAuMgr audio reaching backend: {} bytes, buffered {}", size, AudioPlayerBuffered());
    }

    const float master = AudioVolume_GetMaster();

    if (master >= 1.0f) {
        AudioPlayerPlayFrame((const uint8_t*) buf, size);
        return 0;
    }

    static thread_local std::vector<int16_t> scaled;
    scaled.resize(size / sizeof(int16_t));

    const int16_t* src = (const int16_t*) buf;
    for (size_t i = 0; i < scaled.size(); i++) {
        scaled[i] = (int16_t) (src[i] * master);
    }

    AudioPlayerPlayFrame((const uint8_t*) scaled.data(), size);
    return 0;
}

extern "C" uint32_t osAiGetStatus(void) {
    if (BackendGone()) {
        return AI_STATUS_FIFO_FULL;
    }
    if (AudioPlayerBuffered() + AlFrameSize > kBackendCapacityFrames) {
        return AI_STATUS_FIFO_FULL;
    }
    return 0;
}
