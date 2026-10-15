#include "battle/battle.h"
#include "hud_element.h"

#define MENU_CAPACITY 24
#define MENU_LINE_HEIGHT 13
#define MENU_MAX_VISIBLE 6

enum {
    BTL_SUBMENU_STATE_CANCEL                = -2, // selection is canceled
    BTL_SUBMENU_STATE_SELECT                = -1, // a result is selected
    BTL_SUBMENU_STATE_INIT                  = 0,  // build and initialize the menu
    BTL_SUBMENU_STATE_CHOOSING              = 1,  // selecting an option
    BTL_SUBMENU_STATE_HIDE_INIT             = 10, // begin hiding the menu, will quickly change to HIDE_HOLD
    BTL_SUBMENU_STATE_HIDE_HOLD             = 11,
    BTL_SUBMENU_STATE_RESTORE               = 20, // reappear and resume choosing
    BTL_SUBMENU_STATE_LOCK                  = 30,
    BTL_SUBMENU_STATE_ERROR_INIT            = 40,
    BTL_SUBMENU_STATE_ERROR_SHOW            = 41,
    BTL_SUBMENU_STATE_ERROR_DONE            = 42,
};

extern HudScript HES_GreenArrowDown;
extern HudScript HES_GreenArrowUp;
extern HudScript HES_HandPointer;

BSS HudElemID HID_MovesArrowUp;
BSS HudElemID HID_MovesArrowDown;
BSS HudElemID HID_MovesCursor;
BSS HudElemID HID_MovesTitle;

extern HudScript HES_MenuStarPower;
extern HudScript HES_FPCost;
extern HudScript HES_FPCostReduced;
extern HudScript HES_FPCostReducedTwice;
extern HudScript HES_POWCost;
extern HudScript HES_POWCostReduced;
extern HudScript HES_POWCostReducedTwice;
extern HudScript HES_StatusFlower;
extern HudScript HES_NotEnoughFP;
extern HudScript HES_NotEnoughPOW;

BSS s16 MovesMenuPosX;
BSS s16 MovesMenuPosY;

BSS s8 MovesMenuState;
BSS s32 MovesPrevSelected; // index of previously selected option, set by caller before initializing the menu

// menu options are sorted before being displayed (according to priority and fp/bp cost)
// the arrays for option data are NOT sorted, so we use this to look up display order indices --> data array indices
BSS s32 MovesOptionIndexMap[MENU_CAPACITY];

BSS HudScript* MovesOptionHudScripts[MENU_CAPACITY];
BSS HudElemID MovesOptionHIDs[MENU_CAPACITY];
BSS HudElemID MovesOptionCostHIDs[MENU_CAPACITY];
BSS MsgID MovesOptionNames[MENU_CAPACITY];
BSS MsgID MovesOptionDesc[MENU_CAPACITY];
BSS s32 MovesOptionDisplayCosts[MENU_CAPACITY];
BSS s32 MovesOptionDiscounts[MENU_CAPACITY];
BSS s32 MovesOptionDiscountColors[MENU_CAPACITY];
BSS s32 MovesOptionBPCosts[MENU_CAPACITY];
BSS s32 MovesOptionIndices[MENU_CAPACITY];
BSS s32 MovesOptionEnabled[MENU_CAPACITY];
BSS s8 MovesOptionSortPriority[MENU_CAPACITY];
BSS s8 MovesOptionError[MENU_CAPACITY];
BSS s32 MovesOptionCount;

BSS s8 MovesCursorPos;
BSS s8 MovesPrevCursorPos;
BSS s8 MovesVisibleStart; // index of the first visible option (inclusive)
BSS s8 MovesVisibleEnd;   // index one past the last visible option (exclusive)
BSS s8 MovesMenuLines;
BSS b8 MovesDescVisible;
BSS s16 MovesScrollOffset;
BSS s16 MovesCursorOffset;

BSS s32 MovesErrorCode;
BSS s8 MovesErrorTimer; // how much time is left for showing an error message

BSS s16 MovesTextColor;
BSS s16 MovesTextAlpha;

BSS b32 UsingSpiritsSubmenu;
BSS s32 SelectedMovesIndex;

s16 ErrorMessageHeight[] = { 28, 40 };
s16 ErrorMessageAdjustY[] = { 0, -2 };

void btl_menu_moves_draw_content(void* data, s32 x, s32 y);
void btl_menu_moves_show_title(void* data, s32 x, s32 y);
void btl_menu_moves_show_icon(void* data, s32 x, s32 y);
void btl_menu_moves_show_desc(void* data, s32 x, s32 y);
void btl_menu_moves_show_error(void* data, s32 x, s32 y);

