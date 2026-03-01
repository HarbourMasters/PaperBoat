#include "Engine.h"

#include <cstdarg>
#include <fstream>
#include <mutex>
#include <unordered_map>
#include <libultraship.h>
#include <ship/resource/factory/BlobFactory.h>
#include <libultraship/controller/controldeck/ControlDeck.h>
#include <fast/Fast3dWindow.h>
#include <fast/interpreter.h>
#include <fast/resource/factory/TextureFactory.h>
#include <fast/resource/factory/DisplayListFactory.h>
#include <fast/resource/factory/VertexFactory.h>
#include <fast/resource/factory/LightFactory.h>
#include <fast/resource/factory/MatrixFactory.h>
#include <fast/resource/ResourceType.h>
#include <filesystem>
#include "src/Companion.h"
#include "factories/PM64SpriteFactory.h"
#include "factories/PM64ShapeFactory.h"
#include "factories/PM64BackgroundFactory.h"
#include "factories/PM64TextureFactory.h"
#include "factories/PM64CollisionFactory.h"
#include "factories/PM64MapTextureFactory.h"
#include "factories/PM64AudioFactory.h"
#include "factories/PM64StoryImageFactory.h"
#include "factories/PM64ImgFXAnimFactory.h"
#include "factories/PM64TitleDataFactory.h"
#include "factories/PM64EntityGfxFactory.h"
#include "factories/PM64EffectDListFactory.h"
#include "factories/PM64VertexFactory.h"

namespace fs = std::filesystem;

std::vector<uint8_t*> MemoryPool;
GameEngine* GameEngine::Instance;

// Static audio thread state definition
decltype(GameEngine::mAudio) GameEngine::mAudio;

// Game audio system functions and globals
extern "C" {
    void nuScCreateScheduler(uint8_t mode, uint8_t numFields);
    void create_audio_system(void);
    Acmd* alAudioFrame(Acmd* cmdList, int32_t* cmdLen, int16_t* outBuf, int32_t outLen);
    extern int32_t AlFrameSize;
}

// Audio constants from game
#define AUDIO_SAMPLES 184
#define HARDWARE_OUTPUT_RATE 32000

// Thread-local context for display list debugging
static thread_local const char* gDisplayListContext = nullptr;

// Access to the display list pointer for emitting context markers
// Gfx is already defined in libultraship's gbi.h (included via libultraship.h)
extern "C" {
    extern Gfx* gMainGfxPos;
}

