#include "common.h"
#include "effects.h"
#include "hud_element.h"
#include "npc.h"
#include "dx/versioning.h"
#include "port/Engine.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_rawmem.h"
#include "../include/ttyd64_symbols.h"
#include "world_lib.h"
#include "world_lib_gen.h"
#include <string.h>

#define SOLD_BADGES_OFFSET       0xFC
#define SOLD_BADGES_COUNT        130
#define SOLD_BADGES_N64_ADDR     0x803560FC
#define SHOP_ROW_SIZE            0x10
#define SHOP_INVENTORY_SIZE      0x124
#define PAGE_ROWS                30
#define FLAG_GF_MAC01_BADGE1     ((s32) 0xF8407200)
#define FLAG_RowfBadgeAvailableA ((s32) 0xF8406BFA)
#define BYTE_STORY_PROGRESS      ((s32) 0xF5DE0180)

extern s32 gPopupState;
extern s32 PopupDelayTime;
extern s32 PopupMenu_SelectedIndex;
extern IconHudScriptPair gItemHudScripts[];
extern SaveFileSummary gSaveSlotSummary[4];

s32 TTYD64_Data_ShopInventory_CurrentPage[PAGE_ROWS][4];
static u8 sPushTattleFlags[0x34];
static u8 sPushModFlags[0x18];
static u8 sPushModBytes[0x110];

static s16 sold_get(s32 i) {
    return (s16) TTYD64_ReadBE(TTYD64_ModBytes(), SOLD_BADGES_OFFSET + 2 * i, 2);
}

static void sold_set(s32 i, s32 value) {
    TTYD64_WriteBE(TTYD64_ModBytes(), SOLD_BADGES_OFFSET + 2 * i, 2, value);
}

static s32 shop_row(s32 row, s32 field) {
    if (row * SHOP_ROW_SIZE + field * 4 + 4 > SHOP_INVENTORY_SIZE) {
        return -1;
    }
    return TTYD64_ReadBE(TTYD64_Data_ShopInventory, row * SHOP_ROW_SIZE + field * 4, 4);
}

static s32* sale_table(void) {
    return (s32*) evt_get_variable(NULL, MapVar(2));
}

static s32 get_others_badges_amount(void) {
    s32 invIdx = 0;
    s32 count = 0;
    s32 row = 0;
    s32 i;
    s32 notOnSale;

    do {
        if (evt_get_variable(NULL, invIdx + FLAG_GF_MAC01_BADGE1) != 0) {
            invIdx++;
        } else if (evt_get_variable(NULL, BYTE_STORY_PROGRESS) < shop_row(row, 1)) {
            invIdx++;
        } else {
            invIdx++;
            count++;
        }
        row++;
    } while (shop_row(row, 0) != -1);

    for (i = 0; i < SOLD_BADGES_COUNT; i++) {
        if (sold_get(i) != 0) {
            count++;
        }
    }

    notOnSale = 5;
    for (i = 0; i < 5; i++) {
        notOnSale -= evt_get_variable(NULL, FLAG_RowfBadgeAvailableA + i);
    }
    return count - notOnSale;
}

s32 TTYD64_get_sold_badges_amount(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < SOLD_BADGES_COUNT; i++) {
        if (sold_get(i) != 0) {
            count++;
        }
    }
    return count;
}

static s32 get_player_badges_amount(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 128; i++) {
        if ((u16) gPlayerData.badges[i] != 0) {
            count++;
        }
    }
    return count;
}

void TTYD64_Function_SortSoldBadges(void) {
    s32 i;
    s32 j;
    u16 badge;

    if (TTYD64_get_sold_badges_amount() == 0) {
        return;
    }
    for (i = 0; i < SOLD_BADGES_COUNT; i++) {
        if ((u16) sold_get(i) != 0) {
            continue;
        }
        for (j = i; j < SOLD_BADGES_COUNT; j++) {
            badge = sold_get(j);
            if (badge != 0) {
                sold_set(j, 0);
                sold_set(i, badge);
                break;
            }
        }
        if (j >= SOLD_BADGES_COUNT) {
            return;
        }
    }
}

