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
#include "port/romhack/specific/TTYD64/world/newmaps.h"

API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(GetColliderCenter);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcImgFXParams);
API_CALLABLE(SetNpcPos);
API_CALLABLE(UseExitHeading);

extern NpcData TTYD64_kpa_137_NpcGroup_Boo[];
extern NpcData TTYD64_kpa_137_NpcGroup_Boos[];
extern EvtScript TTYD64_kpa_137_Script_Boos_BooAppears;
extern EvtScript TTYD64_kpa_137_Script_Boos_DissapearAllBoos;
extern EvtScript TTYD64_kpa_137_Script_Boos_Completed;
extern EvtScript TTYD64_kpa_137_Script_Tombstone;
extern EvtScript TTYD64_kpa_137_Script_EnterMap;
extern EvtScript TTYD64_kpa_137_Script_SetupTexturePan;
extern EvtScript TTYD64_kpa_137_Script_Boos_Wrong;
extern EvtScript TTYD64_kpa_137_Script_Main;
extern EvtScript TTYD64_kpa_137_Script_TexturePan_Update;
extern u8 TTYD64_kpa_137_String_Tattle[];
extern EvtScript TTYD64_kpa_137_Script_Exit0;
extern MapSettings TTYD64_kpa_137_Header;
extern EvtScript TTYD64_kpa_137_Script_SetupMusic;
extern NpcSettings TTYD64_kpa_137_NPCSettings_NPC;
extern NpcSettings TTYD64_kpa_137_NpcSettings_Generic;
extern EvtScript TTYD64_kpa_137_Script_Tomb3;
extern EvtScript TTYD64_kpa_137_Script_Tomb2;
extern EvtScript TTYD64_kpa_137_Script_Tomb1;
extern EvtScript TTYD64_kpa_137_Script_Tomb7;
extern EvtScript TTYD64_kpa_137_Script_Tomb6;
extern EvtScript TTYD64_kpa_137_Script_Tomb5;
extern EvtScript TTYD64_kpa_137_Script_Tomb4;
extern EvtScript TTYD64_kpa_137_Script_Tomb9;
extern EvtScript TTYD64_kpa_137_Script_Tomb8;
extern EvtScript TTYD64_kpa_137_Script_CreateExitTriggers;
extern NpcGroupList TTYD64_kpa_137_NpcGroupList_arn22;
extern NpcGroupList TTYD64_kpa_137_NpcGroupList_kpa137;
extern EntryList TTYD64_kpa_137_EntryList;
extern EvtScript TTYD64_kpa_137_Script_Init_NPC_Boo;
extern s32 TTYD64_kpa_137_Data_Solution[];

// clang-format off
static s32 TTYD64_kpa_137_GetTattleMsg;

static s32 TTYD64_kpa_137_GetTattle(void) {
    return TTYD64_kpa_137_GetTattleMsg;
}

