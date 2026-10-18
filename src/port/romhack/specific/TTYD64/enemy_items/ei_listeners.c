#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "enemy_items_internal.h"

static void ei_on_actor_created(IEvent* event) {
    OnActorCreated* ev = (OnActorCreated*) event;
    Actor* actor = ev->actor;

    TTYD64_EI_ApplyDifficultyHP(actor);
    TTYD64_EI_RollHeldItem(actor);
    TTYD64_EI_ApplyCreateBadges(actor);
}

static void ei_on_turn_order(IEvent* event) {
    OnTurnOrder* ev = (OnTurnOrder*) event;
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* actor;
    s32 found;
    s32 i;

    if (ev->decision != TURN_ORDER_FIRST_STRIKE) {
        return;
    }
    i = 0;
    actor = battleStatus->enemyActors[0];
    while (true) {
        found = TTYD64_EI_EnemyHasItem(actor, 0xFE);
        if (found) {
            break;
        }
        i++;
        if (i >= ARRAY_COUNT(battleStatus->enemyActors)) {
            break;
        }
        actor = battleStatus->enemyActors[i];
        if (actor == NULL) {
            break;
        }
    }
    if (*ev->value == FIRST_STRIKE_PLAYER && found) {
        *ev->value = FIRST_STRIKE_NONE;
    }
}

static s32 ei_close_call_lucky(Actor* target, s32 closeCallP, s32 prettyLuckyP) {
    if (TTYD64_EI_EnemyHasItem(target, 0x112) || (closeCallP && TTYD64_EI_EnemyHasItem(target, 0x17E))) {
        if (target->curHP < 6) {
            if (rand_int(100) < 33) {
                return HIT_RESULT_MISS;
            }
            return HIT_RESULT_HIT;
        }
    }
    if (TTYD64_EI_EnemyHasItem(target, 0xF1) || (prettyLuckyP && TTYD64_EI_EnemyHasItem(target, 0x17F))) {
        if (rand_int(100) < 10) {
            return HIT_RESULT_MISS;
        }
        return HIT_RESULT_HIT;
    }
    if (TTYD64_EI_EnemyHasItem(target, 0x114)) {
        if (rand_int(100) < 20) {
            return HIT_RESULT_MISS;
        }
    }
    return HIT_RESULT_HIT;
}

static void ei_on_hit_check(IEvent* event) {
    OnHitCheck* ev = (OnHitCheck*) event;
    Actor* target = ev->target;

    if (ev->phase != HIT_CHECK_TEST || target == NULL) {
        return;
    }
    switch (ev->source) {
        case ATTACK_SOURCE_PLAYER:
            if (*ev->hitResult == HIT_RESULT_HIT || *ev->hitResult == HIT_RESULT_HIT_STATIC) {
                if (ei_close_call_lucky(target, true, false) == HIT_RESULT_MISS) {
                    *ev->hitResult = HIT_RESULT_MISS;
                }
            }
            break;
        case ATTACK_SOURCE_PARTNER:
            if (*ev->hitResult == HIT_RESULT_HIT) {
                if (ei_close_call_lucky(target, false, true) == HIT_RESULT_MISS) {
                    *ev->hitResult = HIT_RESULT_MISS;
                }
            }
            break;
        case ATTACK_SOURCE_ITEM:
            if ((u16) target->actorID == ACTOR_PLAYER || (u16) target->actorID == ACTOR_PARTNER) {
                if ((u8) gBattleStatus.outtaSightActive != 0) {
                    *ev->hitResult = HIT_RESULT_MISS;
                }
            }
            break;
    }
}

