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

extern ShopItemData kpa_96_Inventory[];

extern ShopItemData TTYD64_kpa_96_ShopInventory_8024034C[];

// clang-format off
ShopItemData TTYD64_kpa_96_ShopInventory_8024034C[] = {
    { .itemID = 150, .price = 5, .descMsg = 0x24002B },
    { .itemID = 154, .price = 25, .descMsg = 0x240029 },
    { .itemID = 418, .price = 15, .descMsg = 0x230146 },
    { .itemID = 130, .price = 30, .descMsg = 0x240002 },
    { .itemID = 163, .price = 30, .descMsg = 0x240017 },
    { .itemID = 140, .price = 30, .descMsg = 0x24000A },
    { .itemID = 0, .price = 0, .descMsg = 0x000000 },
};
// clang-format on

void TTYD64_InstallMap_kpa_96(void) {
    memcpy(&kpa_96_Inventory, &TTYD64_kpa_96_ShopInventory_8024034C, sizeof(TTYD64_kpa_96_ShopInventory_8024034C));
}
