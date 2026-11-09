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

extern EvtScript jan_05_EVS_MakeEntities;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(MakeEntity);

extern EvtScript TTYD64_jan_05_Script_MakeEntities;

// clang-format off
EvtScript TTYD64_jan_05_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_RedBlock), 0, 60, 0, 0, 232, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1238))
    Call(MakeEntity, Ref(Entity_CymbalPlant), 205, 0, 220, 0, 0x80000000)
    Call(MakeEntity, Ref(Entity_TrumpetPlant), -386, 0, -214, 160, 0x80000000)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_jan_05(void) {
    Mod_ReplaceScript("TTYD64", &jan_05_EVS_MakeEntities, &TTYD64_jan_05_Script_MakeEntities);
}
