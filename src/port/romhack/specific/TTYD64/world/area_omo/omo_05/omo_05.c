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

extern s32 omo_05_AllConsumables[ITEM_NUM_CONSUMABLES + 1];
extern NpcGroupList omo_05_DefaultNPCs;
extern EvtScript omo_05_EVS_BindExitTriggers;
extern EvtScript omo_05_EVS_ChooseItem;
extern EvtScript omo_05_EVS_Main;
extern EvtScript omo_05_EVS_MakeEntities;
extern EvtScript omo_05_EVS_NpcInteract_GourmetGuy;
extern EvtScript omo_05_EVS_SetupGizmos;
extern EvtScript omo_05_EVS_SetupMusic;
extern MapSettings omo_05_settings;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GetAngleToPlayer);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetSelfVar);
API_CALLABLE(GotoMap);
API_CALLABLE(InterpNpcYaw);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(NpcFacePlayer);
API_CALLABLE(NpcJump0);
API_CALLABLE(NpcMoveTo);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlaySoundAtNpc);
API_CALLABLE(PlayerFaceNpc);
API_CALLABLE(PlayerJump);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(RemoveNpc);
API_CALLABLE(ResetCam);
API_CALLABLE(RotateModel);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamDistance);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamPitch);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetGroupVisibility);
API_CALLABLE(SetItemFlags);
API_CALLABLE(SetItemPos);
API_CALLABLE(SetMotionBlurParams);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcJumpscale);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetNpcRotation);
API_CALLABLE(SetNpcRotationPivot);
API_CALLABLE(SetNpcSpeed);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerJumpscale);
API_CALLABLE(SetSelfVar);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(ShowMessageAtScreenPos);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(WaitForCam);
API_CALLABLE(func_802D2484);
API_CALLABLE(omo_05_MakeAllConsumablesItemList);
API_CALLABLE(omo_05_SpinCameraAround);

extern EntryList TTYD64_omo_05_EntryList;
extern EvtScript TTYD64_omo_05_Script_Main_EnterWalk;
extern EvtScript TTYD64_omo_05_Script_Interact_80243224;
extern EvtScript TTYD64_omo_05_Script_ScriptedSpring_Entity8024524C;
extern EvtScript TTYD64_omo_05_Script_MakeEntities;
extern EvtScript TTYD64_omo_05_Script_EnterMap;
extern EvtScript TTYD64_omo_05_Script_EnterMap_Spring;

// clang-format off
EntryList TTYD64_omo_05_EntryList = {
    { 590.0f, 0.0f, 135.0f, 270.0f },
    { 590.0f, 10.0f, -140.0f, 270.0f },
    { -600.0f, 10.0f, 0.0f, 90.0f },
    { 600.0f, 10.0f, 0.0f, 270.0f },
    { -499.0f, 211.0f, -95.0f, 90.0f },
};

