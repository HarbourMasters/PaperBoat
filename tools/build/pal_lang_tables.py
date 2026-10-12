"""Generate src/port/language/PalLangTables.inc, the metadata the port needs to
build language packs from a European (PAL) ROM.

The table lists *where* things are (PAL message names with their section/index,
and ROM offsets of the localized images mapped to PaperBoat resource paths). It
contains no game data. Run it once when the layout changes; it needs a
papermario decomp checkout (for the PAL splat files) and a pm64.o2r (to map
image names to resource paths):

    python tools/build/pal_lang_tables.py --decomp ../papermario-reference --archive pm64.o2r
"""

from __future__ import annotations

import argparse
import re
import zipfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
OUTPUT = ROOT / "src/port/language/PalLangTables.inc"

LANGS = ("en", "de", "fr", "es")
NON_EN = ("de", "fr", "es")

# Effect blocks PAL ships once per language. Their textures sit at the same
# relative offsets as PaperBoat's effects/<effect>/tex_<offset> resources.
EFFECT_BLOCKS = {
    "attack_result_text": "effects/effect_gfx_attack_result_text",
    "chapter_change": "effects/effect_gfx_chapter_change",
}

TEX_BYTES = {
    "ci4": lambda w, h: w * h // 2,
    "ia4": lambda w, h: w * h // 2,
    "i4": lambda w, h: w * h // 2,
    "ia8": lambda w, h: w * h,
    "i8": lambda w, h: w * h,
    "rgba16": lambda w, h: w * h * 2,
}


def load_toc(path: Path) -> list[tuple[str, int, int]]:
    text = path.read_text(encoding="utf-8")
    return [
        (name, int(section, 16), int(index, 16))
        for section, index, name in re.findall(r"\[0x([0-9A-Fa-f]+), 0x([0-9A-Fa-f]+), ([A-Za-z_0-9]+)", text)
    ]


def scan_splat(splat: Path) -> dict[str, list[tuple[str, str, int, int]]]:
    """lang -> [(kind, name, rom offset, size)] for localized images with explicit offsets."""
    result: dict[str, list] = {lang: [] for lang in NON_EN}
    in_auto, offset = False, 0
    pattern = re.compile(
        r"\[(auto|0x[\da-fA-F]+),\s*(ci4|palette|ia8|ia4|i4|i8|rgba16),\s*([\w./]+)(?:,\s*(\d+),\s*(\d+))?\]"
    )
    last_start, segment = 0, None
    for line in splat.read_text(encoding="utf-8").splitlines():
        sm = re.search(r"start:\s*(0x[\da-fA-F]+)", line)
        if sm:
            last_start = int(sm.group(1), 16)
        nm = re.search(r"name:\s*([a-z_]+)_([a-z]{2})\s*$", line)
        if nm:
            segment = (EFFECT_BLOCKS[nm.group(1)], nm.group(2), last_start) if (
                nm.group(1) in EFFECT_BLOCKS and nm.group(2) in NON_EN) else None
        elif re.search(r"^\s*-?\s*name:", line):
            segment = None
        m = pattern.search(line)
        if segment and m:
            address, kind, name, w, h = m.groups()
            if address != "auto" and name.startswith(segment[1] + "/") and kind != "palette":
                rel = int(address, 16) - segment[2]
                result[segment[1]].append(("@", f"{segment[0]}|{rel:X}", int(address, 16), TEX_BYTES[kind](int(w), int(h))))
            continue
        if "start: 0x8DA40" in line:
            in_auto, offset = True, 0x8DA40
        if in_auto and "[0x9B5A0]" in line:
            if offset != 0x9B5A0:
                raise SystemExit(f"PAL UI offsets drifted: {offset:#x}")
            in_auto = False
        if not m:
            continue
        address, kind, name, w, h = m.groups()
        if address == "auto" and not in_auto:
            continue
        if address != "auto":
            offset = int(address, 16)
        size = 0x20 if kind == "palette" else TEX_BYTES[kind](int(w), int(h))
        lang = name[:2]
        if lang in NON_EN and name[2:].startswith("/ui/"):
            result[lang].append(("ui", name[3:] + (".pal" if kind == "palette" else ""), offset, size))
        elif lang in NON_EN and name[2:3] == "/" and "D_PAL" not in name and address != "auto":
            result[lang].append(("?", name[3:] + (".pal" if kind == "palette" else ""), offset, size))
        if in_auto:
            offset += size
    return result


def resolve(entries, archive: zipfile.ZipFile):
    """Turn scan results into [(resource path, rom offset, size)], checking sizes."""
    names = set(archive.namelist())
    by_leaf: dict[str, list[str]] = {}
    for n in names:
        by_leaf.setdefault(n.rsplit("/", 1)[-1], []).append(n)
    out, skipped = [], []

    def raster(path: str) -> int | None:
        if path not in names:
            return None
        data = archive.read(path)
        return len(data) - 80 if data[4:8] == b"XETO" else None

    for kind, name, rom, size in entries:
        if kind == "ui":
            if raster(name) != size:
                raise SystemExit(f"UI asset {name}: size mismatch")
            out.append((name, rom, size))
        elif kind == "?":
            match = by_leaf.get(name.rsplit("/", 1)[-1], [])
            if len(match) == 1 and raster(match[0]) == size:
                out.append((match[0], rom, size))
            else:
                skipped.append(name)
        else:  # "@" effect texture, possibly spanning several PaperBoat textures
            effect, rel_hex = name.split("|")
            cursor, done, pieces = int(rel_hex, 16), 0, []
            while done < size:
                path = f"{effect}/tex_{cursor:X}"
                r = raster(path)
                if r is None or r <= 0 or done + r > size:
                    pieces = None
                    break
                pieces.append((path, rom + done, r))
                cursor, done = cursor + r, done + r
            if pieces:
                out.extend(pieces)
            else:
                skipped.append(name)
    return out, skipped


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--decomp", type=Path, required=True, help="papermario decomp checkout (PAL splat files)")
    ap.add_argument("--archive", type=Path, required=True, help="pm64.o2r extracted from the US ROM")
    args = ap.parse_args()

    toc = load_toc(args.decomp / "tools/splat_ext/msg_pal.yaml")
    scanned = scan_splat(args.decomp / "ver/pal/splat.yaml")
    with zipfile.ZipFile(args.archive) as archive:
        resolved = {lang: resolve(scanned[lang], archive) for lang in NON_EN}

    lines = [
        "// Generated by tools/build/pal_lang_tables.py. Do not edit.",
        "// Locations only (message names, ROM offsets, resource paths); no game data.",
        "",
        "static const PalMessage kPalMessages[] = {",
    ]
    lines += [f'    {{ "{n}", {s}, {i} }},' for n, s, i in toc]
    lines += ["};", "", "static const PalImage kPalImages[] = {"]
    for lang in NON_EN:
        for path, rom, size in resolved[lang][0]:
            lines.append(f'    {{ {LANGS.index(lang)}, "{path}", 0x{rom:X}, {size} }},')
    lines += ["};", ""]
    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    OUTPUT.write_text("\n".join(lines), encoding="utf-8")
    for lang in NON_EN:
        print(f"{lang}: {len(resolved[lang][0])} images ({len(resolved[lang][1])} not matched)")
    print(f"{len(toc)} messages -> {OUTPUT.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
