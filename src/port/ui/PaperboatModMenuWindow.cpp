#include <algorithm>
#include <atomic>
#include <cctype>
#include <thread>
#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <libultraship/libultraship.h>
#include <libultraship/bridge/consolevariablebridge.h>
#include <ship/Context.h>
#include <ship/resource/ResourceManager.h>
#include <ship/resource/archive/ArchiveManager.h>
#include <ship/utils/StringHelper.h>
#include <ship/window/Window.h>
#include <ship/window/gui/IconsFontAwesome4.h>
#include <spdlog/spdlog.h>

#include "PaperboatModMenuWindow.h"
#include "PaperboatGui.hpp"
#include "PaperboatMenu.h"
#include "Menu.h"
#include "MenuTypes.h"
#include "UIWidgets.hpp"
#include "port/Engine.h"
#include "port/extractor/GameExtractor.h"
#include "port/modding/Features.h"
#include "port/modding/ModManifest.h"
#include "port/romhack/Romhack.h"

static std::vector<std::string> enabledModFiles;
static std::vector<std::string> disabledModFiles;
static std::map<std::string, std::filesystem::path> filePaths;

static int dragSourceIndex = -1;
static int dragTargetIndex = -1;

static WidgetInfo altAssetsWidget;
static WidgetInfo autoMipmapsWidget;

#define CVAR_ENABLED_MODS_NAME  CVAR_SETTING("EnabledMods")
#define CVAR_DISABLED_MODS_NAME CVAR_SETTING("DisabledMods")
#define SEPARATOR               "|"

static std::string JoinModList(const std::vector<std::string>& list) {
    std::string s;
    for (const auto& name : list) {
        s += name + SEPARATOR;
    }
    if (!s.empty()) {
        s.pop_back();
    }
    return s;
}

static void SaveModLists() {
    CVarSetString(CVAR_ENABLED_MODS_NAME, JoinModList(enabledModFiles).c_str());
    CVarSetString(CVAR_DISABLED_MODS_NAME, JoinModList(disabledModFiles).c_str());
    Ship::Context::GetRawInstance()->GetWindow()->GetGui()->SaveConsoleVariablesNextFrame();
}

static void SortDisabledMods() {
    std::sort(disabledModFiles.begin(), disabledModFiles.end(), [](const std::string& a, const std::string& b) {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), [](char c1, char c2) {
            return std::tolower(c1) < std::tolower(c2);
        });
    });
}

static void ModsPostDragAndDrop() {
    if (dragTargetIndex != -1) {
        std::string file = enabledModFiles[dragSourceIndex];
        enabledModFiles.erase(enabledModFiles.begin() + dragSourceIndex);
        enabledModFiles.insert(enabledModFiles.begin() + dragTargetIndex, file);
        dragTargetIndex = dragSourceIndex = -1;
    }
}

static void ModsHandleDragAndDrop(int targetIndex, const std::string& itemName) {
    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
        ImGui::SetDragDropPayload("DragMove", &targetIndex, sizeof(uint32_t));
        ImGui::Text("Move %s", itemName.c_str());
        ImGui::EndDragDropSource();
    }

    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragMove")) {
            IM_ASSERT(payload->DataSize == sizeof(uint32_t));
            dragSourceIndex = *(const int*) payload->Data;
            dragTargetIndex = targetIndex;
        }
        ImGui::EndDragDropTarget();
    }
}

static std::vector<std::string> SplitModCVar(const char* name) {
    std::string value = CVarGetString(name, "");
    if (value.empty()) {
        return {};
    }
    return StringHelper::Split(value, SEPARATOR);
}

static std::vector<std::string>& GetModFiles(bool enabled) {
    return enabled ? enabledModFiles : disabledModFiles;
}

static std::shared_ptr<Ship::ArchiveManager> GetArchiveManager() {
    return Ship::Context::GetRawInstance()->GetResourceManager()->GetArchiveManager();
}

