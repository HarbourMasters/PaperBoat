#ifdef ENABLE_SCRIPTING

#include "port/api/ui.h"

#include "port/ShipInit.hpp"
#include "port/api/ModOwner.hpp"
#include "port/api/SizedDef.hpp"
#include "port/mods/ModScripts.h"
#include "port/ui/MenuTypes.h"
#include "port/ui/PaperboatGui.hpp"
#include "port/ui/PaperboatMenu.h"
#include "port/ui/UIWidgets.hpp"
#include "port/ui/cvar_prefixes.h"

#include "common.h"
#include "game_modes.h"
#undef End // an EVT macro, clashes with ImGui::End

#include <fast/Fast3dWindow.h>
#include <fast/interpreter.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <ship/Context.h>
#include <ship/window/Window.h>
#include <ship/window/gui/Gui.h>
#include <spdlog/spdlog.h>

#include <deque>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace {

constexpr const char* kSection = "Mods";

using Lock = std::lock_guard<std::recursive_mutex>;

struct GuiDraw {
    C_GuiDrawFunc callback;
    std::string owner;
};

struct OwnedSidebar {
    std::string name;
    std::string owner;
};

struct OwnedWidget {
    WidgetPath path;
    std::string label;
    std::string owner;
};

std::vector<GuiDraw> sGuiDraws;
std::vector<OwnedSidebar> sSidebars;
std::vector<OwnedWidget> sWidgets;
// Copies of the strings mods pass. The menu keeps pointers to them, so they outlive the mod's own.
std::deque<std::string> sStrings;

const char* Keep(const char* text) {
    if (text == nullptr) {
        return nullptr;
    }
    return sStrings.emplace_back(text).c_str();
}

const char* KeepTooltip(const char* text) {
    return text != nullptr ? Keep(text) : "";
}

PaperboatGui::PaperboatMenu* Menu() {
    return PaperboatGui::mPaperboatMenu.get();
}

UIWidgets::ComponentAlignments MapAlign(C_ComponentAlign align) {
    return align == C_ALIGN_RIGHT ? UIWidgets::ComponentAlignments::Right : UIWidgets::ComponentAlignments::Left;
}

UIWidgets::LabelPositions MapLabel(C_LabelPos pos) {
    return pos == C_LABEL_FAR ? UIWidgets::LabelPositions::Far : UIWidgets::LabelPositions::Near;
}

// Runs a mod's function for a widget as that mod.
WidgetFunc InOwner(void (*func)(void), const std::string& owner) {
    return [func, owner](WidgetInfo&) {
        Lock lock(ModScripts::Lock());
        ModOwner::Scope scope(owner);
        func();
    };
}

bool Supported(C_WidgetType type) {
    switch (type) {
        case C_WIDGET_INPUT:
        case C_WIDGET_CVAR_INPUT:
        case C_WIDGET_COLOR_PICKER:
        case C_WIDGET_SEARCH:
        case C_WIDGET_AUDIO_BACKEND:
        case C_WIDGET_VIDEO_BACKEND:
            return false;
        default:
            return type >= C_WIDGET_CHECKBOX && type <= C_WIDGET_CUSTOM;
    }
}

void RemoveSidebar(const std::string& name) {
    if (Menu() != nullptr) {
        Menu()->RemoveSidebarEntry(kSection, name);
    }
    std::erase_if(sSidebars, [&](const OwnedSidebar& sidebar) { return sidebar.name == name; });
    std::erase_if(sWidgets, [&](const OwnedWidget& widget) { return widget.path.sidebarName == name; });
}

void ReleaseUi(const std::string& mod) {
    Lock lock(ModScripts::Lock());
    std::erase_if(sGuiDraws, [&](const GuiDraw& draw) { return draw.owner == mod; });
    for (const OwnedWidget& widget : sWidgets) {
        if (widget.owner == mod && Menu() != nullptr) {
            Menu()->RemoveWidget(widget.path, widget.label);
        }
    }
    std::erase_if(sWidgets, [&](const OwnedWidget& widget) { return widget.owner == mod; });
    std::vector<std::string> sidebars;
    for (const OwnedSidebar& sidebar : sSidebars) {
        if (sidebar.owner == mod) {
            sidebars.push_back(sidebar.name);
        }
    }
    for (const std::string& name : sidebars) {
        RemoveSidebar(name);
    }
}

// Draws the windows of mods, on the window thread with the rest of the GUI.
class ModGuiWindow : public Ship::GuiWindow {
public:
    using GuiWindow::GuiWindow;

    void InitElement() override {
    }
    void DrawElement() override {
    }
    void UpdateElement() override {
    }

