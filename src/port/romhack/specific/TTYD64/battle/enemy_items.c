#include "common.h"
#include "battle/battle.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/battle/enemy_items_internal.h"

extern EvtScript EVS_Enemy_Death;
extern EvtScript EVS_ForceNextTarget;

void TTYD64_InstallEnemyItems(void) {
    Mod_ReplaceScript("TTYD64", &EVS_Enemy_Death, &TTYD64_EVS_Enemy_Death_Patch);
    Mod_ReplaceScript("TTYD64", &EVS_ForceNextTarget, &TTYD64_EVS_ForceNextTarget_Patch);
    TTYD64_EI_InstallListeners();
    TTYD64_EI_InstallGlitzPit();
}
