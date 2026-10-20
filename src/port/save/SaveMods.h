#pragma once

#include <nlohmann/json.hpp>

struct PlayerData;

// Mod content in save files, kept under "mods". "ids" maps the id of every mod item the file holds to the number it
// had when written, with the mod that registered it. "data" holds the values mods keep for the file.
namespace SaveMods {

// Renumbers the mod items of a file read from disk to this session's numbers, and makes its mod data the current
// file's. Items the file holds without an id, from before mods were saved by id, become no item.
void Load(const nlohmann::json& file, PlayerData* player);
// Starts a new file, with no mod data.
void Reset();
// Writes the ids of the mod items the file holds and the current file's mod data.
void Store(nlohmann::ordered_json& file, const PlayerData* player);
// Warns about mod items in the current file that no loaded mod registers.
void CheckMissing();
// Mod data of the current file, the one last loaded or created.
nlohmann::json& Data();

} // namespace SaveMods
