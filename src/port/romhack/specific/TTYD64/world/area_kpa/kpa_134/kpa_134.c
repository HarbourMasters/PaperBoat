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

extern NpcGroupList kpa_134_DefaultNPCs;
extern EvtScript kpa_134_EVS_BindExitTriggers;
extern EvtScript kpa_134_EVS_BreakBlock_Brick;
extern EvtScript kpa_134_EVS_EnterMap;
extern EvtScript kpa_134_EVS_ExitDoors_kpa_130_0;
extern EvtScript kpa_134_EVS_ExitWalk_kpa_133_1;
extern EvtScript kpa_134_EVS_ExitWalk_kpa_133_2;
extern EvtScript kpa_134_EVS_ExitWalk_kpa_133_3;
extern EvtScript kpa_134_EVS_FlipWallPanel;
extern EvtScript kpa_134_EVS_FlipWallPanels;
extern EvtScript kpa_134_EVS_FocusCam_Wall;
extern EvtScript kpa_134_EVS_LowerWaterLevel0;
extern EvtScript kpa_134_EVS_Main;
extern EvtScript kpa_134_EVS_MakeEntities;
extern EvtScript kpa_134_EVS_RaiseWaterLevel1;
extern EvtScript kpa_134_EVS_SetupChains;
extern EvtScript kpa_134_EVS_SetupLowerChain;
extern EvtScript kpa_134_EVS_SetupMusic;
extern EvtScript kpa_134_EVS_SetupUpperChain;
extern EvtScript kpa_134_EVS_UnlockPrompt_Door;
extern EvtScript kpa_134_EVS_UpdateTexturePan;
extern s32 kpa_134_KeyList_BowsersCastle[];
extern s32 kpa_134_WallPanels[];

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(AssignSwitchFlag);
API_CALLABLE(CloseChoicePopup);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableModel);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(EnableTexPanning);
API_CALLABLE(GetPlayerActionState);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(GrabCamera);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAt);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(RemoveKeyItemAt);
API_CALLABLE(ResetCam);
API_CALLABLE(RotateModel);
API_CALLABLE(ScaleModel);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetGroupVisibility);
API_CALLABLE(SetInterpCamParams);
API_CALLABLE(SetMusic);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetRenderMode);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTexPanOffset);
API_CALLABLE(SetTexPanner);
API_CALLABLE(SetTrackVolumes);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowKeyChoicePopup);
API_CALLABLE(ShowMessageAtScreenPos);
API_CALLABLE(StopSound);
API_CALLABLE(StopTrackingSoundPos);
API_CALLABLE(TranslateGroup);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseDoorSounds);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(WaitForCam);
API_CALLABLE(kpa_134_GetEntityPosition);
API_CALLABLE(kpa_134_RemovePadlock);

extern EvtScript TTYD64_kpa_134_Script_ExitDoubleDoor_802408E8;
extern EvtScript TTYD64_kpa_134_Script_80240A44;
extern EvtScript TTYD64_kpa_134_Script_Main;
extern EvtScript TTYD64_kpa_134_Script_802410C0;
extern EvtScript TTYD64_kpa_134_Script_80241570;
extern EvtScript TTYD64_kpa_134_Script_80241968;
extern EvtScript TTYD64_kpa_134_Script_80243190;
extern EvtScript TTYD64_kpa_134_Script_802435A0;
extern EvtScript TTYD64_kpa_134_Script_MakeEntities;
extern EvtScript TTYD64_kpa_134_Script_SecretWall;
extern EvtScript TTYD64_kpa_134_Script_ExitSecretWall;
extern EvtScript TTYD64_kpa_134_Script_InitNewStuff;
extern EvtScript TTYD64_kpa_134_Script_80240780;

