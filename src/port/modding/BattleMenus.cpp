#include "BattleMenus.h"

#include <algorithm>
#include <optional>
#include <string>
#include <vector>

#include <spdlog/spdlog.h>

#include "ModInternal.h"

extern "C" {
#include "common.h"
#include "battle/battle_menu.h"
#include "message_ids.h"
}

namespace {

struct Item {
    BattleMenuEntry entry;
    int32_t errorCode;
    int32_t discount;
    int32_t discountColor;
    int32_t bpCost;
    int32_t sortPriority;
};

struct Provider {
    std::string owner;
    int32_t menu;
    BattleMenuProvider fn;
};

struct Hud {
    std::string owner;
    int32_t menu;
    BattleMenuHud hud;
};

std::vector<Provider>& Providers() {
    static std::vector<Provider> sProviders;
    return sProviders;
}

std::vector<Hud>& Huds() {
    static std::vector<Hud> sHuds;
    return sHuds;
}

std::vector<std::string>& TypeOwners() {
    static std::vector<std::string> sTypeOwners;
    return sTypeOwners;
}

} // namespace

struct BattleMenuList {
    BattleMenuContext ctx;
    int32_t capacity;
    int32_t initial;
    std::vector<Item> items;
};

namespace {

std::optional<BattleMenuList>& Remembered(int32_t menu) {
    static std::optional<BattleMenuList> sLists[BATTLE_MENU_COUNT];
    return sLists[menu];
}

bool ValidMenu(int32_t menu) {
    return menu >= 0 && menu < BATTLE_MENU_COUNT;
}

int32_t Capacity(int32_t menu) {
    switch (menu) {
        case BATTLE_MENU_WHEEL:
            return 6;
        case BATTLE_MENU_STRATEGIES:
            return 6;
        case BATTLE_MENU_MOVES:
            return ARRAY_COUNT(gBattleStatus.submenuMoves);
        case BATTLE_MENU_PARTNER_LIST:
            return ARRAY_COUNT(BattlePopupMenu.ptrIcon);
    }
    return 0;
}

int32_t VanillaStratsErrorMsg(int32_t code) {
    return code == 0 ? MSG_Menus_Battle_CantSwitch2 : MSG_Menus_Battle_CantRunAway;
}

Item DefaultItem(int32_t menu) {
    Item item = {};
    item.entry.menuType = BTL_MENU_TYPE_INVALID;
    item.entry.moveID = MOVE_NONE;
    item.entry.enabled = true;
    item.entry.costPalette = MSG_PAL_STANDARD;
    if (menu == BATTLE_MENU_STRATEGIES) {
        item.entry.errorMsg = MSG_Menus_Battle_CantRunAway;
    }
    return item;
}

void Import(BattleMenuList& list, int32_t count) {
    const int32_t menu = list.ctx.menu;
    PopupMenu* popup = &BattlePopupMenu;

    for (int32_t i = 0; i < count; i++) {
        Item item = DefaultItem(menu);
        BattleMenuEntry& e = item.entry;

        switch (menu) {
            case BATTLE_MENU_WHEEL:
                e.menuType = WheelOptionSubmenu[i];
                e.enabled = WheelOptionEnabled[i];
                e.errorMsg = WheelOptionError[i];
                e.icon = WheelOptionHudScript[i];
                e.nameMsg = WheelOptionName[i];
                break;
            case BATTLE_MENU_STRATEGIES:
                e.menuType = StratsOptionMenuTypes[i];
                e.nameMsg = StratsOptionNames[i];
                e.icon = StratsOptionHudScripts[i];
                e.enabled = StratsOptionEnabled[i];
                e.descMsg = StratsOptionMessage[i];
                item.errorCode = StratsOptionError[i];
                e.errorMsg = VanillaStratsErrorMsg(item.errorCode);
                break;
            case BATTLE_MENU_MOVES:
                e.moveID = gBattleStatus.submenuMoves[i];
                e.userIndex = MovesOptionIndices[i];
                e.icon = MovesOptionHudScripts[i];
                e.nameMsg = MovesOptionNames[i];
                e.descMsg = MovesOptionDesc[i];
                e.enabled = MovesOptionEnabled[i];
                e.errorMsg = MovesOptionError[i];
                e.cost = MovesOptionDisplayCosts[i];
                item.discount = MovesOptionDiscounts[i];
                item.discountColor = MovesOptionDiscountColors[i];
                item.bpCost = MovesOptionBPCosts[i];
                item.sortPriority = MovesOptionSortPriority[i];
                break;
            case BATTLE_MENU_PARTNER_LIST:
                e.icon = popup->ptrIcon[i];
                e.userIndex = popup->userIndex[i];
                e.enabled = popup->enabled[i];
                e.nameMsg = popup->nameMsg[i];
                e.descMsg = popup->descMsg[i];
                e.value = popup->value[i];
                break;
        }
        list.items.push_back(item);
    }
}

void WriteBack(const BattleMenuList& list) {
    PopupMenu* popup = &BattlePopupMenu;

    for (int32_t i = 0; i < (int32_t) list.items.size(); i++) {
        const Item& item = list.items[i];
        const BattleMenuEntry& e = item.entry;

        switch (list.ctx.menu) {
            case BATTLE_MENU_WHEEL:
                WheelOptionSubmenu[i] = e.menuType;
                WheelOptionEnabled[i] = e.enabled;
                WheelOptionError[i] = e.errorMsg;
                WheelOptionHudScript[i] = e.icon;
                WheelOptionName[i] = e.nameMsg;
                break;
            case BATTLE_MENU_STRATEGIES:
                StratsOptionMenuTypes[i] = e.menuType;
                StratsOptionNames[i] = e.nameMsg;
                StratsOptionHudScripts[i] = e.icon;
                StratsOptionEnabled[i] = e.enabled;
                StratsOptionMessage[i] = e.descMsg;
                StratsOptionError[i] = item.errorCode;
                break;
            case BATTLE_MENU_MOVES:
                MovesOptionIndices[i] = e.userIndex;
                MovesOptionHudScripts[i] = e.icon;
                MovesOptionNames[i] = e.nameMsg;
                MovesOptionDesc[i] = e.descMsg;
                MovesOptionEnabled[i] = e.enabled;
                MovesOptionError[i] = (s8) e.errorMsg;
                MovesOptionDisplayCosts[i] = e.cost;
                MovesOptionDiscounts[i] = item.discount;
                MovesOptionDiscountColors[i] = item.discountColor;
                MovesOptionBPCosts[i] = item.bpCost;
                MovesOptionSortPriority[i] = (s8) item.sortPriority;
                break;
            case BATTLE_MENU_PARTNER_LIST:
                popup->ptrIcon[i] = e.icon;
                popup->userIndex[i] = e.userIndex;
                popup->enabled[i] = e.enabled;
                popup->nameMsg[i] = e.nameMsg;
                popup->descMsg[i] = e.descMsg;
                popup->value[i] = e.value;
                break;
        }
    }
}

BattleMenuContext ContextFor(int32_t menu) {
    const auto& list = Remembered(menu);
    if (list.has_value()) {
        return list->ctx;
    }
    return { menu, -1, -1 };
}

const BattleMenuEntry* EntryAt(int32_t menu, int32_t index) {
    const auto& list = Remembered(menu);
    if (!list.has_value() || index < 0 || index >= (int32_t) list->items.size()) {
        return nullptr;
    }
    return &list->items[index].entry;
}

void OnBuilt(IEvent* event) {
    OnBattleMenuBuilt* ev = (OnBattleMenuBuilt*) event;
    const int32_t menu = ev->menu;

    if (!ValidMenu(menu)) {
        return;
    }
    std::vector<BattleMenuProvider> providers;
    for (const Provider& provider : Providers()) {
        if (provider.menu == menu) {
            providers.push_back(provider.fn);
        }
    }
    if (providers.empty()) {
        Remembered(menu).reset();
        return;
    }

    BattleMenuList list;
    list.ctx = { menu, ev->who, ev->submenu };
    list.capacity = Capacity(menu);
    list.initial = *ev->initialPos;
    list.items.reserve(list.capacity);
    Import(list, std::clamp(*ev->count, 0, list.capacity));

    for (BattleMenuProvider provider : providers) {
        provider(&list.ctx, &list);
    }

    WriteBack(list);
    const int32_t count = (int32_t) list.items.size();
    *ev->count = count;
    if (menu != BATTLE_MENU_MOVES && count > 0) {
        list.initial = std::clamp(list.initial, 0, count - 1);
    }
    *ev->initialPos = list.initial;
    Remembered(menu) = std::move(list);
}

void OnSelect(IEvent* event) {
    OnBattleMenuSelect* ev = (OnBattleMenuSelect*) event;

    if (!ValidMenu(ev->menu)) {
        return;
    }
    const BattleMenuEntry* entry = EntryAt(ev->menu, ev->index);
    if (entry == nullptr) {
        return;
    }
    if (entry->onSelect != nullptr) {
        const BattleMenuEntry copy = *entry;
        const BattleMenuContext ctx = ContextFor(ev->menu);
        copy.onSelect(&ctx, &copy);
    } else if (ev->menu == BATTLE_MENU_STRATEGIES) {
        SPDLOG_ERROR("Mod: battle menu type {} was chosen but has no onSelect", entry->menuType);
    }
}

void OnDrawEntry(IEvent* event) {
    OnBattleMenuDrawEntry* ev = (OnBattleMenuDrawEntry*) event;

    if (!ValidMenu(ev->menu)) {
        return;
    }
    const BattleMenuContext ctx = ContextFor(ev->menu);
    const BattleMenuEntry* entry = EntryAt(ev->menu, ev->index);
    for (const Hud& hud : Huds()) {
        if (hud.menu == ev->menu && hud.hud.drawEntry != nullptr) {
            hud.hud.drawEntry(&ctx, ev->index, entry, ev->x, ev->y, ev->alpha);
        }
    }
}

void OnErrorText(IEvent* event) {
    OnBattleMenuErrorText* ev = (OnBattleMenuErrorText*) event;

    if (!ValidMenu(ev->menu)) {
        return;
    }
    const BattleMenuEntry* entry = EntryAt(ev->menu, ev->index);
    if (entry != nullptr) {
        *ev->msgID = entry->errorMsg;
    }
}

void OnCostStyle(IEvent* event) {
    OnBattleMenuCostStyle* ev = (OnBattleMenuCostStyle*) event;
    const BattleMenuEntry* entry = EntryAt(BATTLE_MENU_MOVES, ev->row);

    if (entry != nullptr) {
        *ev->palette = entry->costPalette;
    }
}

void OnCreated(IEvent* event) {
    OnBattleMenuCreated* ev = (OnBattleMenuCreated*) event;

    if (!ValidMenu(ev->menu)) {
        return;
    }
    const BattleMenuContext ctx = ContextFor(ev->menu);
    for (const Hud& hud : Huds()) {
        if (hud.menu == ev->menu && hud.hud.create != nullptr) {
            hud.hud.create(&ctx);
        }
    }
}

void OnDestroyed(IEvent* event) {
    OnBattleMenuDestroyed* ev = (OnBattleMenuDestroyed*) event;

    if (!ValidMenu(ev->menu)) {
        return;
    }
    const BattleMenuContext ctx = ContextFor(ev->menu);
    for (const Hud& hud : Huds()) {
        if (hud.menu == ev->menu && hud.hud.destroy != nullptr) {
            hud.hud.destroy(&ctx);
        }
    }
    Remembered(ev->menu).reset();
}

void OnOpen(IEvent*) {
    for (int32_t menu = 0; menu < BATTLE_MENU_COUNT; menu++) {
        Remembered(menu).reset();
    }
}

void Listen() {
    static bool sListening = false;
    if (sListening) {
        return;
    }
    sListening = true;
    REGISTER_LISTENER(OnBattleMenuBuilt, EVENT_PRIORITY_NORMAL, OnBuilt);
    REGISTER_LISTENER(OnBattleMenuSelect, EVENT_PRIORITY_NORMAL, OnSelect);
    REGISTER_LISTENER(OnBattleMenuDrawEntry, EVENT_PRIORITY_NORMAL, OnDrawEntry);
    REGISTER_LISTENER(OnBattleMenuErrorText, EVENT_PRIORITY_NORMAL, OnErrorText);
    REGISTER_LISTENER(OnBattleMenuCostStyle, EVENT_PRIORITY_NORMAL, OnCostStyle);
    REGISTER_LISTENER(OnBattleMenuCreated, EVENT_PRIORITY_NORMAL, OnCreated);
    REGISTER_LISTENER(OnBattleMenuDestroyed, EVENT_PRIORITY_NORMAL, OnDestroyed);
    REGISTER_LISTENER(OnBattleMenuOpen, EVENT_PRIORITY_NORMAL, OnOpen);
}

} // namespace

