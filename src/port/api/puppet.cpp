#ifdef ENABLE_SCRIPTING

#include "port/api/puppet.h"

#include "port/ShipInit.hpp"
#include "port/api/ModOwner.hpp"
#include "port/api/SizedDef.hpp"
#include "port/hooks/Events.h"

#include "common.h"
#include "game_modes.h"
#include "npc.h"
#include "sprite/npc/Luigi.h"

#include <array>
#include <cmath>
#include <cstring>
#include <string>

namespace {

// NPC ids past the ones maps give their own NPCs.
constexpr s32 kFirstNpcID = 100;
// Further than this, a puppet jumps to its pose instead of easing there.
constexpr float kSnapDistance = 200.0f;

struct Puppet {
    bool used = false;
    bool hasPose = false;
    std::string owner;
    C_PlayerPose pose {};
    s32 npcIndex = -1;
};

std::array<Puppet, C_PUPPET_MAX> sPuppets;

const char* CurrentMap() {
    const AreaConfig& area = gAreas[gGameStatusPtr->areaID];
    return gGameStatusPtr->mapID < area.mapCount ? area.maps[gGameStatusPtr->mapID].id : "";
}

AnimID MotionAnim(int32_t motion) {
    switch (motion) {
        case C_PUPPET_WALK:
            return ANIM_Luigi_Walk;
        case C_PUPPET_RUN:
            return ANIM_Luigi_Run;
        case C_PUPPET_JUMP:
            return ANIM_Luigi_Jump;
        case C_PUPPET_FALL:
            return ANIM_Luigi_Fall;
        case C_PUPPET_LAND:
            return ANIM_Luigi_Land;
        default:
            return ANIM_Luigi_Idle;
    }
}

void FreeNpc(Puppet& puppet) {
    if (puppet.npcIndex >= 0) {
        if (Npc* npc = get_npc_by_index(puppet.npcIndex)) {
            free_npc(npc);
        }
        puppet.npcIndex = -1;
    }
}

Npc* SpawnNpc(Puppet& puppet, int slot) {
    NpcBlueprint blueprint = {};
    blueprint.flags = NPC_FLAG_IGNORE_PLAYER_COLLISION | NPC_FLAG_IGNORE_WORLD_COLLISION;
    blueprint.initialAnim = ANIM_Luigi_Idle;
    puppet.npcIndex = create_basic_npc(&blueprint);
    Npc* npc = get_npc_by_index(puppet.npcIndex);
    if (npc == nullptr) {
        puppet.npcIndex = -1;
        return nullptr;
    }
    npc->npcID = kFirstNpcID + slot;
    npc->pos.x = puppet.pose.x;
    npc->pos.y = puppet.pose.y;
    npc->pos.z = puppet.pose.z;
    enable_npc_shadow(npc);
    return npc;
}

// Once per frame on the game thread: puppets in the map being played follow their poses, the others are hidden.
void Update() {
    if (get_game_mode() != GAME_MODE_WORLD) {
        return;
    }
    const char* map = CurrentMap();
    for (int slot = 0; slot < C_PUPPET_MAX; slot++) {
        Puppet& puppet = sPuppets[slot];
        if (!puppet.used || !puppet.hasPose || strncmp(puppet.pose.map, map, sizeof(puppet.pose.map)) != 0) {
            FreeNpc(puppet);
            continue;
        }
        Npc* npc = puppet.npcIndex >= 0 ? get_npc_by_index(puppet.npcIndex) : SpawnNpc(puppet, slot);
        if (npc == nullptr) {
            continue;
        }
        const float dx = puppet.pose.x - npc->pos.x;
        const float dy = puppet.pose.y - npc->pos.y;
        const float dz = puppet.pose.z - npc->pos.z;
        const float ease = std::sqrt(dx * dx + dy * dy + dz * dz) > kSnapDistance ? 1.0f : 0.5f;
        npc->pos.x += dx * ease;
        npc->pos.y += dy * ease;
        npc->pos.z += dz * ease;
        npc->yaw = puppet.pose.yaw;
        const AnimID anim = MotionAnim(puppet.pose.motion);
        if (npc->curAnim != anim) {
            npc->curAnim = anim;
        }
    }
}

void InitPuppetApi() {
    REGISTER_LISTENER(GameFrameUpdate, EVENT_PRIORITY_NORMAL, [](IEvent*) { Update(); });
    // Loading a map frees every NPC, the puppets' too.
    REGISTER_LISTENER(OnMapLoad, EVENT_PRIORITY_NORMAL, [](IEvent*) {
        for (Puppet& puppet : sPuppets) {
            puppet.npcIndex = -1;
        }
    });
    ModOwner::AddReleaser([](const std::string& mod) {
        for (int slot = 0; slot < C_PUPPET_MAX; slot++) {
            if (sPuppets[slot].used && sPuppets[slot].owner == mod) {
                C_RemovePuppet(slot);
            }
        }
    });
}

RegisterShipInitFunc sInitPuppetApi(InitPuppetApi);

Puppet* Find(int puppet) {
    return puppet >= 0 && puppet < C_PUPPET_MAX && sPuppets[puppet].used ? &sPuppets[puppet] : nullptr;
}

} // namespace

