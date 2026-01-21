#include "Engine.h"

#include <cstdarg>
#include <fstream>
#include <libultraship.h>
#include <ship/resource/factory/BlobFactory.h>
#include <libultraship/controller/controldeck/ControlDeck.h>
#include <fast/Fast3dWindow.h>
#include <fast/interpreter.h>
#include <fast/resource/factory/TextureFactory.h>
#include <fast/resource/ResourceType.h>
#include <filesystem>
#include "src/Companion.h"
#include "factories/PM64SpriteFactory.h"
#include "factories/PM64TextureFactory.h"

namespace fs = std::filesystem;

std::vector<uint8_t*> MemoryPool;
GameEngine* GameEngine::Instance;

static void ExtractAssets(const std::string& romPath, const std::string& outputPath) {
    std::ifstream file(romPath, std::ios::binary);
    std::vector<uint8_t> romData(std::istreambuf_iterator<char>(file), {});
    file.close();

    std::string assetsDir = Ship::Context::GetAppBundlePath();
    std::string destDir = Ship::Context::GetAppDirectoryPath();

    Companion::Instance = new Companion(romData, ArchiveType::O2R, false, assetsDir, destDir);

    // Register PM64-specific factories before Init()
    Companion::Instance->RegisterFactory("PM64:SPRITE", std::make_shared<PM64SpriteFactory>());

    Companion::Instance->Init(ExportType::Binary);
}

GameEngine::GameEngine() {
    this->context = Ship::Context::CreateUninitializedInstance("StarRod", "ship", "starrod.cfg.json");

    std::vector<std::string> archiveFiles;
    const std::string main_path = Ship::Context::GetPathRelativeToAppDirectory("pm64.o2r");
    const std::string assets_path = Ship::Context::LocateFileAcrossAppDirs("f3d.o2r");

#ifdef _WIN32
    AllocConsole();
#endif

    if (std::filesystem::exists(main_path)) {
        archiveFiles.push_back(main_path);
    } else {
        const std::string rom_path = Ship::Context::GetPathRelativeToAppDirectory("baserom.z64");
        if (std::filesystem::exists(rom_path)) {
            SPDLOG_INFO("Extracting assets from baserom.z64...");
            ExtractAssets(rom_path, main_path);
            archiveFiles.push_back(main_path);
        } else {
            SPDLOG_ERROR("pm64.o2r not found and baserom.z64 not present. Cannot continue.");
            exit(1);
        }
    }

    if (std::filesystem::exists(assets_path)) {
        archiveFiles.push_back(assets_path);
    } else {
        // Log
    }

    this->context->InitConfiguration();
    this->context->InitConsoleVariables();

    this->context->InitResourceManager(archiveFiles, {}, 3);
    this->context->InitConsole();
    this->context->InitCrashHandler();

    this->context->InitGfxDebugger();

    this->context->InitLogging();
    this->context->InitConsoleVariables();

    // ControlDeck is needed by window keyboard callbacks
    auto controlDeck = std::make_shared<LUS::ControlDeck>();
    auto window = std::make_shared<Fast::Fast3dWindow>(std::vector<std::shared_ptr<Ship::GuiWindow>>({}));

    auto audioChannelsSetting = Ship::Context::GetInstance()->GetConfig()->GetCurrentAudioChannelsSetting();
    this->context->Init(archiveFiles, {}, 3, { 32000, 1024, 1680, audioChannelsSetting }, window, controlDeck);

    auto loader = context->GetResourceManager()->GetResourceLoader();
    loader->RegisterResourceFactory(std::make_shared<Ship::ResourceFactoryBinaryBlobV0>(), RESOURCE_FORMAT_BINARY,
                                    "Blob", static_cast<uint32_t>(Ship::ResourceType::Blob), 0);
    loader->RegisterResourceFactory(std::make_shared<PM64::ResourceFactoryBinaryTextureV0>(), RESOURCE_FORMAT_BINARY,
                                    "Texture", static_cast<uint32_t>(Fast::ResourceType::Texture), 0);

}

bool GameEngine::GenAssetFile(bool exitOnFail) {
    return false;
}

void GameEngine::Create() {
    const auto instance = Instance = new GameEngine();
    instance->AudioInit();
//    DisplayListPatch::Run();
}

void GameEngine::Destroy() {
    AudioExit();
    for (auto ptr : MemoryPool) {
        free(ptr);
    }
    MemoryPool.clear();
}

