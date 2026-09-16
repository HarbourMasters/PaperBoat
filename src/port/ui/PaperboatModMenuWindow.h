#pragma once

#include <string>

#include <libultraship/libultraship.h>

#ifdef __cplusplus
class PaperboatModMenuWindow : public Ship::GuiWindow {
  public:
    using GuiWindow::GuiWindow;

    void InitElement() override;
    void DrawElement() override;
    void UpdateElement() override {};
};
void UpdateModFiles(bool init = false, bool reset = false);
void EnableMod(std::string file);
void DisableMod(std::string file);
#endif
