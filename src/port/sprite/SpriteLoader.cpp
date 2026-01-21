// Include libultraship headers FIRST to avoid macro conflicts with game code
#include <cstdio>
#include <cstring>
#include <libultraship.h>
#include <ship/resource/type/Blob.h>
#include <ship/utils/binarytools/endianness.h>
#include <spdlog/spdlog.h>

#include "SpriteLoader.h"

// Forward declaration of ResourceGetDataByName from Engine
extern "C" void* ResourceGetDataByName(const char* name);

// Global flag indicating sprites are loaded from assets
static SpriteS32 sSpritesAvailable = 0;

// Cache for sprite data header
static uint32_t sSpriteDataHeader[3] = {0};

// Asset path prefix for sprites
static const char* SPRITE_ASSET_PREFIX = "__OTR__sprites/npc/sprite_";

void Sprite_Init(void) {
    // Check if sprite assets exist by trying to load the header
    const char* headerPath = "__OTR__sprites/sprite_data_header";
    void* headerData = ResourceGetDataByName(headerPath);

    if (headerData != nullptr) {
        sSpritesAvailable = 1;
        // Copy header data and byte-swap (BLOB is raw big-endian bytes)
        uint32_t* src = (uint32_t*)headerData;
        sSpriteDataHeader[0] = BSWAP32(src[0]);
        sSpriteDataHeader[1] = BSWAP32(src[1]);
        sSpriteDataHeader[2] = BSWAP32(src[2]);
        SPDLOG_INFO("Sprite assets available, header loaded: [0x{:X}, 0x{:X}, 0x{:X}]",
                    sSpriteDataHeader[0], sSpriteDataHeader[1], sSpriteDataHeader[2]);
    } else {
        sSpritesAvailable = 0;
        SPDLOG_WARN("Sprite assets not available, will use ROM loading fallback");
    }
}

void Sprite_LoadHeader(void) {
    const char* headerPath = "__OTR__sprites/sprite_data_header";
    void* headerData = ResourceGetDataByName(headerPath);

    if (headerData != nullptr) {
        uint32_t* src = (uint32_t*)headerData;
        sSpriteDataHeader[0] = BSWAP32(src[0]);
        sSpriteDataHeader[1] = BSWAP32(src[1]);
        sSpriteDataHeader[2] = BSWAP32(src[2]);
    }
}

SpriteS32 Sprite_AssetsAvailable(void) {
    return sSpritesAvailable;
}

size_t Sprite_GetNPCSize(SpriteS32 spriteIdx) {
    // Build asset path: __OTR__sprites/npc/sprite_XXX
    char assetPath[64];
    snprintf(assetPath, sizeof(assetPath), "%s%03d", SPRITE_ASSET_PREFIX, spriteIdx);

    // Try to get size from resource manager
    auto ctx = Ship::Context::GetInstance();
    if (ctx == nullptr) {
        return 0;
    }

    auto resourceMgr = ctx->GetResourceManager();
    if (resourceMgr == nullptr) {
        return 0;
    }

    // Load resource to get size
    auto resource = resourceMgr->LoadResource(assetPath);
    if (resource == nullptr) {
        return 0;
    }

    // For blob resources, the size is stored in the data vector
    auto blob = std::dynamic_pointer_cast<Ship::Blob>(resource);
    if (blob != nullptr) {
        return blob->Data.size();
    }

    return 0;
}

void* Sprite_LoadNPC(SpriteS32 spriteIdx, void* destBuffer, size_t bufferSize) {
    if (destBuffer == nullptr || bufferSize == 0) {
        SPDLOG_ERROR("Sprite_LoadNPC: Invalid destination buffer");
        return nullptr;
    }

    // Build asset path: __OTR__sprites/npc/sprite_XXX
    char assetPath[64];
    snprintf(assetPath, sizeof(assetPath), "%s%03d", SPRITE_ASSET_PREFIX, spriteIdx);

    // Load sprite data from archive
    void* spriteData = ResourceGetDataByName(assetPath);

    if (spriteData == nullptr) {
        SPDLOG_WARN("Sprite_LoadNPC: Failed to load sprite {} from {}", spriteIdx, assetPath);
        return nullptr;
    }

    // Get the actual size of the sprite data
    size_t spriteSize = Sprite_GetNPCSize(spriteIdx);
    if (spriteSize == 0) {
        SPDLOG_WARN("Sprite_LoadNPC: Could not determine size for sprite {}", spriteIdx);
        return nullptr;
    }

    if (spriteSize > bufferSize) {
        SPDLOG_ERROR("Sprite_LoadNPC: Buffer too small for sprite {} (need {}, have {})",
                     spriteIdx, spriteSize, bufferSize);
        return nullptr;
    }

    // Copy sprite data to destination buffer
    // The data is already decompressed and byte-swapped
    memcpy(destBuffer, spriteData, spriteSize);

    SPDLOG_DEBUG("Sprite_LoadNPC: Loaded sprite {} ({} bytes)", spriteIdx, spriteSize);

    return destBuffer;
}

