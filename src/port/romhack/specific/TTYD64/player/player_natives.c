#include "common.h"
#include "effects.h"
#include "hud_element.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "player_internal.h"

extern HudScript HES_Refund;
extern b32 DidChillOutHit;
extern ActorBlueprint battle_partner_bow;
extern ActorBlueprint TTYD64_battle_partner_bow;

API_CALLABLE(battle_item_mystery_func_802A13E4_72C994);

static HudElemID sRefundHID;
static EffectInstance* sTattleWindow;
static EffectInstance* sSquirtEffect;

static s32 sWattFX_initialized;
static s32 sWattFX_isBouncing;
static s32 sWattFX_bouncePhase;
static s32 sWattFX_isActive;
static s32 sWattFX_currentEffectIndex;
static EffectInstance* sWattFX_effect1;
static EffectInstance* sWattFX_effect2;

static TTYD64MoveScratch sMoveScratch[TTYD64_MSI_COUNT];

static TTYD64MoveScratch* move_scratch(s32 id) {
    if (id < 0 || id >= TTYD64_MSI_COUNT) {
        return nullptr;
    }
    return &sMoveScratch[id];
}

API_CALLABLE(TTYD64_GetMoveScratch) {
    Bytecode* args = script->ptrReadPos;
    TTYD64MoveScratch* scratch = move_scratch(evt_get_variable(script, *args++));
    s32 slot = evt_get_variable(script, *args++);
    s32 value = 0;

    if (scratch != nullptr) {
        switch (slot) {
            case TTYD64_MS_FLAG:
                value = scratch->flag;
                break;
            case TTYD64_MS_RESULT:
                value = scratch->result;
                break;
            case TTYD64_MS_THREAD:
                value = scratch->threadID;
                break;
        }
    }
    evt_set_variable(script, *args++, value);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetMoveScratch) {
    Bytecode* args = script->ptrReadPos;
    TTYD64MoveScratch* scratch = move_scratch(evt_get_variable(script, *args++));
    s32 slot = evt_get_variable(script, *args++);
    s32 value = evt_get_variable(script, *args++);

    if (scratch == nullptr) {
        return ApiStatus_DONE2;
    }
    switch (slot) {
        case TTYD64_MS_FLAG:
            scratch->flag = value;
            break;
        case TTYD64_MS_RESULT:
            scratch->result = value;
            break;
        case TTYD64_MS_THREAD:
            scratch->threadID = value;
            break;
    }
    return ApiStatus_DONE2;
}

static void reset_move_scratch(s32 id) {
    sMoveScratch[id] = (TTYD64MoveScratch) { 0 };
}

static void move_scratch_on_battle_script_load(IEvent* event) {
    OnBattleScriptLoad* ev = (OnBattleScriptLoad*) event;

    if (ev->kind != BATTLE_SCRIPT_LOAD_MOVE) {
        return;
    }
    switch (ev->id) {
        case MOVE_AUTO_MULTIBOUNCE:
            reset_move_scratch(TTYD64_MSI_AUTO_MULTIBOUNCE);
            break;
        case MOVE_EARTHQUAKE_JUMP:
            reset_move_scratch(TTYD64_MSI_EARTHQUAKE_JUMP);
            break;
        case MOVE_SMASH_CHARGE:
        case MOVE_UNUSED_HAMMER_10:
            reset_move_scratch(TTYD64_MSI_HAMMER_CHARGE_1);
            break;
    }
}

static void move_scratch_on_actor_blueprint_load(IEvent* event) {
    OnActorBlueprintLoad* ev = (OnActorBlueprintLoad*) event;

    if (*ev->blueprint == &battle_partner_bow || *ev->blueprint == &TTYD64_battle_partner_bow) {
        reset_move_scratch(TTYD64_MSI_BOW);
    }
}

void TTYD64_Player_InstallMoveScratch(void) {
    REGISTER_LISTENER(OnBattleScriptLoad, EVENT_PRIORITY_LOW, move_scratch_on_battle_script_load);
    REGISTER_LISTENER(OnActorBlueprintLoad, EVENT_PRIORITY_LOW, move_scratch_on_actor_blueprint_load);
}

