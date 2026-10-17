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
#include "port/romhack/specific/TTYD64/newmaps_tyd_pit/tp.h"

API_CALLABLE(iwa_01_GetEncounterEnemyIsOwner);
API_CALLABLE(iwa_01_ProjectileAI_Main);
API_CALLABLE(iwa_01_ProjectileAI_Reflect);

extern NpcData TTYD64_imp_MontyMole_Offensive_Npc_DarkMontyMole[];
extern EvtScript TTYD64_imp_MontyMole_Offensive_Script_80244184_iwa_01;
extern EvtScript TTYD64_imp_MontyMole_Offensive_Script_80243F20_iwa_01;
extern EvtScript TTYD64_imp_MontyMole_Offensive_Script_NpcAI_80244020_iwa_01;
extern EvtScript TTYD64_imp_MontyMole_Offensive_Script_NpcAI_80244104_iwa_01;
extern MobileAISettings TTYD64_imp_MontyMole_Offensive_AISettings_802440D4_iwa_01;
extern MobileAISettings TTYD64_imp_MontyMole_Offensive_AISettings_80243FF0_iwa_01;
extern NpcSettings TTYD64_imp_MontyMole_Offensive_NpcSettings_80244358_iwa_01;
extern NpcSettings TTYD64_imp_MontyMole_Offensive_NpcSettings_802440A8_iwa_01;
extern EvtScript TTYD64_imp_MontyMole_Offensive_Script_NpcAI_80244174_iwa_01;

// clang-format off
NpcData TTYD64_imp_MontyMole_Offensive_Npc_DarkMontyMole[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_MontyMole_Offensive_NpcSettings_802440A8_iwa_01,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000800,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 16, .itemDrops = { { 164, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 10, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 10, .detectPos.z = 93, .detectSize.x = 180, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x002F0201, .walk = 0x002F0202, .run = 0x002F0203, .chase = 0x002F0203, .anim_4 = 0x002F0201, .anim_5 = 0x002F0201, .death = 0x002F0205, .hit = 0x002F0205, .anim_8 = 0x002F0200, .anim_9 = 0x002F0200, .anim_A = 0x002F0200, .anim_B = 0x002F0200, .anim_C = 0x002F0200, .anim_D = 0x002F0200, .anim_E = 0x002F0200, .anim_F = 0x002F0200 },
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
        .settings = &TTYD64_imp_MontyMole_Offensive_NpcSettings_80244358_iwa_01,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x002F020F, .walk = 0x002F020F, .run = 0x002F020F, .chase = 0x002F020F, .anim_4 = 0x002F020F, .anim_5 = 0x002F020F, .death = 0x002F020F, .hit = 0x002F020F, .anim_8 = 0x002F020F, .anim_9 = 0x002F020F, .anim_A = 0x002F020F, .anim_B = 0x002F020F, .anim_C = 0x002F020F, .anim_D = 0x002F020F, .anim_E = 0x002F020F, .anim_F = 0x002F020F },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_MontyMole_Offensive_Script_80244184_iwa_01 = {
    Call(iwa_01_GetEncounterEnemyIsOwner)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(BindNpcAI, -1, (Bytecode) TTYD64_imp_MontyMole_Offensive_Script_NpcAI_80244174_iwa_01)
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
    Call(BindNpcAI, -1, (Bytecode) TTYD64_imp_MontyMole_Offensive_Script_NpcAI_80244104_iwa_01)
    Return
    End
};

EvtScript TTYD64_imp_MontyMole_Offensive_Script_80243F20_iwa_01 = {
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

EvtScript TTYD64_imp_MontyMole_Offensive_Script_NpcAI_80244020_iwa_01 = {
    Call(SetNpcFlagBits, -1, 0x200002, 1)
    Call(EnableNpcShadow, -1, 0)
    Label(0)
    Call(RandInt, 15, LVar0)
    Add(LVar0, 15)
    Wait(LVar0)
    Call(TTYD64_tp_iwa_01_MontyMoleAI_Main, Ref(TTYD64_imp_MontyMole_Offensive_AISettings_80243FF0_iwa_01))
    Return
    End
};

EvtScript TTYD64_imp_MontyMole_Offensive_Script_NpcAI_80244104_iwa_01 = {
    Call(SetSelfVar, 0, 0)
    Call(SetSelfVar, 1, 0)
    Call(SetSelfVar, 2, 17)
    Call(SetSelfVar, 3, 17)
    Call(iwa_01_ProjectileAI_Main, Ref(TTYD64_imp_MontyMole_Offensive_AISettings_802440D4_iwa_01))
    Return
    End
};

MobileAISettings TTYD64_imp_MontyMole_Offensive_AISettings_802440D4_iwa_01 = {
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

MobileAISettings TTYD64_imp_MontyMole_Offensive_AISettings_80243FF0_iwa_01 = {
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

NpcSettings TTYD64_imp_MontyMole_Offensive_NpcSettings_80244358_iwa_01 = {
    .defaultAnim = 0x00000000,
    .height = 12,
    .radius = 12,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_MontyMole_Offensive_Script_NpcAI_80244104_iwa_01,
    .onHit = TTYD64_imp_MontyMole_Offensive_Script_80244184_iwa_01,
    .aux = NULL,
    .onDefeat = TTYD64_imp_MontyMole_Offensive_Script_80243F20_iwa_01,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 0,
    .actionFlags = 8,
};

NpcSettings TTYD64_imp_MontyMole_Offensive_NpcSettings_802440A8_iwa_01 = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_MontyMole_Offensive_Script_NpcAI_80244020_iwa_01,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 8,
    .actionFlags = 8,
};

EvtScript TTYD64_imp_MontyMole_Offensive_Script_NpcAI_80244174_iwa_01 = {
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_MontyMole_Offensive(void) {
}
