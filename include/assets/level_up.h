#pragma once
#include "alignment.h"

// --- Big letter textures (IA8 64x64) ---
static const ALIGN_ASSET(2) char level_up_big_V_png[] = "__OTR__level_up/big_V";
static const ALIGN_ASSET(2) char level_up_big_P_png[] = "__OTR__level_up/big_P";
static const ALIGN_ASSET(2) char level_up_big_exclamation_mark_png[] = "__OTR__level_up/big_exclamation_mark";
static const ALIGN_ASSET(2) char level_up_big_U_png[] = "__OTR__level_up/big_U";
static const ALIGN_ASSET(2) char level_up_big_L_png[] = "__OTR__level_up/big_L";
static const ALIGN_ASSET(2) char level_up_big_E_png[] = "__OTR__level_up/big_E";

// VRAM aliases for level_up_letters_en_de.c
#define D_PAL_802A6838_7F8418 level_up_big_V_png
#define D_PAL_802A78B0_7F9490 level_up_big_P_png
#define D_PAL_802A8928_7FA508 level_up_big_exclamation_mark_png
#define D_PAL_802A99A0_7FB580 level_up_big_U_png
#define D_PAL_802AAA18_7FC5F8 level_up_big_L_png
#define D_PAL_802ABA90_7FD670 level_up_big_E_png

// --- Big letter texture DLs ---
static const ALIGN_ASSET(2) char level_up_big_V_gfx[] = "__OTR__level_up/big_V.gfx";
static const ALIGN_ASSET(2) char level_up_big_P_gfx[] = "__OTR__level_up/big_P.gfx";
static const ALIGN_ASSET(2) char level_up_big_exclamation_mark_gfx[] = "__OTR__level_up/big_exclamation_mark.gfx";
static const ALIGN_ASSET(2) char level_up_big_U_gfx[] = "__OTR__level_up/big_U.gfx";
static const ALIGN_ASSET(2) char level_up_big_L_gfx[] = "__OTR__level_up/big_L.gfx";
static const ALIGN_ASSET(2) char level_up_big_E_gfx[] = "__OTR__level_up/big_E.gfx";

// --- Letter composition DLs ---
static const ALIGN_ASSET(2) char level_up_draw_exclamation_mark_gfx[] = "__OTR__level_up/draw_exclamation_mark.gfx";
static const ALIGN_ASSET(2) char level_up_draw_U_gfx[] = "__OTR__level_up/draw_U.gfx";
static const ALIGN_ASSET(2) char level_up_draw_P_gfx[] = "__OTR__level_up/draw_P.gfx";
static const ALIGN_ASSET(2) char level_up_draw_L_gfx[] = "__OTR__level_up/draw_L.gfx";
static const ALIGN_ASSET(2) char level_up_draw_second_L_gfx[] = "__OTR__level_up/draw_second_L.gfx";
static const ALIGN_ASSET(2) char level_up_draw_E_gfx[] = "__OTR__level_up/draw_E.gfx";
static const ALIGN_ASSET(2) char level_up_draw_V_gfx[] = "__OTR__level_up/draw_V.gfx";
static const ALIGN_ASSET(2) char level_up_draw_second_E_gfx[] = "__OTR__level_up/draw_second_E.gfx";

// --- Chain DLs ---
static const ALIGN_ASSET(2) char level_up_letters_chain_gfx[] = "__OTR__level_up/letters_chain.gfx";
static const ALIGN_ASSET(2) char level_up_chain_gfx[] = "__OTR__level_up/chain.gfx";

