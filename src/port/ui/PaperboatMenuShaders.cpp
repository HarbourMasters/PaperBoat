#include "PaperboatMenu.h"

#include <ship/window/gui/ShaderSettingsWindow.h>

namespace PaperboatGui {

using namespace UIWidgets;

void PaperboatMenu::AddMenuShaderSettings() {
  AddMenuEntry("Shaders", CVAR_SETTING("Menu.ShadersSidebarSection"));

  AddSidebarEntry("Shaders", "Shader Packs", 1);
  WidgetPath path = {"Shaders", "Shader Packs", SECTION_COLUMN_1};

  AddWidget(path, "Popout Shader Settings", WIDGET_WINDOW_BUTTON)
      .CVar(CVAR_WINDOW("ShaderSettings"))
      .WindowName("Shader Settings")
      .HideInSearch(true)
      .Options(WindowButtonOptions().Tooltip(
          "Enables the separate Shader Settings Window."));
}

} // namespace PaperboatGui
