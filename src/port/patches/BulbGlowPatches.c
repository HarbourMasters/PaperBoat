#include "common.h"
#include "effects_internal.h"
#include "assets/effects.h"
#include "nu/nusys.h"
#include "port/Engine.h"
#include "port/patches/Patches.h"

// Port reimplementation of bulb_glow_appendGfx (src/effects/bulb_glow.c).
// Used in Watt power shock attack + General Guy bulb.

typedef struct UnkBulbGlow {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} UnkBulbGlow;

extern const char* D_E0078900[];
extern UnkBulbGlow D_E0078918[];
extern Color_RGB8 D_E00789AC[];

// Bulb glow disc textures from effect_gfx_bulb_glow.yml
extern const char D_09000000_37ADD0[]; // tex_0
extern const char D_09000C00_37B9D0[]; // tex_C00

#define TMEM_ADDR(x) (x / sizeof(u64))

void port_bulb_glow_appendGfx(void* effect) {
    BulbGlowFXData* data = ((EffectInstance*)effect)->data.bulbGlow;
    f32 centerX;
    f32 centerY;
    s32 xMin, xMax, yMin, yMax;
    s32 xStart, yStart;
    s32 numRects;
    s32 type;
    s32 rectHeight;
    s32 glowExtent;
    s32 colorScale;
    s32 brightness;
    s32 isPointVisible;
    UnkBulbGlow* preset;
    Color_RGB8* color;
    u8 r, g, b;
    s32 i;
    u16* prevGfxCfb;

    brightness = data->brightness;
    type = data->type;
    if (brightness > 127) {
        brightness = 127;
    }

    isPointVisible = is_point_visible(data->pos.x, data->pos.y, data->pos.z,
                                      -1, &centerX, &centerY);
    if (type == 5) {
        isPointVisible = true;
    }
    if (!isPointVisible || centerX < 0.0f || centerY < 0.0f
        || centerX >= SCREEN_WIDTH || centerY >= SCREEN_HEIGHT) {
        return;
    }

    preset = &D_E0078918[type];
    glowExtent = preset->unk_10;
    rectHeight = preset->unk_14;

    // Watt's power shock attack
    if (type == 0) {
        gDPPipeSync(gMainGfxPos++);
        gSPSegment(gMainGfxPos++, 0x09,
                   VIRTUAL_TO_PHYSICAL(((EffectInstance*)effect)->shared->graphics));

        colorScale = brightness * 2;
        r = 255 * colorScale / 255;
        g = 255 * colorScale / 255;
        b = 64  * colorScale / 255;

        gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
        gDPSetTexturePersp(gMainGfxPos++, G_TP_NONE);
        gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
        gDPSetTextureFilter(gMainGfxPos++, G_TF_BILERP);
        gDPSetCombineMode(gMainGfxPos++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetRenderMode(gMainGfxPos++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gMainGfxPos++, 0, 0, r, g, b, brightness * 2);

        xMin = centerX - glowExtent;
        xMax = xMin + glowExtent * 2;
        yMin = centerY - glowExtent;
        yMax = yMin + glowExtent * 2;
        xStart = 0;
        if (xMin < 0) { xStart = -xMin; }
        yStart = 0;
        if (yMin < 0) { yStart = -yMin; }
        if (xMax > SCREEN_WIDTH)  xMax = SCREEN_WIDTH  - 1;
        if (yMax > SCREEN_HEIGHT) yMax = SCREEN_HEIGHT - 1;

        // Disc texture as alpha mask. tex_C00 is the bigger I4 64x64 disc.
        gSPTexture(gMainGfxPos++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gDPLoadTextureBlock_4b(gMainGfxPos++, D_09000C00_37B9D0, G_IM_FMT_I,
                               64, 64, 0,
                               G_TX_CLAMP, G_TX_CLAMP, 6, 6,
                               G_TX_NOLOD, G_TX_NOLOD);

        {
            s32 dsdx = (64 << 10) / (glowExtent * 2);
            s32 dtdy = (64 << 10) / (glowExtent * 2);
            gSPTextureRectangle(gMainGfxPos++,
                (xMin + xStart) * 4, (yMin + yStart) * 4,
                xMax * 4, yMax * 4,
                G_TX_RENDERTILE,
                xStart * dsdx >> 5, yStart * dtdy >> 5,
                dsdx, dtdy);
        }
        gDPPipeSync(gMainGfxPos++);
        return;
    }

    prevGfxCfb = port_getPrevFrameSentinel();
    port_requestPrevFrameCapture();

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09,
               VIRTUAL_TO_PHYSICAL(((EffectInstance*)effect)->shared->graphics));

    gSPDisplayList(gMainGfxPos++, D_E0078900[type]);

    color = &D_E00789AC[data->unk_20];
    colorScale = brightness * 2;
    r = color->r * colorScale / 255;
    g = color->g * colorScale / 255;
    b = color->b * colorScale / 255;
    gDPSetPrimColor(gMainGfxPos++, 0, 0, r, g, b, 220);

    xMin = centerX - glowExtent;
    xMax = xMin + glowExtent * 2;
    yMin = centerY - glowExtent;
    yMax = yMin + glowExtent * 2;

    xStart = 0;
    if (xMin < 0) {
        xStart = -xMin;
    }
    yStart = 0;
    if (yMin < 0) {
        yStart = -yMin;
    }
    if (xMax > SCREEN_WIDTH) {
        xMax = SCREEN_WIDTH - 1;
    }
    if (yMax > SCREEN_HEIGHT) {
        yMax = SCREEN_HEIGHT - 1;
    }

    numRects = (yMax - yMin) / rectHeight;

    for (i = yStart / rectHeight; i < numRects; i++) {
        s32 y = yMin + i * rectHeight;
        if (y + rectHeight >= SCREEN_HEIGHT) {
            break;
        }

        if (y < 0) {
            continue;
        }

        gDPSetTileSize(gMainGfxPos++, G_TX_RENDERTILE,
            (s32)(xMin * preset->unk_08) * 4,
            (s32)((preset->unk_04 * 20 - i * preset->unk_14 * preset->unk_0C) + y) * 4,
            (s32)(xMin * preset->unk_08 + preset->unk_00) * 4,
            (s32)((preset->unk_04 * 21 - i * preset->unk_14 * preset->unk_0C) + y) * 4);

        gDPLoadMultiTile(gMainGfxPos++,
            VIRTUAL_TO_PHYSICAL(prevGfxCfb),
            TMEM_ADDR(TMEM_SIZE / 2), G_TX_RENDERTILE + 1,
            G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, SCREEN_HEIGHT,
            xMin + xStart, y, xMax - 1, y + rectHeight - 1,
            0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
            9, 8, G_TX_NOLOD, G_TX_NOLOD);

        gSPTextureRectangle(gMainGfxPos++,
            (xMin + xStart) * 4, y * 4,
            xMax * 4, (y + rectHeight) * 4,
            G_TX_RENDERTILE,
            ((xMin + xStart) & 0x1FF) << 5, y << 5,
            1 << 10, 1 << 10);
        gDPPipeSync(gMainGfxPos++);
    }
}