extern "C" int C_GetPlayerPoseSized(C_PlayerPose* out, uint32_t size) {
    if (out == nullptr || get_game_mode() != GAME_MODE_WORLD) {
        return 0;
    }
    const PlayerStatus& player = gPlayerStatus;
    C_PlayerPose pose = {};
    pose.x = player.pos.x;
    pose.y = player.pos.y;
    pose.z = player.pos.z;
    pose.yaw = player.targetYaw;
    pose.anim = player.anim;
    switch (player.actionState) {
        case ACTION_STATE_WALK:
            pose.motion = C_PUPPET_WALK;
            break;
        case ACTION_STATE_RUN:
            pose.motion = C_PUPPET_RUN;
            break;
        case ACTION_STATE_JUMP:
        case ACTION_STATE_HOP:
            pose.motion = C_PUPPET_JUMP;
            break;
        case ACTION_STATE_FALLING:
            pose.motion = C_PUPPET_FALL;
            break;
        case ACTION_STATE_LAND:
            pose.motion = C_PUPPET_LAND;
            break;
        default:
            pose.motion = C_PUPPET_IDLE;
            break;
    }
    strncpy(pose.map, CurrentMap(), sizeof(pose.map) - 1);
    memcpy(out, &pose, std::min<size_t>(size, sizeof(pose)));
    return 1;
}

extern "C" int C_SpawnPuppet(void) {
    for (int slot = 0; slot < C_PUPPET_MAX; slot++) {
        if (!sPuppets[slot].used) {
            sPuppets[slot] = Puppet {};
            sPuppets[slot].used = true;
            sPuppets[slot].owner = ModOwner::Current();
            return slot;
        }
    }
    return -1;
}

extern "C" void C_SetPuppetPoseSized(int puppet, const C_PlayerPose* poseDef, uint32_t size) {
    Puppet* found = Find(puppet);
    const SizedDef<C_PlayerPose> sized(poseDef, size);
    if (found == nullptr || sized.get() == nullptr) {
        return;
    }
    found->pose = *sized.get();
    found->pose.map[sizeof(found->pose.map) - 1] = '\0';
    found->hasPose = true;
}

extern "C" void C_RemovePuppet(int puppet) {
    if (Puppet* found = Find(puppet)) {
        FreeNpc(*found);
        *found = Puppet {};
    }
}

extern "C" void* C_GetPuppetNpc(int puppet) {
    Puppet* found = Find(puppet);
    return found != nullptr && found->npcIndex >= 0 ? get_npc_by_index(found->npcIndex) : nullptr;
}

#endif
