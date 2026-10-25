#include "port/romhack/specific/TTYD64/partner_hp_internal.h"
#include "battle/battle_menu.h"
#include "port/modding/Mod.h"
#include "pause/pause_common.h"

extern EvtScript EVS_World_UseItem;
extern EvtScript TTYD64_ph_EVS_World_UseItem;

static s32 sMsgPartnerDead;

typedef struct TTYD64HealBoxCursor {
    u8 target;
    u8 lastRow;
} TTYD64HealBoxCursor;

static TTYD64HealBoxCursor sHealBoxCursor;

API_CALLABLE(TTYD64_GetHealBoxTarget) {
    evt_set_variable(script, *script->ptrReadPos, sHealBoxCursor.target);
    return ApiStatus_DONE2;
}

static const u8* ph_partner_hp_data(s32 msgID) {
    switch (msgID) {
        case 0x1D0007:
            return (u8*) TTYD64_PartnerHPRecord(1);
        case 0x1D0008:
            return (u8*) TTYD64_PartnerHPRecord(2);
        case 0x1D0009:
            return (u8*) TTYD64_PartnerHPRecord(3);
        case 0x1D000A:
            return (u8*) TTYD64_PartnerHPRecord(4);
        case 0x1D000F:
            return (u8*) TTYD64_PartnerHPRecord(9);
        case 0x1D000C:
            return (u8*) TTYD64_PartnerHPRecord(6);
        case 0x1D000D:
            return (u8*) TTYD64_PartnerHPRecord(7);
        case 0x1D000E:
            return (u8*) TTYD64_PartnerHPRecord(8);
    }
    return nullptr;
}

static void ph_draw_hp_numbers(s32 curHP, s32 maxHP, s32 x, s32 y, s32 dark, s32 drawLabel) {
    s32 palette = dark ? 0 : 0xA;
    s32 digitsX;

    if (drawLabel) {
        draw_msg((intptr_t) (dark ? TTYD64_String_HP_B : TTYD64_String_HP_W), x + 0x53, y - 2, 0xFF, -1, 0);
    }
    digitsX = (u32) curHP < 10 ? x + 0x68 : x + 0x61;
    draw_number(curHP, digitsX, y, 1, palette, 0xFF, 0);
    draw_msg((intptr_t) (dark ? TTYD64_String_Slash_B : TTYD64_String_Slash_W), x + 0x72, y - 2, 0xFF, palette, 0);
    draw_number(maxHP, x + 0x7D, y, 1, palette, 0xFF, 0);
}

static void ph_draw_partner_hp_by_id(s32 partnerID, s32 x, s32 y, s32 dark, s32 drawLabel) {
    const u8* data;

    switch (partnerID) {
        case PARTNER_GOOMBARIO:
        case PARTNER_KOOPER:
        case PARTNER_BOMBETTE:
        case PARTNER_PARAKARRY:
        case PARTNER_WATT:
        case PARTNER_SUSHIE:
        case PARTNER_LAKILESTER:
        case PARTNER_BOW:
            break;
        default:
            return;
    }
    data = (u8*) TTYD64_PartnerHPRecord(partnerID);
    ph_draw_hp_numbers(data[1], data[2], x, y, dark, drawLabel);
}

void TTYD64_ph_DrawPartnerHP(s32 msgID, s32 x, s32 y, s32 dark, s32 drawLabel) {
    const u8* data = ph_partner_hp_data(msgID);

    if (data == nullptr) {
        return;
    }
    ph_draw_hp_numbers(data[1], data[2], x, y, dark, drawLabel);
}

void TTYD64_ph_DrawMarioHP(s32 x, s32 y, s32 dark) {
    ph_draw_hp_numbers((u8) gPlayerData.curHP, (u8) gPlayerData.curMaxHP, x, y, dark, true);
}

static void ph_heal_box_set_order_list(void) {
    u8* order = TTYD64_HealingBox_PartnersOrder;
    s32 count = 1;
    s32 partnerID;
    s32 index;
    s32 record;

    memset(order, 0, 8);
    partnerID = (u8) gPlayerData.curPartner;
    if (partnerID == PARTNER_BOW) {
        partnerID = 5;
    }
    order[1] = partnerID;
    index = 0;
    record = 1;
    while (true) {
        index++;
        if (gPlayerData.partners[record].enabled != 0 && index != order[1]) {
            count++;
            order[count] = index;
        }
        if (record == 9) {
            record = 5;
        }
        record++;
        if (record == 5) {
            record = 9;
            continue;
        }
        if (record > 8) {
            break;
        }
    }
}

