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

API_CALLABLE(kpa_09_GetEncounterEnemyIsOwner);
API_CALLABLE(kpa_09_ProjectileAI_Main);
API_CALLABLE(kpa_09_ProjectileAI_Reflect);
API_CALLABLE(kpa_09_RangedAttackAI_Main);

extern NpcData TTYD64_imp_DryBones_Npc_DryBones[];
extern EvtScript TTYD64_imp_DryBones_Script_80241DDC_kpa_09;
extern EvtScript TTYD64_imp_DryBones_Script_80241B90_kpa_09;
extern EvtScript TTYD64_imp_DryBones_Script_NpcAI_80241C90_kpa_09;
extern EvtScript TTYD64_imp_DryBones_Script_NpcAI_80241D5C_kpa_09;
extern MobileAISettings TTYD64_imp_DryBones_AISettings_80241D2C_kpa_09;
extern MobileAISettings TTYD64_imp_DryBones_AISettings_80241C60_kpa_09;
extern NpcSettings TTYD64_imp_DryBones_NpcSettings_80241FA4_kpa_09;
extern NpcSettings TTYD64_imp_DryBones_NpcSettings_80241D00_kpa_09;
extern EvtScript TTYD64_imp_DryBones_Script_NpcAI_80241DCC_kpa_09;

// clang-format off
NpcData TTYD64_imp_DryBones_Npc_DryBones[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_DryBones_NpcSettings_80241D00_kpa_09,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000800,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 140, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 4, 13106 }, { 9830, 13106, 4, 13106 }, { 16383, 13106, 4, 13106 }, { 26213, 13106, 4, 13106 }, { 32767, 9830, 4, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 4, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00530002, .walk = 0x00530003, .run = 0x00530004, .chase = 0x00530004, .anim_4 = 0x00530002, .anim_5 = 0x00530002, .death = 0x00530007, .hit = 0x00530007, .anim_8 = 0x00530005, .anim_9 = 0x00530006, .anim_A = 0x00530002, .anim_B = 0x00530002, .anim_C = 0x00530002, .anim_D = 0x00530002, .anim_E = 0x00530002, .anim_F = 0x00530002 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 1,
        .settings = &TTYD64_imp_DryBones_NpcSettings_80241FA4_kpa_09,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800D00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00540000, .walk = 0x00540000, .run = 0x00540000, .chase = 0x00540000, .anim_4 = 0x00540000, .anim_5 = 0x00540000, .death = 0x00540000, .hit = 0x00540000, .anim_8 = 0x00540000, .anim_9 = 0x00540000, .anim_A = 0x00540000, .anim_B = 0x00540000, .anim_C = 0x00540000, .anim_D = 0x00540000, .anim_E = 0x00540000, .anim_F = 0x00540000 },
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
        .settings = &TTYD64_imp_DryBones_NpcSettings_80241FA4_kpa_09,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800D00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00540000, .walk = 0x00540000, .run = 0x00540000, .chase = 0x00540000, .anim_4 = 0x00540000, .anim_5 = 0x00540000, .death = 0x00540000, .hit = 0x00540000, .anim_8 = 0x00540000, .anim_9 = 0x00540000, .anim_A = 0x00540000, .anim_B = 0x00540000, .anim_C = 0x00540000, .anim_D = 0x00540000, .anim_E = 0x00540000, .anim_F = 0x00540000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 3,
        .settings = &TTYD64_imp_DryBones_NpcSettings_80241FA4_kpa_09,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800D00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00540000, .walk = 0x00540000, .run = 0x00540000, .chase = 0x00540000, .anim_4 = 0x00540000, .anim_5 = 0x00540000, .death = 0x00540000, .hit = 0x00540000, .anim_8 = 0x00540000, .anim_9 = 0x00540000, .anim_A = 0x00540000, .anim_B = 0x00540000, .anim_C = 0x00540000, .anim_D = 0x00540000, .anim_E = 0x00540000, .anim_F = 0x00540000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_DryBones_Script_80241DDC_kpa_09 = {
    Call(kpa_09_GetEncounterEnemyIsOwner)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(BindNpcAI, -1, (Bytecode) TTYD64_imp_DryBones_Script_NpcAI_80241DCC_kpa_09)
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
    CaseOrEq(4)
    CaseOrEq(3)
        Call(SetSelfVar, 0, 3)
        Call(kpa_09_ProjectileAI_Reflect)
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
    Call(BindNpcAI, -1, (Bytecode) TTYD64_imp_DryBones_Script_NpcAI_80241D5C_kpa_09)
    Return
    End
};

EvtScript TTYD64_imp_DryBones_Script_80241B90_kpa_09 = {
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

EvtScript TTYD64_imp_DryBones_Script_NpcAI_80241C90_kpa_09 = {
    Call(SetSelfVar, 0, 0)
    Call(SetSelfVar, 1, 15)
    Call(SetSelfVar, 2, 10)
    Call(SetSelfVar, 3, 2)
    Call(kpa_09_RangedAttackAI_Main, Ref(TTYD64_imp_DryBones_AISettings_80241C60_kpa_09))
    Return
    End
};

EvtScript TTYD64_imp_DryBones_Script_NpcAI_80241D5C_kpa_09 = {
    Call(SetSelfVar, 0, 0)
    Call(SetSelfVar, 1, 3)
    Call(SetSelfVar, 2, 15)
    Call(SetSelfVar, 3, 15)
    Call(kpa_09_ProjectileAI_Main, Ref(TTYD64_imp_DryBones_AISettings_80241D2C_kpa_09))
    Return
    End
};

MobileAISettings TTYD64_imp_DryBones_AISettings_80241D2C_kpa_09 = {
    .moveSpeed = 7.5f,
    .moveTime = 0,
    .waitTime = 0,
    .alertRadius = 1.10000002f,
    .alertOffsetDist = 0.180000007f,
    .playerSearchInterval = -1,
    .chaseSpeed = 0.0f,
    .chaseTurnRate = 0,
    .chaseUpdateInterval = 0,
    .chaseRadius = 0.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 0,
};

MobileAISettings TTYD64_imp_DryBones_AISettings_80241C60_kpa_09 = {
    .moveSpeed = 2.0f,
    .moveTime = 20,
    .waitTime = 3,
    .alertRadius = 120.0f,
    .alertOffsetDist = 120.0f,
    .playerSearchInterval = 2,
    .chaseSpeed = 1.0f,
    .chaseTurnRate = 0,
    .chaseUpdateInterval = 0,
    .chaseRadius = 150.0f,
    .chaseOffsetDist = 150.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_DryBones_NpcSettings_80241FA4_kpa_09 = {
    .defaultAnim = 0x00000000,
    .height = 12,
    .radius = 12,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_DryBones_Script_NpcAI_80241D5C_kpa_09,
    .onHit = TTYD64_imp_DryBones_Script_80241DDC_kpa_09,
    .aux = NULL,
    .onDefeat = TTYD64_imp_DryBones_Script_80241B90_kpa_09,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 0,
    .actionFlags = 8,
};

NpcSettings TTYD64_imp_DryBones_NpcSettings_80241D00_kpa_09 = {
    .defaultAnim = 0x00000000,
    .height = 32,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_DryBones_Script_NpcAI_80241C90_kpa_09,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 30,
    .actionFlags = 0,
};

EvtScript TTYD64_imp_DryBones_Script_NpcAI_80241DCC_kpa_09 = {
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_DryBones(void) {
}
