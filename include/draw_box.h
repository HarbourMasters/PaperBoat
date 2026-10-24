#ifndef _DRAW_BOX_H_
#define _DRAW_BOX_H_

#include "common_structs.h"

#define WINDOW_STYLE_REGISTERED_MAX 100

typedef struct DefaultWindowStyle {
    /* 0x00 */ u8 bgIndex;
    /* 0x01 */ u8 cornersIndex;
    /* 0x02 */ u8 combineModeIndex;
    /* 0x03 */ Color_RGBA8 color1;
    /* 0x07 */ Color_RGBA8 color2;
} DefaultWindowStyle; // size = 0x0B

#endif