static b32 find_sold_badge(s32 badgeID) {
    s32 i;

    for (i = 0; i < SOLD_BADGES_COUNT; i++) {
        if (badgeID == (u16) sold_get(i)) {
            return 1;
        }
    }
    return 0;
}

s32 TTYD64_add_badge_to_sold_inventory(s32 badgeID) {
    s32 i;

    if (find_sold_badge(badgeID)) {
        return -1;
    }
    TTYD64_Function_SortSoldBadges();
    for (i = 0; i < SOLD_BADGES_COUNT; i++) {
        if (sold_get(i) == 0) {
            sold_set(i, badgeID);
            return badgeID;
        }
    }
    return -1;
}

static b32 is_sold_badge_on_sale(s32 itemID, b32 checkFlag) {
    s32* table;
    s32 entry;
    s32 i;

    if (itemID == 0) {
        return 0;
    }
    table = sale_table();
    for (i = 1; i <= 5; i++) {
        entry = table[i - 1];
        if (entry == 0 || (u32) entry < 0xBF || entry != itemID) {
            continue;
        }
        if (!checkFlag || evt_get_variable(NULL, FLAG_RowfBadgeAvailableA + (i - 1)) == 0) {
            return 1;
        }
    }
    return 0;
}

b32 TTYD64_Function_IsThisSoldBadgeOnSale(s32 itemID) {
    return is_sold_badge_on_sale(itemID, 0);
}

API_CALLABLE(TTYD64_Function_Inventory_ClearPageData) {
    s32 i;

    for (i = 1; i < PAGE_ROWS; i++) {
        TTYD64_Data_ShopInventory_CurrentPage[i - 1][0] = 0;
        TTYD64_Data_ShopInventory_CurrentPage[i - 1][1] = 0;
        TTYD64_Data_ShopInventory_CurrentPage[i - 1][2] = 0;
        TTYD64_Data_ShopInventory_CurrentPage[i - 1][3] = 0;
    }
    return isInitialCall ? script->curArgc : script->blocked;
}

API_CALLABLE(TTYD64_Function_GetTypeOfBadge) {
    Bytecode* args = script->ptrReadPos;
    s32 flag = evt_get_variable(script, args[0]);

    evt_set_variable(script, args[1], (flag & 0x7F000000) ? 0 : 1);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_GetOtherBadgesAmount) {
    evt_set_variable(script, *script->ptrReadPos, get_others_badges_amount());
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_GetPlayerBadgesAmount) {
    evt_set_variable(script, *script->ptrReadPos, get_player_badges_amount());
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_GetSoldBadgesAmount) {
    evt_set_variable(script, *script->ptrReadPos, TTYD64_get_sold_badges_amount());
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_AddBadgeToSoldInventory) {
    TTYD64_add_badge_to_sold_inventory(evt_get_variable(script, *script->ptrReadPos));
    return ApiStatus_DONE2;
}

typedef struct ShopCursor {
    s32 row;
    s32 invIdx;
    s32 soldIdx;
    s32 inSold;
} ShopCursor;

static void get_current_page_start(s32 page, ShopCursor* c) {
    s32 counted = 0;
    s32 target = page * PAGE_ROWS + 1;

    do {
        if (evt_get_variable(NULL, c->invIdx + FLAG_GF_MAC01_BADGE1) != 0) {
            c->invIdx++;
        } else if (evt_get_variable(NULL, BYTE_STORY_PROGRESS) < shop_row(c->row, 1)) {
            c->invIdx++;
        } else {
            c->invIdx++;
            counted++;
            c->inSold = 0;
            if (counted == target) {
                return;
            }
        }
        c->row++;
    } while (shop_row(c->row, 0) != -1);

    for (c->soldIdx = 0; c->soldIdx < SOLD_BADGES_COUNT; c->soldIdx++) {
        if (sold_get(c->soldIdx) != 0) {
            counted++;
            c->inSold = 1;
            if (counted == target) {
                return;
            }
        }
    }
}

