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

API_CALLABLE(flo_16_FlyingNoAttackAI_Main);

extern EvtScript TTYD64_tyd_06_Script_EnterHorizontalPipe;
extern EvtScript TTYD64_tyd_06_Script_EnterVerticalPipe;
extern EvtScript TTYD64_tyd_06_Script_ExitHorizontalPipe;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_Obstacle;
extern EvtScript TTYD64_tyd_06_Script_ExitVerticalPipe;
extern NpcData TTYD64_tyd_06_NpcGroup_RuffPuff[];
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T6;
extern EvtScript TTYD64_tyd_06_Script_InitStuff;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T1_Main;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_M_Main;
extern EvtScript TTYD64_tyd_06_Script_Main;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_GenericRotation_Horizontal;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T5_Rotation;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_GenericRotation_Vertical;
extern u8 TTYD64_tyd_06_String_Tattle[];
extern EvtScript TTYD64_tyd_06_Script_EnterMap;
extern EvtScript TTYD64_tyd_06_Script_NpcAI_80244058_flo_16;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T2_Shadow;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T5_Shadow;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T4_Shadow;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T5_Decoration;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T4_1;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T3_T2;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T3_T3;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T3_T1;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T5_T1;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T2_T2;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T2_T1;
extern EvtScript TTYD64_tyd_06_Script_Exit0;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T1_T3;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T1_T2;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T1_T4;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T1_T1;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T1_Init;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T5_Init;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T3_Init;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T2_Init;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_M2;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_M1;
extern MapSettings TTYD64_tyd_06_Header;
extern EvtScript TTYD64_tyd_06_Script_GotoMap_Exit0;
extern EvtScript TTYD64_tyd_06_Script_SetupMusic;
extern EvtScript TTYD64_tyd_06_Script_UpdateModels_T4_Init;
extern MobileAISettings TTYD64_tyd_06_AISettings_80244028_flo_16;
extern NpcSettings TTYD64_tyd_06_NpcSettings_802440C8_flo_16;
s32 TTYD64_tyd_06_Function_Init(void);
extern EvtScript TTYD64_tyd_06_Script_CreateExitTriggers;
extern NpcGroupList TTYD64_tyd_06_NpcGroupList_tyd06;
extern EntryList TTYD64_tyd_06_EntryList;

// clang-format off
static s32 TTYD64_tyd_06_GetTattleMsg;

static s32 TTYD64_tyd_06_GetTattle(void) {
    return TTYD64_tyd_06_GetTattleMsg;
}

