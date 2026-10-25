#include "port/romhack/specific/TTYD64/partner_hp_internal.h"
#include "port/modding/Mod.h"

u8 TTYD64_HealingItem_Bool[1];
u8 TTYD64_HealingBox_PartnersOrder[12];
u8 TTYD64_ActorDead[4];

TTYD64PartnerHPRecord TTYD64_PartnerHPRecords[12];
u8 TTYD64_ShineSprites;
s32 TTYD64_FortressKeys;

TTYD64PartnerHPRecord* TTYD64_PartnerHPRecord(s32 partnerID) {
    return &TTYD64_PartnerHPRecords[partnerID];
}

static b32 ph_has_hp(s32 partnerID) {
    switch (partnerID) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
        case 7:
        case 8:
        case 9:
            return true;
    }
    return false;
}

s32 TTYD64_ph_InlineMsg(const u8* msg) {
    return Mod_RegisterInlineMessage("TTYD64", msg);
}

s32 TTYD64_PartnerHP(s32 partnerID) {
    return TTYD64_PartnerHPRecord(partnerID)->hp;
}

s32 TTYD64_PartnerMaxHP(s32 partnerID) {
    return TTYD64_PartnerHPRecord(partnerID)->max;
}

void TTYD64_SetPartnerHPByID(s32 partnerID, s32 hp) {
    TTYD64_PartnerHPRecord(partnerID)->hp = hp;
}

void TTYD64_SetPartnerMaxHPByID(s32 partnerID, s32 maxHP) {
    TTYD64_PartnerHPRecord(partnerID)->max = maxHP;
}

s32 TTYD64_GetPartnerHP(void) {
    s32 partnerID = (u8) gPlayerData.curPartner;

    if (!ph_has_hp(partnerID)) {
        return -1;
    }
    return TTYD64_PartnerHPRecord(partnerID)->hp;
}

s32 TTYD64_GetPartnerHP_byID(s32 partnerID) {
    if (!ph_has_hp(partnerID)) {
        return 0xFFFF;
    }
    return TTYD64_PartnerHPRecord(partnerID)->hp;
}

s32 TTYD64_GetPartnerMaxHP(void) {
    s32 partnerID = (u8) gPlayerData.curPartner;

    if (!ph_has_hp(partnerID)) {
        return 0xFFFF;
    }
    return TTYD64_PartnerHPRecord(partnerID)->max;
}

void TTYD64_SetPartnerHP(s32 hp) {
    s32 partnerID = (u8) gPlayerData.curPartner;

    if (ph_has_hp(partnerID)) {
        TTYD64_PartnerHPRecord(partnerID)->hp = hp;
    }
}

void TTYD64_Function_HealPartners(void) {
    s32 i;
    u8 maxHP;

    for (i = 1; i <= 9; i++) {
        maxHP = TTYD64_PartnerHPRecord(i)->max;
        TTYD64_PartnerHPRecord(i)->hp = maxHP;
        if ((u8) gPlayerData.curPartner != i) {
            TTYD64_PartnerHPRecord(i)->displayed = maxHP;
        }
    }
}

void TTYD64_sync_status_menu_OnlyPartners(void) {
    s32 i;

    for (i = 1; i <= 9; i++) {
        TTYD64_PartnerHPRecord(i)->displayed = TTYD64_PartnerHPRecord(i)->hp;
    }
}

void TTYD64_updatePartnerMaxHP(s32 partnerID) {
    TTYD64PartnerHPRecord* record = TTYD64_PartnerHPRecord(partnerID);
    s32 maxHP = TTYD64_PartnersHPTable[(partnerID - 1) * 3 + (u8) gPlayerData.partners[partnerID].level];

    maxHP += 5 * TTYD64_IsBadgeActivated_Stack(0x18D);
    record->hp = maxHP;
    record->max = maxHP;
}

API_CALLABLE(TTYD64_GetPartnerHP_API) {
    evt_set_variable(script, *script->ptrReadPos, TTYD64_GetPartnerHP());
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_GetPartnerData_API) {
    s32 partnerID = (u8) gPlayerData.curPartner;
    Bytecode value = -1;

    if (ph_has_hp(partnerID)) {
        value = (Bytecode) &gPlayerData.partners[partnerID];
    }
    evt_set_variable(script, *script->ptrReadPos, value);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_RaisePartnerMaxHP) {
    TTYD64_updatePartnerMaxHP(evt_get_variable(script, *script->ptrReadPos));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Heal_PlayerTeam) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID = evt_get_variable(script, *args++);
    s32 amount;
    u8* hpData;
    s32 partnerID;
    s32 hp;
    s32 maxHP;

    if (actorID == (s32) ACTOR_SELF) {
        actorID = script->owner1.actorID;
    }
    amount = evt_get_variable(script, *args++);
    if (actorID == ACTOR_PLAYER) {
        hpData = (u8*) &gPlayerData.curHP;
    } else {
        partnerID = (u8) gPlayerData.curPartner;
        if (!ph_has_hp(partnerID)) {
            return ApiStatus_DONE2;
        }
        hpData = &TTYD64_PartnerHPRecord(partnerID)->hp;
    }
    hp = hpData[0] + amount;
    maxHP = hpData[1];
    if (hp < 0) {
        return ApiStatus_DONE2;
    }
    if ((u32) hp >= (u32) maxHP) {
        hp = maxHP;
    }
    hpData[0] = hp;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_HealActor) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID = evt_get_variable(script, *args++);
    s32 amount;
    Actor* actor;
    s32 hp;
    s32 maxHP;

    if (actorID == (s32) ACTOR_SELF) {
        actorID = script->owner1.actorID;
    }
    amount = evt_get_variable(script, *args++);
    actor = get_actor(actorID);
    hp = actor->curHP + amount;
    maxHP = actor->maxHP;
    if (hp < 0) {
        hp = 0;
    }
    if ((u32) hp >= (u32) maxHP) {
        hp = maxHP;
    }
    actor->curHP = hp;
    return ApiStatus_DONE2;
}

