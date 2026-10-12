#include "battle/battle.h"

extern u8 D_PAL_802AB4C8[4];
#include "hud_element.h"

#define MENU_CAPACITY 6
#define MENU_LINE_HEIGHT 13
#define MENU_MAX_VISIBLE 6

enum {
    BTL_SUBMENU_STATE_CANCEL                = -2, // selection is canceled
    BTL_SUBMENU_STATE_SELECT                = -1, // a result is selected
    BTL_SUBMENU_STATE_INIT                  = 0,  // build and initialize the menu
    BTL_SUBMENU_STATE_CHOOSING              = 1,  // selecting an option
    BTL_SUBMENU_STATE_HIDE_INIT             = 10,
    BTL_SUBMENU_STATE_HIDE_HOLD             = 11,
    BTL_SUBMENU_STATE_RESTORE               = 20,
    BTL_SUBMENU_STATE_LOCK                  = 30,
    BTL_SUBMENU_STATE_ERROR_INIT            = 40,
    BTL_SUBMENU_STATE_ERROR_SHOW            = 41,
    BTL_SUBMENU_STATE_ERROR_DONE            = 42,
};

extern HudScript HES_GreenArrowDown;
extern HudScript HES_GreenArrowUp;
extern HudScript HES_HandPointer;

BSS HudElemID HID_StratsArrowUp;
BSS HudElemID HID_StratsArrowDown;
BSS HudElemID HID_StratsCursor;

BSS s16 StratsMenuPosX;
BSS s16 StratsMenuPosY;

BSS s8 StratsMenuState;
BSS s32 StratsPrevSelected; // index of previously selected option, set by caller before initializing the menu

BSS HudScript* StratsOptionHudScripts[MENU_CAPACITY];
BSS s32 StratsOptionHIDs[MENU_CAPACITY];
BSS s32 StratsOptionNames[MENU_CAPACITY];
BSS s32 StratsOptionMenuTypes[MENU_CAPACITY];
BSS b32 StratsOptionEnabled[MENU_CAPACITY];
BSS s32 StratsOptionMessage[MENU_CAPACITY];
BSS s32 StratsOptionError[MENU_CAPACITY];
BSS s32 StratsOptionCount;

BSS s8 StratsCursorPos;
BSS s8 StratsPrevCursorPos;
BSS s8 StratsVisibleStart;
BSS s8 StratsVisibleEnd;
BSS s8 StratsMenuLines;
BSS s8 StratsDescVisible;
BSS s16 StratsScrollOffset;
BSS s16 StratsCursorOffset;

BSS s8 ShowingErrorMessage;
BSS s16 StratsErrorCode;
BSS s16 StratsErrorTimer;

BSS s8 StratsTextColor;
BSS s32 StratsTextAlpha;

void btl_menu_strats_draw_content(void* data, s32 x, s32 y);
void btl_menu_strats_show_title(void* data, s32 x, s32 y);
void btl_menu_strats_show_desc(void* data, s32 x, s32 y);
void btl_menu_strats_show_error(void* data, s32 x, s32 y);

void btl_menu_strats_init(void) {
    StratsMenuState = BTL_SUBMENU_STATE_INIT;
    StratsCursorPos = StratsPrevSelected;
    StratsPrevCursorPos = StratsPrevSelected;
    StratsMenuLines = StratsOptionCount;
    StratsVisibleStart = 0;

    if (StratsMenuLines > MENU_MAX_VISIBLE) {
        StratsMenuLines = MENU_MAX_VISIBLE;
    }

    StratsVisibleEnd = MENU_MAX_VISIBLE;
    if (StratsOptionCount < MENU_MAX_VISIBLE) {
        StratsVisibleEnd = StratsOptionCount;
    }

    StratsTextAlpha = 255;
    StratsDescVisible = true;

    if (StratsPrevCursorPos < 0) {
        StratsVisibleStart = StratsPrevCursorPos;
    }
    if (StratsPrevCursorPos >= StratsVisibleEnd) {
        StratsVisibleStart = StratsPrevCursorPos + 1 - StratsMenuLines;
    }

    StratsVisibleEnd = StratsVisibleStart + MENU_MAX_VISIBLE;
    if (StratsVisibleEnd > StratsOptionCount) {
        StratsVisibleEnd = StratsOptionCount;
    }

    StratsScrollOffset = -StratsVisibleStart * MENU_LINE_HEIGHT;
    StratsCursorOffset = (StratsPrevCursorPos - StratsVisibleStart) * MENU_LINE_HEIGHT;
    ShowingErrorMessage = false;
}

