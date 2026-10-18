#include "common.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/modding/Popups.h"
#include "badges_internal.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_symbols.h"
#include "../include/ttyd64_rawmem.h"
#include "inventory.h"

s32 TTYD64_bs_HID_FPDrain;

static s32 sFPDrainAmount;
static s32 sHappyFPRecovery;
static s32 sPartnerGuardBase;
static s32 sDefendThreadID;
static b32 sPartnerHappyActive;

API_CALLABLE(TTYD64_SetDefendThread) {
    sDefendThreadID = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetPartnerHappyActive) {
    sPartnerHappyActive = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetPartnerHappyActive) {
    evt_set_variable(script, *script->ptrReadPos, sPartnerHappyActive);
    return ApiStatus_DONE2;
}

static void bs_on_ability_effect(IEvent* event) {
    OnAbilityEffect* ev = (OnAbilityEffect*) event;
    Actor* player = gBattleStatus.playerActor;
    s32 count;

    switch (ev->ability) {
        case ABILITY_FIRE_SHIELD:
        case ABILITY_PRETTY_LUCKY:
        case ABILITY_CLOSE_CALL:
        case ABILITY_LUCKY_DAY:
        case ABILITY_P_UP_D_DOWN:
        case ABILITY_P_DOWN_D_UP:
            *ev->value = player_team_is_ability_active(player, ev->ability);
            break;
        case ABILITY_LAST_STAND:
            *ev->value = 2 + (TTYD64_IsBadgeActivated_Stack(0x111) - 1);
            break;
        case ABILITY_POWER_RUSH:
            *ev->value = TTYD64_IsBadgeActivated_Stack(0x10D) * 2;
            break;
        case ABILITY_MEGA_RUSH:
            *ev->value = TTYD64_IsBadgeActivated_Stack(0xF9) * 4;
            break;
        case ABILITY_HP_DRAIN:
            *ev->value += TTYD64_IsBadgeActivated_Stack(0xF5) - 1;
            break;
        case ABILITY_HEART_FINDER:
        case ABILITY_FLOWER_FINDER:
            count = is_ability_active(ev->ability);
            *ev->value = (count - 1) * 2 + 2;
            break;
        case ABILITY_PAY_OFF:
            count = is_ability_active(ABILITY_PAY_OFF);
            *ev->value = (u8) gCurrentEncounter.damageTaken * (count * 2);
            break;
        case ABILITY_MONEY_MONEY:
            count = is_ability_active(ABILITY_MONEY_MONEY);
            *ev->value = count * 2;
            break;
        case ABILITY_DIZZY_ATTACK:
            *ev->value = (TTYD64_IsBadgeActivated_Stack(0x11D) - 1) + 2;
            break;
    }
}

static void bs_on_partner_luck_hit_check(IEvent* event) {
    OnHitCheck* ev = (OnHitCheck*) event;
    s32 hit = *ev->hitResult;
    s32 result;

    if (ev->source != ATTACK_SOURCE_ENEMY || ev->phase != HIT_CHECK_TEST || ev->target == nullptr) {
        return;
    }
    if ((gBattleStatus.curTargetID & ACTOR_CLASS_MASK) != ACTOR_CLASS_PARTNER
        || (gBattleStatus.curAttackElement & DAMAGE_TYPE_TRIGGER_LUCKY))
    {
        return;
    }
    if (hit != HIT_RESULT_HIT && hit != HIT_RESULT_HIT_STATIC && hit != HIT_RESULT_IMMUNE) {
        return;
    }
    result = TTYD64_bs_PartnerTestLuck();
    if (result >= 0) {
        *ev->hitResult = result;
    }
}

