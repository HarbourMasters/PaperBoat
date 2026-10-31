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
#include "port/romhack/specific/TTYD64/world/maps.h"

extern EvtScript kmr_03_EVS_BindExitTriggers;
extern EvtScript kmr_03_EVS_ExitWalk_kmr_04_0;
extern EvtScript kmr_03_EVS_ExitWalk_kmr_05_0;
extern MapSettings kmr_03_settings;

API_CALLABLE(GotoMap);
API_CALLABLE(UseExitHeading);

extern EntryList TTYD64_kmr_03_EntryList;
extern EvtScript TTYD64_kmr_03_Script_802407A8;
extern EvtScript TTYD64_kmr_03_Script_Exit2;

// clang-format off
EntryList TTYD64_kmr_03_EntryList = {
    { -340.0f, 0.0f, 348.0f, 48.0f },
    { 480.0f, 0.0f, 0.0f, 270.0f },
    { -310.0f, 20.0f, -80.0f, 135.0f },
    { 433.0f, 227.0f, -301.0f, -135.0f },
};

EvtScript TTYD64_kmr_03_Script_802407A8 = {
    BindTrigger(kmr_03_EVS_ExitWalk_kmr_04_0, 0x80000, 3, 1, 0)
    BindTrigger(kmr_03_EVS_ExitWalk_kmr_05_0, 0x80000, 5, 1, 0)
    BindTrigger(TTYD64_kmr_03_Script_Exit2, 0x80000, 60, 1, 0)
    Return
    End
};

EvtScript TTYD64_kmr_03_Script_Exit2 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 3)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "kmr_32", 0)
    Wait(100)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_kmr_03(void) {
    kmr_03_settings.entryList = &TTYD64_kmr_03_EntryList;
    kmr_03_settings.entryCount = 4;
    Mod_ReplaceScript("TTYD64", &kmr_03_EVS_BindExitTriggers, &TTYD64_kmr_03_Script_802407A8);
}
