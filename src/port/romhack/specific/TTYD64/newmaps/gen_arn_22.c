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
#include "port/romhack/specific/TTYD64/newmaps/nm.h"

API_CALLABLE(BasicAI_Main);
API_CALLABLE(BindNpcDefeat);
API_CALLABLE(DoNpcDefeat);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeNpcs);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcPos);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_arn_22_Script_Main;
extern NpcData TTYD64_arn_22_NpcGroup_Goomba3_1[];
extern NpcData TTYD64_arn_22_NpcGroup_Goomba2_2[];
extern NpcData TTYD64_arn_22_NpcGroup_Goomba2_1[];
extern NpcData TTYD64_arn_22_NpcGroup_Goomba1_2[];
extern NpcData TTYD64_arn_22_NpcGroup_Goomba1_1[];
extern NpcData TTYD64_arn_22_NpcGroup_Goomba3_2[];
extern EvtScript TTYD64_arn_22_Script_GoBack;
extern u8 TTYD64_arn_22_String_Tattle[];
extern EvtScript TTYD64_arn_22_Script_Exit3;
extern EvtScript TTYD64_arn_22_Script_CreateExitTriggers;
extern NpcGroupList TTYD64_arn_22_NpcGroupList_arn22;
extern EvtScript TTYD64_arn_22_Script_SetupMusic;
extern EntryList TTYD64_arn_22_EntryList;
extern MapSettings TTYD64_arn_22_Header;
extern EvtScript TTYD64_arn_22_Script_EnterMap;
extern MobileAISettings TTYD64_arn_22_AISettings_Goomba;
extern EvtScript TTYD64_arn_22_Script_Exit1;
extern EvtScript TTYD64_arn_22_Script_Exit0;
extern EvtScript TTYD64_arn_22_Script_Exit2;
extern NpcSettings TTYD64_arn_22_NpcSettings_Goomba;
extern EvtScript TTYD64_arn_22_Script_NPC_Init_Goomba;
extern EvtScript TTYD64_arn_22_Script_NpcAI_Goomba;
extern EvtScript TTYD64_arn_22_Script_NPC_Defeat_Goomba;

// clang-format off
static s32 TTYD64_arn_22_GetTattleMsg;

static s32 TTYD64_arn_22_GetTattle(void) {
    return TTYD64_arn_22_GetTattleMsg;
}

EvtScript TTYD64_arn_22_Script_Main = {
    Set(GameByte(425), 35)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_arn_22_NpcGroupList_arn22)
    Switch(AreaByte(0))
    CaseOrEq(1)
    CaseOrEq(2)
        Call(SetNpcPos, 3, 0, -4096, 0)
        Call(SetNpcPos, 4, 0, -4096, 0)
        Call(SetNpcPos, 5, 0, -4096, 0)
        Call(EnableNpcShadow, 3, 0)
        Call(EnableNpcShadow, 4, 0)
        Call(EnableNpcShadow, 5, 0)
        EndCaseGroup
    CaseOrEq(3)
    CaseOrEq(4)
    CaseOrEq(5)
        Call(SetNpcPos, 0, 0, -4096, 0)
        Call(SetNpcPos, 1, 0, -4096, 0)
        Call(SetNpcPos, 2, 0, -4096, 0)
        Call(EnableNpcShadow, 0, 0)
        Call(EnableNpcShadow, 1, 0)
        Call(EnableNpcShadow, 2, 0)
        EndCaseGroup
    EndSwitch
    Exec(TTYD64_arn_22_Script_SetupMusic)
    Exec(TTYD64_arn_22_Script_EnterMap)
    Return
    End
};

