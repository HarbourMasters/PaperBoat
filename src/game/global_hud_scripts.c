#include "common.h"
#include "hud_element.h"
#include "sparkle_script.h"
#include "assets/ui.h"

Gfx D_801041A0[] = {
    gsSPEndDisplayList(),
};

Gfx D_801045A8[] = {
    gsSPEndDisplayList(),
};

HudScript HES_ArrowLeft = HES_TEMPLATE_CI_ENUM_SIZE(ui_arrow_left, 16, 16);

HudScript HES_ArrowRight = HES_TEMPLATE_CI_ENUM_SIZE(ui_arrow_right, 16, 16);

HudScript HES_HandPointer = HES_TEMPLATE_CI_ENUM_SIZE(ui_point_right, 16, 16);

HudScript HES_AnimatedHandPointer = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_16x16)
    hs_Loop
        hs_AddTexelOffsetX(-1)
        hs_SetCI(4, ui_point_right)
        hs_AddTexelOffsetX(1)
        hs_SetCI(8, ui_point_right)
    hs_Restart
    hs_End
};

HudScript HES_FilledCircle = HES_TEMPLATE_CI_ENUM_SIZE(ui_pip, 8, 8);

HudScript HES_EmptyCircle = HES_TEMPLATE_CI_ENUM_SIZE(ui_pip2, 8, 8);

SparkleScript SparkleScript_Coin = {
    sp_Break(13)
    sp_SetCI(1, ui_coin_sparkle_0, 8, 8)
    sp_SetCI(1, ui_coin_sparkle_1, 8, 8)
    sp_SetCI(1, ui_coin_sparkle_2, 8, 8)
    sp_SetCI(2, ui_coin_sparkle_none, 8, 8)
    sp_SetCI(1, ui_coin_sparkle_2, 8, 8)
    sp_SetCI(1, ui_coin_sparkle_3, 8, 8)
    sp_SetCI(1, ui_coin_sparkle_none, 8, 8)
    sp_SetCI(1, ui_coin_sparkle_4, 8, 8)
    sp_SetCI(1, ui_coin_sparkle_none, 8, 8)
    sp_SetCI(1, ui_coin_sparkle_5, 8, 8)
    sp_SetCI(127, ui_coin_sparkle_none, 8, 8)
    sp_SetCI(127, ui_coin_sparkle_none, 8, 8)
    sp_End
};

HudScript HES_StatusSPShine = {
    hs_UseIA8
    hs_SetTileSize(HUD_ELEMENT_SIZE_24x24)
    hs_Loop
        hs_SetRGBA(60, ui_status_star_point_shine_png)
    hs_Restart
    hs_End
};

HudScript HES_StatusStarPiece = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_16x16)
    hs_Loop
        hs_SetCI(12, ui_status_star_piece_0)
        hs_SetCI(4, ui_status_star_piece_1)
        hs_SetCI(12, ui_status_star_piece_2)
        hs_SetCI(4, ui_status_star_piece_1)
    hs_Restart
    hs_End
};

HudScript HES_AsleepLoop = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_Loop
        hs_SetCI(8, ui_battle_status_sleep_0)
        hs_SetCI(4, ui_battle_status_sleep_1)
        hs_SetCI(8, ui_battle_status_sleep_2)
        hs_SetCI(4, ui_battle_status_sleep_1)
    hs_Restart
    hs_End
};

HudScript HES_AsleepBegin = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_Loop
        hs_SetCI(8, ui_battle_status_sleep_0)
        hs_SetCI(4, ui_battle_status_sleep_1)
        hs_SetCI(8, ui_battle_status_sleep_2)
        hs_SetCI(4, ui_battle_status_sleep_1)
    hs_Restart
    hs_End
};

HudScript HES_AsleepEnd = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_sleep_0)
    hs_End
};

HudScript HES_ElectrifiedLoop = {
    hs_SetVisible
    hs_SetCustomSize( 16, 16)
    hs_Loop
        hs_SetCI(24,ui_battle_status_static_0)
        hs_SetCI(1, ui_battle_status_static_1)
        hs_SetCI(1, ui_battle_status_static_0)
        hs_SetCI(1, ui_battle_status_static_1)
        hs_SetCI(49,ui_battle_status_static_0)
        hs_SetCI(1, ui_battle_status_static_1)
        hs_SetCI(1, ui_battle_status_static_0)
        hs_SetCI_Explicit(1, ui_battle_status_static_1, ui_battle_status_static_0)
        hs_SetCI_Explicit(1, ui_battle_status_static_0, ui_battle_status_static_1)
        hs_SetCI_Explicit(1, ui_battle_status_static_1, ui_battle_status_static_0)
        hs_SetCI_Explicit(1, ui_battle_status_static_0, ui_battle_status_static_1)
        hs_SetCI_Explicit(1, ui_battle_status_static_1, ui_battle_status_static_0)
        hs_SetCI_Explicit(1, ui_battle_status_static_0, ui_battle_status_static_1)
    hs_Restart
    hs_End
};

HudScript HES_ElectrifiedBegin = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_Loop
        hs_SetCI(24,ui_battle_status_static_0)
        hs_SetCI(1, ui_battle_status_static_1)
        hs_SetCI(1, ui_battle_status_static_0)
        hs_SetCI(1, ui_battle_status_static_1)
        hs_SetCI(49,ui_battle_status_static_0)
        hs_SetCI(1, ui_battle_status_static_1)
        hs_SetCI(1, ui_battle_status_static_0)
        hs_SetCI_Explicit(1, ui_battle_status_static_1, ui_battle_status_static_0)
        hs_SetCI_Explicit(1, ui_battle_status_static_0, ui_battle_status_static_1)
        hs_SetCI_Explicit(1, ui_battle_status_static_1, ui_battle_status_static_0)
        hs_SetCI_Explicit(1, ui_battle_status_static_0, ui_battle_status_static_1)
        hs_SetCI_Explicit(1, ui_battle_status_static_1, ui_battle_status_static_0)
        hs_SetCI_Explicit(1, ui_battle_status_static_0, ui_battle_status_static_1)
    hs_Restart
    hs_End
};

