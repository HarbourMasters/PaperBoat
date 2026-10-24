#include "common.h"
#include "filemenu.h"
#include "fio.h"
#include "game_modes.h"
#include "dx/config.h"
#include <string.h>
#include "port/patches/Patches.h"

#if VERSION_IQUE
#define DELETE_FILE_DELETE_X            20
#define DELETE_FILE_FILE_X              50
#define DELETE_FILE_NUMBER_X            93
#define DELETE_FILE_QMARK_X             92
#define COPY_FILE_NUMBER_X              49
#define COPY_CONFIRM_SUFFIX_X           49
#define START_GAME_START_WITH_X         37
#define START_GAME_FILE_X               100
#define START_GAME_NUMBER_X             142
#define START_GAME_QMARK_X              140
#define NUMBER_OFFSET_Y                 1
#else
#define DELETE_FILE_DELETE_X            10
#define DELETE_FILE_FILE_X              port_filemenu_layout(FM_LAYOUT_DELETE_CONFIRM_FILE_X, 60)
#define DELETE_FILE_NUMBER_X            port_filemenu_layout(FM_LAYOUT_DELETE_CONFIRM_NUMBER_X, 98)
#define DELETE_FILE_QMARK_X             port_filemenu_layout(FM_LAYOUT_DELETE_CONFIRM_QMARK_X, 99)
#define COPY_FILE_NUMBER_X              port_filemenu_layout(FM_LAYOUT_COPY_CONFIRM_NUMBER_X, 48)
#define COPY_CONFIRM_SUFFIX_X           port_filemenu_layout(FM_LAYOUT_COPY_CONFIRM_SUFFIX_X, 49)
#define START_GAME_START_WITH_X         10
#define START_GAME_FILE_X               port_filemenu_layout(FM_LAYOUT_START_FILE_X, 127)
#define START_GAME_NUMBER_X             port_filemenu_layout(FM_LAYOUT_START_NUMBER_X, 165)
#define START_GAME_QMARK_X              port_filemenu_layout(FM_LAYOUT_START_QMARK_X, 162)
#define NUMBER_OFFSET_Y                 0
#endif

u8 filemenu_yesno_gridData[] = {
    0, 1,
    0, 1,
    0, 1,
    0, 1,
};

MenuWindowBP filemenu_yesno_windowBPs[] = {
    {
        .windowID = WIN_FILES_CONFIRM_OPTIONS,
        .unk_01 = 0,
        .pos = { .x = 0, .y = 0 },
        .width = 0,
        .height = 0,
        .priority = WINDOW_PRIORITY_64,
        .fpDrawContents = &filemenu_yesno_draw_options_contents,
        .tab = nullptr,
        .parentID = -1,
        .fpUpdate = { WINDOW_UPDATE_HIDE },
        .extraFlags = 0,
        .style = { .customStyle = &filemenu_windowStyles[19] }
    },
    {
        .windowID = WIN_FILES_CONFIRM_PROMPT,
        .unk_01 = 0,
        .pos = { .x = 0, .y = 0 },
        .width = 0,
        .height = 0,
        .priority = WINDOW_PRIORITY_0,
        .fpDrawContents = &filemenu_yesno_draw_prompt_contents,
        .tab = nullptr,
        .parentID = WIN_FILES_CONFIRM_OPTIONS,
        .fpUpdate = { WINDOW_UPDATE_SHOW },
        .extraFlags = 0,
        .style = { .customStyle = &filemenu_windowStyles[19] }
    },
};

MenuPanel filemenu_yesno_menuBP = {
    .initialized = false,
    .col = 0,
    .row = 0,
    .selected = 0,
    .state = 0,
    .numCols = 1,
    .numRows = 2,
    .numPages = 0,
    .gridData = filemenu_yesno_gridData,
    .fpInit = &filemenu_yesno_init,
    .fpHandleInput = &filemenu_yesno_handle_input,
    .fpUpdate = &filemenu_yesno_update,
    .fpCleanup = &filemenu_yesno_cleanup
};

