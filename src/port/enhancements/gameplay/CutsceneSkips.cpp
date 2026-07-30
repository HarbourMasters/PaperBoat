#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"
#include "port/ShipInit.hpp"

extern "C" {
#include "dx/versioning.h"

    extern SaveData gCurrentSaveFile;
}

void RegisterCutsceneSkips_Init() {
	REGISTER_LISTENER(OnPostSaveFileLoad, EVENT_PRIORITY_NORMAL, [](IEvent *event) {
        OnPostSaveFileLoad* ev = (OnPostSaveFileLoad*)event;

        if (!CVarGetInteger(CVAR_ENHANCEMENT("NoIntro"), 0)) {
            return;
        }

        if (gCurrentSaveFile.player.battlesCount > 0) {
            return;
        }

        gCurrentSaveFile.player.battlesCount = 1;
        gCurrentSaveFile.mapID = 1;
        gCurrentSaveFile.entryID = 5;

        gCurrentSaveFile.globalFlags[2] = -2147483648;
        gCurrentSaveFile.globalFlags[4] = -480;
        gCurrentSaveFile.globalFlags[8] = 128;
        gCurrentSaveFile.globalFlags[61] = 16384;

        gCurrentSaveFile.globalBytes[0] = -126;

        gCurrentSaveFile.savePos.x = 250;
        gCurrentSaveFile.savePos.y = 0;
        gCurrentSaveFile.savePos.z = 85;
	});
}

static RegisterShipInitFunc initFunc(RegisterCutsceneSkips_Init);