HudScript HES_ElectrifiedEnd = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_static_0)
    hs_End
};

HudScript HES_ParalyzedLoop = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_Loop
        hs_SetCI(24,ui_battle_status_paralyze_0)
        hs_SetCI(1, ui_battle_status_paralyze_1)
        hs_SetCI(1, ui_battle_status_paralyze_0)
        hs_SetCI(1, ui_battle_status_paralyze_1)
        hs_SetCI(49,ui_battle_status_paralyze_0)
        hs_SetCI(1, ui_battle_status_paralyze_1)
        hs_SetCI(1, ui_battle_status_paralyze_0)
        hs_SetCI_Explicit(1, ui_battle_status_paralyze_1, ui_battle_status_paralyze_0)
        hs_SetCI_Explicit(1, ui_battle_status_paralyze_0, ui_battle_status_paralyze_1)
        hs_SetCI_Explicit(1, ui_battle_status_paralyze_1, ui_battle_status_paralyze_0)
        hs_SetCI_Explicit(1, ui_battle_status_paralyze_0, ui_battle_status_paralyze_1)
        hs_SetCI_Explicit(1, ui_battle_status_paralyze_1, ui_battle_status_paralyze_0)
        hs_SetCI_Explicit(1, ui_battle_status_paralyze_0, ui_battle_status_paralyze_1)
    hs_Restart
    hs_End
};

HudScript HES_ParalyzedBegin = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_Loop
        hs_SetCI(24,ui_battle_status_paralyze_0)
        hs_SetCI(1, ui_battle_status_paralyze_1)
        hs_SetCI(1, ui_battle_status_paralyze_0)
        hs_SetCI(1, ui_battle_status_paralyze_1)
        hs_SetCI(49,ui_battle_status_paralyze_0)
        hs_SetCI(1, ui_battle_status_paralyze_1)
        hs_SetCI(1, ui_battle_status_paralyze_0)
        hs_SetCI_Explicit(1, ui_battle_status_paralyze_1, ui_battle_status_paralyze_0)
        hs_SetCI_Explicit(1, ui_battle_status_paralyze_0, ui_battle_status_paralyze_1)
        hs_SetCI_Explicit(1, ui_battle_status_paralyze_1, ui_battle_status_paralyze_0)
        hs_SetCI_Explicit(1, ui_battle_status_paralyze_0, ui_battle_status_paralyze_1)
        hs_SetCI_Explicit(1, ui_battle_status_paralyze_1, ui_battle_status_paralyze_0)
        hs_SetCI_Explicit(1, ui_battle_status_paralyze_0, ui_battle_status_paralyze_1)
    hs_Restart
    hs_End
};

HudScript HES_ParalyzedEnd = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_paralyze_0)
    hs_End
};

HudScript HES_DizzyLoop = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_Loop
        hs_SetCI(4, ui_battle_status_dizzy_0)
        hs_SetCI(4, ui_battle_status_dizzy_1)
        hs_SetCI(4, ui_battle_status_dizzy_2)
        hs_SetCI(4, ui_battle_status_dizzy_3)
    hs_Restart
    hs_End
};

HudScript HES_DizzyBegin = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_Loop
        hs_SetCI(4, ui_battle_status_dizzy_0)
        hs_SetCI(4, ui_battle_status_dizzy_1)
        hs_SetCI(4, ui_battle_status_dizzy_2)
        hs_SetCI(4, ui_battle_status_dizzy_3)
    hs_Restart
    hs_End
};

HudScript HES_DizzyEnd = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_dizzy_0)
    hs_End
};

HudScript HES_PoisonedLoop = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_Loop
        hs_SetCI(27, ui_battle_status_poison_0)
        hs_SetCI(3, ui_battle_status_poison_1)
        hs_SetCI(3, ui_battle_status_poison_0)
        hs_SetCI(3, ui_battle_status_poison_1)
    hs_Restart
    hs_End
};

HudScript HES_PoisonedBegin = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_Loop
        hs_SetCI(27, ui_battle_status_poison_0)
        hs_SetCI(3, ui_battle_status_poison_1)
        hs_SetCI(3, ui_battle_status_poison_0)
        hs_SetCI(3, ui_battle_status_poison_1)
    hs_Restart
    hs_End
};

HudScript HES_PoisonedEnd = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_poison_0)
    hs_End
};

HudScript HES_FrozenLoop = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_Loop
        hs_SetCI(24, ui_battle_status_frozen_0)
        hs_SetCI(3, ui_battle_status_frozen_1)
        hs_SetCI(4, ui_battle_status_frozen_2)
        hs_SetCI(3, ui_battle_status_frozen_3)
    hs_Restart
    hs_End
};

HudScript HES_FrozenBegin = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_Loop
        hs_SetCI(24, ui_battle_status_frozen_0)
        hs_SetCI(3, ui_battle_status_frozen_1)
        hs_SetCI(4, ui_battle_status_frozen_2)
        hs_SetCI(3, ui_battle_status_frozen_3)
    hs_Restart
    hs_End
};

HudScript HES_FrozenEnd = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_frozen_0)
    hs_End
};

HudScript HES_WeakenedLoop = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_Loop
        hs_SetCI(6, ui_battle_status_pdown_0)
        hs_SetCI(6, ui_battle_status_pdown_1)
    hs_Restart
    hs_End
};

HudScript HES_WeakenedBegin = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_Loop
        hs_SetCI(6, ui_battle_status_pdown_0)
        hs_SetCI(6, ui_battle_status_pdown_1)
    hs_Restart
    hs_End
};

HudScript HES_WeakenedEnd = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_pdown_0)
    hs_End
};

