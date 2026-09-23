#include "Notification.h"
#include "PaperboatInputEditorWindow.h"
#include "PaperboatMenu.h"
#include "PaperboatModals.h"
#include "TouchControls.h"
#include "UIWidgets.hpp"
#include "port/Engine.h"
#include "port/TextureCache.h"
#include <spdlog/fmt/fmt.h>

namespace PaperboatGui {

extern std::shared_ptr<PaperboatMenu> mPaperboatMenu;
extern std::shared_ptr<PaperboatModalWindow> mModalWindow;
using namespace UIWidgets;

static std::unordered_map<int32_t, const char*> imguiScaleOptions = {
    { 0, "Small" },
    { 1, "Normal" },
    { 2, "Large" },
    { 3, "X-Large" },
};

static const std::unordered_map<int32_t, const char*> menuThemeOptions = {
    { UIWidgets::Colors::Red, "Red" },
    { UIWidgets::Colors::DarkRed, "Dark Red" },
    { UIWidgets::Colors::Orange, "Orange" },
    { UIWidgets::Colors::Green, "Green" },
    { UIWidgets::Colors::DarkGreen, "Dark Green" },
    { UIWidgets::Colors::LightBlue, "Light Blue" },
    { UIWidgets::Colors::Blue, "Blue" },
    { UIWidgets::Colors::DarkBlue, "Dark Blue" },
    { UIWidgets::Colors::Indigo, "Indigo" },
    { UIWidgets::Colors::Violet, "Violet" },
    { UIWidgets::Colors::Purple, "Purple" },
    { UIWidgets::Colors::Brown, "Brown" },
    { UIWidgets::Colors::Gray, "Gray" },
    { UIWidgets::Colors::DarkGray, "Dark Gray" },
};

static const std::unordered_map<int32_t, const char*> textureFilteringMap = {
    { Fast::FILTER_THREE_POINT, "Three-Point" },
    { Fast::FILTER_LINEAR, "Linear" },
    { Fast::FILTER_NONE, "None" },
};

static const std::unordered_map<int32_t, const char*> notificationPosition = {
    { 0, "Top Left" }, { 1, "Top Right" }, { 2, "Bottom Left" }, { 3, "Bottom Right" }, { 4, "Hidden" },
};

void PaperboatMenu::AddMenuSettings() {
    // Add Settings Menu
    AddMenuEntry("Settings", CVAR_SETTING("Menu.SettingsSidebarSection"));
    AddSidebarEntry("Settings", "General", 2);
    WidgetPath path = { "Settings", "General", SECTION_COLUMN_1 };

    // Settings > General
    AddWidget(path, "Menu Settings", WIDGET_SEPARATOR_TEXT);
    AddWidget(path, "Menu Theme", WIDGET_CVAR_COMBOBOX)
        .CVar(CVAR_SETTING("Menu.Theme"))
        .RaceDisable(false)
        .Options(
            ComboboxOptions()
                .Tooltip("Changes the Theme of the Menu Widgets.")
                .ComboMap(menuThemeOptions)
                .DefaultIndex(Colors::LightBlue)
        );
#if not defined(__SWITCH__) and not defined(__WIIU__)
    AddWidget(path, "Menu Controller Navigation", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR_IMGUI_CONTROLLER_NAV)
        .RaceDisable(false)
        .Options(
            CheckboxOptions().Tooltip(
                "Allows controller navigation of the port menu (Settings, "
                "Enhancements,...)\nCAUTION: "
                "This will disable game inputs while the menu is visible.\n\nD-pad "
                "to move between "
                "items, A to select, B to move up in scope."
            )
        );
    AddWidget(path, "Menu Background Opacity", WIDGET_CVAR_SLIDER_FLOAT)
        .CVar(CVAR_SETTING("Menu.BackgroundOpacity"))
        .RaceDisable(false)
        .Options(
            FloatSliderOptions().DefaultValue(0.85f).IsPercentage().Tooltip(
                "Sets the opacity of the background of the port menu."
            )
        );

    AddWidget(path, "General Settings", WIDGET_SEPARATOR_TEXT);
    AddWidget(path, "Cursor Always Visible", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR_SETTING("CursorVisibility"))
        .RaceDisable(false)
        .Callback([](WidgetInfo& info) {
            Ship::Context::GetRawInstance()->GetWindow()->SetForceCursorVisibility(
                CVarGetInteger(CVAR_SETTING("CursorVisibility"), 0)
            );
        })
        .Options(CheckboxOptions().Tooltip("Makes the cursor always visible, even in full screen."));
#endif
    AddWidget(path, "Search In Sidebar", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR_SETTING("Menu.SidebarSearch"))
        .RaceDisable(false)
        .Callback([](WidgetInfo& info) {
            if (CVarGetInteger(CVAR_SETTING("Menu.SidebarSearch"), 0)) {
                mPaperboatMenu->InsertSidebarSearch();
            } else {
                mPaperboatMenu->RemoveSidebarSearch();
            }
        })
        .Options(
            CheckboxOptions().Tooltip(
                "Displays the Search menu as a sidebar entry in Settings instead of "
                "in the header."
            )
        );
    AddWidget(path, "Search Input Autofocus", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR_SETTING("Menu.SearchAutofocus"))
        .RaceDisable(false)
        .Options(
            CheckboxOptions().Tooltip(
                "Search input box gets autofocus when visible. Does not affect using "
                "other widgets."
            )
        );
    AddWidget(path, "Open App Files Folder", WIDGET_BUTTON)
        .RaceDisable(false)
        .Callback([](WidgetInfo& info) {
            std::string filesPath = Ship::Context::GetAppDirectoryPath();
            SDL_OpenURL(std::string("file:///" + std::filesystem::absolute(filesPath).string()).c_str());
        })
        .Options(ButtonOptions().Tooltip("Opens the folder that contains the save and mods folders, etc."));
    AddWidget(path, "EXPERIMENTAL", WIDGET_SEPARATOR_TEXT).Options(TextOptions().Color(Colors::Orange));
    AddWidget(path, "ImGui Menu Scaling", WIDGET_CVAR_COMBOBOX)
        .CVar(CVAR_SETTING("ImGuiScale"))
        .RaceDisable(false)
        .Options(
            ComboboxOptions()
                .ComboMap(imguiScaleOptions)
                .Tooltip("Changes the scaling of the ImGui menu elements.")
                .DefaultIndex(1)
                .ComponentAlignment(ComponentAlignments::Right)
                .LabelPosition(LabelPositions::Far)
        )
        .Callback([](WidgetInfo& info) { GameEngine::Instance->ScaleImGui(); });

    // Settings > Audio
    path.sidebarName = "Audio";
    path.column = SECTION_COLUMN_1;
    AddSidebarEntry("Settings", "Audio", 3);

    AddWidget(path, "Master Volume: %d %%", WIDGET_CVAR_SLIDER_INT)
        .CVar(CVAR_SETTING("Volume.Master"))
        .RaceDisable(false)
        .Options(
            IntSliderOptions().Min(0).Max(100).DefaultValue(100).ShowButtons(true).Format("").Tooltip(
                "Scales the final audio output."
            )
        );
    AddWidget(path, "Main Music Volume: %d %%", WIDGET_CVAR_SLIDER_INT)
        .CVar(CVAR_SETTING("Volume.MainMusic"))
        .RaceDisable(false)
        .Options(
            IntSliderOptions().Min(0).Max(100).DefaultValue(100).ShowButtons(true).Format("").Tooltip(
                "Volume of background music."
            )
        );
    AddWidget(path, "Environment Volume: %d %%", WIDGET_CVAR_SLIDER_INT)
        .CVar(CVAR_SETTING("Volume.Environment"))
        .RaceDisable(false)
        .Options(
            IntSliderOptions().Min(0).Max(100).DefaultValue(100).ShowButtons(true).Format("").Tooltip(
                "Volume of ambient environment tracks."
            )
        );
    AddWidget(path, "Sound Effects Volume: %d %%", WIDGET_CVAR_SLIDER_INT)
        .CVar(CVAR_SETTING("Volume.SFX"))
        .RaceDisable(false)
        .Options(
            IntSliderOptions().Min(0).Max(100).DefaultValue(100).ShowButtons(true).Format("").Tooltip(
                "Volume of sound effects."
            )
        );
    AddWidget(path, "Audio API (Needs reload)", WIDGET_AUDIO_BACKEND).RaceDisable(false);

    // Settings > Controls
    path.sidebarName = "Controls";
    path.column = SECTION_COLUMN_1;
    AddSidebarEntry("Settings", "Controls", 1);
    AddWidget(path, "Clear Devices", WIDGET_BUTTON)
        .Callback([](WidgetInfo& info) {
            PaperboatGui::mModalWindow->RegisterPopup(
                "Clear Config",
                "This will completely erase the controls config, including "
                "registered devices.\nContinue?",
                "Clear", "Cancel",
                []() {
                    Ship::Context::GetRawInstance()->GetConsoleVariables()->ClearBlock(
                        CVAR_PREFIX_SETTING ".Controllers"
                    );
                    uint8_t bits = 0;
                    Ship::Context::GetRawInstance()->GetControlDeck()->Init(&bits);
                },
                nullptr
            );
        })
        .Options(ButtonOptions().Size(Sizes::Inline));
    AddWidget(path, "Controller Bindings", WIDGET_SEPARATOR_TEXT);
    AddWidget(path, "Popout Bindings Window", WIDGET_WINDOW_BUTTON)
        .CVar(CVAR_WINDOW("ControllerConfiguration"))
        .RaceDisable(false)
        .WindowName("Configure Controller")
        .HideInSearch(true)
        .Options(WindowButtonOptions().Tooltip("Enables the separate Bindings Window."));

    AddWidget(path, "Touch Controls", WIDGET_SEPARATOR_TEXT);
    AddWidget(path, "Enable Touch Controls", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR_TOUCH("Enabled"))
        .RaceDisable(false)
        .Options(
            CheckboxOptions().Tooltip(
                "Shows an on-screen virtual controller for touch screens.\nOn "
                "desktop the mouse can drive it for testing."
            )
        );
    AddWidget(path, "Touch Controls Scale", WIDGET_CVAR_SLIDER_FLOAT)
        .CVar(CVAR_TOUCH("Scale"))
        .RaceDisable(false)
        .Options(
            FloatSliderOptions().Min(0.5f).Max(2.0f).DefaultValue(1.0f).Tooltip(
                "Size of the on-screen buttons and stick."
            )
        );
    AddWidget(path, "Touch Controls Opacity", WIDGET_CVAR_SLIDER_FLOAT)
        .CVar(CVAR_TOUCH("Opacity"))
        .RaceDisable(false)
        .Options(
            FloatSliderOptions().Min(0.1f).Max(1.0f).DefaultValue(0.8f).IsPercentage().Tooltip(
                "Opacity of the on-screen controls."
            )
        );
    AddWidget(path, "Edit Touch Layout", WIDGET_BUTTON)
        .Options(
            ButtonOptions().Tooltip(
                "Closes the menu and lets you drag the on-screen controls to new "
                "positions.\nTap Done to save or Reset to restore the default "
                "layout."
            )
        )
        .Callback([](WidgetInfo& info) {
            CVarSetInteger(CVAR_TOUCH("Enabled"), 1);
            CVarSetInteger(CVAR_TOUCH("EditMode"), 1);
            Ship::Context::GetRawInstance()->GetWindow()->GetGui()->GetMenu()->Hide();
        });

    path.column = SECTION_COLUMN_2;
    AddWidget(path, "Additional Control Settings", WIDGET_SEPARATOR_TEXT);
    AddWidget(path, "D-Pad as Left Stick", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR_SETTING("Controls.DPadAsLeftStick"))
        .Options(
            CheckboxOptions().Tooltip(
                "Makes the d-pad move Mario like the left stick does. The game only "
                "walks from the stick, so a handheld d-pad does nothing without it."
            )
        );

    // Settings > Graphics
    static int32_t maxFps = 360;
    const char* tooltip = "Uses Matrix Interpolation to create extra frames, "
                          "resulting in smoother graphics. This is "
                          "purely visual and does not impact game logic, "
                          "execution of glitches etc.\n\nA higher target "
                          "FPS than your monitor's refresh rate will waste "
                          "resources, and might give a worse result.";
    path.sidebarName = "Graphics";
    path.column = SECTION_COLUMN_1;
    AddSidebarEntry("Settings", "Graphics", 2);
    AddWidget(path, "Graphics Options", WIDGET_SEPARATOR_TEXT);
    AddWidget(path, "Toggle Fullscreen", WIDGET_BUTTON)
        .RaceDisable(false)
        .Callback([](WidgetInfo& info) { Ship::Context::GetRawInstance()->GetWindow()->ToggleFullscreen(); })
        .Options(ButtonOptions().Tooltip("Toggles Fullscreen On/Off."));
    AddWidget(path, "Internal Resolution", WIDGET_CVAR_SLIDER_FLOAT)
        .CVar(CVAR_INTERNAL_RESOLUTION)
        .RaceDisable(false)
        .Callback([](WidgetInfo& info) {
            Ship::Context::GetRawInstance()->GetWindow()->SetResolutionMultiplier(
                CVarGetFloat(CVAR_INTERNAL_RESOLUTION, 1)
            );
        })
        .PreFunc([](WidgetInfo& info) {
            if (mPaperboatMenu->disabledMap.at(DISABLE_FOR_ADVANCED_RESOLUTION_ON).active
                && mPaperboatMenu->disabledMap.at(DISABLE_FOR_VERTICAL_RES_TOGGLE_ON).active)
            {
                info.activeDisables.push_back(DISABLE_FOR_ADVANCED_RESOLUTION_ON);
                info.activeDisables.push_back(DISABLE_FOR_VERTICAL_RES_TOGGLE_ON);
            } else if (mPaperboatMenu->disabledMap.at(DISABLE_FOR_LOW_RES_MODE_ON).active) {
                info.activeDisables.push_back(DISABLE_FOR_LOW_RES_MODE_ON);
            }
        })
        .Options(
            FloatSliderOptions()
                .Tooltip(
                    "Multiplies your output resolution by the value "
                    "inputted, as a more intensive but effective "
                    "form of anti-aliasing."
                )
                .ShowButtons(false)
                .IsPercentage()
                .Min(0.5f)
                .Max(2.0f)
        );
#ifndef __WIIU__
    AddWidget(path, "Anti-aliasing (MSAA)", WIDGET_CVAR_SLIDER_INT)
        .CVar(CVAR_MSAA_VALUE)
        .RaceDisable(false)
        .Callback([](WidgetInfo& info) {
            Ship::Context::GetRawInstance()->GetWindow()->SetMsaaLevel(CVarGetInteger(CVAR_MSAA_VALUE, 1));
        })
        .Options(
            IntSliderOptions()
                .Tooltip(
                    "Activates MSAA (multi-sample anti-aliasing) from "
                    "2x up to 8x, to smooth the edges of "
                    "rendered geometry.\n"
                    "Higher sample count will result in smoother edges "
                    "on models, but may reduce performance."
                )
                .Min(1)
                .Max(8)
                .DefaultValue(1)
        );
#endif
    auto fps = CVarGetInteger(CVAR_SETTING("InterpolationFPS"), 30);
    const char* fpsFormat = fps == 30 ? "Original (%d)" : "%d";
    AddWidget(path, "Current FPS", WIDGET_CVAR_SLIDER_INT)
        .CVar(CVAR_SETTING("InterpolationFPS"))
        .RaceDisable(false)
        .Callback([](WidgetInfo& info) {
            auto options = std::static_pointer_cast<IntSliderOptions>(info.options);
            int32_t defaultValue = options->defaultValue;
            if (CVarGetInteger(info.cVar, defaultValue) == defaultValue) {
                options->format = "Original (%d)";
            } else {
                options->format = "%d";
            }
        })
        .PreFunc([](WidgetInfo& info) {
            if (mPaperboatMenu->disabledMap.at(DISABLE_FOR_MATCH_REFRESH_RATE_ON).active)
                info.activeDisables.push_back(DISABLE_FOR_MATCH_REFRESH_RATE_ON);
        })
        .Options(IntSliderOptions().Tooltip(tooltip).Min(30).Max(maxFps).DefaultValue(30).Format(fpsFormat));
    AddWidget(path, "Match Refresh Rate", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR_SETTING("MatchRefreshRate"))
        .RaceDisable(false)
        .Options(CheckboxOptions().Tooltip("Matches interpolation value to the refresh rate of your display."));
    AddWidget(path, "Renderer API (Needs reload)", WIDGET_VIDEO_BACKEND).RaceDisable(false);
    AddWidget(path, "Enable Vsync", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR_VSYNC_ENABLED)
        .RaceDisable(false)
        .PreFunc([](WidgetInfo& info) { info.isHidden = mPaperboatMenu->disabledMap.at(DISABLE_FOR_NO_VSYNC).active; })
        .Options(
            CheckboxOptions()
                .Tooltip(
                    "Removes tearing, but clamps your max FPS to your "
                    "displays refresh rate."
                )
                .DefaultValue(true)
        );
    AddWidget(path, "Windowed Fullscreen", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR_SDL_WINDOWED_FULLSCREEN)
        .RaceDisable(false)
        .PreFunc([](WidgetInfo& info) {
            info.isHidden = mPaperboatMenu->disabledMap.at(DISABLE_FOR_NO_WINDOWED_FULLSCREEN).active;
        })
        .Options(CheckboxOptions().Tooltip("Enables Windowed Fullscreen Mode."));
    AddWidget(path, "Allow multi-windows", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR_ENABLE_MULTI_VIEWPORTS)
        .RaceDisable(false)
        .PreFunc([](WidgetInfo& info) {
            info.isHidden = mPaperboatMenu->disabledMap.at(DISABLE_FOR_NO_MULTI_VIEWPORT).active;
        })
        .Options(
            CheckboxOptions()
                .Tooltip(
                    "Allows multiple windows to be opened at once. "
                    "Requires a reload to take effect."
                )
                .DefaultValue(true)
        );
    AddWidget(path, "Texture Filter (Needs reload)", WIDGET_CVAR_COMBOBOX)
        .CVar(CVAR_TEXTURE_FILTER)
        .RaceDisable(false)
        .Options(ComboboxOptions().Tooltip("Sets the applied Texture Filtering.").ComboMap(textureFilteringMap));

    path.column = SECTION_COLUMN_2;
    AddWidget(path, "Advanced Graphics Options", WIDGET_SEPARATOR_TEXT);
    // Settings > Input Viewer
    path.sidebarName = "Input Viewer";
    path.column = SECTION_COLUMN_1;
    AddSidebarEntry("Settings", path.sidebarName, 1);
    AddWidget(path, "Input Viewer", WIDGET_SEPARATOR_TEXT);
    AddWidget(path, "Toggle Input Viewer", WIDGET_WINDOW_BUTTON)
        .CVar(CVAR_WINDOW("InputViewer"))
        .RaceDisable(false)
        .WindowName("Input Viewer")
        .HideInSearch(true)
        .Options(WindowButtonOptions().Tooltip("Toggles the Input Viewer.").EmbedWindow(false));

    AddWidget(path, "Input Viewer Settings", WIDGET_SEPARATOR_TEXT);
    AddWidget(path, "Popout Input Viewer Settings", WIDGET_WINDOW_BUTTON)
        .CVar(CVAR_WINDOW("InputViewerSettings"))
        .RaceDisable(false)
        .WindowName("Input Viewer Settings")
        .HideInSearch(true)
        .Options(WindowButtonOptions().Tooltip("Enables the separate Input Viewer Settings Window."));

    // Notifications
    path.sidebarName = "Notifications";
    path.column = SECTION_COLUMN_1;
    AddSidebarEntry("Settings", path.sidebarName, 2);
    AddWidget(path, "Position", WIDGET_CVAR_COMBOBOX)
        .CVar(CVAR_SETTING("Notifications.Position"))
        .RaceDisable(false)
        .Options(
            ComboboxOptions()
                .Tooltip("Which corner of the screen notifications appear in.")
                .ComboMap(notificationPosition)
                .DefaultIndex(3)
        );
    AddWidget(path, "Duration (seconds):", WIDGET_CVAR_SLIDER_FLOAT)
        .CVar(CVAR_SETTING("Notifications.Duration"))
        .RaceDisable(false)
        .Options(
            FloatSliderOptions()
                .Tooltip("How long notifications are displayed for.")
                .Format("%.1f")
                .Step(0.1f)
                .Min(3.0f)
                .Max(30.0f)
                .DefaultValue(10.0f)
        );
    AddWidget(path, "Background Opacity", WIDGET_CVAR_SLIDER_FLOAT)
        .CVar(CVAR_SETTING("Notifications.BgOpacity"))
        .RaceDisable(false)
        .Options(
            FloatSliderOptions()
                .Tooltip("How opaque the background of notifications is.")
                .DefaultValue(0.5f)
                .IsPercentage()
        );
    AddWidget(path, "Size:", WIDGET_CVAR_SLIDER_FLOAT)
        .CVar(CVAR_SETTING("Notifications.Size"))
        .RaceDisable(false)
        .Options(
            FloatSliderOptions()
                .Tooltip("How large notifications are.")
                .Format("%.1f")
                .Step(0.1f)
                .Min(1.0f)
                .Max(5.0f)
                .DefaultValue(1.8f)
        );
    AddWidget(path, "Test Notification", WIDGET_BUTTON)
        .RaceDisable(false)
        .Callback([](WidgetInfo& info) {
            Notification::Emit(
                {
                    .prefix = "Welcome",
                    .message = "to",
                    .suffix = "Paperboat.",
                }
            );
        })
        .Options(ButtonOptions().Tooltip("Displays a test notification."));
    AddWidget(path, "Test Achievement Notification", WIDGET_BUTTON)
        .RaceDisable(false)
        .Callback([](WidgetInfo& info) { Notification::EmitAchievement(nullptr, "Harbour Mastery", 0); })
        .Options(ButtonOptions().Tooltip("Displays a test notification."));

    // Mod Menu
    path.sidebarName = "Mod Menu";
    path.column = SECTION_COLUMN_1;
    AddSidebarEntry("Settings", path.sidebarName, 1);
    AddWidget(path, "Popout Mod Menu Window", WIDGET_WINDOW_BUTTON)
        .CVar(CVAR_WINDOW("ModMenu"))
        .RaceDisable(false)
        .WindowName("Mod Menu")
        .HideInSearch(true)
        .Options(WindowButtonOptions().Tooltip("Enables the separate Mod Menu Window."));
}

} // namespace PaperboatGui
