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

extern EvtScript obk_01_EVS_MakeEntities;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignPanelFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(MakeEntity);

extern EvtScript TTYD64_obk_01_Script_Entity_Shine1;
extern EvtScript TTYD64_obk_01_Script_MakeEntities;

// clang-format off
EvtScript TTYD64_obk_01_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(5093))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_obk_01_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_HiddenPanel), 675, -420, 415, 180, 47, 0x80000000)
    Call(AssignPanelFlag, GameFlag(961))
    Call(MakeEntity, Ref(Entity_SuperBlock), -95, -156, 114, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(5093))
    Call(AssignScript, Ref(TTYD64_obk_01_Script_Entity_Shine1))
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_obk_01(void) {
    Mod_ReplaceScript("TTYD64", &obk_01_EVS_MakeEntities, &TTYD64_obk_01_Script_MakeEntities);
}
