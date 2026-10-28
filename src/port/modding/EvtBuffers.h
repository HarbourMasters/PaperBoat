#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Registers a pointer-holding UseBuf table so BufRead steps 8 bytes per slot. The table itself must
// be declared Bytecode[]; an unregistered pointer table is read as 4-byte slots and yields half-pointers.
void Mod_RegisterWideEvtBuffer(const char* owner, const intptr_t* buf, size_t count);

#ifdef __cplusplus
}
#endif
