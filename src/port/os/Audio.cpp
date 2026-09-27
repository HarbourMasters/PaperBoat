#include "OS.h"

#include <atomic>
#include <cstddef>
#include <mutex>
#include <vector>

#include "port/audio/AudioVolume.h"

extern "C" {
extern int32_t AlFrameSize;

int32_t AudioPlayerBuffered(void);
int32_t AudioPlayerGetDesiredBuffered(void);
void AudioPlayerPlayFrame(const uint8_t* buf, size_t len);
}

#define AI_STATUS_FIFO_FULL (1u << 31)

namespace {

constexpr int kBackendCapacityFrames = 6000;

std::atomic<bool> sBackendGone { false };

bool BackendGone() {
    return sBackendGone.load(std::memory_order_acquire);
}

std::recursive_mutex& BgmMutex() {
    static std::recursive_mutex* m = new std::recursive_mutex();
    return *m;
}

} // namespace

extern "C" void port_auBgmLock(void) {
    BgmMutex().lock();
}

extern "C" void port_auBgmUnlock(void) {
    BgmMutex().unlock();
}

extern "C" void port_auReleaseFence(void) {
    std::atomic_thread_fence(std::memory_order_release);
}

extern "C" void port_auAcquireFence(void) {
    std::atomic_thread_fence(std::memory_order_acquire);
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
