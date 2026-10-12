#include "Language.h"

#include <filesystem>
#include <mutex>
#include <string>
#include <thread>

#include <SDL2/SDL.h>
#include <libultraship.h>

#include "Engine.h"
#include "FilePicker.h"
#include "language/LanguagePackBuilder.h"
#include "ui/cvar_prefixes.h"

extern "C" {
// Language chosen for this run. Game code keeps using gCurrentLanguage (0 in
// the US build) until each language-indexed table has its PAL entries.
int gGameLanguage = GAME_LANGUAGE_EN;
}

#define CVAR_LANGUAGE CVAR_SETTING("Language")

static const char* const kLanguageCodes[GAME_LANGUAGE_COUNT] = { "en", "de", "fr", "es" };

static int ParseLocale(const char* locale) {
    if (locale == nullptr) {
        return -1;
    }
    for (int i = 0; i < GAME_LANGUAGE_COUNT; i++) {
        if (std::string_view(locale).substr(0, 2) == kLanguageCodes[i]) {
            return i;
        }
    }
    return -1;
}

// First supported language in the OS preference list, English if none.
static int DetectSystemLanguage() {
    int result = GAME_LANGUAGE_EN;
    SDL_Locale* locales = SDL_GetPreferredLocales();
    if (locales != nullptr) {
        for (SDL_Locale* l = locales; l->language != nullptr; l++) {
            int id = ParseLocale(l->language);
            if (id >= 0) {
                result = id;
                break;
            }
        }
        SDL_free(locales);
    }
    return result;
}

static std::string FindPack(int language) {
    const std::string file = std::string("lang_") + kLanguageCodes[language] + ".o2r";
    for (const std::string& candidate : { "langpacks/" + file, file }) {
        const std::string path = Ship::Context::LocateFileAcrossAppDirs(candidate);
        if (std::filesystem::exists(path)) {
            return path;
        }
    }
    return {};
}

// The setting is stored as 0 = automatic, 1..4 = EN/DE/FR/ES so it maps
// directly onto the menu combo box.
int GameLanguage_GetPreferred(void) {
    int value = CVarGetInteger(CVAR_LANGUAGE, 0) - 1;
    return (value >= 0 && value < GAME_LANGUAGE_COUNT) ? value : GAME_LANGUAGE_AUTO;
}

void GameLanguage_SetPreferred(int language) {
    CVarSetInteger(CVAR_LANGUAGE, language + 1);
    CVarSave();
}

const unsigned char* GameLanguage_GetMessage(const char* name) {
    if (gGameLanguage == GAME_LANGUAGE_EN || name == nullptr) {
        return nullptr;
    }
    const std::string path = std::string("__OTR__messages/") + name;
    return static_cast<const unsigned char*>(GameEngine_GetDataExact(path.c_str()));
}

int GameLanguage_Get(void) {
    return gGameLanguage;
}

void GameLanguage_Init(void) {
    int language = GameLanguage_GetPreferred();
    if (language == GAME_LANGUAGE_AUTO) {
        language = DetectSystemLanguage();
    }

    // English is the base (US) text and needs no pack.
    if (language != GAME_LANGUAGE_EN) {
        const std::string pack = FindPack(language);
        if (pack.empty()) {
            SPDLOG_WARN("Language pack lang_{}.o2r not found; falling back to English", kLanguageCodes[language]);
            language = GAME_LANGUAGE_EN;
        } else {
            SPDLOG_INFO("Loading language pack: {}", pack);
            Ship::Context::GetRawInstance()->GetResourceManager()->GetArchiveManager()->AddArchive(pack);
        }
    }

    gGameLanguage = language;
    SPDLOG_INFO("Game language: {}", kLanguageCodes[language]);
}

bool GameLanguage_PackInstalled(int language) {
    if (language == GAME_LANGUAGE_EN) {
        return true;
    }
    return language > GAME_LANGUAGE_EN && language < GAME_LANGUAGE_COUNT && !FindPack(language).empty();
}

namespace {
std::mutex sStatusMutex;
std::string sStatus;
Paperboat::LanguagePackProgress sProgress;

void SetStatus(std::string text) {
    std::lock_guard lock(sStatusMutex);
    sStatus = std::move(text);
}

void StartBuild(const std::filesystem::path& rom) {
    const std::string archive = Ship::Context::LocateFileAcrossAppDirs("pm64.o2r");
    const std::string outDir = Ship::Context::GetPathRelativeToAppDirectory("langpacks");
    SetStatus("Building language packs...");
    std::thread([rom, archive, outDir]() {
        const Paperboat::LanguagePackResult result = Paperboat::BuildLanguagePacks(rom, archive, outDir, &sProgress);
        if (result.ok) {
            SPDLOG_INFO("Language packs created in {}", outDir);
        } else {
            SPDLOG_ERROR("Language pack build failed: {}", result.message);
        }
        SetStatus(result.ok ? result.message : "Failed: " + result.message);
    }).detach();
}
} // namespace

void GameLanguage_AddFromRomPrompt() {
    if (sProgress.running) {
        return;
    }
    Ship::FileBrowserRequest req;
    req.Title = "Select the European (PAL) Paper Mario ROM";
    req.Filters = { { "N64 ROMs (.z64)", { "*.z64" } }, { "All files", { "*" } } };
    req.StartDir = Ship::Context::GetAppDirectoryPath("boat");
    Paperboat::PickFile(std::move(req), [](std::optional<std::filesystem::path> path) {
        if (path.has_value()) {
            StartBuild(*path);
        }
    });
}

std::string GameLanguage_GetStatusText() {
    std::string text;
    {
        std::lock_guard lock(sStatusMutex);
        text = sStatus;
    }
    if (sProgress.running) {
        return text + " " + std::to_string(sProgress.percent.load()) + "%";
    }
    if (text.empty()) {
        // Hint when the chosen language has no pack yet.
        const int preferred = GameLanguage_GetPreferred();
        if (preferred > GAME_LANGUAGE_EN && !GameLanguage_PackInstalled(preferred)) {
            return "That language is not installed yet. Add it from your European ROM.";
        }
    }
    return text;
}
