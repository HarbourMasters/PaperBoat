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
#include "port/romhack/specific/TTYD64/newmaps/nm.h"

API_CALLABLE(BindNpcHit);
API_CALLABLE(BindNpcIdle);
API_CALLABLE(BindNpcInteract);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(CloseMessage);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(FadeOutMusic);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetSelfVar);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeNpcs);
API_CALLABLE(PlaySound);
API_CALLABLE(PushSong);
API_CALLABLE(RandInt);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetEnemyFlagBits);
API_CALLABLE(SetMessageValue);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetPlayerFlagBits);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetSelfEnemyFlagBits);
API_CALLABLE(SetSelfVar);
API_CALLABLE(ShowChoice);
API_CALLABLE(ShowGotItem);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(TeleportPartnerToPlayer);
API_CALLABLE(UseExitHeading);

extern NpcData TTYD64_kmr_32_NpcGroup_Montys[];
extern EvtScript TTYD64_kmr_32_Script_Idle_Hole;
extern EvtScript TTYD64_kmr_32_Script_Hit_Hole;
extern NpcData TTYD64_kmr_32_NpcGroup_Monty[];
extern EvtScript TTYD64_kmr_32_Script_Mole_AfterGame;
extern EvtScript TTYD64_kmr_32_Script_Interact_Monty0;
extern EvtScript TTYD64_kmr_32_Script_InitGame;
extern u8 TTYD64_kmr_32_String_Monty0_0[];
extern u8 TTYD64_kmr_32_String_Tattle[];
extern u8 TTYD64_kmr_32_Tattle_Monty[];
extern EvtScript TTYD64_kmr_32_Script_Main;
extern u8 TTYD64_kmr_32_String_Monty0_Stats[];
extern EvtScript TTYD64_kmr_32_Script_EnterMap;
extern EvtScript TTYD64_kmr_32_Script_Exit0;
extern u8 TTYD64_kmr_32_String_Monty0_NewHighscore[];
extern u8 TTYD64_kmr_32_String_Monty0_NoHighscore[];
extern u8 TTYD64_kmr_32_String_Monty0_Badge[];
extern MapSettings TTYD64_kmr_32_Header;
extern u8 TTYD64_kmr_32_String_Monty0_1[];
extern u8 TTYD64_kmr_32_String_Choice_Mole[];
extern EvtScript TTYD64_kmr_32_Script_NPC_Init_Monty;
extern EvtScript TTYD64_kmr_32_Script_SetupMusic;
extern EvtScript TTYD64_kmr_32_Script_NPC_Init_Hole;
extern NpcSettings TTYD64_kmr_32_NpcSettings_Generic;
extern EvtScript TTYD64_kmr_32_Script_CreateExitTriggers;
extern NpcGroupList TTYD64_kmr_32_NpcGroupList_kmr32;
extern EntryList TTYD64_kmr_32_EntryList;

// clang-format off
static s32 TTYD64_kmr_32_GetTattleMsg;

static s32 TTYD64_kmr_32_GetTattle(void) {
    return TTYD64_kmr_32_GetTattleMsg;
}

