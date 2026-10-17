#include "common.h"
#include "npc.h"
#include "port/Engine.h"
#include "../include/ttyd64_api.h"
#include "world_lib.h"

API_CALLABLE(TTYD64_Function_AnimateTexture);
API_CALLABLE(TTYD64_Func_AnimateTexture_DelayAll);

API_CALLABLE(TTYD64_Pipe_SetAnimFlag) {
    gPlayerStatusPtr->animFlags |= PA_FLAG_CHANGING_MAP;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Pipe_GetCurrentFloor) {
    script->varTable[0] = gCollisionStatus.curFloor;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Pipe_CheckDownInput) {
    CollisionStatus* collisionStatus = &gCollisionStatus;
    s32 stickX;
    s32 stickY;

    if (collisionStatus->curFloor != script->varTable[11]) {
        script->varTable[0] = false;
        return ApiStatus_DONE2;
    }

    stickX = abs(gGameStatusPtr->stickX[0]);
    stickY = gGameStatusPtr->stickY[0];

    if (stickX != 0 || stickY != 0) {
        if (atan2(0.0f, 0.0f, stickX, stickY) < 60.0f) {
            script->varTable[0] = true;
            return ApiStatus_DONE2;
        }
    }

    return ApiStatus_BLOCK;
}

API_CALLABLE(TTYD64_Pipe_GetEntryCoords) {
    MapSettings* mapSettings = get_current_map_settings();
    s32 index = evt_get_variable(script, LVar0);

    evt_set_variable(script, LVar1, ((Vec4f*) *mapSettings->entryList)[index].x);
    evt_set_variable(script, LVar2, ((Vec4f*) *mapSettings->entryList)[index].y);
    evt_set_variable(script, LVar3, ((Vec4f*) *mapSettings->entryList)[index].z);
    evt_set_variable(script, LVar4, ((Vec4f*) *mapSettings->entryList)[index].yaw);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Pipe_GetCameraYaw) {
    script->varTable[0] = clamp_angle(gCameras[gCurrentCameraID].curYaw + 180.0f);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Pipe_GetPointInFrontOfPlayer) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 r = evt_get_float_variable(script, *script->ptrReadPos);
    f32 x = playerStatus->pos.x;
    f32 y = playerStatus->pos.y;
    f32 z = playerStatus->pos.z;

    add_vec2D_polar(&x, &z, r, playerStatus->targetYaw);
    evt_set_float_variable(script, LVar0, x);
    evt_set_float_variable(script, LVar1, y);
    evt_set_float_variable(script, LVar2, z);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_TexturePan_Simple) {
    return TTYD64_Func_AnimateTexture_DelayAll(script, isInitialCall);
}

API_CALLABLE(TTYD64_TexturePan_Complex) {
    return TTYD64_Function_AnimateTexture(script, isInitialCall);
}
