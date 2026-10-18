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

extern EvtScript kmr_20_EVS_Inspect_Records;
extern EvtScript kmr_20_EVS_Luigi_PlayWalkSounds_Intro;
extern EvtScript kmr_20_EVS_OpenAndCloseDoor_Intro;
extern EvtScript kmr_20_EVS_OpenAndCloseDoor_Intro_Impl;
extern EvtScript kmr_20_EVS_Scene_BeginGame;
extern EvtScript kmr_20_EVS_TetherCamToLuigi;

API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableModel);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMapSpecial);
API_CALLABLE(InterpNpcYaw);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(MakeLerp);
API_CALLABLE(NpcFlyTo);
API_CALLABLE(NpcMoveTo);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlaySoundAtNpc);
API_CALLABLE(RotateGroup);
API_CALLABLE(SetCamDistance);
API_CALLABLE(SetCamPitch);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetNpcSpeed);
API_CALLABLE(SetNpcVar);
API_CALLABLE(SetNpcYaw);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(TranslateGroup);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(WaitForCam);
API_CALLABLE(func_802D1270);
API_CALLABLE(kmr_20_SetAmbienceVolumeHalf_Intro);
API_CALLABLE(kmr_20_func_80241C9C_8EDABC);

extern EvtScript TTYD64_kmr_20_Script_8024FD70;
extern s32 TTYD64_kmr_20_DataTable_80252DC0[];
extern EvtScript TTYD64_kmr_20_Script_80252E8C;
extern EvtScript TTYD64_kmr_20_Script_8024FD70_2;

// clang-format off
EvtScript TTYD64_kmr_20_Script_8024FD70 = {
    ExecWait(TTYD64_kmr_20_Script_8024FD70_2)
    Return
    End
};

s32 TTYD64_kmr_20_DataTable_80252DC0[] = {
    -129994066, -129994065, -129994064, -129994063, -129994062, -129994061,
    -129994060, -129994059, -129994058, -129994057, -129994056, -129994055,
    -129994054, -129994053, -129994052, -129994051, -129994050, -129994049,
    -129994047, -129994046, -129994045, -129994044, -129994043, -129994042,
    -129994041, -129994040, -129994039, -129994038, -129994037, -129994036,
    -129994035, -129994034, -129994033, -129994032, -129994031, -129994030,
    -129994029, -129994028, -129994027, -129994026, -129994025, -129994024,
    -129994023, -129994022, -129994021, -129994019, -129994018, -129994017,
    -129994016, -129994015, -129994014, -129994013, -129994012, -129994011,
    -129994010, -129994009, -129994008, -129994007, -129994006, -129994005,
    -129994004, -129994003, -129994002, -129994001, -129994000, -129993999,
    -129993998, -129993997, -129993996, -129993995, -129993994, -129993993,
    -129993992, -129993991, -129993990, -129993989, -129993988, -129993987,
    -129993986, -129993985, -129993984, -129993983, -129993982, -129993981,
    -129993980, -129993979, -129993978, -129993977, -129993976, -129993975,
    0
};

EvtScript TTYD64_kmr_20_Script_80252E8C = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(GetPlayerPos, LVarA, LVarB, LVarC)
    Call(UseSettingsFrom, 0, LVarA, 30, LVarC)
    Call(SetPanTarget, 0, LVarA, 30, LVarC)
    Call(SetCamDistance, 0, Float(320.0))
    Call(SetCamSpeed, 0, Float(4.2001953125))
    Call(PanToTarget, 0, 0, 1)
    Call(WaitForCam, 0, Float(1.0))
    Call(TTYD64_kmr_20_ShowGameRecords)
    Call(SetCamDistance, 0, Float(400.0))
    Call(SetCamSpeed, 0, Float(4.2001953125))
    Call(PanToTarget, 0, 0, 1)
    Call(WaitForCam, 0, Float(1.0))
    Call(PanToTarget, 0, 0, 0)
    Call(DisablePlayerInput, 0)
    Call(DisablePlayerPhysics, 0)
    Return
    End
};

