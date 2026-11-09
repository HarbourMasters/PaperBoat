#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_drop_tables.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/battle/area/battles_a.h"

API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetEnemyMaxHP);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastDamage);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToCurrent);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HideHealthBar);
API_CALLABLE(JumpToGoal);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(ResetAllActorSounds);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetDarknessMode);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetProjectileTargetOffset);
API_CALLABLE(SetTargetOffset);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(b_area_kgr_fuzzipede_CheckPlayerCanLoseCommand);
API_CALLABLE(b_area_kgr_fuzzipede_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_kgr_fuzzipede_StartRumbleWithParams);
extern s32 b_area_kgr_fuzzipede_DefenseTable[];
extern EvtScript b_area_kgr_fuzzipede_EVS_HandlePhase;
extern EvtScript b_area_kgr_fuzzipede_EVS_Idle;
extern EvtScript b_area_kgr_fuzzipede_EVS_ManageCommandLoss;
extern EvtScript b_area_kgr_fuzzipede_EVS_Recover;
extern s32 b_area_kgr_fuzzipede_StatusTable[];
extern Stage b_area_kgr_kgr_01;
extern EvtScript TTYD64_kgr_fuzzipede_EVS_Attack_DisableTackle;
extern EvtScript TTYD64_kgr_fuzzipede_EVS_Attack_Leap;
extern EvtScript TTYD64_kgr_fuzzipede_EVS_Floor_HandleEvent;
extern EvtScript TTYD64_kgr_fuzzipede_EVS_ClimbOntoCeiling;
extern EvtScript TTYD64_kgr_fuzzipede_EVS_Ceiling_HandleEvent;
extern EvtScript TTYD64_kgr_fuzzipede_EVS_LeaveHome;
extern EvtScript TTYD64_kgr_fuzzipede_EVS_HopOntoCrate;
extern EvtScript TTYD64_kgr_fuzzipede_EVS_HopToGround;
extern EvtScript TTYD64_kgr_fuzzipede_EVS_ReturnHome;
extern EvtScript TTYD64_kgr_fuzzipede_EVS_TakeTurn;
extern EvtScript TTYD64_kgr_fuzzipede_EVS_CeilingHit;
extern EvtScript TTYD64_kgr_fuzzipede_EVS_Init;
extern ActorBlueprint TTYD64_kgr_fuzzipede;
extern s32 TTYD64_kgr_fuzzipede_HangingAnims[];
extern s32 TTYD64_kgr_fuzzipede_DefaultAnims[];
extern ActorPartBlueprint TTYD64_kgr_fuzzipede_ActorParts[];
extern Battle TTYD64_kgr_Formations[];
extern FormationRow TTYD64_kgr_Formation_00[];

