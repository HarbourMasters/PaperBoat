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

extern NpcGroupList sbk_02_DefaultNPCs;
extern EvtScript sbk_02_EVS_BindExitTriggers;
extern EvtScript sbk_02_EVS_Doors_Open;
extern EvtScript sbk_02_EVS_EnterMap;
extern EvtScript sbk_02_EVS_ExitWalk_isk_01_0;
extern EvtScript sbk_02_EVS_ExitWalk_sbk_01_1;
extern EvtScript sbk_02_EVS_ExitWalk_sbk_03_0;
extern EvtScript sbk_02_EVS_ExitWalk_sbk_12_2;
extern EvtScript sbk_02_EVS_LightRays_Vanish;
extern EvtScript sbk_02_EVS_Main;
extern EvtScript sbk_02_EVS_MakeEntities;
extern EvtScript sbk_02_EVS_OnInteract_Pedestal;
extern EvtScript sbk_02_EVS_Ruins_FinishRising;
extern EvtScript sbk_02_EVS_SandRingClone_Vanish;
extern EvtScript sbk_02_EVS_SandRing_Vanish;
extern EvtScript sbk_02_EVS_SetupMusic;
extern EvtScript sbk_02_EVS_SetupRuins;
extern EvtScript sbk_02_EVS_Steps_FinishRising;
extern EvtScript sbk_02_EVS_Steps_Unfold;
extern EvtScript sbk_02_EVS_TexPan_SandRing;
extern s32 sbk_02_ModelList_Solid[];
extern s32 sbk_02_ModelList_Translucent[];
extern s32 sbk_02_PedestalKeyList[];
extern MapSettings sbk_02_settings;

API_CALLABLE(CloneModel);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePulseStone);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableModel);
API_CALLABLE(FacePlayerTowardPoint);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamDistance);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamPitch);
API_CALLABLE(SetCamPosA);
API_CALLABLE(SetCamPosB);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetMusic);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(ShakeCam);
API_CALLABLE(UseExitHeading);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(WaitForCam);
API_CALLABLE(func_802CF56C);
API_CALLABLE(sbk_02_InterpWorldEnvColor);
API_CALLABLE(sbk_02_SetModelTintMode);

extern EvtScript TTYD64_sbk_02_Script_Exit5;
extern EvtScript TTYD64_sbk_02_Script_Main;
extern EvtScript TTYD64_sbk_02_Script_80243B38_2;
extern EvtScript TTYD64_sbk_02_Script_80240EB0;
extern EvtScript TTYD64_sbk_02_Script_80243A00;
extern EntryList TTYD64_sbk_02_EntryList;

