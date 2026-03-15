#ifndef __FRAME_INTERPOLATION_H
#define __FRAME_INTERPOLATION_H

#include "common_structs.h"

#ifdef __cplusplus
#include <unordered_map>
std::unordered_map<Mtx*, MtxF> FrameInterpolation_Interpolate(float step);

extern "C" {
#endif

#define TAG_OBJ(id, ptr) (((((ptr)->listIndex) << 16) & 0x0FFF0000) | (((id) << 8) & 0x0000FF00))
#define TAG_ACTOR(id, ptr) (((((ptr)->actorID) << 16) & 0x0FFF0000) | (((id) << 8) & 0x0000FF00))
#define TAG_ITEM(id, ptr) (((((ptr)->itemID) << 16) & 0x0FFF0000) | (((id) << 8) & 0x0000FF00))
#define TAG_MODEL(id, ptr) (((((ptr)->modelID) << 16) & 0x0FFF0000) | (((id) << 8) & 0x0000FF00))
#define TAG_NPC(id, ptr) (((((ptr)->npcID) << 16) & 0x0FFF0000) | (((id) << 8) & 0x0000FF00))
#define TAG_EFFECT(id, ptr) (((((ptr)->effectID) << 16) & 0x0FFF0000) | (((id) << 8) & 0x0000FF00))
#define TAG_GENERIC(id, ptr) ((((id) << 8) & 0x0000FF00) | (u32)(ptr))
#define TAG_TASK(x) ((u32)0x30000000 | ((u32) (uintptr_t) (x) & 0x0FFFFFFF))

#define TAG_ITEM_ADDR(x) ((u32) 0x10000000 | (u32)x)
#define TAG_SMOKE_DUST(x) ((u32) 0x20000000 | (u32) (x))
#define TAG_LETTER(x) ((u32)0x30000000 | ((u32) (uintptr_t) (x) & 0x0FFFFFFF))
#define TAG_OBJECT(x) ((u32)0x40000000 | (u32)  (uintptr_t) (x))
#define TAG_CLOUDS(x) ((u32)0x50000000 | (u32)  (uintptr_t) (x))
#define TAG_RENDER_LAYER(layer, x) ((u32)layer | (u32)  (uintptr_t) (x))
#define TAG_RENDER_TASK(x) ((u32)0x60000000 | (u32)  (uintptr_t) (x))
//                          Mask the bits so that the 7 can't get overridden
#define TAG_TRACK(x) ((u32)0x70000000 | ((u32)(x) & 0x0FFFFFFF))
#define TAG_MINIMAP_DOTS(x) ((u32)0x80000000 | ((u32)(x) & 0x0FFFFFFF))
#define TAG_PORTRAITS(x) ((u32)0x90000000 | ((u32)(x) & 0x0FFFFFFF))

void FrameInterpolation_ShouldInterpolateFrame(bool shouldInterpolate);

bool check_if_recording();

void FrameInterpolation_StartRecord(void);

void FrameInterpolation_StopRecord(void);

void FrameInterpolation_RecordMarker(const char* file, int line);

void FrameInterpolation_RecordOpenChild(const void* a, uintptr_t b);

void FrameInterpolation_RecordCloseChild(void);

void FrameInterpolation_DontInterpolateCamera(void);

int FrameInterpolation_GetCameraEpoch(void);

void FrameInterpolation_RecordActorPosRotMatrix(void);

void FrameInterpolation_RecordMatrixPosRotXYZ(MtxF* out, Vec3f pos, Vec3s orientation);
void FrameInterpolation_RecordMatrixPosRotZXY(MtxF* out, Vec3f pos, Vec3s orientation);

void FrameInterpolation_RecordMatrixPosRotScaleXY(MtxF* matrix, s32 x, s32 y, u16 angle, f32 scale);

void FrameInterpolation_Record_SetTextMatrix(MtxF* matrix, f32 x, f32 y, f32 arg3, f32 arg4);

//void FrameInterpolation_RecordMatrixPush(MtxF* matrix);

//void FrameInterpolation_RecordMatrixPop(MtxF* matrix);

void FrameInterpolation_RecordMatrixMult(MtxF* matrix, MtxF* mf, u8 mode);

void FrameInterpolation_RecordMatrixTranslate(MtxF* matrix, Vec3f b);

void FrameInterpolation_RecordMatrixScale(MtxF* matrix, f32 scale);

void FrameInterpolation_RecordMatrixRotate1Coord(MtxF* matrix, u32 coord, s16 value);

void FrameInterpolation_RecordMatrixRotateXYCoords(MtxF* matrix, s16 x, s16 y);

void FrameInterpolation_RecordMatrixMtxFToMtx(MtxF* src, Mtx* dest);

void FrameInterpolation_RecordMatrixToMtx(Mtx* dest, char* file, s32 line);

void FrameInterpolation_RecordMatrixReplaceRotation(MtxF* mf);

//void FrameInterpolation_RecordMatrixRotateAxis(f32 angle, Vec3f* axis, u8 mode);

void FrameInterpolation_RecordSkinMatrixMtxFToMtx(MtxF* src, Mtx* dest);

//void FrameInterpolation_RecordMatrixMultVec3f(Matrix* matrix, Vec3f src, Vec3f dest);

//void FrameInterpolation_RecordMatrixMultVec3fNoTranslate(Matrix* matrix, Vec3f src, Vec3f dest);

void FrameInterpolation_RecordSetTransformMatrix(MtxF* dest, Vec3f orientationVector, Vec3f positionVector, u16 rotationAngle,
                          f32 scaleFactor);

void FrameInterpolation_RecordTranslateRotate(MtxF* dest, Vec3f pos, Vec3s rotation);

void FrameInterpolation_RecordOrtho(Mtx* m, f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far, f32 scale);

//void FrameInterpolation_func_80062B18(f32* arg0, f32* arg1, f32* arg2, arg3, arg4, arg5, arg6, arg7);

#ifdef __cplusplus
}
#endif

#endif // __FRAME_INTERPOLATION_H
