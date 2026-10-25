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

extern EvtScript obk_09_EVS_EnterMap;
extern EvtScript obk_09_EVS_PlayNewPartnerSong;
extern EvtScript obk_09_EVS_ResetMusic;

API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(InterpNpcYaw);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(MakeLerp);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(NpcJump0);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlaySoundAtNpc);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(SetCamDistance);
API_CALLABLE(SetCamPitch);
API_CALLABLE(SetCamPosA);
API_CALLABLE(SetCamPosB);
API_CALLABLE(SetCamPosC);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetCamType);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcImgFXParams);
API_CALLABLE(SetNpcJumpscale);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetNpcYaw);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowMessageAtScreenPos);
API_CALLABLE(SpeakToNpc);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(StopSound);
API_CALLABLE(TranslateGroup);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseDoorSounds);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(WaitForCam);
API_CALLABLE(obk_09_ChangeNpcToPartner);
API_CALLABLE(obk_09_LoadPartyImage);

extern EvtScript TTYD64_obk_09_Script_EnterDoubleDoor_80240580;
extern EvtScript TTYD64_obk_09_Script_80240990_New;

// clang-format off
EvtScript TTYD64_obk_09_Script_EnterDoubleDoor_80240580 = {
    Call(DisablePlayerInput, 1)
    Call(EnableGroup, 41, 0)
    Call(ModifyColliderFlags, 0, 37, 0x7FFFFE00)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Call(UseDoorSounds, 3)
        Set(LVar2, 57)
        Set(LVar3, 55)
        ExecWait(EnterDoubleDoor)
    CaseEq(1)
        Call(UseDoorSounds, 3)
        Set(LVar2, 61)
        Set(LVar3, 59)
        ExecWait(EnterDoubleDoor)
    EndSwitch
    Exec(TTYD64_obk_09_Script_80240990_New)
    Wait(1)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_obk_09_Script_80240990_New = {
    IfGe(GameByte(0), -36)
        Return
    EndIf
    Set(GameByte(0), -36)
    Call(DisablePlayerInput, 1)
    Call(SetMusic, 0, 28, 0, 8)
    Thread
        Wait(10)
        Call(SetPlayerPos, -180, 0, 344)
        Call(SetNpcPos, -4, -180, 20, 344)
        Call(PlayerMoveTo, 0, 190, 60)
        Call(SetPlayerAnimation, 0x8001E)
    EndThread
    Wait(10)
    Call(SetCamType, 0, 4, 1)
    Call(SetCamSpeed, 0, Float(90.0))
    Call(SetCamPitch, 0, Float(5.0), Float(-9.0))
    Call(SetCamDistance, 0, 500)
    Call(SetCamPosA, 0, 200, 280)
    Call(SetCamPosB, 0, 0, 110)
    Call(SetCamPosC, 0, 0, 0)
    Call(PanToTarget, 0, 0, 1)
    Wait(48)
    Call(ShowMessageAtScreenPos, 0xE0042, 160, 40)
    KillThread(LVarA)
    Call(InterpPlayerYaw, 40, 0)
    Call(SetPlayerAnimation, 0x1010002)
    Call(SetCamSpeed, 0, Float(2.0))
    Call(SetCamPitch, 0, Float(4.0), Float(-9.0))
    Call(SetCamDistance, 0, 400)
    Call(SetCamPosA, 0, 200, 300)
    Call(SetCamPosB, 0, -20, 10)
    Call(SetCamPosC, 0, 0, 60)
    Call(PanToTarget, 0, 0, 1)
    Call(WaitForCam, 0, Float(1.0))
    Wait(20)
    Call(SetNpcPos, 0, -10, 80, -35)
    Call(SetNpcPos, 1, 30, 70, -75)
    Call(SetNpcYaw, 0, 270)
    Call(SetNpcYaw, 1, 270)
    Call(PlaySoundAtNpc, 0, 193, 0)
    SetF(LVar0, Float(0.0))
    Loop(20)
        AddF(LVar0, Float(12.0))
        Call(SetNpcImgFXParams, 0, 7, LVar0, 0, 0, 0)
        Call(SetNpcImgFXParams, 1, 7, LVar0, 0, 0, 0)
        Wait(1)
    EndLoop
    Wait(40)
    Call(UseSettingsFrom, 0, 0, 50, -70)
    Call(SetCamDistance, 0, Float(300.0))
    Call(SetCamPitch, 0, Float(3.0), Float(-10.0))
    Call(SetCamSpeed, 0, Float(90.0))
    Call(SetPanTarget, 0, 0, 50, -70)
    Wait(20)
    Call(SpeakToPlayer, 0, 0x50004, 0x50001, 0, 0xE0043)
    Call(SpeakToPlayer, 1, 0xBF0004, 0xBF0001, 0, 0xE0044)
    Wait(10)
    Call(SpeakToPlayer, 0, 0x50004, 0x50001, 0, 0xE0045)
    Wait(20)
    Call(InterpNpcYaw, 0, 225, 0)
    Call(SpeakToPlayer, 1, 0xBF0004, 0xBF0001, 0, 0xE0046)
    Call(SetCamSpeed, 0, Float(2.0))
    Call(SetPanTarget, 0, 20, 50, -70)
    Wait(10)
    Call(SpeakToPlayer, 1, 0xBF0004, 0xBF0001, 0, 0xE0047)
    Call(SetCamType, 0, 4, 1)
    Call(SetCamSpeed, 0, Float(90.0))
    Call(SetCamPitch, 0, Float(15.5), Float(-9.5))
    Call(SetCamDistance, 0, 550)
    Call(SetCamPosA, 0, 200, 300)
    Call(SetCamPosB, 0, 0, 80)
    Call(SetCamPosC, 0, 0, 0)
    Call(PanToTarget, 0, 0, 1)
    Wait(10)
    Call(SpeakToPlayer, 1, 0xBF0007, 0xBF0008, 0, 0xE0048)
    Call(UseSettingsFrom, 0, 0, 50, -70)
    Call(SetCamDistance, 0, 300)
    Call(SetCamPitch, 0, Float(3.0), Float(-10.0))
    Call(SetCamSpeed, 0, Float(90.0))
    Call(SetPanTarget, 0, 20, 50, -70)
    Wait(10)
    Call(SpeakToPlayer, 1, 0xBF0004, 0xBF0001, 0, 0xE0049)
    Call(SetCamSpeed, 0, Float(2.0))
    Call(SetPanTarget, 0, 0, 50, -70)
    Wait(10)
    Call(InterpNpcYaw, 0, 270, 0)
    Wait(10)
    Call(SpeakToPlayer, 0, 0x50004, 0x50001, 5, 0xE004A)
    Call(InterpNpcYaw, 0, 90, 0)
    Call(SpeakToPlayer, 0, 0x50004, 0x50001, 5, 0xE004B)
    Call(SetCamDistance, 0, 550)
    Call(SetCamPitch, 0, Float(3.0), Float(-12.0))
    Call(PanToTarget, 0, 0, 1)
    Wait(10)
    Call(EnableGroup, 41, 1)
    Call(SetNpcPos, 2, 1, 650, 80)
    Call(EnableNpcShadow, 2, 0)
    Call(PlaySoundAtNpc, 2, 0x8000000F, 0)
    Call(MakeLerp, -280, -480, 100, 1)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, 41, 0, LVar0, 0)
        Add(LVar0, 650)
        Call(SetNpcPos, 2, 1, LVar0, 80)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(StopSound, 0x8000000F)
    Call(PlaySoundAtNpc, 2, 155, 0)
    Call(ShakeCam, 0, 0, 15, Float(0.2001953125))
    Wait(40)
    Call(SetCamType, 0, 4, 1)
    Call(SetCamSpeed, 0, Float(90.0))
    Call(SetCamPitch, 0, Float(30.0), Float(-18.0))
    Call(SetCamDistance, 0, 500)
    Call(SetCamPosA, 0, 0, 350)
    Call(SetCamPosB, 0, 0, 0)
    Call(SetCamPosC, 0, 0, 0)
    Call(PanToTarget, 0, 0, 1)
    Wait(20)
    Call(SpeakToPlayer, 2, 0x140005, 0x140009, 0, 0xE004C)
    Call(UseSettingsFrom, 0, 0, 50, -70)
    Call(SetCamDistance, 0, 300)
    Call(SetCamPitch, 0, Float(3.0), Float(-10.0))
    Call(SetCamSpeed, 0, Float(90.0))
    Call(SetPanTarget, 0, 0, 50, -70)
    Wait(20)
    Thread
        Wait(30)
        Call(SetNpcPos, 2, 1, 620, 80)
        Call(EnableNpcShadow, 2, 0)
        Call(PlaySoundAtNpc, 2, 0x8000000F, 0)
        Call(MakeLerp, -480, -280, 100, 1)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, 41, 0, LVar0, 0)
            Add(LVar0, 640)
            Call(SetNpcPos, 2, 1, LVar0, 80)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(StopSound, 0x8000000F)
        Call(EnableGroup, 41, 0)
    EndThread
    Call(SpeakToPlayer, 0, 0x50004, 0x50001, 0, 0xE004D)
    Call(SpeakToPlayer, 1, 0xBF0006, 0xBF0005, 0, 0xE004E)
    Call(SpeakToNpc, 0, 0x50004, 0x50001, 0, 1, 0xE004F)
    Call(SpeakToPlayer, 1, 0xBF000B, 0xBF0008, 0, 0xE0050)
    Call(SpeakToPlayer, 0, 0x50008, 0x50001, 0, 0xE0051)
    Call(SpeakToPlayer, 1, 0xBF0007, 0xBF0008, 0, 0xE0052)
    Call(SetCamSpeed, 0, Float(2.0))
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
    Call(PanToTarget, 0, 0, 1)
    Call(WaitForCam, 0, Float(1.0))
    Call(PanToTarget, 0, 0, 0)
    Call(SetNpcJumpscale, 0, 0)
    Call(GetNpcPos, 0, LVar0, LVar1, LVar2)
    Sub(LVar1, 40)
    Add(LVar2, 150)
    Call(NpcJump0, 0, LVar0, LVar1, LVar2, 25)
    Call(SpeakToPlayer, 0, 0x50004, 0x50001, 0, 0xE0053)
    Call(obk_09_ChangeNpcToPartner, 0, 9)
    Call(obk_09_LoadPartyImage)
    Exec(obk_09_EVS_PlayNewPartnerSong)
    Wait(15)
    Call(ShowMessageAtScreenPos, 0x1D018D, 160, 40)
    Exec(obk_09_EVS_ResetMusic)
    Wait(10)
    Wait(10)
    Call(DisablePartnerAI, 0)
    Call(SpeakToPlayer, -4, 0x5000B, 0x5000B, 0, 0xE0054)
    Call(EnablePartnerAI)
    Call(DisablePlayerInput, 0)
    Call(TTYD64_RaisePartnerMaxHP, 9)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_obk_09(void) {
    Mod_ReplaceScript("TTYD64", &obk_09_EVS_EnterMap, &TTYD64_obk_09_Script_EnterDoubleDoor_80240580);
}
