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

API_CALLABLE(ActorSpeak);
API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(EnableBattleStatusBar);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EndActorSpeech);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(JumpToGoal);
API_CALLABLE(LandJump);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(ResetActorSounds);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetDamageSource);
API_CALLABLE(SetEndBattleFadeOutRate);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetTargetActor);
API_CALLABLE(ShakeCam);
API_CALLABLE(StartRumble);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
extern s32 b_area_dgb_clubba_DefenseTable[];
extern EvtScript b_area_dgb_clubba_EVS_HandleEvent;
extern EvtScript b_area_dgb_clubba_EVS_Idle;
extern Stage b_area_dgb_dgb_01;
extern s32 b_area_dgb_tubba_blubba_DefenseTable[];
extern EvtScript b_area_dgb_tubba_blubba_EVS_HandleEvent;
extern EvtScript b_area_dgb_tubba_blubba_EVS_HandlePhase;
extern EvtScript b_area_dgb_tubba_blubba_EVS_Idle;
extern EvtScript b_area_dgb_tubba_blubba_EVS_PlayFootstepQuaking;
extern EvtScript b_area_dgb_tubba_blubba_EVS_ReturnHome;
extern s32 b_area_dgb_tubba_blubba_StatusTable[];
extern Vec3i b_area_dgb_vector3D_8021B348;
extern EvtScript TTYD64_dgb_tubba_blubba_EVS_Attack_BodySlam;
extern EvtScript TTYD64_dgb_tubba_blubba_EVS_TakeTurn;
extern EvtScript TTYD64_dgb_tubba_blubba_EVS_Attack_SlamFist;
extern EvtScript TTYD64_dgb_clubba_EVS_TakeTurn;
extern EvtScript TTYD64_dgb_tubba_blubba_EVS_Init;
extern EvtScript TTYD64_dgb_clubba_EVS_Init;
extern ActorBlueprint TTYD64_dgb_clubba;
extern ActorBlueprint TTYD64_dgb_tubba_blubba;
extern s32 TTYD64_dgb_clubba_StatusTable[];
extern Battle TTYD64_dgb_Formations[];
extern FormationRow TTYD64_dgb_Formation_03[];
extern s32 TTYD64_dgb_tubba_blubba_DefaultAnims[];
extern FormationRow TTYD64_dgb_Formation_02[];
extern s32 TTYD64_dgb_clubba_DefaultAnims[];
extern FormationRow TTYD64_dgb_Formation_01[];
extern ActorPartBlueprint TTYD64_dgb_clubba_ActorParts[];
extern ActorPartBlueprint TTYD64_dgb_tubba_blubba_ActorParts[];
extern FormationRow TTYD64_dgb_Formation_00[];
extern FormationRow TTYD64_dgb_Formation_04[];
extern FormationRow TTYD64_dgb_Formation_05[];

