#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace Ship {
class ArchiveManager;
}

namespace Romhack {

// Marker file Torch writes into every romhack o2r; its presence is what makes an archive a romhack.
constexpr const char* kMarkerFile = "romhack/info";
constexpr const char* kFolder = "~romhacks";

struct Info {
    std::string id;
    std::string name;
    std::string version;
    std::string romSha1;
};

// A hack config.yml has a recipe for, whether or not it has been extracted.
struct Supported {
    std::string id;
    std::string name;
    std::string version;
    std::string url;
};
std::vector<Supported> ListSupported();

std::string MarkerText(const Info& info);
std::optional<Info> ParseMarker(const std::string& text);

// Absolute mods/~romhacks directory.
std::string Directory();
// Stems of every romhack o2r in mods/~romhacks.
std::vector<std::string> ListArchives();

// Strips -hack/--hack <stem> from argv; the stem wins over the saved selection for this launch.
std::vector<std::string> ConsumeLaunchArgs(int argc, char* argv[]);

std::string GetSelected();
void SetSelected(const std::string& stem);

// Adds the selected romhack archive after the base game. Call once, after pm64.o2r is mounted.
void Mount(const std::shared_ptr<Ship::ArchiveManager>& archives);
// Runs the active port's ApplyDataTables. Needs the Blob factory, and
// must run before ShipInit so enhancements that snapshot those tables see the hack's values.
void ApplyDataTables();

const Info* Active();
const std::string& ActiveStem();

} // namespace Romhack

extern "C" {
#endif

bool Romhack_IsActive(void);
// The name saves are stamped with and checked against: the active hack's name, or DX_MOD_NAME.
const char* Romhack_GetModName(void);
// The active hack's version from its config.yml entry (e.g. "1.2"), or NULL when unknown or on vanilla.
const char* Romhack_GetVersion(void);
// The active hack's identifier (its config.yml romhack.id), or NULL on vanilla.
const char* Romhack_GetId(void);

#ifdef __cplusplus
}
#endif
