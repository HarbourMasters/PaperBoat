#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

#include "common.h"
#include "model.h"
#include <stdio.h>
#include <string.h>
#include "port/patches/Patches.h"
#include "port/modding/MapTextures.h"

#include <deque>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <libultraship/libultraship.h>
#include <ship/resource/ResourceManager.h>
#include <ship/resource/type/Blob.h>

#include "MapTextureMeta.inc.c"

namespace {

struct ModMapTexArchive {
    std::deque<std::string> strings;
    std::vector<MapTexMeta> textures;
    MapTexArchive archive;
};

u32 MapTexImageSize(u32 depth, u32 w, u32 h) {
    static const u32 bits[] = { 4, 8, 16, 32 };
    return depth < 4 ? w * h * bits[depth] / 8 : 0;
}

u32 MapTexPaletteBytes(u32 fmt, u32 depth) {
    return fmt != G_IM_FMT_CI ? 0 : (depth == 0 ? 16 : 256) * 2;
}

std::unique_ptr<ModMapTexArchive> ParseModMapTexArchive(const char* archiveName, const u8* data, size_t size) {
    auto out = std::make_unique<ModMapTexArchive>();
    size_t p = 0;

    while (p + sizeof(TextureHeader) <= size && data[p] != 0) {
        const u8* h = data + p;
        char name[33] = { 0 };
        memcpy(name, h, 32);
        const u16 auxW = (h[0x20] << 8) | h[0x21];
        const u16 mainW = (h[0x22] << 8) | h[0x23];
        const u16 auxH = (h[0x24] << 8) | h[0x25];
        const u16 mainH = (h[0x26] << 8) | h[0x27];
        const u8 extra = h[0x29];
        const u8 mainFmt = h[0x2B] & 0xF, auxFmt = h[0x2B] >> 4;
        const u8 mainDepth = h[0x2C] & 0xF, auxDepth = h[0x2C] >> 4;
        MapTexMeta m;

        memset(&m, 0, sizeof(m));
        p += sizeof(TextureHeader);
        switch (extra) {
            case EXTRA_TILE_NONE:
                p += MapTexImageSize(mainDepth, mainW, mainH) + MapTexPaletteBytes(mainFmt, mainDepth);
                break;
            case EXTRA_TILE_MIPMAPS: {
                u32 div = 2;
                p += MapTexImageSize(mainDepth, mainW, mainH);
                if (mainW >= (32 >> mainDepth)) {
                    while (mainW / div > 0) {
                        p += MapTexImageSize(mainDepth, mainW / div, mainH / div);
                        div *= 2;
                        if (mainW / div < (u32) (16 >> mainDepth)) {
                            break;
                        }
                    }
                }
                p += MapTexPaletteBytes(mainFmt, mainDepth);
                break;
            }
            case EXTRA_TILE_AUX_SAME_AS_MAIN:
                p += 2 * MapTexImageSize(mainDepth, mainW, mainH / 2) + MapTexPaletteBytes(mainFmt, mainDepth);
                break;
            case EXTRA_TILE_AUX_INDEPENDENT:
                p += MapTexImageSize(mainDepth, mainW, mainH) + MapTexPaletteBytes(mainFmt, mainDepth);
                p += MapTexImageSize(auxDepth, auxW, auxH) + MapTexPaletteBytes(auxFmt, auxDepth);
                break;
            default:
                GameEngine_LogWarn("[maptex] %s: texture %s has unknown extra tiles %d", archiveName, name, extra);
                return nullptr;
        }

        const std::string base = std::string("__OTR__textures/") + archiveName + "/" + name;
        out->strings.push_back(name);
        m.name = out->strings.back().c_str();
        out->strings.push_back(base);
        m.otrPath = out->strings.back().c_str();
        if (extra == EXTRA_TILE_AUX_SAME_AS_MAIN || extra == EXTRA_TILE_AUX_INDEPENDENT) {
            out->strings.push_back(base + "_aux");
            m.auxOtrPath = out->strings.back().c_str();
        }
        m.mainW = mainW;
        m.mainH = mainH;
        m.mainFmt = mainFmt;
        m.mainDepth = mainDepth;
        m.mainWrapW = h[0x2D] & 0xF;
        m.mainWrapH = h[0x2E] & 0xF;
        m.filter = h[0x2F];
        m.auxCombineType = h[0x2A] >> 2;
        m.auxCombineSubType = h[0x2A] & 3;
        m.extraTiles = extra;
        m.isVariant = h[0x28];
        m.auxW = auxW;
        m.auxH = auxH;
        m.auxFmt = auxFmt;
        m.auxDepth = auxDepth;
        m.auxWrapW = h[0x2D] >> 4;
        m.auxWrapH = h[0x2E] >> 4;
        m.hasMipmaps = extra == EXTRA_TILE_MIPMAPS;
        out->textures.push_back(m);
    }

    out->strings.push_back(archiveName);
    out->archive.archive = out->strings.back().c_str();
    out->archive.textures = out->textures.data();
    out->archive.count = (u32) out->textures.size();
    return out;
}

const MapTexArchive* ModMapTexArchiveOverride(const char* archiveName) {
    static std::unordered_map<std::string, std::unique_ptr<ModMapTexArchive>> sCache;

    const char* blobPath = Mod_GetMapTexArchiveBlob(archiveName);
    if (blobPath == nullptr) {
        return nullptr;
    }
    auto it = sCache.find(blobPath);
    if (it == sCache.end()) {
        std::unique_ptr<ModMapTexArchive> parsed;
        auto blob = std::dynamic_pointer_cast<Ship::Blob>(
            Ship::Context::GetRawInstance()->GetResourceManager()->LoadResource(blobPath)
        );
        if (blob != nullptr) {
            parsed =
                ParseModMapTexArchive(archiveName, reinterpret_cast<const u8*>(blob->Data.data()), blob->Data.size());
        }
        it = sCache.emplace(blobPath, std::move(parsed)).first;
    }
    return it->second != nullptr ? &it->second->archive : nullptr;
}

} // namespace

