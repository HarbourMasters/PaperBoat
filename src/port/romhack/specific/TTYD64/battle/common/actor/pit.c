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

extern EvtScript TTYD64_imp_Pit_Script_EnterHorizontalPipe;
extern EvtScript TTYD64_imp_Pit_Script_EnterVerticalPipe;
extern EvtScript TTYD64_imp_Pit_Script_EnterTopPipe;
extern EvtScript TTYD64_imp_Pit_Script_ExitHorizontalPipe;
extern EvtScript TTYD64_imp_Pit_Script_UpdateNpcSpawnPos;
extern EvtScript TTYD64_imp_Pit_Script_SpawnNpcs;
extern EvtScript TTYD64_imp_Pit_Script_ExitVerticalPipe;
extern EvtScript TTYD64_imp_Pit_Script_SetupTexturePan;
extern EvtScript TTYD64_imp_Pit_Script_GoToNextMap;
extern u8 TTYD64_imp_Pit_String_Tattle_3[];
extern EvtScript TTYD64_imp_Pit_Script_ShowPipe;
extern u8 TTYD64_imp_Pit_String_Tattle_2[];
extern EvtScript TTYD64_imp_Pit_Script_MakeEntities;
extern EvtScript TTYD64_imp_Pit_Script_EnterMap;
extern EvtScript TTYD64_imp_Pit_Script_TexturePan_Update;
extern EvtScript TTYD64_imp_Pit_Script_UpdateFloorTheme;
extern EvtScript TTYD64_imp_Pit_Script_TrackOutcome;
extern u8 TTYD64_imp_Pit_String_Tattle_1[];
extern EvtScript TTYD64_imp_Pit_Script_InitEnemyNPC;
extern EvtScript TTYD64_imp_Pit_Script_ReadSign_Entity_Sign;
extern EvtScript TTYD64_imp_Pit_Script_Exit0;
s32 TTYD64_imp_Pit_Function_Init(void);
extern EvtScript TTYD64_imp_Pit_Script_GotoMap_Exit0;
extern EvtScript TTYD64_imp_Pit_Script_SetupMusic;
extern EvtScript TTYD64_imp_Pit_Script_CreateExitTriggers;
extern EntryList TTYD64_imp_Pit_EntryList;
extern NpcGroupList TTYD64_imp_Pit_NpcGroupList_pit;
extern u8 TTYD64_imp_Pit_String_ReadSign_Entity_Sign[];
extern char TTYD64_imp_Pit_ASCII_NextFloor[];

// clang-format off
EvtScript TTYD64_imp_Pit_Script_EnterHorizontalPipe = {
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

EvtScript TTYD64_imp_Pit_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_imp_Pit_Script_EnterTopPipe = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(HidePlayerShadow, 1)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Call(DisablePartnerAI, 0)
        Call(EnableNpcShadow, -4, 0)
        Call(SetNpcFlagBits, -4, 2, 1)
        Call(SetNpcPos, -4, 0, LVarA, 0)
    EndIf
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
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(SetPlayerImgFXFlags, 256)
    Call(UpdatePlayerImgFX, 0x10000, 5, 2, 1, 1, 0)
    Wait(4)
    Call(PlaySound, 355)
    Loop(40)
        Sub(LVar1, 1)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Wait(1)
    Call(UpdatePlayerImgFX, 0x10000, 0, 0, 0, 0, 0)
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Call(HidePlayerShadow, 0)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Wait(4)
        Call(GetPlayerPos, LVar4, LVar5, LVar6)
        Call(SetNpcPos, -4, LVar4, LVar5, LVar6)
        Call(SetNpcFlagBits, -4, 2, 0)
        Call(EnablePartnerAI)
        Call(EnableNpcShadow, -4, 1)
    EndIf
    Exec(LVarC)
    Return
    End
};

