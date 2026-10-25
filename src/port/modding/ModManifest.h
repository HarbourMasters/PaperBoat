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
constexpr const char* kBaseVanilla = "vanilla";

struct BaseRef {
    std::string name;
    std::string versions;
};

struct Base {
    std::string name;
    std::string version;
};

struct Manifest {
    std::string name;
    std::string version;
    std::string author;
    std::string description;
    std::string website;
    std::string romSha1;
    std::optional<std::vector<BaseRef>> worksWith;
    std::vector<std::string> disable;
    std::vector<std::pair<std::string, nlohmann::json>> force;

    bool IsRomhack() const {
        return !romSha1.empty();
    }
};

std::optional<Manifest> ParseManifest(const std::string& text);
std::vector<BaseRef> ParseWorksWith(const nlohmann::json& node);
std::string ManifestText(const Manifest& manifest);
std::optional<Manifest> ReadManifest(Ship::Archive& archive);

std::shared_ptr<Ship::Archive> OpenArchive(const std::filesystem::path& path);

bool VersionInRange(const std::string& version, const std::string& range);

Base ActiveBase();
std::optional<std::string> IncompatibleReason(const Manifest& manifest, const Base& base);

struct ModRecord {
    std::string file;
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