static void ei_on_attack_begin(IEvent* event) {
    OnAttackBegin* ev = (OnAttackBegin*) event;
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* actor = ev->owner;
    s32 status;
    Evt* script;

    if (ev->api != ATTACK_API_ENEMY_DAMAGE_TARGET) {
        return;
    }

    if (TTYD64_EI_EnemyHasItem(actor, 0xEE)) {
        TTYD64_PierceDefenseFlag[0] = 1;
    }

    status = *ev->status;
    if (status == 0) {
        if (TTYD64_EI_EnemyHasItem(actor, 0xEB)) {
            status = 0x80001250;
        } else {
            if (TTYD64_EI_EnemyHasItem(actor, 0x12F)) {
                script = start_script(&TTYD64_Script_ApplyDebuff_Attack, 1, 0);
                script->owner1.actorID = (u16) battleStatus->activeEnemyActorID;
            }
            if (TTYD64_EI_EnemyHasItem(actor, 0xEF)) {
                status = 0x80040250;
            } else if (TTYD64_EI_EnemyHasItem(actor, 0x17A)) {
                status = 0x80040250;
            } else if (TTYD64_EI_EnemyHasItem(actor, 0x12E)) {
                script = start_script(&TTYD64_Script_ApplyDebuff_Defense, 1, 0);
                script->owner1.actorID = (u16) battleStatus->activeEnemyActorID;
            }
        }
    }
    *ev->status = status;
    *ev->damage = TTYD64_EI_DifficultyScale(*ev->damage) + TTYD64_EI_PiercePlayerTeamDefense(actor);
}

static void ei_enemy_base_damage(OnDamageCalc* ev) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* attacker = ev->attacker;
    Actor* target = ev->target;
    s32 damage = *ev->damage;
    TTYD64BattleRec* rec;

    if (TTYD64_EI_EnemyHasItem(attacker, 0xE2) || TTYD64_EI_EnemyHasItem(attacker, 0x13C)
        || TTYD64_EI_EnemyHasItem(attacker, 0x183))
    {
        damage += 1;
    } else if (TTYD64_EI_EnemyHasItem(attacker, 0xF5) || TTYD64_EI_EnemyHasItem(attacker, 0x18C)
               || TTYD64_EI_EnemyHasItem(attacker, 0x116))
    {
        damage -= 1;
    } else if (TTYD64_EI_EnemyHasItem(attacker, 0x113)) {
        damage += 1;
    } else if (TTYD64_EI_EnemyHasItem(attacker, 0x10D) || TTYD64_EI_EnemyHasItem(attacker, 0x184)) {
        if (attacker->curHP < 6) {
            damage += 2;
        }
    } else if (TTYD64_EI_EnemyHasItem(attacker, 0xF9) || TTYD64_EI_EnemyHasItem(attacker, 0x185)) {
        if (attacker->curHP < 2) {
            damage += 4;
        }
    }

    damage = TTYD64_EnemyCalcDamage_Defense(attacker, damage);
    rec = TTYD64_ActorRec((u16) target->actorID);
    if (rec != NULL) {
        s32 defenseBoost = rec->buffs[TTYD64_BUFF_DEFENSE].amount;
        if (!(battleStatus->curAttackElement & DAMAGE_TYPE_IGNORE_DEFENSE)) {
            damage -= defenseBoost;
        }
    }
    *ev->damage = damage;
}

static s32 ei_defense_badges(Actor* target, s32 boost, s32 withP) {
    if (TTYD64_EI_EnemyHasItem(target, 0xFB)) {
        return boost + 1;
    }
    if (withP && TTYD64_EI_EnemyHasItem(target, 0x181)) {
        return boost + 1;
    }
    if (TTYD64_EI_EnemyHasItem(target, 0x116)) {
        return boost + 1;
    }
    if (withP && TTYD64_EI_EnemyHasItem(target, 0x186)) {
        return boost + 1;
    }
    if (TTYD64_EI_EnemyHasItem(target, 0x113)) {
        return boost - 1;
    }
    if (withP && TTYD64_EI_EnemyHasItem(target, 0x187)) {
        return boost - 1;
    }
    return boost;
}

