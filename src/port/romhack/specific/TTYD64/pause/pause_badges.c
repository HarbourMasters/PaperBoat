#include "port/romhack/specific/TTYD64/hud_pause_internal.h"
#include "port/hooks/Events.h"
#include "port/modding/Abilities.h"
#include "port/modding/Messages.h"
#include "port/modding/Panels.h"
#include "pause/pause_common.h"

#define HP_BADGE_NONE_STANDIN 0x7FFE
#define HP_BADGE_INVALID      0x7FFF

extern Gfx PauseGfxOrbs[];
s32 pause_badges_get_pos_x(s32 page, s32 itemIndex);
s32 pause_badges_get_pos_y(s32 page, s32 itemIndex);
s32 pause_badges_get_column(s32 page, s32 itemIdx);
s32 pause_badges_get_row(s32 page, s32 itemIdx);
s32 pause_badges_is_visible(s32 y);
s32 pause_badges_scroll_offset_y(s32 offset);
s32 pause_badges_scroll_offset_x(s32 x);
void pause_badges_draw_bp_orbs(s32 orbState, s32 x, s32 y);

static const ALIGN_ASSET(2) char sTex_DPad[] = "__OTR__romhack/res/belts/dpad";
static const ALIGN_ASSET(2) char sPal_DPad[] = "__OTR__romhack/res/belts/dpad.pal";
static const ALIGN_ASSET(2) char sTex_LeftB[] = "__OTR__romhack/res/belts/0A8";
static const ALIGN_ASSET(2) char sPal_LeftB[] = "__OTR__romhack/res/belts/0A8.pal";
static const ALIGN_ASSET(2) char sTex_RightB[] = "__OTR__romhack/res/belts/0AE";
static const ALIGN_ASSET(2) char sPal_RightB[] = "__OTR__romhack/res/belts/0AE.pal";
static const ALIGN_ASSET(2) char sTex_DownB[] = "__OTR__romhack/res/belts/0B9";
static const ALIGN_ASSET(2) char sPal_DownB[] = "__OTR__romhack/res/belts/0B9.pal";
static const ALIGN_ASSET(2) char sTex_BumpAttack[] = "__OTR__romhack/res/belts/0C8";
static const ALIGN_ASSET(2) char sPal_BumpAttack[] = "__OTR__romhack/res/belts/0C8.pal";
static const ALIGN_ASSET(2) char sTex_ShinePause[] = "__OTR__romhack/res/pause_menu/ssprite_0";
static const ALIGN_ASSET(2) char sPal_ShinePause[] = "__OTR__romhack/res/pause_menu/ssprite_0.pal";
static const ALIGN_ASSET(2) char sTex_Compass[] = "__OTR__romhack/res/pause_menu/unused_compass";
static const ALIGN_ASSET(2) char sPal_Compass[] = "__OTR__romhack/res/pause_menu/unused_compass.pal";
static const ALIGN_ASSET(2) char sTex_EmptyBook[] = "__OTR__romhack/res/pause_menu/EmptyBook";
static const ALIGN_ASSET(2) char sPal_EmptyBook[] = "__OTR__romhack/res/pause_menu/EmptyBook.pal";
static const ALIGN_ASSET(2) char sTex_GearBoots1[] = "__OTR__romhack/res/pause_menu/gear_boots_1";
static const ALIGN_ASSET(2) char sPal_GearBoots1[] = "__OTR__romhack/res/pause_menu/gear_boots_1.pal";
static const ALIGN_ASSET(2) char sTex_Screwdriver[] = "__OTR__romhack/res/pause_menu/screwdriver";
static const ALIGN_ASSET(2) char sPal_Screwdriver[] = "__OTR__romhack/res/pause_menu/screwdriver.pal";

// clang-format off
#define TTYD64_HP_PAUSE_ICON(raster, palette)                              \
    {                                                                      \
        hs_SetVisible                                                      \
        hs_SetSizesFixedScale(3, 4)                                        \
        HUD_ELEMENT_OP_SetCI, 60, (intptr_t) (raster), (intptr_t) (palette), \
        hs_End                                                             \
        hs_End                                                             \
        hs_Restart                                                         \
        hs_End                                                             \
    }
// clang-format on

