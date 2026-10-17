#include "common.h"
#include "hud_element.h"
#include "port/Engine.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_rawmem.h"
#include "../include/ttyd64_symbols.h"
#include "world_lib.h"
#include "world_lib_gen.h"
#include <stdio.h>

void draw_hud_element_internal(s32 id, s32 clipMode);

typedef struct TTYD64MoleGame {
    u8 state;
    u8 hours;
    u8 minutes;
    u8 seconds;
    u8 ticks;
    s32 score;
} TTYD64MoleGame;

static TTYD64MoleGame sMole;
static u8 sBartenderState;
u8 TTYD64_GoTimer[4];

static void ready_set_go(void) {
    u32 state = TTYD64_ReadBE(TTYD64_GoTimer, 0, 2);
    s32 timer;
    s32 done;
    s32 n;
    const u8* msg;

    if (state != 0) {
        if (state == 1 || state == 2 || state == 3) {
            n = state == 1 ? 3 : state == 2 ? 2 : 1;
            sprintf(TTYD64_ASCII_Buffer, "%3u", n);
            TTYD64_ConvertAsciiToPM64String(TTYD64_String_Buffer_Size25, TTYD64_ASCII_Buffer);
            msg = TTYD64_String_Buffer_Size25;
        } else {
            msg = TTYD64_String_Go;
        }
        draw_msg(TTYD64_WorldLib_MsgID(msg), 0x68, 0x71, 0xFF, 0, 2);
    }
    state = (s16) TTYD64_ReadBE(TTYD64_GoTimer, 0, 2);
    timer = (TTYD64_ReadBE(TTYD64_GoTimer, 2, 2) + 1) & 0xFFFF;
    TTYD64_WriteBE(TTYD64_GoTimer, 2, 2, timer);
    if ((s32) state == 4) {
        done = (u32) timer < 0x19;
    } else {
        done = (u32) timer < 0x14;
    }
    if (done) {
        return;
    }
    state = (s32) state + 1;
    TTYD64_WriteBE(TTYD64_GoTimer, 0, 2, state);
    TTYD64_WriteBE(TTYD64_GoTimer, 2, 2, 0);
    if (state < 5) {
        sfx_play_sound(state == 4 ? 0x395 : 0x233);
    }
}

static void mole_ready_set_go(void) {
    if (TTYD64_ReadBE(TTYD64_GoTimer, 0, 2) == 5) {
        sMole.state = 2;
    } else {
        ready_set_go();
    }
}

static void mole_clear_timer(void) {
    sMole.hours = 0;
    sMole.minutes = 0;
    sMole.seconds = 0;
    sMole.ticks = 0;
}

static void mole_update_score_and_timer(void) {
    TTYD64MoleGame* d = &sMole;
    s32 x;
    s32 y;
    s8 t;
    s8 minutes;

    draw_msg(TTYD64_WorldLib_MsgID(TTYD64_String_Score), 0x13, 0xC5, 0xFF, 0, 0);
    draw_number(d->score, 0x45, 0xC8, 0, 0, 0xFF, 0);

    sprintf(TTYD64_ASCII_Buffer, "%02u", (s8) d->minutes);
    TTYD64_ConvertAsciiToPM64String(TTYD64_String_Buffer_Size20, TTYD64_ASCII_Buffer);
    x = 0xD9;
    y = 0xC4;
    draw_msg(TTYD64_WorldLib_MsgID(TTYD64_String_Buffer_Size20), x, y, 0xFF, 0, 0);
    draw_msg(TTYD64_WorldLib_MsgID(TTYD64_String_DosPuntos), x + 0x34, y, 0xFF, 0, 0);
    sprintf(TTYD64_ASCII_Buffer, "%02u", (s8) d->seconds);
    TTYD64_ConvertAsciiToPM64String(TTYD64_String_Buffer_Size20, TTYD64_ASCII_Buffer);
    x += 0x20;
    draw_msg(TTYD64_WorldLib_MsgID(TTYD64_String_Buffer_Size20), x, y, 0xFF, 0, 0);

    if ((s8) d->minutes + (s8) d->seconds == 0) {
        mole_clear_timer();
        d->state = 3;
        return;
    }
    if (d->state != 2) {
        return;
    }
    t = d->ticks;
    if (t > 0) {
        d->ticks = t - 3;
        return;
    }
    d->ticks = 85;
    t = d->seconds;
    if (t > 0) {
        t = t - 1;
        minutes = d->minutes;
        if (minutes == 0 && (u32) (s32) t < 11) {
            sfx_play_sound(0x1A5);
        }
        d->seconds = t;
        return;
    }
    sfx_play_sound(0x1A5);
    d->seconds = 59;
    t = d->minutes;
    if (t > 0) {
        d->minutes = t - 1;
        return;
    }
    d->minutes = 59;
    d->hours = (s8) d->hours - 1;
}

