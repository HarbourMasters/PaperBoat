#include "battle/battle.h"
#include "battle_hud_scripts.h"
#include "port/patches/Patches.h"

#define BTL_MENU_Y(y) ((y) + port_btl_menu_y())
#define MENU_CAPACITY 6

#define WHEEL_SPACING (28.0f)
#define WHEEL_RADIUS (87.0f)

#define REEL_APPEAR_TIME (3)

enum BattleMenuStates {
    BTL_MENU_STATE_SUBMENU_OPEN         = -1,
    BTL_MENU_STATE_CREATE               = 0,
    BTL_MENU_STATE_SHOW_REEL            = 1,
    BTL_MENU_STATE_CHOOSING             = 2,
    BTL_MENU_STATE_HIDE_INIT            = 10,
    BTL_MENU_STATE_HIDE_HOLD            = 11,
    BTL_MENU_STATE_RESTORE              = 20, // reappear and resume choosing
    BTL_MENU_STATE_RESUME_SUBMENU       = 30,
    BTL_MENU_STATE_ERROR_SHOW           = 100,
    BTL_MENU_STATE_ERROR_DONE           = 101,
};

extern HudScript HES_YellowArrow;

extern HudScript HES_MenuFlee;
extern HudScript HES_MenuFleeDisabled;
extern HudScript HES_MenuDefend;
extern HudScript HES_MenuDefendDisabled;
extern HudScript HES_MenuStrategies;
extern HudScript HES_MenuStrategiesDisabled;
extern HudScript HES_MenuPouch;
extern HudScript HES_MenuPouchDisabled;
extern HudScript HES_MenuDoNothing;
extern HudScript HES_MenuDoNothingDisabled;

extern HudScript HES_Kooper;
extern HudScript HES_Bombette;
extern HudScript HES_Partner0;
extern HudScript HES_Partner0Disabled;
extern HudScript HES_Goombario;
extern HudScript HES_GoombarioDisabled;
extern HudScript HES_KooperDisabled;
extern HudScript HES_BombetteDisabled;
extern HudScript HES_Parakarry;
extern HudScript HES_ParakarryDisabled;
extern HudScript HES_Bow;
extern HudScript HES_BowDisabled;
extern HudScript HES_Watt;
extern HudScript HES_WattDisabled;
extern HudScript HES_Sushie;
extern HudScript HES_SushieDisabled;
extern HudScript HES_Lakilester;
extern HudScript HES_LakilesterDisabled;
extern HudScript HES_PartnerA;
extern HudScript HES_PartnerADisabled;

extern HudScript HES_MenuBoots1;
extern HudScript HES_MenuBoots1Disabled;
extern HudScript HES_MenuBoots2;
extern HudScript HES_MenuBoots2Disabled;
extern HudScript HES_MenuBoots3;
extern HudScript HES_MenuBoots3Disabled;

extern HudScript HES_MenuHammer1;
extern HudScript HES_MenuHammer1Disabled;
extern HudScript HES_MenuHammer2;
extern HudScript HES_MenuHammer2Disabled;
extern HudScript HES_MenuHammer3;
extern HudScript HES_MenuHammer3Disabled;

extern HudScript HES_MenuItem;
extern HudScript HES_MenuItemDisabled;

extern HudScript HES_MenuStarPower;
extern HudScript HES_MenuStarPowerDisabled;

extern HudScript HES_Eldstar;
extern HudScript HES_EldstarDisabled;
extern HudScript HES_Mamar;
extern HudScript HES_MamarDisabled;
extern HudScript HES_Skolar;
extern HudScript HES_SkolarDisabled;
extern HudScript HES_Muskular;
extern HudScript HES_MuskularDisabled;
extern HudScript HES_Misstar;
extern HudScript HES_MisstarDisabled;
extern HudScript HES_Klevar;
extern HudScript HES_KlevarDisabled;
extern HudScript HES_Kalmar;
extern HudScript HES_KalmarDisabled;
extern HudScript HES_StarBeam;
extern HudScript HES_StarBeamDisabled;
extern HudScript HES_PeachBeam;
extern HudScript HES_PeachBeamDisabled;

