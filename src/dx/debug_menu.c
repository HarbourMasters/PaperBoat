// #include "dx/debug_menu.h"
#include "common.h"
#if DX_DEBUG_MENU || defined(DX_QUICK_LAUNCH_BATTLE)
#include "game_modes.h"
#include "battle/battle.h"
#include "hud_element.h"
#include "inventory.h"
#include "qsort.h"
#include <string.h>
#include "dx/utils.h"
#include "msg.h"
#include "fio.h"

// layout

const s32 MainMenuPosX    = 26;
const s32 MainMenuPosY    = 60;

const s32 RowHeight       = 15;
const s32 BottomRowY      = 222;

const s32 SubmenuPosX     = 140;
const s32 SubmenuPosY     = MainMenuPosY;

const s32 BoxOutsetX      = 10;
const s32 BoxOutsetY      = 4;

const s32 SubBoxPosX      = SubmenuPosX - BoxOutsetX;
const s32 SubBoxPosY      = SubmenuPosY - BoxOutsetY;

// which menu or submenu is open, only one is displayed at a time
// pressing ACCEPT (R) or CANCEL (L) usually moves between these states
enum DebugMenuStates {
    DBM_NONE,
    // press D-left to open debug menu
    DBM_MAIN_MENU,
    DBM_QUICK_SAVE,
    DBM_SELECT_AREA,
        DBM_SELECT_MAP,
        DBM_SELECT_ENTRY,
    DBM_SELECT_BATTLE,
    DBM_SET_STORY,
    DBM_SOUND_PLAYER,
        DBM_SELECT_SOUND,
    DBM_EDIT_PARTNERS,
    DBM_EDIT_INVENTORY,
        DBM_INV_EDIT_ITEMS,
        DBM_INV_EDIT_BADGES,
        DBM_INV_EDIT_KEYS,
        DBM_INV_EDIT_GEAR,
        DBM_INV_EDIT_STATS,
        DBM_INV_EDIT_COINS,
        DBM_INV_EDIT_STAR_POINTS,
        DBM_INV_EDIT_STAR_PIECES,
    DBM_EDIT_MEMORY,
    DBM_VIEW_COLLISION,
    DBM_CHEAT_MENU,
    // press D-right to open script debugger
    DBM_EVT_MAIN,
    DBM_EVT_SELECT,
    DBM_EVT_ATTACHED,
};

s32 DebugMenuState = DBM_NONE;
b32 DebugStateChanged = false;

const s32 DefaultColor = MSG_PAL_WHITE;
const s32 HoverColor   = MSG_PAL_GREEN;
const s32 SelectColor  = MSG_PAL_PURPLE;
s32 HighlightColor;

// data grabbed during map or battle load

char LastMapName[16];
char LastStageName[16];
s32 LastMapEntry;
s32 LastBattleID;

void dx_debug_set_map_info(char* mapName, s32 entryID) {
    strcpy(LastMapName, mapName);
    LastMapEntry = entryID;
}

void dx_debug_set_battle_info(s32 battleID, const char* stageName) {
    s32 len = strlen(stageName);

    strcpy(LastStageName, stageName);
    if (len > 6) {
        // trim "_shape" from name
        LastStageName[len - 6] = '\0';
    }
    LastBattleID = battleID;
}

// input

u32 DebugButtonsCur;
u32 DebugButtonsPrev;
u32 DebugButtonsPress;
u32 DebugButtonsHold;
u32 DebugButtonsRelease;

typedef struct DebugHold {
    s16 delay;
    u16 triggers;
} DebugHold;

DebugHold DebugHoldU = { 0 };
DebugHold DebugHoldD = { 0 };
DebugHold DebugHoldL = { 0 };
DebugHold DebugHoldR = { 0 };

#define PRESSED(but) (DebugButtonsPress & (but))
#define RELEASED(but) (DebugButtonsRelease & (but))
#define HELD(but) (DebugButtonsHold & (but))

#define INIT_HOLD_RATE 6 // slight start-up delay
#define SLOW_HOLD_RATE 4
#define FAST_HOLD_RATE 2

void dx_debug_update_hold_frames(DebugHold* hold, u32 but) {
    if (PRESSED(but)) {
        hold->delay = INIT_HOLD_RATE;
        hold->triggers = 0;
    } else if (HELD(but)) {
        hold->delay--;
        if (hold->delay < 0) {
            hold->triggers++;

            if (hold->triggers < 5) {
                hold->delay = SLOW_HOLD_RATE;
            } else if (hold->triggers < 15) {
                hold->delay = FAST_HOLD_RATE;
            } else {
                hold->delay = 1;
            }
        }
    } else {
        hold->delay = 999;
        hold->triggers = 0;
    }
}

void dx_debug_update_buttons() {
    DebugButtonsPrev = DebugButtonsCur;
    DebugButtonsCur = gGameStatus.curButtons[0];
    DebugButtonsHold = DebugButtonsCur & DebugButtonsPrev;
    DebugButtonsPress = DebugButtonsCur & (DebugButtonsCur ^ DebugButtonsPrev);
    DebugButtonsRelease = DebugButtonsPrev & (DebugButtonsCur ^ DebugButtonsPrev);

    dx_debug_update_hold_frames(&DebugHoldU, BUTTON_D_UP);
    dx_debug_update_hold_frames(&DebugHoldD, BUTTON_D_DOWN);
    dx_debug_update_hold_frames(&DebugHoldL, BUTTON_D_LEFT);
    dx_debug_update_hold_frames(&DebugHoldR, BUTTON_D_RIGHT);
};

#define NAV_UP    (PRESSED(BUTTON_D_UP)    || DebugHoldU.delay == 0)
#define NAV_DOWN  (PRESSED(BUTTON_D_DOWN)  || DebugHoldD.delay == 0)
#define NAV_LEFT  (PRESSED(BUTTON_D_LEFT)  || DebugHoldL.delay == 0)
#define NAV_RIGHT (PRESSED(BUTTON_D_RIGHT) || DebugHoldR.delay == 0)

// utility functions for drawing menus

void dx_debug_draw_box(s32 posX, s32 posY, s32 sizeX, s32 sizeY, int style, s32 opacity) {
    draw_box(0, (void*)(intptr_t)style, posX, posY, 0, sizeX, sizeY, opacity,
        0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, nullptr, 0, nullptr, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr);
}

void dx_debug_draw_ascii(char* text, s32 color, s32 posX, s32 posY) {
    char buf[128] = {
        MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SIZE, 12, 12
    };
    dx_string_to_msg(&buf[4], text);
    draw_msg((intptr_t)buf, posX, posY, 255, color, 0);
}

void dx_debug_draw_ascii_with_effect(char* text, s32 color, s32 posX, s32 posY, s32 effect) {
    char buf[128] = {
        MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SIZE, 12, 12
    };
    dx_string_to_msg(&buf[4], text);
    draw_msg((intptr_t)buf, posX, posY, 255, color, effect);
}

void dx_debug_draw_msg(s32 msgID, s32 color, s32 alpha, s32 posX, s32 posY) {
    ALIGNED(8) char buf[128] = {
        MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SIZE, 12, 12,
    };
    dma_load_msg(msgID, &buf[4]);
    draw_msg((intptr_t)buf, posX, posY, alpha, color, 0);
}

void dx_debug_draw_number(s32 number, char* fmt, s32 color, s32 alpha, s32 posX, s32 posY) {
    char fmtBuf[16];
    char buf[16] = {
        MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SIZE, 12, 12
    };
    sprintf(fmtBuf, fmt, number);
    dx_string_to_msg(&buf[4], fmtBuf);
    draw_msg((intptr_t)buf, posX, posY, alpha, color, 0);
}

// efficiently renders an number with (optionally) a digit highlighted using a single draw_msg call
void dx_debug_draw_editable_number(s32 number, char* fmt, s32 selectedDigit, b32 hasSelected, s32 posX, s32 posY) {
    char msgBuf[32] = {
        MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SIZE, 12, 12,
        MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SPACING, 8
    };
    s32 pos = 7; // writePos to msgBuf

    char fmtBuf[16];
    s32 len = sprintf(fmtBuf, fmt, number);
    s32 idx; // readPos from fmtBuf

    for (idx = 0; idx < len; idx++) {
        if (hasSelected && selectedDigit == idx) {
            msgBuf[pos++] = MSG_CHAR_READ_FUNCTION;
            msgBuf[pos++] = MSG_READ_FUNC_SAVE_COLOR;
            msgBuf[pos++] = MSG_CHAR_READ_FUNCTION;
            msgBuf[pos++] = MSG_READ_FUNC_COLOR;
            msgBuf[pos++] = HighlightColor;
        }
        msgBuf[pos++] = dx_ascii_char_to_msg(fmtBuf[idx]);
        if (hasSelected && selectedDigit == idx) {
            msgBuf[pos++] = MSG_CHAR_READ_FUNCTION;
            msgBuf[pos++] = MSG_READ_FUNC_RESTORE_COLOR;
        }
    }
    msgBuf[pos] = MSG_CHAR_READ_END;

    if (hasSelected && selectedDigit == -1) {
        draw_msg((intptr_t)msgBuf, posX, posY, 255, HighlightColor, 0);
    } else {
        draw_msg((intptr_t)msgBuf, posX, posY, 255, DefaultColor, 0);
    }
}

// utility functions for menu navigation

s32 dx_debug_clamp(s32 v, s32 min, s32 max) {
  const s32 u = v < min ? min : v;
  return u > max ? max : u;
}

s32 dx_debug_wrap(s32 v, s32 min, s32 max) {
  const s32 u = v < min ? v + (max - min + 1) : v;
  return u > max ? u - (max - min + 1) : u;
}

// range from [min, max] with min < max
s32 dx_debug_menu_nav_1D_vertical(s32 cur, s32 min, s32 max, b32 flip) {
    if (NAV_UP) {
        if(flip) {
            cur++;
        } else {
            cur--;
        }
    }
    if (NAV_DOWN) {
        if(flip) {
            cur--;
        } else {
            cur++;
        }
    }
    // wrap
    if (cur < min) {
        cur += (1 + max - min);
    }
    if (cur > max) {
        cur -= (1 + max - min);
    }
    return cur;
}

// range from [min, max] with min < max
s32 dx_debug_menu_nav_1D_horizontal(s32 cur, s32 min, s32 max, b32 flip) {
    if (NAV_LEFT) {
        if(flip) {
            cur++;
        } else {
            cur--;
        }
    }
    if (NAV_RIGHT) {
        if(flip) {
            cur--;
        } else {
            cur++;
        }
    }
    // wrap
    if (cur < min) {
        cur += (1 + max - min);
    }
    if (cur > max) {
        cur -= (1 + max - min);
    }
    return cur;
}

s32 dx_debug_menu_nav_2D(s32 cur, s32 max, s32 nrows) {
    s32 ncols = max / nrows;
    if ((max % nrows) != 0) {
        ncols++;
    }

    if (NAV_UP) {
        cur--;
        if (cur < 0) {
            cur += nrows;
        }
        else if (cur % nrows == nrows - 1) {
            cur += nrows;
        }
        while (cur >= max) {
            cur--;
        }
    }
    if (NAV_DOWN) {
        cur++;
        if (cur >= max) {
            cur = (cur / nrows) * nrows;
        }
        else if (cur % nrows == 0) {
            cur -= nrows;
        }
    }
    if (NAV_LEFT) {
        cur -= nrows;
        if (cur < 0) {
            cur += (nrows * ncols);
            while (cur >= max) {
                cur -= nrows;
            }
        }
    }
    if (NAV_RIGHT) {
        cur += nrows;
        if (cur >= max) {
            cur -= (nrows * ncols);
            while (cur < 0) {
                cur += nrows;
            }
        }
    }
    return cur;
}

// utility functions for number input fields

typedef struct DebugEditableNumber {
    b8 isHex;
    s8 pos;
    s8 size;
    s8 digits[];
} DebugEditableNumber;

void dx_debug_nav_editable_num(DebugEditableNumber* num) {
    s32 max = num->isHex ? 0xF : 9;

    if (num->size > 1) {
        num->pos = dx_debug_menu_nav_1D_horizontal(num->pos, 0, num->size - 1, false);
    }
    num->digits[num->pos] = dx_debug_menu_nav_1D_vertical(num->digits[num->pos], 0, max, true);
}

void dx_debug_draw_editable_num(DebugEditableNumber* num, s32 posX, s32 posY) {
    char* fmt = num->isHex ? "%X" : "%d";
    s32 idx;

    for (idx = 0; idx < num->size; idx++) {
        s32 color = (num->pos == idx) ? HighlightColor : DefaultColor;
        dx_debug_draw_number(num->digits[idx], fmt, color, 255, posX + (7 * idx), posY);
    }
}

s32 dx_debug_get_editable_num(DebugEditableNumber* num) {
    s32 idx;
    s32 out = 0;

    if (num->isHex) {
        for (idx = 0; idx < num->size; idx++) {
            out <<= 4;
            out |= (num->digits[idx] & 0xF);
        }
    } else {
        for (idx = 0; idx < num->size; idx++) {
            out *= 10;
            out += num->digits[idx];
        }
    }

    return out;
}

void dx_debug_set_editable_num(DebugEditableNumber* num, s32 in) {
    s32 idx;

    if (num->isHex) {
        for (idx = num->size - 1; idx >= 0; idx--) {
            num->digits[idx] = (in & 0xF);
            in >>= 4;
        }
    } else {
        for (idx = num->size - 1; idx >= 0; idx--) {
            num->digits[idx] = in % 10;
            in /= 10;
        }
    }
}

// menus

void dx_debug_draw_main_menu();

b32 dx_debug_menu_is_open() {
    return DebugMenuState != DBM_NONE;
}

void dx_debug_exec_full_restore() {
    gPlayerData.curHP = gPlayerData.curMaxHP;
    gPlayerData.curFP = gPlayerData.curMaxFP;
    gPlayerData.starPower = gPlayerData.maxStarPower * SP_PER_BAR;
    sfx_play_sound(SOUND_UNUSED_STAR_SPIRIT_APPEARS);
}

typedef struct DebugMenuEntry {
    char* text;
    void (*onSelect)();
    s32 nextState;
} DebugMenuEntry;

