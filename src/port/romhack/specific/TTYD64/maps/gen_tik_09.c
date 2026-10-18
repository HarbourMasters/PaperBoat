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

extern EvtScript tik_09_EVS_BindExitTriggers;
extern EvtScript tik_09_EVS_ExitWalk_tik_08_0;
extern EvtScript tik_09_EVS_ExitWalk_tik_10_0;
extern MapSettings tik_09_settings;

API_CALLABLE(GotoMap);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_tik_09_Script_80242358;
extern EvtScript TTYD64_tik_09_Script_Exit4;
extern EvtScript TTYD64_tik_09_Script_Exit3;
extern EntryList TTYD64_tik_09_EntryList;

// clang-format off
EvtScript TTYD64_tik_09_Script_80242358 = {
    BindTrigger(tik_09_EVS_ExitWalk_tik_10_0, 0x80000, 9, 1, 0)
    BindTrigger(tik_09_EVS_ExitWalk_tik_08_0, 0x80000, 5, 1, 0)
    BindTrigger(TTYD64_tik_09_Script_Exit3, 0x80000, 19, 1, 0)
    BindTrigger(TTYD64_tik_09_Script_Exit4, 0x80000, 20, 1, 0)
    Return
    End
};

EvtScript TTYD64_tik_09_Script_Exit4 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 4)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "tik_10", 1)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_tik_09_Script_Exit3 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 3)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "tik_08", 5)
    Wait(100)
    Return
    End
};

EntryList TTYD64_tik_09_EntryList = {
    { -225.0f, -10.0f, 0.0f, 90.0f },
    { 325.0f, -10.0f, 0.0f, 270.0f },
    { -30.0f, 25.0f, -40.0f, 180.0f },
    { 327.0f, -18.0f, 112.0f, -90.0f },
    { -232.0f, -18.0f, 112.0f, 90.0f },
};
// clang-format on

void TTYD64_InstallMap_tik_09(void) {
    tik_09_settings.entryList = &TTYD64_tik_09_EntryList;
    tik_09_settings.entryCount = 5;
    Mod_ReplaceScript("TTYD64", &tik_09_EVS_BindExitTriggers, &TTYD64_tik_09_Script_80242358);
}
