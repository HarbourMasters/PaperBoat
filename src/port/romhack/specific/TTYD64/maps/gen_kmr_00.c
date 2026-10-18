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

extern EvtScript kmr_00_EVS_MakeEntities;
extern MapSettings kmr_00_settings;

API_CALLABLE(AssignPanelFlag);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlaySoundAtCollider);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_kmr_00_Script_MakeEntities;
extern EvtScript TTYD64_kmr_00_Script_BushesAnimation;
extern EvtScript TTYD64_kmr_00_Script_MoveBushes;
extern EvtScript TTYD64_kmr_00_Script_InitNewStuff;
extern EvtScript TTYD64_kmr_00_Script_Exit1;
extern EntryList TTYD64_kmr_00_EntryList;

// clang-format off
EvtScript TTYD64_kmr_00_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_HiddenPanel), 0, 0, 0, 0, 2, 0x80000000)
    Call(AssignPanelFlag, GameFlag(86))
    Exec(TTYD64_kmr_00_Script_InitNewStuff)
    Return
    End
};

EvtScript TTYD64_kmr_00_Script_BushesAnimation = {
    Call(PlaySoundAtCollider, 11, 8351, 0)
    Thread
        Set(LVar0, MapVar(4))
        Set(LVar6, 0)
        Set(LVar7, 0)
        Loop(60)
            SetF(LVar2, MapVar(4))
            SubF(LVar2, LVar0)
            SetF(LVar4, LVar2)
            MulF(LVar4, Float(0.09375))
            MulF(LVar6, Float(0.7998046875))
            MulF(LVar7, Float(0.7998046875))
            AddF(LVar6, LVar4)
            AddF(LVar0, LVar6)
            Call(TranslateModel, 83, MapVar(4), 0, 0)
            Call(TTYD64_maps_StretchModel, 83, LVar6)
            Wait(1)
        EndLoop
    EndThread
    Thread
        Set(LVar0, MapVar(3))
        Set(LVar6, 0)
        Set(LVar7, 0)
        Loop(60)
            SetF(LVar2, MapVar(3))
            SubF(LVar2, LVar0)
            SetF(LVar4, LVar2)
            MulF(LVar4, Float(0.09375))
            MulF(LVar6, Float(0.7998046875))
            MulF(LVar7, Float(0.7998046875))
            AddF(LVar6, LVar4)
            AddF(LVar0, LVar6)
            Call(TranslateModel, 82, MapVar(3), 0, 0)
            Call(TTYD64_maps_StretchModel, 82, LVar6)
            Wait(1)
        EndLoop
    EndThread
    Set(LVar0, MapVar(2))
    Set(LVar6, 0)
    Set(LVar7, 0)
    Loop(60)
        SetF(LVar2, MapVar(2))
        SubF(LVar2, LVar0)
        SetF(LVar4, LVar2)
        MulF(LVar4, Float(0.09375))
        MulF(LVar6, Float(0.7998046875))
        MulF(LVar7, Float(0.7998046875))
        AddF(LVar6, LVar4)
        AddF(LVar0, LVar6)
        Call(TranslateModel, 81, MapVar(2), 0, 0)
        Call(TTYD64_maps_StretchModel, 81, LVar6)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_kmr_00_Script_MoveBushes = {
    Set(GameFlag(4207), 1)
    Call(DisablePlayerInput, 1)
    Unbind
    Call(ModifyColliderFlags, 0, 11, 0x7FFFFE00)
    Exec(TTYD64_kmr_00_Script_BushesAnimation)
    Thread
        Call(MakeLerp, 0, 35, 30, 5)
        Loop(0)
            Call(UpdateLerp)
            SetF(MapVar(4), LVar0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Thread
        Call(MakeLerp, 0, 37, 30, 5)
        Loop(0)
            Call(UpdateLerp)
            SetF(MapVar(3), LVar0)
            MulF(MapVar(3), -1)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Call(MakeLerp, 0, 125, 30, 5)
    Loop(0)
        Call(UpdateLerp)
        SetF(MapVar(2), LVar0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_kmr_00_Script_InitNewStuff = {
    IfEq(GameFlag(4207), 1)
        Call(ModifyColliderFlags, 0, 11, 0x7FFFFE00)
        Call(TranslateModel, 81, 90, 0, 0)
        Call(TranslateModel, 82, -37, 0, 0)
        Call(TranslateModel, 83, 35, 0, 0)
    Else
        BindTrigger(TTYD64_kmr_00_Script_MoveBushes, 256, 11, 1, 0)
    EndIf
    BindTrigger(TTYD64_kmr_00_Script_Exit1, 128, 25, 1, 0)
    Return
    End
};

EvtScript TTYD64_kmr_00_Script_Exit1 = {
    Call(UseExitHeading, 60, 1)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "kmr_34", 0)
    Wait(100)
    Return
    End
};

EntryList TTYD64_kmr_00_EntryList = {
    { 485.0f, 0.0f, 0.0f, 270.0f },
    { 0.0f, 0.0f, -308.0f, -180.0f },
};
// clang-format on

void TTYD64_InstallMap_kmr_00(void) {
    kmr_00_settings.entryList = &TTYD64_kmr_00_EntryList;
    kmr_00_settings.entryCount = 2;
    Mod_ReplaceScript("TTYD64", &kmr_00_EVS_MakeEntities, &TTYD64_kmr_00_Script_MakeEntities);
}
