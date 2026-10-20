#pragma once

#include <libultraship/libultraship.h>
#include "UIWidgets.hpp"
#include "Menu.h"
#include <fast/backends/gfx_rendering_api.h>
#include "port/ui/cvar_prefixes.h"
#include "port/ui/enhancementTypes.h"

namespace PaperboatGui {
class PaperboatMenu : public Ship::Menu {
  public:
    PaperboatMenu(const std::string& consoleVariable, const std::string& name);

    void InitElement() override;
    void DrawElement() override;
    void UpdateElement() override;
    void Draw() override;

    void AddSidebarEntry(std::string sectionName, std::string sidbarName, uint32_t columnCount);
    WidgetInfo& AddWidget(WidgetPath& pathInfo, std::string widgetName, WidgetType widgetType);
    void AddSection(std::string sectionName, const char* sidebarCvar);
    void RemoveSidebarEntry(std::string sectionName, std::string sidebarName);
    void RemoveWidget(const WidgetPath& pathInfo, const std::string& widgetName);
    void AddMenuSettings();
    void AddMenuEnhancements();
    void AddMenuShaderSettings();
    void AddMenuDevTools();

  private:
    char mGitCommitHashTruncated[8];
    bool mIsTaggedVersion;
};
} // namespace PaperboatGui
