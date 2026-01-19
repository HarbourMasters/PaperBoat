#include "common.h"
#include "variables.h"

// Symbols normally assigned by the ROM linker script (ver/*/undefined_syms.txt).
// Define only the ones we need on PC so far.
BackgroundHeader gBackgroundImage = { 0 };

u64 gspF3DZEX2_NoN_PosLight_fifoTextStart[1] = { 0 };
u64 gspF3DZEX2_NoN_PosLight_fifoDataStart[1] = { 0 };

u64* nuGfxUcodeFifoPtr = NULL;
s32 nuGfxUcodeFifoSize = 0;

HeapNode heap_battleHead = { 0 };

// Obfuscated symbols - not needed for PC port (C code compiles directly)
s32 obfuscated_battle_heap_create[1] = { 0 };
u8 obfuscated_general_heap_create[1] = { 0 };
u8 obfuscated_load_engine_data[1] = { 0 };
u8 obfuscated_create_audio_system[1] = { 0 };

s8 obfuscated_obfuscation_shims_VRAM[1] = { 0 };
s8 obfuscated_obfuscation_shims_ROM_START[1] = { 0 };

u8 sprite_shading_profiles_data_ROM_START[1] = { 0 };