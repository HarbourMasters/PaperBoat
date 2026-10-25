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
#include "port/romhack/specific/TTYD64/world/nm.h"

API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(RemoveEffect);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetTexPanner);
API_CALLABLE(TranslateGroup);
API_CALLABLE(UpdateLerp);

extern EvtScript TTYD64_kpa_138_Script_PressBlock;
extern EvtScript TTYD64_kpa_138_Script_MovePillars;
extern EvtScript TTYD64_kpa_138_Script_EnterMap;
extern EvtScript TTYD64_kpa_138_Script_SetupTexturePan;
extern EvtScript TTYD64_kpa_138_Script_CheckSolution;
extern EvtScript TTYD64_kpa_138_Script_Main;
extern EvtScript TTYD64_kpa_138_Script_TexturePan_Update;
extern u8 TTYD64_kpa_138_String_Tattle[];
extern EvtScript TTYD64_kpa_138_Script_Exit0;
extern MapSettings TTYD64_kpa_138_Header;
extern EvtScript TTYD64_kpa_138_Script_SetupMusic;
extern EvtScript TTYD64_kpa_138_Script_Block1;
extern EvtScript TTYD64_kpa_138_Script_Block2;
extern EvtScript TTYD64_kpa_138_Script_Block3;
extern EvtScript TTYD64_kpa_138_Script_Block4;
extern EvtScript TTYD64_kpa_138_Script_Block9;
extern EvtScript TTYD64_kpa_138_Script_Block5;
extern EvtScript TTYD64_kpa_138_Script_Block6;
extern EvtScript TTYD64_kpa_138_Script_Block7;
extern EvtScript TTYD64_kpa_138_Script_Block8;
extern EvtScript TTYD64_kpa_138_Script_CreateExitTriggers;
extern s32 TTYD64_kpa_138_Data_ModelGroupsTable[];
extern EntryList TTYD64_kpa_138_EntryList;

// clang-format off
static s32 TTYD64_kpa_138_GetTattleMsg;

static s32 TTYD64_kpa_138_GetTattle(void) {
    return TTYD64_kpa_138_GetTattleMsg;
}

