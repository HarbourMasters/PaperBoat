#include "Romhack.h"
#include "RomhackPort.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <filesystem>

#include <libultraship/libultraship.h>
#include <libultraship/bridge/consolevariablebridge.h>
#include <ship/Context.h>
#include <ship/resource/File.h>
#include <ship/resource/archive/Archive.h>
#include <ship/resource/archive/ArchiveManager.h>
#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>

#include "dx/config.h"
#include "port/ShipInit.hpp"
#include "port/hooks/Events.h"
#include "port/modding/MapTextures.h"
#include "port/ui/cvar_prefixes.h"

#define CVAR_ROMHACK_SELECTED CVAR_SETTING("Romhack.Selected")

namespace fs = std::filesystem;

namespace Romhack {

static std::optional<std::string> sLaunchStem;
static std::optional<Info> sActive;
static std::optional<Mod::Manifest> sActiveManifest;
static std::string sActiveStem;

static fs::path ConfigPath() {
    return fs::path(Ship::Context::GetAppBundlePath()) / "config.yml";
}

static nlohmann::json YamlToJson(const YAML::Node& node) {
    if (node.IsSequence()) {
        nlohmann::json out = nlohmann::json::array();
        for (const auto& item : node) {
            out.push_back(YamlToJson(item));
        }
        return out;
    }
    if (node.IsMap()) {
        nlohmann::json out = nlohmann::json::object();
        for (const auto& item : node) {
            out[item.first.as<std::string>()] = YamlToJson(item.second);
        }
        return out;
    }
    if (!node.IsScalar()) {
        return nullptr;
    }
    const std::string text = node.Scalar();
    if (node.Tag() != "!") {
        if (text == "true" || text == "false") {
            return text == "true";
        }
        try {
            size_t used = 0;
            const long long i = std::stoll(text, &used, 0);
            if (used == text.size()) {
                return i;
            }
            const double d = std::stod(text, &used);
            if (used == text.size()) {
                return d;
            }
        } catch (const std::exception&) {
        }
    }
    return text;
}

static std::vector<std::string> YamlStringList(const YAML::Node& node) {
    std::vector<std::string> out;
    if (node.IsScalar()) {
        out.push_back(node.as<std::string>());
    } else if (node.IsSequence()) {
        for (const auto& item : node) {
            out.push_back(item.as<std::string>());
        }
    }
    return out;
}

Mod::Manifest ConfigManifest(const YAML::Node& rom, const std::string& romSha1) {
    const YAML::Node hack = rom["romhack"];
    Mod::Manifest manifest;
    manifest.id = hack["id"].as<std::string>("");
    manifest.name = rom["name"].as<std::string>(manifest.id);
    manifest.version = hack["version"].as<std::string>("");
    manifest.kind = Mod::kKindRomhack;
    manifest.romSha1 = romSha1;
    manifest.worksWith =
        hack["works_with"] ? YamlStringList(hack["works_with"]) : std::vector<std::string> { Mod::kBaseVanilla };
    if (hack["disable"]) {
        manifest.disable = YamlStringList(hack["disable"]);
    }
    if (hack["force"] && hack["force"].IsMap()) {
        for (const auto& item : hack["force"]) {
            manifest.force.emplace_back(item.first.as<std::string>(), YamlToJson(item.second));
        }
    }
    return manifest;
}

std::optional<Mod::Manifest> FindConfigManifest(const Info& info) {
    try {
        const YAML::Node config = YAML::LoadFile(ConfigPath().generic_string());
        std::optional<Mod::Manifest> byId;
        for (const auto& entry : config) {
            const YAML::Node rom = entry.second;
            if (!rom.IsMap() || !rom["romhack"]) {
                continue;
            }
            const std::string sha1 = entry.first.as<std::string>("");
            if (!info.romSha1.empty() && sha1 == info.romSha1) {
                return ConfigManifest(rom, sha1);
            }
            if (!byId.has_value() && rom["romhack"]["id"].as<std::string>("") == info.id) {
                byId = ConfigManifest(rom, sha1);
            }
        }
        return byId;
    } catch (const YAML::Exception& e) {
        SPDLOG_WARN("Romhack: could not read {}: {}", ConfigPath().generic_string(), e.what());
    }
    return std::nullopt;
}

std::vector<Supported> ListSupported() {
    std::vector<Supported> hacks;
    const fs::path configPath = ConfigPath();
    try {
        const YAML::Node config = YAML::LoadFile(configPath.generic_string());
        for (const auto& entry : config) {
            const YAML::Node rom = entry.second;
            if (!rom.IsMap() || !rom["romhack"]) {
                continue;
            }
            const YAML::Node hack = rom["romhack"];
            Supported info;
            info.id = hack["id"].as<std::string>("");
            info.name = rom["name"].as<std::string>(info.id);
            info.version = hack["version"].as<std::string>("");
            info.url = hack["url"].as<std::string>("");
            hacks.push_back(std::move(info));
        }
    } catch (const YAML::Exception& e) {
        SPDLOG_WARN("Romhack: could not read {}: {}", configPath.generic_string(), e.what());
    }
    std::sort(hacks.begin(), hacks.end(), [](const Supported& a, const Supported& b) { return a.name < b.name; });
    return hacks;
}

std::optional<Info> ParseMarker(const std::string& text) {
    try {
        YAML::Node node = YAML::Load(text);
        if (!node["id"]) {
            return std::nullopt;
        }
        Info info;
        info.id = node["id"].as<std::string>();
        info.name = node["name"] ? node["name"].as<std::string>() : info.id;
        info.version = node["version"] ? node["version"].as<std::string>() : "";
        info.romSha1 = node["rom_sha1"] ? node["rom_sha1"].as<std::string>() : "";
        return info;
    } catch (const YAML::Exception& e) {
        SPDLOG_WARN("Romhack: unreadable marker: {}", e.what());
        return std::nullopt;
    }
}

std::string Directory() {
    return Ship::Context::GetPathRelativeToAppDirectory(std::string("mods/") + kFolder);
}

std::vector<std::string> ListArchives() {
    std::vector<std::string> stems;
    std::error_code ec;
    for (const auto& entry : fs::directory_iterator(Directory(), ec)) {
        if (entry.is_regular_file() && entry.path().extension() == ".o2r") {
            stems.push_back(entry.path().stem().string());
        }
    }
    std::sort(stems.begin(), stems.end());
    return stems;
}

std::vector<std::string> ConsumeLaunchArgs(int argc, char* argv[]) {
    std::vector<std::string> rest;
    for (int i = 1; i < argc; i++) {
        const std::string arg = argv[i];
        if ((arg == "-hack" || arg == "--hack") && i + 1 < argc) {
            sLaunchStem = argv[++i];
            continue;
        }
        rest.push_back(arg);
    }
    return rest;
}

std::string GetSelected() {
    if (sLaunchStem.has_value()) {
        return *sLaunchStem;
    }
    return CVarGetString(CVAR_ROMHACK_SELECTED, "");
}

void SetSelected(const std::string& stem) {
    sLaunchStem.reset();
    CVarSetString(CVAR_ROMHACK_SELECTED, stem.c_str());
    Ship::Context::GetRawInstance()->GetConsoleVariables()->Save();
}

void ApplyDataTables() {
    if (Port* port = ActivePort()) {
        port->ApplyDataTables();
    }
}

void Mount(const std::shared_ptr<Ship::ArchiveManager>& archives) {
    const std::string stem = GetSelected();
    if (stem.empty()) {
        return;
    }

    const fs::path path = fs::path(Directory()) / (stem + ".o2r");
    if (!fs::exists(path)) {
        SPDLOG_WARN("Romhack: selected archive {} is missing, starting vanilla", path.string());
        return;
    }

    SPDLOG_INFO("Romhack: loading {}", path.string());
    auto archive = Mod::OpenArchive(path);
    if (archive == nullptr) {
        SPDLOG_WARN("Romhack: could not open {}, starting vanilla", path.string());
        return;
    }

    std::optional<Info> info;
    auto manifest = Mod::ReadManifest(*archive);
    if (manifest.has_value() && manifest->kind == Mod::kKindRomhack && !manifest->id.empty()) {
        info = Info { manifest->id, manifest->name.empty() ? manifest->id : manifest->name, manifest->version,
                      manifest->romSha1 };
    } else {
        manifest.reset();
        auto marker = archive->LoadFile(kMarkerFile);
        if (marker != nullptr && marker->Buffer != nullptr) {
            info = ParseMarker(std::string(marker->Buffer->begin() + marker->BufferOffset, marker->Buffer->end()));
        }
    }
    if (!info.has_value()) {
        SPDLOG_WARN("Romhack: {} has no manifest; treating it as an asset-only hack", stem);
        info = Info { stem, stem, "" };
    }
    if (!manifest.has_value()) {
        manifest = FindConfigManifest(*info);
        if (manifest.has_value()) {
            SPDLOG_INFO(
                "Romhack: {} predates {}; using its config.yml rules, re-extract to embed them", stem,
                Mod::kManifestFile
            );
        }
    }
    archives->AddArchive(archive);
    sActive = info;
    sActiveManifest = manifest;
    sActiveStem = stem;

    const std::string mapTexPrefix = "romhack/maptex_";
    const auto mapTexFiles = archives->ListFiles(mapTexPrefix + "*");
    for (const std::string& file : *mapTexFiles) {
        if (file.rfind(mapTexPrefix, 0) == 0) {
            Mod_RegisterMapTexArchive(info->id.c_str(), file.substr(mapTexPrefix.size()).c_str(), file.c_str());
        }
    }
}

const Info* Active() {
    return sActive.has_value() ? &*sActive : nullptr;
}

const Mod::Manifest* ActiveManifest() {
    return sActiveManifest.has_value() ? &*sActiveManifest : nullptr;
}

const std::string& ActiveStem() {
    return sActiveStem;
}

} // namespace Romhack