void btl_submenu_strats_hide(void) {
    StratsMenuState = BTL_SUBMENU_STATE_HIDE_INIT;
}

void btl_submenu_strats_destroy(void) {
    s32 i;

    set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_HIDE);
    set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_HIDE);
    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);

    for (i = 0; i < StratsOptionCount; i++) {
        hud_element_free(StratsOptionHIDs[i]);
    }

    hud_element_free(HID_StratsCursor);
    hud_element_free(HID_StratsArrowUp);
    hud_element_free(HID_StratsArrowDown);
}

// show submenu after a popup was canceled (Change Partner).
// restores colors/hand pointer and returns directly to CHOOSE
void btl_submenu_strats_resume_choose(void) {
    s32 i;

    for (i = 0; i < StratsOptionCount; i++) {
        hud_element_set_tint(StratsOptionHIDs[i], 255, 255, 255);
    }

    hud_element_set_tint(HID_StratsCursor, 255, 255, 255);
    hud_element_set_tint(HID_StratsArrowUp, 255, 255, 255);
    hud_element_set_tint(HID_StratsArrowDown, 255, 255, 255);
    hud_element_set_script(HID_StratsCursor, &HES_AnimatedHandPointer);
    set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_TRANSPARENT);
    set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_TRANSPARENT);
    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
    StratsTextColor = MSG_PAL_STANDARD;
    StratsTextAlpha = 255;
    StratsDescVisible = true;
    StratsMenuState = BTL_SUBMENU_STATE_CHOOSING;
}

// show submenu after it was hidden (eg, after handing control to select target)
// sets state to RESTORE; next update shows windows and returns to CHOOSE
void btl_submenu_strats_restore_choose(void) {
    s32 i;

    set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_TRANSPARENT);
    set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_TRANSPARENT);
    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);

    for (i = 0; i < StratsOptionCount; i++) {
        hud_element_set_tint(StratsOptionHIDs[i], 255, 255, 255);
    }

    hud_element_set_tint(HID_StratsCursor, 255, 255, 255);
    hud_element_set_tint(HID_StratsArrowUp, 255, 255, 255);
    hud_element_set_tint(HID_StratsArrowDown, 255, 255, 255);
    hud_element_set_script(HID_StratsCursor, &HES_AnimatedHandPointer);
    StratsTextColor = MSG_PAL_STANDARD;
    StratsDescVisible = true;
    StratsMenuState = BTL_SUBMENU_STATE_RESTORE;
}

// reopen submenu in a locked/selected state
// sets state to LOCK; next update switches to SELECT (grayed out and non-interactive)
// use this when the menu should be visibile, but in the background of another menu
void btl_submenu_strats_restore_locked(void) {
    set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_TRANSPARENT);
    set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_TRANSPARENT);
    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
    StratsMenuState = BTL_SUBMENU_STATE_LOCK;
}

