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

extern EvtScript kkj_25_AddStarSpiritHovering;
extern EvtScript kkj_25_EVS_Scene_KammyDefeated;
extern EvtScript kkj_25_EVS_SpawnBowserStarEnergyWaves;
extern Vec3f kkj_25_TwinkStrikeBowserPath[];

API_CALLABLE(AdjustCam);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(FadeOutMusic);
API_CALLABLE(GetNextPathPos);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(InterpNpcYaw);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(LoadPath);
API_CALLABLE(NpcJump0);
API_CALLABLE(NpcMoveTo);
API_CALLABLE(PanToTarget);
API_CALLABLE(PartnerIsFlying);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAt);
API_CALLABLE(PlaySoundAtNpc);
API_CALLABLE(PlayerJump);
API_CALLABLE(SetCamDistance);
API_CALLABLE(SetCamPitch);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcDecoration);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcImgFXParams);
API_CALLABLE(SetNpcJumpscale);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetNpcVar);
API_CALLABLE(SetNpcYaw);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerJumpscale);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowMessageAtScreenPos);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(StopSound);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(WaitForCam);
API_CALLABLE(kkj_25_DismissStarsOrbitingKammy2);
API_CALLABLE(kkj_25_SpawnStarsOrbitingKammy2);

extern EvtScript TTYD64_kkj_25_Script_80248998;