static void ExtractAssets(const std::string& romPath, const std::string& outputPath) {
    std::ifstream file(romPath, std::ios::binary);
    std::vector<uint8_t> romData(std::istreambuf_iterator<char>(file), {});
    file.close();

    std::string assetsDir = Ship::Context::GetAppBundlePath();
    std::string destDir = Ship::Context::GetAppDirectoryPath();

    Companion::Instance = new Companion(romData, ArchiveType::O2R, false, assetsDir, destDir);

    // Register PM64-specific factories before Init()
    Companion::Instance->RegisterFactory("PM64:SPRITE", std::make_shared<PM64SpriteFactory>());
    Companion::Instance->RegisterFactory("PM64:SHAPE", std::make_shared<PM64ShapeFactory>());
    Companion::Instance->RegisterFactory("PM64:BACKGROUND", std::make_shared<PM64BackgroundFactory>());
    Companion::Instance->RegisterFactory("PM64:COLLISION", std::make_shared<PM64CollisionFactory>());
    Companion::Instance->RegisterFactory("PM64:MAP_TEXTURE", std::make_shared<PM64MapTextureFactory>());
    Companion::Instance->RegisterFactory("PM64:AUDIO", std::make_shared<PM64AudioFactory>());
    Companion::Instance->RegisterFactory("PM64:STORY_IMAGE", std::make_shared<PM64StoryImageFactory>());
    Companion::Instance->RegisterFactory("PM64:IMGFX_ANIM", std::make_shared<PM64ImgFXAnimFactory>());
    Companion::Instance->RegisterFactory("PM64:TITLE_DATA", std::make_shared<PM64TitleDataFactory>());
    Companion::Instance->RegisterFactory("PM64:ENTITY_GFX", std::make_shared<PM64EntityGfxFactory>());
    Companion::Instance->RegisterFactory("PM64:EFFECT_DL", std::make_shared<PM64EffectDListFactory>());

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

    const std::string hd_path = Ship::Context::GetPathRelativeToAppDirectory("starrod.o2r");
    if (std::filesystem::exists(hd_path)) {
        SPDLOG_INFO("Loading HD asset archive: starrod.o2r");
        archiveFiles.push_back(hd_path);
    }

    const std::string mods_path = Ship::Context::GetPathRelativeToAppDirectory("mods");
    if (std::filesystem::exists(mods_path) && std::filesystem::is_directory(mods_path)) {
        std::vector<std::string> mod_archives;
        for (const auto& entry : std::filesystem::directory_iterator(mods_path)) {
            const auto ext = entry.path().extension().string();
            if (entry.is_regular_file() && (ext == ".o2r" || ext == ".otr" || ext == ".zip")) {
                mod_archives.push_back(std::filesystem::absolute(entry.path()).string());
            }
        }
        std::sort(mod_archives.begin(), mod_archives.end());
        for (const auto& mod : mod_archives) {
            SPDLOG_INFO("Loading mod archive: {}", mod);
            archiveFiles.push_back(mod);
        }
    }

    this->context->InitConfiguration();
    this->context->InitConsoleVariables();

    this->context->InitResourceManager(archiveFiles, {}, 3);
    this->context->InitConsole();
    this->context->InitCrashHandler();

    this->context->InitGfxDebugger();

    this->context->InitLogging(spdlog::level::trace, spdlog::level::trace);
    this->context->InitConsoleVariables();

    // ControlDeck is needed by window keyboard callbacks
    auto controlDeck = std::make_shared<LUS::ControlDeck>();
    auto window = std::make_shared<Fast::Fast3dWindow>(std::vector<std::shared_ptr<Ship::GuiWindow>>({}));

    auto audioChannelsSetting = Ship::Context::GetInstance()->GetConfig()->GetCurrentAudioChannelsSetting();
    this->context->Init(archiveFiles, {}, 3, { 32000, 1024, 1680, audioChannelsSetting }, window, controlDeck);

    auto loader = context->GetResourceManager()->GetResourceLoader();
    loader->RegisterResourceFactory(std::make_shared<Ship::ResourceFactoryBinaryBlobV0>(), RESOURCE_FORMAT_BINARY,
                                    "Blob", static_cast<uint32_t>(Ship::ResourceType::Blob), 0);

    // TODO: Use v0 or v1 factory
    loader->RegisterResourceFactory(std::make_shared<PM64::ResourceFactoryBinaryTextureV0>(), RESOURCE_FORMAT_BINARY,
                                    "Texture", static_cast<uint32_t>(Fast::ResourceType::Texture), 0);
    loader->RegisterResourceFactory(std::make_shared<Fast::ResourceFactoryBinaryTextureV1>(), RESOURCE_FORMAT_BINARY,
                                    "Texture", static_cast<uint32_t>(Fast::ResourceType::Texture), 1);
    loader->RegisterResourceFactory(std::make_shared<Fast::ResourceFactoryBinaryDisplayListV0>(), RESOURCE_FORMAT_BINARY,
                                    "DisplayList", static_cast<uint32_t>(Fast::ResourceType::DisplayList), 0);
    loader->RegisterResourceFactory(std::make_shared<Fast::ResourceFactoryBinaryVertexV0>(), RESOURCE_FORMAT_BINARY,
                                    "Vertex", static_cast<uint32_t>(Fast::ResourceType::Vertex), 0);
    loader->RegisterResourceFactory(std::make_shared<ResourceFactoryBinaryVertexV1>(), RESOURCE_FORMAT_BINARY,
                                    "Vertex", static_cast<uint32_t>(Fast::ResourceType::Vertex), 1);
    loader->RegisterResourceFactory(std::make_shared<Fast::ResourceFactoryBinaryLightV0>(), RESOURCE_FORMAT_BINARY,
                                    "Light", static_cast<uint32_t>(Fast::ResourceType::Light), 0);
    loader->RegisterResourceFactory(std::make_shared<Fast::ResourceFactoryBinaryMatrixV0>(), RESOURCE_FORMAT_BINARY,
                                    "Matrix", static_cast<uint32_t>(Fast::ResourceType::Matrix), 0);

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
    // Process window events (keyboard/mouse/gamepad) BEFORE game logic reads input.
    // This fires the keyboard callbacks that set mKeyPressed state in ControlDeck,
    // so that WriteToPad() sees current key state when called from update_input().
    this->context->GetWindow()->HandleEvents();

    const bool altAssets = CVarGetInteger("gEnhancements.Mods.AlternateAssets", 0) != 0;
    if (altAssets != mPrevAltAssets) {
        mPrevAltAssets = altAssets;
        context->GetResourceManager()->SetAltAssetsEnabled(altAssets);
        gfx_texture_cache_clear();
        SPDLOG_INFO("Alt assets {}", altAssets ? "enabled" : "disabled");
    }

    using Ship::KbScancode;
    const int32_t dwScancode = this->context->GetWindow()->GetLastScancode();
    this->context->GetWindow()->SetLastScancode(-1);

    switch (dwScancode) {
        case KbScancode::LUS_KB_TAB: {
            CVarSetInteger("gEnhancements.Mods.AlternateAssets",
                           !CVarGetInteger("gEnhancements.Mods.AlternateAssets", 0));
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
    int16_t audioBuffer[AUDIO_SAMPLES * 4 * 2];
    Acmd cmdList[0x800];

    while (mAudio.running) {
        {
            std::unique_lock<std::mutex> lock(mAudio.mutex);
            while (!mAudio.processing && mAudio.running) {
                mAudio.cv_to_thread.wait(lock);
            }
            if (!mAudio.running) break;
        }

        // Generate audio twice per game frame, matching N64's 60Hz audio thread.
        // On N64, nuAuMgr wakes every VI retrace (60Hz) and generates AlFrameSize
        // (~552) samples. The game loop runs at 30fps → 2 audio frames per game frame.
        // This ensures au_update_clients_for_video_frame() runs at the correct 60Hz.
        for (int pass = 0; pass < 2; pass++) {
            int samplesToGen = AlFrameSize;

            memset(audioBuffer, 0, samplesToGen * 2 * sizeof(int16_t));
            int32_t cmdLen = 0;
            alAudioFrame(cmdList, &cmdLen, audioBuffer, samplesToGen);

            size_t bufferSize = samplesToGen * 2 * sizeof(int16_t);
            AudioPlayerPlayFrame((uint8_t*)audioBuffer, bufferSize);
        }

        {
            std::unique_lock<std::mutex> lock(mAudio.mutex);
            mAudio.processing = false;
        }
        mAudio.cv_from_thread.notify_one();
    }
}

void GameEngine::StartAudioFrame() {
    if (!mAudio.running) return;

    {
        std::unique_lock<std::mutex> lock(mAudio.mutex);
        mAudio.processing = true;
    }
    mAudio.cv_to_thread.notify_one();
}

void GameEngine::EndAudioFrame() {
    if (!mAudio.running) return;

    std::unique_lock<std::mutex> lock(mAudio.mutex);
    while (mAudio.processing) {
        mAudio.cv_from_thread.wait(lock);
    }
}

void GameEngine::AudioInit() {
    SPDLOG_INFO("Initializing audio system...");

    // NTSC: retraceCount=1 → AlFrameSize=552 (3 chunks of 184 samples)
    // Must be set before create_audio_system() which reads nusched.retraceCount
    nuScCreateScheduler(0, 1);

    // Initialize the game's audio system
    create_audio_system();

    // Start the audio thread
    mAudio.running = true;
    mAudio.processing = false;
    mAudio.thread = std::thread(&GameEngine::HandleAudioThread);

    SPDLOG_INFO("Audio system initialized");
}

void GameEngine::AudioExit() {
    if (mAudio.running) {
        SPDLOG_INFO("Shutting down audio system...");

        // Signal thread to stop
        {
            std::unique_lock<std::mutex> lock(mAudio.mutex);
            mAudio.running = false;
            mAudio.processing = true;  // Wake up the thread
        }
        mAudio.cv_to_thread.notify_one();

        // Wait for thread to finish
        if (mAudio.thread.joinable()) {
            mAudio.thread.join();
        }

        SPDLOG_INFO("Audio system shut down");
    }
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

void GameEngine::ProcessGfxCommands(Gfx* commands) {
    auto wnd = std::dynamic_pointer_cast<Fast::Fast3dWindow>(
        Ship::Context::GetInstance()->GetWindow());

    if (wnd == nullptr) return;

    // Set microcode handler
    wnd->SetRendererUCode(UcodeHandlers::ucode_f3dex2);

    // Build matrix replacements for interpolation
    std::vector<std::unordered_map<Mtx*, MtxF>> mtx_replacements;

    // For now, just one pass (no interpolation)
    // Later: Generate multiple matrix sets for 30fps->60fps or 60fps->120fps
    mtx_replacements.push_back({});

    RunCommands(commands, mtx_replacements);
}

static const char* sOtrSignature = "__OTR__";

extern "C" uint8_t GameEngine_OTRSigCheck(const char* data) {
    if (data == nullptr) {
        return 0;
    }
    // Guard against small integers masquerading as pointers.
    // This happens when N64 code computes addresses from NULL-based buffers
    // (e.g. nuGfxZBuffer is NULL on the port, so &nuGfxZBuffer[offset] yields
    // a small integer that would crash strncmp).
    if ((uintptr_t)data < 0x10000) {
        return 0;
    }
    return strncmp(data, sOtrSignature, strlen(sOtrSignature)) == 0;
}

// C-callable audio frame hooks
extern "C" void GameEngine_StartAudioFrame(void) {
    GameEngine::StartAudioFrame();
}

extern "C" void GameEngine_EndAudioFrame(void) {
    GameEngine::EndAudioFrame();
}

// C-callable wrapper for processing graphics commands
extern "C" void GameEngine_ProcessGfxCommands(Gfx* commands) {
    std::vector<std::unordered_map<Mtx*, MtxF>> mtx_replacements;
    mtx_replacements.push_back({});  // Empty map for now, interpolation can be added later
    GameEngine::RunCommands(commands, mtx_replacements);
}

// C-callable controller input reader
extern "C" void GameEngine_ReadController(OSContPad* pads) {
    auto controlDeck = Ship::Context::GetInstance()->GetControlDeck();
    if (controlDeck != nullptr) {
        controlDeck->WriteToPad(pads);
    }
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

// C-callable display list context tracking for debugging
// This emits a G_NOOP marker command into the display list so the context
// survives from construction time to execution time in the interpreter.
extern "C" void GameEngine_SetDisplayListContext(const char* context) {
    gDisplayListContext = context;

    // Emit G_NOOP with p=9 (context marker) into the display list
    // Format: w0 = (G_NOOP << 24) | (p << 16) | l, w1 = context pointer
    // G_NOOP = 0x00 for F3DEX2
    if (gMainGfxPos != nullptr) {
        Gfx* g = gMainGfxPos++;
        g->words.w0 = (0x00 << 24) | (9 << 16) | 0;  // G_NOOP, p=9 (context), l=0
        g->words.w1 = (uintptr_t)context;
    }
}

extern "C" const char* GameEngine_GetDisplayListContext() {
    return gDisplayListContext ? gDisplayListContext : "(unknown)";
}

// Debug check for uninitialized textures - called from gDPSetTextureImage macro
extern "C" void _gbi_debug_check_texture(const void* img, const char* file, int line) {
    if (img == nullptr) {
        SPDLOG_WARN("[GBI DEBUG] NULL texture at {}:{}", file, line);
        return;
    }
    // Check if this is an OTR path
    if (GameEngine_OTRSigCheck((const char*)img)) {
        SPDLOG_INFO("[GBI DEBUG] OTR texture path at {}:{}, path='{}'", file, line, (const char*)img);
        return;
    }
    // Check if first 16 bytes are all zeros
    // Note: This is normal for CI4 textures with transparent regions (palette index 0)
    static const char zeros[16] = {0};
    if (memcmp(img, zeros, 16) == 0) {
        SPDLOG_DEBUG("[GBI DEBUG] Texture starts with 16 zero bytes at {}:{}, addr={} (may be CI4 transparent region)",
                    file, line, img);
    }
}

// Texture debug tracking system - maps memory addresses to source asset paths
// This helps diagnose texture issues by showing which asset file a texture came from
struct TextureDebugInfo {
    std::string assetPath;
    int rasterIdx;
};

static std::mutex sTextureDebugMutex;
static std::unordered_map<uintptr_t, TextureDebugInfo> sTextureDebugRegistry;

extern "C" void GameEngine_RegisterTextureDebugInfo(const void* addr, const char* assetPath, int rasterIdx) {
    if (addr == nullptr || assetPath == nullptr) {
        return;
    }
    std::lock_guard<std::mutex> lock(sTextureDebugMutex);
    sTextureDebugRegistry[reinterpret_cast<uintptr_t>(addr)] = { assetPath, rasterIdx };
}

// Thread-local buffer for returning texture source info
static thread_local char sTextureSourceBuffer[256];

extern "C" const char* GameEngine_LookupTextureSource(const void* addr) {
    if (addr == nullptr) {
        return nullptr;
    }
    std::lock_guard<std::mutex> lock(sTextureDebugMutex);
    auto it = sTextureDebugRegistry.find(reinterpret_cast<uintptr_t>(addr));
    if (it != sTextureDebugRegistry.end()) {
        snprintf(sTextureSourceBuffer, sizeof(sTextureSourceBuffer), "%s (raster %d)",
                 it->second.assetPath.c_str(), it->second.rasterIdx);
        return sTextureSourceBuffer;
    }
    return nullptr;
}

extern "C" void GameEngine_InvalidateTextureCache(const void* addr) {
    if (addr == nullptr) {
        return;
    }
    auto window = Ship::Context::GetInstance()->GetWindow();
    if (window != nullptr) {
        auto fast3d = std::dynamic_pointer_cast<Fast::Fast3dWindow>(window);
        if (fast3d != nullptr) {
            auto interp = fast3d->GetInterpreterWeak().lock();
            if (interp != nullptr) {
                interp->TextureCacheDelete(reinterpret_cast<const uint8_t*>(addr));
            }
        }
    }
}

extern "C" int GameEngine_GetSaveFilePath(char* buf, int bufSize) {
    std::string path = Ship::Context::GetPathRelativeToAppDirectory("default.sav");
    if ((int)path.size() >= bufSize) {
        return -1;
    }
    strncpy(buf, path.c_str(), bufSize);
    buf[bufSize - 1] = '\0';
    return 0;
}

extern "C" int GameEngine_CVarGetInteger(const char* name, int defaultValue) {
    return CVarGetInteger(name, defaultValue);
}

extern "C" void GameEngine_ClearDepthBuffer(void) {
    auto wnd = std::dynamic_pointer_cast<Fast::Fast3dWindow>(Ship::Context::GetInstance()->GetWindow());
    if (wnd) {
        auto interp = wnd->GetInterpreterWeak().lock();
        if (interp) {
            interp->GetCurrentRenderingAPI()->ClearFramebuffer(false, true);
        }
    }
}