static void bs_on_damage_calc(IEvent* event) {
    OnDamageCalc* ev = (OnDamageCalc*) event;
    BattleStatus* battleStatus = &gBattleStatus;

    switch (ev->source) {
        case ATTACK_SOURCE_PLAYER:
            switch (ev->stage) {
                case DAMAGE_STAGE_AFTER_BOOSTS:
                    *ev->damage += TTYD64_bs_PowerBadgesBonus((u16) battleStatus->selectedMoveID);
                    *ev->damage += TTYD64_bs_PlayerChargeBoost(battleStatus->turboChargeTurnsLeft);
                    break;
            }
            break;
        case ATTACK_SOURCE_PARTNER:
            if (ev->stage == DAMAGE_STAGE_BASE) {
                *ev->damage = TTYD64_bs_PartnerAttackDamage(*ev->damage) - ev->attacker->attackBoost;
            }
            break;
        case ATTACK_SOURCE_ENEMY:
            if ((ev->target->actorID & ACTOR_CLASS_MASK) != ACTOR_CLASS_PARTNER) {
                break;
            }
            if (ev->stage == DAMAGE_STAGE_AFTER_BADGES) {
                *ev->damage = TTYD64_bs_PartnerDefenseBadges(*ev->damage);
                sPartnerGuardBase = *ev->damage;
            } else if (ev->stage == DAMAGE_STAGE_GUARD && (battleStatus->flags1 & BS_FLAGS1_ATK_BLOCKED)
                       && !TTYD64_Guard.superguarded)
            {
                *ev->damage = sPartnerGuardBase - TTYD64_IsBadgeActivated_Stack(0x180) - 1;
            }
            break;
    }
}

static void bs_on_damage_defense(IEvent* event) {
    OnDamageDefense* ev = (OnDamageDefense*) event;
    ActorPart* part;
    s32 count;

    if (ev->source != ATTACK_SOURCE_PLAYER || !(gBattleStatus.curAttackElement & DAMAGE_TYPE_ICE)) {
        return;
    }
    part = get_actor_part(ev->target, gBattleStatus.curTargetPart);
    if (get_defense(ev->target, part->defenseTable, gBattleStatus.curAttackElement) >= 0) {
        return;
    }
    count = TTYD64_IsBadgeActivated_Stack(0xFA);
    if (count != 0) {
        *ev->defense -= count - 1;
    }
}

static void bs_on_turn_end_recovery(IEvent* event) {
    OnTurnEndRecovery* ev = (OnTurnEndRecovery*) event;

    sFPDrainAmount = TTYD64_bs_FPDrainRecovery();
    sHappyFPRecovery = *ev->fp;
    *ev->fp += sFPDrainAmount;
}

API_CALLABLE(TTYD64_bs_SplitHappyFP) {
    script->varTable[13] = sFPDrainAmount;
    script->varTable[12] = sHappyFPRecovery > 99 ? 99 : sHappyFPRecovery;
    sFPDrainAmount = 0;
    return ApiStatus_DONE2;
}

static void bs_on_player_speed_update(IEvent* event) {
    OnPlayerSpeedUpdate* ev = (OnPlayerSpeedUpdate*) event;
    PlayerStatus* playerStatus = &gPlayerStatus;
    s32 count;
    f32 speed = 2.0f;

    if (playerStatus->actionState != ACTION_STATE_WALK || (playerStatus->flags & PS_FLAG_CUTSCENE_MOVEMENT)
        || (playerStatus->animFlags & PA_FLAG_USING_PEACH_PHYSICS))
    {
        return;
    }
    count = is_ability_active(ABILITY_SLOW_GO);
    if (count != 0) {
        speed = 2.0f - 1.0f * (f32) (count - 1);
        if (speed < 0.0f) {
            speed = 0.0f;
        }
    }
    *ev->walkSpeed = speed;
    playerStatus->curSpeed = speed;
}

static void bs_on_player_spin_start(IEvent* event) {
    OnPlayerSpinStart* ev = (OnPlayerSpinStart*) event;
    s32 count = is_ability_active(ABILITY_SPEEDY_SPIN);

    if (count != 0) {
        *ev->spinSpeedScale = 2.7f + (f32) (count - 1) * 1.0f;
    }
}

