#pragma once

#include "Companion.h"

#include <atomic>
#include <cstdint>
#include <filesystem>
#include <vector>

class GameExtractor {
public:
    static bool GenAssetFile();
    std::optional<std::string> ValidateChecksum() const;
    bool RunStandalone(std::string rom);
    bool SelectGameFromUI();
    void SetSearchPath(const std::string& path);
    void GetRoms(std::vector<std::string>& roms);
    std::string GetRomPath();
    bool GenerateOTR(std::string appShortName = "");
    bool GenerateOTR(std::atomic<size_t>& assetCount, std::string appShortName = "");
    bool GenerateOTR(std::atomic<size_t>& assetCount, std::atomic<size_t>& totalAssets, std::string appShortName = "");
    void WritePortVersion();
    static std::string sStatusText;
    static std::string sLastError;
    static std::atomic<int> sPhase;

private:
    std::filesystem::path mGamePath;
    std::vector<uint8_t> mGameData;
    std::string mSearchPath;
};
