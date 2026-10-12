#pragma once

#include <atomic>
#include <filesystem>
#include <string>

namespace Paperboat {

struct LanguagePackResult {
    bool ok = false;
    std::string message;
};

// Progress shared with the UI while a build runs on another thread.
struct LanguagePackProgress {
    std::atomic<int> percent { 0 };
    std::atomic<bool> running { false };
};

// True when `rom` is a supported European (PAL) Paper Mario dump: big-endian
// .z64, and either the full 64 MB image or its 48 MB trimmed form.
LanguagePackResult ValidatePalRom(const std::filesystem::path& rom);

// Builds lang_de/fr/es.o2r into `outDir` from the PAL ROM, using the US
// pm64.o2r as the template for resource formats. English needs no pack: it is
// the US text. Nothing is written unless every pack builds successfully.
LanguagePackResult BuildLanguagePacks(
    const std::filesystem::path& palRom,
    const std::filesystem::path& usArchive,
    const std::filesystem::path& outDir,
    LanguagePackProgress* progress = nullptr
);

// `Paperboat --build-language-packs <pal.z64> [pm64.o2r] [outDir]`: builds the
// packs without starting the game. Returns the process exit code.
int RunBuildLanguagePacksCli(int argc, char** argv);

} // namespace Paperboat