EvtScript TTYD64_imp_Pit_Script_ExitHorizontalPipe = {
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

EvtScript TTYD64_imp_Pit_Script_UpdateNpcSpawnPos = {
    Call(RandInt, 1, LVar0)
    IfEq(LVar0, 0)
        Call(RandInt, 177, LVar0)
        Mul(LVar0, -1)
    Else
        Call(RandInt, 192, LVar0)
    EndIf
    Call(RandInt, 1, LVar2)
    IfEq(LVar2, 0)
        Call(RandInt, 26, LVar2)
        Mul(LVar2, -1)
        Add(LVar2, -132)
    Else
        Call(RandInt, 68, LVar2)
    EndIf
    Call(TTYD64_GetEnemyPointer, 0, LVar6)
    Call(TTYD64_ReadPtrField, LVar6, TTYD64_F_ENEMY_D0_4U, LVar6)
    Call(GetNpcPos, 0, LVar3, LVar4, LVar5)
    Add(LVar3, LVar0)
    Add(LVar5, LVar2)
    Call(SetNpcPos, 0, LVar3, LVar4, LVar5)
    Call(TTYD64_tp_TerritoryWrite, LVar6, 2, LVar3, 0, 0)
    Call(TTYD64_tp_TerritoryWrite, LVar6, 2, LVar5, 8, 0)
    Call(TTYD64_tp_TerritoryWrite, LVar6, 2, LVar3, 28, 0)
    Call(TTYD64_tp_TerritoryWrite, LVar6, 2, LVar5, 36, 0)
    Switch(AreaByte(0))
    CaseOrEq(12)
    CaseOrEq(17)
        Call(TTYD64_GetEnemyPointer, 1, LVar6)
        Call(TTYD64_ReadPtrField, LVar6, TTYD64_F_ENEMY_D0_4U, LVar6)
        Call(SetNpcPos, 1, LVar3, LVar4, LVar5)
        Call(TTYD64_tp_TerritoryWrite, LVar6, 2, LVar3, 0, 0)
        Call(TTYD64_tp_TerritoryWrite, LVar6, 2, LVar5, 8, 0)
        Call(TTYD64_tp_TerritoryWrite, LVar6, 2, LVar3, 28, 0)
        Call(TTYD64_tp_TerritoryWrite, LVar6, 2, LVar5, 36, 0)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_imp_Pit_Script_SpawnNpcs = {
    Set(LVar2, AreaByte(0))
    Set(LVar1, LVar2)
    Div(LVar2, 10)
    Mul(LVar2, 10)
    Sub(LVar1, LVar2)
    IfGt(LVar1, 5)
        Sub(LVar1, 5)
    EndIf
    Sub(LVar1, 1)
    Set(LVar4, LVar1)
    Set(LVar2, 8)
    Mul(LVar2, LVar1)
    Add(LVar0, LVar2)
    Call(TTYD64_tp_PitNpcsRead, LVar0, 2, LVar1, 0, 0)
    Call(TTYD64_tp_PitNpcsRead, LVar0, 2, LVar2, 4, 0)
    IfGt(LVar1, 0xFFFF)
        Set(LVarA, LVar1)
    Else
        Set(LVarA, (Bytecode) TTYD64_imp_Pit_NpcGroupList_pit)
        Call(TTYD64_tp_PitGroupWrite, LVarA, 2, LVar1, 0, 0)
        Call(TTYD64_tp_PitGroupWrite, LVarA, 2, LVar2, 4, 0)
    EndIf
    Set(LVar2, AreaByte(0))
    Div(LVar2, 10)
    Set(LVar1, 48)
    Add(LVar1, LVar2)
    Call(TTYD64_tp_PitGroupWrite, LVarA, 0, LVar1, 8, 0)
    Set(LVar1, 3)
    Mul(LVar1, LVar4)
    Call(RandInt, 100, LVar2)
    Switch(LVar2)
    CaseLt(20)
        Set(LVar3, 2)
    CaseLt(65)
        Set(LVar3, 1)
    CaseLt(101)
        Set(LVar3, 0)
    EndSwitch
    Add(LVar1, LVar3)
    Call(TTYD64_tp_PitGroupWrite, LVarA, 0, LVar1, 9, 0)
    Call(MakeNpcs, 0, LVarA)
    Exec(TTYD64_imp_Pit_Script_InitEnemyNPC)
    Return
    End
};

EvtScript TTYD64_imp_Pit_Script_ExitVerticalPipe = {
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

EvtScript TTYD64_imp_Pit_Script_SetupTexturePan = {
    Call(SetTexPanner, 9, 1)
    Call(SetTexPanner, 16, 1)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 50)
        Set(LVar2, 200)
        Set(LVar3, 110)
        Set(LVar4, 500)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_imp_Pit_Script_TexturePan_Update)
    EndThread
    Thread
        Set(LVar0, 1)
        Set(LVar1, 0)
        Set(LVar2, -200)
        Set(LVar3, -100)
        Set(LVar4, -500)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_imp_Pit_Script_TexturePan_Update)
    EndThread
    Return
    End
};

