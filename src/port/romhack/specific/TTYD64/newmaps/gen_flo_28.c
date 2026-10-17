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

API_CALLABLE(AssignBlockFlag);
API_CALLABLE(AssignScript);
API_CALLABLE(BindNpcDefeat);
API_CALLABLE(BindNpcHit);
API_CALLABLE(BindNpcIdle);
API_CALLABLE(BindNpcInteract);
API_CALLABLE(DisablePartnerAI);
API_CALLABLE(DisablePlayerInput);
API_CALLABLE(DisablePlayerPhysics);
API_CALLABLE(EnableNpcShadow);
API_CALLABLE(EnablePartnerAI);
API_CALLABLE(GetBattleOutcome);
API_CALLABLE(GetCurrentPartnerID);
API_CALLABLE(GetEntryID);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GetNpcAnimation);
API_CALLABLE(GetPartnerInUse);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GetSelfNpcID);
API_CALLABLE(GetSelfVar);
API_CALLABLE(GotoMap);
API_CALLABLE(HidePlayerShadow);
API_CALLABLE(InterpPlayerYaw);
API_CALLABLE(InterruptUsePartner);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(MakeNpcs);
API_CALLABLE(PlaySound);
API_CALLABLE(PlayerJump);
API_CALLABLE(PlayerJump2);
API_CALLABLE(PlayerMoveTo);
API_CALLABLE(RotateModel);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetCamTarget);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcFlagBits);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetNpcVar);
API_CALLABLE(SetPlayerActionState);
API_CALLABLE(SetPlayerAnimation);
API_CALLABLE(SetPlayerFlagBits);
API_CALLABLE(SetPlayerImgFXFlags);
API_CALLABLE(SetPlayerJumpscale);
API_CALLABLE(SetPlayerPos);
API_CALLABLE(SetSelfEnemyFlagBits);
API_CALLABLE(SetSelfVar);
API_CALLABLE(SetTexPanner);
API_CALLABLE(SpeakToPlayer);
API_CALLABLE(StartBossBattle);
API_CALLABLE(StopSound);
API_CALLABLE(TranslateModel);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UpdatePlayerImgFX);
API_CALLABLE(func_802D2484);

extern EvtScript TTYD64_flo_28_Script_PullPlant;
extern NpcData TTYD64_flo_28_NpcGroup_Dayzee2[];
extern NpcData TTYD64_flo_28_NpcGroup_Dayzee1[];
extern NpcData TTYD64_flo_28_NpcGroup_Dayzee4[];
extern NpcData TTYD64_flo_28_NpcGroup_Dayzee3[];
extern NpcData TTYD64_flo_28_NpcGroup_Dayzee5[];
extern NpcData TTYD64_flo_28_NpcGroup_Bzzap1[];
extern NpcData TTYD64_flo_28_NpcGroup_Bzzap2[];
extern NpcData TTYD64_flo_28_NpcGroup_Bzzap3[];
extern EvtScript TTYD64_flo_28_Script_EnterVerticalPipe;
extern EvtScript TTYD64_flo_28_Script_Outcome;
extern EvtScript TTYD64_flo_28_Script_ExitVerticalPipe;
extern EvtScript TTYD64_flo_28_Script_SetupTexturePan;
extern EvtScript TTYD64_flo_28_Script_ExitSecretTunnel;
extern EvtScript TTYD64_flo_28_Script_Idle;
extern EvtScript TTYD64_flo_28_Script_Main;
extern EvtScript TTYD64_flo_28_Script_StartBattle;
extern EvtScript TTYD64_flo_28_Script_ScriptedSpring;
extern EvtScript TTYD64_flo_28_Script_EnterMap_Spring;
extern EvtScript TTYD64_flo_28_Script_TexturePan_Update;
extern EvtScript TTYD64_flo_28_Script_MakeEntities;
extern u8 TTYD64_flo_28_Tattle_Dayzee[];
extern u8 TTYD64_flo_28_Tattle_NPC[];
extern u8 TTYD64_flo_28_String_Dayzee0_1[];
extern u8 TTYD64_flo_28_String_Tattle[];
extern EvtScript TTYD64_flo_28_Script_SetupMusic;
extern NpcGroupList TTYD64_flo_28_NpcGroupList_flo28;
extern EvtScript TTYD64_flo_28_Script_InitNPC_Dayzee1;
extern EvtScript TTYD64_flo_28_Script_InitNPC_Dayzee3;
extern EvtScript TTYD64_flo_28_Script_InitNPC_Dayzee2;
extern EvtScript TTYD64_flo_28_Script_InitNPC_Dayzee5;
extern EvtScript TTYD64_flo_28_Script_InitNPC_Dayzee4;
extern EvtScript TTYD64_flo_28_Script_InitNPC_Bzzap1;
extern u8 TTYD64_flo_28_String_Dayzee1_1[];
extern EvtScript TTYD64_flo_28_Script_Exit1;
extern EvtScript TTYD64_flo_28_Script_InitNPC_Bzzap3;
extern u8 TTYD64_flo_28_String_Ouch[];
extern EvtScript TTYD64_flo_28_Script_InitNPC_Bzzap2;
extern EvtScript TTYD64_flo_28_Script_BindScripts;
extern u8 TTYD64_flo_28_String_Dayzee2_1[];
extern u8 TTYD64_flo_28_String_Bzzap1_1[];
extern MapSettings TTYD64_flo_28_Header;
extern EvtScript TTYD64_flo_28_Script_Entity_Shine1;
extern EvtScript TTYD64_flo_28_Script_InitNPC_HitBox;
extern EvtScript TTYD64_flo_28_Script_Interact_Dayzee4;
extern EvtScript TTYD64_flo_28_Script_Interact_Dayzee3;
extern EvtScript TTYD64_flo_28_Script_Interact_Dayzee5;
extern EvtScript TTYD64_flo_28_Script_Interact_Dayzee2;
extern EvtScript TTYD64_flo_28_Script_Interact_Dayzee1;
extern EvtScript TTYD64_flo_28_Script_Interact_Bzzap1;
extern EvtScript TTYD64_flo_28_Script_GotoMap_Exit1;
extern NpcSettings TTYD64_flo_28_NPCSettings_NPC;
extern EvtScript TTYD64_flo_28_Script_CreateExitTriggers;
extern EntryList TTYD64_flo_28_EntryList;
extern u8 TTYD64_flo_28_String_Dayzee3_1[];

