#include "bc_internal.h"
#include <math.h>

s32 TTYD64_Data_ActorsWithHPFPBuffs;

extern EvtScript TTYD64_Script_MakeEffect;

static s32 counter_actor_id(s32 index) {
    switch (index) {
        case 0:
            return ACTOR_PLAYER;
        case 1:
            return ACTOR_PARTNER;
        default:
            return ACTOR_ENEMY0 + index - 2;
    }
}

static void update_counters(void) {
    s32 index;
    s32 buff;

    for (index = 0; index < TTYD64_BC_NUM_ACTOR_SLOTS; index++) {
        s32 actorID = counter_actor_id(index);
        TTYD64BattleRec* rec = TTYD64_ActorRec(actorID);
        TTYD64CounterUI* counters = TTYD64_bc_ActorCounters(actorID);

        if (rec == nullptr || counters == nullptr) {
            continue;
        }

        for (buff = 0; buff < TTYD64_BUFF_COUNT; buff++) {
            TTYD64CounterUI* counter = &counters[buff];
            TTYD64Buff* boost = &rec->buffs[buff];
            s32 animState = counter->animationState;
            s32 amount = boost->amount;

            if (((animState & 0xFFFF) | (amount & 0xFFFF)) == 0) {
                continue;
            }
            if (counter->fx != nullptr && !(counter->fx->flags & FX_INSTANCE_FLAG_BATTLE)) {
                continue;
            }
            if (boost->turns == 0) {
                boost->amount = 0;
                boost->turns = 0;
            }
            if (animState == 2) {
                s32 counterType = counter->counterType;

                amount = boost->amount;
                if (amount == 0) {
                    counter->animationState = 3;
                } else if (amount > 0) {
                    if (counterType != 0) {
                        counter->animationState = 3;
                    }
                } else {
                    if (counterType == 0) {
                        counter->animationState = 3;
                    }
                }
                continue;
            }
            if (counter->animationState == 0) {
                Evt* script;

                counter->animationState = 1;
                script = start_script(&TTYD64_Script_MakeEffect, EVT_PRIORITY_1, 0);
                if (buff < 2) {
                    script->varTable[0] = EFFECT_STAT_CHANGE;
                } else {
                    script->varTable[0] = EFFECT_RECOVER;
                    script->varTable[1] = buff == 2 ? 0 : 1;
                }
                script->varTable[2] = (Bytecode) &counter->fx;
                script->varTable[3] = buff;
                script->varTable[4] = boost->amount;
                script->varTable[5] = (Bytecode) &counter->counterType;
                counter->animationState = 1;
                continue;
            }
            {
                u32 timer = (u32) counter->animationTimer + 1;

                counter->animationTimer = timer;
                if (timer < 10) {
                    continue;
                }
            }
            animState = counter->animationState;
            counter->animationTimer = 0;
            if (animState == 1) {
                counter->animationState = 2;
                continue;
            }
            if (counter->fx != nullptr) {
                remove_effect(counter->fx);
            }
            counter->fx = nullptr;
            counter->counterType = 0;
            counter->animationState = 0;
            counter->animationTimer = 0;
        }
    }
}

