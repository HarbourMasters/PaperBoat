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

API_CALLABLE(nok_14_ParatroopaAI_Main);

extern NpcData TTYD64_imp_Paratroopa_Npc_Paratroopa[];
extern EvtScript TTYD64_imp_Paratroopa_Script_NpcAI_80243A60_nok_14;
extern MobileAISettings TTYD64_imp_Paratroopa_AISettings_80243A30_nok_14;
extern NpcSettings TTYD64_imp_Paratroopa_NpcSettings_80243AD0_nok_14;

// clang-format off
NpcData TTYD64_imp_Paratroopa_Npc_Paratroopa[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_Paratroopa_NpcSettings_80243AD0_nok_14,
        .pos = { 17.0f, 50.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 144, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 1, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 50, .centerPos.z = 93, .wanderSize.x = 65, .wanderSize.z = 40, .moveSpeedOverride = -32767, .wanderShape = 1, .detectPos.x = 17, .detectPos.y = 50, .detectPos.z = 93, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002A0101, .walk = 0x002A0102, .run = 0x002A0103, .chase = 0x002A0103, .anim_4 = 0x002A0101, .anim_5 = 0x002A0101, .death = 0x002A0106, .hit = 0x002A0106, .anim_8 = 0x002A0104, .anim_9 = 0x002A010C, .anim_A = 0x002A010A, .anim_B = 0x002A010E, .anim_C = 0x002A0103, .anim_D = 0x002A0103, .anim_E = 0x002A0103, .anim_F = 0x002A0103 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_Paratroopa_Script_NpcAI_80243A60_nok_14 = {
    Call(SetSelfVar, 0, 0)
    Call(SetSelfVar, 5, -650)
    Call(SetSelfVar, 6, 30)
    Call(SetSelfVar, 1, 600)
    Call(nok_14_ParatroopaAI_Main, Ref(TTYD64_imp_Paratroopa_AISettings_80243A30_nok_14))
    Return
    End
};

MobileAISettings TTYD64_imp_Paratroopa_AISettings_80243A30_nok_14 = {
    .moveSpeed = 2.0f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 100.0f,
    .alertOffsetDist = 20.0f,
    .playerSearchInterval = 10,
    .chaseSpeed = 2.5999999f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 10,
    .chaseRadius = 150.0f,
    .chaseOffsetDist = 20.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_Paratroopa_NpcSettings_80243AD0_nok_14 = {
    .defaultAnim = 0x00000000,
    .height = 40,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Paratroopa_Script_NpcAI_80243A60_nok_14,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 6,
    .actionFlags = 1,
};
// clang-format on

void TTYD64_tp_Install_imp_Paratroopa(void) {
}
