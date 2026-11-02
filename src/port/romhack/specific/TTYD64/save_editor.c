#include "common.h"
#include "script_api/macros.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/TTYD64.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/world/maps.h"

#define TTYD64_TOTAL_STAR_PIECES 134

static const ModSaveEditorEntry sStarPieces[] = {
    { "Dry Dry Outpost (dro_04)", "Overworld", 0, GameFlag(4861), 0 },
    { "Flower Fields (flo_27)", "Overworld", 0, GameFlag(5513), 0 },
    { "Shooting Star Summit (hos_04)", "Overworld", 0, GameFlag(4642), 0 },
    { "Mt Rugged (iwa_03)", "Overworld", 0, GameFlag(4826), 0 },
    { "Mt Rugged (iwa_11)", "Overworld", 0, GameFlag(4823), 0 },
    { "Jade Jungle (jan_11)", "Overworld", 0, GameFlag(5382), 0 },
    { "Jade Jungle (jan_13)", "Overworld", 0, GameFlag(5387), 0 },
    { "Jade Jungle (jan_22)", "Overworld", 0, GameFlag(5384), 0 },
    { "Jade Jungle (jan_24)", "Overworld", 0, GameFlag(5388), 0 },
    { "Peach's Castle (kkj_16)", "Overworld", 0, GameFlag(4608), 0 },
    { "Peach's Castle (kkj_18)", "Overworld", 0, GameFlag(4612), 0 },
    { "Peach's Castle (kkj_30)", "Overworld", 0, GameFlag(4610), 0 },
    { "Peach's Castle (kkj_30)", "Overworld", 0, GameFlag(4611), 0 },
    { "Goomba Region (kmr_34)", "Overworld", 0, GameFlag(4213), 0 },
    { "Bowser's Castle (kpa_01)", "Overworld", 0, GameFlag(5693), 0 },
    { "Bowser's Castle (kpa_130)", "Overworld", 0, GameFlag(5698), 0 },
    { "Bowser's Castle (kpa_134)", "Overworld", 0, GameFlag(5697), 0 },
    { "Bowser's Castle (kpa_63)", "Overworld", 0, GameFlag(5688), 0 },
    { "Toad Town (mac_00)", "Overworld", 0, GameFlag(4466), 0 },
    { "Toad Town (mac_07)", "Overworld", 0, GameFlag(4476), 0 },
    { "Koopa Region (nok_01)", "Overworld", 0, GameFlag(4717), 0 },
    { "Koopa Region (nok_02)", "Overworld", 0, GameFlag(4718), 0 },
    { "Boo's Mansion (obk_08)", "Overworld", 0, GameFlag(5089), 0 },
    { "Shy Guy's Toybox (omo_04)", "Overworld", 0, GameFlag(5252), 0 },
    { "Pit of the 100 Trials (pit_00)", "Overworld", 0, GameFlag(4723), 0 },
    { "Mt Shiver (sam_06)", "Overworld", 0, GameFlag(5567), 0 },
    { "Toad Town Tunnels (tik_03)", "Overworld", 0, GameFlag(4537), 0 },
    { "Koopa Bros Fortress (trd_01)", "Overworld", 0, GameFlag(638), 0 },
    { "Koopa Bros Fortress (trd_03)", "Overworld", 0, GameFlag(4766), 0 },
    { "Rogueport (tyd_00)", "Overworld", 0, GameFlag(4556), 0 },
    { "Rogueport (tyd_00)", "Overworld", 0, GameFlag(4558), 0 },
    { "Rogueport (tyd_00)", "Overworld", 0, GameFlag(4559), 0 },
    { "Rogueport (tyd_00)", "Overworld", 0, GameFlag(4560), 0 },
    { "Petal Meadows (tyd_01)", "Overworld", 0, GameFlag(4713), 0 },
    { "Abandoned Facility (tyd_06)", "Overworld", 0, GameFlag(5522), 0 },
    { "Factory (tyd_07)", "Overworld", 0, GameFlag(5573), 0 },
    { "Rogueport (tyd_00)", "Hidden Panel", 0, GameFlag(4561), 0 },
    { "Rogueport (tyd_00)", "Hidden Panel", 0, GameFlag(4562), 0 },
    { "Toad Town (mac_02)", "Crate", 0, GameFlag(4467), 0 },
    { "Great Tree (tyd_02)", "Bush", 0, GameFlag(4864), 0 },
    { "Koopa Region (nok_01)", "Bob-omb Minigame", 0, GameFlag(4719), 0 },
};

