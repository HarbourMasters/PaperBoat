#include "common.h"
#include "effects.h"
#include "entity.h"
#include "map.h"
#include "npc.h"
#include "script_api/map.h"
#include <stdio.h>
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/world/nm.h"

API_CALLABLE(AddCoin);
API_CALLABLE(AddItem);
API_CALLABLE(AddStarPieces);
API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(BindNpcInteract);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(CloseMessage);
API_CALLABLE(ContinueSpeech);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMessageValue);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(ShowChoice);
API_CALLABLE(ShowCoinCounter);
API_CALLABLE(ShowGotItem);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(UseExitHeading);

extern NpcData TTYD64_mac_07_NpcGroup_NPCs[];
extern NpcData TTYD64_mac_07_NpcGroup_Shopkeepers[];
extern EvtScript TTYD64_mac_07_Script_BuyItem;
extern EvtScript TTYD64_mac_07_Script_InitShops;
extern EvtScript TTYD64_mac_07_Script_Main;
extern u8 TTYD64_mac_07_String_ToadKid5[];
extern EvtScript TTYD64_mac_07_Script_SetupMusic;
extern EvtScript TTYD64_mac_07_Script_Shop1_Item3;
extern EvtScript TTYD64_mac_07_Script_Shop1_Item1;
extern EvtScript TTYD64_mac_07_Script_Shop1_Item2;
extern EvtScript TTYD64_mac_07_Script_Shop2_Item2;
extern EvtScript TTYD64_mac_07_Script_Shop2_Item3;
extern EvtScript TTYD64_mac_07_Script_Shop2_Item1;
extern EvtScript TTYD64_mac_07_Script_Shop3_Item3;
extern EvtScript TTYD64_mac_07_Script_Shop3_Item1;
extern EvtScript TTYD64_mac_07_Script_Shop3_Item2;
extern u8 TTYD64_mac_07_String_Tattle[];
extern u8 TTYD64_mac_07_Tattle_ToadKid[];
extern u8 TTYD64_mac_07_String_Shopkeeper2_Hi[];
extern u8 TTYD64_mac_07_String_ToadTalking2[];
extern u8 TTYD64_mac_07_String_ToadKid6[];
extern u8 TTYD64_mac_07_String_ToadTalking1[];
extern u8 TTYD64_mac_07_Tattle_Toad[];
extern EvtScript TTYD64_mac_07_Script_MakeEntities;
extern u8 TTYD64_mac_07_String_ShopKeeper_Welcome[];
extern u8 TTYD64_mac_07_String_ShopKeeper_NotEnoughMoney[];
extern u8 TTYD64_mac_07_String_ToadKid4[];
extern u8 TTYD64_mac_07_String_Shopkeeper1_Hi[];
extern EvtScript TTYD64_mac_07_Script_Exit0;
extern u8 TTYD64_mac_07_String_Toad2[];
extern u8 TTYD64_mac_07_String_ToadKid3[];
extern u8 TTYD64_mac_07_String_ToadKid2[];
extern u8 TTYD64_mac_07_Tattle_Shopkeeper[];
extern MapSettings TTYD64_mac_07_Header;
extern u8 TTYD64_mac_07_Tattle_DarkToad[];
extern EvtScript TTYD64_mac_07_Script_Entity_Shine1;
extern EvtScript TTYD64_mac_07_Script_Init_ToadTalking2;
extern u8 TTYD64_mac_07_String_ToadKid1[];
extern u8 TTYD64_mac_07_String_Toad1[];
extern EvtScript TTYD64_mac_07_Script_Interact_Toad2;
extern EvtScript TTYD64_mac_07_Script_Interact_Toad1;
extern u8 TTYD64_mac_07_String_ShopKeeper_ThankYou[];
extern EvtScript TTYD64_mac_07_Script_Interact_Shopkeeper1;
extern EvtScript TTYD64_mac_07_Script_Interact_Shopkeeper2;
extern EvtScript TTYD64_mac_07_Script_Interact_Shopkeeper3;
extern EvtScript TTYD64_mac_07_Script_Interact_DarkToad;
extern EvtScript TTYD64_mac_07_Script_Interact_ToadKid2;
extern EvtScript TTYD64_mac_07_Script_Interact_ToadKid1;
extern EvtScript TTYD64_mac_07_Script_Interact_ToadTalking2;
extern EvtScript TTYD64_mac_07_Script_Interact_ToadTalking1;
extern EvtScript TTYD64_mac_07_Script_Interact_ToadKid6;
extern EvtScript TTYD64_mac_07_Script_Interact_ToadKid5;
extern EvtScript TTYD64_mac_07_Script_Interact_ToadKid4;
extern EvtScript TTYD64_mac_07_Script_Interact_ToadKid3;
extern NpcSettings TTYD64_mac_07_NpcSettings_Toad;
extern EvtScript TTYD64_mac_07_Script_CreateExitTriggers;
extern u8 TTYD64_mac_07_String_Shopkeeper3_Hi[];
extern EvtScript TTYD64_mac_07_Script_Init_Toad2;
extern EvtScript TTYD64_mac_07_Script_Init_Toad1;
extern EvtScript TTYD64_mac_07_Script_Init_Shopkeeper3;
extern EvtScript TTYD64_mac_07_Script_Init_Shopkeeper2;
extern EvtScript TTYD64_mac_07_Script_Init_Shopkeeper1;
extern u8 TTYD64_mac_07_String_DarkToad1_Hi[];
extern NpcGroupList TTYD64_mac_07_NpcGroupList_mac07;
extern EvtScript TTYD64_mac_07_Script_Init_DarkToad;
extern EvtScript TTYD64_mac_07_Script_Init_ToadKid2;
extern EvtScript TTYD64_mac_07_Script_Init_ToadKid1;
extern EvtScript TTYD64_mac_07_Script_Init_ToadKid4;
extern EvtScript TTYD64_mac_07_Script_Init_ToadKid3;
extern EvtScript TTYD64_mac_07_Script_Init_ToadKid6;
extern EvtScript TTYD64_mac_07_Script_Init_ToadKid5;
extern EvtScript TTYD64_mac_07_Script_Init_ToadTalking1;
extern EvtScript TTYD64_mac_07_Script_EnterMap;
extern EntryList TTYD64_mac_07_EntryList;

// clang-format off
static s32 TTYD64_mac_07_GetTattleMsg;

static s32 TTYD64_mac_07_GetTattle(void) {
    return TTYD64_mac_07_GetTattleMsg;
}

