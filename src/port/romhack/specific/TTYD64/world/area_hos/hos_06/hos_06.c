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
#include "port/romhack/specific/TTYD64/world/maps.h"

extern ShopItemData hos_06_MerlowBadgeInventory[];

extern ShopItemData TTYD64_hos_06_MerlowBadgeInventory[];

// clang-format off
ShopItemData TTYD64_hos_06_MerlowBadgeInventory[] = {
    { .itemID = 243, .price = 1, .descMsg = 0x24008D },
    { .itemID = 252, .price = 1, .descMsg = 0x240096 },
    { .itemID = 324, .price = 2, .descMsg = 0x24009F },
    { .itemID = 254, .price = 4, .descMsg = 0x240098 },
    { .itemID = 241, .price = 5, .descMsg = 0x240081 },
    { .itemID = 242, .price = 5, .descMsg = 0x24008C },
    { .itemID = 255, .price = 8, .descMsg = 0x240079 },
    { .itemID = 320, .price = 8, .descMsg = 0x24007A },
    { .itemID = 383, .price = 5, .descMsg = 0x230123 },
    { .itemID = 282, .price = 10, .descMsg = 0x24007C },
    { .itemID = 283, .price = 12, .descMsg = 0x24007D },
    { .itemID = 245, .price = 12, .descMsg = 0x240078 },
    { .itemID = 394, .price = 20, .descMsg = 0x23012E },
    { .itemID = 261, .price = 20, .descMsg = 0x24007B },
    { .itemID = 226, .price = 20, .descMsg = 0x240073 },
};
// clang-format on

void TTYD64_InstallMap_hos_06(void) {
    memcpy(
        &hos_06_MerlowBadgeInventory, &TTYD64_hos_06_MerlowBadgeInventory, sizeof(TTYD64_hos_06_MerlowBadgeInventory)
    );
}
