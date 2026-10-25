#include "common.h"
#include "effects.h"
#include "entity.h"
#include "map.h"
#include "npc.h"
#include "script_api/map.h"
#include <stdio.h>
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/world/tyd_pit.h"

API_CALLABLE(omo_02_GetEncounterEnemyIsOwner);
API_CALLABLE(omo_02_ProjectileAI_Main);
API_CALLABLE(omo_02_ProjectileAI_Reflect);
API_CALLABLE(omo_02_RangedAttackAI_Main);
API_CALLABLE(omo_02_SetSpyGuyInstigatorValue);

extern NpcData TTYD64_imp_SpyGuy_Npc_SpyGuy[];
extern EvtScript TTYD64_imp_SpyGuy_Script_80244B70_omo_02;
extern EvtScript TTYD64_imp_SpyGuy_Script_80244918_omo_02;
extern EvtScript TTYD64_imp_SpyGuy_Script_NpcAI_80244A18_omo_02;
extern EvtScript TTYD64_imp_SpyGuy_Script_NpcAI_80244AF0_omo_02;
extern MobileAISettings TTYD64_imp_SpyGuy_AISettings_802449E8_omo_02;
extern MobileAISettings TTYD64_imp_SpyGuy_AISettings_80244AC0_omo_02;
extern NpcSettings TTYD64_imp_SpyGuy_NpcSettings_80244D38_omo_02;
extern NpcSettings TTYD64_imp_SpyGuy_NpcSettings_80244A94_omo_02;
extern EvtScript TTYD64_imp_SpyGuy_Script_NpcAI_80244B60_omo_02;

// clang-format off
NpcData TTYD64_imp_SpyGuy_Npc_SpyGuy[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_SpyGuy_NpcSettings_80244A94_omo_02,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 128, 2, 0 }, { 130, 2, 0 }, { 132, 2, 0 }, { 134, 2, 0 }, { 133, 2, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x003F0002, .walk = 0x003F0004, .run = 0x003F0005, .chase = 0x003F0004, .anim_4 = 0x003F0002, .anim_5 = 0x003F0002, .death = 0x003F000B, .hit = 0x003F000B, .anim_8 = 0x003F0015, .anim_9 = 0x003F0016, .anim_A = 0x003F0002, .anim_B = 0x003F0002, .anim_C = 0x003F0002, .anim_D = 0x003F0002, .anim_E = 0x003F0002, .anim_F = 0x003F0002 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 1,
        .settings = &TTYD64_imp_SpyGuy_NpcSettings_80244D38_omo_02,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800D00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x003F0010, .walk = 0x003F0010, .run = 0x003F0010, .chase = 0x003F0010, .anim_4 = 0x003F0010, .anim_5 = 0x003F0010, .death = 0x003F0010, .hit = 0x003F0010, .anim_8 = 0x003F0010, .anim_9 = 0x003F0010, .anim_A = 0x003F0010, .anim_B = 0x003F0010, .anim_C = 0x003F0010, .anim_D = 0x003F0010, .anim_E = 0x003F0010, .anim_F = 0x003F0010 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 2,
        .settings = &TTYD64_imp_SpyGuy_NpcSettings_80244D38_omo_02,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800D00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x003F0010, .walk = 0x003F0010, .run = 0x003F0010, .chase = 0x003F0010, .anim_4 = 0x003F0010, .anim_5 = 0x003F0010, .death = 0x003F0010, .hit = 0x003F0010, .anim_8 = 0x003F0010, .anim_9 = 0x003F0010, .anim_A = 0x003F0010, .anim_B = 0x003F0010, .anim_C = 0x003F0010, .anim_D = 0x003F0010, .anim_E = 0x003F0010, .anim_F = 0x003F0010 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_SpyGuy_Script_80244B70_omo_02 = {
    Call(omo_02_GetEncounterEnemyIsOwner)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(BindNpcAI, -1, (Bytecode) TTYD64_imp_SpyGuy_Script_NpcAI_80244B60_omo_02)
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
    CaseOrEq(4)
    CaseOrEq(3)
        Call(SetSelfVar, 0, 3)
        Call(omo_02_ProjectileAI_Reflect)
        IfEq(LVar0, 0)
            Return
        EndIf
        EndCaseGroup
    CaseOrEq(2)
    CaseOrEq(6)
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
    Call(BindNpcAI, -1, (Bytecode) TTYD64_imp_SpyGuy_Script_NpcAI_80244AF0_omo_02)
    Return
    End
};

EvtScript TTYD64_imp_SpyGuy_Script_80244918_omo_02 = {
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

EvtScript TTYD64_imp_SpyGuy_Script_NpcAI_80244A18_omo_02 = {
    Call(omo_02_SetSpyGuyInstigatorValue)
    Call(SetSelfVar, 0, 0)
    Call(SetSelfVar, 1, 12)
    Call(SetSelfVar, 2, 5)
    Call(SetSelfVar, 3, 2)
    Call(omo_02_RangedAttackAI_Main, Ref(TTYD64_imp_SpyGuy_AISettings_802449E8_omo_02))
    Return
    End
};

EvtScript TTYD64_imp_SpyGuy_Script_NpcAI_80244AF0_omo_02 = {
    Call(SetSelfVar, 0, 0)
    Call(SetSelfVar, 1, 0)
    Call(SetSelfVar, 2, 12)
    Call(SetSelfVar, 3, 13)
    Call(omo_02_ProjectileAI_Main, Ref(TTYD64_imp_SpyGuy_AISettings_80244AC0_omo_02))
    Return
    End
};

MobileAISettings TTYD64_imp_SpyGuy_AISettings_802449E8_omo_02 = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 15,
    .alertRadius = 90.0f,
    .alertOffsetDist = 50.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 3.79999995f,
    .chaseTurnRate = 8,
    .chaseUpdateInterval = 1,
    .chaseRadius = 140.0f,
    .chaseOffsetDist = 60.0f,
    .unk_AI_2C = 1,
};

MobileAISettings TTYD64_imp_SpyGuy_AISettings_80244AC0_omo_02 = {
    .moveSpeed = 8.0f,
    .moveTime = 0,
    .waitTime = 0,
    .alertRadius = 4.0f,
    .alertOffsetDist = 0.5f,
    .playerSearchInterval = -1,
    .chaseSpeed = 0.0f,
    .chaseTurnRate = 0,
    .chaseUpdateInterval = 0,
    .chaseRadius = 0.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 0,
};

NpcSettings TTYD64_imp_SpyGuy_NpcSettings_80244D38_omo_02 = {
    .defaultAnim = 0x00000000,
    .height = 7,
    .radius = 7,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_SpyGuy_Script_NpcAI_80244AF0_omo_02,
    .onHit = TTYD64_imp_SpyGuy_Script_80244B70_omo_02,
    .aux = NULL,
    .onDefeat = TTYD64_imp_SpyGuy_Script_80244918_omo_02,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 0,
    .actionFlags = 8,
};

NpcSettings TTYD64_imp_SpyGuy_NpcSettings_80244A94_omo_02 = {
    .defaultAnim = 0x00000000,
    .height = 24,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_SpyGuy_Script_NpcAI_80244A18_omo_02,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 15,
    .actionFlags = 0,
};

EvtScript TTYD64_imp_SpyGuy_Script_NpcAI_80244B60_omo_02 = {
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_SpyGuy(void) {
}
