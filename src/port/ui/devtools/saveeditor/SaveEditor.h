#pragma once
#include <libultraship/libultraship.h>

typedef struct {
    const char* name;
    ImTextureID textureId;
} TextureData;

class SaveEditorWindow : public Ship::GuiWindow {
public:
    using Ship::GuiWindow::GuiWindow;

    void OnInit(const nlohmann::json& initArgs = nlohmann::json::object()) override;
    void DrawElement() override;
    void Draw() override;
    void UpdateElement() override{};
};
