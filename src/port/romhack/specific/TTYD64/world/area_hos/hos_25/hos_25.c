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
API_CALLABLE(BindNpcInteract);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(NpcJump0);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetItemPos);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcJumpscale);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetTexPanner);
API_CALLABLE(ShowMessageAtScreenPos);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(UseExitHeading);

extern NpcData TTYD64_hos_25_NpcGroup_NPCs[];
extern EvtScript TTYD64_hos_25_Script_DropMoney;
extern EvtScript TTYD64_hos_25_Script_SetupTexturePan;
extern NpcData TTYD64_hos_25_NpcGroup_Coin[];
extern EvtScript TTYD64_hos_25_Script_UpdateCoinPos;
extern EvtScript TTYD64_hos_25_Script_Main;
extern u8 TTYD64_hos_25_String_Couple0_1[];
extern EvtScript TTYD64_hos_25_Script_EnterMap;
extern u8 TTYD64_hos_25_String_Couple4_2_1[];
extern u8 TTYD64_hos_25_Tattle_Couple[];
extern EvtScript TTYD64_hos_25_Script_TexturePan_Update;
extern u8 TTYD64_hos_25_Tattle_Solo[];
extern u8 TTYD64_hos_25_String_Tattle[];
extern u8 TTYD64_hos_25_String_Couple4_1_1[];
extern EvtScript TTYD64_hos_25_Script_InitNPC_Coin;
extern EvtScript TTYD64_hos_25_Script_Exit0;
extern u8 TTYD64_hos_25_String_Couple1_2_1[];
extern u8 TTYD64_hos_25_String_Couple1_1_1[];
extern MapSettings TTYD64_hos_25_Header;
extern u8 TTYD64_hos_25_String_Couple3_1_1[];
extern EvtScript TTYD64_hos_25_Script_SetupMusic;
extern EvtScript TTYD64_hos_25_Script_Interact_Couple3_1;
extern EvtScript TTYD64_hos_25_Script_Interact_Couple4_1;
extern EvtScript TTYD64_hos_25_Script_Interact_Couple4_2;
extern EvtScript TTYD64_hos_25_Script_Interact_Couple0;
extern EvtScript TTYD64_hos_25_Script_Interact_Couple1_2;
extern EvtScript TTYD64_hos_25_Script_Interact_Couple2_1;
extern EvtScript TTYD64_hos_25_Script_Interact_Couple1_1;
extern u8 TTYD64_hos_25_String_EnoughCoins[];
extern NpcSettings TTYD64_hos_25_NpcSettings_Generic;
extern EvtScript TTYD64_hos_25_Script_CreateExitTriggers;
extern u8 TTYD64_hos_25_String_Couple2_1_1[];
extern NpcGroupList TTYD64_hos_25_NpcGroupList_hos25;
extern EvtScript TTYD64_hos_25_Script_InitNPC_Couple0;
extern EvtScript TTYD64_hos_25_Script_InitNPC_Couple1_1;
extern EvtScript TTYD64_hos_25_Script_InitNPC_Couple1_2;
extern EvtScript TTYD64_hos_25_Script_InitNPC_Couple2_1;
extern EvtScript TTYD64_hos_25_Script_InitNPC_Couple3_1;
extern EvtScript TTYD64_hos_25_Script_InitNPC_Couple4_1;
extern EvtScript TTYD64_hos_25_Script_InitNPC_Couple4_2;
extern u8 TTYD64_hos_25_String_NotEnoughCoins[];
extern EntryList TTYD64_hos_25_EntryList;

// clang-format off
static s32 TTYD64_hos_25_GetTattleMsg;

static s32 TTYD64_hos_25_GetTattle(void) {
    return TTYD64_hos_25_GetTattleMsg;
}

