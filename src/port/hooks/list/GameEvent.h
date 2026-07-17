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

DEFINE_EVENT(OnPlayerDamageReceived,
    int32_t* damage;
);

DEFINE_EVENT(OnPlayerFPChange,
    int32_t fpCost;
);

DEFINE_EVENT(OnPlayerSPChange,
    int32_t spCost;
);

DEFINE_EVENT(OnPlayerBPCostCheck,
    int32_t requiredBP;
    int32_t maxBP;
);