static void draw_counters(void) {
    s32 index;
    s32 buff;

    for (index = 0; index < TTYD64_BC_NUM_ACTOR_SLOTS; index++) {
        s32 actorID = counter_actor_id(index);
        TTYD64BattleRec* rec = TTYD64_ActorRec(actorID);
        TTYD64CounterUI* counters = TTYD64_bc_ActorCounters(actorID);
        s32 active = 0;

        if (counters == nullptr) {
            continue;
        }

        for (buff = 0; buff < TTYD64_BUFF_COUNT; buff++) {
            TTYD64CounterUI* counter = &counters[buff];
            EffectInstance* fx = counter->fx;
            Actor* actor;
            s32 iconX;
            s32 iconY;
            f32 x, y, z, anim;
            s32 opacity;
            s32 number;

            if (fx == nullptr || !(fx->flags & FX_INSTANCE_FLAG_BATTLE)) {
                continue;
            }
            active++;
            actor = get_actor(actorID);
            if (actor == nullptr) {
                continue;
            }
            iconX = actor->actorBlueprint->statusTextOffset.x;
            iconY = actor->actorBlueprint->statusTextOffset.y;
            if ((u16) actor->actorID >= ACTOR_ENEMY0 && (actor->flags & ACTOR_FLAG_UPSIDE_DOWN)) {
                iconY = 0;
            }
            iconY = (s32) rintf((f32) iconY * actor->scalingFactor);
            iconX += 3;
            iconY += 17 * (active - 1);
            x = actor->curPos.x - (f32) iconX;
            y = actor->curPos.y + (f32) iconY;
            z = actor->curPos.z + 3.0f;
            if (counter->animationState == 3) {
                anim = (f32) (-(s32) counter->animationTimer);
            } else if (counter->animationState == 2) {
                anim = 0.0f;
            } else {
                anim = (f32) ((s32) counter->animationTimer - 10);
            }
            x += anim;
            y -= anim;
            if (buff < 2) {
                fx->data.statChange->pos.x = x;
                fx->data.statChange->pos.y = y;
                fx->data.statChange->pos.z = z;
            } else {
                fx->data.recover->pos.x = x;
                fx->data.recover->pos.y = y;
                fx->data.recover->pos.z = z;
            }
            if (counter->animationState == 2) {
                opacity = 255;
            } else {
                opacity = (s32) rintf((f32) counter->animationTimer / 10.0f * 255.0f);
                if (counter->animationState == 3) {
                    opacity = 255 - opacity;
                }
            }
            if (rec == nullptr) {
                continue;
            }
            number = rec->buffs[buff].turns;
            if (buff < 2) {
                StatChangeFXData* data = fx->data.statChange;

                if (number == 0) {
                    number = 1;
                } else if (counter->counterType != 0) {
                    number = -number;
                }
                data->arrowValue = number;
                data->timeLeft = 20;
                data->unk_24 = opacity;
                data->scale = 0.6875f;
                data->scaleX = 1.0f;
                data->scaleY = 0.8125f;
            } else {
                RecoverFXData* data = fx->data.recover;

                if (number == 0) {
                    number = 1;
                }
                data[0].unk_40 = number;
                data[0].timeLeft = 20;
                data[1].vel.y = 0.0f;
                data[1].angle = 0.0f;
                data[1].alpha = opacity;
                data[1].scaleX = 0.75f;
                data[1].scaleY = 0.75f;
                data[0].pos.y = data[0].pos.y + 9.5f;
            }
        }
    }
}

void TTYD64_bc_NewStatuses_Step(void) {
    update_counters();
    draw_counters();
}

static void remove_counters(s32 actorID) {
    TTYD64CounterUI* counters = TTYD64_bc_ActorCounters(actorID);
    s32 i;

    if (counters == nullptr) {
        return;
    }
    for (i = 0; i < TTYD64_BUFF_COUNT; i++) {
        counters[i].counterType = 0;
        counters[i].animationState = 0;
        counters[i].animationTimer = 0;
        if (counters[i].fx != nullptr) {
            remove_effect(counters[i].fx);
        }
        counters[i].fx = nullptr;
    }
}

static void clear_buffs(TTYD64BattleRec* rec) {
    memset(rec->buffs, 0, sizeof(rec->buffs));
}

void TTYD64_bc_RemoveBuffs_Partner(void) {
    TTYD64BattleRec* rec = TTYD64_CurPartnerRec();

    if (rec == nullptr) {
        return;
    }
    clear_buffs(rec);
    remove_counters(ACTOR_PARTNER);
}

void TTYD64_Function_RemoveBuffs_ActorID(s32 actorID) {
    TTYD64BattleRec* rec;

    if (actorID == ACTOR_PARTNER) {
        TTYD64_bc_RemoveBuffs_Partner();
        return;
    }
    rec = TTYD64_ActorRec(actorID);
    if (rec != nullptr) {
        clear_buffs(rec);
    }
    remove_counters(actorID);
}

