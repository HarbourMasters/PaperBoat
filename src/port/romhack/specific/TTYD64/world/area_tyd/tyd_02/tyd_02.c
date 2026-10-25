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

API_CALLABLE(flo_16_FlyingNoAttackAI_Main);
API_CALLABLE(kzn_03_MeleeHitbox_Main);

extern EvtScript TTYD64_tyd_02_Script_EnterHorizontalPipe;
extern NpcData TTYD64_tyd_02_NpcGroup_PalePiranha1[];
extern NpcData TTYD64_tyd_02_NpcGroup_PalePiranha2[];
extern EvtScript TTYD64_tyd_02_Script_Foliage_SearchBush;
extern EvtScript TTYD64_tyd_02_Script_EnterVerticalPipe;
extern EvtScript TTYD64_tyd_02_Script_ExitHorizontalPipe;
extern EvtScript TTYD64_tyd_02_Script_ExitVerticalPipe;
extern EvtScript TTYD64_tyd_02_Script_SetupTexturePan;
extern NpcData TTYD64_tyd_02_NpcGroup_DarkPuff[];
extern EvtScript TTYD64_tyd_02_Script_BindFoliage;
extern EvtScript TTYD64_tyd_02_Script_Main;
extern EvtScript TTYD64_tyd_02_Script_NpcAI_80243F10_kzn_03;
extern EvtScript TTYD64_tyd_02_Script_80243E24_kzn_03;
extern EvtScript TTYD64_tyd_02_Script_TexturePan_Update;
extern EvtScript TTYD64_tyd_02_Script_EnterMap;
extern u8 TTYD64_tyd_02_String_Tattle[];
extern EvtScript TTYD64_tyd_02_Script_NpcAI_80244010_kzn_03;
extern EvtScript TTYD64_tyd_02_Script_NpcAI_80244058_flo_16;
extern EvtScript TTYD64_tyd_02_Script_MakeEntities;
extern EvtScript TTYD64_tyd_02_Script_CreateExitTriggers;
extern EvtScript TTYD64_tyd_02_Script_Exit1;
extern EvtScript TTYD64_tyd_02_Script_Exit0;
extern EvtScript TTYD64_tyd_02_Script_Exit2;
extern MapSettings TTYD64_tyd_02_Header;
extern EvtScript TTYD64_tyd_02_Script_Entity_Shine1;
extern EvtScript TTYD64_tyd_02_Script_SetupMusic;
extern NpcGroupList TTYD64_tyd_02_NpcGroupList_tyd02;
extern EntryList TTYD64_tyd_02_EntryList;
extern MobileAISettings TTYD64_tyd_02_AISettings_80244028_flo_16;
extern EvtScript TTYD64_tyd_02_Script_GoToMap_Exit2;
extern EvtScript TTYD64_tyd_02_Script_GoToMap_Exit1;
extern EvtScript TTYD64_tyd_02_Script_GoToMap_Exit0;
extern MobileAISettings TTYD64_tyd_02_AISettings_80243EE0_kzn_03;
extern NpcSettings TTYD64_tyd_02_NpcSettings_802440C8_flo_16;
s32 TTYD64_tyd_02_Function_Init(void);
extern NpcSettings TTYD64_tyd_02_NpcSettings_80244070_mim_01;
extern NpcSettings TTYD64_tyd_02_NpcSettings_802441A8_mim_01;
extern s32 TTYD64_tyd_02_FoliageDrops_bush2[];
extern s32 TTYD64_tyd_02_FoliageDrops_bush6[];
extern Bytecode TTYD64_tyd_02_SearchBushData_bush5[];
extern Bytecode TTYD64_tyd_02_SearchBushData_bush6[];
extern Bytecode TTYD64_tyd_02_SearchBushData_bush3[];
extern Bytecode TTYD64_tyd_02_SearchBushData_bush4[];
extern Bytecode TTYD64_tyd_02_SearchBushData_bush1[];
extern Bytecode TTYD64_tyd_02_SearchBushData_bush2[];
extern s32 TTYD64_tyd_02_FoliageFXPos_bush1[];
extern s32 TTYD64_tyd_02_FoliageFXPos_bush4[];
extern s32 TTYD64_tyd_02_FoliageFXPos_bush5[];
extern s32 TTYD64_tyd_02_FoliageFXPos_bush2[];
extern s32 TTYD64_tyd_02_FoliageFXPos_bush3[];
extern s32 TTYD64_tyd_02_FoliageFXPos_bush6[];
extern s32 TTYD64_tyd_02_BushModels_bush5[];
extern s32 TTYD64_tyd_02_BushModels_bush6[];
extern s32 TTYD64_tyd_02_BushModels_bush3[];
extern s32 TTYD64_tyd_02_BushModels_bush4[];
extern s32 TTYD64_tyd_02_BushModels_bush1[];
extern s32 TTYD64_tyd_02_BushModels_bush2[];

