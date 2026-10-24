#include "MapRegistry.h"

#include <algorithm>
#include <cstring>
#include <iterator>
#include <memory>
#include <unordered_map>
#include <vector>

#include <spdlog/spdlog.h>

#include "ModInternal.h"
#include "port/hooks/Events.h"

extern "C" {
#include "common.h"
#include "map.h"
}

struct AreaState {
    std::unique_ptr<MapConfig[]> storage;
    MapConfig* originalMaps = nullptr;
    s32 originalCount = 0;
    std::vector<std::string> mapOwners;
    std::string addedBy;
    bool orphaned = false;
};

static AreaState& Area(int32_t area) {
    static AreaState sAreas[AREA_TABLE_CAPACITY];
    return sAreas[area];
}

extern "C" MapConfig* Mod_FindMapConfig(const char* mapName) {
    for (s32 i = 0; gAreas[i].maps != nullptr; i++) {
        for (s32 j = 0; j < gAreas[i].mapCount; j++) {
            if (strcmp(gAreas[i].maps[j].id, mapName) == 0) {
                return &gAreas[i].maps[j];
            }
        }
    }
    return nullptr;
}

static bool ValidMapArea(int32_t area) {
    if (area < 0 || area >= AREA_TABLE_CAPACITY - 1 || gAreas[area].maps == nullptr) {
        SPDLOG_ERROR("Mod: map area {} is not registered", area);
        return false;
    }
    return true;
}

extern "C" int32_t Mod_AddArea(const char* owner, const char* id, const char* name) {
    if (id == nullptr) {
        return -1;
    }
    int32_t area = 0;
    for (; area < AREA_TABLE_CAPACITY - 1 && gAreas[area].maps != nullptr; area++) {
        if (strcmp(gAreas[area].id, id) == 0) {
            return area;
        }
    }
    if (area >= AREA_TABLE_CAPACITY - 1) {
        SPDLOG_ERROR("Mod: area table is full, cannot add {}", id);
        return -1;
    }
    AreaState& state = Area(area);
    state = AreaState {};
    state.storage = std::make_unique<MapConfig[]>(MOD_AREA_MAP_CAPACITY);
    state.addedBy = Mod::OwnerName(owner);
    gAreas[area].mapCount = 0;
    gAreas[area].maps = state.storage.get();
    gAreas[area].id = const_cast<char*>(id);
    gAreas[area].name = const_cast<char*>(name != nullptr ? name : id);
    return area;
}

extern "C" MapConfig* Mod_AddMap(const char* owner, int32_t area, const MapConfig* config) {
    if (config == nullptr || config->id == nullptr || !ValidMapArea(area)) {
        return nullptr;
    }
    AreaConfig* areaConfig = &gAreas[area];
    for (s32 i = 0; i < areaConfig->mapCount; i++) {
        if (strcmp(areaConfig->maps[i].id, config->id) == 0) {
            SPDLOG_ERROR("Mod: map {} already exists in {}", config->id, areaConfig->id);
            return nullptr;
        }
    }
    AreaState& state = Area(area);
    if (areaConfig->maps != state.storage.get()) {
        if (areaConfig->mapCount > MOD_AREA_MAP_CAPACITY) {
            SPDLOG_ERROR("Mod: area {} has too many maps", areaConfig->id);
            return nullptr;
        }
        state.originalMaps = areaConfig->maps;
        state.originalCount = areaConfig->mapCount;
        state.mapOwners.clear();
        state.storage = std::make_unique<MapConfig[]>(MOD_AREA_MAP_CAPACITY);
        std::copy(areaConfig->maps, areaConfig->maps + areaConfig->mapCount, state.storage.get());
        areaConfig->maps = state.storage.get();
    }
    if (areaConfig->mapCount >= MOD_AREA_MAP_CAPACITY) {
        SPDLOG_ERROR("Mod: area {} is full, cannot add {}", areaConfig->id, config->id);
        return nullptr;
    }
    MapConfig* entry = &areaConfig->maps[areaConfig->mapCount++];
    *entry = *config;
    state.mapOwners.push_back(Mod::OwnerName(owner));
    return entry;
}

