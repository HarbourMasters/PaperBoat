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
#include "port/romhack/specific/TTYD64/world/tyd_pit.h"

API_CALLABLE(arn_04_CleftAI_Main);

extern EvtScript TTYD64_tyd_04_Script_EnterHorizontalPipe;
extern EvtScript TTYD64_tyd_04_Script_EnterVerticalPipe;
extern EvtScript TTYD64_tyd_04_Script_ExitHorizontalPipe;
extern EvtScript TTYD64_tyd_04_Script_MoveRock;
extern EvtScript TTYD64_tyd_04_Script_ExitVerticalPipe;
extern NpcData TTYD64_tyd_04_Npc_HyperCleft[];
extern EvtScript TTYD64_tyd_04_Script_JumpFromHole;
extern EvtScript TTYD64_tyd_04_Script_BindScripts;
extern EvtScript TTYD64_tyd_04_Script_MakeEntities;
extern EvtScript TTYD64_tyd_04_Script_Main;
extern u8 TTYD64_tyd_04_String_Tattle[];
extern EvtScript TTYD64_tyd_04_Script_EnterMap;
extern EvtScript TTYD64_tyd_04_Script_Exit0;
extern MapSettings TTYD64_tyd_04_Header;
extern EvtScript TTYD64_tyd_04_Script_Hole2;
extern EvtScript TTYD64_tyd_04_Script_SetupMusic;
extern EvtScript TTYD64_tyd_04_Script_Hole3;
extern EvtScript TTYD64_tyd_04_Script_Hole1;
extern EvtScript TTYD64_tyd_04_Script_Hole4;
extern EvtScript TTYD64_tyd_04_Script_GotoMap_Exit0;
extern EvtScript TTYD64_tyd_04_Script_MoveRock_Init;
extern MobileAISettings TTYD64_tyd_04_AISettings_802437C0_arn_04;
extern NpcSettings TTYD64_tyd_04_NpcSettings_80243814_arn_04;
s32 TTYD64_tyd_04_Function_Init(void);
extern EvtScript TTYD64_tyd_04_Script_CreateExitTriggers;
extern EvtScript TTYD64_tyd_04_Script_NpcAI_802437F0_arn_04;
extern EvtScript TTYD64_tyd_04_Script_WoodenFloor;
extern NpcGroupList TTYD64_tyd_04_NpcGroupList_tyd04;
extern EntryList TTYD64_tyd_04_EntryList;

// clang-format off
static s32 TTYD64_tyd_04_GetTattleMsg;

static s32 TTYD64_tyd_04_GetTattle(void) {
    return TTYD64_tyd_04_GetTattleMsg;
}

