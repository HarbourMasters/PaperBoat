#include "Engine.h"

#include "ShipInit.hpp"
#include "importer/PM64TextureFactory.h"
#include "port/enhancements/PortEnhancements.h"
#include "port/ui/cvar_prefixes.h"
#include "src/Companion.h"
#include "ui/PaperboatGui.hpp"
#include <cstdarg>
#include <fast/Fast3dWindow.h>
#include <fast/interpreter.h>
#include <fast/resource/ResourceType.h>
#include <fast/resource/factory/DisplayListFactory.h>
#include <fast/resource/factory/LightFactory.h>
#include <fast/resource/factory/MatrixFactory.h>
#include <fast/resource/factory/TextureFactory.h>
#include <fast/resource/factory/VertexFactory.h>
#include <filesystem>
#include <fstream>
#include <libultraship.h>
#include <libultraship/controller/controldeck/ControlDeck.h>
#include <mutex>
#include <ship/resource/factory/BlobFactory.h>
#include <ship/window/gui/Fonts.h>
#include <ship/window/gui/resource/Font.h>
#include <unordered_map>

const float imguiScaleOptionToValue[4] = {0.75f, 1.0f, 1.5f, 2.0f};
std::shared_ptr<Fast::Fast3dWindow> gsFast3dWindow;
const uint32_t defaultImGuiScale = 1;
int32_t previousImGuiScaleIndex = -1;
float previousImGuiScale = defaultImGuiScale;

namespace fs = std::filesystem;

std::vector<uint8_t *> MemoryPool;
GameEngine *GameEngine::Instance;

// Static audio thread state definition
decltype(GameEngine::mAudio) GameEngine::mAudio;

// Game audio system functions and globals
extern "C" {
void nuScCreateScheduler(uint8_t mode, uint8_t numFields);
void create_audio_system(void);
Acmd *alAudioFrame(Acmd *cmdList, int32_t *cmdLen, int16_t *outBuf,
                   int32_t outLen);
extern int32_t AlFrameSize;
}

// Audio constants from game
#define AUDIO_SAMPLES 184
#define HARDWARE_OUTPUT_RATE 32000

// Access to the display list pointer for emitting context markers
// Gfx is already defined in libultraship's gbi.h (included via libultraship.h)
extern "C" {
extern Gfx *gMainGfxPos;
}

static void ExtractAssets(const std::string &romPath,
                          const std::string &outputPath) {
  std::ifstream file(romPath, std::ios::binary);
  std::vector<uint8_t> romData(std::istreambuf_iterator<char>(file), {});
  file.close();

  std::string assetsDir = Ship::Context::GetAppBundlePath();
  std::string destDir = Ship::Context::GetAppDirectoryPath();

  Companion::Instance =
      new Companion(romData, ArchiveType::O2R, false, assetsDir, destDir);
  Companion::Instance->Init(ExportType::Binary);
}

