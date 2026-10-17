#include "ph_internal.h"
#include "battle/battle_menu.h"
#include "battle/states/states.h"
#include "port/modding/Mod.h"

#define PH_STAR_POWER_POS_REFRESH 0
#define PH_STAR_POWER_POS_SMOOCH  4

extern EvtScript EVS_Partner_SpikeContact;
extern EvtScript EVS_Partner_BurnContact;
extern EvtScript EVS_UseLifeShroom;
extern EvtScript EVS_Partner_RunAway;
extern EvtScript EVS_Mario_HandlePhase;
extern EvtScript TTYD64_ph_EVS_Partner_SpikeContact;
extern EvtScript TTYD64_ph_EVS_Partner_BurnContact;
extern EvtScript TTYD64_ph_EVS_UseLifeShroom;
extern EvtScript TTYD64_ph_EVS_Partner_RunAway;

static u8 sSavedTurnUsed[2];

static s32 ph_turn_slot(s32 actorClass, s32* flag) {
    switch (actorClass) {
        case ACTOR_CLASS_PLAYER:
            *flag = BS_FLAGS2_PLAYER_TURN_USED;
            return 0;
        case ACTOR_CLASS_PARTNER:
            *flag = BS_FLAGS2_PARTNER_TURN_USED;
            return 1;
    }
    return -1;
}

API_CALLABLE(TTYD64_StashTurnUsed) {
    Bytecode* args = script->ptrReadPos;
    s32 flag;
    s32 slot = ph_turn_slot(evt_get_variable(script, *args++), &flag);
    b32 used;

    if (slot < 0) {
        return ApiStatus_DONE2;
    }
    used = (gBattleStatus.flags2 & flag) != 0;
    if (used) {
        gBattleStatus.flags2 &= ~flag;
    }
    sSavedTurnUsed[slot] = used;
    evt_set_variable(script, *args++, used);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_RestoreTurnUsed) {
    Bytecode* args = script->ptrReadPos;
    s32 flag;
    s32 slot = ph_turn_slot(evt_get_variable(script, *args++), &flag);
    s32 saved;

    if (slot < 0) {
        return ApiStatus_DONE2;
    }
    saved = sSavedTurnUsed[slot];
    if (saved == 1) {
        gBattleStatus.flags2 |= flag;
        sSavedTurnUsed[slot] = 0;
    }
    evt_set_variable(script, *args++, saved);
    return ApiStatus_DONE2;
}

static b32 ph_kooper_flipped_extra(void) {
    return gPlayerData.curPartner == PARTNER_KOOPER && TTYD64_PartnerRec(PARTNER_KOOPER)->flipped != 0;
}

static void ph_on_guard_check(IEvent* event) {
    OnGuardCheck* ev = (OnGuardCheck*) event;
    Actor* target = ev->target;

    if ((target->actorID & ACTOR_CLASS_MASK) != ACTOR_CLASS_PARTNER) {
        return;
    }
    if (!*ev->canGuard && target->stoneStatus == 0 && !(gBattleStatus.curAttackElement & DAMAGE_TYPE_UNBLOCKABLE)
        && (target->debuff == STATUS_KEY_POISON || target->debuff == STATUS_KEY_SHRINK))
    {
        *ev->canGuard = true;
    }
    if (*ev->canGuard && ph_kooper_flipped_extra()) {
        *ev->canGuard = false;
        cancel_action_rating_combo(target);
    }
}

static void ph_on_actor_hp_change(IEvent* event) {
    OnActorHpChange* ev = (OnActorHpChange*) event;
    s32 hp;

    if (ev->actor == nullptr || (ev->actor->actorID & ACTOR_CLASS_MASK) != ACTOR_CLASS_PARTNER) {
        return;
    }
    if (ev->source != HP_SOURCE_ENEMY_ATTACK && ev->source != HP_SOURCE_DIRECT) {
        return;
    }
    if (*ev->delta >= 0) {
        return;
    }
    hp = TTYD64_GetPartnerHP() + *ev->delta;
    if (hp <= 0) {
        hp = 0;
    }
    TTYD64_SetPartnerHP(hp);
    event->Cancelled = true;
}

static void ph_on_damage_event_dispatch(IEvent* event) {
    OnDamageEventDispatch* ev = (OnDamageEventDispatch*) event;

    if (ev->source != HP_SOURCE_ITEM) {
        return;
    }
    if ((u16) ev->target->actorID == ACTOR_PARTNER && (u8) gPlayerData.curPartner == PARTNER_KOOPER
        && (gBattleStatus.curAttackElement & (DAMAGE_TYPE_JUMP | DAMAGE_TYPE_POW | DAMAGE_TYPE_QUAKE)))
    {
        *ev->event = EVENT_FLIP_TRIGGER;
    }
}

