#include "PaperboatMenu.h"

#define CVAR_INT_SHIP_INIT(cvar, val)                                          \
  CVarSetInteger(cvar, val);                                                   \
  ShipInit::Init(cvar);

static std::string comboboxTooltip = "";

namespace PaperboatGui {

extern std::shared_ptr<PaperboatMenu> mPaperboatMenu;

static std::unordered_map<int32_t, const char *> hudAspects = {
    {0, "Expand"},
    {1, "Custom"},
    {2, "Original (4:3)"},
    {3, "Widescreen (16:9)"},
    {4, "Nintendo 3DS (5:3)"},
    {5, "16:10 (8:5)"},
    {6, "Ultrawide (21:9)"},
};

using namespace UIWidgets;

void PaperboatMenu::AddMenuEnhancements() {
  // Add Enhancements Menu
  AddMenuEntry("Enhancements", CVAR_SETTING("Menu.EnhancementsSidebarSection"));

  // Enhancements > Graphics
  WidgetPath path = {"Enhancements", "Graphics", SECTION_COLUMN_1};
  AddSidebarEntry("Enhancements", "Graphics", 2);

  AddWidget(path, "Mods", WIDGET_SEPARATOR_TEXT);
  AddWidget(path, "Use Alternate Assets", WIDGET_CVAR_CHECKBOX)
      .CVar("gEnhancements.Mods.AlternateAssets")
      .Options(CheckboxOptions().Tooltip(
          "Toggle between standard assets and alternate assets. Usually mods "
          "will indicate if "
          "this setting has to be used or not."));

  AddWidget(path, "Game", WIDGET_SEPARATOR_TEXT);

  AddWidget(path, "HUD Aspect Ratio", WIDGET_CVAR_COMBOBOX)
      .CVar("gHUDAspectRatio.Selection")
      .RaceDisable(false)
      .Options(ComboboxOptions()
                   .ComboMap(hudAspects)
                   .Tooltip("Changes the aspect ratio of the HUD elements.")
                   .DefaultIndex(0)
                   .ComponentAlignment(ComponentAlignments::Right)
                   .LabelPosition(LabelPositions::Far))
      .Callback([](WidgetInfo &info) {
        CVarSetInteger("gHUDAspectRatio.Enabled", 1);
        switch (CVarGetInteger("gHUDAspectRatio.Selection", 0)) {
        case 0:
          CVarSetInteger("gHUDAspectRatio.Enabled", 0);
          CVarSetInteger("gHUDAspectRatio.X", 0);
          CVarSetInteger("gHUDAspectRatio.Y", 0);
          break;
        case 1:
          if (CVarGetInteger("gHUDAspectRatio.X", 0) <= 0) {
            CVarSetInteger("gHUDAspectRatio.X", 1);
          }
          if (CVarGetInteger("gHUDAspectRatio.Y", 0) <= 0) {
            CVarSetInteger("gHUDAspectRatio.Y", 1);
          }
          break;
        case 2:
          CVarSetInteger("gHUDAspectRatio.X", 4);
          CVarSetInteger("gHUDAspectRatio.Y", 3);
          break;
        case 3:
          CVarSetInteger("gHUDAspectRatio.X", 16);
          CVarSetInteger("gHUDAspectRatio.Y", 9);
          break;
        case 4:
          CVarSetInteger("gHUDAspectRatio.X", 5);
          CVarSetInteger("gHUDAspectRatio.Y", 3);
          break;
        case 5:
          CVarSetInteger("gHUDAspectRatio.X", 8);
          CVarSetInteger("gHUDAspectRatio.Y", 5);
          break;
        case 6:
          CVarSetInteger("gHUDAspectRatio.X", 21);
          CVarSetInteger("gHUDAspectRatio.Y", 9);
          break;
        }
      });

  AddWidget(path, "Custom HUD Aspect Ratio X", WIDGET_CVAR_SLIDER_INT)
      .CVar("gHUDAspectRatio.X")
      .RaceDisable(false)
      .PreFunc([](WidgetInfo &info) {
        if (CVarGetInteger("gHUDAspectRatio.Selection", 0) != 1) {
          info.isHidden = true;
        } else {
          info.isHidden = false;
        }
      })
      .Options(IntSliderOptions()
                   .Min(1)
                   .Max(100)
                   .DefaultValue(16)
                   .ShowButtons(true)
                   .Format("%d"));
  AddWidget(path, "Custom HUD Aspect Ratio Y", WIDGET_CVAR_SLIDER_INT)
      .CVar("gHUDAspectRatio.Y")
      .RaceDisable(false)
      .PreFunc([](WidgetInfo &info) {
        if (CVarGetInteger("gHUDAspectRatio.Selection", 0) != 1) {
          info.isHidden = true;
        } else {
          info.isHidden = false;
        }
      })
      .Options(IntSliderOptions()
                   .Min(1)
                   .Max(100)
                   .DefaultValue(9)
                   .ShowButtons(true)
                   .Format("%d"));

  path = {"Enhancements", "Gameplay", SECTION_COLUMN_1};
  AddSidebarEntry("Enhancements", path.sidebarName, 1);
  path.column = SECTION_COLUMN_1;

  AddWidget(path, "Skip Intro", WIDGET_CVAR_CHECKBOX)
      .CVar(CVAR_ENHANCEMENT("NoIntro"))
      .RaceDisable(false)
      .Options(CheckboxOptions().Tooltip("Skip the intro sequence."));

  path = {"Enhancements", "Fixes", SECTION_COLUMN_1};
  AddSidebarEntry("Enhancements", path.sidebarName, 1);
  path.column = SECTION_COLUMN_1;

  path = {"Enhancements", "Cheats", SECTION_COLUMN_1};
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
}

} // namespace PaperboatGui
