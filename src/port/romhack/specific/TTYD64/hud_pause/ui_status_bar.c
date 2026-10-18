#include "hp_internal.h"
#include "port/hooks/Events.h"
#include "port/modding/Panels.h"
#include "assets/ui.h"

extern HudScript* SPIncrementHudScripts[];
extern HudScript* SPStarHudScripts[];
extern HudScript HES_StatusSPEmptyIncrement;
extern HudScript HES_StatusStarEmpty;

static const ALIGN_ASSET(2) char sTex_Mario[] = "__OTR__romhack/res/status_menu/mario_icon";
static const ALIGN_ASSET(2) char sPal_Mario[] = "__OTR__romhack/res/status_menu/mario_icon.pal";
static const ALIGN_ASSET(2) char sTex_Heart[] = "__OTR__romhack/res/status_menu/stat_heart";
static const ALIGN_ASSET(2) char sPal_Heart[] = "__OTR__romhack/res/status_menu/stat_heart.pal";

// clang-format off
#define TTYD64_HP_CI(raster, palette) HUD_ELEMENT_OP_SetCI, 60, (intptr_t) (raster), (intptr_t) (palette),
#define TTYD64_HP_IMAGE(time, icon, a, b) \
    HUD_ELEMENT_OP_SetImage, time, (intptr_t) ICON_##icon##_raster, (intptr_t) ICON_##icon##_palette, a, b,

HudScript TTYD64_hp_IconScript_FPPickup = {
    hs_SetVisible
    hs_SetSizesFixedScale(3, 2)
    TTYD64_HP_IMAGE(8, anim_fp_0, 3, 3)
    TTYD64_HP_IMAGE(5, anim_fp_1, 4, 4)
    TTYD64_HP_IMAGE(8, anim_fp_2, 5, 5)
    hs_Restart
    hs_End
};

HudScript TTYD64_hp_IconScript_LifeShroom = {
    hs_SetVisible
    hs_SetSizesFixedScale(3, 2)
    TTYD64_HP_IMAGE(60, food_LifeShroom, 4, 4)
    hs_Restart
    hs_End
};

HudScript TTYD64_hp_IconScript_LifeShroomBandW = {
    hs_SetVisible
    hs_SetSizesFixedScale(3, 2)
    TTYD64_HP_IMAGE(60, food_LifeShroom_disabled, 6, 10)
    hs_Restart
    hs_End
};

HudScript TTYD64_hp_IconScript_Star = {
    hs_SetVisible
    hs_SetSizesFixedScale(3, 2)
    TTYD64_HP_CI(ui_star_spirit_png, ui_star_spirit_pal)
    hs_Restart
    hs_End
};

HudScript TTYD64_IconScript_Mario = {
    hs_SetVisible
    hs_SetSizesFixedScale(3, 2)
    TTYD64_HP_CI(sTex_Mario, sPal_Mario)
    hs_Restart
    hs_End
};

HudScript TTYD64_hp_IconScript_Heart = {
    hs_SetVisible
    hs_SetSizesFixedScale(1, 2)
    TTYD64_HP_CI(sTex_Heart, sPal_Heart)
    hs_Restart
    hs_End
};
// clang-format on

TTYD64_hp_LSIconState TTYD64_hp_CurrentLSIcon;
u8 TTYD64_hp_PartnerHPAnimTimer;

const s32 TTYD64_hp_SPIncrementOffsets[7] = { 0x49, 0x4A, 0x4B, 0x4D, 0x4E, 0x4F, 0x50 };
const s16 TTYD64_hp_FirstBoxCoords[4] = { 0x000F, 0x0000, 0x005A, 0x001B };
const u8 TTYD64_hp_FirstBoxOpacity = 0xFF;

