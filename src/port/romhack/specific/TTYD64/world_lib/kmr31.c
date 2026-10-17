#include "common.h"
#include "port/Engine.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_symbols.h"
#include "world_lib.h"
#include "world_lib_gen.h"
#include <string.h>

typedef struct TTYD64Kmr31Box {
    u8 state;
    u8 alpha;
    u8 arrowReturning;
    u8 arrowOffset;
    u8 arrowTimer;
    s32 message;
} TTYD64Kmr31Box;

static TTYD64Kmr31Box sBox;

void TTYD64_Function_kmr31_DrawDescriptionBox(void) {
    TTYD64Kmr31Box* d = &sBox;
    u8 timer;
    u8 state;
    u8 offset;

    if (d->state == 0) {
        return;
    }
    TTYD64_DrawBox(0x14, 0xBA, 0x118, 0x20, 3, d->alpha);
    draw_msg(d->message, 0x1D, 0xBA, d->alpha, 0, 0);

    timer = d->arrowTimer;
    if (timer < 2) {
        d->arrowTimer = timer + 1;
    } else {
        d->arrowTimer = 0;
        state = d->arrowReturning;
        offset = d->arrowOffset;
        if (state != 0) {
            if (offset == 0) {
                d->arrowReturning = 0;
            }
        } else if (offset >= 3) {
            d->arrowReturning = 1;
        }
        if (d->arrowReturning == 0) {
            offset = offset + 1;
        } else {
            offset = offset - 1;
        }
        d->arrowOffset = offset;
    }
    draw_msg(TTYD64_WorldLib_MsgID(TTYD64_String_Arrow_Left), 0x18 - d->arrowOffset, 0x76, d->alpha, 0, 0);
    draw_msg(TTYD64_WorldLib_MsgID(TTYD64_String_Arrow_Right), 0x117 + d->arrowOffset, 0x76, d->alpha, 0, 0);
}

API_CALLABLE(TTYD64_Function_ClearData_KMR31_ExtraData) {
    memset(&sBox, 0, sizeof(sBox));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_kmr31_Get) {
    Bytecode* args = script->ptrReadPos;
    s32 slot = evt_get_variable(script, *args++);
    s32 value = 0;

    switch (slot) {
        case TTYD64_K31_STATE:
            value = sBox.state;
            break;
        case TTYD64_K31_ALPHA:
            value = sBox.alpha;
            break;
        case TTYD64_K31_MESSAGE:
            value = sBox.message;
            break;
    }
    evt_set_variable(script, *args++, value);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_kmr31_Set) {
    Bytecode* args = script->ptrReadPos;
    s32 slot = evt_get_variable(script, *args++);
    s32 value = evt_get_variable(script, *args++);

    switch (slot) {
        case TTYD64_K31_STATE:
            sBox.state = value;
            break;
        case TTYD64_K31_ALPHA:
            sBox.alpha = value;
            break;
        case TTYD64_K31_MESSAGE:
            sBox.message = value;
            break;
    }
    return ApiStatus_DONE2;
}
