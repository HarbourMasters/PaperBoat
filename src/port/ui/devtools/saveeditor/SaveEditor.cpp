#include "SaveEditor.h"
#include "port/Engine.h"
#include "port/features/Features.h"
#include "port/ui/UIWidgets.hpp"
#include "port/ActorTypeNames.h"
#include "port/modding/SaveEditorLists.h"
#include "port/modding/Items.h"
#include "port/romhack/Romhack.h"
#include <string>
#include <spdlog/fmt/fmt.h>
#include <imgui.h>
#include <ship/Context.h>
#include <ship/window/Window.h>
#include <libultraship/bridge/windowbridge.h>
#include "fast/interpreter.h"
#include "fast/Fast3dWindow.h"
#include "fast/Fast3dGui.h"
#include "fast/resource/type/Texture.h"
#include <unordered_set>

#include "common_structs.h"
#include "assets/ui.h"

extern "C" {
extern s32 get_global_byte(s32 index);
extern s8 set_global_byte(s32 index, s32 value);

#include "dx/versioning.h"

extern s32 set_global_flag(s32 index);
extern s32 clear_global_flag(s32 index);
extern s32 get_global_flag(s32 index);
extern void enforce_hpfp_limits(void);
extern s32 get_consumables_capacity(void);

extern s8* load_message_to_buffer(s32 msgID);

extern const s32 CookableItemIDs[];
extern const s32 CookableDiscoveredFlags[];

extern SaveData gCurrentSaveFile;
extern s32 gPausePartnersPartnerIDs[8];
extern intptr_t gItemIconRasterOffsets[];
extern intptr_t gItemIconPaletteOffsets[];
}

#pragma push_macro("End")
#undef End

#define MAX_KEY_ITEM_SIZE    ARRAY_COUNT(gPlayerData.keyItems)
#define NUM_COOKABLE_RECIPES 52

#define LIMIT(name) Mod::SaveEditorLimit(MOD_SAVE_EDITOR_LIMIT_##name)

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

typedef enum {
    LETTER_NOT_FOUND,
    LETTER_WITH_PARAKARRY,
    LETTER_IN_ITEMS,
    LETTER_DELIVERED,
} LetterState;

typedef Mod::SaveEditorEntry SaveEditorEntry;

// Standalone letters Parakarry delivers, keyed by the flag set when the letter is picked up.
// Delivering one only removes the key item, so "delivered" is picked up but no longer held.
const std::vector<SaveEditorEntry> kVanillaLetters = {
    { "Letter to Merlon", "", ITEM_LETTER_TO_MERLON, GF_IWA01_Item_Letter01, 1 },
    { "Letter to Goompa", "", ITEM_LETTER_TO_GOOMPA, GF_SBK30_Tree2_Letter02, 0 },
    { "Letter to Mort T.", "", ITEM_LETTER_TO_MORT_T, GF_SBK36_Tree9_Letter03, 0 },
    { "Letter to Russ T.", "", ITEM_LETTER_TO_RUSS_T, GF_JAN04_Tree2_Letter04, 0 },
    { "Letter to Mayor Penguin", "", ITEM_LETTER_TO_MAYOR_PENGUIN, GF_SAM04_Item_Letter05, 0 },
    { "Letter to Merlow", "", ITEM_LETTER_TO_MERLOW, GF_SAM05_Item_Letter06, 0 },
    { "Letter to Fice T.", "", ITEM_LETTER_TO_FICE_T, GF_ARN02_Item_LetterFiceT, 0 },
    { "Letter to Nomadimouse", "", ITEM_LETTER_TO_NOMADIMOUSE, GF_DRO02_Item_Letter08, 0 },
    { "Letter to Minh T.", "", ITEM_LETTER_TO_MINH_T, GF_FLO17_Item_Letter09, 0 },
    { "Letter to Igor", "", ITEM_LETTER_TO_IGOR, GF_JAN01_Item_Letter11, 0 },
    { "Letter to Kolorado", "", ITEM_LETTER_TO_KOLORADO, GF_IWA03_Item_LettertoKolorado, 1 },
};

// The chain letter quest in delivery order, named after the recipient. Each letter is the reward
// for delivering the one before it, so only the first has a pickup flag and the rest of the chain
// is derived from which chain letter is currently held.
const std::vector<SaveEditorEntry> kVanillaChainLetters = {
    { "Goompapa (1st)", "", ITEM_LETTER_CHAIN_GOOMPAPA_1, GF_IWA04_Item_Letter10, 1 },
    { "Muss T.", "", ITEM_LETTER_CHAIN_MUSS_T, 0, 0 },
    { "Koover (1st)", "", ITEM_LETTER_CHAIN_KOOVER_1, 0, 0 },
    { "Fishmael", "", ITEM_LETTER_CHAIN_FISHMAEL, 0, 0 },
    { "Koover (2nd)", "", ITEM_LETTER_CHAIN_KOOVER_2, 0, 0 },
    { "Mr. E", "", ITEM_LETTER_CHAIN_MR_E, 0, 0 },
    { "Miss T.", "", ITEM_LETTER_CHAIN_MISS_T, 0, 0 },
    { "Little Mouser", "", ITEM_LETTER_CHAIN_LITTLE_MOUSER, 0, 0 },
    { "Franky", "", ITEM_LETTER_CHAIN_FRANKY, 0, 0 },
    { "Dane T. (1st)", "", ITEM_LETTER_CHAIN_DANE_T_1, 0, 0 },
    { "Yoshi Kid", "", ITEM_LETTER_CHAIN_YOSHI_KID, 0, 0 },
    { "Dane T. (2nd)", "", ITEM_LETTER_CHAIN_DANE_T_2, 0, 0 },
    { "Frost T.", "", ITEM_LETTER_CHAIN_FROST_T, 0, 0 },
    { "Goompapa (2nd)", "", ITEM_LETTER_CHAIN_GOOMPAPA_2, 0, 0 },
};