DebugMenuEntry DebugMainMenu[] = {
    { "Full Restore",   dx_debug_exec_full_restore },
    { "Save/Load",      nullptr, DBM_QUICK_SAVE },
    { "Map Select",     nullptr, DBM_SELECT_AREA },
    { "Battle Select",  nullptr, DBM_SELECT_BATTLE },
    { "Set Story Byte", nullptr, DBM_SET_STORY },
    { "Sound Player",   nullptr, DBM_SOUND_PLAYER },
    { "Edit Partners",  nullptr, DBM_EDIT_PARTNERS },
    { "Edit Inventory", nullptr, DBM_EDIT_INVENTORY },
//  { "Edit Memory",    nullptr, DBM_EDIT_MEMORY },
    { "View Collision", nullptr, DBM_VIEW_COLLISION },
    { "Cheats",         nullptr, DBM_CHEAT_MENU },
};
s32 MainMenuPos = 0;

// position of the blue box containing the main menu options
const s32 MainBoxPosX     = MainMenuPosX - BoxOutsetX;
const s32 MainBoxPosY     = MainMenuPosY - BoxOutsetY;
const s32 MainBoxWidth    = 96;
const s32 MainBoxHeight   = ARRAY_COUNT(DebugMainMenu) * RowHeight + 8;

f32 ArrowAnimOffset = 0;
f32 DebugArrowPhase = 0.0f;
#define DEBUG_ARROW_ANIM_RATE 6

void dx_debug_update_banner();
void dx_debug_update_main_menu();
void dx_debug_update_quick_save();
void dx_debug_update_select_area();
void dx_debug_update_select_map();
void dx_debug_update_select_entry();
void dx_debug_update_select_battle();
void dx_debug_update_edit_progress();
void dx_debug_update_sound_player();
void dx_debug_update_select_sound();
void dx_debug_update_edit_partners();
void dx_debug_update_edit_inventory();
void dx_debug_update_edit_items();
void dx_debug_update_edit_items();
void dx_debug_update_edit_items();
void dx_debug_update_edit_gear();
void dx_debug_update_edit_stats();
void dx_debug_update_edit_coins();
void dx_debug_update_edit_star_points();
void dx_debug_update_edit_star_pieces();
void dx_debug_update_view_collision();
void dx_debug_update_cheat_menu();
void dx_debug_update_evt_main();
void dx_debug_update_evt_select();
void dx_debug_update_evt_attached();

void dx_debug_menu_main() {
    s32 initialMenuState = DebugMenuState;

    dx_debug_update_buttons();

    HighlightColor = HELD(BUTTON_R) ? SelectColor : HoverColor;

    DebugArrowPhase += DEBUG_ARROW_ANIM_RATE;
    if (DebugArrowPhase >= 360.0f) {
        DebugArrowPhase -= 360.0f;
    }
    ArrowAnimOffset = cos_deg(DebugArrowPhase);

    dx_debug_update_banner();

    // check input for menu open/close
    if (DebugMenuState == DBM_NONE) {
        if (PRESSED(BUTTON_D_LEFT)) {
            DebugMenuState = DBM_MAIN_MENU;
        }
        if (PRESSED(BUTTON_D_RIGHT)) {
            DebugMenuState = DBM_EVT_MAIN;
        }
    } else if (DebugMenuState == DBM_MAIN_MENU) {
        if (PRESSED(BUTTON_D_LEFT | BUTTON_L)) {
            DebugMenuState = DBM_NONE;
        }
    } else if (DebugMenuState == DBM_EVT_MAIN) {
        if (PRESSED(BUTTON_D_RIGHT | BUTTON_L)) {
            DebugMenuState = DBM_NONE;
        }
    }

    if (DebugMenuState != DBM_NONE) {
        // main menu is always drawn if the debug menu is open at all
        if (DebugMenuState < DBM_EVT_MAIN) {
            dx_debug_draw_main_menu();
        }

        switch (DebugMenuState) {
            case DBM_NONE: // to satisfy compiler
                break;
            case DBM_MAIN_MENU:
                dx_debug_update_main_menu();
                break;
            case DBM_QUICK_SAVE:
                dx_debug_update_quick_save();
                break;
            case DBM_SELECT_AREA:
                dx_debug_update_select_area();
                break;
            case DBM_SELECT_MAP:
                dx_debug_update_select_map();
                break;
            case DBM_SELECT_ENTRY:
                dx_debug_update_select_entry();
                break;
            case DBM_SELECT_BATTLE:
                dx_debug_update_select_battle();
                break;
            case DBM_SET_STORY:
                dx_debug_update_edit_progress();
                break;
            case DBM_SOUND_PLAYER:
                dx_debug_update_sound_player();
                break;
            case DBM_SELECT_SOUND:
                dx_debug_update_select_sound();
                break;
            case DBM_EDIT_PARTNERS:
                dx_debug_update_edit_partners();
                break;
            case DBM_EDIT_INVENTORY:
                dx_debug_update_edit_inventory();
                break;
            case DBM_INV_EDIT_ITEMS:
                dx_debug_update_edit_items();
                break;
            case DBM_INV_EDIT_BADGES:
                dx_debug_update_edit_items();
                break;
            case DBM_INV_EDIT_KEYS:
                dx_debug_update_edit_items();
                break;
            case DBM_INV_EDIT_GEAR:
                dx_debug_update_edit_gear();
                break;
            case DBM_INV_EDIT_STATS:
                dx_debug_update_edit_stats();
                break;
            case DBM_INV_EDIT_COINS:
                dx_debug_update_edit_coins();
                break;
            case DBM_INV_EDIT_STAR_POINTS:
                dx_debug_update_edit_star_points();
                break;
            case DBM_INV_EDIT_STAR_PIECES:
                dx_debug_update_edit_star_pieces();
                break;
            case DBM_EDIT_MEMORY:
                break;
            case DBM_VIEW_COLLISION:
                dx_debug_update_view_collision();
                break;
            case DBM_CHEAT_MENU:
                dx_debug_update_cheat_menu();
                break;
            case DBM_EVT_MAIN:
                dx_debug_update_evt_main();
                break;
            case DBM_EVT_SELECT:
                dx_debug_update_evt_select();
                break;
            case DBM_EVT_ATTACHED:
                dx_debug_update_evt_attached();
                break;
        }
    }

    DebugStateChanged = (initialMenuState != DebugMenuState);
}

void dx_debug_update_main_menu() {
    MainMenuPos = dx_debug_menu_nav_1D_vertical(MainMenuPos, 0, ARRAY_COUNT(DebugMainMenu) - 1, false);
    if (RELEASED(BUTTON_R | BUTTON_D_RIGHT)) {
        if (DebugMainMenu[MainMenuPos].onSelect != nullptr) {
            DebugMainMenu[MainMenuPos].onSelect();
        } else {
            DebugMenuState = DebugMainMenu[MainMenuPos].nextState;
        }
    }
}

void dx_debug_draw_main_menu() {
    s32 idx;

    dx_debug_draw_box(MainBoxPosX, MainBoxPosY, MainBoxWidth, MainBoxHeight, WINDOW_STYLE_4, 192);

    for (idx = 0; idx < ARRAY_COUNT(DebugMainMenu); idx++) {
        s32 color = DefaultColor;
        if (MainMenuPos == idx) {
            color = (DebugMenuState == DBM_MAIN_MENU) ? HighlightColor : HoverColor;
        }
        dx_debug_draw_ascii(DebugMainMenu[idx].text, color, MainMenuPosX, MainMenuPosY + idx * RowHeight);
    }
}

// ----------------------------------------------------------------------------
// quick save
// only restores previous player position on maps with save points, otherwise enters through most recent entry

void dx_debug_exec_quick_save() {
    sfx_play_sound(SOUND_MENU_SHOW_CHOICE);
    gGameStatusPtr->savedPos.x = gPlayerStatusPtr->pos.x;
    gGameStatusPtr->savedPos.y = gPlayerStatusPtr->pos.y;
    gGameStatusPtr->savedPos.z = gPlayerStatusPtr->pos.z;
    fio_save_game(gGameStatusPtr->saveSlot);
    DebugMenuState = DBM_MAIN_MENU;
}

void dx_debug_exec_quick_load() {
    fio_load_game(gGameStatus.saveSlot);
    set_map_transition_effect(TRANSITION_STANDARD);
    set_game_mode(GAME_MODE_ENTER_WORLD);
    DebugMenuState = DBM_MAIN_MENU;
}

DebugMenuEntry DebugQuickSaveMenu[] = {
    { "Cancel", nullptr, DBM_MAIN_MENU },
    { "Quick Save", dx_debug_exec_quick_save },
    { "Quick Load", dx_debug_exec_quick_load },
};
s32 QuickSaveMenuPos = 0;

void dx_debug_update_quick_save() {
    s32 idx;

    // handle input
    QuickSaveMenuPos = dx_debug_menu_nav_1D_vertical(QuickSaveMenuPos, 0, ARRAY_COUNT(DebugQuickSaveMenu) - 1, false);
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    } else if (RELEASED(BUTTON_R)) {
        if (DebugQuickSaveMenu[QuickSaveMenuPos].onSelect != nullptr) {
            DebugQuickSaveMenu[QuickSaveMenuPos].onSelect();
        } else {
            DebugMenuState = DebugQuickSaveMenu[QuickSaveMenuPos].nextState;
        }
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 75, ARRAY_COUNT(DebugQuickSaveMenu) * RowHeight + 8, WINDOW_STYLE_20, 192);

    for (idx = 0; idx < ARRAY_COUNT(DebugQuickSaveMenu); idx++) {
        s32 color = (QuickSaveMenuPos == idx) ? HighlightColor : DefaultColor;
        dx_debug_draw_ascii(DebugQuickSaveMenu[idx].text, color, SubmenuPosX, SubmenuPosY + (idx + 1) * RowHeight);
    }
}

// ----------------------------------------------------------------------------
// map select

s32 SelectAreaMenuPos = 0;
s32 SelectMapMenuPos = 0;
s32 SelectedEntryValue = 0;

const s32 AreaSizeX = 30;
const s32 MapSizeX = 50;

void dx_debug_update_select_area() {
    s32 i, j, idx;
    s32 nrows, ncols;
    s32 numAreas = ARRAY_COUNT(gAreas) - 1;
    s32 prev = SelectAreaMenuPos;

    // select optimal shape for the menu based on numAreas
    // maximum supported size is 9 x 5 (45 areas)

    if (numAreas <= 6) {
        nrows = numAreas;
        ncols = 1;
    } else if (numAreas <= 12) {
        nrows = 6;
        ncols = 2;
    } else if (numAreas <= 18) {
        nrows = 6;
        ncols = 3;
    } else if (numAreas <= 24) {
        nrows = 6;
        ncols = 4;
    } else if (numAreas <= 30) {
        nrows = 6;
        ncols = 5;
    } else if (numAreas <= 35) {
        nrows = 7;
        ncols = 5;
    } else if (numAreas <= 40) {
        nrows = 8;
        ncols = 5;
    } else {
        nrows = 9;
        ncols = 5;
    }

    // handle input

    SelectAreaMenuPos = dx_debug_menu_nav_2D(SelectAreaMenuPos, numAreas, nrows);
    if (SelectAreaMenuPos != prev) {
        SelectMapMenuPos = 0;
        SelectedEntryValue = 0;
    }
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    } else if (RELEASED(BUTTON_R)) {
        DebugMenuState = DBM_SELECT_MAP;
    }

    // draw

    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, AreaSizeX * ncols + 8, RowHeight * nrows + 8, WINDOW_STYLE_20, 192);

    idx = 0;
    for (i = 0; i < ncols; i++) {
        for (j = 0; j < nrows; j++) {
            if (idx < numAreas) {
                s32 color = (SelectAreaMenuPos == idx) ? HighlightColor : DefaultColor;
                char* name = &(gAreas[idx].id)[5]; // trim "area_" prefix
                dx_debug_draw_ascii(name, color, SubmenuPosX + i * AreaSizeX, SubmenuPosY + (j + 1) * RowHeight);
            }
            idx++;
        }
    }
}

void dx_debug_update_select_map() {
    s32 i, j, idx;
    s32 numRows, numCols;
    s32 curCol, maxCol, startCol;
    MapConfig* maps = gAreas[SelectAreaMenuPos].maps;
    s32 numMaps = gAreas[SelectAreaMenuPos].mapCount;
    s32 prev = SelectMapMenuPos;

    // select optimal shape for the menu based on numMaps

    if (numMaps <= 6) {
        numRows = numMaps;
        numCols = 1;
    } else if (numMaps <= 12) {
        numRows = 6;
        numCols = 2;
    } else {
        numRows = 6;
        numCols = 3;
    }

    // handle input

    SelectMapMenuPos = dx_debug_menu_nav_2D(SelectMapMenuPos, numMaps, numRows);
    if (SelectMapMenuPos != prev) {
        SelectedEntryValue = 0;
    }
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_SELECT_AREA;
    } else if (RELEASED(BUTTON_R)) {
        DebugMenuState = DBM_SELECT_ENTRY;
    }

    // draw

    curCol = SelectMapMenuPos / numRows;
    maxCol = numMaps / numRows;

    if (maxCol > 2) {
        dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, MapSizeX * numCols + 8, RowHeight * (numRows + 1) + 8, WINDOW_STYLE_20, 192);
    } else {
        dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, MapSizeX * numCols + 8, RowHeight * numRows + 8, WINDOW_STYLE_20, 192);
    }

    if (maxCol < 3) {
        startCol = 0;
    } else if (curCol == 0) {
        startCol = 0;
    } else if (curCol == maxCol) {
        startCol = maxCol - 2;
    } else {
        startCol = curCol - 1;
    }

    idx = numRows * startCol;
    for (i = startCol; i <= startCol + 2; i++) {
        for (j = 0; j < numRows; j++) {
            if (idx < numMaps) {
                s32 color = (SelectMapMenuPos == idx) ? HighlightColor : DefaultColor;
                char* name = maps[idx].id;
                dx_debug_draw_ascii(name, color, SubmenuPosX + (i - startCol) * MapSizeX, SubmenuPosY + (j + 1) * RowHeight);
            }
            idx++;
        }
    }

    if (maxCol > 2) {
        // left arrow
        if (curCol > 1) {
            char msgLeftArrow[] = {
                MSG_CHAR_LEFT, MSG_CHAR_READ_END
            };
            draw_msg((intptr_t)msgLeftArrow, SubmenuPosX - 2 - round(3.0f * ArrowAnimOffset), SubmenuPosY + 104, 255, DefaultColor, 0);
        }
        // right arrow
        if (curCol < maxCol - 1) {
            char msgRightArrow[] = {
                MSG_CHAR_RIGHT, MSG_CHAR_READ_END
            };
            draw_msg((intptr_t)msgRightArrow, SubmenuPosX + 128 + round(3.0f * ArrowAnimOffset), SubmenuPosY + 104, 255, DefaultColor, 0);
        }
    }
}

