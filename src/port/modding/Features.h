#pragma once

#include <ship/utils/color.h>

#include <string>
#include <utility>
#include <vector>

#include <nlohmann/json.hpp>

namespace Features {

struct RuleSource {
    std::string owner;
    std::string name;
    std::vector<std::string> disable;
    std::vector<std::pair<std::string, nlohmann::json>> force;
};

struct Conflict {
    std::string id;
    std::string winner;
    std::string loser;
};

void Resolve(const std::vector<RuleSource>& sources);
void ResolveMounted();

bool IsLocked(const char* id);
std::string LockReason(const char* id);
const char* ForCVar(const char* cvar);
const std::vector<Conflict>& Conflicts();

bool DrawLockedNotice(const char* id);

} // namespace Features

Color_RGBA8 Port_FeatureColor(const char* id, Color_RGBA8 fallback);
