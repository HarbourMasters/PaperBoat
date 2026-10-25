#include "port/romhack/specific/TTYD64/battle/bc_internal.h"
#include "port/patches/Patches.h"

static b32 sPlayerTurnRestarting;

b32 TTYD64_bc_PlayerTurnRestarting(void) {
    return sPlayerTurnRestarting;
}

void TTYD64_bc_UnhideAllEnemiesDebuffIcons(void) {
    s32 i;

    for (i = 0; i < 24; i++) {
        Actor* enemy = gBattleStatus.enemyActors[i];

        if (enemy != nullptr) {
            enemy->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS;
        }
    }
}

void TTYD64_bc_AdvanceEnemiesStatus(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    s32 waiting = false;
    s32 i;

    for (i = 0; i < 24; i++) {
        Actor* enemy = battleStatus->enemyActors[i];

        if (enemy == nullptr || enemy->handleEventScript == nullptr) {
            continue;
        }
        if (does_script_exist(enemy->handleEventScriptID)) {
            waiting = true;
        } else {
            enemy->handleEventScript = nullptr;
        }
    }
    if (waiting) {
        return;
    }
    reset_actor_turn_info();
    for (i = 0; i < 24; i++) {
        Actor* enemy = battleStatus->enemyActors[i];
        s32 oldKo;
        s32 duration;

        if (enemy == nullptr) {
            continue;
        }
        enemy->flags =
            (enemy->flags | ACTOR_FLAG_USING_IDLE_ANIM | ACTOR_FLAG_SHOW_STATUS_ICONS) & ~ACTOR_FLAG_SKIP_TURN;
        if (enemy->debuff != 0) {
            enemy->debuffDuration--;
            if (enemy->debuffDuration <= 0) {
                enemy->debuff = 0;
                remove_status_debuff(enemy->hudElementDataIndex);
                dispatch_event_actor(enemy, EVENT_RECOVER_STATUS);
                BattleStatusUpdateDelay = 20;
            }
        }
        if (enemy->staticStatus != 0) {
            enemy->staticDuration--;
            if (enemy->staticDuration <= 0) {
                enemy->staticStatus = 0;
                remove_status_static(enemy->hudElementDataIndex);
                BattleStatusUpdateDelay = 20;
            }
        }
        if (enemy->transparentStatus != 0) {
            enemy->transparentDuration--;
            if (enemy->transparentDuration <= 0) {
                enemy->transparentStatus = 0;
                remove_status_transparent(enemy->hudElementDataIndex);
                BattleStatusUpdateDelay = 20;
            }
        }
        if (enemy->stoneStatus != 0) {
            enemy->stoneDuration--;
            if (enemy->stoneDuration <= 0) {
                enemy->stoneStatus = 0;
                BattleStatusUpdateDelay = 20;
            }
        }
        oldKo = enemy->koDuration;
        enemy->koDuration = enemy->debuffDuration;
        duration = enemy->koDuration;
        if (duration > 0) {
            enemy->koStatus = STATUS_KEY_KO;
            enemy->disableEffect->data.disableX->koDuration = enemy->koDuration;
        } else if (oldKo != duration) {
            enemy->koStatus = 0;
            enemy->disableEffect->data.disableX->koDuration = 0;
        }
        TTYD64_bc_AdvanceBuffData_Actor(enemy->actorID);
        if (enemy->debuff == STATUS_KEY_POISON) {
            s32 timer;

            gBattleStatus.flags1 |= BS_FLAGS1_TRIGGER_EVENTS;
            dispatch_damage_event_actor_0(enemy, 1, EVENT_HIT);
            timer = enemy->curHP == 0 ? 100 : 20;
            if (BattleStatusUpdateDelay != 100) {
                BattleStatusUpdateDelay = timer;
            }
        }
    }
}