static void set_counters_visible(s32 first, s32 last, b32 visible) {
    s32 index;
    s32 i;

    for (index = first; index < last; index++) {
        TTYD64CounterUI* counters = TTYD64_bc_ActorCounters(counter_actor_id(index));

        if (counters == nullptr) {
            continue;
        }
        for (i = 0; i < TTYD64_BUFF_COUNT; i++) {
            EffectInstance* fx = counters[i].fx;

            if (fx == nullptr) {
                continue;
            }
            if (visible) {
                fx->flags |= FX_INSTANCE_FLAG_BATTLE;
            } else {
                fx->flags &= 0xFFFB;
            }
        }
    }
}

void TTYD64_UpdateNewStatuses_Visibility(s32 battleState) {
    s32 all = TTYD64_BC_NUM_ACTOR_SLOTS;

    switch (battleState) {
        case BATTLE_STATE_PLAYER_MOVE:
        case BATTLE_STATE_PARTNER_MOVE:
        case BATTLE_STATE_NEXT_ENEMY:
            set_counters_visible(0, all, false);
            break;
        case BATTLE_STATE_PLAYER_MENU:
        case BATTLE_STATE_PARTNER_MENU:
        case BATTLE_STATE_SWITCH_TO_PLAYER:
        case BATTLE_STATE_SWITCH_TO_PARTNER:
            set_counters_visible(0, all, true);
            break;
        case BATTLE_STATE_SELECT_TARGET:
        case BATTLE_STATE_RUN_AWAY:
        case BATTLE_STATE_DEFEND:
            set_counters_visible(0, 2, false);
            break;
        case BATTLE_STATE_CELEBRATION:
        case BATTLE_STATE_BEGIN_PLAYER_TURN:
        case BATTLE_STATE_PREPARE_MENU:
        case BATTLE_STATE_CHANGE_PARTNER:
            set_counters_visible(0, 2, true);
            break;
        case BATTLE_STATE_TRANSFER_TURN:
            set_counters_visible(2, all, true);
            break;
        default:
            set_counters_visible(0, all, false);
            break;
    }
}

void TTYD64_bc_AdvanceBuffData_Actor(s32 actorID) {
    TTYD64BattleRec* rec = TTYD64_ActorRec(actorID);
    s32 i;

    if (rec == nullptr) {
        return;
    }
    for (i = 0; i < TTYD64_BUFF_COUNT; i++) {
        s32 turns = rec->buffs[i].turns;

        if (turns == 0) {
            continue;
        }
        turns--;
        rec->buffs[i].turns = turns;
        if (turns == 0) {
            BattleStatusUpdateDelay = TTYD64_BC_BATTLE_WAIT_TIMER_EXPIRED;
        }
    }
}

void TTYD64_bc_AdvanceBuffData_Enemies(void) {
    s32 enemy;
    s32 i;

    for (enemy = 0; enemy < 24; enemy++) {
        TTYD64BattleRec* rec = TTYD64_ActorRec(ACTOR_ENEMY0 + enemy);

        if (rec == nullptr) {
            continue;
        }
        for (i = 0; i < TTYD64_BUFF_COUNT; i++) {
            if (rec->buffs[i].turns != 0) {
                rec->buffs[i].turns--;
            }
        }
    }
}

