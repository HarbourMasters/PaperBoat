#include <libultraship/bridge.h>

#include "port/Engine.h"
#include <map>
#include <math.h>
#include <stdlib.h>
#include <unordered_map>
#include <vector>

#include "FrameInterpolation.h"

extern MtxF* gInterpolationMatrix;
extern "C" {
void guOrtho(Mtx* dest, float left, float right, float bottom, float oTop, float oNear, float oFar, float oScale);
}

/*
Frame interpolation.

The idea of this code is to interpolate all matrices.

The code contains two approaches. The first is to interpolate
all inputs in transformations, such as angles, scale and distances,
and then perform the same transformations with the interpolated values.
After evaluation for some reason some animations such rolling look strange.

The second approach is to simply interpolate the final matrices. This will
more or less simply interpolate the world coordinates for movements.
This will however make rotations ~180 degrees get the "paper effect".
The mitigation is to identify this case for actors and interpolate the
MtxF but in model coordinates instead, by "removing" the rotation-
translation before interpolating, create a rotation MtxF with the
interpolated angle which is then applied to the MtxF.

Currently the code contains both methods but only the second one is currently
used.

Both approaches build a tree of instructions, containing matrices
at leaves. Every node is built from OPEN_DISPS/CLOSE_DISPS and manually
inserted FrameInterpolation_OpenChild/FrameInterpolation_Close child calls.
These nodes contain information that should suffice to identify the MtxF,
so we can find it in an adjacent frame.

We can interpolate an arbitrary amount of frames between two original frames,
given a specific interpolation factor (0=old frame, 0.5=average of frames,
1.0=new frame).
*/

static bool invert_MtxF(const float m[16], float invOut[16]);

using namespace std;

namespace {

enum class Op {
    Marker,
    OpenChild,
    CloseChild,

    MtxFPush,
    MtxFPop,
    MtxFPut,
    MtxFMult,
    MtxFTranslate,
    MtxFScale,
    MtxFRotate1Coord,
    MtxFMultVec3fNoTranslate,
    MtxFMultVec3f,
    MtxFMtxFToMtx,
    MtxFToMtx,
    MtxFRotateAxis,
    SkinMtxFMtxFToMtx
};

typedef pair<const void*, uintptr_t> label;

union Data {
    Data() {
    }

    struct {
        MtxF** MtxF;
    } MtxF_ptr;

    struct {
        const char* file;
        int line;
    } marker;

    struct {
        MtxF* mtxF;
        MtxF mf;
        u8 mode;
    } MtxF_mult;

    struct {
        MtxF* MtxF;
        f32 x, y, z;
        u8 mode;
    } MtxF_translate, MtxF_scale;

    struct {
        MtxF* MtxF;
        u32 coord;
        f32 value;
        u8 mode;
    } MtxF_rotate_1_coord;

    struct {
        MtxF* MtxF;
        Vec3f src;
        Vec3f dest;
    } MtxF_vec_translate;

    struct {
        MtxF* MtxF;
        Vec3f src;
        Vec3f dest;
    } MtxF_vec_no_translate;

    struct {
        MtxF* MtxF;
        Vec3f translation;
        Vec3s rotation;
    } MtxF_translate_rotate_zyx;

    struct {
        MtxF* MtxF;
        f32 translateX, translateY, translateZ;
        Vec3s rot;
        // MtxF mtx;
        bool has_mtx;
    } MtxF_set_translate_rotate_yxz;

    struct {
        MtxF src;
        Mtx* dest;
    } MtxF_mtxf_to_mtx;

    struct {
        Mtx* dest;
        MtxF src;
        bool has_adjusted;
    } MtxF_to_mtx;

    struct {
        MtxF mf;
    } MtxF_replace_rotation;

    struct {
        f32 angle;
        Vec3f axis;
        u8 mode;
    } MtxF_rotate_axis;

