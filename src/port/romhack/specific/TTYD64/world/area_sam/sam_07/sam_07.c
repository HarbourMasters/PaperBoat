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

extern BombTrigger sam_07_BombPos_Ice;
extern NpcGroupList sam_07_DefaultNPCs;
extern EvtScript sam_07_EVS_BindExitTriggers;
extern EvtScript sam_07_EVS_Blast_FragileIce;
extern EvtScript sam_07_EVS_EnterMap;
extern EvtScript sam_07_EVS_ExitWalk_sam_04_2;
extern EvtScript sam_07_EVS_ExitWalk_sam_08_0;
extern EvtScript sam_07_EVS_Main;
extern EvtScript sam_07_EVS_SetupMusic;
extern EvtScript sam_07_EVS_TouchFloor_FragileIce;
extern MapSettings sam_07_settings;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnableCameraFollowPlayerY);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableModel);
API_CALLABLE(GetEntryID);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlaySoundAtCollider);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetGroupVisibility);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(TranslateGroup);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseExitHeading);
API_CALLABLE(sam_07_AwaitPlayerNotPoundingFloor);
API_CALLABLE(sam_07_GetEntityPosition);
API_CALLABLE(sam_07_SetEntityPositionF);

extern EntryList TTYD64_sam_07_EntryList;
extern EvtScript TTYD64_sam_07_Script_Main;
extern EvtScript TTYD64_sam_07_Script_80242148;
extern EvtScript TTYD64_sam_07_Script_InitModels;
extern EvtScript TTYD64_sam_07_Script_Exit2;
extern EvtScript TTYD64_sam_07_Script_GreenSwitch;
extern EvtScript TTYD64_sam_07_Script_MakeEntities_New;

// clang-format off
EntryList TTYD64_sam_07_EntryList = {
    { -1500.0f, -120.0f, -75.0f, 90.0f },
    { 1085.0f, 270.0f, -80.0f, 270.0f },
    { -933.0f, -277.0f, -74.0f, -90.0f },
};

EvtScript TTYD64_sam_07_Script_Main = {
    Set(GameByte(425), 43)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Set(GameFlag(1989), 1)
    Call(MakeNpcs, 0, Ref(sam_07_DefaultNPCs))
    ExecWait(TTYD64_sam_07_Script_MakeEntities_New)
    ExecWait(sam_07_EVS_SetupMusic)
    ExecWait(TTYD64_sam_07_Script_InitModels)
    Call(ModifyColliderFlags, 3, 10, 8)
    Call(ModifyColliderFlags, 3, 14, 8)
    Call(ModifyColliderFlags, 3, 11, 8)
    Call(ModifyColliderFlags, 3, 15, 8)
    Call(ModifyColliderFlags, 3, 1, 8)
    Call(ModifyColliderFlags, 3, 6, 8)
    Exec(sam_07_EVS_EnterMap)
    Wait(1)
    Return
    End
};

EvtScript TTYD64_sam_07_Script_80242148 = {
    BindTrigger(sam_07_EVS_ExitWalk_sam_04_2, 0x80000, 1, 1, 0)
    BindTrigger(sam_07_EVS_ExitWalk_sam_08_0, 0x80000, 6, 1, 0)
    BindTrigger(TTYD64_sam_07_Script_Exit2, 0x80000, 30, 1, 0)
    Return
    End
};

EvtScript TTYD64_sam_07_Script_InitModels = {
    Call(EnableGroup, 137, 1)
    Call(ModifyColliderFlags, 0, 23, 0x7FFFFE00)
    Call(ParentColliderToModel, 22, 22)
    Call(ParentColliderToModel, 24, 22)
    IfEq(GameFlag(1454), 0)
        Call(EnableModel, 136, 1)
        Switch(GameByte(4326))
        CaseEq(0)
            Set(LVar0, 0)
        CaseEq(1)
            Set(LVar0, -180)
        CaseEq(2)
            Set(LVar0, -278)
        EndSwitch
        Call(TranslateGroup, 134, 0, LVar0, 0)
        Call(UpdateColliderTransform, 22)
        Call(UpdateColliderTransform, 24)
        BindTrigger(sam_07_EVS_TouchFloor_FragileIce, 128, 24, 1, 0)
        BindTrigger(sam_07_EVS_Blast_FragileIce, 0x100000, Ref(sam_07_BombPos_Ice), 1, 0)
    Else
        Call(ModifyColliderFlags, 0, 24, 0x7FFFFE00)
        Call(SetGroupVisibility, 134, 0)
        Call(EnableModel, 22, 1)
        Call(EnableModel, 23, 1)
        Call(EnableModel, 135, 1)
        Switch(GameByte(4326))
        CaseEq(0)
            Call(EnableModel, 135, 1)
        CaseEq(1)
            Call(EnableModel, 136, 1)
            Call(TranslateGroup, 134, 0, -180, 0)
            Call(UpdateColliderTransform, 22)
        CaseEq(2)
            Call(EnableModel, 136, 1)
            Call(TranslateGroup, 134, 0, -278, 0)
            Call(UpdateColliderTransform, 22)
        EndSwitch
    EndIf
    Return
    End
};