static void shop_extra_set(Evt* script, s32 show) {
    if (script != NULL) {
        memcpy(&TTYD64_Data_Shop_ExtraData[0], &script, sizeof(script));
    }
    TTYD64_WriteBE(TTYD64_Data_Shop_ExtraData, sizeof(void*), 4, show);
}

static ApiStatus shop_popup_step(Evt* script) {
    PopupMenu* popup = script->functionTempPtr[2];
    s32 page;
    s32 pages;
    u32 stick;
    s32 sel;
    s32 itemID;

    if (script->functionTemp[0] == 0) {
        if (script->varTable[11] != 0) {
            shop_extra_set(script, 1);
        }
        if (gPopupState == 1 && PopupDelayTime == 0 && !(gWindows[WIN_POPUP_CONTENT].updateCounter < 9)
            && (pages = script->varTable[11]) != 0)
        {
            page = script->varTable[10];
            stick = (gGameStatusPtr->pressedButtons[0] >> 16) & 0xFF;
            if (page != 0 && (stick & 4)) {
                script->varTable[3] = page;
                popup->result = 0xFF;
            } else if (page != pages && (stick & 8)) {
                script->varTable[3] = page + 2;
                popup->result = 0xFF;
            }
        }
        script->functionTemp[1] = popup->result;
        if (popup->result == 0) {
            return ApiStatus_BLOCK;
        }
        hide_popup_menu();
        TTYD64_WriteBE(TTYD64_Data_Shop_ExtraData, sizeof(void*), 4, 0);
    }
    script->functionTemp[0] = (s32) script->functionTemp[0] + 1;
    if ((s32) script->functionTemp[0] < 20) {
        return ApiStatus_BLOCK;
    }
    destroy_popup_menu();
    if (script->functionTemp[1] != 0xFF) {
        sel = PopupMenu_SelectedIndex;
        itemID = TTYD64_Data_ShopInventory_CurrentPage[sel][0];
        script->varTable[0] = itemID;
        script->varTable[2] = sel;
        script->varTable[1] = TTYD64_Data_ShopInventory_CurrentPage[sel][3];
        script->varTable[4] = gItemTable[itemID].nameMsg;
        script->varTable[6] = TTYD64_Data_ShopInventory_CurrentPage[sel][2];
        script->varTable[5] = gMoveTable[gItemTable[TTYD64_Data_ShopInventory_CurrentPage[sel][0]].moveID].costBP;
    } else {
        script->varTable[0] = -1;
    }
    heap_free(script->functionTempPtr[2]);
    return ApiStatus_DONE2;
}

static void popup_add_entry(PopupMenu* popup, s32 entry, s32 userIndex, s32 itemID, s32 price) {
    ItemData* item = &gItemTable[itemID];
    IconHudScriptPair* icons = &gItemHudScripts[item->hudElemID];

    popup->userIndex[entry] = userIndex;
    popup->descMsg[entry] = item->shortDescMsg;
    popup->nameMsg[entry] = item->nameMsg;
    popup->ptrIcon[entry] = icons->enabled;
    popup->enabled[entry] = !((u16) gPlayerData.coins < price);
    if ((u16) gPlayerData.coins < price) {
        popup->ptrIcon[entry] = icons->disabled;
        popup->enabled[entry] = 0;
    }
    popup->value[entry] = price;
}

