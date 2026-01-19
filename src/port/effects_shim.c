#include "ultra64.h"
#include "effects.h"
#include "functions.h"

extern void guTranslateF(float mf[4][4], float x, float y, float z);
extern void guScaleF(float mf[4][4], float x, float y, float z);
extern void guRotateF(float mf[4][4], float a, float x, float y, float z);
extern void guMtxCatF(float m[4][4], float n[4][4], float r[4][4]);
extern void guMtxF2L(float mf[4][4], Mtx* m);
extern void guPositionF(float mf[4][4], float r, float p, float h, float s, float x, float y, float z);
extern void guOrthoF(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale);
extern void guFrustumF(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale);
extern void guPerspectiveF(float mf[4][4], u16* perspNorm, float fovy, float aspect, float near, float far, float scale);

extern f32 sin_deg(f32 x);
extern f32 cos_deg(f32 x);
extern EffectInstance* create_effect_instance(EffectBlueprint* effectBp);
extern void remove_effect(EffectInstance* effectInstance);
extern void* general_heap_malloc(s32 size);
extern f32 sqrtf(f32 value);
extern s32 rand_int(s32 max);
extern RenderTask* queue_render_task(RenderTask* task);
extern void mem_clear(void* data, s32 numBytes);
extern f32 atan2(f32 startX, f32 startZ, f32 endX, f32 endZ);
extern bool npc_raycast_down_sides(s32 ignoreFlags, f32* posX, f32* posY, f32* posZ, f32* hitDepth);
extern s32 load_effect(s32 effectIndex);
extern void sfx_play_sound_at_position(s32 soundID, s32 flags, f32 posX, f32 posY, f32 posZ);
extern f32 clamp_angle(f32 theta);
extern void transform_point(Matrix4f mtx, f32 inX, f32 inY, f32 inZ, f32 inS, f32* outX, f32* outY, f32* outZ, f32* outW);
extern void draw_prev_frame_buffer_at_screen_pos(s32 x1, s32 y1, s32 x2, s32 y2, f32 alpha);
// draw_box declaration now comes from functions.h (uses void* for windowStyle on PC)
extern void draw_msg(s32 msgID, s32 posX, s32 posY, s32 opacity, s32 palette, u8 style);
extern s32 get_msg_width(s32 msgID, u16 charset);
extern void mdl_get_shroud_tint_params(u8* r, u8* g, u8* b, u8* a);
extern bool is_point_visible(f32 x, f32 y, f32 z, s32 depthQueryID, f32* screenX, f32* screenY);

void shim_guRotateF(float mf[4][4], float a, float x, float y, float z) {
    guRotateF(mf, a, x, y, z);
}

void shim_guTranslateF(float mf[4][4], float x, float y, float z) {
    guTranslateF(mf, x, y, z);
}

void shim_guTranslate(Mtx* m, float x, float y, float z) {
    float mf[4][4];
    guTranslateF(mf, x, y, z);
    guMtxF2L(mf, m);
}

void shim_guScaleF(float mf[4][4], float x, float y, float z) {
    guScaleF(mf, x, y, z);
}

void shim_guMtxCatF(float m[4][4], float n[4][4], float r[4][4]) {
    guMtxCatF(m, n, r);
}

void shim_guMtxF2L(float mf[4][4], Mtx* m) {
    guMtxF2L(mf, m);
}

void shim_guPerspectiveF(f32 mf[4][4], u16* perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale) {
    guPerspectiveF(mf, perspNorm, fovy, aspect, near, far, scale);
}

void shim_guPositionF(float mf[4][4], float r, float p, float h, float s, float x, float y, float z) {
    guPositionF(mf, r, p, h, s, x, y, z);
}

void shim_guOrthoF(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale) {
    guOrthoF(mf, l, r, b, t, n, f, scale);
}

void shim_guFrustumF(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale) {
    guFrustumF(mf, l, r, b, t, n, f, scale);
}

