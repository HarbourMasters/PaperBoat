#!/usr/bin/env python3
"""Emit torch asset YAMLs and a header for PAL's localized UI textures.

Reads the de/, fr/ and es/ prefixed texture entries out of a splat config and
rewrites them as torch YAML. Only entries with an explicit ROM offset are
handled; splat's `auto` offsets chain off compiled section sizes and cannot be
resolved without running splat.

    gen_localized_ui_yaml.py --splat ver/pal/splat.yaml --out-dir assets/yaml/pal \\
                             --header include/assets/ui_pal.h

    gen_localized_ui_yaml.py --splat ver/us/splat.yaml --lang "" \\
                             --verify assets/yaml/us/ui.yml
"""

import argparse
import re
import sys
from pathlib import Path

LANGS = ("de", "fr", "es")

# - [0x133c40, ci4, de/ui/pause/label_items, 48, 16]
RASTER_RE = re.compile(
    r"^\s*-\s*\[\s*(0x[0-9a-fA-F]+)\s*,\s*(\w+)\s*,\s*([\w/.]+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\]", re.M
)
# - [0x133dc0, palette, de/ui/pause/label_items]
PALETTE_RE = re.compile(r"^\s*-\s*\[\s*(0x[0-9a-fA-F]+)\s*,\s*palette\s*,\s*([\w/.]+)\s*\]", re.M)

COLORS = {"ci4": 16, "ci8": 256}


def parse(splat_path, lang):
    """Return [(key, kind, offset, fmt, w, h)] for one language prefix.

    lang="" reads the unprefixed ui/ entries, which is what --verify uses to
    check this against the committed US YAML.
    """
    text = Path(splat_path).read_text(encoding="utf-8")
    prefix = f"{lang}/ui/" if lang else "ui/"

    rasters = {}
    out = []
    for offset, fmt, path, w, h in RASTER_RE.findall(text):
        if not path.startswith(prefix) or fmt not in COLORS:
            continue
        key = path[len(prefix):]
        rasters[path] = fmt
        out.append((key, "raster", int(offset, 16), fmt, int(w), int(h)))

    for offset, path in PALETTE_RE.findall(text):
        if path.startswith(prefix):
            base = path.split(".")[0]
            if base in rasters:
                out.append((path[len(prefix):] + ".pal", "palette", int(offset, 16), rasters[base], 0, 0))

    out.sort(key=lambda e: e[2])
    return out


def symbol(key, lang, kind):
    if kind == "palette":
        key = key[: -len(".pal")]
    stem = ("%s_ui_%s" % (lang, key) if lang else "ui_%s" % key).replace("/", "_").replace(".", "_")
    return stem + ("_pal" if kind == "palette" else "_png")


def render_yaml(entries, lang):
    lines = []
    for key, kind, offset, fmt, w, h in entries:
        lines.append(f"{key}:")
        sym = symbol(key, lang, kind)
        if kind == "raster":
            lines.append(
                f"  {{ type: TEXTURE, format: {fmt.upper()}, offset: 0x{offset:X}, "
                f"width: {w}, height: {h}, symbol: {sym} }}"
            )
        else:
            lines.append(
                f"  {{ type: TEXTURE, format: TLUT, offset: 0x{offset:X}, "
                f"colors: {COLORS[fmt]}, symbol: {sym} }}"
            )
    return "\n".join(lines) + "\n"


def render_header(per_lang):
    lines = ["#pragma once", "", '#include "alignment.h"', ""]
    for lang, entries in per_lang.items():
        for key, kind, _, _, _, _ in entries:
            sym = symbol(key, lang, kind)
            lines.append(f'static const ALIGN_ASSET(2) char {sym}[] = "__OTR__ui_{lang}/{key}";')
        lines.append("")
    return "\n".join(lines)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--splat", required=True)
    ap.add_argument("--out-dir")
    ap.add_argument("--header")
    ap.add_argument("--lang", help="single language prefix; '' for the unprefixed ui/ entries")
    ap.add_argument("--verify", help="compare generated entries against an existing torch YAML")
    args = ap.parse_args()

    if args.verify:
        lang = args.lang if args.lang is not None else ""
        entries = parse(args.splat, lang)
        existing = Path(args.verify).read_text(encoding="utf-8")
        missing, mismatch = [], []
        for key, kind, offset, fmt, w, h in entries:
            want = render_yaml([(key, kind, offset, fmt, w, h)], lang).rstrip("\n")
            if f"\n{key}:\n" not in "\n" + existing:
                missing.append(key)
            elif want not in existing:
                mismatch.append(key)
        print(f"checked {len(entries)} entries: {len(missing)} missing, {len(mismatch)} mismatched")
        for k in (missing + mismatch)[:5]:
            print(f"  {k}")
        return 1 if (missing or mismatch) else 0

    per_lang = {}
    for lang in LANGS:
        entries = parse(args.splat, lang)
        if not entries:
            continue
        per_lang[lang] = entries
        if args.out_dir:
            path = Path(args.out_dir) / f"ui_{lang}.yml"
            path.write_text(render_yaml(entries, lang), encoding="utf-8")
            print(f"wrote {path} ({len(entries)} entries)", file=sys.stderr)

    if args.header and per_lang:
        Path(args.header).write_text(render_header(per_lang), encoding="utf-8")
        print(f"wrote {args.header}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
