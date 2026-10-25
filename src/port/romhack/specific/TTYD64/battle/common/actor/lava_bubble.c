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

API_CALLABLE(kzn_07_FlyingNoAttackAI_Main);

extern NpcData TTYD64_imp_LavaBubble_Npc_LavaBubble[];
extern NpcData TTYD64_imp_LavaBubble_Npc_DarkEmber[];
extern EvtScript TTYD64_imp_LavaBubble_Script_NpcAI_80242BD8_kzn_07;
extern MobileAISettings TTYD64_imp_LavaBubble_AISettings_80242BA8_kzn_07;
extern NpcSettings TTYD64_imp_LavaBubble_NpcSettings_80242C48_kzn_07;

// clang-format off
NpcData TTYD64_imp_LavaBubble_Npc_LavaBubble[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_LavaBubble_NpcSettings_80242C48_kzn_07,
        .pos = { 17.0f, 20.0f, 93.0f },
        .flags = 0x00000400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 140, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 20, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 20, .detectPos.z = 93, .detectSize.x = 220, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00460001, .walk = 0x00460002, .run = 0x00460003, .chase = 0x00460003, .anim_4 = 0x00460001, .anim_5 = 0x00460001, .death = 0x00460007, .hit = 0x00460007, .anim_8 = 0x00460004, .anim_9 = 0x00460001, .anim_A = 0x00460001, .anim_B = 0x00460001, .anim_C = 0x00460001, .anim_D = 0x00460001, .anim_E = 0x00460001, .anim_F = 0x00460001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_imp_LavaBubble_Npc_DarkEmber[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_LavaBubble_NpcSettings_80242C48_kzn_07,
        .pos = { 17.0f, 20.0f, 93.0f },
        .flags = 0x00000400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 140, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 20, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 20, .detectPos.z = 93, .detectSize.x = 220, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00460401, .walk = 0x00460402, .run = 0x00460403, .chase = 0x00460403, .anim_4 = 0x00460401, .anim_5 = 0x00460401, .death = 0x00460407, .hit = 0x00460407, .anim_8 = 0x00460404, .anim_9 = 0x00460401, .anim_A = 0x00460401, .anim_B = 0x00460401, .anim_C = 0x00460401, .anim_D = 0x00460401, .anim_E = 0x00460401, .anim_F = 0x00460401 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_LavaBubble_Script_NpcAI_80242BD8_kzn_07 = {
    Call(SetSelfVar, 0, 1)
    Call(SetSelfVar, 5, 0)
    Call(SetSelfVar, 6, 0)
    Call(SetSelfVar, 1, 150)
    Call(kzn_07_FlyingNoAttackAI_Main, Ref(TTYD64_imp_LavaBubble_AISettings_80242BA8_kzn_07))
    Return
    End
};

MobileAISettings TTYD64_imp_LavaBubble_AISettings_80242BA8_kzn_07 = {
    .moveSpeed = 0.800000012f,
    .moveTime = 100,
    .waitTime = 0,
    .alertRadius = 90.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 4,
    .chaseSpeed = 3.20000005f,
    .chaseTurnRate = 10,
    .chaseUpdateInterval = 1,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_LavaBubble_NpcSettings_80242C48_kzn_07 = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_LavaBubble_Script_NpcAI_80242BD8_kzn_07,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 17,
    .actionFlags = 0,
};
// clang-format on

void TTYD64_tp_Install_imp_LavaBubble(void) {
}
