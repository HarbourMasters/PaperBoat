#pragma once
#include <libultraship/libultraship.h>

typedef enum {
    VALUE_TYPE_MAP,
    VALUE_TYPE_POSITION,
} ValueViewerTypes;

class ValueViewerWindow : public Ship::GuiWindow {
public:
    using Ship::GuiWindow::GuiWindow;

    void OnInit(const nlohmann::json& initArgs = nlohmann::json::object()) override;
    void DrawElement() override{};
    void Draw() override;
    void UpdateElement() override{};
};

class ValueViewerSettingsWindow : public Ship::GuiWindow {
public:
    using Ship::GuiWindow::GuiWindow;

    void OnInit(const nlohmann::json& initArgs = nlohmann::json::object()) override {
        Ship::GuiWindow::OnInit(initArgs);
    };
    void DrawElement() override;
    void UpdateElement() override{};
};
