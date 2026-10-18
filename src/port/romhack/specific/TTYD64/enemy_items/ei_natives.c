#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "enemy_items_internal.h"

extern s32 ItemKeys[];
extern BattleMoveEntry gBattleItemTable[];

EvtScript* TTYD64_Stack_TakeTurnScript = NULL;
u8 TTYD64_PierceDefenseFlag[1] = { 0 };

static TTYD64EnemyItemRecord sEnemiesItemsBattleData[TTYD64_EI_ITEM_TABLE_RECORDS];
static TTYD64EnemyItemRecord sEnemiesItemsBattleData_OriginalFormation[TTYD64_EI_ITEM_TABLE_RECORDS];

s32 TTYD64_EI_HeldItem(Actor* actor) {
    TTYD64BattleRec* rec = TTYD64_ActorRec(actor->actorID);

    return rec != NULL ? (u16) rec->heldItem : ITEM_NONE;
}

b32 TTYD64_EI_HasHeldItemData(Actor* actor) {
    TTYD64BattleRec* rec = TTYD64_ActorRec(actor->actorID);

    return rec != NULL && (rec->heldItem != ITEM_NONE || rec->heldItemEntity != 0);
}

void TTYD64_EI_SetHeldItem(Actor* actor, s32 itemID, s32 entityIndex) {
    TTYD64BattleRec* rec = TTYD64_ActorRec(actor->actorID);

    if (rec != NULL) {
        rec->heldItem = itemID;
        rec->heldItemEntity = entityIndex;
    }
}

s32 TTYD64_EI_GetItemEntityIndex(Actor* actor) {
    TTYD64BattleRec* rec = TTYD64_ActorRec(actor->actorID);

    return rec != NULL ? rec->heldItemEntity : 0;
}

s32 TTYD64_EI_EnemyHasItem(Actor* actor, s32 itemID) {
    if (actor == NULL) {
        return false;
    }
    return TTYD64_EI_HeldItem(actor) == itemID;
}

