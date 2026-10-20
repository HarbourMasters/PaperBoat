#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "api.h"

// Widget types, in the order of the port menu's own. Widgets marked "no" aren't available to mods.
typedef enum {
    C_WIDGET_CHECKBOX,          // value is a bool*
    C_WIDGET_COMBOBOX,          // value is an int32_t*
    C_WIDGET_SLIDER_INT,        // value is an int32_t*
    C_WIDGET_SLIDER_FLOAT,      // value is a float*
    C_WIDGET_CVAR_CHECKBOX,     // cvar holds the value
    C_WIDGET_CVAR_COMBOBOX,     // cvar holds the value
    C_WIDGET_CVAR_SLIDER_INT,   // cvar holds the value
    C_WIDGET_CVAR_SLIDER_FLOAT, // cvar holds the value
    C_WIDGET_BUTTON,            // runs callback when pressed
    C_WIDGET_INPUT,             // no
    C_WIDGET_CVAR_INPUT,        // no
    C_WIDGET_CVAR_COLOR_PICKER, // cvar holds the colour
    C_WIDGET_COLOR_PICKER,      // no
    C_WIDGET_SEARCH,            // no
    C_WIDGET_SEPARATOR,         // a line
    C_WIDGET_SEPARATOR_TEXT,    // a line with the label in it
    C_WIDGET_TEXT,              // the label as text
    C_WIDGET_WINDOW_BUTTON,     // shows or hides the window named window_name
    C_WIDGET_AUDIO_BACKEND,     // no
    C_WIDGET_VIDEO_BACKEND,     // no
    C_WIDGET_CUSTOM,            // callback draws it with the C_Gui functions
} C_WidgetType;

typedef enum {
    C_ALIGN_LEFT,
    C_ALIGN_RIGHT
} C_ComponentAlign;
typedef enum {
    C_LABEL_NEAR,
    C_LABEL_FAR
} C_LabelPos;

typedef struct {
    int id;            // value stored when the option is picked
    const char* value; // text shown for it
} C_ComboboxOption;

typedef struct {
    const char* tooltip;
    int default_index;
    C_ComponentAlign alignment;
    C_LabelPos label_pos;
    C_ComboboxOption* map; // the options, ended by one whose value is NULL
} C_ComboboxOpts;

typedef struct {
    const char* tooltip;
    int min, max, default_val, step;
    const char* format; // printf format of the value, e.g. "%d%%"
} C_SliderIntOpts;

typedef struct {
    const char* tooltip;
    float min, max, default_val, step;
    const char* format; // printf format of the value, e.g. "%.1fx"
} C_SliderFloatOpts;

typedef struct {
    const char* tooltip;
    bool default_val;
} C_CheckboxOpts;

typedef struct {
    const char* tooltip;
    uint8_t default_r, default_g, default_b, default_a;
} C_ColorPickerOpts;

typedef struct {
    const char* tooltip;
} C_ButtonOpts;

typedef struct {
    C_WidgetType type;
    const char* cvar;        // setting of the C_WIDGET_CVAR_* widgets, e.g. C_MOD_CVAR("MyMod", "Speed")
    const char* window_name; // window a C_WIDGET_WINDOW_BUTTON shows and hides
    void* value;             // value of the widgets without a CVar, see C_WidgetType

    bool race_disable;   // greyed out while the DisableChanges setting locks the menu
    bool same_line;      // on the same line as the widget before it
    bool hide_in_search; // left out of the menu's search results

    void (*callback)(void);  // when a button is pressed or a value changes, or draws a C_WIDGET_CUSTOM
    void (*pre_func)(void);  // before the widget draws
    void (*post_func)(void); // after the widget draws

    union {
        C_ComboboxOpts combo;
        C_SliderIntOpts slider_int;
        C_SliderFloatOpts slider_float;
        C_CheckboxOpts checkbox;
        C_ColorPickerOpts color_picker;
        C_ButtonOpts generic;
    } opts;
} C_WidgetConfig;

// Adds a sidebar entry with column columns under the "Mods" header of the port menu. The header shows while any
// mod has an entry in it.
PB_API void C_AddSidebarEntry(const char* label, int columns);
// Adds a widget to a column of a sidebar entry, counted from 0. Labels must be unique within the entry. Strings in
// the config are copied.
#define C_AddWidget(sidebar, column, label, config) \
    C_AddWidgetSized((sidebar), (column), (label), (config), sizeof(*(config)))
