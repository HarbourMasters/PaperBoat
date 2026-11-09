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

extern NpcGroupList kpa_01_DefaultNPCs;
extern EvtScript kpa_01_EVS_CreateDarkness;
extern EvtScript kpa_01_EVS_EnterMap;
extern EvtScript kpa_01_EVS_Main;
extern EvtScript kpa_01_EVS_MakeEntities;
extern EvtScript kpa_01_EVS_SetupMusic;

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);

extern EvtScript TTYD64_kpa_01_Script_MakeEntities;
extern EvtScript TTYD64_kpa_01_Script_Main;

// clang-format off
EvtScript TTYD64_kpa_01_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_RedBlock), 220, 208, -125, 0, 388, 0x80000000)
    Call(AssignBlockFlag, GameFlag(1545))
    Return
    End
};

EvtScript TTYD64_kpa_01_Script_Main = {
    Set(GameByte(425), 22)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 1, Ref(kpa_01_DefaultNPCs))
    Call(MakeItemEntity, 348, -505, -53, 62, 17, GameFlag(5693))
    ExecWait(kpa_01_EVS_MakeEntities)
    Exec(kpa_01_EVS_CreateDarkness)
    Exec(kpa_01_EVS_EnterMap)
    Wait(1)
    Exec(kpa_01_EVS_SetupMusic)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_kpa_01(void) {
    Mod_ReplaceScript("TTYD64", &kpa_01_EVS_MakeEntities, &TTYD64_kpa_01_Script_MakeEntities);
    Mod_ReplaceScript("TTYD64", &kpa_01_EVS_Main, &TTYD64_kpa_01_Script_Main);
}
