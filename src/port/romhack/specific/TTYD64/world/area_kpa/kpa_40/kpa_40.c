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

extern EvtScript kpa_40_EVS_ExitWalk_kpa_40_3;
extern EvtScript kpa_40_EVS_ExitWalk_kpa_41_3;

API_CALLABLE(GotoMap);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_kpa_40_Script_ExitWalk_802401F0;
extern EvtScript TTYD64_kpa_40_Script_ExitWalk_80240194;

// clang-format off
EvtScript TTYD64_kpa_40_Script_ExitWalk_802401F0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 2)
    Exec(ExitWalk)
    Set(AreaByte(11), 1)
    Set(AreaByte(15), 0)
    Call(GotoMap, (Bytecode) "kpa_41", 3)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_kpa_40_Script_ExitWalk_80240194 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 1)
    Exec(ExitWalk)
    Set(AreaByte(11), 0)
    Set(AreaByte(15), 1)
    Call(GotoMap, (Bytecode) "kpa_41", 0)
    Wait(100)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_kpa_40(void) {
    Mod_ReplaceScript("TTYD64", &kpa_40_EVS_ExitWalk_kpa_41_3, &TTYD64_kpa_40_Script_ExitWalk_802401F0);
    Mod_ReplaceScript("TTYD64", &kpa_40_EVS_ExitWalk_kpa_40_3, &TTYD64_kpa_40_Script_ExitWalk_80240194);
}
