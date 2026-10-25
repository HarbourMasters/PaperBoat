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
#include "port/romhack/specific/TTYD64/world/tp.h"

API_CALLABLE(flo_13_SpinyAI_Main);
API_CALLABLE(flo_17_LakituAI_Main);

extern NpcData TTYD64_imp_Lakitu_Npc_DarkLakitu[];
extern NpcData TTYD64_imp_Lakitu_Npc_SpinyA[];
extern NpcData TTYD64_imp_Lakitu_Npc_SpinyB[];
extern NpcData TTYD64_imp_Lakitu_Npc_SpinyC[];
extern NpcData TTYD64_imp_Lakitu_Npc_SpinyD[];
extern NpcData TTYD64_imp_Lakitu_Npc_Lakitu[];
extern NpcData TTYD64_imp_Lakitu_Npc_BlueSpinyD[];
extern NpcData TTYD64_imp_Lakitu_Npc_BlueSpinyC[];
extern NpcData TTYD64_imp_Lakitu_Npc_BlueSpinyB[];
extern NpcData TTYD64_imp_Lakitu_Npc_BlueSpinyA[];
extern EvtScript TTYD64_imp_Lakitu_Script_802442B0_flo_13;
extern EvtScript TTYD64_imp_Lakitu_Script_NpcAI_80244174_flo_13;
extern EvtScript TTYD64_imp_Lakitu_Script_NpcAI_80244240_flo_13_BlueSpiny;
extern EvtScript TTYD64_imp_Lakitu_Script_NpcAI_80244240_flo_13;
extern MobileAISettings TTYD64_imp_Lakitu_AISettings_80244144_flo_13;
extern MobileAISettings TTYD64_imp_Lakitu_AISettings_80244210_flo_13;
extern NpcSettings TTYD64_imp_Lakitu_NpcSettings_802441E4_flo_13;
extern NpcSettings TTYD64_imp_Lakitu_NpcSettings_8024437C_flo_13_BlueSpiny;
extern NpcSettings TTYD64_imp_Lakitu_NpcSettings_8024437C_flo_13;
extern EvtScript TTYD64_imp_Lakitu_Script_Init_802463E8_flo_13;

