#include "common.h"
#include "effects.h"
#include "entity.h"
#include "foliage.h"
#include "map.h"
#include "npc.h"
#include "script_api/map.h"
#include <string.h>
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/maps/maps.h"

extern EvtScript kpa_17_EVS_BindExitTriggers;
extern EvtScript kpa_17_EVS_EnterMap;
extern EvtScript kpa_17_EVS_ExitWalk_kpa_1X_2;
extern EvtScript kpa_17_EVS_Scene_FallIntoCell;
extern MapSettings kpa_17_settings;

API_CALLABLE(GetEntryID);
API_CALLABLE(GotoMap);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_kpa_17_Script_EnterWalk_8024026C;
extern EvtScript TTYD64_kpa_17_Script_Exit2;
extern EvtScript TTYD64_kpa_17_Script_80240240;
extern EntryList TTYD64_kpa_17_EntryList;

// clang-format off
EvtScript TTYD64_kpa_17_Script_EnterWalk_8024026C = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Exec(kpa_17_EVS_BindExitTriggers)
        Exec(kpa_17_EVS_Scene_FallIntoCell)
    CaseEq(2)
        Exec(kpa_17_EVS_BindExitTriggers)
    CaseDefault
        Set(LVar0, Ref(kpa_17_EVS_BindExitTriggers))
        Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_kpa_17_Script_Exit2 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 2)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "kpa_135", 0)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_kpa_17_Script_80240240 = {
    BindTrigger(kpa_17_EVS_ExitWalk_kpa_1X_2, 0x80000, 14, 1, 0)
    BindTrigger(TTYD64_kpa_17_Script_Exit2, 0x80000, 24, 1, 0)
    Return
    End
};

EntryList TTYD64_kpa_17_EntryList = {
    { 1042.0f, 250.0f, -496.0f, 90.0f },
    { 1168.0f, 30.0f, -560.0f, 270.0f },
    { 777.0f, 29.0f, -564.0f, 90.0f },
};
// clang-format on

void TTYD64_InstallMap_kpa_17(void) {
    kpa_17_settings.entryList = &TTYD64_kpa_17_EntryList;
    kpa_17_settings.entryCount = 3;
    Mod_ReplaceScript("TTYD64", &kpa_17_EVS_EnterMap, &TTYD64_kpa_17_Script_EnterWalk_8024026C);
    Mod_ReplaceScript("TTYD64", &kpa_17_EVS_BindExitTriggers, &TTYD64_kpa_17_Script_80240240);
}
