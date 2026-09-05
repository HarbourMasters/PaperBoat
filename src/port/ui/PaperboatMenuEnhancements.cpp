#include "PaperboatMenu.h"

namespace PaperboatGui {

extern std::shared_ptr<PaperboatMenu> mPaperboatMenu;

using namespace UIWidgets;

void PaperboatMenu::AddMenuEnhancements() {
  // Add Enhancements Menu
  AddMenuEntry("Enhancements", CVAR_SETTING("Menu.EnhancementsSidebarSection"));

  // Enhancements > Cheats
  WidgetPath path = { "Enhancements", "Cheats", SECTION_COLUMN_1 };
  AddSidebarEntry("Enhancements", path.sidebarName, 1);
  path.column = SECTION_COLUMN_1;

  AddWidget(path, "Infinite Health", WIDGET_CVAR_CHECKBOX)
      .CVar(CVAR_CHEAT("InfiniteHealth"))
      .Options(CheckboxOptions().Tooltip(
          "Mario's HP won't decrease during battle."));

  AddWidget(path, "Infinite Flower Points", WIDGET_CVAR_CHECKBOX)
      .CVar(CVAR_CHEAT("InfiniteFlowerPoints"))
      .Options(CheckboxOptions().Tooltip(
          "Mario's FP won't decrease during battle."));

  AddWidget(path, "No Badge Cost", WIDGET_CVAR_CHECKBOX)
      .CVar(CVAR_CHEAT("NoBPCost"))
      .Options(
          CheckboxOptions().Tooltip("Equip any badge regardless of BP cost."));

  AddWidget(path, "Max Star Power", WIDGET_CVAR_CHECKBOX)
      .CVar(CVAR_CHEAT("MaxStarPower"))
      .Options(CheckboxOptions().Tooltip(
          "Star Power stays full and won't decrease."));

  // Enhancements > Gameplay
  path = { "Enhancements", "Gameplay", SECTION_COLUMN_1 };
  AddSidebarEntry("Enhancements", path.sidebarName, 1);
  path.column = SECTION_COLUMN_1;

  // Enhancements > Graphics
  path = {"Enhancements", "Graphics", SECTION_COLUMN_1};
  AddSidebarEntry("Enhancements", "Graphics", 1);

  AddWidget(path, "Mods", WIDGET_SEPARATOR_TEXT);
  AddWidget(path, "Use Alternate Assets", WIDGET_CVAR_CHECKBOX)
      .CVar("gEnhancements.Mods.AlternateAssets")
      .Options(CheckboxOptions().Tooltip(
          "Toggle between standard assets and alternate assets. Usually mods "
          "will indicate if "
          "this setting has to be used or not."));

}

} // namespace PaperboatGui