f32 shim_sin_deg(f32 x) {
    return sin_deg(x);
}

f32 shim_cos_deg(f32 x) {
    return cos_deg(x);
}

f32 shim_clamp_angle(f32 theta) {
    return clamp_angle(theta);
}

EffectInstance* shim_create_effect_instance(EffectBlueprint* effectBp) {
    return create_effect_instance(effectBp);
}

void shim_remove_effect(EffectInstance* effectInstance) {
    remove_effect(effectInstance);
}

void* shim_general_heap_malloc(s32 size) {
    return general_heap_malloc(size);
}

float shim_sqrtf(float value) {
    return sqrtf(value);
}

f32 shim_atan2(f32 startX, f32 startZ, f32 endX, f32 endZ) {
    return atan2(startX, startZ, endX, endZ);
}

bool shim_npc_raycast_down_sides(s32 ignoreFlags, f32* posX, f32* posY, f32* posZ, f32* hitDepth) {
    return npc_raycast_down_sides(ignoreFlags, posX, posY, posZ, hitDepth);
}

s32 shim_load_effect(s32 effectIndex) {
    return load_effect(effectIndex);
}

void shim_sfx_play_sound_at_position(s32 soundID, s32 value2, f32 posX, f32 posY, f32 posZ) {
    sfx_play_sound_at_position(soundID, value2, posX, posY, posZ);
}

s32 shim_rand_int(s32 max) {
    return rand_int(max);
}

RenderTask* shim_queue_render_task(RenderTask* task) {
    return queue_render_task(task);
}

void shim_mem_clear(void* data, s32 numBytes) {
    mem_clear(data, numBytes);
}

bool shim_is_point_visible(f32 x, f32 y, f32 z, s32 depthQueryID, f32* screenX, f32* screenY) {
    return is_point_visible(x, y, z, depthQueryID, screenX, screenY);
}

void shim_transform_point(Matrix4f mtx, f32 inX, f32 inY, f32 inZ, f32 inS, f32* outX, f32* outY, f32* outZ, f32* outW) {
    transform_point(mtx, inX, inY, inZ, inS, outX, outY, outZ, outW);
}

void shim_draw_prev_frame_buffer_at_screen_pos(s32 x1, s32 y1, s32 x2, s32 y2, f32 alpha) {
    draw_prev_frame_buffer_at_screen_pos(x1, y1, x2, y2, alpha);
}

void shim_draw_box(
    s32 flags, void* windowStyle, s32 posX, s32 posY, s32 posZ, s32 width, s32 height, u8 opacity,
    u8 darkening, f32 scaleX, f32 scaleY, f32 rotX, f32 rotY, f32 rotZ, void (*fpDrawContents)(void*),
    void* drawContentsArg0, Matrix4f rotScaleMtx, s32 translateX, s32 translateY, f32 (*outMtx)[4]
) {
    Matrix4f scratch;
    Matrix4f* outPtr = (outMtx != NULL) ? (Matrix4f*)outMtx : &scratch;

    (void)fpDrawContents;
    draw_box(flags, windowStyle, posX, posY, posZ, width, height, opacity, darkening, scaleX, scaleY, rotX, rotY, rotZ,
             NULL, drawContentsArg0, rotScaleMtx, translateX, translateY, *outPtr);
}

void shim_draw_msg(s32 msgID, s32 posX, s32 posY, s32 opacity, s32 palette, s32 style) {
    draw_msg(msgID, posX, posY, opacity, palette, (u8)style);
}

s32 shim_get_msg_width(s32 msgID, u16 charset) {
    return get_msg_width(msgID, charset);
}

void shim_mdl_get_shroud_tint_params(u8* r, u8* g, u8* b, u8* a) {
    mdl_get_shroud_tint_params(r, g, b, a);
}

void shim_mdl_draw_hidden_panel_surface(Gfx** gfxP, u16 treeIndex) {
    (void)gfxP;
    (void)treeIndex;
}