static void heal_actor_buffs(s32 actorID) {
    TTYD64BattleRec* rec = TTYD64_ActorRec(actorID);
    Actor* actor;
    s32 amount;

    if (rec == nullptr) {
        return;
    }
    if (actorID == ACTOR_PLAYER) {
        actor = gBattleStatus.playerActor;
    } else {
        actor = get_actor(actorID);
    }
    amount = rec->buffs[TTYD64_BUFF_HP_REGEN].amount;
    if (amount != 0) {
        TTYD64_ShowFlyingStat(actor, 0, amount);
        TTYD64_Data_ActorsWithHPFPBuffs++;
        TTYD64_heal_actor((u16) actor->actorID, rec->buffs[TTYD64_BUFF_HP_REGEN].amount);
        if (actorID == ACTOR_PLAYER) {
            u32 curHP = (u8) gPlayerData.curHP;
            s32 rush = (u8) gBattleStatus.rushFlags;

            gBattleStatus.rushFlags = 0;
            if (rush != 0) {
                if (curHP == 1) {
                    if (TTYD64_IsBadgeEquipped(0xF9)) {
                        gBattleStatus.rushFlags = 1;
                    }
                } else if (curHP < 6) {
                    if (TTYD64_IsBadgeEquipped(0x10D)) {
                        gBattleStatus.rushFlags = 2;
                    }
                }
            }
        }
    }
    amount = rec->buffs[TTYD64_BUFF_FP_REGEN].amount;
    if (amount != 0) {
        f32 savedY = actor->curPos.y;

        actor->curPos.y = actor->curPos.y + 23.0f;
        TTYD64_ShowFlyingStat(actor, 1, amount);
        actor->curPos.y = savedY;
        if ((u16) actor->actorID < ACTOR_ENEMY0) {
            s32 fp = (u8) gPlayerData.curFP + rec->buffs[TTYD64_BUFF_FP_REGEN].amount;
            u32 maxFP = (u8) gPlayerData.curMaxFP;

            if (fp < 0) {
                fp = 0;
            }
            if (!((u32) fp < maxFP)) {
                fp = maxFP;
            }
            gPlayerData.curFP = fp;
        }
    }
}

void TTYD64_bc_HPFBBuffs_Heal_Init(void) {
    s32 i;
    s32 count;

    TTYD64_Data_ActorsWithHPFPBuffs = 0;
    for (i = 0; i < TTYD64_BC_NUM_ACTOR_SLOTS; i++) {
        Actor* actor = i == 0 ? gBattleStatus.playerActor
            : i == 1          ? gBattleStatus.partnerActor
                              : gBattleStatus.enemyActors[i - 2];

        if (actor != nullptr) {
            heal_actor_buffs((u16) actor->actorID);
        }
    }
    count = TTYD64_Data_ActorsWithHPFPBuffs;
    TTYD64_Data_ActorsWithHPFPBuffs = 0;
    if (count != 0) {
        sfx_play_sound(0x213);
        BattleStatusUpdateDelay = TTYD64_BC_BATTLE_WAIT_TIMER_EXPIRED;
    }
}

static s32 resolve_actor_arg(Evt* script, s32 actorID) {
    if (actorID == ACTOR_SELF) {
        actorID = script->owner1.actorID;
    }
    return actorID;
}

static void apply_boost_native(Evt* script, s32 buff) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID = evt_get_variable(script, args[0]);
    s32 amount = evt_get_variable(script, args[1]);
    s32 turns = evt_get_variable(script, args[2]);
    TTYD64BattleRec* rec;
    TTYD64Buff* boost;
    s32 old;

    actorID = resolve_actor_arg(script, actorID);
    if (!((u32) actorID < 0xA0)) {
        turns++;
    }
    rec = TTYD64_ActorRec(actorID);
    if (rec == nullptr) {
        return;
    }
    boost = &rec->buffs[buff];
    old = boost->amount;
    if (old > 0) {
        if (amount < 0) {
            boost->amount = 0;
            boost->turns = 0;
            return;
        }
    } else if (old != 0) {
        if (amount > 0) {
            boost->amount = 0;
            boost->turns = 0;
            return;
        }
    }
    boost->amount = amount;
    boost->turns = turns;
}

