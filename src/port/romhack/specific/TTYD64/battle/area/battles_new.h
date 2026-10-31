#pragma once

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

API_CALLABLE(TTYD64_BattlesNew_AddBadge);
API_CALLABLE(TTYD64_BattlesNew_ReadN64PlayerBadge);
API_CALLABLE(TTYD64_imp_BadgeBandit_Function_UpdateBadgePos);
API_CALLABLE(TTYD64_imp_BadgeBandit_Function_RemoveAndUnequipBadge);
API_CALLABLE(TTYD64_imp_BadgeBandit_Function_ActivateBadge);
API_CALLABLE(TTYD64_imp_BigBandit_Function_UpdateItemPos);
API_CALLABLE(TTYD64_imp_BigBandit_Function_GetItemByIndex);
API_CALLABLE(TTYD64_imp_BigBandit_Function_GetAmountOfItems);
API_CALLABLE(TTYD64_imp_BigBandit_Function_GetFreeItemSlots);
API_CALLABLE(TTYD64_imp_FlowerFuzzy_Function_UpdateBGColor_Darker);

void TTYD64_InstallBattles_pit_part_1(void);
void TTYD64_InstallBattles_pit_part_2(void);
void TTYD64_InstallBattles_pit_part_3(void);
void TTYD64_InstallBattles_pit_part_4(void);
void TTYD64_InstallBattles_pit_part_5(void);
void TTYD64_InstallBattles_pit_part_6(void);
void TTYD64_InstallBattles_pit_part_7(void);
void TTYD64_InstallBattles_pit_part_8(void);
void TTYD64_InstallBattles_pit_part_9(void);
void TTYD64_InstallBattles_pit_part_10(void);
void TTYD64_InstallBattles_pit_part_11(void);
void TTYD64_InstallBattles_tyd_part_1(void);
void TTYD64_InstallBattles_tyd_part_2(void);
void TTYD64_InstallBattles_tyd_part_3(void);

#ifdef __cplusplus
}
#endif
