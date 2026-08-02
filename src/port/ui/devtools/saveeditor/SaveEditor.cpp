#include "SaveEditor.h"
#include "port/UI/UIWidgets.hpp"
#include <string>
#include <spdlog/fmt/fmt.h>
#include <imgui.h>
#include <ship/Context.h>
#include <ship/window/Window.h>
#include "fast/interpreter.h"
#include "fast/Fast3dWindow.h"
#include "fast/Fast3dGui.h"

#include "common_structs.h"
#include "assets/ui.h"

extern "C" {
extern s32 get_global_byte(s32 index);
extern s8 set_global_byte(s32 index, s32 value);

#include "dx/versioning.h"


extern SaveData gCurrentSaveFile;
extern s32 gPausePartnersPartnerIDs[8];
extern intptr_t gItemIconRasterOffsets[349];
extern intptr_t gItemIconPaletteOffsets[349];
}

#pragma push_macro("End")
#undef End

#define MAX_ICON_RASTER_SIZE 349
#define MAX_INVENTORY_SIZE 10

#define CVAR_NAME_POPOUT_SAVE_EDITOR "gOpenWindows.SaveEditor"

#define CVAR_SHOW_POPOUT_SAVE_EDITOR CVarGetInteger(CVAR_NAME_POPOUT_SAVE_EDITOR, 0)

ImGuiWindowFlags saveEditorWindowFlags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoTitleBar;
ImVec4 saveEditorBG = ImVec4{ 0, 0, 0, 0.5f };
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
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetInstance()->GetWindow()->GetGui());
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
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetInstance()->GetWindow()->GetGui());

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

void SetAllTattleFlags() {
    s32 numBytes = sizeof(gBattleStatus.tattleFlags);
    for (s32 i = 0; i < numBytes; i++) {
        set_global_byte(EVT_INDEX_OF_GAME_BYTE(GB_Tattles_00) + i, 0xFF);
        gBattleStatus.tattleFlags[i] = 0xFF;
    }
}

