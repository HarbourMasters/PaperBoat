#include "shape_loader.h"
#include <string.h>
#include <stdio.h>

extern void GameEngine_LogInfo(const char* fmt, ...);
extern void* ResourceGetDataByName(const char* name);

// Current shape name for display list path building
static const char* gCurrentShapeName = NULL;

// Bump allocator — native structs (ModelNode, ModelGroupData, etc.) are placed
// in shapeFile->data, which is a persistent global buffer. This avoids the
// game's general_heap entirely (it gets recreated during map load, invalidating
// pointers).
static u8* sArenaBase = NULL;
static size_t sArenaPos = 0;
static size_t sArenaSize = 0;

static void shape_arena_init(u8* base, size_t size) {
    sArenaBase = base;
    sArenaPos = 0;
    sArenaSize = size;
}

static void* shape_alloc(size_t size) {
    size = (size + 15) & ~15; // align to 16 bytes
    if (sArenaPos + size > sArenaSize) {
        GameEngine_LogInfo("[Shape] Arena exhausted! pos=%zu, need=%zu, limit=%zu", sArenaPos, size, sArenaSize);
        return NULL;
    }
    void* ptr = sArenaBase + sArenaPos;
    sArenaPos += size;
    return ptr;
}

// Forward declarations for recursive conversion
static ModelNode* ConvertModelNode(u8* base, u32 offset);
static ModelGroupData* ConvertModelGroupData(u8* base, u32 offset);

static Gfx* LoadDisplayListByOffset(u32 dlOffset) {
    if (dlOffset == 0 || gCurrentShapeName == NULL) {
        return NULL;
    }

    char path[128];
    snprintf(path, sizeof(path), "__OTR__shapes/%s/dlist_%X", gCurrentShapeName, dlOffset);

    Gfx* dl = (Gfx*) ResourceGetDataByName(path);
    if (dl == NULL) {
        GameEngine_LogInfo("[Shape] WARNING: Could not load display list from %s", path);
    }
    return dl;
}

static ModelDisplayData* ConvertModelDisplayData(u8* base, u32 offset) {
    if (offset == 0)
        return NULL;

    RawModelDisplayData* raw = (RawModelDisplayData*) (base + offset);
    if (raw->displayListOffset == 0)
        return NULL;

    ModelDisplayData* native = shape_alloc(sizeof(ModelDisplayData));
    native->displayList = LoadDisplayListByOffset(raw->displayListOffset);
    memcpy(native->unk_04, &raw->unk_04, 4);
    return native;
}

static ModelNodeProperty* ConvertModelNodeProperties(u8* base, u32 offset, s32 numProperties) {
    if (offset == 0 || numProperties <= 0)
        return NULL;

    ModelNodeProperty* native = shape_alloc(sizeof(ModelNodeProperty) * numProperties);
    RawModelNodeProperty* raw = (RawModelNodeProperty*) (base + offset);

    for (s32 i = 0; i < numProperties; i++) {
        native[i].key = raw[i].key;
        native[i].dataType = raw[i].dataType;

        if (raw[i].key == MODEL_PROP_KEY_TEXTURE_NAME) {
            native[i].data.p = Shape_OffsetToPtr(base, raw[i].data);
        } else {
            native[i].data.s = raw[i].data;
        }
    }
    return native;
}

static ModelGroupData* ConvertModelGroupData(u8* base, u32 offset) {
    if (offset == 0)
        return NULL;

    RawModelGroupData* raw = (RawModelGroupData*) (base + offset);

    ModelGroupData* native = shape_alloc(sizeof(ModelGroupData));
    native->transformMatrix = (Mtx*) Shape_OffsetToPtr(base, raw->transformMatrixOffset);
    native->lightingGroup = (Lightsn*) Shape_OffsetToPtr(base, raw->lightingGroupOffset);
    native->numLights = raw->numLights;
    native->numChildren = raw->numChildren;

    if (raw->childListOffset && raw->numChildren > 0) {
        native->childList = shape_alloc(sizeof(ModelNode*) * raw->numChildren);
        u32* rawChildOffsets = (u32*) (base + raw->childListOffset);
        for (s32 i = 0; i < raw->numChildren; i++) {
            native->childList[i] = ConvertModelNode(base, rawChildOffsets[i]);
        }
    } else {
        native->childList = NULL;
    }
    return native;
}

static ModelNode* ConvertModelNode(u8* base, u32 offset) {
    if (offset == 0)
        return NULL;

    RawModelNode* raw = (RawModelNode*) (base + offset);

    ModelNode* native = shape_alloc(sizeof(ModelNode));
    native->type = raw->type;
    native->displayData = ConvertModelDisplayData(base, raw->displayDataOffset);
    native->numProperties = raw->numProperties;
    native->propertyList = ConvertModelNodeProperties(base, raw->propertyListOffset, raw->numProperties);
    native->groupData = ConvertModelGroupData(base, raw->groupDataOffset);
    return native;
}

static char** ConvertNameTable(u8* base, u32 offset) {
    if (offset == 0)
        return NULL;

    // Name tables are terminated by an entry pointing to the string "db"
    u32* rawOffsets = (u32*) (base + offset);
    s32 count = 0;
    while (rawOffsets[count] != 0) {
        char* str = (char*) (base + rawOffsets[count]);
        if (str[0] == 'd' && str[1] == 'b' && str[2] == '\0')
            break;
        count++;
    }
    if (count == 0)
        return NULL;

    char** native = shape_alloc(sizeof(char*) * (count + 1));
    for (s32 i = 0; i < count; i++) {
        native[i] = (char*) (base + rawOffsets[i]);
    }
    native[count] = NULL;
    return native;
}

void Shape_LoadFromRawData(ShapeFile* shapeFile, const u8* rawData, size_t rawSize, const char* shapeName) {
    if (rawData == NULL || rawSize == 0) {
        shapeFile->header.root = NULL;
        shapeFile->header.vertexTable = NULL;
        shapeFile->header.modelNames = NULL;
        shapeFile->header.colliderNames = NULL;
        shapeFile->header.zoneNames = NULL;
        return;
    }

    (void) rawSize;
    u8* base = (u8*) rawData;
    RawShapeFileHeader* rawHeader = (RawShapeFileHeader*) base;

    shape_arena_init(shapeFile->data, sizeof(shapeFile->data));

    gCurrentShapeName = shapeName;

    shapeFile->header.root = ConvertModelNode(base, rawHeader->rootOffset);
    shapeFile->header.vertexTable = (Vtx_t*) Shape_OffsetToPtr(base, rawHeader->vertexTableOffset);
    shapeFile->header.modelNames = ConvertNameTable(base, rawHeader->modelNamesOffset);
    shapeFile->header.colliderNames = ConvertNameTable(base, rawHeader->colliderNamesOffset);
    shapeFile->header.zoneNames = ConvertNameTable(base, rawHeader->zoneNamesOffset);

    gCurrentShapeName = NULL;
}