API_CALLABLE(TTYD64_AddDefenseBoost) {
    apply_boost_native(script, TTYD64_BUFF_DEFENSE);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_AddAttackBoost) {
    apply_boost_native(script, TTYD64_BUFF_ATTACK);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_AddCharge) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID = resolve_actor_arg(script, evt_get_variable(script, args[0]));
    TTYD64BattleRec* rec = TTYD64_ActorRec(actorID);
    s32 amount = evt_get_variable(script, args[1]);

    if (rec != nullptr) {
        rec->charge = (s8) rec->charge + amount;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_MakeActorGiant) {
    s32 actorID = resolve_actor_arg(script, evt_get_variable(script, script->ptrReadPos[0]));
    TTYD64BattleRec* rec = TTYD64_ActorRec(actorID);

    if (rec != nullptr) {
        rec->giant = true;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_MakeActorTiny) {
    s32 actorID = resolve_actor_arg(script, evt_get_variable(script, script->ptrReadPos[0]));
    TTYD64BattleRec* rec = TTYD64_ActorRec(actorID);

    if (rec != nullptr) {
        rec->tiny = true;
    }
    return ApiStatus_DONE2;
}

static void stash_boost_turns(Evt* script, s32 stat) {
    Bytecode* args = script->ptrReadPos;
    TTYD64BattleRec* rec = TTYD64_ActorRec(resolve_actor_arg(script, evt_get_variable(script, args[0])));

    if (rec != nullptr) {
        rec->pendingBoostTurns[stat] = evt_get_variable(script, args[2]);
    }
}

API_CALLABLE(TTYD64_BoostAttack) {
    if (isInitialCall) {
        stash_boost_turns(script, ACTOR_STAT_BOOST_ATTACK);
    }
    return BoostAttack(script, isInitialCall);
}

API_CALLABLE(TTYD64_BoostDefense) {
    if (isInitialCall) {
        stash_boost_turns(script, ACTOR_STAT_BOOST_DEFENSE);
    }
    return BoostDefense(script, isInitialCall);
}

static void sync_size(TTYD64BattleRec* rec) {
    s32 attack = rec->buffs[TTYD64_BUFF_ATTACK].amount;

    if (attack <= 0) {
        rec->giant = false;
    } else if (rec->giant) {
        rec->tiny = false;
    }
    if (attack >= 0) {
        rec->tiny = false;
    }
}

static void sync_all_sizes(void) {
    TTYD64BattleRec* rec;
    s32 i;

    rec = TTYD64_ActorRec(ACTOR_PLAYER);
    if (rec != nullptr) {
        sync_size(rec);
    }
    rec = TTYD64_ActorRec(ACTOR_PARTNER);
    if (rec != nullptr) {
        sync_size(rec);
    }
    for (i = 0; i < 24; i++) {
        rec = TTYD64_ActorRec(ACTOR_ENEMY0 + i);
        if (rec != nullptr) {
            sync_size(rec);
        }
    }
}

static s32 scale_target(Actor* actor) {
    TTYD64BattleRec* rec = TTYD64_ActorRec((u16) actor->actorID);

    if (rec == nullptr) {
        return 100;
    }
    if (rec->giant && rec->buffs[TTYD64_BUFF_ATTACK].amount > 0) {
        return 200;
    }
    if (rec->tiny && rec->buffs[TTYD64_BUFF_ATTACK].amount < 0) {
        return 40;
    }
    return 100;
}

static void bc_on_actor_stat(IEvent* event) {
    OnActorStat* ev = (OnActorStat*) event;
    Actor* actor = ev->actor;
    TTYD64BattleRec* rec = TTYD64_ActorRec((u16) actor->actorID);

    switch (ev->stat) {
        case ACTOR_STAT_ATTACK_BOOST:
            *ev->value = rec != nullptr ? rec->buffs[TTYD64_BUFF_ATTACK].amount : 0;
            break;
        case ACTOR_STAT_DEFENSE_BOOST:
            *ev->value = rec != nullptr ? rec->buffs[TTYD64_BUFF_DEFENSE].amount : 0;
            break;
        case ACTOR_STAT_GLOW:
            *ev->value = rec != nullptr ? rec->charge : 0;
            break;
        case ACTOR_STAT_IDLE_PALETTE:
            *ev->value = ACTOR_PAL_ADJUST_NONE;
            break;
        case ACTOR_STAT_STATUS_FLAGS: {
            s32 flags = *ev->value
                & ~(STATUS_FLAG_ATTACK_BOOST | STATUS_FLAG_DEFENSE_BOOST | STATUS_FLAG_CHILL_OUT | STATUS_FLAG_SHRINK
                    | STATUS_FLAG_GLOWING);

            if (rec != nullptr) {
                if (rec->tiny) {
                    flags |= STATUS_FLAG_SHRINK;
                }
                if (rec->charge != 0) {
                    flags |= STATUS_FLAG_GLOWING;
                }
                if (rec->buffs[TTYD64_BUFF_ATTACK].amount != 0) {
                    flags |= STATUS_FLAG_ATTACK_BOOST;
                }
                if (rec->buffs[TTYD64_BUFF_DEFENSE].amount != 0) {
                    flags |= STATUS_FLAG_DEFENSE_BOOST;
                }
            }
            *ev->value = flags;
            break;
        }
        case ACTOR_STAT_SCALE:
            *ev->value = scale_target(actor);
            break;
        case ACTOR_STAT_KO_TURNS:
            if ((u8) actor->debuff == STATUS_KEY_SHRINK) {
                *ev->value = 0;
            }
            break;
    }
}

static void bc_on_damage_calc(IEvent* event) {
    OnDamageCalc* ev = (OnDamageCalc*) event;
    Actor* attacker = ev->attacker;
    TTYD64BattleRec* rec;

    if (ev->source != ATTACK_SOURCE_ENEMY || ev->stage != DAMAGE_STAGE_AFTER_BOOSTS) {
        return;
    }
    rec = TTYD64_ActorRec((u16) attacker->actorID);
    if (rec != nullptr) {
        *ev->damage += rec->charge;
    }
    if (attacker->chillOutTurns != 0) {
        *ev->damage += attacker->chillOutAmount;
    }
}

API_CALLABLE(TTYD64_ApplyShrinkFromOwner) {
    Bytecode* args = script->ptrReadPos;
    Actor* actor = get_actor(script->owner1.actorID);
    s32 amt = evt_get_variable(script, *args);
    TTYD64BattleRec* rec = TTYD64_ActorRec(actor->actorID);

    if (rec != nullptr && rec->tiny) {
        amt += rec->buffs[TTYD64_BUFF_ATTACK].amount;
    }
    evt_set_variable(script, *args++, amt);
    return ApiStatus_DONE2;
}

static void bc_on_actor_boost(IEvent* event) {
    OnActorBoost* ev = (OnActorBoost*) event;
    s32 buff = ev->stat == ACTOR_STAT_BOOST_ATTACK ? TTYD64_BUFF_ATTACK : TTYD64_BUFF_DEFENSE;
    TTYD64BattleRec* rec = TTYD64_ActorRec((u16) ev->actor->actorID);
    s32 amount = ev->amount;
    TTYD64Buff* boost;
    s32 turns;
    s32 old;

    event->Cancelled = true;
    if (rec == nullptr) {
        return;
    }
    turns = rec->pendingBoostTurns[ev->stat];
    rec->pendingBoostTurns[ev->stat] = 0;
    boost = &rec->buffs[buff];
    old = boost->amount;
    if (old > 0) {
        if (amount < 0) {
            boost->amount = 0;
            boost->turns = 0;
            return;
        }
    } else if (old != 0) {
        if (amount != 0) {
            boost->amount = 0;
            boost->turns = 0;
            return;
        }
    }
    boost->amount = amount;
    boost->turns = turns;
}

static void clear_player_buffs(s32* mask) {
    TTYD64BattleRec* rec = TTYD64_ActorRec(ACTOR_PLAYER);

    if (*mask & PLAYER_BUFF_JUMP_CHARGE) {
        *mask &= ~PLAYER_BUFF_JUMP_CHARGE;
        gBattleStatus.flags1 &= ~BS_FLAGS1_JUMP_CHARGED;
        rec->buffs[TTYD64_BUFF_ATTACK].amount = 0;
        rec->buffs[TTYD64_BUFF_ATTACK].turns = 0;
    }
    if (*mask & PLAYER_BUFF_HAMMER_CHARGE) {
        *mask &= ~PLAYER_BUFF_HAMMER_CHARGE;
        gBattleStatus.flags1 &= ~BS_FLAGS1_HAMMER_CHARGED;
        rec->buffs[TTYD64_BUFF_DEFENSE].amount = 0;
        rec->buffs[TTYD64_BUFF_DEFENSE].turns = 0;
    }
    *mask &= ~PLAYER_BUFF_TURBO_CHARGE;
    if (*mask & 0x400) {
        rec->buffs[TTYD64_BUFF_HP_REGEN].amount = 0;
        rec->buffs[TTYD64_BUFF_HP_REGEN].turns = 0;
    }
    if (*mask & 0x800) {
        rec->buffs[TTYD64_BUFF_FP_REGEN].amount = 0;
        rec->buffs[TTYD64_BUFF_FP_REGEN].turns = 0;
    }
    if (*mask & 0x1000) {
        rec->charge = 0;
    }
}

static void clear_partner_buffs(Actor* partner, s32* mask) {
    TTYD64BattleRec* rec = TTYD64_CurPartnerRec();

    *mask &= ~PLAYER_BUFF_PARTNER_GLOWING;
    if (rec != nullptr) {
        rec->staticTurns = 0;
        rec->transparentTurns = 0;
        memset(rec->buffs, 0, sizeof(rec->buffs));
        rec->charge = 0;
    }
    if (partner->staticStatus != 0) {
        remove_status_static(partner->hudElementDataIndex);
    }
    partner->staticStatus = 0;
    partner->staticDuration = 0;
    partner->stoneStatus = 0;
    partner->stoneDuration = 0;
    if (partner->transparentStatus != 0) {
        remove_status_transparent(partner->hudElementDataIndex);
    }
    partner->transparentStatus = 0;
    partner->transparentDuration = 0;
}

static void dispel_buffs(Actor* target, s32* mask) {
    TTYD64BattleRec* rec = TTYD64_ActorRec((u16) target->actorID);

    if (rec != nullptr && rec->tiny) {
        *mask |= ACTOR_BUFF_BOOSTS;
    }
    if (*mask == 0) {
        return;
    }
    if (rec != nullptr) {
        memset(rec->buffs, 0, sizeof(rec->buffs));
        rec->charge = 0;
    }
    if (target->staticStatus == 0) {
        target->staticDuration = 0;
    }
}

static void bc_on_buffs_clear(IEvent* event) {
    OnBuffsClear* ev = (OnBuffsClear*) event;

    switch (ev->reason) {
        case BUFFS_CLEAR_SCRIPT:
            if (ev->actor->actorID == ACTOR_PLAYER) {
                clear_player_buffs(ev->mask);
            } else {
                clear_partner_buffs(ev->actor, ev->mask);
            }
            break;
        case BUFFS_CLEAR_DISPEL:
            dispel_buffs(ev->actor, ev->mask);
            break;
    }
}

static void bc_on_battle_step(IEvent* event) {
    OnBattleStep* ev = (OnBattleStep*) event;

    if (ev->stage == BATTLE_STEP_AFTER_EFFECTS) {
        sync_all_sizes();
        TTYD64_bc_NewStatuses_Step();
    }
}

void TTYD64_InstallBattleCoreNewStatuses(void) {
    REGISTER_LISTENER(OnActorStat, EVENT_PRIORITY_NORMAL, bc_on_actor_stat);
    REGISTER_LISTENER(OnDamageCalc, EVENT_PRIORITY_NORMAL, bc_on_damage_calc);
    REGISTER_LISTENER(OnActorBoost, EVENT_PRIORITY_NORMAL, bc_on_actor_boost);
    REGISTER_LISTENER(OnBuffsClear, EVENT_PRIORITY_NORMAL, bc_on_buffs_clear);
    REGISTER_LISTENER(OnBattleStep, EVENT_PRIORITY_NORMAL, bc_on_battle_step);
}