void dx_debug_update_select_entry() {
    s32 idx;
    MapConfig map = gAreas[SelectAreaMenuPos].maps[SelectMapMenuPos];

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_SELECT_MAP;
    } else if (RELEASED(BUTTON_R)) {
        gGameStatusPtr->areaID = SelectAreaMenuPos;
        gGameStatusPtr->mapID = SelectMapMenuPos;
        gGameStatusPtr->entryID = SelectedEntryValue;
        set_map_transition_effect(TRANSITION_STANDARD);
        set_game_mode(GAME_MODE_CHANGE_MAP);
        play_ambient_sounds(AMBIENT_SILENCE, 1);
        DebugMenuState = DBM_NONE;
    }

    if (NAV_UP) {
        SelectedEntryValue++;
    }
    if (NAV_DOWN) {
        SelectedEntryValue--;
    }

    if (SelectedEntryValue < 0) {
        SelectedEntryValue = 0;
    }
    if (SelectedEntryValue > 0x7F) {
        SelectedEntryValue = 0x7F;
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 80, 2 * RowHeight + 8, WINDOW_STYLE_20, 192);

    for (idx = 0; idx < ARRAY_COUNT(DebugQuickSaveMenu); idx++) {
        char fmtBuf[16];
        dx_debug_draw_ascii(map.id, DefaultColor, SubmenuPosX, SubmenuPosY + RowHeight);
        dx_debug_draw_ascii("Entry:", DefaultColor, SubmenuPosX, SubmenuPosY + 2 * RowHeight);
        sprintf(fmtBuf, "%2lX", SelectedEntryValue);
        dx_debug_draw_ascii(fmtBuf, HighlightColor, SubmenuPosX + 40, SubmenuPosY + 2 * RowHeight);
    }
}

// ----------------------------------------------------------------------------
// battle select

enum DebugBattleValues {
    DEBUG_BATTLE_AREA_TENS,
    DEBUG_BATTLE_AREA_ONES,
    DEBUG_BATTLE_FORMATION_TENS,
    DEBUG_BATTLE_FORMATION_ONES,
    DEBUG_BATTLE_STAGE,
};

s32 DebugBattleNum[] = {
    [DEBUG_BATTLE_AREA_TENS]        0,
    [DEBUG_BATTLE_AREA_ONES]        0,
    [DEBUG_BATTLE_FORMATION_TENS]   0,
    [DEBUG_BATTLE_FORMATION_ONES]   0,
    [DEBUG_BATTLE_STAGE]            -1,
};

s32 BattleDigitOffsets[] = {
    [DEBUG_BATTLE_AREA_TENS]        10,
    [DEBUG_BATTLE_AREA_ONES]        17,
    [DEBUG_BATTLE_FORMATION_TENS]   35,
    [DEBUG_BATTLE_FORMATION_ONES]   42,
    [DEBUG_BATTLE_STAGE]            63,
};

s32 DebugBattleColumn = 0;

EnemyDrops DebugDummyDrops = NO_DROPS;

Enemy DebugDummyEnemy = {
    .npcID = DX_DEBUG_DUMMY_ID,
    .drops = &DebugDummyDrops,
};

Encounter DebugDummyEncounter = {
    .encounterID = DX_DEBUG_DUMMY_ID,
    .enemy = { &DebugDummyEnemy },
    .count = 0,
    .battle = 0,
    .stage = 0,
};

void dx_debug_begin_battle_with_IDs(s16 battle, s16 stage) {
    EncounterStatus* es = &gCurrentEncounter;

    DebugDummyEncounter.battle = battle;
    DebugDummyEncounter.stage = stage;

    es->curEncounter = &DebugDummyEncounter;
    es->curEnemy = &DebugDummyEnemy;
    es->hitType = ENCOUNTER_TRIGGER_NONE;
    es->firstStrikeType = FIRST_STRIKE_NONE;
    es->forbidFleeing = false;
    es->scriptedBattle = true;
    es->songID = -1;
    es->unk_18 = -1;
    es->fadeOutAmount = 0;
    es->substateDelay = 0;

    disable_player_input();
    partner_disable_input();

    gEncounterState = ENCOUNTER_STATE_PRE_BATTLE;
    gEncounterSubState = ENCOUNTER_SUBSTATE_PRE_BATTLE_INIT;
    EncounterStateChanged = true;
}

void dx_debug_begin_battle() {
    s16 battle = (DebugBattleNum[DEBUG_BATTLE_AREA_TENS] & 0xF) << 12
        | (DebugBattleNum[DEBUG_BATTLE_AREA_ONES] & 0xF) << 8
        | (DebugBattleNum[DEBUG_BATTLE_FORMATION_TENS] & 0xF) << 4
        | (DebugBattleNum[DEBUG_BATTLE_FORMATION_ONES] & 0xF);
    s16 stage = DebugBattleNum[DEBUG_BATTLE_STAGE] & 0xFFFF;

    dx_debug_begin_battle_with_IDs(battle, stage);
}

void dx_debug_update_select_battle() {
    s32 idx;
    s32 maxAreaTens = ARRAY_COUNT(gBattleAreas) >> 4;

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    } else if (RELEASED(BUTTON_R)) {
        dx_debug_begin_battle();
        DebugMenuState = DBM_NONE;
    }

    DebugBattleColumn = dx_debug_menu_nav_1D_horizontal(DebugBattleColumn, 0, 4, false);
    if (NAV_UP) {
        s32 value = DebugBattleNum[DebugBattleColumn] + 1;
        if (DebugBattleColumn == DEBUG_BATTLE_STAGE) {
            value = dx_debug_clamp(value, -1, 0x7F);
        } else if (DebugBattleColumn == DEBUG_BATTLE_AREA_TENS) {
            value = dx_debug_wrap(value, 0, maxAreaTens);
        } else {
            value = dx_debug_wrap(value, 0, 0xF);
        }
        DebugBattleNum[DebugBattleColumn] = value;
    }
    if (NAV_DOWN) {
        s32 value = DebugBattleNum[DebugBattleColumn] - 1;
        if (DebugBattleColumn == DEBUG_BATTLE_STAGE) {
            value = dx_debug_clamp(value, -1, 0x7F);
        } else if (DebugBattleColumn == DEBUG_BATTLE_AREA_TENS) {
            value = dx_debug_wrap(value, 0, maxAreaTens);
        } else {
            value = dx_debug_wrap(value, 0, 0xF);
        }
        DebugBattleNum[DebugBattleColumn] = value;
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 104, 2 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Start Battle:", DefaultColor, SubmenuPosX, SubmenuPosY + 1 * RowHeight);
    dx_debug_draw_ascii("-", DefaultColor, SubmenuPosX + 26, SubmenuPosY + 2 * RowHeight);
    dx_debug_draw_ascii("(", DefaultColor, SubmenuPosX + 55, SubmenuPosY + 2 * RowHeight);
    dx_debug_draw_ascii(")", DefaultColor, SubmenuPosX + 77, SubmenuPosY + 2 * RowHeight);

    for (idx = 0; idx < 5; idx++) {
        s32 color = (DebugBattleColumn == idx) ? HighlightColor : DefaultColor;
        s32 offset = BattleDigitOffsets[idx];
        char* fmt = (idx == 4) ? "%02X" : "%X";

        dx_debug_draw_number(DebugBattleNum[idx] & 0xFF, fmt, color, 255, SubmenuPosX + offset, SubmenuPosY + 2 * RowHeight);
    }
}

// ----------------------------------------------------------------------------
// set story byte

DebugEditableNumber DebugStoryProgress = {
    .isHex = true,
    .digits = { 0, 0 },
    .size = 2,
    .pos = 0,
};

void dx_debug_update_edit_progress() {
    if (DebugStateChanged) {
        s32 val = evt_get_variable(nullptr, GB_StoryProgress);
        dx_debug_set_editable_num(&DebugStoryProgress, val);
    }

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    } else if (RELEASED(BUTTON_R)) {
        s32 val = dx_debug_get_editable_num(&DebugStoryProgress);
        evt_set_variable(nullptr, GB_StoryProgress, val);
        sfx_play_sound(SOUND_MENU_BADGE_EQUIP);
    }

    dx_debug_nav_editable_num(&DebugStoryProgress);

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 104, 2 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Set Progress:", DefaultColor, SubmenuPosX, SubmenuPosY + RowHeight);
    dx_debug_draw_editable_num(&DebugStoryProgress, SubmenuPosX + 35, SubmenuPosY + 2 * RowHeight);
}

// ----------------------------------------------------------------------------
// sound player

DebugMenuEntry DebugSoundPlayerMenu[] = {
    { "Play Sound", nullptr, DBM_SELECT_SOUND },
    { "Stop Sound", nullptr, DBM_SELECT_SOUND },
};
s32 SoundPlayerMenuPos = 0;

void dx_debug_draw_sound_player(b32 activeMenu) {
    s32 idx;

    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 75, ARRAY_COUNT(DebugSoundPlayerMenu) * RowHeight + 8, WINDOW_STYLE_20, 192);

    for (idx = 0; idx < ARRAY_COUNT(DebugSoundPlayerMenu); idx++) {
        s32 color;
        if (activeMenu) {
            color = (SoundPlayerMenuPos == idx) ? HighlightColor : DefaultColor;
        } else {
            color = (SoundPlayerMenuPos == idx) ? HoverColor : DefaultColor;
        }
        dx_debug_draw_ascii(DebugSoundPlayerMenu[idx].text, color, SubmenuPosX, SubmenuPosY + (idx + 1) * RowHeight);
    }
}

void dx_debug_update_sound_player() {
    // handle input
    SoundPlayerMenuPos = dx_debug_menu_nav_1D_vertical(SoundPlayerMenuPos, 0, ARRAY_COUNT(DebugSoundPlayerMenu) - 1, false);
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    } else if (RELEASED(BUTTON_R)) {
        DebugMenuState = DBM_SELECT_SOUND;
    }

    dx_debug_draw_sound_player(true);
}

DebugEditableNumber DebugSoundID = {
    .isHex = true,
    .digits = { 0, 0, 0, 0 },
    .size = 4,
    .pos = 0,
};

void dx_debug_update_select_sound() {
    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_SOUND_PLAYER;
    } else if (RELEASED(BUTTON_R)) {
        if (SoundPlayerMenuPos == 0) {
            sfx_play_sound(dx_debug_get_editable_num(&DebugSoundID) & 0xFFFF);
        } else {
            sfx_stop_sound(dx_debug_get_editable_num(&DebugSoundID) & 0xFFFF);
        }
    }

    dx_debug_nav_editable_num(&DebugSoundID);

    dx_debug_draw_sound_player(false);
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + (4 * RowHeight), 75, 2 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Sound ID:", DefaultColor, SubmenuPosX, SubmenuPosY + 4 * RowHeight);
    dx_debug_draw_editable_num(&DebugSoundID, SubmenuPosX, SubmenuPosY + 5 * RowHeight);
}

// ----------------------------------------------------------------------------
// edit partners

s8 DebugPartnerLevels[ARRAY_COUNT(gPlayerData.partners)];
s32 SelectPartnerMenuPos = 1;

void dx_debug_update_edit_partners() {
    s32 idx;

    if (DebugStateChanged) {
        for (idx = 1; idx < ARRAY_COUNT(gPlayerData.partners); idx++) {
            DebugPartnerLevels[idx] = gPlayerData.partners[idx].enabled + gPlayerData.partners[idx].level - 1;
        }
    }

    // handle input
    SelectPartnerMenuPos = dx_debug_menu_nav_1D_vertical(SelectPartnerMenuPos, 1, ARRAY_COUNT(gPlayerData.partners) - 1, false);
    DebugPartnerLevels[SelectPartnerMenuPos] = dx_debug_menu_nav_1D_horizontal(DebugPartnerLevels[SelectPartnerMenuPos], -1, 2, false);
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    } else if (RELEASED(BUTTON_R)) {
        for (idx = 1; idx < ARRAY_COUNT(gPlayerData.partners); idx++) {
            s32 val = DebugPartnerLevels[idx];
            if (val >= 0) {
                gPlayerData.partners[idx].enabled = true;
                gPlayerData.partners[idx].level = val;
            } else {
                gPlayerData.partners[idx].enabled = false;
                gPlayerData.partners[idx].level = 0;
            }
        }
        if (DebugPartnerLevels[SelectPartnerMenuPos] >= 0) {
            switch_to_partner(SelectPartnerMenuPos);
        }
        sfx_play_sound(SOUND_MENU_BADGE_EQUIP);
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY, 120, 14 * 11 + 8, WINDOW_STYLE_20, 192);

    for (idx = 1; idx < ARRAY_COUNT(gPlayerData.partners); idx++) {
        b32 isSelected = (SelectPartnerMenuPos == idx);
        s32 color = isSelected ? HighlightColor : DefaultColor;
        s32 posY = SubmenuPosY + (idx - 1) * 14;
        s32 level = DebugPartnerLevels[idx];
        s32 alpha = (isSelected || level >= 0) ? 254 : 120;

        if (level < 0) {
            dx_debug_draw_number(level, "%d", color, alpha, SubmenuPosX - 3, posY);
        } else {
            dx_debug_draw_number(level, "%d", color, alpha, SubmenuPosX + 3, posY);
        }

        dx_debug_draw_msg(gPartnerPopupProperties[idx].nameMsg, color, alpha, SubmenuPosX + 15, posY);

        if (level == 1) {
            char msg[] = { MSG_CHAR_CIRCLE, MSG_CHAR_READ_END };
            draw_msg((intptr_t)msg, SubmenuPosX + 82, posY - 1, 255, MSG_PAL_BLUE, 0);
        } else if (level == 2) {
            char msg[] = { MSG_CHAR_CIRCLE, MSG_CHAR_CIRCLE, MSG_CHAR_READ_END };
            draw_msg((intptr_t)msg, SubmenuPosX + 82, posY - 1, 255, MSG_PAL_BLUE, 0);
        }
    }
}

// ----------------------------------------------------------------------------
// edit inventory

DebugMenuEntry DebugInventoryMenu[] = {
    { "Items", nullptr, DBM_INV_EDIT_ITEMS },
    { "Badges", nullptr, DBM_INV_EDIT_BADGES },
    { "Key Items", nullptr, DBM_INV_EDIT_KEYS },
    { "Equipment", nullptr, DBM_INV_EDIT_GEAR },
    { "Stats", nullptr, DBM_INV_EDIT_STATS },
    { "Coins", nullptr, DBM_INV_EDIT_COINS },
    { "Star Points", nullptr, DBM_INV_EDIT_STAR_POINTS },
    { "Star Pieces", nullptr, DBM_INV_EDIT_STAR_PIECES },
};
s32 InventoryMenuPos = 0;

