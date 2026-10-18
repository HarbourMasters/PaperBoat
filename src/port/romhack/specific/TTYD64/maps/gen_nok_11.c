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

extern NpcGroupList nok_11_DefaultNPCs;
extern EvtScript nok_11_EVS_BindExitTriggers;
extern EvtScript nok_11_EVS_Main;
extern EvtScript nok_11_EVS_MakeEntities;
extern EvtScript nok_11_EVS_SetupMusic;
extern NpcGroupList nok_11_JrTroopaNPCs;
extern NpcGroupList nok_11_KentCKoopaNPCs;
extern MapSettings nok_11_settings;

API_CALLABLE(DisablePlayerInput);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtCollider);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanOffset);
API_CALLABLE(SetTexPanner);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_nok_11_Script_802420D8;
extern EvtScript TTYD64_nok_11_Script_80242240;
extern EvtScript TTYD64_nok_11_Script_Bushes;
extern EntryList TTYD64_nok_11_EntryList;
extern EvtScript TTYD64_nok_11_Script_MoveBushes;
extern EvtScript TTYD64_nok_11_Script_BushesAnimation;
extern EvtScript TTYD64_nok_11_Script_Main_EnterWalk;
extern EvtScript TTYD64_nok_11_Script_ExitWalk_Entry2;

// clang-format off
EvtScript TTYD64_nok_11_Script_802420D8 = {
    Call(SetTexPanner, 59, 0)
    Call(SetTexPanner, 60, 0)
    Call(SetTexPanner, 61, 0)
    Call(SetTexPanner, 62, 0)
    Call(SetTexPanner, 63, 0)
    Call(SetTexPanner, 64, 0)
    Call(SetTexPanner, 65, 0)
    Call(SetTexPanner, 66, 0)
    Call(SetTexPanner, 67, 0)
    Call(SetTexPanner, 68, 0)
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

EvtScript TTYD64_nok_11_Script_80242240 = {
    Thread
        Call(SetTexPanner, 97, 1)
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
    Call(SetTexPanner, 84, 2)
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

EvtScript TTYD64_nok_11_Script_Bushes = {
    Call(SetTexPanner, 106, 0)
    Call(SetTexPanner, 108, 0)
    BindTrigger(TTYD64_nok_11_Script_ExitWalk_Entry2, 0x80000, 30, 1, 0)
    IfEq(GameFlag(4714), 1)
        Call(ModifyColliderFlags, 0, 21, 0x7FFFFE00)
        Call(TranslateModel, 101, -96, 0, 0)
        Call(TranslateModel, 106, -96, 0, 0)
        Call(TranslateModel, 104, 148, 0, 0)
        Call(TranslateModel, 108, 148, 0, 0)
    Else
        BindTrigger(TTYD64_nok_11_Script_MoveBushes, 256, 20, 1, 0)
    EndIf
    Return
    End
};

EntryList TTYD64_nok_11_EntryList = {
    { -758.0f, 0.0f, -49.0f, 90.0f },
    { 886.0f, 0.0f, -40.0f, 270.0f },
    { 155.0f, 16.0f, -240.0f, -180.0f },
};

EvtScript TTYD64_nok_11_Script_MoveBushes = {
    Set(GameFlag(4714), 1)
    Call(DisablePlayerInput, 1)
    Unbind
    Call(PlaySound, 8435)
    Call(GetModelCenter, 32)
    Add(LVar0, -5)
    Add(LVar1, 1)
    Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 15, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(GetModelCenter, 32)
    Add(LVar0, 5)
    Add(LVar1, 1)
    Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 15, 0, 0, 0, 0, 0, 0, 0, 0)
    Wait(10)
    Call(ModifyColliderFlags, 0, 21, 0x7FFFFE00)
    Exec(TTYD64_nok_11_Script_BushesAnimation)
    Thread
        Call(MakeLerp, 0, 148, 30, 5)
        Loop(0)
            Call(UpdateLerp)
            SetF(MapVar(1), LVar0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Call(MakeLerp, 0, 96, 30, 5)
    Loop(0)
        Call(UpdateLerp)
        SetF(MapVar(0), LVar0)
        MulF(MapVar(0), -1)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_nok_11_Script_BushesAnimation = {
    Call(PlaySoundAtCollider, 21, 8351, 0)
    Set(LVar0, MapVar(0))
    Set(LVar1, MapVar(1))
    Set(LVar6, 0)
    Set(LVar7, 0)
    Loop(60)
        SetF(LVar2, MapVar(0))
        SetF(LVar3, MapVar(1))
        SubF(LVar2, LVar0)
        SubF(LVar3, LVar1)
        SetF(LVar4, LVar2)
        SetF(LVar5, LVar3)
        MulF(LVar4, Float(0.09375))
        MulF(LVar5, Float(0.09375))
        MulF(LVar6, Float(0.7998046875))
        MulF(LVar7, Float(0.7998046875))
        AddF(LVar6, LVar4)
        AddF(LVar7, LVar5)
        AddF(LVar0, LVar6)
        AddF(LVar1, LVar7)
        Call(TranslateModel, 101, MapVar(0), 0, 0)
        Call(TranslateModel, 104, MapVar(1), 0, 0)
        Call(TranslateModel, 106, MapVar(0), 0, 0)
        Call(TranslateModel, 108, MapVar(1), 0, 0)
        Call(TTYD64_maps_StretchModel, 101, LVar6)
        Call(TTYD64_maps_StretchModel, 104, LVar7)
        Call(TTYD64_maps_StretchModel, 106, LVar6)
        Call(TTYD64_maps_StretchModel, 108, LVar7)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_nok_11_Script_Main_EnterWalk = {
    Set(GameByte(425), 32)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Set(GameFlag(1968), 1)
    IfEq(GameByte(0), -75)
        Call(MakeNpcs, 0, Ref(nok_11_JrTroopaNPCs))
    Else
        IfGe(GameByte(0), 41)
            IfEq(GameFlag(610), 0)
                Call(MakeNpcs, 0, Ref(nok_11_KentCKoopaNPCs))
            Else
                Call(MakeNpcs, 0, Ref(nok_11_DefaultNPCs))
            EndIf
        Else
            Call(MakeNpcs, 0, Ref(nok_11_DefaultNPCs))
        EndIf
    EndIf
    ExecWait(nok_11_EVS_MakeEntities)
    Exec(TTYD64_nok_11_Script_802420D8)
    Exec(TTYD64_nok_11_Script_80242240)
    Exec(nok_11_EVS_SetupMusic)
    Exec(TTYD64_nok_11_Script_Bushes)
    Call(PlaySound, 0x8000005B)
    Set(LVar0, Ref(nok_11_EVS_BindExitTriggers))
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};

EvtScript TTYD64_nok_11_Script_ExitWalk_Entry2 = {
    Call(UseExitHeading, 60, 2)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "nok_05", 1)
    Wait(100)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_nok_11(void) {
    nok_11_settings.entryList = &TTYD64_nok_11_EntryList;
    nok_11_settings.entryCount = 3;
    Mod_ReplaceScript("TTYD64", &nok_11_EVS_Main, &TTYD64_nok_11_Script_Main_EnterWalk);
}
