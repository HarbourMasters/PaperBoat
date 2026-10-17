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
#include "port/romhack/specific/TTYD64/newmaps_tyd_pit/tp.h"

API_CALLABLE(kpa_50_GetEncounterEnemyIsOwner);
API_CALLABLE(kpa_50_ProjectileAI_Main);
API_CALLABLE(kpa_50_ProjectileAI_Reflect);
API_CALLABLE(kpa_50_RangedAttackAI_Main);

extern NpcData TTYD64_imp_HammerBros_Npc_HammerBros[];
extern NpcData TTYD64_imp_HammerBros_Npc_DarkHammerBros[];
extern EvtScript TTYD64_imp_HammerBros_Script_80242028_kpa_50;
extern EvtScript TTYD64_imp_HammerBros_Script_80241DF0_kpa_50;
extern EvtScript TTYD64_imp_HammerBros_Script_NpcAI_80241EF0_kpa_50;
extern EvtScript TTYD64_imp_HammerBros_Script_NpcAI_80241FBC_kpa_50;
extern MobileAISettings TTYD64_imp_HammerBros_AISettings_80241EC0_kpa_50;
extern MobileAISettings TTYD64_imp_HammerBros_AISettings_80241F8C_kpa_50;
extern NpcSettings TTYD64_imp_HammerBros_NpcSettings_802421F0_kpa_50;
extern NpcSettings TTYD64_imp_HammerBros_NpcSettings_80241F60_kpa_50;
extern EvtScript TTYD64_imp_HammerBros_Script_NpcAI_80242018_kpa_50;
extern AnimID TTYD64_imp_HammerBros_ExtraAnimationList_8024221C_kpa_50[];
extern AnimID TTYD64_imp_HammerBros_ExtraAnimationList_DarkKoopa[];