static HudScript* const sHealBoxIconScripts[] = {
    &TTYD64_IconScript_Mario,      &TTYD64_IconScript_Goombario, &TTYD64_IconScript_Kooper, &TTYD64_IconScript_Bombette,
    &TTYD64_IconScript_Parakarry,  &TTYD64_IconScript_Bow,       &TTYD64_IconScript_Watt,   &TTYD64_IconScript_Sushie,
    &TTYD64_IconScript_Lakilester, &TTYD64_IconScript_Cursor,
};

static HudElemID sHealBoxIcons[ARRAY_COUNT(sHealBoxIconScripts)];

static void ph_heal_box_reset(void) {
    memset(TTYD64_HealingBox_PartnersOrder, 0, sizeof(TTYD64_HealingBox_PartnersOrder));
    sHealBoxCursor.target = 0;
    sHealBoxCursor.lastRow = 0;
}

static s32 ph_heal_box_icon(s32 slot) {
    return sHealBoxIcons[slot];
}

static void ph_heal_box_open(PopupMenu* menu) {
    s32 i;

    ph_heal_box_reset();
    for (i = 0; i < ARRAY_COUNT(sHealBoxIconScripts); i++) {
        sHealBoxIcons[i] = TTYD64_CreateIcon(sHealBoxIconScripts[i]);
    }
    ph_heal_box_set_order_list();
}

static void ph_heal_box_close(PopupMenu* menu, s32 result) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sHealBoxIcons); i++) {
        hud_element_free(sHealBoxIcons[i]);
    }
}

static s32 ph_heal_box_frame(PopupMenu* menu, s32 acceptInput) {
    const s16 boxX = TTYD64_HealingBox_Data[0];
    const s16 boxY = TTYD64_HealingBox_Data[1];
    TTYD64HealBoxCursor* cursor = &sHealBoxCursor;
    u8* order = TTYD64_HealingBox_PartnersOrder;
    u32 pressed;
    s32 numPartners;
    s32 sizeY;
    s32 i;
    s32 posY;
    s32 msgID;
    s32 iconID;
    s32 cursorPos;

    numPartners = TTYD64_Function_GetPartnersUnlocked();
    cursor->lastRow = numPartners;
    sizeY = numPartners < 7 ? 0x18 : 0x19;
    sizeY -= numPartners;
    sizeY += sizeY * numPartners;
    TTYD64_DrawBox(boxX, boxY, 0xB8, sizeY, 3, 0xFF);
    TTYD64_DrawBox(boxX - 0x62, boxY + 0xA, 0x5F, 0x30, 0, 0xFF);
    draw_msg((intptr_t) TTYD64_String_HealBox_LeftBox, boxX - 0x50, boxY + 0x10, 0xFF, -1, 0);

    posY = 0x41;
    i = 0;
    do {
        posY += i == 2 ? 0x13 : 0xF;
        iconID = ph_heal_box_icon(order[i]);
        hud_element_set_render_pos(iconID, boxX + 0x1B, posY);
        TTYD64_SetIconSize(iconID, 18.0f, 18.0f);
        hud_element_draw_next(iconID);
        i++;
    } while (!((u32) cursor->lastRow < (u32) i));

    posY = 0x3A;
    i = 0;
    do {
        posY += i == 2 ? 0x13 : 0xF;
        msgID = TTYD64_HealingBox_Strings[order[i]];
        draw_msg(msgID, boxX + 0x25, posY, 0xFF, 0xA, 0);
        if (i == 2) {
            draw_msg((intptr_t) TTYD64_String_Separator, boxX + 0x25 - 0x16, posY - 0xB, 0xFF, 0xA, 0);
        }
        if (msgID == 0x1D0013) {
            TTYD64_ph_DrawMarioHP(boxX + 0x25 - 1, posY + 2, false);
        } else {
            TTYD64_ph_DrawPartnerHP(msgID, boxX + 0x25 - 1, posY + 2, false, true);
        }
        i++;
    } while (!((u32) cursor->lastRow < (u32) i));

    cursorPos = cursor->target;
    posY = 0x52 + 0xF * cursorPos;
    if (cursorPos >= 2) {
        posY += 3;
    }
    iconID = ph_heal_box_icon(9);
    hud_element_set_render_pos(iconID, boxX + 0xA, posY);
    TTYD64_SetIconSize(iconID, 16.0f, 16.0f);
    hud_element_draw_next(iconID);

    if (!acceptInput) {
        return MOD_POPUP_PANEL_STAY;
    }
    pressed = gGameStatus.pressedButtons[0];
    if ((pressed & BUTTON_STICK_UP) || (pressed & BUTTON_Z)) {
        cursorPos = cursor->target - 1;
        if (cursorPos < 0) {
            cursorPos = cursor->lastRow;
        }
        cursor->target = cursorPos;
        sfx_play_sound_with_params(0xC7, 0, 0, 0);
    } else if ((pressed & BUTTON_STICK_DOWN) || (pressed & BUTTON_R)) {
        cursorPos = cursor->target + 1;
        if ((s32) cursor->lastRow < cursorPos) {
            cursorPos = 0;
        }
        cursor->target = cursorPos;
        sfx_play_sound_with_params(0xC7, 0, 0, 0);
    } else if (pressed & BUTTON_B) {
        sfx_play_sound_with_params(0xCA, 0, 0, 0);
        return MOD_POPUP_PANEL_BACK;
    } else if (pressed & BUTTON_A) {
        sfx_play_sound_with_params(0xC9, 0, 0, 0);
        return MOD_POPUP_PANEL_CHOSE;
    }
    return MOD_POPUP_PANEL_STAY;
}

