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
API_CALLABLE(GetEntryID);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_trd_11_Script_Main;
extern EvtScript TTYD64_trd_11_Script_EnterMap;
extern EvtScript TTYD64_trd_11_Script_MakeEntities;
extern EvtScript TTYD64_trd_11_Script_Exit0;
extern MapSettings TTYD64_trd_11_Header;
extern EvtScript TTYD64_trd_11_Script_Entity_Shine;
extern EvtScript TTYD64_trd_11_Script_SetupMusic;
extern u8 TTYD64_trd_11_MapTattle[];
extern EvtScript TTYD64_trd_11_Script_CreateExitTriggers;
extern EntryList TTYD64_trd_11_EntryList;

// clang-format off
static s32 TTYD64_trd_11_GetTattleMsg;

static s32 TTYD64_trd_11_GetTattle(void) {
    return TTYD64_trd_11_GetTattleMsg;
}

EvtScript TTYD64_trd_11_Script_Main = {
    Set(GameByte(425), 7)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_trd_11_Script_MakeEntities)
    Exec(TTYD64_trd_11_Script_SetupMusic)
    Exec(TTYD64_trd_11_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_trd_11_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVar0, (Bytecode) TTYD64_trd_11_Script_CreateExitTriggers)
        Exec(EnterWalk)
    CaseDefault
        Exec(TTYD64_trd_11_Script_CreateExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_trd_11_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SuperBlock), 0, 63, 0, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(4763))
    Call(AssignScript, (Bytecode) TTYD64_trd_11_Script_Entity_Shine)
    Return
    End
};

EvtScript TTYD64_trd_11_Script_Exit0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "trd_00", 6)
    Wait(100)
    Return
    End
};

MapSettings TTYD64_trd_11_Header = {
    .main = &TTYD64_trd_11_Script_Main,
    .entryList = &TTYD64_trd_11_EntryList,
    .entryCount = 1,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_trd_11_GetTattle },
};

EvtScript TTYD64_trd_11_Script_Entity_Shine = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(4763))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_trd_11_Script_SetupMusic = {
    Call(SetMusic, 0, 20, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

u8 TTYD64_trd_11_MapTattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x35, 0x48, 0x0C, 0xF7, 0x54, 0x48, 0x49, 0x53,
    0xF7, 0x4C, 0x4F, 0x4F, 0x4B, 0x53, 0xF7, 0x4C, 0x49, 0x4B, 0x45, 0xF7,
    0x53, 0x4F, 0x4D, 0x45, 0xF7, 0x4B, 0x49, 0x4E, 0x44, 0xF7, 0x4F, 0x46,
    0xF0, 0x57, 0x41, 0x52, 0x45, 0x48, 0x4F, 0x55, 0x53, 0x45, 0x0E, 0xF1,
    0xFD
};

EvtScript TTYD64_trd_11_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_trd_11_Script_Exit0, 0x80000, 1, 1, 0)
    Return
    End
};

EntryList TTYD64_trd_11_EntryList = {
    { -135.0f, 0.0f, -2.0f, 90.0f },
};

MapConfig TTYD64_mapcfg_trd_11 = {
    .id = "trd_11",
    .settings = &TTYD64_trd_11_Header,
    .bgName = "obk_bg",
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 3,
};
// clang-format on

void TTYD64_nm_Install_trd_11(void) {
    TTYD64_trd_11_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_trd_11_MapTattle);
}
