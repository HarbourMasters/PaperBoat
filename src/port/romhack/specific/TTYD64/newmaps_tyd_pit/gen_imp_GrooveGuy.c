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

API_CALLABLE(omo_05_GrooveGuyAI_Main);

extern NpcData TTYD64_imp_GrooveGuy_Npc_GrooveGuy[];
extern MobileAISettings TTYD64_imp_GrooveGuy_AISettings_80242F0C_omo_05;
extern NpcSettings TTYD64_imp_GrooveGuy_NpcSettings_80242F5C_omo_05;
extern EvtScript TTYD64_imp_GrooveGuy_Script_NpcAI_80242F3C_omo_05;

// clang-format off
NpcData TTYD64_imp_GrooveGuy_Npc_GrooveGuy[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_GrooveGuy_NpcSettings_80242F5C_omo_05,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 128, 2, 0 }, { 130, 2, 0 }, { 132, 2, 0 }, { 134, 2, 0 }, { 133, 2, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x003C0001, .walk = 0x003C0003, .run = 0x003C0004, .chase = 0x003C0003, .anim_4 = 0x003C0001, .anim_5 = 0x003C0001, .death = 0x003C0008, .hit = 0x003C0008, .anim_8 = 0x003C0001, .anim_9 = 0x003C0001, .anim_A = 0x003C0001, .anim_B = 0x003C0001, .anim_C = 0x003C0001, .anim_D = 0x003C0001, .anim_E = 0x003C0001, .anim_F = 0x003C0001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

MobileAISettings TTYD64_imp_GrooveGuy_AISettings_80242F0C_omo_05 = {
    .moveSpeed = 1.70000005f,
    .moveTime = 80,
    .waitTime = 1,
    .alertRadius = 100.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 4,
    .chaseSpeed = 4.5f,
    .chaseTurnRate = 20,
    .chaseUpdateInterval = 1,
    .chaseRadius = 140.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_GrooveGuy_NpcSettings_80242F5C_omo_05 = {
    .defaultAnim = 0x00000000,
    .height = 24,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_GrooveGuy_Script_NpcAI_80242F3C_omo_05,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 15,
    .actionFlags = 1,
};

EvtScript TTYD64_imp_GrooveGuy_Script_NpcAI_80242F3C_omo_05 = {
    Call(omo_05_GrooveGuyAI_Main, Ref(TTYD64_imp_GrooveGuy_AISettings_80242F0C_omo_05))
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_GrooveGuy(void) {
}
