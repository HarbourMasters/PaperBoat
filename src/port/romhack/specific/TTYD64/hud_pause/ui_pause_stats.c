#include "hp_internal.h"
#include "port/hooks/Events.h"
#include "port/modding/Panels.h"
#include "port/modding/Messages.h"
#include "pause/pause_common.h"

enum {
    HP_STAT_ICON_MARIO = 0,
    HP_STAT_ICON_BOOTS = 1,
    HP_STAT_ICON_HAMMER = 2,
    HP_STAT_ICON_COIN = 3,
    HP_STAT_ICON_STAR_POINT = 4,
    HP_STAT_ICON_STAR_PIECE = 5,
    HP_STAT_ICON_CLOCK = 6,
    HP_STAT_ICON_HP = 7,
    HP_STAT_ICON_FP = 8,
    HP_STAT_ICON_BP = 9,
    HP_STAT_ICON_STAR = 10,
    HP_STAT_ICON_TIMES = 11,
};

extern HudScript* gStatsBootsElements[];
extern HudScript* gStatsHammerElements[];
extern s32 gPauseStatsBootsMessages[];
extern s32 gPauseStatsHammerMessages[];
extern HudScript* gPauseStatsSPIncElements[];
extern HudScript* gPauseStatsStarElements[];
extern s32 D_8024F46C[];
extern HudScript HES_StatusSPEmptyIncrement;
extern HudScript HES_StatusStarEmpty;

static const u8 sString_Shine[] = { 0x33, 0x0E, 0xF7, 0x33, 0x50, 0x52, 0x49, 0x54, 0x45, 0x53, 0xFD };
static const u8 sString_SpritesDesc[] = {
    0x33, 0x48, 0x49, 0x4E, 0x45, 0xF7, 0x33, 0x50, 0x52, 0x49, 0x54, 0x45, 0x53, 0xF7, 0x2D,
    0x41, 0x52, 0x49, 0x4F, 0xF7, 0x48, 0x41, 0x53, 0xF7, 0x46, 0x4F, 0x55, 0x4E, 0x44, 0x0E,
    0xF0, 0x34, 0x48, 0x52, 0x45, 0x45, 0xF7, 0x43, 0x41, 0x4E, 0xF7, 0x4C, 0x45, 0x56, 0x45,
    0x4C, 0xF7, 0x55, 0x50, 0xF7, 0x41, 0x4E, 0xF7, 0x41, 0x4C, 0x4C, 0x59, 0x0E, 0xFD,
};

static const s32 sStatsMenu_CursorTableData[12][3] = {
    { 0x09, 0x24, 0x21 }, { 0x08, 0x44, 0x25 }, { 0x08, 0x62, 0x29 }, { 0x11, 0x84, 0x24 },
    { 0x7E, 0x31, 0x22 }, { 0xC8, 0x31, 0x23 }, { 0x84, 0x4C, 0x2C }, { 0x7D, 0x5B, 0x2D },
    { 0x7D, 0x6A, 0x2E }, { 0x7D, 0x79, 0x2F }, { 0x7D, 0x8A, 0x00 }, { 0x7D, 0x99, 0x31 },
};

static s32 sStringShineID;
static s32 sStringSpritesDescID;

