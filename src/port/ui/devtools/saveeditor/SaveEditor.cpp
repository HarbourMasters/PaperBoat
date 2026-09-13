#include "SaveEditor.h"
#include "port/ui/UIWidgets.hpp"
#include <string>
#include <spdlog/fmt/fmt.h>
#include <imgui.h>
#include <ship/Context.h>
#include <ship/window/Window.h>
#include <libultraship/bridge/windowbridge.h>
#include "fast/interpreter.h"
#include "fast/Fast3dWindow.h"
#include "fast/Fast3dGui.h"

#include "common_structs.h"
#include "assets/ui.h"

extern "C" {
extern s32 get_global_byte(s32 index);
extern s8 set_global_byte(s32 index, s32 value);

#include "dx/versioning.h"

extern s32 set_global_flag(s32 index);
extern s32 clear_global_flag(s32 index);
extern s32 get_global_flag(s32 index);

extern const s32 CookableItemIDs[];
extern const s32 CookableDiscoveredFlags[];

extern SaveData gCurrentSaveFile;
extern s32 gPausePartnersPartnerIDs[8];
extern intptr_t gItemIconRasterOffsets[349];
extern intptr_t gItemIconPaletteOffsets[349];
}

#pragma push_macro("End")
#undef End

#define MAX_ICON_RASTER_SIZE 349
#define MAX_INVENTORY_SIZE   10
#define MAX_KEY_ITEM_SIZE    32
#define NUM_COOKABLE_RECIPES 52
#define TOTAL_STAR_PIECES    160

#define CVAR_NAME_POPOUT_SAVE_EDITOR "gOpenWindows.SaveEditor"

#define CVAR_SHOW_POPOUT_SAVE_EDITOR CVarGetInteger(CVAR_NAME_POPOUT_SAVE_EDITOR, 0)

ImGuiWindowFlags saveEditorWindowFlags =
    ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoTitleBar;
ImVec4 saveEditorBG = ImVec4 { 0, 0, 0, 0.5f };
ImVec2 itemImageSize = ImVec2(42.0f, 42.0f);

std::vector<std::pair<const char*, const char*>> partyMemberList = {
    { "Goombario", ui_goombario_png },
    { "Kooper", ui_kooper_png },
    { "Bombette", ui_bombette_png },
    { "Parakarry", ui_parakarry_png },
    { "Bow", ui_bow_png },
    { "Watt", ui_watt_png },
    { "Sushie", ui_sushie_png },
    { "Lakilester", ui_lakilester_png },
};

typedef struct {
    const char* name;
    s32 itemID;
} LetterData;

typedef struct {
    const char* location;
    const char* kind;
    s32 flag;
} StarPieceData;

typedef struct {
    const char* name;
    s32 actorType;
    bool isUnused; // UNUSED_*/_DUP/_STUB entries, hidden behind a toggle
} TattleData;

// Standalone letters Parakarry delivers, followed by the chain letter quest that ends
// back at Goompapa with the Lucky Day badge. Chain entries are named after the recipient.
std::vector<LetterData> letterList = {
    { "Letter to Merlon", ITEM_LETTER_TO_MERLON },
    { "Letter to Goompa", ITEM_LETTER_TO_GOOMPA },
    { "Letter to Mort T.", ITEM_LETTER_TO_MORT_T },
    { "Letter to Russ T.", ITEM_LETTER_TO_RUSS_T },
    { "Letter to Mayor Penguin", ITEM_LETTER_TO_MAYOR_PENGUIN },
    { "Letter to Merlow", ITEM_LETTER_TO_MERLOW },
    { "Letter to Fice T.", ITEM_LETTER_TO_FICE_T },
    { "Letter to Nomadimouse", ITEM_LETTER_TO_NOMADIMOUSE },
    { "Letter to Minh T.", ITEM_LETTER_TO_MINH_T },
    { "Letter to Igor", ITEM_LETTER_TO_IGOR },
    { "Letter to Kolorado", ITEM_LETTER_TO_KOLORADO },
    { "Chain: Goompapa (1st)", ITEM_LETTER_CHAIN_GOOMPAPA_1 },
    { "Chain: Franky", ITEM_LETTER_CHAIN_FRANKY },
    { "Chain: Muss T.", ITEM_LETTER_CHAIN_MUSS_T },
    { "Chain: Koover (1st)", ITEM_LETTER_CHAIN_KOOVER_1 },
    { "Chain: Fishmael", ITEM_LETTER_CHAIN_FISHMAEL },
    { "Chain: Koover (2nd)", ITEM_LETTER_CHAIN_KOOVER_2 },
    { "Chain: Mr. E", ITEM_LETTER_CHAIN_MR_E },
    { "Chain: Miss T.", ITEM_LETTER_CHAIN_MISS_T },
    { "Chain: Little Mouser", ITEM_LETTER_CHAIN_LITTLE_MOUSER },
    { "Chain: Dane T. (1st)", ITEM_LETTER_CHAIN_DANE_T_1 },
    { "Chain: Yoshi Kid", ITEM_LETTER_CHAIN_YOSHI_KID },
    { "Chain: Dane T. (2nd)", ITEM_LETTER_CHAIN_DANE_T_2 },
    { "Chain: Frost T.", ITEM_LETTER_CHAIN_FROST_T },
    { "Chain: Goompapa (2nd)", ITEM_LETTER_CHAIN_GOOMPAPA_2 },
};

