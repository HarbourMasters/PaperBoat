#include "ActorBlueprints.h"

#include "port/ActorTypeNames.h"
#include "port/ShipInit.hpp"
#include "port/hooks/Events.h"
#include "port/ui/cvar_prefixes.h"

#include <libultraship/bridge/consolevariablebridge.h>
#include <nlohmann/json.hpp>
#include <ship/Context.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <fstream>
#include <map>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

#include "common.h"
#include "battle/battle.h"

using nlohmann::ordered_json;

extern "C" {
extern ActorBlueprint b_area_tik2_blooper_baby;
extern ActorBlueprint b_area_isk_part_2_chain_chomp;
extern ActorBlueprint b_area_kzn2_lava_bud;
extern ActorBlueprint b_area_kzn2_petit_piranha_bomb;
extern ActorBlueprint b_area_flo2_tuff_puff;
extern ActorBlueprint b_area_omo2_1_shy_squad;
extern ActorBlueprint b_area_omo2_2_stilt_guy;
extern ActorBlueprint b_area_omo2_3_shy_stack;
extern ActorBlueprint b_area_omo2_4_signal_guy;
extern ActorBlueprint b_area_omo2_5_shy_squad_redux;
extern ActorBlueprint b_area_pra3_goombario_clone;
extern ActorBlueprint b_area_pra3_kooper_clone;
extern ActorBlueprint b_area_pra3_bombette_clone;
extern ActorBlueprint b_area_pra3_parakarry_clone;
extern ActorBlueprint b_area_pra3_bow_clone;
extern ActorBlueprint b_area_pra3_watt_clone;
extern ActorBlueprint b_area_pra3_sushie_clone;
extern ActorBlueprint b_area_pra3_lakilester_clone;
extern ActorBlueprint b_area_mac_goombario_lee;
extern ActorBlueprint b_area_mac_kooper_lee;
extern ActorBlueprint b_area_mac_bombette_lee;
extern ActorBlueprint b_area_mac_parakarry_lee;
extern ActorBlueprint b_area_mac_bow_lee;
extern ActorBlueprint b_area_mac_watt_lee;
extern ActorBlueprint b_area_mac_sushie_lee;
extern ActorBlueprint b_area_mac_lakilester_lee;
extern ActorBlueprint battle_partner_goombario;
extern ActorBlueprint battle_partner_kooper;
extern ActorBlueprint battle_partner_bombette;
extern ActorBlueprint battle_partner_parakarry;
extern ActorBlueprint battle_partner_bow;
extern ActorBlueprint battle_partner_watt;
extern ActorBlueprint battle_partner_sushie;
extern ActorBlueprint battle_partner_lakilester;
extern ActorBlueprint battle_partner_twink;
}

