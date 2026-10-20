#pragma once

#include <stdint.h>

#include "api.h"

typedef struct C_MapDef_s {
    const char* id;        // map name, up to 7 characters like the game's, e.g. "mym_00". Its shape, hit and texture
                           // assets load under this name, so the mod archive ships them as the game's maps do
    void* settings;        // MapSettings: the main script, entry points, background and tattle
    const char* bg_name;   // background image, e.g. "kmr_bg", or NULL
    int32_t (*init)(void); // MapInit run before the assets load, NULL for none
    int8_t song_variation; // 0 or 1
    int8_t sfx_reverb;     // reverb of sound effects
} C_MapDef;

// Adds a map to an area, e.g. "kmr" or "area_kmr", from ModInit. Once added, GotoMap and the other EVT map functions
// reach it by its id. Returns 1 when added. A mod adding the same id again replaces its definition.
#define C_RegisterMap(area, def) C_RegisterMapSized((area), (def), sizeof(*(def)))
PB_API int C_RegisterMapSized(const char* area, const C_MapDef* def, uint32_t size);
// Removes a mod map. Saves made in it continue from the area's first map.
PB_API void C_UnregisterMap(const char* id);

typedef struct C_BattleDef_s {
    const char* id;              // stable unique key, e.g. "mymod.goomba_trio"
    int32_t formation_size;      // number of enemies in formation
    void* formation;             // Formation: each enemy's ActorBlueprint, position and priority
    void* stage;                 // Stage the battle takes place on
    const void* on_battle_start; // EvtScript run as the battle starts, replacing the stage's, or NULL
} C_BattleDef;

// Registers a battle from ModInit. Returns its battle ID, usable wherever the game takes one, such as the battle of an
// NPC_GROUP, or -1 when it can't.
#define C_RegisterBattle(def) C_RegisterBattleSized((def), sizeof(*(def)))
PB_API int32_t C_RegisterBattleSized(const C_BattleDef* def, uint32_t size);
// Unregisters a battle. Starting it afterwards gives a battle with no enemies.
PB_API void C_UnregisterBattle(int32_t battleID);
// Battle ID of the registered battle with this id, or -1.
PB_API int32_t C_FindBattle(const char* id);