// The 63 star pieces lying around the overworld - the same set Merluvlee can predict.
std::vector<StarPieceData> starPieceList = {
    { "Goomba Village (kmr_05)", "Overworld", GF_KMR05_Item_StarPiece },
    { "Goomba Village (kmr_11)", "Tree", GF_KMR11_Tree1_StarPiece },
    { "Goomba Village (kmr_00)", "Hidden Panel", GF_KMR00_HiddenPanel },
    { "Goomba Village (kmr_03)", "Hidden Panel", GF_KMR03_HiddenPanel },
    { "Goomba Village (kmr_11)", "Hidden Panel", GF_KMR11_HiddenPanel },
    { "Toad Town (mac_00)", "Overworld", GF_MAC00_Item_StarPiece },
    { "Toad Town (mac_00)", "Hidden Panel", GF_MAC00_HiddenPanel },
    { "Toad Town (mac_02)", "Hidden Panel", GF_MAC02_HiddenPanel },
    { "Toad Town (mac_03)", "Hidden Panel", GF_MAC03_HiddenPanel },
    { "Toad Town (mac_05)", "Hidden Panel", GF_MAC05_HiddenPanel },
    { "Toad Town (mac_01)", "Tree", GF_MAC01_Tree1_StarPiece },
    { "Shooting Star Summit (hos_00)", "Hidden Panel", GF_HOS00_HiddenPanel },
    { "Shooting Star Summit (hos_01)", "Hidden Panel", GF_HOS01_HiddenPanel },
    { "Shooting Star Summit (hos_06)", "Hidden Panel", GF_HOS06_HiddenPanel },
    { "Shooting Star Summit (hos_01)", "Overworld", GF_HOS01_Item_StarPiece },
    { "Toad Town Tunnels (tik_07)", "Overworld", GF_TIK07_Item_StarPiece },
    { "Koopa Village (nok_12)", "Overworld", GF_NOK12_Item_StarPiece },
    { "Koopa Village (nok_01)", "Hidden Panel", GF_NOK01_HiddenPanel },
    { "Koopa Village (nok_13)", "Hidden Panel", GF_NOK13_HiddenPanel },
    { "Koopa Village (nok_14)", "Hidden Panel", GF_NOK14_HiddenPanel },
    { "Koopa Village (nok_02)", "Overworld", GF_NOK02_Item_StarPiece },
    { "Koopa Village (nok_15)", "Tree", GF_NOK15_Tree1_StarPiece },
    { "Mt. Rugged (iwa_02)", "Overworld", GF_IWA02_Item_StarPiece },
    { "Mt. Rugged (iwa_01)", "Hidden Panel", GF_IWA01_HiddenPanel },
    { "Mt. Rugged (iwa_03)", "Overworld", GF_IWA03_Item_StarPiece },
    { "Dry Dry Desert (sbk_33)", "Hidden Panel", GF_SBK33_HiddenPanel },
    { "Dry Dry Outpost (dro_02)", "Hidden Panel", GF_DRO02_HiddenPanel },
    { "Dry Dry Ruins (isk_06)", "Overworld", GF_ISK06_Item_StarPiece },
    { "Boo's Mansion (obk_01)", "Hidden Panel", GF_OBK01_HiddenPanel },
    { "Boo's Mansion (obk_02)", "Hidden Panel", GF_OBK02_HiddenPanel },
    { "Boo's Mansion (obk_04)", "Hidden Panel", GF_OBK04_HiddenPanel },
    { "Boo's Mansion (obk_08)", "Hidden Panel", GF_OBK08_HiddenPanel },
    { "Boo's Mansion (obk_06)", "Crate", GF_OBK06_Crate_StarPiece },
    { "Forever Forest (mim_12)", "Hidden Panel", GF_MIM12_HiddenPanel },
    { "Gusty Gulch (arn_04)", "Overworld", GF_ARN04_Item_StarPiece },
    { "Tubba Blubba's Castle (dgb_03)", "Overworld", GF_DGB03_Item_StarPiece },
    { "Tubba Blubba's Castle (dgb_07)", "Overworld", GF_DGB07_Item_StarPiece },
    { "Shy Guy's Toy Box (omo_04)", "Overworld", GF_OMO04_Item_StarPieceA },
    { "Shy Guy's Toy Box (omo_03)", "Hidden Panel", GF_OMO03_HiddenPanel },
    { "Shy Guy's Toy Box (omo_06)", "Hidden Panel", GF_OMO06_HiddenPanel },
    { "Shy Guy's Toy Box (omo_08)", "Hidden Panel", GF_OMO08_HiddenPanel },
    { "Shy Guy's Toy Box (omo_10)", "Hidden Panel", GF_OMO10_HiddenPanel },
    { "Shy Guy's Toy Box (omo_04)", "Overworld", GF_OMO04_Item_StarPieceB },
    { "Shy Guy's Toy Box (omo_09)", "Overworld", GF_OMO09_Item_StarPiece },
    { "Jade Jungle (jan_02)", "Hidden Panel", GF_JAN02_HiddenPanel },
    { "Jade Jungle (jan_15)", "Hidden Panel", GF_JAN15_HiddenPanel },
    { "Jade Jungle (jan_04)", "Overworld", GF_JAN04_Item_StarPiece },
    { "Jade Jungle (jan_01)", "Tree", GF_JAN01_Tree7_StarPiece },
    { "Jade Jungle (jan_10)", "Overworld", GF_JAN10_Item_StarPiece },
    { "Mt. Lavalava (kzn_09)", "Hidden Panel", GF_KZN09_HiddenPanel },
    { "Mt. Lavalava (kzn_18)", "Hidden Panel", GF_KZN18_HiddenPanel },
    { "Flower Fields (flo_16)", "Overworld", GF_FLO16_Item_StarPiece },
    { "Flower Fields (flo_03)", "Hidden Panel", GF_FLO03_HiddenPanel },
    { "Flower Fields (flo_24)", "Hidden Panel", GF_FLO24_HiddenPanel },
    { "Flower Fields (flo_14)", "Overworld", GF_FLO14_Item_StarPiece },
    { "Flower Fields (flo_25)", "Hidden Panel", GF_FLO25_HiddenPanel },
    { "Flower Fields (flo_08)", "Overworld", GF_FLO08_Item_StarPiece },
    { "Shiver City (sam_10)", "Overworld", GF_SAM10_Item_StarPiece },
    { "Shiver City (sam_01)", "Hidden Panel", GF_SAM01_HiddenPanel },
    { "Shiver City (sam_04)", "Hidden Panel", GF_SAM04_HiddenPanel },
    { "Crystal Palace (pra_15)", "Overworld", GF_PRA15_Item_StarPiece },
    { "Crystal Palace (pra_21)", "Hidden Panel", GF_PRA21_HiddenPanel },
    { "Crystal Palace (pra_22)", "Hidden Panel", GF_PRA22_HiddenPanel },
};

