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

API_CALLABLE(BindNpcIdle);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableModel);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetNpcVar);
API_CALLABLE(GetPlayerActionState);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(InterpNpcYaw);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(NpcJump0);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtNpc);
API_CALLABLE(ResetCam);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetItemPos);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcJumpscale);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetNpcVar);
API_CALLABLE(SetPanTarget);
API_CALLABLE(ShowEmote);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(UseExitHeading);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(WaitForCam);

extern EvtScript TTYD64_omo_18_Script_InitMinigame;
extern EvtScript TTYD64_omo_18_Script_ShowSolution;
extern EvtScript TTYD64_omo_18_Script_ToggleBoxesModels;
extern EvtScript TTYD64_omo_18_Script_Minigame_Completed;
extern NpcData TTYD64_omo_18_NpcGroup_ShyGuy[];
extern EvtScript TTYD64_omo_18_Script_InputBox;
extern EvtScript TTYD64_omo_18_Script_Main;
extern EvtScript TTYD64_omo_18_Script_DisableLightModels;
extern u8 TTYD64_omo_18_String_ShyGuy_1[];
extern u8 TTYD64_omo_18_String_Tattle[];
extern u8 TTYD64_omo_18_String_ShyGuy_2[];
extern EvtScript TTYD64_omo_18_Script_Exit_Entry0;
extern MapSettings TTYD64_omo_18_Header;
extern EvtScript TTYD64_omo_18_Script_SetupMusic;
extern EvtScript TTYD64_omo_18_Script_InitNPC_ShyGuy;
extern EvtScript TTYD64_omo_18_Script_Minigame_Input_Green;
extern EvtScript TTYD64_omo_18_Script_Minigame_Input_Red;
extern EvtScript TTYD64_omo_18_Script_Minigame_Input_Blue;
extern EvtScript TTYD64_omo_18_Script_Minigame_Input_Yellow;
extern NpcSettings TTYD64_omo_18_NpcSettings_ShyGuy;
extern EvtScript TTYD64_omo_18_Script_CreateExitTriggers;
extern s32 TTYD64_omo_18_Data_Solution3[];
extern NpcGroupList TTYD64_omo_18_NpcGroupList_omo18;
extern s32 TTYD64_omo_18_Data_Solution2[];
extern s32 TTYD64_omo_18_Data_Solution1[];
extern EntryList TTYD64_omo_18_EntryList;
extern EvtScript TTYD64_omo_18_Script_NPCIdle_UpdateMinigame;

// clang-format off
static s32 TTYD64_omo_18_GetTattleMsg;

static s32 TTYD64_omo_18_GetTattle(void) {
    return TTYD64_omo_18_GetTattleMsg;
}