b32 TTYD64_heal_actor(s32 actorID, s32 amount) {
    Actor* actor = nullptr;
    s32 hp;
    s32 maxHP;

    if ((u32) actorID < ACTOR_CLASS_ENEMY) {
        if (actorID == ACTOR_PLAYER) {
            hp = (u8) gPlayerData.curHP;
            maxHP = (u8) gPlayerData.curMaxHP;
        } else {
            hp = TTYD64_GetPartnerHP();
            if (hp < 0) {
                return false;
            }
            maxHP = TTYD64_GetPartnerMaxHP();
        }
    } else {
        actor = get_actor(actorID);
        hp = actor->curHP;
        maxHP = actor->maxHP;
    }
    hp += amount;
    if (hp < 0) {
        hp = 0;
    }
    if ((u32) hp >= (u32) maxHP) {
        hp = maxHP;
    }
    if ((u32) actorID < ACTOR_CLASS_ENEMY) {
        if (actorID == ACTOR_PLAYER) {
            gPlayerData.curHP = hp;
        } else {
            TTYD64_SetPartnerHP(hp);
        }
    } else {
        actor->curHP = hp;
    }
    return true;
}

API_CALLABLE(TTYD64_RecoverFP) {
    s32 amount = evt_get_variable(script, *script->ptrReadPos);
    s32 fp = gPlayerData.curFP + amount;
    s32 maxFP = gPlayerData.curMaxFP;

    if (fp < 0) {
        fp = 0;
    }
    if (maxFP < fp) {
        fp = maxFP;
    }
    gPlayerData.curFP = fp;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_InflictStatus) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID = evt_get_variable(script, args[0]);
    Actor* actor;
    s32 statusID;
    s32 duration;

    if (actorID == (s32) ACTOR_SELF) {
        actorID = script->owner1.actorID;
    }
    actor = get_actor(actorID);
    statusID = evt_get_variable(script, args[1]);
    duration = evt_get_variable(script, args[2]);
    inflict_status(actor, statusID, duration);
    if (actorID == ACTOR_PLAYER) {
        actor->statusAfflicted = 0;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_TryToInflictStatus) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID = evt_get_variable(script, args[0]);
    Actor* actor;
    s32 statusID;
    s32 duration;
    s32 flag = 0;
    s32 turnMod = 0;

    if (actorID == (s32) ACTOR_SELF) {
        actorID = script->owner1.actorID;
    }
    actor = get_actor(actorID);
    statusID = evt_get_variable(script, args[1]);
    duration = evt_get_variable(script, args[2]);
    gBattleStatus.statusChance = 100;
    gBattleStatus.statusDuration = duration;
    switch (statusID) {
        case STATUS_KEY_SLEEP:
            flag = 0x1000;
            turnMod = 0x20;
            break;
        case STATUS_KEY_STATIC:
            flag = 0x2000;
            turnMod = 0x21;
            break;
        case STATUS_KEY_FROZEN:
            flag = 0x4000;
            turnMod = 0x22;
            break;
        case STATUS_KEY_PARALYZE:
            flag = 0x10000;
            turnMod = 0x26;
            break;
        case STATUS_KEY_POISON:
            flag = 0x20000;
            turnMod = 0x25;
            break;
        case STATUS_KEY_DIZZY:
            flag = 0x40000;
            turnMod = 0x24;
            break;
        case STATUS_KEY_SHRINK:
            flag = 0x80000;
            turnMod = 0x27;
            break;
        case STATUS_KEY_STONE:
            flag = 0x100000;
            turnMod = 0x28;
            break;
        case STATUS_KEY_STOP:
            flag = 0x200000;
            turnMod = 0x29;
            break;
    }
    gBattleStatus.curAttackStatus = (s32) (0x80000000 | ((u32) (u8) duration << 8) | 100 | flag);
    try_inflict_status(actor, statusID, turnMod);
    if (actorID == ACTOR_PLAYER) {
        actor->statusAfflicted = 0;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_ph_ReadPtrByte) {
    Bytecode* args = script->ptrReadPos;
    u8* ptr = (u8*) evt_get_variable(script, args[0]);
    s32 offset = evt_get_variable(script, args[1]);

    evt_set_variable(script, args[2], ptr[offset]);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_ph_WritePtrByte) {
    Bytecode* args = script->ptrReadPos;
    u8* ptr = (u8*) evt_get_variable(script, args[0]);
    s32 offset = evt_get_variable(script, args[1]);

    ptr[offset] = evt_get_variable(script, args[2]);
    return ApiStatus_DONE2;
}

void TTYD64_InstallPartnerHP(void) {
    TTYD64_InstallPartnerHPBattle();
    TTYD64_InstallPartnerHPWorld();
}
