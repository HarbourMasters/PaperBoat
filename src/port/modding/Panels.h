#pragma once

#include <stdint.h>

#include "port/hooks/Events.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ModPanelID {
    MOD_PANEL_STATUS_BAR,
    MOD_PANEL_PAUSE_STATS,
    MOD_PANEL_PAUSE_BADGES,
    MOD_PANEL_PAUSE_ITEMS,
    MOD_PANEL_PAUSE_PARTNERS,
    MOD_PANEL_PAUSE_SPIRITS,
    MOD_PANEL_PAUSE_MAP,
    MOD_PANEL_COUNT,
} ModPanelID;

typedef struct ModPanelOps {
    void (*init)(MenuPanel* panel);
    void (*sync)(void);
    void (*input)(MenuPanel* panel);
    void (*update)(MenuPanel* panel);
    void (*draw)(const ModPanelDraw* draw);
    void (*cleanup)(MenuPanel* panel);
    int8_t numCols;
    int8_t numRows;
} ModPanelOps;

int32_t Mod_ReplacePanel(const char* owner, int32_t panel, const ModPanelOps* ops);
const ModPanelOps* Mod_VanillaPanel(int32_t panel);
int32_t Mod_PanelReplaced(int32_t panel);

typedef struct ModBattleStateOps {
    void (*update)(void);
    void (*draw)(void);
} ModBattleStateOps;

int32_t Mod_ReplaceBattleState(const char* owner, int32_t state, const ModBattleStateOps* ops);

typedef enum ModPopupPanelResult {
    MOD_POPUP_PANEL_STAY,
    MOD_POPUP_PANEL_BACK,
    MOD_POPUP_PANEL_CHOSE,
} ModPopupPanelResult;

typedef struct ModPopupPanelOps {
    void (*open)(PopupMenu* menu);
    int32_t (*frame)(PopupMenu* menu, int32_t acceptInput);
    void (*close)(PopupMenu* menu, int32_t result);
} ModPopupPanelOps;

int32_t Mod_OpenPopupPanel(const char* owner, PopupMenu* menu, const ModPopupPanelOps* ops);

#ifdef __cplusplus
}
#endif
