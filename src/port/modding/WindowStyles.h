#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct DefaultWindowStyle;

#define MOD_WINDOW_STYLE_FIRST 23
#define MOD_WINDOW_STYLE_LAST  100

int32_t Mod_RegisterWindowStyles(const char* owner, const struct DefaultWindowStyle* styles, int32_t count);

#ifdef __cplusplus
}
#endif