    void Draw() override {
        Lock lock(ModScripts::Lock());
        for (const GuiDraw& draw : sGuiDraws) {
            ModOwner::Scope scope(draw.owner);
            // A callback that leaves a window or an ID pushed can't break the rest of the frame.
            ImGuiErrorRecoveryState state;
            ImGui::ErrorRecoveryStoreState(&state);
            draw.callback();
            ImGui::ErrorRecoveryTryToRecoverState(&state);
        }
    }
};

std::shared_ptr<ModGuiWindow> sModGuiWindow;

void InitUiApi() {
    ModOwner::AddReleaser(ReleaseUi);
    auto gui = Ship::Context::GetRawInstance()->GetWindow()->GetGui();
    sModGuiWindow = std::make_shared<ModGuiWindow>(CVAR_WINDOW("ModGui"), "##ModGui");
    gui->AddGuiWindow(sModGuiWindow);
    sModGuiWindow->Show();
}

RegisterShipInitFunc sInitUiApi(InitUiApi);

ImU32 ToImColor(uint32_t rgba) {
    return IM_COL32((rgba >> 24) & 0xFF, (rgba >> 16) & 0xFF, (rgba >> 8) & 0xFF, rgba & 0xFF);
}

ImVec4 ToImVec4(uint32_t rgba) {
    return ImGui::ColorConvertU32ToFloat4(ToImColor(rgba));
}

ImGuiWindowFlags ToWindowFlags(int flags) {
    ImGuiWindowFlags out = ImGuiWindowFlags_None;
    out |= (flags & C_GUI_NO_TITLE) ? ImGuiWindowFlags_NoTitleBar : 0;
    out |= (flags & C_GUI_NO_RESIZE) ? ImGuiWindowFlags_NoResize : 0;
    out |= (flags & C_GUI_NO_MOVE) ? ImGuiWindowFlags_NoMove : 0;
    out |= (flags & C_GUI_NO_BACKGROUND) ? ImGuiWindowFlags_NoBackground : 0;
    out |= (flags & C_GUI_AUTO_RESIZE) ? ImGuiWindowFlags_AlwaysAutoResize : 0;
    out |= (flags & C_GUI_NO_INPUT) ? ImGuiWindowFlags_NoInputs : 0;
    out |= (flags & C_GUI_NO_SCROLLBAR) ? ImGuiWindowFlags_NoScrollbar : 0;
    out |= (flags & C_GUI_NO_FOCUS) ? ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus : 0;
    return out;
}

const char* Str(const char* s) {
    return s != nullptr ? s : "";
}

} // namespace

extern "C" void C_AddGuiDraw(C_GuiDrawFunc callback) {
    if (callback != nullptr) {
        Lock lock(ModScripts::Lock());
        sGuiDraws.push_back({ callback, ModOwner::Current() });
    }
}

extern "C" void C_RemoveGuiDraw(C_GuiDrawFunc callback) {
    Lock lock(ModScripts::Lock());
    std::erase_if(sGuiDraws, [callback](const GuiDraw& draw) { return draw.callback == callback; });
}

extern "C" void C_AddSidebarEntry(const char* label, int columns) {
    if (Menu() == nullptr || label == nullptr || label[0] == '\0') {
        return;
    }
    Lock lock(ModScripts::Lock());
    for (const OwnedSidebar& sidebar : sSidebars) {
        if (sidebar.name == label) {
            SPDLOG_ERROR("Mods menu: there already is a sidebar entry named {}", label);
            return;
        }
    }
    Menu()->AddSection(kSection, CVAR_SETTING("Menu.ModsSidebarSection"));
    Menu()->AddSidebarEntry(kSection, label, std::max(columns, 1));
    sSidebars.push_back({ label, ModOwner::Current() });
}

extern "C" void C_RemoveSidebarEntry(const char* sidebarName) {
    if (sidebarName == nullptr) {
        return;
    }
    Lock lock(ModScripts::Lock());
    const std::string owner = ModOwner::Current();
    for (const OwnedSidebar& sidebar : sSidebars) {
        if (sidebar.name == sidebarName && sidebar.owner == owner) {
            RemoveSidebar(sidebarName);
            return;
        }
    }
}