SpriteS32 Sprite_GetDataHeader(int32_t* outHeader) {
    if (outHeader == nullptr) {
        return 0;
    }

    // If we have cached header data, use it
    if (sSpritesAvailable && (sSpriteDataHeader[0] != 0 || sSpriteDataHeader[1] != 0 || sSpriteDataHeader[2] != 0)) {
        outHeader[0] = (int32_t)sSpriteDataHeader[0];
        outHeader[1] = (int32_t)sSpriteDataHeader[1];
        outHeader[2] = (int32_t)sSpriteDataHeader[2];
        return 1;
    }

    // Try to load from assets
    const char* headerPath = "__OTR__sprites/sprite_data_header";
    void* headerData = ResourceGetDataByName(headerPath);

    if (headerData == nullptr) {
        SPDLOG_WARN("Sprite_GetDataHeader: Failed to load sprite_data_header");
        return 0;
    }

    // Byte-swap from big-endian
    uint32_t* src = (uint32_t*)headerData;
    outHeader[0] = (int32_t)BSWAP32(src[0]);
    outHeader[1] = (int32_t)BSWAP32(src[1]);
    outHeader[2] = (int32_t)BSWAP32(src[2]);

    // Cache the values
    sSpriteDataHeader[0] = (uint32_t)outHeader[0];
    sSpriteDataHeader[1] = (uint32_t)outHeader[1];
    sSpriteDataHeader[2] = (uint32_t)outHeader[2];
    sSpritesAvailable = 1;

    SPDLOG_INFO("Sprite_GetDataHeader: Loaded [0x{:X}, 0x{:X}, 0x{:X}]",
                outHeader[0], outHeader[1], outHeader[2]);
    return 1;
}

SpriteS32 Sprite_GetPlayerRasterHeader(int32_t* outHeader) {
    if (outHeader == nullptr) {
        return 0;
    }

    const char* headerPath = "__OTR__sprites/player_raster_header";
    void* headerData = ResourceGetDataByName(headerPath);

    if (headerData == nullptr) {
        SPDLOG_WARN("Sprite_GetPlayerRasterHeader: Failed to load player_raster_header");
        return 0;
    }

    // PlayerRastersHeader is 3 x s32: indexRanges, loadDescriptors, imageData
    uint32_t* src = (uint32_t*)headerData;
    outHeader[0] = (int32_t)BSWAP32(src[0]);
    outHeader[1] = (int32_t)BSWAP32(src[1]);
    outHeader[2] = (int32_t)BSWAP32(src[2]);

    SPDLOG_INFO("Sprite_GetPlayerRasterHeader: Loaded [0x{:X}, 0x{:X}, 0x{:X}]",
                outHeader[0], outHeader[1], outHeader[2]);
    return 1;
}

SpriteS32 Sprite_GetPlayerRasterSets(int32_t* outSets, SpriteS32 maxCount) {
    if (outSets == nullptr || maxCount <= 0) {
        return 0;
    }

    const char* setsPath = "__OTR__sprites/player_raster_sets";
    void* setsData = ResourceGetDataByName(setsPath);

    if (setsData == nullptr) {
        SPDLOG_WARN("Sprite_GetPlayerRasterSets: Failed to load player_raster_sets");
        return 0;
    }

    // Get the blob to determine actual size
    auto ctx = Ship::Context::GetInstance();
    if (ctx == nullptr) {
        return 0;
    }

    auto resourceMgr = ctx->GetResourceManager();
    if (resourceMgr == nullptr) {
        return 0;
    }

    auto resource = resourceMgr->LoadResource(setsPath);
    if (resource == nullptr) {
        return 0;
    }

    auto blob = std::dynamic_pointer_cast<Ship::Blob>(resource);
    if (blob == nullptr) {
        return 0;
    }

    SpriteS32 count = (SpriteS32)(blob->Data.size() / sizeof(int32_t));
    if (count > maxCount) {
        count = maxCount;
    }

    // Byte-swap each entry
    uint32_t* src = (uint32_t*)setsData;
    for (SpriteS32 i = 0; i < count; i++) {
        outSets[i] = (int32_t)BSWAP32(src[i]);
    }

    SPDLOG_INFO("Sprite_GetPlayerRasterSets: Loaded {} entries", count);
    return count;
}

