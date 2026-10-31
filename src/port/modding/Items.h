#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct ItemData;

void Mod_RegisterItem(
    const char* owner,
    int32_t itemID,
    const struct ItemData* data,
    const intptr_t (*enabled)[],
    const intptr_t (*disabled)[],
    intptr_t (*entityScript)[],
    const char* raster,
    const char* palette
);
void Mod_SetItemIcon(
    const char* owner,
    int32_t itemID,
    const intptr_t (*enabled)[],
    const intptr_t (*disabled)[],
    intptr_t (*entityScript)[],
    const char* raster,
    const char* palette
);

#ifdef __cplusplus
}
#endif
