/* This file is auto-generated. Do not edit. */

#include "common.h"

#define NUM_INGREDIENTS 29

s32 CookingIngredients[] = {
    ITEM_MUSHROOM,
    ITEM_SUPER_SHROOM,
    ITEM_ULTRA_SHROOM,
    ITEM_LIFE_SHROOM,
    ITEM_VOLT_SHROOM,
    ITEM_FIRE_FLOWER,
    ITEM_COCONUT,
    ITEM_LIME,
    ITEM_LEMON,
    ITEM_HONEY_SYRUP,
    ITEM_MAPLE_SYRUP,
    ITEM_JAMMIN_JELLY,
    ITEM_APPLE,
    ITEM_RED_BERRY,
    ITEM_BLUE_BERRY,
    ITEM_YELLOW_BERRY,
    ITEM_GOOMNUT,
    ITEM_KOOPA_LEAF,
    ITEM_DRIED_PASTA,
    ITEM_DRIED_FRUIT,
    ITEM_STRANGE_LEAF,
    ITEM_CAKE_MIX,
    ITEM_EGG,
    ITEM_MELON,
    ITEM_STINKY_HERB,
    ITEM_ICED_POTATO,
    ITEM_DRIED_SHROOM,
    ITEM_BUBBLE_BERRY,
    ITEM_WHACKAS_BUMP,
    -1,
};

CookingResult CookingResults[] = {
    { QUALITY_BAD,    ITEM_MISTAKE },
    { QUALITY_OK,     ITEM_FRIED_SHROOM },
    { QUALITY_OK,     ITEM_SPICY_SOUP },
    { QUALITY_OK,     ITEM_TASTY_TONIC },
    { QUALITY_OK,     ITEM_NUTTY_CAKE },
    { QUALITY_OK,     ITEM_KOOPA_TEA },
    { QUALITY_OK,     ITEM_SPAGHETTI },
    { QUALITY_ODD,    ITEM_DIZZY_DIAL },
    { QUALITY_GOOD,   ITEM_BIG_COOKIE },
    { QUALITY_OK,     ITEM_CAKE },
    { QUALITY_OK,     ITEM_FRIED_EGG },
    { QUALITY_OK,     ITEM_BOILED_EGG },
    { QUALITY_OK,     ITEM_SUPER_SODA },
    { QUALITY_OK,     ITEM_YOSHI_COOKIE },
    { QUALITY_GREAT,  ITEM_DELUXE_FEAST },
    { QUALITY_OK,     ITEM_FROZEN_FRIES },
    { QUALITY_OK,     ITEM_POTATO_SALAD },
    { QUALITY_OK,     ITEM_HOT_SHROOM },
    { QUALITY_GOOD,   ITEM_BLAND_MEAL },
    { QUALITY_OK,     ITEM_HONEY_SHROOM },
    { QUALITY_OK,     ITEM_MAPLE_SHROOM },
    { QUALITY_OK,     ITEM_JELLY_SHROOM },
    { QUALITY_OK,     ITEM_LIFE_SHROOM },
    { QUALITY_OK,     ITEM_VOLT_SHROOM },
    { QUALITY_ODD,    ITEM_SLEEPY_SHEEP },
    { QUALITY_OK,     ITEM_SHROOM_CAKE },
    { QUALITY_OK,     ITEM_SHROOM_STEAK },
    { QUALITY_OK,     ITEM_HONEY_SUPER },
    { QUALITY_OK,     ITEM_MAPLE_SUPER },
    { QUALITY_OK,     ITEM_JELLY_SUPER },
    { QUALITY_GOOD,   ITEM_YUMMY_MEAL },
    { QUALITY_OK,     ITEM_HONEY_ULTRA },
    { QUALITY_OK,     ITEM_MAPLE_ULTRA },
    { QUALITY_OK,     ITEM_JELLY_ULTRA },
    { QUALITY_OK,     ITEM_SWEET_SHROOM },
    { QUALITY_OK,     ITEM_ELECTRO_POP },
    { QUALITY_ODD,    ITEM_THUNDER_RAGE },
    { QUALITY_OK,     ITEM_FIRE_POP },
    { QUALITY_OK,     ITEM_EGG_MISSILE },
    { QUALITY_GOOD,   ITEM_SPECIAL_SHAKE },
    { QUALITY_OK,     ITEM_COCO_POP },
    { QUALITY_GREAT,  ITEM_HEALTHY_JUICE },
    { QUALITY_OK,     ITEM_LIME_CANDY },
    { QUALITY_OK,     ITEM_LEMON_CANDY },
    { QUALITY_OK,     ITEM_HONEY_CANDY },
    { QUALITY_OK,     ITEM_JELLY_POP },
    { QUALITY_OK,     ITEM_APPLE_PIE },
    { QUALITY_OK,     ITEM_KOOPASTA },
    { QUALITY_OK,     ITEM_KOOKY_COOKIE },
    { QUALITY_ODD,    ITEM_FIRE_FLOWER },
    { QUALITY_GOOD,   ITEM_STRANGE_CAKE },
    { -1, -1 },
};

