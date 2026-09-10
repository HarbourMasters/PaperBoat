#pragma once

#include <libultraship/libultraship.h>

class EventDebuggerWindow final : public Ship::GuiWindow {
  public:
    using GuiWindow::GuiWindow;

    void OnInit(const nlohmann::json& initArgs = nlohmann::json::object()) override;
    void DrawElement() override;
    void UpdateElement() override{};
};