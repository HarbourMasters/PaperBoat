#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ModSaveEditorList {
    MOD_SAVE_EDITOR_STAR_PIECES,
    MOD_SAVE_EDITOR_LETTERS,
    MOD_SAVE_EDITOR_CHAIN_LETTERS,
    MOD_SAVE_EDITOR_RECIPES,
    MOD_SAVE_EDITOR_TATTLES,
    MOD_SAVE_EDITOR_BADGES,
    MOD_SAVE_EDITOR_FOOD,
    MOD_SAVE_EDITOR_BATTLE_ITEMS,
    MOD_SAVE_EDITOR_LIST_COUNT,
} ModSaveEditorList;

typedef enum ModSaveEditorLimit {
    MOD_SAVE_EDITOR_LIMIT_LEVEL,
    MOD_SAVE_EDITOR_LIMIT_MAX_HP,
    MOD_SAVE_EDITOR_LIMIT_MAX_FP,
    MOD_SAVE_EDITOR_LIMIT_MAX_BP,
    MOD_SAVE_EDITOR_LIMIT_STAR_PIECES,
    MOD_SAVE_EDITOR_LIMIT_STAR_POWER,
    MOD_SAVE_EDITOR_LIMIT_STAR_POINTS,
    MOD_SAVE_EDITOR_LIMIT_COINS,
    MOD_SAVE_EDITOR_LIMIT_COUNT,
} ModSaveEditorLimit;

typedef struct ModSaveEditorEntry {
    const char* name;
    const char* detail;
    int32_t id;
    int32_t flag;
    int32_t option;
} ModSaveEditorEntry;

typedef struct ModSaveEditorCounter {
    const char* label;
    int32_t (*get)(void);
    void (*set)(int32_t value);
    int32_t max;
} ModSaveEditorCounter;

typedef struct ModSaveEditorTracker {
    const char* title;
    const char* description;
    const ModSaveEditorEntry* entries;
    int32_t entryCount;
    const ModSaveEditorCounter* counters;
    int32_t counterCount;
} ModSaveEditorTracker;

void Mod_SaveEditorAdd(const char* owner, int32_t list, const ModSaveEditorEntry* entries, int32_t count);
void Mod_SaveEditorHide(const char* owner, int32_t list, int32_t key);
void Mod_SaveEditorClear(const char* owner, int32_t list);
void Mod_SaveEditorSetLimit(const char* owner, int32_t limit, int32_t max);
void Mod_SaveEditorAddTracker(const char* owner, const ModSaveEditorTracker* tracker);
void Mod_SaveEditorAddSection(const char* owner, const char* title, void (*draw)(void));

#ifdef __cplusplus
}

#include <string>
#include <vector>

namespace Mod {

struct SaveEditorEntry {
    std::string name;
    std::string detail;
    int32_t id;
    int32_t flag;
    int32_t option;
    std::string owner;
};

struct SaveEditorCounter {
    std::string label;
    int32_t (*get)(void);
    void (*set)(int32_t value);
    int32_t max;
};

struct SaveEditorTracker {
    std::string owner;
    std::string title;
    std::string description;
    std::vector<SaveEditorEntry> entries;
    std::vector<SaveEditorCounter> counters;
};

struct SaveEditorSection {
    std::string owner;
    std::string title;
    void (*draw)(void);
};

int32_t SaveEditorEntryKey(int32_t list, const SaveEditorEntry& entry);
std::vector<SaveEditorEntry> SaveEditorList(int32_t list, const std::vector<SaveEditorEntry>& defaults);
std::vector<SaveEditorEntry> SaveEditorRemoved(int32_t list, const std::vector<SaveEditorEntry>& defaults);
std::string SaveEditorOwnerName(const std::string& owner);
int32_t SaveEditorLimit(int32_t limit);
const std::vector<SaveEditorTracker>& SaveEditorTrackers();
const std::vector<SaveEditorSection>& SaveEditorSections();

} // namespace Mod

#endif
