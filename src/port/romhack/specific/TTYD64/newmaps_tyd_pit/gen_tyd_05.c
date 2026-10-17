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
#include "port/romhack/specific/TTYD64/newmaps_tyd_pit/tp.h"

API_CALLABLE(kzn_07_FlyingNoAttackAI_Main);

extern EvtScript TTYD64_tyd_05_Script_MarioDrowned;
extern EvtScript TTYD64_tyd_05_Script_EnterHorizontalPipe;
extern EvtScript TTYD64_tyd_05_Script_EnterVerticalPipe;
extern EvtScript TTYD64_tyd_05_Script_ExitHorizontalPipe;
extern EvtScript TTYD64_tyd_05_Script_ExitVerticalPipe;
extern EvtScript TTYD64_tyd_05_Script_UpdateSpikes;
extern EvtScript TTYD64_tyd_05_Script_UpdateBoatPos_Down;
extern NpcData TTYD64_tyd_05_Npc_BulkyBobomb[];
extern NpcData TTYD64_tyd_05_Npc_LavaBubble[];
extern EvtScript TTYD64_tyd_05_Script_UpdateBoatPos_Up;
extern EvtScript TTYD64_tyd_05_Script_InitStuff;
extern EvtScript TTYD64_tyd_05_Script_SetupTexturePan;
extern EvtScript TTYD64_tyd_05_Script_Main;
extern EvtScript TTYD64_tyd_05_Script_Boat1_Up;
extern EvtScript TTYD64_tyd_05_Script_Boat2_Up;
extern EvtScript TTYD64_tyd_05_Script_MakeEntities;
extern EvtScript TTYD64_tyd_05_Script_TexturePan_Update;
extern EvtScript TTYD64_tyd_05_Script_EnterMap;
extern EvtScript TTYD64_tyd_05_Script_NpcAI_80242BD8_kzn_07;
extern EvtScript TTYD64_tyd_05_Script_Boat1_Down;
extern EvtScript TTYD64_tyd_05_Script_Boat2_Down;
extern EvtScript TTYD64_tyd_05_Script_Exit0;
extern MapSettings TTYD64_tyd_05_Header;
extern EvtScript TTYD64_tyd_05_Script_Entity_Shine1;
extern EvtScript TTYD64_tyd_05_Script_Entity_Shine2;
extern EvtScript TTYD64_tyd_05_Script_SetupMusic;
extern LavaReset TTYD64_tyd_05_LaveReset_Pos[];
extern EvtScript TTYD64_tyd_05_Script_GotoMap_Exit0;
extern u8 TTYD64_tyd_05_String_Tattle[];
extern MobileAISettings TTYD64_tyd_05_AISettings_80242BA8_kzn_07;
extern MobileAISettings TTYD64_tyd_05_AISettings_802417F0;
extern NpcSettings TTYD64_tyd_05_NpcSettings_80242C48_kzn_07;
s32 TTYD64_tyd_05_Function_Init(void);
extern NpcSettings TTYD64_tyd_05_NpcSettings_80241840;
extern EvtScript TTYD64_tyd_05_Script_CreateExitTriggers;
extern NpcGroupList TTYD64_tyd_05_NpcGroupList_tyd05;
extern EvtScript TTYD64_tyd_05_Script_NpcAI_80241820;
extern EvtScript TTYD64_tyd_05_Script_UpdateRespawnPoint_7;
extern EvtScript TTYD64_tyd_05_Script_UpdateRespawnPoint_6;
extern EvtScript TTYD64_tyd_05_Script_UpdateRespawnPoint_1;
extern EvtScript TTYD64_tyd_05_Script_UpdateRespawnPoint_5;
extern EvtScript TTYD64_tyd_05_Script_UpdateRespawnPoint_4;
extern EvtScript TTYD64_tyd_05_Script_UpdateRespawnPoint_3;
extern EvtScript TTYD64_tyd_05_Script_UpdateRespawnPoint_2;
extern EntryList TTYD64_tyd_05_EntryList;

// clang-format off
static s32 TTYD64_tyd_05_GetTattleMsg;

