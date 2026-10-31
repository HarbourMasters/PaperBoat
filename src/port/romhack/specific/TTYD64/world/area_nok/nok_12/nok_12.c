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

extern NpcGroupList nok_12_DefaultNPCs;
extern NpcGroupList nok_12_DemoNPCs;
extern EvtScript nok_12_EVS_EnterMap;
extern EvtScript nok_12_EVS_Main;
extern EvtScript nok_12_EVS_MakeEntities;
extern EvtScript nok_12_EVS_PlayDemoScene1;
extern EvtScript nok_12_EVS_PlayDemoScene2;
extern EvtScript nok_12_EVS_SetupBridge;
extern EvtScript nok_12_EVS_SetupFoliage;
extern EvtScript nok_12_EVS_SetupMusic;
extern EvtScript nok_12_EVS_UpdateEnounterStages;

API_CALLABLE(DeleteTrigger);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(GetDemoState);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetModelCenter);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(RotateModel);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanOffset);
API_CALLABLE(SetTexPanner);
API_CALLABLE(UpdateLerp);

extern EvtScript TTYD64_nok_12_Script_80242290;
extern EvtScript TTYD64_nok_12_Script_802423DC;
extern EvtScript TTYD64_nok_12_Script_CanesBadge;
extern EvtScript TTYD64_nok_12_Script_Cane_C2;
extern EvtScript TTYD64_nok_12_Script_Cane_C4;
extern EvtScript TTYD64_nok_12_Script_Cane_Main;
extern EvtScript TTYD64_nok_12_Script_Main;
extern EvtScript TTYD64_nok_12_Script_Cane_C1;
extern EvtScript TTYD64_nok_12_Script_Cane_C3;
extern EvtScript TTYD64_nok_12_Script_Cane_C5;

