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

extern EvtScript mim_03_EVS_CheckFlowers_East;
extern EvtScript mim_03_EVS_ExitWalk_e;
extern EvtScript mim_03_EVS_FlowersReact_Correct;

API_CALLABLE(GotoMap);
API_CALLABLE(PlaySoundAt);
API_CALLABLE(UseExitHeading);

extern EvtScript TTYD64_mim_03_Script_ExitWalk_80240704;
extern EvtScript TTYD64_mim_03_Script_80241020;
extern s32 TTYD64_mim_03_Data_Bush3_FlowerIDs[];

// clang-format off
EvtScript TTYD64_mim_03_Script_ExitWalk_80240704 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 3)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "mim_13", 3)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_mim_03_Script_80241020 = {
    Call(PlaySoundAt, 8282, 0, 300, 0, 0)
    Set(LVar8, (Bytecode) TTYD64_mim_03_Data_Bush3_FlowerIDs)
    Set(LVar9, 3)
    ExecWait(mim_03_EVS_FlowersReact_Correct)
    Return
    End
};

s32 TTYD64_mim_03_Data_Bush3_FlowerIDs[] = {
    69, 70, 72, 73, 72, 73,
    75, 76
};
// clang-format on

void TTYD64_InstallMap_mim_03(void) {
    Mod_ReplaceScript("TTYD64", &mim_03_EVS_ExitWalk_e, &TTYD64_mim_03_Script_ExitWalk_80240704);
    Mod_ReplaceScript("TTYD64", &mim_03_EVS_CheckFlowers_East, &TTYD64_mim_03_Script_80241020);
}
