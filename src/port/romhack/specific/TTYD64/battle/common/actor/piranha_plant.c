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
#include "port/romhack/specific/TTYD64/world/tp.h"

API_CALLABLE(kzn_03_MeleeHitbox_Main);

extern NpcData TTYD64_imp_PiranhaPlant_Npc_PiranhaPlant[];
extern EvtScript TTYD64_imp_PiranhaPlant_Script_NpcAI_80243F10_kzn_03;
extern EvtScript TTYD64_imp_PiranhaPlant_Script_80243E24_kzn_03;
extern EvtScript TTYD64_imp_PiranhaPlant_Script_NpcAI_80244010_kzn_03;
extern MobileAISettings TTYD64_imp_PiranhaPlant_AISettings_80243EE0_kzn_03;
extern NpcSettings TTYD64_imp_PiranhaPlant_NpcSettings_80244070_mim_01;
extern NpcSettings TTYD64_imp_PiranhaPlant_NpcSettings_802441A8_mim_01;

// clang-format off
NpcData TTYD64_imp_PiranhaPlant_Npc_PiranhaPlant[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_PiranhaPlant_NpcSettings_80244070_mim_01,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 128, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 3, 13106 }, { 9830, 13106, 3, 13106 }, { 16383, 13106, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 250, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00370001, .walk = 0x00370001, .run = 0x00370001, .chase = 0x00370001, .anim_4 = 0x00370001, .anim_5 = 0x00370001, .death = 0x00370009, .hit = 0x00370009, .anim_8 = 0x00370004, .anim_9 = 0x00370003, .anim_A = 0x00370007, .anim_B = 0x00370007, .anim_C = 0x00370008, .anim_D = 0x00370001, .anim_E = 0x00370001, .anim_F = 0x00370001 },
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
        .settings = &TTYD64_imp_PiranhaPlant_NpcSettings_802441A8_mim_01,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800D00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00370001, .walk = 0x00370001, .run = 0x00370001, .chase = 0x00370001, .anim_4 = 0x00370001, .anim_5 = 0x00370001, .death = 0x00370009, .hit = 0x00370009, .anim_8 = 0x00370004, .anim_9 = 0x00370003, .anim_A = 0x00370007, .anim_B = 0x00370007, .anim_C = 0x00370008, .anim_D = 0x00370001, .anim_E = 0x00370001, .anim_F = 0x00370001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_PiranhaPlant_Script_NpcAI_80243F10_kzn_03 = {
    Call(SetSelfVar, 7, 1)
    Call(SetSelfVar, 8, 10)
    Call(SetSelfVar, 9, 9)
    Call(SetSelfVar, 10, 12)
    Call(SetSelfVar, 11, 7)
    Call(SetSelfVar, 12, 30)
    Call(SetSelfVar, 13, 15)
    Call(SetSelfVar, 14, 18)
    Call(SetSelfVar, 15, 15)
    Call(TTYD64_tp_kzn_03_PiranhaPlantAI_Main, Ref(TTYD64_imp_PiranhaPlant_AISettings_80243EE0_kzn_03))
    Return
    End
};

EvtScript TTYD64_imp_PiranhaPlant_Script_80243E24_kzn_03 = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
    CaseEq(0)
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

EvtScript TTYD64_imp_PiranhaPlant_Script_NpcAI_80244010_kzn_03 = {
    Call(EnableNpcShadow, -1, 0)
    Call(SetSelfVar, 0, 14)
    Call(SetSelfVar, 1, 28)
    Call(SetSelfVar, 4, 3)
    Call(SetSelfVar, 15, 8414)
    Call(kzn_03_MeleeHitbox_Main)
    Return
    End
};

MobileAISettings TTYD64_imp_PiranhaPlant_AISettings_80243EE0_kzn_03 = {
    .moveSpeed = 0.0f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 150.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 0.0f,
    .chaseTurnRate = 0,
    .chaseUpdateInterval = 0,
    .chaseRadius = 0.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 0,
};

NpcSettings TTYD64_imp_PiranhaPlant_NpcSettings_80244070_mim_01 = {
    .defaultAnim = 0x00000000,
    .height = 32,
    .radius = 26,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_PiranhaPlant_Script_NpcAI_80243F10_kzn_03,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 11,
    .actionFlags = 0,
};

NpcSettings TTYD64_imp_PiranhaPlant_NpcSettings_802441A8_mim_01 = {
    .defaultAnim = 0x00000000,
    .height = 18,
    .radius = 18,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_PiranhaPlant_Script_NpcAI_80244010_kzn_03,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = TTYD64_imp_PiranhaPlant_Script_80243E24_kzn_03,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 11,
    .actionFlags = 8,
};
// clang-format on

void TTYD64_tp_Install_imp_PiranhaPlant(void) {
}
