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

API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GetCurrentPartnerID);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetPartnerInUse);
API_CALLABLE(GetPlayerActionState);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GotoMap);
API_CALLABLE(HidePlayerShadow);
API_CALLABLE(InterpNpcYaw);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(InterruptUsePartner);
API_CALLABLE(IsPlayerOnValidFloor);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(PanToTarget);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAt);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveEncounter);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamSpeed);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetPanTarget);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerFlagBits);
API_CALLABLE(SetPlayerImgFXFlags);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(UpdatePlayerImgFX);
API_CALLABLE(UseExitHeading);
API_CALLABLE(UseSettingsFrom);
API_CALLABLE(kzn_04_FireBarAI_Main);

extern NpcData TTYD64_kpa_136_NpcGroup_Flame1[];
extern NpcData TTYD64_kpa_136_NpcGroup_Flame3[];
extern NpcData TTYD64_kpa_136_NpcGroup_Flame2[];
extern EvtScript TTYD64_kpa_136_Script_EnterHorizontalPipe;
extern EvtScript TTYD64_kpa_136_Script_KillFlames;
extern EvtScript TTYD64_kpa_136_Script_EnterVerticalPipe;
extern EvtScript TTYD64_kpa_136_Script_ExitHorizontalPipe;
extern EvtScript TTYD64_kpa_136_Script_ExitVerticalPipe;
extern EvtScript TTYD64_kpa_136_Script_UpdateFlamesAnimations;
extern EvtScript TTYD64_kpa_136_Script_Main;
extern EvtScript TTYD64_kpa_136_Script_EnterMap;
extern u8 TTYD64_kpa_136_String_Tattle[];
extern EvtScript TTYD64_kpa_136_Script_Exit0;
extern EvtScript TTYD64_kpa_136_Script_Exit1;
extern EvtScript TTYD64_kpa_136_Script_CreateExitTriggers;
extern MapSettings TTYD64_kpa_136_Header;
extern EvtScript TTYD64_kpa_136_Script_SetupMusic;
extern NpcGroupList TTYD64_kpa_136_NpcGroupList_kpa136;
extern EvtScript TTYD64_kpa_136_Script_GotoMap_Exit1;
extern NpcSettings TTYD64_kpa_136_NpcSettings_Flame_3;
extern NpcSettings TTYD64_kpa_136_NpcSettings_Flame_2;
extern NpcSettings TTYD64_kpa_136_NpcSettings_Flame_1;
extern s32 TTYD64_kpa_136_IntTable_AnimationsTable[];
extern NpcSettings TTYD64_kpa_136_NpcSettings_SubFlame;
extern EntryList TTYD64_kpa_136_EntryList;
extern EvtScript TTYD64_kpa_136_Script_NpcAI_Flame3;
extern EvtScript TTYD64_kpa_136_Script_NpcAI_Flame1;
extern EvtScript TTYD64_kpa_136_Script_NpcAI_Flame2;
extern FireBarAISettings TTYD64_kpa_136_AISettings_Flame2;
extern FireBarAISettings TTYD64_kpa_136_AISettings_Flame1;
extern FireBarAISettings TTYD64_kpa_136_AISettings_Flame3;

// clang-format off
static s32 TTYD64_kpa_136_GetTattleMsg;

static s32 TTYD64_kpa_136_GetTattle(void) {
    return TTYD64_kpa_136_GetTattleMsg;
}

