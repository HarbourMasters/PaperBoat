#pragma once

#include "common.h"
#include "map.h"
#include "npc.h"

#ifdef __cplusplus
extern "C" {
#endif

void TTYD64_nm_BindMessage(Bytecode* script, const u8* msg);
void TTYD64_nm_InstallGenerated(void);
void TTYD64_nm_InstallRegistry(void);

API_CALLABLE(TTYD64_nm_AddBadge);
API_CALLABLE(TTYD64_nm_AddKeyItem);
API_CALLABLE(TTYD64_nm_GetVarFromVar);
API_CALLABLE(TTYD64_nm_ToggleBool);
API_CALLABLE(TTYD64_nm_TableWordRead);
API_CALLABLE(TTYD64_nm_ArrayWordRead);
API_CALLABLE(TTYD64_nm_ArrayWordWrite);
API_CALLABLE(TTYD64_nm_kpa_138_GetFXPos);
API_CALLABLE(TTYD64_nm_jan_25_UpdateRockPosInTable);
API_CALLABLE(TTYD64_nm_jan_25_RestereRocksTable);
API_CALLABLE(TTYD64_nm_omo_19_UpdateRotatingPlatforms_Movement_1);
API_CALLABLE(TTYD64_nm_omo_19_UpdateRotatingPlatforms_Movement_2);
API_CALLABLE(TTYD64_nm_omo_19_UpdateRotatingPlatforms_Movement_3);
void TTYD64_nm_isk_20_FlameAI(FireBarData* data, s32 mode);
void TTYD64_nm_kpa_136_FlameAI(FireBarData* data, s32 mode);

extern Vec3i TTYD64_kpa_138_Data_FXPosTable[9];

#ifdef __cplusplus
}
#endif