HudScript HES_Stopped = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_Loop
        hs_SetCI(5, ui_battle_status_stop_0)
        hs_SetCI(5, ui_battle_status_stop_1)
        hs_SetCI(5, ui_battle_status_stop_2)
        hs_SetCI(5, ui_battle_status_stop_3)
    hs_Restart
    hs_End
};

HudScript HES_StoppedBegin = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_Loop
        hs_SetCI(5, ui_battle_status_stop_0)
        hs_SetCI(5, ui_battle_status_stop_1)
        hs_SetCI(5, ui_battle_status_stop_2)
        hs_SetCI(5, ui_battle_status_stop_3)
    hs_Restart
    hs_End
};

HudScript HES_StoppedEnd = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_stop_0)
    hs_End
};

HudScript HES_ShrunkLoop = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_Loop
        hs_SetCI(5, ui_battle_status_shrink_0)
        hs_SetCI(6, ui_battle_status_shrink_1)
        hs_SetCI(6, ui_battle_status_shrink_2)
        hs_SetCI(5, ui_battle_status_shrink_3)
    hs_Restart
    hs_End
};

HudScript HES_ShrunkBegin = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_Loop
        hs_SetCI(5, ui_battle_status_shrink_0)
        hs_SetCI(6, ui_battle_status_shrink_1)
        hs_SetCI(6, ui_battle_status_shrink_2)
        hs_SetCI(5, ui_battle_status_shrink_3)
    hs_Restart
    hs_End
};

HudScript HES_ShrunkEnd = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_shrink_0)
    hs_End
};

HudScript HES_TransparentLoop = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_Loop
        hs_SetCI(3, ui_battle_status_transparent_0)
        hs_SetCI(3, ui_battle_status_transparent_1)
        hs_SetCI(3, ui_battle_status_transparent_2)
        hs_SetCI(3, ui_battle_status_transparent_3)
        hs_SetCI(3, ui_battle_status_transparent_4)
        hs_SetCI(3, ui_battle_status_transparent_5)
    hs_Restart
    hs_End
};

HudScript HES_TransparentBegin = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_Loop
        hs_SetCI(3, ui_battle_status_transparent_0)
        hs_SetCI(3, ui_battle_status_transparent_1)
        hs_SetCI(3, ui_battle_status_transparent_2)
        hs_SetCI(3, ui_battle_status_transparent_3)
        hs_SetCI(3, ui_battle_status_transparent_4)
        hs_SetCI(3, ui_battle_status_transparent_5)
    hs_Restart
    hs_End
};

HudScript HES_TransparentEnd = {
    hs_SetVisible
    hs_SetCustomSize(16, 16)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(240)
    hs_SetTexelOffset(1, -1)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(220)
    hs_SetTexelOffset(2, -2)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(200)
    hs_SetTexelOffset(3, -3)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(170)
    hs_SetTexelOffset(4, -4)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(120)
    hs_SetTexelOffset(5, -5)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(80)
    hs_SetTexelOffset(6, -6)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(50)
    hs_SetTexelOffset(8, -8)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_SetAlpha(30)
    hs_SetTexelOffset(10, -10)
    hs_SetCI(1, ui_battle_status_transparent_0)
    hs_End
};

HudScript HES_BoostJumpLoop = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_battle_status_charge_jump, 24, 24);

HudScript HES_BoostJumpBegin = {
    hs_SetVisible
    hs_SetCustomSize(24, 24)
    hs_SetAlpha(30)
    hs_SetTexelOffset(0, -10)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetAlpha(50)
    hs_SetTexelOffset(0, -8)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetAlpha(80)
    hs_SetTexelOffset(0, -6)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetAlpha(120)
    hs_SetTexelOffset(0, -5)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetAlpha(170)
    hs_SetTexelOffset(0, -4)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetAlpha(200)
    hs_SetTexelOffset(0, -3)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetAlpha(220)
    hs_SetTexelOffset(0, -2)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetAlpha(240)
    hs_SetTexelOffset(0, -1)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_Loop
        hs_SetCI(60, ui_battle_status_charge_jump)
    hs_Restart
    hs_End
};

HudScript HES_BoostJumpEnd = {
    hs_SetVisible
    hs_SetCustomSize(24, 24)
    hs_SetAlpha(240)
    hs_SetTexelOffset(0, -1)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetAlpha(220)
    hs_SetTexelOffset(-3, -3)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetAlpha(200)
    hs_SetTexelOffset(-6, -5)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetAlpha(170)
    hs_SetTexelOffset(-8, -6)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetAlpha(120)
    hs_SetTexelOffset(-10, -5)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetAlpha(80)
    hs_SetTexelOffset(-12, -3)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetAlpha(50)
    hs_SetTexelOffset(-13, 0)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetAlpha(30)
    hs_SetTexelOffset(-14, 4)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetTexelOffset(-15, 9)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_SetTexelOffset(-15, 15)
    hs_SetCI(1, ui_battle_status_charge_jump)
    hs_End
};

HudScript HES_BoostHammerLoop = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_battle_status_charge_hammer, 24, 24);

HudScript HES_BoostHammerBegin = {
    hs_SetVisible
    hs_SetCustomSize(24, 24)
    hs_SetAlpha(30)
    hs_SetTexelOffset(0, -10)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetAlpha(50)
    hs_SetTexelOffset(0, -8)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetAlpha(80)
    hs_SetTexelOffset(0, -6)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetAlpha(120)
    hs_SetTexelOffset(0, -5)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetAlpha(170)
    hs_SetTexelOffset(0, -4)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetAlpha(200)
    hs_SetTexelOffset(0, -3)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetAlpha(220)
    hs_SetTexelOffset(0, -2)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetAlpha(240)
    hs_SetTexelOffset(0, -1)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetAlpha(255)
    hs_SetTexelOffset(0, 0)
    hs_Loop
        hs_SetCI(60, ui_battle_status_charge_hammer)
    hs_Restart
    hs_End
};

