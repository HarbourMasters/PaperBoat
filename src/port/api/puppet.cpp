#ifdef ENABLE_SCRIPTING

#include "port/api/puppet.h"

#include "port/ShipInit.hpp"
#include "port/api/ModOwner.hpp"
#include "port/api/SizedDef.hpp"
#include "port/hooks/Events.h"
#include "port/interpolation/FrameInterpolation.h"
#include "port/patches/Patches.h"
#include "port/sprite/SpriteLoader.h"

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
#include <map>
#include <string>
#include <vector>

extern "C" {
extern SpriteAnimData* PlayerSprites[13];
extern s32 MaxPlayerSpriteComponents;
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
    s32 slotComponents = 0;
};

std::array<Puppet, C_PUPPET_MAX> sPuppets;
uint32_t sFrame = 0;
std::vector<s32> sOrphanNpcs;

// Player sprites the current set didn't load, e.g. the battle ones in the world. Kept outside the sprite heap.
std::map<s32, std::vector<uint64_t>> sExtraPlayerSprites;

struct ColoredPalettes {
    std::vector<PAL_PTR> source;
    std::vector<std::array<u16, SPR_PAL_SIZE>> data;
    std::vector<PAL_PTR> list;
};
std::map<std::pair<PAL_PTR*, uint32_t>, ColoredPalettes> sColoredPalettes;

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

SpriteAnimData* GetPlayerSprite(s32 sprite) {
    if (sprite < SPR_Mario1 || sprite > SPR_Peach3) {
        return nullptr;
    }
    SpriteAnimData*& loaded = PlayerSprites[sprite - 1];
    if (loaded != nullptr) {
        return loaded;
    }
    auto it = sExtraPlayerSprites.find(sprite);
    if (it == sExtraPlayerSprites.end()) {
        const size_t size = Sprite_GetPlayerSize(sprite - 1);
        std::vector<uint64_t> data((size + sizeof(uint64_t) - 1) / sizeof(uint64_t));
        if (size == 0 || Sprite_LoadPlayer(sprite - 1, data.data(), size) == nullptr) {
            data.clear();
        }
        it = sExtraPlayerSprites.emplace(sprite, std::move(data)).first;
    }
    if (it->second.empty()) {
        return nullptr;
    }
    loaded = reinterpret_cast<SpriteAnimData*>(it->second.data());
    MaxPlayerSpriteComponents = std::max(MaxPlayerSpriteComponents, loaded->maxComponents);
    return loaded;
}

// anim comes from another game, so it is checked before indexing animListStart.
bool IsPlayableAnim(s32 anim) {
    SpriteAnimData* sprite = GetPlayerSprite(SPR_UNPACK_SPR(anim));
    if (sprite == nullptr) {
        return false;
    }
    const s32 index = SPR_UNPACK_ANIM(anim);
    for (s32 i = 0; i <= index; i++) {
        if (sprite->animListStart[i] == PTR_LIST_END) {
            return false;
        }
    }
    return true;
}