static HudScript* const sStatusIconScripts[] = {
    &TTYD64_hp_IconScript_Star,       &TTYD64_hp_IconScript_LifeShroomBandW,
    &TTYD64_hp_IconScript_LifeShroom, &TTYD64_hp_IconScript_Heart,
    &TTYD64_IconScript_Mario,         &TTYD64_IconScript_Goombario,
    &TTYD64_IconScript_Kooper,        &TTYD64_IconScript_Bombette,
    &TTYD64_IconScript_Parakarry,     &TTYD64_IconScript_Bow,
    &TTYD64_IconScript_Watt,          &TTYD64_IconScript_Sushie,
    &TTYD64_IconScript_Lakilester,
};

static s32 hp_abs_x(s32 absX) {
    return gStatusBar.drawPosX - 12 + absX;
}

static s32 sStatusIconsWorld[ARRAY_COUNT(sStatusIconScripts)];
static s32 sStatusIconsBattle[ARRAY_COUNT(sStatusIconScripts)];

static s32 hp_status_icon(s32 index) {
    if (gGameStatus.context == CONTEXT_WORLD) {
        return sStatusIconsWorld[index];
    }
    return sStatusIconsBattle[index];
}

void TTYD64_hp_CreateStatusIcons(s32 battle) {
    s32* icons = battle ? sStatusIconsBattle : sStatusIconsWorld;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sStatusIconScripts); i++) {
        icons[i] = TTYD64_CreateIcon(sStatusIconScripts[i]);
        if (i == 1) {
            TTYD64_hp_SetIconPalette(icons[i], 0xFAAFAF00);
        }
    }
}

void TTYD64_hp_UpdateCurrentLS(void) {
    if (find_item(ITEM_LIFE_SHROOM) == -1) {
        TTYD64_hp_CurrentLSIcon.lsType = 0;
    } else {
        TTYD64_hp_CurrentLSIcon.lsType = 1;
    }
}

void TTYD64_hp_StarMeterRemoveBrownOutline(void) {
    static const char* const palettes[] = {
        ui_status_pow_unit_1_pal, ui_status_pow_unit_2_pal, ui_status_pow_unit_3_pal, ui_status_pow_unit_4_pal,
        ui_status_pow_unit_5_pal, ui_status_pow_unit_6_pal, ui_status_pow_unit_7_pal,
    };
    s32 i;

    for (i = 0; i < ARRAY_COUNT(palettes); i++) {
        u8* data = (u8*) LOAD_ASSET(palettes[i]);

        if (data == nullptr || data == (u8*) palettes[i]) {
            continue;
        }
        if (data[0x14] | data[0x15] | data[0x16] | data[0x17]) {
            data[0x14] = 0;
            data[0x15] = 0;
            data[0x16] = 0;
            data[0x17] = 0;
            gDPInvalTexByPalette(gMainGfxPos++, data);
        }
    }
}

void TTYD64_hp_StatusBarInit(void) {
    StatusBar* statusBar = &gStatusBar;
    HudElemID hid;

    if (TTYD64_Function_GetPartnersUnlocked() != 0) {
        TTYD64_hp_SyncPartnerHP();
    }

    hid = statusBar->hpIconHIDs[1];
    hud_element_set_script(hid, &TTYD64_hp_IconScript_Heart);
    hid = statusBar->fpIconHIDs[1];
    hud_element_set_script(hid, &TTYD64_hp_IconScript_FPPickup);

    TTYD64_hp_CreateStatusIcons(false);
}

void TTYD64_hp_StatusBarSync(void) {
    if (TTYD64_Function_GetPartnersUnlocked() != 0) {
        TTYD64_hp_SyncPartnerHP();
    }
}