static bool IsValidExtension(const std::string& extension) {
    return StringHelper::IEquals(extension, ".o2r") || StringHelper::IEquals(extension, ".otr")
        || StringHelper::IEquals(extension, ".zip");
}

void UpdateModFiles(bool init, bool reset) {
    if (init || reset) {
        enabledModFiles = SplitModCVar(CVAR_ENABLED_MODS_NAME);
        disabledModFiles = SplitModCVar(CVAR_DISABLED_MODS_NAME);
    } else {
        disabledModFiles.clear();
    }
    filePaths.clear();

    std::string modsPath = Ship::Context::GetPathRelativeToAppDirectory("mods");
    if (modsPath.empty() || !std::filesystem::is_directory(modsPath)) {
        return;
    }

    bool changed = false;

    std::vector<std::string> discovered;
    for (const auto& entry : std::filesystem::directory_iterator(modsPath)) {
        if (!entry.is_directory() && !(entry.is_regular_file() && IsValidExtension(entry.path().extension().string())))
        {
            continue;
        }
        std::string name = entry.path().filename().generic_string();
        if (name.starts_with("~")) {
            continue;
        }
        filePaths.emplace(name, entry.path());
        discovered.push_back(name);
    }

    std::sort(discovered.begin(), discovered.end());
    for (const std::string& name : discovered) {
        if (std::find(enabledModFiles.begin(), enabledModFiles.end(), name) != enabledModFiles.end()) {
            continue;
        }
        if (std::find(disabledModFiles.begin(), disabledModFiles.end(), name) != disabledModFiles.end()) {
            continue;
        }
        enabledModFiles.push_back(name);
        changed = true;
    }

    auto vanished = [](const std::string& n) { return filePaths.find(n) == filePaths.end(); };
    size_t before = enabledModFiles.size() + disabledModFiles.size();
    enabledModFiles.erase(
        std::remove_if(enabledModFiles.begin(), enabledModFiles.end(), vanished), enabledModFiles.end()
    );
    disabledModFiles.erase(
        std::remove_if(disabledModFiles.begin(), disabledModFiles.end(), vanished), disabledModFiles.end()
    );
    if (enabledModFiles.size() + disabledModFiles.size() != before) {
        changed = true;
    }

    for (const auto& [name, path] : filePaths) {
        if (std::find(enabledModFiles.begin(), enabledModFiles.end(), name) == enabledModFiles.end()
            && std::find(disabledModFiles.begin(), disabledModFiles.end(), name) == disabledModFiles.end())
        {
            disabledModFiles.push_back(name);
        }
    }
    SortDisabledMods();

    if (init) {
        const std::string base = Mod::ActiveBase();
        for (const std::string& mod : enabledModFiles) {
            auto it = filePaths.find(mod);
            if (it == filePaths.end()) {
                continue;
            }
            SPDLOG_INFO("Loading mod archive: {}", it->second.generic_string());
            Mod::ModRecord record;
            record.file = mod;
            auto archive = Mod::OpenArchive(it->second);
            if (archive == nullptr) {
                record.owner = record.displayName = mod;
                record.skipReason = "The archive could not be opened.";
                Mod::RecordMod(std::move(record));
                continue;
            }
            record.manifest = Mod::ReadManifest(*archive);
            record.owner = record.manifest.has_value() && !record.manifest->id.empty() ? record.manifest->id : mod;
            record.displayName =
                record.manifest.has_value() && !record.manifest->name.empty() ? record.manifest->name : mod;
            const auto reason =
                record.manifest.has_value() ? Mod::IncompatibleReason(*record.manifest, base) : std::nullopt;
            if (reason.has_value()) {
                SPDLOG_WARN("Not loading mod {}: {}", mod, *reason);
                record.skipReason = *reason;
            } else {
                record.mounted = GetArchiveManager()->AddArchive(archive) != nullptr;
                if (!record.mounted) {
                    record.skipReason = "The archive could not be added.";
                }
            }
            Mod::RecordMod(std::move(record));
        }
    }

    if (changed) {
        SaveModLists();
    }
}

