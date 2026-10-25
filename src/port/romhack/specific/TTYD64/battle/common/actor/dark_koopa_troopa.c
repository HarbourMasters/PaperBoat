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

API_CALLABLE(tik_09_TackleAI_Main);

extern NpcData TTYD64_imp_DarkKoopaTroopa_Npc_DarkKoopaTroopa[];
extern EvtScript TTYD64_imp_DarkKoopaTroopa_Script_NpcAI_802438F0_tik_09;
extern MobileAISettings TTYD64_imp_DarkKoopaTroopa_AISettings_802438C0_tik_09;
extern NpcSettings TTYD64_imp_DarkKoopaTroopa_NpcSettings_80243960_tik_09;

// clang-format off
NpcData TTYD64_imp_DarkKoopaTroopa_Npc_DarkKoopaTroopa[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_DarkKoopaTroopa_NpcSettings_80243960_tik_09,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00040C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 32, .itemDrops = { { 144, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 1, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00290002, .walk = 0x00290002, .run = 0x00290002, .chase = 0x00290002, .anim_4 = 0x00290002, .anim_5 = 0x00290002, .death = 0x0029000B, .hit = 0x0029000B, .anim_8 = 0x00290007, .anim_9 = 0x00290006, .anim_A = 0x00290008, .anim_B = 0x00290000, .anim_C = 0x00290004, .anim_D = 0x00290004, .anim_E = 0x00290004, .anim_F = 0x00290004 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x02,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_DarkKoopaTroopa_Script_NpcAI_802438F0_tik_09 = {
    Call(SetSelfVar, 2, 6)
    Call(SetSelfVar, 3, 4)
    Call(SetSelfVar, 5, 13)
    Call(SetSelfVar, 7, 1)
    Call(tik_09_TackleAI_Main, Ref(TTYD64_imp_DarkKoopaTroopa_AISettings_802438C0_tik_09))
    Return
    End
};

MobileAISettings TTYD64_imp_DarkKoopaTroopa_AISettings_802438C0_tik_09 = {
    .moveSpeed = 2.0f,
    .moveTime = 60,
    .waitTime = 5,
    .alertRadius = 80.0f,
    .alertOffsetDist = 60.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 9.0f,
    .chaseTurnRate = 0,
    .chaseUpdateInterval = 0,
    .chaseRadius = 90.0f,
    .chaseOffsetDist = 70.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_DarkKoopaTroopa_NpcSettings_80243960_tik_09 = {
    .defaultAnim = 0x00000000,
    .height = 35,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_DarkKoopaTroopa_Script_NpcAI_802438F0_tik_09,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 18,
    .actionFlags = 0,
};
// clang-format on

void TTYD64_tp_Install_imp_DarkKoopaTroopa(void) {
}