HudScript TTYD64_hp_IconScript_DPad = TTYD64_HP_PAUSE_ICON(sTex_DPad, sPal_DPad);
HudScript TTYD64_hp_IconScript_LeftBelt = TTYD64_HP_PAUSE_ICON(sTex_LeftB, sPal_LeftB);
HudScript TTYD64_hp_IconScript_RightBelt = TTYD64_HP_PAUSE_ICON(sTex_RightB, sPal_RightB);
HudScript TTYD64_hp_IconScript_DownBelt = TTYD64_HP_PAUSE_ICON(sTex_DownB, sPal_DownB);
HudScript TTYD64_hp_IconScript_BumpAttack = TTYD64_HP_PAUSE_ICON(sTex_BumpAttack, sPal_BumpAttack);
HudScript TTYD64_hp_IconScript_Shine_Pause = TTYD64_HP_PAUSE_ICON(sTex_ShinePause, sPal_ShinePause);
HudScript TTYD64_hp_IconScript_Compass = TTYD64_HP_PAUSE_ICON(sTex_Compass, sPal_Compass);
HudScript TTYD64_hp_IconScript_EmptyBook = TTYD64_HP_PAUSE_ICON(sTex_EmptyBook, sPal_EmptyBook);
HudScript TTYD64_hp_IconScript_GearBoots1 = TTYD64_HP_PAUSE_ICON(sTex_GearBoots1, sPal_GearBoots1);
HudScript TTYD64_hp_IconScript_Screwdriver = TTYD64_HP_PAUSE_ICON(sTex_Screwdriver, sPal_Screwdriver);

static HudScript* const sPauseIconScripts[] = {
    &TTYD64_hp_IconScript_DPad,        &TTYD64_hp_IconScript_LeftBelt,    &TTYD64_hp_IconScript_RightBelt,
    &TTYD64_hp_IconScript_DownBelt,    &TTYD64_hp_IconScript_BumpAttack,  &TTYD64_IconScript_HealBoxHeart,
    &TTYD64_hp_IconScript_Shine_Pause, &TTYD64_hp_IconScript_Compass,     &TTYD64_hp_IconScript_EmptyBook,
    &TTYD64_hp_IconScript_GearBoots1,  &TTYD64_hp_IconScript_Screwdriver,
};

static const u8 sString_All[] = { 0x21, 0x4C, 0x4C, 0xFD };
static const u8 sString_On[] = { 0x2F, 0x4E, 0xFD };
static s32 sStringAllID;
static s32 sStringOnID;

static s32 sPauseIcons[ARRAY_COUNT(sPauseIconScripts)];

s32 TTYD64_hp_PauseIcon(s32 index) {
    return sPauseIcons[index];
}

void TTYD64_hp_PauseMenuInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sPauseIconScripts); i++) {
        sPauseIcons[i] = TTYD64_CreateIcon(sPauseIconScripts[i]);
    }
}

void TTYD64_hp_PauseMenuCleanup(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sPauseIconScripts); i++) {
        hud_element_free(sPauseIcons[i]);
    }
}