API_CALLABLE(TTYD64_Function_ShowInventory_Others) {
    PopupMenu* popup;
    ShopCursor c;
    s32 count;
    s32 out;
    s32 i;
    s32* sale;
    b32 skip;
    s32 itemID;
    s32 price;

    if (isInitialCall) {
        if (script->varTable[3] != 0) {
            script->varTable[10] = (s32) script->varTable[3] - 1;
            script->varTable[3] = 0;
        }
        popup = heap_malloc(sizeof(PopupMenu));
        script->functionTempPtr[2] = popup;
        count = 0;
        out = 0;
        c.row = 0;
        c.invIdx = 0;
        c.soldIdx = 0;
        c.inSold = 0;
        script->varTable[11] = get_others_badges_amount() / 31;
        if (script->varTable[10] != 0) {
            get_current_page_start(script->varTable[10], &c);
        }
        if (!c.inSold) {
            do {
                if (evt_get_variable(NULL, c.invIdx + FLAG_GF_MAC01_BADGE1) != 0) {
                    c.invIdx++;
                } else if (evt_get_variable(NULL, BYTE_STORY_PROGRESS) < shop_row(c.row, 1)) {
                    c.invIdx++;
                } else {
                    sale = sale_table();
                    skip = 0;
                    for (i = 0; i < 5; i++) {
                        if (c.invIdx + FLAG_GF_MAC01_BADGE1 == sale[i]) {
                            skip = 1;
                            break;
                        }
                    }
                    if (skip) {
                        c.invIdx++;
                    } else {
                        for (i = 0; i < 4; i++) {
                            TTYD64_Data_ShopInventory_CurrentPage[out][i] = shop_row(c.row, i);
                        }
                        out++;
                        popup_add_entry(popup, count, c.invIdx, shop_row(c.row, 0), shop_row(c.row, 3));
                        count++;
                        c.invIdx++;
                    }
                }
                if (count >= PAGE_ROWS) {
                    goto create;
                }
                c.row++;
            } while (shop_row(c.row, 0) != -1);
            c.soldIdx = 0;
        }
        for (; c.soldIdx < SOLD_BADGES_COUNT; c.soldIdx++) {
            itemID = sold_get(c.soldIdx);
            if (itemID != 0 && !is_sold_badge_on_sale(itemID, 1)) {
                price = (u16) gItemTable[itemID].sellValue * 2;
                TTYD64_Data_ShopInventory_CurrentPage[out][0] = itemID;
                TTYD64_Data_ShopInventory_CurrentPage[out][1] = -128;
                TTYD64_Data_ShopInventory_CurrentPage[out][2] = SOLD_BADGES_N64_ADDR + c.soldIdx * 2;
                TTYD64_Data_ShopInventory_CurrentPage[out][3] = price;
                out++;
                popup_add_entry(popup, count, c.soldIdx, itemID, price);
                count++;
            }
            if (count >= PAGE_ROWS) {
                break;
            }
        }
    create:
        popup->popupType = 5;
        popup->numEntries = count;
        popup->initialPos = 0;
        create_standard_popup_menu(popup);
        script->functionTemp[0] = 0;
    }
    return shop_popup_step(script);
}

API_CALLABLE(TTYD64_Function_ShowInventory_PlayerBadges) {
    PopupMenu* popup;
    s32 count;
    s32 out;
    s32 idx;
    s32 userIndex;
    s32 itemID;
    ItemData* item;
    u16 price;

    if (isInitialCall) {
        TTYD64_pause_sort_item_list(gPlayerData.badges, 128, TTYD64_pause_badges_comparator);
        if (script->varTable[3] != 0) {
            script->varTable[10] = (s32) script->varTable[3] - 1;
            script->varTable[3] = 0;
        }
        popup = heap_malloc(sizeof(PopupMenu));
        script->functionTempPtr[2] = popup;
        count = 0;
        out = 0;
        idx = 0;
        userIndex = 0;
        script->varTable[11] = get_player_badges_amount() / 31;
        if (script->varTable[10] != 0) {
            idx = script->varTable[10] * PAGE_ROWS;
            userIndex = idx * 2;
        }
        do {
            itemID = gPlayerData.badges[idx];
            if (itemID != 0) {
                item = &gItemTable[itemID];
                popup->userIndex[count] = userIndex;
                popup->descMsg[count] = item->shortDescMsg;
                popup->nameMsg[count] = item->nameMsg;
                popup->ptrIcon[count] = gItemHudScripts[item->hudElemID].enabled;
                price = item->sellValue;
                TTYD64_Data_ShopInventory_CurrentPage[out][0] = gPlayerData.badges[idx];
                TTYD64_Data_ShopInventory_CurrentPage[out][1] = -128;
                TTYD64_Data_ShopInventory_CurrentPage[out][2] = 0;
                TTYD64_Data_ShopInventory_CurrentPage[out][3] = price;
                out++;
                popup->enabled[count] = 1;
                count++;
                popup->value[count - 1] = price;
            }
            if (count >= PAGE_ROWS) {
                break;
            }
            idx++;
        } while ((u32) idx < 128);
        popup->popupType = 5;
        popup->numEntries = count;
        popup->initialPos = 0;
        create_standard_popup_menu(popup);
        script->functionTemp[0] = 0;
    }
    return shop_popup_step(script);
}

