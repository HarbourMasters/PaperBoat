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
API_CALLABLE(BasicAI_Main);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerJump);
API_CALLABLE(ResetCam);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetCamTarget);
API_CALLABLE(SetMusic);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerJumpscale);
API_CALLABLE(SetTexPanner);
API_CALLABLE(UseExitHeading);
API_CALLABLE(UseSettingsFrom);

extern EvtScript TTYD64_tik_27_Script_PuzzleSolved;
extern EvtScript TTYD64_tik_27_Script_RedSwitch;
extern NpcData TTYD64_tik_27_NpcGroup_SpikedGoomba[];
extern EvtScript TTYD64_tik_27_Script_MakeEntities;
extern EvtScript TTYD64_tik_27_Script_StartTimer;
extern EvtScript TTYD64_tik_27_Script_SetupTexturePan;
extern EvtScript TTYD64_tik_27_Script_Main;
extern EvtScript TTYD64_tik_27_Script_ScriptedSpring_Entity_Spring;
extern EvtScript TTYD64_tik_27_Script_TexturePan_Update;
extern u8 TTYD64_tik_27_String_Tattle[];
extern EvtScript TTYD64_tik_27_Script_ScriptedSpring_FollowCam;
extern EvtScript TTYD64_tik_27_Script_Exit_Entry0;
extern EvtScript TTYD64_tik_27_Script_Switch3;
extern EvtScript TTYD64_tik_27_Script_Switch2;
extern EvtScript TTYD64_tik_27_Script_Switch1;
extern EvtScript TTYD64_tik_27_Script_EnterMap;
extern MapSettings TTYD64_tik_27_Header;
extern EvtScript TTYD64_tik_27_Script_Entity_Shine1;
extern EvtScript TTYD64_tik_27_Script_SetupMusic;
extern MobileAISettings TTYD64_tik_27_AISettings_80241C90;
extern NpcSettings TTYD64_tik_27_NpcSettings_80241CE0;
extern EvtScript TTYD64_tik_27_Script_CreateExitTriggers;
extern EvtScript TTYD64_tik_27_Script_NpcAI_80241CC0;
extern NpcGroupList TTYD64_tik_27_NpcGroupList_tik27;
extern EntryList TTYD64_tik_27_EntryList;

// clang-format off
static s32 TTYD64_tik_27_GetTattleMsg;

static s32 TTYD64_tik_27_GetTattle(void) {
    return TTYD64_tik_27_GetTattleMsg;
}

