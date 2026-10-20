#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "api.h"

// Settings of a mod go under "gMods.<mod>.", so they don't clash with the game's or other mods' settings. They are
// saved with the port's own settings.
#define C_MOD_CVAR(mod, name) "gMods." mod "." name

PB_API int32_t CVarGetInteger(const char* name, int32_t defaultValue);
PB_API float CVarGetFloat(const char* name, float defaultValue);
PB_API const char* CVarGetString(const char* name, const char* defaultValue);
PB_API void CVarSetInteger(const char* name, int32_t value);
PB_API void CVarSetFloat(const char* name, float value);
PB_API void CVarSetString(const char* name, const char* value);
PB_API void CVarRegisterInteger(const char* name, int32_t defaultValue);
PB_API void CVarRegisterFloat(const char* name, float defaultValue);
PB_API void CVarRegisterString(const char* name, const char* defaultValue);
PB_API void CVarClear(const char* name);
PB_API bool CVarExists(const char* name);
PB_API void CVarSave(void);
PB_API uint32_t C_CVarGetColor(const char* cvar, uint32_t defaultValue);