static const ModSaveEditorEntry sShineSprites[] = {
    { "Tubba's Castle (dgb_00)", "Shine Block", 0, GameFlag(5168), 0 },
    { "Tubba's Castle (dgb_04)", "Shine Block", 0, GameFlag(1046), 0 },
    { "Dry Dry Outpost (dro_02)", "Shine Block", 0, GameFlag(4858), 0 },
    { "Flower Fields (flo_08)", "Shine Block", 0, GameFlag(1402), 0 },
    { "Flower Fields (flo_16)", "Shine Block", 0, GameFlag(1403), 0 },
    { "Flower Fields (flo_26)", "Shine Block", 0, GameFlag(5519), 0 },
    { "Flower Fields (flo_27)", "Shine Block 1", 0, GameFlag(5514), 0 },
    { "Flower Fields (flo_27)", "Shine Block 2", 0, GameFlag(5515), 0 },
    { "Flower Fields (flo_27)", "Shine Block 3", 0, GameFlag(5516), 0 },
    { "Flower Fields (flo_27)", "Shine Block 4", 0, GameFlag(5517), 0 },
    { "Flower Fields (flo_28)", "Shine Block", 0, GameFlag(5520), 0 },
    { "Dry Dry Ruins (isk_10)", "Shine Block", 0, GameFlag(903), 0 },
    { "Dry Dry Ruins (isk_20)", "Shine Block", 0, GameFlag(5006), 0 },
    { "Mt Rugged (iwa_00)", "Shine Block", 0, GameFlag(4825), 0 },
    { "Mt Rugged (iwa_10)", "Shine Block", 0, GameFlag(721), 0 },
    { "Mt Rugged (iwa_11)", "Shine Block", 0, GameFlag(4824), 0 },
    { "Jade Jungle (jan_00)", "Shine Block", 0, GameFlag(5379), 0 },
    { "Jade Jungle (jan_08)", "Shine Block", 0, GameFlag(1278), 0 },
    { "Jade Jungle (jan_25)", "Shine Block", 0, GameFlag(5393), 0 },
    { "Jade Jungle (jan_26)", "Shine Block", 0, GameFlag(5437), 0 },
    { "Jade Jungle (jan_27)", "Shine Block", 0, GameFlag(5385), 0 },
    { "Mt Lavalava (kzn_04)", "Shine Block", 0, GameFlag(1328), 0 },
    { "Mt Lavalava (kzn_09)", "Shine Block", 0, GameFlag(1329), 0 },
    { "Toad Town (mac_07)", "Shine Block", 0, GameFlag(4477), 0 },
    { "Koopa Region (nok_05)", "Shine Block", 0, GameFlag(4720), 0 },
    { "Boo's Mansion (obk_01)", "Shine Block", 0, GameFlag(5093), 0 },
    { "Boo's Mansion (obk_10)", "Shine Block", 0, GameFlag(5090), 0 },
    { "Shy Guy's Toybox (omo_11)", "Shine Block 1", 0, GameFlag(5264), 0 },
    { "Shy Guy's Toybox (omo_11)", "Shine Block 2", 0, GameFlag(1194), 0 },
    { "Mt Shiver (sam_06)", "Shine Block", 0, GameFlag(5566), 0 },
    { "Mt Shiver (sam_08)", "Shine Block", 0, GameFlag(1457), 0 },
    { "Dry Dry Desert (sbk_56)", "Shine Block", 0, GameFlag(829), 0 },
    { "Toad Town Tunnels (tik_03)", "Shine Block", 0, GameFlag(4538), 0 },
    { "Toad Town Tunnels (tik_07)", "Shine Block", 0, GameFlag(433), 0 },
    { "Toad Town Tunnels (tik_10)", "Shine Block", 0, GameFlag(434), 0 },
    { "Toad Town Tunnels (tik_12)", "Shine Block 1", 0, GameFlag(435), 0 },
    { "Toad Town Tunnels (tik_12)", "Shine Block 2", 0, GameFlag(4540), 0 },
    { "Toad Town Tunnels (tik_17)", "Shine Block", 0, GameFlag(436), 0 },
    { "Toad Town Tunnels (tik_19)", "Shine Block", 0, GameFlag(437), 0 },
    { "Toad Town Tunnels (tik_27)", "Shine Block", 0, GameFlag(4549), 0 },
    { "Toad Town Tunnels (tik_28)", "Shine Block", 0, GameFlag(4550), 0 },
    { "Koopa Bros Fortress (trd_11)", "Shine Block", 0, GameFlag(4763), 0 },
    { "Great Tree (tyd_02)", "Shine Block", 0, GameFlag(4863), 0 },
    { "Glitz Pit (tyd_03)", "Shine Block", 0, GameFlag(5170), 0 },
    { "Mt. Lavalava (tyd_05)", "Shine Block 1", 0, GameFlag(5438), 0 },
    { "Mt. Lavalava (tyd_05)", "Shine Block 2", 0, GameFlag(5439), 0 },
    { "Factory (tyd_07)", "Shine Block 1", 0, GameFlag(5570), 0 },
    { "Factory (tyd_07)", "Shine Block 2", 0, GameFlag(5571), 0 },
};

