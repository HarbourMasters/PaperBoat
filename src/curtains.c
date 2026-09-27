#include "common.h"
#include "assets/theater.h"
#include "ld_addrs.h"
#include "nu/nusys.h"
#include "game_modes.h"
#include "port/Engine.h"
#include "port/patches/Patches.h"
#include "alignment.h"

static const ALIGN_ASSET(2) char theater_walls_tex_setup_gfx[]    = "__OTR__theater/walls_tex_setup_gfx";
static const ALIGN_ASSET(2) char theater_curtains_tex_setup_gfx[] = "__OTR__theater/curtains_tex_setup_gfx";
static const ALIGN_ASSET(2) char theater_floor_tex_setup_gfx[]    = "__OTR__theater/floor_tex_setup_gfx";

typedef struct {
    s32 idx;    // vertex index in the group
    f32 innerX; // |X| of the partner on the same texture row (the seam that stays fixed)
    f32 innerS; // partner's S texcoord
} TbPartner;

static const TbPartner tbPart_Floor[]     = {
    {4,800,2688},{5,800,2688},{11,800,2688},{20,800,2688},
    {13,800,640},{14,800,640},{16,800,640},{17,800,640},{-1,0,0}};
static const TbPartner tbPart_Curtain[]   = {
    {12,960,1024},{15,960,1024},{18,960,2048},
    {20,960,-1024},{21,960,-1024},{29,960,7168},{30,960,7168},{-1,0,0}};

// Mutable per-frame working copies (filled by build_theater_widescreen_dl).
static Vtx tb_LeftWall[6];
static Vtx tb_RightWall[6];
static Vtx tb_Floor[25];
static Vtx tb_LeftInsetShadow[4];
static Vtx tb_RightInsetShadow[4];
static Vtx tb_Curtain[31];
static Vtx tb_WallShadows[8];

// Scratch DL buffer for the rebuilt theater frame (generously sized; original is < 80 cmds).
static Gfx tb_theaterGfx[160];

// Copy base -> out and push every |X|==1600 vertex out to |X|==1600*k, scaling the
// S texcoord of listed vertices by the world-width factor about their inner partner.
static void tb_remap_group(const Vtx* base, Vtx* out, s32 count, const TbPartner* parts, f32 k) {
    const f32 edge = 1600.0f;
    s32 i;
    for (i = 0; i < count; i++) {
        out[i] = base[i];
        if (out[i].v.ob[0] == 1600 || out[i].v.ob[0] == -1600) {
            f32 sgn = (out[i].v.ob[0] > 0) ? 1.0f : -1.0f;
            out[i].v.ob[0] = (s16)(sgn * edge * k + (sgn > 0 ? 0.5f : -0.5f));
            if (parts != nullptr) {
                const TbPartner* p;
                for (p = parts; p->idx >= 0; p++) {
                    if (p->idx == i) {
                        f32 widthFactor = (edge * k - p->innerX) / (edge - p->innerX);
                        f32 ns = p->innerS + ((f32)base[i].v.tc[0] - p->innerS) * widthFactor;
                        out[i].v.tc[0] = (s16)(ns + (ns >= 0 ? 0.5f : -0.5f));
                        break;
                    }
                }
            }
        }
    }
}

// Rigid-body translate of a whole column group (wall leg or column shadow).
static void tb_translate_group(const Vtx* base, Vtx* out, s32 count, f32 k) {
    const f32 edge = 1600.0f;
    f32 dx = edge * (k - 1.0f); // how far the screen edge moved out
    s32 i;
    for (i = 0; i < count; i++) {
        out[i] = base[i];
        s16 x = base[i].v.ob[0];
        if (x > 0) {
            out[i].v.ob[0] = (s16)(x + dx + 0.5f);
        } else if (x < 0) {
            out[i].v.ob[0] = (s16)(x - dx - 0.5f);
        }
    }
}

