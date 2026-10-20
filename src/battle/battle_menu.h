#ifndef _BATTLE_MENU_H_
#define _BATTLE_MENU_H_

#include "common.h"
#include "hud_element.h"

#define MENU_CHANGE_DELAY 8
#define MENU_DIPPING_DELAY 5

void btl_main_menu_init(void);

// hides the main menu (wheel) (e.g., while choosing a target for an action)
void btl_main_menu_hide(void);

// restore main menu (wheel) to a choosing state immediately (e.g., after a submenu is closed)
void btl_main_menu_resume_choose(void);

// restore main menu (wheel) to a choosing state after a one-frame transitional state
void btl_main_menu_restore_choose(void);

// restore main menu (wheel) to a visible, but locked state (e.g., canceling target selection to reopen a submenu)
// use this when the menu should be visibile, but in the background of another menu
void btl_main_menu_restore_submenu(void);

void btl_main_menu_destroy(void);

s32 btl_main_menu_update(void);
void btl_main_menu_draw(void);

s32 btl_submenu_strats_update(void);

b32 btl_player_can_act(void);
b32 btl_partner_can_act(void);

void create_battle_popup_menu(PopupMenu* popup);

void flush_popup_menu(void);
void show_popup_menu(void);

void btl_submenu_moves_init(void);
void btl_submenu_moves_hide(void);
void btl_submenu_moves_destroy(void);
void btl_submenu_strats_destroy(void);
void btl_submenu_strats_resume_choose(void);
void btl_submenu_strats_restore_choose(void);
void btl_submenu_strats_restore_locked(void);

void btl_submenu_moves_restore_choose(void);
void btl_menu_strats_init(void);

void btl_submenu_moves_resume_choose(void);
void btl_submenu_moves_restore_locked(void);

void btl_submenu_strats_hide(void);

void btl_check_can_change_partner(void);
void btl_init_menu_items(void);
s32 btl_submenu_moves_update(void);

extern PopupMenu BattlePopupMenu;

extern s32 StratsOptionHIDs[];
extern s16 StratsMenuPosX;
extern s16 StratsMenuPosY;
extern HudScript* StratsOptionHudScripts[];
extern s32 StratsOptionNames[]; // msg IDs
extern s32 StratsOptionCount;
extern s32 StratsPrevSelected;

extern s32 StratsOptionMenuTypes[];
extern s32 StratsOptionEnabled[];
extern s32 StratsOptionError[];
extern s32 StratsOptionMessage[];

extern s8 BattleMenu_CurPos;
extern s8 BattleMenu_HomePos;

extern s32 PartnerNameMessages[];

extern IconHudScriptPair ItemsHudScripts;
extern IconHudScriptPair StarPowersHudScripts;
extern IconHudScriptPair StrategiesHudScripts;
extern IconHudScriptPair DoNothingHudScripts;
extern IconHudScriptPair FleeHudScripts;

extern s32 LeftJustMenuMessages[];
extern s32 CenteredBattleMessages[];

extern IconHudScriptPair PartnerHudScripts[];
extern HudScript* battle_menu_DisabledPartnerHudScripts[];

extern IconHudScriptPair StarPowerMovesHudScripts[];

extern HudScript HES_HandPointDownLoop;
extern HudScript HES_HandPointLeftLoop;
extern s32 BattleMenu_TargetHudElems[];

extern s32 BattleMenu_ChooseDelay;
extern s32 BattleMenu_TargetPointerAlpha;
extern s32 BattleMenu_TargetNameOffsetX;
extern s32 BattleMenu_SwapDelay;

extern HudScript* MovesOptionHudScripts[24];
extern s32 MovesOptionNames[24];
extern s32 MovesOptionDisplayCosts[24];
extern s32 MovesOptionDiscounts[24];
extern s32 MovesOptionDiscountColors[24];
extern s32 MovesOptionBPCosts[24];
extern s32 UsingSpiritsSubmenu;
extern s32 MovesOptionCount;
extern s32 MovesPrevSelected;
extern s32 MovesOptionIndices[24];
extern s32 MovesOptionEnabled[24];
extern s32 MovesOptionDesc[24];
extern s8 MovesOptionSortPriority[24];
extern s8 MovesOptionError[24];
extern s32 SelectedMovesIndex;

extern s32 WheelOptionSubmenu[];
extern s32 WheelOptionEnabled[];
extern s32 WheelOptionError[];
extern HudScript* WheelOptionHudScript[];
extern s32 WheelOptionName[];

extern b32 BattleMenu_ShowSwapIcons;
extern s32 WheelOptionCount;

extern s32 BattleMenu_PrevSelected;
extern s32 BattleMenu_WheelBase;
extern s8 ShowingErrorMessage;

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

extern HudScript HES_GreenArrowDown;
extern HudScript HES_GreenArrowUp;
extern HudScript HES_HandPointer;
extern HudScript HES_HandPointDownLoop;
extern HudScript HES_HandPointLeftLoop;

extern HudScript HES_FPCost;
extern HudScript HES_FPCostReduced;
extern HudScript HES_FPCostReducedTwice;
extern HudScript HES_POWCost;
extern HudScript HES_POWCostReduced;
extern HudScript HES_POWCostReducedTwice;
extern HudScript HES_StatusFlower;
extern HudScript HES_NotEnoughFP;
extern HudScript HES_NotEnoughPOW;
extern HudScript HES_ProjectorBeam;
extern HudScript HES_ProjectorReel;
extern HudScript HES_ProjectorSpot;
extern HudScript HES_SwapArrowLeft;
extern HudScript HES_SwapArrowRight;
extern HudScript HES_SwapBackground;
extern HudScript HES_SwapZ;

extern IconHudScriptPair* gItemHudScripts;

extern s32 MenuIndexFromPartnerID[];

#endif
