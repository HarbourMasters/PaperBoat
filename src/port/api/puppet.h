#pragma once

#include <stdint.h>

#include "api.h"

// Puppets are figures a mod moves, such as other players in an online game. A puppet shows as Luigi in whatever map
// its pose names, while that map is the one being played, and follows the last pose set on it.

#define C_PUPPET_MAX 16

// What the figure is doing, which picks its animation.
typedef enum {
    C_PUPPET_IDLE,
    C_PUPPET_WALK,
    C_PUPPET_RUN,
    C_PUPPET_JUMP,
    C_PUPPET_FALL,
    C_PUPPET_LAND,
} C_PuppetMotion;

typedef struct {
    float x; // position in the map
    float y;
    float z;
    float yaw;      // direction faced, in degrees
    int32_t motion; // C_PUPPET_*
    int32_t anim;   // the player's own animation, an ANIM_Mario* value, for mods that show it their own way
    char map[8];    // map the player is in, e.g. "kmr_20"
} C_PlayerPose;

// Writes the pose of the player being played. Returns 0 outside of a map.
#define C_GetPlayerPose(pose) C_GetPlayerPoseSized((pose), sizeof(*(pose)))
PB_API int C_GetPlayerPoseSized(C_PlayerPose* pose, uint32_t size);

// Makes a puppet and returns it, or -1 when C_PUPPET_MAX are in use. It shows once it has a pose.
PB_API int C_SpawnPuppet(void);
// Moves the puppet towards the pose, easing when it is close. A pose in another map hides the puppet.
#define C_SetPuppetPose(puppet, pose) C_SetPuppetPoseSized((puppet), (pose), sizeof(*(pose)))
PB_API void C_SetPuppetPoseSized(int puppet, const C_PlayerPose* pose, uint32_t size);
// Removes the puppet. A mod's puppets are removed when it unloads.
PB_API void C_RemovePuppet(int puppet);
// The puppet's Npc, or NULL while it isn't in the map being played.
PB_API void* C_GetPuppetNpc(int puppet);
