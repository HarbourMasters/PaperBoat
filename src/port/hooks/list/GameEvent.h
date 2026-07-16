#pragma once

#include "port/hooks/impl/EventSystem.h"

DEFINE_EVENT(OnSaveFileSave,
    void* saveData;
);

DEFINE_EVENT(OnSaveFileLoad,
    int32_t saveSlot;
    void* currentSaveFile;
);

DEFINE_EVENT(OnSaveFileErase,
    int32_t saveSlot;
);

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
