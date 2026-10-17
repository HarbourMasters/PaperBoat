#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include <libultraship/libultraship.h>
#include <ship/resource/type/Blob.h>
#include <spdlog/spdlog.h>

#include "port/modding/Mod.h"
#include "../TTYD64.h"
#include "../include/ttyd64_items.h"

extern "C" {
#include "common.h"
#include "battle/battle.h"
#include "msg.h"
#include "data.h"

extern MoveData gMoveTable[];
extern ItemData gItemTable[];
extern intptr_t gItemIconRasterOffsets[];
extern intptr_t gItemIconPaletteOffsets[];
extern PartnerDMAData bPartnerDmaTable[];
extern u8* ActorTypesLists[];
}

static_assert(sizeof(MoveData) == 0x14);
static_assert(sizeof(ItemData) == 0x20);
static_assert(sizeof(ActorSounds) == 0x1C);
static_assert(sizeof(ActorOffsets) == 4);

namespace {

constexpr const char* kOwner = "TTYD64";
constexpr size_t kItemStride = 0x20;
constexpr size_t kActorTypeCount = 212;
constexpr size_t kActorTypesListsCapacity = 11;
constexpr size_t kActorGroupDataCapacity = 0x100;
constexpr u8 kActorTypeListEnd = 0xFF;
// libultraship's BlobFactory appends kBlobPadding (16) zero bytes to every loaded blob. Tables are
// checked against that exact size on purpose, so a change to the padding fails loudly here.
constexpr size_t kLusBlobPadding = 16;

u8 sActorGroupData[kActorGroupDataCapacity];

std::shared_ptr<Ship::Blob> LoadExact(const char* path, size_t size) {
    auto blob = Mod_LoadTable(path);
    if (blob == nullptr) {
        SPDLOG_ERROR("TTYD64: missing data table {}", path);
        return nullptr;
    }
    if (blob->Data.size() != size + kLusBlobPadding) {
        SPDLOG_ERROR(
            "TTYD64: data table {} is 0x{:X} bytes, expected 0x{:X}", path,
            blob->Data.size() - std::min<size_t>(blob->Data.size(), kLusBlobPadding), size
        );
        return nullptr;
    }
    return blob;
}

const uint8_t* Record(const std::shared_ptr<Ship::Blob>& blob, size_t stride, size_t i) {
    return reinterpret_cast<const uint8_t*>(blob->Data.data()) + i * stride;
}

ItemData DecodeItem(const uint8_t* src, s16 hudElemID) {
    ItemData item = {};
    item.nameMsg = Mod_ReadBE32(src + 0x00);
    item.hudElemID = hudElemID;
    item.sortValue = Mod_ReadBE16(src + 0x06);
    item.targetFlags = Mod_ReadBE32(src + 0x08);
    item.sellValue = Mod_ReadBE16(src + 0x0C);
    item.unk_0E[0] = (char) src[0x0E];
    item.unk_0E[1] = (char) src[0x0F];
    item.fullDescMsg = Mod_ReadBE32(src + 0x10);
    item.shortDescMsg = Mod_ReadBE32(src + 0x14);
    item.typeFlags = Mod_ReadBE16(src + 0x18);
    item.moveID = src[0x1A];
    item.potencyA = (s8) src[0x1B];
    item.potencyB = (s8) src[0x1C];
    item.unk_1D[0] = (char) src[0x1D];
    item.unk_1D[1] = (char) src[0x1E];
    item.unk_1D[2] = (char) src[0x1F];
    return item;
}

const TTYD64_ItemIcon* FindIcon(s32 itemID) {
    for (s32 i = 0; i < TTYD64_ItemIconCount; i++) {
        if (TTYD64_ItemIcons[i].itemID == itemID) {
            return &TTYD64_ItemIcons[i];
        }
    }
    return nullptr;
}

void ApplyItems() {
    auto items = LoadExact("romhack/item_table", TTYD64_ITEM_COUNT * kItemStride);
    if (items == nullptr) {
        return;
    }
    for (s32 i = 0; i < NUM_ITEMS; i++) {
        gItemTable[i] = DecodeItem(Record(items, kItemStride, i), gItemTable[i].hudElemID);
    }
    for (s32 i = 0; i < TTYD64_ItemIconTailCount; i++) {
        const TTYD64_ItemIconOffsets* tail = &TTYD64_ItemIconTail[i];
        gItemIconRasterOffsets[tail->itemID] = (intptr_t) tail->raster;
        gItemIconPaletteOffsets[tail->itemID] = (intptr_t) tail->palette;
    }
    for (s32 i = 0; i < TTYD64_ItemIconCount; i++) {
        const TTYD64_ItemIcon* icon = &TTYD64_ItemIcons[i];
        if (icon->itemID < NUM_ITEMS) {
            Mod_SetItemIcon(
                kOwner, icon->itemID, icon->enabled, icon->disabled, icon->entity, icon->raster, icon->palette
            );
        }
    }
    for (s32 i = NUM_ITEMS; i < TTYD64_ITEM_COUNT; i++) {
        const ItemData data = DecodeItem(Record(items, kItemStride, i), (s16) i);
        const TTYD64_ItemIcon* icon = FindIcon(i);
        if (icon == nullptr) {
            SPDLOG_ERROR("TTYD64: item {} has no icon", i);
            continue;
        }
        Mod_RegisterItem(kOwner, i, &data, icon->enabled, icon->disabled, icon->entity, icon->raster, icon->palette);
    }
    SPDLOG_INFO("TTYD64: applied {} item records, gItemCount {}", TTYD64_ITEM_COUNT, gItemCount);
}

void ApplyMoves() {
    auto moves = LoadExact("romhack/move_table", TTYD64_MOVE_COUNT * sizeof(MoveData));
    if (moves == nullptr) {
        return;
    }
    for (s32 i = 0; i < TTYD64_MOVE_COUNT; i++) {
        const uint8_t* src = Record(moves, sizeof(MoveData), i);
        MoveData* dst = &gMoveTable[i];
        const s32 nameMsg = Mod_ReadBE32(src + 0x00);
        const s32 shortDescMsg = Mod_ReadBE32(src + 0x08);
        const s32 fullDescMsg = Mod_ReadBE32(src + 0x0C);
        if (!MSG_ID_IS_PTR(nameMsg)) {
            dst->nameMsg = nameMsg;
        }
        dst->flags = Mod_ReadBE32(src + 0x04);
        if (!MSG_ID_IS_PTR(shortDescMsg)) {
            dst->shortDescMsg = shortDescMsg;
        }
        if (!MSG_ID_IS_PTR(fullDescMsg)) {
            dst->fullDescMsg = fullDescMsg;
        }
        dst->category = (s8) src[0x10];
        dst->costFP = (s8) src[0x11];
        dst->costBP = (s8) src[0x12];
        dst->actionTip = src[0x13];
    }
    gMoveCount = TTYD64_MOVE_COUNT;
    SPDLOG_INFO("TTYD64: applied {} move records", TTYD64_MOVE_COUNT);
}

void ApplyActorTypes() {
    if (auto names = LoadExact("romhack/actor_names", kActorTypeCount * 4)) {
        for (size_t i = 0; i < kActorTypeCount; i++) {
            bActorNames[i] = Mod_ReadBE32(Record(names, 4, i));
        }
    }
    if (auto tattles = LoadExact("romhack/actor_tattles", kActorTypeCount * 4)) {
        for (size_t i = 0; i < kActorTypeCount; i++) {
            bActorTattles[i] = Mod_ReadBE32(Record(tattles, 4, i));
        }
    }
    if (auto offsets = LoadExact("romhack/actor_offsets", kActorTypeCount * 4)) {
        for (size_t i = 0; i < kActorTypeCount; i++) {
            const uint8_t* src = Record(offsets, 4, i);
            bActorOffsets[i].tattleCam.x = (s8) src[0];
            bActorOffsets[i].tattleCam.y = (s8) src[1];
            bActorOffsets[i].tattleCam.z = (s8) src[2];
            bActorOffsets[i].shadow = (s8) src[3];
        }
    }
    if (auto sounds = LoadExact("romhack/actor_sounds", kActorTypeCount * sizeof(ActorSounds))) {
        for (size_t i = 0; i < kActorTypeCount; i++) {
            const uint8_t* src = Record(sounds, sizeof(ActorSounds), i);
            ActorSounds* dst = &bActorSoundTable[i];
            dst->walk[0] = Mod_ReadBE32(src + 0x00);
            dst->walk[1] = Mod_ReadBE32(src + 0x04);
            dst->fly[0] = Mod_ReadBE32(src + 0x08);
            dst->fly[1] = Mod_ReadBE32(src + 0x0C);
            dst->jump = Mod_ReadBE32(src + 0x10);
            dst->hurt = Mod_ReadBE32(src + 0x14);
            dst->delay[0] = Mod_ReadBE16(src + 0x18);
            dst->delay[1] = Mod_ReadBE16(src + 0x1A);
        }
    }
}

void ApplyActorGroups() {
    auto lists = Mod_LoadTable("romhack/actor_groups");
    auto table = Mod_LoadTable("romhack/actor_groups_table");
    if (lists == nullptr || table == nullptr) {
        SPDLOG_ERROR("TTYD64: missing actor group tables");
        return;
    }
    const size_t listSize = lists->Data.size();
    const size_t tableCount = table->Data.size() / 4;
    if (listSize > kActorGroupDataCapacity || tableCount == 0) {
        SPDLOG_ERROR("TTYD64: actor group tables have an unexpected size");
        return;
    }

    uint32_t base = UINT32_MAX;
    size_t groupCount = 0;
    for (; groupCount < tableCount; groupCount++) {
        const uint32_t ptr = (uint32_t) Mod_ReadBE32(Record(table, 4, groupCount));
        if (ptr == 0) {
            break;
        }
        base = std::min<uint32_t>(base, ptr);
    }

    u8* groups[kActorTypesListsCapacity + 1] = {};
    size_t used = 0;
    for (size_t i = 0; i < groupCount; i++) {
        const size_t offset = (uint32_t) Mod_ReadBE32(Record(table, 4, i)) - base;
        size_t len = 0;
        while (offset + len < listSize && Record(lists, 1, offset + len)[0] != kActorTypeListEnd) {
            len++;
        }
        if (offset + len >= listSize) {
            SPDLOG_ERROR("TTYD64: actor group {} is not terminated", i);
            return;
        }
        if (len < 2) {
            continue;
        }
        if (used == kActorTypesListsCapacity) {
            SPDLOG_ERROR("TTYD64: too many actor groups");
            return;
        }
        groups[used++] = &sActorGroupData[offset];
    }

    std::memcpy(sActorGroupData, lists->Data.data(), listSize);
    for (size_t i = 0; i <= kActorTypesListsCapacity; i++) {
        ActorTypesLists[i] = groups[i];
    }
    SPDLOG_INFO("TTYD64: applied {} actor groups ({} with several members)", groupCount, used);
}

void ApplyPartnerSpawnHeights() {
    bPartnerDmaTable[PARTNER_PARAKARRY].y = 4;
    bPartnerDmaTable[PARTNER_WATT].y = 11;
    bPartnerDmaTable[PARTNER_LAKILESTER].y = 4;
    bPartnerDmaTable[PARTNER_BOW].y = 9;
}

} // namespace

extern "C" void TTYD64_ApplyDataTables(void) {
    ApplyMoves();
    ApplyItems();
    ApplyActorTypes();
    ApplyActorGroups();
    ApplyPartnerSpawnHeights();
}