API_CALLABLE(TTYD64_Player_Refund) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    s32 sellValue = gItemTable[battleStatus->moveArgument].sellValue;
    Actor* actor = get_actor(script->owner1.actorID);
    f32 posY = actor->curPos.y + actor->size.y;
    f32 angle = 0.0f;
    s32 copies = player_team_is_ability_active(player, ABILITY_REFUND);
    s32 delayTime = 0;
    s32 iconX;
    s32 iconY;
    s32 iconZ;
    s32 i;

    if (copies == 0) {
        script->varTable[0] = 0;
        return ApiStatus_DONE2;
    }
    if (sellValue > 0) {
        sellValue = (sellValue * 75 + 99) / 100;
        i = 0;
        if (i < sellValue) {
            sellValue *= copies;
            delayTime = 1;
            do {
                make_item_entity(
                    ITEM_COIN, actor->curPos.x, posY, actor->curPos.z, ITEM_SPAWN_MODE_TOSS_FADE1, delayTime, angle, 0
                );
                delayTime += 3;
                i++;
                angle += 30.0f;
                add_coins(1);
            } while (i < sellValue);
        }
        delayTime = i * 3 + 30;
        get_screen_coords(gCurrentCameraID, actor->curPos.x, actor->curPos.y, actor->curPos.z, &iconX, &iconY, &iconZ);
        sRefundHID = hud_element_create(&HES_Refund);
        hud_element_set_render_pos(sRefundHID, iconX + 36, iconY - 63);
    }
    script->varTable[0] = delayTime;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_Refund_FreeIcons) {
    BattleStatus* battleStatus = &gBattleStatus;
    s32 sellValue = gItemTable[battleStatus->moveArgument].sellValue;

    if (player_team_is_ability_active(battleStatus->playerActor, ABILITY_REFUND) && sellValue > 0) {
        hud_element_free(sRefundHID);
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_starpower4_802A16F4) {
    Actor* enemy = get_actor(script->owner1.enemyID);
    Actor* target = get_actor(enemy->targetActorID);
    ActorPart* targetPart = get_actor_part(target, enemy->targetPartID);
    f32 x, y, z;

    if (target->flags & ACTOR_FLAG_TARGET_ONLY) {
        return ApiStatus_DONE2;
    }
    if (target->flags & ACTOR_FLAG_NO_DMG_APPLY) {
        return ApiStatus_DONE2;
    }
    if (target->flags & ACTOR_FLAG_DAMAGE_IMMUNE) {
        return ApiStatus_DONE2;
    }
    if (targetPart->eventFlags & ACTOR_EVENT_FLAG_ENCHANTED) {
        return ApiStatus_DONE2;
    }
    if (targetPart->eventFlags & ACTOR_EVENT_FLAG_STAR_ROD_ENCHANTED) {
        return ApiStatus_DONE2;
    }

    dispatch_damage_event_actor_0(target, 0, EVENT_HIT);

    x = target->curPos.x + target->headOffset.x + (target->size.x / 2);
    if (target->flags & ACTOR_FLAG_UPSIDE_DOWN) {
        y = target->curPos.y + target->headOffset.y - target->size.y;
    } else if (!(target->flags & ACTOR_FLAG_HALF_HEIGHT)) {
        y = target->curPos.y + target->headOffset.y + target->size.y;
    } else {
        y = target->curPos.y + target->headOffset.y + target->size.y * 2;
    }
    z = target->curPos.z + target->headOffset.z + 5.0f;

    fx_stat_change(5, x, y, z, 1.0f, 60);
    sfx_play_sound(SOUND_INFLICT_CHILL_OUT);
    DidChillOutHit = true;
    return ApiStatus_DONE2;
}

static void clear_debuffs(Evt* script, b32 dispatchRecover) {
    Actor* actor = get_actor(evt_get_variable(script, *script->ptrReadPos));
    s32 actorClass = actor->actorID & ACTOR_CLASS_MASK;
    TTYD64BattleRec* rec;

    if (actor->debuff != 0) {
        actor->debuffDuration = 0;
        actor->debuff = 0;
        remove_status_debuff(actor->hudElementDataIndex);
    }
    if (actor->koStatus != 0) {
        actor->koDuration = 0;
        actor->koStatus = 0;
        if (actorClass == ACTOR_CLASS_PARTNER) {
            rec = TTYD64_CurPartnerRec();
            if (rec != nullptr) {
                rec->debuffKey = 0;
                rec->debuffTurns = 0;
            }
            if (dispatchRecover) {
                dispatch_event_partner(EVENT_RECOVER_STATUS);
            }
        }
        actor->disableEffect->data.disableX->koDuration = 0;
    }
}

API_CALLABLE(TTYD64_Player_item13_ClearDebuffs) {
    clear_debuffs(script, true);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_item17_ClearDebuffs) {
    clear_debuffs(script, true);
    btl_update_ko_status();
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_starpower1_ClearDebuffs) {
    clear_debuffs(script, false);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_item29_ElectroPop_Heal_Enemies) {
    script->varTable[3] = gItemTable[ITEM_ELECTRO_POP].potencyB;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_item30_KookyCookie_Heal_Enemies) {
    script->varTable[3] = gItemTable[ITEM_KOOKY_COOKIE].potencyB;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_partner1_Goombario_TattleCam_Start) {
    TTYD64_FFWD.suppressed = 1;
    sTattleWindow = fx_tattle_window(0, 206.0f, 144.0f, 0.0f, 1.0f, 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_partner1_Goombario_80238E48) {
    EffectInstance* effect;

    TTYD64_FFWD.suppressed = 0;
    effect = sTattleWindow;
    effect->data.tattleWindow->pos.y = 144.0f;
    effect->flags |= FX_INSTANCE_FLAG_DISMISS;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_partner1_Goombario_8023903C) {
    TTYD64BattleRec* rec = TTYD64_CurPartnerRec();

    if (rec != nullptr) {
        rec->charge = 0;
    }
    gBattleStatus.flags1 &= ~BS_FLAGS1_GOOMBARIO_CHARGED;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_partner1_Charge_GetBoosts) {
    TTYD64BattleRec* rec = TTYD64_CurPartnerRec();

    script->varTable[0] = rec != nullptr ? (s8) rec->charge : 0;
    if (rec != nullptr) {
        rec->charge = 0;
    }
    gBattleStatus.flags1 &= ~BS_FLAGS1_GOOMBARIO_CHARGED;
    return ApiStatus_DONE2;
}

void TTYD64_Player_item25_EnemySetTarget(void) {
    Actor* actor;
    s32 itemID;
    s32 targetID;

    if (gBattleState == BATTLE_STATE_ENEMY_MOVE && (u16) gBattleStatus.activeEnemyActorID != 0) {
        actor = get_actor((u16) gBattleStatus.activeEnemyActorID);
        itemID = (u16) gBattleStatus.moveArgument;
        switch (itemID) {
            case ITEM_FIRE_FLOWER:
            case ITEM_DIZZY_DIAL:
            case ITEM_THUNDER_RAGE:
                targetID = 0;
                break;
            default:
                targetID = (u16) actor->actorID;
                break;
        }
        actor->targetActorID = targetID;
    }
}

API_CALLABLE(TTYD64_Player_item25_Mystery_Roulette) {
    ApiStatus status = battle_item_mystery_func_802A13E4_72C994(script, isInitialCall);

    if (status == ApiStatus_DONE2) {
        TTYD64_Player_item25_EnemySetTarget();
    }
    return status;
}

API_CALLABLE(TTYD64_Player_item11_RotateTargets_Start) {
    Actor* actor = (Actor*) evt_get_variable(script, *script->ptrReadPos);
    SelectableTarget* sel;
    Actor* target;
    ActorPart* part;
    s32 i;

    if (isInitialCall) {
        script->functionTemp[0] = 0;
        script->functionTemp[1] = 90;
    }
    for (i = 0; i < actor->targetListLength; i++) {
        sel = &actor->targetData[actor->targetIndexList[i]];
        target = get_actor(sel->actorID);
        part = get_actor_part(target, sel->partID);
        if (target->transparentStatus == 0 && !(part->eventFlags & ACTOR_EVENT_FLAG_ILLUSORY)) {
            target->yaw += 33.0f;
            target->yaw = clamp_angle(target->yaw);
        }
    }
    if (script->functionTemp[1] == 0) {
        return ApiStatus_DONE2;
    }
    script->functionTemp[1]--;
    return ApiStatus_BLOCK;
}

API_CALLABLE(TTYD64_Player_item11_RotateTargets_End) {
    Actor* actor = (Actor*) evt_get_variable(script, *script->ptrReadPos);
    SelectableTarget* sel;
    Actor* target;
    ActorPart* part;
    b32 stillRotating = false;
    f32 yaw;
    s32 i;

    if (isInitialCall) {
        script->functionTemp[0] = 0;
    }
    for (i = 0; i < actor->targetListLength; i++) {
        sel = &actor->targetData[actor->targetIndexList[i]];
        target = get_actor(sel->actorID);
        if (target == nullptr) {
            continue;
        }
        part = get_actor_part(target, sel->partID);
        if (target->transparentStatus != 0 || (part->eventFlags & ACTOR_EVENT_FLAG_ILLUSORY)) {
            continue;
        }
        yaw = target->yaw;
        if (!(yaw < 360.0f)) {
            continue;
        }
        yaw += 33.0f;
        target->yaw = yaw;
        if (360.0f <= yaw) {
            target->yaw = 360.0f;
        }
        stillRotating = true;
    }
    return stillRotating ? ApiStatus_BLOCK : ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_partner4_ParcelCheck_TryToGetRandomItem) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID = evt_get_variable(script, *args++);
    TTYD64EnemyItemRecord* record = TTYD64_get_actor_itemTableData(actorID);
    s32 itemID = ITEM_COIN;
    const TTYD64DropEntry* table;
    s32 count;
    s32 totalWeight;
    s32 weight;
    s32 roll;
    s32 i;

    if (record != nullptr && record->dropTable != 0) {
        table = TTYD64_GetDropTable(record->dropTable, &count);
        if (table != nullptr) {
            totalWeight = 0;
            for (i = 0; i < count; i++) {
                totalWeight += table[i].holdWeight;
            }

            i = count + 1;
            while (true) {
                i--;
                if (i >= count) {
                    break;
                }
                weight = table[i].holdWeight;
                if (weight == 0) {
                    i++;
                    continue;
                }
                roll = rand_int((200 + totalWeight) / weight);
                if (roll == 0) {
                    roll = 1;
                }
                if (roll != 1) {
                    i++;
                    continue;
                }
                if (record->stolen) {
                    break;
                }
                record->stolen = true;
                if (record->origin != TTYD64_EI_ORIGIN_MID_BATTLE) {
                    TTYD64_get_actor_itemTableData_OriginalFormation(actorID)->stolen = true;
                }
                itemID = table[i].itemID;
                break;
            }
        }
    }
    evt_set_variable(script, *args++, itemID);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_partner6_Watt_UpdateSparkles) {
    Actor* partner = gBattleStatus.partnerActor;
    f32 x, y, z;

    if (isInitialCall) {
        sWattFX_isBouncing = true;
        sWattFX_bouncePhase = 0;
        sWattFX_isActive = true;
        sWattFX_currentEffectIndex = 0;
        sWattFX_effect1 = fx_static_status(0, partner->curPos.x, partner->curPos.y, partner->curPos.z, 1.0f, 5, 0);
        sWattFX_effect2 = fx_static_status(1, partner->curPos.x, NPC_DISPOSE_POS_Y, partner->curPos.z, 1.0f, 5, 0);
        sWattFX_initialized = true;
    }

    if (!sWattFX_initialized) {
        return ApiStatus_DONE2;
    }

    if (sWattFX_isBouncing) {
        sWattFX_bouncePhase += 15;
        sWattFX_bouncePhase = clamp_angle(sWattFX_bouncePhase);
    }

    partner->verticalRenderOffset = sin_rad(DEG_TO_RAD(sWattFX_bouncePhase)) * 3.0f;
    x = partner->curPos.x + partner->headOffset.x;
    y = partner->curPos.y + partner->headOffset.y + partner->verticalRenderOffset + 12.0f;
    z = partner->curPos.z + partner->headOffset.z;
    if (!(gBattleStatus.flags2 & BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER)
        && (gBattleStatus.flags2 & BS_FLAGS2_PARTNER_TURN_USED))
    {
        y = NPC_DISPOSE_POS_Y;
    }

    if (gBattleStatus.partnerActor->debuff != STATUS_KEY_POISON && sWattFX_isActive) {
        switch (sWattFX_currentEffectIndex) {
            case 0:
                if (sWattFX_effect1 == nullptr) {
                    sWattFX_effect1 = fx_static_status(0, x, y, z, 1.0f, 5, 0);
                }
                if (sWattFX_effect2 != nullptr) {
                    sWattFX_effect2->flags |= FX_INSTANCE_FLAG_DISMISS;
                    sWattFX_effect2 = nullptr;
                }
                sWattFX_effect1->data.staticStatus->pos.x = x;
                sWattFX_effect1->data.staticStatus->pos.y = y;
                sWattFX_effect1->data.staticStatus->pos.z = z;
                break;
            case 1:
                if (sWattFX_effect1 != nullptr) {
                    sWattFX_effect1->flags |= FX_INSTANCE_FLAG_DISMISS;
                    sWattFX_effect1 = nullptr;
                }
                if (sWattFX_effect2 == nullptr) {
                    sWattFX_effect2 = fx_static_status(1, x, y, z, 1.0f, 5, 0);
                }
                sWattFX_effect2->data.staticStatus->pos.x = x;
                sWattFX_effect2->data.staticStatus->pos.y = y;
                sWattFX_effect2->data.staticStatus->pos.z = z;
                break;
        }
    } else {
        if (sWattFX_effect1 != nullptr) {
            sWattFX_effect1->flags |= FX_INSTANCE_FLAG_DISMISS;
            sWattFX_effect1 = nullptr;
        }
        if (sWattFX_effect2 != nullptr) {
            sWattFX_effect2->flags |= FX_INSTANCE_FLAG_DISMISS;
            sWattFX_effect2 = nullptr;
        }
    }

    return ApiStatus_BLOCK;
}

API_CALLABLE(TTYD64_Player_partner6_WattFXRemove) {
    sWattFX_initialized = false;
    if (sWattFX_effect1 != nullptr) {
        remove_effect(sWattFX_effect1);
    }
    if (sWattFX_effect2 != nullptr) {
        remove_effect(sWattFX_effect2);
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_partner6_WattFXBounce) {
    sWattFX_isBouncing = 1;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_partner6_WattFXDisableBounce) {
    sWattFX_isBouncing = 0;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_partner6_WattFXEnable) {
    sWattFX_isActive = 1;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_partner6_WattFXDisable) {
    sWattFX_isActive = 0;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_partner6_WattFXSetEffect) {
    sWattFX_currentEffectIndex = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Player_partner7_WaterBlock_PlayFX_59) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* partnerActor = battleStatus->partnerActor;
    Actor* playerActor = battleStatus->playerActor;
    s32 r = rand_int(10);
    f32 partnerX = partnerActor->curPos.x;

    if (TTYD64_MarioInFront) {
        partnerX += 12.0f;
    }
    sSquirtEffect = fx_squirt(
        1, partnerX - 5.5, partnerActor->curPos.y + 15.5, partnerActor->curPos.z + 5, playerActor->curPos.x,
        playerActor->curPos.y, playerActor->curPos.z, (r * 0.1) + 1, 30
    );
    return ApiStatus_DONE2;
}