NpcData TTYD64_kpa_136_NpcGroup_Flame1[] = {
    {
        .id = 0,
        .settings = &TTYD64_kpa_136_NpcSettings_Flame_1,
        .pos = { -130.0f, 50.0f, 54.0f },
        .flags = 0x00000001,
        .init = (void*) 0x00004003,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00D40001, .walk = 0x00D40000, .run = 0x00D40000, .chase = 0x00D40000, .anim_4 = 0x00D40000, .anim_5 = 0x00D40000, .death = 0x00D40000, .hit = 0x00D40000, .anim_8 = 0x00D40000, .anim_9 = 0x00D40000, .anim_A = 0x00D40000, .anim_B = 0x00D40000, .anim_C = 0x00D40000, .anim_D = 0x00D40000, .anim_E = 0x00D40000, .anim_F = 0x00D40000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 1,
        .settings = &TTYD64_kpa_136_NpcSettings_SubFlame,
        .pos = { -130.0f, 50.0f, 54.0f },
        .flags = 0x00000001,
        .init = (void*) 0x00004003,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00D40001, .walk = 0x00D40000, .run = 0x00D40000, .chase = 0x00D40000, .anim_4 = 0x00D40000, .anim_5 = 0x00D40000, .death = 0x00D40000, .hit = 0x00D40000, .anim_8 = 0x00D40000, .anim_9 = 0x00D40000, .anim_A = 0x00D40000, .anim_B = 0x00D40000, .anim_C = 0x00D40000, .anim_D = 0x00D40000, .anim_E = 0x00D40000, .anim_F = 0x00D40000 },
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
        .settings = &TTYD64_kpa_136_NpcSettings_SubFlame,
        .pos = { -130.0f, 50.0f, 54.0f },
        .flags = 0x00000001,
        .init = (void*) 0x00004003,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00D40001, .walk = 0x00D40000, .run = 0x00D40000, .chase = 0x00D40000, .anim_4 = 0x00D40000, .anim_5 = 0x00D40000, .death = 0x00D40000, .hit = 0x00D40000, .anim_8 = 0x00D40000, .anim_9 = 0x00D40000, .anim_A = 0x00D40000, .anim_B = 0x00D40000, .anim_C = 0x00D40000, .anim_D = 0x00D40000, .anim_E = 0x00D40000, .anim_F = 0x00D40000 },
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
        .settings = &TTYD64_kpa_136_NpcSettings_SubFlame,
        .pos = { -130.0f, 50.0f, 54.0f },
        .flags = 0x00000001,
        .init = (void*) 0x00004003,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00D40001, .walk = 0x00D40000, .run = 0x00D40000, .chase = 0x00D40000, .anim_4 = 0x00D40000, .anim_5 = 0x00D40000, .death = 0x00D40000, .hit = 0x00D40000, .anim_8 = 0x00D40000, .anim_9 = 0x00D40000, .anim_A = 0x00D40000, .anim_B = 0x00D40000, .anim_C = 0x00D40000, .anim_D = 0x00D40000, .anim_E = 0x00D40000, .anim_F = 0x00D40000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_kpa_136_NpcGroup_Flame3[] = {
    {
        .id = 10,
        .settings = &TTYD64_kpa_136_NpcSettings_Flame_3,
        .pos = { -130.0f, 50.0f, 54.0f },
        .flags = 0x00000001,
        .init = (void*) 0x00004003,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00D40001, .walk = 0x00D40000, .run = 0x00D40000, .chase = 0x00D40000, .anim_4 = 0x00D40000, .anim_5 = 0x00D40000, .death = 0x00D40000, .hit = 0x00D40000, .anim_8 = 0x00D40000, .anim_9 = 0x00D40000, .anim_A = 0x00D40000, .anim_B = 0x00D40000, .anim_C = 0x00D40000, .anim_D = 0x00D40000, .anim_E = 0x00D40000, .anim_F = 0x00D40000 },
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
        .settings = &TTYD64_kpa_136_NpcSettings_SubFlame,
        .pos = { -130.0f, 50.0f, 54.0f },
        .flags = 0x00000001,
        .init = (void*) 0x00004003,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00D40001, .walk = 0x00D40000, .run = 0x00D40000, .chase = 0x00D40000, .anim_4 = 0x00D40000, .anim_5 = 0x00D40000, .death = 0x00D40000, .hit = 0x00D40000, .anim_8 = 0x00D40000, .anim_9 = 0x00D40000, .anim_A = 0x00D40000, .anim_B = 0x00D40000, .anim_C = 0x00D40000, .anim_D = 0x00D40000, .anim_E = 0x00D40000, .anim_F = 0x00D40000 },
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
        .settings = &TTYD64_kpa_136_NpcSettings_SubFlame,
        .pos = { -130.0f, 50.0f, 54.0f },
        .flags = 0x00000001,
        .init = (void*) 0x00004003,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00D40001, .walk = 0x00D40000, .run = 0x00D40000, .chase = 0x00D40000, .anim_4 = 0x00D40000, .anim_5 = 0x00D40000, .death = 0x00D40000, .hit = 0x00D40000, .anim_8 = 0x00D40000, .anim_9 = 0x00D40000, .anim_A = 0x00D40000, .anim_B = 0x00D40000, .anim_C = 0x00D40000, .anim_D = 0x00D40000, .anim_E = 0x00D40000, .anim_F = 0x00D40000 },
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
        .settings = &TTYD64_kpa_136_NpcSettings_SubFlame,
        .pos = { -130.0f, 50.0f, 54.0f },
        .flags = 0x00000001,
        .init = (void*) 0x00004003,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00D40001, .walk = 0x00D40000, .run = 0x00D40000, .chase = 0x00D40000, .anim_4 = 0x00D40000, .anim_5 = 0x00D40000, .death = 0x00D40000, .hit = 0x00D40000, .anim_8 = 0x00D40000, .anim_9 = 0x00D40000, .anim_A = 0x00D40000, .anim_B = 0x00D40000, .anim_C = 0x00D40000, .anim_D = 0x00D40000, .anim_E = 0x00D40000, .anim_F = 0x00D40000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_kpa_136_NpcGroup_Flame2[] = {
    {
        .id = 5,
        .settings = &TTYD64_kpa_136_NpcSettings_Flame_2,
        .pos = { -130.0f, 50.0f, 54.0f },
        .flags = 0x00000001,
        .init = (void*) 0x00004003,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00D40001, .walk = 0x00D40000, .run = 0x00D40000, .chase = 0x00D40000, .anim_4 = 0x00D40000, .anim_5 = 0x00D40000, .death = 0x00D40000, .hit = 0x00D40000, .anim_8 = 0x00D40000, .anim_9 = 0x00D40000, .anim_A = 0x00D40000, .anim_B = 0x00D40000, .anim_C = 0x00D40000, .anim_D = 0x00D40000, .anim_E = 0x00D40000, .anim_F = 0x00D40000 },
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
        .settings = &TTYD64_kpa_136_NpcSettings_SubFlame,
        .pos = { -130.0f, 50.0f, 54.0f },
        .flags = 0x00000001,
        .init = (void*) 0x00004003,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00D40001, .walk = 0x00D40000, .run = 0x00D40000, .chase = 0x00D40000, .anim_4 = 0x00D40000, .anim_5 = 0x00D40000, .death = 0x00D40000, .hit = 0x00D40000, .anim_8 = 0x00D40000, .anim_9 = 0x00D40000, .anim_A = 0x00D40000, .anim_B = 0x00D40000, .anim_C = 0x00D40000, .anim_D = 0x00D40000, .anim_E = 0x00D40000, .anim_F = 0x00D40000 },
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
        .settings = &TTYD64_kpa_136_NpcSettings_SubFlame,
        .pos = { -130.0f, 50.0f, 54.0f },
        .flags = 0x00000001,
        .init = (void*) 0x00004003,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00D40001, .walk = 0x00D40000, .run = 0x00D40000, .chase = 0x00D40000, .anim_4 = 0x00D40000, .anim_5 = 0x00D40000, .death = 0x00D40000, .hit = 0x00D40000, .anim_8 = 0x00D40000, .anim_9 = 0x00D40000, .anim_A = 0x00D40000, .anim_B = 0x00D40000, .anim_C = 0x00D40000, .anim_D = 0x00D40000, .anim_E = 0x00D40000, .anim_F = 0x00D40000 },
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
        .settings = &TTYD64_kpa_136_NpcSettings_SubFlame,
        .pos = { -130.0f, 50.0f, 54.0f },
        .flags = 0x00000001,
        .init = (void*) 0x00004003,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00D40001, .walk = 0x00D40000, .run = 0x00D40000, .chase = 0x00D40000, .anim_4 = 0x00D40000, .anim_5 = 0x00D40000, .death = 0x00D40000, .hit = 0x00D40000, .anim_8 = 0x00D40000, .anim_9 = 0x00D40000, .anim_A = 0x00D40000, .anim_B = 0x00D40000, .anim_C = 0x00D40000, .anim_D = 0x00D40000, .anim_E = 0x00D40000, .anim_F = 0x00D40000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_kpa_136_Script_EnterHorizontalPipe = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(HidePlayerShadow, 1)
    Call(ModifyColliderFlags, 0, LVarB, 0x7FFFFE00)
    Call(GetEntryID, LVar0)
    Call(TTYD64_Pipe_GetEntryCoords)
    Set(LVar5, LVar1)
    Set(LVar6, LVar2)
    Set(LVar7, LVar3)
    Add(LVar2, 2)
    Call(SetPlayerPos, LVar1, LVar2, LVar3)
    Call(InterpPlayerYaw, LVar4, 0)
    IfEq(LVar4, 90)
        Add(LVar5, 40)
    Else
        Sub(LVar5, 40)
    EndIf
    Call(UseSettingsFrom, 0, LVar5, LVar6, LVar7)
    Call(SetPanTarget, 0, LVar5, LVar6, LVar7)
    Call(SetCamSpeed, 0, Float(90.0))
    Call(PanToTarget, 0, 0, 1)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Call(DisablePartnerAI, 0)
        Call(EnableNpcShadow, -4, 0)
        Call(SetNpcPos, -4, 0, -1000, 0)
        Call(InterpNpcYaw, -4, LVar0, 0)
    EndIf
    Wait(1)
    Call(PlaySound, 355)
    Thread
        Wait(25)
        Call(HidePlayerShadow, 0)
    EndThread
    Call(SetPlayerImgFXFlags, 2304)
    Call(UpdatePlayerImgFX, 0x10002, 5, 3, 1, 1, 0)
    Loop(40)
        Call(TTYD64_Pipe_GetPointInFrontOfPlayer, Float(1.0))
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Thread
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Sub(LVar2, 3)
            Call(SetNpcPos, -4, LVar0, LVar1, LVar2)
            Call(EnableNpcShadow, -4, 1)
            Call(EnablePartnerAI)
        EndThread
    EndIf
    Wait(5)
    Call(UpdatePlayerImgFX, 0x10002, 0, 0, 0, 0, 0)
    Call(ModifyColliderFlags, 1, LVarB, 0x7FFFFE00)
    Call(DisablePlayerInput, 0)
    Call(DisablePlayerPhysics, 0)
    Call(PanToTarget, 0, 0, 0)
    Exec(LVarA)
    Return
    End
};

