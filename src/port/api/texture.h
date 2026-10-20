#pragma once

#include <stdint.h>

#include "api.h"

PB_API const void* C_LoadFile(const char* path, uint32_t* size);

typedef enum {
    C_TEXTURE_RGBA32 = 1,
    C_TEXTURE_RGBA16 = 2,
    C_TEXTURE_CI4 = 3,
    C_TEXTURE_CI8 = 4,
    C_TEXTURE_I4 = 5,
    C_TEXTURE_I8 = 6,
    C_TEXTURE_IA4 = 7,
    C_TEXTURE_IA8 = 8,
    C_TEXTURE_IA16 = 9,
} C_TextureFormat;

typedef struct C_TextureInfo_s {
    uint32_t width;
    uint32_t height;
    C_TextureFormat format;
    const void* data; // pixels in the format's N64 layout
    uint32_t size;    // bytes of data
} C_TextureInfo;

// Loads a texture asset and fills info. Returns 1 when it is one. The pixels stay valid until the mod unloads.
PB_API int C_LoadTexture(const char* path, C_TextureInfo* info);

// Tells the renderer that a texture in memory changed, e.g. pixels a mod drew into. The renderer keeps textures by
// address and would otherwise go on drawing the old ones.
PB_API void C_InvalidateTexture(const void* address);
