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

extern EvtScript sbk_56_EVS_MakeEntities;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(MakeEntity);

extern EvtScript TTYD64_sbk_56_Script_Entity_Shine1;
extern EvtScript TTYD64_sbk_56_Script_MakeEntities;

// clang-format off
EvtScript TTYD64_sbk_56_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(829))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_sbk_56_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_HeartBlock), 300, 60, 0, 0, 0x80000000)
    Call(MakeEntity, Ref(Entity_SuperBlock), -50, 60, 275, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(829))
    Call(AssignScript, Ref(TTYD64_sbk_56_Script_Entity_Shine1))
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_sbk_56(void) {
    Mod_ReplaceScript("TTYD64", &sbk_56_EVS_MakeEntities, &TTYD64_sbk_56_Script_MakeEntities);
}