HudScript HES_BoostHammerEnd = {
    hs_SetVisible
    hs_SetCustomSize(24, 24)
    hs_SetAlpha(240)
    hs_SetTexelOffset(0, -1)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetAlpha(220)
    hs_SetTexelOffset(-3, -3)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetAlpha(200)
    hs_SetTexelOffset(-6, -5)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetAlpha(170)
    hs_SetTexelOffset(-8, -6)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetAlpha(120)
    hs_SetTexelOffset(-10, -5)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetAlpha(80)
    hs_SetTexelOffset(-12, -3)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetAlpha(50)
    hs_SetTexelOffset(-13, 0)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetAlpha(30)
    hs_SetTexelOffset(-14, 4)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetTexelOffset(-15, 9)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_SetTexelOffset(-15, 15)
    hs_SetCI(1, ui_battle_status_charge_hammer)
    hs_End
};

HudScript HES_BoostPartner = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_battle_status_charge_goombario, 24, 24);

HudScript HES_Surprise = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_battle_status_exclamation, 24, 24);

HudScript HES_FPCost = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost, 16, 8);

HudScript HES_FPCostReduced = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost_reduced, 16, 8);

HudScript HES_FPCostReducedTwice = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost_reduced_twice, 16, 8);

HudScript HES_NotEnoughFP = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost_notenough, 16, 8);

HudScript HES_POWCost = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost, 16, 8);

HudScript HES_POWCostReduced = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost_reduced, 16, 8);

HudScript HES_POWCostReducedTwice = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost_reduced_twice, 16, 8);

HudScript HES_NotEnoughPOW = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost_notenough, 16, 8);

#if VERSION_PAL
HudScript HES_FPCost_de = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost_de, 16, 8);
HudScript HES_FPCostReduced_de = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost_de_reduced, 16, 8);
HudScript HES_FPCostReducedTwice_de = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost_de_reduced_twice, 16, 8);
HudScript HES_NotEnoughFP_de = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost_de_notenough, 16, 8);
HudScript HES_POWCost_de = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost_de, 16, 8);
HudScript HES_POWCostReduced_de = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost_de_reduced, 16, 8);
HudScript HES_POWCostReducedTwice_de = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost_de_reduced_twice, 16, 8);
HudScript HES_NotEnoughPOW_de = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost_de_notenough, 16, 8);

HudScript HES_FPCost_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost_fr, 16, 8);
HudScript HES_FPCostReduced_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost_fr_reduced, 16, 8);
HudScript HES_FPCostReducedTwice_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost_fr_reduced_twice, 16, 8);
HudScript HES_NotEnoughFP_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost_fr_notenough, 16, 8);
HudScript HES_POWCost_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost_fr, 16, 8);
HudScript HES_POWCostReduced_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost_fr_reduced, 16, 8);
HudScript HES_POWCostReducedTwice_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost_fr_reduced_twice, 16, 8);
HudScript HES_NotEnoughPOW_fr = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost_fr_notenough, 16, 8);

HudScript HES_FPCost_es = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost_es, 16, 8);
HudScript HES_FPCostReduced_es = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost_es_reduced, 16, 8);
HudScript HES_FPCostReducedTwice_es = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost_es_reduced_twice, 16, 8);
HudScript HES_NotEnoughFP_es = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_fp_cost_es_notenough, 16, 8);
HudScript HES_POWCost_es = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost_es, 16, 8);
HudScript HES_POWCostReduced_es = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost_es_reduced, 16, 8);
HudScript HES_POWCostReducedTwice_es = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost_es_reduced_twice, 16, 8);
HudScript HES_NotEnoughPOW_es = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_pow_cost_es_notenough, 16, 8);
#endif

HudScript HES_GreenArrowDown = {
    hs_SetVisible
    hs_SetCustomSize(16, 8)
    hs_Loop
        hs_ClearFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(9, ui_green_arrow_down)
        hs_SetFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(6, ui_green_arrow_down)
    hs_Restart
    hs_End
};

HudScript HES_GreenArrowUp = {
    hs_SetVisible
    hs_SetCustomSize(16, 8)
    hs_Loop
        hs_ClearFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(9, ui_green_arrow_up)
        hs_SetFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(6, ui_green_arrow_up)
    hs_Restart
    hs_End
};

HudScript HES_UnusedPinkFrame = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_kaime, 56, 24);

HudScript HES_UnusedDigit1 = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_unused_1, 16, 16);

HudScript HES_UnusedDigit2 = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_unused_2, 16, 16);

HudScript HES_UnusedDigit3 = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_unused_3, 16, 16);

HudScript HES_RedBar1 = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_red_bar1, 112, 8);

HudScript HES_EmptyBar = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_empty_bar, 112, 8);

HudScript HES_RedBar2 = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_red_bar2, 104, 8);

HudScript HES_MarioHead = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_mario_head, 16, 16);

HudScript HES_Eldstar = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_eldstar, 32, 32);

HudScript HES_EldstarDisabled = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_eldstar_disabled, 32, 32);

HudScript HES_Mamar = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_mamar, 32, 32);

HudScript HES_MamarDisabled = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_mamar_disabled, 32, 32);

HudScript HES_Skolar = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_skolar, 32, 32);

HudScript HES_SkolarDisabled = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_skolar_disabled, 32, 32);

HudScript HES_Muskular = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_muskular, 32, 32);

HudScript HES_MuskularDisabled = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_muskular_disabled, 32, 32);

HudScript HES_Misstar = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_misstar, 32, 32);

HudScript HES_MisstarDisabled = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_misstar_disabled, 32, 32);

HudScript HES_Klevar = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_klevar, 32, 32);

HudScript HES_KlevarDisabled = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_klevar_disabled, 32, 32);

HudScript HES_Kalmar = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_kalmar, 32, 32);

HudScript HES_KalmarDisabled = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_kalmar_disabled, 32, 32);

