#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

#include "common.h"
#include "map.h"
#include "model.h"

extern "C" {

extern MapSettings gMapSettings;

// The the backdrop layers in end_00/end_01 parade are 1500-unit walls
// whose contents repeat every 750 units, and the ground is 750-unit tiles.
// On wider aspects each listed model is redrawn shifted by `stepX`, `count` times.
#define BACKDROP_WIDTH    1500.0f
#define GROUND_TILE_WIDTH 750.0f
#define ROAD_STRIP_WIDTH  3750.0f

#define FIRST_CUSTOM_GFX_SLOT CUSTOM_GFX_4
#define NUM_CUSTOM_GFX_SLOTS  16

typedef struct ParadeCopy {
    const char* modelName;
    f32 stepX;
    s32 count;
} ParadeCopy;

typedef struct ParadeMap {
    const char* mapName;
    const ParadeCopy* copies;
    s32 numCopies;
} ParadeMap;

static const ParadeCopy sEnd00Copies[] = {
    { "sky", -BACKDROP_WIDTH, 1 },   { "sky", BACKDROP_WIDTH, 1 },       { "cloud", -BACKDROP_WIDTH, 1 },
    { "cloud", BACKDROP_WIDTH, 1 },  { "mountain", -BACKDROP_WIDTH, 1 }, { "mountain", BACKDROP_WIDTH, 1 },
    { "j1", -GROUND_TILE_WIDTH, 2 }, { "j3", -GROUND_TILE_WIDTH, 2 },    { "j3_b", -GROUND_TILE_WIDTH, 2 },
    { "j2", -ROAD_STRIP_WIDTH, 1 },  { "j25", GROUND_TILE_WIDTH, 2 },    { "o226", GROUND_TILE_WIDTH, 2 },
    { "j27", GROUND_TILE_WIDTH, 2 },
};

static const ParadeCopy sEnd01Copies[] = {
    { "sky", -BACKDROP_WIDTH, 1 },     { "sky", BACKDROP_WIDTH, 1 },      { "mountain", -BACKDROP_WIDTH, 1 },
    { "mountain", BACKDROP_WIDTH, 1 }, { "o145", -GROUND_TILE_WIDTH, 2 }, { "o146", -GROUND_TILE_WIDTH, 2 },
    { "j2", -GROUND_TILE_WIDTH, 2 },
};

static const ParadeMap sParadeMaps[] = {
    { "end_00", sEnd00Copies, ARRAY_COUNT(sEnd00Copies) },
    { "end_01", sEnd01Copies, ARRAY_COUNT(sEnd01Copies) },
};

typedef struct ParadeSlot {
    Model* model;
    const ParadeCopy* copies[4];
    s32 numCopies;
} ParadeSlot;

static ParadeSlot sSlots[NUM_CUSTOM_GFX_SLOTS];

static s32 find_model_tree_index(const char* name) {
    char** names = gMapSettings.modelNameList;
    s32 i;

    if (names == NULL) {
        return -1;
    }
    for (i = 0; names[i] != NULL; i++) {
        if (strcmp(names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

static void parade_append_copy(Gfx* dl, f32 dx) {
    Matrix4f mtx;
    Mtx* dispMtx = &gDisplayContext->matrixStack[gMatrixListPos++];

    guTranslateF(mtx, dx, 0.0f, 0.0f);
    guMtxF2L(mtx, dispMtx);
    gSPMatrix(gMainGfxPos++, dispMtx, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(gMainGfxPos++, dl);
    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
}

static void parade_build_copies(s32 index) {
    ParadeSlot* slot;
    Gfx* dl;
    s32 i, j;

    if (index < 0 || index >= NUM_CUSTOM_GFX_SLOTS || GameEngine_GetAspectRatio() <= 4.0f / 3.0f) {
        return;
    }
    slot = &sSlots[index];
    if (slot->model == NULL || slot->model->modelNode->displayData == NULL) {
        return;
    }

    dl = slot->model->modelNode->displayData->displayList;
    for (i = 0; i < slot->numCopies; i++) {
        for (j = 1; j <= slot->copies[i]->count; j++) {
            parade_append_copy(dl, slot->copies[i]->stepX * j);
        }
    }
}

static ParadeSlot* claim_slot(Model* model, s32* nextSlot) {
    s32 i;

    for (i = FIRST_CUSTOM_GFX_SLOT; i < *nextSlot; i++) {
        if (sSlots[i].model == model) {
            return &sSlots[i];
        }
    }
    if (*nextSlot >= NUM_CUSTOM_GFX_SLOTS) {
        return NULL;
    }

    i = (*nextSlot)++;
    sSlots[i].model = model;
    sSlots[i].numCopies = 0;
    set_mdl_custom_gfx_set(model, i, ENV_TINT_UNCHANGED);
    model->flags |= MODEL_FLAG_USES_CUSTOM_GFX;
    set_custom_gfx_builders(i, nullptr, parade_build_copies);
    return &sSlots[i];
}

static void setup_parade_copies(const ParadeMap* map) {
    s32 nextSlot = FIRST_CUSTOM_GFX_SLOT;
    s32 i;

    for (i = 0; i < map->numCopies; i++) {
        const ParadeCopy* copy = &map->copies[i];
        s32 treeIndex = find_model_tree_index(copy->modelName);
        Model* model;
        ParadeSlot* slot;

        if (treeIndex < 0) {
            continue;
        }
        model = get_model_from_list_index(get_model_list_index_from_tree_index(treeIndex));
        if (model == NULL || model->modelNode == NULL) {
            continue;
        }
        slot = claim_slot(model, &nextSlot);
        if (slot != NULL && slot->numCopies < (s32) ARRAY_COUNT(slot->copies)) {
            slot->copies[slot->numCopies++] = copy;
        }
    }
}

static void RegisterParadeBackdropPatches_Init() {
    REGISTER_LISTENER(OnMapReady, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        const char* mapName = ((OnMapReady*) event)->mapName;
        u32 i;

        memset(sSlots, 0, sizeof(sSlots));
        if (mapName == nullptr) {
            return;
        }
        for (i = 0; i < ARRAY_COUNT(sParadeMaps); i++) {
            if (strcmp(mapName, sParadeMaps[i].mapName) == 0) {
                setup_parade_copies(&sParadeMaps[i]);
                return;
            }
        }
    });
}
} // extern "C"

static RegisterShipInitFunc initFunc(RegisterParadeBackdropPatches_Init);
