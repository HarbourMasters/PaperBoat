#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

#include "common.h"
#include "effects_internal.h"
#include "assets/effects.h"
#include "port/patches/Patches.h"

extern "C" {

// Port reimplementation of flashing_box_shockwave_appendGfx
// (src/effects/flashing_box_shockwave.c).
//
// Theory: The original branch for FX_SHOCK_OVERLAY_SHOCK_HIT / FX_SHOCK_OVERLAY_LIGHTNING_WORLD
// emitted gSPDisplayList(D_09000600_3936A0), which is a ROM DL containing a buggy
// LOADBLOCK lrs=124, dxt=124 -> only ~125 of 1024 bytes of the I8 32x32 texture are
// loaded, and the DL is 2-CYCLE with an unbound tile-1. On N64 the rectangle was
// effectively invisible and the visible "yellow silhouette on shock" came from the
// actor's STATIC status palette (set_actor_pal_adjustment(ACTOR_PAL_ADJUST_STATIC) ->
// STATIC_BRIGHT yellow), not from this overlay. Reproducing the buggy load on port
// produces a visible garbage rectangle, so:
//
//   - For SHOCK_HIT: skip the rectangle quad entirely — matches N64 visual.
//   - For LIGHTNING_WORLD: emit a clean 1-CYCLE full-texture load with the ROM's
//     intended combiner.

void port_flashing_box_shockwave_appendGfx(void* effect) {
    ShockOverlayFXData* data = ((EffectInstance*) effect)->data.flashingBoxShockwave;
    s32 type = data->type;
    s32 time = data->lifetime;
    Matrix4f mtxTransform;
    Matrix4f mtxUnkScale;
    Matrix4f mtxCamRot;

    guRotateF(mtxCamRot, -gCameras[gCurrentCameraID].curYaw, 0.0f, 1.0f, 0.0f);

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*) effect)->shared->graphics));

    guTranslateF(mtxTransform, data->pos.x, data->pos.y, data->pos.z);
    guMtxCatF(mtxCamRot, mtxTransform, mtxTransform);
    guMtxF2L(mtxTransform, &gDisplayContext->matrixStack[gMatrixListPos]);

    gSPMatrix(
        gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW
    );
    gDPSetPrimColor(gMainGfxPos++, 0, 0, data->primCol.r, data->primCol.g, data->primCol.b, data->unk_18);
    gDPSetEnvColor(gMainGfxPos++, data->envCol.r, data->envCol.g, data->envCol.b, 0);

    // SHOCK_HIT: skipped
    if (type == FX_SHOCK_OVERLAY_LIGHTNING_WORLD && time % 2) {
        guScaleF(mtxTransform, data->scaleX, data->scaleY, 15.0f / 14);
        guMtxF2L(mtxTransform, &gDisplayContext->matrixStack[gMatrixListPos]);

        gSPMatrix(
            gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW
        );
        gDPPipeSync(gMainGfxPos++);
        gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
        gDPSetTexturePersp(gMainGfxPos++, G_TP_NONE);
        gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
        gDPSetTextureFilter(gMainGfxPos++, G_TF_BILERP);
        gDPSetCombineLERP(
            gMainGfxPos++, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, ENVIRONMENT, PRIMITIVE,
            TEXEL0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
        );
        gDPSetRenderMode(gMainGfxPos++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gSPTexture(gMainGfxPos++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gDPLoadTextureBlock(
            gMainGfxPos++, D_09000200_3932A0, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5,
            G_TX_NOLOD, G_TX_NOLOD
        );
        gSPDisplayList(gMainGfxPos++, D_090008E8_393988);
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    }

    if (type == FX_SHOCK_OVERLAY_LIGHTNING_WORLD || type == FX_SHOCK_OVERLAY_LIGHTNING_BATTLE
        || type == FX_SHOCK_OVERLAY_MEGA_SHOCK)
    {
        if (type == FX_SHOCK_OVERLAY_LIGHTNING_WORLD) {
            gDPSetPrimColor(gMainGfxPos++, 0, 0, 255, 255, 0, data->unk_14);
        }

        guTranslateF(mtxTransform, 0.0f, data->scaleY, 0.0f);
        guScaleF(mtxUnkScale, data->unk_24 * 0.25, data->unk_24 * 0.25, 1.0f);
        guMtxCatF(mtxUnkScale, mtxTransform, mtxTransform);
        guMtxF2L(mtxTransform, &gDisplayContext->matrixStack[gMatrixListPos]);

        gSPMatrix(
            gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW
        );
        gSPDisplayList(gMainGfxPos++, D_09000950_3939F0);
        gSPDisplayList(gMainGfxPos++, D_09000FF8_394098);
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    }

    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
}
}
