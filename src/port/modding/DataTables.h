#pragma once

#include <stdint.h>

#ifdef __cplusplus
#include <memory>

namespace Ship {
class Blob;
}

std::shared_ptr<Ship::Blob> Mod_LoadTable(const char* resourcePath);

extern "C" {
#endif

int32_t Mod_ReadBE32(const uint8_t* p);
int16_t Mod_ReadBE16(const uint8_t* p);

#ifdef __cplusplus
}
#endif