EvtScript TTYD64_kpa_136_Script_KillFlames = {
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Loop(15)
        Loop(LVar1)
            Call(SetNpcFlagBits, LVar0, 2, 1)
            Add(LVar0, 1)
        EndLoop
        Wait(1)
        Set(LVar0, LVarA)
        Set(LVar1, LVarB)
        Loop(LVar1)
            Call(SetNpcFlagBits, LVar0, 2, 0)
            Add(LVar0, 1)
        EndLoop
        Wait(1)
        Set(LVar0, LVarA)
        Set(LVar1, LVarB)
    EndLoop
    Call(GetNpcPos, LVar0, LVar1, LVar2, LVar3)
    Call(PlaySoundAt, 0xB000000A, 0, LVar1, LVar2, LVar3)
    Loop(10)
        Call(GetNpcPos, LVar0, LVar1, LVar2, LVar3)
        Call(RandInt, 50, LVar4)
        Sub(LVar4, 25)
        Call(RandInt, 30, LVar5)
        Add(LVar1, LVar4)
        Add(LVar2, LVar5)
        Call(PlayEffect_impl, 0, LVar1, LVar2, LVar3, 1, 20, 3, 2, 0, 0, 0, 0, 0, 0)
    EndLoop
    IfEq(LVarA, 0)
        IfEq(AreaFlag(20), 0)
            Set(AreaFlag(20), 1)
            Loop(5)
                Call(MakeItemEntity, 343, LVar1, LVar2, LVar3, 3, 0)
            EndLoop
        EndIf
    EndIf
    IfEq(LVarA, 5)
        IfEq(AreaFlag(21), 0)
            Set(AreaFlag(21), 1)
            Loop(5)
                Call(MakeItemEntity, 343, LVar1, LVar2, LVar3, 3, 0)
            EndLoop
        EndIf
    EndIf
    IfEq(LVarA, 10)
        IfEq(AreaFlag(22), 0)
            Set(AreaFlag(22), 1)
            Loop(5)
                Call(MakeItemEntity, 343, LVar1, LVar2, LVar3, 3, 0)
            EndLoop
        EndIf
    EndIf
    Call(RemoveEncounter, LVarA)
    Return
    End
};