void filemenu_yesno_draw_options_contents(
    MenuPanel* menu,
    s32 baseX, s32 baseY,
    s32 width, s32 height,
    s32 opacity, s32 darkening
) {
    s32 xOffset1;
    s32 yOffset1;
    s32 xOffset2;
    s32 yOffset2;
    s32 cursorGoalXOffset;
    s32 cursorGoalYOffset;

    switch (menu->state) {
        case FM_CONFIRM_DELETE:
            xOffset1 = 28;
            yOffset1 = 4;
            xOffset2 = 28;
            yOffset2 = 21;
            break;
        case FM_CONFIRM_CREATE:
            xOffset1 = 28;
            yOffset1 = 4;
            xOffset2 = 28;
            yOffset2 = 21;
            break;
        case FM_CONFIRM_COPY:
            xOffset1 = 28;
            yOffset1 = 4;
            xOffset2 = 28;
            yOffset2 = 21;
            break;
        case FM_CONFIRM_START:
            xOffset1 = 28;
            yOffset1 = 4;
            xOffset2 = 28;
            yOffset2 = 21;
            break;
    }

    filemenu_draw_message(filemenu_get_menu_message(FILE_MESSAGE_YES), baseX + xOffset1, baseY + yOffset1, 255, MSG_PAL_WHITE, 0);
    filemenu_draw_message(filemenu_get_menu_message(FILE_MESSAGE_NO), baseX + xOffset2, baseY + yOffset2, 255, MSG_PAL_WHITE, 0);

    if (filemenu_currentMenu == FILE_MENU_CONFIRM) {
        if (menu->selected == 0) {
            cursorGoalXOffset = xOffset1 - 10;
            cursorGoalYOffset = yOffset1 + 8;
        } else {
            cursorGoalXOffset = xOffset2 - 10;
            cursorGoalYOffset = yOffset2 + 8;
        }
        filemenu_set_cursor_goal_pos(WIN_FILES_CONFIRM_OPTIONS, baseX + cursorGoalXOffset, baseY + cursorGoalYOffset);
    }
}

void filemenu_yesno_draw_prompt_contents(
    MenuPanel* menu,
    s32 baseX, s32 baseY,
    s32 width, s32 height,
    s32 opacity, s32 darkening
) {
    s32 selectedFile;
    s32 msgColor;
    s32 xOffset;
    s32 i;

    switch (menu->state) {
        case FM_CONFIRM_DELETE:
            filemenu_draw_message(filemenu_get_menu_message(FILE_MESSAGE_DELETE), baseX + DELETE_FILE_DELETE_X, baseY + 4, 0xFF, 0, 0);
            filemenu_draw_message(filemenu_get_menu_message(FILE_MESSAGE_FILE_22), baseX + DELETE_FILE_FILE_X, baseY + 4, 0xFF, 0, 0);
            draw_number(filemenu_menus[FILE_MENU_MAIN]->selected + 1, baseX + DELETE_FILE_NUMBER_X, baseY + 6 + NUMBER_OFFSET_Y, DRAW_NUMBER_CHARSET_NORMAL, MSG_PAL_WHITE, 0xFF, DRAW_NUMBER_STYLE_MONOSPACE | DRAW_NUMBER_STYLE_ALIGN_RIGHT);
            filemenu_draw_message(filemenu_get_menu_message(FILE_MESSAGE_QUESTION), baseX + DELETE_FILE_QMARK_X, baseY + 4, 0xFF, 0, 0);            break;
        case FM_CONFIRM_COPY:
            filemenu_draw_message(filemenu_get_menu_message(FILE_MESSAGE_FILE_22), baseX + 10, baseY + 4, 0xFF, 0, 0);
            draw_number(filemenu_menus[FILE_MENU_MAIN]->selected + 1, baseX + COPY_FILE_NUMBER_X, baseY + 6 + NUMBER_OFFSET_Y, DRAW_NUMBER_CHARSET_NORMAL, MSG_PAL_WHITE, 0xFF, DRAW_NUMBER_STYLE_MONOSPACE | DRAW_NUMBER_STYLE_ALIGN_RIGHT);
            filemenu_draw_message(filemenu_get_menu_message(FILE_MESSAGE_WILL_BE_DELETED), baseX + COPY_CONFIRM_SUFFIX_X, baseY + 4, 0xFF, 0, 0);
            filemenu_draw_message(filemenu_get_menu_message(FILE_MESSAGE_OK_TO_COPY_TO_THIS_FILE), baseX + 10, baseY + 18, 0xFF, 0, 0);
            break;
        case FM_CONFIRM_CREATE:
            filemenu_draw_message(filemenu_get_menu_message(FILE_MESSAGE_FILE_NAME_IS), baseX + 10, baseY + 6, 0xFF, 0, 0);

            for (i = ARRAY_COUNT(filemenu_filename) - 1; i >= 0; i--) {
                if (filemenu_filename[i] != MSG_CHAR_READ_SPACE) {
                    break;
                }
            }

            xOffset = (147 - (i * 11)) / 2;
            filemenu_draw_file_name(filemenu_filename, i + 1, baseX + xOffset, baseY + 22, 0xFF, 0, 8, 0xB);
            xOffset += (i + 1) * 11;
            filemenu_draw_message(filemenu_get_menu_message(FILE_MESSAGE_PERIOD_20), baseX + xOffset, baseY + 22, 0xFF, 0, 0);
            filemenu_draw_message(filemenu_get_menu_message(FILE_MESSAGE_OK), baseX + 70, baseY + 38, 0xFF, 0, 0);
            break;
        case FM_CONFIRM_START:
            selectedFile = filemenu_menus[FILE_MENU_MAIN]->selected;
            if (gSaveSlotMetadata[selectedFile].validData) {
                msgColor = MSG_PAL_WHITE;
            } else {
                msgColor = MSG_PAL_RED;
            }
            filemenu_draw_message(filemenu_get_menu_message(FILE_MESSAGE_START_GAME_WITH), baseX + START_GAME_START_WITH_X, baseY + 4, 255, msgColor, 0);
            filemenu_draw_message(filemenu_get_menu_message(FILE_MESSAGE_FILE_22), baseX + START_GAME_FILE_X, baseY + 4, 255, msgColor, 0);
            draw_number(filemenu_menus[FILE_MENU_MAIN]->selected + 1, baseX + START_GAME_NUMBER_X, baseY + 6 + NUMBER_OFFSET_Y, DRAW_NUMBER_CHARSET_NORMAL, msgColor, 255, DRAW_NUMBER_STYLE_MONOSPACE | DRAW_NUMBER_STYLE_ALIGN_RIGHT);
            filemenu_draw_message(filemenu_get_menu_message(FILE_MESSAGE_QUESTION), baseX + START_GAME_QMARK_X, baseY + 4, 255, msgColor, 0);
            break;
    }
}