void TTYD64_bc_AdvancePartnersStatus(void) {
    Actor* partner;
    TTYD64BattleRec* rec;

    TTYD64_bc_AdvancePartnersExtraData();
    if (TTYD64_GetPartnerHP() <= 0) {
        btl_update_ko_status();
        return;
    }
    partner = get_actor(ACTOR_PARTNER);
    rec = TTYD64_CurPartnerRec();
    if (rec->debuffKey != 0) {
        if (rec->debuffTurns != 0) {
            s32 turns = partner->debuffDuration - 1;

            partner->debuffDuration = turns;
            BattleStatusUpdateDelay = 20;
            partner->disableEffect->data.disableX->koDuration = turns;
            partner->koDuration = turns;
        }
        if (rec->debuffTurns == 0) {
            partner->debuff = 0;
            partner->debuffDuration = 0;
            rec->debuffKey = 0;
            rec->debuffTurns = 0;
            remove_status_debuff((u16) partner->hudElementDataIndex);
            if (partner->koStatus != 0) {
                partner->koStatus = 0;
                partner->koDuration = 0;
                BattleStatusUpdateDelay = 20;
                partner->disableEffect->data.disableX->koDuration = 0;
                dispatch_event_partner(EVENT_RECOVER_FROM_KO);
            }
        }
    }
    if (rec->staticTurns != 0) {
        s32 left = rec->staticTurns - 1;

        rec->staticTurns = left;
        partner->staticDuration = left;
        if ((u8) left == 0) {
            rec->staticTurns = 0;
            partner->staticStatus = 0;
            partner->staticDuration = 0;
            remove_status_static((u16) partner->hudElementDataIndex);
        }
    }
    if (rec->transparentTurns != 0) {
        s32 left = rec->transparentTurns - 1;

        rec->transparentTurns = left;
        partner->transparentDuration = left;
        if ((u8) left == 0) {
            rec->transparentTurns = 0;
            partner->transparentStatus = 0;
            partner->transparentDuration = 0;
            remove_status_transparent((u16) partner->hudElementDataIndex);
        }
    }
    btl_update_ko_status();
}

static void bc_on_inflict_status(IEvent* event) {
    OnInflictStatus* ev = (OnInflictStatus*) event;
    Actor* target = ev->actor;
    s32 key = ev->status;
    b32 debuffGroup = key >= STATUS_KEY_UNUSED && key <= STATUS_KEY_SHRINK;
    TTYD64BattleRec* rec;

    if ((u16) target->actorID < ACTOR_ENEMY0) {
        (*ev->duration)++;
    }
    if (target->actorID == ACTOR_PARTNER) {
        *ev->immune = debuffGroup && TTYD64_IsBadgeActivated_Stack(0x189) != 0;
    }
    if (*ev->immune) {
        return;
    }
    if (target->actorID == ACTOR_PARTNER) {
        rec = TTYD64_CurPartnerRec();
        if (rec == nullptr) {
            return;
        }
        if (debuffGroup) {
            rec->debuffKey = key;
            rec->debuffTurns = *ev->duration;
            rec->defendStack = 0;
        } else if (key == STATUS_KEY_STATIC) {
            rec->staticTurns = *ev->duration;
        } else if (key == STATUS_KEY_TRANSPARENT) {
            rec->transparentTurns = *ev->duration;
        } else if (key == STATUS_KEY_STONE) {
            rec->debuffKey = key;
            rec->debuffTurns = *ev->duration;
        }
    } else if (target->actorID == ACTOR_PLAYER && debuffGroup) {
        TTYD64_ActorRec(ACTOR_PLAYER)->defendStack = 0;
    }
}

static void bc_on_status_tick(IEvent* event) {
    OnStatusTick* ev = (OnStatusTick*) event;
    Actor* actor = ev->actor;

    switch (ev->phase) {
        case STATUS_PHASE_PLAYER_TURN_DAMAGE:
            if (sPlayerTurnRestarting) {
                event->Cancelled = true;
                break;
            }
            if (actor->actorID == ACTOR_PARTNER && TTYD64_GetPartnerHP() > 0 && actor->debuff == STATUS_KEY_POISON) {
                dispatch_damage_event_partner_0(1, EVENT_HIT, 0);
            }
            break;
        case STATUS_PHASE_PLAYER_TURN:
            if (sPlayerTurnRestarting) {
                event->Cancelled = true;
                break;
            }
            if (actor->actorID == ACTOR_PLAYER) {
                TTYD64_bc_HPFBBuffs_Heal_Init();
                TTYD64_bc_AdvancePartnersStatus();
                TTYD64_bc_AdvanceBuffData_Actor(ACTOR_PLAYER);
                TTYD64_bc_AdvanceEnemiesStatus();
            }
            break;
        case STATUS_PHASE_PARTNER_TURN:
        case STATUS_PHASE_ENEMY_TURN:
            event->Cancelled = true;
            break;
        case STATUS_PHASE_TURN_END:
            if (actor->actorID == ACTOR_PARTNER) {
                if ((u8) actor->debuff == STATUS_KEY_POISON) {
                    event->Cancelled = true;
                } else {
                    actor->flags |= ACTOR_FLAG_SHOW_STATUS_ICONS | ACTOR_FLAG_USING_IDLE_ANIM;
                }
            }
            break;
    }
}

