#include "port/api/world.h"
#include "port/api/WorldTables.hpp"

#include "port/ShipInit.hpp"
#include "port/api/SizedDef.hpp"
#include "port/api/StableIds.hpp"
#ifdef ENABLE_SCRIPTING
#include "port/api/ModOwner.hpp"
#endif

#include "common.h"
#include "battle/battle.h"

#include <array>
#include <memory>
#include <string>
#include <vector>

namespace {

// A mod map keeps its slot for the session, so the map IDs of the others never change.
constexpr int kModMapsPerArea = 64;
// The last of the battle areas, which the game leaves empty, holds the mod battles.
constexpr int kModBattleArea = ARRAY_COUNT(gBattleAreas) - 1;
constexpr int kModBattles = 256;

struct AreaMaps {
    int vanillaCount = 0;
    std::vector<MapConfig> maps;
    std::vector<std::unique_ptr<std::string>> names;
    std::vector<std::string> owners;
};

std::array<AreaMaps, ARRAY_COUNT(gAreas)> sAreaMaps;

struct CustomBattle {
    bool used = false;
    std::string owner;
};

std::vector<Battle> sBattles;
std::array<CustomBattle, kModBattles> sBattleInfo;
StableIds sBattleNumbers("battles", 0, kModBattles - 1);

std::string CurrentOwner() {
#ifdef ENABLE_SCRIPTING
    return ModOwner::Current();
#else
    return {};
#endif
}

int FindArea(const char* name) {
    const std::string wanted = std::string(name).rfind("area_", 0) == 0 ? name : std::string("area_") + name;
    for (int area = 0; area < ARRAY_COUNT(gAreas) && gAreas[area].maps != nullptr; area++) {
        if (wanted == gAreas[area].id) {
            return area;
        }
    }
    return -1;
}

// Copies an area's maps into room for mod maps and points the area at the copy, the first time a mod adds one.
AreaMaps& Grow(int area) {
    AreaMaps& entry = sAreaMaps[area];
    if (entry.maps.empty()) {
        entry.vanillaCount = gAreas[area].mapCount;
        entry.maps.reserve(entry.vanillaCount + kModMapsPerArea);
        entry.maps.assign(gAreas[area].maps, gAreas[area].maps + entry.vanillaCount);
        gAreas[area].maps = entry.maps.data();
    }
    return entry;
}

// A battle without enemies on one of the game's stages, for numbers no mod registers.
Battle EmptyBattle() {
    Battle battle = {};
    battle.name = "";
    battle.stage = (*gBattleAreas[0].stages)[0].stage;
    return battle;
}

void GrowBattles() {
    if (!sBattles.empty()) {
        return;
    }
    sBattles.assign(kModBattles, EmptyBattle());
    BattleArea& area = gBattleAreas[kModBattleArea];
    area = {};
    area.name = (char*) "Mods";
    area.battles = (BattleList*) sBattles.data();
}

#ifdef ENABLE_SCRIPTING
void InitWorldApi() {
    ModOwner::AddReleaser([](const std::string& mod) {
        for (AreaMaps& entry : sAreaMaps) {
            for (size_t slot = 0; slot < entry.owners.size(); slot++) {
                if (entry.owners[slot] == mod) {
                    C_UnregisterMap(entry.names[slot]->c_str());
                }
            }
        }
        for (int index = 0; index < kModBattles; index++) {
            if (sBattleInfo[index].used && sBattleInfo[index].owner == mod) {
                C_UnregisterBattle(kModBattleArea << 8 | index);
            }
        }
    });
}

RegisterShipInitFunc sInitWorldApi(InitWorldApi);
#endif

} // namespace

bool WorldTables::IsModMap(int area, int map) {
    if (area < 0 || area >= ARRAY_COUNT(gAreas)) {
        return false;
    }
    const AreaMaps& entry = sAreaMaps[area];
    return !entry.maps.empty() && map >= entry.vanillaCount;
}

