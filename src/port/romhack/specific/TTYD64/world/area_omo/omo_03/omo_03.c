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

extern EvtScript omo_03_EVS_MakeEntities;
extern EvtScript omo_03_EVS_UseSpring_Exit;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignPanelFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(MakeEntity);

extern EvtScript TTYD64_omo_03_Script_MakeEntities;

// clang-format off
EvtScript TTYD64_omo_03_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SavePoint), -250, 60, 50, 0, 0x80000000)
    Call(MakeEntity, Ref(Entity_ScriptSpring), -150, 0, 250, 0, 0x80000000)
    Call(AssignScript, Ref(omo_03_EVS_UseSpring_Exit))
    Call(MakeEntity, Ref(Entity_HiddenPanel), 203, 0, 200, 0, 25, 0x80000000)
    Call(AssignPanelFlag, GameFlag(1190))
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), 400, 60, -50, 0, 398, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1117))
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_omo_03(void) {
    Mod_ReplaceScript("TTYD64", &omo_03_EVS_MakeEntities, &TTYD64_omo_03_Script_MakeEntities);
}
