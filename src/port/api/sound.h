#pragma once

#include <stdint.h>

#include "api.h"

// Sounds and music of a mod's own, from WAV, MP3 or FLAC files in its archive. They are decoded when registered and
// mixed into the game's output, following the music and sound effect volume settings.

// Registers a sound from a file in a mod archive, e.g. "sound/chime.wav". Returns its number, or -1.
PB_API int C_RegisterSound(const char* path);
// Same as C_RegisterSound, from file data in memory, which is copied.
PB_API int C_RegisterSoundData(const uint8_t* data, uint32_t size);
// Unregisters a sound and stops it. A mod's sounds are unregistered when it unloads.
PB_API void C_UnregisterSound(int sound);
// Length of a sound in samples at 32 kHz, 0 for no sound.
PB_API uint32_t C_SoundLength(int sound);

// Plays a sound effect at volume 0 to 1 and pan -1 (left) to 1 (right). Returns a voice, or -1.
PB_API int C_PlaySound(int sound, float volume, float pan);
PB_API void C_StopSound(int voice);
PB_API int C_IsSoundPlaying(int voice);

// Plays a sound as music, silencing the game's music and song replacements until C_StopMusic or its end. loop_start
// is the sample (at 32 kHz) the music goes back to when it ends, -1 to play it once.
PB_API void C_PlayMusic(int sound, int32_t loop_start);
PB_API void C_StopMusic(void);
// Plays the sound whenever the game plays song (a SONG_* value) as its main music, until the game changes or stops
// it. sound -1 gives the game's own song back.
PB_API void C_ReplaceSong(int32_t song, int sound, int32_t loop_start);
