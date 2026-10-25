#include "common.h"
#include "battle/battle.h"
#include "sprite.h"
#include "script_api/battle.h"
#include "port/romhack/specific/TTYD64/badges_internal.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"

extern s32 BattleStatusUpdateDelay;
extern PlayerCurrentAnimInfo CurPlayerAnimInfo[3];

s32 TTYD64_bs_PartnerTestLuck(void) {
    u32 left = TTYD64_IsBadgeActivated_Stack(0x17E);

    if (left != 0 && (u32) TTYD64_GetPartnerHP() < 6) {
        do {
            if (rand_int(100) < 30) {
                return HIT_RESULT_LUCKY;
            }
            left--;
        } while (left != 0);
    }
    left = TTYD64_IsBadgeActivated_Stack(0x17F);
    if (left != 0) {
        do {
            if (rand_int(100) < 10) {
                return HIT_RESULT_LUCKY;
            }
            left--;
        } while (left != 0);
    }
    return -1;
}

s32 TTYD64_bs_PartnerDefenseBadges(s32 damage) {
    s32 count;

    damage -= TTYD64_IsBadgeActivated_Stack(0x181);
    damage -= TTYD64_IsBadgeActivated_Stack(0x186);
    damage += TTYD64_IsBadgeActivated_Stack(0x187);
    count = TTYD64_IsBadgeActivated_Stack(0x182);
    if (count != 0) {
        s32 divisor = 2 + (count - 1);

        if ((u32) TTYD64_GetPartnerHP() < 6) {
            damage /= divisor;
        }
    }
    return damage;
}

static void bs_add_drain_count(void) {
    u32 next = (u8) gBattleStatus.hpDrainCount + 1;

    if (!(next < 5)) {
        next = 5;
    }
    gBattleStatus.hpDrainCount = next;
}

s32 TTYD64_bs_PartnerAttackDamage(s32 base) {
    BattleStatus* battleStatus = &gBattleStatus;
    s32 damage = base;
    s32 boost = 0;
    s32 megaRush = 0;
    s32 count;
    TTYD64BattleRec* rec;

    if (gPlayerData.curPartner == PARTNER_BOW && evt_get_variable(nullptr, GameByte(0x100B)) != 1
        && (battleStatus->curAttackElement & 0x08000000))
    {
        if (TTYD64_IsBadgeActivated_Stack(0x18C) != 0) {
            bs_add_drain_count();
        }
        return damage;
    }

    damage += TTYD64_IsBadgeActivated_Stack(0x183);
    damage -= TTYD64_IsBadgeActivated_Stack(0x186);
    damage += TTYD64_IsBadgeActivated_Stack(0x187);
    if (TTYD64_IsBadgeActivated_Stack(0x18C) != 0) {
        damage--;
        bs_add_drain_count();
    }
    count = TTYD64_IsBadgeActivated_Stack(0x185);
    if (count != 0 && (u32) TTYD64_GetPartnerHP() < 2) {
        megaRush = count * 4;
        damage += megaRush;
    }
    count = TTYD64_IsBadgeActivated_Stack(0x184);
    if (count != 0 && (u32) TTYD64_GetPartnerHP() < 6 && megaRush == 0) {
        damage += count * 2;
    }
    rec = TTYD64_ActorRec(ACTOR_PARTNER);
    if (rec != nullptr) {
        boost = rec->buffs[TTYD64_BUFF_ATTACK].amount + rec->charge;
    }
    return damage + boost;
}

s32 TTYD64_bs_PlayerChargeBoost(s32 turboChargeTurnsLeft) {
    TTYD64BattleRec* rec = TTYD64_ActorRec(ACTOR_PLAYER);
    s32 boost = rec->charge;

    if (TTYD64_IsBadgeActivated_Stack(0x16E) != 0) {
        u32 next;

        boost--;
        next = TTYD64_FPDrainByte[0] + 1;
        if (next < 6) {
            TTYD64_FPDrainByte[0] = next;
        }
    }
    return boost + turboChargeTurnsLeft;
}

s32 TTYD64_bs_PowerBadgesBonus(u32 selectedMoveID) {
    s32 bonus = 0;

    if (selectedMoveID != 6) {
        bonus += TTYD64_IsBadgeActivated_Stack(0x170);
    }
    if (selectedMoveID != 0x1D) {
        bonus += TTYD64_IsBadgeActivated_Stack(0x171);
    }
    return bonus;
}

s32 TTYD64_bs_FPDrainRecovery(void) {
    s32 count = TTYD64_IsBadgeActivated_Stack(0x16E);
    s32 amount = 0;

    if (count != 0) {
        u8 drained = TTYD64_FPDrainByte[0];

        TTYD64_FPDrainByte[0] = 0;
        if (drained != 0) {
            amount = drained + (count - 1);
        }
    }
    return amount;
}