// Tattle flags are one bit per ACTOR_TYPE_*, so this mirrors the whole actor type enum.
std::vector<TattleData> tattleList = {
    { "Red Goomba", ACTOR_TYPE_RED_GOOMBA, false },
    { "Red Paragoomba", ACTOR_TYPE_RED_PARAGOOMBA, false },
    { "Gloomba", ACTOR_TYPE_GLOOMBA, false },
    { "Paragloomba", ACTOR_TYPE_PARAGLOOMBA, false },
    { "Spiked Gloomba", ACTOR_TYPE_SPIKED_GLOOMBA, false },
    { "Dark Koopa", ACTOR_TYPE_DARK_KOOPA, false },
    { "Dark Paratroopa", ACTOR_TYPE_DARK_PARATROOPA, false },
    { "Goomba", ACTOR_TYPE_GOOMBA, false },
    { "Paragoomba", ACTOR_TYPE_PARAGOOMBA, false },
    { "Spiked Goomba", ACTOR_TYPE_SPIKED_GOOMBA, false },
    { "Fuzzy", ACTOR_TYPE_FUZZY, false },
    { "Koopa Troopa", ACTOR_TYPE_KOOPA_TROOPA, false },
    { "Paratroopa", ACTOR_TYPE_PARATROOPA, false },
    { "Bob-omb", ACTOR_TYPE_BOB_OMB, false },
    { "Bob-omb Dup", ACTOR_TYPE_BOB_OMB_DUP, true },
    { "Bullet Bill", ACTOR_TYPE_BULLET_BILL, false },
    { "Bill Blaster", ACTOR_TYPE_BILL_BLASTER, false },
    { "Cleft", ACTOR_TYPE_CLEFT, false },
    { "Monty Mole", ACTOR_TYPE_MONTY_MOLE, false },
    { "Bandit", ACTOR_TYPE_BANDIT, false },
    { "Pokey", ACTOR_TYPE_POKEY, false },
    { "Pokey Mummy", ACTOR_TYPE_POKEY_MUMMY, false },
    { "Swooper", ACTOR_TYPE_SWOOPER, false },
    { "Buzzy Beetle", ACTOR_TYPE_BUZZY_BEETLE, false },
    { "Stone Chomp", ACTOR_TYPE_STONE_CHOMP, false },
    { "Piranha Plant", ACTOR_TYPE_PIRANHA_PLANT, false },
    { "Forest Fuzzy", ACTOR_TYPE_FOREST_FUZZY, false },
    { "Hyper Goomba", ACTOR_TYPE_HYPER_GOOMBA, false },
    { "Hyper Paragoomba", ACTOR_TYPE_HYPER_PARAGOOMBA, false },
    { "Hyper Cleft", ACTOR_TYPE_HYPER_CLEFT, false },
    { "Clubba", ACTOR_TYPE_CLUBBA, false },
    { "Shy Guy", ACTOR_TYPE_SHY_GUY, false },
    { "Groove Guy", ACTOR_TYPE_GROOVE_GUY, false },
    { "Sky Guy", ACTOR_TYPE_SKY_GUY, false },
    { "Medi Guy", ACTOR_TYPE_MEDI_GUY, false },
    { "Pyro Guy", ACTOR_TYPE_PYRO_GUY, false },
    { "Spy Guy", ACTOR_TYPE_SPY_GUY, false },
    { "Fuzzipede", ACTOR_TYPE_FUZZIPEDE, false },
    { "Hurt Plant", ACTOR_TYPE_HURT_PLANT, false },
    { "M. Bush", ACTOR_TYPE_M_BUSH, false },
    { "Aqua Fuzzy", ACTOR_TYPE_AQUA_FUZZY, false },
    { "Jungle Fuzzy", ACTOR_TYPE_JUNGLE_FUZZY, false },
    { "Spear Guy", ACTOR_TYPE_SPEAR_GUY, false },
    { "Lava Bubble", ACTOR_TYPE_LAVA_BUBBLE, false },
    { "Spike Top", ACTOR_TYPE_SPIKE_TOP, false },
    { "Putrid Piranha", ACTOR_TYPE_PUTRID_PIRANHA, false },
    { "Lakitu", ACTOR_TYPE_LAKITU, false },
    { "Spiny", ACTOR_TYPE_SPINY, false },
    { "Monty Mole Boss", ACTOR_TYPE_MONTY_MOLE_BOSS, false },
    { "Bzzap!", ACTOR_TYPE_BZZAP, false },
    { "Crazee Dayzee", ACTOR_TYPE_CRAZEE_DAYZEE, false },
    { "Amazy Dayzee", ACTOR_TYPE_AMAZY_DAYZEE, false },
    { "Ruff Puff", ACTOR_TYPE_RUFF_PUFF, false },
    { "Spike", ACTOR_TYPE_SPIKE, false },
    { "Gulpit", ACTOR_TYPE_GULPIT, false },
    { "Gulpit Rocks", ACTOR_TYPE_GULPIT_ROCKS, false },
    { "White Clubba", ACTOR_TYPE_WHITE_CLUBBA, false },
    { "Frost Piranha", ACTOR_TYPE_FROST_PIRANHA, false },
    { "Swoopula", ACTOR_TYPE_SWOOPULA, false },
    { "Duplighost", ACTOR_TYPE_DUPLIGHOST, false },
    { "Ghost Goombario", ACTOR_TYPE_GHOST_GOOMBARIO, false },
    { "Ghost Kooper", ACTOR_TYPE_GHOST_KOOPER, false },
    { "Ghost Bombette", ACTOR_TYPE_GHOST_BOMBETTE, false },
    { "Ghost Parakarry", ACTOR_TYPE_GHOST_PARAKARRY, false },
    { "Ghost Bow", ACTOR_TYPE_GHOST_BOW, false },
    { "Ghost Watt", ACTOR_TYPE_GHOST_WATT, false },
    { "Ghost Sushie", ACTOR_TYPE_GHOST_SUSHIE, false },
    { "Ghost Lakilester", ACTOR_TYPE_GHOST_LAKILESTER, false },
    { "Albino Dino", ACTOR_TYPE_ALBINO_DINO, false },
    { "Ember", ACTOR_TYPE_EMBER, false },
    { "Bony Beetle", ACTOR_TYPE_BONY_BEETLE, false },
    { "Dry Bones", ACTOR_TYPE_DRY_BONES, false },
    { "Dry Bones 2", ACTOR_TYPE_DRY_BONES2, false },
    { "Bombshell Blaster", ACTOR_TYPE_BOMBSHELL_BLASTER, false },
    { "Bombshell Bill", ACTOR_TYPE_BOMBSHELL_BILL, false },
    { "Hammer Bros", ACTOR_TYPE_HAMMER_BROS, false },
    { "Koopatrol", ACTOR_TYPE_KOOPATROL, false },
    { "Magikoopa", ACTOR_TYPE_MAGIKOOPA, false },
    { "Flying Magikoopa", ACTOR_TYPE_FLYING_MAGIKOOPA, false },
    { "Magiclone", ACTOR_TYPE_MAGICLONE, false },
    { "Flying Magiclone", ACTOR_TYPE_FLYING_MAGICLONE, false },
    { "Red Magikoopa", ACTOR_TYPE_RED_MAGIKOOPA, false },
    { "Flying Red Magikoopa", ACTOR_TYPE_FLYING_RED_MAGIKOOPA, false },
    { "Green Magikoopa", ACTOR_TYPE_GREEN_MAGIKOOPA, false },
    { "Flying Green Magikoopa", ACTOR_TYPE_FLYING_GREEN_MAGIKOOPA, false },
    { "Yellow Magikoopa", ACTOR_TYPE_YELLOW_MAGIKOOPA, false },
    { "Flying Yellow Magikoopa", ACTOR_TYPE_FLYING_YELLOW_MAGIKOOPA, false },
    { "Gray Magikoopa", ACTOR_TYPE_GRAY_MAGIKOOPA, false },
    { "Flying Gray Magikoopa", ACTOR_TYPE_FLYING_GRAY_MAGIKOOPA, false },
    { "White Magikoopa", ACTOR_TYPE_WHITE_MAGIKOOPA, false },
    { "Flying White Magikoopa", ACTOR_TYPE_FLYING_WHITE_MAGIKOOPA, false },
    { "Unused", ACTOR_TYPE_UNUSED_5B, true },
    { "Unused", ACTOR_TYPE_UNUSED_5C, true },
    { "Unused", ACTOR_TYPE_UNUSED_5D, true },
    { "Unused", ACTOR_TYPE_UNUSED_5E, true },
    { "Unused", ACTOR_TYPE_UNUSED_5F, true },
    { "Unused", ACTOR_TYPE_UNUSED_60, true },
    { "Unused", ACTOR_TYPE_UNUSED_61, true },
    { "Unused", ACTOR_TYPE_UNUSED_62, true },
    { "Unused", ACTOR_TYPE_UNUSED_63, true },
    { "Unused", ACTOR_TYPE_UNUSED_64, true },
    { "Unused", ACTOR_TYPE_UNUSED_65, true },
    { "Unused", ACTOR_TYPE_UNUSED_66, true },
    { "Unused", ACTOR_TYPE_UNUSED_67, true },
    { "Unused", ACTOR_TYPE_UNUSED_68, true },
    { "Unused", ACTOR_TYPE_UNUSED_69, true },
    { "Unused", ACTOR_TYPE_UNUSED_6A, true },
    { "Monty Hole", ACTOR_TYPE_MONTY_HOLE, false },
    { "Unused", ACTOR_TYPE_UNUSED_6C, true },
    { "Unused", ACTOR_TYPE_UNUSED_6D, true },
    { "Player", ACTOR_TYPE_PLAYER, false },
    { "Goombario", ACTOR_TYPE_GOOMBARIO, false },
    { "Kooper", ACTOR_TYPE_KOOPER, false },
    { "Bombette", ACTOR_TYPE_BOMBETTE, false },
    { "Parakarry", ACTOR_TYPE_PARAKARRY, false },
    { "Bow", ACTOR_TYPE_BOW, false },
    { "Watt", ACTOR_TYPE_WATT, false },
    { "Sushie", ACTOR_TYPE_SUSHIE, false },
    { "Lakilester", ACTOR_TYPE_LAKILESTER, false },
    { "Twink", ACTOR_TYPE_TWINK, false },
    { "Unused", ACTOR_TYPE_UNUSED_78, true },
    { "Unused", ACTOR_TYPE_UNUSED_79, true },
    { "The Master 1", ACTOR_TYPE_THE_MASTER_1, false },
    { "The Master 2", ACTOR_TYPE_THE_MASTER_2, false },
    { "The Master 3", ACTOR_TYPE_THE_MASTER_3, false },
    { "Chan", ACTOR_TYPE_CHAN, false },
    { "Lee", ACTOR_TYPE_LEE, false },
    { "Lee Goombario", ACTOR_TYPE_LEE_GOOMBARIO, false },
    { "Lee Kooper", ACTOR_TYPE_LEE_KOOPER, false },
    { "Lee Bombette", ACTOR_TYPE_LEE_BOMBETTE, false },
    { "Lee Parakarry", ACTOR_TYPE_LEE_PARAKARRY, false },
    { "Lee Bow", ACTOR_TYPE_LEE_BOW, false },
    { "Lee Watt", ACTOR_TYPE_LEE_WATT, false },
    { "Lee Sushie", ACTOR_TYPE_LEE_SUSHIE, false },
    { "Lee Lakilester", ACTOR_TYPE_LEE_LAKILESTER, false },
    { "Kammy Koopa", ACTOR_TYPE_KAMMY_KOOPA, false },
    { "Jr. Troopa 1", ACTOR_TYPE_JR_TROOPA_1, false },
    { "Jr. Troopa 2", ACTOR_TYPE_JR_TROOPA_2, false },
    { "Jr. Troopa 3", ACTOR_TYPE_JR_TROOPA_3, false },
    { "Jr. Troopa 4", ACTOR_TYPE_JR_TROOPA_4, false },
    { "Jr. Troopa 5", ACTOR_TYPE_JR_TROOPA_5, false },
    { "Jr. Troopa 6", ACTOR_TYPE_JR_TROOPA_6, false },
    { "Jr. Troopa Dup 1", ACTOR_TYPE_JR_TROOPA_DUP1, true },
    { "Jr. Troopa Dup 2", ACTOR_TYPE_JR_TROOPA_DUP2, true },
    { "Blue Goomba Boss", ACTOR_TYPE_BLUE_GOOMBA_BOSS, false },
    { "Red Goomba Boss", ACTOR_TYPE_RED_GOOMBA_BOSS, false },
    { "Goomba King", ACTOR_TYPE_GOOMBA_KING, false },
    { "Goomnut Tree", ACTOR_TYPE_GOOMNUT_TREE, false },
    { "Goombario Tutor 1", ACTOR_TYPE_GOOMBARIO_TUTOR1, false },
    { "Magikoopa Boss", ACTOR_TYPE_MAGIKOOPA_BOSS, false },
    { "Flying Magikoopa Boss", ACTOR_TYPE_FLYING_MAGIKOOPA_BOSS, false },
    { "Magikoopa Dup 1", ACTOR_TYPE_MAGIKOOPA_DUP1, true },
    { "Magikoopa Dup 2", ACTOR_TYPE_MAGIKOOPA_DUP2, true },
    { "Fake Bowser", ACTOR_TYPE_FAKE_BOWSER, false },
    { "Koopa Bros", ACTOR_TYPE_KOOPA_BROS, false },
    { "Green Ninjakoopa", ACTOR_TYPE_GREEN_NINJAKOOPA, false },
    { "Red Ninjakoopa", ACTOR_TYPE_RED_NINJAKOOPA, false },
    { "Black Ninjakoopa", ACTOR_TYPE_BLACK_NINJAKOOPA, false },
    { "Yellow Ninjakoopa", ACTOR_TYPE_YELLOW_NINJAKOOPA, false },
    { "Eldstar", ACTOR_TYPE_ELDSTAR, false },
    { "Buzzar", ACTOR_TYPE_BUZZAR, false },
    { "Tutankoopa", ACTOR_TYPE_TUTANKOOPA, false },
    { "Chomp", ACTOR_TYPE_CHOMP, false },
    { "Tubba Blubba Invincible", ACTOR_TYPE_TUBBA_BLUBBA_INVINCIBLE, false },
    { "Tubba Blubba", ACTOR_TYPE_TUBBA_BLUBBA, false },
    { "Tubba Heart", ACTOR_TYPE_TUBBA_HEART, false },
    { "Stilt Guy", ACTOR_TYPE_STILT_GUY, false },
    { "Shy Stack", ACTOR_TYPE_SHY_STACK, false },
    { "Shy Squad", ACTOR_TYPE_SHY_SQUAD, false },
    { "General Guy", ACTOR_TYPE_GENERAL_GUY, false },
    { "Toy Tank", ACTOR_TYPE_TOY_TANK, false },
    { "Light Bulb", ACTOR_TYPE_LIGHT_BULB, false },
    { "Signal Guy", ACTOR_TYPE_SIGNAL_GUY, false },
    { "Shy Squad Redux", ACTOR_TYPE_SHY_SQUAD_REDUX, false },
    { "Shy Squad Stub", ACTOR_TYPE_SHY_SQUAD_STUB, true },
    { "Anti Guy (Toy Box)", ACTOR_TYPE_ANTI_GUY_OMO, false },
    { "Anti Guy (Bowser's Castle)", ACTOR_TYPE_ANTI_GUY_KPA, false },
    { "Big Lantern Ghost", ACTOR_TYPE_BIG_LANTERN_GHOST, false },
    { "Goomba King Dup", ACTOR_TYPE_GOOMBA_KING_DUP, true },
    { "Lava Piranha Phase 1", ACTOR_TYPE_LAVA_PIRANHA_PHASE_1, false },
    { "Lava Piranha Phase 2", ACTOR_TYPE_LAVA_PIRANHA_PHASE_2, false },
    { "Lava Bud Phase 1", ACTOR_TYPE_LAVA_BUD_PHASE_1, false },
    { "Lava Bud Phase 2", ACTOR_TYPE_LAVA_BUD_PHASE_2, false },
    { "Petit Piranha", ACTOR_TYPE_PETIT_PIRANHA, false },
    { "Petit Piranha Bomb", ACTOR_TYPE_PETIT_PIRANHA_BOMB, false },
    { "Kent C. Koopa", ACTOR_TYPE_KENT_C_KOOPA, false },
    { "Huff N. Puff", ACTOR_TYPE_HUFF_N_PUFF, false },
    { "Tuff Puff", ACTOR_TYPE_TUFF_PUFF, false },
    { "Monstar", ACTOR_TYPE_MONSTAR, false },
    { "Crystal King", ACTOR_TYPE_CRYSTAL_KING, false },
    { "Crystal Clone", ACTOR_TYPE_CRYSTAL_CLONE, false },
    { "Crystal Bit", ACTOR_TYPE_CRYSTAL_BIT, false },
    { "Intro Bowser", ACTOR_TYPE_INTRO_BOWSER, false },
    { "Hallway Bowser", ACTOR_TYPE_HALLWAY_BOWSER, false },
    { "Hallway Bowser Dup", ACTOR_TYPE_HALLWAY_BOWSER_DUP, true },
    { "Final Bowser 1", ACTOR_TYPE_FINAL_BOWSER_1, false },
    { "Final Bowser 1 Dup", ACTOR_TYPE_FINAL_BOWSER_1_DUP, true },
    { "Final Bowser 2", ACTOR_TYPE_FINAL_BOWSER_2, false },
    { "Final Bowser 2 Dup", ACTOR_TYPE_FINAL_BOWSER_2_DUP, true },
    { "Blooper", ACTOR_TYPE_BLOOPER, false },
    { "Electro Blooper 1", ACTOR_TYPE_ELECTRO_BLOOPER1, false },
    { "Electro Blooper 2", ACTOR_TYPE_ELECTRO_BLOOPER2, false },
    { "Super Blooper 1", ACTOR_TYPE_SUPER_BLOOPER1, false },
    { "Super Blooper 2", ACTOR_TYPE_SUPER_BLOOPER2, false },
    { "Blooper Baby", ACTOR_TYPE_BLOOPER_BABY, false },
    { "Lakilester Dup", ACTOR_TYPE_LAKILESTER_DUP, true },
    { "Slot Machine Start", ACTOR_TYPE_SLOT_MACHINE_START, false },
    { "Slot Machine Stop", ACTOR_TYPE_SLOT_MACHINE_STOP, false },
    { "Whacka", ACTOR_TYPE_WHACKA, false },
    { "Slot Machine Start Dup 1", ACTOR_TYPE_SLOT_MACHINE_START_DUP1, true },
    { "Slot Machine Start Dup 2", ACTOR_TYPE_SLOT_MACHINE_START_DUP2, true },
    { "Slot Machine Start Dup 3", ACTOR_TYPE_SLOT_MACHINE_START_DUP3, true },
};

