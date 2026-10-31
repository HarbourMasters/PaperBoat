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
API_CALLABLE(MakeLerp);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PanToTarget);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerJump);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(RandInt);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerFlagBits);
API_CALLABLE(SetPlayerImgFXFlags);
API_CALLABLE(SetPlayerJumpscale);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UpdatePlayerImgFX);
API_CALLABLE(UseExitHeading);
API_CALLABLE(UseSettingsFrom);

extern EvtScript TTYD64_omo_19_Script_EnterHorizontalPipe;
extern EvtScript TTYD64_omo_19_Script_EnterVerticalPipe;
extern EvtScript TTYD64_omo_19_Script_ExitHorizontalPipe;
extern EvtScript TTYD64_omo_19_Script_ExitVerticalPipe;
extern EvtScript TTYD64_omo_19_Script_InitStuff;
extern EvtScript TTYD64_omo_19_Script_Update_MovingPlatform;
extern EvtScript TTYD64_omo_19_Script_EnterMap;
extern EvtScript TTYD64_omo_19_Script_Main;
extern u8 TTYD64_omo_19_String_Tattle[];
extern EvtScript TTYD64_omo_19_Script_Exit0;
extern EvtScript TTYD64_omo_19_Script_Exit1;
extern EvtScript TTYD64_omo_19_Script_CreateExitTriggers;
extern MapSettings TTYD64_omo_19_Header;
extern EvtScript TTYD64_omo_19_Script_SetupMusic;
extern EvtScript TTYD64_omo_19_Script_GotoMap_Exit1;
extern EntryList TTYD64_omo_19_EntryList;
extern s32 TTYD64_omo_19_IntTable_Colliders_Carousel_2[];
extern s32 TTYD64_omo_19_IntTable_Colliders_Carousel_1[];
extern s32 TTYD64_omo_19_IntTable_Models_Carousel_1[];
extern s32 TTYD64_omo_19_IntTable_Models_Carousel_3[];
extern s32 TTYD64_omo_19_IntTable_Models_Carousel_2[];
extern s32 TTYD64_omo_19_IntTable_Colliders_Carousel_3[];

// clang-format off
static s32 TTYD64_omo_19_GetTattleMsg;

static s32 TTYD64_omo_19_GetTattle(void) {
    return TTYD64_omo_19_GetTattleMsg;
}