s32 TTYD64_bs_PartnerTurnEnd(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    s32 delay = BattleStatusUpdateDelay;
    s32 happy = 0;
    s32 drain = 0;
    u32 buttonsHigh;
    Evt* script;

    if (delay != 0) {
        delay--;
        BattleStatusUpdateDelay = delay;
        return delay > 0;
    }
    if (TTYD64_GetPartnerHP() <= 0) {
        return false;
    }
    buttonsHigh = (u32) battleStatus->curButtonsDown >> 24;
    if (buttonsHigh == 0 || buttonsHigh == 9 || buttonsHigh == 10) {
        if ((u8) battleStatus->outtaSightActive == 0) {
            s32 count;

            happy = TTYD64_IsBadgeActivated_Stack(0x18B);
            if (happy != 0) {
                if (!((u32) rand_int(100) < 50)) {
                    happy = 0;
                }
            }
            count = TTYD64_IsBadgeActivated_Stack(0x18C);
            if (count != 0) {
                drain = (u8) battleStatus->hpDrainCount + (count - 1);
                battleStatus->hpDrainCount = 0;
            }
        }
    }
    if (((happy & 0xFFFF) | (drain & 0xFFFF)) == 0) {
        return false;
    }
    BattleStatusUpdateDelay = 30;
    script = start_script(&TTYD64_PartnerHappy, EVT_PRIORITY_A, 0);
    script->varTable[10] = drain;
    script->varTable[11] = happy;
    return true;
}

void TTYD64_bs_HPPlusP(void) {
    s32 partnerID = PARTNER_GOOMBARIO;
    s32 count;
    s32 prev;
    s32 prevBonus;
    s32 unlocked;
    u32 i;

    if (TTYD64_Function_GetPartnersUnlocked() == 0) {
        return;
    }
    count = TTYD64_IsBadgeActivated_Stack(0x18D);
    prev = evt_get_variable(nullptr, GameByte(0x1007));
    if (prev == count) {
        return;
    }
    prevBonus = 0;
    if (prev != 0) {
        prevBonus = 5 * prev;
    }
    unlocked = TTYD64_Function_GetPartnersUnlocked();
    i = 0;
    do {
        u32 maxHP = TTYD64_PartnerHPRecords[partnerID].max - prevBonus + count * 5;

        if (!(maxHP < 100)) {
            maxHP = 99;
        }
        TTYD64_PartnerHPRecords[partnerID].max = maxHP;
        do {
            partnerID++;
            if (i == (u32) (unlocked - 1) || partnerID >= ARRAY_COUNT(TTYD64_PartnerHPRecords)) {
                break;
            }
        } while (TTYD64_PartnerHPRecords[partnerID].max == 0);
        i++;
    } while (i < (u32) unlocked && partnerID < ARRAY_COUNT(TTYD64_PartnerHPRecords));
    evt_set_variable(nullptr, GameByte(0x1007), count);
}

s32 TTYD64_bs_SkinPalette(SpriteComponent** compList, s32 compIndex, s32 palette) {
    s32 skin;
    s32 lEmblem;
    s32 wEmblem;
    s32 skinPalette;

    if (compList == nullptr || compList != CurPlayerAnimInfo[0].componentList) {
        return palette;
    }
    if (compIndex != 0 && compIndex != 1) {
        return palette;
    }
    if (CurPlayerAnimInfo[0].animID == 0x1002F) {
        return palette;
    }
    lEmblem = TTYD64_IsBadgeEquipped(0x173);
    wEmblem = TTYD64_IsBadgeEquipped(0x174);
    if (wEmblem + lEmblem == 0) {
        skin = 0;
    } else if (!((u32) (wEmblem + lEmblem) < 2)) {
        skin = 3;
    } else if (lEmblem == 0) {
        skin = 2;
    } else {
        skin = 1;
    }
    if (!(gPlayerStatus.animFlags & 0x4000)) {
        skinPalette = skin != 0 ? 0x20 + skin : 0;
    } else {
        skinPalette = 0x18 + skin;
    }

    if ((u8) gGameStatus.context == 0) {
        u8 initByte = 0;
        AnimID anim = gPlayerStatus.anim;

        if (compList[0] != PTR_LIST_END && compList[1] != PTR_LIST_END) {
            initByte = (u8) compList[1]->initialized;
        }
        if (initByte == 0) {
            return skinPalette;
        }
        if (anim == 0x6000C || anim == 0x6000E || anim == 0x6000F || anim == 0x8001E) {
            return skinPalette;
        }
        return compIndex == 1 ? skinPalette : palette;
    } else {
        Actor* player = gBattleStatus.playerActor;
        s32 animID = CurPlayerAnimInfo[0].animID;

        if (player != nullptr) {
            if ((u8) player->debuff == 9) {
                return palette;
            }
            if ((u8) player->stoneStatus == 0xC) {
                return palette;
            }
        }
        if (animID == 0x30013 || animID == 0x30019 || animID == 0x3001A || animID == 0x30020 || animID == 0x30021
            || animID == 0x4001B || animID == 0x40021 || animID == 0x40026 || animID == 0x40027)
        {
            return compIndex == 0 ? palette : skinPalette;
        }
        return compIndex == 1 ? palette : skinPalette;
    }
}