EvtScript TTYD64_kpa_136_Script_EnterVerticalPipe = {
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(DisablePartnerAI, 0)
    Call(HidePlayerShadow, 1)
    Call(SetPlayerAnimation, 0x10000)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Call(EnableNpcShadow, -4, 0)
        Call(SetNpcPos, -4, 0, -1000, 0)
    EndIf
    Call(GetEntryID, LVar0)
    Call(TTYD64_Pipe_GetEntryCoords)
    Sub(LVar2, 40)
    Call(SetPlayerPos, LVar1, LVar2, LVar3)
    Call(InterpPlayerYaw, LVar4, 0)
    Call(PlaySound, 355)
    Call(SetPlayerImgFXFlags, 256)
    Call(UpdatePlayerImgFX, 0x10000, 5, 2, 1, 1, 0)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Loop(40)
        Add(LVar1, 1)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Wait(3)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, 0)
        Thread
            Call(DisablePartnerAI, 0)
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Sub(LVar2, 3)
            Call(SetNpcPos, -4, LVar0, LVar1, LVar2)
            Call(SetNpcFlagBits, -4, 2, 0)
            Call(EnablePartnerAI)
            Call(EnableNpcShadow, -4, 1)
        EndThread
    EndIf
    Wait(2)
    Call(UpdatePlayerImgFX, 0x10000, 0, 0, 0, 0, 0)
    Wait(1)
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Call(HidePlayerShadow, 0)
    Label(0)
    Call(TTYD64_Pipe_GetCurrentFloor)
    Wait(1)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Exec(LVarA)
    Return
    End
};

