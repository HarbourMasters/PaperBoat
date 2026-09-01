#include "common.h"
#include "effects_internal.h"
#include "assets/effects.h"
#include "port/Engine.h"
#include "port/patches/Patches.h"

// Port reimplementation of sun_appendGfx (src/effects/sun.c).

extern const char* D_E0120780[];
extern const char* D_E0120794[];

// Height a tail's cap must reach; the ortho box tops out at y 1200.
#define SUN_CAP_CLEAR_Y 1240.0f

// T a tail may add. The ray texture is 64 texels tall, fading to nothing at T=0 and full by
// T=63, and tile 0 mirrors in T, so T in [64,96] folds onto rows 63..32 -- its flat bright band.
// Growing further folds back into the fade and dims the tail out in mid-air.
#define SUN_TAIL_MAX_T (32 * 32)

// vtx_600 holds two ray quads, each ordered near cap (0,1) then far cap (2,3); the stock DL
// draws them as triangles (0,1,2) and (0,2,3).
#define SUN_RAY_VERTS 8

// vtx_600 copied out of the o2r, plus room for a tail behind each quad.
static Vtx sunWideRays[SUN_RAY_VERTS * 2];

// Continue `quad` past its far cap, writing the tail to `tail` and returning the vertices used,
// or 0 if the cap already clears the frame. The cap edge translates rigidly, so the ray keeps
// its width and angle, and the tail reuses the cap's verts so the join is exact.
static s32 sun_append_ray_tail(const Vtx* quad, Vtx* tail) {
    f32 dirX = ((f32) quad[2].v.ob[0] + quad[3].v.ob[0] - quad[0].v.ob[0] - quad[1].v.ob[0]) * 0.5f;
    f32 dirY = ((f32) quad[2].v.ob[1] + quad[3].v.ob[1] - quad[0].v.ob[1] - quad[1].v.ob[1]) * 0.5f;
    f32 len = sqrtf(SQ(dirX) + SQ(dirY));
    f32 unitX, unitY, ext;
    s32 i;

    if (len == 0.0f) {
        return 0;
    }
    unitX = dirX / len;
    unitY = dirY / len;
    if (unitY <= 0.0f) {
        return 0;
    }

    ext = (SUN_CAP_CLEAR_Y - MIN(quad[2].v.ob[1], quad[3].v.ob[1])) / unitY;
    if (ext <= 0.0f) {
        return 0;
    }

    tail[0] = quad[3];
    tail[1] = quad[2];
    tail[2] = quad[2];
    tail[3] = quad[3];

    for (i = 2; i < 4; i++) {
        // vert 2 spans the ray's T from vert 1, vert 3 from vert 0
        s32 span = tail[i].v.tc[1] - quad[3 - i].v.tc[1];
        s32 grow = MIN((s32) (span * (ext / len)), SUN_TAIL_MAX_T);

        tail[i].v.ob[0] += unitX * ext;
        tail[i].v.ob[1] += unitY * ext;
        tail[i].v.tc[1] += grow;
    }
    return 4;
}

// Copy the ray quads out of the o2r and give each one a tail
static s32 sun_build_wide_rays(void) {
    const Vtx* base = (const Vtx*) LOAD_ASSET(D_09000600_40C1A0);
    s32 count = SUN_RAY_VERTS;
    s32 i;

    if (base == nullptr) {
        return 0;
    }
    for (i = 0; i < SUN_RAY_VERTS; i++) {
        sunWideRays[i] = base[i];
    }
    for (i = 0; i < SUN_RAY_VERTS; i += 4) {
        Vtx* tail = &sunWideRays[count];

        count += sun_append_ray_tail(&sunWideRays[i], tail);
    }
    return count;
}

void port_sun_appendGfx(void* argEffect) {
    EffectInstance* effect = (EffectInstance*) argEffect;
    SunFXData* data;
    Matrix4f mtx;
    s32 alpha;
    s32 offsetS;
    s32 fromRight;
    s32 wideRayVerts;
    s32 i;

    data = effect->data.sun;
    alpha = data->alpha;
    fromRight = data->shineFromRight;

    if (alpha != 0) {
        wideRayVerts = sun_build_wide_rays();

        gDPPipeSync(gMainGfxPos++);
        gSPSegment(gMainGfxPos++, 0x9, VIRTUAL_TO_PHYSICAL(effect->shared->graphics));

        if (!fromRight) {
            guOrthoF(mtx, -1600.0f, 1600.0f, -1200.0f, 1200.0f, -100.0f, 100.0f, 1.0f);
        } else {
            guOrthoF(mtx, 1600.0f, -1600.0f, -1200.0f, 1200.0f, -100.0f, 100.0f, 1.0f);
        }

        guMtxF2L(mtx, &gDisplayContext->matrixStack[gMatrixListPos]);
        gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++],
            G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        guTranslateF(mtx, 0.0f, 0.0f, 0.0f);
        guMtxF2L(mtx, &gDisplayContext->matrixStack[gMatrixListPos]);
        gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++],
            G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gDPSetPrimColor(gMainGfxPos++, 0, 0, data->primColor.r, data->primColor.g, data->primColor.b, alpha >> 1);
        gDPSetEnvColor(gMainGfxPos++, data->envColor.r, data->envColor.g, data->envColor.b, data->envColor.a);
        gSPDisplayList(gMainGfxPos++, D_E0120794[0]);

        for (i = 0; i < ARRAY_COUNT(data->texScrollAmt); i++) {
            offsetS = data->texScrollAmt[i] * 4.0f;
            gDPSetTileSize(gMainGfxPos++, 1, offsetS + (44 * i), 0, offsetS + (44 * i) + 252, 124);
            if (i == 0 && wideRayVerts != 0) {
                // group 0 comes from sunWideRays (its quads plus tails) instead of D_E0120780[0]
                s32 v;

                gDPPipeSync(gMainGfxPos++);
                gSPVertex(gMainGfxPos++, sunWideRays, wideRayVerts, 0);
                for (v = 0; v < wideRayVerts; v += 4) {
                    gSP2Triangles(gMainGfxPos++, v, v + 1, v + 2, 0, v, v + 2, v + 3, 0);
                }
                gDPPipeSync(gMainGfxPos++);
            } else {
                gSPDisplayList(gMainGfxPos++, D_E0120780[i]);
            }
        }
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        gSPMatrix(gMainGfxPos++, &gDisplayContext->camPerspMatrix[gCurrentCameraID],
            G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gDPPipeSync(gMainGfxPos++);
    }
}