void SaveEditor_PushImageButtonStyle() {
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 1.0f, 0.2f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 1.0f, 0.1f));
}

void SaveEditor_PopImageButtonStyle() {
    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar(1);
}

const char* GetNameFromPath(const char* path) {
    if (path == NULL) {
        return NULL;
    }

    const char* lastSlash = strrchr(path, '/');
    return (lastSlash != NULL) ? (lastSlash + 1) : path;
}

TextureData GetEquipmentTextureId(const char* equipName) {
    TextureData textureData;
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetRawInstance()->GetWindow()->GetGui());
    if (equipName == ICON_gear_boots_1_raster) {
        switch (gPlayerData.bootsLevel) {
            case 0:
                textureData.name = "Boots";
                textureData.textureId = gui->GetTextureByName(ICON_gear_boots_1_raster);
                break;
            case 1:
                textureData.name = "Super Boots";
                textureData.textureId = gui->GetTextureByName(ICON_gear_boots_2_raster);
                break;
            case 2:
                textureData.name = "Ultra Boots";
                textureData.textureId = gui->GetTextureByName(ICON_gear_boots_3_raster);
                break;
            default:
                break;
        }
    }
    if (equipName == ICON_gear_hammer_1_raster) {
        switch (gPlayerData.hammerLevel) {
            case -1:
            case 0:
                textureData.name = gPlayerData.hammerLevel == 0 ? "Hammer" : "None";
                textureData.textureId = gui->GetTextureByName(ICON_gear_hammer_1_raster);
                break;
            case 1:
                textureData.name = "Super Hammer";
                textureData.textureId = gui->GetTextureByName(ICON_gear_hammer_2_raster);
                break;
            case 2:
                textureData.name = "Ultra Hammer";
                textureData.textureId = gui->GetTextureByName(ICON_gear_hammer_3_raster);
                break;
            default:
                break;
        }
    }

    return textureData;
}

TextureData GetRankTexture(int32_t currentRank) {
    TextureData rankData;
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetRawInstance()->GetWindow()->GetGui());

    rankData.textureId = gui->GetTextureByName(currentRank > 1 ? "Ultra Rank" : ui_pause_partner_rank_png);

    return rankData;
}

bool PlayerHasItem(int16_t itemId) {
    for (int i = 0; i < 10; i++) {
        if (gPlayerData.invItems[i] == itemId) {
            return true;
        }
    }
    return false;
}

bool PlayerHasBadge(int16_t badgeId) {
    for (int b = 0; b < 128; b++) {
        if (gPlayerData.badges[b] == badgeId) {
            return true;
        }
    }
    return false;
}

void AddRemove_Badge(int badgeId, bool currentState) {
    if (currentState) {
        for (int b = 0; b < 128; b++) {
            if (gPlayerData.badges[b] == badgeId) {
                gPlayerData.badges[b] = 0;
                break;
            }
        }
    } else {
        for (int b = 0; b < 128; b++) {
            if (gPlayerData.badges[b] == 0) {
                gPlayerData.badges[b] = badgeId;
                break;
            }
        }
    }
}