NpcData TTYD64_kmr_32_NpcGroup_Montys[] = {
    {
        .id = 1,
        .settings = &TTYD64_kmr_32_NpcSettings_Generic,
        .pos = { -90.0f, 0.0f, -217.0f },
        .flags = 0x01111D09,
        .init = &TTYD64_kmr_32_Script_NPC_Init_Hole,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002F0012, .walk = 0x002F0002, .run = 0x002F0003, .chase = 0x002F0003, .anim_4 = 0x002F0001, .anim_5 = 0x002F0001, .death = 0x002F0005, .hit = 0x002F0005, .anim_8 = 0x002F0000, .anim_9 = 0x002F0000, .anim_A = 0x002F0000, .anim_B = 0x002F0000, .anim_C = 0x002F0000, .anim_D = 0x002F0000, .anim_E = 0x002F0000, .anim_F = 0x002F0000 },
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
        .settings = &TTYD64_kmr_32_NpcSettings_Generic,
        .pos = { -33.0f, 0.0f, -277.0f },
        .flags = 0x01111D09,
        .init = &TTYD64_kmr_32_Script_NPC_Init_Hole,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002F0012, .walk = 0x002F0002, .run = 0x002F0003, .chase = 0x002F0003, .anim_4 = 0x002F0001, .anim_5 = 0x002F0001, .death = 0x002F0005, .hit = 0x002F0005, .anim_8 = 0x002F0000, .anim_9 = 0x002F0000, .anim_A = 0x002F0000, .anim_B = 0x002F0000, .anim_C = 0x002F0000, .anim_D = 0x002F0000, .anim_E = 0x002F0000, .anim_F = 0x002F0000 },
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
        .settings = &TTYD64_kmr_32_NpcSettings_Generic,
        .pos = { 36.0f, 0.0f, -277.0f },
        .flags = 0x01111D09,
        .init = &TTYD64_kmr_32_Script_NPC_Init_Hole,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002F0012, .walk = 0x002F0002, .run = 0x002F0003, .chase = 0x002F0003, .anim_4 = 0x002F0001, .anim_5 = 0x002F0001, .death = 0x002F0005, .hit = 0x002F0005, .anim_8 = 0x002F0000, .anim_9 = 0x002F0000, .anim_A = 0x002F0000, .anim_B = 0x002F0000, .anim_C = 0x002F0000, .anim_D = 0x002F0000, .anim_E = 0x002F0000, .anim_F = 0x002F0000 },
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
        .settings = &TTYD64_kmr_32_NpcSettings_Generic,
        .pos = { 92.0f, 0.0f, -217.0f },
        .flags = 0x01111D09,
        .init = &TTYD64_kmr_32_Script_NPC_Init_Hole,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002F0012, .walk = 0x002F0002, .run = 0x002F0003, .chase = 0x002F0003, .anim_4 = 0x002F0001, .anim_5 = 0x002F0001, .death = 0x002F0005, .hit = 0x002F0005, .anim_8 = 0x002F0000, .anim_9 = 0x002F0000, .anim_A = 0x002F0000, .anim_B = 0x002F0000, .anim_C = 0x002F0000, .anim_D = 0x002F0000, .anim_E = 0x002F0000, .anim_F = 0x002F0000 },
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
        .settings = &TTYD64_kmr_32_NpcSettings_Generic,
        .pos = { 36.0f, 0.0f, -145.0f },
        .flags = 0x01111D09,
        .init = &TTYD64_kmr_32_Script_NPC_Init_Hole,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002F0012, .walk = 0x002F0002, .run = 0x002F0003, .chase = 0x002F0003, .anim_4 = 0x002F0001, .anim_5 = 0x002F0001, .death = 0x002F0005, .hit = 0x002F0005, .anim_8 = 0x002F0000, .anim_9 = 0x002F0000, .anim_A = 0x002F0000, .anim_B = 0x002F0000, .anim_C = 0x002F0000, .anim_D = 0x002F0000, .anim_E = 0x002F0000, .anim_F = 0x002F0000 },
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
        .settings = &TTYD64_kmr_32_NpcSettings_Generic,
        .pos = { -33.0f, 0.0f, -145.0f },
        .flags = 0x01111D09,
        .init = &TTYD64_kmr_32_Script_NPC_Init_Hole,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002F0012, .walk = 0x002F0002, .run = 0x002F0003, .chase = 0x002F0003, .anim_4 = 0x002F0001, .anim_5 = 0x002F0001, .death = 0x002F0005, .hit = 0x002F0005, .anim_8 = 0x002F0000, .anim_9 = 0x002F0000, .anim_A = 0x002F0000, .anim_B = 0x002F0000, .anim_C = 0x002F0000, .anim_D = 0x002F0000, .anim_E = 0x002F0000, .anim_F = 0x002F0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_kmr_32_Script_Idle_Hole = {
    Loop(0)
        Call(TTYD64_Mole_GetState, LVar0)
        IfEq(LVar0, 2)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Loop(0)
        Call(RandInt, 100, LVar0)
        Switch(LVar0)
        CaseLe(55)
            Set(LVar1, 0)
        CaseLe(85)
            Set(LVar1, 1)
        CaseLe(100)
            Set(LVar1, 2)
        EndSwitch
        IfGe(MapVar(3), 15)
            Set(LVar1, 1)
        EndIf
        IfGe(MapVar(2), 35)
            Set(LVar1, 0)
        EndIf
        IfGe(MapVar(1), 70)
            Set(LVar1, 2)
        EndIf
        Set(LVar8, LVar1)
        Call(SetSelfVar, 0, LVar1)
        Switch(LVar1)
        CaseEq(0)
            Add(MapVar(1), 1)
        CaseEq(1)
            Add(MapVar(2), 1)
        CaseEq(2)
            Add(MapVar(3), 1)
        EndSwitch
        Switch(LVar8)
        CaseEq(0)
            Call(SetNpcAnimation, -1, 0x2F0016)
        CaseEq(1)
            Call(SetNpcAnimation, -1, 0x2F0116)
        CaseEq(2)
            Call(SetNpcAnimation, -1, 0x2F0D16)
        EndSwitch
        Call(SetSelfEnemyFlagBits, 1, 0)
        Call(TTYD64_Mole_GetSeconds, LVar0)
        Set(LVar3, LVar0)
        SetF(LVar0, LVar0)
        SetF(LVar1, Float(59.0))
        SetF(LVar2, Float(80.0))
        DivF(LVar0, LVar1)
        MulF(LVar0, LVar2)
        Set(LVar0, LVar0)
        IfLe(LVar0, 45)
            Set(LVar0, 45)
        EndIf
        IfLt(LVar3, 10)
            Set(LVar0, 35)
        EndIf
        Wait(LVar0)
        Call(SetSelfEnemyFlagBits, 1, 1)
        Switch(LVar8)
        CaseEq(0)
            Call(SetNpcAnimation, -1, 0x2F0017)
        CaseEq(1)
            Call(SetNpcAnimation, -1, 0x2F0117)
        CaseEq(2)
            Call(SetNpcAnimation, -1, 0x2F0D17)
        EndSwitch
        Wait(25)
    EndLoop
    Return
    End
};