static void ei_on_damage_calc(IEvent* event) {
    OnDamageCalc* ev = (OnDamageCalc*) event;
    Actor* target = ev->target;
    s32 isPartner = ev->source == ATTACK_SOURCE_PARTNER;

    if (ev->source == ATTACK_SOURCE_ENEMY) {
        if (ev->stage == DAMAGE_STAGE_BASE) {
            ei_enemy_base_damage(ev);
        }
        return;
    }
    if (ev->source != ATTACK_SOURCE_PLAYER && ev->source != ATTACK_SOURCE_PARTNER) {
        return;
    }
    if (ev->stage == DAMAGE_STAGE_FINAL) {
        if (TTYD64_EI_EnemyHasItem(target, 0x111) || (!isPartner && TTYD64_EI_EnemyHasItem(target, 0x182))) {
            if (target->curHP < 6) {
                *ev->damage = *ev->damage / 2;
            }
        }
    }
}

static void ei_on_damage_defense(IEvent* event) {
    OnDamageDefense* ev = (OnDamageDefense*) event;

    if (ev->source != ATTACK_SOURCE_PLAYER && ev->source != ATTACK_SOURCE_PARTNER) {
        return;
    }
    if (!(gBattleStatus.curAttackElement & DAMAGE_TYPE_IGNORE_DEFENSE)) {
        *ev->defense += ei_defense_badges(ev->target, 0, ev->source == ATTACK_SOURCE_PLAYER);
    }
}

static void ei_on_damage_event_dispatch(IEvent* event) {
    OnDamageEventDispatch* ev = (OnDamageEventDispatch*) event;

    if (ev->source != HP_SOURCE_PLAYER_ATTACK && ev->source != HP_SOURCE_PARTNER_ATTACK) {
        return;
    }
    if (gBattleStatus.lastAttackDamage > 0 && TTYD64_EI_EnemyHasItem(ev->target, 0x176)) {
        start_script(
            ev->source == HP_SOURCE_PARTNER_ATTACK ? &TTYD64_Script_Dispatch_ReturnPostage_Partner
                                                   : &TTYD64_Script_Dispatch_ReturnPostage_Mario,
            1, 0
        );
    }
}

static void ei_on_status_chance(IEvent* event) {
    OnStatusChance* ev = (OnStatusChance*) event;
    Actor* target = ev->actor;

    if ((u16) target->actorID < ACTOR_CLASS_ENEMY) {
        return;
    }
    if (TTYD64_EI_EnemyHasItem(target, 0xF2)) {
        *ev->chance = 0;
    } else if (TTYD64_EI_EnemyHasItem(target, 0x189)) {
        *ev->chance = 0;
    }
}

static void ei_on_status_tick(IEvent* event) {
    OnStatusTick* ev = (OnStatusTick*) event;
    Actor* actor = ev->actor;
    s32 heal = 0;
    s32 hp;
    s32 maxHP;
    TTYD64BattleRec* rec;

    if (ev->phase != STATUS_PHASE_ACTION_END || (actor->actorID & ACTOR_CLASS_MASK) != ACTOR_CLASS_ENEMY) {
        return;
    }
    if (TTYD64_EI_EnemyHasItem(actor, 0xFF) || TTYD64_EI_EnemyHasItem(actor, 0x136)
        || TTYD64_EI_EnemyHasItem(actor, 0x18B))
    {
        if (rand_int(100) < 33) {
            heal++;
        }
    } else if (TTYD64_EI_EnemyHasItem(actor, 0xF5)) {
        heal++;
    }
    if (heal != 0) {
        hp = actor->curHP + heal;
        maxHP = actor->maxHP;
        if (hp >= maxHP) {
            hp = maxHP;
        }
        actor->curHP = hp;
        sfx_play_sound(0x213);
        TTYD64_ShowFlyingStat(actor, 0, heal);
    }
    if ((u16) gBattleStatus.lastAttackDamage != 0) {
        rec = TTYD64_ActorRec((u16) actor->actorID);
        if (rec != NULL) {
            rec->charge = 0;
        }
    }
}

static void ei_on_enemy_take_turn_script(IEvent* event) {
    OnEnemyTakeTurnScript* ev = (OnEnemyTakeTurnScript*) event;
    s32 itemID = TTYD64_EI_HeldItem(ev->enemy);

    if (itemID == ITEM_NONE) {
        return;
    }
    if (!(TTYD64_get_item_flags(itemID, 0) & ITEM_TYPE_FLAG_BADGE)) {
        TTYD64_Stack_TakeTurnScript = *ev->takeTurnSource;
        *ev->takeTurnSource = &TTYD64_EnemyUseItem;
        return;
    }
    if (itemID == 0x16D || itemID == 0x17D) {
        TTYD64_Stack_TakeTurnScript = *ev->takeTurnSource;
        *ev->takeTurnSource = &TTYD64_EnemyUseCharge;
    }
}

