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

extern EvtScript kkj_24_EVS_SetupMusic;

API_CALLABLE(MakeItemEntity);
API_CALLABLE(SetMusic);

extern EvtScript TTYD64_kkj_24_Script_80240080;

// clang-format off
EvtScript TTYD64_kkj_24_Script_80240080 = {
    IfGe(GameByte(0), 95)
        Call(SetMusic, 0, 102, 0, 8)
    EndIf
    Call(MakeItemEntity, 417, -150, 0, 48, 17, GameFlag(4614))
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_kkj_24(void) {
    Mod_ReplaceScript("TTYD64", &kkj_24_EVS_SetupMusic, &TTYD64_kkj_24_Script_80240080);
}
