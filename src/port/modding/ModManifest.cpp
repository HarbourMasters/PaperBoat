#include "ModManifest.h"

#include <algorithm>
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

std::optional<Manifest> ParseManifest(const std::string& text) {
    try {
        const nlohmann::json root = nlohmann::json::parse(text);
        if (!root.is_object()) {
            return std::nullopt;
        }
        Manifest manifest;
        manifest.name = root.value("name", "");
        manifest.version = root.value("version", "");
        const auto pb = root.find("paperboat");
        if (pb != root.end() && pb->is_object()) {
            manifest.id = pb->value("id", "");
            manifest.kind = pb->value("kind", kKindMod);
            manifest.romSha1 = pb->value("rom_sha1", "");
            if (const auto it = pb->find("works_with"); it != pb->end()) {
                manifest.worksWith = StringList(*it);
            }
            if (const auto it = pb->find("disable"); it != pb->end()) {
                manifest.disable = StringList(*it);
            }
            if (const auto it = pb->find("force"); it != pb->end() && it->is_object()) {
                for (const auto& [key, value] : it->items()) {
                    manifest.force.emplace_back(key, value);
                }
            }
        }
        return manifest;
    } catch (const std::exception& e) {
        SPDLOG_WARN("Mod: unreadable {}: {}", kManifestFile, e.what());
        return std::nullopt;
    }
}

std::string ManifestText(const Manifest& manifest) {
    nlohmann::ordered_json pb;
    pb["id"] = manifest.id;
    pb["kind"] = manifest.kind;
    if (!manifest.romSha1.empty()) {
        pb["rom_sha1"] = manifest.romSha1;
    }
    if (manifest.worksWith.has_value()) {
        pb["works_with"] = *manifest.worksWith;
    }
    pb["disable"] = manifest.disable;
    pb["force"] = nlohmann::ordered_json::object();
    for (const auto& [key, value] : manifest.force) {
        pb["force"][key] = value;
    }

    nlohmann::ordered_json root;
    root["name"] = manifest.name;
    if (!manifest.version.empty()) {
        root["version"] = manifest.version;
    }
    root["paperboat"] = pb;
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

std::string ActiveBase() {
    const Romhack::Info* info = Romhack::Active();
    return info != nullptr ? info->id : kBaseVanilla;
}

static std::string BaseLabel(const std::string& base) {
    if (base == kBaseVanilla) {
        return "Paper Mario";
    }
    const Romhack::Info* info = Romhack::Active();
    return info != nullptr && info->id == base ? info->name : base;
}

std::optional<std::string> IncompatibleReason(const Manifest& manifest, const std::string& base) {
    if (manifest.kind == kKindRomhack) {
        return std::string("This is a romhack; install it in mods/~romhacks and pick it in the Romhack Menu.");
    }
    if (!manifest.worksWith.has_value() || manifest.worksWith->empty()) {
        return std::nullopt;
    }
    for (const std::string& target : *manifest.worksWith) {
        if (target == "*" || target == base) {
            return std::nullopt;
        }
    }
    std::string targets;
    for (const std::string& target : *manifest.worksWith) {
        targets += (targets.empty() ? "" : ", ") + BaseLabel(target);
    }
    return fmt::format("Made for {}, not {}.", targets, BaseLabel(base));
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
