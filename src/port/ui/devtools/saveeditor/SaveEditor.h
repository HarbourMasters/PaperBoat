#pragma once
#include <libultraship/libultraship.h>

typedef struct {
    const char* name;
    ImTextureID textureId;
} TextureData;

class SaveEditorWindow : public Ship::GuiWindow {
public:
    using Ship::GuiWindow::GuiWindow;

    void InitElement() override;
    void DrawElement() override;
    void Draw() override;
    void UpdateElement() override{};
};
