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

extern NpcGroupList iwa_10_DefaultNPCs;
extern EvtScript iwa_10_EVS_ArriveFromToadTown;
extern EvtScript iwa_10_EVS_BindExitTriggers;
extern EvtScript iwa_10_EVS_InitializeTrainScene;
extern EvtScript iwa_10_EVS_Main;
extern EvtScript iwa_10_EVS_MakeEntities;
extern EvtScript iwa_10_EVS_OnSmashBlock;
extern EvtScript iwa_10_EVS_Scene_MeetParakarry;
extern EvtScript iwa_10_EVS_SetupFoliage;
extern MapSettings iwa_10_settings;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(ClearDefeatedEnemies);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnableTexPanning);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetLoadType);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlaySoundAtCollider);
API_CALLABLE(PlaySoundAtF);
API_CALLABLE(RotateModel);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanOffset);
API_CALLABLE(SetTexPanner);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseExitHeading);
API_CALLABLE(iwa_10_GetClockHandAngles);

extern EvtScript TTYD64_iwa_10_Script_EnterWalk;
extern EvtScript TTYD64_iwa_10_Script_Main;
extern EvtScript TTYD64_iwa_10_Script_BushesAnimation;
extern EvtScript TTYD64_iwa_10_Script_BindBushes;
extern EvtScript TTYD64_iwa_10_Script_Entity_Shine1;
extern EvtScript TTYD64_iwa_10_Script_MakeEntities;
extern EvtScript TTYD64_iwa_10_Script_MoveBushes;
extern EvtScript TTYD64_iwa_10_Script_Exit2;
extern EntryList TTYD64_iwa_10_EntryList;

// clang-format off
EvtScript TTYD64_iwa_10_Script_EnterWalk = {
    Call(GetLoadType, LVar1)
    IfEq(LVar1, 1)
        Exec(EnterSavePoint)
        Exec(iwa_10_EVS_BindExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 0)
        Exec(iwa_10_EVS_ArriveFromToadTown)
        Exec(iwa_10_EVS_BindExitTriggers)
    Else
        Set(LVar0, Ref(iwa_10_EVS_BindExitTriggers))
        Exec(EnterWalk)
    EndIf
    Return
    End
};

EvtScript TTYD64_iwa_10_Script_Main = {
    Set(GameByte(425), 8)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamLeadPlayer, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Set(GameFlag(1971), 1)
    Call(MakeNpcs, 1, Ref(iwa_10_DefaultNPCs))
    Call(ClearDefeatedEnemies)
    ExecWait(iwa_10_EVS_MakeEntities)
    ExecWait(iwa_10_EVS_InitializeTrainScene)
    Exec(TTYD64_iwa_10_Script_EnterWalk)
    Wait(1)
    Exec(TTYD64_iwa_10_Script_BindBushes)
    Exec(iwa_10_EVS_SetupFoliage)
    Call(PlaySoundAtF, 0x80000009, 1, -560, 0, -233)
    Thread
        Set(LVarF, 0)
        Label(10)
        Add(LVarF, 1)
        Call(iwa_10_GetClockHandAngles)
        Call(RotateModel, 91, LVar0, 0, 0, -1)
        Call(RotateModel, 93, LVar1, 0, 0, -1)
        Wait(10)
        Goto(10)
    EndThread
    Thread
        Call(SetTexPanner, 106, 2)
        Call(SetTexPanner, 104, 2)
        Call(EnableTexPanning, 106, 1)
        Call(EnableTexPanning, 104, 1)
        Set(LVar0, 0)
        Label(20)
        Sub(LVar0, 3000)
        Call(SetTexPanOffset, 2, 0, 0, LVar0)
        Wait(1)
        Goto(20)
    EndThread
    IfLt(GameByte(0), -71)
        Exec(iwa_10_EVS_Scene_MeetParakarry)
    EndIf
    Return
    End
};

