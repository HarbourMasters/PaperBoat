"""Generate the DE/FR/ES file-menu text tables used by the US-based port.

The PAL file-menu strings are compiled arrays in src/filemenu/filemenu_msg.c
(under VERSION_PAL) indexed with PAL's FileMenuMessages enum, which differs from
the US enum. This maps each US index to the matching PAL entry for every
language and writes src/filemenu/filemenu_intl.inc.c. English keeps the US text.
"""

from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "src/filemenu/filemenu_msg.c"
OUTPUT = ROOT / "src/filemenu/filemenu_intl.inc.c"

LANGS = {  # language -> PAL table symbol
    "de": "D_filemenu_80251018",
    "fr": "D_filemenu_802510B8",
    "es": "D_filemenu_80251158",
}
US_COUNT = 35  # FILE_MESSAGE_NONE .. FILE_MESSAGE_PERIOD_34

# US-only messages (the PC save flow) that PAL never had. US index -> text.
US_ONLY = {
    3: {"de": "Datei speichern:", "fr": "Sauvegarder:", "es": "Guardar fichero:"},
    17: {"de": "Daten ersetzen?", "fr": "Remplacer les donnees?", "es": "Sobrescribir datos?"},
    18: {"de": "Speichern?", "fr": "Sauvegarder?", "es": "Guardar?"},
}




# FileMenuMessages order in the US build (include/enums.h, !VERSION_PAL)...
US_NAMES = [
    "NONE", "SELECT_FILE_TO_START", "SELECT_FILE_TO_DELETE", "SELECT_FILE_TO_SAVE", "COPY_WHICH_FILE",
    "COPY_TO_WHICH_FILE", "NEW", "LEVEL", "PLAY_TIME", "DELETE_FILE", "CANCEL", "COPY_FILE", "FIRST_PLAY",
    "PERIOD_13", "YES", "NO", "DELETE", "OVERRIDE_TO_NEW_DATA", "SAVE_OK", "FILE_NAME_IS", "PERIOD_20", "OK",
    "FILE_22", "WILL_BE_DELETED", "OK_TO_COPY_TO_THIS_FILE", "START_GAME_WITH", "FILE_26", "HAS_BEEN_DELETED",
    "28", "COPY_FROM", "TO", "HAS_BEEN_CREATED", "ENTER_A_FILE_NAME", "QUESTION", "PERIOD_34",
]
assert len(US_NAMES) == US_COUNT

# ...and in the PAL build (papermario decomp), which drops three US-only entries
# and inserts four language-dependent ones.
PAL_NAMES = [
    "NONE", "SELECT_FILE_TO_START", "SELECT_FILE_TO_DELETE", "COPY_WHICH_FILE", "COPY_TO_WHICH_FILE", "NEW",
    "LEVEL", "PLAY_TIME", "DELETE_FILE", "CANCEL", "COPY_FILE", "FIRST_PLAY", "PERIOD_13", "YES", "NO", "DELETE",
    "FILE_NAME_IS", "PERIOD_20", "OK", "FILE_22", "PAL_FILE_20", "WILL_BE_DELETED", "OK_TO_COPY_TO_THIS_FILE",
    "START_GAME_WITH", "PAL_QUESTION_24", "FILE_26", "HAS_BEEN_DELETED", "28", "COPY_FROM", "TO", "PAL_PERIOD_30",
    "HAS_BEEN_CREATED", "PAL_ARTICLE", "ENTER_A_FILE_NAME", "QUESTION", "PERIOD_34",
]

# Entries only PAL has. They get indices after the US ones (FILE_MESSAGE_INTL_* in enums.h).
PAL_EXTRAS = ["PAL_FILE_20", "PAL_QUESTION_24", "PAL_PERIOD_30", "PAL_ARTICLE"]


def encode(text: str) -> bytes:
    out = bytearray()
    for n, ch in enumerate(text):
        if ch == " ":
            out.append(0xF7)
        elif ch.isalpha() and ch.isascii():
            base = 0x21 if n == 0 else 0x41
            out.append(ord(ch.upper()) - ord("A") + base)
        elif ch in ".?:!":
            out.append({".": 0x0E, "?": 0x1F, ":": 0x1A, "!": 0x01}[ch])
        else:
            raise ValueError(f"Unsupported character {ch!r}")
    return bytes(out) + b"\xFD"


