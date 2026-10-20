#include "port/mods/ModScripts.h"

std::recursive_mutex& ModScripts::Lock() {
    static std::recursive_mutex lock;
    return lock;
}

#ifdef ENABLE_SCRIPTING

#include "port/api/ModOwner.hpp"
#include "port/api/api.h"
#include "port/ui/Notification.h"

#include <SDL2/SDL.h>
#include <ship/Context.h>
#include <ship/resource/ResourceManager.h>
#include <ship/resource/archive/Archive.h>
#include <ship/resource/archive/ArchiveManager.h>
#include <ship/scripting/ScriptLoader.h>
#include <ship/security/Keystore.h>
#include <spdlog/spdlog.h>

#include <atomic>
#include <filesystem>
#include <map>
#include <unordered_map>

#if defined(__linux__) || defined(__ANDROID__)
#include <dlfcn.h>
#endif

namespace {

// Keyed by the path the archive was mounted from.
std::map<std::string, ModScripts::Status> sStatus;
std::atomic<bool> sReloadRequested = false;

const ImVec4 kErrorColor = ImVec4(1.0f, 0.5f, 0.5f, 1.0f);

std::shared_ptr<Ship::ArchiveManager> GetArchiveManager() {
    return Ship::Context::GetRawInstance()->GetResourceManager()->GetArchiveManager();
}

bool ShipsCode(const std::shared_ptr<Ship::Archive>& archive) {
    const auto& info = archive->GetManifest();
    return !info.Main.empty() || !info.Binaries.empty();
}

void SetStatus(const std::string& name, const std::string& text, bool failed) {
    const auto archives = GetArchiveManager()->GetArchives();
    for (const auto& archive : *archives) {
        if (ShipsCode(archive) && archive->GetManifest().Name == name) {
            auto& status = sStatus[archive->GetPath()];
            status.text = text;
            status.failed = failed;
        }
    }
}

std::string TccBase() {
    std::string base = Ship::Context::GetPathRelativeToAppDirectory(".tcc");
    if (!std::filesystem::exists(base)) {
        base = Ship::Context::GetAppBundlePath() + "/.tcc";
    }
    return base;
}

// The folder libmain.so, the game itself, was loaded from. Android mods link against it to reach the game.
std::string OwnLibraryDir() {
#if defined(__ANDROID__)
    Dl_info self = {};
    if (dladdr((void*) &OwnLibraryDir, &self) && self.dli_fname != nullptr) {
        return std::filesystem::path(self.dli_fname).parent_path().string();
    }
#endif
    return {};
}

#if defined(__linux__) && !defined(__ANDROID__)
// TCC links mods against "libc.so", which distros only ship as a linker script or with the -dev package.
void LinkLibcStub(const std::string& tccBase) {
    const auto stub = std::filesystem::path(tccBase) / "lib" / "libc.so";
    std::error_code ec;
    const bool stale = std::filesystem::is_symlink(stub, ec) && !std::filesystem::exists(stub, ec);
    if (std::filesystem::exists(stub, ec) && !stale) {
        return;
    }
    Dl_info info = {};
    void* libcFunc = dlsym(RTLD_DEFAULT, "printf");
    if (libcFunc != nullptr && dladdr(libcFunc, &info) && info.dli_fname != nullptr && *info.dli_fname) {
        std::filesystem::remove(stub, ec);
        std::filesystem::create_symlink(info.dli_fname, stub, ec);
        if (ec) {
            SPDLOG_WARN("ModScripts: failed to create the libc.so symlink: {}", ec.message());
        }
    }
}
#endif

bool AskToTrust(Ship::Archive& archive, Ship::KeystoreEntry& key) {
    const auto& info = archive.GetManifest();

    std::string message = "A mod from an unknown author was found.\n\n";
    message += "Mod: " + info.Name + "\n";
    message += "Author: " + info.Author + "\n\n";
    message += "Mods can run code on your device. Trust this author and load the mod?";

    const SDL_MessageBoxButtonData buttons[] = {
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Yes" },
        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "No" },
    };
    const SDL_MessageBoxData messageBox = {
        SDL_MESSAGEBOX_WARNING,
        nullptr,
        "Untrusted Mod Author",
        message.c_str(),
        SDL_arraysize(buttons),
        buttons,
        nullptr,
    };

