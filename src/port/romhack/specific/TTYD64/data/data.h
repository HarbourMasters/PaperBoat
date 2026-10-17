#pragma once

#include "common.h"
#include "hud_element.h"
#include "item_entity.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TTYD64_ItemIcon {
    s32 itemID;
    HudScript* enabled;
    HudScript* disabled;
    ItemScript* entity;
    const char* raster;
    const char* palette;
} TTYD64_ItemIcon;

typedef struct TTYD64_ItemIconOffsets {
    s32 itemID;
    const char* raster;
    const char* palette;
} TTYD64_ItemIconOffsets;

extern const TTYD64_ItemIcon TTYD64_ItemIcons[];
extern const s32 TTYD64_ItemIconCount;
extern const TTYD64_ItemIconOffsets TTYD64_ItemIconTail[];
extern const s32 TTYD64_ItemIconTailCount;

#ifdef __cplusplus
}
#endif
