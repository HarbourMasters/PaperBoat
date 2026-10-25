#include "ModManifest.h"

#include <algorithm>
#include <cctype>
#include <map>

#include <ship/resource/File.h>
#include <ship/resource/archive/Archive.h>
#include <ship/resource/archive/FolderArchive.h>
#include <ship/resource/archive/O2rArchive.h>
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>

#include "port/romhack/Romhack.h"

namespace fs = std::filesystem;

namespace Mod {

static std::vector<std::string> StringList(const nlohmann::json& node) {
    std::vector<std::string> out;
    if (node.is_string()) {
        out.push_back(node.get<std::string>());
    } else if (node.is_array()) {
        for (const auto& item : node) {
            if (item.is_string()) {
                out.push_back(item.get<std::string>());
            }
        }
    }
    return out;
}

static std::optional<BaseRef> ParseBaseRef(const nlohmann::json& node) {
    if (node.is_string()) {
        return BaseRef { node.get<std::string>(), "" };
    }
    if (node.is_object() && node.contains("name") && node["name"].is_string()) {
        return BaseRef { node["name"].get<std::string>(), node.value("version", "") };
    }
    return std::nullopt;
}

std::vector<BaseRef> ParseWorksWith(const nlohmann::json& node) {
    std::vector<BaseRef> out;
    if (node.is_array()) {
        for (const auto& item : node) {
            if (auto ref = ParseBaseRef(item)) {
                out.push_back(std::move(*ref));
            }
        }
    } else if (auto ref = ParseBaseRef(node)) {
        out.push_back(std::move(*ref));
    }
    return out;
}

static std::string StringField(const nlohmann::json& root, const char* key) {
    const auto it = root.find(key);
    return it != root.end() && it->is_string() ? it->get<std::string>() : "";
}

std::optional<Manifest> ParseManifest(const std::string& text) {
    try {
        const nlohmann::json root = nlohmann::json::parse(text);
        if (!root.is_object()) {
            return std::nullopt;
        }
        Manifest manifest;
        manifest.name = StringField(root, "name");
        manifest.version = StringField(root, "version");
        manifest.author = StringField(root, "author");
        manifest.description = StringField(root, "description");
        manifest.website = StringField(root, "website");
        manifest.romSha1 = StringField(root, "rom_sha1");
        if (const auto it = root.find("works_with"); it != root.end()) {
            manifest.worksWith = ParseWorksWith(*it);
        }
        if (const auto it = root.find("disable"); it != root.end()) {
            manifest.disable = StringList(*it);
        }
        if (const auto it = root.find("force"); it != root.end() && it->is_object()) {
            for (const auto& [key, value] : it->items()) {
                manifest.force.emplace_back(key, value);
            }
        }
        return manifest;
    } catch (const std::exception& e) {
        SPDLOG_WARN("Mod: unreadable {}: {}", kManifestFile, e.what());
        return std::nullopt;
    }
}

std::string ManifestText(const Manifest& manifest) {
    nlohmann::ordered_json root;
    root["name"] = manifest.name;
    const std::pair<const char*, const std::string*> strings[] = {
        { "version", &manifest.version }, { "author", &manifest.author },    { "description", &manifest.description },
        { "website", &manifest.website }, { "rom_sha1", &manifest.romSha1 },
    };
    for (const auto& [key, value] : strings) {
        if (!value->empty()) {
            root[key] = *value;
        }
    }
    if (manifest.worksWith.has_value()) {
        nlohmann::ordered_json bases = nlohmann::ordered_json::array();
        for (const BaseRef& ref : *manifest.worksWith) {
            if (ref.versions.empty()) {
                bases.push_back(ref.name);
            } else {
                bases.push_back({ { "name", ref.name }, { "version", ref.versions } });
            }
        }
        root["works_with"] = bases;
    }
    if (!manifest.disable.empty()) {
        root["disable"] = manifest.disable;
    }
    if (!manifest.force.empty()) {
        root["force"] = nlohmann::ordered_json::object();
        for (const auto& [key, value] : manifest.force) {
            root["force"][key] = value;
        }
    }
    return root.dump(2);
}

std::optional<Manifest> ReadManifest(Ship::Archive& archive) {
    auto file = archive.LoadFile(kManifestFile);
    if (file == nullptr || file->Buffer == nullptr || file->Buffer->size() <= file->BufferOffset) {
        return std::nullopt;
    }
    return ParseManifest(std::string(file->Buffer->begin() + file->BufferOffset, file->Buffer->end()));
}

std::shared_ptr<Ship::Archive> OpenArchive(const fs::path& path) {
    std::shared_ptr<Ship::Archive> archive;
    std::error_code ec;
    const std::string abs = fs::absolute(path, ec).generic_string();
    if (fs::is_directory(path, ec)) {
        archive = std::make_shared<Ship::FolderArchive>(abs);
    } else {
        archive = std::make_shared<Ship::O2rArchive>(abs);
    }
    archive->Load();
    if (!archive->IsLoaded()) {
        SPDLOG_WARN("Mod: could not open {}", abs);
        return nullptr;
    }
    return archive;
}

static std::vector<int64_t> VersionParts(const std::string& version) {
    std::vector<int64_t> parts;
    size_t pos = 0;
    while (pos <= version.size()) {
        const size_t dot = std::min(version.find('.', pos), version.size());
        int64_t value = 0;
        for (size_t i = pos; i < dot && std::isdigit(static_cast<unsigned char>(version[i])); i++) {
            value = value * 10 + (version[i] - '0');
        }
        parts.push_back(value);
        pos = dot + 1;
    }
    return parts;
}

static int CompareVersions(const std::string& a, const std::string& b) {
    const auto pa = VersionParts(a);
    const auto pb = VersionParts(b);
    for (size_t i = 0; i < std::max(pa.size(), pb.size()); i++) {
        const int64_t x = i < pa.size() ? pa[i] : 0;
        const int64_t y = i < pb.size() ? pb[i] : 0;
        if (x != y) {
            return x < y ? -1 : 1;
        }
    }
    return 0;
}

bool VersionInRange(const std::string& version, const std::string& range) {
    std::vector<std::string> tokens;
    std::string current;
    for (const char c : range) {
        if (c == ' ' || c == ',') {
            if (!current.empty()) {
                tokens.push_back(std::move(current));
                current.clear();
            }
        } else {
            current += c;
        }
    }
    if (!current.empty()) {
        tokens.push_back(std::move(current));
    }

    for (size_t i = 0; i < tokens.size(); i++) {
        std::string token = tokens[i];
        size_t opLength = 0;
        while (opLength < token.size() && (token[opLength] == '<' || token[opLength] == '>' || token[opLength] == '='))
        {
            opLength++;
        }
        std::string op = token.substr(0, opLength);
        std::string target = token.substr(opLength);
        if (target.empty() && i + 1 < tokens.size()) {
            target = tokens[++i];
        }
        if (op.empty()) {
            op = ">=";
        }
        const int cmp = CompareVersions(version, target);
        const bool ok = op == ">=" ? cmp >= 0
            : op == ">"            ? cmp > 0
            : op == "<="           ? cmp <= 0
            : op == "<"            ? cmp < 0
                                   : cmp == 0;
        if (!ok) {
            return false;
        }
    }
    return true;
}

Base ActiveBase() {
    const Romhack::Info* info = Romhack::Active();
    return info != nullptr ? Base { info->name, info->version } : Base { kBaseVanilla, "" };
}

static std::string BaseLabel(const std::string& name) {
    return name == kBaseVanilla ? "Paper Mario" : name;
}

std::optional<std::string> IncompatibleReason(const Manifest& manifest, const Base& base) {
    if (manifest.IsRomhack()) {
        return std::string("This is a romhack; install it in mods/~romhacks and pick it in the Romhack Menu.");
    }
    if (!manifest.worksWith.has_value() || manifest.worksWith->empty()) {
        return std::nullopt;
    }
    for (const BaseRef& ref : *manifest.worksWith) {
        if (ref.name == "*") {
            return std::nullopt;
        }
        if (ref.name == base.name && (ref.versions.empty() || VersionInRange(base.version, ref.versions))) {
            return std::nullopt;
        }
    }
    std::string targets;
    for (const BaseRef& ref : *manifest.worksWith) {
        targets +=
            (targets.empty() ? "" : ", ") + BaseLabel(ref.name) + (ref.versions.empty() ? "" : " " + ref.versions);
    }
    const std::string current = BaseLabel(base.name) + (base.version.empty() ? "" : " " + base.version);
    return fmt::format("Made for {}, not {}.", targets, current);
}

static std::vector<ModRecord> sRecords;
static std::map<std::string, std::optional<Manifest>> sManifestCache;

void RecordMod(ModRecord record) {
    sManifestCache[record.file] = record.manifest;
    sRecords.push_back(std::move(record));
}

const std::vector<ModRecord>& ModRecords() {
    return sRecords;
}

const ModRecord* FindModRecord(const std::string& file) {
    const auto it =
        std::find_if(sRecords.begin(), sRecords.end(), [&](const ModRecord& record) { return record.file == file; });
    return it != sRecords.end() ? &*it : nullptr;
}

const std::optional<Manifest>& CachedManifest(const std::string& file, const fs::path& path) {
    auto it = sManifestCache.find(file);
    if (it == sManifestCache.end()) {
        std::optional<Manifest> manifest;
        if (auto archive = OpenArchive(path)) {
            manifest = ReadManifest(*archive);
        }
        it = sManifestCache.emplace(file, std::move(manifest)).first;
    }
    return it->second;
}

} // namespace Mod
