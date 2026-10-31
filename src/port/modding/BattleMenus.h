#pragma once

#include <stdint.h>

#include "port/hooks/Events.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MOD_BATTLE_MENU_TYPE_FIRST 0x40
#define MOD_BATTLE_MENU_TYPE_LAST  0x7F

typedef struct BattleMenuContext {
    int32_t menu;
    int32_t who;
    int32_t submenu;
} BattleMenuContext;

typedef struct BattleMenuEntry BattleMenuEntry;

struct BattleMenuEntry {
    int32_t menuType;
    int32_t moveID;
    int32_t userIndex;
    int32_t nameMsg;
    int32_t descMsg;
    HudScript* icon;
    int32_t enabled;
    int32_t errorMsg;
    int32_t cost;
    int32_t costPalette;
    int32_t value;
    void (*onSelect)(const BattleMenuContext* ctx, const BattleMenuEntry* entry);
    intptr_t userData;
};

typedef struct BattleMenuList BattleMenuList;

typedef void (*BattleMenuProvider)(const BattleMenuContext* ctx, BattleMenuList* list);

typedef struct BattleMenuHud {
    void (*create)(const BattleMenuContext* ctx);
    void (*destroy)(const BattleMenuContext* ctx);
    void (*drawEntry)(
        const BattleMenuContext* ctx, int32_t index, const BattleMenuEntry* entry, int32_t x, int32_t y, int32_t alpha
    );
} BattleMenuHud;

int32_t Mod_AddBattleMenuEntries(const char* owner, int32_t menu, BattleMenuProvider provider);
int32_t Mod_AddBattleMenuHud(const char* owner, int32_t menu, const BattleMenuHud* hud);
int32_t Mod_AllocBattleMenuType(const char* owner);

int32_t BattleMenu_Count(const BattleMenuList* list);
BattleMenuEntry* BattleMenu_At(BattleMenuList* list, int32_t index);
int32_t BattleMenu_FindType(const BattleMenuList* list, int32_t menuType);
int32_t BattleMenu_FindMove(const BattleMenuList* list, int32_t moveID);
BattleMenuEntry* BattleMenu_Insert(BattleMenuList* list, int32_t index);
void BattleMenu_Remove(BattleMenuList* list, int32_t index);
int32_t BattleMenu_Initial(const BattleMenuList* list);
void BattleMenu_SetInitial(BattleMenuList* list, int32_t index);

#ifdef __cplusplus
}
#endif