static void bs_on_damage_event_dispatch(IEvent* event) {
    OnDamageEventDispatch* ev = (OnDamageEventDispatch*) event;
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* attacker;

    if (ev->source != HP_SOURCE_ENEMY_ATTACK || battleStatus->lastAttackDamage <= 0) {
        return;
    }
    attacker = get_actor(battleStatus->attackerActorID);
    TTYD64_bs_ReturnPostage(attacker);
    if (!(ev->target->flags & ACTOR_FLAG_NO_DMG_POPUP)
        && !(battleStatus->curAttackElement & (DAMAGE_TYPE_MULTIPLE_POPUPS | DAMAGE_TYPE_SMASH))
        && (u16) attacker->targetActorID == 0)
    {
        s32 hits = TTYD64_bs_PityFlowerRolls();

        if (hits != 0) {
            TTYD64_ShowFlyingStat(battleStatus->playerActor, 1, hits);
            sfx_play_sound(0x2055);
            recover_fp(hits);
        }
    }
}

static void bs_on_damage_popup_kind(IEvent* event) {
    OnDamagePopupKind* ev = (OnDamagePopupKind*) event;

    *ev->kind = DAMAGE_POPUP_NEXT;
}

static void bs_on_tried_to_hit_check(IEvent* event) {
    OnHitCheck* ev = (OnHitCheck*) event;

    if (ev->phase != HIT_CHECK_TEST) {
        return;
    }
    if (ev->source == ATTACK_SOURCE_PARTNER) {
        TTYD64_DoesActorTriedToHitTarget_Partner[0] = 1;
    } else if (ev->source == ATTACK_SOURCE_PLAYER) {
        TTYD64_DoesActorTriedToHitTarget_Player[0] = 1;
    }
}

static void bs_on_battle_menus_enabled(IEvent* event) {
    OnBattleMenusEnabled* ev = (OnBattleMenusEnabled*) event;

    *ev->enabledMenus = TTYD64_bs_EnabledMenus(*ev->enabledMenus);
}

static void bs_on_status_tick(IEvent* event) {
    OnStatusTick* ev = (OnStatusTick*) event;
    u8 tried;

    switch (ev->phase) {
        case STATUS_PHASE_ACTION_END:
            if (ev->actor->actorID == ACTOR_PLAYER) {
                tried = TTYD64_DoesActorTriedToHitTarget_Player[0];
                TTYD64_DoesActorTriedToHitTarget_Player[0] = 0;
                if (tried != 0) {
                    TTYD64_ActorRec(ACTOR_PLAYER)->charge = 0;
                }
            } else if (ev->actor->actorID == ACTOR_PARTNER) {
                tried = TTYD64_DoesActorTriedToHitTarget_Partner[0];
                TTYD64_DoesActorTriedToHitTarget_Partner[0] = 0;
                if (tried != 0) {
                    TTYD64BattleRec* rec = TTYD64_CurPartnerRec();

                    if (rec != nullptr) {
                        rec->charge = 0;
                    }
                }
            }
            break;
        case STATUS_PHASE_PARTNER_TURN_END:
            if (TTYD64_bs_PartnerTurnEnd()) {
                event->Cancelled = true;
            }
            break;
    }
}

static void bs_on_player_actor_loaded(IEvent* event) {
    OnPlayerActorLoaded* ev = (OnPlayerActorLoaded*) event;

    TTYD64_bs_LuckyStart(ev->player);
}

static s32 bs_player_flower_discount(void) {
    Actor* player = gBattleStatus.playerActor;

    return player_team_is_ability_active(player, ABILITY_FLOWER_SAVER)
        + player_team_is_ability_active(player, ABILITY_FLOWER_FANATIC) * 2;
}