void filemenu_yesno_init(MenuPanel* tab) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(filemenu_yesno_windowBPs); i++) {
        filemenu_yesno_windowBPs[i].tab = tab;
    }

    setup_pause_menu_tab(filemenu_yesno_windowBPs, ARRAY_COUNT(filemenu_yesno_windowBPs));
    tab->initialized = true;
}

void filemenu_yesno_handle_input(MenuPanel* menu) {
    s32 oldSelected = menu->selected;
    s32 selected;

    if (filemenu_heldButtons & BUTTON_STICK_UP) {
        menu->row--;
        if (menu->row < 0) {
            menu->row = 0;
        }
    }

    if (filemenu_heldButtons & BUTTON_STICK_DOWN) {
        menu->row++;
        if (menu->row >= menu->numRows) {
            menu->row = menu->numRows - 1;
        }
    }

    menu->selected = MENU_PANEL_SELECTED_GRID_DATA(menu);

    if (oldSelected != menu->selected) {
        sfx_play_sound(SOUND_MENU_CHANGE_SELECTION);
    }

    if ((filemenu_pressedButtons & BUTTON_START) && menu->state == FM_CONFIRM_START) {
        filemenu_set_selected(menu, 0, 0);
        filemenu_pressedButtons = BUTTON_A;
    }

    if (filemenu_pressedButtons & BUTTON_A) {
        s32 i;

        sfx_play_sound(SOUND_MENU_NEXT);

        switch (menu->selected) {
            case 0: // YES
                switch (menu->state) {
                    case FM_CONFIRM_DELETE:
                        filemenu_currentMenu = FILE_MENU_MESSAGE;
                        filemenu_menus[FILE_MENU_MESSAGE]->state = FM_MESSAGE_DELETED;
                        gWindows[WIN_FILES_MESSAGE].width = 182;
                        gWindows[WIN_FILES_MESSAGE].height = 25;
                        gWindows[WIN_FILES_MESSAGE].pos.x = CENTER_WINDOW_X(WIN_FILES_MESSAGE);
                        gWindows[WIN_FILES_MESSAGE].pos.y = CENTER_WINDOW_Y(WIN_FILES_MESSAGE);
                        set_window_update(WIN_FILES_MESSAGE, WINDOW_UPDATE_SHOW);
                        set_window_update(WIN_FILES_CONFIRM_OPTIONS, (intptr_t)filemenu_update_hidden_name_confirm);

                        selected = filemenu_menus[FILE_MENU_MAIN]->selected;
                        for (i = 0; i < ARRAY_COUNT(gSaveSlotSummary->filename); i++) {
                            gSaveSlotSummary[selected].filename[i] = MSG_CHAR_READ_SPACE;
                        }
                        gSaveSlotSummary[selected].level = 0;
                        gSaveSlotSummary[selected].timePlayed = 0;
                        gSaveSlotSummary[selected].spiritsRescued = 0;
                        fio_erase_game(selected);
                        gSaveSlotMetadata[selected].hasData = false;
                        gSaveSlotMetadata[selected].validData = false;
                        break;
                    case FM_CONFIRM_COPY:
                        filemenu_currentMenu = FILE_MENU_MESSAGE;
                        filemenu_menus[FILE_MENU_MESSAGE]->state = FM_MESSAGE_COPIED;
                        gWindows[WIN_FILES_MESSAGE].width = 154;
                        gWindows[WIN_FILES_MESSAGE].height = 39;
                        gWindows[WIN_FILES_MESSAGE].pos.x = CENTER_WINDOW_X(WIN_FILES_MESSAGE);
                        gWindows[WIN_FILES_MESSAGE].pos.y = CENTER_WINDOW_Y(WIN_FILES_MESSAGE);
                        set_window_update(WIN_FILES_MESSAGE, WINDOW_UPDATE_SHOW);
                        set_window_update(WIN_FILES_CONFIRM_OPTIONS, (intptr_t)filemenu_update_hidden_name_confirm);
                        fio_load_game(filemenu_CopyFromFileIdx);
                        gSaveSlotSummary[filemenu_CopyToFileIdx] = gSaveSlotSummary[filemenu_CopyFromFileIdx];
                        gSaveSlotMetadata[filemenu_CopyToFileIdx] = gSaveSlotMetadata[filemenu_CopyFromFileIdx];
                        fio_save_game(filemenu_CopyToFileIdx);
                        break;
                    case FM_CONFIRM_CREATE:
                        clear_player_data();
                        clear_saved_variables();
                        get_map_IDs_by_name_checked(NEW_GAME_MAP_ID, &gGameStatusPtr->areaID, &gGameStatusPtr->mapID);
                        gGameStatusPtr->entryID = NEW_GAME_ENTRY_ID;
                        evt_set_variable(nullptr, GB_StoryProgress, NEW_GAME_STORY_PROGRESS);

                        selected = filemenu_menus[FILE_MENU_MAIN]->selected;
                        for (i = 0; i < ARRAY_COUNT(gSaveSlotSummary->filename); i++) {
                            gSaveSlotSummary[selected].filename[i] = filemenu_filename[i];
                        }
                        fio_save_game(selected);
                        gSaveSlotMetadata[selected].hasData = true;
                        gSaveSlotMetadata[selected].validData = true;
                        strcpy(gSaveSlotMetadata[selected].modName, DX_MOD_NAME);

                        set_window_update(WIN_FILES_INPUT_FIELD, (intptr_t)filemenu_update_hidden_name_input);
                        set_window_update(WIN_FILES_INPUT_KEYBOARD, (intptr_t)filemenu_update_hidden_name_input);
                        set_window_update(WIN_FILES_TITLE, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_STEREO, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_MONO, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_OPTION_LEFT, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_OPTION_CENTER, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_OPTION_RIGHT, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_OPTION_LEFT, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_SLOT1_BODY, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_SLOT2_BODY, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_SLOT3_BODY, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_SLOT4_BODY, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_CONFIRM_OPTIONS, (intptr_t)filemenu_update_hidden_name_confirm);
                        filemenu_currentMenu = FILE_MENU_MESSAGE;
                        filemenu_menus[FILE_MENU_MESSAGE]->state = FM_MESSAGE_CREATED;
                        gWindows[WIN_FILES_MESSAGE].width = 184;
                        gWindows[WIN_FILES_MESSAGE].height = 25;
                        gWindows[WIN_FILES_MESSAGE].pos.x = CENTER_WINDOW_X(WIN_FILES_MESSAGE);
                        gWindows[WIN_FILES_MESSAGE].pos.y = CENTER_WINDOW_Y(WIN_FILES_MESSAGE);
                        set_window_update(WIN_FILES_MESSAGE, WINDOW_UPDATE_SHOW);
                        break;
                    case FM_CONFIRM_START:
                        selected = filemenu_menus[FILE_MENU_MAIN]->selected;
                        if (gGameStatusPtr->soundOutputMode != 1 - gSaveGlobals.useMonoSound ||
                            selected != (u8)gSaveGlobals.lastFileSelected)
                        {
                            gSaveGlobals.useMonoSound = 1 - gGameStatusPtr->soundOutputMode;
                            gSaveGlobals.lastFileSelected = selected;
                            fio_save_globals();
                        }
                        fio_load_game(selected);
                        set_game_mode(GAME_MODE_END_FILE_SELECT);
                        break;
                }
                break;
            case 1: // NO
                switch (menu->state) {
                    case FM_CONFIRM_DELETE:
                    case FM_CONFIRM_COPY:
                        filemenu_currentMenu = FILE_MENU_MAIN;
                        set_window_update(WIN_FILES_CONFIRM_OPTIONS, (intptr_t)filemenu_update_hidden_name_confirm);
                        break;
                    case FM_CONFIRM_CREATE:
                        filemenu_currentMenu = FILE_MENU_INPUT_NAME;
                        set_window_update(WIN_FILES_CONFIRM_OPTIONS, (intptr_t)filemenu_update_hidden_name_confirm);
                        break;
                    case FM_CONFIRM_START:
                        filemenu_currentMenu = FILE_MENU_MAIN;
                        selected = filemenu_menus[FILE_MENU_MAIN]->selected;
                        set_window_update(WIN_FILES_TITLE, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_STEREO, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_MONO, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_OPTION_LEFT, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_OPTION_CENTER, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_OPTION_RIGHT, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_OPTION_LEFT, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_SLOT1_BODY, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_SLOT2_BODY, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_SLOT3_BODY, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(WIN_FILES_SLOT4_BODY, (intptr_t)filemenu_update_show_with_rotation);
                        set_window_update(selected + WIN_FILES_SLOT1_BODY, (intptr_t)filemenu_update_deselect_file);
                        set_window_update(WIN_FILES_CONFIRM_OPTIONS, WINDOW_UPDATE_HIDE);
                        break;
                }
                break;
        }
    }

    if (filemenu_pressedButtons & BUTTON_B) {
        sfx_play_sound(SOUND_MENU_BACK);
        filemenu_set_selected(menu, 0, 1);

        switch (menu->state) {
            case FM_CONFIRM_DELETE:
            case FM_CONFIRM_COPY:
                filemenu_currentMenu = FILE_MENU_MAIN;
                set_window_update(WIN_FILES_CONFIRM_OPTIONS, (intptr_t)filemenu_update_hidden_name_confirm);
                break;
            case FM_CONFIRM_CREATE:
                filemenu_currentMenu = FILE_MENU_INPUT_NAME;
                set_window_update(WIN_FILES_CONFIRM_OPTIONS, (intptr_t)filemenu_update_hidden_name_confirm);
                break;
            case FM_CONFIRM_START:
                filemenu_currentMenu = FILE_MENU_MAIN;
                selected = filemenu_menus[FILE_MENU_MAIN]->selected;
                set_window_update(WIN_FILES_TITLE, (intptr_t)filemenu_update_show_with_rotation);
                set_window_update(WIN_FILES_STEREO, (intptr_t)filemenu_update_show_with_rotation);
                set_window_update(WIN_FILES_MONO, (intptr_t)filemenu_update_show_with_rotation);
                set_window_update(WIN_FILES_OPTION_LEFT, (intptr_t)filemenu_update_show_with_rotation);
                set_window_update(WIN_FILES_OPTION_CENTER, (intptr_t)filemenu_update_show_with_rotation);
                set_window_update(WIN_FILES_OPTION_RIGHT, (intptr_t)filemenu_update_show_with_rotation);
                set_window_update(WIN_FILES_OPTION_LEFT, (intptr_t)filemenu_update_show_with_rotation);
                set_window_update(WIN_FILES_SLOT1_BODY, (intptr_t)filemenu_update_show_with_rotation);
                set_window_update(WIN_FILES_SLOT2_BODY, (intptr_t)filemenu_update_show_with_rotation);
                set_window_update(WIN_FILES_SLOT3_BODY, (intptr_t)filemenu_update_show_with_rotation);
                set_window_update(WIN_FILES_SLOT4_BODY, (intptr_t)filemenu_update_show_with_rotation);
                set_window_update(selected + WIN_FILES_SLOT1_BODY, (intptr_t)filemenu_update_deselect_file);
                set_window_update(WIN_FILES_CONFIRM_OPTIONS, WINDOW_UPDATE_HIDE);
                break;
        }
    }
}

void filemenu_yesno_update(MenuPanel* menu) {
}

void filemenu_yesno_cleanup(MenuPanel* menu) {
}
