#include "PaperboatModals.h"
#include "PaperboatGui.hpp"
#include "UIWidgets.hpp"
#include <imgui.h>
#include <mutex>
#include <string>
#include <vector>

struct PaperboatModal {
    std::string title_;
    std::string message_;
    std::string button1_;
    std::string button2_;
    std::function<void()> button1callback_;
    std::function<void()> button2callback_;
};
std::vector<PaperboatModal> modals;
std::mutex modalsMutex;

bool closePopup = false;
double frontShownAt = -1.0;
constexpr double kAnswerDelay = 0.5;

void PaperboatModalWindow::Draw() {
    if (!IsVisible()) {
        return;
    }
    DrawElement();
    // Sync up the IsVisible flag if it was changed by ImGui
    SyncVisibilityConsoleVariable();
}

void PaperboatModalWindow::DrawElement() {
    PaperboatModal curModal;
    {
        std::lock_guard<std::mutex> lock(modalsMutex);
        if (modals.empty()) {
            return;
        }
        if (closePopup) {
            modals.erase(modals.begin());
            closePopup = false;
            ImGui::CloseCurrentPopup();
            return;
        }
        curModal = modals.at(0);
    }
    if (!ImGui::IsPopupOpen(curModal.title_.c_str())) {
        ImGui::OpenPopup(curModal.title_.c_str());
        frontShownAt = ImGui::GetTime();
    }
    if (!ImGui::BeginPopupModal(
            curModal.title_.c_str(), NULL,
            ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings
        ))
    {
        return;
    }
    std::function<void()> pressed;
    bool answered = false;
    ImGui::Text("%s", curModal.message_.c_str());
    ImGui::BeginDisabled(ImGui::GetTime() - frontShownAt < kAnswerDelay);
    UIWidgets::PushStyleButton(THEME_COLOR);
    if (ImGui::Button(curModal.button1_.c_str())) {
        pressed = curModal.button1callback_;
        answered = true;
    }
    UIWidgets::PopStyleButton();
    if (curModal.button2_ != "") {
        ImGui::SameLine();
        UIWidgets::PushStyleButton(THEME_COLOR);
        if (ImGui::Button(curModal.button2_.c_str())) {
            pressed = curModal.button2callback_;
            answered = true;
        }
        UIWidgets::PopStyleButton();
    }
    ImGui::EndDisabled();
    if (answered) {
        ImGui::CloseCurrentPopup();
        {
            std::lock_guard<std::mutex> lock(modalsMutex);
            if (!modals.empty()) {
                modals.erase(modals.begin());
            }
        }
        // Outside the lock: a callback may queue another popup.
        if (pressed != nullptr) {
            pressed();
        }
    }
    ImGui::EndPopup();
}

void PaperboatModalWindow::RegisterPopup(
    std::string title,
    std::string message,
    std::string button1,
    std::string button2,
    std::function<void()> button1callback,
    std::function<void()> button2callback
) {
    std::lock_guard<std::mutex> lock(modalsMutex);
    modals.push_back({ title, message, button1, button2, button1callback, button2callback });
}

size_t PaperboatModalWindow::PopupsQueued() {
    std::lock_guard<std::mutex> lock(modalsMutex);
    return modals.size();
}

bool PaperboatModalWindow::IsPopupOpen(std::string title) {
    std::lock_guard<std::mutex> lock(modalsMutex);
    return !modals.empty() && modals.at(0).title_ == title;
}

void PaperboatModalWindow::DismissPopup() {
    closePopup = true;
}
