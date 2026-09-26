#include "common.h"
#include "hud_element.h"
#include "assets/ui_pal.h"
#include "port/patches/Patches.h"

HudScript HES_PortHeaderStats_de = HES_TEMPLATE_CI_CUSTOM_SIZE(de_ui_pause_label_stats, 48, 16);
HudScript HES_PortHeaderBadges_de = HES_TEMPLATE_CI_CUSTOM_SIZE(de_ui_pause_label_badges, 48, 16);
HudScript HES_PortHeaderItems_de = HES_TEMPLATE_CI_CUSTOM_SIZE(de_ui_pause_label_items, 48, 16);
HudScript HES_PortHeaderParty_de = HES_TEMPLATE_CI_CUSTOM_SIZE(de_ui_pause_label_party, 48, 16);
HudScript HES_PortHeaderSpirits_de = HES_TEMPLATE_CI_CUSTOM_SIZE(de_ui_pause_label_spirits, 48, 16);
HudScript HES_PortHeaderMap_de = HES_TEMPLATE_CI_CUSTOM_SIZE(de_ui_pause_label_map, 48, 16);

HudScript HES_PortHeaderStats_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(fr_ui_pause_label_stats, 48, 16);
HudScript HES_PortHeaderBadges_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(fr_ui_pause_label_badges, 48, 16);
HudScript HES_PortHeaderItems_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(fr_ui_pause_label_items, 48, 16);
HudScript HES_PortHeaderParty_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(fr_ui_pause_label_party, 48, 16);
HudScript HES_PortHeaderSpirits_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(fr_ui_pause_label_spirits, 48, 16);
HudScript HES_PortHeaderMap_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(fr_ui_pause_label_map, 48, 16);

HudScript HES_PortHeaderStats_es = HES_TEMPLATE_CI_CUSTOM_SIZE(es_ui_pause_label_stats, 48, 16);
HudScript HES_PortHeaderBadges_es = HES_TEMPLATE_CI_CUSTOM_SIZE(es_ui_pause_label_badges, 48, 16);
HudScript HES_PortHeaderItems_es = HES_TEMPLATE_CI_CUSTOM_SIZE(es_ui_pause_label_items, 48, 16);
HudScript HES_PortHeaderParty_es = HES_TEMPLATE_CI_CUSTOM_SIZE(es_ui_pause_label_party, 48, 16);
HudScript HES_PortHeaderSpirits_es = HES_TEMPLATE_CI_CUSTOM_SIZE(es_ui_pause_label_spirits, 48, 16);
HudScript HES_PortHeaderMap_es = HES_TEMPLATE_CI_CUSTOM_SIZE(es_ui_pause_label_map, 48, 16);

static HudScript* sPauseTabScripts[][6] = {
    [LANGUAGE_DE] = {
        &HES_PortHeaderStats_de, &HES_PortHeaderBadges_de, &HES_PortHeaderItems_de,
        &HES_PortHeaderParty_de, &HES_PortHeaderSpirits_de, &HES_PortHeaderMap_de
    },
    [LANGUAGE_FR] = {
        &HES_PortHeaderStats_fr, &HES_PortHeaderBadges_fr, &HES_PortHeaderItems_fr,
        &HES_PortHeaderParty_fr, &HES_PortHeaderSpirits_fr, &HES_PortHeaderMap_fr
    },
    [LANGUAGE_ES] = {
        &HES_PortHeaderStats_es, &HES_PortHeaderBadges_es, &HES_PortHeaderItems_es,
        &HES_PortHeaderParty_es, &HES_PortHeaderSpirits_es, &HES_PortHeaderMap_es
    },
};

HudScript* port_pause_tab_hud_script(s32 index, HudScript* fallback) {
    s32 language = port_msg_language();

    if (language <= LANGUAGE_EN || language >= (s32) ARRAY_COUNT(sPauseTabScripts)) {
        return fallback;
    }
    if (index < 0 || index >= (s32) ARRAY_COUNT(sPauseTabScripts[0])) {
        return fallback;
    }
    return sPauseTabScripts[language][index];
}
