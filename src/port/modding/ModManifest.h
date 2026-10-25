#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <nlohmann/json.hpp>

namespace Ship {
class Archive;
}

namespace Mod {

constexpr const char* kManifestFile = "manifest.json";
constexpr const char* kKindMod = "mod";
constexpr const char* kKindRomhack = "romhack";
constexpr const char* kBaseVanilla = "vanilla";

struct Manifest {
    std::string name;
    std::string version;
    std::string id;
    std::string kind = kKindMod;
    std::string romSha1;
    std::optional<std::vector<std::string>> worksWith;
    std::vector<std::string> disable;
    std::vector<std::pair<std::string, nlohmann::json>> force;
};

std::optional<Manifest> ParseManifest(const std::string& text);
std::string ManifestText(const Manifest& manifest);
std::optional<Manifest> ReadManifest(Ship::Archive& archive);

std::shared_ptr<Ship::Archive> OpenArchive(const std::filesystem::path& path);

std::string ActiveBase();
std::optional<std::string> IncompatibleReason(const Manifest& manifest, const std::string& base);

struct ModRecord {
    std::string file;
    std::string owner;
    std::string displayName;
    std::optional<Manifest> manifest;
    bool mounted = false;
    std::string skipReason;
};

void RecordMod(ModRecord record);
const std::vector<ModRecord>& ModRecords();
const ModRecord* FindModRecord(const std::string& file);

const std::optional<Manifest>& CachedManifest(const std::string& file, const std::filesystem::path& path);

} // namespace Mod
