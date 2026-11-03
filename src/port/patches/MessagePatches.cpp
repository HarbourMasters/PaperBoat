#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

#include "common.h"
#include "port/patches/Patches.h"

extern "C" {

extern IMG_BIN MsgCharImgNormal[];
extern IMG_BIN MsgCharImgTitle[];
extern IMG_BIN MsgCharImgSubtitle[];
extern PAL_BIN D_802F4560[80][8];

typedef struct GlyphSheet {
    const u8* base;
    u32 size;
    u32 glyphBytes;
    const char* prefix;
    char** paths;
    u32 count;
} GlyphSheet;

static char* sStandardPaths[0x5100 / 128];
static char* sTitlePaths[0xF60 / 96];
static char* sSubtitlePaths[0xB88 / 72];

static GlyphSheet sSheets[] = {
    { (const u8*) MsgCharImgNormal, 0x5100, 128, "__OTR__charset/charset_standard_", sStandardPaths,
      ARRAY_COUNT(sStandardPaths) },
    { (const u8*) MsgCharImgTitle, 0xF60, 96, "__OTR__charset/charset_title_", sTitlePaths, ARRAY_COUNT(sTitlePaths) },
    { (const u8*) MsgCharImgSubtitle, 0xB88, 72, "__OTR__charset/charset_subtitle_", sSubtitlePaths,
      ARRAY_COUNT(sSubtitlePaths) },
};

// load_font fills D_802F4560 from one of two palette tables; remember which so
// the palette paths point at the right one.
static const char* sPalettePrefix = "__OTR__charset/charset_standard_palette_";
static char* sPalettePaths[2][80];
static s32 sPaletteSet = 0;

static char* intern_path(const char* prefix, u32 index) {
    char path[80];
    char* copy;

    snprintf(path, sizeof(path), "%s%u", prefix, index);
    if (GameEngine_GetDataExact(path) == NULL) {
        return NULL;
    }
    copy = (char*) malloc(strlen(path) + 1);
    strcpy(copy, path);
    return copy;
}

void port_msg_font_loaded(s32 font) {
    sPaletteSet = font == 1 ? 1 : 0;
    sPalettePrefix =
        font == 1 ? "__OTR__charset/charset_subtitle_palette_" : "__OTR__charset/charset_standard_palette_";
}

IMG_PTR port_msg_glyph_raster(IMG_PTR glyph) {
    const u8* p = (const u8*) glyph;
    s32 i;

    for (i = 0; i < (s32) ARRAY_COUNT(sSheets); i++) {
        GlyphSheet* sheet = &sSheets[i];
        if (p >= sheet->base && p < sheet->base + sheet->size) {
            u32 index = (u32) (p - sheet->base) / sheet->glyphBytes;
            if (index >= sheet->count) {
                return glyph;
            }
            if (sheet->paths[index] == NULL) {
                sheet->paths[index] = intern_path(sheet->prefix, index);
                if (sheet->paths[index] == NULL) {
                    sheet->paths[index] = (char*) glyph;
                }
            }
            return (IMG_PTR) sheet->paths[index];
        }
    }
    return glyph;
}

PAL_PTR port_msg_glyph_palette(PAL_PTR palette) {
    const u8* p = (const u8*) palette;
    const u8* base = (const u8*) D_802F4560;
    u32 index;

    if (p < base || p >= base + sizeof(D_802F4560)) {
        return palette;
    }
    index = (u32) (p - base) / sizeof(D_802F4560[0]);
    if (index >= ARRAY_COUNT(sPalettePaths[0])) {
        return palette;
    }
    if (sPalettePaths[sPaletteSet][index] == NULL) {
        sPalettePaths[sPaletteSet][index] = intern_path(sPalettePrefix, index);
        if (sPalettePaths[sPaletteSet][index] == NULL) {
            sPalettePaths[sPaletteSet][index] = (char*) palette;
        }
    }
    return (PAL_PTR) sPalettePaths[sPaletteSet][index];
}

void* port_msg_override(const char* name, void* fallback) {
    void* data;

    if (name == NULL) {
        return fallback;
    }
    data = ResourceGetDataByName(name);
    return data != NULL ? data : fallback;
}

// filemenu/layout: u16 version, u16 count, s16 values[count] (LE). v1 = FM_LAYOUT_COUNT entries.
s32 port_filemenu_layout(s32 id, s32 fallback) {
    static s16 sValues[FM_LAYOUT_COUNT];
    static s32 sReady = -1;

    if (sReady < 0) {
        u8* data = (u8*)ResourceGetDataByName("__OTR__filemenu/layout");
        sReady = 0;
        if (data != NULL) {
            u16 version = data[0] | (data[1] << 8);
            u16 count = data[2] | (data[3] << 8);
            if (version == 1 && count > 0) {
                s32 n = count < FM_LAYOUT_COUNT ? count : FM_LAYOUT_COUNT;
                s32 i;

                for (i = 0; i < n; i++) {
                    u8* p = data + 4 + i * 2;
                    sValues[i] = (s16)(p[0] | (p[1] << 8));
                }
                for (; i < FM_LAYOUT_COUNT; i++) {
                    sValues[i] = 0x7FFF; // unset → use fallback
                }
                sReady = 1;
            }
        }
    }

    if (sReady == 1 && id >= 0 && id < FM_LAYOUT_COUNT && sValues[id] != 0x7FFF) {
        return sValues[id];
    }
    return fallback;
}
}
