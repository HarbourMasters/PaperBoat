#pragma once

#include "common.h"
#include "effects.h"

#ifdef __cplusplus
extern "C" {
#endif

// world_lib
extern EvtScript TTYD64_DoNpcDefeat;
extern EvtScript TTYD64_IsBadgeEquipped_Script;
extern EvtScript TTYD64_MovePartnerBehindMario;
extern EvtScript TTYD64_Script_AdvancedUpdateModelAlpha;
extern EvtScript TTYD64_Script_FadeScreenIn;
extern EvtScript TTYD64_Script_FadeScreenOut;
extern EvtScript TTYD64_Script_Init_NPC_NGPlus;
extern EvtScript TTYD64_Script_Init_NPC_Settings;
extern EvtScript TTYD64_Script_UpdateModelAlpha;
extern EvtScript TTYD64_Script_UpgradePartners_Main;
extern EvtScript TTYD64_SetPartnerAnimation;
extern EvtScript TTYD64_SetPlayerAnimation;
extern u8 TTYD64_Data_RocksPositionTable[];
extern u8 TTYD64_Data_RocksPositionTable_Original[];
extern u8 TTYD64_Data_ShopInventory[];

// battle_core
extern EvtScript TTYD64_DoSuperguard;
extern EvtScript TTYD64_Script_BellyFlop_GoBackToHome_Succeed;
extern EvtScript TTYD64_Script_Bomb_DoStylish;
extern EvtScript TTYD64_Script_DoStylishFX;
extern EvtScript TTYD64_Script_DoStylish_DizzyShell;
extern EvtScript TTYD64_Script_DoStylish_Multibonk;
extern EvtScript TTYD64_Script_Goombario_HandleEvent_Immune;
extern EvtScript TTYD64_Script_Goombario_Init_Ponder;
extern EvtScript TTYD64_Script_InitTracker;
extern EvtScript TTYD64_Script_NukeTracker;
extern EvtScript TTYD64_Script_ShellToss_GoBackToHome_Succeed;
extern EvtScript TTYD64_Script_Slam_DoStylish;
extern EvtScript TTYD64_Script_TimingTutor;
extern EvtScript TTYD64_Script_TryToShrinkTarget;
extern EvtScript TTYD64_Script_Tattle_DoStylish;
extern EvtScript TTYD64_Script_Kooper_FirstStrike_GetMoveData;
extern EvtScript TTYD64_Script_Goombario_Multibonk_GetAmountToDeal;
extern EvtScript TTYD64_Script_TydalWave_GoBackToHome;

// badges_strats
extern EvtScript TTYD64_Script_ChargeCommand;
extern const u8 TTYD64_String_TooMuchBadges[];
extern s32 TTYD64_MsgID_TooMuchBadges;
extern u8 TTYD64_FPDrainByte[];

// partner_hp
extern EvtScript TTYD64_BattleScript_DrinkItem;
extern EvtScript TTYD64_BattleScript_EatItem;
extern EvtScript TTYD64_BattleScript_GoBackToHome_HealingItem;
extern EvtScript TTYD64_BattleScript_GoBackToHome_Item;
extern EvtScript TTYD64_PartnerDies;
extern EvtScript TTYD64_SetPartnerAnimation_Battle;
extern EvtScript TTYD64_UseLifeShroom_Actor;
extern HudScript TTYD64_IconScript_HealBoxHeart;

// battle_items_ui
extern EvtScript TTYD64_NewItemsScripts_GetNewScript;
extern HudScript TTYD64_IconScript_Bombette;
extern HudScript TTYD64_IconScript_Bow;
extern HudScript TTYD64_IconScript_Goombario;
extern HudScript TTYD64_IconScript_Kooper;
extern HudScript TTYD64_IconScript_Lakilester;
extern HudScript TTYD64_IconScript_Parakarry;
extern HudScript TTYD64_IconScript_Sushie;
extern HudScript TTYD64_IconScript_Watt;
extern u8 TTYD64_PopupMenu_Byte[];

// hud_pause
extern EvtScript TTYD64_Script_ShineBlock;
extern HudScript TTYD64_IconScript_Mario;

// world_systems
extern char TTYD64_ASCII_Buffer[];
extern u8 TTYD64_Data_Shop_ExtraData[];

// maps_patched
extern EvtScript TTYD64_nok_01_Script_DoBombExplotion;
extern s32 TTYD64_nok_01_Data_BombMinigame_Level1_Order[];
extern s32 TTYD64_nok_01_Data_BombMinigame_Level2_Order[];
extern s32 TTYD64_nok_01_Data_BombMinigame_Level3_Order[];

// newmaps_tyd_pit
extern EvtScript TTYD64_tes_00_Script_Entity_Shine1;

#ifdef __cplusplus
}
#endif
