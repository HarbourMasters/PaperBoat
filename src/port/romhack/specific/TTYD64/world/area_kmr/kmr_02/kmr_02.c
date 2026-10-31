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

extern EvtScript kmr_02_EVS_BindExitTriggers;
extern EvtScript kmr_02_EVS_DropDoor_House;
extern EvtScript kmr_02_EVS_EnterMap;
extern EvtScript kmr_02_EVS_ExitWalk_kmr_00_0;
extern EvtScript kmr_02_EVS_ExitWalk_kmr_05_1;
extern EvtScript kmr_02_EVS_ExitWalk_kmr_09_0;
extern EvtScript kmr_02_EVS_Goombaria_Kiss;
extern EvtScript kmr_02_EVS_HandOverDolly;
extern EvtScript kmr_02_EVS_LetterReward_Goompapa;
extern EvtScript kmr_02_EVS_Pipe_EnterVertical;
extern EvtScript kmr_02_EVS_PopSong;
extern EvtScript kmr_02_EVS_PushNewPartnerSong;
extern EvtScript kmr_02_EVS_ReturnToVillage;
extern EvtScript kmr_02_EVS_RoomListener_House;
extern EvtScript kmr_02_EVS_SetDoorRot_House;
extern EvtScript kmr_02_EVS_SetWallRot_House;
extern EvtScript kmr_02_EVS_SetWallsDown_ToadHouse;
extern EvtScript kmr_02_EVS_SetupGoombaRoadGate;
extern EvtScript kmr_02_GiveItemReward;
extern MapSettings kmr_02_settings;

API_CALLABLE(AddStarPieces);
API_CALLABLE(AdjustCam);
API_CALLABLE(CloseMessage);
API_CALLABLE(ContinueSpeech);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableNpcAI);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(EndSpeech);
API_CALLABLE(GetAngleBetweenNPCs);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetLoadType);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(InterpNpcYaw);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(MakeLerp);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(NpcFacePlayer);
API_CALLABLE(NpcJump0);
API_CALLABLE(NpcMoveTo);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtCollider);
API_CALLABLE(PlaySoundAtNpc);
API_CALLABLE(PlayerFaceNpc);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(RemoveKeyItemAt);
API_CALLABLE(ResetCam);
API_CALLABLE(RestartNpcAI);
API_CALLABLE(RotateModel);
API_CALLABLE(SetCamDistance);
API_CALLABLE(SetCamPitch);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcJumpscale);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetNpcSpeed);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetPlayerSpeed);
API_CALLABLE(ShowChoice);
API_CALLABLE(ShowMessageAtScreenPos);
API_CALLABLE(SpeakToNpc);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UpdatePlayerImgFX);
API_CALLABLE(UseExitHeading);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(WaitForCam);
API_CALLABLE(kmr_02_ChangeNpcToPartner);
API_CALLABLE(kmr_02_CloseStatusBar);
API_CALLABLE(kmr_02_IsPlayerHPFull);
API_CALLABLE(kmr_02_LoadHeartBlockMsgImg);
API_CALLABLE(kmr_02_LoadPartyImage);
API_CALLABLE(kmr_02_OpenPauseMenu);
API_CALLABLE(kmr_02_RemoveGoompaPartner);
API_CALLABLE(kmr_02_WaitForStartInput);
API_CALLABLE(kmr_02_func_80242014_8B2084);
API_CALLABLE(sam_11_UpdateHouseShowHide);

extern EvtScript TTYD64_kmr_02_Script_80244D38;
extern EvtScript TTYD64_kmr_02_Script_EnterWalk_80244D9C;
extern EvtScript TTYD64_kmr_02_Script_80248910;
extern EvtScript TTYD64_kmr_02_Script_ComeFromAttic;
extern EvtScript TTYD64_kmr_02_Script_ExitB;
extern EvtScript TTYD64_kmr_02_Script_802497F4;
extern EvtScript TTYD64_kmr_02_Script_Goompa_TalkAboutBadges;
extern EntryList TTYD64_kmr_02_EntryList;