EvtScript TTYD64_omo_05_Script_Main_EnterWalk = {
    Set(GameByte(425), 16)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 1, Ref(omo_05_DefaultNPCs))
    ExecWait(omo_05_EVS_MakeEntities)
    ExecWait(omo_05_EVS_SetupGizmos)
    Exec(omo_05_EVS_SetupMusic)
    Call(SetCamLeadPlayer, 0, 0)
    Call(SetGroupVisibility, 136, 0)
    IfGe(GameByte(0), -2)
        Call(RotateModel, 46, 105, 0, 1, 0)
        Call(RotateModel, 47, 105, 0, 1, 0)
        Call(RotateModel, 48, 105, 0, 1, 0)
        Call(RotateModel, 50, 105, 0, 1, 0)
        Call(RotateModel, 51, 105, 0, 1, 0)
        Call(RotateModel, 52, 105, 0, 1, 0)
        Call(ModifyColliderFlags, 0, 0, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
    EndIf
    Exec(TTYD64_omo_05_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_omo_05_Script_Interact_80243224 = {
    Call(DisablePlayerInput, 1)
    Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
    Call(UseSettingsFrom, 0, LVar0, 0, LVar2)
    Call(SetPanTarget, 0, LVar0, 0, LVar2)
    Call(SetCamDistance, 0, 350)
    Call(SetCamPitch, 0, Float(17.5), Float(-10.0))
    Call(SetCamSpeed, 0, Float(4.0))
    Call(PanToTarget, 0, 0, 1)
    Call(WaitForCam, 0, Float(1.0))
    Call(omo_05_MakeAllConsumablesItemList)
    Call(NpcFacePlayer, -1, 1)
    Call(SetNpcAnimation, -1, 0xC10001)
    IfEq(GameFlag(1099), 0)
        Call(SpeakToPlayer, -1, 0xC10004, 0xC10001, 0, 0xF0040)
        Set(GameFlag(1099), 1)
    Else
        Call(SpeakToPlayer, -1, 0xC10004, 0xC10001, 0, 0xF0041)
    EndIf
    Set(LVar0, Ref(omo_05_AllConsumables))
    Set(LVar1, -1)
    ExecWait(omo_05_EVS_ChooseItem)
    IfLe(LVar0, 0)
        Call(SetNpcAnimation, -1, 0xC1000D)
        Call(ResetCam, 0, Float(8.0))
        Call(DisablePlayerInput, 0)
        Return
    EndIf
    Set(LVar8, LVar0)
    Call(TTYD64_omo_05_Function_GetItemFlavor, LVar0)
    Call(MakeItemEntity, LVar8, -255, 35, 110, 1, 0)
    Set(LVar7, LVar0)
    Call(SetItemFlags, LVar7, 64, 1)
    Call(SetNpcAnimation, -1, 0xC10005)
    Loop(6)
        Wait(10)
        Call(PlaySoundAtNpc, -1, 8341, 0)
    EndLoop
    IfNe(LVar9, 2)
        Call(ResetCam, 0, Float(10.0))
        Wait(10)
        Call(PlaySoundAtNpc, -1, 8342, 0)
        Call(SetNpcAnimation, -1, 0xC10006)
        Call(SetItemFlags, LVar7, 64, 0)
        Call(GetAngleToPlayer, -1, LVar0)
        IfLt(LVar0, 180)
            Call(MakeLerp, 0, 100, 7, 0)
            Loop(0)
                Call(UpdateLerp)
                SetF(LVar2, Float(-1.0))
                SetF(LVar3, Float(-0.349609375))
                SetF(LVar4, Float(0.0))
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar0)
                MulF(LVar4, LVar0)
                AddF(LVar2, Float(-270.0))
                AddF(LVar3, Float(35.0))
                AddF(LVar4, Float(110.0))
                Call(SetItemPos, LVar7, LVar2, LVar3, LVar4)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
            Call(MakeLerp, 0, 100, 7, 0)
            Loop(0)
                Call(UpdateLerp)
                SetF(LVar2, Float(-1.0))
                SetF(LVar3, Float(0.3505859375))
                SetF(LVar4, Float(0.0))
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar0)
                MulF(LVar4, LVar0)
                AddF(LVar2, Float(-355.0))
                AddF(LVar3, Float(0.0))
                AddF(LVar4, Float(110.0))
                Call(SetItemPos, LVar7, LVar2, LVar3, LVar4)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
        Else
            Call(MakeLerp, 0, 100, 7, 0)
            Loop(0)
                Call(UpdateLerp)
                SetF(LVar2, Float(1.0))
                SetF(LVar3, Float(-0.349609375))
                SetF(LVar4, Float(0.0))
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar0)
                MulF(LVar4, LVar0)
                AddF(LVar2, Float(-240.0))
                AddF(LVar3, Float(35.0))
                AddF(LVar4, Float(110.0))
                Call(SetItemPos, LVar7, LVar2, LVar3, LVar4)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
            Call(MakeLerp, 0, 100, 7, 0)
            Loop(0)
                Call(UpdateLerp)
                SetF(LVar2, Float(1.0))
                SetF(LVar3, Float(0.3505859375))
                SetF(LVar4, Float(0.0))
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar0)
                MulF(LVar4, LVar0)
                AddF(LVar2, Float(-155.0))
                AddF(LVar3, Float(0.0))
                AddF(LVar4, Float(110.0))
                Call(SetItemPos, LVar7, LVar2, LVar3, LVar4)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
        EndIf
    EndIf
    Call(RemoveItemEntity, LVar7)
    Call(SetNpcAnimation, -1, 0xC10001)
    Switch(LVar9)
    CaseEq(0)
        Call(SpeakToPlayer, -1, 0xC10004, 0xC10001, 0, 0xF0042)
        Call(SetNpcAnimation, -1, 0xC1000D)
    CaseEq(1)
        Call(SpeakToPlayer, -1, 0xC10004, 0xC10001, 0, 0xF0043)
        Call(SetNpcAnimation, -1, 0xC1000D)
    CaseEq(2)
        Thread
            Call(ShowMessageAtScreenPos, 0xF0044, 160, 40)
        EndThread
        Call(DisablePartnerAI, 0)
        Call(SetNpcAnimation, -1, 0xC10007)
        Thread
            Call(SetNpcFlagBits, 2, 2, 0)
            Call(GetNpcPos, 2, LVar0, LVar1, LVar2)
            Call(SetNpcJumpscale, 2, Float(0.05078125))
            Call(NpcJump0, 2, LVar0, 2, LVar2, 8)
            Call(SetNpcRotationPivot, 2, 15)
            Set(LVar3, 0)
            Loop(5)
                Add(LVar3, 50)
                Call(SetNpcRotation, 2, 0, 0, LVar3)
                Wait(1)
            EndLoop
            Add(LVar2, 20)
            Call(SetNpcJumpscale, 2, Float(0.2001953125))
            Call(NpcJump0, 2, LVar0, -10, LVar2, 8)
            Wait(10)
            Call(RemoveNpc, 2)
        EndThread
        Thread
            Call(SetNpcFlagBits, 1, 2, 0)
            Call(GetNpcPos, 1, LVar0, LVar1, LVar2)
            Call(SetNpcJumpscale, 1, Float(0.05078125))
            Call(NpcJump0, 1, LVar0, 2, LVar2, 8)
            Call(SetNpcRotationPivot, 1, 15)
            Set(LVar3, 0)
            Loop(5)
                Sub(LVar3, 50)
                Call(SetNpcRotation, 1, 0, 0, LVar3)
                Wait(1)
            EndLoop
            Add(LVar2, 20)
            Call(SetNpcJumpscale, 1, Float(0.2001953125))
            Call(NpcJump0, 1, LVar0, -10, LVar2, 8)
            Wait(10)
            Call(RemoveNpc, 1)
        EndThread
        Call(UseSettingsFrom, 0, -250, 25, -100)
        Call(SetPanTarget, 0, -250, 25, -100)
        Call(SetCamDistance, 0, Float(420.0))
        Call(SetCamPitch, 0, Float(12.0), Float(-1.5))
        Call(SetCamSpeed, 0, Float(25.0))
        Call(PanToTarget, 0, 0, 1)
        Call(WaitForCam, 0, Float(1.0))
        Call(PlaySoundAtNpc, -1, 897, 0)
        Wait(33)
        Call(SetCamDistance, 0, Float(320.0))
        Call(SetCamPitch, 0, Float(13.0), Float(-0.7998046875))
        Call(SetCamSpeed, 0, Float(25.0))
        Call(PanToTarget, 0, 0, 1)
        Call(WaitForCam, 0, Float(1.0))
        Call(PlaySoundAtNpc, -1, 898, 0)
        Wait(33)
        Call(SetCamDistance, 0, Float(250.0))
        Call(SetCamPitch, 0, Float(14.0), Float(0.0))
        Call(SetCamSpeed, 0, Float(25.0))
        Call(PanToTarget, 0, 0, 1)
        Call(WaitForCam, 0, Float(1.0))
        Call(PlaySoundAtNpc, -1, 899, 0)
        Wait(18)
        Call(SetMusic, 0, 114, 0, 8)
        Wait(30)
        Call(SetMotionBlurParams, 0, 0, 0, 320, 240, 128, 10)
        Loop(7)
            Call(SetCamDistance, 0, Float(320.0))
            Call(SetCamPitch, 0, Float(14.0), Float(0.0))
            Call(SetCamSpeed, 0, Float(15.0))
            Call(PanToTarget, 0, 0, 1)
            Call(WaitForCam, 0, Float(1.0))
            Call(SetCamDistance, 0, Float(250.0))
            Call(SetCamPitch, 0, Float(14.0), Float(0.0))
            Call(SetCamSpeed, 0, Float(15.0))
            Call(PanToTarget, 0, 0, 1)
            Call(WaitForCam, 0, Float(1.0))
        EndLoop
        Call(RotateModel, 46, 105, 0, 1, 0)
        Call(RotateModel, 47, 105, 0, 1, 0)
        Call(RotateModel, 48, 105, 0, 1, 0)
        Call(RotateModel, 50, 105, 0, 1, 0)
        Call(RotateModel, 51, 105, 0, 1, 0)
        Call(RotateModel, 52, 105, 0, 1, 0)
        Wait(5)
        Call(omo_05_SpinCameraAround)
        Call(omo_05_SpinCameraAround)
        Call(omo_05_SpinCameraAround)
        Call(SetMotionBlurParams, 0, 0, 0, 320, 240, 0, 10)
        Call(UseSettingsFrom, 0, -250, 0, 100)
        Call(SetPanTarget, 0, -250, 0, 100)
        Call(SetCamSpeed, 0, Float(90.0))
        Call(PanToTarget, 0, 0, 1)
        Call(SetSelfVar, 0, 1)
        Thread
            Label(19)
            Call(PlayerFaceNpc, -1, 0)
            Call(GetSelfVar, 0, LVar0)
            IfNe(LVar0, 0)
                Wait(1)
                Goto(19)
            EndIf
        EndThread
        Call(PlaySoundAtNpc, -1, 900, 0)
        Call(SetNpcAnimation, -1, 0xC10003)
        Call(SetNpcFlagBits, -1, 256, 1)
        Call(SetNpcSpeed, -1, Float(20.0))
        Call(NpcMoveTo, -1, 0, 110, 0)
        Wait(20)
        Call(PlaySoundAtNpc, -1, 900, 0)
        Call(SetNpcFlagBits, -1, 128, 1)
        Call(SetNpcPos, -1, 0, 145, 110)
        Call(NpcMoveTo, -1, -500, 110, 0)
        Call(SetNpcFlagBits, -1, 128, 0)
        Wait(20)
        Call(PlaySoundAtNpc, -1, 900, 0)
        Call(SetNpcRotation, -1, 0, 0, -45)
        Call(InterpNpcYaw, -1, 90, 0)
        Call(MakeLerp, 0, 100, 30, 0)
        Label(10)
        Call(UpdateLerp)
        SetF(LVar2, Float(3.9501953125))
        SetF(LVar3, Float(-1.8994140625))
        SetF(LVar4, Float(0.0))
        MulF(LVar2, LVar0)
        MulF(LVar3, LVar0)
        MulF(LVar4, LVar0)
        AddF(LVar2, Float(-445.0))
        AddF(LVar3, Float(130.0))
        AddF(LVar4, Float(230.0))
        Call(SetNpcPos, -1, LVar2, LVar3, LVar4)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(10)
        EndIf
        Wait(20)
        Call(PlaySoundAtNpc, -1, 900, 0)
        Call(SetNpcRotation, -1, 0, 0, 0)
        Call(SetNpcPos, -1, -500, 0, 110)
        Call(NpcMoveTo, -1, -250, 110, 0)
        Wait(20)
        Call(SetNpcAnimation, -1, 0xC10008)
        Thread
            Wait(15)
            Call(SetCamPitch, 0, Float(-2.5), Float(-24.0))
            Call(SetCamSpeed, 0, Float(1.5))
            Call(PanToTarget, 0, 0, 1)
        EndThread
        Thread
            Wait(15)
            Call(PlaySoundAtNpc, -1, 901, 0)
            Call(SetNpcAnimation, -1, 0xC1000B)
            Call(SetNpcJumpscale, -1, Float(0.001953125))
            Call(NpcJump0, -1, -250, 500, 110, 40)
            Call(SetSelfVar, 0, 2)
        EndThread
        Call(ShowMessageAtScreenPos, 0xF0045, 160, 40)
        Label(12)
        Call(GetSelfVar, 0, LVar0)
        IfNe(LVar0, 2)
            Wait(1)
            Goto(12)
        EndIf
        Call(SetSelfVar, 0, 0)
        Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
        Call(MakeItemEntity, 41, LVar0, 400, LVar2, 13, GameFlag(1106))
        Wait(30)
        Call(EnablePartnerAI)
        Wait(20)
        Call(SetPlayerAnimation, 0x10021)
        Wait(1)
        Call(ResetCam, 0, Float(90.0))
        Wait(60)
        Call(SetPlayerAnimation, 0x10002)
        Call(ModifyColliderFlags, 0, 0, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
        Set(GameByte(0), -2)
    EndSwitch
    Exec(omo_05_EVS_SetupMusic)
    Call(DisablePlayerInput, 0)
    IfEq(GameByte(0), -2)
        Call(RemoveNpc, -1)
    EndIf
    Return
    End
};

