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

API_CALLABLE(iwa_03_CleftAI_Main);

extern NpcData TTYD64_imp_Cleft_Npc_Cleft[];
extern MobileAISettings TTYD64_imp_Cleft_AISettings_80241EF0_iwa_03;
extern NpcSettings TTYD64_imp_Cleft_NpcSettings_80241F44_iwa_03;
extern EvtScript TTYD64_imp_Cleft_Script_NpcAI_80241F20_iwa_03;

// clang-format off
NpcData TTYD64_imp_Cleft_Npc_Cleft[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_Cleft_NpcSettings_80241F44_iwa_03,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 1, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 250, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00300002, .walk = 0x00300006, .run = 0x00300007, .chase = 0x00300007, .anim_4 = 0x00300002, .anim_5 = 0x00300002, .death = 0x00300008, .hit = 0x00300008, .anim_8 = 0x00300014, .anim_9 = 0x00300017, .anim_A = 0x00300013, .anim_B = 0x00300015, .anim_C = 0x00300010, .anim_D = 0x00300011, .anim_E = 0x00300016, .anim_F = 0x00300000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

MobileAISettings TTYD64_imp_Cleft_AISettings_80241EF0_iwa_03 = {
    .moveSpeed = 1.0f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 120.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 7.0f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 5,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 60.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_Cleft_NpcSettings_80241F44_iwa_03 = {
    .defaultAnim = 0x00000000,
    .height = 26,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Cleft_Script_NpcAI_80241F20_iwa_03,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 10,
    .actionFlags = 0,
};

EvtScript TTYD64_imp_Cleft_Script_NpcAI_80241F20_iwa_03 = {
    Call(iwa_03_CleftAI_Main, Ref(TTYD64_imp_Cleft_AISettings_80241EF0_iwa_03), 16)
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_Cleft(void) {
}