void btl_submenu_moves_init(void) {
    if (MovesPrevSelected >= MovesOptionCount) {
        MovesPrevSelected = MovesOptionCount - 1;
    }

    MovesMenuState = BTL_SUBMENU_STATE_INIT;
    MovesCursorPos = MovesPrevSelected;
    MovesPrevCursorPos = MovesPrevSelected;
    MovesMenuLines = MovesOptionCount;
    MovesVisibleStart = 0;

    if (MovesMenuLines > MENU_MAX_VISIBLE) {
        MovesMenuLines = MENU_MAX_VISIBLE;
    }

    MovesVisibleEnd = MENU_MAX_VISIBLE;
    if (MovesOptionCount < MENU_MAX_VISIBLE) {
        MovesVisibleEnd = MovesOptionCount;
    }

    MovesTextAlpha = 255;
    MovesDescVisible = true;

    if (MovesPrevCursorPos < 0) {
        MovesVisibleStart = MovesPrevCursorPos;
    }
    if (MovesPrevCursorPos >= MovesVisibleEnd) {
        MovesVisibleStart = MovesPrevCursorPos + 1 - MovesMenuLines;
    }

    MovesVisibleEnd = MovesVisibleStart + MENU_MAX_VISIBLE;
    if (MovesVisibleEnd > MovesOptionCount) {
        MovesVisibleEnd = MovesOptionCount;
    }

    MovesScrollOffset = -MovesVisibleStart * MENU_LINE_HEIGHT;
    MovesCursorOffset = (MovesPrevCursorPos - MovesVisibleStart) * MENU_LINE_HEIGHT;
    SelectedMovesIndex = 0;
}

void btl_submenu_moves_hide(void) {
    MovesMenuState = BTL_SUBMENU_STATE_HIDE_INIT;
}

void btl_submenu_moves_destroy(void) {
    s32 i;

    set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_HIDE);

    if (!UsingSpiritsSubmenu) {
        set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_HIDE);
        set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_HIDE);
    } else {
        set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_HIDE);
        set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_HIDE);
    }

    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);

    for (i = 0; i < MovesOptionCount; i++) {
        hud_element_free(MovesOptionHIDs[i]);
    }

    hud_element_free(HID_MovesCursor);
    hud_element_free(HID_MovesArrowUp);
    hud_element_free(HID_MovesArrowDown);
    hud_element_free(HID_MovesTitle);

    for (i = 0; i < MovesOptionCount; i++) {
        hud_element_free(MovesOptionCostHIDs[i]);
    }
}

void btl_submenu_moves_resume_choose(void) {
    s32* moveOptionIconIDs;
    s32* moveOptionCostUnitIconIDs;
    s32 i;

    moveOptionIconIDs = MovesOptionHIDs;

    for (i = 0; i < MovesOptionCount; i++) {
        hud_element_set_tint(moveOptionIconIDs[i], 255, 255, 255);
    }

    hud_element_set_tint(HID_MovesCursor, 255, 255, 255);
    hud_element_set_tint(HID_MovesArrowUp, 255, 255, 255);
    hud_element_set_tint(HID_MovesArrowDown, 255, 255, 255);
    hud_element_set_tint(HID_MovesTitle, 255, 255, 255);

    moveOptionCostUnitIconIDs = MovesOptionCostHIDs;

    for (i = 0; i < MovesOptionCount; i++) {
        hud_element_set_tint(moveOptionCostUnitIconIDs[i], 255, 255, 255);
    }

    hud_element_set_script(HID_MovesCursor, &HES_AnimatedHandPointer);
    set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_TRANSPARENT);

    if (!UsingSpiritsSubmenu) {
        set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_TRANSPARENT);
        set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_TRANSPARENT);
    } else {
        set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_TRANSPARENT);
        set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_TRANSPARENT);
    }

    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
    MovesTextColor = MSG_PAL_STANDARD;
    MovesDescVisible = true;
    MovesTextAlpha = 255;
    MovesMenuState = BTL_SUBMENU_STATE_CHOOSING;
}