s8 SingleRecipesWithoutCookbook[] = {
     1, // ITEM_MUSHROOM        --> ITEM_FRIED_SHROOM
     1, // ITEM_SUPER_SHROOM    --> ITEM_FRIED_SHROOM
    26, // ITEM_ULTRA_SHROOM    --> ITEM_SHROOM_STEAK
    17, // ITEM_LIFE_SHROOM     --> ITEM_HOT_SHROOM
    17, // ITEM_VOLT_SHROOM     --> ITEM_HOT_SHROOM
     2, // ITEM_FIRE_FLOWER     --> ITEM_SPICY_SOUP
     3, // ITEM_COCONUT         --> ITEM_TASTY_TONIC
     3, // ITEM_LIME            --> ITEM_TASTY_TONIC
     3, // ITEM_LEMON           --> ITEM_TASTY_TONIC
    12, // ITEM_HONEY_SYRUP     --> ITEM_SUPER_SODA
    12, // ITEM_MAPLE_SYRUP     --> ITEM_SUPER_SODA
    12, // ITEM_JAMMIN_JELLY    --> ITEM_SUPER_SODA
    12, // ITEM_APPLE           --> ITEM_SUPER_SODA
     0, // ITEM_RED_BERRY       --> ITEM_MISTAKE
     0, // ITEM_BLUE_BERRY      --> ITEM_MISTAKE
     0, // ITEM_YELLOW_BERRY    --> ITEM_MISTAKE
     4, // ITEM_GOOMNUT         --> ITEM_NUTTY_CAKE
     5, // ITEM_KOOPA_LEAF      --> ITEM_KOOPA_TEA
     6, // ITEM_DRIED_PASTA     --> ITEM_SPAGHETTI
     0, // ITEM_DRIED_FRUIT     --> ITEM_MISTAKE
     0, // ITEM_STRANGE_LEAF    --> ITEM_MISTAKE
     9, // ITEM_CAKE_MIX        --> ITEM_CAKE
    10, // ITEM_EGG             --> ITEM_FRIED_EGG
    39, // ITEM_MELON           --> ITEM_SPECIAL_SHAKE
     0, // ITEM_STINKY_HERB     --> ITEM_MISTAKE
    16, // ITEM_ICED_POTATO     --> ITEM_POTATO_SALAD
     0, // ITEM_DRIED_SHROOM    --> ITEM_MISTAKE
     0, // ITEM_BUBBLE_BERRY    --> ITEM_MISTAKE
     0, // ITEM_WHACKAS_BUMP    --> ITEM_MISTAKE
};

