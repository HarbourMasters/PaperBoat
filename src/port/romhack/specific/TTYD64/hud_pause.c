#include "port/romhack/specific/TTYD64/hud_pause_internal.h"
#include "port/hooks/Events.h"
#include "port/modding/WindowStyles.h"

extern HudElementList gHudElementsWorld;
extern HudElementList gHudElementsBattle;

TTYD64ShineBox TTYD64_ShineBox;

s32 TTYD64_hp_BoxStyleBase = WINDOW_STYLE_0;

const DefaultWindowStyle TTYD64_hp_BoxStyles[4] = {
    { 0x01, 0x08, 0x01, { 0xED, 0x87, 0x87, 0xFF }, { 0x69, 0x29, 0x29, 0xFF } },
    { 0x01, 0x08, 0x01, { 0xE8, 0xE7, 0xA2, 0xFF }, { 0x61, 0x60, 0x38, 0xFF } },
    { 0x01, 0x08, 0x01, { 0x98, 0xC8, 0xA6, 0xFF }, { 0x42, 0x4D, 0x3F, 0xFF } },
    { 0x01, 0x08, 0x01, { 0xEF, 0xC4, 0xA8, 0xFF }, { 0x4D, 0x89, 0x8D, 0xFF } },
};

static HudElement* hp_get_element(s32 hid) {
    HudElementList* list;
    s32 index;

    if (gGameStatus.context == CONTEXT_WORLD) {
        list = &gHudElementsWorld;
        index = hid;
    } else {
        list = &gHudElementsBattle;
        index = hid - 0x80D + 0xD;
    }
    if ((u32) index >= ARRAY_COUNT(*list)) {
        return nullptr;
    }
    return (*list)[index];
}

s32 TTYD64_CreateIcon(HudScript* script) {
    s32 hid = hud_element_create(script);

    hud_element_set_flags(hid, HUD_ELEMENT_FLAG_MANUAL_RENDER);
    hud_element_clear_flags(hid, 0xFFFF8000);
    hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FIXED_SIZE);
    return hid;
}

void TTYD64_SetIconSize(s32 hid, f32 width, f32 height) {
    HudElement* elem = hp_get_element(hid);

    if (elem == nullptr) {
        return;
    }
    elem->dynamicSize.x = width;
    elem->dynamicSize.y = height;
}

void TTYD64_hp_SetIconPalette(s32 hid, u32 rgb) {
    HudElement* elem = hp_get_element(hid);

    if (elem == nullptr) {
        return;
    }
    elem->tint.r = rgb >> 24;
    elem->tint.g = (rgb << 8) >> 24;
    elem->tint.b = (rgb << 16) >> 24;
}

s32 TTYD64_Function_GetPartnersUnlocked(void) {
    s32 count = 0;
    s32 i;

    for (i = PARTNER_GOOMBARIO; i <= PARTNER_BOW; i++) {
        if (i == PARTNER_GOOMPA) {
            continue;
        }
        count += gPlayerData.partners[i].enabled;
    }
    return count;
}

s32 TTYD64_hp_IsPartnerHPCompatible(void) {
    switch ((u8) gPlayerData.curPartner) {
        case PARTNER_GOOMBARIO:
        case PARTNER_KOOPER:
        case PARTNER_BOMBETTE:
        case PARTNER_PARAKARRY:
        case PARTNER_BOW:
        case PARTNER_WATT:
        case PARTNER_SUSHIE:
        case PARTNER_LAKILESTER:
            return true;
    }
    return false;
}

s32 TTYD64_hp_GetIconIndexPartnerIcon(void) {
    switch ((u8) gPlayerData.curPartner) {
        case PARTNER_GOOMBARIO:
            return 5;
        case PARTNER_KOOPER:
            return 6;
        case PARTNER_BOMBETTE:
            return 7;
        case PARTNER_PARAKARRY:
            return 8;
        case PARTNER_BOW:
            return 9;
        case PARTNER_WATT:
            return 0xA;
        case PARTNER_SUSHIE:
            return 0xB;
        case PARTNER_LAKILESTER:
            return 0xC;
    }
    return 5;
}

u8* TTYD64_hp_PartnerHPBytes(s32 partnerID) {
    return (u8*) TTYD64_PartnerHPRecord(partnerID);
}

void TTYD64_hp_PlayHealSFX(void) {
    sfx_play_sound_with_params(SOUND_HEART_PICKUP, 0, 0, 0);
}

void TTYD64_hp_SyncPartnerHP(void) {
    s32 i;

    for (i = PARTNER_GOOMBARIO; i <= PARTNER_BOW; i++) {
        u8* bytes = TTYD64_hp_PartnerHPBytes(i);

        bytes[0] = bytes[1];
    }
}

void TTYD64_InstallHudPause(void) {
    TTYD64_hp_BoxStyleBase = Mod_RegisterWindowStyles("TTYD64", TTYD64_hp_BoxStyles, ARRAY_COUNT(TTYD64_hp_BoxStyles));
    if (TTYD64_hp_BoxStyleBase < 0) {
        GameEngine_LogWarn("TTYD64: window styles could not be registered");
        TTYD64_hp_BoxStyleBase = WINDOW_STYLE_0;
    } else if (TTYD64_hp_BoxStyleBase != 0x17) {
        GameEngine_LogWarn("TTYD64: window styles registered at %d, the ROM used 23", TTYD64_hp_BoxStyleBase);
    }
    TTYD64_hp_InstallStatusBar();
    TTYD64_hp_InstallPauseStats();
    TTYD64_hp_InstallPauseBadges();
    TTYD64_hp_InstallShine();
}