extern HudScript HES_MoveDiamond;
extern HudScript HES_MoveDiamond_disabled;
extern HudScript HES_MoveBlueOrb;
extern HudScript HES_MoveBlueOrbDisabled;
extern HudScript HES_MoveGreenOrb;
extern HudScript HES_MoveGreenOrbDisabled;
extern HudScript HES_MoveRedOrb;
extern HudScript HES_MoveRedOrbDisabled;

extern HudScript HES_HandPointDownLoop;
extern HudScript HES_HandPointLeftLoop;

extern HudScript HES_ProjectorBeam;
extern HudScript HES_ProjectorReel;
extern HudScript HES_ProjectorSpot;
extern HudScript HES_SwapArrowLeft;
extern HudScript HES_SwapArrowRight;
extern HudScript HES_SwapBackground;
extern HudScript HES_SwapZ;

IconHudScriptPair ItemsHudScripts = { &HES_MenuItem, &HES_MenuItemDisabled };

IconHudScriptPair StarPowersHudScripts = { &HES_MenuStarPower, &HES_MenuStarPowerDisabled };

IconHudScriptPair StarPowerMovesHudScripts[] = {
    { &HES_MenuStarPower,   &HES_MenuStarPowerDisabled },
    { &HES_Eldstar,         &HES_EldstarDisabled },
    { &HES_Mamar,           &HES_MamarDisabled },
    { &HES_Skolar,          &HES_SkolarDisabled },
    { &HES_Muskular,        &HES_MuskularDisabled },
    { &HES_Misstar,         &HES_MisstarDisabled },
    { &HES_Klevar,          &HES_KlevarDisabled },
    { &HES_Kalmar,          &HES_KalmarDisabled },
    { &HES_StarBeam,        &HES_StarBeamDisabled },
    { &HES_PeachBeam,       &HES_PeachBeamDisabled },
    { &HES_MenuStarPower,   &HES_MenuStarPowerDisabled },
    { &HES_MenuStarPower,   &HES_MenuStarPowerDisabled },
};

IconHudScriptPair PartnerHudScripts[] = {
    { &HES_Partner0,        &HES_Partner0Disabled },
    { &HES_Goombario,       &HES_GoombarioDisabled },
    { &HES_Kooper,          &HES_KooperDisabled },
    { &HES_Bombette,        &HES_BombetteDisabled },
    { &HES_Parakarry,       &HES_ParakarryDisabled },
    { &HES_Partner0,        &HES_Partner0Disabled },
    { &HES_Watt,            &HES_WattDisabled },
    { &HES_Sushie,          &HES_SushieDisabled },
    { &HES_Lakilester,      &HES_LakilesterDisabled },
    { &HES_Bow,             &HES_BowDisabled },
    { &HES_PartnerA,        &HES_PartnerADisabled },
    { &HES_PartnerA,        &HES_PartnerADisabled },
    { &HES_PartnerA,        &HES_PartnerADisabled },
    { &HES_PartnerA,        &HES_PartnerADisabled },
    { &HES_PartnerA,        &HES_PartnerADisabled },
    { &HES_PartnerA,        &HES_PartnerADisabled }
};

IconHudScriptPair StrategiesHudScripts = { &HES_MenuStrategies, &HES_MenuStrategiesDisabled };

IconHudScriptPair DoNothingHudScripts = { &HES_MenuDoNothing, &HES_MenuDoNothingDisabled };

IconHudScriptPair FleeHudScripts = { &HES_MenuFlee, &HES_MenuFleeDisabled };

s32 LeftJustMenuMessages[] = {
    MSG_Menus_Jump,
    MSG_Menus_Hammer,
    MSG_Menus_Items,
    MSG_Menus_RunAway,
    MSG_Menus_Defense,
    MSG_Menus_ChangeMember,
    MSG_Menus_Abilities,
    MSG_Menus_Strategies,
    MSG_Menus_StarSpirits,
    MSG_Menus_DoNothing,
    MSG_Menus_ActLater,
    MSG_Menus_Focus,
};

s32 CenteredBattleMessages[] = {
    MSG_Menus_Jump_Centered,
    MSG_Menus_Hammer_Centered,
    MSG_Menus_Items_Centered,
    MSG_Menus_RunAway_Centered,
    MSG_Menus_Defense_Centered,
    MSG_Menus_ChangeMember_Centered,
    MSG_Menus_Abilities_Centered,
    MSG_Menus_Strategies_Centered,
    MSG_Menus_StarSpirits_Centered,
    MSG_Menus_DoNothing_Centered,
    MSG_Menus_ActLater_Centered,
    MSG_Menus_Focus_Centered,
};

