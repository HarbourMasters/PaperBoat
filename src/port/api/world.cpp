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
#include "dx/debug_menu.h"
#include "game_modes.h"
#include "npc.h"
#include "sprite.h"

#include <array>
#include <cstring>
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
    // Battle lists end with an entry that has neither a name nor a formation.
    sBattles.push_back(Battle {});
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

extern "C" void* C_FindBattleStage(const char* map) {
    if (map == nullptr) {
        return nullptr;
    }
    for (int area = 0; area < kModBattleArea; area++) {
        StageList* stages = gBattleAreas[area].stages;
        for (StageListRow* row = stages != nullptr ? *stages : nullptr; row != nullptr && row->name != nullptr; row++) {
            if (strcmp(row->name, map) == 0) {
                return row->stage;
            }
        }
    }
    return nullptr;
}

extern "C" int C_StartBattle(int32_t battleID, int32_t songID, int canFlee, int32_t start) {
#if DX_DEBUG_MENU
    // The encounter code skips the NPC of an enemy with this ID, as the debug menu's battles have none.
    static NpcSettings sSettings;
    static EnemyDrops sNoDrops;
    static Enemy sEnemy;
    static Encounter sEncounter;
    EncounterStatus* es = &gCurrentEncounter;

    if (get_game_mode() != GAME_MODE_WORLD || gEncounterState != ENCOUNTER_STATE_NEUTRAL
        || (gPlayerStatus.flags & PS_FLAG_INPUT_DISABLED)) {
        return 0;
    }
    sNoDrops = {};
    sNoDrops.dropFlags = NPC_DROP_FLAG_80;
    sNoDrops.heartDrops[0] = { F16(100), F16(0), 0, F16(0) };
    sNoDrops.flowerDrops[0] = { F16(100), F16(0), 0, F16(0) };
    // Out of reach of First Attack, Bump Attack and Spin Attack, which would win the battle on contact.
    sSettings = {};
    sSettings.level = 0x7FFF;
    sEnemy = {};
    sEnemy.npcID = DX_DEBUG_DUMMY_ID;
    sEnemy.npcSettings = &sSettings;
    sEnemy.drops = &sNoDrops;
    sEncounter = {};
    sEncounter.encounterID = DX_DEBUG_DUMMY_ID;
    sEncounter.enemy[0] = &sEnemy;
    sEncounter.battle = battleID;
    sEncounter.stage = -1;

    es->curEncounter = &sEncounter;
    es->curEnemy = &sEnemy;
    es->hitType = ENCOUNTER_TRIGGER_NONE;
    es->hitTier = 0;
    es->firstStrikeType = FIRST_STRIKE_NONE;
    switch (start) {
        case C_BATTLE_START_JUMP:
            es->hitType = ENCOUNTER_TRIGGER_JUMP;
            es->firstStrikeType = FIRST_STRIKE_PLAYER;
            switch (gPlayerStatus.actionState) {
                case ACTION_STATE_SPIN_JUMP:
                case ACTION_STATE_SPIN_POUND:
                    es->hitTier = 1;
                    break;
                case ACTION_STATE_TORNADO_JUMP:
                case ACTION_STATE_TORNADO_POUND:
                    es->hitTier = 2;
                    break;
            }
            break;
        case C_BATTLE_START_HAMMER:
            es->hitType = ENCOUNTER_TRIGGER_HAMMER;
            es->hitTier = gPlayerData.hammerLevel;
            es->firstStrikeType = FIRST_STRIKE_PLAYER;
            break;
        case C_BATTLE_START_STRUCK:
            es->firstStrikeType = FIRST_STRIKE_ENEMY;
            break;
    }
    if (es->firstStrikeType == FIRST_STRIKE_PLAYER) {
        sfx_play_sound_at_position(SOUND_HIT_PLAYER_NORMAL, SOUND_SPACE_DEFAULT, gPlayerStatus.pos.x,
                                   gPlayerStatus.pos.y, gPlayerStatus.pos.z);
    }
    es->forbidFleeing = !canFlee;
    es->scriptedBattle = true;
    es->songID = songID;
    es->unk_18 = -1;
    es->fadeOutAmount = 0;
    es->substateDelay = 0;
    es->flags |= ENCOUNTER_FLAG_SKIP_FLEE_DROPS;

    disable_player_input();
    partner_disable_input();

    gEncounterState = ENCOUNTER_STATE_PRE_BATTLE;
    gEncounterSubState = ENCOUNTER_SUBSTATE_PRE_BATTLE_INIT;
    EncounterStateChanged = true;
    return 1;
#else
    return 0;
#endif
}

extern "C" void C_SetActorPartColor(int32_t actorID, int32_t partID, uint32_t color) {
    if (gGameStatusPtr->context != CONTEXT_BATTLE) {
        return;
    }
    Actor* actor = get_actor(actorID);
    ActorPart* part = actor != nullptr ? get_actor_part(actor, partID) : nullptr;
    if (part != nullptr && part->spriteInstanceID >= 0) {
        spr_set_player_instance_color(part->spriteInstanceID, color);
    }
}
