#include "common.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/romhack/specific/TTYD64/battle/enemy_items_internal.h"

#define GLITZ_ID                         (sGlitz.id)
#define GLITZ_STATUS                     (sGlitz.status)
#define GLITZ_VAR                        (sGlitz.var)
#define GLITZ_FAILED                     0xFF
#define GLITZ_PARTNER_ACTING(flagsByte1) ((flagsByte1) & 0x10)

typedef struct TTYD64GlitzState {
    u8 id;
    u8 status;
    u8 var;
} TTYD64GlitzState;

static TTYD64GlitzState sGlitz;

API_CALLABLE(TTYD64_GetGlitzChallenge) {
    evt_set_variable(script, *script->ptrReadPos, GLITZ_ID);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetGlitzChallenge) {
    GLITZ_ID = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetGlitzStatus) {
    GLITZ_STATUS = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

static u8 glitz_flags1_byte1(void) {
    return (gBattleStatus.flags1 >> 16) & 0xFF;
}

void TTYD64_Function_GlitzPit_DamageChallenge(void) {
    u32 threshold;
    u32 count;

    if (GLITZ_ID == 9) {
        threshold = 3;
    } else if (GLITZ_ID == 0xA) {
        threshold = 5;
    } else {
        return;
    }
    count = GLITZ_VAR + 1;
    GLITZ_VAR = count;
    if (!(count < threshold)) {
        GLITZ_STATUS = 1;
    }
}

void TTYD64_Function_GlitzPit_DontSwapChallenge(void) {
    if (GLITZ_ID == 0xC) {
        GLITZ_STATUS = GLITZ_FAILED;
    }
}

void TTYD64_Function_GlitzPit_NoFPChallenge(s32 fpCost) {
    if (GLITZ_ID == 0xF && fpCost != 0) {
        GLITZ_STATUS = GLITZ_FAILED;
    }
}

static void glitz_check_challenge_e(void) {
    if (GLITZ_ID == 0xE) {
        if (!(gBattleStatus.damageTaken < 20)) {
            GLITZ_STATUS = GLITZ_FAILED;
        }
    }
}

static void glitz_remove_life_shrooms(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gPlayerData.invItems); i++) {
        if ((u16) gPlayerData.invItems[i] == TTYD64_EI_ITEM_LIFE_SHROOM) {
            gPlayerData.invItems[i] = ITEM_NONE;
        }
    }
}

static void glitz_on_actor_created(IEvent* event) {
    OnActorCreated* ev = (OnActorCreated*) event;

    if (gBattleState != BATTLE_STATE_START || ev->actor != gBattleStatus.enemyActors[0]) {
        return;
    }
    GLITZ_ID = 0xFF;
    GLITZ_STATUS = 0;
    GLITZ_VAR = 0;
    if ((u8) gGameStatus.areaID == 0x1D && (u8) gGameStatus.mapID == 3) {
        start_script(&TTYD64_Script_Init_BattleCondition, 1, 0);
    }
}

static void glitz_on_actor_defeat_check(IEvent* event) {
    OnActorDefeatCheck* ev = (OnActorDefeatCheck*) event;

    if ((u16) ev->actor->actorID != ACTOR_PLAYER) {
        return;
    }
    if ((s8) GLITZ_ID < 0) {
        return;
    }
    if (!btl_are_all_enemies_defeated()) {
        return;
    }
    glitz_check_challenge_e();
    if ((s8) GLITZ_STATUS >= 0) {
        return;
    }
    glitz_remove_life_shrooms();
    gPlayerData.curHP = 0;
    *ev->defeated = true;
}

static void glitz_move_script_load(void);

static void glitz_on_battle_script_load(IEvent* event) {
    OnBattleScriptLoad* ev = (OnBattleScriptLoad*) event;
    s32 id = (s8) GLITZ_ID;
    s32 isFocus;
    u32 count;

    if (id < 0) {
        return;
    }
    if (ev->kind == BATTLE_SCRIPT_LOAD_MOVE) {
        glitz_move_script_load();
        return;
    }
    if (ev->kind == BATTLE_SCRIPT_LOAD_ITEM) {
        if (id == 4) {
            GLITZ_STATUS = GLITZ_FAILED;
        }
        return;
    }
    if (ev->kind != BATTLE_SCRIPT_LOAD_STAR_POWER) {
        return;
    }
    isFocus = ev->id == 0;
    if (id == 0 || id == 1) {
        if (isFocus) {
            return;
        }
        if (id == 0) {
            GLITZ_STATUS = 1;
        } else {
            GLITZ_STATUS = GLITZ_FAILED;
        }
    } else if (id == 5 || id == 6) {
        if (!isFocus) {
            return;
        }
        count = GLITZ_VAR + 1;
        GLITZ_VAR = count;
        if (id != 6) {
            GLITZ_STATUS = 1;
        } else if (!(count < 3)) {
            GLITZ_STATUS = 1;
        }
    }
}