static void hp_draw_partner_hp(void) {
    StatusBar* statusBar = &gStatusBar;
    u8* bytes;
    u8 timer;

    if (TTYD64_Function_GetPartnersUnlocked() == 0) {
        return;
    }
    if (!TTYD64_hp_IsPartnerHPCompatible()) {
        return;
    }
    if (TTYD64_GetPartnerMaxHP() == 0) {
        TTYD64_updatePartnerMaxHP((u8) gPlayerData.curPartner);
    }
    switch ((u8) gPlayerData.curPartner) {
        case PARTNER_GOOMBARIO:
        case PARTNER_KOOPER:
        case PARTNER_BOMBETTE:
        case PARTNER_PARAKARRY:
        case PARTNER_BOW:
        case PARTNER_WATT:
        case PARTNER_SUSHIE:
        case PARTNER_LAKILESTER:
            break;
        default:
            return;
    }
    bytes = TTYD64_hp_PartnerHPBytes((u8) gPlayerData.curPartner);

    if (bytes[1] == bytes[0]) {
        timer = 0;
    } else {
        statusBar->showTimer = 0;
        statusBar->hidden = false;
        statusBar->unk_3B = true;
        if (bytes[0] < bytes[1]) {
            timer = TTYD64_hp_PartnerHPAnimTimer + 1;
            if (timer >= 4) {
                timer = 0;
                bytes[0] = bytes[0] + 1;
                TTYD64_hp_PlayHealSFX();
            }
        } else {
            timer = TTYD64_hp_PartnerHPAnimTimer + 1;
            if (timer >= 4) {
                timer = 0;
                bytes[0] = bytes[0] + 0xFF;
            }
        }
    }
    TTYD64_hp_PartnerHPAnimTimer = timer;
    status_bar_draw_stat(
        statusBar->hpTimesHID, statusBar->drawPosX + 0x17, statusBar->drawPosY + 0x1C, bytes[0], bytes[2]
    );
}

static void hp_draw_star_point_extras(void) {
    StatusBar* statusBar = &gStatusBar;
    s32 starIcon;
    s32 hid;
    s32 heartY;
    s32 leak;

    TTYD64_hp_UpdateCurrentLS();
    starIcon = hp_status_icon(0);

    hid = hp_status_icon(1 + TTYD64_hp_CurrentLSIcon.lsType);
    hud_element_set_render_pos(hid, statusBar->drawPosX + 0x4A, statusBar->drawPosY + 0xE);
    TTYD64_SetIconSize(hid, 15.0f, 15.0f);
    hud_element_draw_next(hid);

    if (gPlayerData.maxStarPower == 0) {
        hud_element_set_render_pos(starIcon, hp_abs_x(-0x14), statusBar->drawPosY + 0x22);
    } else {
        hud_element_set_render_pos(starIcon, statusBar->drawPosX + 0x53, statusBar->drawPosY + 0x22);
    }
    TTYD64_SetIconSize(starIcon, 20.0f, 20.0f);
    hud_element_draw_next(starIcon);

    hid = hp_status_icon(4);
    hud_element_set_render_pos(hid, hp_abs_x(0x16), gStatusBar.drawPosY + 0xF);
    TTYD64_SetIconSize(hid, 22.0f, 22.0f);
    hud_element_draw_next(hid);

    if (TTYD64_Function_GetPartnersUnlocked() != 0 && TTYD64_hp_IsPartnerHPCompatible()) {
        heartY = gStatusBar.drawPosY + 0x1D;
        hid = hp_status_icon(3);
        hud_element_set_render_pos(hid, hp_abs_x(0x1D), heartY);
        TTYD64_SetIconSize(hid, 16.0f, 16.0f);
        hud_element_draw_next(hid);

        leak = (heartY >= -24 && heartY <= 248) ? 0 : 0x1F;
        hid = hp_status_icon(TTYD64_hp_GetIconIndexPartnerIcon());
        hud_element_set_render_pos(hid, hp_abs_x(leak + 0x17), gStatusBar.drawPosY + 0x22);
        TTYD64_SetIconSize(hid, 22.0f, 22.0f);
        hud_element_draw_next(hid);
    }

    TTYD64_hp_StarMeterRemoveBrownOutline();
}

