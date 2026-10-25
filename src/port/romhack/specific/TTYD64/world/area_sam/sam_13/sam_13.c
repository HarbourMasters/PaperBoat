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
#include "port/romhack/specific/TTYD64/world/nm.h"

API_CALLABLE(ClearAmbientSounds);
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
API_CALLABLE(HidePlayerShadow);
API_CALLABLE(InterpNpcYaw);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(InterruptUsePartner);
API_CALLABLE(IsPlayerOnValidFloor);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(ResetCam);
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
API_CALLABLE(SetPlayerPos);
API_CALLABLE(TeleportPartnerToPlayer);
API_CALLABLE(UpdatePlayerImgFX);
API_CALLABLE(UseExitHeading);
API_CALLABLE(UseSettingsFrom);

extern EvtScript TTYD64_sam_13_Script_EnterHorizontalPipe;
extern EvtScript TTYD64_sam_13_Script_EnterVerticalPipe;
extern EvtScript TTYD64_sam_13_Script_ExitHorizontalPipe;
extern EvtScript TTYD64_sam_13_Script_ExitVerticalPipe;
extern EvtScript TTYD64_sam_13_Script_Respawn;
extern EvtScript TTYD64_sam_13_Script_InitStuff;
extern EvtScript TTYD64_sam_13_Script_Main;
extern EvtScript TTYD64_sam_13_Script_EnterMap;
extern EvtScript TTYD64_sam_13_Script_TrackDeathTrigger;
extern EvtScript TTYD64_sam_13_Script_Exit1;
extern u8 TTYD64_sam_13_String_Tattle[];
extern EvtScript TTYD64_sam_13_Script_Exit0;
extern EvtScript TTYD64_sam_13_Script_CreateExitTriggers;
extern MapSettings TTYD64_sam_13_Header;
extern EvtScript TTYD64_sam_13_Script_SetupMusic;
extern EvtScript TTYD64_sam_13_Script_GotoMap_Exit1;
extern EntryList TTYD64_sam_13_EntryList;
extern EvtScript TTYD64_sam_13_Script_SetRespawnPos_6;
extern EvtScript TTYD64_sam_13_Script_SetRespawnPos_5;
extern EvtScript TTYD64_sam_13_Script_SetRespawnPos_4;
extern EvtScript TTYD64_sam_13_Script_SetRespawnPos_3;
extern EvtScript TTYD64_sam_13_Script_SetRespawnPos_2;
extern EvtScript TTYD64_sam_13_Script_SetRespawnPos_1;

// clang-format off
static s32 TTYD64_sam_13_GetTattleMsg;

static s32 TTYD64_sam_13_GetTattle(void) {
    return TTYD64_sam_13_GetTattleMsg;
}

