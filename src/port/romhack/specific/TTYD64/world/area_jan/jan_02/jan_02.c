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

extern NpcGroupList jan_02_DefaultNPCs;
extern EvtScript jan_02_EVS_BindExitTriggers;
extern EvtScript jan_02_EVS_ExitWalk_jan_01_1;
extern EvtScript jan_02_EVS_ExitWalk_jan_03_0;
extern EvtScript jan_02_EVS_Main;
extern EvtScript jan_02_EVS_MakeEntities;
extern EvtScript jan_02_EVS_NpcInteract_VillageLeader;
extern EvtScript jan_02_EVS_SetupFoliage;
extern EvtScript jan_02_EVS_SetupMusic;
extern EvtScript jan_02_EVS_UpdateTexturePan;
extern EvtScript jan_02_GiveItemReward;
extern MapSettings jan_02_settings;

API_CALLABLE(ContinueSpeech);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(EnableTexPanning);
API_CALLABLE(GetCurrentPartnerID);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(InterpNpcYaw);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(NpcMoveTo);
API_CALLABLE(PanToTarget);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtPlayer);
API_CALLABLE(PlayerFaceNpc);
API_CALLABLE(PlayerJump);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(ResetCam);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamDistance);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamPitch);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowEmote);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(StopSound);
API_CALLABLE(TranslateGroup);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(WaitForCam);
API_CALLABLE(func_802D2C14);
API_CALLABLE(jan_02_ManageBigPalmTreeVisibility);
API_CALLABLE(jan_02_SwitchToPartner);

extern EvtScript TTYD64_jan_02_Script_Main_EnterWalk;
extern EvtScript TTYD64_jan_02_Script_MoveStatue;
extern EvtScript TTYD64_jan_02_Script_CreateExitTriggers;
extern EntryList TTYD64_jan_02_EntryList;
extern EvtScript TTYD64_jan_02_Script_MoveStatue_InitLeft;
extern EvtScript TTYD64_jan_02_Script_Interact_80245ECC;
extern EvtScript TTYD64_jan_02_Script_Cutscene_GiveJadeRaven;
extern EvtScript TTYD64_jan_02_Script_TrackEntry;
extern EvtScript TTYD64_jan_02_Script_InitExit2;
extern EvtScript TTYD64_jan_02_Script_Exit2;
extern EvtScript TTYD64_jan_02_Script_MoveStatue_InitRight;

// clang-format off
EvtScript TTYD64_jan_02_Script_Main_EnterWalk = {
    Set(GameByte(425), 37)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Set(GameFlag(1982), 1)
    Set(AreaFlag(4), 0)
    Set(AreaFlag(5), 0)
    Call(MakeNpcs, 0, Ref(jan_02_DefaultNPCs))
    ExecWait(jan_02_EVS_MakeEntities)
    Exec(jan_02_EVS_SetupFoliage)
    Call(ModifyColliderFlags, 0, 1, 0x7FFFFE00)
    Call(ModifyColliderFlags, 0, 5, 0x7FFFFE00)
    Set(LVar0, Ref(jan_02_EVS_BindExitTriggers))
    Exec(TTYD64_jan_02_Script_TrackEntry)
    Exec(TTYD64_jan_02_Script_InitExit2)
    Call(PlaySound, 0x80000017)
    Call(EnableTexPanning, 62, 1)
    Call(EnableTexPanning, 61, 1)
    Call(EnableTexPanning, 63, 1)
    Thread
        Set(LVar0, 1)
        Set(LVar1, 0)
        Set(LVar2, 400)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 0)
        Set(LVar6, 1)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(jan_02_EVS_UpdateTexturePan)
    EndThread
    Thread
        Set(LVar0, 2)
        Set(LVar1, -100)
        Set(LVar2, 200)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(jan_02_EVS_UpdateTexturePan)
    EndThread
    Thread
        Call(jan_02_ManageBigPalmTreeVisibility)
    EndThread
    Call(ModifyColliderFlags, 3, 24, 1)
    Call(ModifyColliderFlags, 3, 25, 1)
    Return
    End
};

