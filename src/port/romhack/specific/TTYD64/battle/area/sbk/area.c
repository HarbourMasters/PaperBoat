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
API_CALLABLE(AddCoin);
API_CALLABLE(AddGoalPos);
API_CALLABLE(AddVectorPolar);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(CreateHomeTargetList);
API_CALLABLE(DispatchDamageEvent);
API_CALLABLE(EnableActorBlur);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FallToGoal);
API_CALLABLE(FlyPartTo);
API_CALLABLE(FlyToGoal);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetDamageSource);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastDamage);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartOffset);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HideHealthBar);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActor);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(ResetAllActorSounds);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorSize);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSize);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetTargetActor);
API_CALLABLE(ShakeCam);
API_CALLABLE(StartRumble);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
API_CALLABLE(b_area_sbk_pokey_SetAbsoluteStatusOffsets);
extern s32 b_area_sbk_bandit_CoinAnims[];
extern FormationRow b_area_sbk_bandit_CoinFormation[];
extern s32 b_area_sbk_bandit_DefenseTable[];
extern u8 b_area_sbk_bandit_DropCoinScript[];
extern EvtScript b_area_sbk_bandit_EVS_Dummy;
extern EvtScript b_area_sbk_bandit_EVS_Idle;
extern s32 b_area_sbk_bandit_StatusTable[];
extern EvtScript b_area_sbk_pokey_EVS_CountSummonerPokeys;
extern EvtScript b_area_sbk_pokey_EVS_FindValidSummonPosition;
extern EvtScript b_area_sbk_pokey_EVS_HitReactionBounce;
extern Vec3i b_area_sbk_pokey_SummonPos;
extern s32 b_area_sbk_pokey_ThrownPartAnims[];
extern Stage b_area_sbk_sbk_02;
extern EvtScript TTYD64_sbk_bandit_EVS_TakeTurn;
extern EvtScript TTYD64_sbk_pokey_EVS_HandleEvent;
extern EvtScript TTYD64_sbk_pokey_EVS_TakeTurn;
extern EvtScript TTYD64_sbk_pokey_EVS_Attack_GroundSmash;
extern EvtScript TTYD64_sbk_pokey_EVS_Attack_SinglePartLeap;
extern EvtScript TTYD64_sbk_bandit_EVS_HandleEvent;
extern EvtScript TTYD64_sbk_bandit_EVS_DropCoin;
extern EvtScript TTYD64_sbk_pokey_EVS_SummonBackup;
extern EvtScript TTYD64_sbk_pokey_EVS_DecrementSize;
extern EvtScript TTYD64_sbk_pokey_EVS_Pokey_Hit;
extern EvtScript TTYD64_sbk_pokey_EVS_KnockPartAway;
extern EvtScript TTYD64_sbk_pokey_EVS_Pokey_ScareAway;
extern EvtScript TTYD64_sbk_pokey_EVS_Init;
extern EvtScript TTYD64_sbk_pokey_EVS_Pokey_SpinSmashHit;
extern EvtScript TTYD64_sbk_bandit_EVS_Init;
extern ActorBlueprint TTYD64_sbk_bandit;
extern ActorBlueprint TTYD64_sbk_pokey;
extern ActorBlueprint TTYD64_sbk_pokey_8021FED0;
extern Battle TTYD64_sbk_Formations[];
extern ActorPartBlueprint TTYD64_sbk_pokey_ActorParts[];
extern s32 TTYD64_sbk_pokey_StatusTable[];
extern FormationRow TTYD64_sbk_Formation_0C[];
extern FormationRow TTYD64_sbk_Formation_0F[];
extern FormationRow TTYD64_sbk_Formation_03[];
extern FormationRow TTYD64_sbk_Formation_08[];
extern FormationRow TTYD64_sbk_Formation_06[];
extern FormationRow TTYD64_sbk_Formation_0E[];
extern FormationRow TTYD64_sbk_Formation_0B[];
extern FormationRow TTYD64_sbk_Formation_10[];
extern FormationRow TTYD64_sbk_Formation_05[];
extern FormationRow TTYD64_sbk_Formation_02[];
extern FormationRow TTYD64_sbk_Formation_07[];
extern s32 TTYD64_sbk_bandit_HoldingAnims[];
extern s32 TTYD64_sbk_bandit_DefaultAnims[];
extern ActorPartBlueprint TTYD64_sbk_bandit_ActorParts[];
extern s32 TTYD64_sbk_pokey_OnePartAnims[];
extern s32 TTYD64_sbk_pokey_FourPartAnims[];
extern s32 TTYD64_sbk_pokey_ThreePartAnims[];
extern s32 TTYD64_sbk_pokey_TwoPartAnims[];
extern FormationRow TTYD64_sbk_Formation_0A[];
extern FormationRow TTYD64_sbk_Formation_0D[];
extern FormationRow TTYD64_sbk_Formation_01[];
extern FormationRow TTYD64_sbk_Formation_04[];
extern FormationRow TTYD64_sbk_pokey_SummonFormation[];
extern FormationRow TTYD64_sbk_Formation_00[];
extern FormationRow TTYD64_sbk_Formation_09[];