// clang-format off
EvtScript TTYD64_dgb_tubba_blubba_EVS_Attack_BodySlam = {
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamDist, 180)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6B0007)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 70, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6B000F)
    Wait(8)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6B0010)
    Call(SetActorSounds, ACTOR_SELF, 2, 999, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Wait(12)
                Call(SetAnimation, ACTOR_SELF, 1, 0x6B0011)
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 15)
            Set(LVar1, 0)
            Add(LVar2, 5)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 23, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8426)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6B0012)
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 60, 8, 10, 20, 0, 0, 0, 0, 0)
            EndThread
            Thread
                Call(StartRumble, 1)
                Call(ShakeCam, 1, 0, 5, Float(3.0))
            EndThread
            Call(ResetActorSounds, ACTOR_SELF, 2)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 0)
            Add(LVar2, 5)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(StartRumble, 1)
            Call(ShakeCam, 1, 0, 5, Float(3.0))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 60, 8, 10, 20, 0, 0, 0, 0, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Wait(8)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6B0013)
            Wait(4)
            ExecWait(b_area_dgb_tubba_blubba_EVS_ReturnHome)
            Return
        EndCaseGroup
        CaseDefault
            Thread
                Wait(12)
                Call(SetAnimation, ACTOR_SELF, 1, 0x6B0011)
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
    EndSwitch
    Wait(2)
    Call(PlaySoundAtActor, ACTOR_SELF, 8426)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar5)
    IfNotFlag(LVar5, 0x80000)
        Call(SetDamageSource, 24)
        Call(PlaySoundAtActor, ACTOR_SELF, 8426)
    EndIf
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 6, 32)
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamDist, 200)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(MoveBattleCamOver, 30)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(GetStatusFlags, ACTOR_SELF, LVar5)
            IfFlag(LVar5, 0x80000)
                Goto(1)
            EndIf
            Call(GetBattleFlags, LVar0)
            IfNotFlag(LVar0, (-0x7FFFFFFF - 1))
                Call(GetOwnerTarget, LVar2, 0)
                Call(GetStatusFlags, LVar2, LVar0)
                IfNotFlag(LVar0, 0x100000)
                    Call(LandJump, ACTOR_SELF)
                Else
                    Goto(1)
                EndIf
            Else
                Goto(1)
            EndIf
            Label(0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 37, 0, LVar0, 0, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6B000D)
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 60, 8, 10, 20, 0, 0, 0, 0, 0)
            EndThread
            Thread
                Call(StartRumble, 1)
                Call(ShakeCam, 1, 0, 5, Float(3.0))
            EndThread
            Call(ResetActorSounds, ACTOR_SELF, 2)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 0)
            Add(LVar2, 5)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(StartRumble, 1)
            Call(ShakeCam, 1, 0, 5, Float(3.0))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 60, 8, 10, 20, 0, 0, 0, 0, 0)
            Goto(2)
            Label(1)
            Call(GetStatusFlags, ACTOR_SELF, LVar5)
            IfNotFlag(LVar5, 0x80000)
                Wait(3)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(PlayEffect_impl, 37, 1, LVar0, 0, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                Call(StartRumble, 1)
                Call(ShakeCam, 1, 0, 5, Float(3.0))
            EndIf
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Thread
                Wait(8)
                Call(SetAnimation, ACTOR_SELF, 1, 0x6B000E)
            EndThread
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            IfNotFlag(LVar5, 0x80000)
                Call(StartRumble, 1)
                Call(ShakeCam, 1, 0, 5, Float(3.0))
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 60, 8, 10, 20, 0, 0, 0, 0, 0)
                Wait(8)
            EndIf
            Label(2)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            IfEq(LVarF, 10)
                Return
            EndIf
            Call(YieldTurn)
            ExecWait(b_area_dgb_tubba_blubba_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_dgb_tubba_blubba_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    IfEq(LVar0, 6)
        Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetAnimation, ACTOR_SELF, 1, 0x6B0007)
        Call(SetGoalPos, ACTOR_SELF, 0, 0, 0)
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x6B0001)
        Wait(30)
        Set(LVar0, 0)
        Loop(12)
            Add(LVar0, 15)
            Call(SetActorYaw, ACTOR_SELF, LVar0)
            Wait(1)
        EndLoop
        Wait(10)
        Set(LVar0, 180)
        Loop(12)
            Sub(LVar0, 15)
            Call(SetActorYaw, ACTOR_SELF, LVar0)
            Wait(1)
        EndLoop
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x6B0002)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 80)
        Call(PlayEffect_impl, 16, 2, 0, LVar0, LVar1, LVar2, 30, 315, 30, 0, 0, 0, 0, 0)
        Wait(40)
        Call(SetAnimation, ACTOR_SELF, 1, 0x6B0001)
        Set(LVar0, 0)
        Loop(15)
            Add(LVar0, 12)
            Call(SetActorYaw, ACTOR_SELF, LVar0)
            Wait(1)
        EndLoop
        Call(SetAnimation, ACTOR_SELF, 1, 0x6B0006)
        Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar0, 220)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(GetActorVar, ACTOR_SELF, 2, LVar0)
        KillThread(LVar0)
        Call(SetActorFlagBits, ACTOR_SELF, 0x400000, 1)
        Call(SetBattleFlagBits, 0x60000, 1)
        Call(SetEndBattleFadeOutRate, 10)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    IfEq(LVar0, 1)
        Call(EnableBattleStatusBar, 0)
        Call(SetActorVar, ACTOR_SELF, 1, 2)
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 75)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 380)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 20)
        Wait(20)
        Call(ActorSpeak, 0xE0103, ACTOR_SELF, 1, 0x6B0009, 0x6B0002)
        Thread
            Call(SetAnimation, ACTOR_SELF, 1, 0x6B0015)
            Wait(4)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6B0016)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6B0002)
        EndThread
        Call(EndActorSpeech, ACTOR_SELF, 1, -1, -1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x6B0001)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 15)
        Wait(15)
        Call(EnableBattleStatusBar, 1)
    EndIf
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 60)
        ExecWait(TTYD64_dgb_tubba_blubba_EVS_Attack_SlamFist)
    Else
        ExecWait(TTYD64_dgb_tubba_blubba_EVS_Attack_BodySlam)
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_dgb_tubba_blubba_EVS_Attack_SlamFist = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamDist, 150)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6B0007)
    Call(SetGoalToTarget, ACTOR_SELF)
    IfNotFlag(LVar5, 0x80000)
        Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Else
        Call(AddGoalPos, ACTOR_SELF, 20, 0, 0)
    EndIf
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6B0015)
    Wait(8)
    Call(PlaySoundAtActor, ACTOR_SELF, 862)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6B0016)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6B0017)
    Wait(3)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 0)
        Call(PlayEffect_impl, 6, 4, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 37, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Thread
            Call(StartRumble, 1)
            Call(ShakeCam, 1, 0, 5, Float(15.0))
        EndThread
        Call(PlaySoundAtActor, ACTOR_SELF, 8426)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6B0002)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            ExecWait(b_area_dgb_tubba_blubba_EVS_ReturnHome)
            Return
        EndCaseGroup
        CaseDefault
    EndSwitch
    Call(GetStatusFlags, ACTOR_SELF, LVar5)
    IfNotFlag(LVar5, 0x80000)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 37, 1, LVar0, 0, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    IfNotFlag(LVar5, 0x80000)
        Call(SetDamageSource, 23)
    EndIf
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000000, 0, 0, 4, 32)
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamDist, 200)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(MoveBattleCamOver, 30)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Wait(30)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6B0002)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            IfEq(LVarF, 10)
                Return
            EndIf
            Call(YieldTurn)
            ExecWait(b_area_dgb_tubba_blubba_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_dgb_clubba_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 27)
        Set(LVar1, 0)
        Sub(LVar2, 6)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Wait(15)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x3A0002)
        Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetStatusFlags, ACTOR_SELF, LVar0)
        IfNotFlag(LVar0, 0x80000)
            Call(AddGoalPos, ACTOR_SELF, 27, 0, -6)
        Else
            Call(AddGoalPos, ACTOR_SELF, 10, 0, -6)
        EndIf
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x3A0001)
        Wait(10)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8389)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3A0008)
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                Wait(20)
            EndIf
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3A0002)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x3A0009)
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_SELF, 8389)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3A000A)
    Wait(2)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Thread
                Call(ShakeCam, 1, 0, 10, Float(1.5))
            EndThread
            Call(UseBattleCamPreset, 2)
            Wait(19)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3A0002)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_dgb_tubba_blubba_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_dgb_tubba_blubba_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_dgb_tubba_blubba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_dgb_tubba_blubba_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_dgb_tubba_blubba_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    IfGe(GameByte(0), -30)
        Call(SetActorVar, ACTOR_SELF, 0, 0)
    Else
        Call(SetActorVar, ACTOR_SELF, 0, 1)
    EndIf
    ExecGetTID(b_area_dgb_tubba_blubba_EVS_PlayFootstepQuaking, LVar0)
    Call(SetActorVar, ACTOR_SELF, 2, LVar0)
    Return
    End
};
// clang-format on