EvtScript TTYD64_jan_02_Script_MoveStatue = {
    Thread
        Call(ShakeCam, 0, 0, 100, Float(0.599609375))
    EndThread
    Thread
        Call(GetModelCenter, 17)
        Call(UseSettingsFrom, 0, LVar0, 0, LVar2)
        Call(GetPlayerPos, 0, LVar1, 0)
        Call(SetCamSpeed, 0, Float(3.0))
        Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
        Call(PanToTarget, 0, 0, 1)
    EndThread
    Set(LVar3, LVar0)
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(PlaySound, 0x80000010)
    Set(LVar0, 70)
    Mul(LVar0, LVar3)
    Call(MakeLerp, 0, LVar0, 100, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, 25, LVar0, 0, 0)
        Call(UpdateColliderTransform, 33)
        Call(UpdateColliderTransform, 71)
        Call(UpdateColliderTransform, 70)
        Set(LVar4, LVar1)
        Set(LVar7, 0)
        Call(GetModelCenter, 134)
        Call(GetPlayerPos, LVar1, 0, 0)
        IfEq(LVar3, 1)
            IfLe(LVar1, LVar0)
                Set(LVar7, 1)
            EndIf
        Else
            IfGe(LVar1, LVar0)
                Set(LVar7, 1)
            EndIf
        EndIf
        IfEq(LVar7, 1)
            Call(GetModelCenter, 17)
            Set(LVar5, -37)
            Mul(LVar5, LVar3)
            Add(LVar0, LVar5)
            Call(GetPlayerPos, 0, LVar1, LVar2)
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
        EndIf
        Call(SetPlayerActionState, 20)
        Wait(1)
        IfEq(LVar4, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(StopSound, 0x80000010)
    Wait(10)
    IfEq(LVar3, 1)
        Set(GameByte(4325), 1)
    Else
        Set(GameByte(4325), 2)
    EndIf
    Call(SetPlayerAnimation, 0x10002)
    Call(SetPlayerAnimation, 0x80016)
    Call(PlaySoundAtPlayer, 610, 0)
    Call(ShowEmote, 0, 0, -45, 20, 0, 0, 0, 0, 0)
    Wait(20)
    Call(SetPlayerAnimation, 0x10002)
    Call(SetPlayerAnimation, 0x80017)
    Wait(20)
    Call(SetPlayerAnimation, 0x10002)
    Call(SetPlayerAnimation, 0x80018)
    Wait(10)
    Call(SetPlayerAnimation, 0x10002)
    Call(SetPlayerAnimation, 0x80019)
    Call(PlaySound, 353)
    Loop(10)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Sub(LVar1, 10)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Call(GotoMap, (Bytecode) "jan_24", 0)
    Wait(200)
    Call(StopSound, 353)
    Return
    End
};

EvtScript TTYD64_jan_02_Script_CreateExitTriggers = {
    BindTrigger(jan_02_EVS_ExitWalk_jan_01_1, 0x80000, 0, 1, 0)
    BindTrigger(jan_02_EVS_ExitWalk_jan_03_0, 0x80000, 4, 1, 0)
    BindTrigger(TTYD64_jan_02_Script_Exit2, 128, 73, 1, 0)
    Return
    End
};

EntryList TTYD64_jan_02_EntryList = {
    { -450.0f, 0.0f, -450.0f, 135.0f },
    { 640.0f, 0.0f, 0.0f, 270.0f },
    { 26.0f, -13.0f, -201.0f, 90.0f },
};

EvtScript TTYD64_jan_02_Script_MoveStatue_InitLeft = {
    Set(LVar0, 1)
    ExecWait(TTYD64_jan_02_Script_MoveStatue)
    Return
    End
};

EvtScript TTYD64_jan_02_Script_Interact_80245ECC = {
    Switch(GameByte(0))
    CaseLt(14)
        IfEq(GameFlag(1223), 0)
            Call(SpeakToPlayer, -1, 0xC2000B, 0xC20005, 0, 0x100021)
            Set(GameFlag(1223), 1)
        Else
            Call(SpeakToPlayer, -1, 0xC2000B, 0xC20005, 0, 0x100022)
        EndIf
    CaseLt(16)
    CaseLt(17)
        ExecWait(TTYD64_jan_02_Script_Cutscene_GiveJadeRaven)
    CaseLt(21)
        Call(SpeakToPlayer, -1, 0xC20009, 0xC20003, 0, 0x10002D)
    CaseLt(24)
        IfEq(AreaFlag(4), 0)
            Call(SpeakToPlayer, -1, 0xC2000B, 0xC20005, 0, 0x10002E)
            Set(AreaFlag(4), 1)
        Else
            Call(SpeakToPlayer, -1, 0xC2000B, 0xC20005, 0, 0x10002F)
        EndIf
    CaseLt(25)
        Call(SpeakToPlayer, -1, 0xC2000B, 0xC20005, 0, 0x100030)
    CaseLt(39)
        Call(SpeakToPlayer, -1, 0xC2000B, 0xC20005, 0, 0x100031)
    CaseLt(42)
        Call(SpeakToPlayer, -1, 0xC2000B, 0xC20005, 0, 0x100032)
    CaseDefault
        Call(SpeakToPlayer, -1, 0xC2000B, 0xC20005, 0, 0x100033)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_jan_02_Script_Cutscene_GiveJadeRaven = {
    Call(SetNpcFlagBits, -4, 64, 1)
    IfEq(GameFlag(1223), 1)
        Call(SpeakToPlayer, -1, 0xC20009, 0xC20003, 0, 0x100023)
    Else
        Call(SpeakToPlayer, -1, 0xC20009, 0xC20003, 0, 0x100024)
    EndIf
    Wait(5)
    Call(SetNpcFlagBits, -1, 256, 1)
    Call(SetNpcAnimation, -1, 0xC20006)
    IfEq(GameByte(4325), 0)
        Call(NpcMoveTo, -1, 8, -140, 25)
    Else
        IfEq(GameByte(4325), 1)
            Call(NpcMoveTo, -1, 68, -140, 25)
        Else
            Call(NpcMoveTo, -1, -48, -140, 25)
        EndIf
    EndIf
    Call(SetNpcFlagBits, -1, 256, 0)
    Call(SetNpcAnimation, -1, 0xC20003)
    Wait(5)
    Call(UseSettingsFrom, 0, 25, 15, -150)
    Call(SetPanTarget, 0, 25, 15, -150)
    Call(SetCamDistance, 0, Float(300.0))
    Call(SetCamPitch, 0, Float(16.0), Float(-8.0))
    Call(SetCamSpeed, 0, Float(4.0))
    Call(PanToTarget, 0, 0, 1)
    Wait(5)
    IfEq(GameByte(4325), 0)
        Call(PlayerMoveTo, 58, -140, 25)
    Else
        IfEq(GameByte(4325), 1)
            Call(PlayerMoveTo, 118, -140, 25)
        Else
            Call(PlayerMoveTo, 8, -140, 25)
        EndIf
    EndIf
    Call(PlayerFaceNpc, -1, 0)
    Call(func_802D2C14, 1)
    Call(SetNpcFlagBits, -4, 256, 1)
    Wait(30)
    Call(SetNpcAnimation, -1, 0xC2000E)
    Wait(30)
    Call(SpeakToPlayer, -1, 0xC2000E, 0xC2000E, 5, 0x100025)
    Wait(60)
    Call(SetNpcAnimation, -1, 0xC20003)
    Call(SpeakToPlayer, -1, 0xC20009, 0xC20003, 0, 0x100026)
    Set(LVar0, 42)
    Set(LVar1, 1)
    ExecWait(jan_02_GiveItemReward)
    Call(TTYD64_maps_AddKeyItem, 42)
    Call(SpeakToPlayer, -1, 0xC20009, 0xC20003, 0, 0x100027)
    Set(GameByte(0), 17)
    Wait(15)
    Call(GetPlayerPos, LVar3, LVar4, LVar5)
    Add(LVar3, 25)
    Call(SetPanTarget, 0, LVar3, LVar4, LVar5)
    Call(SetCamSpeed, 0, Float(2.5))
    Call(PanToTarget, 0, 0, 1)
    Call(WaitForCam, 0, Float(1.0))
    Call(SetNpcFlagBits, -4, 64, 0)
    Call(func_802D2C14, 0)
    Call(GetCurrentPartnerID, LVar0)
    IfEq(LVar0, 7)
        Thread
            Wait(15)
            Call(PlayerFaceNpc, -4, 0)
        EndThread
        Call(DisablePartnerAI, 0)
        Call(SpeakToPlayer, -4, 0x70004, 0x70001, 2, 0x100028)
    Else
        Call(jan_02_SwitchToPartner, 7)
        Call(SpeakToPlayer, -4, -1, -1, 5, 0x100029)
        Call(SetNpcFlagBits, -4, 256, 1)
        Wait(15)
        Call(GetNpcPos, -4, LVar2, LVar3, LVar4)
        Call(MakeLerp, LVar2, 85, 10, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(SetNpcPos, -4, LVar0, LVar3, LVar4)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(InterpNpcYaw, -4, 270, 0)
        Wait(10)
        Thread
            Wait(10)
            Call(PlayerFaceNpc, -4, 0)
        EndThread
        Call(DisablePartnerAI, 0)
        Call(ContinueSpeech, -4, 0x70004, 0x70001, 5, 0x10002A)
        Wait(10)
    EndIf
    Call(ContinueSpeech, -4, 0x70004, 0x70001, 5, 0x10002B)
    Call(SetPlayerAnimation, 0x80007)
    Wait(30)
    Call(SpeakToPlayer, -4, 0x70004, 0x70001, 5, 0x10002C)
    Wait(10)
    Call(EnablePartnerAI)
    Call(ResetCam, 0, Float(2.0))
    Return
    End
};

EvtScript TTYD64_jan_02_Script_TrackEntry = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 2)
        Call(DisablePlayerInput, 1)
        Call(DisablePlayerPhysics, 1)
        Call(ResetCam, 0, 30)
        Call(DisablePlayerPhysics, 0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        IfEq(GameByte(4325), 1)
            Sub(LVar0, 47)
        Else
            Add(LVar0, 47)
        EndIf
        Add(LVar1, 23)
        Add(LVar2, 28)
        Call(PlayerJump, LVar0, LVar1, LVar2, 20)
        Call(DisablePlayerInput, 0)
        Exec(TTYD64_jan_02_Script_CreateExitTriggers)
    Else
        Set(LVar0, Ref(TTYD64_jan_02_Script_CreateExitTriggers))
        Exec(EnterWalk)
    EndIf
    Return
    End
};

EvtScript TTYD64_jan_02_Script_InitExit2 = {
    Call(ParentColliderToModel, 33, 18)
    Call(ParentColliderToModel, 71, 18)
    Call(ParentColliderToModel, 70, 18)
    IfEq(GameByte(4325), 0)
        BindTrigger(TTYD64_jan_02_Script_MoveStatue_InitLeft, 64, 71, 1, 0)
        BindTrigger(TTYD64_jan_02_Script_MoveStatue_InitRight, 64, 70, 1, 0)
    Else
        IfEq(GameByte(4325), 1)
            Call(TranslateGroup, 25, 70, 0, 0)
        Else
            Call(TranslateGroup, 25, -70, 0, 0)
        EndIf
        Call(UpdateColliderTransform, 33)
        Call(UpdateColliderTransform, 71)
        Call(UpdateColliderTransform, 70)
    EndIf
    Exec(jan_02_EVS_SetupMusic)
    Return
    End
};

EvtScript TTYD64_jan_02_Script_Exit2 = {
    Call(DisablePlayerInput, 1)
    Call(GotoMap, (Bytecode) "jan_24", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_jan_02_Script_MoveStatue_InitRight = {
    Set(LVar0, -1)
    ExecWait(TTYD64_jan_02_Script_MoveStatue)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_jan_02(void) {
    jan_02_settings.entryList = &TTYD64_jan_02_EntryList;
    jan_02_settings.entryCount = 3;
    Mod_ReplaceScript("TTYD64", &jan_02_EVS_Main, &TTYD64_jan_02_Script_Main_EnterWalk);
    Mod_ReplaceScript("TTYD64", &jan_02_EVS_NpcInteract_VillageLeader, &TTYD64_jan_02_Script_Interact_80245ECC);
}