void TTYD64_hp_PauseBadgesDraw(
    MenuPanel* menu,
    s32 baseX,
    s32 baseY,
    s32 width,
    s32 height,
    s32 opacity,
    s32 darkening,
    const PauseBadgesView* state
) {
    s32 pageIndex, i;
    s32 badgeIndex;
    s32 currentBadgeRow;
    s32 currentBadgeColumn;
    s32 style;
    s32 palette;
    s32 bpAvailable;
    s32 costBP;
    s32 canBeEquipped;
    const PauseItemPage* page;
    s32 badgeListX;
    s32 badgeListY;
    s32 isEquipped;
    s32 isNone;
    s32 cannotBeEquipped;
    s32 x1, y1, x2, y2;
    s16 badgeID;
    s32 isSelected;
    s32 badgeEntryOffsetX, badgeEntryOffsetY;
    s32 posX, posY, cursorOffsetX, cursorOffsetY, selectedPosX, selectedPosY;
    s32 orbOffsetY;
    s32 numOrbs;
    s32 orbY, orbX;
    s32 bpAmount;
    s32 bpAvailOffsetX;
    s32 bpAvailOffsetY;
    f32 orbBlinkValue;
    s32 orbBlinkOpacity;
    s32 orbColorR, orbColorG, orbColorB;
    s32 orbColorR1, orbColorG1, orbColorB1;
    s32 badgeIconElement;
    s32 maxBP;
    s32 itemIndex, j;
    s16* equippedBadges;
    s32 itemID;
    s32 orbIndex;
    const s32* iconIDs;
    PlayerData* playerData = &gPlayerData;
    const PauseItemPage* pages = state->pages;
    const s32* pauseIconIDs = state->iconIDs;
    s32 currentPageIdx = *state->currentPage;
    s32 selectedIndex = *state->selectedIndex;
    s32 currentTab;
    s32 level = *state->level;
    const PauseItemPage* currentPage = &pages[currentPageIdx];
    s32 bpAmountX;

    costBP = 0;
    canBeEquipped = false;
    style = DRAW_MSG_STYLE_MENU;
    bpAvailable = gPlayerData.maxBP - pause_get_total_equipped_bp_cost();
    currentBadgeColumn = selectedIndex / currentPage->numCols;
    currentBadgeRow = selectedIndex % currentPage->numCols;

    draw_box(
        DRAW_FLAG_NO_CLIP, &gPauseWS_15, baseX + 84, baseY, 0, width - 84, height, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        SCREEN_WIDTH, SCREEN_HEIGHT, 0
    );
    hud_element_set_render_pos(pauseIconIDs[20], baseX + 241, baseY + 11);
    palette = MSG_PAL_STANDARD;
    hud_element_draw_without_clipping(pauseIconIDs[20]);

    x1 = baseX + 1;
    y1 = baseY + 14;
    x2 = baseX + width - 1;
    y2 = baseY + height - 9;

    if (x1 <= 0) {
        x1 = 1;
    }
    if (y1 <= 0) {
        y1 = 1;
    }

    if (x2 <= 0 || y2 <= 0 || x1 >= SCREEN_WIDTH - 1 || y1 >= SCREEN_HEIGHT - 1) {
        return;
    }

    if (x2 >= SCREEN_WIDTH - 1) {
        x2 = SCREEN_WIDTH - 1;
    }
    if (y2 >= SCREEN_HEIGHT - 1) {
        y2 = SCREEN_HEIGHT - 1;
    }
    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, x1, y1, x2, y2);

    badgeIndex = 0;
    for (i = 0; i < 3; i++) {
        for (pageIndex = 0; pageIndex < 20; pageIndex++) {
            iconIDs = pauseIconIDs;
            badgeListX = baseX + 119;
            badgeListY = baseY + 17;

            page = &pages[pageIndex];
            if (!page->enabled) {
                break;
            }

            pause_badges_get_pos_y(pageIndex, 0);

            for (itemIndex = 0; itemIndex < page->count; itemIndex++) {
                badgeID = state->itemIds[page->startIndex + itemIndex];
                isEquipped = false;
                isSelected = false;
                equippedBadges = gPlayerData.equippedBadges;
                cannotBeEquipped = false;
                if (badgeID == HP_BADGE_INVALID) {
                    continue;
                }

                posX = pause_badges_get_pos_x(pageIndex, itemIndex);
                posY = pause_badges_get_pos_y(pageIndex, itemIndex);
                isNone = badgeID == HP_BADGE_NONE_STANDIN;

                for (j = 0; j < ARRAY_COUNT(gPlayerData.equippedBadges); equippedBadges++, j++) {
                    if (badgeID == *equippedBadges) {
                        isEquipped = true;
                        break;
                    }
                }
                isEquipped = TTYD64_bs_PauseDrawEquipped(
                    page->startIndex + itemIndex, *state->currentTab, state->itemIds, isEquipped
                );

                if (gPauseMenuCurrentTab == 2 && level == 1
                    && pause_badges_get_column(pageIndex, itemIndex) == currentBadgeRow
                    && pause_badges_get_row(pageIndex, itemIndex) == currentBadgeColumn)
                {
                    itemID = badgeID;
                    isSelected = true;
                    if (!isNone) {
                        costBP = Mod_GetBadgeBPCost(itemID);
                        if (!isEquipped && bpAvailable >= costBP) {
                            canBeEquipped = true;
                        }
                    }
                }

                if (!isNone && bpAvailable < Mod_GetBadgeBPCost(badgeID)) {
                    cannotBeEquipped = true;
                }

                badgeEntryOffsetX = 0;
                badgeEntryOffsetY = 0;
                if (isSelected) {
                    badgeEntryOffsetX = -1;
                    badgeEntryOffsetY = -1;
                }

                if (i == 0) {
                    style = DRAW_MSG_STYLE_MENU;
                    palette = MSG_PAL_STANDARD;
                    if (isSelected) {
                        style = DRAW_MSG_STYLE_MENU | DRAW_MSG_STYLE_DROP_SHADOW;
                    }

                    if (isEquipped) {
                        draw_box(
                            DRAW_FLAG_NO_CLIP, &gPauseWS_14, badgeListX + pause_badges_scroll_offset_x(posX) - 20,
                            baseY + pause_badges_scroll_offset_y(posY) + 17, 0, 200, 13, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            SCREEN_WIDTH, SCREEN_HEIGHT, 0
                        );
                    } else if (cannotBeEquipped) {
                        palette = MSG_PAL_0B;
                    }
                }

                if (!pause_badges_is_visible(posY)) {
                    continue;
                }

                if (i == 0) {
                    if (isNone) {
                        draw_msg(
                            pause_get_menu_msg(PAUSE_MSG_NO_BADGE),
                            badgeListX + pause_badges_scroll_offset_x(posX) + badgeEntryOffsetX,
                            badgeListY + pause_badges_scroll_offset_y(posY) + badgeEntryOffsetY, 255, palette, style
                        );
                    } else {
                        if (gItemTable[badgeID].nameMsg) {
                            if (gItemTable[badgeID].nameMsg > 0) {
                                draw_msg(
                                    gItemTable[badgeID].nameMsg,
                                    badgeListX + pause_badges_scroll_offset_x(posX) + badgeEntryOffsetX,
                                    badgeListY + pause_badges_scroll_offset_y(posY) + badgeEntryOffsetY, 255, palette,
                                    style
                                );
                            }
                        }
                        draw_number(
                            Mod_GetBadgeBPCost(badgeID), baseX + 235 + pause_badges_scroll_offset_x(posX),
                            baseY + 17 + pause_badges_scroll_offset_y(posY), DRAW_NUMBER_CHARSET_THIN, palette, 255,
                            DRAW_NUMBER_STYLE_ALIGN_RIGHT | DRAW_NUMBER_STYLE_MONOSPACE
                        );
                    }
                }

                if (i == 1) {
                    badgeIconElement = iconIDs[badgeIndex];
                    hud_element_clear_flags(badgeIconElement, HUD_ELEMENT_FLAG_DROP_SHADOW);
                    hud_element_set_flags(badgeIconElement, HUD_ELEMENT_FLAG_FILTER_TEX);
                    if (isNone) {
                        badgeIconElement = pauseIconIDs[21];
                    } else {
                        if (isSelected) {
                            hud_element_set_flags(badgeIconElement, HUD_ELEMENT_FLAG_DROP_SHADOW);
                            gPauseCurrentDescIconScript = gItemHudScripts[gItemTable[badgeID].hudElemID].enabled;
                        }

                        if (!isEquipped && cannotBeEquipped) {
                            hud_element_set_script(
                                badgeIconElement, gItemHudScripts[gItemTable[badgeID].hudElemID].disabled
                            );
                        } else {
                            hud_element_set_script(
                                badgeIconElement, gItemHudScripts[gItemTable[badgeID].hudElemID].enabled
                            );
                        }

                        hud_element_set_scale(badgeIconElement, 0.670816f);
                        hud_element_set_scale(badgeIconElement, TTYD64_bs_PauseBadgeIconScale());
                    }

                    hud_element_set_render_pos(
                        badgeIconElement,
                        baseX + 107 + pause_badges_scroll_offset_x(posX) + badgeEntryOffsetX,
                        baseY + 23 + pause_badges_scroll_offset_y(posY) + badgeEntryOffsetY
                    );
                    if (badgeIndex == 0) {
                        hud_element_draw_without_clipping(badgeIconElement);
                    } else {
                        hud_element_draw_next(badgeIconElement);
                    }

                    badgeIndex++;
                }

                if (i == 2 && !isNone) {
                    numOrbs = Mod_GetBadgeBPCost(badgeID);
                    orbOffsetY = 1;
                    if (numOrbs < 11) {
                        orbOffsetY = 4;
                    }

                    orbColorR1 = 0;
                    orbColorG1 = 255;
                    orbColorB1 = 100;

                    gSPDisplayList(gMainGfxPos++, PauseGfxOrbs);
                    gDPSetTextureFilter(gMainGfxPos++, G_TF_BILERP);

                    if (isEquipped == 0) {
                        for (j = 0; j < numOrbs; j++) {
                            gDPSetPrimColor(gMainGfxPos++, 0, 0, 227, 227, 227, 255);
                            orbX = baseX + 235 + pause_badges_scroll_offset_x(posX) + 1 + (j % 5) * 6;
                            orbY = baseY + 17 + pause_badges_scroll_offset_y(posY) + orbOffsetY;
                            if (numOrbs >= 5) {
                                orbY += j / 5 * 6 - 3;
                            }
                            pause_badges_draw_bp_orbs(0, orbX, orbY);
                        }

                        gDPPipeSync(gMainGfxPos++);
                        gDPSetRenderMode(gMainGfxPos++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
                        gDPSetPrimColor(gMainGfxPos++, 0, 0, orbColorR1, orbColorG1, orbColorB1, 128);

                        for (j = 0; j < numOrbs; j++) {
                            if (j < bpAvailable) {
                                orbX = baseX + 235 + pause_badges_scroll_offset_x(posX) + 1 + (j % 5) * 6;
                                orbY = baseY + 17 + pause_badges_scroll_offset_y(posY) + orbOffsetY;
                                if (numOrbs >= 5) {
                                    orbY += j / 5 * 6 - 3;
                                }
                                pause_badges_draw_bp_orbs(1, orbX, orbY);
                            }
                        }
                    } else {
                        gDPSetPrimColor(gMainGfxPos++, 0, 0, 0, 255, 100, 255);
                        for (j = 0; j < numOrbs; j++) {
                            orbX = baseX + 235 + pause_badges_scroll_offset_x(posX) + 1 + (j % 5) * 6;
                            orbY = baseY + 17 + pause_badges_scroll_offset_y(posY) + orbOffsetY;
                            if (numOrbs >= 5) {
                                orbY += j / 5 * 6 - 3;
                            }
                            pause_badges_draw_bp_orbs(2, orbX, orbY);
                        }
                        gDPPipeSync(gMainGfxPos++);
                    }
                }
            }
        }
    }

    x1 = baseX + 1;
    y1 = baseY + 1;
    x2 = baseX + width - 1;
    y2 = baseY + height - 1;
    gDPPipeSync(gMainGfxPos++);

    if (x1 <= 0) {
        x1 = 1;
    }
    if (y1 <= 0) {
        y1 = 1;
    }

    if (x2 <= 0 || y2 <= 0 || x1 >= SCREEN_WIDTH - 1 || y1 >= SCREEN_HEIGHT - 1) {
        return;
    }

    if (x2 >= SCREEN_WIDTH - 1) {
        x2 = SCREEN_WIDTH - 1;
    }
    if (y2 >= SCREEN_HEIGHT - 1) {
        y2 = SCREEN_HEIGHT - 1;
    }

    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, x1, y1, x2, y2);

    if (gPauseMenuCurrentTab == 2 && level == 1) {
        if (currentPageIdx > 0) {
            hud_element_set_render_pos(pauseIconIDs[17], baseX + 278, baseY + 14);
            hud_element_draw_without_clipping(pauseIconIDs[17]);
        }

        if (pages[currentPageIdx + 1].enabled) {
            hud_element_set_render_pos(pauseIconIDs[18], baseX + 278, baseY + 146);
            hud_element_draw_without_clipping(pauseIconIDs[18]);
        }
    }

    hud_element_set_render_pos(pauseIconIDs[16], baseX + 43, baseY + 0x2D);
    hud_element_draw_without_clipping(pauseIconIDs[16]);
    draw_msg(
        pause_get_menu_msg(PAUSE_MSG_BADGE_BP), baseX + 16, baseY + 74 - 0x23, 255, MSG_PAL_STANDARD,
        DRAW_MSG_STYLE_MENU
    );
    draw_number(
        playerData->maxBP, baseX + 69, baseY + 74 - 0x23, DRAW_NUMBER_CHARSET_THIN, MSG_PAL_STANDARD, 255,
        DRAW_NUMBER_STYLE_MONOSPACE | DRAW_NUMBER_STYLE_ALIGN_RIGHT
    );
    bpAmount = playerData->maxBP - pause_get_total_equipped_bp_cost();
    bpAvailOffsetX = 0;
    bpAvailOffsetY = (playerData->maxBP - 1) / 10 * 8;
    if (bpAmount < 10) {
        bpAvailOffsetX = -4;
    }
    pause_draw_menu_label(PAUSE_LBL_AVAILABLE, baseX + 12, baseY + 100 + bpAvailOffsetY - 0x26);

    if (bpAmount < 0) {
        bpAmount = 0;
    }
    bpAmountX = baseX + 73 + bpAvailOffsetX;

    draw_number(
        bpAmount, bpAmountX, baseY + 100 + bpAvailOffsetY - 0x26, DRAW_NUMBER_CHARSET_THIN, MSG_PAL_STANDARD, 255,
        DRAW_NUMBER_STYLE_MONOSPACE | DRAW_NUMBER_STYLE_ALIGN_RIGHT
    );

    orbColorR = 0;
    orbColorG = 255;
    orbColorB = 100;
    maxBP = playerData->maxBP;
    gSPDisplayList(gMainGfxPos++, PauseGfxOrbs);
    gDPSetTextureFilter(gMainGfxPos++, G_TF_BILERP);
    for (orbIndex = 0; orbIndex < maxBP; orbIndex++) {
        gDPSetPrimColor(gMainGfxPos++, 0, 0, 227, 227, 227, 255);
        pause_badges_draw_bp_orbs(0, baseX + 11 + (orbIndex % 10) * 6, baseY + 0x35 + (orbIndex / 10) * 8);
    }

    gDPPipeSync(gMainGfxPos++);
    if (canBeEquipped) {
        gDPSetPrimColor(gMainGfxPos++, 0, 0, orbColorR, orbColorG, orbColorB, 255);
        for (orbIndex = 0; orbIndex < bpAvailable - costBP; orbIndex++) {
            pause_badges_draw_bp_orbs(2, baseX + 11 + (orbIndex % 10) * 6, baseY + 0x35 + (orbIndex / 10) * 8);
        }

        gDPPipeSync(gMainGfxPos++);
        orbBlinkValue = (sin_deg(gGameStatusPtr->frameCounter * 15) + 1.0f) * 0.2 + 0.5;
        gDPSetRenderMode(gMainGfxPos++, G_RM_CLD_SURF, G_RM_CLD_SURF2);

        orbBlinkOpacity = orbBlinkValue * 255.0f;
        gDPSetPrimColor(gMainGfxPos++, 0, 0, orbColorR, orbColorG, orbColorB, orbBlinkOpacity);

        for (orbIndex = bpAvailable - costBP; orbIndex < bpAvailable; orbIndex++) {
            pause_badges_draw_bp_orbs(2, baseX + 11 + (orbIndex % 10) * 6, baseY + 0x35 + (orbIndex / 10) * 8);
        }
        gDPPipeSync(gMainGfxPos++);
    } else {
        gDPSetPrimColor(gMainGfxPos++, 0, 0, orbColorR, orbColorG, orbColorB, 255);
        for (orbIndex = 0; orbIndex < bpAvailable; orbIndex++) {
            pause_badges_draw_bp_orbs(2, baseX + 11 + (orbIndex % 10) * 6, baseY + 0x35 + (orbIndex / 10) * 8);
        }
        gDPPipeSync(gMainGfxPos++);
    }

    currentTab = *state->currentTab;
    draw_box(
        DRAW_FLAG_NO_CLIP, &gPauseWS_13, baseX, baseY + 7, 0, 0x5B, 0x20, 255, 0x80, 0, 0, 0, 0, 0, 0, 0, 0,
        SCREEN_WIDTH, SCREEN_HEIGHT, 0
    );
    pause_get_menu_msg(PAUSE_MSG_ALL_BADGES);

    currentTab = *state->currentTab;
    draw_box(
        DRAW_FLAG_NO_CLIP, &gPauseWS_13, currentTab == 1 ? baseX + 0x28 : baseX, baseY + 7, 0, 0x33, 0x20, 255, 0, 0, 0,
        0, 0, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0
    );
    pause_get_menu_msg(PAUSE_MSG_ACTIVE);
    pause_get_menu_msg(PAUSE_MSG_BADGES);

    currentTab = *state->currentTab;
    if (currentTab == 0) {
        draw_msg(sStringAllID, baseX + 0x10, baseY + 0xF, 0xFF, 0, 0);
    } else {
        draw_msg(sStringOnID, baseX + 0x39, baseY + 0xE, 0xFF, 0, 0);
    }

    if (gPauseMenuCurrentTab == 2) {
        if (level == 0) {
            pause_set_cursor_pos(WIN_PAUSE_BADGES, baseY + (*state->currentTab << 5) - 0xD, baseX + 0x2D);
        } else {
            selectedPosX = pause_badges_get_pos_x(
                currentPageIdx, selectedIndex - pages[currentPageIdx].listStart * pages[currentPageIdx].numCols
            );
            selectedPosY = pause_badges_get_pos_y(
                currentPageIdx, selectedIndex - pages[currentPageIdx].listStart * pages[currentPageIdx].numCols
            );
            cursorOffsetX = pause_badges_scroll_offset_x(selectedPosX);
            cursorOffsetY = pause_badges_scroll_offset_y(selectedPosY);
            if (cursorOffsetY < 0) {
                cursorOffsetY = 0;
            } else if (cursorOffsetY > 112) {
                cursorOffsetY = 112;
            }

            if (*state->currentScrollPos != *state->targetScrollPos) {
                pause_set_cursor_pos_immediate(
                    WIN_PAUSE_BADGES, baseX + 93 + cursorOffsetX, baseY + 23 + cursorOffsetY
                );
            } else {
                pause_set_cursor_pos(WIN_PAUSE_BADGES, baseX + 93 + cursorOffsetX, baseY + 23 + cursorOffsetY);
            }
        }
    }

    if (*state->showNotEnoughBP != 0) {
        pause_set_cursor_opacity(0);
        if (*state->showNotEnoughBP == 1) {
            draw_box(
                DRAW_FLAG_NO_CLIP, &gPauseWS_13, baseX + 67, baseY + 60, 0, 137, 26, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                SCREEN_WIDTH, SCREEN_HEIGHT, 0
            );
            draw_msg(
                pause_get_menu_msg(PAUSE_MSG_NOT_ENOUGH_BP), baseX + 86, baseY + 66, 255, MSG_PAL_WHITE,
                DRAW_MSG_STYLE_MENU
            );
        } else {
            s32 warningWidth = TTYD64_BS_PAUSE_WARNING_BOX_WIDTH;
            draw_box(
                DRAW_FLAG_NO_CLIP, &gPauseWS_13, baseX + 67, baseY + 60, 0, warningWidth, 26, 255, 0, 0, 0, 0, 0, 0, 0,
                0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0
            );
            draw_msg(
                pause_get_menu_msg(PAUSE_MSG_DONT_WEAR_MORE), baseX + 90, baseY + 66, 255, MSG_PAL_WHITE,
                DRAW_MSG_STYLE_MENU
            );
        }
    }
}

