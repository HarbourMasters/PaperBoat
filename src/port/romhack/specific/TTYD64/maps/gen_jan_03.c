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

extern ShopItemData jan_03_Inventory[];
extern FoliageDropList jan_03_Tree1_Drops;

extern ShopItemData TTYD64_jan_03_ShopInventory_802449BC[];

// clang-format off
ShopItemData TTYD64_jan_03_ShopInventory_802449BC[] = {
    { .itemID = 415, .price = 5, .descMsg = 0x230143 },
    { .itemID = 130, .price = 15, .descMsg = 0x240002 },
    { .itemID = 128, .price = 5, .descMsg = 0x240000 },
    { .itemID = 137, .price = 2, .descMsg = 0x24000E },
    { .itemID = 164, .price = 6, .descMsg = 0x240016 },
    { .itemID = 140, .price = 15, .descMsg = 0x24000A },
    { .itemID = 0, .price = 0, .descMsg = 0x000000 },
};
// clang-format on

void TTYD64_InstallMap_jan_03(void) {
    jan_03_Tree1_Drops.count = 1;
    jan_03_Tree1_Drops.drops[0].itemID = 411;
    jan_03_Tree1_Drops.drops[0].pos.x = 586;
    jan_03_Tree1_Drops.drops[0].pos.y = 75;
    jan_03_Tree1_Drops.drops[0].pos.z = -115;
    jan_03_Tree1_Drops.drops[0].spawnMode = 15;
    jan_03_Tree1_Drops.drops[0].pickupFlag = 0;
    jan_03_Tree1_Drops.drops[0].spawnFlag = AreaFlag(23);
    memcpy(&jan_03_Inventory, &TTYD64_jan_03_ShopInventory_802449BC, sizeof(TTYD64_jan_03_ShopInventory_802449BC));
}