BSS s32 BattleMenu_ChooseDelay;
BSS s32 BattleMenu_TargetPointerAlpha;
BSS s32 BattleMenu_TargetNameOffsetX; // used to animate the position of the target name box
BSS s32 BattleMenu_SwapDelay; // delay before the player and partner can swap after the main menu is opened
BSS s32 BattleMenu_TargetHudElems[MAX_ENEMY_ACTORS];
BSS PopupMenu BattlePopupMenu;
BSS s8 BattleMenuState;
BSS s8 BattleMenu_ReelAppearTimer;
BSS s8 BattleMenu_CurPos;
BSS s8 BattleMenu_PrevPos;
BSS b8 BattleMenu_WheelMoving;
BSS s16 BattleMenu_ReelAlpha;
BSS s16 BattleMenuAlpha;
BSS s16 BattleMenu_ReelHidePercent;
BSS HudElemID HID_HighlightSpot;
BSS HudElemID HID_ProjectorReelA;
BSS HudElemID HID_ProjectorReelB;
BSS HudElemID HID_ProjectorBeam;
BSS HudElemID HID_SwapZ;
BSS HudElemID HID_SwapArrowLeft;
BSS HudElemID HID_SwapArrowRight;
BSS HudElemID HID_SwapBackground;
BSS s32 BattleMenu_BasePosX;
BSS s32 BattleMenu_BasePosY;
BSS s8 BattleMenu_ErrorCode;
BSS s8 BattleMenu_MinIdx;
BSS s8 BattleMenu_MaxIdx;
BSS s8 BattleMenu_HomePos;
BSS s32 BattleMenu_PrevSelected;
BSS s32 BattleMenu_WheelBase;
BSS f32 BattleMenu_WheelAngle;
BSS f32 BattleMenu_WheelSpeed;
BSS b32 BattleMenu_ShowSwapIcons;

BSS HudScript* WheelOptionHudScript[MENU_CAPACITY];
BSS HudElemID HID_OptionIcons[MENU_CAPACITY];
BSS HudElemID HID_Spotlights[MENU_CAPACITY];
BSS MsgID WheelOptionName[MENU_CAPACITY];
BSS s32 WheelOptionSubmenu[MENU_CAPACITY];
BSS s32 WheelOptionEnabled[MENU_CAPACITY];
BSS s32 WheelOptionError[MENU_CAPACITY];
BSS s32 WheelOptionCount;

void btl_main_menu_init(void) {
    BattleMenu_ReelAlpha = 255;
    BattleMenuAlpha = 255;
    BattleMenuState = BTL_MENU_STATE_CREATE;
    BattleMenu_ErrorCode = -1;
}

void btl_main_menu_hide(void) {
    BattleMenu_ReelAppearTimer = REEL_APPEAR_TIME;
    BattleMenuState = BTL_MENU_STATE_HIDE_INIT;
}

void btl_main_menu_resume_choose(void) {
    BattleMenuState = BTL_MENU_STATE_CHOOSING;
    BattleMenu_ReelAlpha = 255;
    BattleMenuAlpha = 255;
}

void btl_main_menu_restore_choose(void) {
    BattleMenuAlpha = 255;
    BattleMenuState = BTL_MENU_STATE_RESTORE;
}

void btl_main_menu_restore_submenu(void) {
    BattleMenuAlpha = 100;
    BattleMenuState = BTL_MENU_STATE_RESUME_SUBMENU;
}

void btl_main_menu_destroy(void) {
    s32 i;

    for (i = 0; i < WheelOptionCount; i++) {
        hud_element_free(HID_OptionIcons[i]);
        hud_element_free(HID_Spotlights[i]);
    }

    hud_element_free(HID_HighlightSpot);
    hud_element_free(HID_ProjectorReelA);
    hud_element_free(HID_ProjectorReelB);
    hud_element_free(HID_ProjectorBeam);
    hud_element_free(HID_SwapBackground);
    hud_element_free(HID_SwapZ);
    hud_element_free(HID_SwapArrowLeft);
    hud_element_free(HID_SwapArrowRight);
}