// The 63 star pieces lying around the overworld - the same set Merluvlee can predict.
const std::vector<SaveEditorEntry> kVanillaStarPieces = {
    { "Goomba Village (kmr_05)", "Overworld", 0, GF_KMR05_Item_StarPiece, 0 },
    { "Goomba Village (kmr_11)", "Tree", 0, GF_KMR11_Tree1_StarPiece, 0 },
    { "Goomba Village (kmr_00)", "Hidden Panel", 0, GF_KMR00_HiddenPanel, 0 },
    { "Goomba Village (kmr_03)", "Hidden Panel", 0, GF_KMR03_HiddenPanel, 0 },
    { "Goomba Village (kmr_11)", "Hidden Panel", 0, GF_KMR11_HiddenPanel, 0 },
    { "Toad Town (mac_00)", "Overworld", 0, GF_MAC00_Item_StarPiece, 0 },
    { "Toad Town (mac_00)", "Hidden Panel", 0, GF_MAC00_HiddenPanel, 0 },
    { "Toad Town (mac_02)", "Hidden Panel", 0, GF_MAC02_HiddenPanel, 0 },
    { "Toad Town (mac_03)", "Hidden Panel", 0, GF_MAC03_HiddenPanel, 0 },
    { "Toad Town (mac_05)", "Hidden Panel", 0, GF_MAC05_HiddenPanel, 0 },
    { "Toad Town (mac_01)", "Tree", 0, GF_MAC01_Tree1_StarPiece, 0 },
    { "Shooting Star Summit (hos_00)", "Hidden Panel", 0, GF_HOS00_HiddenPanel, 0 },
    { "Shooting Star Summit (hos_01)", "Hidden Panel", 0, GF_HOS01_HiddenPanel, 0 },
    { "Shooting Star Summit (hos_06)", "Hidden Panel", 0, GF_HOS06_HiddenPanel, 0 },
    { "Shooting Star Summit (hos_01)", "Overworld", 0, GF_HOS01_Item_StarPiece, 0 },
    { "Toad Town Tunnels (tik_07)", "Overworld", 0, GF_TIK07_Item_StarPiece, 0 },
    { "Koopa Village (nok_12)", "Overworld", 0, GF_NOK12_Item_StarPiece, 0 },
    { "Koopa Village (nok_01)", "Hidden Panel", 0, GF_NOK01_HiddenPanel, 0 },
    { "Koopa Village (nok_13)", "Hidden Panel", 0, GF_NOK13_HiddenPanel, 0 },
    { "Koopa Village (nok_14)", "Hidden Panel", 0, GF_NOK14_HiddenPanel, 0 },
    { "Koopa Village (nok_02)", "Overworld", 0, GF_NOK02_Item_StarPiece, 0 },
    { "Koopa Village (nok_15)", "Tree", 0, GF_NOK15_Tree1_StarPiece, 0 },
    { "Mt. Rugged (iwa_02)", "Overworld", 0, GF_IWA02_Item_StarPiece, 0 },
    { "Mt. Rugged (iwa_01)", "Hidden Panel", 0, GF_IWA01_HiddenPanel, 0 },
    { "Mt. Rugged (iwa_03)", "Overworld", 0, GF_IWA03_Item_StarPiece, 0 },
    { "Dry Dry Desert (sbk_33)", "Hidden Panel", 0, GF_SBK33_HiddenPanel, 0 },
    { "Dry Dry Outpost (dro_02)", "Hidden Panel", 0, GF_DRO02_HiddenPanel, 0 },
    { "Dry Dry Ruins (isk_06)", "Overworld", 0, GF_ISK06_Item_StarPiece, 0 },
    { "Boo's Mansion (obk_01)", "Hidden Panel", 0, GF_OBK01_HiddenPanel, 0 },
    { "Boo's Mansion (obk_02)", "Hidden Panel", 0, GF_OBK02_HiddenPanel, 0 },
    { "Boo's Mansion (obk_04)", "Hidden Panel", 0, GF_OBK04_HiddenPanel, 0 },
    { "Boo's Mansion (obk_08)", "Hidden Panel", 0, GF_OBK08_HiddenPanel, 0 },
    { "Boo's Mansion (obk_06)", "Crate", 0, GF_OBK06_Crate_StarPiece, 0 },
    { "Forever Forest (mim_12)", "Hidden Panel", 0, GF_MIM12_HiddenPanel, 0 },
    { "Gusty Gulch (arn_04)", "Overworld", 0, GF_ARN04_Item_StarPiece, 0 },
    { "Tubba Blubba's Castle (dgb_03)", "Overworld", 0, GF_DGB03_Item_StarPiece, 0 },
    { "Tubba Blubba's Castle (dgb_07)", "Overworld", 0, GF_DGB07_Item_StarPiece, 0 },
    { "Shy Guy's Toy Box (omo_04)", "Overworld", 0, GF_OMO04_Item_StarPieceA, 0 },
    { "Shy Guy's Toy Box (omo_03)", "Hidden Panel", 0, GF_OMO03_HiddenPanel, 0 },
    { "Shy Guy's Toy Box (omo_06)", "Hidden Panel", 0, GF_OMO06_HiddenPanel, 0 },
    { "Shy Guy's Toy Box (omo_08)", "Hidden Panel", 0, GF_OMO08_HiddenPanel, 0 },
    { "Shy Guy's Toy Box (omo_10)", "Hidden Panel", 0, GF_OMO10_HiddenPanel, 0 },
    { "Shy Guy's Toy Box (omo_04)", "Overworld", 0, GF_OMO04_Item_StarPieceB, 0 },
    { "Shy Guy's Toy Box (omo_09)", "Overworld", 0, GF_OMO09_Item_StarPiece, 0 },
    { "Jade Jungle (jan_02)", "Hidden Panel", 0, GF_JAN02_HiddenPanel, 0 },
    { "Jade Jungle (jan_15)", "Hidden Panel", 0, GF_JAN15_HiddenPanel, 0 },
    { "Jade Jungle (jan_04)", "Overworld", 0, GF_JAN04_Item_StarPiece, 0 },
    { "Jade Jungle (jan_01)", "Tree", 0, GF_JAN01_Tree7_StarPiece, 0 },
    { "Jade Jungle (jan_10)", "Overworld", 0, GF_JAN10_Item_StarPiece, 0 },
    { "Mt. Lavalava (kzn_09)", "Hidden Panel", 0, GF_KZN09_HiddenPanel, 0 },
    { "Mt. Lavalava (kzn_18)", "Hidden Panel", 0, GF_KZN18_HiddenPanel, 0 },
    { "Flower Fields (flo_16)", "Overworld", 0, GF_FLO16_Item_StarPiece, 0 },
    { "Flower Fields (flo_03)", "Hidden Panel", 0, GF_FLO03_HiddenPanel, 0 },
    { "Flower Fields (flo_24)", "Hidden Panel", 0, GF_FLO24_HiddenPanel, 0 },
    { "Flower Fields (flo_14)", "Overworld", 0, GF_FLO14_Item_StarPiece, 0 },
    { "Flower Fields (flo_25)", "Hidden Panel", 0, GF_FLO25_HiddenPanel, 0 },
    { "Flower Fields (flo_08)", "Overworld", 0, GF_FLO08_Item_StarPiece, 0 },
    { "Shiver City (sam_10)", "Overworld", 0, GF_SAM10_Item_StarPiece, 0 },
    { "Shiver City (sam_01)", "Hidden Panel", 0, GF_SAM01_HiddenPanel, 0 },
    { "Shiver City (sam_04)", "Hidden Panel", 0, GF_SAM04_HiddenPanel, 0 },
    { "Crystal Palace (pra_15)", "Overworld", 0, GF_PRA15_Item_StarPiece, 0 },
    { "Crystal Palace (pra_21)", "Hidden Panel", 0, GF_PRA21_HiddenPanel, 0 },
    { "Crystal Palace (pra_22)", "Hidden Panel", 0, GF_PRA22_HiddenPanel, 0 },
};

std::vector<SaveEditorEntry> letterList;
std::vector<SaveEditorEntry> chainLetterList;
std::vector<SaveEditorEntry> starPieceList;

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
    const int capacity = get_consumables_capacity();
    for (int i = 0; i < capacity; i++) {
        if (gPlayerData.invItems[i] == itemId) {
            return true;
        }
    }
    return false;
}

bool PlayerHasBadge(int16_t badgeId) {
    for (int b = 0; b < ARRAY_COUNT(gPlayerData.badges); b++) {
        if (gPlayerData.badges[b] == badgeId) {
            return true;
        }
    }
    return false;
}

void AddRemove_Badge(int badgeId, bool currentState) {
    if (currentState) {
        for (int b = 0; b < ARRAY_COUNT(gPlayerData.badges); b++) {
            if (gPlayerData.badges[b] == badgeId) {
                gPlayerData.badges[b] = 0;
                break;
            }
        }
    } else {
        for (int b = 0; b < ARRAY_COUNT(gPlayerData.badges); b++) {
            if (gPlayerData.badges[b] == 0) {
                gPlayerData.badges[b] = badgeId;
                break;
            }
        }
    }
}

