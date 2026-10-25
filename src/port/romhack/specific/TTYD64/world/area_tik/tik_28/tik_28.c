#include "common.h"
#include "effects.h"
#include "entity.h"
#include "map.h"
#include "npc.h"
#include "script_api/map.h"
#include <stdio.h>
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/world/newmaps.h"

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableModel);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GetCurrentPartnerID);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetPartnerInUse);
API_CALLABLE(GetPlayerActionState);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(HidePlayerShadow);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(InterruptUsePartner);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerJump);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(ScaleGroup);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamTarget);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerFlagBits);
API_CALLABLE(SetPlayerImgFXFlags);
API_CALLABLE(SetPlayerJumpscale);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetTexPanner);
API_CALLABLE(StopSound);
API_CALLABLE(TeleportPartnerToPlayer);
API_CALLABLE(TranslateGroup);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UpdatePlayerImgFX);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_tik_28_Script_MarioDrowned;
extern EvtScript TTYD64_tik_28_Script_SetupTexturePan;
extern EvtScript TTYD64_tik_28_Script_EnterVerticalPipe;
extern EvtScript TTYD64_tik_28_Script_ExitVerticalPipe;
extern EvtScript TTYD64_tik_28_Script_Water_Start;
extern EvtScript TTYD64_tik_28_Script_Water_Stop;
extern EvtScript TTYD64_tik_28_Script_UpdateWaterLevel;
extern EvtScript TTYD64_tik_28_Script_EnterMap;
extern EvtScript TTYD64_tik_28_Script_MakeEntities;
extern EvtScript TTYD64_tik_28_Script_HidePipe;
extern EvtScript TTYD64_tik_28_Script_ScriptedSpring_Entity_Spring2;
extern EvtScript TTYD64_tik_28_Script_ScriptedSpring_Entity_Spring1;
extern EvtScript TTYD64_tik_28_Script_ScriptedSpring_Entity_Spring4;
extern EvtScript TTYD64_tik_28_Script_ScriptedSpring_Entity_Spring3;
extern EvtScript TTYD64_tik_28_Script_Main;
extern u8 TTYD64_tik_28_String_Tattle[];
extern EvtScript TTYD64_tik_28_Script_TexturePan_Update;
extern EvtScript TTYD64_tik_28_Script_Exit1;
extern EvtScript TTYD64_tik_28_Script_ScriptedSpring_FollowCam;
extern EvtScript TTYD64_tik_28_Script_Exit0;
extern EvtScript TTYD64_tik_28_Script_CreateExitTriggers;
extern MapSettings TTYD64_tik_28_Header;
extern EvtScript TTYD64_tik_28_Script_Entity_Shine1;
extern EvtScript TTYD64_tik_28_Script_SetupMusic;
extern EntryList TTYD64_tik_28_EntryList;
extern EvtScript TTYD64_tik_28_Script_GoToMapPipe;
extern EvtScript TTYD64_tik_28_Script_UpdateRespawnPoint_1;
extern EvtScript TTYD64_tik_28_Script_UpdateRespawnPoint_2;

// clang-format off
static s32 TTYD64_tik_28_GetTattleMsg;

static s32 TTYD64_tik_28_GetTattle(void) {
    return TTYD64_tik_28_GetTattleMsg;
}

EvtScript TTYD64_tik_28_Script_MarioDrowned = {
    Call(PlaySound, 8419)
    IfEq(LVarA, 8)
        Call(TTYD64_SetPartnerAbilityState, PARTNER_LAKILESTER, 3)
    Else
        Call(DisablePlayerInput, 1)
        Loop(0)
            Call(GetPlayerActionState, LVar0)
            IfEq(LVar0, 0)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Call(DisablePlayerPhysics, 1)
        Thread
            Loop(5)
                Call(GetPlayerPos, LVar0, LVar1, LVar2)
                Sub(LVar1, 1)
                Call(SetPlayerPos, LVar0, LVar1, LVar2)
                Wait(1)
            EndLoop
        EndThread
        Call(SetPlayerAnimation, 0x10002)
        Call(SetPlayerAnimation, 0x1001B)
    EndIf
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(255.0))
    ExecWait(TTYD64_Script_FadeScreenOut)
    IfNe(LVarA, 8)
        Call(DisablePlayerPhysics, 0)
    EndIf
    Switch(MapVar(0))
    CaseEq(0)
        Call(SetPlayerPos, -160, 0, 51)
    CaseEq(1)
        Call(SetPlayerPos, 717, 0, 174)
    EndSwitch
    Switch(LVarA)
    CaseOrEq(9)
    CaseOrEq(6)
        Call(TTYD64_SetPlayerAnimFlagBits, PA_FLAG_INTERRUPT_USE_PARTNER, 1)
        EndCaseGroup
    EndSwitch
    Call(TeleportPartnerToPlayer)
    Call(InterpPlayerYaw, 90, 0)
    Wait(5)
    IfNe(LVarA, 8)
        Call(SetPlayerAnimation, 0x10002)
        Call(SetPlayerAnimation, 0x1000F)
    EndIf
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(5.0))
    Exec(TTYD64_Script_FadeScreenIn)
    Wait(10)
    IfEq(LVarA, 8)
        Return
    Else
        Call(SetPlayerAnimation, 0x10030)
        Wait(15)
        Call(SetPlayerAnimation, 0x10031)
        Thread
            Call(PlaySound, 370)
            Wait(12)
            Call(PlaySound, 370)
        EndThread
        Wait(25)
        Call(SetPlayerAnimation, 0x10002)
        Call(DisablePlayerInput, 0)
    EndIf
    Return
    End
};

