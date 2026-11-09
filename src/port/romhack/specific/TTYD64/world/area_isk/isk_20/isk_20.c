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

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetPartnerInUse);
API_CALLABLE(GotoMap);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(ParentColliderToModel);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAt);
API_CALLABLE(PlaySoundAtCollider);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveEncounter);
API_CALLABLE(ResetFromLava);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(ShakeCam);
API_CALLABLE(TeleportPartnerToPlayer);
API_CALLABLE(TranslateGroup);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateColliderTransform);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseExitHeading);
API_CALLABLE(kzn_04_FireBarAI_Main);

extern NpcData TTYD64_isk_20_NpcGroup_Flame1[];
extern NpcData TTYD64_isk_20_NpcGroup_Flame4[];
extern NpcData TTYD64_isk_20_NpcGroup_Flame3[];
extern NpcData TTYD64_isk_20_NpcGroup_Flame2[];
extern EvtScript TTYD64_isk_20_Script_KillFlames;
extern EvtScript TTYD64_isk_20_Script_UpdatePillars;
extern EvtScript TTYD64_isk_20_Script_UpdateSpikes;
extern EvtScript TTYD64_isk_20_Script_DeadByPillar;
extern EvtScript TTYD64_isk_20_Script_EnterMap;
extern EvtScript TTYD64_isk_20_Script_Main;
extern EvtScript TTYD64_isk_20_Script_UpdateFlamesAnimations;
extern u8 TTYD64_isk_20_String_Tattle[];
extern EvtScript TTYD64_isk_20_Script_MakeEntities;
extern EvtScript TTYD64_isk_20_Script_Exit0;
extern MapSettings TTYD64_isk_20_Header;
extern NpcGroupList TTYD64_isk_20_NpcGroupList_isk20;
extern EvtScript TTYD64_isk_20_Script_Entity_Shine1;
extern EvtScript TTYD64_isk_20_Script_SetupMusic;
extern NpcSettings TTYD64_isk_20_NpcSettings_Flame_4;
extern NpcSettings TTYD64_isk_20_NpcSettings_Flame_3;
extern NpcSettings TTYD64_isk_20_NpcSettings_Flame_2;
extern NpcSettings TTYD64_isk_20_NpcSettings_Flame_1;
extern s32 TTYD64_isk_20_IntTable_AnimationsTable[];
extern NpcSettings TTYD64_isk_20_NpcSettings_SubFlame;
extern EvtScript TTYD64_isk_20_Script_CreateExitTriggers;
extern LavaReset TTYD64_isk_20_LaveReset_Pos[];
extern EvtScript TTYD64_isk_20_Script_NpcAI_Flame3;
extern EvtScript TTYD64_isk_20_Script_NpcAI_Flame4;
extern EvtScript TTYD64_isk_20_Script_NpcAI_Flame1;
extern EvtScript TTYD64_isk_20_Script_NpcAI_Flame2;
extern FireBarAISettings TTYD64_isk_20_AISettings_Flame2;
extern FireBarAISettings TTYD64_isk_20_AISettings_Flame1;
extern FireBarAISettings TTYD64_isk_20_AISettings_Flame4;
extern FireBarAISettings TTYD64_isk_20_AISettings_Flame3;
extern EntryList TTYD64_isk_20_EntryList;

// clang-format off
static s32 TTYD64_isk_20_GetTattleMsg;

static s32 TTYD64_isk_20_GetTattle(void) {
    return TTYD64_isk_20_GetTattleMsg;
}

