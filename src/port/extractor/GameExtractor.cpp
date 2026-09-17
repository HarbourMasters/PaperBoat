#ifdef _WIN32
#include <Windows.h>
#include <shlwapi.h>
#include <winuser.h>
#pragma comment(lib, "shlwapi.lib")
#endif

#include "GameExtractor.h"
#include "build.h"

#include <algorithm>
#include <cstdio>
#include <fstream>

#include "ship/Context.h"
#include "spdlog/spdlog.h"

#include "port/FilePicker.h"

#ifdef __EMSCRIPTEN__
#include "port/web/WebUtils.h"
#endif

#ifdef unix
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

// Set by CMake
#ifndef PAPERBOAT_ASSET_YAML_COUNT
#define PAPERBOAT_ASSET_YAML_COUNT 0
#endif

std::string GameExtractor::sStatusText;
std::string GameExtractor::sLastError;
std::atomic<int> GameExtractor::sPhase { 0 };

namespace {
// Where config.yml lives. Empty means "ask Ship::Context"; the Android
// launcher runs before it exists and names the directory itself.
std::filesystem::path ConfigPath(const std::string& configDir) {
    const auto base =
        configDir.empty() ? std::filesystem::path(Ship::Context::GetAppBundlePath()) : std::filesystem::path(configDir);
    return base / "config.yml";
}

std::optional<YAML::Node> GetSupportedRomNode(const std::vector<uint8_t>& romData, const std::string& configDir = "") {
    const auto configPath = ConfigPath(configDir);
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

std::vector<uint8_t> ReadWholeFile(const std::filesystem::path& path) {
    std::ifstream inFile(path, std::ios::binary);
    if (!inFile.is_open()) {
        return { };
    }
    return std::vector<uint8_t>(std::istreambuf_iterator<char>(inFile), { });
}
} // namespace

bool GameExtractor::RunStandalone(std::string rom, const std::string& configDir) {
    if (!std::filesystem::exists(rom)) {
        SPDLOG_INFO("No ROM at path: {}, continuing", rom);
        return false;
    }

    std::vector<uint8_t> data = ReadWholeFile(rom);
    if (data.empty()) {
        SPDLOG_INFO("Failed to read ROM at path: {}, continuing", rom);
        return false;
    }

    if (!GetSupportedRomNode(data, configDir).has_value()) {
        return false;
    }

    this->mGamePath = rom;
    this->mGameData = std::move(data);

    return true;
}

// Reads a ROM off disk into the extractor. Shared by every pick path below.
bool GameExtractor::LoadRomFromPath(const std::string& romPath) {
    if (!std::filesystem::exists(romPath)) {
        SPDLOG_ERROR("Failed to find ROM at path: {}", romPath);
        return false;
    }

    std::vector<uint8_t> romData = ReadWholeFile(romPath);
    if (romData.empty()) {
        return false;
    }

    this->mGamePath = romPath;
    this->mGameData = std::move(romData);
    return true;
}

// Paperboat::PickFile decides the backend: a native dialog where there is one, otherwise
// libultraship's ImGui browser. The ImGui browser answers on a later frame, so the result
// always comes back through onComplete rather than a return value.
void GameExtractor::SelectGameFromUI(std::function<void(bool)> onComplete) {
    const auto finish = [onComplete](bool ok) {
        if (onComplete) {
            onComplete(ok);
        }
    };

#if defined(__EMSCRIPTEN__)
    // Blocks (ASYNCIFY) until the user picks a file or cancels.
    const std::string romPath = WebFilePicker_PickROM();
    finish(!romPath.empty() && LoadRomFromPath(romPath));
#elif defined(__IOS__) || defined(__ANDROID__)
    // Mobile has no file dialog: the ROM is put in place beforehand.
    finish(LoadRomFromPath(Ship::Context::GetPathRelativeToAppDirectory("baserom.us.z64")));
#else
    Ship::FileBrowserRequest req;
    req.Title = "Select a Paper Mario ROM";
    req.Filters = { { "N64 ROMs (.z64, .n64, .v64)", { "*.z64", "*.n64", "*.v64" } }, { "All files", { "*" } } };
    req.StartDir = Ship::Context::GetAppDirectoryPath("boat");
    Paperboat::PickFile(std::move(req), [this, finish](std::optional<std::filesystem::path> path) {
        finish(path.has_value() && LoadRomFromPath(path->string()));
    });
#endif
}

void GameExtractor::SetSearchPath(const std::string& path) {
    mSearchPath = path;
}

void GameExtractor::GetRoms(std::vector<std::string>& roms) {
#ifdef _WIN32
    WIN32_FIND_DATAA ffd;
    std::string search = std::string(mSearchPath + "\\*");
    HANDLE h = FindFirstFileA(search.c_str(), &ffd);

    if (h == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            char* ext = PathFindExtensionA(ffd.cFileName);
            if (ext != NULL && strcmp(ext, ".z64") == 0) {
                roms.push_back((std::filesystem::path(mSearchPath) / ffd.cFileName).generic_string());
            }
        }
    } while (FindNextFileA(h, &ffd) != 0);
    FindClose(h);
#elif unix
    DIR* d = opendir(mSearchPath.c_str());
    struct dirent* dir;

