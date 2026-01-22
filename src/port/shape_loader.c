#include "shape_loader.h"
#include "gcc/string.h"
#include <stdio.h>

// Forward declarations for recursive conversion
static ModelNode* ConvertModelNode(u8* base, u32 offset);
static ModelGroupData* ConvertModelGroupData(u8* base, u32 offset);

static ModelDisplayData* ConvertModelDisplayData(u8* base, u32 offset) {
    if (offset == 0) return NULL;

    RawModelDisplayData* raw = (RawModelDisplayData*)(base + offset);

    // ModelDisplayData can be used directly since it only has a Gfx* which we
    // convert to offset-based, and unk_04. We allocate a native structure.
    ModelDisplayData* native = general_heap_malloc(sizeof(ModelDisplayData));
    native->displayList = (Gfx*)Shape_OffsetToPtr(base, raw->displayListOffset);
    // Note: displayList is also an offset, but Gfx display lists are handled
    // differently by the graphics system - they stay as raw data
    native->displayList = (Gfx*)(base + raw->displayListOffset);
    // Copy other fields (unk_04 is raw bytes)
    memcpy(native->unk_04, &raw->unk_04, 4);

    return native;
}

static ModelNodeProperty* ConvertModelNodeProperties(u8* base, u32 offset, s32 numProperties) {
    if (offset == 0 || numProperties <= 0) return NULL;

    ModelNodeProperty* native = general_heap_malloc(sizeof(ModelNodeProperty) * numProperties);
    RawModelNodeProperty* raw = (RawModelNodeProperty*)(base + offset);

    for (s32 i = 0; i < numProperties; i++) {
        native[i].key = raw[i].key;
        native[i].dataType = raw[i].dataType;

        // Convert offset to pointer for properties that contain pointers
        if (raw[i].key == MODEL_PROP_KEY_TEXTURE_NAME) {
            // Texture name is a string pointer - convert offset to actual pointer
            native[i].data.p = Shape_OffsetToPtr(base, raw[i].data);
        } else {
            // Other properties store scalar values
            native[i].data.s = raw[i].data;
        }
    }

    return native;
}

static ModelGroupData* ConvertModelGroupData(u8* base, u32 offset) {
    if (offset == 0) return NULL;

    RawModelGroupData* raw = (RawModelGroupData*)(base + offset);

    ModelGroupData* native = general_heap_malloc(sizeof(ModelGroupData));
    native->transformMatrix = (Mtx*)Shape_OffsetToPtr(base, raw->transformMatrixOffset);
    native->lightingGroup = (Lightsn*)Shape_OffsetToPtr(base, raw->lightingGroupOffset);
    native->numLights = raw->numLights;
    native->numChildren = raw->numChildren;

    // Convert child list - array of ModelNode pointers
    if (raw->childListOffset && raw->numChildren > 0) {
        native->childList = general_heap_malloc(sizeof(ModelNode*) * raw->numChildren);
        u32* rawChildOffsets = (u32*)(base + raw->childListOffset);
        for (s32 i = 0; i < raw->numChildren; i++) {
            native->childList[i] = ConvertModelNode(base, rawChildOffsets[i]);
        }
    } else {
        native->childList = NULL;
    }

    return native;
}

static ModelNode* ConvertModelNode(u8* base, u32 offset) {
    if (offset == 0) return NULL;

    RawModelNode* raw = (RawModelNode*)(base + offset);

    ModelNode* native = general_heap_malloc(sizeof(ModelNode));
    native->type = raw->type;
    native->displayData = ConvertModelDisplayData(base, raw->displayDataOffset);
    native->numProperties = raw->numProperties;
    native->propertyList = ConvertModelNodeProperties(base, raw->propertyListOffset, raw->numProperties);
    native->groupData = ConvertModelGroupData(base, raw->groupDataOffset);

    return native;
}

static char** ConvertNameTable(u8* base, u32 offset) {
    if (offset == 0) return NULL;

    // Count names first (null-terminated array of offsets)
    u32* rawOffsets = (u32*)(base + offset);
    s32 count = 0;
    while (rawOffsets[count] != 0) {
        count++;
    }

    if (count == 0) return NULL;

    // Allocate and populate native pointer array
    char** native = general_heap_malloc(sizeof(char*) * (count + 1));
    for (s32 i = 0; i < count; i++) {
        native[i] = (char*)(base + rawOffsets[i]);
    }
    native[count] = NULL; // null terminator

    return native;
}

void Shape_LoadFromRawData(ShapeFile* shapeFile, const u8* rawData, size_t rawSize) {
    if (rawData == NULL || rawSize == 0) {
        shapeFile->header.root = NULL;
        shapeFile->header.vertexTable = NULL;
        shapeFile->header.modelNames = NULL;
        shapeFile->header.colliderNames = NULL;
        shapeFile->header.zoneNames = NULL;
        return;
    }

    // Copy raw data into the data buffer
    if (rawSize > sizeof(shapeFile->data)) {
        rawSize = sizeof(shapeFile->data);
    }
    memcpy(shapeFile->data, rawData, rawSize);

    u8* base = shapeFile->data;
    RawShapeFileHeader* rawHeader = (RawShapeFileHeader*)base;

    // Data is already byte-swapped and converted by PM64ShapeFactory
    // All offsets are file-relative (not N64 virtual addresses)

    // Convert the model tree (allocates native structures)
    shapeFile->header.root = ConvertModelNode(base, rawHeader->rootOffset);

    // Vertex table is just raw data, convert offset to pointer
    shapeFile->header.vertexTable = (Vtx_t*)Shape_OffsetToPtr(base, rawHeader->vertexTableOffset);

    // Convert name tables
    shapeFile->header.modelNames = ConvertNameTable(base, rawHeader->modelNamesOffset);
    shapeFile->header.colliderNames = ConvertNameTable(base, rawHeader->colliderNamesOffset);
    shapeFile->header.zoneNames = ConvertNameTable(base, rawHeader->zoneNamesOffset);
}
