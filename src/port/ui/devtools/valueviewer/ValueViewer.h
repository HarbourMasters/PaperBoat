#pragma once
#include <libultraship/libultraship.h>

typedef enum {
    VALUE_TYPE_MAP,
    VALUE_TYPE_POSITION,
} ValueViewerTypes;

class ValueViewerWindow : public Ship::GuiWindow {
public:
    using Ship::GuiWindow::GuiWindow;

    void InitElement() override;
    void DrawElement() override{};
    void Draw() override;
    void UpdateElement() override{};
};

class ValueViewerSettingsWindow : public Ship::GuiWindow {
public:
    using Ship::GuiWindow::GuiWindow;

    void InitElement() override {
    };
    void DrawElement() override;
    void UpdateElement() override{};
};
