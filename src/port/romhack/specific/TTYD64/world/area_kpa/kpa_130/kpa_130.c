#include "common.h"
#include "effects.h"
#include "entity.h"
#include "foliage.h"
#include "map.h"
#include "npc.h"
#include "script_api/map.h"
#include <string.h>
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/world/maps.h"

extern EvtScript kpa_130_EVS_EnterMap;
extern EvtScript kpa_130_EVS_Main;
extern EvtScript kpa_130_EVS_NpcInit_BombshellBlaster;
extern EvtScript kpa_130_EVS_SetupMusic;
extern NpcData kpa_130_NpcData_BombshellBill_01;
extern NpcData kpa_130_NpcData_BombshellBill_02;
extern NpcData kpa_130_NpcData_BombshellBill_03;
extern NpcData kpa_130_NpcData_BombshellBill_04;
extern NpcData kpa_130_NpcData_BombshellBill_05;
extern NpcData kpa_130_NpcData_BombshellBill_06;
extern NpcData kpa_130_NpcData_BombshellBill_07;
extern NpcData kpa_130_NpcData_BombshellBill_08;
extern NpcData kpa_130_NpcData_BombshellBill_09;
extern NpcData kpa_130_NpcData_BombshellBill_10;
extern NpcData kpa_130_NpcData_BombshellBlaster_01[];
extern NpcData kpa_130_NpcData_BombshellBlaster_03[];
extern NpcData kpa_130_NpcData_BombshellBlaster_05[];
extern NpcData kpa_130_NpcData_BombshellBlaster_07[];
extern NpcSettings kpa_130_NpcSettings_BombshellBill;
extern NpcSettings kpa_130_NpcSettings_BombshellBlaster;

API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetSpriteShading);

extern EvtScript TTYD64_kpa_130_Script_Main;
extern EvtScript TTYD64_kpa_130_Script_NewStuff;
extern NpcData TTYD64_kpa_130_NpcGroup_BillBlaster_05[];
extern NpcData TTYD64_kpa_130_NpcGroup_BulletBill_5B[];
extern NpcData TTYD64_kpa_130_NpcGroup_BulletBill_5A[];
extern NpcGroupList TTYD64_kpa_130_NpcGroupList_80244688;

// clang-format off
EvtScript TTYD64_kpa_130_Script_Main = {
    Set(GameByte(425), 22)
    Call(SetSpriteShading, -1)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(MakeNpcs, 1, Ref(TTYD64_kpa_130_NpcGroupList_80244688))
    Call(ModifyColliderFlags, 1, 2, 0x7FFFFE00)
    Exec(kpa_130_EVS_EnterMap)
    Wait(1)
    Exec(TTYD64_kpa_130_Script_NewStuff)
    Return
    End
};

EvtScript TTYD64_kpa_130_Script_NewStuff = {
    Exec(kpa_130_EVS_SetupMusic)
    Call(MakeItemEntity, 348, 373, 330, 0, 17, GameFlag(5698))
    Return
    End
};