    int buttonId = 0;
    if (SDL_ShowMessageBox(&messageBox, &buttonId) < 0) {
        return false;
    }
    return buttonId == 1;
}

} // namespace

bool ModScripts::Supported() {
    return true;
}

void ModScripts::Setup() {
    auto context = Ship::Context::GetRawInstance();
    if (context->GetScriptLoader() != nullptr) {
        return;
    }

    // The defines the game itself is built with, so mods see the same headers.
    std::unordered_map<std::string, std::string> defines = {
        { "PORT", "1" },        { "MODERN_COMPILER", "1" }, { "VERSION", "us" },    { "VERSION_US", "1" },
        { "F3DEX_GBI_2", "1" }, { "__CTX__", "1" },         { "_LANGUAGE_C", "1" }, { "_USE_MATH_DEFINES", "1" },
    };

    const std::string tccBase = TccBase();
    std::vector<std::string> includePaths = { tccBase + "/include" };
    std::vector<std::string> libraryPaths = { tccBase + "/lib" };
    std::vector<std::string> libraries;

#if defined(_WIN32)
    const std::string buildOptions = "-g -rdynamic -funsigned-char -std=c11";
    for (const char* dir : { "/include/winapi", "/include/sys", "/include/sec_api" }) {
        includePaths.push_back(tccBase + dir);
    }
    // The game's exports, from the .def file staged next to libtcc1.
    libraries.push_back("Paperboat");
#elif defined(__ANDROID__)
    defines["__ANDROID_MIN_SDK_VERSION__"] = std::to_string(__ANDROID_MIN_SDK_VERSION__);
    defines["__ANDROID_API__"] = std::to_string(__ANDROID_API__);
    const std::string buildOptions = "-nostdlib -funsigned-char -std=c11";
    libraryPaths.push_back(OwnLibraryDir());
    libraries = { "tcc1", "main" };
#else
    const std::string buildOptions = "-rdynamic -funsigned-char -std=c11";
#endif

#if defined(__APPLE__)
    // TinyCC ships no libc headers; the macOS SDK has them.
    if (FILE* fp = popen("xcrun --show-sdk-path 2>/dev/null", "r")) {
        char buf[4096] = {};
        if (fgets(buf, sizeof(buf), fp)) {
            std::string sdkPath(buf);
            sdkPath.erase(sdkPath.find_last_not_of("\n\r \t") + 1);
            if (!sdkPath.empty()) {
                includePaths.push_back(sdkPath + "/usr/include");
            }
        }
        pclose(fp);
    }
#elif defined(__linux__) && !defined(__ANDROID__)
    LinkLibcStub(tccBase);
#endif

    context->InitKeystore();
    context->InitScriptLoader(defines, PB_CODE_VERSION, buildOptions, includePaths, libraryPaths, libraries);

    auto scripts = context->GetScriptLoader();
    scripts->SetApiVersion(PB_API_VERSION);
    scripts->SetEntryHook([](const std::string& name, const std::string& symbol, Ship::Scripting::LibraryFunc_t entry) {
        if (entry != nullptr) {
            ModOwner::Scope scope(name);
            entry();
        }
        if (symbol == "ModExit") {
            ModOwner::Release(name);
        }
    });

    GetArchiveManager()->SetUntrustedArchiveHandler(AskToTrust);
}

size_t ModScripts::Count() {
    size_t count = 0;
    const auto archives = GetArchiveManager()->GetArchives();
    for (const auto& archive : *archives) {
        count += ShipsCode(archive) ? 1 : 0;
    }
    return count;
}

