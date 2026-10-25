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

extern EvtScript tik_07_EVS_MakeEntities;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);

extern EvtScript TTYD64_tik_07_Script_Entity_Shine1;
extern EvtScript TTYD64_tik_07_Script_MakeEntities;

// clang-format off
EvtScript TTYD64_tik_07_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(433))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_tik_07_Script_MakeEntities = {
    Call(MakeItemEntity, 348, 306, 90, -104, 17, GameFlag(404))
    Call(MakeEntity, Ref(Entity_SuperBlock), 820, 70, -5, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(433))
    Call(AssignScript, Ref(TTYD64_tik_07_Script_Entity_Shine1))
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_tik_07(void) {
    Mod_ReplaceScript("TTYD64", &tik_07_EVS_MakeEntities, &TTYD64_tik_07_Script_MakeEntities);
}
