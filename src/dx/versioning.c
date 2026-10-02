#include "dx/versioning.h"
#include "dx/config.h"
#include <string.h>

void ver_deserialize_standard();
void ver_deserialize_vanilla_save(SaveData* save);

/// Store current game data to gCurrentSaveFile
void fio_serialize_state() {
    SaveData* saveData = &gCurrentSaveFile;
    s32 i, j;

    saveData->player = gPlayerData;

    saveData->areaID = gGameStatus.areaID;
    saveData->mapID = gGameStatus.mapID;
    saveData->entryID = gGameStatus.entryID;
    saveData->savePos.x = gGameStatus.savedPos.x;
    saveData->savePos.y = gGameStatus.savedPos.y;
    saveData->savePos.z = gGameStatus.savedPos.z;

    for (i = 0; i < ARRAY_COUNT(gCurrentEncounter.defeatFlags[0]); i++) {
        for (j = 0; j < ARRAY_COUNT(gCurrentEncounter.defeatFlags); j++) {
            saveData->enemyDefeatFlags[j][i] = gCurrentEncounter.defeatFlags[j][i];
        }
    }

    saveData->debugEnemyContact = gGameStatus.debugEnemyContact;
    saveData->debugUnused1 = gGameStatus.debugUnused1;
    saveData->debugUnused2 = gGameStatus.debugUnused2;
    saveData->musicEnabled = gGameStatus.musicEnabled;
}

/// Load game data from gCurrentSaveFile
/// Performs version checking and supports potential migration between versions.
void fio_deserialize_state() {
    SaveData* saveData = &gCurrentSaveFile;

    if (saveData->modName[0] == '\0') {
        // handle loading vanilla saves here
        ver_deserialize_vanilla_save(saveData);
    } else if (strcmp(saveData->modName, DX_MOD_NAME) != 0) {
        // handle loading saves from other mods here
        // by default, dx assumes other mod save data format is vanilla
        ver_deserialize_vanilla_save(saveData);
    } else if (saveData->majorVersion != DX_MOD_VER_MAJOR) {
        // handle breaking changes between major versions here
        ver_deserialize_standard(saveData);
    } else {
        ver_deserialize_standard(saveData);
    }

    gGameStatus.debugEnemyContact = DEBUG_CONTACT_NONE;
    gGameStatus.debugUnused1 = false;
    gGameStatus.debugUnused2 = false;
    gGameStatus.musicEnabled = true;
}

/// Load save file data from a supported save version
/// Assumes no changes in the SaveData, PlayerData, or PartnerData structs and no remapped item IDs.
void ver_deserialize_standard() {
    SaveData* saveData = &gCurrentSaveFile;
    s32 i, j;

    // simply copy the saved player data
    gPlayerData = saveData->player;

    // copy saved game status fields to GameStatus
    gGameStatus.areaID = saveData->areaID;
    gGameStatus.mapID = saveData->mapID;
    gGameStatus.entryID = saveData->entryID;
    gGameStatus.savedPos.x = saveData->savePos.x;
    gGameStatus.savedPos.y = saveData->savePos.y;
    gGameStatus.savedPos.z = saveData->savePos.z;

    // copy saved enemy defeat flags
    for (i = 0; i < ARRAY_COUNT(gCurrentEncounter.defeatFlags[0]); i++) {
        for (j = 0; j < ARRAY_COUNT(gCurrentEncounter.defeatFlags); j++) {
            gCurrentEncounter.defeatFlags[j][i] = saveData->enemyDefeatFlags[j][i];
        }
    }
}

void ver_copy_s8_array(s8* dest, s8* src, s32 srcMax, s32 destMax) {
    s32 i;
    for (i = 0; i < srcMax; i++) {
        dest[i] = src[i];
    }
    for (; i < destMax; i++) {
        dest[i] = 0;
    }
}

void ver_copy_s16_array(s16* dest, s16* src, s32 srcMax, s32 destMax) {
    s32 i;
    for (i = 0; i < srcMax; i++) {
        dest[i] = src[i];
    }
    for (; i < destMax; i++) {
        dest[i] = 0;
    }
}

void ver_copy_s32_array(s32* dest, s32* src, s32 srcMax, s32 destMax) {
    s32 i;
    for (i = 0; i < srcMax; i++) {
        dest[i] = src[i];
    }
    for (; i < destMax; i++) {
        dest[i] = 0;
    }
}