extern "C" int C_RegisterMapSized(const char* areaName, const C_MapDef* mapDef, uint32_t size) {
    const SizedDef<C_MapDef> sized(mapDef, size);
    const C_MapDef* def = sized.get();
    if (areaName == nullptr || def == nullptr || def->id == nullptr || def->settings == nullptr) {
        return 0;
    }
    if (strlen(def->id) == 0 || strlen(def->id) > MAP_ID_MAX_LEN) {
        SPDLOG_ERROR("Map {}: the name must be 1 to {} characters", def->id, MAP_ID_MAX_LEN);
        return 0;
    }
    const int area = FindArea(areaName);
    if (area < 0) {
        SPDLOG_ERROR("Map {}: there is no area {}", def->id, areaName);
        return 0;
    }

    AreaMaps& entry = Grow(area);
    s16 foundArea = -1;
    s16 foundMap = -1;
    int slot = -1;
    for (size_t i = 0; i < entry.names.size(); i++) {
        if (*entry.names[i] == def->id) {
            slot = (int) i;
        }
    }
    if (slot < 0) {
        if (get_map_IDs_by_name(def->id, &foundArea, &foundMap)) {
            SPDLOG_ERROR("Map {}: a map with this name exists", def->id);
            return 0;
        }
        if ((int) entry.names.size() >= kModMapsPerArea) {
            SPDLOG_ERROR("Map {}: {} has no room for more mod maps", def->id, gAreas[area].id);
            return 0;
        }
        slot = (int) entry.names.size();
        entry.names.push_back(std::make_unique<std::string>(def->id));
        entry.owners.emplace_back();
        entry.maps.emplace_back();
    }

    MapConfig& map = entry.maps[entry.vanillaCount + slot];
    map = {};
    map.id = entry.names[slot]->data();
    map.settings = (MapSettings*) def->settings;
    map.bgName = (char*) def->bg_name;
    map.init = (MapInit) def->init;
    map.songVariation = def->song_variation;
    map.sfxReverb = def->sfx_reverb;
    entry.owners[slot] = CurrentOwner();
    gAreas[area].mapCount = (s32) entry.maps.size();
    return 1;
}

extern "C" void C_UnregisterMap(const char* id) {
    if (id == nullptr) {
        return;
    }
    for (AreaMaps& entry : sAreaMaps) {
        for (size_t slot = 0; slot < entry.names.size(); slot++) {
            if (*entry.names[slot] == id) {
                // The slot stays so the other maps keep their IDs, under a name no map lookup finds.
                MapConfig& map = entry.maps[entry.vanillaCount + slot];
                map.settings = nullptr;
                map.init = nullptr;
                map.id = (char*) "";
                entry.owners[slot].clear();
            }
        }
    }
}

extern "C" int32_t C_RegisterBattleSized(const C_BattleDef* battleDef, uint32_t size) {
    const SizedDef<C_BattleDef> sized(battleDef, size);
    const C_BattleDef* def = sized.get();
    if (def == nullptr || def->id == nullptr || def->id[0] == '\0' || def->stage == nullptr) {
        return -1;
    }
    if (def->formation_size <= 0 || def->formation == nullptr) {
        SPDLOG_ERROR("Battle {}: it needs at least one enemy", def->id);
        return -1;
    }
    if (gBattleAreas[kModBattleArea].battles != nullptr && sBattles.empty()) {
        SPDLOG_ERROR("Battle {}: the battle area for mods is in use", def->id);
        return -1;
    }

    GrowBattles();
    const std::string owner = CurrentOwner();
    const int index = sBattleNumbers.Register(def->id, owner);
    if (index < 0) {
        return -1;
    }
    Battle& battle = sBattles[index];
    battle = EmptyBattle();
    battle.name = sBattleNumbers.IdOf(index)->c_str();
    battle.formationSize = def->formation_size;
    battle.formation = (Formation*) def->formation;
    battle.stage = (Stage*) def->stage;
    battle.onBattleStart = (EvtScript*) def->on_battle_start;
    sBattleInfo[index] = { true, owner };
    return kModBattleArea << 8 | index;
}

extern "C" void C_UnregisterBattle(int32_t battleID) {
    const int index = battleID & 0xFF;
    if ((battleID >> 8) != kModBattleArea || !sBattleInfo[index].used) {
        return;
    }
    sBattleInfo[index] = {};
    sBattleNumbers.Unregister(index);
    sBattles[index] = EmptyBattle();
}

extern "C" int32_t C_FindBattle(const char* id) {
    if (id == nullptr) {
        return -1;
    }
    const int index = sBattleNumbers.Find(id);
    return index >= 0 && sBattleInfo[index].used ? kModBattleArea << 8 | index : -1;
}