static void glitz_move_script_load(void) {
    s32 id = (s8) GLITZ_ID;
    u8 submenu;

    if (id != 2 && id != 3) {
        return;
    }
    submenu = gBattleStatus.curSubmenu;
    if (GLITZ_PARTNER_ACTING(glitz_flags1_byte1())) {
        return;
    }
    if (id == 3) {
        if (submenu == 1) {
            GLITZ_STATUS = GLITZ_FAILED;
        }
    } else if (submenu == 0) {
        GLITZ_STATUS = GLITZ_FAILED;
    }
}

static void glitz_wait_turns_check(void) {
    if (GLITZ_VAR < 4) {
        GLITZ_STATUS = GLITZ_FAILED;
    }
}

static void glitz_on_attack_begin(IEvent* event) {
    OnAttackBegin* ev = (OnAttackBegin*) event;
    s32 id = (s8) GLITZ_ID;
    u8 flagsByte1;

    if (id < 0) {
        return;
    }
    switch (ev->api) {
        case ATTACK_API_PARTNER_DAMAGE_ENEMY:
            if (id == 7) {
                GLITZ_STATUS = GLITZ_FAILED;
            } else if (id == 0xB) {
                glitz_wait_turns_check();
            }
            break;
        case ATTACK_API_PLAYER_DAMAGE_ENEMY:
            if (id == 8) {
                GLITZ_STATUS = GLITZ_FAILED;
            } else if (id == 0xB) {
                glitz_wait_turns_check();
            }
            break;
        case ATTACK_API_ITEM_DAMAGE_ENEMY:
            flagsByte1 = glitz_flags1_byte1();
            if (id == 7) {
                if (GLITZ_PARTNER_ACTING(flagsByte1)) {
                    GLITZ_STATUS = GLITZ_FAILED;
                }
            } else if (id == 8) {
                if (!GLITZ_PARTNER_ACTING(flagsByte1)) {
                    GLITZ_STATUS = GLITZ_FAILED;
                }
            } else if (id == 0xB) {
                glitz_wait_turns_check();
            }
            break;
    }
}

static void glitz_on_status_tick(IEvent* event) {
    OnStatusTick* ev = (OnStatusTick*) event;
    u32 count;

    if (ev->phase != STATUS_PHASE_PLAYER_TURN_DAMAGE || ev->actor->actorID != ACTOR_PLAYER) {
        return;
    }
    if (TTYD64_bc_PlayerTurnRestarting()) {
        return;
    }
    if (GLITZ_ID == 0xB) {
        GLITZ_VAR = GLITZ_VAR + 1;
    } else if (GLITZ_ID == 0xD) {
        count = GLITZ_VAR + 1;
        GLITZ_VAR = count;
        if (!(count < 6)) {
            GLITZ_STATUS = GLITZ_FAILED;
        }
    }
}

static void glitz_on_damage_event_dispatch(IEvent* event) {
    OnDamageEventDispatch* ev = (OnDamageEventDispatch*) event;

    if (ev->source != HP_SOURCE_ENEMY_ATTACK || gBattleStatus.lastAttackDamage <= 0) {
        return;
    }
    if ((ev->target->actorID & ACTOR_CLASS_MASK) != ACTOR_CLASS_PLAYER) {
        gBattleStatus.damageTaken += gBattleStatus.lastAttackDamage;
    }
}

void TTYD64_EI_InstallGlitzPit(void) {
    REGISTER_LISTENER(OnActorCreated, EVENT_PRIORITY_HIGH, glitz_on_actor_created);
    REGISTER_LISTENER(OnActorDefeatCheck, EVENT_PRIORITY_LOW, glitz_on_actor_defeat_check);
    REGISTER_LISTENER(OnBattleScriptLoad, EVENT_PRIORITY_NORMAL, glitz_on_battle_script_load);
    REGISTER_LISTENER(OnAttackBegin, EVENT_PRIORITY_NORMAL, glitz_on_attack_begin);
    REGISTER_LISTENER(OnStatusTick, EVENT_PRIORITY_NORMAL, glitz_on_status_tick);
    REGISTER_LISTENER(OnDamageEventDispatch, EVENT_PRIORITY_NORMAL, glitz_on_damage_event_dispatch);
}
