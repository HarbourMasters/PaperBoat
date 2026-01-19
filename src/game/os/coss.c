#include "ultra64.h"

s16 sins(u16 x);

s16 coss(u16 angle) {
    return sins(angle + 0x4000);
}