// clang-format off
EvtScript TTYD64_nok_12_Script_80242290 = {
    SetGroup(0)
    Call(SetTexPanner, 188, 0)
    Call(SetTexPanner, 189, 0)
    Call(SetTexPanner, 190, 0)
    Call(SetTexPanner, 191, 0)
    Call(SetTexPanner, 192, 0)
    Call(SetTexPanner, 193, 0)
    Call(SetTexPanner, 194, 0)
    Call(SetTexPanner, 195, 0)
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

EvtScript TTYD64_nok_12_Script_802423DC = {
    SetGroup(0)
    Thread
        Call(SetTexPanner, 197, 1)
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
    Call(SetTexPanner, 33, 2)
    Call(SetTexPanner, 34, 2)
    Call(SetTexPanner, 35, 2)
    Call(SetTexPanner, 31, 2)
    Call(SetTexPanner, 32, 2)
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

EvtScript TTYD64_nok_12_Script_CanesBadge = {
    IfEq(GameFlag(4715), 0)
        BindTrigger(TTYD64_nok_12_Script_Cane_C1, 256, 39, 1, MapVar(2))
        BindTrigger(TTYD64_nok_12_Script_Cane_C2, 256, 40, 1, MapVar(3))
        BindTrigger(TTYD64_nok_12_Script_Cane_C3, 256, 41, 1, MapVar(4))
        BindTrigger(TTYD64_nok_12_Script_Cane_C4, 256, 42, 1, MapVar(5))
        BindTrigger(TTYD64_nok_12_Script_Cane_C5, 256, 43, 1, MapVar(6))
    EndIf
    Return
    End
};

EvtScript TTYD64_nok_12_Script_Cane_C2 = {
    Set(LVar5, 2)
    Set(LVar6, 209)
    ExecWait(TTYD64_nok_12_Script_Cane_Main)
    Return
    End
};

EvtScript TTYD64_nok_12_Script_Cane_C4 = {
    Set(LVar5, 4)
    Set(LVar6, 213)
    ExecWait(TTYD64_nok_12_Script_Cane_Main)
    Return
    End
};

EvtScript TTYD64_nok_12_Script_Cane_Main = {
    Switch(LVar5)
    CaseEq(1)
        IfEq(MapVar(1), 2)
            Set(LVar7, 1)
        Else
            Set(LVar7, 0)
        EndIf
    CaseEq(2)
        IfEq(MapVar(1), 5)
            Set(LVar7, 1)
        Else
            Set(LVar7, 0)
        EndIf
    CaseEq(3)
        IfEq(MapVar(1), 1)
            Set(LVar7, 1)
        Else
            Set(LVar7, 0)
        EndIf
    CaseEq(4)
        IfEq(MapVar(1), 0)
            Set(LVar7, 1)
        Else
            Set(LVar7, 0)
        EndIf
    CaseEq(5)
        IfEq(MapVar(1), 4)
            Set(LVar7, 1)
        Else
            Set(LVar7, 0)
        EndIf
    EndSwitch
    IfEq(LVar7, 0)
        Call(PlaySound, 541)
        Set(MapVar(1), 0)
        SetGroup(0)
        SuspendGroup(2)
        Call(DisablePlayerInput, 1)
        Call(MakeLerp, 0, -5, 3, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, LVar6, LVar0, 0, 1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(MakeLerp, -5, 5, 6, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, LVar6, LVar0, 0, 1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(MakeLerp, 5, 0, 3, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, LVar6, LVar0, 0, 1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        ResumeGroup(2)
        Call(DisablePlayerInput, 0)
    Else
        Set(MapVar(1), LVar5)
        Call(PlaySound, 11)
        IfEq(MapVar(1), 3)
            SetGroup(0)
            SuspendGroup(2)
            Call(DisablePlayerInput, 1)
            Call(PlaySound, 8435)
            Call(GetModelCenter, 211)
            Add(LVar0, -2)
            Add(LVar1, 5)
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 15, 0, 0, 0, 0, 0, 0, 0, 0)
            Call(GetModelCenter, 211)
            Add(LVar0, 6)
            Add(LVar1, 5)
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 15, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(10)
            Call(MakeItemEntity, 386, -40, 216, -176, 13, GameFlag(4715))
            Wait(35)
            Call(DeleteTrigger, MapVar(2))
            Call(DeleteTrigger, MapVar(3))
            Call(DeleteTrigger, MapVar(4))
            Call(DeleteTrigger, MapVar(5))
            Call(DeleteTrigger, MapVar(6))
            ResumeGroup(2)
            Call(DisablePlayerInput, 0)
        EndIf
    EndIf
    Return
    End
};

EvtScript TTYD64_nok_12_Script_Main = {
    Set(GameByte(425), 32)
    Call(SetSpriteShading, -1)
    Set(AreaFlag(1), 0)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(GetDemoState, LVar0)
    IfEq(LVar0, 0)
        Call(MakeNpcs, 0, Ref(nok_12_DefaultNPCs))
    Else
        Call(GetEntryID, LVar0)
        IfEq(LVar0, 2)
            Call(MakeNpcs, 0, Ref(nok_12_DemoNPCs))
        EndIf
    EndIf
    ExecWait(nok_12_EVS_MakeEntities)
    ExecWait(nok_12_EVS_SetupFoliage)
    Exec(TTYD64_nok_12_Script_80242290)
    Exec(TTYD64_nok_12_Script_802423DC)
    Exec(nok_12_EVS_SetupBridge)
    Call(GetDemoState, LVar0)
    IfNe(LVar0, 0)
        Call(GetEntryID, LVar0)
        IfEq(LVar0, 2)
            ExecWait(nok_12_EVS_PlayDemoScene1)
        Else
            ExecWait(nok_12_EVS_PlayDemoScene2)
        EndIf
        Return
    EndIf
    Exec(nok_12_EVS_UpdateEnounterStages)
    Exec(nok_12_EVS_SetupMusic)
    Exec(nok_12_EVS_EnterMap)
    Exec(TTYD64_nok_12_Script_CanesBadge)
    Wait(1)
    Set(GameFlag(263), 0)
    Return
    End
};

EvtScript TTYD64_nok_12_Script_Cane_C1 = {
    Set(LVar5, 1)
    Set(LVar6, 207)
    ExecWait(TTYD64_nok_12_Script_Cane_Main)
    Return
    End
};

EvtScript TTYD64_nok_12_Script_Cane_C3 = {
    Set(LVar5, 3)
    Set(LVar6, 211)
    ExecWait(TTYD64_nok_12_Script_Cane_Main)
    Return
    End
};

EvtScript TTYD64_nok_12_Script_Cane_C5 = {
    Set(LVar5, 5)
    Set(LVar6, 215)
    ExecWait(TTYD64_nok_12_Script_Cane_Main)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_nok_12(void) {
    Mod_ReplaceScript("TTYD64", &nok_12_EVS_Main, &TTYD64_nok_12_Script_Main);
}