static void bc_on_turn_order(IEvent* event) {
    OnTurnOrder* ev = (OnTurnOrder*) event;
    Actor* partner = gBattleStatus.partnerActor;

    switch (ev->decision) {
        case TURN_ORDER_PLAYER_SKIPPED:
            if ((u8) gBattleStatus.playerActor->debuff != 0) {
                break;
            }
            if (TTYD64_MarioInFront) {
                *ev->value = TURN_SKIP_RESTART;
                sPlayerTurnRestarting = true;
            } else {
                *ev->value = TURN_SKIP_KEEP_TURN;
            }
            break;
        case TURN_ORDER_SKIP_PARTNER_TURN:
            if (gBattleState == BATTLE_STATE_BEGIN_PARTNER_TURN && partner->koStatus != 0
                && partner->debuff != STATUS_KEY_POISON && partner->debuff != STATUS_KEY_SHRINK)
            {
                *ev->value = true;
            }
            break;
        case TURN_ORDER_CAN_CHANGE_PARTNER:
            *ev->value = true;
            break;
        case TURN_ORDER_PLAYER_IN_FRONT:
            if (gBattleState == BATTLE_STATE_CHANGE_PARTNER) {
                TTYD64BattleRec* rec = TTYD64_CurPartnerRec();
                s32 status = rec != nullptr ? rec->debuffKey : 0;

                if (status != 0 && status != STATUS_KEY_POISON && status != STATUS_KEY_SHRINK) {
                    *ev->value = true;
                }
            }
            break;
    }
}

static void bc_on_battle_state_changed(IEvent* event) {
    OnBattleStateChanged* ev = (OnBattleStateChanged*) event;

    if (TTYD64_RequestedBattleState(ev->next) != BATTLE_STATE_BEGIN_PLAYER_TURN) {
        sPlayerTurnRestarting = false;
    }
    if (ev->prev == BATTLE_STATE_CHANGE_PARTNER) {
        TTYD64BattleRec* rec = TTYD64_CurPartnerRec();

        if (rec != nullptr && rec->debuffKey != 0) {
            gBattleStatus.flags2 |= BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;
        }
        TTYD64_bc_UnhideAllEnemiesDebuffIcons();
    }
}

static void change_partner_leave(Actor* partner) {
    TTYD64BattleRec* rec = TTYD64_CurPartnerRec();
    s32 status;

    if (rec != nullptr && rec->staticTurns != 0) {
        partner->staticStatus = 0;
        partner->staticDuration = 0;
        port_remove_status_icon_now((u16) partner->hudElementDataIndex, STATUS_ICON_SLOT_STATIC);
    }
    if (rec != nullptr && rec->transparentTurns != 0) {
        partner->transparentStatus = 0;
        partner->transparentDuration = 0;
        port_remove_status_icon_now((u16) partner->hudElementDataIndex, STATUS_ICON_SLOT_TRANSPARENT);
    }
    status = rec != nullptr ? rec->debuffKey : 0;
    if (status != 0) {
        if (status != STATUS_KEY_POISON && status != STATUS_KEY_SHRINK) {
            if (status == STATUS_KEY_FROZEN) {
                sfx_play_sound(0xE7);
                if (partner->icePillarEffect != nullptr) {
                    partner->icePillarEffect->flags |= FX_INSTANCE_FLAG_DISMISS;
                }
            }
            gBattleStatus.flags2 |= BS_FLAGS2_PARTNER_TURN_USED;
        }
        partner->debuff = 0;
        partner->debuffDuration = 0;
        port_remove_status_icon_now((u16) partner->hudElementDataIndex, STATUS_ICON_SLOT_DEBUFF);
    }
    if (TTYD64_GetPartnerHP() <= 0) {
        gBattleStatus.flags2 &= ~BS_FLAGS2_PARTNER_TURN_USED;
    }
    TTYD64_Function_GlitzPit_DontSwapChallenge();
}

