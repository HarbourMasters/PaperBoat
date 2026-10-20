#pragma once

#include <nlohmann/json.hpp>

struct SaveData;

// Mod content in save files, kept under "mods". "ids" maps the id of every mod item the file holds to the number it
// had when written, with the mod that registered it. "map" names the mod map the file was saved in, as its map ID can
// differ between sessions. "data" holds the values mods keep for the file.
namespace SaveMods {

// Renumbers the mod items of a file read from disk to this session's numbers, finds its mod map, and makes its mod
// data the current file's. Items the file holds without an id, from before mods were saved by id, become no item. A
// file saved in a mod map that isn't loaded continues from the area's first map.
void Load(const nlohmann::json& file, SaveData* save);
// Starts a new file, with no mod data.
void Reset();
// Writes the ids of the mod items the file holds, its mod map and the current file's mod data.
void Store(nlohmann::ordered_json& file, const SaveData* save);
// Warns about mod items and the mod map of the current file when no loaded mod registers them.
void CheckMissing();
// Mod data of the current file, the one last loaded or created.
nlohmann::json& Data();

} // namespace SaveMods
