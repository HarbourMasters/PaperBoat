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
#include "port/romhack/specific/TTYD64/newmaps/nm.h"

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(GetMapID);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(PanToTarget);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlayAmbientSounds);
API_CALLABLE(PlaySoundAtCollider);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(RotateGroup);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetZoneEnabled);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseExitHeading);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(WaitForCam);
API_CALLABLE(isk_05_HoppingAI_Main);
API_CALLABLE(mim_01_SetForeverForestFog);
API_CALLABLE(mim_03_GetPlayerDistFromMapCenter);

extern EvtScript TTYD64_mim_13_Script_MoveLog;
extern EvtScript TTYD64_mim_13_Script_InitCameraZones;
extern EvtScript TTYD64_mim_13_Script_UpdateCameraZones;
extern NpcData TTYD64_mim_13_NpcGroup_Fuzzy[];
extern EvtScript TTYD64_mim_13_Script_802441E0;
extern EvtScript TTYD64_mim_13_Script_Main_EnterWalk;
extern EvtScript TTYD64_mim_13_Script_802437D4;
extern EvtScript TTYD64_mim_13_Script_ResetLogsRotation;
extern u8 TTYD64_mim_13_String_Tattle[];
extern EvtScript TTYD64_mim_13_Script_CreateExitTriggers;
extern EvtScript TTYD64_mim_13_Script_80243FF0;
extern EvtScript TTYD64_mim_13_Script_8024406C;
extern EvtScript TTYD64_mim_13_Script_802440E8;
extern EvtScript TTYD64_mim_13_Script_80244164;
extern EvtScript TTYD64_mim_13_Script_Exit_Entry3;
extern EvtScript TTYD64_mim_13_Script_Exit_Entry2;
extern EvtScript TTYD64_mim_13_Script_Exit_Entry1;
extern EvtScript TTYD64_mim_13_Script_Exit_Entry0;
extern EvtScript TTYD64_mim_13_Script_MakeEntities;
extern EntryList TTYD64_mim_13_EntryList;
extern MapSettings TTYD64_mim_13_Header;
extern EvtScript TTYD64_mim_13_Script_NpcAI_Fuzzy;
extern EvtScript TTYD64_mim_13_Script_SetupMusic;
extern MobileAISettings TTYD64_mim_13_AISettings_Fuzzy;
extern NpcSettings TTYD64_mim_13_NpcSettings_Fuzzy;
extern NpcGroupList TTYD64_mim_13_NpcGroupList_Enemies;

// clang-format off
static s32 TTYD64_mim_13_GetTattleMsg;

static s32 TTYD64_mim_13_GetTattle(void) {
    return TTYD64_mim_13_GetTattleMsg;
}

