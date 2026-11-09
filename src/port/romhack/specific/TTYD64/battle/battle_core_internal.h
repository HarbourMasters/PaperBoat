#pragma once

#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/romhack/specific/TTYD64/TTYD64.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_flags.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TTYD64_BC_NUM_ACTOR_SLOTS           26
#define TTYD64_BC_BATTLE_WAIT_TIMER_EXPIRED 20

extern u8 TTYD64_EnemiesTurnEnded[4];
extern s32 TTYD64_Data_ActorsWithHPFPBuffs;

s32 dispatch_damage_event_partner_0(s32 damageAmount, s32 event, s32 stopMotion);

extern s32 BattleStatusUpdateDelay;
extern b32 BattleSkipActorTurn;

TTYD64CounterUI* TTYD64_bc_ActorCounters(s32 actorID);
u8 TTYD64_bc_GetRecField(TTYD64BattleRec* rec, s32 offset);
void TTYD64_bc_SetRecField(TTYD64BattleRec* rec, s32 offset, s32 value);
void TTYD64_bc_ClearPlayerStatusData(void);
void TTYD64_bc_AdvancePartnersExtraData(void);

void TTYD64_bc_RemoveBuffs_Partner(void);
void TTYD64_bc_AdvanceBuffData_Actor(s32 actorID);
void TTYD64_bc_AdvanceBuffData_Enemies(void);
void TTYD64_bc_HPFBBuffs_Heal_Init(void);
void TTYD64_bc_NewStatuses_Step(void);

void TTYD64_bc_AdvanceEnemiesStatus(void);
void TTYD64_bc_AdvancePartnersStatus(void);
void TTYD64_bc_UnhideAllEnemiesDebuffIcons(void);

void TTYD64_InstallBattleCoreActorData(void);
void TTYD64_InstallBattleCoreNewStatuses(void);
void TTYD64_InstallBattleCoreStatusEffects(void);
void TTYD64_InstallBattleCorePositions(void);
void TTYD64_InstallBattleCoreSuperguard(void);
void TTYD64_InstallBattleCoreStylish(void);

#ifdef __cplusplus
}
#endif