void AddRemove_Item(int itemId, bool currentState) {
    const int capacity = get_consumables_capacity();
    if (currentState) {
        for (int i = 0; i < capacity; i++) {
            if (gPlayerData.invItems[i] == itemId) {
                gPlayerData.invItems[i] = 0;
                break;
            }
        }
    } else {
        for (int i = 0; i < capacity; i++) {
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

// Before Parakarry joins, the letters he lost may have been handed back to him rather than delivered.
bool ParakarryHoldsLostLetters() {
    return get_global_byte(EVT_INDEX_OF_GAME_BYTE(GB_StoryProgress)) < STORY_CH2_PARAKARRY_JOINED_PARTY;
}

LetterState GetLetterState(const SaveEditorEntry& letter) {
    if (PlayerHasKeyItem(letter.id)) {
        return LETTER_IN_ITEMS;
    }
    if (!get_global_flag(letter.flag)) {
        return LETTER_NOT_FOUND;
    }
    if (letter.option && ParakarryHoldsLostLetters()) {
        return LETTER_WITH_PARAKARRY;
    }
    return LETTER_DELIVERED;
}

void SetLetterState(const SaveEditorEntry& letter, LetterState state) {
    bool held = PlayerHasKeyItem(letter.id);

    if (state == LETTER_IN_ITEMS) {
        if (!held && CountUsedKeyItemSlots() >= MAX_KEY_ITEM_SIZE) {
            return;
        }
        set_global_flag(letter.flag);
        if (!held) {
            AddRemove_KeyItem(letter.id, false);
        }
        return;
    }

    if (held) {
        AddRemove_KeyItem(letter.id, true);
    }
    if (state == LETTER_NOT_FOUND) {
        clear_global_flag(letter.flag);
    } else {
        set_global_flag(letter.flag);
    }
}

// 0 = not started, N = holding chain letter N - 1, size + 1 = finished, -1 = first letter is with Parakarry.
int32_t GetChainLetterProgress() {
    for (int i = (int) chainLetterList.size() - 1; i >= 0; i--) {
        if (PlayerHasKeyItem(chainLetterList[i].id)) {
            return i + 1;
        }
    }
    if (chainLetterList.empty() || !get_global_flag(chainLetterList[0].flag)) {
        return 0;
    }
    if (ParakarryHoldsLostLetters()) {
        return -1;
    }
    return (int32_t) chainLetterList.size() + 1;
}

void SetChainLetterProgress(int32_t progress) {
    for (auto& letter : chainLetterList) {
        if (PlayerHasKeyItem(letter.id)) {
            AddRemove_KeyItem(letter.id, true);
        }
    }
    if (chainLetterList.empty()) {
        return;
    }
    if (progress <= 0) {
        clear_global_flag(chainLetterList[0].flag);
        return;
    }
    set_global_flag(chainLetterList[0].flag);
    if (progress <= (int32_t) chainLetterList.size()) {
        AddRemove_KeyItem(chainLetterList[progress - 1].id, false);
    }
}

LetterState GetChainLetterState(int32_t index) {
    int32_t progress = GetChainLetterProgress();

    if (progress < 0) {
        return index == 0 ? LETTER_WITH_PARAKARRY : LETTER_NOT_FOUND;
    }
    if (progress <= index) {
        return LETTER_NOT_FOUND;
    }
    if (progress == index + 1) {
        return LETTER_IN_ITEMS;
    }
    return LETTER_DELIVERED;
}

void SetChainLetterState(int32_t index, LetterState state) {
    switch (state) {
        case LETTER_NOT_FOUND:
            SetChainLetterProgress(index);
            break;
        case LETTER_DELIVERED:
            SetChainLetterProgress(index + 2);
            break;
        default:
            SetChainLetterProgress(index + 1);
            break;
    }
}

LetterState NextLetterState(LetterState state) {
    switch (state) {
        case LETTER_NOT_FOUND:
        case LETTER_WITH_PARAKARRY:
            return LETTER_IN_ITEMS;
        case LETTER_IN_ITEMS:
            return LETTER_DELIVERED;
        default:
            return LETTER_NOT_FOUND;
    }
}

const char* LetterStateName(LetterState state) {
    switch (state) {
        case LETTER_WITH_PARAKARRY:
            return "With Parakarry";
        case LETTER_IN_ITEMS:
            return "In Items";
        case LETTER_DELIVERED:
            return "Delivered";
        default:
            return "Not Found";
    }
}

ImVec4 LetterStateColor(LetterState state) {
    switch (state) {
        case LETTER_WITH_PARAKARRY:
            return ImVec4(0.45f, 0.7f, 1.0f, 1.0f);
        case LETTER_IN_ITEMS:
            return ImVec4(0.95f, 0.85f, 0.3f, 1.0f);
        case LETTER_DELIVERED:
            return ImVec4(0.35f, 0.85f, 0.35f, 1.0f);
        default:
            return ImVec4(0.55f, 0.55f, 0.55f, 1.0f);
    }
}

int32_t GetStarPieces() {
    return gPlayerData.starPieces;
}

void SetStarPieces(int32_t value) {
    gPlayerData.starPieces = value;
}

int32_t GetStarPiecesCollected() {
    return gPlayerData.starPiecesCollected;
}

void SetStarPiecesCollected(int32_t value) {
    gPlayerData.starPiecesCollected = value;
}

std::vector<Mod::SaveEditorCounter> StarPieceCounters() {
    return {
        { "Current Pieces", GetStarPieces, SetStarPieces, MAX_STAR_PIECES },
        { "Collected Pieces", GetStarPiecesCollected, SetStarPiecesCollected, LIMIT(STAR_PIECES) },
    };
}

// Mirrors what picking a collectible up does: sets the pickup flag and moves every counter by one.
void SetCollected(const SaveEditorEntry& entry, const std::vector<Mod::SaveEditorCounter>& counters, bool collected) {
    bool wasCollected = get_global_flag(entry.flag) != 0;

    if (collected == wasCollected) {
        return;
    }

    if (collected) {
        set_global_flag(entry.flag);
    } else {
        clear_global_flag(entry.flag);
    }
    for (const Mod::SaveEditorCounter& counter : counters) {
        const int32_t value = counter.get();
        if (collected && value < counter.max) {
            counter.set(value + 1);
        } else if (!collected && value > 0) {
            counter.set(value - 1);
        }
    }
}

// Tattle state lives in the saved game bytes; gBattleStatus.tattleFlags is a runtime mirror
// that battles OR on top, so read both and write both.
bool TattleInRange(int32_t actorType) {
    return actorType >= 0 && actorType < (int32_t) ARRAY_COUNT(gBattleStatus.tattleFlags) * 8;
}

bool GetTattleFlag(int32_t actorType) {
    if (!TattleInRange(actorType)) {
        return false;
    }
    int32_t flags = get_global_byte(EVT_INDEX_OF_GAME_BYTE(GB_Tattles_00) + actorType / 8);

    flags |= gBattleStatus.tattleFlags[actorType / 8];
    return (flags >> (actorType % 8)) & 1;
}

void SetTattleFlag(int32_t actorType, bool known) {
    if (!TattleInRange(actorType)) {
        return;
    }
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

typedef enum {
    ITEM_BUTTON_ADD_ITEM,
    ITEM_BUTTON_TOGGLE_BADGE,
    ITEM_BUTTON_REMOVE_ITEM,
} ItemButtonAction;

const char* ItemRaster(int32_t itemID) {
    if (itemID < 0 || itemID >= ITEM_TABLE_CAPACITY) {
        return nullptr;
    }
    return reinterpret_cast<const char*>(gItemIconRasterOffsets[itemID]);
}

typedef struct {
    const char* raster;
    const char* palette;
    s16 typeFlags;
    s32 nameMsg;
} VanillaItem;

std::vector<VanillaItem> SnapshotVanillaItems() {
    std::vector<VanillaItem> items;

    for (int32_t i = 0; i < NUM_ITEMS; i++) {
        items.push_back(
            { reinterpret_cast<const char*>(gItemIconRasterOffsets[i]),
              reinterpret_cast<const char*>(gItemIconPaletteOffsets[i]), gItemTable[i].typeFlags,
              gItemTable[i].nameMsg }
        );
    }
    return items;
}

// Taken at static init, before a romhack rewrites the item tables, so replaced slots can be told apart.
const std::vector<VanillaItem> kVanillaItems = SnapshotVanillaItems();

bool IsPlaceholderIcon(const char* raster) {
    const char* placeholder = kVanillaItems.empty() ? nullptr : kVanillaItems[0].raster;
    return raster == nullptr || (placeholder != nullptr && strcmp(raster, placeholder) == 0);
}

// Vanilla icons sit in badge/food/battle folders, which is how the tabs have always been split.
// Icons outside those folders (a romhack's own) fall back to the item's type flags.
int32_t ListForIcon(const char* raster, s16 typeFlags) {
    if (IsPlaceholderIcon(raster)) {
        return -1;
    }
    std::string_view path = raster;
    if (path.find("/badge/") != std::string_view::npos) {
        return MOD_SAVE_EDITOR_BADGES;
    }
    if (path.find("/food/") != std::string_view::npos) {
        return MOD_SAVE_EDITOR_FOOD;
    }
    if (path.find("/battle/") != std::string_view::npos) {
        return MOD_SAVE_EDITOR_BATTLE_ITEMS;
    }
    if (typeFlags & ITEM_TYPE_FLAG_BADGE) {
        return MOD_SAVE_EDITOR_BADGES;
    }
    if (typeFlags & ITEM_TYPE_FLAG_FOOD_OR_DRINK) {
        return MOD_SAVE_EDITOR_FOOD;
    }
    if (typeFlags & ITEM_TYPE_FLAG_BATTLE_USABLE) {
        return MOD_SAVE_EDITOR_BATTLE_ITEMS;
    }
    return -1;
}

int32_t ItemListFor(int32_t itemID) {
    if (itemID <= 0 || itemID >= gItemCount) {
        return -1;
    }
    return ListForIcon(ItemRaster(itemID), gItemTable[itemID].typeFlags);
}

bool IsReplacedSlot(int32_t itemID) {
    const char* current = ItemRaster(itemID);
    const char* vanilla = kVanillaItems[itemID].raster;

    return current != nullptr && (vanilla == nullptr || strcmp(current, vanilla) != 0);
}

std::string ItemOwnerFor(int32_t itemID) {
    std::string owner = Mod::ItemOwner(itemID);
    if (owner.empty() && Romhack_GetId() != nullptr) {
        owner = Romhack_GetId();
    }
    return owner.empty() ? "Mods" : owner;
}

typedef struct {
    std::vector<SaveEditorEntry> entries;
    std::vector<SaveEditorEntry> disabled;
} ItemSections;

// A vanilla slot whose icon changed holds a romhack's item now: that item counts as added by the romhack,
// and the vanilla item it took the place of as disabled.
ItemSections BuildItemSections(int32_t list) {
    std::vector<SaveEditorEntry> defaults;
    ItemSections sections;

    for (int32_t i = 1; i < std::max<int32_t>(gItemCount, NUM_ITEMS); i++) {
        const bool vanillaSlot = i < NUM_ITEMS;
        const bool replaced = vanillaSlot && IsReplacedSlot(i);

        if (ItemListFor(i) == list) {
            defaults.push_back({ "", "", i, 0, 0, vanillaSlot && !replaced ? "" : ItemOwnerFor(i) });
        }
        if (replaced && ListForIcon(kVanillaItems[i].raster, kVanillaItems[i].typeFlags) == list) {
            sections.disabled.push_back({ "", "", i, 0, 1, ItemOwnerFor(i) });
        }
    }
    sections.entries = Mod::SaveEditorList(list, defaults);
    for (SaveEditorEntry& removed : Mod::SaveEditorRemoved(list, defaults)) {
        sections.disabled.push_back(removed);
    }
    return sections;
}

std::vector<std::pair<std::string, std::vector<SaveEditorEntry>>>
GroupByOwner(const std::vector<SaveEditorEntry>& entries) {
    std::vector<std::pair<std::string, std::vector<SaveEditorEntry>>> groups = { { "", {} } };

    for (const SaveEditorEntry& entry : entries) {
        auto group = std::find_if(groups.begin(), groups.end(), [&](const auto& g) { return g.first == entry.owner; });
        if (group == groups.end()) {
            groups.push_back({ entry.owner, {} });
            group = std::prev(groups.end());
        }
        group->second.push_back(entry);
    }
    return groups;
}

const char* kAddedBy = "Collectables added by";

void SaveEditor_DrawOwnerHeader(const std::string& owner, const std::string& what) {
    const std::string name = Mod::SaveEditorOwnerName(owner);
    ImGui::SeparatorText(name.c_str());
    ImGui::TextDisabled("%s %s", what.c_str(), name.c_str());
}

// The item names are plain text in the US charset: 0x00-0x5F are ASCII shifted down by 0x20.
std::string MessageText(int32_t msgID) {
    const u8* msg = reinterpret_cast<const u8*>(load_message_to_buffer(msgID));
    std::string text;

    if (msg == nullptr) {
        return text;
    }
    for (int i = 0; i < 0x100; i++) {
        const u8 c = msg[i];
        if (c == MSG_CHAR_READ_END || c == 0xFF) {
            break;
        }
        if (c == MSG_CHAR_READ_SPACE || c == MSG_CHAR_READ_ENDL) {
            if (!text.empty() && text.back() != ' ') {
                text += ' ';
            }
        } else if (c < 0x60) {
            text += (char) (c + 0x20);
        }
    }
    while (!text.empty() && text.back() == ' ') {
        text.pop_back();
    }
    return text;
}

ImTextureID IconTexture(const std::shared_ptr<Fast::Fast3dGui>& gui, const char* raster, const char* palette) {
    static std::unordered_set<std::string> sTried;

    if (raster == nullptr) {
        return nullptr;
    }
    if (!gui->HasTextureByName(raster) && sTried.insert(raster).second) {
        auto texture = std::dynamic_pointer_cast<Fast::Texture>(
            Ship::Context::GetRawInstance()->GetResourceManager()->LoadResource(raster, true)
        );
        if (texture != nullptr) {
            gui->LoadGuiTexture(raster, *texture, palette != nullptr ? palette : "");
        }
    }
    return gui->GetTextureByName(raster);
}

ImTextureID ItemIconTexture(const std::shared_ptr<Fast::Fast3dGui>& gui, int32_t itemID) {
    if (itemID < 0 || itemID >= ITEM_TABLE_CAPACITY) {
        return nullptr;
    }
    return IconTexture(gui, ItemRaster(itemID), reinterpret_cast<const char*>(gItemIconPaletteOffsets[itemID]));
}

std::string IconName(const char* raster) {
    if (raster != nullptr && strchr(raster, '/') != nullptr) {
        return GetNameFromPath(raster);
    }
    return "";
}

std::string ItemTooltip(const SaveEditorEntry& entry) {
    if (!entry.name.empty()) {
        return entry.name;
    }
    if (entry.id > 0 && entry.id < gItemCount) {
        std::string name = MessageText(gItemTable[entry.id].nameMsg);
        if (!name.empty()) {
            return name;
        }
    }
    std::string name = IconName(ItemRaster(entry.id));
    return name.empty() ? fmt::format("Item 0x{:03X}", entry.id) : name;
}

void SaveEditor_DrawImageButton(const SaveEditorEntry& entry, ItemButtonAction action) {
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetRawInstance()->GetWindow()->GetGui());
    const int32_t itemID = entry.id;
    const char* rasterPath = ItemRaster(itemID);
    if (rasterPath == nullptr) {
        return;
    }
    ImTextureID itemTexture = ItemIconTexture(gui, itemID);
    bool hasItem = true;

    if (action == ITEM_BUTTON_ADD_ITEM) {
        hasItem = PlayerHasItem(itemID);
    } else if (action == ITEM_BUTTON_TOGGLE_BADGE) {
        hasItem = PlayerHasBadge(itemID);
    }

    SaveEditor_PushImageButtonStyle();
    if (ImGui::ImageButton(
            rasterPath, itemTexture, itemImageSize, ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0),
            ImVec4(1, 1, 1, hasItem ? 1.0f : 0.5f)
        ))
    {
        switch (action) {
            case ITEM_BUTTON_ADD_ITEM:
                AddRemove_Item(itemID, false);
                break;
            case ITEM_BUTTON_TOGGLE_BADGE:
                AddRemove_Badge(itemID, hasItem);
                break;
            case ITEM_BUTTON_REMOVE_ITEM:
                AddRemove_Item(itemID, true);
                break;
        }
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("%s", ItemTooltip(entry).c_str());
    }
    SaveEditor_PopImageButtonStyle();
}

// "GroupFocus" -> "Group Focus", "HPPlus" -> "HP Plus".
std::string SpacedIconName(const char* raster) {
    const std::string name = IconName(raster);
    std::string spaced;

    for (size_t i = 0; i < name.size(); i++) {
        const bool upper = isupper((unsigned char) name[i]);
        const bool afterLower = i > 0 && (islower((unsigned char) name[i - 1]) || isdigit((unsigned char) name[i - 1]));
        const bool endsAcronym = i > 0 && i + 1 < name.size() && isupper((unsigned char) name[i - 1])
            && islower((unsigned char) name[i + 1]);
        if (upper && (afterLower || endsAcronym)) {
            spaced += ' ';
        }
        spaced += name[i];
    }
    return spaced;
}

// The vanilla name message, unless the romhack rewrote it for the item that now sits in the slot.
std::string VanillaItemName(int32_t itemID) {
    std::string name = MessageText(kVanillaItems[itemID].nameMsg);

    if (name.empty() || (itemID < gItemCount && name == MessageText(gItemTable[itemID].nameMsg))) {
        name = SpacedIconName(kVanillaItems[itemID].raster);
    }
    return name;
}

// A replaced slot (option set) shows the vanilla item it held, which can't be given any more;
// a hidden or cleared entry shows the item as it is now.
void SaveEditor_DrawDisabledItem(const SaveEditorEntry& entry) {
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetRawInstance()->GetWindow()->GetGui());
    const bool vanillaSlot = entry.option != 0 && entry.id > 0 && entry.id < NUM_ITEMS;
    const char* raster = vanillaSlot ? kVanillaItems[entry.id].raster : ItemRaster(entry.id);
    const char* palette = vanillaSlot ? kVanillaItems[entry.id].palette
                                      : reinterpret_cast<const char*>(gItemIconPaletteOffsets[entry.id]);

    ImGui::ImageWithBg(
        IconTexture(gui, raster, palette), itemImageSize, ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0),
        ImVec4(1, 1, 1, 0.35f)
    );
    if (ImGui::IsItemHovered()) {
        std::string name = vanillaSlot ? VanillaItemName(entry.id) : ItemTooltip(entry);
        ImGui::SetTooltip("%s\nDisabled by %s", name.c_str(), Mod::SaveEditorOwnerName(entry.owner).c_str());
    }
}