extern "C" void
C_AddWidgetSized(const char* sidebar, int column, const char* label, C_WidgetConfig* widgetConfig, uint32_t size) {
    const SizedDef<C_WidgetConfig> sized(widgetConfig, size);
    const C_WidgetConfig* config = sized.get();
    if (Menu() == nullptr || sidebar == nullptr || label == nullptr || label[0] == '\0' || config == nullptr) {
        return;
    }
    Lock lock(ModScripts::Lock());
    auto owned = std::find_if(sSidebars.begin(), sSidebars.end(), [&](const OwnedSidebar& entry) {
        return entry.name == sidebar;
    });
    if (owned == sSidebars.end()) {
        SPDLOG_ERROR("Mods menu: widget {} names sidebar entry {}, which no mod added", label, sidebar);
        return;
    }
    if (!Supported(config->type)) {
        SPDLOG_ERROR("Mods menu: widget {} has a type mods can't add", label);
        return;
    }
    const bool usesCVar = config->type == C_WIDGET_CVAR_CHECKBOX || config->type == C_WIDGET_CVAR_COMBOBOX
        || config->type == C_WIDGET_CVAR_SLIDER_INT || config->type == C_WIDGET_CVAR_SLIDER_FLOAT
        || config->type == C_WIDGET_CVAR_COLOR_PICKER;
    const bool usesValue = config->type == C_WIDGET_CHECKBOX || config->type == C_WIDGET_COMBOBOX
        || config->type == C_WIDGET_SLIDER_INT || config->type == C_WIDGET_SLIDER_FLOAT;
    if ((usesCVar && config->cvar == nullptr) || (usesValue && config->value == nullptr)
        || (config->type == C_WIDGET_WINDOW_BUTTON && config->window_name == nullptr))
    {
        SPDLOG_ERROR("Mods menu: widget {} lacks its cvar, value or window_name", label);
        return;
    }

    const std::string owner = ModOwner::Current();
    WidgetPath path = { kSection, sidebar, static_cast<SectionColumns>(std::max(column, 0)) };
    sWidgets.push_back({ path, label, owner });
    WidgetInfo& widget = Menu()
                             ->AddWidget(path, label, static_cast<WidgetType>(config->type))
                             .RaceDisable(config->race_disable)
                             .SameLine(config->same_line)
                             .HideInSearch(config->hide_in_search);

    if (usesCVar) {
        widget.CVar(Keep(config->cvar));
    }
    if (config->window_name != nullptr) {
        widget.WindowName(Keep(config->window_name));
    }
    if (config->callback != nullptr) {
        if (config->type == C_WIDGET_CUSTOM) {
            widget.CustomFunction(InOwner(config->callback, owner));
        } else {
            widget.Callback(InOwner(config->callback, owner));
        }
    }
    if (config->pre_func != nullptr) {
        widget.PreFunc(InOwner(config->pre_func, owner));
    }
    if (config->post_func != nullptr) {
        widget.PostFunc(InOwner(config->post_func, owner));
    }

    switch (config->type) {
        case C_WIDGET_COMBOBOX:
        case C_WIDGET_CVAR_COMBOBOX: {
            auto options = UIWidgets::ComboboxOptions()
                               .DefaultIndex(config->opts.combo.default_index)
                               .ComponentAlignment(MapAlign(config->opts.combo.alignment))
                               .LabelPosition(MapLabel(config->opts.combo.label_pos));
            options.Tooltip(KeepTooltip(config->opts.combo.tooltip));
            std::unordered_map<int32_t, const char*> comboMap;
            for (C_ComboboxOption* it = config->opts.combo.map; it != nullptr && it->value != nullptr; it++) {
                comboMap[it->id] = Keep(it->value);
            }
            options.ComboMap(comboMap);
            if (config->type == C_WIDGET_COMBOBOX) {
                widget.ValuePointer((int32_t*) config->value);
            }
            widget.Options(options);
            break;
        }
        case C_WIDGET_SLIDER_INT:
        case C_WIDGET_CVAR_SLIDER_INT: {
            auto options = UIWidgets::IntSliderOptions()
                               .Min(config->opts.slider_int.min)
                               .Max(config->opts.slider_int.max)
                               .DefaultValue(config->opts.slider_int.default_val)
                               .Step(std::max(config->opts.slider_int.step, 1));
            options.Tooltip(KeepTooltip(config->opts.slider_int.tooltip));
            if (config->opts.slider_int.format != nullptr) {
                options.Format(Keep(config->opts.slider_int.format));
            }
            if (config->type == C_WIDGET_SLIDER_INT) {
                widget.ValuePointer((int32_t*) config->value);
            }
            widget.Options(options);
            break;
        }
        case C_WIDGET_SLIDER_FLOAT:
        case C_WIDGET_CVAR_SLIDER_FLOAT: {
            auto options = UIWidgets::FloatSliderOptions()
                               .Min(config->opts.slider_float.min)
                               .Max(config->opts.slider_float.max)
                               .DefaultValue(config->opts.slider_float.default_val);
            if (config->opts.slider_float.step > 0.0f) {
                options.Step(config->opts.slider_float.step);
            }
            options.Tooltip(KeepTooltip(config->opts.slider_float.tooltip));
            if (config->opts.slider_float.format != nullptr) {
                options.Format(Keep(config->opts.slider_float.format));
            }
            if (config->type == C_WIDGET_SLIDER_FLOAT) {
                widget.ValuePointer((float*) config->value);
            }
            widget.Options(options);
            break;
        }
        case C_WIDGET_CHECKBOX:
        case C_WIDGET_CVAR_CHECKBOX: {
            auto options = UIWidgets::CheckboxOptions().DefaultValue(config->opts.checkbox.default_val);
            options.Tooltip(KeepTooltip(config->opts.checkbox.tooltip));
            if (config->type == C_WIDGET_CHECKBOX) {
                widget.ValuePointer((bool*) config->value);
            }
            widget.Options(options);
            break;
        }
        case C_WIDGET_CVAR_COLOR_PICKER: {
            const C_ColorPickerOpts& color = config->opts.color_picker;
            auto options = UIWidgets::ColorPickerOptions().DefaultValue(
                Color_RGBA8 { color.default_r, color.default_g, color.default_b, color.default_a }
            );
            options.Tooltip(KeepTooltip(color.tooltip));
            widget.Options(options);
            break;
        }
        case C_WIDGET_TEXT:
        case C_WIDGET_SEPARATOR_TEXT:
            widget.Options(UIWidgets::TextOptions());
            break;
        case C_WIDGET_WINDOW_BUTTON: {
            auto options = UIWidgets::WindowButtonOptions();
            options.Tooltip(KeepTooltip(config->opts.generic.tooltip));
            widget.Options(options);
            break;
        }
        case C_WIDGET_BUTTON: {
            auto options = UIWidgets::ButtonOptions();
            options.Tooltip(KeepTooltip(config->opts.generic.tooltip));
            widget.Options(options);
            break;
        }
        default:
            break;
    }
}

