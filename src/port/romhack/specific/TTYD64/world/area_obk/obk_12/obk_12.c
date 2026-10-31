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

API_CALLABLE(AssignScript);
API_CALLABLE(BindNpcIdle);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetPlayerActionState);
API_CALLABLE(GetSelfNpcID);
API_CALLABLE(GotoMap);
API_CALLABLE(HidePlayerShadow);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(ModifyColliderFlags);
API_CALLABLE(NpcFlyTo);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(ResetCam);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcImgFXParams);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetNpcSpeed);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(StopSound);
API_CALLABLE(UseExitHeading);

extern NpcData TTYD64_obk_12_NpcGroup_Decorations[];
extern EvtScript TTYD64_obk_12_Script_ShowHiddenDoor;
extern EvtScript TTYD64_obk_12_Script_NPCIdle_Boo;
extern EvtScript TTYD64_obk_12_Script_Main;
extern EvtScript TTYD64_obk_12_Script_Respawn;
extern EvtScript TTYD64_obk_12_Script_MakeBlueSwitch;
extern EvtScript TTYD64_obk_12_Script_Exit2;
extern EvtScript TTYD64_obk_12_Script_EnterMap;
extern EvtScript TTYD64_obk_12_Script_SetupMusic;
extern EvtScript TTYD64_obk_12_Script_MakeEntities;
extern EvtScript TTYD64_obk_12_Script_CreateExitTriggers;
extern EvtScript TTYD64_obk_12_Script_Exit0;
extern EvtScript TTYD64_obk_12_Script_NPC_Init_Boo;
extern EvtScript TTYD64_obk_12_Script_Exit1;
extern MapSettings TTYD64_obk_12_Header;
extern NpcSettings TTYD64_obk_12_NpcSettings_Decoration;
extern EntryList TTYD64_obk_12_EntryList;
extern NpcGroupList TTYD64_obk_12_NpcGroupList_obk12;

