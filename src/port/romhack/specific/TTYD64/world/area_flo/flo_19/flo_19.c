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

extern EvtScript flo_19_EVS_BindExitTriggers;
extern EvtScript flo_19_EVS_Enter_Beanstalk;
extern EvtScript flo_19_EVS_Exit_Beanstalk;
extern EvtScript flo_19_EVS_Main;
extern EvtScript flo_19_EVS_MakeEntities;
extern EvtScript flo_19_EVS_Scene_BeanstalkGrowing;
extern EvtScript flo_19_EVS_SetupClouds;
extern EvtScript flo_19_EVS_SetupMusic;
extern EvtScript flo_19_EVS_UpdateTexturePan;
extern MapSettings flo_19_settings;

API_CALLABLE(EnableTexPanning);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetLoadType);
API_CALLABLE(GotoMap);
API_CALLABLE(HidePlayerShadow);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(UseExitHeading);
API_CALLABLE(flo_19_SpawnSunEffect);

extern EvtScript TTYD64_flo_19_Script_80240AC0;
extern EvtScript TTYD64_flo_19_Script_InitNewStuff;
extern EvtScript TTYD64_flo_19_Script_Exit1;
extern EvtScript TTYD64_flo_19_Script_Main_EnterWalk;
extern EvtScript TTYD64_flo_19_Script_BindExit0;
extern EntryList TTYD64_flo_19_EntryList;

// clang-format off
EvtScript TTYD64_flo_19_Script_80240AC0 = {
    Call(MakeItemEntity, 371, -200, 160, -213, 17, GameFlag(1391))
    Return
    End
};

EvtScript TTYD64_flo_19_Script_InitNewStuff = {
    Call(MakeEntity, Ref(Entity_SavePoint), 68, 61, -144, 0, 0x80000000)
    Call(MakeEntity, Ref(Entity_HeartBlock), 119, 61, -144, 0, 0x80000000)
    BindTrigger(TTYD64_flo_19_Script_Exit1, 0x80000, 17, 1, 0)
    Return
    End
};

EvtScript TTYD64_flo_19_Script_Exit1 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 4)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "flo_27", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_flo_19_Script_Main_EnterWalk = {
    Set(GameByte(425), 39)
    Call(SetSpriteShading, -1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Set(GameFlag(1985), 1)
    ExecWait(flo_19_EVS_MakeEntities)
    Call(ParentColliderToModel, 12, 86)
    Call(HidePlayerShadow, 1)
    Exec(TTYD64_flo_19_Script_BindExit0)
    Exec(flo_19_EVS_SetupClouds)
    Call(ModifyColliderFlags, 3, 5, 7)
    Call(EnableTexPanning, 17, 1)
    Call(EnableTexPanning, 18, 1)
    Thread
        Set(LVar0, 1)
        Set(LVar1, -120)
        Set(LVar2, 0)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 1)
        Set(LVar6, 0)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(flo_19_EVS_UpdateTexturePan)
    EndThread
    Thread
        Set(LVar0, 2)
        Set(LVar1, -90)
        Set(LVar2, 0)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 1)
        Set(LVar6, 0)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(flo_19_EVS_UpdateTexturePan)
    EndThread
    Call(GetEntryID, LVar0)
    IfNe(LVar0, 3)
        Set(AreaFlag(44), 0)
    EndIf
    Call(GetLoadType, LVar1)
    IfEq(LVar1, 1)
        Exec(EnterSavePoint)
        Exec(flo_19_EVS_BindExitTriggers)
        Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
    Else
        Switch(LVar0)
        CaseEq(0)
            Exec(flo_19_EVS_BindExitTriggers)
        CaseOrEq(1)
        CaseOrEq(4)
            Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
            Set(LVar0, Ref(flo_19_EVS_BindExitTriggers))
            Exec(EnterWalk)
            EndCaseGroup
        CaseEq(2)
            Exec(flo_19_EVS_Scene_BeanstalkGrowing)
            Exec(flo_19_EVS_BindExitTriggers)
        CaseEq(3)
            Exec(flo_19_EVS_Enter_Beanstalk)
            Exec(flo_19_EVS_BindExitTriggers)
        EndSwitch
    EndIf
    ExecWait(flo_19_EVS_SetupMusic)
    IfGe(GameByte(0), 53)
        Call(flo_19_SpawnSunEffect)
    EndIf
    Return
    End
};

EvtScript TTYD64_flo_19_Script_BindExit0 = {
    BindTrigger(flo_19_EVS_Exit_Beanstalk, 128, 12, 1, 0)
    Call(GetEntryID, LVar0)
    IfNe(LVar0, 2)
        Exec(TTYD64_flo_19_Script_InitNewStuff)
    EndIf
    Return
    End
};

EntryList TTYD64_flo_19_EntryList = {
    { 0.0f, 0.0f, 100.0f, 90.0f },
    { 460.0f, 0.0f, 0.0f, 270.0f },
    { 0.0f, -500.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { -426.0f, 0.0f, 0.0f, 90.0f },
};
// clang-format on

void TTYD64_InstallMap_flo_19(void) {
    flo_19_settings.entryList = &TTYD64_flo_19_EntryList;
    flo_19_settings.entryCount = 5;
    Mod_ReplaceScript("TTYD64", &flo_19_EVS_MakeEntities, &TTYD64_flo_19_Script_80240AC0);
    Mod_ReplaceScript("TTYD64", &flo_19_EVS_Main, &TTYD64_flo_19_Script_Main_EnterWalk);
}
