#ifndef PORT_PATCHES_H
#define PORT_PATCHES_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

// Framebuffer (FramebufferPatches.c)
s32 port_fbMirrorS(s32 screenX);
u16* port_getPrevFrameSentinel(void);
void port_emitPrevFrameCapture(Gfx** gfxP);
void port_appendGfx_draw_prev_frame_buffer(s32 x1, s32 y1, s32 x2, s32 y2, f32 alpha);
u16* port_getSceneMirrorSentinel(void);
void port_emitSceneMirrorCapture(Gfx** gfxP);

// Static Gfx[] with VTXs
void port_patch_dl(Gfx* dl);
struct StaticAnimatorNode;
void port_patch_animator_tree(struct StaticAnimatorNode** tree);

// Map and battle textures O2R loader, replaces mdl_load_all_textures
struct ModelNode;
void port_load_map_textures(struct ModelNode* rootModel, const char* archiveName);
IMG_PTR port_tex_named_level(IMG_PTR raster, const char* suffix);
IMG_PTR port_mip_raster(IMG_PTR raster, IMG_PTR rasterPtr, s32 lod);
IMG_PTR port_aux_raster(IMG_PTR raster, IMG_PTR auxPtr);
IMG_PTR port_named_image(const char* asset, const char* suffix, void* fallback);

// Sprite palettes carry asset paths, not colors (SpriteLoader.cpp)
PAL_PTR port_sprite_palette_data(PAL_PTR palette);

// Sprite shading (SpritePatches.c)
void port_set_shading_source_palette(PAL_PTR palette);
void port_appendGfx_shading_palette(
    Matrix4f mtx, s32 uls, s32 ult, s32 lrs, s32 lrt, s32 alpha,
    f32 shadowX, f32 shadowY, f32 shadowZ,
    s32 shadowR, s32 shadowG, s32 shadowB,
    s32 highlightR, s32 highlightG, s32 highlightB,
    s32 ambientPower, s32 renderMode);

// Message fonts (MessagePatches.c)
void port_msg_font_loaded(s32 font);
IMG_PTR port_msg_glyph_raster(IMG_PTR glyph);
PAL_PTR port_msg_glyph_palette(PAL_PTR palette);

// Background (BackgroundPatches.c)
extern char* gBgPalettePath;
void port_load_map_bg(char* optAssetName);
void port_appendGfx_background_texture(void);

// Flame effect (FlamePatches.c)
void port_flame_appendGfx(void* effect);

// Underwater effect (UnderwaterPatches.c)
void port_underwater_appendGfx(void* effect);

// Motion blur flame effect (MotionBlurFlamePatches.c)
void port_motion_blur_flame_appendGfx(void* effect);

// Bulb glow effect (BulbGlowPatches.c)
void port_bulb_glow_appendGfx(void* effect);

// Energy in/out effect (EnergyInOutPatches.c)
void port_energy_in_out_appendGfx(void* effect);

// Flashing box shockwave effect (FlashingBoxShockwavePatches.c)
void port_flashing_box_shockwave_appendGfx(void* effect);

// Sun effect (SunPatches.c)
void port_sun_appendGfx(void* effect);

// Darkness stencil (DarknessStencilPatches.c)
void port_appendGfx_darkness_stencil(b32 isWorld, s32 posX, s32 posY, f32 alpha, f32 progress);

// EVT (EvtPatches.c) — pointer-safe replacement for `UseBuf(Ref(T*[])) +
// BufRead1`.
ApiStatus LoadPtrFromArray(Evt* script, bool isInitialCall);
ApiStatus StepTaggedAIWaveBuf(Evt* script, bool isInitialCall);

// Lava piranha vines (LavaPiranhaPatches.c)
extern u8 PortLavaPiranhaVineBase[4][16];
void port_lava_piranha_set_script(s32 vine, s32 index);
s16* port_lava_piranha_translate(s16* addr);
#define VINE_0_BASE ((intptr_t) PortLavaPiranhaVineBase[0])
#define VINE_1_BASE ((intptr_t) PortLavaPiranhaVineBase[1])
#define VINE_2_BASE ((intptr_t) PortLavaPiranhaVineBase[2])
#define VINE_3_BASE ((intptr_t) PortLavaPiranhaVineBase[3])


#ifdef __cplusplus
}
#endif

#endif  // PORT_PATCHES_H
