# Builds the modding wiki from the mod API headers and src/port/hooks/EVENTS.md.
#   python3 tools/wiki/build_wiki.py <paperboat checkout> <output.html>

import json
import os
import re
import sys

HEADERS = ["api", "item", "message", "script", "world", "savedata", "cvar", "ui", "texture", "sound", "puppet",
           "permissions", "online", "relay", "room", "player_store", "channel_store"]


def join_comment(lines):
    text = " ".join(l.strip()[2:].strip() for l in lines)
    return re.sub(r"\s+", " ", text).strip()


def parse_header(path):
    src = open(path).read().splitlines()
    items = []
    intro = []
    comment = []
    i = 0
    seen_decl = False
    while i < len(src):
        line = src[i]
        s = line.strip()
        if s.startswith("//"):
            comment.append(line)
            i += 1
            continue
        if s == "":
            if comment and not seen_decl and not intro:
                intro = comment
            elif comment and not seen_decl:
                intro += comment
            comment = []
            i += 1
            continue
        if s.startswith("#pragma") or s.startswith("#include"):
            i += 1
            continue
        doc = join_comment(comment)
        comment = []
        if s.startswith("typedef struct") or (s.startswith("typedef enum") and "{" in s and "}" not in s):
            kind = "enum" if "enum" in s else "struct"
            body = []
            name = None
            i += 1
            depth = 1
            while i < len(src):
                l = src[i]
                if l.strip().startswith("}") and depth == 1:
                    name = re.search(r"}\s*(\w+)\s*;", l.strip())
                    break
                depth += l.count("{") - l.count("}")
                body.append(l)
                i += 1
            name = name.group(1) if name else "?"
            if kind == "enum" and "{" in s and "}" in s:
                pass
            items.append({"kind": kind, "name": name, "doc": doc, "fields": parse_fields(body, kind)})
            seen_decl = True
            i += 1
            continue
        if s.startswith("typedef enum") and "}" in s:
            m = re.match(r"typedef enum\s*{(.*)}\s*(\w+);", s)
            items.append({"kind": "enum", "name": m.group(2), "doc": doc,
                          "fields": [{"decl": v.strip(), "doc": ""} for v in m.group(1).split(",") if v.strip()]})
            seen_decl = True
            i += 1
            continue
        if s.startswith("typedef"):
            items.append({"kind": "typedef", "name": re.findall(r"\w+", s)[-1], "decl": s, "doc": doc})
            seen_decl = True
            i += 1
            continue
        if s.startswith("#define"):
            decl = s
            while decl.endswith("\\"):
                i += 1
                decl = decl[:-1].rstrip() + " " + src[i].strip()
            m = re.match(r"#define\s+(\w+)(\([^)]*\))?\s*(.*)", decl)
            name, args, value = m.group(1), m.group(2), m.group(3)
            items.append({"kind": "macro" if args else "const", "name": name, "args": args or "", "value": value,
                          "doc": doc})
            seen_decl = True
            i += 1
            continue
        if s.startswith("PB_API"):
            decl = s
            while not decl.endswith(";"):
                i += 1
                decl += " " + src[i].strip()
            decl = re.sub(r"\s+", " ", decl[len("PB_API"):].strip().rstrip(";"))
            m = re.match(r"(.*?)\b(\w+)\s*\((.*)\)$", decl)
            items.append({"kind": "func", "name": m.group(2), "ret": m.group(1).strip(), "args": m.group(3),
                          "doc": doc})
            seen_decl = True
            i += 1
            continue
        if s.startswith("static inline"):
            decl = s
            m = re.match(r"static inline (.*?)\b(\w+)\s*\((.*)\)\s*{", decl)
            depth = decl.count("{") - decl.count("}")
            i += 1
            while i < len(src) and depth > 0:
                depth += src[i].count("{") - src[i].count("}")
                i += 1
            if m:
                items.append({"kind": "helper", "name": m.group(2), "ret": m.group(1).strip(), "args": m.group(3),
                              "doc": doc})
            seen_decl = True
            continue
        i += 1
    return {"intro": join_comment(intro), "items": items}


