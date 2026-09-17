#include "common.h"
#include "world/partners.h"
#include "port/ui/cvar_prefixes.h"

API_CALLABLE(DisableLoadingZoneInput) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    if (!CVarGetInteger(CVAR_ENHANCEMENT("PreventLoadingZoneStorage"), 0)) {
        return ApiStatus_DONE2;
    }

    disable_player_input();
    partner_disable_input();
    close_status_bar();
    disable_status_bar_input();
    if (playerStatus->actionState == ACTION_STATE_SPIN) {
        playerStatus->animFlags |= PA_FLAG_INTERRUPT_SPIN;
    }
    gOverrideFlags |= GLOBAL_OVERRIDES_40;

    return ApiStatus_DONE2;
}