EvtScript TTYD64_mim_13_Script_MoveLog = {
    Thread
        Call(PlaySoundAtCollider, LVar9, 468, 0)
        Wait(19)
        Call(PlaySoundAtCollider, LVar9, 469, 0)
    EndThread
    Switch(AreaByte(1))
    CaseEq(0)
        Thread
            Call(MakeLerp, 10, 90, 10, 1)
            Label(10)
            Call(UpdateLerp)
            Call(RotateGroup, LVarA, LVar0, 0, 1, 0)
            Call(UpdateColliderTransform, LVar9)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(10)
            EndIf
        EndThread
        Wait(15)
        Thread
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Add(LVar0, LVar7)
            Add(LVar2, LVar8)
            Call(PlayerMoveTo, LVar0, LVar2, 15)
        EndThread
        Set(LVar1, 1)
        Exec(TTYD64_mim_13_Script_UpdateCameraZones)
        Call(MakeLerp, 90, 360, 30, 0)
        Label(20)
        Call(UpdateLerp)
        Call(RotateGroup, LVarA, LVar0, 0, 1, 0)
        Call(UpdateColliderTransform, LVar9)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(20)
        EndIf
        Exec(TTYD64_mim_13_Script_ResetLogsRotation)
        Set(AreaByte(1), 1)
        Set(GameFlag(924), 1)
    CaseEq(1)
        Thread
            Call(MakeLerp, 360, 270, 10, 1)
            Label(30)
            Call(UpdateLerp)
            Call(RotateGroup, LVarA, LVar0, 0, 1, 0)
            Call(UpdateColliderTransform, LVar9)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(30)
            EndIf
        EndThread
        Wait(15)
        Thread
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Sub(LVar0, LVar7)
            Sub(LVar2, LVar8)
            Call(PlayerMoveTo, LVar0, LVar2, 15)
        EndThread
        Set(LVar1, 2)
        Exec(TTYD64_mim_13_Script_UpdateCameraZones)
        Call(MakeLerp, 270, -10, 30, 0)
        Label(40)
        Call(UpdateLerp)
        Call(RotateGroup, LVarA, LVar0, 0, 1, 0)
        Call(UpdateColliderTransform, LVar9)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(40)
        EndIf
        Set(AreaByte(1), 2)
    CaseEq(2)
        Thread
            Call(MakeLerp, -10, 90, 10, 1)
            Label(50)
            Call(UpdateLerp)
            Call(RotateGroup, LVarA, LVar0, 0, 1, 0)
            Call(UpdateColliderTransform, LVar9)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(50)
            EndIf
        EndThread
        Wait(15)
        Thread
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Add(LVar0, LVar7)
            Add(LVar2, LVar8)
            Call(PlayerMoveTo, LVar0, LVar2, 15)
        EndThread
        Set(LVar1, 1)
        Exec(TTYD64_mim_13_Script_UpdateCameraZones)
        Call(MakeLerp, 90, 360, 30, 0)
        Label(60)
        Call(UpdateLerp)
        Call(RotateGroup, LVarA, LVar0, 0, 1, 0)
        Call(UpdateColliderTransform, LVar9)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(60)
        EndIf
        Exec(TTYD64_mim_13_Script_ResetLogsRotation)
        Set(AreaByte(1), 1)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_mim_13_Script_InitCameraZones = {
    Switch(LVar1)
    CaseEq(0)
        Call(SetZoneEnabled, 11, 1)
        Call(SetZoneEnabled, 9, 1)
        Call(SetZoneEnabled, 10, 1)
        Call(SetZoneEnabled, 8, 1)
        Call(SetZoneEnabled, 2, 0)
        Call(SetZoneEnabled, 3, 0)
        Call(SetZoneEnabled, 4, 0)
        Call(SetZoneEnabled, 5, 0)
        Call(SetZoneEnabled, 0, 0)
        Set(LVar1, 0)
    CaseEq(1)
        Call(SetZoneEnabled, 11, 0)
        Call(SetZoneEnabled, 9, 0)
        Call(SetZoneEnabled, 10, 0)
        Call(SetZoneEnabled, 8, 0)
        Call(SetZoneEnabled, 2, 0)
        Call(SetZoneEnabled, 3, 0)
        Call(SetZoneEnabled, 4, 0)
        Call(SetZoneEnabled, 5, 0)
        Call(SetZoneEnabled, 0, 1)
        Set(LVar1, 1)
    CaseEq(2)
        Call(SetZoneEnabled, 11, 0)
        Call(SetZoneEnabled, 9, 0)
        Call(SetZoneEnabled, 10, 0)
        Call(SetZoneEnabled, 8, 0)
        Call(SetZoneEnabled, 2, 1)
        Call(SetZoneEnabled, 3, 1)
        Call(SetZoneEnabled, 4, 1)
        Call(SetZoneEnabled, 5, 1)
        Call(SetZoneEnabled, 0, 0)
        Set(LVar1, 2)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_mim_13_Script_UpdateCameraZones = {
    Switch(LVar1)
    CaseEq(0)
        Call(SetZoneEnabled, 11, 1)
        Call(SetZoneEnabled, 9, 1)
        Call(SetZoneEnabled, 10, 1)
        Call(SetZoneEnabled, 8, 1)
        Call(SetZoneEnabled, 2, 0)
        Call(SetZoneEnabled, 3, 0)
        Call(SetZoneEnabled, 4, 0)
        Call(SetZoneEnabled, 5, 0)
        Call(SetZoneEnabled, 0, 0)
        Set(LVar1, 0)
    CaseEq(1)
        Call(SetZoneEnabled, 11, 0)
        Call(SetZoneEnabled, 9, 0)
        Call(SetZoneEnabled, 10, 0)
        Call(SetZoneEnabled, 8, 0)
        Call(SetZoneEnabled, 2, 0)
        Call(SetZoneEnabled, 3, 0)
        Call(SetZoneEnabled, 4, 0)
        Call(SetZoneEnabled, 5, 0)
        Call(SetZoneEnabled, 0, 1)
        Set(LVar1, 1)
    CaseEq(2)
        Call(SetZoneEnabled, 11, 0)
        Call(SetZoneEnabled, 9, 0)
        Call(SetZoneEnabled, 10, 0)
        Call(SetZoneEnabled, 8, 0)
        Call(SetZoneEnabled, 2, 1)
        Call(SetZoneEnabled, 3, 1)
        Call(SetZoneEnabled, 4, 1)
        Call(SetZoneEnabled, 5, 1)
        Call(SetZoneEnabled, 0, 0)
        Set(LVar1, 2)
    EndSwitch
    Return
    End
};

NpcData TTYD64_mim_13_NpcGroup_Fuzzy[] = {
    {
        .id = 0,
        .settings = &TTYD64_mim_13_NpcSettings_Fuzzy,
        .pos = { 270.0f, 0.0f, 200.0f },
        .flags = 0x00000000,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 132, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 270, .centerPos.y = 0, .centerPos.z = 200, .wanderSize.x = 100, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 400, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x002B0102, .walk = 0x002B0102, .run = 0x002B0103, .chase = 0x002B0103, .anim_4 = 0x002B0101, .anim_5 = 0x002B0101, .death = 0x002B0108, .hit = 0x002B0108, .anim_8 = 0x002B0103, .anim_9 = 0x002B0103, .anim_A = 0x002B0103, .anim_B = 0x002B0103, .anim_C = 0x002B0103, .anim_D = 0x002B0103, .anim_E = 0x002B0103, .anim_F = 0x002B0103 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_mim_13_Script_802441E0 = {
    IfEq(GameFlag(924), 0)
        Set(GameFlag(924), 1)
        Set(AreaByte(1), 2)
        Set(LVar1, 2)
        Set(LVar2, -10)
    Else
        Set(GameFlag(924), 0)
        Set(AreaByte(1), 0)
        Set(LVar1, 0)
        Set(LVar2, 10)
    EndIf
    ExecWait(TTYD64_mim_13_Script_InitCameraZones)
    Exec(TTYD64_mim_13_Script_802437D4)
    Call(SetCamSpeed, 0, Float(90.0))
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
    Call(PanToTarget, 0, 0, 1)
    Wait(1)
    Call(PanToTarget, 0, 0, 0)
    BindTrigger(TTYD64_mim_13_Script_80243FF0, 256, 32, 1, 0)
    BindTrigger(TTYD64_mim_13_Script_8024406C, 256, 36, 1, 0)
    BindTrigger(TTYD64_mim_13_Script_80244164, 256, 38, 1, 0)
    BindTrigger(TTYD64_mim_13_Script_802440E8, 256, 34, 1, 0)
    Return
    End
};

EvtScript TTYD64_mim_13_Script_Main_EnterWalk = {
    Set(GameByte(425), 12)
    Call(SetSpriteShading, 0x70007)
    Call(SetCamPerspective, 0, 3, 25, 16, 650)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Set(AreaByte(2), GameByte(171))
    Call(GetMapID, GameByte(171))
    ExecWait(TTYD64_mim_13_Script_802441E0)
    Call(MakeNpcs, 1, (Bytecode) TTYD64_mim_13_NpcGroupList_Enemies)
    ExecWait(TTYD64_mim_13_Script_MakeEntities)
    Set(LVar0, (Bytecode) TTYD64_mim_13_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Exec(TTYD64_mim_13_Script_SetupMusic)
    Call(mim_01_SetForeverForestFog)
    Thread
        Label(0)
        Call(WaitForCam, 0, Float(1.0))
        Call(mim_03_GetPlayerDistFromMapCenter)
        IfLt(LVar0, 350)
            Call(SetCamSpeed, 0, Float(1.0))
        Else
            Call(SetCamSpeed, 0, Float(3.0))
        EndIf
        Goto(0)
    EndThread
    Return
    End
};

EvtScript TTYD64_mim_13_Script_802437D4 = {
    Call(ParentColliderToModel, 32, 120)
    Call(RotateGroup, 122, LVar2, 0, 1, 0)
    Call(UpdateColliderTransform, 32)
    Call(ParentColliderToModel, 36, 126)
    Call(RotateGroup, 128, LVar2, 0, 1, 0)
    Call(UpdateColliderTransform, 36)
    Call(ParentColliderToModel, 34, 123)
    Call(RotateGroup, 125, LVar2, 0, 1, 0)
    Call(UpdateColliderTransform, 34)
    Call(ParentColliderToModel, 38, 129)
    Call(RotateGroup, 131, LVar2, 0, 1, 0)
    Call(UpdateColliderTransform, 38)
    Return
    End
};

EvtScript TTYD64_mim_13_Script_ResetLogsRotation = {
    Call(RotateGroup, 122, 0, 0, 1, 0)
    Call(UpdateColliderTransform, 32)
    Call(RotateGroup, 128, 0, 0, 1, 0)
    Call(UpdateColliderTransform, 36)
    Call(RotateGroup, 125, 0, 0, 1, 0)
    Call(UpdateColliderTransform, 34)
    Call(RotateGroup, 131, 0, 0, 1, 0)
    Call(UpdateColliderTransform, 38)
    Return
    End
};

u8 TTYD64_mim_13_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x2C, 0x4F, 0x4F, 0x4B, 0x0C, 0xF7, 0x29, 0x07,
    0x4D, 0xF7, 0x53, 0x49, 0x43, 0x4B, 0xF7, 0x4F, 0x46, 0xF7, 0x54, 0x48,
    0x49, 0x53, 0xF7, 0x46, 0x4F, 0x52, 0x45, 0x53, 0x54, 0x0C, 0xF7, 0x41,
    0x4C, 0x4C, 0xF0, 0x52, 0x49, 0x47, 0x48, 0x54, 0x1F, 0xF7, 0x2C, 0x45,
    0x54, 0x07, 0x53, 0xF7, 0x47, 0x45, 0x54, 0xF7, 0x4F, 0x55, 0x54, 0xF7,
    0x4F, 0x46, 0xF7, 0x48, 0x45, 0x52, 0x45, 0x0E, 0xF0, 0xF1, 0xFB, 0x29,
    0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x43, 0x41, 0x52, 0x45, 0xF7,
    0x48, 0x4F, 0x57, 0xF7, 0x4D, 0x41, 0x4E, 0x59, 0xF7, 0x49, 0x4D, 0x50,
    0x4F, 0x52, 0x54, 0x41, 0x4E, 0x54, 0xF0, 0x54, 0x48, 0x49, 0x4E, 0x47,
    0x53, 0xF7, 0x41, 0x52, 0x45, 0xF7, 0x48, 0x49, 0x44, 0x44, 0x45, 0x4E,
    0xF7, 0x49, 0x4E, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7, 0x46, 0x4F, 0x52,
    0x45, 0x53, 0x54, 0x0C, 0xF0, 0x29, 0xF7, 0x43, 0x41, 0x4E, 0x07, 0x54,
    0xF7, 0x53, 0x50, 0x45, 0x4E, 0x44, 0xF7, 0x41, 0x4E, 0x4F, 0x54, 0x48,
    0x45, 0x52, 0xF7, 0x49, 0x4E, 0x53, 0x54, 0x41, 0x4E, 0x54, 0xF7, 0x49,
    0x4E, 0xF0, 0x54, 0x48, 0x45, 0xF7, 0x46, 0x52, 0x45, 0x41, 0x4B, 0x59,
    0xF7, 0x50, 0x4C, 0x41, 0x43, 0x45, 0x01, 0xF0, 0xF1, 0xFD
};

EvtScript TTYD64_mim_13_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_mim_13_Script_Exit_Entry0, 0x80000, 7, 1, 0)
    BindTrigger(TTYD64_mim_13_Script_Exit_Entry1, 0x80000, 22, 1, 0)
    BindTrigger(TTYD64_mim_13_Script_Exit_Entry2, 0x80000, 17, 1, 0)
    BindTrigger(TTYD64_mim_13_Script_Exit_Entry3, 0x80000, 12, 1, 0)
    Return
    End
};

EvtScript TTYD64_mim_13_Script_80243FF0 = {
    Call(DisablePlayerInput, 1)
    Set(LVar7, 0)
    Set(LVar8, 70)
    Set(LVar9, 32)
    Set(LVarA, 122)
    ExecWait(TTYD64_mim_13_Script_MoveLog)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_mim_13_Script_8024406C = {
    Call(DisablePlayerInput, 1)
    Set(LVar7, 0)
    Set(LVar8, -70)
    Set(LVar9, 36)
    Set(LVarA, 128)
    ExecWait(TTYD64_mim_13_Script_MoveLog)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_mim_13_Script_802440E8 = {
    Call(DisablePlayerInput, 1)
    Set(LVar7, -70)
    Set(LVar8, 0)
    Set(LVar9, 34)
    Set(LVarA, 125)
    ExecWait(TTYD64_mim_13_Script_MoveLog)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_mim_13_Script_80244164 = {
    Call(DisablePlayerInput, 1)
    Set(LVar7, 70)
    Set(LVar8, 0)
    Set(LVar9, 38)
    Set(LVarA, 131)
    ExecWait(TTYD64_mim_13_Script_MoveLog)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_mim_13_Script_Exit_Entry3 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 3)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "mim_03", 3)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_mim_13_Script_Exit_Entry2 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 2)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "mim_01", 1)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_mim_13_Script_Exit_Entry1 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 1)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "mim_01", 1)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_mim_13_Script_Exit_Entry0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "mim_01", 1)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_mim_13_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_RedBlock), 0, 92, 0, 45, 397, 0x80000000)
    Call(AssignBlockFlag, GameFlag(5032))
    Return
    End
};

