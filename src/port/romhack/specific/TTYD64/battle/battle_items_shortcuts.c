#include "port/romhack/specific/TTYD64/battle/battle_items_internal.h"
#include "assets/ui.h"
#include "battle/battle_menu.h"
#include "port/patches/Patches.h"
#include "port/modding/Mod.h"

extern s8 BattleMenuState;
extern s16 BattleMenuAlpha;
extern HudElementList gHudElementsWorld;
extern HudElementList gHudElementsBattle;
extern HudScript HES_ProjectorSpot;

static const ALIGN_ASSET(2) char sTex_C[] = "__OTR__romhack/res/battle_shorcuts/c_middle";
static const ALIGN_ASSET(2) char sPal_C[] = "__OTR__romhack/res/battle_shorcuts/c_middle.pal";
static const ALIGN_ASSET(2) char sTex_RButton[] = "__OTR__romhack/res/battle_shorcuts/r_button";
static const ALIGN_ASSET(2) char sTex_Equal[] = "__OTR__romhack/res/battle_shorcuts/equal";
static const ALIGN_ASSET(2) char sPal_2831080[] = "__OTR__romhack/res/battle_shorcuts/equal.pal";
static const ALIGN_ASSET(2) char sPal_28310A0[] = "__OTR__romhack/res/battle_shorcuts/r_button.pal";
static const ALIGN_ASSET(2) char sTex_Goombario[] = "__OTR__romhack/res/status_menu/goombario_icon";
static const ALIGN_ASSET(2) char sPal_Goombario[] = "__OTR__romhack/res/status_menu/goombario_icon.pal";
static const ALIGN_ASSET(2) char sTex_Kooper[] = "__OTR__romhack/res/status_menu/kooper_icon";
static const ALIGN_ASSET(2) char sPal_Kooper[] = "__OTR__romhack/res/status_menu/kooper_icon.pal";
static const ALIGN_ASSET(2) char sTex_Bombette[] = "__OTR__romhack/res/status_menu/bombette_icon";
static const ALIGN_ASSET(2) char sPal_Bombette[] = "__OTR__romhack/res/status_menu/bombette_icon.pal";
static const ALIGN_ASSET(2) char sTex_Parakarry[] = "__OTR__romhack/res/status_menu/parakarry_icon";
static const ALIGN_ASSET(2) char sPal_Parakarry[] = "__OTR__romhack/res/status_menu/parakarry_icon.pal";
static const ALIGN_ASSET(2) char sTex_Bow[] = "__OTR__romhack/res/status_menu/bow_icon";
static const ALIGN_ASSET(2) char sPal_Bow[] = "__OTR__romhack/res/status_menu/bow_icon.pal";
static const ALIGN_ASSET(2) char sTex_Watt[] = "__OTR__romhack/res/status_menu/watt_icon";
static const ALIGN_ASSET(2) char sPal_Watt[] = "__OTR__romhack/res/status_menu/watt_icon.pal";
static const ALIGN_ASSET(2) char sTex_Sushie[] = "__OTR__romhack/res/status_menu/sushie_icon";
static const ALIGN_ASSET(2) char sPal_Sushie[] = "__OTR__romhack/res/status_menu/sushie_icon.pal";
static const ALIGN_ASSET(2) char sTex_Lakilester[] = "__OTR__romhack/res/status_menu/lakilester_icon";
static const ALIGN_ASSET(2) char sPal_Lakilester[] = "__OTR__romhack/res/status_menu/lakilester_icon.pal";

#define TTYD64_BI_CI(raster, palette) HUD_ELEMENT_OP_SetCI, 60, (intptr_t) (raster), (intptr_t) (palette),

// clang-format off
HudScript TTYD64_bi_IconScript_C = {
    hs_SetVisible
    hs_SetSizesFixedScale(1, 4)
    TTYD64_BI_CI(sTex_C, sPal_C)
    hs_End
    HUD_ELEMENT_OP_End,
    HUD_ELEMENT_OP_Restart,
    HUD_ELEMENT_OP_End,
};

HudScript TTYD64_bi_IconScript_RButton = {
    hs_SetVisible
    hs_SetSizesFixedScale(1, 4)
    TTYD64_BI_CI(sTex_RButton, sPal_2831080)
    hs_End
    HUD_ELEMENT_OP_End,
    HUD_ELEMENT_OP_Restart,
    HUD_ELEMENT_OP_End,
};

HudScript TTYD64_bi_IconScript_Equal = {
    hs_SetVisible
    hs_SetSizesFixedScale(1, 4)
    TTYD64_BI_CI(sTex_Equal, sPal_28310A0)
    hs_End
    HUD_ELEMENT_OP_End,
    HUD_ELEMENT_OP_Restart,
    HUD_ELEMENT_OP_End,
};