extern "C" int C_GuiBegin(const char* title, int* open, int flags) {
    if (open == nullptr) {
        return ImGui::Begin(Str(title), nullptr, ToWindowFlags(flags));
    }
    bool shown = *open != 0;
    const bool visible = ImGui::Begin(Str(title), &shown, ToWindowFlags(flags));
    *open = shown;
    return visible;
}

extern "C" void C_GuiEnd(void) {
    ImGui::End();
}

extern "C" void C_GuiSetNextWindowPos(float x, float y, int always) {
    ImGui::SetNextWindowPos(ImVec2(x, y), always ? ImGuiCond_Always : ImGuiCond_FirstUseEver);
}

extern "C" void C_GuiSetNextWindowSize(float width, float height, int always) {
    ImGui::SetNextWindowSize(ImVec2(width, height), always ? ImGuiCond_Always : ImGuiCond_FirstUseEver);
}

extern "C" int C_GuiBeginChild(const char* id, float width, float height, int border) {
    return ImGui::BeginChild(Str(id), ImVec2(width, height), border ? ImGuiChildFlags_Borders : ImGuiChildFlags_None);
}

extern "C" void C_GuiEndChild(void) {
    ImGui::EndChild();
}

extern "C" void C_GuiText(const char* text) {
    ImGui::TextUnformatted(Str(text));
}

extern "C" void C_GuiTextColored(uint32_t color, const char* text) {
    ImGui::PushStyleColor(ImGuiCol_Text, ToImVec4(color));
    ImGui::TextUnformatted(Str(text));
    ImGui::PopStyleColor();
}

extern "C" void C_GuiTextWrapped(const char* text) {
    ImGui::PushTextWrapPos(0.0f);
    ImGui::TextUnformatted(Str(text));
    ImGui::PopTextWrapPos();
}

extern "C" int C_GuiButton(const char* label) {
    return ImGui::Button(Str(label));
}

extern "C" int C_GuiInputText(const char* label, char* buffer, uint32_t size, int submit_on_enter) {
    if (buffer == nullptr || size == 0) {
        return 0;
    }
    const ImGuiInputTextFlags flags = submit_on_enter ? ImGuiInputTextFlags_EnterReturnsTrue : ImGuiInputTextFlags_None;
    return ImGui::InputText(Str(label), buffer, size, flags);
}

extern "C" int C_GuiCheckbox(const char* label, int* value) {
    if (value == nullptr) {
        return 0;
    }
    bool checked = *value != 0;
    const bool changed = ImGui::Checkbox(Str(label), &checked);
    *value = checked;
    return changed;
}

