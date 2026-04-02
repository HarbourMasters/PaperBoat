#include "Engine.h"

#include "ShipInit.hpp"
#include "extractor/GameExtractor.h"
#include "importer/PM64TextureFactory.h"
#include "importer/Vec3sFactory.h"
#include "nlohmann/json.hpp"
#include "port/enhancements/PortEnhancements.h"
#include "port/interpolation/FrameInterpolation.h"
#include "port/ui/cvar_prefixes.h"
#include "src/Companion.h"
#include "ui/PaperboatGui.hpp"
#include <BS_thread_pool.hpp>
#include <algorithm>
#include <atomic>
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
#include <imgui.h>
#include <libultraship.h>
#include <libultraship/controller/controldeck/ControlDeck.h>
#include <mutex>
#include <optional>
#include <ship/resource/factory/BlobFactory.h>
#include <ship/window/gui/Fonts.h>
#include <ship/window/gui/resource/Font.h>
#include <thread>
#include <unordered_map>

using json = nlohmann::json;

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

static bool portArchiveExists = false;
static const std::vector<std::string> sRomArchives = {"pm64.o2r"};

typedef enum ExtractSteps {
  ES_PORT_ARCHIVE,
  ES_WINDOWS,
  ES_EXTRACT_ARGS,
  ES_EXTRACT,
  ES_VERIFY,
} ExtractSteps;

typedef enum PromptSteps {
  PS_FILE_CHECK,
  PS_LOCAL,
  PS_FIRST,
  PS_DUPE,
  PS_WAIT,
  PS_NONE,
} PromptSteps;

typedef enum WindowsSteps {
  WS_TEMP,
  WS_PERMS,
  WS_ONEDRIVE,
  WS_DONE,
} WindowsSteps;

static bool IsSubpath(const std::filesystem::path &path,
                      const std::filesystem::path &base) {
  auto rel = std::filesystem::relative(path, base);
  return !rel.empty() && rel.native()[0] != '.';
}

static bool PathTestCleanup(FILE *tfile) {
  try {
    if (std::filesystem::exists("./text.txt")) {
      std::filesystem::remove("./text.txt");
    }
    if (std::filesystem::exists("./test/")) {
      std::filesystem::remove("./test/");
    }
  } catch (std::filesystem::filesystem_error const &ex) {
    return false;
  }
  return true;
}

static void CheckAndCreateModFolder() {
  try {
    std::string modsPath =
        Ship::Context::LocateFileAcrossAppDirs("mods", "boat");
    if (!std::filesystem::exists(modsPath)) {
      modsPath = Ship::Context::GetPathRelativeToAppDirectory("mods", "boat");
      std::string filePath = modsPath + "/custom_mod_files_go_here.txt";
      if (std::filesystem::create_directories(modsPath)) {
        std::ofstream(filePath).close();
      }
    }
  } catch (std::filesystem::filesystem_error const &ex) {
    return;
  }
}

static bool AnyRomArchiveExists() {
  for (const auto &archive : sRomArchives) {
    if (std::filesystem::exists(
            Ship::Context::LocateFileAcrossAppDirs(archive))) {
      return true;
    }
  }
  return false;
}

