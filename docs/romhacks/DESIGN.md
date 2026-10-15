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
   │                     │        │  - romhack/info marker       │
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

3. **Detecting the romhack**: during extraction, Torch writes a `romhack/info` marker (id, name, version, ROM SHA1) into the romhack o2r in place of the base game's `portVersion`. At boot, the marker tells the port which romhack is loaded, and which code port to run.

4. **Loading order**: the base game loads first, then the selected romhack, then mods. Resources are looked up by path, so the romhack shadows the base game, and the HD pack and mods shadow both. Only one romhack is active at a time; it's stored in `gSettings.Romhack.Selected`, and the `-hack <stem>` launch argument overrides it for a single launch.

5. **Data tables**: tables compiled into the game code can't be swapped by an asset. Their hack values ship as `romhack/<table>` blobs in the romhack o2r, and the hack's code port copies the fields it trusts over   the compiled table at boot. This step runs before `ShipInit`, so enhancements that snapshot those tables (e.g. *Free QoL Badges* saves the BP costs) see the hack's values.

6. **Custom code**: each hack with code has a `Romhack::Port` subclass in `src/port/romhack/specific/<Id>.cpp`, listed in the X-macro `ROMHACK_PORT_LIST`. Only the active hack's port is created. All custom logic goes through **game hooks** (`REGISTER_LISTENER`). If no event fires where a hack changes the logic, a new generic event is added to the hooks list instead of editing decomp code for one hack.

7. **Identity and saves**: each romhack has its own saves folder, `saves/~romhacks/<stem>/`. Saves are stamped with the romhack's name instead of the dx mod name or `PaperBoat`, so a save from one romhack is shown as incompatible in another. A version bump keeps the same name, so saves stay loadable across versions. The dx `majorVersion`/`minorVersion`/`patchVersion` fields keep describing the save format for PaperBoat as a whole while the romhack's own version is written as a separate `romhackVersion` string in the JSON file.

8. **Romhack Menu**: romhacks are managed in **Settings → Romhack Menu**, separate from the Mod Menu. It holds the *Generate Romhack from ROM* button, the *Installed Romhacks* list (one enabled at a time) and the *Supported Romhacks* list with download links, read from `config.yml`.

> [!NOTE]
> starting a folder name with `~` means it's a reserved folder name and it's managed by the port.

### Layers

A romhack is split into three layers, each with its own path into the port:

| Layer | Where it comes from | Example |
|---|---|---|
| **Assets**: sprites, messages, icons, map textures, collision | delta YAML -> romhack o2r | a hack's sprites, dialog msgs...etc |
| **Data tables** compiled into the port | `romhack/<table>` blobs -> the hack's `Port::ApplyDataTables()` | move FP/BP costs, item descriptions, player sprite raster sizes, ...etc |
| **Custom code**: overlays, scripts, injected code, strings kept in the original romhack code | `Port::Init()` in `src/port/romhack/specific/<Id>.cpp`, through game hooks | pause menu labels, resized map texture sizes, new behaviour |

### The romhack specifics interface

```cpp
namespace Romhack {
class Port {
  public:
    // End of FinishInit, before ShipInit.
    virtual void ApplyDataTables() {}

    // ShipInit. Register game hooks here.
    virtual void Init() {}

  protected:
    static std::shared_ptr<Ship::Blob> LoadTable(const char* name);  // romhack/<name>
    static int32_t ReadBE32(const uint8_t* p);
};
}
```

A hack's file subclasses `Port` and exposes `Create<Id>Port()`, and `<Id>` is added to `ROMHACK_PORT_LIST` in `src/port/romhack/RomhackRegistration.cpp`. `Init()` runs once per launch, and since switching romhacks needs a restart, listeners never need unregistering.

### Star Rod & DX romhacks

> [!WARNING]
> This section is not complete, and some details might differ based on how the romhack was created: Star Rod vs. DX vs. whatever.

Most Paper Mario romhacks are built with [Star Rod](https://docs.starhaven.dev/papermario-dx/), which relocates almost everything where same-offset ROM diff makes the whole game look rewritten:

- **Overlays** (battle moves, items, partners) are repacked to new ROM offsets, but are often byte-identical.
- **Battle areas** and **map files** are recompressed (Yay0), and often match vanilla once decompressed.
- **Engine tables, heaps and hooks** move into expansion RAM (ROM `0x2800000` -> RAM `0x80400000`).
- **Sprites**: player raster offsets are stored in 16-byte units instead of bytes. Torch extractor has a new property that allows the reads with `raster_offset_scale: 16` on `PM64:SPRITE`.

Compare overlays through their load tables, or by searching the hack ROM for the vanilla bytes, and decompress before comparing. Star Rod's stock engine patches (moved heaps, enlarged tables, EVT/flag/save
hooks, the ×16 raster decode, battle-area compression) need no porting, only the hack's own changes do.
