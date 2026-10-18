#pragma once

#include "common.h"
#include "hud_element.h"
#include "draw_box.h"
#include "script_api/macros.h"
#include "port/Engine.h"
#include "../TTYD64.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_symbols.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TTYD64_hp_LSIconState {
    u8 lsType;
} TTYD64_hp_LSIconState;

extern TTYD64_hp_LSIconState TTYD64_hp_CurrentLSIcon;
extern u8 TTYD64_hp_PartnerHPAnimTimer;
extern const DefaultWindowStyle TTYD64_hp_BoxStyles[4];
extern const s32 TTYD64_hp_SPIncrementOffsets[7];
extern const s16 TTYD64_hp_FirstBoxCoords[4];
extern const u8 TTYD64_hp_FirstBoxOpacity;

extern HudScript TTYD64_hp_IconScript_FPPickup;
extern HudScript TTYD64_hp_IconScript_LifeShroom;
extern HudScript TTYD64_hp_IconScript_LifeShroomBandW;
extern HudScript TTYD64_hp_IconScript_Star;
extern HudScript TTYD64_hp_IconScript_Heart;
extern HudScript TTYD64_hp_IconScript_Shine_Pause;

s32 TTYD64_hp_IsPartnerHPCompatible(void);
s32 TTYD64_hp_GetIconIndexPartnerIcon(void);
void TTYD64_hp_SetIconPalette(s32 hid, u32 rgb);
void TTYD64_hp_PlayHealSFX(void);
void TTYD64_hp_SyncPartnerHP(void);
void TTYD64_hp_UpdateCurrentLS(void);
void TTYD64_hp_StarMeterRemoveBrownOutline(void);
u8* TTYD64_hp_PartnerHPBytes(s32 partnerID);

void TTYD64_hp_StatusBarInit(void);
void TTYD64_hp_StatusBarSync(void);
void TTYD64_hp_StatusBarDraw(void);
void TTYD64_hp_CreateStatusIcons(s32 battle);
void TTYD64_hp_InstallStatusBar(void);

void TTYD64_hp_PauseStatsDraw(
    MenuPanel* menu, s32 baseX, s32 baseY, s32 width, s32 height, s32 opacity, s32 darkening, const s32* iconIDs
);
void TTYD64_hp_PauseStatsInput(MenuPanel* panel);
void TTYD64_hp_InstallPauseStats(void);

void TTYD64_hp_PauseBadgesDraw(
    MenuPanel* menu,
    s32 baseX,
    s32 baseY,
    s32 width,
    s32 height,
    s32 opacity,
    s32 darkening,
    const PauseBadgesView* state
);
void TTYD64_hp_PauseMenuInit(void);
void TTYD64_hp_PauseMenuCleanup(void);
void TTYD64_hp_InstallPauseBadges(void);

void TTYD64_hp_InstallShine(void);

#ifdef __cplusplus
}
#endif
