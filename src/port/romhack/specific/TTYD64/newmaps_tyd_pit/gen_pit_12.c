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

extern EvtScript TTYD64_pit_12_Script_EnterTopPipe;
extern EvtScript TTYD64_pit_12_Script_ExitHorizontalPipe;
extern EvtScript TTYD64_pit_12_Script_ExitVerticalPipe;
extern NpcData TTYD64_pit_12_NpcGroup_Bowser[];
extern EvtScript TTYD64_pit_12_Script_Cutscene_Start;
extern u8 TTYD64_pit_12_String_Tattle[];
extern EvtScript TTYD64_pit_12_Script_GiveItem;
extern EvtScript TTYD64_pit_12_Script_Main;
extern EvtScript TTYD64_pit_12_Script_MakeEntities;
extern EvtScript TTYD64_pit_12_Script_NPC_Outcome;
extern EvtScript TTYD64_pit_12_Script_NPC_Idle;
extern EvtScript TTYD64_pit_12_Script_EnterMap;
extern EvtScript TTYD64_pit_12_Script_ShowGotItem;
extern EvtScript TTYD64_pit_12_Script_Exit0;
extern EvtScript TTYD64_pit_12_Script_InitNPC_Bowser;
extern EvtScript TTYD64_pit_12_Script_OpenChest;
extern EvtScript TTYD64_pit_12_Script_ReadSign_Entity_Sign;
extern MapSettings TTYD64_pit_12_Header;
extern EvtScript TTYD64_pit_12_Script_SetupMusic;
extern NpcSettings TTYD64_pit_12_NPCSettings_NPC;
s32 TTYD64_pit_12_Function_Init(void);
extern EvtScript TTYD64_pit_12_Script_CreateExitTriggers;
extern u8 TTYD64_pit_12_String_ReadSign_Entity_Sign[];
extern EvtScript TTYD64_pit_12_Script_GotoMap_Exit0;
extern EntryList TTYD64_pit_12_EntryList;
extern NpcGroupList TTYD64_pit_12_NpcGroupList_pit12;

// clang-format off
static s32 TTYD64_pit_12_GetTattleMsg;

static s32 TTYD64_pit_12_GetTattle(void) {
    return TTYD64_pit_12_GetTattleMsg;
}

EvtScript TTYD64_pit_12_Script_EnterTopPipe = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(HidePlayerShadow, 1)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Call(DisablePartnerAI, 0)
        Call(EnableNpcShadow, -4, 0)
        Call(SetNpcFlagBits, -4, 2, 1)
        Call(SetNpcPos, -4, 0, LVarA, 0)
    EndIf
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
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(SetPlayerImgFXFlags, 256)
    Call(UpdatePlayerImgFX, 0x10000, 5, 2, 1, 1, 0)
    Wait(4)
    Call(PlaySound, 355)
    Loop(40)
        Sub(LVar1, 1)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Wait(1)
    Call(UpdatePlayerImgFX, 0x10000, 0, 0, 0, 0, 0)
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Call(HidePlayerShadow, 0)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Wait(4)
        Call(GetPlayerPos, LVar4, LVar5, LVar6)
        Call(SetNpcPos, -4, LVar4, LVar5, LVar6)
        Call(SetNpcFlagBits, -4, 2, 0)
        Call(EnablePartnerAI)
        Call(EnableNpcShadow, -4, 1)
    EndIf
    Exec(LVarC)
    Return
    End
};

