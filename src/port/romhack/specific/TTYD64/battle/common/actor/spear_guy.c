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

API_CALLABLE(jan_06_MeleeHitbox_Main);
API_CALLABLE(jan_06_SpearGuyAI_Main);

extern NpcData TTYD64_imp_SpearGuy_Npc_SpearGuy[];
extern EvtScript TTYD64_imp_SpearGuy_Script_80244FEC_jan_06;
extern EvtScript TTYD64_imp_SpearGuy_Script_NpcAI_80245174_jan_06;
extern EvtScript TTYD64_imp_SpearGuy_Script_NpcAI_802450D8_jan_06;
extern AnimID TTYD64_imp_SpearGuy_ExtraAnimationList_8024544C_jan_06[];
extern MobileAISettings TTYD64_imp_SpearGuy_AISettings_802450A8_jan_06;
extern NpcSettings TTYD64_imp_SpearGuy_NpcSettings_8024521C_jan_06;
extern NpcSettings TTYD64_imp_SpearGuy_NpcSettings_80245148_jan_06;
extern AnimID TTYD64_imp_SpearGuy_ExtraAnimationList_80244FE4_jan_06[];

// clang-format off
NpcData TTYD64_imp_SpearGuy_Npc_SpearGuy[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_SpearGuy_NpcSettings_80245148_jan_06,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00400400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 143, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 150, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00420003, .walk = 0x00420005, .run = 0x00420006, .chase = 0x00420006, .anim_4 = 0x00420003, .anim_5 = 0x00420003, .death = 0x00420007, .hit = 0x00420007, .anim_8 = 0x0042001A, .anim_9 = 0x0042001B, .anim_A = 0x00420003, .anim_B = 0x00420003, .anim_C = 0x00420003, .anim_D = 0x00420003, .anim_E = 0x00420003, .anim_F = 0x00420003 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_SpearGuy_ExtraAnimationList_8024544C_jan_06,
        .tattle = 0,
    },
    {
        .id = 1,
        .settings = &TTYD64_imp_SpearGuy_NpcSettings_8024521C_jan_06,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800D00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00420003, .walk = 0x00420005, .run = 0x00420006, .chase = 0x00420006, .anim_4 = 0x00420003, .anim_5 = 0x00420003, .death = 0x00420007, .hit = 0x00420007, .anim_8 = 0x0042001A, .anim_9 = 0x0042001B, .anim_A = 0x00420003, .anim_B = 0x00420003, .anim_C = 0x00420003, .anim_D = 0x00420003, .anim_E = 0x00420003, .anim_F = 0x00420003 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_SpearGuy_ExtraAnimationList_80244FE4_jan_06,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_SpearGuy_Script_80244FEC_jan_06 = {
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

EvtScript TTYD64_imp_SpearGuy_Script_NpcAI_80245174_jan_06 = {
    Call(EnableNpcShadow, -1, 0)
    Call(SetSelfVar, 0, 4)
    Call(SetSelfVar, 1, 22)
    Call(SetSelfVar, 2, 40)
    Call(SetSelfVar, 3, 28)
    Call(SetSelfVar, 4, 1)
    Call(SetSelfVar, 15, 0)
    Call(jan_06_MeleeHitbox_Main)
    Return
    End
};

EvtScript TTYD64_imp_SpearGuy_Script_NpcAI_802450D8_jan_06 = {
    Call(SetSelfVar, 0, 0)
    Call(SetSelfVar, 1, 5)
    Call(SetSelfVar, 2, 12)
    Call(SetSelfVar, 3, 9)
    Call(jan_06_SpearGuyAI_Main, Ref(TTYD64_imp_SpearGuy_AISettings_802450A8_jan_06))
    Return
    End
};

AnimID TTYD64_imp_SpearGuy_ExtraAnimationList_8024544C_jan_06[] = {
    0x00420003, 0x00420004, 0x00420005, 0x00420006, 0x0042000F, 0x00420010, 0x00420007, 0x00420008, 0x00420009, 0x0042000D, 0x0042001A, 0x0042001B, -1
};

MobileAISettings TTYD64_imp_SpearGuy_AISettings_802450A8_jan_06 = {
    .moveSpeed = 1.70000005f,
    .moveTime = 100,
    .waitTime = 1,
    .alertRadius = 100.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 3.5f,
    .chaseTurnRate = 20,
    .chaseUpdateInterval = 1,
    .chaseRadius = 120.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_SpearGuy_NpcSettings_8024521C_jan_06 = {
    .defaultAnim = 0x00000000,
    .height = 8,
    .radius = 20,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_SpearGuy_Script_NpcAI_80245174_jan_06,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = TTYD64_imp_SpearGuy_Script_80244FEC_jan_06,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 16,
    .actionFlags = 8,
};

NpcSettings TTYD64_imp_SpearGuy_NpcSettings_80245148_jan_06 = {
    .defaultAnim = 0x00000000,
    .height = 23,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_SpearGuy_Script_NpcAI_802450D8_jan_06,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 16,
    .actionFlags = 0,
};

AnimID TTYD64_imp_SpearGuy_ExtraAnimationList_80244FE4_jan_06[] = {
    0x00420000, -1
};
// clang-format on

void TTYD64_tp_Install_imp_SpearGuy(void) {
}