// clang-format off
EvtScript TTYD64_kkj_25_Script_80248998 = {
    Call(DisablePlayerInput, 1)
    Call(DisablePartnerAI, 0)
    Call(SetPlayerAnimation, 0x10006)
    Call(SetPlayerPos, 100, 0, 0)
    Call(PartnerIsFlying, LVar0)
    IfEq(LVar0, 0)
        Call(SetNpcPos, -4, 60, 10, 0)
    Else
        Call(SetNpcPos, -4, 60, 0, 0)
    EndIf
    Call(SetNpcYaw, -4, 90)
    Call(SetNpcAnimation, -4, 262)
    Call(GetNpcPos, 1, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
    Call(SetCamSpeed, 0, Float(90.0))
    Call(SetCamPitch, 0, Float(17.0), Float(-8.5))
    Call(SetCamDistance, 0, 300)
    Call(PanToTarget, 0, 0, 1)
    Call(GetNpcPos, 7, LVar0, LVar1, LVar2)
    Add(LVar1, 30)
    Set(LVar3, 20)
    Set(LVar4, 3)
    Call(kkj_25_SpawnStarsOrbitingKammy2)
    Set(MapVar(1), LVar0)
    Wait(20)
    Call(InterpNpcYaw, 1, 90, 0)
    Wait(20)
    Call(InterpNpcYaw, 1, 270, 0)
    Wait(10)
    Call(SetNpcAnimation, 1, 0xC0000)
    Wait(10)
    Call(SetNpcAnimation, 1, 0xC0026)
    Call(SpeakToPlayer, 1, 0xC0001, 0xC0026, 5, 0x13009C)
    Wait(10)
    Call(InterpNpcYaw, 1, 90, 0)
    Call(SpeakToPlayer, 4, 0x200009, 0x200001, 0, 0x13009D)
    Wait(10)
    Call(StopSound, 557)
    Call(SetMusic, 0, 104, 0, 8)
    Call(InterpNpcYaw, 1, 270, 0)
    Wait(10)
    Call(SpeakToPlayer, 1, 0xC0001, 0xC0026, 5, 0x13009E)
    Wait(10)
    Call(SpeakToPlayer, 4, 0x200009, 0x200001, 5, 0x13009F)
    Wait(10)
    Call(SetNpcAnimation, 1, 0xC0002)
    Wait(10)
    Call(SetNpcAnimation, 1, 0xD000F)
    Wait(10)
    Call(LoadPath, 20, (Bytecode) kkj_25_TwinkStrikeBowserPath, 3, 1)
    Loop(0)
        Call(GetNextPathPos)
        Call(SetNpcPos, 4, LVar1, LVar2, LVar3)
        Wait(1)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
    EndLoop
    Wait(20)
    Call(GetNpcPos, 1, LVar0, LVar1, LVar2)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
    Call(SetCamDistance, 0, 245)
    Call(SetCamPitch, 0, Float(17.0), Float(-11.0))
    Call(SetCamSpeed, 0, Float(0.6005859375))
    Call(PanToTarget, 0, 0, 1)
    Call(WaitForCam, 0, Float(1.0))
    Call(GetNpcPos, 1, LVar0, LVar1, LVar2)
    Add(LVar1, 10)
    Call(PlaySoundAt, 8273, 0, LVar0, LVar1, LVar2)
    Call(PlayEffect_impl, 34, 5, LVar0, LVar1, LVar2, 40, 120, 45, 150, 0, 0, 0, 0, 0)
    Wait(150)
    Call(SetNpcAnimation, 5, 0x80000E)
    Call(SetNpcDecoration, 5, 0, 1)
    Call(SetNpcDecoration, 5, 1, 6)
    Set(LVar8, 5)
    Exec(kkj_25_EVS_SpawnBowserStarEnergyWaves)
    Wait(5)
    Call(GetNpcPos, 5, LVar0, LVar1, LVar2)
    Add(LVar0, -50)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
    Call(SetCamDistance, 0, 400)
    Call(SetCamPitch, 0, Float(16.0), Float(-10.0))
    Call(SetCamSpeed, 0, Float(90.0))
    Call(PanToTarget, 0, 0, 1)
    Set(LVar0, MapVar(1))
    Call(kkj_25_DismissStarsOrbitingKammy2)
    Wait(20)
    Call(SpeakToPlayer, 5, 0x80000E, 0x80000E, 0, 0x1300A0)
    Wait(10)
    Call(SetNpcPos, 4, 500, 200, 0)
    Call(SetNpcJumpscale, 4, Float(0.0))
    Call(NpcJump0, 4, 205, 90, 0, 20)
    Call(PlaySoundAtNpc, 4, 233, 0)
    Call(SetNpcAnimation, 5, 0x80000D)
    Call(PlayEffect_impl, 24, 3, 205, 90, 0, -1, -1, 0, 3, 0, 0, 0, 0, 0)
    Thread
        Call(ShakeCam, 0, 0, 8, Float(1.5))
    EndThread
    Call(SetNpcJumpscale, 4, Float(0.30078125))
    Call(NpcJump0, 4, 195, 200, 0, 20)
    Wait(10)
    Call(SetPlayerAnimation, 0x10002)
    Call(SetNpcAnimation, -4, 262)
    Thread
        Call(SetNpcAnimation, 5, 0x800002)
        Call(InterpNpcYaw, 5, 90, 0)
        Wait(15)
        Call(InterpNpcYaw, 5, 270, 0)
        Wait(15)
        Call(InterpNpcYaw, 5, 90, 0)
        Wait(20)
        Call(SetNpcAnimation, 5, 0x800004)
        Call(GetNpcPos, 5, LVar0, LVar1, LVar2)
        Add(LVar0, 50)
        Call(NpcMoveTo, 5, LVar0, LVar2, 50)
        Call(SetNpcAnimation, 5, 0x800002)
    EndThread
    Wait(15)
    Call(AdjustCam, 0, Float(2.0), 0, 300, Float(17.0), Float(-13.0))
    Call(PlayEffect_impl, 34, 5, 100, 45, -66, 40, 50, 45, 80, 0, 0, 0, 0, 0)
    Call(PlaySound, 8273)
    Wait(30)
    Set(LVar0, 8)
    Exec(kkj_25_AddStarSpiritHovering)
    Set(LVar0, 9)
    Exec(kkj_25_AddStarSpiritHovering)
    Set(LVar0, 10)
    Exec(kkj_25_AddStarSpiritHovering)
    Set(LVar0, 11)
    Exec(kkj_25_AddStarSpiritHovering)
    Set(LVar0, 12)
    Exec(kkj_25_AddStarSpiritHovering)
    Set(LVar0, 13)
    Exec(kkj_25_AddStarSpiritHovering)
    Set(LVar0, 14)
    Exec(kkj_25_AddStarSpiritHovering)
    Call(GetNpcPos, 8, LVar0, LVar1, LVar2)
    Add(LVar1, 15)
    Call(PlaySoundAt, 0xB000001E, 0, LVar0, LVar1, LVar2)
    Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 10, 0, 0, 0, 0, 0, 0, 0, 0)
    SetF(LVar0, 0)
    Loop(20)
        AddF(LVar0, Float(12.0))
        Call(SetNpcImgFXParams, 8, 7, LVar0, 0, 0, 0)
        Wait(1)
    EndLoop
    Wait(10)
    Thread
        Wait(15)
        Call(InterpPlayerYaw, 270, 0)
        Wait(15)
        Call(InterpPlayerYaw, 90, 0)
        Wait(10)
        Call(SetPlayerAnimation, 0x1002A)
    EndThread
    Call(SpeakToPlayer, 8, 0x120002, 0x120001, 512, 0x1300A1)
    Wait(10)
    Call(PlaySoundAt, 100, 0, LVar0, LVar1, LVar2)
    Call(GetNpcPos, 9, LVar0, LVar1, LVar2)
    Add(LVar1, 15)
    Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 10, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(GetNpcPos, 10, LVar0, LVar1, LVar2)
    Add(LVar1, 15)
    Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 10, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(GetNpcPos, 11, LVar0, LVar1, LVar2)
    Add(LVar1, 15)
    Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 10, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(GetNpcPos, 12, LVar0, LVar1, LVar2)
    Add(LVar1, 15)
    Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 10, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(GetNpcPos, 13, LVar0, LVar1, LVar2)
    Add(LVar1, 15)
    Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 10, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(GetNpcPos, 14, LVar0, LVar1, LVar2)
    Add(LVar1, 15)
    Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 10, 0, 0, 0, 0, 0, 0, 0, 0)
    SetF(LVar0, 0)
    Loop(20)
        AddF(LVar0, Float(12.0))
        Call(SetNpcImgFXParams, 9, 7, LVar0, 0, 0, 0)
        Call(SetNpcImgFXParams, 10, 7, LVar0, 0, 0, 0)
        Call(SetNpcImgFXParams, 11, 7, LVar0, 0, 0, 0)
        Call(SetNpcImgFXParams, 12, 7, LVar0, 0, 0, 0)
        Call(SetNpcImgFXParams, 13, 7, LVar0, 0, 0, 0)
        Call(SetNpcImgFXParams, 14, 7, LVar0, 0, 0, 0)
        Wait(1)
    EndLoop
    Call(SetNpcImgFXParams, 8, 0, 0, 0, 0, 0)
    Call(SetNpcImgFXParams, 9, 0, 0, 0, 0, 0)
    Call(SetNpcImgFXParams, 10, 0, 0, 0, 0, 0)
    Call(SetNpcImgFXParams, 11, 0, 0, 0, 0, 0)
    Call(SetNpcImgFXParams, 12, 0, 0, 0, 0, 0)
    Call(SetNpcImgFXParams, 13, 0, 0, 0, 0, 0)
    Call(SetNpcImgFXParams, 14, 0, 0, 0, 0, 0)
    Call(SetNpcJumpscale, 4, Float(0.0))
    Call(NpcJump0, 4, 140, 65, 30, 20)
    Call(GetNpcPos, 8, LVar0, LVar1, LVar2)
    Add(LVar0, 15)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
    Call(SetCamDistance, 0, 250)
    Call(SetCamPitch, 0, Float(17.0), Float(-8.5))
    Call(SetCamSpeed, 0, Float(0.80078125))
    Call(PanToTarget, 0, 0, 1)
    Wait(10)
    Call(SpeakToPlayer, 4, 0x200009, 0x200001, 0, 0x1300A2)
    Wait(10)
    Call(SpeakToPlayer, 8, 0x120002, 0x120001, 512, 0x1300A3)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
    Call(SetCamDistance, 0, 350)
    Call(SetCamPitch, 0, Float(17.0), Float(-10.0))
    Call(SetCamSpeed, 0, Float(4.0))
    Call(PanToTarget, 0, 0, 1)
    Call(WaitForCam, 0, Float(1.0))
    Wait(10)
    Call(SpeakToPlayer, 8, 0x120002, 0x120001, 512, 0x1300A4)
    Call(SetPlayerAnimation, 0x10029)
    Wait(15)
    Call(SetPlayerAnimation, 0x1002A)
    Wait(5)
    Thread
        Call(SetNpcFlagBits, 8, 0x400000, 0)
        Call(SetNpcJumpscale, 8, Float(3.2001953125))
        Call(GetNpcPos, 8, LVar6, LVar7, LVar8)
        Call(NpcJump0, 8, LVar6, LVar7, LVar8, 5)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Add(LVar1, 20)
        Call(PlaySoundAt, 0xB000001F, 0, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 10, 0, 0, 0, 0, 0, 0, 0, 0)
    EndThread
    Thread
        Wait(20)
        Call(SetNpcFlagBits, 9, 0x400000, 0)
        Call(SetNpcJumpscale, 9, Float(3.2001953125))
        Call(GetNpcPos, 9, LVar6, LVar7, LVar8)
        Call(NpcJump0, 9, LVar6, LVar7, LVar8, 5)
    EndThread
    Thread
        Wait(21)
        Call(SetNpcFlagBits, 10, 0x400000, 0)
        Call(SetNpcJumpscale, 10, Float(3.2001953125))
        Call(GetNpcPos, 10, LVar6, LVar7, LVar8)
        Call(NpcJump0, 10, LVar6, LVar7, LVar8, 5)
    EndThread
    Thread
        Wait(22)
        Call(SetNpcFlagBits, 11, 0x400000, 0)
        Call(SetNpcJumpscale, 11, Float(3.2001953125))
        Call(GetNpcPos, 11, LVar6, LVar7, LVar8)
        Call(NpcJump0, 11, LVar6, LVar7, LVar8, 5)
    EndThread
    Thread
        Wait(20)
        Call(SetNpcFlagBits, 12, 0x400000, 0)
        Call(SetNpcJumpscale, 12, Float(3.2001953125))
        Call(GetNpcPos, 12, LVar6, LVar7, LVar8)
        Call(NpcJump0, 12, LVar6, LVar7, LVar8, 5)
    EndThread
    Thread
        Wait(21)
        Call(SetNpcFlagBits, 13, 0x400000, 0)
        Call(SetNpcJumpscale, 13, Float(3.2001953125))
        Call(GetNpcPos, 13, LVar6, LVar7, LVar8)
        Call(NpcJump0, 13, LVar6, LVar7, LVar8, 5)
    EndThread
    Thread
        Wait(22)
        Call(SetNpcFlagBits, 14, 0x400000, 0)
        Call(SetNpcJumpscale, 14, Float(3.2001953125))
        Call(GetNpcPos, 14, LVar6, LVar7, LVar8)
        Call(NpcJump0, 14, LVar6, LVar7, LVar8, 5)
    EndThread
    Thread
        Wait(23)
        Call(SetNpcFlagBits, 4, 0x400000, 0)
        Call(SetNpcJumpscale, 4, Float(3.2001953125))
        Call(GetNpcPos, 4, LVar6, LVar7, LVar8)
        Call(NpcJump0, 4, LVar6, LVar7, LVar8, 5)
    EndThread
    Thread
        Call(PlayEffect_impl, 51, 2, 100, 28, 10, Float(2.80078125), 100, 0, 0, 0, 0, 0, 0, 0)
        Call(PlaySound, 8493)
        Wait(115)
        Add(LVar1, 20)
        Call(PlaySoundAt, 392, 0, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 82, 4, LVar0, LVar1, LVar2, Float(0.30078125), 30, 0, 0, 0, 0, 0, 0, 0)
    EndThread
    Wait(40)
    Call(PlaySoundAt, 0xB000001F, 0, 110, 20, 3)
    Call(PlayEffect_impl, 17, 0, 110, 20, 3, 10, 0, 0, 0, 0, 0, 0, 0, 0)
    Wait(6)
    Call(PlaySoundAt, 0xB000001F, 0, 100, 20, 3)
    Call(PlayEffect_impl, 17, 0, 100, 20, 3, 15, 0, 0, 0, 0, 0, 0, 0, 0)
    Wait(6)
    Call(PlaySoundAt, 0xB000001F, 0, 90, 20, 3)
    Call(PlayEffect_impl, 17, 0, 90, 20, 3, 20, 0, 0, 0, 0, 0, 0, 0, 0)
    Wait(6)
    Call(PlaySoundAt, 0xB000001F, 0, 110, 20, 3)
    Call(PlayEffect_impl, 17, 0, 110, 20, 3, 25, 0, 0, 0, 0, 0, 0, 0, 0)
    Wait(6)
    Call(SetPlayerAnimation, 0x1001F)
    Loop(3)
        Call(PlaySoundAt, 0xB000001F, 0, 100, 20, 3)
        Call(PlayEffect_impl, 17, 0, 100, 20, 3, 30, 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(6)
        Call(PlaySoundAt, 0xB000001F, 0, 90, 20, 3)
        Call(PlayEffect_impl, 17, 0, 90, 20, 3, 30, 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(6)
        Call(PlaySoundAt, 0xB000001F, 0, 110, 20, 3)
        Call(PlayEffect_impl, 17, 0, 110, 20, 3, 30, 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(6)
    EndLoop
    Call(TTYD64_kkj_25_Function_FullyHeal)
    Wait(30)
    Call(ShowMessageAtScreenPos, 0x1D0199, 160, 40)
    Wait(30)
    Call(SetPlayerAnimation, 0x10006)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Add(LVar0, 45)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
    Call(SetCamDistance, 0, 450)
    Call(SetCamPitch, 0, Float(17.0), Float(-10.0))
    Call(SetCamSpeed, 0, Float(5.0))
    Call(PanToTarget, 0, 0, 1)
    Thread
        Call(SpeakToPlayer, 5, 0x800006, 0x800002, 0, 0x1300A5)
    EndThread
    Wait(5)
    Call(InterpNpcYaw, 5, 270, 0)
    Wait(25)
    Call(FadeOutMusic, 0, 500)
    Wait(20)
    Thread
        Call(SetPlayerJumpscale, Float(0.5))
        Call(PlayerJump, 100, 0, 0, 20)
    EndThread
    Thread
        Call(SetNpcJumpscale, -4, Float(0.5))
        Call(GetNpcPos, -4, LVar0, LVar1, LVar2)
        Call(NpcJump0, -4, LVar0, LVar1, LVar2, 20)
    EndThread
    Call(SetNpcVar, 5, 0, 1)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_kkj_25(void) {
    Mod_ReplaceScript("TTYD64", &kkj_25_EVS_Scene_KammyDefeated, &TTYD64_kkj_25_Script_80248998);
}
