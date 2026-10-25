#include <algorithm>
#include <cstddef>
#include <cstdint>

#include <libultraship/libultraship.h>
#include <ship/resource/type/Blob.h>
#include <spdlog/spdlog.h>

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
static uint8_t sPauseHeels[] = { 0xF7, 0x28, 0x45, 0x45, 0x4C, 0x53, 0xFD };
static uint8_t sPauseSuperHeels[] = { 0xF7, 0x33, 0x55, 0x50, 0x45, 0x52, 0xF7, 0x28, 0x45, 0x45, 0x4C, 0x53, 0xFD };
static uint8_t sPauseUltraHeels[] = { 0xF7, 0x35, 0x4C, 0x54, 0x52, 0x41, 0xF7, 0x28, 0x45, 0x45, 0x4C, 0x53, 0xFD };
static uint8_t sPauseParasol[] = { 0xF7, 0x30, 0x41, 0x52, 0x41, 0x53, 0x4F, 0x4C, 0xFD };
static uint8_t sPauseSuperParasol[] = { 0xF7, 0x33, 0x55, 0x50, 0x45, 0x52, 0xF7, 0x30,
                                        0x41, 0x52, 0x41, 0x53, 0x4F, 0x4C, 0xFD };
static uint8_t sPauseUltraParasol[] = { 0xF7, 0x35, 0x4C, 0x54, 0x52, 0x41, 0xF7, 0x30,
                                        0x41, 0x52, 0x41, 0x53, 0x4F, 0x4C, 0xFD };
static uint8_t sPausePeach[] = { 0xF7, 0xFF, 0x10, 0x00, 0x00, 0x30, 0x45, 0x41, 0x43, 0x48, 0xFD };

constexpr size_t kItemStride = 0x20;
constexpr size_t kPlayerSpriteSetStride = 0xC;

// Paper Peach by AgateTrevalyn (gamebanana.com/mods/576687); see docs/romhacks/paper-peach.md.
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
        gPauseMessages[PAUSE_MSG_3C] = (intptr_t) sPauseHeels;
        gPauseMessages[PAUSE_MSG_3D] = (intptr_t) sPauseSuperHeels;
        gPauseMessages[PAUSE_MSG_3E] = (intptr_t) sPauseUltraHeels;
        gPauseMessages[PAUSE_MSG_40] = (intptr_t) sPauseParasol;
        gPauseMessages[PAUSE_MSG_41] = (intptr_t) sPauseSuperParasol;
        gPauseMessages[PAUSE_MSG_42] = (intptr_t) sPauseUltraParasol;
        gPauseMessages[PAUSE_MSG_MARIO] = (intptr_t) sPausePeach;
    }
};

std::unique_ptr<Romhack::Port> CreatePaperPeachPort() {
    return std::make_unique<PaperPeachPort>();
}
