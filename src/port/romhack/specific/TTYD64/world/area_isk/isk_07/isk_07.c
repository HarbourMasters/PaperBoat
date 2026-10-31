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

extern NpcGroupList isk_07_DefaultNPCs;
extern EvtScript isk_07_EVS_ExitWalk_isk_04_1;
extern EvtScript isk_07_EVS_ExitWalk_isk_08_2;
extern EvtScript isk_07_EVS_Main;
extern EvtScript isk_07_EVS_MakeEntities;
extern EvtScript isk_07_EVS_OnTouch_StairSwitch;
extern EvtScript isk_07_EVS_OpenSarcophagus1;
extern EvtScript isk_07_EVS_OpenSarcophagus2;
extern EvtScript isk_07_EVS_OpenSarcophagus3;
extern EvtScript isk_07_EVS_OpenSarcophagusAnim;
extern EvtScript isk_07_EVS_SetupLock;
extern EvtScript isk_07_EVS_SetupSarcophagi;
extern EvtScript isk_07_EVS_SetupStairs;
extern EvtScript isk_07_EVS_SetupSwitch;
extern EvtScript isk_07_EVS_ShutEntryDoor;
extern MapSettings isk_07_settings;

API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnableGroup);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PanToTarget);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlaySound);
API_CALLABLE(RotateModel);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcYaw);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(ShakeCam);
API_CALLABLE(TranslateGroup);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UpdatePlayerImgFX);
API_CALLABLE(UseExitHeading);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(WaitForCam);

extern EntryList TTYD64_isk_07_EntryList;
extern EvtScript TTYD64_isk_07_Script_Main_EnterWalk;
extern EvtScript TTYD64_isk_07_Script_80242190;
extern EvtScript TTYD64_isk_07_Script_802428E8;
extern EvtScript TTYD64_isk_07_Script_80242964;
extern EvtScript TTYD64_isk_07_Script_OpenSecret;
extern EvtScript TTYD64_isk_07_Script_InitNewStuff;
extern EvtScript TTYD64_isk_07_Script_BindExits;
extern EvtScript TTYD64_isk_07_Script_Exit2;
extern EvtScript TTYD64_isk_07_Script_80241F50;

// clang-format off
EntryList TTYD64_isk_07_EntryList = {
    { -283.0f, -390.0f, 530.0f, 110.0f },
    { 560.0f, -340.0f, 217.0f, 210.0f },
    { 45.0f, -390.0f, 530.0f, -180.0f },
};

EvtScript TTYD64_isk_07_Script_Main_EnterWalk = {
    Set(GameByte(425), 11)
    Call(SetSpriteShading, 0x20004)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamLeadPlayer, 0, 0)
    Call(SetCamEnabled, 0, 1)
    IfEq(GameFlag(876), 0)
        Call(MakeNpcs, 1, Ref(isk_07_DefaultNPCs))
    EndIf
    ExecWait(isk_07_EVS_MakeEntities)
    Exec(isk_07_EVS_SetupLock)
    Exec(isk_07_EVS_SetupStairs)
    Exec(isk_07_EVS_SetupSwitch)
    Exec(isk_07_EVS_SetupSarcophagi)
    Switch(GameByte(0))
    CaseLt(-57)
        Call(SetMusic, 0, 24, 0, 8)
    CaseLt(-56)
        Call(SetMusic, 0, 25, 0, 8)
    CaseGe(-56)
        Call(SetMusic, 0, 24, 0, 8)
    EndSwitch
    Set(LVar0, Ref(TTYD64_isk_07_Script_BindExits))
    Exec(EnterWalk)
    Return
    End
};

EvtScript TTYD64_isk_07_Script_80242190 = {
    IfEq(GameFlag(886), 0)
        Set(AreaFlag(10), 0)
        Set(AreaFlag(11), 0)
        Set(AreaFlag(12), 0)
        Call(ModifyColliderFlags, 0, 47, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 48, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 49, 0x7FFFFE00)
        Label(10)
        IfEq(GameFlag(886), 0)
            Wait(1)
            Goto(10)
        EndIf
        Call(PlaySound, 10)
        Call(DisablePlayerInput, 1)
        Call(ShakeCam, 0, 0, 30, Float(1.0))
        Call(SetNpcYaw, 0, 105)
        Call(SetNpcFlagBits, 0, 2, 0)
        Call(SetNpcFlagBits, 1, 2, 0)
        Call(SetNpcFlagBits, 2, 2, 0)
        Thread
            Wait(12)
            Call(InterpPlayerYaw, 109, 0)
            Wait(3)
            Call(UpdatePlayerImgFX, 0x10002, 5, 0, 1, 1, 0)
            Call(SetPlayerAnimation, 0x8000A)
            Wait(20)
            Call(UpdatePlayerImgFX, 0x10002, 0, 0, 0, 0, 0)
            Call(SetPlayerAnimation, 0x10002)
        EndThread
        Call(SetCamSpeed, 0, Float(2.0))
        Call(UseSettingsFrom, 0, -151, -390, 576)
        Call(SetPanTarget, 0, -151, -390, 576)
        Wait(1)
        Call(PanToTarget, 0, 0, 1)
        Call(WaitForCam, 0, Float(1.0))
        Exec(isk_07_EVS_OpenSarcophagus1)
        Wait(15)
        Call(SetPanTarget, 0, 51, -390, 589)
        Call(WaitForCam, 0, Float(1.0))
        Exec(isk_07_EVS_OpenSarcophagus2)
        Wait(15)
        Call(SetPanTarget, 0, 239, -390, 515)
        Call(WaitForCam, 0, Float(1.0))
        Exec(isk_07_EVS_OpenSarcophagus3)
        Wait(15)
        Call(SetPanTarget, 0, 517, -390, 292)
        Call(WaitForCam, 0, Float(1.0))
        Exec(isk_07_EVS_ShutEntryDoor)
        Wait(30)
        Call(SetCamSpeed, 0, Float(90.0))
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
        Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
        Wait(1)
        Call(PanToTarget, 0, 0, 0)
        Set(AreaFlag(13), 1)
        Call(DisablePlayerInput, 0)
    Else
        Set(AreaFlag(10), 1)
        Set(AreaFlag(11), 1)
        Set(AreaFlag(12), 1)
        Call(TranslateModel, 107, 38, 0, 13)
        Call(RotateModel, 107, 35, 0, 1, 0)
        Call(TranslateModel, 117, 38, 0, 13)
        Call(RotateModel, 117, 35, 0, 1, 0)
        Call(TranslateModel, 126, 38, 0, 13)
        Call(RotateModel, 126, 35, 0, 1, 0)
        Wait(5)
        Set(AreaFlag(10), 0)
        Set(AreaFlag(11), 0)
        Set(AreaFlag(12), 0)
        Call(ModifyColliderFlags, 0, 43, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 44, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 45, 0x7FFFFE00)
        Set(AreaFlag(13), 1)
    EndIf
    Return
    End
};

