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

API_CALLABLE(mim_02_HoppingAI_Main);

extern NpcData TTYD64_imp_ForestFuzzy_Npc_ForestFuzzy[];
extern EvtScript TTYD64_imp_ForestFuzzy_Script_NpcAI_8024163C_mim_02;
extern MobileAISettings TTYD64_imp_ForestFuzzy_AISettings_8024160C_mim_02;
extern NpcSettings TTYD64_imp_ForestFuzzy_NpcSettings_80241678_mim_02;

// clang-format off
NpcData TTYD64_imp_ForestFuzzy_Npc_ForestFuzzy[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_ForestFuzzy_NpcSettings_80241678_mim_02,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000000,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 132, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 50, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x002B0102, .walk = 0x002B0102, .run = 0x002B0103, .chase = 0x002B0103, .anim_4 = 0x002B0101, .anim_5 = 0x002B0101, .death = 0x002B0108, .hit = 0x002B0108, .anim_8 = 0x002B0103, .anim_9 = 0x002B0103, .anim_A = 0x002B0103, .anim_B = 0x002B0103, .anim_C = 0x002B0103, .anim_D = 0x002B0103, .anim_E = 0x002B0103, .anim_F = 0x002B0103 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_ForestFuzzy_Script_NpcAI_8024163C_mim_02 = {
    Call(SetNpcFlagBits, -1, 64, 1)
    Call(mim_02_HoppingAI_Main, Ref(TTYD64_imp_ForestFuzzy_AISettings_8024160C_mim_02), 1)
    Return
    End
};

MobileAISettings TTYD64_imp_ForestFuzzy_AISettings_8024160C_mim_02 = {
    .moveSpeed = 1.0f,
    .moveTime = 30,
    .waitTime = 10,
    .alertRadius = 120.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 5,
    .chaseSpeed = 4.5f,
    .chaseTurnRate = 90,
    .chaseUpdateInterval = 5,
    .chaseRadius = 160.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_ForestFuzzy_NpcSettings_80241678_mim_02 = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_ForestFuzzy_Script_NpcAI_8024163C_mim_02,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 11,
    .actionFlags = 0,
};
// clang-format on

void TTYD64_tp_Install_imp_ForestFuzzy(void) {
}