EvtScript TTYD64_omo_05_Script_ScriptedSpring_Entity8024524C = {
    IfEq(MapFlag(0), 1)
        Return
    EndIf
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerActionState, 6)
    Wait(1)
    Call(SetPlayerJumpscale, Float(0.7001953125))
    Call(PlayerJump, -540, 248, -150, 30)
    Thread
        Wait(10)
        Call(GotoMap, (Bytecode) "omo_19", 0)
    EndThread
    Return
    End
};

EvtScript TTYD64_omo_05_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_YellowBlock), 400, 70, -150, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1134))
    Call(MakeEntity, Ref(Entity_YellowBlock), 550, 70, -150, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1135))
    IfEq(GameFlag(1106), 0)
        IfGt(GameByte(0), -3)
            Call(MakeItemEntity, 41, -250, 0, 120, 0, GameFlag(1106))
        EndIf
    EndIf
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), 475, 70, -150, 0, 154, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1136))
    Call(MakeEntity, Ref(Entity_StarBoxLauncher), -540, 10, -150, 0, 0x80000000)
    Call(AssignScript, Ref(TTYD64_omo_05_Script_ScriptedSpring_Entity8024524C))
    Call(MakeItemEntity, 343, -540, 106, -150, 17, 0)
    Call(MakeItemEntity, 343, -540, 144, -150, 17, 0)
    Call(MakeItemEntity, 343, -540, 177, -150, 17, 0)
    Return
    End
};

