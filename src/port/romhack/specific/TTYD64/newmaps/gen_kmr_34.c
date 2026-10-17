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
API_CALLABLE(MakeItemEntity);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_kmr_34_Script_EnterMap;
extern u8 TTYD64_kmr_34_String_Tattle[];
extern EvtScript TTYD64_kmr_34_Script_Main;
extern EvtScript TTYD64_kmr_34_Script_Exit0;
extern MapSettings TTYD64_kmr_34_Header;
extern EvtScript TTYD64_kmr_34_Script_SetupMusic;
extern EvtScript TTYD64_kmr_34_Script_CreateExitTriggers;
extern EvtScript TTYD64_kmr_34_Script_HammerBlock;
extern EntryList TTYD64_kmr_34_EntryList;

// clang-format off
static s32 TTYD64_kmr_34_GetTattleMsg;

static s32 TTYD64_kmr_34_GetTattle(void) {
    return TTYD64_kmr_34_GetTattleMsg;
}

EvtScript TTYD64_kmr_34_Script_EnterMap = {
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), 39, 60, -59, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(4208))
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), 99, 60, -59, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(4209))
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), 159, 60, -59, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(4210))
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), 219, 60, -59, 0, 343, 0x80000000)
    Call(AssignBlockFlag, GameFlag(4211))
    IfEq(GameFlag(4212), 0)
        Call(MakeEntity, Ref(Entity_Hammer1Block), 219, 0, -59, 0, 343, 0x80000000)
        Call(AssignScript, (Bytecode) TTYD64_kmr_34_Script_HammerBlock)
    EndIf
    Call(MakeItemEntity, 343, 465, 0, 50, 17, 0)
    Call(MakeItemEntity, 343, 466, 0, -25, 17, 0)
    Call(MakeItemEntity, 343, 466, 0, -110, 17, 0)
    Call(MakeItemEntity, 348, 467, 0, -189, 17, GameFlag(4213))
    Call(MakeItemEntity, 395, -356, 143, -170, 17, GameFlag(4214))
    Return
    End
};

u8 TTYD64_kmr_34_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x2E, 0x4F, 0x57, 0xF7, 0x54, 0x48, 0x41, 0x54,
    0xF7, 0x29, 0xF7, 0x54, 0x48, 0x49, 0x4E, 0x4B, 0xF7, 0x41, 0x42, 0x4F,
    0x55, 0x54, 0xF7, 0x49, 0x54, 0x0C, 0xF7, 0x49, 0x54, 0x07, 0x53, 0xF7,
    0x47, 0x4F, 0x4F, 0x44, 0xF0, 0x54, 0x48, 0x41, 0x54, 0xF7, 0x59, 0x4F,
    0x55, 0xF7, 0x4C, 0x41, 0x4E, 0x44, 0x45, 0x44, 0xF7, 0x4E, 0x45, 0x58,
    0x54, 0xF7, 0x54, 0x4F, 0xF7, 0x4F, 0x55, 0x52, 0xF7, 0x48, 0x4F, 0x4D,
    0x45, 0xF0, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0E, 0xF0, 0xF1, 0xFB, 0x37,
    0x48, 0x41, 0x54, 0xF7, 0x57, 0x4F, 0x55, 0x4C, 0x44, 0xF7, 0x48, 0x41,
    0x56, 0x45, 0xF7, 0x48, 0x41, 0x50, 0x50, 0x45, 0x4E, 0x45, 0x44, 0xF7,
    0x49, 0x46, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x48, 0x41, 0x44, 0xF0, 0x46,
    0x41, 0x4C, 0x4C, 0x45, 0x4E, 0xF7, 0x49, 0x4E, 0xF7, 0x41, 0xF7, 0x50,
    0x4C, 0x41, 0x43, 0x45, 0xF7, 0x57, 0x49, 0x54, 0x48, 0xF7, 0x4E, 0x4F,
    0xF7, 0x4F, 0x4E, 0x45, 0xF7, 0x41, 0x52, 0x4F, 0x55, 0x4E, 0x44, 0x0E,
    0x0E, 0x0E, 0xF0, 0xF1, 0xFB, 0x21, 0x4E, 0x59, 0x57, 0x41, 0x59, 0x53,
    0x0C, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x42, 0x45, 0x53, 0x54, 0xF7, 0x4F,
    0x46, 0xF7, 0x41, 0x4C, 0x4C, 0xF7, 0x49, 0x53, 0xF7, 0x54, 0x48, 0x41,
    0x4E, 0x4B, 0x53, 0xF0, 0x54, 0x4F, 0xF7, 0x54, 0x48, 0x41, 0x54, 0x0C,
    0xF7, 0x4E, 0x4F, 0x57, 0xF7, 0x57, 0x45, 0x07, 0x52, 0x45, 0xF7, 0x47,
    0x4F, 0x4F, 0x44, 0xF7, 0x46, 0x52, 0x49, 0x45, 0x4E, 0x44, 0x53, 0x01,
    0xF1, 0xFD
};

EvtScript TTYD64_kmr_34_Script_Main = {
    Set(GameByte(425), 30)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_kmr_34_Script_SetupMusic)
    Exec(TTYD64_kmr_34_Script_EnterMap)
    Set(LVar0, (Bytecode) TTYD64_kmr_34_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

EvtScript TTYD64_kmr_34_Script_Exit0 = {
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "kmr_00", 1)
    Wait(100)
    Return
    End
};

MapSettings TTYD64_kmr_34_Header = {
    .main = &TTYD64_kmr_34_Script_Main,
    .entryList = &TTYD64_kmr_34_EntryList,
    .entryCount = 1,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_kmr_34_GetTattle },
};

EvtScript TTYD64_kmr_34_Script_SetupMusic = {
    Call(SetMusic, 0, 16, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_kmr_34_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_kmr_34_Script_Exit0, 0x80000, 4, 1, 0)
    Return
    End
};

EvtScript TTYD64_kmr_34_Script_HammerBlock = {
    Set(GameFlag(4212), 1)
    Return
    End
};

EntryList TTYD64_kmr_34_EntryList = {
    { -370.0f, 0.0f, 170.0f, 0.0f },
};

MapConfig TTYD64_mapcfg_kmr_34 = {
    .id = "kmr_34",
    .settings = &TTYD64_kmr_34_Header,
    .bgName = "kmr_bg",
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_kmr_34(void) {
    TTYD64_kmr_34_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_kmr_34_String_Tattle);
}