s32 btl_main_menu_update(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    HudElemID hid;
    s32 i;
    f32 x, y;
    s32 l, t;

    switch (BattleMenuState) {
        case BTL_MENU_STATE_CREATE:
            BattleMenu_BasePosX = 54;
            BattleMenu_BasePosY = 173;
            BattleMenu_WheelSpeed = 0.3f;
            BattleMenu_WheelMoving = false;
            BattleMenu_HomePos = BattleMenu_PrevSelected;
            BattleMenu_MinIdx = 0;
            BattleMenu_MaxIdx = WheelOptionCount - 1;
            BattleMenu_MinIdx -= BattleMenu_PrevSelected;
            BattleMenu_MaxIdx -= BattleMenu_PrevSelected;

            for (i = 0; i < WheelOptionCount; i++) {
                HID_OptionIcons[i] = hid = hud_element_create(WheelOptionHudScript[i]);
                hud_element_set_render_depth(hid, 5);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                hud_element_set_scale(hid, 0.75f);

                HID_Spotlights[i] = hid = hud_element_create(&HES_ProjectorSpot);
                hud_element_create_transform_B(hid);
                hud_element_set_render_depth(hid, 10);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
            }

            HID_HighlightSpot = hid = hud_element_create(&HES_ProjectorSpot);
            hud_element_create_transform_B(hid);
            hud_element_set_render_depth(hid, 7);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DISABLED);

            HID_ProjectorReelA = hid = hud_element_create(&HES_ProjectorReel);
            hud_element_create_transform_B(hid);
            hud_element_set_render_depth(hid, 0);
            hud_element_set_render_pos(hid, 40, 212);
            hud_element_set_tint(hid, 0, 91, 127);
            hud_element_set_transform_rotation_pivot(hid, 16, -16);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_alpha(hid, 240);

            HID_ProjectorReelB = hid = hud_element_create(&HES_ProjectorReel);
            hud_element_create_transform_B(hid);
            hud_element_set_render_depth(hid, 2);
            hud_element_set_render_pos(hid, 39, 212);
            hud_element_set_tint(hid, 0, 91, 127);
            hud_element_set_transform_rotation_pivot(hid, 16, -16);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_alpha(hid, 240);

            HID_ProjectorBeam = hid = hud_element_create(&HES_ProjectorBeam);
            hud_element_create_transform_B(hid);
            hud_element_set_render_depth(hid, 20);
            hud_element_set_render_pos(hid, 78, 178);
            hud_element_set_tint(hid, 255, 255, 255);
            hud_element_set_transform_rotation_pivot(hid, 0, 0);
            hud_element_set_transform_rotation(hid, 0.0f, 0.0f, -45.0f);
            hud_element_set_alpha(hid, 200);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DISABLED);

            HID_SwapBackground = hid = hud_element_create(&HES_SwapBackground);
            hud_element_set_render_depth(hid, 0);
            hud_element_set_render_pos(hid, 97, 208);
            hud_element_set_tint(hid, 255, 255, 255);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_alpha(hid, 230);

            HID_SwapZ = hid = hud_element_create(&HES_SwapZ);
            hud_element_set_render_depth(hid, 5);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);
            hud_element_set_render_pos(hid, 94, 209);

            HID_SwapArrowLeft = hid = hud_element_create(&HES_SwapArrowLeft);
            hud_element_set_render_depth(hid, 5);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);
            hud_element_set_render_pos(hid, 81, 210);

            HID_SwapArrowRight = hid = hud_element_create(&HES_SwapArrowRight);
            hud_element_set_render_depth(hid, 5);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);
            hud_element_set_render_pos(hid, 102, 210);
            BattleMenu_ReelHidePercent = 100;
            BattleMenu_ReelAppearTimer = REEL_APPEAR_TIME;
            BattleMenuState = BTL_MENU_STATE_SHOW_REEL;
            BattleMenu_WheelAngle = BattleMenu_WheelBase * WHEEL_SPACING;
            break;
        case BTL_MENU_STATE_SHOW_REEL:
            BattleMenu_ReelHidePercent = (100 * BattleMenu_ReelAppearTimer) / REEL_APPEAR_TIME;

            switch (BattleMenu_ReelAppearTimer) {
                default:
                    BattleMenu_ReelAppearTimer--;
                    break;
                case 1:
                    // show the projector beam
                    hid = HID_ProjectorBeam;
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    // last tick
                    BattleMenu_ReelAppearTimer--;
                    break;
                case 0:
                    BattleMenu_CurPos = 0;
                    BattleMenu_PrevPos = 0;
                    BattleMenu_WheelAngle = BattleMenu_WheelBase * WHEEL_SPACING;
                    for (i = 0; i < WheelOptionCount; i++) {
                        x = 0.0f;
                        y = 0.0f;
                        add_vec2D_polar(&x, &y, WHEEL_RADIUS, BattleMenu_WheelBase * WHEEL_SPACING);

                        l = BattleMenu_BasePosX + x;
                        t = BTL_MENU_Y(BattleMenu_BasePosY) + y;
                        hid = HID_OptionIcons[i];
                        hud_element_set_render_pos(hid, l, t);
                        hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);

                        hid = HID_Spotlights[i];
                        hud_element_set_render_pos(hid, l, t);
                        hud_element_set_alpha(hid, 100);
                        hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    }

                    x = 0.0f;
                    y = 0.0f;
                    add_vec2D_polar(&x, &y, WHEEL_RADIUS, BattleMenu_WheelBase * WHEEL_SPACING);

                    l = BattleMenu_BasePosX + x;
                    t = BTL_MENU_Y(BattleMenu_BasePosY) + y;
                    hid = HID_HighlightSpot;
                    hud_element_set_render_pos(hid, l, t);
                    hud_element_set_alpha(hid, 180);
                    hud_element_set_scale(hid, 0.85f);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    BattleMenuState = BTL_MENU_STATE_CHOOSING;
                    break;
            }
            break;
        case BTL_MENU_STATE_CHOOSING:
            if (battleStatus->curButtonsPressed & BUTTON_A) {
                if (WheelOptionEnabled[BattleMenu_CurPos + BattleMenu_HomePos] == true) {
                    sfx_play_sound(SOUND_MENU_NEXT);
                    BattleMenuState = BTL_MENU_STATE_SUBMENU_OPEN;
                } else {
                    sfx_play_sound(SOUND_MENU_ERROR);
                    BattleMenu_ErrorCode = WheelOptionError[BattleMenu_CurPos + BattleMenu_HomePos];
                    BattleMenuState = BTL_MENU_STATE_ERROR_SHOW;
                }
            } else {
                BattleMenu_PrevPos = BattleMenu_CurPos;
                if (!BattleMenu_WheelMoving) {
                    if ((battleStatus->curButtonsHeld & (BUTTON_STICK_LEFT | BUTTON_STICK_UP)) &&
                        BattleMenu_MinIdx < BattleMenu_CurPos)
                    {
                        BattleMenu_CurPos--;
                    }
                    if ((battleStatus->curButtonsHeld & (BUTTON_STICK_RIGHT | BUTTON_STICK_DOWN)) &&
                        BattleMenu_CurPos < BattleMenu_MaxIdx)
                    {
                        BattleMenu_CurPos++;
                    }
                }

                if (BattleMenu_PrevPos != BattleMenu_CurPos) {
                    BattleMenu_WheelMoving = true;
                    sfx_play_sound(SOUND_MENU_CHANGE_TAB);
                }
            }
            break;
        case BTL_MENU_STATE_SUBMENU_OPEN:
            BattleMenuAlpha = 100;
            return BattleMenu_CurPos + BattleMenu_HomePos + 1;
        case BTL_MENU_STATE_HIDE_INIT:
            BattleMenu_ReelAppearTimer = 0;
            BattleMenu_ReelAlpha = 0;
            BattleMenuState = BTL_MENU_STATE_HIDE_HOLD;
            return BattleMenu_CurPos + BattleMenu_HomePos + 1;
        case BTL_MENU_STATE_HIDE_HOLD:
            return BattleMenu_CurPos + BattleMenu_HomePos + 1;
        case BTL_MENU_STATE_RESTORE:
            BattleMenu_ReelAppearTimer = REEL_APPEAR_TIME;
            BattleMenu_ReelAlpha = 255;
            BattleMenuState = BTL_MENU_STATE_CHOOSING;
            return BattleMenu_CurPos + BattleMenu_HomePos + 1;
        case BTL_MENU_STATE_RESUME_SUBMENU:
            BattleMenu_ReelAppearTimer = REEL_APPEAR_TIME;
            BattleMenu_ReelAlpha = 255;
            BattleMenuState = BTL_MENU_STATE_SUBMENU_OPEN;
            break;
        case BTL_MENU_STATE_ERROR_SHOW:
            btl_show_battle_message(BattleMenu_ErrorCode, 90);
            BattleMenuState = BTL_MENU_STATE_ERROR_DONE;
            break;
        case BTL_MENU_STATE_ERROR_DONE:
            if (btl_is_popup_displayed()) {
                break;
            }
            BattleMenu_ErrorCode = -1;
            BattleMenuState = BTL_MENU_STATE_CHOOSING;
            break;
    }
    return 0;
}