static void hp_stats_draw_pow(s32 baseX, s32 baseY, const s32* iconIDs) {
    PlayerData* playerData = &gPlayerData;
    s32 powHudElemID;
    s32 powIncrements;
    s32 powIncIdx;
    s32 curIncrement;
    b32 drawingFirst;
    s32 powBarIdx;
    s32 powFullBars;
    s32 k;

    drawingFirst = true;
    curIncrement = 0;
    powBarIdx = 0;
    powIncIdx = 0;
    powHudElemID = iconIDs[HP_STAT_ICON_STAR];

    powFullBars = playerData->starPower / SP_PER_BAR;
    powIncrements = playerData->starPower % SP_PER_BAR;
    powIncrements /= SP_PER_SEG;
    powIncrements += powFullBars * 8;

    while (true) {
        for (k = 0; k < 7; k++) {
            if (curIncrement >= powIncrements) {
                goto filled_done;
            }
            curIncrement++;
            hud_element_set_script(powHudElemID, gPauseStatsSPIncElements[powBarIdx]);
            hud_element_set_render_pos(powHudElemID, baseX + 140 + (powBarIdx * 20) + D_8024F46C[k], baseY + 75);
            if (drawingFirst) {
                hud_element_draw_without_clipping(powHudElemID);
                drawingFirst = false;
            } else {
                hud_element_draw_next(powHudElemID);
            }
            powIncIdx++;
        }

        if (curIncrement >= powIncrements) {
            break;
        }
        curIncrement++;
        hud_element_set_script(powHudElemID, gPauseStatsStarElements[powBarIdx]);
        hud_element_set_render_pos(powHudElemID, baseX + 152 + (powBarIdx * 20), baseY + 77);
        if (drawingFirst) {
            hud_element_draw_without_clipping(powHudElemID);
            drawingFirst = false;
        } else {
            hud_element_draw_next(powHudElemID);
        }
        powIncIdx = 0;
        powBarIdx++;
        if (curIncrement >= powIncrements) {
            break;
        }
    }
filled_done:

    powFullBars = playerData->maxStarPower;
    powIncrements = 8 * powFullBars;

    while (true) {
        if (curIncrement >= powIncrements) {
            break;
        }
        if (powIncIdx == 0) {
            curIncrement++;
            hud_element_set_script(powHudElemID, &HES_StatusSPEmptyIncrement);
            hud_element_set_render_pos(powHudElemID, baseX + 140 + (powBarIdx * 20) + D_8024F46C[0], baseY + 75);
            if (drawingFirst) {
                hud_element_draw_without_clipping(powHudElemID);
                drawingFirst = false;
            } else {
                hud_element_draw_next(powHudElemID);
            }
            if (curIncrement >= powIncrements) {
                break;
            }
            powIncIdx++;
        }
        for (k = 1; k < 7; k++) {
            if (powIncIdx == k) {
                curIncrement++;
                hud_element_set_script(powHudElemID, &HES_StatusSPEmptyIncrement);
                hud_element_set_render_pos(powHudElemID, baseX + 140 + (powBarIdx * 20) + D_8024F46C[k], baseY + 75);
                if (drawingFirst) {
                    hud_element_draw_without_clipping(powHudElemID);
                    drawingFirst = false;
                } else {
                    hud_element_draw_next(powHudElemID);
                }
                powIncIdx++;
                if (curIncrement >= powIncrements) {
                    return;
                }
            }
        }
        if (powIncIdx == 7) {
            curIncrement++;
            hud_element_set_script(powHudElemID, &HES_StatusStarEmpty);
            hud_element_set_render_pos(powHudElemID, baseX + 152 + (powBarIdx * 20), baseY + 77);
            if (drawingFirst) {
                hud_element_draw_without_clipping(powHudElemID);
                drawingFirst = false;
            } else {
                hud_element_draw_next(powHudElemID);
            }
            powIncIdx++;
            if (curIncrement >= powIncrements) {
                break;
            }
        }
        powIncIdx = 0;
        powBarIdx++;
    }
}

