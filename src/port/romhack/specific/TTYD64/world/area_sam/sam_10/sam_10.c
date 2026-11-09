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

extern EvtScript sam_10_EVS_MakeEntities;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(DropResizableItemEntity);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(sam_10_SetStarStoneItemScale);

extern EvtScript TTYD64_sam_10_Script_MakeEntities;

// clang-format off
EvtScript TTYD64_sam_10_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_RedBlock), 775, 540, -50, 0, 289, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1463))
    Call(MakeItemEntity, 348, -160, 300, -110, 17, GameFlag(1464))
    IfLt(GameByte(0), 77)
        Call(DropResizableItemEntity, 108, 0, -1000, 0, 1, 0)
        Call(sam_10_SetStarStoneItemScale)
        Set(MapVar(0), LVar0)
    Else
        Call(DropResizableItemEntity, 108, -117, 179, -55, 1, 0)
        Call(sam_10_SetStarStoneItemScale)
    EndIf
    Call(MakeEntity, Ref(Entity_SavePoint), -250, 870, -210, 0, 0x80000000)
    Call(MakeEntity, Ref(Entity_HeartBlock), 770, 1200, -225, 0, 0x80000000)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_sam_10(void) {
    Mod_ReplaceScript("TTYD64", &sam_10_EVS_MakeEntities, &TTYD64_sam_10_Script_MakeEntities);
}
