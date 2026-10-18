#pragma once

#include "common.h"
#include "effects.h"
#include "entity.h"
#include "hud_element.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/hooks/Events.h"
#include "port/romhack/specific/TTYD64/TTYD64.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_flags.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_items.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"

#ifdef __cplusplus
extern "C" {
#endif

void TTYD64_InstallBattleItemsPopups(void);
void TTYD64_InstallBattleItemsShortcuts(void);
void TTYD64_InstallBattleItemsMisc(void);

extern s16 TTYD64_ShortTable_802A285A[12];

API_CALLABLE(TTYD64_bi_Function_IceStorm_ChangeBreathColor);
API_CALLABLE(TTYD64_bi_Function_IceStorm_Rumble);
API_CALLABLE(TTYD64_bi_Function_802A123C_Projectile);
API_CALLABLE(TTYD64_bi_Function_ClearDebuffs);
API_CALLABLE(battle_item_strange_cake_func_802A13E4_7316E4);

extern EntityModelScript TTYD64_bi_EntityModelScript_CoconutBomb;
extern EntityModelScript TTYD64_bi_EntityModelScript_CourageMeal;
extern EntityModelScript TTYD64_bi_EntityModelScript_Dynamite;

#ifdef __cplusplus
}
#endif