extern "C" bool Romhack_IsActive(void) {
    return Romhack::Active() != nullptr;
}

extern "C" const char* Romhack_GetModName(void) {
    const auto* info = Romhack::Active();
    return info != nullptr ? info->name.c_str() : DX_MOD_NAME;
}

extern "C" const char* Romhack_GetVersion(void) {
    const auto* info = Romhack::Active();
    return info != nullptr && !info->version.empty() ? info->version.c_str() : nullptr;
}

extern "C" const char* Romhack_GetId(void) {
    const auto* info = Romhack::Active();
    return info != nullptr ? info->id.c_str() : nullptr;
}

static void OnFileMenuModLabelRomhack(IEvent* event) {
    auto* ev = (OnFileMenuModLabel*) event;
    if (!Romhack_IsActive() || ev->size <= 0) {
        return;
    }
    if (Romhack_GetVersion() != nullptr) {
        snprintf(ev->label, ev->size, "%s (v%s)", Romhack_GetModName(), Romhack_GetVersion());
    } else {
        snprintf(ev->label, ev->size, "%s", Romhack_GetModName());
    }
}

static void ListenRomhackLabel() {
    REGISTER_LISTENER(OnFileMenuModLabel, EVENT_PRIORITY_NORMAL, OnFileMenuModLabelRomhack);
}

static RegisterShipInitFunc sRomhackLabelInit(ListenRomhackLabel);
