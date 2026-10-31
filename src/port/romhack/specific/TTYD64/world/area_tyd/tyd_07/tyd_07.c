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

extern EvtScript TTYD64_tyd_07_Script_EnterHorizontalPipe;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_Main;
extern EvtScript TTYD64_tyd_07_Script_EnterVerticalPipe;
extern EvtScript TTYD64_tyd_07_Script_EnterVerticalPipe_NoFromGoToMap;
extern EvtScript TTYD64_tyd_07_Script_ExitHorizontalPipe;
extern EvtScript TTYD64_tyd_07_Script_ExitVerticalPipe_NoGoToMap;
extern EvtScript TTYD64_tyd_07_Script_ExitVerticalPipe;
extern EvtScript TTYD64_tyd_07_Script_InitStuff;
extern EvtScript TTYD64_tyd_07_Script_MakeEntities;
extern EvtScript TTYD64_tyd_07_Script_SetupTexturePan;
extern EvtScript TTYD64_tyd_07_Script_BindScripts_Pipes;
extern EvtScript TTYD64_tyd_07_Script_Main;
extern EvtScript TTYD64_tyd_07_Script_ScriptedSpring_Entity_Spring;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Back_Init;
extern EvtScript TTYD64_tyd_07_Script_UpdateModels_GenericRotation_Z;
extern EvtScript TTYD64_tyd_07_Script_TexturePan_Update;
extern EvtScript TTYD64_tyd_07_Script_EnterMap;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_Front_1;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_Front_3;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_Front_2;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_Front_5;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_Front_4;
extern u8 TTYD64_tyd_07_String_Tattle[];
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_1;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_2;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_3;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_4;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_5;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_6;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_7;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_8;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Front_Init;
extern EvtScript TTYD64_tyd_07_Script_ScriptedSpring_FollowCam;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Gear4;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Gear5;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Gear1;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Gear2;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Gear3;
extern EvtScript TTYD64_tyd_07_Script_pipe7;
extern EvtScript TTYD64_tyd_07_Script_pipe1;
extern EvtScript TTYD64_tyd_07_Script_pipe5;
extern EvtScript TTYD64_tyd_07_Script_pipe4;
extern EvtScript TTYD64_tyd_07_Script_Exit0;
extern EvtScript TTYD64_tyd_07_Script_pipeB5;
extern EvtScript TTYD64_tyd_07_Script_pipeB4;
extern EvtScript TTYD64_tyd_07_Script_pipeB1;
extern EvtScript TTYD64_tyd_07_Script_pipeB3;
extern EvtScript TTYD64_tyd_07_Script_pipeB2;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_UpdateMarioXPos_Right;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatform_UpdateMarioXPos_Left;
extern EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Gears_Init;
extern MapSettings TTYD64_tyd_07_Header;
extern EvtScript TTYD64_tyd_07_Script_Entity_Shine1;
extern EvtScript TTYD64_tyd_07_Script_Entity_Shine2;
extern EvtScript TTYD64_tyd_07_Script_SetupMusic;
extern EvtScript TTYD64_tyd_07_Script_GotoMap_Exit0;
s32 TTYD64_tyd_07_Function_Init(void);
extern EvtScript TTYD64_tyd_07_Script_CreateExitTriggers;
extern EntryList TTYD64_tyd_07_EntryList;

// clang-format off
static s32 TTYD64_tyd_07_GetTattleMsg;

static s32 TTYD64_tyd_07_GetTattle(void) {
    return TTYD64_tyd_07_GetTattleMsg;
}

