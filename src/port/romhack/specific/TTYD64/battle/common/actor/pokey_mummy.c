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

API_CALLABLE(sbk_00_SetPokeyInstigatorValue);

extern NpcData TTYD64_imp_PokeyMummy_Npc_PokeyMummy[];
extern MobileAISettings TTYD64_imp_PokeyMummy_AISettings_80240300_sbk_00;
extern NpcSettings TTYD64_imp_PokeyMummy_NpcSettings_8024035C_sbk_00;
extern EvtScript TTYD64_imp_PokeyMummy_Script_NpcAI_80240330_sbk_00;

// clang-format off
NpcData TTYD64_imp_PokeyMummy_Npc_PokeyMummy[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_PokeyMummy_NpcSettings_8024035C_sbk_00,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000800,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 21, .itemDrops = { { 168, 9, 0 }, { 137, 1, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 100, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 250, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00310104, .walk = 0x00310108, .run = 0x00310108, .chase = 0x00310108, .anim_4 = 0x00310104, .anim_5 = 0x00310104, .death = 0x0031010C, .hit = 0x0031010C, .anim_8 = 0x00310108, .anim_9 = 0x00310108, .anim_A = 0x00310108, .anim_B = 0x00310108, .anim_C = 0x00310108, .anim_D = 0x00310108, .anim_E = 0x00310108, .anim_F = 0x00310108 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

MobileAISettings TTYD64_imp_PokeyMummy_AISettings_80240300_sbk_00 = {
    .moveSpeed = 1.79999995f,
    .moveTime = 50,
    .waitTime = 10,
    .alertRadius = 250.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 2,
    .chaseSpeed = 3.5f,
    .chaseTurnRate = 45,
    .chaseUpdateInterval = 6,
    .chaseRadius = 300.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_PokeyMummy_NpcSettings_8024035C_sbk_00 = {
    .defaultAnim = 0x00000000,
    .height = 72,
    .radius = 15,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_PokeyMummy_Script_NpcAI_80240330_sbk_00,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 9,
    .actionFlags = 0,
};

EvtScript TTYD64_imp_PokeyMummy_Script_NpcAI_80240330_sbk_00 = {
    Call(sbk_00_SetPokeyInstigatorValue)
    Call(BasicAI_Main, Ref(TTYD64_imp_PokeyMummy_AISettings_80240300_sbk_00))
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_PokeyMummy(void) {
}
