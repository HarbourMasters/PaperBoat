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

extern ShopItemData sam_02_Inventory[];

extern ShopItemData TTYD64_sam_02_ShopInventory_8024B6CC[];

// clang-format off
ShopItemData TTYD64_sam_02_ShopInventory_8024B6CC[] = {
    { .itemID = 410, .price = 6, .descMsg = 0x23013E },
    { .itemID = 131, .price = 30, .descMsg = 0x240004 },
    { .itemID = 129, .price = 8, .descMsg = 0x240001 },
    { .itemID = 163, .price = 20, .descMsg = 0x240017 },
    { .itemID = 149, .price = 40, .descMsg = 0x24000C },
    { .itemID = 140, .price = 20, .descMsg = 0x24000A },
    { .itemID = 0, .price = 0, .descMsg = 0x000000 },
};
// clang-format on

void TTYD64_InstallMap_sam_02(void) {
    memcpy(&sam_02_Inventory, &TTYD64_sam_02_ShopInventory_8024B6CC, sizeof(TTYD64_sam_02_ShopInventory_8024B6CC));
}