s32 TTYD64_dgb_clubba_StatusTable[] = {
    1,  0, 2,  0, 6,  90, 9,  50, 7,  60, 4,  75, 3,  100, 11, 50, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 1, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0,   38, 1,  39, 0,  41, -1, 0,
};

Battle TTYD64_dgb_Formations[] = {
    { .name = "\254\334\363xD",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_dgb_Formation_00,
      .stage = &b_area_dgb_dgb_01,
      .onBattleStart = NULL },
    { .name = "\254\334\363xDx\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_dgb_Formation_01,
      .stage = &b_area_dgb_dgb_01,
      .onBattleStart = NULL },
    { .name = "\254\334\363xDx\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_dgb_Formation_02,
      .stage = &b_area_dgb_dgb_01,
      .onBattleStart = NULL },
    { .name = "\254\334\363xDx\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_dgb_Formation_03,
      .stage = &b_area_dgb_dgb_01,
      .onBattleStart = NULL },
    { .name = "\200fM\311\254\334\363",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_dgb_Formation_04,
      .stage = &b_area_dgb_dgb_01,
      .onBattleStart = NULL },
    { .name = "\200fM\311\254\334\363[\212ujW",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_dgb_Formation_05,
      .stage = &b_area_dgb_dgb_01,
      .onBattleStart = NULL },
    {},
};

