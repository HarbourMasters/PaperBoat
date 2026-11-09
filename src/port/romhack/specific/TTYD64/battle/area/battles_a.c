#include "common.h"
#include "battle/battle.h"
#include "port/romhack/specific/TTYD64/TTYD64.h"
#include "port/romhack/specific/TTYD64/battle/area/battles_a.h"

API_CALLABLE(TTYD64_BattlesA_WriteFormationActor) {
    Bytecode* args = script->ptrReadPos;
    FormationRow* row = (FormationRow*) evt_get_variable(script, *args++);
    ActorBlueprint* actor = (ActorBlueprint*) evt_get_variable(script, *args++);

    row->actor = actor;
    return ApiStatus_DONE2;
}

void TTYD64_InstallBattlesA(void) {
    TTYD64_InstallBattles_kmr_part_1();
    TTYD64_InstallBattles_kmr_part_2();
    TTYD64_InstallBattles_kmr_part_3();
    TTYD64_InstallBattles_mac();
    TTYD64_InstallBattles_hos();
    TTYD64_InstallBattles_nok();
    TTYD64_InstallBattles_trd_part_1();
    TTYD64_InstallBattles_trd_part_2();
    TTYD64_InstallBattles_trd_part_3();
    TTYD64_InstallBattles_iwa();
    TTYD64_InstallBattles_sbk();
    TTYD64_InstallBattles_isk_part_1();
    TTYD64_InstallBattles_isk_part_2();
    TTYD64_InstallBattles_mim();
    TTYD64_InstallBattles_arn();
    TTYD64_InstallBattles_dgb();
    TTYD64_InstallBattles_omo();
    TTYD64_InstallBattles_omo2();
    TTYD64_InstallBattles_omo3();
    TTYD64_InstallBattles_kgr();
    TTYD64_InstallBattles_jan();
    TTYD64_InstallBattles_jan2();
    TTYD64_InstallBattles_kzn();
    TTYD64_InstallBattles_kzn2();
}
