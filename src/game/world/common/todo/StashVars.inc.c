#include "common.h"
#include "npc.h"

static s32 N(varStashStorage)[16];
static s32 N(varStashActive) = false;

API_CALLABLE(N(StashVars)) {
    s32 i;

    if (!N(varStashActive)) {
        for (i = 0; i < ARRAY_COUNT(script->varTable); i++) {
            N(varStashStorage)[i] = script->varTable[i];
        }
        N(varStashActive) = true;
    } else {
        for (i = 0; i < ARRAY_COUNT(script->varTable); i++) {
            script->varTable[i] = N(varStashStorage)[i];
        }
        N(varStashActive) = false;
    }

    return ApiStatus_DONE2;
}
