#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <utility>

#include <libultraship/libultraship.h>
#include <ship/resource/type/Blob.h>
#include <spdlog/spdlog.h>

#include "port/Engine.h"
#include "port/modding/DataTables.h"
#include "port/romhack/RomhackPort.h"

extern "C" {
#include "common.h"
#include "pause/pause_common.h"
#include "sprite.h"

extern intptr_t gPauseMessages[];
extern MoveData gMoveTable[];
extern ItemData gItemTable[];
extern PlayerSpriteSet PlayerSpriteSets[];
}

// Pause menu labels the hack keeps in expansion RAM rather than the message bank.
static const std::pair<int32_t, const char*> sPauseMessageAssets[] = {
    { PAUSE_MSG_3C, "__OTR__romhack/pause_heels" },         { PAUSE_MSG_3D, "__OTR__romhack/pause_super_heels" },
    { PAUSE_MSG_3E, "__OTR__romhack/pause_ultra_heels" },   { PAUSE_MSG_40, "__OTR__romhack/pause_parasol" },
    { PAUSE_MSG_41, "__OTR__romhack/pause_super_parasol" }, { PAUSE_MSG_42, "__OTR__romhack/pause_ultra_parasol" },
    { PAUSE_MSG_MARIO, "__OTR__romhack/pause_peach" },
};

constexpr size_t kItemStride = 0x20;
constexpr size_t kPlayerSpriteSetStride = 0xC;

class PaperPeachPort final : public Romhack::Port {
public:
    void ApplyDataTables() override {
        if (auto moves = Mod_LoadTable("romhack/move_table")) {
            const size_t count = std::min<size_t>(moves->Data.size() / sizeof(MoveData), NUM_MOVES);
            for (size_t i = 0; i < count; i++) {
                const auto* src = reinterpret_cast<const uint8_t*>(moves->Data.data()) + i * sizeof(MoveData);
                gMoveTable[i].costFP = (s8) src[offsetof(MoveData, costFP)];
                gMoveTable[i].costBP = (s8) src[offsetof(MoveData, costBP)];
            }
            SPDLOG_INFO("Romhack: applied FP/BP costs for {} moves", count);
        }
        if (auto items = Mod_LoadTable("romhack/item_table")) {
            const size_t count = std::min<size_t>(items->Data.size() / kItemStride, NUM_ITEMS);
            for (size_t i = 0; i < count; i++) {
                const auto* src = reinterpret_cast<const uint8_t*>(items->Data.data()) + i * kItemStride;
                gItemTable[i].nameMsg = Mod_ReadBE32(src + offsetof(ItemData, nameMsg));
                gItemTable[i].fullDescMsg = Mod_ReadBE32(src + offsetof(ItemData, fullDescMsg));
                gItemTable[i].shortDescMsg = Mod_ReadBE32(src + offsetof(ItemData, shortDescMsg));
            }
            SPDLOG_INFO("Romhack: applied item messages for {} items", count);
        }
        if (auto sets = Mod_LoadTable("romhack/player_sprite_sets")) {
            const size_t count =
                std::min<size_t>(sets->Data.size() / kPlayerSpriteSetStride, PLAYER_SPRITES_PEACH_BATTLE + 1);
            for (size_t i = 0; i < count; i++) {
                const auto* src = reinterpret_cast<const uint8_t*>(sets->Data.data()) + i * kPlayerSpriteSetStride;
                PlayerSpriteSets[i].rasterSize = Mod_ReadBE32(src + offsetof(PlayerSpriteSet, rasterSize));
            }
            SPDLOG_INFO("Romhack: applied raster sizes for {} player sprite sets", count);
        }
    }

    void Init() override {
        for (const auto& [index, path] : sPauseMessageAssets) {
            if (void* data = LOAD_ASSET(path)) {
                gPauseMessages[index] = (intptr_t) data;
            }
        }
    }
};

std::unique_ptr<Romhack::Port> CreatePaperPeachPort() {
    return std::make_unique<PaperPeachPort>();
}
