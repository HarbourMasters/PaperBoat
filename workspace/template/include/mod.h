#pragma once

#include <stddef.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#define PB_EXPORT __declspec(dllexport)
#else
#define PB_EXPORT __attribute__((visibility("default")))
#endif

// The functions the game calls when the mod loads and unloads.
#define MOD_INIT PB_EXPORT void ModInit
#define MOD_EXIT PB_EXPORT void ModExit

// Calls a function another mod exports: CALL_FUNC("Other Mod", Name, args) with NameFunc, its type, and NameSymbol,
// its name as a string, defined by that mod's header.
extern void* ScriptGetFunction(const char* module, const char* function);
#define CALL_FUNC(mod, func, ...) ((func##Func) ScriptGetFunction(mod, func##Symbol))(__VA_ARGS__)

// Declared before the defines below, or TinyCC would take them for functions returning int and cut pointers to 32
// bits.
extern void* GameEngine_Malloc(size_t size);
extern void GameEngine_Free(void* ptr);

#define malloc(size) GameEngine_Malloc(size)
#define free(ptr) GameEngine_Free(ptr)