EvtScript TTYD64_omo_19_Script_EnterHorizontalPipe = {
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

EvtScript TTYD64_omo_19_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_omo_19_Script_ExitHorizontalPipe = {
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

EvtScript TTYD64_omo_19_Script_ExitVerticalPipe = {
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

EvtScript TTYD64_omo_19_Script_InitStuff = {
    SetGroup(11)
    Call(ParentColliderToModel, 23, 63)
    Call(ParentColliderToModel, 34, 74)
    Call(ParentColliderToModel, 25, 65)
    Call(ParentColliderToModel, 26, 66)
    Call(ParentColliderToModel, 28, 68)
    Call(ParentColliderToModel, 29, 69)
    Call(ParentColliderToModel, 31, 71)
    Call(ParentColliderToModel, 32, 72)
    Thread
        Call(TTYD64_nm_omo_19_UpdateRotatingPlatforms_Movement_1)
    EndThread
    Call(ParentColliderToModel, 37, 77)
    Call(ParentColliderToModel, 38, 78)
    Call(ParentColliderToModel, 41, 81)
    Call(ParentColliderToModel, 52, 92)
    Call(ParentColliderToModel, 43, 83)
    Call(ParentColliderToModel, 44, 84)
    Call(ParentColliderToModel, 46, 86)
    Call(ParentColliderToModel, 47, 87)
    Call(ParentColliderToModel, 49, 89)
    Call(ParentColliderToModel, 50, 90)
    Thread
        Call(TTYD64_nm_omo_19_UpdateRotatingPlatforms_Movement_2)
    EndThread
    Call(ParentColliderToModel, 55, 95)
    Call(ParentColliderToModel, 66, 106)
    Call(ParentColliderToModel, 57, 97)
    Call(ParentColliderToModel, 58, 98)
    Call(ParentColliderToModel, 60, 100)
    Call(ParentColliderToModel, 61, 101)
    Call(ParentColliderToModel, 63, 103)
    Call(ParentColliderToModel, 64, 104)
    Thread
        Call(TTYD64_nm_omo_19_UpdateRotatingPlatforms_Movement_3)
    EndThread
    Exec(TTYD64_omo_19_Script_Update_MovingPlatform)
    Return
    End
};

EvtScript TTYD64_omo_19_Script_Update_MovingPlatform = {
    Call(RandInt, 20, LVarA)
    Wait(LVarA)
    Label(0)
    Call(MakeLerp, 0, -82, 60, 10)
    Label(1)
    Call(UpdateLerp)
    Call(TranslateModel, 77, 0, LVar0, 0)
    Call(TranslateModel, 78, 0, LVar0, 0)
    Call(UpdateColliderTransform, 37)
    Call(UpdateColliderTransform, 38)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(1)
    EndIf
    Wait(20)
    Call(MakeLerp, -82, 0, 60, 10)
    Label(2)
    Call(UpdateLerp)
    Call(TranslateModel, 77, 0, LVar0, 0)
    Call(TranslateModel, 78, 0, LVar0, 0)
    Call(UpdateColliderTransform, 37)
    Call(UpdateColliderTransform, 38)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(2)
    EndIf
    Wait(20)
    Goto(0)
    Return
    End
};

EvtScript TTYD64_omo_19_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVar0, 730)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Add(LVar0, 100)
        Call(SetPlayerPos, 730, 0, 0)
        Call(SetPlayerJumpscale, Float(1.5))
        Call(DisablePlayerInput, 1)
        Call(PlayerJump, 730, 0, 0, 16)
        Call(SetPlayerAnimation, 0x10002)
        Call(DisablePlayerInput, 0)
        Exec(TTYD64_omo_19_Script_CreateExitTriggers)
    CaseEq(1)
        Set(LVarA, (Bytecode) TTYD64_omo_19_Script_CreateExitTriggers)
        Exec(TTYD64_omo_19_Script_EnterVerticalPipe)
    CaseDefault
        Exec(TTYD64_omo_19_Script_CreateExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_omo_19_Script_Main = {
    Set(GameByte(425), 16)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_omo_19_Script_SetupMusic)
    ExecWait(TTYD64_omo_19_Script_InitStuff)
    Exec(TTYD64_omo_19_Script_EnterMap)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 0)
        Wait(7)
    EndIf
    Return
    End
};

u8 TTYD64_omo_19_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x29, 0xF7, 0x48, 0x41, 0x54, 0x45, 0xF7, 0x57,
    0x41, 0x49, 0x54, 0x49, 0x4E, 0x47, 0xF7, 0x46, 0x4F, 0x52, 0xF7, 0x54,
    0x48, 0x45, 0x53, 0x45, 0xF7, 0x50, 0x4C, 0x41, 0x54, 0x46, 0x4F, 0x52,
    0x4D, 0x53, 0xF0, 0x54, 0x4F, 0xF7, 0x42, 0x45, 0xF7, 0x49, 0x4E, 0xF7,
    0x50, 0x4F, 0x53, 0x49, 0x54, 0x49, 0x4F, 0x4E, 0x0C, 0xF7, 0x29, 0xF7,
    0x57, 0x4F, 0x4E, 0x44, 0x45, 0x52, 0xF7, 0x49, 0x46, 0xF7, 0x54, 0x48,
    0x45, 0x52, 0x45, 0x07, 0x53, 0xF0, 0x41, 0xF7, 0x57, 0x41, 0x59, 0xF7,
    0x54, 0x4F, 0xF7, 0x4D, 0x41, 0x4B, 0x45, 0xF7, 0x54, 0x48, 0x49, 0x53,
    0xF7, 0x46, 0x41, 0x53, 0x54, 0x45, 0x52, 0x0C, 0xF7, 0x43, 0x4F, 0x4D,
    0x45, 0xF7, 0x4F, 0x4E, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_omo_19_Script_Exit0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "omo_05", 4)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_omo_19_Script_Exit1 = {
    SetGroup(27)
    Set(LVarA, 1)
    Set(LVarB, 70)
    Set(LVarC, (Bytecode) TTYD64_omo_19_Script_GotoMap_Exit1)
    ExecWait(TTYD64_omo_19_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_omo_19_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_omo_19_Script_Exit0, 0x80000, 0, 1, 0)
    BindTrigger(TTYD64_omo_19_Script_Exit1, 128, 70, 1, 0)
    Return
    End
};

MapSettings TTYD64_omo_19_Header = {
    .main = &TTYD64_omo_19_Script_Main,
    .entryList = &TTYD64_omo_19_EntryList,
    .entryCount = 2,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_omo_19_GetTattle },
};

EvtScript TTYD64_omo_19_Script_SetupMusic = {
    Call(SetMusic, 0, 32, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_omo_19_Script_GotoMap_Exit1 = {
    Call(GotoMap, (Bytecode) "tyd_04", 0)
    Wait(100)
    Return
    End
};

EntryList TTYD64_omo_19_EntryList = {
    { 730.0f, 0.0f, 0.0f, 270.0f },
    { -283.0f, 171.0f, 115.0f, 90.0f },
};

s32 TTYD64_omo_19_IntTable_Colliders_Carousel_2[] = {
    43, 44, 46, 47, 49, 50
};

s32 TTYD64_omo_19_IntTable_Colliders_Carousel_1[] = {
    25, 26, 28, 29, 31, 32
};

s32 TTYD64_omo_19_IntTable_Models_Carousel_1[] = {
    65, 66, 68, 69, 71, 72
};

s32 TTYD64_omo_19_IntTable_Models_Carousel_3[] = {
    97, 98, 100, 101, 103, 104
};

s32 TTYD64_omo_19_IntTable_Models_Carousel_2[] = {
    83, 84, 86, 87, 89, 90
};

s32 TTYD64_omo_19_IntTable_Colliders_Carousel_3[] = {
    57, 58, 60, 61, 63, 64
};

MapConfig TTYD64_mapcfg_omo_19 = {
    .id = "omo_19",
    .settings = &TTYD64_omo_19_Header,
    .bgName = "omo_bg",
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 2,
};
// clang-format on

void TTYD64_nm_Install_omo_19(void) {
    TTYD64_omo_19_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_omo_19_String_Tattle);
}
