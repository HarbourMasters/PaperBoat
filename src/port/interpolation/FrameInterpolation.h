#ifndef __FRAME_INTERPOLATION_H
#define __FRAME_INTERPOLATION_H

#include "common_structs.h"

#ifdef __cplusplus
#include <unordered_map>
std::unordered_map<Mtx*, MtxF> FrameInterpolation_Interpolate(float step);

extern "C" {
#endif

#define TAG_ENTRY(id, ptrIdx) (((((ptrIdx) << 16) & 0x0FFF0000) | (((id) << 8) & 0x0000FF00)))

#define TAG_OBJ(id, ptr) ((u32) (0x10000000 | (TAG_ENTRY((id), (ptr)->listIndex))))
#define TAG_ACTOR(id, ptr) ((u32) (0x20000000 | (TAG_ENTRY((id), (ptr)->actorID))))
#define TAG_ITEM(id, ptr) ((u32) (0x30000000 | (TAG_ENTRY((id), (ptr)->itemID))))
#define TAG_MODEL(id, ptr) ((u32) (0x40000000 | (TAG_ENTRY((id), (ptr)->modelID))))
#define TAG_GROUP(id, ptr) ((u32) (0x50000000 | (TAG_ENTRY((id), (ptr)->groupModelID))))
#define TAG_NPC(id, ptr) ((u32) (0x60000000 | (TAG_ENTRY((id), (ptr)->npcID))))
#define TAG_EFFECT(id, ptr) ((u32) (0x70000000 | (TAG_ENTRY((id), (ptr)->effectID))))

#define TAG_TASK(x) ((u32)0x80000000 | ((u32) (uintptr_t) (x) & 0x0FFFFFFF))
#define TAG_RENDER_LAYER(layer, x) ((u32)0x90000000 | (((layer) << 24) & 0x0F000000) | ((u32) (uintptr_t) (x) & 0x00FFFFFF))
#define TAG_RENDER_TASK(x) ((u32)0xA0000000 | ((u32) (uintptr_t) (x) & 0x0FFFFFFF))
#define TAG_ANIMATOR(id, ptr) ((u32) (0xB0000000 | (TAG_ENTRY((id), (ptr)->treeIndexPos))))
#define TAG_CAMERA(id, ptr) ((u32) (0xC0000000 | (TAG_ENTRY((id), (u32) ptr))))
#define TAG_SHADOW(id, ptr) ((u32) (0xD0000000 | (TAG_ENTRY((id), (ptr)->listIndex))))
#define TAG_ITEM_ENTITY(id, ptr) ((u32) (0xE0000000 | (TAG_ENTRY((id), (ptr)->itemID))))
#define TAG_TRANSFORM_GROUP(id, ptr) ((u32) (0xF0000000 | (TAG_ENTRY((id), (ptr)->groupModelID))))
#define TAG_WORKER(id, ptr) ((u32) (0x0F000000 | (TAG_ENTRY((id), (uint32_t)(ptr)->draw))))
#define TAG_ANIMATED_MODEL(id, ptr) ((u32) (0x00F00000 | (TAG_ENTRY((id), (ptr)->animModelID))))
#define TAG_GENERIC(id, ptr) ((u32) (0x00000000 | (TAG_ENTRY((id), (uint32_t)(ptr)))))

void FrameInterpolation_ShouldInterpolateFrame(bool shouldInterpolate);

bool check_if_recording();

void FrameInterpolation_StartRecord(void);

void FrameInterpolation_StopRecord(void);
void FrameInterpolation_GetRecordingPair(int* prevSlot, int* currSlot, bool* shouldInterpolate);
void FrameInterpolation_ClaimPair(int prevSlot, int currSlot);
void FrameInterpolation_ReleasePair(int prevSlot, int currSlot);
void FrameInterpolation_BeginRenderPass(int prevSlot, int currSlot, bool shouldInterpolate);

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