NpcData TTYD64_mac_07_NpcGroup_NPCs[] = {
    {
        .id = 4,
        .settings = &TTYD64_mac_07_NpcSettings_Toad,
        .pos = { -742.0f, 0.0f, 173.0f },
        .flags = 0x00112D09,
        .init = &TTYD64_mac_07_Script_Init_DarkToad,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00650001, .walk = 0x00650000, .run = 0x00650000, .chase = 0x00650000, .anim_4 = 0x00650000, .anim_5 = 0x00650000, .death = 0x00650000, .hit = 0x00650000, .anim_8 = 0x00650000, .anim_9 = 0x00650000, .anim_A = 0x00650000, .anim_B = 0x00650000, .anim_C = 0x00650000, .anim_D = 0x00650000, .anim_E = 0x00650000, .anim_F = 0x00650000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 5,
        .settings = &TTYD64_mac_07_NpcSettings_Toad,
        .pos = { 56.0f, 0.0f, 76.0f },
        .flags = 0x00112D09,
        .init = &TTYD64_mac_07_Script_Init_ToadTalking1,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00830004, .walk = 0x00830000, .run = 0x00830000, .chase = 0x00830000, .anim_4 = 0x00830000, .anim_5 = 0x00830000, .death = 0x00830000, .hit = 0x00830000, .anim_8 = 0x00830000, .anim_9 = 0x00830000, .anim_A = 0x00830000, .anim_B = 0x00830000, .anim_C = 0x00830000, .anim_D = 0x00830000, .anim_E = 0x00830000, .anim_F = 0x00830000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 6,
        .settings = &TTYD64_mac_07_NpcSettings_Toad,
        .pos = { 94.0f, 0.0f, 75.0f },
        .flags = 0x00112D09,
        .init = &TTYD64_mac_07_Script_Init_ToadTalking2,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00830004, .walk = 0x00830000, .run = 0x00830000, .chase = 0x00830000, .anim_4 = 0x00830000, .anim_5 = 0x00830000, .death = 0x00830000, .hit = 0x00830000, .anim_8 = 0x00830000, .anim_9 = 0x00830000, .anim_A = 0x00830000, .anim_B = 0x00830000, .anim_C = 0x00830000, .anim_D = 0x00830000, .anim_E = 0x00830000, .anim_F = 0x00830000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 7,
        .settings = &TTYD64_mac_07_NpcSettings_Toad,
        .pos = { 241.0f, 80.0f, 27.0f },
        .flags = 0x00112D09,
        .init = &TTYD64_mac_07_Script_Init_Toad1,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00830001, .walk = 0x00830000, .run = 0x00830000, .chase = 0x00830000, .anim_4 = 0x00830000, .anim_5 = 0x00830000, .death = 0x00830000, .hit = 0x00830000, .anim_8 = 0x00830000, .anim_9 = 0x00830000, .anim_A = 0x00830000, .anim_B = 0x00830000, .anim_C = 0x00830000, .anim_D = 0x00830000, .anim_E = 0x00830000, .anim_F = 0x00830000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 8,
        .settings = &TTYD64_mac_07_NpcSettings_Toad,
        .pos = { 560.0f, 80.0f, -52.0f },
        .flags = 0x00112D09,
        .init = &TTYD64_mac_07_Script_Init_Toad2,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00830301, .walk = 0x00830300, .run = 0x00830300, .chase = 0x00830300, .anim_4 = 0x00830300, .anim_5 = 0x00830300, .death = 0x00830300, .hit = 0x00830300, .anim_8 = 0x00830300, .anim_9 = 0x00830300, .anim_A = 0x00830300, .anim_B = 0x00830300, .anim_C = 0x00830300, .anim_D = 0x00830300, .anim_E = 0x00830300, .anim_F = 0x00830300 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 9,
        .settings = &TTYD64_mac_07_NpcSettings_Toad,
        .pos = { 440.0f, 1.0f, -26.0f },
        .flags = 0x00112D09,
        .init = &TTYD64_mac_07_Script_Init_ToadKid1,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00860101, .walk = 0x00860100, .run = 0x00860100, .chase = 0x00860100, .anim_4 = 0x00860100, .anim_5 = 0x00860100, .death = 0x00860100, .hit = 0x00860100, .anim_8 = 0x00860100, .anim_9 = 0x00860100, .anim_A = 0x00860100, .anim_B = 0x00860100, .anim_C = 0x00860100, .anim_D = 0x00860100, .anim_E = 0x00860100, .anim_F = 0x00860100 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 10,
        .settings = &TTYD64_mac_07_NpcSettings_Toad,
        .pos = { 755.0f, 1.0f, -212.0f },
        .flags = 0x00112D09,
        .init = &TTYD64_mac_07_Script_Init_ToadKid2,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00860101, .walk = 0x00860100, .run = 0x00860100, .chase = 0x00860100, .anim_4 = 0x00860100, .anim_5 = 0x00860100, .death = 0x00860100, .hit = 0x00860100, .anim_8 = 0x00860100, .anim_9 = 0x00860100, .anim_A = 0x00860100, .anim_B = 0x00860100, .anim_C = 0x00860100, .anim_D = 0x00860100, .anim_E = 0x00860100, .anim_F = 0x00860100 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 11,
        .settings = &TTYD64_mac_07_NpcSettings_Toad,
        .pos = { 804.0f, 1.0f, -227.0f },
        .flags = 0x00112D09,
        .init = &TTYD64_mac_07_Script_Init_ToadKid3,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00860001, .walk = 0x00860000, .run = 0x00860000, .chase = 0x00860000, .anim_4 = 0x00860000, .anim_5 = 0x00860000, .death = 0x00860000, .hit = 0x00860000, .anim_8 = 0x00860000, .anim_9 = 0x00860000, .anim_A = 0x00860000, .anim_B = 0x00860000, .anim_C = 0x00860000, .anim_D = 0x00860000, .anim_E = 0x00860000, .anim_F = 0x00860000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 12,
        .settings = &TTYD64_mac_07_NpcSettings_Toad,
        .pos = { 783.0f, 0.0f, -180.0f },
        .flags = 0x00112D09,
        .init = &TTYD64_mac_07_Script_Init_ToadKid4,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00860201, .walk = 0x00860200, .run = 0x00860200, .chase = 0x00860200, .anim_4 = 0x00860200, .anim_5 = 0x00860200, .death = 0x00860200, .hit = 0x00860200, .anim_8 = 0x00860200, .anim_9 = 0x00860200, .anim_A = 0x00860200, .anim_B = 0x00860200, .anim_C = 0x00860200, .anim_D = 0x00860200, .anim_E = 0x00860200, .anim_F = 0x00860200 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 13,
        .settings = &TTYD64_mac_07_NpcSettings_Toad,
        .pos = { 752.0f, -1.0f, 185.0f },
        .flags = 0x00112D09,
        .init = &TTYD64_mac_07_Script_Init_ToadKid5,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00860301, .walk = 0x00860300, .run = 0x00860300, .chase = 0x00860300, .anim_4 = 0x00860300, .anim_5 = 0x00860300, .death = 0x00860300, .hit = 0x00860300, .anim_8 = 0x00860300, .anim_9 = 0x00860300, .anim_A = 0x00860300, .anim_B = 0x00860300, .anim_C = 0x00860300, .anim_D = 0x00860300, .anim_E = 0x00860300, .anim_F = 0x00860300 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 14,
        .settings = &TTYD64_mac_07_NpcSettings_Toad,
        .pos = { 780.0f, 0.0f, 196.0f },
        .flags = 0x00112D09,
        .init = &TTYD64_mac_07_Script_Init_ToadKid6,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00860301, .walk = 0x00860300, .run = 0x00860300, .chase = 0x00860300, .anim_4 = 0x00860300, .anim_5 = 0x00860300, .death = 0x00860300, .hit = 0x00860300, .anim_8 = 0x00860300, .anim_9 = 0x00860300, .anim_A = 0x00860300, .anim_B = 0x00860300, .anim_C = 0x00860300, .anim_D = 0x00860300, .anim_E = 0x00860300, .anim_F = 0x00860300 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_mac_07_NpcGroup_Shopkeepers[] = {
    {
        .id = 1,
        .settings = &TTYD64_mac_07_NpcSettings_Toad,
        .pos = { 260.0f, 1.0f, 12.0f },
        .flags = 0x00112D09,
        .init = &TTYD64_mac_07_Script_Init_Shopkeeper1,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00830001, .walk = 0x00830000, .run = 0x00830000, .chase = 0x00830000, .anim_4 = 0x00830000, .anim_5 = 0x00830000, .death = 0x00830000, .hit = 0x00830000, .anim_8 = 0x00830000, .anim_9 = 0x00830000, .anim_A = 0x00830000, .anim_B = 0x00830000, .anim_C = 0x00830000, .anim_D = 0x00830000, .anim_E = 0x00830000, .anim_F = 0x00830000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 2,
        .settings = &TTYD64_mac_07_NpcSettings_Toad,
        .pos = { 406.0f, 1.0f, -47.0f },
        .flags = 0x00112D09,
        .init = &TTYD64_mac_07_Script_Init_Shopkeeper2,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00830101, .walk = 0x00830100, .run = 0x00830100, .chase = 0x00830100, .anim_4 = 0x00830100, .anim_5 = 0x00830100, .death = 0x00830100, .hit = 0x00830100, .anim_8 = 0x00830100, .anim_9 = 0x00830100, .anim_A = 0x00830100, .anim_B = 0x00830100, .anim_C = 0x00830100, .anim_D = 0x00830100, .anim_E = 0x00830100, .anim_F = 0x00830100 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 3,
        .settings = &TTYD64_mac_07_NpcSettings_Toad,
        .pos = { 596.0f, 1.0f, 79.0f },
        .flags = 0x00112D09,
        .init = &TTYD64_mac_07_Script_Init_Shopkeeper3,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00830201, .walk = 0x00830200, .run = 0x00830200, .chase = 0x00830200, .anim_4 = 0x00830200, .anim_5 = 0x00830200, .death = 0x00830200, .hit = 0x00830200, .anim_8 = 0x00830200, .anim_9 = 0x00830200, .anim_A = 0x00830200, .anim_B = 0x00830200, .anim_C = 0x00830200, .anim_D = 0x00830200, .anim_E = 0x00830200, .anim_F = 0x00830200 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_mac_07_Script_BuyItem = {
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Set(LVarC, LVar2)
    Set(LVarD, LVar3)
    Set(LVarE, LVar4)
    Set(LVar9, LVar5)
    Call(DisablePlayerInput, 1)
    Call(ShowCoinCounter, 1)
    Call(SetMessageValue, LVarB, 0)
    Call(SpeakToPlayer, LVarC, LVarD, LVarE, 0, (Bytecode) TTYD64_mac_07_String_ShopKeeper_Welcome)
    Call(ShowChoice, 0x1E000D)
    IfNe(LVar0, 0)
        Call(CloseMessage)
        Call(ShowCoinCounter, 0)
        Call(DisablePlayerInput, 0)
        Return
    EndIf
    Call(AddCoin, 0)
    IfLt(LVar0, LVarB)
        Call(ContinueSpeech, LVarC, LVarD, LVarE, 0, (Bytecode) TTYD64_mac_07_String_ShopKeeper_NotEnoughMoney)
        Call(ShowCoinCounter, 0)
        Call(DisablePlayerInput, 0)
        Return
    EndIf
    Call(CloseMessage)
    Mul(LVarB, -1)
    Call(AddCoin, LVarB)
    Switch(LVar9)
    CaseEq(1)
        Set(LVar0, MapVar(1))
        Set(LVar1, 16)
        Set(GameFlag(4468), 1)
    CaseEq(2)
        Set(LVar0, MapVar(2))
        Set(LVar1, 17)
        Set(GameFlag(4469), 1)
    CaseEq(3)
        Set(LVar0, MapVar(3))
        Set(LVar1, 18)
        Set(GameFlag(4470), 1)
    CaseEq(4)
        Set(LVar0, MapVar(4))
        Set(LVar1, 20)
        Set(GameFlag(4471), 1)
    CaseEq(5)
        Set(LVar0, MapVar(5))
        Set(LVar1, 21)
        Set(GameFlag(4472), 1)
    CaseEq(6)
        Set(LVar0, MapVar(6))
        Set(LVar1, 22)
        Set(GameFlag(4473), 1)
    CaseEq(7)
        Set(LVar0, MapVar(7))
        Set(LVar1, 24)
        Set(GameFlag(4474), 1)
    CaseEq(8)
        Set(LVar0, MapVar(8))
        Set(LVar1, 25)
        Set(GameFlag(4475), 1)
    CaseEq(9)
        Set(LVar0, MapVar(9))
        Set(LVar1, 26)
        Set(GameFlag(4476), 1)
    EndSwitch
    Call(RemoveItemEntity, LVar0)
    Call(ModifyColliderFlags, 0, LVar1, 0x7FFFFE00)
    Call(ShowGotItem, LVarA, 1, 0)
    Call(ShowCoinCounter, 0)
    IfNe(LVarA, 348)
        Call(TTYD64_GetItemFlags, LVarA, LVar0, 0)
        Switch(LVar0)
        CaseFlag(64)
            Call(TTYD64_nm_AddBadge, LVarA, 0)
        CaseFlag(8)
            Call(TTYD64_nm_AddKeyItem, LVarA)
        CaseDefault
            Call(AddItem, LVarA, 0)
        EndSwitch
    Else
        Call(AddStarPieces, 1)
    EndIf
    Call(SpeakToPlayer, LVarC, LVarD, LVarE, 0, (Bytecode) TTYD64_mac_07_String_ShopKeeper_ThankYou)
    Unbind
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_InitShops = {
    IfEq(GameFlag(4468), 0)
        Call(MakeItemEntity, 369, 244, 0, 59, 1, GameFlag(4468))
        Set(MapVar(1), LVar0)
        BindTrigger(TTYD64_mac_07_Script_Shop1_Item1, 256, 16, 1, 0)
    Else
        Call(ModifyColliderFlags, 0, 16, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4469), 0)
        Call(MakeItemEntity, 131, 277, 0, 59, 1, GameFlag(4469))
        Set(MapVar(2), LVar0)
        BindTrigger(TTYD64_mac_07_Script_Shop1_Item2, 256, 17, 1, 0)
    Else
        Call(ModifyColliderFlags, 0, 17, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4470), 0)
        Call(MakeItemEntity, 162, 309, 0, 59, 1, GameFlag(4470))
        Set(MapVar(3), LVar0)
        BindTrigger(TTYD64_mac_07_Script_Shop1_Item3, 256, 18, 1, 0)
    Else
        Call(ModifyColliderFlags, 0, 18, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4471), 0)
        Call(MakeItemEntity, 146, 390, 0, 0, 1, GameFlag(4471))
        Set(MapVar(4), LVar0)
        BindTrigger(TTYD64_mac_07_Script_Shop2_Item1, 256, 20, 1, 0)
    Else
        Call(ModifyColliderFlags, 0, 20, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4472), 0)
        Call(MakeItemEntity, 301, 423, 0, 0, 1, GameFlag(4472))
        Set(MapVar(5), LVar0)
        BindTrigger(TTYD64_mac_07_Script_Shop2_Item2, 256, 21, 1, 0)
    Else
        Call(ModifyColliderFlags, 0, 21, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4473), 0)
        Call(MakeItemEntity, 142, 455, 0, 0, 1, GameFlag(4473))
        Set(MapVar(6), LVar0)
        BindTrigger(TTYD64_mac_07_Script_Shop2_Item3, 256, 22, 1, 0)
    Else
        Call(ModifyColliderFlags, 0, 22, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4474), 0)
        Call(MakeItemEntity, 368, 530, 0, 104, 1, GameFlag(4474))
        Set(MapVar(7), LVar0)
        BindTrigger(TTYD64_mac_07_Script_Shop3_Item1, 256, 24, 1, 0)
    Else
        Call(ModifyColliderFlags, 0, 24, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4475), 0)
        Call(MakeItemEntity, 141, 561, 0, 113, 1, GameFlag(4475))
        Set(MapVar(8), LVar0)
        BindTrigger(TTYD64_mac_07_Script_Shop3_Item2, 256, 25, 1, 0)
    Else
        Call(ModifyColliderFlags, 0, 25, 0x7FFFFE00)
    EndIf
    IfEq(GameFlag(4476), 0)
        Call(MakeItemEntity, 348, 592, 0, 121, 1, GameFlag(4476))
        Set(MapVar(9), LVar0)
        BindTrigger(TTYD64_mac_07_Script_Shop3_Item3, 256, 26, 1, 0)
    Else
        Call(ModifyColliderFlags, 0, 26, 0x7FFFFE00)
    EndIf
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Main = {
    Set(GameByte(425), 1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_mac_07_NpcGroupList_mac07)
    Exec(TTYD64_mac_07_Script_MakeEntities)
    Exec(TTYD64_mac_07_Script_SetupMusic)
    Exec(TTYD64_mac_07_Script_EnterMap)
    Set(LVar0, (Bytecode) TTYD64_mac_07_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

u8 TTYD64_mac_07_String_ToadKid5[] = {
    0xFC, 0x01, 0x28, 0x45, 0x4C, 0x4C, 0x4F, 0xF7, 0x2D, 0x41, 0x52, 0x49,
    0x4F, 0x0C, 0xF7, 0x4D, 0x45, 0xF7, 0x41, 0x4E, 0x44, 0xF7, 0x4D, 0x59,
    0xF7, 0x42, 0x52, 0x4F, 0x54, 0x48, 0x45, 0x52, 0xF0, 0x41, 0x52, 0x45,
    0xF7, 0x57, 0x41, 0x49, 0x54, 0x49, 0x4E, 0x47, 0xF7, 0x46, 0x4F, 0x52,
    0xF7, 0x4F, 0x55, 0x52, 0xF7, 0x46, 0x41, 0x54, 0x48, 0x45, 0x52, 0xF7,
    0x54, 0x4F, 0xF0, 0x43, 0x4F, 0x4D, 0x45, 0xF7, 0x48, 0x4F, 0x4D, 0x45,
    0xF7, 0x46, 0x52, 0x4F, 0x4D, 0xF7, 0x57, 0x4F, 0x52, 0x4B, 0x0E, 0xF0,
    0xF1, 0xFB, 0x28, 0x45, 0xF7, 0x4A, 0x55, 0x53, 0x54, 0xF7, 0x42, 0x4F,
    0x55, 0x47, 0x48, 0xF7, 0x55, 0x53, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x4E,
    0x45, 0x57, 0xF7, 0x53, 0x45, 0x51, 0x55, 0x45, 0x4C, 0xF0, 0x4F, 0x46,
    0xF7, 0x4F, 0x55, 0x52, 0xF7, 0x46, 0x41, 0x56, 0x4F, 0x52, 0x49, 0x54,
    0x45, 0xF7, 0x47, 0x41, 0x4D, 0x45, 0xF7, 0x33, 0x55, 0x50, 0x45, 0x52,
    0xF7, 0x2A, 0x52, 0x0E, 0xF0, 0x2B, 0x4F, 0x4F, 0x50, 0x41, 0xF7, 0x22,
    0x52, 0x4F, 0x53, 0x0C, 0xF7, 0x57, 0x45, 0xF7, 0x43, 0x41, 0x4E, 0x07,
    0x54, 0xF7, 0x57, 0x41, 0x49, 0x54, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_mac_07_Script_SetupMusic = {
    Switch(GameByte(0))
    CaseRange(-13, 5)
        Call(SetMusic, 0, 74, 0, 6)
    CaseDefault
        Call(SetMusic, 0, 0, 0, 6)
    EndSwitch
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Shop1_Item3 = {
    Set(LVar0, 162)
    Set(LVar1, 120)
    Set(LVar2, 1)
    Set(LVar3, 0x830004)
    Set(LVar4, 0x830001)
    Set(LVar5, 3)
    ExecWait(TTYD64_mac_07_Script_BuyItem)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Shop1_Item1 = {
    Set(LVar0, 369)
    Set(LVar1, 180)
    Set(LVar2, 1)
    Set(LVar3, 0x830004)
    Set(LVar4, 0x830001)
    Set(LVar5, 1)
    ExecWait(TTYD64_mac_07_Script_BuyItem)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Shop1_Item2 = {
    Set(LVar0, 131)
    Set(LVar1, 36)
    Set(LVar2, 1)
    Set(LVar3, 0x830004)
    Set(LVar4, 0x830001)
    Set(LVar5, 2)
    ExecWait(TTYD64_mac_07_Script_BuyItem)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Shop2_Item2 = {
    Set(LVar0, 301)
    Set(LVar1, 120)
    Set(LVar2, 2)
    Set(LVar3, 0x830004)
    Set(LVar4, 0x830001)
    Set(LVar5, 5)
    ExecWait(TTYD64_mac_07_Script_BuyItem)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Shop2_Item3 = {
    Set(LVar0, 142)
    Set(LVar1, 120)
    Set(LVar2, 2)
    Set(LVar3, 0x830004)
    Set(LVar4, 0x830001)
    Set(LVar5, 6)
    ExecWait(TTYD64_mac_07_Script_BuyItem)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Shop2_Item1 = {
    Set(LVar0, 146)
    Set(LVar1, 24)
    Set(LVar2, 2)
    Set(LVar3, 0x830004)
    Set(LVar4, 0x830001)
    Set(LVar5, 4)
    ExecWait(TTYD64_mac_07_Script_BuyItem)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Shop3_Item3 = {
    Set(LVar0, 348)
    Set(LVar1, 20)
    Set(LVar2, 3)
    Set(LVar3, 0x830004)
    Set(LVar4, 0x830001)
    Set(LVar5, 9)
    ExecWait(TTYD64_mac_07_Script_BuyItem)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Shop3_Item1 = {
    Set(LVar0, 368)
    Set(LVar1, 180)
    Set(LVar2, 3)
    Set(LVar3, 0x830004)
    Set(LVar4, 0x830001)
    Set(LVar5, 7)
    ExecWait(TTYD64_mac_07_Script_BuyItem)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Shop3_Item2 = {
    Set(LVar0, 141)
    Set(LVar1, 20)
    Set(LVar2, 3)
    Set(LVar3, 0x830004)
    Set(LVar4, 0x830001)
    Set(LVar5, 8)
    ExecWait(TTYD64_mac_07_Script_BuyItem)
    Return
    End
};

u8 TTYD64_mac_07_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x34, 0x48, 0x49, 0x53, 0xF7, 0x41, 0x52, 0x45,
    0x41, 0xF7, 0x49, 0x53, 0xF7, 0x46, 0x55, 0x4C, 0x4C, 0xF7, 0x4F, 0x46,
    0xF7, 0x4C, 0x4F, 0x43, 0x41, 0x4C, 0xF7, 0x56, 0x45, 0x4E, 0x44, 0x4F,
    0x52, 0x53, 0x0C, 0xF0, 0x57, 0x45, 0xF7, 0x53, 0x48, 0x4F, 0x55, 0x4C,
    0x44, 0xF7, 0x53, 0x45, 0x45, 0xF7, 0x57, 0x48, 0x41, 0x54, 0xF7, 0x54,
    0x48, 0x45, 0x59, 0xF7, 0x53, 0x45, 0x4C, 0x4C, 0x0C, 0xF0, 0x4D, 0x41,
    0x59, 0x42, 0x45, 0xF7, 0xF7, 0x54, 0x48, 0x45, 0x52, 0x45, 0xF7, 0x41,
    0x52, 0x45, 0xF7, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x45, 0x53, 0x54, 0x49,
    0x4E, 0x47, 0xF0, 0x54, 0x48, 0x49, 0x4E, 0x47, 0x53, 0xF7, 0x2D, 0x41,
    0x52, 0x49, 0x4F, 0x0E, 0xF1, 0xFD
};

u8 TTYD64_mac_07_Tattle_ToadKid[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x21, 0xF7, 0x4B, 0x49, 0x44, 0xF7, 0x46, 0x52,
    0x4F, 0x4D, 0xF7, 0x34, 0x4F, 0x41, 0x44, 0xF7, 0x34, 0x4F, 0x57, 0x4E,
    0x0C, 0xF7, 0x57, 0x4F, 0x57, 0x0C, 0xF7, 0x54, 0x48, 0x45, 0x52, 0x45,
    0xF0, 0x41, 0x52, 0x45, 0xF7, 0x41, 0xF7, 0x4C, 0x4F, 0x54, 0xF7, 0x4F,
    0x46, 0xF7, 0x43, 0x48, 0x49, 0x4C, 0x44, 0x52, 0x45, 0x4E, 0xF7, 0x49,
    0x4E, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7, 0x54, 0x4F, 0x57, 0x4E, 0x0C,
    0xF0, 0x29, 0xF7, 0x57, 0x49, 0x53, 0x48, 0xF7, 0x49, 0x54, 0xF7, 0x57,
    0x41, 0x53, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x53, 0x41, 0x4D, 0x45, 0xF7,
    0x49, 0x4E, 0xF7, 0x27, 0x4F, 0x4F, 0x4D, 0x42, 0x41, 0xF0, 0x36, 0x49,
    0x4C, 0x4C, 0x41, 0x47, 0x45, 0x0E, 0xF1, 0xFD
};

u8 TTYD64_mac_07_String_Shopkeeper2_Hi[] = {
    0xFC, 0x01, 0x28, 0x49, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C, 0xF7,
    0x4D, 0x45, 0xF7, 0x41, 0x4E, 0x44, 0xF7, 0x4D, 0x59, 0xF7, 0x53, 0x4F,
    0x4E, 0xF7, 0x41, 0x52, 0x45, 0xF0, 0x53, 0x45, 0x4C, 0x4C, 0x49, 0x4E,
    0x47, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0xF7, 0x53, 0x54, 0x55, 0x46, 0x46,
    0xF7, 0x54, 0x4F, 0xF7, 0x47, 0x45, 0x54, 0xF7, 0x41, 0xF0, 0x4C, 0x49,
    0x54, 0x54, 0x4C, 0x45, 0xF7, 0x45, 0x58, 0x54, 0x52, 0x41, 0xF7, 0x4D,
    0x4F, 0x4E, 0x45, 0x59, 0x0C, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF7,
    0x46, 0x4F, 0x52, 0x47, 0x45, 0x54, 0xF0, 0x54, 0x4F, 0xF7, 0x42, 0x55,
    0x59, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0x54, 0x48, 0x49, 0x4E, 0x47, 0x0E,
    0xF1, 0xFD
};

u8 TTYD64_mac_07_String_ToadTalking2[] = {
    0xFC, 0x01, 0x34, 0x48, 0x45, 0xF7, 0x4C, 0x41, 0x53, 0x54, 0xF7, 0x54,
    0x48, 0x49, 0x4E, 0x47, 0xF7, 0x29, 0xF7, 0x57, 0x41, 0x54, 0x43, 0x48,
    0x45, 0x44, 0xF7, 0x57, 0x41, 0x53, 0xF0, 0x54, 0x48, 0x45, 0xF7, 0x43,
    0x48, 0x41, 0x50, 0x54, 0x45, 0x52, 0xF7, 0x57, 0x48, 0x45, 0x4E, 0xF7,
    0x48, 0x45, 0xF7, 0x47, 0x45, 0x54, 0x53, 0xF7, 0x54, 0x48, 0x45, 0xF0,
    0x50, 0x49, 0x43, 0x4B, 0x41, 0x58, 0x45, 0xF7, 0x46, 0x4F, 0x52, 0xF7,
    0x54, 0x48, 0x45, 0xF7, 0x46, 0x49, 0x52, 0x53, 0x54, 0xF7, 0x54, 0x49,
    0x4D, 0x45, 0x0C, 0xF0, 0x49, 0x54, 0xF7, 0x57, 0x41, 0x53, 0xF7, 0x52,
    0x45, 0x41, 0x4C, 0x4C, 0x59, 0xF7, 0x47, 0x4F, 0x4F, 0x44, 0x0E, 0xF1,
    0xFD
};

u8 TTYD64_mac_07_String_ToadKid6[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C,
    0xF7, 0x48, 0x41, 0x56, 0x45, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x50, 0x4C,
    0x41, 0x59, 0x45, 0x44, 0xF7, 0x54, 0x48, 0x45, 0xF0, 0x33, 0x55, 0x50,
    0x45, 0x52, 0xF7, 0x2A, 0x52, 0x0E, 0xF7, 0x2B, 0x4F, 0x4F, 0x50, 0x41,
    0xF7, 0x22, 0x52, 0x4F, 0x53, 0xF7, 0x47, 0x41, 0x4D, 0x45, 0xF7, 0x59,
    0x45, 0x54, 0x1F, 0xF0, 0xF1, 0xFB, 0x29, 0x54, 0x07, 0x53, 0xF7, 0x56,
    0x45, 0x52, 0x59, 0xF7, 0x47, 0x4F, 0x4F, 0x44, 0x0C, 0xF7, 0x59, 0x4F,
    0x55, 0xF7, 0x53, 0x48, 0x4F, 0x55, 0x4C, 0x44, 0xF7, 0x43, 0x48, 0x45,
    0x43, 0x4B, 0xF0, 0x49, 0x54, 0xF7, 0x4F, 0x55, 0x54, 0x0E, 0xF1, 0xFD
};

u8 TTYD64_mac_07_String_ToadTalking1[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0x0C, 0xF7, 0x48, 0x41, 0x56, 0x45, 0xF7,
    0x59, 0x4F, 0x55, 0xF7, 0x41, 0x4C, 0x52, 0x45, 0x41, 0x44, 0x59, 0xF7,
    0x57, 0x41, 0x54, 0x43, 0x48, 0x45, 0x44, 0xF0, 0x54, 0x48, 0x45, 0xF7,
    0x4E, 0x45, 0x57, 0xF7, 0x45, 0x50, 0x49, 0x53, 0x4F, 0x44, 0x45, 0xF7,
    0x4F, 0x46, 0xF7, 0x33, 0x55, 0x50, 0x45, 0x52, 0xF7, 0x23, 0x41, 0x50,
    0x54, 0x41, 0x49, 0x4E, 0xF0, 0x34, 0x4F, 0x41, 0x44, 0x1F, 0xF0, 0xF1,
    0xFB, 0x29, 0xF7, 0x48, 0x45, 0x41, 0x52, 0x44, 0xF7, 0x49, 0x54, 0xF7,
    0x57, 0x41, 0x53, 0xF7, 0x4C, 0x49, 0x4B, 0x45, 0xF7, 0x4D, 0x4F, 0x56,
    0x49, 0x45, 0x01, 0xF1, 0xFD
};

u8 TTYD64_mac_07_Tattle_Toad[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x21, 0xF7, 0x43, 0x49, 0x54, 0x49, 0x5A, 0x45,
    0x4E, 0xF7, 0x4F, 0x46, 0xF7, 0x34, 0x4F, 0x41, 0x44, 0xF7, 0x34, 0x4F,
    0x57, 0x4E, 0x0C, 0xF7, 0x56, 0x45, 0x52, 0x59, 0xF7, 0x4E, 0x49, 0x43,
    0x45, 0xF0, 0x43, 0x49, 0x54, 0x59, 0x0C, 0xF7, 0x42, 0x55, 0x54, 0xF7,
    0x29, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x4B, 0x4E, 0x4F, 0x57,
    0x0C, 0xF7, 0x29, 0xF7, 0x50, 0x52, 0x45, 0x46, 0x45, 0x52, 0xF0, 0x27,
    0x4F, 0x4F, 0x4D, 0x42, 0x41, 0xF7, 0x36, 0x49, 0x4C, 0x4C, 0x41, 0x47,
    0x45, 0xF7, 0x57, 0x41, 0x59, 0xF7, 0x4D, 0x4F, 0x52, 0x45, 0x0E, 0xF1,
    0xFD
};

EvtScript TTYD64_mac_07_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SuperBlock), -737, 56, -118, 0, 0x80000000)
    Set(MapVar(10), LVar0)
    Call(AssignBlockFlag, GameFlag(4477))
    Call(AssignScript, (Bytecode) TTYD64_mac_07_Script_Entity_Shine1)
    Return
    End
};

u8 TTYD64_mac_07_String_ShopKeeper_Welcome[] = {
    0xFC, 0x01, 0x34, 0x48, 0x41, 0x54, 0xF7, 0x49, 0x54, 0x45, 0x4D, 0xF7,
    0x48, 0x41, 0x53, 0xF7, 0x41, 0xF7, 0x43, 0x4F, 0x53, 0x54, 0xF7, 0x4F,
    0x46, 0xF7, 0xFF, 0x24, 0xFF, 0x05, 0x19, 0xFF, 0x28, 0x00, 0xFF, 0x25,
    0xF0, 0x43, 0x4F, 0x49, 0x4E, 0x53, 0x0C, 0xF7, 0x57, 0x4F, 0x55, 0x4C,
    0x44, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x42, 0x45, 0xF7, 0x49, 0x4E, 0x54,
    0x45, 0x52, 0x45, 0x53, 0x54, 0x45, 0x44, 0xF7, 0x49, 0x4E, 0xF0, 0x42,
    0x55, 0x59, 0x49, 0x4E, 0x47, 0xF7, 0x49, 0x54, 0x1F, 0xF0, 0xFF, 0x04,
    0xFD
};

u8 TTYD64_mac_07_String_ShopKeeper_NotEnoughMoney[] = {
    0xFB, 0x29, 0x54, 0xF7, 0x53, 0x45, 0x45, 0x4D, 0x53, 0xF7, 0x59, 0x4F,
    0x55, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x48, 0x41, 0x56, 0x45,
    0xF7, 0x45, 0x4E, 0x4F, 0x55, 0x47, 0x48, 0xF0, 0x4D, 0x4F, 0x4E, 0x45,
    0x59, 0x0C, 0xF7, 0x43, 0x4F, 0x4D, 0x45, 0xF7, 0x42, 0x41, 0x43, 0x4B,
    0xF7, 0x57, 0x48, 0x45, 0x4E, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x48, 0x41,
    0x56, 0x45, 0xF7, 0x41, 0xF0, 0x4C, 0x49, 0x54, 0x54, 0x4C, 0x45, 0xF7,
    0x4D, 0x4F, 0x52, 0x45, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0E, 0xF1,
    0xFD
};

u8 TTYD64_mac_07_String_ToadKid4[] = {
    0xFC, 0x01, 0x28, 0x49, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C, 0xF7,
    0x48, 0x45, 0x59, 0x0C, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x59,
    0x4F, 0x55, 0xF7, 0x4E, 0x45, 0x45, 0x44, 0xF7, 0x41, 0xF0, 0x4E, 0x45,
    0x57, 0xF7, 0x41, 0x44, 0x56, 0x45, 0x4E, 0x54, 0x55, 0x52, 0x45, 0xF7,
    0x50, 0x41, 0x52, 0x54, 0x4E, 0x45, 0x52, 0x1F, 0xF0, 0x29, 0x07, 0x4D,
    0xF7, 0x44, 0x59, 0x49, 0x4E, 0x47, 0xF7, 0x46, 0x4F, 0x52, 0xF7, 0x53,
    0x4F, 0x4D, 0x45, 0xF7, 0x46, 0x55, 0x4E, 0x01, 0xF1, 0xFD
};

u8 TTYD64_mac_07_String_Shopkeeper1_Hi[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C,
    0xF7, 0x29, 0xF7, 0x48, 0x41, 0x56, 0x45, 0xF7, 0x41, 0xF7, 0x42, 0x49,
    0x54, 0xF7, 0x4F, 0x46, 0xF0, 0x45, 0x56, 0x45, 0x52, 0x59, 0x54, 0x48,
    0x49, 0x4E, 0x47, 0x0C, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x46,
    0x4F, 0x52, 0x47, 0x45, 0x54, 0xF7, 0x54, 0x4F, 0xF0, 0x43, 0x48, 0x45,
    0x43, 0x4B, 0xF7, 0x57, 0x48, 0x45, 0x4E, 0xF7, 0x59, 0x4F, 0x55, 0xF7,
    0x43, 0x41, 0x4E, 0x0E, 0xF1, 0xFD
};

EvtScript TTYD64_mac_07_Script_Exit0 = {
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "mac_04", 6)
    Wait(100)
    Return
    End
};

u8 TTYD64_mac_07_String_Toad2[] = {
    0xFC, 0x01, 0x33, 0x41, 0x4C, 0x45, 0x53, 0xF7, 0x48, 0x41, 0x56, 0x45,
    0xF7, 0x42, 0x45, 0x45, 0x4E, 0xF7, 0x51, 0x55, 0x49, 0x54, 0x45, 0xF7,
    0x43, 0x41, 0x4C, 0x4D, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF0, 0x4C, 0x41,
    0x53, 0x54, 0xF7, 0x57, 0x45, 0x45, 0x4B, 0x0C, 0xF7, 0x29, 0xF7, 0x48,
    0x4F, 0x50, 0x45, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x53, 0x49, 0x54, 0x55,
    0x41, 0x54, 0x49, 0x4F, 0x4E, 0xF0, 0x49, 0x4D, 0x50, 0x52, 0x4F, 0x56,
    0x45, 0x53, 0x0E, 0xF1, 0xFD
};

u8 TTYD64_mac_07_String_ToadKid3[] = {
    0xFC, 0x01, 0x29, 0xF7, 0x43, 0x41, 0x4E, 0x07, 0x54, 0xF7, 0x57, 0x41,
    0x49, 0x54, 0xF7, 0x46, 0x4F, 0x52, 0xF7, 0x4D, 0x59, 0xF7, 0x4D, 0x4F,
    0x4D, 0xF7, 0x54, 0x4F, 0xF7, 0x46, 0x49, 0x4E, 0x49, 0x53, 0x48, 0xF0,
    0x43, 0x4F, 0x4F, 0x4B, 0x49, 0x4E, 0x47, 0xF7, 0x54, 0x4F, 0x44, 0x41,
    0x59, 0x07, 0x53, 0xF7, 0x44, 0x49, 0x4E, 0x4E, 0x45, 0x52, 0x0C, 0xF7,
    0x29, 0x07, 0x4D, 0xF0, 0x53, 0x54, 0x41, 0x52, 0x56, 0x49, 0x4E, 0x47,
    0x01, 0xF1, 0xFD
};

u8 TTYD64_mac_07_String_ToadKid2[] = {
    0xFC, 0x01, 0x29, 0x54, 0x07, 0x53, 0xF7, 0x42, 0x45, 0x45, 0x4E, 0xF7,
    0x50, 0x52, 0x45, 0x54, 0x54, 0x59, 0xF7, 0x51, 0x55, 0x49, 0x45, 0x54,
    0xF7, 0x54, 0x4F, 0x44, 0x41, 0x59, 0x0C, 0xF0, 0x29, 0xF7, 0x48, 0x4F,
    0x50, 0x45, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0x54, 0x48, 0x49, 0x4E, 0x47,
    0xF7, 0x46, 0x55, 0x4E, 0x4E, 0x59, 0xF7, 0x48, 0x41, 0x50, 0x50, 0x45,
    0x4E, 0x53, 0xF0, 0x53, 0x4F, 0x4F, 0x4E, 0xF7, 0xF1, 0xFD
};

u8 TTYD64_mac_07_Tattle_Shopkeeper[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x21, 0xF7, 0x4C, 0x4F, 0x43, 0x41, 0x4C, 0xF7,
    0x53, 0x45, 0x4C, 0x4C, 0x45, 0x52, 0x0C, 0xF7, 0x41, 0x4C, 0x57, 0x41,
    0x59, 0x53, 0xF7, 0x52, 0x45, 0x4D, 0x45, 0x4D, 0x42, 0x45, 0x52, 0xF0,
    0x54, 0x4F, 0xF7, 0x48, 0x45, 0x4C, 0x50, 0xF7, 0x4C, 0x4F, 0x43, 0x41,
    0x4C, 0xF7, 0x42, 0x55, 0x53, 0x49, 0x4E, 0x45, 0x53, 0x53, 0x45, 0x53,
    0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0E, 0xF1, 0xFD
};

MapSettings TTYD64_mac_07_Header = {
    .main = &TTYD64_mac_07_Script_Main,
    .entryList = &TTYD64_mac_07_EntryList,
    .entryCount = 1,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_mac_07_GetTattle },
};

u8 TTYD64_mac_07_Tattle_DarkToad[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x28, 0x4D, 0x4D, 0xF7, 0x54, 0x48, 0x49, 0x53,
    0xF7, 0x54, 0x4F, 0x41, 0x44, 0xF7, 0x4C, 0x4F, 0x4F, 0x4B, 0x53, 0xF7,
    0x56, 0x45, 0x52, 0x59, 0xF0, 0x53, 0x55, 0x53, 0x50, 0x49, 0x43, 0x49,
    0x4F, 0x55, 0x53, 0x0C, 0xF7, 0x29, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54,
    0xF7, 0x4B, 0x4E, 0x4F, 0x57, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0E,
    0xF1, 0xFD
};

EvtScript TTYD64_mac_07_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(10))
    SetConst(LVar1, GameFlag(4477))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Init_ToadTalking2 = {
    Call(SetNpcFlagBits, -1, 0x40000, 1)
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_mac_07_Script_Interact_ToadTalking2)
    Return
    End
};

u8 TTYD64_mac_07_String_ToadKid1[] = {
    0xFC, 0x01, 0x28, 0x45, 0x4C, 0x4C, 0x4F, 0xF7, 0x2D, 0x41, 0x52, 0x49,
    0x4F, 0x0C, 0xF7, 0x48, 0x45, 0x59, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54,
    0xF7, 0x46, 0x4F, 0x52, 0x47, 0x45, 0x54, 0xF7, 0x54, 0x4F, 0xF0, 0x42,
    0x55, 0x59, 0xF7, 0x55, 0x53, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0x54, 0x48,
    0x49, 0x4E, 0x47, 0x01, 0xF1, 0xFD
};

u8 TTYD64_mac_07_String_Toad1[] = {
    0xFC, 0x01, 0x29, 0xF7, 0x4C, 0x4F, 0x56, 0x45, 0xF7, 0x54, 0x48, 0x45,
    0xF7, 0x57, 0x45, 0x41, 0x54, 0x48, 0x45, 0x52, 0xF7, 0x4F, 0x46, 0xF7,
    0x54, 0x48, 0x45, 0xF7, 0x44, 0x41, 0x59, 0x0C, 0xF0, 0x44, 0x4F, 0xF7,
    0x59, 0x4F, 0x55, 0xF7, 0x54, 0x4F, 0x4F, 0xF7, 0x2D, 0x41, 0x52, 0x49,
    0x4F, 0x1F, 0xF1, 0xFD
};

EvtScript TTYD64_mac_07_Script_Interact_Toad2 = {
    Call(SpeakToPlayer, -1, 0x830304, 0x830301, 0, (Bytecode) TTYD64_mac_07_String_Toad2)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Interact_Toad1 = {
    Call(SpeakToPlayer, -1, 0x830004, 0x830001, 0, (Bytecode) TTYD64_mac_07_String_Toad1)
    Return
    End
};

u8 TTYD64_mac_07_String_ShopKeeper_ThankYou[] = {
    0xFC, 0x01, 0x34, 0x48, 0x41, 0x4E, 0x4B, 0xF7, 0x59, 0x4F, 0x55, 0xF7,
    0x56, 0x45, 0x52, 0x59, 0xF7, 0x4D, 0x55, 0x43, 0x48, 0xF7, 0x2D, 0x41,
    0x52, 0x49, 0x4F, 0x0C, 0xF0, 0x48, 0x41, 0x56, 0x45, 0xF7, 0x41, 0xF7,
    0x4E, 0x49, 0x43, 0x45, 0xF7, 0x44, 0x41, 0x59, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_mac_07_Script_Interact_Shopkeeper1 = {
    Call(SpeakToPlayer, -1, 0x830004, 0x830001, 0, (Bytecode) TTYD64_mac_07_String_Shopkeeper1_Hi)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Interact_Shopkeeper2 = {
    Call(SpeakToPlayer, -1, 0x830104, 0x830101, 0, (Bytecode) TTYD64_mac_07_String_Shopkeeper2_Hi)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Interact_Shopkeeper3 = {
    Call(SpeakToPlayer, -1, 0x830204, 0x830201, 0, (Bytecode) TTYD64_mac_07_String_Shopkeeper3_Hi)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Interact_DarkToad = {
    Call(SpeakToPlayer, -1, 0x650004, 0x650001, 0, (Bytecode) TTYD64_mac_07_String_DarkToad1_Hi)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Interact_ToadKid2 = {
    Call(SpeakToPlayer, -1, 0x860304, 0x860301, 0, (Bytecode) TTYD64_mac_07_String_ToadKid2)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Interact_ToadKid1 = {
    Call(SpeakToPlayer, -1, 0x830304, 0x830301, 0, (Bytecode) TTYD64_mac_07_String_ToadKid1)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Interact_ToadTalking2 = {
    Call(SpeakToPlayer, -1, 0x830004, 0x830001, 0, (Bytecode) TTYD64_mac_07_String_ToadTalking2)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Interact_ToadTalking1 = {
    Call(SpeakToPlayer, -1, 0x830004, 0x830001, 0, (Bytecode) TTYD64_mac_07_String_ToadTalking1)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Interact_ToadKid6 = {
    Call(SpeakToPlayer, -1, 0x860304, 0x860301, 0, (Bytecode) TTYD64_mac_07_String_ToadKid6)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Interact_ToadKid5 = {
    Call(SpeakToPlayer, -1, 0x860304, 0x860301, 0, (Bytecode) TTYD64_mac_07_String_ToadKid5)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Interact_ToadKid4 = {
    Call(SpeakToPlayer, -1, 0x860204, 0x860201, 0, (Bytecode) TTYD64_mac_07_String_ToadKid4)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Interact_ToadKid3 = {
    Call(SpeakToPlayer, -1, 0x860004, 0x860001, 0, (Bytecode) TTYD64_mac_07_String_ToadKid3)
    Return
    End
};

NpcSettings TTYD64_mac_07_NpcSettings_Toad = {
    .defaultAnim = 0x00000000,
    .height = 30,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = NULL,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 99,
    .actionFlags = 0,
};

EvtScript TTYD64_mac_07_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_mac_07_Script_Exit0, 0x80000, 2, 1, 0)
    Return
    End
};

u8 TTYD64_mac_07_String_Shopkeeper3_Hi[] = {
    0xFC, 0x01, 0x28, 0x45, 0x4C, 0x4C, 0x4F, 0xF7, 0x2D, 0x41, 0x52, 0x49,
    0x4F, 0x0C, 0xF7, 0x54, 0x48, 0x41, 0x4E, 0x4B, 0x53, 0xF7, 0x46, 0x4F,
    0x52, 0xF0, 0x56, 0x49, 0x53, 0x49, 0x54, 0x49, 0x4E, 0x47, 0xF7, 0x55,
    0x53, 0x0E, 0xF1, 0xFD
};

EvtScript TTYD64_mac_07_Script_Init_Toad2 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_mac_07_Script_Interact_Toad2)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Init_Toad1 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_mac_07_Script_Interact_Toad1)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Init_Shopkeeper3 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_mac_07_Script_Interact_Shopkeeper3)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Init_Shopkeeper2 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_mac_07_Script_Interact_Shopkeeper2)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Init_Shopkeeper1 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_mac_07_Script_Interact_Shopkeeper1)
    Return
    End
};

u8 TTYD64_mac_07_String_DarkToad1_Hi[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0x0C, 0xF7, 0x43, 0x41, 0x4E, 0x07, 0x54,
    0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x53, 0x45, 0x45, 0xF7, 0x29, 0x07, 0x4D,
    0xF7, 0x42, 0x55, 0x53, 0x59, 0x1F, 0x01, 0xF1, 0xFD
};

NpcGroupList TTYD64_mac_07_NpcGroupList_mac07 = {
    { .npcCount = 3, .npcs = TTYD64_mac_07_NpcGroup_Shopkeepers, .battle = 0x0000, .stage = 0 },
    { .npcCount = 11, .npcs = TTYD64_mac_07_NpcGroup_NPCs, .battle = 0x0000, .stage = 0 },
    {},
};

EvtScript TTYD64_mac_07_Script_Init_DarkToad = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_mac_07_Script_Interact_DarkToad)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Init_ToadKid2 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_mac_07_Script_Interact_ToadKid2)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Init_ToadKid1 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_mac_07_Script_Interact_ToadKid1)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Init_ToadKid4 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_mac_07_Script_Interact_ToadKid4)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Init_ToadKid3 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_mac_07_Script_Interact_ToadKid3)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Init_ToadKid6 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_mac_07_Script_Interact_ToadKid6)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Init_ToadKid5 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_mac_07_Script_Interact_ToadKid5)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_Init_ToadTalking1 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_mac_07_Script_Interact_ToadTalking1)
    Return
    End
};

