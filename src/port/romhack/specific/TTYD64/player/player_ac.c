#include "common.h"
#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/romhack/specific/TTYD64/player/player_internal.h"

API_CALLABLE(action_command_air_lift_init);
API_CALLABLE(action_command_air_raid_init);
API_CALLABLE(action_command_body_slam_init);
API_CALLABLE(action_command_bomb_init);
API_CALLABLE(action_command_break_free_init);
API_CALLABLE(action_command_dizzy_shell_init);
API_CALLABLE(action_command_fire_shell_init);
API_CALLABLE(action_command_flee_init);
API_CALLABLE(action_command_hammer_init);
API_CALLABLE(action_command_hurricane_init);
API_CALLABLE(action_command_jump_init);
API_CALLABLE(action_command_jump_start);
API_CALLABLE(action_command_mega_shock_init);
API_CALLABLE(action_command_power_shock_init);
API_CALLABLE(action_command_smack_init);
API_CALLABLE(action_command_spiny_surge_init);
API_CALLABLE(action_command_spook_init);
API_CALLABLE(action_command_squirt_init);
API_CALLABLE(action_command_stop_leech_init);
API_CALLABLE(action_command_three_chances_init);
API_CALLABLE(action_command_tidal_wave_init);
API_CALLABLE(action_command_unused_flee_init);
API_CALLABLE(action_command_unused_mash_a_init);
API_CALLABLE(action_command_whirlwind_init);

static s32 sLoadedActionCommand = -1;

static ApiFunc sActionCommand_802A9000[] = {
    NULL,
    action_command_jump_init,
    action_command_hammer_init,
    action_command_flee_init,
    action_command_break_free_init,
    action_command_whirlwind_init,
    action_command_stop_leech_init,
    action_command_unused_flee_init,
    action_command_dizzy_shell_init,
    action_command_fire_shell_init,
    action_command_unused_mash_a_init,
    action_command_bomb_init,
    action_command_body_slam_init,
    action_command_air_lift_init,
    action_command_air_raid_init,
    action_command_squirt_init,
    action_command_power_shock_init,
    action_command_mega_shock_init,
    action_command_smack_init,
    action_command_spiny_surge_init,
    action_command_hurricane_init,
    action_command_spook_init,
    action_command_three_chances_init,
    action_command_tidal_wave_init,
};

static ApiFunc sActionCommand_802A9120[] = {
    NULL, action_command_jump_start,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
};

static ApiStatus call_loaded(ApiFunc* table, Evt* script, b32 isInitialCall) {
    if (sLoadedActionCommand < 0 || sLoadedActionCommand >= 24 || table[sLoadedActionCommand] == NULL) {
        GameEngine_LogWarn("TTYD64: no action command routine for loaded command %d", sLoadedActionCommand);
        return ApiStatus_DONE2;
    }
    return table[sLoadedActionCommand](script, isInitialCall);
}

API_CALLABLE(TTYD64_Player_AC_802A9000) {
    return call_loaded(sActionCommand_802A9000, script, isInitialCall);
}

API_CALLABLE(TTYD64_Player_AC_802A9120) {
    return call_loaded(sActionCommand_802A9120, script, isInitialCall);
}

static void on_action_command_load(IEvent* event) {
    sLoadedActionCommand = ((OnActionCommandLoad*) event)->actionCommandID;
}

void TTYD64_Player_InstallActionCommands(void) {
    REGISTER_LISTENER(OnActionCommandLoad, EVENT_PRIORITY_NORMAL, on_action_command_load);
}
