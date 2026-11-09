#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void Mod_OverrideMapTextureSize(
    const char* owner, const char* archive, const char* name, uint16_t width, uint16_t height
);
bool Mod_GetMapTextureSize(const char* archive, const char* name, uint16_t* width, uint16_t* height);

void Mod_RegisterMapTexArchive(const char* owner, const char* archive, const char* blobPath);
const char* Mod_GetMapTexArchiveBlob(const char* archive);

#ifdef __cplusplus
}
#endif