void EnableMod(std::string file) {
    auto it = std::find(disabledModFiles.begin(), disabledModFiles.end(), file);
    if (it == disabledModFiles.end()) {
        return;
    }
    disabledModFiles.erase(it);
    enabledModFiles.push_back(file);
}

void DisableMod(std::string file) {
    auto it = std::find(enabledModFiles.begin(), enabledModFiles.end(), file);
    if (it == enabledModFiles.end()) {
        return;
    }
    enabledModFiles.erase(it);
    disabledModFiles.push_back(file);
    SortDisabledMods();
}

static std::string ModSkipReason(const std::string& file) {
    if (const Mod::ModRecord* record = Mod::FindModRecord(file)) {
        return record->mounted ? "" : "Not loaded. " + record->skipReason;
    }
    const auto path = filePaths.find(file);
    if (path == filePaths.end()) {
        return "";
    }
    const auto& manifest = Mod::CachedManifest(file, path->second);
    if (!manifest.has_value()) {
        return "";
    }
    return Mod::IncompatibleReason(*manifest, Mod::ActiveBase()).value_or("");
}

static void DrawRuleConflicts() {
    const auto& conflicts = Features::Conflicts();
    if (conflicts.empty()) {
        return;
    }
    ImGui::TextColored(UIWidgets::ColorValues.at(UIWidgets::Colors::Orange), "Mods disagree on these settings:");
    for (const Features::Conflict& conflict : conflicts) {
        ImGui::BulletText(
            "%s: %s overrides %s (%s)", conflict.id.c_str(), conflict.winner.c_str(), conflict.loser.c_str(),
            Features::LockReason(conflict.id.c_str()).c_str()
        );
    }
}

static void DrawMods(bool enabled) {
    std::vector<std::string>& selectedModFiles = GetModFiles(enabled);
    if (selectedModFiles.empty()) {
        return;
    }

    bool reordered = false;
    size_t switchFromIndex = 0;
    size_t switchToIndex = 0;
    std::string pendingMoveFile;

    for (size_t k = 0; k < selectedModFiles.size(); k++) {
        size_t i = enabled ? (selectedModFiles.size() - 1 - k) : k;
        std::string file = selectedModFiles[i];
        if (enabled) {
            ImGui::BeginGroup();
        }

        if (UIWidgets::StateButton(
                (file + "_left_right").c_str(), enabled ? ICON_FA_ARROW_RIGHT : ICON_FA_ARROW_LEFT, ImVec2(25, 25),
                UIWidgets::ButtonOptions().Color(THEME_COLOR)
            ))
        {
            pendingMoveFile = file;
        }

        if (enabled) {
            const bool atTop = (i == selectedModFiles.size() - 1);
            const bool atBottom = (i == 0);

            ImGui::SameLine();
            ImGui::BeginDisabled(atTop);
            if (UIWidgets::StateButton(
                    (file + "_up").c_str(), ICON_FA_ARROW_UP, ImVec2(25, 25),
                    UIWidgets::ButtonOptions().Color(THEME_COLOR)
                ))
            {
                reordered = true;
                switchFromIndex = i;
                switchToIndex = i + 1;
            }
            ImGui::EndDisabled();

            ImGui::SameLine();
            ImGui::BeginDisabled(atBottom);
            if (UIWidgets::StateButton(
                    (file + "_down").c_str(), ICON_FA_ARROW_DOWN, ImVec2(25, 25),
                    UIWidgets::ButtonOptions().Color(THEME_COLOR)
                ))
            {
                reordered = true;
                switchFromIndex = i;
                switchToIndex = i - 1;
            }
            ImGui::EndDisabled();
        }

        ImGui::SameLine();
        const std::string reason = ModSkipReason(file);
        if (reason.empty()) {
            ImGui::Text("%s", file.c_str());
        } else {
            ImGui::TextDisabled("%s " ICON_FA_EXCLAMATION_TRIANGLE, file.c_str());
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
                ImGui::SetTooltip("%s", reason.c_str());
            }
        }

        if (enabled) {
            ImGui::EndGroup();
            ModsHandleDragAndDrop((int) i, file);
        }
    }

    if (enabled) {
        ModsPostDragAndDrop();
    }

    if (reordered) {
        std::iter_swap(selectedModFiles.begin() + switchFromIndex, selectedModFiles.begin() + switchToIndex);
    }

    if (!pendingMoveFile.empty()) {
        if (enabled) {
            DisableMod(pendingMoveFile);
        } else {
            EnableMod(pendingMoveFile);
        }
    }
}