EvtScript TTYD64_omo_05_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(4)
        Exec(TTYD64_omo_05_Script_EnterMap_Spring)
        Wait(8)
        Exec(omo_05_EVS_BindExitTriggers)
    CaseDefault
        Set(LVar0, Ref(omo_05_EVS_BindExitTriggers))
        Exec(EnterWalk)
        Wait(1)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_omo_05_Script_EnterMap_Spring = {
    Set(MapFlag(0), 1)
    Call(DisablePlayerInput, 1)
    Call(SetPlayerActionState, 8)
    Call(func_802D2484)
    Call(SetPlayerActionState, 0)
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerInput, 0)
    Set(MapFlag(0), 0)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_omo_05(void) {
    omo_05_settings.entryList = &TTYD64_omo_05_EntryList;
    omo_05_settings.entryCount = 5;
    Mod_ReplaceScript("TTYD64", &omo_05_EVS_Main, &TTYD64_omo_05_Script_Main_EnterWalk);
    Mod_ReplaceScript("TTYD64", &omo_05_EVS_NpcInteract_GourmetGuy, &TTYD64_omo_05_Script_Interact_80243224);
    Mod_ReplaceScript("TTYD64", &omo_05_EVS_MakeEntities, &TTYD64_omo_05_Script_MakeEntities);
}
