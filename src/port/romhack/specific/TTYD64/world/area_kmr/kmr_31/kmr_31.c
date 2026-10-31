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
#include "port/romhack/specific/TTYD64/world/newmaps.h"

API_CALLABLE(CloseMessage);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(GotoMapSpecial);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(PlaySound);
API_CALLABLE(RotateGroup);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(ShowChoice);
API_CALLABLE(ShowMessageAtScreenPos);
API_CALLABLE(SwitchMessage);
API_CALLABLE(UpdateLerp);

extern NpcData TTYD64_kmr_31_NpcGroup_InitPlaythrough[];
extern EvtScript TTYD64_kmr_31_Script_Difficulty_InputsStep;
extern EvtScript TTYD64_kmr_31_Script_Start_InputsStep;
extern EvtScript TTYD64_kmr_31_Script_Mode_InputsStep;
extern EvtScript TTYD64_kmr_31_Script_Confirm_InputsStep;
extern EvtScript TTYD64_kmr_31_Script_InitPlaythough_Inputs_Step;
extern EvtScript TTYD64_kmr_31_Script_UpdateCursorPos;
extern EvtScript TTYD64_kmr_31_Script_Start_UpdateSprite;
extern EvtScript TTYD64_kmr_31_Script_InitPlaythough_Step;
extern EvtScript TTYD64_kmr_31_Script_WelcomeMessage;
extern EvtScript TTYD64_kmr_31_Script_Mode_UpdateSprite;
extern EvtScript TTYD64_kmr_31_Script_Difficulty_UpdateSprite;
extern EvtScript TTYD64_kmr_31_Script_UpdateString;
extern EvtScript TTYD64_kmr_31_Script_Main;
extern u8 TTYD64_kmr_31_String_MQ_Confirmation[];
extern EvtScript TTYD64_kmr_31_Script_CloseDoor;
extern EvtScript TTYD64_kmr_31_Script_OpenDoor;
extern EvtScript TTYD64_kmr_31_Script_SetNpcs;
extern u8 TTYD64_kmr_31_String_Welcome[];
extern u8 TTYD64_kmr_31_String_Mode_Rando[];
extern u8 TTYD64_kmr_31_String_Mode_Bow[];
extern u8 TTYD64_kmr_31_String_Prologue[];
extern MapSettings TTYD64_kmr_31_Header;
extern u8 TTYD64_kmr_31_String_Difficulty_Hard_Description[];
s32 TTYD64_kmr_31_Function_Init(void);
extern u8 TTYD64_kmr_31_String_Difficulty_Normal_Description[];
extern u8 TTYD64_kmr_31_String_Start_Goomba[];
extern u8 TTYD64_kmr_31_String_Difficulty_MQ_Description[];
extern u8 TTYD64_kmr_31_String_Mode[];
extern u8 TTYD64_kmr_31_String_Start_JrTroopa[];
extern u8 TTYD64_kmr_31_String_Confirmation[];
extern NpcSettings TTYD64_kmr_31_NpcSettings_Generic;
extern u8 TTYD64_kmr_31_String_Mode_Original[];
extern u8 TTYD64_kmr_31_String_Start_Original[];
extern u8 TTYD64_kmr_31_String_Difficulty_Easy_Description[];
extern u8 TTYD64_kmr_31_String_Difficulty[];
extern NpcGroupList TTYD64_kmr_31_NpcGroupList;
extern EntryList TTYD64_kmr_31_EntryList;
extern u8 TTYD64_kmr_31_String_Difficulty_MQ_Title[];
extern EvtScript TTYD64_kmr_31_Script_Init_NoShadow;
extern u8 TTYD64_kmr_31_String_Difficulty_Normal_Title[];
extern u8 TTYD64_kmr_31_String_Difficulty_Hard_Title[];
extern u8 TTYD64_kmr_31_String_Difficulty_Easy_Title[];
extern u8 TTYD64_kmr_31_String_Empty[];

