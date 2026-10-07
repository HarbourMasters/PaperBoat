#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/sprite/SpriteLoader.h"

#include "common.h"
#include "sprite.h"
#include "sprite/player.h"
#include "port/patches/Patches.h"

extern "C" {

// The component's own palette, which the two-tone one is built from.
static PAL_PTR sShadingSourcePalette;

// One palette per shaded component: the display list is built now and run later, so a
// single buffer would leave every component drawing with the last one written.
#define SHADING_PALETTE_COUNT 512
static PAL_BIN sShadingPalettes[SHADING_PALETTE_COUNT][16];
static s32 sShadingPaletteIdx;

void port_set_shading_source_palette(PAL_PTR palette) {
    sShadingSourcePalette = palette;
}

void port_appendGfx_shading_palette(
    Matrix4f mtx,
    s32 uls,
    s32 ult,
    s32 lrs,
    s32 lrt,
    s32 alpha,
    f32 shadowX,
    f32 shadowY,
    f32 shadowZ,
    s32 shadowR,
    s32 shadowG,
    s32 shadowB,
    s32 highlightR,
    s32 highlightG,
    s32 highlightB,
    s32 ambientPower,
    s32 renderMode
) {
    Camera* camera = &gCameras[gCurrentCameraID];
    f32 mtx01, mtx11, mtx21;
    f32 offsetX, offsetY;
    f32 shadowMag;
    f32 var_f12_2;
    f32 shadowXZ;
    f32 facingDir;
    f32 pm02, pm22;

    shadowMag = SQ(shadowX) + SQ(shadowY) + SQ(shadowZ);

    if (shadowMag < 1.0) {
        ambientPower *= shadowMag;
    }
    if (shadowMag != 0.0f) {
        shadowMag = 1.0f / sqrtf(shadowMag);
    }
    shadowX *= shadowMag;
    shadowY *= shadowMag;
    shadowZ *= shadowMag;

    if (((-mtx[0][2] * camera->mtxPerspective[0][2]) + (mtx[2][2] * camera->mtxPerspective[2][2])) < 0.0f) {
        facingDir = 1.0f;
    } else {
        facingDir = -1.0f;
    }

    pm02 = camera->mtxPerspective[0][2];
    pm22 = camera->mtxPerspective[2][2];

    offsetX = ambientPower * ((shadowX * -pm22) + (shadowZ * pm02));

    shadowXZ = SQ(shadowX) + SQ(shadowZ);
    if (shadowXZ != 0.0f) {
        shadowXZ = sqrtf(shadowXZ);
    }
    mtx01 = mtx[0][1];
    mtx11 = mtx[1][1];
    mtx21 = mtx[2][1];
    var_f12_2 = SQ(mtx01) + SQ(mtx21);
    if (var_f12_2 != 0.0f) {
        var_f12_2 = sqrtf(var_f12_2);
    }
    offsetY = -((shadowXZ * var_f12_2) + (shadowY * mtx11)) * ambientPower;

    // Per-channel clamp to 8-bit.
    if (shadowR > 255) {
        shadowR = 255;
    }
    if (shadowG > 255) {
        shadowG = 255;
    }
    if (shadowB > 255) {
        shadowB = 255;
    }
    if (highlightR > 255) {
        highlightR = 255;
    }
    if (highlightG > 255) {
        highlightG = 255;
    }
    if (highlightB > 255) {
        highlightB = 255;
    }

    // [port] The N64 built this palette by drawing a 16x2 rectangle and reading it back, which
    // stalled the GPU once per shaded component. PM_CC_55 over a 1-bit alpha only selects
    // between two colours, so fill it directly: opaque entries take the shadow tone.
    PAL_BIN* palette = sShadingPalettes[sShadingPaletteIdx];
    sShadingPaletteIdx = (sShadingPaletteIdx + 1) % SHADING_PALETTE_COUNT;
    s32 opaque = 0;
    s32 transparent = 0;
    {
        const u8* source = (const u8*) port_sprite_palette_data(sShadingSourcePalette);
        u8* out = (u8*) palette;
        const u16 shadow = ((shadowR >> 3) << 11) | ((shadowG >> 3) << 6) | ((shadowB >> 3) << 1) | 1;
        const u16 highlight = ((highlightR >> 3) << 11) | ((highlightG >> 3) << 6) | ((highlightB >> 3) << 1) | 1;
        s32 i;
        for (i = 0; i < 16; i++) {
            const b32 isOpaque = source != NULL && (source[i * 2 + 1] & 1);
            const u16 entry = isOpaque ? shadow : highlight;
            out[i * 2 + 0] = entry >> 8;
            out[i * 2 + 1] = entry & 0xFF;
            if (isOpaque) {
                opaque = i;
            } else {
                transparent = i;
            }
        }
    }

    // HD art is then shaded by its own silhouette rather than the raster's
    gDPPaletteMask(gMainGfxPos++, palette, opaque, transparent);
    gDPLoadTLUT_pal16(gMainGfxPos++, 1, palette);
    // Drop textures cached against this palette address: the ring comes back to it later.
    gDPInvalTexByPalette(gMainGfxPos++, palette);

    gSPSetOtherMode(
        gMainGfxPos++, G_SETOTHERMODE_H, 4, 18,
        G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP
            | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE
    );
    CALL_EVENT(SpriteShadingPreDraw);

    gDPSetRenderMode(gMainGfxPos++, G_RM_PASS, renderMode);
    gDPSetEnvColor(gMainGfxPos++, 100, 100, 100, 255);

    if (alpha == 255) {
        gDPSetCombineMode(gMainGfxPos++, PM_CC_50, PM_CC_52);
    } else {
        gDPSetCombineMode(gMainGfxPos++, PM_CC_51, PM_CC_52);
    }

    gDPSetTileSize(
        gMainGfxPos++,
        0,
        ((uls + 0x100) << 2) + (s32) (offsetX * facingDir),
        ((ult + 0x100) << 2) + (s32) offsetY,
        ((lrs + 0x100 - 1) << 2) + (s32) (offsetX * facingDir),
        ((lrt + 0x100 - 1) << 2) + (s32) offsetY
    );
}

// Start decoding the HD art for an animation's frames before they're drawn. Reads its
// SetImage commands and skips the rest by length, like spr_load_npc_extra_anims.
static void PrefetchAnim(SpriteAnimData* sprite, s32 animIndex, s32 playerSpriteIndex) {
    SpriteAnimComponent** compList = sprite->animListStart[animIndex];
    SpriteAnimComponent* comp;

    while ((comp = *compList++) != PTR_LIST_END) {
        u16* cmd = comp->cmdList;
        u16* end = &comp->cmdList[comp->cmdListSize / 2];

        while (cmd < end) {
            switch (*cmd & 0xF000) {
                case 0x1000:
                    if ((*cmd & 0xFFF) != 0xFFF) {
                        s32 raster = *cmd & 0xFFF;
                        GameEngine_PrefetchTexture(
                            playerSpriteIndex >= 0 ? (const char*) Sprite_GetPlayerRasterPath(playerSpriteIndex, raster)
                                                   : (const char*) sprite->rastersOffset[raster]->image
                        );
                    }
                    cmd += 1;
                    break;
                case 0x3000:
                    cmd += 4;
                    break;
                case 0x4000:
                    cmd += 3;
                    break;
                case 0x5000:
                case 0x7000:
                    cmd += 2;
                    break;
                default:
                    cmd += 1;
                    break;
            }
        }
    }
}

void port_prefetch_npc_anim(SpriteAnimData* sprite, s32 prevAnimID, s32 animID) {
    if (SPR_UNPACK_ANIM(prevAnimID) != SPR_UNPACK_ANIM(animID)) {
        PrefetchAnim(sprite, SPR_UNPACK_ANIM(animID), -1);
    }
}

void port_prefetch_player_anim(SpriteAnimData* sprite, s32 prevAnimID, s32 animID) {
    if (animID == prevAnimID) {
        return;
    }
    // Facing away draws from the next sprite (see spr_draw_player_sprite)
    s32 spriteID = SPR_UNPACK_SPR(animID);
    b32 back = (animID & SPRITE_ID_BACK_FACING)
        && (spriteID == SPR_Mario1 || spriteID == SPR_MarioW1 || spriteID == SPR_Peach1);
    PrefetchAnim(sprite, SPR_UNPACK_ANIM(animID), spriteID - 1 + back);
}

#define RESOLVED_PALETTE_LISTS 64
#define RESOLVED_PALETTE_MAX   27
#define ORIGINAL_PALETTE_LISTS 32
#define PALETTE_BLEND_TAGS     64
#define SILHOUETTE_SPREAD      4

typedef struct ResolvedPalettes {
    const void* owner;
    u32 frame;
    PAL_BIN data[2][RESOLVED_PALETTE_MAX][SPR_PAL_SIZE];
} ResolvedPalettes;

typedef struct OriginalPalettes {
    PAL_PTR* list;
    u32 frame;
    s32 count;
    PAL_PTR names[RESOLVED_PALETTE_MAX];
    PAL_PTR data[RESOLVED_PALETTE_MAX];
} OriginalPalettes;

typedef struct PaletteBlendTag {
    PAL_PTR palette;
    PAL_PTR from;
    PAL_PTR to;
    s32 alpha;
    u8 scale[3];
    s8 tint[3];
    b8 isTint;
    u32 frame;
} PaletteBlendTag;

static ResolvedPalettes sResolvedPalettes[RESOLVED_PALETTE_LISTS];
static OriginalPalettes sOriginalPalettes[ORIGINAL_PALETTE_LISTS];
static s32 sOriginalPalettesNext;
static PaletteBlendTag sBlendTags[PALETTE_BLEND_TAGS];
static s32 sBlendTagsNext;
static u32 sPaletteFrame;

static PAL_PTR* sOverridePalettes;
static OriginalPalettes* sOverrideOriginals;
static ResolvedPalettes* sOverrideSlot;

void port_palette_frame(void) {
    sPaletteFrame++;
}

static PaletteBlendTag* port_palette_tag(PAL_PTR palette) {
    PaletteBlendTag* tag = &sBlendTags[sBlendTagsNext];
    s32 i;

    for (i = 0; i < PALETTE_BLEND_TAGS; i++) {
        if (sBlendTags[i].palette == palette) {
            tag = &sBlendTags[i];
            break;
        }
    }
    if (tag == &sBlendTags[sBlendTagsNext]) {
        sBlendTagsNext = (sBlendTagsNext + 1) % PALETTE_BLEND_TAGS;
    }
    tag->palette = palette;
    tag->frame = sPaletteFrame;
    return tag;
}

void port_palette_blend(PAL_PTR palette, PAL_PTR from, PAL_PTR to, s32 alpha) {
    PaletteBlendTag* tag = port_palette_tag(palette);
    tag->from = from;
    tag->to = to;
    tag->alpha = alpha;
    tag->isTint = false;
}

void port_palette_tint(PAL_PTR palette, PAL_PTR base, f32 sr, f32 sg, f32 sb, s32 r, s32 g, s32 b) {
    PaletteBlendTag* tag = port_palette_tag(palette);
    tag->from = base;
    tag->scale[0] = std::clamp<f32>(sr * 128.0f + 0.5f, 0.0f, 255.0f);
    tag->scale[1] = std::clamp<f32>(sg * 128.0f + 0.5f, 0.0f, 255.0f);
    tag->scale[2] = std::clamp<f32>(sb * 128.0f + 0.5f, 0.0f, 255.0f);
    tag->tint[0] = r;
    tag->tint[1] = g;
    tag->tint[2] = b;
    tag->isTint = true;
}

static b32 is_named_palette(PAL_PTR palette) {
    return palette == NULL || palette == (PAL_PTR) -1 || GameEngine_OTRSigCheck((const char*) palette);
}

static OriginalPalettes* get_original_palettes(PAL_PTR* list) {
    OriginalPalettes* entry = NULL;
    s32 count = 0;
    s32 i;

    while (count < RESOLVED_PALETTE_MAX && list[count] != (PAL_PTR) -1) {
        count++;
    }
    for (i = 0; i < ORIGINAL_PALETTE_LISTS; i++) {
        if (sOriginalPalettes[i].list == list) {
            entry = &sOriginalPalettes[i];
            break;
        }
    }
    if (entry != NULL && entry->frame == sPaletteFrame && entry->count == count
        && memcmp(entry->names, list, count * sizeof(PAL_PTR)) == 0)
    {
        return entry;
    }
    if (entry == NULL) {
        entry = &sOriginalPalettes[sOriginalPalettesNext];
        sOriginalPalettesNext = (sOriginalPalettesNext + 1) % ORIGINAL_PALETTE_LISTS;
    }
    entry->list = list;
    entry->frame = sPaletteFrame;
    entry->count = count;
    for (i = 0; i < count; i++) {
        entry->names[i] = list[i];
        entry->data[i] = is_named_palette(list[i]) ? port_sprite_palette_data(list[i]) : NULL;
    }
    return entry;
}

static ResolvedPalettes* get_resolved_slot(const void* owner) {
    const u32 frame = sPaletteFrame;
    ResolvedPalettes* oldest = NULL;
    s32 i;

    for (i = 0; i < RESOLVED_PALETTE_LISTS; i++) {
        ResolvedPalettes* slot = &sResolvedPalettes[i];
        if (slot->owner == owner) {
            slot->frame = frame;
            return slot;
        }
        if (slot->frame != frame && (oldest == NULL || frame - slot->frame > frame - oldest->frame)) {
            oldest = slot;
        }
    }
    if (oldest != NULL) {
        oldest->owner = owner;
        oldest->frame = frame;
    }
    return oldest;
}

static PAL_PTR find_original_palette(PAL_PTR palette, const OriginalPalettes* originals, s32 index) {
    s32 k;

    for (k = -1; k < originals->count; k++) {
        const s32 i = k < 0 ? index : k;
        if (i >= originals->count) {
            continue;
        }
        if (originals->names[i] == palette) {
            return palette;
        }
        if (originals->data[i] != NULL && memcmp(originals->data[i], palette, sizeof(PAL_BIN) * SPR_PAL_SIZE) == 0) {
            return originals->names[i];
        }
    }
    return NULL;
}

static b32 emit_blend_tag(PAL_PTR palette, PAL_PTR copy) {
    s32 i;

    for (i = 0; i < PALETTE_BLEND_TAGS; i++) {
        const PaletteBlendTag* tag = &sBlendTags[i];
        if (tag->palette == palette && tag->frame == sPaletteFrame) {
            if (tag->isTint) {
                gDPPaletteTint(
                    gMainGfxPos++, copy, tag->from, tag->scale[0], tag->scale[1], tag->scale[2], tag->tint[0],
                    tag->tint[1], tag->tint[2]
                );
            } else {
                gDPPaletteBlend(gMainGfxPos++, copy, tag->from, tag->to, tag->alpha);
            }
            return true;
        }
    }
    return false;
}

static void emit_silhouette(PAL_PTR copy) {
    const u8* data = (const u8*) copy;
    s32 lo[3] = { 31, 31, 31 };
    s32 hi[3] = { 0, 0, 0 };
    s32 opaque = -1;
    s32 transparent = -1;
    s32 i, c;

    for (i = SPR_PAL_SIZE - 1; i >= 0; i--) {
        const u16 color = (data[i * 2] << 8) | data[i * 2 + 1];
        const s32 rgb[3] = { (color >> 11) & 0x1F, (color >> 6) & 0x1F, (color >> 1) & 0x1F };
        if (!(color & 1)) {
            transparent = i;
            continue;
        }
        opaque = i;
        for (c = 0; c < 3; c++) {
            lo[c] = MIN(lo[c], rgb[c]);
            hi[c] = MAX(hi[c], rgb[c]);
        }
    }
    if (opaque < 0 || transparent < 0) {
        return;
    }
    for (c = 0; c < 3; c++) {
        if (hi[c] - lo[c] > SILHOUETTE_SPREAD) {
            return;
        }
    }
    gDPPaletteMask(gMainGfxPos++, copy, opaque, transparent);
}

void port_begin_palette_override(PAL_PTR* palettes, PAL_PTR* originals) {
    sOverridePalettes = palettes;
    sOverrideOriginals = get_original_palettes(originals);
    sOverrideSlot = NULL;
}

void port_end_palette_override(void) {
    sOverridePalettes = NULL;
    sOverrideOriginals = NULL;
    sOverrideSlot = NULL;
}

PAL_PTR port_resolve_palette(PAL_PTR* palettes, s32 index) {
    PAL_PTR palette = palettes[index];

    if (palettes != sOverridePalettes || is_named_palette(palette)) {
        return palette;
    }
    PAL_PTR original = find_original_palette(palette, sOverrideOriginals, index);
    if (original != NULL) {
        return original;
    }
    if (index < 0 || index >= RESOLVED_PALETTE_MAX) {
        return palette;
    }
    if (sOverrideSlot == NULL) {
        sOverrideSlot = get_resolved_slot(sOverridePalettes);
        if (sOverrideSlot == NULL) {
            return palette;
        }
    }
    PAL_PTR copy = sOverrideSlot->data[gCurrentDisplayContextIndex & 1][index];
    memcpy(copy, palette, sizeof(PAL_BIN) * SPR_PAL_SIZE);
    if (!emit_blend_tag(palette, copy)) {
        emit_silhouette(copy);
    }
    return copy;
}
}
