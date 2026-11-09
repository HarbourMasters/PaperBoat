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

extern EvtScript flo_13_EVS_MakeEntities;
extern EvtScript flo_13_EVS_OnBlast_Rock;

API_CALLABLE(AssignScript);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(ModifyColliderFlags);

extern EvtScript TTYD64_flo_13_Script_MakeEntities;

// clang-format off
EvtScript TTYD64_flo_13_Script_MakeEntities = {
    Call(MakeItemEntity, 292, -61, 60, -85, 17, GameFlag(1385))
    Call(MakeItemEntity, 131, 128, 0, 157, 17, GameFlag(1386))
    IfEq(GameFlag(1385), 0)
        Call(MakeEntity, Ref(Entity_BombableRock), -160, 160, -90, 0, 0x80000000)
        Call(AssignScript, Ref(flo_13_EVS_OnBlast_Rock))
    Else
        Call(ModifyColliderFlags, 0, 14, 0x7FFFFE00)
    EndIf
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_flo_13(void) {
    Mod_ReplaceScript("TTYD64", &flo_13_EVS_MakeEntities, &TTYD64_flo_13_Script_MakeEntities);
}