// --- Icons (CI4 40x40) ---
static const ALIGN_ASSET(2) char level_up_heart_png[] = "__OTR__level_up/heart";
static const ALIGN_ASSET(2) char level_up_heart_pal[] = "__OTR__level_up/heart.pal";
static const ALIGN_ASSET(2) char level_up_flower_png[] = "__OTR__level_up/flower";
static const ALIGN_ASSET(2) char level_up_flower_pal[] = "__OTR__level_up/flower.pal";
static const ALIGN_ASSET(2) char level_up_leaves_png[] = "__OTR__level_up/leaves";
static const ALIGN_ASSET(2) char level_up_leaves_pal[] = "__OTR__level_up/leaves.pal";
static const ALIGN_ASSET(2) char level_up_badge_png[] = "__OTR__level_up/badge";
static const ALIGN_ASSET(2) char level_up_badge_pal[] = "__OTR__level_up/badge.pal";

// --- Stat labels (CI4 32x24) ---
static const ALIGN_ASSET(2) char level_up_FP_png[] = "__OTR__level_up/FP";
static const ALIGN_ASSET(2) char level_up_FP_pal[] = "__OTR__level_up/FP.pal";
static const ALIGN_ASSET(2) char level_up_BP_png[] = "__OTR__level_up/BP";
static const ALIGN_ASSET(2) char level_up_BP_pal[] = "__OTR__level_up/BP.pal";
static const ALIGN_ASSET(2) char level_up_HP_png[] = "__OTR__level_up/HP";
static const ALIGN_ASSET(2) char level_up_HP_pal[] = "__OTR__level_up/HP.pal";

// --- Digits (CI4 8x16) + green/red/blue palettes ---
static const ALIGN_ASSET(2) char level_up_digit_0_png[] = "__OTR__level_up/digit_0";
static const ALIGN_ASSET(2) char level_up_digit_0_pal[] = "__OTR__level_up/digit_0.pal";
#define level_up_digit_0_red_png level_up_digit_0_png
static const ALIGN_ASSET(2) char level_up_digit_0_red_pal[] = "__OTR__level_up/digit_0.red.pal";
#define level_up_digit_0_blue_png level_up_digit_0_png
static const ALIGN_ASSET(2) char level_up_digit_0_blue_pal[] = "__OTR__level_up/digit_0.blue.pal";

static const ALIGN_ASSET(2) char level_up_digit_1_png[] = "__OTR__level_up/digit_1";
static const ALIGN_ASSET(2) char level_up_digit_1_pal[] = "__OTR__level_up/digit_1.pal";
#define level_up_digit_1_red_png level_up_digit_1_png
static const ALIGN_ASSET(2) char level_up_digit_1_red_pal[] = "__OTR__level_up/digit_1.red.pal";
#define level_up_digit_1_blue_png level_up_digit_1_png
static const ALIGN_ASSET(2) char level_up_digit_1_blue_pal[] = "__OTR__level_up/digit_1.blue.pal";

static const ALIGN_ASSET(2) char level_up_digit_2_png[] = "__OTR__level_up/digit_2";
static const ALIGN_ASSET(2) char level_up_digit_2_pal[] = "__OTR__level_up/digit_2.pal";
#define level_up_digit_2_red_png level_up_digit_2_png
static const ALIGN_ASSET(2) char level_up_digit_2_red_pal[] = "__OTR__level_up/digit_2.red.pal";
#define level_up_digit_2_blue_png level_up_digit_2_png
static const ALIGN_ASSET(2) char level_up_digit_2_blue_pal[] = "__OTR__level_up/digit_2.blue.pal";

static const ALIGN_ASSET(2) char level_up_digit_3_png[] = "__OTR__level_up/digit_3";
static const ALIGN_ASSET(2) char level_up_digit_3_pal[] = "__OTR__level_up/digit_3.pal";
#define level_up_digit_3_red_png level_up_digit_3_png
static const ALIGN_ASSET(2) char level_up_digit_3_red_pal[] = "__OTR__level_up/digit_3.red.pal";
#define level_up_digit_3_blue_png level_up_digit_3_png
static const ALIGN_ASSET(2) char level_up_digit_3_blue_pal[] = "__OTR__level_up/digit_3.blue.pal";

