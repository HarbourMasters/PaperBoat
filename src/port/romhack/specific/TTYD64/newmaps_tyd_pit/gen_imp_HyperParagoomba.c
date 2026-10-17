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

API_CALLABLE(arn_04_FlyingAI_Main);

extern NpcData TTYD64_imp_HyperParagoomba_Npc_HyperParagoomba[];
extern EvtScript TTYD64_imp_HyperParagoomba_Script_NpcAI_80243724_arn_04;
extern MobileAISettings TTYD64_imp_HyperParagoomba_AISettings_802436F4_arn_04;
extern NpcSettings TTYD64_imp_HyperParagoomba_NpcSettings_80243794_arn_04;

// clang-format off
NpcData TTYD64_imp_HyperParagoomba_Npc_HyperParagoomba[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_HyperParagoomba_NpcSettings_80243794_arn_04,
        .pos = { 17.0f, 50.0f, 93.0f },
        .flags = 0x00000400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 32, .itemDrops = { { 141, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 50, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 50, .detectPos.z = 93, .detectSize.x = 150, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00280201, .walk = 0x00280203, .run = 0x00280204, .chase = 0x00280204, .anim_4 = 0x00280201, .anim_5 = 0x00280201, .death = 0x00280206, .hit = 0x00280206, .anim_8 = 0x00280205, .anim_9 = 0x00280204, .anim_A = 0x00280204, .anim_B = 0x00280204, .anim_C = 0x00280204, .anim_D = 0x00280204, .anim_E = 0x00280204, .anim_F = 0x00280204 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_HyperParagoomba_Script_NpcAI_80243724_arn_04 = {
    Call(SetSelfVar, 0, 1)
    Call(SetSelfVar, 5, -850)
    Call(SetSelfVar, 6, 60)
    Call(SetSelfVar, 1, 700)
    Call(arn_04_FlyingAI_Main, Ref(TTYD64_imp_HyperParagoomba_AISettings_802436F4_arn_04))
    Return
    End
};

MobileAISettings TTYD64_imp_HyperParagoomba_AISettings_802436F4_arn_04 = {
    .moveSpeed = 1.79999995f,
    .moveTime = 60,
    .waitTime = 15,
    .alertRadius = 120.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 4.0f,
    .chaseTurnRate = 5,
    .chaseUpdateInterval = 1,
    .chaseRadius = 150.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_HyperParagoomba_NpcSettings_80243794_arn_04 = {
    .defaultAnim = 0x00000000,
    .height = 18,
    .radius = 20,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_HyperParagoomba_Script_NpcAI_80243724_arn_04,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 12,
    .actionFlags = 1,
};
// clang-format on

void TTYD64_tp_Install_imp_HyperParagoomba(void) {
}
