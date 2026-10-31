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

API_CALLABLE(jan_01_HoppingAI_Main);

extern NpcData TTYD64_imp_JungleFuzzy_Npc_JungleFuzzy[];
extern EvtScript TTYD64_imp_JungleFuzzy_Script_NpcAI_802419B0_jan_01;
extern MobileAISettings TTYD64_imp_JungleFuzzy_AISettings_80241980_jan_01;
extern NpcSettings TTYD64_imp_JungleFuzzy_NpcSettings_802419EC_jan_01;

// clang-format off
NpcData TTYD64_imp_JungleFuzzy_Npc_JungleFuzzy[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_JungleFuzzy_NpcSettings_802419EC_jan_01,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00400400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 138, 3, 0 }, { 166, 7, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 50, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002B0302, .walk = 0x002B0302, .run = 0x002B0303, .chase = 0x002B0303, .anim_4 = 0x002B0301, .anim_5 = 0x002B0301, .death = 0x002B0308, .hit = 0x002B0308, .anim_8 = 0x002B0303, .anim_9 = 0x002B0303, .anim_A = 0x002B0303, .anim_B = 0x002B0303, .anim_C = 0x002B0303, .anim_D = 0x002B0303, .anim_E = 0x002B0303, .anim_F = 0x002B0303 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x02,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_JungleFuzzy_Script_NpcAI_802419B0_jan_01 = {
    Call(SetNpcFlagBits, -1, 64, 1)
    Call(jan_01_HoppingAI_Main, Ref(TTYD64_imp_JungleFuzzy_AISettings_80241980_jan_01), 2)
    Return
    End
};

MobileAISettings TTYD64_imp_JungleFuzzy_AISettings_80241980_jan_01 = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 10,
    .alertRadius = 150.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 5.0f,
    .chaseTurnRate = 70,
    .chaseUpdateInterval = 5,
    .chaseRadius = 200.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_JungleFuzzy_NpcSettings_802419EC_jan_01 = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_JungleFuzzy_Script_NpcAI_802419B0_jan_01,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 16,
    .actionFlags = 0,
};
// clang-format on

void TTYD64_tp_Install_imp_JungleFuzzy(void) {
}
