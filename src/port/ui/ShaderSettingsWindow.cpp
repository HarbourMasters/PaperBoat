#include "ShaderSettingsWindow.h"

#include "fast/Fast3dWindow.h"
#include "fast/interpreter.h"
#include <imgui.h>

void ShaderSettingsWindow::DrawElement() {
    auto wnd = std::dynamic_pointer_cast<Fast::Fast3dWindow>(Ship::Context::GetInstance()->GetWindow());
    if (wnd == nullptr) {
        return;
    }
    auto interp = wnd->GetInterpreterWeak().lock();
    if (interp == nullptr) {
        return;
    }

    // ---- Post-processing passes ----
    auto passes = interp->GetPostPasses();
    if (!passes.empty()) {
        ImGui::SeparatorText("Post-processing passes");
        for (const auto& pass : passes) {
            bool enabled = pass.enabled;
            if (ImGui::Checkbox((pass.path + "##pass" + std::to_string(pass.id)).c_str(), &enabled)) {
                interp->SetPostPassEnabled(pass.id, enabled);
            }
        }
    }

    // ---- Per-shader @setting tweakables ----
    const auto& registry = interp->GetShaderSettingsRegistry();
    if (registry.empty()) {
        ImGui::TextDisabled("No tweakable shaders compiled yet.");
        ImGui::TextDisabled("Settings appear once a shader using @setting() is used.");
        return;
    }

    for (const auto& [shaderId, entry] : registry) {
        if (entry.decls.empty()) {
            continue;
        }
        ImGui::SeparatorText(entry.path.empty() ? "(unnamed shader)" : entry.path.c_str());
        ImGui::PushID((int)shaderId);
        for (const auto& decl : entry.decls) {
            float value = entry.values.at(decl.var);
            const char* label = decl.name.empty() ? decl.var.c_str() : decl.name.c_str();
            if (decl.type == "toggle") {
                bool on = value != 0.0f;
                if (ImGui::Checkbox(label, &on)) {
                    interp->SetShaderSettingValue(shaderId, decl.var, on ? 1.0f : 0.0f);
                }
            } else {
                // Track the drag in the registry so the widget doesn't snap
                // back (the local re-reads the registry every frame); persist
                // and recompile only once, on release.
                if (ImGui::SliderFloat(label, &value, decl.min, decl.max)) {
                    interp->UpdateShaderSettingValue(shaderId, decl.var, value);
                }
                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    interp->SetShaderSettingValue(shaderId, decl.var, value);
                }
            }
        }
        ImGui::PopID();
    }
}