// clang-format off
EvtScript TTYD64_kgr_fuzzipede_EVS_Attack_DisableTackle = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    ExecWait(TTYD64_kgr_fuzzipede_EVS_LeaveHome)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x41000A)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 80)
    Set(LVar1, 0)
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetAnimation, ACTOR_SELF, 1, 0x410012)
    Wait(30)
    Call(PlaySoundAtActor, ACTOR_SELF, 8411)
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0, 0, 1, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x410011)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.001953125))
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            IfEq(LVarF, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x410004)
            Thread
                Set(LVar0, 90)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 14, 0)
                Loop(6)
                    Add(LVar0, 15)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Sub(LVar0, 30)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Thread
                Set(LVar0, 180)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 14, 0)
                Loop(7)
                    Add(LVar0, 25)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Sub(LVar0, 20)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 7, 0, 1, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(TTYD64_kgr_fuzzipede_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x410011)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.001953125))
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, 1)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
    Wait(1)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0, 0, 3, 32)
    Thread
        Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    EndThread
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Set(LFlag0, 0)
            Call(GetBattleFlags, LVar0)
            IfNotFlag(LVar0, (-0x7FFFFFFF - 1))
                Set(LFlag0, 1)
            EndIf
            Call(GetLastDamage, 0, LVar0)
            IfLe(LVar0, 0)
                Set(LFlag0, 0)
            EndIf
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x80000)
                Set(LFlag0, 0)
            EndIf
            Call(GetStatusFlags, 0, LVar0)
            IfFlag(LVar0, 0x40100000)
                Set(LFlag0, 0)
            EndIf
            IfEq(LFlag0, 1)
                Call(SetActorVar, ACTOR_SELF, 1, 1)
                Exec(b_area_kgr_fuzzipede_EVS_ManageCommandLoss)
                Call(SetAnimation, ACTOR_SELF, 1, 0x410004)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar0, 40)
                Set(LVar1, 0)
                Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                Add(LVar0, 30)
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
                Add(LVar0, 20)
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
                Add(LVar0, 10)
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x410004)
                Wait(8)
                Label(0)
                Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                IfNe(LVar0, 0)
                    Wait(1)
                    Goto(0)
                EndIf
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Loop(3)
                    Sub(LVar0, 10)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
                EndLoop
                Wait(10)
                Call(SetActorVar, ACTOR_SELF, 1, 2)
                Call(PlayEffect_impl, 67, 0, LVar0, LVar1, LVar2, Float(1.0), 0, 0, 0, 0, 0, 0, 0, 0)
                Call(b_area_kgr_fuzzipede_StartRumbleWithParams, 200, 10)
                Call(PlaySoundAtActor, ACTOR_SELF, 8412)
                Call(SetAnimation, ACTOR_SELF, 1, 0x410013)
                Wait(20)
                Call(SetAnimation, ACTOR_SELF, 1, 0x410004)
            Else
                Call(SetAnimation, ACTOR_SELF, 1, 0x410004)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar0, 40)
                Set(LVar1, 0)
                Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                Add(LVar0, 30)
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
                Add(LVar0, 20)
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
                Add(LVar0, 10)
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x410004)
                Wait(8)
                Wait(10)
            EndIf
            Call(UseBattleCamPreset, 2)
            ExecWait(TTYD64_kgr_fuzzipede_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kgr_fuzzipede_EVS_Attack_Leap = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    ExecWait(TTYD64_kgr_fuzzipede_EVS_LeaveHome)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x41000A)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetAnimation, ACTOR_SELF, 1, 0x410012)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 8410)
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0, 0, 1, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x410005)
            Thread
                Set(LVar0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 14, 0)
                Loop(20)
                    Add(LVar0, 9)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -20, 0, 5)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, -5, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            IfEq(LVarF, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(30)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Thread
                Wait(5)
                Call(SetAnimation, ACTOR_SELF, 1, 0x410004)
            EndThread
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(TTYD64_kgr_fuzzipede_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x410005)
    Thread
        Set(LVar0, 0)
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 14, 0)
        Loop(20)
            Add(LVar0, 9)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
    Wait(1)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 128, 0, 0, 3, 32)
    Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x410004)
            Thread
                Set(LVar0, 180)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 14, 0)
                Loop(10)
                    Sub(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Add(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Wait(8)
            ExecWait(TTYD64_kgr_fuzzipede_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kgr_fuzzipede_EVS_Floor_HandleEvent = {
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001B)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001E)
            SetConst(LVar2, 0x41001F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001E)
            SetConst(LVar2, 0x41001F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001F)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x410008)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(TTYD64_kgr_fuzzipede_EVS_ReturnHome)
        CaseEq(38)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x410004)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001B)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            Call(SetActorYaw, ACTOR_SELF, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x410004)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(63)
            Call(SetAnimation, ACTOR_SELF, 1, 0x410019)
            Call(UseBattleCamPreset, 1)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(UseBattleCamPreset, 2)
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kgr_fuzzipede_EVS_ClimbOntoCeiling = {
    Call(SetHomePos, ACTOR_SELF, 30, 115, -28)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(SetAnimation, ACTOR_SELF, 1, 0x41000A)
    Set(LVar0, 65)
    Set(LVar1, 0)
    Set(LVar2, -15)
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
    Call(SetGoalPos, ACTOR_SELF, 125, 33, -15)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(SetGoalPos, ACTOR_SELF, 130, 100, -28)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
    Call(SetGoalPos, ACTOR_SELF, 110, 109, -28)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Call(SetGoalPos, ACTOR_SELF, 90, 117, -28)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Call(SetGoalPos, ACTOR_SELF, 70, 120, -28)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Call(SetGoalPos, ACTOR_SELF, 50, 125, -28)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Call(SetGoalPos, ACTOR_SELF, 30, 130, -28)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Loop(10)
            AddF(LVar1, Float(-1.5))
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Set(LVar0, 0)
    Loop(10)
        Add(LVar0, 18)
        Call(SetActorRotation, ACTOR_SELF, LVar0, 0, 0)
        Wait(1)
    EndLoop
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kgr_fuzzipede_HangingAnims))
    Call(SetAnimation, ACTOR_SELF, 1, 0x410006)
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kgr_fuzzipede_EVS_Ceiling_HandleEvent))
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 1)
    Call(SetTargetOffset, ACTOR_SELF, 1, 2, 24)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 2, 8)
    Call(b_area_kgr_fuzzipede_SetAbsoluteStatusOffsets, -10, -25, 10, -30)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x800000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20000, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x800000, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20000, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kgr_fuzzipede_EVS_Ceiling_HandleEvent = {
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001C)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001C)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_kgr_fuzzipede_EVS_CeilingHit)
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x410020)
            SetConst(LVar2, 0x410021)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_kgr_fuzzipede_EVS_CeilingHit)
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x410020)
            SetConst(LVar2, 0x410021)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x410021)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x410008)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(TTYD64_kgr_fuzzipede_EVS_ReturnHome)
        CaseEq(38)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x410006)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001C)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x41001C)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kgr_fuzzipede_EVS_LeaveHome = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 60)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
        CaseEq(3)
        CaseOrEq(1)
        CaseOrEq(2)
        CaseOrEq(4)
            Call(SetActorFlagBits, ACTOR_SELF, 2560, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x410004)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 180)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.001953125))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVarA)
            IfFlag(LVarA, 0x80000)
                Set(LVar1, 11)
            Else
                Set(LVar1, 28)
            EndIf
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Wait(1)
            Thread
                Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            EndThread
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 14, 0)
                Set(LVar0, 180)
                Loop(8)
                    Sub(LVar0, 22)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kgr_fuzzipede_EVS_HopOntoCrate = {
    Call(SetHomePos, ACTOR_SELF, 125, 33, -15)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(SetAnimation, ACTOR_SELF, 1, 0x41000A)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 60)
    Set(LVar1, 0)
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x410004)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kgr_fuzzipede_DefaultAnims))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kgr_fuzzipede_EVS_Floor_HandleEvent))
    Call(SetActorFlagBits, ACTOR_SELF, 2560, 0)
    Call(SetTargetOffset, ACTOR_SELF, 1, 2, 24)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -2, -10)
    Call(b_area_kgr_fuzzipede_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x800000, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x800000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20000, 0)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kgr_fuzzipede_EVS_HopToGround = {
    Call(SetHomePos, ACTOR_SELF, 60, 0, 15)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(SetAnimation, ACTOR_SELF, 1, 0x41000A)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kgr_fuzzipede_DefaultAnims))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kgr_fuzzipede_EVS_Floor_HandleEvent))
    Call(SetActorFlagBits, ACTOR_SELF, 2560, 0)
    Call(SetTargetOffset, ACTOR_SELF, 1, 2, 24)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -2, -10)
    Call(b_area_kgr_fuzzipede_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x800000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20000, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x800000, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20000, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kgr_fuzzipede_EVS_ReturnHome = {
    Call(HideHealthBar, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 0, 2)
        CaseEq(2)
            Call(SetActorVar, ACTOR_SELF, 0, 3)
        CaseEq(3)
            Call(SetActorVar, ACTOR_SELF, 0, 4)
        CaseEq(4)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_kgr_fuzzipede_EVS_HopOntoCrate)
        CaseOrEq(1)
        CaseOrEq(2)
        CaseOrEq(4)
            ExecWait(TTYD64_kgr_fuzzipede_EVS_ClimbOntoCeiling)
        EndCaseGroup
        CaseEq(3)
            ExecWait(TTYD64_kgr_fuzzipede_EVS_HopToGround)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kgr_fuzzipede_EVS_TakeTurn = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(3)
            Call(GetActorHP, ACTOR_SELF, LVar0)
            Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
            Mul(LVar0, 100)
            Div(LVar0, LVar1)
            IfLe(LVar0, 35)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 500)
                    ExecWait(b_area_kgr_fuzzipede_EVS_Recover)
                    Return
                EndIf
            EndIf
        EndCaseGroup
    EndSwitch
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 500)
        ExecWait(TTYD64_kgr_fuzzipede_EVS_Attack_Leap)
    Else
        Call(b_area_kgr_fuzzipede_CheckPlayerCanLoseCommand, LVar0)
        IfEq(LVar0, 0)
            ExecWait(TTYD64_kgr_fuzzipede_EVS_Attack_DisableTackle)
        Else
            ExecWait(TTYD64_kgr_fuzzipede_EVS_Attack_Leap)
        EndIf
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kgr_fuzzipede_EVS_CeilingHit = {
    Call(GetLastDamage, ACTOR_SELF, LVar0)
    IfLe(LVar0, 0)
        Return
    EndIf
    Call(HideHealthBar, ACTOR_SELF)
    ExecWait(TTYD64_kgr_fuzzipede_EVS_LeaveHome)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kgr_fuzzipede_DefaultAnims))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kgr_fuzzipede_EVS_Floor_HandleEvent))
    Call(SetActorFlagBits, ACTOR_SELF, 2560, 0)
    Call(SetTargetOffset, ACTOR_SELF, 1, 2, 24)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -2, -10)
    Call(b_area_kgr_fuzzipede_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x35D000)
        Call(SetActorVar, ACTOR_SELF, 0, 3)
        Call(HPBarToCurrent, ACTOR_SELF)
    Else
        ExecWait(TTYD64_kgr_fuzzipede_EVS_ClimbOntoCeiling)
        Wait(20)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kgr_fuzzipede_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kgr_fuzzipede_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kgr_fuzzipede_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kgr_fuzzipede_EVS_Floor_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kgr_fuzzipede_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorPos, ACTOR_SELF, 125, 33, -15)
    Call(SetHomePos, ACTOR_SELF, 125, 33, -15)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetDarknessMode, 1)
    Return
    End
};
// clang-format on

