#pragma once

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TTYD64_BS_DUP_SLOTS           64
#define TTYD64_BS_INIT_SORT_END       ((0x80270280 - 0x8010F498) / 2)
#define TTYD64_BS_BADGE_LIST_SORT_END ((0x80270280 - 0x80270180) / 2)

#define TTYD64_BS_OWNER                 "TTYD64"
#define TTYD64_SHOP_MSG_TOO_MANY_BADGES 0x17

extern u32 TTYD64_bs_DupTable[TTYD64_BS_DUP_SLOTS];
extern u32 TTYD64_bs_DupTableCopy[TTYD64_BS_DUP_SLOTS];

extern u8 TTYD64_DoesActorTriedToHitTarget_Player[16];
extern u8 TTYD64_DoesActorTriedToHitTarget_Partner[16];
extern s32 TTYD64_bs_HID_FPDrain;

extern HudScript TTYD64_IconScript_FPDrain;
extern HudScript TTYD64_IconScript_Focus;
extern HudScript TTYD64_IconScript_ChargeCommand;
extern HudScript TTYD64_IconScript_ChargeCommandBW;
extern HudScript TTYD64_IconScript_Defense;
extern HudScript TTYD64_IconScript_RunAway;
extern HudScript TTYD64_IconScript_RunAwayBW;

extern const u8 TTYD64_Charge_FPAmount[];
extern const u8 TTYD64_String_Defense_Desc[];
extern const u8 TTYD64_String_Charge_Desc[];
extern const u8 TTYD64_String_TooManyBadges[];

extern s32 TTYD64_bs_MsgChargeDesc;
extern s32 TTYD64_bs_MsgDefenseDesc;

extern EvtScript TTYD64_PartnerHappy;
extern EvtScript TTYD64_PlayerHappy;
extern EvtScript TTYD64_Script_DispatchActorHandleEvent;
extern EvtScript TTYD64_Script_ReturnPostage_HurtEnemy;
extern EvtScript TTYD64_Script_Dispatch_BattleState19;
extern EvtScript TTYD64_Script_Dispatch_DefendORCharge;
extern EvtScript TTYD64_Script_Defend;
extern EvtScript TTYD64_PlayerScriptDispatcher;
extern EvtScript TTYD64_RunAwayStart;
extern EvtScript TTYD64_RunAwayStart_Animationless;
extern EvtScript TTYD64_EVS_PlayerHappy_Patch;
extern EvtScript TTYD64_EVS_StartDefend_Patch;
extern EvtScript TTYD64_EVS_Mario_HandlePhase_Patch;
extern EvtScript TTYD64_EVS_RunAwayStart_Patch;

s32 TTYD64_bs_GetSameBadgeAmount(u32 badgeID);
s32 TTYD64_bs_GetBadgeInventoryPosition(u32 badgeID);
s32 TTYD64_bs_GetBadgeListFirstPos(const s16* badgeList, u32 badgeID);
void TTYD64_bs_DupClear(void);
void TTYD64_bs_DupBackupClear(void);
void TTYD64_bs_DupInit(void);
void TTYD64_bs_DupReorder(void);
void TTYD64_bs_DupBackup(void);
s32 TTYD64_bs_IsEquippedDup(u32 badgeID, u32 copyID);
s32 TTYD64_bs_IsEquippedDupByIndex(u32 badgeID, u32 copyIndex);
void TTYD64_bs_DupEquip(u32 badgeID, u32 copyID);
void TTYD64_bs_DupEquipByIndex(u32 badgeID, u32 copyIndex);
void TTYD64_bs_DupUnequip(u32 badgeID, u32 copyID);
void TTYD64_bs_DupUnequipByIndex(u32 badgeID, u32 copyIndex);
void TTYD64_bs_SortCopies(s16* list, s32 endIndex, s32 readable);
s32 TTYD64_bs_CanThisBadgeBeEquipped(u32 badgeID);
s32 TTYD64_bs_IsBadgeInSubMenu(u32 badgeID, s32 count);
API_CALLABLE(TTYD64_bs_IsBadgeActivated_Stack_API);
API_CALLABLE(TTYD64_bs_SplitHappyFP);
void TTYD64_bs_PauseInitHook(void);
void TTYD64_bs_PauseLoadHook(void);
void TTYD64_bs_PauseTabSwitchHook(s16* badgeList, s32 badgeListCount, s32 tab);
s32 TTYD64_bs_DrawItemDecision(u32 badgeID, s32 pagePlusOne, u32 rowOffset, s32 tab, const s16* badgeList);
s32 TTYD64_bs_DrawItemDecisionPos(u32 badgeID, u32 position, s32 tab, const s16* badgeList);
s32 TTYD64_bs_TryEquipDecision(s32 badgeID, s32 selectedItem, s32 tab, const s16* badgeList);
s32 TTYD64_bs_RemoveBadge(s32 badgeID);

void TTYD64_dispatch_event_actor_dontKillScripts(Actor* actor, s32 event);

s32 TTYD64_bs_PartnerTestLuck(void);
s32 TTYD64_bs_PartnerDefenseBadges(s32 damage);
s32 TTYD64_bs_PartnerAttackDamage(s32 base);
s32 TTYD64_bs_PlayerChargeBoost(s32 turboChargeTurnsLeft);
s32 TTYD64_bs_PowerBadgesBonus(u32 selectedMoveID);
s32 TTYD64_bs_FPDrainRecovery(void);
s32 TTYD64_bs_PartnerTurnEnd(void);
void TTYD64_bs_HPPlusP(void);
s32 TTYD64_bs_SkinPalette(struct SpriteComponent** compList, s32 compIndex, s32 palette);
void TTYD64_bs_LuckyStart(Actor* player);
s32 TTYD64_bs_PityFlowerRolls(void);
void TTYD64_bs_ReturnPostage(Actor* attacker);
s32 TTYD64_bs_DipBadge(s32 badgeID, s32 entryCount);
s32 TTYD64_bs_DipCost(s32 costFP);
s32 TTYD64_bs_EnabledMenus(s32 enabledMenus);
void TTYD64_bs_DrawChargeCost(s32 x, s32 y);

void TTYD64_InstallBadgesBattle(void);
void TTYD64_InstallBadgesStratsMenu(void);
void TTYD64_InstallBadgesWorld(void);
void TTYD64_InstallBadgesAssets(void);

#ifdef __cplusplus
}
#endif