SpriteS32 Sprite_GetPlayerSpriteIndexEntry(SpriteS32 spriteIdx, int32_t* outEntry) {
    if (outEntry == nullptr) {
        return 0;
    }

    const char* indexPath = "__OTR__sprites/player_sprite_index";
    void* indexData = ResourceGetDataByName(indexPath);

    if (indexData == nullptr) {
        SPDLOG_WARN("Sprite_GetPlayerSpriteIndexEntry: Failed to load player_sprite_index");
        return 0;
    }

    // Index table is array of u32 offsets
    // Reading at idx gives offset[idx] and offset[idx+1] (start and end)
    uint32_t* src = (uint32_t*)indexData;
    outEntry[0] = (int32_t)BSWAP32(src[spriteIdx]);
    outEntry[1] = (int32_t)BSWAP32(src[spriteIdx + 1]);

    SPDLOG_INFO("Sprite_GetPlayerSpriteIndexEntry: sprite {} -> [0x{:X}, 0x{:X}]",
                spriteIdx, outEntry[0], outEntry[1]);
    return 1;
}

// Asset path prefix for player sprites
static const char* PLAYER_SPRITE_ASSET_PREFIX = "__OTR__sprites/player_sprite_";

// N64 format sprite structures (32-bit offsets)
// These match the binary layout in the asset blob
#pragma pack(push, 1)
struct N64_SpriteAnimData {
    uint32_t rastersOffset;
    uint32_t palettesOffset;
    int32_t maxComponents;
    int32_t colorVariations;
    // Followed by animListStart[] array of uint32_t, -1 terminated
};

struct N64_SpriteRasterCacheEntry {
    uint32_t imageOffset;
    uint8_t width;
    uint8_t height;
    int8_t palette;
    int8_t quadCacheIndex;
};

struct N64_SpriteAnimComponent {
    uint32_t cmdListOffset;
    int16_t cmdListSize;
    int16_t compOffsetX;
    int16_t compOffsetY;
    int16_t compOffsetZ;
};
#pragma pack(pop)

// Helper to count -1 terminated array of u32
static int CountN64PtrArray(const uint8_t* base, uint32_t offset) {
    const uint32_t* arr = reinterpret_cast<const uint32_t*>(base + offset);
    int count = 0;
    while (arr[count] != 0xFFFFFFFF) {
        count++;
        if (count > 1000) break; // Safety limit
    }
    return count;
}