EvtScript TTYD64_kpa_136_Script_ExitHorizontalPipe = {
    Call(IsPlayerOnValidFloor, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(GetPlayerActionState, LVar0)
    IfEq(LVar0, 26)
        Return
    EndIf
    Call(GetPartnerInUse, LVar0)
    IfNe(LVar0, 0)
        Call(GetCurrentPartnerID, LVar1)
        IfNe(LVar1, 6)
            Return
        Else
            Call(InterruptUsePartner)
            Call(DisablePlayerInput, 1)
        EndIf
    Else
        Call(DisablePlayerInput, 1)
    EndIf
    SetGroup(27)
    Call(TTYD64_Pipe_SetAnimFlag)
    Call(DisablePlayerPhysics, 1)
    Call(ModifyColliderFlags, 0, LVarB, 0x7FFFFE00)
    Set(LVar0, LVarA)
    Call(TTYD64_Pipe_GetEntryCoords)
    Set(LVar5, LVar1)
    Set(LVar6, LVar2)
    Add(LVar6, 2)
    Set(LVar7, LVar3)
    Set(LVar8, LVar4)
    Add(LVar8, 180)
    IfGe(LVar4, 360)
        Sub(LVar4, 360)
    EndIf
    Call(InterpPlayerYaw, LVar8, 1)
    Wait(1)
    Call(PlaySound, 355)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(SetPlayerPos, LVar0, LVar6, LVar7)
    Call(SetPlayerAnimation, 0x10000)
    Call(SetPlayerImgFXFlags, 2048)
    Call(UpdatePlayerImgFX, 0x10000, 5, 3, 1, 1, 0)
    Thread
        Wait(8)
        Call(HidePlayerShadow, 1)
    EndThread
    Thread
        Wait(3)
        Loop(40)
            Call(TTYD64_Pipe_GetPointInFrontOfPlayer, Float(1.0))
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Wait(25)
    ExecWait(LVarC)
    Return
    End
};

EvtScript TTYD64_kpa_136_Script_ExitVerticalPipe = {
    Call(TTYD64_Pipe_CheckDownInput)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(GetPartnerInUse, LVar0)
    IfNe(LVar0, 0)
        Call(GetCurrentPartnerID, LVar1)
        IfNe(LVar1, 6)
            Return
        Else
            Call(InterruptUsePartner)
            Call(DisablePlayerInput, 1)
        EndIf
    Else
        Call(DisablePlayerInput, 1)
    EndIf
    SetGroup(27)
    Call(TTYD64_Pipe_SetAnimFlag)
    Call(DisablePlayerPhysics, 1)
    Call(HidePlayerShadow, 1)
    Set(LVar0, LVarA)
    Call(TTYD64_Pipe_GetEntryCoords)
    Call(PlayerMoveTo, LVar1, LVar3, 3)
    Set(LVar0, LVarA)
    Call(TTYD64_Pipe_GetEntryCoords)
    Call(SetPlayerPos, LVar1, LVar2, LVar3)
    Call(SetPlayerFlagBits, 0x200000, 1)
    Call(TTYD64_Pipe_GetCameraYaw)
    Call(InterpPlayerYaw, LVar0, 0)
    Wait(2)
    Call(SetPlayerFlagBits, 0x200000, 0)
    Call(PlaySound, 355)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Thread
        Wait(4)
        Loop(40)
            Sub(LVar1, 1)
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Call(SetPlayerImgFXFlags, 2048)
    Call(UpdatePlayerImgFX, 0x10002, 5, 2, 1, 1, 0)
    Wait(25)
    ExecWait(LVarC)
    Return
    End
};

EvtScript TTYD64_kpa_136_Script_UpdateFlamesAnimations = {
    Call(EnableNpcShadow, -1, 0)
    Call(SetNpcFlagBits, -1, 0, 1)
    Call(EnableNpcShadow, -1, 1)
    Thread
        Call(RandInt, 5, LVar0)
        Add(LVar0, 1)
        Wait(LVar0)
        Call(SetNpcAnimation, -1, 0xD40000)
        Wait(1)
        Call(SetNpcAnimation, -1, 0xD40001)
    EndThread
    Return
    End
};

EvtScript TTYD64_kpa_136_Script_Main = {
    Set(GameByte(425), 22)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_kpa_136_Script_SetupMusic)
    Exec(TTYD64_kpa_136_Script_EnterMap)
    Call(MakeNpcs, 1, (Bytecode) TTYD64_kpa_136_NpcGroupList_kpa136)
    Return
    End
};