EvtScript TTYD64_omo_18_Script_InitMinigame = {
    Call(MakeItemEntity, 377, -62, 0, -95, 17, GameFlag(5259))
    Set(MapVar(0), LVar0)
    IfLt(GameByte(4310), 4)
        BindTrigger(TTYD64_omo_18_Script_Minigame_Input_Green, 4096, 11, 1, 0)
        BindTrigger(TTYD64_omo_18_Script_Minigame_Input_Yellow, 4096, 12, 1, 0)
        BindTrigger(TTYD64_omo_18_Script_Minigame_Input_Red, 4096, 13, 1, 0)
        BindTrigger(TTYD64_omo_18_Script_Minigame_Input_Blue, 4096, 14, 1, 0)
    EndIf
    Switch(GameByte(4310))
    CaseEq(0)
        Call(DisablePlayerInput, 1)
        Loop(0)
            Call(GetPlayerActionState, LVar0)
            IfEq(LVar0, 0)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Call(GetNpcPos, 1, LVar0, LVar1, LVar2)
        Add(LVar0, 90)
        Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
        Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
        Call(SetCamSpeed, 0, Float(2.5))
        Call(PanToTarget, 0, 0, 1)
        Call(WaitForCam, 0, Float(1.0))
        Call(InterpNpcYaw, 1, -90, 0)
        Wait(15)
        Call(PlaySoundAtNpc, 1, 610, 0)
        Call(ShowEmote, 1, 0, -45, 20, 1, 0, 0, 0, 0)
        Wait(10)
        Call(InterpNpcYaw, 1, 90, 0)
        Wait(20)
        Call(SetItemPos, MapVar(0), 0, -1000, 0)
        Call(PlaySoundAtNpc, 1, 539, 0)
        Wait(10)
        Call(SetNpcAnimation, 1, 0x3B000A)
        Call(PlaySoundAtNpc, 1, 994, 0)
        Call(SetNpcJumpscale, 1, Float(0.6796875))
        Call(NpcJump0, 1, -38, 18, -153, 20)
        Call(SetNpcAnimation, 1, 0x3B0001)
        Wait(5)
        Call(PlaySoundAtNpc, 1, 994, 0)
        Call(SetNpcAnimation, 1, 0x3B000A)
        Call(NpcJump0, 1, -7, 38, -184, 15)
        Call(SetNpcAnimation, 1, 0x3B0001)
        Wait(5)
        Call(PlaySoundAtNpc, 1, 994, 0)
        Call(SetNpcAnimation, 1, 0x3B000A)
        Call(NpcJump0, 1, 0, 0, -249, 20)
        Call(SetNpcAnimation, 1, 0x3B0001)
        Wait(5)
        Call(GetModelCenter, 64)
        Add(LVar0, -43)
        Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
        Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
        Call(SetCamSpeed, 0, Float(2.5))
        Call(PanToTarget, 0, 0, 1)
        Call(WaitForCam, 0, Float(1.0))
        Call(SpeakToPlayer, 1, 0x3B0011, 0x3B0001, 0, (Bytecode) TTYD64_omo_18_String_ShyGuy_1)
        Set(GameByte(4310), 1)
        ExecWait(TTYD64_omo_18_Script_ShowSolution)
        Call(DisablePlayerInput, 0)
    CaseOrEq(1)
    CaseOrEq(2)
    CaseOrEq(3)
        Call(SetNpcPos, 1, 0, -1000, 0)
        Call(SetItemPos, MapVar(0), 0, -1000, 0)
        EndCaseGroup
    CaseEq(4)
        Call(SetNpcPos, 1, 0, -1000, 0)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_omo_18_Script_ShowSolution = {
    Call(GetModelCenter, 64)
    Add(LVar0, -43)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(SetPanTarget, 0, LVar0, LVar1, LVar2)
    Call(SetCamSpeed, 0, Float(2.5))
    Call(PanToTarget, 0, 0, 1)
    Call(WaitForCam, 0, Float(1.0))
    Wait(10)
    Set(LVar1, 25)
    Switch(GameByte(4310))
    CaseEq(1)
        Set(LVar0, 1)
        ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
        Set(LVar0, 3)
        ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
        Set(LVar0, 4)
        ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
        Set(LVar0, 2)
        ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
    CaseEq(2)
        Set(LVar0, 3)
        ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
        Set(LVar0, 1)
        ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
        Set(LVar0, 4)
        ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
        Set(LVar0, 1)
        ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
        Set(LVar0, 4)
        ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
    CaseEq(3)
        Set(LVar0, 1)
        ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
        Set(LVar0, 3)
        ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
        Set(LVar0, 2)
        ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
        Set(LVar0, 4)
        ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
        Set(LVar0, 1)
        ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
        Set(LVar0, 1)
        ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
    CaseEq(4)
        ExecWait(TTYD64_omo_18_Script_Minigame_Completed)
    EndSwitch
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(UseSettingsFrom, 0, LVar0, LVar1, LVar2)
    Call(ResetCam, 0, Float(2.0))
    Call(WaitForCam, 0, Float(1.0))
    Return
    End
};

EvtScript TTYD64_omo_18_Script_ToggleBoxesModels = {
    Switch(LVar0)
    CaseEq(1)
        Call(EnableGroup, 56, 0)
        Call(EnableModel, 51, 1)
        Call(EnableModel, 54, 1)
    CaseEq(2)
        Call(EnableGroup, 63, 0)
        Call(EnableModel, 58, 1)
        Call(EnableModel, 61, 1)
    CaseEq(3)
        Call(EnableGroup, 70, 0)
        Call(EnableModel, 65, 1)
        Call(EnableModel, 68, 1)
    CaseEq(4)
        Call(EnableGroup, 77, 0)
        Call(EnableModel, 72, 1)
        Call(EnableModel, 75, 1)
    EndSwitch
    Switch(GameByte(4310))
    CaseEq(1)
        Call(PlaySound, 417)
    CaseEq(2)
        Call(PlaySound, 418)
    CaseEq(3)
        Call(PlaySound, 419)
    EndSwitch
    Wait(LVar1)
    Switch(LVar0)
    CaseEq(1)
        Call(EnableGroup, 56, 0)
        Call(EnableModel, 50, 1)
        Call(EnableModel, 53, 1)
    CaseEq(2)
        Call(EnableGroup, 63, 0)
        Call(EnableModel, 57, 1)
        Call(EnableModel, 60, 1)
    CaseEq(3)
        Call(EnableGroup, 70, 0)
        Call(EnableModel, 64, 1)
        Call(EnableModel, 67, 1)
    CaseEq(4)
        Call(EnableGroup, 77, 0)
        Call(EnableModel, 71, 1)
        Call(EnableModel, 74, 1)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_omo_18_Script_Minigame_Completed = {
    Call(SpeakToPlayer, 1, 0x3B0011, 0x3B0001, 0, (Bytecode) TTYD64_omo_18_String_ShyGuy_2)
    Call(SetNpcPos, 1, 0, 0, -249)
    Call(SetNpcFlagBits, 1, 0xC0000000, 1)
    Thread
        Loop(0)
            Call(GetNpcPos, 1, LVar0, LVar1, LVar2)
            Call(SetItemPos, MapVar(0), LVar0, LVar1, LVar2)
            Call(GetNpcVar, 1, 0, LVar0)
            IfEq(LVar0, 1)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndThread
    Call(SetNpcJumpscale, 1, Float(0.6796875))
    Call(PlaySoundAtNpc, 1, 539, 0)
    Call(NpcJump0, 1, -7, 38, -184, 20)
    Call(PlaySoundAtNpc, 1, 539, 0)
    Call(NpcJump0, 1, -12, 18, -144, 20)
    Call(PlaySoundAtNpc, 1, 539, 0)
    Call(NpcJump0, 1, -20, 0, -101, 20)
    Call(SetNpcVar, 1, 0, 1)
    Wait(2)
    Call(SetNpcPos, 1, 0, -1000, 0)
    Return
    End
};

NpcData TTYD64_omo_18_NpcGroup_ShyGuy[] = {
    {
        .id = 1,
        .settings = &TTYD64_omo_18_NpcSettings_ShyGuy,
        .pos = { -91.0f, 0.0f, -96.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_omo_18_Script_InitNPC_ShyGuy,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x003B0001, .walk = 0x003B0002, .run = 0x003B0003, .chase = 0x003B0003, .anim_4 = 0x003B0001, .anim_5 = 0x003B0001, .death = 0x003B000C, .hit = 0x003B000C, .anim_8 = 0x003B0015, .anim_9 = 0x003B0012, .anim_A = 0x003B0011, .anim_B = 0x003B0010, .anim_C = 0x003B0005, .anim_D = 0x003B0001, .anim_E = 0x003B0001, .anim_F = 0x003B0001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_omo_18_Script_InputBox = {
    IfEq(GameByte(4310), 4)
        Return
    EndIf
    Set(LVar8, LVar0)
    Set(LVar0, LVar8)
    Set(LVar1, 10)
    ExecWait(TTYD64_omo_18_Script_ToggleBoxesModels)
    Call(DisablePlayerInput, 1)
    Switch(GameByte(4310))
    CaseEq(1)
        UseBuf((Bytecode) TTYD64_omo_18_Data_Solution1)
    CaseEq(2)
        UseBuf((Bytecode) TTYD64_omo_18_Data_Solution2)
    CaseEq(3)
        UseBuf((Bytecode) TTYD64_omo_18_Data_Solution3)
    EndSwitch
    Set(LVar1, MapVar(1))
    BufPeek(LVar0, LVar1)
    IfEq(LVar0, LVar8)
        Add(LVar1, 1)
        BufPeek(LVar0, LVar1)
        IfEq(LVar0, -1)
            Set(MapVar(1), 0)
            Add(GameByte(4310), 1)
            Call(PlaySound, 11)
            ExecWait(TTYD64_omo_18_Script_ShowSolution)
        Else
            Add(MapVar(1), 1)
        EndIf
    Else
        Call(PlaySound, 541)
        Set(MapVar(1), 0)
        ExecWait(TTYD64_omo_18_Script_ShowSolution)
    EndIf
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_omo_18_Script_Main = {
    Set(GameByte(425), 16)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_omo_18_NpcGroupList_omo18)
    Exec(TTYD64_omo_18_Script_SetupMusic)
    Set(LVar0, (Bytecode) TTYD64_omo_18_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Exec(TTYD64_omo_18_Script_InitMinigame)
    Exec(TTYD64_omo_18_Script_DisableLightModels)
    Return
    End
};

EvtScript TTYD64_omo_18_Script_DisableLightModels = {
    Call(EnableGroup, 78, 0)
    Call(EnableModel, 50, 1)
    Call(EnableModel, 53, 1)
    Call(EnableModel, 57, 1)
    Call(EnableModel, 60, 1)
    Call(EnableModel, 64, 1)
    Call(EnableModel, 67, 1)
    Call(EnableModel, 71, 1)
    Call(EnableModel, 74, 1)
    Return
    End
};

u8 TTYD64_omo_18_String_ShyGuy_1[] = {
    0xFC, 0x01, 0x39, 0x4F, 0x55, 0xF7, 0x4B, 0x4E, 0x4F, 0x57, 0xF7, 0x57,
    0x48, 0x41, 0x54, 0x1F, 0xF7, 0x29, 0x07, 0x4D, 0xF7, 0x42, 0x4F, 0x52,
    0x45, 0x44, 0x01, 0xF0, 0x37, 0x48, 0x41, 0x54, 0xF7, 0x49, 0x46, 0xF7,
    0x59, 0x4F, 0x55, 0xF7, 0x50, 0x4C, 0x41, 0x59, 0xF7, 0x41, 0xF7, 0x4C,
    0x49, 0x54, 0x54, 0x4C, 0x45, 0xF7, 0x42, 0x49, 0x54, 0xF0, 0x57, 0x49,
    0x54, 0x48, 0xF7, 0x4D, 0x45, 0x1F, 0xF0, 0xF1, 0xFB, 0x21, 0x4E, 0x44,
    0xF7, 0x54, 0x48, 0x45, 0x4E, 0xF7, 0x29, 0xF7, 0x43, 0x41, 0x4E, 0xF7,
    0x54, 0x48, 0x49, 0x4E, 0x4B, 0xF7, 0x49, 0x46, 0xF7, 0x29, 0xF7, 0x47,
    0x49, 0x56, 0x45, 0xF0, 0x59, 0x4F, 0x55, 0xF7, 0x54, 0x48, 0x49, 0x53,
    0xF7, 0x4F, 0x52, 0xF7, 0x4E, 0x4F, 0x54, 0x0E, 0xF1, 0xFD
};

u8 TTYD64_omo_18_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0xF7, 0x49, 0x54,
    0x07, 0x53, 0xF7, 0x54, 0x49, 0x4D, 0x45, 0xF7, 0x54, 0x4F, 0xF7, 0x53,
    0x45, 0x45, 0xF7, 0x49, 0x46, 0xF7, 0x59, 0x4F, 0x55, 0x52, 0xF7, 0x4D,
    0x45, 0x4D, 0x4F, 0x52, 0x59, 0xF0, 0x49, 0x53, 0xF7, 0x41, 0x53, 0xF7,
    0x47, 0x4F, 0x4F, 0x44, 0xF7, 0x41, 0x53, 0xF7, 0x59, 0x4F, 0x55, 0xF7,
    0x54, 0x48, 0x49, 0x4E, 0x4B, 0x0C, 0xF7, 0x57, 0x45, 0xF7, 0x4E, 0x45,
    0x45, 0x44, 0xF7, 0x54, 0x4F, 0xF0, 0x42, 0x45, 0x41, 0x54, 0xF7, 0x54,
    0x48, 0x41, 0x54, 0xF7, 0x33, 0x48, 0x59, 0xF7, 0x27, 0x55, 0x59, 0x01,
    0xF1, 0xFD
};

u8 TTYD64_omo_18_String_ShyGuy_2[] = {
    0xFC, 0x01, 0x39, 0x4F, 0x55, 0xF7, 0x4B, 0x4E, 0x4F, 0x57, 0xF7, 0x57,
    0x48, 0x41, 0x54, 0x1F, 0xF0, 0xF1, 0xFB, 0x29, 0x46, 0xF7, 0x59, 0x4F,
    0x55, 0xF7, 0x57, 0x41, 0x4E, 0x54, 0xF7, 0x49, 0x54, 0xF7, 0x54, 0x48,
    0x41, 0x54, 0xF7, 0x4D, 0x55, 0x43, 0x48, 0x0C, 0xF7, 0x59, 0x4F, 0x55,
    0xF0, 0x43, 0x41, 0x4E, 0xF7, 0x4B, 0x45, 0x45, 0x50, 0xF7, 0x49, 0x54,
    0x0C, 0xF7, 0x29, 0xF7, 0x44, 0x49, 0x44, 0x4E, 0x07, 0x54, 0xF7, 0x45,
    0x56, 0x45, 0x4E, 0xF7, 0x57, 0x41, 0x4E, 0x54, 0xF0, 0x49, 0x54, 0xF7,
    0x41, 0x4E, 0x59, 0x57, 0x41, 0x59, 0x53, 0xF7, 0xF1, 0xFD
};

EvtScript TTYD64_omo_18_Script_Exit_Entry0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "omo_09", 1)
    Wait(100)
    Return
    End
};

MapSettings TTYD64_omo_18_Header = {
    .main = &TTYD64_omo_18_Script_Main,
    .entryList = &TTYD64_omo_18_EntryList,
    .entryCount = 1,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_omo_18_GetTattle },
};

EvtScript TTYD64_omo_18_Script_SetupMusic = {
    Call(SetMusic, 0, 32, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_omo_18_Script_InitNPC_ShyGuy = {
    Call(EnableNpcShadow, -1, 0)
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_omo_18_Script_NPCIdle_UpdateMinigame)
    Return
    End
};

EvtScript TTYD64_omo_18_Script_Minigame_Input_Green = {
    Set(LVar0, 1)
    ExecWait(TTYD64_omo_18_Script_InputBox)
    Return
    End
};

EvtScript TTYD64_omo_18_Script_Minigame_Input_Red = {
    Set(LVar0, 3)
    ExecWait(TTYD64_omo_18_Script_InputBox)
    Return
    End
};

EvtScript TTYD64_omo_18_Script_Minigame_Input_Blue = {
    Set(LVar0, 4)
    ExecWait(TTYD64_omo_18_Script_InputBox)
    Return
    End
};

EvtScript TTYD64_omo_18_Script_Minigame_Input_Yellow = {
    Set(LVar0, 2)
    ExecWait(TTYD64_omo_18_Script_InputBox)
    Return
    End
};

NpcSettings TTYD64_omo_18_NpcSettings_ShyGuy = {
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

EvtScript TTYD64_omo_18_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_omo_18_Script_Exit_Entry0, 0x80000, 3, 1, 0)
    Return
    End
};

s32 TTYD64_omo_18_Data_Solution3[] = {
    1, 3, 2, 4, 1, 1, -1
};

NpcGroupList TTYD64_omo_18_NpcGroupList_omo18 = {
    { .npcCount = 1, .npcs = TTYD64_omo_18_NpcGroup_ShyGuy, .battle = 0x0000, .stage = 0 },
    {},
};

s32 TTYD64_omo_18_Data_Solution2[] = {
    3, 1, 4, 1, 4, -1
};

s32 TTYD64_omo_18_Data_Solution1[] = {
    1, 3, 4, 2, -1
};

EntryList TTYD64_omo_18_EntryList = {
    { -290.0f, 0.0f, 0.0f, 90.0f },
};

EvtScript TTYD64_omo_18_Script_NPCIdle_UpdateMinigame = {
    Return
    End
};

MapConfig TTYD64_mapcfg_omo_18 = {
    .id = "omo_18",
    .settings = &TTYD64_omo_18_Header,
    .bgName = "omo_bg",
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 2,
};
// clang-format on

void TTYD64_nm_Install_omo_18(void) {
    TTYD64_nm_BindMessage(TTYD64_omo_18_Script_InitMinigame, TTYD64_omo_18_String_ShyGuy_1);
    TTYD64_nm_BindMessage(TTYD64_omo_18_Script_Minigame_Completed, TTYD64_omo_18_String_ShyGuy_2);
    TTYD64_omo_18_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_omo_18_String_Tattle);
}