static const ModPopupPanelOps sHealBoxOps = {
    .open = ph_heal_box_open,
    .frame = ph_heal_box_frame,
    .close = ph_heal_box_close,
};

static void ph_on_player_recover(IEvent* event) {
    OnActorHpChange* ev = (OnActorHpChange*) event;
    s32 hp;

    switch (ev->source) {
        case HP_SOURCE_FULL_RESTORE:
            if (TTYD64_Function_GetPartnersUnlocked() != 0) {
                TTYD64_Function_HealPartners();
            }
            break;
        case HP_SOURCE_HEART_BLOCK:
            gPlayerData.starPower = (u8) gPlayerData.maxStarPower << 8;
            if (TTYD64_Function_GetPartnersUnlocked() != 0) {
                TTYD64_Function_HealPartners();
            }
            break;
        case HP_SOURCE_FIELD_HEART:
            hp = TTYD64_GetPartnerHP();
            if (hp < 0) {
                break;
            }
            hp++;
            if ((u32) TTYD64_GetPartnerMaxHP() < (u32) hp) {
                break;
            }
            TTYD64_SetPartnerHP(hp);
            break;
    }
}

static void ph_on_popup_menu(IEvent* event) {
    OnPopupMenu* ev = (OnPopupMenu*) event;

    if (ev->phase != POPUP_MENU_LAID_OUT || ev->menu->popupType != POPUP_MENU_SWITCH_PARTNER) {
        return;
    }
    if ((u8) gGameStatus.context == CONTEXT_BATTLE) {
        gWindows[WIN_POPUP_CONTENT].width = 0xB5;
        gWindows[WIN_POPUP_TITLE_B].pos.x = 0x25;
    } else if (TTYD64_Function_GetPartnersUnlocked() != 0) {
        gWindows[WIN_POPUP_CONTENT].pos.x = 0x5B;
        gWindows[WIN_POPUP_CONTENT].width = 0xD0;
        gWindows[WIN_POPUP_TITLE_B].pos.x = 0x2D;
        gWindows[WIN_POPUP_PROMPT].pos.y = 0x158;
    }
}

static void ph_on_popup_menu_layout(IEvent* event) {
    OnPopupMenuLayout* ev = (OnPopupMenuLayout*) event;

    if (ev->menu->popupType != POPUP_MENU_SWITCH_PARTNER) {
        return;
    }
    ev->layout->contentScissorWidth = 0xCA;
    ev->layout->partnerLevelX = 0x9A;
    ev->layout->partnerScissorWidth = 0x70;
    ev->layout->arrowOffsetX = 0x45;
}

static void ph_on_popup_menu_draw_entry(IEvent* event) {
    OnPopupMenuDrawEntry* ev = (OnPopupMenuDrawEntry*) event;

    if (ev->menu->popupType != POPUP_MENU_SWITCH_PARTNER) {
        return;
    }
    TTYD64_ph_DrawPartnerHP(ev->menu->nameMsg[ev->index], ev->x - 2, ev->y, false, true);
}

static void ph_on_popup_menu_choose(IEvent* event) {
    OnPopupMenuChoose* ev = (OnPopupMenuChoose*) event;

    if ((u8) gGameStatus.context != CONTEXT_WORLD) {
        return;
    }
    if (ev->menu->popupType != POPUP_MENU_USE_ITEM) {
        return;
    }
    if ((u8) PopupNotBattle == 0) {
        return;
    }
    if (TTYD64_Function_GetPartnersUnlocked() == 0) {
        ph_heal_box_reset();
        return;
    }
    if (Mod_OpenPopupPanel("TTYD64", ev->menu, &sHealBoxOps) == 0) {
        event->Cancelled = true;
    } else {
        sHealBoxCursor.target = 0;
    }
}