EvtScript TTYD64_sam_07_Script_Exit2 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 2)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "sam_13", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_sam_07_Script_GreenSwitch = {
    Call(DisablePlayerInput, 1)
    Call(sam_07_GetEntityPosition, MapVar(0), LVar7, LVar8, LVar9)
    Switch(GameByte(4326))
    CaseEq(0)
        Call(EnableModel, 136, 1)
        Call(EnableModel, 135, 0)
        Call(PlaySoundAtCollider, 22, 922, 0)
        Call(MakeLerp, 0, -180, 120, 10)
        Label(0)
        Call(UpdateLerp)
        Call(TranslateModel, 22, 0, LVar0, 0)
        Call(TranslateModel, 23, 0, LVar0, 0)
        Call(UpdateColliderTransform, 22)
        Add(LVar0, LVar8)
        Call(sam_07_SetEntityPositionF, MapVar(0), LVar7, LVar0, LVar9)
        Call(EnableCameraFollowPlayerY)
        Wait(1)
        Call(sam_07_AwaitPlayerNotPoundingFloor, 22, 16384)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
        Set(GameByte(4326), 1)
    CaseEq(1)
        Call(EnableModel, 136, 1)
        Call(EnableModel, 135, 0)
        Sub(LVar8, -180)
        Call(PlaySoundAtCollider, 22, 922, 0)
        Call(MakeLerp, -180, -278, 120, 10)
        Label(1)
        Call(UpdateLerp)
        Call(TranslateModel, 22, 0, LVar0, 0)
        Call(TranslateModel, 23, 0, LVar0, 0)
        Call(UpdateColliderTransform, 22)
        Add(LVar0, LVar8)
        Call(sam_07_SetEntityPositionF, MapVar(0), LVar7, LVar0, LVar9)
        Call(EnableCameraFollowPlayerY)
        Wait(1)
        Call(sam_07_AwaitPlayerNotPoundingFloor, 22, 16384)
        IfEq(LVar1, 1)
            Goto(1)
        EndIf
        Set(GameByte(4326), 2)
    CaseEq(2)
        Call(PlaySoundAtCollider, 22, 921, 0)
        Sub(LVar8, -278)
        Call(MakeLerp, -278, 0, 120, 10)
        Label(2)
        Call(UpdateLerp)
        Call(TranslateModel, 22, 0, LVar0, 0)
        Call(TranslateModel, 23, 0, LVar0, 0)
        Call(UpdateColliderTransform, 22)
        Add(LVar0, LVar8)
        Call(sam_07_SetEntityPositionF, MapVar(0), LVar7, LVar0, LVar9)
        Call(EnableCameraFollowPlayerY)
        Wait(1)
        Call(sam_07_AwaitPlayerNotPoundingFloor, 22, 16384)
        IfEq(LVar1, 1)
            Goto(2)
        EndIf
        Call(EnableModel, 135, 1)
        Call(EnableModel, 136, 0)
        Set(GameByte(4326), 0)
    EndSwitch
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_sam_07_Script_MakeEntities_New = {
    IfEq(GameFlag(1454), 0)
        Set(GameByte(4326), 1)
    EndIf
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 2)
        Set(GameByte(4326), 2)
    EndIf
    Switch(GameByte(4326))
    CaseEq(0)
        Call(MakeEntity, Ref(Entity_GreenStompSwitch), -945, 1, -75, 0, 0x80000000)
        Set(MapVar(0), LVar0)
        Call(AssignScript, Ref(TTYD64_sam_07_Script_GreenSwitch))
    CaseEq(1)
        Call(MakeEntity, Ref(Entity_GreenStompSwitch), -945, -179, -75, 0, 0x80000000)
        Set(MapVar(0), LVar0)
        Call(AssignScript, Ref(TTYD64_sam_07_Script_GreenSwitch))
    CaseEq(2)
        Call(MakeEntity, Ref(Entity_GreenStompSwitch), -945, -277, -75, 0, 0x80000000)
        Set(MapVar(0), LVar0)
        Call(AssignScript, Ref(TTYD64_sam_07_Script_GreenSwitch))
    EndSwitch
    Call(MakeEntity, Ref(Entity_BrickBlock), 810, 330, -120, 90, 0x80000000)
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), 810, 360, -120, 90, 142, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1456))
    Call(MakeEntity, Ref(Entity_SavePoint), -1350, -60, -120, 0, 0x80000000)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_sam_07(void) {
    sam_07_settings.entryList = &TTYD64_sam_07_EntryList;
    sam_07_settings.entryCount = 3;
    Mod_ReplaceScript("TTYD64", &sam_07_EVS_Main, &TTYD64_sam_07_Script_Main);
    Mod_ReplaceScript("TTYD64", &sam_07_EVS_BindExitTriggers, &TTYD64_sam_07_Script_80242148);
}
