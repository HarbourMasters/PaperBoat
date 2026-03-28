#ifndef _MODEL_H_
#define _MODEL_H_

#include "common.h"

typedef union ModelNodePropertyData {
    s32 s;
    f32 f;
    void* p;
} ModelNodePropertyData;

// In memory this is a list of 6 ModelNodeProperty entries reinterpreted as a
// bounding box. On N64 each property was 12 bytes (sizeof(void*)==4), making
// the overlay 0x48 bytes. On 64-bit each property is 16 bytes
// (sizeof(void*)==8), so the layout must account for the larger stride.
//
// Property mapping (field → property member):
//   key        → prop[0].key
//   halfSizeX  → prop[0].dataType   (computed and stored by mdl_create_model)
//   minX       → prop[0].data.f
//   halfSizeY  → prop[1].dataType
//   minY       → prop[1].data.f
//   halfSizeZ  → prop[2].dataType
//   minZ       → prop[2].data.f
//   maxX       → prop[3].data.f
//   maxY       → prop[4].data.f
//   maxZ       → prop[5].data.f
typedef struct ModelBoundingBox {
    /* prop[0] */ s32 key; // MODEL_PROP_KEY_BOUNDING_BOX
    /* prop[0] */ s32 halfSizeX;
    /* prop[0] */ f32 minX;
                  char _pad0[sizeof(ModelNodePropertyData) - sizeof(f32)];
    /* prop[1] */ s32 _key1;
    /* prop[1] */ s32 halfSizeY;
    /* prop[1] */ f32 minY;
                  char _pad1[sizeof(ModelNodePropertyData) - sizeof(f32)];
    /* prop[2] */ s32 _key2;
    /* prop[2] */ s32 halfSizeZ;
    /* prop[2] */ f32 minZ;
                  char _pad2[sizeof(ModelNodePropertyData) - sizeof(f32)];
    /* prop[3] */ s32 _key3;
    /* prop[3] */ s32 _type3;
    /* prop[3] */ f32 maxX;
                  char _pad3[sizeof(ModelNodePropertyData) - sizeof(f32)];
    /* prop[4] */ s32 _key4;
    /* prop[4] */ s32 _type4;
    /* prop[4] */ f32 maxY;
                  char _pad4[sizeof(ModelNodePropertyData) - sizeof(f32)];
    /* prop[5] */ s32 _key5;
    /* prop[5] */ s32 _type5;
    /* prop[5] */ f32 maxZ;
                  char _pad5[sizeof(ModelNodePropertyData) - sizeof(f32)];
} ModelBoundingBox; // size = 6 * sizeof(ModelNodeProperty)

typedef struct ModelNodeProperty {
    /* 0x0 */ s32 key;
    /* 0x4 */ s32 dataType;
    /* 0x8 */ ModelNodePropertyData data;
} ModelNodeProperty; // size = 0xC;

typedef struct ModelGroupData {
    /* 0x00 */ Mtx* transformMatrix;
    /* 0x04 */ Lightsn* lightingGroup;
    /* 0x08 */ s32 numLights;
    /* 0x0C */ s32 numChildren;
    /* 0x10 */ struct ModelNode** childList;
} ModelGroupData; // size = 0x14

typedef struct ModelDisplayData {
    /* 0x0 */ Gfx* displayList;
    /* 0x4 */ char unk_04[0x4];
} ModelDisplayData; // size = 0x8

typedef struct ModelNode {
    /* 0x00 */ s32 type; /* 2 = model */
    /* 0x04 */ ModelDisplayData* displayData;
    /* 0x08 */ s32 numProperties;
    /* 0x0C */ ModelNodeProperty* propertyList;
    /* 0x10 */ struct ModelGroupData* groupData;
} ModelNode; // size = 0x14

typedef struct Model {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u16 modelID;
    /* 0x04 */ Mtx* bakedMtx; // pointer to stack-allocated copy of matrix supplied by the shape file for this model
    /* 0x08 */ ModelNode* modelNode;
    /* 0x0C */ ModelGroupData* groupData;
    /* 0x10 */ Mtx* finalMtx; // the matrix actually used while building the display list
    /* 0x14 */ char unk_14[4];
    /* 0x18 */ Mtx savedMtx;
    /* 0x58 */ Matrix4f userTransformMtx; // provided for user code to apply an additional multiplicative transformation
    /* 0x98 */ Vec3f center;
    /* 0xA4 */ u8 texPannerID;
    /* 0xA5 */ u8 customGfxIndex;
    /* 0xA6 */ s8 renderMode;
    /* 0xA7 */ u8 matrixFreshness;
    /* 0xA8 */ u8 textureID;
    /* 0xA9 */ s8 textureVariation;
    /* 0xAA */ char unk_AA[6];
} Model; // size = 0xB0