void SaveEditor_DrawImageButton(int32_t iconIndex, const char* itemType) {
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetInstance()->GetWindow()->GetGui());
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
    if (ImGui::ImageButton(rasterPath, itemTexture, itemImageSize, ImVec2(0, 0), ImVec2(1, 1),
        ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, hasItem ? 1.0f : 0.5f))) {
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
        ImGui::SetTooltip(GetNameFromPath(rasterPath));
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
                if (reinterpret_cast<const char*>(gItemIconRasterOffsets[i]) != nullptr && std::string_view(reinterpret_cast<const char*>(gItemIconRasterOffsets[i])).find(itemType) == std::string_view::npos) {
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

void SaveEditor_DrawGeneralMenu() {
    if (UIWidgets::Button("Enable All Tattle Flags", UIWidgets::ButtonOptions().Color(WIDGET_COLOR))) {
        SetAllTattleFlags();
    }
}

void SaveEditor_DrawPlayerMenu() {
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetInstance()->GetWindow()->GetGui());
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
                if (UIWidgets::SliderInt("##pLevel", &playerLevel, UIWidgets::IntSliderOptions()
                    .Color(WIDGET_COLOR)
                    .LabelPosition(UIWidgets::LabelPositions::None)
                    .Format("Level: %i")
                    .Min(1)
                    .Max(30))) {
                    gPlayerData.level = playerLevel;
                };

                // Heart Points
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_stat_heart_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t curHealth = gPlayerData.curHP;
                int32_t maxHealth = gPlayerData.curMaxHP;
                if (UIWidgets::SliderInt("##pCurHP", &curHealth, UIWidgets::IntSliderOptions()
                    .Color(WIDGET_COLOR)
                    .LabelPosition(UIWidgets::LabelPositions::None)
                    .Format("Current HP: %i")
                    .Min(1)
                    .Max(gPlayerData.curMaxHP))) {
                    gPlayerData.curHP = curHealth;
                };
                if (UIWidgets::SliderInt("##pMaxHP", &maxHealth, UIWidgets::IntSliderOptions()
                    .Color(WIDGET_COLOR)
                    .LabelPosition(UIWidgets::LabelPositions::None)
                    .Format("Max HP: %i")
                    .Step(5)
                    .Min(5)
                    .Max(50))) {
                    gPlayerData.curMaxHP = maxHealth;
                };

                // Flower Points
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_stat_flower_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t curFlower = gPlayerData.curFP;
                int32_t maxFlower = gPlayerData.curMaxFP;
                if (UIWidgets::SliderInt("##pCurFP", &curFlower, UIWidgets::IntSliderOptions()
                    .Color(WIDGET_COLOR)
                    .LabelPosition(UIWidgets::LabelPositions::None)
                    .Format("Current FP: %i")
                    .Min(1)
                    .Max(gPlayerData.curMaxFP))) {
                    gPlayerData.curFP = curFlower;
                };
                if (UIWidgets::SliderInt("##pMaxFP", &maxFlower, UIWidgets::IntSliderOptions()
                    .Color(WIDGET_COLOR)
                    .LabelPosition(UIWidgets::LabelPositions::None)
                    .Format("Max FP: %i")
                    .Step(5)
                    .Min(5)
                    .Max(50))) {
                    gPlayerData.curMaxFP = maxFlower;
                };

                // Badge Points
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_pause_stat_bp_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t maxBadgePoints = gPlayerData.maxBP;
                if (UIWidgets::SliderInt("##pCurBP", &maxBadgePoints, UIWidgets::IntSliderOptions()
                    .Color(WIDGET_COLOR)
                    .LabelPosition(UIWidgets::LabelPositions::None)
                    .Format("Current BP: %i")
                    .Min(3)
                    .Max(30))) {
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
                    }
                    else {
                        gPlayerData.bootsLevel++;
                    }
                }
                ImGui::TableNextColumn();
                TableCellCenteredText(equipmentData.name, statImageSize);

                // Hammer
                ImGui::TableNextColumn();
                equipmentData = GetEquipmentTextureId(ICON_gear_hammer_1_raster);
                if (ImGui::ImageButton("##pHammer", equipmentData.textureId, statImageSize, ImVec2(0, 0), ImVec2(1, 1),
                    ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, gPlayerData.hammerLevel == -1 ? 0.5f : 1.0f))) {
                    if (gPlayerData.hammerLevel >= 2) {
                        gPlayerData.hammerLevel = -1;
                    }
                    else {
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
                if (UIWidgets::SliderInt("##pCurEnergy", &curEnergy, UIWidgets::IntSliderOptions()
                    .Color(WIDGET_COLOR)
                    .LabelPosition(UIWidgets::LabelPositions::None)
                    .Format("Current Energy: %i")
                    .Min(0)
                    .Max(maxEnergy))) {
                    gPlayerData.starPower = (curEnergy * 256);
                };
                if (UIWidgets::SliderInt("##pMaxEnergy", &maxEnergy, UIWidgets::IntSliderOptions()
                    .Color(WIDGET_COLOR)
                    .LabelPosition(UIWidgets::LabelPositions::None)
                    .Format("Max Energy: %i")
                    .Min(0)
                    .Max(7))) {
                    gPlayerData.maxStarPower = maxEnergy;
                };

                // Star Points
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_status_star_point_0_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t curPoints = gPlayerData.starPoints;
                if (UIWidgets::SliderInt("##pCurSP", &curPoints, UIWidgets::IntSliderOptions()
                    .Color(WIDGET_COLOR)
                    .LabelPosition(UIWidgets::LabelPositions::None)
                    .Format("Star Points: %i")
                    .Min(0)
                    .Max(99))) {
                    gPlayerData.starPoints = curPoints;
                };

                // Coins
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_status_coin_0_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t curCoins = gPlayerData.coins;
                if (UIWidgets::SliderInt("##pCurCoins", &curCoins, UIWidgets::IntSliderOptions()
                    .Color(WIDGET_COLOR)
                    .LabelPosition(UIWidgets::LabelPositions::None)
                    .Format("Coins: %i")
                    .Min(0)
                    .Max(999))) {
                    gPlayerData.coins = curCoins;
                };

                // Star Pieces
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_status_star_piece_0_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t curPieces = gPlayerData.starPieces;
                int32_t collectedPieces = gPlayerData.starPiecesCollected;
                if (UIWidgets::SliderInt("##pCurPieces", &curPieces, UIWidgets::IntSliderOptions()
                    .Color(WIDGET_COLOR)
                    .LabelPosition(UIWidgets::LabelPositions::None)
                    .Format("Current Pieces: %i")
                    .Min(0)
                    .Max(160))) {
                    gPlayerData.starPieces = curPieces;
                };
                if (UIWidgets::SliderInt("##pColPieces", &collectedPieces, UIWidgets::IntSliderOptions()
                    .Color(WIDGET_COLOR)
                    .LabelPosition(UIWidgets::LabelPositions::None)
                    .Format("Collected Pieces: %i")
                    .Min(0)
                    .Max(160))) {
                    gPlayerData.starPiecesCollected = collectedPieces;
                };

                // Play Time
                ImGui::TableNextColumn();
                ImGui::Image(gui->GetTextureByName(ui_pause_stat_time_png), statImageSize);
                ImGui::TableNextColumn();
                int32_t curTime = ((gPlayerData.frameCounter / 60) / 60);
                if (UIWidgets::SliderInt("##pCurTime", &curTime, UIWidgets::IntSliderOptions()
                    .Color(WIDGET_COLOR)
                    .LabelPosition(UIWidgets::LabelPositions::None)
                    .Format("Time: %i")
                    .Min(0)
                    .Max(5998))) {
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
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetInstance()->GetWindow()->GetGui());
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
    auto gui = std::dynamic_pointer_cast<Fast::Fast3dGui>(Ship::Context::GetInstance()->GetWindow()->GetGui());
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
                if (ImGui::ImageButton(label.c_str(), gui->GetTextureByName(partyMemberList[partyIndex].second), statImageSize, ImVec2(0, 0), ImVec2(1, 1),
                    ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, isUnlocked == 0 ? 0.5f : 1.0f))) {
                    if (isUnlocked == 1) {
                        gPlayerData.partners[gPausePartnersPartnerIDs[i]].enabled = 0;
                    }
                    else {
                        gPlayerData.partners[gPausePartnersPartnerIDs[i]].enabled = 1;
                    }
                }

                ImGui::TableNextColumn();
                TextureData rankTexture = GetRankTexture(rank);
                if (ImGui::ImageButton("Rank", rankTexture.textureId, statImageSize, ImVec2(0, 0), ImVec2(1, 1),
                    ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, rank == 0 ? 0.5f : 1.0f))) {
                    if (rank == 2) {
                        gPlayerData.partners[gPausePartnersPartnerIDs[i]].level = 0;
                    }
                    else {
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

void SaveEditor_DrawTabBar() {
    UIWidgets::PushStyleTabs(WIDGET_COLOR);
    if (ImGui::BeginTabBar("SaveEditorTabBar")) {
        if (ImGui::BeginTabItem("General")) {
            SaveEditor_DrawGeneralMenu();
            ImGui::EndTabItem();
        }
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

void SaveEditorWindow::InitElement() {}

#pragma pop_macro("End")