#define TTYD64_BI_MENU_ICON(icon)    \
    {                                \
        hs_SetVisible                \
        hs_SetSizesFixedScale(3, 2)  \
        hs_SetIcon(60, icon)         \
        hs_Restart                   \
        hs_End                       \
    }

HudScript TTYD64_bi_IconScript_Boots1 = TTYD64_BI_MENU_ICON(menu_boots_1);
HudScript TTYD64_bi_IconScript_Boots2 = TTYD64_BI_MENU_ICON(menu_boots_2);
HudScript TTYD64_bi_IconScript_Boots3 = TTYD64_BI_MENU_ICON(menu_boots_3);
HudScript TTYD64_bi_IconScript_Hammer1 = TTYD64_BI_MENU_ICON(menu_hammer_1);
HudScript TTYD64_bi_IconScript_Hammer2 = TTYD64_BI_MENU_ICON(menu_hammer_2);
HudScript TTYD64_bi_IconScript_Hammer3 = TTYD64_BI_MENU_ICON(menu_hammer_3);
HudScript TTYD64_bi_IconScript_Items = TTYD64_BI_MENU_ICON(menu_items);

HudScript TTYD64_bi_IconScript_StarSpirits = {
    hs_SetVisible
    hs_SetSizesFixedScale(3, 2)
    hs_SetCI(60, ui_star_spirit)
    hs_Restart
    hs_End
};

HudScript TTYD64_bi_IconScript_Strategies = {
    hs_SetVisible
    hs_SetSizesFixedScale(3, 4)
    hs_SetCI(60, ui_battle_menu_strategies)
    hs_Restart
    hs_End
};

#define TTYD64_BI_PARTNER_ICON(raster, palette) \
    {                                           \
        hs_SetVisible                           \
        hs_SetSizesFixedScale(3, 2)             \
        TTYD64_BI_CI(raster, palette)           \
        hs_Restart                              \
        hs_End                                  \
    }

HudScript TTYD64_IconScript_Goombario = TTYD64_BI_PARTNER_ICON(sTex_Goombario, sPal_Goombario);
HudScript TTYD64_IconScript_Kooper = TTYD64_BI_PARTNER_ICON(sTex_Kooper, sPal_Kooper);
HudScript TTYD64_IconScript_Bombette = TTYD64_BI_PARTNER_ICON(sTex_Bombette, sPal_Bombette);
HudScript TTYD64_IconScript_Parakarry = TTYD64_BI_PARTNER_ICON(sTex_Parakarry, sPal_Parakarry);
HudScript TTYD64_IconScript_Bow = TTYD64_BI_PARTNER_ICON(sTex_Bow, sPal_Bow);
HudScript TTYD64_IconScript_Watt = TTYD64_BI_PARTNER_ICON(sTex_Watt, sPal_Watt);
HudScript TTYD64_IconScript_Sushie = TTYD64_BI_PARTNER_ICON(sTex_Sushie, sPal_Sushie);
HudScript TTYD64_IconScript_Lakilester = TTYD64_BI_PARTNER_ICON(sTex_Lakilester, sPal_Lakilester);
// clang-format on

static HudScript* const sShortcutIconScripts[] = {
    &HES_ProjectorSpot,
    &TTYD64_bi_IconScript_C,
    &TTYD64_bi_IconScript_RButton,
    &TTYD64_bi_IconScript_Equal,
    &TTYD64_bi_IconScript_Boots1,
    &TTYD64_bi_IconScript_Boots2,
    &TTYD64_bi_IconScript_Boots3,
    &TTYD64_bi_IconScript_Hammer1,
    &TTYD64_bi_IconScript_Hammer2,
    &TTYD64_bi_IconScript_Hammer3,
    &TTYD64_bi_IconScript_StarSpirits,
    &TTYD64_bi_IconScript_Items,
    &TTYD64_bi_IconScript_Strategies,
    &TTYD64_IconScript_Goombario,
    &TTYD64_IconScript_Kooper,
    &TTYD64_IconScript_Bombette,
    &TTYD64_IconScript_Parakarry,
    &TTYD64_IconScript_Bow,
    &TTYD64_IconScript_Watt,
    &TTYD64_IconScript_Sushie,
    &TTYD64_IconScript_Lakilester,
};

