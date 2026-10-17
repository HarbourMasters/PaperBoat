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

extern NpcData TTYD64_imp_MontyMole_Npc_MontyMole[];
extern EvtScript TTYD64_imp_MontyMole_Script_NpcAI_80241C4C_iwa_03;
extern EvtScript TTYD64_imp_MontyMole_Script_80241B00_iwa_03;
extern EvtScript TTYD64_imp_MontyMole_Script_80241B9C_iwa_03;
extern MobileAISettings TTYD64_imp_MontyMole_AISettings_80241C1C_iwa_03;
extern NpcSettings TTYD64_imp_MontyMole_NpcSettings_80241EC4_iwa_03;
extern NpcSettings TTYD64_imp_MontyMole_NpcSettings_80241E98_iwa_03;

// clang-format off
NpcData TTYD64_imp_MontyMole_Npc_MontyMole[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_MontyMole_NpcSettings_80241E98_iwa_03,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x80, .itemDropChance = 16, .itemDrops = { { 164, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 40, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 250, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002F0019, .walk = 0x002F0002, .run = 0x002F0003, .chase = 0x002F0003, .anim_4 = 0x002F0019, .anim_5 = 0x002F0019, .death = 0x002F0009, .hit = 0x002F0009, .anim_8 = 0x002F0019, .anim_9 = 0x002F0019, .anim_A = 0x002F0019, .anim_B = 0x002F0019, .anim_C = 0x002F0019, .anim_D = 0x002F0019, .anim_E = 0x002F0019, .anim_F = 0x002F0019 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 1,
        .settings = &TTYD64_imp_MontyMole_NpcSettings_80241EC4_iwa_03,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000F21,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 1017, .centerPos.y = -23, .centerPos.z = 33, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 1017, .detectPos.y = -23, .detectPos.z = 33, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x002F0019, .walk = 0x002F0002, .run = 0x002F0003, .chase = 0x002F0003, .anim_4 = 0x002F0019, .anim_5 = 0x002F0019, .death = 0x002F0009, .hit = 0x002F0009, .anim_8 = 0x002F0019, .anim_9 = 0x002F0019, .anim_A = 0x002F0019, .anim_B = 0x002F0019, .anim_C = 0x002F0019, .anim_D = 0x002F0019, .anim_E = 0x002F0019, .anim_F = 0x002F0019 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_MontyMole_Script_NpcAI_80241C4C_iwa_03 = {
    Wait(5)
    Call(func_800445D4, LVar0)
    IfEq(LVar0, 100)
        Call(SetSelfEnemyFlagBits, 32, 1)
        Label(10)
        Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
        Call(IsPlayerWithin, LVar0, LVar2, 80, LVar3)
        IfNe(LVar3, 1)
            Wait(1)
            Goto(10)
        EndIf
        Call(GetSelfNpcID, LVar0)
        Add(LVar0, 1)
        Call(GetNpcPos, LVar0, LVar1, LVar2, LVar3)
        Add(LVar2, 30)
        Call(SetNpcPos, LVar0, LVar1, LVar2, LVar3)
        Wait(1)
        Call(SetNpcFlagBits, -1, 4, 0)
        Call(EnableNpcShadow, -1, 1)
        Call(SetNpcAnimation, -1, 0x2F000E)
        Call(GetNpcPos, -1, LVar4, LVar5, LVar6)
        Add(LVar5, 30)
        Call(SetNpcJumpscale, -1, Float(1.0))
        Call(PlaySoundAtNpc, -1, 803, 0)
        Call(NpcJump0, -1, LVar4, LVar5, LVar6, 20)
        Call(SetNpcPos, LVar0, 0, -1000, 0)
        Call(SetSelfEnemyFlagBits, 32, 0)
        Call(NpcFacePlayer, -1, 0)
        Call(SetSelfEnemyFlagBits, 0x40000000, 1)
        Call(BasicAI_Main, Ref(TTYD64_imp_MontyMole_AISettings_80241C1C_iwa_03))
    EndIf
    Return
    End
};

EvtScript TTYD64_imp_MontyMole_Script_80241B00_iwa_03 = {
    Call(EnableNpcShadow, -1, 0)
    Call(SetNpcFlagBits, -1, 4, 1)
    Call(SetNpcFlagBits, -1, 512, 1)
    Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
    Sub(LVar1, 30)
    Call(SetNpcPos, -1, LVar0, LVar1, LVar2)
    Return
    End
};

EvtScript TTYD64_imp_MontyMole_Script_80241B9C_iwa_03 = {
    Call(EnableNpcShadow, -1, 0)
    Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
    Sub(LVar1, 30)
    Call(SetNpcPos, -1, LVar0, LVar1, LVar2)
    Call(SetNpcAnimation, -1, 0x2F0012)
    Return
    End
};

MobileAISettings TTYD64_imp_MontyMole_AISettings_80241C1C_iwa_03 = {
    .moveSpeed = 1.79999995f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 90.0f,
    .alertOffsetDist = 70.0f,
    .playerSearchInterval = 2,
    .chaseSpeed = 3.0f,
    .chaseTurnRate = 90,
    .chaseUpdateInterval = 25,
    .chaseRadius = 120.0f,
    .chaseOffsetDist = 70.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_MontyMole_NpcSettings_80241EC4_iwa_03 = {
    .defaultAnim = 0x00000000,
    .height = 24,
    .radius = 22,
    .otherAI = TTYD64_imp_MontyMole_Script_80241B9C_iwa_03,
    .onInteract = NULL,
    .ai = NULL,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 8,
    .actionFlags = 1,
};

NpcSettings TTYD64_imp_MontyMole_NpcSettings_80241E98_iwa_03 = {
    .defaultAnim = 0x00000000,
    .height = 24,
    .radius = 22,
    .otherAI = TTYD64_imp_MontyMole_Script_80241B00_iwa_03,
    .onInteract = NULL,
    .ai = TTYD64_imp_MontyMole_Script_NpcAI_80241C4C_iwa_03,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 8,
    .actionFlags = 1,
};
// clang-format on

void TTYD64_tp_Install_imp_MontyMole(void) {
}