extern "C" int32_t Mod_AddBattleMenuEntries(const char* owner, int32_t menu, BattleMenuProvider provider) {
    const std::string name = Mod::OwnerName(owner);
    if (!ValidMenu(menu) || provider == nullptr) {
        SPDLOG_ERROR("Mod: {} registered an invalid battle menu provider (menu {})", name, menu);
        return -1;
    }
    Listen();
    Providers().push_back({ name, menu, provider });
    return 0;
}

extern "C" int32_t Mod_AddBattleMenuHud(const char* owner, int32_t menu, const BattleMenuHud* hud) {
    const std::string name = Mod::OwnerName(owner);
    if (!ValidMenu(menu) || hud == nullptr) {
        SPDLOG_ERROR("Mod: {} registered an invalid battle menu HUD (menu {})", name, menu);
        return -1;
    }
    Listen();
    Huds().push_back({ name, menu, *hud });
    return 0;
}

extern "C" int32_t Mod_AllocBattleMenuType(const char* owner) {
    const std::string name = Mod::OwnerName(owner);
    auto& owners = TypeOwners();
    if ((int32_t) owners.size() > MOD_BATTLE_MENU_TYPE_LAST - MOD_BATTLE_MENU_TYPE_FIRST) {
        SPDLOG_ERROR(
            "Mod: {} asked for a battle menu type, but all {} are taken", name,
            MOD_BATTLE_MENU_TYPE_LAST - MOD_BATTLE_MENU_TYPE_FIRST + 1
        );
        return -1;
    }
    owners.push_back(name);
    return MOD_BATTLE_MENU_TYPE_FIRST + (int32_t) owners.size() - 1;
}