static const ALIGN_ASSET(2) char level_up_digit_4_png[] = "__OTR__level_up/digit_4";
static const ALIGN_ASSET(2) char level_up_digit_4_pal[] = "__OTR__level_up/digit_4.pal";
#define level_up_digit_4_red_png level_up_digit_4_png
static const ALIGN_ASSET(2) char level_up_digit_4_red_pal[] = "__OTR__level_up/digit_4.red.pal";
#define level_up_digit_4_blue_png level_up_digit_4_png
static const ALIGN_ASSET(2) char level_up_digit_4_blue_pal[] = "__OTR__level_up/digit_4.blue.pal";

static const ALIGN_ASSET(2) char level_up_digit_5_png[] = "__OTR__level_up/digit_5";
static const ALIGN_ASSET(2) char level_up_digit_5_pal[] = "__OTR__level_up/digit_5.pal";
#define level_up_digit_5_red_png level_up_digit_5_png
static const ALIGN_ASSET(2) char level_up_digit_5_red_pal[] = "__OTR__level_up/digit_5.red.pal";
#define level_up_digit_5_blue_png level_up_digit_5_png
static const ALIGN_ASSET(2) char level_up_digit_5_blue_pal[] = "__OTR__level_up/digit_5.blue.pal";

static const ALIGN_ASSET(2) char level_up_digit_6_png[] = "__OTR__level_up/digit_6";
static const ALIGN_ASSET(2) char level_up_digit_6_pal[] = "__OTR__level_up/digit_6.pal";
#define level_up_digit_6_red_png level_up_digit_6_png
static const ALIGN_ASSET(2) char level_up_digit_6_red_pal[] = "__OTR__level_up/digit_6.red.pal";
#define level_up_digit_6_blue_png level_up_digit_6_png
static const ALIGN_ASSET(2) char level_up_digit_6_blue_pal[] = "__OTR__level_up/digit_6.blue.pal";

static const ALIGN_ASSET(2) char level_up_digit_7_png[] = "__OTR__level_up/digit_7";
static const ALIGN_ASSET(2) char level_up_digit_7_pal[] = "__OTR__level_up/digit_7.pal";
#define level_up_digit_7_red_png level_up_digit_7_png
static const ALIGN_ASSET(2) char level_up_digit_7_red_pal[] = "__OTR__level_up/digit_7.red.pal";
#define level_up_digit_7_blue_png level_up_digit_7_png
static const ALIGN_ASSET(2) char level_up_digit_7_blue_pal[] = "__OTR__level_up/digit_7.blue.pal";

static const ALIGN_ASSET(2) char level_up_digit_8_png[] = "__OTR__level_up/digit_8";
static const ALIGN_ASSET(2) char level_up_digit_8_pal[] = "__OTR__level_up/digit_8.pal";
#define level_up_digit_8_red_png level_up_digit_8_png
static const ALIGN_ASSET(2) char level_up_digit_8_red_pal[] = "__OTR__level_up/digit_8.red.pal";
#define level_up_digit_8_blue_png level_up_digit_8_png
static const ALIGN_ASSET(2) char level_up_digit_8_blue_pal[] = "__OTR__level_up/digit_8.blue.pal";

static const ALIGN_ASSET(2) char level_up_digit_9_png[] = "__OTR__level_up/digit_9";
static const ALIGN_ASSET(2) char level_up_digit_9_pal[] = "__OTR__level_up/digit_9.pal";
#define level_up_digit_9_red_png level_up_digit_9_png
static const ALIGN_ASSET(2) char level_up_digit_9_red_pal[] = "__OTR__level_up/digit_9.red.pal";
#define level_up_digit_9_blue_png level_up_digit_9_png
static const ALIGN_ASSET(2) char level_up_digit_9_blue_pal[] = "__OTR__level_up/digit_9.blue.pal";