// clang-format off
NpcData TTYD64_obk_12_NpcGroup_Decorations[] = {
    {
        .id = 0,
        .settings = &TTYD64_obk_12_NpcSettings_Decoration,
        .pos = { -84.0f, 176.0f, -27.0f },
        .flags = 0x00A40D01,
        .init = &TTYD64_obk_12_Script_NPC_Init_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .patrol = { .numPoints = 2, .points[0].x = -83, .points[0].y = 175, .points[0].z = 0, .points[1].x = 1111, .points[1].y = 175, .points[1].z = 0, .points[2].x = 0, .points[2].y = 0, .points[2].z = 0, .points[3].x = 0, .points[3].y = 0, .points[3].z = 0, .points[4].x = 0, .points[4].y = 0, .points[4].z = 0, .points[5].x = 0, .points[5].y = 0, .points[5].z = 0, .points[6].x = 0, .points[6].y = 0, .points[6].z = 0, .points[7].x = 0, .points[7].y = 0, .points[7].z = 0, .points[8].x = 0, .points[8].y = 0, .points[8].z = 0, .points[9].x = 0, .points[9].y = 0, .points[9].z = 0, .moveSpeedOverride = -32767, .detectPos.x = -84, .detectPos.y = 176, .detectPos.z = -27, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x00950002, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_obk_12_NpcSettings_Decoration,
        .pos = { 21.0f, 198.0f, -27.0f },
        .flags = 0x00A40D01,
        .init = &TTYD64_obk_12_Script_NPC_Init_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .patrol = { .numPoints = 2, .points[0].x = 22, .points[0].y = 197, .points[0].z = 0, .points[1].x = 1111, .points[1].y = 197, .points[1].z = 0, .points[2].x = 0, .points[2].y = 0, .points[2].z = 0, .points[3].x = 0, .points[3].y = 0, .points[3].z = 0, .points[4].x = 0, .points[4].y = 0, .points[4].z = 0, .points[5].x = 0, .points[5].y = 0, .points[5].z = 0, .points[6].x = 0, .points[6].y = 0, .points[6].z = 0, .points[7].x = 0, .points[7].y = 0, .points[7].z = 0, .points[8].x = 0, .points[8].y = 0, .points[8].z = 0, .points[9].x = 0, .points[9].y = 0, .points[9].z = 0, .moveSpeedOverride = -32767, .detectPos.x = 21, .detectPos.y = 198, .detectPos.z = -27, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x00950002, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_obk_12_NpcSettings_Decoration,
        .pos = { 91.0f, 140.0f, -27.0f },
        .flags = 0x00A40D01,
        .init = &TTYD64_obk_12_Script_NPC_Init_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .patrol = { .numPoints = 2, .points[0].x = 92, .points[0].y = 139, .points[0].z = 0, .points[1].x = 1110, .points[1].y = 139, .points[1].z = 0, .points[2].x = 0, .points[2].y = 0, .points[2].z = 0, .points[3].x = 0, .points[3].y = 0, .points[3].z = 0, .points[4].x = 0, .points[4].y = 0, .points[4].z = 0, .points[5].x = 0, .points[5].y = 0, .points[5].z = 0, .points[6].x = 0, .points[6].y = 0, .points[6].z = 0, .points[7].x = 0, .points[7].y = 0, .points[7].z = 0, .points[8].x = 0, .points[8].y = 0, .points[8].z = 0, .points[9].x = 0, .points[9].y = 0, .points[9].z = 0, .moveSpeedOverride = -32767, .detectPos.x = 91, .detectPos.y = 140, .detectPos.z = -27, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x00950002, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_obk_12_NpcSettings_Decoration,
        .pos = { 199.0f, 196.0f, -27.0f },
        .flags = 0x00A40D01,
        .init = &TTYD64_obk_12_Script_NPC_Init_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .patrol = { .numPoints = 2, .points[0].x = 200, .points[0].y = 195, .points[0].z = 0, .points[1].x = 1110, .points[1].y = 195, .points[1].z = 0, .points[2].x = 0, .points[2].y = 0, .points[2].z = 0, .points[3].x = 0, .points[3].y = 0, .points[3].z = 0, .points[4].x = 0, .points[4].y = 0, .points[4].z = 0, .points[5].x = 0, .points[5].y = 0, .points[5].z = 0, .points[6].x = 0, .points[6].y = 0, .points[6].z = 0, .points[7].x = 0, .points[7].y = 0, .points[7].z = 0, .points[8].x = 0, .points[8].y = 0, .points[8].z = 0, .points[9].x = 0, .points[9].y = 0, .points[9].z = 0, .moveSpeedOverride = -32767, .detectPos.x = 199, .detectPos.y = 196, .detectPos.z = -27, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x00950002, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_obk_12_NpcSettings_Decoration,
        .pos = { 293.0f, 153.0f, -27.0f },
        .flags = 0x00A40D01,
        .init = &TTYD64_obk_12_Script_NPC_Init_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .patrol = { .numPoints = 2, .points[0].x = 294, .points[0].y = 152, .points[0].z = 0, .points[1].x = 1109, .points[1].y = 152, .points[1].z = 0, .points[2].x = 0, .points[2].y = 0, .points[2].z = 0, .points[3].x = 0, .points[3].y = 0, .points[3].z = 0, .points[4].x = 0, .points[4].y = 0, .points[4].z = 0, .points[5].x = 0, .points[5].y = 0, .points[5].z = 0, .points[6].x = 0, .points[6].y = 0, .points[6].z = 0, .points[7].x = 0, .points[7].y = 0, .points[7].z = 0, .points[8].x = 0, .points[8].y = 0, .points[8].z = 0, .points[9].x = 0, .points[9].y = 0, .points[9].z = 0, .moveSpeedOverride = -32767, .detectPos.x = 293, .detectPos.y = 153, .detectPos.z = -27, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x00950002, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_obk_12_NpcSettings_Decoration,
        .pos = { 422.0f, 185.0f, -27.0f },
        .flags = 0x00A40D01,
        .init = &TTYD64_obk_12_Script_NPC_Init_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .patrol = { .numPoints = 2, .points[0].x = 423, .points[0].y = 184, .points[0].z = 0, .points[1].x = 1112, .points[1].y = 184, .points[1].z = 0, .points[2].x = 0, .points[2].y = 0, .points[2].z = 0, .points[3].x = 0, .points[3].y = 0, .points[3].z = 0, .points[4].x = 0, .points[4].y = 0, .points[4].z = 0, .points[5].x = 0, .points[5].y = 0, .points[5].z = 0, .points[6].x = 0, .points[6].y = 0, .points[6].z = 0, .points[7].x = 0, .points[7].y = 0, .points[7].z = 0, .points[8].x = 0, .points[8].y = 0, .points[8].z = 0, .points[9].x = 0, .points[9].y = 0, .points[9].z = 0, .moveSpeedOverride = -32767, .detectPos.x = 422, .detectPos.y = 185, .detectPos.z = -27, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x00950002, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_obk_12_NpcSettings_Decoration,
        .pos = { 603.0f, 176.0f, -37.0f },
        .flags = 0x00A40D01,
        .init = &TTYD64_obk_12_Script_NPC_Init_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .patrol = { .numPoints = 2, .points[0].x = 604, .points[0].y = 175, .points[0].z = -10, .points[1].x = -54, .points[1].y = 175, .points[1].z = -10, .points[2].x = 0, .points[2].y = 0, .points[2].z = 0, .points[3].x = 0, .points[3].y = 0, .points[3].z = 0, .points[4].x = 0, .points[4].y = 0, .points[4].z = 0, .points[5].x = 0, .points[5].y = 0, .points[5].z = 0, .points[6].x = 0, .points[6].y = 0, .points[6].z = 0, .points[7].x = 0, .points[7].y = 0, .points[7].z = 0, .points[8].x = 0, .points[8].y = 0, .points[8].z = 0, .points[9].x = 0, .points[9].y = 0, .points[9].z = 0, .moveSpeedOverride = -32767, .detectPos.x = 603, .detectPos.y = 176, .detectPos.z = -37, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x00950002, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_obk_12_NpcSettings_Decoration,
        .pos = { 708.0f, 198.0f, -37.0f },
        .flags = 0x00A40D01,
        .init = &TTYD64_obk_12_Script_NPC_Init_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .patrol = { .numPoints = 2, .points[0].x = 709, .points[0].y = 197, .points[0].z = -10, .points[1].x = -54, .points[1].y = 197, .points[1].z = -10, .points[2].x = 0, .points[2].y = 0, .points[2].z = 0, .points[3].x = 0, .points[3].y = 0, .points[3].z = 0, .points[4].x = 0, .points[4].y = 0, .points[4].z = 0, .points[5].x = 0, .points[5].y = 0, .points[5].z = 0, .points[6].x = 0, .points[6].y = 0, .points[6].z = 0, .points[7].x = 0, .points[7].y = 0, .points[7].z = 0, .points[8].x = 0, .points[8].y = 0, .points[8].z = 0, .points[9].x = 0, .points[9].y = 0, .points[9].z = 0, .moveSpeedOverride = -32767, .detectPos.x = 708, .detectPos.y = 198, .detectPos.z = -37, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x00950002, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_obk_12_NpcSettings_Decoration,
        .pos = { 778.0f, 140.0f, -37.0f },
        .flags = 0x00A40D01,
        .init = &TTYD64_obk_12_Script_NPC_Init_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .patrol = { .numPoints = 2, .points[0].x = 779, .points[0].y = 139, .points[0].z = -10, .points[1].x = -55, .points[1].y = 139, .points[1].z = -10, .points[2].x = 0, .points[2].y = 0, .points[2].z = 0, .points[3].x = 0, .points[3].y = 0, .points[3].z = 0, .points[4].x = 0, .points[4].y = 0, .points[4].z = 0, .points[5].x = 0, .points[5].y = 0, .points[5].z = 0, .points[6].x = 0, .points[6].y = 0, .points[6].z = 0, .points[7].x = 0, .points[7].y = 0, .points[7].z = 0, .points[8].x = 0, .points[8].y = 0, .points[8].z = 0, .points[9].x = 0, .points[9].y = 0, .points[9].z = 0, .moveSpeedOverride = -32767, .detectPos.x = 778, .detectPos.y = 140, .detectPos.z = -37, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x00950002, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_obk_12_NpcSettings_Decoration,
        .pos = { 886.0f, 196.0f, -37.0f },
        .flags = 0x00A40D01,
        .init = &TTYD64_obk_12_Script_NPC_Init_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .patrol = { .numPoints = 2, .points[0].x = 887, .points[0].y = 195, .points[0].z = -10, .points[1].x = -55, .points[1].y = 195, .points[1].z = -10, .points[2].x = 0, .points[2].y = 0, .points[2].z = 0, .points[3].x = 0, .points[3].y = 0, .points[3].z = 0, .points[4].x = 0, .points[4].y = 0, .points[4].z = 0, .points[5].x = 0, .points[5].y = 0, .points[5].z = 0, .points[6].x = 0, .points[6].y = 0, .points[6].z = 0, .points[7].x = 0, .points[7].y = 0, .points[7].z = 0, .points[8].x = 0, .points[8].y = 0, .points[8].z = 0, .points[9].x = 0, .points[9].y = 0, .points[9].z = 0, .moveSpeedOverride = -32767, .detectPos.x = 886, .detectPos.y = 196, .detectPos.z = -37, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x00950002, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_obk_12_NpcSettings_Decoration,
        .pos = { 980.0f, 153.0f, -37.0f },
        .flags = 0x00A40D01,
        .init = &TTYD64_obk_12_Script_NPC_Init_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .patrol = { .numPoints = 2, .points[0].x = 981, .points[0].y = 152, .points[0].z = -10, .points[1].x = -56, .points[1].y = 152, .points[1].z = -10, .points[2].x = 0, .points[2].y = 0, .points[2].z = 0, .points[3].x = 0, .points[3].y = 0, .points[3].z = 0, .points[4].x = 0, .points[4].y = 0, .points[4].z = 0, .points[5].x = 0, .points[5].y = 0, .points[5].z = 0, .points[6].x = 0, .points[6].y = 0, .points[6].z = 0, .points[7].x = 0, .points[7].y = 0, .points[7].z = 0, .points[8].x = 0, .points[8].y = 0, .points[8].z = 0, .points[9].x = 0, .points[9].y = 0, .points[9].z = 0, .moveSpeedOverride = -32767, .detectPos.x = 980, .detectPos.y = 153, .detectPos.z = -37, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x00950002, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
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
        .settings = &TTYD64_obk_12_NpcSettings_Decoration,
        .pos = { 1109.0f, 185.0f, -37.0f },
        .flags = 0x00A40D01,
        .init = &TTYD64_obk_12_Script_NPC_Init_Boo,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .patrol = { .numPoints = 2, .points[0].x = 1110, .points[0].y = 184, .points[0].z = -10, .points[1].x = -53, .points[1].y = 184, .points[1].z = -10, .points[2].x = 0, .points[2].y = 0, .points[2].z = 0, .points[3].x = 0, .points[3].y = 0, .points[3].z = 0, .points[4].x = 0, .points[4].y = 0, .points[4].z = 0, .points[5].x = 0, .points[5].y = 0, .points[5].z = 0, .points[6].x = 0, .points[6].y = 0, .points[6].z = 0, .points[7].x = 0, .points[7].y = 0, .points[7].z = 0, .points[8].x = 0, .points[8].y = 0, .points[8].z = 0, .points[9].x = 0, .points[9].y = 0, .points[9].z = 0, .moveSpeedOverride = -32767, .detectPos.x = 1109, .detectPos.y = 185, .detectPos.z = -37, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 1, .isFlying = 0 } },
        .animations = { .idle = 0x00950002, .walk = 0x00950000, .run = 0x00950000, .chase = 0x00950000, .anim_4 = 0x00950000, .anim_5 = 0x00950000, .death = 0x00950000, .hit = 0x00950000, .anim_8 = 0x00950000, .anim_9 = 0x00950000, .anim_A = 0x00950000, .anim_B = 0x00950000, .anim_C = 0x00950000, .anim_D = 0x00950000, .anim_E = 0x00950000, .anim_F = 0x00950000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_obk_12_Script_ShowHiddenDoor = {
    Call(TTYD64_Set8BitSwitchPressed, 1)
    Call(TTYD64_SetPlayerAnimFlagBits, PA_FLAG_8BIT_MARIO, 0)
    Thread
        Loop(0)
            Call(GetPlayerActionState, LVar0)
            IfEq(LVar0, 10)
                Call(TTYD64_Set8BitSwitchPressed, 0)
                Call(TTYD64_SetPlayerAnimFlagBits, PA_FLAG_8BIT_MARIO, 1)
                BreakLoop
            EndIf
            Call(SetPlayerAnimation, 0x10002)
            Call(SetPlayerAnimation, 0x90005)
            Wait(1)
        EndLoop
    EndThread
    Call(EnableGroup, 20, 1)
    Call(ModifyColliderFlags, 1, 7, 0x7FFFFE00)
    Set(GameFlag(5079), 0)
    Set(GameFlag(5080), 0)
    Set(GameFlag(5081), 0)
    Set(GameFlag(5082), 0)
    Set(GameFlag(5083), 0)
    Set(GameFlag(5084), 0)
    Set(GameFlag(5085), 0)
    Set(GameFlag(5086), 0)
    Set(GameFlag(5087), 0)
    Call(MakeItemEntity, 343, 698, 48, -8, 17, GameFlag(5079))
    Set(MapVar(0), LVar0)
    Call(MakeItemEntity, 343, 682, 48, -8, 17, GameFlag(5080))
    Call(MakeItemEntity, 343, 698, 65, -8, 17, GameFlag(5081))
    Call(MakeItemEntity, 343, 698, 30, -8, 17, GameFlag(5082))
    Call(MakeItemEntity, 343, 713, 81, -8, 17, GameFlag(5083))
    Call(MakeItemEntity, 343, 713, 14, -8, 17, GameFlag(5084))
    Call(MakeItemEntity, 343, 714, 48, -8, 17, GameFlag(5085))
    Call(MakeItemEntity, 343, 732, 48, -8, 17, GameFlag(5086))
    Call(MakeItemEntity, 343, 749, 48, -8, 17, GameFlag(5087))
    Thread
        Set(MapFlag(0), 1)
        Call(PlaySound, 142)
        Wait(350)
        Set(MapFlag(0), 0)
        Call(StopSound, 142)
        Call(EnableGroup, 20, 0)
        Call(ModifyColliderFlags, 0, 7, 0x7FFFFE00)
        IfEq(GameFlag(5079), 0)
            Call(RemoveItemEntity, MapVar(0))
        EndIf
        IfEq(GameFlag(5080), 0)
            Set(LVar0, MapVar(0))
            Add(LVar0, 1)
            Call(RemoveItemEntity, LVar0)
        EndIf
        IfEq(GameFlag(5081), 0)
            Set(LVar0, MapVar(0))
            Add(LVar0, 2)
            Call(RemoveItemEntity, LVar0)
        EndIf
        IfEq(GameFlag(5082), 0)
            Set(LVar0, MapVar(0))
            Add(LVar0, 3)
            Call(RemoveItemEntity, LVar0)
        EndIf
        IfEq(GameFlag(5083), 0)
            Set(LVar0, MapVar(0))
            Add(LVar0, 4)
            Call(RemoveItemEntity, LVar0)
        EndIf
        IfEq(GameFlag(5084), 0)
            Set(LVar0, MapVar(0))
            Add(LVar0, 5)
            Call(RemoveItemEntity, LVar0)
        EndIf
        IfEq(GameFlag(5085), 0)
            Set(LVar0, MapVar(0))
            Add(LVar0, 6)
            Call(RemoveItemEntity, LVar0)
        EndIf
        IfEq(GameFlag(5086), 0)
            Set(LVar0, MapVar(0))
            Add(LVar0, 7)
            Call(RemoveItemEntity, LVar0)
        EndIf
        IfEq(GameFlag(5087), 0)
            Set(LVar0, MapVar(0))
            Add(LVar0, 8)
            Call(RemoveItemEntity, LVar0)
        EndIf
    EndThread
    Return
    End
};

EvtScript TTYD64_obk_12_Script_NPCIdle_Boo = {
    Set(LVar9, 100)
    Call(RandInt, 200, LVar0)
    Add(LVar9, LVar0)
    Wait(LVar9)
    Loop(0)
        Call(EnableNpcShadow, -1, 1)
        Call(GetSelfNpcID, LVar0)
        Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(1)
        CaseOrEq(2)
        CaseOrEq(3)
        CaseOrEq(4)
        CaseOrEq(5)
            Set(LVarA, 0)
            EndCaseGroup
        CaseOrEq(6)
        CaseOrEq(7)
        CaseOrEq(8)
        CaseOrEq(9)
        CaseOrEq(10)
        CaseOrEq(11)
            Set(LVarA, 1)
            EndCaseGroup
        EndSwitch
        Set(LVar1, 0)
        Thread
            Loop(10)
                Add(LVar1, 24)
                Call(SetNpcImgFXParams, -1, 7, LVar1, 0, 0, 0)
                Wait(1)
            EndLoop
        EndThread
        Call(SetNpcSpeed, -1, Float(2.5))
        Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
        IfEq(LVarA, 0)
            Set(LVar0, 1109)
        Else
            Set(LVar0, -84)
        EndIf
        Call(NpcFlyTo, -1, LVar0, LVar1, LVar2, 0, 0, 0)
        Call(SetNpcImgFXParams, -1, 7, Float(0.0), 0, 0, 0)
        Call(GetSelfNpcID, LVar0)
        Switch(LVar0)
        CaseEq(0)
            Call(SetNpcPos, -1, -84, 176, -27)
        CaseEq(1)
            Call(SetNpcPos, -1, 21, 198, -27)
        CaseEq(2)
            Call(SetNpcPos, -1, 91, 140, -27)
        CaseEq(3)
            Call(SetNpcPos, -1, 199, 196, -27)
        CaseEq(4)
            Call(SetNpcPos, -1, 293, 153, -27)
        CaseEq(5)
            Call(SetNpcPos, -1, 422, 185, -27)
        CaseEq(6)
            Call(SetNpcPos, -1, 603, 176, -37)
        CaseEq(7)
            Call(SetNpcPos, -1, 708, 198, -37)
        CaseEq(8)
            Call(SetNpcPos, -1, 778, 140, -37)
        CaseEq(9)
            Call(SetNpcPos, -1, 886, 196, -37)
        CaseEq(10)
            Call(SetNpcPos, -1, 980, 153, -37)
        CaseEq(11)
            Call(SetNpcPos, -1, 1109, 185, -37)
        EndSwitch
        Call(EnableNpcShadow, -1, 0)
        Call(RandInt, 200, LVar9)
        Wait(LVar9)
    EndLoop
    Return
    End
};

EvtScript TTYD64_obk_12_Script_Main = {
    Set(GameByte(425), 13)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(TTYD64_SetPlayerAnimFlagBits, PA_FLAG_8BIT_MARIO, 1)
    Exec(TTYD64_obk_12_Script_SetupMusic)
    Exec(TTYD64_obk_12_Script_MakeEntities)
    Exec(TTYD64_obk_12_Script_EnterMap)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_obk_12_NpcGroupList_obk12)
    BindTrigger(TTYD64_obk_12_Script_Respawn, 0x80000, 11, 1, 0)
    Call(EnableGroup, 20, 0)
    Call(ModifyColliderFlags, 0, 7, 0x7FFFFE00)
    Call(HidePlayerShadow, 1)
    Return
    End
};

EvtScript TTYD64_obk_12_Script_Respawn = {
    Wait(5)
    Call(DisablePlayerInput, 1)
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(255.0))
    ExecWait(TTYD64_Script_FadeScreenOut)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 0)
        Call(SetPlayerPos, -58, 0, -5)
    Else
        Call(SetPlayerPos, 939, -100, -6)
    EndIf
    Call(ResetCam, 0, Float(50.0))
    Wait(10)
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(5.0))
    ExecWait(TTYD64_Script_FadeScreenIn)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_obk_12_Script_MakeBlueSwitch = {
    Call(PlaySound, 717)
    Set(LVar0, 818)
    Set(LVar1, -1)
    Set(LVar2, -11)
    Add(LVar1, 7)
    Call(PlayEffect_impl, 1, LVar0, LVar1, LVar2)
    Wait(5)
    Call(MakeEntity, Ref(Entity_BlueSwitch), 818, -1, -11, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_obk_12_Script_ShowHiddenDoor)
    Return
    End
};

EvtScript TTYD64_obk_12_Script_Exit2 = {
    Call(StopSound, 142)
    Call(DisablePlayerInput, 1)
    Call(PlaySound, 449)
    IfEq(MapFlag(0), 0)
        Call(GotoMap, (Bytecode) "obk_12", 1)
    Else
        Call(TTYD64_SetVerticalMovementLocked, 0)
        Call(GotoMap, (Bytecode) "obk_14", 0)
    EndIf
    Return
    End
};

EvtScript TTYD64_obk_12_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 0)
        Set(LVar0, (Bytecode) TTYD64_obk_12_Script_CreateExitTriggers)
        Exec(EnterWalk)
    Else
        Exec(TTYD64_obk_12_Script_CreateExitTriggers)
        Call(DisablePlayerInput, 1)
        Wait(5)
        Call(DisablePlayerInput, 0)
    EndIf
    Return
    End
};

EvtScript TTYD64_obk_12_Script_SetupMusic = {
    IfLt(GameByte(0), -16)
        Call(SetMusic, 0, 27, 0, 8)
    Else
        Call(SetMusic, 0, 28, 0, 8)
    EndIf
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_obk_12_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_InertYellowBlock), 818, -26, -11, 0, 0x80000000)
    Call(MakeEntity, Ref(Entity_TriggerBlock), 818, -52, -11, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_obk_12_Script_MakeBlueSwitch)
    Return
    End
};

EvtScript TTYD64_obk_12_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_obk_12_Script_Exit0, 0x80000, 6, 1, 0)
    BindTrigger(TTYD64_obk_12_Script_Exit1, 256, 7, 1, 0)
    BindTrigger(TTYD64_obk_12_Script_Exit2, 256, 8, 1, 0)
    Return
    End
};

EvtScript TTYD64_obk_12_Script_Exit0 = {
    Call(StopSound, 142)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "obk_05", 1)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_obk_12_Script_NPC_Init_Boo = {
    Call(EnableNpcShadow, -1, 0)
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_obk_12_Script_NPCIdle_Boo)
    Call(SetNpcImgFXParams, -1, 7, Float(0.0), 0, 0, 0)
    Return
    End
};

EvtScript TTYD64_obk_12_Script_Exit1 = {
    Call(StopSound, 142)
    Call(DisablePlayerInput, 1)
    Call(PlaySound, 449)
    Call(GotoMap, (Bytecode) "obk_13", 0)
    Return
    End
};

MapSettings TTYD64_obk_12_Header = {
    .main = &TTYD64_obk_12_Script_Main,
    .entryList = &TTYD64_obk_12_EntryList,
    .entryCount = 2,
    .background = NULL,
    .tattle = { .get = NULL },
};

NpcSettings TTYD64_obk_12_NpcSettings_Decoration = {
    .defaultAnim = 0x00000000,
    .height = 32,
    .radius = 37,
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

EntryList TTYD64_obk_12_EntryList = {
    { -58.0f, 0.0f, -5.0f, 90.0f },
    { 939.0f, -100.0f, -6.0f, -90.0f },
};

NpcGroupList TTYD64_obk_12_NpcGroupList_obk12 = {
    { .npcCount = 12, .npcs = TTYD64_obk_12_NpcGroup_Decorations, .battle = 0x0000, .stage = 0 },
    {},
};

MapConfig TTYD64_mapcfg_obk_12 = {
    .id = "obk_12",
    .settings = &TTYD64_obk_12_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 1,
};
// clang-format on

void TTYD64_nm_Install_obk_12(void) {
}
