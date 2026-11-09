#pragma once

#include "common.h"

enum {
    SG_ZERO,
    SG_SIGN,
    SG_FLOAT,
};

typedef struct TTYD64FieldRef {
    void* addr;
    s32 n64Size;
    s32 lvSize;
    s32 sign;
} TTYD64FieldRef;

MessagePrintState* msg_get_printer_by_index(s32 index);

b32 TTYD64_WorldLib_FieldRef(s32 field, void* ptr, TTYD64FieldRef* r);

s32 TTYD64_WorldLib_MsgID(const u8* msg);

void TTYD64_Function_InitDisplayListCode(s32 index);