static void ph_on_set_target_actor(IEvent* event) {
    OnSetTargetActor* ev = (OnSetTargetActor*) event;

    if (*ev->targetActorID != ACTOR_PARTNER) {
        return;
    }
    if (gGameStatus.peachFlags != 0) {
        return;
    }
    if (TTYD64_GetPartnerHP() <= 0) {
        *ev->targetActorID = ACTOR_PLAYER;
    }
}

static void ph_add_partner_target(SelectableTarget* target) {
    Actor* partner = gBattleStatus.partnerActor;

    memset(target, 0, sizeof(*target));
    target->actorID = ACTOR_PARTNER;
    target->partID = 1;
    target->truePos.x = (s32) partner->curPos.x + 10;
    target->truePos.y = (s32) partner->curPos.y + 32;
    target->priorityOffset = -100;
}

static void ph_on_target_list_append(IEvent* event) {
    OnTargetListAppend* ev = (OnTargetListAppend*) event;
    BattleStatus* battleStatus = &gBattleStatus;
    s32 noTargetFlag = false;

    if (gBattleState != BATTLE_STATE_SELECT_TARGET) {
        return;
    }
    TTYD64_HealingItem_Bool[0] = 1;
    if (TTYD64_GetPartnerHP() <= 0 || battleStatus->partnerActor == nullptr) {
        return;
    }
    if (battleStatus->flags1 & BS_FLAGS1_PLAYER_IN_BACK) {
        if ((u8) battleStatus->curPartnerSubmenu != BTL_MENU_TYPE_ITEMS) {
            return;
        }
    } else if ((u8) battleStatus->curSubmenu == BTL_MENU_TYPE_STAR_POWERS) {
        if ((u8) MovesCursorPos != PH_STAR_POWER_POS_REFRESH && (u8) MovesCursorPos != PH_STAR_POWER_POS_SMOOCH) {
            return;
        }
        noTargetFlag = true;
    } else if ((u8) battleStatus->curSubmenu != BTL_MENU_TYPE_ITEMS) {
        return;
    }
    if (*ev->count >= ev->capacity) {
        return;
    }
    ph_add_partner_target(&ev->list[*ev->count]);
    *ev->count += 1;
    if (!noTargetFlag) {
        battleStatus->curTargetListFlags |= TARGET_FLAG_SELECT_ONE;
    }
}

static void ph_on_target_list_cursor(IEvent* event) {
    OnTargetListCursor* ev = (OnTargetListCursor*) event;
    BattleStatus* battleStatus = &gBattleStatus;

    if (TTYD64_HealingItem_Bool[0] != 0 && TTYD64_GetPartnerHP() > 0) {
        if (battleStatus->flags1 & BS_FLAGS1_PLAYER_IN_BACK) {
            if ((u8) battleStatus->curPartnerSubmenu == BTL_MENU_TYPE_ITEMS && !TTYD64_MarioInFront) {
                *ev->index = 1;
            }
        } else {
            if ((u8) battleStatus->curSubmenu == BTL_MENU_TYPE_ITEMS && TTYD64_MarioInFront) {
                *ev->index = 1;
            }
        }
    }
    TTYD64_HealingItem_Bool[0] = 0;
}

static void ph_on_mystery_item_target(IEvent* event) {
    OnMysteryItemTarget* ev = (OnMysteryItemTarget*) event;

    if (gBattleStatus.flags1 & BS_FLAGS1_PLAYER_IN_BACK) {
        *ev->actor = gBattleStatus.partnerActor;
    }
}

static b32 ph_kooper_flip_counting(void) {
    return (u8) gPlayerData.curPartner == PARTNER_KOOPER && TTYD64_PartnerRec(PARTNER_KOOPER)->flipCountdown != 0;
}

static void ph_skip_partner_turn(s32* skip) {
    switch (gBattleState) {
        case BATTLE_STATE_NEXT_ENEMY:
            if (TTYD64_GetPartnerHP() == 0) {
                *skip = true;
            } else if (ph_kooper_flip_counting()) {
                gBattleStatus.flags2 |= BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;
                *skip = true;
            }
            break;
        case BATTLE_STATE_BEGIN_TURN:
            if (TTYD64_GetPartnerHP() == 0) {
                *skip = true;
            } else if ((u8) gPlayerData.curPartner == PARTNER_KOOPER) {
                if (TTYD64_PartnerRec(PARTNER_KOOPER)->flipCountdown != 0) {
                    *skip = true;
                } else if (TTYD64_PartnerRec(PARTNER_KOOPER)->flipped != 0) {
                    TTYD64_PartnerRec(PARTNER_KOOPER)->flipped = 0;
                    *skip = true;
                }
            }
            break;
        case BATTLE_STATE_TRANSFER_TURN:
        case BATTLE_STATE_RUN_AWAY:
            if (TTYD64_GetPartnerHP() == 0 || ph_kooper_flip_counting()) {
                *skip = true;
            }
            break;
    }
}

