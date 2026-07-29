#include "common.h"
#include "model.h"
#include <stdio.h>
#include <string.h>
#include "port/Engine.h"
#include "port/patches/Patches.h"

#include "MapTextureMeta.inc.c"

// Port-side reimplementation of the map/battle texture loaders.
#define MAX_TEXTURE_GFX_CMDS 64

// Defined in model.c (kept there; the render path appendGfx_model also calls it).
void make_texture_gfx(TextureHeader* header, Gfx** gfxPos, IMG_PTR raster, PAL_PTR palette,
                      IMG_PTR auxRaster, PAL_PTR auxPalette, u8 auxShiftS, u8 auxShiftT,
                      u16 auxOffsetS, u16 auxOffsetT, PAL_PTR combinedPalette);

extern TextureHandle TextureHandles[128];
extern s32 TreeIterPos;
// gCurrentModelTreeNodeInfo is declared in model.h.

// Build a TextureHeader on the stack from a MapTexMeta entry
static void port_build_texture_header(TextureHeader* h, const MapTexMeta* m) {
    s32 i;

    memset(h, 0, sizeof(*h));

    for (i = 0; i < (s32)sizeof(h->name) && m->name[i] != '\0'; i++) {
        h->name[i] = m->name[i];
    }

    h->auxW = m->auxW;
    h->mainW = m->mainW;
    h->auxH = m->auxH;
    h->mainH = m->mainH;

    h->isVariant = m->isVariant;
    h->extraTiles = m->extraTiles;

    h->auxFmt = m->auxFmt;
    h->mainFmt = m->mainFmt;
    h->auxBitDepth = m->auxDepth;
    h->mainBitDepth = m->mainDepth;
    h->auxWrapW = m->auxWrapW;
    h->mainWrapW = m->mainWrapW;
    h->auxWrapH = m->auxWrapH;
    h->mainWrapH = m->mainWrapH;
    h->filtering = m->filter;
    
    h->auxCombineType = m->auxCombineType;
    h->auxCombineSubType = m->auxCombineSubType;
}

// Resolve a named texture resource to its raw pixel/palette pointer.
static void* port_get_tex_resource(const char* archive, const char* name, const char* suffix) {
    char path[128];

    if (suffix != NULL) {
        snprintf(path, sizeof(path), "__OTR__textures/%s/%s%s", archive, name, suffix);
    } else {
        snprintf(path, sizeof(path), "__OTR__textures/%s/%s", archive, name);
    }
    return ResourceGetDataByName(path);
}

static size_t port_get_tex_resource_size(const char* archive, const char* name, const char* suffix) {
    char path[128];

    if (suffix != NULL) {
        snprintf(path, sizeof(path), "__OTR__textures/%s/%s%s", archive, name, suffix);
    } else {
        snprintf(path, sizeof(path), "__OTR__textures/%s/%s", archive, name);
    }
    return ResourceGetSizeByName(path);
}

static IMG_PTR port_resolve_main_raster(const char* archive, const char* name, u8 extraTiles) {
    void* base;
    size_t baseSize;
    size_t total;
    void* mm[16];
    size_t mmSize[16];
    s32 mmCount;
    char suffix[8];
    u8* buf;
    size_t off;
    s32 i;

    base = port_get_tex_resource(archive, name, NULL);

    if (extraTiles != EXTRA_TILE_MIPMAPS || base == NULL) {
        return (IMG_PTR)base;
    }

    // Collect consecutive mip-level resources.
    mmCount = 0;
    total = 0;
    baseSize = port_get_tex_resource_size(archive, name, NULL);
    total += baseSize;
    for (i = 1; i < (s32)ARRAY_COUNT(mm); i++) {
        void* p;
        snprintf(suffix, sizeof(suffix), "_mm%d", i);
        p = port_get_tex_resource(archive, name, suffix);
        if (p == NULL) {
            break;
        }
        mm[mmCount] = p;
        mmSize[mmCount] = port_get_tex_resource_size(archive, name, suffix);
        total += mmSize[mmCount];
        mmCount++;
    }

    if (mmCount == 0) {
        // No separate mip resources -> base is already the whole (single-LOD) raster.
        return (IMG_PTR)base;
    }

    // Concatenate base + mip levels into a contiguous buffer (matches the blob
    // layout make_texture_gfx expects).
    buf = (u8*)malloc(total);
    memcpy(buf, base, baseSize);
    off = baseSize;
    for (i = 0; i < mmCount; i++) {
        memcpy(buf + off, mm[i], mmSize[i]);
        off += mmSize[i];
    }
    return (IMG_PTR)buf;
}