EvtScript TTYD64_sam_13_Script_EnterHorizontalPipe = {
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

EvtScript TTYD64_sam_13_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_sam_13_Script_ExitHorizontalPipe = {
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

EvtScript TTYD64_sam_13_Script_ExitVerticalPipe = {
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

EvtScript TTYD64_sam_13_Script_Respawn = {
    Call(DisablePlayerInput, 1)
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(255.0))
    ExecWait(TTYD64_Script_FadeScreenOut)
    Switch(MapVar(0))
    CaseEq(0)
        Call(SetPlayerPos, -167, 0, -42)
    CaseEq(1)
        Call(SetPlayerPos, 105, -56, -12)
    CaseEq(2)
        Call(SetPlayerPos, 175, -73, 63)
    CaseEq(3)
        Call(SetPlayerPos, 386, -70, -84)
    CaseEq(4)
        Call(SetPlayerPos, 453, -80, 66)
    CaseEq(5)
        Call(SetPlayerPos, 582, -67, 49)
    EndSwitch
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(ResetCam, 0, Float(200.0))
    Call(TeleportPartnerToPlayer)
    Call(SetPlayerActionState, 0)
    Wait(1)
    Call(SetPlayerAnimation, 0x10002)
    Call(SetPlayerAnimation, 0x1000F)
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(5.0))
    Exec(TTYD64_Script_FadeScreenIn)
    Wait(10)
    Call(SetPlayerAnimation, 0x10030)
    Wait(15)
    Call(SetPlayerAnimation, 0x10031)
    Thread
        Call(PlaySound, 370)
        Wait(12)
        Call(PlaySound, 370)
    EndThread
    Wait(25)
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_sam_13_Script_InitStuff = {
    Set(GameByte(4326), 2)
    Call(MakeItemEntity, 376, 702, -67, 20, 17, GameFlag(5568))
    BindTrigger(TTYD64_sam_13_Script_SetRespawnPos_1, 128, 18, 1, 0)
    BindTrigger(TTYD64_sam_13_Script_SetRespawnPos_2, 128, 19, 1, 0)
    BindTrigger(TTYD64_sam_13_Script_SetRespawnPos_3, 128, 20, 1, 0)
    BindTrigger(TTYD64_sam_13_Script_SetRespawnPos_4, 128, 21, 1, 0)
    BindTrigger(TTYD64_sam_13_Script_SetRespawnPos_5, 128, 22, 1, 0)
    BindTrigger(TTYD64_sam_13_Script_SetRespawnPos_6, 128, 23, 1, 0)
    Exec(TTYD64_sam_13_Script_TrackDeathTrigger)
    Return
    End
};

EvtScript TTYD64_sam_13_Script_Main = {
    Set(GameByte(425), 43)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_sam_13_Script_SetupMusic)
    Exec(TTYD64_sam_13_Script_InitStuff)
    Exec(TTYD64_sam_13_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_sam_13_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVar0, (Bytecode) TTYD64_sam_13_Script_CreateExitTriggers)
        Exec(EnterWalk)
    CaseEq(1)
        Set(LVarA, (Bytecode) TTYD64_sam_13_Script_CreateExitTriggers)
        Exec(TTYD64_sam_13_Script_EnterVerticalPipe)
    EndSwitch
    Wait(1)
    Return
    End
};

EvtScript TTYD64_sam_13_Script_TrackDeathTrigger = {
    Loop(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        IfLt(LVar1, -110)
            ExecWait(TTYD64_sam_13_Script_Respawn)
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_sam_13_Script_Exit1 = {
    SetGroup(27)
    Set(LVarA, 1)
    Set(LVarB, 1)
    Set(LVarC, (Bytecode) TTYD64_sam_13_Script_GotoMap_Exit1)
    ExecWait(TTYD64_sam_13_Script_ExitVerticalPipe)
    Return
    End
};

u8 TTYD64_sam_13_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x22, 0x45, 0xF7, 0x43, 0x41, 0x52, 0x45, 0x46,
    0x55, 0x4C, 0xF7, 0x57, 0x48, 0x45, 0x52, 0x45, 0xF7, 0x59, 0x4F, 0x55,
    0xF7, 0x53, 0x54, 0x45, 0x50, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C,
    0xF0, 0x54, 0x48, 0x4F, 0x53, 0x45, 0xF7, 0x50, 0x49, 0x4C, 0x4C, 0x41,
    0x52, 0x53, 0xF7, 0x41, 0x52, 0x45, 0xF7, 0x56, 0x45, 0x52, 0x59, 0xF7,
    0x53, 0x4C, 0x49, 0x50, 0x50, 0x45, 0x52, 0x59, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_sam_13_Script_Exit0 = {
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "sam_07", 2)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_sam_13_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_sam_13_Script_Exit0, 128, 0, 1, 0)
    BindTrigger(TTYD64_sam_13_Script_Exit1, 128, 1, 1, 0)
    Return
    End
};

MapSettings TTYD64_sam_13_Header = {
    .main = &TTYD64_sam_13_Script_Main,
    .entryList = &TTYD64_sam_13_EntryList,
    .entryCount = 2,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_sam_13_GetTattle },
};

EvtScript TTYD64_sam_13_Script_SetupMusic = {
    Call(SetMusic, 0, 59, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_sam_13_Script_GotoMap_Exit1 = {
    Call(GotoMap, (Bytecode) "tyd_07", 0)
    Wait(100)
    Return
    End
};

EntryList TTYD64_sam_13_EntryList = {
    { -360.0f, 0.0f, 0.0f, 90.0f },
    { -355.0f, 253.0f, -6.0f, 90.0f },
};

EvtScript TTYD64_sam_13_Script_SetRespawnPos_6 = {
    Set(MapVar(0), 5)
    Return
    End
};

EvtScript TTYD64_sam_13_Script_SetRespawnPos_5 = {
    Set(MapVar(0), 4)
    Return
    End
};

EvtScript TTYD64_sam_13_Script_SetRespawnPos_4 = {
    Set(MapVar(0), 3)
    Return
    End
};

EvtScript TTYD64_sam_13_Script_SetRespawnPos_3 = {
    Set(MapVar(0), 2)
    Return
    End
};

EvtScript TTYD64_sam_13_Script_SetRespawnPos_2 = {
    Set(MapVar(0), 1)
    Return
    End
};

EvtScript TTYD64_sam_13_Script_SetRespawnPos_1 = {
    Set(MapVar(0), 0)
    Return
    End
};

MapConfig TTYD64_mapcfg_sam_13 = {
    .id = "sam_13",
    .settings = &TTYD64_sam_13_Header,
    .bgName = "yki_bg",
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 1,
};
// clang-format on

void TTYD64_nm_Install_sam_13(void) {
    TTYD64_sam_13_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_sam_13_String_Tattle);
}
