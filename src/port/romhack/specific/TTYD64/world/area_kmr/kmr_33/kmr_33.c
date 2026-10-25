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

extern EvtScript TTYD64_kmr_33_Script_GiveItem;
extern EvtScript TTYD64_kmr_33_Script_Main;
extern EvtScript TTYD64_kmr_33_Script_ShowGotItem;
extern EvtScript TTYD64_kmr_33_Script_EnterMap;
extern EvtScript TTYD64_kmr_33_Script_OpenChest;
extern MapSettings TTYD64_kmr_33_Header;
extern EvtScript TTYD64_kmr_33_Script_Exit0;
extern EvtScript TTYD64_kmr_33_Script_SetupMusic;
extern EvtScript TTYD64_kmr_33_Script_CreateExitTriggers;
extern EntryList TTYD64_kmr_33_EntryList;

// clang-format off
EvtScript TTYD64_kmr_33_Script_GiveItem = {
    Call(DisablePlayerInput, 1)
    Set(LVar0, LVarA)
    IfNe(LVarA, 0)
        ExecWait(TTYD64_kmr_33_Script_ShowGotItem)
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

EvtScript TTYD64_kmr_33_Script_Main = {
    Set(GameByte(425), 30)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_kmr_33_Script_SetupMusic)
    Exec(TTYD64_kmr_33_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_kmr_33_Script_ShowGotItem = {
    SetGroup(0)
    Call(SetTimeFreezeMode, 2)
    Wait(40)
    Call(ShowGotItem, LVar0, 0, 0)
    Call(SetTimeFreezeMode, 0)
    Return
    Return
    End
};

EvtScript TTYD64_kmr_33_Script_EnterMap = {
    Call(MakeEntity, Ref(Entity_Chest), -111, 0, -47, 75, 0, 0x80000000)
    Call(AssignChestFlag, GameFlag(4215))
    Call(AssignScript, (Bytecode) TTYD64_kmr_33_Script_OpenChest)
    Exec(TTYD64_kmr_33_Script_CreateExitTriggers)
    Return
    End
};

EvtScript TTYD64_kmr_33_Script_OpenChest = {
    Set(LVarA, 241)
    Set(LVarB, 2)
    Set(GameFlag(4215), 1)
    ExecWait(TTYD64_kmr_33_Script_GiveItem)
    Return
    End
};

MapSettings TTYD64_kmr_33_Header = {
    .main = &TTYD64_kmr_33_Script_Main,
    .entryList = &TTYD64_kmr_33_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = NULL },
};

EvtScript TTYD64_kmr_33_Script_Exit0 = {
    Call(DisablePlayerInput, 1)
    Call(GotoMap, (Bytecode) "kmr_02", 11)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_kmr_33_Script_SetupMusic = {
    Call(SetMusic, 0, 16, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_kmr_33_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_kmr_33_Script_Exit0, 128, 9, 1, 0)
    Return
    End
};

EntryList TTYD64_kmr_33_EntryList = {
    { 152.0f, 0.0f, 0.0f, -90.0f },
};

MapConfig TTYD64_mapcfg_kmr_33 = {
    .id = "kmr_33",
    .settings = &TTYD64_kmr_33_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_kmr_33(void) {
}