static PauseBadgesView sBadgesView;

static void hp_on_pause_badges_view(IEvent* event) {
    sBadgesView = *((OnPauseBadgesView*) event)->view;
}

static void hp_pause_badges_draw(const ModPanelDraw* draw) {
    if (sBadgesView.itemIds == nullptr) {
        return;
    }
    TTYD64_hp_PauseBadgesDraw(
        draw->panel, draw->x, draw->y, draw->width, draw->height, draw->opacity, draw->darkening, &sBadgesView
    );
}

static void hp_on_pause_badge_tab_buttons(IEvent* event) {
    *((OnPauseBadgeTabButtons*) event)->buttons = BUTTON_STICK_LEFT | BUTTON_STICK_RIGHT;
}

static void hp_on_pause_menu(IEvent* event) {
    OnPauseMenu* ev = (OnPauseMenu*) event;

    switch (ev->phase) {
        case PAUSE_MENU_OPEN:
            TTYD64_hp_PauseMenuInit();
            break;
        case PAUSE_MENU_CLOSE:
            TTYD64_hp_PauseMenuCleanup();
            break;
    }
}

static const ModPanelOps sPauseBadgesOps = {
    .draw = hp_pause_badges_draw,
};

void TTYD64_hp_InstallPauseBadges(void) {
    sStringAllID = Mod_RegisterInlineMessage("TTYD64", sString_All);
    sStringOnID = Mod_RegisterInlineMessage("TTYD64", sString_On);
    REGISTER_LISTENER(OnPauseBadgesView, EVENT_PRIORITY_NORMAL, hp_on_pause_badges_view);
    REGISTER_LISTENER(OnPauseBadgeTabButtons, EVENT_PRIORITY_NORMAL, hp_on_pause_badge_tab_buttons);
    REGISTER_LISTENER(OnPauseMenu, EVENT_PRIORITY_NORMAL, hp_on_pause_menu);
    Mod_ReplacePanel("TTYD64", MOD_PANEL_PAUSE_BADGES, &sPauseBadgesOps);
}
