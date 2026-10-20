#pragma once

#include <stdint.h>

#include "api.h"

// EVT scripts written in a mod with the game's EVT_ macros. The game calls the functions a script names by address,
// so a mod's own API_CALLABLE functions work in its scripts as they are.
//
// Start scripts while the game runs, e.g. from an OnMapReady listener: the game clears every script when it starts
// and when a map loads. A mod's scripts are stopped before it unloads, together with their child scripts. Scripts
// they start with Exec aren't tracked, so give long-running ones their own C_StartScript.

// Starts a script with an EVT_PRIORITY_* priority and EVT_FLAG_* flags. Returns its script ID, or -1.
PB_API int32_t C_StartScript(const void* script, int32_t priority, int32_t flags);
// Stops a script this mod started, and its child scripts.
PB_API void C_StopScript(int32_t scriptID);
// 1 while the script started with this ID still runs.
PB_API int C_IsScriptRunning(int32_t scriptID);

// Variables of a running script, for API functions called from a mod's scripts. var is anything a script can name:
// LVar0, GameFlag(...), MapVar(...), a constant.
PB_API intptr_t C_ScriptGetVar(void* script, intptr_t var);
PB_API void C_ScriptSetVar(void* script, intptr_t var, intptr_t value);
PB_API float C_ScriptGetFloat(void* script, intptr_t var);
PB_API void C_ScriptSetFloat(void* script, intptr_t var, float value);
