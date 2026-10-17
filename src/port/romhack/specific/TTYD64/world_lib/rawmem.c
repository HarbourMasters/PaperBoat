#include "common.h"
#include "effects.h"
#include "port/Engine.h"
#include "dx/versioning.h"
#include "../include/ttyd64_flags.h"
#include "../include/ttyd64_rawmem.h"
#include "world_lib.h"
#include <string.h>

static u32 load_native(const void* addr, s32 size) {
    switch (size) {
        case 1:
            return *(const u8*) addr;
        case 2:
            return *(const u16*) addr;
        default:
            return *(const u32*) addr;
    }
}

static void store_native(void* addr, s32 size, u32 value) {
    switch (size) {
        case 1:
            *(u8*) addr = value;
            break;
        case 2:
            *(u16*) addr = value;
            break;
        default:
            *(u32*) addr = value;
            break;
    }
}

static u32 size_mask(s32 size) {
    return size == 1 ? 0xFF : size == 2 ? 0xFFFF : 0xFFFFFFFF;
}

u32 TTYD64_ReadBE(const void* base, u32 offset, u32 size) {
    const u8* p = (const u8*) base + offset;
    u32 v = 0;
    u32 i;

    for (i = 0; i < size; i++) {
        v = (v << 8) | p[i];
    }
    return v;
}

void TTYD64_WriteBE(void* base, u32 offset, u32 size, u32 value) {
    u8* p = (u8*) base + offset;
    u32 i;

    for (i = 0; i < size; i++) {
        p[i] = value >> (8 * (size - 1 - i));
    }
}

u32* TTYD64_ModFlagWords(void) {
    return (u32*) &gCurrentSaveFile.globalFlags[TTYD64_MODFLAG_BASE / 32];
}

u8* TTYD64_ModBytes(void) {
    return (u8*) &gCurrentSaveFile.globalBytes[TTYD64_MODBYTE_BASE];
}

static b32 field_get(s32 field, void* ptr, intptr_t* out, s32* sign) {
    TTYD64FieldRef r;
    u32 raw;

    if (!TTYD64_WorldLib_FieldRef(field, ptr, &r)) {
        GameEngine_LogWarn("TTYD64: raw field %d read without a valid target", field);
        *out = 0;
        *sign = SG_ZERO;
        return false;
    }
    *sign = r.sign;
    if (r.lvSize == sizeof(void*) && r.lvSize > 4) {
        *out = *(intptr_t*) r.addr;
        return true;
    }
    raw = load_native(r.addr, r.lvSize) & size_mask(r.n64Size);
    if (r.sign == SG_SIGN) {
        *out = r.n64Size == 1 ? (s8) raw : r.n64Size == 2 ? (s16) raw : (s32) raw;
    } else if (r.n64Size == 4 && r.sign != SG_FLOAT) {
        *out = (s32) raw;
    } else {
        *out = raw;
    }
    return true;
}

static b32 field_set(s32 field, void* ptr, intptr_t value) {
    TTYD64FieldRef r;

    if (!TTYD64_WorldLib_FieldRef(field, ptr, &r)) {
        GameEngine_LogWarn("TTYD64: raw field %d write without a valid target", field);
        return false;
    }
    if (r.lvSize == sizeof(void*) && r.lvSize > 4) {
        *(intptr_t*) r.addr = value;
    } else {
        store_native(r.addr, r.lvSize, (u32) value);
    }
    return true;
}

static void read_to_var(Evt* script, s32 field, void* ptr, Bytecode outVar) {
    intptr_t v;
    s32 sign;
    u32 bits;
    f32 f;

    field_get(field, ptr, &v, &sign);
    if (sign == SG_FLOAT) {
        bits = (u32) v;
        memcpy(&f, &bits, sizeof(f));
        evt_set_float_variable(script, outVar, f);
    } else {
        evt_set_variable(script, outVar, v);
    }
}

static void write_from_arg(Evt* script, s32 field, void* ptr, Bytecode arg) {
    TTYD64FieldRef r;
    u32 bits;
    f32 f;

    if (TTYD64_WorldLib_FieldRef(field, ptr, &r) && r.sign == SG_FLOAT) {
        f = evt_get_float_variable(script, arg);
        memcpy(&bits, &f, sizeof(bits));
        field_set(field, ptr, bits);
    } else {
        field_set(field, ptr, evt_get_variable(script, arg));
    }
}

s32 TTYD64_FieldRead(s32 field, void* ptr) {
    intptr_t v;
    s32 sign;

    field_get(field, ptr, &v, &sign);
    return (s32) v;
}

void TTYD64_FieldWrite(s32 field, void* ptr, s32 value) {
    field_set(field, ptr, value);
}

API_CALLABLE(TTYD64_ReadField) {
    Bytecode* args = script->ptrReadPos;
    s32 field = evt_get_variable(script, *args++);

    read_to_var(script, field, NULL, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_WriteField) {
    Bytecode* args = script->ptrReadPos;
    s32 field = evt_get_variable(script, *args++);

    write_from_arg(script, field, NULL, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_ReadPtrField) {
    Bytecode* args = script->ptrReadPos;
    void* ptr = (void*) evt_get_variable(script, *args++);
    s32 field = evt_get_variable(script, *args++);

    read_to_var(script, field, ptr, *args++);
    return ApiStatus_DONE2;
}

extern EffectInstance* gEffectInstances[96];

static EffectInstance* live_effect(Bytecode value) {
    s32 i;

    if (value == 0) {
        return NULL;
    }
    for (i = 0; i < ARRAY_COUNT(gEffectInstances); i++) {
        if (gEffectInstances[i] != NULL && (Bytecode) gEffectInstances[i] == value) {
            return gEffectInstances[i];
        }
    }
    return NULL;
}

API_CALLABLE(TTYD64_GetEffect) {
    Bytecode* args = script->ptrReadPos;
    EffectInstance* effect = live_effect(evt_get_variable(script, *args++));

    evt_set_variable(script, *args++, (Bytecode) effect);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetEffectData) {
    Bytecode* args = script->ptrReadPos;
    EffectInstance* effect = live_effect(evt_get_variable(script, *args++));

    evt_set_variable(script, *args++, effect != NULL ? (Bytecode) effect->data.any : 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_WritePtrField) {
    Bytecode* args = script->ptrReadPos;
    void* ptr = (void*) evt_get_variable(script, *args++);
    s32 field = evt_get_variable(script, *args++);

    write_from_arg(script, field, ptr, *args++);
    return ApiStatus_DONE2;
}
