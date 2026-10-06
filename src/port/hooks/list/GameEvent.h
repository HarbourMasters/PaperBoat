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

DEFINE_EVENT(OnSaveGlobalsSave,
    void* saveGlobals;
);

DEFINE_EVENT(OnSaveGlobalsLoad,
    void* saveGlobals;
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

DEFINE_EVENT(OnActionCommandDifficulty,
    int32_t* difficultyLevel;
);

DEFINE_EVENT(OnPowerBounceChance,
    int32_t* hitChance;
    int32_t targetChance;
);

DEFINE_EVENT(OnStarPointDrop,
    int32_t* count;
);

DEFINE_EVENT(OnCoinDrop,
    int32_t* count;
);

// Battle > Actors
DEFINE_EVENT(OnActorBlueprintLoad,
    struct ActorBlueprint** blueprint;
);

DEFINE_EVENT(OnActorCreated,
    Actor* actor;
);

DEFINE_EVENT(OnEnemyAttackDamage,
    Actor* attacker;
    int32_t* damage;
);

DEFINE_EVENT(OnPartnerAttackDamage,
    Actor* partner;
    Actor* target;
    int32_t* damage;
);

// World
DEFINE_EVENT(OnMapLoad,
    const char* mapName;
);

DEFINE_EVENT(OnPlayerSpeedUpdate,
    float* walkSpeed;
    float* runSpeed;
);

DEFINE_EVENT(OnMapReady,
    const char* mapName;
);
