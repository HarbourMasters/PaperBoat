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

extern NpcGroupList nok_13_DefaultNPCs;
extern EvtScript nok_13_EVS_BindExitTriggers;
extern EvtScript nok_13_EVS_ExitWalk_nok_01_0;
extern EvtScript nok_13_EVS_ExitWalk_nok_12_1;
extern EvtScript nok_13_EVS_ExitWalk_nok_14_0;
extern EvtScript nok_13_EVS_Main;
extern EvtScript nok_13_EVS_MakeEntities;
extern EvtScript nok_13_EVS_SetupMusic;
extern EvtScript nok_13_EVS_SetupMusicalHill;
extern MapSettings nok_13_settings;

API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
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
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PanToTarget);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(ResetCam);
API_CALLABLE(RotateModel);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamDistance);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerFlagBits);
API_CALLABLE(SetPlayerImgFXFlags);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanOffset);
API_CALLABLE(SetTexPanner);
API_CALLABLE(TranslateGroup);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UpdatePlayerImgFX);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(WaitForCam);
API_CALLABLE(nok_13_MonitorPlayerOrbiting);

extern EvtScript TTYD64_nok_13_Script_GotoMap_Exit3;
extern EvtScript TTYD64_nok_13_Script_80241630;
extern EvtScript TTYD64_nok_13_Script_8024170C;
extern EvtScript TTYD64_nok_13_Script_Exit3;
extern EvtScript TTYD64_nok_13_Script_Main_EnterWalk;
extern EvtScript TTYD64_nok_13_Script_EnterVerticalPipe;
extern EvtScript TTYD64_nok_13_Script_ExitVerticalPipe;
extern EvtScript TTYD64_nok_13_Script_SpawnPipe;
extern EvtScript TTYD64_nok_13_Script_NewCanes_FollowPlayer;
extern EvtScript TTYD64_nok_13_Script_EnterMap;
extern EvtScript TTYD64_nok_13_Script_802418CC;
extern EvtScript TTYD64_nok_13_Script_C3_FollowPlayer;
extern EvtScript TTYD64_nok_13_Script_C2_FollowPlayer;
extern EntryList TTYD64_nok_13_EntryList;
extern PlayerOrbitTarget TTYD64_nok_13_Data_CaneReward_Pipe;