s32 btl_submenu_strats_update(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    HudElemID hid;
    s32 x, y;
    s32 width;
    s32 msgID;
    s32 i;

    switch (StratsMenuState) {
        case BTL_SUBMENU_STATE_INIT:
            StratsScrollOffset = -StratsVisibleStart * MENU_LINE_HEIGHT;
            StratsCursorOffset = (StratsCursorPos - StratsVisibleStart) * MENU_LINE_HEIGHT;
            StratsMenuPosX = 20;
            StratsMenuPosY = 68;

            for (i = 0; i < StratsOptionCount; i++) {
                StratsOptionHIDs[i] = hid = hud_element_create(StratsOptionHudScripts[i]);
                hud_element_set_scale(hid, 0.45f);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX | HUD_ELEMENT_FLAG_MANUAL_RENDER);
            }

            HID_StratsCursor = hid = hud_element_create(&HES_AnimatedHandPointer);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DROP_SHADOW | HUD_ELEMENT_FLAG_MANUAL_RENDER);
            hud_element_set_render_pos(hid, StratsMenuPosX, StratsMenuPosY);

            HID_StratsArrowUp = hid = hud_element_create(&HES_GreenArrowUp);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DROP_SHADOW | HUD_ELEMENT_FLAG_MANUAL_RENDER);
            hud_element_set_render_pos(hid, StratsMenuPosX + 39, StratsMenuPosY - 7);

            HID_StratsArrowDown = hid = hud_element_create(&HES_GreenArrowDown);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DROP_SHADOW | HUD_ELEMENT_FLAG_MANUAL_RENDER);
            hud_element_set_render_pos(hid, StratsMenuPosX + 39, StratsMenuPosY + 78);

            StratsTextColor = MSG_PAL_STANDARD;
            x = StratsMenuPosX;
            y = StratsMenuPosY;
            if (gGameLanguage == LANGUAGE_EN) {
                set_window_properties(WIN_BTL_STRATS_MENU, x, y, 144, (StratsMenuLines * MENU_LINE_HEIGHT) + 26, 0, btl_menu_strats_draw_content, nullptr, -1);
                set_window_properties(WIN_BTL_STRATS_TITLE, x + 18, y - 6, 108, 16, 1, btl_menu_strats_show_title, nullptr, -1);
            } else {
                // PAL sizes the title to the message, and the menu per language.
                s32 titleWidth = get_msg_width(MSG_Menus_Strategies, 0) + 32;

                set_window_properties(WIN_BTL_STRATS_MENU, x, y, D_PAL_802AB4C8[gGameLanguage], (StratsMenuLines * MENU_LINE_HEIGHT) + 26, 0, btl_menu_strats_draw_content, nullptr, -1);
                set_window_properties(WIN_BTL_STRATS_TITLE, x + (D_PAL_802AB4C8[gGameLanguage] - titleWidth) / 2, y - 6, titleWidth, 16, 1, btl_menu_strats_show_title, nullptr, -1);
            }
            x = 20;
            y = 186;
            set_window_properties(WIN_BTL_DESC_BOX, x, y, 280, 32, WINDOW_PRIORITY_20, btl_menu_strats_show_desc, nullptr, -1);
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
            StratsMenuState = BTL_SUBMENU_STATE_CHOOSING;
            return POPUP_RESULT_CHOOSING;
        case BTL_SUBMENU_STATE_CHOOSING:
            if (!ShowingErrorMessage) {
                StratsPrevCursorPos = StratsCursorPos;

                // only wrap selection on stick press, not when held
                if (battleStatus->curButtonsHeld & BUTTON_STICK_UP) {
                    if (StratsCursorPos > 0) {
                        StratsCursorPos--;
                    } else if (battleStatus->curButtonsPressed & BUTTON_STICK_UP) {
                        StratsCursorPos--;
                    }
                }

                if (battleStatus->curButtonsHeld & BUTTON_STICK_DOWN) {
                    if (StratsCursorPos < StratsOptionCount - 1) {
                        StratsCursorPos++;
                    } else if (battleStatus->curButtonsPressed & BUTTON_STICK_DOWN) {
                        StratsCursorPos++;
                    }
                }

                // wrap the selected index
                if (StratsCursorPos < 0) {
                    StratsCursorPos = StratsOptionCount - 1;
                }
                if (StratsOptionCount - 1 < StratsCursorPos) {
                    StratsCursorPos = 0;
                }

                if (StratsPrevCursorPos != StratsCursorPos) {
                    hud_element_set_scale(StratsOptionHIDs[StratsPrevCursorPos], 0.45f);
                    sfx_play_sound(SOUND_MENU_CHANGE_SELECTION);
                }

                if (StratsCursorPos < StratsVisibleStart) {
                    StratsVisibleStart = StratsCursorPos;
                }
                if (StratsCursorPos >= StratsVisibleEnd) {
                    StratsVisibleStart = StratsCursorPos + 1 - StratsMenuLines;
                }
                StratsVisibleEnd = StratsVisibleStart + MENU_MAX_VISIBLE;
                if (StratsVisibleEnd > StratsOptionCount) {
                    StratsVisibleEnd = StratsOptionCount;
                }

                if (battleStatus->curButtonsPressed & BUTTON_A) {
                    if (StratsOptionEnabled[StratsCursorPos]) {
                        sfx_play_sound(SOUND_MENU_NEXT);
                        StratsMenuState = BTL_SUBMENU_STATE_SELECT;
                    } else {
                        sfx_play_sound(SOUND_MENU_ERROR);
                        StratsMenuState = BTL_SUBMENU_STATE_ERROR_INIT;
                        StratsErrorCode = StratsOptionError[StratsCursorPos];
                    }
                } else if (battleStatus->curButtonsPressed & BUTTON_B) {
                    sfx_play_sound(SOUND_MENU_BACK);
                    btl_submenu_strats_destroy();
                    StratsMenuState = BTL_SUBMENU_STATE_CANCEL;
                }
            }
            return POPUP_RESULT_CHOOSING;
        case BTL_SUBMENU_STATE_SELECT:
            for (i = 0; i < StratsOptionCount; i++) {
                hud_element_set_tint(StratsOptionHIDs[i], 160, 160, 160);
            }
            hud_element_set_tint(HID_StratsCursor, 160, 160, 160);
            hud_element_set_tint(HID_StratsArrowUp, 160, 160, 160);
            hud_element_set_tint(HID_StratsArrowDown, 160, 160, 160);
            hud_element_set_script(HID_StratsCursor, &HES_HandPointer);
            StratsTextColor = MSG_PAL_0D;
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_DARKENED);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_DARKENED);
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);
            return StratsCursorPos + 1;
        case BTL_SUBMENU_STATE_CANCEL:
            return POPUP_RESULT_CANCEL;
        case BTL_SUBMENU_STATE_HIDE_INIT:
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_HIDE);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_HIDE);
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);
            StratsMenuState = BTL_SUBMENU_STATE_HIDE_HOLD;
            return StratsCursorPos + 1;
        case BTL_SUBMENU_STATE_HIDE_HOLD:
            return StratsCursorPos + 1;
        case BTL_SUBMENU_STATE_RESTORE:
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
            StratsMenuState = BTL_SUBMENU_STATE_CHOOSING;
            return StratsCursorPos + 1;
        case BTL_SUBMENU_STATE_LOCK:
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
            StratsMenuState = BTL_SUBMENU_STATE_SELECT;
            return POPUP_RESULT_CHOOSING;
        case BTL_SUBMENU_STATE_ERROR_INIT:
            StratsMenuState = BTL_SUBMENU_STATE_ERROR_SHOW;
            return POPUP_RESULT_INVALID;
        case BTL_SUBMENU_STATE_ERROR_SHOW:
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_HIDE);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_HIDE);
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);
            switch (StratsErrorCode) {
                case 0:
                    msgID = MSG_Menus_Battle_CantSwitch2;
                    break;
                case 1:
                    msgID = MSG_Menus_Battle_CantRunAway;
                    break;
                default:
                    msgID = MSG_Menus_Battle_CantRunAway;
                    break;
            }
            width = get_msg_width(msgID, 0) + 23;
            set_window_properties(WIN_BTL_POPUP, (SCREEN_WIDTH / 2) - (width / 2), 80, width, 28, 20, btl_menu_strats_show_error, nullptr, -1);
            set_window_update(WIN_BTL_POPUP, WINDOW_UPDATE_SHOW);
            StratsErrorTimer = 60;
            StratsMenuState = BTL_SUBMENU_STATE_ERROR_DONE;
            return POPUP_RESULT_INVALID;
        case BTL_SUBMENU_STATE_ERROR_DONE:
            if (gGameStatusPtr->pressedButtons[0] & (BUTTON_A | BUTTON_B)) {
                StratsErrorTimer = 0;
            }
            if (StratsErrorTimer != 0) {
                StratsErrorTimer--;
                return POPUP_RESULT_INVALID;
            }
            set_window_update(WIN_BTL_POPUP, WINDOW_UPDATE_HIDE);
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
            StratsMenuState = BTL_SUBMENU_STATE_CHOOSING;
            return POPUP_RESULT_CHOOSING;
    }
    return POPUP_RESULT_CHOOSING;
}

