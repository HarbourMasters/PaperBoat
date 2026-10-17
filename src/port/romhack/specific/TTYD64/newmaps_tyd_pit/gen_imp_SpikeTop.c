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

API_CALLABLE(kzn_03_TackleAI_Main);

extern NpcData TTYD64_imp_SpikeTop_Npc_SpikeTop[];
extern EvtScript TTYD64_imp_SpikeTop_Script_NpcAI_80243B70_kzn_03;
extern MobileAISettings TTYD64_imp_SpikeTop_AISettings_80243B40_kzn_03;
extern NpcSettings TTYD64_imp_SpikeTop_NpcSettings_80243DCC_kzn_03;

// clang-format off
NpcData TTYD64_imp_SpikeTop_Npc_SpikeTop[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_SpikeTop_NpcSettings_80243DCC_kzn_03,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00002C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 155, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 4, 16383 }, { 9830, 19660, 4, 16383 }, { 16383, 16383, 4, 13106 }, { 26213, 13106, 4, 13106 }, { 32767, 9830, 4, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 2, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 220, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x004D0003, .walk = 0x004D0006, .run = 0x004D0008, .chase = 0x004D0008, .anim_4 = 0x004D0003, .anim_5 = 0x004D0003, .death = 0x004D0013, .hit = 0x004D0013, .anim_8 = 0x004D000B, .anim_9 = 0x004D000A, .anim_A = 0x004D000C, .anim_B = 0x004D0003, .anim_C = 0x004D0003, .anim_D = 0x004D0003, .anim_E = 0x004D0003, .anim_F = 0x004D0003 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_SpikeTop_Script_NpcAI_80243B70_kzn_03 = {
    Call(SetSelfVar, 2, 4)
    Call(SetSelfVar, 3, 10)
    Call(SetSelfVar, 5, 4)
    Call(SetSelfVar, 7, 3)
    Call(kzn_03_TackleAI_Main, Ref(TTYD64_imp_SpikeTop_AISettings_80243B40_kzn_03))
    Return
    End
};

MobileAISettings TTYD64_imp_SpikeTop_AISettings_80243B40_kzn_03 = {
    .moveSpeed = 1.0f,
    .moveTime = 60,
    .waitTime = 60,
    .alertRadius = 90.0f,
    .alertOffsetDist = 40.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 7.0f,
    .chaseTurnRate = 0,
    .chaseUpdateInterval = 0,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 40.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_SpikeTop_NpcSettings_80243DCC_kzn_03 = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_SpikeTop_Script_NpcAI_80243B70_kzn_03,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 17,
    .actionFlags = 0,
};
// clang-format on

void TTYD64_tp_Install_imp_SpikeTop(void) {
}
