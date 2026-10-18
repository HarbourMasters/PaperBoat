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

extern EvtScript kzn_08_EVS_Chest_GetItem;
extern EvtScript kzn_08_EVS_OpenChest_DizzyStomp;

extern EvtScript TTYD64_kzn_08_Script_80244CFC;

// clang-format off
EvtScript TTYD64_kzn_08_Script_80244CFC = {
    Set(LVarA, 378)
    Set(LVarB, 2)
    Set(GameFlag(1324), 1)
    ExecWait(kzn_08_EVS_Chest_GetItem)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_kzn_08(void) {
    Mod_ReplaceScript("TTYD64", &kzn_08_EVS_OpenChest_DizzyStomp, &TTYD64_kzn_08_Script_80244CFC);
}