static void mole_finish_game(void) {
    sMole.state = 0;
    start_script(&TTYD64_Script_ExitMinigame_Mole, 1, 0);
}

static void mole_step(void) {
    switch (sMole.state) {
        case 1:
            mole_ready_set_go();
            break;
        case 2:
            mole_update_score_and_timer();
            break;
        case 3:
            mole_finish_game();
            break;
    }
}

static void bar_ready_set_go(void) {
    if (TTYD64_ReadBE(TTYD64_GoTimer, 0, 2) == 5) {
        sBartenderState = 2;
    } else {
        ready_set_go();
    }
}

static void bar_draw_hp(void) {
    s32 hp;
    s32 size;

    TTYD64_DrawBox(0x3C, 0xC2, 0xD0, 0x14, 1, 0xFF);
    hp = evt_get_variable(NULL, MapVar(0));
    hp = (hp * 100) / 100;
    size = (0xD0 * hp) / 100;
    if (size < 0x10) {
        evt_set_variable(NULL, MapVar(0), 0);
        size = 0;
    }
    TTYD64_DrawBox(0x3C, 0xC2, size, 0x14, TTYD64_hp_BoxStyleBase, 0xFF);
    hud_element_set_render_pos(1, 0x32, 0xCB);
    TTYD64_SetIconSize(1, 20.0f, 20.0f);
    draw_hud_element_internal(1, 0);
    TTYD64_SetIconSize2(1, 16.0f, 16.0f);
}

static void bartender_step(void) {
    switch (sBartenderState) {
        case 1:
            bar_ready_set_go();
            break;
        case 2:
            bar_draw_hp();
            break;
    }
}

void TTYD64_Function_UpdateMinigames(void) {
    mole_step();
    bartender_step();
}

void TTYD64_Function_ClearMinigameData_Moles(void) {
    sMole.state = 0;
    TTYD64_WriteBE(TTYD64_GoTimer, 0, 4, 0);
    mole_clear_timer();
    sMole.score = 0;
}

void TTYD64_Function_ClearMinigameData_Bar(void) {
    sBartenderState = 0;
    TTYD64_WriteBE(TTYD64_GoTimer, 0, 4, 0);
}

API_CALLABLE(TTYD64_Mole_ClearData) {
    TTYD64_Function_ClearMinigameData_Moles();
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Bar_ClearData) {
    TTYD64_Function_ClearMinigameData_Bar();
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Mole_GetState) {
    evt_set_variable(script, *script->ptrReadPos, sMole.state);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Mole_SetState) {
    sMole.state = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Mole_StartTimer) {
    mole_clear_timer();
    sMole.seconds = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Mole_GetSeconds) {
    evt_set_variable(script, *script->ptrReadPos, sMole.seconds);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Mole_GetScore) {
    evt_set_variable(script, *script->ptrReadPos, sMole.score);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Mole_SetScore) {
    sMole.score = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Bar_GetState) {
    evt_set_variable(script, *script->ptrReadPos, sBartenderState);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Bar_SetState) {
    sBartenderState = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}