void dx_debug_update_edit_inventory() {
    s32 idx;

    // handle input
    InventoryMenuPos = dx_debug_menu_nav_1D_vertical(InventoryMenuPos, 0, ARRAY_COUNT(DebugInventoryMenu) - 1, false);
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    } else if (RELEASED(BUTTON_R)) {
        if (DebugInventoryMenu[InventoryMenuPos].onSelect != nullptr) {
            DebugInventoryMenu[InventoryMenuPos].onSelect();
        } else {
            DebugMenuState = DebugInventoryMenu[InventoryMenuPos].nextState;
        }
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 75, ARRAY_COUNT(DebugInventoryMenu) * RowHeight + 8, WINDOW_STYLE_20, 192);

    for (idx = 0; idx < ARRAY_COUNT(DebugInventoryMenu); idx++) {
        s32 color = (InventoryMenuPos == idx) ? HighlightColor : DefaultColor;
        dx_debug_draw_ascii(DebugInventoryMenu[idx].text, color, SubmenuPosX, SubmenuPosY + (idx + 1) * RowHeight);
    }
}

b32 DebugEditingItem = false;

#define _MAX_INV_SIZE(a,b,c) MAX(MAX(ARRAY_COUNT(a), ARRAY_COUNT(b)), ARRAY_COUNT(c))
s8 DebugItemDigits[_MAX_INV_SIZE(gPlayerData.invItems, gPlayerData.keyItems, gPlayerData.badges)][3];

typedef struct DebugItemsMenu {
    s16 pos;
    s16 startPos;
    s8 col;
} DebugItemsMenu;

DebugItemsMenu DebugItems = {
    .pos = 0,
    .startPos = 0,
    .col = 0,
};

DebugItemsMenu DebugKeys = {
    .pos = 0,
    .startPos = 0,
    .col = 0,
};

DebugItemsMenu DebugBadges = {
    .pos = 0,
    .startPos = 0,
    .col = 0,
};

void dx_debug_set_item_id(s32 idx, s16 itemID) {
    s32 j;

    for (j = 2; j >= 0; j--) {
        DebugItemDigits[idx][j] = (itemID & 0xF);
        itemID >>= 4;
    }
}

s16 dx_debug_get_item_id(s32 idx) {
    s32 j;
    s16 val = 0;

    for (j = 0; j < 3; j++) {
        val <<= 4;
        val |= (DebugItemDigits[idx][j] & 0xF);
    }
    return val;
}

void dx_debug_update_edit_items() {
    DebugItemsMenu* menu;
    s16* invItems;
    s32 invSize;
    s32 i;

    switch (DebugMenuState) {
        case DBM_INV_EDIT_ITEMS:
            menu = &DebugItems;
            invItems = gPlayerData.invItems;
            invSize = ARRAY_COUNT(gPlayerData.invItems);
            break;
        case DBM_INV_EDIT_KEYS:
            menu = &DebugKeys;
            invItems = gPlayerData.keyItems;
            invSize = ARRAY_COUNT(gPlayerData.keyItems);
            break;
        case DBM_INV_EDIT_BADGES:
            menu = &DebugBadges;
            invItems = gPlayerData.badges;
            invSize = ARRAY_COUNT(gPlayerData.badges);
            break;
        default:
            PANIC_MSG("invalid debug menu state");
    }

    if (DebugStateChanged) {
        for (i = 0; i < invSize; i++) {
            dx_debug_set_item_id(i, invItems[i]);
        }
    }

    if (RELEASED(BUTTON_L)) {
        if (DebugEditingItem) {
            DebugEditingItem = false;
        } else {
            DebugMenuState = DBM_EDIT_INVENTORY;
        }
    } else if (RELEASED(BUTTON_R)) {
        if (!DebugEditingItem) {
            DebugEditingItem = true;
        } else {
            for (i = 0; i < invSize; i++) {
                invItems[i] = dx_debug_get_item_id(i);
            }
            sfx_play_sound(SOUND_MENU_BADGE_EQUIP);
        }
    }

    if (DebugEditingItem) {
        s32 digit;
        menu->col = dx_debug_menu_nav_1D_horizontal(menu->col, 0, 2, false);
        digit = DebugItemDigits[menu->pos][menu->col];
        digit = dx_debug_menu_nav_1D_vertical(digit, 0, 0xF, true);
        DebugItemDigits[menu->pos][menu->col] = digit;
    } else {
        if (NAV_UP) {
            menu->pos--;
            if (menu->pos < 0) {
                menu->pos = invSize - 1;
                menu->startPos = menu->pos - 9;
            } else {
                menu->startPos = MIN(menu->startPos, menu->pos);
            }
        }
        if (NAV_DOWN) {
            menu->pos++;
            if (menu->pos >= invSize) {
                menu->pos = 0;
                menu->startPos = 0;
            } else {
                menu->startPos = MAX(menu->startPos, menu->pos - 9);
            }
        }
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY, 160, 10 * RowHeight + 8, WINDOW_STYLE_20, 192);

    for (i = menu->startPos; i <= menu->startPos + 9; i++) {
        s32 posY = SubmenuPosY + (i - menu->startPos) * RowHeight;
        s32 itemID = dx_debug_get_item_id(i);
        b32 isSelectedRow = (menu->pos == i);

        if (DebugEditingItem) {
            dx_debug_draw_editable_number(i, "%02X", -1, false, SubmenuPosX, posY);
            dx_debug_draw_editable_number(itemID, "%03X", menu->col, isSelectedRow, SubmenuPosX + 20, posY);
        } else {
            dx_debug_draw_editable_number(i, "%02X", -1, isSelectedRow, SubmenuPosX, posY);
            dx_debug_draw_editable_number(itemID, "%03X", -1, false, SubmenuPosX + 20, posY);
        }

        s32 itemMsg = MSG_NONE;
        if (itemID > 0 && itemID < NUM_ITEMS) {
            itemMsg = gItemTable[itemID].nameMsg;
        }
        if (itemMsg != MSG_NONE) {
            dx_debug_draw_msg(itemMsg, DefaultColor, 255, SubmenuPosX + 50, posY);
        } else {
            char msgBuf[] = {
                MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SIZE, 12, 12,
                MSG_CHAR_LOWER_E, MSG_CHAR_LOWER_M, MSG_CHAR_LOWER_P, MSG_CHAR_LOWER_T, MSG_CHAR_LOWER_Y,
                MSG_CHAR_READ_END,
            };
            draw_msg((intptr_t)msgBuf, SubmenuPosX + 50, posY, 255, DefaultColor, 0);
        }
    }

    // up arrow
    if (menu->startPos > 0) {
        char msgArrow[] = {
            MSG_CHAR_UP, MSG_CHAR_READ_END
        };
        draw_msg((intptr_t)msgArrow, SubmenuPosX + 132, SubmenuPosY + round(3.0f * ArrowAnimOffset), 255, DefaultColor, 0);
    }
    // down arrow
    if (menu->startPos + 10 < invSize) {
        char msgArrow[] = {
            MSG_CHAR_DOWN, MSG_CHAR_READ_END
        };
        draw_msg((intptr_t)msgArrow, SubmenuPosX + 132, SubmenuPosY + 134 - round(3.0f * ArrowAnimOffset), 255, DefaultColor, 0);
    }
}

enum {
    DEBUG_GEAR_BOOTS,
    DEBUG_GEAR_HAMMER,
    DEBUG_GEAR_LUCKY_STAR,
    DEBUG_GEAR_STAR_BEAM,
};

s32 DebugGearValues[] = {
    [DEBUG_GEAR_BOOTS]          0,
    [DEBUG_GEAR_HAMMER]         0,
    [DEBUG_GEAR_LUCKY_STAR]     0,
    [DEBUG_GEAR_STAR_BEAM]      0,
};
s32 DebugGearPos = 0;

void dx_debug_update_edit_gear() {
    s32 idx;
    s32 dx;

    if (DebugStateChanged) {
        DebugGearValues[DEBUG_GEAR_BOOTS] = gPlayerData.bootsLevel;
        DebugGearValues[DEBUG_GEAR_HAMMER] = gPlayerData.hammerLevel;
        DebugGearValues[DEBUG_GEAR_LUCKY_STAR] = gPlayerData.hasActionCommands;
        DebugGearValues[DEBUG_GEAR_STAR_BEAM] = gPlayerData.starBeamLevel;
    }

    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_EDIT_INVENTORY;
    } else if (RELEASED(BUTTON_R)) {
        gPlayerData.bootsLevel = DebugGearValues[DEBUG_GEAR_BOOTS];
        gPlayerData.hammerLevel = DebugGearValues[DEBUG_GEAR_HAMMER];
        gPlayerData.hasActionCommands = DebugGearValues[DEBUG_GEAR_LUCKY_STAR];
        gPlayerData.starBeamLevel = DebugGearValues[DEBUG_GEAR_STAR_BEAM];

        if (gPlayerData.hasActionCommands && !has_item(ITEM_LUCKY_STAR)) {
            add_item(ITEM_LUCKY_STAR);
        }
        if (!gPlayerData.hasActionCommands && has_item(ITEM_LUCKY_STAR)) {
            remove_item(ITEM_LUCKY_STAR);
        }

        sfx_play_sound(SOUND_MENU_BADGE_EQUIP);
    }

    DebugGearPos = dx_debug_menu_nav_1D_vertical(DebugGearPos, 0, ARRAY_COUNT(DebugGearValues) - 1, false);

    dx = 0;
    if (NAV_RIGHT) {
        dx++;
    }
    if (NAV_LEFT) {
        dx--;
    }
    if (dx != 0) {
        s32 min = 0;
        s32 max = 0;

        switch (DebugGearPos) {
            case DEBUG_GEAR_BOOTS:
                min = -1;
                max = 2;
                break;
            case DEBUG_GEAR_HAMMER:
                min = -1;
                max = 2;
                break;
            case DEBUG_GEAR_LUCKY_STAR:
                min = 0;
                max = 1;
                break;
            case DEBUG_GEAR_STAR_BEAM:
                min = 0;
                max = 2;
                break;
        }

        DebugGearValues[DebugGearPos] = dx_debug_clamp(DebugGearValues[DebugGearPos] + dx, min, max);
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 95, 5 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Gear:", DefaultColor, SubmenuPosX, SubmenuPosY + RowHeight);
    dx_debug_draw_ascii("Boots", DefaultColor, SubmenuPosX, SubmenuPosY + 2 * RowHeight);
    dx_debug_draw_ascii("Hammer", DefaultColor, SubmenuPosX, SubmenuPosY + 3 * RowHeight);
    dx_debug_draw_ascii("Lucky Star", DefaultColor, SubmenuPosX, SubmenuPosY + 4 * RowHeight);
    dx_debug_draw_ascii("Star Beam", DefaultColor, SubmenuPosX, SubmenuPosY + 5 * RowHeight);

    for (idx = 0; idx < ARRAY_COUNT(DebugGearValues); idx++) {
        s32 color = (DebugGearPos == idx) ? HighlightColor : DefaultColor;
        dx_debug_draw_number(DebugGearValues[idx], "%2d", color, 255, SubmenuPosX + 63, SubmenuPosY + (idx + 2) * RowHeight);
    }
}

enum {
    DEBUG_STAT_HP,
    DEBUG_STAT_FP,
    DEBUG_STAT_BP,
    DEBUG_STAT_LEVEL,
    DEBUG_STAT_SPIRITS,
};

s32 DebugStatValues[] = {
    [DEBUG_STAT_HP]         0,
    [DEBUG_STAT_FP]         0,
    [DEBUG_STAT_BP]         0,
    [DEBUG_STAT_LEVEL]      0,
    [DEBUG_STAT_SPIRITS]    0,
};
s32 DebugStatPos = 0;

void dx_debug_update_edit_stats() {
    s32 idx;
    s32 val, dx;

    if (DebugStateChanged) {
        DebugStatValues[DEBUG_STAT_HP] = gPlayerData.hardMaxHP;
        DebugStatValues[DEBUG_STAT_FP] = gPlayerData.hardMaxFP;
        DebugStatValues[DEBUG_STAT_BP] = gPlayerData.maxBP;
        DebugStatValues[DEBUG_STAT_LEVEL] = gPlayerData.level;
        DebugStatValues[DEBUG_STAT_SPIRITS] = gPlayerData.maxStarPower;
    }

    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_EDIT_INVENTORY;
    } else if (RELEASED(BUTTON_R)) {
        gPlayerData.curHP = gPlayerData.curMaxHP = gPlayerData.hardMaxHP = DebugStatValues[DEBUG_STAT_HP];
        gPlayerData.curFP = gPlayerData.curMaxFP = gPlayerData.hardMaxFP = DebugStatValues[DEBUG_STAT_FP];
        gPlayerData.maxBP = DebugStatValues[DEBUG_STAT_BP];
        gPlayerData.level = DebugStatValues[DEBUG_STAT_LEVEL];
        gPlayerData.maxStarPower = DebugStatValues[DEBUG_STAT_SPIRITS];
        gPlayerData.starPower = gPlayerData.maxStarPower * SP_PER_BAR;
        sfx_play_sound(SOUND_MENU_BADGE_EQUIP);
    }

    DebugStatPos = dx_debug_menu_nav_1D_vertical(DebugStatPos, 0, ARRAY_COUNT(DebugStatValues) - 1, false);

    dx = 0;
    if (NAV_RIGHT) {
        dx++;
    }
    if (NAV_LEFT) {
        dx--;
    }
    if (dx != 0) {
        switch (DebugStatPos) {
            case DEBUG_STAT_HP:
                val = DebugStatValues[DEBUG_STAT_HP] + 5 * dx;
                DebugStatValues[DEBUG_STAT_HP] = dx_debug_clamp(val, 5, 50);
                break;
            case DEBUG_STAT_FP:
                val = DebugStatValues[DEBUG_STAT_FP] + 5 * dx;
                DebugStatValues[DEBUG_STAT_FP] = dx_debug_clamp(val, 0, 50);
                break;
            case DEBUG_STAT_BP:
                val = DebugStatValues[DEBUG_STAT_BP] + 3 * dx;
                DebugStatValues[DEBUG_STAT_BP] = dx_debug_clamp(val, 3, 30);
                break;
            case DEBUG_STAT_LEVEL:
                val = DebugStatValues[DEBUG_STAT_LEVEL] + dx;
                DebugStatValues[DEBUG_STAT_LEVEL] = dx_debug_clamp(val, 1, 27);
                break;
            case DEBUG_STAT_SPIRITS:
                val = DebugStatValues[DEBUG_STAT_SPIRITS] + dx;
                DebugStatValues[DEBUG_STAT_SPIRITS] = dx_debug_clamp(val, 0, 7);
                break;
        }
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 88, 6 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Stats:", DefaultColor, SubmenuPosX, SubmenuPosY + RowHeight);
    dx_debug_draw_ascii("Max HP", DefaultColor, SubmenuPosX, SubmenuPosY + 2 * RowHeight);
    dx_debug_draw_ascii("Max FP", DefaultColor, SubmenuPosX, SubmenuPosY + 3 * RowHeight);
    dx_debug_draw_ascii("Max BP", DefaultColor, SubmenuPosX, SubmenuPosY + 4 * RowHeight);
    dx_debug_draw_ascii("Level", DefaultColor, SubmenuPosX, SubmenuPosY + 5 * RowHeight);
    dx_debug_draw_ascii("Spirits", DefaultColor, SubmenuPosX, SubmenuPosY + 6 * RowHeight);

    for (idx = 0; idx < ARRAY_COUNT(DebugStatValues); idx++) {
        s32 color = (DebugStatPos == idx) ? HighlightColor : DefaultColor;
        dx_debug_draw_number(DebugStatValues[idx], "%2d", color, 255, SubmenuPosX + 55, SubmenuPosY + (idx + 2) * RowHeight);
    }
}