// Convert N64 format sprite blob to native format with proper pointer sizes
// Returns the required buffer size, or 0 on error
// If destBuffer is provided and large enough, performs the conversion
static size_t ConvertN64SpriteToNative(const uint8_t* srcBlob, size_t srcSize,
                                        uint8_t* destBuffer, size_t destBufferSize,
                                        bool isPlayerSprite) {
    if (srcSize < sizeof(N64_SpriteAnimData)) {
        SPDLOG_ERROR("Sprite blob too small: {}", srcSize);
        return 0;
    }

    const N64_SpriteAnimData* n64Header = reinterpret_cast<const N64_SpriteAnimData*>(srcBlob);

    // Count entries in each array
    int numRasters = CountN64PtrArray(srcBlob, n64Header->rastersOffset);
    int numPalettes = CountN64PtrArray(srcBlob, n64Header->palettesOffset);

    // Count animations and components
    int numAnims = 0;
    int totalComponents = 0;
    const uint32_t* animOffsets = reinterpret_cast<const uint32_t*>(srcBlob + 0x10);
    while (animOffsets[numAnims] != 0xFFFFFFFF) {
        uint32_t animOffset = animOffsets[numAnims];
        if (animOffset < srcSize) {
            int numComps = CountN64PtrArray(srcBlob, animOffset);
            totalComponents += numComps;
        }
        numAnims++;
        if (numAnims > 1000) break;
    }

    SPDLOG_DEBUG("N64 sprite: {} rasters, {} palettes, {} anims, {} total components",
                 numRasters, numPalettes, numAnims, totalComponents);

    // Calculate size needed for native format
    // Native header: 2 pointers + 2 ints + animListStart array of pointers
    size_t headerSize = sizeof(void*) * 2 + sizeof(int32_t) * 2 + sizeof(void*) * (numAnims + 1);

    // Raster pointer array (pointers + terminator)
    size_t rasterArraySize = sizeof(void*) * (numRasters + 1);

    // Raster entries (each has a pointer field that expands)
    size_t rasterEntriesSize = sizeof(void*) * numRasters; // For expanded SpriteRasterCacheEntry
    // Actually, SpriteRasterCacheEntry is: pointer + 4 bytes = 8 + 4 = 12 bytes on 64-bit (with padding maybe 16)
    // On N64 it's 8 bytes. Let's use native struct size.
    // For now, keep the N64 raster entries as-is since image is an offset we convert to pointer

    // Palette pointer array
    size_t paletteArraySize = sizeof(void*) * (numPalettes + 1);

    // Component list arrays (one per animation)
    size_t compListArraysSize = 0;
    for (int i = 0; i < numAnims; i++) {
        uint32_t animOffset = animOffsets[i];
        if (animOffset < srcSize) {
            int numComps = CountN64PtrArray(srcBlob, animOffset);
            compListArraysSize += sizeof(void*) * (numComps + 1);
        }
    }

    // Component entries (each has a pointer field)
    // N64_SpriteAnimComponent is 12 bytes, native is larger due to pointer
    // Native: pointer(8) + s16(2) + Vec3s(6) = 16 bytes
    size_t compEntriesSize = 16 * totalComponents;

    // Raw data (images, palettes, command lists) - copy as-is
    // This is everything that's not a pointer array or struct with pointers
    // For simplicity, we'll copy the entire source blob and then overlay the converted structures

    // Total size estimate (generous)
    size_t totalSize = headerSize + rasterArraySize + paletteArraySize +
                       compListArraysSize + compEntriesSize + srcSize;

    // Round up to 16-byte alignment
    totalSize = (totalSize + 15) & ~15;

    if (destBuffer == nullptr) {
        // Just return size estimate
        return totalSize;
    }

    if (destBufferSize < totalSize) {
        SPDLOG_ERROR("Dest buffer too small: need {}, have {}", totalSize, destBufferSize);
        return 0;
    }

    // Now perform the actual conversion
    memset(destBuffer, 0, destBufferSize);

    // Layout in dest buffer:
    // [Native SpriteAnimData header with animListStart array]
    // [Raster pointer array]
    // [Palette pointer array]
    // [Component list arrays...]
    // [Component entries...]
    // [Raw data (images, palettes, commands)]

    uint8_t* writePtr = destBuffer;

    // 1. Write header
    void** headerPtr = reinterpret_cast<void**>(writePtr);
    size_t headerPtrCount = 2 + (numAnims + 1); // rastersOffset, palettesOffset, animListStart[]
    int32_t* headerIntPtr = reinterpret_cast<int32_t*>(writePtr + sizeof(void*) * 2);

    writePtr += sizeof(void*) * 2 + sizeof(int32_t) * 2 + sizeof(void*) * (numAnims + 1);

    // 2. Raster pointer array
    void** rasterArray = reinterpret_cast<void**>(writePtr);
    headerPtr[0] = rasterArray; // rastersOffset now points to raster array
    writePtr += rasterArraySize;

    // 3. Palette pointer array
    void** paletteArray = reinterpret_cast<void**>(writePtr);
    headerPtr[1] = paletteArray; // palettesOffset now points to palette array
    writePtr += paletteArraySize;

    // 4. Set scalar fields
    headerIntPtr[0] = n64Header->maxComponents;
    headerIntPtr[1] = n64Header->colorVariations;

    // 5. Allocate component list arrays and entries
    void*** animListStart = reinterpret_cast<void***>(reinterpret_cast<uint8_t*>(headerIntPtr) + sizeof(int32_t) * 2);

    // Track where to write component arrays and entries
    uint8_t* compListsPtr = writePtr;
    writePtr += compListArraysSize;
    uint8_t* compEntriesPtr = writePtr;
    writePtr += compEntriesSize;

    // 6. Copy raw data (everything from source blob)
    uint8_t* rawDataPtr = writePtr;
    memcpy(rawDataPtr, srcBlob, srcSize);

    // 7. Now fix up all the pointers

    // Raster array: convert offsets to pointers
    const uint32_t* n64RasterOffsets = reinterpret_cast<const uint32_t*>(srcBlob + n64Header->rastersOffset);
    for (int i = 0; i < numRasters; i++) {
        uint32_t offset = n64RasterOffsets[i];
        // Point to the raster entry in the raw data copy
        // The raster entry itself has an image offset we need to convert
        N64_SpriteRasterCacheEntry* n64Raster = reinterpret_cast<N64_SpriteRasterCacheEntry*>(rawDataPtr + offset);

        // For player sprites, image offset stays as offset (loaded from ROM at runtime)
        // For NPC sprites, convert image offset to pointer
        if (!isPlayerSprite) {
            // Convert image offset to pointer within raw data
            n64Raster->imageOffset = (uint32_t)(uintptr_t)(rawDataPtr + n64Raster->imageOffset);
        }

        rasterArray[i] = n64Raster;
    }
    rasterArray[numRasters] = reinterpret_cast<void*>(-1); // PTR_LIST_END

    // Palette array: convert offsets to pointers
    const uint32_t* n64PaletteOffsets = reinterpret_cast<const uint32_t*>(srcBlob + n64Header->palettesOffset);
    for (int i = 0; i < numPalettes; i++) {
        uint32_t offset = n64PaletteOffsets[i];
        paletteArray[i] = rawDataPtr + offset;
    }
    paletteArray[numPalettes] = reinterpret_cast<void*>(-1); // PTR_LIST_END

    // Animation lists: convert offsets to pointers
    uint8_t* currentCompListPtr = compListsPtr;
    uint8_t* currentCompEntryPtr = compEntriesPtr;

    for (int animIdx = 0; animIdx < numAnims; animIdx++) {
        uint32_t animOffset = animOffsets[animIdx];
        const uint32_t* n64CompOffsets = reinterpret_cast<const uint32_t*>(srcBlob + animOffset);
        int numComps = CountN64PtrArray(srcBlob, animOffset);

        // This animation's component pointer array
        void** compPtrArray = reinterpret_cast<void**>(currentCompListPtr);
        animListStart[animIdx] = compPtrArray;
        currentCompListPtr += sizeof(void*) * (numComps + 1);

        for (int compIdx = 0; compIdx < numComps; compIdx++) {
            uint32_t compOffset = n64CompOffsets[compIdx];
            const N64_SpriteAnimComponent* n64Comp = reinterpret_cast<const N64_SpriteAnimComponent*>(srcBlob + compOffset);

            // Create native component entry
            // Native layout: void* cmdList, s16 cmdListSize, Vec3s compOffset
            struct NativeComp {
                void* cmdList;
                int16_t cmdListSize;
                int16_t compOffsetX;
                int16_t compOffsetY;
                int16_t compOffsetZ;
            };
            NativeComp* nativeComp = reinterpret_cast<NativeComp*>(currentCompEntryPtr);
            nativeComp->cmdList = rawDataPtr + n64Comp->cmdListOffset;
            nativeComp->cmdListSize = n64Comp->cmdListSize;
            nativeComp->compOffsetX = n64Comp->compOffsetX;
            nativeComp->compOffsetY = n64Comp->compOffsetY;
            nativeComp->compOffsetZ = n64Comp->compOffsetZ;

            compPtrArray[compIdx] = nativeComp;
            currentCompEntryPtr += sizeof(NativeComp);
        }
        compPtrArray[numComps] = reinterpret_cast<void*>(-1); // PTR_LIST_END
    }
    animListStart[numAnims] = reinterpret_cast<void**>(-1); // PTR_LIST_END

    SPDLOG_INFO("Converted N64 sprite: {} bytes src -> {} bytes native",
                srcSize, totalSize);

    return totalSize;
}