void btl_main_menu_draw(void) {
    s32 hid;
    s32 opacity;
    f32 theta;
    b32 wheelDoneMoving;
    f32 x, y;
    f32 scale;
    s32 i;

    switch (BattleMenuState) {
        case BTL_MENU_STATE_SHOW_REEL:
            hud_element_draw_complex_hud_first(-1);
            hid = HID_ProjectorReelB;
            hud_element_set_transform_rotation(hid, 0.0f, 0.0f, 0.0f);
            hud_element_set_alpha(hid, (BattleMenu_ReelAlpha * 254) / 255);
            hud_element_set_render_pos(hid, 40 - BattleMenu_ReelHidePercent + 3900,
                                       BTL_MENU_Y(BattleMenu_ReelHidePercent + 212));
            hud_element_draw_complex_hud_next(hid);
            hid = HID_ProjectorReelA;
            hud_element_set_alpha(hid, (BattleMenu_ReelAlpha * 254) / 255);
            {
                CALL_EVENT(BattleMenuDrawReel, hid, 40 - BattleMenu_ReelHidePercent,
                           BTL_MENU_Y(BattleMenu_ReelHidePercent + 212));
            }
            hud_element_set_render_pos(hid, 40 - BattleMenu_ReelHidePercent,
                                       BTL_MENU_Y(BattleMenu_ReelHidePercent + 212));
            hud_element_draw_complex_hud_next(hid);
            break;
        case BTL_MENU_STATE_SUBMENU_OPEN:
        case BTL_MENU_STATE_CHOOSING:
        case BTL_MENU_STATE_HIDE_INIT:
        case BTL_MENU_STATE_RESTORE:
        case BTL_MENU_STATE_RESUME_SUBMENU:
            opacity = (BattleMenu_ReelAlpha * BattleMenuAlpha) / 255;
            hud_element_draw_complex_hud_first(-1);
            theta = (BattleMenu_WheelBase - BattleMenu_CurPos) * WHEEL_SPACING;

            wheelDoneMoving = false;
            if (BattleMenu_WheelAngle > theta) {
                BattleMenu_WheelAngle -= BattleMenu_WheelSpeed;
                if (BattleMenu_WheelAngle < theta) {
                    BattleMenu_WheelAngle = theta;
                    wheelDoneMoving = true;
                }
            } else if (BattleMenu_WheelAngle < theta) {
                BattleMenu_WheelAngle += BattleMenu_WheelSpeed;
                if (BattleMenu_WheelAngle > theta) {
                    BattleMenu_WheelAngle = theta;
                    wheelDoneMoving = true;
                }
            } else { // BattleMenu_WheelAngle == theta
                wheelDoneMoving = true;
            }

            if (wheelDoneMoving) {
                BattleMenu_WheelMoving = false;
                BattleMenu_WheelSpeed = 0.3f;
            } else {
                BattleMenu_WheelSpeed *= SQ(BattleMenu_WheelSpeed + 1.0f);
            }

            // draw the spotlights
            for (i = 0; i < WheelOptionCount; i++) {
                // draw the series of base spotlights under each option
                theta = BattleMenu_WheelAngle + i * WHEEL_SPACING;
                x = 0.0f;
                y = 0.0f;
                add_vec2D_polar(&x, &y, WHEEL_RADIUS, theta);
                x += BattleMenu_BasePosX;
                y += BTL_MENU_Y(BattleMenu_BasePosY);

                hid = HID_Spotlights[i];
                hud_element_set_transform_pos(hid, x, -y, 0.0f);
                hud_element_set_render_pos(hid, 0, 0);
                hud_element_set_alpha(hid, (opacity * 150) / 255);

                if (wheelDoneMoving && theta == (2 * WHEEL_SPACING)) {
                    hud_element_set_scale(hid, 1.6f);
                } else {
                    hud_element_set_scale(hid, 1.0f);
                }
                hud_element_draw_complex_hud_next(hid);

                // draw the current selection highlight (if aligned)
                if (i == BattleMenu_HomePos + BattleMenu_CurPos) {
                    x = 0.0f;
                    y = 0.0f;
                    add_vec2D_polar(&x, &y, WHEEL_RADIUS, 2 * WHEEL_SPACING);
                    x += BattleMenu_BasePosX;
                    y += BTL_MENU_Y(BattleMenu_BasePosY);

                    hid = HID_HighlightSpot;
                    hud_element_set_transform_pos(hid, x, -y, 0.0f);
                    hud_element_set_render_pos(hid, 0, 0);
                    hud_element_set_alpha(hid, (opacity * 180) / 255);
                    hud_element_set_scale(hid, 1.2f);

                    if (!wheelDoneMoving) {
                        hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    } else {
                        hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    }
                    hud_element_draw_complex_hud_next(hid);
                }
            }
            theta = (BattleMenu_WheelBase - BattleMenu_CurPos) * WHEEL_SPACING;

            // calculate beam narrowing
            scale = (fabsf(fabsf((BattleMenu_WheelAngle - theta) * (45.0 / WHEEL_SPACING)) - 22.5) / 22.5) + 0.01;
            if (wheelDoneMoving) {
                scale = 1.0f;
            }

            hid = HID_ProjectorBeam;
            hud_element_set_transform_rotation_pivot(hid, 0, 0);
            hud_element_set_transform_rotation(hid, 0.0f, 0.0f, -43.0f);
            hud_element_set_scale(hid, scale);
            hud_element_set_transform_scale(hid, 1.0f, 1.8f, 1.0f);
            hud_element_set_alpha(hid, (opacity * 200) / 255);
            hud_element_set_render_pos(hid, 79, BTL_MENU_Y(176));
            hud_element_draw_complex_hud_next(hid);

            hid = HID_ProjectorReelB;
            theta = (BattleMenu_WheelBase - BattleMenu_CurPos) * WHEEL_SPACING;
            scale = (BattleMenu_WheelAngle - theta) * (45.0 / WHEEL_SPACING);
            hud_element_set_transform_rotation(hid, 0.0f, 0.0f, -scale);
            hud_element_set_transform_rotation_pivot(hid, 18, -20);
            hud_element_set_scale(hid, 0.95f);
            hud_element_set_alpha(hid, (opacity * 254) / 255);
            hud_element_set_render_pos(hid, 40 - BattleMenu_ReelHidePercent,
                                       BTL_MENU_Y(BattleMenu_ReelHidePercent + 212));
            hud_element_draw_complex_hud_next(hid);

            hid = HID_ProjectorReelA;
            hud_element_set_alpha(hid, (opacity * 254) / 255);
            {
                CALL_EVENT(BattleMenuDrawReel, hid, 40 - BattleMenu_ReelHidePercent,
                           BTL_MENU_Y(BattleMenu_ReelHidePercent + 212));
            }
            hud_element_set_render_pos(hid, 40 - BattleMenu_ReelHidePercent,
                                       BTL_MENU_Y(BattleMenu_ReelHidePercent + 212));
            hud_element_set_scale(hid, 1.0f);
            hud_element_draw_complex_hud_next(hid);

            // draw the icons for each option
            for (i = 0; i < WheelOptionCount; i++) {
                theta = BattleMenu_WheelAngle + i * WHEEL_SPACING;
                x = 0.0f;
                y = 0.0f;
                add_vec2D_polar(&x, &y, WHEEL_RADIUS, theta);
                x += BattleMenu_BasePosX;
                y += BTL_MENU_Y(BattleMenu_BasePosY);

                btl_draw_prim_quad(0, 0, 0, 0, x - 12, y - 12, 24, 24);
                hid = HID_OptionIcons[i];
                hud_element_set_render_pos(hid, x, y);
                hud_element_set_alpha(hid, (opacity * 180) / 255);
                if (i == BattleMenu_HomePos + BattleMenu_CurPos) {
                    hud_element_set_alpha(hid, opacity);
                }
                hud_element_draw_clipped(hid);
            }

            // draw the names for each option
            if (wheelDoneMoving) {
                x = BattleMenu_BasePosX + 20;
                y = BTL_MENU_Y(BattleMenu_BasePosY) - 34;
                btl_draw_prim_quad(0, 0, 0, 0, x + 26, y, 48, 16);
                draw_msg(WheelOptionName[BattleMenu_CurPos + BattleMenu_HomePos], x, y, opacity, MSG_PAL_35, 0);
            }

            if ((gBattleStatus.flags1 & BS_FLAGS1_TUTORIAL_BATTLE) || (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE)) {
                BattleMenu_ShowSwapIcons = false;
            }

            if (BattleMenu_ShowSwapIcons) {
                hid = HID_SwapBackground;
                hud_element_set_render_pos(hid, 97, BTL_MENU_Y(208));
                hud_element_set_alpha(hid, (opacity * 200) / 255);
                hud_element_draw_clipped(hid);
                hid = HID_SwapZ;
                hud_element_set_render_pos(hid, 94, BTL_MENU_Y(209));
                hud_element_set_alpha(hid, opacity);
                hud_element_draw_clipped(hid);
                hid = HID_SwapArrowLeft;
                hud_element_set_render_pos(hid, 81, BTL_MENU_Y(210));
                hud_element_set_alpha(hid, opacity);
                hud_element_draw_clipped(hid);
                hid = HID_SwapArrowRight;
                hud_element_set_render_pos(hid, 102, BTL_MENU_Y(210));
                hud_element_set_alpha(hid, opacity);
                hud_element_draw_clipped(hid);
            }
            break;
    }
}

