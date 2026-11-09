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

extern EvtScript TTYD64_imp_Pit_Script_ShowPipe;

API_CALLABLE(isk_05_StoneChompAI_Main);

extern NpcData TTYD64_imp_StoneChomp_Npc_StoneChomp[];
extern EvtScript TTYD64_imp_StoneChomp_Script_80242578_isk_05_Pit;
extern EvtScript TTYD64_imp_StoneChomp_Script_Init_Chomp;
extern EvtScript TTYD64_imp_StoneChomp_Script_EnemyAI;
extern MobileAISettings TTYD64_imp_StoneChomp_AISettings_Enemy;
extern NpcSettings TTYD64_imp_StoneChomp_NpcSettings_802425E8_isk_05_Pit;
extern EvtScript TTYD64_imp_StoneChomp_Script_ChompIdle;

// clang-format off
NpcData TTYD64_imp_StoneChomp_Npc_StoneChomp[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_StoneChomp_NpcSettings_802425E8_isk_05_Pit,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00040B00,
        .init = TTYD64_imp_StoneChomp_Script_Init_Chomp,
        .initVarCount = 1,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 164, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 26213, 3, 16383 }, { 9830, 22936, 3, 16383 }, { 16383, 19660, 3, 13106 }, { 26213, 16383, 3, 13106 }, { 32767, 13106, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 70, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 250, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00350001, .walk = 0x00350005, .run = 0x00350004, .chase = 0x00350004, .anim_4 = 0x00350001, .anim_5 = 0x00350001, .death = 0x00350006, .hit = 0x00350006, .anim_8 = 0x00350000, .anim_9 = 0x00350000, .anim_A = 0x00350000, .anim_B = 0x00350000, .anim_C = 0x00350000, .anim_D = 0x00350000, .anim_E = 0x00350000, .anim_F = 0x00350000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_StoneChomp_Script_80242578_isk_05_Pit = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Thread
            Wait(10)
            Exec(TTYD64_imp_Pit_Script_ShowPipe)
        EndThread
        Call(DoNpcDefeat)
    CaseEq(1)
    CaseEq(2)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_imp_StoneChomp_Script_Init_Chomp = {
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_imp_StoneChomp_Script_ChompIdle)
    Call(BindNpcDefeat, -1, (Bytecode) TTYD64_imp_StoneChomp_Script_80242578_isk_05_Pit)
    Return
    End
};

EvtScript TTYD64_imp_StoneChomp_Script_EnemyAI = {
    Call(GetSelfVar, 0, LVar0)
    Call(isk_05_StoneChompAI_Main, Ref(TTYD64_imp_StoneChomp_AISettings_Enemy))
    Return
    End
};

MobileAISettings TTYD64_imp_StoneChomp_AISettings_Enemy = {
    .moveSpeed = 2.0f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 100.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 10,
    .chaseSpeed = 5.0f,
    .chaseTurnRate = 70,
    .chaseUpdateInterval = 10,
    .chaseRadius = 500.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_StoneChomp_NpcSettings_802425E8_isk_05_Pit = {
    .defaultAnim = 0x00000000,
    .height = 32,
    .radius = 32,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_StoneChomp_Script_EnemyAI,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 14,
    .actionFlags = 0,
};

EvtScript TTYD64_imp_StoneChomp_Script_ChompIdle = {
    Call(BindNpcAI, -1, (Bytecode) TTYD64_imp_StoneChomp_Script_EnemyAI)
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_StoneChomp(void) {
}