s32 TTYD64_pause_badges_comparator(s16* a, s16* b) {
    s16 va = *a == 0 ? 0x7FFF : gItemTable[*a].sortValue;
    s16 vb = *b == 0 ? 0x7FFF : gItemTable[*b].sortValue;

    if (va == vb) {
        return 0;
    }
    return va < vb ? -1 : 1;
}

void TTYD64_pause_sort_item_list(s16* itemList, s32 listLength, s32 (*comparator)(s16*, s16*)) {
    u32 gap = 1;
    s16* end;
    s16* windowEnd;
    s16* cur;
    s16 tmp;

    if (listLength < 2) {
        return;
    }
    if (listLength == 2) {
        if (comparator(&itemList[0], &itemList[1]) > 0) {
            tmp = itemList[0];
            itemList[0] = itemList[1];
            itemList[1] = tmp;
        }
        return;
    }
    while (gap < (u32) listLength) {
        gap = gap * 2 + 1;
    }
    end = &itemList[listLength];
    while ((gap /= 2) != 0) {
        for (windowEnd = &itemList[gap]; windowEnd < end; windowEnd++) {
            cur = windowEnd - gap;
            while (cur >= itemList && cur < end) {
                if (comparator(cur, cur + gap) <= 0) {
                    break;
                }
                tmp = *cur;
                *cur = cur[gap];
                cur[gap] = tmp;
                cur -= gap;
            }
        }
    }
}

static s32 upgrade_partner_rank(s32 partnerID, s16 maxLevel) {
    PartnerData* p = &gPlayerData.partners[partnerID];

    if (!p->enabled) {
        return -1;
    }
    if (maxLevel < p->level) {
        return -1;
    }
    return p->level;
}