static s32 TTYD64_se_GetShines(void) {
    return TTYD64_ShineSprites;
}

static void TTYD64_se_SetShines(s32 value) {
    TTYD64_ShineSprites = value;
}

static void TTYD64_se_AddRecipes(void) {
    ModSaveEditorEntry recipe = { 0 };
    s32 i;

    Mod_SaveEditorClear("TTYD64", MOD_SAVE_EDITOR_RECIPES);
    for (i = 0; TTYD64_mac_02_RecipesDiscovedIDs[i] != 0 && TTYD64_mac_02_RecipesDiscovedFlags[i] != 0; i++) {
        recipe.id = TTYD64_mac_02_RecipesDiscovedIDs[i];
        recipe.flag = TTYD64_mac_02_RecipesDiscovedFlags[i];
        Mod_SaveEditorAdd("TTYD64", MOD_SAVE_EDITOR_RECIPES, &recipe, 1);
    }
}

void TTYD64_InstallSaveEditor(void) {
    static const ModSaveEditorCounter shineCounter = {
        "Shine Sprites",
        TTYD64_se_GetShines,
        TTYD64_se_SetShines,
        ARRAY_COUNT(sShineSprites),
    };
    const ModSaveEditorTracker shineTracker = {
        "Shine Sprites", "The Shine Blocks around the world. Ticking one also moves the Shine Sprite counter.",
        sShineSprites,   ARRAY_COUNT(sShineSprites),
        &shineCounter,   1,
    };

    Mod_SaveEditorSetLimit("TTYD64", MOD_SAVE_EDITOR_LIMIT_STAR_PIECES, TTYD64_TOTAL_STAR_PIECES);
    Mod_SaveEditorAdd("TTYD64", MOD_SAVE_EDITOR_STAR_PIECES, sStarPieces, ARRAY_COUNT(sStarPieces));
    TTYD64_se_AddRecipes();
    Mod_SaveEditorAddTracker("TTYD64", &shineTracker);
}
