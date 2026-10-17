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

extern NpcData TTYD64_tyd_03_NpcGroup_Goombas[];
extern EvtScript TTYD64_tyd_03_Script_EnterHorizontalPipe;
extern EvtScript TTYD64_tyd_03_Script_EnterVerticalPipe;
extern EvtScript TTYD64_tyd_03_Script_ExitHorizontalPipe;
extern EvtScript TTYD64_tyd_03_Script_Goomba_TrackBattle;
extern EvtScript TTYD64_tyd_03_Script_ExitVerticalPipe;
extern u8 TTYD64_tyd_03_String_Goomba_Start[];
extern EvtScript TTYD64_tyd_03_Script_Goomba_Interact_Main;
extern EvtScript TTYD64_tyd_03_Script_Main;
extern EvtScript TTYD64_tyd_03_Script_EnterMap;
extern u8 TTYD64_tyd_03_Tattle_Goomba[];
extern EvtScript TTYD64_tyd_03_Script_MakeEntities;
extern EvtScript TTYD64_tyd_03_Script_Goomba_Idle;
extern u8 TTYD64_tyd_03_String_Goomba_Beated[];
extern u8 TTYD64_tyd_03_String_Tattle[];
extern u8 TTYD64_tyd_03_String_Goomba_NextBattle[];
extern EvtScript TTYD64_tyd_03_Script_Exit0;
extern EvtScript TTYD64_tyd_03_Script_Goomba_Init_Main;
extern u8 TTYD64_tyd_03_String_Goomba_FinalBattle[];
extern MapSettings TTYD64_tyd_03_Header;
extern EvtScript TTYD64_tyd_03_Script_Entity_Shine1;
extern u8 TTYD64_tyd_03_String_Goomba_Reward[];
extern EvtScript TTYD64_tyd_03_Script_SetupMusic;
extern u8 TTYD64_tyd_03_String_Goomba_Yes[];
extern u8 TTYD64_tyd_03_String_Goomba_No[];
extern EvtScript TTYD64_tyd_03_Script_GotoMap_Exit0;
s32 TTYD64_tyd_03_Function_Init(void);
extern NpcSettings TTYD64_tyd_03_NpcSettings_Goomba;
extern EvtScript TTYD64_tyd_03_Script_CreateExitTriggers;
extern EvtScript TTYD64_tyd_03_Script_Goomba_Interact;
extern NpcGroupList TTYD64_tyd_03_NpcGroupList_tyd03;
extern EntryList TTYD64_tyd_03_EntryList;
extern EvtScript TTYD64_tyd_03_Script_Goomba_Init;

// clang-format off
static s32 TTYD64_tyd_03_GetTattleMsg;

static s32 TTYD64_tyd_03_GetTattle(void) {
    return TTYD64_tyd_03_GetTattleMsg;
}