// clang-format off
EvtScript TTYD64_sbk_bandit_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorYaw, ACTOR_SELF, 180)
        Call(SetAnimation, ACTOR_SELF, 1, 0x320008)
        Wait(30)
        Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
        Call(SetGoalPos, ACTOR_SELF, 300, 0, 0)
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetBattleFlagBits, 0x40000, 1)
        Call(HideHealthBar, ACTOR_SELF)
        Call(RemoveActor, ACTOR_SELF)
        Return
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 50)
        Set(LVar1, 0)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x320007)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
        Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x320001)
        Wait(6)
    EndIf
    Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x320005)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 35, 0, 0)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8386)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x32000D)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Sub(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320007)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320001)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x32000D)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(GetOwnerTarget, LVar3, 0)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(GetLastDamage, LVar3, LVar0)
            IfLe(LVar0, 0)
                Set(LVar0, 1)
                Goto(10)
            EndIf
            Call(GetBattleFlags, LVar0)
            IfFlag(LVar0, (-0x7FFFFFFF - 1))
                Set(LVar0, 1)
                Goto(10)
            EndIf
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x80000)
                Set(LVar0, 0)
                Goto(10)
            EndIf
            Call(GetStatusFlags, LVar3, LVar0)
            IfFlag(LVar0, 0x100000)
                Set(LVar0, 0)
                Goto(10)
            EndIf
            Call(AddCoin, 0)
            Switch(LVar0)
                CaseEq(0)
                    Set(LVar0, 1)
                CaseLt(10)
                    Call(SetActorVar, ACTOR_SELF, 1, LVar0)
                    Set(LVar0, 2)
                CaseGe(10)
                    Call(SetActorVar, ACTOR_SELF, 1, 10)
                    Set(LVar0, 2)
            EndSwitch
            Label(10)
            Switch(LVar0)
                CaseEq(0)
                    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Add(LVar0, 30)
                    Set(LVar1, 0)
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x320001)
                    Wait(20)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x320007)
                CaseEq(1)
                    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Add(LVar0, 30)
                    Set(LVar1, 0)
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x32000E)
                    Wait(20)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8387)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x320010)
                    Wait(20)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x320007)
                CaseDefault
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(GetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
                    Add(LVarA, 30)
                    Set(LVarB, 0)
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Mul(LVar0, -1)
                    Call(AddCoin, LVar0)
                    Thread
                        Call(SetPartFlagBits, ACTOR_SELF, 2, 0x100000, 1)
                        Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
                        Call(GetOwnerTarget, LVar3, 0)
                        Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                        Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
                        Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(1.0))
                        Add(LVarB, 30)
                        Call(JumpPartTo, ACTOR_SELF, 2, LVarA, LVarB, LVarC, 22, 1)
                        Call(SetPartFlagBits, ACTOR_SELF, 2, 0x100000, 0)
                    EndThread
                    Thread
                        Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                        Loop(LVar0)
                            Call(PlaySoundAtActor, ACTOR_SELF, 530)
                            Wait(1)
                        EndLoop
                    EndThread
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
                    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
                    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_sbk_bandit_HoldingAnims))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x32000E)
                    Call(SetActorVar, ACTOR_SELF, 0, 1)
                    Wait(7)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x32000F)
                    Wait(20)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x320008)
            EndSwitch
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sbk_pokey_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x80000)
                SetConst(LVar0, 1)
                Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 3)
                    SetConst(LVar0, 1)
                    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                    ExecWait(Ref(EVS_Enemy_Hit))
                Else
                    Call(GetDamageSource, LVar0)
                    Switch(LVar0)
                        CaseOrEq(6)
                        CaseOrEq(7)
                        CaseOrEq(9)
                            ExecWait(TTYD64_sbk_pokey_EVS_Pokey_Hit)
                        EndCaseGroup
                        CaseDefault
                            SetConst(LVar0, 1)
                            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                            ExecWait(Ref(EVS_Enemy_Hit))
                    EndSwitch
                EndIf
            EndIf
        CaseEq(32)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x80000)
                SetConst(LVar0, 1)
                Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
            Else
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 3)
                    SetConst(LVar0, 1)
                    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Wait(10)
                Else
                    Call(GetDamageSource, LVar0)
                    Switch(LVar0)
                        CaseOrEq(6)
                        CaseOrEq(7)
                        CaseOrEq(9)
                            ExecWait(TTYD64_sbk_pokey_EVS_Pokey_Hit)
                        EndCaseGroup
                        CaseDefault
                            SetConst(LVar0, 1)
                            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                            ExecWait(Ref(EVS_Enemy_Hit))
                            Wait(10)
                    EndSwitch
                EndIf
            EndIf
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(14)
            Call(GetActorVar, ACTOR_SELF, 6, LVar1)
            Call(GetActorVar, ACTOR_SELF, 7, LVar2)
            SetConst(LVar0, 1)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 3)
                    ExecWait(Ref(EVS_Enemy_BurnHit))
                Else
                    Call(GetDamageSource, LVarA)
                    Switch(LVarA)
                        CaseOrEq(6)
                        CaseOrEq(7)
                        CaseOrEq(9)
                            ExecWait(TTYD64_sbk_pokey_EVS_Pokey_Hit)
                        EndCaseGroup
                        CaseDefault
                            ExecWait(Ref(EVS_Enemy_BurnHit))
                    EndSwitch
                EndIf
            EndIf
        CaseOrEq(36)
            Call(GetActorVar, ACTOR_SELF, 6, LVar1)
            Call(GetActorVar, ACTOR_SELF, 7, LVar2)
            SetConst(LVar0, 1)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 3)
                    ExecWait(Ref(EVS_Enemy_BurnHit))
                Else
                    Call(GetDamageSource, LVarA)
                    Switch(LVarA)
                        CaseOrEq(6)
                        CaseOrEq(7)
                        CaseOrEq(9)
                            ExecWait(TTYD64_sbk_pokey_EVS_Pokey_Hit)
                        EndCaseGroup
                        CaseDefault
                            ExecWait(Ref(EVS_Enemy_BurnHit))
                    EndSwitch
                EndIf
            EndIf
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 7, LVar1)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            ExecWait(TTYD64_sbk_pokey_EVS_Pokey_SpinSmashHit)
        CaseEq(33)
            ExecWait(TTYD64_sbk_pokey_EVS_Pokey_SpinSmashHit)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(17)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                SetConst(LVar0, 1)
                Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                ExecWait(TTYD64_sbk_pokey_EVS_Pokey_Hit)
            EndIf
        CaseEq(37)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                SetConst(LVar0, 1)
                Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                ExecWait(TTYD64_sbk_pokey_EVS_Pokey_Hit)
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, -1)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Call(GetActorVar, ACTOR_SELF, 2, LVar1)
            Call(SetAnimation, ACTOR_SELF, 1, LVar1)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            ExecWait(Ref(EVS_Enemy_HopToPos))
        CaseEq(38)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 1, LVar1)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(27)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Set(LVar0, 0)
                    Set(LVar1, 77)
                    SetConst(LVar2, 0x310021)
                CaseEq(1)
                    Set(LVar0, 0)
                    Set(LVar1, 59)
                    SetConst(LVar2, 0x310022)
                CaseEq(2)
                    Set(LVar0, 0)
                    Set(LVar1, 41)
                    SetConst(LVar2, 0x310023)
                CaseEq(3)
                    Set(LVar0, 0)
                    Set(LVar1, 23)
                    SetConst(LVar2, 0x310024)
            EndSwitch
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfNotFlag(LVar3, 4096)
                Call(SetAnimation, ACTOR_SELF, 1, LVar2)
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Call(GetStatusFlags, ACTOR_SELF, LVar6)
            IfFlag(LVar6, 0x80000)
                MulF(LVar0, Float(0.400390625))
                MulF(LVar1, Float(0.400390625))
            EndIf
            AddF(LVar3, LVar0)
            AddF(LVar4, LVar1)
            Call(PlayEffect_impl, 26, 0, LVar3, LVar4, LVar5, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(30)
        CaseEq(49)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 1, LVar1)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            ExecWait(TTYD64_sbk_pokey_EVS_Pokey_ScareAway)
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
EvtScript TTYD64_sbk_pokey_EVS_TakeTurn = {
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfEq(LVarA, 3)
        ExecWait(TTYD64_sbk_pokey_EVS_Attack_SinglePartLeap)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 9, LVar0)
    IfEq(LVar0, 0)
        Call(GetActorVar, ACTOR_SELF, 10, LVar0)
        IfEq(LVar0, 2)
            Goto(123)
        EndIf
        ExecWait(b_area_sbk_pokey_EVS_FindValidSummonPosition)
        IfEq(LVarE, -1)
            Goto(123)
        EndIf
        ExecWait(b_area_sbk_pokey_EVS_CountSummonerPokeys)
        Switch(LVar9)
            CaseEq(1)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 400)
                    ExecWait(TTYD64_sbk_pokey_EVS_SummonBackup)
                    Return
                EndIf
            CaseEq(2)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 200)
                    ExecWait(TTYD64_sbk_pokey_EVS_SummonBackup)
                    Return
                EndIf
            CaseEq(3)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 100)
                    ExecWait(TTYD64_sbk_pokey_EVS_SummonBackup)
                    Return
                EndIf
        EndSwitch
    EndIf
    Label(123)
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 500)
        ExecWait(TTYD64_sbk_pokey_EVS_Attack_GroundSmash)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    EndIf
    Call(SetPartSounds, ACTOR_SELF, 6, 2, 0, 0)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 6, Float(1.0), Float(1.0), Float(1.0))
    Else
        Call(SetPartScale, ACTOR_SELF, 6, Float(0.400390625), Float(0.400390625), Float(1.0))
    EndIf
    ChildThread
        Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
        Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(2.2001953125))
        Call(SetAnimation, ACTOR_SELF, 6, 0x310016)
        Call(GetStatusFlags, ACTOR_SELF, LVar5)
        Call(GetActorVar, ACTOR_SELF, 0, LVarA)
        Switch(LVarA)
            CaseEq(0)
                IfNotFlag(LVar5, 0x80000)
                    Add(LVar1, 38)
                Else
                    Add(LVar1, 15)
                    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(1.2001953125))
                EndIf
                Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 15, 1)
            CaseEq(1)
                IfNotFlag(LVar5, 0x80000)
                    Add(LVar1, 20)
                Else
                    Add(LVar1, 8)
                    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(1.2001953125))
                EndIf
                Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 15, 1)
            CaseEq(2)
                IfNotFlag(LVar5, 0x80000)
                    Add(LVar1, 8)
                Else
                    Add(LVar1, 3)
                    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(1.2001953125))
                EndIf
                Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 15, 1)
            CaseEq(3)
        EndSwitch
    EndChildThread
    Call(PlaySoundAtActor, ACTOR_SELF, 834)
    Call(GetActorVar, ACTOR_SELF, 4, LVar1)
    Call(SetAnimation, ACTOR_SELF, 1, LVar1)
    Wait(12)
    Call(GetActorVar, ACTOR_SELF, 5, LVar1)
    Call(SetAnimation, ACTOR_SELF, 1, LVar1)
    Wait(1)
    Call(PlaySoundAtActor, ACTOR_SELF, 718)
    Wait(3)
    ExecWait(TTYD64_sbk_pokey_EVS_DecrementSize)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVar0, 5)
                ChildThread
                    Wait(5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndChildThread
            EndIf
            Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 80)
            Sub(LVar1, 5)
            Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(20.0))
            Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
            Call(SetAnimation, ACTOR_SELF, 6, 0x310016)
            Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
            Call(GetActorVar, ACTOR_SELF, 2, LVar1)
            Call(SetAnimation, ACTOR_SELF, 1, LVar1)
            Return
        EndCaseGroup
    EndSwitch
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(20.0))
    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
    Call(SetAnimation, ACTOR_SELF, 6, 0x310016)
    Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 1)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, -0x7FFDFD00, 3, 32)
    Call(GetActorVar, ACTOR_SELF, 2, LVar1)
    Call(SetAnimation, ACTOR_SELF, 1, LVar1)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(GetOwnerTarget, LVar3, 0)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Sub(LVar0, 55)
            Set(LVar1, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(6.0))
            Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
            Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 25, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(4.0))
            Sub(LVar0, 24)
            Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 21, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(3.0))
            Sub(LVar0, 20)
            Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 20, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sbk_pokey_EVS_Attack_GroundSmash = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Call(AddGoalPos, ACTOR_SELF, 60, 0, 0)
            Else
                Call(AddGoalPos, ACTOR_SELF, 24, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x310008)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310004)
        CaseEq(1)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Call(AddGoalPos, ACTOR_SELF, 40, 0, 0)
            Else
                Call(AddGoalPos, ACTOR_SELF, 16, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x310009)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310005)
        CaseEq(2)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Call(AddGoalPos, ACTOR_SELF, 20, 0, 0)
            Else
                Call(AddGoalPos, ACTOR_SELF, 8, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x31000A)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310006)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 834)
    Call(MakeLerp, 0, -40, 20, 10)
    Label(0)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    ChildThread
        Wait(3)
        Call(PlaySoundAtActor, ACTOR_SELF, 749)
    EndChildThread
    Call(MakeLerp, -40, 90, 5, 1)
    Label(3)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(3)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 32)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(MakeLerp, 90, 0, 5, 0)
            Label(4)
            Call(UpdateLerp)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(4)
            EndIf
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310008)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310004)
                CaseEq(1)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310009)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310005)
                CaseEq(2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x31000A)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310006)
            EndSwitch
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Set(LVar1, 2)
        CaseEq(1)
            Set(LVar1, 2)
        CaseDefault
            Set(LVar1, 2)
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, -0x7FFDFD00, LVar1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(MakeLerp, 90, 0, 10, 0)
            Label(5)
            Call(UpdateLerp)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(5)
            EndIf
            Call(YieldTurn)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310008)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310004)
                CaseEq(1)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310009)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310005)
                CaseEq(2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x31000A)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310006)
            EndSwitch
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sbk_pokey_EVS_Attack_SinglePartLeap = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorSounds, ACTOR_SELF, 0, 748, 748)
    Call(SetActorSounds, ACTOR_SELF, 2, 748, 0)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0x31000B)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetAnimation, ACTOR_SELF, 1, 0x310007)
    Wait(4)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(4)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x31000B)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 2, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 5)
            Set(LVar1, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.099609375))
            ChildThread
                Wait(2)
                Set(LVar0, 0)
                Loop(5)
                    Add(LVar0, 30)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndChildThread
            Call(JumpToGoal, ACTOR_SELF, 22, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
            ChildThread
                Wait(2)
                Set(LVar0, 180)
                Loop(6)
                    Add(LVar0, 30)
                    IfEq(LVar0, 360)
                        Set(LVar0, 0)
                    EndIf
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            EndChildThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x31000B)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            ExecWait(Ref(EVS_Enemy_HopToPos))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310007)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.099609375))
    ChildThread
        Wait(2)
        Set(LVar0, 0)
        Loop(5)
            Add(LVar0, 30)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndChildThread
    Call(JumpToGoal, ACTOR_SELF, 18, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, -0x7FFDFD00, 4, 32)
    Call(SetAnimation, ACTOR_SELF, 1, 0x310007)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
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
            Sub(LVar0, 10)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310007)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x31000B)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            ExecWait(Ref(EVS_Enemy_HopToPos))
            Call(SetAnimation, ACTOR_SELF, 1, 0x310007)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sbk_bandit_EVS_HandleEvent = {
    UseArray(Ref(b_area_sbk_bandit_DropCoinScript))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            ExecGetTID(TTYD64_sbk_bandit_EVS_DropCoin, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320009)
            ExecWait(Ref(EVS_Enemy_Hit))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        CaseOrEq(10)
        CaseOrEq(17)
            ExecGetTID(TTYD64_sbk_bandit_EVS_DropCoin, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320009)
            ExecWait(Ref(EVS_Enemy_Hit))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        EndCaseGroup
        CaseEq(14)
            ExecGetTID(TTYD64_sbk_bandit_EVS_DropCoin, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x32000A)
            SetConst(LVar2, 0x32000B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        CaseEq(36)
            ExecGetTID(TTYD64_sbk_bandit_EVS_DropCoin, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x32000A)
            SetConst(LVar2, 0x32000B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x32000B)
            ExecWait(Ref(EVS_Enemy_Death))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            Return
        CaseEq(11)
            ExecGetTID(TTYD64_sbk_bandit_EVS_DropCoin, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320009)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        CaseEq(33)
            ExecGetTID(TTYD64_sbk_bandit_EVS_DropCoin, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320009)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320009)
            ExecWait(Ref(EVS_Enemy_Death))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320009)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320009)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320007)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320009)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320009)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar1, 0x320001)
                CaseEq(1)
                    SetConst(LVar1, 0x320002)
            EndSwitch
            SetConst(LVar0, 1)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseOrEq(32)
        CaseOrEq(37)
            ExecGetTID(TTYD64_sbk_bandit_EVS_DropCoin, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320009)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320009)
            ExecWait(Ref(EVS_Enemy_Death))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            Return
        EndCaseGroup
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            ExecGetTID(TTYD64_sbk_bandit_EVS_DropCoin, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320007)
            SetConst(LVar2, 0x320009)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            Return
        CaseEq(58)
            ExecGetTID(TTYD64_sbk_bandit_EVS_DropCoin, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320009)
            ExecWait(Ref(EVS_Enemy_AirLift))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320009)
            SetConst(LVar2, 0x40000)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x320001)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sbk_bandit_EVS_DropCoin = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_sbk_bandit_DefaultAnims))
            Call(SetPartFlagBits, ACTOR_SELF, 2, 0x100000, 0)
            Call(SummonEnemy, Ref(b_area_sbk_bandit_CoinFormation), 0)
            Set(LVarA, LVar0)
            Call(GetPartOffset, ACTOR_SELF, 2, LVar1, LVar2, LVar3)
            Call(SetActorPos, LVarA, LVar1, LVar2, LVar3)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Call(SetActorVar, LVarA, 1, LVar0)
            Call(SetActorJumpGravity, LVarA, Float(1.0))
            Call(RandInt, 360, LVar0)
            Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
            Add(LVar2, 30)
            Call(SetActorPos, LVarA, LVar1, LVar2, LVar3)
            Call(SetActorSounds, LVarA, 2, 0, 0)
            Call(AddVectorPolar, LVar1, LVar3, Float(40.0), LVar0)
            Call(SetGoalPos, LVarA, LVar1, 0, LVar3)
            Call(JumpToGoal, LVarA, 20, 0, 1, 0)
            Call(PlaySoundAtActor, LVarA, 530)
            Call(AddVectorPolar, LVar1, LVar3, Float(20.0), LVar0)
            Call(SetGoalPos, LVarA, LVar1, 0, LVar3)
            Call(JumpToGoal, LVarA, 10, 0, 1, 0)
            Call(PlaySoundAtActor, LVarA, 530)
            Call(AddVectorPolar, LVar1, LVar3, Float(10.0), LVar0)
            Call(SetGoalPos, LVarA, LVar1, 0, LVar3)
            Call(JumpToGoal, LVarA, 5, 0, 1, 0)
            Call(PlaySoundAtActor, LVarA, 530)
            Loop(0)
                Call(GetBattleFlags, LVar1)
                IfFlag(LVar1, 0x80000)
                    BreakLoop
                EndIf
                IfNotFlag(LVar1, 256)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            Wait(15)
            Call(SetActorJumpGravity, LVarA, Float(1.0))
            Call(SetActorSpeed, LVarA, Float(6.0))
            Set(LVar0, -70)
            Set(LVar1, 0)
            Set(LVar2, 10)
            Label(5)
            Call(GetActorPos, LVarA, LVar3, LVar4, LVar5)
            IfEq(LVar3, LVar0)
                Goto(10)
            EndIf
            IfLt(LVar3, LVar0)
                Set(LVar4, LVar0)
                Sub(LVar4, LVar3)
                IfLt(LVar4, 30)
                    Call(SetGoalPos, LVarA, LVar0, LVar1, LVar2)
                    Call(JumpToGoal, LVarA, 5, 0, 1, 0)
                    Call(PlaySoundAtActor, LVarA, 530)
                Else
                    Set(LVar4, LVar3)
                    Add(LVar3, 30)
                    Call(SetGoalPos, LVarA, LVar3, LVar1, LVar2)
                    Call(JumpToGoal, LVarA, 0, 0, 1, 0)
                    Call(PlaySoundAtActor, LVarA, 530)
                EndIf
            Else
                Set(LVar4, LVar3)
                Sub(LVar4, LVar0)
                IfLt(LVar4, 30)
                    Call(SetGoalPos, LVarA, LVar0, LVar1, LVar2)
                    Call(JumpToGoal, LVarA, 5, 0, 1, 0)
                    Call(PlaySoundAtActor, LVarA, 530)
                Else
                    Sub(LVar3, 30)
                    Call(SetGoalPos, LVarA, LVar3, LVar1, LVar2)
                    Call(JumpToGoal, LVarA, 0, 0, 1, 0)
                    Call(PlaySoundAtActor, LVarA, 530)
                EndIf
            EndIf
            Goto(5)
            Label(10)
            Call(EnableActorBlur, LVarA, 1)
            Call(SetTargetActor, LVarA, 0)
            Call(SetGoalToTarget, LVarA)
            Call(JumpToGoal, LVarA, 15, 0, 0, 0)
            Call(GetGoalPos, LVarA, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 73, 0, LVar0, LVar1, LVar2, Float(1.0), 0, 0, 0, 0, 0, 0, 0, 0)
            Call(PlaySoundAtActor, LVarA, 529)
            Call(GetActorVar, LVarA, 1, LVar0)
            Call(AddCoin, LVar0)
            Call(RemoveActor, LVarA)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sbk_pokey_EVS_SummonBackup = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x310004)
    Call(MakeLerp, 0, -20, 20, 10)
    Label(0)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    ChildThread
        Wait(8)
        Call(PlaySoundAtActor, ACTOR_SELF, 836)
    EndChildThread
    Call(MakeLerp, -20, 30, 20, 10)
    Label(1)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(1)
    EndIf
    ChildThread
        Wait(6)
        Call(PlaySoundAtActor, ACTOR_SELF, 837)
    EndChildThread
    Call(MakeLerp, 30, -40, 20, 10)
    Label(2)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(2)
    EndIf
    ChildThread
        Wait(4)
        Call(PlaySoundAtActor, ACTOR_SELF, 750)
    EndChildThread
    Call(MakeLerp, -40, 90, 10, 10)
    Label(3)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(3)
    EndIf
    Wait(20)
    Call(PlaySoundAtActor, ACTOR_SELF, 838)
    Call(StartRumble, 9)
    Thread
        Call(ShakeCam, 1, 0, 10, Float(1.0))
    EndThread
    Call(SummonEnemy, Ref(TTYD64_sbk_pokey_SummonFormation), 0)
    Set(LVarB, LVar0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Sub(LVar1, 80)
    Call(SetActorPos, LVarB, LVar0, LVar1, LVar2)
    ChildThread
        Call(PlayEffect_impl, 37, 2, LVar0, 0, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(UseIdleAnimation, LVarB, 0)
        Call(SetAnimation, LVarB, 1, 0x31000C)
        Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
        Call(SetActorJumpGravity, LVarB, Float(1.2001953125))
        Call(SetGoalPos, LVarB, LVar0, 0, LVar2)
        Call(JumpToGoal, LVarB, 20, 0, 1, 0)
        Wait(20)
        Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
        Call(SetAnimation, LVarB, 1, 0x310004)
        Call(SetHomePos, LVarB, LVar0, LVar1, LVar2)
        Call(HPBarToHome, LVarB)
        Call(UseIdleAnimation, LVarB, 1)
    EndChildThread
    Call(GetActorVar, ACTOR_SELF, 10, LVar1)
    Switch(LVar1)
        CaseEq(0)
            Call(SetActorVar, LVarB, 10, 1)
        CaseEq(1)
            Call(SetActorVar, LVarB, 10, 2)
    EndSwitch
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Set(LVarA, LVar0)
    Call(MakeLerp, 90, -30, 7, 4)
    Label(4)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(4)
    EndIf
    Wait(20)
    Call(MakeLerp, -30, 0, 10, 10)
    Label(5)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(5)
    EndIf
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x310004)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sbk_pokey_EVS_DecrementSize = {
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    Switch(LVarA)
        CaseEq(0)
            Call(SetActorVar, ACTOR_SELF, 1, 0x310005)
            Call(SetActorVar, ACTOR_SELF, 2, 0x310009)
            Call(SetActorVar, ACTOR_SELF, 3, 0x31000D)
            Call(SetActorVar, ACTOR_SELF, 4, 0x310012)
            Call(SetActorVar, ACTOR_SELF, 5, 0x310013)
            Call(SetActorVar, ACTOR_SELF, 6, 0x31001A)
            Call(SetActorVar, ACTOR_SELF, 7, 0x31001B)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_sbk_pokey_ThreePartAnims))
            Call(SetPartFlagBits, ACTOR_SELF, 2, 0x800000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20000, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x20000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x800000, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(SetActorSize, ACTOR_SELF, 62, -0xEE6B280)
            Call(SetPartSize, ACTOR_SELF, 1, 62, -0xEE6B280)
            Call(b_area_sbk_pokey_SetAbsoluteStatusOffsets, -15, 55, 10, 45)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 1, 0x310006)
            Call(SetActorVar, ACTOR_SELF, 2, 0x31000A)
            Call(SetActorVar, ACTOR_SELF, 3, 0x31000E)
            Call(SetActorVar, ACTOR_SELF, 4, 0x310014)
            Call(SetActorVar, ACTOR_SELF, 5, 0x310015)
            Call(SetActorVar, ACTOR_SELF, 6, 0x31001C)
            Call(SetActorVar, ACTOR_SELF, 7, 0x31001D)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_sbk_pokey_TwoPartAnims))
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x800000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x20000, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x20000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x800000, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 2)
            Call(SetActorSize, ACTOR_SELF, 44, -0xEE6B280)
            Call(SetPartSize, ACTOR_SELF, 1, 44, -0xEE6B280)
            Call(b_area_sbk_pokey_SetAbsoluteStatusOffsets, -15, 35, 10, 25)
        CaseEq(2)
            Call(SetActorVar, ACTOR_SELF, 1, 0x310007)
            Call(SetActorVar, ACTOR_SELF, 2, 0x31000B)
            Call(SetActorVar, ACTOR_SELF, 3, 0x31000F)
            Call(SetActorVar, ACTOR_SELF, 6, 0x31001E)
            Call(SetActorVar, ACTOR_SELF, 7, 0x31001F)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_sbk_pokey_OnePartAnims))
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x800000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x20000, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 5, 0x20000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 5, 0x800000, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 3)
            Call(SetActorSize, ACTOR_SELF, 26, -0xEE6B280)
            Call(SetPartSize, ACTOR_SELF, 1, 26, -0xEE6B280)
            Call(b_area_sbk_pokey_SetAbsoluteStatusOffsets, -15, 15, 10, 5)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sbk_pokey_EVS_Pokey_Hit = {
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 6, Float(1.0), Float(1.0), Float(1.0))
    Else
        Call(SetPartScale, ACTOR_SELF, 6, Float(0.400390625), Float(0.400390625), Float(1.0))
    EndIf
    ExecWait(TTYD64_sbk_pokey_EVS_DecrementSize)
    SetConst(LVar0, 1)
    Call(GetLastEvent, ACTOR_SELF, LVar1)
    Switch(LVar1)
        CaseOrEq(14)
        CaseOrEq(36)
            Call(SetAnimation, ACTOR_SELF, 6, 0x310020)
            Call(GetActorVar, ACTOR_SELF, 6, LVar1)
        EndCaseGroup
        CaseDefault
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    ChildThread
        Wait(4)
        ExecWait(b_area_sbk_pokey_EVS_HitReactionBounce)
    EndChildThread
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfNe(LVarA, 3)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
        Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
        Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(6.0))
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 30)
        Set(LVar1, 0)
        Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 10, 18, 0)
        Add(LVar0, 20)
        Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 8, 10, 0)
        Loop(20)
            Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
            Wait(1)
            Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
            Wait(1)
        EndLoop
        Call(SetPartFlagBits, ACTOR_SELF, 6, 0x20000, 1)
        Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
    Else
        Wait(30)
    EndIf
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(14)
            Call(GetActorVar, ACTOR_SELF, 7, LVar1)
            Call(SetAnimation, ACTOR_SELF, 1, LVar1)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetActorSize, ACTOR_SELF, LVar3, LVar4)
            Div(LVar3, 2)
            Add(LVar1, LVar3)
            Add(LVar2, 5)
            DivF(LVar3, Float(10.0))
            Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
        CaseEq(36)
            Call(GetActorVar, ACTOR_SELF, 7, LVar1)
            Call(SetAnimation, ACTOR_SELF, 1, LVar1)
            Wait(10)
        CaseDefault
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sbk_pokey_EVS_KnockPartAway = {
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 6, Float(1.0), Float(1.0), Float(1.0))
    Else
        Call(SetPartScale, ACTOR_SELF, 6, Float(0.400390625), Float(0.400390625), Float(1.0))
    EndIf
    ExecWait(TTYD64_sbk_pokey_EVS_DecrementSize)
    SetConst(LVar0, 1)
    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    ChildThread
        Wait(4)
        ExecWait(b_area_sbk_pokey_EVS_HitReactionBounce)
    EndChildThread
    Call(CreateHomeTargetList, 0x18004)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerID, LVar1)
    Call(GetOwnerTarget, LVar0, LVar9)
    IfNe(LVar1, LVar0)
        Call(ChooseNextTarget, 0, LVar0)
        Goto(0)
    EndIf
    Label(1)
    Add(LVarF, 1)
    Call(ChooseNextTarget, 0, LVar0)
    IfEq(LVar0, -1)
        Goto(10)
    EndIf
    Call(GetOwnerTarget, LVar0, LVar9)
    Call(GetActorFlags, LVar0, LVar1)
    IfFlag(LVar1, 0x4000)
        Goto(1)
    EndIf
    Call(GetOwnerID, LVar0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
    Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(7.0))
    Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 1)
    ChildThread
        Call(ShakeCam, 1, 0, 2, Float(1.0))
    EndChildThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(DispatchDamageEvent, LVar0, 1, 17)
    Goto(1)
    Label(10)
    Call(UseBattleCamPreset, 3)
    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
    Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(6.0))
    Call(JumpPartTo, ACTOR_SELF, 6, 296, 0, 0, 0, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 6, 0x20000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sbk_pokey_EVS_Pokey_ScareAway = {
    SetConst(LVar0, 1)
    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
    Call(UseBattleCamPreset, 2)
    Call(GetActorFlags, ACTOR_SELF, LVar9)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.0498046875))
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Set(LVarD, LVarB)
    Add(LVarD, 40)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarD, LVarC)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    Wait(20)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(FallToGoal, ACTOR_SELF, 10)
    Wait(20)
    Call(SetActorYaw, ACTOR_SELF, 180)
    Wait(5)
    Call(SetActorVar, ACTOR_SELF, 0, LVar2)
    Switch(LVar2)
        CaseEq(0)
            Set(LVar2, 96)
            Set(LVar6, 4)
        CaseEq(1)
            Set(LVar2, 72)
            Set(LVar6, 3)
        CaseEq(2)
            Set(LVar2, 48)
            Set(LVar6, 2)
        CaseDefault
            Set(LVar2, 24)
            Set(LVar6, 1)
    EndSwitch
    ChildThread
        Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
        Loop(LVar6)
            Call(PlayEffect_impl, 37, 2, LVarA, 0, LVarC, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(10)
        EndLoop
    EndChildThread
    Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar4, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
    Wait(8)
    Call(HideHealthBar, ACTOR_SELF)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(RemoveActor, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_sbk_pokey_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_sbk_pokey_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sbk_bandit_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_sbk_pokey_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Call(SetActorVar, ACTOR_SELF, 9, LVar0)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0x310004)
    Call(SetActorVar, ACTOR_SELF, 2, 0x310008)
    Call(SetActorVar, ACTOR_SELF, 3, 0x31000C)
    Call(SetActorVar, ACTOR_SELF, 4, 0x310010)
    Call(SetActorVar, ACTOR_SELF, 5, 0x310011)
    Call(SetActorVar, ACTOR_SELF, 6, 0x310018)
    Call(SetActorVar, ACTOR_SELF, 7, 0x310019)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

Battle TTYD64_sbk_Formations[] = {
    { .name = "\265\363\334",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_sbk_Formation_00,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "\265\363\334x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_sbk_Formation_01,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "\265\363\334x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_sbk_Formation_02,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "MD\215\265\363\334x4",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_sbk_Formation_03,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "\265\363\334,\334\355\311\374",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_sbk_Formation_04,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "\265\363\334x2,\334\355\311\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_sbk_Formation_05,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "\265\363\334x2,\334\355\311\374x2",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_sbk_Formation_06,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "\265\363\334,\334\355\311\374,\265\363\334",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_sbk_Formation_07,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "\265\363\334x2,\334\355\311\374,\265\363\334",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_sbk_Formation_08,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "\334\355\311\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_sbk_Formation_09,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "\334\355\311\374x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_sbk_Formation_0A,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "\334\355\311\374x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_sbk_Formation_0B,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "\334\355\311\374x4",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_sbk_Formation_0C,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "\334\355\311\374,\265\363\334",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_sbk_Formation_0D,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "\334\355\311\374x2,\265\363\334",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_sbk_Formation_0E,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "\334\355\311\374x2,\265\363\334x2",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_sbk_Formation_0F,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    { .name = "\334\355\311\374,\265\363\334,\334\355\311\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_sbk_Formation_10,
      .stage = &b_area_sbk_sbk_02,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_sbk_pokey_EVS_Pokey_SpinSmashHit = {
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        SetConst(LVar0, 1)
        Call(GetActorVar, ACTOR_SELF, 3, LVar1)
        ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    Switch(LVarA)
        CaseEq(0)
            ExecWait(TTYD64_sbk_pokey_EVS_KnockPartAway)
        CaseEq(1)
            ExecWait(TTYD64_sbk_pokey_EVS_KnockPartAway)
        CaseEq(2)
            ExecWait(TTYD64_sbk_pokey_EVS_KnockPartAway)
        CaseEq(3)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
    EndSwitch
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_sbk_pokey_ActorParts[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_sbk_pokey_FourPartAnims,
        .defenseTable = b_area_sbk_bandit_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 72 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_sbk_bandit_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 54 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_sbk_bandit_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 36 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_sbk_bandit_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 16 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_sbk_bandit_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 6,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_sbk_pokey_ThrownPartAnims,
        .defenseTable = b_area_sbk_bandit_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_sbk_pokey_StatusTable[] = {
    1,  0, 2,  0, 6,  90, 9,  0, 7,  90, 4,  90, 3,  0, 11, 0, 5,  100, 10, 90, 8, 100,
    31, 0, 32, 0, 37, 0,  34, 0, 36, 0,  35, 0,  33, 0, 38, 0, 39, 0,   41, 0,  0,
};

FormationRow TTYD64_sbk_Formation_0C[] = {
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
};

FormationRow TTYD64_sbk_Formation_0F[] = {
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
};

FormationRow TTYD64_sbk_Formation_03[] = {
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
};

FormationRow TTYD64_sbk_Formation_08[] = {
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
};

FormationRow TTYD64_sbk_Formation_06[] = {
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
};

// clang-format off
EvtScript TTYD64_sbk_bandit_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_sbk_bandit_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sbk_bandit_EVS_Dummy))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_sbk_bandit_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_sbk_Formation_0E[] = {
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
};

FormationRow TTYD64_sbk_Formation_0B[] = {
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
};

FormationRow TTYD64_sbk_Formation_10[] = {
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
};

FormationRow TTYD64_sbk_Formation_05[] = {
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
};

FormationRow TTYD64_sbk_Formation_02[] = {
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
};

FormationRow TTYD64_sbk_Formation_07[] = {
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
};

s32 TTYD64_sbk_bandit_HoldingAnims[] = {
    1,  0x320002, 7, 0x320004, 6, 0x320010, 9, 0x320002, 8, 0x320004,
    11, 0x320002, 5, 0x320004, 4, 0x320011, 3, 0x320011, 0,
};

s32 TTYD64_sbk_bandit_DefaultAnims[] = {
    1,  0x320001, 7, 0x320000, 6, 0x320010, 9, 0x320001, 8, 0x320000,
    11, 0x320001, 5, 0x320000, 4, 0x320011, 3, 0x320011, 0,
};

ActorPartBlueprint TTYD64_sbk_bandit_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 28 },
        .opacity = 255,
        .idleAnimations = TTYD64_sbk_bandit_DefaultAnims,
        .defenseTable = b_area_sbk_bandit_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -12 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 2,
        .posOffset = { 0, 30, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_sbk_bandit_CoinAnims,
        .defenseTable = b_area_sbk_bandit_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_sbk_pokey_OnePartAnims[] = {
    1, 0x310007, 7, 0x310003, 6, 0x310028, 8, 0x310003, 5, 0x310003, 4, 0x310024, 3, 0x310024, 0,
};

s32 TTYD64_sbk_pokey_FourPartAnims[] = {
    1, 0x310004, 7, 0x310000, 6, 0x310025, 8, 0x310000, 5, 0x310000, 4, 0x310021, 3, 0x310021, 0,
};

s32 TTYD64_sbk_pokey_ThreePartAnims[] = {
    1, 0x310005, 7, 0x310001, 6, 0x310026, 8, 0x310001, 5, 0x310001, 4, 0x310022, 3, 0x310022, 0,
};

s32 TTYD64_sbk_pokey_TwoPartAnims[] = {
    1, 0x310006, 7, 0x310002, 6, 0x310027, 8, 0x310002, 5, 0x310002, 4, 0x310023, 3, 0x310023, 0,
};

FormationRow TTYD64_sbk_Formation_0A[] = {
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
};

FormationRow TTYD64_sbk_Formation_0D[] = {
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
};

FormationRow TTYD64_sbk_Formation_01[] = {
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
};

FormationRow TTYD64_sbk_Formation_04[] = {
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
};

ActorBlueprint TTYD64_sbk_bandit = {
    .flags = 0x0,
    .maxHP = 5,
    .type = 0x13,
    .level = 9,
    .partCount = 2,
    .partsData = TTYD64_sbk_bandit_ActorParts,
    .initScript = &TTYD64_sbk_bandit_EVS_Init,
    .statusTable = b_area_sbk_bandit_StatusTable,
    .escapeChance = 40,
    .airLiftChance = 90,
    .hurricaneChance = 90,
    .spookChance = 90,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 1,
    .size = { 26, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 25 },
    .statusTextOffset = { 10, 25 },
};

ActorBlueprint TTYD64_sbk_pokey = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x14,
    .level = 9,
    .partCount = 6,
    .partsData = TTYD64_sbk_pokey_ActorParts,
    .initScript = &TTYD64_sbk_pokey_EVS_Init,
    .statusTable = TTYD64_sbk_pokey_StatusTable,
    .escapeChance = 70,
    .airLiftChance = 90,
    .hurricaneChance = 85,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 24, 80 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 75 },
    .statusTextOffset = { 10, 65 },
};

ActorBlueprint TTYD64_sbk_pokey_8021FED0 = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x14,
    .level = 9,
    .partCount = 6,
    .partsData = TTYD64_sbk_pokey_ActorParts,
    .initScript = &TTYD64_sbk_pokey_EVS_Init,
    .statusTable = TTYD64_sbk_pokey_StatusTable,
    .escapeChance = 70,
    .airLiftChance = 90,
    .hurricaneChance = 85,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 24, 80 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 75 },
    .statusTextOffset = { 10, 65 },
};

FormationRow TTYD64_sbk_pokey_SummonFormation[] = {
    { .actor = &TTYD64_sbk_pokey_8021FED0,
      .home = { .vec = &b_area_sbk_pokey_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_sbk_Formation_00[] = {
    { .actor = &TTYD64_sbk_pokey,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
};

FormationRow TTYD64_sbk_Formation_09[] = {
    { .actor = &TTYD64_sbk_bandit,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
};

void TTYD64_InstallBattles_sbk(void) {
    Mod_SetBattleList("TTYD64", 10, TTYD64_sbk_Formations);
}