    struct {
        label key;
        size_t idx;
    } open_child;
};

struct Path {
    map<label, vector<Path>> children;
    map<Op, vector<Data>> ops;
    vector<pair<Op, size_t>> items;
    // `items` drives replay and so includes OpenChild. `op_signature` is the same
    // sequence with the OpenChild entries removed: only this path's *own* ops, the
    // ones paired by ordinal index. Child subtrees are matched by label key
    // instead, so how many of them there are has no responsibility on whether this path's
    // matrices can be paired.
    vector<pair<Op, size_t>> op_signature;
};

struct Recording {
    Path root_path;
};

bool is_recording;
vector<Path*> current_path;
uint32_t camera_epoch;
uint32_t previous_camera_epoch;
Recording current_recording;
Recording previous_recording;

bool next_is_actor_pos_rot_MtxF;
bool has_inv_actor_mtx;
MtxF inv_actor_mtx;
size_t inv_actor_mtx_path_index;

Data& append(Op op) {
    auto& m = current_path.back()->ops[op];
    current_path.back()->items.emplace_back(op, m.size());
    if (op != Op::OpenChild) {
        current_path.back()->op_signature.emplace_back(op, m.size());
    }
    return m.emplace_back();
}

MtxF* MtxF_GetCurrent() {
    return gInterpolationMatrix;
}

struct InterpolateCtx {
    float step;
    float w;
    unordered_map<Mtx*, MtxF> mtx_replacements;
    MtxF tmp_mtxf, tmp_mtxf2;
    Vec3f tmp_vec3f, tmp_vec3f2;
    Vec3s tmp_vec3s;
    MtxF actor_mtx;

    MtxF* new_replacement(Mtx* addr) {
        return &mtx_replacements[addr];
    }

