#include "Features.h"
#include "port/Engine.h"

#include <algorithm>
#include <cmath>
#include <optional>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include <imgui.h>
#include <libultraship/bridge/consolevariablebridge.h>
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>

#include "port/ui/cvar_prefixes.h"

namespace Features {

enum class Kind {
    Toggle,
    Int,
    Float,
    Color,
    Action,
};

struct Def {
    const char* id;
    const char* cvar;
    Kind kind;
    float value;
    Color_RGBA8 color;
};

#define FEATURE_TOGGLE(id, cvar, value) \
    { \
        id, cvar, Kind::Toggle, value, { \
        } \
    }
#define FEATURE_INT(id, cvar, value) \
    { \
        id, cvar, Kind::Int, value, { \
        } \
    }
#define FEATURE_COLOR(id, cvar, r, g, b) { id, cvar, Kind::Color, 0, { r, g, b, 255 } }
#define FEATURE_ACTION(id, cvar) \
    { \
        id, cvar, Kind::Action, 0, { \
        } \
    }

static const Def sDefs[] = {
    FEATURE_TOGGLE("cheats.infinite_health", CVAR_CHEAT("InfiniteHealth"), 0),
    FEATURE_TOGGLE("cheats.infinite_fp", CVAR_CHEAT("InfiniteFlowerPoints"), 0),
    FEATURE_TOGGLE("cheats.no_bp_cost", CVAR_CHEAT("NoBPCost"), 0),
    FEATURE_TOGGLE("cheats.max_star_power", CVAR_CHEAT("MaxStarPower"), 0),
    FEATURE_TOGGLE("cheats.max_power_bounce", CVAR_CHEAT("MaxPowerBounceChance"), 0),
    FEATURE_TOGGLE("cheats.double_rewards", CVAR_CHEAT("DoubleRewards"), 0),

    FEATURE_TOGGLE("enhancements.prevent_lz_storage", CVAR_ENHANCEMENT("PreventLoadingZoneStorage"), 0),
    FEATURE_TOGGLE("enhancements.sprint_button", CVAR_ENHANCEMENT("SprintButton"), 0),
    FEATURE_TOGGLE("enhancements.free_qol_badges", CVAR_ENHANCEMENT("FreeQoLBadges"), 0),
    FEATURE_INT("enhancements.action_command_difficulty", CVAR_ENHANCEMENT("ActionCommandDifficulty"), 0),
    FEATURE_INT("enhancements.block_window", CVAR_ENHANCEMENT("BlockWindowMode"), 0),
    FEATURE_TOGGLE("enhancements.no_intro", CVAR_ENHANCEMENT("NoIntro"), 0),
    FEATURE_TOGGLE("enhancements.actor_blueprints", CVAR_ENHANCEMENT("ActorBlueprints.Enabled"), 0),
    FEATURE_INT("enhancements.show_hidden_blocks", CVAR_ENHANCEMENT("ShowHiddenBlocks"), 0),
    FEATURE_TOGGLE("enhancements.mute_i_spy_sound", CVAR_ENHANCEMENT("MuteISpySound"), 0),
    FEATURE_TOGGLE("enhancements.always_chuck_quizmo", CVAR_ENHANCEMENT("AlwaysChuckQuizmo"), 0),

    FEATURE_TOGGLE("graphics.full_height_view", CVAR_ENHANCEMENT("Graphics.FullHeightView"), 0),
    FEATURE_TOGGLE("graphics.rounded_reel", CVAR_ENHANCEMENT("Graphics.RoundedReel"), 0),
    FEATURE_TOGGLE("graphics.disable_mipmaps", CVAR_ENHANCEMENT("Graphics.DisableMipmaps"), 0),
    FEATURE_TOGGLE("graphics.alt_assets", CVAR_ENHANCEMENT("Mods.AlternateAssets"), 0),
    FEATURE_TOGGLE("graphics.hd_mipmaps", CVAR_ENHANCEMENT("Mods.AutoMipmaps"), 0),
    FEATURE_TOGGLE("graphics.sprite_filter", CVAR_2D_TEXTURE_FILTER, 0),
    FEATURE_TOGGLE("graphics.dialogue_filter", CVAR_DIALOGUE_TEXT_FILTER, 0),
    FEATURE_INT("graphics.interpolation_fps", CVAR_SETTING("InterpolationFPS"), 30),
    FEATURE_TOGGLE("graphics.match_refresh_rate", CVAR_SETTING("MatchRefreshRate"), 0),
    FEATURE_INT("graphics.texture_cache", "gGraphics.TextureCache", 0),
    FEATURE_ACTION("graphics.shaders", CVAR_WINDOW("ShaderSettings")),

    FEATURE_TOGGLE("graphics.status_bar.always_show", CVAR_ENHANCEMENT("StatusBar.AlwaysShow"), 0),
    FEATURE_INT("graphics.status_bar.scale", CVAR_ENHANCEMENT("StatusBar.Scale"), 100),
    FEATURE_INT("graphics.status_bar.box_width", CVAR_ENHANCEMENT("StatusBar.BoxWidth"), 100),
    FEATURE_INT("graphics.status_bar.box_height", CVAR_ENHANCEMENT("StatusBar.BoxHeight"), 100),
    FEATURE_TOGGLE("graphics.status_bar.show.background", CVAR_ENHANCEMENT("StatusBar.ShowBackground"), 1),
    FEATURE_TOGGLE("graphics.status_bar.show.hp", CVAR_ENHANCEMENT("StatusBar.ShowHP"), 1),
    FEATURE_TOGGLE("graphics.status_bar.show.fp", CVAR_ENHANCEMENT("StatusBar.ShowFP"), 1),
    FEATURE_TOGGLE("graphics.status_bar.show.star_power", CVAR_ENHANCEMENT("StatusBar.ShowStarPower"), 1),
    FEATURE_TOGGLE("graphics.status_bar.show.star_points", CVAR_ENHANCEMENT("StatusBar.ShowStarPoints"), 1),
    FEATURE_TOGGLE("graphics.status_bar.show.coins", CVAR_ENHANCEMENT("StatusBar.ShowCoins"), 1),
    FEATURE_TOGGLE("graphics.status_bar.show.star_pieces", CVAR_ENHANCEMENT("StatusBar.ShowStarPieces"), 0),
    FEATURE_TOGGLE("graphics.status_bar.show.badges", CVAR_ENHANCEMENT("StatusBar.ShowBadges"), 0),
    FEATURE_TOGGLE("graphics.status_bar.flat_bottom", CVAR_ENHANCEMENT("StatusBar.FlatBottom"), 0),
    FEATURE_TOGGLE("graphics.status_bar.flat_color", CVAR_ENHANCEMENT("StatusBar.FlatColor"), 0),
    FEATURE_COLOR("graphics.status_bar.highlight_color", CVAR_ENHANCEMENT("StatusBar.HighlightColor"), 235, 230, 119),
    FEATURE_COLOR("graphics.status_bar.shadow_color", CVAR_ENHANCEMENT("StatusBar.ShadowColor"), 142, 90, 37),
    FEATURE_COLOR("graphics.status_bar.fill_color", CVAR_ENHANCEMENT("StatusBar.FillColor"), 185, 155, 75),
    FEATURE_ACTION("graphics.status_bar.reset", nullptr),

    FEATURE_ACTION("save.import_n64", nullptr),

    FEATURE_TOGGLE("devtools.debug_menu", CVAR_DEVELOPER_TOOLS("DebugMenu"), 0),
    FEATURE_ACTION("devtools.debug_menu.full_restore", nullptr),
    FEATURE_ACTION("devtools.debug_menu.save_load", nullptr),
    FEATURE_ACTION("devtools.debug_menu.map_select", nullptr),
    FEATURE_ACTION("devtools.debug_menu.battle_select", nullptr),
    FEATURE_ACTION("devtools.debug_menu.story_byte", nullptr),
    FEATURE_ACTION("devtools.debug_menu.sound_player", nullptr),
    FEATURE_ACTION("devtools.debug_menu.partners", nullptr),
    FEATURE_ACTION("devtools.debug_menu.inventory", nullptr),
    FEATURE_ACTION("devtools.debug_menu.collision", nullptr),
    FEATURE_ACTION("devtools.debug_menu.cheats", nullptr),
    FEATURE_ACTION("devtools.debug_menu.evt_debugger", nullptr),
    FEATURE_ACTION("devtools.save_editor", CVAR_WINDOW("SaveEditor")),
    FEATURE_ACTION("devtools.blueprint_editor", CVAR_WINDOW("ActorBlueprintEditor")),
    FEATURE_ACTION("devtools.event_debugger", CVAR_WINDOW("EventDebugger")),
    FEATURE_ACTION("devtools.value_viewer", CVAR_WINDOW("ValueViewerSettings")),
    FEATURE_ACTION("devtools.console", CVAR_WINDOW("Console")),
    FEATURE_ACTION("devtools.stats", CVAR_WINDOW("Stats")),
    FEATURE_TOGGLE("devtools.gfx_trace", CVAR_DEVELOPER_TOOLS("GFXTrace"), 0),
};

#undef FEATURE_TOGGLE
#undef FEATURE_INT
#undef FEATURE_COLOR
#undef FEATURE_ACTION

struct Value {
    int32_t i = 0;
    float f = 0.0f;
    Color_RGBA8 c = {};

