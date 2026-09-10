#include "ValueViewer.h"
#include "port/ui/UIWidgets.hpp"
#include <string>
#include <spdlog/fmt/fmt.h>
#include <imgui.h>
#include <ship/Context.h>
#include <ship/window/Window.h>

#include "common_structs.h"

extern "C" {
#include "map.h"
#include "battle/battle.h"
}

#pragma push_macro("End")
#undef End

#define CVAR_NAME_SHOW_VALUE_VIEWER "gWindows.ValueViewer"
#define CVAR_NAME_ENABLE_FLOATING_WINDOW "gValueViewer.Floating"
#define CVAR_NAME_VALUE_VIEWER_OPACITY "gValueViewer.Opacity"
#define CVAR_NAME_VALUE_VIEWER_SCALE "gValueViewer.Scale"
#define CVAR_NAME_SHOW_MAP "gValueViewer.ShowMap"
#define CVAR_NAME_SHOW_POSITION "gValueViewer.ShowPosition"

#define CVAR_SHOW_VALUE_VIEWER CVarGetInteger(CVAR_NAME_SHOW_VALUE_VIEWER, 0)
#define CVAR_ENABLE_FLOATING_WINDOW CVarGetInteger(CVAR_NAME_ENABLE_FLOATING_WINDOW, 0)
#define CVAR_VALUE_VIEWER_OPACITY CVarGetFloat(CVAR_NAME_VALUE_VIEWER_OPACITY, 0.5f)
#define CVAR_VALUE_VIEWER_SCALE CVarGetFloat(CVAR_NAME_VALUE_VIEWER_SCALE, 0.5f)
#define CVAR_SHOW_MAP CVarGetInteger(CVAR_NAME_SHOW_MAP, 0)
#define CVAR_SHOW_POSITION CVarGetInteger(CVAR_NAME_SHOW_POSITION, 0)

extern "C" {
extern PlayerStatus gPlayerStatus;
extern PlayerData gPlayerData;
extern GameStatus* gGameStatusPtr;
extern AreaConfig gAreas[29];
extern StageListRow* gCurrentStagePtr;
extern s32 gCurrentBattleID;
extern s32 gCurrentStageID;
}

std::map<ValueViewerTypes, const char*> valueViewerOptions = {
    { VALUE_TYPE_MAP,  CVAR_NAME_SHOW_MAP },
    { VALUE_TYPE_POSITION,  CVAR_NAME_SHOW_POSITION },
};

std::vector<ValueViewerTypes> enabledSettingsList;

ImGuiWindowFlags valueViewerWindowFlags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_AlwaysAutoResize;
ImVec4 valueViewerBG = ImVec4{ 0, 0, 0, 0.5f };
float valueViewerScale = 1.0f;

std::string position = "";
std::string stageName = "";
std::string battleName = "";
int32_t battleId = 0;
MapConfig* mapData;

void ValueViewerSettings_Update() {
    enabledSettingsList.clear();
    for (auto& [setting, cvar] : valueViewerOptions) {
        if (CVarGetInteger(cvar, 0)) {
            enabledSettingsList.push_back(setting);
        }
    }
}

