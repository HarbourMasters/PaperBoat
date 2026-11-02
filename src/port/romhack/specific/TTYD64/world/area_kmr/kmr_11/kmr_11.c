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

extern FoliageDropList kmr_11_Tree2_Drops;

// clang-format off

// clang-format on

void TTYD64_InstallMap_kmr_11(void) {
    kmr_11_Tree2_Drops.count = 1;
    kmr_11_Tree2_Drops.drops[0].itemID = 414;
    kmr_11_Tree2_Drops.drops[0].pos.x = 307;
    kmr_11_Tree2_Drops.drops[0].pos.y = 115;
    kmr_11_Tree2_Drops.drops[0].pos.z = -462;
    kmr_11_Tree2_Drops.drops[0].spawnMode = 15;
    kmr_11_Tree2_Drops.drops[0].pickupFlag = 0;
    kmr_11_Tree2_Drops.drops[0].spawnFlag = AreaFlag(11);
}