EvtScript TTYD64_kmr_32_Script_Hit_Hole = {
    Call(SetSelfEnemyFlagBits, 33, 1)
    Call(GetSelfVar, 0, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Call(SetNpcAnimation, -1, 0x2F0005)
        Set(LVar0, 100)
    CaseEq(1)
        Call(SetNpcAnimation, -1, 0x2F0105)
        Set(LVar0, 250)
    CaseEq(2)
        Call(SetNpcAnimation, -1, 0x2F0D05)
        Set(LVar0, 500)
    EndSwitch
    Call(TTYD64_Mole_GetScore, LVar1)
    Add(LVar1, LVar0)
    IfGt(LVar1, 0xF423F)
        Set(LVar1, 0xF423F)
    EndIf
    Call(TTYD64_Mole_SetScore, LVar1)
    Call(PlaySound, 16)
    Wait(20)
    Call(GetSelfVar, 0, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Call(SetNpcAnimation, -1, 0x2F0017)
    CaseEq(1)
        Call(SetNpcAnimation, -1, 0x2F0117)
    CaseEq(2)
        Call(SetNpcAnimation, -1, 0x2F0D17)
    EndSwitch
    Wait(15)
    Call(SetSelfEnemyFlagBits, 32, 0)
    Return
    End
};

NpcData TTYD64_kmr_32_NpcGroup_Monty[] = {
    {
        .id = 0,
        .settings = &TTYD64_kmr_32_NpcSettings_Generic,
        .pos = { 170.0f, 0.0f, -217.0f },
        .flags = 0x00111D09,
        .init = &TTYD64_kmr_32_Script_NPC_Init_Monty,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002F0001, .walk = 0x002F0002, .run = 0x002F0003, .chase = 0x002F0003, .anim_4 = 0x002F0001, .anim_5 = 0x002F0001, .death = 0x002F0005, .hit = 0x002F0005, .anim_8 = 0x002F0000, .anim_9 = 0x002F0000, .anim_A = 0x002F0000, .anim_B = 0x002F0000, .anim_C = 0x002F0000, .anim_D = 0x002F0000, .anim_E = 0x002F0000, .anim_F = 0x002F0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_kmr_32_Script_Mole_AfterGame = {
    Call(DisablePlayerInput, 1)
    Call(TTYD64_Mole_GetScore, LVar1)
    Call(SetMessageValue, LVar1, 0)
    Call(TTYD64_GetMoleHighScore, LVar2)
    IfGt(LVar1, LVar2)
        Call(TTYD64_SetMoleHighScore, LVar1)
        IfEq(GameFlag(4217), 0)
            IfGe(LVar1, 8000)
                Call(SpeakToPlayer, 0, 0x2F0001, 0x2F0001, 0, (Bytecode) TTYD64_kmr_32_String_Monty0_Badge)
                Call(TTYD64_nm_AddBadge, 287, 0)
                Call(ShowGotItem, 287, 1, 0)
                Set(GameFlag(4217), 1)
            Else
                Call(SpeakToPlayer, 0, 0x2F0001, 0x2F0001, 0, (Bytecode) TTYD64_kmr_32_String_Monty0_NewHighscore)
            EndIf
        Else
            Call(SpeakToPlayer, 0, 0x2F0001, 0x2F0001, 0, (Bytecode) TTYD64_kmr_32_String_Monty0_NewHighscore)
        EndIf
    Else
        Call(SpeakToPlayer, 0, 0x2F0001, 0x2F0001, 0, (Bytecode) TTYD64_kmr_32_String_Monty0_NoHighscore)
    EndIf
    Call(TTYD64_Mole_ClearData)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_kmr_32_Script_Interact_Monty0 = {
    IfEq(GameFlag(4216), 0)
        Call(SpeakToPlayer, -1, 0x2F0001, 0x2F0001, 0, (Bytecode) TTYD64_kmr_32_String_Monty0_0)
        Call(CloseMessage)
        Set(GameFlag(4216), 1)
    EndIf
    Call(SpeakToPlayer, -1, 0x2F0001, 0x2F0001, 0, (Bytecode) TTYD64_kmr_32_String_Monty0_1)
    Call(ShowChoice, (Bytecode) TTYD64_kmr_32_String_Choice_Mole)
    Set(LVar1, LVar0)
    Call(CloseMessage)
    Switch(LVar1)
    CaseEq(1)
        Return
    CaseEq(2)
        Call(TTYD64_GetMoleHighScore, LVar1)
        Call(SetMessageValue, LVar1, 0)
        Call(SpeakToPlayer, -1, 0x2F0001, 0x2F0001, 0, (Bytecode) TTYD64_kmr_32_String_Monty0_Stats)
        Return
    EndSwitch
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(255.0))
    ExecWait(TTYD64_Script_FadeScreenOut)
    ExecWait(TTYD64_kmr_32_Script_InitGame)
    Return
    End
};

EvtScript TTYD64_kmr_32_Script_InitGame = {
    Call(FadeOutMusic, 0, 500)
    Call(SetPlayerPos, 5, 0, -214)
    Call(TeleportPartnerToPlayer)
    Call(TTYD64_Mole_StartTimer, 59)
    Call(TTYD64_Mole_SetState, 1)
    Call(SetPlayerFlagBits, 256, 1)
    Call(SetNpcAnimation, -1, 0x2F0012)
    Call(SetEnemyFlagBits, -1, 32, 1)
    SetF(LVar0, Float(25.0))
    SetF(LVar1, Float(5.0))
    ExecWait(TTYD64_Script_FadeScreenIn)
    Wait(95)
    Call(PushSong, 133, 0)
    Return
    End
};

u8 TTYD64_kmr_32_String_Monty0_0[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0xF7,
    0x29, 0xF7, 0x48, 0x41, 0x56, 0x45, 0xF7, 0x41, 0xF7, 0x43, 0x48, 0x41,
    0x4C, 0x4C, 0x45, 0x4E, 0x47, 0x45, 0xF7, 0x46, 0x4F, 0x52, 0xF0, 0x59,
    0x4F, 0x55, 0x0E, 0xF0, 0xF1, 0xFB, 0x2D, 0x59, 0xF7, 0x46, 0x52, 0x49,
    0x45, 0x4E, 0x44, 0x53, 0xF7, 0x41, 0x4E, 0x44, 0xF7, 0x29, 0xF7, 0x48,
    0x41, 0x56, 0x45, 0xF7, 0x48, 0x45, 0x41, 0x44, 0x53, 0xF7, 0x4F, 0x46,
    0xF0, 0x53, 0x54, 0x45, 0x45, 0x4C, 0x01, 0xF0, 0xF1, 0xFB, 0x28, 0x4F,
    0x57, 0xF7, 0x41, 0x42, 0x4F, 0x55, 0x54, 0xF7, 0x49, 0x46, 0xF7, 0x57,
    0x45, 0xF7, 0x50, 0x4C, 0x41, 0x59, 0xF7, 0x41, 0xF7, 0x4C, 0x49, 0x54,
    0x54, 0x4C, 0x45, 0xF0, 0x57, 0x48, 0x41, 0x43, 0x4B, 0x0D, 0x41, 0x0D,
    0x4D, 0x4F, 0x4C, 0x45, 0x1F, 0xF0, 0xF1, 0xFB, 0x29, 0x07, 0x4D, 0xF7,
    0x53, 0x55, 0x52, 0x45, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x57, 0x4F, 0x4E,
    0x07, 0x54, 0xF7, 0x42, 0x45, 0xF7, 0x41, 0x42, 0x4C, 0x45, 0xF7, 0x54,
    0x4F, 0xF7, 0x47, 0x45, 0x54, 0xF0, 0x41, 0x54, 0xF7, 0x4C, 0x45, 0x41,
    0x53, 0x54, 0xF7, 0xFF, 0x24, 0xFF, 0x05, 0x19, 0x18, 0x10, 0x10, 0x10,
    0xF7, 0x50, 0x4F, 0x49, 0x4E, 0x54, 0x53, 0xFF, 0x25, 0x0C, 0xF7, 0x57,
    0x45, 0x07, 0x52, 0x45, 0xF7, 0x54, 0x48, 0x45, 0xF0, 0x46, 0x41, 0x53,
    0x54, 0x45, 0x53, 0x54, 0xF7, 0x4D, 0x4F, 0x4C, 0x45, 0x53, 0xF7, 0x41,
    0x52, 0x4F, 0x55, 0x4E, 0x44, 0xF7, 0x48, 0x45, 0x52, 0x45, 0x01, 0xF1,
    0xFD
};

u8 TTYD64_kmr_32_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x34, 0x48, 0x49, 0x53, 0xF7, 0x49, 0x53, 0xF7,
    0x54, 0x48, 0x45, 0xF7, 0x4C, 0x41, 0x49, 0x52, 0xF7, 0x4F, 0x46, 0xF7,
    0x41, 0xF7, 0x43, 0x4F, 0x55, 0x50, 0x4C, 0x45, 0xF7, 0x4F, 0x46, 0xF0,
    0x46, 0x52, 0x49, 0x45, 0x4E, 0x44, 0x4C, 0x59, 0xF7, 0x2D, 0x4F, 0x55,
    0x4E, 0x54, 0x59, 0xF7, 0x2D, 0x4F, 0x4C, 0x45, 0x53, 0x0C, 0xF7, 0x29,
    0xF7, 0x57, 0x49, 0x53, 0x48, 0xF7, 0x41, 0x4C, 0x4C, 0xF7, 0x4F, 0x55,
    0x52, 0xF0, 0x45, 0x4E, 0x45, 0x4D, 0x49, 0x45, 0x53, 0xF7, 0x57, 0x45,
    0x52, 0x45, 0xF7, 0x4C, 0x49, 0x4B, 0x45, 0xF7, 0x54, 0x48, 0x41, 0x54,
    0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C, 0xF0, 0x46, 0x52, 0x49, 0x45,
    0x4E, 0x44, 0x4C, 0x59, 0x0E, 0xF0, 0xF1, 0xFB, 0x37, 0x45, 0xF7, 0x4E,
    0x45, 0x56, 0x45, 0x52, 0xF7, 0x44, 0x4F, 0xF7, 0x41, 0x4E, 0x59, 0x54,
    0x48, 0x49, 0x4E, 0x47, 0xF7, 0x42, 0x41, 0x44, 0xF7, 0x54, 0x4F, 0xF7,
    0x41, 0x4E, 0x59, 0x4F, 0x4E, 0x45, 0x0C, 0xF0, 0x59, 0x4F, 0x55, 0xF7,
    0x4B, 0x4E, 0x4F, 0x57, 0xF7, 0x57, 0x48, 0x41, 0x54, 0xF7, 0x29, 0xF7,
    0x4D, 0x45, 0x41, 0x4E, 0x1F, 0xF1, 0xFD
};

u8 TTYD64_kmr_32_Tattle_Monty[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x34, 0x48, 0x49, 0x53, 0xF7, 0x49, 0x53, 0xF7,
    0x41, 0xF7, 0x2D, 0x4F, 0x4E, 0x54, 0x59, 0xF7, 0x2D, 0x4F, 0x4C, 0x45,
    0xF7, 0x4C, 0x49, 0x4B, 0x45, 0xF7, 0x4E, 0x4F, 0xF7, 0x4F, 0x54, 0x48,
    0x45, 0x52, 0x0C, 0xF0, 0x48, 0x45, 0xF7, 0x4D, 0x55, 0x53, 0x54, 0xF7,
    0x48, 0x41, 0x56, 0x45, 0xF7, 0x41, 0xF7, 0x48, 0x45, 0x41, 0x44, 0xF7,
    0x4F, 0x46, 0xF7, 0x53, 0x54, 0x45, 0x45, 0x4C, 0xF7, 0x49, 0x46, 0xF7,
    0x48, 0x45, 0xF0, 0x57, 0x41, 0x4E, 0x54, 0x53, 0xF7, 0x55, 0x53, 0xF7,
    0x54, 0x4F, 0xF7, 0x50, 0x4C, 0x41, 0x59, 0xF7, 0x57, 0x49, 0x54, 0x48,
    0xF7, 0x48, 0x49, 0x4D, 0x0C, 0xF7, 0x4A, 0x55, 0x53, 0x54, 0xF7, 0x4C,
    0x49, 0x4B, 0x45, 0xF0, 0x4D, 0x45, 0x0E, 0xF0, 0xF1, 0xFB, 0x34, 0x48,
    0x41, 0x54, 0x07, 0x53, 0xF7, 0x57, 0x48, 0x59, 0xF7, 0x4D, 0x59, 0xF7,
    0x48, 0x45, 0x41, 0x44, 0x42, 0x4F, 0x4E, 0x4B, 0x53, 0xF7, 0x41, 0x52,
    0x45, 0xF7, 0x54, 0x48, 0x45, 0xF0, 0x53, 0x54, 0x52, 0x4F, 0x4E, 0x47,
    0x45, 0x53, 0x54, 0x0C, 0xF7, 0x52, 0x49, 0x47, 0x48, 0x54, 0xF7, 0x2D,
    0x41, 0x52, 0x49, 0x4F, 0x1F, 0xF1, 0xFD
};

EvtScript TTYD64_kmr_32_Script_Main = {
    Set(GameByte(425), 30)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_kmr_32_Script_SetupMusic)
    Exec(TTYD64_kmr_32_Script_EnterMap)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_kmr_32_NpcGroupList_kmr32)
    Return
    End
};

u8 TTYD64_kmr_32_String_Monty0_Stats[] = {
    0xFC, 0x01, 0xFF, 0x09, 0xFF, 0x22, 0xFF, 0x10, 0x00, 0x00, 0xFF, 0x13,
    0x00, 0x28, 0x49, 0x0D, 0x53, 0x43, 0x4F, 0x52, 0x45, 0x1A, 0xF7, 0xFF,
    0x24, 0xFF, 0x05, 0x19, 0xFF, 0x28, 0x00, 0xFF, 0x25, 0xFF, 0x23, 0xFF,
    0x10, 0x00, 0x05, 0xFF, 0x11, 0x09, 0xFF, 0x1A, 0x00, 0x00, 0x0E, 0xFF,
    0x16, 0x00, 0x2F, 0x00, 0xFF, 0x1B, 0x00, 0x00, 0xFF, 0x1C, 0x00, 0xFF,
    0x10, 0x00, 0x5F, 0xFF, 0x11, 0x09, 0xFF, 0x1A, 0x00, 0x00, 0x0E, 0xFF,
    0x16, 0x00, 0x2F, 0x25, 0xFF, 0x1B, 0x00, 0x00, 0xFF, 0x1C, 0x00, 0xFF,
    0x10, 0x00, 0xB9, 0xFF, 0x11, 0x09, 0xFF, 0x1A, 0x00, 0x00, 0x0E, 0xFF,
    0x16, 0x00, 0x2F, 0x26, 0xFF, 0x1B, 0x00, 0x00, 0xFF, 0x1C, 0x00, 0xFF,
    0x23, 0xFF, 0x10, 0x00, 0x0F, 0xFF, 0x13, 0x24, 0x11, 0x10, 0x10, 0xFF,
    0x23, 0xFF, 0x10, 0x00, 0x69, 0xFF, 0x13, 0x24, 0xFF, 0x26, 0x01, 0x12,
    0x15, 0x10, 0xFF, 0x27, 0x01, 0xFF, 0x23, 0xFF, 0x10, 0x00, 0xC3, 0xFF,
    0x13, 0x24, 0xFF, 0x26, 0x01, 0xFF, 0x26, 0x06, 0x15, 0x10, 0x10, 0xFF,
    0x27, 0x06, 0xFF, 0x27, 0x01, 0xFF, 0x23, 0xFF, 0x23, 0xF1, 0xFD
};

EvtScript TTYD64_kmr_32_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Call(TTYD64_Mole_ClearData)
        Set(LVar0, (Bytecode) TTYD64_kmr_32_Script_CreateExitTriggers)
        Exec(EnterWalk)
    CaseEq(1)
        Exec(TTYD64_kmr_32_Script_CreateExitTriggers)
        Exec(TTYD64_kmr_32_Script_Mole_AfterGame)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_kmr_32_Script_Exit0 = {
    SetGroup(27)
    Call(TTYD64_Mole_ClearData)
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "kmr_03", 3)
    Wait(100)
    Return
    End
};