void AddRemove_Item(int itemId, bool currentState) {
    if (currentState) {
        for (int i = 0; i < 10; i++) {
            if (gPlayerData.invItems[i] == itemId) {
                gPlayerData.invItems[i] = 0;
                break;
            }
        }
    } else {
        for (int i = 0; i < 10; i++) {
            if (gPlayerData.invItems[i] == 0) {
                gPlayerData.invItems[i] = itemId;
                break;
            }
        }
    }
}

bool PlayerHasKeyItem(int16_t itemId) {
    for (int i = 0; i < MAX_KEY_ITEM_SIZE; i++) {
        if (gPlayerData.keyItems[i] == itemId) {
            return true;
        }
    }
    return false;
}

int32_t CountUsedKeyItemSlots() {
    int32_t used = 0;
    for (int i = 0; i < MAX_KEY_ITEM_SIZE; i++) {
        if (gPlayerData.keyItems[i] != ITEM_NONE) {
            used++;
        }
    }
    return used;
}

void AddRemove_KeyItem(int itemId, bool currentState) {
    if (currentState) {
        for (int i = 0; i < MAX_KEY_ITEM_SIZE; i++) {
            if (gPlayerData.keyItems[i] == itemId) {
                gPlayerData.keyItems[i] = ITEM_NONE;
                break;
            }
        }
    } else {
        for (int i = 0; i < MAX_KEY_ITEM_SIZE; i++) {
            if (gPlayerData.keyItems[i] == ITEM_NONE) {
                gPlayerData.keyItems[i] = itemId;
                break;
            }
        }
    }
}

// Mirrors what picking a star piece up does: sets the pickup flag and moves both counters.
void SetStarPieceCollected(const StarPieceData& starPiece, bool collected) {
    bool wasCollected = get_global_flag(starPiece.flag) != 0;

    if (collected == wasCollected) {
        return;
    }

    if (collected) {
        set_global_flag(starPiece.flag);
        if (gPlayerData.starPieces < TOTAL_STAR_PIECES) {
            gPlayerData.starPieces++;
        }
        if (gPlayerData.starPiecesCollected < TOTAL_STAR_PIECES) {
            gPlayerData.starPiecesCollected++;
        }
    } else {
        clear_global_flag(starPiece.flag);
        if (gPlayerData.starPieces > 0) {
            gPlayerData.starPieces--;
        }
        if (gPlayerData.starPiecesCollected > 0) {
            gPlayerData.starPiecesCollected--;
        }
    }
}

// Tattle state lives in the saved game bytes; gBattleStatus.tattleFlags is a runtime mirror
// that battles OR on top, so read both and write both.
bool GetTattleFlag(int32_t actorType) {
    int32_t flags = get_global_byte(EVT_INDEX_OF_GAME_BYTE(GB_Tattles_00) + actorType / 8);

    flags |= gBattleStatus.tattleFlags[actorType / 8];
    return (flags >> (actorType % 8)) & 1;
}

void SetTattleFlag(int32_t actorType, bool known) {
    int32_t byteIndex = actorType / 8;
    int32_t bit = 1 << (actorType % 8);
    int32_t saved = get_global_byte(EVT_INDEX_OF_GAME_BYTE(GB_Tattles_00) + byteIndex) & 0xFF;

    if (known) {
        saved |= bit;
        gBattleStatus.tattleFlags[byteIndex] |= bit;
    } else {
        saved &= ~bit;
        gBattleStatus.tattleFlags[byteIndex] &= ~bit;
    }
    set_global_byte(EVT_INDEX_OF_GAME_BYTE(GB_Tattles_00) + byteIndex, saved);
}

bool ContainsIgnoreCase(const char* haystack, const char* needle) {
    if (needle[0] == '\0') {
        return true;
    }

    for (const char* start = haystack; *start != '\0'; start++) {
        const char* a = start;
        const char* b = needle;

        while (*a != '\0' && *b != '\0') {
            char ca = (*a >= 'A' && *a <= 'Z') ? (char) (*a + 32) : *a;
            char cb = (*b >= 'A' && *b <= 'Z') ? (char) (*b + 32) : *b;

            if (ca != cb) {
                break;
            }
            a++;
            b++;
        }
        if (*b == '\0') {
            return true;
        }
    }
    return false;
}

void SaveEditor_DrawImageButton(int32_t iconIndex, const char* itemType) {
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetRawInstance()->GetWindow()->GetGui());
    const char* rasterPath = reinterpret_cast<const char*>(gItemIconRasterOffsets[iconIndex]);
    const char* palettePath = reinterpret_cast<const char*>(gItemIconPaletteOffsets[iconIndex]);
    ImTextureID itemTexture = gui->GetTextureByName(rasterPath);
    bool hasItem = false;

    if (itemType == "food" || itemType == "battle") {
        hasItem = PlayerHasItem(iconIndex);
    } else if (itemType == "badge") {
        hasItem = PlayerHasBadge(iconIndex);
    } else {
        hasItem = true;
    }

    SaveEditor_PushImageButtonStyle();
    if (ImGui::ImageButton(
            rasterPath, itemTexture, itemImageSize, ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0),
            ImVec4(1, 1, 1, hasItem ? 1.0f : 0.5f)
        ))
    {
        if (itemType == "food" || itemType == "battle") {
            AddRemove_Item(iconIndex, false);
        }
        if (itemType == "badge") {
            AddRemove_Badge(iconIndex, hasItem);
        }
        if (itemType == "inventory") {
            AddRemove_Item(iconIndex, true);
        }
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("%s", GetNameFromPath(rasterPath));
    }
    SaveEditor_PopImageButtonStyle();
}

void SaveEditor_DrawItemList(const char* itemType) {
    int32_t columns = 13;
    ImVec2 padding = ImGui::GetStyle().CellPadding;
    padding.y += 2.0f;

    if (ImGui::BeginChild("ItemChild")) {
        if (ImGui::BeginTable("ItemListTable", columns, ImGuiTableFlags_SizingStretchSame)) {
            ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, padding);
            for (int c = 0; c < columns; c++) {
                ImGui::TableSetupColumn(std::to_string(c).c_str(), ImGuiTableColumnFlags_WidthFixed, itemImageSize.x);
            }

            for (int i = 0; i < MAX_ICON_RASTER_SIZE; i++) {
                if (reinterpret_cast<const char*>(gItemIconRasterOffsets[i]) != nullptr
                    && std::string_view(reinterpret_cast<const char*>(gItemIconRasterOffsets[i])).find(itemType)
                        == std::string_view::npos)
                {
                    continue;
                }

                ImGui::PushID(i);
                ImGui::TableNextColumn();
                SaveEditor_DrawImageButton(i, itemType);
                ImGui::PopID();
            }

            ImGui::PopStyleVar(1);
            ImGui::EndTable();
        }
        ImGui::EndChild();
    }
}