void SaveEditor_DrawItemGrid(
    const char* id, const std::vector<SaveEditorEntry>& entries, ItemButtonAction action, bool disabled
) {
    ImVec2 padding = ImGui::GetStyle().CellPadding;
    padding.y += 2.0f;
    const float cellWidth = itemImageSize.x + ImGui::GetStyle().CellPadding.x * 2.0f;
    const int32_t columns = std::max<int32_t>(1, (int32_t) (ImGui::GetContentRegionAvail().x / cellWidth));

    if (entries.empty()) {
        ImGui::TextDisabled("None");
        return;
    }
    if (ImGui::BeginTable(id, columns, ImGuiTableFlags_SizingStretchSame)) {
        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, padding);
        for (int c = 0; c < columns; c++) {
            ImGui::TableSetupColumn(std::to_string(c).c_str(), ImGuiTableColumnFlags_WidthFixed, itemImageSize.x);
        }
        for (int i = 0; i < (int) entries.size(); i++) {
            ImGui::PushID(i);
            ImGui::TableNextColumn();
            if (disabled) {
                SaveEditor_DrawDisabledItem(entries[i]);
            } else {
                SaveEditor_DrawImageButton(entries[i], action);
            }
            ImGui::PopID();
        }
        ImGui::PopStyleVar(1);
        ImGui::EndTable();
    }
}