u8 TTYD64_kmr_32_String_Monty0_NewHighscore[] = {
    0xFC, 0x01, 0xFF, 0x24, 0xFF, 0x05, 0x19, 0xFF, 0x28, 0x00, 0xFF, 0x25,
    0x1F, 0xF7, 0x39, 0x4F, 0x55, 0xF7, 0x47, 0x4F, 0x54, 0xF7, 0x41, 0xF7,
    0x4E, 0x45, 0x57, 0xF7, 0x48, 0x49, 0x0D, 0x53, 0x43, 0x4F, 0x52, 0x45,
    0x0C, 0xF0, 0x4E, 0x49, 0x43, 0x45, 0xF7, 0x4A, 0x4F, 0x42, 0x01, 0xF0,
    0xF1, 0xFB, 0x28, 0x45, 0x59, 0x0C, 0xF7, 0x57, 0x48, 0x41, 0x54, 0xF7,
    0x44, 0x4F, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x54, 0x48, 0x49, 0x4E, 0x4B,
    0xF7, 0x49, 0x46, 0xF7, 0x57, 0x45, 0xF7, 0x50, 0x4C, 0x41, 0x59, 0xF0,
    0x4F, 0x4E, 0x45, 0xF7, 0x4D, 0x4F, 0x52, 0x45, 0xF7, 0x47, 0x41, 0x4D,
    0x45, 0x1F, 0xF1, 0xFD
};