// --- Small digits (CI4 8x8) + green/red/blue palettes ---
static const ALIGN_ASSET(2) char level_up_small_digit_0_png[] = "__OTR__level_up/small_digit_0";
static const ALIGN_ASSET(2) char level_up_small_digit_0_pal[] = "__OTR__level_up/small_digit_0.pal";
#define level_up_small_digit_0_red_png level_up_small_digit_0_png
static const ALIGN_ASSET(2) char level_up_small_digit_0_red_pal[] = "__OTR__level_up/small_digit_0.red.pal";
#define level_up_small_digit_0_blue_png level_up_small_digit_0_png
static const ALIGN_ASSET(2) char level_up_small_digit_0_blue_pal[] = "__OTR__level_up/small_digit_0.blue.pal";

static const ALIGN_ASSET(2) char level_up_small_digit_1_png[] = "__OTR__level_up/small_digit_1";
static const ALIGN_ASSET(2) char level_up_small_digit_1_pal[] = "__OTR__level_up/small_digit_1.pal";
#define level_up_small_digit_1_red_png level_up_small_digit_1_png
static const ALIGN_ASSET(2) char level_up_small_digit_1_red_pal[] = "__OTR__level_up/small_digit_1.red.pal";
#define level_up_small_digit_1_blue_png level_up_small_digit_1_png
static const ALIGN_ASSET(2) char level_up_small_digit_1_blue_pal[] = "__OTR__level_up/small_digit_1.blue.pal";

static const ALIGN_ASSET(2) char level_up_small_digit_2_png[] = "__OTR__level_up/small_digit_2";
static const ALIGN_ASSET(2) char level_up_small_digit_2_pal[] = "__OTR__level_up/small_digit_2.pal";
#define level_up_small_digit_2_red_png level_up_small_digit_2_png
static const ALIGN_ASSET(2) char level_up_small_digit_2_red_pal[] = "__OTR__level_up/small_digit_2.red.pal";
#define level_up_small_digit_2_blue_png level_up_small_digit_2_png
static const ALIGN_ASSET(2) char level_up_small_digit_2_blue_pal[] = "__OTR__level_up/small_digit_2.blue.pal";

static const ALIGN_ASSET(2) char level_up_small_digit_3_png[] = "__OTR__level_up/small_digit_3";
static const ALIGN_ASSET(2) char level_up_small_digit_3_pal[] = "__OTR__level_up/small_digit_3.pal";
#define level_up_small_digit_3_red_png level_up_small_digit_3_png
static const ALIGN_ASSET(2) char level_up_small_digit_3_red_pal[] = "__OTR__level_up/small_digit_3.red.pal";
#define level_up_small_digit_3_blue_png level_up_small_digit_3_png
static const ALIGN_ASSET(2) char level_up_small_digit_3_blue_pal[] = "__OTR__level_up/small_digit_3.blue.pal";

static const ALIGN_ASSET(2) char level_up_small_digit_4_png[] = "__OTR__level_up/small_digit_4";
static const ALIGN_ASSET(2) char level_up_small_digit_4_pal[] = "__OTR__level_up/small_digit_4.pal";
#define level_up_small_digit_4_red_png level_up_small_digit_4_png
static const ALIGN_ASSET(2) char level_up_small_digit_4_red_pal[] = "__OTR__level_up/small_digit_4.red.pal";
#define level_up_small_digit_4_blue_png level_up_small_digit_4_png
static const ALIGN_ASSET(2) char level_up_small_digit_4_blue_pal[] = "__OTR__level_up/small_digit_4.blue.pal";

static const ALIGN_ASSET(2) char level_up_small_digit_5_png[] = "__OTR__level_up/small_digit_5";
static const ALIGN_ASSET(2) char level_up_small_digit_5_pal[] = "__OTR__level_up/small_digit_5.pal";
#define level_up_small_digit_5_red_png level_up_small_digit_5_png
static const ALIGN_ASSET(2) char level_up_small_digit_5_red_pal[] = "__OTR__level_up/small_digit_5.red.pal";
#define level_up_small_digit_5_blue_png level_up_small_digit_5_png
static const ALIGN_ASSET(2) char level_up_small_digit_5_blue_pal[] = "__OTR__level_up/small_digit_5.blue.pal";