EvtScript TTYD64_isk_07_Script_802428E8 = {
    Set(AreaFlag(11), 1)
    Set(LVar3, 117)
    ExecWait(isk_07_EVS_OpenSarcophagusAnim)
    Set(AreaFlag(11), 0)
    Call(ModifyColliderFlags, 0, 44, 0x7FFFFE00)
    Call(ModifyColliderFlags, 1, 48, 0x7FFFFE00)
    Return
    End
};

EvtScript TTYD64_isk_07_Script_80242964 = {
    Set(AreaFlag(12), 1)
    Set(LVar3, 126)
    ExecWait(isk_07_EVS_OpenSarcophagusAnim)
    Set(AreaFlag(12), 0)
    Call(ModifyColliderFlags, 0, 45, 0x7FFFFE00)
    Call(ModifyColliderFlags, 1, 49, 0x7FFFFE00)
    Return
    End
};

EvtScript TTYD64_isk_07_Script_OpenSecret = {
    SetGroup(0)
    SuspendGroup(2)
    Call(DisablePlayerInput, 1)
    Call(PlaySound, 465)
    Call(MakeLerp, 0, -16, 15, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, 132, 0, 0, LVar0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(PlaySound, 614)
    Call(MakeLerp, 0, 52, 15, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, 132, LVar0, 0, -16)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(EnableGroup, 132, 0)
    Call(ModifyColliderFlags, 0, 54, 0x7FFFFE00)
    Call(PlaySound, 10)
    Wait(15)
    Call(DisablePlayerInput, 0)
    Set(GameFlag(5004), 1)
    ResumeGroup(2)
    Return
    End
};

EvtScript TTYD64_isk_07_Script_InitNewStuff = {
    IfEq(GameFlag(5004), 1)
        Call(EnableGroup, 132, 0)
        Call(ModifyColliderFlags, 0, 54, 0x7FFFFE00)
    Else
        BindTrigger(TTYD64_isk_07_Script_OpenSecret, 256, 54, 1, 0)
    EndIf
    Return
    End
};

EvtScript TTYD64_isk_07_Script_BindExits = {
    BindTrigger(isk_07_EVS_ExitWalk_isk_08_2, 0x80000, 0, 1, 0)
    BindTrigger(isk_07_EVS_ExitWalk_isk_04_1, 0x80000, 4, 1, 0)
    BindTrigger(TTYD64_isk_07_Script_Exit2, 0x80000, 57, 1, 0)
    Return
    End
};

EvtScript TTYD64_isk_07_Script_Exit2 = {
    SetGroup(27)
    Call(UseExitHeading, 40, 2)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "isk_21", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_isk_07_Script_80241F50 = {
    Call(ParentColliderToModel, 37, 83)
    BindTrigger(isk_07_EVS_OnTouch_StairSwitch, 128, 37, 1, 0)
    Exec(TTYD64_isk_07_Script_InitNewStuff)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_isk_07(void) {
    isk_07_settings.entryList = &TTYD64_isk_07_EntryList;
    isk_07_settings.entryCount = 3;
    Mod_ReplaceScript("TTYD64", &isk_07_EVS_Main, &TTYD64_isk_07_Script_Main_EnterWalk);
    Mod_ReplaceScript("TTYD64", &isk_07_EVS_SetupSarcophagi, &TTYD64_isk_07_Script_80242190);
    Mod_ReplaceScript("TTYD64", &isk_07_EVS_OpenSarcophagus2, &TTYD64_isk_07_Script_802428E8);
    Mod_ReplaceScript("TTYD64", &isk_07_EVS_OpenSarcophagus3, &TTYD64_isk_07_Script_80242964);
    Mod_ReplaceScript("TTYD64", &isk_07_EVS_SetupSwitch, &TTYD64_isk_07_Script_80241F50);
}
