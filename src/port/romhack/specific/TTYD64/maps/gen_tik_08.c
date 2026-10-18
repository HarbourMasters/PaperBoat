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

extern EvtScript tik_08_EVS_BindExitTriggers;
extern EvtScript tik_08_EVS_ExitPipe_tik_06_2;
extern EvtScript tik_08_EVS_ExitWalk_tik_09_1;
extern EvtScript tik_08_EVS_ExitWalk_tik_20_0;
extern MapSettings tik_08_settings;

API_CALLABLE(GotoMap);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_tik_08_Script_Exit5;
extern EntryList TTYD64_tik_08_EntryList;
extern EvtScript TTYD64_tik_08_Script_80241ABC;

// clang-format off
EvtScript TTYD64_tik_08_Script_Exit5 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 5)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "tik_09", 3)
    Wait(100)
    Return
    End
};

EntryList TTYD64_tik_08_EntryList = {
    { -520.0f, -10.0f, 0.0f, 90.0f },
    { 170.0f, -10.0f, 0.0f, 270.0f },
    { -375.0f, 200.0f, 0.0f, 90.0f },
    { -467.0f, -10.0f, -110.0f, 90.0f },
    { 95.0f, 25.0f, -88.0f, 180.0f },
    { -532.0f, -30.0f, 107.0f, 90.0f },
};

EvtScript TTYD64_tik_08_Script_80241ABC = {
    BindTrigger(tik_08_EVS_ExitWalk_tik_09_1, 0x80000, 19, 1, 0)
    BindTrigger(tik_08_EVS_ExitWalk_tik_20_0, 0x80000, 24, 1, 0)
    Call(ModifyColliderFlags, 1, 29, 0x7FFFFE00)
    BindTrigger(tik_08_EVS_ExitPipe_tik_06_2, 64, 29, 1, 0)
    BindTrigger(TTYD64_tik_08_Script_Exit5, 0x80000, 32, 1, 0)
    Return
    End
};
// clang-format on

void TTYD64_InstallMap_tik_08(void) {
    tik_08_settings.entryList = &TTYD64_tik_08_EntryList;
    tik_08_settings.entryCount = 6;
    Mod_ReplaceScript("TTYD64", &tik_08_EVS_BindExitTriggers, &TTYD64_tik_08_Script_80241ABC);
}