EvtScript TTYD64_tik_27_Script_PuzzleSolved = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(DisablePartnerAI, 1)
    Call(PlaySound, 11)
    Set(GameFlag(4545), 1)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(SetCamSpeed, 0, Float(7.0))
    Call(SetPanTarget, 0, 186, 99, -198)
    Call(PanToTarget, 0, 0, 1)
    Wait(10)
    Set(LVar0, 186)
    Set(LVar1, 99)
    Set(LVar2, -198)
    Add(LVar1, 200)
    Call(MakeItemEntity, 323, LVar0, LVar1, LVar2, 13, GameFlag(4546))
    Wait(50)
    Set(LVar2, -198)
    Add(LVar2, 8)
    Call(PlaySound, 717)
    Call(PlayEffect_impl, 1, 291, 56, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Set(LVar2, 42)
    Add(LVar2, 8)
    Call(PlaySound, 717)
    Call(PlayEffect_impl, 1, -138, 98, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Set(LVar2, 42)
    Add(LVar2, 8)
    Call(PlaySound, 717)
    Call(PlayEffect_impl, 1, 285, -2, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Wait(5)
    Call(TTYD64_GetEntityPointer, 1, LVar0)
    Call(TTYD64_WritePtrField, LVar0, TTYD64_F_ENTITY_4C_4U, 0xC47A0000)
    Call(TTYD64_GetEntityPointer, 2, LVar0)
    Call(TTYD64_WritePtrField, LVar0, TTYD64_F_ENTITY_4C_4U, 0xC47A0000)
    Call(TTYD64_GetEntityPointer, 3, LVar0)
    Call(TTYD64_WritePtrField, LVar0, TTYD64_F_ENTITY_4C_4U, 0xC47A0000)
    Call(SetCamSpeed, 0, Float(1.0))
    Call(ResetCam, 0, Float(5.0))
    Wait(15)
    Call(DisablePlayerInput, 0)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePartnerAI, 0)
    Return
    End
};

EvtScript TTYD64_tik_27_Script_RedSwitch = {
    Set(LVar6, LVar0)
    Set(LVar7, LVar1)
    Set(LVar8, LVar2)
    IfEq(MapVar(0), LVar6)
        Return
    EndIf
    IfNe(MapVar(1), 0)
        KillThread(MapVar(1))
        Set(MapVar(1), 0)
    EndIf
    IfEq(MapVar(0), LVar8)
        Set(LVar5, 1)
    Else
        Set(LVar5, 0)
    EndIf
    IfEq(LVar5, 1)
        Call(PlaySound, 540)
        Switch(LVar6)
        CaseEq(1)
            Set(MapFlag(0), 1)
        CaseEq(2)
            Set(MapFlag(1), 1)
        CaseEq(3)
            Set(MapFlag(2), 1)
        EndSwitch
        Set(MapVar(0), LVar6)
        Set(LVar0, MapFlag(0))
        Add(LVar0, MapFlag(1))
        Add(LVar0, MapFlag(2))
        IfGe(LVar0, 3)
            ExecWait(TTYD64_tik_27_Script_PuzzleSolved)
        Else
            ExecGetTID(TTYD64_tik_27_Script_StartTimer, MapVar(1))
        EndIf
    Else
        Call(PlaySound, 541)
        Set(MapFlag(0), 0)
        Set(MapFlag(1), 0)
        Set(MapFlag(2), 0)
        Set(MapVar(0), 0)
    EndIf
    Return
    End
};

NpcData TTYD64_tik_27_NpcGroup_SpikedGoomba[] = {
    {
        .id = 0,
        .settings = &TTYD64_tik_27_NpcSettings_80241CE0,
        .pos = { 199.0f, -2.0f, -38.0f },
        .flags = 0x00002C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 32, .itemDrops = { { 154, 5, 0 }, { 143, 5, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 1, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 199, .centerPos.y = -2, .centerPos.z = -38, .wanderSize.x = 20, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 150, .detectPos.y = -1, .detectPos.z = -30, .detectSize.x = 190, .detectSize.z = 112, .detectShape = 1, .isFlying = 1 } },
        .animations = { .idle = 0x00270101, .walk = 0x00270103, .run = 0x00270103, .chase = 0x00270103, .anim_4 = 0x00270103, .anim_5 = 0x00270101, .death = 0x00270105, .hit = 0x00270105, .anim_8 = 0x00270100, .anim_9 = 0x00270100, .anim_A = 0x00270100, .anim_B = 0x00270100, .anim_C = 0x00270100, .anim_D = 0x00270100, .anim_E = 0x00270100, .anim_F = 0x00270100 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_tik_27_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_ScriptSpring), -28, -2, 41, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_tik_27_Script_ScriptedSpring_Entity_Spring)
    IfEq(GameFlag(4545), 0)
        Call(MakeEntity, Ref(Entity_RedSwitch), 291, 56, -198, -180, 0x80000000)
        Call(AssignScript, (Bytecode) TTYD64_tik_27_Script_Switch1)
        Call(MakeEntity, Ref(Entity_RedSwitch), -138, 98, 42, -180, 0x80000000)
        Call(AssignScript, (Bytecode) TTYD64_tik_27_Script_Switch2)
        Call(MakeEntity, Ref(Entity_RedSwitch), 285, -2, 42, -180, 0x80000000)
        Call(AssignScript, (Bytecode) TTYD64_tik_27_Script_Switch3)
    Else
        Call(MakeItemEntity, 323, 186, 99, -198, 17, GameFlag(4546))
    EndIf
    Call(MakeEntity, Ref(Entity_SuperBlock), 184, 60, -95, 0, 0x80000000)
    Set(MapVar(2), LVar0)
    Call(AssignBlockFlag, GameFlag(4549))
    Call(AssignScript, (Bytecode) TTYD64_tik_27_Script_Entity_Shine1)
    Return
    End
};

EvtScript TTYD64_tik_27_Script_StartTimer = {
    Set(LVar5, 0)
    Loop(LVar7)
        Add(LVar5, 1)
        Set(LVar0, 5)
        Set(LVar1, LVar7)
        Div(LVar1, 10)
        Add(LVar0, LVar1)
        IfGe(LVar5, LVar0)
            Set(LVar5, 0)
            Call(PlaySound, 5)
        EndIf
        Wait(1)
    EndLoop
    Set(MapFlag(0), 0)
    Set(MapFlag(1), 0)
    Set(MapFlag(2), 0)
    Set(MapVar(0), 0)
    Set(MapVar(1), 0)
    Call(PlaySound, 541)
    Return
    End
};

EvtScript TTYD64_tik_27_Script_SetupTexturePan = {
    Call(SetTexPanner, 6, 1)
    Thread
        Set(LVar0, 1)
        Set(LVar1, 50)
        Set(LVar2, 200)
        Set(LVar3, 110)
        Set(LVar4, 500)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_tik_27_Script_TexturePan_Update)
    EndThread
    Return
    End
};

