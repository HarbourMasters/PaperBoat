#pragma once

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

enum TTYD64BattlesBFormationField {
    TTYD64_BATTLESB_FORMATION_PRIORITY = 0,
    TTYD64_BATTLESB_FORMATION_VAR0 = 1,
    TTYD64_BATTLESB_FORMATION_VAR1 = 2,
    TTYD64_BATTLESB_FORMATION_VAR2 = 3,
    TTYD64_BATTLESB_FORMATION_VAR3 = 4,
};

API_CALLABLE(TTYD64_BattlesB_SetFormationField);

void TTYD64_InstallBattles_flo(void);
void TTYD64_InstallBattles_flo2(void);
void TTYD64_InstallBattles_tik(void);
void TTYD64_InstallBattles_tik2(void);
void TTYD64_InstallBattles_tik3(void);
void TTYD64_InstallBattles_sam(void);
void TTYD64_InstallBattles_sam2(void);
void TTYD64_InstallBattles_pra(void);
void TTYD64_InstallBattles_pra2(void);
void TTYD64_InstallBattles_pra3(void);
void TTYD64_InstallBattles_kpa(void);
void TTYD64_InstallBattles_kpa2(void);
void TTYD64_InstallBattles_kpa3(void);
void TTYD64_InstallBattles_kpa4(void);
void TTYD64_InstallBattles_dig(void);
void TTYD64_InstallBattles_omo2_1(void);
void TTYD64_InstallBattles_omo2_2(void);
void TTYD64_InstallBattles_omo2_3(void);

#ifdef __cplusplus
}
#endif