// clang-format off
NpcData TTYD64_imp_HammerBros_Npc_HammerBros[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_HammerBros_NpcSettings_80241F60_kpa_50,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 140, 5, 0 }, { 163, 5, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 4, 16383 }, { 9830, 19660, 4, 16383 }, { 16383, 16383, 4, 13106 }, { 26213, 13106, 4, 13106 }, { 32767, 9830, 4, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 3, 13106 }, { 9830, 13106, 3, 13106 }, { 16383, 13106, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 50, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 220, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x005A0002, .walk = 0x005A0004, .run = 0x005A0007, .chase = 0x005A0007, .anim_4 = 0x005A0002, .anim_5 = 0x005A0002, .death = 0x005A000E, .hit = 0x005A000E, .anim_8 = 0x005A0018, .anim_9 = 0x005A0019, .anim_A = 0x005A0002, .anim_B = 0x005A0002, .anim_C = 0x005A0002, .anim_D = 0x005A0002, .anim_E = 0x005A0002, .anim_F = 0x005A0002 },
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
        .settings = &TTYD64_imp_HammerBros_NpcSettings_802421F0_kpa_50,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x005A000D, .walk = 0x005A000D, .run = 0x005A000D, .chase = 0x005A000D, .anim_4 = 0x005A000D, .anim_5 = 0x005A000D, .death = 0x005A000D, .hit = 0x005A000D, .anim_8 = 0x005A000D, .anim_9 = 0x005A000D, .anim_A = 0x005A000D, .anim_B = 0x005A000D, .anim_C = 0x005A000D, .anim_D = 0x005A000D, .anim_E = 0x005A000D, .anim_F = 0x005A000D },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_HammerBros_ExtraAnimationList_8024221C_kpa_50,
        .tattle = 0,
    },
    {
        .id = 2,
        .settings = &TTYD64_imp_HammerBros_NpcSettings_802421F0_kpa_50,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x005A000D, .walk = 0x005A000D, .run = 0x005A000D, .chase = 0x005A000D, .anim_4 = 0x005A000D, .anim_5 = 0x005A000D, .death = 0x005A000D, .hit = 0x005A000D, .anim_8 = 0x005A000D, .anim_9 = 0x005A000D, .anim_A = 0x005A000D, .anim_B = 0x005A000D, .anim_C = 0x005A000D, .anim_D = 0x005A000D, .anim_E = 0x005A000D, .anim_F = 0x005A000D },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_HammerBros_ExtraAnimationList_8024221C_kpa_50,
        .tattle = 0,
    },
    {
        .id = 3,
        .settings = &TTYD64_imp_HammerBros_NpcSettings_802421F0_kpa_50,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x005A000D, .walk = 0x005A000D, .run = 0x005A000D, .chase = 0x005A000D, .anim_4 = 0x005A000D, .anim_5 = 0x005A000D, .death = 0x005A000D, .hit = 0x005A000D, .anim_8 = 0x005A000D, .anim_9 = 0x005A000D, .anim_A = 0x005A000D, .anim_B = 0x005A000D, .anim_C = 0x005A000D, .anim_D = 0x005A000D, .anim_E = 0x005A000D, .anim_F = 0x005A000D },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_HammerBros_ExtraAnimationList_8024221C_kpa_50,
        .tattle = 0,
    },
    {
        .id = 4,
        .settings = &TTYD64_imp_HammerBros_NpcSettings_802421F0_kpa_50,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x005A000D, .walk = 0x005A000D, .run = 0x005A000D, .chase = 0x005A000D, .anim_4 = 0x005A000D, .anim_5 = 0x005A000D, .death = 0x005A000D, .hit = 0x005A000D, .anim_8 = 0x005A000D, .anim_9 = 0x005A000D, .anim_A = 0x005A000D, .anim_B = 0x005A000D, .anim_C = 0x005A000D, .anim_D = 0x005A000D, .anim_E = 0x005A000D, .anim_F = 0x005A000D },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_HammerBros_ExtraAnimationList_8024221C_kpa_50,
        .tattle = 0,
    },
    {
        .id = 5,
        .settings = &TTYD64_imp_HammerBros_NpcSettings_802421F0_kpa_50,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x005A000D, .walk = 0x005A000D, .run = 0x005A000D, .chase = 0x005A000D, .anim_4 = 0x005A000D, .anim_5 = 0x005A000D, .death = 0x005A000D, .hit = 0x005A000D, .anim_8 = 0x005A000D, .anim_9 = 0x005A000D, .anim_A = 0x005A000D, .anim_B = 0x005A000D, .anim_C = 0x005A000D, .anim_D = 0x005A000D, .anim_E = 0x005A000D, .anim_F = 0x005A000D },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_HammerBros_ExtraAnimationList_8024221C_kpa_50,
        .tattle = 0,
    },
    {
        .id = 6,
        .settings = &TTYD64_imp_HammerBros_NpcSettings_802421F0_kpa_50,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x005A000D, .walk = 0x005A000D, .run = 0x005A000D, .chase = 0x005A000D, .anim_4 = 0x005A000D, .anim_5 = 0x005A000D, .death = 0x005A000D, .hit = 0x005A000D, .anim_8 = 0x005A000D, .anim_9 = 0x005A000D, .anim_A = 0x005A000D, .anim_B = 0x005A000D, .anim_C = 0x005A000D, .anim_D = 0x005A000D, .anim_E = 0x005A000D, .anim_F = 0x005A000D },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_HammerBros_ExtraAnimationList_8024221C_kpa_50,
        .tattle = 0,
    },
};