u8 TTYD64_kmr_32_String_Monty0_NoHighscore[] = {
    0xFC, 0x01, 0x39, 0x4F, 0x55, 0xF7, 0x47, 0x4F, 0x54, 0xF7, 0x41, 0xF7,
    0x53, 0x43, 0x4F, 0x52, 0x45, 0xF7, 0x4F, 0x46, 0xF7, 0xFF, 0x24, 0xFF,
    0x05, 0x19, 0xFF, 0x28, 0x00, 0xFF, 0x25, 0x0C, 0xF7, 0x4E, 0x4F, 0x54,
    0xF0, 0x42, 0x41, 0x44, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x01, 0xF0,
    0xF1, 0xFB, 0x28, 0x45, 0x59, 0x0C, 0xF7, 0x57, 0x48, 0x41, 0x54, 0xF7,
    0x44, 0x4F, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x54, 0x48, 0x49, 0x4E, 0x4B,
    0xF7, 0x49, 0x46, 0xF7, 0x57, 0x45, 0xF7, 0x50, 0x4C, 0x41, 0x59, 0xF0,
    0x4F, 0x4E, 0x45, 0xF7, 0x4D, 0x4F, 0x52, 0x45, 0xF7, 0x47, 0x41, 0x4D,
    0x45, 0x1F, 0xF1, 0xFD
};

