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

extern NpcData TTYD64_imp_Bobomb_Npc_Bobomb[];
extern MobileAISettings TTYD64_imp_Bobomb_AISettings_80242AD0_trd_02;
extern NpcSettings TTYD64_imp_Bobomb_NpcSettings_80242B20_trd_02;
extern EvtScript TTYD64_imp_Bobomb_Script_NpcAI_80242B00_trd_02;

// clang-format off
NpcData TTYD64_imp_Bobomb_Npc_Bobomb[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_Bobomb_NpcSettings_80242B20_trd_02,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 164, 5, 0 }, { 128, 5, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 50, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 190, .detectSize.z = 155, .detectShape = 1, .isFlying = 1 } },
        .animations = { .idle = 0x002C0002, .walk = 0x002C0004, .run = 0x002C0006, .chase = 0x002C0006, .anim_4 = 0x002C0002, .anim_5 = 0x002C0002, .death = 0x002C000E, .hit = 0x002C000E, .anim_8 = 0x002C0006, .anim_9 = 0x002C0006, .anim_A = 0x002C0006, .anim_B = 0x002C0006, .anim_C = 0x002C0006, .anim_D = 0x002C0006, .anim_E = 0x002C0006, .anim_F = 0x002C0006 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

MobileAISettings TTYD64_imp_Bobomb_AISettings_80242AD0_trd_02 = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 10,
    .alertRadius = 110.0f,
    .alertOffsetDist = 65.0f,
    .playerSearchInterval = 8,
    .chaseSpeed = 3.4000001f,
    .chaseTurnRate = 120,
    .chaseUpdateInterval = 2,
    .chaseRadius = 110.0f,
    .chaseOffsetDist = 65.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_Bobomb_NpcSettings_80242B20_trd_02 = {
    .defaultAnim = 0x00000000,
    .height = 23,
    .radius = 20,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Bobomb_Script_NpcAI_80242B00_trd_02,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 6,
    .actionFlags = 0,
};

EvtScript TTYD64_imp_Bobomb_Script_NpcAI_80242B00_trd_02 = {
    Call(BasicAI_Main, Ref(TTYD64_imp_Bobomb_AISettings_80242AD0_trd_02))
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_Bobomb(void) {
}