void TTYD64_bs_LuckyStart(Actor* player) {
    u32 roll;

    if (TTYD64_IsBadgeActivated_Stack(0x175) == 0) {
        return;
    }
    roll = rand_int(100);
    if (roll < 50) {
        TTYD64BattleRec* rec = TTYD64_ActorRec(ACTOR_PLAYER);

        if (rand_int(1) != 0) {
            rec->buffs[TTYD64_BUFF_FP_REGEN].amount = 2;
            rec->buffs[TTYD64_BUFF_FP_REGEN].turns = 4;
        } else {
            rec->buffs[TTYD64_BUFF_HP_REGEN].amount = 2;
            rec->buffs[TTYD64_BUFF_HP_REGEN].turns = 4;
        }
    } else if (roll < 70) {
        player->transparentStatus = 0xE;
        player->transparentDuration = 2;
    } else if (roll < 101) {
        player->staticStatus = 0xB;
        player->staticDuration = 3;
    }
}

s32 TTYD64_bs_PityFlowerRolls(void) {
    u32 count = TTYD64_IsBadgeActivated_Stack(0x16F);
    u32 i = 0;
    s32 hits = 0;

    if (count == 0) {
        return 0;
    }
    do {
        hits += (u32) rand_int(100) < 0x21;
        i++;
    } while (i < count);
    return hits;
}

void TTYD64_bs_ReturnPostage(Actor* attacker) {
    if ((u16) attacker->targetActorID == 0 && (u16) gBattleStatus.curAttackDamage != 0) {
        if (TTYD64_IsBadgeActivated_Stack(0x176) != 0) {
            TTYD64_dispatch_event_actor_dontKillScripts(attacker, EVENT_HIT);
        }
    }
    TTYD64_Function_GlitzPit_DamageChallenge();
}

s32 TTYD64_bs_DipBadge(s32 badgeID, s32 entryCount) {
    s32 badge = badgeID;

    if (badge == 0) {
        return 0;
    }
    if (badge == 0xE9 && TTYD64_bs_IsBadgeInSubMenu(0xE9, entryCount)) {
        badge = TTYD64_bs_IsBadgeInSubMenu(0x106, entryCount) ? 0 : 0x106;
    }
    if (TTYD64_bs_IsBadgeInSubMenu(0xE9, entryCount) && TTYD64_bs_IsBadgeInSubMenu(0x106, entryCount)) {
        return 0;
    }
    return badge;
}

s32 TTYD64_bs_DipCost(s32 costFP) {
    s32 savers = TTYD64_IsBadgeActivated_Stack(0x105);
    s32 cost;

    savers += TTYD64_IsBadgeActivated_Stack(0x138);
    cost = costFP - savers;
    if (cost <= 0) {
        cost = 1;
    }
    return cost;
}

s32 TTYD64_bs_EnabledMenus(s32 enabledMenus) {
    if (TTYD64_IsBadgeActivated_Stack(0x170) != 0) {
        enabledMenus &= ~2;
    }
    if (TTYD64_IsBadgeActivated_Stack(0x171) != 0) {
        enabledMenus &= ~1;
    }
    return enabledMenus;
}

void TTYD64_bs_DrawChargeCost(s32 x, s32 y) {
    s32 count;

    if (gBattleStatus.flags1 & BS_FLAGS1_PLAYER_IN_BACK) {
        count = TTYD64_IsBadgeActivated_Stack(0x17D);
    } else {
        count = TTYD64_IsBadgeActivated_Stack(0x16D);
    }
    if (count == 0) {
        return;
    }
    set_message_int_var(count, 0);
    draw_msg(
        (intptr_t) TTYD64_Charge_FPAmount, x + 0x32, y - 1, 0xFF,
        (u32) (u8) gPlayerData.curFP < (u32) count ? 0xB : 0xA, 0
    );
}