static void ph_on_turn_order(IEvent* event) {
    OnTurnOrder* ev = (OnTurnOrder*) event;
    BattleStatus* battleStatus = &gBattleStatus;

    switch (ev->decision) {
        case TURN_ORDER_SKIP_PARTNER_TURN:
            ph_skip_partner_turn(ev->value);
            break;
        case TURN_ORDER_FLEE_ENDS_TEAM_TURN:
        case TURN_ORDER_PLAYER_IN_FRONT:
            if (gBattleState != BATTLE_STATE_RUN_AWAY) {
                break;
            }
            if (TTYD64_GetPartnerHP() == 0 || ph_kooper_flip_counting()) {
                break;
            }
            if (battleStatus->flags2 & (BS_FLAGS2_PLAYER_TURN_USED | BS_FLAGS2_PARTNER_TURN_USED)) {
                break;
            }
            if (ev->decision == TURN_ORDER_FLEE_ENDS_TEAM_TURN) {
                *ev->value = false;
            } else {
                *ev->value = (battleStatus->flags1 & BS_FLAGS1_PLAYER_IN_BACK) != 0;
            }
            break;
    }
}

static void ph_on_actor_defeat_check(IEvent* event) {
    OnActorDefeatCheck* ev = (OnActorDefeatCheck*) event;

    if ((ev->actor->actorID & ACTOR_CLASS_MASK) != ACTOR_CLASS_PARTNER) {
        return;
    }
    memset(TTYD64_ActorDead, 0, sizeof(TTYD64_ActorDead));
    *ev->defeated = TTYD64_GetPartnerHP() == 0 && ev->actor->rot.x == 0.0f;
}

enum {
    PH_DEFEAT_CHECK_LIFE_SHROOM = 1,
    PH_DEFEAT_AWAIT_LIFE_SHROOM = 2,
    PH_DEFEAT_DONE = 10,
};

static void ph_update_defeat_player(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    Actor* partner = battleStatus->partnerActor;
    Evt* script;

    switch (gBattleSubState) {
        case BTL_SUBSTATE_INIT:
            battleStatus->flags1 &= ~BS_FLAGS1_SHOW_PLAYER_DECORATIONS;
            gBattleStatus.flags2 &= ~BS_FLAGS2_PLAYER_TURN_USED;
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER;
            gBattleStatus.flags2 &= ~BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER;
            battleStatus->stateFreezeCount = 0;

            if (player->debuff != 0) {
                if (player->debuff == STATUS_KEY_FROZEN) {
                    sfx_play_sound(SOUND_FROZEN_SHATTER);
                    player->icePillarEffect->flags |= FX_INSTANCE_FLAG_DISMISS;
                    player->icePillarEffect = nullptr;
                }
                player->debuff = 0;
                player->debuffDuration = 0;
                remove_status_debuff(player->hudElementDataIndex);
                player->koStatus = 0;
                player->koDuration = 0;
                player->disableEffect->data.disableX->koDuration = 0;
            }

            btl_cam_use_preset(BTL_CAM_PLAYER_FLEE);
            btl_cam_target_actor(ACTOR_PLAYER);

            battleStatus->battlePhase = PHASE_DEATH;
            script = start_script(&EVS_Mario_HandlePhase, EVT_PRIORITY_A, 0);
            player->takeTurnScript = script;
            player->takeTurnScriptID = script->id;
            script->owner1.actorID = ACTOR_PLAYER;

            if (partner != nullptr) {
                script = start_script(partner->takeTurnSource, EVT_PRIORITY_A, 0);
                partner->takeTurnScript = script;
                partner->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PARTNER;
            }
            gBattleSubState = PH_DEFEAT_CHECK_LIFE_SHROOM;
            break;
        case PH_DEFEAT_CHECK_LIFE_SHROOM:
            if (does_script_exist(player->takeTurnScriptID) || battleStatus->stateFreezeCount != 0) {
                break;
            }
            if (find_item(ITEM_LIFE_SHROOM) >= 0) {
                battleStatus->battlePhase = PHASE_USE_LIFE_SHROOM;
                script = start_script(&EVS_Mario_HandlePhase, EVT_PRIORITY_A, 0);
                player->takeTurnScript = script;
                player->takeTurnScriptID = script->id;
                script->owner1.actorID = ACTOR_PLAYER;
                gBattleSubState = PH_DEFEAT_AWAIT_LIFE_SHROOM;
            } else {
                gBattleSubState = PH_DEFEAT_DONE;
            }
            break;
        case PH_DEFEAT_AWAIT_LIFE_SHROOM:
            if (does_script_exist(player->takeTurnScriptID) || battleStatus->stateFreezeCount != 0) {
                break;
            }
            gBattleSubState = PH_DEFEAT_DONE;
            break;
    }

    if (gBattleSubState == PH_DEFEAT_DONE) {
        gCurrentEncounter.battleOutcome = OUTCOME_PLAYER_LOST;
        if (!(gBattleStatus.flags2 & BS_FLAGS2_DONT_STOP_MUSIC)) {
            bgm_set_song(0, -1, 0, 1500, 8);
        }
        btl_set_state(BATTLE_STATE_END_BATTLE);
    }
}