u8 TTYD64_kmr_32_String_Monty0_Badge[] = {
    0xFC, 0x01, 0xFF, 0x24, 0xFF, 0x05, 0x19, 0xFF, 0x28, 0x00, 0xFF, 0x25,
    0x1F, 0x01, 0xF7, 0x37, 0x4F, 0x57, 0x0C, 0xF7, 0x59, 0x4F, 0x55, 0xF7,
    0x41, 0x52, 0x45, 0xF7, 0x42, 0x45, 0x54, 0x54, 0x45, 0x52, 0xF7, 0x54,
    0x48, 0x41, 0x4E, 0xF0, 0x29, 0xF7, 0x45, 0x58, 0x50, 0x45, 0x43, 0x54,
    0x45, 0x44, 0x01, 0xF0, 0xF1, 0xFB, 0x28, 0x45, 0x52, 0x45, 0x0C, 0xF7,
    0x54, 0x41, 0x4B, 0x45, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7, 0x2D, 0x41,
    0x52, 0x49, 0x4F, 0x0C, 0xF7, 0x59, 0x4F, 0x55, 0xF0, 0x44, 0x45, 0x53,
    0x45, 0x52, 0x56, 0x45, 0xF7, 0x49, 0x54, 0x01, 0xF1, 0xFD
};

