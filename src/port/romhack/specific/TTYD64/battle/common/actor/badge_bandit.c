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

API_CALLABLE(sbk_06_Bandit_TetherStolenCoin);

extern NpcData TTYD64_imp_BadgeBandit_Npc_BadgeBandit[];
extern EvtScript TTYD64_imp_BadgeBandit_Script_80240630_sbk_06;
extern MobileAISettings TTYD64_imp_BadgeBandit_AISettings_802406C8_sbk_06;
extern NpcSettings TTYD64_imp_BadgeBandit_NpcSettings_80240964_sbk_06;
extern EvtScript TTYD64_imp_BadgeBandit_Script_NpcAI_802406F8_sbk_06;

// clang-format off
NpcData TTYD64_imp_BadgeBandit_Npc_BadgeBandit[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_BadgeBandit_NpcSettings_80240964_sbk_06,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00002C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 164, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 1, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 100, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 400, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00320101, .walk = 0x00320105, .run = 0x00320107, .chase = 0x00320107, .anim_4 = 0x00320101, .anim_5 = 0x00320101, .death = 0x00320109, .hit = 0x00320109, .anim_8 = 0x00320100, .anim_9 = 0x00320100, .anim_A = 0x00320100, .anim_B = 0x00320100, .anim_C = 0x00320100, .anim_D = 0x00320100, .anim_E = 0x00320100, .anim_F = 0x00320100 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_BadgeBandit_Script_80240630_sbk_06 = {
    Set(LVarA, LVar0)
    Call(GetNpcPos, LVarA, LVar1, LVar2, LVar3)
    Add(LVar2, 30)
    Call(MakeItemEntity, 343, LVar1, LVar2, LVar3, 1, 0)
    Call(sbk_06_Bandit_TetherStolenCoin, LVarA, LVar0, AreaFlag(1))
    Call(RemoveItemEntity, LVar0)
    Return
    End
};

MobileAISettings TTYD64_imp_BadgeBandit_AISettings_802406C8_sbk_06 = {
    .moveSpeed = 2.70000005f,
    .moveTime = 45,
    .waitTime = 30,
    .alertRadius = 450.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 10,
    .chaseSpeed = 8.30000019f,
    .chaseTurnRate = 180,
    .chaseUpdateInterval = 100,
    .chaseRadius = 550.0f,
    .chaseOffsetDist = 100.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_BadgeBandit_NpcSettings_80240964_sbk_06 = {
    .defaultAnim = 0x00000000,
    .height = 26,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_BadgeBandit_Script_NpcAI_802406F8_sbk_06,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 9,
    .actionFlags = 5,
};

EvtScript TTYD64_imp_BadgeBandit_Script_NpcAI_802406F8_sbk_06 = {
    Call(BasicAI_Main, Ref(TTYD64_imp_BadgeBandit_AISettings_802406C8_sbk_06))
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_BadgeBandit(void) {
}
