#include "common.h"
#include "hud_element.h"
#include "entity.h"
#include "assets/level_up.h"

#if !VERSION_PAL
EntityModelScript EMS_level_up = STANDARD_ENTITY_MODEL_SCRIPT(level_up_chain_gfx, RENDER_MODE_CLOUD_NO_ZCMP);
#endif

HudScript HES_level_up_heart = HES_TEMPLATE_CI_ENUM_SIZE(level_up_heart, 40, 40);
HudScript HES_level_up_heart_copy = HES_TEMPLATE_CI_ENUM_SIZE(level_up_heart, 40, 40);
HudScript HES_level_up_flower = HES_TEMPLATE_CI_ENUM_SIZE(level_up_flower, 40, 40);
HudScript HES_level_up_leaves = HES_TEMPLATE_CI_ENUM_SIZE(level_up_leaves, 40, 40);
HudScript HES_level_up_badge = HES_TEMPLATE_CI_ENUM_SIZE(level_up_badge, 40, 40);

HudScript HES_level_up_FP = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_FP, 32, 24);
#if VERSION_PAL
HudScript HES_level_up_FP_de = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_FP_de, 32, 24);
HudScript HES_level_up_FP_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_FP_fr, 32, 24);
HudScript HES_level_up_FP_es = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_FP_es, 32, 24);
#endif
HudScript HES_level_up_green_digit_0 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_0, 8, 16);
HudScript HES_level_up_green_digit_1 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_1, 8, 16);
HudScript HES_level_up_green_digit_2 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_2, 8, 16);
HudScript HES_level_up_green_digit_3 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_3, 8, 16);
HudScript HES_level_up_green_digit_4 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_4, 8, 16);
HudScript HES_level_up_green_digit_5 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_5, 8, 16);
HudScript HES_level_up_green_digit_6 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_6, 8, 16);
HudScript HES_level_up_green_digit_7 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_7, 8, 16);
HudScript HES_level_up_green_digit_8 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_8, 8, 16);
HudScript HES_level_up_green_digit_9 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_9, 8, 16);
HudScript HES_level_up_small_green_digit_0 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_0, 8, 8);
HudScript HES_level_up_small_green_digit_1 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_1, 8, 8);
HudScript HES_level_up_small_green_digit_2 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_2, 8, 8);
HudScript HES_level_up_small_green_digit_3 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_3, 8, 8);
HudScript HES_level_up_small_green_digit_4 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_4, 8, 8);
HudScript HES_level_up_small_green_digit_5 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_5, 8, 8);
HudScript HES_level_up_small_green_digit_6 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_6, 8, 8);
HudScript HES_level_up_small_green_digit_7 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_7, 8, 8);
HudScript HES_level_up_small_green_digit_8 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_8, 8, 8);
HudScript HES_level_up_small_green_digit_9 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_9, 8, 8);
HudScript HES_level_up_small_green_arrow = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_arrow, 8, 8);

HudScript HES_level_up_HP = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_HP, 32, 24);
#if VERSION_PAL
HudScript HES_level_up_HP_de = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_HP_de, 32, 24);
HudScript HES_level_up_HP_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_HP_fr, 32, 24);
HudScript HES_level_up_HP_es = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_HP_es, 32, 24);
#endif
HudScript HES_level_up_red_digit_0 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_0_red, 8, 16);
HudScript HES_level_up_red_digit_1 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_1_red, 8, 16);
HudScript HES_level_up_red_digit_2 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_2_red, 8, 16);
HudScript HES_level_up_red_digit_3 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_3_red, 8, 16);
HudScript HES_level_up_red_digit_4 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_4_red, 8, 16);
HudScript HES_level_up_red_digit_5 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_5_red, 8, 16);
HudScript HES_level_up_red_digit_6 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_6_red, 8, 16);
HudScript HES_level_up_red_digit_7 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_7_red, 8, 16);
HudScript HES_level_up_red_digit_8 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_8_red, 8, 16);
HudScript HES_level_up_red_digit_9 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_9_red, 8, 16);
HudScript HES_level_up_small_red_digit_0 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_0_red, 8, 8);
HudScript HES_level_up_small_red_digit_1 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_1_red, 8, 8);
HudScript HES_level_up_small_red_digit_2 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_2_red, 8, 8);
HudScript HES_level_up_small_red_digit_3 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_3_red, 8, 8);
HudScript HES_level_up_small_red_digit_4 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_4_red, 8, 8);
HudScript HES_level_up_small_red_digit_5 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_5_red, 8, 8);
HudScript HES_level_up_small_red_digit_6 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_6_red, 8, 8);
HudScript HES_level_up_small_red_digit_7 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_7_red, 8, 8);
HudScript HES_level_up_small_red_digit_8 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_8_red, 8, 8);
HudScript HES_level_up_small_red_digit_9 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_9_red, 8, 8);
HudScript HES_level_up_small_red_arrow = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_arrow_red, 8, 8);

HudScript HES_level_up_BP = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_BP, 32, 24);
#if VERSION_PAL
HudScript HES_level_up_BP_de = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_BP_de, 32, 24);
HudScript HES_level_up_BP_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_BP_fr, 32, 24);
HudScript HES_level_up_BP_es = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_BP_es, 32, 24);
#endif
HudScript HES_level_up_blue_digit_0 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_0_blue, 8, 16);
HudScript HES_level_up_blue_digit_1 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_1_blue, 8, 16);
HudScript HES_level_up_blue_digit_2 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_2_blue, 8, 16);
HudScript HES_level_up_blue_digit_3 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_3_blue, 8, 16);
HudScript HES_level_up_blue_digit_4 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_4_blue, 8, 16);
HudScript HES_level_up_blue_digit_5 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_5_blue, 8, 16);
HudScript HES_level_up_blue_digit_6 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_6_blue, 8, 16);
HudScript HES_level_up_blue_digit_7 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_7_blue, 8, 16);
HudScript HES_level_up_blue_digit_8 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_8_blue, 8, 16);
HudScript HES_level_up_blue_digit_9 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_digit_9_blue, 8, 16);
HudScript HES_level_up_small_blue_digit_0 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_0_blue, 8, 8);
HudScript HES_level_up_small_blue_digit_1 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_1_blue, 8, 8);
HudScript HES_level_up_small_blue_digit_2 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_2_blue, 8, 8);
HudScript HES_level_up_small_blue_digit_3 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_3_blue, 8, 8);
HudScript HES_level_up_small_blue_digit_4 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_4_blue, 8, 8);
HudScript HES_level_up_small_blue_digit_5 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_5_blue, 8, 8);
HudScript HES_level_up_small_blue_digit_6 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_6_blue, 8, 8);
HudScript HES_level_up_small_blue_digit_7 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_7_blue, 8, 8);
HudScript HES_level_up_small_blue_digit_8 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_8_blue, 8, 8);
HudScript HES_level_up_small_blue_digit_9 = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_digit_9_blue, 8, 8);
HudScript HES_level_up_small_blue_arrow = HES_TEMPLATE_CI_ENUM_SIZE(level_up_small_arrow_blue, 8, 8);

HudScript HES_level_up_select_one_to_upgrade = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_select_one_to_upgrade, 208, 16);
#if VERSION_PAL
HudScript HES_level_up_select_one_to_upgrade_de = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_select_one_to_upgrade_de, 208, 16);
HudScript HES_level_up_select_one_to_upgrade_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_select_one_to_upgrade_fr, 208, 16);
HudScript HES_level_up_select_one_to_upgrade_es = HES_TEMPLATE_CI_CUSTOM_SIZE(level_up_select_one_to_upgrade_es, 208, 16);
#endif