static bool editing = false;

static void DrawModManager() {
    auto editOpts = UIWidgets::ButtonOptions().Size(UIWidgets::Sizes::Inline).Color(THEME_COLOR);
    editOpts.Disabled(editing);
    editOpts.DisabledTooltip("Already editing...");
    if (UIWidgets::Button("Edit", editOpts)) {
        editing = true;
    }
    if (editing) {
        ImGui::SameLine();
        if (UIWidgets::Button("Cancel", UIWidgets::ButtonOptions().Size(UIWidgets::Sizes::Inline))) {
            editing = false;
            UpdateModFiles(false, true);
        }
        ImGui::SameLine();
        if (UIWidgets::Button("Clear List", UIWidgets::ButtonOptions().Size(UIWidgets::Sizes::Inline))) {
            PaperboatGui::RegisterPopup(
                "Clear List", "Disable every mod in the list.\nClick Apply to save this change.", "Clear", "Cancel",
                []() {
                    for (const std::string& mod : enabledModFiles) {
                        disabledModFiles.push_back(mod);
                    }
                    enabledModFiles.clear();
                    SortDisabledMods();
                }
            );
        }
        ImGui::SameLine();
        const bool restarts = GameEngine::CanRelaunch();
        if (UIWidgets::Button(
                restarts ? "Apply & Restart" : "Apply",
                UIWidgets::ButtonOptions().Size(UIWidgets::Sizes::Inline).Color(THEME_COLOR)
            ))
        {
            PaperboatGui::RegisterPopup(
                restarts ? "Apply & Restart" : "Apply",
                restarts ? "Applying mods requires a restart. Save the mod list and relaunch Paperboat now?"
                         : "Save the mod list? Mods are loaded at boot, so the change takes\neffect the next time "
                           "Paperboat starts.",
                restarts ? "Restart" : "Save", "Cancel", [restarts]() {
                    SaveModLists();
                    Ship::Context::GetRawInstance()->GetConsoleVariables()->Save();
                    editing = false;
                    if (restarts) {
                        GameEngine::RequestRelaunch();
                        Ship::Context::GetRawInstance()->GetWindow()->Close();
                    }
                }
            );
        }
    }
    ImGui::BeginDisabled(!editing);
    if (ImGui::BeginTable("tableMods", 2, ImGuiTableFlags_BordersH | ImGuiTableFlags_BordersV)) {
        ImGui::TableSetupColumn("Enabled Mods", ImGuiTableColumnFlags_WidthStretch, 200.0f);
        ImGui::TableSetupColumn("Disabled Mods", ImGuiTableColumnFlags_WidthStretch, 200.0f);
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::TableHeadersRow();
        ImGui::PopItemFlag();
        ImGui::TableNextRow();

        ImGui::TableNextColumn();
        if (ImGui::BeginChild("Enabled Mods", ImVec2(0, -8))) {
            DrawMods(true);
            ImGui::EndChild();
        }

        ImGui::TableNextColumn();
        if (ImGui::BeginChild("Disabled Mods", ImVec2(0, -8))) {
            DrawMods(false);
            ImGui::EndChild();
        }

        ImGui::EndTable();
    }
    ImGui::EndDisabled();
}