void ver_port_item_ids(s16* array, s16* mapping, s32 size, s32 mapMax) {
    s32 i;

    for (i = 0; i < size; i++) {
        s16 old = array[i];
        if (old < mapMax) {
            array[i] = mapping[old];
        } else {
            array[i] = ITEM_NONE;
        }
    }
}

#define COPY_S8_ARRAY(new, old)   ver_copy_s8_array(new, old, ARRAY_COUNT(old), ARRAY_COUNT(new));
#define COPY_S16_ARRAY(new, old) ver_copy_s16_array(new, old, ARRAY_COUNT(old), ARRAY_COUNT(new));
#define COPY_S32_ARRAY(new, old) ver_copy_s32_array(new, old, ARRAY_COUNT(old), ARRAY_COUNT(new));

#define PORT_ITEM_IDS(array, map) ver_port_item_ids(array, map, ARRAY_COUNT(array), ARRAY_COUNT(map));

// Maps vanilla itemIDs to enum values which may have changed in the mod
// If your mod removes an item, you can remap it to ITEM_NONE or something else here.
s16 VanillaItemIDs[] = {
    [0x000] ITEM_NONE,
    [0x001] ITEM_BOOTS,
    [0x002] ITEM_SUPER_BOOTS,
    [0x003] ITEM_ULTRA_BOOTS,
    [0x004] ITEM_HAMMER,
    [0x005] ITEM_SUPER_HAMMER,
    [0x006] ITEM_ULTRA_HAMMER,
    [0x007] ITEM_LUCKY_STAR,
    [0x008] ITEM_MAP,
    [0x009] ITEM_BIG_MAP,
    [0x00A] ITEM_FIRST_DEGREE_CARD,
    [0x00B] ITEM_SECOND_DEGREE_CARD,
    [0x00C] ITEM_THIRD_DEGREE_CARD,
    [0x00D] ITEM_FOURTH_DEGREE_CARD,
    [0x00E] ITEM_DIPLOMA,
    [0x00F] ITEM_ULTRA_STONE,
    [0x010] ITEM_KOOPA_FORTRESS_KEY,
    [0x011] ITEM_RUINS_KEY,
    [0x012] ITEM_PULSE_STONE,
    [0x013] ITEM_TUBBA_CASTLE_KEY,
    [0x014] ITEM_CRYSTAL_PALACE_KEY,
    [0x015] ITEM_LUNAR_STONE,
    [0x016] ITEM_PYRAMID_STONE,
    [0x017] ITEM_DIAMOND_STONE,
    [0x018] ITEM_GOLDEN_JAR,
    [0x019] ITEM_KOOPER_SHELL,
    [0x01A] ITEM_BOWSER_CASTLE_KEY,
    [0x01B] ITEM_FOREST_PASS,
    [0x01C] ITEM_BOO_WEIGHT,
    [0x01D] ITEM_BOO_PORTRAIT,
    [0x01E] ITEM_CRYSTAL_BERRY,
    [0x01F] ITEM_MYSTICAL_KEY,
    [0x020] ITEM_STOREROOM_KEY,
    [0x021] ITEM_TOY_TRAIN,
    [0x022] ITEM_BOO_RECORD,
    [0x023] ITEM_FRYING_PAN,
    [0x024] ITEM_DICTIONARY,
    [0x025] ITEM_MYSTERY_NOTE,
    [0x026] ITEM_SUSPICIOUS_NOTE,
    [0x027] ITEM_CRYSTAL_BALL,
    [0x028] ITEM_SCREWDRIVER,
    [0x029] ITEM_COOKBOOK,
    [0x02A] ITEM_JADE_RAVEN,
    [0x02B] ITEM_MAGICAL_SEED1,
    [0x02C] ITEM_MAGICAL_SEED2,
    [0x02D] ITEM_MAGICAL_SEED3,
    [0x02E] ITEM_MAGICAL_SEED4,
    [0x02F] ITEM_TOAD_DOLL,
    [0x030] ITEM_CALCULATOR,
    [0x031] ITEM_SNOWMAN_BUCKET,
    [0x032] ITEM_SNOWMAN_SCARF,
    [0x033] ITEM_RED_KEY,
    [0x034] ITEM_BLUE_KEY,
    [0x035] ITEM_UNUSED_LETTER_1,
    [0x036] ITEM_LETTER_TO_MERLON,
    [0x037] ITEM_LETTER_TO_GOOMPA,
    [0x038] ITEM_LETTER_TO_MORT_T,
    [0x039] ITEM_LETTER_TO_RUSS_T,
    [0x03A] ITEM_LETTER_TO_MAYOR_PENGUIN,
    [0x03B] ITEM_LETTER_TO_MERLOW,
    [0x03C] ITEM_LETTER_TO_FICE_T,
    [0x03D] ITEM_LETTER_TO_NOMADIMOUSE,
    [0x03E] ITEM_LETTER_TO_MINH_T,
    [0x03F] ITEM_UNUSED_LETTER_2,
    [0x040] ITEM_LETTER_CHAIN_GOOMPAPA_1,
    [0x041] ITEM_LETTER_TO_IGOR,
    [0x042] ITEM_UNUSED_LETTER_3,
    [0x043] ITEM_UNUSED_LETTER_4,
    [0x044] ITEM_UNUSED_LETTER_5,
    [0x045] ITEM_LETTER_CHAIN_FRANKY,
    [0x046] ITEM_LETTER_CHAIN_MUSS_T,
    [0x047] ITEM_LETTER_CHAIN_KOOVER_1,
    [0x048] ITEM_LETTER_CHAIN_FISHMAEL,
    [0x049] ITEM_LETTER_CHAIN_KOOVER_2,
    [0x04A] ITEM_LETTER_CHAIN_MR_E,
    [0x04B] ITEM_LETTER_CHAIN_MISS_T,
    [0x04C] ITEM_LETTER_CHAIN_LITTLE_MOUSER,
    [0x04D] ITEM_UNUSED_LETTER_6,
    [0x04E] ITEM_LETTER_CHAIN_DANE_T_1,
    [0x04F] ITEM_LETTER_CHAIN_YOSHI_KID,
    [0x050] ITEM_LETTER_CHAIN_DANE_T_2,
    [0x051] ITEM_LETTER_CHAIN_FROST_T,
    [0x052] ITEM_LETTER_CHAIN_GOOMPAPA_2,
    [0x053] ITEM_ARTIFACT,
    [0x054] ITEM_LETTER_TO_KOLORADO,
    [0x055] ITEM_UNUSED_LETTER_7,
    [0x056] ITEM_DOLLY,
    [0x057] ITEM_WATER_STONE,
    [0x058] ITEM_MAGICAL_BEAN,
    [0x059] ITEM_FERTILE_SOIL,
    [0x05A] ITEM_MIRACLE_WATER,
    [0x05B] ITEM_VOLCANO_VASE,
    [0x05C] ITEM_KOOT_THE_TAPE,
    [0x05D] ITEM_BAKING_SUGAR,
    [0x05E] ITEM_BAKING_SALT,
    [0x05F] ITEM_BAKING_EGG,
    [0x060] ITEM_BAKING_CREAM,
    [0x061] ITEM_BAKING_STRAWBERRY,
    [0x062] ITEM_BAKING_BUTTER,
    [0x063] ITEM_BAKING_CLEANSER,
    [0x064] ITEM_BAKING_WATER,
    [0x065] ITEM_BAKING_FLOUR,
    [0x066] ITEM_BAKING_MILK,
    [0x067] ITEM_LYRICS,
    [0x068] ITEM_MELODY,
    [0x069] ITEM_MAILBAG,
    [0x06A] ITEM_PEACH_KEY,
    [0x06B] ITEM_ODD_KEY,
    [0x06C] ITEM_STAR_STONE,
    [0x06D] ITEM_SNEAKY_PARASOL,
    [0x06E] ITEM_KOOT_KOOPA_LEGENDS,
    [0x06F] ITEM_KOOT_LUIGI_AUTOGRAPH,
    [0x070] ITEM_KOOT_EMPTY_WALLET,
    [0x071] ITEM_KOOT_MERLUVLEE_AUTOGRAPH,
    [0x072] ITEM_KOOT_SHELL,
    [0x073] ITEM_KOOT_OLD_PHOTO,
    [0x074] ITEM_KOOT_GLASSES,
    [0x075] ITEM_KOOT_ALT_PHOTO,
    [0x076] ITEM_KOOT_PACKAGE,
    [0x077] ITEM_KOOT_RED_JAR,
    [0x078] ITEM_UNUSED_PEACH_KEY,
    [0x079] ITEM_WAREHOUSE_KEY,
    [0x07A] ITEM_PRISON_KEY,
    [0x07B] ITEM_SILVER_CREDIT,
    [0x07C] ITEM_GOLD_CREDIT,
    [0x07D] ITEM_UNUSED_PRISON_KEY_1,
    [0x07E] ITEM_UNUSED_PRISON_KEY_2,
    [0x07F] ITEM_UNUSED_PRISON_KEY_3,
    [0x080] ITEM_FIRE_FLOWER,
    [0x081] ITEM_SNOWMAN_DOLL,
    [0x082] ITEM_THUNDER_RAGE,
    [0x083] ITEM_SHOOTING_STAR,
    [0x084] ITEM_THUNDER_BOLT,
    [0x085] ITEM_PEBBLE,
    [0x086] ITEM_DUSTY_HAMMER,
    [0x087] ITEM_INSECTICIDE_HERB,
    [0x088] ITEM_STONE_CAP,
    [0x089] ITEM_TASTY_TONIC,
    [0x08A] ITEM_MUSHROOM,
    [0x08B] ITEM_VOLT_SHROOM,
    [0x08C] ITEM_SUPER_SHROOM,
    [0x08D] ITEM_DRIED_SHROOM,
    [0x08E] ITEM_ULTRA_SHROOM,
    [0x08F] ITEM_SLEEPY_SHEEP,
    [0x090] ITEM_POW_BLOCK,
    [0x091] ITEM_HUSTLE_DRINK,
    [0x092] ITEM_STOP_WATCH,
    [0x093] ITEM_WHACKAS_BUMP,
    [0x094] ITEM_APPLE,
    [0x095] ITEM_LIFE_SHROOM,
    [0x096] ITEM_MYSTERY,
    [0x097] ITEM_REPEL_GEL,
    [0x098] ITEM_FRIGHT_JAR,
    [0x099] ITEM_PLEASE_COME_BACK,
    [0x09A] ITEM_DIZZY_DIAL,
    [0x09B] ITEM_SUPER_SODA,
    [0x09C] ITEM_LEMON,
    [0x09D] ITEM_LIME,
    [0x09E] ITEM_BLUE_BERRY,
    [0x09F] ITEM_RED_BERRY,
    [0x0A0] ITEM_YELLOW_BERRY,
    [0x0A1] ITEM_BUBBLE_BERRY,
    [0x0A2] ITEM_JAMMIN_JELLY,
    [0x0A3] ITEM_MAPLE_SYRUP,
    [0x0A4] ITEM_HONEY_SYRUP,
    [0x0A5] ITEM_GOOMNUT,
    [0x0A6] ITEM_KOOPA_LEAF,
    [0x0A7] ITEM_DRIED_PASTA,
    [0x0A8] ITEM_DRIED_FRUIT,
    [0x0A9] ITEM_STRANGE_LEAF,
    [0x0AA] ITEM_CAKE_MIX,
    [0x0AB] ITEM_EGG,
    [0x0AC] ITEM_COCONUT,
    [0x0AD] ITEM_MELON,
    [0x0AE] ITEM_STINKY_HERB,
    [0x0AF] ITEM_ICED_POTATO,
    [0x0B0] ITEM_SPICY_SOUP,
    [0x0B1] ITEM_APPLE_PIE,
    [0x0B2] ITEM_HONEY_ULTRA,
    [0x0B3] ITEM_MAPLE_ULTRA,
    [0x0B4] ITEM_JELLY_ULTRA,
    [0x0B5] ITEM_KOOPASTA,
    [0x0B6] ITEM_FRIED_SHROOM,
    [0x0B7] ITEM_SHROOM_CAKE,
    [0x0B8] ITEM_SHROOM_STEAK,
    [0x0B9] ITEM_HOT_SHROOM,
    [0x0BA] ITEM_SWEET_SHROOM,
    [0x0BB] ITEM_YUMMY_MEAL,
    [0x0BC] ITEM_HEALTHY_JUICE,
    [0x0BD] ITEM_BLAND_MEAL,
    [0x0BE] ITEM_DELUXE_FEAST,
    [0x0BF] ITEM_SPECIAL_SHAKE,
    [0x0C0] ITEM_BIG_COOKIE,
    [0x0C1] ITEM_CAKE,
    [0x0C2] ITEM_MISTAKE,
    [0x0C3] ITEM_KOOPA_TEA,
    [0x0C4] ITEM_HONEY_SUPER,
    [0x0C5] ITEM_MAPLE_SUPER,
    [0x0C6] ITEM_JELLY_SUPER,
    [0x0C7] ITEM_SPAGHETTI,
    [0x0C8] ITEM_EGG_MISSILE,
    [0x0C9] ITEM_FRIED_EGG,
    [0x0CA] ITEM_HONEY_SHROOM,
    [0x0CB] ITEM_HONEY_CANDY,
    [0x0CC] ITEM_ELECTRO_POP,
    [0x0CD] ITEM_FIRE_POP,
    [0x0CE] ITEM_LIME_CANDY,
    [0x0CF] ITEM_COCO_POP,
    [0x0D0] ITEM_LEMON_CANDY,
    [0x0D1] ITEM_JELLY_POP,
    [0x0D2] ITEM_STRANGE_CAKE,
    [0x0D3] ITEM_KOOKY_COOKIE,
    [0x0D4] ITEM_FROZEN_FRIES,
    [0x0D5] ITEM_POTATO_SALAD,
    [0x0D6] ITEM_NUTTY_CAKE,
    [0x0D7] ITEM_MAPLE_SHROOM,
    [0x0D8] ITEM_BOILED_EGG,
    [0x0D9] ITEM_YOSHI_COOKIE,
    [0x0DA] ITEM_JELLY_SHROOM,
    [0x0DB] ITEM_UNUSED_JELLY_SHROOM_1,
    [0x0DC] ITEM_UNUSED_JELLY_SHROOM_2,
    [0x0DD] ITEM_UNUSED_JELLY_SHROOM_3,
    [0x0DE] ITEM_UNUSED_JELLY_SHROOM_4,
    [0x0DF] ITEM_UNUSED_JELLY_SHROOM_5,
    [0x0E0] ITEM_SPIN_SMASH,
    [0x0E1] ITEM_MULTIBOUNCE,
    [0x0E2] ITEM_POWER_PLUS_A,
    [0x0E3] ITEM_DODGE_MASTER,
    [0x0E4] ITEM_POWER_BOUNCE,
    [0x0E5] ITEM_SPIKE_SHIELD,
    [0x0E6] ITEM_FIRST_ATTACK,
    [0x0E7] ITEM_HP_PLUS_A,
    [0x0E8] ITEM_QUAKE_HAMMER,
    [0x0E9] ITEM_DOUBLE_DIP,
    [0x0EA] ITEM_MYSTERY_SCROLL,
    [0x0EB] ITEM_SLEEP_STOMP,
    [0x0EC] ITEM_FIRE_SHIELD,
    [0x0ED] ITEM_QUICK_CHANGE,
    [0x0EE] ITEM_D_DOWN_POUND,
    [0x0EF] ITEM_DIZZY_STOMP,
    [0x0F0] ITEM_SMASH_CHARGE0,
    [0x0F1] ITEM_PRETTY_LUCKY,
    [0x0F2] ITEM_FEELING_FINE,
    [0x0F3] ITEM_ATTACK_FX_A,
    [0x0F4] ITEM_ALLOR_NOTHING,
    [0x0F5] ITEM_HP_DRAIN,
    [0x0F6] ITEM_JUMP_CHARGE0,
    [0x0F7] ITEM_SLOW_GO,
    [0x0F8] ITEM_FP_PLUS_A,
    [0x0F9] ITEM_MEGA_RUSH,
    [0x0FA] ITEM_ICE_POWER,
    [0x0FB] ITEM_DEFEND_PLUS_A,
    [0x0FC] ITEM_PAY_OFF,
    [0x0FD] ITEM_MONEY_MONEY,
    [0x0FE] ITEM_CHILL_OUT,
    [0x0FF] ITEM_HAPPY_HEART_A,
    [0x100] ITEM_ZAP_TAP,
    [0x101] ITEM_BERSERKER,
    [0x102] ITEM_RIGHT_ON,
    [0x103] ITEM_RUNAWAY_PAY,
    [0x104] ITEM_REFUND,
    [0x105] ITEM_FLOWER_SAVER_A,
    [0x106] ITEM_TRIPLE_DIP,
    [0x107] ITEM_HAMMER_THROW,
    [0x108] ITEM_MEGA_QUAKE,
    [0x109] ITEM_SMASH_CHARGE,
    [0x10A] ITEM_JUMP_CHARGE,
    [0x10B] ITEM_S_SMASH_CHG,
    [0x10C] ITEM_S_JUMP_CHG,
    [0x10D] ITEM_POWER_RUSH,
    [0x10E] ITEM_AUTO_JUMP,
    [0x10F] ITEM_AUTO_SMASH,
    [0x110] ITEM_CRAZY_HEART,
    [0x111] ITEM_LAST_STAND,
    [0x112] ITEM_CLOSE_CALL,
    [0x113] ITEM_P_UP_D_DOWN,
    [0x114] ITEM_LUCKY_DAY,
    [0x115] ITEM_MEGA_HP_DRAIN,
    [0x116] ITEM_P_DOWN_D_UP,
    [0x117] ITEM_POWER_QUAKE,
    [0x118] ITEM_AUTO_MULTIBOUNCE,
    [0x119] ITEM_FLOWER_FANATIC,
    [0x11A] ITEM_HEART_FINDER,
    [0x11B] ITEM_FLOWER_FINDER,
    [0x11C] ITEM_SPIN_ATTACK,
    [0x11D] ITEM_DIZZY_ATTACK,
    [0x11E] ITEM_I_SPY,
    [0x11F] ITEM_SPEEDY_SPIN,
    [0x120] ITEM_BUMP_ATTACK,
    [0x121] ITEM_POWER_JUMP,
    [0x122] ITEM_SUPER_JUMP,
    [0x123] ITEM_MEGA_JUMP,
    [0x124] ITEM_POWER_SMASH,
    [0x125] ITEM_SUPER_SMASH,
    [0x126] ITEM_MEGA_SMASH,
    [0x127] ITEM_UNUSED_POWER_SMASH_1,
    [0x128] ITEM_UNUSED_POWER_SMASH_2,
    [0x129] ITEM_DEEP_FOCUS_A,
    [0x12A] ITEM_SUPER_FOCUS,
    [0x12B] ITEM_SHRINK_SMASH,
    [0x12C] ITEM_SHELL_CRACK,
    [0x12D] ITEM_KAIDEN,
    [0x12E] ITEM_D_DOWN_JUMP,
    [0x12F] ITEM_SHRINK_STOMP,
    [0x130] ITEM_DAMAGE_DODGE_A,
    [0x131] ITEM_EARTHQUAKE_JUMP,
    [0x132] ITEM_DEEP_FOCUS_B,
    [0x133] ITEM_DEEP_FOCUS_C,
    [0x134] ITEM_HP_PLUS_B,
    [0x135] ITEM_FP_PLUS_B,
    [0x136] ITEM_HAPPY_HEART_B,
    [0x137] ITEM_HAPPY_HEART_X,
    [0x138] ITEM_FLOWER_SAVER_B,
    [0x139] ITEM_FLOWER_SAVER_X,
    [0x13A] ITEM_DAMAGE_DODGE_B,
    [0x13B] ITEM_DAMAGE_DODGE_X,
    [0x13C] ITEM_POWER_PLUS_B,
    [0x13D] ITEM_POWER_PLUS_X,
    [0x13E] ITEM_DEFEND_PLUS_X,
    [0x13F] ITEM_DEFEND_PLUS_Y,
    [0x140] ITEM_HAPPY_FLOWER_A,
    [0x141] ITEM_HAPPY_FLOWER_B,
    [0x142] ITEM_HAPPY_FLOWER_X,
    [0x143] ITEM_GROUP_FOCUS,
    [0x144] ITEM_PEEKABOO,
    [0x145] ITEM_ATTACK_FX_D,
    [0x146] ITEM_ATTACK_FX_B,
    [0x147] ITEM_ATTACK_FX_E,
    [0x148] ITEM_ATTACK_FX_C,
    [0x149] ITEM_ATTACK_FX_F,
    [0x14A] ITEM_HP_PLUS_C,
    [0x14B] ITEM_HP_PLUS_X,
    [0x14C] ITEM_HP_PLUS_Y,
    [0x14D] ITEM_FP_PLUS_C,
    [0x14E] ITEM_FP_PLUS_X,
    [0x14F] ITEM_FP_PLUS_Y,
    [0x150] ITEM_HEALTHY_HEALTHY,
    [0x151] ITEM_UNUSED_ATTACK_FX_1,
    [0x152] ITEM_UNUSED_ATTACK_FX_2,
    [0x153] ITEM_UNUSED_ATTACK_FX_3,
    [0x154] ITEM_UNUSED_ATTACK_FX_4,
    [0x155] ITEM_PARTNER_ATTACK,
    [0x156] ITEM_HEART,
    [0x157] ITEM_COIN,
    [0x158] ITEM_HEART_PIECE,
    [0x159] ITEM_STAR_POINT,
    [0x15A] ITEM_HEART_POINT,
    [0x15B] ITEM_FLOWER_POINT,
    [0x15C] ITEM_STAR_PIECE,
    [0x15D] ITEM_PRESENT,
    [0x15E] ITEM_CAKE_DONE,
    [0x15F] ITEM_CAKE_BARE,
    [0x160] ITEM_CAKE_PAN,
    [0x161] ITEM_CAKE_BATTER,
    [0x162] ITEM_CAKE_BOWL,
    [0x163] ITEM_CAKE_MIXED,
    [0x164] ITEM_CAKE_WITH_ICING,
    [0x165] ITEM_CAKE_WITH_BERRIES,
    [0x166] ITEM_MENU_HAMMER1,
    [0x167] ITEM_MENU_HAMMER2,
    [0x168] ITEM_MENU_HAMMER3,
    [0x169] ITEM_MENU_BOOTS1,
    [0x16A] ITEM_MENU_BOOTS2,
    [0x16B] ITEM_MENU_BOOTS3,
    [0x16C] ITEM_MENU_ITEMS,
};