static b32 port_class_uses_otr_path(u8 extraTiles) {
    return extraTiles == EXTRA_TILE_NONE || extraTiles == EXTRA_TILE_AUX_INDEPENDENT;
}

// Load one texture (resolved via MapTexMeta index `metaIdx`) into
// TextureHandles[textureID]. Mirrors load_texture_impl.
static void port_load_one_texture(const char* archive, const MapTexMeta* meta, s32 metaIdx, s32 textureID) {
    TextureHandle* handle = &TextureHandles[textureID];
    const MapTexMeta* m = &meta[metaIdx];
    TextureHeader header;
    Gfx* gfxCursor;
    IMG_PTR raster;
    PAL_PTR palette;
    IMG_PTR auxRaster;
    PAL_PTR auxPalette;
    b32 mainIsCI;
    b32 auxIsCI;

    port_build_texture_header(&header, m);

    mainIsCI = (m->mainFmt == G_IM_FMT_CI);
    auxIsCI = (m->auxFmt == G_IM_FMT_CI);

    if (port_class_uses_otr_path(m->extraTiles)) {
        raster = (IMG_PTR)m->otrPath;
    } else {
        raster = port_resolve_main_raster(archive, m->name, m->extraTiles);
    }

    // Main palette (CI only).
    if (mainIsCI) {
        palette = (PAL_PTR)port_get_tex_resource(archive, m->name, "_tlut");
    } else {
        palette = NULL;
    }

    // Aux raster/palette only for the independent-aux case (shared-aux keeps the
    // bottom half inside the full-height main raster, exactly like the blob).
    if (m->extraTiles == EXTRA_TILE_AUX_INDEPENDENT) {
        // The aux tile is its own resource loaded by its own gDPSetTextureImage
        // (gDPScrollMultiTile passes it through unmodified), so it is
        // path-addressed like the main raster.
        auxRaster = (IMG_PTR)m->auxOtrPath;
        if (auxIsCI) {
            auxPalette = (PAL_PTR)port_get_tex_resource(archive, m->name, "_aux_tlut");
        } else {
            auxPalette = NULL;
        }
    } else {
        auxRaster = NULL;
        auxPalette = NULL;
    }

    handle->raster = raster;
    handle->palette = palette;
    handle->auxRaster = auxRaster;
    handle->auxPalette = auxPalette;

    // Combined 32-entry CI4 palette for AUX_INDEPENDENT CI4+CI4 (matches
    // load_texture_impl).
    handle->combinedPalette = NULL;
    if (header.extraTiles == EXTRA_TILE_AUX_INDEPENDENT
        && handle->palette != NULL && handle->auxPalette != NULL
        && header.mainBitDepth == G_IM_SIZ_4b && header.auxBitDepth == G_IM_SIZ_4b)
    {
        handle->combinedPalette = (PAL_PTR)malloc(64); // 32 entries * 2 bytes
        memcpy(handle->combinedPalette, handle->palette, 32);
        memcpy((u8*)handle->combinedPalette + 32, handle->auxPalette, 32);
    }

    handle->gfx = (Gfx*)malloc(MAX_TEXTURE_GFX_CMDS * sizeof(Gfx));
    gfxCursor = handle->gfx;
    memcpy(&handle->header, &header, sizeof(header));

    make_texture_gfx(&header, &gfxCursor, handle->raster, handle->palette,
                     handle->auxRaster, handle->auxPalette, 0, 0, 0, 0, handle->combinedPalette);

    gSPEndDisplayList(gfxCursor++);
}