// clang-format off
EvtScript TTYD64_nok_13_Script_GotoMap_Exit3 = {
    Call(GotoMap, (Bytecode) "tyd_01", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_nok_13_Script_80241630 = {
    Call(SetTexPanner, 113, 0)
    Call(SetTexPanner, 114, 0)
    Call(SetTexPanner, 115, 0)
    Label(10)
    Loop(12)
        Call(SetTexPanOffset, 0, 0, 0, 0)
        Wait(1)
    EndLoop
    Loop(12)
        Call(SetTexPanOffset, 0, 0, 16384, 0)
        Wait(1)
    EndLoop
    Goto(10)
    Return
    End
};

EvtScript TTYD64_nok_13_Script_8024170C = {
    Thread
        Call(SetTexPanner, 146, 1)
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Label(10)
        Call(SetTexPanOffset, 1, 0, LVar0, 0)
        Call(SetTexPanOffset, 1, 1, LVar1, LVar2)
        Sub(LVar0, 100)
        Sub(LVar1, 400)
        Add(LVar1, 1000)
        Wait(1)
        Goto(10)
    EndThread
    Call(SetTexPanner, 148, 2)
    Set(LVar0, 0)
    Set(LVar1, 0)
    Set(LVar2, 0)
    Label(20)
    Call(SetTexPanOffset, 2, 0, LVar0, 0)
    Call(SetTexPanOffset, 2, 1, LVar1, LVar2)
    Sub(LVar0, 100)
    Add(LVar1, 800)
    Sub(LVar1, 400)
    Wait(1)
    Goto(20)
    Return
    End
};

EvtScript TTYD64_nok_13_Script_Exit3 = {
    SetGroup(27)
    Set(LVarA, 3)
    Set(LVarB, 70)
    Set(LVarC, Ref(TTYD64_nok_13_Script_GotoMap_Exit3))
    ExecWait(TTYD64_nok_13_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_nok_13_Script_Main_EnterWalk = {
    Set(GameByte(425), 32)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamLeadPlayer, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 0, Ref(nok_13_DefaultNPCs))
    ExecWait(nok_13_EVS_MakeEntities)
    Exec(TTYD64_nok_13_Script_80241630)
    Exec(TTYD64_nok_13_Script_8024170C)
    Exec(nok_13_EVS_SetupMusic)
    Exec(nok_13_EVS_SetupMusicalHill)
    Exec(TTYD64_nok_13_Script_NewCanes_FollowPlayer)
    Exec(TTYD64_nok_13_Script_EnterMap)
    Wait(1)
    Return
    End
};

EvtScript TTYD64_nok_13_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_nok_13_Script_ExitVerticalPipe = {
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

EvtScript TTYD64_nok_13_Script_SpawnPipe = {
    Call(DisablePlayerInput, 1)
    Call(SetCamSpeed, 0, Float(4.0))
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Set(LVar0, -259)
    Set(LVar1, 182)
    Set(LVar2, -51)
    Add(LVar1, -30)
    Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
    Call(SetCamDistance, 0, 350)
    Call(PanToTarget, 0, 0, 1)
    Call(WaitForCam, 0, Float(1.0))
    Call(PlaySound, 8334)
    Call(ParentColliderToModel, 69, 161)
    Call(ParentColliderToModel, 70, 161)
    Call(MakeLerp, -40, 0, 25, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, 163, 0, LVar0, 0)
        Call(UpdateColliderTransform, 69)
        Call(UpdateColliderTransform, 70)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(ModifyColliderFlags, 1, 69, 0x7FFFFE00)
    Call(ModifyColliderFlags, 1, 70, 0x7FFFFE00)
    Wait(10)
    Call(ResetCam, 0, Float(4.0))
    Call(SetCamSpeed, 0, Float(1.0))
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_nok_13_Script_NewCanes_FollowPlayer = {
    IfEq(GameFlag(4716), 0)
        Call(TranslateGroup, 163, 0, -40, 0)
        Call(ModifyColliderFlags, 0, 69, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 70, 0x7FFFFE00)
    EndIf
    Exec(TTYD64_nok_13_Script_C2_FollowPlayer)
    Exec(TTYD64_nok_13_Script_C3_FollowPlayer)
    Call(nok_13_MonitorPlayerOrbiting, Ref(TTYD64_nok_13_Data_CaneReward_Pipe))
    Return
    End
};

EvtScript TTYD64_nok_13_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(3)
        Set(LVarA, Ref(nok_13_EVS_BindExitTriggers))
        Exec(TTYD64_nok_13_Script_EnterVerticalPipe)
    CaseDefault
        Set(LVar0, Ref(nok_13_EVS_BindExitTriggers))
        Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_nok_13_Script_802418CC = {
    BindTrigger(nok_13_EVS_ExitWalk_nok_12_1, 0x80000, 10, 1, 0)
    BindTrigger(nok_13_EVS_ExitWalk_nok_01_0, 0x80000, 7, 1, 0)
    BindTrigger(nok_13_EVS_ExitWalk_nok_14_0, 0x80000, 20, 1, 0)
    BindTrigger(TTYD64_nok_13_Script_Exit3, 128, 70, 1, 0)
    Return
    End
};

EvtScript TTYD64_nok_13_Script_C3_FollowPlayer = {
    Label(0)
    Call(TTYD64_nok_13_Function_UpdateCaneAxis_Cane3, LVar0)
    Add(LVar0, 180)
    Call(RotateModel, 155, LVar0, 0, -1, 0)
    Wait(1)
    Goto(0)
    Return
    End
};

EvtScript TTYD64_nok_13_Script_C2_FollowPlayer = {
    Label(0)
    Call(TTYD64_nok_13_Function_UpdateCaneAxis_Cane2, LVar0)
    Add(LVar0, 180)
    Call(RotateModel, 150, LVar0, 0, -1, 0)
    Wait(1)
    Goto(0)
    Return
    End
};

EntryList TTYD64_nok_13_EntryList = {
    { -488.0f, 150.0f, 0.0f, 90.0f },
    { 165.0f, 0.0f, -483.0f, 180.0f },
    { 277.0f, 150.0f, 210.0f, 315.0f },
    { -259.0f, 182.0f, -51.0f, 90.0f },
};

PlayerOrbitTarget TTYD64_nok_13_Data_CaneReward_Pipe = {
    .pos = { -259, 149, -155 },
    .startRadius = 181,
    .orbitRadius = 192,
    .eventListener = TTYD64_nok_13_Function_UpdateReward
};
// clang-format on

void TTYD64_InstallMap_nok_13(void) {
    nok_13_settings.entryList = &TTYD64_nok_13_EntryList;
    nok_13_settings.entryCount = 4;
    Mod_ReplaceScript("TTYD64", &nok_13_EVS_Main, &TTYD64_nok_13_Script_Main_EnterWalk);
    Mod_ReplaceScript("TTYD64", &nok_13_EVS_BindExitTriggers, &TTYD64_nok_13_Script_802418CC);
}
