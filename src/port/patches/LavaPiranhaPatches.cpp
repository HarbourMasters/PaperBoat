#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

// Port-side replacement for the lava piranha vine DMA loader.
//
// Exposes host BSS buffers as VINE_*_BASE identity tokens, records the
// compiled-in C-symbol script for each LoadAnimationFromTable call per vine,
// and translates VINE_*_BASE back to that script pointer inside
// play_model_animation / play_model_animation_starting_from.

#include "common.h"
#include "animation_script.h"

extern "C" {

// 37 compiled-in lava piranha animation scripts at src/world/model_anim/kzn/XX.c.
extern s16 LavaPiranha_ModelScript_00[];
extern s16 LavaPiranha_ModelScript_01[];
extern s16 LavaPiranha_ModelScript_02[];
extern s16 LavaPiranha_ModelScript_03[];
extern s16 LavaPiranha_ModelScript_04[];
extern s16 LavaPiranha_ModelScript_05[];
extern s16 LavaPiranha_ModelScript_06[];
extern s16 LavaPiranha_ModelScript_07[];
extern s16 LavaPiranha_ModelScript_08[];
extern s16 LavaPiranha_ModelScript_09[];
extern s16 LavaPiranha_ModelScript_0A[];
extern s16 LavaPiranha_ModelScript_0B[];
extern s16 LavaPiranha_ModelScript_0C[];
extern s16 LavaPiranha_ModelScript_0D[];
extern s16 LavaPiranha_ModelScript_0E[];
extern s16 LavaPiranha_ModelScript_0F[];
extern s16 LavaPiranha_ModelScript_10[];
extern s16 LavaPiranha_ModelScript_11[];
extern s16 LavaPiranha_ModelScript_12[];
extern s16 LavaPiranha_ModelScript_13[];
extern s16 LavaPiranha_ModelScript_14[];
extern s16 LavaPiranha_ModelScript_15[];
extern s16 LavaPiranha_ModelScript_16[];
extern s16 LavaPiranha_ModelScript_17[];
extern s16 LavaPiranha_ModelScript_18[];
extern s16 LavaPiranha_ModelScript_19[];
extern s16 LavaPiranha_ModelScript_1A[];
extern s16 LavaPiranha_ModelScript_1B[];
extern s16 LavaPiranha_ModelScript_1C[];
extern s16 LavaPiranha_ModelScript_1D[];
extern s16 LavaPiranha_ModelScript_1E[];
extern s16 LavaPiranha_ModelScript_1F[];
extern s16 LavaPiranha_ModelScript_20[];
extern s16 LavaPiranha_ModelScript_21[];
extern s16 LavaPiranha_ModelScript_22[];
extern s16 LavaPiranha_ModelScript_23[];
extern s16 LavaPiranha_ModelScript_24[];

static s16* const PortLavaPiranhaScripts[37] = {
    LavaPiranha_ModelScript_00, LavaPiranha_ModelScript_01, LavaPiranha_ModelScript_02, LavaPiranha_ModelScript_03,
    LavaPiranha_ModelScript_04, LavaPiranha_ModelScript_05, LavaPiranha_ModelScript_06, LavaPiranha_ModelScript_07,
    LavaPiranha_ModelScript_08, LavaPiranha_ModelScript_09, LavaPiranha_ModelScript_0A, LavaPiranha_ModelScript_0B,
    LavaPiranha_ModelScript_0C, LavaPiranha_ModelScript_0D, LavaPiranha_ModelScript_0E, LavaPiranha_ModelScript_0F,
    LavaPiranha_ModelScript_10, LavaPiranha_ModelScript_11, LavaPiranha_ModelScript_12, LavaPiranha_ModelScript_13,
    LavaPiranha_ModelScript_14, LavaPiranha_ModelScript_15, LavaPiranha_ModelScript_16, LavaPiranha_ModelScript_17,
    LavaPiranha_ModelScript_18, LavaPiranha_ModelScript_19, LavaPiranha_ModelScript_1A, LavaPiranha_ModelScript_1B,
    LavaPiranha_ModelScript_1C, LavaPiranha_ModelScript_1D, LavaPiranha_ModelScript_1E, LavaPiranha_ModelScript_1F,
    LavaPiranha_ModelScript_20, LavaPiranha_ModelScript_21, LavaPiranha_ModelScript_22, LavaPiranha_ModelScript_23,
    LavaPiranha_ModelScript_24,
};

// Identity buffers used as VINE_*_BASE in EVT scripts
u8 PortLavaPiranhaVineBase[4][16];
static s16* PortLavaPiranhaCurrentScript[4];

void port_lava_piranha_set_script(s32 vine, s32 index) {
    if ((u32) vine >= 4 || (u32) index >= 37) {
        return;
    }
    PortLavaPiranhaCurrentScript[vine] = PortLavaPiranhaScripts[index];
}

s16* port_lava_piranha_translate(s16* addr) {
    for (s32 i = 0; i < 4; i++) {
        if (addr == (s16*) PortLavaPiranhaVineBase[i]) {
            return PortLavaPiranhaCurrentScript[i];
        }
    }
    return addr;
}

}
