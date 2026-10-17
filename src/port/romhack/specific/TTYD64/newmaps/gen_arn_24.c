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

API_CALLABLE(AssignScript);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GetCurrentPartnerID);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetPartnerInUse);
API_CALLABLE(GetPlayerActionState);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(GotoMapSpecial);
API_CALLABLE(HidePlayerShadow);
API_CALLABLE(InterpNpcYaw);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(InterruptUsePartner);
API_CALLABLE(IsPlayerOnValidFloor);
API_CALLABLE(MakeEntity);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerJump);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerFlagBits);
API_CALLABLE(SetPlayerImgFXFlags);
API_CALLABLE(SetPlayerJumpscale);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(UpdatePlayerImgFX);
API_CALLABLE(UseExitHeading);
API_CALLABLE(UseSettingsFrom);

extern EvtScript TTYD64_arn_24_Script_EnterHorizontalPipe;
extern EvtScript TTYD64_arn_24_Script_EnterVerticalPipe;
extern EvtScript TTYD64_arn_24_Script_ExitHorizontalPipe;
extern EvtScript TTYD64_arn_24_Script_ExitVerticalPipe;
extern EvtScript TTYD64_arn_24_Script_ScriptedSpring_EntitySpring;
extern EvtScript TTYD64_arn_24_Script_Main;
extern EvtScript TTYD64_arn_24_Script_EnterMap;
extern u8 TTYD64_arn_24_String_Tattle[];
extern EvtScript TTYD64_arn_24_Script_Exit1;
extern EvtScript TTYD64_arn_24_Script_Exit0;
extern EvtScript TTYD64_arn_24_Script_SetupMusic;
extern EvtScript TTYD64_arn_24_Script_CreateExitTriggers;
extern EvtScript TTYD64_arn_24_Script_MakeEntities;
extern MapSettings TTYD64_arn_24_Header;
extern EvtScript TTYD64_arn_24_Script_GotoMap_Exit1;
extern EntryList TTYD64_arn_24_EntryList;

// clang-format off
static s32 TTYD64_arn_24_GetTattleMsg;

static s32 TTYD64_arn_24_GetTattle(void) {
    return TTYD64_arn_24_GetTattleMsg;
}

EvtScript TTYD64_arn_24_Script_EnterHorizontalPipe = {
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

EvtScript TTYD64_arn_24_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_arn_24_Script_ExitHorizontalPipe = {
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

EvtScript TTYD64_arn_24_Script_ExitVerticalPipe = {
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

EvtScript TTYD64_arn_24_Script_ScriptedSpring_EntitySpring = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerActionState, 6)
    Wait(1)
    Call(SetPlayerJumpscale, Float(0.7001953125))
    Call(PlayerJump, 336, 200, 69, 30)
    Thread
        Wait(10)
        Call(GotoMapSpecial, (Bytecode) "arn_21", 3, 0)
    EndThread
    Return
    End
};

EvtScript TTYD64_arn_24_Script_Main = {
    Set(GameByte(425), 35)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    ExecWait(TTYD64_arn_24_Script_MakeEntities)
    Exec(TTYD64_arn_24_Script_SetupMusic)
    Exec(TTYD64_arn_24_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_arn_24_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVar0, (Bytecode) TTYD64_arn_24_Script_CreateExitTriggers)
        Exec(EnterWalk)
    CaseEq(1)
        Set(LVarA, (Bytecode) TTYD64_arn_24_Script_CreateExitTriggers)
        Exec(TTYD64_arn_24_Script_EnterVerticalPipe)
    EndSwitch
    Wait(1)
    Return
    End
};

u8 TTYD64_arn_24_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x33, 0x45, 0x45, 0x4D, 0x53, 0xF7, 0x57, 0x45,
    0xF7, 0x46, 0x49, 0x4E, 0x41, 0x4C, 0x4C, 0x59, 0xF7, 0x44, 0x49, 0x44,
    0xF7, 0x49, 0x54, 0x01, 0xF0, 0x2E, 0x4F, 0x57, 0x0E, 0x0E, 0x0E, 0xF0,
    0xF1, 0xFB, 0x23, 0x41, 0x4E, 0xF7, 0x57, 0x45, 0xF7, 0x46, 0x49, 0x4E,
    0x41, 0x4C, 0x4C, 0x59, 0xF7, 0x4C, 0x45, 0x41, 0x56, 0x45, 0xF7, 0x54,
    0x48, 0x49, 0x53, 0xF0, 0x50, 0x4C, 0x41, 0x43, 0x45, 0xF7, 0x50, 0x4C,
    0x45, 0x41, 0x53, 0x45, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x1F, 0xF1,
    0xFD
};

EvtScript TTYD64_arn_24_Script_Exit1 = {
    SetGroup(27)
    Set(LVarA, 1)
    Set(LVarB, 1)
    Set(LVarC, (Bytecode) TTYD64_arn_24_Script_GotoMap_Exit1)
    ExecWait(TTYD64_arn_24_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_arn_24_Script_Exit0 = {
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "arn_22", 3)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_arn_24_Script_SetupMusic = {
    Switch(GameByte(0))
    CaseDefault
        Call(SetMusic, 0, 29, 0, 8)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_arn_24_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_arn_24_Script_Exit0, 0x80000, 0, 1, 0)
    BindTrigger(TTYD64_arn_24_Script_Exit1, 128, 1, 1, 0)
    Return
    End
};

EvtScript TTYD64_arn_24_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_ScriptSpring), 336, 0, 69, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_arn_24_Script_ScriptedSpring_EntitySpring)
    Return
    End
};

MapSettings TTYD64_arn_24_Header = {
    .main = &TTYD64_arn_24_Script_Main,
    .entryList = &TTYD64_arn_24_EntryList,
    .entryCount = 2,
    .background = NULL,
    .tattle = { .get = TTYD64_arn_24_GetTattle },
};

EvtScript TTYD64_arn_24_Script_GotoMap_Exit1 = {
    Call(GotoMap, (Bytecode) "tyd_03", 0)
    Wait(100)
    Return
    End
};

EntryList TTYD64_arn_24_EntryList = {
    { -170.0f, 0.0f, 1.0f, 90.0f },
    { 273.0f, 53.0f, -11.0f, 90.0f },
};

MapConfig TTYD64_mapcfg_arn_24 = {
    .id = "arn_24",
    .settings = &TTYD64_arn_24_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 1,
};
// clang-format on

void TTYD64_nm_Install_arn_24(void) {
    TTYD64_arn_24_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_arn_24_String_Tattle);
}