EvtScript TTYD64_kmr_20_Script_8024FD70_2 = {
    Call(DisablePlayerInput, 1)
    Thread
        Wait(5)
        Call(SetMusic, 0, 62, 0, 8)
    EndThread
    Call(InterpPlayerYaw, 90, 0)
    Call(SetPlayerPos, -50, 30, -80)
    Call(SetNpcPos, 1, 220, 30, -80)
    Call(SetNpcPos, 0, 720, 220, -150)
    Call(SetNpcYaw, 0, 270)
    Call(EnableGroup, 28, 0)
    Call(EnableGroup, 107, 1)
    Call(UseSettingsFrom, 0, 550, 0, 20)
    Call(SetPanTarget, 0, 550, 0, 20)
    Call(SetCamDistance, 0, 550)
    Call(SetCamPitch, 0, Float(15.0), Float(-14.0))
    Call(SetCamSpeed, 0, Float(90.0))
    Call(PanToTarget, 0, 0, 1)
    Wait(1)
    Call(SetCamDistance, 0, 450)
    Call(SetCamSpeed, 0, Float(0.7001953125))
    Call(PanToTarget, 0, 0, 1)
    Thread
        Wait(10)
        Call(MakeLerp, 0, 70, 60, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, 90, LVar0, 0, 0)
            SetF(LVar2, 0)
            SubF(LVar2, LVar0)
            Call(TranslateGroup, 92, LVar2, 0, 0)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndThread
    Thread
        Wait(30)
        Call(MakeLerp, 0, 50, 40, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, 94, LVar0, 0, 0)
            SetF(LVar2, 0)
            SubF(LVar2, LVar0)
            Call(TranslateGroup, 96, LVar2, 0, 0)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndThread
    Thread
        Wait(50)
        Call(MakeLerp, 0, 50, 40, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, 98, LVar0, 0, 0)
            Call(TranslateGroup, 106, LVar0, 0, 0)
            SetF(LVar2, 0)
            SubF(LVar2, LVar0)
            Call(TranslateGroup, 100, LVar2, 0, 0)
            Call(TranslateGroup, 102, LVar2, 0, 0)
            Call(TranslateGroup, 104, LVar2, 0, 0)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndThread
    Wait(120)
    Call(NpcFlyTo, 0, 430, 20, -165, 60, -10, 0)
    Call(InterpNpcYaw, 0, 45, 10)
    Wait(20)
    Call(PlaySoundAtNpc, 0, 224, 0)
    Thread
        Call(TranslateModel, 34, 2, 0, 0)
        Call(TranslateModel, 35, 2, 0, 0)
        Call(TranslateModel, 36, 2, 0, 0)
        Wait(1)
        Call(TranslateModel, 34, -3, 0, 0)
        Call(TranslateModel, 35, -3, 0, 0)
        Call(TranslateModel, 36, -3, 0, 0)
        Wait(1)
        Call(TranslateModel, 34, 2, 0, 0)
        Call(TranslateModel, 35, 2, 0, 0)
        Call(TranslateModel, 36, 2, 0, 0)
        Wait(1)
        Call(TranslateModel, 34, -3, 0, 0)
        Call(TranslateModel, 35, -3, 0, 0)
        Call(TranslateModel, 36, -3, 0, 0)
        Wait(1)
        Call(TranslateModel, 34, 0, 0, 0)
        Call(TranslateModel, 35, 0, 0, 0)
        Call(TranslateModel, 36, 0, 0, 0)
    EndThread
    Wait(35)
    Call(InterpNpcYaw, 0, 220, 5)
    Wait(10)
    Call(SpeakToPlayer, 0, 0x40006, 0x40001, 5, 30)
    Wait(10)
    Call(NpcFlyTo, 0, 360, 260, 60, 60, -10, 0)
    Wait(30)
    Exec(kmr_20_EVS_OpenAndCloseDoor_Intro)
    Wait(10)
    Call(SetNpcAnimation, 1, 0x82000A)
    ExecGetTID(kmr_20_EVS_Luigi_PlayWalkSounds_Intro, LVarA)
    Call(SetNpcSpeed, 1, Float(4.0))
    Call(NpcMoveTo, 1, 450, -80, 0)
    Call(NpcMoveTo, 1, 430, -165, 0)
    Call(SetNpcAnimation, 1, 0x820004)
    KillThread(LVarA)
    Wait(20)
    Call(PlaySoundAtNpc, 1, 224, 0)
    Thread
        Call(TranslateModel, 34, 1, 0, 0)
        Call(TranslateModel, 35, 1, 0, 0)
        Call(TranslateModel, 36, 1, 0, 0)
        Wait(1)
        Call(TranslateModel, 34, -2, 0, 0)
        Call(TranslateModel, 35, -2, 0, 0)
        Call(TranslateModel, 36, -2, 0, 0)
        Wait(1)
        Call(TranslateModel, 34, 1, 0, 0)
        Call(TranslateModel, 35, 1, 0, 0)
        Call(TranslateModel, 36, 1, 0, 0)
        Wait(1)
        Call(TranslateModel, 34, -2, 0, 0)
        Call(TranslateModel, 35, -2, 0, 0)
        Call(TranslateModel, 36, -2, 0, 0)
        Wait(1)
        Call(TranslateModel, 34, 0, 0, 0)
        Call(TranslateModel, 35, 0, 0, 0)
        Call(TranslateModel, 36, 0, 0, 0)
    EndThread
    Wait(2)
    Call(SetNpcAnimation, 1, 0x820005)
    Wait(40)
    Call(InterpNpcYaw, 1, 270, 5)
    Call(SetNpcAnimation, 1, 0x82000B)
    ExecGetTID(kmr_20_EVS_Luigi_PlayWalkSounds_Intro, LVarA)
    Call(NpcMoveTo, 1, 450, -80, 0)
    Call(NpcMoveTo, 1, 290, -70, 0)
    KillThread(LVarA)
    Call(EnableGroup, 145, 1)
    Call(EnableGroup, 165, 1)
    Call(EnableGroup, 178, 1)
    Call(EnableModel, 268, 1)
    Call(kmr_20_func_80241C9C_8EDABC)
    Call(RotateGroup, 117, 90, 1, 0, 0)
    Call(RotateGroup, 114, 90, -1, 0, 0)
    Call(EnableGroup, 117, 0)
    Call(EnableGroup, 114, 0)
    Call(UseSettingsFrom, 0, 250, 30, -80)
    Call(SetPanTarget, 0, 250, 30, -80)
    Call(SetCamSpeed, 0, Float(90.0))
    Call(PanToTarget, 0, 0, 1)
    Call(kmr_20_SetAmbienceVolumeHalf_Intro)
    Exec(kmr_20_EVS_OpenAndCloseDoor_Intro_Impl)
    Wait(10)
    Call(SetNpcAnimation, 1, 0x820009)
    ExecGetTID(kmr_20_EVS_Luigi_PlayWalkSounds_Intro, LVarA)
    Call(SetNpcSpeed, 1, Float(2.0))
    Call(NpcMoveTo, 1, 240, -80, 0)
    Call(SetNpcAnimation, 1, 0x820005)
    KillThread(LVarA)
    Call(SpeakToPlayer, 1, 0x820015, 0x820005, 0, 31)
    Wait(10)
    Exec(kmr_20_EVS_TetherCamToLuigi)
    Thread
        Call(SetNpcAnimation, 1, 0x820009)
        ExecGetTID(kmr_20_EVS_Luigi_PlayWalkSounds_Intro, LVarA)
        Call(NpcMoveTo, 1, 230, -130, 0)
        Call(NpcMoveTo, 1, 110, -110, 0)
        Call(SetNpcAnimation, 1, 0x820005)
        KillThread(LVarA)
        Call(SetNpcVar, 1, 0, 0)
    EndThread
    Wait(20)
    Call(func_802D1270, 70, -80, Float(2.0))
    Call(func_802D1270, 70, -110, Float(2.0))
    Wait(10)
    Call(SpeakToPlayer, 1, 0x820015, 0x820005, 0, 32)
    Call(SetNpcAnimation, 1, 0x820018)
    Wait(20)
    Call(SetNpcAnimation, 1, 0x820006)
    Call(SpeakToPlayer, 1, 0x820016, 0x820006, 0, 33)
    Call(SetNpcAnimation, 1, 0x820019)
    Wait(10)
    Call(SetMusic, 0, 115, 0, 8)
    Wait(5)
    Call(ClearAmbientSounds, 250)
    Call(GotoMapSpecial, (Bytecode) "osr_00", 3, 7)
    Wait(15)
    Call(ClearAmbientSounds, 250)
    Wait(100)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_kmr_20(void) {
    Mod_ReplaceScript("TTYD64", &kmr_20_EVS_Scene_BeginGame, &TTYD64_kmr_20_Script_8024FD70);
    Mod_ReplaceScript("TTYD64", &kmr_20_EVS_Inspect_Records, &TTYD64_kmr_20_Script_80252E8C);
}