void btl_submenu_moves_restore_choose(void) {
    s32* moveOptionIconIDs;
    s32* moveOptionCostUnitIconIDs;
    s32 i;

    set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_TRANSPARENT);

    if (!UsingSpiritsSubmenu) {
        set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_TRANSPARENT);
        set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_TRANSPARENT);
    } else {
        set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_TRANSPARENT);
        set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_TRANSPARENT);
    }
    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);

    moveOptionIconIDs = MovesOptionHIDs;

    for (i = 0; i < MovesOptionCount; i++) {
        hud_element_set_tint(moveOptionIconIDs[i], 255, 255, 255);
    }

    hud_element_set_tint(HID_MovesCursor, 255, 255, 255);
    hud_element_set_tint(HID_MovesArrowUp, 255, 255, 255);
    hud_element_set_tint(HID_MovesArrowDown, 255, 255, 255);
    hud_element_set_tint(HID_MovesTitle, 255, 255, 255);

    moveOptionCostUnitIconIDs = MovesOptionCostHIDs;

    for (i = 0; i < MovesOptionCount; i++) {
        hud_element_set_tint(moveOptionCostUnitIconIDs[i], 255, 255, 255);
    }

    hud_element_set_script(HID_MovesCursor, &HES_AnimatedHandPointer);
    MovesTextColor = MSG_PAL_STANDARD;
    MovesDescVisible = true;
    MovesMenuState = BTL_SUBMENU_STATE_RESTORE;
}

// reopen submenu in a locked/selected state
// sets state to LOCK; next update switches to SELECT (grayed out and non-interactive)
// use this when the menu should be visibile, but in the background of another menu
void btl_submenu_moves_restore_locked(void) {
    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
    MovesMenuState = BTL_SUBMENU_STATE_LOCK;
}

