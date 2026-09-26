#include "common.h"
#include "pause/pause_common.h"
#include "port/patches/Patches.h"

static const struct { s16 pauseMsg; s16 palIndex; } sPalMenuMsgs[] = {
    { PAUSE_MSG_LBL_COINS, 0x039 },
    { PAUSE_MSG_LBL_STAR_POINTS, 0x03A },
    { PAUSE_MSG_LBL_STAR_PIECES, 0x03B },
    { PAUSE_MSG_LBL_TIME, 0x03C },
    { PAUSE_MSG_LBL_HP, 0x03D },
    { PAUSE_MSG_LBL_FP, 0x03E },
    { PAUSE_MSG_LBL_BP, 0x03F },
    { PAUSE_MSG_SLASH, 0x040 },
    { PAUSE_MSG_DOT, 0x041 },
    { PAUSE_MSG_3C, 0x042 },
    { PAUSE_MSG_3D, 0x043 },
    { PAUSE_MSG_3E, 0x044 },
    { PAUSE_MSG_40, 0x045 },
    { PAUSE_MSG_41, 0x046 },
    { PAUSE_MSG_42, 0x047 },
    { PAUSE_MSG_MARIO, 0x048 },
    { PAUSE_MSG_LEVEL, 0x049 },
    { PAUSE_MSG_BADGE_BP, 0x03F },
    { PAUSE_MSG_ALL_BADGES, 0x04A },
    { PAUSE_MSG_ACTIVE, 0x04C },
    { PAUSE_MSG_BADGES, 0x04D },
    { PAUSE_MSG_NOT_ENOUGH_BP, 0x04E },
    { PAUSE_MSG_DONT_WEAR_MORE, 0x04F },
    { PAUSE_MSG_KEY_ITEMS, 0x051 },
    { PAUSE_MSG_CONSUMABLES, 0x050 },
    { PAUSE_MSG_PARTNER_HP, 0x03D },
    { PAUSE_MSG_PARTNER_FP, 0x03E },
    { PAUSE_MSG_PARTNER_ABILITIES, 0x053 },
    { PAUSE_MSG_UNKNOWN_SPIRIT, 0x054 },};

intptr_t port_pause_menu_msg(s32 index) {
    s32 i;

    for (i = 0; i < (s32) ARRAY_COUNT(sPalMenuMsgs); i++) {
        if (sPalMenuMsgs[i].pauseMsg == index) {
            return (intptr_t) port_msg_pal_menu_asset(sPalMenuMsgs[i].palIndex);
        }
    }
    return 0;
}