// clang-format off
NpcData TTYD64_kmr_31_NpcGroup_InitPlaythrough[] = {
    {
        .id = 1,
        .settings = &TTYD64_kmr_31_NpcSettings_Generic,
        .pos = { 104.0f, 30.0f, -21.0f },
        .flags = 0x00A40D20,
        .init = &TTYD64_kmr_31_Script_Init_NoShadow,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00E60000, .walk = 0x00E60000, .run = 0x00E60000, .chase = 0x00E60000, .anim_4 = 0x00E60000, .anim_5 = 0x00E60000, .death = 0x00E60000, .hit = 0x00E60000, .anim_8 = 0x00E60000, .anim_9 = 0x00E60000, .anim_A = 0x00E60000, .anim_B = 0x00E60000, .anim_C = 0x00E60000, .anim_D = 0x00E60000, .anim_E = 0x00E60000, .anim_F = 0x00E60000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 2,
        .settings = &TTYD64_kmr_31_NpcSettings_Generic,
        .pos = { 181.0f, 32.0f, -117.0f },
        .flags = 0x00A40D20,
        .init = &TTYD64_kmr_31_Script_Init_NoShadow,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00820001, .walk = 0x00820000, .run = 0x00820000, .chase = 0x00820000, .anim_4 = 0x00820000, .anim_5 = 0x00820000, .death = 0x00820000, .hit = 0x00820000, .anim_8 = 0x00820000, .anim_9 = 0x00820000, .anim_A = 0x00820000, .anim_B = 0x00820000, .anim_C = 0x00820000, .anim_D = 0x00820000, .anim_E = 0x00820000, .anim_F = 0x00820000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 3,
        .settings = &TTYD64_kmr_31_NpcSettings_Generic,
        .pos = { 181.0f, 32.0f, -117.0f },
        .flags = 0x00A40D20,
        .init = &TTYD64_kmr_31_Script_Init_NoShadow,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00A00001, .walk = 0x00A00000, .run = 0x00A00000, .chase = 0x00A00000, .anim_4 = 0x00A00000, .anim_5 = 0x00A00000, .death = 0x00A00000, .hit = 0x00A00000, .anim_8 = 0x00A00000, .anim_9 = 0x00A00000, .anim_A = 0x00A00000, .anim_B = 0x00A00000, .anim_C = 0x00A00000, .anim_D = 0x00A00000, .anim_E = 0x00A00000, .anim_F = 0x00A00000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 4,
        .settings = &TTYD64_kmr_31_NpcSettings_Generic,
        .pos = { 181.0f, 32.0f, -117.0f },
        .flags = 0x00A40D20,
        .init = &TTYD64_kmr_31_Script_Init_NoShadow,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00210003, .walk = 0x00210000, .run = 0x00210000, .chase = 0x00210000, .anim_4 = 0x00210000, .anim_5 = 0x00210000, .death = 0x00210000, .hit = 0x00210000, .anim_8 = 0x00210000, .anim_9 = 0x00210000, .anim_A = 0x00210000, .anim_B = 0x00210000, .anim_C = 0x00210000, .anim_D = 0x00210000, .anim_E = 0x00210000, .anim_F = 0x00210000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 5,
        .settings = &TTYD64_kmr_31_NpcSettings_Generic,
        .pos = { 242.0f, 60.0f, -119.0f },
        .flags = 0x00A40D20,
        .init = &TTYD64_kmr_31_Script_Init_NoShadow,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x0005000A, .walk = 0x00050000, .run = 0x00050000, .chase = 0x00050000, .anim_4 = 0x00050000, .anim_5 = 0x00050000, .death = 0x00050000, .hit = 0x00050000, .anim_8 = 0x00050000, .anim_9 = 0x00050000, .anim_A = 0x00050000, .anim_B = 0x00050000, .anim_C = 0x00050000, .anim_D = 0x00050000, .anim_E = 0x00050000, .anim_F = 0x00050000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 6,
        .settings = &TTYD64_kmr_31_NpcSettings_Generic,
        .pos = { 244.0f, 22.0f, -117.0f },
        .flags = 0x00A40D20,
        .init = &TTYD64_kmr_31_Script_Init_NoShadow,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00AF000B, .walk = 0x00AF0000, .run = 0x00AF0000, .chase = 0x00AF0000, .anim_4 = 0x00AF0000, .anim_5 = 0x00AF0000, .death = 0x00AF0000, .hit = 0x00AF0000, .anim_8 = 0x00AF0000, .anim_9 = 0x00AF0000, .anim_A = 0x00AF0000, .anim_B = 0x00AF0000, .anim_C = 0x00AF0000, .anim_D = 0x00AF0000, .anim_E = 0x00AF0000, .anim_F = 0x00AF0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_kmr_31_Script_Difficulty_InputsStep = {
    Exec(TTYD64_kmr_31_Script_Difficulty_UpdateSprite)
    Call(TTYD64_kmr31_Get, TTYD64_K31_STATE, LVar1)
    Switch(LVar1)
    CaseEq(0)
        Call(TTYD64_kmr31_Set, TTYD64_K31_STATE, 1)
        Return
    CaseEq(1)
        Call(TTYD64_kmr31_Get, TTYD64_K31_ALPHA, LVar1)
        Add(LVar1, 64)
        IfGe(LVar1, 255)
            Set(LVar1, 255)
            Call(TTYD64_kmr31_Set, TTYD64_K31_ALPHA, LVar1)
            Call(TTYD64_kmr31_Set, TTYD64_K31_STATE, 3)
        EndIf
        Call(TTYD64_kmr31_Set, TTYD64_K31_ALPHA, LVar1)
        Return
    CaseEq(2)
        Call(TTYD64_kmr31_Get, TTYD64_K31_ALPHA, LVar1)
        Sub(LVar1, 64)
        IfLe(LVar1, 0)
            Set(LVar1, 0)
            Call(TTYD64_kmr31_Set, TTYD64_K31_ALPHA, LVar1)
            Call(TTYD64_kmr31_Set, TTYD64_K31_STATE, 0)
            Set(MapVar(1), 0)
        EndIf
        Call(TTYD64_kmr31_Set, TTYD64_K31_ALPHA, LVar1)
        Return
    CaseEq(3)
    EndSwitch
    Call(TTYD64_ReadField, TTYD64_F_GGAMESTATUS_10_4U, LVar0)
    IfFlag(LVar0, 0x40000)
        Call(PlaySound, 199)
        IfEq(MapVar(2), 0)
            Set(MapVar(2), 3)
        Else
            Add(MapVar(2), -1)
        EndIf
    EndIf
    IfFlag(LVar0, 0x80000)
        Call(PlaySound, 199)
        IfEq(MapVar(2), 3)
            Set(MapVar(2), 0)
        Else
            Add(MapVar(2), 1)
        EndIf
    EndIf
    IfFlag(LVar0, 32768)
        Set(GameByte(4105), MapVar(2))
        Call(PlaySound, 16)
        Call(TTYD64_kmr31_Set, TTYD64_K31_STATE, 2)
    EndIf
    IfFlag(LVar0, 16384)
        Call(PlaySound, 202)
        Set(MapVar(2), GameByte(4105))
        Call(TTYD64_kmr31_Set, TTYD64_K31_STATE, 2)
    EndIf
    Return
    End
};

EvtScript TTYD64_kmr_31_Script_Start_InputsStep = {
    Exec(TTYD64_kmr_31_Script_Start_UpdateSprite)
    Call(TTYD64_kmr31_Get, TTYD64_K31_STATE, LVar1)
    Switch(LVar1)
    CaseEq(0)
        Call(TTYD64_kmr31_Set, TTYD64_K31_STATE, 1)
        Return
    CaseEq(1)
        Call(TTYD64_kmr31_Get, TTYD64_K31_ALPHA, LVar1)
        Add(LVar1, 64)
        IfGe(LVar1, 255)
            Set(LVar1, 255)
            Call(TTYD64_kmr31_Set, TTYD64_K31_ALPHA, LVar1)
            Call(TTYD64_kmr31_Set, TTYD64_K31_STATE, 3)
        EndIf
        Call(TTYD64_kmr31_Set, TTYD64_K31_ALPHA, LVar1)
        Return
    CaseEq(2)
        Call(TTYD64_kmr31_Get, TTYD64_K31_ALPHA, LVar1)
        Sub(LVar1, 64)
        IfLe(LVar1, 0)
            Set(LVar1, 0)
            Call(TTYD64_kmr31_Set, TTYD64_K31_ALPHA, LVar1)
            Call(TTYD64_kmr31_Set, TTYD64_K31_STATE, 0)
            Set(MapVar(1), 0)
        EndIf
        Call(TTYD64_kmr31_Set, TTYD64_K31_ALPHA, LVar1)
        Return
    CaseEq(3)
    EndSwitch
    Call(TTYD64_ReadField, TTYD64_F_GGAMESTATUS_10_4U, LVar0)
    IfFlag(LVar0, 0x40000)
        Call(PlaySound, 199)
        IfEq(MapVar(2), 0)
            Set(MapVar(2), 2)
        Else
            Add(MapVar(2), -1)
        EndIf
    EndIf
    IfFlag(LVar0, 0x80000)
        Call(PlaySound, 199)
        IfEq(MapVar(2), 2)
            Set(MapVar(2), 0)
        Else
            Add(MapVar(2), 1)
        EndIf
    EndIf
    IfFlag(LVar0, 32768)
        Set(MapVar(4), MapVar(2))
        Call(PlaySound, 16)
        Call(TTYD64_kmr31_Set, TTYD64_K31_STATE, 2)
    EndIf
    IfFlag(LVar0, 16384)
        Call(PlaySound, 202)
        Set(MapVar(2), MapVar(4))
        Call(TTYD64_kmr31_Set, TTYD64_K31_STATE, 2)
    EndIf
    Return
    End
};

EvtScript TTYD64_kmr_31_Script_Mode_InputsStep = {
    Exec(TTYD64_kmr_31_Script_Mode_UpdateSprite)
    Call(TTYD64_kmr31_Get, TTYD64_K31_STATE, LVar1)
    Switch(LVar1)
    CaseEq(0)
        Call(TTYD64_kmr31_Set, TTYD64_K31_STATE, 1)
        Return
    CaseEq(1)
        Call(TTYD64_kmr31_Get, TTYD64_K31_ALPHA, LVar1)
        Add(LVar1, 64)
        IfGe(LVar1, 255)
            Set(LVar1, 255)
            Call(TTYD64_kmr31_Set, TTYD64_K31_ALPHA, LVar1)
            Call(TTYD64_kmr31_Set, TTYD64_K31_STATE, 3)
        EndIf
        Call(TTYD64_kmr31_Set, TTYD64_K31_ALPHA, LVar1)
        Return
    CaseEq(2)
        Call(TTYD64_kmr31_Get, TTYD64_K31_ALPHA, LVar1)
        Sub(LVar1, 64)
        IfLe(LVar1, 0)
            Set(LVar1, 0)
            Call(TTYD64_kmr31_Set, TTYD64_K31_ALPHA, LVar1)
            Call(TTYD64_kmr31_Set, TTYD64_K31_STATE, 0)
            Set(MapVar(1), 0)
        EndIf
        Call(TTYD64_kmr31_Set, TTYD64_K31_ALPHA, LVar1)
        Return
    CaseEq(3)
    EndSwitch
    Call(TTYD64_ReadField, TTYD64_F_GGAMESTATUS_10_4U, LVar0)
    IfFlag(LVar0, 0x40000)
        Call(PlaySound, 199)
        IfEq(MapVar(2), 0)
            Set(MapVar(2), 2)
        Else
            Add(MapVar(2), -1)
        EndIf
    EndIf
    IfFlag(LVar0, 0x80000)
        Call(PlaySound, 199)
        IfEq(MapVar(2), 2)
            Set(MapVar(2), 0)
        Else
            Add(MapVar(2), 1)
        EndIf
    EndIf
    IfFlag(LVar0, 32768)
        Set(GameByte(4107), MapVar(2))
        Call(PlaySound, 16)
        Call(TTYD64_kmr31_Set, TTYD64_K31_STATE, 2)
    EndIf
    IfFlag(LVar0, 16384)
        Call(PlaySound, 202)
        Set(MapVar(2), GameByte(4107))
        Call(TTYD64_kmr31_Set, TTYD64_K31_STATE, 2)
    EndIf
    Return
    End
};

EvtScript TTYD64_kmr_31_Script_Confirm_InputsStep = {
    Call(CloseMessage)
    Call(ShowMessageAtScreenPos, (Bytecode) TTYD64_kmr_31_String_Confirmation, 160, 40)
    Call(ShowChoice, 0x1E000D)
    IfEq(LVar0, 0)
        Call(CloseMessage)
        ExecWait(TTYD64_kmr_31_Script_OpenDoor)
        Wait(10)
        Set(MapVar(0), 4)
        Call(PlaySound, 392)
        Set(GameByte(0), -128)
        Switch(MapVar(4))
        CaseEq(0)
            Call(GotoMapSpecial, (Bytecode) "kmr_20", 0, 6)
        CaseEq(1)
            Call(GotoMapSpecial, (Bytecode) "kmr_00", 0, 6)
        CaseEq(2)
            Set(GameByte(0), -122)
            Set(GameFlag(40), 1)
            Set(GameFlag(38), 1)
            Set(GameFlag(32), 1)
            Set(GameFlag(104), 1)
            Set(GameFlag(1966), 1)
            Call(GotoMapSpecial, (Bytecode) "kmr_03", 2, 6)
        EndSwitch
        Set(GameFlag(95), 1)
        Set(GameFlag(97), 1)
        Set(GameFlag(96), 1)
        Call(TTYD64_WriteField, TTYD64_F_GPLAYERDATA_A_1U, 1)
        Call(TTYD64_ResetFFWD)
        Call(TTYD64_Function_ClearData_KMR31_ExtraData)
        Wait(1000)
    Else
        Call(CloseMessage)
        Wait(5)
        Call(ShowMessageAtScreenPos, (Bytecode) TTYD64_kmr_31_String_Empty, 160, 40)
        Call(SwitchMessage, (Bytecode) TTYD64_kmr_31_String_Difficulty)
        Set(MapVar(1), 0)
        Set(MapVar(0), 0)
        Wait(10)
    EndIf
    Return
    End
};

EvtScript TTYD64_kmr_31_Script_InitPlaythough_Inputs_Step = {
    Call(TTYD64_Function_ClearData_KMR31_ExtraData)
    Loop(0)
        Switch(MapVar(0))
        CaseEq(0)
            Switch(MapVar(1))
            CaseEq(0)
                Exec(TTYD64_kmr_31_Script_UpdateCursorPos)
            CaseEq(1)
                Wait(1)
                Set(MapVar(1), 2)
            CaseEq(2)
                Exec(TTYD64_kmr_31_Script_Difficulty_InputsStep)
            EndSwitch
        CaseEq(1)
            Switch(MapVar(1))
            CaseEq(0)
                Exec(TTYD64_kmr_31_Script_UpdateCursorPos)
            CaseEq(1)
                Wait(1)
                Set(MapVar(1), 2)
            CaseEq(2)
                Exec(TTYD64_kmr_31_Script_Start_InputsStep)
            EndSwitch
        CaseEq(2)
            Switch(MapVar(1))
            CaseEq(0)
                Exec(TTYD64_kmr_31_Script_UpdateCursorPos)
            CaseEq(1)
                Wait(1)
                Set(MapVar(1), 2)
            CaseEq(2)
                Exec(TTYD64_kmr_31_Script_Mode_InputsStep)
            EndSwitch
        CaseEq(3)
            Switch(MapVar(1))
            CaseEq(1)
                Wait(1)
                Set(MapVar(1), 2)
            CaseEq(2)
                ExecWait(TTYD64_kmr_31_Script_Confirm_InputsStep)
            EndSwitch
        EndSwitch
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_kmr_31_Script_UpdateCursorPos = {
    Call(TTYD64_ReadField, TTYD64_F_GGAMESTATUS_10_4U, LVar0)
    IfFlag(LVar0, 0x40000)
        IfEq(MapVar(0), 0)
            Set(MapVar(0), 2)
        Else
            Add(MapVar(0), -1)
        EndIf
        Exec(TTYD64_kmr_31_Script_UpdateString)
        Call(PlaySound, 199)
    EndIf
    IfFlag(LVar0, 0x80000)
        IfEq(MapVar(0), 2)
            Set(MapVar(0), 0)
        Else
            Add(MapVar(0), 1)
        EndIf
        Exec(TTYD64_kmr_31_Script_UpdateString)
        Call(PlaySound, 199)
    EndIf
    IfFlag(LVar0, 32768)
        Switch(MapVar(0))
        CaseEq(0)
            Set(MapVar(2), GameByte(4105))
        CaseEq(1)
            Set(MapVar(2), MapVar(4))
        CaseEq(2)
            Set(MapVar(2), GameByte(4107))
        EndSwitch
        Set(MapVar(1), 1)
        Call(PlaySound, 201)
    EndIf
    IfFlag(LVar0, 4096)
        Set(MapVar(0), 3)
        Set(MapVar(1), 1)
        Call(PlaySound, 201)
    EndIf
    Return
    End
};

EvtScript TTYD64_kmr_31_Script_Start_UpdateSprite = {
    Call(SetNpcPos, 2, 0, -1000, 0)
    Call(SetNpcPos, 3, 0, -1000, 0)
    Call(SetNpcPos, 4, 0, -1000, 0)
    Switch(MapVar(2))
    CaseEq(0)
        Set(LVar2, (Bytecode) TTYD64_kmr_31_String_Start_Original)
        Call(SetNpcPos, 2, 181, 32, -117)
    CaseEq(1)
        Set(LVar2, (Bytecode) TTYD64_kmr_31_String_Start_Goomba)
        Call(SetNpcPos, 3, 181, 32, -117)
    CaseEq(2)
        Set(LVar2, (Bytecode) TTYD64_kmr_31_String_Start_JrTroopa)
        Call(SetNpcPos, 4, 181, 32, -117)
    EndSwitch
    Call(TTYD64_kmr31_Get, TTYD64_K31_STATE, LVar1)
    IfNe(LVar1, 2)
        Call(TTYD64_kmr31_Set, TTYD64_K31_MESSAGE, LVar2)
    EndIf
    Return
    End
};

EvtScript TTYD64_kmr_31_Script_InitPlaythough_Step = {
    Exec(TTYD64_kmr_31_Script_InitPlaythough_Inputs_Step)
    Call(ShowMessageAtScreenPos, (Bytecode) TTYD64_kmr_31_String_Empty, 160, 40)
    Call(SwitchMessage, (Bytecode) TTYD64_kmr_31_String_Difficulty)
    Call(SetCamSpeed, 0, Float(3.0))
    Thread
        Loop(0)
            Switch(MapVar(0))
            CaseEq(0)
                Call(SetPlayerPos, 596, -152, -95)
            CaseEq(1)
                Call(SetPlayerPos, 637, -152, -95)
            CaseEq(2)
                Call(SetPlayerPos, 682, -152, -95)
            CaseEq(3)
                Call(SetPlayerPos, 726, -152, -95)
            CaseEq(4)
                Call(SetPlayerPos, 596, -152, -51)
            EndSwitch
            Wait(1)
        EndLoop
    EndThread
    Return
    End
};

EvtScript TTYD64_kmr_31_Script_WelcomeMessage = {
    IfEq(GameByte(4106), 0)
        Set(GameByte(4105), 1)
        Set(GameFlag(4105), 1)
    EndIf
    Call(SetMusic, 0, 148, 0, 8)
    Call(SetCamSpeed, 0, Float(7.0))
    Call(ShowMessageAtScreenPos, (Bytecode) TTYD64_kmr_31_String_Welcome, 160, 40)
    Wait(10)
    Call(SetPlayerPos, 637, -152, -140)
    Wait(10)
    ExecWait(TTYD64_kmr_31_Script_OpenDoor)
    Wait(5)
    Call(SetPlayerPos, 682, -152, -140)
    Wait(20)
    Exec(TTYD64_kmr_31_Script_CloseDoor)
    Call(SetPlayerPos, 726, -152, -140)
    Wait(20)
    Set(MapVar(0), 0)
    Exec(TTYD64_kmr_31_Script_InitPlaythough_Step)
    Return
    End
};

EvtScript TTYD64_kmr_31_Script_Mode_UpdateSprite = {
    Call(SetNpcPos, 5, 0, -1000, 0)
    Call(SetNpcPos, 6, 0, -1000, 0)
    Switch(MapVar(2))
    CaseEq(0)
        Set(LVar2, (Bytecode) TTYD64_kmr_31_String_Mode_Original)
    CaseEq(1)
        Set(LVar2, (Bytecode) TTYD64_kmr_31_String_Mode_Bow)
        Call(SetNpcPos, 5, 242, 60, -119)
    CaseEq(2)
        Set(LVar2, (Bytecode) TTYD64_kmr_31_String_Mode_Rando)
        Call(SetNpcPos, 6, 244, 22, -117)
    EndSwitch
    Call(TTYD64_kmr31_Get, TTYD64_K31_STATE, LVar1)
    IfNe(LVar1, 2)
        Call(TTYD64_kmr31_Set, TTYD64_K31_MESSAGE, LVar2)
    EndIf
    Return
    End
};

EvtScript TTYD64_kmr_31_Script_Difficulty_UpdateSprite = {
    Switch(MapVar(2))
    CaseEq(0)
        Set(LVar2, (Bytecode) TTYD64_kmr_31_String_Difficulty_Easy_Description)
        Call(SetNpcAnimation, 1, 0xE6000B)
    CaseEq(1)
        Set(LVar2, (Bytecode) TTYD64_kmr_31_String_Difficulty_Normal_Description)
        Call(SetNpcAnimation, 1, 0xE6000C)
    CaseEq(2)
        Set(LVar2, (Bytecode) TTYD64_kmr_31_String_Difficulty_Hard_Description)
        Call(SetNpcAnimation, 1, 0xE6000D)
    CaseEq(3)
        Set(LVar2, (Bytecode) TTYD64_kmr_31_String_Difficulty_MQ_Description)
        Call(SetNpcAnimation, 1, 0xE6000E)
    EndSwitch
    Call(TTYD64_kmr31_Get, TTYD64_K31_STATE, LVar1)
    IfNe(LVar1, 2)
        Call(TTYD64_kmr31_Set, TTYD64_K31_MESSAGE, LVar2)
    EndIf
    Return
    End
};

EvtScript TTYD64_kmr_31_Script_UpdateString = {
    Call(TTYD64_ReadField, TTYD64_F_GCURRENTPRINTCONTEXT_0_4U, LVar1)
    Call(TTYD64_WritePtrField, LVar1, TTYD64_F_MESSAGEPRINTSTATE_4_2U, 2)
    Switch(MapVar(0))
    CaseEq(0)
        Call(SwitchMessage, (Bytecode) TTYD64_kmr_31_String_Difficulty)
    CaseEq(1)
        Call(SwitchMessage, (Bytecode) TTYD64_kmr_31_String_Prologue)
    CaseEq(2)
        Call(SwitchMessage, (Bytecode) TTYD64_kmr_31_String_Mode)
    EndSwitch
    Call(TTYD64_WritePtrField, LVar1, TTYD64_F_MESSAGEPRINTSTATE_460_4U, 0)
    Call(TTYD64_WritePtrField, LVar1, TTYD64_F_MESSAGEPRINTSTATE_466_2U, 0)
    Call(TTYD64_WritePtrField, LVar1, TTYD64_F_MESSAGEPRINTSTATE_486_1U, 0)
    Return
    End
};

EvtScript TTYD64_kmr_31_Script_Main = {
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(DisablePlayerInput, 1)
    Call(TTYD64_SetFFWDSuppressed, 1)
    Exec(TTYD64_kmr_31_Script_WelcomeMessage)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_kmr_31_NpcGroupList)
    Exec(TTYD64_kmr_31_Script_SetNpcs)
    Return
    End
};

u8 TTYD64_kmr_31_String_MQ_Confirmation[] = {
    0xFC, 0x06, 0x21, 0x52, 0x45, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x53, 0x55,
    0x52, 0x45, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x57, 0x41, 0x4E, 0x54, 0xF7,
    0x54, 0x4F, 0xF7, 0x50, 0x4C, 0x41, 0x59, 0xF7, 0x49, 0x4E, 0xF0, 0x54,
    0x48, 0x45, 0xF7, 0xFF, 0x24, 0xFF, 0x05, 0x07, 0x2D, 0x41, 0x53, 0x54,
    0x45, 0x52, 0xF7, 0x31, 0x55, 0x45, 0x53, 0x54, 0xFF, 0x25, 0xF7, 0x44,
    0x49, 0x46, 0x46, 0x49, 0x43, 0x55, 0x4C, 0x54, 0x59, 0x1F, 0xF0, 0xF1,
    0xFB, 0x33, 0x55, 0x50, 0x45, 0x52, 0xF7, 0x27, 0x55, 0x41, 0x52, 0x44,
    0x53, 0xF7, 0x41, 0x52, 0x45, 0xF7, 0x44, 0x49, 0x53, 0x41, 0x42, 0x4C,
    0x45, 0x44, 0x0E, 0xF0, 0xF1, 0xFB, 0x21, 0x4E, 0x44, 0xF7, 0x59, 0x4F,
    0x55, 0xF7, 0xFF, 0x24, 0xFF, 0x05, 0x07, 0x43, 0x41, 0x4E, 0x07, 0x54,
    0xF7, 0x52, 0x45, 0x44, 0x55, 0x43, 0x45, 0xF7, 0x54, 0x48, 0x45, 0xF0,
    0x44, 0x49, 0x46, 0x46, 0x49, 0x43, 0x55, 0x4C, 0x54, 0x59, 0xFF, 0x25,
    0xF7, 0x41, 0x46, 0x54, 0x45, 0x52, 0xF7, 0x54, 0x48, 0x49, 0x53, 0x0E,
    0xF0, 0xF1, 0xFB, 0x21, 0x52, 0x45, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x53,
    0x55, 0x52, 0x45, 0xF7, 0x41, 0x42, 0x4F, 0x55, 0x54, 0xF7, 0x54, 0x48,
    0x49, 0x53, 0x1F, 0xFF, 0x04, 0xFD
};

EvtScript TTYD64_kmr_31_Script_CloseDoor = {
    Call(PlaySound, 450)
    Call(MakeLerp, 105, 0, 20, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(RotateGroup, 87, LVar0, 0, -1, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript TTYD64_kmr_31_Script_OpenDoor = {
    Call(PlaySound, 449)
    Call(MakeLerp, 0, 105, 20, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(RotateGroup, 87, LVar0, 0, -1, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript TTYD64_kmr_31_Script_SetNpcs = {
    Set(MapVar(2), GameByte(4105))
    ExecWait(TTYD64_kmr_31_Script_Difficulty_UpdateSprite)
    Set(MapVar(2), 0)
    ExecWait(TTYD64_kmr_31_Script_Start_UpdateSprite)
    Set(MapVar(2), GameByte(4107))
    ExecWait(TTYD64_kmr_31_Script_Mode_UpdateSprite)
    Return
    End
};

u8 TTYD64_kmr_31_String_Welcome[] = {
    0xFC, 0x06, 0x37, 0x45, 0x4C, 0x43, 0x4F, 0x4D, 0x45, 0xF7, 0x54, 0x4F,
    0xF7, 0x34, 0x34, 0x39, 0x24, 0x16, 0x14, 0x0E, 0xF0, 0xF1, 0xFB, 0x22,
    0x45, 0x46, 0x4F, 0x52, 0x45, 0xF7, 0x53, 0x54, 0x41, 0x52, 0x54, 0x49,
    0x4E, 0x47, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x47, 0x41, 0x4D, 0x45, 0x0C,
    0xF7, 0x46, 0x49, 0x52, 0x53, 0x54, 0xF0, 0x54, 0x41, 0x4B, 0x45, 0xF7,
    0x41, 0xF7, 0x4C, 0x4F, 0x4F, 0x4B, 0xF7, 0x41, 0x54, 0xF7, 0x53, 0x4F,
    0x4D, 0x45, 0xF7, 0x53, 0x45, 0x54, 0x54, 0x49, 0x4E, 0x47, 0x53, 0x0E,
    0xF0, 0xF1, 0xFD
};

u8 TTYD64_kmr_31_String_Mode_Rando[] = {
    0xFF, 0x05, 0x0A, 0x29, 0x4E, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7, 0x4D,
    0x4F, 0x44, 0x45, 0xF7, 0x49, 0x54, 0x45, 0x4D, 0x53, 0xF7, 0x46, 0x52,
    0x4F, 0x4D, 0xF7, 0x43, 0x48, 0x45, 0x53, 0x54, 0x53, 0x0C, 0xF0, 0x42,
    0x4C, 0x4F, 0x43, 0x4B, 0x53, 0xF7, 0x41, 0x4E, 0x44, 0xF7, 0x45, 0x4E,
    0x45, 0x4D, 0x49, 0x45, 0x53, 0xF7, 0x41, 0x52, 0x45, 0xF7, 0x52, 0x41,
    0x4E, 0x44, 0x4F, 0x4D, 0x49, 0x5A, 0x45, 0x44, 0xFD
};

u8 TTYD64_kmr_31_String_Mode_Bow[] = {
    0xFF, 0x05, 0x0A, 0x29, 0x4E, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7, 0x4D,
    0x4F, 0x44, 0x45, 0xF7, 0x22, 0x4F, 0x57, 0xF7, 0x49, 0x53, 0xF7, 0x54,
    0x48, 0x45, 0xF7, 0x4F, 0x4E, 0x4C, 0x59, 0xF0, 0x50, 0x41, 0x52, 0x54,
    0x4E, 0x45, 0x52, 0x0C, 0xF7, 0x42, 0x55, 0x54, 0xF7, 0x53, 0x48, 0x45,
    0xF7, 0x49, 0x53, 0x0E, 0x0E, 0x0E, 0xF7, 0x53, 0x54, 0x52, 0x4F, 0x4E,
    0x47, 0x45, 0x52, 0x1F, 0xFD
};

u8 TTYD64_kmr_31_String_Prologue[] = {
    0xFB, 0xFF, 0x09, 0x26, 0x52, 0x4F, 0x4D, 0xF7, 0x57, 0x48, 0x49, 0x43,
    0x48, 0xF7, 0x50, 0x41, 0x52, 0x54, 0xF7, 0x44, 0x4F, 0xF7, 0x59, 0x4F,
    0x55, 0xF7, 0x57, 0x41, 0x4E, 0x54, 0xF7, 0x54, 0x4F, 0xF0, 0x53, 0x54,
    0x41, 0x52, 0x54, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7, 0x50, 0x4C, 0x41,
    0x59, 0x54, 0x48, 0x52, 0x4F, 0x55, 0x47, 0x48, 0x1F, 0xF0, 0xFF, 0x04,
    0xFD
};

MapSettings TTYD64_kmr_31_Header = {
    .main = &TTYD64_kmr_31_Script_Main,
    .entryList = &TTYD64_kmr_31_EntryList,
    .entryCount = 1,
    .background = &gBackgroundImage,
    .tattle = { .get = NULL },
};

u8 TTYD64_kmr_31_String_Difficulty_Hard_Description[] = {
    0xFF, 0x05, 0x0A, 0x32, 0x45, 0x43, 0x4F, 0x4D, 0x4D, 0x45, 0x4E, 0x44,
    0x45, 0x44, 0xF7, 0x46, 0x4F, 0x52, 0xF7, 0x50, 0x4C, 0x41, 0x59, 0x45,
    0x52, 0x53, 0xF7, 0x54, 0x48, 0x41, 0x54, 0xF0, 0x46, 0x49, 0x4E, 0x44,
    0xF7, 0x30, 0x2D, 0xF7, 0x41, 0xF7, 0x4C, 0x49, 0x54, 0x54, 0x4C, 0x45,
    0xF7, 0x54, 0x4F, 0x4F, 0xF7, 0x45, 0x41, 0x53, 0x59, 0x0E, 0xFD
};

s32 TTYD64_kmr_31_Function_Init(void) {
    sprintf(wMapTexName, "kmr_tex");
    return false;
}

u8 TTYD64_kmr_31_String_Difficulty_Normal_Description[] = {
    0xFF, 0x05, 0x0A, 0x32, 0x45, 0x43, 0x4F, 0x4D, 0x4D, 0x45, 0x4E, 0x44,
    0x45, 0x44, 0xF7, 0x46, 0x4F, 0x52, 0xF7, 0x50, 0x4C, 0x41, 0x59, 0x45,
    0x52, 0x53, 0xF7, 0x57, 0x48, 0x4F, 0xF0, 0x57, 0x41, 0x4E, 0x54, 0xF7,
    0x41, 0xF7, 0x46, 0x41, 0x49, 0x52, 0xF7, 0x43, 0x48, 0x41, 0x4C, 0x4C,
    0x45, 0x4E, 0x47, 0x45, 0x0E, 0xFD
};

u8 TTYD64_kmr_31_String_Start_Goomba[] = {
    0xFF, 0x05, 0x0A, 0x33, 0x54, 0x41, 0x52, 0x54, 0xF7, 0x54, 0x48, 0x45,
    0xF7, 0x47, 0x41, 0x4D, 0x45, 0xF7, 0x41, 0x46, 0x54, 0x45, 0x52, 0xF7,
    0x59, 0x4F, 0x55, 0xF7, 0x46, 0x41, 0x4C, 0x4C, 0xF0, 0x49, 0x4E, 0x54,
    0x4F, 0xF7, 0x27, 0x4F, 0x4F, 0x4D, 0x42, 0x41, 0xF7, 0x56, 0x49, 0x4C,
    0x4C, 0x41, 0x47, 0x45, 0x0E, 0xFD
};

u8 TTYD64_kmr_31_String_Difficulty_MQ_Description[] = {
    0xFF, 0x05, 0x0A, 0x32, 0x45, 0x43, 0x4F, 0x4D, 0x4D, 0x45, 0x4E, 0x44,
    0x45, 0x44, 0xF7, 0x46, 0x4F, 0x52, 0xF7, 0x50, 0x4C, 0x41, 0x59, 0x45,
    0x52, 0x53, 0xF7, 0x52, 0x45, 0x41, 0x4C, 0x4C, 0x59, 0xF0, 0x46, 0x41,
    0x4D, 0x49, 0x4C, 0x49, 0x41, 0x52, 0xF7, 0x57, 0x49, 0x54, 0x48, 0xF7,
    0x30, 0x2D, 0x0E, 0xFD
};

u8 TTYD64_kmr_31_String_Mode[] = {
    0xFB, 0xFF, 0x09, 0x30, 0x4C, 0x41, 0x59, 0xF7, 0x54, 0x48, 0x45, 0xF7,
    0x47, 0x41, 0x4D, 0x45, 0xF7, 0x49, 0x4E, 0xF7, 0x41, 0xF7, 0x4D, 0x4F,
    0x44, 0x45, 0xF7, 0x49, 0x4E, 0xF0, 0x50, 0x41, 0x52, 0x54, 0x49, 0x43,
    0x55, 0x4C, 0x41, 0x52, 0x0E, 0xF0, 0xFF, 0x04, 0xFD
};

u8 TTYD64_kmr_31_String_Start_JrTroopa[] = {
    0xFF, 0x05, 0x0A, 0x33, 0x54, 0x41, 0x52, 0x54, 0xF7, 0x54, 0x48, 0x45,
    0xF7, 0x47, 0x41, 0x4D, 0x45, 0xF7, 0x41, 0x46, 0x54, 0x45, 0x52, 0xF7,
    0x59, 0x4F, 0x55, 0xF7, 0x41, 0x4E, 0x44, 0xF0, 0x27, 0x4F, 0x4F, 0x4D,
    0x50, 0x41, 0xF7, 0x46, 0x41, 0x4C, 0x4C, 0x0E, 0xFD
};

u8 TTYD64_kmr_31_String_Confirmation[] = {
    0xFC, 0x06, 0x21, 0x52, 0x45, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x52, 0x45,
    0x41, 0x44, 0x59, 0xF7, 0x54, 0x4F, 0xF7, 0x53, 0x54, 0x41, 0x52, 0x54,
    0xF7, 0x54, 0x48, 0x49, 0x53, 0xF0, 0x50, 0x4C, 0x41, 0x59, 0x54, 0x48,
    0x52, 0x4F, 0x55, 0x47, 0x48, 0x1F, 0xFF, 0x04, 0xFD
};

NpcSettings TTYD64_kmr_31_NpcSettings_Generic = {
    .defaultAnim = 0x00000000,
    .height = 32,
    .radius = 37,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = NULL,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 99,
    .actionFlags = 0,
};

u8 TTYD64_kmr_31_String_Mode_Original[] = {
    0xFF, 0x05, 0x0A, 0x30, 0x4C, 0x41, 0x59, 0xF7, 0x54, 0x48, 0x45, 0xF7,
    0x4F, 0x52, 0x49, 0x47, 0x49, 0x4E, 0x41, 0x4C, 0xF7, 0x34, 0x34, 0x39,
    0x24, 0x16, 0x14, 0xF0, 0x45, 0x58, 0x50, 0x45, 0x52, 0x49, 0x45, 0x4E,
    0x43, 0x45, 0x0E, 0xFD
};

u8 TTYD64_kmr_31_String_Start_Original[] = {
    0xFF, 0x05, 0x0A, 0x33, 0x54, 0x41, 0x52, 0x54, 0xF7, 0x54, 0x48, 0x45,
    0xF7, 0x47, 0x41, 0x4D, 0x45, 0xF7, 0x41, 0x53, 0xF7, 0x54, 0x48, 0x45,
    0xF7, 0x4F, 0x52, 0x49, 0x47, 0x49, 0x4E, 0x41, 0x4C, 0xF0, 0x47, 0x41,
    0x4D, 0x45, 0x0E, 0xFD
};

u8 TTYD64_kmr_31_String_Difficulty_Easy_Description[] = {
    0xFF, 0x05, 0x0A, 0x32, 0x45, 0x43, 0x4F, 0x4D, 0x4D, 0x45, 0x4E, 0x44,
    0x45, 0x44, 0xF7, 0x46, 0x4F, 0x52, 0xF7, 0x4D, 0x4F, 0x52, 0x45, 0xF7,
    0x43, 0x41, 0x53, 0x55, 0x41, 0x4C, 0xF0, 0x50, 0x4C, 0x41, 0x59, 0x45,
    0x52, 0x53, 0x0E, 0xFD
};

u8 TTYD64_kmr_31_String_Difficulty[] = {
    0xFB, 0xFF, 0x09, 0x23, 0x48, 0x41, 0x4E, 0x47, 0x45, 0xF7, 0x54, 0x48,
    0x45, 0xF7, 0x47, 0x41, 0x4D, 0x45, 0xF7, 0x44, 0x49, 0x46, 0x46, 0x49,
    0x43, 0x55, 0x4C, 0x54, 0x59, 0x0E, 0xF0, 0xF0, 0xFF, 0x04, 0xFD
};

NpcGroupList TTYD64_kmr_31_NpcGroupList = {
    { .npcCount = 6, .npcs = TTYD64_kmr_31_NpcGroup_InitPlaythrough, .battle = 0x0000, .stage = 0 },
    {},
};

EntryList TTYD64_kmr_31_EntryList = {
    { 596.0f, -152.0f, -140.0f, 90.0f },
};

u8 TTYD64_kmr_31_String_Difficulty_MQ_Title[] = {
    0x2D, 0x41, 0x53, 0x54, 0x45, 0x52, 0xF7, 0x31, 0x55, 0x45, 0x53, 0x54,
    0xFD
};

EvtScript TTYD64_kmr_31_Script_Init_NoShadow = {
    Call(EnableNpcShadow, NPC_SELF, false)
    Return
    End
};

u8 TTYD64_kmr_31_String_Difficulty_Normal_Title[] = {
    0x2E, 0x4F, 0x52, 0x4D, 0x41, 0x4C, 0xFD
};

u8 TTYD64_kmr_31_String_Difficulty_Hard_Title[] = {
    0x28, 0x41, 0x52, 0x44, 0xFD
};

u8 TTYD64_kmr_31_String_Difficulty_Easy_Title[] = {
    0x25, 0x41, 0x53, 0x59, 0xFD
};

u8 TTYD64_kmr_31_String_Empty[] = {
    0xFC, 0x06, 0xFF, 0x04, 0xFD
};

MapConfig TTYD64_mapcfg_kmr_31 = {
    .id = "kmr_31",
    .settings = &TTYD64_kmr_31_Header,
    .bgName = "kmr_bg",
    .init = TTYD64_kmr_31_Function_Init,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_kmr_31(void) {
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_Confirm_InputsStep, TTYD64_kmr_31_String_Confirmation);
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_Confirm_InputsStep, TTYD64_kmr_31_String_Empty);
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_Confirm_InputsStep, TTYD64_kmr_31_String_Difficulty);
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_Start_UpdateSprite, TTYD64_kmr_31_String_Start_Original);
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_Start_UpdateSprite, TTYD64_kmr_31_String_Start_Goomba);
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_Start_UpdateSprite, TTYD64_kmr_31_String_Start_JrTroopa);
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_InitPlaythough_Step, TTYD64_kmr_31_String_Empty);
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_InitPlaythough_Step, TTYD64_kmr_31_String_Difficulty);
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_WelcomeMessage, TTYD64_kmr_31_String_Welcome);
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_Mode_UpdateSprite, TTYD64_kmr_31_String_Mode_Original);
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_Mode_UpdateSprite, TTYD64_kmr_31_String_Mode_Bow);
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_Mode_UpdateSprite, TTYD64_kmr_31_String_Mode_Rando);
    TTYD64_nm_BindMessage(
        TTYD64_kmr_31_Script_Difficulty_UpdateSprite, TTYD64_kmr_31_String_Difficulty_Easy_Description
    );
    TTYD64_nm_BindMessage(
        TTYD64_kmr_31_Script_Difficulty_UpdateSprite, TTYD64_kmr_31_String_Difficulty_Normal_Description
    );
    TTYD64_nm_BindMessage(
        TTYD64_kmr_31_Script_Difficulty_UpdateSprite, TTYD64_kmr_31_String_Difficulty_Hard_Description
    );
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_Difficulty_UpdateSprite, TTYD64_kmr_31_String_Difficulty_MQ_Description);
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_UpdateString, TTYD64_kmr_31_String_Difficulty);
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_UpdateString, TTYD64_kmr_31_String_Prologue);
    TTYD64_nm_BindMessage(TTYD64_kmr_31_Script_UpdateString, TTYD64_kmr_31_String_Mode);
}