EvtScript TTYD64_pit_12_Script_ExitHorizontalPipe = {
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

EvtScript TTYD64_pit_12_Script_ExitVerticalPipe = {
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

NpcData TTYD64_pit_12_NpcGroup_Bowser[] = {
    {
        .id = 0,
        .settings = &TTYD64_pit_12_NPCSettings_NPC,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x81006001,
        .init = TTYD64_pit_12_Script_InitNPC_Bowser,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00660004, .walk = 0x00660002, .run = 0x00660003, .chase = 0x00660003, .anim_4 = 0x00660004, .anim_5 = 0x00660004, .death = 0x0066000A, .hit = 0x0066000A, .anim_8 = 0x00660003, .anim_9 = 0x00660003, .anim_A = 0x00660003, .anim_B = 0x00660003, .anim_C = 0x00660003, .anim_D = 0x00660003, .anim_E = 0x00660003, .anim_F = 0x00660003 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_pit_12_Script_Cutscene_Start = {
    Exec(TTYD64_pit_12_Script_CreateExitTriggers)
    Call(DisablePlayerInput, 1)
    Wait(15)
    Exec(TTYD64_MovePartnerBehindMario)
    Call(GetPlayerPos, LVar3, LVar4, LVar5)
    Add(LVar3, 255)
    Call(TranslateGroup, 59, LVar3, LVar4, LVar5)
    Call(PlaySound, 958)
    Set(LVar6, LVar3)
    Add(LVar3, -155)
    Call(MakeLerp, LVar6, LVar3, 50, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateGroup, 59, LVar0, LVar4, LVar5)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Wait(10)
    Call(SetNpcVar, 0, 0, 1)
    Return
    End
};

u8 TTYD64_pit_12_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x26, 0x49, 0x4E, 0x41, 0x4C, 0x4C, 0x59, 0x0E,
    0x0E, 0x0E, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x4C, 0x41, 0x53, 0x54, 0xF7,
    0x46, 0x4C, 0x4F, 0x4F, 0x52, 0xF7, 0x4F, 0x46, 0xF7, 0x54, 0x48, 0x45,
    0xF0, 0x50, 0x49, 0x54, 0x0C, 0xF7, 0x46, 0x4C, 0x4F, 0x4F, 0x52, 0xF7,
    0x11, 0x10, 0x10, 0x01, 0xF0, 0xF1, 0xFB, 0x22, 0x55, 0x54, 0x0C, 0xF7,
    0x54, 0x48, 0x45, 0x52, 0x45, 0xF7, 0x57, 0x41, 0x53, 0x4E, 0x07, 0x54,
    0xF7, 0x45, 0x56, 0x45, 0x4E, 0xF7, 0x41, 0xF7, 0x50, 0x45, 0x52, 0x53,
    0x4F, 0x4E, 0xF0, 0x44, 0x4F, 0x57, 0x4E, 0xF7, 0x48, 0x45, 0x52, 0x45,
    0x0C, 0xF7, 0x42, 0x55, 0x54, 0xF7, 0x41, 0xF7, 0x52, 0x4F, 0x42, 0x4F,
    0x54, 0x0C, 0xF7, 0x4D, 0x41, 0x59, 0x42, 0x45, 0xF7, 0x49, 0x54, 0xF7,
    0x57, 0x41, 0x53, 0xF0, 0x53, 0x4F, 0x4D, 0x45, 0xF7, 0x4B, 0x49, 0x4E,
    0x44, 0xF7, 0x4F, 0x46, 0xF7, 0x53, 0x45, 0x43, 0x55, 0x52, 0x49, 0x54,
    0x59, 0xF7, 0x44, 0x45, 0x56, 0x49, 0x43, 0x45, 0x1F, 0xF0, 0xF1, 0xFB,
    0x29, 0xF7, 0x57, 0x4F, 0x4E, 0x44, 0x45, 0x52, 0xF7, 0x57, 0x48, 0x41,
    0x54, 0xF7, 0x49, 0x54, 0xF7, 0x50, 0x52, 0x4F, 0x54, 0x45, 0x43, 0x54,
    0x45, 0x44, 0x0C, 0xF7, 0x29, 0xF7, 0x48, 0x4F, 0x50, 0x45, 0xF0, 0x49,
    0x54, 0x07, 0x53, 0xF7, 0x57, 0x4F, 0x52, 0x54, 0x48, 0xF7, 0x49, 0x54,
    0x01, 0xF1, 0xFD
};

EvtScript TTYD64_pit_12_Script_GiveItem = {
    Set(LVar0, LVarA)
    IfNe(LVarA, 0)
        ExecWait(TTYD64_pit_12_Script_ShowGotItem)
    EndIf
    Switch(LVarB)
    CaseEq(0)
        Call(AddItem, LVarA, LVar0)
    CaseEq(1)
        Call(TTYD64_tp_AddKeyItem, LVarA)
    CaseEq(2)
        Call(TTYD64_tp_AddBadge, LVarA, LVar0)
    EndSwitch
    Wait(15)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_pit_12_Script_Main = {
    Set(GameByte(425), 2)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Set(AreaByte(0), 100)
    Call(MakeNpcs, 1, (Bytecode) TTYD64_pit_12_NpcGroupList_pit12)
    Exec(TTYD64_pit_12_Script_MakeEntities)
    Exec(TTYD64_pit_12_Script_SetupMusic)
    Exec(TTYD64_pit_12_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_pit_12_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_Signpost), -329, -9, -160, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_pit_12_Script_ReadSign_Entity_Sign)
    Call(MakeEntity, Ref(Entity_GiantChest), 284, 0, -53, 0, 0x80000000)
    Set(MapVar(0), 374)
    Set(MapVar(1), 2)
    Call(AssignChestFlag, GameFlag(4733))
    Call(AssignScript, (Bytecode) TTYD64_pit_12_Script_OpenChest)
    Return
    End
};

EvtScript TTYD64_pit_12_Script_NPC_Outcome = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
    CaseDefault
        Call(SetSelfEnemyFlagBits, 4, 1)
        Call(EnableGroup, 59, 0)
        Call(DisablePlayerInput, 0)
        Return
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_pit_12_Script_NPC_Idle = {
    Loop(0)
        Call(GetSelfVar, 0, LVar0)
        IfEq(LVar0, 1)
            Call(SetSelfVar, 0, 0)
            Call(StartBossBattle, 9)
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_pit_12_Script_EnterMap = {
    Set(LVarA, 0)
    Set(LVarB, 0)
    Set(LVarC, (Bytecode) TTYD64_pit_12_Script_Cutscene_Start)
    Exec(TTYD64_pit_12_Script_EnterTopPipe)
    Set(GameFlag(4101), 1)
    Return
    End
};

EvtScript TTYD64_pit_12_Script_ShowGotItem = {
    SetGroup(0)
    Call(SetTimeFreezeMode, 2)
    Call(ShowGotItem, LVar0, 1, 0)
    Call(SetTimeFreezeMode, 0)
    Return
    Return
    End
};

EvtScript TTYD64_pit_12_Script_Exit0 = {
    SetGroup(27)
    Set(LVarA, 1)
    Set(LVarB, 14)
    Set(LVarC, (Bytecode) TTYD64_pit_12_Script_GotoMap_Exit0)
    ExecWait(TTYD64_pit_12_Script_ExitHorizontalPipe)
    Return
    End
};

EvtScript TTYD64_pit_12_Script_InitNPC_Bowser = {
    Call(SetSelfVar, 0, 0)
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_pit_12_Script_NPC_Idle)
    Call(BindNpcDefeat, -1, (Bytecode) TTYD64_pit_12_Script_NPC_Outcome)
    Return
    End
};

EvtScript TTYD64_pit_12_Script_OpenChest = {
    Set(GameFlag(4101), 0)
    Set(LVarA, MapVar(0))
    Set(LVarB, MapVar(1))
    ExecWait(TTYD64_pit_12_Script_GiveItem)
    Return
    End
};

EvtScript TTYD64_pit_12_Script_ReadSign_Entity_Sign = {
    Call(DisablePlayerInput, 1)
    Call(ShowMessageAtScreenPos, (Bytecode) TTYD64_pit_12_String_ReadSign_Entity_Sign, 160, 40)
    Call(DisablePlayerInput, 0)
    Return
    End
};

MapSettings TTYD64_pit_12_Header = {
    .main = TTYD64_pit_12_Script_Main,
    .entryList = &TTYD64_pit_12_EntryList,
    .entryCount = 2,
    .background = NULL,
    .tattle = { .get = TTYD64_pit_12_GetTattle },
};

EvtScript TTYD64_pit_12_Script_SetupMusic = {
    Call(FadeOutMusic, 0, 500)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

NpcSettings TTYD64_pit_12_NPCSettings_NPC = {
    .defaultAnim = 0x00000000,
    .height = 24,
    .radius = 40,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = NULL,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 13,
    .actionFlags = 0,
};

s32 TTYD64_pit_12_Function_Init(void) {
    sprintf(wMapTexName, "tik_tex");
    return false;
}

EvtScript TTYD64_pit_12_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_pit_12_Script_Exit0, 64, 14, 1, 0)
    Return
    End
};

u8 TTYD64_pit_12_String_ReadSign_Entity_Sign[] = {
    0xFF, 0x09, 0xFC, 0x07, 0xFF, 0x29, 0xFF, 0xFF, 0x13, 0x0F, 0x92, 0xF7,
    0x22, 0x41, 0x43, 0x4B, 0xF7, 0x54, 0x4F, 0xF7, 0x54, 0x48, 0x45, 0xF7,
    0x45, 0x4E, 0x54, 0x52, 0x41, 0x4E, 0x43, 0x45, 0x0E, 0xFF, 0x0A, 0xF1,
    0xFD
};

EvtScript TTYD64_pit_12_Script_GotoMap_Exit0 = {
    Call(GotoMap, (Bytecode) "pit_00", 2)
    Return
    End
};

EntryList TTYD64_pit_12_EntryList = {
    { -120.0f, 279.0f, -76.0f, -270.0f },
    { -302.0f, -1.0f, -211.0f, -270.0f },
};

NpcGroupList TTYD64_pit_12_NpcGroupList_pit12 = {
    { .npcCount = 1, .npcs = TTYD64_pit_12_NpcGroup_Bowser, .battle = 0x3A00, .stage = 0 },
    {},
};

MapConfig TTYD64_mapcfg_pit_12 = {
    .id = "pit_12",
    .settings = &TTYD64_pit_12_Header,
    .bgName = NULL,
    .init = TTYD64_pit_12_Function_Init,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_tp_Install_pit_12(void) {
    TTYD64_tp_BindMessage(TTYD64_pit_12_Script_ReadSign_Entity_Sign, TTYD64_pit_12_String_ReadSign_Entity_Sign);
    TTYD64_pit_12_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_pit_12_String_Tattle);
}