GameEngine::GameEngine() {
  this->context = Ship::Context::CreateUninitializedInstance(
      "StarRod", "ship", "starrod.cfg.json");

  std::vector<std::string> archiveFiles;
  const std::string main_path =
      Ship::Context::GetPathRelativeToAppDirectory("pm64.o2r");
  const std::string assets_path =
      Ship::Context::LocateFileAcrossAppDirs("paperboat.o2r");

#ifdef _WIN32
  AllocConsole();
#endif

  if (std::filesystem::exists(main_path)) {
    archiveFiles.push_back(main_path);
  } else {
    const std::string rom_path =
        Ship::Context::GetPathRelativeToAppDirectory("baserom.z64");
    if (std::filesystem::exists(rom_path)) {
      SPDLOG_INFO("Extracting assets from baserom.z64...");
      ExtractAssets(rom_path, main_path);
      archiveFiles.push_back(main_path);
    } else {
      SPDLOG_ERROR(
          "pm64.o2r not found and baserom.z64 not present. Cannot continue.");
      exit(1);
    }
  }

  if (std::filesystem::exists(assets_path)) {
    archiveFiles.push_back(assets_path);
  } else {
    // Log
  }

  const std::string hd_path =
      Ship::Context::GetPathRelativeToAppDirectory("starrod.o2r");
  if (std::filesystem::exists(hd_path)) {
    SPDLOG_INFO("Loading HD asset archive: starrod.o2r");
    archiveFiles.push_back(hd_path);
  }

  const std::string mods_path =
      Ship::Context::GetPathRelativeToAppDirectory("mods");
  if (std::filesystem::exists(mods_path) &&
      std::filesystem::is_directory(mods_path)) {
    std::vector<std::string> mod_archives;
    for (const auto &entry : std::filesystem::directory_iterator(mods_path)) {
      const auto ext = entry.path().extension().string();
      if (entry.is_regular_file() &&
          (ext == ".o2r" || ext == ".otr" || ext == ".zip")) {
        mod_archives.push_back(
            std::filesystem::absolute(entry.path()).string());
      }
    }
    std::sort(mod_archives.begin(), mod_archives.end());
    for (const auto &mod : mod_archives) {
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
  auto window = std::make_shared<Fast::Fast3dWindow>(
      std::vector<std::shared_ptr<Ship::GuiWindow>>({}));

  auto audioChannelsSetting = Ship::Context::GetInstance()
                                  ->GetConfig()
                                  ->GetCurrentAudioChannelsSetting();
  this->context->Init(archiveFiles, {}, 3,
                      {32000, 1024, 1680, audioChannelsSetting}, window,
                      controlDeck);

  auto loader = context->GetResourceManager()->GetResourceLoader();
  loader->RegisterResourceFactory(
      std::make_shared<Ship::ResourceFactoryBinaryBlobV0>(),
      RESOURCE_FORMAT_BINARY, "Blob",
      static_cast<uint32_t>(Ship::ResourceType::Blob), 0);

  // TODO: Use v0 or v1 factory
  loader->RegisterResourceFactory(
      std::make_shared<PM64::ResourceFactoryBinaryTextureV0>(),
      RESOURCE_FORMAT_BINARY, "Texture",
      static_cast<uint32_t>(Fast::ResourceType::Texture), 0);
  loader->RegisterResourceFactory(
      std::make_shared<Fast::ResourceFactoryBinaryTextureV1>(),
      RESOURCE_FORMAT_BINARY, "Texture",
      static_cast<uint32_t>(Fast::ResourceType::Texture), 1);
  loader->RegisterResourceFactory(
      std::make_shared<Fast::ResourceFactoryBinaryDisplayListV0>(),
      RESOURCE_FORMAT_BINARY, "DisplayList",
      static_cast<uint32_t>(Fast::ResourceType::DisplayList), 0);
  loader->RegisterResourceFactory(
      std::make_shared<Fast::ResourceFactoryBinaryVertexV0>(),
      RESOURCE_FORMAT_BINARY, "Vertex",
      static_cast<uint32_t>(Fast::ResourceType::Vertex), 0);
  loader->RegisterResourceFactory(
      std::make_shared<Fast::ResourceFactoryBinaryLightV0>(),
      RESOURCE_FORMAT_BINARY, "Light",
      static_cast<uint32_t>(Fast::ResourceType::Light), 0);
  loader->RegisterResourceFactory(
      std::make_shared<Fast::ResourceFactoryBinaryMatrixV0>(),
      RESOURCE_FORMAT_BINARY, "Matrix",
      static_cast<uint32_t>(Fast::ResourceType::Matrix), 0);

  PaperboatGui::SetupMenu();

  if (std::filesystem::exists(assets_path)) {
    fontMono = CreateFontWithSize(16.0f, "fonts/Inconsolata-Regular.ttf");
    fontMonoLarger = CreateFontWithSize(20.0f, "fonts/Inconsolata-Regular.ttf");
    fontMonoLargest =
        CreateFontWithSize(24.0f, "fonts/Inconsolata-Regular.ttf");
    fontStandard = CreateFontWithSize(16.0f, "fonts/Montserrat-Regular.ttf");
    fontStandardLarger =
        CreateFontWithSize(20.0f, "fonts/Montserrat-Regular.ttf");
    fontStandardLargest =
        CreateFontWithSize(24.0f, "fonts/Montserrat-Regular.ttf");
    ImGui::GetIO().FontDefault = fontStandardLarger;
  }

  previousImGuiScaleIndex = -1;
  previousImGuiScale = defaultImGuiScale;
  ScaleImGui();

  PaperboatGui::SetupGuiElements();
  PortEnhancements_Init();
  ShipInit::InitAll();
}

bool GameEngine::GenAssetFile(bool exitOnFail) { return false; }

ImFont *GameEngine::CreateFontWithSize(float size, std::string fontPath) {
  auto mImGuiIo = &ImGui::GetIO();
  ImFont *font;
  if (fontPath == "") {
    ImFontConfig fontCfg = ImFontConfig();
    fontCfg.OversampleH = fontCfg.OversampleV = 1;
    fontCfg.PixelSnapH = true;
    fontCfg.SizePixels = size;
    font = mImGuiIo->Fonts->AddFontDefault(&fontCfg);
  } else {
    auto initData = std::make_shared<Ship::ResourceInitData>();
    ImFontConfig config;
    config.FontDataOwnedByAtlas = false;

    initData->Format = RESOURCE_FORMAT_BINARY;
    initData->Type = static_cast<uint32_t>(RESOURCE_TYPE_FONT);
    initData->ResourceVersion = 0;
    initData->Path = fontPath;
    std::shared_ptr<Ship::Font> fontData = std::static_pointer_cast<Ship::Font>(
        Ship::Context::GetInstance()->GetResourceManager()->LoadResource(
            fontPath, false, initData));
    font = mImGuiIo->Fonts->AddFontFromMemoryTTF(
        fontData->Data, fontData->DataSize, size, &config);
  }
  // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to
  // align correctly
  float iconFontSize = size * 2.0f / 3.0f;
  static const ImWchar sIconsRanges[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};
  ImFontConfig iconsConfig;
  iconsConfig.MergeMode = true;
  iconsConfig.PixelSnapH = true;
  iconsConfig.GlyphMinAdvanceX = iconFontSize;
  mImGuiIo->Fonts->AddFontFromMemoryCompressedBase85TTF(
      fontawesome_compressed_data_base85, iconFontSize, &iconsConfig,
      sIconsRanges);

  return font;
}

void GameEngine::ScaleImGui() {
  int32_t imGuiScaleIndex =
      CVarGetInteger("gSettings.ImGuiScale", defaultImGuiScale);
  if (imGuiScaleIndex == previousImGuiScaleIndex) {
    return;
  }

  float scale = imguiScaleOptionToValue[imGuiScaleIndex];
  float newScale = scale / previousImGuiScale;
  ImGui::GetStyle().ScaleAllSizes(newScale);
  ImGui::GetIO().FontGlobalScale = scale;
  previousImGuiScale = scale;
  previousImGuiScaleIndex = imGuiScaleIndex;
}

void GameEngine::Create() {
  const auto instance = Instance = new GameEngine();
  instance->AudioInit();
}

void GameEngine::Destroy() {
  PortEnhancements_Exit();
  AudioExit();
  for (auto ptr : MemoryPool) {
    free(ptr);
  }
  MemoryPool.clear();
}

void GameEngine::StartFrame() const {
  // Process window events (keyboard/mouse/gamepad) BEFORE game logic reads
  // input. This fires the keyboard callbacks that set mKeyPressed state in
  // ControlDeck, so that WriteToPad() sees current key state when called from
  // update_input().
  this->context->GetWindow()->HandleEvents();

  const bool altAssets =
      CVarGetInteger("gEnhancements.Mods.AlternateAssets", 0) != 0;
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
    // gNextGameState = GSTATE_BOOT;
    break;
  }
  default:
    break;
  }
}