extern "C" int32_t BattleMenu_Count(const BattleMenuList* list) {
    return (int32_t) list->items.size();
}

extern "C" BattleMenuEntry* BattleMenu_At(BattleMenuList* list, int32_t index) {
    if (index < 0 || index >= (int32_t) list->items.size()) {
        return nullptr;
    }
    return &list->items[index].entry;
}

extern "C" int32_t BattleMenu_FindType(const BattleMenuList* list, int32_t menuType) {
    for (int32_t i = 0; i < (int32_t) list->items.size(); i++) {
        if (list->items[i].entry.menuType == menuType) {
            return i;
        }
    }
    return -1;
}

extern "C" int32_t BattleMenu_FindMove(const BattleMenuList* list, int32_t moveID) {
    for (int32_t i = 0; i < (int32_t) list->items.size(); i++) {
        if (list->items[i].entry.moveID == moveID) {
            return i;
        }
    }
    return -1;
}

extern "C" BattleMenuEntry* BattleMenu_Insert(BattleMenuList* list, int32_t index) {
    if (list->ctx.menu == BATTLE_MENU_MOVES || (int32_t) list->items.size() >= list->capacity) {
        return nullptr;
    }
    index = std::clamp(index, 0, (int32_t) list->items.size());
    list->items.insert(list->items.begin() + index, DefaultItem(list->ctx.menu));
    if (index <= list->initial) {
        list->initial++;
    }
    return &list->items[index].entry;
}

extern "C" void BattleMenu_Remove(BattleMenuList* list, int32_t index) {
    if (index < 0 || index >= (int32_t) list->items.size()) {
        return;
    }
    list->items.erase(list->items.begin() + index);
    if (list->ctx.menu != BATTLE_MENU_MOVES && index < list->initial) {
        list->initial--;
    }
}

extern "C" int32_t BattleMenu_Initial(const BattleMenuList* list) {
    return list->initial;
}

extern "C" void BattleMenu_SetInitial(BattleMenuList* list, int32_t index) {
    list->initial = index;
}

namespace Mod {

void UnregisterBattleMenus(const std::string& owner) {
    auto& providers = Providers();
    providers.erase(
        std::remove_if(
            providers.begin(), providers.end(), [&](const Provider& provider) { return provider.owner == owner; }
        ),
        providers.end()
    );
    auto& huds = Huds();
    huds.erase(
        std::remove_if(huds.begin(), huds.end(), [&](const Hud& hud) { return hud.owner == owner; }), huds.end()
    );
}

} // namespace Mod
