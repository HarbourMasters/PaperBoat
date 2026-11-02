#include "common.h"
#include "effects.h"
#include "entity.h"
#include "foliage.h"
#include "map.h"
#include "npc.h"
#include "script_api/map.h"
#include <string.h>
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/world/maps.h"

extern EvtScript tik_03_EVS_BindExitTriggers;
extern EvtScript tik_03_EVS_EnterMap;
extern EvtScript tik_03_EVS_ExitPipe_tik_04_2;
extern EvtScript tik_03_EVS_ExitWalk_tik_01_1;
extern EvtScript tik_03_EVS_MakeEntities;
extern EvtScript tik_03_EVS_Pipe_EnterHorizontal;
extern EvtScript tik_03_EVS_SetupMusic;
extern MapSettings tik_03_settings;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableModel);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GetCurrentPartnerID);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetPartnerInUse);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(HidePlayerShadow);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(InterruptUsePartner);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerFlagBits);
API_CALLABLE(SetPlayerImgFXFlags);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(UpdatePlayerImgFX);

extern EvtScript TTYD64_tik_03_Script_80240B40;
extern EvtScript TTYD64_tik_03_Script_GoToMapPipe;
extern EvtScript TTYD64_tik_03_Script_UpdateModelTransparency;
extern EvtScript TTYD64_tik_03_Script_EnterVerticalPipe;
extern EvtScript TTYD64_tik_03_Script_ExitVerticalPipe;
extern EvtScript TTYD64_tik_03_Script_80241A20;
extern EvtScript TTYD64_tik_03_Script_EnterWalk_80241A68;
extern EvtScript TTYD64_tik_03_Script_MakeEntities;
extern EntryList TTYD64_tik_03_EntryList;
extern EvtScript TTYD64_tik_03_Script_InitNewStuff;
extern EvtScript TTYD64_tik_03_Script_BlastWall;
extern EvtScript TTYD64_tik_03_Script_UpdateWall;
extern EvtScript TTYD64_tik_03_Script_Pipe10;
extern EvtScript TTYD64_tik_03_Script_Pipe6;
extern EvtScript TTYD64_tik_03_Script_Pipe7;
extern EvtScript TTYD64_tik_03_Script_Pipe8;
extern EvtScript TTYD64_tik_03_Script_Pipe9;
extern EvtScript TTYD64_tik_03_Script_Pipe1;
extern EvtScript TTYD64_tik_03_Script_Pipe2;
extern EvtScript TTYD64_tik_03_Script_Pipe3;
extern EvtScript TTYD64_tik_03_Script_Pipe4;
extern EvtScript TTYD64_tik_03_Script_Pipe5;
extern EvtScript TTYD64_tik_03_Script_Entity_Shine1;
extern BombTrigger TTYD64_tik_03_TriggerCoord_Door;

// clang-format off
EvtScript TTYD64_tik_03_Script_80240B40 = {
    Call(SetMusic, 0, 75, 0, 8)
    Exec(TTYD64_tik_03_Script_InitNewStuff)
    Return
    End
};

