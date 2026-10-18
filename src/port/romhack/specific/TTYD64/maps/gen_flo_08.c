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

extern EvtScript flo_08_EVS_MakeEntities;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);

extern EvtScript TTYD64_flo_08_Script_Entity_Shine1;
extern EvtScript TTYD64_flo_08_Script_MakeEntities;

// clang-format off
EvtScript TTYD64_flo_08_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(1402))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_flo_08_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SuperBlock), -780, 120, -110, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(1402))
    Call(AssignScript, Ref(TTYD64_flo_08_Script_Entity_Shine1))
    Call(MakeItemEntity, 348, 510, 0, -90, 17, GameFlag(1381))
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_flo_08(void) {
    Mod_ReplaceScript("TTYD64", &flo_08_EVS_MakeEntities, &TTYD64_flo_08_Script_MakeEntities);
}