static void ei_on_star_point_drop_check(IEvent* event) {
    OnStarPointDropCheck* ev = (OnStarPointDropCheck*) event;
    s32 itemID = TTYD64_EI_HeldItem(ev->dropper);

    if (itemID == ITEM_NONE) {
        return;
    }
    if (TTYD64_get_item_flags(itemID, 0) & ITEM_TYPE_FLAG_BADGE) {
        return;
    }
    if (itemID != TTYD64_EI_ITEM_LIFE_SHROOM) {
        return;
    }
    event->Cancelled = true;
}

static void ei_set_item_entity_visible(s32 visible) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* actor;
    ItemEntity* item;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
        actor = battleStatus->enemyActors[i];
        if (actor == NULL || !TTYD64_EI_HasHeldItemData(actor)) {
            continue;
        }
        item = get_item_entity(TTYD64_EI_GetItemEntityIndex(actor));
        if (item == NULL) {
            continue;
        }
        if (visible) {
            item->flags |= 2;
        } else {
            item->flags &= -3;
        }
    }
}

static void ei_on_battle_state_changed(IEvent* event) {
    OnBattleStateChanged* ev = (OnBattleStateChanged*) event;
    s32 newState = TTYD64_RequestedBattleState(ev->next);

    if (ev->prev == BATTLE_STATE_BEGIN_TURN
        && (newState == BATTLE_STATE_BEGIN_PLAYER_TURN || newState == BATTLE_STATE_RUN_AWAY))
    {
        ei_set_item_entity_visible(true);
    } else if (ev->prev == BATTLE_STATE_TRANSFER_TURN && newState == BATTLE_STATE_NEXT_ENEMY) {
        ei_set_item_entity_visible(false);
    }
}

static void ei_on_battle_step(IEvent* event) {
    OnBattleStep* ev = (OnBattleStep*) event;
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* actor;
    ItemEntity* item;
    s32 x;
    s32 y;
    s32 z;
    s32 i;

    if (ev->stage != BATTLE_STEP_BEGIN) {
        return;
    }
    for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
        actor = battleStatus->enemyActors[i];
        if (actor == NULL || !TTYD64_EI_HasHeldItemData(actor)) {
            continue;
        }
        item = get_item_entity(TTYD64_EI_GetItemEntityIndex(actor));
        if (item == NULL) {
            continue;
        }
        x = (s32) actor->curPos.x + (s8) actor->size.x / 2;
        item->pos.x = x;
        y = (s32) actor->curPos.y + 2;
        if (actor->flags & ACTOR_FLAG_UPSIDE_DOWN) {
            y -= (s8) actor->size.y;
        }
        item->pos.y = y;
        z = (s32) actor->curPos.z - 3;
        item->pos.z = z;
    }
}

static void ei_on_actor_deleted(IEvent* event) {
    OnActorDeleted* ev = (OnActorDeleted*) event;
    Actor* actor = ev->actor;

    if (actor->actorID < ACTOR_CLASS_ENEMY) {
        return;
    }
    TTYD64_Function_RemoveBuffs_ActorID(actor->actorID);
    if (TTYD64_EI_HasHeldItemData(actor)) {
        TTYD64_EI_DespawnEnemyItem(actor);
    }
    if ((u8) actor->debuff == STATUS_KEY_FROZEN) {
        sfx_play_sound(0xE7);
        if (actor->icePillarEffect != NULL) {
            actor->icePillarEffect->flags |= 0x10;
        }
    }
}

static void ei_on_damage_attacker_resolve(IEvent* event) {
    OnDamageAttackerResolve* ev = (OnDamageAttackerResolve*) event;

    if (ev->source == ATTACK_SOURCE_ITEM && ev->owner != NULL) {
        *ev->attacker = ev->owner;
    }
}

