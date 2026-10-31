#include "common.h"
#include "inventory.h"
#include "model.h"
#include "vars_access.h"
#include "npc.h"
#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/world/maps.h"

void TTYD64_maps_BindInlineMessage(Bytecode* script, const u8* msg) {
    const Bytecode id = Mod_RegisterInlineMessage("TTYD64", msg);
    Bytecode* cmd = script;

    while (true) {
        const Bytecode op = cmd[0];
        const Bytecode argc = cmd[1];

        for (Bytecode i = 0; i < argc; i++) {
            if (cmd[2 + i] == (Bytecode) msg) {
                cmd[2 + i] = id;
            }
        }
        if (op == EVT_OP_END) {
            break;
        }
        cmd += 2 + argc;
    }
}

API_CALLABLE(TTYD64_maps_AddKeyItem) {
    Bytecode* args = script->ptrReadPos;
    s32 value = *args++;
    PlayerData* playerData = &gPlayerData;
    s32 itemID = evt_get_variable(script, value);
    s32 i;

    if (itemID == ITEM_KOOPA_FORTRESS_KEY) {
        TTYD64_FortressKeys++;
        return ApiStatus_DONE2;
    }

    for (i = 0; i < ARRAY_COUNT(playerData->keyItems); i++) {
        if (playerData->keyItems[i] == ITEM_NONE) {
            break;
        }
    }

    if (i < ARRAY_COUNT(playerData->keyItems)) {
        playerData->keyItems[i] = itemID;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_maps_FindKeyItem) {
    Bytecode* args = script->ptrReadPos;
    s32 itemID = evt_get_variable(script, *args++);
    s32 value = *args++;
    PlayerData* playerData = &gPlayerData;
    s32 i;
    s32 itemIndex;

    for (i = 0; i < ARRAY_COUNT(playerData->keyItems); i++) {
        if (playerData->keyItems[i] == itemID) {
            break;
        }
    }

    itemIndex = -1;
    if (i != ARRAY_COUNT(playerData->keyItems)) {
        itemIndex = i;
    }

    evt_set_variable(script, value, itemIndex);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_maps_AddBadge) {
    Bytecode* args = script->ptrReadPos;
    s32 badgeID = evt_get_variable(script, *args++);
    Bytecode outBadgeIdx = *args++;

    evt_set_variable(script, outBadgeIdx, add_item(badgeID));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_maps_RemoveBadge) {
    Bytecode* args = script->ptrReadPos;
    s32 badge = evt_get_variable(script, *args++);
    s32 i;
    s32 j;

    for (i = 0; i < ARRAY_COUNT(gPlayerData.badges); i++) {
        if ((u16) gPlayerData.badges[i] == badge) {
            gPlayerData.badges[i] = ITEM_NONE;
            for (j = 0; j < ARRAY_COUNT(gPlayerData.equippedBadges); j++) {
                if ((u16) gPlayerData.equippedBadges[j] == badge) {
                    gPlayerData.equippedBadges[j] = ITEM_NONE;
                    break;
                }
            }
            break;
        }
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_maps_WriteModBytesBE16) {
    Bytecode* args = script->ptrReadPos;
    s32 addr = evt_get_variable(script, *args++);
    s32 value = evt_get_variable(script, *args++);

    TTYD64_WriteBE(TTYD64_ModBytes(), addr - 0x80356000, 2, value);
    return ApiStatus_DONE2;
}

static void TTYD64_maps_foliage_setup_shear_mtx(Matrix4f mtx, f32 scale, f32 xAmount, f32 zAmount) {
    guMtxIdentF(mtx);
    mtx[1][0] = scale * xAmount;
    mtx[1][1] = 1.0f;
    mtx[1][2] = scale * zAmount;
}

API_CALLABLE(TTYD64_maps_TransformFoliage) {
    Bytecode* args = script->ptrReadPos;
    s32 modelListIndex = get_model_list_index_from_tree_index(evt_get_variable(script, *args++));
    f32 scale = evt_get_float_variable(script, *args++);
    f32 dx = evt_get_float_variable(script, *args++);
    f32 dy = evt_get_float_variable(script, *args++);
    f32 dz = evt_get_float_variable(script, *args++);
    Model* model = get_model_from_list_index(modelListIndex);
    Matrix4f mtx;

    if (!(model->flags & MODEL_FLAG_HAS_TRANSFORM)) {
        guTranslateF(model->userTransformMtx, 0.0f, dy, 0.0f);
        TTYD64_maps_foliage_setup_shear_mtx(mtx, scale, dx, dz);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        guTranslateF(mtx, 0.0f, -dy, 0.0f);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        model->flags |= (MODEL_FLAG_HAS_TRANSFORM | MODEL_FLAG_MATRIX_DIRTY);
    } else {
        guTranslateF(mtx, 0.0f, dy, 0.0f);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        TTYD64_maps_foliage_setup_shear_mtx(mtx, scale, dx, dz);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        guTranslateF(mtx, 0.0f, -dy, 0.0f);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
    }

    return ApiStatus_DONE2;
}

static void TTYD64_maps_stretch_mtx(Matrix4f mtx, f32 amount) {
    guMtxIdentF(mtx);
    mtx[1][2] = 0.0f;
    mtx[1][1] = 1.0f;
    mtx[1][0] = (f32) ((f64) amount * 0.09);
}

API_CALLABLE(TTYD64_maps_StretchModel) {
    Bytecode* args = script->ptrReadPos;
    s32 modelListIndex = get_model_list_index_from_tree_index(evt_get_variable(script, *args++));
    f32 amount = evt_get_float_variable(script, *args++);
    Model* model = get_model_from_list_index(modelListIndex);
    Matrix4f mtx;

    if (!(model->flags & MODEL_FLAG_HAS_TRANSFORM)) {
        TTYD64_maps_stretch_mtx(model->userTransformMtx, amount);
        model->flags |= (MODEL_FLAG_HAS_TRANSFORM | MODEL_FLAG_MATRIX_DIRTY);
    } else {
        TTYD64_maps_stretch_mtx(mtx, amount);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
    }
    return ApiStatus_DONE2;
}

static void TTYD64_maps_on_quizmo_spawn_check(IEvent* event) {
    if (strcmp(gAreas[gGameStatusPtr->areaID].maps[gGameStatusPtr->mapID].id, "mac_04") == 0) {
        event->Cancelled = true;
    }
}

void TTYD64_maps_InstallCommon(void) {
    REGISTER_LISTENER(OnQuizmoSpawnCheck, EVENT_PRIORITY_NORMAL, TTYD64_maps_on_quizmo_spawn_check);
}
