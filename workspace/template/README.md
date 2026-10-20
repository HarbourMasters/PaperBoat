# PaperBoat C Mod Template

A starting point for C code mods for PaperBoat. Mods ship as C source inside an `.o2r` archive and are compiled by
TinyCC when the game starts, on desktop and Android. iOS and the web build load a mod's assets but not its code.

The build merges every `.c` file in `src/` with the game and libultraship headers it includes into one self-contained
file per source under `output/dist/`, which is packaged next to `manifest.json`.

## Layout

```
├── CMakeLists.txt
├── manifest.json        Mod metadata (name, version, author, dependencies, ...)
├── include/
│   └── mod.h            MOD_INIT / MOD_EXIT and allocator macros
├── src/
│   └── demo.c           Example mod: an item, a setting and an event
├── assets/              Optional files copied into the archive as they are
└── output/              Generated: dist/*.c, build.gen, manifest.json with code_version and api_version
```

## Building

The template lives in a PaperBoat checkout, in `workspace/<your-mod>`, with the `external/libultraship` submodule
initialized, or in the mod SDK, a zip with the same layout holding only what mods are built against: the headers, the
mod tools, this template and `workspace/online`. `cmake --build build --target mod_sdk` in a PaperBoat build writes it
as `paperboat-mod-sdk-code<code version>-api<API version>.zip`.

Requirements: CMake 3.10+ and Python 3. Pillow is needed only for `.png` files referenced with `#asset`.

```sh
cmake -B build -S .
cmake --build build --target package_mod
```

This writes `DemoMod.o2r`, named after `project()` in `CMakeLists.txt`. Copy it into PaperBoat's `mods/` folder and
start the game.

## Writing a mod

```c
#include "mod.h"

MOD_INIT() {
    // Register listeners, content and menu entries
}

MOD_EXIT() {
    // Undo anything else MOD_INIT did
}
```

When a mod unloads, everything it registered through the `port/api` headers is removed after its `MOD_EXIT`, with its
event listeners, menu entries, GUI callbacks, sounds and scripts. `MOD_EXIT` only needs to undo what the mod did by
other means. **Reload Scripts** in the Mod Menu rebuilds and reloads every mod without restarting.

### Events

Events are declared in `src/port/hooks/list/*.h` and documented in `src/port/hooks/EVENTS.md`.

```c
#include "port/hooks/Events.h"

static void LogCoins(IEvent* event) {
    OnCoinsChanged* coins = (OnCoinsChanged*) event;
}

MOD_INIT() {
    REGISTER_LISTENER(OnCoinsChanged, EVENT_PRIORITY_NORMAL, LogCoins);
}
```

Name listeners after what they do, not after the event: the event's name is already its struct type.

### The API

| Header | What it does |
|---|---|
| `port/api/item.h` | New items, badges and moves, saved by id |
| `port/api/message.h` | New text and replacements for the game's, with `<<TAGS>>` for control codes |
| `port/api/script.h` | Starts EVT scripts written with the game's `EVT_` macros |
| `port/api/world.h` | New maps in an area, and new battles |
| `port/api/savedata.h` | Values the mod keeps in the save file |
| `port/api/cvar.h`, `port/api/ui.h` | Settings, Mods menu pages and widgets, ImGui windows |
| `port/api/texture.h`, `port/api/sound.h` | Files, textures, sounds and music from the mod's archive |
| `port/api/puppet.h` | Figures that stand for other players |
| `port/api/online.h` and the other online headers | Satella rooms, relay channels, stores and the player's key |

Game headers from `include/` can be included directly, such as `common.h` for `gPlayerData` and the game's functions.

On Windows a mod can only read or write a game variable declared `extern_s`, which becomes `__declspec(dllimport)` when
TinyCC builds a mod. `gPlayerData`, `gPlayerStatus`, `gGameStatus`, `gItemTable`, `gMoveTable`, `gBattleStatus`,
`gCameras` and the other globals in `include/variables.h` that mods use most already are. Functions don't need it.

### Settings

Keep the mod's settings under its own prefix, `gMods.<mod>.`: `C_MOD_CVAR("Demo", "CoinLog")` spells it out. The
strings a widget config holds are copied, so they can come from anywhere.

### The Mod Menu

**Settings > Mod Menu** lists the installed mods, enabled and disabled, with a code icon before each code mod (one
whose manifest names a `main` or `binaries`) and a brush before each shader mod (one with `shaders` passes or
materials). Each enabled code mod also shows whether it is signed and
whether its code loaded, with the compiler's message or the reason it was skipped on hover. After **Edit**, mods can be
turned on and off and reordered; mods higher in the list are mounted later, so their files replace those of mods below
them, and their code initializes later. Dependencies always initialize first. Changes apply on **Apply & Restart**.
A mod's own pages go under the **Mods** header of the menu, next to **Satella**.

### Dependencies

A mod that needs another lists it by its manifest name, with an optional version range:

```json
"dependencies": ["Other Mod", { "name": "Core Library", "version": ">=1.2 <2" }]
```

Dependencies initialize first. A mod whose dependency is missing, failed to build or is out of range is skipped, as
are the mods that depend on it. Call into another mod with `CALL_FUNC` from `mod.h`.

## Notes

- Each source becomes one translation unit with every header it includes. Mark helpers `static`, and avoid names the
  game already uses, such as `AddItem` (an EVT function).
- `mod.h` routes `malloc` and `free` through the engine allocator.
- The build writes `code_version` and `api_version` from `src/port/api/api.h` into the packaged `manifest.json`. A mod
  loads only in a PaperBoat with the same code version and at least its API version.
- The `C_Register*` and `C_AddWidget` macros pass the size of the definition the mod was built with, so fields added
  in later versions read as zero for older mods.
- Archives can be signed with `external/libultraship/tools/sign.py`. Unsigned mods load too, marked as such.