HudScript HES_StarBeam = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_star_beam, 32, 32);

HudScript HES_StarBeamDisabled = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_star_beam_disabled, 32, 32);

HudScript HES_PeachBeam = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_peach_beam, 32, 32);

HudScript HES_PeachBeamDisabled = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_peach_beam_disabled, 32, 32);

HudScript HES_Partner0 = HES_TEMPLATE_CI_ENUM_SIZE(ui_partner0, 32, 32);

HudScript HES_Partner0Disabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_partner0_disabled, 32, 32);

HudScript HES_Goombario = HES_TEMPLATE_CI_ENUM_SIZE(ui_goombario, 32, 32);

HudScript HES_GoombarioDisabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_goombario_disabled, 32, 32);

HudScript HES_Kooper = HES_TEMPLATE_CI_ENUM_SIZE(ui_kooper, 32, 32);

HudScript HES_KooperDisabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_kooper_disabled, 32, 32);

HudScript HES_Bombette = HES_TEMPLATE_CI_ENUM_SIZE(ui_bombette, 32, 32);

HudScript HES_BombetteDisabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_bombette_disabled, 32, 32);

HudScript HES_Parakarry = HES_TEMPLATE_CI_ENUM_SIZE(ui_parakarry, 32, 32);

HudScript HES_ParakarryDisabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_parakarry_disabled, 32, 32);

HudScript HES_Bow = HES_TEMPLATE_CI_ENUM_SIZE(ui_bow, 32, 32);

HudScript HES_BowDisabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_bow_disabled, 32, 32);

HudScript HES_Watt = HES_TEMPLATE_CI_ENUM_SIZE(ui_watt, 32, 32);

HudScript HES_WattDisabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_watt_disabled, 32, 32);

HudScript HES_Sushie = HES_TEMPLATE_CI_ENUM_SIZE(ui_sushie, 32, 32);

HudScript HES_SushieDisabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_sushie_disabled, 32, 32);

HudScript HES_Lakilester = HES_TEMPLATE_CI_ENUM_SIZE(ui_lakilester, 32, 32);

HudScript HES_LakilesterDisabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_lakilester_disabled, 32, 32);

HudScript HES_Partner9 = HES_TEMPLATE_CI_ENUM_SIZE(ui_partner9, 32, 32);

HudScript HES_Partner9Disabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_partner9_disabled, 32, 32);

HudScript HES_PartnerA = HES_TEMPLATE_CI_ENUM_SIZE(ui_partner10, 32, 32);

HudScript HES_PartnerADisabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_partner10_disabled, 32, 32);

HudScript HES_PartnerB = HES_TEMPLATE_CI_ENUM_SIZE(ui_partner11, 32, 32);

HudScript HES_PartnerBDisabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_partner11_disabled, 32, 32);

HudScript HES_StatusTimes = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_times, 8, 8);

HudScript HES_StatusSlash = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_slash, 8, 16);

HudScript HES_StatusDigit0 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_0, 16, 16);

HudScript HES_StatusDigit1 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_1, 16, 16);

HudScript HES_StatusDigit2 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_2, 16, 16);

HudScript HES_StatusDigit3 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_3, 16, 16);

HudScript HES_StatusDigit4 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_4, 16, 16);

HudScript HES_StatusDigit5 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_5, 16, 16);

HudScript HES_StatusDigit6 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_6, 16, 16);

HudScript HES_StatusDigit7 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_7, 16, 16);

HudScript HES_StatusDigit8 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_8, 16, 16);

HudScript HES_StatusDigit9 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_9, 16, 16);

HudScript HES_StatusHP = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_hp, 16, 16);

HudScript HES_StatusFP = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_fp, 16, 16);

#if VERSION_PAL
HudScript HES_StatusHP_de = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_hp_de, 16, 16);
HudScript HES_StatusFP_de = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_fp_de, 16, 16);

HudScript HES_StatusHP_fr = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_hp_fr, 16, 16);
HudScript HES_StatusFP_fr = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_fp_fr, 16, 16);

HudScript HES_StatusHP_es = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_hp_es, 16, 16);
HudScript HES_StatusFP_es = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_text_fp_es, 16, 16);
#endif

HudScript HES_StatusSPIncrement1 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_unit_1, 8, 8);

HudScript HES_StatusSPIncrement2 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_unit_2, 8, 8);

HudScript HES_StatusSPIncrement3 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_unit_3, 8, 8);

HudScript HES_StatusSPIncrement4 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_unit_4, 8, 8);

HudScript HES_StatusSPIncrement5 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_unit_5, 8, 8);

HudScript HES_StatusSPIncrement6 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_unit_6, 8, 8);

HudScript HES_StatusSPIncrement7 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_unit_7, 8, 8);

HudScript HES_StatusSPEmptyIncrement = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_unit_empty, 8, 8);

HudScript HES_StatusStar1 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_star_1, 8, 8);

HudScript HES_StatusStar2 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_star_2, 8, 8);

HudScript HES_StatusStar3 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_star_3, 8, 8);

HudScript HES_StatusStar4 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_star_4, 8, 8);

HudScript HES_StatusStar5 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_star_5, 8, 8);

HudScript HES_StatusStar6 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_star_6, 8, 8);

HudScript HES_StatusStar7 = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_star_7, 8, 8);

HudScript HES_StatusStarEmpty = HES_TEMPLATE_CI_ENUM_SIZE(ui_status_pow_star_empty, 8, 8);

HudScript HES_StatusHeart = {
    hs_SetTileSize(HUD_ELEMENT_SIZE_16x16)
    hs_Loop
        hs_SetRGBA(60, ui_stat_heart_png)
    hs_Restart
    hs_End
};

HudScript HES_StatusFlower = {
    hs_SetTileSize(HUD_ELEMENT_SIZE_16x16)
    hs_Loop
        hs_SetRGBA(60, ui_stat_flower_png)
    hs_Restart
    hs_End
};