NpcData TTYD64_kpa_137_NpcGroup_Boo[] = {
    {
        .id = 1,
        .settings = &TTYD64_kpa_137_NPCSettings_NPC,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00440C0D,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_kpa_137_NPCSettings_NPC,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00440C0D,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_kpa_137_NPCSettings_NPC,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00440C0D,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_kpa_137_NPCSettings_NPC,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00440C0D,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_kpa_137_NPCSettings_NPC,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00440C0D,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_kpa_137_NPCSettings_NPC,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00440C0D,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_kpa_137_NPCSettings_NPC,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00440C0D,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_kpa_137_NPCSettings_NPC,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00440C0D,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_kpa_137_NPCSettings_NPC,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00440C0D,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_kpa_137_NpcGroup_Boos[] = {
    {
        .id = 1,
        .settings = &TTYD64_kpa_137_NpcSettings_Generic,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_kpa_137_Script_Init_NPC_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_kpa_137_NpcSettings_Generic,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_kpa_137_Script_Init_NPC_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_kpa_137_NpcSettings_Generic,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_kpa_137_Script_Init_NPC_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 4,
        .settings = &TTYD64_kpa_137_NpcSettings_Generic,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_kpa_137_Script_Init_NPC_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_kpa_137_NpcSettings_Generic,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_kpa_137_Script_Init_NPC_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_kpa_137_NpcSettings_Generic,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_kpa_137_Script_Init_NPC_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_kpa_137_NpcSettings_Generic,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_kpa_137_Script_Init_NPC_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_kpa_137_NpcSettings_Generic,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_kpa_137_Script_Init_NPC_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_kpa_137_NpcSettings_Generic,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00110D09,
        .init = &TTYD64_kpa_137_Script_Init_NPC_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00950001, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_kpa_137_Script_Boos_BooAppears = {
    Call(PlaySound, 8207)
    UseBuf((Bytecode) TTYD64_kpa_137_Data_Solution)
    Set(LVar1, MapVar(1))
    BufPeek(LVar0, LVar1)
    Switch(LVar0)
    CaseEq(1)
        Set(LVar3, 1)
        Set(LVar4, 19)
    CaseEq(2)
        Set(LVar3, 2)
        Set(LVar4, 20)
    CaseEq(3)
        Set(LVar3, 3)
        Set(LVar4, 21)
    CaseEq(4)
        Set(LVar3, 4)
        Set(LVar4, 22)
    CaseEq(5)
        Set(LVar3, 5)
        Set(LVar4, 23)
    CaseEq(6)
        Set(LVar3, 6)
        Set(LVar4, 24)
    CaseEq(7)
        Set(LVar3, 7)
        Set(LVar4, 25)
    CaseEq(8)
        Set(LVar3, 8)
        Set(LVar4, 26)
    CaseEq(9)
        Set(LVar3, 9)
        Set(LVar4, 27)
    EndSwitch
    Call(SetNpcAnimation, LVar3, 0x950005)
    Call(GetColliderCenter, LVar4)
    Add(LVar1, 15)
    Call(SetNpcPos, LVar3, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Loop(10)
        Add(LVar1, 24)
        Call(SetNpcImgFXParams, LVar3, 7, LVar1, 0, 0, 0)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_Boos_DissapearAllBoos = {
    Set(LVar1, 240)
    Loop(10)
        Sub(LVar1, 24)
        Call(SetNpcImgFXParams, 1, 7, LVar1, 0, 0, 0)
        Call(SetNpcImgFXParams, 2, 7, LVar1, 0, 0, 0)
        Call(SetNpcImgFXParams, 3, 7, LVar1, 0, 0, 0)
        Call(SetNpcImgFXParams, 4, 7, LVar1, 0, 0, 0)
        Call(SetNpcImgFXParams, 5, 7, LVar1, 0, 0, 0)
        Call(SetNpcImgFXParams, 6, 7, LVar1, 0, 0, 0)
        Call(SetNpcImgFXParams, 7, 7, LVar1, 0, 0, 0)
        Call(SetNpcImgFXParams, 8, 7, LVar1, 0, 0, 0)
        Call(SetNpcImgFXParams, 9, 7, LVar1, 0, 0, 0)
        Wait(1)
    EndLoop
    Call(SetNpcPos, 1, 0, -1000, 0)
    Call(SetNpcPos, 2, 0, -1000, 0)
    Call(SetNpcPos, 3, 0, -1000, 0)
    Call(SetNpcPos, 4, 0, -1000, 0)
    Call(SetNpcPos, 5, 0, -1000, 0)
    Call(SetNpcPos, 6, 0, -1000, 0)
    Call(SetNpcPos, 7, 0, -1000, 0)
    Call(SetNpcPos, 8, 0, -1000, 0)
    Call(SetNpcPos, 9, 0, -1000, 0)
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_Boos_Completed = {
    Call(SetNpcAnimation, 1, 0x950008)
    Call(SetNpcAnimation, 2, 0x950008)
    Call(SetNpcAnimation, 3, 0x950008)
    Call(SetNpcAnimation, 4, 0x950008)
    Call(SetNpcAnimation, 5, 0x950008)
    Call(SetNpcAnimation, 6, 0x950008)
    Call(SetNpcAnimation, 7, 0x950008)
    Call(SetNpcAnimation, 8, 0x950008)
    Call(SetNpcAnimation, 9, 0x950008)
    Wait(25)
    ExecWait(TTYD64_kpa_137_Script_Boos_DissapearAllBoos)
    Wait(10)
    Set(LVar0, 109)
    Set(LVar1, 0)
    Set(LVar2, 104)
    Add(LVar1, 60)
    Call(PlaySound, 717)
    Add(LVar2, 1)
    Call(PlayEffect_impl, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Sub(LVar2, 1)
    Call(MakeItemEntity, 251, LVar0, LVar1, LVar2, 13, GameFlag(5696))
    Wait(20)
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_Tombstone = {
    IfEq(GameFlag(5695), 1)
        Return
    EndIf
    Set(LVar8, LVar0)
    Set(LVar0, LVar8)
    Set(LVar1, 10)
    Call(DisablePlayerInput, 1)
    UseBuf((Bytecode) TTYD64_kpa_137_Data_Solution)
    Set(LVar1, MapVar(1))
    BufPeek(LVar0, LVar1)
    IfEq(LVar0, LVar8)
        Add(LVar1, 1)
        BufPeek(LVar0, LVar1)
        IfEq(LVar0, -1)
            ExecWait(TTYD64_kpa_137_Script_Boos_BooAppears)
            Set(MapVar(1), 0)
            Add(GameFlag(5695), 1)
            Call(PlaySound, 11)
            ExecWait(TTYD64_kpa_137_Script_Boos_Completed)
        Else
            ExecWait(TTYD64_kpa_137_Script_Boos_BooAppears)
            Add(MapVar(1), 1)
        EndIf
    Else
        Call(PlaySound, 541)
        ExecWait(TTYD64_kpa_137_Script_Boos_Wrong)
        Set(MapVar(1), 0)
    EndIf
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_EnterMap = {
    IfEq(GameFlag(5695), 0)
        BindTrigger(TTYD64_kpa_137_Script_Tomb1, 256, 19, 1, 0)
        BindTrigger(TTYD64_kpa_137_Script_Tomb2, 256, 20, 1, 0)
        BindTrigger(TTYD64_kpa_137_Script_Tomb3, 256, 21, 1, 0)
        BindTrigger(TTYD64_kpa_137_Script_Tomb4, 256, 22, 1, 0)
        BindTrigger(TTYD64_kpa_137_Script_Tomb5, 256, 23, 1, 0)
        BindTrigger(TTYD64_kpa_137_Script_Tomb6, 256, 24, 1, 0)
        BindTrigger(TTYD64_kpa_137_Script_Tomb7, 256, 25, 1, 0)
        BindTrigger(TTYD64_kpa_137_Script_Tomb8, 256, 26, 1, 0)
        BindTrigger(TTYD64_kpa_137_Script_Tomb9, 256, 27, 1, 0)
    Else
        Call(MakeItemEntity, 251, 109, 0, 104, 13, GameFlag(5696))
    EndIf
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_SetupTexturePan = {
    Thread
        Set(LVar0, 0)
        Set(LVar1, -400)
        Set(LVar2, 0)
        Set(LVar3, -800)
        Set(LVar4, 0)
        Set(LVar5, 1)
        Set(LVar6, 0)
        Set(LVar7, 1)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_kpa_137_Script_TexturePan_Update)
    EndThread
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_Boos_Wrong = {
    IfNe(MapVar(1), 0)
        Call(PlaySound, 8206)
    EndIf
    Call(SetNpcAnimation, 1, 0x950007)
    Call(SetNpcAnimation, 2, 0x950007)
    Call(SetNpcAnimation, 3, 0x950007)
    Call(SetNpcAnimation, 4, 0x950007)
    Call(SetNpcAnimation, 5, 0x950007)
    Call(SetNpcAnimation, 6, 0x950007)
    Call(SetNpcAnimation, 7, 0x950007)
    Call(SetNpcAnimation, 8, 0x950007)
    Call(SetNpcAnimation, 9, 0x950007)
    Exec(TTYD64_kpa_137_Script_Boos_DissapearAllBoos)
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_Main = {
    Set(GameByte(425), 22)
    Call(SetCamPerspective, 0, 3, 30, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_kpa_137_Script_SetupMusic)
    Exec(TTYD64_kpa_137_Script_SetupTexturePan)
    Exec(TTYD64_kpa_137_Script_EnterMap)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_kpa_137_NpcGroupList_kpa137)
    Set(LVar0, (Bytecode) TTYD64_kpa_137_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_TexturePan_Update = {
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

u8 TTYD64_kpa_137_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x28, 0x4F, 0x57, 0xF7, 0x4B, 0x49, 0x4E, 0x44,
    0xF7, 0x4F, 0x46, 0xF7, 0x22, 0x4F, 0x57, 0x53, 0x45, 0x52, 0xF7, 0x54,
    0x48, 0x41, 0x54, 0xF7, 0x48, 0x45, 0xF7, 0x57, 0x4F, 0x55, 0x4C, 0x44,
    0xF0, 0x48, 0x41, 0x56, 0x45, 0xF7, 0x4F, 0x52, 0x44, 0x45, 0x52, 0x45,
    0x44, 0xF7, 0x4D, 0x41, 0x4B, 0x49, 0x4E, 0x47, 0xF7, 0x41, 0xF7, 0x43,
    0x45, 0x4D, 0x45, 0x54, 0x45, 0x52, 0x59, 0xF7, 0x46, 0x4F, 0x52, 0xF0,
    0x48, 0x49, 0x53, 0xF7, 0x54, 0x52, 0x4F, 0x4F, 0x50, 0x53, 0x0C, 0xF7,
    0x54, 0x48, 0x45, 0xF7, 0x44, 0x45, 0x41, 0x44, 0xF7, 0x41, 0x4C, 0x53,
    0x4F, 0xF7, 0x4E, 0x45, 0x45, 0x44, 0xF7, 0x54, 0x4F, 0xF0, 0x52, 0x45,
    0x53, 0x54, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x4B, 0x4E, 0x4F, 0x57, 0x1F,
    0xF1, 0xFD
};

EvtScript TTYD64_kpa_137_Script_Exit0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "kpa_03", 2)
    Wait(100)
    Return
    End
};

MapSettings TTYD64_kpa_137_Header = {
    .main = &TTYD64_kpa_137_Script_Main,
    .entryList = &TTYD64_kpa_137_EntryList,
    .entryCount = 1,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_kpa_137_GetTattle },
};

EvtScript TTYD64_kpa_137_Script_SetupMusic = {
    Call(SetMusic, 0, 100, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

NpcSettings TTYD64_kpa_137_NPCSettings_NPC = {
    .defaultAnim = 0x00000000,
    .height = 24,
    .radius = 40,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = NULL,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 13,
    .actionFlags = 0,
};

NpcSettings TTYD64_kpa_137_NpcSettings_Generic = {
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

EvtScript TTYD64_kpa_137_Script_Tomb3 = {
    Set(LVar0, 3)
    Exec(TTYD64_kpa_137_Script_Tombstone)
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_Tomb2 = {
    Set(LVar0, 2)
    Exec(TTYD64_kpa_137_Script_Tombstone)
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_Tomb1 = {
    Set(LVar0, 1)
    Exec(TTYD64_kpa_137_Script_Tombstone)
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_Tomb7 = {
    Set(LVar0, 7)
    Exec(TTYD64_kpa_137_Script_Tombstone)
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_Tomb6 = {
    Set(LVar0, 6)
    Exec(TTYD64_kpa_137_Script_Tombstone)
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_Tomb5 = {
    Set(LVar0, 5)
    Exec(TTYD64_kpa_137_Script_Tombstone)
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_Tomb4 = {
    Set(LVar0, 4)
    Exec(TTYD64_kpa_137_Script_Tombstone)
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_Tomb9 = {
    Set(LVar0, 9)
    Exec(TTYD64_kpa_137_Script_Tombstone)
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_Tomb8 = {
    Set(LVar0, 8)
    Exec(TTYD64_kpa_137_Script_Tombstone)
    Return
    End
};

EvtScript TTYD64_kpa_137_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_kpa_137_Script_Exit0, 0x80000, 0, 1, 0)
    Return
    End
};

NpcGroupList TTYD64_kpa_137_NpcGroupList_arn22 = {
    { .npcCount = 9, .npcs = TTYD64_kpa_137_NpcGroup_Boo, .battle = 0x0000, .stage = 0 },
    {},
};

NpcGroupList TTYD64_kpa_137_NpcGroupList_kpa137 = {
    { .npcCount = 9, .npcs = TTYD64_kpa_137_NpcGroup_Boos, .battle = 0x0000, .stage = 0 },
    {},
};

EntryList TTYD64_kpa_137_EntryList = {
    { 331.0f, -5.0f, 138.0f, -90.0f },
};

EvtScript TTYD64_kpa_137_Script_Init_NPC_Boo = {
    Return
    End
};

s32 TTYD64_kpa_137_Data_Solution[] = {
    2, 6, 4, -1
};

MapConfig TTYD64_mapcfg_kpa_137 = {
    .id = "kpa_137",
    .settings = &TTYD64_kpa_137_Header,
    .bgName = "kpa_bg",
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 3,
};
// clang-format on

void TTYD64_nm_Install_kpa_137(void) {
    TTYD64_kpa_137_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_kpa_137_String_Tattle);
}