void SaveEditor_DrawPlayerMenu() {
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetRawInstance()->GetWindow()->GetGui());
    ImVec2 padding = ImGui::GetStyle().CellPadding;
    ImVec2 statImageSize = ImVec2(36.0f, 36.0f);
    padding.y += 8.0f;

    if (ImGui::BeginChild("PlayerChild")) {
        if (ImGui::BeginTable("PlayerTable", 2, ImGuiTableFlags_SizingStretchSame)) {
            ImGui::TableNextColumn();

            // Player Stats
            ImGui::SeparatorText("Status");
            if (ImGui::BeginTable("PlayerStats", 2)) {
                ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, padding);
                ImGui::TableSetupColumn("col1", ImGuiTableColumnFlags_WidthFixed, statImageSize.x);
                ImGui::TableSetupColumn("col1", ImGuiTableColumnFlags_WidthStretch);
                // Level
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_pause_mario_large_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t playerLevel = gPlayerData.level;
                if (UIWidgets::SliderInt(
                        "##pLevel", &playerLevel,
                        UIWidgets::IntSliderOptions()
                            .Color(WIDGET_COLOR)
                            .LabelPosition(UIWidgets::LabelPositions::None)
                            .Format("Level: %i")
                            .Min(1)
                            .Max(30)
                    ))
                {
                    gPlayerData.level = playerLevel;
                };

                // Heart Points
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_stat_heart_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t curHealth = gPlayerData.curHP;
                int32_t maxHealth = gPlayerData.curMaxHP;
                if (UIWidgets::SliderInt(
                        "##pCurHP", &curHealth,
                        UIWidgets::IntSliderOptions()
                            .Color(WIDGET_COLOR)
                            .LabelPosition(UIWidgets::LabelPositions::None)
                            .Format("Current HP: %i")
                            .Min(1)
                            .Max(gPlayerData.curMaxHP)
                    ))
                {
                    gPlayerData.curHP = curHealth;
                };
                if (UIWidgets::SliderInt(
                        "##pMaxHP", &maxHealth,
                        UIWidgets::IntSliderOptions()
                            .Color(WIDGET_COLOR)
                            .LabelPosition(UIWidgets::LabelPositions::None)
                            .Format("Max HP: %i")
                            .Step(5)
                            .Min(5)
                            .Max(50)
                    ))
                {
                    gPlayerData.curMaxHP = maxHealth;
                };

                // Flower Points
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_stat_flower_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t curFlower = gPlayerData.curFP;
                int32_t maxFlower = gPlayerData.curMaxFP;
                if (UIWidgets::SliderInt(
                        "##pCurFP", &curFlower,
                        UIWidgets::IntSliderOptions()
                            .Color(WIDGET_COLOR)
                            .LabelPosition(UIWidgets::LabelPositions::None)
                            .Format("Current FP: %i")
                            .Min(1)
                            .Max(gPlayerData.curMaxFP)
                    ))
                {
                    gPlayerData.curFP = curFlower;
                };
                if (UIWidgets::SliderInt(
                        "##pMaxFP", &maxFlower,
                        UIWidgets::IntSliderOptions()
                            .Color(WIDGET_COLOR)
                            .LabelPosition(UIWidgets::LabelPositions::None)
                            .Format("Max FP: %i")
                            .Step(5)
                            .Min(5)
                            .Max(50)
                    ))
                {
                    gPlayerData.curMaxFP = maxFlower;
                };

                // Badge Points
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_pause_stat_bp_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t maxBadgePoints = gPlayerData.maxBP;
                if (UIWidgets::SliderInt(
                        "##pCurBP", &maxBadgePoints,
                        UIWidgets::IntSliderOptions()
                            .Color(WIDGET_COLOR)
                            .LabelPosition(UIWidgets::LabelPositions::None)
                            .Format("Current BP: %i")
                            .Min(3)
                            .Max(30)
                    ))
                {
                    gPlayerData.maxBP = maxBadgePoints;
                };
                ImGui::PopStyleVar(1);
                ImGui::EndTable();
            }

            ImGui::TableNextColumn();
            padding.y -= 4.0f;

            // Player Equipment
            TextureData equipmentData;
            ImGui::SeparatorText("Inventory");
            if (ImGui::BeginTable("PlayerInventory", 2)) {
                ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, padding);
                ImGui::TableSetupColumn("col1", ImGuiTableColumnFlags_WidthFixed, statImageSize.x);
                ImGui::TableSetupColumn("col1", ImGuiTableColumnFlags_WidthStretch);

                SaveEditor_PushImageButtonStyle();
                // Boots
                ImGui::TableNextColumn();
                equipmentData = GetEquipmentTextureId(ICON_gear_boots_1_raster);
                if (ImGui::ImageButton("##pBoots", equipmentData.textureId, statImageSize)) {
                    if (gPlayerData.bootsLevel >= 2) {
                        gPlayerData.bootsLevel = 0;
                    } else {
                        gPlayerData.bootsLevel++;
                    }
                }
                ImGui::TableNextColumn();
                TableCellCenteredText(equipmentData.name, statImageSize);

                // Hammer
                ImGui::TableNextColumn();
                equipmentData = GetEquipmentTextureId(ICON_gear_hammer_1_raster);
                if (ImGui::ImageButton(
                        "##pHammer", equipmentData.textureId, statImageSize, ImVec2(0, 0), ImVec2(1, 1),
                        ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, gPlayerData.hammerLevel == -1 ? 0.5f : 1.0f)
                    ))
                {
                    if (gPlayerData.hammerLevel >= 2) {
                        gPlayerData.hammerLevel = -1;
                    } else {
                        gPlayerData.hammerLevel++;
                    }
                }
                ImGui::TableNextColumn();
                TableCellCenteredText(equipmentData.name, statImageSize);

                // Star Energy
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_files_eldstar_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t curEnergy = (gPlayerData.starPower / 256);
                int32_t maxEnergy = gPlayerData.maxStarPower;
                if (UIWidgets::SliderInt(
                        "##pCurEnergy", &curEnergy,
                        UIWidgets::IntSliderOptions()
                            .Color(WIDGET_COLOR)
                            .LabelPosition(UIWidgets::LabelPositions::None)
                            .Format("Current Energy: %i")
                            .Min(0)
                            .Max(maxEnergy)
                    ))
                {
                    gPlayerData.starPower = (curEnergy * 256);
                };
                if (UIWidgets::SliderInt(
                        "##pMaxEnergy", &maxEnergy,
                        UIWidgets::IntSliderOptions()
                            .Color(WIDGET_COLOR)
                            .LabelPosition(UIWidgets::LabelPositions::None)
                            .Format("Max Energy: %i")
                            .Min(0)
                            .Max(7)
                    ))
                {
                    gPlayerData.maxStarPower = maxEnergy;
                };

                // Star Points
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_status_star_point_0_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t curPoints = gPlayerData.starPoints;
                if (UIWidgets::SliderInt(
                        "##pCurSP", &curPoints,
                        UIWidgets::IntSliderOptions()
                            .Color(WIDGET_COLOR)
                            .LabelPosition(UIWidgets::LabelPositions::None)
                            .Format("Star Points: %i")
                            .Min(0)
                            .Max(99)
                    ))
                {
                    gPlayerData.starPoints = curPoints;
                };

                // Coins
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_status_coin_0_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t curCoins = gPlayerData.coins;
                if (UIWidgets::SliderInt(
                        "##pCurCoins", &curCoins,
                        UIWidgets::IntSliderOptions()
                            .Color(WIDGET_COLOR)
                            .LabelPosition(UIWidgets::LabelPositions::None)
                            .Format("Coins: %i")
                            .Min(0)
                            .Max(999)
                    ))
                {
                    gPlayerData.coins = curCoins;
                };

                // Star Pieces
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_status_star_piece_0_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t curPieces = gPlayerData.starPieces;
                int32_t collectedPieces = gPlayerData.starPiecesCollected;
                if (UIWidgets::SliderInt(
                        "##pCurPieces", &curPieces,
                        UIWidgets::IntSliderOptions()
                            .Color(WIDGET_COLOR)
                            .LabelPosition(UIWidgets::LabelPositions::None)
                            .Format("Current Pieces: %i")
                            .Min(0)
                            .Max(160)
                    ))
                {
                    gPlayerData.starPieces = curPieces;
                };
                if (UIWidgets::SliderInt(
                        "##pColPieces", &collectedPieces,
                        UIWidgets::IntSliderOptions()
                            .Color(WIDGET_COLOR)
                            .LabelPosition(UIWidgets::LabelPositions::None)
                            .Format("Collected Pieces: %i")
                            .Min(0)
                            .Max(160)
                    ))
                {
                    gPlayerData.starPiecesCollected = collectedPieces;
                };

                // Play Time
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_pause_stat_time_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t curTime = ((gPlayerData.frameCounter / 60) / 60);
                if (UIWidgets::SliderInt(
                        "##pCurTime", &curTime,
                        UIWidgets::IntSliderOptions()
                            .Color(WIDGET_COLOR)
                            .LabelPosition(UIWidgets::LabelPositions::None)
                            .Format("Time: %i")
                            .Min(0)
                            .Max(5998)
                    ))
                {
                    gPlayerData.frameCounter = ((curTime * 60) * 60);
                };

                SaveEditor_PopImageButtonStyle();
                ImGui::PopStyleVar(1);
                ImGui::EndTable();
            }

            ImGui::EndTable();
        }
        ImGui::EndChild();
    }
}

