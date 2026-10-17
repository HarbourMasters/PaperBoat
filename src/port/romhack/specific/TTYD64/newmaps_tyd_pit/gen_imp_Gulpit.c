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

API_CALLABLE(sam_03_MeleeHitbox_Main);
API_CALLABLE(sam_03_WanderMeleeAI_Main);

extern NpcData TTYD64_imp_Gulpit_Npc_Gulpit[];
extern EvtScript TTYD64_imp_Gulpit_Script_802418F0_sam_03;
extern EvtScript TTYD64_imp_Gulpit_Script_NpcAI_80241A78_sam_03;
extern EvtScript TTYD64_imp_Gulpit_Script_NpcAI_802419DC_sam_03;
extern MobileAISettings TTYD64_imp_Gulpit_AISettings_802419AC_sam_03;
extern NpcSettings TTYD64_imp_Gulpit_NpcSettings_80241B20_sam_03;
extern NpcSettings TTYD64_imp_Gulpit_NpcSettings_80241A4C_sam_03;
extern AnimID TTYD64_imp_Gulpit_ExtraAnimationList_80241B54_sam_03[];
extern AnimID TTYD64_imp_Gulpit_ExtraAnimationList_80241B4C_sam_03[];

// clang-format off
NpcData TTYD64_imp_Gulpit_Npc_Gulpit[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_Gulpit_NpcSettings_80241A4C_sam_03,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 133, 2, 0 }, { 140, 8, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 1, .maxCoinBonus = 4, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 250, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00520001, .walk = 0x00520002, .run = 0x00520003, .chase = 0x00520003, .anim_4 = 0x00520001, .anim_5 = 0x00520001, .death = 0x0052000B, .hit = 0x0052000B, .anim_8 = 0x00520004, .anim_9 = 0x00520004, .anim_A = 0x00520001, .anim_B = 0x00520001, .anim_C = 0x00520001, .anim_D = 0x00520001, .anim_E = 0x00520001, .anim_F = 0x00520001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_Gulpit_ExtraAnimationList_80241B54_sam_03,
        .tattle = 0,
    },
    {
        .id = 1,
        .settings = &TTYD64_imp_Gulpit_NpcSettings_80241B20_sam_03,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800D00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00520001, .walk = 0x00520002, .run = 0x00520003, .chase = 0x00520003, .anim_4 = 0x00520001, .anim_5 = 0x00520001, .death = 0x0052000B, .hit = 0x0052000B, .anim_8 = 0x00520004, .anim_9 = 0x00520004, .anim_A = 0x00520001, .anim_B = 0x00520001, .anim_C = 0x00520001, .anim_D = 0x00520001, .anim_E = 0x00520001, .anim_F = 0x00520001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_Gulpit_ExtraAnimationList_80241B4C_sam_03,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_Gulpit_Script_802418F0_sam_03 = {
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

EvtScript TTYD64_imp_Gulpit_Script_NpcAI_80241A78_sam_03 = {
    Call(EnableNpcShadow, -1, 0)
    Call(SetSelfVar, 0, 6)
    Call(SetSelfVar, 1, 28)
    Call(SetSelfVar, 2, 55)
    Call(SetSelfVar, 3, 32)
    Call(SetSelfVar, 4, 10)
    Call(SetSelfVar, 15, 0)
    Call(sam_03_MeleeHitbox_Main)
    Return
    End
};

EvtScript TTYD64_imp_Gulpit_Script_NpcAI_802419DC_sam_03 = {
    Call(SetSelfVar, 0, 0)
    Call(SetSelfVar, 1, 5)
    Call(SetSelfVar, 2, 13)
    Call(SetSelfVar, 3, 30)
    Call(sam_03_WanderMeleeAI_Main, Ref(TTYD64_imp_Gulpit_AISettings_802419AC_sam_03))
    Return
    End
};

MobileAISettings TTYD64_imp_Gulpit_AISettings_802419AC_sam_03 = {
    .moveSpeed = 0.5f,
    .moveTime = 60,
    .waitTime = 15,
    .alertRadius = 100.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 10,
    .chaseSpeed = 3.5f,
    .chaseTurnRate = 180,
    .chaseUpdateInterval = 20,
    .chaseRadius = 150.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_imp_Gulpit_NpcSettings_80241B20_sam_03 = {
    .defaultAnim = 0x00000000,
    .height = 32,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Gulpit_Script_NpcAI_80241A78_sam_03,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = TTYD64_imp_Gulpit_Script_802418F0_sam_03,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 22,
    .actionFlags = 8,
};

NpcSettings TTYD64_imp_Gulpit_NpcSettings_80241A4C_sam_03 = {
    .defaultAnim = 0x00000000,
    .height = 48,
    .radius = 36,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Gulpit_Script_NpcAI_802419DC_sam_03,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 22,
    .actionFlags = 0,
};

AnimID TTYD64_imp_Gulpit_ExtraAnimationList_80241B54_sam_03[] = {
    0x00520000, 0x00520001, 0x0052000B, 0x00520004, 0x00520002, 0x00520003, -1
};

AnimID TTYD64_imp_Gulpit_ExtraAnimationList_80241B4C_sam_03[] = {
    0x00520000, -1
};
// clang-format on

void TTYD64_tp_Install_imp_Gulpit(void) {
}
