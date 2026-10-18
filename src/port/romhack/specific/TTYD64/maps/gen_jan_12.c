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

extern EvtScript jan_12_EVS_MakeEntities;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(MakeEntity);

extern EvtScript TTYD64_jan_12_Script_MakeEntities;

// clang-format off
EvtScript TTYD64_jan_12_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_PinkFlower), 130, 0, -110, 170, 0x80000000)
    Call(MakeEntity, Ref(Entity_BellbellPlant), -350, 30, -55, 25, 0x80000000)
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), -310, 90, -25, 0, 398, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1250))
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_jan_12(void) {
    Mod_ReplaceScript("TTYD64", &jan_12_EVS_MakeEntities, &TTYD64_jan_12_Script_MakeEntities);
}
