#include "common.h"
#include "model.h"
#include "port/Engine.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_flags.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/world/world_lib.h"

extern s32 world_lakilester_AbilityState;
extern s32 world_watt_AbilityState;

API_CALLABLE(TTYD64_TestPlayerFlags) {
    Bytecode* args = script->ptrReadPos;
    s32 mask = evt_get_variable(script, *args++);

    evt_set_variable(script, *args++, (gPlayerStatus.flags & mask) != 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_TestPlayerAnimFlags) {
    Bytecode* args = script->ptrReadPos;
    s32 mask = evt_get_variable(script, *args++);

    evt_set_variable(script, *args++, (gPlayerStatus.animFlags & mask) != 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetPlayerAnimFlagBits) {
    Bytecode* args = script->ptrReadPos;
    s32 mask = evt_get_variable(script, *args++);
    s32 enable = evt_get_variable(script, *args++);

    if (enable) {
        gPlayerStatus.animFlags |= mask;
    } else {
        gPlayerStatus.animFlags &= ~mask;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetPlayerColliderDiameter) {
    gPlayerStatus.colliderDiameter = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_DisarmChestEntity) {
    Entity* entity = (Entity*) evt_get_variable(script, *script->ptrReadPos);

    if (entity != NULL) {
        entity->updateScriptCallback = NULL;
        entity->flags &= ~ENTITY_FLAG_SHOWS_INSPECT_PROMPT;
    }
    return ApiStatus_DONE2;
}

static s32* partner_ability_state(s32 partnerID) {
    switch (partnerID) {
        case PARTNER_LAKILESTER:
            return &world_lakilester_AbilityState;
        case PARTNER_WATT:
            return &world_watt_AbilityState;
        default:
            return NULL;
    }
}

API_CALLABLE(TTYD64_GetPartnerAbilityState) {
    Bytecode* args = script->ptrReadPos;
    s32* state = partner_ability_state(evt_get_variable(script, *args++));

    evt_set_variable(script, *args++, state != NULL ? *state : 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetPartnerAbilityState) {
    Bytecode* args = script->ptrReadPos;
    s32* state = partner_ability_state(evt_get_variable(script, *args++));
    s32 value = evt_get_variable(script, *args++);

    if (state != NULL) {
        *state = value;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetScreenOverlayFront) {
    Bytecode* args = script->ptrReadPos;
    s32 type = evt_get_variable(script, *args++);
    f32 progress = evt_get_float_variable(script, *args++);

    set_screen_overlay_params_front(type, progress);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetScreenOverlayFrontProgress) {
    u8 type;
    f32 progress;

    get_screen_overlay_params(SCREEN_LAYER_FRONT, &type, &progress);
    evt_set_float_variable(script, *script->ptrReadPos, progress);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetScreenOverlayColor) {
    Bytecode* args = script->ptrReadPos;
    s32 layer = evt_get_variable(script, *args++);
    s32 r = evt_get_variable(script, *args++);
    s32 g = evt_get_variable(script, *args++);
    s32 b = evt_get_variable(script, *args++);

    set_screen_overlay_color(layer, r, g, b);
    return ApiStatus_DONE2;
}

static s32 model_translation_int(Model* model, s32 axis) {
    s32 word = ((s32*) &model->savedMtx)[6 + axis / 2];

    return (s16) ((axis & 1) ? word : word >> 16);
}

API_CALLABLE(TTYD64_GetModelBaseTranslation) {
    Bytecode* args = script->ptrReadPos;
    Model* model = (Model*) evt_get_variable(script, *args++);
    s32 i;

    for (i = 0; i < 3; i++) {
        evt_set_variable(script, *args++, model != NULL ? model_translation_int(model, i) : 0);
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetFountainCoins) {
    evt_set_variable(script, *script->ptrReadPos, TTYD64_ModBytes()[TTYD64_MB_GB_HOS25_FountainCoins]);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetMoleHighScore) {
    evt_set_variable(
        script, *script->ptrReadPos, (s32) TTYD64_ReadBE(TTYD64_ModBytes(), TTYD64_MB_GB_KMR32_Highscore1, 4)
    );
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetMoleHighScore) {
    TTYD64_WriteBE(TTYD64_ModBytes(), TTYD64_MB_GB_KMR32_Highscore1, 4, evt_get_variable(script, *script->ptrReadPos));
    return ApiStatus_DONE2;
}
