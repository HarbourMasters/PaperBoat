#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MOD_BATTLE_POPUP_FIRST 0x100
#define MOD_BATTLE_POPUP_LAST  0x7FFF

int32_t Mod_RegisterBattlePopup(const char* owner, int32_t msgID, int32_t layoutLike);
int32_t Mod_RegisterBattlePopupAt(const char* owner, int32_t index, int32_t msgID, int32_t layoutLike);

#ifdef __cplusplus
}
#endif
