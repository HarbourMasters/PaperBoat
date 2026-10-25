#pragma once

#include "common.h"
#include "port/romhack/specific/TTYD64/TTYD64.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_drop_tables.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_flags.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TTYD64_EI_ITEM_LIFE_SHROOM   0x95
#define TTYD64_EI_ITEM_TABLE_RECORDS 24

extern EvtScript* TTYD64_Stack_TakeTurnScript;
extern u8 TTYD64_PierceDefenseFlag[1];

extern EvtScript TTYD64_DoReturnPostageHit;
extern EvtScript TTYD64_Script_ReturnPostage_HurtMario;
extern EvtScript TTYD64_Script_ReturnPostage_HurtPartner;
extern EvtScript TTYD64_Script_Dispatch_ReturnPostage_Mario;
extern EvtScript TTYD64_Script_Dispatch_ReturnPostage_Partner;
extern EvtScript TTYD64_Script_ApplyDebuff_Attack;
extern EvtScript TTYD64_Script_ApplyDebuff_Defense;
extern EvtScript TTYD64_EnemyUseCharge;
extern EvtScript TTYD64_ForceNextTarget;
extern EvtScript TTYD64_DoDeath;
extern EvtScript TTYD64_EnemyUseItem;
extern EvtScript TTYD64_Script_BattleCondition_ShowWarning;
extern EvtScript TTYD64_Script_Init_BattleCondition;
extern EvtScript TTYD64_EVS_Enemy_Death_Patch;
extern EvtScript TTYD64_EVS_ForceNextTarget_Patch;

API_CALLABLE(TTYD64_LoadItemScriptEnemy);
API_CALLABLE(TTYD64_Function_DeleteData_EnemyItemDropTable_SelfActor);
API_CALLABLE(TTYD64_EI_UpdateKoStatus);

extern const s32 TTYD64_ItemHog_ItemTable[10];

s32 TTYD64_EI_EnemyHasItem(Actor* actor, s32 itemID);
s32 TTYD64_EI_HeldItem(Actor* actor);
b32 TTYD64_EI_HasHeldItemData(Actor* actor);
void TTYD64_EI_SetHeldItem(Actor* actor, s32 itemID, s32 entityIndex);
s32 TTYD64_EI_GetItemEntityIndex(Actor* actor);
s32 TTYD64_get_item_flags(s32 itemID, s32 typeOfFlags);
TTYD64EnemyItemRecord* TTYD64_EI_GetActorMostFrontRecord(void);
s32 TTYD64_EI_FormationRecordCount(void);
void TTYD64_EI_SpawnEnemyItem(Actor* actor);
void TTYD64_EI_DespawnEnemyItem(Actor* actor);
void TTYD64_EI_RollHeldItem(Actor* actor);
void TTYD64_EI_ApplyDifficultyHP(Actor* actor);
void TTYD64_EI_ApplyCreateBadges(Actor* actor);
s32 TTYD64_EI_DifficultyScale(s32 value);
s32 TTYD64_EI_PiercePlayerTeamDefense(Actor* attacker);
void TTYD64_EI_SpawnDrops(struct Enemy* enemy, s32* itemToDrop);

void TTYD64_EI_InstallListeners(void);
void TTYD64_EI_InstallGlitzPit(void);

#ifdef __cplusplus
}
#endif
