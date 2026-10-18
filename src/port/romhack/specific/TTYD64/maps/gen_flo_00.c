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

extern EvtScript flo_00_EVS_MakeEntities;

API_CALLABLE(MakeEntity);

extern EvtScript TTYD64_flo_00_Script_MakeEntities;

// clang-format off
EvtScript TTYD64_flo_00_Script_MakeEntities = {
    IfLt(GameByte(0), 96)
        Call(MakeEntity, Ref(Entity_SavePoint), 110, 60, -100, 0, 0x80000000)
        Call(MakeEntity, Ref(Entity_HeartBlock), 162, 60, -100, 0, 0x80000000)
    EndIf
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_flo_00(void) {
    Mod_ReplaceScript("TTYD64", &flo_00_EVS_MakeEntities, &TTYD64_flo_00_Script_MakeEntities);
}
