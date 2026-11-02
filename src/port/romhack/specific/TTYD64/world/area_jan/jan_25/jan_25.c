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
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GetPlayerTargetYaw);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(StopSound);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_jan_25_Script_MoveRock;
extern EvtScript TTYD64_jan_25_Script_InitRocks;
extern EvtScript TTYD64_jan_25_Script_Main;
extern u8 TTYD64_jan_25_String_Tattle[];
extern EvtScript TTYD64_jan_25_Script_MakeEntities;
extern EvtScript TTYD64_jan_25_Script_Exit0;
extern MapSettings TTYD64_jan_25_Header;
extern EvtScript TTYD64_jan_25_Script_MoveRock_R_4_3;
extern EvtScript TTYD64_jan_25_Script_MoveRock_R_4_1;
extern EvtScript TTYD64_jan_25_Script_MoveRock_R_4_2;
extern EvtScript TTYD64_jan_25_Script_MoveRock_R_1_2;
extern EvtScript TTYD64_jan_25_Script_MoveRock_R_2_1;
extern EvtScript TTYD64_jan_25_Script_MoveRock_R_2_2;
extern EvtScript TTYD64_jan_25_Script_Entity_Shine1;
extern EvtScript TTYD64_jan_25_Script_SetupMusic;
extern EvtScript TTYD64_jan_25_Script_MoveRock_L_2_3;
extern EvtScript TTYD64_jan_25_Script_MoveRock_L_4_1;
extern EvtScript TTYD64_jan_25_Script_MoveRock_L_1_2;
extern EvtScript TTYD64_jan_25_Script_MoveRock_L_2_2;
extern EvtScript TTYD64_jan_25_Script_MoveRock_L_3_1;
extern EvtScript TTYD64_jan_25_Script_MoveRock_L_4_3;
extern EvtScript TTYD64_jan_25_Script_MoveRock_L_5_2;
extern EvtScript TTYD64_jan_25_Script_MakeExits;
extern EntryList TTYD64_jan_25_EntryList;

// clang-format off
static s32 TTYD64_jan_25_GetTattleMsg;

static s32 TTYD64_jan_25_GetTattle(void) {
    return TTYD64_jan_25_GetTattleMsg;
}