static GameExtractor sRomhackExtractor;
static std::atomic<bool> sRomhackExtracting = false;
static std::atomic<size_t> sRomhackExtractCount { 0 }, sRomhackExtractTotal { 0 };
static std::string sRomhackPending;
enum class RomhackResult {
    None,
    Done,
    Failed
};
static std::atomic<RomhackResult> sRomhackResult = RomhackResult::None;

static void RestartIntoRomhack(const std::string& stem) {
    Romhack::SetSelected(stem);
    if (GameEngine::CanRelaunch()) {
        GameEngine::RequestRelaunch();
        Ship::Context::GetRawInstance()->GetWindow()->Close();
    }
}

static void StartRomhackExtraction() {
    sRomhackExtractor = GameExtractor();
    sRomhackExtractor.SelectGameFromUI([](bool picked) {
        if (!picked) {
            return;
        }
        const auto recipe = sRomhackExtractor.GetRomhack();
        if (!recipe.has_value()) {
            PaperboatGui::RegisterPopup(
                "Not a Supported Romhack",
                "That ROM is not a romhack PaperBoat has a recipe for.\nPatch the hack onto a US Paper Mario ROM "
                "and pick the patched .z64."
            );
            return;
        }
        sRomhackPending = std::filesystem::path(recipe->output).stem().string();
        sRomhackExtracting = true;
        std::thread([]() {
            const bool ok = sRomhackExtractor.GenerateOTR(sRomhackExtractCount, sRomhackExtractTotal, "boat");
            sRomhackResult = ok ? RomhackResult::Done : RomhackResult::Failed;
            sRomhackExtracting = false;
        }).detach();
    });
}

static void ReportRomhackExtraction() {
    const RomhackResult result = sRomhackResult.exchange(RomhackResult::None);
    if (result == RomhackResult::Failed) {
        const std::string msg = "Extraction failed:\n" + GameExtractor::sLastError;
        PaperboatGui::RegisterPopup("Romhack Extraction Failed", msg.c_str());
    } else if (result == RomhackResult::Done) {
        const std::string stem = sRomhackPending;
        PaperboatGui::RegisterPopup(
            "Romhack Ready", "Play it now? PaperBoat restarts into the romhack.", "Play", "Later",
            [stem]() { RestartIntoRomhack(stem); }
        );
    }
}

static bool sRomhackEditing = false;
static std::string sRomhackEnabled;
static WidgetInfo generateRomhackWidget;

static void DrawRomhackList(bool enabled, const std::vector<std::string>& stems) {
    for (const auto& stem : stems) {
        if ((stem == sRomhackEnabled) != enabled) {
            continue;
        }
        if (UIWidgets::StateButton(
                (stem + "_romhack_left_right").c_str(), enabled ? ICON_FA_ARROW_RIGHT : ICON_FA_ARROW_LEFT,
                ImVec2(25, 25), UIWidgets::ButtonOptions().Color(THEME_COLOR)
            ))
        {
            sRomhackEnabled = enabled ? "" : stem;
        }
        ImGui::SameLine();
        ImGui::Text("%s.o2r", stem.c_str());
    }
}

