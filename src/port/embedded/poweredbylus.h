#pragma once

// "powered by libultraship" logo, drawn beneath the Nintendo 64 logo on the
// boot logo screen (see state_logos.c).

#include "common.h"

#define POWERED_BY_LUS_WIDTH  96
#define POWERED_BY_LUS_HEIGHT 32

// Rows uploaded per gDPLoadTextureTile call: 96 texels * 16 rows * 2 bytes =
// 3072 bytes, within the 4KB TMEM budget.
#define POWERED_BY_LUS_TILE_ROWS 16

// Position in logo-screen coordinates
#define POWERED_BY_LUS_X 112
#define POWERED_BY_LUS_Y 181

extern u8 gPoweredByLusLogo[POWERED_BY_LUS_WIDTH * POWERED_BY_LUS_HEIGHT * 2];