def pal_branch(source: str) -> str:
    """Keep only the lines active when VERSION_PAL is 1 and every other VERSION_* is 0."""
    def cond(expr: str) -> bool:
        expr = expr.strip()
        neg = expr.startswith("!")
        name = expr.lstrip("!").strip()
        if not name.startswith("VERSION_"):
            raise ValueError(f"Unsupported #if expression: {expr}")
        return (name == "VERSION_PAL") != neg

    kept, stack = [], []  # stack of [parent_active, taken, active]
    for line in source.splitlines():
        m = re.match(r"\s*#\s*(ifdef|ifndef|if|elif|else|endif)\s*(.*)", line)
        if m:
            kind, rest = m.groups()
            parent = all(f[2] for f in stack)
            if kind in ("ifdef", "ifndef"):
                stack.append([parent, True, True])  # not a version switch: keep the code
            elif kind == "if":
                value = cond(rest)
                stack.append([parent, value, value])
            elif kind == "elif":
                f = stack[-1]
                value = (not f[1]) and cond(rest)
                f[1] |= value
                f[2] = value
            elif kind == "else":
                f = stack[-1]
                f[2] = not f[1]
                f[1] = True
            else:
                stack.pop()
            continue
        if re.match(r"\s*#\s*(include|define|undef|pragma)", line):
            continue
        if all(f[2] for f in stack):
            kept.append(line)
    return "\n".join(kept)


def parse(source: str):
    source = pal_branch(source)
    arrays: dict[str, set[bytes]] = {}
    for name, body in re.findall(r"u8\s+([A-Za-z0-9_]+)\[\]\s*=\s*\{([^}]*)\};", source):
        data = bytes(int(b, 16) for b in re.findall(r"0x([0-9A-Fa-f]{2})", body))
        arrays.setdefault(name, set()).add(data)
    tables = {}
    for name, body in re.findall(r"u8\s*\*\s*([A-Za-z0-9_]+)\[\]\s*=\s*\{([^}]*)\};", source):
        tables[name] = [t.strip() for t in body.split(",") if t.strip()]
    return arrays, tables


def main() -> None:
    arrays, tables = parse(SOURCE.read_text(encoding="utf-8"))

    def resolve(sym: str, context: str) -> bytes:
        variants = arrays.get(sym)
        if not variants:
            raise ValueError(f"{context}: no array {sym}")
        if len(variants) > 1:
            raise ValueError(f"{context}: ambiguous definitions of {sym}")
        return next(iter(variants))

    out = ["/* Generated by tools/build/intl_filemenu.py from the PAL file-menu arrays. */",
           "#if !VERSION_PAL"]
    refs: dict[str, list[str]] = {}
    for lang, table_sym in LANGS.items():
        entries = tables[table_sym]
        assert len(entries) >= len(PAL_NAMES), (lang, len(entries))
        names = []
        for i, name in enumerate(US_NAMES + PAL_EXTRAS):
            if i == 0:
                names.append("NULL")
                continue
            if i in US_ONLY:
                data = encode(US_ONLY[i][lang])
            else:
                data = resolve(entries[PAL_NAMES.index(name)], f"{lang}.{name}")
            sym = f"sFileMenu_{lang}_{i:02d}"
            out.append(f"static u8 {sym}[] = {{ " + ", ".join(f"0x{b:02X}" for b in data) + " };")
            names.append(sym)
        refs[lang] = names

    count = len(US_NAMES) + len(PAL_EXTRAS)
    out.append("// Index 0 = German, 1 = French, 2 = Spanish (language id - 1).")
    out.append(f"static u8* sFileMenuIntl[3][{count}] = {{")
    for lang in LANGS:
        out.append("    { " + ", ".join(refs[lang]) + " },")
    out.append("};")
    out.append("#endif")
    OUTPUT.write_text("\n".join(out) + "\n", encoding="utf-8")
    print(f"Generated {OUTPUT.name}: {len(LANGS)} languages x {count - 1} messages")


if __name__ == "__main__":
    main()
