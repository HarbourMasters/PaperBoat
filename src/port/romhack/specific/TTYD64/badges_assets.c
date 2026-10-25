#include "common.h"
#include "hud_element.h"
#include "port/romhack/specific/TTYD64/badges_internal.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"

u8 TTYD64_FPDrainByte[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
u8 TTYD64_DoesActorTriedToHitTarget_Player[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
u8 TTYD64_DoesActorTriedToHitTarget_Partner[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

const u8 TTYD64_String_TooMuchBadges[] = {
    0xFB, 0x39, 0x4F, 0x55, 0xF7, 0x43, 0x41, 0x4E, 0x07, 0x54, 0xF7, 0x43, 0x41, 0x52, 0x52, 0x59, 0xF7, 0x41, 0x4E,
    0x59, 0xF7, 0x4D, 0x4F, 0x52, 0x45, 0xF7, 0x42, 0x41, 0x44, 0x47, 0x45, 0x53, 0xF0, 0x52, 0x49, 0x47, 0x48, 0x54,
    0xF7, 0x4E, 0x4F, 0x57, 0x0E, 0xF0, 0xF1, 0xFB, 0x30, 0x4C, 0x45, 0x41, 0x53, 0x45, 0xF7, 0x43, 0x4F, 0x4D, 0x45,
    0xF7, 0x42, 0x41, 0x43, 0x4B, 0xF7, 0x41, 0x46, 0x54, 0x45, 0x52, 0xF7, 0x53, 0x45, 0x4C, 0x4C, 0x49, 0x4E, 0x47,
    0x0C, 0xF0, 0x53, 0x4F, 0x4D, 0x45, 0xF7, 0x42, 0x41, 0x44, 0x47, 0x45, 0x53, 0x0E, 0xF1, 0xFD
};
const u8 TTYD64_String_TooManyBadges[] = { 0x22, 0x41, 0x44, 0x47, 0x45, 0x53, 0xF7, 0x49, 0x4E, 0x56, 0x45, 0x4E,
                                           0x54, 0x4F, 0x52, 0x59, 0xF7, 0x46, 0x55, 0x4C, 0x4C, 0x01, 0xFD };
const u8 TTYD64_Charge_FPAmount[] = { 0xF7, 0xF7, 0xF7, 0xF7, 0xFF, 0x28, 0x00, 0xFF, 0x0D, 0x0C,
                                      0x0C, 0xFF, 0x13, 0x03, 0xFF, 0x12, 0x02, 0x26, 0x30, 0xFD };
const u8 TTYD64_String_Defense_Desc[] = { 0x24, 0x45, 0x46, 0x45, 0x4E, 0x44, 0xF7, 0x54, 0x48,
                                          0x49, 0x53, 0xF7, 0x54, 0x55, 0x52, 0x4E, 0x0E, 0xFD };
const u8 TTYD64_String_Charge_Desc[] = { 0x33, 0x41, 0x56, 0x45, 0xF7, 0x55, 0x50, 0xF7, 0x53, 0x54, 0x52, 0x45,
                                         0x4E, 0x47, 0x54, 0x48, 0xF7, 0x54, 0x4F, 0xF7, 0x50, 0x4F, 0x57, 0x45,
                                         0x52, 0xF7, 0x55, 0x50, 0xF0, 0x59, 0x4F, 0x55, 0x52, 0xF7, 0x4E, 0x45,
                                         0x58, 0x54, 0xF7, 0x41, 0x54, 0x54, 0x41, 0x43, 0x4B, 0x0E, 0xFD };

static const ALIGN_ASSET(2) char sTex_fp_drain[] = "__OTR__romhack/res/misc/fp_drain";
static const ALIGN_ASSET(2) char sTex_fp_drain_pal[] = "__OTR__romhack/res/misc/fp_drain.pal";
static const ALIGN_ASSET(2) char sTex_focus[] = "__OTR__romhack/res/battle_strats/focus";
static const ALIGN_ASSET(2) char sTex_focus_pal[] = "__OTR__romhack/res/battle_strats/focus.pal";
static const ALIGN_ASSET(2) char sTex_charge[] = "__OTR__romhack/res/battle_strats/charge";
static const ALIGN_ASSET(2) char sTex_charge_pal[] = "__OTR__romhack/res/battle_strats/charge.pal";
static const ALIGN_ASSET(2) char sTex_charge_bw_pal[] = "__OTR__romhack/res/battle_strats/charge_bw.pal";
static const ALIGN_ASSET(2) char sTex_defense[] = "__OTR__romhack/res/battle_strats/defense";
static const ALIGN_ASSET(2) char sTex_defense_pal[] = "__OTR__romhack/res/battle_strats/defense.pal";
static const ALIGN_ASSET(2) char sTex_runAway[] = "__OTR__romhack/res/battle_strats/runAway";
static const ALIGN_ASSET(2) char sTex_runAway_pal[] = "__OTR__romhack/res/battle_strats/runAway.pal";
static const ALIGN_ASSET(2) char sTex_runAway_bw_pal[] = "__OTR__romhack/res/battle_strats/runAway_bw.pal";

HudScript TTYD64_IconScript_FPDrain = { hs_SetVisible hs_SetTileSize(22) hs_Loop HUD_ELEMENT_OP_SetCI, 60,
                                        (intptr_t) sTex_fp_drain, (intptr_t) sTex_fp_drain_pal, hs_Restart hs_End };

HudScript TTYD64_IconScript_Focus = { hs_SetVisible hs_SetTileSize(3) hs_Loop HUD_ELEMENT_OP_SetCI, 60,
                                      (intptr_t) sTex_focus, (intptr_t) sTex_focus_pal, hs_Restart hs_End };

HudScript TTYD64_IconScript_ChargeCommand = { hs_SetVisible hs_SetTileSize(3) hs_Loop HUD_ELEMENT_OP_SetCI, 60,
                                              (intptr_t) sTex_charge, (intptr_t) sTex_charge_pal, hs_Restart hs_End };

HudScript TTYD64_IconScript_ChargeCommandBW = { hs_SetVisible hs_SetTileSize(3) hs_Loop HUD_ELEMENT_OP_SetCI, 60,
                                                (intptr_t) sTex_charge, (intptr_t) sTex_charge_bw_pal,
                                                hs_Restart hs_End };

HudScript TTYD64_IconScript_Defense = { hs_SetVisible hs_SetTileSize(3) hs_Loop HUD_ELEMENT_OP_SetCI, 60,
                                        (intptr_t) sTex_defense, (intptr_t) sTex_defense_pal, hs_Restart hs_End };

HudScript TTYD64_IconScript_RunAway = { hs_SetVisible hs_SetTileSize(3) hs_Loop HUD_ELEMENT_OP_SetCI, 60,
                                        (intptr_t) sTex_runAway, (intptr_t) sTex_runAway_pal, hs_Restart hs_End };

HudScript TTYD64_IconScript_RunAwayBW = { hs_SetVisible hs_SetTileSize(3) hs_Loop HUD_ELEMENT_OP_SetCI, 60,
                                          (intptr_t) sTex_runAway, (intptr_t) sTex_runAway_bw_pal, hs_Restart hs_End };
