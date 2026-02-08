#include "common.h"

#ifdef SHIFT
BSS u8 WorldEntityHeapBottom[WORLD_ENTITY_HEAP_SIZE];
#endif
BSS u8 WorldEntityHeapBase[0x10];
BSS u8 heap_collisionHead[COLLISION_HEAP_SIZE];

// CRITICAL FIX: heap_battleHead must be large enough to hold BATTLE_HEAP_SIZE bytes.
// Previously defined in undefined_symbols.c as HeapNode (only 24 bytes), causing memory corruption!
BSS u8 heap_battleHead[BATTLE_HEAP_SIZE];
