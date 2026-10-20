#pragma once

#include <stdint.h>

#include "api.h"

// Values kept in the save file being played, under keys like "mymod.visits". A file's values are read when it loads,
// before OnSaveFileStart fires, and written every time the game saves it. A new file starts with none.

PB_API int C_SaveDataHas(const char* key);
PB_API void C_SaveDataRemove(const char* key);

PB_API int32_t C_SaveDataGetInt(const char* key, int32_t defaultValue);
PB_API void C_SaveDataSetInt(const char* key, int32_t value);
PB_API float C_SaveDataGetFloat(const char* key, float defaultValue);
PB_API void C_SaveDataSetFloat(const char* key, float value);
// The string stays valid until the key is set again or another file loads.
PB_API const char* C_SaveDataGetString(const char* key, const char* defaultValue);
PB_API void C_SaveDataSetString(const char* key, const char* value);
// Copies up to capacity bytes into out and returns the size of the stored data, 0 when there is none.
PB_API uint32_t C_SaveDataGetBytes(const char* key, void* out, uint32_t capacity);
PB_API void C_SaveDataSetBytes(const char* key, const void* data, uint32_t size);