// clang-format off
EvtScript TTYD64_kpa_134_Script_ExitDoubleDoor_802408E8 = {
    SetGroup(27)
    Call(DisablePlayerInput, 1)
    Set(LVar0, 1)
    Set(LVar1, 35)
    Set(LVar2, 98)
    Set(LVar3, 100)
    Exec(ExitDoubleDoor)
    Wait(17)
    Call(GotoMap, (Bytecode) "kpa_130", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_kpa_134_Script_80240A44 = {
    BindTrigger(kpa_134_EVS_ExitWalk_kpa_133_1, 0x80000, 28, 1, 0)
    BindTrigger(kpa_134_EVS_ExitWalk_kpa_133_2, 0x80000, 29, 1, 0)
    BindTrigger(kpa_134_EVS_ExitWalk_kpa_133_3, 0x80000, 43, 1, 0)
    Return
    End
};

EvtScript TTYD64_kpa_134_Script_Main = {
    Set(GameByte(425), 22)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 1, Ref(kpa_134_DefaultNPCs))
    ExecWait(kpa_134_EVS_MakeEntities)
    Exec(kpa_134_EVS_SetupChains)
    IfEq(GameFlag(1590), 0)
        BindTrigger(kpa_134_EVS_FlipWallPanels, 0x20000, AreaFlag(9), 1, 0)
    Else
        Call(ModifyColliderFlags, 0, 17, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 19, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 21, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 23, 0x7FFFFE00)
        Call(EnableModel, 81, 0)
        Call(EnableModel, 79, 0)
        Call(EnableModel, 77, 0)
        Call(EnableModel, 75, 0)
        Call(EnableModel, 73, 0)
        Call(EnableModel, 71, 0)
        Call(EnableModel, 69, 0)
        Call(EnableModel, 67, 0)
        Call(EnableModel, 65, 0)
        Call(EnableModel, 63, 0)
        Call(EnableModel, 61, 0)
        Call(EnableModel, 59, 0)
        Call(EnableModel, 57, 0)
        Call(EnableModel, 55, 0)
    EndIf
    IfEq(GameFlag(1585), 1)
        Call(EnableModel, 89, 0)
        Call(EnableModel, 91, 0)
        Call(ModifyColliderFlags, 0, 44, 0x7FFFFE00)
    Else
        Call(EnableModel, 90, 0)
    EndIf
    Call(EnableTexPanning, 104, 1)
    Call(EnableTexPanning, 106, 1)
    Call(EnableTexPanning, 108, 1)
    Thread
        Set(LVar0, 1)
        Set(LVar1, -100)
        Set(LVar2, 100)
        Set(LVar3, 70)
        Set(LVar4, -70)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(kpa_134_EVS_UpdateTexturePan)
    EndThread
    Thread
        Set(LVar0, 4)
        Set(LVar1, 200)
        Set(LVar2, -100)
        Set(LVar3, 20)
        Set(LVar4, -20)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(kpa_134_EVS_UpdateTexturePan)
    EndThread
    Exec(kpa_134_EVS_SetupMusic)
    Exec(kpa_134_EVS_EnterMap)
    Wait(1)
    Return
    End
};

EvtScript TTYD64_kpa_134_Script_802410C0 = {
    Call(SetRenderMode, 106, 22)
    Call(SetRenderMode, 108, 22)
    Call(EnableModel, 111, 0)
    Call(EnableModel, 113, 0)
    Call(TranslateModel, 115, 0, 30, 0)
    Call(TranslateModel, 117, 0, 0, 0)
    Switch(GameByte(297))
    CaseEq(0)
        Call(SetGroupVisibility, 110, 0)
        Call(ModifyColliderFlags, 0, 48, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 39, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 31, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 50, 0x7FFFFE00)
    CaseEq(1)
        Call(EnableModel, 106, 0)
        Call(TranslateGroup, 105, 0, 120, 0)
        Call(TranslateModel, 108, 0, 120, 0)
        Call(ModifyColliderFlags, 0, 31, 0x7FFFFE00)
        Call(ModifyColliderFlags, 3, 39, 4)
        Call(ModifyColliderFlags, 0, 39, 0x80000)
    CaseEq(2)
        Call(ModifyColliderFlags, 0, 48, 0x7FFFFE00)
        Call(EnableModel, 108, 0)
        Call(TranslateGroup, 105, 0, 220, 0)
        Call(TranslateModel, 106, 0, 220, 0)
    EndSwitch
    Exec(kpa_134_EVS_SetupLowerChain)
    Exec(kpa_134_EVS_SetupUpperChain)
    Return
    End
};

EvtScript TTYD64_kpa_134_Script_80241570 = {
    Wait(20)
    Thread
        Call(ShakeCam, 0, 0, 120, Float(1.0))
    EndThread
    Thread
        Call(GrabCamera, 0, LVar4, LVar5, LVar6, LVar7)
        Call(MakeLerp, LVar6, 600, 20, 0)
        Label(10)
        Call(UpdateLerp)
        Call(SetInterpCamParams, 0, LVar4, LVar5, LVar0, LVar7)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(10)
        EndIf
        Set(LVar2, LVar0)
        Wait(5)
        Call(MakeLerp, LVar7, -20, 20, 0)
        Label(15)
        Call(UpdateLerp)
        Call(SetInterpCamParams, 0, LVar4, LVar5, LVar2, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(15)
        EndIf
    EndThread
    Call(SetGroupVisibility, 105, 1)
    Call(EnableModel, 108, 1)
    Call(PlaySound, 0x80000053)
    Call(MakeLerp, 120, 20, 120, 0)
    Label(30)
    Call(UpdateLerp)
    Call(TranslateGroup, 105, 0, LVar0, 0)
    Call(TranslateModel, 108, 0, LVar0, 0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(30)
    EndIf
    Call(PlaySound, 1579)
    Call(StopTrackingSoundPos, 555)
    Call(SetGroupVisibility, 105, 0)
    Call(EnableModel, 106, 0)
    Call(EnableModel, 108, 0)
    Call(ModifyColliderFlags, 0, 48, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 50, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 39, 0x7FFFFE00)
    Wait(10)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(ResetCam, 0, Float(90.0))
    Call(PanToTarget, 0, 0, 0)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Thread
        Set(LVar0, 17)
        Loop(13)
            Add(LVar0, 1)
            Call(TranslateModel, 115, 0, LVar0, 0)
            Wait(1)
        EndLoop
    EndThread
    Return
    End
};

EvtScript TTYD64_kpa_134_Script_80241968 = {
    Wait(20)
    Thread
        Call(ShakeCam, 0, 0, 220, Float(1.0))
    EndThread
    Thread
        Wait(60)
        Call(GrabCamera, 0, LVar4, LVar5, LVar6, LVar7)
        Call(MakeLerp, LVar6, 600, 20, 0)
        Label(10)
        Call(UpdateLerp)
        Call(SetInterpCamParams, 0, LVar4, LVar5, LVar0, LVar7)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(10)
        EndIf
        Set(LVar2, LVar0)
        Wait(5)
        Call(MakeLerp, LVar7, -20, 20, 0)
        Label(15)
        Call(UpdateLerp)
        Call(SetInterpCamParams, 0, LVar4, LVar5, LVar2, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(15)
        EndIf
    EndThread
    Call(PlaySoundAt, 0x80000052, 0, 118, 115, -11)
    Wait(20)
    Thread
        Call(SetTexPanner, 111, 2)
        Call(SetTexPanner, 113, 3)
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 0)
        Loop(1000)
            Call(SetTexPanOffset, 2, 0, LVar0, LVar1)
            Call(SetTexPanOffset, 3, 0, 0, LVar2)
            Add(LVar0, 1000)
            Add(LVar1, 4000)
            Add(LVar2, -1500)
            Wait(1)
        EndLoop
    EndThread
    Thread
        Call(EnableModel, 111, 1)
        Call(MakeLerp, 400, 0, 20, 0)
        Label(20)
        Call(UpdateLerp)
        Call(TranslateModel, 111, -100, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(20)
        EndIf
        Call(SetGroupVisibility, 105, 1)
        Call(EnableModel, 108, 1)
        Call(EnableModel, 113, 1)
        Call(MakeLerp, 20, 120, 180, 0)
        Label(30)
        Call(UpdateLerp)
        Call(TranslateGroup, 105, 0, LVar0, 0)
        Call(TranslateModel, 108, 0, LVar0, 0)
        Call(TranslateModel, 113, -100, LVar0, 0)
        Call(TranslateModel, 111, -100, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(30)
        EndIf
        Call(MakeLerp, 100, 1, 20, 0)
        Label(40)
        Call(UpdateLerp)
        SetF(LVar2, LVar0)
        DivF(LVar2, 100)
        Call(TranslateModel, 113, -100, 120, 0)
        Call(TranslateModel, 111, -100, 120, 0)
        Call(ScaleModel, 113, LVar2, Float(1.0), LVar2)
        Call(ScaleModel, 111, LVar2, Float(1.0), LVar2)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(40)
        EndIf
        Call(PlaySound, 1578)
        Call(StopTrackingSoundPos, 554)
        Call(EnableModel, 113, 0)
        Call(EnableModel, 111, 0)
    EndThread
    Wait(230)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(ResetCam, 0, Float(90.0))
    Call(PanToTarget, 0, 0, 0)
    Call(ModifyColliderFlags, 1, 48, 0x7FFFFE00)
    Call(ModifyColliderFlags, 1, 50, 0x7FFFFE00)
    Call(ModifyColliderFlags, 1, 39, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 39, 32768)
    Call(ModifyColliderFlags, 3, 39, 4)
    Call(ModifyColliderFlags, 0, 39, 0x80000)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Thread
        Set(LVar0, 17)
        Loop(13)
            Add(LVar0, 1)
            Call(TranslateModel, 115, 0, LVar0, 0)
            Wait(1)
        EndLoop
    EndThread
    Return
    End
};

EvtScript TTYD64_kpa_134_Script_80243190 = {
    Call(DisablePlayerInput, 1)
    Loop(0)
        Wait(1)
        Call(GetPlayerActionState, LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
    EndLoop
    Wait(20)
    Call(ModifyColliderFlags, 0, 17, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 19, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 21, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 23, 0x7FFFFE00)
    UseBuf((Bytecode) kpa_134_WallPanels)
    Call(GetPlayerPos, LVar6, LVar7, LVar8)
    Set(LVar6, 615)
    Exec(kpa_134_EVS_FocusCam_Wall)
    Loop(0)
        BufRead4(LVar5, LVar6, LVar7, LVar8)
        IfEq(LVar5, -1)
            BreakLoop
        EndIf
        Call(PlaySoundAt, 8256, 0, LVar6, LVar7, LVar8)
        Exec(kpa_134_EVS_FlipWallPanel)
        Wait(10)
    EndLoop
    Wait(50)
    Call(StopSound, 8256)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(SetCamSpeed, 0, Float(3.0))
    Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
    Call(WaitForCam, 0, Float(1.0))
    Call(PanToTarget, 0, 0, 0)
    Set(GameFlag(1590), 1)
    Call(DisablePlayerInput, 0)
    Unbind
    Return
    End
};

EvtScript TTYD64_kpa_134_Script_802435A0 = {
    Call(ShowKeyChoicePopup)
    IfEq(LVar0, 0)
        Call(ShowMessageAtScreenPos, 0x1D00D8, 160, 40)
        Call(CloseChoicePopup)
        Return
    EndIf
    IfEq(LVar0, -1)
        Call(CloseChoicePopup)
        Return
    EndIf
    Call(RemoveKeyItemAt, LVar1)
    Set(GameFlag(1589), 1)
    Call(kpa_134_GetEntityPosition, MapVar(1), LVar0, LVar1, LVar2)
    Call(PlaySoundAt, 617, 0, LVar0, LVar1, LVar2)
    Set(LVar0, MapVar(1))
    Call(kpa_134_RemovePadlock)
    Set(LVar1, 0)
    Wait(5)
    Call(CloseChoicePopup)
    Unbind
    BindTrigger(kpa_134_EVS_ExitDoors_kpa_130_0, 256, 35, 1, 0)
    Return
    End
};

EvtScript TTYD64_kpa_134_Script_MakeEntities = {
    IfEq(GameFlag(1589), 0)
        Call(MakeEntity, Ref(Entity_Padlock), 743, 10, 115, 270, 0x80000000)
        Set(MapVar(1), LVar0)
        BindPadlock(kpa_134_EVS_UnlockPrompt_Door, 256, 16384, (Bytecode) kpa_134_KeyList_BowsersCastle, 0, 1)
    Else
        BindTrigger(kpa_134_EVS_ExitDoors_kpa_130_0, 256, 35, 1, 0)
    EndIf
    IfEq(GameFlag(1590), 0)
        Call(MakeEntity, Ref(Entity_BlueSwitch), -224, 355, -25, 0, 0x80000000)
        Call(AssignSwitchFlag, 9)
        Set(MapVar(0), LVar0)
    EndIf
    Call(MakeEntity, Ref(Entity_BrickBlock), -224, 330, -25, 0, 0x80000000)
    Call(AssignScript, Ref(kpa_134_EVS_BreakBlock_Brick))
    Call(MakeEntity, Ref(Entity_SimpleSpring), 475, 0, -20, 90, 60, 0x80000000)
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), 195, 300, -75, 0, 163, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1591))
    Return
    End
};

EvtScript TTYD64_kpa_134_Script_SecretWall = {
    Wait(3)
    Call(DisablePlayerPhysics, 1)
    Call(DisablePlayerInput, 1)
    Call(DisablePartnerAI, 0)
    Thread
        Call(PlaySound, 167)
        Wait(5)
        Call(StopSound, 167)
    EndThread
    Thread
        Call(MakeLerp, 0, 180, 15, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, 119, LVar0, 0, -1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Wait(5)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Sub(LVar2, 20)
    Call(PlayerMoveTo, LVar0, LVar2, 10)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Call(EnablePartnerAI)
    Return
    End
};

EvtScript TTYD64_kpa_134_Script_ExitSecretWall = {
    Call(DisablePlayerPhysics, 1)
    Call(DisablePlayerInput, 1)
    Thread
        Call(PlaySound, 167)
        Wait(5)
        Call(StopSound, 167)
    EndThread
    Thread
        Call(MakeLerp, 0, 180, 15, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, 119, LVar0, 0, -1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Wait(5)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Add(LVar2, 20)
    Call(PlayerMoveTo, LVar0, LVar2, 10)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_kpa_134_Script_InitNewStuff = {
    Call(MakeItemEntity, 348, -75, 115, -114, 17, GameFlag(5697))
    BindTrigger(TTYD64_kpa_134_Script_SecretWall, 256, 63, 1, 0)
    BindTrigger(TTYD64_kpa_134_Script_ExitSecretWall, 256, 64, 1, 0)
    Call(ModifyColliderFlags, 0, 31, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 50, 0x7FFFFE00)
    Return
    End
};

EvtScript TTYD64_kpa_134_Script_80240780 = {
    Call(SetMusic, 0, 100, 0, 8)
    Call(UseDoorSounds, 1)
    Thread
        Wait(30)
        Call(SetTrackVolumes, 6)
    EndThread
    Exec(TTYD64_kpa_134_Script_InitNewStuff)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_kpa_134(void) {
    Mod_ReplaceScript("TTYD64", &kpa_134_EVS_ExitDoors_kpa_130_0, &TTYD64_kpa_134_Script_ExitDoubleDoor_802408E8);
    Mod_ReplaceScript("TTYD64", &kpa_134_EVS_BindExitTriggers, &TTYD64_kpa_134_Script_80240A44);
    Mod_ReplaceScript("TTYD64", &kpa_134_EVS_Main, &TTYD64_kpa_134_Script_Main);
    Mod_ReplaceScript("TTYD64", &kpa_134_EVS_SetupChains, &TTYD64_kpa_134_Script_802410C0);
    Mod_ReplaceScript("TTYD64", &kpa_134_EVS_LowerWaterLevel0, &TTYD64_kpa_134_Script_80241570);
    Mod_ReplaceScript("TTYD64", &kpa_134_EVS_RaiseWaterLevel1, &TTYD64_kpa_134_Script_80241968);
    Mod_ReplaceScript("TTYD64", &kpa_134_EVS_FlipWallPanels, &TTYD64_kpa_134_Script_80243190);
    Mod_ReplaceScript("TTYD64", &kpa_134_EVS_UnlockPrompt_Door, &TTYD64_kpa_134_Script_802435A0);
    Mod_ReplaceScript("TTYD64", &kpa_134_EVS_MakeEntities, &TTYD64_kpa_134_Script_MakeEntities);
    Mod_ReplaceScript("TTYD64", &kpa_134_EVS_SetupMusic, &TTYD64_kpa_134_Script_80240780);
}