EvtScript TTYD64_jan_25_Script_MoveRock = {
    Set(LVar7, LVar0)
    Set(LVar8, LVar1)
    Call(GetPlayerTargetYaw, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVar9, 0)
        Set(LVarA, 0)
    CaseEq(90)
        Set(LVar9, 1)
        Set(LVarA, 0)
    CaseEq(180)
        Set(LVar9, 0)
        Set(LVarA, 1)
    CaseEq(270)
        Set(LVar9, 1)
        Set(LVarA, 1)
    CaseDefault
        Set(MapVar(0), 0)
        Return
    EndSwitch
    Set(MapVar(1), LVar7)
    IfEq(MapVar(2), 0)
        Set(MapVar(2), MapVar(1))
    Else
        IfNe(MapVar(1), MapVar(2))
            Set(MapVar(0), 0)
            Set(MapVar(2), MapVar(1))
        EndIf
    EndIf
    Add(MapVar(0), 1)
    IfLt(MapVar(0), 3)
        Return
    EndIf
    Set(MapVar(0), 0)
    Set(MapVar(2), 0)
    Call(TTYD64_nm_jan_25_UpdateRockPosInTable, LVar7, LVar9, LVarA, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(DisablePlayerInput, 1)
    Call(TTYD64_GetModelPointer, LVar7, LVar0)
    Call(TTYD64_GetModelBaseTranslation, LVar0, LVar4, LVar5, LVar6)
    Call(PlaySound, 0x80000010)
    IfEq(LVar9, 0)
        Set(LVar1, 52)
        IfEq(LVarA, 0)
            Set(LVar2, -1)
        Else
            Set(LVar2, 1)
        EndIf
        Mul(LVar1, LVar2)
        Set(LVar3, LVar6)
        Add(LVar3, LVar1)
        Set(LVar9, 0)
        Call(MakeLerp, LVar6, LVar3, 70, 0)
        Loop(0)
            Call(UpdateLerp)
            Set(LVar4, LVar1)
            Call(TTYD64_GetModelPointer, LVar7, LVar1)
            Call(TTYD64_GetModelBaseTranslation, LVar1, LVar2, 0, 0)
            Call(TranslateModel, LVar7, LVar2, 0, LVar0)
            Call(UpdateColliderTransform, LVar8)
            Call(GetModelCenter, LVar7)
            Set(LVar5, -37)
            IfEq(LVarA, 0)
                Set(LVar3, -1)
            Else
                Set(LVar3, 1)
            EndIf
            Mul(LVar5, LVar3)
            Add(LVar2, LVar5)
            Call(GetPlayerPos, LVar0, LVar1, 0)
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Call(SetPlayerActionState, 20)
            Add(LVar9, 1)
            IfGe(LVar9, 6)
                Call(GetModelCenter, LVar7)
                Call(GetPlayerPos, 0, LVar1, 0)
                Set(LVar5, 26)
                IfEq(LVarA, 0)
                    Set(LVar3, 1)
                Else
                    Set(LVar3, -1)
                EndIf
                Mul(LVar5, LVar3)
                Add(LVar2, LVar5)
                Sub(LVar1, 7)
                Sub(LVar0, 15)
                Call(PlayEffect_impl, 7, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                Add(LVar0, 15)
                Call(PlayEffect_impl, 7, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                Add(LVar0, 15)
                Call(PlayEffect_impl, 7, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                Set(LVar9, 0)
            EndIf
            Wait(1)
            IfEq(LVar4, 0)
                BreakLoop
            EndIf
        EndLoop
    Else
        Set(LVar1, 49)
        IfEq(LVarA, 0)
            Set(LVar2, 1)
        Else
            Set(LVar2, -1)
        EndIf
        Mul(LVar1, LVar2)
        Set(LVar3, LVar4)
        Add(LVar3, LVar1)
        Set(LVar9, 0)
        Call(MakeLerp, LVar4, LVar3, 70, 0)
        Loop(0)
            Call(UpdateLerp)
            Set(LVar4, LVar1)
            Call(TTYD64_GetModelPointer, LVar7, LVar1)
            Call(TTYD64_GetModelBaseTranslation, LVar1, 0, 0, LVar2)
            Call(TranslateModel, LVar7, LVar0, 0, LVar2)
            Call(UpdateColliderTransform, LVar8)
            Call(GetModelCenter, LVar7)
            Set(LVar5, -37)
            IfEq(LVarA, 0)
                Set(LVar3, 1)
            Else
                Set(LVar3, -1)
            EndIf
            Mul(LVar5, LVar3)
            Add(LVar0, LVar5)
            Call(GetPlayerPos, 0, LVar1, LVar2)
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Call(SetPlayerActionState, 20)
            Add(LVar9, 1)
            IfGe(LVar9, 6)
                Call(GetModelCenter, LVar7)
                Call(GetPlayerPos, 0, LVar1, 0)
                Set(LVar5, 17)
                IfEq(LVarA, 0)
                    Set(LVar3, -1)
                Else
                    Set(LVar3, 1)
                EndIf
                Mul(LVar5, LVar3)
                Add(LVar0, LVar5)
                Sub(LVar1, 7)
                Sub(LVar2, 15)
                Call(PlayEffect_impl, 7, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                Add(LVar2, 15)
                Call(PlayEffect_impl, 7, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                Add(LVar2, 15)
                Call(PlayEffect_impl, 7, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                Set(LVar9, 0)
            EndIf
            Wait(1)
            IfEq(LVar4, 0)
                BreakLoop
            EndIf
        EndLoop
    EndIf
    Call(StopSound, 0x80000010)
    Call(SetPlayerActionState, 0)
    Wait(10)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_InitRocks = {
    BindTrigger(TTYD64_jan_25_Script_MoveRock_L_1_2, 64, 11, 1, 0)
    BindTrigger(TTYD64_jan_25_Script_MoveRock_L_2_2, 64, 12, 1, 0)
    BindTrigger(TTYD64_jan_25_Script_MoveRock_L_2_3, 64, 13, 1, 0)
    BindTrigger(TTYD64_jan_25_Script_MoveRock_L_3_1, 64, 14, 1, 0)
    BindTrigger(TTYD64_jan_25_Script_MoveRock_L_4_1, 64, 15, 1, 0)
    BindTrigger(TTYD64_jan_25_Script_MoveRock_L_4_3, 64, 16, 1, 0)
    BindTrigger(TTYD64_jan_25_Script_MoveRock_L_5_2, 64, 17, 1, 0)
    BindTrigger(TTYD64_jan_25_Script_MoveRock_R_1_2, 64, 19, 1, 0)
    BindTrigger(TTYD64_jan_25_Script_MoveRock_R_2_1, 64, 20, 1, 0)
    BindTrigger(TTYD64_jan_25_Script_MoveRock_R_2_2, 64, 21, 1, 0)
    BindTrigger(TTYD64_jan_25_Script_MoveRock_R_4_1, 64, 22, 1, 0)
    BindTrigger(TTYD64_jan_25_Script_MoveRock_R_4_2, 64, 23, 1, 0)
    BindTrigger(TTYD64_jan_25_Script_MoveRock_R_4_3, 64, 24, 1, 0)
    Call(ParentColliderToModel, 11, 27)
    Call(ParentColliderToModel, 12, 28)
    Call(ParentColliderToModel, 13, 29)
    Call(ParentColliderToModel, 14, 30)
    Call(ParentColliderToModel, 15, 31)
    Call(ParentColliderToModel, 16, 32)
    Call(ParentColliderToModel, 17, 33)
    Call(ParentColliderToModel, 19, 35)
    Call(ParentColliderToModel, 20, 36)
    Call(ParentColliderToModel, 21, 37)
    Call(ParentColliderToModel, 22, 38)
    Call(ParentColliderToModel, 23, 39)
    Call(ParentColliderToModel, 24, 40)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_Main = {
    Set(GameByte(425), 36)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_jan_25_Script_SetupMusic)
    ExecWait(TTYD64_jan_25_Script_MakeEntities)
    Exec(TTYD64_jan_25_Script_InitRocks)
    Call(TTYD64_nm_jan_25_RestereRocksTable)
    Set(LVar0, (Bytecode) TTYD64_jan_25_Script_MakeExits)
    Exec(EnterWalk)
    Return
    End
};

u8 TTYD64_jan_25_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x37, 0x4F, 0x57, 0xF7, 0x54, 0x48, 0x45, 0x52,
    0x45, 0x07, 0x53, 0xF7, 0x41, 0xF7, 0x4C, 0x4F, 0x54, 0xF7, 0x4F, 0x46,
    0xF7, 0x52, 0x4F, 0x43, 0x4B, 0x53, 0xF7, 0x48, 0x45, 0x52, 0x45, 0x01,
    0xF0, 0x29, 0x54, 0xF7, 0x4C, 0x4F, 0x4F, 0x4B, 0x53, 0xF7, 0x4C, 0x49,
    0x4B, 0x45, 0xF7, 0x54, 0x48, 0x45, 0x59, 0xF7, 0x43, 0x41, 0x4E, 0xF7,
    0x42, 0x45, 0xF7, 0x50, 0x55, 0x53, 0x48, 0x45, 0x44, 0x0E, 0xF0, 0xF1,
    0xFB, 0x34, 0x52, 0x59, 0xF7, 0x4F, 0x50, 0x45, 0x4E, 0x49, 0x4E, 0x47,
    0xF7, 0x54, 0x48, 0x45, 0xF7, 0x57, 0x41, 0x59, 0xF7, 0x42, 0x59, 0xF7,
    0x50, 0x55, 0x53, 0x48, 0x49, 0x4E, 0x47, 0xF7, 0x54, 0x48, 0x45, 0xF0,
    0x52, 0x4F, 0x43, 0x4B, 0x53, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0E,
    0xF0, 0xF1, 0xFD
};

EvtScript TTYD64_jan_25_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SuperBlock), 0, 55, -25, 0, 0x80000000)
    Set(MapVar(3), LVar0)
    Call(AssignBlockFlag, GameFlag(5393))
    Call(AssignScript, (Bytecode) TTYD64_jan_25_Script_Entity_Shine1)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_Exit0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "jan_07", 1)
    Wait(100)
    Return
    End
};

MapSettings TTYD64_jan_25_Header = {
    .main = &TTYD64_jan_25_Script_Main,
    .entryList = &TTYD64_jan_25_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_jan_25_GetTattle },
};

EvtScript TTYD64_jan_25_Script_MoveRock_R_4_3 = {
    Set(LVar0, 40)
    Set(LVar1, 24)
    ExecWait(TTYD64_jan_25_Script_MoveRock)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_MoveRock_R_4_1 = {
    Set(LVar0, 38)
    Set(LVar1, 22)
    ExecWait(TTYD64_jan_25_Script_MoveRock)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_MoveRock_R_4_2 = {
    Set(LVar0, 39)
    Set(LVar1, 23)
    ExecWait(TTYD64_jan_25_Script_MoveRock)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_MoveRock_R_1_2 = {
    Set(LVar0, 35)
    Set(LVar1, 19)
    ExecWait(TTYD64_jan_25_Script_MoveRock)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_MoveRock_R_2_1 = {
    Set(LVar0, 36)
    Set(LVar1, 20)
    ExecWait(TTYD64_jan_25_Script_MoveRock)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_MoveRock_R_2_2 = {
    Set(LVar0, 37)
    Set(LVar1, 21)
    ExecWait(TTYD64_jan_25_Script_MoveRock)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(3))
    SetConst(LVar1, GameFlag(5393))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_SetupMusic = {
    Call(SetMusic, 0, 36, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_MoveRock_L_2_3 = {
    Set(LVar0, 29)
    Set(LVar1, 13)
    ExecWait(TTYD64_jan_25_Script_MoveRock)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_MoveRock_L_4_1 = {
    Set(LVar0, 31)
    Set(LVar1, 15)
    ExecWait(TTYD64_jan_25_Script_MoveRock)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_MoveRock_L_1_2 = {
    Set(LVar0, 27)
    Set(LVar1, 11)
    ExecWait(TTYD64_jan_25_Script_MoveRock)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_MoveRock_L_2_2 = {
    Set(LVar0, 28)
    Set(LVar1, 12)
    ExecWait(TTYD64_jan_25_Script_MoveRock)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_MoveRock_L_3_1 = {
    Set(LVar0, 30)
    Set(LVar1, 14)
    ExecWait(TTYD64_jan_25_Script_MoveRock)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_MoveRock_L_4_3 = {
    Set(LVar0, 32)
    Set(LVar1, 16)
    ExecWait(TTYD64_jan_25_Script_MoveRock)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_MoveRock_L_5_2 = {
    Set(LVar0, 33)
    Set(LVar1, 17)
    ExecWait(TTYD64_jan_25_Script_MoveRock)
    Return
    End
};

EvtScript TTYD64_jan_25_Script_MakeExits = {
    BindTrigger(TTYD64_jan_25_Script_Exit0, 0x80000, 10, 1, 0)
    Return
    End
};

EntryList TTYD64_jan_25_EntryList = {
    { 0.0f, 0.0f, 172.0f, 0.0f },
};

MapConfig TTYD64_mapcfg_jan_25 = {
    .id = "jan_25",
    .settings = &TTYD64_jan_25_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_jan_25(void) {
    TTYD64_jan_25_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_jan_25_String_Tattle);
}