EvtScript TTYD64_tyd_04_Script_EnterHorizontalPipe = {
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

EvtScript TTYD64_tyd_04_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_tyd_04_Script_ExitHorizontalPipe = {
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

EvtScript TTYD64_tyd_04_Script_MoveRock = {
    Thread
        Call(ShakeCam, 0, 0, 100, Float(0.599609375))
    EndThread
    ChildThread
        Call(GetModelCenter, 54)
        Call(UseSettingsFrom, 0, LVar0, 0, LVar2)
        Call(GetPlayerPos, 0, LVar1, 0)
        Call(SetCamSpeed, 0, Float(3.0))
        Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
        Call(PanToTarget, 0, 0, 1)
    EndChildThread
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(PlaySound, 0x80000010)
    Call(MakeLerp, 0, 100, 142, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, 56, LVar0, 0, 0)
        Call(UpdateColliderTransform, 11)
        Call(UpdateColliderTransform, 12)
        Set(LVar4, LVar1)
        Call(GetModelCenter, 55)
        Set(LVar5, 44)
        Sub(LVar0, LVar5)
        Call(GetPlayerPos, 0, LVar1, LVar2)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetPlayerActionState, 20)
        Wait(1)
        IfEq(LVar4, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(StopSound, 0x80000010)
    Call(PlaySound, 11)
    Call(SetPlayerActionState, 0)
    Call(SetPlayerAnimation, 0x10002)
    Unbind
    Wait(10)
    Set(GameFlag(5261), 1)
    Call(DisablePlayerInput, 0)
    Call(DisablePlayerPhysics, 0)
    Return
    End
};

EvtScript TTYD64_tyd_04_Script_ExitVerticalPipe = {
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

NpcData TTYD64_tyd_04_Npc_HyperCleft[] = {
    {
        .id = 0,
        .settings = &TTYD64_tyd_04_NpcSettings_80243814_arn_04,
        .pos = { 541.0f, 0.0f, 39.0f },
        .flags = 0x00000400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 1, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 541, .centerPos.y = 0, .centerPos.z = 39, .wanderSize.x = 50, .wanderSize.z = 30, .moveSpeedOverride = -32767, .wanderShape = 1, .detectPos.x = 541, .detectPos.y = 0, .detectPos.z = 39, .detectSize.x = 120, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00300102, .walk = 0x00300106, .run = 0x00300107, .chase = 0x00300107, .anim_4 = 0x00300102, .anim_5 = 0x00300102, .death = 0x00300108, .hit = 0x00300108, .anim_8 = 0x00300114, .anim_9 = 0x00300117, .anim_A = 0x00300113, .anim_B = 0x00300115, .anim_C = 0x00300110, .anim_D = 0x00300111, .anim_E = 0x00300116, .anim_F = 0x00300100 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_tyd_04_Script_JumpFromHole = {
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Call(DisablePlayerPhysics, 1)
    Call(PlaySound, 8321)
    Call(GetColliderCenter, LVarA)
    Add(LVar1, 2)
    Call(SetPlayerPos, LVar0, LVar1, LVar2)
    Call(TeleportPartnerToPlayer)
    Thread
        Call(ResetCam, 0, Float(1.0))
    EndThread
    Call(SetPlayerActionState, 6)
    Call(SetPlayerJumpscale, Float(1.5))
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Set(LVar3, 62)
    IfEq(LVarB, 0)
        Mul(LVar3, -1)
    EndIf
    Add(LVar0, LVar3)
    Add(LVar1, 44)
    Call(PlayerJump, LVar0, LVar1, LVar2, 16)
    Call(WaitForCam, 0, Float(1.0))
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerPhysics, 0)
    Return
    End
};

EvtScript TTYD64_tyd_04_Script_BindScripts = {
    Call(ParentColliderToModel, 11, 54)
    Call(ParentColliderToModel, 12, 55)
    IfEq(GameFlag(5261), 1)
        Call(TranslateGroup, 56, 100, 0, 0)
        Call(UpdateColliderTransform, 11)
        Call(UpdateColliderTransform, 12)
    Else
        BindTrigger(TTYD64_tyd_04_Script_MoveRock_Init, 256, 12, 1, 0)
    EndIf
    BindTrigger(TTYD64_tyd_04_Script_Hole1, 128, 7, 1, 0)
    BindTrigger(TTYD64_tyd_04_Script_Hole2, 128, 8, 1, 0)
    BindTrigger(TTYD64_tyd_04_Script_Hole3, 128, 9, 1, 0)
    BindTrigger(TTYD64_tyd_04_Script_Hole4, 128, 10, 1, 0)
    Return
    End
};

EvtScript TTYD64_tyd_04_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_MulticoinBlock), -492, 59, 23, 0, 0x80000000)
    Call(AssignBlockFlag, GameFlag(5260))
    Call(MakeEntity, Ref(Entity_RedBlock), 733, 60, -17, 0, 373, 0x80000000)
    Call(AssignBlockFlag, GameFlag(5262))
    IfEq(GameFlag(5263), 0)
        Call(MakeEntity, Ref(Entity_BoardedFloor), -256, -6, 0, 0, 0x80000000)
        Call(AssignScript, (Bytecode) TTYD64_tyd_04_Script_WoodenFloor)
    EndIf
    Return
    End
};

EvtScript TTYD64_tyd_04_Script_Main = {
    Set(GameByte(425), 16)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_tyd_04_NpcGroupList_tyd04)
    Exec(TTYD64_tyd_04_Script_MakeEntities)
    Exec(TTYD64_tyd_04_Script_SetupMusic)
    Exec(TTYD64_tyd_04_Script_BindScripts)
    Exec(TTYD64_tyd_04_Script_EnterMap)
    Return
    End
};

