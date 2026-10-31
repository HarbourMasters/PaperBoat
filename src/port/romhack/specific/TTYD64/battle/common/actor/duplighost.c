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

extern NpcData TTYD64_imp_Duplighost_Npc_Duplighost[];
extern MobileAISettings TTYD64_imp_Duplighost_AISettings_80241DE8_pra_39;
extern NpcSettings TTYD64_imp_Duplighost_NpcSettings_80241E38_pra_39;
extern EvtScript TTYD64_imp_Duplighost_Script_Init_80241E64_pra_39;
extern EvtScript TTYD64_imp_Duplighost_Script_NpcAI_80241E18_pra_39;

// clang-format off
NpcData TTYD64_imp_Duplighost_Npc_Duplighost[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_Duplighost_NpcSettings_80241E38_pra_39,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00200C00,
        .init = TTYD64_imp_Duplighost_Script_Init_80241E64_pra_39,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 150, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 3, 13106 }, { 9830, 13106, 3, 13106 }, { 16383, 13106, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x004E0002, .walk = 0x004E0003, .run = 0x004E0004, .chase = 0x004E0004, .anim_4 = 0x004E0002, .anim_5 = 0x004E0002, .death = 0x004E000A, .hit = 0x004E000A, .anim_8 = 0x004E0002, .anim_9 = 0x004E0002, .anim_A = 0x004E0002, .anim_B = 0x004E0002, .anim_C = 0x004E0002, .anim_D = 0x004E0002, .anim_E = 0x004E0002, .anim_F = 0x004E0002 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x02,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

MobileAISettings TTYD64_imp_Duplighost_AISettings_80241DE8_pra_39 = {
    .moveSpeed = 2.0f,
    .moveTime = 60,
    .waitTime = 15,
    .alertRadius = 100.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 4,
    .chaseSpeed = 3.5f,
    .chaseTurnRate = 30,
    .chaseUpdateInterval = 3,
    .chaseRadius = 150.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_Duplighost_NpcSettings_80241E38_pra_39 = {
    .defaultAnim = 0x00000000,
    .height = 30,
    .radius = 30,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Duplighost_Script_NpcAI_80241E18_pra_39,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 23,
    .actionFlags = 0,
};

EvtScript TTYD64_imp_Duplighost_Script_Init_80241E64_pra_39 = {
    Call(SetNpcFlagBits, -1, 0x80000, 1)
    Return
    End
};

EvtScript TTYD64_imp_Duplighost_Script_NpcAI_80241E18_pra_39 = {
    Call(BasicAI_Main, Ref(TTYD64_imp_Duplighost_AISettings_80241DE8_pra_39))
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_Duplighost(void) {
}
