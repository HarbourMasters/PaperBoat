#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

#include "common.h"
#include "evt.h"
#include "npc.h"
#include "port/patches/Patches.h"

extern "C" {

// Read a pointer-sized element from a host-pointer array into an EVT variable.
//
// EVT's BufRead1 reads s32 (4 bytes) per entry, which truncates host pointers
// on 64-bit builds. Scripts that walk a `T*[]` table with
// `UseBuf(Ref(arr)) / Loop / BufRead1(LVarX) / UseBuf(LVarX)` end up using a
// half-pointer as the next buffer base and crash on the first read.
//
// Bytecode is intptr_t, so storing the resolved pointer through
// evt_set_variable preserves the full address. Subsequent UseBuf(LVarX) reads
// it back as a real pointer.
//
// args: arrayPtr (Ref to T*[]), index, count (ARRAY_COUNT), outVar.
// index is wrapped into [0, count) so callers don't have to. Count is required
// because EVT can't compute ARRAY_COUNT itself.
API_CALLABLE(LoadPtrFromArray) {
    Bytecode* args = script->ptrReadPos;

    void** array = (void**) evt_get_variable(script, *args++);
    s32 index = evt_get_variable(script, *args++);
    s32 count = evt_get_variable(script, *args++);
    Bytecode outVar = *args++;

    if (count <= 0) {
        count = 1;
    }
    s32 i = index % count;
    if (i < 0) {
        i += count;
    }

    evt_set_variable(script, outVar, (Bytecode) (intptr_t) array[i]);

    return ApiStatus_DONE2;
}

// Replaces EVT's UseBuf+BufRead, which reads with s32 stride and so splits the
// 8-byte script pointers on 64-bit (NULL source -> crash in find_script_labels).
//
// Buffer entries: (npcID, scriptPtr) | (-2, frames) for a wait | -1 for end.
// args: bufPtr, iterVarId, outWaitVarId. Binds until a wait (outWait=frames) or
// end (outWait=-1); caller does the Wait in EVT.
API_CALLABLE(StepTaggedAIWaveBuf) {
    Bytecode* args = script->ptrReadPos;
    Bytecode bufArg = *args++;
    Bytecode iterVar = *args++;
    Bytecode outWaitVar = *args++;
    intptr_t* buf = (intptr_t*) evt_get_variable(script, bufArg);
    s32 i = evt_get_variable(script, iterVar);

    while (true) {
        intptr_t entry = buf[i];

        if (entry == -1) {
            evt_set_variable(script, iterVar, i);
            evt_set_variable(script, outWaitVar, -1);
            return ApiStatus_DONE2;
        }
        if (entry == -2) {
            s32 frames = (s32) buf[i + 1];
            evt_set_variable(script, iterVar, i + 2);
            evt_set_variable(script, outWaitVar, frames);
            return ApiStatus_DONE2;
        }

        s32 npcID = (s32) entry;
        EvtScript* aiSrc = (EvtScript*) buf[i + 1];
        Enemy* enemy = get_enemy(npcID);
        s32 groupFlags = (enemy->flags & ENEMY_FLAG_PASSIVE) ? EVT_GROUP_PASSIVE_NPC : EVT_GROUP_HOSTILE_NPC;

        if (enemy->aiScript != NULL) {
            kill_script_by_ID(enemy->aiScriptID);
        }
        enemy->unk_C8 = 100;
        enemy->aiBytecode = aiSrc;
        Evt* aiScript = start_script(aiSrc, EVT_PRIORITY_A, 0);
        enemy->aiScript = aiScript;
        enemy->aiScriptID = aiScript->id;
        aiScript->owner1.enemy = enemy;
        aiScript->owner2.npcID = npcID;
        aiScript->groupFlags = groupFlags;

        i += 2;
    }
}

API_CALLABLE(DisableLoadingZoneInput) {
    if (!CVarGetInteger(CVAR_ENHANCEMENT("PreventLoadingZoneStorage"), 0)) {
        return ApiStatus_DONE2;
    }

    return DisablePlayerInput(script, isInitialCall);
}
}