MapSettings TTYD64_kmr_32_Header = {
    .main = &TTYD64_kmr_32_Script_Main,
    .entryList = &TTYD64_kmr_32_EntryList,
    .entryCount = 2,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_kmr_32_GetTattle },
};

u8 TTYD64_kmr_32_String_Monty0_1[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C,
    0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x57, 0x41, 0x4E, 0x4E, 0x41, 0xF7, 0x50,
    0x4C, 0x41, 0x59, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0xF0, 0x57, 0x48, 0x41,
    0x43, 0x4B, 0x0D, 0x41, 0x0D, 0x4D, 0x4F, 0x4C, 0x45, 0xF7, 0x57, 0x49,
    0x54, 0x48, 0xF7, 0x55, 0x53, 0x1F, 0xF0, 0xFF, 0x04, 0xFD
};

u8 TTYD64_kmr_32_String_Choice_Mole[] = {
    0xFC, 0x05, 0x6E, 0x5A, 0x69, 0x3E, 0xFF, 0x09, 0xFF, 0x1E, 0x00, 0xFF,
    0x21, 0x00, 0x33, 0x55, 0x52, 0x45, 0xF0, 0xFF, 0x1E, 0x01, 0xFF, 0x21,
    0x01, 0x2E, 0x4F, 0xF7, 0x54, 0x48, 0x41, 0x4E, 0x4B, 0x53, 0xF0, 0xFF,
    0x1E, 0x02, 0xFF, 0x21, 0x02, 0x33, 0x54, 0x41, 0x54, 0x53, 0xF0, 0xFF,
    0x21, 0xFF, 0xFF, 0x0A, 0xFF, 0x20, 0x01, 0xFF, 0x1F, 0x03, 0xFD
};