s32 TTYD64_kgr_fuzzipede_HangingAnims[] = {
    1,  0x410006, 7, 0x410002, 6, 0x41002A, 9, 0x410006, 8, 0x410002,
    11, 0x410006, 5, 0x410002, 4, 0x410027, 3, 0x410027, 0,
};

s32 TTYD64_kgr_fuzzipede_DefaultAnims[] = {
    1,  0x410004, 7, 0x410000, 6, 0x410029, 9, 0x410004, 8, 0x410000,
    11, 0x410004, 5, 0x410000, 4, 0x410026, 3, 0x410026, 0,
};

ActorPartBlueprint TTYD64_kgr_fuzzipede_ActorParts[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_kgr_fuzzipede_DefaultAnims,
        .defenseTable = b_area_kgr_fuzzipede_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -2, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x80800001,
        .index = 2,
        .posOffset = { 0, 40, 0 },
        .targetOffset = { 2, -16 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_kgr_fuzzipede_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -2, -10 },
        .overrideNameMsg = 0,
    },
};

ActorBlueprint TTYD64_kgr_fuzzipede = {
    .flags = 0x0,
    .maxHP = 20,
    .type = 0x25,
    .level = 43,
    .partCount = 2,
    .partsData = TTYD64_kgr_fuzzipede_ActorParts,
    .initScript = &TTYD64_kgr_fuzzipede_EVS_Init,
    .statusTable = b_area_kgr_fuzzipede_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 26, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

Battle TTYD64_kgr_Formations[] = {
    { .name = "\261\340\267",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_kgr_Formation_00,
      .stage = &b_area_kgr_kgr_01,
      .onBattleStart = NULL },
    {},
};

FormationRow TTYD64_kgr_Formation_00[] = {
    { .actor = &TTYD64_kgr_fuzzipede,
      .home = { .index = 2 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

void TTYD64_InstallBattles_kgr(void) {
    Mod_SetBattleList("TTYD64", 19, TTYD64_kgr_Formations);
}