EvtScript TTYD64_tik_28_Script_SetupTexturePan = {
    Call(SetTexPanner, 63, 0)
    Call(SetTexPanner, 66, 2)
    Call(SetTexPanner, 50, 1)
    Call(SetTexPanner, 53, 1)
    Call(SetTexPanner, 56, 1)
    Call(SetTexPanner, 59, 1)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 70)
        Set(LVar2, 100)
        Set(LVar3, 100)
        Set(LVar4, 130)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_tik_28_Script_TexturePan_Update)
    EndThread
    Thread
        Set(LVar0, 1)
        Set(LVar1, -50)
        Set(LVar2, -900)
        Set(LVar3, -70)
        Set(LVar4, -1200)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_tik_28_Script_TexturePan_Update)
    EndThread
    Thread
        Set(LVar0, 2)
        Set(LVar1, 0)
        Set(LVar2, -1400)
        Set(LVar3, -2600)
        Set(LVar4, -60)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_tik_28_Script_TexturePan_Update)
    EndThread
    Return
    End
};

EvtScript TTYD64_tik_28_Script_EnterVerticalPipe = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(DisablePartnerAI, 0)
    Call(HidePlayerShadow, 1)
    Call(SetPlayerAnimation, 0x10000)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Call(EnableNpcShadow, -4, 0)
        Call(SetNpcPos, -4, 0, -1000, 0)
    EndIf
    Call(GetEntryID, LVar0)
    Call(TTYD64_Pipe_GetEntryCoords)
    Sub(LVar2, 40)
    Call(SetPlayerPos, LVar1, LVar2, LVar3)
    Call(InterpPlayerYaw, LVar4, 0)
    Call(PlaySound, 355)
    Call(SetPlayerImgFXFlags, 256)
    Call(UpdatePlayerImgFX, 0x10000, 5, 2, 1, 1, 0)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Loop(40)
        Add(LVar1, 1)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Wait(3)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Thread
            Call(DisablePartnerAI, 0)
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Sub(LVar2, 3)
            Call(SetNpcPos, -4, LVar0, LVar1, LVar2)
            Call(SetNpcFlagBits, -4, 2, 0)
            Call(EnablePartnerAI)
            Call(EnableNpcShadow, -4, 1)
        EndThread
    EndIf
    Wait(2)
    Call(UpdatePlayerImgFX, 0x10000, 0, 0, 0, 0, 0)
    Wait(1)
    Call(SetPlayerAnimation, 0x10002)
    ExecWait(TTYD64_tik_28_Script_HidePipe)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Call(HidePlayerShadow, 0)
    Exec(LVarA)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_ExitVerticalPipe = {
    Call(TTYD64_Pipe_CheckDownInput)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(GetPartnerInUse, LVar0)
    IfNe(LVar0, 0)
        Call(GetCurrentPartnerID, LVar1)
        IfNe(LVar1, 6)
            Return
        Else
            Call(InterruptUsePartner)
            Call(DisablePlayerInput, 1)
        EndIf
    Else
        Call(DisablePlayerInput, 1)
    EndIf
    SetGroup(27)
    Call(TTYD64_Pipe_SetAnimFlag)
    Call(DisablePlayerPhysics, 1)
    Call(HidePlayerShadow, 1)
    Set(LVar0, LVarA)
    Call(TTYD64_Pipe_GetEntryCoords)
    Call(PlayerMoveTo, LVar1, LVar3, 3)
    Set(LVar0, LVarA)
    Call(TTYD64_Pipe_GetEntryCoords)
    Call(SetPlayerPos, LVar1, LVar2, LVar3)
    Call(SetPlayerFlagBits, 0x200000, 1)
    Call(TTYD64_Pipe_GetCameraYaw)
    Call(InterpPlayerYaw, LVar0, 0)
    Wait(2)
    Call(SetPlayerFlagBits, 0x200000, 0)
    Call(PlaySound, 355)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Thread
        Wait(4)
        Loop(40)
            Sub(LVar1, 1)
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Call(SetPlayerImgFXFlags, 2048)
    Call(UpdatePlayerImgFX, 0x10002, 5, 2, 1, 1, 0)
    Wait(25)
    ExecWait(LVarC)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_Water_Start = {
    Call(PlaySound, 33)
    Call(ModifyColliderFlags, 1, 25, 0x7FFFFE00)
    Call(EnableGroup, 52, 1)
    Call(EnableGroup, 55, 1)
    Call(EnableGroup, 58, 1)
    Call(EnableGroup, 61, 1)
    Call(ScaleGroup, 52, 0, Float(1.0), Float(1.0))
    Call(ScaleGroup, 55, 0, Float(1.0), Float(1.0))
    Call(ScaleGroup, 58, 0, Float(1.0), Float(1.0))
    Call(ScaleGroup, 61, 0, Float(1.0), Float(1.0))
    SetF(LVar0, Float(0.0))
    Thread
        Loop(20)
            AddF(LVar0, Float(0.0498046875))
            Call(ScaleGroup, 52, LVar0, Float(1.0), Float(1.0))
            Call(ScaleGroup, 55, LVar0, Float(1.0), Float(1.0))
            Call(ScaleGroup, 58, LVar0, Float(1.0), Float(1.0))
            Call(ScaleGroup, 61, LVar0, Float(1.0), Float(1.0))
            Wait(1)
        EndLoop
        Call(ScaleGroup, 52, Float(1.0), Float(1.0), Float(1.0))
        Call(ScaleGroup, 55, Float(1.0), Float(1.0), Float(1.0))
        Call(ScaleGroup, 58, Float(1.0), Float(1.0), Float(1.0))
        Call(ScaleGroup, 61, Float(1.0), Float(1.0), Float(1.0))
    EndThread
    Wait(8)
    Set(LVar0, 66)
    Set(LVar1, 15)
    Set(LVar2, 0)
    Set(LVar3, 63)
    ExecWait(TTYD64_Script_AdvancedUpdateModelAlpha)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_Water_Stop = {
    Call(StopSound, 33)
    Call(ModifyColliderFlags, 0, 25, 0x7FFFFE00)
    SetF(LVar0, Float(1.0))
    Thread
        Loop(20)
            SubF(LVar0, Float(0.0498046875))
            Call(ScaleGroup, 52, LVar0, Float(1.0), Float(1.0))
            Call(ScaleGroup, 55, LVar0, Float(1.0), Float(1.0))
            Call(ScaleGroup, 58, LVar0, Float(1.0), Float(1.0))
            Call(ScaleGroup, 61, LVar0, Float(1.0), Float(1.0))
            Wait(1)
        EndLoop
        Call(ScaleGroup, 52, 0, Float(1.0), Float(1.0))
        Call(ScaleGroup, 55, 0, Float(1.0), Float(1.0))
        Call(ScaleGroup, 58, 0, Float(1.0), Float(1.0))
        Call(ScaleGroup, 61, 0, Float(1.0), Float(1.0))
        Call(EnableGroup, 52, 0)
        Call(EnableGroup, 55, 0)
        Call(EnableGroup, 58, 0)
        Call(EnableGroup, 61, 0)
    EndThread
    Wait(8)
    Set(LVar0, 66)
    Set(LVar1, 15)
    Set(LVar2, 63)
    Set(LVar3, 0)
    ExecWait(TTYD64_Script_AdvancedUpdateModelAlpha)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_UpdateWaterLevel = {
    Loop(0)
        IfEq(MapVar(1), 0)
            Wait(50)
            Exec(TTYD64_tik_28_Script_Water_Start)
            Call(MakeLerp, -180, 0, 300, 0)
            Loop(0)
                Call(UpdateLerp)
                Call(TranslateGroup, 67, 0, LVar0, 0)
                Call(UpdateColliderTransform, 19)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
            Exec(TTYD64_tik_28_Script_Water_Stop)
            Set(MapVar(1), 1)
        Else
            Wait(100)
            Call(PlaySound, 66)
            Call(MakeLerp, 0, -180, 200, 0)
            Loop(0)
                Call(UpdateLerp)
                Call(TranslateGroup, 67, 0, LVar0, 0)
                Call(UpdateColliderTransform, 19)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
            Set(MapVar(1), 0)
        EndIf
    EndLoop
    Return
    End
};

EvtScript TTYD64_tik_28_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 0)
        Set(LVar0, (Bytecode) TTYD64_tik_28_Script_CreateExitTriggers)
        Exec(EnterWalk)
        Call(EnableModel, 47, 0)
    Else
        Set(LVarA, (Bytecode) TTYD64_tik_28_Script_CreateExitTriggers)
        Exec(TTYD64_tik_28_Script_EnterVerticalPipe)
    EndIf
    BindTrigger(TTYD64_tik_28_Script_UpdateRespawnPoint_1, 128, 2, 1, 0)
    BindTrigger(TTYD64_tik_28_Script_UpdateRespawnPoint_2, 128, 14, 1, 0)
    BindTrigger(TTYD64_tik_28_Script_MarioDrowned, 128, 19, 1, 0)
    Call(MakeItemEntity, 385, 849, 0, 6, 17, GameFlag(4548))
    Call(ParentColliderToModel, 19, 63)
    Call(TranslateGroup, 67, 0, -180, 0)
    Call(UpdateColliderTransform, 19)
    Call(EnableGroup, 52, 0)
    Call(EnableGroup, 55, 0)
    Call(EnableGroup, 58, 0)
    Call(EnableGroup, 61, 0)
    Call(ModifyColliderFlags, 0, 25, 0x7FFFFE00)
    Exec(TTYD64_tik_28_Script_UpdateWaterLevel)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_ScriptSpring), -3, -185, -113, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_tik_28_Script_ScriptedSpring_Entity_Spring1)
    Call(MakeEntity, Ref(Entity_ScriptSpring), 236, -185, 168, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_tik_28_Script_ScriptedSpring_Entity_Spring2)
    Call(MakeEntity, Ref(Entity_ScriptSpring), 512, -185, -124, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_tik_28_Script_ScriptedSpring_Entity_Spring3)
    Call(MakeEntity, Ref(Entity_ScriptSpring), 666, -185, 175, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_tik_28_Script_ScriptedSpring_Entity_Spring4)
    Call(MakeEntity, Ref(Entity_SuperBlock), 347, 55, 170, 0, 0x80000000)
    Set(MapVar(2), LVar0)
    Call(AssignBlockFlag, GameFlag(4550))
    Call(AssignScript, (Bytecode) TTYD64_tik_28_Script_Entity_Shine1)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_HidePipe = {
    ExecGetTID(TTYD64_tik_28_Script_ScriptedSpring_FollowCam, LVar8)
    Call(SetPlayerJumpscale, Float(0.2998046875))
    Call(PlayerJump, -172, 0, -65, 30)
    KillThread(LVar8)
    Call(PlaySound, 355)
    Call(MakeLerp, 0, -50, 30, 10)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateModel, 47, 0, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript TTYD64_tik_28_Script_ScriptedSpring_Entity_Spring2 = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerActionState, 6)
    Wait(1)
    ExecGetTID(TTYD64_tik_28_Script_ScriptedSpring_FollowCam, LVarA)
    Call(SetPlayerJumpscale, Float(0.7001953125))
    Call(PlayerJump, 298, 0, 169, 30)
    KillThread(LVarA)
    Call(SetPlayerActionState, 0)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_ScriptedSpring_Entity_Spring1 = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerActionState, 6)
    Wait(1)
    ExecGetTID(TTYD64_tik_28_Script_ScriptedSpring_FollowCam, LVarA)
    Call(SetPlayerJumpscale, Float(0.7001953125))
    Call(PlayerJump, 52, 0, -123, 30)
    KillThread(LVarA)
    Call(SetPlayerActionState, 0)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_ScriptedSpring_Entity_Spring4 = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerActionState, 6)
    Wait(1)
    ExecGetTID(TTYD64_tik_28_Script_ScriptedSpring_FollowCam, LVarA)
    Call(SetPlayerJumpscale, Float(0.7001953125))
    Call(PlayerJump, 717, 0, 174, 30)
    KillThread(LVarA)
    Call(SetPlayerActionState, 0)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_ScriptedSpring_Entity_Spring3 = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerActionState, 6)
    Wait(1)
    ExecGetTID(TTYD64_tik_28_Script_ScriptedSpring_FollowCam, LVarA)
    Call(SetPlayerJumpscale, Float(0.7001953125))
    Call(PlayerJump, 571, 0, -129, 30)
    KillThread(LVarA)
    Call(SetPlayerActionState, 0)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_Main = {
    Set(GameByte(425), 2)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_tik_28_Script_MakeEntities)
    Exec(TTYD64_tik_28_Script_SetupMusic)
    Exec(TTYD64_tik_28_Script_SetupTexturePan)
    Exec(TTYD64_tik_28_Script_EnterMap)
    Return
    End
};