void SaveEditor_DrawItemList(int32_t list, ItemButtonAction action, const char* kind) {
    const ItemSections sections = BuildItemSections(list);
    const auto groups = GroupByOwner(sections.entries);
    const bool modded = groups.size() > 1 || !sections.disabled.empty();

    if (ImGui::BeginChild("ItemChild")) {
        if (!modded) {
            SaveEditor_DrawItemGrid("ItemListTable", groups[0].second, action, false);
        } else if (ImGui::BeginTable("ItemSplit", 2, ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_BordersInnerV))
        {
            ImGui::TableSetupColumn("items", ImGuiTableColumnFlags_WidthStretch, 2.0f);
            ImGui::TableSetupColumn("disabled", ImGuiTableColumnFlags_WidthStretch, 1.0f);

            ImGui::TableNextColumn();
            for (int g = 0; g < (int) groups.size(); g++) {
                ImGui::PushID(g);
                if (!groups[g].first.empty()) {
                    SaveEditor_DrawOwnerHeader(groups[g].first, fmt::format("{} added by", kind));
                }
                SaveEditor_DrawItemGrid("ItemListTable", groups[g].second, action, false);
                ImGui::PopID();
            }

            ImGui::TableNextColumn();
            const auto disabledGroups = GroupByOwner(sections.disabled);
            bool anyDisabled = false;
            for (int g = 0; g < (int) disabledGroups.size(); g++) {
                if (disabledGroups[g].second.empty()) {
                    continue;
                }
                anyDisabled = true;
                ImGui::PushID(g);
                SaveEditor_DrawOwnerHeader(disabledGroups[g].first, fmt::format("{} disabled by", kind));
                SaveEditor_DrawItemGrid("DisabledTable", disabledGroups[g].second, action, true);
                ImGui::PopID();
            }
            if (!anyDisabled) {
                ImGui::SeparatorText("Disabled");
                ImGui::TextDisabled("No %s disabled", kind);
            }
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
                            .Max(LIMIT(LEVEL))
                    ))
                {
                    gPlayerData.level = playerLevel;
                };

                // Heart Points
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_stat_heart_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t curHealth = gPlayerData.curHP;
                int32_t maxHealth = gPlayerData.hardMaxHP;
                std::string maxHealthFormat = gPlayerData.curMaxHP != gPlayerData.hardMaxHP
                    ? fmt::format("Max HP: %i ({} with badges)", gPlayerData.curMaxHP)
                    : "Max HP: %i";
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
                            .Format(maxHealthFormat.c_str())
                            .Step(5)
                            .Min(5)
                            .Max(LIMIT(MAX_HP))
                    ))
                {
                    gPlayerData.hardMaxHP = maxHealth;
                    enforce_hpfp_limits();
                };

                // Flower Points
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_stat_flower_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t curFlower = gPlayerData.curFP;
                int32_t maxFlower = gPlayerData.hardMaxFP;
                std::string maxFlowerFormat = gPlayerData.curMaxFP != gPlayerData.hardMaxFP
                    ? fmt::format("Max FP: %i ({} with badges)", gPlayerData.curMaxFP)
                    : "Max FP: %i";
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
                            .Format(maxFlowerFormat.c_str())
                            .Step(5)
                            .Min(5)
                            .Max(LIMIT(MAX_FP))
                    ))
                {
                    gPlayerData.hardMaxFP = maxFlower;
                    enforce_hpfp_limits();
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
                            .Max(LIMIT(MAX_BP))
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
                            .Max(LIMIT(STAR_POWER))
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
                            .Max(LIMIT(STAR_POINTS))
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
                            .Max(LIMIT(COINS))
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
                            .Max(MAX_STAR_PIECES)
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
                            .Max(LIMIT(STAR_PIECES))
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
        const int capacity = get_consumables_capacity();
        for (int i = 0; i < capacity; i++) {

            ImGui::PushID(i);
            if (gPlayerData.invItems[i] == 0) {
                SaveEditor_PushImageButtonStyle();
                ImGui::ImageButton("Empty", gui->GetTextureByName(ui_battle_menu_nothing_png), itemImageSize);
                SaveEditor_PopImageButtonStyle();
            } else {
                SaveEditor_DrawImageButton({ "", "", gPlayerData.invItems[i], 0, 0 }, ITEM_BUTTON_REMOVE_ITEM);
            }
            ImGui::PopID();
            if (i != capacity - 1 && i % 10 != 9) {
                ImGui::SameLine();
            }
        }

        ImGui::SeparatorText("Available Items");
        if (ImGui::BeginTabBar("ItemTabBar")) {
            if (ImGui::BeginTabItem("Food")) {
                SaveEditor_DrawItemList(MOD_SAVE_EDITOR_FOOD, ITEM_BUTTON_ADD_ITEM, "Items");
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Battle")) {
                SaveEditor_DrawItemList(MOD_SAVE_EDITOR_BATTLE_ITEMS, ITEM_BUTTON_ADD_ITEM, "Items");
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

void SaveEditor_SetupLetterTable(ImVec2 padding, ImVec2 imageSize) {
    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, padding);
    ImGui::TableSetupColumn("icon1", ImGuiTableColumnFlags_WidthFixed, imageSize.x);
    ImGui::TableSetupColumn("name1", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableSetupColumn("icon2", ImGuiTableColumnFlags_WidthFixed, imageSize.x);
    ImGui::TableSetupColumn("name2", ImGuiTableColumnFlags_WidthStretch);
    SaveEditor_PushImageButtonStyle();
}

bool SaveEditor_DrawLetterCell(
    const std::shared_ptr<Fast::Fast3dGui>& gui, const SaveEditorEntry& letter, LetterState state, ImVec2 imageSize
) {
    ImVec4 stateColor = LetterStateColor(state);
    bool found = state != LETTER_NOT_FOUND;

    ImGuiStorage* storage = ImGui::GetStateStorage();
    ImGuiID cardID = ImGui::GetID("card");
    bool wasHovered = storage->GetBool(cardID);
    float highlightAlpha = (found ? 0.15f : 0.0f) + (wasHovered ? 0.12f : 0.0f);
    ImU32 highlight = ImGui::GetColorU32(ImVec4(stateColor.x, stateColor.y, stateColor.z, highlightAlpha));

    ImGui::TableNextColumn();
    if (highlightAlpha > 0.0f) {
        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, highlight);
    }
    bool clicked = ImGui::ImageButton(
        letter.name.c_str(), ItemIconTexture(gui, letter.id), imageSize, ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0),
        ImVec4(1, 1, 1, found ? 1.0f : 0.35f)
    );
    bool hovered = ImGui::IsItemHovered();

    ImGui::TableNextColumn();
    if (highlightAlpha > 0.0f) {
        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, highlight);
    }
    ImVec2 textCellPos = ImGui::GetCursorPos();
    float textCellWidth = std::max<float>(ImGui::GetContentRegionAvail().x, 1.0f);
    clicked |= ImGui::InvisibleButton("##card", ImVec2(textCellWidth, imageSize.y));
    hovered |= ImGui::IsItemHovered();

    float textHeight = ImGui::GetTextLineHeightWithSpacing() + ImGui::GetTextLineHeight();
    ImGui::SetCursorPos(
        ImVec2(textCellPos.x, textCellPos.y + std::max<float>(0.0f, (imageSize.y - textHeight) * 0.5f))
    );
    ImGui::Text("%s", letter.name.c_str());
    ImGui::TextColored(stateColor, "%s", LetterStateName(state));

    if (hovered) {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        ImGui::SetTooltip("Click to mark as %s", LetterStateName(NextLetterState(state)));
    }
    storage->SetBool(cardID, hovered);
    return clicked;
}

