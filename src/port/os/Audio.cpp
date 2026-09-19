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

extern "C" {
extern int32_t AlFrameSize;

int32_t AudioPlayerBuffered(void);
int32_t AudioPlayerGetDesiredBuffered(void);
void AudioPlayerPlayFrame(const uint8_t* buf, size_t len);
}

#define AI_STATUS_FIFO_FULL (1 << 31)
#define NU_SC_RETRACE_MSG   0x0001

namespace {

constexpr int kMaxPendingTicks = 4;
constexpr int kBackendCapacityFrames = 6000;
constexpr int64_t kStallCushionMs = 2000;

std::mutex sTickMutex;
std::condition_variable sTickCv;
int sPendingTicks = 0;

std::thread sTicker;
std::atomic<bool> sTickerRunning{ false };

std::atomic<int64_t> sAllowedUntilMs{ 0 };

short sRetraceMsg = NU_SC_RETRACE_MSG;

std::recursive_mutex sBgmMutex;

int64_t NowMs() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch())
        .count();
}

bool NeedsCatchup() {
    return AudioPlayerBuffered() + AlFrameSize < AudioPlayerGetDesiredBuffered();
}

void TickerMain() {
    using clock = std::chrono::steady_clock;
    const auto period = std::chrono::duration_cast<clock::duration>(std::chrono::duration<double>(1.0 / 60.0));

    auto next = clock::now() + period;
    bool lastWasCatchup = false;

    while (sTickerRunning.load(std::memory_order_acquire)) {
        std::this_thread::sleep_until(next);

        const auto now = clock::now();
        next += period;
        if (next < now) {
            next = now + period;
        }

        if (!sTickerRunning.load(std::memory_order_acquire) || OS_ThreadShouldExit()) {
            break;
        }

        if (port_audioStallHold()) {
            lastWasCatchup = false;
            continue;
        }

        int ticks = 1;
        if (!lastWasCatchup && NeedsCatchup()) {
            ticks = 2;
            lastWasCatchup = true;
        } else {
            lastWasCatchup = false;
        }

        {
            std::lock_guard<std::mutex> lock(sTickMutex);
            sPendingTicks += ticks;
            if (sPendingTicks > kMaxPendingTicks) {
                sPendingTicks = kMaxPendingTicks;
            }
        }
        sTickCv.notify_one();
    }

    sTickCv.notify_all();
}

} // namespace

extern "C" void port_auBgmLock(void) {
    sBgmMutex.lock();
}

extern "C" void port_auBgmUnlock(void) {
    sBgmMutex.unlock();
}

extern "C" int port_auBgmTryLock(void) {
    return sBgmMutex.try_lock() ? 1 : 0;
}

extern "C" void port_auReleaseFence(void) {
    std::atomic_thread_fence(std::memory_order_release);
}

extern "C" void port_auAcquireFence(void) {
    std::atomic_thread_fence(std::memory_order_acquire);
}

extern "C" void port_noteMainLoopAlive(void) {
    sAllowedUntilMs.store(NowMs() + kStallCushionMs, std::memory_order_relaxed);
}

extern "C" int port_audioStallHold(void) {
    const int64_t allowedUntil = sAllowedUntilMs.load(std::memory_order_relaxed);
    return allowedUntil != 0 && NowMs() > allowedUntil;
}

extern "C" void port_auWaitRetrace(short** outMsg) {
    std::unique_lock<std::mutex> lock(sTickMutex);
    sTickCv.wait(lock, [] { return sPendingTicks > 0 || OS_ThreadShouldExit(); });

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
        std::lock_guard<std::mutex> lock(sTickMutex);
    }
    sTickCv.notify_all();

    if (wasRunning && sTicker.joinable()) {
        sTicker.join();
    }
}

extern "C" uint32_t port_aiGetLength(void) {
    const int32_t excess = AudioPlayerBuffered() - AudioPlayerGetDesiredBuffered();
    return excess > 0 ? (uint32_t) excess * 4 : 0;
}

extern "C" int32_t port_aiSetNextBuffer(void* buf, uint32_t size) {
    static std::atomic<bool> sLoggedFirst{ false };
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
    if (AudioPlayerBuffered() + AlFrameSize > kBackendCapacityFrames) {
        return AI_STATUS_FIFO_FULL;
    }
    return 0;
}