HudScript HES_StatusCoin = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_16x16)
    hs_Loop
        hs_op_15(0)
        hs_SetCI(3, ui_status_coin_0)
        hs_SetCI(3, ui_status_coin_1)
        hs_SetCI(3, ui_status_coin_4)
        hs_SetCI(3, ui_status_coin_5)
        hs_SetCI(3, ui_status_coin_6)
        hs_SetCI(3, ui_status_coin_7)
        hs_SetCI(3, ui_status_coin_8)
        hs_SetCI(3, ui_status_coin_9)
        hs_RandomRestart(100, 70)
        hs_op_15(1)
        hs_SetCI(3, ui_status_coin_0)
        hs_SetCI(2, ui_status_coin_1)
        hs_SetCI(1, ui_status_coin_2)
        hs_SetCI(1, ui_status_coin_3)
        hs_SetCI(2, ui_status_coin_4)
        hs_SetCI(3, ui_status_coin_5)
        hs_SetCI(3, ui_status_coin_6)
        hs_SetCI(3, ui_status_coin_7)
        hs_SetCI(3, ui_status_coin_8)
        hs_SetCI(3, ui_status_coin_9)
    hs_Restart
    hs_End
};

HudScript HES_StatusStarPoint = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_16x16)
    hs_Loop
        hs_SetCI(2, ui_status_star_point_0)
        hs_SetCI(2, ui_status_star_point_1)
        hs_SetCI(2, ui_status_star_point_2)
        hs_SetCI(2, ui_status_star_point_3)
        hs_SetCI(2, ui_status_star_point_4)
        hs_SetCI(2, ui_status_star_point_5)
        hs_SetCI(2, ui_status_star_point_6)
        hs_SetCI(2, ui_status_star_point_7)
    hs_Restart
    hs_End
};

HudScript HES_MenuBoots1 = HES_TEMPLATE_CI_ENUM_SIZE(ui_boots, 32, 32);

HudScript HES_MenuBoots1Disabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_boots_disabled, 32, 32);

HudScript HES_MenuBoots2 = HES_TEMPLATE_CI_ENUM_SIZE(ui_super_boots, 32, 32);

HudScript HES_MenuBoots2Disabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_super_boots_disabled, 32, 32);

HudScript HES_MenuBoots3 = HES_TEMPLATE_CI_ENUM_SIZE(ui_ultra_boots, 32, 32);

HudScript HES_MenuBoots3Disabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_ultra_boots_disabled, 32, 32);

HudScript HES_MenuHammer1 = HES_TEMPLATE_CI_ENUM_SIZE(ui_hammer, 32, 32);

HudScript HES_MenuHammer1Disabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_hammer_disabled, 32, 32);

HudScript HES_MenuHammer2 = HES_TEMPLATE_CI_ENUM_SIZE(ui_super_hammer, 32, 32);

HudScript HES_MenuHammer2Disabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_super_hammer_disabled, 32, 32);

HudScript HES_MenuHammer3 = HES_TEMPLATE_CI_ENUM_SIZE(ui_ultra_hammer, 32, 32);

HudScript HES_MenuHammer3Disabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_ultra_hammer_disabled, 32, 32);

HudScript HES_MenuItem = HES_TEMPLATE_CI_ENUM_SIZE(ui_item, 32, 32);

HudScript HES_MenuItemDisabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_item_disabled, 32, 32);

HudScript HES_MenuStarPower = HES_TEMPLATE_CI_ENUM_SIZE(ui_star_spirit, 32, 32);

HudScript HES_MenuStarPowerDisabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_star_spirit_disabled, 32, 32);

HudScript HES_Peril = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_40x16)
    hs_Loop
        hs_PlaySound(SOUND_PERIL)
        hs_ClearFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(15, ui_battle_status_peril)
        hs_SetFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(10, ui_battle_status_peril)
    hs_Restart
    hs_End
};

HudScript HES_Danger = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_40x16)
    hs_Loop
        hs_PlaySound(SOUND_DANGER)
        hs_ClearFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(15, ui_battle_status_danger)
        hs_SetFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(10, ui_battle_status_danger)
    hs_Restart
    hs_End
};

HudScript HES_Refund = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_40x24)
    hs_Loop
        hs_ClearFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(8, ui_battle_status_refund)
        hs_SetFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(4, ui_battle_status_refund)
    hs_Restart
    hs_End
};

HudScript HES_Happy = HES_TEMPLATE_CI_ENUM_SIZE(ui_battle_status_happy, 40, 16);

HudScript HES_HPDrain = HES_TEMPLATE_CI_ENUM_SIZE(ui_battle_status_hp_drain, 40, 16);

#if VERSION_PAL
// German
HudScript HES_Peril_de = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_40x16)
    hs_Loop
        hs_PlaySound(SOUND_PERIL)
        hs_ClearFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(15, ui_battle_status_peril_de)
        hs_SetFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(10, ui_battle_status_peril_de)
    hs_Restart
    hs_End
};

HudScript HES_Danger_de = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_40x16)
    hs_Loop
        hs_PlaySound(SOUND_DANGER)
        hs_ClearFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(15, ui_battle_status_danger_de)
        hs_SetFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(10, ui_battle_status_danger_de)
    hs_Restart
    hs_End
};

HudScript HES_Refund_de = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_40x24)
    hs_Loop
        hs_ClearFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(8, ui_battle_status_refund_de)
        hs_SetFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(4, ui_battle_status_refund_de)
    hs_Restart
    hs_End
};

HudScript HES_Happy_de = HES_TEMPLATE_CI_ENUM_SIZE(ui_battle_status_happy_de, 40, 16);

HudScript HES_HPDrain_de = HES_TEMPLATE_CI_ENUM_SIZE(ui_battle_status_hp_drain_de, 40, 16);

// French
HudScript HES_Peril_fr = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_40x16)
    hs_Loop
        hs_PlaySound(SOUND_PERIL)
        hs_ClearFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(15, ui_battle_status_peril_fr)
        hs_SetFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(10, ui_battle_status_peril_fr)
    hs_Restart
    hs_End
};

