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

extern EvtScript pra_35_EVS_Chest_GetItem;
extern EvtScript pra_35_EVS_OpenChest_TripleDip;

extern EvtScript TTYD64_pra_35_Script_80243F2C;

// clang-format off
EvtScript TTYD64_pra_35_Script_80243F2C = {
    Set(LVarA, 233)
    Set(LVarB, 2)
    Set(GameFlag(1517), 1)
    ExecWait(pra_35_EVS_Chest_GetItem)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_pra_35(void) {
    Mod_ReplaceScript("TTYD64", &pra_35_EVS_OpenChest_TripleDip, &TTYD64_pra_35_Script_80243F2C);
}
