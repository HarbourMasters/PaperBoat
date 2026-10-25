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

extern NpcData TTYD64_imp_SpikedGloomba_Npc_SpikedGloomba[];
extern MobileAISettings TTYD64_imp_SpikedGloomba_AISettings_80242040_kmr_06;
extern NpcSettings TTYD64_imp_SpikedGloomba_NpcSettings_80242090_kmr_06;
extern EvtScript TTYD64_imp_SpikedGloomba_Script_NpcAI_80242070_kmr_06;

// clang-format off
NpcData TTYD64_imp_SpikedGloomba_Npc_SpikedGloomba[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_SpikedGloomba_NpcSettings_80242090_kmr_06,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00002C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 138, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 20, .moveSpeedOverride = -32767, .wanderShape = 1, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00270101, .walk = 0x00270102, .run = 0x00270103, .chase = 0x00270103, .anim_4 = 0x00270101, .anim_5 = 0x00270101, .death = 0x00270105, .hit = 0x00270105, .anim_8 = 0x00270103, .anim_9 = 0x00270103, .anim_A = 0x00270103, .anim_B = 0x00270103, .anim_C = 0x00270103, .anim_D = 0x00270103, .anim_E = 0x00270103, .anim_F = 0x00270103 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

MobileAISettings TTYD64_imp_SpikedGloomba_AISettings_80242040_kmr_06 = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 130.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 2.5f,
    .chaseTurnRate = 180,
    .chaseUpdateInterval = 3,
    .chaseRadius = 150.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_SpikedGloomba_NpcSettings_80242090_kmr_06 = {
    .defaultAnim = 0x00000000,
    .height = 23,
    .radius = 23,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_SpikedGloomba_Script_NpcAI_80242070_kmr_06,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 6,
    .actionFlags = 0,
};

EvtScript TTYD64_imp_SpikedGloomba_Script_NpcAI_80242070_kmr_06 = {
    Call(BasicAI_Main, Ref(TTYD64_imp_SpikedGloomba_AISettings_80242040_kmr_06))
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_SpikedGloomba(void) {
}
