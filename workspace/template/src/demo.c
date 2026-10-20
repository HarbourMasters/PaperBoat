#include "mod.h"

#include "common.h"
#include "port/api/cvar.h"
#include "port/api/item.h"
#include "port/api/message.h"
#include "port/api/ui.h"
#include "port/hooks/Events.h"
#include <stdio.h>

#define CVAR_COIN_LOG C_MOD_CVAR("Demo", "CoinLog")

static ListenerID sCoinsListener;

static void LogCoins(IEvent* event) {
    OnCoinsChanged* coins = (OnCoinsChanged*) event;

    if (CVarGetInteger(CVAR_COIN_LOG, 0)) {
        printf("[Demo Mod] Coins: %d -> %d\n", coins->before, coins->after);
    }
}

static void RegisterDemoItem(void) {
    C_ItemDef item = { 0 };
    item.id = "demo.mega_mushroom";
    item.copy_from = ITEM_MUSHROOM;
    item.name_msg = C_RegisterMessage("demo.mega_mushroom.name", "Mega Mushroom");
    item.short_desc_msg = C_RegisterMessage("demo.mega_mushroom.desc", "Restores 25 HP.");
    item.full_desc_msg = item.short_desc_msg;
    item.potency_a = 25;
    item.sell_value = 15;
    C_RegisterItem(&item);
}

static void AddDemoSettings(void) {
    C_WidgetConfig check = { 0 };
    check.type = C_WIDGET_CVAR_CHECKBOX;
    check.cvar = CVAR_COIN_LOG;
    check.opts.checkbox.tooltip = "Prints every change of the coin count to the console.";
    C_AddSidebarEntry("Demo Mod", 1);
    C_AddWidget("Demo Mod", 0, "Log Coins", &check);
}

MOD_INIT() {
    RegisterDemoItem();
    AddDemoSettings();
    sCoinsListener = REGISTER_LISTENER(OnCoinsChanged, EVENT_PRIORITY_NORMAL, LogCoins);
}

MOD_EXIT() {
    // Everything registered above is also removed when the mod unloads; this shows how to stop early.
    UNREGISTER_LISTENER(OnCoinsChanged, sCoinsListener);
}