void TTYD64_hp_PauseStatsDraw(
    MenuPanel* menu, s32 baseX, s32 baseY, s32 width, s32 height, s32 opacity, s32 darkening, const s32* iconIDs
) {
    s16 bootsLevel;
    s16 hammerLevel;
    s16 level;
    s32 frameCount;
    s32 shineIcon;
    s32 powBaseY;

    hud_element_set_render_pos(iconIDs[HP_STAT_ICON_COIN], baseX + 143, baseY + 0x5D);
    hud_element_draw_without_clipping(iconIDs[HP_STAT_ICON_COIN]);
    draw_msg(pause_get_menu_msg(PAUSE_MSG_LBL_COINS), baseX + 155, baseY + 0x56, 255, MSG_PAL_STANDARD, 1);
    draw_number(gPlayerData.coins, baseX + 281, baseY + 0x56, 1, MSG_PAL_STANDARD, 255, 3);
    hud_element_set_render_pos(iconIDs[HP_STAT_ICON_TIMES], baseX + 248, baseY + 0x5D);
    hud_element_draw_without_clipping(iconIDs[HP_STAT_ICON_TIMES]);

    hud_element_set_render_pos(iconIDs[HP_STAT_ICON_STAR_POINT], baseX + 143, baseY + 0x4E);
    hud_element_draw_without_clipping(iconIDs[HP_STAT_ICON_STAR_POINT]);
    draw_msg(pause_get_menu_msg(PAUSE_MSG_LBL_STAR_POINTS), baseX + 155, baseY + 0x47, 255, MSG_PAL_STANDARD, 1);
    draw_number(gPlayerData.starPoints, baseX + 281, baseY + 0x47, 1, MSG_PAL_STANDARD, 255, 3);
    hud_element_set_render_pos(iconIDs[HP_STAT_ICON_TIMES], baseX + 248, baseY + 0x4E);
    hud_element_draw_without_clipping(iconIDs[HP_STAT_ICON_TIMES]);

    hud_element_set_render_pos(iconIDs[HP_STAT_ICON_STAR_PIECE], baseX + 143, baseY + 0x6B);
    hud_element_draw_without_clipping(iconIDs[HP_STAT_ICON_STAR_PIECE]);
    draw_msg(pause_get_menu_msg(PAUSE_MSG_LBL_STAR_PIECES), baseX + 155, baseY + 0x64, 255, MSG_PAL_STANDARD, 1);
    draw_number(gPlayerData.starPieces, baseX + 281, baseY + 0x64, 1, MSG_PAL_STANDARD, 255, 3);
    hud_element_set_render_pos(iconIDs[HP_STAT_ICON_TIMES], baseX + 248, baseY + 0x6B);
    hud_element_draw_without_clipping(iconIDs[HP_STAT_ICON_TIMES]);

    shineIcon = TTYD64_hp_PauseIcon(TTYD64_HP_PAUSE_ICON_SHINE);
    hud_element_set_render_pos(shineIcon, baseX + 248 - 0x6A, baseY + 0x6B + 0xF);
    TTYD64_SetIconSize(shineIcon, 18.0f, 18.0f);
    hud_element_draw_next(shineIcon);
    draw_msg(sStringShineID, baseX + 281 - 0x7D, baseY + 0x1D + 0x57, 0xFF, MSG_PAL_STANDARD, 1);
    draw_number(TTYD64_ShineSprites, baseX + 281, baseY + 0x1D + 0x57, 1, MSG_PAL_STANDARD, 0xFF, 3);
    hud_element_set_render_pos(iconIDs[HP_STAT_ICON_TIMES], baseX + 248, baseY + 0x6B + 0x10);
    hud_element_draw_without_clipping(iconIDs[HP_STAT_ICON_TIMES]);

    pause_draw_menu_label(PAUSE_LBL_HP, baseX + 21 + 0x71, baseY + 0xD);
    hud_element_set_render_pos(iconIDs[HP_STAT_ICON_HP], baseX + 52 + 0x59, baseY + 0x22);
    hud_element_draw_without_clipping(iconIDs[HP_STAT_ICON_HP]);
    pause_get_menu_msg(PAUSE_MSG_LBL_HP);
    draw_number(gPlayerData.curHP, baseX + 78 + 0x5A, baseY + 0x1D, 1, 0, 255, 3);
    draw_msg(pause_get_menu_msg(PAUSE_MSG_SLASH), baseX + 78 + 0x5B, baseY + 0x1D, 255, MSG_PAL_WHITE, 1);
    draw_number(gPlayerData.curMaxHP, baseX + 105 + 0x5D, baseY + 0x1D, 1, 0, 255, 3);

    pause_draw_menu_label(PAUSE_LBL_FP, baseX + 21 + 0xBA, baseY + 0xD);
    hud_element_set_render_pos(iconIDs[HP_STAT_ICON_FP], baseX + 52 + 0xA3, baseY + 0x24);
    hud_element_draw_without_clipping(iconIDs[HP_STAT_ICON_FP]);
    pause_get_menu_msg(PAUSE_MSG_LBL_FP);
    draw_number(gPlayerData.curFP, baseX + 78 + 0xA3, baseY + 0x1D, 1, MSG_PAL_WHITE, 255, 3);
    draw_msg(pause_get_menu_msg(PAUSE_MSG_SLASH), baseX + 78 + 0xA4, baseY + 0x1D, 255, MSG_PAL_WHITE, 1);
    draw_number(gPlayerData.curMaxFP, baseX + 105 + 0xA6, baseY + 0x1D, 1, MSG_PAL_WHITE, 255, 3);

    pause_draw_menu_label(PAUSE_LBL_BP, baseX + 21, baseY + 0x60);
    hud_element_set_render_pos(iconIDs[HP_STAT_ICON_BP], baseX + 52, baseY + 0x76);
    hud_element_draw_without_clipping(iconIDs[HP_STAT_ICON_BP]);
    draw_msg(pause_get_menu_msg(PAUSE_MSG_LBL_BP), baseX + 25, baseY + 0x6F, 255, MSG_PAL_WHITE, 1);
    draw_number(gPlayerData.maxBP, baseX + 78, baseY + 0x6F, 1, MSG_PAL_WHITE, 255, 3);

#define HP_MINUTE (60 * 60)
#define HP_HOUR   (HP_MINUTE * 60)

    hud_element_set_render_pos(iconIDs[HP_STAT_ICON_CLOCK], baseX + 143, baseY + 140);
    hud_element_draw_without_clipping(iconIDs[HP_STAT_ICON_CLOCK]);
    draw_msg(pause_get_menu_msg(PAUSE_MSG_LBL_TIME), baseX + 155, baseY + 133, 255, MSG_PAL_STANDARD, 1);
    frameCount = gPlayerData.frameCounter;
    if (frameCount >= (100 * HP_HOUR)) {
        frameCount = (100 * HP_HOUR) - 1;
    }
    draw_number((frameCount / (10 * HP_HOUR)) % 10, baseX + 237, baseY + 133, 1, MSG_PAL_STANDARD, 255, 2);
    draw_number((frameCount / HP_HOUR) % 10, baseX + 246, baseY + 133, 1, MSG_PAL_STANDARD, 255, 2);
    draw_msg(pause_get_menu_msg(PAUSE_MSG_DOT), baseX + 257, baseY + 132, 255, MSG_PAL_STANDARD, 1);
    draw_msg(pause_get_menu_msg(PAUSE_MSG_DOT), baseX + 257, baseY + 127, 255, MSG_PAL_STANDARD, 1);
    draw_number((frameCount / (10 * HP_MINUTE)) % 6, baseX + 264, baseY + 133, 1, MSG_PAL_STANDARD, 255, 2);
    draw_number((frameCount / HP_MINUTE) % 10, baseX + 273, baseY + 133, 1, MSG_PAL_STANDARD, 255, 2);

    bootsLevel = gPlayerData.bootsLevel;
    hammerLevel = gPlayerData.hammerLevel;
    level = gPlayerData.level;
    draw_box(
        4, &gPauseWS_10, baseX + 7, baseY + 12, 0, level >= 10 ? 121 : 113, 17, 255, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        nullptr, nullptr, nullptr, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr
    );

    hud_element_set_render_pos(iconIDs[HP_STAT_ICON_MARIO], baseX + 61, baseY + 21);
    hud_element_draw_without_clipping(iconIDs[HP_STAT_ICON_MARIO]);
    draw_msg(pause_get_menu_msg(PAUSE_MSG_MARIO), baseX + 16, baseY + 14, 255, MSG_PAL_WHITE, 1);
    draw_msg(pause_get_menu_msg(PAUSE_MSG_LEVEL), baseX + 67, baseY + 14, 255, MSG_PAL_WHITE, 1);
    draw_number(level, baseX + 106, baseY + 14, 1, MSG_PAL_WHITE, 255, 2);

    bootsLevel++;
    if (bootsLevel < 0) {
        bootsLevel = 0;
    }
    if (bootsLevel > 3) {
        bootsLevel = 3;
    }

    hammerLevel++;
    if (hammerLevel < 0) {
        hammerLevel = 0;
    }
    if (hammerLevel > 3) {
        hammerLevel = 3;
    }

    pause_draw_menu_label(PAUSE_LBL_BOOTS, baseX + 0x16, baseY + 0x21);
    pause_draw_menu_label(PAUSE_LBL_HAMMER, baseX + 0x16, baseY + 0x3F);

    hud_element_set_script(iconIDs[HP_STAT_ICON_BOOTS], gStatsBootsElements[bootsLevel]);
    hud_element_set_render_pos(iconIDs[HP_STAT_ICON_BOOTS], baseX + 0x17, baseY + 0x35);
    hud_element_draw_without_clipping(iconIDs[HP_STAT_ICON_BOOTS]);
    draw_msg(
        pause_get_menu_msg(gPauseStatsBootsMessages[bootsLevel]), baseX + 0x20, baseY + 0x2F, 255, MSG_PAL_WHITE, 1
    );

    hud_element_set_script(iconIDs[HP_STAT_ICON_HAMMER], gStatsHammerElements[hammerLevel]);
    hud_element_set_render_pos(iconIDs[HP_STAT_ICON_HAMMER], baseX + 0x17, baseY + 0x53);
    hud_element_draw_without_clipping(iconIDs[HP_STAT_ICON_HAMMER]);
    draw_msg(
        pause_get_menu_msg(gPauseStatsHammerMessages[hammerLevel]), baseX + 0x20, baseY + 0x4D, 255, MSG_PAL_WHITE, 1
    );

    if (gWindows[WIN_PAUSE_STATS].updateCounter < 6) {
        powBaseY = -0x10;
    } else {
        powBaseY = 0x14;
    }

    pause_draw_menu_label(PAUSE_LBL_STATS, baseX + 130, powBaseY + 69);
    pause_draw_menu_label(PAUSE_LBL_ENERGY, baseX + 138, powBaseY + 60);

    hp_stats_draw_pow(baseX, powBaseY, iconIDs);

    if (gPauseMenuCurrentTab == 1) {
        const s32* entry = sStatsMenu_CursorTableData[menu->selected];

        pause_set_cursor_pos(WIN_PAUSE_STATS, baseX + entry[0], powBaseY + entry[1]);
    }
}

