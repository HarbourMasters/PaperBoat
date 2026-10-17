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

API_CALLABLE(DisablePlayerInput);
API_CALLABLE(GetPlayerActionState);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtCollider);
API_CALLABLE(RotateGroup);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(ShakeCam);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_kkj_30_Script_Bookcase_UpdatePlayer;
extern EvtScript TTYD64_kkj_30_Script_BookcaseFalls;
extern EvtScript TTYD64_kkj_30_Script_EnterMap;
extern EvtScript TTYD64_kkj_30_Script_Main;
extern u8 TTYD64_kkj_30_String_Tattle[];
extern EvtScript TTYD64_kkj_30_Script_Exit0;
extern MapSettings TTYD64_kkj_30_Header;
extern EvtScript TTYD64_kkj_30_Script_CreateExitTriggers;
extern EntryList TTYD64_kkj_30_EntryList;

// clang-format off
static s32 TTYD64_kkj_30_GetTattleMsg;

static s32 TTYD64_kkj_30_GetTattle(void) {
    return TTYD64_kkj_30_GetTattleMsg;
}

EvtScript TTYD64_kkj_30_Script_Bookcase_UpdatePlayer = {
    Loop(0)
        IfEq(MapVar(0), 1)
            Call(TTYD64_ReadField, TTYD64_F_GCOLLISIONSTATUS_8_2U, LVar0)
            IfEq(LVar0, 0)
                Call(DisablePlayerInput, 1)
                Loop(0)
                    Call(GetPlayerActionState, LVar0)
                    Switch(LVar0)
                    CaseOrEq(0)
                    CaseOrEq(33)
                        BreakLoop
                        EndCaseGroup
                    EndSwitch
                    Wait(1)
                EndLoop
                Call(SetPlayerAnimation, 0x10002)
                Call(SetPlayerAnimation, 0x10014)
                Loop(0)
                    IfEq(MapVar(1), 1)
                        Call(SetPlayerAnimation, 0x1000F)
                        Wait(10)
                        Call(SetPlayerAnimation, 0x10030)
                        Wait(15)
                        Call(SetPlayerAnimation, 0x10031)
                        Thread
                            Call(PlaySound, 370)
                            Wait(12)
                            Call(PlaySound, 370)
                        EndThread
                        Wait(12)
                        Call(DisablePlayerInput, 0)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
            EndIf
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_kkj_30_Script_BookcaseFalls = {
    Call(ModifyColliderFlags, 0, 21, 0x7FFFFE00)
    Set(MapVar(0), 1)
    Call(MakeLerp, 0, -90, 30, 3)
    Label(10)
    Call(UpdateLerp)
    Call(RotateGroup, 80, LVar0, -1, 0, 0)
    Call(UpdateColliderTransform, 0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(10)
    EndIf
    Set(MapVar(0), 0)
    Call(PlaySoundAtCollider, 0, 247, 0)
    Thread
        Call(ShakeCam, 0, 0, 30, Float(1.5))
    EndThread
    Wait(60)
    Set(MapVar(1), 1)
    Call(MakeLerp, -90, 0, 30, 0)
    Label(15)
    Call(UpdateLerp)
    Call(RotateGroup, 80, LVar0, -1, 0, 0)
    Call(UpdateColliderTransform, 0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(15)
    EndIf
    Set(MapVar(1), 0)
    Call(ModifyColliderFlags, 1, 21, 0x7FFFFE00)
    Return
    End
};

EvtScript TTYD64_kkj_30_Script_EnterMap = {
    Call(MakeItemEntity, 287, -371, 100, -122, 17, GameFlag(4609))
    Call(MakeItemEntity, 348, 0, 0, -206, 17, GameFlag(4610))
    Call(MakeItemEntity, 348, -178, 100, 209, 17, GameFlag(4611))
    Call(ParentColliderToModel, 0, 77)
    Exec(TTYD64_kkj_30_Script_Bookcase_UpdatePlayer)
    BindTrigger(TTYD64_kkj_30_Script_BookcaseFalls, 0x80000, 20, 1, 0)
    BindTrigger(TTYD64_kkj_30_Script_BookcaseFalls, 256, 21, 1, 0)
    Call(DisablePlayerInput, 1)
    Wait(5)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_kkj_30_Script_Main = {
    Set(GameByte(425), 26)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_kkj_30_Script_EnterMap)
    Exec(TTYD64_kkj_30_Script_CreateExitTriggers)
    Return
    End
};

u8 TTYD64_kkj_30_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C, 0xF7, 0x53,
    0x4F, 0x4D, 0x45, 0x54, 0x49, 0x4D, 0x45, 0x53, 0xF7, 0x29, 0xF7, 0x52,
    0x45, 0x41, 0x4C, 0x4C, 0x59, 0xF7, 0x57, 0x4F, 0x4E, 0x44, 0x45, 0x52,
    0xF7, 0x48, 0x4F, 0x57, 0xF0, 0x4D, 0x41, 0x4E, 0x59, 0xF7, 0x53, 0x45,
    0x43, 0x52, 0x45, 0x54, 0xF7, 0x52, 0x4F, 0x4F, 0x4D, 0x53, 0xF7, 0x44,
    0x4F, 0x45, 0x53, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7, 0x43, 0x41, 0x53,
    0x54, 0x4C, 0x45, 0xF0, 0x48, 0x41, 0x56, 0x45, 0x1F, 0xF1, 0xFD
};

EvtScript TTYD64_kkj_30_Script_Exit0 = {
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "kkj_16", 1)
    Wait(100)
    Return
    End
};

MapSettings TTYD64_kkj_30_Header = {
    .main = &TTYD64_kkj_30_Script_Main,
    .entryList = &TTYD64_kkj_30_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_kkj_30_GetTattle },
};

EvtScript TTYD64_kkj_30_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_kkj_30_Script_Exit0, 128, 17, 1, 0)
    Return
    End
};

EntryList TTYD64_kkj_30_EntryList = {
    { 314.0f, 0.0f, -142.0f, -90.0f },
};

MapConfig TTYD64_mapcfg_kkj_30 = {
    .id = "kkj_30",
    .settings = &TTYD64_kkj_30_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_kkj_30(void) {
    TTYD64_kkj_30_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_kkj_30_String_Tattle);
}
