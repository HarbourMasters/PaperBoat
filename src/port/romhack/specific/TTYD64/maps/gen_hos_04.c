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

extern EvtScript hos_04_EVS_SetupNarrator;

API_CALLABLE(GetEntryID);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(hos_04_SetCurtainCallback);
API_CALLABLE(hos_04_curtain_callback_narration);

extern EvtScript TTYD64_hos_04_Script_80243294;

// clang-format off
EvtScript TTYD64_hos_04_Script_80243294 = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(4)
        Call(hos_04_SetCurtainCallback, (Bytecode) hos_04_curtain_callback_narration)
    EndSwitch
    Call(MakeItemEntity, 348, 272, 100, 217, 17, GameFlag(4642))
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_hos_04(void) {
    Mod_ReplaceScript("TTYD64", &hos_04_EVS_SetupNarrator, &TTYD64_hos_04_Script_80243294);
}