EvtScript TTYD64_imp_Pit_Script_GoToNextMap = {
    Set(LVar5, LVar0)
    IfGe(LVar0, 100)
        Call(GotoMap, (Bytecode) "pit_12", 0)
    Else
        Call(TTYD64_tp_GetReminderFromDiv, LVar5, 10, LVar1)
        IfEq(LVar1, 0)
            Call(TTYD64_tp_SetNextFloorDigit, (Bytecode) TTYD64_imp_Pit_ASCII_NextFloor, TTYD64_TP_FLOOR_TENS, 49)
            Call(TTYD64_tp_SetNextFloorDigit, (Bytecode) TTYD64_imp_Pit_ASCII_NextFloor, TTYD64_TP_FLOOR_ONES, 49)
        Else
            Set(LVar1, LVar0)
            Div(LVar1, 10)
            Set(LVar0, 49)
            IfNe(LVar1, 9)
                Add(LVar0, LVar1)
                Call(TTYD64_tp_SetNextFloorDigit, (Bytecode) TTYD64_imp_Pit_ASCII_NextFloor, TTYD64_TP_FLOOR_ONES, LVar0)
            Else
                Call(TTYD64_tp_SetNextFloorDigit, (Bytecode) TTYD64_imp_Pit_ASCII_NextFloor, TTYD64_TP_FLOOR_TENS, LVar0)
            EndIf
        EndIf
        Call(GotoMap, (Bytecode) TTYD64_imp_Pit_ASCII_NextFloor, 0)
    EndIf
    Set(AreaByte(0), LVar5)
    Wait(100)
    Return
    End
};