// clang-format off
EvtScript TTYD64_sbk_02_Script_Exit5 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 8)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "isk_20", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_sbk_02_Script_Main = {
    Set(GameByte(425), 10)
    Call(SetSpriteShading, -1)
    IfEq(GameByte(0), -63)
        Call(DisablePulseStone, 0)
    EndIf
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeNpcs, 0, Ref(sbk_02_DefaultNPCs))
    ExecWait(sbk_02_EVS_MakeEntities)
    IfLt(GameByte(0), -62)
        Call(PlayEffect_impl, 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Set(MapVar(0), LVarF)
    EndIf
    IfEq(GameByte(0), -54)
        Call(SetMusic, 0, 120, 1, 8)
    Else
        Exec(sbk_02_EVS_SetupMusic)
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseOrEq(6)
    CaseOrEq(7)
        EndCaseGroup
    CaseDefault
        ExecWait(sbk_02_EVS_SetupRuins)
    EndSwitch
    Exec(sbk_02_EVS_EnterMap)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(5)
        Wait(65)
    CaseOrEq(6)
    CaseOrEq(7)
        Exec(TTYD64_sbk_02_Script_80243B38_2)
        Wait(3)
        EndCaseGroup
    CaseDefault
        Wait(1)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_sbk_02_Script_80243B38_2 = {
    Call(PlaySound, 92)
    Call(DisablePlayerInput, 1)
    Call(func_802CF56C, 1)
    Call(FacePlayerTowardPoint, 0, 0, 0)
    Call(ModifyColliderFlags, 0, 13, 0x7FFFFE00)
    Call(EnableModel, 130, 0)
    Call(EnableGroup, 22, 0)
    Thread
        Call(ShakeCam, 0, 0, 400, Float(0.2001953125))
    EndThread
    Call(UseSettingsFrom, 0, 0, 0, 0)
    Call(SetPanTarget, 0, 210, 0, 137)
    Call(SetCamPosA, 0, Float(150.0), Float(500.0))
    Call(SetCamPosB, 0, Float(-450.0), Float(-500.0))
    Call(SetCamPitch, 0, Float(8.0), Float(-9.0))
    Call(SetCamDistance, 0, Float(500.0))
    Call(SetCamSpeed, 0, Float(90.0))
    Call(PanToTarget, 0, 0, 1)
    Call(sbk_02_SetModelTintMode, 2, 0, 3)
    Call(sbk_02_SetModelTintMode, 1, -1, 3)
    Call(sbk_02_SetModelTintMode, 1, (Bytecode) sbk_02_ModelList_Solid, 0)
    Call(sbk_02_SetModelTintMode, 0, (Bytecode) sbk_02_ModelList_Translucent, 0)
    Call(sbk_02_InterpWorldEnvColor, 44, 32, 177, 0, 0, 0, 0)
    Exec(sbk_02_EVS_Ruins_FinishRising)
    Exec(sbk_02_EVS_Steps_FinishRising)
    Call(CloneModel, 128, 10000)
    Exec(sbk_02_EVS_TexPan_SandRing)
    Exec(sbk_02_EVS_SandRing_Vanish)
    Exec(sbk_02_EVS_SandRingClone_Vanish)
    Wait(20)
    Exec(sbk_02_EVS_LightRays_Vanish)
    Call(WaitForCam, 0, Float(1.0))
    Call(UseSettingsFrom, 0, 0, 0, 0)
    Call(SetPanTarget, 0, 0, 0, 0)
    Call(SetCamPitch, 0, Float(4.0), Float(-6.5))
    Call(SetCamDistance, 0, Float(790.0))
    Call(SetCamSpeed, 0, Float(0.2001953125))
    Call(PanToTarget, 0, 0, 1)
    Wait(100)
    Exec(sbk_02_EVS_Doors_Open)
    Wait(100)
    ExecWait(sbk_02_EVS_Steps_Unfold)
    Call(ModifyColliderFlags, 1, 22, 0x7FFFFE00)
    Call(ModifyColliderFlags, 1, 27, 0x7FFFFE00)
    Call(WaitForCam, 0, Float(1.0))
    Wait(60)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
    Call(SetCamSpeed, 0, Float(90.0))
    Call(WaitForCam, 0, Float(1.0))
    Call(PanToTarget, 0, 0, 0)
    Call(func_802CF56C, 0)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_sbk_02_Script_80240EB0 = {
    BindTrigger(sbk_02_EVS_ExitWalk_sbk_01_1, 0x80000, 3, 1, 0)
    BindTrigger(sbk_02_EVS_ExitWalk_sbk_03_0, 0x80000, 7, 1, 0)
    BindTrigger(sbk_02_EVS_ExitWalk_sbk_12_2, 0x80000, 5, 1, 0)
    BindTrigger(sbk_02_EVS_ExitWalk_isk_01_0, 0x80000, 9, 1, 0)
    BindTrigger(TTYD64_sbk_02_Script_Exit5, 0x80000, 26, 1, 0)
    Return
    End
};

EvtScript TTYD64_sbk_02_Script_80243A00 = {
    Switch(GameByte(0))
    CaseLt(-63)
        Call(EnableGroup, 22, 0)
        Call(ModifyColliderFlags, 0, 22, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 27, 0x7FFFFE00)
    CaseLt(-62)
        Call(EnableGroup, 22, 0)
        Call(ModifyColliderFlags, 0, 22, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 27, 0x7FFFFE00)
        BindPadlock(sbk_02_EVS_OnInteract_Pedestal, 256, 13, (Bytecode) sbk_02_PedestalKeyList, 0, 1)
    CaseDefault
        Call(EnableModel, 130, 0)
        Call(ModifyColliderFlags, 0, 15, 0x7FFFFE00)
    EndSwitch
    Call(EnableGroup, 114, 0)
    Call(EnableGroup, 125, 0)
    Call(EnableModel, 126, 0)
    Call(EnableModel, 128, 0)
    Return
    End
};

EntryList TTYD64_sbk_02_EntryList = {
    { -475.0f, 0.0f, 0.0f, 90.0f },
    { 475.0f, 0.0f, 0.0f, 270.0f },
    { 0.0f, 0.0f, -475.0f, 180.0f },
    { 0.0f, 0.0f, 475.0f, 0.0f },
    { 0.0f, 80.0f, -195.0f, 180.0f },
    { 20.0f, 0.0f, 110.0f, 270.0f },
    { -80.0f, 0.0f, 80.0f, 180.0f },
    { 80.0f, 0.0f, 80.0f, 90.0f },
    { 181.0f, 80.0f, -357.0f, -180.0f },
};
// clang-format on

void TTYD64_InstallMap_sbk_02(void) {
    sbk_02_settings.entryList = &TTYD64_sbk_02_EntryList;
    sbk_02_settings.entryCount = 9;
    Mod_ReplaceScript("TTYD64", &sbk_02_EVS_Main, &TTYD64_sbk_02_Script_Main);
    Mod_ReplaceScript("TTYD64", &sbk_02_EVS_BindExitTriggers, &TTYD64_sbk_02_Script_80240EB0);
    Mod_ReplaceScript("TTYD64", &sbk_02_EVS_SetupRuins, &TTYD64_sbk_02_Script_80243A00);
}