DebugEditableNumber DebugCoins = {
    .isHex = false,
    .digits = { 0, 0, 0 },
    .size = 3,
    .pos = 0,
};

void dx_debug_update_edit_coins() {
    if (DebugStateChanged) {
        dx_debug_set_editable_num(&DebugCoins, gPlayerData.coins);
    }

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_EDIT_INVENTORY;
    } else if (RELEASED(BUTTON_R)) {
        gPlayerData.coins = dx_debug_get_editable_num(&DebugCoins);
        open_status_bar_quickly();
        sfx_play_sound(SOUND_COIN_PICKUP);
    }
    dx_debug_nav_editable_num(&DebugCoins);

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 50, 2 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Coins:", DefaultColor, SubmenuPosX, SubmenuPosY + RowHeight);
    dx_debug_draw_editable_num(&DebugCoins, SubmenuPosX, SubmenuPosY + 2 * RowHeight);
}

DebugEditableNumber DebugStarPoints = {
    .isHex = false,
    .digits = { 0, 0 },
    .size = 2,
    .pos = 0,
};

void dx_debug_update_edit_star_points() {
    if (DebugStateChanged) {
        dx_debug_set_editable_num(&DebugStarPoints, gPlayerData.starPoints);
    }

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_EDIT_INVENTORY;
    } else if (RELEASED(BUTTON_R)) {
        gPlayerData.starPoints = dx_debug_get_editable_num(&DebugStarPoints);
        open_status_bar_quickly();
        sfx_play_sound(SOUND_STAR_POINT_PICKUP);
    }
    dx_debug_nav_editable_num(&DebugStarPoints);

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 86, 2 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Star Points:", DefaultColor, SubmenuPosX, SubmenuPosY + RowHeight);
    dx_debug_draw_editable_num(&DebugStarPoints, SubmenuPosX, SubmenuPosY + 2 * RowHeight);
}

DebugEditableNumber DebugStarPieces = {
    .isHex = false,
    .digits = { 0, 0, 0 },
    .size = 3,
    .pos = 0,
};

void dx_debug_update_edit_star_pieces() {
    if (DebugStateChanged) {
        dx_debug_set_editable_num(&DebugStarPieces, gPlayerData.starPieces);
    }

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_EDIT_INVENTORY;
    } else if (RELEASED(BUTTON_R)) {
        gPlayerData.starPieces = dx_debug_get_editable_num(&DebugStarPieces);
        open_status_bar_quickly();
        sfx_play_sound(SOUND_STAR_PIECE_BOUNCE);
    }
    dx_debug_nav_editable_num(&DebugStarPieces);

    // clamp maximum
    if (dx_debug_get_editable_num(&DebugStarPieces) > 255) {
        dx_debug_set_editable_num(&DebugStarPieces, 255);
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 86, 2 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Star Pieces:", DefaultColor, SubmenuPosX, SubmenuPosY + RowHeight);
    dx_debug_draw_editable_num(&DebugStarPieces, SubmenuPosX, SubmenuPosY + 2 * RowHeight);
}

// ----------------------------------------------------------------------------
// view collision

typedef struct DebugCollisionEntry {
    char* text;
    s32 state;
} DebugCollisionEntry;

enum {
    DBC_SHOW_COLLISION,
    DBC_CULL_BACK,
    DBC_SHOW_DISABLED,
    DBC_HIDE_MODELS,
    DBC_EXTRUDE_FACES,
    DBC_HIGHLIGHT_FLOOR,
    DBC_HIGHLIGHT_WALL,
    DBC_FADE_DIST,
};

DebugCollisionEntry DebugCollisionMenu[] = {
    [DBC_SHOW_COLLISION]  { "Show Collision",  false },
    [DBC_CULL_BACK]       { "Cull Back",       true },
    [DBC_SHOW_DISABLED]   { "Show Disabled",   true },
    [DBC_HIDE_MODELS]     { "Hide Models",     false },
    [DBC_EXTRUDE_FACES]   { "Extrude Faces",   false },
    [DBC_HIGHLIGHT_FLOOR] { "Highlight Floor", false },
    [DBC_HIGHLIGHT_WALL]  { "Highlight Wall",  false },
    [DBC_FADE_DIST]       { "Near Fade Dist",  1 },
};

s32 DebugCollisionPos = 0;

void dx_debug_update_view_collision() {
    s32 idx;

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    }

    if (DebugCollisionPos != DBC_FADE_DIST) {
        if (NAV_LEFT || NAV_RIGHT) {
            DebugCollisionMenu[DebugCollisionPos].state = !DebugCollisionMenu[DebugCollisionPos].state;
        }
    } else {
        s32 fadeDist = DebugCollisionMenu[DebugCollisionPos].state;
        fadeDist = dx_debug_menu_nav_1D_horizontal(fadeDist, 0, 9, false);
        DebugCollisionMenu[DebugCollisionPos].state = fadeDist;
    }
    DebugCollisionPos = dx_debug_menu_nav_1D_vertical(DebugCollisionPos, 0, ARRAY_COUNT(DebugCollisionMenu) - 1, false);

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 120, 8 * RowHeight + 8, WINDOW_STYLE_20, 192);

    for (idx = 0; idx < ARRAY_COUNT(DebugCollisionMenu); idx++) {
        s32 color = (DebugCollisionPos == idx) ? HighlightColor : DefaultColor;
        if (idx != DBC_FADE_DIST) {
            char* onoff = DebugCollisionMenu[idx].state ? "On" : "Off";
            dx_debug_draw_ascii(onoff, color, SubmenuPosX, SubmenuPosY + (idx + 1) * RowHeight);
        } else {
            s32 fadeDist = DebugCollisionMenu[idx].state;
            dx_debug_draw_number(fadeDist, "%d", color, 255, SubmenuPosX, SubmenuPosY + (idx + 1) * RowHeight);
        }
        dx_debug_draw_ascii(DebugCollisionMenu[idx].text, DefaultColor, SubmenuPosX + 28, SubmenuPosY + (idx + 1) * RowHeight);
    }
}

void dx_debug_add_collision_vtx(Vtx_t* vtxBuffer, Vec3f* vert, Vec3f* normal, s32 r, s32 g, s32 b, s32 a) {
    if (DebugCollisionMenu[DBC_EXTRUDE_FACES].state) {
        vtxBuffer->ob[0] = vert->x + normal->x;
        vtxBuffer->ob[1] = vert->y + normal->y;
        vtxBuffer->ob[2] = vert->z + normal->z;
    } else {
        vtxBuffer->ob[0] = vert->x;
        vtxBuffer->ob[1] = vert->y;
        vtxBuffer->ob[2] = vert->z;
    }
    vtxBuffer->tc[0] = 0;
    vtxBuffer->tc[1] = 0;
    vtxBuffer->cn[0] = r;
    vtxBuffer->cn[1] = g;
    vtxBuffer->cn[2] = b;
    vtxBuffer->cn[3] = a;
}

#define MAX_DEBUG_TRIS 1024

typedef struct DebugTriangle {
    ColliderTriangle* tri;
    s16 depth;
    s16 colliderID;
} DebugTriangle;

DebugTriangle DebugTris[MAX_DEBUG_TRIS];
s32 DebugTriPos;

Vtx_t DebugVtxBuf[3 * MAX_DEBUG_TRIS];
s32 DebugVtxPos;

void dx_debug_draw_collision() {
    DebugTriangle temp;
    s32 rdpBufPos;
    b32 culling;
    s32 fadeDist;
    s32 i, j;
    s32 dist;

    Camera* camera = &gCameras[gCurrentCameraID];

    if (!DebugCollisionMenu[DBC_SHOW_COLLISION].state) {
        return;
    }

    // find all collider trianges
    DebugTriPos = 0;
    for (i = 0; i < gCollisionData.numColliders; i++) {
        Collider* collider = &gCollisionData.colliderList[i];

        if ((collider->flags & COLLIDER_FLAG_IGNORE_PLAYER) && !DebugCollisionMenu[DBC_SHOW_DISABLED].state) {
            continue;
        }

        for (j = 0; j < collider->numTriangles; j++) {
            if (DebugTriPos < MAX_DEBUG_TRIS) {
                ColliderTriangle* tri = &collider->triangleTable[j];
                f32 outX, outY, outZ, outW;
                f32 cX = (tri->v1->x + tri->v2->x + tri->v3->x) / 3;
                f32 cY = (tri->v1->y + tri->v2->y + tri->v3->y) / 3;
                f32 cZ = (tri->v1->z + tri->v2->z + tri->v3->z) / 3;

                transform_point(camera->mtxPerspective, cX, cY, cZ, 1.0f, &outX, &outY, &outZ, &outW);

                if (outZ < -100) {
                    // dont draw triangles sufficiently far behind the camera
                    DebugTriPos--;
                } else {
                    DebugTris[DebugTriPos].tri = tri;
                    DebugTris[DebugTriPos].depth = outZ;
                    DebugTris[DebugTriPos].colliderID = i;
                }
            }
            DebugTriPos++;
        }
    }

    ASSERT(DebugTriPos < MAX_DEBUG_TRIS)

    // sort triangles by depth
#define LESS(i, j) DebugTris[i].depth > DebugTris[j].depth
#define SWAP(i, j) temp = DebugTris[i], DebugTris[i] = DebugTris[j], DebugTris[j] = temp
    QSORT(DebugTriPos, LESS, SWAP);
#undef LESS
#undef SWAP

    gDPPipeSync(gMainGfxPos++);
    gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
    gDPSetCombineMode(gMainGfxPos++, G_CC_SHADE, G_CC_SHADE);
    gSPTexture(gMainGfxPos++, 0x0080, 0x0080, 0, G_TX_RENDERTILE, G_OFF);
    gSPClearGeometryMode(gMainGfxPos++, G_LIGHTING | G_CULL_BACK);

    if (DebugCollisionMenu[DBC_CULL_BACK].state) {
        gSPSetGeometryMode(gMainGfxPos++, G_CULL_BACK | G_SHADING_SMOOTH);
        culling = true;
    } else {
        gSPSetGeometryMode(gMainGfxPos++, G_SHADING_SMOOTH);
        culling = false;
    }

    DebugVtxPos = 0;
    rdpBufPos = 0;

    // build the display list and fill DebugVtxBuf at the same time
    for (i = 0; i < DebugTriPos; i++) {
        DebugTriangle* debugTri = &DebugTris[i];
        ColliderTriangle* tri = debugTri->tri;
        s32 r, g, b, a;

        b32 highlight = false;
        if (DebugCollisionMenu[DBC_HIGHLIGHT_FLOOR].state && debugTri->colliderID == gCollisionStatus.curFloor) {
            highlight = true;
        }
        if (DebugCollisionMenu[DBC_HIGHLIGHT_WALL].state && debugTri->colliderID == gCollisionStatus.curWall) {
            highlight = true;
        }

        if (rdpBufPos == 0) {
            // always load vertices 30 at a time
            gSPVertex(gMainGfxPos++, &DebugVtxBuf[DebugVtxPos], 30, 0);
        }

        // manage culling state for two-sided triangles
        if (DebugCollisionMenu[DBC_CULL_BACK].state) {
            if (!tri->oneSided && culling) {
                gDPPipeSync(gMainGfxPos++);
                gSPClearGeometryMode(gMainGfxPos++, G_CULL_BACK);
                culling = false;
            } else if (tri->oneSided && !culling) {
                gDPPipeSync(gMainGfxPos++);
                gSPSetGeometryMode(gMainGfxPos++, G_CULL_BACK);
                culling = true;
            }
        }

        // would be more efficient to pack these into gSP2Triangles ad hoc
        // but it becomes difficult to manage once RDP state changes enter the mix due to two-sided triangles
        gSP1Triangle(gMainGfxPos++, rdpBufPos, rdpBufPos + 1, rdpBufPos + 2, 0);

        // update rdp buffer pos for next triangle draw
        rdpBufPos += 3;
        if (rdpBufPos == 30) {
            rdpBufPos = 0;
        }

        if (highlight) {
            r = g = b = 196;
        } else {
            r = round(fabs(tri->normal.x) * 245.0);
            g = round(fabs(tri->normal.y) * 245.0);
            b = round(fabs(tri->normal.z) * 245.0);
        }
        a = 180;

        // fade triangles too close to the camera
        fadeDist = DebugCollisionMenu[DBC_FADE_DIST].state;
        if(fadeDist > 0) {
            dist = debugTri->depth - (fadeDist - 1) * 25;
            if (dist < 20) {
                // from a=20 at d=40 to a=0 at d=-100
                a = dx_debug_clamp((dist + 100) / 6, 0, 20);
            } else {
                a = dx_debug_clamp(dist, 20, 180);
            }
        }

        // build vertices for this triangle
        dx_debug_add_collision_vtx(&DebugVtxBuf[DebugVtxPos++], tri->v1, &tri->normal, r, g, b, a);
        dx_debug_add_collision_vtx(&DebugVtxBuf[DebugVtxPos++], tri->v2, &tri->normal, r, g, b, a);
        dx_debug_add_collision_vtx(&DebugVtxBuf[DebugVtxPos++], tri->v3, &tri->normal, r, g, b, a);
    }

    // done
    gDPPipeSync(gMainGfxPos++);
}

b32 dx_debug_should_hide_models() {
    return DebugCollisionMenu[DBC_HIDE_MODELS].state;
}

// ----------------------------------------------------------------------------
// cheat menu

typedef struct DebugCheatEntry {
    char* text;
    b32 enabled;
} DebugCheatEntry;

