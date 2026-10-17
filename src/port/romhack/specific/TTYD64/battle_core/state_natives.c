#include "bc_internal.h"
#include "battle/action_cmd.h"

API_CALLABLE(TTYD64_TestBattleFlags2) {
    Bytecode* args = script->ptrReadPos;
    s32 mask = evt_get_variable(script, *args++);

    evt_set_variable(script, *args++, (gBattleStatus.flags2 & mask) != 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetCurrentBattleID) {
    evt_set_variable(script, *script->ptrReadPos, gCurrentBattleID & 0xFFFF);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetActionMeterFill) {
    evt_set_variable(script, *script->ptrReadPos, gActionCommandStatus.meterFillLevel);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetLastAttackDamage) {
    evt_set_variable(script, *script->ptrReadPos, gBattleStatus.lastAttackDamage);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetActorHP) {
    Bytecode* args = script->ptrReadPos;
    Actor* actor = (Actor*) evt_get_variable(script, *args++);
    s32 curHP = evt_get_variable(script, *args++);
    s32 maxHP = evt_get_variable(script, *args++);

    if (actor != NULL) {
        actor->curHP = curHP;
        actor->maxHP = maxHP;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_UpdateKOStatus) {
    btl_update_ko_status();
    return ApiStatus_DONE2;
}