NpcData TTYD64_tyd_03_NpcGroup_Goombas[] = {
    {
        .id = 0,
        .settings = &TTYD64_tyd_03_NpcSettings_Goomba,
        .pos = { 38.0f, 60.0f, 13.0f },
        .flags = 0x00850D0D,
        .init = TTYD64_tyd_03_Script_Goomba_Init_Main,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00260001, .walk = 0x00260000, .run = 0x00260000, .chase = 0x00260000, .anim_4 = 0x00260000, .anim_5 = 0x00260000, .death = 0x00260000, .hit = 0x00260000, .anim_8 = 0x00260000, .anim_9 = 0x00260000, .anim_A = 0x00260000, .anim_B = 0x00260000, .anim_C = 0x00260000, .anim_D = 0x00260000, .anim_E = 0x00260000, .anim_F = 0x00260000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 1,
        .settings = &TTYD64_tyd_03_NpcSettings_Goomba,
        .pos = { 64.0f, 60.0f, 13.0f },
        .flags = 0x00850D0D,
        .init = TTYD64_tyd_03_Script_Goomba_Init,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00260001, .walk = 0x00260000, .run = 0x00260000, .chase = 0x00260000, .anim_4 = 0x00260000, .anim_5 = 0x00260000, .death = 0x00260000, .hit = 0x00260000, .anim_8 = 0x00260000, .anim_9 = 0x00260000, .anim_A = 0x00260000, .anim_B = 0x00260000, .anim_C = 0x00260000, .anim_D = 0x00260000, .anim_E = 0x00260000, .anim_F = 0x00260000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 2,
        .settings = &TTYD64_tyd_03_NpcSettings_Goomba,
        .pos = { 50.0f, 60.0f, -7.0f },
        .flags = 0x00850D0D,
        .init = TTYD64_tyd_03_Script_Goomba_Init,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00260001, .walk = 0x00260000, .run = 0x00260000, .chase = 0x00260000, .anim_4 = 0x00260000, .anim_5 = 0x00260000, .death = 0x00260000, .hit = 0x00260000, .anim_8 = 0x00260000, .anim_9 = 0x00260000, .anim_A = 0x00260000, .anim_B = 0x00260000, .anim_C = 0x00260000, .anim_D = 0x00260000, .anim_E = 0x00260000, .anim_F = 0x00260000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 3,
        .settings = &TTYD64_tyd_03_NpcSettings_Goomba,
        .pos = { 76.0f, 60.0f, -7.0f },
        .flags = 0x00850D0D,
        .init = TTYD64_tyd_03_Script_Goomba_Init,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00260001, .walk = 0x00260000, .run = 0x00260000, .chase = 0x00260000, .anim_4 = 0x00260000, .anim_5 = 0x00260000, .death = 0x00260000, .hit = 0x00260000, .anim_8 = 0x00260000, .anim_9 = 0x00260000, .anim_A = 0x00260000, .anim_B = 0x00260000, .anim_C = 0x00260000, .anim_D = 0x00260000, .anim_E = 0x00260000, .anim_F = 0x00260000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_tyd_03_Script_EnterHorizontalPipe = {
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

EvtScript TTYD64_tyd_03_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_tyd_03_Script_ExitHorizontalPipe = {
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

EvtScript TTYD64_tyd_03_Script_Goomba_TrackBattle = {
    Call(DisablePlayerInput, 1)
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Call(SetSelfEnemyFlagBits, 4, 1)
        Switch(MapVar(0))
        CaseEq(0)
            Set(LVar0, 15361)
        CaseEq(1)
            Set(LVar0, 15362)
        CaseEq(2)
            Set(LVar0, 15363)
        CaseEq(3)
            Set(LVar0, 15364)
        CaseEq(4)
            Set(LVar0, 15365)
        CaseEq(5)
            Set(LVar0, 15616)
        CaseEq(6)
            Set(LVar0, 15617)
        CaseEq(7)
            Set(LVar0, 15618)
        CaseEq(8)
            Set(LVar0, 15619)
        CaseEq(9)
            Set(LVar0, 15360)
        EndSwitch
        Call(TTYD64_SetNpcGroupBattleID, 0, LVar0)
        Add(MapVar(0), 1)
        Switch(MapVar(0))
        CaseEq(9)
            Call(SpeakToPlayer, -1, 0x260001, 0x260001, 0, (Bytecode) TTYD64_tyd_03_String_Goomba_FinalBattle)
        CaseEq(10)
            Set(MapVar(0), 0)
            Call(TTYD64_SetNpcGroupBattleID, 0, 15360)
            Call(SpeakToPlayer, -1, 0x260001, 0x260001, 0, (Bytecode) TTYD64_tyd_03_String_Goomba_Beated)
            IfEq(GameFlag(5169), 0)
                Call(SpeakToPlayer, -1, 0x260001, 0x260001, 0, (Bytecode) TTYD64_tyd_03_String_Goomba_Reward)
                Call(ShowGotItem, 226, 1, 0)
                Call(TTYD64_tp_AddBadge, 226, 0)
                Set(GameFlag(5169), 1)
            EndIf
            Call(DisablePlayerInput, 0)
            Return
        CaseDefault
            Call(SpeakToPlayer, -1, 0x260001, 0x260001, 0, (Bytecode) TTYD64_tyd_03_String_Goomba_NextBattle)
        EndSwitch
        Call(SetSelfVar, 0, 1)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_tyd_03_Script_ExitVerticalPipe = {
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

u8 TTYD64_tyd_03_String_Goomba_Start[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0xF7, 0x57, 0x48, 0x41, 0x54, 0x07, 0x53,
    0xF7, 0x55, 0x50, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C, 0xF7, 0x41,
    0x52, 0x45, 0xF7, 0x59, 0x4F, 0x55, 0xF0, 0x4C, 0x4F, 0x4F, 0x4B, 0x49,
    0x4E, 0x47, 0xF7, 0x46, 0x4F, 0x52, 0xF7, 0x41, 0xF7, 0x43, 0x48, 0x41,
    0x4C, 0x4C, 0x45, 0x4E, 0x47, 0x45, 0x1F, 0xF0, 0xF1, 0xFB, 0x29, 0x07,
    0x4D, 0xF7, 0x53, 0x55, 0x52, 0x45, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x57,
    0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x42, 0x45, 0xF7, 0x41, 0x42, 0x4C, 0x45,
    0xF7, 0x54, 0x4F, 0xF0, 0x42, 0x45, 0x41, 0x54, 0xF7, 0x55, 0x53, 0x0C,
    0xF7, 0x41, 0x4C, 0x4F, 0x4E, 0x47, 0xF7, 0x57, 0x49, 0x54, 0x48, 0xF7,
    0x4D, 0x59, 0xF7, 0x4F, 0x54, 0x48, 0x45, 0x52, 0xF0, 0x42, 0x55, 0x44,
    0x44, 0x49, 0x45, 0x53, 0x0E, 0xF0, 0xF1, 0xFB, 0x29, 0x46, 0xF7, 0x59,
    0x4F, 0x55, 0xF7, 0x50, 0x41, 0x53, 0x53, 0xF7, 0x41, 0xF7, 0x52, 0x4F,
    0x55, 0x4E, 0x44, 0xF7, 0x57, 0x48, 0x49, 0x4C, 0x45, 0xF0, 0x46, 0x55,
    0x4C, 0x46, 0x49, 0x4C, 0x4C, 0x49, 0x4E, 0x47, 0xF7, 0x54, 0x48, 0x41,
    0x54, 0xF7, 0x52, 0x4F, 0x55, 0x4E, 0x44, 0xF7, 0x43, 0x4F, 0x4E, 0x44,
    0x49, 0x54, 0x49, 0x4F, 0x4E, 0xF7, 0x59, 0x4F, 0x55, 0xF0, 0x57, 0x49,
    0x4C, 0x4C, 0xF7, 0x4D, 0x4F, 0x56, 0x45, 0xF7, 0x54, 0x4F, 0xF7, 0x54,
    0x48, 0x45, 0xF7, 0x4E, 0x45, 0x58, 0x54, 0xF7, 0x4F, 0x4E, 0x45, 0x0E,
    0xF0, 0xF1, 0xFB, 0x29, 0x54, 0xF7, 0x57, 0x4F, 0x4E, 0x07, 0x54, 0xF7,
    0x42, 0x45, 0xF7, 0x45, 0x41, 0x53, 0x59, 0x0C, 0xF7, 0x44, 0x4F, 0xF7,
    0x59, 0x4F, 0x55, 0xF7, 0x41, 0x43, 0x43, 0x45, 0x50, 0x54, 0x1F, 0xF0,
    0xFF, 0x04, 0xFD
};

EvtScript TTYD64_tyd_03_Script_Goomba_Interact_Main = {
    Call(DisablePlayerInput, 1)
    Call(SpeakToPlayer, -1, 0x260001, 0x260001, 0, (Bytecode) TTYD64_tyd_03_String_Goomba_Start)
    Call(ShowChoice, 0x1E000D)
    IfEq(LVar0, 0)
        Call(ContinueSpeech, -1, 0x260001, 0x260001, 0, (Bytecode) TTYD64_tyd_03_String_Goomba_Yes)
        Call(SetSelfVar, 0, 1)
    Else
        Call(ContinueSpeech, -1, 0x260001, 0x260001, 0, (Bytecode) TTYD64_tyd_03_String_Goomba_No)
        Call(DisablePlayerInput, 0)
    EndIf
    Return
    End
};

EvtScript TTYD64_tyd_03_Script_Main = {
    Set(GameByte(425), 34)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_tyd_03_NpcGroupList_tyd03)
    Exec(TTYD64_tyd_03_Script_MakeEntities)
    Exec(TTYD64_tyd_03_Script_SetupMusic)
    Exec(TTYD64_tyd_03_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_tyd_03_Script_EnterMap = {
    Call(GetLoadType, LVar0)
    IfEq(LVar0, 1)
        Exec(EnterSavePoint)
        Exec(TTYD64_tyd_03_Script_CreateExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVarA, (Bytecode) TTYD64_tyd_03_Script_CreateExitTriggers)
        Exec(TTYD64_tyd_03_Script_EnterVerticalPipe)
    CaseDefault
        Exec(TTYD64_tyd_03_Script_CreateExitTriggers)
    EndSwitch
    Return
    End
};

u8 TTYD64_tyd_03_Tattle_Goomba[] = {
    0xFC, 0x04, 0x34, 0x48, 0x49, 0x53, 0xF7, 0x47, 0x52, 0x4F, 0x55, 0x50,
    0xF7, 0x4F, 0x46, 0xF7, 0x27, 0x4F, 0x4F, 0x4D, 0x42, 0x41, 0x53, 0xF7,
    0x49, 0x53, 0xF7, 0x52, 0x45, 0x41, 0x44, 0x59, 0xF7, 0x54, 0x4F, 0xF0,
    0x46, 0x49, 0x47, 0x48, 0x54, 0xF7, 0x41, 0x47, 0x41, 0x49, 0x4E, 0x53,
    0x54, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x49, 0x4E, 0xF7, 0x41, 0xF7, 0x4D,
    0x55, 0x4C, 0x54, 0x49, 0x0D, 0x52, 0x4F, 0x55, 0x4E, 0x44, 0xF0, 0x43,
    0x4F, 0x4D, 0x42, 0x41, 0x54, 0xF7, 0x41, 0x4C, 0x4F, 0x4E, 0x47, 0xF7,
    0x57, 0x49, 0x54, 0x48, 0xF7, 0x4D, 0x4F, 0x52, 0x45, 0xF7, 0x46, 0x49,
    0x47, 0x48, 0x54, 0x45, 0x52, 0x53, 0x0E, 0xF0, 0xF1, 0xFB, 0x39, 0x4F,
    0x55, 0xF7, 0x53, 0x48, 0x4F, 0x55, 0x4C, 0x44, 0xF7, 0x41, 0x43, 0x43,
    0x45, 0x50, 0x54, 0xF7, 0x54, 0x4F, 0xF7, 0x46, 0x49, 0x47, 0x48, 0x54,
    0xF7, 0x57, 0x48, 0x45, 0x4E, 0xF7, 0x59, 0x4F, 0x55, 0xF0, 0x4B, 0x4E,
    0x4F, 0x57, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x41, 0x52, 0x45, 0xF7, 0x46,
    0x55, 0x4C, 0x4C, 0x59, 0xF7, 0x52, 0x45, 0x41, 0x44, 0x59, 0xF7, 0x2D,
    0x41, 0x52, 0x49, 0x4F, 0x0E, 0xF1, 0xFD
};

EvtScript TTYD64_tyd_03_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SavePoint), 79, 57, 309, 0, 0x80000000)
    Call(MakeEntity, Ref(Entity_HeartBlock), 128, 57, 309, 0, 0x80000000)
    Call(MakeEntity, Ref(Entity_SuperBlock), 530, 57, 51, 0, 0x80000000)
    Set(MapVar(1), LVar0)
    Call(AssignBlockFlag, GameFlag(5170))
    Call(AssignScript, (Bytecode) TTYD64_tyd_03_Script_Entity_Shine1)
    Return
    End
};

EvtScript TTYD64_tyd_03_Script_Goomba_Idle = {
    Loop(0)
        Call(GetSelfVar, 0, LVar0)
        IfEq(LVar0, 1)
            Call(SetSelfVar, 0, 0)
            Call(StartBossBattle, 2)
            Thread
                Wait(1)
                Call(DisablePlayerInput, 0)
            EndThread
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

u8 TTYD64_tyd_03_String_Goomba_Beated[] = {
    0xFC, 0x01, 0x37, 0x4F, 0x57, 0x01, 0xF7, 0x29, 0x54, 0xF7, 0x53, 0x45,
    0x45, 0x4D, 0x53, 0xF7, 0x4C, 0x49, 0x4B, 0x45, 0xF7, 0x59, 0x4F, 0x55,
    0xF7, 0x41, 0x52, 0x45, 0xF7, 0x52, 0x45, 0x41, 0x4C, 0x4C, 0x59, 0xF0,
    0x54, 0x4F, 0x55, 0x47, 0x48, 0xF7, 0x41, 0x54, 0xF7, 0x45, 0x4E, 0x44,
    0xF7, 0x4F, 0x46, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x44, 0x41, 0x59, 0x01,
    0xF0, 0xF1, 0xFB, 0x34, 0x48, 0x41, 0x54, 0xF7, 0x57, 0x41, 0x53, 0xF7,
    0x46, 0x55, 0x4E, 0x0C, 0xF7, 0x43, 0x4F, 0x4D, 0x45, 0xF7, 0x42, 0x41,
    0x43, 0x4B, 0xF0, 0x57, 0x48, 0x45, 0x4E, 0x45, 0x56, 0x45, 0x52, 0xF7,
    0x59, 0x4F, 0x55, 0xF7, 0x57, 0x41, 0x4E, 0x54, 0xF7, 0x49, 0x46, 0xF7,
    0x59, 0x4F, 0x55, 0xF7, 0x57, 0x41, 0x4E, 0x54, 0xF0, 0x54, 0x4F, 0xF7,
    0x46, 0x49, 0x47, 0x48, 0x54, 0xF7, 0x41, 0xF7, 0x4C, 0x49, 0x54, 0x54,
    0x4C, 0x45, 0xF7, 0x4D, 0x4F, 0x52, 0x45, 0x01, 0xF1, 0xFD
};

u8 TTYD64_tyd_03_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x29, 0x53, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7,
    0x53, 0x4F, 0x4D, 0x45, 0xF7, 0x4B, 0x49, 0x4E, 0x44, 0xF7, 0x4F, 0x46,
    0xF7, 0x43, 0x4F, 0x4C, 0x49, 0x53, 0x45, 0x55, 0x4D, 0x1F, 0xF0, 0xF1,
    0xFB, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C, 0xF7, 0x4F, 0x42, 0x56, 0x49,
    0x4F, 0x55, 0x53, 0x4C, 0x59, 0xF7, 0x57, 0x45, 0xF7, 0x41, 0x52, 0x45,
    0xF7, 0x54, 0x48, 0x45, 0xF0, 0x53, 0x54, 0x52, 0x4F, 0x4E, 0x47, 0x45,
    0x53, 0x54, 0x0C, 0xF7, 0x29, 0xF7, 0x4B, 0x4E, 0x4F, 0x57, 0xF7, 0x59,
    0x4F, 0x55, 0xF7, 0x54, 0x48, 0x49, 0x4E, 0x4B, 0xF7, 0x54, 0x48, 0x45,
    0xF0, 0x53, 0x41, 0x4D, 0x45, 0x0C, 0xF7, 0x52, 0x49, 0x47, 0x48, 0x54,
    0x1F, 0xF1, 0xFD
};

u8 TTYD64_tyd_03_String_Goomba_NextBattle[] = {
    0xFC, 0x01, 0x27, 0x4F, 0x4F, 0x44, 0xF7, 0x4A, 0x4F, 0x42, 0x0C, 0xF7,
    0x42, 0x55, 0x54, 0xF7, 0x57, 0x45, 0xF7, 0x53, 0x54, 0x49, 0x4C, 0x4C,
    0xF7, 0x48, 0x41, 0x56, 0x45, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0xF0, 0x46,
    0x52, 0x49, 0x45, 0x4E, 0x44, 0x53, 0xF7, 0x57, 0x48, 0x4F, 0xF7, 0x48,
    0x41, 0x56, 0x45, 0xF7, 0x55, 0x4E, 0x46, 0x49, 0x4E, 0x49, 0x53, 0x48,
    0x45, 0x44, 0xF0, 0x42, 0x55, 0x53, 0x49, 0x4E, 0x45, 0x53, 0x53, 0xF7,
    0x57, 0x49, 0x54, 0x48, 0xF7, 0x59, 0x4F, 0x55, 0x0C, 0xF7, 0x41, 0x52,
    0x45, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x52, 0x45, 0x41, 0x44, 0x59, 0x1F,
    0xF1, 0xFD
};

EvtScript TTYD64_tyd_03_Script_Exit0 = {
    SetGroup(27)
    Set(LVarA, 0)
    Set(LVarB, 1)
    Set(LVarC, (Bytecode) TTYD64_tyd_03_Script_GotoMap_Exit0)
    ExecWait(TTYD64_tyd_03_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tyd_03_Script_Goomba_Init_Main = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_tyd_03_Script_Goomba_Interact)
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_tyd_03_Script_Goomba_Idle)
    Call(BindNpcDefeat, -1, (Bytecode) TTYD64_tyd_03_Script_Goomba_TrackBattle)
    Return
    End
};

u8 TTYD64_tyd_03_String_Goomba_FinalBattle[] = {
    0xFC, 0x01, 0x37, 0x45, 0x4C, 0x4C, 0x0C, 0xF7, 0x54, 0x48, 0x49, 0x53,
    0xF7, 0x49, 0x53, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x4C, 0x41, 0x53, 0x54,
    0xF7, 0x46, 0x49, 0x47, 0x48, 0x54, 0x0C, 0xF7, 0x59, 0x4F, 0x55, 0xF0,
    0x42, 0x45, 0x54, 0x54, 0x45, 0x52, 0xF7, 0x42, 0x45, 0xF7, 0x50, 0x52,
    0x45, 0x50, 0x41, 0x52, 0x45, 0x44, 0x0C, 0xF7, 0x47, 0x4F, 0x4F, 0x44,
    0xF7, 0x4C, 0x55, 0x43, 0x4B, 0x01, 0xF1, 0xFD
};

MapSettings TTYD64_tyd_03_Header = {
    .main = TTYD64_tyd_03_Script_Main,
    .entryList = &TTYD64_tyd_03_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_tyd_03_GetTattle },
};

EvtScript TTYD64_tyd_03_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(1))
    SetConst(LVar1, GameFlag(5170))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

u8 TTYD64_tyd_03_String_Goomba_Reward[] = {
    0xFC, 0x01, 0x39, 0x4F, 0x55, 0xF7, 0x4B, 0x4E, 0x4F, 0x57, 0xF7, 0x57,
    0x48, 0x41, 0x54, 0x1F, 0xF0, 0xF1, 0xFB, 0x34, 0x41, 0x4B, 0x45, 0xF7,
    0x54, 0x48, 0x49, 0x53, 0xF7, 0x41, 0x53, 0xF7, 0x41, 0xF7, 0x53, 0x49,
    0x47, 0x4E, 0xF7, 0x4F, 0x46, 0xF7, 0x4F, 0x55, 0x52, 0xF0, 0x41, 0x44,
    0x4D, 0x49, 0x52, 0x41, 0x54, 0x49, 0x4F, 0x4E, 0x0E, 0xF1, 0xFD
};

EvtScript TTYD64_tyd_03_Script_SetupMusic = {
    Call(SetMusic, 0, 169, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

u8 TTYD64_tyd_03_String_Goomba_Yes[] = {
    0xFB, 0x39, 0x4F, 0x55, 0xF7, 0x42, 0x45, 0x54, 0x54, 0x45, 0x52, 0xF7,
    0x42, 0x45, 0xF7, 0x52, 0x45, 0x41, 0x44, 0x59, 0x0C, 0xF7, 0x54, 0x48,
    0x49, 0x53, 0xF7, 0x49, 0x53, 0xF0, 0x47, 0x4F, 0x49, 0x4E, 0x47, 0xF7,
    0x54, 0x4F, 0xF7, 0x42, 0x45, 0xF7, 0x46, 0x55, 0x4E, 0x0E, 0xF1, 0xFD
};

u8 TTYD64_tyd_03_String_Goomba_No[] = {
    0xFB, 0x2F, 0x4B, 0x41, 0x59, 0x0C, 0xF7, 0x4D, 0x41, 0x59, 0x42, 0x45,
    0xF7, 0x4E, 0x45, 0x58, 0x54, 0xF7, 0x54, 0x49, 0x4D, 0x45, 0x0C, 0xF7,
    0x57, 0x45, 0xF7, 0x57, 0x49, 0x4C, 0x4C, 0xF7, 0x42, 0x45, 0xF0, 0x57,
    0x41, 0x49, 0x54, 0x49, 0x4E, 0x47, 0x0E, 0xF1, 0xFD
};

EvtScript TTYD64_tyd_03_Script_GotoMap_Exit0 = {
    Call(GotoMap, (Bytecode) "arn_24", 1)
    Wait(100)
    Return
    End
};

s32 TTYD64_tyd_03_Function_Init(void) {
    sprintf(wMapTexName, "tst_tex");
    return false;
}

NpcSettings TTYD64_tyd_03_NpcSettings_Goomba = {
    .defaultAnim = 0x00000000,
    .height = 30,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = NULL,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 99,
    .actionFlags = 0,
};

EvtScript TTYD64_tyd_03_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_tyd_03_Script_Exit0, 128, 1, 1, 0)
    Return
    End
};

EvtScript TTYD64_tyd_03_Script_Goomba_Interact = {
    Exec(TTYD64_tyd_03_Script_Goomba_Interact_Main)
    Wait(30)
    Return
    End
};

NpcGroupList TTYD64_tyd_03_NpcGroupList_tyd03 = {
    { .npcCount = 4, .npcs = TTYD64_tyd_03_NpcGroup_Goombas, .battle = 0x3C00, .stage = 0 },
    {},
};

EntryList TTYD64_tyd_03_EntryList = {
    { 1.0f, 31.0f, 363.0f, 90.0f },
};

EvtScript TTYD64_tyd_03_Script_Goomba_Init = {
    Return
    End
};

MapConfig TTYD64_mapcfg_tyd_03 = {
    .id = "tyd_03",
    .settings = &TTYD64_tyd_03_Header,
    .bgName = NULL,
    .init = TTYD64_tyd_03_Function_Init,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_tp_Install_tyd_03(void) {
    TTYD64_tp_BindMessage(TTYD64_tyd_03_Script_Goomba_TrackBattle, TTYD64_tyd_03_String_Goomba_FinalBattle);
    TTYD64_tp_BindMessage(TTYD64_tyd_03_Script_Goomba_TrackBattle, TTYD64_tyd_03_String_Goomba_Beated);
    TTYD64_tp_BindMessage(TTYD64_tyd_03_Script_Goomba_TrackBattle, TTYD64_tyd_03_String_Goomba_Reward);
    TTYD64_tp_BindMessage(TTYD64_tyd_03_Script_Goomba_TrackBattle, TTYD64_tyd_03_String_Goomba_NextBattle);
    TTYD64_tp_BindMessage(TTYD64_tyd_03_Script_Goomba_Interact_Main, TTYD64_tyd_03_String_Goomba_Start);
    TTYD64_tp_BindMessage(TTYD64_tyd_03_Script_Goomba_Interact_Main, TTYD64_tyd_03_String_Goomba_Yes);
    TTYD64_tp_BindMessage(TTYD64_tyd_03_Script_Goomba_Interact_Main, TTYD64_tyd_03_String_Goomba_No);
    TTYD64_tyd_03_NpcGroup_Goombas[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_tyd_03_Tattle_Goomba);
    TTYD64_tyd_03_NpcGroup_Goombas[1].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_tyd_03_Tattle_Goomba);
    TTYD64_tyd_03_NpcGroup_Goombas[2].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_tyd_03_Tattle_Goomba);
    TTYD64_tyd_03_NpcGroup_Goombas[3].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_tyd_03_Tattle_Goomba);
    TTYD64_tyd_03_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_tyd_03_String_Tattle);
}
