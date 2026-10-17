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

extern ActorBlueprint b_area_omo2_1_shy_squad;
extern ActorPartBlueprint b_area_omo2_1_shy_squad_ActorParts[];
extern EvtScript b_area_omo2_1_shy_squad_EVS_Death;
extern EvtScript b_area_omo2_1_shy_squad_EVS_HandlePhase;
extern EvtScript b_area_omo2_1_shy_squad_EVS_HitReaction;
extern EvtScript b_area_omo2_1_shy_squad_EVS_Idle;
extern EvtScript b_area_omo2_1_shy_squad_EVS_MoveMemberToPos;
extern EvtScript b_area_omo2_1_shy_squad_EVS_MoveSquadHome;
extern EvtScript b_area_omo2_1_shy_squad_EVS_ReduceCrowdSize;
extern EvtScript b_area_omo2_1_shy_squad_EVS_SetMembersAnimation;
extern EvtScript b_area_omo2_1_shy_squad_EVS_Shock;
extern s32 b_area_omo2_1_shy_squad_StatusTable[];
extern ActorBlueprint TTYD64_omo2_1_ShySquad;
extern EvtScript TTYD64_omo2_1_Script_ShySquad_EndAttack;
extern EvtScript TTYD64_omo2_1_Script_HandleEvent_802337D0_2;
extern EvtScript TTYD64_omo2_1_Script_TakeTurn_80235468;
extern EvtScript TTYD64_omo2_1_Script_802348E0;
extern EvtScript TTYD64_omo2_1_Script_Init_8023142C_2;

