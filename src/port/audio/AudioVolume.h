#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Publishes the Settings' Audio volume CVars to the audio thread.
void AudioVolume_Update(void);

float AudioVolume_GetMaster(void);
float AudioVolume_GetMusic(void);
float AudioVolume_GetSfx(void);

// Silences the game's music, e.g. while a mod plays its own. Sound effects and ambience keep playing.
void AudioVolume_SetGameMusicMuted(int32_t muted);

// Applies the music/SFX volume to an FX bus gain (see FxBus in audio.h).
uint16_t AudioVolume_ScaleBusGain(uint8_t busID, uint16_t gain);

// Applies the environment volume to an ambience player's fade volume.
int32_t AudioVolume_ScaleAmbience(int32_t volume);

// True while the environment volume differs from what the MSEQ player last
// pushed to its voices; AudioVolume_AmbienceCommit() clears it.
int32_t AudioVolume_AmbienceDirty(void);
void AudioVolume_AmbienceCommit(void);

#ifdef __cplusplus
}
#endif
