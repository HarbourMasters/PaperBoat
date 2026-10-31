#pragma once

#include "common.h"
#include "effects.h"
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

extern u8 TTYD64_HealingItem_Bool[1];
extern u8 TTYD64_HealingBox_PartnersOrder[12];
extern u8 TTYD64_ActorDead[4];

extern const u8 TTYD64_String_Slash_W[];
extern const u8 TTYD64_String_Slash_B[];
extern const u8 TTYD64_String_HP_W[];
extern const u8 TTYD64_String_HP_B[];
extern const u8 TTYD64_String_Separator[];
extern const u8 TTYD64_String_HealBox_LeftBox[];
extern const u8 TTYD64_String_MarioAndPartner[];
extern const u8 TTYD64_String_PartnerDead[];
extern const u8 TTYD64_PartnersHPTable[33];
extern const s32 TTYD64_HealingBox_Strings[10];
extern const s16 TTYD64_HealingBox_Data[2];
extern const u16 TTYD64_PartyMenu_FlipOffsets[2];
extern HudScript TTYD64_IconScript_Cursor;

extern EvtScript TTYD64_UseItem_Init;
extern EvtScript TTYD64_UseItem_ShowItem;
extern EvtScript TTYD64_UseItem_Eat;
extern EvtScript TTYD64_UseItem_Drink;
extern EvtScript TTYD64_DoPartnerSpikeContact;
extern EvtScript TTYD64_DoPartnerBurnContact;
extern EvtScript TTYD64_ph_UseLifeShroom;
extern EvtScript TTYD64_Script_SwapHeroesPositions_MoveMarioUpfront;
extern EvtScript TTYD64_Script_SHP_MMU_MovePartner;
extern EvtScript TTYD64_PartnerRunAway;
extern EvtScript TTYD64_Items_RestoreHeroeTurn;

extern s32 PopupMenu_SelectedIndex;
extern s8 PopupNotBattle;
extern s8 MovesCursorPos;

void dispatch_event_general(Actor* actor, s32 event);
s32 dispatch_damage_event_partner_0(s32 damageAmount, s32 event, s32 stopMotion);

API_CALLABLE(TTYD64_ph_ReadPtrByte);
API_CALLABLE(TTYD64_ph_WritePtrByte);

s32 TTYD64_GetPartnerHP_byID(s32 partnerID);
void TTYD64_sync_status_menu_OnlyPartners(void);
void TTYD64_ph_DrawPartnerHP(s32 msgID, s32 x, s32 y, s32 dark, s32 drawLabel);
void TTYD64_ph_DrawMarioHP(s32 x, s32 y, s32 dark);
s32 TTYD64_ph_InlineMsg(const u8* msg);

void TTYD64_InstallPartnerHPBattle(void);
void TTYD64_InstallPartnerHPWorld(void);

#ifdef __cplusplus
}
#endif
