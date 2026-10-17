#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_drop_tables.h"
#include "../include/ttyd64_rawmem.h"
#include "../include/ttyd64_symbols.h"
#include "battles_b.h"
#include "battles_b_imports.h"

extern ActorBlueprint b_area_omo2_3_shy_stack;
extern ActorPartBlueprint b_area_omo2_3_shy_stack_ActorParts[];
extern EvtScript b_area_omo2_3_shy_stack_EVS_HandleEvent;
extern EvtScript b_area_omo2_3_shy_stack_EVS_Idle;
extern EvtScript b_area_omo2_3_shy_stack_EVS_ShootRock;
extern s32 b_area_omo2_3_shy_stack_StatusTable[];
extern ActorBlueprint TTYD64_omo2_3_ShyStack;
extern EvtScript TTYD64_omo2_3_Script_Init_8023149C;
extern EvtScript TTYD64_omo2_3_Script_TakeTurn_802357B4;

ActorBlueprint TTYD64_omo2_3_ShyStack = {
    .flags = 0x0,
    .maxHP = 10,
    .type = 0xA7,
    .level = 0,
    .partCount = 14,
    .partsData = b_area_omo2_3_shy_stack_ActorParts,
    .initScript = &TTYD64_omo2_3_Script_Init_8023149C,
    .statusTable = b_area_omo2_3_shy_stack_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 30, 75 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 75 },
    .statusTextOffset = { 10, 65 },
};

