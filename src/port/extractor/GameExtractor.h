#pragma once

#include "Companion.h"

#include <atomic>
#include <cstdint>
#include <filesystem>
#include <string>
#include <utility>
#include <vector>

class GameExtractor {
public:
    static bool GenAssetFile();
    std::optional<std::string> ValidateChecksum() const;
    // configDir names the folder holding config.yml. Empty means "ask
    // Ship::Context", which is right everywhere the engine is already up; the
    // Android launcher extracts before SDL exists and so passes it outright.
    bool RunStandalone(std::string rom, const std::string& configDir = "");
    bool SelectGameFromUI();
    void SetSearchPath(const std::string& path);
    void GetRoms(std::vector<std::string>& roms);
    // The name config.yml gives this ROM (e.g. "pm64"), or nullopt when it is
    // not one the bundled recipes can extract.
    static std::optional<std::string> DetectVersion(const std::string& romPath, const std::string& configDir = "");
    // Scans the given directories for supported .z64 ROMs, returning (full path,
    // version name) pairs deduplicated by version so the user is offered one
    // entry per version rather than one per copy.
    static std::vector<std::pair<std::string, std::string>>
    FindSupportedRoms(const std::vector<std::string>& searchPaths);
    std::string GetRomPath();
    bool GenerateOTR(std::string appShortName = "");
    bool GenerateOTR(std::atomic<size_t>& assetCount, std::string appShortName = "");
    bool GenerateOTR(std::atomic<size_t>& assetCount, std::atomic<size_t>& totalAssets, std::string appShortName = "");
    // Same as GenerateOTR, but with the two directories named outright instead
    // of asked of Ship::Context, for callers that run before the engine does.
    bool GenerateOTRTo(std::atomic<size_t>& assetCount, std::atomic<size_t>& totalAssets,
                       const std::string& assetsPath, const std::string& gamePath);
    void WritePortVersion();
    static std::string sStatusText;
    static std::string sLastError;
    static std::atomic<int> sPhase;

private:
    std::filesystem::path mGamePath;
    std::vector<uint8_t> mGameData;
    std::string mSearchPath;
};