u8 TTYD64_tik_28_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x29, 0x54, 0xF7, 0x53, 0x45, 0x45, 0x4D, 0x53,
    0xF7, 0x54, 0x48, 0x41, 0x54, 0xF7, 0x41, 0x4C, 0x4C, 0xF7, 0x54, 0x48,
    0x45, 0xF7, 0x57, 0x41, 0x54, 0x45, 0x52, 0xF7, 0x46, 0x52, 0x4F, 0x4D,
    0xF0, 0x54, 0x48, 0x45, 0xF7, 0x53, 0x45, 0x57, 0x45, 0x52, 0x53, 0xF7,
    0x49, 0x53, 0xF7, 0x44, 0x52, 0x41, 0x49, 0x4E, 0x45, 0x44, 0xF7, 0x48,
    0x45, 0x52, 0x45, 0x0E, 0xF0, 0xF1, 0xFB, 0x37, 0x45, 0xF7, 0x42, 0x45,
    0x54, 0x54, 0x45, 0x52, 0xF7, 0x55, 0x53, 0x45, 0xF7, 0x54, 0x48, 0x4F,
    0x53, 0x45, 0xF7, 0x53, 0x50, 0x52, 0x49, 0x4E, 0x47, 0x53, 0xF7, 0x49,
    0x46, 0xF0, 0x57, 0x45, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x57,
    0x41, 0x4E, 0x54, 0xF7, 0x54, 0x4F, 0xF7, 0x47, 0x45, 0x54, 0xF7, 0x44,
    0x52, 0x4F, 0x57, 0x4E, 0x45, 0x44, 0xF7, 0x49, 0x4E, 0xF0, 0x53, 0x54,
    0x49, 0x4E, 0x4B, 0x59, 0xF7, 0x57, 0x41, 0x54, 0x45, 0x52, 0xF7, 0x2D,
    0x41, 0x52, 0x49, 0x4F, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_tik_28_Script_TexturePan_Update = {
    SetGroup(0)
    IfEq(LVar5, 1)
        IfEq(LVar6, 1)
            IfEq(LVar7, 1)
                IfEq(LVar8, 1)
                    Call(TTYD64_TexturePan_Simple)
                    Return
                EndIf
            EndIf
        EndIf
    EndIf
    Call(TTYD64_TexturePan_Complex)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_Exit1 = {
    SetGroup(27)
    Set(LVarA, 1)
    Set(LVarB, 18)
    Set(LVarC, (Bytecode) TTYD64_tik_28_Script_GoToMapPipe)
    Set(LVarD, 2)
    ExecWait(TTYD64_tik_28_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_ScriptedSpring_FollowCam = {
    Loop(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetCamTarget, 0, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tik_28_Script_Exit0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "tik_23", 2)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_tik_28_Script_Exit0, 0x80000, 0, 1, 0)
    BindTrigger(TTYD64_tik_28_Script_Exit1, 128, 18, 1, 0)
    Return
    End
};

MapSettings TTYD64_tik_28_Header = {
    .main = &TTYD64_tik_28_Script_Main,
    .entryList = &TTYD64_tik_28_EntryList,
    .entryCount = 3,
    .background = NULL,
    .tattle = { .get = TTYD64_tik_28_GetTattle },
};

EvtScript TTYD64_tik_28_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(2))
    SetConst(LVar1, GameFlag(4550))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_SetupMusic = {
    Call(SetMusic, 0, 75, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EntryList TTYD64_tik_28_EntryList = {
    { -160.0f, 0.0f, 51.0f, 90.0f },
    { 848.0f, 33.0f, -123.0f, 90.0f },
    { -173.0f, 33.0f, -122.0f, 90.0f },
};

EvtScript TTYD64_tik_28_Script_GoToMapPipe = {
    Call(GotoMap, (Bytecode) "tik_28", LVarD)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_UpdateRespawnPoint_1 = {
    Set(MapVar(0), 0)
    Return
    End
};

EvtScript TTYD64_tik_28_Script_UpdateRespawnPoint_2 = {
    Set(MapVar(0), 1)
    Return
    End
};

MapConfig TTYD64_mapcfg_tik_28 = {
    .id = "tik_28",
    .settings = &TTYD64_tik_28_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 2,
};
// clang-format on

void TTYD64_nm_Install_tik_28(void) {
    TTYD64_tik_28_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_tik_28_String_Tattle);
}