EvtScript TTYD64_kpa_136_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Set(LVar0, (Bytecode) TTYD64_kpa_136_Script_CreateExitTriggers)
        Exec(EnterWalk)
    CaseEq(1)
        Set(LVarA, (Bytecode) TTYD64_kpa_136_Script_CreateExitTriggers)
        Exec(TTYD64_kpa_136_Script_EnterVerticalPipe)
    EndSwitch
    Wait(1)
    Return
    End
};

u8 TTYD64_kpa_136_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x37, 0x48, 0x41, 0x54, 0xF7, 0x41, 0xF7, 0x4D,
    0x45, 0x53, 0x53, 0xF7, 0x57, 0x41, 0x53, 0xF7, 0x4C, 0x45, 0x46, 0x54,
    0xF7, 0x41, 0x46, 0x54, 0x45, 0x52, 0xF7, 0x57, 0x45, 0xF0, 0x54, 0x55,
    0x52, 0x4E, 0x45, 0x44, 0xF7, 0x4F, 0x46, 0x46, 0xF7, 0x54, 0x48, 0x45,
    0xF7, 0x4C, 0x41, 0x56, 0x41, 0xF7, 0x4D, 0x41, 0x43, 0x48, 0x49, 0x4E,
    0x45, 0x0C, 0xF7, 0x54, 0x48, 0x45, 0xF0, 0x46, 0x4C, 0x4F, 0x4F, 0x52,
    0xF7, 0x53, 0x4D, 0x45, 0x4C, 0x4C, 0x53, 0xF7, 0x46, 0x55, 0x4E, 0x4E,
    0x59, 0x0C, 0xF7, 0x52, 0x49, 0x47, 0x48, 0x54, 0x1F, 0xF1, 0xFD
};

