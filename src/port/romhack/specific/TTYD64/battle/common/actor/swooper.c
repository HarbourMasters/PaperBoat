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

API_CALLABLE(pra_04_SwooperAI_Main);

extern NpcData TTYD64_imp_Swooper_Npc_Swampire[];
extern MobileAISettings TTYD64_imp_Swooper_AISettings_80241200_pra_04;
extern NpcSettings TTYD64_imp_Swooper_NpcSettings_8024127C_pra_04;
extern EvtScript TTYD64_imp_Swooper_Script_NpcAI_80241230_pra_04;

// clang-format off
NpcData TTYD64_imp_Swooper_Npc_Swampire[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_Swooper_NpcSettings_8024127C_pra_04,
        .pos = { 17.0f, 159.0f, 93.0f },
        .flags = 0x00200C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 139, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 4, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 159, .centerPos.z = 93, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 159, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x0034021B, .walk = 0x00340202, .run = 0x00340202, .chase = 0x00340202, .anim_4 = 0x0034021B, .anim_5 = 0x0034021B, .death = 0x00340204, .hit = 0x00340215, .anim_8 = 0x00340200, .anim_9 = 0x00340200, .anim_A = 0x00340201, .anim_B = 0x00340201, .anim_C = 0x00340201, .anim_D = 0x00340201, .anim_E = 0x00340201, .anim_F = 0x00340201 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

MobileAISettings TTYD64_imp_Swooper_AISettings_80241200_pra_04 = {
    .moveSpeed = 1.60000002f,
    .moveTime = 60,
    .waitTime = 30,
    .alertRadius = 80.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 5,
    .chaseSpeed = 2.20000005f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 15,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_Swooper_NpcSettings_8024127C_pra_04 = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 20,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Swooper_Script_NpcAI_80241230_pra_04,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000800,
    .unk_24 = 0,
    .level = 22,
    .actionFlags = 0,
};

EvtScript TTYD64_imp_Swooper_Script_NpcAI_80241230_pra_04 = {
    Call(pra_04_SwooperAI_Main, Ref(TTYD64_imp_Swooper_AISettings_80241200_pra_04))
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_Swooper(void) {
}
