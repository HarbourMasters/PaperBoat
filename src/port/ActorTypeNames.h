#pragma once

#include <cstdint>
#include <vector>

typedef struct {
    const char* name;
    int32_t actorType;
    bool isUnused; // UNUSED_*/_DUP/_STUB entries, hidden behind a toggle
} ActorTypeName;

// Tattle flags are one bit per ACTOR_TYPE_*, so this mirrors the whole actor type enum.
extern const std::vector<ActorTypeName> gActorTypeNames;

const char* ActorTypeNames_Get(int32_t actorType);
