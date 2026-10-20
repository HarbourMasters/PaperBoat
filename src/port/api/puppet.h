#pragma once

#include <stdint.h>

#include "api.h"

// Puppets are figures a mod moves, such as other players in an online game. A puppet shows in whatever map its pose
// names, while that map is the one being played, and follows the last pose set on it. It is drawn with the player's
// own sprites, with the cap and shirt in the pose's color, and plays the animation its pose names, so it swings the
// hammer, lifts items and fights the way the other player does.

#define C_PUPPET_MAX 16

// Luigi's green, for poses without a color of their own.
#define C_PUPPET_DEFAULT_COLOR 0x30B030FF

// What the figure is doing. A puppet plays the pose's anim, and the animation for its motion when anim is 0 or not
// one it can show.
typedef enum {
    C_PUPPET_IDLE,
    C_PUPPET_WALK,
    C_PUPPET_RUN,
    C_PUPPET_JUMP,
    C_PUPPET_FALL,
    C_PUPPET_LAND,
    C_PUPPET_BATTLE, // in a battle, where it started; anim is the player's battle animation
} C_PuppetMotion;

typedef struct {
    float x; // position in the map
    float y;
    float z;
    float yaw;      // direction faced, in degrees
    int32_t motion; // C_PUPPET_*
    int32_t anim;   // the player's animation, an ANIM_Mario* or ANIM_Peach* value, which a puppet plays
    char map[8];    // map the player is in, e.g. "kmr_20"
    uint32_t frame; // game frame the pose was taken on, set by C_GetPlayerPose; 0 to use when it arrives
    uint32_t color; // cap and shirt color, 0xRRGGBBAA, which the mod sets; 0 for C_PUPPET_DEFAULT_COLOR
} C_PlayerPose;

// Writes the pose of the player being played, with color 0 for the mod to fill in. In a battle, the pose is where it started, with the battle animation.
// Returns 0 elsewhere, such as on the title screen or in a menu.
#define C_GetPlayerPose(pose) C_GetPlayerPoseSized((pose), sizeof(*(pose)))
PB_API int C_GetPlayerPoseSized(C_PlayerPose* pose, uint32_t size);

// Makes a puppet and returns it, or -1 when C_PUPPET_MAX are in use. It shows once it has a pose.
PB_API int C_SpawnPuppet(void);
// Gives the puppet its next pose. Puppets play their poses back a few frames behind the newest, moving smoothly between
// them on the frames they were taken on, so poses that arrive unevenly still play evenly. Poses further apart than a
// short run are jumped between. A pose in another map hides the puppet.
#define C_SetPuppetPose(puppet, pose) C_SetPuppetPoseSized((puppet), (pose), sizeof(*(pose)))
PB_API void C_SetPuppetPoseSized(int puppet, const C_PlayerPose* pose, uint32_t size);
// Removes the puppet. A mod's puppets are removed when it unloads.
PB_API void C_RemovePuppet(int puppet);
// The Npc that holds the puppet's place and shadow, or NULL while it isn't in the map being played. The figure
// itself is drawn apart from it, so the Npc's sprite and animation do nothing.
PB_API void* C_GetPuppetNpc(int puppet);

// Lets the player run into the puppet in the field as into an enemy: touching it, jumping on it or hammering it fires
// OnPuppetEncounter with how, a C_BATTLE_START_* from world.h, for the mod to start a battle with C_StartBattle. It
// fires again only after the player has stepped away, and not for a second after a battle or menu. Off by default.
PB_API void C_SetPuppetEncounter(int puppet, int enabled);
