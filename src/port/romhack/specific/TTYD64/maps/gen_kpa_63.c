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

extern EvtScript kpa_63_EVS_SetupStarship;
extern EvtScript kpa_63_EVS_Starship_Update;

API_CALLABLE(MakeItemEntity);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(UpdateColliderTransform);

extern EvtScript TTYD64_kpa_63_Script_80241250;

// clang-format off
EvtScript TTYD64_kpa_63_Script_80241250 = {
    Call(MakeItemEntity, 348, -188, -34, 49, 17, GameFlag(5688))
    Call(MakeItemEntity, 140, -115, -34, 104, 17, GameFlag(5689))
    Call(MakeItemEntity, 149, -39, -34, 104, 17, GameFlag(5690))
    Call(MakeItemEntity, 343, -120, 0, 50, 17, 0)
    Call(MakeItemEntity, 343, -56, 0, 50, 17, 0)
    Call(MakeItemEntity, 343, 12, 0, 50, 17, 0)
    Exec(kpa_63_EVS_Starship_Update)
    Call(ParentColliderToModel, 20, 75)
    Loop(0)
        Call(UpdateColliderTransform, 20)
        Wait(1)
    EndLoop
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_kpa_63(void) {
    Mod_ReplaceScript("TTYD64", &kpa_63_EVS_SetupStarship, &TTYD64_kpa_63_Script_80241250);
}
