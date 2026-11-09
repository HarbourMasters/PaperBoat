#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MOD_INLINE_MSG_SECTION 0xFE

int32_t Mod_RegisterInlineMessage(const char* owner, const uint8_t* bytes);

#ifdef __cplusplus
}
#endif