static void hp_stats_set_index(MenuPanel* panel) {
    s32 col = (u8) panel->col;
    s32 row = (u8) panel->row;
    s32 index;
    s32 msg;

    if (col == 2) {
        index = 5;
    } else if (col == 1 && row == 0) {
        index = 4;
    } else if (col == 1 && row == 2) {
        index = 6;
    } else if (col == 1 && row == 3) {
        index = 7;
    } else if (col == 1 && row == 4) {
        index = 8;
    } else if (col == 1 && row == 5) {
        index = 9;
    } else if (col == 1 && row == 6) {
        index = 0xA;
    } else if (col == 1 && row == 7) {
        index = 0xB;
    } else if (row == 0) {
        index = 0;
    } else if ((u32) row < 3) {
        index = 1;
    } else if ((u32) row < 5) {
        index = 2;
    } else {
        index = 3;
    }
    panel->selected = index;

    if (index == 0xA) {
        gPauseCurrentDescMsg = sStringSpritesDescID;
        return;
    }
    msg = (u8) sStatsMenu_CursorTableData[index][2];
    if (index == 1) {
        msg += gPlayerData.bootsLevel;
    } else if (index == 2) {
        msg += gPlayerData.hammerLevel;
    }
    gPauseCurrentDescMsg = pause_get_menu_msg(msg);
}