    bool operator==(const Value& o) const {
        return i == o.i && f == o.f && c.r == o.c.r && c.g == o.c.g && c.b == o.c.b && c.a == o.c.a;
    }
};

struct State {
    const Def* def = nullptr;
    std::string colorCVar;
    std::vector<std::string> disabledBy;
    std::optional<Value> forced;
    std::string forcedBy;
};

using StateMap = std::unordered_map<std::string_view, State>;

static StateMap& States() {
    static StateMap states = []() {
        StateMap map;
        for (const Def& def : sDefs) {
            State state;
            state.def = &def;
            if (def.kind == Kind::Color && def.cvar != nullptr) {
                state.colorCVar = std::string(def.cvar) + ".Value";
            }
            map.emplace(def.id, std::move(state));
        }
        return map;
    }();
    return states;
}

static const std::unordered_map<std::string, const char*>& CVarIndex() {
    static const std::unordered_map<std::string, const char*> index = []() {
        std::unordered_map<std::string, const char*> map;
        for (const Def& def : sDefs) {
            if (def.cvar != nullptr) {
                map.emplace(def.cvar, def.id);
            }
        }
        return map;
    }();
    return index;
}

static std::vector<Conflict> sConflicts;

static const State* Find(const char* id) {
    if (id == nullptr) {
        return nullptr;
    }
    StateMap& states = States();
    const auto it = states.find(std::string_view(id));
    if (it != states.end()) {
        return &it->second;
    }
    static std::unordered_set<std::string> sWarned;
    if (sWarned.insert(id).second) {
        SPDLOG_WARN("Features: unknown feature id {}", id);
    }
    return nullptr;
}

static std::vector<State*> Match(const std::string& pattern) {
    std::vector<State*> out;
    if (pattern.rfind("settings.", 0) == 0) {
        return out;
    }
    const bool wildcard = pattern.size() >= 2 && pattern.compare(pattern.size() - 2, 2, ".*") == 0;
    const std::string prefix = wildcard ? pattern.substr(0, pattern.size() - 1) : pattern;
    for (auto& [id, state] : States()) {
        if (wildcard ? id.rfind(prefix, 0) == 0 : id == prefix) {
            out.push_back(&state);
        }
    }
    return out;
}

static std::optional<uint8_t> ParseHexByte(const std::string& s, size_t at) {
    if (at + 2 > s.size()) {
        return std::nullopt;
    }
    try {
        return (uint8_t) std::stoul(s.substr(at, 2), nullptr, 16);
    } catch (const std::exception&) {
        return std::nullopt;
    }
}

static std::optional<Value> Convert(const Def& def, const nlohmann::json& json) {
    Value v;
    switch (def.kind) {
        case Kind::Toggle:
        case Kind::Int:
            if (json.is_boolean()) {
                v.i = json.get<bool>() ? 1 : 0;
            } else if (json.is_number()) {
                v.i = (int32_t) std::lround(json.get<double>());
            } else {
                return std::nullopt;
            }
            v.f = (float) v.i;
            return v;
        case Kind::Float:
            if (!json.is_number()) {
                return std::nullopt;
            }
            v.f = json.get<float>();
            v.i = (int32_t) v.f;
            return v;
        case Kind::Color:
            if (json.is_array() && (json.size() == 3 || json.size() == 4)) {
                uint8_t ch[4] = { 0, 0, 0, 255 };
                for (size_t k = 0; k < json.size(); k++) {
                    if (!json[k].is_number()) {
                        return std::nullopt;
                    }
                    ch[k] = (uint8_t) std::clamp(json[k].get<int>(), 0, 255);
                }
                v.c = { ch[0], ch[1], ch[2], ch[3] };
                return v;
            }
            if (json.is_string()) {
                std::string s = json.get<std::string>();
                if (!s.empty() && s[0] == '#') {
                    s.erase(0, 1);
                }
                if (s.size() != 6 && s.size() != 8) {
                    return std::nullopt;
                }
                auto r = ParseHexByte(s, 0), g = ParseHexByte(s, 2), b = ParseHexByte(s, 4);
                auto a = s.size() == 8 ? ParseHexByte(s, 6) : std::optional<uint8_t>(255);
                if (!r || !g || !b || !a) {
                    return std::nullopt;
                }
                v.c = { *r, *g, *b, *a };
                return v;
            }
            return std::nullopt;
        case Kind::Action:
            return std::nullopt;
    }
    return std::nullopt;
}

static std::string FormatValue(const Def& def, const Value& v) {
    switch (def.kind) {
        case Kind::Toggle:
            return v.i != 0 ? "on" : "off";
        case Kind::Int:
            return std::to_string(v.i);
        case Kind::Float:
            return fmt::format("{:g}", v.f);
        case Kind::Color:
            return fmt::format("#{:02X}{:02X}{:02X}", v.c.r, v.c.g, v.c.b);
        case Kind::Action:
            break;
    }
    return "";
}

void Resolve(const std::vector<RuleSource>& sources) {
    for (auto& [id, state] : States()) {
        state.disabledBy.clear();
        state.forced.reset();
        state.forcedBy.clear();
    }
    sConflicts.clear();

    for (const RuleSource& source : sources) {
        for (const std::string& pattern : source.disable) {
            const auto matches = Match(pattern);
            if (matches.empty()) {
                SPDLOG_WARN("Features: {} disables unknown feature {}", source.name, pattern);
            }
            for (State* state : matches) {
                if (std::find(state->disabledBy.begin(), state->disabledBy.end(), source.name)
                    == state->disabledBy.end())
                {
                    state->disabledBy.push_back(source.name);
                }
            }
        }
        for (const auto& [pattern, json] : source.force) {
            const auto matches = Match(pattern);
            if (matches.empty()) {
                SPDLOG_WARN("Features: {} forces unknown feature {}", source.name, pattern);
            }
            for (State* state : matches) {
                const auto value = Convert(*state->def, json);
                if (!value.has_value()) {
                    SPDLOG_WARN(
                        "Features: {} forces {} to {}, which it cannot take", source.name, state->def->id, json.dump()
                    );
                    continue;
                }
                if (state->forced.has_value() && state->forcedBy != source.name && !(*state->forced == *value)) {
                    SPDLOG_WARN(
                        "Features: {} forces {} to {}, overriding {} ({})", source.name, state->def->id,
                        FormatValue(*state->def, *value), state->forcedBy, FormatValue(*state->def, *state->forced)
                    );
                    sConflicts.push_back({ state->def->id, source.name, state->forcedBy });
                }
                state->forced = value;
                state->forcedBy = source.name;
            }
        }
    }

    for (const Def& def : sDefs) {
        const State& state = States().at(def.id);
        if (state.forced.has_value() || !state.disabledBy.empty()) {
            SPDLOG_INFO("Features: {} locked: {}", def.id, LockReason(def.id));
        }
    }
}

bool IsLocked(const char* id) {
    const State* state = Find(id);
    return state != nullptr && (state->forced.has_value() || !state->disabledBy.empty());
}

std::string LockReason(const char* id) {
    const State* state = Find(id);
    if (state == nullptr) {
        return "";
    }
    if (state->forced.has_value()) {
        if (state->def->kind == Kind::Toggle) {
            return fmt::format("Turned {} by {}", FormatValue(*state->def, *state->forced), state->forcedBy);
        }
        return fmt::format("Set to {} by {}", FormatValue(*state->def, *state->forced), state->forcedBy);
    }
    if (state->disabledBy.empty()) {
        return "";
    }
    std::string names;
    for (const std::string& name : state->disabledBy) {
        names += (names.empty() ? "" : ", ") + name;
    }
    return "Disabled by " + names;
}

const char* ForCVar(const char* cvar) {
    if (cvar == nullptr || cvar[0] == '\0') {
        return nullptr;
    }
    const auto& index = CVarIndex();
    const auto it = index.find(cvar);
    return it != index.end() ? it->second : nullptr;
}

const std::vector<Conflict>& Conflicts() {
    return sConflicts;
}

bool DrawLockedNotice(const char* id) {
    if (Port_FeatureAllowed(id)) {
        return false;
    }
    ImGui::TextDisabled("%s.", LockReason(id).c_str());
    return true;
}

} // namespace Features

