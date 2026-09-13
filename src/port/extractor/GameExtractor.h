#pragma once

#include <functional>

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
    // configDir holds config.yml. Empty asks Ship::Context; the Android
    // launcher runs before SDL exists, so it passes the path outright.
    bool RunStandalone(std::string rom, const std::string& configDir = "");
    // Answers through onComplete: the ImGui browser resolves on a later frame.
    void SelectGameFromUI(std::function<void(bool)> onComplete);
    bool LoadRomFromPath(const std::string& romPath);
    void SetSearchPath(const std::string& path);
    void GetRoms(std::vector<std::string>& roms);
    // The name config.yml gives this ROM, or nullopt if it has no recipe.
    static std::optional<std::string> DetectVersion(const std::string& romPath, const std::string& configDir = "");
    // Supported .z64 ROMs as (path, version) pairs, one entry per version.
    static std::vector<std::pair<std::string, std::string>>
    FindSupportedRoms(const std::vector<std::string>& searchPaths);
    std::string GetRomPath();
    bool GenerateOTR(std::string appShortName = "");
    bool GenerateOTR(std::atomic<size_t>& assetCount, std::string appShortName = "");
    bool GenerateOTR(std::atomic<size_t>& assetCount, std::atomic<size_t>& totalAssets, std::string appShortName = "");
    // GenerateOTR with the directories named, for callers predating the engine.
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