// clang-format off
EvtScript TTYD64_omo2_3_Script_Init_8023149C = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo2_3_Script_TakeTurn_802357B4))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo2_3_shy_stack_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo2_3_shy_stack_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 1, 0x720000)
    Call(SetActorVar, ACTOR_SELF, 2, 0x720004)
    Call(SetActorVar, ACTOR_SELF, 3, 0x720008)
    Call(SetActorVar, ACTOR_SELF, 4, 0x720010)
    Call(SetActorVar, ACTOR_SELF, 5, 0x720014)
    Call(SetActorVar, ACTOR_SELF, 6, 0x72001B)
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Set(LVar0, 10)
        Call(SetPartPos, ACTOR_SELF, 14, LVar0, 200, 0)
        Call(SetPartPos, ACTOR_SELF, 13, LVar0, 200, 0)
        Call(SetPartPos, ACTOR_SELF, 12, LVar0, 200, 0)
        Call(SetPartPos, ACTOR_SELF, 11, LVar0, 200, 0)
        Thread
            Wait(5)
            Call(PlaySoundAtPart, ACTOR_SELF, 14, 769)
        EndThread
        Thread
            Call(SetAnimation, ACTOR_SELF, 14, 0x3B000A)
            Call(SetPartFlagBits, ACTOR_SELF, 14, 1, 0)
            Call(SetPartJumpGravity, ACTOR_SELF, 14, Float(1.0))
            Call(SetPartSounds, ACTOR_SELF, 14, 2, 0, 0)
            Call(FallPartTo, ACTOR_SELF, 14, LVar0, 0, 0, 36)
            Call(PlaySoundAtPart, ACTOR_SELF, 14, 8292)
            Call(SetAnimation, ACTOR_SELF, 14, 0x3B0007)
        EndThread
        Thread
            Wait(36)
            Call(PlaySoundAtPart, ACTOR_SELF, 13, 769)
        EndThread
        Thread
            Wait(31)
            Call(SetAnimation, ACTOR_SELF, 13, 0x3B000A)
            Call(SetPartFlagBits, ACTOR_SELF, 13, 1, 0)
            Call(SetPartJumpGravity, ACTOR_SELF, 13, Float(1.0))
            Call(SetPartSounds, ACTOR_SELF, 13, 2, 0, 0)
            Call(FallPartTo, ACTOR_SELF, 13, LVar0, 18, 0, 32)
            Call(PlaySoundAtPart, ACTOR_SELF, 13, 8292)
            Call(SetAnimation, ACTOR_SELF, 13, 0x3B0007)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -3, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.2001953125), Float(0.80078125), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -5, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -3, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.0), Float(1.0), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, 0, 0)
        EndThread
        Thread
            Wait(67)
            Call(PlaySoundAtPart, ACTOR_SELF, 12, 769)
        EndThread
        Thread
            Wait(62)
            Call(SetAnimation, ACTOR_SELF, 12, 0x3B000A)
            Call(SetPartFlagBits, ACTOR_SELF, 12, 1, 0)
            Call(SetPartJumpGravity, ACTOR_SELF, 12, Float(1.0))
            Call(SetPartSounds, ACTOR_SELF, 12, 2, 0, 0)
            Call(FallPartTo, ACTOR_SELF, 12, LVar0, 36, 0, 28)
            Call(PlaySoundAtPart, ACTOR_SELF, 12, 8292)
            Call(SetAnimation, ACTOR_SELF, 12, 0x3B0007)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -2, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, -4, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.2001953125), Float(0.80078125), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.2001953125), Float(0.80078125), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -3, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, -6, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -2, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, -4, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.0), Float(1.0), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.0), Float(1.0), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, 0, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, 0, 0)
        EndThread
        Thread
            Wait(98)
            Call(PlaySoundAtPart, ACTOR_SELF, 11, 769)
        EndThread
        Thread
            Wait(93)
            Call(SetAnimation, ACTOR_SELF, 11, 0x3B000A)
            Call(SetPartFlagBits, ACTOR_SELF, 11, 1, 0)
            Call(SetPartJumpGravity, ACTOR_SELF, 11, Float(1.0))
            Call(SetPartSounds, ACTOR_SELF, 11, 2, 0, 0)
            Call(FallPartTo, ACTOR_SELF, 11, LVar0, 54, 0, 24)
            Call(PlaySoundAtPart, ACTOR_SELF, 11, 8292)
            Call(SetAnimation, ACTOR_SELF, 11, 0x3B0007)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 12, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -1, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, -2, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 11, 0, -3, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.2001953125), Float(0.80078125), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.2001953125), Float(0.80078125), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 12, Float(1.2001953125), Float(0.80078125), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -2, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, -3, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 11, 0, -5, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 12, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -1, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, -2, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 11, 0, -3, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.0), Float(1.0), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.0), Float(1.0), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 12, Float(1.0), Float(1.0), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, 0, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, 0, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 11, 0, 0, 0)
            Wait(7)
            Call(GetPartOffset, ACTOR_SELF, 14, LVar0, LVar1, LVar2)
            Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetPartFlagBits, ACTOR_SELF, 11, 1, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 12, 1, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 13, 1, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 14, 1, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 1, 1, 0)
            Call(HPBarToHome, ACTOR_SELF)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
        EndThread
    Else
        Call(SetPartPos, ACTOR_SELF, 14, 200, 0, 47)
        Call(SetPartPos, ACTOR_SELF, 13, 200, 0, 47)
        Call(SetPartPos, ACTOR_SELF, 12, 200, 0, 47)
        Call(SetPartPos, ACTOR_SELF, 11, 200, 0, 47)
        Thread
            Call(SetAnimation, ACTOR_SELF, 14, 0x3B0004)
            Call(SetPartFlagBits, ACTOR_SELF, 14, 1, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, 14, Float(4.0))
            Call(RunPartTo, ACTOR_SELF, 14, 55, 0, 47, 0)
            Call(RunPartTo, ACTOR_SELF, 14, 50, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 14, 0x3B0007)
        EndThread
        Thread
            Wait(31)
            Call(SetAnimation, ACTOR_SELF, 13, 0x3B0004)
            Call(SetPartFlagBits, ACTOR_SELF, 13, 1, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, 13, Float(4.0))
            Call(RunPartTo, ACTOR_SELF, 13, 55, 0, 47, 36)
            Call(SetAnimation, ACTOR_SELF, 13, 0x3B0009)
            Call(SetPartJumpGravity, ACTOR_SELF, 13, Float(1.0))
            Call(JumpPartTo, ACTOR_SELF, 13, 50, 18, 0, 20, 1)
            Call(PlaySoundAtPart, ACTOR_SELF, 13, 8292)
            Call(SetAnimation, ACTOR_SELF, 13, 0x3B0007)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -3, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.2001953125), Float(0.80078125), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -5, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -3, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.0), Float(1.0), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, 0, 0)
        EndThread
        Thread
            Wait(77)
            Call(SetAnimation, ACTOR_SELF, 13, 0x3B000A)
        EndThread
        Thread
            Wait(62)
            Call(SetAnimation, ACTOR_SELF, 12, 0x3B0004)
            Call(SetPartFlagBits, ACTOR_SELF, 12, 1, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, 12, Float(4.0))
            Call(RunPartTo, ACTOR_SELF, 12, 55, 0, 47, 36)
            Call(SetAnimation, ACTOR_SELF, 12, 0x3B0009)
            Call(SetPartJumpGravity, ACTOR_SELF, 12, Float(1.0))
            Call(JumpPartTo, ACTOR_SELF, 12, 50, 36, 0, 20, 1)
            Call(PlaySoundAtPart, ACTOR_SELF, 12, 8292)
            Call(SetAnimation, ACTOR_SELF, 12, 0x3B0007)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -2, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, -3, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.2001953125), Float(0.80078125), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.2001953125), Float(0.80078125), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -3, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, -5, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -2, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, -3, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.0), Float(1.0), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.0), Float(1.0), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, 0, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, 0, 0)
        EndThread
        Thread
            Wait(108)
            Call(SetAnimation, ACTOR_SELF, 12, 0x3B000A)
        EndThread
        Thread
            Call(SetAnimation, ACTOR_SELF, 11, 0x3B0004)
            Wait(143)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 11, 0x3B0009)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 11, 0x3B000A)
        EndThread
        Thread
            Wait(133)
            Call(GetActorPos, 512, LVar0, LVar1, LVar2)
            Add(LVar1, -3)
            Call(SetPartPos, ACTOR_SELF, 11, LVar0, LVar1, LVar2)
            Call(SetAnimation, 512, 1, 0x760005)
            Call(SetPartFlagBits, ACTOR_SELF, 11, 1, 0)
            Add(LVar0, -20)
            Add(LVar1, 18)
            Call(SetPartJumpGravity, ACTOR_SELF, 11, Float(0.6005859375))
            Call(JumpPartTo, ACTOR_SELF, 11, LVar0, LVar1, LVar2, 20, 1)
            Call(SetPartJumpGravity, ACTOR_SELF, 11, Float(0.30078125))
            Call(JumpPartTo, ACTOR_SELF, 11, 50, 54, 0, 30, 1)
            Call(PlaySoundAtPart, ACTOR_SELF, 11, 8292)
            Call(SetAnimation, ACTOR_SELF, 11, 0x3B0007)
            Call(SetAnimation, 512, 1, 0x760004)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 12, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -1, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, -2, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 11, 0, -3, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.2001953125), Float(0.80078125), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.2001953125), Float(0.80078125), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 12, Float(1.2001953125), Float(0.80078125), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -2, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, -3, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 11, 0, -5, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 12, Float(1.1005859375), Float(0.900390625), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, -1, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, -2, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 11, 0, -3, 0)
            Wait(1)
            Call(SetPartScale, ACTOR_SELF, 14, Float(1.0), Float(1.0), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 13, Float(1.0), Float(1.0), Float(1.0))
            Call(SetPartScale, ACTOR_SELF, 12, Float(1.0), Float(1.0), Float(1.0))
            Call(SetPartDispOffset, ACTOR_SELF, 13, 0, 0, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 12, 0, 0, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 11, 0, 0, 0)
            Wait(12)
            Call(SetAnimation, 512, 1, 0x760003)
            Call(GetPartOffset, ACTOR_SELF, 14, LVar0, LVar1, LVar2)
            Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetPartFlagBits, ACTOR_SELF, 11, 1, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 12, 1, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 13, 1, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 14, 1, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 1, 1, 0)
            Call(HPBarToHome, ACTOR_SELF)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Call(SetActorVar, 513, 2, 4)
        EndThread
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_3_Script_TakeTurn_802357B4 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    Call(SetAnimation, ACTOR_SELF, 1, LVar0)
    Wait(20)
    Add(LVar0, 4)
    Call(SetAnimation, ACTOR_SELF, 1, LVar0)
    Call(PlaySoundAtActor, ACTOR_SELF, 743)
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 744)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0, 0, 1, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVar5, 1)
            Call(SetActorVar, ACTOR_SELF, 7, 0)
        EndCaseGroup
        CaseDefault
            Set(LVar5, 0)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetActorVar, ACTOR_SELF, 7, 4)
                CaseEq(1)
                    Call(SetActorVar, ACTOR_SELF, 7, 3)
                CaseEq(2)
                    Call(SetActorVar, ACTOR_SELF, 7, 2)
                CaseEq(3)
                    Call(SetActorVar, ACTOR_SELF, 7, 1)
                CaseDefault
                    Call(SetActorVar, ACTOR_SELF, 7, 1)
            EndSwitch
    EndSwitch
    Set(LVar1, LVar5)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfLe(LVar0, 0)
        Set(LVar0, 0)
        Exec(b_area_omo2_3_shy_stack_EVS_ShootRock)
    EndIf
    IfLe(LVar0, 1)
        Set(LVar0, 1)
        Exec(b_area_omo2_3_shy_stack_EVS_ShootRock)
    EndIf
    IfLe(LVar0, 2)
        Set(LVar0, 2)
        Exec(b_area_omo2_3_shy_stack_EVS_ShootRock)
    EndIf
    Set(LVar0, 3)
    Exec(b_area_omo2_3_shy_stack_EVS_ShootRock)
    Wait(10)
    Call(GetActorVar, ACTOR_SELF, 7, LVar0)
    Switch(LVar0)
        CaseEq(1)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 1, 32)
        CaseEq(2)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 2, 32)
        CaseEq(3)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
        CaseEq(4)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 4, 32)
        CaseDefault
            Switch(LVarF)
                CaseEq(5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                CaseDefault
            EndSwitch
    EndSwitch
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(UseBattleCamPreset, 2)
            Wait(15)
            Wait(15)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

void TTYD64_InstallBattles_omo2_3(void) {
    Mod_ReplaceActorBlueprint("TTYD64", &b_area_omo2_3_shy_stack, &TTYD64_omo2_3_ShyStack);
}
