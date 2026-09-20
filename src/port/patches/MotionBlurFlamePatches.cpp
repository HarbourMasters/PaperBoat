#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

#include "common.h"
#include "effects_internal.h"
#include "assets/effects.h"
#include "nu/nusys.h"
#include "port/patches/Patches.h"

extern "C" {

// Port-side reimplementation of motion_blur_flame_appendGfx

// Mirror of D_E00A29DC in motion_blur_flame.c.
typedef struct MotionBlurFlamePreset {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s32 halfSize;
    /* 0x14 */ s32 bandHeight;
} MotionBlurFlamePreset;

extern const char* D_E00A29D0[];
extern MotionBlurFlamePreset D_E00A29DC[];
extern s32 D_E00A2A24[];

#define MBF_TEX_SIZE 16

void port_motion_blur_flame_appendGfx(void* effect) {
    MotionBlurFlameFXData* data = ((EffectInstance*) effect)->data.motionBlurFlame;
    s32 type = data->unk_00;
    MotionBlurFlamePreset* preset = &D_E00A29DC[type];
    s32 intensity = data->unk_4C;
    s32 visible[UNK_ARRAY_SIZE_1];
    f32 screenX[UNK_ARRAY_SIZE_1];
    f32 screenY[UNK_ARRAY_SIZE_1];
    s32 i;

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*) effect)->shared->graphics));

    // Loads the noise texture into TMEM 0 on tile 0 and sets 2-cycle, point
    // filtering and the G_RM_PASS / G_RM_CLD_SURF2 blender.
    gSPDisplayList(gMainGfxPos++, D_E00A29D0[type]);

    // Second descriptor over the same TMEM, so the cycle-1 texel fetch reads the
    // noise whichever slot the 2-cycle texel swap resolves to.
    gDPSetTile(
        gMainGfxPos++, G_IM_FMT_I, G_IM_SIZ_8b, MBF_TEX_SIZE / 8, 0, G_TX_RENDERTILE + 1, 0, G_TX_NOMIRROR | G_TX_WRAP,
        4, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD
    );
    gDPSetTileSize(
        gMainGfxPos++, G_TX_RENDERTILE + 1, 0, 0, (MBF_TEX_SIZE - 1) << G_TEXTURE_IMAGE_FRAC,
        (MBF_TEX_SIZE - 1) << G_TEXTURE_IMAGE_FRAC
    );

    // colour: cycle 0 is the hardware's k, cycle 1 turns it into noise * (k + 1)
    // alpha:  the texture itself, so the box has no edge
    gDPSetCombineLERP(
        gMainGfxPos++, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, 0, 0, 0, TEXEL0, COMBINED, 0, TEXEL0, TEXEL0, 0, 0, 0,
        COMBINED
    );

    for (i = 0; i < UNK_ARRAY_SIZE_1; i++) {
        f32 posX = data->unk_1C[i];
        f32 posY = data->unk_2C[i];
        f32 posZ = data->unk_3C[i];
        f32 sx;
        f32 sy;
        s32 vis;

        if (i == 0) {
            vis = is_point_visible(posX, posY, posZ, -1, &sx, &sy);
        } else {
            // Entries 1..3 are the trail
            vis = posZ;
            sx = posX;
            sy = posY;
        }

        visible[i] = vis;
        screenX[i] = sx;
        screenY[i] = sy;

        if (vis != 0 && !(sx < 0.0f) && !(sy < 0.0f) && !(sx >= SCREEN_WIDTH) && !(sy >= SCREEN_HEIGHT)) {
            s32 scale = (intensity * D_E00A2A24[i]) / 100;
            s32 midR = (data->unk_5C * scale) >> 9;
            s32 midG = (data->unk_60 * scale) >> 9;
            s32 midB = (data->unk_64 * scale) >> 9;

            s32 primR = (midR * scale) >> 8;
            s32 primG = (midG * scale) >> 8;
            s32 primB = (midB * scale) >> 8;

            s32 envR = midR + 32;
            s32 envG = midG + 32;
            s32 envB = midB + 32;

            s32 halfSize = preset->halfSize;
            s32 boxLeft = sx - halfSize;
            s32 boxTop = sy - halfSize;
            s32 clipLeft = (boxLeft < 0) ? -boxLeft : 0;
            s32 clipTop = (boxTop < 0) ? -boxTop : 0;
            s32 boxRight = boxLeft + halfSize * 2;
            s32 boxBottom = boxTop + halfSize * 2;

            if (envR > 127) {
                envR = 127;
            }
            if (envG > 127) {
                envG = 127;
            }
            if (envB > 127) {
                envB = 127;
            }

            if (boxRight > SCREEN_WIDTH) {
                boxRight = SCREEN_WIDTH - 1;
            }
            if (boxBottom > SCREEN_HEIGHT) {
                boxBottom = SCREEN_HEIGHT - 1;
            }
            if (boxLeft + clipLeft >= boxRight || boxTop + clipTop >= boxBottom) {
                continue;
            }

            gDPSetPrimColor(gMainGfxPos++, 0, 0, primR, primG, primB, 255);
            gDPSetEnvColor(gMainGfxPos++, envR, envG, envB, 255);

            // Tile origin is 0,0, so the clipped corner indexes straight into
            // the texture and the box stays anchored to the unclipped origin
            gSPTextureRectangle(
                gMainGfxPos++, (boxLeft + clipLeft) * 4, (boxTop + clipTop) * 4, boxRight * 4, boxBottom * 4,
                G_TX_RENDERTILE, clipLeft << 5, clipTop << 5, 1 << 10, 1 << 10
            );
            gDPPipeSync(gMainGfxPos++);
        }
    }

    // Shift this frame's projection into the trail
    for (i = 0; i < ARRAY_COUNT(data->unk_3C) - 1; i++) {
        data->unk_3C[i + 1] = visible[i];
        data->unk_1C[i + 1] = screenX[i];
        data->unk_2C[i + 1] = screenY[i];
    }
}

}