void GameEngine::StartFrame() const {
    using Ship::KbScancode;
    const int32_t dwScancode = this->context->GetWindow()->GetLastScancode();
    this->context->GetWindow()->SetLastScancode(-1);

    switch (dwScancode) {
        case KbScancode::LUS_KB_TAB: {
            // Toggle HD Assets
            //CVarSetInteger("gEnhancements.Mods.AlternateAssets", !CVarGetInteger("gEnhancements.Mods.AlternateAssets", 0));
            break;
        }
        case KbScancode::LUS_KB_F4: {
            //gNextGameState = GSTATE_BOOT;
            break;
        }
        default:
            break;
    }
}

void GameEngine::HandleAudioThread() {
}

void GameEngine::StartAudioFrame() {
}

void GameEngine::EndAudioFrame() {
}

void GameEngine::AudioInit() {
}

void GameEngine::AudioExit() {
}

void GameEngine::RunCommands(Gfx* Commands, const std::vector<std::unordered_map<Mtx*, MtxF>>& mtx_replacements) {
    auto wnd = std::dynamic_pointer_cast<Fast::Fast3dWindow>(Ship::Context::GetInstance()->GetWindow());

    if (wnd == nullptr) {
        return;
    }

    auto interpreter = wnd->GetInterpreterWeak().lock().get();

    // Process window events for resize, mouse, keyboard events
    wnd->HandleEvents();

    interpreter->mInterpolationIndex = 0;

    for (const auto& m : mtx_replacements) {
        wnd->DrawAndRunGraphicsCommands(Commands, m);
        interpreter->mInterpolationIndex++;
    }
}

static const char* sOtrSignature = "__OTR__";

extern "C" uint8_t GameEngine_OTRSigCheck(const char* data) {
    if (data == nullptr) {
        return 0;
    }
    return strncmp(data, sOtrSignature, strlen(sOtrSignature)) == 0;
}

// C-callable wrapper for processing graphics commands
extern "C" void GameEngine_ProcessGfxCommands(Gfx* commands) {
    std::vector<std::unordered_map<Mtx*, MtxF>> mtx_replacements;
    mtx_replacements.push_back({});  // Empty map for now, interpolation can be added later
    GameEngine::RunCommands(commands, mtx_replacements);
}

// C-callable memory allocator
extern "C" void* GameEngine_Malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr != nullptr) {
        MemoryPool.push_back((uint8_t*)ptr);
    }
    return ptr;
}

// C-callable logging using spdlog
extern "C" void GameEngine_LogInfo(const char* fmt, ...) {
    char buffer[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    SPDLOG_INFO("{}", buffer);
}

// C-callable stack trace logging using spdlog
#if defined(__APPLE__) || defined(__linux__)
#include <execinfo.h>
#include <cxxabi.h>
#endif

extern "C" void GameEngine_LogStackTrace(const char* label) {
#if defined(__APPLE__) || defined(__linux__)
    SPDLOG_INFO("Stack trace [{}]:", label ? label : "unnamed");

    void* callstack[32];
    int frames = backtrace(callstack, 32);
    char** symbols = backtrace_symbols(callstack, frames);

    if (symbols) {
        for (int i = 1; i < frames; i++) {  // Skip frame 0 (this function)
            // Try to demangle C++ symbols
            char* symbol = symbols[i];
            char* demangled = nullptr;

            // macOS format: "1   StarRod  0x00000001000abcde _Z12someFunctionv + 42"
            // Try to extract and demangle the symbol name
            char* start = strchr(symbol, '_');
            if (start) {
                char* end = strchr(start, ' ');
                if (end) {
                    size_t len = end - start;
                    char* mangled = (char*)malloc(len + 1);
                    strncpy(mangled, start, len);
                    mangled[len] = '\0';

                    int status;
                    demangled = abi::__cxa_demangle(mangled, nullptr, nullptr, &status);
                    free(mangled);
                }
            }

            if (demangled) {
                SPDLOG_INFO("  [{}] {}", i, demangled);
                free(demangled);
            } else {
                SPDLOG_INFO("  [{}] {}", i, symbol);
            }
        }
        free(symbols);
    }
#else
    SPDLOG_INFO("Stack trace [{}]: (not available on this platform)", label ? label : "unnamed");
#endif
}