NpcData TTYD64_hos_25_NpcGroup_NPCs[] = {
    {
        .id = 1,
        .settings = &TTYD64_hos_25_NpcSettings_Generic,
        .pos = { 443.0f, 33.0f, 254.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_hos_25_Script_InitNPC_Couple1_1,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30000, .run = 0x00B30000, .chase = 0x00B30000, .anim_4 = 0x00B30000, .anim_5 = 0x00B30000, .death = 0x00B30000, .hit = 0x00B30000, .anim_8 = 0x00B30000, .anim_9 = 0x00B30000, .anim_A = 0x00B30000, .anim_B = 0x00B30000, .anim_C = 0x00B30000, .anim_D = 0x00B30000, .anim_E = 0x00B30000, .anim_F = 0x00B30000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 2,
        .settings = &TTYD64_hos_25_NpcSettings_Generic,
        .pos = { 466.0f, 33.0f, 266.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_hos_25_Script_InitNPC_Couple1_2,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30000, .run = 0x00B30000, .chase = 0x00B30000, .anim_4 = 0x00B30000, .anim_5 = 0x00B30000, .death = 0x00B30000, .hit = 0x00B30000, .anim_8 = 0x00B30000, .anim_9 = 0x00B30000, .anim_A = 0x00B30000, .anim_B = 0x00B30000, .anim_C = 0x00B30000, .anim_D = 0x00B30000, .anim_E = 0x00B30000, .anim_F = 0x00B30000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 3,
        .settings = &TTYD64_hos_25_NpcSettings_Generic,
        .pos = { 174.0f, 33.0f, 230.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_hos_25_Script_InitNPC_Couple2_1,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30000, .run = 0x00B30000, .chase = 0x00B30000, .anim_4 = 0x00B30000, .anim_5 = 0x00B30000, .death = 0x00B30000, .hit = 0x00B30000, .anim_8 = 0x00B30000, .anim_9 = 0x00B30000, .anim_A = 0x00B30000, .anim_B = 0x00B30000, .anim_C = 0x00B30000, .anim_D = 0x00B30000, .anim_E = 0x00B30000, .anim_F = 0x00B30000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 4,
        .settings = &TTYD64_hos_25_NpcSettings_Generic,
        .pos = { 145.0f, 33.0f, 231.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_hos_25_Script_InitNPC_Couple2_1,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30000, .run = 0x00B30000, .chase = 0x00B30000, .anim_4 = 0x00B30000, .anim_5 = 0x00B30000, .death = 0x00B30000, .hit = 0x00B30000, .anim_8 = 0x00B30000, .anim_9 = 0x00B30000, .anim_A = 0x00B30000, .anim_B = 0x00B30000, .anim_C = 0x00B30000, .anim_D = 0x00B30000, .anim_E = 0x00B30000, .anim_F = 0x00B30000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 5,
        .settings = &TTYD64_hos_25_NpcSettings_Generic,
        .pos = { -109.0f, 33.0f, 226.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_hos_25_Script_InitNPC_Couple3_1,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30000, .run = 0x00B30000, .chase = 0x00B30000, .anim_4 = 0x00B30000, .anim_5 = 0x00B30000, .death = 0x00B30000, .hit = 0x00B30000, .anim_8 = 0x00B30000, .anim_9 = 0x00B30000, .anim_A = 0x00B30000, .anim_B = 0x00B30000, .anim_C = 0x00B30000, .anim_D = 0x00B30000, .anim_E = 0x00B30000, .anim_F = 0x00B30000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 6,
        .settings = &TTYD64_hos_25_NpcSettings_Generic,
        .pos = { -131.0f, 33.0f, 234.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_hos_25_Script_InitNPC_Couple3_1,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30000, .run = 0x00B30000, .chase = 0x00B30000, .anim_4 = 0x00B30000, .anim_5 = 0x00B30000, .death = 0x00B30000, .hit = 0x00B30000, .anim_8 = 0x00B30000, .anim_9 = 0x00B30000, .anim_A = 0x00B30000, .anim_B = 0x00B30000, .anim_C = 0x00B30000, .anim_D = 0x00B30000, .anim_E = 0x00B30000, .anim_F = 0x00B30000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 7,
        .settings = &TTYD64_hos_25_NpcSettings_Generic,
        .pos = { -544.0f, 17.0f, 471.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_hos_25_Script_InitNPC_Couple4_1,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30000, .run = 0x00B30000, .chase = 0x00B30000, .anim_4 = 0x00B30000, .anim_5 = 0x00B30000, .death = 0x00B30000, .hit = 0x00B30000, .anim_8 = 0x00B30000, .anim_9 = 0x00B30000, .anim_A = 0x00B30000, .anim_B = 0x00B30000, .anim_C = 0x00B30000, .anim_D = 0x00B30000, .anim_E = 0x00B30000, .anim_F = 0x00B30000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 8,
        .settings = &TTYD64_hos_25_NpcSettings_Generic,
        .pos = { -523.0f, 17.0f, 487.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_hos_25_Script_InitNPC_Couple4_2,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30000, .run = 0x00B30000, .chase = 0x00B30000, .anim_4 = 0x00B30000, .anim_5 = 0x00B30000, .death = 0x00B30000, .hit = 0x00B30000, .anim_8 = 0x00B30000, .anim_9 = 0x00B30000, .anim_A = 0x00B30000, .anim_B = 0x00B30000, .anim_C = 0x00B30000, .anim_D = 0x00B30000, .anim_E = 0x00B30000, .anim_F = 0x00B30000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 9,
        .settings = &TTYD64_hos_25_NpcSettings_Generic,
        .pos = { -528.0f, 17.0f, 358.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_hos_25_Script_InitNPC_Couple0,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30000, .run = 0x00B30000, .chase = 0x00B30000, .anim_4 = 0x00B30000, .anim_5 = 0x00B30000, .death = 0x00B30000, .hit = 0x00B30000, .anim_8 = 0x00B30000, .anim_9 = 0x00B30000, .anim_A = 0x00B30000, .anim_B = 0x00B30000, .anim_C = 0x00B30000, .anim_D = 0x00B30000, .anim_E = 0x00B30000, .anim_F = 0x00B30000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_hos_25_Script_DropMoney = {
    Call(DisablePlayerInput, 1)
    Call(TTYD64_GetFountainCoins, LVar6)
    IfGe(LVar6, 240)
        Call(ShowMessageAtScreenPos, (Bytecode) TTYD64_hos_25_String_EnoughCoins, 160, 40)
        Call(DisablePlayerInput, 0)
        Return
    EndIf
    Call(AddCoin, 0)
    IfLt(LVar0, 20)
        Call(ShowMessageAtScreenPos, (Bytecode) TTYD64_hos_25_String_NotEnoughCoins, 160, 40)
        Call(DisablePlayerInput, 0)
        Return
    EndIf
    Call(InterpPlayerYaw, 90, 0)
    Call(SetPlayerAnimation, 0x10002)
    Wait(5)
    Call(SetPlayerAnimation, 0x6000F)
    Call(PlaySound, 8197)
    Call(AddCoin, -20)
    Call(MakeItemEntity, 343, 0, -1000, 0, 17, 0)
    ExecWait(TTYD64_hos_25_Script_UpdateCoinPos)
    Call(SetPlayerAnimation, 0x10002)
    Add(GameByte(4186), 20)
    Call(TTYD64_GetFountainCoins, LVar6)
    Switch(LVar6)
    CaseEq(80)
        Call(MakeItemEntity, 391, -443, 159, 456, 13, GameFlag(4643))
        Set(LVar0, 0x80016)
        Set(LVar1, 1)
        Set(LVar2, 35)
        ExecWait(TTYD64_SetPlayerAnimation)
    CaseEq(240)
        Call(PlaySound, 602)
        Set(LVar0, 0x80016)
        Set(LVar1, 1)
        Set(LVar2, 35)
        Exec(TTYD64_SetPlayerAnimation)
        Call(PlayEffect_impl, 15, 2, -148, 104, 455, -423, 0, 450, 25, 0, 0, 0, 0)
        Wait(9)
        Set(LVar0, -363)
        Set(LVar1, 0)
        Set(LVar2, 450)
        Add(LVar1, 7)
        Add(LVar2, 2)
        Call(PlayEffect_impl, 24, 4, LVar0, LVar1, LVar2, 10, 0, 0, 6, 0, 0, 0, 0)
        Call(PlaySound, 11)
        Call(MakeItemEntity, 269, -363, 0, 450, 5, GameFlag(4644))
        Wait(15)
    EndSwitch
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_SetupTexturePan = {
    Call(SetTexPanner, 20, 1)
    Call(SetTexPanner, 29, 0)
    Call(SetTexPanner, 35, 0)
    Call(SetTexPanner, 37, 0)
    Call(SetTexPanner, 42, 0)
    Call(SetTexPanner, 48, 1)
    Call(SetTexPanner, 49, 0)
    Call(SetTexPanner, 50, 0)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, -2000)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_hos_25_Script_TexturePan_Update)
    EndThread
    Thread
        Set(LVar0, 1)
        Set(LVar1, 100)
        Set(LVar2, -80)
        Set(LVar3, -50)
        Set(LVar4, 120)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_hos_25_Script_TexturePan_Update)
    EndThread
    Return
    End
};

NpcData TTYD64_hos_25_NpcGroup_Coin[] = {
    {
        .id = 10,
        .settings = &TTYD64_hos_25_NpcSettings_Generic,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x01114D29,
        .init = &TTYD64_hos_25_Script_InitNPC_Coin,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00B30001, .walk = 0x00B30000, .run = 0x00B30000, .chase = 0x00B30000, .anim_4 = 0x00B30000, .anim_5 = 0x00B30000, .death = 0x00B30000, .hit = 0x00B30000, .anim_8 = 0x00B30000, .anim_9 = 0x00B30000, .anim_A = 0x00B30000, .anim_B = 0x00B30000, .anim_C = 0x00B30000, .anim_D = 0x00B30000, .anim_E = 0x00B30000, .anim_F = 0x00B30000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_hos_25_Script_UpdateCoinPos = {
    Set(LVarA, LVar0)
    ChildThread
        Loop(0)
            Call(GetNpcPos, 10, LVar0, LVar1, LVar2)
            Call(SetItemPos, LVarA, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndChildThread
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Add(LVar0, 3)
    Add(LVar1, 6)
    Call(SetNpcPos, 10, LVar0, LVar1, LVar2)
    Call(RandInt, 30, LVar3)
    Add(LVar0, 10)
    Add(LVar0, LVar3)
    Sub(LVar1, 30)
    Sub(LVar2, 90)
    Call(NpcJump0, 10, LVar0, LVar1, LVar2, 20)
    Add(LVar1, 10)
    Call(PlayEffect_impl, 35, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(RemoveItemEntity, LVarA)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_Main = {
    Set(GameByte(425), 29)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_hos_25_Script_SetupMusic)
    Exec(TTYD64_hos_25_Script_SetupTexturePan)
    Exec(TTYD64_hos_25_Script_EnterMap)
    Call(MakeNpcs, 1, (Bytecode) TTYD64_hos_25_NpcGroupList_hos25)
    Set(LVar0, (Bytecode) TTYD64_hos_25_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

u8 TTYD64_hos_25_String_Couple0_1[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0x0C, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F,
    0x0C, 0xF7, 0x44, 0x4F, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x4B, 0x4E, 0x4F,
    0x57, 0xF7, 0x57, 0x48, 0x41, 0x54, 0xF0, 0x54, 0x48, 0x45, 0x59, 0xF7,
    0x53, 0x41, 0x59, 0xF7, 0x41, 0x42, 0x4F, 0x55, 0x54, 0xF7, 0x54, 0x48,
    0x49, 0x53, 0xF7, 0x46, 0x4F, 0x55, 0x4E, 0x54, 0x41, 0x49, 0x4E, 0x1F,
    0xF0, 0xF1, 0xFB, 0x34, 0x48, 0x45, 0x59, 0xF7, 0x53, 0x41, 0x59, 0xF7,
    0x54, 0x48, 0x41, 0x54, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x4D, 0x4F, 0x52,
    0x45, 0xF7, 0x4D, 0x4F, 0x4E, 0x45, 0x59, 0xF0, 0x59, 0x4F, 0x55, 0xF7,
    0x54, 0x48, 0x52, 0x4F, 0x57, 0x0C, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x4D,
    0x4F, 0x52, 0x45, 0x53, 0xF7, 0x43, 0x48, 0x41, 0x4E, 0x43, 0x45, 0xF7,
    0x47, 0x4F, 0x4F, 0x44, 0xF0, 0x54, 0x48, 0x49, 0x4E, 0x47, 0x53, 0xF7,
    0x57, 0x49, 0x4C, 0x4C, 0xF7, 0x48, 0x41, 0x50, 0x50, 0x45, 0x4E, 0xF7,
    0x54, 0x4F, 0xF7, 0x59, 0x4F, 0x55, 0x0E, 0xF0, 0xF1, 0xFB, 0x29, 0x07,
    0x4D, 0xF7, 0x4E, 0x4F, 0x54, 0xF7, 0x53, 0x55, 0x52, 0x45, 0xF7, 0x49,
    0x46, 0xF7, 0x54, 0x48, 0x41, 0x54, 0x07, 0x53, 0xF7, 0x43, 0x4F, 0x4D,
    0x50, 0x4C, 0x45, 0x54, 0x45, 0x4C, 0x59, 0xF0, 0x54, 0x52, 0x55, 0x45,
    0xF7, 0x42, 0x55, 0x54, 0xF7, 0x57, 0x48, 0x4F, 0xF7, 0x41, 0x4D, 0xF7,
    0x29, 0xF7, 0x54, 0x4F, 0xF7, 0x41, 0x53, 0x4B, 0x1F, 0xF1, 0xFD
};

EvtScript TTYD64_hos_25_Script_EnterMap = {
    BindTrigger(TTYD64_hos_25_Script_DropMoney, 2048, 4, 1, 0)
    Call(TTYD64_GetFountainCoins, LVar6)
    IfGe(LVar6, 240)
        Call(MakeItemEntity, 391, -363, 0, 450, 17, GameFlag(4644))
    EndIf
    IfGe(LVar6, 80)
        Call(MakeItemEntity, 269, -443, 159, 456, 13, GameFlag(4643))
    EndIf
    Return
    End
};

u8 TTYD64_hos_25_String_Couple4_2_1[] = {
    0xFC, 0x01, 0x29, 0x46, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x57, 0x41, 0x4E,
    0x54, 0xF7, 0x54, 0x4F, 0xF7, 0x54, 0x52, 0x59, 0xF7, 0x59, 0x4F, 0x55,
    0x52, 0xF7, 0x4C, 0x55, 0x43, 0x4B, 0xF0, 0x4A, 0x55, 0x53, 0x54, 0xF7,
    0x47, 0x4F, 0xF7, 0x54, 0x4F, 0xF7, 0x54, 0x48, 0x41, 0x54, 0xF7, 0x4C,
    0x49, 0x54, 0x54, 0x4C, 0x45, 0xF7, 0x50, 0x45, 0x44, 0x45, 0x53, 0x54,
    0x41, 0x4C, 0xF0, 0x41, 0x4E, 0x44, 0xF7, 0x54, 0x52, 0x59, 0xF7, 0x54,
    0x48, 0x52, 0x4F, 0x57, 0x49, 0x4E, 0x47, 0xF7, 0x41, 0xF7, 0x46, 0x45,
    0x57, 0xF7, 0x43, 0x4F, 0x49, 0x4E, 0x53, 0x0E, 0xF0, 0xF1, 0xFB, 0x32,
    0x45, 0x4D, 0x45, 0x4D, 0x42, 0x45, 0x52, 0xF7, 0x54, 0x48, 0x41, 0x54,
    0xF7, 0x54, 0x48, 0x45, 0xF7, 0x4D, 0x4F, 0x52, 0x45, 0xF7, 0x59, 0x4F,
    0x55, 0xF0, 0x54, 0x48, 0x52, 0x4F, 0x57, 0x0C, 0xF7, 0x54, 0x48, 0x45,
    0xF7, 0x4D, 0x4F, 0x52, 0x45, 0xF7, 0x4C, 0x49, 0x4B, 0x45, 0x4C, 0x59,
    0xF7, 0x47, 0x4F, 0x4F, 0x44, 0xF0, 0x54, 0x48, 0x49, 0x4E, 0x47, 0x53,
    0xF7, 0x57, 0x49, 0x4C, 0x4C, 0xF7, 0x48, 0x41, 0x50, 0x50, 0x45, 0x4E,
    0xF7, 0x54, 0x4F, 0xF7, 0x59, 0x4F, 0x55, 0x0E, 0xF1, 0xFD
};

u8 TTYD64_hos_25_Tattle_Couple[] = {
    0xFC, 0x04, 0x2A, 0x55, 0x53, 0x54, 0xF7, 0x41, 0xF7, 0x43, 0x4F, 0x55,
    0x50, 0x4C, 0x45, 0xF7, 0x48, 0x41, 0x56, 0x49, 0x4E, 0x47, 0xF7, 0x41,
    0xF0, 0x47, 0x4F, 0x4F, 0x44, 0xF7, 0x54, 0x49, 0x4D, 0x45, 0xF7, 0x54,
    0x4F, 0x47, 0x45, 0x54, 0x48, 0x45, 0x52, 0x0E, 0xF0, 0xF1, 0xFB, 0x34,
    0x4F, 0xF7, 0x42, 0x45, 0xF7, 0x48, 0x4F, 0x4E, 0x45, 0x53, 0x54, 0xF7,
    0x29, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x46, 0x49, 0x4E, 0x44,
    0xF7, 0x54, 0x48, 0x45, 0xF0, 0x42, 0x49, 0x47, 0xF7, 0x41, 0x50, 0x50,
    0x45, 0x41, 0x4C, 0xF7, 0x4F, 0x46, 0xF7, 0x48, 0x41, 0x56, 0x49, 0x4E,
    0x47, 0xF7, 0x41, 0xF7, 0x43, 0x4F, 0x55, 0x50, 0x4C, 0x45, 0x0C, 0xF0,
    0x29, 0xF7, 0x50, 0x52, 0x45, 0x46, 0x45, 0x52, 0xF7, 0x41, 0x44, 0x56,
    0x45, 0x4E, 0x54, 0x55, 0x52, 0x45, 0x53, 0x01, 0xF0, 0xF1, 0xFB, 0x39,
    0x4F, 0x55, 0xF7, 0x4B, 0x4E, 0x4F, 0x57, 0xF7, 0x57, 0x48, 0x41, 0x54,
    0xF7, 0x29, 0xF7, 0x4D, 0x45, 0x41, 0x4E, 0x0C, 0xF7, 0x52, 0x49, 0x47,
    0x48, 0x54, 0xF0, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x1F, 0xF1, 0xFD
};

EvtScript TTYD64_hos_25_Script_TexturePan_Update = {
    SetGroup(0)
    IfEq(LVar5, 1)
        IfEq(LVar6, 1)
            IfEq(LVar7, 1)
                IfEq(LVar8, 1)
                    Call(TTYD64_TexturePan_Simple)
                    Return
                EndIf
            EndIf
        EndIf
    EndIf
    Call(TTYD64_TexturePan_Complex)
    Return
    End
};

u8 TTYD64_hos_25_Tattle_Solo[] = {
    0xFC, 0x04, 0x34, 0x48, 0x49, 0x53, 0xF7, 0x50, 0x4C, 0x41, 0x43, 0x45,
    0xF7, 0x49, 0x53, 0xF7, 0x4D, 0x4F, 0x53, 0x54, 0x4C, 0x59, 0xF7, 0x4B,
    0x4E, 0x4F, 0x57, 0x4E, 0xF7, 0x41, 0x53, 0xF7, 0x41, 0xF0, 0x50, 0x4C,
    0x41, 0x43, 0x45, 0xF7, 0x54, 0x4F, 0xF7, 0x42, 0x45, 0xF7, 0x57, 0x49,
    0x54, 0x48, 0xF7, 0x59, 0x4F, 0x55, 0x52, 0xF7, 0x4C, 0x4F, 0x56, 0x45,
    0x44, 0xF7, 0x4F, 0x4E, 0x45, 0x53, 0xF0, 0x42, 0x55, 0x54, 0xF7, 0x49,
    0x54, 0x07, 0x53, 0xF7, 0x41, 0x4C, 0x53, 0x4F, 0xF7, 0x47, 0x4F, 0x4F,
    0x44, 0xF7, 0x46, 0x4F, 0x52, 0xF7, 0x48, 0x41, 0x56, 0x49, 0x4E, 0x47,
    0xF7, 0x41, 0xF0, 0x47, 0x4F, 0x4F, 0x44, 0xF7, 0x54, 0x49, 0x4D, 0x45,
    0xF7, 0x41, 0x4C, 0x4F, 0x4E, 0x45, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x4B,
    0x4E, 0x4F, 0x57, 0x1F, 0xF0, 0xF1, 0xFB, 0x2E, 0x4F, 0x54, 0x48, 0x49,
    0x4E, 0x47, 0xF7, 0x57, 0x52, 0x4F, 0x4E, 0x47, 0xF7, 0x57, 0x49, 0x54,
    0x48, 0xF7, 0x54, 0x48, 0x41, 0x54, 0x0E, 0xF1, 0xFD
};

u8 TTYD64_hos_25_String_Tattle[] = {
    0xFC, 0x04, 0x34, 0x48, 0x49, 0x53, 0xF7, 0x49, 0x53, 0xF7, 0x54, 0x48,
    0x45, 0xF7, 0x57, 0x49, 0x53, 0x48, 0xF7, 0x46, 0x4F, 0x55, 0x4E, 0x54,
    0x41, 0x49, 0x4E, 0x0C, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x43, 0x41, 0x4E,
    0xF0, 0x54, 0x52, 0x59, 0xF7, 0x54, 0x48, 0x52, 0x4F, 0x57, 0x49, 0x4E,
    0x47, 0xF7, 0x43, 0x4F, 0x49, 0x4E, 0x53, 0xF7, 0x49, 0x4E, 0x54, 0x4F,
    0xF7, 0x54, 0x48, 0x45, 0xF0, 0x46, 0x4F, 0x55, 0x4E, 0x54, 0x41, 0x49,
    0x4E, 0x0E, 0xF0, 0xF1, 0xFB, 0x2D, 0x41, 0x59, 0x42, 0x45, 0xF7, 0x54,
    0x4F, 0x44, 0x41, 0x59, 0xF7, 0x49, 0x53, 0xF7, 0x59, 0x4F, 0x55, 0x52,
    0xF7, 0x4C, 0x55, 0x43, 0x4B, 0x59, 0xF7, 0x44, 0x41, 0x59, 0xF0, 0x2D,
    0x41, 0x52, 0x49, 0x4F, 0x01, 0xF1, 0xFD
};

u8 TTYD64_hos_25_String_Couple4_1_1[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C,
    0xF7, 0x48, 0x41, 0x56, 0x45, 0x4E, 0x07, 0x54, 0xF7, 0x59, 0x4F, 0x55,
    0xF7, 0x54, 0x48, 0x4F, 0x55, 0x47, 0x48, 0x54, 0xF0, 0x41, 0x42, 0x4F,
    0x55, 0x54, 0xF7, 0x54, 0x48, 0x52, 0x4F, 0x57, 0x49, 0x4E, 0x47, 0xF7,
    0x53, 0x4F, 0x4D, 0x45, 0xF7, 0x43, 0x4F, 0x49, 0x4E, 0x53, 0xF7, 0x49,
    0x4E, 0xF7, 0x54, 0x48, 0x45, 0xF0, 0x57, 0x49, 0x53, 0x48, 0x49, 0x4E,
    0x47, 0xF7, 0x46, 0x4F, 0x55, 0x4E, 0x54, 0x41, 0x49, 0x4E, 0x1F, 0xF1,
    0xFD
};

EvtScript TTYD64_hos_25_Script_InitNPC_Coin = {
    Call(SetNpcJumpscale, -1, Float(1.0))
    Call(EnableNpcShadow, -1, 0)
    Call(SetNpcFlagBits, -1, 0x4000000, 1)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_Exit0 = {
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "hos_03", 11)
    Wait(100)
    Return
    End
};

u8 TTYD64_hos_25_String_Couple1_2_1[] = {
    0xFC, 0x01, 0x29, 0xF7, 0x4C, 0x4F, 0x56, 0x45, 0xF7, 0x43, 0x4F, 0x4D,
    0x49, 0x4E, 0x47, 0xF7, 0x48, 0x45, 0x52, 0x45, 0x0C, 0xF7, 0x49, 0x54,
    0xF7, 0x49, 0x53, 0xF7, 0x4D, 0x59, 0xF0, 0x46, 0x41, 0x56, 0x4F, 0x52,
    0x49, 0x54, 0x45, 0xF7, 0x50, 0x4C, 0x41, 0x43, 0x45, 0xF7, 0x54, 0x4F,
    0xF7, 0x53, 0x50, 0x45, 0x4E, 0x44, 0xF7, 0x54, 0x49, 0x4D, 0x45, 0xF0,
    0x57, 0x49, 0x54, 0x48, 0xF7, 0x48, 0x49, 0x4D, 0x01, 0xF7, 0x90, 0xF1,
    0xFD
};

u8 TTYD64_hos_25_String_Couple1_1_1[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C,
    0xF7, 0x44, 0x4F, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x54, 0x48, 0x49, 0x4E,
    0x4B, 0xF7, 0x57, 0x49, 0x53, 0x48, 0x45, 0x53, 0xF0, 0x43, 0x4F, 0x4D,
    0x45, 0xF7, 0x54, 0x52, 0x55, 0x45, 0x1F, 0xF0, 0xF1, 0xFB, 0x29, 0xF7,
    0x52, 0x45, 0x41, 0x4C, 0x4C, 0x59, 0xF7, 0x48, 0x4F, 0x50, 0x45, 0xF7,
    0x53, 0x4F, 0x0E, 0xF1, 0xFD
};

MapSettings TTYD64_hos_25_Header = {
    .main = &TTYD64_hos_25_Script_Main,
    .entryList = &TTYD64_hos_25_EntryList,
    .entryCount = 1,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_hos_25_GetTattle },
};

u8 TTYD64_hos_25_String_Couple3_1_1[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x01,
    0xF7, 0x23, 0x41, 0x4E, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x47, 0x49, 0x56,
    0x45, 0xF7, 0x55, 0x53, 0xF7, 0x41, 0xF0, 0x4C, 0x49, 0x54, 0x54, 0x4C,
    0x45, 0xF7, 0x50, 0x52, 0x49, 0x56, 0x41, 0x43, 0x59, 0xF7, 0x50, 0x4C,
    0x45, 0x41, 0x53, 0x45, 0x1F, 0x01, 0xF0, 0xF1, 0xFD
};

EvtScript TTYD64_hos_25_Script_SetupMusic = {
    Call(SetMusic, 0, 96, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_Interact_Couple3_1 = {
    Call(SpeakToPlayer, -1, 0xB30002, 0xB30001, 0, (Bytecode) TTYD64_hos_25_String_Couple3_1_1)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_Interact_Couple4_1 = {
    Call(SpeakToPlayer, -1, 0xB30002, 0xB30001, 0, (Bytecode) TTYD64_hos_25_String_Couple4_1_1)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_Interact_Couple4_2 = {
    Call(SpeakToPlayer, -1, 0xB30002, 0xB30001, 0, (Bytecode) TTYD64_hos_25_String_Couple4_2_1)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_Interact_Couple0 = {
    Call(SpeakToPlayer, -1, 0xB30002, 0xB30001, 0, (Bytecode) TTYD64_hos_25_String_Couple0_1)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_Interact_Couple1_2 = {
    Call(SpeakToPlayer, -1, 0xB30002, 0xB30001, 0, (Bytecode) TTYD64_hos_25_String_Couple1_2_1)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_Interact_Couple2_1 = {
    Call(SpeakToPlayer, -1, 0xB30002, 0xB30001, 0, (Bytecode) TTYD64_hos_25_String_Couple2_1_1)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_Interact_Couple1_1 = {
    Call(SpeakToPlayer, -1, 0xB30002, 0xB30001, 0, (Bytecode) TTYD64_hos_25_String_Couple1_1_1)
    Return
    End
};

u8 TTYD64_hos_25_String_EnoughCoins[] = {
    0xFC, 0x06, 0x29, 0xF7, 0x54, 0x48, 0x49, 0x4E, 0x4B, 0xF7, 0x29, 0xF7,
    0x41, 0x4C, 0x52, 0x45, 0x41, 0x44, 0x59, 0xF7, 0x54, 0x48, 0x52, 0x45,
    0x57, 0xF7, 0x45, 0x4E, 0x4F, 0x55, 0x47, 0x48, 0xF0, 0x43, 0x4F, 0x49,
    0x4E, 0x53, 0x0E, 0xF1, 0xFD
};

NpcSettings TTYD64_hos_25_NpcSettings_Generic = {
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

EvtScript TTYD64_hos_25_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_hos_25_Script_Exit0, 0x80000, 5, 1, 0)
    Return
    End
};

u8 TTYD64_hos_25_String_Couple2_1_1[] = {
    0xFC, 0x01, 0x21, 0x4E, 0x44, 0xF7, 0x29, 0xF7, 0x4C, 0x4F, 0x56, 0x45,
    0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x45, 0x56, 0x45, 0x4E, 0xF7, 0x4D, 0x4F,
    0x52, 0x45, 0x0C, 0xF7, 0x4D, 0x59, 0xF0, 0x4C, 0x4F, 0x56, 0x45, 0x01,
    0xF1, 0xFD
};

NpcGroupList TTYD64_hos_25_NpcGroupList_hos25 = {
    { .npcCount = 9, .npcs = TTYD64_hos_25_NpcGroup_NPCs, .battle = 0x0000, .stage = 0 },
    { .npcCount = 1, .npcs = TTYD64_hos_25_NpcGroup_Coin, .battle = 0x0000, .stage = 0 },
    {},
};

EvtScript TTYD64_hos_25_Script_InitNPC_Couple0 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_hos_25_Script_Interact_Couple0)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_InitNPC_Couple1_1 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_hos_25_Script_Interact_Couple1_1)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_InitNPC_Couple1_2 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_hos_25_Script_Interact_Couple1_2)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_InitNPC_Couple2_1 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_hos_25_Script_Interact_Couple2_1)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_InitNPC_Couple3_1 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_hos_25_Script_Interact_Couple3_1)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_InitNPC_Couple4_1 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_hos_25_Script_Interact_Couple4_1)
    Return
    End
};

EvtScript TTYD64_hos_25_Script_InitNPC_Couple4_2 = {
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_hos_25_Script_Interact_Couple4_2)
    Return
    End
};

u8 TTYD64_hos_25_String_NotEnoughCoins[] = {
    0xFC, 0x06, 0x29, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x48, 0x41,
    0x56, 0x45, 0xF7, 0x45, 0x4E, 0x4F, 0x55, 0x47, 0x48, 0xF7, 0x43, 0x4F,
    0x49, 0x4E, 0x53, 0xF7, 0xF1, 0xFD
};

EntryList TTYD64_hos_25_EntryList = {
    { 334.0f, 0.0f, 499.0f, 0.0f },
};

MapConfig TTYD64_mapcfg_hos_25 = {
    .id = "hos_25",
    .settings = &TTYD64_hos_25_Header,
    .bgName = "hos_bg",
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_hos_25(void) {
    TTYD64_nm_BindMessage(TTYD64_hos_25_Script_DropMoney, TTYD64_hos_25_String_EnoughCoins);
    TTYD64_nm_BindMessage(TTYD64_hos_25_Script_DropMoney, TTYD64_hos_25_String_NotEnoughCoins);
    TTYD64_nm_BindMessage(TTYD64_hos_25_Script_Interact_Couple3_1, TTYD64_hos_25_String_Couple3_1_1);
    TTYD64_nm_BindMessage(TTYD64_hos_25_Script_Interact_Couple4_1, TTYD64_hos_25_String_Couple4_1_1);
    TTYD64_nm_BindMessage(TTYD64_hos_25_Script_Interact_Couple4_2, TTYD64_hos_25_String_Couple4_2_1);
    TTYD64_nm_BindMessage(TTYD64_hos_25_Script_Interact_Couple0, TTYD64_hos_25_String_Couple0_1);
    TTYD64_nm_BindMessage(TTYD64_hos_25_Script_Interact_Couple1_2, TTYD64_hos_25_String_Couple1_2_1);
    TTYD64_nm_BindMessage(TTYD64_hos_25_Script_Interact_Couple2_1, TTYD64_hos_25_String_Couple2_1_1);
    TTYD64_nm_BindMessage(TTYD64_hos_25_Script_Interact_Couple1_1, TTYD64_hos_25_String_Couple1_1_1);
    TTYD64_hos_25_NpcGroup_NPCs[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_hos_25_Tattle_Couple);
    TTYD64_hos_25_NpcGroup_NPCs[1].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_hos_25_Tattle_Couple);
    TTYD64_hos_25_NpcGroup_NPCs[2].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_hos_25_Tattle_Couple);
    TTYD64_hos_25_NpcGroup_NPCs[3].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_hos_25_Tattle_Couple);
    TTYD64_hos_25_NpcGroup_NPCs[4].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_hos_25_Tattle_Couple);
    TTYD64_hos_25_NpcGroup_NPCs[5].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_hos_25_Tattle_Couple);
    TTYD64_hos_25_NpcGroup_NPCs[6].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_hos_25_Tattle_Couple);
    TTYD64_hos_25_NpcGroup_NPCs[7].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_hos_25_Tattle_Couple);
    TTYD64_hos_25_NpcGroup_NPCs[8].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_hos_25_Tattle_Solo);
    TTYD64_hos_25_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_hos_25_String_Tattle);
}
