#include "shape_loader.h"
#include "gcc/string.h"
#include <stdio.h>

// Forward declaration for logging and resource loading
extern void GameEngine_LogInfo(const char* fmt, ...);
extern void* ResourceGetDataByName(const char* name);

// Debug logging - use GameEngine_LogInfo for proper logging
#define SHAPE_LOG(...) GameEngine_LogInfo(__VA_ARGS__)
#define SPDLOG_INFO(...) GameEngine_LogInfo(__VA_ARGS__)

// Current shape name for display list path building
static const char* gCurrentShapeName = NULL;

// Forward declarations for recursive conversion
static ModelNode* ConvertModelNode(u8* base, u32 offset);
static ModelGroupData* ConvertModelGroupData(u8* base, u32 offset);

// Load display list from OTR resource by offset
// Display lists use G_VTX_OTR_HASH which libultraship resolves automatically
static Gfx* LoadDisplayListByOffset(u32 dlOffset) {
    if (dlOffset == 0 || gCurrentShapeName == NULL) {
        return NULL;
    }

    SPDLOG_INFO("[Shape] Loading display list from shape: %s, offset: 0x%X\n",
              gCurrentShapeName, dlOffset);

    // Build the resource path: shapes/{shapeName}/dlist_{offset}
    char path[128];
    snprintf(path, sizeof(path), "__OTR__shapes/%s/dlist_%X", gCurrentShapeName, dlOffset);

    // Load the display list from OTR - G_VTX_OTR_HASH resolves vertices automatically
    Gfx* dl = (Gfx*)ResourceGetDataByName(path);

    if (dl == NULL) {
        SPDLOG_INFO("[Shape] WARNING: Could not load display list from %s\n", path);
        return NULL;
    }

    SPDLOG_INFO("[Shape] Loaded display list from %s -> %p\n", path, (void*)dl);

    return dl;
}

static ModelDisplayData* ConvertModelDisplayData(u8* base, u32 offset) {
    if (offset == 0) {
        SPDLOG_INFO("[Shape] ConvertModelDisplayData: offset=0, returning NULL (shape=%s)\n",
                   gCurrentShapeName ? gCurrentShapeName : "(null)");
        return NULL;
    }

    RawModelDisplayData* raw = (RawModelDisplayData*)(base + offset);

    SPDLOG_INFO("[Shape] ConvertModelDisplayData: offset=0x%X, displayListOffset=0x%X\n",
              offset, raw->displayListOffset);

    if (raw->displayListOffset == 0) {
        SPDLOG_INFO("[Shape] ConvertModelDisplayData: displayListOffset=0, returning NULL (shape=%s)\n",
                   gCurrentShapeName ? gCurrentShapeName : "(null)");
        return NULL;
    }

    // Allocate native ModelDisplayData structure
    ModelDisplayData* native = general_heap_malloc(sizeof(ModelDisplayData));

    // Load display list from OTR resource - vertices resolved via G_VTX_OTR_HASH
    native->displayList = LoadDisplayListByOffset(raw->displayListOffset);

    if (native->displayList != NULL) {
        SPDLOG_INFO("[Shape] Display list loaded at %p\n", (void*)native->displayList);
    }

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

    // Debug: hex dump the raw bytes to verify what's actually there
    u8* bytes = (u8*)raw;
    SPDLOG_INFO("[Shape] ConvertModelNode: offset=0x%X, raw bytes: %02X %02X %02X %02X %02X %02X %02X %02X\n",
              offset, bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7]);
    SPDLOG_INFO("[Shape] ConvertModelNode: offset=0x%X, type=%d, displayDataOffset=0x%X, groupDataOffset=0x%X\n",
              offset, raw->type, raw->displayDataOffset, raw->groupDataOffset);

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

void Shape_LoadFromRawData(ShapeFile* shapeFile, const u8* rawData, size_t rawSize, const char* shapeName) {
    SPDLOG_INFO("[Shape] Shape_LoadFromRawData called: rawData=%p, rawSize=%zu, shapeName=%s\n",
              (void*)rawData, rawSize, shapeName ? shapeName : "(null)");

    if (rawData == NULL || rawSize == 0) {
        SPDLOG_INFO("[Shape] Shape_LoadFromRawData: rawData is NULL or size is 0, returning early\n");
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

    SPDLOG_INFO("[Shape] Raw header: root=0x%X, vtx=0x%X, modelNames=0x%X\n",
              rawHeader->rootOffset, rawHeader->vertexTableOffset, rawHeader->modelNamesOffset);

    // Set up global context for display list loading
    gCurrentShapeName = shapeName;

    // Data is already byte-swapped and converted by PM64ShapeFactory
    // All offsets are file-relative (not N64 virtual addresses)

    // Convert the model tree (allocates native structures)
    shapeFile->header.root = ConvertModelNode(base, rawHeader->rootOffset);
    SPDLOG_INFO("[Shape] ConvertModelNode returned: %p\n", (void*)shapeFile->header.root);

    // Vertex table is just raw data, convert offset to pointer
    shapeFile->header.vertexTable = (Vtx_t*)Shape_OffsetToPtr(base, rawHeader->vertexTableOffset);

    // Convert name tables
    shapeFile->header.modelNames = ConvertNameTable(base, rawHeader->modelNamesOffset);
    shapeFile->header.colliderNames = ConvertNameTable(base, rawHeader->colliderNamesOffset);
    shapeFile->header.zoneNames = ConvertNameTable(base, rawHeader->zoneNamesOffset);

    // Clear global context
    gCurrentShapeName = NULL;
}
