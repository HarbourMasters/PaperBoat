#include "PaperboatGui.hpp"

#include <spdlog/spdlog.h>
#include <imgui.h>
#include <imgui_internal.h>

#ifdef __APPLE__
#include <fast/backends/gfx_metal.h>
#endif

#include "Notification.h"
#include "PaperboatInputEditorWindow.h"
#include "port/hooks/ui/EventDebugger.h"
#include <ship/window/gui/ConsoleWindow.h>

namespace PaperboatGui {
// MARK: - Delegates
std::shared_ptr<Ship::GuiWindow> mInputEditorWindow;
std::shared_ptr<PaperboatMenu> mPaperboatMenu;
std::shared_ptr<Notification::Window> mNotificationWindow;
std::shared_ptr<InputViewer> mInputViewer;
std::shared_ptr<InputViewerSettingsWindow> mInputViewerSettings;
std::shared_ptr<PaperboatModalWindow> mModalWindow;
std::shared_ptr<Ship::GuiWindow> mConsoleWindow;
std::shared_ptr<EventDebuggerWindow> mEventDebuggerWindow;

UIWidgets::Colors GetMenuThemeColor() {
    return mPaperboatMenu->GetMenuThemeColor();
}

void SetupMenu() {
    auto gui = Ship::Context::GetInstance()->GetWindow()->GetGui();
    mPaperboatMenu = std::make_shared<PaperboatGui::PaperboatMenu>(CVAR_WINDOW("Menu"), "Port Menu");
    gui->SetMenu(mPaperboatMenu);

    mModalWindow = std::make_shared<PaperboatModalWindow>(CVAR_WINDOW("ModalWindow"), "Modal Window");
    gui->AddGuiWindow(mModalWindow);
    mModalWindow->Show();
}

void SetupGuiElements() {
    auto gui = Ship::Context::GetInstance()->GetWindow()->GetGui();

    auto& style = ImGui::GetStyle();
    style.FramePadding = ImVec2(4.0f, 6.0f);
    style.ItemSpacing = ImVec2(8.0f, 6.0f);
    style.Colors[ImGuiCol_MenuBarBg] = UIWidgets::ColorValues.at(UIWidgets::Colors::DarkGray);

    mConsoleWindow = std::make_shared<Ship::ConsoleWindow>(CVAR_WINDOW("DevConsole"), "Console##Dev", ImVec2(820, 630));
    gui->AddGuiWindow(mConsoleWindow);
    
    mEventDebuggerWindow = std::make_shared<EventDebuggerWindow>(CVAR_WINDOW("EventDebugger"), "Event Debugger");
    gui->AddGuiWindow(mEventDebuggerWindow);

    mPaperboatMenu = std::make_shared<PaperboatMenu>(CVAR_WINDOW("Menu"), "Settings Menu");
    gui->SetMenu(mPaperboatMenu);

    mInputEditorWindow =
        std::make_shared<PaperboatInputEditorWindow>(CVAR_WINDOW("ControllerConfiguration"), "Configure Controller");
    gui->AddGuiWindow(mInputEditorWindow);

    mNotificationWindow = std::make_shared<Notification::Window>(CVAR_WINDOW("Notifications"), "Notifications Window");
    gui->AddGuiWindow(mNotificationWindow);
    mNotificationWindow->Show();

    mInputViewer = std::make_shared<InputViewer>(CVAR_WINDOW("InputViewer"), "Input Viewer");
    gui->AddGuiWindow(mInputViewer);
    mInputViewerSettings = std::make_shared<InputViewerSettingsWindow>(CVAR_WINDOW("InputViewerSettings"),
                                                                       "Input Viewer Settings", ImVec2(500, 525));
    gui->AddGuiWindow(mInputViewerSettings);

    mModalWindow = std::make_shared<PaperboatModalWindow>(CVAR_WINDOW("ModalWindow"), "Modal Window");
    gui->AddGuiWindow(mModalWindow);
    mModalWindow->Show();
}

void Destroy() {
    auto gui = Ship::Context::GetInstance()->GetWindow()->GetGui();

    gui->RemoveAllGuiWindows();
    mPaperboatMenu = nullptr;
    mModalWindow = nullptr;
    mInputEditorWindow = nullptr;
    mNotificationWindow = nullptr;
    mInputViewer = nullptr;
    mInputViewerSettings = nullptr;
    mConsoleWindow = nullptr;
}

void RegisterPopup(std::string title, std::string message, std::string button1, std::string button2,
                   std::function<void()> button1callback, std::function<void()> button2callback) {
    mModalWindow->RegisterPopup(title, message, button1, button2, button1callback, button2callback);
}

size_t PopupsQueued() {
    return mModalWindow->PopupsQueued();
}

} // namespace PaperboatGui
