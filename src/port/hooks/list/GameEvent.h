#pragma once

#include "port/hooks/impl/EventSystem.h"

DEFINE_EVENT(PlayerDamage,
    int32_t* damage;
);

DEFINE_EVENT(PlayerFPDeduct,
    int32_t fpCost;
);

DEFINE_EVENT(StarPowerDeduct,
    int32_t spCost;
);

DEFINE_EVENT(BadgeBPCostCheck,
    int32_t requiredBP;
    int32_t maxBP;
);
