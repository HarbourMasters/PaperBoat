#ifdef ENABLE_SCRIPTING

#include "port/api/puppet.h"
#include "port/api/world.h"

#include "port/ShipInit.hpp"
#include "port/api/ModOwner.hpp"
#include "port/api/SizedDef.hpp"
#include "port/hooks/Events.h"
#include "port/interpolation/FrameInterpolation.h"
#include "port/patches/Patches.h"

#include "common.h"
#include "game_modes.h"
#include "npc.h"
#include "sprite.h"
#include "sprite/player.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <string>
#include <vector>

extern "C" {
extern PlayerCurrentAnimInfo CurPlayerAnimInfo[];
s32 get_player_back_anim(s32 anim);
}

static_assert(C_PUPPET_MAX <= PLAYER_SPRITE_PUPPET_COUNT, "a player sprite slot for each puppet");

namespace {

// NPC ids past the ones maps give their own NPCs.
constexpr s32 kFirstNpcID = 100;
constexpr float kSnapDistance = 200.0f;
// Frames behind the newest pose, so a late pose still arrives in time.
constexpr double kPlaybackDelay = 4.0;
constexpr double kResyncFrames = 30.0;
constexpr size_t kMaxSnapshots = 32;

struct Snapshot {
    C_PlayerPose pose;
    double frame;
};
constexpr float kFlipStep = 28.0f;

struct Puppet {
    bool used = false;
    bool hasPose = false;
    std::string owner;
    C_PlayerPose pose {};
    std::deque<Snapshot> snapshots;
    double playFrame = 0.0;
    bool playing = false;
    s32 npcIndex = -1;
    // Facing, worked out like player_update_sprite.
    bool facingSet = false;
    s32 direction = 0;
    float camRelativeYaw = 0.0f;
    float flipYaw = 0.0f;
    float facingAngle = 0.0f;
    bool encounter = false;
    bool touching = false;
};

std::array<Puppet, C_PUPPET_MAX> sPuppets;
uint32_t sFrame = 0;
// Frames in the world since the last battle or menu, so the player can walk away before a puppet counts again.
int sWorldFrames = 0;
constexpr int kEncounterCooldown = 60;
std::vector<s32> sOrphanNpcs;

// The puppet's NPC while it is in the map being played.
Npc* PuppetNpc(const Puppet& puppet) {
    return puppet.used && puppet.npcIndex >= 0 ? get_npc_by_index(puppet.npcIndex) : nullptr;
}

const char* CurrentMap() {
    const AreaConfig& area = gAreas[gGameStatusPtr->areaID];
    return gGameStatusPtr->mapID < area.mapCount ? area.maps[gGameStatusPtr->mapID].id : "";
}

AnimID MotionAnim(int32_t motion) {
    switch (motion) {
        case C_PUPPET_WALK:
            return ANIM_Mario1_Walk;
        case C_PUPPET_RUN:
            return ANIM_Mario1_Run;
        case C_PUPPET_JUMP:
            return ANIM_Mario1_Jump;
        case C_PUPPET_FALL:
            return ANIM_Mario1_Fall;
        case C_PUPPET_LAND:
            return ANIM_Mario1_Land;
        default:
            return ANIM_Mario1_Idle;
    }
}

void FreeNpc(Puppet& puppet) {
    if (puppet.npcIndex < 0) {
        return;
    }
    if (get_game_mode() != GAME_MODE_WORLD) {
        sOrphanNpcs.push_back(puppet.npcIndex);
    } else if (Npc* npc = get_npc_by_index(puppet.npcIndex)) {
        free_npc(npc);
    }
    puppet.npcIndex = -1;
}

Npc* SpawnNpc(Puppet& puppet, int slot) {
    NpcBlueprint blueprint = {};
    blueprint.flags = NPC_FLAG_IGNORE_PLAYER_COLLISION | NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_HAS_NO_SPRITE;
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
    puppet.facingSet = false;
    return npc;
}

s32 UpdateFacing(Puppet& puppet, s32 anim) {
    const float cameraYaw = gCameras[gCurrentCameraID].curYaw;
    const float diff = get_clamped_angle_diff(cameraYaw, puppet.pose.yaw);
    s32 direction = 2;
    float camRelativeYaw = puppet.camRelativeYaw;
    if (diff < -5.0f && diff > -175.0f) {
        camRelativeYaw = 0.0f;
        direction = 0;
    } else if (diff > 5.0f && diff < 175.0f) {
        camRelativeYaw = 180.0f;
        direction = 1;
    }
    if (!puppet.facingSet) {
        puppet.facingSet = true;
        puppet.direction = direction == 2 ? 0 : direction;
        puppet.flipYaw = 0.0f;
    } else if (direction != 2 && direction != puppet.direction) {
        puppet.direction = direction;
        puppet.flipYaw = direction != 0 ? 180.0f : -180.0f;
        if (std::fabs(diff) >= 90.0f) {
            puppet.flipYaw = -puppet.flipYaw;
        }
    }
    if (puppet.flipYaw < 0.0f) {
        puppet.flipYaw = std::min(puppet.flipYaw + kFlipStep, 0.0f);
    } else if (puppet.flipYaw > 0.0f) {
        puppet.flipYaw = std::max(puppet.flipYaw - kFlipStep, 0.0f);
    }
    puppet.camRelativeYaw = camRelativeYaw;
    puppet.facingAngle = clamp_angle(puppet.flipYaw + camRelativeYaw);

    const s32 sprite = SPR_UNPACK_SPR(anim);
    if ((sprite == SPR_Mario1 || sprite == SPR_MarioW1 || sprite == SPR_Peach1) && std::fabs(diff) < 60.0f) {
        const s32 back = get_player_back_anim(anim);
        // The back of these is drawn from the sprite after them.
        if (!(back & SPRITE_ID_BACK_FACING) || port_player_sprite(sprite + 1) != nullptr) {
            anim = back;
        }
    }
    return anim;
}

void UpdateSprite(Puppet& puppet, int slot) {
    s32 anim = port_is_player_anim(puppet.pose.anim) ? puppet.pose.anim : MotionAnim(puppet.pose.motion);
    if (!port_is_player_anim(anim)) {
        return;
    }
    anim = UpdateFacing(puppet, anim);
    spr_update_player_sprite(PLAYER_SPRITE_PUPPET_FIRST + slot, anim, 1.0f);
}

void AppendPuppetGfx(void* data) {
    Puppet& puppet = *static_cast<Puppet*>(data);
    const int slot = static_cast<int>(&puppet - sPuppets.data());
    Npc* npc = PuppetNpc(puppet);
    const s32 animID = CurPlayerAnimInfo[PLAYER_SPRITE_PUPPET_FIRST + slot].animID;
    if (npc == nullptr || animID == -1) {
        return;
    }
    SpriteAnimData* sprite = port_player_sprite(SPR_UNPACK_SPR(animID));
    if (sprite == nullptr) {
        return;
    }
    Matrix4f mtx, tmp;
    guRotateF(mtx, puppet.facingAngle, 0.0f, 1.0f, 0.0f);
    guScaleF(tmp, SPRITE_WORLD_SCALE_D, SPRITE_WORLD_SCALE_D, SPRITE_WORLD_SCALE_D);
    guMtxCatF(mtx, tmp, mtx);
    guTranslateF(tmp, npc->pos.x, npc->pos.y, npc->pos.z);
    guMtxCatF(mtx, tmp, mtx);
    s32 flags = (PLAYER_SPRITE_PUPPET_FIRST + slot) | DRAW_SPRITE_OVERRIDE_PALETTES;
    if (puppet.facingAngle >= 90.0f && puppet.facingAngle < 270.0f) {
        flags |= DRAW_SPRITE_UPSIDE_DOWN;
    }
    spr_draw_player_sprite(flags, 0, 0, port_colored_player_palettes(
                               sprite->palettesOffset, puppet.pose.color != 0 ? puppet.pose.color : C_PUPPET_DEFAULT_COLOR
                           ), mtx);
}

void DrawPuppets() {
    for (Puppet& puppet : sPuppets) {
        Npc* npc = PuppetNpc(puppet);
        if (npc == nullptr) {
            continue;
        }
        s32 x, y, z;
        get_screen_coords(gCurrentCamID, npc->pos.x, npc->pos.y, npc->pos.z, &x, &y, &z);
        RenderTask task = {};
        task.renderMode = RENDER_MODE_ALPHATEST;
        task.dist = -z;
        task.appendGfxArg = &puppet;
        task.appendGfx = AppendPuppetGfx;
        task.needsInterpolation = true;
        task.interpolationName = (char*) "puppets";
        task.interpolationTag = TAG_NPC(0, npc);
        queue_render_task(&task);
    }
}

// Map loads and battles clear the workers.
void EnsureDrawWorker() {
    for (s32 i = 0; i < MAX_WORKERS; i++) {
        Worker* worker = get_worker(i);
        if (worker != nullptr && worker->draw == DrawPuppets) {
            return;
        }
    }
    create_worker_scene(nullptr, DrawPuppets);
}

void Play(Puppet& puppet) {
    std::deque<Snapshot>& snapshots = puppet.snapshots;
    const double target = snapshots.back().frame - kPlaybackDelay;
    if (!puppet.playing || std::fabs(target - puppet.playFrame) > kResyncFrames) {
        puppet.playFrame = target;
        puppet.playing = true;
    } else {
        puppet.playFrame += 1.0 + std::clamp((target - puppet.playFrame) * 0.02, -0.05, 0.05);
    }
    while (snapshots.size() >= 2 && snapshots[1].frame <= puppet.playFrame) {
        snapshots.pop_front();
    }
    const Snapshot& from = snapshots.front();
    if (snapshots.size() == 1 || puppet.playFrame <= from.frame) {
        puppet.pose = from.pose;
        return;
    }
    const Snapshot& to = snapshots[1];
    const float t = static_cast<float>((puppet.playFrame - from.frame) / (to.frame - from.frame));
    const float dx = to.pose.x - from.pose.x;
    const float dy = to.pose.y - from.pose.y;
    const float dz = to.pose.z - from.pose.z;
    puppet.pose = from.pose;
    if (std::sqrt(dx * dx + dy * dy + dz * dz) <= kSnapDistance && strcmp(from.pose.map, to.pose.map) == 0) {
        puppet.pose.x += dx * t;
        puppet.pose.y += dy * t;
        puppet.pose.z += dz * t;
    }
}

constexpr int32_t kNoEncounter = -1;

// How the player is running into the puppet, as encounter.c works it out for enemies, or kNoEncounter. The puppet is
// the player's size, and walls between them aren't checked.
int32_t TestEncounter(const Npc* npc) {
    const PlayerStatus& player = gPlayerStatus;
    const float radius = player.colliderDiameter / 2.0f;
    const float height = player.colliderHeight;
    const float dx = npc->pos.x - player.pos.x;
    const float dz = npc->pos.z - player.pos.z;
    const float distance = std::sqrt(dx * dx + dz * dz);
    const bool overlapsY = !(player.pos.y > npc->pos.y + height) && !(npc->pos.y > player.pos.y + height);

    switch (player.actionState) {
        case ACTION_STATE_HAMMER:
            if (player.flags & PS_FLAG_HAMMER_CHECK) {
                const float cameraYaw = gCameras[gCurrentCameraID].curYaw;
                float hammerYaw = clamp_angle(player.spriteFacingAngle) < 180.0f ? clamp_angle(cameraYaw - 90.0f)
                                                                                   : clamp_angle(cameraYaw + 90.0f);
                float x = player.pos.x;
                float z = player.pos.z;
                add_vec2D_polar(&x, &z, 24.0f, hammerYaw);
                const float hx = npc->pos.x - x;
                const float hz = npc->pos.z - z;
                if (std::sqrt(hx * hx + hz * hz) < radius * 2.0f && overlapsY) {
                    return C_BATTLE_START_HAMMER;
                }
            }
            break;
        case ACTION_STATE_FALLING:
        case ACTION_STATE_STEP_DOWN:
        case ACTION_STATE_LAND:
        case ACTION_STATE_STEP_DOWN_LAND:
        case ACTION_STATE_SPIN_JUMP:
        case ACTION_STATE_SPIN_POUND:
        case ACTION_STATE_TORNADO_JUMP:
        case ACTION_STATE_TORNADO_POUND:
            if (distance < radius * 2.0f && overlapsY && npc->pos.y + height < player.pos.y + height * 0.5f) {
                return C_BATTLE_START_JUMP;
            }
            break;
    }
    if (distance < radius * 2.0f * 0.8f && overlapsY) {
        return C_BATTLE_START_NORMAL;
    }
    return kNoEncounter;
}

// Fires OnPuppetEncounter when the player runs into a puppet with encounters on, once each time they touch.
void TestEncounters() {
    if (gEncounterState != ENCOUNTER_STATE_NEUTRAL || (gPlayerStatus.flags & PS_FLAG_INPUT_DISABLED)) {
        return;
    }
    // Only frames the player is free to move count towards the cooldown.
    if (++sWorldFrames < kEncounterCooldown) {
        return;
    }
    for (int slot = 0; slot < C_PUPPET_MAX; slot++) {
        Puppet& puppet = sPuppets[slot];
        Npc* npc = puppet.encounter ? PuppetNpc(puppet) : nullptr;
        const int32_t start = npc != nullptr ? TestEncounter(npc) : kNoEncounter;
        const bool touching = start != kNoEncounter;
        if (touching && !puppet.touching) {
            puppet.touching = true;
            CALL_EVENT(OnPuppetEncounter, slot, start);
            if (gEncounterState != ENCOUNTER_STATE_NEUTRAL) {
                return; // a listener started a battle
            }
        }
        puppet.touching = touching;
    }
}

void Update() {
    if (get_game_mode() != GAME_MODE_WORLD) {
        sWorldFrames = 0;
        return;
    }
    for (s32 index : sOrphanNpcs) {
        if (Npc* npc = get_npc_by_index(index)) {
            free_npc(npc);
        }
    }
    sOrphanNpcs.clear();
    const char* map = CurrentMap();
    bool shown = false;
    for (int slot = 0; slot < C_PUPPET_MAX; slot++) {
        Puppet& puppet = sPuppets[slot];
        if (puppet.used && puppet.hasPose) {
            Play(puppet);
        }
        if (!puppet.used || !puppet.hasPose || strncmp(puppet.pose.map, map, sizeof(puppet.pose.map)) != 0) {
            FreeNpc(puppet);
            continue;
        }
        Npc* npc = puppet.npcIndex >= 0 ? get_npc_by_index(puppet.npcIndex) : SpawnNpc(puppet, slot);
        if (npc == nullptr) {
            continue;
        }
        npc->pos.x = puppet.pose.x;
        npc->pos.y = puppet.pose.y;
        npc->pos.z = puppet.pose.z;
        npc->yaw = puppet.pose.yaw;
        UpdateSprite(puppet, slot);
        shown = true;
    }
    if (shown) {
        EnsureDrawWorker();
        TestEncounters();
    } else {
        sWorldFrames = 0;
    }
}

void InitPuppetApi() {
    REGISTER_LISTENER(GameFrameUpdate, EVENT_PRIORITY_NORMAL, [](IEvent*) {
        sFrame++;
        Update();
    });
    // Loading a map frees every NPC and the sprite heap the palettes came from.
    REGISTER_LISTENER(OnMapLoad, EVENT_PRIORITY_NORMAL, [](IEvent*) {
        for (Puppet& puppet : sPuppets) {
            puppet.npcIndex = -1;
        }
        sOrphanNpcs.clear();
        port_reset_colored_palettes();
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

int32_t WorldMotion(const PlayerStatus& player) {
    switch (player.actionState) {
        case ACTION_STATE_WALK:
            return C_PUPPET_WALK;
        case ACTION_STATE_RUN:
            return C_PUPPET_RUN;
        case ACTION_STATE_JUMP:
        case ACTION_STATE_HOP:
            return C_PUPPET_JUMP;
        case ACTION_STATE_FALLING:
            return C_PUPPET_FALL;
        case ACTION_STATE_LAND:
            return C_PUPPET_LAND;
        default:
            return C_PUPPET_IDLE;
    }
}

} // namespace

extern "C" int C_GetPlayerPoseSized(C_PlayerPose* out, uint32_t size) {
    if (out == nullptr) {
        return 0;
    }
    const PlayerStatus& player = gPlayerStatus;
    C_PlayerPose pose = {};
    switch (get_game_mode()) {
        case GAME_MODE_WORLD:
            pose.anim = player.anim;
            pose.motion = WorldMotion(player);
            break;
        case GAME_MODE_BATTLE: {
            Actor* actor = gBattleStatus.playerActor;
            if (actor == nullptr || actor->partsTable == nullptr) {
                return 0;
            }
            pose.anim = actor->partsTable->curAnimation;
            pose.motion = C_PUPPET_BATTLE;
            break;
        }
        default:
            return 0;
    }
    pose.x = player.pos.x;
    pose.y = player.pos.y;
    pose.z = player.pos.z;
    pose.yaw = player.targetYaw;
    pose.frame = sFrame;
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
    Snapshot snapshot { *sized.get(), 0.0 };
    snapshot.pose.map[sizeof(snapshot.pose.map) - 1] = '\0';
    snapshot.frame = snapshot.pose.frame != 0 ? snapshot.pose.frame : sFrame;
    std::deque<Snapshot>& snapshots = found->snapshots;
    if (!snapshots.empty()) {
        const double newest = snapshots.back().frame;
        if (snapshot.frame <= newest && snapshot.frame > newest - kResyncFrames) {
            return;
        }
        if (snapshot.frame < newest) {
            snapshots.clear(); // the sender restarted
        }
    }
    snapshots.push_back(snapshot);
    if (snapshots.size() > kMaxSnapshots) {
        snapshots.pop_front();
    }
    if (!found->hasPose) {
        found->pose = snapshot.pose;
        found->hasPose = true;
    }
}

extern "C" void C_RemovePuppet(int puppet) {
    if (Puppet* found = Find(puppet)) {
        FreeNpc(*found);
        *found = Puppet {};
    }
}

extern "C" void* C_GetPuppetNpc(int puppet) {
    Puppet* found = Find(puppet);
    return found != nullptr ? PuppetNpc(*found) : nullptr;
}

extern "C" void C_SetPuppetEncounter(int puppet, int enabled) {
    if (Puppet* found = Find(puppet)) {
        found->encounter = enabled != 0;
    }
}

#endif