void SaveEditor_DrawItemsMenu() {
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetRawInstance()->GetWindow()->GetGui());
    if (ImGui::BeginChild("ItemChild")) {
        for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {

            ImGui::PushID(i);
            if (gPlayerData.invItems[i] == 0) {
                SaveEditor_PushImageButtonStyle();
                ImGui::ImageButton("Empty", gui->GetTextureByName(ui_battle_menu_nothing_png), itemImageSize);
                SaveEditor_PopImageButtonStyle();
            } else {
                SaveEditor_DrawImageButton(gPlayerData.invItems[i], "inventory");
            }
            ImGui::PopID();
            if (i != MAX_INVENTORY_SIZE - 1) {
                ImGui::SameLine();
            }
        }

        ImGui::SeparatorText("Available Items");
        if (ImGui::BeginTabBar("ItemTabBar")) {
            if (ImGui::BeginTabItem("Food")) {
                SaveEditor_DrawItemList("food");
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Battle")) {
                SaveEditor_DrawItemList("battle");
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::EndChild();
    }
}

void SaveEditor_DrawPartyMenu() {
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetRawInstance()->GetWindow()->GetGui());
    ImVec2 padding = ImGui::GetStyle().CellPadding;
    ImVec2 statImageSize = ImVec2(36.0f, 36.0f);
    padding.y += 4.0f;

    if (ImGui::BeginChild("PartyChild")) {
        if (ImGui::BeginTable("PartyTable", 3, ImGuiTableFlags_SizingStretchSame)) {
            ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, padding);
            ImGui::TableSetupColumn("col1", ImGuiTableColumnFlags_WidthFixed, statImageSize.x);
            ImGui::TableSetupColumn("col2", ImGuiTableColumnFlags_WidthFixed, statImageSize.x);
            ImGui::TableSetupColumn("col3", ImGuiTableColumnFlags_WidthStretch);

            int32_t partyIndex = 0;
            SaveEditor_PushImageButtonStyle();
            for (int i = 0; i < 8; i++) {
                ImGui::PushID(partyIndex);
                std::string label = partyMemberList[partyIndex].first;
                int32_t isUnlocked = gPlayerData.partners[gPausePartnersPartnerIDs[i]].enabled;
                int32_t rank = gPlayerData.partners[gPausePartnersPartnerIDs[i]].level;

                ImGui::TableNextColumn();
                if (ImGui::ImageButton(
                        label.c_str(), gui->GetTextureByName(partyMemberList[partyIndex].second), statImageSize,
                        ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, isUnlocked == 0 ? 0.5f : 1.0f)
                    ))
                {
                    if (isUnlocked == 1) {
                        gPlayerData.partners[gPausePartnersPartnerIDs[i]].enabled = 0;
                    } else {
                        gPlayerData.partners[gPausePartnersPartnerIDs[i]].enabled = 1;
                    }
                }

                ImGui::TableNextColumn();
                TextureData rankTexture = GetRankTexture(rank);
                if (ImGui::ImageButton(
                        "Rank", rankTexture.textureId, statImageSize, ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0),
                        ImVec4(1, 1, 1, rank == 0 ? 0.5f : 1.0f)
                    ))
                {
                    if (rank == 2) {
                        gPlayerData.partners[gPausePartnersPartnerIDs[i]].level = 0;
                    } else {
                        gPlayerData.partners[gPausePartnersPartnerIDs[i]].level++;
                    }
                }

                ImGui::TableNextColumn();
                TableCellCenteredText(label.c_str(), statImageSize);
                partyIndex++;
                ImGui::PopID();
            }
            SaveEditor_PopImageButtonStyle();

            ImGui::PopStyleVar(1);
            ImGui::EndTable();
        }
        ImGui::EndChild();
    }
}

void SaveEditor_DrawLettersMenu() {
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetRawInstance()->GetWindow()->GetGui());
    ImVec2 padding = ImGui::GetStyle().CellPadding;
    ImVec2 statImageSize = ImVec2(36.0f, 36.0f);
    padding.y += 4.0f;

    if (ImGui::BeginChild("LettersChild")) {
        int32_t heldLetters = 0;
        for (auto& letter : letterList) {
            if (PlayerHasKeyItem(letter.itemID)) {
                heldLetters++;
            }
        }
        int32_t usedSlots = CountUsedKeyItemSlots();

        ImGui::Text(
            "Held: %d / %d     Key item slots used: %d / %d", heldLetters, (int32_t) letterList.size(), usedSlots,
            MAX_KEY_ITEM_SIZE
        );

        if (UIWidgets::Button("Give All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
            for (auto& letter : letterList) {
                if (!PlayerHasKeyItem(letter.itemID) && CountUsedKeyItemSlots() < MAX_KEY_ITEM_SIZE) {
                    AddRemove_KeyItem(letter.itemID, false);
                }
            }
        }
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Letters share the 32 key item slots, so this stops once they are full.");
        }
        ImGui::SameLine();
        if (UIWidgets::Button("Remove All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
            for (auto& letter : letterList) {
                if (PlayerHasKeyItem(letter.itemID)) {
                    AddRemove_KeyItem(letter.itemID, true);
                }
            }
        }

        ImGui::SeparatorText("Letters");
        if (ImGui::BeginTable("LettersTable", 4, ImGuiTableFlags_SizingStretchSame)) {
            ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, padding);
            ImGui::TableSetupColumn("icon1", ImGuiTableColumnFlags_WidthFixed, statImageSize.x);
            ImGui::TableSetupColumn("name1", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("icon2", ImGuiTableColumnFlags_WidthFixed, statImageSize.x);
            ImGui::TableSetupColumn("name2", ImGuiTableColumnFlags_WidthStretch);

            SaveEditor_PushImageButtonStyle();
            for (int i = 0; i < (int) letterList.size(); i++) {
                const LetterData& letter = letterList[i];
                const char* rasterPath = reinterpret_cast<const char*>(gItemIconRasterOffsets[letter.itemID]);
                bool hasLetter = PlayerHasKeyItem(letter.itemID);

                ImGui::PushID(i);
                ImGui::TableNextColumn();
                if (ImGui::ImageButton(
                        letter.name, gui->GetTextureByName(rasterPath), statImageSize, ImVec2(0, 0), ImVec2(1, 1),
                        ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, hasLetter ? 1.0f : 0.5f)
                    ))
                {
                    AddRemove_KeyItem(letter.itemID, hasLetter);
                }
                ImGui::TableNextColumn();
                TableCellCenteredText(letter.name, statImageSize);
                ImGui::PopID();
            }
            SaveEditor_PopImageButtonStyle();

            ImGui::PopStyleVar(1);
            ImGui::EndTable();
        }
        ImGui::EndChild();
    }
}

void SaveEditor_DrawRecipesMenu() {
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetRawInstance()->GetWindow()->GetGui());
    int32_t columns = 13;
    ImVec2 padding = ImGui::GetStyle().CellPadding;
    padding.y += 2.0f;

    if (ImGui::BeginChild("RecipesChild")) {
        int32_t discovered = 0;
        for (int i = 0; i < NUM_COOKABLE_RECIPES; i++) {
            if (get_global_flag(CookableDiscoveredFlags[i])) {
                discovered++;
            }
        }

        ImGui::Text("Discovered: %d / %d", discovered, NUM_COOKABLE_RECIPES);

        if (UIWidgets::Button("Discover All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
            for (int i = 0; i < NUM_COOKABLE_RECIPES; i++) {
                set_global_flag(CookableDiscoveredFlags[i]);
            }
        }
        ImGui::SameLine();
        if (UIWidgets::Button("Forget All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
            for (int i = 0; i < NUM_COOKABLE_RECIPES; i++) {
                clear_global_flag(CookableDiscoveredFlags[i]);
            }
        }

        ImGui::SeparatorText("Tayce T. Cookbook");
        if (ImGui::BeginTable("RecipesTable", columns, ImGuiTableFlags_SizingStretchSame)) {
            ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, padding);
            for (int c = 0; c < columns; c++) {
                ImGui::TableSetupColumn(std::to_string(c).c_str(), ImGuiTableColumnFlags_WidthFixed, itemImageSize.x);
            }

            SaveEditor_PushImageButtonStyle();
            for (int i = 0; i < NUM_COOKABLE_RECIPES; i++) {
                const char* rasterPath = reinterpret_cast<const char*>(gItemIconRasterOffsets[CookableItemIDs[i]]);
                bool isDiscovered = get_global_flag(CookableDiscoveredFlags[i]) != 0;

                ImGui::PushID(i);
                ImGui::TableNextColumn();
                if (ImGui::ImageButton(
                        rasterPath, gui->GetTextureByName(rasterPath), itemImageSize, ImVec2(0, 0), ImVec2(1, 1),
                        ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, isDiscovered ? 1.0f : 0.5f)
                    ))
                {
                    if (isDiscovered) {
                        clear_global_flag(CookableDiscoveredFlags[i]);
                    } else {
                        set_global_flag(CookableDiscoveredFlags[i]);
                    }
                }
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("%s", GetNameFromPath(rasterPath));
                }
                ImGui::PopID();
            }
            SaveEditor_PopImageButtonStyle();

            ImGui::PopStyleVar(1);
            ImGui::EndTable();
        }
        ImGui::EndChild();
    }
}