// Get raw blob size (internal helper)
static size_t GetPlayerBlobSize(SpriteS32 spriteIdx) {
    char assetPath[64];
    snprintf(assetPath, sizeof(assetPath), "%s%d", PLAYER_SPRITE_ASSET_PREFIX, spriteIdx);

    auto ctx = Ship::Context::GetInstance();
    if (ctx == nullptr) {
        return 0;
    }

    auto resourceMgr = ctx->GetResourceManager();
    if (resourceMgr == nullptr) {
        return 0;
    }

    auto resource = resourceMgr->LoadResource(assetPath);
    if (resource == nullptr) {
        return 0;
    }

    auto blob = std::dynamic_pointer_cast<Ship::Blob>(resource);
    if (blob != nullptr) {
        return blob->Data.size();
    }

    return 0;
}

size_t Sprite_GetPlayerSize(SpriteS32 spriteIdx) {
    char assetPath[64];
    snprintf(assetPath, sizeof(assetPath), "%s%d", PLAYER_SPRITE_ASSET_PREFIX, spriteIdx);

    void* spriteData = ResourceGetDataByName(assetPath);
    if (spriteData == nullptr) {
        return 0;
    }

    size_t blobSize = GetPlayerBlobSize(spriteIdx);
    if (blobSize == 0) {
        return 0;
    }

    // Calculate native size needed (pass nullptr to just get size)
    size_t nativeSize = ConvertN64SpriteToNative(
        reinterpret_cast<const uint8_t*>(spriteData), blobSize,
        nullptr, 0, true /* isPlayerSprite */);

    SPDLOG_DEBUG("Sprite_GetPlayerSize: sprite {} blob={} native={}", spriteIdx, blobSize, nativeSize);
    return nativeSize;
}