s8 SingleRecipesWithCookbook[] = {
     1, // ITEM_MUSHROOM        --> ITEM_FRIED_SHROOM
     1, // ITEM_SUPER_SHROOM    --> ITEM_FRIED_SHROOM
    26, // ITEM_ULTRA_SHROOM    --> ITEM_SHROOM_STEAK
    17, // ITEM_LIFE_SHROOM     --> ITEM_HOT_SHROOM
    17, // ITEM_VOLT_SHROOM     --> ITEM_HOT_SHROOM
     2, // ITEM_FIRE_FLOWER     --> ITEM_SPICY_SOUP
     3, // ITEM_COCONUT         --> ITEM_TASTY_TONIC
     3, // ITEM_LIME            --> ITEM_TASTY_TONIC
     3, // ITEM_LEMON           --> ITEM_TASTY_TONIC
    12, // ITEM_HONEY_SYRUP     --> ITEM_SUPER_SODA
    12, // ITEM_MAPLE_SYRUP     --> ITEM_SUPER_SODA
    12, // ITEM_JAMMIN_JELLY    --> ITEM_SUPER_SODA
    12, // ITEM_APPLE           --> ITEM_SUPER_SODA
    12, // ITEM_RED_BERRY       --> ITEM_SUPER_SODA
    12, // ITEM_BLUE_BERRY      --> ITEM_SUPER_SODA
    12, // ITEM_YELLOW_BERRY    --> ITEM_SUPER_SODA
     4, // ITEM_GOOMNUT         --> ITEM_NUTTY_CAKE
     5, // ITEM_KOOPA_LEAF      --> ITEM_KOOPA_TEA
     6, // ITEM_DRIED_PASTA     --> ITEM_SPAGHETTI
     0, // ITEM_DRIED_FRUIT     --> ITEM_MISTAKE
     7, // ITEM_STRANGE_LEAF    --> ITEM_DIZZY_DIAL
     9, // ITEM_CAKE_MIX        --> ITEM_CAKE
    10, // ITEM_EGG             --> ITEM_FRIED_EGG
    39, // ITEM_MELON           --> ITEM_SPECIAL_SHAKE
     0, // ITEM_STINKY_HERB     --> ITEM_MISTAKE
    16, // ITEM_ICED_POTATO     --> ITEM_POTATO_SALAD
     1, // ITEM_DRIED_SHROOM    --> ITEM_FRIED_SHROOM
     3, // ITEM_BUBBLE_BERRY    --> ITEM_TASTY_TONIC
    30, // ITEM_WHACKAS_BUMP    --> ITEM_YUMMY_MEAL
};

s8 DoubleRecipesMatrix[] = {
     0, 17, 26, 26, 17, 17,  0,  0,  0, 19, 20, 21,  0,  0,  0,  0, 23, 23, 18, 23, 23, 25, 18,  0,  0, 18,  1,  0,  0,
    -1,  0, 26, 26, 17, 18,  0,  0,  0, 27, 28, 29,  0,  0,  0,  0, 22, 22, 18, 23, 22, 25, 18,  0,  0, 18, 17,  0,  0,
    -1, -1,  0, 26, 26, 30,  0,  0,  0, 31, 32, 33,  0,  0,  0,  0, 22, 22, 30, 23, 22, 34, 30,  0,  0, 30, 26,  0,  0,
    -1, -1, -1,  0,  0, 18,  0,  0,  0, 27, 28, 29,  0,  0,  0,  0, 22, 22, 18, 23, 22, 34, 18,  0,  0, 18, 26,  0,  0,
    -1, -1, -1, -1,  0, 18,  0,  0,  0, 27, 28, 29,  0,  0,  0,  0, 22, 22, 18, 36,  7, 35, 18,  0,  0, 18, 17,  0,  0,
    -1, -1, -1, -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18,  0,  0,  0,  0, 37, 38,  0,  0, 15,  1,  0,  0,
    -1, -1, -1, -1, -1, -1,  0,  0,  0,  3, 12, 39, 12, 12, 12, 12,  0, 12, 18,  0,  0, 40,  0, 12,  0, 18,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1,  0, 12,  3, 12, 39, 12, 12, 12, 12,  0, 12,  0,  0,  0, 42,  0, 39,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1,  0,  3, 12, 39, 12, 12, 12, 12,  0, 12,  0,  0,  0, 43,  0, 39,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, 12, 39,  3,  3,  3,  3,  0, 12,  0,  0,  0, 44,  0, 39,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, 39, 12, 12, 12, 12,  0, 12,  0,  0,  0, 48,  0, 39,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, 39, 39, 39, 39,  0, 12,  0,  0,  0, 45,  0, 39,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, 12, 12, 12,  0,  0,  0,  0,  0, 46,  0, 39,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, 12, 12,  0, 18, 18,  0, 24,  8,  0, 39,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, 12,  0, 18, 18,  0, 24,  8,  0, 39,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0, 18, 18,  0, 24,  8,  0, 39,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, 18, 18,  0, 18,  8,  0,  0,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, 47,  0,  0, 48,  0, 39,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, 30, 18,  0, 18,  0,  0, 18,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, 49,  0,  0,  0,  0, 30,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, 50, 11, 39,  7, 30,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  8, 13, 48, 18,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0, 11, 18,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,
};