static void DrawRomhackManager() {
    const std::vector<std::string> stems = Romhack::ListArchives();
    if (!sRomhackEnabled.empty() && std::find(stems.begin(), stems.end(), sRomhackEnabled) == stems.end()) {
        sRomhackEnabled.clear();
    }

    auto editOpts = UIWidgets::ButtonOptions().Size(UIWidgets::Sizes::Inline).Color(THEME_COLOR);
    editOpts.Disabled(sRomhackEditing || sRomhackExtracting);
    editOpts.DisabledTooltip("Already editing...");
    if (UIWidgets::Button("Edit##romhacks", editOpts)) {
        sRomhackEditing = true;
    }
    if (sRomhackEditing) {
        ImGui::SameLine();
        if (UIWidgets::Button("Cancel##romhacks", UIWidgets::ButtonOptions().Size(UIWidgets::Sizes::Inline))) {
            sRomhackEditing = false;
            sRomhackEnabled = Romhack::GetSelected();
        }
        ImGui::SameLine();
        if (UIWidgets::Button("Clear List##romhacks", UIWidgets::ButtonOptions().Size(UIWidgets::Sizes::Inline))) {
            PaperboatGui::RegisterPopup(
                "Clear List", "Disable the romhack and play Paper Mario.\nClick Apply to save this change.", "Clear",
                "Cancel", []() { sRomhackEnabled.clear(); }
            );
        }
        ImGui::SameLine();
        const bool restarts = GameEngine::CanRelaunch();
        if (UIWidgets::Button(
                restarts ? "Apply & Restart##romhacks" : "Apply##romhacks",
                UIWidgets::ButtonOptions().Size(UIWidgets::Sizes::Inline).Color(THEME_COLOR)
            ))
        {
            PaperboatGui::RegisterPopup(
                restarts ? "Apply & Restart" : "Apply",
                restarts ? "Switching romhacks requires a restart. Save the selection and relaunch Paperboat now?"
                         : "Save the selection? It takes effect the next time Paperboat starts.",
                restarts ? "Restart" : "Save", "Cancel", []() {
                    sRomhackEditing = false;
                    RestartIntoRomhack(sRomhackEnabled);
                }
            );
        }
    }

    ImGui::BeginDisabled(!sRomhackEditing);
    if (ImGui::BeginTable("tableRomhacks", 2, ImGuiTableFlags_BordersH | ImGuiTableFlags_BordersV)) {
        ImGui::TableSetupColumn("Enabled Romhack", ImGuiTableColumnFlags_WidthStretch, 200.0f);
        ImGui::TableSetupColumn("Disabled Romhacks", ImGuiTableColumnFlags_WidthStretch, 200.0f);
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::TableHeadersRow();
        ImGui::PopItemFlag();
        ImGui::TableNextRow();

        ImGui::TableNextColumn();
        if (ImGui::BeginChild("Enabled Romhack", ImVec2(0, -8))) {
            DrawRomhackList(true, stems);
            ImGui::EndChild();
        }

        ImGui::TableNextColumn();
        if (ImGui::BeginChild("Disabled Romhacks", ImVec2(0, -8))) {
            DrawRomhackList(false, stems);
            ImGui::EndChild();
        }

        ImGui::EndTable();
    }
    ImGui::EndDisabled();
}

static std::vector<Romhack::Supported> sSupportedRomhacks;

static void DrawSupportedRomhacks() {
    for (const auto& hack : sSupportedRomhacks) {
        ImGui::PushID(hack.id.c_str());
        ImGui::BeginDisabled(hack.url.empty());
        if (UIWidgets::Button(
                ICON_FA_EXTERNAL_LINK,
                UIWidgets::ButtonOptions().Size(UIWidgets::Sizes::Inline).Color(THEME_COLOR).Tooltip(hack.url.c_str())
            ))
        {
            SDL_OpenURL(hack.url.c_str());
        }
        ImGui::EndDisabled();
        ImGui::SameLine();
        ImGui::AlignTextToFramePadding();
        if (hack.version.empty()) {
            ImGui::Text("%s", hack.name.c_str());
        } else {
            ImGui::Text("%s (v%s)", hack.name.c_str(), hack.version.c_str());
        }
        ImGui::PopID();
    }
}

