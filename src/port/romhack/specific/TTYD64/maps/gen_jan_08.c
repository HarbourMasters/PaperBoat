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

extern EvtScript jan_08_EVS_MakeEntities;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);

extern EvtScript TTYD64_jan_08_Script_Entity_Shine1;
extern EvtScript TTYD64_jan_08_Script_MakeEntities;

// clang-format off
EvtScript TTYD64_jan_08_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(2))
    SetConst(LVar1, GameFlag(1278))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_jan_08_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SuperBlock), 250, 60, 300, 0, 0x80000000)
    Set(MapVar(2), LVar0)
    Call(AssignBlockFlag, GameFlag(1278))
    Call(AssignScript, Ref(TTYD64_jan_08_Script_Entity_Shine1))
    Call(MakeItemEntity, 343, 75, -60, 90, 17, GameFlag(1279))
    Call(MakeItemEntity, 343, 100, -60, 90, 17, GameFlag(1280))
    Call(MakeItemEntity, 343, 125, -60, 90, 17, GameFlag(1281))
    Call(MakeEntity, Ref(Entity_BellbellPlant), 54, 0, -380, 35, 0x80000000)
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), 24, 60, -410, 0, 130, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1249))
    Call(MakeEntity, Ref(Entity_TrumpetPlant), -450, 0, 166, 170, 0x80000000)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_jan_08(void) {
    Mod_ReplaceScript("TTYD64", &jan_08_EVS_MakeEntities, &TTYD64_jan_08_Script_MakeEntities);
}
