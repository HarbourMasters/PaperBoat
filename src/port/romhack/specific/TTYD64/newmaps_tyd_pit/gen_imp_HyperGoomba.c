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

API_CALLABLE(arn_04_PatrolNoAttackAI_Main);

extern NpcData TTYD64_imp_HyperGoomba_Npc_HyperGoomba[];
extern MobileAISettings TTYD64_imp_HyperGoomba_AISettings_80243660_arn_04;
extern NpcSettings TTYD64_imp_HyperGoomba_NpcSettings_802436B0_arn_04;
extern EvtScript TTYD64_imp_HyperGoomba_Script_NpcAI_80243690_arn_04;

// clang-format off
NpcData TTYD64_imp_HyperGoomba_Npc_HyperGoomba[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_HyperGoomba_NpcSettings_802436B0_arn_04,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 32, .itemDrops = { { 141, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 150, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00260201, .walk = 0x00260202, .run = 0x00260203, .chase = 0x00260203, .anim_4 = 0x00260201, .anim_5 = 0x00260201, .death = 0x00260205, .hit = 0x00260205, .anim_8 = 0x00260203, .anim_9 = 0x00260203, .anim_A = 0x00260203, .anim_B = 0x00260203, .anim_C = 0x00260203, .anim_D = 0x00260203, .anim_E = 0x00260203, .anim_F = 0x00260203 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

MobileAISettings TTYD64_imp_HyperGoomba_AISettings_80243660_arn_04 = {
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

NpcSettings TTYD64_imp_HyperGoomba_NpcSettings_802436B0_arn_04 = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 23,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_HyperGoomba_Script_NpcAI_80243690_arn_04,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 12,
    .actionFlags = 0,
};

EvtScript TTYD64_imp_HyperGoomba_Script_NpcAI_80243690_arn_04 = {
    Call(arn_04_PatrolNoAttackAI_Main, Ref(TTYD64_imp_HyperGoomba_AISettings_80243660_arn_04))
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_HyperGoomba(void) {
}