// Build the widescreen theater frame into tb_theaterGfx and return it. At k==1 the
// vertices are identical to the originals, so the output matches theater_gfx exactly.
static Gfx* build_theater_widescreen_dl(void) {
    f32 k = GameEngine_GetAspectRatio() / (4.0f / 3.0f);
    Gfx* gfx = tb_theaterGfx;

    if (k < 1.0f) {
        k = 1.0f;
    }

    // Base (4:3) geometry
    const Vtx* base_LeftWall         = (const Vtx*)LOAD_ASSET(theater_left_wall_vtx);
    const Vtx* base_RightWall        = (const Vtx*)LOAD_ASSET(theater_right_wall_vtx);
    const Vtx* base_Floor            = (const Vtx*)LOAD_ASSET(theater_floor_vtx);
    const Vtx* base_LeftInsetShadow  = (const Vtx*)LOAD_ASSET(theater_left_inset_shadow_vtx);
    const Vtx* base_RightInsetShadow = (const Vtx*)LOAD_ASSET(theater_right_inset_shadow_vtx);
    const Vtx* base_Curtain          = (const Vtx*)LOAD_ASSET(theater_curtain_vtx);
    const Vtx* base_WallShadows      = (const Vtx*)LOAD_ASSET(theater_wall_shadows_vtx);

    // Columns + their shadows
    tb_translate_group(base_LeftWall,         tb_LeftWall,        6,  k);
    tb_translate_group(base_RightWall,        tb_RightWall,       6,  k);
    tb_translate_group(base_LeftInsetShadow,  tb_LeftInsetShadow, 4,  k);
    tb_translate_group(base_RightInsetShadow, tb_RightInsetShadow,4,  k);
    tb_translate_group(base_WallShadows,      tb_WallShadows,     8,  k);
    // Curtain + Floor
    tb_remap_group(base_Floor,           tb_Floor,           25, tbPart_Floor,       k);
    tb_remap_group(base_Curtain,         tb_Curtain,         31, tbPart_Curtain,     k);

    // wall shadows
    gDPPipeSync(gfx++);
    gfx[0].words.w0 = 0xE200001C; gfx[0].words.w1 = 0x0C184340; gfx++; // SetOtherMode_L
    gfx[0].words.w0 = 0xFC121803; gfx[0].words.w1 = 0xFFFFFFF8; gfx++; // SetCombineMode
    gSPDisplayList(gfx++, theater_curtains_tex_setup_gfx);
    gSPVertex(gfx++, tb_WallShadows, 8, 0);
    gSP2Triangles(gfx++, 0,1,2,0, 0,2,3,0);
    gSP2Triangles(gfx++, 4,5,6,0, 4,6,7,0);

    // inset shadows
    gDPPipeSync(gfx++);
    gfx[0].words.w0 = 0xE200001C; gfx[0].words.w1 = 0x0C184240; gfx++;
    gfx[0].words.w0 = 0xFCFFFE03; gfx[0].words.w1 = 0xFFFE79F8; gfx++;
    gfx[0].words.w0 = 0xD7000000; gfx[0].words.w1 = 0x00800080; gfx++; // SetTexScale (texture off-ish)
    gSPVertex(gfx++, tb_LeftInsetShadow, 4, 0);
    gSP2Triangles(gfx++, 0,1,2,0, 0,2,3,0);
    gSPVertex(gfx++, tb_RightInsetShadow, 4, 0);
    gSP2Triangles(gfx++, 0,1,2,0, 0,2,3,0);

    // floor
    gDPPipeSync(gfx++);
    gfx[0].words.w0 = 0xE200001C; gfx[0].words.w1 = 0x0F0A4200; gfx++;
    gfx[0].words.w0 = 0xFC121803; gfx[0].words.w1 = 0xFFFFFFF8; gfx++;
    gSPDisplayList(gfx++, theater_walls_tex_setup_gfx);
    gSPVertex(gfx++, tb_Floor, 25, 0);
    gSP2Triangles(gfx++, 0,1,2,0, 0,2,3,0);
    gSP2Triangles(gfx++, 4,5,0,0, 4,0,3,0);
    gSP2Triangles(gfx++, 1,6,7,0, 1,7,2,0);
    gSP2Triangles(gfx++, 3,8,9,0, 3,9,10,0);
    gSP2Triangles(gfx++, 11,4,3,0, 11,3,10,0);
    gSP2Triangles(gfx++, 12,13,14,0, 12,14,15,0);
    gSP2Triangles(gfx++, 8,12,15,0, 8,15,9,0);
    gSP2Triangles(gfx++, 6,16,13,0, 6,13,7,0);
    gSP2Triangles(gfx++, 14,17,18,0, 19,14,18,0);
    gSP2Triangles(gfx++, 20,11,21,0, 11,22,21,0);
    gSP2Triangles(gfx++, 23,19,18,0, 23,18,24,0);
    gSP2Triangles(gfx++, 22,23,24,0, 22,24,21,0);

    // right wall
    gDPPipeSync(gfx++);
    gfx[0].words.w0 = 0xE200001C; gfx[0].words.w1 = 0x0F0A4200; gfx++;
    gfx[0].words.w0 = 0xFC121803; gfx[0].words.w1 = 0xFFFFFFF8; gfx++;
    gSPDisplayList(gfx++, theater_floor_tex_setup_gfx);
    gSPVertex(gfx++, tb_RightWall, 6, 0);
    gSP2Triangles(gfx++, 0,1,2,0, 0,2,3,0);
    gSP2Triangles(gfx++, 1,4,5,0, 1,5,2,0);

    // left wall
    gDPPipeSync(gfx++);
    gfx[0].words.w0 = 0xE200001C; gfx[0].words.w1 = 0x0F0A4200; gfx++;
    gfx[0].words.w0 = 0xFC121803; gfx[0].words.w1 = 0xFFFFFFF8; gfx++;
    gSPDisplayList(gfx++, theater_floor_tex_setup_gfx);
    gSPVertex(gfx++, tb_LeftWall, 6, 0);
    gSP2Triangles(gfx++, 0,1,2,0, 0,2,3,0);
    gSP2Triangles(gfx++, 1,4,5,0, 1,5,2,0);

    // curtain
    gDPPipeSync(gfx++);
    gfx[0].words.w0 = 0xE200001C; gfx[0].words.w1 = 0x0C184240; gfx++;
    gfx[0].words.w0 = 0xFC127E03; gfx[0].words.w1 = 0xFFFFF3F8; gfx++;
    gSPDisplayList(gfx++, theater_curtains_tex_setup_gfx);
    gSPVertex(gfx++, tb_Curtain, 31, 0);
    gSP2Triangles(gfx++, 0,1,2,0, 0,2,3,0);
    gSP2Triangles(gfx++, 4,5,6,0, 4,6,7,0);
    gSP2Triangles(gfx++, 8,9,10,0, 8,10,11,0);
    gSP2Triangles(gfx++, 12,13,14,0, 12,14,15,0);
    gSP2Triangles(gfx++, 15,16,17,0, 15,17,18,0);
    gSP2Triangles(gfx++, 19,20,21,0, 19,21,22,0);
    gSP2Triangles(gfx++, 13,23,24,0, 13,24,14,0);
    gSP2Triangles(gfx++, 23,25,26,0, 23,26,24,0);
    gSP2Triangles(gfx++, 25,27,28,0, 25,28,26,0);
    gSP2Triangles(gfx++, 27,29,30,0, 27,30,28,0);

    gSPEndDisplayList(gfx++);
    return tb_theaterGfx;
}

