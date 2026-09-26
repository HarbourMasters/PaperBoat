#include "pause/pause_common.h"
#include "message_ids.h"
#include "port/patches/Patches.h"
// Asset paths defined in assets/misc/pause.h, loaded via OTR
#include "assets/misc/pause.h"

Gfx PauseGfxBannerHp[] = {
    gsDPPipeSync(),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(0, pause_banner_hp_pal),
    gsDPLoadTextureTile_4b(pause_banner_hp_png, G_IM_FMT_CI, 64, 16, 0, 0, 63, 15, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetRenderMode(AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM), AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx PauseGfxBannerFp[] = {
    gsDPPipeSync(),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(0, pause_banner_fp_pal),
    gsDPLoadTextureTile_4b(pause_banner_fp_png, G_IM_FMT_CI, 64, 16, 0, 0, 63, 15, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetRenderMode(AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM), AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx PauseGfxBannerBp[] = {
    gsDPPipeSync(),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(0, pause_banner_bp_pal),
    gsDPLoadTextureTile_4b(pause_banner_bp_png, G_IM_FMT_CI, 64, 16, 0, 0, 63, 15, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetRenderMode(AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM), AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx PauseGfxBannerBoots[] = {
    gsDPPipeSync(),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(0, pause_banner_boots_pal),
    gsDPLoadTextureTile_4b(pause_banner_boots_png, G_IM_FMT_CI, 48, 16, 0, 0, 47, 15, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetRenderMode(AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM), AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx PauseGfxBannerHammer[] = {
    gsDPPipeSync(),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(0, pause_banner_hammer_pal),
    gsDPLoadTextureTile_4b(pause_banner_hammer_png, G_IM_FMT_CI, 48, 16, 0, 0, 47, 15, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetRenderMode(AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM), AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx PauseGfxBannerStarEnergy[] = {
    gsDPPipeSync(),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(0, pause_banner_star_energy_pal),
    gsDPLoadTextureTile_4b(pause_banner_star_energy_png, G_IM_FMT_CI, 48, 16, 0, 0, 47, 15, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetRenderMode(AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM), AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx PauseGfxStatsBar[] = {
    gsDPPipeSync(),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(0, pause_stats_bar_pal),
    gsDPLoadTextureTile_4b(pause_stats_bar_png, G_IM_FMT_CI, 160, 8, 0, 0, 159, 7, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_WRAP, 8, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetRenderMode(AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM), AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx PauseGfxWorldMap[] = {
    gsDPPipeSync(),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPLoadTLUT_pal256(pause_world_map_pal),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_CULL_BOTH | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx PauseGfxPathPoints[] = {
    gsDPPipeSync(),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
    gsDPSetCombineMode(PM_CC_2F, PM_CC_2F),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(pause_map_location_png, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0, 0, 15, 15, 0, G_TX_CLAMP, G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadMultiTile(pause_map_path_marker_png, 0x100, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0, 0, 15, 15, 0, G_TX_CLAMP, G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx PauseGfxArrows[] = {
    gsDPPipeSync(),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile_4b(pause_arrows_png, G_IM_FMT_IA, 16, 64, 0, 0, 15, 63, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 4, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetRenderMode(AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM), AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx PauseGfxOrbs[] = {
    gsDPPipeSync(),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(pause_orbs_png, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 32, 0, 0, 7, 31, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 3, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetRenderMode(AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM), AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetCombineMode(PM_CC_01, PM_CC_01),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx PauseGfxAvailable[] = {
    gsDPPipeSync(),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(0, pause_available_pal),
    gsDPLoadTextureTile_4b(pause_available_png, G_IM_FMT_CI, 64, 16, 0, 0, 63, 15, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetRenderMode(AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM), AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx PauseGfxCheckAbilities[] = {
    gsDPPipeSync(),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(0, pause_prompt_check_abilities_pal),
    gsDPLoadTextureTile_4b(pause_prompt_check_abilities_png, G_IM_FMT_CI, 128, 16, 0, 0, 127, 15, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 7, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetRenderMode(AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM), AA_EN | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx PauseGfxSpiritsBg[] = {
    gsDPPipeSync(),
    gsSPTexture(-1, -1, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_AVERAGE),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPLoadTLUT_pal16(0, pause_spirits_bg_pal),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_CULL_BOTH | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

#if VERSION_PAL
u8 D_PAL_80271B10[] = { 0x71, 0x71, 0x78, 0x71 };
u8 D_PAL_80271B14[] = { 0x6A, 0x6A, 0x72, 0x6A };
u8 D_PAL_80271B18[] = { 0x10, 0x10, 0x0F, 0x10 };
u8 D_PAL_80271B1C[] = { 0x3D, 0x3D, 0x3C, 0x3D };
u8 D_PAL_80271B20[] = { 0x43, 0x43, 0x42, 0x43 };
u8 D_PAL_80271B24[] = { 0x8F, 0x7F, 0x88, 0x7C };
u8 D_PAL_80271B28[] = { 0x9B, 0x88, 0x93, 0x84 };
u8 D_PAL_80271B2C[] = { 0x1A, 0x1F, 0x23, 0x18 };
u8 D_PAL_80271B30[] = { 0x00, 0x26, 0x36, 0x1A };
u8 D_PAL_80271B34[] = { 0x19, 0x19, 0x16, 0x12 };
u8 D_PAL_80271B38[] = { 0x0C, 0x08, 0x0B, 0x08 };
u8 D_PAL_80271B3C[] = { 0x85, 0x80, 0x80, 0x80 };
u8 D_PAL_80271B40[] = { 0x8C, 0x96, 0x96, 0x96 };
u8 D_PAL_80271B44[] = { 0x7D, 0x87, 0x87, 0x87 };
u8 D_PAL_80271B48[] = { 0x66, 0x70, 0x70, 0x70 };
u8 D_PAL_80271B4C[] = { 0x0C, 0x0C, 0x12, 0x0C };
u8 D_PAL_80271B50[] = { 0x50, 0x60, 0x52, 0x5F };
#endif

#if VERSION_IQUE
u8 gPauseMsg_17[] = { 0x8F, 0x0C, 0x75, 0x12, 0xFD };
u8 gPauseMsg_18[] = { 0x7B, 0x0E, 0x7C, 0x0E, 0xFD };
u8 gPauseMsg_19[] = { 0x77, 0x10, 0x74, 0x0D, 0xFD };
u8 gPauseMsg_1A[] = { 0x79, 0x12, 0x67, 0x09, 0xFD };
u8 gPauseMsg_32[] = { 0x64, 0x02, 0x75, 0x11, 0xFD };
u8 gPauseMsg_33[] = { 0x62, 0x05, 0x62, 0x05, 0x87, 0x06, 0x5F, 0x18, 0xFD };
u8 gPauseMsg_34[] = { 0x62, 0x05, 0x73, 0x02, 0x67, 0x11, 0x85, 0x10, 0xFD };
u8 gPauseMsg_35[] = { 0x7D, 0x0C, 0x85, 0x12, 0x85, 0x05, 0x79, 0x02, 0xFD };
u8 gPauseMsg_36[] = { 0x28, 0x30, 0xFD };
u8 gPauseMsg_37[] = { 0x26, 0x30, 0xFD };
u8 gPauseMsg_38[] = { 0x22, 0x30, 0xFD };
u8 gPauseMsg_39[] = { 0x0F, 0xFD };
u8 gPauseMsg_3A[] = { 0x0E, 0xFD };
u8 gPauseMsg_3B[] = { 0x69, 0x08, 0x81, 0x07, 0xFD };
u8 gPauseMsg_3C[] = { 0x7B, 0x25, 0x60, 0x01, 0xFD };
u8 gPauseMsg_3D[] = { 0x6B, 0x02, 0x6C, 0x02, 0x7B, 0x25, 0x60, 0x01, 0xFD };
u8 gPauseMsg_3E[] = { 0x6D, 0x0A, 0x6C, 0x02, 0x7B, 0x25, 0x60, 0x01, 0xFD };
u8 gPauseMsg_3F[] = { 0x69, 0x08, 0x81, 0x07, 0xFD };
u8 gPauseMsg_40[] = { 0x68, 0x04, 0x60, 0x01, 0xFD };
u8 gPauseMsg_41[] = { 0x6B, 0x02, 0x6C, 0x02, 0x68, 0x04, 0x60, 0x01, 0xFD };
u8 gPauseMsg_42[] = { 0x6D, 0x0A, 0x6C, 0x02, 0x68, 0x04, 0x60, 0x01, 0xFD };
u8 gPauseMsg_43[] = { 0x75, 0x04, 0x76, 0x04, 0x81, 0x03, 0xFD };
u8 gPauseMsg_44[] = { 0x82, 0x07, 0x6C, 0x02, 0xFD };
u8 gPauseMsg_46[] = { 0x22, 0x30, 0xFD };
u8 gPauseMsg_47[] = { 0x69, 0x07, 0x81, 0x07, 0x7B, 0x0E, 0x7C, 0x0E, 0xFD };
u8 gPauseMsg_48[] = { 0x81, 0x07, 0x6F, 0x17, 0x7B, 0x0E, 0x7C, 0x0E, 0xFD };
u8 gPauseMsg_49[] = { 0xFD };
u8 gPauseMsg_4A[] = { 0x69, 0x08, 0x81, 0x07, 0x6C, 0x14, 0x78, 0x0D, 0xF7, 0x22, 0x30, 0xFD };
u8 gPauseMsg_4B[] = { 0x76, 0x06, 0x8B, 0x06, 0x85, 0x07, 0x82, 0x12, 0x8C, 0x04, 0x87, 0x04, 0xFD };
u8 gPauseMsg_50[] = { 0x77, 0x10, 0x74, 0x0D, 0xFD };
u8 gPauseMsg_4F[] = { 0x8C, 0x07, 0x80, 0x05, 0x77, 0x10, 0x74, 0x0D, 0xFD };
u8 gPauseMsg_53[] = { 0x28, 0x30, 0xFD };
u8 gPauseMsg_54[] = { 0x26, 0x30, 0xFD };
u8 gPauseMsg_55[] = { 0x6A, 0x11, 0x8B, 0x06, 0xFD };
u8 gPauseMsg_56[] = { 0x74, 0x08, 0x74, 0x08, 0x74, 0x08, 0xFD };
#elif VERSION_US
u8 gPauseMsg_17[] = { 0x33, 0x54, 0x41, 0x54, 0x53, 0xFD };                                                                   // Stats[End]
u8 gPauseMsg_18[] = { 0x22, 0x41, 0x44, 0x47, 0x45, 0xFD };                                                                   // Badge[End]
u8 gPauseMsg_19[] = { 0x29, 0x54, 0x45, 0x4D, 0x53, 0xFD };                                                                   // Items[End]
u8 gPauseMsg_1A[] = { 0x30, 0x41, 0x52, 0x54, 0x59, 0xFD };                                                                   // Party[End]
u8 gPauseMsg_32[] = { 0x23, 0x4F, 0x49, 0x4E, 0x53, 0xFD };                                                                   // Coins[End]
u8 gPauseMsg_33[] = { 0x33, 0x54, 0x41, 0x52, 0xF7, 0x30, 0x4F, 0x49, 0x4E, 0x54, 0x53, 0xFD };                               // Star Points[End]
u8 gPauseMsg_34[] = { 0x33, 0x54, 0x41, 0x52, 0xF7, 0x30, 0x49, 0x45, 0x43, 0x45, 0x53, 0xFD };                               // Star Pieces[End]
u8 gPauseMsg_35[] = { 0x30, 0x4C, 0x41, 0x59, 0xF7, 0x34, 0x49, 0x4D, 0x45, 0xFD };                                           // Play Time[End]
u8 gPauseMsg_36[] = { MSG_CHAR_UPPER_H, MSG_CHAR_UPPER_P, MSG_CHAR_READ_END };                                                // HP[End]
u8 gPauseMsg_37[] = { MSG_CHAR_UPPER_F, MSG_CHAR_UPPER_P, MSG_CHAR_READ_END };                                                // FP[End]
u8 gPauseMsg_38[] = { MSG_CHAR_UPPER_B, MSG_CHAR_UPPER_P, MSG_CHAR_READ_END };                                                // BP[End]
u8 gPauseMsg_39[] = { MSG_CHAR_FORWARDSLASH, MSG_CHAR_READ_END };                                                             // /[End]
u8 gPauseMsg_3A[] = { MSG_CHAR_PERIOD, MSG_CHAR_READ_END };                                                                   // .[End]
u8 gPauseMsg_3B[] = { 0x2E, 0x4F, 0x4E, 0x45, 0xFD };                                                                         // None[End]
u8 gPauseMsg_3C[] = { 0x22, 0x4F, 0x4F, 0x54, 0x53, 0xFD };                                                                   // Boots[End]
u8 gPauseMsg_3D[] = { 0x33, 0x55, 0x50, 0x45, 0x52, 0xF7, 0x22, 0x4F, 0x4F, 0x54, 0x53, 0xFD };                               // Super Boots[End]
u8 gPauseMsg_3E[] = { 0x35, 0x4C, 0x54, 0x52, 0x41, 0xF7, 0x22, 0x4F, 0x4F, 0x54, 0x53, 0xFD };                               // Ultra Boots[End]
u8 gPauseMsg_3F[] = { 0x2E, 0x4F, 0x4E, 0x45, 0xFD };                                                                         // None[End]
u8 gPauseMsg_40[] = { 0x28, 0x41, 0x4D, 0x4D, 0x45, 0x52, 0xFD };                                                             // Hammer[End]
u8 gPauseMsg_41[] = { 0x33, 0x55, 0x50, 0x45, 0x52, 0xF7, 0x28, 0x41, 0x4D, 0x4D, 0x45, 0x52, 0xFD };                         // Super Hammer[End]
u8 gPauseMsg_42[] = { 0x35, 0x4C, 0x54, 0x52, 0x41, 0xF7, 0x28, 0x41, 0x4D, 0x4D, 0x45, 0x52, 0xFD };                         // Ultra Hammer[End]
u8 gPauseMsg_43[] = { 0x2D, 0x41, 0x52, 0x49, 0x4F, 0xFD };                                                                   // Mario[End]
u8 gPauseMsg_44[] = { 0x2C, 0x45, 0x56, 0x45, 0x4C, 0xFD };                                                                   // Level[End]
u8 gPauseMsg_46[] = { MSG_CHAR_UPPER_B, MSG_CHAR_UPPER_P, MSG_CHAR_READ_END };                                                // BP[End]
u8 gPauseMsg_47[] = { 0x21, 0x4C, 0x4C, 0xF7, 0x22, 0x41, 0x44, 0x47, 0x45, 0x53, 0xFD };                                     // All Badges[End]
u8 gPauseMsg_48[] = { 0x21, 0x43, 0x54, 0x49, 0x56, 0x45, 0xFD };                                                             // Active[End]
u8 gPauseMsg_49[] = { 0x22, 0x41, 0x44, 0x47, 0x45, 0x53, 0xFD };                                                             // Badges[End]
u8 gPauseMsg_4A[] = { 0x2E, 0x4F, 0x54, 0xF7, 0x45, 0x4E, 0x4F, 0x55, 0x47, 0x48, 0xF7, 0x22, 0x30, 0xFD };                   // Not enough BP[End]
u8 gPauseMsg_4B[] = { 0x24, 0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x57, 0x45, 0x41, 0x52, 0xF7, 0x4D, 0x4F, 0x52, 0x45, 0x01, 0xFD }; // Don't wear more![End]
u8 gPauseMsg_50[] = { 0x29, 0x54, 0x45, 0x4D, 0x53, 0xFD };                                                                   // Items[End]
u8 gPauseMsg_4F[] = { 0x2B, 0x45, 0x59, 0xF7, 0x29, 0x54, 0x45, 0x4D, 0x53, 0xFD };                                           // Key Items[End]
u8 gPauseMsg_53[] = { MSG_CHAR_UPPER_H, MSG_CHAR_UPPER_P, MSG_CHAR_READ_END };                                                // HP[End]
u8 gPauseMsg_54[] = { MSG_CHAR_UPPER_F, MSG_CHAR_UPPER_P, MSG_CHAR_READ_END };                                                // FP[End]
u8 gPauseMsg_55[] = { 0x21, 0x42, 0x49, 0x4C, 0x49, 0x54, 0x49, 0x45, 0x53, 0xFD };                                           // Abilities[End]
u8 gPauseMsg_56[] = { MSG_CHAR_QUESTION, MSG_CHAR_QUESTION, MSG_CHAR_QUESTION, MSG_CHAR_READ_END };                                                                               // ???[End]
#elif VERSION_PAL
#define gPauseMsg_32 MSG_PAL_Menu_0039 /* Coins */
#define gPauseMsg_33 MSG_PAL_Menu_003A /* Star Points */
#define gPauseMsg_34 MSG_PAL_Menu_003B /* Star Pieces */
#define gPauseMsg_35 MSG_PAL_Menu_003C /* Play Time */
#define gPauseMsg_36 MSG_PAL_Menu_003D /* HP */
#define gPauseMsg_37 MSG_PAL_Menu_003E /* FP */
#define gPauseMsg_38 MSG_PAL_Menu_003F /* BP */
#define gPauseMsg_39 MSG_PAL_Menu_0040 /* / */
#define gPauseMsg_3A MSG_PAL_Menu_0041 /* . */
#define gPauseMsg_3C MSG_PAL_Menu_0042 /* Boots */
#define gPauseMsg_3D MSG_PAL_Menu_0043 /* Super Boots */
#define gPauseMsg_3E MSG_PAL_Menu_0044 /* Ultra Boots */
#define gPauseMsg_40 MSG_PAL_Menu_0045 /* Hammer */
#define gPauseMsg_41 MSG_PAL_Menu_0046 /* Super Hammer */
#define gPauseMsg_42 MSG_PAL_Menu_0047 /* Ultra Hammer */
#define gPauseMsg_43 MSG_PAL_Menu_0048 /* Mario */
#define gPauseMsg_44 MSG_PAL_Menu_0049 /* Level */
#define gPauseMsg_46 MSG_PAL_Menu_003F /* BP */
#define gPauseMsg_47 MSG_PAL_Menu_004A /* All Badges */
#define gPauseMsg_PAL_42 MSG_PAL_Menu_004B /* [END] */
#define gPauseMsg_48 MSG_PAL_Menu_004C /* Active */
#define gPauseMsg_49 MSG_PAL_Menu_004D /* Badges */
#define gPauseMsg_4A MSG_PAL_Menu_004E /* Not Enough BP! */
#define gPauseMsg_4B MSG_PAL_Menu_004F /* Don't wear more! */
#define gPauseMsg_4F MSG_PAL_Menu_0051 /* Key Items */
#define gPauseMsg_PAL_4B MSG_PAL_Menu_0052 /* [END] */
#define gPauseMsg_50 MSG_PAL_Menu_0050 /* Items */
#define gPauseMsg_53 MSG_PAL_Menu_003D /* HP */
#define gPauseMsg_54 MSG_PAL_Menu_003E /* FP */
#define gPauseMsg_55 MSG_PAL_Menu_0053 /* Abilities */
#define gPauseMsg_56 MSG_PAL_Menu_0054 /* ??? */
#endif

intptr_t gPauseMessages[] = {
    [PAUSE_MSG_NONE]                MSG_NONE,
    [PAUSE_MSG_TUT_NAME_BADGES]     MSG_MenuTip_BadgeTutorial_01,
    [PAUSE_MSG_TUT_UNUSED_1]        MSG_MenuTip_002B,
    [PAUSE_MSG_TUT_UNUSED_2]        MSG_MenuTip_002C,
    [PAUSE_MSG_TUT_UNUSED_3]        MSG_MenuTip_002D,
    [PAUSE_MSG_TUT_UNUSED_4]        MSG_MenuTip_002E,
    [PAUSE_MSG_TUT_UNUSED_5]        MSG_MenuTip_002F,
    [PAUSE_MSG_TUT_UNUSED_6]        MSG_MenuTip_0030,
    [PAUSE_MSG_TUT_UNUSED_7]        MSG_MenuTip_0031,
    [PAUSE_MSG_TUT_DESC_1]          MSG_MenuTip_BadgeTutorial_02,
    [PAUSE_MSG_TUT_DESC_2]          MSG_MenuTip_BadgeTutorial_03,
    [PAUSE_MSG_TUT_DESC_3]          MSG_MenuTip_BadgeTutorial_04,
    [PAUSE_MSG_TUT_DESC_4]          MSG_MenuTip_BadgeTutorial_05,
    [PAUSE_MSG_TUT_DESC_5]          MSG_MenuTip_BadgeTutorial_06,
    [PAUSE_MSG_TUT_DESC_6]          MSG_MenuTip_BadgeTutorial_07,
    [PAUSE_MSG_TUT_DESC_7]          MSG_MenuTip_BadgeTutorial_08,
    [PAUSE_MSG_TUT_CMD_1]           MSG_MenuTip_BadgeTutorial_09,
    [PAUSE_MSG_TUT_CMD_2]           MSG_MenuTip_BadgeTutorial_10,
    [PAUSE_MSG_TUT_CMD_3]           MSG_MenuTip_BadgeTutorial_11,
    [PAUSE_MSG_TUT_CMD_4]           MSG_MenuTip_BadgeTutorial_12,
    [PAUSE_MSG_TUT_CMD_5]           MSG_MenuTip_BadgeTutorial_13,
    [PAUSE_MSG_TUT_CMD_6]           MSG_MenuTip_BadgeTutorial_14,
    [PAUSE_MSG_TUT_CMD_7]           MSG_MenuTip_BadgeTutorial_15,
#if !VERSION_PAL
    [PAUSE_MSG_17]                  (intptr_t) gPauseMsg_17,
    [PAUSE_MSG_18]                  (intptr_t) gPauseMsg_18,
    [PAUSE_MSG_19]                  (intptr_t) gPauseMsg_19,
    [PAUSE_MSG_1A]                  (intptr_t) gPauseMsg_1A,
#endif
    [PAUSE_MSG_TAB_STATS]           MSG_MenuTip_StatsTab,
    [PAUSE_MSG_TAB_BADGES]          MSG_MenuTip_BadgesTab,
    [PAUSE_MSG_TAB_ITEMS]           MSG_MenuTip_ItemsTab,
    [PAUSE_MSG_TAB_PARTY]           MSG_MenuTip_PartyTab,
    [PAUSE_MSG_TAB_SPIRITS]         MSG_MenuTip_SpiritsTab,
    [PAUSE_MSG_TAB_MAP]             MSG_MenuTip_MapTab,
    [PAUSE_MSG_TIP_CONTROLS]        MSG_MenuTip_ControllingMario,
    [PAUSE_MSG_TIP_HP]              MSG_MenuTip_HeartPoints,
    [PAUSE_MSG_TIP_FP]              MSG_MenuTip_FlowerPoints,
    [PAUSE_MSG_TIP_BP]              MSG_MenuTip_BadgePoints,
    [PAUSE_MSG_TIP_BOOTS_1]         MSG_MenuTip_Boots1,
    [PAUSE_MSG_TIP_BOOTS_2]         MSG_MenuTip_Boots2,
    [PAUSE_MSG_TIP_BOOTS_3]         MSG_MenuTip_Boots3,
    [PAUSE_MSG_TIP_HAMMER_0]        MSG_MenuTip_Hammer0,
    [PAUSE_MSG_TIP_HAMMER_1]        MSG_MenuTip_Hammer1,
    [PAUSE_MSG_TIP_HAMMER_2]        MSG_MenuTip_Hammer2,
    [PAUSE_MSG_TIP_HAMMER_3]        MSG_MenuTip_Hammer3,
    [PAUSE_MSG_TIP_STAR_POWER]      MSG_MenuTip_StarPower,
    [PAUSE_MSG_TIP_STAR_POINTS]     MSG_MenuTip_StarPoints,
    [PAUSE_MSG_TIP_COINS]           MSG_MenuTip_Coins,
    [PAUSE_MSG_TIP_SECRETS]         MSG_MenuTip_Secrets,
    [PAUSE_MSG_TIP_STAR_PIECES]     MSG_MenuTip_StarPieces,
    [PAUSE_MSG_TIP_TIME]            MSG_MenuTip_Time,
    [PAUSE_MSG_LBL_COINS]           (intptr_t) gPauseMsg_32,
    [PAUSE_MSG_LBL_STAR_POINTS]     (intptr_t) gPauseMsg_33,
    [PAUSE_MSG_LBL_STAR_PIECES]     (intptr_t) gPauseMsg_34,
    [PAUSE_MSG_LBL_TIME]            (intptr_t) gPauseMsg_35,
    [PAUSE_MSG_LBL_HP]              (intptr_t) gPauseMsg_36,
    [PAUSE_MSG_LBL_FP]              (intptr_t) gPauseMsg_37,
    [PAUSE_MSG_LBL_BP]              (intptr_t) gPauseMsg_38,
    [PAUSE_MSG_SLASH]               (intptr_t) gPauseMsg_39,
    [PAUSE_MSG_DOT]                 (intptr_t) gPauseMsg_3A,
#if !VERSION_PAL
    [PAUSE_MSG_3B]                  (intptr_t) gPauseMsg_3B,
#endif
    [PAUSE_MSG_3C]                  (intptr_t) gPauseMsg_3C,
    [PAUSE_MSG_3D]                  (intptr_t) gPauseMsg_3D,
    [PAUSE_MSG_3E]                  (intptr_t) gPauseMsg_3E,
#if !VERSION_PAL
    [PAUSE_MSG_3F]                  (intptr_t) gPauseMsg_3F,
#endif
    [PAUSE_MSG_40]                  (intptr_t) gPauseMsg_40,
    [PAUSE_MSG_41]                  (intptr_t) gPauseMsg_41,
    [PAUSE_MSG_42]                  (intptr_t) gPauseMsg_42,
    [PAUSE_MSG_MARIO]               (intptr_t) gPauseMsg_43,
    [PAUSE_MSG_LEVEL]               (intptr_t) gPauseMsg_44,
    [PAUSE_MSG_NO_BADGE]            MSG_MenuTip_None,
    [PAUSE_MSG_BADGE_BP]            (intptr_t) gPauseMsg_46,
    [PAUSE_MSG_ALL_BADGES]          (intptr_t) gPauseMsg_47,
#if VERSION_PAL
    [PAUSE_MSG_PAL_42]              (intptr_t) gPauseMsg_PAL_42,
#endif
    [PAUSE_MSG_ACTIVE]              (intptr_t) gPauseMsg_48,
    [PAUSE_MSG_BADGES]              (intptr_t) gPauseMsg_49,
    [PAUSE_MSG_NOT_ENOUGH_BP]       (intptr_t) gPauseMsg_4A,
    [PAUSE_MSG_DONT_WEAR_MORE]      (intptr_t) gPauseMsg_4B,
    [PAUSE_MSG_BAGDE_DESC_ALL]      MSG_MenuTip_BadgeTab_All,
    [PAUSE_MSG_BAGDE_DESC_ACTIVE]   MSG_MenuTip_BadgeTab_Equipped,
    [PAUSE_MSG_BAGDE_DESC_NONE]     MSG_MenuTip_None,
    [PAUSE_MSG_KEY_ITEMS]           (intptr_t) gPauseMsg_4F,
#if VERSION_PAL
    [PAUSE_MSG_PAL_4B]              (intptr_t) gPauseMsg_PAL_4B,
#endif
    [PAUSE_MSG_CONSUMABLES]         (intptr_t) gPauseMsg_50,
    [PAUSE_MSG_DESC_CONSUMABLES]    MSG_MenuTip_ItemTab_Consumables,
    [PAUSE_MSG_DESC_KEY_ITEMS]      MSG_MenuTip_ItemTab_KeyItems,
    [PAUSE_MSG_PARTNER_HP]          (intptr_t) gPauseMsg_53,
    [PAUSE_MSG_PARTNER_FP]          (intptr_t) gPauseMsg_54,
    [PAUSE_MSG_PARTNER_ABILITIES]   (intptr_t) gPauseMsg_55,
    [PAUSE_MSG_UNKNOWN_SPIRIT]      (intptr_t) gPauseMsg_56,
};

Gfx* PauseGfxLabels[] = {
    [PAUSE_LBL_HP]        PauseGfxBannerHp,
    [PAUSE_LBL_FP]        PauseGfxBannerFp,
    [PAUSE_LBL_BP]        PauseGfxBannerBp,
    [PAUSE_LBL_BOOTS]     PauseGfxBannerBoots,
    [PAUSE_LBL_HAMMER]    PauseGfxBannerHammer,
    [PAUSE_LBL_ENERGY]    PauseGfxBannerStarEnergy,
    [PAUSE_LBL_STATS]     PauseGfxStatsBar,
    [PAUSE_LBL_AVAILABLE] PauseGfxAvailable,
    [PAUSE_LBL_ABILITIES] PauseGfxCheckAbilities,
};

intptr_t pause_get_menu_msg(s32 index) {
    intptr_t localized = port_pause_menu_msg(index);

    if (localized != 0) {
        return localized;
    }
    return gPauseMessages[index];
}

void pause_draw_menu_label(s32 index, s32 x, s32 y) {
    s32 xOffset = 64;

    if (index == 8) {
        xOffset = 128;
    }
    if (index == 3) {
        xOffset = 48;
    }
    if (index == 4) {
        xOffset = 48;
    }
    if (index == 5) {
        xOffset = 48;
    }
    if (index == 6) {
        xOffset = 160;
    }

    gSPDisplayList(gMainGfxPos++, PauseGfxLabels[index]);
    pause_draw_rect(x * 4, y * 4, (x + xOffset) * 4, (y + 16) * 4, 0, 0, 0, 0x400, 0x400);

#if VERSION_PAL
    if (gCurrentLanguage == LANGUAGE_DE && index == 5) {
        s16 xOffset2 = xOffset;

        pause_draw_rect((x + 30) * 4, (y * 4), (xOffset2 + x + 10) * 4, (y + 16) * 4, 0, 0x280, 0, 0x400, 0x400);
    }
#endif
}

BSS s8 gPauseBufferPal1[512];
BSS s8 gPauseBufferImg1[15752];
BSS s8 gPauseBufferPal2[512];
BSS s8 gPauseBufferImg2[15752];