void SaveEditor_DrawLettersMenu() {
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetRawInstance()->GetWindow()->GetGui());
    ImVec2 padding = ImGui::GetStyle().CellPadding;
    ImVec2 statImageSize = ImVec2(36.0f, 36.0f);
    padding.y += 4.0f;

    letterList = Mod::SaveEditorList(MOD_SAVE_EDITOR_LETTERS, kVanillaLetters);
    chainLetterList = Mod::SaveEditorList(MOD_SAVE_EDITOR_CHAIN_LETTERS, kVanillaChainLetters);

    if (ImGui::BeginChild("LettersChild")) {
        int32_t inItems = 0;
        int32_t delivered = 0;
        for (auto& letter : letterList) {
            LetterState state = GetLetterState(letter);
            inItems += state == LETTER_IN_ITEMS;
            delivered += state == LETTER_DELIVERED;
        }
        for (int i = 0; i < (int) chainLetterList.size(); i++) {
            LetterState state = GetChainLetterState(i);
            inItems += state == LETTER_IN_ITEMS;
            delivered += state == LETTER_DELIVERED;
        }
        int32_t totalLetters = (int32_t) (letterList.size() + chainLetterList.size());

        ImGui::Text(
            "Delivered: %d / %d     In Items: %d     Key item slots used: %d / %d", delivered, totalLetters, inItems,
            CountUsedKeyItemSlots(), MAX_KEY_ITEM_SIZE
        );
        ImGui::TextWrapped("Click a letter to cycle it between Not Found, In Items and Delivered.");

        if (UIWidgets::Button("Collect All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
            for (auto& letter : letterList) {
                LetterState state = GetLetterState(letter);
                if (state == LETTER_NOT_FOUND || state == LETTER_WITH_PARAKARRY) {
                    SetLetterState(letter, LETTER_IN_ITEMS);
                }
            }
            if (GetChainLetterProgress() <= 0) {
                SetChainLetterProgress(1);
            }
        }
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(
                "Puts every letter that hasn't been delivered yet in key items.\n"
                "Letters share the 32 key item slots, so this stops once they are full."
            );
        }
        ImGui::SameLine();
        if (UIWidgets::Button("Deliver All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
            for (auto& letter : letterList) {
                SetLetterState(letter, LETTER_DELIVERED);
            }
            SetChainLetterProgress((int32_t) chainLetterList.size() + 1);
        }
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Marks every letter delivered. Delivery rewards are not granted.");
        }
        ImGui::SameLine();
        if (UIWidgets::Button("Clear All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
            for (auto& letter : letterList) {
                SetLetterState(letter, LETTER_NOT_FOUND);
            }
            SetChainLetterProgress(0);
        }

        ImGui::SeparatorText("Letters");
        const auto groups = GroupByOwner(letterList);
        for (int g = 0; g < (int) groups.size(); g++) {
            if (groups[g].second.empty()) {
                continue;
            }
            ImGui::PushID(g);
            if (!groups[g].first.empty()) {
                SaveEditor_DrawOwnerHeader(groups[g].first, kAddedBy);
            }
            if (ImGui::BeginTable("LettersTable", 4, ImGuiTableFlags_SizingStretchSame)) {
                SaveEditor_SetupLetterTable(padding, statImageSize);
                for (int i = 0; i < (int) groups[g].second.size(); i++) {
                    const SaveEditorEntry& letter = groups[g].second[i];
                    LetterState state = GetLetterState(letter);

                    ImGui::PushID(i);
                    if (SaveEditor_DrawLetterCell(gui, letter, state, statImageSize)) {
                        SetLetterState(letter, NextLetterState(state));
                    }
                    ImGui::PopID();
                }
                SaveEditor_PopImageButtonStyle();
                ImGui::PopStyleVar(1);
                ImGui::EndTable();
            }
            ImGui::PopID();
        }

        ImGui::SeparatorText("Chain Letters");
        ImGui::TextWrapped(
            "Delivering a chain letter hands over the next one, so marking a letter here "
            "also updates the rest of the chain."
        );
        if (ImGui::BeginTable("ChainLettersTable", 4, ImGuiTableFlags_SizingStretchSame)) {
            SaveEditor_SetupLetterTable(padding, statImageSize);
            for (int i = 0; i < (int) chainLetterList.size(); i++) {
                const SaveEditorEntry& letter = chainLetterList[i];
                LetterState state = GetChainLetterState(i);

                ImGui::PushID(i);
                if (SaveEditor_DrawLetterCell(gui, letter, state, statImageSize)) {
                    SetChainLetterState(i, NextLetterState(state));
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

std::vector<SaveEditorEntry> RecipeList() {
    std::vector<SaveEditorEntry> defaults;

    for (int i = 0; i < NUM_COOKABLE_RECIPES; i++) {
        defaults.push_back({ "", "", CookableItemIDs[i], CookableDiscoveredFlags[i], 0 });
    }
    return Mod::SaveEditorList(MOD_SAVE_EDITOR_RECIPES, defaults);
}

void SaveEditor_DrawRecipesMenu() {
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetRawInstance()->GetWindow()->GetGui());
    int32_t columns = 13;
    ImVec2 padding = ImGui::GetStyle().CellPadding;
    padding.y += 2.0f;

    if (ImGui::BeginChild("RecipesChild")) {
        const std::vector<SaveEditorEntry> recipes = RecipeList();
        int32_t discovered = 0;
        for (const SaveEditorEntry& recipe : recipes) {
            if (get_global_flag(recipe.flag)) {
                discovered++;
            }
        }

        ImGui::Text("Discovered: %d / %d", discovered, (int32_t) recipes.size());

        if (UIWidgets::Button("Discover All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
            for (const SaveEditorEntry& recipe : recipes) {
                set_global_flag(recipe.flag);
            }
        }
        ImGui::SameLine();
        if (UIWidgets::Button("Forget All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
            for (const SaveEditorEntry& recipe : recipes) {
                clear_global_flag(recipe.flag);
            }
        }

        ImGui::SeparatorText("Tayce T. Cookbook");
        const auto groups = GroupByOwner(recipes);
        for (int g = 0; g < (int) groups.size(); g++) {
            if (groups[g].second.empty()) {
                continue;
            }
            ImGui::PushID(g);
            if (!groups[g].first.empty()) {
                SaveEditor_DrawOwnerHeader(groups[g].first, kAddedBy);
            }
            if (ImGui::BeginTable("RecipesTable", columns, ImGuiTableFlags_SizingStretchSame)) {
                ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, padding);
                for (int c = 0; c < columns; c++) {
                    ImGui::TableSetupColumn(
                        std::to_string(c).c_str(), ImGuiTableColumnFlags_WidthFixed, itemImageSize.x
                    );
                }

                SaveEditor_PushImageButtonStyle();
                for (int i = 0; i < (int) groups[g].second.size(); i++) {
                    const SaveEditorEntry& recipe = groups[g].second[i];
                    const char* rasterPath = ItemRaster(recipe.id);
                    bool isDiscovered = get_global_flag(recipe.flag) != 0;

                    if (rasterPath == nullptr) {
                        continue;
                    }
                    ImGui::PushID(i);
                    ImGui::TableNextColumn();
                    if (ImGui::ImageButton(
                            rasterPath, ItemIconTexture(gui, recipe.id), itemImageSize, ImVec2(0, 0), ImVec2(1, 1),
                            ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, isDiscovered ? 1.0f : 0.5f)
                        ))
                    {
                        if (isDiscovered) {
                            clear_global_flag(recipe.flag);
                        } else {
                            set_global_flag(recipe.flag);
                        }
                    }
                    if (ImGui::IsItemHovered()) {
                        ImGui::SetTooltip("%s", ItemTooltip(recipe).c_str());
                    }
                    ImGui::PopID();
                }
                SaveEditor_PopImageButtonStyle();

                ImGui::PopStyleVar(1);
                ImGui::EndTable();
            }
            ImGui::PopID();
        }
        ImGui::EndChild();
    }
}

void SaveEditor_DrawCollectibles(
    const char* title,
    const char* description,
    const std::vector<SaveEditorEntry>& entries,
    const std::vector<Mod::SaveEditorCounter>& counters,
    ImVec2 padding,
    const std::string& owner = "",
    bool showCounters = false
) {
    int32_t foundCount = 0;
    for (const SaveEditorEntry& entry : entries) {
        if (get_global_flag(entry.flag)) {
            foundCount++;
        }
    }

    ImGui::PushID(title);
    ImGui::SeparatorText(title);
    if (!owner.empty()) {
        ImGui::TextDisabled("%s %s", kAddedBy, Mod::SaveEditorOwnerName(owner).c_str());
    }
    ImGui::Text("Found: %d / %d", foundCount, (int32_t) entries.size());
    if (description[0] != '\0') {
        ImGui::TextWrapped("%s", description);
    }
    if (showCounters) {
        for (int c = 0; c < (int) counters.size(); c++) {
            const Mod::SaveEditorCounter& counter = counters[c];
            int32_t value = counter.get();
            std::string format = fmt::format("{}: %i", counter.label);

            ImGui::PushID(c);
            if (UIWidgets::SliderInt(
                    "##counter", &value,
                    UIWidgets::IntSliderOptions()
                        .Color(WIDGET_COLOR)
                        .LabelPosition(UIWidgets::LabelPositions::None)
                        .Format(format.c_str())
                        .Min(0)
                        .Max(counter.max)
                ))
            {
                counter.set(value);
            }
            ImGui::PopID();
        }
    }

    if (UIWidgets::Button("Collect All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
        for (const SaveEditorEntry& entry : entries) {
            SetCollected(entry, counters, true);
        }
    }
    ImGui::SameLine();
    if (UIWidgets::Button("Clear All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
        for (const SaveEditorEntry& entry : entries) {
            SetCollected(entry, counters, false);
        }
    }

    const auto groups = GroupByOwner(entries);
    for (int g = 0; g < (int) groups.size(); g++) {
        if (groups[g].second.empty()) {
            continue;
        }
        ImGui::PushID(g);
        if (!groups[g].first.empty()) {
            SaveEditor_DrawOwnerHeader(groups[g].first, kAddedBy);
        }
        if (ImGui::BeginTable("CollectibleTable", 2, ImGuiTableFlags_SizingStretchSame)) {
            ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, padding);
            for (int i = 0; i < (int) groups[g].second.size(); i++) {
                const SaveEditorEntry& entry = groups[g].second[i];
                bool isCollected = get_global_flag(entry.flag) != 0;
                std::string label =
                    entry.detail.empty() ? entry.name : fmt::format("{} - {}", entry.name, entry.detail);

                ImGui::PushID(i);
                ImGui::TableNextColumn();
                if (UIWidgets::Checkbox(label.c_str(), &isCollected, UIWidgets::CheckboxOptions().Color(WIDGET_COLOR)))
                {
                    SetCollected(entry, counters, isCollected);
                }
                ImGui::PopID();
            }
            ImGui::PopStyleVar(1);
            ImGui::EndTable();
        }
        ImGui::PopID();
    }
    ImGui::PopID();
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
                        .Max(MAX_STAR_PIECES)
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
                        .Max(LIMIT(STAR_PIECES))
                ))
            {
                gPlayerData.starPiecesCollected = collectedPieces;
            };

            ImGui::EndTable();
        }

        starPieceList = Mod::SaveEditorList(MOD_SAVE_EDITOR_STAR_PIECES, kVanillaStarPieces);
        SaveEditor_DrawCollectibles(
            "Overworld Star Pieces",
            "These are the star pieces lying around the world - the ones Merluvlee can predict. ", starPieceList,
            StarPieceCounters(), padding
        );
        ImGui::EndChild();
    }
}

std::vector<SaveEditorEntry> TattleList() {
    std::vector<SaveEditorEntry> defaults;

    for (const ActorTypeName& tattle : gActorTypeNames) {
        defaults.push_back({ tattle.name, "", tattle.actorType, 0, tattle.isUnused ? 1 : 0 });
    }
    return Mod::SaveEditorList(MOD_SAVE_EDITOR_TATTLES, defaults);
}

void SaveEditor_DrawTattlesMenu() {
    static char tattleFilter[64] = "";
    static bool hideUnusedTattles = true;

    ImVec2 padding = ImGui::GetStyle().CellPadding;
    padding.y += 2.0f;

    if (ImGui::BeginChild("TattlesChild")) {
        const std::vector<SaveEditorEntry> tattles = TattleList();
        int32_t listed = 0;
        int32_t known = 0;
        for (auto& tattle : tattles) {
            if (hideUnusedTattles && tattle.option) {
                continue;
            }
            if (!ContainsIgnoreCase(tattle.name.c_str(), tattleFilter)) {
                continue;
            }
            listed++;
            if (GetTattleFlag(tattle.id)) {
                known++;
            }
        }

        ImGui::Text("Tattled: %d / %d listed", known, listed);

        ImGui::SetNextItemWidth(220.0f);
        ImGui::InputTextWithHint("##tattleFilter", "Filter by name...", tattleFilter, sizeof(tattleFilter));
        ImGui::SameLine();
        UIWidgets::Checkbox("Hide unused", &hideUnusedTattles, UIWidgets::CheckboxOptions().Color(WIDGET_COLOR));

        if (UIWidgets::Button("Enable All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
            for (auto& tattle : tattles) {
                if ((hideUnusedTattles && tattle.option) || !ContainsIgnoreCase(tattle.name.c_str(), tattleFilter)) {
                    continue;
                }
                SetTattleFlag(tattle.id, true);
            }
        }
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Applies to the entries currently listed below.");
        }
        ImGui::SameLine();
        if (UIWidgets::Button("Clear All", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
            for (auto& tattle : tattles) {
                if ((hideUnusedTattles && tattle.option) || !ContainsIgnoreCase(tattle.name.c_str(), tattleFilter)) {
                    continue;
                }
                SetTattleFlag(tattle.id, false);
            }
        }
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Applies to the entries currently listed below.");
        }

        ImGui::SeparatorText("Tattle Log");
        const auto groups = GroupByOwner(tattles);
        for (int g = 0; g < (int) groups.size(); g++) {
            if (groups[g].second.empty()) {
                continue;
            }
            ImGui::PushID(g);
            if (!groups[g].first.empty()) {
                SaveEditor_DrawOwnerHeader(groups[g].first, kAddedBy);
            }
            if (ImGui::BeginTable("TattleTable", 2, ImGuiTableFlags_SizingStretchSame)) {
                ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, padding);
                for (int i = 0; i < (int) groups[g].second.size(); i++) {
                    const SaveEditorEntry& tattle = groups[g].second[i];

                    if (hideUnusedTattles && tattle.option) {
                        continue;
                    }
                    if (!ContainsIgnoreCase(tattle.name.c_str(), tattleFilter)) {
                        continue;
                    }

                    bool isKnown = GetTattleFlag(tattle.id);
                    std::string label = fmt::format("{} (0x{:02X})", tattle.name, tattle.id);

                    ImGui::PushID(i);
                    ImGui::TableNextColumn();
                    if (UIWidgets::Checkbox(label.c_str(), &isKnown, UIWidgets::CheckboxOptions().Color(WIDGET_COLOR)))
                    {
                        SetTattleFlag(tattle.id, isKnown);
                    }
                    ImGui::PopID();
                }
                ImGui::PopStyleVar(1);
                ImGui::EndTable();
            }
            ImGui::PopID();
        }
        ImGui::EndChild();
    }
}

