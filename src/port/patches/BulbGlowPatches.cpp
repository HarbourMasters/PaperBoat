#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

#include "common.h"
#include "effects_internal.h"
#include "assets/effects.h"
#include "nu/nusys.h"
#include "port/patches/Patches.h"

extern "C" {

// Port reimplementation of bulb_glow_appendGfx (src/effects/bulb_glow.c).

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

#define TMEM_ADDR(x) (x / sizeof(u64))

void port_bulb_glow_appendGfx(void* effect) {
    BulbGlowFXData* data = ((EffectInstance*) effect)->data.bulbGlow;
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
    u16* mirror;
    s32 visLeft, visRight, visWidth;

    // Both tiles are sampled through ONE texture rectangle, so they have to agree
    // on what the shared S coordinate means.
    visLeft = OTRGetRectDimensionFromLeftEdge(0);
    visRight = OTRGetRectDimensionFromRightEdge(0);
    visWidth = visRight - visLeft;
    if (visWidth < 1) {
        visLeft = 0;
        visRight = SCREEN_WIDTH;
        visWidth = SCREEN_WIDTH;
    }

    brightness = data->brightness;
    type = data->type;
    if (brightness > 127) {
        brightness = 127;
    }

    // The ROM passes data->depthQueryID here. The port's depth-query readback
    // needs render-to-texture, so -1 reduces this to a frustum test and the glow
    // ignores occlusion.
    isPointVisible = is_point_visible(data->pos.x, data->pos.y, data->pos.z, -1, &centerX, &centerY);
    if (type == 5) {
        isPointVisible = true;
    }

    // Tested against the visible range, not 0..SCREEN_WIDTH: at wide aspect the
    // ROM's 320-space bounds sit inside the screen, so the glow would pop out
    // well before reaching the edge.
    if (!isPointVisible || centerX < visLeft || centerY < 0.0f || centerX >= visRight || centerY >= SCREEN_HEIGHT) {
        return;
    }

    preset = &D_E0078918[type];
    glowExtent = preset->unk_10;
    rectHeight = preset->unk_14;

    mirror = port_getSceneMirrorSentinel();

    gDPPipeSync(gMainGfxPos++);

    // Snapshot the scene as it stands now, so TEXEL1 is what this glow sits on
    // top of rather than the finished frame.
    port_emitSceneMirrorCapture(&gMainGfxPos);

    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*) effect)->shared->graphics));

    // The per-type display list from ROM: 2-cycle, the additive combiner, the
    // blender, and tile 0 (the glow texture) with its own mask/shift/mirror.
    gSPDisplayList(gMainGfxPos++, D_E0078900[type]);

    color = &D_E00789AC[data->unk_20];
    colorScale = brightness * 2;
    r = color->r * colorScale / 255;
    g = color->g * colorScale / 255;
    b = color->b * colorScale / 255;
    gDPSetPrimColor(gMainGfxPos++, 0, 0, r, g, b, 127);

    xMin = centerX - glowExtent;
    xMax = xMin + glowExtent * 2;
    yMin = centerY - glowExtent;
    yMax = yMin + glowExtent * 2;

    xStart = 0;
    if (xMin < visLeft) {
        xStart = visLeft - xMin;
    }
    yStart = 0;
    if (yMin < 0) {
        yStart = -yMin;
    }
    if (xMax > visRight) {
        xMax = visRight - 1;
    }
    if (yMax > SCREEN_HEIGHT) {
        yMax = SCREEN_HEIGHT - 1;
    }

    // Tile 1 = the whole scene mirror, loaded once
    gDPLoadMultiTile(
        gMainGfxPos++, osVirtualToPhysical(mirror), TMEM_ADDR(TMEM_SIZE / 2), G_TX_RENDERTILE + 1, G_IM_FMT_RGBA,
        G_IM_SIZ_16b, visWidth, SCREEN_HEIGHT, 0, 0, visWidth - 1, SCREEN_HEIGHT - 1, 0, G_TX_CLAMP, G_TX_CLAMP,
        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
    );

    numRects = (yMax - yMin) / rectHeight;

    for (i = yStart / rectHeight; i < numRects; i++) {
        s32 y = yMin + i * rectHeight;

        if (y + rectHeight >= SCREEN_HEIGHT) {
            break;
        }
        if (y < 0) {
            continue;
        }

        // Tile 0 origin, as the ROM sets it, plus `y`: the texture rectangle
        // below passes absolute screen T for the mirror's sake, so tile 0 has to
        // cancel that back out to keep the glow's own vertical placement.
        //
        // The cancellation must be scaled by unk_0C. The RDP applies the tile's
        // shift to the incoming coordinate BEFORE subtracting the origin, so the
        // sampled texel is `unk_0C * T - ULT`; a raw `+ y` therefore only cancels
        // for the types whose shift is 1:1 (2, 4, 5) and leaves `y * (unk_0C - 1)`
        // behind for types 0, 1 and 3, scrolling the glow with its screen Y.
        // unk_08/unk_0C ARE the tile's S/T shift factors - that is why the ROM
        // already pre-scales the S origin by unk_08 on the line above.
        // The S origin is shifted into visible space alongside the rectangle's S,
        // so the two cancel to the ROM's `(x - xMin) * unk_08` at any aspect.
        // Scaling happens inside the cast to keep the quarter-texel field: with
        // unk_0C = 0.5 (type 0) an odd `y` carries a half texel that truncating
        // first would throw away.
        gDPSetTileSize(
            gMainGfxPos++, G_TX_RENDERTILE, (s32) ((xMin - visLeft) * preset->unk_08 * 4),
            (s32) (((preset->unk_04 * 20 - i * preset->unk_14 * preset->unk_0C) + y * preset->unk_0C) * 4),
            (s32) (((xMin - visLeft) * preset->unk_08 + preset->unk_00) * 4),
            (s32) (((preset->unk_04 * 21 - i * preset->unk_14 * preset->unk_0C) + y * preset->unk_0C) * 4)
        );

        // Visible-space S, absolute screen T, and dsdx/dtdy left at 1:1 so both
        // tiles advance one texel per screen pixel. Wide variant because xMin can
        // legitimately be negative once the glow reaches the widescreen gutter.
        gSPWideTextureRectangle(
            gMainGfxPos++, (xMin + xStart) * 4, y * 4, xMax * 4, (y + rectHeight) * 4, G_TX_RENDERTILE,
            (xMin + xStart - visLeft) << 5, y << 5, 1 << 10, 1 << 10
        );
        gDPPipeSync(gMainGfxPos++);
    }
}
}
