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

API_CALLABLE(AssignScript);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetPlayerActionState);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(PlayerJump);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerJumpscale);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(UseExitHeading);
API_CALLABLE(func_802D2484);

extern EvtScript TTYD64_arn_21_Script_EnterMap;
extern EvtScript TTYD64_arn_21_Script_Main;
extern EvtScript TTYD64_arn_21_Script_ScriptedSpring_Entity80240488;
extern EvtScript TTYD64_arn_21_Script_EnterMap_Spring;
extern EvtScript TTYD64_arn_21_Script_Exit1;
extern EvtScript TTYD64_arn_21_Script_Exit2;
extern u8 TTYD64_arn_21_String_Tattle[];
extern EvtScript TTYD64_arn_21_Script_SetupMusic;
extern EvtScript TTYD64_arn_21_Script_CreateExitTriggers;
extern EvtScript TTYD64_arn_21_Script_MakeEntities;
extern EntryList TTYD64_arn_21_EntryList;
extern MapSettings TTYD64_arn_21_Header;

// clang-format off
static s32 TTYD64_arn_21_GetTattleMsg;

static s32 TTYD64_arn_21_GetTattle(void) {
    return TTYD64_arn_21_GetTattleMsg;
}

EvtScript TTYD64_arn_21_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        ExecWait(TTYD64_arn_21_Script_EnterMap_Spring)
        Exec(TTYD64_arn_21_Script_CreateExitTriggers)
    CaseOrEq(1)
    CaseOrEq(2)
        Set(LVar0, (Bytecode) TTYD64_arn_21_Script_CreateExitTriggers)
        Exec(EnterWalk)
        Wait(1)
        EndCaseGroup
    CaseEq(3)
        Call(DisablePlayerInput, 1)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Add(LVar1, 70)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Loop(0)
            Call(GetPlayerActionState, LVar0)
            IfEq(LVar0, 10)
                Call(DisablePlayerInput, 0)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Exec(TTYD64_arn_21_Script_CreateExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_arn_21_Script_Main = {
    Set(AreaByte(0), 0)
    Set(GameByte(425), 35)
    Call(SetSpriteShading, 0x80000)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    ExecWait(TTYD64_arn_21_Script_MakeEntities)
    Exec(TTYD64_arn_21_Script_SetupMusic)
    Exec(TTYD64_arn_21_Script_EnterMap)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 0)
        Wait(8)
    EndIf
    Return
    End
};

EvtScript TTYD64_arn_21_Script_ScriptedSpring_Entity80240488 = {
    IfEq(MapFlag(0), 1)
        Return
    EndIf
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerActionState, 6)
    Wait(1)
    Call(SetPlayerJumpscale, Float(0.7001953125))
    Call(PlayerJump, 0, 200, 0, 30)
    Thread
        Wait(10)
        Call(GotoMap, (Bytecode) "arn_05", 2)
    EndThread
    Return
    End
};

EvtScript TTYD64_arn_21_Script_EnterMap_Spring = {
    Set(MapFlag(0), 1)
    Call(DisablePlayerInput, 1)
    Call(SetPlayerActionState, 8)
    Call(func_802D2484)
    Call(SetPlayerActionState, 6)
    Call(SetPlayerJumpscale, Float(1.5))
    Call(PlayerJump, 50, 0, 0, 16)
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerInput, 0)
    Set(MapFlag(0), 0)
    Return
    End
};

EvtScript TTYD64_arn_21_Script_Exit1 = {
    Set(AreaByte(0), 1)
    Call(UseExitHeading, 60, 1)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "arn_22", 1)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_arn_21_Script_Exit2 = {
    Set(AreaByte(0), 2)
    Call(UseExitHeading, 60, 2)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "arn_22", 2)
    Wait(100)
    Return
    End
};

u8 TTYD64_arn_21_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C, 0xF7, 0x48,
    0x45, 0x52, 0x45, 0xF7, 0x53, 0x4D, 0x45, 0x4C, 0x4C, 0x53, 0xF7, 0x57,
    0x45, 0x49, 0x52, 0x44, 0x01, 0xF0, 0x2F, 0x4E, 0x45, 0xF7, 0x4F, 0x46,
    0xF7, 0x54, 0x48, 0x45, 0xF7, 0x52, 0x45, 0x41, 0x53, 0x4F, 0x4E, 0x53,
    0xF7, 0x57, 0x48, 0x59, 0xF0, 0x29, 0xF7, 0x48, 0x41, 0x54, 0x45, 0xF7,
    0x43, 0x41, 0x56, 0x45, 0x53, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_arn_21_Script_SetupMusic = {
    Switch(GameByte(0))
    CaseDefault
        Call(SetMusic, 0, 29, 0, 8)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_arn_21_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_arn_21_Script_Exit1, 0x80000, 0, 1, 0)
    BindTrigger(TTYD64_arn_21_Script_Exit2, 0x80000, 1, 1, 0)
    Return
    End
};

EvtScript TTYD64_arn_21_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_ScriptSpring), 0, 0, 0, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_arn_21_Script_ScriptedSpring_Entity80240488)
    Return
    End
};

EntryList TTYD64_arn_21_EntryList = {
    { 0.0f, 200.0f, 0.0f, 90.0f },
    { 566.0f, 0.0f, -71.0f, -90.0f },
    { 566.0f, 0.0f, 72.0f, -90.0f },
    { 74.0f, 0.0f, 82.0f, -180.0f },
};

MapSettings TTYD64_arn_21_Header = {
    .main = &TTYD64_arn_21_Script_Main,
    .entryList = &TTYD64_arn_21_EntryList,
    .entryCount = 4,
    .background = NULL,
    .tattle = { .get = TTYD64_arn_21_GetTattle },
};

MapConfig TTYD64_mapcfg_arn_21 = {
    .id = "arn_21",
    .settings = &TTYD64_arn_21_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 1,
};
// clang-format on

void TTYD64_nm_Install_arn_21(void) {
    TTYD64_arn_21_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_arn_21_String_Tattle);
}