static u8 sShortcutData[4];
static HudElemID sShortcutIcons[ARRAY_COUNT(sShortcutIconScripts)];
static HudElemID sShortcutIndexes[4];
static const u16 sIconGroup1_MainOffset[2] = { 0xA7, 0xDC };
static const u16 sIconGroup2_MainOffset[2] = { 0xC1, 0xDC };

void TTYD64_SetIconSize2(s32 hid, f32 width, f32 height) {
    HudElementList* list = (gGameStatus.context == CONTEXT_WORLD) ? &gHudElementsWorld : &gHudElementsBattle;
    HudElement* elem;

    if ((u32) hid >= ARRAY_COUNT(*list)) {
        return;
    }
    elem = (*list)[hid];
    elem->dynamicSize.x = width;
    elem->dynamicSize.y = height;
}

static b32 bi_shortcuts_disabled(void) {
    if (evt_get_variable(nullptr, TTYD64_ModFlag(TTYD64_MF_Flag_DisableShortcuts)) != 0) {
        return true;
    }
    return gGameStatus.peachFlags != 0;
}

static void bi_shortcuts_restore_pos(void) {
    if (bi_shortcuts_disabled() || sShortcutData[0] != 2) {
        return;
    }
    BattleMenu_CurPos = (s8) sShortcutData[1];
    sShortcutData[0] = 0;
    sShortcutData[1] = 0;
    sShortcutData[2] = 0;
    sShortcutData[3] = 0;
}

static void bi_shortcuts_track_inputs(IEvent* event) {
    s32 isMarioWheel;
    u8 buttons;
    u8 lastPos;
    s32 newPos;

    if (bi_shortcuts_disabled()) {
        return;
    }

    if (sShortcutData[0] != 0) {
        if (sShortcutData[0] == 2) {
            return;
        }
        if (BattleMenu_ChooseDelay != 0) {
            return;
        }
        BattleMenu_CurPos = (s8) sShortcutData[2];
        BattleMenuState = (s8) 0xFF;
        sfx_play_sound(SOUND_MENU_NEXT);
        sShortcutData[0] = 2;
        return;
    }

    if (BattleMenuAlpha != 0xFF) {
        return;
    }

    isMarioWheel = (gBattleState == BATTLE_STATE_PLAYER_MENU);
    buttons = gGameStatus.pressedButtons[0] & 0xFF;
    lastPos = BattleMenu_PrevSelected & 0xFF;

    if (buttons & BUTTON_C_DOWN) {
        if (isMarioWheel) {
            if ((u8) WheelOptionEnabled[3] == 0) {
                goto error;
            }
            newPos = 3;
        } else {
            if ((u8) WheelOptionEnabled[1] == 0) {
                goto error;
            }
            newPos = 1;
        }
    } else if (buttons & BUTTON_C_UP) {
        if (isMarioWheel) {
            if ((u8) WheelOptionEnabled[2] == 0) {
                goto error;
            }
            newPos = 2;
        } else {
            if ((u8) WheelOptionEnabled[1] == 0) {
                goto error;
            }
            newPos = 1;
        }
    } else if (buttons & BUTTON_C_RIGHT) {
        if (isMarioWheel) {
            if ((u8) gPlayerData.maxStarPower == 0) {
                goto error;
            }
            if ((u8) WheelOptionEnabled[4] == 0) {
                goto error;
            }
            newPos = 4;
        } else {
            if ((u8) WheelOptionEnabled[1] == 0) {
                goto error;
            }
            newPos = 1;
        }
    } else if (buttons & BUTTON_C_LEFT) {
        if (isMarioWheel) {
            if ((u8) WheelOptionEnabled[1] == 0) {
                goto error;
            }
            newPos = 1;
        } else {
            if ((u8) WheelOptionEnabled[2] == 0) {
                goto error;
            }
            newPos = 2;
        }
    } else if (buttons & BUTTON_R) {
        if ((u8) WheelOptionEnabled[0] == 0) {
            goto error;
        }
        newPos = 0;
    } else {
        return;
    }

    newPos -= lastPos;
    sShortcutData[1] = BattleMenu_CurPos;
    sShortcutData[2] = newPos;
    sShortcutData[0] = 1;
    return;

error:
    sfx_play_sound(SOUND_MENU_ERROR);
}

static void bi_shortcuts_draw_icon(s32 hid, s32 x, s32 y, f32 width, f32 height) {
    hud_element_set_render_pos(hid, x, y - SCREEN_INSET_Y + port_btl_menu_y());
    TTYD64_SetIconSize2(hid & ~HUD_ELEMENT_BATTLE_ID_MASK, width, height);
    hud_element_draw_next(hid);
}

