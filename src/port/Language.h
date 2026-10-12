#pragma once

// Runtime game language. The port keeps the US engine/timing and layers the
// PAL text and localized textures on top as `lang_<xx>.o2r` packs.

#ifdef __cplusplus
extern "C" {
#endif

// Matches LANGUAGE_EN..LANGUAGE_ES in include/enums.h.
enum GameLanguageId {
    GAME_LANGUAGE_EN = 0,
    GAME_LANGUAGE_DE = 1,
    GAME_LANGUAGE_FR = 2,
    GAME_LANGUAGE_ES = 3,
    GAME_LANGUAGE_COUNT = 4,
};

// Setting value meaning "follow the operating system language".
#define GAME_LANGUAGE_AUTO (-1)

// Mounts the pack for the configured language and sets gCurrentLanguage.
// Call once after the base archives are mounted and before user mods.
void GameLanguage_Init(void);

// Language in effect for this run (what gCurrentLanguage holds).
int GameLanguage_Get(void);

// Persists the choice (GAME_LANGUAGE_AUTO or 0..3). Takes effect on restart.
void GameLanguage_SetPreferred(int language);

// Persisted choice, GAME_LANGUAGE_AUTO if unset.
int GameLanguage_GetPreferred(void);

// Bytes of a PAL-only message (e.g. "MSG_PAL_Menu_0039") from the active
// language pack, or NULL when the language is English or the pack lacks it.
const unsigned char* GameLanguage_GetMessage(const char* name);

#ifdef __cplusplus
}

#include <string>

// True when the pack for `language` (GAME_LANGUAGE_*) is installed. English
// is always available: it is the original (US) text.
bool GameLanguage_PackInstalled(int language);

// Asks for the European (PAL) ROM and builds the German/French/Spanish packs
// from it in the background. Does nothing to the game until restarted, and
// without packs the game behaves exactly as before.
void GameLanguage_AddFromRomPrompt();

// One-line status for the settings menu ("" when there is nothing to say).
std::string GameLanguage_GetStatusText();
#endif