EvtScript TTYD64_tyd_06_Script_EnterHorizontalPipe = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(HidePlayerShadow, 1)
    Call(ModifyColliderFlags, 0, LVarB, 0x7FFFFE00)
    Call(GetEntryID, LVar0)
    Call(TTYD64_Pipe_GetEntryCoords)
    Set(LVar5, LVar1)
    Set(LVar6, LVar2)
    Set(LVar7, LVar3)
    Add(LVar2, 2)
    Call(SetPlayerPos, LVar1, LVar2, LVar3)
    Call(InterpPlayerYaw, LVar4, 0)
    IfEq(LVar4, 90)
        Add(LVar5, 40)
    Else
        Sub(LVar5, 40)
    EndIf
    Call(UseSettingsFrom, 0, LVar5, LVar6, LVar7)
    Call(SetPanTarget, 0, LVar5, LVar6, LVar7)
    Call(SetCamSpeed, 0, Float(90.0))
    Call(PanToTarget, 0, 0, 1)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Call(DisablePartnerAI, 0)
        Call(EnableNpcShadow, -4, 0)
        Call(SetNpcPos, -4, 0, -1000, 0)
        Call(InterpNpcYaw, -4, LVar0, 0)
    EndIf
    Wait(1)
    Call(PlaySound, 355)
    Thread
        Wait(25)
        Call(HidePlayerShadow, 0)
    EndThread
    Call(SetPlayerImgFXFlags, 2304)
    Call(UpdatePlayerImgFX, 0x10002, 5, 3, 1, 1, 0)
    Loop(40)
        Call(TTYD64_Pipe_GetPointInFrontOfPlayer, Float(1.0))
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Thread
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Sub(LVar2, 3)
            Call(SetNpcPos, -4, LVar0, LVar1, LVar2)
            Call(EnableNpcShadow, -4, 1)
            Call(EnablePartnerAI)
        EndThread
    EndIf
    Wait(5)
    Call(UpdatePlayerImgFX, 0x10002, 0, 0, 0, 0, 0)
    Call(ModifyColliderFlags, 1, LVarB, 0x7FFFFE00)
    Call(DisablePlayerInput, 0)
    Call(DisablePlayerPhysics, 0)
    Call(PanToTarget, 0, 0, 0)
    Exec(LVarA)
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_EnterVerticalPipe = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(DisablePartnerAI, 0)
    Call(HidePlayerShadow, 1)
    Call(SetPlayerAnimation, 0x10000)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Call(EnableNpcShadow, -4, 0)
        Call(SetNpcPos, -4, 0, -1000, 0)
    EndIf
    Call(GetEntryID, LVar0)
    Call(TTYD64_Pipe_GetEntryCoords)
    Sub(LVar2, 40)
    Call(SetPlayerPos, LVar1, LVar2, LVar3)
    Call(InterpPlayerYaw, LVar4, 0)
    Call(PlaySound, 355)
    Call(SetPlayerImgFXFlags, 256)
    Call(UpdatePlayerImgFX, 0x10000, 5, 2, 1, 1, 0)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Loop(40)
        Add(LVar1, 1)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Wait(3)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Thread
            Call(DisablePartnerAI, 0)
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Sub(LVar2, 3)
            Call(SetNpcPos, -4, LVar0, LVar1, LVar2)
            Call(SetNpcFlagBits, -4, 2, 0)
            Call(EnablePartnerAI)
            Call(EnableNpcShadow, -4, 1)
        EndThread
    EndIf
    Wait(2)
    Call(UpdatePlayerImgFX, 0x10000, 0, 0, 0, 0, 0)
    Wait(1)
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Call(HidePlayerShadow, 0)
    Label(0)
    Call(TTYD64_Pipe_GetCurrentFloor)
    Wait(1)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Exec(LVarA)
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_ExitHorizontalPipe = {
    Call(IsPlayerOnValidFloor, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(GetPlayerActionState, LVar0)
    IfEq(LVar0, 26)
        Return
    EndIf
    Call(GetPartnerInUse, LVar0)
    IfNe(LVar0, 0)
        Call(GetCurrentPartnerID, LVar1)
        IfNe(LVar1, 6)
            Return
        Else
            Call(InterruptUsePartner)
            Call(DisablePlayerInput, 1)
        EndIf
    Else
        Call(DisablePlayerInput, 1)
    EndIf
    SetGroup(27)
    Call(TTYD64_Pipe_SetAnimFlag)
    Call(DisablePlayerPhysics, 1)
    Call(ModifyColliderFlags, 0, LVarB, 0x7FFFFE00)
    Set(LVar0, LVarA)
    Call(TTYD64_Pipe_GetEntryCoords)
    Set(LVar5, LVar1)
    Set(LVar6, LVar2)
    Add(LVar6, 2)
    Set(LVar7, LVar3)
    Set(LVar8, LVar4)
    Add(LVar8, 180)
    IfGe(LVar4, 360)
        Sub(LVar4, 360)
    EndIf
    Call(InterpPlayerYaw, LVar8, 1)
    Wait(1)
    Call(PlaySound, 355)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(SetPlayerPos, LVar0, LVar6, LVar7)
    Call(SetPlayerAnimation, 0x10000)
    Call(SetPlayerImgFXFlags, 2048)
    Call(UpdatePlayerImgFX, 0x10000, 5, 3, 1, 1, 0)
    Thread
        Wait(8)
        Call(HidePlayerShadow, 1)
    EndThread
    Thread
        Wait(3)
        Loop(40)
            Call(TTYD64_Pipe_GetPointInFrontOfPlayer, Float(1.0))
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Wait(25)
    ExecWait(LVarC)
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_Obstacle = {
    Call(TranslateGroup, 118, 0, 118, 0)
    Call(UpdateColliderTransform, 37)
    Loop(0)
        Call(PlaySound, 247)
        Call(MakeLerp, 118, 0, 15, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, 118, 0, LVar0, 0)
            Call(UpdateColliderTransform, 37)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(MakeLerp, 0, 10, 4, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, 118, 0, LVar0, 0)
            Call(UpdateColliderTransform, 37)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(MakeLerp, 10, 4, 10, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, 118, 0, LVar0, 0)
            Call(UpdateColliderTransform, 37)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(30)
        Call(MakeLerp, 10, 118, 70, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, 118, 0, LVar0, 0)
            Call(UpdateColliderTransform, 37)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(40)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_ExitVerticalPipe = {
    Call(TTYD64_Pipe_CheckDownInput)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(GetPartnerInUse, LVar0)
    IfNe(LVar0, 0)
        Call(GetCurrentPartnerID, LVar1)
        IfNe(LVar1, 6)
            Return
        Else
            Call(InterruptUsePartner)
            Call(DisablePlayerInput, 1)
        EndIf
    Else
        Call(DisablePlayerInput, 1)
    EndIf
    SetGroup(27)
    Call(TTYD64_Pipe_SetAnimFlag)
    Call(DisablePlayerPhysics, 1)
    Call(HidePlayerShadow, 1)
    Set(LVar0, LVarA)
    Call(TTYD64_Pipe_GetEntryCoords)
    Call(PlayerMoveTo, LVar1, LVar3, 3)
    Set(LVar0, LVarA)
    Call(TTYD64_Pipe_GetEntryCoords)
    Call(SetPlayerPos, LVar1, LVar2, LVar3)
    Call(SetPlayerFlagBits, 0x200000, 1)
    Call(TTYD64_Pipe_GetCameraYaw)
    Call(InterpPlayerYaw, LVar0, 0)
    Wait(2)
    Call(SetPlayerFlagBits, 0x200000, 0)
    Call(PlaySound, 355)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Thread
        Wait(4)
        Loop(40)
            Sub(LVar1, 1)
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Call(SetPlayerImgFXFlags, 2048)
    Call(UpdatePlayerImgFX, 0x10002, 5, 2, 1, 1, 0)
    Wait(25)
    ExecWait(LVarC)
    Return
    End
};

NpcData TTYD64_tyd_06_NpcGroup_RuffPuff[] = {
    {
        .id = 0,
        .settings = &TTYD64_tyd_06_NpcSettings_802440C8_flo_16,
        .pos = { -578.0f, -6.0f, 68.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 16, .itemDrops = { { 140, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = -578, .centerPos.y = -7, .centerPos.z = 68, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = -578, .detectPos.y = -7, .detectPos.z = 68, .detectSize.x = 120, .detectSize.z = 30, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x007D0000, .walk = 0x007D0000, .run = 0x007D0005, .chase = 0x007D0005, .anim_4 = 0x007D0000, .anim_5 = 0x007D0000, .death = 0x007D0006, .hit = 0x007D0006, .anim_8 = 0x007D0005, .anim_9 = 0x007D0000, .anim_A = 0x007D0000, .anim_B = 0x007D0000, .anim_C = 0x007D0000, .anim_D = 0x007D0000, .anim_E = 0x007D0000, .anim_F = 0x007D0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T6 = {
    Call(RotateModel, 113, 15, 0, -1, 0)
    Loop(0)
        Call(MakeLerp, -15, 15, 35, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, 113, LVar0, 0, 1, 0)
            Call(UpdateColliderTransform, 20)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(40)
        Call(MakeLerp, 15, -15, 35, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, 113, LVar0, 0, 1, 0)
            Call(UpdateColliderTransform, 20)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(40)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_InitStuff = {
    Call(MakeItemEntity, 396, 508, 220, 20, 17, GameFlag(5523))
    Call(MakeItemEntity, 348, 378, 138, -32, 17, GameFlag(5522))
    Call(ParentColliderToModel, 13, 77)
    Call(ParentColliderToModel, 14, 79)
    Call(ParentColliderToModel, 15, 81)
    Call(ParentColliderToModel, 16, 83)
    Call(ParentColliderToModel, 17, 88)
    Call(ParentColliderToModel, 18, 100)
    Call(ParentColliderToModel, 19, 105)
    Call(ParentColliderToModel, 20, 113)
    Call(ParentColliderToModel, 37, 116)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T1_Init)
    Exec(TTYD64_tyd_06_Script_UpdateModels_M1)
    Exec(TTYD64_tyd_06_Script_UpdateModels_M2)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T2_Init)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T3_Init)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T4_Init)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T5_Init)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T6)
    Exec(TTYD64_tyd_06_Script_UpdateModels_Obstacle)
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T1_Main = {
    Set(LVar5, LVar0)
    Set(LVar6, LVar1)
    Call(PlaySoundAtModel, LVar5, 84, 0)
    Set(LVar1, 0)
    Set(LVar2, LVar1)
    Add(LVar2, 90)
    Call(MakeLerp, LVar1, LVar2, 35, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(RotateModel, LVar5, LVar0, 1, 0, 0)
        Call(UpdateColliderTransform, LVar6)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Wait(40)
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_M_Main = {
    Set(LVar5, LVar0)
    Call(MakeLerp, 0, 10, 10, 4)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateModel, LVar5, 0, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(MakeLerp, 10, 0, 10, 1)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateModel, LVar5, 0, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_Main = {
    Set(GameByte(425), 38)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(PlaySound, 573)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_tyd_06_NpcGroupList_tyd06)
    Exec(TTYD64_tyd_06_Script_InitStuff)
    Exec(TTYD64_tyd_06_Script_SetupMusic)
    Exec(TTYD64_tyd_06_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_GenericRotation_Horizontal = {
    Set(LVar5, LVar0)
    Set(LVar6, LVar1)
    Set(LVar7, LVar2)
    Add(LVar3, 3)
    Call(RotateModel, LVar5, LVar3, 0, LVar7, 0)
    IfNe(LVar6, 0)
        Call(UpdateColliderTransform, LVar6)
    EndIf
    Wait(1)
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T5_Rotation = {
    Set(LVar5, LVar0)
    Set(LVar6, LVar1)
    Set(LVar7, LVar2)
    Add(LVar3, LVar7)
    Call(RotateModel, LVar5, LVar3, 0, 1, 0)
    IfNe(LVar6, 0)
        Call(UpdateColliderTransform, LVar6)
    EndIf
    Wait(1)
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_GenericRotation_Vertical = {
    Set(LVar5, LVar0)
    Set(LVar6, LVar1)
    Set(LVar7, LVar2)
    Add(LVar3, 10)
    Call(RotateModel, LVar5, LVar3, LVar7, 0, 0)
    IfNe(LVar6, 0)
        Call(UpdateColliderTransform, LVar6)
    EndIf
    Wait(1)
    Return
    End
};

u8 TTYD64_tyd_06_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x34, 0x48, 0x49, 0x53, 0xF7, 0x50, 0x4C, 0x41,
    0x43, 0x45, 0xF7, 0x53, 0x45, 0x45, 0x4D, 0x53, 0xF7, 0x51, 0x55, 0x49,
    0x54, 0x45, 0xF7, 0x41, 0x42, 0x41, 0x4E, 0x44, 0x4F, 0x4E, 0x45, 0x44,
    0x0C, 0xF0, 0x49, 0x54, 0xF7, 0x53, 0x45, 0x45, 0x4D, 0x53, 0xF7, 0x54,
    0x48, 0x41, 0x54, 0xF7, 0x49, 0x54, 0xF7, 0x48, 0x41, 0x53, 0xF7, 0x56,
    0x45, 0x52, 0x59, 0xF0, 0x45, 0x58, 0x50, 0x45, 0x4E, 0x53, 0x49, 0x56,
    0x45, 0xF7, 0x4D, 0x41, 0x43, 0x48, 0x49, 0x4E, 0x45, 0x52, 0x59, 0x0C,
    0xF7, 0x57, 0x48, 0x4F, 0xF7, 0x57, 0x4F, 0x55, 0x4C, 0x44, 0xF0, 0x4C,
    0x45, 0x41, 0x56, 0x45, 0xF7, 0x41, 0xF7, 0x50, 0x4C, 0x41, 0x43, 0x45,
    0xF7, 0x54, 0x48, 0x49, 0x53, 0x1F, 0xF1, 0xFD
};

EvtScript TTYD64_tyd_06_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVarA, (Bytecode) TTYD64_tyd_06_Script_CreateExitTriggers)
        Exec(TTYD64_tyd_06_Script_EnterVerticalPipe)
    CaseDefault
        Exec(TTYD64_tyd_06_Script_CreateExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_NpcAI_80244058_flo_16 = {
    Call(SetSelfVar, 0, 1)
    Call(SetSelfVar, 5, 0)
    Call(SetSelfVar, 6, 0)
    Call(SetSelfVar, 1, 600)
    Call(flo_16_FlyingNoAttackAI_Main, Ref(TTYD64_tyd_06_AISettings_80244028_flo_16))
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T2_Shadow = {
    Loop(0)
        Set(LVar0, 90)
        Set(LVar1, 0)
        Set(LVar2, -1)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_GenericRotation_Horizontal)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T5_Shadow = {
    Loop(0)
        Set(LVar0, 107)
        Set(LVar1, 0)
        Set(LVar2, 3)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_T5_Rotation)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T4_Shadow = {
    Loop(0)
        Set(LVar0, 102)
        Set(LVar1, 0)
        Set(LVar2, -1)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_GenericRotation_Horizontal)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T5_Decoration = {
    Loop(0)
        Set(LVar0, 109)
        Set(LVar1, 0)
        Set(LVar2, 4)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_T5_Rotation)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T4_1 = {
    Loop(0)
        Set(LVar0, 100)
        Set(LVar1, 18)
        Set(LVar2, -1)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_GenericRotation_Horizontal)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T3_T2 = {
    Loop(0)
        Set(LVar0, 95)
        Set(LVar1, 0)
        Set(LVar2, -1)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_GenericRotation_Vertical)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T3_T3 = {
    Loop(0)
        Set(LVar0, 97)
        Set(LVar1, 0)
        Set(LVar2, 1)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_GenericRotation_Vertical)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T3_T1 = {
    Loop(0)
        Set(LVar0, 93)
        Set(LVar1, 0)
        Set(LVar2, 1)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_GenericRotation_Vertical)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T5_T1 = {
    Loop(0)
        Set(LVar0, 105)
        Set(LVar1, 19)
        Set(LVar2, 3)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_T5_Rotation)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T2_T2 = {
    Loop(0)
        Set(LVar0, 88)
        Set(LVar1, 17)
        Set(LVar2, -1)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_GenericRotation_Horizontal)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T2_T1 = {
    Loop(0)
        Set(LVar0, 86)
        Set(LVar1, 0)
        Set(LVar2, 1)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_GenericRotation_Horizontal)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_Exit0 = {
    SetGroup(27)
    Set(LVarA, 0)
    Set(LVarB, 43)
    Set(LVarC, (Bytecode) TTYD64_tyd_06_Script_GotoMap_Exit0)
    ExecWait(TTYD64_tyd_06_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T1_T3 = {
    Loop(0)
        Set(LVar0, 81)
        Set(LVar1, 15)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_T1_Main)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T1_T2 = {
    Loop(0)
        Set(LVar0, 79)
        Set(LVar1, 14)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_T1_Main)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T1_T4 = {
    Loop(0)
        Set(LVar0, 83)
        Set(LVar1, 16)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_T1_Main)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T1_T1 = {
    Loop(0)
        Set(LVar0, 77)
        Set(LVar1, 13)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_T1_Main)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T1_Init = {
    Exec(TTYD64_tyd_06_Script_UpdateModels_T1_T1)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T1_T3)
    Wait(40)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T1_T2)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T1_T4)
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T5_Init = {
    Set(LVar3, 0)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T5_T1)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T5_Shadow)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T5_Decoration)
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T3_Init = {
    Set(LVar3, 0)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T3_T1)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T3_T2)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T3_T3)
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T2_Init = {
    Set(LVar3, 0)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T2_T1)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T2_T2)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T2_Shadow)
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_M2 = {
    Loop(0)
        Set(LVar0, 17)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_M_Main)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_M1 = {
    Loop(0)
        Set(LVar0, 75)
        ExecWait(TTYD64_tyd_06_Script_UpdateModels_M_Main)
    EndLoop
    Return
    End
};

MapSettings TTYD64_tyd_06_Header = {
    .main = TTYD64_tyd_06_Script_Main,
    .entryList = &TTYD64_tyd_06_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_tyd_06_GetTattle },
};

EvtScript TTYD64_tyd_06_Script_GotoMap_Exit0 = {
    Call(StopSound, 573)
    Call(GotoMap, (Bytecode) "flo_28", 1)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_SetupMusic = {
    Call(SetMusic, 0, 171, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_tyd_06_Script_UpdateModels_T4_Init = {
    Set(LVar3, 0)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T4_1)
    Exec(TTYD64_tyd_06_Script_UpdateModels_T4_Shadow)
    Return
    End
};

MobileAISettings TTYD64_tyd_06_AISettings_80244028_flo_16 = {
    .moveSpeed = 1.0f,
    .moveTime = 45,
    .waitTime = 60,
    .alertRadius = 100.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 3.5999999f,
    .chaseTurnRate = 10,
    .chaseUpdateInterval = 1,
    .chaseRadius = 120.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_tyd_06_NpcSettings_802440C8_flo_16 = {
    .defaultAnim = 0x00000000,
    .height = 24,
    .radius = 28,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_tyd_06_Script_NpcAI_80244058_flo_16,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 19,
    .actionFlags = 0,
};

s32 TTYD64_tyd_06_Function_Init(void) {
    sprintf(wMapTexName, "flo_tex");
    return false;
}

EvtScript TTYD64_tyd_06_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_tyd_06_Script_Exit0, 128, 43, 1, 0)
    Return
    End
};

NpcGroupList TTYD64_tyd_06_NpcGroupList_tyd06 = {
    { .npcCount = 1, .npcs = TTYD64_tyd_06_NpcGroup_RuffPuff, .battle = 0x3B09, .stage = 6 },
    {},
};

EntryList TTYD64_tyd_06_EntryList = {
    { -322.0f, 10.0f, 14.0f, -90.0f },
};

MapConfig TTYD64_mapcfg_tyd_06 = {
    .id = "tyd_06",
    .settings = &TTYD64_tyd_06_Header,
    .bgName = NULL,
    .init = TTYD64_tyd_06_Function_Init,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_tp_Install_tyd_06(void) {
    TTYD64_tyd_06_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_tyd_06_String_Tattle);
}
