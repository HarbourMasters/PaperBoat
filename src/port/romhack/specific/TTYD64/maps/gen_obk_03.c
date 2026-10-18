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

extern ShopItemData obk_03_Inventory[];

extern ShopItemData TTYD64_obk_03_ShopInventory_8024154C[];

// clang-format off
ShopItemData TTYD64_obk_03_ShopInventory_8024154C[] = {
    { .itemID = 409, .price = 10, .descMsg = 0x23016B },
    { .itemID = 146, .price = 25, .descMsg = 0x240028 },
    { .itemID = 400, .price = 15, .descMsg = 0x230135 },
    { .itemID = 417, .price = 15, .descMsg = 0x230145 },
    { .itemID = 149, .price = 50, .descMsg = 0x24000C },
    { .itemID = 140, .price = 13, .descMsg = 0x24000A },
    { .itemID = 0, .price = 0, .descMsg = 0x000000 },
};
// clang-format on

void TTYD64_InstallMap_obk_03(void) {
    memcpy(&obk_03_Inventory, &TTYD64_obk_03_ShopInventory_8024154C, sizeof(TTYD64_obk_03_ShopInventory_8024154C));
}
