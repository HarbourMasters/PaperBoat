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
// NPC_GROUP, or -1 when it can't. Registering the same id again replaces it and keeps its battle ID.
#define C_RegisterBattle(def) C_RegisterBattleSized((def), sizeof(*(def)))
PB_API int32_t C_RegisterBattleSized(const C_BattleDef* def, uint32_t size);
// Unregisters a battle. Starting it afterwards gives a battle with no enemies.
PB_API void C_UnregisterBattle(int32_t battleID);
// Battle ID of the registered battle with this id, or -1.
PB_API int32_t C_FindBattle(const char* id);
// The stage the game's battles in a map take place on, by the map's name, e.g. "kmr_02", or NULL when it has none.
PB_API void* C_FindBattleStage(const char* map);

// How a battle started with C_StartBattle begins, as when the player runs into an enemy.
typedef enum {
    C_BATTLE_START_NORMAL, // no one strikes first
    C_BATTLE_START_JUMP,   // the player jumped on the enemy and strikes first, harder with a spin or tornado jump
    C_BATTLE_START_HAMMER, // the player hammered the enemy and strikes first
    C_BATTLE_START_STRUCK, // the enemy strikes first
} C_BattleStart;

// Starts a battle from the world, as touching an enemy would, while the player is free to move: not in a scene, a
// menu or another battle. songID is the battle music, -1 for the usual one. With canFlee 0, Run Away is taken off the menu. start is
// a C_BATTLE_START_*. No enemy is left defeated on the map, fleeing drops no coins, and badges that win battles on
// contact don't. Losing ends the game unless the battle's start script sets BS_FLAGS1_NO_GAME_OVER. Returns 1 when
// the battle starts.
PB_API int C_StartBattle(int32_t battleID, int32_t songID, int canFlee, int32_t start);

// An actor part's animation from the player's sprites, e.g. C_PLAYER_ANIM(ANIM_MarioB1_Jump), for an enemy that moves
// as the player does. Use it for the part's idle animations and with SetAnimation. A part only becomes one when it is
// created with such an animation, and at most 8 can be at once.
#define C_PLAYER_ANIM(anim) ((anim) | 0x40000000)
// Draws a part created with a C_PLAYER_ANIM animation with the player's reds in color, 0xRRGGBBAA; 0 for the player's
// own colors. In battle only.
PB_API void C_SetActorPartColor(int32_t actorID, int32_t partID, uint32_t color);

