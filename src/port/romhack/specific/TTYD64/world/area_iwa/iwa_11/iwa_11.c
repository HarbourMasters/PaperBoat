#include "common.h"
#include "effects.h"
#include "entity.h"
#include "foliage.h"
#include "map.h"
#include "npc.h"
#include "script_api/map.h"
#include <string.h>
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/world/maps.h"

extern EvtScript iwa_11_EVS_InitializeTrainScene;
extern EvtScript iwa_11_EVS_Main;
extern EvtScript iwa_11_EVS_MonitorSceneSkip;
extern EvtScript iwa_11_EVS_TravelToMtRugged;
extern EvtScript iwa_11_EVS_TravelToToadTown;
extern EvtScript iwa_11_EVS_UpdateSceneryPos;
extern NpcData iwa_11_NpcData_TrainToad;
extern MapSettings iwa_11_settings;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(BindNpcAI);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableModel);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(GetBattleOutcome);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetOwnerEncounterTrigger);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(OnPlayerFled);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveNpc);
API_CALLABLE(SetBattleAsScripted);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamPosA);
API_CALLABLE(SetCamPosB);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetEnemyFlagBits);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetSelfVar);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetZoneEnabled);
API_CALLABLE(UseExitHeading);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(iwa_01_GetEncounterEnemyIsOwner);
API_CALLABLE(iwa_01_MontyMoleAI_Main);
API_CALLABLE(iwa_01_ProjectileAI_Main);
API_CALLABLE(iwa_01_ProjectileAI_Reflect);

extern MobileAISettings TTYD64_iwa_11_AISettings_802440D4_iwa_01;
extern EvtScript TTYD64_iwa_11_Script_80244184_iwa_01;
extern EvtScript TTYD64_iwa_11_Script_NpcAI_80244174_iwa_01;
extern NpcData TTYD64_iwa_11_NpcGroup_MontyMole4[];
extern NpcData TTYD64_iwa_11_NpcGroup_MontyMole3[];
extern NpcData TTYD64_iwa_11_NpcGroup_MontyMole2[];
extern NpcData TTYD64_iwa_11_NpcGroup_MontyMole1[];
extern EvtScript TTYD64_iwa_11_Script_Main;
extern EvtScript TTYD64_iwa_11_Script_InitNewStuff;
extern EvtScript TTYD64_iwa_11_Script_80243F20_iwa_01;
extern EvtScript TTYD64_iwa_11_Script_NpcAI_80244020_iwa_01;
extern EvtScript TTYD64_iwa_11_Script_NpcAI_80244104_iwa_01;
extern u8 TTYD64_iwa_11_String_Tattle[];
extern EvtScript TTYD64_iwa_11_Script_Exit2;
extern NpcGroupList TTYD64_iwa_11_NpcGroupList_iwa11;
extern EvtScript TTYD64_iwa_11_Script_Entity_Shine1;
extern EntryList TTYD64_iwa_11_EntryList;
extern MobileAISettings TTYD64_iwa_11_AISettings_80243FF0_iwa_01;
extern NpcSettings TTYD64_iwa_11_NpcSettings_802440A8_iwa_01;
extern EvtScript TTYD64_iwa_11_Script_BindExits;
extern NpcSettings TTYD64_iwa_11_NpcSettings_80244358_iwa_01;

// clang-format off
MobileAISettings TTYD64_iwa_11_AISettings_802440D4_iwa_01 = {
    .moveSpeed = 8.30000019f,
    .moveTime = 0,
    .waitTime = 0,
    .alertRadius = 2.5f,
    .alertOffsetDist = 0.400000006f,
    .playerSearchInterval = -1,
    .chaseSpeed = 0.0f,
    .chaseTurnRate = 0,
    .chaseUpdateInterval = 0,
    .chaseRadius = 0.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 0,
};