NpcData TTYD64_imp_HammerBros_Npc_DarkHammerBros[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_HammerBros_NpcSettings_80241F60_kpa_50,
        .pos = { 17.0f, 0.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 140, 5, 0 }, { 163, 5, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 4, 16383 }, { 9830, 19660, 4, 16383 }, { 16383, 16383, 4, 13106 }, { 26213, 13106, 4, 13106 }, { 32767, 9830, 4, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 3, 13106 }, { 9830, 13106, 3, 13106 }, { 16383, 13106, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 0, .centerPos.z = 93, .wanderSize.x = 50, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 0, .detectPos.z = 93, .detectSize.x = 300, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x005A0102, .walk = 0x005A0104, .run = 0x005A0107, .chase = 0x005A0107, .anim_4 = 0x005A0102, .anim_5 = 0x005A0102, .death = 0x005A010E, .hit = 0x005A010E, .anim_8 = 0x005A0118, .anim_9 = 0x005A0119, .anim_A = 0x005A0102, .anim_B = 0x005A0102, .anim_C = 0x005A0102, .anim_D = 0x005A0102, .anim_E = 0x005A0102, .anim_F = 0x005A0102 },
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
        .settings = &TTYD64_imp_HammerBros_NpcSettings_802421F0_kpa_50,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x005A010D, .walk = 0x005A010D, .run = 0x005A010D, .chase = 0x005A010D, .anim_4 = 0x005A010D, .anim_5 = 0x005A010D, .death = 0x005A010D, .hit = 0x005A010D, .anim_8 = 0x005A010D, .anim_9 = 0x005A010D, .anim_A = 0x005A010D, .anim_B = 0x005A010D, .anim_C = 0x005A010D, .anim_D = 0x005A010D, .anim_E = 0x005A010D, .anim_F = 0x005A010D },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_HammerBros_ExtraAnimationList_DarkKoopa,
        .tattle = 0,
    },
    {
        .id = 2,
        .settings = &TTYD64_imp_HammerBros_NpcSettings_802421F0_kpa_50,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x005A010D, .walk = 0x005A010D, .run = 0x005A010D, .chase = 0x005A010D, .anim_4 = 0x005A010D, .anim_5 = 0x005A010D, .death = 0x005A010D, .hit = 0x005A010D, .anim_8 = 0x005A010D, .anim_9 = 0x005A010D, .anim_A = 0x005A010D, .anim_B = 0x005A010D, .anim_C = 0x005A010D, .anim_D = 0x005A010D, .anim_E = 0x005A010D, .anim_F = 0x005A010D },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_HammerBros_ExtraAnimationList_DarkKoopa,
        .tattle = 0,
    },
    {
        .id = 3,
        .settings = &TTYD64_imp_HammerBros_NpcSettings_802421F0_kpa_50,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x005A010D, .walk = 0x005A010D, .run = 0x005A010D, .chase = 0x005A010D, .anim_4 = 0x005A010D, .anim_5 = 0x005A010D, .death = 0x005A010D, .hit = 0x005A010D, .anim_8 = 0x005A010D, .anim_9 = 0x005A010D, .anim_A = 0x005A010D, .anim_B = 0x005A010D, .anim_C = 0x005A010D, .anim_D = 0x005A010D, .anim_E = 0x005A010D, .anim_F = 0x005A010D },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_HammerBros_ExtraAnimationList_DarkKoopa,
        .tattle = 0,
    },
    {
        .id = 4,
        .settings = &TTYD64_imp_HammerBros_NpcSettings_802421F0_kpa_50,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x005A010D, .walk = 0x005A010D, .run = 0x005A010D, .chase = 0x005A010D, .anim_4 = 0x005A010D, .anim_5 = 0x005A010D, .death = 0x005A010D, .hit = 0x005A010D, .anim_8 = 0x005A010D, .anim_9 = 0x005A010D, .anim_A = 0x005A010D, .anim_B = 0x005A010D, .anim_C = 0x005A010D, .anim_D = 0x005A010D, .anim_E = 0x005A010D, .anim_F = 0x005A010D },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_HammerBros_ExtraAnimationList_DarkKoopa,
        .tattle = 0,
    },
    {
        .id = 5,
        .settings = &TTYD64_imp_HammerBros_NpcSettings_802421F0_kpa_50,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x005A010D, .walk = 0x005A010D, .run = 0x005A010D, .chase = 0x005A010D, .anim_4 = 0x005A010D, .anim_5 = 0x005A010D, .death = 0x005A010D, .hit = 0x005A010D, .anim_8 = 0x005A010D, .anim_9 = 0x005A010D, .anim_A = 0x005A010D, .anim_B = 0x005A010D, .anim_C = 0x005A010D, .anim_D = 0x005A010D, .anim_E = 0x005A010D, .anim_F = 0x005A010D },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_HammerBros_ExtraAnimationList_DarkKoopa,
        .tattle = 0,
    },
    {
        .id = 6,
        .settings = &TTYD64_imp_HammerBros_NpcSettings_802421F0_kpa_50,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = -1000, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = -1000, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x005A010D, .walk = 0x005A010D, .run = 0x005A010D, .chase = 0x005A010D, .anim_4 = 0x005A010D, .anim_5 = 0x005A010D, .death = 0x005A010D, .hit = 0x005A010D, .anim_8 = 0x005A010D, .anim_9 = 0x005A010D, .anim_A = 0x005A010D, .anim_B = 0x005A010D, .anim_C = 0x005A010D, .anim_D = 0x005A010D, .anim_E = 0x005A010D, .anim_F = 0x005A010D },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = TTYD64_imp_HammerBros_ExtraAnimationList_DarkKoopa,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_HammerBros_Script_80242028_kpa_50 = {
    Call(kpa_50_GetEncounterEnemyIsOwner)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(BindNpcAI, -1, (Bytecode) TTYD64_imp_HammerBros_Script_NpcAI_80242018_kpa_50)
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
    CaseOrEq(4)
    CaseOrEq(3)
        Call(SetSelfVar, 0, 3)
        Call(kpa_50_ProjectileAI_Reflect)
        IfEq(LVar0, 0)
            Return
        EndIf
        EndCaseGroup
    CaseOrEq(2)
    CaseOrEq(6)
        Call(SetSelfVar, 0, 4)
        Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 7, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(SetNpcPos, -1, 0, -1000, 0)
        Call(SetSelfVar, 0, 0)
        EndCaseGroup
    CaseDefault
        Call(SetBattleAsScripted)
        EndCaseGroup
    EndSwitch
    Call(BindNpcAI, -1, (Bytecode) TTYD64_imp_HammerBros_Script_NpcAI_80241FBC_kpa_50)
    Return
    End
};