b32 btl_player_can_act(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;

    if (battleStatus->flags2 & BS_FLAGS2_PLAYER_TURN_USED) {
        return false;
    } else {
        s8 debuff = player->debuff;
        s32 playerCantMove = false;

        if (player->koStatus == STATUS_KEY_KO) {
            playerCantMove = true;
        }
        if (debuff == STATUS_KEY_POISON) {
            playerCantMove = false;
        }
        if (debuff == STATUS_KEY_SHRINK) {
            playerCantMove = false;
        }
        if (debuff == STATUS_KEY_SLEEP) {
            playerCantMove = true;
        }
        if (debuff == STATUS_KEY_UNUSED) {
            playerCantMove = true;
        }
        if (debuff == STATUS_KEY_DIZZY) {
            playerCantMove = true;
        }
        if (debuff == STATUS_KEY_PARALYZE) {
            playerCantMove = true;
        }
        if (debuff == STATUS_KEY_FROZEN) {
            playerCantMove = true;
        }
        if (debuff == STATUS_KEY_STOP) {
            playerCantMove = true;
        }
        if (player->stoneStatus == STATUS_KEY_STONE) {
            playerCantMove = true;
        }
        if (battleStatus->outtaSightActive) {
            playerCantMove = true;
        }
        return !playerCantMove;
    }
}

