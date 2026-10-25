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

API_CALLABLE(kpa_61_TackleAI_Main);

extern NpcData TTYD64_imp_Koopatrol_Npc_Koopatrol[];
extern EvtScript TTYD64_imp_Koopatrol_Script_NpcAI_80242C30_kpa_61;
extern MobileAISettings TTYD64_imp_Koopatrol_AISettings_80242C00_kpa_61;
extern NpcSettings TTYD64_imp_Koopatrol_NpcSettings_80242CA0_kpa_61;

// clang-format off
NpcData TTYD64_imp_Koopatrol_Npc_Koopatrol[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_Koopatrol_NpcSettings_80242CA0_kpa_61,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 140, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 5, 16383 }, { 9830, 19660, 5, 16383 }, { 16383, 16383, 5, 13106 }, { 26213, 13106, 5, 13106 }, { 32767, 9830, 5, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 50, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00580001, .walk = 0x00580004, .run = 0x00580006, .chase = 0x00580006, .anim_4 = 0x00580001, .anim_5 = 0x00580001, .death = 0x00580010, .hit = 0x00580010, .anim_8 = 0x0058000C, .anim_9 = 0x0058000B, .anim_A = 0x0058000D, .anim_B = 0x00580001, .anim_C = 0x00580001, .anim_D = 0x00580001, .anim_E = 0x00580001, .anim_F = 0x00580001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_Koopatrol_Script_NpcAI_80242C30_kpa_61 = {
    Call(SetSelfVar, 2, 5)
    Call(SetSelfVar, 3, 4)
    Call(SetSelfVar, 5, 10)
    Call(SetSelfVar, 7, 5)
    Call(kpa_61_TackleAI_Main, Ref(TTYD64_imp_Koopatrol_AISettings_80242C00_kpa_61))
    Return
    End
};

MobileAISettings TTYD64_imp_Koopatrol_AISettings_80242C00_kpa_61 = {
    .moveSpeed = 1.0f,
    .moveTime = 30,
    .waitTime = 50,
    .alertRadius = 90.0f,
    .alertOffsetDist = 40.0f,
    .playerSearchInterval = 2,
    .chaseSpeed = 11.0f,
    .chaseTurnRate = 0,
    .chaseUpdateInterval = 0,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 40.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_Koopatrol_NpcSettings_80242CA0_kpa_61 = {
    .defaultAnim = 0x00000000,
    .height = 40,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Koopatrol_Script_NpcAI_80242C30_kpa_61,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 25,
    .actionFlags = 0,
};
// clang-format on

void TTYD64_tp_Install_imp_Koopatrol(void) {
}
