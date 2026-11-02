#pragma once

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

void TTYD64_Player_BindMessage(Bytecode* script, u8* msg);
void TTYD64_Player_InstallActionCommands(void);

API_CALLABLE(TTYD64_Player_AC_802A9000);
API_CALLABLE(TTYD64_Player_AC_802A9120);
API_CALLABLE(TTYD64_Player_AddBadge);
API_CALLABLE(TTYD64_Player_Refund);
API_CALLABLE(TTYD64_Player_Refund_FreeIcons);
API_CALLABLE(TTYD64_Player_item11_RotateTargets_End);
API_CALLABLE(TTYD64_Player_item11_RotateTargets_Start);
API_CALLABLE(TTYD64_Player_item13_ClearDebuffs);
API_CALLABLE(TTYD64_Player_item17_ClearDebuffs);
API_CALLABLE(TTYD64_Player_item25_Mystery_Roulette);
void TTYD64_Player_item25_EnemySetTarget(void);
API_CALLABLE(TTYD64_Player_item29_ElectroPop_Heal_Enemies);
API_CALLABLE(TTYD64_Player_item30_KookyCookie_Heal_Enemies);
API_CALLABLE(TTYD64_Player_partner1_Charge_GetBoosts);
API_CALLABLE(TTYD64_Player_partner1_Goombario_80238E48);
API_CALLABLE(TTYD64_Player_partner1_Goombario_8023903C);
API_CALLABLE(TTYD64_Player_partner1_Goombario_TattleCam_Start);
API_CALLABLE(TTYD64_Player_partner4_ParcelCheck_TryToGetRandomItem);
API_CALLABLE(TTYD64_Player_partner6_Watt_UpdateSparkles);
API_CALLABLE(TTYD64_Player_partner6_WattFXRemove);
API_CALLABLE(TTYD64_Player_partner6_WattFXBounce);
API_CALLABLE(TTYD64_Player_partner6_WattFXDisableBounce);
API_CALLABLE(TTYD64_Player_partner6_WattFXEnable);
API_CALLABLE(TTYD64_Player_partner6_WattFXDisable);
API_CALLABLE(TTYD64_Player_partner6_WattFXSetEffect);
API_CALLABLE(TTYD64_Player_partner7_WaterBlock_PlayFX_59);
API_CALLABLE(TTYD64_Player_starpower1_ClearDebuffs);
API_CALLABLE(TTYD64_Player_starpower4_802A16F4);

enum TTYD64MoveScratchID {
    TTYD64_MSI_AUTO_MULTIBOUNCE,
    TTYD64_MSI_EARTHQUAKE_JUMP,
    TTYD64_MSI_HAMMER_CHARGE_1,
    TTYD64_MSI_BOW,
    TTYD64_MSI_COUNT,
};

enum TTYD64MoveScratchSlot {
    TTYD64_MS_FLAG,
    TTYD64_MS_RESULT,
    TTYD64_MS_THREAD,
};

typedef struct TTYD64MoveScratch {
    u8 flag;
    u8 result;
    s32 threadID;
} TTYD64MoveScratch;

API_CALLABLE(TTYD64_GetMoveScratch);
API_CALLABLE(TTYD64_SetMoveScratch);
void TTYD64_Player_InstallMoveScratch(void);

#ifdef __cplusplus
}
#endif