FormationRow TTYD64_dgb_Formation_03[] = {
    { .actor = &TTYD64_dgb_clubba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
    { .actor = &TTYD64_dgb_clubba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
    { .actor = &TTYD64_dgb_clubba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
    { .actor = &TTYD64_dgb_clubba,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
};

s32 TTYD64_dgb_tubba_blubba_DefaultAnims[] = {
    1, 0x6B0002, 7, 0x6B0000, 6, 0x6B0000, 9, 0x6B0002, 8, 0x6B0000, 11, 0x6B0000,
    5, 0x6B0000, 5, 0x6B0000, 4, 0x6B0000, 4, 0x6B0000, 3, 0x6B0000, 0,
};

FormationRow TTYD64_dgb_Formation_02[] = {
    { .actor = &TTYD64_dgb_clubba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
    { .actor = &TTYD64_dgb_clubba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
    { .actor = &TTYD64_dgb_clubba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
};

s32 TTYD64_dgb_clubba_DefaultAnims[] = {
    1,  0x3A0001, 7, 0x3A0000, 6, 0x3A0003, 9, 0x3A0001, 8, 0x3A0000,
    11, 0x3A0001, 5, 0x3A0000, 4, 0x3A0005, 3, 0x3A0005, 0,
};

// clang-format off
EvtScript TTYD64_dgb_clubba_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_dgb_clubba_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_dgb_clubba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_dgb_clubba_EVS_HandleEvent))
    Return
    End
};
// clang-format on

FormationRow TTYD64_dgb_Formation_01[] = {
    { .actor = &TTYD64_dgb_clubba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
    { .actor = &TTYD64_dgb_clubba,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
};

ActorBlueprint TTYD64_dgb_clubba = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x1E,
    .level = 13,
    .partCount = 1,
    .partsData = TTYD64_dgb_clubba_ActorParts,
    .initScript = &TTYD64_dgb_clubba_EVS_Init,
    .statusTable = TTYD64_dgb_clubba_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 60,
    .hurricaneChance = 70,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 1,
    .size = { 42, 42 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 35 },
};

ActorBlueprint TTYD64_dgb_tubba_blubba = {
    .flags = 0x0,
    .maxHP = 10,
    .type = 0xA4,
    .level = 0,
    .partCount = 1,
    .partsData = TTYD64_dgb_tubba_blubba_ActorParts,
    .initScript = &TTYD64_dgb_tubba_blubba_EVS_Init,
    .statusTable = b_area_dgb_tubba_blubba_StatusTable,
    .escapeChance = 15,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 100, 100 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -33, 78 },
    .statusTextOffset = { 10, 75 },
};

ActorPartBlueprint TTYD64_dgb_clubba_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -12, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_dgb_clubba_DefaultAnims,
        .defenseTable = b_area_dgb_clubba_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 8, -3 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_dgb_tubba_blubba_ActorParts[] = {
    {
        .flags = 0x802000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -15, 75 },
        .opacity = 255,
        .idleAnimations = TTYD64_dgb_tubba_blubba_DefaultAnims,
        .defenseTable = b_area_dgb_tubba_blubba_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_dgb_Formation_00[] = {
    { .actor = &TTYD64_dgb_clubba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLUBBA },
};

FormationRow TTYD64_dgb_Formation_04[] = {
    { .actor = &TTYD64_dgb_tubba_blubba,
      .home = { .vec = &b_area_dgb_vector3D_8021B348 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_dgb_Formation_05[] = {
    { .actor = &TTYD64_dgb_tubba_blubba,
      .home = { .vec = &b_area_dgb_vector3D_8021B348 },
      .priority = 10,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

void TTYD64_InstallBattles_dgb(void) {
    Mod_SetBattleList("TTYD64", 15, TTYD64_dgb_Formations);
}