u8 TTYD64_tyd_04_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x21, 0x52, 0x45, 0xF7, 0x57, 0x45, 0xF7, 0x49,
    0x4E, 0x0E, 0x0E, 0x0E, 0xF7, 0xF7, 0x26, 0x4F, 0x52, 0x45, 0x56, 0x45,
    0x52, 0xF7, 0x26, 0x4F, 0x52, 0x45, 0x53, 0x54, 0x1F, 0xF0, 0x29, 0x54,
    0xF7, 0x53, 0x45, 0x45, 0x4D, 0x53, 0xF7, 0x53, 0x4F, 0x0C, 0xF7, 0x41,
    0x4E, 0x59, 0x57, 0x41, 0x59, 0x0C, 0xF7, 0x57, 0x45, 0xF7, 0x53, 0x48,
    0x4F, 0x55, 0x4C, 0x44, 0xF0, 0x47, 0x45, 0x54, 0xF7, 0x4F, 0x55, 0x54,
    0xF7, 0x4F, 0x46, 0xF7, 0x48, 0x45, 0x52, 0x45, 0xF7, 0x46, 0x41, 0x53,
    0x54, 0x0C, 0xF7, 0x29, 0xF7, 0x43, 0x41, 0x4E, 0x07, 0x54, 0xF0, 0x53,
    0x54, 0x41, 0x4E, 0x44, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x57, 0x4F, 0x4F,
    0x44, 0x53, 0x0C, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_tyd_04_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVarA, (Bytecode) TTYD64_tyd_04_Script_CreateExitTriggers)
        Exec(TTYD64_tyd_04_Script_EnterVerticalPipe)
    CaseDefault
        Exec(TTYD64_tyd_04_Script_CreateExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_tyd_04_Script_Exit0 = {
    SetGroup(27)
    Set(LVarA, 0)
    Set(LVarB, 2)
    Set(LVarC, (Bytecode) TTYD64_tyd_04_Script_GotoMap_Exit0)
    ExecWait(TTYD64_tyd_04_Script_ExitVerticalPipe)
    Return
    End
};

MapSettings TTYD64_tyd_04_Header = {
    .main = TTYD64_tyd_04_Script_Main,
    .entryList = &TTYD64_tyd_04_EntryList,
    .entryCount = 1,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_tyd_04_GetTattle },
};

EvtScript TTYD64_tyd_04_Script_Hole2 = {
    Set(LVar0, 7)
    Set(LVar1, 0)
    ExecWait(TTYD64_tyd_04_Script_JumpFromHole)
    Return
    End
};

EvtScript TTYD64_tyd_04_Script_SetupMusic = {
    Call(SetMusic, 0, 170, 0, 8)
    Call(PlayAmbientSounds, 0)
    Return
    End
};

EvtScript TTYD64_tyd_04_Script_Hole3 = {
    Set(LVar0, 10)
    Set(LVar1, 1)
    ExecWait(TTYD64_tyd_04_Script_JumpFromHole)
    Return
    End
};

EvtScript TTYD64_tyd_04_Script_Hole1 = {
    Set(LVar0, 8)
    Set(LVar1, 1)
    ExecWait(TTYD64_tyd_04_Script_JumpFromHole)
    Return
    End
};

EvtScript TTYD64_tyd_04_Script_Hole4 = {
    Set(LVar0, 9)
    Set(LVar1, 0)
    ExecWait(TTYD64_tyd_04_Script_JumpFromHole)
    Return
    End
};

EvtScript TTYD64_tyd_04_Script_GotoMap_Exit0 = {
    Call(GotoMap, (Bytecode) "omo_19", 1)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_tyd_04_Script_MoveRock_Init = {
    ExecWait(TTYD64_tyd_04_Script_MoveRock)
    Call(ResetCam, 0, 2000)
    Return
    End
};

MobileAISettings TTYD64_tyd_04_AISettings_802437C0_arn_04 = {
    .moveSpeed = 1.0f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 120.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 8.5f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 3,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 60.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_tyd_04_NpcSettings_80243814_arn_04 = {
    .defaultAnim = 0x00000000,
    .height = 24,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_tyd_04_Script_NpcAI_802437F0_arn_04,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 15,
    .actionFlags = 0,
};

s32 TTYD64_tyd_04_Function_Init(void) {
    sprintf(wMapTexName, "tst_tex");
    return false;
}

EvtScript TTYD64_tyd_04_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_tyd_04_Script_Exit0, 128, 2, 1, 0)
    Return
    End
};

EvtScript TTYD64_tyd_04_Script_NpcAI_802437F0_arn_04 = {
    Call(arn_04_CleftAI_Main, Ref(TTYD64_tyd_04_AISettings_802437C0_arn_04), 8)
    Return
    End
};

EvtScript TTYD64_tyd_04_Script_WoodenFloor = {
    Set(GameFlag(5263), 1)
    Return
    End
};

NpcGroupList TTYD64_tyd_04_NpcGroupList_tyd04 = {
    { .npcCount = 1, .npcs = TTYD64_tyd_04_Npc_HyperCleft, .battle = 0x3B06, .stage = 4 },
    {},
};

EntryList TTYD64_tyd_04_EntryList = {
    { -724.0f, 31.0f, 9.0f, 90.0f },
};

MapConfig TTYD64_mapcfg_tyd_04 = {
    .id = "tyd_04",
    .settings = &TTYD64_tyd_04_Header,
    .bgName = "obk_bg",
    .init = TTYD64_tyd_04_Function_Init,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_tp_Install_tyd_04(void) {
    TTYD64_tyd_04_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_tyd_04_String_Tattle);
}