static void RemoveOwnerMaps(int32_t area, const std::string& owner) {
    AreaState& state = Area(area);
    AreaConfig* areaConfig = &gAreas[area];
    if (state.storage == nullptr || areaConfig->maps != state.storage.get()) {
        return;
    }
    const s32 base = areaConfig->mapCount - (s32) state.mapOwners.size();
    s32 out = base;
    bool shifted = false;
    std::vector<std::string> keptOwners;
    for (size_t i = 0; i < state.mapOwners.size(); i++) {
        if (state.mapOwners[i] == owner) {
            continue;
        }
        if (out != base + (s32) i) {
            areaConfig->maps[out] = areaConfig->maps[base + i];
            shifted = true;
        }
        keptOwners.push_back(state.mapOwners[i]);
        out++;
    }
    if (shifted) {
        SPDLOG_WARN(
            "Mod: removing {}'s maps from {} moves the indices of maps added after them", owner, areaConfig->id
        );
    }
    areaConfig->mapCount = out;
    state.mapOwners = std::move(keptOwners);
    if (state.mapOwners.empty() && state.addedBy.empty() && !state.orphaned && state.originalMaps != nullptr) {
        areaConfig->maps = state.originalMaps;
        areaConfig->mapCount = state.originalCount;
        state = AreaState {};
    }
}

static void RemoveOwnerAreas(const std::string& owner) {
    int32_t last = -1;
    while (last + 1 < AREA_TABLE_CAPACITY - 1 && gAreas[last + 1].maps != nullptr) {
        last++;
    }
    for (int32_t area = last; area >= 0; area--) {
        AreaState& state = Area(area);
        const bool owned = state.orphaned || (!state.addedBy.empty() && state.addedBy == owner);
        if (!owned || gAreas[area].mapCount != 0) {
            break;
        }
        gAreas[area] = AreaConfig {};
        state = AreaState {};
    }
    for (int32_t area = 0; area < AREA_TABLE_CAPACITY - 1 && gAreas[area].maps != nullptr; area++) {
        AreaState& state = Area(area);
        if (state.addedBy == owner) {
            SPDLOG_WARN(
                "Mod: area {} added by {} stays registered, later areas still use the indices after it",
                gAreas[area].id, owner
            );
            state.addedBy.clear();
            state.orphaned = true;
        }
    }
}

struct MapResetData {
    std::string owner;
    void* ptr;
    std::vector<uint8_t> bytes;
};

static std::unordered_map<std::string, std::vector<MapResetData>>& MapResetDataList() {
    static std::unordered_map<std::string, std::vector<MapResetData>> sData;
    return sData;
}

extern "C" void Mod_RegisterMapResetData(const char* owner, const char* map, void* ptr, size_t size) {
    if (map == nullptr || ptr == nullptr || size == 0) {
        return;
    }
    static bool sListening = false;
    if (!sListening) {
        sListening = true;
        REGISTER_LISTENER(OnMapLoad, EVENT_PRIORITY_HIGH, [](IEvent* event) {
            const char* mapName = ((OnMapLoad*) event)->mapName;
            if (mapName == nullptr) {
                return;
            }
            auto& list = MapResetDataList();
            auto it = list.find(mapName);
            if (it == list.end()) {
                return;
            }
            for (const MapResetData& entry : it->second) {
                memcpy(entry.ptr, entry.bytes.data(), entry.bytes.size());
            }
        });
    }
    const std::string name = Mod::OwnerName(owner);
    auto& entries = MapResetDataList()[map];
    for (const MapResetData& entry : entries) {
        if (entry.ptr == ptr && entry.owner != name) {
            SPDLOG_WARN("Mod: {} registers reset data for {} that {} already resets", name, map, entry.owner);
        }
    }
    const uint8_t* src = (const uint8_t*) ptr;
    entries.push_back({ name, ptr, std::vector<uint8_t>(src, src + size) });
}

void Mod::UnregisterMaps(const std::string& owner) {
    auto& resetData = MapResetDataList();
    for (auto it = resetData.begin(); it != resetData.end();) {
        auto& entries = it->second;
        entries.erase(
            std::remove_if(
                entries.begin(), entries.end(), [&](const MapResetData& entry) { return entry.owner == owner; }
            ),
            entries.end()
        );
        it = entries.empty() ? resetData.erase(it) : std::next(it);
    }
    for (int32_t area = 0; area < AREA_TABLE_CAPACITY - 1 && gAreas[area].maps != nullptr; area++) {
        RemoveOwnerMaps(area, owner);
    }
    RemoveOwnerAreas(owner);
}
