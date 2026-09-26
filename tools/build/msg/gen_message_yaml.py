#!/usr/bin/env python3
"""Generate a torch asset YAML for a ROM's message block.

Messages are stored in the ROM as a self-describing two-level offset table:

    +0x00            u32 section_offsets[]   terminated by 0
    section_offsets[i]
                     u32 msg_offsets[]       terminated by a value == section_offsets[i]

Message data for section i lives *before* that section's offset table, so the
last message in a section ends exactly where the table begins. Every offset is
relative to the start of the block.

Walking that structure gives offset and size for every message without any
hardcoded addresses, which is what makes this reusable across regions. Names
come from the splat tables in tools/splat_ext/ (msg.yaml, msg_pal_en.yaml, ...);
slots with no entry there get a positional fallback name.

Usage:
    gen_message_yaml.py --rom ROM --base 0x1B83000 --names tools/splat_ext/msg.yaml \\
                        --out assets/yaml/us/messages.yml

    gen_message_yaml.py ... --verify assets/yaml/us/messages.yml   # compare, don't write
"""

import argparse
import re
import struct
import sys
from pathlib import Path

NAME_RE = re.compile(r"^- \[\s*(0x[0-9A-Fa-f]+)\s*,\s*(0x[0-9A-Fa-f]+)\s*,\s*(\S+?)\s*\]", re.M)


def load_names(path):
    """Parse a splat msg name table into {(section, index): name}.

    Hand-parsed rather than via pyyaml: the tables are uniform three-field
    rows, and avoiding the dependency keeps this runnable from a bare python.
    """
    text = Path(path).read_text(encoding="utf-8")
    names = {}
    for section, index, name in NAME_RE.findall(text):
        names[(int(section, 16), int(index, 16))] = name
    if not names:
        sys.exit(f"error: no names parsed from {path}")
    return names


def walk(rom, base):
    """Return [[(offset, size), ...], ...] indexed by section.

    Offsets are relative to base, matching what torch expects for a segmented
    asset YAML.
    """

    def u32(pos):
        return struct.unpack_from(">I", rom, base + pos)[0]

    section_offsets = []
    pos = 0
    while True:
        offset = u32(pos)
        if offset == 0:
            break
        section_offsets.append(offset)
        pos += 4

    sections = []
    for section_offset in section_offsets:
        msg_offsets = []
        pos = section_offset
        while True:
            offset = u32(pos)
            if offset == section_offset:
                break
            msg_offsets.append(offset)
            pos += 4

        # A message runs to the next one; the last runs to this section's
        # own offset table, which sits immediately after the message data.
        ends = msg_offsets[1:] + [section_offset]
        sections.append(list(zip(msg_offsets, [e - o for o, e in zip(msg_offsets, ends)])))

    return sections


def render(sections, names, segment, base, prefix):
    out = [":config:", "  segments:", f"    - [{segment}, 0x{base:X}]", "  no_compression: true", ""]
    for section_index, messages in enumerate(sections):
        for index, (offset, size) in enumerate(messages):
            name = names.get((section_index, index))
            if name is None:
                # Unnamed slots exist in PAL (5 of them, appended past what the
                # splat table covers). Positional names keep them addressable.
                name = f"sec{section_index:02X}_{index:04X}"
            out.append(f"{prefix}MSG_{name}:")
            out.append(f"  {{ type: BLOB, offset: 0x{offset:X}, size: 0x{size:X} }}")
    return "\n".join(out) + "\n"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--rom", required=True, help="path to the ROM to read")
    ap.add_argument("--base", required=True, help="ROM offset of the message block, e.g. 0x1B83000")
    ap.add_argument("--names", required=True, help="splat name table, e.g. tools/splat_ext/msg.yaml")
    ap.add_argument("--out", help="YAML to write (omit with --verify)")
    ap.add_argument("--verify", help="compare against an existing YAML instead of writing")
    ap.add_argument("--segment", type=int, default=1, help="segment number for the :config: block (default 1)")
    ap.add_argument("--prefix", default="", help="prepended to every key, e.g. 'de/' for messages/de/MSG_*")
    args = ap.parse_args()

    base = int(args.base, 0)
    rom = Path(args.rom).read_bytes()
    sections = walk(rom, base)
    total = sum(len(s) for s in sections)
    print(f"walked 0x{base:X}: {len(sections)} sections, {total} messages", file=sys.stderr)

    text = render(sections, load_names(args.names), args.segment, base, args.prefix)

    if args.verify:
        expected = Path(args.verify).read_text(encoding="utf-8")
        if text == expected:
            print(f"OK: byte-for-byte match against {args.verify}", file=sys.stderr)
            return 0
        print(f"MISMATCH against {args.verify}", file=sys.stderr)
        got, want = text.splitlines(), expected.splitlines()
        print(f"  generated {len(got)} lines, expected {len(want)}", file=sys.stderr)
        for i, (g, w) in enumerate(zip(got, want)):
            if g != w:
                print(f"  first diff at line {i + 1}:\n    got:      {g}\n    expected: {w}", file=sys.stderr)
                break
        return 1

    if not args.out:
        sys.exit("error: --out or --verify is required")
    Path(args.out).write_text(text, encoding="utf-8")
    print(f"wrote {args.out}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