ExtraCookingPair ExtraDoubleRecipes[] = {
    { ITEM_SPECIAL_SHAKE, ITEM_DRIED_SHROOM, 41 },
    { ITEM_SPECIAL_SHAKE, ITEM_STRANGE_LEAF, 41 },
    { ITEM_SPECIAL_SHAKE, ITEM_STINKY_HERB, 41 },
    { ITEM_POTATO_SALAD, ITEM_SPAGHETTI, 30 },
    { ITEM_POTATO_SALAD, ITEM_FRIED_SHROOM, 18 },
    { ITEM_POTATO_SALAD, ITEM_HOT_SHROOM, 30 },
    { ITEM_POTATO_SALAD, ITEM_SHROOM_STEAK, 14 },
    { ITEM_STRANGE_LEAF, ITEM_WHACKAS_BUMP, 14 },
};

s32 MysteryResultOptions[] = {
    ITEM_FIRE_FLOWER,
    ITEM_TASTY_TONIC,
    ITEM_SUPER_SODA,
    ITEM_SLEEPY_SHEEP,
    ITEM_LIFE_SHROOM,
    ITEM_DIZZY_DIAL,
    ITEM_VOLT_SHROOM,
    ITEM_FRIED_SHROOM,
    ITEM_KOOPASTA,
    ITEM_SPICY_SOUP,
    ITEM_KOOPA_TEA,
    ITEM_SPAGHETTI,
    ITEM_FRIED_EGG,
    ITEM_BOILED_EGG,
    ITEM_POTATO_SALAD,
    ITEM_HONEY_SHROOM,
    ITEM_BLAND_MEAL,
    ITEM_THUNDER_RAGE,
    ITEM_EGG_MISSILE,
    ITEM_APPLE_PIE,
    ITEM_KOOKY_COOKIE,
    ITEM_BIG_COOKIE,
    ITEM_SPECIAL_SHAKE,
};

const s32 CookableItemIDs[] = {
    ITEM_SPICY_SOUP,
    ITEM_APPLE_PIE,
    ITEM_HONEY_ULTRA,
    ITEM_MAPLE_ULTRA,
    ITEM_JELLY_ULTRA,
    ITEM_KOOPASTA,
    ITEM_FRIED_SHROOM,
    ITEM_SHROOM_CAKE,
    ITEM_SHROOM_STEAK,
    ITEM_HOT_SHROOM,
    ITEM_SWEET_SHROOM,
    ITEM_BLAND_MEAL,
    ITEM_YUMMY_MEAL,
    ITEM_DELUXE_FEAST,
    ITEM_SPECIAL_SHAKE,
    ITEM_HEALTHY_JUICE,
    ITEM_BIG_COOKIE,
    ITEM_CAKE,
    ITEM_MISTAKE,
    ITEM_KOOPA_TEA,
    ITEM_HONEY_SUPER,
    ITEM_MAPLE_SUPER,
    ITEM_JELLY_SUPER,
    ITEM_SPAGHETTI,
    ITEM_EGG_MISSILE,
    ITEM_FRIED_EGG,
    ITEM_HONEY_SHROOM,
    ITEM_HONEY_CANDY,
    ITEM_ELECTRO_POP,
    ITEM_FIRE_POP,
    ITEM_LIME_CANDY,
    ITEM_COCO_POP,
    ITEM_LEMON_CANDY,
    ITEM_JELLY_POP,
    ITEM_STRANGE_CAKE,
    ITEM_KOOKY_COOKIE,
    ITEM_FROZEN_FRIES,
    ITEM_POTATO_SALAD,
    ITEM_NUTTY_CAKE,
    ITEM_MAPLE_SHROOM,
    ITEM_BOILED_EGG,
    ITEM_YOSHI_COOKIE,
    ITEM_JELLY_SHROOM,
    ITEM_TASTY_TONIC,
    ITEM_DIZZY_DIAL,
    ITEM_SUPER_SODA,
    ITEM_REPEL_GEL,
    ITEM_LIFE_SHROOM,
    ITEM_VOLT_SHROOM,
    ITEM_SLEEPY_SHEEP,
    ITEM_THUNDER_RAGE,
    ITEM_FIRE_FLOWER,
};