static void ph_update_defeat_partner(void) {
    Actor* partner = gBattleStatus.partnerActor;

    if (partner->handleEventScript == nullptr) {
        dispatch_event_partner(EVENT_DEATH);
        return;
    }
    if (does_script_exist_by_ref(partner->handleEventScript)) {
        return;
    }
    kill_script(partner->handleEventScript);
    partner->handleEventScript = nullptr;
    partner->handleEventScriptID = 0;
    btl_set_state(gDefeatedBattleState);
    if ((u8) gBattleStatus.battlePhase == PHASE_FIRST_STRIKE) {
        gBattleSubState = 2;
    } else {
        gBattleSubState = 0x1E;
    }
}

static void ph_defeat_update(void) {
    s32 hp;

    if (gPlayerData.curHP == 0) {
        memset(TTYD64_ActorDead, 0, sizeof(TTYD64_ActorDead));
        TTYD64_ActorDead[0] = 1;
        ph_update_defeat_player();
        return;
    }
    hp = TTYD64_GetPartnerHP();
    if (hp == 0) {
        memset(TTYD64_ActorDead, 0, sizeof(TTYD64_ActorDead));
        TTYD64_ActorDead[1] = 1;
        ph_update_defeat_partner();
        return;
    }
    if (TTYD64_ActorDead[0] != 0) {
        ph_update_defeat_player();
    } else if (TTYD64_ActorDead[1] != 0) {
        ph_update_defeat_partner();
    }
}

static const ModBattleStateOps sDefeatStateOps = {
    .update = ph_defeat_update,
};

static void ph_partner_list_provider(const BattleMenuContext* ctx, BattleMenuList* list) {
    s32 i;

    for (i = 0; i < BattleMenu_Count(list); i++) {
        BattleMenuEntry* entry = BattleMenu_At(list, i);

        if (TTYD64_ModBytes()[TTYD64_MB_GameMode] == 1 || TTYD64_GetPartnerHP_byID(entry->userIndex) == 0) {
            entry->icon = PartnerHudScripts[entry->userIndex].disabled;
            entry->enabled = false;
        }
    }
}

static void ph_partner_items_selected(const BattleMenuContext* ctx, const BattleMenuEntry* entry) {
    gBattleStatus.selectedMoveID = 0;
}

static void ph_partner_wheel_provider(const BattleMenuContext* ctx, BattleMenuList* list) {
    BattleStatus* battleStatus = &gBattleStatus;
    BattleMenuEntry* entry;
    s32 index;

    if (ctx->who != ACTOR_PARTNER) {
        return;
    }
    index = BattleMenu_FindType(list, BTL_MENU_TYPE_PARTNER_FOCUS);
    if (index >= 0) {
        BattleMenu_Remove(list, index);
    }
    entry = BattleMenu_Insert(list, 2);
    if (entry == nullptr) {
        return;
    }
    entry->menuType = BTL_MENU_TYPE_ITEMS;
    entry->enabled = true;
    entry->errorMsg = 0;
    entry->icon = ItemsHudScripts.enabled;
    entry->nameMsg = 0x1D0050;
    entry->onSelect = ph_partner_items_selected;
    if (get_consumables_count() == 0 || !(battleStatus->enabledMenusFlags & BTL_MENU_ENABLED_ITEMS)
        || battleStatus->itemLossTurns != -1)
    {
        entry->enabled = false;
        entry->icon = ItemsHudScripts.disabled;
        entry->errorMsg = 0x48;
    }
    if (battleStatus->lastPartnerMenuSelection[BTL_MENU_IDX_MAIN] == BTL_MENU_TYPE_ITEMS) {
        BattleMenu_SetInitial(list, 2);
    }
}

