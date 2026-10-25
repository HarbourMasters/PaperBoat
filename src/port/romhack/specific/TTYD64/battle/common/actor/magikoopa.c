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

API_CALLABLE(kpa_03_MagikoopaAI_Main);
API_CALLABLE(kpa_03_MagikoopaAI_OnHit);
API_CALLABLE(kpa_03_MagikoopaAI_OnHitInit);
API_CALLABLE(kpa_03_MagikoopaAI_OnPlayerFled);
API_CALLABLE(kpa_03_MagikoopaAI_OnPlayerWon);
API_CALLABLE(kpa_03_MagikoopaAI_SpellMain);

extern NpcData TTYD64_imp_Magikoopa_Npc_DarkMagikoopa[];
extern EvtScript TTYD64_imp_Magikoopa_Script_802428EC_kpa_03;
extern EvtScript TTYD64_imp_Magikoopa_Script_802426B4_kpa_03;
extern EvtScript TTYD64_imp_Magikoopa_Script_80242740_kpa_03;
extern EvtScript TTYD64_imp_Magikoopa_Script_80242898_kpa_03;
extern EvtScript TTYD64_imp_Magikoopa_Script_8024280C_kpa_03;
extern MobileAISettings TTYD64_imp_Magikoopa_AISettings_80242664_kpa_03;
extern NpcSettings TTYD64_imp_Magikoopa_NpcSettings_802429A8_kpa_03;
extern NpcSettings TTYD64_imp_Magikoopa_NpcSettings_802427C0_kpa_03;
extern AnimID TTYD64_imp_Magikoopa_ExtraAnimationList_802427EC_kpa_03[];
extern EvtScript TTYD64_imp_Magikoopa_Script_NpcAI_80242694_kpa_03;
extern EvtScript TTYD64_imp_Magikoopa_Script_NpcAI_8024287C_kpa_03;

// clang-format off
NpcData TTYD64_imp_Magikoopa_Npc_DarkMagikoopa[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_Magikoopa_NpcSettings_802427C0_kpa_03,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 140, 5, 0 }, { 163, 5, 0 }, { 130, 5, 0 }, { 146, 5, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 5, 13106 }, { 9830, 13106, 5, 13106 }, { 16383, 13106, 5, 13106 }, { 26213, 13106, 5, 13106 }, { 32767, 9830, 5, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 1, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 220, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00560601, .walk = 0x00560601, .run = 0x00560601, .chase = 0x00560601, .anim_4 = 0x00560601, .anim_5 = 0x00560601, .death = 0x00560604, .hit = 0x00560604, .anim_8 = 0x00560602, .anim_9 = 0x00560603, .anim_A = 0x00560601, .anim_B = 0x00560601, .anim_C = 0x00560601, .anim_D = 0x00560601, .anim_E = 0x00560601, .anim_F = 0x00560601 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_Magikoopa_ExtraAnimationList_802427EC_kpa_03,
        .tattle = 0,
    },
    {
        .id = 1,
        .settings = &TTYD64_imp_Magikoopa_NpcSettings_802429A8_kpa_03,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800D00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00560600, .walk = 0x00560600, .run = 0x00560600, .chase = 0x00560600, .anim_4 = 0x00560600, .anim_5 = 0x00560600, .death = 0x00560600, .hit = 0x00560600, .anim_8 = 0x00560600, .anim_9 = 0x00560600, .anim_A = 0x00560600, .anim_B = 0x00560600, .anim_C = 0x00560600, .anim_D = 0x00560600, .anim_E = 0x00560600, .anim_F = 0x00560600 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_Magikoopa_Script_802428EC_kpa_03 = {
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

EvtScript TTYD64_imp_Magikoopa_Script_802426B4_kpa_03 = {
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
    CaseEq(1)
    CaseOrEq(2)
    CaseOrEq(4)
    CaseOrEq(6)
        Call(GetSelfAnimationFromTable, 7, LVar0)
        ExecWait(EVS_NpcHitRecoil)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_imp_Magikoopa_Script_80242740_kpa_03 = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Call(kpa_03_MagikoopaAI_OnPlayerWon)
        Call(DoNpcDefeat)
    CaseEq(2)
        Call(kpa_03_MagikoopaAI_OnPlayerFled)
        Call(OnPlayerFled, 0)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_imp_Magikoopa_Script_80242898_kpa_03 = {
    Call(kpa_03_MagikoopaAI_OnHitInit)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(kpa_03_MagikoopaAI_OnHit)
    Exec(EnemyNpcHit)
    Return
    End
};

EvtScript TTYD64_imp_Magikoopa_Script_8024280C_kpa_03 = {
    Call(SetSelfVar, 1, 10)
    Call(SetSelfVar, 2, 40)
    Return
    End
};

MobileAISettings TTYD64_imp_Magikoopa_AISettings_80242664_kpa_03 = {
    .moveSpeed = 1.0f,
    .moveTime = 120,
    .waitTime = 30,
    .alertRadius = 100.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 10,
    .chaseSpeed = 3.0f,
    .chaseTurnRate = 90,
    .chaseUpdateInterval = 15,
    .chaseRadius = 200.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_Magikoopa_NpcSettings_802429A8_kpa_03 = {
    .defaultAnim = 0x00560000,
    .height = 0,
    .radius = 0,
    .otherAI = TTYD64_imp_Magikoopa_Script_8024280C_kpa_03,
    .onInteract = NULL,
    .ai = TTYD64_imp_Magikoopa_Script_NpcAI_8024287C_kpa_03,
    .onHit = TTYD64_imp_Magikoopa_Script_80242898_kpa_03,
    .aux = NULL,
    .onDefeat = TTYD64_imp_Magikoopa_Script_802428EC_kpa_03,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 0,
    .actionFlags = 0,
};

NpcSettings TTYD64_imp_Magikoopa_NpcSettings_802427C0_kpa_03 = {
    .defaultAnim = 0x00000000,
    .height = 32,
    .radius = 28,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Magikoopa_Script_NpcAI_80242694_kpa_03,
    .onHit = TTYD64_imp_Magikoopa_Script_802426B4_kpa_03,
    .aux = NULL,
    .onDefeat = TTYD64_imp_Magikoopa_Script_80242740_kpa_03,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 26,
    .actionFlags = 0,
};

AnimID TTYD64_imp_Magikoopa_ExtraAnimationList_802427EC_kpa_03[] = {
    0x00560600, 0x00560601, 0x00560601, 0x00560601, 0x00560602, 0x00560603, 0x00560604, -1
};

EvtScript TTYD64_imp_Magikoopa_Script_NpcAI_80242694_kpa_03 = {
    Call(kpa_03_MagikoopaAI_Main, Ref(TTYD64_imp_Magikoopa_AISettings_80242664_kpa_03))
    Return
    End
};

EvtScript TTYD64_imp_Magikoopa_Script_NpcAI_8024287C_kpa_03 = {
    Call(kpa_03_MagikoopaAI_SpellMain)
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_Magikoopa(void) {
}
