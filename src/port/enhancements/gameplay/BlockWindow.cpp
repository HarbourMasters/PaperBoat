#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"
#include "port/ShipInit.hpp"

#define BLOCK_WINDOW_ORIGINAL       0
#define BLOCK_WINDOW_FORGIVING      1
#define BLOCK_WINDOW_VERY_FORGIVING 2

#define BLOCK_WINDOW_FORGIVING_FRAMES      7
#define BLOCK_WINDOW_VERY_FORGIVING_FRAMES 10

void RegisterBlockWindow_Init() {
    REGISTER_LISTENER(OnBlockWindowCheck, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnBlockWindowCheck* ev = (OnBlockWindowCheck*) event;

        switch (CVarGetInteger(CVAR_ENHANCEMENT("BlockWindowMode"), BLOCK_WINDOW_ORIGINAL)) {
            case BLOCK_WINDOW_FORGIVING:
                *ev->blockWindow = BLOCK_WINDOW_FORGIVING_FRAMES;
                break;
            case BLOCK_WINDOW_VERY_FORGIVING:
                *ev->blockWindow = BLOCK_WINDOW_VERY_FORGIVING_FRAMES;
                break;
            default:
                break;
        }
    });
}

static RegisterShipInitFunc initBlockWindowFunc(RegisterBlockWindow_Init);