EvtScript TTYD64_iwa_11_Script_80244184_iwa_01 = {
    Call(iwa_01_GetEncounterEnemyIsOwner)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(BindNpcAI, -1, Ref(TTYD64_iwa_11_Script_NpcAI_80244174_iwa_01))
    Call(SetNpcFlagBits, -1, 256, 1)
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
    CaseOrEq(4)
    CaseOrEq(3)
        Call(SetSelfVar, 0, 3)
        Call(iwa_01_ProjectileAI_Reflect)
        IfEq(LVar0, 0)
            Return
        EndIf
        EndCaseGroup
    CaseEq(2)
        Call(SetSelfVar, 0, 4)
        Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 7, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(SetNpcPos, -1, 0, -1000, 0)
        Call(SetSelfVar, 0, 0)
        EndCaseGroup
    CaseDefault
        Call(SetBattleAsScripted)
        EndCaseGroup
    EndSwitch
    Call(BindNpcAI, -1, Ref(TTYD64_iwa_11_Script_NpcAI_80244104_iwa_01))
    Return
    End
};

EvtScript TTYD64_iwa_11_Script_NpcAI_80244174_iwa_01 = {
    Return
    End
};

NpcData TTYD64_iwa_11_NpcGroup_MontyMole4[] = {
    {
        .id = 8,
        .settings = &TTYD64_iwa_11_NpcSettings_802440A8_iwa_01,
        .pos = { 2540.0f, 0.0f, 190.0f },
        .flags = 0x00000800,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 2540, .centerPos.y = 0, .centerPos.z = 190, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 2540, .detectPos.y = 0, .detectPos.z = 190, .detectSize.x = 180, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x002F0001, .walk = 0x002F0002, .run = 0x002F0003, .chase = 0x002F0003, .anim_4 = 0x002F0000, .anim_5 = 0x002F0000, .death = 0x002F0005, .hit = 0x002F0005, .anim_8 = 0x002F0000, .anim_9 = 0x002F0000, .anim_A = 0x002F0000, .anim_B = 0x002F0000, .anim_C = 0x002F0000, .anim_D = 0x002F0000, .anim_E = 0x002F0000, .anim_F = 0x002F0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 9,
        .settings = &TTYD64_iwa_11_NpcSettings_80244358_iwa_01,
        .pos = { 0.0f, 1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002F000F, .walk = 0x002F000F, .run = 0x002F000F, .chase = 0x002F000F, .anim_4 = 0x002F000F, .anim_5 = 0x002F000F, .death = 0x002F000F, .hit = 0x002F000F, .anim_8 = 0x002F000F, .anim_9 = 0x002F000F, .anim_A = 0x002F000F, .anim_B = 0x002F000F, .anim_C = 0x002F000F, .anim_D = 0x002F000F, .anim_E = 0x002F000F, .anim_F = 0x002F000F },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_iwa_11_NpcGroup_MontyMole3[] = {
    {
        .id = 6,
        .settings = &TTYD64_iwa_11_NpcSettings_802440A8_iwa_01,
        .pos = { 3114.0f, 0.0f, 170.0f },
        .flags = 0x00000800,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 3114, .centerPos.y = 0, .centerPos.z = 170, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 3114, .detectPos.y = 0, .detectPos.z = 170, .detectSize.x = 180, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x002F0001, .walk = 0x002F0002, .run = 0x002F0003, .chase = 0x002F0003, .anim_4 = 0x002F0000, .anim_5 = 0x002F0000, .death = 0x002F0005, .hit = 0x002F0005, .anim_8 = 0x002F0000, .anim_9 = 0x002F0000, .anim_A = 0x002F0000, .anim_B = 0x002F0000, .anim_C = 0x002F0000, .anim_D = 0x002F0000, .anim_E = 0x002F0000, .anim_F = 0x002F0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 7,
        .settings = &TTYD64_iwa_11_NpcSettings_80244358_iwa_01,
        .pos = { 0.0f, 1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002F000F, .walk = 0x002F000F, .run = 0x002F000F, .chase = 0x002F000F, .anim_4 = 0x002F000F, .anim_5 = 0x002F000F, .death = 0x002F000F, .hit = 0x002F000F, .anim_8 = 0x002F000F, .anim_9 = 0x002F000F, .anim_A = 0x002F000F, .anim_B = 0x002F000F, .anim_C = 0x002F000F, .anim_D = 0x002F000F, .anim_E = 0x002F000F, .anim_F = 0x002F000F },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_iwa_11_NpcGroup_MontyMole2[] = {
    {
        .id = 4,
        .settings = &TTYD64_iwa_11_NpcSettings_802440A8_iwa_01,
        .pos = { 3613.0f, 0.0f, -140.0f },
        .flags = 0x00000800,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 3613, .centerPos.y = 0, .centerPos.z = -140, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 3613, .detectPos.y = 0, .detectPos.z = -140, .detectSize.x = 180, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x002F0001, .walk = 0x002F0002, .run = 0x002F0003, .chase = 0x002F0003, .anim_4 = 0x002F0000, .anim_5 = 0x002F0000, .death = 0x002F0005, .hit = 0x002F0005, .anim_8 = 0x002F0000, .anim_9 = 0x002F0000, .anim_A = 0x002F0000, .anim_B = 0x002F0000, .anim_C = 0x002F0000, .anim_D = 0x002F0000, .anim_E = 0x002F0000, .anim_F = 0x002F0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 5,
        .settings = &TTYD64_iwa_11_NpcSettings_80244358_iwa_01,
        .pos = { 0.0f, 1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002F000F, .walk = 0x002F000F, .run = 0x002F000F, .chase = 0x002F000F, .anim_4 = 0x002F000F, .anim_5 = 0x002F000F, .death = 0x002F000F, .hit = 0x002F000F, .anim_8 = 0x002F000F, .anim_9 = 0x002F000F, .anim_A = 0x002F000F, .anim_B = 0x002F000F, .anim_C = 0x002F000F, .anim_D = 0x002F000F, .anim_E = 0x002F000F, .anim_F = 0x002F000F },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_iwa_11_NpcGroup_MontyMole1[] = {
    {
        .id = 2,
        .settings = &TTYD64_iwa_11_NpcSettings_802440A8_iwa_01,
        .pos = { 4019.0f, 0.0f, 233.0f },
        .flags = 0x00000800,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 4019, .centerPos.y = 0, .centerPos.z = 233, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 4019, .detectPos.y = 0, .detectPos.z = 233, .detectSize.x = 180, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x002F0001, .walk = 0x002F0002, .run = 0x002F0003, .chase = 0x002F0003, .anim_4 = 0x002F0000, .anim_5 = 0x002F0000, .death = 0x002F0005, .hit = 0x002F0005, .anim_8 = 0x002F0000, .anim_9 = 0x002F0000, .anim_A = 0x002F0000, .anim_B = 0x002F0000, .anim_C = 0x002F0000, .anim_D = 0x002F0000, .anim_E = 0x002F0000, .anim_F = 0x002F0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 3,
        .settings = &TTYD64_iwa_11_NpcSettings_80244358_iwa_01,
        .pos = { 0.0f, 1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002F000F, .walk = 0x002F000F, .run = 0x002F000F, .chase = 0x002F000F, .anim_4 = 0x002F000F, .anim_5 = 0x002F000F, .death = 0x002F000F, .hit = 0x002F000F, .anim_8 = 0x002F000F, .anim_9 = 0x002F000F, .anim_A = 0x002F000F, .anim_B = 0x002F000F, .anim_C = 0x002F000F, .anim_D = 0x002F000F, .anim_E = 0x002F000F, .anim_F = 0x002F000F },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_iwa_11_Script_Main = {
    Set(GameByte(425), 8)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 30, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(GetEntryID, LVar0)
    IfNe(LVar0, 2)
        Call(UseSettingsFrom, 0, 0, 0, 0)
        Call(SetCamPosA, 0, -5800, 0)
        Call(SetCamPosB, 0, 5700, 0)
        Call(SetCamSpeed, 0, Float(90.0))
        Call(SetPanTarget, 0, 0, 0, 0)
        Call(PanToTarget, 0, 0, 1)
    EndIf
    Call(MakeNpcs, 1, Ref(TTYD64_iwa_11_NpcGroupList_iwa11))
    Call(ModifyColliderFlags, 0, 13, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 11, 0x7FFFFE00)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        ExecWait(iwa_11_EVS_InitializeTrainScene)
        Exec(iwa_11_EVS_TravelToMtRugged)
        Exec(iwa_11_EVS_UpdateSceneryPos)
        Exec(iwa_11_EVS_MonitorSceneSkip)
    CaseEq(1)
        ExecWait(iwa_11_EVS_InitializeTrainScene)
        Exec(iwa_11_EVS_TravelToToadTown)
        Exec(iwa_11_EVS_UpdateSceneryPos)
        Exec(iwa_11_EVS_MonitorSceneSkip)
    CaseEq(2)
        Set(LVar0, Ref(TTYD64_iwa_11_Script_BindExits))
        Exec(EnterWalk)
    EndSwitch
    Exec(TTYD64_iwa_11_Script_InitNewStuff)
    Return
    End
};

EvtScript TTYD64_iwa_11_Script_InitNewStuff = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 2)
        Call(SetZoneEnabled, 2, 0)
        Call(SetZoneEnabled, 1, 0)
        Call(EnableModel, 86, 0)
        Call(EnableModel, 87, 0)
        Call(EnableModel, 88, 0)
        Call(SetNpcPos, 0, 0, -1000, 0)
        Call(SetMusic, 0, 22, 0, 8)
    Else
        Call(SetMusic, 0, 128, 0, 8)
        Call(SetZoneEnabled, 4, 0)
        Call(SetZoneEnabled, 5, 0)
        Call(EnableGroup, 143, 0)
    EndIf
    Call(MakeEntity, Ref(Entity_YellowBlock), 3905, 62, 238, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(4820))
    Call(MakeEntity, Ref(Entity_YellowBlock), 3242, 62, -140, 0, 140, 0x80000000)
    Call(AssignBlockFlag, GameFlag(4821))
    Call(MakeEntity, Ref(Entity_YellowBlock), 2650, 62, 215, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(4822))
    Call(MakeItemEntity, 348, 3849, 0, -112, 17, GameFlag(4823))
    Call(MakeEntity, Ref(Entity_SuperBlock), 2254, 61, 245, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(4824))
    Call(AssignScript, Ref(TTYD64_iwa_11_Script_Entity_Shine1))
    Return
    End
};

EvtScript TTYD64_iwa_11_Script_80243F20_iwa_01 = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Call(SetSelfVar, 0, 5)
        Call(RemoveNpc, -1)
    CaseEq(2)
        Call(SetNpcPos, -1, 0, -1000, 0)
        Call(OnPlayerFled, 1)
    CaseEq(3)
        Call(SetEnemyFlagBits, -1, 16, 1)
        Call(RemoveNpc, -1)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_iwa_11_Script_NpcAI_80244020_iwa_01 = {
    Call(SetNpcFlagBits, -1, 0x200002, 1)
    Call(EnableNpcShadow, -1, 0)
    Label(0)
    Call(RandInt, 15, LVar0)
    Add(LVar0, 15)
    Wait(LVar0)
    Call(iwa_01_MontyMoleAI_Main, Ref(TTYD64_iwa_11_AISettings_80243FF0_iwa_01))
    Return
    End
};

EvtScript TTYD64_iwa_11_Script_NpcAI_80244104_iwa_01 = {
    Call(SetSelfVar, 0, 0)
    Call(SetSelfVar, 1, 0)
    Call(SetSelfVar, 2, 17)
    Call(SetSelfVar, 3, 17)
    Call(iwa_01_ProjectileAI_Main, Ref(TTYD64_iwa_11_AISettings_802440D4_iwa_01))
    Return
    End
};

u8 TTYD64_iwa_11_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C, 0xF7, 0x53,
    0x45, 0x45, 0x4D, 0x53, 0xF7, 0x4C, 0x49, 0x4B, 0x45, 0xF7, 0x54, 0x48,
    0x49, 0x53, 0xF0, 0x41, 0x52, 0x45, 0x41, 0xF7, 0x49, 0x53, 0xF7, 0x50,
    0x4C, 0x41, 0x47, 0x45, 0x44, 0xF7, 0x57, 0x49, 0x54, 0x48, 0xF7, 0x4D,
    0x4F, 0x4C, 0x45, 0x53, 0x0E, 0xF0, 0xF1, 0xFB, 0x32, 0x45, 0x4D, 0x45,
    0x4D, 0x42, 0x45, 0x52, 0xF7, 0x54, 0x4F, 0xF7, 0x42, 0x45, 0xF7, 0x43,
    0x41, 0x55, 0x54, 0x49, 0x4F, 0x55, 0x53, 0x0E, 0xF1, 0xFD
};

EvtScript TTYD64_iwa_11_Script_Exit2 = {
    Call(UseExitHeading, 60, 2)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "iwa_10", 2)
    Wait(100)
    Return
    End
};

NpcGroupList TTYD64_iwa_11_NpcGroupList_iwa11 = {
    { .npcCount = 1, .npcs = &iwa_11_NpcData_TrainToad, .battle = 0x0000, .stage = 0 },
    { .npcCount = 2, .npcs = TTYD64_iwa_11_NpcGroup_MontyMole1, .battle = 0x0906, .stage = 2 },
    { .npcCount = 2, .npcs = TTYD64_iwa_11_NpcGroup_MontyMole2, .battle = 0x0906, .stage = 2 },
    { .npcCount = 2, .npcs = TTYD64_iwa_11_NpcGroup_MontyMole3, .battle = 0x0906, .stage = 2 },
    { .npcCount = 2, .npcs = TTYD64_iwa_11_NpcGroup_MontyMole4, .battle = 0x0906, .stage = 2 },
    {},
};

EvtScript TTYD64_iwa_11_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(4824))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EntryList TTYD64_iwa_11_EntryList = {
    { 0.0f, 0.0f, 15.0f, 90.0f },
    { 0.0f, 0.0f, 15.0f, 270.0f },
    { 4193.0f, 0.0f, 0.0f, -90.0f },
};

MobileAISettings TTYD64_iwa_11_AISettings_80243FF0_iwa_01 = {
    .moveSpeed = 1.70000005f,
    .moveTime = 90,
    .waitTime = 0,
    .alertRadius = 110.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 2,
    .chaseSpeed = 7.5f,
    .chaseTurnRate = 0,
    .chaseUpdateInterval = 0,
    .chaseRadius = 110.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_iwa_11_NpcSettings_802440A8_iwa_01 = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = &TTYD64_iwa_11_Script_NpcAI_80244020_iwa_01,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 8,
    .actionFlags = 8,
};

EvtScript TTYD64_iwa_11_Script_BindExits = {
    BindTrigger(TTYD64_iwa_11_Script_Exit2, 128, 40, 1, 0)
    Return
    End
};

NpcSettings TTYD64_iwa_11_NpcSettings_80244358_iwa_01 = {
    .defaultAnim = 0x00000000,
    .height = 12,
    .radius = 12,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = &TTYD64_iwa_11_Script_NpcAI_80244104_iwa_01,
    .onHit = &TTYD64_iwa_11_Script_80244184_iwa_01,
    .aux = NULL,
    .onDefeat = &TTYD64_iwa_11_Script_80243F20_iwa_01,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 0,
    .actionFlags = 8,
};
// clang-format on

void TTYD64_InstallMap_iwa_11(void) {
    iwa_11_settings.entryList = &TTYD64_iwa_11_EntryList;
    iwa_11_settings.entryCount = 3;
    iwa_11_settings.tattle.get = TTYD64_iwa_11_Function_GetTattle;
    Mod_ReplaceScript("TTYD64", &iwa_11_EVS_Main, &TTYD64_iwa_11_Script_Main);
}
