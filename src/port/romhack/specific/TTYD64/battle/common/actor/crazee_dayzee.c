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

extern NpcData TTYD64_imp_CrazeeDayzee_Npc_CrazeeDayzee[];
extern MobileAISettings TTYD64_imp_CrazeeDayzee_AISettings_8024300C_flo_08;
extern NpcSettings TTYD64_imp_CrazeeDayzee_NpcSettings_8024305C_flo_08;
extern EvtScript TTYD64_imp_CrazeeDayzee_Script_NpcAI_8024303C_flo_08;

// clang-format off
NpcData TTYD64_imp_CrazeeDayzee_Npc_CrazeeDayzee[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_CrazeeDayzee_NpcSettings_8024305C_flo_08,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 21, .itemDrops = { { 163, 6, 0 }, { 164, 4, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 4, 13106 }, { 9830, 13106, 4, 13106 }, { 16383, 13106, 4, 13106 }, { 26213, 13106, 4, 13106 }, { 32767, 9830, 4, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00480001, .walk = 0x00480002, .run = 0x00480003, .chase = 0x00480003, .anim_4 = 0x00480001, .anim_5 = 0x00480001, .death = 0x00480008, .hit = 0x00480008, .anim_8 = 0x00480006, .anim_9 = 0x00480007, .anim_A = 0x00480001, .anim_B = 0x00480001, .anim_C = 0x00480001, .anim_D = 0x00480001, .anim_E = 0x00480001, .anim_F = 0x00480001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

MobileAISettings TTYD64_imp_CrazeeDayzee_AISettings_8024300C_flo_08 = {
    .moveSpeed = 1.0f,
    .moveTime = 500,
    .waitTime = 10,
    .alertRadius = 50.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 3.5f,
    .chaseTurnRate = 40,
    .chaseUpdateInterval = 3,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 30.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_CrazeeDayzee_NpcSettings_8024305C_flo_08 = {
    .defaultAnim = 0x00000000,
    .height = 30,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_CrazeeDayzee_Script_NpcAI_8024303C_flo_08,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 19,
    .actionFlags = 0,
};

EvtScript TTYD64_imp_CrazeeDayzee_Script_NpcAI_8024303C_flo_08 = {
    Call(BasicAI_Main, Ref(TTYD64_imp_CrazeeDayzee_AISettings_8024300C_flo_08))
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_CrazeeDayzee(void) {
}
