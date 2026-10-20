#include "PaperboatGui.hpp"
#include "PaperboatMenu.h"

#include "port/mods/ModScripts.h"
#ifdef USE_NETWORKING
#include "port/net/PlayerIdentity.h"
#include "port/net/SatellaClient.h"
#endif
#ifdef ENABLE_SCRIPTING
#include "port/permissions/Permissions.h"
#endif

#include <ship/Context.h>
#include <ship/config/Config.h>
#include <ship/utils/StringHelper.h>

#include <imgui.h>

namespace PaperboatGui {

using namespace UIWidgets;

namespace {

#ifdef USE_NETWORKING
    void DrawSatellaStatus() {
        auto& client = Satella::Client::Instance();
        if (client.IsConnected() && client.IsVerified()) {
            ImGui::TextColored(ColorValues.at(Colors::Green), "Connected");
        } else if (client.IsConnected()) {
            ImGui::TextColored(ColorValues.at(Colors::Yellow), "Connected, player key not accepted yet");
        } else if (client.GetPhase() == Satella::Phase::Connecting) {
            ImGui::TextColored(ColorValues.at(Colors::Yellow), "Connecting...");
        } else {
            ImGui::TextColored(ColorValues.at(Colors::Gray), "Offline");
        }

        // Empty is the public server.
        static char sHost[256] = {};
        static bool sHostRead = false;
        auto config = Ship::Context::GetRawInstance()->GetConfig();
        if (!sHostRead && config != nullptr) {
            snprintf(sHost, sizeof(sHost), "%s", config->GetString("Satella.Host", "").c_str());
            sHostRead = true;
        }
        ImGui::SetNextItemWidth(320.0f);
        ImGui::InputTextWithHint("##SatellaHost", SATELLA_HOST, sHost, sizeof(sHost));
        ImGui::SameLine();
        if (Button("Save Server", ButtonOptions().Size(Sizes::Inline).Color(THEME_COLOR)) && config != nullptr) {
            if (sHost[0] == '\0') {
                config->Erase("Satella.Host");
            } else {
                config->SetString("Satella.Host", sHost);
            }
            config->Save();
        }
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(
                "A Satella server of your own, e.g. ws://localhost:8080. Takes effect on the next start."
            );
        }

        const auto key = PlayerIdentity::GetPublicKey();
        if (!key.empty()) {
            const std::string hex = StringHelper::BytesToHex(key);
            ImGui::TextUnformatted("Player key:");
            ImGui::SameLine();
            ImGui::TextDisabled("%s...%s", hex.substr(0, 8).c_str(), hex.substr(hex.size() - 8).c_str());
            ImGui::SameLine();
            if (Button("Copy", ButtonOptions().Size(Sizes::Inline))) {
                ImGui::SetClipboardText(hex.c_str());
            }
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip(
                    "Other players and mods know you by this key. It never leaves this computer's config."
                );
            }
        }
    }
#endif

#ifdef ENABLE_SCRIPTING
    void DrawPermissions() {
        const auto answers = Permissions::All();
        if (answers.empty()) {
            ImGui::TextDisabled("No mod has asked for a permission yet.");
            return;
        }
        if (!ImGui::BeginTable("Permissions", 3, ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_SizingStretchProp)) {
            return;
        }
        for (const auto& [key, state] : answers) {
            ImGui::PushID(key.c_str());
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            const auto* prompt = Permissions::Prompt(key);
            ImGui::TextUnformatted(prompt != nullptr ? prompt->title.c_str() : key.c_str());
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("%s", prompt != nullptr ? prompt->message.c_str() : key.c_str());
            }
            ImGui::TableNextColumn();
            const bool allowed = state == Permissions::State::Allowed;
            ImGui::TextColored(
                allowed ? ColorValues.at(Colors::Green) : ColorValues.at(Colors::Red), "%s",
                allowed ? "Allowed" : "Denied"
            );
            ImGui::TableNextColumn();
            if (Button(allowed ? "Deny" : "Allow", ButtonOptions().Size(Sizes::Inline))) {
                Permissions::SetAnswer(key, allowed ? Permissions::State::Denied : Permissions::State::Allowed);
            }
            ImGui::SameLine();
            if (Button("Ask Again", ButtonOptions().Size(Sizes::Inline))) {
                Permissions::SetAnswer(key, Permissions::State::Pending);
            }
            ImGui::PopID();
        }
        ImGui::EndTable();
    }
#endif

} // namespace

void PaperboatMenu::AddMenuMods() {
    AddMenuEntry("Mods", CVAR_SETTING("Menu.ModsSidebarSection"));

    WidgetPath path = { "Mods", "Satella", SECTION_COLUMN_1 };
    AddSidebarEntry(path.sectionName, path.sidebarName, 1);
#ifdef USE_NETWORKING
    AddWidget(path, "Connect to Satella", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR_DEVELOPER_TOOLS("Satella"))
        .RaceDisable(false)
        .Options(
            CheckboxOptions().DefaultValue(true).Tooltip(
                "Connects to Satella when the game starts, for the keys trusted mods are signed with and for mods' "
                "online features. Takes effect on the next start."
            )
        );
    AddWidget(path, "##SatellaStatus", WIDGET_CUSTOM).RaceDisable(false).CustomFunction([](WidgetInfo&) {
        DrawSatellaStatus();
    });
#else
    AddWidget(path, "Satella isn't in this build, so mods can't go online.", WIDGET_TEXT).Options(TextOptions());
#endif
#ifdef ENABLE_SCRIPTING
    AddWidget(path, "Permissions", WIDGET_SEPARATOR_TEXT).Options(TextOptions());
    AddWidget(path, "##Permissions", WIDGET_CUSTOM)
        .RaceDisable(false)
        .HideInSearch(true)
        .CustomFunction([](WidgetInfo&) { DrawPermissions(); });
#endif
}

} // namespace PaperboatGui