EvtScript TTYD64_mac_07_Script_EnterMap = {
    Exec(TTYD64_mac_07_Script_InitShops)
    Return
    End
};

EntryList TTYD64_mac_07_EntryList = {
    { -292.0f, 12.0f, 181.0f, 0.0f },
};

MapConfig TTYD64_mapcfg_mac_07 = {
    .id = "mac_07",
    .settings = &TTYD64_mac_07_Header,
    .bgName = "nok_bg",
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_mac_07(void) {
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_BuyItem, TTYD64_mac_07_String_ShopKeeper_Welcome);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_BuyItem, TTYD64_mac_07_String_ShopKeeper_NotEnoughMoney);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_BuyItem, TTYD64_mac_07_String_ShopKeeper_ThankYou);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_Interact_Toad2, TTYD64_mac_07_String_Toad2);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_Interact_Toad1, TTYD64_mac_07_String_Toad1);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_Interact_Shopkeeper1, TTYD64_mac_07_String_Shopkeeper1_Hi);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_Interact_Shopkeeper2, TTYD64_mac_07_String_Shopkeeper2_Hi);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_Interact_Shopkeeper3, TTYD64_mac_07_String_Shopkeeper3_Hi);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_Interact_DarkToad, TTYD64_mac_07_String_DarkToad1_Hi);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_Interact_ToadKid2, TTYD64_mac_07_String_ToadKid2);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_Interact_ToadKid1, TTYD64_mac_07_String_ToadKid1);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_Interact_ToadTalking2, TTYD64_mac_07_String_ToadTalking2);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_Interact_ToadTalking1, TTYD64_mac_07_String_ToadTalking1);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_Interact_ToadKid6, TTYD64_mac_07_String_ToadKid6);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_Interact_ToadKid5, TTYD64_mac_07_String_ToadKid5);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_Interact_ToadKid4, TTYD64_mac_07_String_ToadKid4);
    TTYD64_nm_BindMessage(TTYD64_mac_07_Script_Interact_ToadKid3, TTYD64_mac_07_String_ToadKid3);
    TTYD64_mac_07_NpcGroup_NPCs[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_07_Tattle_DarkToad);
    TTYD64_mac_07_NpcGroup_NPCs[1].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_07_Tattle_Toad);
    TTYD64_mac_07_NpcGroup_NPCs[2].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_07_Tattle_Toad);
    TTYD64_mac_07_NpcGroup_NPCs[3].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_07_Tattle_Toad);
    TTYD64_mac_07_NpcGroup_NPCs[4].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_07_Tattle_Toad);
    TTYD64_mac_07_NpcGroup_NPCs[5].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_07_Tattle_ToadKid);
    TTYD64_mac_07_NpcGroup_NPCs[6].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_07_Tattle_ToadKid);
    TTYD64_mac_07_NpcGroup_NPCs[7].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_07_Tattle_ToadKid);
    TTYD64_mac_07_NpcGroup_NPCs[8].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_07_Tattle_ToadKid);
    TTYD64_mac_07_NpcGroup_NPCs[9].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_07_Tattle_ToadKid);
    TTYD64_mac_07_NpcGroup_NPCs[10].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_07_Tattle_ToadKid);
    TTYD64_mac_07_NpcGroup_Shopkeepers[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_07_Tattle_Shopkeeper);
    TTYD64_mac_07_NpcGroup_Shopkeepers[1].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_07_Tattle_Shopkeeper);
    TTYD64_mac_07_NpcGroup_Shopkeepers[2].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_07_Tattle_Shopkeeper);
    TTYD64_mac_07_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_mac_07_String_Tattle);
}