s32 btl_submenu_moves_update(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    s32 x, y;
    s32 msgWidth;
    s32 msgHeight;
    s32 msgID;
    s32 cond;
    HudElemID hid;
    s32 i;
    s32 j;

    switch (MovesMenuState) {
        case BTL_SUBMENU_STATE_INIT:
            MovesScrollOffset = -MovesVisibleStart * MENU_LINE_HEIGHT;
            MovesCursorOffset = (MovesCursorPos - MovesVisibleStart) * MENU_LINE_HEIGHT;
            MovesMenuPosX = 20;
            MovesMenuPosY = 68;

            for (i = 0; i < MovesOptionCount; i++) {
                MovesOptionIndexMap[i] = i;
            }

            if (!UsingSpiritsSubmenu) {
                for (i = 0; i < (MovesOptionCount - 1); i++) {
                    for (j = i + 1; j < MovesOptionCount; j++) {
                        s32 temp1 = MovesOptionIndexMap[i];
                        s32 temp2 = MovesOptionIndexMap[j];

                        if (MovesOptionSortPriority[temp1] < MovesOptionSortPriority[temp2]) {
                            continue;
                        }

                        if (
                            MovesOptionSortPriority[temp1] != MovesOptionSortPriority[temp2] ||
                            ((MovesOptionDisplayCosts[temp1] >= MovesOptionDisplayCosts[temp2]) &&
                            (MovesOptionDisplayCosts[temp1] != MovesOptionDisplayCosts[temp2] ||
                                MovesOptionBPCosts[temp1] >= MovesOptionBPCosts[temp2]))
                        )
                        {
                            s32 swapTemp = MovesOptionIndexMap[i];
                            MovesOptionIndexMap[i] = MovesOptionIndexMap[j];
                            MovesOptionIndexMap[j] = swapTemp;
                        }
                    }
                }
            }

            for (i = 0; i < MovesOptionCount; i++) {
                hid = hud_element_create(MovesOptionHudScripts[MovesOptionIndexMap[i]]);
                MovesOptionHIDs[i] = hid;
                hud_element_set_scale(hid, 0.45f);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX | HUD_ELEMENT_FLAG_MANUAL_RENDER);
            }

            hid = hud_element_create(&HES_AnimatedHandPointer);
            HID_MovesCursor = hid;
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DROP_SHADOW | HUD_ELEMENT_FLAG_MANUAL_RENDER);
            hud_element_set_render_pos(hid, MovesMenuPosX, MovesMenuPosY);

            hid = hud_element_create(&HES_GreenArrowUp);
            HID_MovesArrowUp = hid;
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DROP_SHADOW | HUD_ELEMENT_FLAG_MANUAL_RENDER);
            hud_element_set_render_pos(hid, MovesMenuPosX + 39, MovesMenuPosY - 7);

            hid = hud_element_create(&HES_GreenArrowDown);
            HID_MovesArrowDown = hid;
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DROP_SHADOW | HUD_ELEMENT_FLAG_MANUAL_RENDER);
            hud_element_set_render_pos(hid, MovesMenuPosX + 39, MovesMenuPosY + 78);

            if (!UsingSpiritsSubmenu) {
                hid = hud_element_create(&HES_StatusFlower);
                HID_MovesTitle = hid;
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);
            } else {
                hid = hud_element_create(&HES_MenuStarPower);
                HID_MovesTitle = hid;
                hud_element_set_scale(hid, 0.75f);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);
            }
            hud_element_set_render_pos(hid, MovesMenuPosX + 56, MovesMenuPosY);

            for (i = 0; i < MovesOptionCount; i++) {
                if (!UsingSpiritsSubmenu) {
                    switch (MovesOptionDiscountColors[i]) {
                        case 0:
                            hid = hud_element_create(&HES_FPCost);
                            MovesOptionCostHIDs[i] = hid;
                            break;
                        case 1:
                            hid = hud_element_create(&HES_FPCostReduced);
                            MovesOptionCostHIDs[i] = hid;
                            break;
                        default:
                            hid = hud_element_create(&HES_FPCostReducedTwice);
                            MovesOptionCostHIDs[i] = hid;
                            break;
                    }
                } else {
                    switch (MovesOptionDiscountColors[i]) {
                        case 0:
                            hid = hud_element_create(&HES_POWCost);
                            MovesOptionCostHIDs[i] = hid;
                            break;
                        case 1:
                            hid = hud_element_create(&HES_POWCostReduced);
                            MovesOptionCostHIDs[i] = hid;
                            break;
                        default:
                            hid = hud_element_create(&HES_POWCostReducedTwice);
                            MovesOptionCostHIDs[i] = hid;
                            break;
                    }
                }
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);
                hud_element_set_render_pos(hid, MovesMenuPosX + 56, MovesMenuPosY);
            }

            MovesTextColor = MSG_PAL_STANDARD;
            x = MovesMenuPosX;
            y = MovesMenuPosY;
            if (!UsingSpiritsSubmenu) {
                set_window_properties(WIN_BTL_MOVES_MENU, x, y, 150, (MovesMenuLines * MENU_LINE_HEIGHT) + 28, 0, btl_menu_moves_draw_content, nullptr, -1);
                set_window_properties(WIN_BTL_MOVES_TITLE, x + 16, y - 6, 90, 16, 1, btl_menu_moves_show_title, nullptr, -1);
                set_window_properties(WIN_BTL_MOVES_ICON, x + 114, y - 12, 32, 32, 1, btl_menu_moves_show_icon, nullptr, -1);
            } else {
                set_window_properties(WIN_BTL_MOVES_MENU, x, y, 144, (MovesMenuLines * MENU_LINE_HEIGHT) + 28, 0, btl_menu_moves_draw_content, nullptr, -1);
                set_window_properties(WIN_BTL_SPIRITS_TITLE, x + 10, y - 6, 100, 16, 1, btl_menu_moves_show_title, 0, -1);
                set_window_properties(WIN_BTL_SPIRITS_ICON, x + 110, y - 12, 32, 35, 1, btl_menu_moves_show_icon, 0, -1);
            }

            set_window_properties(WIN_BTL_DESC_BOX, 20, 186, 280, 32, WINDOW_PRIORITY_20, btl_menu_moves_show_desc, nullptr, -1);
            set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_SHOW);
            if (!UsingSpiritsSubmenu) {
                set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_SHOW);
                set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_SHOW);
            } else {
                set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_SHOW);
                set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_SHOW);
            }
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);

            do {
                cond = false;
                if (MovesCursorPos >= (MovesVisibleStart + MovesVisibleEnd) - 1) {
                    MovesVisibleStart++;
                    if (MovesVisibleStart > MovesOptionCount - MENU_MAX_VISIBLE) {
                        MovesVisibleStart = MovesOptionCount - MENU_MAX_VISIBLE;
                        if (MovesVisibleStart < 0) {
                            MovesVisibleStart = 0;
                        }
                    } else {
                        cond = true;
                    }
                }
            } while (cond);

            MovesMenuState = BTL_SUBMENU_STATE_CHOOSING;
            MovesVisibleEnd = MovesVisibleStart + MENU_MAX_VISIBLE;
            MovesScrollOffset = -MovesVisibleStart * MENU_LINE_HEIGHT;
            MovesCursorOffset = (MovesCursorPos - MovesVisibleStart) * MENU_LINE_HEIGHT;
            break;
        case BTL_SUBMENU_STATE_CHOOSING:
            MovesPrevCursorPos = MovesCursorPos;

            // only wrap selection on stick press, not when held
            if (battleStatus->curButtonsHeld & (BUTTON_STICK_UP | BUTTON_Z)) {
                if (MovesCursorPos > 0) {
                    MovesCursorPos--;
                } else if (battleStatus->curButtonsPressed & (BUTTON_STICK_UP | BUTTON_Z)) {
                    MovesCursorPos--;
                }
            }

            if (battleStatus->curButtonsHeld & (BUTTON_STICK_DOWN | BUTTON_R)) {
                if (MovesCursorPos < MovesOptionCount - 1) {
                    MovesCursorPos++;
                } else if (battleStatus->curButtonsPressed & (BUTTON_STICK_DOWN | BUTTON_R)) {
                    MovesCursorPos++;
                }
            }

            // wrap the selected index
            if (MovesCursorPos < 0) {
                MovesCursorPos = MovesOptionCount - 1;
            }
            if (MovesOptionCount - 1 < MovesCursorPos) {
                MovesCursorPos = 0;
            }

            if (MovesPrevCursorPos != MovesCursorPos) {
                hud_element_set_scale(MovesOptionHIDs[MovesPrevCursorPos], 0.45f);
                sfx_play_sound(SOUND_MENU_CHANGE_SELECTION);
            }

            if (MovesCursorPos < MovesVisibleStart + 1) {
                MovesVisibleStart--;
                if (MovesVisibleStart < 0) {
                    MovesVisibleStart = 0;
                }
            }

            if (MovesCursorPos >= (MovesVisibleEnd - 1)) {
                MovesVisibleStart++;
                if (MovesVisibleStart > MovesOptionCount - MENU_MAX_VISIBLE) {
                    MovesVisibleStart = MovesOptionCount - MENU_MAX_VISIBLE;
                    if (MovesVisibleStart < 0) {
                        MovesVisibleStart = 0;
                    }
                }
            }

            MovesVisibleEnd = MovesVisibleStart + MENU_MAX_VISIBLE;
            if (battleStatus->curButtonsPressed & BUTTON_A) {
                if (MovesOptionEnabled[MovesOptionIndexMap[MovesCursorPos]] == 1) {
                    sfx_play_sound(SOUND_MENU_NEXT);
                    MovesMenuState = BTL_SUBMENU_STATE_SELECT;
                } else {
                    sfx_play_sound(SOUND_MENU_ERROR);
                    MovesErrorCode = MovesOptionError[MovesOptionIndexMap[MovesCursorPos]];
                    MovesMenuState = BTL_SUBMENU_STATE_ERROR_INIT;
                }
                break;
            }

            if (battleStatus->curButtonsPressed & BUTTON_B) {
                sfx_play_sound(SOUND_MENU_BACK);
                btl_submenu_moves_destroy();
                MovesMenuState = BTL_SUBMENU_STATE_CANCEL;
            }
            break;
        case BTL_SUBMENU_STATE_SELECT:
            for (i = 0; i < MovesOptionCount; i++) {
                hid = MovesOptionHIDs[i];
                hud_element_set_tint(hid, 160, 160, 160);
            }
            hud_element_set_tint(HID_MovesCursor, 160, 160, 160);
            hud_element_set_tint(HID_MovesArrowUp, 160, 160, 160);
            hud_element_set_tint(HID_MovesArrowDown, 160, 160, 160);
            hud_element_set_tint(HID_MovesTitle, 160, 160, 160);

            for (i = 0; i < MovesOptionCount; i++) {
                hid = MovesOptionCostHIDs[i];
                hud_element_set_tint(hid, 160, 160, 160);
            }

            hud_element_set_script(HID_MovesCursor, &HES_HandPointer);
            MovesTextColor = MSG_PAL_0D;
            set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_DARKENED);
            if (!UsingSpiritsSubmenu) {
                set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_DARKENED);
                set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_DARKENED);
            } else {
                set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_DARKENED);
                set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_DARKENED);
            }
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);
            if (!UsingSpiritsSubmenu) {
                status_bar_stop_blinking_fp();
            } else {
                status_bar_stop_blinking_sp();
            }
            SelectedMovesIndex = MovesCursorPos;
            return MovesOptionIndexMap[MovesCursorPos] + 1;
        case BTL_SUBMENU_STATE_CANCEL:
            if (!UsingSpiritsSubmenu) {
                status_bar_stop_blinking_fp();
            } else {
                status_bar_stop_blinking_sp();
            }
            return POPUP_RESULT_CANCEL;
        case BTL_SUBMENU_STATE_HIDE_INIT:
            set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_HIDE);
            if (!UsingSpiritsSubmenu) {
                set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_HIDE);
                set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_HIDE);
            } else {
                set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_HIDE);
                set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_HIDE);
            }
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);
            if (!UsingSpiritsSubmenu) {
                status_bar_stop_blinking_fp();
            } else {
                status_bar_stop_blinking_sp();
            }
            MovesMenuState = BTL_SUBMENU_STATE_HIDE_HOLD;
            SelectedMovesIndex = MovesCursorPos;
            return MovesOptionIndexMap[MovesCursorPos] + 1;
        case BTL_SUBMENU_STATE_HIDE_HOLD:
            SelectedMovesIndex = MovesCursorPos;
            return MovesOptionIndexMap[MovesCursorPos] + 1;
        case BTL_SUBMENU_STATE_RESTORE:
            set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_SHOW);
            if (!UsingSpiritsSubmenu) {
                set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_SHOW);
                set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_SHOW);
            } else {
                set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_SHOW);
                set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_SHOW);
            }
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
            MovesMenuState = BTL_SUBMENU_STATE_CHOOSING;
            SelectedMovesIndex = MovesCursorPos;
            return MovesOptionIndexMap[MovesCursorPos] + 1;
        case BTL_SUBMENU_STATE_LOCK:
            set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_9);
            if (!UsingSpiritsSubmenu) {
                set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_9);
                set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_9);
            } else {
                set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_9);
                set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_9);
            }
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);
            MovesMenuState = BTL_SUBMENU_STATE_SELECT;
            break;
        case BTL_SUBMENU_STATE_ERROR_INIT:
            SelectedMovesIndex = -1;
            MovesMenuState = BTL_SUBMENU_STATE_ERROR_SHOW;
            return POPUP_RESULT_INVALID;
        case BTL_SUBMENU_STATE_ERROR_SHOW:
            set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_HIDE);
            if (!UsingSpiritsSubmenu) {
                set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_HIDE);
                set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_HIDE);
            } else {
                set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_HIDE);
                set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_HIDE);
            }
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);

            if (MovesErrorCode != 0) {
                msgID = MSG_Menus_Battle_CantSelectNow;
            } else if (UsingSpiritsSubmenu) {
                msgID = MSG_Menus_NotEnoughStarPower;
            } else {
                msgID = MSG_Menus_NotEnoughFP;
            }

            msgWidth = get_msg_width(msgID, 0) + 23;
            msgHeight = ErrorMessageHeight[get_msg_lines(msgID) - 1];
            x = (SCREEN_WIDTH / 2) - (msgWidth / 2);
            set_window_properties(WIN_BTL_POPUP, x, 80, msgWidth, msgHeight, 20, btl_menu_moves_show_error, nullptr, -1);
            set_window_update(WIN_BTL_POPUP, WINDOW_UPDATE_SHOW);
            MovesErrorTimer = 60;
            MovesMenuState = BTL_SUBMENU_STATE_ERROR_DONE;
            return POPUP_RESULT_INVALID;
        case BTL_SUBMENU_STATE_ERROR_DONE:
            if (gGameStatusPtr->pressedButtons[0] & (BUTTON_A | BUTTON_B)) {
                MovesErrorTimer = 0;
            }
            if (MovesErrorTimer != 0) {
                MovesErrorTimer--;
                return POPUP_RESULT_INVALID;
            }
            set_window_update(WIN_BTL_POPUP, WINDOW_UPDATE_HIDE);
            set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_SHOW);
            if (!UsingSpiritsSubmenu) {
                set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_SHOW);
                set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_SHOW);
            } else {
                set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_SHOW);
                set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_SHOW);
            }
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
            MovesMenuState = BTL_SUBMENU_STATE_CHOOSING;
            break;
    }
    return POPUP_RESULT_CHOOSING;
}