void btl_menu_strats_draw_content(void* data, s32 x, s32 y) {
    s32 target, cur, delta;
    s32 x1, x2, y1, y2;
    s32 xPos, yPos;
    s32 hid;
    s32 i;

    switch (StratsMenuState) {
        case BTL_SUBMENU_STATE_SELECT:
        case BTL_SUBMENU_STATE_CHOOSING:
        case BTL_SUBMENU_STATE_HIDE_INIT:
        case BTL_SUBMENU_STATE_RESTORE:
        case BTL_SUBMENU_STATE_LOCK:
        case BTL_SUBMENU_STATE_ERROR_INIT:
        case BTL_SUBMENU_STATE_ERROR_SHOW:
            // simple midpoint easing, move half the distance each frame
            target = -StratsVisibleStart * MENU_LINE_HEIGHT;
            cur = StratsScrollOffset;
            delta = (target - cur) * 0.5;
            StratsScrollOffset = (delta != 0) ? cur + delta : target;

            x1 = x + 4;
            x2 = x + 142;
            y1 = y + 18;
            y2 = y + 19 + (StratsMenuLines * MENU_LINE_HEIGHT);
            gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, x1, y1, x2, y2);

            // draw option messages
            xPos = x + 33;
            yPos = y + 19 + StratsScrollOffset;
            #if VERSION_IQUE
            yPos -= 3;
            #endif

            for (i = 0; i < StratsOptionCount; i++) {
                s32 palette = StratsTextColor;

                if (StratsOptionMenuTypes[i] == BTL_MENU_TYPE_CHANGE_PARTNER && is_ability_active(ABILITY_QUICK_CHANGE)) {
                    palette = MSG_PAL_37;
                }
                if (!StratsOptionEnabled[i]) {
                    palette = MSG_PAL_0B;
                }
                draw_msg(StratsOptionNames[i], xPos, yPos, StratsTextAlpha, palette, DRAW_MSG_STYLE_MENU);
                yPos += MENU_LINE_HEIGHT;
            }

            // draw option icons
            xPos = x + 24;
            yPos = y + 24 + StratsScrollOffset;

            for (i = 0; i < StratsOptionCount; i++) {
                hid = StratsOptionHIDs[i];
                hud_element_set_render_pos(hid, xPos, yPos);
                hud_element_set_alpha(hid, StratsTextAlpha);
                hud_element_draw_without_clipping(hid);
                yPos += MENU_LINE_HEIGHT;
            }

            // instant snap to target, no easing
            target = (StratsCursorPos - StratsVisibleStart) * MENU_LINE_HEIGHT;
            cur = StratsCursorOffset;
            delta = (target - cur) * 1.0;
            StratsCursorOffset = (delta != 0) ? cur + delta : target;

            // draw the cursor
            xPos = x + 10;
            yPos = y + 26 + StratsCursorOffset;

            hid = HID_StratsCursor;
            hud_element_set_render_pos(hid, xPos, yPos);
            hud_element_set_alpha(hid, StratsTextAlpha);
            hud_element_draw_clipped(hid);

            // draw nav arrows
            if (StratsVisibleStart > 0) {
                hid = HID_StratsArrowUp;
                hud_element_set_render_pos(hid, x + 67, y + 16);
                hud_element_set_alpha(hid, StratsTextAlpha);
                hud_element_draw_clipped(hid);
            }
            if (StratsVisibleEnd < StratsOptionCount) {
                hid = HID_StratsArrowDown;
                hud_element_set_render_pos(hid, x + 67, y + 100);
                hud_element_set_alpha(hid, StratsTextAlpha);
                hud_element_draw_clipped(hid);
            }
            break;
    }
}

