#ifndef SHAPE_LOADER_H
#define SHAPE_LOADER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "model.h"

// Raw N64 structures - these match the exact binary layout in shape files
// All "pointer" fields are actually 32-bit offsets relative to the start of the data

typedef struct RawModelDisplayData {
    /* 0x00 */ u32 displayListOffset;
    /* 0x04 */ u32 unk_04;
} RawModelDisplayData; // size = 0x08

typedef struct RawModelNodeProperty {
    /* 0x00 */ s32 key;
    /* 0x04 */ s32 dataType;
    /* 0x08 */ u32 data; // offset or value depending on dataType
} RawModelNodeProperty; // size = 0x0C

typedef struct RawModelGroupData {
    /* 0x00 */ u32 transformMatrixOffset;
    /* 0x04 */ u32 lightingGroupOffset;
    /* 0x08 */ s32 numLights;
    /* 0x0C */ s32 numChildren;
    /* 0x10 */ u32 childListOffset; // points to array of u32 offsets
} RawModelGroupData; // size = 0x14

typedef struct RawModelNode {
    /* 0x00 */ s32 type;
    /* 0x04 */ u32 displayDataOffset;
    /* 0x08 */ s32 numProperties;
    /* 0x0C */ u32 propertyListOffset;
    /* 0x10 */ u32 groupDataOffset;
} RawModelNode; // size = 0x14

typedef struct RawShapeFileHeader {
    /* 0x00 */ u32 rootOffset;
    /* 0x04 */ u32 vertexTableOffset;
    /* 0x08 */ u32 modelNamesOffset;
    /* 0x0C */ u32 colliderNamesOffset;
    /* 0x10 */ u32 zoneNamesOffset;
    /* 0x14 */ u8 pad[0xC];
} RawShapeFileHeader; // size = 0x20

// Load shape data from raw bytes and populate ShapeFile with proper pointers
// The raw data is copied into shapeFile->data and all pointer fields are converted
void Shape_LoadFromRawData(ShapeFile* shapeFile, const u8* rawData, size_t rawSize);

// Helper to get a pointer from an offset (returns NULL if offset is 0)
static inline void* Shape_OffsetToPtr(u8* base, u32 offset) {
    return offset ? (void*)(base + offset) : NULL;
}

#ifdef __cplusplus
}
#endif

#endif // SHAPE_LOADER_H