b32 btl_partner_can_act(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* partner = battleStatus->partnerActor;
    s8 partnerDebuff;
    s32 partnerCantMove;

    if (battleStatus->flags2 & BS_FLAGS2_PARTNER_TURN_USED || partner == PARTNER_NONE || partner->flags & ACTOR_FLAG_NO_ATTACK) {
        return false;
    }

    partnerDebuff = partner->debuff;
    partnerCantMove = false;

    if (partner->koStatus == STATUS_KEY_KO) {
        partnerCantMove = true;
    }
    if (partnerDebuff == STATUS_KEY_POISON) {
        partnerCantMove = false;
    }
    if (partnerDebuff == STATUS_KEY_SHRINK) {
        partnerCantMove = false;
    }
    if (partnerDebuff == STATUS_KEY_SLEEP) {
        partnerCantMove = true;
    }
    if (partnerDebuff == STATUS_KEY_UNUSED) {
        partnerCantMove = true;
    }
    if (partnerDebuff == STATUS_KEY_PARALYZE) {
        partnerCantMove = true;
    }
    if (partnerDebuff == STATUS_KEY_FROZEN) {
        partnerCantMove = true;
    }
    if (partnerDebuff == STATUS_KEY_STOP) {
        partnerCantMove = true;
    }
    if (partner->stoneStatus == STATUS_KEY_STONE) {
        partnerCantMove = true;
    }
    return !partnerCantMove;
}