static s32 bs_clamped_cost(s32 base, s32 discount) {
    if (base == 0) {
        return 0;
    }
    base -= discount;
    return base < 1 ? 1 : base;
}

static s32 bs_move_fp_enable(Actor* user, s32 moveID, s32 row) {
    BattleStatus* battleStatus = &gBattleStatus;
    s32 base = gMoveTable[moveID].costFP;

    if ((user->actorID & ACTOR_CLASS_MASK) == ACTOR_CLASS_PARTNER) {
        return bs_clamped_cost(base, TTYD64_IsBadgeActivated_Stack(0x18A));
    }
    if (gMoveTable[moveID].category == MOVE_TYPE_ITEMS) {
        return TTYD64_bs_DipCost(base);
    }
    base *= TTYD64_IsBadgeActivated_Stack((u16) battleStatus->submenuIcons[row]);
    return bs_clamped_cost(base, bs_player_flower_discount());
}

static s32 bs_move_fp_deduct(s32 moveID, s32 row) {
    BattleStatus* battleStatus = &gBattleStatus;
    s32 base = gMoveTable[moveID].costFP;

    if (gBattleState != BATTLE_STATE_PARTNER_MOVE && (u8) battleStatus->curSubmenu != 2) {
        u32 slot = (u8) row;

        if (slot < ARRAY_COUNT(battleStatus->submenuIcons)) {
            base *= TTYD64_IsBadgeActivated_Stack((u16) battleStatus->submenuIcons[slot]);
        }
    }
    TTYD64_Function_GlitzPit_NoFPChallenge(base);
    if (gBattleState == BATTLE_STATE_PARTNER_MOVE) {
        return bs_clamped_cost(base, TTYD64_IsBadgeActivated_Stack(0x18A));
    }
    return bs_clamped_cost(base, bs_player_flower_discount());
}

static void bs_on_move_fp_cost(IEvent* event) {
    OnMoveFPCost* ev = (OnMoveFPCost*) event;

    if (ev->use == MOVE_FP_DEDUCT) {
        *ev->cost = bs_move_fp_deduct(ev->moveID, ev->row);
    } else {
        *ev->cost = bs_move_fp_enable(ev->user, ev->moveID, ev->row);
    }
}

static void bs_on_move_cost_display(IEvent* event) {
    OnMoveCostDisplay* ev = (OnMoveCostDisplay*) event;
    BattleStatus* battleStatus = &gBattleStatus;

    if ((ev->user->actorID & ACTOR_CLASS_MASK) == ACTOR_CLASS_PARTNER) {
        *ev->discount = TTYD64_IsBadgeActivated_Stack(0x18A);
        *ev->discountColor = *ev->discount != 0 ? 1 : 0;
    } else if ((u8) battleStatus->curSubmenu != BTL_MENU_TYPE_ITEMS) {
        *ev->cost *= TTYD64_IsBadgeActivated_Stack((u16) battleStatus->submenuIcons[ev->row]);
    }
}

static void bs_on_battle_defend_begin(IEvent* event) {
    OnBattleDefendBegin* ev = (OnBattleDefendBegin*) event;

    ev->script->owner1.actorID = (gBattleStatus.flags1 & BS_FLAGS1_PLAYER_IN_BACK) ? ACTOR_PARTNER : ACTOR_PLAYER;
}

static void bs_on_battle_defend_end(IEvent* event) {
    event->Cancelled = true;
    if (!does_script_exist(sDefendThreadID)) {
        btl_set_state(
            (gBattleStatus.flags1 & BS_FLAGS1_PLAYER_IN_BACK) ? BATTLE_STATE_END_PARTNER_TURN
                                                              : BATTLE_STATE_END_PLAYER_TURN
        );
    }
}

