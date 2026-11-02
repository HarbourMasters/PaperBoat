#include "Panels.h"

#include <iterator>
#include <map>
#include <string>

#include <spdlog/spdlog.h>

#include "ModInternal.h"
#include "port/ShipInit.hpp"

extern "C" {
#include "common.h"
}

extern "C" MenuPanel* gPausePanels[];
extern "C" s32 gPopupState;
extern "C" PopupMenu* gPopupMenu;

namespace {

constexpr int32_t kPauseSlots = 7;
constexpr s32 kPopupStateParked = 2;
constexpr u8 kPopupWindowHidden = 0x20;
constexpr u8 kPopupContentShown = 0x11;
constexpr u8 kPopupOtherShown = 0x01;

typedef void (*PauseDrawFn)(MenuPanel*, s32, s32, s32, s32, s32, s32);

const s32 kContentWindow[kPauseSlots] = {
    -1, WIN_PAUSE_STATS, WIN_PAUSE_BADGES, WIN_PAUSE_ITEMS, WIN_PAUSE_PARTNERS, WIN_PAUSE_SPIRITS, WIN_PAUSE_MAP,
};

struct PanelEntry {
    std::string owner;
    ModPanelOps ops;
};

struct BattleStateEntry {
    std::string owner;
    ModBattleStateOps ops;
};

struct PauseSlot {
    bool wrapped;
    MenuPanel* vanilla;
    MenuPanel wrapper;
    ModPanelOps ops;
    PauseDrawFn vanillaDraw;
};

enum PopupPhase {
    POPUP_IDLE,
    POPUP_PENDING,
    POPUP_ACTIVE,
    POPUP_CLOSING,
};

struct PopupPanel {
    PopupPhase phase;
    int32_t result;
    PopupMenu* menu;
    ModPopupPanelOps ops;
};

PanelEntry* sPanels[MOD_PANEL_COUNT];
PauseSlot sSlots[kPauseSlots];
PopupPanel sPopup;

std::map<int32_t, BattleStateEntry>& ReplacedBattleStates() {
    static std::map<int32_t, BattleStateEntry> sStates;
    return sStates;
}

int32_t SlotOf(int32_t panel) {
    return panel >= MOD_PANEL_PAUSE_STATS && panel <= MOD_PANEL_PAUSE_MAP ? panel - MOD_PANEL_PAUSE_STATS + 1 : -1;
}

int32_t SlotOfWrapper(MenuPanel* panel) {
    for (int32_t i = 1; i < kPauseSlots; i++) {
        if (sSlots[i].wrapped && panel == &sSlots[i].wrapper) {
            return i;
        }
    }
    return -1;
}

MenuPanel* VanillaPanelAt(int32_t slot) {
    return sSlots[slot].wrapped ? sSlots[slot].vanilla : gPausePanels[slot];
}

void PauseDrawTrampoline(MenuPanel* panel, s32 x, s32 y, s32 width, s32 height, s32 opacity, s32 darkening) {
    const int32_t slot = SlotOfWrapper(panel);

    if (slot < 0 || sSlots[slot].ops.draw == nullptr) {
        return;
    }
    const ModPanelDraw draw = { panel, x, y, width, height, opacity, darkening };
    sSlots[slot].ops.draw(&draw);
}

void PauseInitTrampoline(MenuPanel* panel) {
    const int32_t slot = SlotOfWrapper(panel);

    if (slot < 0) {
        return;
    }
    PauseSlot& s = sSlots[slot];
    if (s.ops.init != nullptr) {
        s.ops.init(panel);
    } else if (s.vanilla->fpInit != nullptr) {
        s.vanilla->fpInit(panel);
    }
    if (s.ops.draw != nullptr && panel->initialized) {
        Window* window = &gWindows[kContentWindow[slot]];

        if (window->drawContentsArg0 == panel) {
            s.vanillaDraw = (PauseDrawFn) window->fpDrawContents;
            window->fpDrawContents = (decltype(window->fpDrawContents)) PauseDrawTrampoline;
        }
    }
}

void PauseInputTrampoline(MenuPanel* panel) {
    const int32_t slot = SlotOfWrapper(panel);

    if (slot < 0) {
        return;
    }
    if (sSlots[slot].ops.input != nullptr) {
        sSlots[slot].ops.input(panel);
    } else if (sSlots[slot].vanilla->fpHandleInput != nullptr) {
        sSlots[slot].vanilla->fpHandleInput(panel);
    }
}

void PauseUpdateTrampoline(MenuPanel* panel) {
    const int32_t slot = SlotOfWrapper(panel);

    if (slot < 0) {
        return;
    }
    if (sSlots[slot].ops.update != nullptr) {
        sSlots[slot].ops.update(panel);
    } else if (sSlots[slot].vanilla->fpUpdate != nullptr) {
        sSlots[slot].vanilla->fpUpdate(panel);
    }
}

void PauseCleanupTrampoline(MenuPanel* panel) {
    const int32_t slot = SlotOfWrapper(panel);

    if (slot < 0) {
        return;
    }
    if (sSlots[slot].ops.cleanup != nullptr) {
        sSlots[slot].ops.cleanup(panel);
    } else if (sSlots[slot].vanilla->fpCleanup != nullptr) {
        sSlots[slot].vanilla->fpCleanup(panel);
    }
}

void Unwrap(MenuPanel** panels, int32_t slot) {
    PauseSlot& s = sSlots[slot];
    MenuPanel* vanilla = s.vanilla;
    const MenuPanel keep = *vanilla;

    *vanilla = s.wrapper;
    vanilla->numCols = keep.numCols;
    vanilla->numRows = keep.numRows;
    vanilla->fpInit = keep.fpInit;
    vanilla->fpHandleInput = keep.fpHandleInput;
    vanilla->fpUpdate = keep.fpUpdate;
    vanilla->fpCleanup = keep.fpCleanup;
    panels[slot] = vanilla;
    s.wrapped = false;
    s.vanilla = nullptr;
    s.vanillaDraw = nullptr;
}

void Wrap(MenuPanel** panels, int32_t slot, const ModPanelOps& ops) {
    PauseSlot& s = sSlots[slot];
    MenuPanel* vanilla = panels[slot];

    s.vanilla = vanilla;
    s.ops = ops;
    s.vanillaDraw = nullptr;
    s.wrapper = *vanilla;
    if (ops.numCols != 0) {
        s.wrapper.numCols = ops.numCols;
    }
    if (ops.numRows != 0) {
        s.wrapper.numRows = ops.numRows;
    }
    s.wrapper.fpInit =
        (ops.init != nullptr || ops.draw != nullptr || vanilla->fpInit != nullptr) ? PauseInitTrampoline : nullptr;
    s.wrapper.fpHandleInput =
        (ops.input != nullptr || vanilla->fpHandleInput != nullptr) ? PauseInputTrampoline : nullptr;
    s.wrapper.fpUpdate = (ops.update != nullptr || vanilla->fpUpdate != nullptr) ? PauseUpdateTrampoline : nullptr;
    s.wrapper.fpCleanup = (ops.cleanup != nullptr || vanilla->fpCleanup != nullptr) ? PauseCleanupTrampoline : nullptr;
    s.wrapped = true;
    panels[slot] = &s.wrapper;
}

void OnPauseMenuOpen(IEvent* event) {
    auto* ev = (OnPauseMenu*) event;

    if (ev->phase != PAUSE_MENU_OPEN || ev->panels == nullptr) {
        return;
    }
    for (int32_t slot = 1; slot < kPauseSlots && slot < ev->count; slot++) {
        if (sSlots[slot].wrapped) {
            Unwrap(ev->panels, slot);
        }
        const PanelEntry* entry = sPanels[MOD_PANEL_PAUSE_STATS + slot - 1];
        if (entry != nullptr && ev->panels[slot] != nullptr) {
            Wrap(ev->panels, slot, entry->ops);
        }
    }
}

void OnPauseMenuClose(IEvent* event) {
    auto* ev = (OnPauseMenu*) event;

    if (ev->phase != PAUSE_MENU_CLOSE || ev->panels == nullptr) {
        return;
    }
    for (int32_t slot = 1; slot < kPauseSlots && slot < ev->count; slot++) {
        if (sSlots[slot].wrapped) {
            Unwrap(ev->panels, slot);
        }
    }
}

void OnStatusBarPanelListener(IEvent* event) {
    auto* ev = (OnStatusBarPanel*) event;
    const PanelEntry* entry = sPanels[MOD_PANEL_STATUS_BAR];

    if (entry == nullptr) {
        return;
    }
    switch (ev->phase) {
        case STATUS_BAR_PHASE_INIT:
            if (entry->ops.init != nullptr) {
                entry->ops.init(nullptr);
            }
            break;
        case STATUS_BAR_PHASE_SYNC:
            if (entry->ops.sync != nullptr) {
                entry->ops.sync();
            }
            break;
        case STATUS_BAR_PHASE_DRAW:
            if (entry->ops.draw != nullptr) {
                const ModPanelDraw draw = { nullptr, ev->x, ev->y, 0, 0, 255, 0 };
                entry->ops.draw(&draw);
                event->Cancelled = true;
            }
            break;
    }
}

void OnBattleStateUpdateListener(IEvent* event) {
    auto* ev = (OnBattleStateUpdate*) event;
    const auto& states = ReplacedBattleStates();
    const auto it = states.find(ev->state);

    if (it == states.end() || it->second.ops.update == nullptr) {
        return;
    }
    it->second.ops.update();
    event->Cancelled = true;
}

void SetPopupWindowFlags(u8 content, u8 other) {
    gWindows[WIN_POPUP_CONTENT].flags = content;
    gWindows[WIN_POPUP_DESC].flags = other;
    gWindows[WIN_POPUP_PROMPT].flags = other;
}

void ClosePopupPanel() {
    PopupPanel popup = sPopup;

    sPopup = {};
    if (popup.ops.close != nullptr) {
        popup.ops.close(popup.menu, popup.result);
    }
    SetPopupWindowFlags(kPopupContentShown, kPopupOtherShown);
}

void OnPopupPanelFrame(IEvent* event) {
    switch (sPopup.phase) {
        case POPUP_IDLE:
            return;
        case POPUP_PENDING:
            SetPopupWindowFlags(kPopupWindowHidden, kPopupWindowHidden);
            if (sPopup.ops.open != nullptr) {
                sPopup.ops.open(sPopup.menu);
            }
            sPopup.phase = POPUP_ACTIVE;
            if (sPopup.ops.frame != nullptr) {
                sPopup.ops.frame(sPopup.menu, false);
            }
            return;
        case POPUP_ACTIVE: {
            const int32_t result =
                sPopup.ops.frame != nullptr ? sPopup.ops.frame(sPopup.menu, true) : MOD_POPUP_PANEL_BACK;

            if (result == MOD_POPUP_PANEL_BACK) {
                gPopupState = POPUP_STATE_CHOOSING;
            }
            if (result != MOD_POPUP_PANEL_STAY) {
                sPopup.result = result;
                sPopup.phase = POPUP_CLOSING;
            }
            return;
        }
        case POPUP_CLOSING: {
            const bool chose = sPopup.result == MOD_POPUP_PANEL_CHOSE;

            ClosePopupPanel();
            if (chose) {
                gPopupState = POPUP_STATE_CHOSE_BATTLE;
            }
            return;
        }
    }
}

void OnPopupMenuClosed(IEvent* event) {
    auto* ev = (OnPopupMenu*) event;

    if (ev->phase != POPUP_MENU_CLOSED || sPopup.phase == POPUP_IDLE || ev->menu != sPopup.menu) {
        return;
    }
    if (sPopup.phase != POPUP_CLOSING) {
        sPopup.result = MOD_POPUP_PANEL_BACK;
    }
    if (sPopup.phase == POPUP_PENDING) {
        sPopup = {};
        return;
    }
    PopupPanel popup = sPopup;

    sPopup = {};
    if (popup.ops.close != nullptr) {
        popup.ops.close(popup.menu, popup.result);
    }
}

void OnPopupPanelReset(IEvent* event) {
    sPopup = {};
}

void Listen() {
    REGISTER_LISTENER(OnPauseMenu, EVENT_PRIORITY_LOW, OnPauseMenuOpen);
    REGISTER_LISTENER(OnPauseMenu, EVENT_PRIORITY_HIGH, OnPauseMenuClose);
    REGISTER_LISTENER(OnStatusBarPanel, EVENT_PRIORITY_NORMAL, OnStatusBarPanelListener);
    REGISTER_LISTENER(OnBattleStateUpdate, EVENT_PRIORITY_NORMAL, OnBattleStateUpdateListener);
    REGISTER_LISTENER(OnStatusBarUpdated, EVENT_PRIORITY_LOW, OnPopupPanelFrame);
    REGISTER_LISTENER(OnPopupMenu, EVENT_PRIORITY_NORMAL, OnPopupMenuClosed);
    REGISTER_LISTENER(OnPlayerDataClear, EVENT_PRIORITY_NORMAL, OnPopupPanelReset);
}

RegisterShipInitFunc sPanelsInit(Listen);

template <int32_t Slot> void VanillaInit(MenuPanel* panel) {
    MenuPanel* vanilla = VanillaPanelAt(Slot);

    if (vanilla->fpInit != nullptr) {
        vanilla->fpInit(panel);
    }
}

template <int32_t Slot> void VanillaInput(MenuPanel* panel) {
    MenuPanel* vanilla = VanillaPanelAt(Slot);

    if (vanilla->fpHandleInput != nullptr) {
        vanilla->fpHandleInput(panel);
    }
}

template <int32_t Slot> void VanillaUpdate(MenuPanel* panel) {
    MenuPanel* vanilla = VanillaPanelAt(Slot);

    if (vanilla->fpUpdate != nullptr) {
        vanilla->fpUpdate(panel);
    }
}

template <int32_t Slot> void VanillaCleanup(MenuPanel* panel) {
    MenuPanel* vanilla = VanillaPanelAt(Slot);

    if (vanilla->fpCleanup != nullptr) {
        vanilla->fpCleanup(panel);
    }
}

template <int32_t Slot> void VanillaDraw(const ModPanelDraw* draw) {
    const PauseDrawFn fn = sSlots[Slot].vanillaDraw;

    if (fn != nullptr) {
        fn(draw->panel, draw->x, draw->y, draw->width, draw->height, draw->opacity, draw->darkening);
    }
}

template <int32_t Slot> constexpr ModPanelOps VanillaOps() {
    return { VanillaInit<Slot>,
             nullptr,
             VanillaInput<Slot>,
             VanillaUpdate<Slot>,
             VanillaDraw<Slot>,
             VanillaCleanup<Slot>,
             0,
             0 };
}

const ModPanelOps kVanillaOps[MOD_PANEL_COUNT] = {
    {}, VanillaOps<1>(), VanillaOps<2>(), VanillaOps<3>(), VanillaOps<4>(), VanillaOps<5>(), VanillaOps<6>(),
};

} // namespace

