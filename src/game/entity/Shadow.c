#include "common.h"
#include "entity.h"
#include "assets/entities.h"
#include "Engine.h"
#include <stdio.h>

// Entity vertices are now exported as Vertex resources — VertexFactory handles format conversion
static Vtx* load_and_swap_vtx(const char* path, s32 count) {
    return (Vtx*) LOAD_ASSET(path);
}

void entity_Shadow_init(Shadow* shadow) {
    shadow->scale.x = 0.1f;
    shadow->scale.y = 0.1f;
    shadow->scale.z = 0.1f;
}

s32 entity_can_collide_with_jumping_player(Entity* entity) {
    if ((entity->collisionFlags & ENTITY_COLLISION_PLAYER_TOUCH_CEILING)
        && (gPlayerStatus.flags & PS_FLAG_JUMPING)
    ) {
        return true;
    }
    return false;
}

// Shadow DLs are built at runtime because they reference OTR-loaded textures/vertices.
// Static Gfx arrays can't embed LOAD_ASSET calls, so we build into persistent buffers.
#define SHADOW_DL_MAX 16
static Gfx shadow_dl_common[SHADOW_DL_MAX];
static Gfx shadow_dl_load_tex_square[SHADOW_DL_MAX];
static Gfx shadow_dl_load_tex_circle[SHADOW_DL_MAX];
static Gfx shadow_dl_render_square[SHADOW_DL_MAX];
static Gfx shadow_dl_render_circular[SHADOW_DL_MAX];
static s32 shadow_dls_initialized = false;

static void shadow_build_dls(void) {
    Gfx* g;

    fprintf(stderr, "[shadow_build_dls] ENTER: shadow_dl_render_circular=%p shadow_dl_render_square=%p\n",
        (void*)shadow_dl_render_circular, (void*)shadow_dl_render_square);
    fflush(stderr);

    // Entity_Shadow_GfxCommon
    g = shadow_dl_common;
    gSPTexture(g++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPPipeSync(g++);
    gDPSetTexturePersp(g++, G_TP_PERSP);
    gDPSetTextureDetail(g++, G_TD_CLAMP);
    gDPSetTextureLOD(g++, G_TL_TILE);
    gDPSetTextureLUT(g++, G_TT_NONE);
    gDPSetTextureFilter(g++, G_TF_BILERP);
    gDPSetTextureConvert(g++, G_TC_FILT);
    gSPEndDisplayList(g++);

    // Entity_Shadow_LoadTexSquare
    g = shadow_dl_load_tex_square;
    gSPDisplayList(g++, shadow_dl_common);
    gDPSetTextureLUT(g++, G_TT_NONE);
    gDPLoadTextureTile_4b(g++, (u8*) LOAD_ASSET(Entity_Shadow_TexSquare), G_IM_FMT_I, 16, 16, 0, 0, 15, 15, 0, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD);
    gSPEndDisplayList(g++);

    // Entity_Shadow_LoadTexCircle
    g = shadow_dl_load_tex_circle;
    gSPDisplayList(g++, shadow_dl_common);
    gDPSetTextureLUT(g++, G_TT_NONE);
    gDPLoadTextureTile_4b(g++, (u8*) LOAD_ASSET(Entity_Shadow_TexCircle), G_IM_FMT_I, 16, 16, 0, 0, 15, 15, 0, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD);
    gSPEndDisplayList(g++);

    // Entity_RenderSquareShadow
    g = shadow_dl_render_square;
    gSPDisplayList(g++, shadow_dl_load_tex_square);
    gSPClearGeometryMode(g++, G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH);
    gSPVertex(g++, load_and_swap_vtx(Entity_Shadow_VtxSquare, 4), 4, 0);
    gSP2Triangles(g++, 0, 1, 2, 0, 0, 2, 3, 0);
    gSPEndDisplayList(g++);

    // Entity_RenderCircularShadow
    g = shadow_dl_render_circular;
    gSPDisplayList(g++, shadow_dl_load_tex_circle);
    gSPClearGeometryMode(g++, G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH);
    gSPVertex(g++, load_and_swap_vtx(Entity_Shadow_VtxCircular, 4), 4, 0);
    gSP2Triangles(g++, 0, 1, 2, 0, 0, 2, 3, 0);
    gSPEndDisplayList(g++);

    shadow_dls_initialized = true;

    fprintf(stderr, "[shadow_build_dls] DONE: circular[0].w0=0x%08X square[0].w0=0x%08X\n",
        shadow_dl_render_circular[0].words.w0, shadow_dl_render_square[0].words.w0);
    fflush(stderr);
}

Gfx Entity_RenderNone[] = {
    gsSPEndDisplayList(),
};

EntityModelScript Entity_RenderNone_Script = {
    ems_Draw(Entity_RenderNone, 60)
    ems_Restart
    ems_End
};

//TODO split files
s32 D_802E9844_padding[] = { 0, 0, 0};

EntityModelScript Entity_CircularShadowA_Render = {
    ems_SetFlags(ENTITY_MODEL_FLAG_FOG_DISABLED)
    ems_SetRenderMode(RENDER_MODE_SHADOW)
    ems_Draw(shadow_dl_render_circular, 60)
    ems_Restart
    ems_End
};

EntityModelScript Entity_CircularShadowB_Render = {
    ems_SetFlags(ENTITY_MODEL_FLAG_FOG_DISABLED)
    ems_SetRenderMode(RENDER_MODE_SHADOW)
    ems_Draw(shadow_dl_render_circular, 60)
    ems_Restart
    ems_End
};

EntityModelScript Entity_SquareShadow_Render = {
    ems_SetFlags(ENTITY_MODEL_FLAG_FOG_DISABLED)
    ems_SetRenderMode(RENDER_MODE_SHADOW)
    ems_Draw(shadow_dl_render_square, 60)
    ems_Restart
    ems_End
};

ShadowBlueprint CircularShadowA = {
    .flags = ENTITY_FLAG_DISABLE_COLLISION,
    .renderCommandList = Entity_CircularShadowA_Render,
    .animModelNode =  nullptr,
    .onCreateCallback = entity_Shadow_init,
    .entityType = ENTITY_TYPE_SHADOW,
    .aabbSize = { 25, 10, 25 }
};

ShadowBlueprint CircularShadowB = {
    .flags = ENTITY_FLAG_DISABLE_COLLISION,
    .renderCommandList = Entity_CircularShadowB_Render,
    .animModelNode =  nullptr,
    .onCreateCallback = entity_Shadow_init,
    .entityType = ENTITY_TYPE_SHADOW,
    .aabbSize = { 25, 10, 25 }
};

ShadowBlueprint SquareShadow = {
    .flags = ENTITY_FLAG_DISABLE_COLLISION,
    .renderCommandList = Entity_SquareShadow_Render,
    .animModelNode =  nullptr,
    .onCreateCallback = entity_Shadow_init,
    .entityType = ENTITY_TYPE_SHADOW,
    .aabbSize = { 25, 10, 25 }
};

void entity_shadow_init_dls(void) {
    if (!shadow_dls_initialized) {
        shadow_build_dls();
    }
}
