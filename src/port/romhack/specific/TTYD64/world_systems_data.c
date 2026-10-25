#include "port/romhack/specific/TTYD64/world_systems_internal.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"

char TTYD64_ASCII_Buffer[16] = { 0x20 };
u8 TTYD64_Data_Shop_ExtraData[16] __attribute__((aligned(8)));
TTYD64FFWDState TTYD64_FFWD;
