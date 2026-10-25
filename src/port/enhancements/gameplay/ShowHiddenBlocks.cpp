#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"
#include "port/ShipInit.hpp"

#define BLOCKSHIDDENDEFAULT        0
#define BLOCKSHIDDENCURRENTPARTNER 1
#define BLOCKSHIDDENHASWATT        2
#define BLOCKSHIDDENALWAYSSHOW     3
extern "C" {
#include "common_structs.h"
#include "enums.h"

extern PlayerData gPlayerData;
}

void RegisterHiddenBlock_Init() {
    REGISTER_LISTENER(OnHiddenBlockAlphaChange, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnHiddenBlockAlphaChange* ev = (OnHiddenBlockAlphaChange*) event;
        switch (Port_FeatureInt("enhancements.show_hidden_blocks", BLOCKSHIDDENDEFAULT)) {
            case BLOCKSHIDDENCURRENTPARTNER:
                if (gPlayerData.curPartner == PARTNER_WATT) {
                    *ev->alpha = 192;
                }
                break;
            case BLOCKSHIDDENHASWATT:
                if (gPlayerData.partners[PARTNER_WATT].enabled) {
                    *ev->alpha = 192;
                }
                break;
            case BLOCKSHIDDENALWAYSSHOW:
                *ev->alpha = 192;
                break;
        }
    });
}

static RegisterShipInitFunc initHiddenBlockFunc(RegisterHiddenBlock_Init);