const s32 CookableDiscoveredFlags[] = {
    GF_MAC02_DiscoveredRecipe_00,
    GF_MAC02_DiscoveredRecipe_01,
    GF_MAC02_DiscoveredRecipe_02,
    GF_MAC02_DiscoveredRecipe_03,
    GF_MAC02_DiscoveredRecipe_04,
    GF_MAC02_DiscoveredRecipe_05,
    GF_MAC02_DiscoveredRecipe_06,
    GF_MAC02_DiscoveredRecipe_07,
    GF_MAC02_DiscoveredRecipe_08,
    GF_MAC02_DiscoveredRecipe_09,
    GF_MAC02_DiscoveredRecipe_0A,
    GF_MAC02_DiscoveredRecipe_0B,
    GF_MAC02_DiscoveredRecipe_0C,
    GF_MAC02_DiscoveredRecipe_0D,
    GF_MAC02_DiscoveredRecipe_0E,
    GF_MAC02_DiscoveredRecipe_0F,
    GF_MAC02_DiscoveredRecipe_10,
    GF_MAC02_DiscoveredRecipe_11,
    GF_MAC02_DiscoveredRecipe_12,
    GF_MAC02_DiscoveredRecipe_13,
    GF_MAC02_DiscoveredRecipe_14,
    GF_MAC02_DiscoveredRecipe_15,
    GF_MAC02_DiscoveredRecipe_16,
    GF_MAC02_DiscoveredRecipe_17,
    GF_MAC02_DiscoveredRecipe_18,
    GF_MAC02_DiscoveredRecipe_19,
    GF_MAC02_DiscoveredRecipe_1A,
    GF_MAC02_DiscoveredRecipe_1B,
    GF_MAC02_DiscoveredRecipe_1C,
    GF_MAC02_DiscoveredRecipe_1D,
    GF_MAC02_DiscoveredRecipe_1E,
    GF_MAC02_DiscoveredRecipe_1F,
    GF_MAC02_DiscoveredRecipe_20,
    GF_MAC02_DiscoveredRecipe_21,
    GF_MAC02_DiscoveredRecipe_22,
    GF_MAC02_DiscoveredRecipe_23,
    GF_MAC02_DiscoveredRecipe_24,
    GF_MAC02_DiscoveredRecipe_25,
    GF_MAC02_DiscoveredRecipe_26,
    GF_MAC02_DiscoveredRecipe_27,
    GF_MAC02_DiscoveredRecipe_28,
    GF_MAC02_DiscoveredRecipe_29,
    GF_MAC02_DiscoveredRecipe_2A,
    GF_MAC02_DiscoveredRecipe_2B,
    GF_MAC02_DiscoveredRecipe_2C,
    GF_MAC02_DiscoveredRecipe_2D,
    GF_MAC02_DiscoveredRecipe_2E,
    GF_MAC02_DiscoveredRecipe_2F,
    GF_MAC02_DiscoveredRecipe_30,
    GF_MAC02_DiscoveredRecipe_31,
    GF_MAC02_DiscoveredRecipe_32,
    GF_MAC02_DiscoveredRecipe_33,
};

