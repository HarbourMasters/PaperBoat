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
#include "port/romhack/specific/TTYD64/newmaps_tyd_pit/tp.h"

extern EvtScript TTYD64_tes_00_Script_Entity_Shine1;

// clang-format off
EvtScript TTYD64_tes_00_Script_Entity_Shine1 = {
    Set(LVar0, 0)
    SetConst(LVar1, GameFlag(17))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_tes_00(void) {
}