uint32_t GameEngine::GetInterpolationFPS() {
  if (CVarGetInteger(CVAR_SETTING("MatchRefreshRate"), 0)) {
    return Ship::Context::GetInstance()->GetWindow()->GetCurrentRefreshRate();
  } else if (CVarGetInteger(CVAR_VSYNC_ENABLED, 1) ||
             !Ship::Context::GetInstance()
                  ->GetWindow()
                  ->CanDisableVerticalSync()) {
    return std::min<uint32_t>(
        Ship::Context::GetInstance()->GetWindow()->GetCurrentRefreshRate(),
        CVarGetInteger(CVAR_SETTING("InterpolationFPS"), 30));
  }
  return CVarGetInteger(CVAR_SETTING("InterpolationFPS"), 30);
}

// Audio

void GameEngine::HandleAudioThread() {
  int16_t audioBuffer[AUDIO_SAMPLES * 4 * 2];
  Acmd cmdList[0x800];

  while (mAudio.running) {
    {
      std::unique_lock<std::mutex> lock(mAudio.mutex);
      while (!mAudio.processing && mAudio.running) {
        mAudio.cv_to_thread.wait(lock);
      }
      if (!mAudio.running)
        break;
    }

    // Generate audio twice per game frame, matching N64's 60Hz audio thread.
    // On N64, nuAuMgr wakes every VI retrace (60Hz) and generates AlFrameSize
    // (~552) samples. The game loop runs at 30fps → 2 audio frames per game
    // frame. This ensures au_update_clients_for_video_frame() runs at the
    // correct 60Hz
    for (int pass = 0; pass < 2; pass++) {
      int32_t cmdLen = 0;
      int samplesToGen = AlFrameSize * 2 * sizeof(int16_t);

      memset(audioBuffer, 0, samplesToGen);

      alAudioFrame(cmdList, &cmdLen, audioBuffer, AlFrameSize);
      AudioPlayerPlayFrame((uint8_t *)audioBuffer, samplesToGen);
    }

    {
      std::unique_lock<std::mutex> lock(mAudio.mutex);
      mAudio.processing = false;
    }
    mAudio.cv_from_thread.notify_one();
  }
}