void SaveEditor_DrawStarPiecesMenu() {
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetRawInstance()->GetWindow()->GetGui());
    ImVec2 padding = ImGui::GetStyle().CellPadding;
    ImVec2 statImageSize = ImVec2(36.0f, 36.0f);
    padding.y += 4.0f;

    if (ImGui::BeginChild("StarPiecesChild")) {
        if (ImGui::BeginTable("StarPieceCounts", 2)) {
            ImGui::TableSetupColumn("col1", ImGuiTableColumnFlags_WidthFixed, statImageSize.x);
            ImGui::TableSetupColumn("col2", ImGuiTableColumnFlags_WidthStretch);

            ImGui::TableNextColumn();
            ImGui::Image(gui->GetTextureByName(ui_status_star_piece_0_png), statImageSize);
            ImGui::TableNextColumn();
            int32_t curPieces = gPlayerData.starPieces;
            int32_t collectedPieces = gPlayerData.starPiecesCollected;
            if (UIWidgets::SliderInt(
                    "##spCurPieces", &curPieces,
                    UIWidgets::IntSliderOptions()
                        .Color(WIDGET_COLOR)
                        .LabelPosition(UIWidgets::LabelPositions::None)
                        .Format("Current Pieces: %i")
                        .Min(0)
                        .Max(TOTAL_STAR_PIECES)
                ))
            {
                gPlayerData.starPieces = curPieces;
            };
            if (UIWidgets::SliderInt(
                    "##spColPieces", &collectedPieces,
                    UIWidgets::IntSliderOptions()
                        .Color(WIDGET_COLOR)
                        .LabelPosition(UIWidgets::LabelPositions::None)
                        .Format("Collected Pieces: %i")
                        .Min(0)
                        .Max(TOTAL_STAR_PIECES)
                ))
            {
                gPlayerData.starPiecesCollected = collectedPieces;
            };

            ImGui::EndTable();
        }

        int32_t foundCount = 0;
        for (auto& starPiece : starPieceList) {
            if (get_global_flag(starPiece.flag)) {
                foundCount++;
            }
        }

        ImGui::SeparatorText("Overworld Star Pieces");
        ImGui::Text("Found: %d / %d", foundCount, (int32_t) starPieceList.size());
        ImGui::TextWrapped("These are the star pieces lying around the world - the ones Merluvlee can predict. ");

        if (UIWidgets::Button("Collect All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
            for (auto& starPiece : starPieceList) {
                SetStarPieceCollected(starPiece, true);
            }
        }
        ImGui::SameLine();
        if (UIWidgets::Button("Clear All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
            for (auto& starPiece : starPieceList) {
                SetStarPieceCollected(starPiece, false);
            }
        }

        if (ImGui::BeginTable("StarPieceTable", 2, ImGuiTableFlags_SizingStretchSame)) {
            ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, padding);
            for (int i = 0; i < (int) starPieceList.size(); i++) {
                const StarPieceData& starPiece = starPieceList[i];
                bool isCollected = get_global_flag(starPiece.flag) != 0;
                std::string label = fmt::format("{} - {}", starPiece.location, starPiece.kind);

                ImGui::PushID(i);
                ImGui::TableNextColumn();
                if (UIWidgets::Checkbox(label.c_str(), &isCollected, UIWidgets::CheckboxOptions().Color(WIDGET_COLOR)))
                {
                    SetStarPieceCollected(starPiece, isCollected);
                }
                ImGui::PopID();
            }
            ImGui::PopStyleVar(1);
            ImGui::EndTable();
        }
        ImGui::EndChild();
    }
}

void SaveEditor_DrawTattlesMenu() {
    static char tattleFilter[64] = "";
    static bool hideUnusedTattles = true;

    ImVec2 padding = ImGui::GetStyle().CellPadding;
    padding.y += 2.0f;

    if (ImGui::BeginChild("TattlesChild")) {
        int32_t listed = 0;
        int32_t known = 0;
        for (auto& tattle : tattleList) {
            if (hideUnusedTattles && tattle.isUnused) {
                continue;
            }
            if (!ContainsIgnoreCase(tattle.name, tattleFilter)) {
                continue;
            }
            listed++;
            if (GetTattleFlag(tattle.actorType)) {
                known++;
            }
        }

        ImGui::Text("Tattled: %d / %d listed", known, listed);

        ImGui::SetNextItemWidth(220.0f);
        ImGui::InputTextWithHint("##tattleFilter", "Filter by name...", tattleFilter, sizeof(tattleFilter));
        ImGui::SameLine();
        UIWidgets::Checkbox("Hide unused", &hideUnusedTattles, UIWidgets::CheckboxOptions().Color(WIDGET_COLOR));

        if (UIWidgets::Button("Enable All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
            for (auto& tattle : tattleList) {
                if ((hideUnusedTattles && tattle.isUnused) || !ContainsIgnoreCase(tattle.name, tattleFilter)) {
                    continue;
                }
                SetTattleFlag(tattle.actorType, true);
            }
        }
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Applies to the entries currently listed below.");
        }
        ImGui::SameLine();
        if (UIWidgets::Button("Clear All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
            for (auto& tattle : tattleList) {
                if ((hideUnusedTattles && tattle.isUnused) || !ContainsIgnoreCase(tattle.name, tattleFilter)) {
                    continue;
                }
                SetTattleFlag(tattle.actorType, false);
            }
        }
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Applies to the entries currently listed below.");
        }

        ImGui::SeparatorText("Tattle Log");
        if (ImGui::BeginTable("TattleTable", 2, ImGuiTableFlags_SizingStretchSame)) {
            ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, padding);
            for (int i = 0; i < (int) tattleList.size(); i++) {
                const TattleData& tattle = tattleList[i];

                if (hideUnusedTattles && tattle.isUnused) {
                    continue;
                }
                if (!ContainsIgnoreCase(tattle.name, tattleFilter)) {
                    continue;
                }

                bool isKnown = GetTattleFlag(tattle.actorType);
                std::string label = fmt::format("{} (0x{:02X})", tattle.name, tattle.actorType);

                ImGui::PushID(i);
                ImGui::TableNextColumn();
                if (UIWidgets::Checkbox(label.c_str(), &isKnown, UIWidgets::CheckboxOptions().Color(WIDGET_COLOR))) {
                    SetTattleFlag(tattle.actorType, isKnown);
                }
                ImGui::PopID();
            }
            ImGui::PopStyleVar(1);
            ImGui::EndTable();
        }
        ImGui::EndChild();
    }
}

void SaveEditor_DrawTabBar() {
    UIWidgets::PushStyleTabs(WIDGET_COLOR);
    if (ImGui::BeginTabBar("SaveEditorTabBar")) {
        if (ImGui::BeginTabItem("Player")) {
            SaveEditor_DrawPlayerMenu();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Badges")) {
            SaveEditor_DrawItemList("badge");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Items")) {
            SaveEditor_DrawItemsMenu();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Party")) {
            SaveEditor_DrawPartyMenu();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Letters")) {
            SaveEditor_DrawLettersMenu();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Recipes")) {
            SaveEditor_DrawRecipesMenu();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Star Pieces")) {
            SaveEditor_DrawStarPiecesMenu();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Tattles")) {
            SaveEditor_DrawTattlesMenu();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    UIWidgets::PopStyleTabs();
}

void SaveEditorWindow::DrawElement() {
    if (CVAR_SHOW_POPOUT_SAVE_EDITOR) {
        return;
    }

    if (gCurrentSaveFile.magicString[0] == 0) {
        ImGui::Text("No Save File Loaded");
    } else {
        SaveEditor_DrawTabBar();
    }
}

void SaveEditorWindow::Draw() {
    if (!CVAR_SHOW_POPOUT_SAVE_EDITOR) {
        return;
    }

    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, saveEditorBG);
    ImGui::PushStyleColor(ImGuiCol_TitleBg, saveEditorBG);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, saveEditorBG);
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);

    ImGui::SetNextWindowSize(ImVec2(766.0f, 504.0f), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("SaveEditorWindow", nullptr, saveEditorWindowFlags)) {
        if (gCurrentSaveFile.magicString[0] == 0) {
            ImGui::Text("No Save File Loaded");
        } else {
            SaveEditor_DrawTabBar();
        }
    }
    ImGui::End();

    ImGui::PopStyleColor(4);
    ImGui::PopStyleVar(1);
}

void SaveEditorWindow::InitElement() {
}

#pragma pop_macro("End")