void TTYD64_hp_StatusBarDraw(void) {
    StatusBar* statusBar = &gStatusBar;
    PlayerData* playerData = &gPlayerData;
    s32 sp50;
    b32 showAddedBar;
    s32 i;
    s32 x;
    s32 y;
    s32 showStat;
    s32 id;
    s32 limit;
    s32 s7;
    s32 s1;
    s32 spBars;
    s32 boxX = hp_abs_x(TTYD64_hp_FirstBoxCoords[0]);
    s32 boxW = TTYD64_hp_FirstBoxCoords[2];
    s32 boxH = TTYD64_hp_FirstBoxCoords[3];
    s32 boxStyle = TTYD64_hp_BoxStyleBase;
    s32 boxOpacity = TTYD64_hp_FirstBoxOpacity;

    TTYD64_DrawBox(boxX, statusBar->drawPosY, boxW, boxH, boxStyle, boxOpacity);
    if (TTYD64_Function_GetPartnersUnlocked() != 0 && TTYD64_hp_IsPartnerHPCompatible()) {
        TTYD64_DrawBox(boxX, statusBar->drawPosY + 0x15, boxW - 0x10, boxH, boxStyle, boxOpacity);
    }
    TTYD64_DrawBox(boxX + 0x57, statusBar->drawPosY, boxW - 0xC, boxH, boxStyle + 1, boxOpacity);
    TTYD64_DrawBox(boxX + 0xA0, statusBar->drawPosY, boxW + 0x2A, boxH, boxStyle + 2, boxOpacity);
    if ((u8) playerData->maxStarPower != 0) {
        TTYD64_DrawBox(boxX + 0x49, statusBar->drawPosY + 0x18, boxW + 0x4C, boxH - 5, boxStyle + 3, boxOpacity);
    }

    if (statusBar->hpBlinkTimeLeft > 0) {
        statusBar->hpBlinkTimeLeft--;
        if (statusBar->hpBlinkTimeLeft == 0) {
            status_bar_stop_blinking_hp();
        }
    }

    showStat = true;
    if (statusBar->hpBlinking != false) {
        if (statusBar->hpBlinkAnimTime > 8) {
            showStat = false;
            if (statusBar->hpBlinkAnimTime > 12) {
                statusBar->hpBlinkAnimTime = 0;
                showStat = true;
            }
        }
        statusBar->hpBlinkAnimTime++;
    }

    if (showStat) {
        id = statusBar->hpIconHIDs[0];
        hud_element_set_render_pos(id, statusBar->drawPosX + 0x16, statusBar->drawPosY + 0xD);

        id = statusBar->hpIconHIDs[1];
        hud_element_set_render_pos(id, statusBar->drawPosX + 0x11, statusBar->drawPosY + 8);
        TTYD64_SetIconSize2(id, 16.0f, 16.0f);
        hud_element_draw_next(id);

        status_bar_draw_stat(
            statusBar->hpTimesHID, statusBar->drawPosX + 0x17, statusBar->drawPosY + 8, statusBar->displayHP,
            playerData->curMaxHP
        );
    }
    hp_draw_partner_hp();

    if (statusBar->fpBlinkTimeLeft > 0) {
        statusBar->fpBlinkTimeLeft--;
        if (statusBar->fpBlinkTimeLeft == 0) {
            status_bar_stop_blinking_fp();
        }
    }

    showStat = true;
    if (statusBar->fpBlinking != false) {
        if (statusBar->fpBlinkAnimTime > 8) {
            showStat = false;
            if (statusBar->fpBlinkAnimTime > 12) {
                statusBar->fpBlinkAnimTime = 0;
                showStat = true;
            }
        }
        statusBar->fpBlinkAnimTime++;
    }

    if (showStat) {
        id = statusBar->fpIconHIDs[0];
        hud_element_set_render_pos(id, statusBar->drawPosX + 0x6E, statusBar->drawPosY + 0xD);

        id = statusBar->fpIconHIDs[1];
        hud_element_set_render_pos(id, statusBar->drawPosX + 0x63, statusBar->drawPosY + 0xD);
        TTYD64_SetIconSize2(id, 26.0f, 26.0f);
        hud_element_draw_next(id);

        status_bar_draw_stat(
            statusBar->fpTimesHID, statusBar->drawPosX + 0x70, statusBar->drawPosY + 8, statusBar->displayFP,
            playerData->curMaxFP
        );
    }

    {
        StatLimits limits = STAT_LIMITS_VANILLA;
        CALL_EVENT(OnStatLimits, &limits);
        if (playerData->level >= limits.levelCap) {
            playerData->starPoints = 0;
        }
    }

    showStat = true;
    if (statusBar->starpointsBlinking != false) {
        if (statusBar->starpointsBlinkAnimTime > 8) {
            if (statusBar->starpointsBlinkAnimTime <= 12) {
                showStat = false;
            } else {
                statusBar->starpointsBlinkAnimTime = 0;
            }
        }
        statusBar->starpointsBlinkAnimTime++;
    }

    if (showStat) {
        id = statusBar->spIconHID;
        hud_element_set_render_pos(id, statusBar->drawPosX + 0xB8, statusBar->drawPosY + 0xE);
        hud_element_draw_next(id);

        id = statusBar->spShineHID;
        hud_element_set_render_pos(id, statusBar->drawPosX + 0xB8, statusBar->drawPosY + 9);
        hud_element_draw_next(id);

        hp_draw_star_point_extras();

        status_bar_draw_number(
            statusBar->spTimesHID, statusBar->drawPosX + 0xBD, statusBar->drawPosY + 8, playerData->starPoints, 2
        );
    }

    if (statusBar->coinsBlinkTimeLeft > 0) {
        statusBar->coinsBlinkTimeLeft--;
        if (statusBar->coinsBlinkTimeLeft == 0) {
            status_bar_stop_blinking_coins();
        }
    }

    showStat = true;
    if (statusBar->coinsBlinking != false) {
        if (statusBar->coinsBlinkAnimTime > 8) {
            showStat = false;
            if (statusBar->coinsBlinkAnimTime > 12) {
                statusBar->coinsBlinkAnimTime = 0;
                showStat = true;
            }
        }
        statusBar->coinsBlinkAnimTime++;
    }

    if (showStat) {
        id = statusBar->coinIconHID;
        hud_element_set_render_pos(id, statusBar->drawPosX + 0xEA, statusBar->drawPosY + 0xE);
        hud_element_draw_next(id);

        id = statusBar->coinSparkleHID;
        hud_element_set_render_pos(id, statusBar->drawPosX + 0xF4, statusBar->drawPosY + 0xE);
        hud_element_draw_next(id);

        status_bar_draw_number(
            statusBar->coinTimesHID, statusBar->drawPosX + 0xF0, statusBar->drawPosY + 8, statusBar->displayCoins, 3
        );
    }

    id = statusBar->starIconHID;
    showStat = true;
    if (statusBar->starPowerBlinking != false) {
        if (statusBar->starPowerBlinkCounter > 5) {
            if (statusBar->starPowerBlinkCounter <= 8) {
                showStat = false;
            } else {
                statusBar->starPowerBlinkCounter = 0;
                showStat = true;
            }
        }
        statusBar->starPowerBlinkCounter++;
    }

    x = statusBar->drawPosX + 20;
    y = statusBar->drawPosY + 0x23;

    spBars = statusBar->displayStarPower / SP_PER_BAR;
    limit = statusBar->displayStarPower % SP_PER_BAR;
    limit /= 32;
    limit += spBars * 8;
    if (statusBar->shimmerState == 1) {
        spBars = playerData->starPower / SP_PER_BAR;
        limit = playerData->starPower % SP_PER_BAR;
        limit = limit / 32;
        limit += spBars * 8;
        star_power_shimmer_start(0, (f32) (x + limit * 25 / 10) + 64.0f, (f32) y + 4.0f, 1.0f);
        statusBar->shimmerState = 2;
    }

    showAddedBar = false;
    if (statusBar->shimmerState != 0) {
        if (statusBar->shimmerTime != 0) {
            statusBar->shimmerTime--;
        } else {
            statusBar->shimmerState = 0;
        }
        if ((statusBar->shimmerTime / 5) & 1) {
            showAddedBar = true;
        }
        s7 = statusBar->shimmerLimit % 8;
        s7 += (statusBar->shimmerLimit / 8) * 8;
    } else {
        s7 = limit;
    }

    i = 0;
    sp50 = 0;
    s1 = 0;

    if (statusBar->starPowerBlinking != false) {
        if (!showStat) {
            s32 blinkLimit = statusBar->powBarsToBlink * 8;

            if (sp50 < blinkLimit) {
                while (true) {
                    i++;
                    s1++;
                    if (i >= blinkLimit) {
                        break;
                    }
                    i++;
                    s1++;
                    if (i >= blinkLimit) {
                        break;
                    }
                    i++;
                    s1++;
                    if (i >= blinkLimit) {
                        break;
                    }
                    i++;
                    s1++;
                    if (i >= blinkLimit) {
                        break;
                    }
                    i++;
                    s1++;
                    if (i >= blinkLimit) {
                        break;
                    }
                    i++;
                    s1++;
                    if (i >= blinkLimit) {
                        break;
                    }
                    i++;
                    s1++;
                    if (i >= blinkLimit) {
                        break;
                    }
                    i++;
                    s1 = 0;
                    sp50++;
                    if (i >= blinkLimit) {
                        break;
                    }
                }
            }
        }
    }

    while (true) {
        s32 k;

        for (k = 0; k < 7; k++) {
            if (i >= limit || (i >= s7 && !showAddedBar)) {
                goto filled_done;
            }
            i++;
            hud_element_set_script(id, SPIncrementHudScripts[sp50]);
            hud_element_set_render_pos(id, x + sp50 * 20 + TTYD64_hp_SPIncrementOffsets[k], y - 2);
            hud_element_draw_next(id);
            s1++;
        }

        if (i >= limit || (i >= s7 && !showAddedBar)) {
            break;
        }
        i++;
        hud_element_set_script(id, SPStarHudScripts[sp50]);
        hud_element_set_render_pos(id, x + 0x56 + sp50 * 20, y);
        hud_element_draw_next(id);

        s1 = 0;
        sp50++;
        if (i >= limit || (i >= s7 && !showAddedBar)) {
            break;
        }
    }
filled_done:

    limit = playerData->maxStarPower * 8;
    while (true) {
        if (i >= limit) {
            break;
        }
        while (s1 < 7) {
            i++;
            hud_element_set_script(id, &HES_StatusSPEmptyIncrement);
            hud_element_set_render_pos(id, x + sp50 * 20 + TTYD64_hp_SPIncrementOffsets[s1], y - 2);
            hud_element_draw_next(id);
            if (i >= limit) {
                goto empty_done;
            }
            s1++;
        }
        if (s1 == 7) {
            i++;
            hud_element_set_script(id, &HES_StatusStarEmpty);
            hud_element_set_render_pos(id, x + 0x56 + sp50 * 20, y);
            hud_element_draw_next(id);
            if (i >= limit) {
                break;
            }
        }
        s1 = 0;
        sp50++;
    }
empty_done:

    star_power_shimmer_update();
    star_power_shimmer_draw();
}

static void hp_status_bar_init(MenuPanel* panel) {
    TTYD64_hp_StatusBarInit();
}

static void hp_status_bar_draw(const ModPanelDraw* draw) {
    TTYD64_hp_StatusBarDraw();
}

static const ModPanelOps sStatusBarOps = {
    .init = hp_status_bar_init,
    .sync = TTYD64_hp_StatusBarSync,
    .draw = hp_status_bar_draw,
};

static void hp_on_battle_init(IEvent* event) {
    OnBattleInit* ev = (OnBattleInit*) event;

    if (ev->stage == BATTLE_INIT_END) {
        TTYD64_hp_CreateStatusIcons(true);
    }
}

void TTYD64_hp_InstallStatusBar(void) {
    Mod_ReplacePanel("TTYD64", MOD_PANEL_STATUS_BAR, &sStatusBarOps);
    REGISTER_LISTENER(OnBattleInit, EVENT_PRIORITY_NORMAL, hp_on_battle_init);
}