def parse_fields(body, kind):
    fields = []
    pending = ""
    for l in body:
        s = l.strip()
        if s.startswith("//"):
            if fields:
                fields[-1]["doc"] = (fields[-1]["doc"] + " " + s[2:].strip()).strip()
            continue
        if not s:
            continue
        code, _, doc = s.partition("//")
        code = code.strip()
        if pending:
            code = pending + " " + code
            pending = ""
        if kind == "struct" and code and not code.endswith(";") and not code.endswith("{") and code != "}":
            pending = code
            continue
        if code.startswith("union") or code.startswith("} opts"):
            if code.startswith("} opts"):
                fields.append({"decl": "union { ... } opts;", "doc": "Options for the widget type, see below."})
            continue
        if kind == "enum":
            code = code.rstrip(",")
        if code:
            fields.append({"decl": code, "doc": doc.strip()})
    return fields


def parse_events(path):
    text = open(path).read()
    intro, _, rest = text.partition("\n---\n")
    groups = []
    for block in re.split(r"\n## ", rest)[1:]:
        title, _, body = block.partition("\n")
        events = []
        for entry in re.split(r"\n### ", "\n" + body)[1:]:
            head, _, content = entry.partition("\n")
            m = re.match(r"`(\w+)`\s*(?:_\((\w+)\)_)?", head)
            # PaperBoat marks events in their text: _(cancellable)_, _(cancellable, replaces)_, _(polled)_.
            marks = re.findall(r"_\(([^)]*)\)_", content)
            flag = m.group(2) or next((k.split(",")[0].strip() for k in marks), "")
            content = re.sub(r"_\(([^)]*)\)_", r"(\1)", content)
            fields = ""
            code = re.search(r"```c\n(.*?)```", content, re.S)
            if code:
                fields = code.group(1).rstrip()
                content = content.replace(code.group(0), "")
            content = content.replace("\n---", "").strip()
            cancel = ""
            prose = []
            for para in [p.strip() for p in content.split("\n") if p.strip()]:
                if para.startswith("**Cancel**"):
                    cancel = para[len("**Cancel**:"):].strip()
                else:
                    prose.append(para)
            events.append({"name": m.group(1), "flag": flag, "fields": fields, "doc": " ".join(prose),
                           "cancel": cancel})
        if events:
            groups.append({"title": title.strip(), "events": events})
    return groups


def widget_options(data):
    opts = {"combo", "slider_int", "slider_float", "checkbox", "text", "color_picker", "generic"}
    for it in data["headers"]["ui"]["items"]:
        if it["name"] != "C_WidgetConfig":
            continue
        fields = []
        for f in it["fields"]:
            name = f["decl"].rstrip(";").split()[-1]
            if f["decl"].startswith("union"):
                continue
            if name in opts:
                doc = "Tooltip for buttons and other widgets." if name == "generic" else \
                    "Options when type is a " + name.replace("_", " ") + " widget."
                f = {"decl": f["decl"].replace(name, "opts." + name), "doc": doc}
            fields.append(f)
        it["fields"] = fields


def main():
    root, out = sys.argv[1], sys.argv[2]
    data = {"headers": {h: parse_header(f"{root}/src/port/api/{h}.h") for h in HEADERS},
            "events": parse_events(f"{root}/src/port/hooks/EVENTS.md")}
    widget_options(data)

    template = open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "template.html")).read()
    page = template.replace("/*DATA*/", json.dumps(data, separators=(",", ":")).replace("</", "<\\/"))
    head, sep, body = page.partition("</style>")
    html = ("<!doctype html>\n<html lang=\"en\">\n<head>\n<meta charset=\"utf-8\">\n"
            "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, viewport-fit=cover\">\n"
            "<style>body{margin:0}img{max-width:100%}[hidden]{display:none!important}</style>\n"
            + head + sep + "\n</head>\n<body>\n" + body + "\n</body>\n</html>\n")
    os.makedirs(os.path.dirname(os.path.abspath(out)), exist_ok=True)
    open(out, "w").write(html)
    events = sum(len(g["events"]) for g in data["events"])
    print(f"build_wiki: wrote {out} ({len(data['headers'])} headers, {events} events)")


if __name__ == "__main__":
    main()