typedef struct ModelTransformGroup {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u16 groupModelID;
    /* 0x04 */ Mtx* bakedMtx; // would point to copy of matrix from shape file, but seems to always be nullptr.
    /* 0x08 */ ModelNode* baseModelNode;
    /* 0x0C */ Mtx* finalMtx; // the matrix actually used while building the display list
    /* 0x10 */ Mtx savedMtx;
    /* 0x50 */ Matrix4f userTransformMtx; // provided for user code to apply an additional multiplicative transformation
    /* 0x90 */ Vec3f center;
    /* 0x9C */ u8 minChildModelIndex;
    /* 0x9D */ u8 maxChildModelIndex;
    /* 0x9E */ u8 renderMode;
    /* 0x9F */ u8 matrixFreshness;
} ModelTransformGroup; // size = 0xA0

typedef Model* ModelList[MAX_MODELS];
typedef ModelTransformGroup* ModelTransformGroupList[MAX_MODEL_TRANSFORM_GROUPS];

typedef struct ModelIDList {
    u16 count;
    u16 list[VLA];
} ModelIDList;

typedef struct ModelLocalVertexCopy {
    /* 0x00 */ s32 numVertices;
    /* 0x04 */ Vtx* minVertexAddr;
    /* 0x08 */ Gfx* gfxCopy[2];
    /* 0x10 */ Vtx* vtxCopy[2];
    /* 0x18 */ s32 selector;
} ModelLocalVertexCopy; // size = 0x1C

typedef ModelLocalVertexCopy* ModelLocalVertexCopyList[16];

typedef struct ModelTreeInfo {
    /* 0x00 */ u8 modelIndex;
    /* 0x01 */ u8 treeDepth;
    /* 0x02 */ u8 textureID;
    /* 0x03 */ char unk_03;
} ModelTreeInfo; // size = 0x04

typedef struct TextureHandle {
    /* 0x00 */ Gfx* gfx;
    /* 0x04 */ TextureHeader header;
    /* 0x34 */ IMG_PTR raster;
    /* 0x38 */ PAL_PTR palette;
    /* 0x3C */ IMG_PTR auxRaster;
    /* 0x40 */ PAL_PTR auxPalette;
    // Port: combined 32-entry palette (main 16 + aux 16) for CI4+CI4 AUX_INDEPENDENT textures.
    // Fast3D interpreter stores pal16(pal=1) in palettes[1], but CI4 palette=1 reads
    // palettes[0]+32. A single 32-entry load into palettes[0] fixes the mismatch.
    PAL_PTR combinedPalette;
} TextureHandle;

typedef struct ModelBlueprint {
    /* 0x0 */ s16 flags;
    /* 0x2 */ char unk_02[0x2];
    /* 0x4 */ ModelNode* mdlNode;
    /* 0x8 */ ModelGroupData* groupData;
    /* 0xC */ Mtx* mtx;
} ModelBlueprint; // size = 0x10

typedef void(*ModelCustomGfxBuilderFunc)(s32 index);

typedef Gfx* ModelCustomGfxList[32];
typedef ModelCustomGfxBuilderFunc ModelCustomGfxBuilderList[32];

typedef enum ModelPropertyKeys {
    MODEL_PROP_KEY_RENDER_MODE      = 0x5C,
    MODEL_PROP_KEY_CAMERA_DATA      = 0x5D,
    MODEL_PROP_KEY_TEXTURE_NAME     = 0x5E,
    MODEL_PROP_KEY_SPECIAL          = 0x5F,
    MODEL_PROP_KEY_GROUP_INFO       = 0x60,
    MODEL_PROP_KEY_BOUNDING_BOX     = 0x61,
    MODEL_PROP_KEY_62               = 0x62,
} ModelPropertyKeys;

typedef enum ShapeTypes {
    SHAPE_TYPE_MODEL                = 2,
    SHAPE_TYPE_GROUP                = 5,
    SHAPE_TYPE_ROOT                 = 7,
    SHAPE_TYPE_SPECIAL_GROUP        = 10,
} ShapeTypes;

