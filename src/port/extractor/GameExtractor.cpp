#ifdef _WIN32
#include <Windows.h>
#include <shlwapi.h>
#include <winuser.h>
#pragma comment(lib, "shlwapi.lib")
#endif

#include "GameExtractor.h"
#include "build.h"

#include <cstdio>
#include <fstream>

#include "portable-file-dialogs.h"
#include "ship/Context.h"
#include "spdlog/spdlog.h"

#ifdef unix
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

std::string GameExtractor::sStatusText;
std::string GameExtractor::sLastError;
std::atomic<int> GameExtractor::sPhase{0};

namespace {
std::optional<YAML::Node>
GetSupportedRomNode(const std::vector<uint8_t> &romData) {
  const auto configPath =
      std::filesystem::path(Ship::Context::GetAppBundlePath()) / "config.yml";
  if (!std::filesystem::exists(configPath)) {
    return std::nullopt;
  }

  YAML::Node config = YAML::LoadFile(configPath.generic_string());
  const std::string hash = Companion::CalculateHash(romData);
  if (!config[hash]) {
    return std::nullopt;
  }

  return config[hash];
}
} // namespace

bool GameExtractor::RunStandalone(std::string rom) {
  std::string romPath;
  std::vector<uint8_t> romData;

  if (!std::filesystem::exists(rom)) {
    return false;
  }

  std::ifstream inFile(rom, std::ios::binary);
  if (!inFile.is_open()) {
    SPDLOG_INFO("Failed to open ROM at path: {}, continuing", rom);
    return false;
  }

  inFile.seekg(0, std::ios::end);
  size_t fileSize = inFile.tellg();
  inFile.seekg(0, std::ios::beg);

  std::vector<uint8_t> data(fileSize);
  if (!inFile.read(reinterpret_cast<char *>(data.data()), fileSize)) {
    SPDLOG_INFO("Failed to read ROM at path: {}, continuing", rom);
    return false;
  }

  inFile.close();

  if (GetSupportedRomNode(data).has_value()) {
    romPath = rom;
    romData = std::move(data);
  }

  if (romData.empty()) {
    return false;
  }

  this->mGamePath = romPath;
  this->mGameData = std::move(romData);

  return true;
}

bool GameExtractor::SelectGameFromUI() {
  std::string romPath;
  std::vector<uint8_t> romData;

#if !defined(__IOS__) && !defined(__ANDROID__) && !defined(__SWITCH__)
  if (!pfd::settings::available()) {
    SPDLOG_ERROR("portable-file-dialogs is not available on this system.");
    return false;
  }

  auto selection =
      pfd::open_file("Select a file", ".", {"N64 Roms", "*.z64"}).result();
  if (selection.empty()) {
    return false;
  }

  romPath = selection[0];
#else
  if (!std::filesystem::exists(
          Ship::Context::GetPathRelativeToAppDirectory("baserom.us.z64"))) {
    SPDLOG_ERROR("baserom not found");
    return false;
  }

  romPath = Ship::Context::GetPathRelativeToAppDirectory("baserom.us.z64");
#endif

  if (romData.empty()) {
    if (!std::filesystem::exists(romPath)) {
      SPDLOG_ERROR("Failed to find ROM at path: {}", romPath);
      return false;
    }

    std::ifstream inFile(romPath, std::ios::binary);
    if (!inFile.is_open()) {
      return false;
    }

    romData = std::vector<uint8_t>(std::istreambuf_iterator<char>(inFile), {});
    inFile.close();
  }

  this->mGamePath = romPath;
  this->mGameData = std::move(romData);

  return true;
}

void GameExtractor::SetSearchPath(const std::string &path) {
  mSearchPath = path;
}

void GameExtractor::GetRoms(std::vector<std::string> &roms) {
#ifdef _WIN32
  WIN32_FIND_DATAA ffd;
  std::string search = std::string(mSearchPath + "\\*");
  HANDLE h = FindFirstFileA(search.c_str(), &ffd);

  if (h == INVALID_HANDLE_VALUE) {
    return;
  }

  do {
    if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
      char *ext = PathFindExtensionA(ffd.cFileName);
      if (ext != NULL && strcmp(ext, ".z64") == 0) {
        roms.push_back((std::filesystem::path(mSearchPath) / ffd.cFileName)
                           .generic_string());
      }
    }
  } while (FindNextFileA(h, &ffd) != 0);
  FindClose(h);