void SaveEditor_DrawOthersMenu() {
    ImVec2 padding = ImGui::GetStyle().CellPadding;
    padding.y += 4.0f;

    if (ImGui::BeginChild("OthersChild")) {
        const auto& trackers = Mod::SaveEditorTrackers();
        for (int t = 0; t < (int) trackers.size(); t++) {
            const Mod::SaveEditorTracker& tracker = trackers[t];

            ImGui::PushID(t);
            SaveEditor_DrawCollectibles(
                tracker.title.c_str(), tracker.description.c_str(), tracker.entries, tracker.counters, padding,
                tracker.owner, true
            );
            ImGui::PopID();
        }

        for (const Mod::SaveEditorSection& section : Mod::SaveEditorSections()) {
            ImGui::PushID(section.title.c_str());
            ImGui::SeparatorText(section.title.c_str());
            section.draw();
            ImGui::PopID();
        }
        ImGui::EndChild();
    }
}

void SaveEditor_DrawTabBar() {
    if (Features::DrawLockedNotice("devtools.save_editor")) {
        return;
    }
    UIWidgets::PushStyleTabs(WIDGET_COLOR);
    if (ImGui::BeginTabBar("SaveEditorTabBar")) {
        if (ImGui::BeginTabItem("Player")) {
            SaveEditor_DrawPlayerMenu();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Badges")) {
            SaveEditor_DrawItemList(MOD_SAVE_EDITOR_BADGES, ITEM_BUTTON_TOGGLE_BADGE, "Badges");
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
        if (!Mod::SaveEditorTrackers().empty() || !Mod::SaveEditorSections().empty()) {
            if (ImGui::BeginTabItem("Others")) {
                SaveEditor_DrawOthersMenu();
                ImGui::EndTabItem();
            }
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