GameEngine::GameEngine() {
  this->context = Ship::Context::CreateUninitializedInstance(
      "Paperboat", "boat", "paperboat.cfg.json");

  const std::string assets_path =
      Ship::Context::LocateFileAcrossAppDirs("paperboat.o2r");
  portArchiveExists = std::filesystem::exists(assets_path);

#ifdef _WIN32
  AllocConsole();
#endif

  this->context->InitConfiguration();
  this->context->InitConsoleVariables();
  auto controlDeck = std::make_shared<LUS::ControlDeck>();
  this->context->InitControlDeck(controlDeck);
  this->context->InitResourceManager(portArchiveExists
                                         ? std::vector<std::string>{assets_path}
                                         : std::vector<std::string>{},
                                     {}, 3, true);
  this->context->InitConsole();
  gsFast3dWindow = std::make_shared<Fast::Fast3dWindow>(
      std::vector<std::shared_ptr<Ship::GuiWindow>>({}));
  this->context->InitWindow(gsFast3dWindow);
  PaperboatGui::SetupMenu();

  if (portArchiveExists) {
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
}

void GameEngine::FinishInit() {
  auto archiveManager = context->GetResourceManager()->GetArchiveManager();

  for (const auto &archive : sRomArchives) {
    const auto romPath = Ship::Context::LocateFileAcrossAppDirs(archive);
    if (std::filesystem::exists(romPath)) {
      archiveManager->AddArchive(romPath);
    }
  }

  const std::string hd_path =
      Ship::Context::GetPathRelativeToAppDirectory("paperboat-hd.o2r");
  if (std::filesystem::exists(hd_path)) {
    SPDLOG_INFO("Loading HD asset archive: paperboat-hd.o2r");
    archiveManager->AddArchive(hd_path);
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
      archiveManager->AddArchive(mod);
    }
  }

  this->context->InitLogging(spdlog::level::trace, spdlog::level::trace);
  this->context->InitGfxDebugger();
  this->context->InitCrashHandler();

  auto audioChannelsSetting = Ship::Context::GetInstance()
                                  ->GetConfig()
                                  ->GetCurrentAudioChannelsSetting();
  this->context->InitAudio({32000, 1024, 1680, audioChannelsSetting});

  auto loader = context->GetResourceManager()->GetResourceLoader();
  loader->RegisterResourceFactory(
      std::make_shared<Ship::ResourceFactoryBinaryBlobV0>(),
      RESOURCE_FORMAT_BINARY, "Blob",
      static_cast<uint32_t>(Ship::ResourceType::Blob), 0);
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
  loader->RegisterResourceFactory(
      std::make_shared<PM64::ResourceFactoryBinaryVec3sV0>(),
      RESOURCE_FORMAT_BINARY, "Vec3s", static_cast<uint32_t>(0x56433353), 0);
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

void GameEngine::RunExtract(int argc, char *argv[]) {
  bool extractDone = false;
  ExtractSteps extractStep = ES_PORT_ARCHIVE;
  WindowsSteps windowsStep = WS_TEMP;
  auto wnd =
      std::dynamic_pointer_cast<Fast::Fast3dWindow>(context->GetWindow());
  auto gui = wnd->GetGui();
  bool menuWasVisible = false;
  if (gui->GetMenu()->IsVisible()) {
    menuWasVisible = true;
    gui->GetMenu()->Hide();
  }

  std::vector<std::string> args;
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      args.push_back(argv[i]);
    }
  }

  GameExtractor extract;
  PromptSteps promptStep = PS_FILE_CHECK;
  std::atomic<bool> extracting = false;
  bool extractStarted = false;
  std::atomic<size_t> extractCount{0}, totalExtract{0};
  std::string installPath = Ship::Context::GetAppBundlePath();
  std::string file;
  std::filesystem::path ownPath;

  if (!std::filesystem::exists(
          Ship::Context::LocateFileAcrossAppDirs("assets"))) {
    PaperboatGui::RegisterPopup(
        "Extractor assets not found",
        "No O2R files found. Missing 'assets/' folder needed to generate O2R "
        "file.\nPlease re-extract them from the download.\n\nExiting...",
        "OK", "", [&]() {
          gsFast3dWindow = nullptr;
          context = nullptr;
          exit(1);
        });
  }

  std::shared_ptr<BS::thread_pool> threadPool =
      std::make_shared<BS::thread_pool>(1);

  while (!extractDone) {
    if (PaperboatGui::PopupsQueued() > 0 || extracting) {
      goto render;
    }

    if (extractStep == ES_EXTRACT && promptStep == PS_FIRST && extractStarted &&
        !extracting) {
      extractStep = ES_VERIFY;
      extractCount = 0;
      totalExtract = 0;
    }

    switch (extractStep) {
    case ES_PORT_ARCHIVE: {
      if (portArchiveExists) {
#ifdef _WIN32
        extractStep = ES_WINDOWS;
#else
        extractStep = ES_EXTRACT;
#endif
      } else {
        PaperboatGui::RegisterPopup(
            !std::filesystem::exists(
                Ship::Context::LocateFileAcrossAppDirs("paperboat.o2r"))
                ? "Missing paperboat.o2r"
                : "paperboat.o2r is outdated",
            "Please extract the paperboat.o2r from the PaperBoat download to "
            "your folder.\n\nExiting...",
            "OK", "", [&]() { exit(1); });
      }
      continue;
    }
    case ES_WINDOWS: {
      switch (windowsStep) {
      case WS_TEMP: {
#ifdef _WIN32
        char *tempVar = getenv("TEMP");
        std::filesystem::path tempPath;
        try {
          tempPath = std::filesystem::canonical(tempVar);
        } catch (std::filesystem::filesystem_error const &ex) {
          std::string userPath = getenv("USERPROFILE");
          userPath.append("\\AppData\\Local\\Temp");
          tempPath = std::filesystem::canonical(userPath);
        }
        wchar_t buffer[MAX_PATH];
        GetModuleFileName(NULL, buffer, _countof(buffer));
        ownPath = std::filesystem::canonical(buffer).parent_path();
        if (IsSubpath(ownPath, tempPath)) {
          PaperboatGui::RegisterPopup(
              "PaperBoat Path Error",
              "PaperBoat is running in a temp folder.\nExtract the .zip and "
              "run again.",
              "OK", "", [&]() {
                threadPool = nullptr;
                gsFast3dWindow = nullptr;
                context = nullptr;
                exit(0);
              });
        } else {
          windowsStep = WS_PERMS;
        }
#endif
        continue;
      }
      case WS_PERMS: {
        FILE *tfile = fopen("./text.txt", "w");
        std::filesystem::path tfolder = std::filesystem::path("./test/");
        bool error = false;
        try {
          std::filesystem::create_directories(tfolder);
        } catch (std::filesystem::filesystem_error const &ex) {
          error = true;
        }
        if (tfile == NULL || error) {
          PaperboatGui::RegisterPopup(
              "PaperBoat Permissions Error",
              "PaperBoat does not have proper file permissions.\nPlease move "
              "it to a folder that does and run again.",
              "OK", "", [&]() {
                if (tfile != NULL) {
                  fclose(tfile);
                }
                PathTestCleanup(tfile);
                threadPool = nullptr;
                gsFast3dWindow = nullptr;
                context = nullptr;
                exit(0);
              });
        } else {
          fclose(tfile);
          if (!PathTestCleanup(tfile)) {
            PaperboatGui::RegisterPopup(
                "PaperBoat Permissions Error",
                "PaperBoat does not have proper file permissions.\nPlease move "
                "it to a folder that does and run again.",
                "OK", "", [&]() {
                  threadPool = nullptr;
                  gsFast3dWindow = nullptr;
                  context = nullptr;
                  exit(0);
                });
          }
          windowsStep = WS_ONEDRIVE;
        }
        continue;
      }
      case WS_ONEDRIVE: {
        if (ownPath.string().find("OneDrive") != std::string::npos) {
          PaperboatGui::RegisterPopup(
              "PaperBoat Path Error",
              "PaperBoat appears to be in a OneDrive folder, which will cause "
              "issues.\nPlease move it to a folder outside of OneDrive, like "
              "the root of a\ndrive (e.g. \"C:\\Games\\PaperBoat\").",
              "OK", "", [&]() {
                threadPool = nullptr;
                gsFast3dWindow = nullptr;
                context = nullptr;
                exit(0);
              });
        } else {
          windowsStep = WS_DONE;
          if (!args.empty()) {
            extractStep = ES_EXTRACT_ARGS;
          } else {
            extractStep = ES_EXTRACT;
          }
        }
        continue;
      }
      default:
        continue;
      }
      break;
    }
    case ES_EXTRACT: {
      switch (promptStep) {
      case PS_FILE_CHECK: {
        if (!AnyRomArchiveExists()) {
          PaperboatGui::RegisterPopup(
              "No O2R Files", "No O2R files found. Generate one now?", "Yes",
              "No", [&]() { promptStep = PS_LOCAL; },
              [&]() {
                threadPool = nullptr;
                gsFast3dWindow = nullptr;
                context = nullptr;
                exit(0);
              });
        } else {
          extractStep = ES_VERIFY;
        }
        continue;
      }
      case PS_LOCAL: {
        extract = GameExtractor();
        extract.SetSearchPath(installPath);
        extract.GetRoms(args);
        extract.SetSearchPath(Ship::Context::GetAppDirectoryPath("boat"));
        extract.GetRoms(args);
        if (!args.empty()) {
          promptStep = PS_WAIT;
          PaperboatGui::RegisterPopup(
              "ROMs found",
              "ROMs found in application directory. Would you like to process "
              "them?",
              "Yes", "No", [&]() { extractStep = ES_EXTRACT_ARGS; },
              [&]() {
                args.clear();
                promptStep = PS_FIRST;
              });
        } else {
          promptStep = PS_FIRST;
        }
        continue;
      }
      case PS_FIRST: {
        if (args.empty() && !extract.SelectGameFromUI()) {
          promptStep = PS_FILE_CHECK;
          continue;
        }
        extracting = true;
        extractStarted = true;
        file = extract.GetRomPath();
        threadPool->submit_task([&]() -> void {
          extract.GenerateOTR(extractCount, totalExtract, "boat");
          extracting = false;
        });
        continue;
      }
      default:
        break;
      }
      break;
    }
    case ES_EXTRACT_ARGS: {
#if !defined(__SWITCH__) && !defined(__WIIU__)
      if (args.size() == 0) {
        PaperboatGui::RegisterPopup(
            "Run PaperBoat", "All files have been processed. Run PaperBoat?",
            "Yes", "No",
            [&]() {
              if (!AnyRomArchiveExists()) {
                extractStep = ES_EXTRACT;
                promptStep = PS_FILE_CHECK;
              } else {
                extractStep = ES_VERIFY;
              }
            },
            [&]() {
              threadPool = nullptr;
              gsFast3dWindow = nullptr;
              context = nullptr;
              exit(0);
            });
        break;
      }
      file = args.at(0);
      args.erase(args.begin());
      extract = GameExtractor();
      if (extract.RunStandalone(file)) {
        std::string archive = "pm64.o2r";
        if (std::filesystem::exists(Ship::Context::GetAppDirectoryPath("boat") +
                                    "/" + archive)) {
          std::string msg = "Archive for current ROM, " + archive +
                            ", already exists.\nExtract again?";
          PaperboatGui::RegisterPopup(
              "Confirm Re-extract", msg.c_str(), "Yes", "No", [&]() {
                extracting = true;
                threadPool->submit_task([&]() -> void {
                  extract.GenerateOTR(extractCount, totalExtract, "boat");
                  extracting = false;
                });
              });
        } else {
          extracting = true;
          threadPool->submit_task([&]() -> void {
            extract.GenerateOTR(extractCount, totalExtract, "boat");
            extracting = false;
          });
        }
      } else {
        const std::string msg =
            "File\n" + file +
            "\nis not a ROM or does not match supported ROMs.";
        PaperboatGui::RegisterPopup("PaperBoat ROM Error", msg.c_str());
      }
#else
      extractStep = ES_VERIFY;
#endif
      break;
    }
    case ES_VERIFY: {
      if (!AnyRomArchiveExists()) {
        if (PaperboatGui::PopupsQueued() == 0) {
          std::string errorMsg;
          if (!GameExtractor::sLastError.empty()) {
            std::string wrapped = GameExtractor::sLastError;
            const size_t wrapCol = 80;
            size_t pos = 0;
            while (pos + wrapCol < wrapped.size()) {
              size_t breakAt = wrapped.rfind(' ', pos + wrapCol);
              if (breakAt == std::string::npos || breakAt <= pos) {
                breakAt = pos + wrapCol;
              }
              wrapped.insert(breakAt, "\n");
              pos = breakAt + 1;
            }
            errorMsg = "ROM extraction failed:\n\n" + wrapped +
                       "\n\nCheck logs/Paperboat.log for full details.";
          } else {
            errorMsg = "No ROM O2R file detected.\nPlease generate a ROM O2R "
                       "and relaunch.";
          }
          PaperboatGui::RegisterPopup("Extraction Error", errorMsg.c_str(),
                                      "OK", "", [&]() {
                                        threadPool = nullptr;
                                        gsFast3dWindow = nullptr;
                                        context = nullptr;
                                        exit(0);
                                      });
        }
        continue;
      }
      extractDone = true;
      continue;
    }
    default:
      break;
    }

  render:
    if (!WindowIsRunning()) {
      threadPool = nullptr;
      gsFast3dWindow = nullptr;
      context = nullptr;
      exit(0);
    }

    wnd->HandleEvents();
    UIWidgets::Colors themeColor =
        static_cast<UIWidgets::Colors>(CVarGetInteger(
            CVAR_SETTING("Menu.Theme"), UIWidgets::Colors::LightBlue));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive,
                          UIWidgets::ColorValues.at(themeColor));
    ImGui::PushStyleColor(
        ImGuiCol_ModalWindowDimBg,
        UIWidgets::ColorValues.at(UIWidgets::Colors::DarkGray));
    if (!wnd->IsFrameReady()) {
      ImGui::PopStyleColor(2);
      continue;
    }

    gui->StartDraw();
    wnd->StartFrame();
    wnd->RunGuiOnly();
    if (extracting && !ImGui::IsPopupOpen("ROM Extraction")) {
      ImGui::OpenPopup("ROM Extraction");
    }
    if (extracting) {
      ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, 8.0f));
      auto color = UIWidgets::ColorValues.at(THEME_COLOR);
      ImGui::PushStyleColor(ImGuiCol_FrameBg,
                            ImVec4(color.x, color.y, color.z, 0.6f));
      ImGui::PushStyleColor(ImGuiCol_PlotHistogram,
                            ImVec4(color.x, color.y, color.z, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 0.3f));
      if (ImGui::BeginPopupModal(
              "ROM Extraction", NULL,
              ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize |
                  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                  ImGuiWindowFlags_NoSavedSettings)) {
        int phase = GameExtractor::sPhase;
        float progress = 0.0f;
        if (phase == 3) {
          progress = 100.0f;
        } else {
          progress =
              (totalExtract > 0 ? (float)extractCount / (float)totalExtract
                                : 0.0f) *
              100.0f;
          if (progress > 100.0f) {
            progress = 100.0f;
          }
        }

        auto filename = std::filesystem::path(file).filename().string();
        if (phase == 3) {
          ImGui::Text("Done!");
        } else if (phase >= 1) {
          ImGui::Text("Processing %s...", filename.c_str());
        } else {
          ImGui::Text("Starting up...");
        }

        std::string overlay;
        if (totalExtract > 0 && extractCount > 0) {
          overlay = fmt::format("{:.0f}%", progress);
        } else if (phase >= 1) {
          overlay = "Reading ROM, please wait...";
        } else {
          overlay = "Starting up...";
        }
        ImGui::ProgressBar(progress / 100.0f, ImVec2(600.0f, 50.0f),
                           overlay.c_str());
        ImGui::EndPopup();
      }
      ImGui::PopStyleColor(3);
      ImGui::PopStyleVar(2);
    }
    gui->EndDraw();
    wnd->EndFrame();
    ImGui::PopStyleColor(2);
  }

  threadPool = nullptr;