// clang-format off
EvtScript TTYD64_kmr_02_Script_80244D38 = {
    BindTrigger(kmr_02_EVS_ExitWalk_kmr_05_1, 0x80000, 7, 1, 0)
    BindTrigger(kmr_02_EVS_ExitWalk_kmr_00_0, 0x80000, 9, 1, 0)
    BindTrigger(kmr_02_EVS_ExitWalk_kmr_09_0, 0x80000, 11, 1, 0)
    BindTrigger(TTYD64_kmr_02_Script_ExitB, 0x80000, 107, 1, 0)
    Return
    End
};

EvtScript TTYD64_kmr_02_Script_EnterWalk_80244D9C = {
    Call(GetLoadType, LVar1)
    IfEq(LVar1, 1)
        Exec(EnterSavePoint)
        Exec(kmr_02_EVS_BindExitTriggers)
        Exec(kmr_02_EVS_SetupGoombaRoadGate)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    IfNe(LVar0, 0)
        Exec(kmr_02_EVS_SetupGoombaRoadGate)
    EndIf
    Switch(LVar0)
    CaseEq(2)
        Set(LVar0, Ref(kmr_02_EVS_BindExitTriggers))
        Exec(EnterWalk)
        IfEq(GameFlag(43), 0)
            Call(DisablePlayerInput, 1)
            Wait(20)
            Call(DisablePartnerAI, 0)
            Call(SpeakToPlayer, -4, 0x9D0008, 0x9D0001, 4, 0xB001C)
            Call(EnablePartnerAI)
            Set(GameFlag(43), 1)
            Call(DisablePlayerInput, 0)
        EndIf
    CaseEq(3)
        IfEq(GameFlag(1937), 0)
            Call(DisablePlayerInput, 1)
            Call(DisablePlayerPhysics, 1)
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Call(SetNpcPos, -4, LVar0, LVar1, LVar2)
            Call(SetPlayerPos, LVar0, -1000, LVar2)
            Wait(30)
            Call(PlaySound, 8334)
            Set(GameFlag(1937), 1)
            Wait(30)
            Call(SetPlayerActionState, 0)
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Call(SetNpcPos, -4, LVar0, LVar1, LVar2)
            Call(DisablePlayerPhysics, 0)
            Call(DisablePlayerInput, 0)
        EndIf
        Set(LVarA, Ref(kmr_02_EVS_BindExitTriggers))
        ExecWait(kmr_02_EVS_Pipe_EnterVertical)
    CaseEq(5)
        Exec(kmr_02_EVS_SetWallsDown_ToadHouse)
        Exec(kmr_02_EVS_BindExitTriggers)
    CaseEq(10)
        Exec(EnterPostPipe)
        Exec(kmr_02_EVS_BindExitTriggers)
    CaseEq(11)
        Exec(TTYD64_kmr_02_Script_ComeFromAttic)
    CaseDefault
        Set(LVar0, Ref(kmr_02_EVS_BindExitTriggers))
        Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_kmr_02_Script_80248910 = {
    IfEq(LVarC, 2)
        Set(LVar0, 287)
        Set(LVar1, 2)
        ExecWait(kmr_02_GiveItemReward)
        Call(TTYD64_maps_AddBadge, 287, LVar0)
    EndIf
    Return
    End
};

EvtScript TTYD64_kmr_02_Script_ComeFromAttic = {
    Exec(kmr_02_EVS_BindExitTriggers)
    Set(LVar0, 0)
    ExecWait(kmr_02_EVS_RoomListener_House)
    Set(LVar0, 0)
    ExecWait(kmr_02_EVS_SetDoorRot_House)
    Set(LVar0, 90)
    ExecWait(kmr_02_EVS_SetWallRot_House)
    Set(LVar0, 90)
    ExecWait(kmr_02_EVS_DropDoor_House)
    Set(LVar0, 0)
    Set(LVar1, 111)
    Set(LVar2, 90)
    Call(sam_11_UpdateHouseShowHide)
    Return
    End
};

EvtScript TTYD64_kmr_02_Script_ExitB = {
    SetGroup(27)
    Call(UseExitHeading, 60, 11)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "kmr_33", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_kmr_02_Script_802497F4 = {
    Call(DisablePlayerInput, 1)
    Call(kmr_02_func_80242014_8B2084)
    Call(DisablePartnerAI, 0)
    Call(SpeakToPlayer, -4, 0x9D0008, 0x9D0001, 0, 0xB001D)
    Call(SetNpcSpeed, -4, Float(3.0))
    Call(NpcMoveTo, -4, -295, -30, 0)
    Call(SetNpcAnimation, -4, 0x9D000C)
    Call(PlaySoundAtNpc, -4, 617, 0)
    Wait(15)
    Call(PlaySoundAtCollider, 21, 466, 0)
    Call(MakeLerp, 0, 120, 20, 10)
    Label(0)
    Call(UpdateLerp)
    Call(RotateModel, 167, LVar0, 0, -1, 0)
    Call(RotateModel, 169, LVar0, 0, 1, 0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    Call(ModifyColliderFlags, 0, 21, 0x7FFFFE00)
    Call(ModifyColliderFlags, 1, 22, 0x7FFFFE00)
    Call(EnablePartnerAI)
    Call(SetNpcAnimation, 1, 0x9E0002)
    Call(EnableNpcAI, 2, 0)
    Call(EnableNpcAI, 1, 0)
    Call(EnableNpcAI, 5, 0)
    Call(EnableNpcAI, 4, 0)
    Call(SetNpcPos, 2, -95, 0, -86)
    Call(SetNpcPos, 1, -92, 0, -46)
    Call(SetNpcFlagBits, 2, 256, 1)
    Call(SetNpcFlagBits, 1, 256, 1)
    Call(UseSettingsFrom, 0, -189, 0, -40)
    Call(SetPanTarget, 0, -189, 0, -40)
    Call(SetCamDistance, 0, -350)
    Call(SetCamSpeed, 0, Float(1.30078125))
    Call(PanToTarget, 0, 0, 1)
    Thread
        Call(SetNpcSpeed, 2, Float(4.0))
        Call(SetNpcAnimation, 2, 0x10003)
        Call(NpcMoveTo, 2, -109, -61, 0)
        Call(SetNpcAnimation, 2, 0x10001)
    EndThread
    Thread
        Call(SetNpcSpeed, 1, Float(4.0))
        Call(SetNpcAnimation, 1, 0x9E0008)
        Call(NpcMoveTo, 1, -142, -95, 0)
        Call(SetNpcAnimation, 1, 0x9E0002)
    EndThread
    Thread
        Call(SetPlayerSpeed, Float(3.0))
        Call(PlayerMoveTo, -238, -33, 0)
    EndThread
    Call(kmr_02_func_80242014_8B2084)
    Call(DisablePartnerAI, 0)
    Call(SetNpcSpeed, -4, Float(3.0))
    Call(SetNpcAnimation, -4, 0x9D000C)
    Call(NpcMoveTo, -4, -168, -15, 0)
    Call(SetNpcAnimation, -4, 0x9D000A)
    Call(WaitForCam, 0, Float(1.0))
    Call(SpeakToNpc, 2, 0x10008, 0x10001, 0, -4, 0xB001E)
    Wait(10)
    Call(SpeakToNpc, 1, 0x9E000C, 0x9E0002, 0, -4, 0xB001F)
    Wait(10)
    Call(SpeakToNpc, -4, 0x9D000B, 0x9D000A, 0, 2, 0xB0020)
    Wait(10)
    Call(UseSettingsFrom, 0, -79, 0, -10)
    Call(SetPanTarget, 0, -22, 0, 12)
    Call(SetCamDistance, 0, -350)
    Call(SetCamSpeed, 0, Float(0.400390625))
    Call(SetCamPitch, 0, Float(15.0), Float(-6.0))
    Call(PanToTarget, 0, 0, 1)
    Thread
        Wait(30)
        Call(SetPlayerSpeed, Float(3.0))
        Call(PlayerMoveTo, -79, -10, 0)
    EndThread
    Thread
        Wait(30)
        Call(SetNpcAnimation, 2, 0x10003)
        Call(NpcMoveTo, 2, -45, 40, 0)
        Call(SetNpcAnimation, 2, 0x10001)
    EndThread
    Thread
        Wait(30)
        Call(SetNpcAnimation, 1, 0x9E0008)
        Call(NpcMoveTo, 1, -23, -21, 0)
        Call(SetNpcAnimation, 1, 0x9E0002)
    EndThread
    Call(SetNpcAnimation, -4, 0x9D000C)
    Call(NpcMoveTo, -4, 30, 35, 0)
    Call(SetNpcAnimation, -4, 0x9D000A)
    Call(WaitForCam, 0, Float(1.0))
    Wait(20)
    Call(SpeakToPlayer, -4, 0x9D000B, 0x9D000A, 0, 0xB0021)
    Wait(10)
    Call(SetNpcSpeed, -4, Float(4.0))
    Call(SetNpcAnimation, -4, 0x9D000C)
    Call(NpcMoveTo, -4, 41, -147, 0)
    Call(SetNpcAnimation, -4, 0x9D000A)
    Call(PlaySoundAtCollider, 15, 449, 0)
    Set(LVar0, 0)
    Loop(10)
        Add(LVar0, 3)
        Call(RotateModel, 95, LVar0, 0, 1, 0)
        Wait(1)
    EndLoop
    Call(SetNpcFlagBits, -4, 64, 1)
    Call(SetNpcAnimation, -4, 0x9D000C)
    Call(NpcMoveTo, -4, 127, -157, 0)
    Call(SetNpcAnimation, -4, 0x9D0001)
    Call(SetNpcAnimation, 1, 0x9E0001)
    Loop(10)
        Add(LVar0, -3)
        Call(RotateModel, 95, LVar0, 0, 1, 0)
        Wait(1)
    EndLoop
    Call(PlaySoundAtCollider, 15, 450, 0)
    Call(NpcFacePlayer, 1, 3)
    Call(NpcFacePlayer, 2, 3)
    Call(PlayerFaceNpc, 2, 3)
    IfEq(GameFlag(30), 1)
        Thread
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
            Call(SetCamDistance, 0, Float(-350.0))
            Call(SetCamPitch, 0, Float(15.0), Float(-6.0))
            Call(SetCamSpeed, 0, Float(2.0))
            Call(PanToTarget, 0, 0, 1)
            Call(WaitForCam, 0, Float(1.0))
        EndThread
        Wait(30)
        Call(PlayerFaceNpc, 2, 1)
        Call(SpeakToPlayer, 2, 0x10008, 0x10001, 0, 0xB0022)
        Wait(10)
        Call(ShowChoice, 0x1E0011)
        Wait(10)
        Switch(LVar0)
        CaseEq(0)
            Call(CloseMessage)
            Call(TTYD64_maps_FindKeyItem, 86, LVar0)
            Call(RemoveKeyItemAt, LVar0)
            Call(PlayerFaceNpc, 1, 1)
            Call(PlayerMoveTo, -50, -24, 0)
            Call(InterpPlayerYaw, 94, 0)
            Wait(10)
            ExecWait(kmr_02_EVS_HandOverDolly)
            Call(SpeakToPlayer, 1, 0x9E000C, 0x9E0002, 0, 0xB0024)
            Wait(10)
            Call(SetNpcAnimation, 1, 0x9E0010)
            Call(InterpNpcYaw, 1, 90, 1)
            Wait(10)
            Call(InterpNpcYaw, 1, 270, 1)
            Wait(10)
            Call(SetNpcAnimation, 1, 0x9E0001)
            Call(SpeakToPlayer, 1, 0x9E000B, 0x9E0001, 0, 0xB0025)
            Wait(10)
            Set(LVar0, 348)
            Set(LVar1, 3)
            ExecWait(kmr_02_GiveItemReward)
            Call(AddStarPieces, 1)
            Call(SpeakToPlayer, 1, 0x9E000B, 0x9E0001, 0, 0xB0026)
            Wait(10)
            Exec(kmr_02_EVS_Goombaria_Kiss)
            Call(SetNpcJumpscale, 1, Float(1.0))
            Call(NpcJump0, 1, -30, 0, -19, 10)
            Wait(10)
            Call(UpdatePlayerImgFX, 0x10002, 5, 1, 1, 1, 0)
            Wait(35)
            Call(SetNpcSpeed, 1, Float(3.0))
            Call(SetNpcAnimation, 1, 0x9E0005)
            Call(NpcMoveTo, 1, -23, -21, 0)
            Call(SetNpcAnimation, 1, 0x9E0001)
            Call(NpcFacePlayer, 1, 3)
            Call(UpdatePlayerImgFX, 0x10002, 0, 0, 0, 0, 0)
            Call(PlayerMoveTo, -85, -10, 0)
            Call(PlayerFaceNpc, 1, 1)
            Wait(20)
        CaseEq(1)
            Call(ContinueSpeech, 2, 0x10008, 0x10001, 0, 0xB0023)
            Set(GameFlag(31), 1)
            Wait(10)
        EndSwitch
        Thread
            Call(AdjustCam, 0, Float(3.0), 30, Float(-275.0), Float(15.0), Float(-6.0))
            Call(WaitForCam, 0, Float(1.0))
        EndThread
        Wait(60)
    Else
        Thread
            Call(AdjustCam, 0, Float(3.0), 30, Float(-275.0), Float(15.0), Float(-6.0))
            Call(WaitForCam, 0, Float(1.0))
        EndThread
        Wait(60)
    EndIf
    Call(SpeakToPlayer, 2, 0x10008, 0x10001, 0, 0xB0027)
    Wait(10)
    Call(SpeakToPlayer, 1, 0x9E000B, 0x9E0001, 0, 0xB0028)
    Wait(10)
    Call(SpeakToPlayer, 2, 0x10008, 0x10001, 0, 0xB0029)
    Wait(10)
    Call(PlaySoundAtCollider, 15, 449, 0)
    Set(LVar0, 0)
    Loop(10)
        Add(LVar0, 3)
        Call(RotateModel, 95, LVar0, 0, 1, 0)
        Wait(1)
    EndLoop
    Call(SetPlayerAnimation, 0x10002)
    Thread
        Call(AdjustCam, 0, Float(2.0), 40, Float(-350.0), Float(15.0), Float(-7.0))
    EndThread
    Call(SetNpcPos, -4, 127, 0, -157)
    Call(SetNpcAnimation, -4, 0x9D0003)
    Call(NpcMoveTo, -4, 32, -151, 0)
    Call(SetNpcAnimation, -4, 0x9D0001)
    Call(SetNpcFlagBits, -4, 64, 0)
    Call(GetAngleBetweenNPCs, 1, -4, LVar0)
    Call(InterpNpcYaw, 1, LVar0, 0)
    Call(GetAngleBetweenNPCs, 2, -4, LVar0)
    Call(InterpNpcYaw, 2, LVar0, 0)
    Call(PlayerFaceNpc, -4, 3)
    Set(LVar0, 30)
    Loop(10)
        Add(LVar0, -3)
        Call(RotateModel, 95, LVar0, 0, 1, 0)
        Wait(1)
    EndLoop
    Call(PlaySoundAtCollider, 15, 450, 0)
    Call(SpeakToPlayer, -4, 0x9D0008, 0x9D0001, 0, 0xB002A)
    Wait(10)
    Call(SpeakToNpc, 2, 0x10008, 0x10001, 0, -4, 0xB002B)
    Wait(10)
    Call(SetNpcAnimation, -4, 0x9D0003)
    Call(NpcMoveTo, -4, 3, 9, 0)
    Call(SetNpcAnimation, -4, 0x9D0001)
    Call(SetNpcFlagBits, -4, 64, 0)
    Call(PlayerFaceNpc, -4, 3)
    Call(SpeakToPlayer, -4, 0x9D0008, 0x9D0001, 0, 0xB002C)
    Wait(10)
    Call(SetNpcAnimation, -4, 0x9D0002)
    Call(NpcMoveTo, -4, -60, -14, 0)
    Call(SetNpcAnimation, -4, 0x9D0001)
    Call(SetNpcFlagBits, -4, 64, 0)
    Wait(10)
    Set(LVar0, 289)
    Set(LVar1, 2)
    ExecWait(kmr_02_GiveItemReward)
    Call(TTYD64_maps_AddBadge, 289, LVar0)
    Call(SetNpcAnimation, -4, 0x9D0002)
    Call(NpcMoveTo, -4, 3, 9, 0)
    Call(SetNpcAnimation, -4, 0x9D0001)
    Call(SetNpcFlagBits, -4, 64, 0)
    Wait(10)
    ExecWait(TTYD64_kmr_02_Script_Goompa_TalkAboutBadges)
    Call(EnableNpcAI, 2, 0)
    Call(EnableNpcAI, 1, 0)
    Call(EnableNpcAI, 5, 0)
    Call(EnableNpcAI, 4, 0)
    Call(kmr_02_LoadHeartBlockMsgImg)
    Call(SpeakToPlayer, -4, 0x9D0008, 0x9D0001, 0, 0xB0031)
    Wait(10)
    Call(AdjustCam, 0, Float(3.0), 30, Float(-275.0), Float(15.0), Float(-6.0))
    Call(SpeakToPlayer, -4, 0x9D0008, 0x9D0001, 0, 0xB0032)
    Wait(10)
    Thread
        Call(NpcFacePlayer, 1, 3)
    EndThread
    Call(NpcFacePlayer, 2, 3)
    Call(SetPlayerAnimation, 0x10029)
    Wait(10)
    Call(SetPlayerAnimation, 0x10002)
    Wait(10)
    Call(SpeakToPlayer, 2, 0x10008, 0x10001, 0, 0xB0033)
    Wait(10)
    Thread
        Call(GetAngleBetweenNPCs, 1, -4, LVar0)
        Call(InterpNpcYaw, 1, LVar0, 3)
    EndThread
    Call(GetAngleBetweenNPCs, 2, -4, LVar0)
    Call(InterpNpcYaw, 2, LVar0, 3)
    Call(SpeakToPlayer, -4, 0x9D0008, 0x9D0001, 0, 0xB0034)
    Wait(10)
    Call(NpcFacePlayer, 2, 3)
    Call(SpeakToPlayer, 2, 0x10008, 0x10001, 0, 0xB0035)
    Wait(10)
    Call(NpcFacePlayer, 1, 3)
    Call(SpeakToPlayer, 1, 0x9E000B, 0x9E0001, 0, 0xB0036)
    Wait(10)
    Call(GetAngleBetweenNPCs, 2, -4, LVar0)
    Call(InterpNpcYaw, 2, LVar0, 3)
    Call(SpeakToNpc, -4, 0x9D0008, 0x9D0001, 0, 2, 0xB0037)
    Wait(10)
    Call(SetNpcJumpscale, 2, Float(1.2001953125))
    Call(GetNpcPos, 2, LVar0, LVar1, LVar2)
    Call(NpcJump0, 2, LVar0, LVar1, LVar2, 7)
    Call(SpeakToNpc, 2, 0x10008, 0x10001, 0, -4, 0xB0038)
    Call(kmr_02_LoadPartyImage)
    Exec(kmr_02_EVS_PushNewPartnerSong)
    Wait(10)
    Call(ShowMessageAtScreenPos, 0x1D0189, 160, 40)
    Exec(kmr_02_EVS_PopSong)
    Wait(10)
    Call(SpeakToNpc, 1, 0x9E000B, 0x9E0001, 0, 2, 0xB0039)
    Wait(10)
    Call(SpeakToPlayer, -4, 0x9D0008, 0x9D0001, 0, 0xB003A)
    Wait(10)
    Call(SetNpcSpeed, -4, Float(3.0))
    Call(SetNpcAnimation, -4, 0x9D0003)
    Call(NpcMoveTo, -4, 41, -143, 0)
    Call(SetNpcAnimation, -4, 0x9D0001)
    Call(PlaySoundAtCollider, 15, 449, 0)
    Set(LVar0, 0)
    Loop(10)
        Add(LVar0, 3)
        Call(RotateModel, 95, LVar0, 0, 1, 0)
        Wait(1)
    EndLoop
    Call(SetNpcAnimation, 5, 0x9F0003)
    Call(NpcMoveTo, 5, 127, -157, 0)
    Call(SetNpcAnimation, 5, 0x9F0001)
    Call(SetNpcFlagBits, -4, 64, 1)
    Call(SetNpcAnimation, -4, 0x9D0003)
    Call(NpcMoveTo, -4, 80, -154, 0)
    Call(NpcMoveTo, -4, 111, -200, 0)
    Call(SetNpcAnimation, -4, 0x9D0001)
    Loop(10)
        Add(LVar0, -3)
        Call(RotateModel, 95, LVar0, 0, 1, 0)
        Wait(1)
    EndLoop
    Call(PlaySoundAtCollider, 15, 450, 0)
    Call(kmr_02_RemoveGoompaPartner)
    Call(kmr_02_IsPlayerHPFull)
    IfEq(LVar0, 1)
        Call(SpeakToPlayer, 2, 0x10008, 0x10001, 0, 0xB003B)
    Else
        Call(SpeakToPlayer, 2, 0x10008, 0x10001, 0, 0xB003C)
    EndIf
    Call(kmr_02_ChangeNpcToPartner, 2, 1)
    Wait(10)
    Call(SetNpcPos, 2, 0, -1000, 0)
    Call(SetNpcFlagBits, 2, 512, 0)
    Call(SetNpcPos, 5, 115, 0, -309)
    Call(SetNpcFlagBits, 5, 64, 0)
    Call(SetNpcFlagBits, 0, 512, 1)
    Call(SetNpcFlagBits, 0, 8, 0)
    Call(SetNpcPos, 0, 184, 0, -149)
    Call(EnableNpcShadow, 0, 1)
    Call(SetNpcPos, -1, 200, 0, 100)
    Call(RestartNpcAI, 1)
    Call(EnableNpcAI, 5, 1)
    Call(EnableNpcAI, 4, 1)
    Thread
        Call(ResetCam, 0, Float(4.0))
    EndThread
    Call(SetNpcFlagBits, 1, 256, 0)
    Call(EnablePartnerAI)
    Call(DisablePlayerInput, 0)
    Set(GameByte(0), -115)
    Unbind
    Call(SetNpcFlagBits, 4, 4, 0)
    Return
    End
};

EvtScript TTYD64_kmr_02_Script_Goompa_TalkAboutBadges = {
    Call(SpeakToPlayer, -4, 0x9D0008, 0x9D0001, 0, 0xB002D)
    Call(ShowChoice, 0x1E0013)
    IfEq(LVar0, 1)
        Call(ContinueSpeech, -4, 0x9D0008, 0x9D0001, 0, 0xB002E)
        Call(ShowChoice, 0x1E0013)
        IfEq(LVar0, 1)
            Call(ContinueSpeech, -4, 0x9D0008, 0x9D0001, 0, 0xB002F)
            Return
        EndIf
    EndIf
    Call(TTYD64_SetFFWDSuppressed, 1)
    Call(ContinueSpeech, -4, 0x9D0008, 0x9D0001, 0, 0xB0030)
    Wait(10)
    Call(kmr_02_WaitForStartInput)
    Call(EndSpeech, -4, 0x9D0008, 0x9D0001, 0)
    Wait(10)
    Set(GameFlag(94), 1)
    Call(kmr_02_OpenPauseMenu)
    Call(kmr_02_CloseStatusBar)
    Set(GameFlag(94), 0)
    Call(TTYD64_ResetFFWD)
    Return
    End
};

EntryList TTYD64_kmr_02_EntryList = {
    { 391.0f, 0.0f, 286.0f, 315.0f },
    { -371.0f, 0.0f, 304.0f, 45.0f },
    { -473.0f, 0.0f, 4.0f, 90.0f },
    { 0.0f, 35.0f, 355.0f, 180.0f },
    { 60.0f, 0.0f, 10.0f, 0.0f },
    { -230.0f, 36.0f, -332.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 200.0f, 50.0f, 70.0f, 90.0f },
    { 236.0f, 74.0f, -395.0f, 120.0f },
};
// clang-format on

void TTYD64_InstallMap_kmr_02(void) {
    kmr_02_settings.entryList = &TTYD64_kmr_02_EntryList;
    kmr_02_settings.entryCount = 12;
    Mod_ReplaceScript("TTYD64", &kmr_02_EVS_BindExitTriggers, &TTYD64_kmr_02_Script_80244D38);
    Mod_ReplaceScript("TTYD64", &kmr_02_EVS_EnterMap, &TTYD64_kmr_02_Script_EnterWalk_80244D9C);
    Mod_ReplaceScript("TTYD64", &kmr_02_EVS_LetterReward_Goompapa, &TTYD64_kmr_02_Script_80248910);
    Mod_ReplaceScript("TTYD64", &kmr_02_EVS_ReturnToVillage, &TTYD64_kmr_02_Script_802497F4);
}
