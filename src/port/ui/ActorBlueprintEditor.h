#pragma once
#include <libultraship/libultraship.h>

class ActorBlueprintEditorWindow : public Ship::GuiWindow {
public:
    using Ship::GuiWindow::GuiWindow;

    void InitElement() override { };
    void DrawElement() override;
    void Draw() override;
    void UpdateElement() override { };
};