static void change_partner_enter(void) {
    TTYD64BattleRec* rec = TTYD64_CurPartnerRec();
    Actor* partner;

    if (rec == nullptr) {
        return;
    }
    rec->giant = false;
    rec->tiny = false;
    if (rec->debuffKey != 0) {
        if (rec->debuffKey == STATUS_KEY_FROZEN) {
            partner = gBattleStatus.partnerActor;
            if (partner->icePillarEffect == nullptr) {
                partner->icePillarEffect =
                    fx_ice_pillar(0, partner->curPos.x, partner->curPos.y, partner->curPos.z, 1.0f, 0);
                create_status_debuff(partner->hudElementDataIndex, STATUS_KEY_FROZEN);
            }
        }
        partner = gBattleStatus.partnerActor;
        partner->debuff = rec->debuffKey;
        partner->debuffDuration = rec->debuffTurns;
        btl_update_ko_status();
        if (rec->debuffTurns == 0) {
            if (rec->debuffKey == STATUS_KEY_FROZEN) {
                partner->icePillarEffect->flags |= FX_INSTANCE_FLAG_DISMISS;
                partner->icePillarEffect = nullptr;
                port_remove_status_icon_now((u16) partner->hudElementDataIndex, STATUS_ICON_SLOT_DEBUFF);
            }
            partner->debuff = 0;
            partner->debuffDuration = 0;
            rec->debuffKey = 0;
            btl_update_ko_status();
            sfx_play_sound(0x352);
        }
        if (rec->debuffKey != STATUS_KEY_POISON && rec->debuffKey != STATUS_KEY_SHRINK) {
            gBattleStatus.flags2 |= BS_FLAGS2_PARTNER_TURN_USED | BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;
        }
    }
    if (rec->staticTurns != 0) {
        partner = gBattleStatus.partnerActor;
        partner->staticStatus = STATUS_KEY_STATIC;
        partner->staticDuration = rec->staticTurns;
        btl_update_ko_status();
    }
    if (rec->transparentTurns != 0) {
        partner = gBattleStatus.partnerActor;
        partner->transparentStatus = STATUS_KEY_TRANSPARENT;
        partner->transparentDuration = rec->transparentTurns;
        btl_update_ko_status();
    }
}

static void bc_on_partner_change(IEvent* event) {
    OnPartnerChange* ev = (OnPartnerChange*) event;

    if (gGameStatusPtr->context != CONTEXT_BATTLE) {
        return;
    }
    switch (ev->phase) {
        case PARTNER_CHANGE_LEAVE:
            change_partner_leave(gBattleStatus.partnerActor);
            break;
        case PARTNER_CHANGE_ENTER:
            change_partner_enter();
            break;
    }
}

static void bc_on_status_afflicted_notice(IEvent* event) {
    OnStatusAfflictedNotice* ev = (OnStatusAfflictedNotice*) event;
    Actor* player = ev->player;
    Actor* partner = ev->partner;
    s32 chosen;

    *ev->camPreset = BTL_CAM_PLAYER_ATTACK_APPROACH;
    if (player->statusAfflicted == 0 && (partner == nullptr || partner->statusAfflicted == 0)) {
        *ev->status = 0;
        return;
    }
    if (gBattleStatus.curTargetID == 0) {
        chosen = (u8) player->statusAfflicted;
        if (chosen == 0) {
            chosen = (u8) partner->statusAfflicted;
        }
    } else {
        chosen = partner != nullptr ? (u8) partner->statusAfflicted : 0;
        if (chosen == 0) {
            chosen = (u8) player->statusAfflicted;
        }
    }
    if (chosen == STATUS_KEY_STOP) {
        chosen = STATUS_KEY_PARALYZE;
    }
    *ev->status = chosen;
}

static void bc_on_hit_check(IEvent* event) {
    OnHitCheck* ev = (OnHitCheck*) event;

    if (ev->source != ATTACK_SOURCE_ENEMY || ev->phase != HIT_CHECK_TEST) {
        return;
    }
    if (gPlayerData.curPartner == PARTNER_WATT && ev->target != nullptr && *ev->hitResult == HIT_RESULT_HIT
        && !(gBattleStatus.curAttackElement & DAMAGE_TYPE_TRIGGER_LUCKY))
    {
        *ev->hitResult = HIT_RESULT_HIT_STATIC;
    }
    if (ev->attacker->targetActorID == ACTOR_PARTNER && TTYD64_GetPartnerHP() <= 0) {
        *ev->hitResult = HIT_RESULT_MISS;
    }
}

void TTYD64_InstallBattleCoreStatusEffects(void) {
    REGISTER_LISTENER(OnInflictStatus, EVENT_PRIORITY_NORMAL, bc_on_inflict_status);
    REGISTER_LISTENER(OnStatusTick, EVENT_PRIORITY_NORMAL, bc_on_status_tick);
    REGISTER_LISTENER(OnTurnOrder, EVENT_PRIORITY_NORMAL, bc_on_turn_order);
    REGISTER_LISTENER(OnBattleStateChanged, EVENT_PRIORITY_NORMAL, bc_on_battle_state_changed);
    REGISTER_LISTENER(OnPartnerChange, EVENT_PRIORITY_NORMAL, bc_on_partner_change);
    REGISTER_LISTENER(OnStatusAfflictedNotice, EVENT_PRIORITY_NORMAL, bc_on_status_afflicted_notice);
    REGISTER_LISTENER(OnHitCheck, EVENT_PRIORITY_NORMAL, bc_on_hit_check);
}