typedef enum GroupTypes {
    GROUP_TYPE_0                    = 0,
    GROUP_TYPE_1                    = 1,
} GroupTypes;

typedef enum ExtraTileTypes {
    EXTRA_TILE_NONE                 = 0, // texture contains only a single tile
    EXTRA_TILE_MIPMAPS              = 1, // texture contais mipmaps
    EXTRA_TILE_AUX_SAME_AS_MAIN     = 2, // texture contains main and aux images with identical fmt and size
    EXTRA_TILE_AUX_INDEPENDENT      = 3, // texture contains main and aux images with independent fmt and size
    EXTRA_TILE_4                    = 4, // only use-case may be a mistake? unused and mostly unimplemented
} ExtraTileTypes;

#define SHAPE_SIZE_LIMIT 0x38000  // Increased from 0x30000 — 64-bit native structs need more arena space

typedef struct ShapeFileHeader {
    /* 0x00 */ ModelNode* root;
    /* 0x04 */ Vtx_t* vertexTable;
    /* 0x08 */ char** modelNames;
    /* 0x0C */ char** colliderNames;
    /* 0x10 */ char** zoneNames;
    /* 0x14 */ unsigned char pad_14[0xC];
} ShapeFileHeader; // size = 0x20

typedef struct ShapeFile {
    /* 0x00 */ ShapeFileHeader header;
    /* 0x20 */ u8 data[SHAPE_SIZE_LIMIT - sizeof(ShapeFileHeader)];
} ShapeFile; // size = variable

typedef ModelTreeInfo ModelTreeInfoList[0x200];

#ifndef NO_EXTERN_VARIABLES

extern ModelTreeInfoList* gCurrentModelTreeNodeInfo;
extern ModelList* gCurrentModels;

#endif

void mdl_set_depth_tint_params(u8 primR, u8 primG, u8 primB, u8 primA, u8 fogR, u8 fogG, u8 fogB, s32 fogStart, s32 fogEnd);
void mdl_set_remap_tint_params(u8 primR, u8 primG, u8 primB, u8 envR, u8 envG, u8 envB);
void mdl_get_remap_tint_params(u8* primR, u8* primG, u8* primB, u8* envR, u8* envG, u8* envB);

void init_model_data(void);
void update_model_animator(s32);
void update_model_animator_with_transform(s32 animatorID, Mtx* mtx);
void set_mdl_custom_gfx_set(Model*, s32, u32);
ModelNodeProperty* get_model_property(ModelNode* node, ModelPropertyKeys key);
void load_texture_variants(u8* srcData, s32 textureID, u8* baseData, s32 size);
s32 step_model_animator(ModelAnimator* animator);
AnimatorNode* get_animator_node_for_tree_index(ModelAnimator* animator, s32 treeIndex);
AnimatorNode* get_animator_node_with_id(ModelAnimator* animator, s32 id);
void animator_update_model_transforms(ModelAnimator* animator, Mtx* rootTransform);
void render_animated_model(s32 animatorID, Mtx* rootTransform, u32 interpolationTag);
void animator_node_update_model_transform(ModelAnimator* animator, f32 (*flipMtx)[4], AnimatorNode* node,
                                          Mtx* rootTransform);
void init_worker_list(void);
ModelAnimator* get_animator_by_index(s32 animModelID);
void reset_animator_list(void);
void delete_model_animator_node(AnimatorNode* node);
void delete_model_animator_nodes(ModelAnimator* animator);
void delete_model_animator(ModelAnimator* animator);
void render_animated_model_with_vertices(s32 animatorID, Mtx* rootTransform, s32 segment, void* baseAddr, u32 interpolationTag);
void appendGfx_animator(ModelAnimator* animator);
ModelAnimator* set_animator_render_callback(s32 animModelID, void* callbackArg, void (*callbackFunc)(void*));
void reload_mesh_animator_tree(ModelAnimator* animator);
s32 step_mesh_animator(ModelAnimator* animator);

void set_custom_gfx_builders(s32 customGfxIndex, ModelCustomGfxBuilderFunc pre, ModelCustomGfxBuilderFunc post);
void mdl_make_local_vertex_copy(s32 arg0, u16 treeIdx, s32);
void play_model_animation_starting_from(s32 index, s16* animPos, s32 framesToSkip);

void mdl_set_shroud_tint_params(u8 r, u8 g, u8 b, u8 a);

s32 mdl_is_otr_expanded_opcode(u32 opcode);
Vtx* mdl_resolve_otr_vtx(Gfx* gfx);

#endif