EvtScript TTYD64_imp_HammerBros_Script_80241DF0_kpa_50 = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Call(SetSelfVar, 0, 5)
        Call(RemoveNpc, -1)
    CaseEq(2)
        Call(SetNpcPos, -1, 0, -1000, 0)
        Call(OnPlayerFled, 1)
    CaseEq(3)
        Call(SetEnemyFlagBits, -1, 16, 1)
        Call(RemoveNpc, -1)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_imp_HammerBros_Script_NpcAI_80241EF0_kpa_50 = {
    Call(SetSelfVar, 0, 70)
    Call(SetSelfVar, 1, 3)
    Call(SetSelfVar, 2, 3)
    Call(SetSelfVar, 3, 6)
    Call(kpa_50_RangedAttackAI_Main, Ref(TTYD64_imp_HammerBros_AISettings_80241EC0_kpa_50))
    Return
    End
};

EvtScript TTYD64_imp_HammerBros_Script_NpcAI_80241FBC_kpa_50 = {
    Call(SetSelfVar, 0, 0)
    Call(SetSelfVar, 1, 3)
    Call(SetSelfVar, 2, 20)
    Call(kpa_50_ProjectileAI_Main, Ref(TTYD64_imp_HammerBros_AISettings_80241F8C_kpa_50))
    Return
    End
};

MobileAISettings TTYD64_imp_HammerBros_AISettings_80241EC0_kpa_50 = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 120.0f,
    .alertOffsetDist = 20.0f,
    .playerSearchInterval = 5,
    .chaseSpeed = 3.0f,
    .chaseTurnRate = 90,
    .chaseUpdateInterval = 3,
    .chaseRadius = 140.0f,
    .chaseOffsetDist = 20.0f,
    .unk_AI_2C = 0,
};

MobileAISettings TTYD64_imp_HammerBros_AISettings_80241F8C_kpa_50 = {
    .moveSpeed = 5.4000001f,
    .moveTime = 0,
    .waitTime = 0,
    .alertRadius = 13.0f,
    .alertOffsetDist = 1.39999998f,
    .playerSearchInterval = -1,
    .chaseSpeed = 0.0f,
    .chaseTurnRate = 0,
    .chaseUpdateInterval = 0,
    .chaseRadius = 0.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 0,
};

NpcSettings TTYD64_imp_HammerBros_NpcSettings_802421F0_kpa_50 = {
    .defaultAnim = 0x00000000,
    .height = 12,
    .radius = 12,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_HammerBros_Script_NpcAI_80241FBC_kpa_50,
    .onHit = TTYD64_imp_HammerBros_Script_80242028_kpa_50,
    .aux = NULL,
    .onDefeat = TTYD64_imp_HammerBros_Script_80241DF0_kpa_50,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 0,
    .actionFlags = 8,
};

NpcSettings TTYD64_imp_HammerBros_NpcSettings_80241F60_kpa_50 = {
    .defaultAnim = 0x00000000,
    .height = 36,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_HammerBros_Script_NpcAI_80241EF0_kpa_50,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 27,
    .actionFlags = 0,
};

EvtScript TTYD64_imp_HammerBros_Script_NpcAI_80242018_kpa_50 = {
    Return
    End
};

AnimID TTYD64_imp_HammerBros_ExtraAnimationList_8024221C_kpa_50[] = {
    0x005A000D, -1
};

AnimID TTYD64_imp_HammerBros_ExtraAnimationList_DarkKoopa[] = {
    0x005A010D, -1
};
// clang-format on

void TTYD64_tp_Install_imp_HammerBros(void) {
}
