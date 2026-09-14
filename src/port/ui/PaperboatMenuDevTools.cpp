#include "PaperboatMenu.h"

namespace PaperboatGui {

extern std::shared_ptr<PaperboatMenu> mPaperboatMenu;
using namespace UIWidgets;

static const std::unordered_map<int32_t, const char*> logLevels = {
    { DEBUG_LOG_TRACE, "Trace" }, { DEBUG_LOG_DEBUG, "Debug" }, { DEBUG_LOG_INFO, "Info" },
    { DEBUG_LOG_WARN, "Warn" },   { DEBUG_LOG_ERROR, "Error" }, { DEBUG_LOG_CRITICAL, "Critical" },
    { DEBUG_LOG_OFF, "Off" },
};

#ifdef _DEBUG
DebugLogOption defaultLogLevel = DEBUG_LOG_DEBUG;
#else
DebugLogOption defaultLogLevel = DEBUG_LOG_INFO;
#endif

void PaperboatMenu::AddMenuDevTools() {
    // Add Dev Tools Menu
    AddMenuEntry("Dev Tools", CVAR_SETTING("Menu.DevToolsSidebarSection"));

    // General
    AddSidebarEntry("Dev Tools", "General", 3);
    WidgetPath path = { "Dev Tools", "General", SECTION_COLUMN_1 };

    AddWidget(path, "Popout Menu", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR_SETTING("Menu.Popout"))
        .Options(CheckboxOptions().Tooltip("Changes the menu display from overlay to windowed."));
    AddWidget(path, "Log Level", WIDGET_CVAR_COMBOBOX)
        .CVar(CVAR_DEVELOPER_TOOLS("LogLevel"))
        .Options(
            ComboboxOptions()
                .Tooltip(
                    "The log level determines which messages are "
                    "printed to the console."
                    " This does not affect the log file output"
                )
                .ComboMap(logLevels)
                .DefaultIndex(defaultLogLevel)
        )
        .Callback([](WidgetInfo& info) {
            spdlog::set_level(
                (spdlog::level::level_enum) CVarGetInteger(CVAR_DEVELOPER_TOOLS("LogLevel"), defaultLogLevel)
            );
        });
    AddWidget(path, "DX Debug Menu", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR_DEVELOPER_TOOLS("DebugMenu"))
        .Options(
            CheckboxOptions().Tooltip(
                "Lets D-Pad Left and D-Pad Right open the DX debug menus. Leave this "
                "off to keep the d-pad free for normal play."
            )
        );

#ifdef USE_GBI_TRACE
    AddWidget(path, "GFX Trace Mode", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR_DEVELOPER_TOOLS("GFXTrace"))
        .Options(
            CheckboxOptions().Tooltip(
                "Enables the Gfx trace mode, which will output information about the "
                "Gfx commands being run."
            )
        );
#endif

    // Stats
    path.sidebarName = "Stats";
    AddSidebarEntry("Dev Tools", path.sidebarName, 1);
    AddWidget(path, "Popout Stats", WIDGET_WINDOW_BUTTON)
        .CVar(CVAR_WINDOW("Stats"))
        .WindowName("Stats")
        .HideInSearch(true)
        .Options(
            WindowButtonOptions().Tooltip(
                "Shows the stats window, with frame rate, frame times and the "
                "platform you are playing on."
            )
        );

    // Console
    path.sidebarName = "Console";
    AddSidebarEntry("Dev Tools", path.sidebarName, 1);
    AddWidget(path, "Popout Console", WIDGET_WINDOW_BUTTON)
        .CVar(CVAR_WINDOW("DevConsole"))
        .WindowName("Console##Dev")
        .HideInSearch(true)
        .Options(WindowButtonOptions().Tooltip("Enables the separate Console Window."));

    path.sidebarName = "Event Debugger";
    AddSidebarEntry("Dev Tools", path.sidebarName, 1);
    AddWidget(path, "Popout Event Debugger", WIDGET_WINDOW_BUTTON)
        .CVar(CVAR_WINDOW("EventDebugger"))
        .WindowName("Event Debugger")
        .HideInSearch(true)
        .Options(WindowButtonOptions().Tooltip("Enables the separate Event Debugger Window."));

    path.sidebarName = "Value Viewer";
    AddSidebarEntry("Dev Tools", path.sidebarName, 1);
    AddWidget(path, "Popout Value Viewer Settings", WIDGET_WINDOW_BUTTON)
        .CVar(CVAR_WINDOW("ValueViewerSettings"))
        .WindowName("Value Viewer Settings")
        .HideInSearch(true);

    path.sidebarName = "Save Editor";
    AddSidebarEntry("Dev Tools", path.sidebarName, 1);
    AddWidget(path, "Popout Save Editor", WIDGET_WINDOW_BUTTON)
        .CVar(CVAR_WINDOW("SaveEditor"))
        .WindowName("Save Editor")
        .HideInSearch(true);
}

} // namespace PaperboatGui