DebugCheatEntry DebugCheatMenu[] = {
    [DEBUG_CHEAT_GOD_MODE]      { "God Mode",   false },
    [DEBUG_CHEAT_SPEED_MODE]    { "Speed Mode", false },
    [DEBUG_CHEAT_FLY]           { "Fly With L", false },
    [DEBUG_CHEAT_HIGH_JUMP]     { "High Jump", false },
    [DEBUG_CHEAT_IGNORE_WALLS]  { "Ignore Walls", false },
};

s32 DebugCheatPos = 0;

void dx_debug_update_cheat_menu() {
    s32 idx;

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    }
     if (NAV_LEFT || NAV_RIGHT) {
        DebugCheatMenu[DebugCheatPos].enabled = !DebugCheatMenu[DebugCheatPos].enabled;

        // actions to execute on state change
        switch (DebugCheatPos) {
            case DEBUG_CHEAT_GOD_MODE:
            case DEBUG_CHEAT_FLY:
            case DEBUG_CHEAT_HIGH_JUMP:
            case DEBUG_CHEAT_IGNORE_WALLS:
                break;
            case DEBUG_CHEAT_SPEED_MODE:
                if (!DebugCheatMenu[DebugCheatPos].enabled) {
                    gPlayerStatus.walkSpeed = 2.0f;
                    gPlayerStatus.runSpeed = 4.0f;
                    gGameStatusPtr->debugEnemyContact = DEBUG_CONTACT_NONE;
                } else {
                    gPlayerStatus.walkSpeed = 6.0f;
                    gPlayerStatus.runSpeed = 12.0f;
                    gGameStatusPtr->debugEnemyContact = DEBUG_CONTACT_CANT_TOUCH;
                }
                break;
        }

    }
    DebugCheatPos = dx_debug_menu_nav_1D_vertical(DebugCheatPos, 0, ARRAY_COUNT(DebugCheatMenu) - 1, false);

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 120, ARRAY_COUNT(DebugCheatMenu) * RowHeight + 8, WINDOW_STYLE_20, 192);

    for (idx = 0; idx < ARRAY_COUNT(DebugCheatMenu); idx++) {
        s32 color = (DebugCheatPos == idx) ? HighlightColor : DefaultColor;
        char* onoff = DebugCheatMenu[idx].enabled ? "On" : "Off";

        dx_debug_draw_ascii(onoff, color, SubmenuPosX, SubmenuPosY + (idx + 1) * RowHeight);
        dx_debug_draw_ascii(DebugCheatMenu[idx].text, DefaultColor, SubmenuPosX + 28, SubmenuPosY + (idx + 1) * RowHeight);
    }
}

b32 dx_debug_is_cheat_enabled(DebugCheat cheat) {
    return DebugCheatMenu[cheat].enabled;
}

// ----------------------------------------------------------------------------
// script debugger

const s32 EvtDebugBoxWidth    = 72;
const s32 EvtDebugBoxHeight   = BoxOutsetY + 10 * RowHeight + BoxOutsetY;

const s32 EvtDebugMenuPosX    = 314 - EvtDebugBoxWidth; // right edge should be at 314
const s32 EvtDebugMenuPosY    = 60;

// position of the blue box containing the main menu options
const s32 EvtDebugBoxPosX     = EvtDebugMenuPosX - BoxOutsetX;
const s32 EvtDebugBoxPosY     = EvtDebugMenuPosY - BoxOutsetY;

const s32 EvtDebugInfoX     = 26;
const s32 EvtDebugInfoY     = 60;
const s32 EvtDebugInfoWidth     = 212;
const s32 EvtDebugInfoHeight    = BoxOutsetY + 10 * RowHeight + BoxOutsetY;

char* EvtMainMenuOpts[] = {
    "Attach",
    "Break",
    "Resume",
    "Break All",
    "Resume All",
};

s32 EvtMainMenuPos = 0;

s32 EvtListCurPos = 0;
s32 EvtListDrawPos = 0;

s32 EvtAttachedMenuPos = 0;
s32 EvtAttachedDispMode = 0;
s32 EvtAttachedVarsMode = 0;

extern ScriptList* gCurrentScriptListPtr;
extern s32 gScriptIndexList[];
extern s32 gScriptIdList[];
extern s32 gScriptListCount;

Evt* DebugEvtList[MAX_SCRIPTS];
s32 DebugEvtCount;

Evt* DebugEvtAttached;
s32 DebugEvtPrevLVars[16];
s32 DebugEvtPrevTemps[4];

u16 DebugEvtLineOffsets[1024];
s32 DebugEvtLineCount;
s32 DebugEvtCurLine;
s32 DebugEvtDrawLine;

typedef struct DebugOpcode {
    char* text;
} DebugOpcode;

DebugOpcode DebugOps[] = {
    [EVT_OP_END]                { "End" },
    [EVT_OP_RETURN]             { "Return" },
    [EVT_OP_LABEL]              { "Label" },
    [EVT_OP_GOTO]               { "Goto" },
    [EVT_OP_LOOP]               { "Loop" },
    [EVT_OP_END_LOOP]           { "EndLoop" },
    [EVT_OP_BREAK_LOOP]         { "BreakLoop" },
    [EVT_OP_WAIT_FRAMES]        { "Wait" },
    [EVT_OP_WAIT_SECS]          { "WaitSecs" },
    [EVT_OP_IF_EQ]              { "If EQ" },
    [EVT_OP_IF_NE]              { "If NE" },
    [EVT_OP_IF_LT]              { "If LT" },
    [EVT_OP_IF_GT]              { "If GT" },
    [EVT_OP_IF_LE]              { "If LE" },
    [EVT_OP_IF_GE]              { "If GE" },
    [EVT_OP_IF_FLAG]            { "If AND" },
    [EVT_OP_IF_NOT_FLAG]        { "If NAND" },
    [EVT_OP_ELSE]               { "Else" },
    [EVT_OP_END_IF]             { "EndIf" },
    [EVT_OP_SWITCH]             { "Switch" },
    [EVT_OP_SWITCH_CONST]       { "SwitchConst" },
    [EVT_OP_CASE_EQ]            { "Case EQ" },
    [EVT_OP_CASE_NE]            { "Case NE" },
    [EVT_OP_CASE_LT]            { "Case LT" },
    [EVT_OP_CASE_GT]            { "Case GT" },
    [EVT_OP_CASE_LE]            { "Case LE" },
    [EVT_OP_CASE_GE]            { "Case GE" },
    [EVT_OP_CASE_DEFAULT]       { "Default" },
    [EVT_OP_CASE_OR_EQ]         { "CaseOR EQ" },
    [EVT_OP_CASE_AND_EQ]        { "CaseAND EQ" },
    [EVT_OP_CASE_FLAG]          { "Case AND" },
    [EVT_OP_END_CASE_GROUP]     { "EndCaseGroup" },
    [EVT_OP_CASE_RANGE]         { "Case Range" },
    [EVT_OP_BREAK_SWITCH]       { "BreakSwitch" },
    [EVT_OP_END_SWITCH]         { "EndSwitch" },
    [EVT_OP_SET]                { "Set" },
    [EVT_OP_SET_CONST]          { "SetConst" },
    [EVT_OP_SETF]               { "SetF" },
    [EVT_OP_ADD]                { "Add" },
    [EVT_OP_SUB]                { "Sub" },
    [EVT_OP_MUL]                { "Mul" },
    [EVT_OP_DIV]                { "Div" },
    [EVT_OP_MOD]                { "Mod" },
    [EVT_OP_ADDF]               { "AddF" },
    [EVT_OP_SUBF]               { "SubF" },
    [EVT_OP_MULF]               { "MulF" },
    [EVT_OP_DIVF]               { "DivF" },
    [EVT_OP_USE_BUF]            { "UseBuf" },
    [EVT_OP_BUF_READ1]          { "BufRead1" },
    [EVT_OP_BUF_READ2]          { "BufRead2" },
    [EVT_OP_BUF_READ3]          { "BufRead3" },
    [EVT_OP_BUF_READ4]          { "BufRead4" },
    [EVT_OP_BUF_PEEK]           { "BufPeek" },
    [EVT_OP_USE_FBUF]           { "UseFBuf" },
    [EVT_OP_FBUF_READ1]         { "FBufRead1" },
    [EVT_OP_FBUF_READ2]         { "FBufRead2" },
    [EVT_OP_FBUF_READ3]         { "FBufRead3" },
    [EVT_OP_FBUF_READ4]         { "FBufRead4" },
    [EVT_OP_FBUF_PEEK]          { "FBufPeek" },
    [EVT_OP_USE_ARRAY]          { "UseArray" },
    [EVT_OP_USE_FLAGS]          { "UseFlags" },
    [EVT_OP_MALLOC_ARRAY]       { "MallocArray" },
    [EVT_OP_BITWISE_AND]        { "AND" },
    [EVT_OP_BITWISE_AND_CONST]  { "AND Const" },
    [EVT_OP_BITWISE_OR]         { "OR" },
    [EVT_OP_BITWISE_OR_CONST]   { "OR Const" },
    [EVT_OP_CALL]               { "Call" },
    [EVT_OP_EXEC]               { "Exec" },
    [EVT_OP_EXEC_GET_TID]       { "ExecGet" },
    [EVT_OP_EXEC_WAIT]          { "ExecWait" },
    [EVT_OP_BIND_TRIGGER]       { "BindTrigger" },
    [EVT_OP_UNBIND]             { "Unbind" },
    [EVT_OP_KILL_THREAD]        { "KillThread" },
    [EVT_OP_JUMP]               { "Jump" },
    [EVT_OP_SET_PRIORITY]       { "SetPriority" },
    [EVT_OP_SET_TIMESCALE]      { "SetTimescale" },
    [EVT_OP_SET_GROUP]          { "SetGroup" },
    [EVT_OP_BIND_PADLOCK]       { "BindPadlock" },
    [EVT_OP_SUSPEND_GROUP]      { "SuspendGroup" },
    [EVT_OP_RESUME_GROUP]       { "ResumeGroup" },
    [EVT_OP_SUSPEND_OTHERS]     { "SuspendOthers" },
    [EVT_OP_RESUME_OTHERS]      { "ResumeOthers" },
    [EVT_OP_SUSPEND_THREAD]     { "SuspendThread" },
    [EVT_OP_RESUME_THREAD]      { "ResumeThread" },
    [EVT_OP_IS_THREAD_RUNNING]  { "IsRunning" },
    [EVT_OP_THREAD]             { "Thread" },
    [EVT_OP_END_THREAD]         { "EndThread" },
    [EVT_OP_CHILD_THREAD]       { "ChildThread" },
    [EVT_OP_END_CHILD_THREAD]   { "EndChildThread" },
    [EVT_OP_DEBUG_LOG]          { "Log" },
    [EVT_OP_DEBUG_PRINT_VAR]    { "PrintVar" },
    [EVT_OP_92]                 { "Op92" },
    [EVT_OP_93]                 { "Op93" },
    [EVT_OP_94]                 { "Op94" },
    [EVT_OP_DEBUG_BREAKPOINT]   { "Breakpoint" },
};

// main menu options for evt debugger
enum {
    DEBUG_EVT_MAIN_ATTACH           = 0,
    DEBUG_EVT_MAIN_BREAK            = 1,
    DEBUG_EVT_MAIN_RESUME           = 2,
    DEBUG_EVT_MAIN_BREAK_ALL        = 3,
    DEBUG_EVT_MAIN_RESUME_ALL       = 4,
    DEBUG_EVT_MAIN_COUNT,
};

// menu options for evt debugger while attached
enum {
    DEBUG_EVT_ATTACHED_DETACH       = 0,
    DEBUG_EVT_ATTACHED_BREAK        = 1,
    DEBUG_EVT_ATTACHED_STEP_ONCE    = 2,
    DEBUG_EVT_ATTACHED_STEP_OVER    = 3,
    DEBUG_EVT_ATTACHED_DISP_MODE    = 4,
    DEBUG_EVT_ATTACHED_COUNT,
};

// display modes for evt debugger vars
enum {
    DEBUG_EVT_DISP_MODE_RAW         = 0,
    DEBUG_EVT_DISP_MODE_INT         = 1,
    DEBUG_EVT_DISP_MODE_FIXED       = 2,
    DEBUG_EVT_DISP_MODE_FLOAT       = 3,
    DEBUG_EVT_DISP_MODE_COUNT,
};

void dx_debug_update_evt_list() {
    s32 i;

    DebugEvtCount = 0;

    for (i = 0; i < gScriptListCount; i++) {
        Evt* script = (*gCurrentScriptListPtr)[gScriptIndexList[i]];

        if (script != nullptr
            && script->id == gScriptIdList[i]
            && script->stateFlags != 0
        ) {
            DebugEvtList[DebugEvtCount] = script;
            DebugEvtCount++;
        }
    }

    for (i = DebugEvtCount; i < MAX_SCRIPTS; i++) {
        DebugEvtList[i] = nullptr;
    }
}

void dx_debug_evt_capture_vars() {
    s32 i;

    if (DebugEvtAttached == nullptr) {
        return;
    }

    for (i = 0; i < 16; i++) {
        DebugEvtPrevLVars[i] = DebugEvtAttached->varTable[i];
    }
    for (i = 0; i < 4; i++) {
        DebugEvtPrevTemps[i] = DebugEvtAttached->functionTemp[i];
    }
}

s32 dx_debug_scroll_to_line(s32 drawnLine, s32 selectedLine, s32 maxLine, s32 maxVisible) {
    // if all lines can fit, do not scroll
    if (maxLine <= maxVisible) {
        return 0;
    }

    // scroll up to show selectedLine with an extra line before, if available
    if (selectedLine < drawnLine + 1) {
        return MAX(0, selectedLine - 1);
    }

    // last line selected, scroll to it without end padding
    if (selectedLine == maxLine - 1) {
        return selectedLine - (maxVisible - 1);
    }

    //scroll down to show selectedLine with an extra line after
    if (selectedLine > drawnLine + (maxVisible - 2)) {
        return selectedLine - (maxVisible - 2);
    }

    // no change
    return drawnLine;
}