EvtScript TTYD64_kpa_138_Script_PressBlock = {
    IfEq(GameFlag(5701), 1)
        Return
    EndIf
    Call(DisablePlayerInput, 1)
    Set(MapFlag(1), 0)
    Set(MapFlag(2), 0)
    Set(MapFlag(3), 0)
    Set(MapFlag(4), 0)
    Set(MapFlag(5), 0)
    Set(MapFlag(6), 0)
    Set(MapFlag(7), 0)
    Set(MapFlag(8), 0)
    Set(MapFlag(9), 0)
    Switch(LVar0)
    CaseEq(1)
        Call(TTYD64_nm_ToggleBool, MapVar(1))
        Call(TTYD64_nm_ToggleBool, MapVar(2))
        Call(TTYD64_nm_ToggleBool, MapVar(4))
        Set(MapFlag(1), 1)
        Set(MapFlag(2), 1)
        Set(MapFlag(4), 1)
    CaseEq(2)
        Call(TTYD64_nm_ToggleBool, MapVar(1))
        Call(TTYD64_nm_ToggleBool, MapVar(2))
        Call(TTYD64_nm_ToggleBool, MapVar(3))
        Call(TTYD64_nm_ToggleBool, MapVar(5))
        Set(MapFlag(1), 1)
        Set(MapFlag(2), 1)
        Set(MapFlag(3), 1)
        Set(MapFlag(5), 1)
    CaseEq(3)
        Call(TTYD64_nm_ToggleBool, MapVar(2))
        Call(TTYD64_nm_ToggleBool, MapVar(3))
        Call(TTYD64_nm_ToggleBool, MapVar(6))
        Set(MapFlag(2), 1)
        Set(MapFlag(3), 1)
        Set(MapFlag(6), 1)
    CaseEq(4)
        Call(TTYD64_nm_ToggleBool, MapVar(1))
        Call(TTYD64_nm_ToggleBool, MapVar(4))
        Call(TTYD64_nm_ToggleBool, MapVar(5))
        Call(TTYD64_nm_ToggleBool, MapVar(7))
        Set(MapFlag(1), 1)
        Set(MapFlag(4), 1)
        Set(MapFlag(5), 1)
        Set(MapFlag(7), 1)
    CaseEq(5)
        Call(TTYD64_nm_ToggleBool, MapVar(2))
        Call(TTYD64_nm_ToggleBool, MapVar(4))
        Call(TTYD64_nm_ToggleBool, MapVar(5))
        Call(TTYD64_nm_ToggleBool, MapVar(6))
        Call(TTYD64_nm_ToggleBool, MapVar(8))
        Set(MapFlag(2), 1)
        Set(MapFlag(4), 1)
        Set(MapFlag(5), 1)
        Set(MapFlag(6), 1)
        Set(MapFlag(8), 1)
    CaseEq(6)
        Call(TTYD64_nm_ToggleBool, MapVar(3))
        Call(TTYD64_nm_ToggleBool, MapVar(5))
        Call(TTYD64_nm_ToggleBool, MapVar(6))
        Call(TTYD64_nm_ToggleBool, MapVar(9))
        Set(MapFlag(3), 1)
        Set(MapFlag(5), 1)
        Set(MapFlag(6), 1)
        Set(MapFlag(9), 1)
    CaseEq(7)
        Call(TTYD64_nm_ToggleBool, MapVar(4))
        Call(TTYD64_nm_ToggleBool, MapVar(7))
        Call(TTYD64_nm_ToggleBool, MapVar(8))
        Set(MapFlag(4), 1)
        Set(MapFlag(7), 1)
        Set(MapFlag(8), 1)
    CaseEq(8)
        Call(TTYD64_nm_ToggleBool, MapVar(5))
        Call(TTYD64_nm_ToggleBool, MapVar(7))
        Call(TTYD64_nm_ToggleBool, MapVar(8))
        Call(TTYD64_nm_ToggleBool, MapVar(9))
        Set(MapFlag(5), 1)
        Set(MapFlag(7), 1)
        Set(MapFlag(8), 1)
        Set(MapFlag(9), 1)
    CaseEq(9)
        Call(TTYD64_nm_ToggleBool, MapVar(6))
        Call(TTYD64_nm_ToggleBool, MapVar(8))
        Call(TTYD64_nm_ToggleBool, MapVar(9))
        Set(MapFlag(6), 1)
        Set(MapFlag(8), 1)
        Set(MapFlag(9), 1)
    EndSwitch
    ExecWait(TTYD64_kpa_138_Script_MovePillars)
    ExecWait(TTYD64_kpa_138_Script_CheckSolution)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_MovePillars = {
    UseBuf((Bytecode) TTYD64_kpa_138_Data_ModelGroupsTable)
    SetConst(LVar2, MapFlag(1))
    SetConst(LVar3, MapVar(1))
    Set(LVar4, 0)
    Call(PlaySound, 338)
    Loop(9)
        Call(TTYD64_nm_kpa_138_GetFXPos, LVar4, LVar8, LVar9, LVarA)
        Set(LVar1, LVar4)
        Set(LVar5, 4)
        Mul(LVar1, LVar5)
        Set(LVar7, MapVar(10))
        Add(LVar7, LVar1)
        Call(TTYD64_nm_GetVarFromVar, LVar2, LVar5)
        IfEq(LVar5, 1)
            BufPeek(LVar6, LVar4)
            Call(TTYD64_nm_GetVarFromVar, LVar3, LVar5)
            IfEq(LVar5, 0)
                Thread
                    Call(MakeLerp, -10, 0, 15, 0)
                    Loop(0)
                        Call(UpdateLerp)
                        Call(TranslateGroup, LVar6, 0, LVar0, 0)
                        Wait(1)
                        IfEq(LVar1, 0)
                            BreakLoop
                        EndIf
                    EndLoop
                    Set(LVar1, LVar9)
                    Add(LVar1, 20)
                    Call(PlayEffect_impl, 29, 2, LVar8, LVar1, LVarA, 0, 10, 0, 15, 0, 0, 0, 0)
                    Wait(5)
                    Call(TTYD64_nm_ArrayWordRead, LVar7, MapVar(10), LVar0)
                    Call(RemoveEffect, LVar0)
                EndThread
            Else
                Thread
                    Call(MakeLerp, 0, -10, 15, 0)
                    Loop(0)
                        Call(UpdateLerp)
                        Call(TranslateGroup, LVar6, 0, LVar0, 0)
                        Wait(1)
                        IfEq(LVar1, 0)
                            BreakLoop
                        EndIf
                    EndLoop
                    Set(LVar1, LVar9)
                    Add(LVar1, 20)
                    Call(PlayEffect_impl, 29, 2, LVar8, LVar1, LVarA, 0, 10, 0, 15, 0, 0, 0, 0)
                    Wait(5)
                    Call(PlayEffect_impl, 32, 0, LVar8, LVar9, LVarA, Float(1.0), 0, 0, 0, 0, 0, 0, 0)
                    Call(TTYD64_GetEffect, LVarF, LVar0)
                    Call(TTYD64_nm_ArrayWordWrite, LVar7, MapVar(10), LVar0)
                EndThread
            EndIf
        EndIf
        Add(LVar2, 1)
        Add(LVar3, 1)
        Add(LVar4, 1)
        Wait(1)
    EndLoop
    Wait(5)
    Call(PlaySound, 226)
    Wait(10)
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_EnterMap = {
    Call(ModifyColliderFlags, 3, 7, 4)
    Call(ModifyColliderFlags, 0, 7, 0x80000)
    MallocArray(9, MapVar(10))
    IfEq(GameFlag(5701), 0)
        BindTrigger(TTYD64_kpa_138_Script_Block1, 256, 15, 1, 0)
        BindTrigger(TTYD64_kpa_138_Script_Block2, 256, 16, 1, 0)
        BindTrigger(TTYD64_kpa_138_Script_Block3, 256, 17, 1, 0)
        BindTrigger(TTYD64_kpa_138_Script_Block4, 256, 18, 1, 0)
        BindTrigger(TTYD64_kpa_138_Script_Block5, 256, 19, 1, 0)
        BindTrigger(TTYD64_kpa_138_Script_Block6, 256, 20, 1, 0)
        BindTrigger(TTYD64_kpa_138_Script_Block7, 256, 21, 1, 0)
        BindTrigger(TTYD64_kpa_138_Script_Block8, 256, 22, 1, 0)
        BindTrigger(TTYD64_kpa_138_Script_Block9, 256, 23, 1, 0)
    Else
        Call(TranslateGroup, 33, 0, -10, 0)
        Call(TranslateGroup, 37, 0, -10, 0)
        Call(TranslateGroup, 41, 0, -10, 0)
        Call(TranslateGroup, 45, 0, -10, 0)
        Call(TranslateGroup, 49, 0, -10, 0)
        Call(TranslateGroup, 53, 0, -10, 0)
        Call(TranslateGroup, 57, 0, -10, 0)
        Call(TranslateGroup, 61, 0, -10, 0)
        Call(TranslateGroup, 65, 0, -10, 0)
        Call(PlayEffect_impl, 32, 0, -222, 125, -97, Float(1.0), 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 0, -129, 125, -97, Float(1.0), 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 0, -34, 125, -97, Float(1.0), 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 0, -222, 125, -5, Float(1.0), 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 0, -129, 125, -5, Float(1.0), 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 0, -34, 125, -5, Float(1.0), 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 0, -222, 125, 92, Float(1.0), 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 0, -129, 125, 92, Float(1.0), 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 32, 0, -34, 125, 92, Float(1.0), 0, 0, 0, 0, 0, 0, 0)
        Call(MakeItemEntity, 387, 133, 70, -67, 17, GameFlag(5702))
    EndIf
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_SetupTexturePan = {
    Call(SetTexPanner, 6, 0)
    Call(SetTexPanner, 29, 1)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 200)
        Set(LVar2, -200)
        Set(LVar3, 20)
        Set(LVar4, -20)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_kpa_138_Script_TexturePan_Update)
    EndThread
    Thread
        Set(LVar0, 1)
        Set(LVar1, -100)
        Set(LVar2, 100)
        Set(LVar3, 70)
        Set(LVar4, -70)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_kpa_138_Script_TexturePan_Update)
    EndThread
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_CheckSolution = {
    Set(LVar0, MapVar(1))
    Add(LVar0, MapVar(2))
    Add(LVar0, MapVar(3))
    Add(LVar0, MapVar(4))
    Add(LVar0, MapVar(5))
    Add(LVar0, MapVar(6))
    Add(LVar0, MapVar(7))
    Add(LVar0, MapVar(8))
    Add(LVar0, MapVar(9))
    IfEq(LVar0, 9)
        Set(GameFlag(5701), 1)
        Call(PlaySound, 11)
        Set(LVar0, 133)
        Set(LVar1, 70)
        Add(LVar1, 220)
        Set(LVar2, -67)
        Call(MakeItemEntity, 387, LVar0, LVar1, LVar2, 13, GameFlag(5702))
        Call(DisablePlayerInput, 1)
        Wait(15)
        Call(DisablePlayerInput, 0)
    EndIf
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_Main = {
    Set(GameByte(425), 22)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_kpa_138_Script_SetupMusic)
    Exec(TTYD64_kpa_138_Script_SetupTexturePan)
    Exec(TTYD64_kpa_138_Script_EnterMap)
    Set(LVar0, (Bytecode) TTYD64_kpa_138_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Wait(10)
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_TexturePan_Update = {
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

u8 TTYD64_kpa_138_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C, 0xF7, 0x54,
    0x48, 0x49, 0x4E, 0x4B, 0xF7, 0x56, 0x45, 0x52, 0x59, 0xF7, 0x57, 0x45,
    0x4C, 0x4C, 0xF7, 0x41, 0x42, 0x4F, 0x55, 0x54, 0xF7, 0x54, 0x48, 0x45,
    0xF7, 0x4E, 0x45, 0x58, 0x54, 0xF0, 0x50, 0x49, 0x4C, 0x4C, 0x41, 0x52,
    0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x41, 0x52, 0x45, 0xF7, 0x47, 0x4F, 0x49,
    0x4E, 0x47, 0xF7, 0x54, 0x4F, 0xF7, 0x54, 0x4F, 0x55, 0x43, 0x48, 0x0C,
    0xF7, 0x57, 0x45, 0xF0, 0x4D, 0x55, 0x53, 0x54, 0xF7, 0x4D, 0x41, 0x4B,
    0x45, 0xF7, 0x53, 0x55, 0x52, 0x45, 0xF7, 0x54, 0x48, 0x41, 0x54, 0xF7,
    0x54, 0x48, 0x45, 0x59, 0xF7, 0x41, 0x52, 0x45, 0xF7, 0x41, 0x4C, 0x4C,
    0xF0, 0x41, 0x43, 0x54, 0x49, 0x56, 0x41, 0x54, 0x45, 0x44, 0xF7, 0x54,
    0x4F, 0xF7, 0x43, 0x4F, 0x4D, 0x50, 0x4C, 0x45, 0x54, 0x45, 0xF7, 0x54,
    0x48, 0x49, 0x53, 0xF7, 0x50, 0x55, 0x5A, 0x5A, 0x4C, 0x45, 0x0E, 0xF1,
    0xFD
};

Vec3i TTYD64_kpa_138_Data_FXPosTable[] = {
    { -222, 125, -97 },
    { -129, 125, -97 },
    { -34, 125, -97 },
    { -222, 125, -5 },
    { -129, 125, -5 },
    { -34, 125, -5 },
    { -222, 125, 92 },
    { -129, 125, 92 },
    { -34, 125, 92 },
};

EvtScript TTYD64_kpa_138_Script_Exit0 = {
    Call(TTYD64_WriteField, TTYD64_F_GGAMESTATUS_7D_1U, 1)
    Call(GotoMap, (Bytecode) "kpa_133", 4)
    Wait(100)
    Return
    End
};

MapSettings TTYD64_kpa_138_Header = {
    .main = &TTYD64_kpa_138_Script_Main,
    .entryList = &TTYD64_kpa_138_EntryList,
    .entryCount = 2,
    .background = NULL,
    .tattle = { .get = TTYD64_kpa_138_GetTattle },
};

EvtScript TTYD64_kpa_138_Script_SetupMusic = {
    Call(SetMusic, 0, 100, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_Block1 = {
    Set(LVar0, 1)
    ExecWait(TTYD64_kpa_138_Script_PressBlock)
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_Block2 = {
    Set(LVar0, 2)
    ExecWait(TTYD64_kpa_138_Script_PressBlock)
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_Block3 = {
    Set(LVar0, 3)
    ExecWait(TTYD64_kpa_138_Script_PressBlock)
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_Block4 = {
    Set(LVar0, 4)
    ExecWait(TTYD64_kpa_138_Script_PressBlock)
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_Block9 = {
    Set(LVar0, 9)
    ExecWait(TTYD64_kpa_138_Script_PressBlock)
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_Block5 = {
    Set(LVar0, 5)
    ExecWait(TTYD64_kpa_138_Script_PressBlock)
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_Block6 = {
    Set(LVar0, 6)
    ExecWait(TTYD64_kpa_138_Script_PressBlock)
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_Block7 = {
    Set(LVar0, 7)
    ExecWait(TTYD64_kpa_138_Script_PressBlock)
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_Block8 = {
    Set(LVar0, 8)
    ExecWait(TTYD64_kpa_138_Script_PressBlock)
    Return
    End
};

EvtScript TTYD64_kpa_138_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_kpa_138_Script_Exit0, 0x80000, 5, 1, 0)
    Return
    End
};

s32 TTYD64_kpa_138_Data_ModelGroupsTable[] = {
    33, 37, 41, 45, 49, 53, 57, 61, 65
};

EntryList TTYD64_kpa_138_EntryList = {
    { 113.0f, 66.0f, 98.0f, -90.0f },
    { 58.0f, 70.0f, 46.0f, 0.0f },
};

MapConfig TTYD64_mapcfg_kpa_138 = {
    .id = "kpa_138",
    .settings = &TTYD64_kpa_138_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 3,
};
// clang-format on

void TTYD64_nm_Install_kpa_138(void) {
    TTYD64_kpa_138_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_kpa_138_String_Tattle);
}