void ver_deserialize_vanilla_save(SaveData* newSave) {
    VanillaSaveData oldSave;
    s32 i, j;

    memcpy(&oldSave, newSave, sizeof(VanillaSaveData));
    memset(newSave, 0, sizeof(SaveData));

    strcpy(newSave->magicString, oldSave.magicString);
    memcpy(newSave->modName, oldSave.version, ARRAY_COUNT(oldSave.version));

    // copy metadata
    newSave->saveSlot = oldSave.saveSlot;
    newSave->saveCount = oldSave.saveCount;
    memcpy(newSave->summary.filename, oldSave.summary.filename, ARRAY_COUNT(newSave->summary.filename));
    newSave->summary.level = oldSave.summary.level;
    newSave->summary.timePlayed = oldSave.summary.timePlayed;
    newSave->summary.spiritsRescued = oldSave.summary.spiritsRescued;

    // copy world location
    newSave->areaID = oldSave.areaID;
    newSave->mapID = oldSave.mapID;
    newSave->entryID = oldSave.entryID;
    newSave->savePos = oldSave.savePos;

    // defeat flags are unchanged
    for (i = 0; i < ARRAY_COUNT(gCurrentEncounter.defeatFlags[0]); i++) {
        for (j = 0; j < ARRAY_COUNT(gCurrentEncounter.defeatFlags); j++) {
            newSave->enemyDefeatFlags[j][i] = oldSave.enemyDefeatFlags[j][i];
            gCurrentEncounter.defeatFlags[j][i] = newSave->enemyDefeatFlags[j][i];
        }
    }

    // saved variable arrays may have been expanded
    COPY_S32_ARRAY(newSave->globalFlags, oldSave.globalFlags);
    COPY_S32_ARRAY(newSave->areaFlags, oldSave.areaFlags);
    COPY_S8_ARRAY(newSave->globalBytes, oldSave.globalBytes);
    COPY_S8_ARRAY(newSave->areaBytes, oldSave.areaBytes);

    PlayerData* newPlayer = &newSave->player;
    VanillaPlayerData* oldPlayer = &oldSave.player;

    newPlayer->curHP = oldPlayer->curHP;
    newPlayer->curMaxHP = oldPlayer->curMaxHP;
    newPlayer->hardMaxHP = oldPlayer->hardMaxHP;
    newPlayer->curFP = oldPlayer->curFP;
    newPlayer->curMaxFP = oldPlayer->curMaxFP;
    newPlayer->hardMaxFP = oldPlayer->hardMaxFP;
    newPlayer->maxBP = oldPlayer->maxBP;

    newPlayer->level = oldPlayer->level;
    newPlayer->starPoints = oldPlayer->starPoints;

    newPlayer->bootsLevel = oldPlayer->bootsLevel;
    newPlayer->hammerLevel = oldPlayer->hammerLevel;
    newPlayer->hasActionCommands = oldPlayer->hasActionCommands;

    newPlayer->coins = oldPlayer->coins;
    newPlayer->starPieces = oldPlayer->starPieces;

    newPlayer->curPartner = oldPlayer->curPartner;
    for (i = 0; i < ARRAY_COUNT(oldPlayer->partners); i++) {
        newPlayer->partners[i].enabled = oldPlayer->partners[i].enabled;
        newPlayer->partners[i].level = oldPlayer->partners[i].level;
    }

    COPY_S16_ARRAY(newPlayer->keyItems, oldPlayer->keyItems);
    COPY_S16_ARRAY(newPlayer->badges, oldPlayer->badges);
    COPY_S16_ARRAY(newPlayer->invItems, oldPlayer->invItems);
    COPY_S16_ARRAY(newPlayer->storedItems, oldPlayer->storedItems);
    COPY_S16_ARRAY(newPlayer->equippedBadges, oldPlayer->equippedBadges);

    PORT_ITEM_IDS(newPlayer->keyItems, VanillaItemIDs);
    PORT_ITEM_IDS(newPlayer->badges, VanillaItemIDs);
    PORT_ITEM_IDS(newPlayer->invItems, VanillaItemIDs);
    PORT_ITEM_IDS(newPlayer->storedItems, VanillaItemIDs);
    PORT_ITEM_IDS(newPlayer->equippedBadges, VanillaItemIDs);

    newPlayer->merleeSpellType = oldPlayer->merleeSpellType;
    newPlayer->merleeCastsLeft = oldPlayer->merleeCastsLeft;
    newPlayer->merleeTurnCount = oldPlayer->merleeTurnCount;

    newPlayer->starPower = oldPlayer->starPower;
    newPlayer->maxStarPower = oldPlayer->maxStarPower;
    newPlayer->starBeamLevel = oldPlayer->starBeamLevel;

    newPlayer->actionCommandAttempts = oldPlayer->actionCommandAttempts;
    newPlayer->actionCommandSuccesses = oldPlayer->actionCommandSuccesses;
    newPlayer->hitsTaken = oldPlayer->hitsTaken;
    newPlayer->hitsBlocked = oldPlayer->hitsBlocked;
    newPlayer->playerFirstStrikes = oldPlayer->playerFirstStrikes;
    newPlayer->enemyFirstStrikes = oldPlayer->enemyFirstStrikes;
    newPlayer->powerBounces = oldPlayer->powerBounces;
    newPlayer->battlesCount = oldPlayer->battlesCount;
    newPlayer->battlesWon = oldPlayer->battlesWon;
    newPlayer->fleeAttempts = oldPlayer->fleeAttempts;
    newPlayer->battlesFled = oldPlayer->battlesFled;
    newPlayer->trainingsDone = oldPlayer->trainingsDone;
    newPlayer->walkingStepsTaken = oldPlayer->walkingStepsTaken;
    newPlayer->runningStepsTaken = oldPlayer->runningStepsTaken;
    newPlayer->totalCoinsEarned = oldPlayer->totalCoinsEarned;
    newPlayer->idleFrameCounter = oldPlayer->idleFrameCounter;
    newPlayer->frameCounter = oldPlayer->frameCounter;
    newPlayer->quizzesAnswered = oldPlayer->quizzesAnswered;
    newPlayer->quizzesCorrect = oldPlayer->quizzesCorrect;

    COPY_S32_ARRAY(newPlayer->partnerUnlockedTime, oldPlayer->partnerUnlockedTime);
    COPY_S32_ARRAY(newPlayer->partnerUsedTime, oldPlayer->partnerUsedTime);

    newPlayer->tradeEventStartTime = oldPlayer->tradeEventStartTime;
    newPlayer->droTreeHintTime = oldPlayer->droTreeHintTime;
    newPlayer->starPiecesCollected = oldPlayer->starPiecesCollected;
    newPlayer->jumpGamePlays = oldPlayer->jumpGamePlays;
    newPlayer->jumpGameTotal = oldPlayer->jumpGameTotal;
    newPlayer->jumpGameRecord = oldPlayer->jumpGameRecord;
    newPlayer->smashGamePlays = oldPlayer->smashGamePlays;
    newPlayer->smashGameTotal = oldPlayer->smashGameTotal;
    newPlayer->smashGameRecord = oldPlayer->smashGameRecord;
}