EvtScript TTYD64_kmr_32_Script_NPC_Init_Monty = {
    Call(SetNpcFlagBits, -1, 0x40000, 1)
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_kmr_32_Script_Interact_Monty0)
    Return
    End
};

EvtScript TTYD64_kmr_32_Script_SetupMusic = {
    Call(SetMusic, 0, 17, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript TTYD64_kmr_32_Script_NPC_Init_Hole = {
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_kmr_32_Script_Idle_Hole)
    Call(BindNpcHit, -1, (Bytecode) TTYD64_kmr_32_Script_Hit_Hole)
    Return
    End
};

NpcSettings TTYD64_kmr_32_NpcSettings_Generic = {
    .defaultAnim = 0x00000000,
    .height = 14,
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

EvtScript TTYD64_kmr_32_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_kmr_32_Script_Exit0, 0x80000, 3, 1, 0)
    Return
    End
};

NpcGroupList TTYD64_kmr_32_NpcGroupList_kmr32 = {
    { .npcCount = 1, .npcs = TTYD64_kmr_32_NpcGroup_Monty, .battle = 0x0000, .stage = 0 },
    { .npcCount = 6, .npcs = TTYD64_kmr_32_NpcGroup_Montys, .battle = 0x0000, .stage = 0 },
    {},
};

EntryList TTYD64_kmr_32_EntryList = {
    { -179.0f, 0.0f, -244.0f, 90.0f },
    { 143.0f, 0.0f, -217.0f, 90.0f },
};

MapConfig TTYD64_mapcfg_kmr_32 = {
    .id = "kmr_32",
    .settings = &TTYD64_kmr_32_Header,
    .bgName = "obk_bg",
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_kmr_32(void) {
    TTYD64_nm_BindMessage(TTYD64_kmr_32_Script_Mole_AfterGame, TTYD64_kmr_32_String_Monty0_Badge);
    TTYD64_nm_BindMessage(TTYD64_kmr_32_Script_Mole_AfterGame, TTYD64_kmr_32_String_Monty0_NewHighscore);
    TTYD64_nm_BindMessage(TTYD64_kmr_32_Script_Mole_AfterGame, TTYD64_kmr_32_String_Monty0_NoHighscore);
    TTYD64_nm_BindMessage(TTYD64_kmr_32_Script_Interact_Monty0, TTYD64_kmr_32_String_Monty0_0);
    TTYD64_nm_BindMessage(TTYD64_kmr_32_Script_Interact_Monty0, TTYD64_kmr_32_String_Monty0_1);
    TTYD64_nm_BindMessage(TTYD64_kmr_32_Script_Interact_Monty0, TTYD64_kmr_32_String_Choice_Mole);
    TTYD64_nm_BindMessage(TTYD64_kmr_32_Script_Interact_Monty0, TTYD64_kmr_32_String_Monty0_Stats);
    TTYD64_kmr_32_NpcGroup_Monty[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_kmr_32_Tattle_Monty);
    TTYD64_kmr_32_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_kmr_32_String_Tattle);
}
