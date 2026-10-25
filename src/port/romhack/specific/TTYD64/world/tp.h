#pragma once

#include "common.h"
#include "map.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TTYD64_PitNpcsEntry {
    Bytecode first;
    Bytecode second;
} TTYD64_PitNpcsEntry;

void TTYD64_tp_BindMessage(Bytecode* script, const u8* msg);
s32 TTYD64_tp_PitTattle(s32* msgs);
void TTYD64_tp_InstallGenerated(void);
void TTYD64_tp_RegisterNpcsTable(TTYD64_PitNpcsEntry* table, s32 count);

API_CALLABLE(TTYD64_tp_AddBadge);
API_CALLABLE(TTYD64_tp_AddKeyItem);
API_CALLABLE(TTYD64_tp_GetDigit);
API_CALLABLE(TTYD64_tp_GetReminderFromDiv);
API_CALLABLE(TTYD64_tp_SwitchPartners);
API_CALLABLE(TTYD64_tp_GetFreeItemSlots);
API_CALLABLE(TTYD64_tp_ShowShopInventory);
API_CALLABLE(TTYD64_tp_GetVarFromVar);
API_CALLABLE(TTYD64_tp_SetVarFromVar);
API_CALLABLE(TTYD64_tp_TerritoryWrite);
API_CALLABLE(TTYD64_tp_PitNpcsRead);
API_CALLABLE(TTYD64_tp_PitGroupWrite);
API_CALLABLE(TTYD64_tp_TransformFoliage);
API_CALLABLE(TTYD64_tp_kzn_03_PiranhaPlantAI_Main);
API_CALLABLE(TTYD64_tp_flo_13_BlueSpinyAI_Main);
API_CALLABLE(TTYD64_tp_iwa_01_MontyMoleAI_Main);
API_CALLABLE(TTYD64_tp_SetNextFloorDigit);
API_CALLABLE(TTYD64_tp_GetShopBasePrice);
API_CALLABLE(TTYD64_tp_GetShopPrice);
API_CALLABLE(TTYD64_tp_SetShopPrice);

enum TTYD64PitFloorDigit {
    TTYD64_TP_FLOOR_TENS,
    TTYD64_TP_FLOOR_ONES,
};

#define TTYD64_TP_SHOP_ROWS 7

extern ShopItemData TTYD64_pit_11_Shop_Inventory[TTYD64_TP_SHOP_ROWS];
extern ShopItemData TTYD64_pit_11_Shop_Inventory_Updated[TTYD64_TP_SHOP_ROWS];

#ifdef __cplusplus
}
#endif