void btl_menu_strats_show_title(void* data, s32 x, s32 y) {
    draw_msg(MSG_Menus_Strategies, x + 15, y + 2, StratsTextAlpha, MSG_PAL_33, DRAW_MSG_STYLE_MENU);
}

void btl_menu_strats_show_desc(void* data, s32 x, s32 y) {
    switch (StratsMenuState) {
        case BTL_SUBMENU_STATE_SELECT:
        case BTL_SUBMENU_STATE_CHOOSING:
        case BTL_SUBMENU_STATE_HIDE_INIT:
        case BTL_SUBMENU_STATE_RESTORE:
        case BTL_SUBMENU_STATE_LOCK:
            if (StratsDescVisible) {
                draw_msg(StratsOptionMessage[StratsCursorPos], x + 8, y, StratsTextAlpha, StratsTextColor, 0);
            }
            break;
    }
}

void btl_menu_strats_show_error(void* data, s32 x, s32 y) {
    s32 msgID;

    x += 11;
    y += 6;

    switch (StratsErrorCode) {
        case 0:
            msgID = MSG_Menus_Battle_CantSwitch2;
            break;
        case 1:
            msgID = MSG_Menus_Battle_CantRunAway;
            break;
        default:
            msgID = MSG_Menus_Battle_CantRunAway;
            break;
    }
    draw_msg(msgID, x, y, 255, MSG_PAL_0F, 0);
}