#if VERSION_IQUE
#define Y_VAR1 2
#define X_VAR1 104
#define X_VAR2 89
#else
#define Y_VAR1 0
#define X_VAR1 108
#define X_VAR2 93
#endif

void btl_menu_moves_draw_content(void* data, s32 x, s32 y) {
    s32 target, cur, delta;
    s32 x1, y1, x2, y2;
    s32 xPos, yPos;
    s32 cost, baseCost;
    s32 palette;
    s32 hid;
    s32 index;
    s32 i;

    switch (MovesMenuState) {
        case BTL_SUBMENU_STATE_SELECT:
        case BTL_SUBMENU_STATE_CHOOSING:
        case BTL_SUBMENU_STATE_HIDE_INIT:
        case BTL_SUBMENU_STATE_RESTORE:
        case BTL_SUBMENU_STATE_LOCK:
        case BTL_SUBMENU_STATE_ERROR_INIT:
        case BTL_SUBMENU_STATE_ERROR_SHOW:
            // simple midpoint easing, move half the distance each frame
            target = -MovesVisibleStart * MENU_LINE_HEIGHT;
            cur = MovesScrollOffset;
            delta = (target - cur) * 0.5;
            MovesScrollOffset = (delta != 0) ? cur + delta : target;

            x1 = x + 2;
            x2 = x + 153;
            y1 = y + 18;
            y2 = y + 19 + (MovesMenuLines * MENU_LINE_HEIGHT);
            gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, x1, y1, x2, y2);

            xPos = x + 31;
            yPos = y + 19 + MovesScrollOffset;

            for (i = 0; i < MovesOptionCount; i++) {
                // find the array index for current list display index
                index = MovesOptionIndexMap[i];

                if (i >= MovesVisibleStart - 1 && MovesVisibleStart + MovesMenuLines >= i) {
                    palette = MovesTextColor;

                    if (MovesOptionEnabled[index] <= 0) {
                        palette = MSG_PAL_0B;
                    }

                    if (MovesOptionNames[index] >= 0) {
                        draw_msg(
                            MovesOptionNames[index], xPos, yPos - Y_VAR1, MovesTextAlpha, palette, DRAW_MSG_STYLE_MENU
                        );
                    }

                    baseCost = MovesOptionDisplayCosts[index];
                    cost = baseCost - MovesOptionDiscounts[index];

                    if (baseCost != 0 && cost <= 0) {
                        cost = 1;
                    }

                    if (UsingSpiritsSubmenu ) {
                        if (i == MovesCursorPos) {
                            if (cost == 0 || MovesOptionEnabled[index] <= 0) {
                                status_bar_stop_blinking_sp();
                            } else {
                                status_bar_start_blinking_sp_bars(MovesOptionDisplayCosts[index]);
                            }
                        }
                    } else {
                        if (i == MovesCursorPos) {
                            if (cost == 0 || MovesOptionEnabled[index] <= 0) {
                                status_bar_stop_blinking_fp();
                            } else {
                                status_bar_start_blinking_fp();
                            }
                        }
                    }

                    switch (MovesOptionDiscountColors[i]) {
                        case 0:
                            palette = MSG_PAL_STANDARD;
                            break;
                        case 1:
                            palette = MSG_PAL_37;
                            break;
                        default:
                            palette = MSG_PAL_38;
                            break;
                    }

                    if (MovesOptionEnabled[index] <= 0) {
                        palette = MSG_PAL_0B;
                    }

                    if (MovesOptionDisplayCosts[index] != 0) {
                        hid = MovesOptionCostHIDs[i];

                        if (UsingSpiritsSubmenu) {
                            draw_number(
                                cost, xPos + X_VAR2, yPos, DRAW_NUMBER_CHARSET_THIN, palette, MovesTextAlpha,
                                DRAW_NUMBER_STYLE_MONOSPACE | DRAW_NUMBER_STYLE_ALIGN_RIGHT
                            );
                            if (MovesOptionEnabled[index] <= 0) {
                                hud_element_set_script(hid, &HES_NotEnoughPOW);
                            }
                            hud_element_set_render_pos(hid, xPos + 102, yPos + 7);
                        } else {
                            draw_number(
                                cost, xPos + X_VAR1, yPos, DRAW_NUMBER_CHARSET_THIN, palette, MovesTextAlpha,
                                DRAW_NUMBER_STYLE_MONOSPACE | DRAW_NUMBER_STYLE_ALIGN_RIGHT
                            );
                            if (MovesOptionEnabled[index] <= 0) {
                                hud_element_set_script(hid, &HES_NotEnoughFP);
                            }
                            hud_element_set_render_pos(hid, xPos + 116, yPos + 7);
                        }
                        hud_element_set_alpha(hid, MovesTextAlpha);
                        hud_element_draw_without_clipping(hid);
                    }
                }
                yPos += MENU_LINE_HEIGHT;
            }

            // draw option icons
            xPos = x + 24;
            yPos = y + 24 + MovesScrollOffset;

            for (i = 0; i < MovesOptionCount; i++) {
                if (i < MovesVisibleStart - 1) {
                    yPos += MENU_LINE_HEIGHT;
                } else if (MovesVisibleStart + MovesMenuLines < i) {
                    yPos += MENU_LINE_HEIGHT;
                } else {
                    hid = MovesOptionHIDs[i];
                    hud_element_set_render_pos(hid, xPos, yPos);
                    hud_element_set_alpha(hid, MovesTextAlpha);
                    hud_element_draw_without_clipping(hid);
                    yPos += MENU_LINE_HEIGHT;
                }
            }

            // instant snap to target, no easing
            target = (MovesCursorPos - MovesVisibleStart) * MENU_LINE_HEIGHT;
            cur = MovesCursorOffset;
            delta = (target - cur) * 1.0;
            MovesCursorOffset =  (delta != 0) ? cur + delta : target;

            // draw the cursor
            xPos = x + 10;
            yPos = y + 26 + MovesCursorOffset;

            hid = HID_MovesCursor;
            hud_element_set_render_pos(hid, xPos, yPos);
            hud_element_set_alpha(hid, MovesTextAlpha);
            hud_element_draw_without_clipping(hid);

            // draw nav arrows
            if (MovesVisibleStart > 0) {
                hid = HID_MovesArrowUp;
                hud_element_set_render_pos(hid, x + 72, y + 15);
                hud_element_set_alpha(hid, MovesTextAlpha);
                hud_element_draw_clipped(hid);
            }
            if (MovesVisibleEnd < MovesOptionCount) {
                hid = HID_MovesArrowDown;
                hud_element_set_render_pos(hid, x + 72, y + 100);
                hud_element_set_alpha(hid, MovesTextAlpha);
                hud_element_draw_clipped(hid);
            }

            if (MovesMenuState == BTL_SUBMENU_STATE_SELECT) {
                if (!UsingSpiritsSubmenu) {
                    status_bar_stop_blinking_fp();
                } else {
                    status_bar_stop_blinking_sp();
                }
            }
            break;
    }
}