extern "C" int C_GuiSliderInt(const char* label, int* value, int min, int max) {
    return value != nullptr && ImGui::SliderInt(Str(label), value, min, max);
}

extern "C" int C_GuiSliderFloat(const char* label, float* value, float min, float max) {
    return value != nullptr && ImGui::SliderFloat(Str(label), value, min, max);
}

extern "C" void C_GuiSameLine(void) {
    ImGui::SameLine();
}

extern "C" void C_GuiSeparator(void) {
    ImGui::Separator();
}

extern "C" void C_GuiSpacing(void) {
    ImGui::Spacing();
}

extern "C" void C_GuiFocusNext(void) {
    ImGui::SetKeyboardFocusHere();
}

extern "C" void C_GuiScrollToBottom(void) {
    ImGui::SetScrollHereY(1.0f);
}

extern "C" void C_GuiPushId(const char* id) {
    ImGui::PushID(Str(id));
}

extern "C" void C_GuiPopId(void) {
    ImGui::PopID();
}

extern "C" void C_GuiDrawText(float x, float y, uint32_t color, const char* text) {
    ImGui::GetForegroundDrawList()->AddText(ImVec2(x, y), ToImColor(color), Str(text));
}

extern "C" void C_GuiDrawRect(float x0, float y0, float x1, float y1, uint32_t color, float rounding, int filled) {
    ImDrawList* list = ImGui::GetForegroundDrawList();
    if (filled) {
        list->AddRectFilled(ImVec2(x0, y0), ImVec2(x1, y1), ToImColor(color), rounding);
    } else {
        list->AddRect(ImVec2(x0, y0), ImVec2(x1, y1), ToImColor(color), rounding);
    }
}

extern "C" void C_GuiTextSize(const char* text, float* width, float* height) {
    const ImVec2 size = ImGui::CalcTextSize(Str(text));
    if (width != nullptr) {
        *width = size.x;
    }
    if (height != nullptr) {
        *height = size.y;
    }
}

extern "C" void C_GuiDisplaySize(float* width, float* height) {
    const ImVec2 size = ImGui::GetIO().DisplaySize;
    if (width != nullptr) {
        *width = size.x;
    }
    if (height != nullptr) {
        *height = size.y;
    }
}

extern "C" int C_GuiWantsKeyboard(void) {
    return ImGui::GetIO().WantTextInput;
}

extern "C" int C_WorldToScreen(float x, float y, float z, float* screenX, float* screenY) {
    const s32 mode = get_game_mode();
    if (mode != GAME_MODE_WORLD && mode != GAME_MODE_BATTLE) {
        return 0;
    }
    auto window = std::dynamic_pointer_cast<Fast::Fast3dWindow>(Ship::Context::GetRawInstance()->GetWindow());
    auto interpreter = window != nullptr ? window->GetInterpreterWeak().lock() : nullptr;
    if (interpreter == nullptr) {
        return 0;
    }
    const auto& viewport = interpreter->mGameWindowViewport;
    if (viewport.width <= 0 || viewport.height <= 0) {
        return 0;
    }

    // As get_screen_coords does, into the game's 320x240 screen.
    Camera* camera = &gCameras[mode == GAME_MODE_BATTLE ? CAM_BATTLE : CAM_DEFAULT];
    f32 tX, tY, tZ, tW;
    transform_point(camera->mtxPerspective, x, y, z, 1.0f, &tX, &tY, &tZ, &tW);
    if (tW <= 0.01f) {
        return 0;
    }
    const float nativeX = camera->viewportStartX + (1.0f + tX / tW) * camera->viewportW * 0.5f;
    const float nativeY = camera->viewportStartY + (1.0f - tY / tW) * camera->viewportH * 0.5f;

    // The renderer keeps the game's height and centres its width, widening the sides on wide windows. Its viewport
    // is in framebuffer pixels, ImGui's in window points.
    const float scale = (float) viewport.height / SCREEN_HEIGHT;
    const ImVec2 framebufferScale = ImGui::GetIO().DisplayFramebufferScale;
    const float pixelX = viewport.x + viewport.width * 0.5f + (nativeX - SCREEN_WIDTH * 0.5f) * scale;
    const float pixelY = viewport.y + nativeY * scale;
    if (screenX != nullptr) {
        *screenX = pixelX / (framebufferScale.x > 0.0f ? framebufferScale.x : 1.0f);
    }
    if (screenY != nullptr) {
        *screenY = pixelY / (framebufferScale.y > 0.0f ? framebufferScale.y : 1.0f);
    }
    return 1;
}

#endif
