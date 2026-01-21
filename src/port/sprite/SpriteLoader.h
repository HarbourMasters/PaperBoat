#ifndef SPRITE_LOADER_H
#define SPRITE_LOADER_H

#include <stdint.h>
#include <stddef.h>

// Use stdint types to avoid pulling in game macros that conflict with imgui
typedef int32_t SpriteS32;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the sprite loading system.
 * Called during game boot to set up sprite data header offsets.
 */
void Sprite_Init(void);

/**
 * Load a pre-processed NPC sprite by index.
 * The sprite data is already decompressed and byte-swapped at extraction time.
 *
 * @param spriteIdx The NPC sprite index (0-233 for standard NPC sprites)
 * @param destBuffer Buffer to copy sprite data into (allocated by caller)
 * @param bufferSize Size of destination buffer
 * @return Pointer to sprite data in destBuffer, or NULL on failure
 */
void* Sprite_LoadNPC(SpriteS32 spriteIdx, void* destBuffer, size_t bufferSize);

/**
 * Get the size of an NPC sprite's decompressed data.
 *
 * @param spriteIdx The NPC sprite index
 * @return Size in bytes, or 0 if sprite not found
 */
size_t Sprite_GetNPCSize(SpriteS32 spriteIdx);

/**
 * Load sprite data header containing base offsets.
 * This populates the global SpriteDataHeader used by sprite loading code.
 */
void Sprite_LoadHeader(void);

/**
 * Check if sprite assets are available (extracted from ROM).
 *
 * @return 1 if sprites are available, 0 otherwise
 */
SpriteS32 Sprite_AssetsAvailable(void);

/**
 * Get the sprite data header.
 * Returns pointer to array of 3 uint32 offsets (byte-swapped from big-endian).
 * Values are raw offsets, caller should add SPRITE_ROM_START.
 *
 * @param outHeader Pointer to array of 3 s32 to receive header values
 * @return 1 on success, 0 on failure
 */
SpriteS32 Sprite_GetDataHeader(int32_t* outHeader);

/**
 * Load player raster header structure.
 *
 * @param outHeader Pointer to receive header data (3 x s32: indexRanges, loadDescriptors, imageData)
 * @return 1 on success, 0 on failure
 */
SpriteS32 Sprite_GetPlayerRasterHeader(int32_t* outHeader);

/**
 * Load player sprite raster sets (index table).
 *
 * @param outSets Pointer to array to receive raster set indices
 * @param maxCount Maximum number of entries to load
 * @return Number of entries loaded, or 0 on failure
 */
SpriteS32 Sprite_GetPlayerRasterSets(int32_t* outSets, SpriteS32 maxCount);

/**
 * Get player sprite index entry (offset pair for a specific sprite).
 * Reads from the pre-extracted player_sprite_index asset.
 *
 * @param spriteIdx Player sprite index (0-13, where 1-13 are valid sprites)
 * @param outEntry Pointer to array of 2 int32_t to receive [startOffset, endOffset]
 * @return 1 on success, 0 on failure
 */
SpriteS32 Sprite_GetPlayerSpriteIndexEntry(SpriteS32 spriteIdx, int32_t* outEntry);

/**
 * Get the size of a player sprite's pre-processed data.
 *
 * @param spriteIdx Player sprite index (0-13)
 * @return Size in bytes, or 0 if sprite not found
 */
size_t Sprite_GetPlayerSize(SpriteS32 spriteIdx);

/**
 * Load a pre-processed player sprite by index.
 * The sprite data is already decompressed and byte-swapped at extraction time.
 *
 * @param spriteIdx Player sprite index (0-13)
 * @param destBuffer Buffer to copy sprite data into (allocated by caller)
 * @param bufferSize Size of destination buffer
 * @return Pointer to sprite data in destBuffer, or NULL on failure
 */
void* Sprite_LoadPlayer(SpriteS32 spriteIdx, void* destBuffer, size_t bufferSize);

/**
 * Load player raster load descriptors for a specific sprite.
 * Each descriptor is a u32 containing packed size/offset for loading raster images.
 *
 * @param spriteIdx Player sprite index
 * @param startIndex Starting index in the global descriptor table (from PlayerSpriteRasterSets)
 * @param outBuffer Buffer to receive descriptors (should be at least count * 4 bytes)
 * @param count Number of descriptors to load
 * @return 1 on success, 0 on failure
 */
SpriteS32 Sprite_GetPlayerRasterLoadDescriptors(SpriteS32 spriteIdx, SpriteS32 startIndex,
                                                 int32_t* outBuffer, SpriteS32 count);

/**
 * Load a player raster image by its descriptor info.
 * Uses the pre-extracted raster image data blob.
 *
 * @param rasterOffset Offset into raster image data (lower 20 bits of descriptor)
 * @param destBuffer Buffer to receive raster data
 * @param size Size of raster data to load (upper 12 bits of descriptor, already multiplied)
 * @return 1 on success, 0 on failure
 */
SpriteS32 Sprite_LoadPlayerRaster(SpriteS32 rasterOffset, void* destBuffer, SpriteS32 size);

#ifdef __cplusplus
}
#endif

#endif // SPRITE_LOADER_H
