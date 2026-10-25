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

API_CALLABLE(omo_04_ShyGuyWanderAI_Main);

extern NpcData TTYD64_imp_ShyGuy_Npc_ShyGuy[];
extern MobileAISettings TTYD64_imp_ShyGuy_AISettings_80242FD4_omo_04;
extern NpcSettings TTYD64_imp_ShyGuy_NpcSettings_80243024_omo_04;
extern EvtScript TTYD64_imp_ShyGuy_Script_NpcAI_80243004_omo_04;

// clang-format off
NpcData TTYD64_imp_ShyGuy_Npc_ShyGuy[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_ShyGuy_NpcSettings_80243024_omo_04,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000800,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 154, 2, 0 }, { 140, 2, 0 }, { 132, 2, 0 }, { 141, 2, 0 }, { 143, 2, 0 }, { 144, 2, 0 }, { 152, 2, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x003B0001, .walk = 0x003B0002, .run = 0x003B0003, .chase = 0x003B0003, .anim_4 = 0x003B0001, .anim_5 = 0x003B0001, .death = 0x003B000C, .hit = 0x003B000C, .anim_8 = 0x003B0015, .anim_9 = 0x003B0012, .anim_A = 0x003B0011, .anim_B = 0x003B0010, .anim_C = 0x003B0005, .anim_D = 0x003B0001, .anim_E = 0x003B0001, .anim_F = 0x003B0001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

MobileAISettings TTYD64_imp_ShyGuy_AISettings_80242FD4_omo_04 = {
    .moveSpeed = 2.0f,
    .moveTime = 60,
    .waitTime = 15,
    .alertRadius = 100.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 4,
    .chaseSpeed = 4.0f,
    .chaseTurnRate = 6,
    .chaseUpdateInterval = 1,
    .chaseRadius = 140.0f,
    .chaseOffsetDist = 30.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_ShyGuy_NpcSettings_80243024_omo_04 = {
    .defaultAnim = 0x00000000,
    .height = 23,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_ShyGuy_Script_NpcAI_80243004_omo_04,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 14,
    .actionFlags = 1,
};

EvtScript TTYD64_imp_ShyGuy_Script_NpcAI_80243004_omo_04 = {
    Call(omo_04_ShyGuyWanderAI_Main, Ref(TTYD64_imp_ShyGuy_AISettings_80242FD4_omo_04))
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_ShyGuy(void) {
}
