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
API_CALLABLE(GotoMap);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetTexPanner);
API_CALLABLE(StopSound);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_obk_14_Script_SetupTexturePan;
extern EvtScript TTYD64_obk_14_Script_Main;
extern EvtScript TTYD64_obk_14_Script_TexturePan_Update;
extern u8 TTYD64_obk_14_String_Tattle[];
extern EvtScript TTYD64_obk_14_Script_SetupMusic;
extern EvtScript TTYD64_obk_14_Script_Exit0;
extern MapSettings TTYD64_obk_14_Header;
extern EvtScript TTYD64_obk_14_Script_EnterMap;
extern EvtScript TTYD64_obk_14_Script_CreateExitTriggers;
extern EntryList TTYD64_obk_14_EntryList;

// clang-format off
static s32 TTYD64_obk_14_GetTattleMsg;

static s32 TTYD64_obk_14_GetTattle(void) {
    return TTYD64_obk_14_GetTattleMsg;
}

EvtScript TTYD64_obk_14_Script_SetupTexturePan = {
    Call(SetTexPanner, 22, 0)
    Call(SetTexPanner, 23, 0)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 300)
        Set(LVar2, 100)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_obk_14_Script_TexturePan_Update)
    EndThread
    Return
    End
};

EvtScript TTYD64_obk_14_Script_Main = {
    Set(GameByte(425), 13)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_obk_14_Script_SetupMusic)
    Exec(TTYD64_obk_14_Script_SetupTexturePan)
    Exec(TTYD64_obk_14_Script_EnterMap)
    Call(MakeItemEntity, 381, 42, 0, 19, 17, GameFlag(5092))
    Return
    End
};

EvtScript TTYD64_obk_14_Script_TexturePan_Update = {
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

u8 TTYD64_obk_14_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x37, 0x4F, 0x57, 0x0C, 0xF7, 0x54, 0x48, 0x49,
    0x53, 0xF7, 0x4D, 0x41, 0x4E, 0x53, 0x49, 0x4F, 0x4E, 0xF7, 0x49, 0x53,
    0xF7, 0x46, 0x49, 0x4C, 0x4C, 0x45, 0x44, 0xF7, 0x57, 0x49, 0x54, 0x48,
    0xF7, 0x41, 0xF0, 0x42, 0x55, 0x4E, 0x43, 0x48, 0xF7, 0x4F, 0x46, 0xF7,
    0x53, 0x45, 0x43, 0x52, 0x45, 0x54, 0xF7, 0x50, 0x41, 0x53, 0x53, 0x41,
    0x47, 0x45, 0x53, 0x0E, 0xF0, 0xF1, 0xFB, 0x29, 0xF7, 0x48, 0x4F, 0x50,
    0x45, 0xF7, 0x54, 0x48, 0x45, 0x52, 0x45, 0x07, 0x53, 0xF7, 0x41, 0x54,
    0xF7, 0x4C, 0x45, 0x41, 0x53, 0x54, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0x54,
    0x48, 0x49, 0x4E, 0x47, 0xF0, 0x47, 0x4F, 0x4F, 0x44, 0xF7, 0x41, 0x52,
    0x4F, 0x55, 0x4E, 0x44, 0xF7, 0x48, 0x45, 0x52, 0x45, 0xF7, 0x2D, 0x41,
    0x52, 0x49, 0x4F, 0x0E, 0xF0, 0xF1, 0xFD
};

EvtScript TTYD64_obk_14_Script_SetupMusic = {
    IfLt(GameByte(0), -16)
        Call(SetMusic, 0, 27, 0, 8)
    Else
        Call(SetMusic, 0, 28, 0, 8)
    EndIf
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_obk_14_Script_Exit0 = {
    Call(StopSound, 142)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "obk_05", 1)
    Wait(100)
    Return
    End
};

MapSettings TTYD64_obk_14_Header = {
    .main = &TTYD64_obk_14_Script_Main,
    .entryList = &TTYD64_obk_14_EntryList,
    .entryCount = 1,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_obk_14_GetTattle },
};

EvtScript TTYD64_obk_14_Script_EnterMap = {
    Set(LVar0, (Bytecode) TTYD64_obk_14_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

EvtScript TTYD64_obk_14_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_obk_14_Script_Exit0, 0x80000, 5, 1, 0)
    Return
    End
};

EntryList TTYD64_obk_14_EntryList = {
    { -34.0f, 0.0f, 19.0f, 90.0f },
};

MapConfig TTYD64_mapcfg_obk_14 = {
    .id = "obk_14",
    .settings = &TTYD64_obk_14_Header,
    .bgName = "obk_bg",
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 1,
};
// clang-format on

void TTYD64_nm_Install_obk_14(void) {
    TTYD64_obk_14_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_obk_14_String_Tattle);
}