static void ph_on_popup_menu_text(IEvent* event) {
    OnPopupMenuText* ev = (OnPopupMenuText*) event;
    s32 partnerID = 0;

    if (ev->text != POPUP_TEXT_ALREADY_HAVE_PARTNER) {
        return;
    }
    if ((u8) gGameStatus.context != CONTEXT_BATTLE) {
        return;
    }
    if (PopupMenu_SelectedIndex >= 0 && PopupMenu_SelectedIndex < ev->menu->numEntries) {
        partnerID = ev->menu->userIndex[PopupMenu_SelectedIndex];
    }
    if (TTYD64_ModBytes()[TTYD64_MB_GameMode] == 1 || TTYD64_GetPartnerHP_byID(partnerID) <= 0) {
        *ev->msgID = sMsgPartnerDead;
    }
}

static void ph_on_pause_label_pos(IEvent* event) {
    OnPauseLabelPos* ev = (OnPauseLabelPos*) event;

    if (ev->label != PAUSE_LBL_ABILITIES) {
        return;
    }
    *ev->x = 0xA0;
    *ev->y = 0xA8;
}

static void ph_on_pause_partners_overlay(IEvent* event) {
    OnPausePartnersOverlay* ev = (OnPausePartnersOverlay*) event;
    s32 offsetX = 0;
    s32 offsetY = 0;
    s32 heartID;

    if (gWindows[WIN_PAUSE_PARTNERS].updateCounter >= 6) {
        offsetX = TTYD64_PartyMenu_FlipOffsets[0];
        offsetY = TTYD64_PartyMenu_FlipOffsets[1];
    }
    TTYD64_DrawBox(0x14 + offsetX, 0x79 + offsetY, 0x56, 0x1C, TTYD64_hp_BoxStyleBase, 0xFF);
    ph_draw_partner_hp_by_id(ev->partnerID, -0x31 + offsetX, 0x81 + offsetY, true, false);
    heartID = TTYD64_hp_PauseIcon(TTYD64_HP_PAUSE_ICON_HEART);
    hud_element_set_render_pos(heartID, 0x26 + offsetX, 0x86 + offsetY);
    TTYD64_SetIconSize(heartID, 22.0f, 22.0f);
    hud_element_draw_next(heartID);
}

static void ph_on_partner_change(IEvent* event) {
    OnPartnerChange* ev = (OnPartnerChange*) event;

    if (ev->phase == PARTNER_CHANGE_ENTER && gGameStatusPtr->context == CONTEXT_WORLD) {
        TTYD64_sync_status_menu_OnlyPartners();
    }
}

static int32_t ph_item_capacity(void) {
    return find_item(TTYD64_ITEM_STRANGESACK) >= 0 ? 20 : 10;
}

void TTYD64_InstallPartnerHPWorld(void) {
    REGISTER_LISTENER(OnActorHpChange, EVENT_PRIORITY_NORMAL, ph_on_player_recover);
    sMsgPartnerDead = TTYD64_ph_InlineMsg(TTYD64_String_PartnerDead);
    REGISTER_LISTENER(OnPopupMenu, EVENT_PRIORITY_NORMAL, ph_on_popup_menu);
    REGISTER_LISTENER(OnPopupMenuLayout, EVENT_PRIORITY_NORMAL, ph_on_popup_menu_layout);
    REGISTER_LISTENER(OnPopupMenuDrawEntry, EVENT_PRIORITY_NORMAL, ph_on_popup_menu_draw_entry);
    REGISTER_LISTENER(OnPopupMenuChoose, EVENT_PRIORITY_NORMAL, ph_on_popup_menu_choose);
    REGISTER_LISTENER(OnPopupMenuText, EVENT_PRIORITY_NORMAL, ph_on_popup_menu_text);
    REGISTER_LISTENER(OnPauseLabelPos, EVENT_PRIORITY_NORMAL, ph_on_pause_label_pos);
    REGISTER_LISTENER(OnPausePartnersOverlay, EVENT_PRIORITY_NORMAL, ph_on_pause_partners_overlay);
    REGISTER_LISTENER(OnPartnerChange, EVENT_PRIORITY_NORMAL, ph_on_partner_change);
    Mod_SetItemCapacity("TTYD64", ph_item_capacity);
    Mod_ReplaceScript("TTYD64", &EVS_World_UseItem, &TTYD64_ph_EVS_World_UseItem);
}