    if (d != NULL) {
        while ((dir = readdir(d)) != NULL) {
            struct stat path;
            stat(dir->d_name, &path);
            if (S_ISREG(path.st_mode)) {
                char* ext = strrchr(dir->d_name, '.');
                if (ext != NULL && strcmp(ext, ".z64") == 0) {
                    roms.push_back((std::filesystem::path(mSearchPath) / dir->d_name).generic_string());
                }
            }
        }
    }
    closedir(d);
#else
    for (const auto& file : std::filesystem::directory_iterator(mSearchPath)) {
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

std::optional<std::string> GameExtractor::DetectVersion(const std::string& romPath, const std::string& configDir) {
    std::error_code ec;
    if (!std::filesystem::exists(romPath, ec)) {
        return std::nullopt;
    }

    const std::vector<uint8_t> data = ReadWholeFile(romPath);
    if (data.empty()) {
        return std::nullopt;
    }

    auto rom = GetSupportedRomNode(data, configDir);
    if (!rom.has_value()) {
        return std::nullopt;
    }

    if ((*rom)["name"]) {
        return (*rom)["name"].as<std::string>();
    }

    auto cart = std::make_unique<N64::Cartridge>(data);
    cart->Initialize();
    return cart->GetGameTitle();
}

std::vector<std::pair<std::string, std::string>>
GameExtractor::FindSupportedRoms(const std::vector<std::string>& searchPaths) {
    std::vector<std::pair<std::string, std::string>> found;
    std::vector<std::string> seenVersions;

    for (const auto& dir : searchPaths) {
        std::error_code ec;
        if (dir.empty() || !std::filesystem::is_directory(dir, ec)) {
            continue;
        }
        for (const auto& entry : std::filesystem::directory_iterator(dir, ec)) {
            if (entry.is_directory() || entry.path().extension() != ".z64") {
                continue;
            }
            const std::string full = entry.path().generic_string();
            const auto version = DetectVersion(full);
            if (!version.has_value()) {
                continue; // Only offer ROMs the recipes actually cover.
            }
            // One entry per version, so duplicate copies aren't offered twice.
            if (std::find(seenVersions.begin(), seenVersions.end(), *version) != seenVersions.end()) {
                continue;
            }
            seenVersions.push_back(*version);
            found.emplace_back(full, *version);
        }
    }

    return found;
}

void GameExtractor::WritePortVersion() {
    auto writer = LUS::BinaryWriter();
    writer.SetEndianness(Torch::Endianness::Big);
    writer.Write((uint16_t) gBuildVersionMajor);
    writer.Write((uint16_t) gBuildVersionMinor);
    writer.Write((uint16_t) gBuildVersionPatch);
    writer.Close();

    Companion::Instance->RegisterCompanionFile("portVersion", writer.ToVector());
}

std::string GameExtractor::GetRomPath() {
    return mGamePath.generic_string();
}

bool GameExtractor::GenerateOTR(std::string appShortName) {
    std::atomic<size_t> assetCount { 0 };
    return GenerateOTR(assetCount, appShortName);
}

bool GameExtractor::GenerateOTR(std::atomic<size_t>& assetCount, std::string appShortName) {
    std::atomic<size_t> unused { 0 };
    return GenerateOTR(assetCount, unused, appShortName);
}

bool GameExtractor::GenerateOTR(
    std::atomic<size_t>& assetCount, std::atomic<size_t>& totalAssets, std::string appShortName
) {
    const std::string assets_path =
        fs::path(Ship::Context::LocateFileAcrossAppDirs("assets", appShortName)).parent_path().generic_string();
    const std::string game_path = Ship::Context::GetAppDirectoryPath(appShortName);

    return GenerateOTRTo(assetCount, totalAssets, assets_path, game_path);
}

bool GameExtractor::GenerateOTRTo(
    std::atomic<size_t>& assetCount,
    std::atomic<size_t>& totalAssets,
    const std::string& assetsPath,
    const std::string& gamePath
) {
    totalAssets = PAPERBOAT_ASSET_YAML_COUNT;
    assetCount = 0;

    sLastError.clear();
    sPhase = 1;
    delete Companion::Instance;
    Companion::Instance = new Companion(this->mGameData, ArchiveType::O2R, false, assetsPath, gamePath);
    Companion::Instance->SetPhaseCallback([&assetCount](int phase) {
        if (phase == 2) {
            assetCount++;
        }
    });
    this->WritePortVersion();
    std::atomic<size_t> unusedCounter { 0 };
    try {
        Companion::Instance->Init(ExportType::Binary, unusedCounter, true);
#ifdef __EMSCRIPTEN__
        // Torch's Init() skips the export pass on the web build, so run it here.
        Companion::Instance->Process(unusedCounter);
#endif
    } catch (const std::exception& e) {
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

bool GameExtractor::GenAssetFile() {
    return false;
}