HudScript HES_Danger_fr = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_40x16)
    hs_Loop
        hs_PlaySound(SOUND_DANGER)
        hs_ClearFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(15, ui_battle_status_danger_fr)
        hs_SetFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(10, ui_battle_status_danger_fr)
    hs_Restart
    hs_End
};

HudScript HES_Refund_fr = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_40x24)
    hs_Loop
        hs_ClearFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(8, ui_battle_status_refund_fr)
        hs_SetFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(4, ui_battle_status_refund_fr)
    hs_Restart
    hs_End
};

HudScript HES_Happy_fr = HES_TEMPLATE_CI_ENUM_SIZE(ui_battle_status_happy_fr, 40, 16);

HudScript HES_HPDrain_fr = HES_TEMPLATE_CI_ENUM_SIZE(ui_battle_status_hp_drain_fr, 40, 16);

// Spanish
HudScript HES_Peril_es = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_40x16)
    hs_Loop
        hs_PlaySound(SOUND_PERIL)
        hs_ClearFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(15, ui_battle_status_peril_es)
        hs_SetFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(10, ui_battle_status_peril_es)
    hs_Restart
    hs_End
};

HudScript HES_Danger_es = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_40x16)
    hs_Loop
        hs_PlaySound(SOUND_DANGER)
        hs_ClearFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(15, ui_battle_status_danger_es)
        hs_SetFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(10, ui_battle_status_danger_es)
    hs_Restart
    hs_End
};

HudScript HES_Refund_es = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_40x24)
    hs_Loop
        hs_ClearFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(8, ui_battle_status_refund_es)
        hs_SetFlags(HUD_ELEMENT_FLAG_200000)
        hs_SetCI(4, ui_battle_status_refund_es)
    hs_Restart
    hs_End
};

HudScript HES_Happy_es = HES_TEMPLATE_CI_ENUM_SIZE(ui_battle_status_happy_es, 40, 16);

HudScript HES_HPDrain_es = HES_TEMPLATE_CI_ENUM_SIZE(ui_battle_status_hp_drain_es, 40, 16);
#endif

HudScript HES_BlueMeter = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_input_mash_bar, 72, 16);

HudScript HES_AButton = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_input_a_button_unpressed, 48, 40);

HudScript HES_AButtonDown = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_input_a_button_pressed, 48, 40);

HudScript HES_MashAButton = {
    hs_SetVisible
    hs_SetCustomSize(48, 40)
    hs_Loop
        hs_SetCI(2, ui_input_a_button_unpressed)
        hs_SetCI(2, ui_input_a_button_pressed)
    hs_Restart
    hs_End
};

HudScript HES_PressAButton = {
    hs_SetVisible
    hs_SetCustomSize(48, 40)
    hs_Loop
        hs_SetCI(10, ui_input_a_button_unpressed)
        hs_SetCI(10, ui_input_a_button_pressed)
    hs_Restart
    hs_End
};

HudScript HES_SlowlyPressAButton = {
    hs_SetVisible
    hs_SetCustomSize(48, 40)
    hs_Loop
        hs_SetCI(30, ui_input_a_button_unpressed)
        hs_SetCI(30, ui_input_a_button_pressed)
    hs_Restart
    hs_End
};

HudScript HES_SlowlyMashAButton = {
    hs_SetVisible
    hs_SetCustomSize(48, 40)
    hs_Loop
        hs_SetCI(4, ui_input_a_button_unpressed)
        hs_SetCI(4, ui_input_a_button_pressed)
    hs_Restart
    hs_End
};

HudScript HES_StartButton = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_input_start_button, 48, 40);

HudScript HES_StartButtonDown = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_input_start_button2, 48, 40);

HudScript HES_MashStartButton = {
    hs_SetVisible
    hs_SetCustomSize(48, 40)
    hs_Loop
        hs_SetCI(2, ui_input_start_button)
        hs_SetCI(2, ui_input_start_button2)
    hs_Restart
    hs_End
};

HudScript HES_PressStartButton = {
    hs_SetVisible
    hs_SetCustomSize(48, 40)
    hs_Loop
        hs_SetCI(10, ui_input_start_button)
        hs_SetCI(10, ui_input_start_button2)
    hs_Restart
    hs_End
};

HudScript HES_StartButtonText = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_input_start_text, 24, 8);

HudScript HES_RotateStickCW = {
    hs_SetVisible
    hs_Loop
        hs_SetCustomSize(32, 32)
        hs_SetTexelOffset(0, 0)
        hs_SetCI(2, ui_input_analog_stick_up)
        hs_SetCustomSize(40, 32)
        hs_SetTexelOffset(5, 0)
        hs_SetCI(2, ui_input_analog_stick_right)
        hs_SetCustomSize(32, 32)
        hs_SetTexelOffset(0, 0)
        hs_SetCI(2, ui_input_analog_stick_down)
        hs_SetCustomSize(40, 32)
        hs_SetTexelOffset(-4, 0)
        hs_SetCI(2, ui_input_analog_stick_left)
    hs_Restart
    hs_End
};

HudScript HES_StickNeutral = HES_TEMPLATE_CI_CUSTOM_SIZE(ui_input_analog_stick, 32, 32);

HudScript HES_StickHoldLeft = {
    hs_SetVisible
    hs_SetCustomSize(40, 32)
    hs_SetTexelOffset(-4, 0)
    hs_Loop
        hs_SetCI(60, ui_input_analog_stick_left)
    hs_Restart
    hs_End
};

