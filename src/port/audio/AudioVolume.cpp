#include "AudioVolume.h"

#include <atomic>

#include <libultraship.h>

#include "port/ui/cvar_prefixes.h"

namespace {
std::atomic<int32_t> sMaster { 100 };
std::atomic<int32_t> sMusic { 100 };
std::atomic<int32_t> sSfx { 100 };
std::atomic<int32_t> sAmbience { 100 };
std::atomic<bool> sGameMusicMuted { false };

// Last ambience percentage the MSEQ player has pushed to its voices.
int32_t sAmbienceApplied = 100;

int32_t ClampPercent(int32_t value) {
    if (value < 0) {
        return 0;
    }
    if (value > 100) {
        return 100;
    }
    return value;
}
} // namespace

extern "C" {

void AudioVolume_Update(void) {
    sMaster.store(ClampPercent(CVarGetInteger(CVAR_SETTING("Volume.Master"), 100)), std::memory_order_relaxed);
    sMusic.store(ClampPercent(CVarGetInteger(CVAR_SETTING("Volume.MainMusic"), 100)), std::memory_order_relaxed);
    sSfx.store(ClampPercent(CVarGetInteger(CVAR_SETTING("Volume.SFX"), 100)), std::memory_order_relaxed);
    sAmbience.store(ClampPercent(CVarGetInteger(CVAR_SETTING("Volume.Environment"), 100)), std::memory_order_relaxed);
}

float AudioVolume_GetMaster(void) {
    return sMaster.load(std::memory_order_relaxed) / 100.0f;
}

float AudioVolume_GetMusic(void) {
    return sMusic.load(std::memory_order_relaxed) / 100.0f;
}

float AudioVolume_GetSfx(void) {
    return sSfx.load(std::memory_order_relaxed) / 100.0f;
}

void AudioVolume_SetGameMusicMuted(int32_t muted) {
    sGameMusicMuted.store(muted != 0, std::memory_order_relaxed);
}

uint16_t AudioVolume_ScaleBusGain(uint8_t busID, uint16_t gain) {
    // FX_BUS_SOUND carries both sound effects and ambience; the ambience half
    // is attenuated separately in the MSEQ player.
    int32_t percent = (busID == 1) ? sSfx.load(std::memory_order_relaxed) : sMusic.load(std::memory_order_relaxed);
    if (busID != 1 && sGameMusicMuted.load(std::memory_order_relaxed)) {
        percent = 0;
    }
    return (uint16_t) (((int32_t) gain * percent) / 100);
}

int32_t AudioVolume_ScaleAmbience(int32_t volume) {
    return (volume * sAmbience.load(std::memory_order_relaxed)) / 100;
}

int32_t AudioVolume_AmbienceDirty(void) {
    return sAmbience.load(std::memory_order_relaxed) != sAmbienceApplied;
}

void AudioVolume_AmbienceCommit(void) {
    sAmbienceApplied = sAmbience.load(std::memory_order_relaxed);
}

} // extern "C"
