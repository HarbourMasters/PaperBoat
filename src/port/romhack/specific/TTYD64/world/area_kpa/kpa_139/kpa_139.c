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

API_CALLABLE(AssignCrateFlag);
API_CALLABLE(BindNpcDefeat);
API_CALLABLE(ClearAmbientSounds);
API_CALLABLE(DoNpcDefeat);
API_CALLABLE(GetBattleOutcome);
API_CALLABLE(GetDist2D);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetNpcVar);
API_CALLABLE(GetPlayerPos);
API_CALLABLE(GetSelfVar);
API_CALLABLE(GotoMap);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeNpcs);
API_CALLABLE(NpcJump0);
API_CALLABLE(OnPlayerFled);
API_CALLABLE(PlaySoundAtNpc);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveNpc);
API_CALLABLE(SelfEnemyOverrideSyncPos);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetCamEnabled);
API_CALLABLE(SetCamLeadPlayer);
API_CALLABLE(SetCamPerspective);
API_CALLABLE(SetEnemyFlagBits);
API_CALLABLE(SetMusic);
API_CALLABLE(SetNpcAnimation);
API_CALLABLE(SetNpcJumpscale);
API_CALLABLE(SetNpcPos);
API_CALLABLE(SetNpcRotation);
API_CALLABLE(SetNpcSpeed);
API_CALLABLE(SetNpcVar);
API_CALLABLE(SetSelfVar);
API_CALLABLE(SetTexPanner);
API_CALLABLE(UseExitHeading);
API_CALLABLE(kpa_130_BillBlasterAI_Main);
API_CALLABLE(kpa_130_BulletBillAI_Main);

extern EvtScript TTYD64_kpa_139_Script_NpcAI_Canon2;
extern NpcData TTYD64_kpa_139_NpcGroup_Koopatrol1[];
extern NpcData TTYD64_kpa_139_NpcGroup_Koopatrol2[];
extern EvtScript TTYD64_kpa_139_Script_NpcAI_Ball;
extern EvtScript TTYD64_kpa_139_Script_SetupTexturePan;
extern NpcData TTYD64_kpa_139_NpcGroup_BulletBill4[];
extern NpcData TTYD64_kpa_139_NpcGroup_BulletBill3[];
extern NpcData TTYD64_kpa_139_NpcGroup_BulletBill2[];
extern NpcData TTYD64_kpa_139_NpcGroup_BulletBill1[];
extern NpcData TTYD64_kpa_139_NpcGroup_CanonBall2[];
extern NpcData TTYD64_kpa_139_NpcGroup_CanonBall1[];
extern NpcData TTYD64_kpa_139_NpcGroup_CanonBall3[];
extern EvtScript TTYD64_kpa_139_Script_80240E84;
extern EvtScript TTYD64_kpa_139_Script_Main;
extern EvtScript TTYD64_kpa_139_Script_TexturePan_Update;
extern EvtScript TTYD64_kpa_139_Script_80240CF8;
extern EvtScript TTYD64_kpa_139_Script_MakeEntities;
extern u8 TTYD64_kpa_139_String_Tattle[];
extern NpcGroupList TTYD64_kpa_139_NpcGroupList_kpa139;
extern EvtScript TTYD64_kpa_139_Script_NpcAI_80240C98;
extern EvtScript TTYD64_kpa_139_Script_Exit0;
extern MapSettings TTYD64_kpa_139_Header;
extern EvtScript TTYD64_kpa_139_Script_SetupMusic;
extern MobileAISettings TTYD64_kpa_139_AISettings_80240C68;
extern NpcSettings TTYD64_kpa_139_NpcSettings_Generic;
extern NpcSettings TTYD64_kpa_139_NpcSettings_80240FA8;
extern NpcSettings TTYD64_kpa_139_NpcSettings_80240FD4;
extern NpcSettings TTYD64_kpa_139_NpcSettings_CanonBall;
extern NpcSettings TTYD64_kpa_139_NpcSettings_BillBlaster2;
extern EvtScript TTYD64_kpa_139_Script_CreateExitTriggers;
extern GuardAISettings TTYD64_kpa_139_AISettings_80240C24;
extern EvtScript TTYD64_kpa_139_Script_Init_BillBlaster2;
extern EvtScript TTYD64_kpa_139_Script_Init_80241024;
extern EvtScript TTYD64_kpa_139_Script_Init_NPC_Koopa1;
extern EvtScript TTYD64_kpa_139_Script_Init_80241000;
extern EvtScript TTYD64_kpa_139_Script_NpcAI_80240C48;
extern EvtScript TTYD64_kpa_139_Script_EnterMap;
extern EvtScript TTYD64_kpa_139_Script_DoNpcDefeat;
extern EntryList TTYD64_kpa_139_EntryList;