static s32 TTYD64_tyd_05_GetTattle(void) {
    return TTYD64_tyd_05_GetTattleMsg;
}

EvtScript TTYD64_tyd_05_Script_MarioDrowned = {
    Call(GetPartnerInUse, LVarA)
    IfEq(LVarA, 7)
        Return
    EndIf
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
    Switch(MapVar(3))
    CaseEq(0)
        Call(SetPlayerPos, 502, 50, -87)
    CaseEq(1)
        Call(SetPlayerPos, 44, 50, -87)
    CaseEq(2)
        Call(SetPlayerPos, -142, 39, -87)
    CaseEq(3)
        Call(SetPlayerPos, -164, 25, 46)
    CaseEq(4)
        Call(SetPlayerPos, -38, 25, 89)
    CaseEq(5)
        Call(SetPlayerPos, 276, 25, 32)
    CaseEq(6)
        Call(SetPlayerPos, -416, 25, -57)
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

EvtScript TTYD64_tyd_05_Script_EnterHorizontalPipe = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(HidePlayerShadow, 1)
    Call(ModifyColliderFlags, 0, LVarB, 0x7FFFFE00)
    Call(GetEntryID, LVar0)
    Call(TTYD64_Pipe_GetEntryCoords)
    Set(LVar5, LVar1)
    Set(LVar6, LVar2)
    Set(LVar7, LVar3)
    Add(LVar2, 2)
    Call(SetPlayerPos, LVar1, LVar2, LVar3)
    Call(InterpPlayerYaw, LVar4, 0)
    IfEq(LVar4, 90)
        Add(LVar5, 40)
    Else
        Sub(LVar5, 40)
    EndIf
    Call(UseSettingsFrom, 0, LVar5, LVar6, LVar7)
    Call(SetPanTarget, 0, LVar5, LVar6, LVar7)
    Call(SetCamSpeed, 0, Float(90.0))
    Call(PanToTarget, 0, 0, 1)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Call(DisablePartnerAI, 0)
        Call(EnableNpcShadow, -4, 0)
        Call(SetNpcPos, -4, 0, -1000, 0)
        Call(InterpNpcYaw, -4, LVar0, 0)
    EndIf
    Wait(1)
    Call(PlaySound, 355)
    Thread
        Wait(25)
        Call(HidePlayerShadow, 0)
    EndThread
    Call(SetPlayerImgFXFlags, 2304)
    Call(UpdatePlayerImgFX, 0x10002, 5, 3, 1, 1, 0)
    Loop(40)
        Call(TTYD64_Pipe_GetPointInFrontOfPlayer, Float(1.0))
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Thread
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Sub(LVar2, 3)
            Call(SetNpcPos, -4, LVar0, LVar1, LVar2)
            Call(EnableNpcShadow, -4, 1)
            Call(EnablePartnerAI)
        EndThread
    EndIf
    Wait(5)
    Call(UpdatePlayerImgFX, 0x10002, 0, 0, 0, 0, 0)
    Call(ModifyColliderFlags, 1, LVarB, 0x7FFFFE00)
    Call(DisablePlayerInput, 0)
    Call(DisablePlayerPhysics, 0)
    Call(PanToTarget, 0, 0, 0)
    Exec(LVarA)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_EnterVerticalPipe = {
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
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Call(HidePlayerShadow, 0)
    Label(0)
    Call(TTYD64_Pipe_GetCurrentFloor)
    Wait(1)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Exec(LVarA)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_ExitHorizontalPipe = {
    Call(IsPlayerOnValidFloor, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(GetPlayerActionState, LVar0)
    IfEq(LVar0, 26)
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
    Call(ModifyColliderFlags, 0, LVarB, 0x7FFFFE00)
    Set(LVar0, LVarA)
    Call(TTYD64_Pipe_GetEntryCoords)
    Set(LVar5, LVar1)
    Set(LVar6, LVar2)
    Add(LVar6, 2)
    Set(LVar7, LVar3)
    Set(LVar8, LVar4)
    Add(LVar8, 180)
    IfGe(LVar4, 360)
        Sub(LVar4, 360)
    EndIf
    Call(InterpPlayerYaw, LVar8, 1)
    Wait(1)
    Call(PlaySound, 355)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(SetPlayerPos, LVar0, LVar6, LVar7)
    Call(SetPlayerAnimation, 0x10000)
    Call(SetPlayerImgFXFlags, 2048)
    Call(UpdatePlayerImgFX, 0x10000, 5, 3, 1, 1, 0)
    Thread
        Wait(8)
        Call(HidePlayerShadow, 1)
    EndThread
    Thread
        Wait(3)
        Loop(40)
            Call(TTYD64_Pipe_GetPointInFrontOfPlayer, Float(1.0))
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Wait(25)
    ExecWait(LVarC)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_ExitVerticalPipe = {
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

EvtScript TTYD64_tyd_05_Script_UpdateSpikes = {
    SetGroup(239)
    Call(ModifyColliderFlags, 3, 17, 2)
    Thread
        Call(ResetFromLava, (Bytecode) TTYD64_tyd_05_LaveReset_Pos)
    EndThread
    Set(MapVar(2), 0)
    Loop(0)
        Set(LVar6, 17)
        Set(LVar7, 10)
        Wait(1)
        Call(TranslateModel, LVar7, 0, 0, 0)
        Call(ParentColliderToModel, LVar6, LVar7)
        Call(PlaySound, 8339)
        Call(MakeLerp, 0, 50, 4, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateModel, LVar7, 0, LVar0, 0)
            Call(UpdateColliderTransform, LVar6)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(10)
        Call(MakeLerp, 50, 0, 15, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateModel, LVar7, 0, LVar0, 0)
            Call(UpdateColliderTransform, LVar6)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(30)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_UpdateBoatPos_Down = {
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Set(LVarC, LVar2)
    Set(LVarD, LVar3)
    Set(LVarE, LVar4)
    Call(TTYD64_tp_GetVarFromVar, LVarC, LVar0)
    IfEq(LVar0, 0)
        Call(PlaySound, 466)
        Call(TTYD64_tp_SetVarFromVar, LVarC, 1)
    EndIf
    Call(TTYD64_tp_GetVarFromVar, LVarB, LVar0)
    IfEq(LVar0, 8)
        Call(TTYD64_tp_SetVarFromVar, LVarA, 0)
        Return
    EndIf
    Call(TTYD64_tp_GetVarFromVar, LVarA, LVar0)
    Add(LVar0, 1)
    Call(TTYD64_tp_SetVarFromVar, LVarA, LVar0)
    IfGe(LVar0, 1)
        Set(LVar0, 0)
        Call(TTYD64_tp_SetVarFromVar, LVarA, LVar0)
        Call(TTYD64_tp_GetVarFromVar, LVarB, LVar0)
        IfLt(LVar0, 4)
            Add(LVar0, 2)
            Call(TTYD64_tp_SetVarFromVar, LVarB, LVar0)
        EndIf
        Set(LVar1, LVar0)
        Mul(LVar1, -1)
        Call(TranslateGroup, LVarD, 0, LVar1, 0)
        Call(UpdateColliderTransform, LVarE)
    EndIf
    Return
    End
};

NpcData TTYD64_tyd_05_Npc_BulkyBobomb[] = {
    {
        .id = 1,
        .settings = &TTYD64_tyd_05_NpcSettings_80241840,
        .pos = { -505.0f, 25.0f, -49.0f },
        .flags = 0x00000400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 140, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = -505, .centerPos.y = 25, .centerPos.z = -49, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = -505, .detectPos.y = 25, .detectPos.z = -49, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00EC0001, .walk = 0x00EC0012, .run = 0x00EC0013, .chase = 0x00EC0013, .anim_4 = 0x00EC0000, .anim_5 = 0x00EC0000, .death = 0x00EC000D, .hit = 0x00EC000D, .anim_8 = 0x00EC0000, .anim_9 = 0x00EC0000, .anim_A = 0x00EC0000, .anim_B = 0x00EC0000, .anim_C = 0x00EC0000, .anim_D = 0x00EC0000, .anim_E = 0x00EC0000, .anim_F = 0x00EC0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_tyd_05_Npc_LavaBubble[] = {
    {
        .id = 0,
        .settings = &TTYD64_tyd_05_NpcSettings_80242C48_kzn_07,
        .pos = { -160.0f, 37.0f, 14.0f },
        .flags = 0x00000400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 140, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = -160, .centerPos.y = 37, .centerPos.z = 14, .wanderSize.x = 20, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = -160, .detectPos.y = 37, .detectPos.z = 14, .detectSize.x = 30, .detectSize.z = 110, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x00460001, .walk = 0x00460002, .run = 0x00460003, .chase = 0x00460003, .anim_4 = 0x00460000, .anim_5 = 0x00460000, .death = 0x00460007, .hit = 0x00460007, .anim_8 = 0x00460004, .anim_9 = 0x00460000, .anim_A = 0x00460000, .anim_B = 0x00460000, .anim_C = 0x00460000, .anim_D = 0x00460000, .anim_E = 0x00460000, .anim_F = 0x00460000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_tyd_05_Script_UpdateBoatPos_Up = {
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Set(LVarC, LVar2)
    Set(LVarD, LVar3)
    Call(TTYD64_tp_GetVarFromVar, LVarB, LVar0)
    IfEq(LVar0, 0)
        Call(TTYD64_tp_SetVarFromVar, LVarA, 0)
        Return
    EndIf
    Call(TTYD64_tp_GetVarFromVar, LVarA, LVar0)
    Add(LVar0, 1)
    Call(TTYD64_tp_SetVarFromVar, LVarA, LVar0)
    IfGe(LVar0, 2)
        Set(LVar0, 0)
        Call(TTYD64_tp_SetVarFromVar, LVarA, LVar0)
        Call(TTYD64_tp_GetVarFromVar, LVarB, LVar0)
        IfGt(LVar0, 0)
            Sub(LVar0, 1)
            Call(TTYD64_tp_SetVarFromVar, LVarB, LVar0)
        EndIf
        Set(LVar1, LVar0)
        Mul(LVar1, -1)
        Call(TranslateGroup, LVarC, 0, LVar1, 0)
        Call(UpdateColliderTransform, LVarD)
    EndIf
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_InitStuff = {
    Call(ParentColliderToModel, 18, 26)
    Call(ParentColliderToModel, 19, 26)
    BindTrigger(TTYD64_tyd_05_Script_Boat1_Down, 128, 18, 1, 0)
    BindTrigger(TTYD64_tyd_05_Script_Boat2_Down, 128, 19, 1, 0)
    Exec(TTYD64_tyd_05_Script_Boat1_Up)
    Exec(TTYD64_tyd_05_Script_Boat2_Up)
    BindTrigger(TTYD64_tyd_05_Script_UpdateRespawnPoint_1, 128, 8, 1, 0)
    BindTrigger(TTYD64_tyd_05_Script_UpdateRespawnPoint_2, 128, 9, 1, 0)
    BindTrigger(TTYD64_tyd_05_Script_UpdateRespawnPoint_3, 128, 10, 1, 0)
    BindTrigger(TTYD64_tyd_05_Script_UpdateRespawnPoint_4, 128, 11, 1, 0)
    BindTrigger(TTYD64_tyd_05_Script_UpdateRespawnPoint_5, 128, 12, 1, 0)
    BindTrigger(TTYD64_tyd_05_Script_UpdateRespawnPoint_6, 128, 13, 1, 0)
    BindTrigger(TTYD64_tyd_05_Script_UpdateRespawnPoint_7, 128, 14, 1, 0)
    BindTrigger(TTYD64_tyd_05_Script_MarioDrowned, 128, 6, 1, 0)
    Exec(TTYD64_tyd_05_Script_UpdateSpikes)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_SetupTexturePan = {
    Call(SetTexPanner, 0, 0)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 90)
        Set(LVar3, -60)
        Set(LVar4, -70)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_tyd_05_Script_TexturePan_Update)
    EndThread
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_Main = {
    Set(GameByte(425), 36)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_tyd_05_NpcGroupList_tyd05)
    Exec(TTYD64_tyd_05_Script_MakeEntities)
    Exec(TTYD64_tyd_05_Script_SetupMusic)
    Exec(TTYD64_tyd_05_Script_SetupTexturePan)
    Exec(TTYD64_tyd_05_Script_InitStuff)
    Exec(TTYD64_tyd_05_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_Boat1_Up = {
    Loop(0)
        SetConst(LVar0, MapVar(8))
        SetConst(LVar1, MapVar(5))
        Set(LVar2, 24)
        Set(LVar3, 18)
        Call(TTYD64_ReadField, TTYD64_F_GCOLLISIONSTATUS_2_2U, LVar4)
        IfNe(LVar4, LVar3)
            Set(MapVar(10), 0)
            ExecWait(TTYD64_tyd_05_Script_UpdateBoatPos_Up)
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_Boat2_Up = {
    Loop(0)
        SetConst(LVar0, MapVar(9))
        SetConst(LVar1, MapVar(7))
        Set(LVar2, 29)
        Set(LVar3, 19)
        Call(TTYD64_ReadField, TTYD64_F_GCOLLISIONSTATUS_2_2U, LVar4)
        IfNe(LVar4, LVar3)
            Set(MapVar(11), 0)
            ExecWait(TTYD64_tyd_05_Script_UpdateBoatPos_Up)
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SuperBlock), 277, 88, 76, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(5438))
    Call(AssignScript, (Bytecode) TTYD64_tyd_05_Script_Entity_Shine1)
    Call(MakeEntity, Ref(Entity_SuperBlock), -546, 88, -56, 0, 0x80000000)
    Set(MapVar(1), LVar0)
    Call(AssignBlockFlag, GameFlag(5439))
    Call(AssignScript, (Bytecode) TTYD64_tyd_05_Script_Entity_Shine2)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_TexturePan_Update = {
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

EvtScript TTYD64_tyd_05_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVarA, (Bytecode) TTYD64_tyd_05_Script_CreateExitTriggers)
        Exec(TTYD64_tyd_05_Script_EnterVerticalPipe)
    CaseDefault
        Exec(TTYD64_tyd_05_Script_CreateExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_NpcAI_80242BD8_kzn_07 = {
    Call(SetSelfVar, 0, 1)
    Call(SetSelfVar, 5, 0)
    Call(SetSelfVar, 6, 0)
    Call(SetSelfVar, 1, 150)
    Call(kzn_07_FlyingNoAttackAI_Main, Ref(TTYD64_tyd_05_AISettings_80242BA8_kzn_07))
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_Boat1_Down = {
    SetConst(LVar0, MapVar(4))
    SetConst(LVar1, MapVar(5))
    SetConst(LVar2, MapVar(10))
    Set(LVar3, 24)
    Set(LVar4, 18)
    ExecWait(TTYD64_tyd_05_Script_UpdateBoatPos_Down)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_Boat2_Down = {
    SetConst(LVar0, MapVar(6))
    SetConst(LVar1, MapVar(7))
    SetConst(LVar2, MapVar(11))
    Set(LVar3, 29)
    Set(LVar4, 19)
    ExecWait(TTYD64_tyd_05_Script_UpdateBoatPos_Down)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_Exit0 = {
    SetGroup(27)
    Set(LVarA, 0)
    Set(LVarB, 1)
    Set(LVarC, (Bytecode) TTYD64_tyd_05_Script_GotoMap_Exit0)
    ExecWait(TTYD64_tyd_05_Script_ExitVerticalPipe)
    Return
    End
};

MapSettings TTYD64_tyd_05_Header = {
    .main = TTYD64_tyd_05_Script_Main,
    .entryList = &TTYD64_tyd_05_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_tyd_05_GetTattle },
};

EvtScript TTYD64_tyd_05_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(5438))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_Entity_Shine2 = {
    Set(LVar0, MapVar(1))
    SetConst(LVar1, GameFlag(5439))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_SetupMusic = {
    Call(SetMusic, 0, 173, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

LavaReset TTYD64_tyd_05_LaveReset_Pos[] = {
    { .colliderID = 8, .pos = { 502.0f, 50.0f, -87.0f } },
    { .colliderID = 9, .pos = { 44.0f, 50.0f, -87.0f } },
    { .colliderID = -1 },
};

EvtScript TTYD64_tyd_05_Script_GotoMap_Exit0 = {
    Call(GotoMap, (Bytecode) "kzn_03", 5)
    Wait(100)
    Return
    End
};

u8 TTYD64_tyd_05_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x37, 0x4F, 0x57, 0x0C, 0xF7, 0x2D, 0x54, 0x0E,
    0xF7, 0x2C, 0x41, 0x56, 0x41, 0x4C, 0x41, 0x56, 0x41, 0xF7, 0x49, 0x54,
    0x07, 0x53, 0xF7, 0x52, 0x45, 0x41, 0x4C, 0x4C, 0x59, 0xF0, 0x48, 0x55,
    0x47, 0x45, 0x01, 0xF1, 0xFD
};

MobileAISettings TTYD64_tyd_05_AISettings_80242BA8_kzn_07 = {
    .moveSpeed = 0.800000012f,
    .moveTime = 100,
    .waitTime = 0,
    .alertRadius = 90.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 4,
    .chaseSpeed = 3.20000005f,
    .chaseTurnRate = 10,
    .chaseUpdateInterval = 1,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

MobileAISettings TTYD64_tyd_05_AISettings_802417F0 = {
    .moveSpeed = 1.0f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 50.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 2.0f,
    .chaseTurnRate = 180,
    .chaseUpdateInterval = 3,
    .chaseRadius = 70.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_tyd_05_NpcSettings_80242C48_kzn_07 = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_tyd_05_Script_NpcAI_80242BD8_kzn_07,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 17,
    .actionFlags = 0,
};

s32 TTYD64_tyd_05_Function_Init(void) {
    sprintf(wMapTexName, "kzn_tex");
    return false;
}

NpcSettings TTYD64_tyd_05_NpcSettings_80241840 = {
    .defaultAnim = 0x00000000,
    .height = 56,
    .radius = 56,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_tyd_05_Script_NpcAI_80241820,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 5,
    .actionFlags = 0,
};

EvtScript TTYD64_tyd_05_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_tyd_05_Script_Exit0, 128, 1, 1, 0)
    Return
    End
};

NpcGroupList TTYD64_tyd_05_NpcGroupList_tyd05 = {
    { .npcCount = 1, .npcs = TTYD64_tyd_05_Npc_LavaBubble, .battle = 0x3B07, .stage = 5 },
    { .npcCount = 1, .npcs = TTYD64_tyd_05_Npc_BulkyBobomb, .battle = 0x3B08, .stage = 5 },
    {},
};

EvtScript TTYD64_tyd_05_Script_NpcAI_80241820 = {
    Call(BasicAI_Main, Ref(TTYD64_tyd_05_AISettings_802417F0))
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_UpdateRespawnPoint_7 = {
    Set(MapVar(3), 6)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_UpdateRespawnPoint_6 = {
    Set(MapVar(3), 5)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_UpdateRespawnPoint_1 = {
    Set(MapVar(3), 0)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_UpdateRespawnPoint_5 = {
    Set(MapVar(3), 4)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_UpdateRespawnPoint_4 = {
    Set(MapVar(3), 3)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_UpdateRespawnPoint_3 = {
    Set(MapVar(3), 2)
    Return
    End
};

EvtScript TTYD64_tyd_05_Script_UpdateRespawnPoint_2 = {
    Set(MapVar(3), 1)
    Return
    End
};

EntryList TTYD64_tyd_05_EntryList = {
    { 554.0f, 82.0f, -91.0f, -90.0f },
};

MapConfig TTYD64_mapcfg_tyd_05 = {
    .id = "tyd_05",
    .settings = &TTYD64_tyd_05_Header,
    .bgName = NULL,
    .init = TTYD64_tyd_05_Function_Init,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_tp_Install_tyd_05(void) {
    TTYD64_tyd_05_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_tyd_05_String_Tattle);
}
