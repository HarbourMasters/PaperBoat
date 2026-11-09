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

API_CALLABLE(flo_09_FlyingAI_Main);

extern NpcData TTYD64_imp_Bzzap_Npc_Bzzap[];
extern EvtScript TTYD64_imp_Bzzap_Script_NpcAI_80243674_flo_09;
extern MobileAISettings TTYD64_imp_Bzzap_AISettings_80243644_flo_09;
extern NpcSettings TTYD64_imp_Bzzap_NpcSettings_802436E4_flo_09;

// clang-format off
NpcData TTYD64_imp_Bzzap_Npc_Bzzap[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_Bzzap_NpcSettings_802436E4_flo_09,
        .pos = { 17.0f, 55.0f, 93.0f },
        .flags = 0x00002D00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 21, .itemDrops = { { 163, 6, 0 }, { 164, 4, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 1, .maxCoinBonus = 4, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 55, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 50, .detectPos.z = 93, .detectSize.x = 250, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x004B0002, .walk = 0x004B0002, .run = 0x004B0003, .chase = 0x004B0003, .anim_4 = 0x004B0001, .anim_5 = 0x004B0002, .death = 0x004B0006, .hit = 0x004B0006, .anim_8 = 0x004B0004, .anim_9 = 0x004B0002, .anim_A = 0x004B0001, .anim_B = 0x004B0001, .anim_C = 0x004B0001, .anim_D = 0x004B0001, .anim_E = 0x004B0001, .anim_F = 0x004B0001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_Bzzap_Script_NpcAI_80243674_flo_09 = {
    Call(SetSelfVar, 0, 0)
    Call(SetSelfVar, 5, -630)
    Call(SetSelfVar, 6, 50)
    Call(SetSelfVar, 1, 200)
    Call(flo_09_FlyingAI_Main, Ref(TTYD64_imp_Bzzap_AISettings_80243644_flo_09))
    Return
    End
};

MobileAISettings TTYD64_imp_Bzzap_AISettings_80243644_flo_09 = {
    .moveSpeed = 1.0f,
    .moveTime = 30,
    .waitTime = 5,
    .alertRadius = 80.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 2,
    .chaseSpeed = 4.5f,
    .chaseTurnRate = 6,
    .chaseUpdateInterval = 1,
    .chaseRadius = 90.0f,
    .chaseOffsetDist = 30.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_Bzzap_NpcSettings_802436E4_flo_09 = {
    .defaultAnim = 0x00000000,
    .height = 26,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Bzzap_Script_NpcAI_80243674_flo_09,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 19,
    .actionFlags = 0,
};
// clang-format on

void TTYD64_tp_Install_imp_Bzzap(void) {
}
