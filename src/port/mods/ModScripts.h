#pragma once

#ifdef __cplusplus
#include <cstddef>
#include <functional>
#include <mutex>
#include <string>
#include <vector>

// Builds and runs the code that mods ship as C sources. Builds without ENABLE_SCRIPTING keep these as no-ops, so
// callers need no #ifdef.
namespace ModScripts {

struct Status {
    std::string text;
    bool failed = false;
    bool signedArchive = false;
};

// True when this build can run mod code.
bool Supported();

// Creates the script loader and the "trust this author?" prompt. Must run before any mod is mounted.
void Setup();

// Number of mounted archives that ship code.
size_t Count();

// Builds the code of every mounted mod and returns one "<mod>: <error>" line per mod that failed. onStart gets each
// mod's name before it builds and onFinish runs after it. Safe to call from a worker thread.
std::vector<std::string> Compile(
    const std::function<void(const std::string&)>& onStart = nullptr, const std::function<void()>& onFinish = nullptr
);

// Runs ModInit of every built mod, dependencies first, and reports the mods that were skipped.
void Load();

// Runs ModExit of every loaded mod, in reverse order, and frees their code.
void Unload();

// Unloads, rebuilds and loads every mod again. Only safe while the game isn't running: between frames on the game
// thread, or before it starts.
void Reload();

// Asks the game thread to Reload() before its next frame. Safe from any thread, e.g. a menu.
void RequestReload();

// Runs work on the game thread before its next frame, outside of any event. For calls into mod code that start on
// another thread, such as the answer to a permission prompt.
void RunOnGameThread(std::function<void()> work);

// Held while mod code is loaded, run or freed from more than one thread: by loading and unloading, by the port menu
// while it draws mod widgets, and by the UI API. Recursive, so a mod's callback can call the API.
std::recursive_mutex& Lock();

// What happened to the mod archive at path, or nullptr when it ships no code.
const Status* GetStatus(const std::string& archivePath);

} // namespace ModScripts

extern "C" {
#endif

// Runs the work the game thread was asked to do, such as a requested reload. Called between frames, outside of any
// event.
void ModScripts_RunPending(void);

#ifdef __cplusplus
}
#endif
