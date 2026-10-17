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
API_CALLABLE(AssignScript);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(UseExitHeading);
API_CALLABLE(jan_17_EnableFog);

extern EvtScript TTYD64_jan_27_Script_MakeEntities;
extern EvtScript TTYD64_jan_27_Script_Main;
extern u8 TTYD64_jan_27_String_Tattle[];
extern EvtScript TTYD64_jan_27_Script_Exit0;
extern MapSettings TTYD64_jan_27_Header;
extern EvtScript TTYD64_jan_27_Script_Entity_Shine1;
extern EvtScript TTYD64_jan_27_Script_SetupMusic;
extern EvtScript TTYD64_jan_27_Script_EnterMap;
extern EvtScript TTYD64_jan_27_Script_CreateExitTriggers;
extern EntryList TTYD64_jan_27_EntryList;

// clang-format off
static s32 TTYD64_jan_27_GetTattleMsg;

static s32 TTYD64_jan_27_GetTattle(void) {
    return TTYD64_jan_27_GetTattleMsg;
}

EvtScript TTYD64_jan_27_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SimpleSpring), -161, 0, 74, 0, 60, 0x80000000)
    Call(MakeEntity, Ref(Entity_SimpleSpring), -109, 57, 98, 0, 60, 0x80000000)
    Call(MakeEntity, Ref(Entity_SimpleSpring), -45, 109, 70, 0, 60, 0x80000000)
    Call(MakeEntity, Ref(Entity_SimpleSpring), 10, 109, 17, 0, 60, 0x80000000)
    Call(MakeEntity, Ref(Entity_SimpleSpring), 0, 109, -40, 0, 60, 0x80000000)
    Call(MakeEntity, Ref(Entity_SimpleSpring), -57, 109, -100, 0, 60, 0x80000000)
    Call(MakeEntity, Ref(Entity_SimpleSpring), -135, 109, -91, 0, 60, 0x80000000)
    Call(MakeEntity, Ref(Entity_SimpleSpring), -197, 109, -55, 0, 60, 0x80000000)
    Call(MakeEntity, Ref(Entity_SuperBlock), -202, 266, 3, -180, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(5385))
    Call(AssignScript, (Bytecode) TTYD64_jan_27_Script_Entity_Shine1)
    Return
    End
};

EvtScript TTYD64_jan_27_Script_Main = {
    Set(GameByte(425), 36)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(jan_17_EnableFog)
    Exec(TTYD64_jan_27_Script_MakeEntities)
    Exec(TTYD64_jan_27_Script_SetupMusic)
    Exec(TTYD64_jan_27_Script_EnterMap)
    Return
    End
};

u8 TTYD64_jan_27_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x37, 0x4F, 0x57, 0x0C, 0xF7, 0x41, 0x4E, 0x4F,
    0x54, 0x48, 0x45, 0x52, 0xF7, 0x45, 0x4E, 0x54, 0x52, 0x41, 0x4E, 0x43,
    0x45, 0xF7, 0x49, 0x4E, 0x53, 0x49, 0x44, 0x45, 0xF7, 0x54, 0x48, 0x45,
    0xF0, 0x42, 0x49, 0x47, 0xF7, 0x54, 0x52, 0x45, 0x45, 0x1F, 0xF0, 0xF1,
    0xFB, 0x2E, 0x4F, 0x57, 0xF7, 0x29, 0x07, 0x4D, 0xF7, 0x57, 0x4F, 0x4E,
    0x44, 0x45, 0x52, 0x49, 0x4E, 0x47, 0xF7, 0x48, 0x4F, 0x57, 0xF7, 0x42,
    0x49, 0x47, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF0, 0x54, 0x52, 0x45, 0x45,
    0xF7, 0x45, 0x58, 0x41, 0x43, 0x54, 0x4C, 0x59, 0xF7, 0x49, 0x53, 0x1F,
    0x01, 0xF0, 0xF1, 0xFD
};

EvtScript TTYD64_jan_27_Script_Exit0 = {
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "jan_16", 5)
    Wait(100)
    Return
    End
};

MapSettings TTYD64_jan_27_Header = {
    .main = &TTYD64_jan_27_Script_Main,
    .entryList = &TTYD64_jan_27_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_jan_27_GetTattle },
};

EvtScript TTYD64_jan_27_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(5385))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_jan_27_Script_SetupMusic = {
    Call(SetMusic, 0, 40, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_jan_27_Script_EnterMap = {
    Set(LVar0, (Bytecode) TTYD64_jan_27_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

EvtScript TTYD64_jan_27_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_jan_27_Script_Exit0, 0x80000, 5, 1, 0)
    Return
    End
};

EntryList TTYD64_jan_27_EntryList = {
    { -201.0f, 0.0f, 3.0f, 90.0f },
};

MapConfig TTYD64_mapcfg_jan_27 = {
    .id = "jan_27",
    .settings = &TTYD64_jan_27_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_jan_27(void) {
    TTYD64_jan_27_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_jan_27_String_Tattle);
}