// clang-format off
static s32 TTYD64_tyd_02_GetTattleMsg;

static s32 TTYD64_tyd_02_GetTattle(void) {
    return TTYD64_tyd_02_GetTattleMsg;
}

EvtScript TTYD64_tyd_02_Script_EnterHorizontalPipe = {
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

NpcData TTYD64_tyd_02_NpcGroup_PalePiranha1[] = {
    {
        .id = 1,
        .settings = &TTYD64_tyd_02_NpcSettings_80244070_mim_01,
        .pos = { -159.0f, 1.0f, -41.0f },
        .flags = 0x00000400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 128, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 3, 13106 }, { 9830, 13106, 3, 13106 }, { 16383, 13106, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = -159, .centerPos.y = 1, .centerPos.z = -41, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = -159, .detectPos.y = 1, .detectPos.z = -41, .detectSize.x = 70, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00370101, .walk = 0x00370101, .run = 0x00370101, .chase = 0x00370101, .anim_4 = 0x00370101, .anim_5 = 0x00370101, .death = 0x00370109, .hit = 0x00370109, .anim_8 = 0x00370104, .anim_9 = 0x00370103, .anim_A = 0x00370107, .anim_B = 0x00370107, .anim_C = 0x00370108, .anim_D = 0x00370101, .anim_E = 0x00370101, .anim_F = 0x00370101 },
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
        .settings = &TTYD64_tyd_02_NpcSettings_802441A8_mim_01,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800D00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = -159, .centerPos.y = 1, .centerPos.z = -41, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = -159, .detectPos.y = 1, .detectPos.z = -41, .detectSize.x = 70, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00370101, .walk = 0x00370101, .run = 0x00370101, .chase = 0x00370101, .anim_4 = 0x00370101, .anim_5 = 0x00370101, .death = 0x00370109, .hit = 0x00370109, .anim_8 = 0x00370104, .anim_9 = 0x00370103, .anim_A = 0x00370107, .anim_B = 0x00370107, .anim_C = 0x00370108, .anim_D = 0x00370101, .anim_E = 0x00370101, .anim_F = 0x00370101 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

NpcData TTYD64_tyd_02_NpcGroup_PalePiranha2[] = {
    {
        .id = 3,
        .settings = &TTYD64_tyd_02_NpcSettings_80244070_mim_01,
        .pos = { 156.0f, 1.0f, -13.0f },
        .flags = 0x00000400,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x80, .itemDropChance = 5, .itemDrops = { { 128, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 3, 13106 }, { 9830, 13106, 3, 13106 }, { 16383, 13106, 3, 13106 }, { 26213, 13106, 3, 13106 }, { 32767, 9830, 3, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 156, .centerPos.y = 1, .centerPos.z = -13, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 156, .detectPos.y = 1, .detectPos.z = -13, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00370101, .walk = 0x00370101, .run = 0x00370101, .chase = 0x00370101, .anim_4 = 0x00370101, .anim_5 = 0x00370101, .death = 0x00370109, .hit = 0x00370109, .anim_8 = 0x00370104, .anim_9 = 0x00370103, .anim_A = 0x00370107, .anim_B = 0x00370107, .anim_C = 0x00370108, .anim_D = 0x00370101, .anim_E = 0x00370101, .anim_F = 0x00370101 },
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
        .settings = &TTYD64_tyd_02_NpcSettings_802441A8_mim_01,
        .pos = { 0.0f, -1000.0f, 0.0f },
        .flags = 0x00800D00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 0,
        .drops = { .dropFlags = 0x00, .itemDropChance = 0, .itemDrops = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 0, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = 156, .centerPos.y = 1, .centerPos.z = -13, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = 156, .detectPos.y = 1, .detectPos.z = -13, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x00370101, .walk = 0x00370101, .run = 0x00370101, .chase = 0x00370101, .anim_4 = 0x00370101, .anim_5 = 0x00370101, .death = 0x00370109, .hit = 0x00370109, .anim_8 = 0x00370104, .anim_9 = 0x00370103, .anim_A = 0x00370107, .anim_B = 0x00370107, .anim_C = 0x00370108, .anim_D = 0x00370101, .anim_E = 0x00370101, .anim_F = 0x00370101 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x00,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_tyd_02_Script_Foliage_SearchBush = {
    UseBuf(LVar0)
    BufRead4(LVar1, LVar2, LVar3, LVar4)
    Call(GetPlayerPos, LVar5, LVarF, LVar7)
    Thread
        Set(LFlag0, 0)
        IfNe(LVar1, 0)
            Loop(5)
                UseBuf(LVar1)
                BufRead1(LVar2)
                Loop(LVar2)
                    BufRead1(LVar3)
                    Call(TTYD64_tp_TransformFoliage, LVar3, Float(0.099609375), 1, LVarF, 0)
                    IfEq(LFlag0, 0)
                        Set(LFlag0, 1)
                        Call(PlaySoundAtModel, LVar3, 339, 0)
                    EndIf
                EndLoop
                Wait(1)
                UseBuf(LVar1)
                BufRead1(LVar2)
                Loop(LVar2)
                    BufRead1(LVar3)
                    Call(TTYD64_tp_TransformFoliage, LVar3, Float(0.099609375), -1, LVarF, 0)
                EndLoop
                Wait(1)
            EndLoop
            UseBuf(LVar1)
            BufRead1(LVar2)
            Loop(LVar2)
                BufRead1(LVar3)
                Call(TranslateModel, LVar3, 0, 0, 0)
            EndLoop
            Wait(1)
        EndIf
    EndThread
    Thread
        IfNe(LVar2, 0)
            UseBuf(LVar2)
            BufRead1(LVar3)
            Loop(LVar3)
                BufRead1(LVar4)
                BufRead3(LVar5, LVar6, LVar7)
                BufRead3(LVar8, LVar9, LVarA)
                IfEq(LVarA, 0)
                    Call(DropItemEntity, LVar4, LVar5, LVar6, LVar7, LVar8, LVar9)
                Else
                    Call(GetValueByRef, LVarA, LVarB)
                    IfEq(LVarB, 0)
                        Call(SetValueByRef, LVarA, 1)
                        Call(DropItemEntity, LVar4, LVar5, LVar6, LVar7, LVar8, LVar9)
                    EndIf
                EndIf
            EndLoop
        EndIf
    EndThread
    Wait(15)
    IfNe(LVar4, 0)
        ExecWait(LVar4)
    EndIf
    Return
    End
};

EvtScript TTYD64_tyd_02_Script_EnterVerticalPipe = {
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

EvtScript TTYD64_tyd_02_Script_ExitHorizontalPipe = {
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

EvtScript TTYD64_tyd_02_Script_ExitVerticalPipe = {
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

EvtScript TTYD64_tyd_02_Script_SetupTexturePan = {
    Call(SetTexPanner, 3, 0)
    Call(SetTexPanner, 30, 1)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LVar2, 120)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 0)
        Set(LVar6, 1)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_tyd_02_Script_TexturePan_Update)
    EndThread
    Thread
        Set(LVar0, 1)
        Set(LVar1, 0)
        Set(LVar2, 200)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 0)
        Set(LVar6, 1)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_tyd_02_Script_TexturePan_Update)
    EndThread
    Return
    End
};

NpcData TTYD64_tyd_02_NpcGroup_DarkPuff[] = {
    {
        .id = 0,
        .settings = &TTYD64_tyd_02_NpcSettings_802440C8_flo_16,
        .pos = { -184.0f, 456.0f, 98.0f },
        .flags = 0x00000C00,
        .init = NULL,
        .initVarCount = 0,
        .initVar = { .value = 0 },
        .yaw = 90,
        .drops = { .dropFlags = 0x80, .itemDropChance = 16, .itemDrops = { { 140, 10, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, .heartDrops = { { 6553, 22936, 2, 16383 }, { 9830, 19660, 2, 16383 }, { 16383, 16383, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 9830 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .flowerDrops = { { 6553, 16383, 2, 13106 }, { 9830, 13106, 2, 13106 }, { 16383, 13106, 2, 13106 }, { 26213, 13106, 2, 13106 }, { 32767, 9830, 2, 13106 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, .minCoinBonus = 0, .maxCoinBonus = 2, .unk_DE = { 0, 0 } },
        .territory = { .wander = { .centerPos.x = -184, .centerPos.y = 456, .centerPos.z = 98, .wanderSize.x = 30, .wanderSize.z = 0, .moveSpeedOverride = -32767, .wanderShape = 0, .detectPos.x = -184, .detectPos.y = 456, .detectPos.z = 98, .detectSize.x = 200, .detectSize.z = 0, .detectShape = 0, .isFlying = 0 } },
        .animations = { .idle = 0x007D0201, .walk = 0x007D0203, .run = 0x007D0204, .chase = 0x007D0204, .anim_4 = 0x007D0200, .anim_5 = 0x007D0200, .death = 0x007D0207, .hit = 0x007D0207, .anim_8 = 0x007D0200, .anim_9 = 0x007D0200, .anim_A = 0x007D0200, .anim_B = 0x007D0200, .anim_C = 0x007D0200, .anim_D = 0x007D0200, .anim_E = 0x007D0200, .anim_F = 0x007D0200 },
        .unk__1E0 = 0,
        .unk__1E1 = 0,
        .unk__1E2 = 0,
        .aiDetectFlags = 0x03,
        .aiFlags = 0x00000000,
        .extraAnimations = NULL,
        .tattle = 0,
    },
};

EvtScript TTYD64_tyd_02_Script_BindFoliage = {
    Set(LVar0, (Bytecode) TTYD64_tyd_02_SearchBushData_bush1)
    BindTrigger(TTYD64_tyd_02_Script_Foliage_SearchBush, 256, 15, 1, 0)
    Set(LVar0, (Bytecode) TTYD64_tyd_02_SearchBushData_bush2)
    BindTrigger(TTYD64_tyd_02_Script_Foliage_SearchBush, 256, 16, 1, 0)
    Set(LVar0, (Bytecode) TTYD64_tyd_02_SearchBushData_bush3)
    BindTrigger(TTYD64_tyd_02_Script_Foliage_SearchBush, 256, 17, 1, 0)
    Set(LVar0, (Bytecode) TTYD64_tyd_02_SearchBushData_bush4)
    BindTrigger(TTYD64_tyd_02_Script_Foliage_SearchBush, 256, 18, 1, 0)
    Set(LVar0, (Bytecode) TTYD64_tyd_02_SearchBushData_bush5)
    BindTrigger(TTYD64_tyd_02_Script_Foliage_SearchBush, 256, 19, 1, 0)
    Set(LVar0, (Bytecode) TTYD64_tyd_02_SearchBushData_bush6)
    BindTrigger(TTYD64_tyd_02_Script_Foliage_SearchBush, 256, 20, 1, 0)
    Return
    End
};

EvtScript TTYD64_tyd_02_Script_Main = {
    Set(GameByte(425), 9)
    Call(SetCamPerspective, 0, 3, 25, 16, 4096)
    Call(SetCamBGColor, 0, 0, 0, 0)
    Call(SetCamEnabled, 0, 1)
    Call(SetCamLeadPlayer, 0, 0)
    Call(MakeNpcs, 0, (Bytecode) TTYD64_tyd_02_NpcGroupList_tyd02)
    Exec(TTYD64_tyd_02_Script_SetupMusic)
    Exec(TTYD64_tyd_02_Script_SetupTexturePan)
    Exec(TTYD64_tyd_02_Script_BindFoliage)
    Exec(TTYD64_tyd_02_Script_MakeEntities)
    Exec(TTYD64_tyd_02_Script_EnterMap)
    Return
    End
};

EvtScript TTYD64_tyd_02_Script_NpcAI_80243F10_kzn_03 = {
    Call(SetSelfVar, 7, 1)
    Call(SetSelfVar, 8, 10)
    Call(SetSelfVar, 9, 9)
    Call(SetSelfVar, 10, 12)
    Call(SetSelfVar, 11, 7)
    Call(SetSelfVar, 12, 30)
    Call(SetSelfVar, 13, 15)
    Call(SetSelfVar, 14, 18)
    Call(SetSelfVar, 15, 15)
    Call(TTYD64_tp_kzn_03_PiranhaPlantAI_Main, Ref(TTYD64_tyd_02_AISettings_80243EE0_kzn_03))
    Return
    End
};

EvtScript TTYD64_tyd_02_Script_80243E24_kzn_03 = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
    CaseEq(0)
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

EvtScript TTYD64_tyd_02_Script_TexturePan_Update = {
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

EvtScript TTYD64_tyd_02_Script_EnterMap = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 2)
        Set(LVarA, (Bytecode) TTYD64_tyd_02_Script_CreateExitTriggers)
        Set(LVarB, 11)
        Exec(TTYD64_tyd_02_Script_EnterHorizontalPipe)
    Else
        Set(LVarA, (Bytecode) TTYD64_tyd_02_Script_CreateExitTriggers)
        Exec(TTYD64_tyd_02_Script_EnterVerticalPipe)
    EndIf
    Return
    End
};

u8 TTYD64_tyd_02_String_Tattle[] = {
    0xFC, 0x04, 0xFF, 0x2B, 0x29, 0x54, 0xF7, 0x53, 0x45, 0x45, 0x4D, 0x53,
    0xF7, 0x54, 0x48, 0x41, 0x54, 0xF7, 0x41, 0x4C, 0x4C, 0xF7, 0x54, 0x48,
    0x45, 0xF7, 0x57, 0x41, 0x4C, 0x4C, 0x53, 0xF7, 0x41, 0x52, 0x45, 0xF7,
    0x46, 0x55, 0x4C, 0x4C, 0xF0, 0x4F, 0x46, 0xF7, 0x54, 0x52, 0x45, 0x45,
    0xF7, 0x42, 0x52, 0x41, 0x4E, 0x43, 0x48, 0x45, 0x53, 0x0C, 0xF7, 0x41,
    0x52, 0x45, 0xF7, 0x57, 0x45, 0xF7, 0x49, 0x4E, 0x53, 0x49, 0x44, 0x45,
    0xF7, 0x41, 0xF0, 0x47, 0x49, 0x41, 0x4E, 0x54, 0xF7, 0x54, 0x52, 0x45,
    0x45, 0xF7, 0x4F, 0x52, 0xF7, 0x53, 0x4F, 0x4D, 0x45, 0x54, 0x48, 0x49,
    0x4E, 0x47, 0x1F, 0xF0, 0xF1, 0xFB, 0x34, 0x48, 0x41, 0x54, 0xF7, 0x57,
    0x4F, 0x55, 0x4C, 0x44, 0xF7, 0x42, 0x45, 0xF7, 0x53, 0x4F, 0xF7, 0x41,
    0x57, 0x45, 0x53, 0x4F, 0x4D, 0x45, 0x01, 0xF1, 0xFD
};

EvtScript TTYD64_tyd_02_Script_NpcAI_80244010_kzn_03 = {
    Call(EnableNpcShadow, -1, 0)
    Call(SetSelfVar, 0, 14)
    Call(SetSelfVar, 1, 28)
    Call(SetSelfVar, 4, 3)
    Call(SetSelfVar, 15, 8414)
    Call(kzn_03_MeleeHitbox_Main)
    Return
    End
};

EvtScript TTYD64_tyd_02_Script_NpcAI_80244058_flo_16 = {
    Call(SetSelfVar, 0, 1)
    Call(SetSelfVar, 5, 0)
    Call(SetSelfVar, 6, 0)
    Call(SetSelfVar, 1, 600)
    Call(flo_16_FlyingNoAttackAI_Main, Ref(TTYD64_tyd_02_AISettings_80244028_flo_16))
    Return
    End
};

EvtScript TTYD64_tyd_02_Script_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SuperBlock), -332, 134, 16, 0, 0x80000000)
    Set(MapVar(0), LVar0)
    Call(AssignBlockFlag, GameFlag(4863))
    Call(AssignScript, (Bytecode) TTYD64_tyd_02_Script_Entity_Shine1)
    Return
    End
};

EvtScript TTYD64_tyd_02_Script_CreateExitTriggers = {
    BindTrigger(TTYD64_tyd_02_Script_Exit0, 128, 1, 1, 0)
    BindTrigger(TTYD64_tyd_02_Script_Exit1, 128, 7, 1, 0)
    BindTrigger(TTYD64_tyd_02_Script_Exit2, 64, 11, 1, 0)
    Return
    End
};

EvtScript TTYD64_tyd_02_Script_Exit1 = {
    SetGroup(27)
    Set(LVarA, 1)
    Set(LVarB, 7)
    Set(LVarC, (Bytecode) TTYD64_tyd_02_Script_GoToMap_Exit1)
    ExecWait(TTYD64_tyd_02_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tyd_02_Script_Exit0 = {
    SetGroup(27)
    Set(LVarA, 0)
    Set(LVarB, 1)
    Set(LVarC, (Bytecode) TTYD64_tyd_02_Script_GoToMap_Exit0)
    ExecWait(TTYD64_tyd_02_Script_ExitVerticalPipe)
    Return
    End
};

EvtScript TTYD64_tyd_02_Script_Exit2 = {
    SetGroup(27)
    Set(LVarA, 2)
    Set(LVarB, 11)
    Set(LVarC, (Bytecode) TTYD64_tyd_02_Script_GoToMap_Exit2)
    ExecWait(TTYD64_tyd_02_Script_ExitHorizontalPipe)
    Return
    End
};

MapSettings TTYD64_tyd_02_Header = {
    .main = TTYD64_tyd_02_Script_Main,
    .entryList = &TTYD64_tyd_02_EntryList,
    .entryCount = 3,
    .background = NULL,
    .tattle = { .get = TTYD64_tyd_02_GetTattle },
};

EvtScript TTYD64_tyd_02_Script_Entity_Shine1 = {
    Set(LVar0, MapVar(0))
    SetConst(LVar1, GameFlag(4863))
    ExecWait(TTYD64_Script_ShineBlock)
    Return
    End
};

EvtScript TTYD64_tyd_02_Script_SetupMusic = {
    Call(SetMusic, 0, 168, 0, 8)
    Call(PlayAmbientSounds, 1)
    Return
    End
};

NpcGroupList TTYD64_tyd_02_NpcGroupList_tyd02 = {
    { .npcCount = 1, .npcs = TTYD64_tyd_02_NpcGroup_DarkPuff, .battle = 0x3B04, .stage = 3 },
    { .npcCount = 2, .npcs = TTYD64_tyd_02_NpcGroup_PalePiranha1, .battle = 0x3B05, .stage = 3 },
    { .npcCount = 2, .npcs = TTYD64_tyd_02_NpcGroup_PalePiranha2, .battle = 0x3B05, .stage = 3 },
    {},
};

EntryList TTYD64_tyd_02_EntryList = {
    { 326.0f, 461.0f, -97.0f, 90.0f },
    { -341.0f, 461.0f, -97.0f, 90.0f },
    { -294.0f, -1.0f, -102.0f, 90.0f },
};

MobileAISettings TTYD64_tyd_02_AISettings_80244028_flo_16 = {
    .moveSpeed = 1.0f,
    .moveTime = 45,
    .waitTime = 60,
    .alertRadius = 100.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 3,
    .chaseSpeed = 3.5999999f,
    .chaseTurnRate = 10,
    .chaseUpdateInterval = 1,
    .chaseRadius = 120.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 1,
};

EvtScript TTYD64_tyd_02_Script_GoToMap_Exit2 = {
    Call(GotoMap, (Bytecode) "tyd_02", 1)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_tyd_02_Script_GoToMap_Exit1 = {
    Call(GotoMap, (Bytecode) "tyd_02", 2)
    Wait(100)
    Return
    End
};

EvtScript TTYD64_tyd_02_Script_GoToMap_Exit0 = {
    Call(GotoMap, (Bytecode) "dro_04", 1)
    Wait(100)
    Return
    End
};

MobileAISettings TTYD64_tyd_02_AISettings_80243EE0_kzn_03 = {
    .moveSpeed = 0.0f,
    .moveTime = 30,
    .waitTime = 30,
    .alertRadius = 150.0f,
    .alertOffsetDist = 0.0f,
    .playerSearchInterval = 1,
    .chaseSpeed = 0.0f,
    .chaseTurnRate = 0,
    .chaseUpdateInterval = 0,
    .chaseRadius = 0.0f,
    .chaseOffsetDist = 0.0f,
    .unk_AI_2C = 0,
};

NpcSettings TTYD64_tyd_02_NpcSettings_802440C8_flo_16 = {
    .defaultAnim = 0x00000000,
    .height = 24,
    .radius = 28,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_tyd_02_Script_NpcAI_80244058_flo_16,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 19,
    .actionFlags = 0,
};

s32 TTYD64_tyd_02_Function_Init(void) {
    sprintf(wMapTexName, "tst_tex");
    return false;
}

NpcSettings TTYD64_tyd_02_NpcSettings_80244070_mim_01 = {
    .defaultAnim = 0x00000000,
    .height = 32,
    .radius = 26,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_tyd_02_Script_NpcAI_80243F10_kzn_03,
    .onHit = &EnemyNpcHit,
    .aux = NULL,
    .onDefeat = &EnemyNpcDefeat,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 11,
    .actionFlags = 0,
};

NpcSettings TTYD64_tyd_02_NpcSettings_802441A8_mim_01 = {
    .defaultAnim = 0x00000000,
    .height = 18,
    .radius = 18,
    .otherAI = NULL,
    .onInteract = NULL,
    .ai = TTYD64_tyd_02_Script_NpcAI_80244010_kzn_03,
    .onHit = NULL,
    .aux = NULL,
    .onDefeat = TTYD64_tyd_02_Script_80243E24_kzn_03,
    .flags = 0x00000000,
    .unk_24 = 0,
    .level = 11,
    .actionFlags = 8,
};

s32 TTYD64_tyd_02_FoliageDrops_bush2[] = {
    1, 348, -92, 11, -60, 6, -129995136, 0
};

s32 TTYD64_tyd_02_FoliageDrops_bush6[] = {
    1, 303, 315, 11, 102, 6, -129995135, 0
};

Bytecode TTYD64_tyd_02_SearchBushData_bush5[] = {
    (Bytecode) TTYD64_tyd_02_BushModels_bush5, 0, (Bytecode) TTYD64_tyd_02_FoliageFXPos_bush5, 0
};

Bytecode TTYD64_tyd_02_SearchBushData_bush6[] = {
    (Bytecode) TTYD64_tyd_02_BushModels_bush6, (Bytecode) TTYD64_tyd_02_FoliageDrops_bush6, (Bytecode) TTYD64_tyd_02_FoliageFXPos_bush6, 0
};

Bytecode TTYD64_tyd_02_SearchBushData_bush3[] = {
    (Bytecode) TTYD64_tyd_02_BushModels_bush3, 0, (Bytecode) TTYD64_tyd_02_FoliageFXPos_bush3, 0
};

Bytecode TTYD64_tyd_02_SearchBushData_bush4[] = {
    (Bytecode) TTYD64_tyd_02_BushModels_bush4, 0, (Bytecode) TTYD64_tyd_02_FoliageFXPos_bush4, 0
};

Bytecode TTYD64_tyd_02_SearchBushData_bush1[] = {
    (Bytecode) TTYD64_tyd_02_BushModels_bush1, 0, (Bytecode) TTYD64_tyd_02_FoliageFXPos_bush1, 0
};

Bytecode TTYD64_tyd_02_SearchBushData_bush2[] = {
    (Bytecode) TTYD64_tyd_02_BushModels_bush2, (Bytecode) TTYD64_tyd_02_FoliageDrops_bush2, (Bytecode) TTYD64_tyd_02_FoliageFXPos_bush2, 0
};

s32 TTYD64_tyd_02_FoliageFXPos_bush1[] = {
    1, 315, 11, 102
};

s32 TTYD64_tyd_02_FoliageFXPos_bush4[] = {
    1, 315, 11, 102
};

s32 TTYD64_tyd_02_FoliageFXPos_bush5[] = {
    1, 315, 11, 102
};

s32 TTYD64_tyd_02_FoliageFXPos_bush2[] = {
    1, -92, 11, -60
};

s32 TTYD64_tyd_02_FoliageFXPos_bush3[] = {
    1, 315, 11, 102
};

s32 TTYD64_tyd_02_FoliageFXPos_bush6[] = {
    1, 315, 11, 102
};

s32 TTYD64_tyd_02_BushModels_bush5[] = {
    1, 40
};

s32 TTYD64_tyd_02_BushModels_bush6[] = {
    1, 42
};

s32 TTYD64_tyd_02_BushModels_bush3[] = {
    1, 36
};

s32 TTYD64_tyd_02_BushModels_bush4[] = {
    1, 38
};

s32 TTYD64_tyd_02_BushModels_bush1[] = {
    1, 32
};

s32 TTYD64_tyd_02_BushModels_bush2[] = {
    1, 34
};

MapConfig TTYD64_mapcfg_tyd_02 = {
    .id = "tyd_02",
    .settings = &TTYD64_tyd_02_Header,
    .bgName = NULL,
    .init = TTYD64_tyd_02_Function_Init,
    .songVariation = 0,
    .sfxReverb = 0,
};
// clang-format on

void TTYD64_tp_Install_tyd_02(void) {
    TTYD64_tyd_02_GetTattleMsg = Mod_RegisterInlineMessage("TTYD64", TTYD64_tyd_02_String_Tattle);
    Mod_RegisterWideEvtBuffer(
        "TTYD64", TTYD64_tyd_02_SearchBushData_bush5, ARRAY_COUNT(TTYD64_tyd_02_SearchBushData_bush5)
    );
    Mod_RegisterWideEvtBuffer(
        "TTYD64", TTYD64_tyd_02_SearchBushData_bush6, ARRAY_COUNT(TTYD64_tyd_02_SearchBushData_bush6)
    );
    Mod_RegisterWideEvtBuffer(
        "TTYD64", TTYD64_tyd_02_SearchBushData_bush3, ARRAY_COUNT(TTYD64_tyd_02_SearchBushData_bush3)
    );
    Mod_RegisterWideEvtBuffer(
        "TTYD64", TTYD64_tyd_02_SearchBushData_bush4, ARRAY_COUNT(TTYD64_tyd_02_SearchBushData_bush4)
    );
    Mod_RegisterWideEvtBuffer(
        "TTYD64", TTYD64_tyd_02_SearchBushData_bush1, ARRAY_COUNT(TTYD64_tyd_02_SearchBushData_bush1)
    );
    Mod_RegisterWideEvtBuffer(
        "TTYD64", TTYD64_tyd_02_SearchBushData_bush2, ARRAY_COUNT(TTYD64_tyd_02_SearchBushData_bush2)
    );
}