NpcData TTYD64_isk_20_NpcGroup_Flame1[] = {
    {
        .id = 0,
        .settings = &TTYD64_isk_20_NpcSettings_Flame_1,
        .pos = { 335.0f, 25.0f, 45.0f },
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
        .settings = &TTYD64_isk_20_NpcSettings_SubFlame,
        .pos = { 335.0f, 25.0f, 45.0f },
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
        .settings = &TTYD64_isk_20_NpcSettings_SubFlame,
        .pos = { 335.0f, 25.0f, 45.0f },
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
        .settings = &TTYD64_isk_20_NpcSettings_SubFlame,
        .pos = { 335.0f, 25.0f, 45.0f },
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

NpcData TTYD64_isk_20_NpcGroup_Flame4[] = {
    {
        .id = 15,
        .settings = &TTYD64_isk_20_NpcSettings_Flame_4,
        .pos = { 335.0f, 25.0f, 45.0f },
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
        .id = 16,
        .settings = &TTYD64_isk_20_NpcSettings_SubFlame,
        .pos = { 335.0f, 25.0f, 45.0f },
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
        .id = 17,
        .settings = &TTYD64_isk_20_NpcSettings_SubFlame,
        .pos = { 335.0f, 25.0f, 45.0f },
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
        .id = 18,
        .settings = &TTYD64_isk_20_NpcSettings_SubFlame,
        .pos = { 335.0f, 25.0f, 45.0f },
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

NpcData TTYD64_isk_20_NpcGroup_Flame3[] = {
    {
        .id = 10,
        .settings = &TTYD64_isk_20_NpcSettings_Flame_3,
        .pos = { 335.0f, 25.0f, 45.0f },
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
        .settings = &TTYD64_isk_20_NpcSettings_SubFlame,
        .pos = { 335.0f, 25.0f, 45.0f },
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
        .settings = &TTYD64_isk_20_NpcSettings_SubFlame,
        .pos = { 335.0f, 25.0f, 45.0f },
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
        .settings = &TTYD64_isk_20_NpcSettings_SubFlame,
        .pos = { 335.0f, 25.0f, 45.0f },
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

NpcData TTYD64_isk_20_NpcGroup_Flame2[] = {
    {
        .id = 5,
        .settings = &TTYD64_isk_20_NpcSettings_Flame_2,
        .pos = { 335.0f, 25.0f, 45.0f },
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
        .settings = &TTYD64_isk_20_NpcSettings_SubFlame,
        .pos = { 335.0f, 25.0f, 45.0f },
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
        .settings = &TTYD64_isk_20_NpcSettings_SubFlame,
        .pos = { 335.0f, 25.0f, 45.0f },
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
        .settings = &TTYD64_isk_20_NpcSettings_SubFlame,
        .pos = { 335.0f, 25.0f, 45.0f },
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

EvtScript TTYD64_isk_20_Script_KillFlames = {
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
    IfEq(LVarA, 15)
        IfEq(AreaFlag(23), 0)
            Set(AreaFlag(23), 1)
            Loop(5)
                Call(MakeItemEntity, 343, LVar1, LVar2, LVar3, 3, 0)
            EndLoop
        EndIf
    EndIf
    Call(RemoveEncounter, LVarA)
    Return
    End
};

EvtScript TTYD64_isk_20_Script_UpdatePillars = {
    SetGroup(239)
    Set(LVar6, LVar0)
    Set(LVar7, LVar1)
    Set(LVar8, LVar2)
    Set(LVar9, LVar3)
    Set(LVar0, LVar7)
    Sub(LVar0, 1)
    Call(ParentColliderToModel, LVar6, LVar0)
    BindTrigger(TTYD64_isk_20_Script_DeadByPillar, 0x80000, LVar2, 1, 0)
    Loop(0)
        Wait(1)
        Call(TranslateGroup, LVar7, 0, 0, 0)
        Set(LVar2, 4)
        Call(MakeLerp, 0, -125, LVar2, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, LVar7, 0, LVar0, 0)
            Call(UpdateColliderTransform, LVar6)
            Sub(LVar2, 1)
            Wait(1)
            IfEq(LVar2, 1)
                Call(ModifyColliderFlags, 1, LVar8, 0x7FFFFE00)
                Call(ModifyColliderFlags, 0, LVar9, 0x7FFFFE00)
            EndIf
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(ModifyColliderFlags, 0, LVar8, 0x7FFFFE00)
        Call(ModifyColliderFlags, 1, LVar9, 0x7FFFFE00)
        Call(PlaySoundAtCollider, LVar6, 221, 0)
        Call(ShakeCam, 0, 0, 8, Float(0.400390625))
        Wait(10)
        Call(MakeLerp, -125, 0, 25, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateGroup, LVar7, 0, LVar0, 0)
            Call(UpdateColliderTransform, LVar6)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(40)
    EndLoop
    Return
    End
};

EvtScript TTYD64_isk_20_Script_UpdateSpikes = {
    SetGroup(239)
    Set(LVar6, LVar0)
    Set(LVar7, LVar1)
    Call(ParentColliderToModel, LVar6, LVar7)
    Call(ModifyColliderFlags, 3, LVar0, 2)
    Thread
        Call(ResetFromLava, (Bytecode) TTYD64_isk_20_LaveReset_Pos)
    EndThread
    Loop(0)
        Wait(1)
        Call(TranslateModel, LVar7, 0, 0, 0)
        Call(PlaySound, 8339)
        Call(MakeLerp, 0, 35, 4, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateModel, LVar7, 0, LVar0, 0)
            Call(UpdateColliderTransform, LVar6)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(10)
        Call(MakeLerp, 35, 0, 15, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(TranslateModel, LVar7, 0, LVar0, 0)
            Call(UpdateColliderTransform, LVar6)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Wait(30)
    EndLoop
    Return
    End
};

EvtScript TTYD64_isk_20_Script_DeadByPillar = {
    Call(DisablePlayerInput, 1)
    Call(SetPlayerAnimation, 0x10002)
    Call(SetPlayerAnimation, 0x1000F)
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(255.0))
    ExecWait(TTYD64_Script_FadeScreenOut)
    Call(GetPartnerInUse, LVar0)
    Switch(LVar0)
    CaseOrEq(9)
    CaseOrEq(6)
    CaseOrEq(8)
        Call(TTYD64_SetPlayerAnimFlagBits, PA_FLAG_INTERRUPT_USE_PARTNER, 1)
        EndCaseGroup
    EndSwitch
    Call(SetPlayerPos, -724, 25, 9)
    Call(TeleportPartnerToPlayer)
    Call(InterpPlayerYaw, 90, 0)
    Wait(5)
    Call(SetPlayerAnimation, 0x10002)
    Call(SetPlayerAnimation, 0x1000F)
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(5.0))
    Exec(TTYD64_Script_FadeScreenIn)
    Wait(10)
    Call(SetPlayerAnimation, 0x10030)
    Wait(15)
    Call(SetPlayerAnimation, 0x10031)
    Thread
        Call(PlaySound, 370)
        Wait(12)
        Call(PlaySound, 370)
    EndThread
    Wait(25)
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_isk_20_Script_EnterMap = {
    Thread
        Call(ModifyColliderFlags, 0, 17, 0x7FFFFE00)
        Call(ModifyColliderFlags, 0, 18, 0x7FFFFE00)
        Set(LVar0, 15)
        Set(LVar1, 24)
        Set(LVar2, 17)
        Set(LVar3, 19)
        Exec(TTYD64_isk_20_Script_UpdatePillars)
        Wait(40)
        Set(LVar0, 16)
        Set(LVar1, 27)
        Set(LVar2, 18)
        Set(LVar3, 20)
        Exec(TTYD64_isk_20_Script_UpdatePillars)
    EndThread
    Set(LVar0, 11)
    Set(LVar1, 19)
    Exec(TTYD64_isk_20_Script_UpdateSpikes)
    Wait(30)
    Set(LVar0, 12)
    Set(LVar1, 20)
    Exec(TTYD64_isk_20_Script_UpdateSpikes)
    Return
    End
};

EvtScript TTYD64_isk_20_Script_Main = {
    Set(GameByte(425), 11)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    ExecWait(TTYD64_isk_20_Script_MakeEntities)
    Exec(TTYD64_isk_20_Script_SetupMusic)
    Call(MakeNpcs, 1, (Bytecode) TTYD64_isk_20_NpcGroupList_isk20)
    Exec(TTYD64_isk_20_Script_EnterMap)
    Set(LVar0, (Bytecode) TTYD64_isk_20_Script_CreateExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

EvtScript TTYD64_isk_20_Script_UpdateFlamesAnimations = {
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

u8 TTYD64_isk_20_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x24, 0x41, 0x4D, 0x4E, 0xF7, 0x2D, 0x41, 0x52,
    0x49, 0x4F, 0x0C, 0xF7, 0x49, 0x54, 0xF7, 0x53, 0x45, 0x45, 0x4D, 0x53,
    0xF7, 0x54, 0x48, 0x41, 0x54, 0xF7, 0x57, 0x45, 0xF0, 0x45, 0x4E, 0x54,
    0x45, 0x52, 0x45, 0x44, 0xF7, 0x41, 0xF7, 0x43, 0x48, 0x41, 0x4D, 0x42,
    0x45, 0x52, 0xF7, 0x46, 0x55, 0x4C, 0x4C, 0xF7, 0x4F, 0x46, 0xF7, 0x54,
    0x52, 0x41, 0x50, 0x53, 0x0C, 0xF0, 0x42, 0x45, 0xF7, 0x43, 0x41, 0x52,
    0x45, 0x46, 0x55, 0x4C, 0x01, 0xF0, 0xF1, 0xFB, 0x29, 0xF7, 0x57, 0x4F,
    0x4E, 0x44, 0x45, 0x52, 0xF7, 0x57, 0x48, 0x41, 0x54, 0xF7, 0x4C, 0x49,
    0x45, 0x53, 0xF7, 0x41, 0x54, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x45, 0x4E,
    0x44, 0x0C, 0xF0, 0x29, 0xF7, 0x48, 0x4F, 0x50, 0x45, 0xF7, 0x49, 0x54,
    0x07, 0x53, 0xF7, 0x57, 0x4F, 0x52, 0x54, 0x48, 0xF7, 0x49, 0x54, 0x0E,
    0xF1, 0xFD
};

EvtScript TTYD64_isk_20_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SuperBlock), 918, 54, 12, -180, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(5006))
    Call(AssignScript, (Bytecode) TTYD64_isk_20_Script_Entity_Shine1)
    Return
    End
};

EvtScript TTYD64_isk_20_Script_Exit0 = {
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "sbk_02", 8)
    Wait(100)
    Return
    End
};

MapSettings TTYD64_isk_20_Header = {
    .main = &TTYD64_isk_20_Script_Main,
    .entryList = &TTYD64_isk_20_EntryList,
    .entryCount = 1,
    .background = NULL,
    .tattle = { .get = TTYD64_isk_20_GetTattle },
};

NpcGroupList TTYD64_isk_20_NpcGroupList_isk20 = {
    { .npcCount = 4, .npcs = TTYD64_isk_20_NpcGroup_Flame1, .battle = 0x0006, .stage = 0 },
    { .npcCount = 4, .npcs = TTYD64_isk_20_NpcGroup_Flame2, .battle = 0x0006, .stage = 0 },
    { .npcCount = 4, .npcs = TTYD64_isk_20_NpcGroup_Flame3, .battle = 0x0006, .stage = 0 },
    { .npcCount = 4, .npcs = TTYD64_isk_20_NpcGroup_Flame4, .battle = 0x0006, .stage = 0 },
    {},
};

EvtScript TTYD64_isk_20_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(5006))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_isk_20_Script_SetupMusic = {
    Call(SetMusic, 0, 24, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

NpcSettings TTYD64_isk_20_NpcSettings_Flame_4 = {
    .defaultAnim = 0x00D40001,
    .height = 12,
    .radius = 20,
    .otherAI = &TTYD64_isk_20_Script_UpdateFlamesAnimations,
    .onInteract = NULL,
    .ai = &TTYD64_isk_20_Script_NpcAI_Flame4,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000F00,
    .unk_24 = 0,
    .level = 0,
    .actionFlags = 0,
};

NpcSettings TTYD64_isk_20_NpcSettings_Flame_3 = {
    .defaultAnim = 0x00D40001,
    .height = 12,
    .radius = 20,
    .otherAI = &TTYD64_isk_20_Script_UpdateFlamesAnimations,
    .onInteract = NULL,
    .ai = &TTYD64_isk_20_Script_NpcAI_Flame3,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000F00,
    .unk_24 = 0,
    .level = 0,
    .actionFlags = 0,
};

NpcSettings TTYD64_isk_20_NpcSettings_Flame_2 = {
    .defaultAnim = 0x00D40001,
    .height = 12,
    .radius = 20,
    .otherAI = &TTYD64_isk_20_Script_UpdateFlamesAnimations,
    .onInteract = NULL,
    .ai = &TTYD64_isk_20_Script_NpcAI_Flame2,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000F00,
    .unk_24 = 0,
    .level = 0,
    .actionFlags = 0,
};

NpcSettings TTYD64_isk_20_NpcSettings_Flame_1 = {
    .defaultAnim = 0x00D40001,
    .height = 12,
    .radius = 20,
    .otherAI = &TTYD64_isk_20_Script_UpdateFlamesAnimations,
    .onInteract = NULL,
    .ai = &TTYD64_isk_20_Script_NpcAI_Flame1,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000F00,
    .unk_24 = 0,
    .level = 0,
    .actionFlags = 0,
};

s32 TTYD64_isk_20_IntTable_AnimationsTable[] = {
    -1342177280, -1342177279, -1342177278, -1342177277, -1342177276, -1342177275, -1342177274, -1342177273, -1342177272, -1342177271, -1342177271
};

NpcSettings TTYD64_isk_20_NpcSettings_SubFlame = {
    .defaultAnim = 0x00D40001,
    .height = 12,
    .radius = 20,
    .otherAI = &TTYD64_isk_20_Script_UpdateFlamesAnimations,
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

EvtScript TTYD64_isk_20_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_isk_20_Script_Exit0, 0x80000, 23, 1, 0)
    Return
    End
};

LavaReset TTYD64_isk_20_LaveReset_Pos[] = {
    { .colliderID = 10, .pos = { -724.0f, 25.0f, 9.0f } },
    { .colliderID = -1 },
};

EvtScript TTYD64_isk_20_Script_NpcAI_Flame3 = {
    Call(kzn_04_FireBarAI_Main, Ref(TTYD64_isk_20_AISettings_Flame3))
    Return
    End
};

EvtScript TTYD64_isk_20_Script_NpcAI_Flame4 = {
    Call(kzn_04_FireBarAI_Main, Ref(TTYD64_isk_20_AISettings_Flame4))
    Return
    End
};

EvtScript TTYD64_isk_20_Script_NpcAI_Flame1 = {
    Call(kzn_04_FireBarAI_Main, Ref(TTYD64_isk_20_AISettings_Flame1))
    Return
    End
};

EvtScript TTYD64_isk_20_Script_NpcAI_Flame2 = {
    Call(kzn_04_FireBarAI_Main, Ref(TTYD64_isk_20_AISettings_Flame2))
    Return
    End
};

FireBarAISettings TTYD64_isk_20_AISettings_Flame2 = {
    .centerPos = { 425, 25, -24 },
    .rotRate = 8,
    .firstNpc = 5,
    .npcCount = 4,
    .callback = TTYD64_nm_isk_20_FlameAI,
};

FireBarAISettings TTYD64_isk_20_AISettings_Flame1 = {
    .centerPos = { 335, 25, 45 },
    .rotRate = 8,
    .firstNpc = 0,
    .npcCount = 4,
    .callback = TTYD64_nm_isk_20_FlameAI,
};

FireBarAISettings TTYD64_isk_20_AISettings_Flame4 = {
    .centerPos = { 594, 25, -25 },
    .rotRate = 8,
    .firstNpc = 15,
    .npcCount = 4,
    .callback = TTYD64_nm_isk_20_FlameAI,
};

FireBarAISettings TTYD64_isk_20_AISettings_Flame3 = {
    .centerPos = { 514, 25, 46 },
    .rotRate = 8,
    .firstNpc = 10,
    .npcCount = 4,
    .callback = TTYD64_nm_isk_20_FlameAI,
};

EntryList TTYD64_isk_20_EntryList = {
    { -835.0f, 0.0f, 52.0f, 0.0f },
};

MapConfig TTYD64_mapcfg_isk_20 = {
    .id = "isk_20",
    .settings = &TTYD64_isk_20_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_isk_20(void) {
    TTYD64_isk_20_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_isk_20_String_Tattle);
}