void GameEngine::StartAudioFrame() {
  if (!mAudio.running)
    return;

  {
    std::unique_lock<std::mutex> lock(mAudio.mutex);
    mAudio.processing = true;
  }
  mAudio.cv_to_thread.notify_one();
}

void GameEngine::EndAudioFrame() {
  if (!mAudio.running)
    return;

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
      mAudio.processing = true; // Wake up the thread
    }
    mAudio.cv_to_thread.notify_one();

    // Wait for thread to finish
    if (mAudio.thread.joinable()) {
      mAudio.thread.join();
    }

    SPDLOG_INFO("Audio system shut down");
  }
}

void GameEngine::RunCommands(
    Gfx *Commands,
    const std::vector<std::unordered_map<Mtx *, MtxF>> &mtx_replacements) {
  auto wnd = std::dynamic_pointer_cast<Fast::Fast3dWindow>(
      Ship::Context::GetInstance()->GetWindow());

  if (wnd == nullptr) {
    return;
  }

  auto interpreter = wnd->GetInterpreterWeak().lock().get();

  // Process window events for resize, mouse, keyboard events
  wnd->HandleEvents();

  interpreter->mInterpolationIndex = 0;

  for (const auto &m : mtx_replacements) {
    wnd->DrawAndRunGraphicsCommands(Commands, m);
    interpreter->mInterpolationIndex++;
  }
}

void GameEngine::ProcessGfxCommands(Gfx *commands) {
  auto wnd = std::dynamic_pointer_cast<Fast::Fast3dWindow>(
      Ship::Context::GetInstance()->GetWindow());

  if (wnd == nullptr)
    return;

  // Set microcode handler
  wnd->SetRendererUCode(UcodeHandlers::ucode_f3dex2);

  // Build matrix replacements for interpolation
  std::vector<std::unordered_map<Mtx *, MtxF>> mtx_replacements;

  // For now, just one pass (no interpolation)
  // Later: Generate multiple matrix sets for 30fps->60fps or 60fps->120fps
  mtx_replacements.push_back({});

  RunCommands(commands, mtx_replacements);
}