static const ALIGN_ASSET(2) char level_up_small_digit_6_png[] = "__OTR__level_up/small_digit_6";
static const ALIGN_ASSET(2) char level_up_small_digit_6_pal[] = "__OTR__level_up/small_digit_6.pal";
#define level_up_small_digit_6_red_png level_up_small_digit_6_png
static const ALIGN_ASSET(2) char level_up_small_digit_6_red_pal[] = "__OTR__level_up/small_digit_6.red.pal";
#define level_up_small_digit_6_blue_png level_up_small_digit_6_png
static const ALIGN_ASSET(2) char level_up_small_digit_6_blue_pal[] = "__OTR__level_up/small_digit_6.blue.pal";

static const ALIGN_ASSET(2) char level_up_small_digit_7_png[] = "__OTR__level_up/small_digit_7";
static const ALIGN_ASSET(2) char level_up_small_digit_7_pal[] = "__OTR__level_up/small_digit_7.pal";
#define level_up_small_digit_7_red_png level_up_small_digit_7_png
static const ALIGN_ASSET(2) char level_up_small_digit_7_red_pal[] = "__OTR__level_up/small_digit_7.red.pal";
#define level_up_small_digit_7_blue_png level_up_small_digit_7_png
static const ALIGN_ASSET(2) char level_up_small_digit_7_blue_pal[] = "__OTR__level_up/small_digit_7.blue.pal";

static const ALIGN_ASSET(2) char level_up_small_digit_8_png[] = "__OTR__level_up/small_digit_8";
static const ALIGN_ASSET(2) char level_up_small_digit_8_pal[] = "__OTR__level_up/small_digit_8.pal";
#define level_up_small_digit_8_red_png level_up_small_digit_8_png
static const ALIGN_ASSET(2) char level_up_small_digit_8_red_pal[] = "__OTR__level_up/small_digit_8.red.pal";
#define level_up_small_digit_8_blue_png level_up_small_digit_8_png
static const ALIGN_ASSET(2) char level_up_small_digit_8_blue_pal[] = "__OTR__level_up/small_digit_8.blue.pal";

static const ALIGN_ASSET(2) char level_up_small_digit_9_png[] = "__OTR__level_up/small_digit_9";
static const ALIGN_ASSET(2) char level_up_small_digit_9_pal[] = "__OTR__level_up/small_digit_9.pal";
#define level_up_small_digit_9_red_png level_up_small_digit_9_png
static const ALIGN_ASSET(2) char level_up_small_digit_9_red_pal[] = "__OTR__level_up/small_digit_9.red.pal";
#define level_up_small_digit_9_blue_png level_up_small_digit_9_png
static const ALIGN_ASSET(2) char level_up_small_digit_9_blue_pal[] = "__OTR__level_up/small_digit_9.blue.pal";

// --- Small arrow (CI4 8x8) + green/red/blue palettes ---
static const ALIGN_ASSET(2) char level_up_small_arrow_png[] = "__OTR__level_up/small_arrow";
static const ALIGN_ASSET(2) char level_up_small_arrow_pal[] = "__OTR__level_up/small_arrow.pal";
#define level_up_small_arrow_red_png level_up_small_arrow_png
static const ALIGN_ASSET(2) char level_up_small_arrow_red_pal[] = "__OTR__level_up/small_arrow.red.pal";
#define level_up_small_arrow_blue_png level_up_small_arrow_png
static const ALIGN_ASSET(2) char level_up_small_arrow_blue_pal[] = "__OTR__level_up/small_arrow.blue.pal";

// --- Select one to upgrade (CI4 208x16) ---
static const ALIGN_ASSET(2) char level_up_select_one_to_upgrade_png[] = "__OTR__level_up/select_one_to_upgrade";
static const ALIGN_ASSET(2) char level_up_select_one_to_upgrade_pal[] = "__OTR__level_up/select_one_to_upgrade.pal";