void TTYD64_hp_PauseStatsInput(MenuPanel* panel) {
    u32 pressed = gGameStatusPtr->pressedButtons[0];
    s32 col = (u8) panel->col;
    s32 row = (u8) panel->row;

    if (pressed & BUTTON_STICK_UP) {
        if (row == 0) {
            hp_stats_set_index(panel);
            return;
        }
        if (col == 0) {
            row -= 2;
        } else if (col == 1) {
            row -= 1;
        } else {
            col = 0;
        }
        if (col == 1 && row == 1) {
            row -= 1;
        }
        if (row < 0) {
            row = 0;
        }
        panel->row = row;
    } else if (pressed & BUTTON_STICK_DOWN) {
        s32 cap;

        if (col == 0) {
            if (row >= 5) {
                panel->col = 0;
                panel->row = 6;
                hp_stats_set_index(panel);
                return;
            }
            cap = 1;
        } else {
            cap = 7;
        }
        if (row == cap) {
            hp_stats_set_index(panel);
            return;
        }
        if (col == 0) {
            row += 2;
        } else if (col == 1) {
            row += 1;
        } else if (col == 2) {
            panel->col = 1;
            row = 2;
        }
        if (panel->selected == 4) {
            row = 2;
        }
        panel->row = row;
    } else if (pressed & BUTTON_STICK_LEFT) {
        if (col == 0) {
            hp_stats_set_index(panel);
            return;
        }
        col -= 1;
        if (col == 0 && row == 7) {
            panel->row = 6;
        }
        panel->col = col;
    } else if (pressed & BUTTON_STICK_RIGHT) {
        if (col == 2) {
            hp_stats_set_index(panel);
            return;
        }
        if (col == 1 && row >= 2) {
            hp_stats_set_index(panel);
            return;
        }
        if (col == 0 && row == 1) {
            panel->row = 0;
        }
        panel->col = col + 1;
    } else {
        if (pressed & BUTTON_B) {
            sfx_play_sound(SOUND_MENU_BACK);
            gPauseMenuCurrentTab = 0;
            return;
        }
        hp_stats_set_index(panel);
        return;
    }
    sfx_play_sound(SOUND_MENU_CHANGE_SELECTION);
    hp_stats_set_index(panel);
}

static PauseStatsView sStatsView;

static void hp_on_pause_stats_view(IEvent* event) {
    sStatsView = *((OnPauseStatsView*) event)->view;
}

static void hp_pause_stats_draw(const ModPanelDraw* draw) {
    if (sStatsView.iconIDs == nullptr) {
        return;
    }
    TTYD64_hp_PauseStatsDraw(
        draw->panel, draw->x, draw->y, draw->width, draw->height, draw->opacity, draw->darkening, sStatsView.iconIDs
    );
}

static const ModPanelOps sPauseStatsOps = {
    .input = TTYD64_hp_PauseStatsInput,
    .draw = hp_pause_stats_draw,
    .numCols = 3,
    .numRows = 8,
};

void TTYD64_hp_InstallPauseStats(void) {
    sStringShineID = Mod_RegisterInlineMessage("TTYD64", sString_Shine);
    sStringSpritesDescID = Mod_RegisterInlineMessage("TTYD64", sString_SpritesDesc);
    REGISTER_LISTENER(OnPauseStatsView, EVENT_PRIORITY_NORMAL, hp_on_pause_stats_view);
    Mod_ReplacePanel("TTYD64", MOD_PANEL_PAUSE_STATS, &sPauseStatsOps);
}
