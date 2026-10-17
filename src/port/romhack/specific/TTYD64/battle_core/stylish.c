#include "bc_internal.h"
#include "bc_natives.h"
#include "port/modding/InputHistory.h"

typedef struct TTYD64StylishTracker {
    b8 armed;
    b8 pressed;
    u8 count;
    u16 mask;
} TTYD64StylishTracker;

static TTYD64StylishTracker sStylish;

API_CALLABLE(TTYD64_Function_Multibonk_GetAmountToDeal) {
    s32 amount = (u8) gPlayerData.partners[PARTNER_GOOMBARIO].level == 2 ? 3 : 2;

    evt_set_variable(script, *script->ptrReadPos, amount);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_ExplotionFX) {
    Bytecode* args = script->ptrReadPos;
    s32 x = evt_get_variable(script, *args++);
    s32 y = evt_get_variable(script, *args++);
    s32 z = evt_get_variable(script, *args++);
    s32 strong = (s32) script->varTable[10] > 0;

    fx_smoke_ring(0, x, y, z);
    switch (gBattleStatus.selectedMoveID) {
        case 0x92:
            fx_explosion(strong ? 1 : 0, x, y + 20, z);
            sfx_play_sound(0x2016);
            break;
        case 0x93:
            fx_explosion(strong ? 1 : 0, x, y + 20, z);
            sfx_play_sound(0x2017);
            break;
        case 0x94:
            fx_explosion(strong ? 2 : 1, x, y + 20, z);
            sfx_play_sound(0x2017);
            break;
        default:
            fx_explosion(0, x, y + 20, z);
            sfx_play_sound(0x2016);
            break;
    }
    return ApiStatus_DONE2;
}

static void stylish_reset(void) {
    sStylish = (TTYD64StylishTracker) { 0 };
}

API_CALLABLE(TTYD64_StylishArm) {
    sStylish.mask = BUTTON_A;
    sStylish.armed = true;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_StylishReset) {
    stylish_reset();
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_StylishDisarm) {
    sStylish.armed = false;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_StylishIsArmed) {
    evt_set_variable(script, *script->ptrReadPos, sStylish.armed);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_StylishPressed) {
    evt_set_variable(script, *script->ptrReadPos, sStylish.pressed);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_StylishConsume) {
    sStylish.pressed = false;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_StylishAddCount) {
    s32 count = sStylish.count + 1;

    sStylish.count = count;
    evt_set_variable(script, *script->ptrReadPos, count);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_StylishGetCount) {
    evt_set_variable(script, *script->ptrReadPos, sStylish.count);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_StylishSetCount) {
    sStylish.count = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

static void stylish_on_input_frame(u32 frame, u32 held, u32 pressed) {
    if (sStylish.armed && Mod_InputMatches(pressed, sStylish.mask, MOD_INPUT_MATCH_BYTE_EXACT)) {
        sStylish.pressed = true;
    }
}

static void stylish_on_player_data_clear(IEvent* event) {
    stylish_reset();
}

static void stylish_on_battle_state_changed(IEvent* event) {
    OnBattleStateChanged* ev = (OnBattleStateChanged*) event;

    switch (ev->next) {
        case BATTLE_STATE_END_BATTLE:
        case BATTLE_STATE_END_TRAINING_BATTLE:
        case BATTLE_STATE_END_DEMO_BATTLE:
            sStylish.armed = false;
            break;
    }
}

void TTYD64_InstallBattleCoreStylish(void) {
    stylish_reset();
    Mod_RegisterInputFrameListener("TTYD64", stylish_on_input_frame);
    REGISTER_LISTENER(OnPlayerDataClear, EVENT_PRIORITY_NORMAL, stylish_on_player_data_clear);
    REGISTER_LISTENER(OnBattleStateChanged, EVENT_PRIORITY_NORMAL, stylish_on_battle_state_changed);
}