EvtScript TTYD64_tik_03_Script_GoToMapPipe = {
    Call(GotoMap, (Bytecode) "tik_03", LVarD)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_tik_03_Script_UpdateModelTransparency = {
    Loop(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        IfGt(LVar1, 241)
            Set(LVar0, 43)
            Set(LVar1, 0)
            Set(LVar2, 15)
            Exec(TTYD64_Script_UpdateModelAlpha)
            Wait(15)
            Call(EnableModel, 43, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tik_03_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_tik_03_Script_ExitVerticalPipe = {
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

EvtScript TTYD64_tik_03_Script_80241A20 = {
    BindTrigger(tik_03_EVS_ExitWalk_tik_01_1, 0x80000, 17, 1, 0)
    BindTrigger(tik_03_EVS_ExitPipe_tik_04_2, 64, 6, 1, 0)
    BindTrigger(TTYD64_tik_03_Script_Pipe1, 128, 21, 1, 0)
    BindTrigger(TTYD64_tik_03_Script_Pipe2, 128, 22, 1, 0)
    BindTrigger(TTYD64_tik_03_Script_Pipe3, 128, 23, 1, 0)
    BindTrigger(TTYD64_tik_03_Script_Pipe4, 128, 24, 1, 0)
    BindTrigger(TTYD64_tik_03_Script_Pipe5, 128, 25, 1, 0)
    BindTrigger(TTYD64_tik_03_Script_Pipe6, 128, 26, 1, 0)
    BindTrigger(TTYD64_tik_03_Script_Pipe7, 128, 27, 1, 0)
    BindTrigger(TTYD64_tik_03_Script_Pipe8, 128, 28, 1, 0)
    BindTrigger(TTYD64_tik_03_Script_Pipe9, 128, 29, 1, 0)
    BindTrigger(TTYD64_tik_03_Script_Pipe10, 128, 30, 1, 0)
    Return
    End
};

EvtScript TTYD64_tik_03_Script_EnterWalk_80241A68 = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(1)
        Set(LVarA, Ref(tik_03_EVS_BindExitTriggers))
        Set(LVarB, 6)
        Exec(tik_03_EVS_Pipe_EnterHorizontal)
    CaseOrEq(4)
    CaseOrEq(5)
    CaseOrEq(6)
    CaseOrEq(7)
    CaseOrEq(8)
    CaseOrEq(9)
    CaseOrEq(10)
    CaseOrEq(11)
    CaseOrEq(12)
    CaseOrEq(13)
        Set(LVarA, Ref(tik_03_EVS_BindExitTriggers))
        Exec(TTYD64_tik_03_Script_EnterVerticalPipe)
        EndCaseGroup
    CaseDefault
        Set(LVar0, Ref(tik_03_EVS_BindExitTriggers))
        Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_tik_03_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_YellowBlock), 200, 50, -75, 0, 129, 0x80000000)
    Call(AssignBlockFlag, GameFlag(400))
    Call(MakeEntity, Ref(Entity_YellowBlock), 140, 50, -75, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(401))
    Call(MakeEntity, Ref(Entity_YellowBlock), 260, 50, -75, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(402))
    Call(MakeEntity, Ref(Entity_YellowBlock), 200, 138, -67, 0, 149, 0x80000000)
    Call(AssignBlockFlag, GameFlag(4544))
    Return
    End
};

EntryList TTYD64_tik_03_EntryList = {
    { 320.0f, -10.0f, 0.0f, 270.0f },
    { -215.0f, 60.0f, 0.0f, 90.0f },
    { 260.0f, -10.0f, 0.0f, 270.0f },
    { 91.0f, 252.0f, 75.0f, 0.0f },
    { -83.0f, 287.0f, 83.0f, 90.0f },
    { 192.0f, 287.0f, 83.0f, 90.0f },
    { -217.0f, 378.0f, -115.0f, 90.0f },
    { -224.0f, 368.0f, -15.0f, 90.0f },
    { -224.0f, 368.0f, 51.0f, 90.0f },
    { -224.0f, 368.0f, 113.0f, 90.0f },
    { -43.0f, 383.0f, -119.0f, 90.0f },
    { 107.0f, 383.0f, -119.0f, 90.0f },
    { 328.0f, 378.0f, 125.0f, 90.0f },
    { 321.0f, 383.0f, -126.0f, 90.0f },
};

EvtScript TTYD64_tik_03_Script_InitNewStuff = {
    Exec(TTYD64_tik_03_Script_UpdateWall)
    Exec(TTYD64_tik_03_Script_UpdateModelTransparency)
    Call(MakeItemEntity, 348, 31, 348, -95, 17, GameFlag(4537))
    Call(MakeEntity, Ref(Entity_SuperBlock), 279, 413, -80, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(4538))
    Call(AssignScript, Ref(TTYD64_tik_03_Script_Entity_Shine1))
    Return
    End
};

EvtScript TTYD64_tik_03_Script_BlastWall = {
    Call(PlayEffect_impl, 66, 0, 33, 33, 1, 10, 30, 0, 0, 0, 0, 0, 0)
    Call(EnableGroup, 34, 0)
    Call(ModifyColliderFlags, 0, 32, 0x7FFFFE00)
    Set(GameFlag(4536), 1)
    Unbind
    Return
    End
};

EvtScript TTYD64_tik_03_Script_UpdateWall = {
    IfEq(GameFlag(4536), 0)
        BindTrigger(TTYD64_tik_03_Script_BlastWall, 0x100000, Ref(TTYD64_tik_03_TriggerCoord_Door), 1, 0)
    Else
        Call(EnableGroup, 34, 0)
        Call(ModifyColliderFlags, 0, 32, 0x7FFFFE00)
    EndIf
    Return
    End
};

EvtScript TTYD64_tik_03_Script_Pipe10 = {
    SetGroup(27)
    Set(LVarA, 13)
    Set(LVarB, 30)
    Set(LVarC, Ref(TTYD64_tik_03_Script_GoToMapPipe))
    Set(LVarD, 9)
    ExecWait(TTYD64_tik_03_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tik_03_Script_Pipe6 = {
    SetGroup(27)
    Set(LVarA, 9)
    Set(LVarB, 26)
    Set(LVarC, Ref(TTYD64_tik_03_Script_GoToMapPipe))
    Set(LVarD, 10)
    ExecWait(TTYD64_tik_03_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tik_03_Script_Pipe7 = {
    SetGroup(27)
    Set(LVarA, 10)
    Set(LVarB, 27)
    Set(LVarC, Ref(TTYD64_tik_03_Script_GoToMapPipe))
    Set(LVarD, 9)
    ExecWait(TTYD64_tik_03_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tik_03_Script_Pipe8 = {
    SetGroup(27)
    Set(LVarA, 11)
    Set(LVarB, 28)
    Set(LVarC, Ref(TTYD64_tik_03_Script_GoToMapPipe))
    Set(LVarD, 13)
    ExecWait(TTYD64_tik_03_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tik_03_Script_Pipe9 = {
    SetGroup(27)
    Set(LVarA, 12)
    Set(LVarB, 29)
    Set(LVarC, Ref(TTYD64_tik_03_Script_GoToMapPipe))
    Set(LVarD, 8)
    ExecWait(TTYD64_tik_03_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tik_03_Script_Pipe1 = {
    SetGroup(27)
    Set(LVarA, 4)
    Set(LVarB, 21)
    Set(LVarC, Ref(TTYD64_tik_03_Script_GoToMapPipe))
    Set(LVarD, 6)
    ExecWait(TTYD64_tik_03_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tik_03_Script_Pipe2 = {
    SetGroup(27)
    Set(LVarA, 5)
    Set(LVarB, 22)
    Set(LVarC, Ref(TTYD64_tik_03_Script_GoToMapPipe))
    Set(LVarD, 7)
    ExecWait(TTYD64_tik_03_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tik_03_Script_Pipe3 = {
    SetGroup(27)
    Set(LVarA, 6)
    Set(LVarB, 23)
    Set(LVarC, Ref(TTYD64_tik_03_Script_GoToMapPipe))
    Set(LVarD, 4)
    ExecWait(TTYD64_tik_03_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tik_03_Script_Pipe4 = {
    SetGroup(27)
    Set(LVarA, 7)
    Set(LVarB, 24)
    Set(LVarC, Ref(TTYD64_tik_03_Script_GoToMapPipe))
    Set(LVarD, 5)
    ExecWait(TTYD64_tik_03_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tik_03_Script_Pipe5 = {
    SetGroup(27)
    Set(LVarA, 8)
    Set(LVarB, 25)
    Set(LVarC, Ref(TTYD64_tik_03_Script_GoToMapPipe))
    Set(LVarD, 12)
    ExecWait(TTYD64_tik_03_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tik_03_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(4538))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

BombTrigger TTYD64_tik_03_TriggerCoord_Door = {
    .pos = { 28.0f, 241.0f, -11.0f },
    .diameter = 20.0f
};
// clang-format on

void TTYD64_InstallMap_tik_03(void) {
    tik_03_settings.entryList = &TTYD64_tik_03_EntryList;
    tik_03_settings.entryCount = 14;
    Mod_ReplaceScript("TTYD64", &tik_03_EVS_SetupMusic, &TTYD64_tik_03_Script_80240B40);
    Mod_ReplaceScript("TTYD64", &tik_03_EVS_BindExitTriggers, &TTYD64_tik_03_Script_80241A20);
    Mod_ReplaceScript("TTYD64", &tik_03_EVS_EnterMap, &TTYD64_tik_03_Script_EnterWalk_80241A68);
    Mod_ReplaceScript("TTYD64", &tik_03_EVS_MakeEntities, &TTYD64_tik_03_Script_MakeEntities);
}