// clang-format off
NpcData TTYD64_imp_Lakitu_Npc_DarkLakitu[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_Lakitu_NpcSettings_802441E4_flo_13,
        .pos = { 17.0f, 64.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 37, .itemDrops = { { 140, 2, 0 }, { 163, 2, 0 }, { 130, 2, 0 }, { 146, 2, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 3, 13106 }, { 9830, 13106, 3, 13106 }, { 16383, 13106, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 64, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 64, .detectPos.z = 93, .detectSize.x = 220, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00490101, .walk = 0x00490102, .run = 0x00490103, .chase = 0x00490103, .anim_4 = 0x00490101, .anim_5 = 0x00490101, .death = 0x00490104, .hit = 0x00490104, .anim_8 = 0x00490103, .anim_9 = 0x00490101, .anim_A = 0x00490101, .anim_B = 0x00490101, .anim_C = 0x00490101, .anim_D = 0x00490101, .anim_E = 0x00490101, .anim_F = 0x00490101 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_imp_Lakitu_Npc_SpinyA[] = {
    {
        .id = 50,
        .settings = &TTYD64_imp_Lakitu_NpcSettings_8024437C_flo_13,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00000404,
        .init = TTYD64_imp_Lakitu_Script_Init_802463E8_flo_13,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x004A0001, .walk = 0x004A0003, .run = 0x004A0004, .chase = 0x004A0004, .anim_4 = 0x004A0001, .anim_5 = 0x004A0001, .death = 0x004A0009, .hit = 0x004A0009, .anim_8 = 0x004A0006, .anim_9 = 0x004A0008, .anim_A = 0x004A0007, .anim_B = 0x004A0001, .anim_C = 0x004A0001, .anim_D = 0x004A0001, .anim_E = 0x004A0001, .anim_F = 0x004A0001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_imp_Lakitu_Npc_SpinyB[] = {
    {
        .id = 51,
        .settings = &TTYD64_imp_Lakitu_NpcSettings_8024437C_flo_13,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00000404,
        .init = TTYD64_imp_Lakitu_Script_Init_802463E8_flo_13,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x004A0001, .walk = 0x004A0003, .run = 0x004A0004, .chase = 0x004A0004, .anim_4 = 0x004A0001, .anim_5 = 0x004A0001, .death = 0x004A0009, .hit = 0x004A0009, .anim_8 = 0x004A0006, .anim_9 = 0x004A0008, .anim_A = 0x004A0007, .anim_B = 0x004A0001, .anim_C = 0x004A0001, .anim_D = 0x004A0001, .anim_E = 0x004A0001, .anim_F = 0x004A0001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_imp_Lakitu_Npc_SpinyC[] = {
    {
        .id = 52,
        .settings = &TTYD64_imp_Lakitu_NpcSettings_8024437C_flo_13,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00000404,
        .init = TTYD64_imp_Lakitu_Script_Init_802463E8_flo_13,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x004A0001, .walk = 0x004A0003, .run = 0x004A0004, .chase = 0x004A0004, .anim_4 = 0x004A0001, .anim_5 = 0x004A0001, .death = 0x004A0009, .hit = 0x004A0009, .anim_8 = 0x004A0006, .anim_9 = 0x004A0008, .anim_A = 0x004A0007, .anim_B = 0x004A0001, .anim_C = 0x004A0001, .anim_D = 0x004A0001, .anim_E = 0x004A0001, .anim_F = 0x004A0001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_imp_Lakitu_Npc_SpinyD[] = {
    {
        .id = 53,
        .settings = &TTYD64_imp_Lakitu_NpcSettings_8024437C_flo_13,
        .pos = { 0.0f, -1000.0f, 2.0f },
        .flags = 0x00000404,
        .init = TTYD64_imp_Lakitu_Script_Init_802463E8_flo_13,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 2, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 2, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x004A0001, .walk = 0x004A0003, .run = 0x004A0004, .chase = 0x004A0004, .anim_4 = 0x004A0001, .anim_5 = 0x004A0001, .death = 0x004A0009, .hit = 0x004A0009, .anim_8 = 0x004A0006, .anim_9 = 0x004A0008, .anim_A = 0x004A0007, .anim_B = 0x004A0001, .anim_C = 0x004A0001, .anim_D = 0x004A0001, .anim_E = 0x004A0001, .anim_F = 0x004A0001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_imp_Lakitu_Npc_Lakitu[] = {
    {
        .id = 0,
        .settings = &TTYD64_imp_Lakitu_NpcSettings_802441E4_flo_13,
        .pos = { 17.0f, 64.0f, 93.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x80, .itemDropChance = 37, .itemDrops = { { 140, 2, 0 }, { 163, 2, 0 }, { 130, 2, 0 }, { 146, 2, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 3, 13106 }, { 9830, 13106, 3, 13106 }, { 16383, 13106, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 17, .centerPos.y = 64, .centerPos.z = 93, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 17, .detectPos.y = 64, .detectPos.z = 93, .detectSize.x = 250, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x00490001, .walk = 0x00490002, .run = 0x00490003, .chase = 0x00490003, .anim_4 = 0x00490001, .anim_5 = 0x00490001, .death = 0x00490004, .hit = 0x00490004, .anim_8 = 0x00490003, .anim_9 = 0x00490001, .anim_A = 0x00490001, .anim_B = 0x00490001, .anim_C = 0x00490001, .anim_D = 0x00490001, .anim_E = 0x00490001, .anim_F = 0x00490001 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_imp_Lakitu_Npc_BlueSpinyD[] = {
    {
        .id = 53,
        .settings = &TTYD64_imp_Lakitu_NpcSettings_8024437C_flo_13_BlueSpiny,
        .pos = { 0.0f, -1000.0f, 2.0f },
        .flags = 0x00000404,
        .init = TTYD64_imp_Lakitu_Script_Init_802463E8_flo_13,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 2, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 2, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x004A0101, .walk = 0x004A0103, .run = 0x004A0104, .chase = 0x004A0104, .anim_4 = 0x004A0101, .anim_5 = 0x004A0101, .death = 0x004A0109, .hit = 0x004A0109, .anim_8 = 0x004A0106, .anim_9 = 0x004A0108, .anim_A = 0x004A0107, .anim_B = 0x004A0101, .anim_C = 0x004A0101, .anim_D = 0x004A0101, .anim_E = 0x004A0101, .anim_F = 0x004A0101 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_imp_Lakitu_Npc_BlueSpinyC[] = {
    {
        .id = 52,
        .settings = &TTYD64_imp_Lakitu_NpcSettings_8024437C_flo_13_BlueSpiny,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00000404,
        .init = TTYD64_imp_Lakitu_Script_Init_802463E8_flo_13,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x004A0101, .walk = 0x004A0103, .run = 0x004A0104, .chase = 0x004A0104, .anim_4 = 0x004A0101, .anim_5 = 0x004A0101, .death = 0x004A0109, .hit = 0x004A0109, .anim_8 = 0x004A0106, .anim_9 = 0x004A0108, .anim_A = 0x004A0107, .anim_B = 0x004A0101, .anim_C = 0x004A0101, .anim_D = 0x004A0101, .anim_E = 0x004A0101, .anim_F = 0x004A0101 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_imp_Lakitu_Npc_BlueSpinyB[] = {
    {
        .id = 51,
        .settings = &TTYD64_imp_Lakitu_NpcSettings_8024437C_flo_13_BlueSpiny,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00000404,
        .init = TTYD64_imp_Lakitu_Script_Init_802463E8_flo_13,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x004A0101, .walk = 0x004A0103, .run = 0x004A0104, .chase = 0x004A0104, .anim_4 = 0x004A0101, .anim_5 = 0x004A0101, .death = 0x004A0109, .hit = 0x004A0109, .anim_8 = 0x004A0106, .anim_9 = 0x004A0108, .anim_A = 0x004A0107, .anim_B = 0x004A0101, .anim_C = 0x004A0101, .anim_D = 0x004A0101, .anim_E = 0x004A0101, .anim_F = 0x004A0101 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_imp_Lakitu_Npc_BlueSpinyA[] = {
    {
        .id = 50,
        .settings = &TTYD64_imp_Lakitu_NpcSettings_8024437C_flo_13_BlueSpiny,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00000404,
        .init = TTYD64_imp_Lakitu_Script_Init_802463E8_flo_13,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 1, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x004A0101, .walk = 0x004A0103, .run = 0x004A0104, .chase = 0x004A0104, .anim_4 = 0x004A0101, .anim_5 = 0x004A0101, .death = 0x004A0109, .hit = 0x004A0109, .anim_8 = 0x004A0106, .anim_9 = 0x004A0108, .anim_A = 0x004A0107, .anim_B = 0x004A0101, .anim_C = 0x004A0101, .anim_D = 0x004A0101, .anim_E = 0x004A0101, .anim_F = 0x004A0101 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_imp_Lakitu_Script_802442B0_flo_13 = {
    Call(SetNpcRotation, -1, 0, 0, 0)
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Call(SetSelfVar, 10, 100)
        Call(DoNpcDefeat)
    CaseEq(2)
        Call(OnPlayerFled, 0)
    CaseEq(3)
        Call(SetEnemyFlagBits, -1, 16, 1)
        Call(RemoveNpc, -1)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_imp_Lakitu_Script_NpcAI_80244174_flo_13 = {
    Call(SetSelfVar, 0, 0)
    Call(SetSelfVar, 5, -650)
    Call(SetSelfVar, 6, 30)
    Call(SetSelfVar, 1, 400)
    Call(flo_17_LakituAI_Main, Ref(TTYD64_imp_Lakitu_AISettings_80244144_flo_13))
    Return
    End
};

EvtScript TTYD64_imp_Lakitu_Script_NpcAI_80244240_flo_13_BlueSpiny = {
    Call(SetSelfVar, 2, 3)
    Call(SetSelfVar, 3, 18)
    Call(SetSelfVar, 5, 3)
    Call(SetSelfVar, 7, 4)
    Call(TTYD64_tp_flo_13_BlueSpinyAI_Main, Ref(TTYD64_imp_Lakitu_AISettings_80244210_flo_13))
    Return
    End
};

EvtScript TTYD64_imp_Lakitu_Script_NpcAI_80244240_flo_13 = {
    Call(SetSelfVar, 2, 3)
    Call(SetSelfVar, 3, 18)
    Call(SetSelfVar, 5, 3)
    Call(SetSelfVar, 7, 4)
    Call(flo_13_SpinyAI_Main, Ref(TTYD64_imp_Lakitu_AISettings_80244210_flo_13))
    Return
    End
};

MobileAISettings TTYD64_imp_Lakitu_AISettings_80244144_flo_13 = {
    .moveSpeed = 1.5f,
    .moveTime = 60,
    .waitTime = 30,
    .alertRadius = 60.0f,
    .alertOffsetDist = 50.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 3.5f,
    .chaseTurnRate = 60,
    .chaseUpdateInterval = 10,
    .chaseRadius = 80.0f,
    .chaseOffsetDist = 70.0f,
    .unk_AI_2C = 1,
};

MobileAISettings TTYD64_imp_Lakitu_AISettings_80244210_flo_13 = {
    .moveSpeed = 1.5f,
    .moveTime = 30,
    .waitTime = 50,
    .alertRadius = 60.0f,
    .alertOffsetDist = 30.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 6.0f,
    .chaseTurnRate = 0,
    .chaseUpdateInterval = 0,
    .chaseRadius = 100.0f,
    .chaseOffsetDist = 30.0f,
    .unk_AI_2C = 3,
};

NpcSettings TTYD64_imp_Lakitu_NpcSettings_802441E4_flo_13 = {
    .defaultAnim = 0x00000000,
    .height = 28,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Lakitu_Script_NpcAI_80244174_flo_13,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 20,
    .actionFlags = 0,
};

NpcSettings TTYD64_imp_Lakitu_NpcSettings_8024437C_flo_13_BlueSpiny = {
    .defaultAnim = 0x00000000,
    .height = 21,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Lakitu_Script_NpcAI_80244240_flo_13_BlueSpiny,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = TTYD64_imp_Lakitu_Script_802442B0_flo_13,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 19,
    .actionFlags = 0,
};

NpcSettings TTYD64_imp_Lakitu_NpcSettings_8024437C_flo_13 = {
    .defaultAnim = 0x00000000,
    .height = 21,
    .radius = 22,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_imp_Lakitu_Script_NpcAI_80244240_flo_13,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = TTYD64_imp_Lakitu_Script_802442B0_flo_13,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 19,
    .actionFlags = 0,
};

EvtScript TTYD64_imp_Lakitu_Script_Init_802463E8_flo_13 = {
    Call(SetSelfVar, 13, 1)
    Return
    End
};
// clang-format on

void TTYD64_tp_Install_imp_Lakitu(void) {
}
