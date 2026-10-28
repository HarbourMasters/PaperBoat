#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*ModItemCapacityFn)(void);

void Mod_SetItemCapacity(const char* owner, ModItemCapacityFn capacity);

#ifdef __cplusplus
}
#endif