static void ei_on_actor_hp_change(IEvent* event) {
    OnActorHpChange* ev = (OnActorHpChange*) event;
    Actor* target = ev->actor;
    s32 hp;

    if (ev->source != HP_SOURCE_ITEM) {
        return;
    }
    if ((u16) target->actorID == ACTOR_PLAYER) {
        hp = gPlayerData.curHP + *ev->delta;
        if (hp <= 0) {
            hp = 0;
        }
        gPlayerData.curHP = hp;
        target->curHP = hp;
        event->Cancelled = true;
    } else if ((u16) target->actorID == ACTOR_PARTNER) {
        hp = TTYD64_GetPartnerHP() + *ev->delta;
        if (hp <= 0) {
            hp = 0;
        }
        TTYD64_SetPartnerHP(hp);
        event->Cancelled = true;
    }
}

static void ei_on_actor_defeat_check(IEvent* event) {
    OnActorDefeatCheck* ev = (OnActorDefeatCheck*) event;

    if ((u16) ev->actor->actorID == ACTOR_PLAYER) {
        *ev->defeated = gPlayerData.curHP <= 0;
    }
}

static void ei_on_item_spawn_pick(IEvent* event) {
    OnItemSpawnPick* ev = (OnItemSpawnPick*) event;

    if (ev->source != ITEM_SPAWN_SOURCE_ENEMY_DROP) {
        return;
    }
    TTYD64_EI_SpawnDrops(ev->enemy, ev->itemID);
    event->Cancelled = true;
}

void TTYD64_EI_InstallListeners(void) {
    REGISTER_LISTENER(OnActorCreated, EVENT_PRIORITY_NORMAL, ei_on_actor_created);
    REGISTER_LISTENER(OnTurnOrder, EVENT_PRIORITY_NORMAL, ei_on_turn_order);
    REGISTER_LISTENER(OnHitCheck, EVENT_PRIORITY_NORMAL, ei_on_hit_check);
    REGISTER_LISTENER(OnAttackBegin, EVENT_PRIORITY_NORMAL, ei_on_attack_begin);
    REGISTER_LISTENER(OnDamageCalc, EVENT_PRIORITY_NORMAL, ei_on_damage_calc);
    REGISTER_LISTENER(OnDamageDefense, EVENT_PRIORITY_NORMAL, ei_on_damage_defense);
    REGISTER_LISTENER(OnDamageEventDispatch, EVENT_PRIORITY_NORMAL, ei_on_damage_event_dispatch);
    REGISTER_LISTENER(OnStatusChance, EVENT_PRIORITY_NORMAL, ei_on_status_chance);
    REGISTER_LISTENER(OnStatusTick, EVENT_PRIORITY_NORMAL, ei_on_status_tick);
    REGISTER_LISTENER(OnEnemyTakeTurnScript, EVENT_PRIORITY_NORMAL, ei_on_enemy_take_turn_script);
    REGISTER_LISTENER(OnStarPointDropCheck, EVENT_PRIORITY_NORMAL, ei_on_star_point_drop_check);
    REGISTER_LISTENER(OnBattleStateChanged, EVENT_PRIORITY_NORMAL, ei_on_battle_state_changed);
    REGISTER_LISTENER(OnBattleStep, EVENT_PRIORITY_NORMAL, ei_on_battle_step);
    REGISTER_LISTENER(OnActorDeleted, EVENT_PRIORITY_NORMAL, ei_on_actor_deleted);
    REGISTER_LISTENER(OnDamageAttackerResolve, EVENT_PRIORITY_NORMAL, ei_on_damage_attacker_resolve);
    REGISTER_LISTENER(OnActorHpChange, EVENT_PRIORITY_NORMAL, ei_on_actor_hp_change);
    REGISTER_LISTENER(OnActorDefeatCheck, EVENT_PRIORITY_LOW, ei_on_actor_defeat_check);
    REGISTER_LISTENER(OnItemSpawnPick, EVENT_PRIORITY_NORMAL, ei_on_item_spawn_pick);
}
