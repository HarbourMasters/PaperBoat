#include "PaperboatGui.hpp"
#include <ship/window/gui/ShaderSettingsWindow.h>

#include <imgui.h>
#include <imgui_internal.h>
#include <spdlog/spdlog.h>

#ifdef __APPLE__
#include <fast/backends/gfx_metal.h>
#endif

#include "Notification.h"
#include "PaperboatInputEditorWindow.h"
#include "PaperboatModMenuWindow.h"
#include "TouchControls.h"
#include "port/ui/devtools/hooks/EventDebugger.h"
#include <ship/window/gui/ConsoleWindow.h>
#include "port/ui/devtools/valueviewer/ValueViewer.h"
#include "port/ui/devtools/saveeditor/SaveEditor.h"

namespace PaperboatGui {
// MARK: - Delegates
std::shared_ptr<Ship::GuiWindow> mInputEditorWindow;
std::shared_ptr<PaperboatMenu> mPaperboatMenu;
std::shared_ptr<Notification::Window> mNotificationWindow;
std::shared_ptr<InputViewer> mInputViewer;
std::shared_ptr<InputViewerSettingsWindow> mInputViewerSettings;
std::shared_ptr<Ship::ShaderSettingsWindow> mShaderSettingsWindow;
std::shared_ptr<PaperboatModalWindow> mModalWindow;
std::shared_ptr<Ship::GuiWindow> mConsoleWindow;
std::shared_ptr<EventDebuggerWindow> mEventDebuggerWindow;
std::shared_ptr<ValueViewerWindow> mValueViewerWindow;
std::shared_ptr<ValueViewerSettingsWindow> mValueViewerSettingsWindow;
std::shared_ptr<SaveEditorWindow> mSaveEditorWindow;
std::shared_ptr<PaperboatModMenuWindow> mModMenuWindow;
std::shared_ptr<TouchControlsOverlay> mTouchControlsOverlay;

UIWidgets::Colors GetMenuThemeColor() {
    return mPaperboatMenu->GetMenuThemeColor();
}

void SetupMenu() {
    auto gui = Ship::Context::GetRawInstance()->GetWindow()->GetGui();
    mPaperboatMenu = std::make_shared<PaperboatGui::PaperboatMenu>(CVAR_WINDOW("Menu"), "Port Menu");
    gui->SetMenu(mPaperboatMenu);

    mModalWindow = std::make_shared<PaperboatModalWindow>(CVAR_WINDOW("ModalWindow"), "Modal Window");
    gui->AddGuiWindow(mModalWindow);
    mModalWindow->Show();
}

void SetupGuiElements() {
    auto gui = Ship::Context::GetRawInstance()->GetWindow()->GetGui();

    auto& style = ImGui::GetStyle();
    style.FramePadding = ImVec2(4.0f, 6.0f);
    style.ItemSpacing = ImVec2(8.0f, 6.0f);
    style.Colors[ImGuiCol_MenuBarBg] = UIWidgets::ColorValues.at(UIWidgets::Colors::DarkGray);
    mConsoleWindow = gui->GetGuiWindow("Console");
    if (mConsoleWindow == nullptr) {
        SPDLOG_ERROR("Could not find console window");
    }

    mEventDebuggerWindow = std::make_shared<EventDebuggerWindow>(CVAR_WINDOW("EventDebugger"), "Event Debugger");
    gui->AddGuiWindow(mEventDebuggerWindow);

    mValueViewerWindow = std::make_shared<ValueViewerWindow>(CVAR_WINDOW("ValueViewer"), "Value Viewer");
    gui->AddGuiWindow(mValueViewerWindow);

    mValueViewerSettingsWindow =
        std::make_shared<ValueViewerSettingsWindow>(CVAR_WINDOW("ValueViewerSettings"), "Value Viewer Settings");
    gui->AddGuiWindow(mValueViewerSettingsWindow);

    mSaveEditorWindow = std::make_shared<SaveEditorWindow>(CVAR_WINDOW("SaveEditor"), "Save Editor");
    gui->AddGuiWindow(mSaveEditorWindow);

    mModMenuWindow = std::make_shared<PaperboatModMenuWindow>(CVAR_WINDOW("ModMenu"), "Mod Menu");
    gui->AddGuiWindow(mModMenuWindow);

    mInputEditorWindow =
        std::make_shared<PaperboatInputEditorWindow>(CVAR_WINDOW("ControllerConfiguration"), "Configure Controller");
    gui->AddGuiWindow(mInputEditorWindow);

    mNotificationWindow = std::make_shared<Notification::Window>(CVAR_WINDOW("Notifications"), "Notifications Window");
    gui->AddGuiWindow(mNotificationWindow);
    mNotificationWindow->Show();

    mInputViewer = std::make_shared<InputViewer>(CVAR_WINDOW("InputViewer"), "Input Viewer");
    gui->AddGuiWindow(mInputViewer);
    mInputViewerSettings = std::make_shared<InputViewerSettingsWindow>(
        CVAR_WINDOW("InputViewerSettings"), "Input Viewer Settings", ImVec2(500, 525)
    );
    gui->AddGuiWindow(mInputViewerSettings);

    mShaderSettingsWindow = std::make_shared<Ship::ShaderSettingsWindow>(
        CVAR_WINDOW("ShaderSettings"), "Shader Settings", ImVec2(420, 520)
    );
    gui->AddGuiWindow(mShaderSettingsWindow);

    // Registered everywhere; draws nothing unless the touch controls are on, so
    // the layout can be edited from a desktop build.
    mTouchControlsOverlay = std::make_shared<TouchControlsOverlay>(CVAR_WINDOW("TouchControls"), "##TouchControls");
    gui->AddGuiWindow(mTouchControlsOverlay);
    mTouchControlsOverlay->Show();
}

void Destroy() {
    auto gui = Ship::Context::GetRawInstance()->GetWindow()->GetGui();

    gui->RemoveAllGuiWindows();
    mPaperboatMenu = nullptr;
    mModalWindow = nullptr;
    mInputEditorWindow = nullptr;
    mNotificationWindow = nullptr;
    mInputViewer = nullptr;
    mShaderSettingsWindow = nullptr;
    mInputViewerSettings = nullptr;
    mConsoleWindow = nullptr;
    mValueViewerWindow = nullptr;
    mValueViewerSettingsWindow = nullptr;
    mSaveEditorWindow = nullptr;
    mModMenuWindow = nullptr;
    mTouchControlsOverlay = nullptr;
}

void RegisterPopup(
    std::string title,
    std::string message,
    std::string button1,
    std::string button2,
    std::function<void()> button1callback,
    std::function<void()> button2callback
) {
    mModalWindow->RegisterPopup(title, message, button1, button2, button1callback, button2callback);
}

size_t PopupsQueued() {
    return mModalWindow->PopupsQueued();
}

} // namespace PaperboatGui
