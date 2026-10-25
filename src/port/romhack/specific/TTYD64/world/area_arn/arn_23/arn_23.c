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

API_CALLABLE(GotoMap);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_arn_23_Script_Main;
extern EvtScript TTYD64_arn_23_Script_CreateExitTriggers;
extern EvtScript TTYD64_arn_23_Script_Exit1;
extern EvtScript TTYD64_arn_23_Script_Exit0;
extern EvtScript TTYD64_arn_23_Script_Exit3;
extern EvtScript TTYD64_arn_23_Script_Exit2;
extern EvtScript TTYD64_arn_23_Script_SetupMusic;
extern u8 TTYD64_arn_23_String_Tattle[];
extern EntryList TTYD64_arn_23_EntryList;
extern MapSettings TTYD64_arn_23_Header;
extern EvtScript TTYD64_arn_23_Script_EnterMap;

// clang-format off
static s32 TTYD64_arn_23_GetTattleMsg;

static s32 TTYD64_arn_23_GetTattle(void) {
    return TTYD64_arn_23_GetTattleMsg;
}

EvtScript TTYD64_arn_23_Script_Main = {
    Set(GameByte(425), 35)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_arn_23_Script_SetupMusic)
    Exec(TTYD64_arn_23_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_arn_23_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_arn_23_Script_Exit0, 0x80000, 0, 1, 0)
    BindTrigger(TTYD64_arn_23_Script_Exit1, 0x80000, 1, 1, 0)
    BindTrigger(TTYD64_arn_23_Script_Exit2, 0x80000, 2, 1, 0)
    BindTrigger(TTYD64_arn_23_Script_Exit3, 0x80000, 3, 1, 0)
    Return
    End
};

EvtScript TTYD64_arn_23_Script_Exit1 = {
    Set(AreaByte(0), 3)
    Call(UseExitHeading, 60, 1)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "arn_22", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_arn_23_Script_Exit0 = {
    Set(AreaByte(0), 2)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "arn_22", 3)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_arn_23_Script_Exit3 = {
    Set(AreaByte(0), 5)
    Call(UseExitHeading, 60, 3)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "arn_22", 2)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_arn_23_Script_Exit2 = {
    Set(AreaByte(0), 4)
    Call(UseExitHeading, 60, 2)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "arn_22", 1)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_arn_23_Script_SetupMusic = {
    Switch(GameByte(0))
    CaseDefault
        Call(SetMusic, 0, 29, 0, 8)
    EndSwitch
    Return
    End
};

u8 TTYD64_arn_23_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C, 0xF7, 0x48,
    0x45, 0x52, 0x45, 0xF7, 0x53, 0x4D, 0x45, 0x4C, 0x4C, 0x53, 0xF7, 0x57,
    0x45, 0x49, 0x52, 0x44, 0x01, 0xF0, 0x2F, 0x4E, 0x45, 0xF7, 0x4F, 0x46,
    0xF7, 0x54, 0x48, 0x45, 0xF7, 0x52, 0x45, 0x41, 0x53, 0x4F, 0x4E, 0x53,
    0xF7, 0x57, 0x48, 0x59, 0xF0, 0x29, 0xF7, 0x48, 0x41, 0x54, 0x45, 0xF7,
    0x43, 0x41, 0x56, 0x45, 0x53, 0x01, 0xF1, 0xFD
};

EntryList TTYD64_arn_23_EntryList = {
    { 192.0f, 0.0f, 68.0f, 90.0f },
    { 560.0f, 0.0f, -71.0f, -90.0f },
    { 560.0f, 0.0f, 66.0f, -90.0f },
    { 560.0f, 0.0f, 203.0f, -90.0f },
};

MapSettings TTYD64_arn_23_Header = {
    .main = &TTYD64_arn_23_Script_Main,
    .entryList = &TTYD64_arn_23_EntryList,
    .entryCount = 4,
    .background = NULL,
    .tattle = { .get = TTYD64_arn_23_GetTattle },
};

EvtScript TTYD64_arn_23_Script_EnterMap = {
    Set(LVar0, (Bytecode) TTYD64_arn_23_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};

MapConfig TTYD64_mapcfg_arn_23 = {
    .id = "arn_23",
    .settings = &TTYD64_arn_23_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 1,
};
// clang-format on

void TTYD64_nm_Install_arn_23(void) {
    TTYD64_arn_23_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_arn_23_String_Tattle);
}
