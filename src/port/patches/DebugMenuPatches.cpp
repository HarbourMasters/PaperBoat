#include "port/Engine.h"

#include <cstring>

#include "common.h"
#include "port/patches/Patches.h"

struct DebugMenuFeature {
    const char* text;
    const char* feature;
};

static const DebugMenuFeature sDebugMenuFeatures[] = {
    { "Full Restore", "devtools.debug_menu.full_restore" }, { "Save/Load", "devtools.debug_menu.save_load" },
    { "Map Select", "devtools.debug_menu.map_select" },     { "Battle Select", "devtools.debug_menu.battle_select" },
    { "Set Story Byte", "devtools.debug_menu.story_byte" }, { "Sound Player", "devtools.debug_menu.sound_player" },
    { "Edit Partners", "devtools.debug_menu.partners" },    { "Edit Inventory", "devtools.debug_menu.inventory" },
    { "View Collision", "devtools.debug_menu.collision" },  { "Cheats", "devtools.debug_menu.cheats" },
};

extern "C" b32 port_debug_menu_entry_allowed(const char* text) {
    for (const DebugMenuFeature& entry : sDebugMenuFeatures) {
        if (strcmp(entry.text, text) == 0) {
            return Port_FeatureAllowed(entry.feature);
        }
    }
    return true;
}
