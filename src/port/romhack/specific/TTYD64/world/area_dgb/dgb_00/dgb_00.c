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

extern EvtScript dgb_00_EVS_MakeEntities;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(MakeEntity);

extern EvtScript TTYD64_dgb_00_Script_Entity_Shine1;
extern EvtScript TTYD64_dgb_00_Script_MakeEntities;

// clang-format off
EvtScript TTYD64_dgb_00_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(1))
    SetConst(LVar1, GameFlag(5168))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_dgb_00_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SavePoint), -65, 60, -240, 0, 0x80000000)
    Call(MakeEntity, Ref(Entity_SuperBlock), 966, 62, 260, 0, 0x80000000)
    Set(MapVar(1), LVar0)
    Call(AssignBlockFlag, GameFlag(5168))
    Call(AssignScript, Ref(TTYD64_dgb_00_Script_Entity_Shine1))
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_dgb_00(void) {
    Mod_ReplaceScript("TTYD64", &dgb_00_EVS_MakeEntities, &TTYD64_dgb_00_Script_MakeEntities);
}
