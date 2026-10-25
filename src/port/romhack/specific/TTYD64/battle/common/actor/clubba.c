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

API_CALLABLE(dgb_02_MeleeHitbox_Main);
API_CALLABLE(dgb_02_WanderMeleeAI_Main);

extern NpcData TTYD64_imp_Clubba_Npc_Clubba[];
extern EvtScript TTYD64_imp_Clubba_Script_80241AB0_dgb_02;
extern EvtScript TTYD64_imp_Clubba_Script_NpcAI_80241D34_dgb_02;
extern EvtScript TTYD64_imp_Clubba_Script_NpcAI_80241BCC_dgb_02;
extern MobileAISettings TTYD64_imp_Clubba_AISettings_80241B9C_dgb_02;
extern NpcSettings TTYD64_imp_Clubba_NpcSettings_80241C3C_dgb_02;
extern NpcSettings TTYD64_imp_Clubba_NpcSettings_80241DDC_dgb_02;
extern AnimID TTYD64_imp_Clubba_ExtraAnimationList_80241B6C_dgb_02[];
extern AnimID TTYD64_imp_Clubba_ExtraAnimationList_80241B94_dgb_02[];

// clang-format off
NpcData TTYD64_imp_Clubba_Npc_Clubba[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_Clubba_NpcSettings_80241C3C_dgb_02,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 140, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 2, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 40, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 88, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00390002, .walk = 0x00390003, .run = 0x00390004, .chase = 0x00390004, .anim_4 = 0x00390002, .anim_5 = 0x00390002, .death = 0x0039000C, .hit = 0x0039000C, .anim_8 = 0x00390011, .anim_9 = 0x00390012, .anim_A = 0x00390007, .anim_B = 0x00390008, .anim_C = 0x00390001, .anim_D = 0x00390002, .anim_E = 0x00390002, .anim_F = 0x00390002 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x02,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_Clubba_ExtraAnimationList_80241B6C_dgb_02,
        .tattle = 0,
    },
    {
        .id = 1,
        .settings = &TTYD64_imp_Clubba_NpcSettings_80241DDC_dgb_02,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800D00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00390002, .walk = 0x00390003, .run = 0x00390004, .chase = 0x00390004, .anim_4 = 0x00390002, .anim_5 = 0x00390002, .death = 0x0039000C, .hit = 0x0039000C, .anim_8 = 0x00390011, .anim_9 = 0x00390012, .anim_A = 0x00390007, .anim_B = 0x00390008, .anim_C = 0x00390001, .anim_D = 0x00390002, .anim_E = 0x00390002, .anim_F = 0x00390002 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_Clubba_ExtraAnimationList_80241B94_dgb_02,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_Clubba_Script_80241AB0_dgb_02 = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Call(RemoveNpc, -1)
    CaseEq(2)
        Call(SetNpcPos, -1, 0, -1000, 0)
        Call(OnPlayerFled, 1)
    CaseEq(3)
        Call(SetEnemyFlagBits, -1, 16, 1)
        Call(RemoveNpc, -1)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_imp_Clubba_Script_NpcAI_80241D34_dgb_02 = {
    Call(EnableNpcShadow, -1, 0)
    Call(SetSelfVar, 0, 4)
    Call(SetSelfVar, 1, 32)
    Call(SetSelfVar, 2, 50)
    Call(SetSelfVar, 3, 32)
    Call(SetSelfVar, 4, 3)
    Call(SetSelfVar, 15, 8389)
    Call(dgb_02_MeleeHitbox_Main)
    Return
    End
};

EvtScript TTYD64_imp_Clubba_Script_NpcAI_80241BCC_dgb_02 = {
    Call(SetSelfVar, 0, 0)
    Call(SetSelfVar, 1, 5)
    Call(SetSelfVar, 2, 8)
    Call(SetSelfVar, 3, 12)
    Call(dgb_02_WanderMeleeAI_Main, Ref(TTYD64_imp_Clubba_AISettings_80241B9C_dgb_02))
    Return
    End
};

MobileAISettings TTYD64_imp_Clubba_AISettings_80241B9C_dgb_02 = {
    .moveSpeed = 1.5f,
    .moveTime = 120,
    .waitTime = 30,
    .alertRadius = 85.0f,
    .alertOffsetDist = 65.0f,
    .playerSearchInterval = 5,
    .chaseSpeed = 3.5f,
    .chaseTurnRate = 90,
    .chaseUpdateInterval = 12,
    .chaseRadius = 110.0f,
    .chaseOffsetDist = 90.0f,
    .unk_AI_2C = 3,
};

NpcSettings TTYD64_imp_Clubba_NpcSettings_80241C3C_dgb_02 = {
    .defaultAnim = 0x00000000,
    .height = 36,
    .radius = 34,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Clubba_Script_NpcAI_80241BCC_dgb_02,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 13,
    .actionFlags = 0,
};

NpcSettings TTYD64_imp_Clubba_NpcSettings_80241DDC_dgb_02 = {
    .defaultAnim = 0x00000000,
    .height = 14,
    .radius = 18,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Clubba_Script_NpcAI_80241D34_dgb_02,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = TTYD64_imp_Clubba_Script_80241AB0_dgb_02,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 13,
    .actionFlags = 8,
};

AnimID TTYD64_imp_Clubba_ExtraAnimationList_80241B6C_dgb_02[] = {
    0x00390000, 0x00390002, 0x00390003, 0x00390004, 0x0039000C, 0x00390007, 0x00390008, 0x00390011, 0x00390012, -1
};

AnimID TTYD64_imp_Clubba_ExtraAnimationList_80241B94_dgb_02[] = {
    0x00390000, -1
};
// clang-format on

void TTYD64_tp_Install_imp_Clubba(void) {
}