API_CALLABLE(TTYD64_GetHeldItem) {
    Bytecode* args = script->ptrReadPos;
    Actor* actor = (Actor*) evt_get_variable(script, *args++);

    evt_set_variable(script, *args++, actor != NULL ? TTYD64_EI_HeldItem(actor) : ITEM_NONE);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetHeldItemEntity) {
    Bytecode* args = script->ptrReadPos;
    Actor* actor = (Actor*) evt_get_variable(script, *args++);

    evt_set_variable(script, *args++, actor != NULL ? TTYD64_EI_GetItemEntityIndex(actor) : 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_HasHeldItem) {
    Bytecode* args = script->ptrReadPos;
    Actor* actor = (Actor*) evt_get_variable(script, *args++);

    evt_set_variable(script, *args++, actor != NULL && TTYD64_EI_HasHeldItemData(actor));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_ClearHeldItem) {
    Actor* actor = (Actor*) evt_get_variable(script, *script->ptrReadPos);

    if (actor != NULL) {
        TTYD64_EI_SetHeldItem(actor, ITEM_NONE, 0);
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetWrappedTakeTurn) {
    evt_set_variable(script, *script->ptrReadPos, (Bytecode) TTYD64_Stack_TakeTurnScript);
    return ApiStatus_DONE2;
}

static TTYD64EnemyItemRecord* ei_record(TTYD64EnemyItemRecord* table, s32 actorID) {
    u32 index;

    if ((u32) actorID < ACTOR_CLASS_ENEMY) {
        return NULL;
    }
    index = (u32) actorID & 0xFDFF;
    if (index >= TTYD64_EI_ITEM_TABLE_RECORDS) {
        return NULL;
    }
    return &table[index];
}

TTYD64EnemyItemRecord* TTYD64_get_actor_itemTableData(s32 actorID) {
    return ei_record(sEnemiesItemsBattleData, actorID);
}

TTYD64EnemyItemRecord* TTYD64_get_actor_itemTableData_OriginalFormation(s32 actorID) {
    return ei_record(sEnemiesItemsBattleData_OriginalFormation, actorID);
}

TTYD64EnemyItemRecord* TTYD64_EI_GetActorMostFrontRecord(void) {
    s32 i;

    for (i = 0; i < TTYD64_EI_ITEM_TABLE_RECORDS; i++) {
        if (sEnemiesItemsBattleData_OriginalFormation[i].origin == TTYD64_EI_ORIGIN_FRONT_MOST) {
            return &sEnemiesItemsBattleData_OriginalFormation[i];
        }
    }
    return NULL;
}

s32 TTYD64_EI_FormationRecordCount(void) {
    s32 count = 0;

    while (count < TTYD64_EI_ITEM_TABLE_RECORDS && sEnemiesItemsBattleData_OriginalFormation[count].dropTable != 0) {
        count++;
    }
    return count;
}

API_CALLABLE(TTYD64_EnemyItemTable_SetStolenByte) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID = evt_get_variable(script, *args++);
    TTYD64EnemyItemRecord* record = TTYD64_get_actor_itemTableData(actorID);

    if (record != NULL) {
        if (record->origin != TTYD64_EI_ORIGIN_MID_BATTLE) {
            TTYD64_get_actor_itemTableData_OriginalFormation(actorID)->stolen = true;
        }
        record->stolen = true;
    }
    return ApiStatus_DONE2;
}

void TTYD64_EnemyItemTable_ClearAllData(void) {
    memset(sEnemiesItemsBattleData, 0, sizeof(sEnemiesItemsBattleData));
    memset(sEnemiesItemsBattleData_OriginalFormation, 0, sizeof(sEnemiesItemsBattleData_OriginalFormation));
}

API_CALLABLE(TTYD64_Function_DeleteData_EnemyItemDropTable_SelfActor) {
    TTYD64EnemyItemRecord* record = TTYD64_get_actor_itemTableData(script->owner1.actorID);

    if (record != NULL) {
        memset(record, 0, sizeof(*record));
    }
    return ApiStatus_DONE2;
}

void TTYD64_enemy_item_table_data_update_actorMostInFront(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    s32 closest = 0;
    s32 i;
    f32 closestX;
    Actor* actor;
    TTYD64EnemyItemRecord* record;
    TTYD64EnemyItemRecord* original;

    if (battleStatus->enemyActors[0] == NULL) {
        return;
    }
    closestX = battleStatus->enemyActors[0]->homePos.x + 0.0f;
    for (i = 0; i < ARRAY_COUNT(battleStatus->enemyActors); i++) {
        actor = battleStatus->enemyActors[i];
        if (actor == NULL) {
            break;
        }
        if (actor->homePos.x < closestX) {
            closestX = actor->homePos.x + 0.0f;
            closest = i;
        }
    }
    actor = battleStatus->enemyActors[closest];
    record = TTYD64_get_actor_itemTableData((u16) actor->actorID);
    original = TTYD64_get_actor_itemTableData_OriginalFormation((u16) actor->actorID);
    original->origin = TTYD64_EI_ORIGIN_FRONT_MOST;
    record->origin = TTYD64_EI_ORIGIN_FRONT_MOST;
}

void TTYD64_ShowFlyingStat(Actor* actor, s32 type, s32 amount) {
    f32 z = (s32) actor->curPos.z;
    f32 x = (s32) (actor->curPos.x + 0.0f);
    f32 y = (s32) (actor->curPos.y + 35.0f);

    fx_recover(type, x, y, z, amount);
}

s32 TTYD64_get_item_flags(s32 itemID, s32 typeOfFlags) {
    ItemData* item = &gItemTable[itemID];

    if (typeOfFlags == 0) {
        return (u16) item->typeFlags;
    }
    return item->targetFlags;
}

API_CALLABLE(TTYD64_GetItemFlags) {
    Bytecode* args = script->ptrReadPos;
    s32 itemID = evt_get_variable(script, args[0]);
    ItemData* item = &gItemTable[itemID];

    evt_set_variable(script, args[1], (u16) item->typeFlags);
    evt_set_variable(script, args[2], item->targetFlags);
    return ApiStatus_DONE2;
}

ItemData* TTYD64_get_item_global_data(s32 itemID) {
    return &gItemTable[itemID];
}

API_CALLABLE(TTYD64_GetItemGlobalData) {
    Bytecode* args = script->ptrReadPos;
    ItemData* item = TTYD64_get_item_global_data(evt_get_variable(script, args[0]));

    evt_set_variable(script, args[1], (Bytecode) item);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetMoveData) {
    Bytecode* args = script->ptrReadPos;
    s32 moveID = evt_get_variable(script, args[0]);

    evt_set_variable(script, args[1], (Bytecode) &gMoveTable[moveID]);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_SetActorItemData) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID = evt_get_variable(script, args[0]);
    u32 itemData = evt_get_variable(script, args[1]);
    Actor* actor;

    if (actorID == (s32) ACTOR_SELF) {
        actorID = script->owner1.actorID;
    }
    actor = get_actor(actorID);
    if (actor != NULL) {
        TTYD64_EI_SetHeldItem(actor, (u16) (itemData >> 16), (u8) (itemData >> 8));
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_LoadItemScriptEnemy) {
    BattleStatus* battleStatus = &gBattleStatus;
    ItemData* item = &gItemTable[battleStatus->moveArgument];
    s32* itemPtr = &ItemKeys[0];
    s32 i;

    for (i = 0; *itemPtr != ITEM_NONE; i++, itemPtr++) {
        if (*itemPtr == battleStatus->moveArgument) {
            break;
        }
    }
    if (*itemPtr == ITEM_NONE) {
        if (item->typeFlags & ITEM_TYPE_FLAG_FOOD_OR_DRINK) {
            i = 0;
        } else {
            i = 1;
        }
    }
    script->varTablePtr[0].p = gBattleItemTable[i].mainScript;
    script->varTable[1] = 1;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_EI_UpdateKoStatus) {
    btl_update_ko_status();
    return ApiStatus_BLOCK;
}

void TTYD64_EI_SpawnEnemyItem(Actor* actor) {
    s32 itemID = TTYD64_EI_HeldItem(actor);
    s32 index = make_item_entity_nodelay(itemID, 0.0f, 0.0f, 0.0f, ITEM_SPAWN_MODE_DECORATION, 0);

    TTYD64_EI_SetHeldItem(actor, itemID, index & 0xFF);
}

void TTYD64_EI_DespawnEnemyItem(Actor* actor) {
    s32 index = TTYD64_EI_GetItemEntityIndex(actor);

    TTYD64_EI_SetHeldItem(actor, ITEM_NONE, 0);
    remove_item_entity_by_index(index);
}

void TTYD64_EI_RollHeldItem(Actor* actor) {
    s32 var3 = actor->state.varTable[3];
    const TTYD64DropEntry* table;
    TTYD64EnemyItemRecord* record;
    TTYD64EnemyItemRecord* original = NULL;
    s32 count;
    s32 totalWeight;
    s32 itemID;
    s32 i;

    TTYD64_EI_SetHeldItem(actor, ITEM_NONE, 0);
    record = TTYD64_get_actor_itemTableData((u16) actor->actorID);
    if (var3 > TTYD64_DROP_NONE && var3 < TTYD64_DROP_COUNT && record != NULL) {
        table = TTYD64_GetDropTable(var3, &count);
        record->dropTable = var3;
        if (gBattleState == BATTLE_STATE_START) {
            original = TTYD64_get_actor_itemTableData_OriginalFormation((u16) actor->actorID);
            original->dropTable = var3;
        }

        totalWeight = 0;
        for (i = 0; i < count; i++) {
            totalWeight += table[i].holdWeight;
        }

        for (i = 0; i < count; i++) {
            s32 weight = table[i].holdWeight;
            s32 roll;

            if (weight == 0) {
                continue;
            }
            roll = rand_int((200 + totalWeight) / weight);
            if (roll == 0) {
                roll = 1;
            }
            if (roll != 1) {
                continue;
            }

            itemID = table[i].itemID;
            TTYD64_Function_Mode_Random_GetEnemyItem(&itemID);
            TTYD64_EI_SetHeldItem(actor, (u16) itemID, 0);
            TTYD64_EI_SpawnEnemyItem(actor);

            record->dropTable = var3;
            record->itemID = table[i].itemID;
            if (original != NULL) {
                original->dropTable = var3;
                original->itemID = table[i].itemID;
                original->origin = TTYD64_EI_ORIGIN_FORMATION;
                record->origin = TTYD64_EI_ORIGIN_FORMATION;
            }
            break;
        }
    }
    actor->state.varTable[3] = 0;
}

s32 TTYD64_EI_DifficultyScale(s32 value) {
    s32 difficulty = evt_get_variable(NULL, GameByte(0x1000 + TTYD64_MB_Byte_Settings_Difficulty));

    if (difficulty == 0) {
        value = value / 2;
        if (value == 0) {
            value = 1;
        }
    } else if (difficulty == 1) {
    } else if (difficulty == 2) {
        value = value + value / 2;
    } else {
        value = value + value;
    }
    return value;
}

void TTYD64_EI_ApplyDifficultyHP(Actor* actor) {
    s32 difficulty = evt_get_variable(NULL, GameByte(0x1000 + TTYD64_MB_Byte_Settings_Difficulty));
    s32 baseHP = actor->actorBlueprint->maxHP;
    s32 hp = baseHP;

    if (difficulty != 1) {
        if (difficulty == 0) {
            hp = hp / 2;
            if (hp == 0) {
                hp = 1;
            }
        } else if (difficulty == 2) {
            hp = hp + hp / 2;
        } else {
            hp = hp + hp;
        }
        if (baseHP <= 0xFF && hp >= 0x100) {
            hp = 0xFF;
        }
    }
    actor->curHP = hp;
    actor->maxHP = hp;
}

void TTYD64_EI_ApplyCreateBadges(Actor* actor) {
    TTYD64BattleRec* rec;
    s32 hp;
    s32 roll;

    if (TTYD64_EI_EnemyHasItem(actor, 0xE7) || TTYD64_EI_EnemyHasItem(actor, 0x134)
        || TTYD64_EI_EnemyHasItem(actor, 0x14A) || TTYD64_EI_EnemyHasItem(actor, 0x18D))
    {
        hp = actor->curHP + 5;
        if (actor->curHP <= 0xFF && hp >= 0xFF) {
            hp = 0xFF;
        }
        actor->curHP = hp;
        actor->maxHP = hp;
        return;
    }
    if (TTYD64_EI_EnemyHasItem(actor, 0x100)) {
        actor->staticStatus = STATUS_KEY_STATIC;
        actor->staticDuration = 99;
        return;
    }
    if (!TTYD64_EI_EnemyHasItem(actor, 0x175)) {
        return;
    }
    roll = rand_int(3);
    if (roll == 1) {
        rec = TTYD64_ActorRec((u16) actor->actorID);
        rec->buffs[TTYD64_BUFF_FP_REGEN].amount = 2;
        rec->buffs[TTYD64_BUFF_FP_REGEN].turns = 4;
    } else if (roll == 2) {
        actor->transparentStatus = STATUS_KEY_TRANSPARENT;
        actor->transparentDuration = 3;
    } else if (roll == 3) {
        actor->staticStatus = STATUS_KEY_STATIC;
        actor->staticDuration = 3;
    } else {
        rec = TTYD64_ActorRec((u16) actor->actorID);
        rec->buffs[TTYD64_BUFF_HP_REGEN].amount = 2;
        rec->buffs[TTYD64_BUFF_HP_REGEN].turns = 4;
    }
}

static s32 ei_player_team_defense(s32 actorID, s32 badgeA, s32 badgeB) {
    TTYD64BattleRec* rec = TTYD64_ActorRec(actorID);
    s32 defense = 0;
    s32 count;

    if (rec != NULL) {
        defense += (s8) rec->defendStack;
    }
    count = TTYD64_IsBadgeActivated_Stack(badgeA);
    if (count != 0) {
        defense += count;
    }
    count = TTYD64_IsBadgeActivated_Stack(badgeB);
    if (count != 0) {
        defense += count;
    }
    return defense;
}

s32 TTYD64_EI_PiercePlayerTeamDefense(Actor* attacker) {
    s32 defense = 0;
    u16 targetID;

    if (TTYD64_PierceDefenseFlag[0] != 0 || (gBattleStatus.curAttackElement & DAMAGE_TYPE_IGNORE_DEFENSE)) {
        targetID = attacker->targetActorID;
        if (targetID == ACTOR_PLAYER) {
            defense = ei_player_team_defense(ACTOR_PLAYER, 0xFB, 0x116);
        } else if (targetID == ACTOR_PARTNER) {
            defense = ei_player_team_defense(ACTOR_PARTNER, 0x181, 0x186);
        }
    }
    TTYD64_PierceDefenseFlag[0] = 0;
    return defense;
}

void TTYD64_EI_SpawnDrops(struct Enemy* enemy, s32* itemToDrop) {
    EnemyDrops* drops = enemy->drops;
    s32 itemHog = TTYD64_IsBadgeActivated_Stack(0x172);
    s32 randomOdds = 1 + itemHog;
    s32 heldOdds = randomOdds;
    s32 nothingOdds = 2;
    s32 total;
    s32 roll;
    s32 item = ITEM_NONE;
    s32 spawn = false;

    *itemToDrop = ITEM_NONE;

    if ((u8) gGameStatus.areaID == 0x1C) {
        nothingOdds = 3;
    }
    total = randomOdds + nothingOdds;

    roll = rand_int(total);
    if (roll == 0) {
        roll = 1;
    }
    if ((u32) roll < (u32) (randomOdds + 1)) {
        TTYD64EnemyItemRecord* front = TTYD64_EI_GetActorMostFrontRecord();

        if (front != NULL && front->dropTable != 0) {
            s32 count;
            const TTYD64DropEntry* table = TTYD64_GetDropTable(front->dropTable, &count);
            s32 totalWeight = 0;
            s32 i;

            for (i = 0; i < count; i++) {
                totalWeight += table[i].dropWeight;
            }
            for (i = 0; i < count; i++) {
                s32 weight = table[i].dropWeight;
                s32 r;

                if (weight == 0) {
                    continue;
                }
                r = rand_int((300 + totalWeight) / weight);
                if (r == 0) {
                    r = 1;
                }
                if (r != 1) {
                    continue;
                }
                item = table[i].itemID;
                spawn = true;
                break;
            }
        }
    } else {
        roll = rand_int(total);
        if (roll == 0) {
            roll = 1;
        }
        if ((u32) roll < (u32) (heldOdds + 1)) {
            s32 count = TTYD64_EI_FormationRecordCount();

            if (count != 0) {
                TTYD64EnemyItemRecord* record;

                roll = rand_int(count);
                if (roll == 0) {
                    roll = 1;
                }
                record = TTYD64_get_actor_itemTableData_OriginalFormation(ACTOR_ENEMY0 + roll - 1);
                if (!record->stolen) {
                    item = (u16) record->itemID;
                    spawn = true;
                }
            }
        }
    }

    if (!spawn && itemHog != 0) {
        if (rand_int(100) < 40) {
            roll = rand_int(8);
            if (roll == 0) {
                roll = 1;
            }
            item = TTYD64_ItemHog_ItemTable[roll - 1];
            spawn = true;
        }
    }

    TTYD64_EnemyItemTable_ClearAllData();

    if (spawn) {
        s32 totalWeight = 0;
        s32 curWeight = 0;
        s32 i;

        for (i = 0; i < ARRAY_COUNT(drops->itemDrops); i++) {
            s16 dropItem = (i == 0) ? (s16) item : drops->itemDrops[i].item;
            if (dropItem == ITEM_NONE) {
                break;
            }
            totalWeight += drops->itemDrops[i].weight;
        }
        roll = rand_int(totalWeight);
        for (i = 0; i < ARRAY_COUNT(drops->itemDrops); i++) {
            s16 dropItem = (i == 0) ? (s16) item : drops->itemDrops[i].item;
            if (dropItem == ITEM_NONE) {
                break;
            }
            curWeight += drops->itemDrops[i].weight;
            if (drops->itemDrops[i].flagIdx > 0) {
                if (get_global_flag(EVT_INDEX_OF_GAME_FLAG(GF_Unused_NPC_6C) + drops->itemDrops[i].flagIdx)) {
                    continue;
                }
            }
            if (curWeight >= roll) {
                *itemToDrop = dropItem;
                if (drops->itemDrops[i].flagIdx >= 0) {
                    set_global_flag(EVT_INDEX_OF_GAME_FLAG(GF_SpawnedItemDrop_00) + drops->itemDrops[i].flagIdx);
                }
                break;
            }
        }
    }
}
