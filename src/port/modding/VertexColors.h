#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ModVertexRef {
    const char* vtxAsset;
    int32_t index;
} ModVertexRef;

void Mod_SetVertexColor(ModVertexRef ref, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void Mod_SetVertexColorRGB(ModVertexRef ref, uint8_t r, uint8_t g, uint8_t b);

#ifdef __cplusplus
}
#endif
