#pragma once

#include <libultraship/libultraship.h>

// Auto-generated UI for shader-pack tweakables: post-pass enable toggles plus
// one slider/checkbox per @setting(...) declaration discovered while
// compiling custom shaders. Edits persist to CVars and recompile shaders.
class ShaderSettingsWindow final : public Ship::GuiWindow {
  public:
    using GuiWindow::GuiWindow;
    ~ShaderSettingsWindow() override = default;

    void InitElement() override {};
    void DrawElement() override;
    void UpdateElement() override {};
};
