#include "port/patches/Patches.h"
#include "port/sprite/SpriteLoader.h"

#include "common.h"
#include "sprite.h"
#include "sprite/player.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <map>
#include <utility>
#include <vector>

extern "C" {
extern SpriteAnimData* PlayerSprites[13];
extern s32 MaxPlayerSpriteComponents;
}

namespace {

// Player sprites the current set didn't load, e.g. the battle ones in the world. Kept outside the sprite heap.
std::map<s32, std::vector<uint64_t>> sExtraPlayerSprites;

struct ColoredPalettes {
    std::vector<PAL_PTR> source;
    std::vector<std::array<u16, SPR_PAL_SIZE>> data;
    std::vector<PAL_PTR> list;
};
std::map<std::pair<PAL_PTR*, u32>, ColoredPalettes> sColoredPalettes;

bool IsRed(u16 r, u16 g, u16 b) {
    // Strong reds only: the shoes and hair are brownish reds.
    return r >= 12 && g * 3 <= r && b * 3 <= r;
}

} // namespace

extern "C" {

SpriteAnimData* port_player_sprite(s32 spriteID) {
    if (spriteID < SPR_Mario1 || spriteID > SPR_Peach3) {
        return nullptr;
    }
    SpriteAnimData*& loaded = PlayerSprites[spriteID - 1];
    if (loaded != nullptr) {
        return loaded;
    }
    auto it = sExtraPlayerSprites.find(spriteID);
    if (it == sExtraPlayerSprites.end()) {
        const size_t size = Sprite_GetPlayerSize(spriteID - 1);
        std::vector<uint64_t> data((size + sizeof(uint64_t) - 1) / sizeof(uint64_t));
        if (size == 0 || Sprite_LoadPlayer(spriteID - 1, data.data(), size) == nullptr) {
            data.clear();
        }
        it = sExtraPlayerSprites.emplace(spriteID, std::move(data)).first;
    }
    if (it->second.empty()) {
        return nullptr;
    }
    loaded = reinterpret_cast<SpriteAnimData*>(it->second.data());
    MaxPlayerSpriteComponents = std::max(MaxPlayerSpriteComponents, loaded->maxComponents);
    return loaded;
}

b32 port_is_player_anim(s32 animID) {
    const s32 spriteID = SPR_UNPACK_SPR(animID);
    SpriteAnimData* sprite = port_player_sprite(spriteID);
    if (sprite == nullptr) {
        return false;
    }
    const s32 index = SPR_UNPACK_ANIM(animID);
    for (s32 i = 0; i <= index; i++) {
        if (sprite->animListStart[i] == PTR_LIST_END) {
            return false;
        }
    }
    // The back of these is drawn from the sprite after them.
    if ((animID & SPRITE_ID_BACK_FACING) && (spriteID == SPR_Mario1 || spriteID == SPR_MarioW1 || spriteID == SPR_Peach1)) {
        return port_player_sprite(spriteID + 1) != nullptr;
    }
    return true;
}

PAL_PTR* port_colored_player_palettes(PAL_PTR* palettes, u32 color) {
    if (palettes == nullptr) {
        return nullptr;
    }
    s32 count = 0;
    while (palettes[count] != (PAL_PTR) -1) {
        count++;
    }
    ColoredPalettes& colored = sColoredPalettes[{ palettes, color }];
    if (colored.source.size() == (size_t) count && std::equal(colored.source.begin(), colored.source.end(), palettes)) {
        return colored.list.data();
    }
    const float tint[3] = { ((color >> 24) & 0xFF) / 255.0f, ((color >> 16) & 0xFF) / 255.0f,
                            ((color >> 8) & 0xFF) / 255.0f };
    colored.source.assign(palettes, palettes + count);
    colored.data.assign(count, {});
    colored.list.clear();
    for (s32 i = 0; i < count; i++) {
        const PAL_PTR source = port_sprite_palette_data(palettes[i]);
        if (source == nullptr || source == (PAL_PTR) -1) {
            colored.list.push_back(palettes[i]);
            continue;
        }
        // RGBA5551, high byte first. The brightest red becomes the color and the others the same shade darker.
        const u8* in = reinterpret_cast<const u8*>(source);
        u8* out = reinterpret_cast<u8*>(colored.data[i].data());
        u16 brightest = 0;
        for (s32 c = 0; c < SPR_PAL_SIZE; c++) {
            const u16 entry = (in[c * 2] << 8) | in[c * 2 + 1];
            const u16 r = (entry >> 11) & 0x1F;
            if (IsRed(r, (entry >> 6) & 0x1F, (entry >> 1) & 0x1F)) {
                brightest = std::max(brightest, r);
            }
        }
        for (s32 c = 0; c < SPR_PAL_SIZE; c++) {
            const u16 entry = (in[c * 2] << 8) | in[c * 2 + 1];
            u16 r = (entry >> 11) & 0x1F;
            u16 g = (entry >> 6) & 0x1F;
            u16 b = (entry >> 1) & 0x1F;
            if (IsRed(r, g, b)) {
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

void port_reset_colored_palettes(void) {
    sColoredPalettes.clear();
}

} // extern "C"