API_CALLABLE(TTYD64_Function_UpgradePartner) {
    Bytecode* args = script->ptrReadPos;
    s32 partnerID = evt_get_variable(script, *args++);
    Bytecode outVar = *args++;

    gPlayerData.partners[partnerID].level++;
    evt_set_variable(script, outVar, gPlayerData.partners[partnerID].level);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_SetMessageString_CurrentPartner) {
    set_message_text_var(gPartnerPopupProperties[gPlayerData.curPartner].nameMsg, 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_GetPartnersAbleToUpgrade) {
    s16 hasUltraStone = script->varTable[12] >= 0;
    s32 i;

    script->varTable[0] = -1;
    for (i = 1; i < 12; i++) {
        if (gPlayerData.partners[i].enabled && upgrade_partner_rank(i, hasUltraStone) != -1) {
            script->varTable[0] = 1;
            break;
        }
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_OpenSuperBlockMenu) {
    PopupMenu* popup;
    s32 hasUltraStone;
    s32 entry;
    s32 i;
    s32 partnerID;
    s32 rank;

    if (isInitialCall) {
        popup = heap_malloc(sizeof(PopupMenu));
        entry = 0;
        script->functionTempPtr[2] = popup;
        hasUltraStone = script->varTable[12] >= 0;
        for (i = 0; i < 8; i++) {
            partnerID = (s16) TTYD64_ReadBE(TTYD64_Data_80243D38, i * 2, 2);
            if (!gPlayerData.partners[partnerID].enabled) {
                continue;
            }
            popup->userIndex[entry] = partnerID;
            popup->nameMsg[entry] = gPartnerPopupProperties[partnerID].nameMsg;
            rank = upgrade_partner_rank(partnerID, hasUltraStone);
            if (rank >= 0) {
                popup->ptrIcon[entry] = wPartnerHudScripts[partnerID];
                popup->enabled[entry] = 1;
                popup->descMsg[entry] = TTYD64_ReadBE(TTYD64_StringTable_PartnersUpgrades, rank * 4 + i * 8, 4);
            } else {
                popup->ptrIcon[entry] = wDisabledPartnerHudScripts[partnerID];
                popup->enabled[entry] = 0;
                popup->descMsg[entry] = TTYD64_ReadBE(TTYD64_StringsTable_AlreadyRanked, hasUltraStone * 4, 4);
            }
            popup->value[entry] = gPlayerData.partners[partnerID].level;
            entry++;
        }
        popup->popupType = 4;
        popup->numEntries = entry;
        popup->initialPos = 0;
        create_standard_popup_menu(popup);
        script->functionTemp[0] = 0;
    }

    popup = script->functionTempPtr[2];
    if (script->functionTemp[0] == 0) {
        script->functionTemp[1] = popup->result;
        if (popup->result == 0) {
            return ApiStatus_BLOCK;
        }
        TTYD64_ShineBox.state = 2;
        TTYD64_ShineBox.offset = 7;
        hide_popup_menu();
    }
    script->functionTemp[0] = (s32) script->functionTemp[0] + 1;
    if ((s32) script->functionTemp[0] < 15) {
        return ApiStatus_BLOCK;
    }
    destroy_popup_menu();
    if (script->functionTemp[1] != 0xFF) {
        script->varTable[0] = gPartnerPopupProperties[popup->userIndex[script->functionTemp[1] - 1]].nameMsg;
        script->varTable[1] = popup->userIndex[script->functionTemp[1] - 1];
    } else {
        script->varTable[0] = -1;
    }
    heap_free(script->functionTempPtr[2]);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_SwitchToPartner) {
    switch_to_partner(evt_get_variable(script, *script->ptrReadPos));
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_ChangeScreenColorOverlay) {
    Bytecode* args = script->ptrReadPos;
    s32 ret = ApiStatus_BLOCK;
    s32 v;

    if (isInitialCall) {
        script->varTable[0] = evt_get_variable(script, *args++);
        script->varTable[1] = evt_get_variable(script, *args++);
        script->functionTemp[0] = 0;
        script->functionTemp[1] = 0;
        set_screen_overlay_color(0, 208, 208, 208);
    }

    switch (script->functionTemp[0]) {
        case 0:
            if (script->functionTemp[1] == 255) {
                script->functionTemp[0] = 1;
                script->functionTemp[2] = 0;
            }
            v = (s32) script->functionTemp[1] + (s32) script->varTable[0];
            script->functionTemp[1] = v;
            if (!(v < 256)) {
                script->functionTemp[1] = 255;
            }
            break;
        case 1:
            v = (s32) script->functionTemp[2] + 1;
            script->functionTemp[2] = v;
            if (!(v < 2)) {
                script->functionTemp[0] = 2;
            }
            break;
        case 2:
            if (script->functionTemp[1] == 0) {
                ret = ApiStatus_DONE1;
            }
            v = (s32) script->functionTemp[1] - (s32) script->varTable[1];
            script->functionTemp[1] = v;
            if (v < 0) {
                script->functionTemp[1] = 0;
            }
            break;
    }
    set_screen_overlay_params_front(1, (s32) script->functionTemp[1]);
    return ret;
}

API_CALLABLE(TTYD64_Function_PlayFX_33_RadialFlowOut) {
    Npc* npc = get_npc_safe(NPC_PARTNER);

    fx_radial_shimmer(9, npc->pos.x, npc->pos.y + 12.5f, npc->pos.z, 1.0f, 30);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_PlayFX_11_Sparkles_Random) {
    Npc* npc = get_npc_safe(NPC_PARTNER);

    fx_sparkles(2, npc->pos.x, npc->pos.y + 30.0f, npc->pos.z, 30.0f);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_PlayFX_11_Sparkles_Type4) {
    Npc* npc = get_npc_safe(NPC_PARTNER);

    fx_sparkles(4, npc->pos.x, npc->pos.y + 30.0f, npc->pos.z, 30.0f);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_Function_InitNewGamePlusData) {
    PlayerData* playerData = &gPlayerData;
    u32* modFlags = TTYD64_ModFlagWords();
    u8* modBytes = TTYD64_ModBytes();
    s32 runs = modBytes[0x0A];
    SaveFileSummary* summary;
    u32 name;

    playerData->curHP = 10;
    playerData->curMaxHP = 10;
    playerData->curFP = 10;
    playerData->curMaxFP = 10;
    playerData->maxBP = 3;
    playerData->bootsLevel = 0;
    playerData->hammerLevel = -1;
    playerData->level = 1;
    playerData->starPieces = 0;
    playerData->starPoints = 0;
    playerData->curPartner = 0;
    TTYD64_ShineSprites = 0;
    playerData->maxStarPower = 0;
    playerData->starPower = 0;
    mem_clear(playerData->keyItems, 0x40);
    mem_clear(&playerData->partners[1], 0x48);
    mem_clear(&TTYD64_PartnerHPRecords[1], 9 * sizeof(TTYD64_PartnerHPRecords[0]));
    sync_status_bar();
    close_status_bar();

    mem_clear(sPushTattleFlags, 0x20);
    mem_clear(sPushModFlags, 0x14);
    mem_clear(sPushModBytes, 0x10D);

    memcpy(sPushTattleFlags, &gCurrentSaveFile.globalBytes[0x16C], 0x20);
    memcpy(&sPushTattleFlags[0x24], &gCurrentSaveFile.unk_1304[0x1C], 0x0C);
    memcpy(TTYD64_String_Merlon_AskConfirmation, &gCurrentSaveFile.unk_1304[0x28], 4);
    memcpy(sPushModBytes, modBytes, 0x0C);
    memcpy(&sPushModBytes[0x0C], &modBytes[0xFC], 0x100);

    clear_saved_variables();

    memcpy(&gCurrentSaveFile.globalBytes[0x16C], sPushTattleFlags, 0x20);
    modFlags[0] = TTYD64_ReadBE(sPushModFlags, 0x0, 4);
    modFlags[0xE4 / 4] = TTYD64_ReadBE(sPushModFlags, 0x4, 4);
    modFlags[0xE8 / 4] = TTYD64_ReadBE(sPushModFlags, 0x8, 4);
    modFlags[0xEC / 4] = TTYD64_ReadBE(sPushModFlags, 0xC, 4);
    modFlags[0xF0 / 4] = TTYD64_ReadBE(sPushModFlags, 0x10, 4);
    memcpy(modBytes, sPushModBytes, 0x0C);
    memcpy(&modBytes[0xFC], &sPushModBytes[0x0C], 0x100);

    switch (gGameStatusPtr->saveSlot) {
        case 1:
            summary = &gSaveSlotSummary[1];
            break;
        case 2:
            summary = &gSaveSlotSummary[2];
            break;
        default:
            summary = &gSaveSlotSummary[3];
            break;
    }
    name = runs < 10 ? (0x270B1000 | (runs << 8)) : 0x270B1900;
    summary->filename[0] = 0x2E;
    summary->filename[1] = name >> 24;
    summary->filename[2] = name >> 16;
    summary->filename[3] = name >> 8;
    summary->filename[4] = name;

    set_message_text_var(gPartnerPopupProperties[gPlayerData.curPartner].nameMsg, 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_WorldLib_FindKeyItem) {
    Bytecode* args = script->ptrReadPos;
    s32 itemID = evt_get_variable(script, *args++);
    Bytecode outVar = *args++;
    PlayerData* playerData = &gPlayerData;
    s32 i;
    s32 itemIndex;

    for (i = 0; i < ARRAY_COUNT(playerData->keyItems); i++) {
        if (playerData->keyItems[i] == itemID) {
            break;
        }
    }

    itemIndex = -1;
    if (i != ARRAY_COUNT(playerData->keyItems)) {
        itemIndex = i;
    }

    evt_set_variable(script, outVar, itemIndex);
    return ApiStatus_DONE2;
}