std::vector<std::string>
ModScripts::Compile(const std::function<void(const std::string&)>& onStart, const std::function<void()>& onFinish) {
    std::vector<std::string> errors;
    auto scripts = Ship::Context::GetRawInstance()->GetScriptLoader();
    if (scripts == nullptr) {
        return errors;
    }

    sStatus.clear();
    const auto archives = GetArchiveManager()->GetArchives();
    for (const auto& archive : *archives) {
        if (!ShipsCode(archive)) {
            continue;
        }
        const auto& info = archive->GetManifest();
        auto& status = sStatus[archive->GetPath()];
        status.signedArchive = archive->IsSigned() && archive->IsChecksumValid();

        if (onStart) {
            onStart(info.Name);
        }
        try {
            scripts->Compile(archive);
        } catch (const std::exception& e) {
            SPDLOG_ERROR("Failed to build {}: {}", info.Name, e.what());
            errors.push_back(info.Name + ": " + e.what());
            status.text = std::string("Failed to build: ") + e.what();
            status.failed = true;
        }
        if (onFinish) {
            onFinish();
        }
    }
    return errors;
}

void ModScripts::Load() {
    std::lock_guard<std::recursive_mutex> lock(Lock());
    auto scripts = Ship::Context::GetRawInstance()->GetScriptLoader();
    if (scripts == nullptr) {
        return;
    }

    try {
        scripts->LoadAll();
    } catch (const std::exception& e) {
        SPDLOG_ERROR("Failed to load mods: {}", e.what());
        Notification::Emit(
            { .message = "Failed to load some mods, check the logs for details.",
              .messageColor = kErrorColor,
              .remainingTime = 8.0f,
              .mute = true }
        );
        return;
    }

    for (const auto& error : scripts->GetLoadErrors()) {
        const size_t split = error.find(": ");
        if (split != std::string::npos) {
            SetStatus(error.substr(0, split), "Skipped: " + error.substr(split + 2), true);
        }
        Notification::Emit(
            { .message = "Skipped " + error, .messageColor = kErrorColor, .remainingTime = 8.0f, .mute = true }
        );
    }
    for (auto& [path, status] : sStatus) {
        if (status.text.empty()) {
            status.text = "Loaded";
        }
    }
}

void ModScripts::Unload() {
    std::lock_guard<std::recursive_mutex> lock(Lock());
    if (auto scripts = Ship::Context::GetRawInstance()->GetScriptLoader()) {
        scripts->UnloadAll();
    }
}

void ModScripts::Reload() {
    std::lock_guard<std::recursive_mutex> lock(Lock());
    Unload();
    for (const auto& error : Compile()) {
        Notification::Emit(
            { .message = "Failed to build " + error, .messageColor = kErrorColor, .remainingTime = 8.0f, .mute = true }
        );
    }
    Load();
    Notification::Emit({ .message = "Reloaded mod scripts", .remainingTime = 3.0f, .mute = true });
}

void ModScripts::RequestReload() {
    sReloadRequested = true;
}

const ModScripts::Status* ModScripts::GetStatus(const std::string& archivePath) {
    auto it = sStatus.find(archivePath);
    return it != sStatus.end() ? &it->second : nullptr;
}

extern "C" void ModScripts_RunPending(void) {
    if (sReloadRequested.exchange(false)) {
        ModScripts::Reload();
    }
}

#else

bool ModScripts::Supported() {
    return false;
}

void ModScripts::Setup() {
}

size_t ModScripts::Count() {
    return 0;
}

std::vector<std::string>
ModScripts::Compile(const std::function<void(const std::string&)>&, const std::function<void()>&) {
    return {};
}

void ModScripts::Load() {
}

void ModScripts::Unload() {
}

void ModScripts::Reload() {
}

void ModScripts::RequestReload() {
}

const ModScripts::Status* ModScripts::GetStatus(const std::string&) {
    return nullptr;
}

extern "C" void ModScripts_RunPending(void) {
}

#endif
