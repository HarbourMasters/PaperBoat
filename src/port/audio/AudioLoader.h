#ifndef AUDIO_LOADER_H
#define AUDIO_LOADER_H

#include <stdint.h>

#ifdef __cplusplus
namespace Ship { class BinaryReader; }
typedef Ship::BinaryReader AudioReader;
#else
typedef void AudioReader;
#endif

#ifdef __cplusplus
extern "C" {
#endif

AudioReader* Audio_MakeReader(int32_t offset);
void Audio_FreeReader(AudioReader* reader);
uint32_t Audio_ReadU32(AudioReader* reader);
uint16_t Audio_ReadU16(AudioReader* reader);
int32_t Audio_ReadS32(AudioReader* reader);
int16_t Audio_ReadS16(AudioReader* reader);
uint8_t Audio_ReadU8(AudioReader* reader);
void Audio_ReadBytes(AudioReader* reader, void* buf, uint32_t size);
void Audio_Seek(AudioReader* reader, int32_t offset);

#ifdef __cplusplus
}
#endif

#endif // AUDIO_LOADER_H