// clang-format off
static s32 TTYD64_flo_28_GetTattleMsg;

static s32 TTYD64_flo_28_GetTattle(void) {
    return TTYD64_flo_28_GetTattleMsg;
}

EvtScript TTYD64_flo_28_Script_PullPlant = {
    Set(LVar6, 32)
    Call(TTYD64_TestPlayerAnimFlags, PA_FLAG_USING_WATT, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_SetPartnerAbilityState, PARTNER_WATT, 2)
        Wait(1)
    EndIf
    Call(DisablePartnerAI, 0)
    Call(SetPlayerActionState, 9)
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    ChildThread
        Label(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetCamTarget, 0, LVar0, LVar1, LVar2)
        Wait(1)
        Goto(0)
    EndChildThread
    Call(InterpPlayerYaw, 90, 0)
    Call(SetPlayerAnimation, 0x10002)
    Call(SetPlayerAnimation, 0x80005)
    Call(GetModelCenter, LVar6)
    Add(LVar0, 4)
    Sub(LVar1, 65)
    Add(LVar2, 5)
    Call(SetPlayerPos, LVar0, LVar1, LVar2)
    Wait(3)
    Call(PlaySound, 8386)
    Call(MakeLerp, 0, -4, 4, 0)
    Loop(0)
        Call(UpdateLerp)
        Set(LVar3, LVar0)
        Set(LVar4, LVar1)
        Call(TranslateModel, LVar6, 0, LVar3, 0)
        Call(GetModelCenter, LVar6)
        Add(LVar0, 4)
        Sub(LVar1, 65)
        Add(LVar2, 5)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
        IfEq(LVar4, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(MakeLerp, -4, 0, 4, 0)
    Loop(0)
        Call(UpdateLerp)
        Set(LVar3, LVar0)
        Set(LVar4, LVar1)
        Call(TranslateModel, LVar6, 0, LVar3, 0)
        Call(GetModelCenter, LVar6)
        Add(LVar0, 4)
        Sub(LVar1, 65)
        Add(LVar2, 5)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
        IfEq(LVar4, 0)
            BreakLoop
        EndIf
    EndLoop
    Wait(2)
    Thread
        Wait(5)
        Call(PlaySound, 338)
    EndThread
    Call(MakeLerp, 0, -20, 25, 0)
    Loop(0)
        Call(UpdateLerp)
        Set(LVar3, LVar0)
        Set(LVar4, LVar1)
        Call(TranslateModel, LVar6, 0, LVar3, 0)
        Call(GetModelCenter, LVar6)
        Add(LVar0, 4)
        Sub(LVar1, 65)
        Add(LVar2, 5)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
        IfEq(LVar4, 0)
            BreakLoop
        EndIf
    EndLoop
    Wait(1)
    Thread
        Call(PlaySound, 8329)
        Call(MakeLerp, -32, 7, 5, 0)
        Loop(0)
            Call(UpdateLerp)
            Set(LVar3, LVar0)
            Set(LVar4, LVar1)
            Call(TranslateModel, LVar6, 0, LVar3, 0)
            Wait(1)
            IfEq(LVar4, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(MakeLerp, 7, 0, 6, 0)
        Loop(0)
            Call(UpdateLerp)
            Set(LVar3, LVar0)
            Set(LVar4, LVar1)
            Call(TranslateModel, LVar6, 0, LVar3, 0)
            Wait(1)
            IfEq(LVar4, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Call(SetPlayerAnimation, 0x10008)
    Call(SetPlayerJumpscale, Float(0.7001953125))
    Call(PlayerJump2, 190, 74, -182, 15)
    Thread
        Call(PlaySound, 167)
        Wait(5)
        Call(StopSound, 167)
    EndThread
    Thread
        Call(MakeLerp, 0, 180, 15, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, 58, LVar0, 0, -1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Wait(5)
    Call(GetPlayerPos, LVar4, LVar5, LVar6)
    Set(LVar7, LVar6)
    Sub(LVar7, 55)
    Call(MakeLerp, LVar6, LVar7, 15, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(SetPlayerPos, LVar4, LVar5, LVar0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Call(EnablePartnerAI)
    Return
    End
};

NpcData TTYD64_flo_28_NpcGroup_Dayzee2[] = {
    {
        .id = 3,
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 101.0f, 0.0f, -145.0f },
        .flags = 0x00440C0D,
        .init = &TTYD64_flo_28_Script_InitNPC_Dayzee2,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00480007, .walk = 0x00480000, .run = 0x00480000, .chase = 0x00480000, .anim_4 = 0x00480000, .anim_5 = 0x00480000, .death = 0x00480008, .hit = 0x00480008, .anim_8 = 0x00480000, .anim_9 = 0x00480000, .anim_A = 0x00480000, .anim_B = 0x00480000, .anim_C = 0x00480000, .anim_D = 0x00480000, .anim_E = 0x00480000, .anim_F = 0x00480000 },
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
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 101.0f, 0.0f, -145.0f },
        .flags = 0x21544C0C,
        .init = &TTYD64_flo_28_Script_InitNPC_HitBox,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00480007, .walk = 0x00480000, .run = 0x00480000, .chase = 0x00480000, .anim_4 = 0x00480000, .anim_5 = 0x00480000, .death = 0x00480008, .hit = 0x00480008, .anim_8 = 0x00480000, .anim_9 = 0x00480000, .anim_A = 0x00480000, .anim_B = 0x00480000, .anim_C = 0x00480000, .anim_D = 0x00480000, .anim_E = 0x00480000, .anim_F = 0x00480000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_flo_28_NpcGroup_Dayzee1[] = {
    {
        .id = 1,
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 350.0f, 0.0f, -63.0f },
        .flags = 0x00440C0D,
        .init = &TTYD64_flo_28_Script_InitNPC_Dayzee1,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00480101, .walk = 0x00480100, .run = 0x00480100, .chase = 0x00480100, .anim_4 = 0x00480100, .anim_5 = 0x00480100, .death = 0x00480108, .hit = 0x00480108, .anim_8 = 0x00480100, .anim_9 = 0x00480100, .anim_A = 0x00480100, .anim_B = 0x00480100, .anim_C = 0x00480100, .anim_D = 0x00480100, .anim_E = 0x00480100, .anim_F = 0x00480100 },
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
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 350.0f, 0.0f, -63.0f },
        .flags = 0x21544C0C,
        .init = &TTYD64_flo_28_Script_InitNPC_HitBox,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00480101, .walk = 0x00480100, .run = 0x00480100, .chase = 0x00480100, .anim_4 = 0x00480100, .anim_5 = 0x00480100, .death = 0x00480108, .hit = 0x00480108, .anim_8 = 0x00480100, .anim_9 = 0x00480100, .anim_A = 0x00480100, .anim_B = 0x00480100, .anim_C = 0x00480100, .anim_D = 0x00480100, .anim_E = 0x00480100, .anim_F = 0x00480100 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_flo_28_NpcGroup_Dayzee4[] = {
    {
        .id = 7,
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 152.0f, 0.0f, 173.0f },
        .flags = 0x00440C0D,
        .init = &TTYD64_flo_28_Script_InitNPC_Dayzee4,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00480007, .walk = 0x00480000, .run = 0x00480000, .chase = 0x00480000, .anim_4 = 0x00480000, .anim_5 = 0x00480000, .death = 0x00480008, .hit = 0x00480000, .anim_8 = 0x00480000, .anim_9 = 0x00480000, .anim_A = 0x00480000, .anim_B = 0x00480000, .anim_C = 0x00480000, .anim_D = 0x00480000, .anim_E = 0x00480000, .anim_F = 0x00480000 },
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
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 152.0f, 0.0f, 173.0f },
        .flags = 0x21544C0C,
        .init = &TTYD64_flo_28_Script_InitNPC_HitBox,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00480007, .walk = 0x00480000, .run = 0x00480000, .chase = 0x00480000, .anim_4 = 0x00480000, .anim_5 = 0x00480000, .death = 0x00480008, .hit = 0x00480000, .anim_8 = 0x00480000, .anim_9 = 0x00480000, .anim_A = 0x00480000, .anim_B = 0x00480000, .anim_C = 0x00480000, .anim_D = 0x00480000, .anim_E = 0x00480000, .anim_F = 0x00480000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_flo_28_NpcGroup_Dayzee3[] = {
    {
        .id = 5,
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 63.0f, 0.0f, -56.0f },
        .flags = 0x00440C0D,
        .init = &TTYD64_flo_28_Script_InitNPC_Dayzee3,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00480001, .walk = 0x00480000, .run = 0x00480000, .chase = 0x00480000, .anim_4 = 0x00480000, .anim_5 = 0x00480000, .death = 0x00480008, .hit = 0x00480008, .anim_8 = 0x00480000, .anim_9 = 0x00480000, .anim_A = 0x00480000, .anim_B = 0x00480000, .anim_C = 0x00480000, .anim_D = 0x00480000, .anim_E = 0x00480000, .anim_F = 0x00480000 },
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
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 63.0f, 0.0f, -56.0f },
        .flags = 0x21544C0C,
        .init = &TTYD64_flo_28_Script_InitNPC_HitBox,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00480001, .walk = 0x00480000, .run = 0x00480000, .chase = 0x00480000, .anim_4 = 0x00480000, .anim_5 = 0x00480000, .death = 0x00480008, .hit = 0x00480008, .anim_8 = 0x00480000, .anim_9 = 0x00480000, .anim_A = 0x00480000, .anim_B = 0x00480000, .anim_C = 0x00480000, .anim_D = 0x00480000, .anim_E = 0x00480000, .anim_F = 0x00480000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_flo_28_NpcGroup_Dayzee5[] = {
    {
        .id = 9,
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 188.0f, 0.0f, 173.0f },
        .flags = 0x00440C0D,
        .init = &TTYD64_flo_28_Script_InitNPC_Dayzee5,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00480007, .walk = 0x00480000, .run = 0x00480000, .chase = 0x00480000, .anim_4 = 0x00480000, .anim_5 = 0x00480000, .death = 0x00480008, .hit = 0x00480000, .anim_8 = 0x00480000, .anim_9 = 0x00480000, .anim_A = 0x00480000, .anim_B = 0x00480000, .anim_C = 0x00480000, .anim_D = 0x00480000, .anim_E = 0x00480000, .anim_F = 0x00480000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 10,
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 188.0f, 0.0f, 173.0f },
        .flags = 0x21544C0C,
        .init = &TTYD64_flo_28_Script_InitNPC_HitBox,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00480007, .walk = 0x00480000, .run = 0x00480000, .chase = 0x00480000, .anim_4 = 0x00480000, .anim_5 = 0x00480000, .death = 0x00480008, .hit = 0x00480000, .anim_8 = 0x00480000, .anim_9 = 0x00480000, .anim_A = 0x00480000, .anim_B = 0x00480000, .anim_C = 0x00480000, .anim_D = 0x00480000, .anim_E = 0x00480000, .anim_F = 0x00480000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_flo_28_NpcGroup_Bzzap1[] = {
    {
        .id = 11,
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 160.0f, 10.0f, -88.0f },
        .flags = 0x00440C0D,
        .init = &TTYD64_flo_28_Script_InitNPC_Bzzap1,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x004B0001, .walk = 0x004B0000, .run = 0x004B0000, .chase = 0x004B0000, .anim_4 = 0x004B0000, .anim_5 = 0x004B0000, .death = 0x004B0000, .hit = 0x004B0006, .anim_8 = 0x004B0006, .anim_9 = 0x004B0000, .anim_A = 0x004B0000, .anim_B = 0x004B0000, .anim_C = 0x004B0000, .anim_D = 0x004B0000, .anim_E = 0x004B0000, .anim_F = 0x004B0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 12,
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 160.0f, 10.0f, -88.0f },
        .flags = 0x21544C0C,
        .init = &TTYD64_flo_28_Script_InitNPC_HitBox,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x004B0001, .walk = 0x004B0000, .run = 0x004B0000, .chase = 0x004B0000, .anim_4 = 0x004B0000, .anim_5 = 0x004B0000, .death = 0x004B0000, .hit = 0x004B0006, .anim_8 = 0x004B0006, .anim_9 = 0x004B0000, .anim_A = 0x004B0000, .anim_B = 0x004B0000, .anim_C = 0x004B0000, .anim_D = 0x004B0000, .anim_E = 0x004B0000, .anim_F = 0x004B0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_flo_28_NpcGroup_Bzzap2[] = {
    {
        .id = 13,
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 198.0f, 17.0f, -173.0f },
        .flags = 0x00440C0D,
        .init = &TTYD64_flo_28_Script_InitNPC_Bzzap2,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x004B0005, .walk = 0x004B0000, .run = 0x004B0000, .chase = 0x004B0000, .anim_4 = 0x004B0000, .anim_5 = 0x004B0000, .death = 0x004B0006, .hit = 0x004B0006, .anim_8 = 0x004B0000, .anim_9 = 0x004B0000, .anim_A = 0x004B0000, .anim_B = 0x004B0000, .anim_C = 0x004B0000, .anim_D = 0x004B0000, .anim_E = 0x004B0000, .anim_F = 0x004B0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 14,
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 198.0f, 17.0f, -173.0f },
        .flags = 0x21544C0C,
        .init = &TTYD64_flo_28_Script_InitNPC_HitBox,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x004B0005, .walk = 0x004B0000, .run = 0x004B0000, .chase = 0x004B0000, .anim_4 = 0x004B0000, .anim_5 = 0x004B0000, .death = 0x004B0006, .hit = 0x004B0006, .anim_8 = 0x004B0000, .anim_9 = 0x004B0000, .anim_A = 0x004B0000, .anim_B = 0x004B0000, .anim_C = 0x004B0000, .anim_D = 0x004B0000, .anim_E = 0x004B0000, .anim_F = 0x004B0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_flo_28_NpcGroup_Bzzap3[] = {
    {
        .id = 15,
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 250.0f, 17.0f, -173.0f },
        .flags = 0x00440C0D,
        .init = &TTYD64_flo_28_Script_InitNPC_Bzzap3,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x004B000A, .walk = 0x004B0000, .run = 0x004B0000, .chase = 0x004B0000, .anim_4 = 0x004B0000, .anim_5 = 0x004B0000, .death = 0x004B0006, .hit = 0x004B0006, .anim_8 = 0x004B0000, .anim_9 = 0x004B0000, .anim_A = 0x004B0000, .anim_B = 0x004B0000, .anim_C = 0x004B0000, .anim_D = 0x004B0000, .anim_E = 0x004B0000, .anim_F = 0x004B0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 16,
        .settings = &TTYD64_flo_28_NPCSettings_NPC,
        .pos = { 250.0f, 17.0f, -173.0f },
        .flags = 0x21544C0C,
        .init = &TTYD64_flo_28_Script_InitNPC_HitBox,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 270,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x004B000A, .walk = 0x004B0000, .run = 0x004B0000, .chase = 0x004B0000, .anim_4 = 0x004B0000, .anim_5 = 0x004B0000, .death = 0x004B0006, .hit = 0x004B0006, .anim_8 = 0x004B0000, .anim_9 = 0x004B0000, .anim_A = 0x004B0000, .anim_B = 0x004B0000, .anim_C = 0x004B0000, .anim_D = 0x004B0000, .anim_E = 0x004B0000, .anim_F = 0x004B0000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x01,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_flo_28_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_flo_28_Script_Outcome = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
    CaseOrEq(0)
    CaseOrEq(3)
        Set(LVar0, 1)
        Set(LVar1, 0x480008)
        Exec(TTYD64_DoNpcDefeat)
        Set(LVar0, 3)
        Set(LVar1, 0x480008)
        Exec(TTYD64_DoNpcDefeat)
        Set(LVar0, 5)
        Set(LVar1, 0x480008)
        Exec(TTYD64_DoNpcDefeat)
        Set(LVar0, 7)
        Set(LVar1, 0x480008)
        Exec(TTYD64_DoNpcDefeat)
        Set(LVar0, 9)
        Set(LVar1, 0x480008)
        Exec(TTYD64_DoNpcDefeat)
        Set(LVar0, 11)
        Set(LVar1, 0x4B0006)
        Exec(TTYD64_DoNpcDefeat)
        Set(LVar0, 13)
        Set(LVar1, 0x4B0006)
        Exec(TTYD64_DoNpcDefeat)
        Set(LVar0, 15)
        Set(LVar1, 0x4B0006)
        Exec(TTYD64_DoNpcDefeat)
        Call(SetNpcPos, 1, 0, -1000, 0)
        Call(SetNpcPos, 3, 0, -1000, 0)
        Call(SetNpcPos, 5, 0, -1000, 0)
        Call(SetNpcPos, 7, 0, -1000, 0)
        Call(SetNpcPos, 9, 0, -1000, 0)
        Call(SetNpcPos, 11, 0, -1000, 0)
        Call(SetNpcPos, 13, 0, -1000, 0)
        Call(SetNpcPos, 15, 0, -1000, 0)
        Call(SetSelfEnemyFlagBits, 4, 1)
        Set(GameFlag(5521), 1)
        Call(DisablePlayerInput, 0)
        Return
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_flo_28_Script_ExitVerticalPipe = {
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

EvtScript TTYD64_flo_28_Script_SetupTexturePan = {
    Call(SetTexPanner, 40, 0)
    Call(SetTexPanner, 42, 1)
    Call(SetTexPanner, 50, 0)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 140)
        Set(LVar2, -80)
        Set(LVar3, -70)
        Set(LVar4, 100)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_flo_28_Script_TexturePan_Update)
    EndThread
    Thread
        Set(LVar0, 1)
        Set(LVar1, -70)
        Set(LVar2, 100)
        Set(LVar3, 100)
        Set(LVar4, -40)
        Set(LVar5, 1)
        Set(LVar6, 1)
        Set(LVar7, 1)
        Set(LVar8, 1)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_flo_28_Script_TexturePan_Update)
    EndThread
    Return
    End
};

EvtScript TTYD64_flo_28_Script_ExitSecretTunnel = {
    Call(DisablePlayerPhysics, 1)
    Call(DisablePlayerInput, 1)
    Thread
        Call(PlaySound, 167)
        Wait(5)
        Call(StopSound, 167)
    EndThread
    Thread
        Call(MakeLerp, 0, 180, 15, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, 58, LVar0, 0, -1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Wait(5)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Add(LVar2, 25)
    Call(PlayerMoveTo, LVar0, LVar2, 10)
    Call(DisablePlayerPhysics, 0)
    Call(DisablePlayerInput, 0)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_Idle = {
    Loop(0)
        Call(GetSelfVar, 0, LVar0)
        IfEq(LVar0, 1)
            Call(DisablePlayerInput, 1)
            Call(SetSelfVar, 0, 0)
            Call(SetNpcAnimation, 1, 0x480105)
            Call(SetNpcAnimation, 3, 0x480005)
            Call(SetNpcAnimation, 5, 0x480005)
            Call(SetNpcAnimation, 7, 0x480005)
            Call(SetNpcAnimation, 9, 0x480005)
            Call(SetNpcAnimation, 11, 0x4B0005)
            Call(SetNpcAnimation, 13, 0x4B0005)
            Call(SetNpcAnimation, 15, 0x4B0005)
            Call(GetNpcAnimation, -1, LVar0)
            Call(SpeakToPlayer, -1, LVar0, LVar0, 0, (Bytecode) TTYD64_flo_28_String_Ouch)
            Call(StartBossBattle, 3)
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_flo_28_Script_Main = {
    Set(GameByte(425), 38)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Exec(TTYD64_flo_28_Script_SetupMusic)
    Exec(TTYD64_flo_28_Script_SetupTexturePan)
    ExecWait(TTYD64_flo_28_Script_MakeEntities)
    Exec(TTYD64_flo_28_Script_BindScripts)
    IfEq(GameFlag(5521), 0)
        Call(MakeNpcs, 1, (Bytecode) TTYD64_flo_28_NpcGroupList_flo28)
    EndIf
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 0)
        Set(LVarA, (Bytecode) TTYD64_flo_28_Script_CreateExitTriggers)
        Exec(TTYD64_flo_28_Script_EnterMap_Spring)
    Else
        Set(LVarA, (Bytecode) TTYD64_flo_28_Script_CreateExitTriggers)
        Exec(TTYD64_flo_28_Script_EnterVerticalPipe)
    EndIf
    Return
    End
};

EvtScript TTYD64_flo_28_Script_StartBattle = {
    Call(SetSelfEnemyFlagBits, 0x1F000000, 1)
    Call(GetSelfNpcID, LVar0)
    Sub(LVar0, 1)
    Call(SetNpcVar, LVar0, 0, 1)
    Call(SetNpcPos, 2, 0, -1000, 0)
    Call(SetNpcPos, 4, 0, -1000, 0)
    Call(SetNpcPos, 6, 0, -1000, 0)
    Call(SetNpcPos, 8, 0, -1000, 0)
    Call(SetNpcPos, 10, 0, -1000, 0)
    Call(SetNpcPos, 12, 0, -1000, 0)
    Call(SetNpcPos, 14, 0, -1000, 0)
    Call(SetNpcPos, 16, 0, -1000, 0)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_ScriptedSpring = {
    IfEq(MapFlag(0), 1)
        Return
    EndIf
    Call(DisablePlayerInput, 1)
    Call(DisablePlayerPhysics, 1)
    Call(SetPlayerActionState, 6)
    Wait(1)
    Call(SetPlayerJumpscale, Float(0.7001953125))
    Thread
        Wait(10)
        Call(GotoMap, (Bytecode) "flo_22", 1)
    EndThread
    Call(PlayerJump, -259, 198, -9, 30)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_EnterMap_Spring = {
    Set(MapFlag(0), 1)
    Call(DisablePlayerInput, 1)
    Call(SetPlayerActionState, 8)
    Call(func_802D2484)
    Call(SetPlayerActionState, 6)
    Call(SetPlayerJumpscale, Float(1.5))
    Call(PlayerJump, -216, -9, -9, 16)
    Call(SetPlayerAnimation, 0x10002)
    Call(DisablePlayerInput, 0)
    Set(MapFlag(0), 0)
    Exec(LVarA)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_TexturePan_Update = {
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

EvtScript TTYD64_flo_28_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_ScriptSpring), -260, -9, -11, 0, 0x80000000)
    Call(AssignScript, (Bytecode) TTYD64_flo_28_Script_ScriptedSpring)
    Call(MakeEntity, Ref(Entity_SuperBlock), 321, 57, 89, -180, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(5520))
    Call(AssignScript, (Bytecode) TTYD64_flo_28_Script_Entity_Shine1)
    Return
    End
};

u8 TTYD64_flo_28_Tattle_Dayzee[] = {
    0xFC, 0x01, 0x29, 0x07, 0x4D, 0xF7, 0x47, 0x4C, 0x41, 0x44, 0xF7, 0x48,
    0x45, 0xF7, 0x49, 0x4E, 0x56, 0x49, 0x54, 0x45, 0x44, 0xF7, 0x55, 0x53,
    0xF7, 0x49, 0x4E, 0x54, 0x4F, 0xF7, 0x48, 0x49, 0x53, 0xF0, 0x48, 0x55,
    0x4D, 0x42, 0x4C, 0x45, 0xF7, 0x41, 0x42, 0x4F, 0x44, 0x45, 0x0E, 0xF0,
    0xF1, 0xFB, 0x21, 0x4C, 0x54, 0x48, 0x4F, 0x55, 0x47, 0x48, 0xF7, 0x49,
    0x54, 0xF7, 0x53, 0x45, 0x45, 0x4D, 0x53, 0xF7, 0x54, 0x48, 0x41, 0x54,
    0xF7, 0x4D, 0x4F, 0x53, 0x54, 0xF0, 0x4F, 0x54, 0x48, 0x45, 0x52, 0x53,
    0xF7, 0x41, 0x52, 0x45, 0xF7, 0x4E, 0x4F, 0x54, 0xF7, 0x56, 0x45, 0x52,
    0x59, 0xF7, 0x46, 0x4F, 0x4E, 0x44, 0xF7, 0x4F, 0x46, 0xF0, 0x54, 0x48,
    0x41, 0x54, 0xF7, 0x49, 0x44, 0x45, 0x41, 0xF7, 0x57, 0x48, 0x45, 0x4E,
    0xF7, 0x54, 0x48, 0x45, 0x59, 0xF7, 0x53, 0x41, 0x57, 0xF7, 0x49, 0x54,
    0xF7, 0x57, 0x41, 0x53, 0xF0, 0x59, 0x4F, 0x55, 0xF7, 0x2D, 0x41, 0x52,
    0x49, 0x4F, 0xF7, 0xF1, 0xFD
};

u8 TTYD64_flo_28_Tattle_NPC[] = {
    0xFC, 0x01, 0x21, 0xF7, 0x52, 0x45, 0x53, 0x49, 0x44, 0x45, 0x4E, 0x54,
    0xF7, 0x4F, 0x46, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7, 0x42, 0x45, 0x41,
    0x55, 0x54, 0x49, 0x46, 0x55, 0x4C, 0xF7, 0x57, 0x45, 0x4C, 0x4C, 0x0E,
    0xF0, 0xF1, 0xFB, 0x29, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x4B,
    0x4E, 0x4F, 0x57, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0C, 0xF7, 0x29,
    0xF7, 0x46, 0x45, 0x45, 0x4C, 0xF7, 0x4C, 0x49, 0x4B, 0x45, 0xF0, 0x4E,
    0x4F, 0x54, 0xF7, 0x45, 0x56, 0x45, 0x52, 0x59, 0x4F, 0x4E, 0x45, 0xF7,
    0x4C, 0x49, 0x4B, 0x45, 0x53, 0xF7, 0x55, 0x53, 0xF7, 0x48, 0x45, 0x52,
    0x45, 0xF7, 0x56, 0x45, 0x52, 0x59, 0xF0, 0x4D, 0x55, 0x43, 0x48, 0x0E,
    0xF0, 0xF1, 0xFB, 0x2B, 0x45, 0x45, 0x50, 0xF7, 0x59, 0x4F, 0x55, 0x52,
    0xF7, 0x47, 0x55, 0x41, 0x52, 0x44, 0xF7, 0x55, 0x50, 0x0E, 0xF1, 0xFD
};

u8 TTYD64_flo_28_String_Dayzee0_1[] = {
    0xFC, 0x01, 0x37, 0x41, 0x49, 0x54, 0x0C, 0xF7, 0x53, 0x4F, 0xF7, 0x49,
    0x54, 0xF7, 0x57, 0x41, 0x53, 0xF7, 0x41, 0x43, 0x54, 0x55, 0x41, 0x4C,
    0x4C, 0x59, 0xF7, 0x59, 0x4F, 0x55, 0x0E, 0x0E, 0x0E, 0xF0, 0x21, 0x4E,
    0x59, 0x57, 0x41, 0x59, 0x53, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x44, 0x4F,
    0x4E, 0x07, 0x54, 0xF7, 0x53, 0x45, 0x45, 0x4D, 0xF7, 0x41, 0x53, 0xF7,
    0x42, 0x41, 0x44, 0xF0, 0x41, 0x53, 0xF7, 0x45, 0x56, 0x45, 0x52, 0x59,
    0x4F, 0x4E, 0x45, 0xF7, 0x53, 0x41, 0x59, 0x53, 0x0E, 0xF0, 0xF1, 0xFB,
    0x39, 0x4F, 0x55, 0x07, 0x52, 0x45, 0xF7, 0x57, 0x45, 0x4C, 0x43, 0x4F,
    0x4D, 0x45, 0xF7, 0x48, 0x45, 0x52, 0x45, 0xF7, 0x41, 0x4E, 0x59, 0x54,
    0x49, 0x4D, 0x45, 0xF7, 0x59, 0x4F, 0x55, 0xF0, 0x57, 0x41, 0x4E, 0x54,
    0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x01, 0xF1, 0xFD
};

u8 TTYD64_flo_28_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x37, 0x4F, 0x57, 0x0C, 0xF7, 0x2D, 0x41, 0x52,
    0x49, 0x4F, 0xF7, 0x49, 0x54, 0xF7, 0x53, 0x45, 0x45, 0x4D, 0x53, 0xF7,
    0x4C, 0x49, 0x4B, 0x45, 0xF7, 0x57, 0x45, 0xF7, 0x41, 0x52, 0x45, 0xF0,
    0x49, 0x4E, 0xF7, 0x54, 0x48, 0x45, 0xF7, 0x24, 0x41, 0x59, 0x5A, 0x45,
    0x45, 0x53, 0x07, 0xF7, 0x41, 0x42, 0x4F, 0x44, 0x45, 0x0C, 0xF0, 0x29,
    0xF7, 0x57, 0x49, 0x4C, 0x4C, 0xF7, 0x4E, 0x4F, 0x54, 0xF7, 0x44, 0x45,
    0x4E, 0x59, 0xF7, 0x49, 0x54, 0x0C, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7,
    0x50, 0x4C, 0x41, 0x43, 0x45, 0xF0, 0x4C, 0x4F, 0x4F, 0x4B, 0x53, 0xF7,
    0x56, 0x45, 0x52, 0x59, 0xF7, 0x43, 0x4F, 0x4D, 0x46, 0x4F, 0x52, 0x54,
    0x41, 0x42, 0x4C, 0x45, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_flo_28_Script_SetupMusic = {
    Switch(GameByte(0))
    CaseLt(53)
        Call(SetMusic, 0, 48, 0, 8)
    CaseDefault
        Call(SetMusic, 0, 49, 0, 8)
    EndSwitch
    Return
    End
};

NpcGroupList TTYD64_flo_28_NpcGroupList_flo28 = {
    { .npcCount = 2, .npcs = TTYD64_flo_28_NpcGroup_Dayzee1, .battle = 0x1825, .stage = 11 },
    { .npcCount = 2, .npcs = TTYD64_flo_28_NpcGroup_Dayzee2, .battle = 0x1825, .stage = 11 },
    { .npcCount = 2, .npcs = TTYD64_flo_28_NpcGroup_Dayzee3, .battle = 0x1825, .stage = 11 },
    { .npcCount = 2, .npcs = TTYD64_flo_28_NpcGroup_Dayzee4, .battle = 0x1825, .stage = 11 },
    { .npcCount = 2, .npcs = TTYD64_flo_28_NpcGroup_Dayzee5, .battle = 0x1825, .stage = 11 },
    { .npcCount = 2, .npcs = TTYD64_flo_28_NpcGroup_Bzzap1, .battle = 0x1825, .stage = 11 },
    { .npcCount = 2, .npcs = TTYD64_flo_28_NpcGroup_Bzzap2, .battle = 0x1825, .stage = 11 },
    { .npcCount = 2, .npcs = TTYD64_flo_28_NpcGroup_Bzzap3, .battle = 0x1825, .stage = 11 },
    {},
};

EvtScript TTYD64_flo_28_Script_InitNPC_Dayzee1 = {
    Call(SetSelfVar, 0, 0)
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_flo_28_Script_Idle)
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_flo_28_Script_Interact_Dayzee1)
    Call(BindNpcDefeat, -1, (Bytecode) TTYD64_flo_28_Script_Outcome)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_InitNPC_Dayzee3 = {
    Call(SetSelfVar, 0, 0)
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_flo_28_Script_Idle)
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_flo_28_Script_Interact_Dayzee3)
    Call(BindNpcDefeat, -1, (Bytecode) TTYD64_flo_28_Script_Outcome)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_InitNPC_Dayzee2 = {
    Call(SetSelfVar, 0, 0)
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_flo_28_Script_Idle)
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_flo_28_Script_Interact_Dayzee2)
    Call(BindNpcDefeat, -1, (Bytecode) TTYD64_flo_28_Script_Outcome)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_InitNPC_Dayzee5 = {
    Call(SetSelfVar, 0, 0)
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_flo_28_Script_Idle)
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_flo_28_Script_Interact_Dayzee5)
    Call(BindNpcDefeat, -1, (Bytecode) TTYD64_flo_28_Script_Outcome)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_InitNPC_Dayzee4 = {
    Call(SetSelfVar, 0, 0)
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_flo_28_Script_Idle)
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_flo_28_Script_Interact_Dayzee4)
    Call(BindNpcDefeat, -1, (Bytecode) TTYD64_flo_28_Script_Outcome)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_InitNPC_Bzzap1 = {
    Call(SetSelfVar, 0, 0)
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_flo_28_Script_Idle)
    Call(BindNpcInteract, -1, (Bytecode) TTYD64_flo_28_Script_Interact_Bzzap1)
    Call(BindNpcDefeat, -1, (Bytecode) TTYD64_flo_28_Script_Outcome)
    Return
    End
};

