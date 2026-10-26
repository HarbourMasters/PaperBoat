#include "common.h"
#include "hud_element.h"
#include "sprite.h"
#include "pause/pause_common.h"
#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/romhack/specific/TTYD64/badges_internal.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"

extern intptr_t gPauseMessages[];

static PauseBadgesView sBadgesView;

f32 TTYD64_bs_PauseBadgeIconScale(void) {
    union {
        u32 bits;
        f32 value;
    } scale;

    scale.bits = 0x3F19BA99;
    return scale.value;
}

s32 TTYD64_bs_PauseDrawEquipped(s32 listIndex, s32 tab, const s16* list, s32 equipped) {
    s32 decision = TTYD64_bs_DrawItemDecisionPos((u16) list[listIndex], listIndex, tab, list);

    return decision >= 0 ? decision : equipped;
}

static void bs_on_pause_badges_view(IEvent* event) {
    sBadgesView = *((OnPauseBadgesView*) event)->view;
}

static void bs_on_pause_badge_list(IEvent* event) {
    OnPauseBadgeList* ev = (OnPauseBadgeList*) event;

    switch (ev->reason) {
        case PAUSE_BADGE_LIST_OPEN:
            TTYD64_bs_PauseInitHook();
            break;
        case PAUSE_BADGE_LIST_REBUILD:
            TTYD64_bs_PauseLoadHook();
            break;
        case PAUSE_BADGE_LIST_TAB_SWITCHED:
            TTYD64_bs_PauseTabSwitchHook(
                ev->list->ids, ev->list->capacity < 128 ? ev->list->capacity : 128, ev->list->tab
            );
            break;
    }
}

static void bs_on_pause_badge_equipped(IEvent* event) {
    OnPauseBadgeEquipped* ev = (OnPauseBadgeEquipped*) event;

    if (sBadgesView.itemIds == nullptr) {
        return;
    }
    *ev->equipped =
        TTYD64_bs_TryEquipDecision((s16) ev->badgeID, ev->listIndex, *sBadgesView.currentTab, sBadgesView.itemIds);
}

static void bs_on_max_stats_recalculated(IEvent* event) {
    TTYD64_bs_HPPlusP();
}

static void bs_on_shop_purchase_item(IEvent* event) {
    OnShopPurchaseItem* ev = (OnShopPurchaseItem*) event;

    if (ev->badgeSlot < 0) {
        *ev->refusalMsg = TTYD64_SHOP_MSG_TOO_MANY_BADGES;
        event->Cancelled = true;
    }
}

static void bs_on_remove_badge(IEvent* event) {
    OnRemoveBadge* ev = (OnRemoveBadge*) event;

    *ev->slot = TTYD64_bs_RemoveBadge(ev->badgeID);
    event->Cancelled = true;
}

static void bs_on_sprite_component_palette(IEvent* event) {
    OnSpriteComponentPalette* ev = (OnSpriteComponentPalette*) event;

    *ev->palette = TTYD64_bs_SkinPalette(ev->compList, ev->compIndex, *ev->palette);
}

static void bs_on_player_raster_palette(IEvent* event) {
    OnPlayerRasterPalette* ev = (OnPlayerRasterPalette*) event;

    *ev->palette = TTYD64_bs_RasterSkinPalette(ev->playerSpriteID, *ev->palette);
}

void TTYD64_InstallBadgesWorld(void) {
    gPauseMessages[PAUSE_MSG_DONT_WEAR_MORE] = (intptr_t) TTYD64_String_TooManyBadges;
    REGISTER_LISTENER(OnPauseBadgesView, EVENT_PRIORITY_NORMAL, bs_on_pause_badges_view);
    REGISTER_LISTENER(OnPauseBadgeList, EVENT_PRIORITY_NORMAL, bs_on_pause_badge_list);
    REGISTER_LISTENER(OnPauseBadgeEquipped, EVENT_PRIORITY_NORMAL, bs_on_pause_badge_equipped);
    REGISTER_LISTENER(OnMaxStatsRecalculated, EVENT_PRIORITY_NORMAL, bs_on_max_stats_recalculated);
    REGISTER_LISTENER(OnShopPurchaseItem, EVENT_PRIORITY_NORMAL, bs_on_shop_purchase_item);
    REGISTER_LISTENER(OnRemoveBadge, EVENT_PRIORITY_NORMAL, bs_on_remove_badge);
    REGISTER_LISTENER(OnSpriteComponentPalette, EVENT_PRIORITY_NORMAL, bs_on_sprite_component_palette);
    REGISTER_LISTENER(OnPlayerRasterPalette, EVENT_PRIORITY_NORMAL, bs_on_player_raster_palette);
}