NpcData TTYD64_kpa_130_NpcGroup_BillBlaster_05[] = {
    {
        .id = 8,
        .settings = &kpa_130_NpcSettings_BombshellBlaster,
        .pos = { 306.0f, 300.0f, -22.0f },
        .flags = 0x00002D00,
        .init = &kpa_130_EVS_NpcInit_BombshellBlaster,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 4, 16383 }, { 9830, 19660, 4, 16383 }, { 16383, 16383, 4, 13106 }, { 26213, 13106, 4, 13106 }, { 32767, 9830, 4, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 1, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = -442, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = -442, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x002E0101, .walk = 0x002E0101, .run = 0x002E0101, .chase = 0x002E0101, .anim_4 = 0x002E0101, .anim_5 = 0x002E0101, .death = 0x002E0103, .hit = 0x002E0103, .anim_8 = 0x002E0102, .anim_9 = 0x002E0101, .anim_A = 0x002E0101, .anim_B = 0x002E0101, .anim_C = 0x002E0101, .anim_D = 0x002E0101, .anim_E = 0x002E0101, .anim_F = 0x002E0101 },
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
        .settings = &kpa_130_NpcSettings_BombshellBlaster,
        .pos = { 306.0f, 300.0f, 22.0f },
        .flags = 0x00002D00,
        .init = &kpa_130_EVS_NpcInit_BombshellBlaster,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = -442, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = -442, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x002E0101, .walk = 0x002E0101, .run = 0x002E0101, .chase = 0x002E0101, .anim_4 = 0x002E0101, .anim_5 = 0x002E0101, .death = 0x002E0103, .hit = 0x002E0103, .anim_8 = 0x002E0102, .anim_9 = 0x002E0101, .anim_A = 0x002E0101, .anim_B = 0x002E0101, .anim_C = 0x002E0101, .anim_D = 0x002E0101, .anim_E = 0x002E0101, .anim_F = 0x002E0101 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_kpa_130_NpcGroup_BulletBill_5B[] = {
    {
        .id = 61,
        .settings = &kpa_130_NpcSettings_BombshellBill,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00280D04,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x80, .itemDropChance = 3, .itemDrops = { { 140, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 1, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x002D0100, .walk = 0x002D0102, .run = 0x002D0103, .chase = 0x002D0103, .anim_4 = 0x002D0100, .anim_5 = 0x002D0104, .death = 0x002D0105, .hit = 0x002D0105, .anim_8 = 0x002D0100, .anim_9 = 0x002D0100, .anim_A = 0x002D0100, .anim_B = 0x002D0100, .anim_C = 0x002D0100, .anim_D = 0x002D0100, .anim_E = 0x002D0100, .anim_F = 0x002D0100 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_kpa_130_NpcGroup_BulletBill_5A[] = {
    {
        .id = 60,
        .settings = &kpa_130_NpcSettings_BombshellBill,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00280D04,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x80, .itemDropChance = 3, .itemDrops = { { 140, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 3, 16383 }, { 9830, 19660, 3, 16383 }, { 16383, 16383, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 1, .maxCoinBonus = 3, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 1 } },
        .animations = { .idle = 0x002D0100, .walk = 0x002D0102, .run = 0x002D0103, .chase = 0x002D0103, .anim_4 = 0x002D0100, .anim_5 = 0x002D0104, .death = 0x002D0105, .hit = 0x002D0105, .anim_8 = 0x002D0100, .anim_9 = 0x002D0100, .anim_A = 0x002D0100, .anim_B = 0x002D0100, .anim_C = 0x002D0100, .anim_D = 0x002D0100, .anim_E = 0x002D0100, .anim_F = 0x002D0100 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcGroupList TTYD64_kpa_130_NpcGroupList_80244688 = {
    { .npcCount = 2, .npcs = kpa_130_NpcData_BombshellBlaster_01, .battle = 0x2502, .stage = 5 },
    { .npcCount = 2, .npcs = kpa_130_NpcData_BombshellBlaster_03, .battle = 0x2502, .stage = 6 },
    { .npcCount = 2, .npcs = kpa_130_NpcData_BombshellBlaster_05, .battle = 0x2503, .stage = 6 },
    { .npcCount = 2, .npcs = kpa_130_NpcData_BombshellBlaster_07, .battle = 0x2504, .stage = 6 },
    { .npcCount = 1, .npcs = &kpa_130_NpcData_BombshellBill_01, .battle = 0x2501, .stage = 5 },
    { .npcCount = 1, .npcs = &kpa_130_NpcData_BombshellBill_02, .battle = 0x2501, .stage = 5 },
    { .npcCount = 1, .npcs = &kpa_130_NpcData_BombshellBill_03, .battle = 0x2501, .stage = 5 },
    { .npcCount = 1, .npcs = &kpa_130_NpcData_BombshellBill_04, .battle = 0x2501, .stage = 5 },
    { .npcCount = 1, .npcs = &kpa_130_NpcData_BombshellBill_05, .battle = 0x2501, .stage = 5 },
    { .npcCount = 1, .npcs = &kpa_130_NpcData_BombshellBill_06, .battle = 0x2501, .stage = 5 },
    { .npcCount = 1, .npcs = &kpa_130_NpcData_BombshellBill_07, .battle = 0x2501, .stage = 5 },
    { .npcCount = 1, .npcs = &kpa_130_NpcData_BombshellBill_08, .battle = 0x2501, .stage = 5 },
    { .npcCount = 1, .npcs = &kpa_130_NpcData_BombshellBill_09, .battle = 0x2501, .stage = 5 },
    { .npcCount = 1, .npcs = &kpa_130_NpcData_BombshellBill_10, .battle = 0x2501, .stage = 5 },
    { .npcCount = 2, .npcs = TTYD64_kpa_130_NpcGroup_BillBlaster_05, .battle = 0x2503, .stage = 6 },
    { .npcCount = 1, .npcs = TTYD64_kpa_130_NpcGroup_BulletBill_5A, .battle = 0x2501, .stage = 5 },
    { .npcCount = 1, .npcs = TTYD64_kpa_130_NpcGroup_BulletBill_5B, .battle = 0x2501, .stage = 5 },
    {},
};
// clang-format on

void TTYD64_InstallMap_kpa_130(void) {
    Mod_ReplaceScript("TTYD64", &kpa_130_EVS_Main, &TTYD64_kpa_130_Script_Main);
}
