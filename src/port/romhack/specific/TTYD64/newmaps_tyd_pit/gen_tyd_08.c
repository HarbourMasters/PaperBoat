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

extern EvtScript TTYD64_tyd_08_Script_EnterHorizontalPipe;
extern EvtScript TTYD64_tyd_08_Script_EnterVerticalPipe;
extern EvtScript TTYD64_tyd_08_Script_ExitHorizontalPipe;
extern EvtScript TTYD64_tyd_08_Script_ExitVerticalPipe;
extern EvtScript TTYD64_tyd_08_Script_Main;
extern EvtScript TTYD64_tyd_08_Script_BlastWall;
extern EvtScript TTYD64_tyd_08_Script_MakeEntities;
extern EvtScript TTYD64_tyd_08_Script_EnterMap;
extern EvtScript TTYD64_tyd_08_Script_UpdateCrack;
extern u8 TTYD64_tyd_08_String_Tattle[];
extern EvtScript TTYD64_tyd_08_Script_Exit0;
extern MapSettings TTYD64_tyd_08_Header;
extern EvtScript TTYD64_tyd_08_Script_SetupMusic;
extern EvtScript TTYD64_tyd_08_Script_GotoMap_Exit0;
s32 TTYD64_tyd_08_Function_Init(void);
extern EvtScript TTYD64_tyd_08_Script_CreateExitTriggers;
extern EntryList TTYD64_tyd_08_EntryList;
extern BombTrigger TTYD64_tyd_08_TriggerCoord_Door;

// clang-format off
static s32 TTYD64_tyd_08_GetTattleMsg;

static s32 TTYD64_tyd_08_GetTattle(void) {
    return TTYD64_tyd_08_GetTattleMsg;
}

EvtScript TTYD64_tyd_08_Script_EnterHorizontalPipe = {
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

EvtScript TTYD64_tyd_08_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_tyd_08_Script_ExitHorizontalPipe = {
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

EvtScript TTYD64_tyd_08_Script_ExitVerticalPipe = {
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

EvtScript TTYD64_tyd_08_Script_Main = {
    Set(GameByte(425), 22)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_tyd_08_Script_MakeEntities)
    Exec(TTYD64_tyd_08_Script_SetupMusic)
    Exec(TTYD64_tyd_08_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_tyd_08_Script_BlastWall = {
    Call(PlayEffect_impl, 66, 0, 198, 198, 1, 10, 30, 0, 0, 0, 0, 0, 0)
    Call(EnableGroup, 205, 0)
    Call(ModifyColliderFlags, 0, 6, 0x7FFFFE00)
    Set(GameFlag(5705), 1)
    Unbind
    Return
    End
};

EvtScript TTYD64_tyd_08_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_RedBlock), 993, 65, 0, 0, 376, 0x80000000)
    Call(AssignBlockFlag, GameFlag(5703))
    Call(MakeEntity, Ref(Entity_RedBlock), 1103, 65, 0, 0, 247, 0x80000000)
    Call(AssignBlockFlag, GameFlag(5704))
    Return
    End
};

EvtScript TTYD64_tyd_08_Script_EnterMap = {
    Exec(TTYD64_tyd_08_Script_UpdateCrack)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVarA, (Bytecode) TTYD64_tyd_08_Script_CreateExitTriggers)
        Exec(TTYD64_tyd_08_Script_EnterVerticalPipe)
    CaseDefault
        Exec(TTYD64_tyd_08_Script_CreateExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_tyd_08_Script_UpdateCrack = {
    IfEq(GameFlag(5705), 0)
        BindTrigger(TTYD64_tyd_08_Script_BlastWall, 0x100000, Ref(TTYD64_tyd_08_TriggerCoord_Door), 1, 0)
    Else
        Call(EnableGroup, 205, 0)
        Call(ModifyColliderFlags, 0, 6, 0x7FFFFE00)
    EndIf
    Return
    End
};

u8 TTYD64_tyd_08_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x37, 0x4F, 0x57, 0x0C, 0xF7, 0x54, 0x48, 0x49,
    0x53, 0xF7, 0x50, 0x4C, 0x41, 0x43, 0x45, 0xF7, 0x4C, 0x4F, 0x4F, 0x4B,
    0x53, 0xF7, 0x52, 0x45, 0x41, 0x4C, 0x4C, 0x59, 0xF7, 0x4E, 0x49, 0x43,
    0x45, 0x0C, 0xF0, 0x29, 0xF7, 0x57, 0x4F, 0x4E, 0x44, 0x45, 0x52, 0xF7,
    0x57, 0x48, 0x4F, 0xF7, 0x57, 0x49, 0x4C, 0x4C, 0xF7, 0x4C, 0x49, 0x56,
    0x45, 0xF7, 0x48, 0x45, 0x52, 0x45, 0x1F, 0xF0, 0xF1, 0xFB, 0x2C, 0x4F,
    0x4F, 0x4B, 0x53, 0xF7, 0x4C, 0x49, 0x4B, 0x45, 0xF7, 0x41, 0xF7, 0x50,
    0x41, 0x4C, 0x41, 0x43, 0x45, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_tyd_08_Script_Exit0 = {
    SetGroup(27)
    Set(LVarA, 0)
    Set(LVarB, 1)
    Set(LVarC, (Bytecode) TTYD64_tyd_08_Script_GotoMap_Exit0)
    ExecWait(TTYD64_tyd_08_Script_ExitVerticalPipe)
    Return
    End
};

MapSettings TTYD64_tyd_08_Header = {
    .main = TTYD64_tyd_08_Script_Main,
    .entryList = &TTYD64_tyd_08_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_tyd_08_GetTattle },
};

EvtScript TTYD64_tyd_08_Script_SetupMusic = {
    Call(FadeOutMusic, 0, 500)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_tyd_08_Script_GotoMap_Exit0 = {
    Call(GotoMap, (Bytecode) "kpa_136", 1)
    Wait(100)
    Return
    End
};

s32 TTYD64_tyd_08_Function_Init(void) {
    sprintf(wMapTexName, "kpa_tex");
    return false;
}

EvtScript TTYD64_tyd_08_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_tyd_08_Script_Exit0, 128, 1, 1, 0)
    Return
    End
};

EntryList TTYD64_tyd_08_EntryList = {
    { -468.0f, 32.0f, 8.0f, -270.0f },
};

BombTrigger TTYD64_tyd_08_TriggerCoord_Door = {
    .pos = { 522.0f, 0.0f, 3.0f },
    .diameter = 0.0f,
};

MapConfig TTYD64_mapcfg_tyd_08 = {
    .id = "tyd_08",
    .settings = &TTYD64_tyd_08_Header,
    .bgName = NULL,
    .init = TTYD64_tyd_08_Function_Init,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_tp_Install_tyd_08(void) {
    TTYD64_tyd_08_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_tyd_08_String_Tattle);
}