void ValueViewerSettings_DrawOptionsMenu() {
    if (ImGui::BeginTable("OptionsTable", 2)) {
        ImGui::TableSetupColumn("col1", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("col2", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableNextColumn();

        ImGui::SeparatorText("Window Options");
        UIWidgets::CVarCheckbox("Floating Window", CVAR_NAME_ENABLE_FLOATING_WINDOW);
        if (UIWidgets::CVarSliderFloat("", CVAR_NAME_VALUE_VIEWER_OPACITY,
            {
                .format = "Opacity: %.1f",
                .step = 0.01f,
                .min = 0.0f,
                .max = 1.0f,
                .defaultValue = 0.5f,
                .labelPosition = UIWidgets::LabelPositions::None,
                .color = WIDGET_COLOR,
            })) {
            valueViewerBG.w = CVAR_VALUE_VIEWER_OPACITY;
        }
        if (UIWidgets::CVarSliderFloat(" ", CVAR_NAME_VALUE_VIEWER_SCALE,
            {
                .format = "Scale: %.1f",
                .step = 0.10f,
                .min = 0.7f,
                .max = 2.5f,
                .defaultValue = 1.0f,
                .labelPosition = UIWidgets::LabelPositions::None,
                .color = WIDGET_COLOR,
            })) {
            valueViewerScale = CVAR_VALUE_VIEWER_SCALE;
        }

        ImGui::TableNextColumn();
        ImGui::SeparatorText("Value Options");
        if (UIWidgets::CVarCheckbox("Show Current Map", CVAR_NAME_SHOW_MAP)) {
            ValueViewerSettings_Update();
        };
        if (UIWidgets::CVarCheckbox("Show Mario's Position", CVAR_NAME_SHOW_POSITION)) {
            ValueViewerSettings_Update();
        };

        ImGui::EndTable();
    }
}

void ValueViewer_DrawOption(ValueViewerTypes option) {
    switch (option) {
        case VALUE_TYPE_MAP:
            if (gGameStatus.context == CONTEXT_WORLD) {
                ImGui::TableNextColumn();
                ImGui::Text("Map:");

                ImGui::TableNextColumn();
                mapData = &gAreas[gGameStatusPtr->areaID].maps[gGameStatusPtr->mapID];
                ImGui::Text("%s (%i)", mapData->id, gGameStatus.entryID);
            } else if (gGameStatus.context == CONTEXT_BATTLE && gCurrentStagePtr != NULL) {
                ImGui::TableNextColumn();
                ImGui::Text("Stage:");

                ImGui::TableNextColumn();
                stageName = gCurrentStagePtr->stage->shape;
                if (stageName.size() > 6) {
                    stageName.erase(stageName.size() - 6);
                }
                ImGui::Text(stageName.c_str());

                ImGui::TableNextColumn();
                ImGui::Text("Battle:");

                ImGui::TableNextColumn();
                battleId = (gCurrentBattleID << 16 | (gCurrentStageID & 0xFFFF));
                battleName = fmt::format("{:02}-{:02} ({})", ((battleId >> 24) & 0xFF), ((battleId >> 16) & 0xFF), (battleId & 0xFFF));
                ImGui::Text(battleName.c_str());
            }
            break;
        case VALUE_TYPE_POSITION:
            if (gGameStatus.context == CONTEXT_WORLD) {
                ImGui::TableNextColumn();
                ImGui::Text("Pos:");
                ImGui::TableNextColumn();
                position = fmt::format("{:.5f}, {:.5f}, {:.5f}", gPlayerStatus.pos.x, gPlayerStatus.pos.y, gPlayerStatus.pos.z);
                ImGui::Text(position.c_str());
            }
            break;
        default:
            break;
    }
}

void ValueViewerSettings_DrawTabBar(void) {
    UIWidgets::PushStyleTabs(WIDGET_COLOR);
    if (ImGui::BeginTabBar("ValueViewerTabBar")) {
        if (ImGui::BeginTabItem("Options")) {
            ValueViewerSettings_DrawOptionsMenu();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    UIWidgets::PopStyleTabs();
}

void ValueViewerWindow::Draw() {
    if (!CVAR_SHOW_VALUE_VIEWER) {
        return;
    }

    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, valueViewerBG);
    ImGui::PushStyleColor(ImGuiCol_TitleBg, valueViewerBG);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, valueViewerBG);
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);

    if (ImGui::Begin("ValueViewer", nullptr, valueViewerWindowFlags)) {
        ImGui::SetWindowFontScale(valueViewerScale);

        if (enabledSettingsList.empty()) {
            ImGui::TextColored(UIWidgets::ColorValues.at(UIWidgets::Colors::Orange), "No Options Enabled");
        } else {
            if (ImGui::BeginTable("ValueTable", 2)) {
                for (auto& setting : enabledSettingsList) {
                    ValueViewer_DrawOption(setting);
                }
                ImGui::EndTable();
            }


        }
    }

    ImGui::End();

    ImGui::PopStyleColor(4);
    ImGui::PopStyleVar(1);
}

void ValueViewerWindow::OnInit(const nlohmann::json& initArgs) {
  Ship::GuiWindow::OnInit(initArgs);
    ValueViewerSettings_Update();
    valueViewerBG = { 0, 0, 0, CVAR_VALUE_VIEWER_OPACITY };
    valueViewerScale = CVAR_VALUE_VIEWER_SCALE;

    valueViewerWindowFlags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_AlwaysAutoResize;
    if (CVAR_ENABLE_FLOATING_WINDOW) {
        valueViewerWindowFlags |= ImGuiWindowFlags_NoTitleBar;
    }
}

void ValueViewerSettingsWindow::DrawElement() {
    if (UIWidgets::Button("Toggle Value Viewer", UIWidgets::ButtonOptions().Color(CVarGetInteger("gWindows.ValueViewer", 0) ? UIWidgets::Colors::Red : UIWidgets::Colors::Green))) {
        int32_t value = CVarGetInteger("gWindows.ValueViewer", 0) ? 0 : 1;
        CVarSetInteger("gWindows.ValueViewer", value);
    }

    ValueViewerSettings_DrawTabBar();
}

#pragma pop_macro("End")