EvtScript TTYD64_kpa_136_Script_Exit0 = {
    SetGroup(27)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "kpa_12", 3)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_kpa_136_Script_Exit1 = {
    SetGroup(27)
    Set(LVarA, 1)
    Set(LVarB, 13)
    Set(LVarC, (Bytecode) TTYD64_kpa_136_Script_GotoMap_Exit1)
    ExecWait(TTYD64_kpa_136_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_kpa_136_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_kpa_136_Script_Exit0, 0x80000, 6, 1, 0)
    BindTrigger(TTYD64_kpa_136_Script_Exit1, 128, 13, 1, 0)
    Return
    End
};

MapSettings TTYD64_kpa_136_Header = {
    .main = &TTYD64_kpa_136_Script_Main,
    .entryList = &TTYD64_kpa_136_EntryList,
    .entryCount = 2,
    .background = NULL,
    .tattle = { .get = TTYD64_kpa_136_GetTattle },
};

EvtScript TTYD64_kpa_136_Script_SetupMusic = {
    Call(SetMusic, 0, 100, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

NpcGroupList TTYD64_kpa_136_NpcGroupList_kpa136 = {
    { .npcCount = 4, .npcs = TTYD64_kpa_136_NpcGroup_Flame1, .battle = 0x0006, .stage = 0 },
    { .npcCount = 4, .npcs = TTYD64_kpa_136_NpcGroup_Flame2, .battle = 0x0006, .stage = 0 },
    { .npcCount = 4, .npcs = TTYD64_kpa_136_NpcGroup_Flame3, .battle = 0x0006, .stage = 0 },
    {},
};

EvtScript TTYD64_kpa_136_Script_GotoMap_Exit1 = {
    Call(GotoMap, (Bytecode) "tyd_08", 0)
    Wait(100)
    Return
    End
};

NpcSettings TTYD64_kpa_136_NpcSettings_Flame_3 = {
    .defaultAnim = 0x00D40001,
    .height = 12,
    .radius = 20,
    .otherAI = &TTYD64_kpa_136_Script_UpdateFlamesAnimations,
    .onInteract = NULL,
    .ai = &TTYD64_kpa_136_Script_NpcAI_Flame3,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000F00,
    .unk_24 = 0,
    .level = 0,
    .actionFlags = 0,
};

NpcSettings TTYD64_kpa_136_NpcSettings_Flame_2 = {
    .defaultAnim = 0x00D40001,
    .height = 12,
    .radius = 20,
    .otherAI = &TTYD64_kpa_136_Script_UpdateFlamesAnimations,
    .onInteract = NULL,
    .ai = &TTYD64_kpa_136_Script_NpcAI_Flame2,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000F00,
    .unk_24 = 0,
    .level = 0,
    .actionFlags = 0,
};

NpcSettings TTYD64_kpa_136_NpcSettings_Flame_1 = {
    .defaultAnim = 0x00D40001,
    .height = 12,
    .radius = 20,
    .otherAI = &TTYD64_kpa_136_Script_UpdateFlamesAnimations,
    .onInteract = NULL,
    .ai = &TTYD64_kpa_136_Script_NpcAI_Flame1,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000F00,
    .unk_24 = 0,
    .level = 0,
    .actionFlags = 0,
};

s32 TTYD64_kpa_136_IntTable_AnimationsTable[] = {
    -1342177280, -1342177279, -1342177278, -1342177277, -1342177276, -1342177275, -1342177274, -1342177273, -1342177272, -1342177271, -1342177271
};

NpcSettings TTYD64_kpa_136_NpcSettings_SubFlame = {
    .defaultAnim = 0x00D40001,
    .height = 12,
    .radius = 20,
    .otherAI = &TTYD64_kpa_136_Script_UpdateFlamesAnimations,
    .onInteract = NULL,
    .ai = NULL,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000F00,
    .unk_24 = 0,
    .level = 0,
    .actionFlags = 0,
};

EntryList TTYD64_kpa_136_EntryList = {
    { -471.0f, 0.0f, -95.0f, -180.0f },
    { 253.0f, 102.0f, 16.0f, -90.0f },
};

EvtScript TTYD64_kpa_136_Script_NpcAI_Flame3 = {
    Call(kzn_04_FireBarAI_Main, Ref(TTYD64_kpa_136_AISettings_Flame3))
    Return
    End
};

EvtScript TTYD64_kpa_136_Script_NpcAI_Flame1 = {
    Call(kzn_04_FireBarAI_Main, Ref(TTYD64_kpa_136_AISettings_Flame1))
    Return
    End
};

EvtScript TTYD64_kpa_136_Script_NpcAI_Flame2 = {
    Call(kzn_04_FireBarAI_Main, Ref(TTYD64_kpa_136_AISettings_Flame2))
    Return
    End
};

FireBarAISettings TTYD64_kpa_136_AISettings_Flame2 = {
    .centerPos = { -8, 50, -18 },
    .rotRate = 8,
    .firstNpc = 5,
    .npcCount = 4,
    .callback = TTYD64_nm_kpa_136_FlameAI,
};

FireBarAISettings TTYD64_kpa_136_AISettings_Flame1 = {
    .centerPos = { -130, 50, 54 },
    .rotRate = 8,
    .firstNpc = 0,
    .npcCount = 4,
    .callback = TTYD64_nm_kpa_136_FlameAI,
};

FireBarAISettings TTYD64_kpa_136_AISettings_Flame3 = {
    .centerPos = { 116, 50, 54 },
    .rotRate = 8,
    .firstNpc = 10,
    .npcCount = 4,
    .callback = TTYD64_nm_kpa_136_FlameAI,
};

MapConfig TTYD64_mapcfg_kpa_136 = {
    .id = "kpa_136",
    .settings = &TTYD64_kpa_136_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 3,
};
// clang-format on

void TTYD64_nm_Install_kpa_136(void) {
    TTYD64_kpa_136_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_kpa_136_String_Tattle);
}
