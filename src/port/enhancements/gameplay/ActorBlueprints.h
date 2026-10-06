#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

struct ActorBlueprint;

namespace ActorBlueprints {

enum Field : int32_t {
    FIELD_MAX_HP,
    FIELD_ATTACK_PERCENT,
    FIELD_ATTACK_BONUS,
    FIELD_LEVEL,
    FIELD_COIN_REWARD,
    FIELD_ESCAPE_CHANCE,
    FIELD_POWER_BOUNCE_CHANCE,
    FIELD_AIR_LIFT_CHANCE,
    FIELD_HURRICANE_CHANCE,
    FIELD_SPOOK_CHANCE,
    FIELD_UP_AND_AWAY_CHANCE,
    FIELD_SPIN_SMASH_REQ,
    FIELD_COUNT,
};

struct FieldInfo {
    const char* key;
    const char* label;
    const char* tooltip;
    int32_t min;
    int32_t max;
};

enum Chapter : int32_t {
    CHAPTER_PROLOGUE,
    CHAPTER_1,
    CHAPTER_2,
    CHAPTER_3,
    CHAPTER_4,
    CHAPTER_5,
    CHAPTER_6,
    CHAPTER_7,
    CHAPTER_8,
    CHAPTER_TOAD_TOWN,
    CHAPTER_PARTNERS,
    CHAPTER_OTHER,
    CHAPTER_COUNT,
};

struct Override {
    bool isSet[FIELD_COUNT] = {};
    int32_t value[FIELD_COUNT] = {};

    bool Any() const;
};

struct CatalogEntry {
    int32_t actorType;
    const ActorBlueprint* blueprint;
    Chapter chapter;
    int32_t variantCount;
};

const FieldInfo& GetFieldInfo(Field field);
bool FieldApplies(const CatalogEntry& entry, Field field);
const char* GetChapterName(Chapter chapter);
int32_t GetDefault(const ActorBlueprint* blueprint, Field field);

bool IsEnabled();
void SetEnabled(bool enabled);

std::vector<CatalogEntry> GetCatalog();
Override GetOverride(int32_t actorType);
void SetOverride(int32_t actorType, Field field, int32_t value);
void ClearOverride(int32_t actorType, Field field);
void ClearActor(int32_t actorType);
void ClearAll();
int32_t CountModifiedActors();

bool ExportPreset(const std::filesystem::path& path, std::string* error);
bool ImportPreset(const std::filesystem::path& path, std::string* error);

} // namespace ActorBlueprints
