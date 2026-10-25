#include "common.h"
#include "inventory.h"
#include "model.h"
#include "npc.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "script_api/macros.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/world/nm.h"

#define TTYD64_NM_ROCKS_TABLE_SIZE 0x80
#define TTYD64_NM_ROCKS_TABLE_END  0x0123

extern EvtScript TTYD64_isk_20_Script_KillFlames;
extern EvtScript TTYD64_kpa_136_Script_KillFlames;
extern s32 TTYD64_omo_19_IntTable_Models_Carousel_1[];
extern s32 TTYD64_omo_19_IntTable_Models_Carousel_2[];
extern s32 TTYD64_omo_19_IntTable_Models_Carousel_3[];
extern s32 TTYD64_omo_19_IntTable_Colliders_Carousel_1[];
extern s32 TTYD64_omo_19_IntTable_Colliders_Carousel_2[];
extern s32 TTYD64_omo_19_IntTable_Colliders_Carousel_3[];

void TTYD64_nm_BindMessage(Bytecode* script, const u8* msg) {
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

API_CALLABLE(TTYD64_nm_AddKeyItem) {
    Bytecode* args = script->ptrReadPos;
    Bytecode value = *args++;
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

API_CALLABLE(TTYD64_nm_AddBadge) {
    Bytecode* args = script->ptrReadPos;
    s32 badgeID = evt_get_variable(script, *args++);
    Bytecode outBadgeIdx = *args++;

    evt_set_variable(script, outBadgeIdx, add_item(badgeID));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_nm_GetVarFromVar) {
    Bytecode* args = script->ptrReadPos;
    Bytecode var = evt_get_variable(script, args[0]);

    evt_set_variable(script, args[1], evt_get_variable(script, var));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_nm_ToggleBool) {
    Bytecode* args = script->ptrReadPos;
    s32 value = evt_get_variable(script, args[0]);

    evt_set_variable(script, args[0], value == 0 ? 1 : 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_nm_TableWordRead) {
    Bytecode* args = script->ptrReadPos;
    Bytecode* table = (Bytecode*) evt_get_variable(script, args[0]);
    s32 offset = evt_get_variable(script, args[1]);

    evt_set_variable(script, args[2], table[offset / 4]);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_nm_ArrayWordRead) {
    Bytecode* args = script->ptrReadPos;
    Bytecode ptr = evt_get_variable(script, args[0]);
    Bytecode base = evt_get_variable(script, args[1]);

    evt_set_variable(script, args[2], ((Bytecode*) base)[(ptr - base) / 4]);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_nm_ArrayWordWrite) {
    Bytecode* args = script->ptrReadPos;
    Bytecode ptr = evt_get_variable(script, args[0]);
    Bytecode base = evt_get_variable(script, args[1]);

    ((Bytecode*) base)[(ptr - base) / 4] = evt_get_variable(script, args[2]);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_nm_kpa_138_GetFXPos) {
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);
    Vec3i pos = { 0, 0, 0 };

    if (index >= 0 && index < ARRAY_COUNT(TTYD64_kpa_138_Data_FXPosTable)) {
        pos = TTYD64_kpa_138_Data_FXPosTable[index];
    }
    evt_set_variable(script, *args++, pos.x);
    evt_set_variable(script, *args++, pos.y);
    evt_set_variable(script, *args++, pos.z);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_nm_jan_25_UpdateRockPosInTable) {
    Bytecode* args = script->ptrReadPos;
    s32 modelID = evt_get_variable(script, args[0]);
    s32 horizontal = evt_get_variable(script, args[1]);
    s32 downLeft = evt_get_variable(script, args[2]);
    u8* table = TTYD64_Data_RocksPositionTable;
    s32 pos = 0;
    s32 next;
    s32 result = 0;

    while (true) {
        s32 cell = (s16) TTYD64_ReadBE(table, pos, 2);

        if (cell == TTYD64_NM_ROCKS_TABLE_END) {
            pos = -1;
            break;
        }
        if (cell == modelID) {
            break;
        }
        pos += 2;
    }

    if (pos >= 0) {
        if (horizontal != 0) {
            next = downLeft != 0 ? pos - 2 : pos + 2;
        } else {
            next = downLeft != 0 ? pos + 0x12 : pos - 0x12;
        }
        if (next >= 0 && next + 2 <= TTYD64_NM_ROCKS_TABLE_SIZE && (s16) TTYD64_ReadBE(table, next, 2) == 0) {
            TTYD64_WriteBE(table, next, 2, modelID);
            TTYD64_WriteBE(table, pos, 2, 0);
            result = 1;
        }
    }

    evt_set_variable(script, args[3], result);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_nm_jan_25_RestereRocksTable) {
    s32 pos = 0;

    while (pos + 2 <= TTYD64_NM_ROCKS_TABLE_SIZE) {
        u32 cell = TTYD64_ReadBE(TTYD64_Data_RocksPositionTable_Original, pos, 2);

        TTYD64_WriteBE(TTYD64_Data_RocksPositionTable, pos, 2, cell);
        if (cell == TTYD64_NM_ROCKS_TABLE_END) {
            break;
        }
        pos += 2;
    }
    return ApiStatus_DONE2;
}

static void TTYD64_nm_FlameAI(FireBarData* data, s32 mode, EvtScript* killScript) {
    switch (mode) {
        case 0:
            if (data->flags & 2) {
                data->rotRate *= 0.95f;
            }
            break;
        case 1:
            data->rotRate *= 1.12f;
            if (data->soundIndex == 10) {
                Evt* script = start_script(killScript, EVT_PRIORITY_1, 0);
                script->varTable[0] = data->firstNpc;
                script->varTable[1] = data->npcCount;
                data->flags |= 2;
            }
            break;
        case 2:
            data->rotRate = abs(data->settings->rotRate) * signF(-data->rotRate);
            break;
    }
}

void TTYD64_nm_isk_20_FlameAI(FireBarData* data, s32 mode) {
    TTYD64_nm_FlameAI(data, mode, &TTYD64_isk_20_Script_KillFlames);
}

void TTYD64_nm_kpa_136_FlameAI(FireBarData* data, s32 mode) {
    TTYD64_nm_FlameAI(data, mode, &TTYD64_kpa_136_Script_KillFlames);
}

typedef struct TTYD64_nm_RotatingPlatform {
    /* 0x00 */ Vec3f relativePos;
    /* 0x0C */ Vec3f lastRelativePos;
    /* 0x18 */ Matrix4f transformMatrix;
} TTYD64_nm_RotatingPlatform;

static ApiStatus TTYD64_nm_UpdateRotatingPlatforms(
    Evt* script,
    b32 isInitialCall,
    s32* platformModels,
    s32* platformColliders,
    s32 axisModelID,
    s32 ringModelID,
    s32 ringColliderID
) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Matrix4f sp20, sp60, spA0, spE0;
    Npc* partner = get_npc_unsafe(NPC_PARTNER);
    Model* axisModel = get_model_from_list_index(get_model_list_index_from_tree_index(axisModelID));
    Model* ringModel = get_model_from_list_index(get_model_list_index_from_tree_index(ringModelID));
    f32 ox, oy, oz;
    Model* loopModel;
    f32 x, y, z;
    TTYD64_nm_RotatingPlatform* it;
    u32 isPounding;
    u32 i;
    s32 j, k;

    if (isInitialCall) {
        sfx_play_sound_at_position(SOUND_LOOP_OMO_ROTATING_WHEEL, SOUND_SPACE_DEFAULT, 315.0f, 125.0f, -100.0f);
        script->functionTempPtr[0] = it = heap_malloc(sizeof(*it) * 6);
        script->functionTemp[1] = 0;

        for (i = 0; i < 6; it++, i += 2) {
            loopModel = get_model_from_list_index(get_model_list_index_from_tree_index(platformModels[i]));

            it->relativePos.x = x = loopModel->center.x - axisModel->center.x;
            it->relativePos.y = y = loopModel->center.y - axisModel->center.y;
            it->relativePos.z = z = loopModel->center.z - axisModel->center.z;

            ox = x;
            oy = y;
            oz = z;

            for (j = 0; j < 4; j++) {
                for (k = 0; k < 4; k++) {
                    it->transformMatrix[j][k] = loopModel->userTransformMtx[j][k];
                }
            }

            it++;
            loopModel = get_model_from_list_index(get_model_list_index_from_tree_index(platformModels[i + 1]));

            it->relativePos.x = ox;
            it->relativePos.y = oy;
            it->relativePos.z = oz;

            for (j = 0; j < 4; j++) {
                for (k = 0; k < 4; k++) {
                    it->transformMatrix[j][k] = loopModel->userTransformMtx[j][k];
                }
            }
        }
    }

    it = script->functionTempPtr[0];
    for (i = 0; i < 6; i++, it++) {
        loopModel = get_model_from_list_index(get_model_list_index_from_tree_index(platformModels[i]));

        for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
                loopModel->userTransformMtx[j][k] = it->transformMatrix[j][k];
            }
        }

        loopModel->flags |= MODEL_FLAG_MATRIX_DIRTY | MODEL_FLAG_HAS_TRANSFORM;
        guTranslateF(sp20, it->relativePos.x, it->relativePos.y, it->relativePos.z);
        guRotateF(spA0, script->functionTemp[1], 0.0f, 0.0f, 1.0f);
        guTranslateF(sp60, -it->relativePos.x, -it->relativePos.y, -it->relativePos.z);
        guRotateF(spE0, -script->functionTemp[1], 0.0f, 0.0f, 1.0f);
        guMtxCatF(sp20, spA0, spA0);
        guMtxCatF(spA0, sp60, sp60);
        guMtxCatF(spE0, sp60, sp60);
        guMtxCatF(loopModel->userTransformMtx, sp60, loopModel->userTransformMtx);
        update_collider_transform(platformColliders[i]);
        guMtxXFMF(loopModel->userTransformMtx, 0.0f, 0.0f, 0.0f, &ox, &oy, &oz);
        if (gCollisionStatus.curFloor == platformColliders[i]
            || gCollisionStatus.lastTouchedFloor == platformColliders[i])
        {
            playerStatus->pushVel.x = ox - it->lastRelativePos.x;
            playerStatus->pushVel.y = oy - it->lastRelativePos.y;
            playerStatus->pushVel.z = oz - it->lastRelativePos.z;
        }
        if (partner->curFloor == platformColliders[i]) {
            partner->pos.x += ox - it->lastRelativePos.x;
            partner->pos.y += oy - it->lastRelativePos.y;
            partner->pos.z += oz - it->lastRelativePos.z;
        }
        it->lastRelativePos.x = ox;
        it->lastRelativePos.y = oy;
        it->lastRelativePos.z = oz;
    }

    guRotateF(axisModel->userTransformMtx, script->functionTemp[1], 0.0f, 0.0f, 1.0f);
    axisModel->flags |= MODEL_FLAG_MATRIX_DIRTY | MODEL_FLAG_HAS_TRANSFORM;
    update_collider_transform(0x32);

    guRotateF(ringModel->userTransformMtx, script->functionTemp[1], 0.0f, 0.0f, 1.0f);
    ringModel->flags |= MODEL_FLAG_MATRIX_DIRTY | MODEL_FLAG_HAS_TRANSFORM;
    update_collider_transform(ringColliderID);

    isPounding = false;
    for (i = 0; i < 6; i++) {
        if (gCollisionStatus.curFloor == platformColliders[i]) {
            if (playerStatus->flags & PS_FLAG_NO_STATIC_COLLISION) {
                gCameras[CAM_DEFAULT].targetPos.x = playerStatus->pos.x;
                gCameras[CAM_DEFAULT].targetPos.y = playerStatus->pos.y;
                gCameras[CAM_DEFAULT].targetPos.z = playerStatus->pos.z;
            }
            if (playerStatus->actionState == ACTION_STATE_SPIN_POUND
                || playerStatus->actionState == ACTION_STATE_TORNADO_POUND)
            {
                isPounding = true;
            }
        }
    }
    if (!isPounding) {
        script->functionTemp[1]--;
    }

    return ApiStatus_BLOCK;
}

API_CALLABLE(TTYD64_nm_omo_19_UpdateRotatingPlatforms_Movement_1) {
    return TTYD64_nm_UpdateRotatingPlatforms(
        script, isInitialCall, TTYD64_omo_19_IntTable_Models_Carousel_1, TTYD64_omo_19_IntTable_Colliders_Carousel_1,
        0x4A, 0x3F, 0x17
    );
}

API_CALLABLE(TTYD64_nm_omo_19_UpdateRotatingPlatforms_Movement_2) {
    return TTYD64_nm_UpdateRotatingPlatforms(
        script, isInitialCall, TTYD64_omo_19_IntTable_Models_Carousel_2, TTYD64_omo_19_IntTable_Colliders_Carousel_2,
        0x5C, 0x51, 0x29
    );
}

API_CALLABLE(TTYD64_nm_omo_19_UpdateRotatingPlatforms_Movement_3) {
    return TTYD64_nm_UpdateRotatingPlatforms(
        script, isInitialCall, TTYD64_omo_19_IntTable_Models_Carousel_3, TTYD64_omo_19_IntTable_Colliders_Carousel_3,
        0x6A, 0x5F, 0x37
    );
}