    void interpolate_mtxf(MtxF* res, MtxF* o, MtxF* n) {
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                res->mf[i][j] = w * o->mf[i][j] + step * n->mf[i][j];
            }
        }
    }

    float lerp(f32 o, f32 n) {
        return w * o + step * n;
    }

    void lerp_vec3f(Vec3f* res, Vec3f* o, Vec3f* n) {
        res->x = lerp(o->x, n->x);
        res->y = lerp(o->y, n->y);
        res->z = lerp(o->z, n->z);
    }

    float interpolate_angle(f32 o, f32 n) {
        if (o == n)
            return n;
        o = fmodf(o, 2 * M_PI);
        if (o < 0.0f) {
            o += 2 * M_PI;
        }
        n = fmodf(n, 2 * M_PI);
        if (n < 0.0f) {
            n += 2 * M_PI;
        }
        if (fabsf(o - n) > M_PI) {
            if (o < n) {
                o += 2 * M_PI;
            } else {
                n += 2 * M_PI;
            }
        }
        if (fabsf(o - n) > M_PI / 2) {
            // return n;
        }
        return lerp(o, n);
    }

    s16 interpolate_angle(s16 os, s16 ns) {
        if (os == ns)
            return ns;
        int o = (u16) os;
        int n = (u16) ns;
        u16 res;
        int diff = o - n;
        if (-0x8000 <= diff && diff <= 0x8000) {
            if (diff < -0x4000 || diff > 0x4000) {
                return ns;
            }
            res = (u16) (w * o + step * n);
        } else {
            if (o < n) {
                o += 0x10000;
            } else {
                n += 0x10000;
            }
            diff = o - n;
            if (diff < -0x4000 || diff > 0x4000) {
                return ns;
            }
            res = (u16) (w * o + step * n);
        }
        if (os / 327 == ns / 327 && (s16) res / 327 != os / 327) {
            int bp = 0;
        }
        return res;
    }

    void interpolate_vecs(Vec3f* res, Vec3f* o, Vec3f* n) {
        res->x = interpolate_angle(o->x, n->x);
        res->y = interpolate_angle(o->y, n->y);
        res->z = interpolate_angle(o->z, n->z);
    }

    void interpolate_angles(Vec3s* res, Vec3s* o, Vec3s* n) {
        res->x = interpolate_angle(o->x, n->x);
        res->y = interpolate_angle(o->y, n->y);
        res->z = interpolate_angle(o->z, n->z);
    }

    void interpolate_branch(Path* old_path, Path* new_path) {
        // Preliminary solution: ops are paired by index, so a path whose recorded
        // sequence changed would pair every matrix with an unrelated one. Interpolate
        // it against itself instead preventing weird flashes with curtains and STORY_INTRO.
        if (old_path != new_path && old_path->op_signature != new_path->op_signature) {
            old_path = new_path;
        }

        for (auto& item : new_path->items) {
            Data& new_op = new_path->ops[item.first][item.second];

            if (item.first == Op::OpenChild) {
                if (auto it = old_path->children.find(new_op.open_child.key);
                    it != old_path->children.end() && new_op.open_child.idx < it->second.size())
                {
                    interpolate_branch(
                        &it->second[new_op.open_child.idx],
                        &new_path->children.find(new_op.open_child.key)->second[new_op.open_child.idx]
                    );
                } else {
                    interpolate_branch(
                        &new_path->children.find(new_op.open_child.key)->second[new_op.open_child.idx],
                        &new_path->children.find(new_op.open_child.key)->second[new_op.open_child.idx]
                    );
                }
                continue;
            }

            if (auto it = old_path->ops.find(item.first); it != old_path->ops.end()) {
                if (item.second < it->second.size()) {
                    Data& old_op = it->second[item.second];
                    switch (item.first) {
                        case Op::OpenChild:
                        case Op::CloseChild:
                        case Op::Marker:
                            break;

                        case Op::MtxFPush:
                            // MtxF_Push(&gInterpolationMtxF);
                            break;

                        case Op::MtxFPop:
                            // MtxF_Pop(&gInterpolationMtxF);
                            break;

                            // Unused on SF64
                            // case Op::MtxFPut:
                            //     interpolate_mtxf(&tmp_mtxf, &old_op.MtxF_put.src,
                            //     &new_op.MtxF_put.src); MtxF_Put(&tmp_mtxf); break;

                        case Op::MtxFMult:
                            interpolate_mtxf(&tmp_mtxf, &old_op.MtxF_mult.mf, &new_op.MtxF_mult.mf);
                            // MtxF_Mult(gInterpolationMtxF, (MtxF*) &tmp_mtxf,
                            // new_op.MtxF_mult.mode);
                            break;

                        case Op::MtxFTranslate:
                            // MtxF_Translate(gInterpolationMtxF, lerp(old_op.MtxF_translate.x,
                            // new_op.MtxF_translate.x),
                            //                 lerp(old_op.MtxF_translate.y,
                            //                 new_op.MtxF_translate.y),
                            //                 lerp(old_op.MtxF_translate.z,
                            //                 new_op.MtxF_translate.z),
                            //                 new_op.MtxF_translate.mode);
                            break;

                        case Op::MtxFScale:
                            // MtxF_Scale(gInterpolationMtxF, lerp(old_op.MtxF_scale.x,
                            // new_op.MtxF_scale.x),
                            //              lerp(old_op.MtxF_scale.y, new_op.MtxF_scale.y),
                            //              lerp(old_op.MtxF_scale.z, new_op.MtxF_scale.z),
                            //              new_op.MtxF_scale.mode);
                            break;

                        case Op::MtxFRotate1Coord: {
                            float v =
                                interpolate_angle(old_op.MtxF_rotate_1_coord.value, new_op.MtxF_rotate_1_coord.value);
                            u8 mode = new_op.MtxF_rotate_1_coord.mode;
                            switch (new_op.MtxF_rotate_1_coord.coord) {
                                case 0:
                                    // MtxF_RotateX(gInterpolationMtxF, v, mode);
                                    break;

                                case 1:
                                    // MtxF_RotateY(gInterpolationMtxF, v, mode);
                                    break;

                                case 2:
                                    // MtxF_RotateZ(gInterpolationMtxF, v, mode);
                                    break;
                            }
                            break;
                        }
                        case Op::MtxFMultVec3fNoTranslate: {
                            interpolate_vecs(
                                &tmp_vec3f, &old_op.MtxF_vec_no_translate.src, &new_op.MtxF_vec_no_translate.src
                            );
                            interpolate_vecs(
                                &tmp_vec3f2, &old_op.MtxF_vec_no_translate.dest, &new_op.MtxF_vec_no_translate.dest
                            );
                            // MtxF_MultVec3fNoTranslate(gInterpolationMtxF, &tmp_vec3f,
                            // &tmp_vec3f2);
                            break;
                        }
                        case Op::MtxFMultVec3f: {
                            interpolate_vecs(
                                &tmp_vec3f, &old_op.MtxF_vec_translate.src, &new_op.MtxF_vec_translate.src
                            );
                            interpolate_vecs(
                                &tmp_vec3f2, &old_op.MtxF_vec_translate.dest, &new_op.MtxF_vec_translate.dest
                            );
                            // MtxF_MultVec3f(gInterpolationMtxF, &tmp_vec3f, &tmp_vec3f2);
                            break;
                        }

                        case Op::MtxFMtxFToMtx:
                            interpolate_mtxf(
                                new_replacement(new_op.MtxF_mtxf_to_mtx.dest),
                                &old_op.MtxF_mtxf_to_mtx.src,
                                &new_op.MtxF_mtxf_to_mtx.src
                            );
                            break;

                        case Op::MtxFToMtx: {
                            //*new_replacement(new_op.MtxF_to_mtx.dest) = *MtxF_GetCurrent();
                            if (old_op.MtxF_to_mtx.has_adjusted && new_op.MtxF_to_mtx.has_adjusted) {
                                interpolate_mtxf(&tmp_mtxf, &old_op.MtxF_to_mtx.src, &new_op.MtxF_to_mtx.src);
                                // MtxF_MtxFMtxFMult(&actor_mtx, &tmp_mtxf,
                                // new_replacement(new_op.MtxF_to_mtx.dest));
                            } else {
                                interpolate_mtxf(
                                    new_replacement(new_op.MtxF_to_mtx.dest),
                                    &old_op.MtxF_to_mtx.src,
                                    &new_op.MtxF_to_mtx.src
                                );
                            }
                            break;
                        }

                        case Op::MtxFRotateAxis: {
                            lerp_vec3f(&tmp_vec3f, &old_op.MtxF_rotate_axis.axis, &new_op.MtxF_rotate_axis.axis);
                            auto tmp = interpolate_angle(old_op.MtxF_rotate_axis.angle, new_op.MtxF_rotate_axis.angle);
                            // MtxF_RotateAxis((MtxF*) &tmp_vec3f, tmp, 1.0f, 1.0f, 1.0f,
                            // new_op.MtxF_rotate_axis.mode);
                            break;
                        }
                    }
                }
            }
        }
    }
};

} // anonymous namespace