void dx_debug_draw_evt_list() {
    s32 i;

    const s32 BoxStartX = EvtDebugInfoX - BoxOutsetX;
    const s32 BoxStartY = EvtDebugInfoY - BoxOutsetY;
    const s32 BoxHeight = BoxOutsetY + 10 * RowHeight + BoxOutsetY;
    const s32 BoxWidth = 212;

    // script list box
    dx_debug_draw_box(BoxStartX, BoxStartY, BoxWidth, BoxHeight, WINDOW_STYLE_20, 192);

    dx_debug_draw_ascii("Grp", DefaultColor, EvtDebugInfoX - 3, EvtDebugInfoY);
    dx_debug_draw_ascii("Start", DefaultColor, EvtDebugInfoX + 20 + 8, EvtDebugInfoY);
    dx_debug_draw_ascii("Current", DefaultColor, EvtDebugInfoX + 80, EvtDebugInfoY);

    EvtListDrawPos = dx_debug_scroll_to_line(EvtListDrawPos, EvtListCurPos, DebugEvtCount, 9);
    s32 last = MIN(EvtListDrawPos + 9, DebugEvtCount);
    s32 row = 0;

    for (i = EvtListDrawPos; i < last; i++) {
        Evt* script = DebugEvtList[i];

        s32 posY = EvtDebugInfoY + (1 + row) * RowHeight;
        s32 color = DefaultColor;

        if (script->debugPaused) {
            color = MSG_PAL_RED;
        }

        if (DebugMenuState == DBM_EVT_SELECT && EvtListCurPos == i) {
            color = HighlightColor;
        }

        dx_debug_draw_number(script->groupFlags, "%02X", color, 255, EvtDebugInfoX, posY);
        dx_debug_draw_number(script->ptrFirstLine, "%08X", color, 255, EvtDebugInfoX + 20, posY);
        dx_debug_draw_number((u8*)script->ptrCurLine - (u8*)script->ptrFirstLine, "%X", color, 255, EvtDebugInfoX + 80, posY);

        row++;
    }

    // animated down arrow
    if (DebugEvtCount > last) {
        char msgDownArrow[] = {
            MSG_CHAR_DOWN, MSG_CHAR_READ_END
        };
        s32 posY = EvtDebugInfoY + (9) * RowHeight;
        draw_msg((intptr_t)msgDownArrow, EvtDebugInfoX + 185, posY - round(2.0f * ArrowAnimOffset), 255, DefaultColor, 0);
    }
    // animated up arrow
    if (EvtListDrawPos > 0) {
        char msgUpArrow[] = {
            MSG_CHAR_UP, MSG_CHAR_READ_END
        };
        s32 posY = EvtDebugInfoY + (1) * RowHeight;
        draw_msg((intptr_t)msgUpArrow, EvtDebugInfoX + 185, posY + round(2.0f * ArrowAnimOffset), 255, DefaultColor, 0);
    }

    // menu box (upper right)
    dx_debug_draw_box(EvtDebugBoxPosX, EvtDebugBoxPosY, EvtDebugBoxWidth, ARRAY_COUNT(EvtMainMenuOpts) * RowHeight + 8, WINDOW_STYLE_4, 192);

    for (i = 0; i < ARRAY_COUNT(EvtMainMenuOpts); i++) {
        s32 color = DefaultColor;
        if (EvtMainMenuPos == i) {
            color = (DebugMenuState != DBM_EVT_SELECT) ? HighlightColor : HoverColor;
        }
        dx_debug_draw_ascii(EvtMainMenuOpts[i], color, EvtDebugMenuPosX, EvtDebugMenuPosY + i * RowHeight);
    }

    // count box (lower right)
    dx_debug_draw_box(EvtDebugBoxPosX, EvtDebugBoxPosY + 9 * RowHeight, EvtDebugBoxWidth, RowHeight + 8, WINDOW_STYLE_4, 192);
    dx_debug_draw_number(DebugEvtCount, "%d running", DefaultColor, 255, EvtDebugMenuPosX, EvtDebugMenuPosY + 9 * RowHeight);
}

void dx_debug_evt_break_all() {
    s32 i;

    debug_printf("count: %d", DebugEvtCount);

    for (i = 0; i < DebugEvtCount; i++) {
        Evt* script = DebugEvtList[i];
        script->debugPaused = true;
        script->debugStep = DEBUG_EVT_STEP_NONE;
    }
}

void dx_debug_evt_resume_all() {
    s32 i;

    for (i = 0; i < DebugEvtCount; i++) {
        Evt* script = DebugEvtList[i];
        script->debugPaused = false;
        script->debugStep = DEBUG_EVT_STEP_NONE;
    }
}

void dx_debug_update_evt_main() {

    dx_debug_update_evt_list();

    EvtMainMenuPos = dx_debug_menu_nav_1D_vertical(EvtMainMenuPos, 0, DEBUG_EVT_MAIN_COUNT - 1, false);

    // handle input
    if (RELEASED(BUTTON_R)) {
        switch (EvtMainMenuPos) {
            case DEBUG_EVT_MAIN_ATTACH:
            case DEBUG_EVT_MAIN_BREAK:
            case DEBUG_EVT_MAIN_RESUME:
                DebugMenuState = DBM_EVT_SELECT;
                break;
            case DEBUG_EVT_MAIN_BREAK_ALL:
                dx_debug_evt_break_all();
                break;
            case DEBUG_EVT_MAIN_RESUME_ALL:
                dx_debug_evt_resume_all();
                break;
        }
    }

    dx_debug_draw_evt_list();
}

void dx_debug_update_evt_select() {

    dx_debug_update_evt_list();

    if (DebugEvtCount > 1) {
        EvtListCurPos = dx_debug_menu_nav_1D_vertical(EvtListCurPos, 0, DebugEvtCount - 1, false);
    } else {
        EvtListCurPos = 0;
    }

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_EVT_MAIN;
    } else if (RELEASED(BUTTON_R)) {
        if (DebugEvtCount > 0) {
            switch (EvtMainMenuPos) {
                case DEBUG_EVT_MAIN_ATTACH:
                    DebugMenuState = DBM_EVT_ATTACHED;
                    DebugEvtAttached = DebugEvtList[EvtListCurPos];
                    DebugEvtAttached->debugStep = DEBUG_EVT_STEP_NONE;
                    DebugEvtDrawLine = 0;
                    dx_debug_evt_capture_vars();
                    break;
                case DEBUG_EVT_MAIN_BREAK:
                    DebugEvtList[EvtListCurPos]->debugPaused = true;
                    DebugEvtList[EvtListCurPos]->debugStep = DEBUG_EVT_STEP_NONE;
                    break;
                case DEBUG_EVT_MAIN_RESUME:
                    DebugEvtList[EvtListCurPos]->debugPaused = false;
                    DebugEvtList[EvtListCurPos]->debugStep = DEBUG_EVT_STEP_NONE;
                    break;
            }
        }
    }

    dx_debug_draw_evt_list();
}

void dx_debug_evt_draw_menu_line(s32 idx, char* text) {
    s32 color = DefaultColor;
    if (EvtAttachedMenuPos == idx) {
        color = (DebugMenuState != DBM_EVT_SELECT) ? HighlightColor : HoverColor;
    }
    dx_debug_draw_ascii(text, color, EvtDebugMenuPosX, EvtDebugMenuPosY + idx * RowHeight);
}

void dx_debug_draw_var(s32 i, s32 number, char* fmt, s32 color, s32 alpha, s32 posX, s32 posY) {
    char fmtBuf[64];
    char buf[64] = {
        MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SIZE, 12, 12
    };
    sprintf(fmtBuf, fmt, i, number);
    dx_string_to_msg(&buf[4], fmtBuf);
    draw_msg((intptr_t)buf, posX, posY, alpha, color, 0);
}

void dx_debug_draw_fvar(s32 i, f32 number, char* fmt, s32 color, s32 alpha, s32 posX, s32 posY) {
    char fmtBuf[64];
    char buf[64] = {
        MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SIZE, 12, 12
    };
    sprintf(fmtBuf, fmt, i, number);
    dx_string_to_msg(&buf[4], fmtBuf);
    draw_msg((intptr_t)buf, posX, posY, alpha, color, 0);
}

void dx_debug_evt_draw_vars() {
    #define MAX_VALID_FLOAT 1e9
    s32 val;
    f32 fval;
    s32 i;

    for (i = 0; i < 16; i++) {
        s32 posX = EvtDebugInfoX + (i / 8) * 106;
        s32 posY = EvtDebugInfoY + (i % 8) * RowHeight;
        s32 color = DebugEvtPrevLVars[i] == DebugEvtAttached->varTable[i] ? DefaultColor : HoverColor;

        switch (EvtAttachedVarsMode) {
                case DEBUG_EVT_DISP_MODE_RAW:
                dx_debug_draw_var(i, DebugEvtAttached->varTable[i], "LVar%X  %08X", color, 255, posX, posY);
                break;
            case DEBUG_EVT_DISP_MODE_INT:
                dx_debug_draw_var(i, DebugEvtAttached->varTable[i], "LVar%X  %d", color, 255, posX, posY);
                break;
            case DEBUG_EVT_DISP_MODE_FLOAT:
                fval = DebugEvtAttached->varTableF[i];
                if (fabsf(fval) < MAX_VALID_FLOAT) {
                    dx_debug_draw_fvar(i, fval, "LVar%X  %f", color, 255, posX, posY);
                } else {
                    dx_debug_draw_var(i, 0, "LVar%X  ---", color, 255, posX, posY);
                }
                break;
            case DEBUG_EVT_DISP_MODE_FIXED:
                val = DebugEvtAttached->varTable[i];
                if (val > EVT_FIXED_END && val < EVT_FIXED_CUTOFF) {
                    dx_debug_draw_fvar(i, EVT_FIXED_TO_FLOAT(val), "LVar%X  %f", color, 255, posX, posY);
                } else {
                    dx_debug_draw_var(i, 0, "LVar%X  ---", color, 255, posX, posY);
                }
                break;
        }
    }

    for (i = 0; i < 4; i++) {
        s32 posX = EvtDebugInfoX + (i / 2) * 106;
        s32 posY = EvtDebugInfoY + (8 + (i % 2)) * RowHeight;
        s32 color = DebugEvtPrevTemps[i] == DebugEvtAttached->functionTemp[i] ? DefaultColor : HoverColor;

        switch (EvtAttachedVarsMode) {
            case DEBUG_EVT_DISP_MODE_RAW:
                dx_debug_draw_var(i, DebugEvtAttached->functionTemp[i], "Temp%X  %08X", color, 255, posX, posY);
                break;
            case DEBUG_EVT_DISP_MODE_INT:
                dx_debug_draw_var(i, DebugEvtAttached->functionTemp[i], "Temp%X  %d", color, 255, posX, posY);
                break;
            case DEBUG_EVT_DISP_MODE_FLOAT:
                fval = DebugEvtAttached->functionTempF[i].f;
                if (fabsf(fval) < MAX_VALID_FLOAT) {
                    dx_debug_draw_fvar(i, fval, "Temp%X  %f", color, 255, posX, posY);
                } else {
                    dx_debug_draw_var(i, 0, "Temp%X  ---", color, 255, posX, posY);
                }
                dx_debug_draw_fvar(i, DebugEvtAttached->functionTempF[i].f, "Temp%X  %f", color, 255, posX, posY);
                break;
            case DEBUG_EVT_DISP_MODE_FIXED:
                val = DebugEvtAttached->functionTemp[i];
                if (val > EVT_FIXED_END && val < EVT_FIXED_CUTOFF) {
                    dx_debug_draw_fvar(i, EVT_FIXED_TO_FLOAT(val), "Temp%X  %f", color, 255, posX, posY);
                } else {
                    dx_debug_draw_var(i, 0, "Temp%X  ---", color, 255, posX, posY);
                }
                break;
        }
    }
}

void dx_debug_evt_draw_arg(u32 value, b32 asDecimal, s32 color, s32 posX, s32 posY) {
    if (value >= LVar0 && value <= LVarF) {
        dx_debug_draw_number(value - LVar0, "LVar%X", color, 255, posX, posY);
    } else if (asDecimal) {
        dx_debug_draw_number(value, "%d", color, 255, posX, posY);
    } else {
        dx_debug_draw_number(value, "%08X", color, 255, posX, posY);
    }
}

void dx_debug_evt_draw_disasm() {
    Bytecode* pos;
    s32 i, j;
    s32 op, nargs;

    if (DebugEvtAttached == nullptr) {
        return;
    }

    pos = DebugEvtAttached->ptrFirstLine;
    DebugEvtLineCount = 0;

    // find offsets for all lines in script
    while (true) {
        DebugEvtLineOffsets[DebugEvtLineCount] = (u16)(pos - DebugEvtAttached->ptrFirstLine);

        if (pos == DebugEvtAttached->ptrCurLine) {
            DebugEvtCurLine = DebugEvtLineCount;
        }

        op = *pos++;
        nargs = *pos++;
        pos += nargs;

        DebugEvtLineCount++;

        if (op == EVT_OP_END || DebugEvtLineCount == ARRAY_COUNT(DebugEvtLineOffsets)) {
            break;
        }
    }

    DebugEvtDrawLine = dx_debug_scroll_to_line(DebugEvtDrawLine, DebugEvtCurLine, DebugEvtLineCount, 10);
    s32 last = MIN(DebugEvtDrawLine + 10, DebugEvtLineCount);
    s32 row = 0;

    for (i = DebugEvtDrawLine; i < last; i++) {
        pos = DebugEvtAttached->ptrFirstLine + DebugEvtLineOffsets[i];
        op = *pos++;
        nargs = *pos++;
        s32* args = pos;
        pos += nargs;

        s32 posY = EvtDebugInfoY + row * RowHeight;
        s32 color = (i == DebugEvtCurLine) ? HoverColor : DefaultColor;

        dx_debug_draw_number(i, "%d", color, 255, EvtDebugInfoX, posY);

        if (op > 0 && op < ARRAY_COUNT(DebugOps)) {
            dx_debug_draw_ascii(DebugOps[op].text, color, EvtDebugInfoX + 15, posY);
        } else {
            dx_debug_draw_number(op, "%08X", color, 255, EvtDebugInfoX + 15, posY);
        }

        switch (op) {
            case EVT_OP_LABEL:
            case EVT_OP_GOTO:
            case EVT_OP_LOOP:
            case EVT_OP_WAIT_FRAMES:
            case EVT_OP_WAIT_SECS:
                dx_debug_evt_draw_arg(args[0], true, color, EvtDebugInfoX + 15 + 55, posY);
                break;
            default:
                for (j = 0; j < MIN(2, nargs); j++) {
                    dx_debug_evt_draw_arg(args[j], false, color, EvtDebugInfoX + 15 + 55 * (j + 1), posY);
                }
                break;
        }

        if (nargs > 2) {
            dx_debug_draw_ascii("...", color, EvtDebugInfoX + 15 + 55 * 3, posY);
        }

        row++;
    }
}

