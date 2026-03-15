#include "AudioLoader.h"
#include "ship/utils/binarytools/BinaryReader.h"

extern "C" {

// Global SBN data pointer (defined in engine.c)
extern uint8_t *gSbnData;

// Size of the SBN data - we'll use a large value since we don't track actual
// size
static constexpr size_t kMaxSbnSize =
    16 * 1024 * 1024; // 16MB should be more than enough

AudioReader *Audio_MakeReader(int32_t offset) {
  auto reader =
      new Ship::BinaryReader((char *)gSbnData + offset, kMaxSbnSize - offset);
  reader->SetEndianness(Ship::Endianness::Big);
  return reader;
}

void Audio_FreeReader(AudioReader *reader) { delete reader; }

uint32_t Audio_ReadU32(AudioReader *reader) { return reader->ReadUInt32(); }

uint16_t Audio_ReadU16(AudioReader *reader) { return reader->ReadUInt16(); }

int32_t Audio_ReadS32(AudioReader *reader) { return reader->ReadInt32(); }

int16_t Audio_ReadS16(AudioReader *reader) { return reader->ReadInt16(); }

uint8_t Audio_ReadU8(AudioReader *reader) { return reader->ReadUByte(); }

void Audio_ReadBytes(AudioReader *reader, void *buf, uint32_t size) {
  reader->Read((char *)buf, size);
}

void Audio_Seek(AudioReader *reader, int32_t offset) {
  reader->Seek(offset, Ship::SeekOffsetType::Start);
}

} // extern "C"