extern "C" int32_t Mod_ReplacePanel(const char* owner, int32_t panel, const ModPanelOps* ops) {
    const std::string name = Mod::OwnerName(owner);

    if (panel < 0 || panel >= MOD_PANEL_COUNT || ops == nullptr) {
        SPDLOG_ERROR("Mod: {} replaced panel {}, invalid", name, panel);
        return -1;
    }
    if (sPanels[panel] != nullptr && sPanels[panel]->owner != name) {
        SPDLOG_ERROR("Mod: {} replaced panel {}, already replaced by {}", name, panel, sPanels[panel]->owner);
        return -1;
    }
    delete sPanels[panel];
    sPanels[panel] = new PanelEntry { name, *ops };
    return 0;
}

extern "C" const ModPanelOps* Mod_VanillaPanel(int32_t panel) {
    if (panel < 0 || panel >= MOD_PANEL_COUNT) {
        return nullptr;
    }
    return &kVanillaOps[panel];
}

extern "C" int32_t Mod_PanelReplaced(int32_t panel) {
    return panel >= 0 && panel < MOD_PANEL_COUNT && sPanels[panel] != nullptr;
}

extern "C" int32_t Mod_ReplaceBattleState(const char* owner, int32_t state, const ModBattleStateOps* ops) {
    const std::string name = Mod::OwnerName(owner);
    auto& states = ReplacedBattleStates();
    const auto it = states.find(state);

    if (ops == nullptr) {
        SPDLOG_ERROR("Mod: {} replaced battle state {}, invalid", name, state);
        return -1;
    }
    if (it != states.end() && it->second.owner != name) {
        SPDLOG_ERROR("Mod: {} replaced battle state {}, already replaced by {}", name, state, it->second.owner);
        return -1;
    }
    states[state] = { name, *ops };
    return 0;
}

extern "C" int32_t Mod_OpenPopupPanel(const char* owner, PopupMenu* menu, const ModPopupPanelOps* ops) {
    if (menu == nullptr || ops == nullptr || menu != gPopupMenu) {
        SPDLOG_ERROR("Mod: {} opened a popup panel without the current popup menu", Mod::OwnerName(owner));
        return -1;
    }
    if (sPopup.phase != POPUP_IDLE) {
        SPDLOG_ERROR("Mod: {} opened a popup panel while another one is open", Mod::OwnerName(owner));
        return -1;
    }
    sPopup = { POPUP_PENDING, MOD_POPUP_PANEL_STAY, menu, *ops };
    gPopupState = kPopupStateParked;
    return 0;
}

void Mod::UnregisterPanels(const std::string& owner) {
    for (auto& entry : sPanels) {
        if (entry != nullptr && entry->owner == owner) {
            delete entry;
            entry = nullptr;
        }
    }
    auto& states = ReplacedBattleStates();
    for (auto it = states.begin(); it != states.end();) {
        it = it->second.owner == owner ? states.erase(it) : std::next(it);
    }
}