EntryList TTYD64_mim_13_EntryList = {
    { 0.0f, 0.0f, -530.0f, 180.0f },
    { -530.0f, 0.0f, 0.0f, 90.0f },
    { 0.0f, 0.0f, 530.0f, 0.0f },
    { 530.0f, 0.0f, 0.0f, 270.0f },
};

MapSettings TTYD64_mim_13_Header = {
    .main = &TTYD64_mim_13_Script_Main_EnterWalk,
    .entryList = &TTYD64_mim_13_EntryList,
    .entryCount = 4,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_mim_13_GetTattle },
};

EvtScript TTYD64_mim_13_Script_NpcAI_Fuzzy = {
    Call(SetNpcFlagBits, -1, 64, 1)
    Call(isk_05_HoppingAI_Main, Ref(TTYD64_mim_13_AISettings_Fuzzy), 1)
    Return
    End
};

EvtScript TTYD64_mim_13_Script_SetupMusic = {
    Call(SetMusic, 0, 26, 0, 8)
    Call(PlayAmbientSounds, 0)
    Return
    End
};

MobileAISettings TTYD64_mim_13_AISettings_Fuzzy = {
    .moveSpeed = 1.0f,
    .moveTime = 30,
    .waitTime = 10,
    .alertRadius = 120.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 5,
    .chaseSpeed = 4.5f,
    .chaseTurnRate = 90,
    .chaseUpdateInterval = 5,
    .chaseRadius = 160.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_mim_13_NpcSettings_Fuzzy = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = &TTYD64_mim_13_Script_NpcAI_Fuzzy,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 11,
    .actionFlags = 0,
};

NpcGroupList TTYD64_mim_13_NpcGroupList_Enemies = {
    { .npcCount = 1, .npcs = TTYD64_mim_13_NpcGroup_Fuzzy, .battle = 0x0D00, .stage = 1 },
    {},
};

MapConfig TTYD64_mapcfg_mim_13 = {
    .id = "mim_13",
    .settings = &TTYD64_mim_13_Header,
    .bgName = "obk_bg",
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 2,
};
// clang-format on

void TTYD64_nm_Install_mim_13(void) {
    TTYD64_mim_13_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_mim_13_String_Tattle);
}
