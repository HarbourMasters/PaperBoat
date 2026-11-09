#include "common.h"
#include "port/hooks/Events.h"
#include "script_api/macros.h"
#include "port/romhack/specific/TTYD64/TTYD64.h"
#include "port/romhack/specific/TTYD64/world/tyd_pit.h"

static s32 tp_default_floor(const char* mapName) {
    s32 map;

    if (mapName == nullptr || strncmp(mapName, "pit_", 4) != 0) {
        return 0;
    }
    map = atoi(mapName + 4);
    if (map >= 1 && map <= 10) {
        return (map - 1) * 10 + 1;
    }
    if (map == 11) {
        return 10;
    }
    if (map == 12) {
        return 100;
    }
    return 0;
}

static void tp_on_map_load(IEvent* event) {
    OnMapLoad* ev = (OnMapLoad*) event;
    s32 floor;

    if (evt_get_variable(NULL, AreaByte(0)) != 0) {
        return;
    }
    floor = tp_default_floor(ev->mapName);
    if (floor != 0) {
        evt_set_variable(NULL, AreaByte(0), floor);
    }
}

void TTYD64_InstallNewMapsTydPit(void) {
    TTYD64_tp_InstallGenerated();
    REGISTER_LISTENER(OnMapLoad, EVENT_PRIORITY_NORMAL, tp_on_map_load);
}