EvtScript TTYD64_tik_27_Script_Main = {
    Set(GameByte(425), 2)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_tik_27_Script_MakeEntities)
    Exec(TTYD64_tik_27_Script_SetupMusic)
    Exec(TTYD64_tik_27_Script_SetupTexturePan)
    Exec(TTYD64_tik_27_Script_EnterMap)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_tik_27_NpcGroupList_tik27)
    Set(LVar0, (Bytecode) TTYD64_tik_27_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

EvtScript TTYD64_tik_27_Script_ScriptedSpring_Entity_Spring = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerActionState, 6)
    Wait(1)
    ExecGetTID(TTYD64_tik_27_Script_ScriptedSpring_FollowCam, LVarA)
    Call(SetPlayerJumpscale, Float(0.7001953125))
    Call(PlayerJump, -85, 98, 42, 30)
    KillThread(LVarA)
    Call(SetPlayerActionState, 0)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_tik_27_Script_TexturePan_Update = {
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

u8 TTYD64_tik_27_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x29, 0x54, 0xF7, 0x53, 0x45, 0x45, 0x4D, 0x53,
    0xF7, 0x54, 0x48, 0x41, 0x54, 0xF7, 0x57, 0x45, 0xF7, 0x48, 0x41, 0x56,
    0x45, 0xF7, 0x54, 0x4F, 0xF7, 0x50, 0x52, 0x45, 0x53, 0x53, 0xF0, 0x54,
    0x48, 0x4F, 0x53, 0x45, 0xF7, 0x42, 0x55, 0x54, 0x54, 0x4F, 0x4E, 0x53,
    0xF7, 0x49, 0x4E, 0xF7, 0x41, 0xF7, 0x53, 0x50, 0x45, 0x43, 0x49, 0x46,
    0x49, 0x43, 0xF7, 0x4F, 0x52, 0x44, 0x45, 0x52, 0x0C, 0xF0, 0x29, 0xF7,
    0x57, 0x4F, 0x4E, 0x44, 0x45, 0x52, 0xF7, 0x57, 0x48, 0x49, 0x43, 0x48,
    0xF7, 0x4F, 0x4E, 0x45, 0xF7, 0x49, 0x53, 0xF7, 0x54, 0x48, 0x45, 0xF7,
    0x43, 0x4F, 0x52, 0x52, 0x45, 0x43, 0x54, 0xF0, 0x4F, 0x4E, 0x45, 0x1F,
    0xF1, 0xFD
};

EvtScript TTYD64_tik_27_Script_ScriptedSpring_FollowCam = {
    Loop(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetCamTarget, 0, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_tik_27_Script_Exit_Entry0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "tik_10", 2)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_tik_27_Script_Switch3 = {
    Set(LVar0, 3)
    Set(LVar1, 160)
    Set(LVar2, 0)
    ExecWait(TTYD64_tik_27_Script_RedSwitch)
    Return
    End
};

EvtScript TTYD64_tik_27_Script_Switch2 = {
    Set(LVar0, 2)
    Set(LVar1, 0)
    Set(LVar2, 1)
    ExecWait(TTYD64_tik_27_Script_RedSwitch)
    Return
    End
};

EvtScript TTYD64_tik_27_Script_Switch1 = {
    Set(LVar0, 1)
    Set(LVar1, 155)
    Set(LVar2, 3)
    ExecWait(TTYD64_tik_27_Script_RedSwitch)
    Return
    End
};

EvtScript TTYD64_tik_27_Script_EnterMap = {
    Call(ModifyColliderFlags, 3, 13, 4)
    Call(ModifyColliderFlags, 0, 13, 0x80000)
    Return
    End
};

MapSettings TTYD64_tik_27_Header = {
    .main = &TTYD64_tik_27_Script_Main,
    .entryList = &TTYD64_tik_27_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_tik_27_GetTattle },
};

EvtScript TTYD64_tik_27_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(2))
    SetConst(LVar1, GameFlag(4549))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_tik_27_Script_SetupMusic = {
    Call(SetMusic, 0, 75, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

MobileAISettings TTYD64_tik_27_AISettings_80241C90 = {
    .moveSpeed = 2.20000005f,
    .moveTime = 0,
    .waitTime = 0,
    .alertRadius = 70.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 3.20000005f,
    .chaseTurnRate = 15,
    .chaseUpdateInterval = 1,
    .chaseRadius = 90.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_tik_27_NpcSettings_80241CE0 = {
    .defaultAnim = 0x00000000,
    .height = 23,
    .radius = 23,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = &TTYD64_tik_27_Script_NpcAI_80241CC0,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 12,
    .actionFlags = 0,
};

EvtScript TTYD64_tik_27_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_tik_27_Script_Exit_Entry0, 0x80000, 5, 1, 0)
    Return
    End
};

EvtScript TTYD64_tik_27_Script_NpcAI_80241CC0 = {
    Call(BasicAI_Main, Ref(TTYD64_tik_27_AISettings_80241C90))
    Return
    End
};

NpcGroupList TTYD64_tik_27_NpcGroupList_tik27 = {
    { .npcCount = 1, .npcs = TTYD64_tik_27_NpcGroup_SpikedGoomba, .battle = 0x1A10, .stage = 1 },
    {},
};

EntryList TTYD64_tik_27_EntryList = {
    { 331.0f, -18.0f, 158.0f, -90.0f },
};

MapConfig TTYD64_mapcfg_tik_27 = {
    .id = "tik_27",
    .settings = &TTYD64_tik_27_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 2,
};
// clang-format on

void TTYD64_nm_Install_tik_27(void) {
    TTYD64_tik_27_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_tik_27_String_Tattle);
}
