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

API_CALLABLE(isk_04_TackleAI_Main);

extern NpcData TTYD64_imp_BuzzyBeetle_Npc_BuzzyBeetle[];
extern EvtScript TTYD64_imp_BuzzyBeetle_Script_NpcAI_80241560_isk_04;
extern MobileAISettings TTYD64_imp_BuzzyBeetle_AISettings_80241530_isk_04;
extern NpcSettings TTYD64_imp_BuzzyBeetle_NpcSettings_80241804_isk_04;

// clang-format off
NpcData TTYD64_imp_BuzzyBeetle_Npc_BuzzyBeetle[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_BuzzyBeetle_NpcSettings_80241804_isk_04,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 355,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 26213, 2, 16383 }, { 9830, 22936, 2, 16383 }, { 16383, 19660, 2, 13106 }, { 26213, 16383, 2, 13106 }, { 32767, 13106, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 1, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00330001, .walk = 0x00330003, .run = 0x00330004, .chase = 0x00330004, .anim_4 = 0x00330000, .anim_5 = 0x00330000, .death = 0x00330007, .hit = 0x00330007, .anim_8 = 0x0033000C, .anim_9 = 0x00330005, .anim_A = 0x0033000D, .anim_B = 0x00330000, .anim_C = 0x00330000, .anim_D = 0x00330000, .anim_E = 0x00330000, .anim_F = 0x00330000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_BuzzyBeetle_Script_NpcAI_80241560_isk_04 = {
    Call(SetSelfVar, 2, 5)
    Call(SetSelfVar, 3, 2)
    Call(SetSelfVar, 5, 5)
    Call(SetSelfVar, 7, 2)
    Call(isk_04_TackleAI_Main, Ref(TTYD64_imp_BuzzyBeetle_AISettings_80241530_isk_04))
    Return
    End
};

MobileAISettings TTYD64_imp_BuzzyBeetle_AISettings_80241530_isk_04 = {
    .moveSpeed = 1.0f,
    .moveTime = 60,
    .waitTime = 60,
    .alertRadius = 90.0f,
    .alertOffsetDist = 40.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 4.5f,
    .chaseTurnRate = 0,
    .chaseUpdateInterval = 0,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 40.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_BuzzyBeetle_NpcSettings_80241804_isk_04 = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_BuzzyBeetle_Script_NpcAI_80241560_isk_04,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 10,
    .actionFlags = 0,
};
// clang-format on

void TTYD64_tp_Install_imp_BuzzyBeetle(void) {
}