// Reimplements load_texture_by_name + load_texture_variants for a single model node.
static void port_load_texture_for_node(const char* archive, const MapTexMeta* meta, u32 count,
                                       ModelNodeProperty* propTextureName) {
    const char* textureName = (const char*)propTextureName->data.p;
    s32 idx;
    s32 textureID;

    if (textureName == NULL) {
        (*gCurrentModelTreeNodeInfo)[TreeIterPos].textureID = 0;
        return;
    }

    // Find the texture by name (archive order == metadata order).
    idx = -1;
    {
        u32 i;
        for (i = 0; i < count; i++) {
            if (strcmp(textureName, meta[i].name) == 0) {
                idx = (s32)i;
                break;
            }
        }
    }

    if (idx < 0) {
        // Not found -> unloaded, matching the blob walk running off the end.
        (*gCurrentModelTreeNodeInfo)[TreeIterPos].textureID = 0;
        return;
    }

    if (port_get_tex_resource(archive, meta[idx].name, NULL) == NULL) {
        GameEngine_LogInfo("[maptex] MISSING resource arc=%s name=%s -> textureID=0",
                           archive, meta[idx].name);
        (*gCurrentModelTreeNodeInfo)[TreeIterPos].textureID = 0;
        return;
    }

    textureID = idx + 1;
    (*gCurrentModelTreeNodeInfo)[TreeIterPos].textureID = textureID;

    // Only load the first time this texture (and its variant run) is referenced,
    // exactly like `if (textureHandle->gfx == nullptr)` in load_texture_by_name.
    if (TextureHandles[textureID].gfx == NULL) {
        s32 j;

        port_load_one_texture(archive, meta, idx, textureID);

        // load_texture_variants: consecutive following textures while isVariant,
        // into consecutive TextureHandles[] slots. Bounded by the archive count
        // (no blob walk -> no over-read).
        for (j = idx + 1; j < (s32)count; j++) {
            if (!meta[j].isVariant) {
                break;
            }
            port_load_one_texture(archive, meta, j, j + 1);
        }
    }
}

// Reimplements load_next_model_textures: walks the tree, advancing TreeIterPos
// once per node (group and model).
static void port_load_next_model_textures(const char* archive, const MapTexMeta* meta, u32 count,
                                          ModelNode* model) {
    if (model->type != SHAPE_TYPE_MODEL) {
        if (model->groupData != NULL) {
            s32 numChildren = model->groupData->numChildren;

            if (numChildren != 0) {
                s32 i;
                for (i = 0; i < numChildren; i++) {
                    port_load_next_model_textures(archive, meta, count, model->groupData->childList[i]);
                }
            }
        }
    } else {
        ModelNodeProperty* propTextureName = get_model_property(model, MODEL_PROP_KEY_TEXTURE_NAME);
        if (propTextureName != NULL) {
            port_load_texture_for_node(archive, meta, count, propTextureName);
        }
    }
    TreeIterPos++;
}

void port_load_map_textures(ModelNode* rootModel, const char* archiveName) {
    const MapTexArchive* arc = NULL;
    u32 i;

    if (rootModel == NULL || archiveName == NULL) {
        return;
    }

    for (i = 0; i < gMapTexArchiveCount; i++) {
        if (strcmp(gMapTexArchives[i].archive, archiveName) == 0) {
            arc = &gMapTexArchives[i];
            break;
        }
    }

    if (arc == NULL) {
        GameEngine_LogInfo("port_load_map_textures: no metadata for archive '%s'", archiveName);
        return;
    }

    // Reset handles exactly as mdl_load_all_textures does.
    for (i = 0; i < ARRAY_COUNT(TextureHandles); i++) {
        TextureHandles[i].gfx = NULL;
    }

    TreeIterPos = 0;
    port_load_next_model_textures(arc->archive, arc->textures, arc->count, rootModel);
}
