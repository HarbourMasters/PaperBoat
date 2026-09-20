#include "port/ShipInit.hpp"
#include "port/Engine.h"
#include "port/hooks/Events.h"

#include "common.h"
#include "effects_internal.h"
#include "assets/effects.h"
#include "port/patches/Patches.h"

extern "C" {

// Port reimplementation of energy_in_out_appendGfx (src/effects/energy_in_out.c).
//
// The original calls gSPDisplayList(D_09000200_3D6130), which is a ROM DL containing
// a buggy LOADBLOCK lrs=30, dxt=252 that loads ~31 of 512 bytes for the I4 16x64
// "blob" texture, plus 2-CYCLE mode reading TEXEL1 from an unbound tile. On N64 the
// remaining TMEM held leftover data and the quad rendered acceptably; on the LUS
// interpreter the partial load + cycle-2 unbound tile combine into a huge rectangle
// of garbage when the matrix is scaled up (Watt's PowerShock grow animation).
//
// This replacement does a clean 1-CYCLE full-texture load with a combiner that
// matches the ROM's intent: color = (PRIM - ENV) * T0, alpha = T0 * PRIM_a.

extern const char* D_E00D6E40[];

void port_energy_in_out_appendGfx(void* effect) {
    EnergyInOutFXData* part = ((EffectInstance*) effect)->data.energyInOut;
    s32 unk_24 = part->unk_24;
    s32 unk_00 = part->unk_00;
    f32 scale = part->scale * part->unk_44;
    s32 unk_18 = part->unk_18;
    s32 unk_1C = part->unk_1C;
    s32 unk_20 = part->unk_20;
    f32 unk_38 = part->unk_38;
    Matrix4f sp20;
    Matrix4f sp60;
    s32 i;

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*) effect)->shared->graphics));

    guPositionF(sp20, 0.0f, -gCameras[gCurrentCameraID].curYaw, 0.0f, scale, part->pos.x, part->pos.y, part->pos.z);
    guMtxF2L(sp20, &gDisplayContext->matrixStack[gMatrixListPos]);

    gSPMatrix(
        gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW
    );
    gDPSetPrimColor(gMainGfxPos++, 0, 0, part->unk_18, part->unk_1C, part->unk_20, unk_24);
    gDPSetEnvColor(gMainGfxPos++, part->unk_28, part->unk_2C, part->unk_30, 0);

    // Replaces gSPDisplayList(D_09000200_3D6130) — see file header.
    gDPPipeSync(gMainGfxPos++);
    gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
    gDPSetTexturePersp(gMainGfxPos++, G_TP_NONE);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
    gDPSetTextureFilter(gMainGfxPos++, G_TF_BILERP);
    gDPSetCombineLERP(
        gMainGfxPos++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, ENVIRONMENT,
        TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0
    );
    gDPSetRenderMode(gMainGfxPos++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPTexture(gMainGfxPos++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPLoadTextureBlock_4b(gMainGfxPos++, D_09000000_3D5F30, G_IM_FMT_I, 16, 64, 0, G_TX_CLAMP, G_TX_CLAMP, 4, 6, 1, 1);

    part++;
    for (i = 1; i < ((EffectInstance*) effect)->numParts; i++, part++) {
        f32 scale = part->scale;

        gDPSetPrimColor(gMainGfxPos++, 0, 0, unk_18, unk_1C, unk_20, (unk_24 * part->unk_24) / 255);

        guRotateF(sp20, part->unk_3C, 0.0f, 0.0f, 1.0f);
        guTranslateF(sp60, part->pos.x + unk_38, 0.0f, 0.0f);
        guMtxCatF(sp60, sp20, sp20);
        if (D_E00D6E40[unk_00] == D_09000688_3D65B8 || D_E00D6E40[unk_00] == D_09000808_3D6738) {
            guScaleF(sp60, scale, 1.0f, 1.0f);
        } else {
            guScaleF(sp60, scale, scale, 1.0f);
        }
        guMtxCatF(sp60, sp20, sp20);
        guMtxF2L(sp20, &gDisplayContext->matrixStack[gMatrixListPos]);

        gSPMatrix(
            gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW
        );
        gSPDisplayList(gMainGfxPos++, D_E00D6E40[unk_00]);
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    }

    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
}

}
