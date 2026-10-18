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
#include "port/romhack/specific/TTYD64/maps/maps.h"

extern NpcGroupList dro_02_DefaultNPCs;
extern EvtScript dro_02_EVS_EnterScene;
extern EvtScript dro_02_EVS_ExitWalk_dro_01_1;
extern EvtScript dro_02_EVS_Main;
extern EvtScript dro_02_EVS_MakeEntities;
extern EvtScript dro_02_EVS_OnReadPoster;
extern EvtScript dro_02_EVS_SetupMusic;
extern EvtScript dro_02_EVS_SetupRooms;
extern MapSettings dro_02_settings;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableGroup);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(InitVirtualEntityList);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlayerJump);
API_CALLABLE(ResetCam);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerJumpscale);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanOffset);
API_CALLABLE(SetTexPanner);
API_CALLABLE(UseExitHeading);
API_CALLABLE(UseSettingsFrom);

extern EvtScript TTYD64_dro_02_Script_Entity_Shine1;
extern EvtScript TTYD64_dro_02_Script_WoodenFloor;
extern EvtScript TTYD64_dro_02_Script_EnterSpring;
extern EntryList TTYD64_dro_02_EntryList;
extern EvtScript TTYD64_dro_02_Script_Exit1;
extern EvtScript TTYD64_dro_02_Script_Main_EnterWalk;
extern EvtScript TTYD64_dro_02_Script_InitNewStuff;
extern EvtScript TTYD64_dro_02_Script_Exit2;
extern EvtScript TTYD64_dro_02_Script_MakeExits;

// clang-format off
EvtScript TTYD64_dro_02_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(4858))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_dro_02_Script_WoodenFloor = {
    Set(GameFlag(4859), 1)
    Return
    End
};

EvtScript TTYD64_dro_02_Script_EnterSpring = {
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerJumpscale, Float(1.0))
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Sub(LVar0, 50)
    Add(LVar1, 52)
    Thread
        Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
        Call(SetCamSpeed, 0, Float(3.0))
        Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
        Call(PanToTarget, 0, 0, 1)
    EndThread
    Call(PlayerJump, LVar0, LVar1, LVar2, 20)
    Call(ResetCam, 0, 2000)
    Call(DisablePlayerPhysics, 0)
    Exec(TTYD64_dro_02_Script_MakeExits)
    Return
    End
};

EntryList TTYD64_dro_02_EntryList = {
    { -473.0f, 0.0f, 12.0f, 90.0f },
    { 415.0f, 35.0f, -15.0f, 180.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 61.0f, 108.0f, -196.0f, 0.0f },
    { -476.0f, 0.0f, 101.0f, 0.0f },
};

EvtScript TTYD64_dro_02_Script_Exit1 = {
    Unbind
    Call(DisablePlayerInput, 1)
    Call(DisablePartnerAI, 0)
    Call(GotoMap, (Bytecode) "dro_04", 0)
    Return
    End
};

EvtScript TTYD64_dro_02_Script_Main_EnterWalk = {
    Set(GameByte(425), 9)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeNpcs, 0, Ref(dro_02_DefaultNPCs))
    Call(InitVirtualEntityList)
    ExecWait(dro_02_EVS_MakeEntities)
    ExecWait(dro_02_EVS_SetupRooms)
    Exec(dro_02_EVS_SetupMusic)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseOrEq(2)
    CaseOrEq(3)
        ExecWait(dro_02_EVS_EnterScene)
        EndCaseGroup
    CaseEq(4)
        Exec(TTYD64_dro_02_Script_EnterSpring)
    CaseDefault
        Set(LVar0, Ref(TTYD64_dro_02_Script_MakeExits))
        Exec(EnterWalk)
    EndSwitch
    Wait(1)
    Thread
        Call(SetTexPanner, 162, 1)
        Set(LVar0, 0)
        Label(123)
        Add(LVar0, 420)
        IfGt(LVar0, 0x10000)
            Add(LVar0, -65536)
        EndIf
        Call(SetTexPanOffset, 1, 0, 0, LVar0)
        Wait(1)
        Goto(123)
    EndThread
    Set(MapFlag(0), 0)
    BindTrigger(dro_02_EVS_OnReadPoster, 256, 56, 1, 0)
    Thread
        Loop(0)
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            IfLt(LVar2, -200)
                Call(EnableGroup, 163, 1)
            Else
                Call(EnableGroup, 163, 0)
            EndIf
            Wait(1)
        EndLoop
    EndThread
    Call(SetCamSpeed, 0, Float(1.333984375))
    Return
    End
};

EvtScript TTYD64_dro_02_Script_InitNewStuff = {
    IfEq(GameFlag(4859), 0)
        Call(MakeEntity, Ref(Entity_BoardedFloor), 63, 160, -194, 0, 0x80000000)
        Call(AssignScript, Ref(TTYD64_dro_02_Script_WoodenFloor))
    EndIf
    Call(MakeEntity, Ref(Entity_SuperBlock), -245, 63, -340, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(4858))
    Call(AssignScript, Ref(TTYD64_dro_02_Script_Entity_Shine1))
    BindTrigger(TTYD64_dro_02_Script_Exit1, 128, 60, 1, 0)
    BindTrigger(TTYD64_dro_02_Script_Exit2, 0x80000, 66, 1, 0)
    Return
    End
};

EvtScript TTYD64_dro_02_Script_Exit2 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 5)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "dro_03", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_dro_02_Script_MakeExits = {
    Exec(TTYD64_dro_02_Script_InitNewStuff)
    BindTrigger(dro_02_EVS_ExitWalk_dro_01_1, 0x80000, 4, 1, 0)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_dro_02(void) {
    dro_02_settings.entryList = &TTYD64_dro_02_EntryList;
    dro_02_settings.entryCount = 6;
    Mod_ReplaceScript("TTYD64", &dro_02_EVS_Main, &TTYD64_dro_02_Script_Main_EnterWalk);
}