EvtScript TTYD64_iwa_10_Script_BushesAnimation = {
    Call(PlaySoundAtCollider, 100, 8351, 0)
    Set(LVar0, MapVar(2))
    Set(LVar1, MapVar(3))
    Set(LVar6, 0)
    Set(LVar7, 0)
    Loop(60)
        SetF(LVar2, MapVar(2))
        SetF(LVar3, MapVar(3))
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
        Call(TranslateModel, 119, MapVar(2), 0, 0)
        Call(TranslateModel, 121, MapVar(3), 0, 0)
        Call(TTYD64_maps_StretchModel, 119, LVar6)
        Call(TTYD64_maps_StretchModel, 121, LVar7)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_iwa_10_Script_BindBushes = {
    Call(SetMusic, 0, 22, 0, 8)
    IfEq(GameFlag(4819), 1)
        Call(ModifyColliderFlags, 0, 100, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 92, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 93, 0x7FFFFE00)
        Call(TranslateModel, 119, -50, 0, 0)
        Call(TranslateModel, 121, 60, 0, 0)
    Else
        BindTrigger(TTYD64_iwa_10_Script_MoveBushes, 256, 100, 1, 0)
    EndIf
    BindTrigger(TTYD64_iwa_10_Script_Exit2, 128, 102, 1, 0)
    Return
    End
};

EvtScript TTYD64_iwa_10_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(11))
    SetConst(LVar1, GameFlag(721))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_iwa_10_Script_MakeEntities = {
    IfEq(GameFlag(720), 0)
        Call(MakeEntity, Ref(Entity_Hammer2BlockWideZ), -1040, 160, -425, 0, 0x80000000)
        Call(AssignScript, Ref(iwa_10_EVS_OnSmashBlock))
    EndIf
    Call(MakeEntity, Ref(Entity_SuperBlock), -1350, 220, -210, 0, 0x80000000)
    Set(MapVar(11), LVar0)
    Call(AssignBlockFlag, GameFlag(721))
    Call(AssignScript, Ref(TTYD64_iwa_10_Script_Entity_Shine1))
    Call(MakeEntity, Ref(Entity_ArrowSign), -780, 0, -227, -15, 270, 0x80000000)
    Call(MakeEntity, Ref(Entity_ArrowSign), -1157, 70, -282, 40, 120, 0x80000000)
    Call(MakeEntity, Ref(Entity_ArrowSign), -901, 185, -555, 0, 120, 0x80000000)
    Call(MakeEntity, Ref(Entity_SavePoint), -525, 80, 115, 0, 0x80000000)
    Call(MakeEntity, Ref(Entity_HeartBlock), -730, 275, -510, 0, 0x80000000)
    Return
    End
};

EvtScript TTYD64_iwa_10_Script_MoveBushes = {
    Set(GameFlag(4819), 1)
    Call(DisablePlayerInput, 1)
    Unbind
    Call(ModifyColliderFlags, 0, 100, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 92, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 93, 0x7FFFFE00)
    Exec(TTYD64_iwa_10_Script_BushesAnimation)
    Thread
        Call(MakeLerp, 0, 50, 30, 5)
        Loop(0)
            Call(UpdateLerp)
            SetF(MapVar(3), LVar0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Call(MakeLerp, 0, 60, 30, 5)
    Loop(0)
        Call(UpdateLerp)
        SetF(MapVar(2), LVar0)
        MulF(MapVar(2), -1)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_iwa_10_Script_Exit2 = {
    Call(UseExitHeading, 60, 2)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "iwa_11", 2)
    Wait(100)
    Return
    End
};

EntryList TTYD64_iwa_10_EntryList = {
    { -1250.0f, 30.0f, 0.0f, 90.0f },
    { -445.0f, 215.0f, -500.0f, 270.0f },
    { -1064.0f, 0.0f, 0.0f, 90.0f },
};
// clang-format on

void TTYD64_InstallMap_iwa_10(void) {
    iwa_10_settings.entryList = &TTYD64_iwa_10_EntryList;
    iwa_10_settings.entryCount = 3;
    Mod_ReplaceScript("TTYD64", &iwa_10_EVS_Main, &TTYD64_iwa_10_Script_Main);
    Mod_ReplaceScript("TTYD64", &iwa_10_EVS_MakeEntities, &TTYD64_iwa_10_Script_MakeEntities);
}