unordered_map<Mtx*, MtxF> FrameInterpolation_Interpolate(float step) {
    InterpolateCtx ctx;
    ctx.step = step;
    ctx.w = 1.0f - step;
    ctx.interpolate_branch(&previous_recording.root_path, &current_recording.root_path);
    return ctx.mtx_replacements;
}

bool camera_interpolation = true;

void FrameInterpolation_ShouldInterpolateFrame(bool shouldInterpolate) {
    // camera_interpolation = shouldInterpolate;
    is_recording = shouldInterpolate;
}

void FrameInterpolation_StartRecord(void) {
    previous_recording = move(current_recording);
    current_recording = {};
    current_path.clear();
    current_path.push_back(&current_recording.root_path);
    if (!camera_interpolation) {
        // default to interpolating
        camera_interpolation = true;
        is_recording = false;
        return;
    }
    if (GameEngine::GetInterpolationFPS() != 20) {
        is_recording = true;
    }
}

void FrameInterpolation_StopRecord(void) {
    previous_camera_epoch = camera_epoch;
    is_recording = false;
}

void FrameInterpolation_RecordOpenChild(const void* a, uintptr_t b) {
    if (!is_recording)
        return;
    label key = { a, b };
    auto& m = current_path.back()->children[key];
    append(Op::OpenChild).open_child = { key, m.size() };
    current_path.push_back(&m.emplace_back());
}

void FrameInterpolation_RecordCloseChild(void) {
    if (!is_recording)
        return;
    // append(Op::CloseChild);
    if (has_inv_actor_mtx && current_path.size() == inv_actor_mtx_path_index) {
        has_inv_actor_mtx = false;
    }
    current_path.pop_back();
}

void FrameInterpolation_DontInterpolateCamera(void) {
    camera_epoch = previous_camera_epoch + 1;
}

int FrameInterpolation_GetCameraEpoch(void) {
    return (int) camera_epoch;
}

void FrameInterpolation_RecordActorPosRotMtxF(void) {
    if (!is_recording)
        return;
    next_is_actor_pos_rot_MtxF = true;
}

void FrameInterpolation_RecordMtxFPush(MtxF** MtxF) {
    if (!is_recording)
        return;

    append(Op::MtxFPush).MtxF_ptr = { MtxF };
}

