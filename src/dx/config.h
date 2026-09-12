#ifndef DX
#define DX

/// Creates the version string that appears on the file select menu.
/// Also used to sign save files created with this mod.
/// WARNING: name must not exceed 27 characters!
#define DX_MOD_NAME "PaperBoat"
#define DX_MOD_VER_MAJOR 1 /// Increase this when you make breaking changes to the savefile format (like reordering items)
#define DX_MOD_VER_MINOR 0 /// Increase this when adding new features or other enchancements
#define DX_MOD_VER_PATCH 0 /// Increase this when fixing bugs

/// Enables the debug menu.
#define DX_DEBUG_MENU 1

/// Loads last used save file.
#define DX_QUICK_LAUNCH 0

/// Quick launch into this battle.
/// Comment out to disable,
//#define DX_QUICK_LAUNCH_BATTLE BTL_NOK_FORMATION_00, BTL_NOK_STAGE_00

/// Skips logos (Nintendo, Intelligent Systems, etc.).
#define DX_SKIP_LOGOS 0

/// Skips the introductory storybook.
#define DX_SKIP_STORY 0

/// Skips the demo reel playing while waiting for the player to 'Press Start'.
#define DX_SKIP_DEMO 0

/// Map to load when starting a new game.
#define NEW_GAME_MAP_ID "kmr_20"

/// Entry to use when starting a new game.
#define NEW_GAME_ENTRY_ID kmr_20_ENTRY_0

/// Story progress when starting a new game.
#define NEW_GAME_STORY_PROGRESS STORY_INTRO

/// Enables the profiler, which shows lots of performance info on screen.
/// Press L + D-Pad Up to show/hide the profiler.
/// Disabled on port — relies on N64 hardware cycle counters and RDP registers.
#define USE_PROFILER 0

/// Skip laggy blur operations when opening the pause menu on emulator
#define DX_PAUSE_LAG_FIX 1

#endif
