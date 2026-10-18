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

extern ShopItemData dro_01_Shop_Inventory[];

extern ShopItemData TTYD64_dro_01_ShopInventory_8024B4FC[];

// clang-format off
ShopItemData TTYD64_dro_01_ShopInventory_8024B4FC[] = {
    { .itemID = 132, .price = 5, .descMsg = 0x240003 },
    { .itemID = 134, .price = 2, .descMsg = 0x240005 },
    { .itemID = 167, .price = 3, .descMsg = 0x24001D },
    { .itemID = 141, .price = 2, .descMsg = 0x24000D },
    { .itemID = 402, .price = 110, .descMsg = 0x230137 },
    { .itemID = 403, .price = 350, .descMsg = 0x230138 },
    { .itemID = 0, .price = 0, .descMsg = 0x000000 },
};
// clang-format on

void TTYD64_InstallMap_dro_01(void) {
    memcpy(&dro_01_Shop_Inventory, &TTYD64_dro_01_ShopInventory_8024B4FC, sizeof(TTYD64_dro_01_ShopInventory_8024B4FC));
}
