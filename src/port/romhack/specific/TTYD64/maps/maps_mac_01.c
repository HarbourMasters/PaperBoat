#include "common.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/maps/maps.h"

#define MAC_01_FLAG_BADGE_BOUGHT  ((s32) 0xF8407200)
#define MAC_01_FLAG_SALE_SLOT     ((s32) 0xF8406BFA)
#define MAC_01_FLAG_SALE_INIT     ((s32) 0xF8405C87)
#define MAC_01_BYTE_SALE_COUNT    ((s32) 0xF5DE01AC)
#define MAC_01_SALE_SLOTS_OFFSET  0x2E
#define MAC_01_SOLD_BADGES_OFFSET 0xFC
#define MAC_01_SOLD_BADGES_COUNT  0x82
#define MAC_01_SHOP_ROWS          0x12

static s32 sTTYD64_mac_01_AvailableIndexes[MAC_01_SHOP_ROWS];

static s32 TTYD64_mac_01_ShopRow(s32 row, s32 field) {
    const u8* p = &TTYD64_Data_ShopInventory[row * 0x10 + field * 4];

    return (s32) (((u32) p[0] << 24) | ((u32) p[1] << 16) | ((u32) p[2] << 8) | (u32) p[3]);
}

static void TTYD64_mac_01_SetShopEntityFlags(b32 set) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (evt_get_variable(NULL, MAC_01_FLAG_SALE_SLOT + i) == 0) {
            if (set) {
                set_item_entity_flags(gGameStatusPtr->shopItemEntities[i].index, 0x40);
            } else {
                clear_item_entity_flags(gGameStatusPtr->shopItemEntities[i].index, 0x40);
            }
        }
    }
}

API_CALLABLE(TTYD64_mac_01_Function_80244CC0_2) {
    TTYD64_mac_01_SetShopEntityFlags(false);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_mac_01_Function_80244D68_2) {
    TTYD64_mac_01_SetShopEntityFlags(true);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_mac_01_Function_802463E0_2) {
    TTYD64_mac_01_SetShopEntityFlags(true);
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_mac_01_Function_AllBadgesHasBeenBought) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (evt_get_variable(NULL, MAC_01_FLAG_BADGE_BOUGHT + i) == 0) {
            count++;
        }
    }
    script->varTable[0] = count;
    return ApiStatus_DONE2;
}

API_CALLABLE(TTYD64_mac_01_Function_SetVarFromVar) {
    Bytecode* args = script->ptrReadPos;
    Bytecode var = evt_get_variable(script, args[0]);
    Bytecode value = evt_get_variable(script, args[1]);

    evt_set_variable(script, var, value);
    return ApiStatus_DONE2;
}

static s32 TTYD64_mac_01_GetSoldItemOffset(s32 itemID) {
    s32 i;

    for (i = 0; i < MAC_01_SOLD_BADGES_COUNT; i++) {
        if ((s16) TTYD64_ReadBE(TTYD64_ModBytes(), MAC_01_SOLD_BADGES_OFFSET + 2 * i, 2) == itemID) {
            return MAC_01_SOLD_BADGES_OFFSET + 2 * i;
        }
    }
    return -1;
}

API_CALLABLE(TTYD64_mac_01_Function_SetSaleBadgeGlobalFlag) {
    s32 slot = evt_get_variable(script, *script->ptrReadPos);
    s32* saleFlags = (s32*) evt_get_variable(NULL, MapVar(2));
    s32 entry;
    s32 offset;

    set_item_entity_flags(gGameStatusPtr->shopItemEntities[slot].index, 0x40);
    entry = saleFlags[slot];
    if ((u32) entry < 0x200) {
        offset = TTYD64_mac_01_GetSoldItemOffset(entry);
        if (offset >= 0) {
            TTYD64_WriteBE(TTYD64_ModBytes(), offset, 2, 0);
        }
    } else {
        evt_set_variable(NULL, entry, 1);
    }
    return ApiStatus_DONE2;
}

typedef struct TTYD64_mac_01_SaleState {
    s32 soldCount;
    s32 placed;
    s32* saleFlags;
    s32* out;
} TTYD64_mac_01_SaleState;

static s32 TTYD64_mac_01_PlaceShopEntry(s32* out, s32 itemID, s32 price) {
    out[0] = itemID;
    out[1] = price - (price * 3) / 10;
    out[2] = gItemTable[itemID].shortDescMsg;
    return itemID;
}

static s32 TTYD64_mac_01_GetAvailableBadgeSold(TTYD64_mac_01_SaleState* st) {
    s32 roll;
    s32 itemID;
    s32 slotOffset;

    if (st->soldCount == 0) {
        return 0;
    }
    TTYD64_pause_sort_item_list(gPlayerData.badges, 0x80, TTYD64_pause_badges_comparator);
    roll = rand_int(st->soldCount - 1);
    while (true) {
        slotOffset = MAC_01_SOLD_BADGES_OFFSET + roll * 2;
        itemID = (u16) TTYD64_ReadBE(TTYD64_ModBytes(), slotOffset, 2);
        if (!TTYD64_Function_IsThisSoldBadgeOnSale(itemID)) {
            break;
        }
        roll = rand_int(TTYD64_get_sold_badges_amount() - 1);
    }
    TTYD64_mac_01_PlaceShopEntry(st->out, itemID, (u16) gItemTable[itemID].sellValue * 2);
    itemID = (u16) TTYD64_ReadBE(TTYD64_ModBytes(), slotOffset, 2);
    TTYD64_WriteBE(TTYD64_ModBytes(), MAC_01_SALE_SLOTS_OFFSET + st->placed * 2, 2, itemID);
    *st->saleFlags = itemID;
    if (st->soldCount > 0) {
        st->soldCount--;
    }
    st->placed++;
    st->saleFlags++;
    st->out += 3;
    return st->placed < 5 ? 1 : 2;
}