u8 TTYD64_imp_Pit_String_Tattle_3[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x34, 0x48, 0x49, 0x53, 0xF7, 0x49, 0x53, 0xF7,
    0x54, 0x48, 0x45, 0xF7, 0x50, 0x49, 0x54, 0xF7, 0x4F, 0x46, 0xF7, 0x11,
    0x10, 0x10, 0xF7, 0x54, 0x52, 0x49, 0x41, 0x4C, 0x53, 0x0C, 0xF0, 0x54,
    0x48, 0x49, 0x53, 0xF7, 0x50, 0x4C, 0x41, 0x43, 0x45, 0xF7, 0x53, 0x45,
    0x45, 0x4D, 0x53, 0xF7, 0x54, 0x4F, 0xF7, 0x48, 0x41, 0x56, 0x45, 0xF7,
    0x4E, 0x4F, 0xF7, 0x45, 0x4E, 0x44, 0x0C, 0xF0, 0x29, 0xF7, 0x57, 0x4F,
    0x4E, 0x44, 0x45, 0x52, 0xF7, 0x57, 0x48, 0x45, 0x4E, 0xF7, 0x57, 0x45,
    0x07, 0x4C, 0x4C, 0xF7, 0x47, 0x45, 0x54, 0xF7, 0x54, 0x4F, 0xF7, 0x54,
    0x48, 0x45, 0xF0, 0x45, 0x4E, 0x44, 0x0E, 0x0E, 0x0E, 0xF0, 0xF1, 0xFB,
    0x29, 0x53, 0x4E, 0x07, 0x54, 0xF7, 0x45, 0x41, 0x53, 0x59, 0xF7, 0x54,
    0x4F, 0xF7, 0x42, 0x52, 0x45, 0x41, 0x54, 0x48, 0x45, 0xF7, 0x4F, 0x4E,
    0xF7, 0x54, 0x48, 0x45, 0x53, 0x45, 0xF0, 0x46, 0x4C, 0x4F, 0x4F, 0x52,
    0x53, 0x0C, 0xF7, 0x57, 0x45, 0x07, 0x52, 0x45, 0xF7, 0x56, 0x45, 0x52,
    0x59, 0xF7, 0x44, 0x45, 0x45, 0x50, 0xF7, 0x49, 0x4E, 0xF7, 0x54, 0x48,
    0x45, 0xF7, 0x50, 0x49, 0x54, 0x0C, 0xF0, 0x41, 0x4E, 0x44, 0xF7, 0x54,
    0x48, 0x45, 0xF7, 0x57, 0x41, 0x54, 0x45, 0x52, 0xF7, 0x44, 0x4F, 0x45,
    0x53, 0x4E, 0x07, 0x54, 0xF7, 0x45, 0x56, 0x45, 0x4E, 0xF7, 0x43, 0x4F,
    0x4D, 0x45, 0xF7, 0x4F, 0x55, 0x54, 0xF0, 0x4F, 0x46, 0xF7, 0x54, 0x48,
    0x45, 0xF7, 0x44, 0x52, 0x41, 0x49, 0x4E, 0xF7, 0x41, 0x4E, 0x59, 0x4D,
    0x4F, 0x52, 0x45, 0x0C, 0xF0, 0xF1, 0xFB, 0x2D, 0x41, 0x52, 0x49, 0x4F,
    0x0C, 0xF7, 0x4E, 0x4F, 0x57, 0xF7, 0x29, 0xF7, 0x57, 0x4F, 0x4E, 0x44,
    0x45, 0x52, 0xF7, 0x48, 0x4F, 0x57, 0xF7, 0x54, 0x48, 0x45, 0x59, 0xF7,
    0x43, 0x4C, 0x45, 0x41, 0x4E, 0xF0, 0x54, 0x48, 0x45, 0x53, 0x45, 0xF7,
    0x46, 0x4C, 0x4F, 0x4F, 0x52, 0x53, 0xF7, 0x41, 0x43, 0x54, 0x55, 0x41,
    0x4C, 0x4C, 0x59, 0x0C, 0xF7, 0x45, 0x57, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_imp_Pit_Script_ShowPipe = {
    Call(DisablePlayerInput, 1)
    Call(PlaySound, 8334)
    Call(MakeLerp, -40, 0, 25, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, 1, 0, LVar0, 10)
        Call(UpdateColliderTransform, 7)
        Call(UpdateColliderTransform, 6)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(DisablePlayerInput, 0)
    Return
    End
};

u8 TTYD64_imp_Pit_String_Tattle_2[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x34, 0x48, 0x49, 0x53, 0xF7, 0x49, 0x53, 0xF7,
    0x54, 0x48, 0x45, 0xF7, 0x50, 0x49, 0x54, 0xF7, 0x4F, 0x46, 0xF7, 0x11,
    0x10, 0x10, 0xF7, 0x54, 0x52, 0x49, 0x41, 0x4C, 0x53, 0x0C, 0xF0, 0x54,
    0x48, 0x49, 0x53, 0xF7, 0x50, 0x4C, 0x41, 0x43, 0x45, 0xF7, 0x53, 0x45,
    0x45, 0x4D, 0x53, 0xF7, 0x54, 0x4F, 0xF7, 0x48, 0x41, 0x56, 0x45, 0xF7,
    0x4E, 0x4F, 0xF7, 0x45, 0x4E, 0x44, 0x0C, 0xF0, 0x29, 0xF7, 0x57, 0x4F,
    0x4E, 0x44, 0x45, 0x52, 0xF7, 0x57, 0x48, 0x45, 0x4E, 0xF7, 0x57, 0x45,
    0x07, 0x4C, 0x4C, 0xF7, 0x47, 0x45, 0x54, 0xF7, 0x54, 0x4F, 0xF7, 0x54,
    0x48, 0x45, 0xF0, 0x45, 0x4E, 0x44, 0x0E, 0x0E, 0x0E, 0xF0, 0xF1, 0xFB,
    0x34, 0x48, 0x45, 0xF7, 0x41, 0x49, 0x52, 0xF7, 0x53, 0x45, 0x45, 0x4D,
    0x53, 0xF7, 0x54, 0x4F, 0xF7, 0x42, 0x45, 0xF7, 0x41, 0xF7, 0x4C, 0x49,
    0x54, 0x54, 0x4C, 0x45, 0xF7, 0x54, 0x48, 0x49, 0x4E, 0x4E, 0x45, 0x52,
    0x0C, 0xF0, 0x57, 0x45, 0xF7, 0x41, 0x52, 0x45, 0xF7, 0x41, 0x4C, 0x52,
    0x45, 0x41, 0x44, 0x59, 0xF7, 0x51, 0x55, 0x49, 0x54, 0x45, 0xF7, 0x44,
    0x45, 0x45, 0x50, 0xF7, 0x49, 0x4E, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x50,
    0x49, 0x54, 0x0C, 0xF0, 0x29, 0xF7, 0x4A, 0x55, 0x53, 0x54, 0xF7, 0x57,
    0x4F, 0x4E, 0x44, 0x45, 0x52, 0xF7, 0x57, 0x48, 0x45, 0x4E, 0xF7, 0x49,
    0x54, 0xF7, 0x57, 0x49, 0x4C, 0x4C, 0xF7, 0x46, 0x49, 0x4E, 0x49, 0x53,
    0x48, 0x0E, 0xF1, 0xFD
};

EvtScript TTYD64_imp_Pit_Script_MakeEntities = {
    Set(GameFlag(4734), 0)
    Call(MakeEntity, Ref(Entity_BlueWarpPipe), 16, 0, 35, 0, 0, 0, 4734, 0x80000000)
    Call(MakeEntity, Ref(Entity_Signpost), -84, -9, -112, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_imp_Pit_Script_ReadSign_Entity_Sign)
    IfEq(MapVar(0), 1)
        Call(MakeEntity, Ref(Entity_BlueSwitch), 62, 0, 97, 0, 0x80000000)
        Call(AssignScript, (Bytecode) TTYD64_imp_Pit_Script_ShowPipe)
    EndIf
    Return
    End
};

EvtScript TTYD64_imp_Pit_Script_EnterMap = {
    Set(LVarA, 0)
    Set(LVarB, 3)
    Set(LVarC, (Bytecode) TTYD64_imp_Pit_Script_CreateExitTriggers)
    Exec(TTYD64_imp_Pit_Script_EnterTopPipe)
    Call(ParentColliderToModel, 6, 1)
    Call(ParentColliderToModel, 7, 1)
    Call(TranslateModel, 1, 0, -40, 0)
    Call(UpdateColliderTransform, 6)
    Call(UpdateColliderTransform, 7)
    Exec(TTYD64_imp_Pit_Script_UpdateFloorTheme)
    Return
    End
};

EvtScript TTYD64_imp_Pit_Script_TexturePan_Update = {
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

EvtScript TTYD64_imp_Pit_Script_UpdateFloorTheme = {
    Call(EnableGroup, 24, 0)
    Switch(AreaByte(0))
    CaseGe(80)
        Call(EnableGroup, 23, 1)
    CaseGe(50)
        Call(EnableGroup, 17, 1)
    CaseDefault
        Call(EnableGroup, 10, 1)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_imp_Pit_Script_TrackOutcome = {
    Call(GetBattleOutcome, LVar0)
    IfEq(LVar0, 0)
        Thread
            Wait(10)
            Exec(TTYD64_imp_Pit_Script_ShowPipe)
        EndThread
        Call(DoNpcDefeat)
    EndIf
    Return
    End
};

u8 TTYD64_imp_Pit_String_Tattle_1[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x34, 0x48, 0x49, 0x53, 0xF7, 0x49, 0x53, 0xF7,
    0x54, 0x48, 0x45, 0xF7, 0x50, 0x49, 0x54, 0xF7, 0x4F, 0x46, 0xF7, 0x11,
    0x10, 0x10, 0xF7, 0x54, 0x52, 0x49, 0x41, 0x4C, 0x53, 0x0C, 0xF0, 0x54,
    0x48, 0x49, 0x53, 0xF7, 0x50, 0x4C, 0x41, 0x43, 0x45, 0xF7, 0x53, 0x45,
    0x45, 0x4D, 0x53, 0xF7, 0x54, 0x4F, 0xF7, 0x48, 0x41, 0x56, 0x45, 0xF7,
    0x4E, 0x4F, 0xF7, 0x45, 0x4E, 0x44, 0x0C, 0xF0, 0x29, 0xF7, 0x57, 0x4F,
    0x4E, 0x44, 0x45, 0x52, 0xF7, 0x57, 0x48, 0x45, 0x4E, 0xF7, 0x57, 0x45,
    0x07, 0x4C, 0x4C, 0xF7, 0x47, 0x45, 0x54, 0xF7, 0x54, 0x4F, 0xF7, 0x54,
    0x48, 0x45, 0xF0, 0x45, 0x4E, 0x44, 0xF7, 0xF1, 0xFD
};

EvtScript TTYD64_imp_Pit_Script_InitEnemyNPC = {
    Switch(AreaByte(0))
    CaseOrEq(23)
    CaseOrEq(28)
        EndCaseGroup
    CaseDefault
        Call(BindNpcDefeat, 0, (Bytecode) TTYD64_imp_Pit_Script_TrackOutcome)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_imp_Pit_Script_ReadSign_Entity_Sign = {
    Call(DisablePlayerInput, 1)
    Call(SetMessageValue, AreaByte(0), 0)
    Call(ShowMessageAtScreenPos, (Bytecode) TTYD64_imp_Pit_String_ReadSign_Entity_Sign, 160, 40)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_imp_Pit_Script_Exit0 = {
    SetGroup(27)
    Set(LVarA, 1)
    Set(LVarB, 6)
    Set(LVarC, (Bytecode) TTYD64_imp_Pit_Script_GotoMap_Exit0)
    ExecWait(TTYD64_imp_Pit_Script_ExitVerticalPipe)
    Return
    End
};

s32 TTYD64_imp_Pit_Function_Init(void) {
    sprintf(wMapTexName, "tik_tex");
    sprintf(wMapHitName, "pit_01_hit");
    sprintf(wMapShapeName, "pit_01_shape");
    return false;
}

EvtScript TTYD64_imp_Pit_Script_GotoMap_Exit0 = {
    Set(LVar0, AreaByte(0))
    Add(LVar0, 1)
    ExecWait(TTYD64_imp_Pit_Script_GoToNextMap)
    Return
    End
};

EvtScript TTYD64_imp_Pit_Script_SetupMusic = {
    Call(SetMusic, 0, 75, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_imp_Pit_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_imp_Pit_Script_Exit0, 128, 6, 1, 0)
    Return
    End
};

EntryList TTYD64_imp_Pit_EntryList = {
    { 17.0f, 149.0f, 15.0f, -270.0f },
    { 17.0f, 28.0f, 25.0f, -270.0f },
};

NpcGroupList TTYD64_imp_Pit_NpcGroupList_pit = {
    { .npcCount = 1, .npcs = NULL, .battle = 0x3000, .stage = 0 },
    {},
};

u8 TTYD64_imp_Pit_String_ReadSign_Entity_Sign[] = {
    0xFF, 0x09, 0xFC, 0x07, 0xFF, 0x29, 0xFF, 0xFF, 0x13, 0x10, 0x26, 0x4C,
    0x4F, 0x4F, 0x52, 0xF7, 0xFF, 0x28, 0x00, 0xFF, 0x0A, 0xF1, 0xFD
};

char TTYD64_imp_Pit_ASCII_NextFloor[12] = "pit_00";
// clang-format on

void TTYD64_tp_Install_imp_Pit(void) {
    TTYD64_tp_BindMessage(TTYD64_imp_Pit_Script_ReadSign_Entity_Sign, TTYD64_imp_Pit_String_ReadSign_Entity_Sign);
}