static void ph_on_swap_refused(IEvent* event) {
    OnSwapRefused* ev = (OnSwapRefused*) event;

    if (*ev->msgIndex == 0x50 && TTYD64_GetPartnerHP() <= 0) {
        *ev->msgIndex = 0x100;
    }
}

static void ph_on_target_name(IEvent* event) {
    OnTargetName* ev = (OnTargetName*) event;
    s32 move;

    if (TTYD64_GetPartnerHP() <= 0 || gBattleStatus.moveCategory != BTL_MENU_TYPE_STAR_POWERS) {
        return;
    }
    move = (u16) gBattleStatus.selectedMoveID;
    if (move == MOVE_REFRESH || move == MOVE_SMOOCH) {
        *ev->msgID = TTYD64_ph_InlineMsg(TTYD64_String_MarioAndPartner);
    }
}

static void ph_on_level_up_recover(IEvent* event) {
    OnActorHpChange* ev = (OnActorHpChange*) event;
    Actor* partner;
    s32 maxHP;
    s32 x, y, z;

    if (ev->source != HP_SOURCE_LEVEL_UP) {
        return;
    }
    if (TTYD64_GetPartnerHP() < 0) {
        return;
    }
    partner = gBattleStatus.partnerActor;
    maxHP = TTYD64_GetPartnerMaxHP();
    TTYD64_SetPartnerHP(maxHP);
    if (partner == nullptr) {
        return;
    }
    x = partner->curPos.x + 0.0f;
    y = partner->curPos.y + 35.0f;
    z = partner->curPos.z;
    fx_recover(0, x, y, z, maxHP);
}

void TTYD64_InstallPartnerHPBattle(void) {
    REGISTER_LISTENER(OnGuardCheck, EVENT_PRIORITY_LOW, ph_on_guard_check);
    REGISTER_LISTENER(OnActorHpChange, EVENT_PRIORITY_NORMAL, ph_on_actor_hp_change);
    REGISTER_LISTENER(OnActorHpChange, EVENT_PRIORITY_NORMAL, ph_on_level_up_recover);
    REGISTER_LISTENER(OnDamageEventDispatch, EVENT_PRIORITY_LOW, ph_on_damage_event_dispatch);
    REGISTER_LISTENER(OnActorDefeatCheck, EVENT_PRIORITY_NORMAL, ph_on_actor_defeat_check);
    REGISTER_LISTENER(OnSetTargetActor, EVENT_PRIORITY_NORMAL, ph_on_set_target_actor);
    REGISTER_LISTENER(OnTargetListAppend, EVENT_PRIORITY_NORMAL, ph_on_target_list_append);
    REGISTER_LISTENER(OnTargetListCursor, EVENT_PRIORITY_NORMAL, ph_on_target_list_cursor);
    REGISTER_LISTENER(OnMysteryItemTarget, EVENT_PRIORITY_NORMAL, ph_on_mystery_item_target);
    REGISTER_LISTENER(OnTurnOrder, EVENT_PRIORITY_NORMAL, ph_on_turn_order);
    REGISTER_LISTENER(OnSwapRefused, EVENT_PRIORITY_NORMAL, ph_on_swap_refused);
    REGISTER_LISTENER(OnTargetName, EVENT_PRIORITY_NORMAL, ph_on_target_name);
    Mod_ReplaceBattleState("TTYD64", BATTLE_STATE_DEFEAT, &sDefeatStateOps);
    Mod_AddBattleMenuEntries("TTYD64", BATTLE_MENU_PARTNER_LIST, ph_partner_list_provider);
    Mod_AddBattleMenuEntries("TTYD64", BATTLE_MENU_WHEEL, ph_partner_wheel_provider);
    Mod_ReplaceScript("TTYD64", &EVS_Partner_SpikeContact, &TTYD64_ph_EVS_Partner_SpikeContact);
    Mod_ReplaceScript("TTYD64", &EVS_Partner_BurnContact, &TTYD64_ph_EVS_Partner_BurnContact);
    Mod_ReplaceScript("TTYD64", &EVS_UseLifeShroom, &TTYD64_ph_EVS_UseLifeShroom);
    Mod_ReplaceScript("TTYD64", &EVS_Partner_RunAway, &TTYD64_ph_EVS_Partner_RunAway);
}