void FrameInterpolation_RecordMarker(const char* file, int line) {
    if (!is_recording)
        return;

    // append(Op::Marker).marker = { file, line };
}

void FrameInterpolation_RecordMtxFPop(MtxF** MtxF) {
    if (!is_recording)
        return;
    append(Op::MtxFPop).MtxF_ptr = { MtxF };
}

void FrameInterpolation_RecordMtxFPut(MtxF* src) {
    if (!is_recording)
        return;
    //    append(Op::MtxFPut).MtxF_put = { MtxF, *src };
}

void FrameInterpolation_RecordMtxFMult(MtxF* mtxF, MtxF* mf, u8 mode) {
    if (!is_recording)
        return;
    append(Op::MtxFMult).MtxF_mult = { mtxF, *mf, mode };
}

void FrameInterpolation_RecordMtxFTranslate(MtxF* MtxF, f32 x, f32 y, f32 z, u8 mode) {
    if (!is_recording)
        return;
    append(Op::MtxFTranslate).MtxF_translate = { MtxF, x, y, z, mode };
}

void FrameInterpolation_RecordMtxFScale(MtxF* MtxF, f32 x, f32 y, f32 z, u8 mode) {
    if (!is_recording)
        return;
    append(Op::MtxFScale).MtxF_scale = { MtxF, x, y, z, mode };
}

void FrameInterpolation_RecordMtxFMultVec3fNoTranslate(MtxF* MtxF, Vec3f src, Vec3f dest) {
    if (!is_recording)
        return;
    append(Op::MtxFMultVec3fNoTranslate).MtxF_vec_no_translate = { MtxF, src, dest };
}

void FrameInterpolation_RecordMtxFMultVec3f(MtxF* MtxF, Vec3f src, Vec3f dest) {
    if (!is_recording)
        return;
    append(Op::MtxFMultVec3f).MtxF_vec_translate = { MtxF, src, dest };
}

void FrameInterpolation_RecordMtxFRotate1Coord(MtxF* MtxF, u32 coord, f32 value, u8 mode) {
    if (!is_recording)
        return;
    append(Op::MtxFRotate1Coord).MtxF_rotate_1_coord = { MtxF, coord, value, mode };
}

void FrameInterpolation_RecordMatrixMtxFToMtx(MtxF* src, Mtx* dest) {
    if (!is_recording)
        return;
    append(Op::MtxFMtxFToMtx).MtxF_mtxf_to_mtx = { *src, dest };
}

void FrameInterpolation_RecordMtxFToMtx(Mtx* dest, char* file, s32 line) {
    if (!is_recording)
        return;
    auto& d = append(Op::MtxFToMtx).MtxF_to_mtx = { dest };
    if (has_inv_actor_mtx) {
        d.has_adjusted = true;
        // MtxF_MtxFMtxFMult(&inv_actor_mtx, MtxF_GetCurrent(), &d.src);
    } else {
        d.src = *MtxF_GetCurrent();
    }
}

void FrameInterpolation_RecordMtxFRotateAxis(f32 angle, Vec3f* axis, u8 mode) {
    if (!is_recording)
        return;
    append(Op::MtxFRotateAxis).MtxF_rotate_axis = { angle, *axis, mode };
}

void FrameInterpolation_RecordSkinMtxFMtxFToMtx(MtxF* src, Mtx* dest) {
    if (!is_recording)
        return;
    FrameInterpolation_RecordMatrixMtxFToMtx(src, dest);
}

// https://stackoverflow.com/questions/1148309/inverting-a-4x4-MtxF
static bool invert_MtxF(const float m[16], float invOut[16]) {
    float inv[16], det;
    int i;

    inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14]
        + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];

    inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14]
        - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];

    inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13]
        + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];

    inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13]
        - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];

    inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14]
        - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];

    inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14]
        + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];

    inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13]
        - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];

    inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13]
        + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];

    inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7]
        - m[13] * m[3] * m[6];

    inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14]
        - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];

    inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13]
        + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];

    inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13]
        - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7]
        + m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7]
        - m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7]
        + m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6]
        - m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0) {
        return false;
    }

    det = 1.0 / det;

    for (i = 0; i < 16; i++) {
        invOut[i] = inv[i] * det;
    }

    return true;
}
