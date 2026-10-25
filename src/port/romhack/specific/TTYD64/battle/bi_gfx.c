#include "port/romhack/specific/TTYD64/battle/bi_internal.h"

static const ALIGN_ASSET(2) char sTex_CoconutBomb[] = "__OTR__romhack/res/battle_items/coconutbomb";
static const ALIGN_ASSET(2) char sPal_CoconutBomb[] = "__OTR__romhack/res/battle_items/coconutbomb.pal";
static const ALIGN_ASSET(2) char sTex_CourageMeal[] = "__OTR__romhack/res/battle_items/couragemeal";
static const ALIGN_ASSET(2) char sPal_CourageMeal[] = "__OTR__romhack/res/battle_items/couragemeal.pal";
static const ALIGN_ASSET(2) char sTex_ZessDynamite[] = "__OTR__romhack/res/battle_items/zessdynamite";
static const ALIGN_ASSET(2) char sPal_ZessDynamite[] = "__OTR__romhack/res/battle_items/zessdynamite.pal";

// clang-format off
Vtx TTYD64_bi_VertexTable_802A2150[] = {
    { .v = { { -16, -16, 0 }, false, { 0, 0 }, { 0, 0, 0, 255 } } },
    { .v = { { 15, -16, 0 }, false, { 1024, 0 }, { 0, 0, 0, 255 } } },
    { .v = { { 15, 15, 0 }, false, { 1024, 1024 }, { 0, 0, 0, 255 } } },
    { .v = { { -16, 15, 0 }, false, { 0, 1024 }, { 0, 0, 0, 255 } } },
};

#define TTYD64_BI_PROJECTILE_GFX(tex, pal)                                                                            \
    {                                                                                                                 \
        gsDPPipeSync(),                                                                                               \
        gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),                                                        \
        gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),                                                           \
        gsDPSetTexturePersp(G_TP_PERSP),                                                                              \
        gsDPSetTextureDetail(G_TD_CLAMP),                                                                             \
        gsDPSetTextureLOD(G_TL_TILE),                                                                                 \
        gsDPSetTextureLUT(G_TT_NONE),                                                                                 \
        gsDPSetTextureFilter(G_TF_AVERAGE),                                                                           \
        gsDPSetTextureConvert(G_TC_FILT),                                                                             \
        gsDPSetTextureLUT(G_TT_RGBA16),                                                                               \
        gsDPLoadTLUT_pal16(0, pal),                                                                                   \
        gsDPLoadTextureTile_4b(tex, G_IM_FMT_CI, 32, 32, 0, 0, 31, 31, 0, G_TX_NOMIRROR | G_TX_WRAP,                   \
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),          \
        gsSPClearGeometryMode(G_LIGHTING),                                                                            \
        gsSPClearGeometryMode(G_SHADING_SMOOTH),                                                                      \
        gsSPVertex(TTYD64_bi_VertexTable_802A2150, ARRAY_COUNT(TTYD64_bi_VertexTable_802A2150), 0),                   \
        gsSP1Triangle(0, 1, 2, 0),                                                                                    \
        gsSP1Triangle(0, 2, 3, 0),                                                                                    \
        gsDPPipeSync(),                                                                                               \
        gsSPEndDisplayList(),                                                                                         \
    }

Gfx TTYD64_bi_DisplayList_CoconutBomb[] = TTYD64_BI_PROJECTILE_GFX(sTex_CoconutBomb, sPal_CoconutBomb);
Gfx TTYD64_bi_DisplayList_CourageMeal[] = TTYD64_BI_PROJECTILE_GFX(sTex_CourageMeal, sPal_CourageMeal);
Gfx TTYD64_bi_DisplayList_Dynamite[] = TTYD64_BI_PROJECTILE_GFX(sTex_ZessDynamite, sPal_ZessDynamite);

EntityModelScript TTYD64_bi_EntityModelScript_CoconutBomb = {
    ems_SetRenderMode(RENDER_MODE_ALPHATEST)
    ems_Draw(TTYD64_bi_DisplayList_CoconutBomb, 2)
    ems_Restart
    ems_End
};

EntityModelScript TTYD64_bi_EntityModelScript_CourageMeal = {
    ems_SetRenderMode(RENDER_MODE_ALPHATEST)
    ems_Draw(TTYD64_bi_DisplayList_CourageMeal, 2)
    ems_Restart
    ems_End
};

EntityModelScript TTYD64_bi_EntityModelScript_Dynamite = {
    ems_SetRenderMode(RENDER_MODE_ALPHATEST)
    ems_Draw(TTYD64_bi_DisplayList_Dynamite, 2)
    ems_Restart
    ems_End
};
// clang-format on