void dx_debug_update_evt_attached() {
    s32 posY;

    if (DebugEvtAttached == nullptr) {
        DebugMenuState = DBM_EVT_MAIN;
        return;
    }

    // saves worrying about null checks while drawing on the frame we detach the evt
    b32 detachAfter = false;

    EvtAttachedMenuPos = dx_debug_menu_nav_1D_vertical(EvtAttachedMenuPos, 0, DEBUG_EVT_ATTACHED_COUNT - 1, false);
    EvtAttachedDispMode = dx_debug_menu_nav_1D_horizontal(EvtAttachedDispMode, 0, 1, false);

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_EVT_MAIN;
    } else if (RELEASED(BUTTON_R)) {
        switch (EvtAttachedMenuPos) {
            case DEBUG_EVT_ATTACHED_DETACH:
                detachAfter = true;
                break;
            case DEBUG_EVT_ATTACHED_BREAK:
                DebugEvtAttached->debugPaused = !DebugEvtAttached->debugPaused;
                break;
            case DEBUG_EVT_ATTACHED_STEP_ONCE:
                dx_debug_evt_capture_vars();
                DebugEvtAttached->debugStep = DEBUG_EVT_STEP_ONCE;
                break;
            case DEBUG_EVT_ATTACHED_STEP_OVER:
                dx_debug_evt_capture_vars();
                DebugEvtAttached->debugStep = DEBUG_EVT_STEP_OVER;
                break;
            case DEBUG_EVT_ATTACHED_DISP_MODE:
                EvtAttachedVarsMode++;
                if (EvtAttachedVarsMode >= DEBUG_EVT_DISP_MODE_COUNT) {
                    EvtAttachedVarsMode = 0;
                }
                break;
        }
    }

    // draw menu (upper right)
    dx_debug_draw_box(EvtDebugBoxPosX, EvtDebugBoxPosY, EvtDebugBoxWidth, 5 * RowHeight + 8, WINDOW_STYLE_4, 192);

    dx_debug_evt_draw_menu_line(0, "Detach");
    if (DebugEvtAttached->debugPaused) {
        dx_debug_evt_draw_menu_line(1, "Resume");
    } else {
        dx_debug_evt_draw_menu_line(1, "Break");
    }
    dx_debug_evt_draw_menu_line(2, "Step Once");
    dx_debug_evt_draw_menu_line(3, "Step Over");
    switch (EvtAttachedVarsMode) {
        case DEBUG_EVT_DISP_MODE_INT:
            dx_debug_evt_draw_menu_line(4, "Vars: Int");
            break;
        case DEBUG_EVT_DISP_MODE_FIXED:
            dx_debug_evt_draw_menu_line(4, "Vars: Fixed");
            break;
        case DEBUG_EVT_DISP_MODE_FLOAT:
            dx_debug_evt_draw_menu_line(4, "Vars: Float");
            break;
        case DEBUG_EVT_DISP_MODE_RAW:
            dx_debug_evt_draw_menu_line(4, "Vars: Raw");
            break;
    }

    // header box
    posY = EvtDebugInfoY - 4;
    posY -= RowHeight + 3; // move up one line and include a small gap
    dx_debug_draw_box(EvtDebugInfoX - 10, posY - 4, EvtDebugInfoWidth, 18, WINDOW_STYLE_20, 192);

    dx_debug_draw_number(DebugEvtAttached->ptrFirstLine, "%08X", DefaultColor, 255, EvtDebugInfoX + 40, posY);

    // evt info box
    dx_debug_draw_box(EvtDebugInfoX - 10, EvtDebugInfoY - 4, EvtDebugInfoWidth, EvtDebugInfoHeight, WINDOW_STYLE_20, 192);

    switch (EvtAttachedDispMode) {
        case 0:
            dx_debug_draw_ascii("Vars", DefaultColor, EvtDebugInfoX, posY);
            dx_debug_evt_draw_vars();
            break;
        case 1:
            dx_debug_draw_ascii("Disasm", DefaultColor, EvtDebugInfoX, posY);
            dx_debug_evt_draw_disasm();
            break;
    }

    if (!DebugEvtAttached->debugPaused) {
        dx_debug_evt_capture_vars();
    }

    if (detachAfter) {
        DebugMenuState = DBM_EVT_SELECT;
        DebugEvtAttached = nullptr;
    }
}

void dx_debug_evt_force_detach(Evt* evt) {
    if (DebugEvtAttached != nullptr && (DebugEvtAttached == evt)) {
        DebugEvtAttached = nullptr;

        if (DebugMenuState == DBM_EVT_ATTACHED) {
            DebugMenuState = DBM_EVT_MAIN;
        }
    }
}

void dx_debug_evt_reset() {
    if (DebugEvtAttached != nullptr) {
        DebugEvtAttached = nullptr;
    }

    EvtListCurPos = 0;
    EvtListDrawPos = 0;
}

// ----------------------------------------------------------------------------
// banner info

void dx_debug_update_banner() {
    // Moved to ImGui ValueViewer.cpp
    // char fmtBuf[128];
    // s32 effect;
    // 
    // if (gGameStatus.context == CONTEXT_WORLD) {
    //     sprintf(fmtBuf, "Map: %7s (%lX)", LastMapName, LastMapEntry);
    //     dx_debug_draw_ascii(fmtBuf, DefaultColor, 220, BottomRowY);
    // 
    //     dx_debug_draw_ascii("Pos:", DefaultColor, 20, BottomRowY);
    // 
    //     effect = dx_debug_is_cheat_enabled(DEBUG_CHEAT_SPEED_MODE) ? DRAW_MSG_STYLE_RAINBOW : 0;
    // 
    //     sprintf(fmtBuf, "%5ld", round(gPlayerStatus.pos.x));
    //     dx_debug_draw_ascii_with_effect(fmtBuf, DefaultColor, 48, BottomRowY, effect);
    //     
    //     sprintf(fmtBuf, "%5ld", round(gPlayerStatus.pos.y));
    //     dx_debug_draw_ascii_with_effect(fmtBuf, DefaultColor, 80, BottomRowY, effect);
    //     
    //     sprintf(fmtBuf, "%5ld", round(gPlayerStatus.pos.z));
    //     dx_debug_draw_ascii_with_effect(fmtBuf, DefaultColor, 112, BottomRowY, effect);
    // 
    //     if (dx_debug_is_cheat_enabled(DEBUG_CHEAT_GOD_MODE)) {
    //         dx_debug_draw_ascii("(GOD MODE)", MSG_PAL_YELLOW, 151, BottomRowY);
    //     }
    // } else if (gGameStatus.context == CONTEXT_BATTLE) {
    //     s32 areaID = (LastBattleID >> 24) & 0xFF;
    //     s32 battleID = (LastBattleID >> 16) & 0xFF;
    //     s32 stageID = LastBattleID & 0xFFFF;
    // 
    //     sprintf(fmtBuf, "Battle:  %02lX-%02lX (%lX)", areaID, battleID, stageID);
    //     dx_debug_draw_ascii(fmtBuf, DefaultColor, 200, BottomRowY);
    // 
    //     sprintf(fmtBuf, "Stage:  %-15s", LastStageName);
    //     dx_debug_draw_ascii(fmtBuf, DefaultColor, 20, BottomRowY);
    // 
    //     if (dx_debug_is_cheat_enabled(DEBUG_CHEAT_GOD_MODE)) {
    //         dx_debug_draw_ascii("(GOD MODE)", MSG_PAL_YELLOW, 128, BottomRowY);
    //     }
    // }
}

// ----------------------------------------------------------------------------
// console printing

#define DEBUG_CONSOLE_DEFAULT_TIMELEFT 60
#define DEBUG_CONSOLE_MSG_BUF_SIZE 85

typedef struct DebugConsoleLine {
    u32 hash;
    s32 timeLeft;
    u8 buf[DEBUG_CONSOLE_MSG_BUF_SIZE];
} DebugConsoleLine;

DebugConsoleLine DebugConsoleLine0 = { 0 };
DebugConsoleLine DebugConsoleLine1 = { 0 };
DebugConsoleLine DebugConsoleLine2 = { 0 };
DebugConsoleLine DebugConsoleLine3 = { 0 };
DebugConsoleLine DebugConsoleLine4 = { 0 };
DebugConsoleLine DebugConsoleLine5 = { 0 };
DebugConsoleLine DebugConsoleLine6 = { 0 };
DebugConsoleLine DebugConsoleLine7 = { 0 };

DebugConsoleLine *DebugConsole[8] = {
    &DebugConsoleLine0,
    &DebugConsoleLine1,
    &DebugConsoleLine2,
    &DebugConsoleLine3,
    &DebugConsoleLine4,
    &DebugConsoleLine5,
    &DebugConsoleLine6,
    &DebugConsoleLine7,
};

u32 dx_debug_hash_location(const char* filename, s32 line) {
    u32 hash = 5381;
    s32 c;

    while ((c = *filename++)) {
        hash = ((hash << 5) + hash) + c;
    }

    hash = ((hash << 5) + hash) + line;

    return hash;
}

static char *proutSprintf(char *dst, const char *src, size_t count) {
    return (char *)memcpy((u8 *)dst, (u8 *)src, count) + count;
}

void dx_hashed_debug_printf(const char* filename, s32 line, const char* fmt, ...) {
    char fmtBuf[128];
    va_list args;
    va_start(args, fmt);
    s32 len = _Printf(&proutSprintf, fmtBuf, fmt, args);
    if (len >= 0) {
        fmtBuf[len] = 0;
    }
    ASSERT(len < 85);

    u32 hash = dx_debug_hash_location(filename, line);
    s32 matchedLine = -1;
    s32 idx;

    // find a line with the matching hash
    for (idx = 0; idx < ARRAY_COUNT(DebugConsole); idx++) {
        if (DebugConsole[idx]->hash == hash) {
            matchedLine = idx;
            break;
        }
    }

    // find the oldest line
    if (matchedLine == -1) {
        s32 minTimeLeft = DEBUG_CONSOLE_DEFAULT_TIMELEFT;

        for (idx = 0; idx < ARRAY_COUNT(DebugConsole); idx++) {
            if (DebugConsole[idx]->timeLeft == 0) {
                matchedLine = idx;
                break;
            }
            if (DebugConsole[idx]->timeLeft < minTimeLeft) {
                minTimeLeft = DebugConsole[idx]->timeLeft;
                matchedLine = idx;
            }
        }
    }

    // update the ConsoleLine entry
    if (matchedLine != -1) {
        DebugConsole[matchedLine]->buf[0] = MSG_CHAR_READ_FUNCTION;
        DebugConsole[matchedLine]->buf[1] = MSG_READ_FUNC_SIZE;
        DebugConsole[matchedLine]->buf[2] = 12;
        DebugConsole[matchedLine]->buf[3] = 12;

        dx_string_to_msg(&DebugConsole[matchedLine]->buf[4], fmtBuf);

        DebugConsole[matchedLine]->hash = hash;
        DebugConsole[matchedLine]->timeLeft = DEBUG_CONSOLE_DEFAULT_TIMELEFT;
    }
}

API_CALLABLE(_dxDebugIntPrintf) {
    Bytecode* args = script->ptrReadPos;
    s32 i[8];
    s32 nargs = 0;
    s32 idx;

    char* filename = (char*)*args++;
    s32 line = *args++;
    char* fmt = (char*)*args++;

    for (idx = 0; idx < 8; idx++) {
        s32 var = *args++;
        if (var == 0) {
            break;
        }
        i[idx] = evt_get_variable(script, var);
        nargs++;
    }

    switch (nargs) {
        case 0: dx_hashed_debug_printf(filename, line, fmt); break;
        case 1: dx_hashed_debug_printf(filename, line, fmt, i[0]); break;
        case 2: dx_hashed_debug_printf(filename, line, fmt, i[0], i[1]); break;
        case 3: dx_hashed_debug_printf(filename, line, fmt, i[0], i[1], i[2]); break;
        case 4: dx_hashed_debug_printf(filename, line, fmt, i[0], i[1], i[2], i[3]); break;
        case 5: dx_hashed_debug_printf(filename, line, fmt, i[0], i[1], i[2], i[3], i[4]); break;
        case 6: dx_hashed_debug_printf(filename, line, fmt, i[0], i[1], i[2], i[3], i[4], i[5]); break;
        case 7: dx_hashed_debug_printf(filename, line, fmt, i[0], i[1], i[2], i[3], i[4], i[5], i[6]); break;
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(_dxDebugFloatPrintf) {
    Bytecode* args = script->ptrReadPos;
    f32 f[8];
    s32 nargs = 0;
    s32 idx;

    char* filename = (char*)*args++;
    s32 line = *args++;
    char* fmt = (char*)*args++;

    for (idx = 0; idx < 8; idx++) {
        s32 var = *args++;
        if (var == 0) {
            break;
        }
        f[idx] = evt_get_float_variable(script, var);
        nargs++;
    }

    switch (nargs) {
        case 0: dx_hashed_debug_printf(filename, line, fmt); break;
        case 1: dx_hashed_debug_printf(filename, line, fmt, f[0]); break;
        case 2: dx_hashed_debug_printf(filename, line, fmt, f[0], f[1]); break;
        case 3: dx_hashed_debug_printf(filename, line, fmt, f[0], f[1], f[2]); break;
        case 4: dx_hashed_debug_printf(filename, line, fmt, f[0], f[1], f[2], f[3]); break;
        case 5: dx_hashed_debug_printf(filename, line, fmt, f[0], f[1], f[2], f[3], f[4]); break;
        case 6: dx_hashed_debug_printf(filename, line, fmt, f[0], f[1], f[2], f[3], f[4], f[5]); break;
        case 7: dx_hashed_debug_printf(filename, line, fmt, f[0], f[1], f[2], f[3], f[4], f[5], f[6]); break;
    }

    return ApiStatus_DONE2;
}

void dx_debug_console_main() {
    DebugConsoleLine* temp;
    s32 idx;

#define LESS(i, j) DebugConsole[i]->timeLeft > DebugConsole[j]->timeLeft
#define SWAP(i, j) temp = DebugConsole[i], DebugConsole[i] = DebugConsole[j], DebugConsole[j] = temp
    QSORT(ARRAY_COUNT(DebugConsole), LESS, SWAP);
#undef LESS
#undef SWAP

    for (idx = 0; idx < ARRAY_COUNT(DebugConsole); idx++) {
        s32 timeLeft = DebugConsole[idx]->timeLeft;

        if (timeLeft > 0) {
            s32 alpha = 254;
            if (timeLeft < 20) {
                alpha = round(254 * (timeLeft / 20.0f));
            }

            draw_msg((intptr_t)DebugConsole[idx]->buf, 32, 200 - 15 * idx, alpha, DefaultColor, 0);
            DebugConsole[idx]->timeLeft--;
        }
    }
}

#endif