// clang-format off
static s32 TTYD64_kpa_139_GetTattleMsg;

static s32 TTYD64_kpa_139_GetTattle(void) {
    return TTYD64_kpa_139_GetTattleMsg;
}

EvtScript TTYD64_kpa_139_Script_NpcAI_Canon2 = {
    Loop(0)
        Call(GetPlayerPos, LVar0, 0, 0)
        IfGt(LVar0, -340)
            Call(TTYD64_ReadField, TTYD64_F_GCOLLISIONSTATUS_2_2U, LVar0)
            IfEq(LVar0, 1)
                Call(GetNpcVar, 54, 0, LVar0)
                IfNe(LVar0, 1)
                    Call(SetNpcAnimation, -1, 0x2E0409)
                    Wait(20)
                    Call(SetNpcAnimation, -1, 0x2E0408)
                    Call(PlaySoundAtNpc, -1, 808, 0)
                    Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
                    Add(LVar0, 27)
                    Add(LVar1, 35)
                    Call(SetNpcPos, 54, LVar0, LVar1, LVar2)
                    Call(SetNpcVar, 54, 0, 1)
                    Wait(10)
                EndIf
            EndIf
        EndIf
        Call(GetPlayerPos, LVar0, 0, 0)
        IfGt(LVar0, -340)
            Call(TTYD64_ReadField, TTYD64_F_GCOLLISIONSTATUS_2_2U, LVar0)
            IfEq(LVar0, 1)
                Call(GetNpcVar, 55, 0, LVar0)
                IfNe(LVar0, 1)
                    Call(SetNpcAnimation, -1, 0x2E0409)
                    Wait(20)
                    Call(SetNpcAnimation, -1, 0x2E0408)
                    Call(PlaySoundAtNpc, -1, 808, 0)
                    Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
                    Add(LVar0, 27)
                    Add(LVar1, 35)
                    Call(SetNpcPos, 55, LVar0, LVar1, LVar2)
                    Call(SetNpcVar, 55, 0, 1)
                    Wait(10)
                EndIf
            EndIf
        EndIf
        Call(GetPlayerPos, LVar0, 0, 0)
        IfGt(LVar0, -340)
            Call(TTYD64_ReadField, TTYD64_F_GCOLLISIONSTATUS_2_2U, LVar0)
            IfEq(LVar0, 1)
                Call(GetNpcVar, 56, 0, LVar0)
                IfNe(LVar0, 1)
                    Call(SetNpcAnimation, -1, 0x2E0409)
                    Wait(20)
                    Call(SetNpcAnimation, -1, 0x2E0408)
                    Call(PlaySoundAtNpc, -1, 808, 0)
                    Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
                    Add(LVar0, 27)
                    Add(LVar1, 35)
                    Call(SetNpcPos, 56, LVar0, LVar1, LVar2)
                    Call(SetNpcVar, 56, 0, 1)
                    Wait(10)
                EndIf
            EndIf
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

NpcData TTYD64_kpa_139_NpcGroup_Koopatrol1[] = {
    {
        .id = 2,
        .settings = &TTYD64_kpa_139_NpcSettings_Generic,
        .pos = { -456.0f, -1.0f, 8.0f },
        .flags = 0x00000C00,
        .init = &TTYD64_kpa_139_Script_Init_NPC_Koopa1,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00590001, .walk = 0x00590003, .run = 0x00590004, .chase = 0x00590004, .anim_4 = 0x00590000, .anim_5 = 0x00590000, .death = 0x0059000B, .hit = 0x0059000B, .anim_8 = 0x00590000, .anim_9 = 0x00590000, .anim_A = 0x00590000, .anim_B = 0x00590000, .anim_C = 0x00590000, .anim_D = 0x00590000, .anim_E = 0x00590000, .anim_F = 0x00590000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
    {
        .id = 0,
        .settings = &TTYD64_kpa_139_NpcSettings_80240FA8,
        .pos = { -423.0f, -1.0f, 8.0f },
        .flags = 0x00002D01,
        .init = &TTYD64_kpa_139_Script_Init_80241024,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002E0400, .walk = 0x002E0400, .run = 0x002E0400, .chase = 0x002E0400, .anim_4 = 0x002E0400, .anim_5 = 0x002E0400, .death = 0x002E0403, .hit = 0x002E0403, .anim_8 = 0x002E0402, .anim_9 = 0x002E0400, .anim_A = 0x002E0400, .anim_B = 0x002E0400, .anim_C = 0x002E0400, .anim_D = 0x002E0400, .anim_E = 0x002E0400, .anim_F = 0x002E0400 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_kpa_139_NpcGroup_Koopatrol2[] = {
    {
        .id = 3,
        .settings = &TTYD64_kpa_139_NpcSettings_Generic,
        .pos = { -536.0f, 179.0f, -88.0f },
        .flags = 0x00000C00,
        .init = &TTYD64_kpa_139_Script_Init_NPC_Koopa1,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00590001, .walk = 0x00590003, .run = 0x00590004, .chase = 0x00590004, .anim_4 = 0x00590000, .anim_5 = 0x00590000, .death = 0x0059000B, .hit = 0x0059000B, .anim_8 = 0x00590000, .anim_9 = 0x00590000, .anim_A = 0x00590000, .anim_B = 0x00590000, .anim_C = 0x00590000, .anim_D = 0x00590000, .anim_E = 0x00590000, .anim_F = 0x00590000 },
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
        .settings = &TTYD64_kpa_139_NpcSettings_BillBlaster2,
        .pos = { -503.0f, 179.0f, -88.0f },
        .flags = 0x00002D01,
        .init = &TTYD64_kpa_139_Script_Init_BillBlaster2,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x002E0400, .walk = 0x002E0400, .run = 0x002E0400, .chase = 0x002E0400, .anim_4 = 0x002E0400, .anim_5 = 0x002E0400, .death = 0x002E0403, .hit = 0x002E0403, .anim_8 = 0x002E0402, .anim_9 = 0x002E0400, .anim_A = 0x002E0400, .anim_B = 0x002E0400, .anim_C = 0x002E0400, .anim_D = 0x002E0400, .anim_E = 0x002E0400, .anim_F = 0x002E0400 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_kpa_139_Script_NpcAI_Ball = {
    Call(SelfEnemyOverrideSyncPos, 1)
    Call(SetNpcSpeed, -1, Float(8.0))
    Call(SetNpcJumpscale, -1, Float(0.1015625))
    Loop(0)
        Call(GetSelfVar, 0, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_ReadField, TTYD64_F_GPLAYERSTATUS_54_4U, LVar3)
            Call(TTYD64_Function_ConvertToInt, LVar3, LVar3)
            IfLe(LVar3, 0)
                Call(GetPlayerPos, LVar0, LVar1, LVar2)
                Call(NpcJump0, -1, LVar0, -1, LVar2, 0)
            Else
                Call(GetPlayerPos, LVar0, LVar1, LVar2)
                Call(GetPlayerPos, LVarA, LVarB, 0)
                Call(GetNpcPos, -1, LVarC, LVarD, 0)
                Call(GetDist2D, LVarE, LVarA, LVarB, LVarC, LVarD)
                Div(LVarE, 10)
                Call(GetPlayerPos, LVar5, 0, 0)
                IfGt(LVar5, -270)
                    Mul(LVar3, LVarE)
                EndIf
                Call(TTYD64_ReadField, TTYD64_F_GPLAYERSTATUS_A8_4F, LVar5)
                IfLe(LVar5, Float(80.0))
                    Sub(LVar0, LVar3)
                Else
                    Add(LVar0, LVar3)
                EndIf
                IfGt(LVar0, 525)
                    Set(LVar0, 525)
                EndIf
                Call(NpcJump0, -1, LVar0, -1, LVar2, 0)
            EndIf
            Call(PlaySoundAtNpc, -1, 233, 0)
            Call(SetNpcSpeed, -1, Float(1.0))
            Call(SetNpcJumpscale, -1, Float(1.0))
            Call(GetNpcPos, -1, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Call(RandInt, 20, LVar4)
            Add(LVar0, LVar4)
            IfGt(LVar2, 5)
                Set(LVar2, 70)
            Else
                Set(LVar2, -70)
            EndIf
            Call(NpcJump0, -1, LVar0, -180, LVar2, 30)
            Call(SetNpcPos, -1, 0, -1000, 0)
            Wait(5)
            Call(SetNpcSpeed, -1, Float(8.0))
            Call(SetNpcJumpscale, -1, Float(0.1015625))
            Call(SetSelfVar, 0, 0)
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript TTYD64_kpa_139_Script_SetupTexturePan = {
    Call(SetTexPanner, 10, 3)
    Call(SetTexPanner, 11, 4)
    Thread
        Set(LVar0, 3)
        Set(LVar1, -120)
        Set(LVar2, 0)
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
        Exec(TTYD64_kpa_139_Script_TexturePan_Update)
    EndThread
    Thread
        Set(LVar0, 4)
        Set(LVar1, -70)
        Set(LVar2, 0)
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
        Exec(TTYD64_kpa_139_Script_TexturePan_Update)
    EndThread
    Return
    End
};

NpcData TTYD64_kpa_139_NpcGroup_BulletBill4[] = {
    {
        .id = 53,
        .settings = &TTYD64_kpa_139_NpcSettings_80240FD4,
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

NpcData TTYD64_kpa_139_NpcGroup_BulletBill3[] = {
    {
        .id = 52,
        .settings = &TTYD64_kpa_139_NpcSettings_80240FD4,
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

NpcData TTYD64_kpa_139_NpcGroup_BulletBill2[] = {
    {
        .id = 51,
        .settings = &TTYD64_kpa_139_NpcSettings_80240FD4,
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

NpcData TTYD64_kpa_139_NpcGroup_BulletBill1[] = {
    {
        .id = 50,
        .settings = &TTYD64_kpa_139_NpcSettings_80240FD4,
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

NpcData TTYD64_kpa_139_NpcGroup_CanonBall2[] = {
    {
        .id = 55,
        .settings = &TTYD64_kpa_139_NpcSettings_CanonBall,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00280D04,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00590006, .walk = 0x00590006, .run = 0x00590006, .chase = 0x00590006, .anim_4 = 0x00590000, .anim_5 = 0x00590000, .death = 0x0059000B, .hit = 0x0059000B, .anim_8 = 0x00590000, .anim_9 = 0x00590000, .anim_A = 0x00590000, .anim_B = 0x00590000, .anim_C = 0x00590000, .anim_D = 0x00590000, .anim_E = 0x00590000, .anim_F = 0x00590000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_kpa_139_NpcGroup_CanonBall1[] = {
    {
        .id = 54,
        .settings = &TTYD64_kpa_139_NpcSettings_CanonBall,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00280D04,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00590006, .walk = 0x00590006, .run = 0x00590006, .chase = 0x00590006, .anim_4 = 0x00590000, .anim_5 = 0x00590000, .death = 0x0059000B, .hit = 0x0059000B, .anim_8 = 0x00590000, .anim_9 = 0x00590000, .anim_A = 0x00590000, .anim_B = 0x00590000, .anim_C = 0x00590000, .anim_D = 0x00590000, .anim_E = 0x00590000, .anim_F = 0x00590000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_kpa_139_NpcGroup_CanonBall3[] = {
    {
        .id = 56,
        .settings = &TTYD64_kpa_139_NpcSettings_CanonBall,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00280D04,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 0, .centerPos.y = 0, .centerPos.z = 0, .wanderSize.x = 0, .wanderSize.z = 0, .moveSpeedOverride = 0, .wanderShape = 0, .detectPos.x = 0, .detectPos.y = 0, .detectPos.z = 0, .detectSize.x = 0, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00590006, .walk = 0x00590006, .run = 0x00590006, .chase = 0x00590006, .anim_4 = 0x00590000, .anim_5 = 0x00590000, .death = 0x0059000B, .hit = 0x0059000B, .anim_8 = 0x00590000, .anim_9 = 0x00590000, .anim_A = 0x00590000, .anim_B = 0x00590000, .anim_C = 0x00590000, .anim_D = 0x00590000, .anim_E = 0x00590000, .anim_F = 0x00590000 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_kpa_139_Script_80240E84 = {
    Call(SetNpcRotation, -1, 0, 0, 0)
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
    CaseEq(0)
        Call(SetSelfVar, 0, 100)
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

EvtScript TTYD64_kpa_139_Script_Main = {
    Set(GameByte(425), 22)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeNpcs, 1, (Bytecode) TTYD64_kpa_139_NpcGroupList_kpa139)
    Exec(TTYD64_kpa_139_Script_MakeEntities)
    Exec(TTYD64_kpa_139_Script_SetupMusic)
    Exec(TTYD64_kpa_139_Script_SetupTexturePan)
    Exec(TTYD64_kpa_139_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_kpa_139_Script_TexturePan_Update = {
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

EvtScript TTYD64_kpa_139_Script_80240CF8 = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
    CaseEq(0)
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

EvtScript TTYD64_kpa_139_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_WoodenCrate), -696, 179, -140, -15, -1, 0x80000000)
    Call(MakeEntity, Ref(Entity_WoodenCrate), -651, 179, -155, 15, -1, 0x80000000)
    Call(MakeEntity, Ref(Entity_WoodenCrate), -685, 179, -190, 0, 381, 0x80000000)
    Call(AssignCrateFlag, GameFlag(5700))
    Return
    End
};

u8 TTYD64_kpa_139_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x24, 0x4F, 0x45, 0x53, 0xF7, 0x54, 0x48, 0x49,
    0x53, 0xF7, 0x43, 0x41, 0x53, 0x54, 0x4C, 0x45, 0xF7, 0x48, 0x41, 0x56,
    0x45, 0xF7, 0x4E, 0x4F, 0xF7, 0x45, 0x4E, 0x44, 0x1F, 0xF0, 0x37, 0x4F,
    0x57, 0x0C, 0xF7, 0x48, 0x4F, 0x57, 0xF7, 0x44, 0x49, 0x44, 0xF7, 0x54,
    0x48, 0x45, 0x59, 0xF7, 0x4D, 0x41, 0x4E, 0x41, 0x47, 0x45, 0xF7, 0x54,
    0x4F, 0xF7, 0x42, 0x55, 0x49, 0x4C, 0x44, 0xF7, 0x41, 0x4C, 0x4C, 0xF0,
    0x4F, 0x46, 0xF7, 0x54, 0x48, 0x49, 0x53, 0xF7, 0x55, 0x4E, 0x44, 0x45,
    0x52, 0xF7, 0x30, 0x45, 0x41, 0x43, 0x48, 0x07, 0x53, 0xF7, 0x43, 0x41,
    0x53, 0x54, 0x4C, 0x45, 0xF7, 0x57, 0x49, 0x54, 0x48, 0x4F, 0x55, 0x54,
    0xF0, 0x41, 0x4E, 0x59, 0x4F, 0x4E, 0x45, 0xF7, 0x4E, 0x4F, 0x54, 0x49,
    0x43, 0x49, 0x4E, 0x47, 0x1F, 0xF1, 0xFD
};

NpcGroupList TTYD64_kpa_139_NpcGroupList_kpa139 = {
    { .npcCount = 2, .npcs = TTYD64_kpa_139_NpcGroup_Koopatrol1, .battle = 0x2223, .stage = 9 },
    { .npcCount = 2, .npcs = TTYD64_kpa_139_NpcGroup_Koopatrol2, .battle = 0x2221, .stage = 9 },
    { .npcCount = 1, .npcs = TTYD64_kpa_139_NpcGroup_CanonBall1, .battle = 0x2217, .stage = 9 },
    { .npcCount = 1, .npcs = TTYD64_kpa_139_NpcGroup_CanonBall2, .battle = 0x2217, .stage = 9 },
    { .npcCount = 1, .npcs = TTYD64_kpa_139_NpcGroup_CanonBall3, .battle = 0x2217, .stage = 9 },
    { .npcCount = 1, .npcs = TTYD64_kpa_139_NpcGroup_BulletBill1, .battle = 0x2501, .stage = 9 },
    { .npcCount = 1, .npcs = TTYD64_kpa_139_NpcGroup_BulletBill2, .battle = 0x2501, .stage = 9 },
    { .npcCount = 1, .npcs = TTYD64_kpa_139_NpcGroup_BulletBill3, .battle = 0x2501, .stage = 9 },
    { .npcCount = 1, .npcs = TTYD64_kpa_139_NpcGroup_BulletBill4, .battle = 0x2501, .stage = 9 },
    {},
};

EvtScript TTYD64_kpa_139_Script_NpcAI_80240C98 = {
    Call(SelfEnemyOverrideSyncPos, 1)
    Call(SetSelfVar, 0, 0)
    Call(SetNpcPos, -1, 0, -1000, 0)
    Call(kpa_130_BulletBillAI_Main, Ref(TTYD64_kpa_139_AISettings_80240C68))
    Return
    End
};

EvtScript TTYD64_kpa_139_Script_Exit0 = {
    Call(UseExitHeading, 60, 0)
    Exec(ExitWalk)
    Call(GotoMap, (Bytecode) "kpa_61", 2)
    Wait(100)
    Return
    End
};

MapSettings TTYD64_kpa_139_Header = {
    .main = &TTYD64_kpa_139_Script_Main,
    .entryList = &TTYD64_kpa_139_EntryList,
    .entryCount = 1,
    .background = &gBackgroundImage,
    .tattle = { .get = TTYD64_kpa_139_GetTattle },
};

EvtScript TTYD64_kpa_139_Script_SetupMusic = {
    Call(SetMusic, 0, 100, 0, 8)
    Call(ClearAmbientSounds, 250)
    Return
    End
};

MobileAISettings TTYD64_kpa_139_AISettings_80240C68 = {
    .moveSpeed = 0.0f,
    .moveTime = 0,
    .waitTime = 0,
    .alertRadius = 0.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 0,
    .chaseSpeed = 7.30000019f,
    .chaseTurnRate = 0,
    .chaseUpdateInterval = 0,
    .chaseRadius = 0.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

NpcSettings TTYD64_kpa_139_NpcSettings_Generic = {
    .defaultAnim = 0x00000000,
    .height = 40,
    .radius = 24,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = NULL,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 25,
    .actionFlags = 0,
};

NpcSettings TTYD64_kpa_139_NpcSettings_80240FA8 = {
    .defaultAnim = 0x00000000,
    .height = 26,
    .radius = 32,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = &TTYD64_kpa_139_Script_NpcAI_80240C48,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = &TTYD64_kpa_139_Script_80240CF8,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 27,
    .actionFlags = 0,
};

NpcSettings TTYD64_kpa_139_NpcSettings_80240FD4 = {
    .defaultAnim = 0x00000000,
    .height = 14,
    .radius = 31,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = &TTYD64_kpa_139_Script_NpcAI_80240C98,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &TTYD64_kpa_139_Script_80240E84,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 24,
    .actionFlags = 0,
};

NpcSettings TTYD64_kpa_139_NpcSettings_CanonBall = {
    .defaultAnim = 0x00000000,
    .height = 20,
    .radius = 23,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = &TTYD64_kpa_139_Script_NpcAI_Ball,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 12,
    .actionFlags = 0,
};

NpcSettings TTYD64_kpa_139_NpcSettings_BillBlaster2 = {
    .defaultAnim = 0x00000000,
    .height = 26,
    .radius = 32,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = &TTYD64_kpa_139_Script_NpcAI_Canon2,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = NULL,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 27,
    .actionFlags = 0,
};

EvtScript TTYD64_kpa_139_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_kpa_139_Script_Exit0, 0x80000, 12, 1, 0)
    Return
    End
};

GuardAISettings TTYD64_kpa_139_AISettings_80240C24 = {
    .alertRadius = 0.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 10,
    .chaseSpeed = 0.0f,
    .chaseTurnRate = 0,
    .chaseUpdateInterval = 0,
    .chaseRadius = 0.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_20 = 0,
};

EvtScript TTYD64_kpa_139_Script_Init_BillBlaster2 = {
    Call(BindNpcDefeat, -1, (Bytecode) TTYD64_kpa_139_Script_DoNpcDefeat)
    Return
    End
};

EvtScript TTYD64_kpa_139_Script_Init_80241024 = {
    Call(SetSelfVar, 1, 400)
    Return
    End
};

EvtScript TTYD64_kpa_139_Script_Init_NPC_Koopa1 = {
    Call(BindNpcDefeat, -1, (Bytecode) TTYD64_kpa_139_Script_DoNpcDefeat)
    Return
    End
};

EvtScript TTYD64_kpa_139_Script_Init_80241000 = {
    Call(SetSelfVar, 1, -995)
    Return
    End
};

EvtScript TTYD64_kpa_139_Script_NpcAI_80240C48 = {
    Call(kpa_130_BillBlasterAI_Main, Ref(TTYD64_kpa_139_AISettings_80240C24))
    Return
    End
};

EvtScript TTYD64_kpa_139_Script_EnterMap = {
    Exec(TTYD64_kpa_139_Script_CreateExitTriggers)
    Return
    End
};

EvtScript TTYD64_kpa_139_Script_DoNpcDefeat = {
    Call(DoNpcDefeat)
    Return
    End
};

EntryList TTYD64_kpa_139_EntryList = {
    { 495.0f, 0.0f, -15.0f, -90.0f },
};

MapConfig TTYD64_mapcfg_kpa_139 = {
    .id = "kpa_139",
    .settings = &TTYD64_kpa_139_Header,
    .bgName = "kpa_bg",
    .init = NULL,
    .songVariation = 1,
    .sfxReverb = 3,
};
// clang-format on

void TTYD64_nm_Install_kpa_139(void) {
    TTYD64_kpa_139_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_kpa_139_String_Tattle);
}