PB_API void C_AddWidgetSized(const char* sidebar, int column, const char* label, C_WidgetConfig* config, uint32_t size);
// Removes a sidebar entry and its widgets. A mod's entries are removed when it unloads.
PB_API void C_RemoveSidebarEntry(const char* sidebarName);

// Runs callback every frame while the game's windows draw, to draw the mod's own. A mod's callbacks are removed when
// it unloads.
typedef void (*C_GuiDrawFunc)(void);
PB_API void C_AddGuiDraw(C_GuiDrawFunc callback);
PB_API void C_RemoveGuiDraw(C_GuiDrawFunc callback);

// Drawing with Dear ImGui, from a C_AddGuiDraw callback only. Positions are from the game window's top-left, in the
// units of C_GuiDisplaySize, also with multi-window mode on. Colors are 0xRRGGBBAA. Every C_GuiBegin needs a
// C_GuiEnd, whatever it returned; a callback that leaves one open has it closed for it.

enum {
    C_GUI_NO_TITLE = 1 << 0,
    C_GUI_NO_RESIZE = 1 << 1,
    C_GUI_NO_MOVE = 1 << 2,
    C_GUI_NO_BACKGROUND = 1 << 3,
    C_GUI_AUTO_RESIZE = 1 << 4,
    C_GUI_NO_INPUT = 1 << 5,
    C_GUI_NO_SCROLLBAR = 1 << 6,
    C_GUI_NO_FOCUS = 1 << 7,
};

// A window. open, when not NULL, gets a close button and turns FALSE when it is pressed. Returns FALSE while the
// window is collapsed or hidden: skip its contents, but still call C_GuiEnd.
PB_API int C_GuiBegin(const char* title, int* open, int flags);
PB_API void C_GuiEnd(void);
// For the next C_GuiBegin. always TRUE sets it every frame, FALSE only the first time the window appears.
PB_API void C_GuiSetNextWindowPos(float x, float y, int always);
PB_API void C_GuiSetNextWindowSize(float width, float height, int always);
// A scrolling area inside a window; 0 for a size fills the space left.
PB_API int C_GuiBeginChild(const char* id, float width, float height, int border);
PB_API void C_GuiEndChild(void);

PB_API void C_GuiText(const char* text);
PB_API void C_GuiTextColored(uint32_t color, const char* text);
PB_API void C_GuiTextWrapped(const char* text);
// TRUE on the frame it is clicked.
PB_API int C_GuiButton(const char* label);
// Edits buffer, of size bytes. Returns TRUE when the text changed, or with submit_on_enter when Enter is pressed.
PB_API int C_GuiInputText(const char* label, char* buffer, uint32_t size, int submit_on_enter);
// The following return TRUE when the value changed.
PB_API int C_GuiCheckbox(const char* label, int* value);
PB_API int C_GuiSliderInt(const char* label, int* value, int min, int max);
PB_API int C_GuiSliderFloat(const char* label, float* value, float min, float max);
PB_API void C_GuiSameLine(void);
PB_API void C_GuiSeparator(void);
PB_API void C_GuiSpacing(void);
// Gives the keyboard to the next widget.
PB_API void C_GuiFocusNext(void);
// Scrolls the current window or child to its end, e.g. after adding a chat line.
PB_API void C_GuiScrollToBottom(void);
// Tells apart widgets with the same label, e.g. one per player.
PB_API void C_GuiPushId(const char* id);
PB_API void C_GuiPopId(void);

// Drawn on top of the game and every window.
PB_API void C_GuiDrawText(float x, float y, uint32_t color, const char* text);
PB_API void C_GuiDrawRect(float x0, float y0, float x1, float y1, uint32_t color, float rounding, int filled);
PB_API void C_GuiTextSize(const char* text, float* width, float* height);
PB_API void C_GuiDisplaySize(float* width, float* height);
// TRUE while a text box has the keyboard, so the mod can ignore its own key shortcuts.
PB_API int C_GuiWantsKeyboard(void);

// Where a point in the game world shows on screen, in the same pixels as the drawing above, e.g. for a name over a
// character. FALSE outside gameplay or when the point is behind the camera.
PB_API int C_WorldToScreen(float x, float y, float z, float* screen_x, float* screen_y);