NpcData TTYD64_arn_22_NpcGroup_Goomba3_1[] = {
    {
        .id = 2,
        .settings = &TTYD64_arn_22_NpcSettings_Goomba,
        .pos = { 0.0f, 0.0f, 0.0f },
        .flags = 0x00000C00,
        .init = &TTYD64_arn_22_Script_NPC_Init_Goomba,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 32, .itemDrops = { { 141, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 20, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 150, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00260201, .walk = 0x00260202, .run = 0x00260203, .chase = 0x00260203, .anim_4 = 0x00260201, .anim_5 = 0x00260201, .death = 0x00260205, .hit = 0x00260205, .anim_8 = 0x00260203, .anim_9 = 0x00260203, .anim_A = 0x00260203, .anim_B = 0x00260203, .anim_C = 0x00260203, .anim_D = 0x00260203, .anim_E = 0x00260203, .anim_F = 0x00260203 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_arn_22_NpcGroup_Goomba2_2[] = {
    {
        .id = 4,
        .settings = &TTYD64_arn_22_NpcSettings_Goomba,
        .pos = { 124.0f, 220.0f, 0.0f },
        .flags = 0x00000C00,
        .init = &TTYD64_arn_22_Script_NPC_Init_Goomba,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 32, .itemDrops = { { 141, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 124, .centerPos.y = 220, .centerPos.z = 0, .wanderSize.x = 20, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 124, .detectPos.y = 220, .detectPos.z = 0, .detectSize.x = 150, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00260201, .walk = 0x00260202, .run = 0x00260203, .chase = 0x00260203, .anim_4 = 0x00260201, .anim_5 = 0x00260201, .death = 0x00260205, .hit = 0x00260205, .anim_8 = 0x00260203, .anim_9 = 0x00260203, .anim_A = 0x00260203, .anim_B = 0x00260203, .anim_C = 0x00260203, .anim_D = 0x00260203, .anim_E = 0x00260203, .anim_F = 0x00260203 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_arn_22_NpcGroup_Goomba2_1[] = {
    {
        .id = 1,
        .settings = &TTYD64_arn_22_NpcSettings_Goomba,
        .pos = { 124.0f, 220.0f, 0.0f },
        .flags = 0x00000C00,
        .init = &TTYD64_arn_22_Script_NPC_Init_Goomba,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 32, .itemDrops = { { 141, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 124, .centerPos.y = 220, .centerPos.z = 0, .wanderSize.x = 20, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 124, .detectPos.y = 220, .detectPos.z = 0, .detectSize.x = 150, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00260201, .walk = 0x00260202, .run = 0x00260203, .chase = 0x00260203, .anim_4 = 0x00260201, .anim_5 = 0x00260201, .death = 0x00260205, .hit = 0x00260205, .anim_8 = 0x00260203, .anim_9 = 0x00260203, .anim_A = 0x00260203, .anim_B = 0x00260203, .anim_C = 0x00260203, .anim_D = 0x00260203, .anim_E = 0x00260203, .anim_F = 0x00260203 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_arn_22_NpcGroup_Goomba1_2[] = {
    {
        .id = 3,
        .settings = &TTYD64_arn_22_NpcSettings_Goomba,
        .pos = { 13.0f, 444.0f, 0.0f },
        .flags = 0x00000C00,
        .init = &TTYD64_arn_22_Script_NPC_Init_Goomba,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 32, .itemDrops = { { 141, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 13, .centerPos.y = 444, .centerPos.z = 0, .wanderSize.x = 20, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 13, .detectPos.y = 444, .detectPos.z = 0, .detectSize.x = 150, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00260201, .walk = 0x00260202, .run = 0x00260203, .chase = 0x00260203, .anim_4 = 0x00260201, .anim_5 = 0x00260201, .death = 0x00260205, .hit = 0x00260205, .anim_8 = 0x00260203, .anim_9 = 0x00260203, .anim_A = 0x00260203, .anim_B = 0x00260203, .anim_C = 0x00260203, .anim_D = 0x00260203, .anim_E = 0x00260203, .anim_F = 0x00260203 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_arn_22_NpcGroup_Goomba1_1[] = {
    {
        .id = 0,
        .settings = &TTYD64_arn_22_NpcSettings_Goomba,
        .pos = { 13.0f, 444.0f, 0.0f },
        .flags = 0x00000C00,
        .init = &TTYD64_arn_22_Script_NPC_Init_Goomba,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 32, .itemDrops = { { 141, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 13, .centerPos.y = 444, .centerPos.z = 0, .wanderSize.x = 20, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 13, .detectPos.y = 444, .detectPos.z = 0, .detectSize.x = 150, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00260201, .walk = 0x00260202, .run = 0x00260203, .chase = 0x00260203, .anim_4 = 0x00260201, .anim_5 = 0x00260201, .death = 0x00260205, .hit = 0x00260205, .anim_8 = 0x00260203, .anim_9 = 0x00260203, .anim_A = 0x00260203, .anim_B = 0x00260203, .anim_C = 0x00260203, .anim_D = 0x00260203, .anim_E = 0x00260203, .anim_F = 0x00260203 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_arn_22_NpcGroup_Goomba3_2[] = {
    {
        .id = 5,
        .settings = &TTYD64_arn_22_NpcSettings_Goomba,
        .pos = { 0.0f, 0.0f, 0.0f },
        .flags = 0x00000C00,
        .init = &TTYD64_arn_22_Script_NPC_Init_Goomba,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 32, .itemDrops = { { 141, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 20, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 150, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00260201, .walk = 0x00260202, .run = 0x00260203, .chase = 0x00260203, .anim_4 = 0x00260201, .anim_5 = 0x00260201, .death = 0x00260205, .hit = 0x00260205, .anim_8 = 0x00260203, .anim_9 = 0x00260203, .anim_A = 0x00260203, .anim_B = 0x00260203, .anim_C = 0x00260203, .anim_D = 0x00260203, .anim_E = 0x00260203, .anim_F = 0x00260203 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_arn_22_Script_GoBack = {
    Call(UseExitHeading, 60, LVar0)
    Exec(ExitWalk)
    Switch(AreaByte(0))
    CaseEq(1)
        Call(GotoMap, (Bytecode) "arn_21", 1)
    CaseEq(2)
        Call(GotoMap, (Bytecode) "arn_21", 2)
    CaseEq(3)
        Call(GotoMap, (Bytecode) "arn_23", 1)
    CaseEq(4)
        Call(GotoMap, (Bytecode) "arn_23", 2)
    CaseEq(5)
        Call(GotoMap, (Bytecode) "arn_23", 3)
    EndSwitch
    Wait(100)
    Return
    End
};

u8 TTYD64_arn_22_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x29, 0x54, 0xF7, 0x53, 0x45, 0x45, 0x4D, 0x53,
    0xF7, 0x4C, 0x49, 0x4B, 0x45, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7, 0x49,
    0x53, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0xF7, 0x4B, 0x49, 0x4E, 0x44, 0xF0,
    0x4F, 0x46, 0xF7, 0x4C, 0x41, 0x42, 0x59, 0x52, 0x49, 0x4E, 0x54, 0x48,
    0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0E, 0xF0, 0xF1, 0xFB, 0x37, 0x45,
    0xF7, 0x4E, 0x45, 0x45, 0x44, 0xF7, 0x54, 0x4F, 0xF7, 0x4B, 0x45, 0x45,
    0x50, 0xF7, 0x4F, 0x55, 0x52, 0xF7, 0x45, 0x59, 0x45, 0x53, 0xF7, 0x4F,
    0x50, 0x45, 0x4E, 0xF0, 0x41, 0x54, 0xF7, 0x41, 0x4C, 0x4C, 0xF7, 0x43,
    0x4F, 0x53, 0x54, 0x53, 0xF7, 0x49, 0x46, 0xF7, 0x57, 0x45, 0xF7, 0x44,
    0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x57, 0x41, 0x4E, 0x54, 0xF0, 0x54, 0x4F,
    0xF7, 0x47, 0x45, 0x54, 0xF7, 0x4C, 0x4F, 0x53, 0x54, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_arn_22_Script_Exit3 = {
    Call(UseExitHeading, 60, 3)
    Exec(ExitWalk)
    IfEq(AreaByte(0), 2)
        Call(GotoMap, (Bytecode) "arn_23", 0)
    Else
        Call(GotoMap, (Bytecode) "arn_24", 0)
    EndIf
    Wait(100)
    Return
    End
};

EvtScript TTYD64_arn_22_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_arn_22_Script_Exit0, 0x80000, 3, 1, 0)
    BindTrigger(TTYD64_arn_22_Script_Exit1, 0x80000, 8, 1, 0)
    BindTrigger(TTYD64_arn_22_Script_Exit2, 0x80000, 13, 1, 0)
    BindTrigger(TTYD64_arn_22_Script_Exit3, 0x80000, 14, 1, 0)
    Return
    End
};

NpcGroupList TTYD64_arn_22_NpcGroupList_arn22 = {
    { .npcCount = 1, .npcs = TTYD64_arn_22_NpcGroup_Goomba1_1, .battle = 0x0E00, .stage = 7 },
    { .npcCount = 1, .npcs = TTYD64_arn_22_NpcGroup_Goomba2_1, .battle = 0x0E00, .stage = 7 },
    { .npcCount = 1, .npcs = TTYD64_arn_22_NpcGroup_Goomba3_1, .battle = 0x0E00, .stage = 7 },
    { .npcCount = 1, .npcs = TTYD64_arn_22_NpcGroup_Goomba1_2, .battle = 0x0E00, .stage = 7 },
    { .npcCount = 1, .npcs = TTYD64_arn_22_NpcGroup_Goomba2_2, .battle = 0x0E00, .stage = 7 },
    { .npcCount = 1, .npcs = TTYD64_arn_22_NpcGroup_Goomba3_2, .battle = 0x0E00, .stage = 7 },
    {},
};

EvtScript TTYD64_arn_22_Script_SetupMusic = {
    Switch(GameByte(0))
    CaseDefault
        Call(SetMusic, 0, 29, 0, 8)
    EndSwitch
    Return
    End
};

EntryList TTYD64_arn_22_EntryList = {
    { -225.0f, 444.0f, 0.0f, 90.0f },
    { -225.0f, 220.0f, 0.0f, 90.0f },
    { -225.0f, 0.0f, 0.0f, 90.0f },
    { 225.0f, 0.0f, 0.0f, 270.0f },
};

MapSettings TTYD64_arn_22_Header = {
    .main = &TTYD64_arn_22_Script_Main,
    .entryList = &TTYD64_arn_22_EntryList,
    .entryCount = 4,
    .background = NULL,
    .tattle = { .get = TTYD64_arn_22_GetTattle },
};

EvtScript TTYD64_arn_22_Script_EnterMap = {
    Set(LVar0, (Bytecode) TTYD64_arn_22_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};

MobileAISettings TTYD64_arn_22_AISettings_Goomba = {
    .moveSpeed = 1.79999995f,
    .moveTime = 40,
    .waitTime = 15,
    .alertRadius = 150.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 2,
    .chaseSpeed = 3.29999995f,
    .chaseTurnRate = 70,
    .chaseUpdateInterval = 1,
    .chaseRadius = 180.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

EvtScript TTYD64_arn_22_Script_Exit1 = {
    Set(LVar0, 1)
    ExecWait(TTYD64_arn_22_Script_GoBack)
    Return
    End
};

EvtScript TTYD64_arn_22_Script_Exit0 = {
    Set(LVar0, 0)
    ExecWait(TTYD64_arn_22_Script_GoBack)
    Return
    End
};

EvtScript TTYD64_arn_22_Script_Exit2 = {
    Set(LVar0, 2)
    ExecWait(TTYD64_arn_22_Script_GoBack)
    Return
    End
};

NpcSettings TTYD64_arn_22_NpcSettings_Goomba = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 23,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = &TTYD64_arn_22_Script_NpcAI_Goomba,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 12,
    .actionFlags = 0,
};

EvtScript TTYD64_arn_22_Script_NPC_Init_Goomba = {
    Call(BindNpcDefeat, -1, (Bytecode) TTYD64_arn_22_Script_NPC_Defeat_Goomba)
    Return
    End
};

EvtScript TTYD64_arn_22_Script_NpcAI_Goomba = {
    Call(BasicAI_Main, Ref(TTYD64_arn_22_AISettings_Goomba))
    Return
    End
};

EvtScript TTYD64_arn_22_Script_NPC_Defeat_Goomba = {
    Call(DoNpcDefeat)
    Return
    End
};

MapConfig TTYD64_mapcfg_arn_22 = {
    .id = "arn_22",
    .settings = &TTYD64_arn_22_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 1,
};
// clang-format on

void TTYD64_nm_Install_arn_22(void) {
    TTYD64_arn_22_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_arn_22_String_Tattle);
}