extern "C" {

// Port-side reimplementation of the map/battle texture loaders.
#define MAX_TEXTURE_GFX_CMDS 64

// Defined in model.c (kept there; the render path appendGfx_model also calls it).
void make_texture_gfx(
    TextureHeader* header,
    Gfx** gfxPos,
    IMG_PTR raster,
    PAL_PTR palette,
    IMG_PTR auxRaster,
    PAL_PTR auxPalette,
    u8 auxShiftS,
    u8 auxShiftT,
    u16 auxOffsetS,
    u16 auxOffsetT,
    PAL_PTR combinedPalette
);

extern TextureHandle TextureHandles[128];
extern s32 TreeIterPos;
// gCurrentModelTreeNodeInfo is declared in model.h.

// Build a TextureHeader on the stack from a MapTexMeta entry
static void port_build_texture_header(TextureHeader* h, const MapTexMeta* m) {
    s32 i;

    memset(h, 0, sizeof(*h));

    for (i = 0; i < (s32) sizeof(h->name) && m->name[i] != '\0'; i++) {
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

static void* port_get_tex_resource(const char* archive, const char* name, const char* suffix) {
    char path[128];

    if (suffix != NULL) {
        snprintf(path, sizeof(path), "__OTR__textures/%s/%s%s", archive, name, suffix);
    } else {
        snprintf(path, sizeof(path), "__OTR__textures/%s/%s", archive, name);
    }
    return GameEngine_GetDataExact(path);
}

typedef struct NamedLevel {
    const char* base;
    const char* suffix;
    char* path;
    u32 hash;
} NamedLevel;

static NamedLevel* sNamedLevels = NULL;
static s32 sNamedLevelCount = 0;
static s32 sNamedLevelCap = 0;
static s32* sNamedLevelIndex = NULL; // open addressing over sNamedLevels, -1 = empty
static u32 sNamedLevelMask = 0;

static u32 named_level_hash(const char* base, const char* suffix) {
    u32 h = 2166136261u;
    uintptr_t p = (uintptr_t) base;
    while (p != 0) {
        h = (h ^ (u32) (p & 0xFF)) * 16777619u;
        p >>= 8;
    }
    for (; *suffix != '\0'; suffix++) {
        h = (h ^ (u8) *suffix) * 16777619u;
    }
    return h;
}

static void named_level_index_insert(s32 entry) {
    u32 slot = sNamedLevels[entry].hash & sNamedLevelMask;
    while (sNamedLevelIndex[slot] >= 0) {
        slot = (slot + 1) & sNamedLevelMask;
    }
    sNamedLevelIndex[slot] = entry;
}

static void named_level_grow(void) {
    s32 i;

    sNamedLevelCap = sNamedLevelCap == 0 ? 1024 : sNamedLevelCap * 2;
    sNamedLevels = (NamedLevel*) realloc(sNamedLevels, sNamedLevelCap * sizeof(NamedLevel));
    sNamedLevelMask = (u32) sNamedLevelCap * 2 - 1;
    sNamedLevelIndex = (s32*) realloc(sNamedLevelIndex, (sNamedLevelMask + 1) * sizeof(s32));
    for (i = 0; i <= (s32) sNamedLevelMask; i++) {
        sNamedLevelIndex[i] = -1;
    }
    for (i = 0; i < sNamedLevelCount; i++) {
        named_level_index_insert(i);
    }
}

IMG_PTR port_tex_named_level(IMG_PTR raster, const char* suffix) {
    const char* base = (const char*) raster;
    const u32 hash = named_level_hash(base, suffix);
    NamedLevel* entry;
    size_t len;

    if (sNamedLevelIndex != NULL) {
        u32 slot = hash & sNamedLevelMask;
        while (sNamedLevelIndex[slot] >= 0) {
            entry = &sNamedLevels[sNamedLevelIndex[slot]];
            if (entry->hash == hash && entry->base == base && strcmp(entry->suffix, suffix) == 0) {
                return (IMG_PTR) entry->path;
            }
            slot = (slot + 1) & sNamedLevelMask;
        }
    }

    if (sNamedLevelCount >= sNamedLevelCap) {
        named_level_grow();
    }
    len = strlen(base) + strlen(suffix) + 1;
    entry = &sNamedLevels[sNamedLevelCount];
    entry->base = base;
    entry->suffix = suffix;
    entry->hash = hash;
    entry->path = (char*) malloc(len);
    snprintf(entry->path, len, "%s%s", base, suffix);
    named_level_index_insert(sNamedLevelCount);
    sNamedLevelCount++;
    return (IMG_PTR) entry->path;
}

IMG_PTR port_named_image(const char* asset, const char* suffix, void* fallback) {
    IMG_PTR path = port_tex_named_level((IMG_PTR) asset, suffix);
    if (path != NULL && GameEngine_GetDataExact((const char*) path) != NULL) {
        return path;
    }
    return (IMG_PTR) fallback;
}

IMG_PTR port_mip_raster(IMG_PTR raster, IMG_PTR rasterPtr, s32 lod) {
    static const char* const suffixes[] = { "", "_mm1", "_mm2", "_mm3", "_mm4", "_mm5", "_mm6", "_mm7" };

    if (!GameEngine_OTRSigCheck((const char*) raster)) {
        return rasterPtr;
    }
    if (lod == 0) {
        return raster;
    }
    if (lod >= (s32) ARRAY_COUNT(suffixes)) {
        return NULL;
    }
    return port_tex_named_level(raster, suffixes[lod]);
}

IMG_PTR port_aux_raster(IMG_PTR raster, IMG_PTR auxPtr) {
    if (!GameEngine_OTRSigCheck((const char*) raster)) {
        return auxPtr;
    }
    return port_tex_named_level(raster, "_aux");
}

// Load one texture (resolved via MapTexMeta index `metaIdx`) into
// TextureHandles[textureID]. Mirrors load_texture_impl.
static void port_load_one_texture(const char* archive, const MapTexMeta* meta, s32 metaIdx, s32 textureID) {
    TextureHandle* handle = &TextureHandles[textureID];
    const MapTexMeta* m = &meta[metaIdx];
    MapTexMeta resized;
    TextureHeader header;
    Gfx* gfxCursor;
    IMG_PTR raster;
    PAL_PTR palette;
    IMG_PTR auxRaster;
    PAL_PTR auxPalette;
    b32 mainIsCI;
    b32 auxIsCI;

    if (Mod_GetMapTextureSize(archive, m->name, &resized.mainW, &resized.mainH)) {
        const u16 w = resized.mainW, h = resized.mainH;
        resized = *m;
        resized.mainW = w;
        resized.mainH = h;
        m = &resized;
    }

    port_build_texture_header(&header, m);

    mainIsCI = (m->mainFmt == G_IM_FMT_CI);
    auxIsCI = (m->auxFmt == G_IM_FMT_CI);

    raster = (IMG_PTR) m->otrPath;
    GameEngine_PrefetchTexture(m->otrPath);
    GameEngine_PrefetchTexture(m->auxOtrPath);
    if (m->extraTiles == EXTRA_TILE_MIPMAPS) {
        // Same mip levels make_texture_gfx loads
        s32 lod, d;
        for (lod = 1, d = 2; m->mainW / d * (4 << m->mainDepth) >= 64 && m->mainH / d != 0; lod++, d *= 2) {
            GameEngine_PrefetchTexture((const char*) port_mip_raster(raster, NULL, lod));
        }
    }

    // Main palette (CI only): the "<name>_tlut" resource, by name like the raster, so
    // Fast3D can key palette-specific replacement art on it. Nothing reads its bytes.
    if (mainIsCI) {
        palette = (PAL_PTR) port_tex_named_level(raster, "_tlut");
    } else {
        palette = NULL;
    }

    // Aux raster/palette only for the independent-aux case (shared-aux draws its
    // bottom half from the "<name>_aux" resource, see make_texture_gfx).
    if (m->extraTiles == EXTRA_TILE_AUX_INDEPENDENT) {
        // The aux tile is its own resource loaded by its own gDPSetTextureImage
        // (gDPScrollMultiTile passes it through unmodified), so it is
        // path-addressed like the main raster.
        auxRaster = (IMG_PTR) m->auxOtrPath;
        if (auxIsCI) {
            auxPalette = (PAL_PTR) port_tex_named_level(raster, "_aux_tlut");
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

    // No combined 32-entry palette: main and aux load into banks 0 and 1 by name
    // (make_texture_gfx's plain path); Fast3D keeps a slot's banks contiguous itself.
    handle->combinedPalette = NULL;

    handle->gfx = (Gfx*) malloc(MAX_TEXTURE_GFX_CMDS * sizeof(Gfx));
    gfxCursor = handle->gfx;
    memcpy(&handle->header, &header, sizeof(header));

    make_texture_gfx(
        &header, &gfxCursor, handle->raster, handle->palette, handle->auxRaster, handle->auxPalette, 0, 0, 0, 0,
        handle->combinedPalette
    );

    gSPEndDisplayList(gfxCursor++);
}

// Reimplements load_texture_by_name + load_texture_variants for a single model node.
static void
port_load_texture_for_node(const char* archive, const MapTexMeta* meta, u32 count, ModelNodeProperty* propTextureName) {
    const char* textureName = (const char*) propTextureName->data.p;
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
                idx = (s32) i;
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
        GameEngine_LogInfo("[maptex] MISSING resource arc=%s name=%s -> textureID=0", archive, meta[idx].name);
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
        for (j = idx + 1; j < (s32) count; j++) {
            if (!meta[j].isVariant) {
                break;
            }
            port_load_one_texture(archive, meta, j, j + 1);
        }
    }
}

// Reimplements load_next_model_textures: walks the tree, advancing TreeIterPos
// once per node (group and model).
static void port_load_next_model_textures(const char* archive, const MapTexMeta* meta, u32 count, ModelNode* model) {
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

    arc = ModMapTexArchiveOverride(archiveName);
    for (i = 0; arc == NULL && i < gMapTexArchiveCount; i++) {
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
}
