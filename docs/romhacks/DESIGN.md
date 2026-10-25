# Romhacks design

This document describes how Paperboat supports existing paper mario romhacks, so that contributors can port new romhacks in a consistent way.

For applying a romhack, see [Playing a romhack](PLAYING.md).

---

Paper Mario keeps most of its data compiled into the game code (move and item tables, sprite set sizes, message section lists, map texture sizes), and Paper Mario romhacks are mostly built with either [Star Rod or DX](https://docs.starhaven.dev/papermario-dx/), which relocates and repacks large parts of the ROM. Paperboat always runs its own game logic, while a romhack brings its assets and data as an overlay, and the custom code is ported by hand.

**Design**

```
                         ROM SOURCES
     ┌──────────────────┐          ┌──────────────────────────┐
     │  US Paper Mario  │          │  US Paper Mario +        │
     │  (base rom)      │          │  romhack patch (.bps)    │
     └────────┬─────────┘          └────────────┬─────────────┘
              │                                 │
              ▼                                 ▼
   ┌─────────────────────┐        ┌──────────────────────────────┐
   │  First boot         │        │  Settings -> Romhack Menu    │
   │                     │        │  "Generate Romhack from ROM" │
   └──────────┬──────────┘        └──────────────┬───────────────┘
              │                                  │
              │                       ┌──────────┴───────────┐
              │                       │  Rejected if:        │
              │                       │  - no config.yml     │
              │                       │    entry (SHA1)      │
              │                       │  - no base game yet  │
              │                       └──────────┬───────────┘
              ▼                                  ▼
   ┌─────────────────────┐        ┌──────────────────────────────┐
   │  pm64.o2r  (BASE)   │        │  mods/~romhacks/<stem>.o2r   │
   │  - full game        │        │  - changed assets only       │
   │  - portVersion      │        │  - romhack/<table> blobs     │
   │                     │        │  - manifest.json             │
   └──────────┬──────────┘        └──────────────┬───────────────┘
              │                                  │
              └────────────────┬─────────────────┘
                               ▼
         ┌─────────────────────────────────────────────┐
         │  BOOT                                       │
         │  1. mount pm64.o2r, romhack, HD pack, mods  │
         │  2. Port::ApplyDataTables()  (FinishInit)   │
         │  3. Port::Init()  -> REGISTER_LISTENER(...) │
         │     (ShipInit)                              │
         └─────────────────────────────────────────────┘
```


1. **Base rom and romhack**: Paperboat distinguishes between the **base rom**, a US Paper Mario ROM extracted into `pm64.o2r`, and a **romhack**, an o2r file in `mods/~romhacks/` that holds only what the hack changed. A romhack can't be extracted, or picked at first boot, without the base game.

2. **Curated romhacks**: every supported romhack has a hand-made entry/recipe in `config.yml`, keyed by the SHA1 of the patched ROM. A ROM without an entry is rejected.

   ```yaml
   <patched ROM SHA1>:
     name: <Name>                           # shown in menus, stamped into saves
     path: ./assets/yaml/romhacks/<stem>    # YAML holding only the changed assets
     romhack:
       id: <Id>                             # matches specific/<Id>.cpp
       version: "<version>"
       url: <download page>                 # linked from the Supported Romhacks tab
       works_with: [vanilla]                # optional, default vanilla
       disable: [<feature id or group.*>]   # optional, see Feature rules
       force: { <feature id>: <value> }     # optional, see Feature rules
     config:
       gbi: F3DEX2_PM64
       gbi_floats: false
       sort: OFFSET
       logging: WARN
       output:
         binary: mods/~romhacks/<stem>.o2r
         headers: include
         code: code
   ```

3. **Detecting the romhack**: during extraction, Torch writes a root `manifest.json` (see [Manifest](#manifest)) into the romhack o2r in place of the base game's `portVersion`, built from the `romhack:` block. At boot, the manifest tells the port which romhack is loaded, which code port to run and which feature rules apply. Archives extracted before the manifest existed carry a `romhack/info` marker (YAML `id`, `name`, `version`, `rom_sha1`) instead, which is still read when there is no romhack manifest. Such an archive takes its `works_with`/`disable`/`force` from the matching `config.yml` entry at boot (`Romhack::FindConfigManifest`: the entry whose key is the marker's `rom_sha1`, else the one whose `romhack.id` is the marker's id); re-extracting the hack embeds them in its `manifest.json`.

4. **Loading order**: the base game loads first, then the selected romhack, then mods. Resources are looked up by path, so the romhack shadows the base game, and the HD pack and mods shadow both. Only one romhack is active at a time; it's stored in `gSettings.Romhack.Selected`, and the `-hack <stem>` launch argument overrides it for a single launch.

5. **Data tables**: tables compiled into the game code can't be swapped by an asset. Their hack values ship as `romhack/<table>` blobs in the romhack o2r, and the hack's code port copies the fields it trusts over   the compiled table at boot. This step runs before `ShipInit`, so enhancements that snapshot those tables (e.g. *Free QoL Badges* saves the BP costs) see the hack's values.

6. **Custom code**: each hack with code has a `Romhack::Port` subclass in `src/port/romhack/specific/<Id>.cpp`, listed in the X-macro `ROMHACK_PORT_LIST`. Only the active hack's port is created. All custom logic goes through **game hooks** (`REGISTER_LISTENER`) and the **modding layer** (`src/port/modding/`, see [The modding layer](#the-modding-layer)). If no event or `Mod_` call fits where a hack changes the logic, a new generic one is added instead of editing decomp code for one hack.

7. **Identity and saves**: each romhack has its own saves folder, `saves/~romhacks/<stem>/`. Saves are stamped with the romhack's name instead of the dx mod name or `PaperBoat`, so a save from one romhack is shown as incompatible in another. A version bump keeps the same name, so saves stay loadable across versions. The dx `majorVersion`/`minorVersion`/`patchVersion` fields keep describing the save format for PaperBoat as a whole while the romhack's own version is written as a separate `romhackVersion` string in the JSON file. The Blueprint Editor's autosaved presets follow the same split: `actor_blueprints.json` in the app folder for the base game, `saves/~romhacks/<stem>/actor_blueprints.json` for a romhack (vanilla overrides are not carried over, since they were tuned for vanilla enemies).

8. **Romhack Menu**: romhacks are managed in **Settings → Romhack Menu**, separate from the Mod Menu. It holds the *Generate Romhack from ROM* button, the *Installed Romhacks* list (one enabled at a time) and the *Supported Romhacks* list with download links, read from `config.yml`.

> [!NOTE]
> starting a folder name with `~` means it's a reserved folder name and it's managed by the port.

### Manifest

Every mounted archive is a mod; a romhack is a mod with `kind: romhack`. A mod may carry the LUS root `manifest.json`, with the PaperBoat keys in a `paperboat` object. Without a manifest (or without the `paperboat` object) it is a plain asset mod: no rules, works with everything.

```json
{ "name": "<Name>", "version": "<version>",
  "paperboat": { "id": "<Id>", "kind": "romhack", "rom_sha1": "...",
                 "works_with": ["vanilla"],
                 "disable": ["enhancements.no_intro", "graphics.status_bar.*"],
                 "force": {} } }
```

| Key | Meaning |
|---|---|
| `name`, `version` | LUS manifest fields. `name` is what menus and "Disabled by" tooltips show (the file name when missing); LUS needs it to parse the rest of its own fields |
| `paperboat.id` | stable owner id (romhack id for romhacks; the file name when missing) |
| `paperboat.kind` | `mod` (default) or `romhack`. A `romhack` archive in `mods/` is not loaded; romhacks go in `mods/~romhacks/` |
| `paperboat.rom_sha1` | romhacks: SHA1 of the patched ROM |
| `paperboat.works_with` | list of bases: `vanilla`, romhack ids, or `*`. Missing = works with everything. For a romhack it is what the hack is built on (always `vanilla` today) |
| `paperboat.disable` | feature ids or `group.*` wildcards the mod turns off |
| `paperboat.force` | `{ feature id or group.*: value }`: toggles and ints take a number or bool, colours `[r, g, b(, a)]` or `"#RRGGBB(AA)"` |

The manifest is read per archive (`Mod::ReadManifest`, `src/port/modding/ModManifest.h`), never through the merged VFS: every archive ships `manifest.json` at the same path, so the shared index only returns the top archive's copy.

- **Mount loop** (`UpdateModFiles`): each enabled mod is opened, its manifest read, and it is only mounted if `works_with` includes the active base (`vanilla` or the active romhack id). An incompatible mod stays in `EnabledMods`, so switching back to its base loads it again; the Mod Menu shows it greyed with the reason.
- **Rule resolution** (`Features::ResolveMounted()`, called from `FinishInit` right after `UpdateModFiles(true)`, before the data tables, events and `ShipInit`): sources in load order are the built-in rules, the romhack, then each mounted mod.

### Feature rules

`src/port/modding/Features.h` is the registry of port features a mod can lock. Rules are boot-time constants; changing the mod set or the romhack needs a restart (already true).

- `disable` is the union over every source: reads return the feature's registered default and actions refuse.
- `force` pins a value; when two sources force different values, the later in load order wins, the conflict is logged and listed in the Mod Menu. A forced value wins over a disable.
- The built-in rule: `save.import_n64` is disabled whenever a romhack is the base. There is no per-hack import fixup; an imported save is stamped with the active mod name (`Port_CopyModName`).
- Per-hack rules live in each hack's `config.yml` `romhack:` block and are listed in its page; Paper Peach has none.
- `settings.*` (audio, controls, menu, renderer, mod/romhack selection) is never lockable; unknown ids are logged and ignored.
- Nothing writes CVars: the user's own value is kept and comes back once the rule is gone.

| API | Use |
|---|---|
| `bool Port_FeatureAllowed(const char* id)` (C) | false while any source disables the feature; for actions, windows, debug menu entries |
| `int32_t Port_FeatureInt(const char* id, int32_t fallback)` (C) | forced value, else the registered default while disabled, else the feature's CVar (`fallback` is the CVar default) |
| `float Port_FeatureFloat(const char* id, float fallback)` (C) | the same for float CVars |
| `Color_RGBA8 Port_FeatureColor(const char* id, Color_RGBA8 fallback)` (C++) | the same for colour CVars (`<cvar>.Value`) |
| `const char* Port_FeatureDisabledBy(const char* id)` (C) | name of the first source that disables it, or NULL |
| `Features::IsLocked`, `Features::LockReason`, `Features::ForCVar`, `Features::Conflicts`, `Features::DrawLockedNotice` (C++) | UI: "Disabled by X" / "Set to V by X", the widget-CVar lookup, the conflict list, the notice a dev window draws instead of itself |

The menu greys a locked widget in `Menu::MenuDrawItem` (a third disable source after `activeDisables` and the race lockout): the feature comes from `WidgetInfo::feature` (`.Feature(id)`, for buttons and windows) or from the widget's CVar, the tooltip lists "Disabled by <mod name>", and the flag is set and cleared every frame. Dev windows draw the notice instead of the tool, the TAB alternate-assets hotkey does nothing while `graphics.alt_assets` is locked, init-time listeners (Free QoL Badges, the texture filters) read the registry when `ShipInit` runs, and the DX debug menu draws locked entries in red and ignores them.

| Id | CVar | Default when disabled |
|---|---|---|
| `cheats.infinite_health` | `gCheats.InfiniteHealth` | 0 |
| `cheats.infinite_fp` | `gCheats.InfiniteFlowerPoints` | 0 |
| `cheats.no_bp_cost` | `gCheats.NoBPCost` | 0 |
| `cheats.max_star_power` | `gCheats.MaxStarPower` | 0 |
| `cheats.max_power_bounce` | `gCheats.MaxPowerBounceChance` | 0 |
| `cheats.double_rewards` | `gCheats.DoubleRewards` | 0 |
| `enhancements.prevent_lz_storage` | `gEnhancements.PreventLoadingZoneStorage` | 0 |
| `enhancements.sprint_button` | `gEnhancements.SprintButton` | 0 |
| `enhancements.free_qol_badges` | `gEnhancements.FreeQoLBadges` | 0 |
| `enhancements.action_command_difficulty` | `gEnhancements.ActionCommandDifficulty` | 0 |
| `enhancements.block_window` | `gEnhancements.BlockWindowMode` | 0 (original) |
| `enhancements.no_intro` | `gEnhancements.NoIntro` | 0 |
| `enhancements.actor_blueprints` | `gEnhancements.ActorBlueprints.Enabled` | 0 |
| `graphics.full_height_view` | `gEnhancements.Graphics.FullHeightView` | 0 |
| `graphics.rounded_reel` | `gEnhancements.Graphics.RoundedReel` | 0 |
| `graphics.disable_mipmaps` | `gEnhancements.Graphics.DisableMipmaps` | 0 |
| `graphics.alt_assets` | `gEnhancements.Mods.AlternateAssets` | 0 |
| `graphics.hd_mipmaps` | `gEnhancements.Mods.AutoMipmaps` | 0 |
| `graphics.sprite_filter` | `gSettings.2DTextureFilter` | 0 |
| `graphics.dialogue_filter` | `gSettings.DialogueTextFilter` | 0 |
| `graphics.interpolation_fps` | `gSettings.InterpolationFPS` | 30 |
| `graphics.match_refresh_rate` | `gSettings.MatchRefreshRate` | 0 |
| `graphics.texture_cache` | `gGraphics.TextureCache` | 0 (auto) |
| `graphics.shaders` | window `ShaderSettings` | menu button only |
| `graphics.status_bar.always_show` | `gEnhancements.StatusBar.AlwaysShow` | 0 |
| `graphics.status_bar.scale` / `.box_width` / `.box_height` | `gEnhancements.StatusBar.Scale` / `BoxWidth` / `BoxHeight` | 100 |
| `graphics.status_bar.show.{background,hp,fp,star_power,star_points,coins}` | `gEnhancements.StatusBar.Show*` | 1 |
| `graphics.status_bar.show.{star_pieces,badges}` | `gEnhancements.StatusBar.Show*` | 0 |
| `graphics.status_bar.flat_bottom` / `.flat_color` | `gEnhancements.StatusBar.FlatBottom` / `FlatColor` | 0 |
| `graphics.status_bar.highlight_color` / `.shadow_color` / `.fill_color` | `gEnhancements.StatusBar.*Color` | the vanilla colours |
| `graphics.status_bar.reset` | (Reset Status Bar button) | action |
| `save.import_n64` | (Import N64 Save + its slot combos) | action |
| `devtools.debug_menu` | `gDeveloperTools.DebugMenu` | 0 |
| `devtools.debug_menu.{full_restore,save_load,map_select,battle_select,story_byte,sound_player,partners,inventory,collision,cheats}` | DX debug menu entries | action |
| `devtools.debug_menu.evt_debugger` | DX script debugger (D-pad Right) | action |
| `devtools.save_editor` / `.blueprint_editor` / `.event_debugger` / `.value_viewer` | windows `SaveEditor` / `ActorBlueprintEditor` / `EventDebugger` / `ValueViewerSettings` | window |
| `devtools.console` / `.stats` | windows `Console` / `Stats` (LUS) | menu button only |
| `devtools.gfx_trace` | `gDeveloperTools.GFXTrace` | 0 |

### Layers

A romhack is split into three layers, each with its own path into the port:

| Layer | Where it comes from | Example |
|---|---|---|
| **Assets**: sprites, messages, icons, map textures, collision | delta YAML -> romhack o2r | a hack's sprites, dialog msgs...etc |
| **Data tables** compiled into the port | `romhack/<table>` blobs -> the hack's `Port::ApplyDataTables()` via `Mod_LoadTable` | move FP/BP costs, item descriptions, player sprite raster sizes, ...etc |
| **Custom code**: overlays, scripts, injected code, strings kept in the original romhack code | `Port::Init()` in `src/port/romhack/specific/<Id>.cpp`, through game hooks and `Mod_` calls | pause menu labels, resized map texture sizes, new behaviour |

### The romhack specifics interface

```cpp
namespace Romhack {
class Port {
  public:
    // End of FinishInit, before ShipInit.
    virtual void ApplyDataTables() {}

    // ShipInit. Register game hooks and Mod_ calls here.
    virtual void Init() {}
};
}
```

A hack's file subclasses `Port` and exposes `Create<Id>Port()`, and `<Id>` is added to `ROMHACK_PORT_LIST` in `src/port/romhack/RomhackRegistration.cpp`. `ApplyDataTables()` reads its blobs with `Mod_LoadTable("romhack/<table>")` and decodes them with `Mod_ReadBE32`/`Mod_ReadBE16`. `Init()` runs once per launch, and since switching romhacks needs a restart, listeners never need unregistering. The modding services register their own listeners once at startup (`ShipInit` or `Mod::ListenServices()` right after it), never on first use, so the registering `Mod_*` calls are safe from `ApplyDataTables()` too.

### The modding layer

The romhack code doesn't touch decomp code directly. It goes through `src/port/modding/`, a set of C-callable `Mod_` seams the game calls into, which isn't specific to romhacks: any PaperBoat mod can use it the same way. `port/modding/Mod.h` includes all of it.

| Header | API | Game side |
|---|---|---|
| `ScriptOverrides.h` | `Mod_ReplaceScript(owner, original, replacement)` | `start_script*`, `start_child_script`, the `Jump` opcode and `IsEventForSourceRunning` fire `OnScriptResolve` (pre-filled with the script the game asked for); the service's listener, registered at startup, swaps in the latest replacement and returns at once while nothing is replaced |
| `BattleOverrides.h` | `Mod_SetBattleList` / `Mod_SetStageList` / `Mod_SetBattleDmaTable(owner, area, ...)`, `Mod_ReplaceActorBlueprint(owner, original, replacement)` | `gBattleAreas`, `OnActorBlueprintLoad` |
| `Messages.h` | `Mod_RegisterInlineMessage(owner, bytes)`, `MOD_INLINE_MSG_SECTION` (`0xFE`) | `load_msg_asset` fires `OnMessageLoad` (pre-filled with the vanilla asset, null for IDs outside the compiled sections). The service's listeners are registered at startup, so they answer for every hack: inline bytes for section `0xFE`, otherwise the `__OTR__messages/MSG_mod_SS_IIII` asset; a final (HIGH) listener answers an ID nobody else did with message 0/0 (`MSG_NONE`) and warns once |
| `Popups.h` | `Mod_RegisterBattlePopup(owner, msgID, layoutLike)` (next free index `>= 0x100`), `Mod_RegisterBattlePopupAt(owner, index, msgID, layoutLike)` (a fixed index, also over a vanilla one; `-1` if another owner holds it) | the battle popup sites fire `OnBattlePopupMessage(index, *layout, *msgID)`; for a registered index the service answers the message and the vanilla `BTL_MSG_*` whose case supplies the timing, box and draw (`layoutLike`) |
| `WindowStyles.h` | `Mod_RegisterWindowStyles(owner, styles, count)` → first style ID of a contiguous block of free slots in `23`-`100` (`DefaultWindowStyle`, `include/draw_box.h`; every call gets its own block, a second call by the same owner never overwrites the first) | `draw_box` treats a style argument up to `100` as a style ID, like vanilla's `0`-`22`, and fires `OnWindowStyle` for the registered range only; an ID nobody answers draws as `WINDOW_STYLE_0` |
| `MapRegistry.h` | `Mod_AddArea`, `Mod_AddMap`, `Mod_RegisterMapResetData`, `Mod_FindMapConfig` | `gAreas`, `OnMapLoad` |
| `EvtBuffers.h` | `Mod_RegisterWideEvtBuffer(owner, buf, count)` | `BufRead`/`FBufRead`/`BufPeek` read through `evt_buffer_next`/`evt_buffer_at` (`functions.h`), which the service defines: inside a registered range they step `sizeof(Bytecode)`, otherwise 4 bytes as vanilla |
| `MapTextures.h` | `Mod_OverrideMapTextureSize(owner, archive, name, w, h)` | the map texture loader reads `Mod_GetMapTextureSize` |
| `DataTables.h` | `Mod_LoadTable(path)`, `Mod_ReadBE32`, `Mod_ReadBE16` | blobs from any mounted o2r |
| `ModSaveData.h` (C++) | `Mod_RegisterSaveData(owner, key, { save, load, clear })` | per-save hack state, written as native JSON under `modData.<owner>.<key>` in the save file; `load` runs when a save is read (a `load` that throws, e.g. on a wrong-typed value, is logged and that key falls back to `clear` and is dropped from the file on the next write), `clear` when the key is missing, on a new file and whenever `clear_player_data` fires `OnPlayerDataClear` |
| `ActorExt.h` | `Mod_RegisterActorExt(owner, size)` → handle, `Mod_ActorExt(handle, actorID)`, `Mod_PartnerExt(handle, partnerID)` | typed per-actor battle records (player, partner, 24 enemies) plus per-partner records that survive swaps; all zeroed at `OnBattleInit(BEGIN)`, an enemy's record also at `OnActorCreated`; the player and partner actor records are kept across a mid-battle partner swap. The service's listeners are registered once at startup (`Mod::ListenServices`, after the hack's `Init`), so the LOW clears run before a hack's own LOW listeners |
| `Abilities.h` | `Mod_RegisterAbility(owner, moveID, holder)` → ability ID (`>= MOD_ABILITY_BASE`, `0x100`), `Mod_GetBadgeBPCost(itemID)` | an `OnAbilityCount` listener at `EVENT_PRIORITY_LOW` (dispatched first, so other listeners can still adjust the count) counts the equipped badges with that move for the holder (`MOD_ABILITY_HOLDER_PLAYER` or `_PARTNER`); the BP cost helper fires `OnBadgeBPCost` for port-drawn badge panels |
| `BattleMenus.h` | `Mod_AddBattleMenuEntries(owner, menu, provider)`, `Mod_AddBattleMenuHud(owner, menu, hud)`, `Mod_AllocBattleMenuType(owner)` (`0x40`-`0x7F`); list helpers `BattleMenu_Count/At/FindType/FindMove/Insert/Remove/Initial/SetInitial` | each battle menu builder (`WHEEL`, `STRATEGIES`, `MOVES`, `PARTNER_LIST`) fires `OnBattleMenuBuilt` once with vanilla's finished list; the service turns it into typed `BattleMenuEntry` rows, runs the providers in registration order and writes the list back (with no provider for that menu nothing is touched; the builder clamps the returned count to `0`..capacity and the initial position to the list). `MOVES` lists are views: rows can be hidden or restyled, not added, and keep their index into `submenuMoves`. A chosen Strats entry of a port type runs its `onSelect` after vanilla's teardown (`OnBattleMenuSelect`, which the service cancels when an `onSelect` ran; a Strats choice nobody handles reopens the player or partner menu); wheel entries get `onSelect` as a notification. A HUD draws per entry (`OnBattleMenuDrawEntry`) and owns HUD elements for the wheel's lifetime (`OnBattleMenuCreated`/`OnBattleMenuDestroyed`); a Strats entry's error text and a moves row's cost palette come from the entry (`OnBattleMenuErrorText`, `OnBattleMenuCostStyle` with the row's list index, not its sorted display row) |
| `Panels.h` | `Mod_ReplacePanel(owner, panel, ops)` (`MOD_PANEL_STATUS_BAR`, `MOD_PANEL_PAUSE_STATS` ... `_MAP`; `ModPanelOps` `init`/`sync`/`input`/`update`/`draw`/`cleanup`/`numCols`/`numRows`, a null callback keeps vanilla), `Mod_VanillaPanel(panel)` (the vanilla callbacks, to wrap), `Mod_PanelReplaced(panel)`, `Mod_ReplaceBattleState(owner, state, { update, draw })`, `Mod_OpenPopupPanel(owner, menu, { open, frame, close })` | one owner per panel or state (a second owner is refused and logged). Status bar: `update_status_bar` fires `OnStatusBarPanel` (INIT after vanilla created its HUD elements, SYNC inside `sync_status_bar`, DRAW cancellable between the update and draw halves, before the scale is applied); `init`/`sync` run after vanilla's, `draw` replaces vanilla's draw half. A replaced bar still gets the Status Bar options through the vanilla update half (Always Show, and Scale/Box Height through the retracted position); a hack whose bar should ignore them disables `graphics.status_bar.*` in its manifest, which makes those reads return the 100% / off defaults. Pause: `pause_init`/`pause_cleanup` fire `OnPauseMenu` (`PAUSE_MENU_OPEN` before the panel inits, `PAUSE_MENU_CLOSE` after the panel cleanups); for the session the service puts a port-owned copy of each replaced `MenuPanel` into `gPausePanels` (its own `numCols`/`numRows`, callbacks routed to the replacement or vanilla) and points the content window's draw at the replacement, then copies the panel state back at close. A replacement `init` must set `initialized` and set up its windows; a replacement `input` returns to the tab row with `gPauseMenuCurrentTab = 0`. Battle states: `btl_state_update_defeat` fires cancellable `OnBattleStateUpdate` (only DEFEAT has the hook; `draw` is reserved). Popup sub-panel: opened from a cancelled `OnPopupMenuChoose`; the service parks the popup, hides its content/description/prompt windows, calls `frame` once per status UI pass (first frame without input), and on BACK returns the popup to choosing (same frame), on CHOSE ends it with the choice (next frame); `close` runs on the frame after, or when the popup is destroyed while the panel is open |
| `Inventory.h` | `Mod_SetItemCapacity(owner, capacity)`, `int32_t capacity(void)` | `get_consumables_capacity()` (`inventory.h`) calls the provider (10 with none) and clamps it to `[1, INV_ITEMS_MAX]` (32, the size of `PlayerData.invItems`); every carried-item loop in the decomp (add/remove/find/count/sort, pickup, throw-away popup, pause Items tab, item popups, shops, battle item and Dip menus) reads it. Storage stays 32. One provider at a time: a second owner wins and is logged. The provider must not query consumables (`find_item` on a key item is fine). Items left above a shrunk capacity stay in the save, hidden, until it grows again |
| `VertexColors.h` | `Mod_SetVertexColor(ModVertexRef ref, r, g, b, a)`, `Mod_SetVertexColorRGB(ref, r, g, b)` (keeps alpha); `ModVertexRef` = `{ vtxAsset, index }` | writes `Vtx.v.cn` of one vertex of an OTR vertex resource (`vtxAsset` = the resource path, `__OTR__` prefix optional), the same resource the renderer draws (alternate assets included). The index is checked against the resource's vertex count; a missing asset or an index out of range is a no-op, logged once per asset. The resource is looked up on every write (a cache hit; the vertex count is re-read only when the returned pointer changes, e.g. after the alternate-assets toggle), so writes always land in the buffer the renderer currently resolves; an asset that was missing once is not looked up again. Fast3D reads vertex colours when the display list runs at the end of the frame, so a write from `EntityPreDraw` or earlier shows that frame and needs no invalidation. The resource is shared by every model that draws it, and a write stays until restart (not owner-scoped, nothing is restored on unregister). A logical vertex that the asset export split into two resources is two refs |
| `InputHistory.h` | `Mod_InputFrame()`, `Mod_InputPressedAt(frame)`, `Mod_InputHeldAt(frame)`, `Mod_InputMatches(pressed, mask, match)`, `Mod_InputPressedSince(frame, mask, match)`, `Mod_InputPressedWithin(frames, mask, match)`, `Mod_InputFirstPress(since, mask, match)` (frame or `-1`), `Mod_RegisterInputFrameListener(owner, fn(frame, held, pressed))`; EVT natives `Mod_EvtInputMarkFrame(out frame)`, `Mod_EvtInputPressedSince(frame, mask, match, out bool)`, `Mod_EvtInputPressedWithin(frames, mask, match, out bool)` | a ring of the last `MOD_INPUT_HISTORY_FRAMES` (64) game steps of controller 1 (`curButtons[0]`, `pressedButtons[0]`), recorded by a `GameFrameUpdate` listener (`EVENT_PRIORITY_LOW`) at the top of `step_game_loop`, before `update_input`. So frame `N` holds the buttons of the step that just finished, as its scripts and its draw saw them, and is readable from the next step's scripts on; it doesn't depend on the draw running. Frames count from 1 (`0` = nothing recorded); `Mod_InputFrame()` is the newest. "Since `T`" means the frames after `T` up to the newest, "within `n`" the newest `n`; older frames than the ring holds are not searched and `PressedAt/HeldAt` read 0 for them. `match`: `MOD_INPUT_MATCH_ANY` (any bit of `mask`), `MOD_INPUT_MATCH_ONLY` (a bit of `mask` and no other button), `MOD_INPUT_MATCH_BYTE_EXACT` (each byte of the button word that `mask` touches equals `mask`'s byte, e.g. `BUTTON_A` alone among A/B/Z/Start/D-pad: the N64 hacks' `lbu`-compare of `pressedButtons` byte 1). Frame listeners run after the frame is stored, in registration order |

GameFlag/GameByte indices at and above `0x1000` (Star Rod's extended globals) need no API: `SaveData.globalFlags` and
`globalBytes` are sized for them (`SAVE_GLOBAL_FLAG_WORDS`, `SAVE_GLOBAL_BYTE_COUNT`), so `vars_access.c` is vanilla.
The JSON save writes the vanilla 64 words / 512 bytes and only extends the arrays up to the last nonzero entry. The
N64 flash importer copies Star Rod's extended region (flash offsets `0x2000`/`0x3000`) into the same indices.

Every registering call takes an `owner` string first (`"PaperPeach"`, ...), stored with the entry. The services on a hot path (script replacement, wide EVT buffers) cost a single compare while nothing is registered. The EVT buffer readers run per `BufRead`, so they are port-owned accessors (like `get_consumables_capacity()`) rather than an event dispatch.

- When an owner registers over an entry another owner already holds (the same script, blueprint, battle area list, map texture, overlapping wide buffer or reset data), the new one wins and the conflict is logged.
- `Mod_UnregisterOwner(owner)` removes everything that owner registered: script and blueprint replacements, inline messages, wide buffers, map texture sizes, map reset data, abilities, the item capacity provider, input frame listeners, battle menu providers, HUDs and allocated battle menu types (a freed type is handed out again), battle popups, window styles and panel/battle-state replacements. Overridden battle lists, stage lists and DMA tables go back to the previous owner's value, or to the original that was saved when the area was first overridden. Maps the owner added are removed from their areas, and a vanilla area whose added maps are all gone gets its compiled map list back.
- Freed inline message IDs are never reused, so a stale ID loads nothing instead of another owner's message.
- Areas and maps are indexed and those indices are saved, so a rollback can't always be complete: an owner's area is only cleared when it's the last one in `gAreas` (or every area after it is cleared too), otherwise it stays registered with no maps; removing maps that other owners appended after moves their indices, which is logged.

### Game events

Engine changes that a modding call can't express go through game events (`src/port/hooks/list/GameEvent.h`,
registered in `PortEnhancements.cpp`). A site calls `CALL_EVENT` with pointers to the values a listener may change,
and with no listener the site behaves exactly as before. Most events are families: one event per subsystem, with a
`stage` (or `site`) field that says which program point fired it, so a listener filters on the stage it ports.

| Family | Covers |
|---|---|
| `OnAbilityCount`, `OnAbilityEffect`, `OnBadgeBPCost` | how many copies of an ability an actor has (fired by `is_ability_active` with a null actor for Mario, and by the partner/enemy ability queries; silent for Peach and Attack FX), the size of one ability's effect at its vanilla site (pre-filled with the vanilla value, keyed by ability), and a badge's BP cost |
| `OnTurnEndRecovery`, `OnPlayerSpeedUpdate`, `OnPlayerSpinStart` | the end-of-turn drain/HP/FP recovery amounts, walk/run speed every frame, the spin speed scale when a spin starts |
| `OnAttackBegin`, `OnDamageAttackerResolve`, `OnHitCheck`, `OnDamageCalc`, `OnPowerBounceDamage` | an attack API's damage/status arguments, who performs an item attack, the hit decision (`phase` TEST in the test APIs, STRIKE at the damage functions' miss gates) and the damage arithmetic (`stage` BASE, AFTER_BOOSTS, AFTER_DEFENSE, AFTER_BADGES, GUARD, FINAL; `source` ENEMY/PLAYER/PARTNER/ITEM). FINAL is the value about to be taken from HP. On the PLAYER, PARTNER and ITEM paths it fires before the hit counters; on the ENEMY path (`calc_enemy_damage_target`) it fires only where HP is really applied (not for DAMAGE_IMMUNE parts, tutorial battles or `ACTOR_FLAG_NO_DMG_APPLY`), after `OnPlayerDamageReceived` and the `damageCounter`/`hpChangeCounter` updates, so a FINAL listener there changes the HP loss and `lastAttackDamage` but not those counters |
| `OnDamageDefense`, `OnGuardCheck`, `OnGuardInput`, `OnBlockWindowCheck` | the target's defense against a hit (before vanilla voids it for All or Nothing, ignition explosions and `STATUS_ALWAYS_HITS`), whether Mario/the partner may guard, the guard result after the vanilla input read (`GUARD_RESULT_NONE`/`GUARD`/`SUPERGUARD`; SUPERGUARD = no damage, attack blocked, no rating), and the guard input window per button plus whether a successful guard consumes the input buffer (the Block Window enhancement only widens the vanilla A guard, `buttonMask == BUTTON_A` with `consumeInput` set, and never narrows a window an earlier listener set) |
| `OnActorHpChange`, `OnActorDefeatCheck`, `OnDamageEventDispatch`, `OnDamagePopupKind` | an HP change about to be applied (`source` `HpChangeSource`, signed `delta`, cancellable = "a listener applied it"; null actor for field sources, which are always Mario; a cancelled partner change also skips vanilla's partner KO), whether an actor is out (`btl_check_player_defeated`, item death check), the damage event about to be dispatched to a target (cancellable = "a listener dispatched it"), and primary vs. stacked damage popups |
| `OnContactHazard`, `OnContactCounter`, `OnAttackStatusSelect` | contact hazard damage (`attacker` = the actor whose spikes/fire/shock/counter hurt `victim`; `ContactHazard` enum, spiky-top separate; a negative value is clamped to 0), whether touching the target counters the enemy attacker (`CONTACT_COUNTER_NONE`/`SHOCK`/`GUARD`), and which status Mario's attack tries in vanilla's shrink slot |
| `OnActorStat`, `OnInflictStatus`, `OnStatusChance`, `OnStatusTick`, `OnActorBoost`, `OnBuffsClear`, `OnStatusIconDraw` | statuses, buffs and their turn counters (`OnStatusTick` phases also mark the end of an actor's move, `ACTION_END`, and the partner's turn end, `PARTNER_TURN_END`, where cancelling holds the state for a frame; `PARTNER_TURN` is vanilla's countdown at the start of the partner's turn, which is only the KO countdown, so it fires only while the partner is KO'd. `OnBuffsClear(DISPEL)` is pre-filled with `BOOSTS` whenever the target has a boost, static or transparency, because vanilla's dispel clears the boost fields in all those cases; each bit gates its own removal) |
| `OnTurnOrder`, `OnBattleStateChanged`, `OnPartnerChange` | turn order decisions (`decision` `TurnOrderDecision`: who acts first in the player phase, where Mario stands, whether the partner sits a turn out, the Z swap and partner change permissions, the first strike, whether a failed flee uses up both the player's and the partner's turn; the value is a typed actor class, bool or enum, pre-filled with vanilla's choice), a notification at the end of every `btl_set_state` with the previous and final state (also when they are equal; a `btl_set_state` from inside a listener is queued and notified after the current dispatch finishes, as one change from the state being notified to the final state, so several nested calls in one dispatch collapse into one notification), and a partner leaving or entering (`PARTNER_CHANGE_LEAVE`/`ENTER`, battle swap or overworld wheel swap; listeners check `gGameStatusPtr->context`) |
| `OnBattleInit`, `OnBattleScriptLoad`, `OnBattlePartnerSelect`, `OnBattleMenusEnabled`, `OnStatusAfflictedNotice` | battle flow: setup stages, the main script of a move, item or star power about to run (`kind` MOVE/ITEM/STAR_POWER, replaceable), the partner brought into a battle, the menus enabled at battle start, and which afflicted status the enemy-phase message announces (a camera preset outside `BattleCamPreset` falls back to `BTL_CAM_PLAYER_STATUS_AFFLICTED`) |
| `OnMoveFPCost`, `OnMoveCostDisplay`, `OnBattleBadgeMenuEntry` | a move's FP cost where vanilla computes it (`use` ENABLE in the menu builders, DEDUCT in `deduct_current_move_fp`, where a negative cost is clamped to 0; pre-filled with the vanilla cost, `row` = the submenu row), what the moves list shows as cost, discount and discount colour, and which badge an equipped slot adds to the Jump, Hammer or Items list (0 = none; an ID outside the item table counts as none) |
| `OnBattleMenuOpen`, `OnBattleMainMenuInput`, `OnSwapRefused`, `OnTargetName`, `OnBattleDefendBegin`, `OnBattleDefendEnd` | a player or partner menu opening, the top of every wheel update (for extra inputs), the message when Z can't swap, the name shown for Mario or the partner as a target, the Defend take-turn script just started, the end of the Defend state (cancellable: a listener ends the turn itself) |
| `OnBattleMenuBuilt`, `OnBattleMenuSelect`, `OnBattleMenuDrawEntry`, `OnBattleMenuErrorText`, `OnBattleMenuCostStyle`, `OnBattleMenuCreated`, `OnBattleMenuDestroyed` | the battle menu service's own hooks (`BattleMenus.h`); mods use the `Mod_` API instead |
| `OnPerilState`, `OnActorAnim`, `OnPartnerAnim`, `OnPlayerIdleTick`, `OnPlayerIdleAnim`, `OnPlayerSpriteAnim` | presentation: how in danger an actor looks (`PerilState` NONE/DANGER/PERIL, pre-filled from its HP; fired for Mario's danger idles and, for Mario and the partner, the peril icon, which shows the worse of the two), the battle idle anim a part plays for a status key (pre-filled with the idle-table lookup, at every lookup of the NPC idle block and at the end of `get_player_anim_for_status`), the partner's idle anim (`context` WORLD_IDLE, BATTLE_MENU_THINK, BATTLE_MENU_CHOSEN), Mario's field idle (every idle frame with a pointer to the timer, before vanilla's increment, so a listener can reset it; and the anim chosen when the idle starts), and Mario's final field sprite anim; `OnActorStat` `IDLE_PALETTE` is the partner's idle palette (Watt) |
| `OnStatLimits`, `OnMaxStatsRecalculated`, `OnBattleCelebration` | the stat caps as one record (`StatLimits`: level, HP, FP and BP caps, the HP/FP value that can't be raised at a level-up and the level-up clamp; pre-filled with `STAT_LIMITS_VANILLA`, a pure query; `levelCap` also gates `DropStarPoints`), a notification after `enforce_hpfp_limits`, and the victory screen (`phase` AWARD with the star points, clamped to 0-127, JINGLE cancellable, WALK_OFF_BEGIN with Mario's anim, WALK_OFF_STEP every frame with both steps) |
| `OnBgmSong`, `OnSpriteComponentPalette` | the song a BGM player is about to request (after the map variation, before the "already playing" check) and a sprite component's palette (with the component list and index) |
| `OnItemSpawnPick`, `OnItemSpawned` | the item a source is about to spawn (`source` `ItemSpawnSource`: ITEM_BLOCK with the block as `entity`, pre-filled with its item, not cancellable; ENEMY_DROP with the encounter `enemy`, pre-filled `ITEM_NONE` after vanilla's chance roll, cancellable = "a listener picked instead of vanilla's chance and weighted selection", including the drop-table flag; out-of-range picks fall back to the block's item or to no drop), and a notification after that item entity was made (`itemEntityIndex`, -1 if `make_item_entity` refused) |
| `OnPlayerMovementConstraint`, `OnPlayerLandAnim` | field movement limits (`lockWalkZ`: walking doesn't change Z) and the switch-landing anim (cancellable, not fired when Watt is out) |
| `OnStatusBarPanel`, `OnPauseMenu`, `OnBattleStateUpdate` | the panel service's hooks (`Panels.h`); mods use the `Mod_` API instead. `OnPauseMenu` (`PAUSE_MENU_OPEN`/`CLOSE`, with `gPausePanels`) is also a notification for mods that own HUD elements for a pause session |
| `OnPauseBadgeList`, `OnPauseBadgeEquipped`, `OnPauseBadgeTabButtons`, `OnPauseBadgesView`, `OnPauseStatsView` | the Badges tab list about to be built (`OPEN`: before `pause_badges_init` sorts the inventory; `REBUILD`: before each list build; `TAB_SWITCHED`: after the build on a stick tab switch, not on the B-back reload), whether the selected entry is already equipped so A unequips it (pre-filled with the vanilla scan, listener may update its own tables), the buttons that switch All/Active (pre-filled stick up/down), and read-only views of the Badges and Stats tab state, fired once by their vanilla init for replacement draws |
| `OnPauseLabelPos`, `OnPausePartnersOverlay`, `OnPauseMenuDrawElement` | where a pause label is drawn (every `pause_draw_menu_label`), a notification to draw over the Partners tab carousel with the shown partner's ID (before the portrait pane sets its scissor), and single pause elements a listener may hide (cancellable) |
| `OnPopupMenu`, `OnPopupMenuLayout`, `OnPopupMenuDrawEntry`, `OnPopupMenuText`, `OnPopupMenuChoose` | item/partner popup menus, always with the real `gPopupMenu`: `phase` OPENED (end of every `create_*_popup_menu`), LAID_OUT (end of the INIT state, after the popup's windows are set up; a listener may adjust `gWindows`) and CLOSED (`destroy_popup_menu`); the menu's scissor widths, partner level X and arrow X (`PopupMenuLayout`, pre-filled per type, once per content draw); each visible entry before it is drawn; the Sell prompt title and the "already have this partner" text (`PopupMenuText`, the box is still sized from the vanilla text); an enabled entry being chosen (cancellable: the listener sets `gPopupState` itself or opens a popup sub-panel with `Mod_OpenPopupPanel`) |
| `OnWindowStyle`, `OnFileSlotHighlightStyle`, `OnFileMenuModLabel` | the window style service's hook, the highlight body/title styles `filemenu_main_update` gives the selected and copy-to file slots, and the label centred under the file select title (`label` pre-filled empty = no label, `size` bytes including the terminator, which the site enforces; the romhack layer writes `<name> (v<version>)` while a hack is active) |
| `OnScriptResolve` | the script override service's hook (`ScriptOverrides.h`); mods use `Mod_ReplaceScript` instead |
| `OnMessageLoad`, `OnMessageSpeed`, `OnMessageOpen` | the message service's hook; per printer per frame the fast print rate (pre-filled 12, the A-held/quick rate) and `skip` (auto-advance: waiting prompts act as if B were held and printing uses the fast rate with no delay); a printer just acquired for a new message |
| `OnBattlePopupMessage` | the popup service's hook (`index`, the vanilla `switch` key `layout`, `msgID` pre-filled from the vanilla table, `MSG_NONE` out of range; a `layout` outside the vanilla table is ignored; a replacement message of more than two lines gets the two-line box and offset) |
| `OnTitleScreenTimeout` | the title screen timing out (cancellable = stay on the title screen; fires every frame once the timer has run out; `nextState` pre-filled with vanilla's demo/intro choice, only `NEXT_STATE_DEMO`/`INTRO`/`FILE_SELECT` from `game_modes.h` are taken) |
| `OnStarPointDrop`, `OnStarPowerRegen` | battle: the star points an enemy drops and the level compared against `StatLimits.levelCap` (the pending total is clamped to 0-127), and the end-of-turn star power regeneration (cancellable; star power is clamped to 0..max) |
| `OnChangeMapInit`, `OnChangeMapStep` | field: the map change starting and each step (`state` is `enum ChangeMapStates` in `game_modes.h`) |

The engine event `EntityPreDraw` fires in `render_entities` for every entity drawn this frame, before its render callback is bound.

One port flag needs no event: a HUD element with `HUD_ELEMENT_FLAG_FIXED_SIZE` (`0x80000000`) keeps its size through a
`SetSizesFixedScale` tween (no per-frame size step, no reset when the image changes), so a mod that sizes its own
icons sets it after creating them.

Three latent vanilla bugs are fixed alongside these seams, with no effect on the base rom: `DispatchDamageEvent` on a
partner-class actor goes through `dispatch_damage_event_partner` (vanilla only ever targets enemies with it), an
item's damage event is dispatched with `dispatch_event_general` so a player-team target gets the right handler, and
`dispatch_damage_event_partner` aims at part `-1` (the first part) instead of part 0, which doesn't exist on
Lakilester's two-part actor. `SetEnemyHP` clamps a negative value to 0. The partner's Strats menu handles a disabled
entry the way Mario's does (an error state that returns to choosing); vanilla had no case for it and would read
`StratsOptionMenuTypes[-2]`.

### New areas and maps

`gAreas` has room for `AREA_TABLE_CAPACITY` (`0x30`) entries and stays zero-terminated: anything that walks it stops at the first area with `maps == NULL`. Vanilla fills the first 28 slots, the rest is free for romhacks. A hack adds its maps from `Port::Init()` through `port/modding/MapRegistry.h`:

```c
int32_t Mod_AddArea(const char* owner, const char* id, const char* name);                  // "area_xxx", returns its index
MapConfig* Mod_AddMap(const char* owner, int32_t area, const MapConfig* config);           // appends, returns the stored entry
void Mod_RegisterMapResetData(const char* owner, const char* map, void* ptr, size_t size); // restored on every load of <map>
```

- `Mod_AddArea` takes the first free slot, so areas keep the hack's indices only if they're added in the hack's order. Adding an id that already exists returns its index. `id` and `name` are kept as pointers, so they must be string literals or static.
- `Mod_AddMap` moves the area's map list into a fixed array of `MOD_AREA_MAP_CAPACITY` (128) entries the first time, then appends. Vanilla maps keep their index, new maps get the next one, so add them in the hack's order (a placeholder map is added as a stub to keep the following indices). Pointers taken from the area before its first `Mod_AddMap` (including `Mod_FindMapConfig`) are stale afterwards; pointers returned after are stable.
- Area and map indices are saved, and `GotoMap` asserts on unknown maps, so maps that link to each other are added together, before anything that could send the player there.
- Map overlay data is never re-copied in the port, so data a map changes at runtime is registered with `Mod_RegisterMapResetData`: the bytes are copied at registration and written back when that map loads (`OnMapLoad`, before the map's settings and init run).

`UseBuf` tables are read in 4-byte slots by `BufRead`/`FBufRead`/`BufPeek`, which cannot hold a pointer on 64-bit. A table that needs pointers (a Star Rod `ShakeTreeConfig`, for example) is emitted as `Bytecode[]` and registered with `Mod_RegisterWideEvtBuffer(owner, buf, count)`; reads from inside a registered range then step by `sizeof(Bytecode)`. The readers (`evt_buffer_next`/`evt_buffer_at`) live in the service; with nothing registered the check is a single compare.

### Star Rod & DX romhacks

> [!WARNING]
> This section is not complete, and some details might differ based on how the romhack was created: Star Rod vs. DX vs. whatever.

Most Paper Mario romhacks are built with [Star Rod](https://docs.starhaven.dev/papermario-dx/), which relocates almost everything where same-offset ROM diff makes the whole game look rewritten:

- **Overlays** (battle moves, items, partners) are repacked to new ROM offsets, but are often byte-identical.
- **Battle areas** and **map files** are recompressed (Yay0), and often match vanilla once decompressed.
- **Engine tables, heaps and hooks** move into expansion RAM (ROM `0x2800000` -> RAM `0x80400000`).
- **Sprites**: player raster offsets are stored in 16-byte units instead of bytes. Torch extractor has a new property that allows the reads with `raster_offset_scale: 16` on `PM64:SPRITE`. For the player raster load descriptors the sprite loader detects the unit at runtime (`Sprite_GetPlayerRasterOffsetScale`: 16 when the first offset lies before the image data or any offset isn't 16-byte aligned, else 1), and `spr_get_player_raster` multiplies by it.

Compare overlays through their load tables, or by searching the hack ROM for the vanilla bytes, and decompress before comparing. Star Rod's stock engine patches (moved heaps, enlarged tables, EVT/flag/save
hooks, the ×16 raster decode, battle-area compression) need no porting, only the hack's own changes do.
