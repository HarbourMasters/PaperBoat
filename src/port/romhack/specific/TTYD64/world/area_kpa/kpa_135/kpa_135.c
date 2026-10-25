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

API_CALLABLE(AddItem);
API_CALLABLE(AssignChestFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetTimeFreezeMode);
API_CALLABLE(ShowGotItem);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_kpa_135_Script_GiveItem;
extern EvtScript TTYD64_kpa_135_Script_Main;
extern u8 TTYD64_kpa_135_String_Tattle[];
extern EvtScript TTYD64_kpa_135_Script_ShowGotItem;
extern EvtScript TTYD64_kpa_135_Script_Exit0;
extern EvtScript TTYD64_kpa_135_Script_MakeEntities;
extern EvtScript TTYD64_kpa_135_Script_OpenChest;
extern MapSettings TTYD64_kpa_135_Header;
extern EvtScript TTYD64_kpa_135_Script_SetupMusic;
extern EvtScript TTYD64_kpa_135_Script_CreateExitTriggers;
extern EntryList TTYD64_kpa_135_EntryList;

// clang-format off
static s32 TTYD64_kpa_135_GetTattleMsg;

static s32 TTYD64_kpa_135_GetTattle(void) {
    return TTYD64_kpa_135_GetTattleMsg;
}

EvtScript TTYD64_kpa_135_Script_GiveItem = {
    Call(DisablePlayerInput, 1)
    Set(LVar0, LVarA)
    IfNe(LVarA, 0)
        ExecWait(TTYD64_kpa_135_Script_ShowGotItem)
    EndIf
    Switch(LVarB)
    CaseEq(0)
        Call(AddItem, LVarA, LVar0)
    CaseEq(1)
        Call(TTYD64_nm_AddKeyItem, LVarA)
    CaseEq(2)
        Call(TTYD64_nm_AddBadge, LVarA, LVar0)
    EndSwitch
    Wait(15)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_kpa_135_Script_Main = {
    Set(GameByte(425), 22)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_kpa_135_Script_SetupMusic)
    Exec(TTYD64_kpa_135_Script_MakeEntities)
    Exec(TTYD64_kpa_135_Script_CreateExitTriggers)
    Return
    End
};

u8 TTYD64_kpa_135_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C, 0xF7, 0x29,
    0xF7, 0x4A, 0x55, 0x53, 0x54, 0xF7, 0x57, 0x4F, 0x4E, 0x44, 0x45, 0x52,
    0xF7, 0x57, 0x48, 0x4F, 0x53, 0x45, 0xF7, 0x49, 0x44, 0x45, 0x41, 0xF7,
    0x49, 0x54, 0xF0, 0x57, 0x41, 0x53, 0xF7, 0x54, 0x4F, 0xF7, 0x50, 0x55,
    0x54, 0xF7, 0x41, 0xF7, 0x53, 0x45, 0x43, 0x52, 0x45, 0x54, 0xF7, 0x52,
    0x4F, 0x4F, 0x4D, 0xF7, 0x4E, 0x45, 0x58, 0x54, 0xF7, 0x54, 0x4F, 0xF7,
    0x41, 0xF0, 0x43, 0x45, 0x4C, 0x4C, 0x1F, 0xF0, 0xF1, 0xFB, 0x29, 0xF7,
    0x44, 0x55, 0x55, 0x4E, 0x4F, 0x0C, 0xF7, 0x54, 0x48, 0x45, 0x59, 0xF7,
    0x53, 0x48, 0x4F, 0x55, 0x4C, 0x44, 0xF7, 0x46, 0x49, 0x52, 0x45, 0xF7,
    0x54, 0x48, 0x41, 0x54, 0xF0, 0x41, 0x52, 0x43, 0x48, 0x49, 0x54, 0x45,
    0x43, 0x54, 0x0C, 0xF7, 0x4A, 0x55, 0x53, 0x54, 0xF7, 0x4D, 0x59, 0xF7,
    0x4F, 0x50, 0x49, 0x4E, 0x49, 0x4F, 0x4E, 0x0E, 0xF1, 0xFD
};

EvtScript TTYD64_kpa_135_Script_ShowGotItem = {
    SetGroup(0)
    Call(SetTimeFreezeMode, 2)
    Wait(40)
    Call(ShowGotItem, LVar0, 0, 0)
    Call(SetTimeFreezeMode, 0)
    Return
    Return
    End
};

EvtScript TTYD64_kpa_135_Script_Exit0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "kpa_17", 2)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_kpa_135_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_Chest), -40, 0, -99, 0, 0, 0x80000000)
    Call(AssignChestFlag, GameFlag(5691))
    Call(AssignScript, (Bytecode) TTYD64_kpa_135_Script_OpenChest)
    Return
    End
};

EvtScript TTYD64_kpa_135_Script_OpenChest = {
    Set(LVarA, 375)
    Set(LVarB, 2)
    Set(GameFlag(5691), 1)
    ExecWait(TTYD64_kpa_135_Script_GiveItem)
    Return
    End
};

MapSettings TTYD64_kpa_135_Header = {
    .main = &TTYD64_kpa_135_Script_Main,
    .entryList = &TTYD64_kpa_135_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_kpa_135_GetTattle },
};

EvtScript TTYD64_kpa_135_Script_SetupMusic = {
    Call(SetMusic, 0, 100, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_kpa_135_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_kpa_135_Script_Exit0, 0x80000, 3, 1, 0)
    Return
    End
};

EntryList TTYD64_kpa_135_EntryList = {
    { 131.0f, 60.0f, -53.0f, -90.0f },
};

MapConfig TTYD64_mapcfg_kpa_135 = {
    .id = "kpa_135",
    .settings = &TTYD64_kpa_135_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 3,
};
// clang-format on

void TTYD64_nm_Install_kpa_135(void) {
    TTYD64_kpa_135_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_kpa_135_String_Tattle);
}