HudScript HES_StickBackAndForth = {
    hs_SetVisible
    hs_Loop
        hs_SetCustomSize(40, 32)
        hs_SetTexelOffset(-4, 0)
        hs_SetCI(2, ui_input_analog_stick_left)
        hs_SetCustomSize(32, 32)
        hs_SetTexelOffset(0, 0)
        hs_SetCI(1, ui_input_analog_stick3)
        hs_SetCustomSize(40, 32)
        hs_SetTexelOffset(5, 0)
        hs_SetCI(2, ui_input_analog_stick_right)
        hs_SetCustomSize(32, 32)
        hs_SetTexelOffset(0, 0)
        hs_SetCI(1, ui_input_analog_stick2)
    hs_Restart
    hs_End
};

HudScript HES_StickMashLeft = {
    hs_SetVisible
    hs_Loop
        hs_SetCustomSize(40, 32)
        hs_SetTexelOffset(-4, 0)
        hs_SetCI(6, ui_input_analog_stick_left)
        hs_SetCustomSize(32, 32)
        hs_SetTexelOffset(0, 0)
        hs_SetCI(1, ui_input_analog_stick)
    hs_Restart
    hs_End
};

HudScript HES_StickTapLeft = {
    hs_SetVisible
    hs_Loop
        hs_SetCustomSize(40, 32)
        hs_SetTexelOffset(-4, 0)
        hs_SetCI(22, ui_input_analog_stick_left)
        hs_SetCustomSize(32, 32)
        hs_SetTexelOffset(0, 0)
        hs_SetCI(8, ui_input_analog_stick)
    hs_Restart
    hs_End
};

HudScript HES_StickTapNeutral = {
    hs_SetVisible
    hs_SetCustomSize(32, 32)
    hs_SetTexelOffset(0, 0)
    hs_SetCI(1, ui_input_analog_stick3)
    hs_SetCustomSize(32, 32)
    hs_SetCI(1, ui_input_analog_stick2)
    hs_SetCustomSize(32, 32)
    hs_SetCI(1, ui_input_analog_stick3)
    hs_SetCustomSize(32, 32)
    hs_SetCI(20, ui_input_analog_stick2)
    hs_Loop
        hs_SetCI(60, ui_input_analog_stick2)
    hs_Restart
    hs_End
};

HudScript HES_StickHoldDown = {
    hs_SetVisible
    hs_SetCustomSize(32, 32)
    hs_SetTexelOffset(0, 0)
    hs_Loop
        hs_SetCI(60, ui_input_analog_stick_down)
    hs_Restart
    hs_End
};

HudScript HES_StickMashDown = {
    hs_SetVisible
    hs_Loop
        hs_SetCustomSize(32, 32)
        hs_SetTexelOffset(0, 0)
        hs_SetCI(2, ui_input_analog_stick)
        hs_SetCustomSize(32, 32)
        hs_SetTexelOffset(0, 0)
        hs_SetCI(1, ui_input_analog_stick_down)
    hs_Restart
    hs_End
};

HudScript HES_StickTapDown = {
    hs_SetVisible
    hs_Loop
        hs_SetCustomSize(32, 32)
        hs_SetTexelOffset(0, 0)
        hs_SetCI(12, ui_input_analog_stick)
        hs_SetCustomSize(32, 32)
        hs_SetTexelOffset(0, 0)
        hs_SetCI(10, ui_input_analog_stick_down)
    hs_Restart
    hs_End
};

HudScript HES_StickSlowlyTapDown = {
    hs_SetVisible
    hs_Loop
        hs_SetCustomSize(32, 32)
        hs_SetTexelOffset(0, 0)
        hs_SetCI(6, ui_input_analog_stick)
        hs_SetCustomSize(32, 32)
        hs_SetTexelOffset(0, 0)
        hs_SetCI(1, ui_input_analog_stick_down)
    hs_Restart
    hs_End
};

HudScript HES_StickTapRight = {
    hs_SetVisible
    hs_Loop
        hs_SetCustomSize(32, 32)
        hs_SetTexelOffset(0, 0)
        hs_SetCI(6, ui_input_analog_stick)
        hs_SetCustomSize(40, 32)
        hs_SetTexelOffset(5, 0)
        hs_SetCI(2, ui_input_analog_stick_right)
    hs_Restart
    hs_End
};

HudScript HES_RunAwayOK = {
    hs_SetVisible
    hs_Loop
        hs_SetCustomSize(24, 16)
        hs_SetCI(60, ui_ok)
    hs_Restart
    hs_End
};

HudScript HES_MenuTimes = HES_TEMPLATE_CI_ENUM_SIZE(ui_menu_times, 8, 8);

HudScript HES_PartnerRank1A = HES_TEMPLATE_CI_ENUM_SIZE(ui_bluepip, 16, 16);

HudScript HES_PartnerRank1B = HES_TEMPLATE_CI_ENUM_SIZE(ui_bluepip, 16, 16);

HudScript HES_PartnerRank2A = HES_TEMPLATE_CI_ENUM_SIZE(ui_bluepip2, 16, 16);

HudScript HES_PartnerRank2B = HES_TEMPLATE_CI_ENUM_SIZE(ui_bluepip2, 16, 16);

HudScript HES_MoveDiamond = HES_TEMPLATE_CI_ENUM_SIZE(ui_move_basic, 32, 32);

HudScript HES_MoveBlueOrb = HES_TEMPLATE_CI_ENUM_SIZE(ui_move_partner_1, 32, 32);

HudScript HES_MoveGreenOrb = HES_TEMPLATE_CI_ENUM_SIZE(ui_move_partner_2, 32, 32);

HudScript HES_MoveRedOrb = HES_TEMPLATE_CI_ENUM_SIZE(ui_move_partner_3, 32, 32);

HudScript HES_MoveDiamond_disabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_move_basic_disabled, 32, 32);

HudScript HES_MoveBlueOrbDisabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_move_partner_1_disabled, 32, 32);

HudScript HES_MoveGreenOrbDisabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_move_partner_2_disabled, 32, 32);

HudScript HES_MoveRedOrbDisabled = HES_TEMPLATE_CI_ENUM_SIZE(ui_move_partner_3_disabled, 32, 32);
