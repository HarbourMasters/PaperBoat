#include "common.h"
#include "script_api/battle.h"
#include "port/modding/Abilities.h"
#include "port/modding/Messages.h"
#include "port/modding/ScriptOverrides.h"
#include "../TTYD64.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_items.h"
#include "../include/ttyd64_symbols.h"
#include "badges_internal.h"

extern EvtScript EVS_PlayerHappy;
extern EvtScript EVS_StartDefend;
extern EvtScript EVS_Mario_HandlePhase;
extern EvtScript EVS_RunAwayStart;
extern s32 TTYD64_mac_01_IntTable_80247E00[];

s32 TTYD64_bs_MsgChargeDesc;
s32 TTYD64_bs_MsgDefenseDesc;
s32 TTYD64_MsgID_TooMuchBadges;

typedef struct BadgeAbility {
    s16 itemID;
    s16 moveID;
    s32 holder;
    s32 ability;
} BadgeAbility;

static BadgeAbility sBadgeAbilities[] = {
    { TTYD64_ITEM_CHARGE, TTYD64_MOVE_CHARGE_1, MOD_ABILITY_HOLDER_PLAYER, -1 },
    { TTYD64_ITEM_FPDRAIN, TTYD64_MOVE_FPDRAIN, MOD_ABILITY_HOLDER_PLAYER, -1 },
    { TTYD64_ITEM_PITYFLOWER, TTYD64_MOVE_PITYFLOWER, MOD_ABILITY_HOLDER_PLAYER, -1 },
    { TTYD64_ITEM_JUMPMAN, TTYD64_MOVE_JUMPMAN, MOD_ABILITY_HOLDER_PLAYER, -1 },
    { TTYD64_ITEM_HAMMERMAN, TTYD64_MOVE_HAMMERMAN, MOD_ABILITY_HOLDER_PLAYER, -1 },
    { TTYD64_ITEM_ITEMHOG, TTYD64_MOVE_ITEMHOG, MOD_ABILITY_HOLDER_PLAYER, -1 },
    { TTYD64_ITEM_LEMBLEM, TTYD64_MOVE_LEMBLEM, MOD_ABILITY_HOLDER_PLAYER, -1 },
    { TTYD64_ITEM_WEMBLEM, TTYD64_MOVE_WEMBLEM, MOD_ABILITY_HOLDER_PLAYER, -1 },
    { TTYD64_ITEM_LUCKYSTART, TTYD64_MOVE_LUCKYSTART, MOD_ABILITY_HOLDER_PLAYER, -1 },
    { TTYD64_ITEM_RETURNPOSTAGE, TTYD64_MOVE_RETURNPOSTAGE, MOD_ABILITY_HOLDER_PLAYER, -1 },
    { TTYD64_ITEM_SIMPLIFIER, TTYD64_MOVE_SIMPLIFIER, MOD_ABILITY_HOLDER_PLAYER, -1 },
    { TTYD64_ITEM_UNSIMPLIFIER, TTYD64_MOVE_UNSIMPLIFIER, MOD_ABILITY_HOLDER_PLAYER, -1 },
    { TTYD64_ITEM_CHARGEP, TTYD64_MOVE_CHARGEP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_CLOSECALLP, TTYD64_MOVE_CLOSECALLP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_PRETTYLUCKYP, TTYD64_MOVE_PRETTYLUCKYP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_DAMAGEDODGEP, TTYD64_MOVE_DAMAGEDODGEP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_DEFENDPLUSP, TTYD64_MOVE_DEFENDPLUSP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_LASTSTANDP, TTYD64_MOVE_LASTSTANDP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_POWERPLUSP, TTYD64_MOVE_POWERPLUSP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_POWERRUSHP, TTYD64_MOVE_POWERRUSHP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_MEGARUSHP, TTYD64_MOVE_MEGARUSHP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_PDOWNDUPP, TTYD64_MOVE_PDOWNDUPP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_PUPDDOWNP, TTYD64_MOVE_PUPDDOWNP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_DOUBLEDIPP, TTYD64_MOVE_DOUBLEDIPP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_FEELINGFINEP, TTYD64_MOVE_FEELINGFINEP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_FLOWERSAVERP, TTYD64_MOVE_FLOWERSAVERP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_HAPPYHEARTP, TTYD64_MOVE_HAPPYHEARTP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_HPDRAINP, TTYD64_MOVE_HPDRAINP, MOD_ABILITY_HOLDER_PARTNER, -1 },
    { TTYD64_ITEM_HPPLUSP, TTYD64_MOVE_HPPLUSP, MOD_ABILITY_HOLDER_PARTNER, -1 },
};

s32 TTYD64_BadgeAbility(s32 itemID) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sBadgeAbilities); i++) {
        if (sBadgeAbilities[i].itemID == itemID) {
            return sBadgeAbilities[i].ability;
        }
    }
    return -1;
}

static void bs_register_abilities(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sBadgeAbilities); i++) {
        BadgeAbility* entry = &sBadgeAbilities[i];

        entry->ability = Mod_RegisterAbility(TTYD64_BS_OWNER, entry->moveID, entry->holder);
    }
}

void TTYD64_InstallBadgesStrats(void) {
    TTYD64_bs_MsgChargeDesc = Mod_RegisterInlineMessage(TTYD64_BS_OWNER, TTYD64_String_Charge_Desc);
    TTYD64_bs_MsgDefenseDesc = Mod_RegisterInlineMessage(TTYD64_BS_OWNER, TTYD64_String_Defense_Desc);
    TTYD64_MsgID_TooMuchBadges = Mod_RegisterInlineMessage(TTYD64_BS_OWNER, TTYD64_String_TooMuchBadges);
    TTYD64_mac_01_IntTable_80247E00[TTYD64_SHOP_MSG_TOO_MANY_BADGES] = TTYD64_MsgID_TooMuchBadges;
    bs_register_abilities();
    Mod_ReplaceScript(TTYD64_BS_OWNER, &EVS_PlayerHappy, &TTYD64_EVS_PlayerHappy_Patch);
    Mod_ReplaceScript(TTYD64_BS_OWNER, &EVS_StartDefend, &TTYD64_EVS_StartDefend_Patch);
    Mod_ReplaceScript(TTYD64_BS_OWNER, &EVS_Mario_HandlePhase, &TTYD64_EVS_Mario_HandlePhase_Patch);
    Mod_ReplaceScript(TTYD64_BS_OWNER, &EVS_RunAwayStart, &TTYD64_EVS_RunAwayStart_Patch);
    TTYD64_InstallBadgesBattle();
    TTYD64_InstallBadgesStratsMenu();
    TTYD64_InstallBadgesWorld();
}