static void bi_shortcuts_draw(void) {
    if (bi_shortcuts_disabled()) {
        return;
    }
    if (BattleMenuAlpha == 100) {
        return;
    }

    bi_shortcuts_draw_icon(sShortcutIcons[1], sIconGroup1_MainOffset[0], sIconGroup1_MainOffset[1], 13.0f, 13.0f);
    bi_shortcuts_draw_icon(sShortcutIcons[2], sIconGroup2_MainOffset[0], sIconGroup2_MainOffset[1], 15.0f, 15.0f);
    bi_shortcuts_draw_icon(sShortcutIcons[3], sIconGroup2_MainOffset[0] + 9, sIconGroup2_MainOffset[1], 15.0f, 12.0f);
    bi_shortcuts_draw_icon(
        sShortcutIcons[0xC], sIconGroup2_MainOffset[0] + 0x12, sIconGroup2_MainOffset[1], 11.0f, 11.0f
    );

    if (gBattleState == BATTLE_STATE_PLAYER_MENU) {
        u8 boots = gPlayerData.bootsLevel;
        u8 hammer = gPlayerData.hammerLevel;

        sShortcutIndexes[0] = sShortcutIcons[boots == 0 ? 4 : boots == 1 ? 5 : 6];
        sShortcutIndexes[1] = sShortcutIcons[0xA];
        sShortcutIndexes[2] = sShortcutIcons[hammer == 0 ? 7 : hammer == 1 ? 8 : 9];
        sShortcutIndexes[3] = sShortcutIcons[0xB];
    } else {
        u8 partner = gPlayerData.curPartner;
        HudElemID index = sShortcutIcons[0];

        switch (partner) {
            case PARTNER_GOOMBARIO:
                index = sShortcutIcons[0xD];
                break;
            case PARTNER_KOOPER:
                index = sShortcutIcons[0xE];
                break;
            case PARTNER_BOMBETTE:
                index = sShortcutIcons[0xF];
                break;
            case PARTNER_PARAKARRY:
                index = sShortcutIcons[0x10];
                break;
            case PARTNER_BOW:
                index = sShortcutIcons[0x11];
                break;
            case PARTNER_WATT:
                index = sShortcutIcons[0x12];
                break;
            case PARTNER_SUSHIE:
                index = sShortcutIcons[0x13];
                break;
            case PARTNER_LAKILESTER:
                index = sShortcutIcons[0x14];
                break;
        }
        sShortcutIndexes[0] = index;
        sShortcutIndexes[1] = index;
        sShortcutIndexes[2] = index;
        sShortcutIndexes[3] = sShortcutIcons[0xB];
    }

    bi_shortcuts_draw_icon(
        sShortcutIndexes[0], sIconGroup1_MainOffset[0], sIconGroup1_MainOffset[1] - 11, 11.0f, 11.0f
    );
    bi_shortcuts_draw_icon(
        sShortcutIndexes[1], sIconGroup1_MainOffset[0] + 10, sIconGroup1_MainOffset[1], 11.0f, 11.0f
    );
    bi_shortcuts_draw_icon(sShortcutIndexes[2], sIconGroup1_MainOffset[0], sIconGroup1_MainOffset[1] + 9, 11.0f, 11.0f);
    bi_shortcuts_draw_icon(
        sShortcutIndexes[3], sIconGroup1_MainOffset[0] - 11, sIconGroup1_MainOffset[1], 11.0f, 11.0f
    );
}

static void bi_shortcuts_create(const BattleMenuContext* ctx) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sShortcutIconScripts); i++) {
        sShortcutIcons[i] = TTYD64_CreateIcon(sShortcutIconScripts[i]);
    }
}

static void bi_shortcuts_destroy(const BattleMenuContext* ctx) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sShortcutIcons); i++) {
        hud_element_free(sShortcutIcons[i]);
        sShortcutIcons[i] = 0;
    }
}

static void bi_shortcuts_draw_entry(
    const BattleMenuContext* ctx, s32 index, const BattleMenuEntry* entry, s32 x, s32 y, s32 alpha
) {
    if (index == 0) {
        bi_shortcuts_restore_pos();
    }
    bi_shortcuts_draw();
}

void TTYD64_InstallBattleItemsShortcuts(void) {
    static const BattleMenuHud sWheelHud = { bi_shortcuts_create, bi_shortcuts_destroy, bi_shortcuts_draw_entry };

    Mod_AddBattleMenuHud("TTYD64", BATTLE_MENU_WHEEL, &sWheelHud);
    REGISTER_LISTENER(OnBattleMainMenuInput, EVENT_PRIORITY_NORMAL, bi_shortcuts_track_inputs);
}
