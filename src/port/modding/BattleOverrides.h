#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct ActorBlueprint;
struct Battle;
struct StageListRow;
struct DmaTable;

void Mod_SetBattleList(const char* owner, int32_t area, struct Battle* battles);
void Mod_SetStageList(const char* owner, int32_t area, struct StageListRow* stages);
void Mod_SetBattleDmaTable(const char* owner, int32_t area, struct DmaTable* table);
void Mod_ReplaceActorBlueprint(
    const char* owner, const struct ActorBlueprint* original, struct ActorBlueprint* replacement
);

#ifdef __cplusplus
}
#endif