API_CALLABLE(TTYD64_mac_01_Function_InitSaleInventory) {
    s32* inventory = heap_malloc(0x174);
    s32* saleFlags = heap_malloc(0x14);
    TTYD64_mac_01_SaleState st;
    s32 available;
    s32 last;
    s32 i;
    s32 pick;
    s32 index;
    s32 count;
    s32 target;
    s32* out;
    s32* flagsOut;
    s32 entry;

    mem_clear(inventory, 0x174);
    saleFlags[0] = 0;
    saleFlags[1] = 0;
    saleFlags[2] = 0;
    saleFlags[3] = 0;
    saleFlags[4] = 0;
    st.soldCount = TTYD64_get_sold_badges_amount();
    TTYD64_Function_SortSoldBadges();
    evt_set_variable(NULL, MapVar(2), (Bytecode) saleFlags);
    st.placed = 0;

    if (evt_get_variable(NULL, MAC_01_FLAG_SALE_INIT) == 0) {
        available = 0;
        for (i = 0; i < MAC_01_SHOP_ROWS; i++) {
            if (evt_get_variable(NULL, GameByte(0)) < TTYD64_mac_01_ShopRow(i, 1)) {
                continue;
            }
            if (evt_get_variable(NULL, MAC_01_FLAG_BADGE_BOUGHT + i) != 0) {
                continue;
            }
            sTTYD64_mac_01_AvailableIndexes[available] = i;
            available++;
        }

        st.out = inventory;
        st.saleFlags = saleFlags;
        if (available == 0) {
            if (st.soldCount != 0) {
                while (TTYD64_mac_01_GetAvailableBadgeSold(&st) != 2) {
                    if (st.soldCount == 0) {
                        break;
                    }
                }
            }
        } else {
            last = available - 1;
            while (true) {
                if (st.soldCount != 0) {
                    if (available == 1 && st.placed != 4) {
                        target = 5 - st.placed - 1;
                        if ((u32) st.soldCount < (u32) target) {
                            target = st.soldCount;
                        }
                        count = 0;
                        while (true) {
                            if (TTYD64_mac_01_GetAvailableBadgeSold(&st) == 2) {
                                goto done_init;
                            }
                            count++;
                            if (count == target) {
                                break;
                            }
                        }
                    }
                    if ((u32) rand_int(100) < 40 && st.soldCount != 0) {
                        if (TTYD64_mac_01_GetAvailableBadgeSold(&st) == 2) {
                            goto done_init;
                        }
                    }
                }
                pick = rand_int(last);
                index = sTTYD64_mac_01_AvailableIndexes[pick];
                TTYD64_mac_01_PlaceShopEntry(st.out, TTYD64_mac_01_ShopRow(index, 0), TTYD64_mac_01_ShopRow(index, 3));
                TTYD64_WriteBE(TTYD64_ModBytes(), MAC_01_SALE_SLOTS_OFFSET + st.placed * 2, 2, index);
                st.placed++;
                *st.saleFlags = MAC_01_FLAG_BADGE_BOUGHT + index;
                st.saleFlags++;
                st.out += 3;
                if (st.placed >= 5) {
                    break;
                }
                for (i = pick; i < last; i++) {
                    sTTYD64_mac_01_AvailableIndexes[i] = sTTYD64_mac_01_AvailableIndexes[i + 1];
                }
                available--;
                last--;
                if (available == 0) {
                    break;
                }
            }
        }
    done_init:
        evt_set_variable(script, MAC_01_BYTE_SALE_COUNT, st.placed);
        evt_set_variable(script, MAC_01_FLAG_SALE_INIT, 1);
        script->varTable[3] = 0;
    } else {
        st.placed = evt_get_variable(script, MAC_01_BYTE_SALE_COUNT);
        out = inventory;
        flagsOut = saleFlags;
        for (i = 0; i < st.placed; i++) {
            index = (u16) TTYD64_ReadBE(TTYD64_ModBytes(), MAC_01_SALE_SLOTS_OFFSET + i * 2, 2);
            if ((u32) index < 0xE0) {
                TTYD64_mac_01_PlaceShopEntry(out, TTYD64_mac_01_ShopRow(index, 0), TTYD64_mac_01_ShopRow(index, 3));
                entry = MAC_01_FLAG_BADGE_BOUGHT + index;
            } else {
                TTYD64_mac_01_PlaceShopEntry(out, index, (u16) gItemTable[index].sellValue * 2);
                entry = index;
            }
            out += 3;
            *flagsOut = entry;
            flagsOut++;
        }
        script->varTable[3] = 1;
    }
    script->varTable[0] = st.placed;
    script->varTable[1] = (Bytecode) saleFlags;
    script->varTable[2] = (Bytecode) inventory;
    return ApiStatus_DONE2;
}
