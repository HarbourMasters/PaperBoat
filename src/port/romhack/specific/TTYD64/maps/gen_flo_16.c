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

extern EvtScript flo_16_EVS_MakeEntities;
extern EvtScript flo_16_EVS_MonitorCeilingPound;
extern EvtScript flo_16_EVS_UseSpring;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(MakeEntity);

extern EvtScript TTYD64_flo_16_Script_Entity_Shine1;
extern EvtScript TTYD64_flo_16_Script_MakeEntities;

// clang-format off
EvtScript TTYD64_flo_16_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(1403))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_flo_16_Script_MakeEntities = {
    Set(AreaFlag(39), 0)
    BindTrigger(flo_16_EVS_MonitorCeilingPound, 128, 20, 1, 0)
    Call(MakeEntity, Ref(Entity_SuperBlock), 350, 240, -100, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(1403))
    Call(AssignScript, Ref(TTYD64_flo_16_Script_Entity_Shine1))
    Call(MakeEntity, Ref(Entity_ScriptSpring), 472, 100, -100, 0, 0x80000000)
    Call(AssignScript, Ref(flo_16_EVS_UseSpring))
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_flo_16(void) {
    Mod_ReplaceScript("TTYD64", &flo_16_EVS_MakeEntities, &TTYD64_flo_16_Script_MakeEntities);
}
