#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MOD_ABILITY_BASE 0x100

typedef enum ModAbilityHolder {
    MOD_ABILITY_HOLDER_PLAYER,
    MOD_ABILITY_HOLDER_PARTNER,
} ModAbilityHolder;

int32_t Mod_RegisterAbility(const char* owner, int32_t moveID, int32_t holder);
int32_t Mod_GetBadgeBPCost(int32_t itemID);

#ifdef __cplusplus
}
#endif
