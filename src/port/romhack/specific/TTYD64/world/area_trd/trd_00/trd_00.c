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

extern EvtScript trd_00_D_80240B34_99A7A4;
extern NpcGroupList trd_00_DefaultNPCs;
extern EvtScript trd_00_EVS_BindExitTriggers;
extern EvtScript trd_00_EVS_EnterMap;
extern EvtScript trd_00_EVS_ExitDoors_trd_01_0;
extern EvtScript trd_00_EVS_ExitDoors_trd_05_1;
extern EvtScript trd_00_EVS_ExitWalk_nok_15_1;
extern EvtScript trd_00_EVS_ExitWalk_nok_15_2;
extern EvtScript trd_00_EVS_ExitWalk_trd_05_2;
extern EvtScript trd_00_EVS_Main;
extern EvtScript trd_00_EVS_MakeEntities;
extern EvtScript trd_00_EVS_SetupMusic;
extern EvtScript trd_00_EVS_UpdateTexturePan;
extern MapSettings trd_00_settings;

API_CALLABLE(EnableTexPanning);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetLoadType);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetGroupVisibility);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanOffset);
API_CALLABLE(SetTexPanner);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_trd_00_Script_ExitWalk_Exit5;
extern EntryList TTYD64_trd_00_EntryList;
extern EvtScript TTYD64_trd_00_Script_80240A98;
extern EvtScript TTYD64_trd_00_Script_80240F8C;
extern EvtScript TTYD64_trd_00_Script_EnterWalk_80240D8C;
extern EvtScript TTYD64_trd_00_Script_Main;

// clang-format off
EvtScript TTYD64_trd_00_Script_ExitWalk_Exit5 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 6)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "trd_11", 0)
    Wait(100)
    Return
    End
};

EntryList TTYD64_trd_00_EntryList = {
    { -973.0f, 0.0f, 204.0f, 90.0f },
    { -525.0f, 0.0f, 130.0f, 240.0f },
    { 400.0f, 0.0f, 185.0f, 180.0f },
    { 587.0f, 0.0f, 6.0f, 90.0f },
    { -955.0f, 200.0f, -101.0f, 90.0f },
    { -518.0f, 0.0f, 212.0f, 240.0f },
    { -589.0f, 205.0f, -39.0f, -90.0f },
};

EvtScript TTYD64_trd_00_Script_80240A98 = {
    BindTrigger(trd_00_EVS_ExitWalk_nok_15_1, 0x80000, 1, 1, 0)
    BindTrigger(trd_00_EVS_ExitDoors_trd_01_0, 256, 6, 1, 0)
    BindTrigger(trd_00_EVS_ExitDoors_trd_05_1, 256, 11, 1, 0)
    BindTrigger(trd_00_EVS_ExitWalk_trd_05_2, 0x80000, 19, 1, 0)
    BindTrigger(trd_00_EVS_ExitWalk_nok_15_2, 0x80000, 15, 1, 0)
    BindTrigger(TTYD64_trd_00_Script_ExitWalk_Exit5, 0x80000, 34, 1, 0)
    Return
    End
};

EvtScript TTYD64_trd_00_Script_80240F8C = {
    SetGroup(0)
    Call(SetTexPanner, 2, 1)
    Set(LVar0, 0)
    Set(LVar1, 0)
    Label(10)
    Call(SetTexPanOffset, 1, 0, LVar0, 0)
    Call(SetTexPanOffset, 1, 1, LVar1, 0)
    Add(LVar0, 100)
    Sub(LVar1, 100)
    Wait(1)
    Goto(10)
    Return
    End
};

EvtScript TTYD64_trd_00_Script_EnterWalk_80240D8C = {
    SetGroup(0)
    SuspendGroup(1)
    Call(GetLoadType, LVar1)
    IfEq(LVar1, 1)
        Exec(EnterSavePoint)
        Exec(trd_00_EVS_BindExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        IfLt(GameByte(0), -90)
            Set(GameByte(0), -90)
            ExecWait(trd_00_D_80240B34_99A7A4)
            Exec(trd_00_EVS_BindExitTriggers)
        Else
            Set(LVar0, Ref(trd_00_EVS_BindExitTriggers))
            Exec(EnterWalk)
        EndIf
    CaseEq(1)
        Set(LVar2, 67)
        Set(LVar3, 65)
        ExecWait(EnterDoubleDoor)
        Exec(trd_00_EVS_BindExitTriggers)
    CaseEq(2)
        Set(LVar2, 71)
        Set(LVar3, 69)
        ExecWait(EnterDoubleDoor)
        Exec(trd_00_EVS_BindExitTriggers)
    CaseEq(3)
        Set(LVar0, Ref(trd_00_EVS_BindExitTriggers))
        Exec(EnterWalk)
    CaseOrEq(4)
    CaseOrEq(6)
        Set(LVar0, Ref(trd_00_EVS_BindExitTriggers))
        Exec(EnterWalk)
        EndCaseGroup
    CaseEq(5)
        Exec(trd_00_EVS_BindExitTriggers)
    EndSwitch
    ResumeGroup(1)
    Return
    End
};

EvtScript TTYD64_trd_00_Script_Main = {
    Set(GameByte(425), 7)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Set(GameFlag(1970), 1)
    Call(MakeNpcs, 1, Ref(trd_00_DefaultNPCs))
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
    CaseOrEq(1)
    CaseOrEq(4)
    CaseOrEq(6)
    EndSwitch
    ExecWait(trd_00_EVS_MakeEntities)
    Exec(TTYD64_trd_00_Script_80240F8C)
    Exec(trd_00_EVS_SetupMusic)
    Wait(1)
    IfEq(GameFlag(658), 0)
        Call(SetGroupVisibility, 80, 0)
    Else
        Call(ModifyColliderFlags, 0, 20, 0x7FFFFE00)
        Call(SetGroupVisibility, 77, 0)
    EndIf
    Exec(trd_00_EVS_EnterMap)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 5)
        Wait(65)
    Else
        Wait(1)
    EndIf
    Call(EnableTexPanning, 4, 1)
    Thread
        Set(LVar0, 2)
        Set(LVar1, 0)
        Set(LVar2, 90)
        Set(LVar3, -60)
        Set(LVar4, -70)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(trd_00_EVS_UpdateTexturePan)
    EndThread
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_trd_00(void) {
    trd_00_settings.entryList = &TTYD64_trd_00_EntryList;
    trd_00_settings.entryCount = 7;
    Mod_ReplaceScript("TTYD64", &trd_00_EVS_BindExitTriggers, &TTYD64_trd_00_Script_80240A98);
    Mod_ReplaceScript("TTYD64", &trd_00_EVS_EnterMap, &TTYD64_trd_00_Script_EnterWalk_80240D8C);
    Mod_ReplaceScript("TTYD64", &trd_00_EVS_Main, &TTYD64_trd_00_Script_Main);
}
