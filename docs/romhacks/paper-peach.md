# Paper Peach

[Paper Peach](https://gamebanana.com/mods/576687) by AgateTrevalyn swaps Mario for Peach. It was
built with Star Rod and targets the US ROM.

- Patch: `Paper Peach Patch.bps` (from `paper_peach_patch_6b1b2.zip`, the "Sprite Fix" release)
- Patched ROM SHA1: `c02972e81d5f05da7ed0e7b4f0efc30f05a01b18`
- Stem / id: `paper_peach` / `PaperPeach`
- The "OG values" variant (`paper_peach_patch_og_values_a30a4.zip`) produces a different SHA1. It
  needs its own `config.yml` entry, which can reuse this YAML set minus the `move_table` blob.

**Status: fully ported.** Paper Peach is a content mod. Apart from Star Rod's own engine patches
(see below), it carries no custom code.

## What the hack changes, and where the port gets it

| Area | Change | Ported via |
|---|---|---|
| Player sprites | All 13 rebuilt as Peach, with 32 extra rasters (descriptors 718 → 750). The "custom battle animations" live here, not in code | asset delta. Star Rod packs raster offsets in 16-byte units, handled by `raster_offset_scale: 16` on `PM64:SPRITE` (a local Torch patch that still needs upstreaming) and detected again in `spr_get_player_raster`. `PlayerRasterLoadDesc` was grown to 0x400 |
| Player sprite sets | Max raster size raised from 0x700/0x900 to 0x2000 | `romhack/player_sprite_sets` → `PaperPeachPort::ApplyDataTables` |
| NPC sprites | Goombario, Parakarry and Lakilester (world + battle); Twink, Lakilulu, Parade Peach (→ Daisy), parade partner | asset delta |
| Messages | 2084 of 8009 rewritten, with section and message counts unchanged | asset delta |
| Items | Hammer, Super Hammer and Ultra Hammer gain descriptions (`0x2300A3`–`A5`) | `romhack/item_table` (message fields only) |
| Moves | FP/BP costs lowered on 53 of 185 moves | `romhack/move_table` |
| Pause menu | Boots → Heels, Hammer → Parasol (each with its Super and Ultra tiers), Mario → Peach | `PaperPeachPort::Init` overrides `gPauseMessages` with the hack's strings |
| Icons / UI | Gear (heels and parasol), badges, the Mario head, the swapped partner icons, the pause and file menus, battle menu icons | asset delta |
| Map files | `hos_tex` (`hos_ochi_mariotif` is now 64×44) and `trd_03_hit` collision | asset delta + `Mod_OverrideMapTextureSize` |
| Effects / shading | Ending decals, Peach star beam texture, 18 sprite shading profiles | asset delta |

## Star Rod engine changes (nothing to port)

A raw ROM diff makes the hack look as if it rewrote most of the game. Nearly all of that is Star Rod
relocating things.

- **Overlays are repacked, not changed.** Every battle-move, item and partner overlay is
  byte-identical to vanilla at a new ROM offset. Compare them through their load tables, never at
  the same offset:
  - `gMoveScriptTable` 0x1C2760
  - `gBattleItemTable` 0x1C24E4
  - `bPartnerDmaTable` 0x1B27F0
  - `wPartners` 0x914EC
- **Battle areas are Yay0-compressed.** They are loaded through a `load_battle_section` hook, and
  all 46 match vanilla after decompression, apart from repointed tables and stripped JP debug names.
- **The ROM grows by 0x2800000 bytes, loaded into RAM at 0x80400000.** This is Star Rod's stock
  engine expansion:
  - the general, sprite and collision heaps and a framebuffer move into expansion RAM;
  - `gAreas`, the item, HUD and icon tables, the NPC sprite tables, `gMessageMsgVars` and the
    entity collider tables are rebuilt there;
  - save, global-flag and EVT-interpreter hooks extend its scripting;
  - `is_ability_active` is rewritten with the vanilla ability → badge mapping;
  - player rasters are decoded with ×16 offsets;
  - the button font is re-strided to 0x50 bytes per glyph, with identical glyphs.

  The port has none of the N64 memory limits these work around. Its sprite heap, for example, is
  already 1MB.
- **Small map edits** (`mac_01`, `kmr_06`, `hos_06`, `kkj_17`, `end_00`/`end_01`) only repoint
  the tables above.

Known issues inherited from the mod: Peach looks squashed in pipes and beds, and some animations
reuse unrelated frames.

The full generator output is in [paper-peach-assets.md](paper-peach-assets.md).
