#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct MapConfig;

#define MOD_AREA_MAP_CAPACITY 128

struct MapConfig* Mod_FindMapConfig(const char* mapName);
int32_t Mod_AddArea(const char* owner, const char* id, const char* name);
struct MapConfig* Mod_AddMap(const char* owner, int32_t area, const struct MapConfig* config);
void Mod_RegisterMapResetData(const char* owner, const char* map, void* ptr, size_t size);

#ifdef __cplusplus
}
#endif
