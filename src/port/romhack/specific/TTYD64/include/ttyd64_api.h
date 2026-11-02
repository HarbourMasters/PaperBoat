#pragma once

#include "common.h"
#include "effects.h"

#ifdef __cplusplus
extern "C" {
#endif

// world_lib
API_CALLABLE(TTYD64_Pipe_CheckDownInput);
API_CALLABLE(TTYD64_Pipe_GetCameraYaw);
API_CALLABLE(TTYD64_Pipe_GetCurrentFloor);
API_CALLABLE(TTYD64_Pipe_GetEntryCoords);
API_CALLABLE(TTYD64_Pipe_GetPointInFrontOfPlayer);
API_CALLABLE(TTYD64_Pipe_SetAnimFlag);
API_CALLABLE(TTYD64_TexturePan_Simple);
API_CALLABLE(TTYD64_TexturePan_Complex);
void TTYD64_DrawBox(s32 posX, s32 posY, s32 sizeX, s32 sizeY, s32 style, s32 opacity);
extern s32 TTYD64_hp_BoxStyleBase;

#define TTYD64_HP_PAUSE_ICON_HEART 5
#define TTYD64_HP_PAUSE_ICON_SHINE 6
s32 TTYD64_hp_PauseIcon(s32 index);
API_CALLABLE(TTYD64_Function_AddBadgeToSoldInventory);
API_CALLABLE(TTYD64_Function_ClearData_KMR31_ExtraData);
void TTYD64_Function_ClearMinigameData_Bar(void);
void TTYD64_Function_ClearMinigameData_Moles(void);
API_CALLABLE(TTYD64_Function_ConvertToInt);
API_CALLABLE(TTYD64_Function_GetOtherBadgesAmount);
API_CALLABLE(TTYD64_Function_GetPlayerBadgesAmount);
API_CALLABLE(TTYD64_Function_GetSoldBadgesAmount);
API_CALLABLE(TTYD64_Function_GetTypeOfBadge);
API_CALLABLE(TTYD64_Function_Inventory_ClearPageData);
b32 TTYD64_Function_IsThisSoldBadgeOnSale(s32 itemID);
API_CALLABLE(TTYD64_Function_ShowInventory_Others);
API_CALLABLE(TTYD64_Function_ShowInventory_PlayerBadges);
void TTYD64_Function_SortSoldBadges(void);
void TTYD64_Function_UpdateMinigames(void);
void TTYD64_Function_kmr31_DrawDescriptionBox(void);
API_CALLABLE(TTYD64_GetActorPointer);
API_CALLABLE(TTYD64_GetEnemyPointer);
API_CALLABLE(TTYD64_GetEntityPointer);
API_CALLABLE(TTYD64_GetModelPointer);
b32 TTYD64_IsBadgeEquipped(s32 badgeID);
API_CALLABLE(TTYD64_SetNpcGroupBattleID);
s32 TTYD64_add_badge_to_sold_inventory(s32 badgeID);
s32 TTYD64_get_sold_badges_amount(void);
s32 TTYD64_pause_badges_comparator(s16* a, s16* b);
void TTYD64_pause_sort_item_list(s16* itemList, s32 listLength, s32 (*comparator)(s16*, s16*));
API_CALLABLE(TTYD64_Mole_ClearData);
API_CALLABLE(TTYD64_Bar_ClearData);
API_CALLABLE(TTYD64_TestPlayerFlags);
API_CALLABLE(TTYD64_TestPlayerAnimFlags);
API_CALLABLE(TTYD64_SetPlayerAnimFlagBits);
API_CALLABLE(TTYD64_SetPlayerColliderDiameter);
API_CALLABLE(TTYD64_DisarmChestEntity);
API_CALLABLE(TTYD64_GetPartnerAbilityState);
API_CALLABLE(TTYD64_SetPartnerAbilityState);
API_CALLABLE(TTYD64_SetScreenOverlayFront);
API_CALLABLE(TTYD64_GetScreenOverlayFrontProgress);
API_CALLABLE(TTYD64_SetScreenOverlayColor);
API_CALLABLE(TTYD64_GetModelBaseTranslation);
API_CALLABLE(TTYD64_SetFadeModelAlpha);
API_CALLABLE(TTYD64_GetFountainCoins);
API_CALLABLE(TTYD64_GetMoleHighScore);
API_CALLABLE(TTYD64_SetMoleHighScore);
API_CALLABLE(TTYD64_Mole_GetState);
API_CALLABLE(TTYD64_Mole_SetState);
API_CALLABLE(TTYD64_Mole_StartTimer);
API_CALLABLE(TTYD64_Mole_GetSeconds);
API_CALLABLE(TTYD64_Mole_GetScore);
API_CALLABLE(TTYD64_Mole_SetScore);
API_CALLABLE(TTYD64_Bar_GetState);
API_CALLABLE(TTYD64_Bar_SetState);

enum TTYD64Kmr31Slot {
    TTYD64_K31_STATE,
    TTYD64_K31_ALPHA,
    TTYD64_K31_MESSAGE,
};

API_CALLABLE(TTYD64_kmr31_Get);
API_CALLABLE(TTYD64_kmr31_Set);

// battle_core
#define TTYD64_EVENT_SUPERGUARD          0x43
#define TTYD64_DAMAGE_TYPE_NO_SUPERGUARD 0x00080000

typedef struct TTYD64GuardState {
    u8 superguarded;
} TTYD64GuardState;

extern TTYD64GuardState TTYD64_Guard;
b32 TTYD64_SuperguardedHit(Actor* target);

API_CALLABLE(TTYD64_StylishArm);
API_CALLABLE(TTYD64_StylishReset);
API_CALLABLE(TTYD64_StylishDisarm);
API_CALLABLE(TTYD64_StylishIsArmed);
API_CALLABLE(TTYD64_StylishPressed);
API_CALLABLE(TTYD64_StylishConsume);
API_CALLABLE(TTYD64_StylishAddCount);
API_CALLABLE(TTYD64_StylishGetCount);
API_CALLABLE(TTYD64_StylishSetCount);

enum TTYD64BuffIndex {
    TTYD64_BUFF_DEFENSE,
    TTYD64_BUFF_ATTACK,
    TTYD64_BUFF_HP_REGEN,
    TTYD64_BUFF_FP_REGEN,
    TTYD64_BUFF_COUNT,
};

typedef struct TTYD64Buff {
    s8 amount;
    u8 turns;
} TTYD64Buff;

typedef struct TTYD64CounterUI {
    struct EffectInstance* fx;
    u8 counterType;
    u8 animationState;
    u16 animationTimer;
} TTYD64CounterUI;

typedef struct TTYD64BattleRec {
    u8 debuffKey;
    u8 debuffTurns;
    u8 staticTurns;
    u8 transparentTurns;
    TTYD64Buff buffs[TTYD64_BUFF_COUNT];
    u8 flipped;
    u8 flipCountdown;
    u8 defendStack;
    u8 charge;
    b8 giant;
    b8 tiny;
    u8 pendingBoostTurns[2];
    s16 heldItem;
    u8 heldItemEntity;
    TTYD64CounterUI counters[TTYD64_BUFF_COUNT];
} TTYD64BattleRec;

TTYD64BattleRec* TTYD64_ActorRec(s32 actorID);
TTYD64BattleRec* TTYD64_PartnerRec(s32 partnerID);
TTYD64BattleRec* TTYD64_CurPartnerRec(void);
void TTYD64_InstallActorRecords(void);
API_CALLABLE(TTYD64_AddAttackBoost);
API_CALLABLE(TTYD64_AddCharge);
API_CALLABLE(TTYD64_AddDefenseBoost);
API_CALLABLE(TTYD64_BoostAttack);
API_CALLABLE(TTYD64_BoostDefense);
void TTYD64_ClearPartnerExtraData(void);
void TTYD64_ClearPartnerStatusData(void);
API_CALLABLE(TTYD64_ClearPartnerExtraData_API);
API_CALLABLE(TTYD64_ClearPartnerStatusData_API);
API_CALLABLE(TTYD64_TestBattleFlags2);
API_CALLABLE(TTYD64_GetCurrentBattleID);
API_CALLABLE(TTYD64_GetActionMeterFill);
API_CALLABLE(TTYD64_GetLastAttackDamage);
API_CALLABLE(TTYD64_SetActorHP);
API_CALLABLE(TTYD64_UpdateKOStatus);
API_CALLABLE(TTYD64_Function_Multibonk_GetAmountToDeal);
API_CALLABLE(TTYD64_Function_ExplotionFX);
void TTYD64_Function_RemoveBuffs_ActorID(s32 actorID);
API_CALLABLE(TTYD64_GetActorExtraData);
extern b8 TTYD64_MarioInFront;
API_CALLABLE(TTYD64_GetMarioPos);
API_CALLABLE(TTYD64_SetMarioInFront);
API_CALLABLE(TTYD64_GetPartnerExtraBattleData_API);
API_CALLABLE(TTYD64_MakeActorGiant);
API_CALLABLE(TTYD64_MakeActorTiny);
API_CALLABLE(TTYD64_SetActorExtraData);
API_CALLABLE(TTYD64_SetPartnerExtraBattleData_API);
API_CALLABLE(TTYD64_SetTargetActorInFront);
API_CALLABLE(TTYD64_SetTargetActorInTheBack);
void TTYD64_UpdateNewStatuses_Visibility(s32 battleState);
b32 TTYD64_bc_PlayerTurnRestarting(void);
s32 TTYD64_RequestedBattleState(s32 battleState);

// enemy_items
typedef struct TTYD64DropEntry {
    s32 itemID;
    u16 holdWeight;
    u16 dropWeight;
} TTYD64DropEntry;

enum TTYD64EnemyItemOrigin {
    TTYD64_EI_ORIGIN_MID_BATTLE,
    TTYD64_EI_ORIGIN_FORMATION,
    TTYD64_EI_ORIGIN_FRONT_MOST,
};

typedef struct TTYD64EnemyItemRecord {
    s32 dropTable;
    s16 itemID;
    u8 origin;
    u8 stolen;
} TTYD64EnemyItemRecord;

const TTYD64DropEntry* TTYD64_GetDropTable(s32 dropTable, s32* count);
void TTYD64_EnemyItemTable_ClearAllData(void);
API_CALLABLE(TTYD64_EnemyItemTable_SetStolenByte);
void TTYD64_Function_GlitzPit_DamageChallenge(void);
void TTYD64_Function_GlitzPit_DontSwapChallenge(void);
void TTYD64_Function_GlitzPit_NoFPChallenge(s32 fpCost);
API_CALLABLE(TTYD64_GetItemFlags);
API_CALLABLE(TTYD64_GetItemGlobalData);
API_CALLABLE(TTYD64_GetMoveData);
API_CALLABLE(TTYD64_SetActorItemData);
API_CALLABLE(TTYD64_GetHeldItem);
API_CALLABLE(TTYD64_GetHeldItemEntity);
API_CALLABLE(TTYD64_HasHeldItem);
API_CALLABLE(TTYD64_ClearHeldItem);
API_CALLABLE(TTYD64_GetWrappedTakeTurn);
API_CALLABLE(TTYD64_GetGlitzChallenge);
API_CALLABLE(TTYD64_SetGlitzChallenge);
API_CALLABLE(TTYD64_SetGlitzStatus);
void TTYD64_ShowFlyingStat(Actor* actor, s32 type, s32 amount);
void TTYD64_enemy_item_table_data_update_actorMostInFront(void);
TTYD64EnemyItemRecord* TTYD64_get_actor_itemTableData(s32 actorID);
TTYD64EnemyItemRecord* TTYD64_get_actor_itemTableData_OriginalFormation(s32 actorID);
ItemData* TTYD64_get_item_global_data(s32 itemID);

// badges_strats
s32 TTYD64_BadgeCount(s32 itemID);
#define TTYD64_BS_PAUSE_WARNING_BOX_WIDTH 0xD2
f32 TTYD64_bs_PauseBadgeIconScale(void);
s32 TTYD64_bs_PauseDrawEquipped(s32 listIndex, s32 tab, const s16* list, s32 equipped);
s32 TTYD64_EnemyCalcDamage_Defense(Actor* attacker, s32 damage);
API_CALLABLE(TTYD64_Function_PartnerFocus);
API_CALLABLE(TTYD64_GetStackBoost);
API_CALLABLE(TTYD64_GetStackBoostDebuff);
s32 TTYD64_IsBadgeActivated_Stack(s32 badgeID);
s32 TTYD64_BadgeAbility(s32 itemID);
API_CALLABLE(TTYD64_SetDefendThread);
API_CALLABLE(TTYD64_SetPartnerHappyActive);
API_CALLABLE(TTYD64_GetPartnerHappyActive);

// partner_hp
typedef struct TTYD64PartnerHPRecord {
    u8 displayed;
    u8 hp;
    u8 max;
} TTYD64PartnerHPRecord;

extern TTYD64PartnerHPRecord TTYD64_PartnerHPRecords[12];
extern u8 TTYD64_ShineSprites;
extern s32 TTYD64_FortressKeys;

TTYD64PartnerHPRecord* TTYD64_PartnerHPRecord(s32 partnerID);
s32 TTYD64_PartnerHP(s32 partnerID);
s32 TTYD64_PartnerMaxHP(s32 partnerID);
void TTYD64_SetPartnerHPByID(s32 partnerID, s32 hp);
void TTYD64_SetPartnerMaxHPByID(s32 partnerID, s32 maxHP);
void TTYD64_Function_HealPartners(void);
API_CALLABLE(TTYD64_Function_InflictStatus);
API_CALLABLE(TTYD64_Function_TryToInflictStatus);
API_CALLABLE(TTYD64_GetPartnerData_API);
s32 TTYD64_GetPartnerHP(void);
API_CALLABLE(TTYD64_GetPartnerHP_API);
s32 TTYD64_GetPartnerMaxHP(void);
API_CALLABLE(TTYD64_HealActor);
API_CALLABLE(TTYD64_Heal_PlayerTeam);
API_CALLABLE(TTYD64_RaisePartnerMaxHP);
API_CALLABLE(TTYD64_RecoverFP);
void TTYD64_SetPartnerHP(s32 hp);
b32 TTYD64_heal_actor(s32 actorID, s32 amount);
void TTYD64_updatePartnerMaxHP(s32 partnerID);
API_CALLABLE(TTYD64_GetHealBoxTarget);
API_CALLABLE(TTYD64_StashTurnUsed);
API_CALLABLE(TTYD64_RestoreTurnUsed);

// battle_items_ui
API_CALLABLE(TTYD64_Function_GetActorDefense);
void TTYD64_SetIconSize2(s32 hid, f32 width, f32 height);
API_CALLABLE(TTYD64_SetTornadoJumpHud);

// hud_pause
s32 TTYD64_CreateIcon(HudScript* script);
void TTYD64_Draw_ShinesCounter(void);
s32 TTYD64_Function_GetPartnersUnlocked(void);
void TTYD64_SetIconSize(s32 hid, f32 width, f32 height);

typedef struct TTYD64ShineBox {
    s32 state;
    s32 offset;
    b32 visible;
} TTYD64ShineBox;

extern TTYD64ShineBox TTYD64_ShineBox;
API_CALLABLE(TTYD64_GetShineBoxAnim);
API_CALLABLE(TTYD64_SetShineBoxOffset);
API_CALLABLE(TTYD64_SetShineCounterVisible);

// world_systems
void TTYD64_HudDriverFrame(void);
void TTYD64_ConvertAsciiToPM64String(u8* dest, const char* ascii);
void TTYD64_Function_Mode_Random_GetEnemyItem(s32* itemID);
API_CALLABLE(TTYD64_SetPoisonDrive);
API_CALLABLE(TTYD64_SetFireBreathTint);

typedef struct TTYD64FFWDState {
    u8 enabled;
    u8 printerOpen;
    u8 suppressed;
} TTYD64FFWDState;

extern TTYD64FFWDState TTYD64_FFWD;
API_CALLABLE(TTYD64_ResetFFWD);
API_CALLABLE(TTYD64_SetFFWDSuppressed);
API_CALLABLE(TTYD64_SetUnderwaterFollowsMover);
API_CALLABLE(TTYD64_SetShopBuyPopup);
API_CALLABLE(TTYD64_SetVerticalMovementLocked);
API_CALLABLE(TTYD64_Set8BitSwitchPressed);

#ifdef __cplusplus
}
#endif