void* Sprite_LoadPlayer(SpriteS32 spriteIdx, void* destBuffer, size_t bufferSize) {
    if (destBuffer == nullptr || bufferSize == 0) {
        SPDLOG_ERROR("Sprite_LoadPlayer: Invalid destination buffer");
        return nullptr;
    }

    char assetPath[64];
    snprintf(assetPath, sizeof(assetPath), "%s%d", PLAYER_SPRITE_ASSET_PREFIX, spriteIdx);

    void* spriteData = ResourceGetDataByName(assetPath);

    if (spriteData == nullptr) {
        SPDLOG_WARN("Sprite_LoadPlayer: Failed to load player sprite {} from {}", spriteIdx, assetPath);
        return nullptr;
    }

    size_t blobSize = GetPlayerBlobSize(spriteIdx);
    if (blobSize == 0) {
        SPDLOG_WARN("Sprite_LoadPlayer: Could not determine blob size for player sprite {}", spriteIdx);
        return nullptr;
    }

    // Convert N64 format to native format
    size_t convertedSize = ConvertN64SpriteToNative(
        reinterpret_cast<const uint8_t*>(spriteData), blobSize,
        reinterpret_cast<uint8_t*>(destBuffer), bufferSize,
        true /* isPlayerSprite */);

    if (convertedSize == 0) {
        SPDLOG_ERROR("Sprite_LoadPlayer: Failed to convert player sprite {}", spriteIdx);
        return nullptr;
    }

    SPDLOG_INFO("Sprite_LoadPlayer: Loaded player sprite {} ({} bytes native)", spriteIdx, convertedSize);

    return destBuffer;
}

SpriteS32 Sprite_GetPlayerRasterLoadDescriptors(SpriteS32 spriteIdx, SpriteS32 startIndex,
                                                 int32_t* outBuffer, SpriteS32 count) {
    if (outBuffer == nullptr || count <= 0) {
        return 0;
    }

    const char* descPath = "__OTR__sprites/player_raster_load_descriptors";
    void* descData = ResourceGetDataByName(descPath);

    if (descData == nullptr) {
        SPDLOG_WARN("Sprite_GetPlayerRasterLoadDescriptors: Failed to load player_raster_load_descriptors");
        return 0;
    }

    // Byte-swap each descriptor from big-endian
    uint32_t* src = (uint32_t*)descData;
    for (SpriteS32 i = 0; i < count; i++) {
        outBuffer[i] = (int32_t)BSWAP32(src[startIndex + i]);
    }

    SPDLOG_DEBUG("Sprite_GetPlayerRasterLoadDescriptors: Loaded {} descriptors starting at index {}",
                 count, startIndex);
    return 1;
}

SpriteS32 Sprite_LoadPlayerRaster(SpriteS32 rasterOffset, void* destBuffer, SpriteS32 size) {
    if (destBuffer == nullptr || size <= 0) {
        return 0;
    }

    const char* imagePath = "__OTR__sprites/player_raster_image_data";
    void* imageData = ResourceGetDataByName(imagePath);

    if (imageData == nullptr) {
        SPDLOG_WARN("Sprite_LoadPlayerRaster: Failed to load player_raster_image_data");
        return 0;
    }

    // Copy raster data (CI4 image data is byte-level, no byte-swap needed)
    uint8_t* src = (uint8_t*)imageData;
    memcpy(destBuffer, src + rasterOffset, size);

    SPDLOG_DEBUG("Sprite_LoadPlayerRaster: Loaded {} bytes at offset 0x{:X}", size, rasterOffset);
    return 1;
}