Vp TheaterViewport = {
    {
        {(SCREEN_WIDTH/2)*4, (SCREEN_HEIGHT/2)*4, 0x200 - 1, 0},
        {(SCREEN_WIDTH/2)*4, (SCREEN_HEIGHT/2)*4, 0x200 - 1, 0},
    }
};

Gfx TheaterInitGfx[] = {
    gsSPViewport(&TheaterViewport),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 320, 240),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetAlphaDither(G_AD_PATTERN),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                          G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPPerspNormalize(0x0014),
    gsSPEndDisplayList(),
};

Gfx NoControllerSetupTexGfx[] = {
    gsDPPipeSync(),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(ui_no_controller, G_IM_FMT_IA, G_IM_SIZ_8b, ui_no_controller_width,
                        ui_no_controller_height, 0, 0, ui_no_controller_width - 1,
                        ui_no_controller_height - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 7,
                        5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPClearGeometryMode(G_CULL_BOTH | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx NoControllerGfx[] = {
    gsSPTextureRectangle(0x0180, 0x0260, 0x0380, 0x02E0, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

BSS f32 gCurtainScale;
BSS f32 gCurtainScaleGoal;
BSS f32 gCurtainFade;
BSS f32 gCurtainFadeGoal;
BSS UNK_FUN_PTR(gCurtainDrawCallback);
BSS Mtx D_8009BAA8[2];

void initialize_curtains(void) {
    gCurtainDrawCallback = nullptr;
    gCurtainScale = 2.0f;
    gCurtainScaleGoal = 2.0f;
    gCurtainFade = 0.0f;
    gCurtainFadeGoal = 0.0f;
}

void update_curtains(void) {
}

void render_curtains(void) {
    if (gCurtainScaleGoal != gCurtainScale) {
        gCurtainScale += (gCurtainScaleGoal - gCurtainScale) * 0.1;
    }

    if (gCurtainFadeGoal != gCurtainFade) {
        gCurtainFade += (gCurtainFadeGoal - gCurtainFade) * 0.03;
    }

    if (gCurtainScale < 1.9) {
        Matrix4f m;
        f32 scale;
        s8 rgb;
        f32 zoom = 1.0f;

        gDPPipeSync(gMainGfxPos++);
        gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(nuGfxCfb_ptr));
        gSPDisplayList(gMainGfxPos++, &TheaterInitGfx);

        // Full Height View zooms the world to fill the letterbox rows, zoom the theater with it
        if (port_cam_full_height(CAM_DEFAULT)) {
            zoom = (f32) SCREEN_HEIGHT / (SCREEN_HEIGHT - 2 * SCREEN_INSET_Y);
        }

        guFrustumF(m, -80.0f / zoom, 80.0f / zoom, -60.0f / zoom, 60.0f / zoom, 160.0f, 640.0f, 1.0f);
        guMtxF2L(m, &D_8009BAA8[0]);

        gSPMatrix(gMainGfxPos++, &D_8009BAA8[0], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

        scale = gCurtainScale - 0.01;
        if (scale < 1.0f) {
            scale = 1.0f;
        }

        guPositionF(m, 0.0f, 0.0f, 0.0f, scale * 0.1, 0.0f, 0.0f, -320.0f);

        guMtxF2L(m, &D_8009BAA8[1]);

        gSPMatrix(gMainGfxPos++, &D_8009BAA8[1], G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        rgb = 255.0f - (gCurtainFade * 255.0f);
        gDPSetPrimColor(gMainGfxPos++, 0, 0, rgb, rgb, rgb, 255);
        // Widescreen: build with outer edges pushed to the widened screen edge.
        gSPDisplayList(gMainGfxPos++, build_theater_widescreen_dl());
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        gDPPipeSync(gMainGfxPos++);
    }

    if (gCurtainDrawCallback != nullptr) {
        gCurtainDrawCallback();
    }

    if (!(gGameStatusPtr->contBitPattern & 1)) {
        if ((get_game_mode() == GAME_MODE_INTRO)
                || (get_game_mode() == GAME_MODE_TITLE_SCREEN)
                || (gGameStatusPtr->demoState != DEMO_STATE_NONE)) {
            s32 alpha = ((gGameStatusPtr->frameCounter) % 0x18) << 5;

            if (alpha > 255) {
                alpha = 255;
            }

            gSPDisplayList(gMainGfxPos++, &TheaterInitGfx);
            gSPDisplayList(gMainGfxPos++, &NoControllerSetupTexGfx);
            gDPSetPrimColor(gMainGfxPos++, 0, 0, 0xFF, 0x20, 0x10, alpha);
            gSPDisplayList(gMainGfxPos++, &NoControllerGfx);
        }
    }
}

void set_curtain_scale_goal(f32 scale) {
    gCurtainScaleGoal = scale;
}

void set_curtain_scale(f32 scale) {
    gCurtainScaleGoal = scale;
    gCurtainScale = scale;
}

void set_curtain_draw_callback(UNK_FUN_PTR(callback)) {
    gCurtainDrawCallback = callback;
}

void set_curtain_fade_goal(f32 fade) {
    gCurtainFadeGoal = fade;
}

void set_curtain_fade(f32 fade) {
    gCurtainFadeGoal = fade;
    gCurtainFade = fade;
}