namespace ActorBlueprints {

#define CVAR_ACTOR_BLUEPRINTS_ENABLED CVAR_ENHANCEMENT("ActorBlueprints.Enabled")

#define PRESET_FORMAT         "paperboat-actor-blueprints"
#define PRESET_VERSION        1
#define PRESET_AUTOSAVE_FILE  "actor_blueprints.json"
#define AUTOSAVE_DELAY_FRAMES 30
#define SPIN_SMASH_IMMUNE     255
#define SPIN_SMASH_IMMUNE_UI  5
#define MAX_ATTACK_DAMAGE     99

static const FieldInfo sFieldInfo[FIELD_COUNT] = {
    { "maxHP", "Max HP", "Starting and maximum HP. Some bosses set their own HP from script mid-fight.", 1, 999 },
    { "attackPercent", "Attack Power %",
      "Scales the damage of every attack this actor makes, before the target's defense. Moves that deal no damage "
      "stay harmless.",
      0, 500 },
    { "attackBonus", "Attack Bonus", "Flat damage added after scaling, only to attacks that already deal damage.", -10,
      20 },
    { "level", "Level", "Drives the Star Points earned for defeating this enemy.", 0, 99 },
    { "coinReward", "Coin Reward", "Coins added to the battle's payout when this enemy is defeated.", 0, 99 },
    { "escapeChance", "Flee Chance", "Chance (%) this enemy runs away when hit by a fear attack.", 0, 100 },
    { "powerBounceChance", "Power Bounce Chance", "Base chance (%) for each extra Power Bounce / Multibonk hit.", 0,
      100 },
    { "airLiftChance", "Air Lift Chance", "Base chance (%) for Parakarry's Air Lift to carry this enemy away.", 0,
      100 },
    { "hurricaneChance", "Hurricane Chance", "Base chance (%) for Lakilester's Hurricane to blow this enemy away.", 0,
      100 },
    { "spookChance", "Spook Chance", "Base chance (%) for Bow's Spook to scare this enemy off.", 0, 100 },
    { "upAndAwayChance", "Up & Away Chance", "Base chance (%) for the Up & Away star power to remove this enemy.", 0,
      100 },
    { "spinSmashReq", "Spin Smash Weight",
      "Hammer tier needed to launch this enemy with Spin Smash (0-1 any hammer, 2 Super, 3 Ultra). 5 = can't be "
      "launched.",
      0, SPIN_SMASH_IMMUNE_UI },
};

static const char* sChapterNames[CHAPTER_COUNT] = {
    "Prologue", "Ch. 1", "Ch. 2", "Ch. 3",     "Ch. 4",    "Ch. 5",
    "Ch. 6",    "Ch. 7", "Ch. 8", "Toad Town", "Partners", "Other",
};

// Indexed like gBattleAreas in src/battle/battle.cpp.
static const Chapter sAreaChapters[] = {
    CHAPTER_PROLOGUE,  // kmr_part_1
    CHAPTER_PROLOGUE,  // kmr_part_2
    CHAPTER_PROLOGUE,  // kmr_part_3
    CHAPTER_TOAD_TOWN, // mac
    CHAPTER_PROLOGUE,  // hos
    CHAPTER_1,         // nok
    CHAPTER_1,         // trd_part_1
    CHAPTER_1,         // trd_part_2
    CHAPTER_1,         // trd_part_3
    CHAPTER_2,         // iwa
    CHAPTER_2,         // sbk
    CHAPTER_2,         // isk_part_1
    CHAPTER_2,         // isk_part_2
    CHAPTER_3,         // mim
    CHAPTER_3,         // arn
    CHAPTER_3,         // dgb
    CHAPTER_4,         // omo
    CHAPTER_4,         // omo2
    CHAPTER_4,         // omo3
    CHAPTER_5,         // kgr
    CHAPTER_5,         // jan
    CHAPTER_5,         // jan2
    CHAPTER_5,         // kzn
    CHAPTER_5,         // kzn2
    CHAPTER_6,         // flo
    CHAPTER_6,         // flo2
    CHAPTER_TOAD_TOWN, // tik
    CHAPTER_TOAD_TOWN, // tik2
    CHAPTER_TOAD_TOWN, // tik3
    CHAPTER_7,         // sam
    CHAPTER_7,         // sam2
    CHAPTER_7,         // pra
    CHAPTER_7,         // pra2
    CHAPTER_7,         // pra3
    CHAPTER_8,         // kpa
    CHAPTER_8,         // kpa2
    CHAPTER_8,         // kpa3
    CHAPTER_8,         // kpa4
    CHAPTER_8,         // kkj
    CHAPTER_OTHER,     // dig
    CHAPTER_4,         // omo2_1
    CHAPTER_4,         // omo2_2
    CHAPTER_4,         // omo2_3
    CHAPTER_4,         // omo2_4
    CHAPTER_4,         // omo2_5
    CHAPTER_4,         // omo2_6
};

// Battle actors that aren't opponents: the player, partners, helpers and props.
static const std::unordered_set<int32_t> sNonEnemyTypes = {
    ACTOR_TYPE_PLAYER,
    ACTOR_TYPE_GOOMBARIO,
    ACTOR_TYPE_KOOPER,
    ACTOR_TYPE_BOMBETTE,
    ACTOR_TYPE_PARAKARRY,
    ACTOR_TYPE_BOW,
    ACTOR_TYPE_WATT,
    ACTOR_TYPE_SUSHIE,
    ACTOR_TYPE_LAKILESTER,
    ACTOR_TYPE_TWINK,
    ACTOR_TYPE_ELDSTAR,
    ACTOR_TYPE_GOOMBARIO_TUTOR1,
    ACTOR_TYPE_GOOMNUT_TREE,
    ACTOR_TYPE_GULPIT_ROCKS,
    ACTOR_TYPE_SLOT_MACHINE_START,
    ACTOR_TYPE_SLOT_MACHINE_STOP,
    ACTOR_TYPE_WHACKA,
};

// kmr_part_3 hosts every Jr. Troopa rematch, so its area chapter only fits the first one.
static const std::unordered_map<int32_t, Chapter> sChapterOverrides = {
    { ACTOR_TYPE_JR_TROOPA_1, CHAPTER_PROLOGUE }, { ACTOR_TYPE_JR_TROOPA_2, CHAPTER_1 },
    { ACTOR_TYPE_JR_TROOPA_3, CHAPTER_3 },        { ACTOR_TYPE_JR_TROOPA_4, CHAPTER_5 },
    { ACTOR_TYPE_JR_TROOPA_5, CHAPTER_7 },        { ACTOR_TYPE_JR_TROOPA_6, CHAPTER_8 },
};

static bool IsListedEnemy(int32_t actorType) {
    if (sNonEnemyTypes.contains(actorType)) {
        return false;
    }
    for (const ActorTypeName& entry : gActorTypeNames) {
        if (entry.actorType == actorType) {
            return !entry.isUnused;
        }
    }
    return true;
}

// The UI thread edits overrides while the game thread reads them inside battle hooks.
static std::mutex sMutex;
static std::map<int32_t, Override> sOverrides;
static std::vector<CatalogEntry> sCatalog;
static std::unordered_map<int32_t, size_t> sCatalogIndex;
static bool sCatalogBuilt = false;

// Game thread only. Edited copies handed to create_actor; never freed so live actors keep valid pointers.
static std::unordered_map<const ActorBlueprint*, std::unique_ptr<ActorBlueprint>> sBlueprintCopies;

static bool sAutosavePending = false;
static int32_t sAutosaveCountdown = 0;

bool Override::Any() const {
    return std::any_of(std::begin(isSet), std::end(isSet), [](bool set) { return set; });
}

const FieldInfo& GetFieldInfo(Field field) {
    return sFieldInfo[field];
}

bool FieldApplies(const CatalogEntry& entry, Field field) {
    if (entry.chapter == CHAPTER_PARTNERS) {
        return field == FIELD_ATTACK_PERCENT || field == FIELD_ATTACK_BONUS;
    }
    return true;
}

const char* GetChapterName(Chapter chapter) {
    return sChapterNames[chapter];
}

int32_t GetDefault(const ActorBlueprint* blueprint, Field field) {
    switch (field) {
        case FIELD_ATTACK_PERCENT:
            return 100;
        case FIELD_ATTACK_BONUS:
            return 0;
        default:
            break;
    }

    if (blueprint == nullptr) {
        return 0;
    }

    switch (field) {
        case FIELD_MAX_HP:
            return blueprint->maxHP;
        case FIELD_LEVEL:
            return blueprint->level;
        case FIELD_COIN_REWARD:
            return blueprint->coinReward;
        case FIELD_ESCAPE_CHANCE:
            return blueprint->escapeChance;
        case FIELD_POWER_BOUNCE_CHANCE:
            return blueprint->powerBounceChance;
        case FIELD_AIR_LIFT_CHANCE:
            return blueprint->airLiftChance;
        case FIELD_HURRICANE_CHANCE:
            return blueprint->hurricaneChance;
        case FIELD_SPOOK_CHANCE:
            return blueprint->spookChance;
        case FIELD_UP_AND_AWAY_CHANCE:
            return blueprint->upAndAwayChance;
        case FIELD_SPIN_SMASH_REQ:
            return blueprint->spinSmashReq == SPIN_SMASH_IMMUNE ? SPIN_SMASH_IMMUNE_UI
                                                                : std::min<int32_t>(blueprint->spinSmashReq, 4);
        default:
            return 0;
    }
}

static void ApplyToBlueprint(ActorBlueprint* blueprint, const Override& ov) {
    for (int32_t i = 0; i < FIELD_COUNT; i++) {
        if (!ov.isSet[i]) {
            continue;
        }
        int32_t value = ov.value[i];
        switch ((Field) i) {
            case FIELD_MAX_HP:
                blueprint->maxHP = value;
                break;
            case FIELD_LEVEL:
                blueprint->level = value;
                break;
            case FIELD_COIN_REWARD:
                blueprint->coinReward = value;
                break;
            case FIELD_ESCAPE_CHANCE:
                blueprint->escapeChance = value;
                break;
            case FIELD_POWER_BOUNCE_CHANCE:
                blueprint->powerBounceChance = value;
                break;
            case FIELD_AIR_LIFT_CHANCE:
                blueprint->airLiftChance = value;
                break;
            case FIELD_HURRICANE_CHANCE:
                blueprint->hurricaneChance = value;
                break;
            case FIELD_SPOOK_CHANCE:
                blueprint->spookChance = value;
                break;
            case FIELD_UP_AND_AWAY_CHANCE:
                blueprint->upAndAwayChance = value;
                break;
            case FIELD_SPIN_SMASH_REQ:
                blueprint->spinSmashReq = value >= SPIN_SMASH_IMMUNE_UI ? SPIN_SMASH_IMMUNE : value;
                break;
            default:
                break;
        }
    }
}

static bool HasBlueprintFields(const Override& ov) {
    for (int32_t i = 0; i < FIELD_COUNT; i++) {
        if (ov.isSet[i] && i != FIELD_ATTACK_PERCENT && i != FIELD_ATTACK_BONUS) {
            return true;
        }
    }
    return false;
}

// Caller holds sMutex.
static void AddToCatalog(const ActorBlueprint* blueprint, Chapter chapter) {
    if (!IsListedEnemy(blueprint->type)) {
        return;
    }
    auto it = sCatalogIndex.find(blueprint->type);
    if (it != sCatalogIndex.end()) {
        CatalogEntry& entry = sCatalog[it->second];
        if (entry.blueprint != blueprint) {
            entry.variantCount++;
        }
        return;
    }
    auto chapterOverride = sChapterOverrides.find(blueprint->type);
    if (chapterOverride != sChapterOverrides.end()) {
        chapter = chapterOverride->second;
    }
    sCatalogIndex[blueprint->type] = sCatalog.size();
    sCatalog.push_back({ blueprint->type, blueprint, chapter, 1 });
}

// Caller holds sMutex.
static void BuildCatalog() {
    if (sCatalogBuilt) {
        return;
    }
    sCatalogBuilt = true;

    std::unordered_map<const ActorBlueprint*, bool> seen;
    for (size_t areaIdx = 0; areaIdx < ARRAY_COUNT(gBattleAreas); areaIdx++) {
        BattleList* battles = gBattleAreas[areaIdx].battles;
        if (battles == nullptr) {
            continue;
        }
        Chapter chapter = areaIdx < ARRAY_COUNT(sAreaChapters) ? sAreaChapters[areaIdx] : CHAPTER_OTHER;

        for (Battle* battle = *battles; battle->formation != nullptr || battle->name != nullptr; battle++) {
            for (s32 i = 0; i < battle->formationSize; i++) {
                const ActorBlueprint* blueprint = (*battle->formation)[i].actor;
                if (blueprint == nullptr || seen[blueprint]) {
                    continue;
                }
                seen[blueprint] = true;
                AddToCatalog(blueprint, chapter);
            }
        }
    }

    // Only ever summoned mid-battle, so no formation table lists them.
    static const std::pair<const ActorBlueprint*, Chapter> sSummonedOnly[] = {
        { &b_area_isk_part_2_chain_chomp, CHAPTER_2 },
        { &b_area_omo2_1_shy_squad, CHAPTER_4 },
        { &b_area_omo2_2_stilt_guy, CHAPTER_4 },
        { &b_area_omo2_3_shy_stack, CHAPTER_4 },
        { &b_area_omo2_4_signal_guy, CHAPTER_4 },
        { &b_area_omo2_5_shy_squad_redux, CHAPTER_4 },
        { &b_area_kzn2_lava_bud, CHAPTER_5 },
        { &b_area_kzn2_petit_piranha_bomb, CHAPTER_5 },
        { &b_area_flo2_tuff_puff, CHAPTER_6 },
        { &b_area_pra3_goombario_clone, CHAPTER_7 },
        { &b_area_pra3_kooper_clone, CHAPTER_7 },
        { &b_area_pra3_bombette_clone, CHAPTER_7 },
        { &b_area_pra3_parakarry_clone, CHAPTER_7 },
        { &b_area_pra3_bow_clone, CHAPTER_7 },
        { &b_area_pra3_watt_clone, CHAPTER_7 },
        { &b_area_pra3_sushie_clone, CHAPTER_7 },
        { &b_area_pra3_lakilester_clone, CHAPTER_7 },
        { &b_area_tik2_blooper_baby, CHAPTER_TOAD_TOWN },
        { &b_area_mac_goombario_lee, CHAPTER_TOAD_TOWN },
        { &b_area_mac_kooper_lee, CHAPTER_TOAD_TOWN },
        { &b_area_mac_bombette_lee, CHAPTER_TOAD_TOWN },
        { &b_area_mac_parakarry_lee, CHAPTER_TOAD_TOWN },
        { &b_area_mac_bow_lee, CHAPTER_TOAD_TOWN },
        { &b_area_mac_watt_lee, CHAPTER_TOAD_TOWN },
        { &b_area_mac_sushie_lee, CHAPTER_TOAD_TOWN },
        { &b_area_mac_lakilester_lee, CHAPTER_TOAD_TOWN },
    };
    for (const auto& [blueprint, chapter] : sSummonedOnly) {
        AddToCatalog(blueprint, chapter);
    }

    static const ActorBlueprint* sPartners[] = {
        &battle_partner_goombario, &battle_partner_kooper,     &battle_partner_bombette,
        &battle_partner_parakarry, &battle_partner_bow,        &battle_partner_watt,
        &battle_partner_sushie,    &battle_partner_lakilester, &battle_partner_twink,
    };
    for (const ActorBlueprint* blueprint : sPartners) {
        sCatalogIndex[blueprint->type] = sCatalog.size();
        sCatalog.push_back({ blueprint->type, blueprint, CHAPTER_PARTNERS, 1 });
    }
}

static std::string GetAutosavePath() {
    return Ship::Context::GetPathRelativeToAppDirectory(PRESET_AUTOSAVE_FILE, "pm64");
}

// Caller holds sMutex.
static ordered_json SerializeOverrides() {
    ordered_json root;
    root["format"] = PRESET_FORMAT;
    root["version"] = PRESET_VERSION;
    ordered_json actors = ordered_json::array();
    for (const auto& [actorType, ov] : sOverrides) {
        if (!ov.Any()) {
            continue;
        }
        ordered_json actor;
        actor["type"] = actorType;
        if (const char* name = ActorTypeNames_Get(actorType)) {
            actor["name"] = name;
        }
        for (int32_t i = 0; i < FIELD_COUNT; i++) {
            if (ov.isSet[i]) {
                actor[sFieldInfo[i].key] = ov.value[i];
            }
        }
        actors.push_back(actor);
    }
    root["actors"] = actors;
    return root;
}

static bool DeserializeOverrides(const ordered_json& root, std::map<int32_t, Override>* out, std::string* error) {
    if (!root.is_object() || root.value("format", "") != PRESET_FORMAT) {
        *error = "Not an actor blueprint preset (missing \"format\": \"" PRESET_FORMAT "\").";
        return false;
    }
    if (root.value("version", 0) > PRESET_VERSION) {
        *error = "Preset was made by a newer version of Paperboat.";
        return false;
    }
    if (!root.contains("actors") || !root["actors"].is_array()) {
        *error = "Preset has no \"actors\" list.";
        return false;
    }

    for (const auto& actor : root["actors"]) {
        if (!actor.is_object() || !actor.contains("type") || !actor["type"].is_number_integer()) {
            continue;
        }
        int32_t actorType = actor["type"].get<int32_t>();
        if (actorType < 0 || actorType > 0xFF) {
            continue;
        }
        Override ov;
        for (int32_t i = 0; i < FIELD_COUNT; i++) {
            const FieldInfo& info = sFieldInfo[i];
            if (actor.contains(info.key) && actor[info.key].is_number_integer()) {
                ov.isSet[i] = true;
                ov.value[i] = std::clamp(actor[info.key].get<int32_t>(), info.min, info.max);
            }
        }
        if (ov.Any()) {
            (*out)[actorType] = ov;
        }
    }
    return true;
}

static bool WriteJson(const std::filesystem::path& path, const ordered_json& root, std::string* error) {
    std::ofstream file(path);
    if (!file.is_open()) {
        *error = "Could not open " + path.string() + " for writing.";
        return false;
    }
    file << root.dump(4);
    return true;
}

static bool ReadJson(const std::filesystem::path& path, ordered_json* root, std::string* error) {
    std::ifstream file(path);
    if (!file.is_open()) {
        *error = "Could not open " + path.string() + ".";
        return false;
    }
    *root = ordered_json::parse(file, nullptr, false);
    if (root->is_discarded()) {
        *error = "File is not valid JSON.";
        return false;
    }
    return true;
}

// Caller holds sMutex.
static void ScheduleAutosave() {
    sAutosavePending = true;
    sAutosaveCountdown = AUTOSAVE_DELAY_FRAMES;
}

static void FlushAutosave() {
    ordered_json root;
    {
        std::lock_guard<std::mutex> lock(sMutex);
        if (!sAutosavePending || --sAutosaveCountdown > 0) {
            return;
        }
        sAutosavePending = false;
        root = SerializeOverrides();
    }
    std::string error;
    if (!WriteJson(GetAutosavePath(), root, &error)) {
        SPDLOG_ERROR("ActorBlueprints: {}", error);
    }
}

static void LoadAutosave() {
    std::filesystem::path path = GetAutosavePath();
    if (!std::filesystem::exists(path)) {
        return;
    }
    ordered_json root;
    std::map<int32_t, Override> loaded;
    std::string error;
    if (!ReadJson(path, &root, &error) || !DeserializeOverrides(root, &loaded, &error)) {
        SPDLOG_ERROR("ActorBlueprints: failed to load {}: {}", path.string(), error);
        return;
    }
    std::lock_guard<std::mutex> lock(sMutex);
    sOverrides = std::move(loaded);
}

bool IsEnabled() {
    return CVarGetInteger(CVAR_ACTOR_BLUEPRINTS_ENABLED, 1) != 0;
}

void SetEnabled(bool enabled) {
    CVarSetInteger(CVAR_ACTOR_BLUEPRINTS_ENABLED, enabled ? 1 : 0);
    CVarSave();
}

std::vector<CatalogEntry> GetCatalog() {
    std::lock_guard<std::mutex> lock(sMutex);
    BuildCatalog();
    return sCatalog;
}

Override GetOverride(int32_t actorType) {
    std::lock_guard<std::mutex> lock(sMutex);
    auto it = sOverrides.find(actorType);
    return it != sOverrides.end() ? it->second : Override {};
}

void SetOverride(int32_t actorType, Field field, int32_t value) {
    std::lock_guard<std::mutex> lock(sMutex);
    Override& ov = sOverrides[actorType];
    ov.isSet[field] = true;
    ov.value[field] = std::clamp(value, sFieldInfo[field].min, sFieldInfo[field].max);
    ScheduleAutosave();
}

void ClearOverride(int32_t actorType, Field field) {
    std::lock_guard<std::mutex> lock(sMutex);
    auto it = sOverrides.find(actorType);
    if (it == sOverrides.end()) {
        return;
    }
    it->second.isSet[field] = false;
    if (!it->second.Any()) {
        sOverrides.erase(it);
    }
    ScheduleAutosave();
}

void ClearActor(int32_t actorType) {
    std::lock_guard<std::mutex> lock(sMutex);
    sOverrides.erase(actorType);
    ScheduleAutosave();
}

void ClearAll() {
    std::lock_guard<std::mutex> lock(sMutex);
    sOverrides.clear();
    ScheduleAutosave();
}

int32_t CountModifiedActors() {
    std::lock_guard<std::mutex> lock(sMutex);
    return (int32_t) sOverrides.size();
}

bool ExportPreset(const std::filesystem::path& path, std::string* error) {
    ordered_json root;
    {
        std::lock_guard<std::mutex> lock(sMutex);
        root = SerializeOverrides();
    }
    return WriteJson(path, root, error);
}

bool ImportPreset(const std::filesystem::path& path, std::string* error) {
    ordered_json root;
    std::map<int32_t, Override> loaded;
    if (!ReadJson(path, &root, error) || !DeserializeOverrides(root, &loaded, error)) {
        return false;
    }
    std::lock_guard<std::mutex> lock(sMutex);
    sOverrides = std::move(loaded);
    ScheduleAutosave();
    return true;
}

static void ApplyAttackOverride(int32_t actorType, int32_t* damage) {
    if (!IsEnabled() || *damage <= 0) {
        return;
    }

    Override ov;
    {
        std::lock_guard<std::mutex> lock(sMutex);
        auto it = sOverrides.find(actorType);
        if (it == sOverrides.end()) {
            return;
        }
        ov = it->second;
    }

    int32_t scaled = *damage;
    if (ov.isSet[FIELD_ATTACK_PERCENT]) {
        scaled = (scaled * ov.value[FIELD_ATTACK_PERCENT] + 50) / 100;
        if (scaled == 0 && ov.value[FIELD_ATTACK_PERCENT] > 0) {
            scaled = 1;
        }
    }
    if (ov.isSet[FIELD_ATTACK_BONUS] && scaled > 0) {
        scaled += ov.value[FIELD_ATTACK_BONUS];
    }
    *damage = std::clamp(scaled, 0, MAX_ATTACK_DAMAGE);
}

static void RegisterActorBlueprints_Init() {
    LoadAutosave();

    REGISTER_LISTENER(OnActorBlueprintLoad, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnActorBlueprintLoad* ev = (OnActorBlueprintLoad*) event;
        const ActorBlueprint* original = *ev->blueprint;
        Override ov;

        {
            std::lock_guard<std::mutex> lock(sMutex);
            BuildCatalog();
            if (sCatalogIndex.find(original->type) == sCatalogIndex.end()) {
                AddToCatalog(original, CHAPTER_OTHER);
            }
            if (!IsEnabled()) {
                return;
            }
            auto it = sOverrides.find(original->type);
            if (it == sOverrides.end() || !HasBlueprintFields(it->second)) {
                return;
            }
            ov = it->second;
        }

        std::unique_ptr<ActorBlueprint>& copy = sBlueprintCopies[original];
        if (copy == nullptr) {
            copy = std::make_unique<ActorBlueprint>();
        }
        *copy = *original;
        ApplyToBlueprint(copy.get(), ov);
        *ev->blueprint = copy.get();
    });

    REGISTER_LISTENER(OnEnemyAttackDamage, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnEnemyAttackDamage* ev = (OnEnemyAttackDamage*) event;
        ApplyAttackOverride(ev->attacker->actorBlueprint->type, ev->damage);
    });

    REGISTER_LISTENER(OnPartnerAttackDamage, EVENT_PRIORITY_NORMAL, [](IEvent* event) {
        OnPartnerAttackDamage* ev = (OnPartnerAttackDamage*) event;
        ApplyAttackOverride(ev->partner->actorType, ev->damage);
    });

    REGISTER_LISTENER(GameFrameUpdate, EVENT_PRIORITY_NORMAL, [](IEvent*) { FlushAutosave(); });
}

static RegisterShipInitFunc initActorBlueprintsFunc(RegisterActorBlueprints_Init);

} // namespace ActorBlueprints