#if !defined(__SWITCH__) && !defined(__WIIU__)
  CheckAndCreateModFolder();
#endif

  if (menuWasVisible) {
    gui->GetMenu()->Show();
  }
}

void GameEngine::Create(int argc, char *argv[]) {
  const auto instance = Instance = new GameEngine();
  instance->RunExtract(argc, argv);
  instance->FinishInit();
  PaperboatGui::SetupGuiElements();
  PortEnhancements_Init();
  ShipInit::InitAll();
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
  }

  if (CVarGetInteger(CVAR_VSYNC_ENABLED, 1) ||
      !Ship::Context::GetInstance()->GetWindow()->CanDisableVerticalSync()) {
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

  std::vector<std::unordered_map<Mtx *, MtxF>> mtx_replacements;

  int target_fps = GetInterpolationFPS();
  static int last_fps;
  static int time;
  int fps = target_fps;
  int original_fps = 60 / 2;

  if (target_fps == 30 || original_fps > target_fps) {
    fps = original_fps;
  }

  if (last_fps != fps) {
    time = 0;
  }

  int next_original_frame = fps;
  while (time + original_fps <= next_original_frame) {
    time += original_fps;
    if (time != next_original_frame) {
      mtx_replacements.push_back(
          FrameInterpolation_Interpolate((float)time / next_original_frame));
    } else {
      mtx_replacements.emplace_back(); // No interpolation for key frames
    }
  }

  time -= fps;

  if (wnd != nullptr) {
    wnd->SetTargetFps(GetInterpolationFPS());
    wnd->SetMaximumFrameLatency(1);
  }
  RunCommands(commands, mtx_replacements);

  last_fps = fps;
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

      // macOS format: "1   Paperboat  0x00000001000abcde _Z12someFunctionv +
      // 42" Try to extract and demangle the symbol name
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