PAL_PTR* GetColoredPalettes(PAL_PTR* palettes, uint32_t color) {
    s32 count = 0;
    while (palettes[count] != (PAL_PTR) -1) {
        count++;
    }
    if (color == 0) {
        color = C_PUPPET_DEFAULT_COLOR;
    }
    const float tint[3] = { ((color >> 24) & 0xFF) / 255.0f, ((color >> 16) & 0xFF) / 255.0f,
                            ((color >> 8) & 0xFF) / 255.0f };
    ColoredPalettes& colored = sColoredPalettes[{ palettes, color }];
    if (colored.source.size() == (size_t) count && std::equal(colored.source.begin(), colored.source.end(), palettes)) {
        return colored.list.data();
    }
    colored.source.assign(palettes, palettes + count);
    colored.data.assign(count, {});
    colored.list.clear();
    for (s32 i = 0; i < count; i++) {
        const PAL_PTR source = port_sprite_palette_data(palettes[i]);
        if (source == nullptr || source == (PAL_PTR) -1) {
            colored.list.push_back(palettes[i]);
            continue;
        }
        // RGBA5551, high byte first. Strong reds only: the shoes and hair are brownish reds.
        const u8* in = reinterpret_cast<const u8*>(source);
        u8* out = reinterpret_cast<u8*>(colored.data[i].data());
        auto isRed = [](u16 r, u16 g, u16 b) { return r >= 12 && g * 3 <= r && b * 3 <= r; };
        u16 brightest = 0;
        for (s32 c = 0; c < SPR_PAL_SIZE; c++) {
            const u16 entry = (in[c * 2] << 8) | in[c * 2 + 1];
            const u16 r = (entry >> 11) & 0x1F;
            if (isRed(r, (entry >> 6) & 0x1F, (entry >> 1) & 0x1F)) {
                brightest = std::max(brightest, r);
            }
        }
        for (s32 c = 0; c < SPR_PAL_SIZE; c++) {
            const u16 entry = (in[c * 2] << 8) | in[c * 2 + 1];
            u16 r = (entry >> 11) & 0x1F;
            u16 g = (entry >> 6) & 0x1F;
            u16 b = (entry >> 1) & 0x1F;
            if (isRed(r, g, b)) {
                const float shade = 31.0f * r / brightest;
                r = static_cast<u16>(std::lround(shade * tint[0]));
                g = static_cast<u16>(std::lround(shade * tint[1]));
                b = static_cast<u16>(std::lround(shade * tint[2]));
            }
            const u16 recolored = (r << 11) | (g << 6) | (b << 1) | (entry & 1);
            out[c * 2] = recolored >> 8;
            out[c * 2 + 1] = recolored & 0xFF;
        }
        colored.list.push_back(colored.data[i].data());
    }
    colored.list.push_back((PAL_PTR) -1);
    return colored.list.data();
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
        if (!(back & SPRITE_ID_BACK_FACING) || GetPlayerSprite(sprite + 1) != nullptr) {
            anim = back;
        }
    }
    return anim;
}

void UpdateSprite(Puppet& puppet, int slot) {
    s32 anim = IsPlayableAnim(puppet.pose.anim) ? puppet.pose.anim : MotionAnim(puppet.pose.motion);
    if (!IsPlayableAnim(anim)) {
        return;
    }
    anim = UpdateFacing(puppet, anim);
    PlayerCurrentAnimInfo& info = CurPlayerAnimInfo[PLAYER_SPRITE_PUPPET_FIRST + slot];
    if (info.componentList != nullptr && puppet.slotComponents < MaxPlayerSpriteComponents) {
        // Allocated before a player sprite with more components was loaded.
        info.componentList = nullptr;
        info.animID = -1;
    }
    if (info.componentList == nullptr) {
        puppet.slotComponents = MaxPlayerSpriteComponents;
    }
    spr_update_player_sprite(PLAYER_SPRITE_PUPPET_FIRST + slot, anim, 1.0f);
}

void AppendPuppetGfx(void* data) {
    Puppet& puppet = *static_cast<Puppet*>(data);
    const int slot = static_cast<int>(&puppet - sPuppets.data());
    Npc* npc = puppet.npcIndex >= 0 ? get_npc_by_index(puppet.npcIndex) : nullptr;
    const s32 animID = CurPlayerAnimInfo[PLAYER_SPRITE_PUPPET_FIRST + slot].animID;
    if (npc == nullptr || animID == -1) {
        return;
    }
    SpriteAnimData* sprite = GetPlayerSprite(SPR_UNPACK_SPR(animID));
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
    spr_draw_player_sprite(flags, 0, 0, GetColoredPalettes(sprite->palettesOffset, puppet.pose.color), mtx);
}

void DrawPuppets() {
    for (Puppet& puppet : sPuppets) {
        Npc* npc = puppet.used && puppet.npcIndex >= 0 ? get_npc_by_index(puppet.npcIndex) : nullptr;
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

void Update() {
    if (get_game_mode() != GAME_MODE_WORLD) {
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
        sColoredPalettes.clear();
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
    return found != nullptr && found->npcIndex >= 0 ? get_npc_by_index(found->npcIndex) : nullptr;
}

#endif
