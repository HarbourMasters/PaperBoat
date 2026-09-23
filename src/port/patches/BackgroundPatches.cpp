#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

// Port reimplementation of load_map_bg / appendGfx_background_texture (src/background.c).

#include "common.h"
#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "port/patches/Patches.h"
#include "alignment.h"

extern "C" {

extern char gCloudyFlowerFieldsBg[];
extern char gSunnyFlowerFieldsBg[];
extern s8 gBackroundWaveEnabled;
extern s8 gBackroundNoTileFill;
extern f32 gBackroundWavePhase;
extern f32 gBackroundLastScrollValue;
extern PAL_BIN gBackgroundPalette[256];

u16 blend_background_channel(u16 arg0, s32 arg1, s32 alpha);

// Fast3D memoizes by path pointer, so each background needs its own stable string:
// a shared buffer would leave every map after the first drawing the previous texture.
#define MAX_BG_PATHS 64

static char* bg_intern_path(const char* path) {
    static char* sPaths[MAX_BG_PATHS];
    static s32 sPathCount = 0;
    s32 i;

    for (i = 0; i < sPathCount; i++) {
        if (strcmp(sPaths[i], path) == 0) {
            return sPaths[i];
        }
    }
    if (sPathCount >= MAX_BG_PATHS) {
        return NULL;
    }
    sPaths[sPathCount] = (char*) malloc(strlen(path) + 1);
    strcpy(sPaths[sPathCount], path);
    return sPaths[sPathCount++];
}

static char* sBgRasterPath = NULL;
char* gBgPalettePath = NULL;

void port_load_map_bg(char* optAssetName) {
    if (optAssetName == NULL) {
        return;
    }

    char* assetName = optAssetName;

    if (evt_get_variable(NULL, GB_StoryProgress) >= STORY_CH6_DESTROYED_PUFF_PUFF_MACHINE) {
        if (strcmp(assetName, gCloudyFlowerFieldsBg) == 0) {
            assetName = gSunnyFlowerFieldsBg;
        }
    }

    char rasterPath[64];
    char palettePath[64];

    snprintf(rasterPath, sizeof(rasterPath), "__OTR__backgrounds/%s", assetName);
    snprintf(palettePath, sizeof(palettePath), "__OTR__backgrounds/%s_pal0", assetName);
    sBgRasterPath = bg_intern_path(rasterPath);
    gBgPalettePath = bg_intern_path(palettePath);
    if (sBgRasterPath == NULL || gBgPalettePath == NULL) {
        return;
    }

    gBackgroundImage.raster = (IMG_PTR) sBgRasterPath;

    // CPU-side fog/tint blending
    u8* palData = (u8*) GameEngine_GetDataExact(gBgPalettePath);
    gBackgroundImage.palette = (PAL_PTR) palData;

    gBackgroundImage.width = GameEngine_GetTexWidthExact(sBgRasterPath);
    gBackgroundImage.height = GameEngine_GetTexHeightExact(sBgRasterPath);
    gBackgroundImage.startX = 12;
    gBackgroundImage.startY = 20;
}

void port_appendGfx_background_texture(void) {
    Camera* cam = &gCameras[gCurrentCameraID];
    u16 flags = 0;
    s32 fogR, fogG, fogB, fogA;
    u8 r1, g1, b1, a1;
    u8 r2, g2, b2;
    u16 blendedR, blendedG, blendedB;
    s32 i;

    f32 theta, sinTheta, cosTheta, scrollValue, f5, waveOffset;

    s32 bgMinX;
    s32 bgMinY;
    s32 bgMaxX;
    s32 bgMaxY;
    s32 lineHeight;
    s32 numLines;
    s32 extraHeight;

    s32 bgXOffset;
    f32 bgScrollF;

    enum {
        BG_BLEND_NONE = 0,
        BG_BLEND_HAS_FOG = 1,
        BG_BLEND_SHOULD_LERP = 2,
        BG_BLEND_SHOULD_BLEND = 4,
    };

    if (is_world_fog_enabled()) {
        get_world_fog_color(&fogR, &fogG, &fogB, &fogA);
        flags = BG_BLEND_HAS_FOG;
        fogA = gGameStatusPtr->backgroundDarkness;
    }

    switch (*gBackgroundTintModePtr) {
        case ENV_TINT_NONE:
        case ENV_TINT_SHROUD:
            mdl_get_shroud_tint_params(&r1, &g1, &b1, &a1);
            if (a1 != 0) {
                flags |= BG_BLEND_SHOULD_LERP;
            }
            break;
        case ENV_TINT_DEPTH:
        case ENV_TINT_REMAP:
        default:
            mdl_get_remap_tint_params(&r1, &g1, &b1, &r2, &g2, &b2);
            if (!(r1 == 255 && g1 == 255 && b1 == 255 && r2 == 0 && g2 == 0 && b2 == 0)) {
                flags |= BG_BLEND_SHOULD_BLEND;
            }
            break;
    }

    switch (flags) {
        case BG_BLEND_NONE:
            gGameStatusPtr->backgroundFlags &= ~BACKGROUND_FLAG_FOG;
            break;
        case BG_BLEND_HAS_FOG:
            gGameStatusPtr->backgroundFlags |= BACKGROUND_FLAG_FOG;
            break;
        case BG_BLEND_SHOULD_LERP:
            gGameStatusPtr->backgroundFlags |= BACKGROUND_FLAG_FOG;
            fogR = r1;
            fogG = g1;
            fogB = b1;
            fogA = a1;
            break;
        case BG_BLEND_HAS_FOG | BG_BLEND_SHOULD_LERP:
            gGameStatusPtr->backgroundFlags |= BACKGROUND_FLAG_FOG;
            fogR = (fogR * (255 - a1) + r1 * a1) / 255;
            fogG = (fogG * (255 - a1) + g1 * a1) / 255;
            fogB = (fogB * (255 - a1) + b1 * a1) / 255;
            fogA = (fogA * (255 - a1) + a1 * a1) / 255;
            break;
        case BG_BLEND_SHOULD_BLEND:
            gGameStatusPtr->backgroundFlags |= BACKGROUND_FLAG_FOG;
            break;
    }

    if (gGameStatusPtr->backgroundFlags & BACKGROUND_FLAG_FOG) {
        switch (*gBackgroundTintModePtr) {
            case ENV_TINT_NONE:
            case ENV_TINT_SHROUD:
                if (fogA == 255) {
                    for (i = 0; i < ARRAY_COUNT(gBackgroundPalette); i++) {
                        gBackgroundPalette[i] = PACK_PAL_RGBA(0, 0, 0, 1);
                    }
                } else {
                    for (i = 0; i < ARRAY_COUNT(gBackgroundPalette); i++) {
                        u16 palColor = gGameStatusPtr->backgroundPalette[i];
                        blendedB = blend_background_channel(UNPACK_PAL_B(palColor), fogB >> 3, fogA);
                        blendedG = blend_background_channel(UNPACK_PAL_G(palColor), fogG >> 3, fogA);
                        blendedR = blend_background_channel(UNPACK_PAL_R(palColor), fogR >> 3, fogA);
                        gBackgroundPalette[i] = PACK_PAL_RGBA(blendedR, blendedG, blendedB, 1);
                    }
                }
                break;
            case ENV_TINT_DEPTH:
            case ENV_TINT_REMAP:
            default:
                for (i = 0; i < ARRAY_COUNT(gBackgroundPalette); i++) {
                    u16 palColor = gGameStatusPtr->backgroundPalette[i];
                    blendedB = (b2 >> 3) + ((UNPACK_PAL_B(palColor) * b1 >> 3) >> 5);
                    blendedG = (g2 >> 3) + ((UNPACK_PAL_G(palColor) * g1 >> 3) >> 5);
                    blendedR = (r2 >> 3) + ((UNPACK_PAL_R(palColor) * r1 >> 3) >> 5);

                    if (blendedB > 0x1F) {
                        blendedB = 0x1F;
                    }
                    if (blendedG > 0x1F) {
                        blendedG = 0x1F;
                    }
                    if (blendedR > 0x1F) {
                        blendedR = 0x1F;
                    }
                    gBackgroundPalette[i] = PACK_PAL_RGBA(blendedR, blendedG, blendedB, 1);
                }
                break;
        }
    }

    bgMaxX = gGameStatusPtr->backgroundMaxX;
    bgMaxY = gGameStatusPtr->backgroundMaxY;
    bgMinX = gGameStatusPtr->backgroundMinX;
    bgMinY = gGameStatusPtr->backgroundMinY;

    s32 bgScaleNum = 1;
    s32 bgScaleDen = 1;
    s32 bgTopY = bgMinY;
    s32 bgBotY = bgMinY + bgMaxY;
    s32 bgDtdy;

    if (bgMaxY > 0 && port_cam_full_height(gCurrentCameraID)) {
        bgScaleNum = cam->viewportH;
        bgScaleDen = bgMaxY;
        bgTopY = cam->viewportStartY;
        bgBotY = cam->viewportStartY + cam->viewportH;
    }

    bgDtdy = 1024 * bgScaleDen / bgScaleNum;

    theta = clamp_angle(-cam->curBoomYaw);
    sinTheta = sin_deg(theta);
    cosTheta = cos_deg(theta);
    f5 = cosTheta * cam->lookAt_obj.x - sinTheta * cam->lookAt_obj.z + cam->leadAmount;
    scrollValue = -f5 * 0.25f;
    scrollValue += bgMaxX * theta * (1 / 90.0f);

    if (fabsf(scrollValue - gBackroundLastScrollValue) < 0.02f) {
        scrollValue = gBackroundLastScrollValue;
    } else {
        gBackroundLastScrollValue = scrollValue;
    }

    while (scrollValue < 0.0f) {
        scrollValue += bgMaxX * 32;
    }

    bgScrollF = fmodf(scrollValue, (f32) bgMaxX);
    bgXOffset = gGameStatusPtr->backgroundXOffset = (s32) bgScrollF;

    // Title screen (widescreen): fill the camera's frame solid first;
    // the bg image is then drawn once on top of the center.
    if (gBackroundNoTileFill) {
        s32 fillLeft;
        s32 fillRight;

        get_cam_frame_x(gCurrentCameraID, &fillLeft, &fillRight);
        gDPPipeSync(gMainGfxPos++);
        gDPSetCycleType(gMainGfxPos++, G_CYC_FILL);
        gDPSetRenderMode(gMainGfxPos++, G_RM_NOOP, G_RM_NOOP2);
        gDPSetFillColor(gMainGfxPos++, PACK_FILL_COLOR(255, 255, 255, 1));
        gDPFillWideRectangle(gMainGfxPos++, fillLeft, bgTopY, fillRight - 1, bgBotY - 1);
        gDPPipeSync(gMainGfxPos++);
    }

    gDPPipeSync(gMainGfxPos++);
    gDPSetTexturePersp(gMainGfxPos++, G_TP_NONE);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    gDPSetTextureFilter(gMainGfxPos++, G_TF_POINT);

    // Always the background's own palette, loaded by name so a replacement can key on it.
    // Fog and tint used to be baked into the palette on the CPU; they're per-channel
    // scales, so the combiner does the same job — and it works on replacement art too.
    s32 bgDsdx = 4096; // copy mode steps four texels per pixel
    s32 bgEdge = 0;
    if (!(gGameStatusPtr->backgroundFlags & BACKGROUND_FLAG_FOG)) {
        gDPSetCycleType(gMainGfxPos++, G_CYC_COPY);
        gDPSetCombineMode(gMainGfxPos++, G_CC_DECALRGB, G_CC_DECALRGB);
        gDPSetRenderMode(gMainGfxPos++, G_RM_NOOP, G_RM_NOOP2);
    } else {
        bgDsdx = 1024;
        bgEdge = 4;
        gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
        gDPSetRenderMode(gMainGfxPos++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        switch (*gBackgroundTintModePtr) {
            case ENV_TINT_NONE:
            case ENV_TINT_SHROUD:
                if (fogA == 255) {
                    gDPSetPrimColor(gMainGfxPos++, 0, 0, 0, 0, 0, 255);
                } else {
                    gDPSetPrimColor(gMainGfxPos++, 0, 0, fogR, fogG, fogB, fogA);
                }
                gDPSetCombineLERP(
                    gMainGfxPos++, PRIMITIVE, TEXEL0, PRIMITIVE_ALPHA, TEXEL0, 0, 0, 0, 1, PRIMITIVE, TEXEL0,
                    PRIMITIVE_ALPHA, TEXEL0, 0, 0, 0, 1
                );
                break;
            case ENV_TINT_DEPTH:
            case ENV_TINT_REMAP:
            default:
                // channels remapped to [offset, offset + scale]: texel * prim + env
                gDPSetPrimColor(gMainGfxPos++, 0, 0, r1, g1, b1, 255);
                gDPSetEnvColor(gMainGfxPos++, r2, g2, b2, 255);
                gDPSetCombineLERP(
                    gMainGfxPos++, TEXEL0, 0, PRIMITIVE, ENVIRONMENT, 0, 0, 0, 1, TEXEL0, 0, PRIMITIVE, ENVIRONMENT, 0,
                    0, 0, 1
                );
                break;
        }
    }
    gDPPipeSync(gMainGfxPos++);
    gDPLoadTLUT_pal256(gMainGfxPos++, gBgPalettePath);

    gDPLoadTextureTile(
        gMainGfxPos++, gGameStatusPtr->backgroundRaster, G_IM_FMT_CI, G_IM_SIZ_8b, bgMaxX, bgMaxY, 0, 0, bgMaxX - 1,
        bgMaxY - 1, 0, G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
    );

    if (!gBackroundWaveEnabled) {
        // Widescreen: tile the scrolling background across the camera's frame.
        // Two rectangles per tile handle the horizontal scroll wrap.
        s32 wsLeft;
        s32 wsRight;
        s32 tx, bgTileBaseX = bgMinX;

        s32 bgStepX = bgMaxX * bgScaleNum / bgScaleDen;
        s32 bgSplitX4 = (s32) (bgScrollF * 4.0f * bgScaleNum / bgScaleDen);
        s32 bgScrollS = (s32) ((bgMaxX - bgScrollF) * 32.0f);

        bgDsdx = bgDsdx * bgScaleDen / bgScaleNum;

        get_cam_frame_x(gCurrentCameraID, &wsLeft, &wsRight);

        if (gBackroundNoTileFill) {
            // Title screen: draw the image exactly once at its native position;
            // the side bands were already filled solid above.
            wsRight = bgMinX + bgStepX;
        } else {
            while (bgTileBaseX > wsLeft) {
                bgTileBaseX -= bgStepX;
            }
        }

        for (tx = bgTileBaseX; tx < wsRight; tx += bgStepX) {
            gSPWideTextureRectangle(
                gMainGfxPos++, tx * 4, bgTopY * 4, tx * 4 + bgSplitX4 - 4 + bgEdge, (bgBotY - 1) * 4 + bgEdge,
                G_TX_RENDERTILE, bgScrollS, 0, bgDsdx, bgDtdy
            );
            gSPWideTextureRectangle(
                gMainGfxPos++, tx * 4 + bgSplitX4, bgTopY * 4, (bgStepX + tx - 1) * 4 + bgEdge,
                (bgBotY - 1) * 4 + bgEdge, G_TX_RENDERTILE, 0, 0, bgDsdx, bgDtdy
            );
        }
    } else {
        // Wave: per-strip rectangles with sine-based horizontal offset
        s32 stripTop, stripBot;

        lineHeight = 6;
        numLines = bgMaxY / lineHeight;
        extraHeight = bgMaxY % lineHeight;
        gBackroundWavePhase += TAU / 60; // 60 frames period
        for (i = 0; i < numLines; i++) {
            waveOffset = sin_rad(gBackroundWavePhase + i * (TAU / 15)) * 3.0f;
            bgXOffset = 2.0f * (gGameStatusPtr->backgroundXOffset + waveOffset);
            stripTop = bgTopY + lineHeight * i * bgScaleNum / bgScaleDen;
            stripBot = bgTopY + lineHeight * (i + 1) * bgScaleNum / bgScaleDen;
            gSPTextureRectangle(
                gMainGfxPos++, bgMinX * 4, stripTop * 4, (2 * bgXOffset + (bgMinX - 1)) * 4 + bgEdge,
                (stripBot - 1) * 4 + bgEdge, G_TX_RENDERTILE, bgMaxX * 32 - bgXOffset * 16, (lineHeight * i) * 32,
                bgDsdx, bgDtdy
            );
            gSPTextureRectangle(
                gMainGfxPos++, bgXOffset * 2 + bgMinX * 4, stripTop * 4, (bgMaxX + bgMinX - 1) * 4 + bgEdge,
                (stripBot - 1) * 4 + bgEdge, G_TX_RENDERTILE, 0, (lineHeight * i) * 32, bgDsdx, bgDtdy
            );
        }
        if (extraHeight != 0) {
            waveOffset = sin_rad(gBackroundWavePhase + i * (TAU / 15)) * 3.0f;
            bgXOffset = 2.0f * (gGameStatusPtr->backgroundXOffset + waveOffset);
            stripTop = bgTopY + lineHeight * i * bgScaleNum / bgScaleDen;
            gSPTextureRectangle(
                gMainGfxPos++, bgMinX * 4, stripTop * 4, (2 * bgXOffset + (bgMinX - 1)) * 4 + bgEdge,
                (bgBotY - 1) * 4 + bgEdge, G_TX_RENDERTILE, bgMaxX * 32 - bgXOffset * 16, (lineHeight * i) * 32, bgDsdx,
                bgDtdy
            );
            gSPTextureRectangle(
                gMainGfxPos++, bgXOffset * 2 + bgMinX * 4, stripTop * 4, (bgMaxX + bgMinX - 1) * 4 + bgEdge,
                (bgBotY - 1) * 4 + bgEdge, G_TX_RENDERTILE, 0, (lineHeight * i) * 32, bgDsdx, bgDtdy
            );
        }
    }
}
}