static void bs_on_turn_end_labels(IEvent* event) {
    OnTurnEndLabels* ev = (OnTurnEndLabels*) event;
    Evt* script = ev->script;

    if (ev->stage == TURN_END_LABELS_CREATE) {
        Bytecode* args = script->ptrReadPos;
        s32 x = evt_get_variable(script, args[0]);
        s32 y = evt_get_variable(script, args[1]);
        s32 z = evt_get_variable(script, args[2]);
        s32 screenX;
        s32 screenY;
        s32 screenZ;

        if (script->varTable[13] <= 0) {
            return;
        }
        get_screen_coords(gCurrentCameraID, x, y, z, &screenX, &screenY, &screenZ);
        screenX += 30;
        screenY -= 19;
        if (script->varTable[10] > 0) {
            screenY += 9;
        }
        if (script->varTable[11] > 0 || script->varTable[12] > 0) {
            screenY += 9;
        }
        TTYD64_bs_HID_FPDrain = hud_element_create(&TTYD64_IconScript_FPDrain);
        hud_element_set_render_pos(TTYD64_bs_HID_FPDrain, screenX, screenY);
    } else if (ev->stage == TURN_END_LABELS_REMOVE) {
        if (script->varTable[13] > 0) {
            hud_element_free(TTYD64_bs_HID_FPDrain);
        }
    }
}

void TTYD64_InstallBadgesBattle(void) {
    REGISTER_LISTENER(OnAbilityEffect, EVENT_PRIORITY_NORMAL, bs_on_ability_effect);
    REGISTER_LISTENER(OnHitCheck, EVENT_PRIORITY_LOW, bs_on_partner_luck_hit_check);
    REGISTER_LISTENER(OnDamageCalc, EVENT_PRIORITY_NORMAL, bs_on_damage_calc);
    REGISTER_LISTENER(OnTurnEndRecovery, EVENT_PRIORITY_NORMAL, bs_on_turn_end_recovery);
    REGISTER_LISTENER(OnPlayerSpeedUpdate, EVENT_PRIORITY_HIGH, bs_on_player_speed_update);
    REGISTER_LISTENER(OnPlayerSpinStart, EVENT_PRIORITY_NORMAL, bs_on_player_spin_start);
    REGISTER_LISTENER(OnDamageDefense, EVENT_PRIORITY_NORMAL, bs_on_damage_defense);
    REGISTER_LISTENER(OnDamageEventDispatch, EVENT_PRIORITY_NORMAL, bs_on_damage_event_dispatch);
    REGISTER_LISTENER(OnDamagePopupKind, EVENT_PRIORITY_NORMAL, bs_on_damage_popup_kind);
    REGISTER_LISTENER(OnHitCheck, EVENT_PRIORITY_NORMAL, bs_on_tried_to_hit_check);
    REGISTER_LISTENER(OnBattleMenusEnabled, EVENT_PRIORITY_NORMAL, bs_on_battle_menus_enabled);
    REGISTER_LISTENER(OnStatusTick, EVENT_PRIORITY_NORMAL, bs_on_status_tick);
    REGISTER_LISTENER(OnPlayerActorLoaded, EVENT_PRIORITY_NORMAL, bs_on_player_actor_loaded);
    REGISTER_LISTENER(OnMoveFPCost, EVENT_PRIORITY_NORMAL, bs_on_move_fp_cost);
    REGISTER_LISTENER(OnMoveCostDisplay, EVENT_PRIORITY_NORMAL, bs_on_move_cost_display);
    REGISTER_LISTENER(OnBattleDefendBegin, EVENT_PRIORITY_NORMAL, bs_on_battle_defend_begin);
    REGISTER_LISTENER(OnBattleDefendEnd, EVENT_PRIORITY_NORMAL, bs_on_battle_defend_end);
    REGISTER_LISTENER(OnTurnEndLabels, EVENT_PRIORITY_NORMAL, bs_on_turn_end_labels);
    Mod_RegisterBattlePopupAt("TTYD64", BTL_MSG_47, 0x1D01AC, BTL_MSG_47);
}