static const char *sOtrSignature = "__OTR__";

extern "C" uint8_t GameEngine_OTRSigCheck(const char *data) {
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

extern "C" void GameEngine_EndAudioFrame(void) { GameEngine::EndAudioFrame(); }

// C-callable wrapper for processing graphics commands
extern "C" void GameEngine_ProcessGfxCommands(Gfx *commands) {
  std::vector<std::unordered_map<Mtx *, MtxF>> mtx_replacements;
  mtx_replacements.push_back(
      {}); // Empty map for now, interpolation can be added later
  GameEngine::RunCommands(commands, mtx_replacements);
}

// C-callable controller input reader
extern "C" void GameEngine_ReadController(OSContPad *pads) {
  auto controlDeck = Ship::Context::GetInstance()->GetControlDeck();
  if (controlDeck != nullptr) {
    controlDeck->WriteToPad(pads);
  }
}

// C-callable memory allocator
extern "C" void *GameEngine_Malloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr != nullptr) {
    MemoryPool.push_back((uint8_t *)ptr);
  }
  return ptr;
}

// C-callable logging using spdlog
extern "C" void GameEngine_LogInfo(const char *fmt, ...) {
  char buffer[512];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);
  SPDLOG_INFO("{}", buffer);
}

// C-callable stack trace logging using spdlog
#if defined(__APPLE__) || defined(__linux__)
#include <cxxabi.h>
#include <execinfo.h>
#endif

extern "C" void GameEngine_LogStackTrace(const char *label) {
#if defined(__APPLE__) || defined(__linux__)
  SPDLOG_INFO("Stack trace [{}]:", label ? label : "unnamed");

  void *callstack[32];
  int frames = backtrace(callstack, 32);
  char **symbols = backtrace_symbols(callstack, frames);

  if (symbols) {
    for (int i = 1; i < frames; i++) { // Skip frame 0 (this function)
      // Try to demangle C++ symbols
      char *symbol = symbols[i];
      char *demangled = nullptr;

      // macOS format: "1   StarRod  0x00000001000abcde _Z12someFunctionv + 42"
      // Try to extract and demangle the symbol name
      char *start = strchr(symbol, '_');
      if (start) {
        char *end = strchr(start, ' ');
        if (end) {
          size_t len = end - start;
          char *mangled = (char *)malloc(len + 1);
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
  SPDLOG_INFO("Stack trace [{}]: (not available on this platform)",
              label ? label : "unnamed");
#endif
}

extern "C" void GameEngine_InvalidateTextureCache(const void *addr) {
  if (addr == nullptr) {
    return;
  }
  auto window = Ship::Context::GetInstance()->GetWindow();
  if (window != nullptr) {
    auto fast3d = std::dynamic_pointer_cast<Fast::Fast3dWindow>(window);
    if (fast3d != nullptr) {
      auto interp = fast3d->GetInterpreterWeak().lock();
      if (interp != nullptr) {
        interp->TextureCacheDelete(reinterpret_cast<const uint8_t *>(addr));
      }
    }
  }
}

extern "C" int GameEngine_GetSaveFilePath(char *buf, int bufSize) {
  std::string path =
      Ship::Context::GetPathRelativeToAppDirectory("default.sav");
  if ((int)path.size() >= bufSize) {
    return -1;
  }
  strncpy(buf, path.c_str(), bufSize);
  buf[bufSize - 1] = '\0';
  return 0;
}

extern "C" void GameEngine_ClearDepthBuffer(void) {
  auto wnd = std::dynamic_pointer_cast<Fast::Fast3dWindow>(
      Ship::Context::GetInstance()->GetWindow());
  if (wnd) {
    auto interp = wnd->GetInterpreterWeak().lock();
    if (interp) {
      interp->GetCurrentRenderingAPI()->ClearFramebuffer(false, true);
    }
  }
}