using namespace Features;

static Value Effective(const State* state, Value cvarValue) {
    if (state->forced.has_value()) {
        return *state->forced;
    }
    if (!state->disabledBy.empty()) {
        Value v;
        v.i = (int32_t) state->def->value;
        v.f = state->def->value;
        v.c = state->def->color;
        return v;
    }
    return cvarValue;
}

Color_RGBA8 Port_FeatureColor(const char* id, Color_RGBA8 fallback) {
    const State* state = Find(id);
    if (state == nullptr) {
        return fallback;
    }
    Value v;
    v.c = state->colorCVar.empty() ? fallback : CVarGetColor(state->colorCVar.c_str(), fallback);
    return Effective(state, v).c;
}

extern "C" bool Port_FeatureAllowed(const char* id) {
    const State* state = Find(id);
    return state == nullptr || state->disabledBy.empty();
}

extern "C" int32_t Port_FeatureInt(const char* id, int32_t fallback) {
    const State* state = Find(id);
    if (state == nullptr) {
        return fallback;
    }
    Value v;
    v.i = state->def->cvar != nullptr ? CVarGetInteger(state->def->cvar, fallback) : fallback;
    return Effective(state, v).i;
}

extern "C" float Port_FeatureFloat(const char* id, float fallback) {
    const State* state = Find(id);
    if (state == nullptr) {
        return fallback;
    }
    Value v;
    v.f = state->def->cvar != nullptr ? CVarGetFloat(state->def->cvar, fallback) : fallback;
    return Effective(state, v).f;
}

extern "C" const char* Port_FeatureDisabledBy(const char* id) {
    const State* state = Find(id);
    return state != nullptr && !state->disabledBy.empty() ? state->disabledBy.front().c_str() : nullptr;
}