ActorBlueprint TTYD64_omo2_1_ShySquad = {
    .flags = 0x4,
    .maxHP = 15,
    .type = 0xA8,
    .level = 0,
    .partCount = 16,
    .partsData = b_area_omo2_1_shy_squad_ActorParts,
    .initScript = &TTYD64_omo2_1_Script_Init_8023142C_2,
    .statusTable = b_area_omo2_1_shy_squad_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 28, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

// clang-format off
EvtScript TTYD64_omo2_1_Script_ShySquad_EndAttack = {
    Call(StopSound, 941)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Wait(20)
    Set(LVar0, 15)
    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
    Sub(LVar0, LVar1)
    Switch(LVar0)
        CaseEq(1)
            Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
            Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
        CaseLt(5)
            Call(PlaySoundAtActor, ACTOR_SELF, 1003)
        CaseDefault
            Call(PlaySoundAtActor, ACTOR_SELF, 1004)
    EndSwitch
    Set(LVar1, 0x6E0004)
    ExecWait(b_area_omo2_1_shy_squad_EVS_MoveSquadHome)
    Set(LVar1, 0x6E0001)
    ExecWait(b_area_omo2_1_shy_squad_EVS_SetMembersAnimation)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_1_Script_HandleEvent_802337D0_2 = {
    Call(StopSound, 941)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVarF)
    Switch(LVarF)
        CaseEq(56)
        CaseOrEq(9)
        CaseOrEq(10)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
            SetConst(LVar1, 0x6E000D)
            ExecWait(b_area_omo2_1_shy_squad_EVS_ReduceCrowdSize)
            SetConst(LVar1, 0x6E000D)
            ExecWait(b_area_omo2_1_shy_squad_EVS_HitReaction)
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar1, 0x6E000D)
            ExecWait(b_area_omo2_1_shy_squad_EVS_ReduceCrowdSize)
            SetConst(LVar1, 0x6E000D)
            ExecWait(b_area_omo2_1_shy_squad_EVS_HitReaction)
            Wait(10)
            SetConst(LVar1, 0x6E000D)
            ExecWait(b_area_omo2_1_shy_squad_EVS_Death)
            Return
        CaseEq(14)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
            SetConst(LVar1, 0x6E000E)
            ExecWait(b_area_omo2_1_shy_squad_EVS_ReduceCrowdSize)
            Set(LVar0, 2)
            Loop(15)
                Call(SetAnimation, ACTOR_SELF, LVar0, 0x6E000E)
                Add(LVar0, 1)
            EndLoop
            Wait(20)
            Set(LVar0, 2)
            Loop(15)
                Call(SetAnimation, ACTOR_SELF, LVar0, 0x6E000F)
                Add(LVar0, 1)
            EndLoop
            Wait(15)
        CaseEq(36)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
            SetConst(LVar1, 0x6E000E)
            ExecWait(b_area_omo2_1_shy_squad_EVS_ReduceCrowdSize)
            Set(LVar0, 2)
            Loop(15)
                Call(SetAnimation, ACTOR_SELF, LVar0, 0x6E000E)
                Add(LVar0, 1)
            EndLoop
            Wait(20)
            Set(LVar0, 2)
            Loop(15)
                Call(SetAnimation, ACTOR_SELF, LVar0, 0x6E000F)
                Add(LVar0, 1)
            EndLoop
            Wait(15)
            Wait(10)
            SetConst(LVar1, 0x6E000F)
            ExecWait(b_area_omo2_1_shy_squad_EVS_Death)
            Return
        CaseEq(11)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
            SetConst(LVar1, 0x6E000D)
            ExecWait(b_area_omo2_1_shy_squad_EVS_ReduceCrowdSize)
            SetConst(LVar1, 0x6E000D)
            ExecWait(b_area_omo2_1_shy_squad_EVS_HitReaction)
        CaseEq(33)
            SetConst(LVar1, 0x6E000D)
            ExecWait(b_area_omo2_1_shy_squad_EVS_ReduceCrowdSize)
            SetConst(LVar1, 0x6E000D)
            ExecWait(b_area_omo2_1_shy_squad_EVS_HitReaction)
            SetConst(LVar1, 0x6E000D)
            ExecWait(b_area_omo2_1_shy_squad_EVS_Death)
            Return
        CaseEq(47)
            SetConst(LVar1, 0x6E000D)
            ExecWait(b_area_omo2_1_shy_squad_EVS_ReduceCrowdSize)
            SetConst(LVar1, 0x6E000D)
            ExecWait(b_area_omo2_1_shy_squad_EVS_Shock)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetActorYaw, ACTOR_SELF, 180)
            Set(LVar1, 0x6E0003)
            ExecWait(b_area_omo2_1_shy_squad_EVS_MoveSquadHome)
        CaseEq(38)
            SetConst(LVar1, 0x6E000D)
            ExecWait(b_area_omo2_1_shy_squad_EVS_ReduceCrowdSize)
            SetConst(LVar1, 0x6E000D)
            ExecWait(b_area_omo2_1_shy_squad_EVS_Shock)
            SetConst(LVar1, 0x6E000D)
            ExecWait(b_area_omo2_1_shy_squad_EVS_Death)
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(27)
        CaseOrEq(31)
            Call(GetBattleFlags, LVar2)
            IfFlag(LVar2, 0x80000)
                Call(GetMenuSelection, LVar0, LVar1, LVar2)
                IfEq(LVar2, 183)
                    Set(LVar1, 0x6E0001)
                    ExecWait(b_area_omo2_1_shy_squad_EVS_SetMembersAnimation)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
                EndIf
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x6E0001)
            ExecWait(b_area_omo2_1_shy_squad_EVS_HitReaction)
        EndCaseGroup
        CaseEq(58)
            Set(LVar1, 0x6E0008)
            ExecWait(b_area_omo2_1_shy_squad_EVS_SetMembersAnimation)
            Wait(1000)
        CaseEq(53)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetActorYaw, ACTOR_SELF, 180)
            Set(LVar1, 0x6E0003)
            ExecWait(b_area_omo2_1_shy_squad_EVS_MoveSquadHome)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x6E0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(48)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x6E000D)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(1000)
        CaseEq(57)
        CaseDefault
    EndSwitch
    Set(LVar1, 0x6E0001)
    ExecWait(b_area_omo2_1_shy_squad_EVS_SetMembersAnimation)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_1_Script_TakeTurn_80235468 = {
    ExecWait(TTYD64_omo2_1_Script_802348E0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_1_Script_802348E0 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 19)
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Call(TTYD64_GetPartnerHP_API, LVar3)
    IfGt(LVar3, 0)
        Add(LVar0, -14)
    EndIf
    Add(LVar1, 20)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 350)
    Call(SetBattleCamOffsetY, 34)
    Call(MoveBattleCamOver, 50)
    Set(LVar0, 15)
    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
    Sub(LVar0, LVar1)
    Switch(LVar0)
        CaseEq(1)
            Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
        CaseLt(5)
            Call(PlaySoundAtActor, ACTOR_SELF, 1003)
        CaseDefault
            Call(PlaySoundAtActor, ACTOR_SELF, 1004)
    EndSwitch
    Set(LVar0, 2)
    Set(LVar1, 0x6E0003)
    Loop(15)
        Thread
            Call(TTYD64_GetMarioPos, LVar6)
            IfEq(LVar6, 1)
                Set(LVar6, 0)
            Else
                Set(LVar6, 256)
            EndIf
            Call(GetActorPos, LVar6, LVar2, LVar5, LVar3)
            Call(TTYD64_GetPartnerHP_API, LVar7)
            IfGt(LVar7, 0)
                Add(LVar2, -14)
            EndIf
            Call(GetPartMovementVar, ACTOR_SELF, LVar0, 4, LVar5)
            Add(LVar2, LVar5)
            Call(GetPartMovementVar, ACTOR_SELF, LVar0, 5, LVar5)
            Add(LVar3, LVar5)
            SetF(LVar4, Float(6.0))
            Set(LVar5, 30)
            ExecWait(b_area_omo2_1_shy_squad_EVS_MoveMemberToPos)
        EndThread
        Add(LVar0, 1)
    EndLoop
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(GetOwnerTarget, LVar6, 0)
    Call(GetGoalPos, LVar6, LVar2, LVar5, LVar3)
    Call(TTYD64_GetPartnerHP_API, LVar7)
    IfGt(LVar7, 0)
        Add(LVar2, -14)
    EndIf
    Call(GetPartMovementVar, ACTOR_SELF, 16, 4, LVar5)
    Add(LVar2, LVar5)
    Call(GetPartMovementVar, ACTOR_SELF, 16, 5, LVar5)
    Add(LVar3, LVar5)
    Call(SetGoalPos, ACTOR_SELF, LVar2, 0, LVar3)
    Call(RunToGoal, ACTOR_SELF, 30, 1)
    Set(LVar0, 2)
    Loop(15)
        Call(GetOwnerTarget, LVar6, 0)
        Call(GetActorPos, LVar6, LVar4, LVar5, LVar6)
        Call(TTYD64_GetPartnerHP_API, LVar7)
        IfGt(LVar7, 0)
            Add(LVar4, -14)
        EndIf
        Call(GetPartOffset, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3)
        IfLt(LVar1, LVar4)
            Call(SetPartYaw, ACTOR_SELF, LVar0, 180)
        Else
            Call(SetPartYaw, ACTOR_SELF, LVar0, 0)
        EndIf
        Call(RandInt, 100, LVar7)
        IfLt(LVar7, 50)
            Set(LVar7, 0x6E000D)
        Else
            Set(LVar7, 0x6E0011)
        EndIf
        Call(SetAnimation, ACTOR_SELF, LVar0, LVar7)
        Add(LVar0, 1)
    EndLoop
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarB, 0, 0, 1, 16)
            Switch(LVarB)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarB, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
                    IfLt(LVar0, 14)
                        Call(GetOwnerTarget, LVar6, 0)
                        Call(GetActorPos, LVar6, LVar0, LVar1, LVar2)
                        Call(TTYD64_GetPartnerHP_API, LVar7)
                        IfGt(LVar7, 0)
                            Add(LVar0, -14)
                        EndIf
                        Call(PlayEffect_impl, 6, 3, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                        Thread
                            Loop(7)
                                Call(PlayEffect_impl, 6, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                                Wait(2)
                                Call(PlayEffect_impl, 6, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                                Wait(2)
                            EndLoop
                        EndThread
                    EndIf
                    Wait(36)
                    Call(UseBattleCamPreset, 2)
                    Call(MoveBattleCamOver, 30)
                    Set(LVar0, 15)
                    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                    Sub(LVar0, LVar1)
                    Switch(LVar0)
                        CaseEq(1)
                            Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
                            Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
                        CaseLt(5)
                            Call(PlaySoundAtActor, ACTOR_SELF, 1003)
                        CaseDefault
                            Call(PlaySoundAtActor, ACTOR_SELF, 1004)
                    EndSwitch
                    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
                    Call(SetActorYaw, ACTOR_SELF, 180)
                    Set(LVar1, 0x6E0004)
                    ExecWait(b_area_omo2_1_shy_squad_EVS_MoveSquadHome)
                    Set(LVar1, 0x6E0001)
                    ExecWait(b_area_omo2_1_shy_squad_EVS_SetMembersAnimation)
                    Call(EnableIdleScript, ACTOR_SELF, 1)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
                EndCaseGroup
                CaseEq(7)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 8192, 0, 0, 1, 32)
                CaseDefault
                    Set(LVarE, 15)
                    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
                    Sub(LVarE, LVar0)
                    Set(LVarD, LVarE)
                    Call(PlaySoundAtActor, ACTOR_SELF, 941)
                    Loop(LVarD)
                        IfGt(LVarE, 1)
                            Set(LVar0, 64)
                        Else
                            Set(LVar0, 32)
                        EndIf
                        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                        Call(SetGoalToTarget, ACTOR_SELF)
                        Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 8192, 0, 0, 1, LVar0)
                        Thread
                            Call(GetOwnerTarget, LVar6, 0)
                            Call(GetActorPos, LVar6, LVar1, LVar2, LVar3)
                            Call(TTYD64_GetPartnerHP_API, LVar7)
                            IfGt(LVar7, 0)
                                Add(LVar1, -14)
                            EndIf
                            Call(PlayEffect_impl, 6, 0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                            Wait(2)
                            Call(PlayEffect_impl, 6, 1, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                            Wait(2)
                        EndThread
                        Call(GetOwnerTarget, LVar1, 0)
                        IfEq(LVar1, 0)
                            Call(GetPlayerHP, LVar1)
                            IfEq(LVar1, 0)
                                BreakLoop
                            EndIf
                        Else
                            Call(TTYD64_GetPartnerHP_API, LVar1)
                            IfEq(LVar1, 0)
                                BreakLoop
                            EndIf
                        EndIf
                        Sub(LVarE, 1)
                        IfEq(LVarE, 0)
                            BreakLoop
                        EndIf
                        Wait(10)
                    EndLoop
                    ExecWait(TTYD64_omo2_1_Script_ShySquad_EndAttack)
                    Return
            EndSwitch
        EndCaseGroup
        CaseEq(7)
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 8192, 0, 0, 1, 32)
    EndSwitch
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 8192, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetActorVar, ACTOR_SELF, 4, 1)
        EndCaseGroup
        CaseEq(7)
            Call(SetActorVar, ACTOR_SELF, 4, 2)
        CaseDefault
            Call(SetActorVar, ACTOR_SELF, 4, 0)
    EndSwitch
    Set(LVarE, 15)
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    Sub(LVarE, LVar0)
    Set(LVarD, LVarE)
    Call(PlaySoundAtActor, ACTOR_SELF, 941)
    Loop(LVarD)
        IfGt(LVarE, 1)
            Set(LVar0, 64)
        Else
            Set(LVar0, 32)
        EndIf
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 8192, 0, 0, 1, LVar0)
        Thread
            Call(GetOwnerTarget, LVar6, 0)
            Call(GetActorPos, LVar6, LVar1, LVar2, LVar3)
            Call(TTYD64_GetPartnerHP_API, LVar7)
            IfGt(LVar7, 0)
                Add(LVar1, -14)
            EndIf
            Call(PlayEffect_impl, 6, 0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(2)
            Call(PlayEffect_impl, 6, 1, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(2)
        EndThread
        Call(GetOwnerTarget, LVar1, 0)
        IfEq(LVar1, 0)
            Call(GetPlayerHP, LVar1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        Else
            Call(TTYD64_GetPartnerHP_API, LVar1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndIf
        Call(GetActorVar, ACTOR_SELF, 4, LVar1)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        IfEq(LVar1, 2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 8192, 0, 0, 1, 32)
        Else
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 8192, 0, 0, 1, LVar0)
        EndIf
        Call(GetOwnerTarget, LVar1, 0)
        IfEq(LVar1, 0)
            Call(GetPlayerHP, LVar1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        Else
            Call(TTYD64_GetPartnerHP_API, LVar1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndIf
        Label(0)
        Sub(LVarE, 1)
        IfEq(LVarE, 0)
            BreakLoop
        EndIf
        Wait(10)
    EndLoop
    ExecWait(TTYD64_omo2_1_Script_ShySquad_EndAttack)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_1_Script_Init_8023142C_2 = {
    Call(TTYD64_GetActorPointer, ACTOR_SELF, LVar0)
    Call(TTYD64_SetActorHP, LVar0, 15, 15)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo2_1_Script_TakeTurn_80235468))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo2_1_shy_squad_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_omo2_1_Script_HandleEvent_802337D0_2))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_omo2_1_shy_squad_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(SetPartMovementVar, ACTOR_SELF, 2, 0, 50)
    Call(SetPartMovementVar, ACTOR_SELF, 2, 1, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 3, 0, 50)
    Call(SetPartMovementVar, ACTOR_SELF, 3, 1, -40)
    Call(SetPartMovementVar, ACTOR_SELF, 4, 0, 40)
    Call(SetPartMovementVar, ACTOR_SELF, 4, 1, 40)
    Call(SetPartMovementVar, ACTOR_SELF, 5, 0, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 5, 1, 40)
    Call(SetPartMovementVar, ACTOR_SELF, 6, 0, 30)
    Call(SetPartMovementVar, ACTOR_SELF, 6, 1, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 7, 0, 40)
    Call(SetPartMovementVar, ACTOR_SELF, 7, 1, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 8, 0, 30)
    Call(SetPartMovementVar, ACTOR_SELF, 8, 1, -40)
    Call(SetPartMovementVar, ACTOR_SELF, 9, 0, 0)
    Call(SetPartMovementVar, ACTOR_SELF, 9, 1, 40)
    Call(SetPartMovementVar, ACTOR_SELF, 10, 0, 10)
    Call(SetPartMovementVar, ACTOR_SELF, 10, 1, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 11, 0, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 11, 1, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 12, 0, 10)
    Call(SetPartMovementVar, ACTOR_SELF, 12, 1, -40)
    Call(SetPartMovementVar, ACTOR_SELF, 13, 0, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 13, 1, -40)
    Call(SetPartMovementVar, ACTOR_SELF, 14, 0, -20)
    Call(SetPartMovementVar, ACTOR_SELF, 14, 1, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 15, 0, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 15, 1, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 16, 0, 0)
    Call(SetPartMovementVar, ACTOR_SELF, 16, 1, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 2, 2, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 2, 3, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 3, 2, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 3, 3, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 4, 2, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 4, 3, 10)
    Call(SetPartMovementVar, ACTOR_SELF, 5, 2, 0)
    Call(SetPartMovementVar, ACTOR_SELF, 5, 3, 10)
    Call(SetPartMovementVar, ACTOR_SELF, 6, 2, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 6, 3, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 7, 2, 30)
    Call(SetPartMovementVar, ACTOR_SELF, 7, 3, 0)
    Call(SetPartMovementVar, ACTOR_SELF, 8, 2, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 8, 3, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 9, 2, -20)
    Call(SetPartMovementVar, ACTOR_SELF, 9, 3, 10)
    Call(SetPartMovementVar, ACTOR_SELF, 10, 2, -20)
    Call(SetPartMovementVar, ACTOR_SELF, 10, 3, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 11, 2, 0)
    Call(SetPartMovementVar, ACTOR_SELF, 11, 3, 0)
    Call(SetPartMovementVar, ACTOR_SELF, 12, 2, -20)
    Call(SetPartMovementVar, ACTOR_SELF, 12, 3, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 13, 2, -20)
    Call(SetPartMovementVar, ACTOR_SELF, 13, 3, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 14, 2, -30)
    Call(SetPartMovementVar, ACTOR_SELF, 14, 3, 0)
    Call(SetPartMovementVar, ACTOR_SELF, 15, 2, -20)
    Call(SetPartMovementVar, ACTOR_SELF, 15, 3, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 16, 2, -30)
    Call(SetPartMovementVar, ACTOR_SELF, 16, 3, 0)
    Call(SetPartMovementVar, ACTOR_SELF, 2, 4, -20)
    Call(SetPartMovementVar, ACTOR_SELF, 2, 5, 0)
    Call(SetPartMovementVar, ACTOR_SELF, 3, 4, 10)
    Call(SetPartMovementVar, ACTOR_SELF, 3, 5, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 4, 4, 0)
    Call(SetPartMovementVar, ACTOR_SELF, 4, 5, -20)
    Call(SetPartMovementVar, ACTOR_SELF, 5, 4, 0)
    Call(SetPartMovementVar, ACTOR_SELF, 5, 5, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 6, 4, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 6, 5, 10)
    Call(SetPartMovementVar, ACTOR_SELF, 7, 4, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 7, 5, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 8, 4, 10)
    Call(SetPartMovementVar, ACTOR_SELF, 8, 5, 10)
    Call(SetPartMovementVar, ACTOR_SELF, 9, 4, 30)
    Call(SetPartMovementVar, ACTOR_SELF, 9, 5, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 10, 4, -20)
    Call(SetPartMovementVar, ACTOR_SELF, 10, 5, -20)
    Call(SetPartMovementVar, ACTOR_SELF, 11, 4, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 11, 5, 0)
    Call(SetPartMovementVar, ACTOR_SELF, 12, 4, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 12, 5, 20)
    Call(SetPartMovementVar, ACTOR_SELF, 13, 4, 30)
    Call(SetPartMovementVar, ACTOR_SELF, 13, 5, 10)
    Call(SetPartMovementVar, ACTOR_SELF, 14, 4, -30)
    Call(SetPartMovementVar, ACTOR_SELF, 14, 5, 10)
    Call(SetPartMovementVar, ACTOR_SELF, 15, 4, -30)
    Call(SetPartMovementVar, ACTOR_SELF, 15, 5, -10)
    Call(SetPartMovementVar, ACTOR_SELF, 16, 4, -20)
    Call(SetPartMovementVar, ACTOR_SELF, 16, 5, 20)
    Call(RandInt, 100, LVar0)
    Add(LVar0, 190)
    Call(RandInt, 100, LVar2)
    Add(LVar2, -50)
    Call(SetActorPos, ACTOR_SELF, LVar0, 0, LVar2)
    Set(LVar1, 2)
    Loop(15)
        Call(RandInt, 100, LVar0)
        Add(LVar0, 190)
        Call(RandInt, 100, LVar2)
        Add(LVar2, -50)
        Call(SetPartPos, ACTOR_SELF, LVar1, LVar0, 0, LVar2)
        Add(LVar1, 1)
    EndLoop
    Set(LVar0, 2)
    Loop(15)
        Call(CreatePartShadow, ACTOR_SELF, LVar0)
        Add(LVar0, 1)
    EndLoop
    Call(SetActorSize, ACTOR_SELF, -0xEE6B280, 72)
    Call(SetPartSize, ACTOR_SELF, 1, 24, 24)
    Return
    End
};
// clang-format on

void TTYD64_InstallBattles_omo2_1(void) {
    Mod_ReplaceActorBlueprint("TTYD64", &b_area_omo2_1_shy_squad, &TTYD64_omo2_1_ShySquad);
}
