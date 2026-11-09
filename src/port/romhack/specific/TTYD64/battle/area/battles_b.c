#include "common.h"
#include "battle/battle.h"
#include "port/romhack/specific/TTYD64/TTYD64.h"
#include "port/romhack/specific/TTYD64/battle/area/battles_b.h"

API_CALLABLE(TTYD64_BattlesB_SetFormationField) {
    Bytecode* args = script->ptrReadPos;
    FormationRow* row = (FormationRow*) evt_get_variable(script, *args++);
    s32 field = evt_get_variable(script, *args++);
    s32 value = evt_get_variable(script, *args++);

    switch (field) {
        case TTYD64_BATTLESB_FORMATION_PRIORITY:
            row->priority = value;
            break;
        case TTYD64_BATTLESB_FORMATION_VAR0:
            row->var0 = value;
            break;
        case TTYD64_BATTLESB_FORMATION_VAR1:
            row->var1 = value;
            break;
        case TTYD64_BATTLESB_FORMATION_VAR2:
            row->var2 = value;
            break;
        case TTYD64_BATTLESB_FORMATION_VAR3:
            row->var3 = value;
            break;
    }
    return ApiStatus_DONE2;
}

void TTYD64_InstallBattlesB(void) {
    TTYD64_InstallBattles_flo();
    TTYD64_InstallBattles_flo2();
    TTYD64_InstallBattles_tik();
    TTYD64_InstallBattles_tik2();
    TTYD64_InstallBattles_tik3();
    TTYD64_InstallBattles_sam();
    TTYD64_InstallBattles_sam2();
    TTYD64_InstallBattles_pra();
    TTYD64_InstallBattles_pra2();
    TTYD64_InstallBattles_pra3();
    TTYD64_InstallBattles_kpa();
    TTYD64_InstallBattles_kpa2();
    TTYD64_InstallBattles_kpa3();
    TTYD64_InstallBattles_kpa4();
    TTYD64_InstallBattles_dig();
    TTYD64_InstallBattles_omo2_1();
    TTYD64_InstallBattles_omo2_2();
    TTYD64_InstallBattles_omo2_3();
}
