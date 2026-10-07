#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"
#include "port/ShipInit.hpp"

extern "C" {
#include "dx/versioning.h"

extern s32 set_global_flag(s32 index);
extern SaveData gCurrentSaveFile;
}

void RegisterCutsceneSkips_Init() {
    REGISTER_LISTENER(OnPostSaveFileLoad, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnPostSaveFileLoad* ev = (OnPostSaveFileLoad*) event;

        if (!CVarGetInteger(CVAR_ENHANCEMENT("NoIntro"), 0)) {
            return;
        }

        if (gCurrentSaveFile.player.battlesCount > 0) {
            return;
        }

        gCurrentSaveFile.player.battlesCount = 1;
        gCurrentSaveFile.mapID = 1;
        gCurrentSaveFile.entryID = 5;

        // Only the flags the skipped intro sets; neighboring flags share these words
        set_global_flag(GF_Tutorial_SaveBlock);
        set_global_flag(GF_MAP_GoombaVillage);

        gCurrentSaveFile.globalBytes[0] = STORY_CH0_MET_INNKEEPER;

        gCurrentSaveFile.savePos.x = 250;
        gCurrentSaveFile.savePos.y = 0;
        gCurrentSaveFile.savePos.z = 85;
    });
}

static RegisterShipInitFunc initFunc(RegisterCutsceneSkips_Init);