void PaperboatRomhackMenuWindow::DrawElement() {
    ReportRomhackExtraction();

    ImGui::BeginDisabled(sRomhackExtracting);
    PaperboatGui::mPaperboatMenu->MenuDrawItem(generateRomhackWidget, 200, PaperboatGui::GetMenuThemeColor());
    ImGui::EndDisabled();
    if (sRomhackExtracting) {
        const size_t total = sRomhackExtractTotal;
        const float progress = total > 0 ? std::min<float>(1.0f, (float) sRomhackExtractCount / (float) total) : 0.0f;
        ImGui::ProgressBar(progress, ImVec2(-1.0f, 0.0f), "Extracting romhack...");
    }

    UIWidgets::PushStyleTabs(THEME_COLOR);
    if (ImGui::BeginTabBar("RomhackTabs")) {
        if (ImGui::BeginTabItem("Installed Romhacks")) {
            DrawRomhackManager();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Supported Romhacks")) {
            DrawSupportedRomhacks();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    UIWidgets::PopStyleTabs();
}

void PaperboatRomhackMenuWindow::InitElement() {
    sRomhackEnabled = Romhack::GetSelected();
    sSupportedRomhacks = Romhack::ListSupported();
}

void PaperboatModMenuWindow::DrawElement() {
    PaperboatGui::mPaperboatMenu->MenuDrawItem(altAssetsWidget, 200, PaperboatGui::GetMenuThemeColor());
    PaperboatGui::mPaperboatMenu->MenuDrawItem(autoMipmapsWidget, 200, PaperboatGui::GetMenuThemeColor());

    ImGui::TextColored(
        UIWidgets::ColorValues.at(UIWidgets::Colors::Yellow),
        "Mods are not reloaded at runtime, so applying changes restarts Paperboat.\n"
        "Priority runs top to bottom: a mod overrides everything listed below it.\n"
        "Drag an entry or use the arrows to reorder the enabled list."
    );
    DrawRuleConflicts();

    DrawModManager();
}

void PaperboatModMenuWindow::InitElement() {
    UpdateModFiles(false, true);
}

static void RegisterModMenuWidgets() {
    altAssetsWidget = { .name = "Use Alternate Assets", .type = WidgetType::WIDGET_CVAR_CHECKBOX };
    altAssetsWidget.CVar(CVAR_ENHANCEMENT("Mods.AlternateAssets"))
        .Options(
            UIWidgets::CheckboxOptions()
                .DisabledTooltip("Temporarily disabled while editing the mods list.")
                .Color(THEME_COLOR)
                .Tooltip(
                    "Toggle between standard assets and alternate assets. Usually mods will indicate if this "
                    "setting has to be used or not."
                )
        )
        .PreFunc([](WidgetInfo& info) {
            std::static_pointer_cast<UIWidgets::CheckboxOptions>(info.options)->disabled = editing;
        });

    autoMipmapsWidget = { .name = "HD Texture Mipmaps", .type = WidgetType::WIDGET_CVAR_CHECKBOX };
    autoMipmapsWidget.CVar(CVAR_ENHANCEMENT("Mods.AutoMipmaps"))
        .Options(
            UIWidgets::CheckboxOptions()
                .DefaultValue(true)
                .DisabledTooltip("Mipmaps are disabled in Enhancements > Graphics.")
                .Color(THEME_COLOR)
                .Tooltip(
                    "Generates mipmaps for HD replacement textures, which smooths them in the distance. Turn it "
                    "off if the GPU hangs while a texture pack is enabled."
                )
        )
        .PreFunc([](WidgetInfo& info) {
            std::static_pointer_cast<UIWidgets::CheckboxOptions>(info.options)->disabled =
                Port_FeatureInt("graphics.disable_mipmaps", 0) != 0;
        });

    generateRomhackWidget = { .name = "Generate Romhack from ROM", .type = WidgetType::WIDGET_BUTTON };
    generateRomhackWidget
        .Callback([](WidgetInfo& info) {
            PaperboatGui::RegisterPopup(
                "Generate Romhack from ROM",
                "Select a patched romhack ROM to extract as an overlay. Torch generates\n"
                "a slim o2r in your mods/~romhacks/ folder alongside the existing\n"
                "pm64.o2r, holding only what the hack changed.",
                "Select ROM", "Cancel", []() { StartRomhackExtraction(); }
            );
        })
        .Options(
            UIWidgets::ButtonOptions()
                .Size(UIWidgets::Sizes::Inline)
                .Tooltip("Pick a patched romhack ROM and extract it as a slim overlay into the mods/~romhacks/ folder.")
        );
}

static RegisterMenuInitFunc menuInitFunc(RegisterModMenuWidgets);