void btl_menu_moves_show_title(void* data, s32 x, s32 y) {
    s32 msgID;
    s32 posX;
    s32 posY;
    s32 opacity;
    s32 palette;

    if (!UsingSpiritsSubmenu) {
        msgID = MSG_Menus_Abilities;
        posX = x + 16;
        posY = y + 2;
        opacity = MovesTextAlpha;
        palette = MSG_PAL_30;
    } else {
        msgID = MSG_Menus_StarSpirits;
        posX = x + 6;
        posY = y + 2;
        opacity = MovesTextAlpha;
        palette = MSG_PAL_31;
    }
    draw_msg(msgID, posX, posY, opacity, palette, DRAW_MSG_STYLE_MENU);
}

void btl_menu_moves_show_icon(void* data, s32 x, s32 y) {
    s32 hid = HID_MovesTitle;

    hud_element_set_render_pos(hid, x + 16, y + 15);
    hud_element_set_alpha(hid, MovesTextAlpha);
    hud_element_draw_clipped(hid);
}

void btl_menu_moves_show_desc(void* data, s32 x, s32 y) {
    switch (MovesMenuState) {
        case BTL_SUBMENU_STATE_SELECT:
        case BTL_SUBMENU_STATE_CHOOSING:
        case BTL_SUBMENU_STATE_HIDE_INIT:
        case BTL_SUBMENU_STATE_RESTORE:
        case BTL_SUBMENU_STATE_LOCK:
            if (MovesDescVisible) {
                draw_msg(MovesOptionDesc[MovesOptionIndexMap[MovesCursorPos]],
                            x + 8, y, MovesTextAlpha, MovesTextColor, 0);
            }
            break;
    }
}

void btl_menu_moves_show_error(void* data, s32 posX, s32 posY) {
    s32 msgID;

    posX += 11;
    posY += 6;

    if (MovesErrorCode != 0) {
        msgID = MSG_Menus_Battle_CantSelectNow;
    } else if (UsingSpiritsSubmenu) {
        msgID = MSG_Menus_NotEnoughStarPower;
    } else {
        msgID = MSG_Menus_NotEnoughFP;
    }
    posY += ErrorMessageAdjustY[get_msg_lines(msgID) - 1];
    draw_msg(msgID, posX, posY, 255, MSG_PAL_0F, 0);
}
