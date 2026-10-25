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

API_CALLABLE(tik_07_FlyingAI_Main);

extern NpcData TTYD64_imp_Paragloomba_Npc_Paragloomba[];
extern EvtScript TTYD64_imp_Paragloomba_Script_NpcAI_80244CF8_tik_07;
extern MobileAISettings TTYD64_imp_Paragloomba_AISettings_80244CC8_tik_07;
extern NpcSettings TTYD64_imp_Paragloomba_NpcSettings_80244D68_tik_07;

// clang-format off
NpcData TTYD64_imp_Paragloomba_Npc_Paragloomba[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_Paragloomba_NpcSettings_80244D68_tik_07,
        .pos = { 17.0f, 50.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 32, .itemDrops = { { 154, 5, 0 }, { 143, 5, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 50, .centerPos.z = 93, .wanderSize.x = 20, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 50, .detectPos.z = 93, .detectSize.x = 150, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00280301, .walk = 0x00280303, .run = 0x00280304, .chase = 0x00280304, .anim_4 = 0x00280301, .anim_5 = 0x00280301, .death = 0x00280306, .hit = 0x00280306, .anim_8 = 0x00280305, .anim_9 = 0x00280304, .anim_A = 0x00280300, .anim_B = 0x00280300, .anim_C = 0x00280300, .anim_D = 0x00280300, .anim_E = 0x00280300, .anim_F = 0x00280300 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_Paragloomba_Script_NpcAI_80244CF8_tik_07 = {
    Call(SetSelfVar, 0, 1)
    Call(SetSelfVar, 5, -850)
    Call(SetSelfVar, 6, 60)
    Call(SetSelfVar, 1, 600)
    Call(tik_07_FlyingAI_Main, Ref(TTYD64_imp_Paragloomba_AISettings_80244CC8_tik_07))
    Return
    End
};

MobileAISettings TTYD64_imp_Paragloomba_AISettings_80244CC8_tik_07 = {
    .moveSpeed = 2.0f,
    .moveTime = 0,
    .waitTime = 0,
    .alertRadius = 80.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 5,
    .chaseSpeed = 3.0f,
    .chaseTurnRate = 10,
    .chaseUpdateInterval = 2,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_Paragloomba_NpcSettings_80244D68_tik_07 = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 21,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Paragloomba_Script_NpcAI_80244CF8_tik_07,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 11,
    .actionFlags = 0,
};
// clang-format on

void TTYD64_tp_Install_imp_Paragloomba(void) {
}
