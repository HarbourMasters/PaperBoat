#ifndef _GAME_MODES_H_
#define _GAME_MODES_H_

#include "common.h"

enum GameMode {
    GAME_MODE_STARTUP,
    GAME_MODE_LOGOS,
    GAME_MODE_TITLE_SCREEN,
    GAME_MODE_ENTER_DEMO_WORLD,
    GAME_MODE_ENTER_WORLD,
    GAME_MODE_WORLD,
    GAME_MODE_CHANGE_MAP,
    GAME_MODE_GAME_OVER,
    GAME_MODE_BATTLE,
    GAME_MODE_END_BATTLE,
    GAME_MODE_PAUSE,
    GAME_MODE_UNPAUSE,
    GAME_MODE_FILE_SELECT,
    GAME_MODE_END_FILE_SELECT,
    GAME_MODE_INTRO,
    GAME_MODE_DEMO,
};

enum LogoStates {
    LOGOS_STATE_N64_FADE_IN         = 0x0,
    LOGOS_STATE_N64_HOLD            = 0x1,
    LOGOS_STATE_N64_FADE_OUT        = 0x2,
    LOGOS_STATE_NINTENDO_FADE_IN    = 0x3,
    LOGOS_STATE_NINTENDO_HOLD       = 0x4,
    LOGOS_STATE_NINTENDO_FADE_OUT   = 0x5,
    LOGOS_STATE_IS_FADE_IN          = 0x6,
    LOGOS_STATE_IS_HOLD_1           = 0x7,
    LOGOS_STATE_IS_HOLD_2           = 0x8,
    LOGOS_STATE_IS_FADE_OUT         = 0x9,
    LOGOS_STATE_CURTAINS_APPEAR     = 0xA,
    LOGOS_STATE_CLEANUP             = 0xB,
};

enum {
    NEXT_STATE_DEMO             = 10,
    NEXT_STATE_INTRO            = 9,
    NEXT_STATE_FILE_SELECT      = 5,
    NEXT_STATE_NONE             = 0, // used only for the initial value
};

enum ChangeMapStates {
    CHANGE_MAP_INIT             = 0,
    CHANGE_MAP_DELAY            = 1,
    CHANGE_MAP_LOAD_MAP         = 2,
    CHANGE_MAP_AWAIT_MAIN       = 3,
    CHANGE_MAP_FADE_IN          = 4,
};

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

void set_game_mode(s32 mode);
s32 get_game_mode(void);
void set_game_mode_render_frontUI(void (*fn)(void));

void clear_game_mode(void);
void step_game_mode(void);
void render_game_mode_backUI(void);
void render_game_mode_frontUI(void);

#ifdef _LANGUAGE_C_PLUS_PLUS
} // extern "C"
#endif

#endif