u8 TTYD64_flo_28_String_Dayzee1_1[] = {
    0xFC, 0x01, 0x28, 0x45, 0x59, 0x0C, 0xF7, 0x29, 0xF7, 0x52, 0x45, 0x41,
    0x4C, 0x4C, 0x59, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF7, 0x47, 0x45,
    0x54, 0xF7, 0x57, 0x48, 0x59, 0xF0, 0x45, 0x56, 0x45, 0x52, 0x59, 0x4F,
    0x4E, 0x45, 0xF7, 0x48, 0x41, 0x54, 0x45, 0x53, 0xF7, 0x59, 0x4F, 0x55,
    0x0C, 0xF7, 0x59, 0x4F, 0x55, 0xF7, 0x4C, 0x4F, 0x4F, 0x4B, 0xF7, 0x4C,
    0x49, 0x4B, 0x45, 0xF0, 0x41, 0xF7, 0x52, 0x45, 0x41, 0x4C, 0x4C, 0x59,
    0xF7, 0x47, 0x4F, 0x4F, 0x44, 0xF7, 0x47, 0x55, 0x59, 0xF7, 0x54, 0x4F,
    0xF7, 0x4D, 0x45, 0x0E, 0xF1, 0xFD
};

EvtScript TTYD64_flo_28_Script_Exit1 = {
    SetGroup(27)
    Set(LVarA, 1)
    Set(LVarB, 24)
    Set(LVarC, (Bytecode) TTYD64_flo_28_Script_GotoMap_Exit1)
    ExecWait(TTYD64_flo_28_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_InitNPC_Bzzap3 = {
    Call(SetSelfVar, 0, 0)
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_flo_28_Script_Idle)
    Call(BindNpcDefeat, -1, (Bytecode) TTYD64_flo_28_Script_Outcome)
    Return
    End
};

u8 TTYD64_flo_28_String_Ouch[] = {
    0xFC, 0x01, 0xFF, 0x26, 0x01, 0x2F, 0x4F, 0x4F, 0x4F, 0x55, 0x43, 0x48,
    0x01, 0xFF, 0x27, 0x01, 0xF0, 0xF1, 0xFB, 0x2C, 0x4F, 0x4F, 0x4B, 0x53,
    0xF7, 0x4C, 0x49, 0x4B, 0x45, 0xF7, 0x59, 0x4F, 0x55, 0x52, 0xF7, 0x54,
    0x52, 0x55, 0x45, 0xF7, 0x43, 0x4F, 0x4C, 0x4F, 0x52, 0x53, 0xF7, 0x41,
    0x52, 0x45, 0xF0, 0x46, 0x49, 0x4E, 0x41, 0x4C, 0x4C, 0x59, 0xF7, 0x53,
    0x48, 0x4F, 0x57, 0x49, 0x4E, 0x47, 0xF7, 0x55, 0x50, 0x01, 0x01, 0xF1,
    0xFD
};

EvtScript TTYD64_flo_28_Script_InitNPC_Bzzap2 = {
    Call(SetSelfVar, 0, 0)
    Call(BindNpcIdle, -1, (Bytecode) TTYD64_flo_28_Script_Idle)
    Call(BindNpcDefeat, -1, (Bytecode) TTYD64_flo_28_Script_Outcome)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_BindScripts = {
    BindTrigger(TTYD64_flo_28_Script_PullPlant, 1024, 13, 1, 0)
    BindTrigger(TTYD64_flo_28_Script_ExitSecretTunnel, 256, 12, 1, 0)
    Return
    End
};

u8 TTYD64_flo_28_String_Dayzee2_1[] = {
    0xFC, 0x01, 0x2C, 0x49, 0x53, 0x54, 0x45, 0x4E, 0xF7, 0x54, 0x4F, 0xF7,
    0x4D, 0x45, 0x0C, 0xF7, 0x2D, 0x41, 0x52, 0x49, 0x4F, 0x0E, 0xF0, 0xF1,
    0xFB, 0x29, 0xF7, 0x44, 0x4F, 0xF7, 0x4E, 0x4F, 0x54, 0xF7, 0x4C, 0x49,
    0x4B, 0x45, 0xF7, 0x59, 0x4F, 0x55, 0x0C, 0xF7, 0x50, 0x4C, 0x45, 0x41,
    0x53, 0x45, 0xF7, 0x44, 0x4F, 0x4E, 0x07, 0x54, 0xF0, 0x54, 0x41, 0x4C,
    0x4B, 0xF7, 0x54, 0x4F, 0xF7, 0x4D, 0x45, 0x0E, 0xF1, 0xFD
};

u8 TTYD64_flo_28_String_Bzzap1_1[] = {
    0xFC, 0x01, 0x34, 0x48, 0x49, 0x53, 0xF7, 0x50, 0x4C, 0x41, 0x43, 0x45,
    0xF7, 0x49, 0x53, 0xF7, 0x52, 0x45, 0x41, 0x4C, 0x4C, 0x59, 0xF7, 0x51,
    0x55, 0x49, 0x45, 0x54, 0x0C, 0xF7, 0x29, 0xF7, 0x48, 0x4F, 0x50, 0x45,
    0xF0, 0x53, 0x4F, 0x4D, 0x45, 0x54, 0x48, 0x49, 0x4E, 0x47, 0xF7, 0x46,
    0x55, 0x4E, 0x4E, 0x59, 0xF7, 0x48, 0x41, 0x50, 0x50, 0x45, 0x4E, 0xF7,
    0x53, 0x4F, 0x4F, 0x4E, 0x0E, 0xF1, 0xFD
};

MapSettings TTYD64_flo_28_Header = {
    .main = &TTYD64_flo_28_Script_Main,
    .entryList = &TTYD64_flo_28_EntryList,
    .entryCount = 2,
    .background = NULL,
    .tattle = { .get = TTYD64_flo_28_GetTattle },
};

EvtScript TTYD64_flo_28_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(5520))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_InitNPC_HitBox = {
    Call(EnableNpcShadow, -1, 0)
    Call(BindNpcHit, -1, (Bytecode) TTYD64_flo_28_Script_StartBattle)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_Interact_Dayzee4 = {
    Call(SpeakToPlayer, -1, 0x480007, 0x480007, 0, (Bytecode) TTYD64_flo_28_String_Dayzee3_1)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_Interact_Dayzee3 = {
    Call(SpeakToPlayer, -1, 0x480001, 0x480001, 0, (Bytecode) TTYD64_flo_28_String_Dayzee2_1)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_Interact_Dayzee5 = {
    Call(SpeakToPlayer, -1, 0x480007, 0x480007, 0, (Bytecode) TTYD64_flo_28_String_Dayzee3_1)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_Interact_Dayzee2 = {
    Call(SpeakToPlayer, -1, 0x480001, 0x480001, 0, (Bytecode) TTYD64_flo_28_String_Dayzee1_1)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_Interact_Dayzee1 = {
    Call(SpeakToPlayer, -1, 0x480101, 0x480101, 0, (Bytecode) TTYD64_flo_28_String_Dayzee0_1)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_Interact_Bzzap1 = {
    Call(SpeakToPlayer, -1, 0x480001, 0x480001, 0, (Bytecode) TTYD64_flo_28_String_Bzzap1_1)
    Return
    End
};

EvtScript TTYD64_flo_28_Script_GotoMap_Exit1 = {
    Call(GotoMap, (Bytecode) "tyd_06", 0)
    Wait(100)
    Return
    End
};

NpcSettings TTYD64_flo_28_NPCSettings_NPC = {
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

EvtScript TTYD64_flo_28_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_flo_28_Script_Exit1, 128, 24, 1, 0)
    Return
    End
};

EntryList TTYD64_flo_28_EntryList = {
    { -259.0f, 198.0f, -9.0f, -270.0f },
    { 370.0f, 30.0f, -234.0f, 90.0f },
};

u8 TTYD64_flo_28_String_Dayzee3_1[] = {
    0xFC, 0x01, 0xFF, 0x26, 0x01, 0x2C, 0x41, 0x4C, 0x41, 0x4C, 0x41, 0xF7,
    0x00, 0x00, 0x00, 0xFF, 0x27, 0x01, 0xF1, 0xFD
};

MapConfig TTYD64_mapcfg_flo_28 = {
    .id = "flo_28",
    .settings = &TTYD64_flo_28_Header,
    .bgName = NULL,
    .init = NULL,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_nm_Install_flo_28(void) {
    TTYD64_nm_BindMessage(TTYD64_flo_28_Script_Idle, TTYD64_flo_28_String_Ouch);
    TTYD64_nm_BindMessage(TTYD64_flo_28_Script_Interact_Dayzee4, TTYD64_flo_28_String_Dayzee3_1);
    TTYD64_nm_BindMessage(TTYD64_flo_28_Script_Interact_Dayzee3, TTYD64_flo_28_String_Dayzee2_1);
    TTYD64_nm_BindMessage(TTYD64_flo_28_Script_Interact_Dayzee5, TTYD64_flo_28_String_Dayzee3_1);
    TTYD64_nm_BindMessage(TTYD64_flo_28_Script_Interact_Dayzee2, TTYD64_flo_28_String_Dayzee1_1);
    TTYD64_nm_BindMessage(TTYD64_flo_28_Script_Interact_Dayzee1, TTYD64_flo_28_String_Dayzee0_1);
    TTYD64_nm_BindMessage(TTYD64_flo_28_Script_Interact_Bzzap1, TTYD64_flo_28_String_Bzzap1_1);
    TTYD64_flo_28_NpcGroup_Dayzee2[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_flo_28_Tattle_NPC);
    TTYD64_flo_28_NpcGroup_Dayzee1[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_flo_28_Tattle_Dayzee);
    TTYD64_flo_28_NpcGroup_Dayzee4[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_flo_28_Tattle_NPC);
    TTYD64_flo_28_NpcGroup_Dayzee3[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_flo_28_Tattle_NPC);
    TTYD64_flo_28_NpcGroup_Dayzee5[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_flo_28_Tattle_NPC);
    TTYD64_flo_28_NpcGroup_Bzzap1[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_flo_28_Tattle_NPC);
    TTYD64_flo_28_NpcGroup_Bzzap2[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_flo_28_Tattle_NPC);
    TTYD64_flo_28_NpcGroup_Bzzap3[0].tattle = Mod_RegisterInlineMessage("TTYD64", TTYD64_flo_28_Tattle_NPC);
    TTYD64_flo_28_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_flo_28_String_Tattle);
}
