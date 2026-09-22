#pragma once

#include "port/hooks/impl/EventSystem.h"

// SaveManager
DEFINE_EVENT(OnSaveFileSave,
    void* saveData;
);

DEFINE_EVENT(OnSaveFileLoad,
    int32_t saveSlot;
);

DEFINE_EVENT(OnSaveFileErase,
    int32_t saveSlot;
);

// Cheats
DEFINE_EVENT(OnPlayerDamageReceived,
    int32_t* damage;
);

DEFINE_EVENT(OnPlayerFPChange,
    int32_t fpCost;
);

DEFINE_EVENT(OnPlayerSPChange,
    int32_t spCost;
);

DEFINE_EVENT(OnPlayerBPCostCheck);

// Gameplay > CutsceneSkips
DEFINE_EVENT(OnPostSaveFileLoad);

// Battle
DEFINE_EVENT(OnBattleEffectsRemoved);

DEFINE_EVENT(OnBlockWindowCheck,
    int32_t* blockWindow;
    int32_t* mashWindow;
);

// World
DEFINE_EVENT(OnMapLoad,
    const char* mapName;
);
