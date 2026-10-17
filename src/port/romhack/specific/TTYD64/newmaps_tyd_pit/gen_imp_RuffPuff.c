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

API_CALLABLE(flo_16_FlyingNoAttackAI_Main);

extern NpcData TTYD64_imp_RuffPuff_Npc_PoisonPuff[];
extern NpcData TTYD64_imp_RuffPuff_Npc_RuffPuff[];
extern EvtScript TTYD64_imp_RuffPuff_Script_NpcAI_80244058_flo_16;
extern MobileAISettings TTYD64_imp_RuffPuff_AISettings_80244028_flo_16;
extern NpcSettings TTYD64_imp_RuffPuff_NpcSettings_802440C8_flo_16;

// clang-format off
NpcData TTYD64_imp_RuffPuff_Npc_PoisonPuff[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_RuffPuff_NpcSettings_802440C8_flo_16,
        .pos = { 17.0f, 45.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 16, .itemDrops = { { 140, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 45, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 45, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x007D0100, .walk = 0x007D0100, .run = 0x007D0105, .chase = 0x007D0105, .anim_4 = 0x007D0100, .anim_5 = 0x007D0100, .death = 0x007D0106, .hit = 0x007D0106, .anim_8 = 0x007D0105, .anim_9 = 0x007D0101, .anim_A = 0x007D0101, .anim_B = 0x007D0101, .anim_C = 0x007D0101, .anim_D = 0x007D0101, .anim_E = 0x007D0101, .anim_F = 0x007D0101 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_imp_RuffPuff_Npc_RuffPuff[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_RuffPuff_NpcSettings_802440C8_flo_16,
        .pos = { 17.0f, 45.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 16, .itemDrops = { { 130, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 45, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 45, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x007D0000, .walk = 0x007D0000, .run = 0x007D0005, .chase = 0x007D0005, .anim_4 = 0x007D0000, .anim_5 = 0x007D0000, .death = 0x007D0006, .hit = 0x007D0006, .anim_8 = 0x007D0005, .anim_9 = 0x007D0001, .anim_A = 0x007D0001, .anim_B = 0x007D0001, .anim_C = 0x007D0001, .anim_D = 0x007D0001, .anim_E = 0x007D0001, .anim_F = 0x007D0001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_RuffPuff_Script_NpcAI_80244058_flo_16 = {
    Call(SetSelfVar, 0, 1)
    Call(SetSelfVar, 5, 0)
    Call(SetSelfVar, 6, 0)
    Call(SetSelfVar, 1, 600)
    Call(flo_16_FlyingNoAttackAI_Main, Ref(TTYD64_imp_RuffPuff_AISettings_80244028_flo_16))
    Return
    End
};

MobileAISettings TTYD64_imp_RuffPuff_AISettings_80244028_flo_16 = {
    .moveSpeed = 1.0f,
    .moveTime = 45,
    .waitTime = 60,
    .alertRadius = 100.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 3.5999999f,
    .chaseTurnRate = 10,
    .chaseUpdateInterval = 1,
    .chaseRadius = 120.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_RuffPuff_NpcSettings_802440C8_flo_16 = {
    .defaultAnim = 0x00000000,
    .height = 24,
    .radius = 28,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_RuffPuff_Script_NpcAI_80244058_flo_16,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 19,
    .actionFlags = 0,
};
// clang-format on

void TTYD64_tp_Install_imp_RuffPuff(void) {
}
