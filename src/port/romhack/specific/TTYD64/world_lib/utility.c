#include "common.h"
#include "model.h"
#include "npc.h"
#include "port/Engine.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_rawmem.h"
#include "world_lib.h"
#include <math.h>
#include <string.h>

static u32 sFadeModelPrimColor;

b32 TTYD64_IsBadgeEquipped(s32 badgeID) {
    s32 i;

    for (i = 0; i <= 60; i++) {
        if (badgeID == gPlayerData.equippedBadges[i]) {
            return 1;
        }
    }
    return 0;
}

void TTYD64_DrawBox(s32 posX, s32 posY, s32 sizeX, s32 sizeY, s32 style, s32 opacity) {
    draw_box(
        0, (void*) (uintptr_t) style, posX, posY, 0, sizeX, sizeY, opacity, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, NULL, NULL,
        NULL, 0, 0, NULL
    );
}

API_CALLABLE(TTYD64_PlayerHasBadge) {
    Bytecode* args = script->ptrReadPos;
    s32 itemID = evt_get_variable(script, args[0]);
    Bytecode outVar = args[1];
    s32 found = 0;
    s32 i;

    for (i = 0; i < 128; i++) {
        if (itemID == gPlayerData.badges[i]) {
            found = 1;
            break;
        }
    }
    evt_set_variable(script, outVar, found);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_WorldLib_ReadEquippedBadgeAt) {
    Bytecode* args = script->ptrReadPos;
    u32 n64Addr = evt_get_variable(script, args[0]);

    evt_set_variable(script, args[1], (u16) gPlayerData.equippedBadges[(n64Addr - 0x8010F498) / 2]);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetModelPointer) {
    Bytecode* args = script->ptrReadPos;
    s32 modelID = evt_get_variable(script, args[0]);
    Model* model = get_model_from_list_index(get_model_list_index_from_tree_index(modelID));

    evt_set_variable(script, args[1], (Bytecode) model);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetActorPointer) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID = evt_get_variable(script, args[0]);

    if (actorID == (s32) ACTOR_SELF) {
        actorID = script->owner1.actorID;
    }
    evt_set_variable(script, args[1], (Bytecode) get_actor(actorID));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetActorPart) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID = evt_get_variable(script, args[0]);
    s32 partIndex = evt_get_variable(script, args[1]);
    Bytecode outVar = args[2];

    if (actorID == (s32) ACTOR_SELF) {
        actorID = script->owner1.actorID;
    }
    evt_set_variable(script, outVar, (Bytecode) get_actor_part(get_actor(actorID), partIndex));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetEnemyPointer) {
    Bytecode* args = script->ptrReadPos;
    s32 npcID = evt_get_variable(script, args[0]);

    if (npcID == NPC_SELF) {
        npcID = script->id;
    }
    evt_set_variable(script, args[1], (Bytecode) get_enemy(npcID));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetEntityPointer) {
    Bytecode* args = script->ptrReadPos;
    s32 entityID = evt_get_variable(script, args[0]);

    evt_set_variable(script, args[1], (Bytecode) get_entity_by_index(entityID));
    return ApiStatus_DONE2;
}

static void animate_texture_step(Evt* script, s32 i) {
    s32 v = (s32) ((u32) script->varTable[9 + i] + (u32) script->varTable[1 + i]);

    script->varTable[9 + i] = v;
    if (v < 0) {
        script->varTable[9 + i] = v + 0x20000;
    } else if (0x20000 < v) {
        script->varTable[9 + i] = v - 0x20000;
    }
}

static void animate_texture_apply(Evt* script) {
    s32 panner = script->varTable[0];

    set_main_pan_u(panner, script->varTable[9]);
    set_main_pan_v(panner, script->varTable[10]);
    set_aux_pan_u(panner, script->varTable[11]);
    set_aux_pan_v(panner, script->varTable[12]);
}

API_CALLABLE(TTYD64_Function_AnimateTexture) {
    s32 i;

    if (isInitialCall) {
        for (i = 0; i < 4; i++) {
            script->functionTemp[i] = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        if (script->functionTemp[i] == 0) {
            animate_texture_step(script, i);
        }
    }
    animate_texture_apply(script);
    for (i = 0; i < 4; i++) {
        script->functionTemp[i] = (s32) script->functionTemp[i] + 1;
    }
    for (i = 0; i < 4; i++) {
        if (!((s32) script->functionTemp[i] < (s32) script->varTable[5 + i])) {
            script->functionTemp[i] = 0;
        }
    }
    return ApiStatus_BLOCK;
}

API_CALLABLE(TTYD64_Func_AnimateTexture_DelayAll) {
    s32 i;

    for (i = 0; i < 4; i++) {
        animate_texture_step(script, i);
    }
    animate_texture_apply(script);
    return ApiStatus_BLOCK;
}

API_CALLABLE(TTYD64_SetNpcGroupBattleID) {
    Bytecode* args = script->ptrReadPos;
    s32 groupIndex = evt_get_variable(script, args[0]);
    s32 formationID = evt_get_variable(script, args[1]);

    gCurrentEncounter.encounterList[groupIndex]->battle = formationID;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_ConvertToInt) {
    Bytecode* args = script->ptrReadPos;
    u32 bits = evt_get_variable(script, args[0]);
    f32 f;

    memcpy(&f, &bits, sizeof(f));
    evt_set_variable(script, args[1], (s32) nearbyintf(f));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetFadeModelAlpha) {
    sFadeModelPrimColor = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

void TTYD64_Function_InitDisplayListCode(s32 index) {
    u32 opacity = sFadeModelPrimColor;

    gDPSetCombine(gMainGfxPos++, 0x121624, 0xFF2FFFFF);
    gDPSetPrimColor(
        gMainGfxPos++, 0, 0, (opacity >> 24) & 0xFF, (opacity >> 16) & 0xFF, (opacity >> 8) & 0xFF, opacity & 0xFF
    );
}