EvtScript TTYD64_tyd_07_Script_EnterHorizontalPipe = {
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

EvtScript TTYD64_tyd_07_Script_MovingPlatform_Main = {
    Set(LVar5, LVar0)
    Set(LVar6, LVar1)
    Set(LVar7, LVar2)
    Set(LVar8, LVar3)
    Set(LVar9, LVar4)
    Set(LVar0, 0)
    Loop(0)
        Call(MakeLerp, 0, LVar7, LVar8, 4)
        Loop(0)
            Set(LVarA, LVar0)
            Call(UpdateLerp)
            IfEq(LVar9, 0)
                Call(TranslateGroup, LVar5, LVar0, 0, 0)
                Call(TTYD64_ReadField, TTYD64_F_GCOLLISIONSTATUS_2_2U, LVar2)
                IfEq(LVar2, LVar6)
                    Call(GetPlayerPos, LVar2, LVar3, LVar4)
                    Sub(LVarA, LVar0)
                    Sub(LVar2, LVarA)
                    Call(SetPlayerPos, LVar2, LVar3, LVar4)
                EndIf
            Else
                Call(TranslateGroup, LVar5, 0, LVar0, 0)
            EndIf
            Call(UpdateColliderTransform, LVar6)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(25)
        Set(LVar0, LVar7)
        Call(MakeLerp, LVar7, 0, LVar8, 4)
        Loop(0)
            Set(LVarA, LVar0)
            Call(UpdateLerp)
            IfEq(LVar9, 0)
                Call(TranslateGroup, LVar5, LVar0, 0, 0)
                Call(TTYD64_ReadField, TTYD64_F_GCOLLISIONSTATUS_2_2U, LVar2)
                IfEq(LVar2, LVar6)
                    Call(GetPlayerPos, LVar2, LVar3, LVar4)
                    Sub(LVarA, LVar0)
                    Sub(LVar2, LVarA)
                    Call(SetPlayerPos, LVar2, LVar3, LVar4)
                EndIf
            Else
                Call(TranslateGroup, LVar5, 0, LVar0, 0)
            EndIf
            Call(UpdateColliderTransform, LVar6)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(25)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_tyd_07_Script_EnterVerticalPipe_NoFromGoToMap = {
    Call(DisablePartnerAI, 0)
    Call(SetPlayerAnimation, 0x10000)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Call(EnableNpcShadow, -4, 0)
        Call(SetNpcPos, -4, 0, -1000, 0)
    EndIf
    Call(GetColliderCenter, LVarC)
    Sub(LVar1, 40)
    Call(SetPlayerPos, LVar0, LVar1, LVar2)
    Call(InterpPlayerYaw, -270, 0)
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
    Call(TTYD64_SetVerticalMovementLocked, LVarD)
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
    Set(MapVar(2), 1)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_ExitHorizontalPipe = {
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

EvtScript TTYD64_tyd_07_Script_ExitVerticalPipe_NoGoToMap = {
    IfEq(MapVar(2), 0)
        Return
    EndIf
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
    Set(MapVar(2), 0)
    SetGroup(27)
    Call(TTYD64_Pipe_SetAnimFlag)
    Call(DisablePlayerPhysics, 1)
    Call(HidePlayerShadow, 1)
    Call(GetColliderCenter, LVarB)
    Call(PlayerMoveTo, LVar0, LVar2, 3)
    Call(GetColliderCenter, LVarB)
    Call(SetPlayerPos, LVar0, LVar1, LVar2)
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
    ExecWait(TTYD64_tyd_07_Script_EnterVerticalPipe_NoFromGoToMap)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_ExitVerticalPipe = {
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

EvtScript TTYD64_tyd_07_Script_InitStuff = {
    Call(ParentColliderToModel, 18, 49)
    Call(ParentColliderToModel, 19, 53)
    Call(ParentColliderToModel, 20, 57)
    Call(ParentColliderToModel, 21, 61)
    Call(ParentColliderToModel, 22, 65)
    Call(ParentColliderToModel, 92, 113)
    Call(ParentColliderToModel, 93, 116)
    Call(ParentColliderToModel, 94, 120)
    Call(ParentColliderToModel, 95, 122)
    Call(ParentColliderToModel, 96, 125)
    Call(ParentColliderToModel, 97, 128)
    Call(ParentColliderToModel, 98, 131)
    Call(ParentColliderToModel, 99, 134)
    Call(ParentColliderToModel, 100, 140)
    Call(ParentColliderToModel, 101, 142)
    Call(ParentColliderToModel, 102, 144)
    Call(ParentColliderToModel, 103, 146)
    Call(ParentColliderToModel, 104, 148)
    BindTrigger(TTYD64_tyd_07_Script_MovingPlatform_UpdateMarioXPos_Right, 128, 3, 1, 0)
    BindTrigger(TTYD64_tyd_07_Script_MovingPlatform_UpdateMarioXPos_Right, 128, 100, 1, 0)
    BindTrigger(TTYD64_tyd_07_Script_MovingPlatform_UpdateMarioXPos_Left, 128, 101, 1, 0)
    BindTrigger(TTYD64_tyd_07_Script_MovingPlatform_UpdateMarioXPos_Left, 128, 102, 1, 0)
    BindTrigger(TTYD64_tyd_07_Script_MovingPlatform_UpdateMarioXPos_Right, 128, 103, 1, 0)
    BindTrigger(TTYD64_tyd_07_Script_MovingPlatform_UpdateMarioXPos_Left, 128, 104, 1, 0)
    Exec(TTYD64_tyd_07_Script_MovingPlatforms_Front_Init)
    Exec(TTYD64_tyd_07_Script_MovingPlatforms_Back_Init)
    Exec(TTYD64_tyd_07_Script_MovingPlatforms_Gears_Init)
    Exec(TTYD64_tyd_07_Script_BindScripts_Pipes)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_ScriptSpring), 639, 325, 94, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_tyd_07_Script_ScriptedSpring_Entity_Spring)
    Call(MakeEntity, Ref(Entity_SuperBlock), -6, 162, 91, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(5570))
    Call(AssignScript, (Bytecode) TTYD64_tyd_07_Script_Entity_Shine1)
    Call(MakeEntity, Ref(Entity_SuperBlock), -677, 372, -471, 0, 0x80000000)
    Set(MapVar(1), LVar0)
    Call(AssignBlockFlag, GameFlag(5571))
    Call(AssignScript, (Bytecode) TTYD64_tyd_07_Script_Entity_Shine2)
    Call(MakeItemEntity, 393, 639, 450, -79, 17, GameFlag(5572))
    Call(MakeItemEntity, 348, 641, 210, 94, 17, GameFlag(5573))
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_SetupTexturePan = {
    Call(SetTexPanner, 5, 0)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, -323)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 0)
        Set(LVar6, 0)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_tyd_07_Script_TexturePan_Update)
    EndThread
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_BindScripts_Pipes = {
    BindTrigger(TTYD64_tyd_07_Script_pipe1, 128, 50, 1, 0)
    BindTrigger(TTYD64_tyd_07_Script_pipe4, 128, 53, 1, 0)
    BindTrigger(TTYD64_tyd_07_Script_pipe5, 128, 54, 1, 0)
    BindTrigger(TTYD64_tyd_07_Script_pipe7, 128, 56, 1, 0)
    BindTrigger(TTYD64_tyd_07_Script_pipeB1, 128, 58, 1, 0)
    BindTrigger(TTYD64_tyd_07_Script_pipeB2, 128, 59, 1, 0)
    BindTrigger(TTYD64_tyd_07_Script_pipeB3, 128, 60, 1, 0)
    BindTrigger(TTYD64_tyd_07_Script_pipeB4, 128, 61, 1, 0)
    BindTrigger(TTYD64_tyd_07_Script_pipeB5, 128, 62, 1, 0)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_Main = {
    Set(GameByte(425), 43)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Set(MapVar(2), 1)
    Exec(TTYD64_tyd_07_Script_MakeEntities)
    Exec(TTYD64_tyd_07_Script_SetupMusic)
    Exec(TTYD64_tyd_07_Script_SetupTexturePan)
    Exec(TTYD64_tyd_07_Script_InitStuff)
    Exec(TTYD64_tyd_07_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_ScriptedSpring_Entity_Spring = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerActionState, 6)
    Wait(1)
    ExecGetTID(TTYD64_tyd_07_Script_ScriptedSpring_FollowCam, LVarA)
    Call(SetPlayerJumpscale, Float(0.7001953125))
    Call(PlayerJump, 639, 450, 19, 30)
    KillThread(LVarA)
    Call(SetPlayerActionState, 0)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Back_Init = {
    Thread
        Wait(42)
        Exec(TTYD64_tyd_07_Script_MovingPlatform_Back_1)
    EndThread
    Exec(TTYD64_tyd_07_Script_MovingPlatform_Back_2)
    Exec(TTYD64_tyd_07_Script_MovingPlatform_Back_3)
    Exec(TTYD64_tyd_07_Script_MovingPlatform_Back_4)
    Exec(TTYD64_tyd_07_Script_MovingPlatform_Back_5)
    Thread
        Wait(62)
        Exec(TTYD64_tyd_07_Script_MovingPlatform_Back_6)
    EndThread
    Exec(TTYD64_tyd_07_Script_MovingPlatform_Back_7)
    Exec(TTYD64_tyd_07_Script_MovingPlatform_Back_8)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_UpdateModels_GenericRotation_Z = {
    Set(LVar5, LVar0)
    Set(LVar6, LVar1)
    Set(LVar7, LVar2)
    Add(LVar3, 3)
    Call(RotateModel, LVar5, LVar3, 0, 0, LVar7)
    IfNe(LVar6, 0)
        Call(UpdateColliderTransform, LVar6)
    EndIf
    Wait(1)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_TexturePan_Update = {
    SetGroup(0)
    IfEq(LVar5, 1)
        IfEq(LVar6, 1)
            IfEq(LVar7, 1)
                IfEq(LVar8, 1)
                    Call(TTYD64_TexturePan_Simple)
                    Return
                EndIf
            EndIf
        EndIf
    EndIf
    Call(TTYD64_TexturePan_Complex)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVarA, (Bytecode) TTYD64_tyd_07_Script_CreateExitTriggers)
        Exec(TTYD64_tyd_07_Script_EnterVerticalPipe)
    CaseDefault
        Exec(TTYD64_tyd_07_Script_CreateExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatform_Front_1 = {
    Set(LVar0, 51)
    Set(LVar1, 18)
    Set(LVar2, 147)
    Set(LVar3, 64)
    Set(LVar4, 1)
    ExecWait(TTYD64_tyd_07_Script_MovingPlatform_Main)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatform_Front_3 = {
    Set(LVar0, 59)
    Set(LVar1, 20)
    Set(LVar2, 206)
    Set(LVar3, 90)
    Set(LVar4, 0)
    ExecWait(TTYD64_tyd_07_Script_MovingPlatform_Main)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatform_Front_2 = {
    Set(LVar0, 55)
    Set(LVar1, 19)
    Set(LVar2, -126)
    Set(LVar3, 55)
    Set(LVar4, 0)
    ExecWait(TTYD64_tyd_07_Script_MovingPlatform_Main)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatform_Front_5 = {
    Set(LVar0, 67)
    Set(LVar1, 22)
    Set(LVar2, -89)
    Set(LVar3, 90)
    Set(LVar4, 0)
    ExecWait(TTYD64_tyd_07_Script_MovingPlatform_Main)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatform_Front_4 = {
    Set(LVar0, 63)
    Set(LVar1, 21)
    Set(LVar2, 124)
    Set(LVar3, 90)
    Set(LVar4, 1)
    ExecWait(TTYD64_tyd_07_Script_MovingPlatform_Main)
    Return
    End
};

u8 TTYD64_tyd_07_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x29, 0x53, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7,
    0x53, 0x4F, 0x4D, 0x45, 0xF7, 0x4B, 0x49, 0x4E, 0x44, 0xF7, 0x4F, 0x46,
    0xF7, 0x46, 0x41, 0x43, 0x54, 0x4F, 0x52, 0x59, 0x1F, 0xF0, 0x29, 0xF7,
    0x57, 0x4F, 0x4E, 0x44, 0x45, 0x52, 0xF7, 0x57, 0x48, 0x41, 0x54, 0xF7,
    0x54, 0x48, 0x45, 0x59, 0xF7, 0x4D, 0x41, 0x4B, 0x45, 0x0C, 0xF7, 0x29,
    0xF7, 0x48, 0x4F, 0x50, 0x45, 0xF0, 0x41, 0x54, 0xF7, 0x4C, 0x45, 0x41,
    0x53, 0x54, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0x54, 0x48, 0x49, 0x4E, 0x47,
    0xF7, 0x52, 0x45, 0x41, 0x4C, 0x4C, 0x59, 0xF7, 0x43, 0x4F, 0x4F, 0x4C,
    0x01, 0xF1, 0xFD
};

EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_1 = {
    Set(LVar0, 115)
    Set(LVar1, 92)
    Set(LVar2, 157)
    Set(LVar3, 68)
    Set(LVar4, 0)
    ExecWait(TTYD64_tyd_07_Script_MovingPlatform_Main)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_2 = {
    Set(LVar0, 118)
    Set(LVar1, 93)
    Set(LVar2, 97)
    Set(LVar3, 42)
    Set(LVar4, 0)
    ExecWait(TTYD64_tyd_07_Script_MovingPlatform_Main)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_3 = {
    Set(LVar0, 121)
    Set(LVar1, 94)
    Set(LVar2, 100)
    Set(LVar3, 84)
    Set(LVar4, 1)
    ExecWait(TTYD64_tyd_07_Script_MovingPlatform_Main)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_4 = {
    Set(LVar0, 124)
    Set(LVar1, 95)
    Set(LVar2, 200)
    Set(LVar3, 87)
    Set(LVar4, 1)
    ExecWait(TTYD64_tyd_07_Script_MovingPlatform_Main)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_5 = {
    Set(LVar0, 127)
    Set(LVar1, 96)
    Set(LVar2, 218)
    Set(LVar3, 95)
    Set(LVar4, 1)
    ExecWait(TTYD64_tyd_07_Script_MovingPlatform_Main)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_6 = {
    Set(LVar0, 130)
    Set(LVar1, 97)
    Set(LVar2, 143)
    Set(LVar3, 62)
    Set(LVar4, 0)
    ExecWait(TTYD64_tyd_07_Script_MovingPlatform_Main)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_7 = {
    Set(LVar0, 133)
    Set(LVar1, 98)
    Set(LVar2, 142)
    Set(LVar3, 62)
    Set(LVar4, 1)
    ExecWait(TTYD64_tyd_07_Script_MovingPlatform_Main)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatform_Back_8 = {
    Set(LVar0, 136)
    Set(LVar1, 99)
    Set(LVar2, -142)
    Set(LVar3, 62)
    Set(LVar4, 1)
    ExecWait(TTYD64_tyd_07_Script_MovingPlatform_Main)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Front_Init = {
    Exec(TTYD64_tyd_07_Script_MovingPlatform_Front_1)
    Exec(TTYD64_tyd_07_Script_MovingPlatform_Front_2)
    Exec(TTYD64_tyd_07_Script_MovingPlatform_Front_3)
    Thread
        Wait(90)
        Exec(TTYD64_tyd_07_Script_MovingPlatform_Front_4)
    EndThread
    Exec(TTYD64_tyd_07_Script_MovingPlatform_Front_5)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_ScriptedSpring_FollowCam = {
    Loop(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetCamTarget, 0, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Gear4 = {
    Loop(0)
        Set(LVar0, 146)
        Set(LVar1, 103)
        Set(LVar2, -1)
        ExecWait(TTYD64_tyd_07_Script_UpdateModels_GenericRotation_Z)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Gear5 = {
    Loop(0)
        Set(LVar0, 148)
        Set(LVar1, 104)
        Set(LVar2, 1)
        ExecWait(TTYD64_tyd_07_Script_UpdateModels_GenericRotation_Z)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Gear1 = {
    Loop(0)
        Set(LVar0, 140)
        Set(LVar1, 100)
        Set(LVar2, -1)
        ExecWait(TTYD64_tyd_07_Script_UpdateModels_GenericRotation_Z)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Gear2 = {
    Loop(0)
        Set(LVar0, 142)
        Set(LVar1, 101)
        Set(LVar2, 1)
        ExecWait(TTYD64_tyd_07_Script_UpdateModels_GenericRotation_Z)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Gear3 = {
    Loop(0)
        Set(LVar0, 144)
        Set(LVar1, 102)
        Set(LVar2, 1)
        ExecWait(TTYD64_tyd_07_Script_UpdateModels_GenericRotation_Z)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_pipe7 = {
    SetGroup(27)
    Set(LVarB, 56)
    Set(LVarC, 62)
    Set(LVarD, 1)
    Exec(TTYD64_tyd_07_Script_ExitVerticalPipe_NoGoToMap)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_pipe1 = {
    SetGroup(27)
    Set(LVarB, 50)
    Set(LVarC, 58)
    Set(LVarD, 1)
    Exec(TTYD64_tyd_07_Script_ExitVerticalPipe_NoGoToMap)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_pipe5 = {
    SetGroup(27)
    Set(LVarB, 54)
    Set(LVarC, 52)
    Set(LVarD, 0)
    Exec(TTYD64_tyd_07_Script_ExitVerticalPipe_NoGoToMap)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_pipe4 = {
    SetGroup(27)
    Set(LVarB, 53)
    Set(LVarC, 60)
    Set(LVarD, 1)
    Exec(TTYD64_tyd_07_Script_ExitVerticalPipe_NoGoToMap)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_Exit0 = {
    SetGroup(27)
    Set(LVarA, 0)
    Set(LVarB, 1)
    Set(LVarC, (Bytecode) TTYD64_tyd_07_Script_GotoMap_Exit0)
    ExecWait(TTYD64_tyd_07_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_pipeB5 = {
    SetGroup(27)
    Set(LVarB, 62)
    Set(LVarC, 56)
    Set(LVarD, 0)
    Exec(TTYD64_tyd_07_Script_ExitVerticalPipe_NoGoToMap)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_pipeB4 = {
    SetGroup(27)
    Set(LVarB, 61)
    Set(LVarC, 55)
    Set(LVarD, 0)
    Exec(TTYD64_tyd_07_Script_ExitVerticalPipe_NoGoToMap)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_pipeB1 = {
    SetGroup(27)
    Set(LVarB, 58)
    Set(LVarC, 50)
    Set(LVarD, 0)
    Exec(TTYD64_tyd_07_Script_ExitVerticalPipe_NoGoToMap)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_pipeB3 = {
    SetGroup(27)
    Set(LVarB, 60)
    Set(LVarC, 53)
    Set(LVarD, 0)
    Exec(TTYD64_tyd_07_Script_ExitVerticalPipe_NoGoToMap)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_pipeB2 = {
    SetGroup(27)
    Set(LVarB, 59)
    Set(LVarC, 51)
    Set(LVarD, 0)
    Exec(TTYD64_tyd_07_Script_ExitVerticalPipe_NoGoToMap)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatform_UpdateMarioXPos_Right = {
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Add(LVar0, 2)
    Call(SetPlayerPos, LVar0, LVar1, LVar2)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatform_UpdateMarioXPos_Left = {
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Sub(LVar0, 2)
    Call(SetPlayerPos, LVar0, LVar1, LVar2)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_MovingPlatforms_Gears_Init = {
    Exec(TTYD64_tyd_07_Script_MovingPlatforms_Gear1)
    Exec(TTYD64_tyd_07_Script_MovingPlatforms_Gear2)
    Exec(TTYD64_tyd_07_Script_MovingPlatforms_Gear3)
    Exec(TTYD64_tyd_07_Script_MovingPlatforms_Gear4)
    Exec(TTYD64_tyd_07_Script_MovingPlatforms_Gear5)
    Return
    End
};

MapSettings TTYD64_tyd_07_Header = {
    .main = TTYD64_tyd_07_Script_Main,
    .entryList = &TTYD64_tyd_07_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_tyd_07_GetTattle },
};

EvtScript TTYD64_tyd_07_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(5570))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_Entity_Shine2 = {
    Set(LVar0, MapVar(1))
    SetConst(LVar1, GameFlag(5571))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_SetupMusic = {
    Call(SetMusic, 0, 172, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_tyd_07_Script_GotoMap_Exit0 = {
    Call(GotoMap, (Bytecode) "sam_13", 1)
    Wait(100)
    Return
    End
};

s32 TTYD64_tyd_07_Function_Init(void) {
    sprintf(wMapTexName, "sam_tex");
    return false;
}

EvtScript TTYD64_tyd_07_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_tyd_07_Script_Exit0, 128, 1, 1, 0)
    Return
    End
};

EntryList TTYD64_tyd_07_EntryList = {
    { -641.0f, 32.0f, 100.0f, -270.0f },
};

MapConfig TTYD64_mapcfg_tyd_07 = {
    .id = "tyd_07",
    .settings = &TTYD64_tyd_07_Header,
    .bgName = NULL,
    .init = TTYD64_tyd_07_Function_Init,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_tp_Install_tyd_07(void) {
    TTYD64_tyd_07_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_tyd_07_String_Tattle);
}