#elif unix
  DIR *d = opendir(mSearchPath.c_str());
  struct dirent *dir;

  if (d != NULL) {
    while ((dir = readdir(d)) != NULL) {
      struct stat path;
      stat(dir->d_name, &path);
      if (S_ISREG(path.st_mode)) {
        char *ext = strrchr(dir->d_name, '.');
        if (ext != NULL && strcmp(ext, ".z64") == 0) {
          roms.push_back((std::filesystem::path(mSearchPath) / dir->d_name)
                             .generic_string());
        }
      }
    }
  }
  closedir(d);
#else
  for (const auto &file : std::filesystem::directory_iterator(mSearchPath)) {
    if (file.is_directory()) {
      continue;
    }
    if (file.path().extension() == ".z64") {
      roms.push_back(file.path().generic_string());
    }
  }
#endif
}

std::optional<std::string> GameExtractor::ValidateChecksum() const {
  auto rom = GetSupportedRomNode(this->mGameData);
  if (!rom.has_value()) {
    return std::nullopt;
  }

  auto cart = std::make_unique<N64::Cartridge>(this->mGameData);
  cart->Initialize();

  if ((*rom)["name"]) {
    return (*rom)["name"].as<std::string>();
  }

  return cart->GetGameTitle();
}

void GameExtractor::WritePortVersion() {
  auto writer = LUS::BinaryWriter();
  writer.SetEndianness(Torch::Endianness::Big);
  writer.Write((uint16_t)gBuildVersionMajor);
  writer.Write((uint16_t)gBuildVersionMinor);
  writer.Write((uint16_t)gBuildVersionPatch);
  writer.Close();

  Companion::Instance->RegisterCompanionFile("portVersion", writer.ToVector());
}

std::string GameExtractor::GetRomPath() { return mGamePath.generic_string(); }

bool GameExtractor::GenerateOTR(std::string appShortName) {
  std::atomic<size_t> assetCount{0};
  return GenerateOTR(assetCount, appShortName);
}

bool GameExtractor::GenerateOTR(std::atomic<size_t> &assetCount,
                                std::string appShortName) {
  std::atomic<size_t> unused{0};
  return GenerateOTR(assetCount, unused, appShortName);
}

bool GameExtractor::GenerateOTR(std::atomic<size_t> &assetCount,
                                std::atomic<size_t> &totalAssets,
                                std::string appShortName) {
  const std::string assets_path =
      fs::path(Ship::Context::LocateFileAcrossAppDirs("assets", appShortName))
          .parent_path()
          .generic_string();
  const std::string game_path =
      Ship::Context::GetAppDirectoryPath(appShortName);

  totalAssets = 0;
  try {
    auto configPath = fs::path(assets_path) / "config.yml";
    if (fs::exists(configPath)) {
      YAML::Node config = YAML::LoadFile(configPath.generic_string());
      std::string hash = Companion::CalculateHash(this->mGameData);
      auto rom = config[hash];
      if (rom && rom["path"]) {
        auto assetDir = (fs::path(assets_path) / rom["path"].as<std::string>())
                            .generic_string();
        for (const auto &entry :
             std::filesystem::recursive_directory_iterator(assetDir)) {
          if (entry.is_directory()) {
            continue;
          }
          const auto path = entry.path().generic_string();
          if (path.find(".yaml") == std::string::npos &&
              path.find(".yml") == std::string::npos) {
            continue;
          }
          if (path.find("config.yml") != std::string::npos) {
            continue;
          }
          YAML::Node root = YAML::LoadFile(path);
          for (auto asset = root.begin(); asset != root.end(); ++asset) {
            auto key = asset->first.as<std::string>();
            if (key.find(":config") != std::string::npos) {
              continue;
            }
            totalAssets++;
          }
        }
      }
    }
  } catch (const std::exception &e) {
    SPDLOG_WARN("Failed to count assets: {}", e.what());
  }

  sPhase = 1;
  delete Companion::Instance;
  Companion::Instance = new Companion(this->mGameData, ArchiveType::O2R, false,
                                      assets_path, game_path);
  this->WritePortVersion();
  try {
    Companion::Instance->Init(ExportType::Binary, assetCount);
  } catch (const std::exception &e) {
    SPDLOG_ERROR("Failed to process O2R: {}", e.what());
    sLastError = e.what();
    sStatusText.clear();
    sPhase = 0;
    delete Companion::Instance;
    Companion::Instance = nullptr;
    return false;
  }

  sPhase = 3;
  sStatusText = "Cleaning up...";
  delete Companion::Instance;
  Companion::Instance = nullptr;
  sStatusText.clear();
  sPhase = 0;
  return true;
}

bool GameExtractor::GenAssetFile() { return false; }
