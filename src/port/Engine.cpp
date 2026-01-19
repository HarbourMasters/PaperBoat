#include "Engine.h"

#include <libultraship.h>
#include <libultraship/controller/controldeck/ControlDeck.h>
#include <fast/Fast3dWindow.h>
#include <fast/interpreter.h>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<uint8_t*> MemoryPool;
GameEngine* GameEngine::Instance;

GameEngine::GameEngine() {
    this->context = Ship::Context::CreateUninitializedInstance("StarRod", "ship", "starrod.cfg.json");

    std::vector<std::string> archiveFiles;
    const std::string main_path = Ship::Context::GetPathRelativeToAppDirectory("pm64.o2r");
    const std::string assets_path = Ship::Context::LocateFileAcrossAppDirs("starrod.o2r");

#ifdef _WIN32
    AllocConsole();
#endif

    if (std::filesystem::exists(main_path)) {
        archiveFiles.push_back(main_path);
    } else {
        // Log
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
//    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryAnimV0>(), RESOURCE_FORMAT_BINARY,
//                                    "Animation", static_cast<uint32_t>(SF64::ResourceType::AnimData), 0);

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
