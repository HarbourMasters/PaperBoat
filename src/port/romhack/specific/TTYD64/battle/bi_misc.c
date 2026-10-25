#include "port/romhack/specific/TTYD64/battle/bi_internal.h"
#include "battle/action_cmd.h"
#include "port/modding/Mod.h"

extern AnimID PartnerThinkAnims[];

static b8 sTornadoJumpHud;

API_CALLABLE(TTYD64_SetTornadoJumpHud) {
    sTornadoJumpHud = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

static void bi_on_attack_status_select(IEvent* event) {
    OnAttackStatusSelect* ev = (OnAttackStatusSelect*) event;
    s32 flags = gBattleStatus.curAttackStatus;

    if (!(flags & (STATUS_FLAG_DIZZY | STATUS_FLAG_SHRINK | STATUS_FLAG_FROZEN))) {
        *ev->status = STATUS_KEY_NORMAL;
    } else if (flags & STATUS_FLAG_SHRINK) {
        *ev->status = STATUS_KEY_SHRINK;
    } else if (flags & STATUS_FLAG_FROZEN) {
        *ev->status = STATUS_KEY_FROZEN;
    } else {
        *ev->status = STATUS_KEY_DIZZY;
    }
}

static void bi_on_action_command_hud_init(IEvent* event) {
    OnActionCommandHudInit* ev = (OnActionCommandHudInit*) event;

    if (ev->actionCommandID != ACTION_COMMAND_TIDAL_WAVE) {
        return;
    }
    if (sTornadoJumpHud) {
        ev->acs->hudPosX += 75;
    }
}

static void bi_on_action_command_next_state(IEvent* event) {
    OnActionCommandNextState* ev = (OnActionCommandNextState*) event;

    if (ev->actionCommandID != ACTION_COMMAND_TIDAL_WAVE) {
        return;
    }
    if (ev->acs->tidalWave.inputCount >= 14) {
        *ev->state = 13;
    }
}

static void bi_on_player_actor_loaded(IEvent* event) {
    OnPlayerActorLoaded* ev = (OnPlayerActorLoaded*) event;

    ev->player->state.goalPos.x = 0.0f;
    ev->player->state.goalPos.y = 0.0f;
    ev->player->state.goalPos.z = 0.0f;
}

static b32 bi_player_inputs_locked(void) {
    return (gPlayerStatus.flags & (PS_FLAG_NO_STATIC_COLLISION | PS_FLAG_INPUT_DISABLED)) != 0;
}

static s32 bi_hp_peril(s32 hp) {
    if (hp <= PERIL_THRESHOLD) {
        return PERIL_STATE_PERIL;
    }
    if (hp <= DANGER_THRESHOLD) {
        return PERIL_STATE_DANGER;
    }
    return PERIL_STATE_NONE;
}

static void bi_on_player_idle_anim(IEvent* event) {
    OnPlayerIdleAnim* ev = (OnPlayerIdleAnim*) event;

    if (bi_player_inputs_locked()) {
        *ev->anim = 0x10002;
    } else if (bi_hp_peril((u8) gPlayerData.curHP) == PERIL_STATE_NONE) {
        *ev->anim = 0x10002;
    } else {
        *ev->anim = 0x10003;
    }
}

static void bi_on_player_idle_tick(IEvent* event) {
    OnPlayerIdleTick* ev = (OnPlayerIdleTick*) event;
    u16 timer = *ev->idleTimer;

    if (gGameStatus.peachFlags != 0) {
        return;
    }
    if (bi_player_inputs_locked()) {
        *ev->idleTimer = 0;
        return;
    }
    if (gPlayerStatus.animFlags & PA_FLAG_8BIT_MARIO) {
        *ev->idleTimer = 0;
        return;
    }
    if (*ev->anim == 0x8001D) {
        return;
    }
    if (bi_hp_peril((u8) gPlayerData.curHP) != PERIL_STATE_NONE) {
        return;
    }
    if (timer == 0x100) {
        *ev->anim = 0x80028;
    } else if (timer == 0x1A0) {
        *ev->anim = 0x80028;
    } else if (timer == 0x19F) {
        *ev->anim = 0x10002;
    } else if (timer == 0x1B5) {
        *ev->anim = 0x8001D;
    }
}

static s32 bi_world_partner_anim(s32 anim) {
    u8 partner;
    s32 hp;

    if (bi_player_inputs_locked()) {
        return anim;
    }
    hp = TTYD64_GetPartnerHP();
    if (hp < 0) {
        return anim;
    }
    partner = gPlayerData.curPartner;
    if (bi_hp_peril(hp) != PERIL_STATE_NONE) {
        switch (partner) {
            case PARTNER_GOOMBARIO:
                return 0x1000C;
            case PARTNER_KOOPER:
                return 0x20015;
            case PARTNER_BOMBETTE:
                return 0x30013;
            case PARTNER_SUSHIE:
                return 0x7000F;
            case PARTNER_PARAKARRY:
                return 0x4000C;
            case PARTNER_BOW:
                return 0x5000E;
            case PARTNER_WATT:
                return 0x6000B;
            case PARTNER_LAKILESTER:
                return 0x8000F;
        }
    }
    if ((u16) gPlayerStatus.curStateTime < 0x1B5) {
        return anim;
    }
    switch (partner) {
        case PARTNER_GOOMBARIO:
            return 0x1000B;
        case PARTNER_KOOPER:
            return 0x20014;
        case PARTNER_BOMBETTE:
            return 0x30012;
        case PARTNER_SUSHIE:
            return 0x7000E;
        case PARTNER_PARAKARRY:
            return 0x4000B;
        case PARTNER_BOW:
            return 0x5000D;
        case PARTNER_WATT:
            return 0x6000A;
        case PARTNER_LAKILESTER:
            return 0x8000E;
    }
    return anim;
}

static s32 bi_battle_partner_menu_anim(s32 anim) {
    s32 hp = TTYD64_GetPartnerHP();

    if (hp < 0) {
        return anim;
    }
    if (bi_hp_peril(hp) == PERIL_STATE_NONE) {
        return anim;
    }
    switch ((u8) gPlayerData.curPartner) {
        case PARTNER_GOOMBARIO:
            return 0x90016;
        case PARTNER_KOOPER:
            return 0xA001F;
        case PARTNER_BOMBETTE:
            return 0xB0020;
        case PARTNER_PARAKARRY:
            return 0xC001C;
        case PARTNER_BOW:
            return 0xD001D;
        case PARTNER_WATT:
            return 0xE0015;
        case PARTNER_SUSHIE:
            return 0xF0016;
        default:
            return 0x10001C;
    }
}

static void bi_on_partner_anim(IEvent* event) {
    OnPartnerAnim* ev = (OnPartnerAnim*) event;

    switch (ev->context) {
        case PARTNER_ANIM_CONTEXT_WORLD_IDLE:
            *ev->anim = bi_world_partner_anim(*ev->anim);
            break;
        case PARTNER_ANIM_CONTEXT_BATTLE_MENU_THINK:
            *ev->anim = bi_battle_partner_menu_anim(*ev->anim);
            break;
        case PARTNER_ANIM_CONTEXT_BATTLE_MENU_CHOSEN:
            *ev->anim = bi_battle_partner_menu_anim(PartnerThinkAnims[gPlayerData.curPartner]);
            break;
    }
}

static b32 bi_partner_defending(void) {
    TTYD64BattleRec* rec = TTYD64_CurPartnerRec();

    return rec != nullptr && rec->defendStack != 0;
}

static s32 bi_partner_normal_anim(ActorPart* part, s32 anim) {
    s32 hp = TTYD64_GetPartnerHP();

    if (hp <= 0) {
        return anim;
    }
    if (bi_partner_defending()) {
        return get_npc_anim_for_status(part->idleAnimations, 0x30);
    }
    if (bi_hp_peril(hp) != PERIL_STATE_NONE) {
        return get_npc_anim_for_status(part->idleAnimations, STATUS_KEY_DANGER);
    }
    return anim;
}

static void bi_on_actor_anim(IEvent* event) {
    OnActorAnim* ev = (OnActorAnim*) event;
    ActorPart* part = ev->part;
    s32 normal;

    if ((u16) ev->actor->actorID == ACTOR_PLAYER) {
        if (TTYD64_ActorRec(ACTOR_PLAYER)->defendStack != 0) {
            *ev->anim = 0x10014;
        }
        return;
    }
    if ((u16) ev->actor->actorID != ACTOR_PARTNER) {
        return;
    }
    switch (ev->statusKey) {
        case STATUS_KEY_INACTIVE:
            if (bi_partner_defending()) {
                *ev->anim = get_npc_anim_for_status(part->idleAnimations, 0x30);
            }
            break;
        case STATUS_KEY_POISON:
        case STATUS_KEY_STATIC:
            if (bi_partner_defending()) {
                normal = get_npc_anim_for_status(part->idleAnimations, STATUS_KEY_NORMAL);
                *ev->anim = bi_partner_normal_anim(part, normal);
            }
            break;
        case STATUS_KEY_NORMAL:
            *ev->anim = bi_partner_normal_anim(part, *ev->anim);
            break;
        case STATUS_KEY_KO:
            normal = get_npc_anim_for_status(part->idleAnimations, STATUS_KEY_NORMAL);
            *ev->anim = normal == *ev->anim ? normal : part->curAnimation;
            break;
    }
}

static void bi_on_peril_state(IEvent* event) {
    OnPerilState* ev = (OnPerilState*) event;
    s32 hp;
    s32 peril;

    if ((u16) ev->actor->actorID != ACTOR_PARTNER) {
        return;
    }
    hp = TTYD64_GetPartnerHP();
    if (hp <= 0) {
        return;
    }
    peril = bi_hp_peril(hp);
    if (peril > *ev->peril) {
        *ev->peril = peril;
    }
}

static void bi_on_status_icon_draw(IEvent* event) {
    OnStatusIconDraw* ev = (OnStatusIconDraw*) event;
    u32 threshold = (ev->icon == STATUS_ICON_PERIL) ? 2 : 6;
    s32 x = *ev->x - 2;
    s32 partnerX = 0;
    s32 partnerInDanger = 0;
    s32 marioInDanger;
    Actor* partner = gBattleStatus.partnerActor;
    s32 hp = partner != nullptr ? TTYD64_GetPartnerHP() : 0;

    if (hp > 0) {
        s32 screenX;
        s32 screenY;
        s32 screenZ;

        partnerInDanger = (u32) hp < threshold;
        get_screen_coords(
            gCurrentCameraID, partner->curPos.x, ev->anchor->y, partner->curPos.y, &screenX, &screenY, &screenZ
        );
        partnerX = screenX;
    }
    marioInDanger = (u32) (u8) gPlayerData.curHP < threshold;

    if (partnerInDanger + marioInDanger == 2) {
        x = 0x39;
    } else if (partnerInDanger) {
        x = partnerX + 2;
    } else if (marioInDanger) {
        x = x + 2;
    }
    *ev->x = x;
}

static void bi_on_battle_celebration(IEvent* event) {
    OnBattleCelebration* ev = (OnBattleCelebration*) event;
    BattleCelebration* c = ev->celebration;

    switch (ev->phase) {
        case BATTLE_CELEBRATION_AWARD:
            if (c->starPoints == 0 && (u8) gPlayerData.level < 67) {
                c->starPoints = 1;
            }
            break;
        case BATTLE_CELEBRATION_JINGLE:
            if (evt_get_variable(nullptr, TTYD64_ModByte(TTYD64_MB_Byte_Settings_BGM)) == 0) {
                event->Cancelled = true;
            }
            break;
        case BATTLE_CELEBRATION_WALK_OFF_BEGIN:
            c->walkOffAnim = 0x10004;
            break;
        case BATTLE_CELEBRATION_WALK_OFF_STEP:
            c->playerStepX = 0.0f;
            c->partnerStepX = 0.0f;
            break;
    }
}

static void bi_on_star_point_drop(IEvent* event) {
    OnStarPointDrop* ev = (OnStarPointDrop*) event;

    if (*ev->level >= 27) {
        *ev->level = 67;
    }
}

static void bi_on_stat_limits(IEvent* event) {
    OnStatLimits* ev = (OnStatLimits*) event;
    StatLimits* limits = ev->limits;

    limits->levelCap = 67;
    limits->hpCap = 99;
    limits->fpCap = 99;
    limits->bpCap = 99;
    limits->levelUpHpFpCap = 95;
    limits->levelUpHpFpClamp = 99;
}

static void bi_on_effect_spawn_params(IEvent* event) {
    OnEffectSpawnParams* ev = (OnEffectSpawnParams*) event;

    if (ev->effectID != EFFECT_FIRE_FLOWER || ev->param != EFFECT_PARAM_FIRE_FLOWER_SPEED_X) {
        return;
    }
    if ((u8) gGameStatus.context != CONTEXT_BATTLE) {
        return;
    }
    if (gBattleState != BATTLE_STATE_ENEMY_MOVE) {
        return;
    }
    *ev->value = -8.0f;
}

static void bi_on_stat_change_glyph(IEvent* event) {
    OnStatChangeEffectGlyph* ev = (OnStatChangeEffectGlyph*) event;
    s32 idx = (ev->amount < 0) ? -ev->amount : ev->amount;

    if ((u32) idx < 10) {
        return;
    }
    *ev->glyph = ((u32) idx / 10) % 10;
}

static void bi_star_spirits_provider(const BattleMenuContext* ctx, BattleMenuList* list) {
    s32 index;

    if (ctx->who != ACTOR_PLAYER || ctx->submenu != BTL_MENU_TYPE_STAR_POWERS) {
        return;
    }
    index = BattleMenu_FindMove(list, MOVE_FOCUS);
    if (index >= 0) {
        BattleMenu_Remove(list, index);
    }
}

static void bi_on_badge_inventory_full(IEvent* event) {
    OnBadgeInventoryFull* ev = (OnBadgeInventoryFull*) event;

    if (gGameStatus.context == CONTEXT_WORLD) {
        show_merlee_message(0x107, 60);
        TTYD64_add_badge_to_sold_inventory(ev->badgeID);
        make_item_entity_nodelay(
            ev->badgeID, gGameStatus.playerPos.x, gGameStatus.playerPos.y, gGameStatus.playerPos.z, 0x17, 0
        );
    }
    *ev->result = -1;
}

static void bi_on_ability_effect(IEvent* event) {
    OnAbilityEffect* ev = (OnAbilityEffect*) event;

    if (ev->ability == ABILITY_ALL_OR_NOTHING) {
        *ev->value = 1;
    }
}

static void bi_on_bgm_song(IEvent* event) {
    OnBgmSong* ev = (OnBgmSong*) event;
    s32 song = *ev->songID;

    if (song == 0x69) {
        *ev->songID = 0xA5;
        return;
    }
    if (song == 0x6A) {
        *ev->songID = 0xA4;
        return;
    }
    if (evt_get_variable(nullptr, TTYD64_ModByte(TTYD64_MB_Byte_Settings_BGM)) != 0) {
        return;
    }
    switch (song) {
        case 0x2:
            *ev->songID = 0xA0;
            break;
        case 0x3:
            *ev->songID = 0xA1;
            break;
        case 0x8B:
            *ev->songID = 0xA2;
            break;
        case 0x8E:
            *ev->songID = 0xA3;
            break;
    }
}

void TTYD64_InstallBattleItemsMisc(void) {
    REGISTER_LISTENER(OnAttackStatusSelect, EVENT_PRIORITY_NORMAL, bi_on_attack_status_select);
    REGISTER_LISTENER(OnActionCommandHudInit, EVENT_PRIORITY_NORMAL, bi_on_action_command_hud_init);
    REGISTER_LISTENER(OnActionCommandNextState, EVENT_PRIORITY_NORMAL, bi_on_action_command_next_state);
    REGISTER_LISTENER(OnPlayerActorLoaded, EVENT_PRIORITY_NORMAL, bi_on_player_actor_loaded);
    REGISTER_LISTENER(OnPlayerIdleTick, EVENT_PRIORITY_NORMAL, bi_on_player_idle_tick);
    REGISTER_LISTENER(OnPlayerIdleAnim, EVENT_PRIORITY_NORMAL, bi_on_player_idle_anim);
    REGISTER_LISTENER(OnPartnerAnim, EVENT_PRIORITY_NORMAL, bi_on_partner_anim);
    REGISTER_LISTENER(OnActorAnim, EVENT_PRIORITY_HIGH, bi_on_actor_anim);
    REGISTER_LISTENER(OnPerilState, EVENT_PRIORITY_HIGH, bi_on_peril_state);
    REGISTER_LISTENER(OnStatusIconDraw, EVENT_PRIORITY_NORMAL, bi_on_status_icon_draw);
    REGISTER_LISTENER(OnBattleCelebration, EVENT_PRIORITY_NORMAL, bi_on_battle_celebration);
    REGISTER_LISTENER(OnStatLimits, EVENT_PRIORITY_HIGH, bi_on_stat_limits);
    REGISTER_LISTENER(OnStarPointDrop, EVENT_PRIORITY_NORMAL, bi_on_star_point_drop);
    REGISTER_LISTENER(OnEffectSpawnParams, EVENT_PRIORITY_HIGH, bi_on_effect_spawn_params);
    REGISTER_LISTENER(OnStatChangeEffectGlyph, EVENT_PRIORITY_NORMAL, bi_on_stat_change_glyph);
    Mod_AddBattleMenuEntries("TTYD64", BATTLE_MENU_MOVES, bi_star_spirits_provider);
    REGISTER_LISTENER(OnBadgeInventoryFull, EVENT_PRIORITY_NORMAL, bi_on_badge_inventory_full);
    REGISTER_LISTENER(OnAbilityEffect, EVENT_PRIORITY_NORMAL, bi_on_ability_effect);
    REGISTER_LISTENER(OnBgmSong, EVENT_PRIORITY_HIGH, bi_on_bgm_song);
}
