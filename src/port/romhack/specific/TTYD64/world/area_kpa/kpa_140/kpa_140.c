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

API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_kpa_140_Script_Main;
extern EvtScript TTYD64_kpa_140_Script_Exit0;
extern u8 TTYD64_kpa_140_String_Tattle[];
extern MapSettings TTYD64_kpa_140_Header;
extern EvtScript TTYD64_kpa_140_Script_SetupMusic;
extern EvtScript TTYD64_kpa_140_Script_EnterMap;
extern EvtScript TTYD64_kpa_140_Script_MakeExits;
extern EntryList TTYD64_kpa_140_EntryList;

// clang-format off
static s32 TTYD64_kpa_140_GetTattleMsg;

static s32 TTYD64_kpa_140_GetTattle(void) {
    return TTYD64_kpa_140_GetTattleMsg;
}

EvtScript TTYD64_kpa_140_Script_Main = {
    Set(GameByte(425), 22)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_kpa_140_Script_SetupMusic)
    Exec(TTYD64_kpa_140_Script_EnterMap)
    Set(LVar0, (Bytecode) TTYD64_kpa_140_Script_MakeExits)
    Exec(EnterWalk)
    Return
    End
};

EvtScript TTYD64_kpa_140_Script_Exit0 = {
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Set(AreaByte(15), 5)
    Call(GotoMap, (Bytecode) "kpa_41", 1)
    Wait(100)
    Return
    End
};

u8 TTYD64_kpa_140_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x37, 0x45, 0x4C, 0x4C, 0x0C, 0xF7, 0x49, 0x54,
    0x07, 0x53, 0xF7, 0x4E, 0x4F, 0x54, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x52,
    0x4F, 0x55, 0x54, 0x45, 0xF7, 0x57, 0x45, 0xF7, 0x45, 0x58, 0x50, 0x45,
    0x43, 0x54, 0x45, 0x44, 0xF0, 0x42, 0x55, 0x54, 0xF7, 0x41, 0x54, 0xF7,
    0x4C, 0x45, 0x41, 0x53, 0x54, 0xF7, 0x57, 0x45, 0xF7, 0x46, 0x4F, 0x55,
    0x4E, 0x44, 0xF7, 0x41, 0xF7, 0x53, 0x45, 0x43, 0x52, 0x45, 0x54, 0x01,
    0xF1, 0xFD
};

MapSettings TTYD64_kpa_140_Header = {
    .main = &TTYD64_kpa_140_Script_Main,
    .entryList = &TTYD64_kpa_140_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_kpa_140_GetTattle },
};

EvtScript TTYD64_kpa_140_Script_SetupMusic = {
    Call(SetMusic, 0, 100, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_kpa_140_Script_EnterMap = {
    Call(MakeItemEntity, 287, -100, 20, 100, 17, GameFlag(5699))
    Return
    End
};

EvtScript TTYD64_kpa_140_Script_MakeExits = {
    BindTrigger(TTYD64_kpa_140_Script_Exit0, 0x80000, 11, 1, 0)
    Return
    End
};

EntryList TTYD64_kpa_140_EntryList = {
    { -199.0f, 0.0f, 100.0f, -270.0f },
};

MapConfig TTYD64_mapcfg_kpa_140 = {
    .id = "kpa_140",
    .settings = &TTYD64_kpa_140_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 3,
};
// clang-format on

void TTYD64_nm_Install_kpa_140(void) {
    TTYD64_kpa_140_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_kpa_140_String_Tattle);
}
