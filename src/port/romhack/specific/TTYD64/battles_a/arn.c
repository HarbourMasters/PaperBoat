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
#include "port/romhack/specific/TTYD64/battles_a/battles_a.h"

API_CALLABLE(ActorSpeak);
API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(EnableActorGlow);
API_CALLABLE(EnableBattleStatusBar);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EndActorSpeech);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyToGoal);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetBattleVar);
API_CALLABLE(GetCurrentPartnerID);
API_CALLABLE(GetEncounterTrigger);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetIndexFromHome);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToCurrent);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HideHealthBar);
API_CALLABLE(IdleFlyToGoal);
API_CALLABLE(IdleRunToGoal);
API_CALLABLE(JumpToGoal);
API_CALLABLE(LandJump);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(RemoveEffect);
API_CALLABLE(ResetActorSounds);
API_CALLABLE(ResetAllActorSounds);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorIdleSpeed);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorType);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetAnimationRate);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetBattleVar);
API_CALLABLE(SetDamageSource);
API_CALLABLE(SetDefenseTable);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetIdleGoal);
API_CALLABLE(SetPartDispOffset);
API_CALLABLE(SetPartEventBits);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartFlags);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartRotation);
API_CALLABLE(SetPartTargetFlagBits);
API_CALLABLE(SetProjectileTargetOffset);
API_CALLABLE(SetStatusTable);
API_CALLABLE(SetTargetActor);
API_CALLABLE(SetTargetOffset);
API_CALLABLE(ShakeCam);
API_CALLABLE(StartRumble);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
API_CALLABLE(b_area_arn_hyper_cleft_SetSpinSmashable);
API_CALLABLE(b_area_arn_hyper_cleft_StartRumbleWithParams);
API_CALLABLE(b_area_arn_hyper_goomba_CalculateArcsinDeg);
API_CALLABLE(b_area_arn_hyper_goomba_StartRumbleWithParams);
API_CALLABLE(b_area_arn_hyper_paragoomba_CalculateArcsinDeg);
API_CALLABLE(b_area_arn_hyper_paragoomba_StartRumbleWithParams);
extern Stage b_area_arn_arn_01;
extern Stage b_area_arn_arn_02;
extern Stage b_area_arn_arn_03;
extern Stage b_area_arn_arn_04;
extern Stage b_area_arn_arn_05;
extern EvtScript b_area_arn_arn_05_EVS_PostBattle;
extern EvtScript b_area_arn_arn_05_EVS_PreBattle;
extern Stage b_area_arn_arn_06;
extern EvtScript b_area_arn_hyper_cleft_EVS_HandlePhase;
extern EvtScript b_area_arn_hyper_cleft_EVS_Idle;
extern s32 b_area_arn_hyper_cleft_ToppledDefenseTable[];
extern s32 b_area_arn_hyper_cleft_UprightDefenseTable[];
extern EvtScript b_area_arn_hyper_goomba_EVS_HandlePhase;
extern s32 b_area_arn_hyper_paragoomba_DownedDefense[];
extern EvtScript b_area_arn_hyper_paragoomba_EVS_Flying_HandlePhase;
extern EvtScript b_area_arn_hyper_paragoomba_EVS_HandlePhase;
extern EvtScript b_area_arn_hyper_paragoomba_EVS_ReturnHome;
extern s32 b_area_arn_hyper_paragoomba_FlyingDefense[];
extern s32 b_area_arn_hyper_paragoomba_LeftWingAnims[];
extern s32 b_area_arn_hyper_paragoomba_RightWingAnims[];
extern s32 b_area_arn_tubba_blubba_DefenseTable[];
extern EvtScript b_area_arn_tubba_blubba_EVS_DummyCheck;
extern EvtScript b_area_arn_tubba_blubba_EVS_HandleEvent;
extern EvtScript b_area_arn_tubba_blubba_EVS_Idle;
extern EvtScript b_area_arn_tubba_blubba_EVS_PlayFootstepQuaking;
extern EvtScript b_area_arn_tubba_blubba_EVS_ReturnHome;
extern s32 b_area_arn_tubba_blubba_StatusTable[];
extern s32 b_area_arn_tubbas_heart_DefenseTable[];
extern EvtScript b_area_arn_tubbas_heart_EVS_FleeFromBattle;
extern EvtScript b_area_arn_tubbas_heart_EVS_Idle;
extern EvtScript b_area_arn_tubbas_heart_EVS_SelectAnimation;
extern s32 b_area_arn_tubbas_heart_StatusTable[];
extern Vec3i b_area_arn_vector3D_802280C0;
extern Vec3i b_area_arn_vector3D_802280E8;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_HandleEvent;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Attack_ChargedDive;
extern EvtScript TTYD64_arn_tubba_blubba_EVS_Attack_BodySlam;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Attack_Headbonk;
extern EvtScript TTYD64_arn_hyper_goomba_EVS_Attack_Headbonk;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_Move_Charge;
extern EvtScript TTYD64_arn_hyper_goomba_EVS_Move_Charge;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Downed_Move_Charge;
extern EvtScript TTYD64_arn_hyper_goomba_EVS_HandleEvent;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Downed_HandleEvent;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_Attack_Tackle;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Attack_SkyDive;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_HandleEvent;
extern EvtScript TTYD64_arn_tubbas_heart_EVS_Attack_DarkSwarm;
extern EvtScript TTYD64_arn_tubbas_heart_EVS_Attack_Leap;
extern EvtScript TTYD64_arn_tubba_blubba_EVS_Attack_SlamFist;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_KnockDown;
extern EvtScript TTYD64_arn_tubbas_heart_EVS_TakeTurn;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_TryGettingUp;
extern EvtScript TTYD64_arn_tubbas_heart_EVS_HandleEvent;
extern EvtScript TTYD64_arn_tubbas_heart_EVS_Move_Charge;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_FlipOver;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Downed_Idle;
extern EvtScript TTYD64_arn_hyper_goomba_EVS_Idle;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Idle;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_TakeTurn;
extern EvtScript TTYD64_arn_hyper_goomba_EVS_TakeTurn;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Downed_TakeTurn;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Flying_TakeTurn;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_KnockDown_Init;
extern EvtScript TTYD64_arn_tubbas_heart_EVS_Init;
extern EvtScript TTYD64_arn_tubbas_heart_EVS_ReturnHome;
extern EvtScript TTYD64_arn_tubba_blubba_EVS_TakeTurn;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_Init;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Init;
extern EvtScript TTYD64_arn_hyper_paragoomba_EVS_Init_80227010;
extern EvtScript TTYD64_arn_tubba_blubba_EVS_Init;
extern Stage TTYD64_arn_Stage_80228030;
extern ActorBlueprint TTYD64_arn_tubbas_heart;
extern ActorBlueprint TTYD64_arn_hyper_cleft;
extern ActorBlueprint TTYD64_arn_tubba_blubba;
extern ActorBlueprint TTYD64_arn_hyper_goomba;
extern ActorBlueprint TTYD64_arn_hyper_paragoomba;
extern Battle TTYD64_arn_Formations[];
extern s32 TTYD64_arn_hyper_paragoomba_DownedStatusTable[];
extern s32 TTYD64_arn_hyper_cleft_StatusTable[];
extern s32 TTYD64_arn_hyper_paragoomba_FlyingStatusTable[];
extern s32 TTYD64_arn_hyper_goomba_StatusTable[];
extern ActorPartBlueprint TTYD64_arn_hyper_paragoomba_ActorParts[];
extern FormationRow TTYD64_arn_Formation_0E[];
extern FormationRow TTYD64_arn_Formation_04[];
extern FormationRow TTYD64_arn_Formation_05[];
extern FormationRow TTYD64_arn_Formation_09[];
extern s32 TTYD64_arn_tubbas_heart_ChargedAnims[];
extern s32 TTYD64_arn_tubbas_heart_DefaultAnims[];
extern FormationRow TTYD64_arn_Formation_0D[];
extern FormationRow TTYD64_arn_Formation_0C[];
extern FormationRow TTYD64_arn_Formation_02[];
extern FormationRow TTYD64_arn_Formation_03[];
extern FormationRow TTYD64_arn_Formation_08[];
extern s32 TTYD64_arn_tubba_blubba_DefaultAnims[];
extern s32 TTYD64_arn_hyper_paragoomba_DownedChargedAnims[];
extern s32 TTYD64_arn_hyper_goomba_ShuffleAnims[];
extern s32 TTYD64_arn_hyper_goomba_HyperAnims[];
extern s32 TTYD64_arn_hyper_cleft_HyperAnims[];
extern s32 TTYD64_arn_hyper_paragoomba_DownedAnims[];
extern s32 TTYD64_arn_hyper_cleft_ToppledAnims[];
extern s32 TTYD64_arn_hyper_paragoomba_DownedAnims_80227C08[];
extern s32 TTYD64_arn_hyper_paragoomba_DownedShuffleAnims[];
extern s32 TTYD64_arn_hyper_paragoomba_ChargedFlyingAnims[];
extern s32 TTYD64_arn_hyper_cleft_UprightAnims[];
extern s32 TTYD64_arn_hyper_paragoomba_FlyingAnims[];
extern s32 TTYD64_arn_hyper_paragoomba_FlyingShuffleAnims[];
extern ActorPartBlueprint TTYD64_arn_tubbas_heart_ActorParts[];
extern StageListRow TTYD64_arn_Stages[];
extern FormationRow TTYD64_arn_Formation_0B[];
extern FormationRow TTYD64_arn_Formation_01[];
extern FormationRow TTYD64_arn_Formation_07[];
extern ActorPartBlueprint TTYD64_arn_tubba_blubba_ActorParts[];
extern ActorPartBlueprint TTYD64_arn_hyper_goomba_ActorParts[];
extern ActorPartBlueprint TTYD64_arn_hyper_cleft_ActorParts[];
extern FormationRow TTYD64_arn_Formation_0A[];
extern FormationRow TTYD64_arn_Formation_0F[];
extern FormationRow TTYD64_arn_Formation_10[];
extern FormationRow TTYD64_arn_Formation_00[];
extern FormationRow TTYD64_arn_Formation_06[];
extern s32 TTYD64_arn_FgModels_80228760[];

// clang-format off
EvtScript TTYD64_arn_hyper_cleft_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Call(GetLastElement, LVar0)
            Switch(LVar0)
                CaseFlag(512)
                    ExecWait(TTYD64_arn_hyper_cleft_EVS_FlipOver)
                CaseDefault
                    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
                    IfEq(LVar0, 1)
                        SetConst(LVar1, 0x300109)
                    Else
                        SetConst(LVar1, 0x300108)
                    EndIf
                    SetConst(LVar0, 1)
                    ExecWait(Ref(EVS_Enemy_Hit))
            EndSwitch
        EndCaseGroup
        CaseEq(14)
            Call(GetLastElement, LVar0)
            Switch(LVar0)
                CaseFlag(512)
                    ExecWait(TTYD64_arn_hyper_cleft_EVS_FlipOver)
                CaseDefault
                    Call(SetPartEventBits, ACTOR_SELF, 1, 512, 1)
                    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
                    IfEq(LVar0, 1)
                        SetConst(LVar0, 1)
                        SetConst(LVar1, 0x300109)
                        SetConst(LVar2, -1)
                        ExecWait(Ref(EVS_Enemy_BurnHit))
                    Else
                        SetConst(LVar0, 1)
                        SetConst(LVar1, 0x300108)
                        SetConst(LVar2, -1)
                        ExecWait(Ref(EVS_Enemy_BurnHit))
                    EndIf
                    Call(SetPartEventBits, ACTOR_SELF, 1, 512, 0)
            EndSwitch
        CaseEq(36)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300109)
                SetConst(LVar2, -1)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300109)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300108)
                SetConst(LVar2, -1)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300108)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(11)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar1, 0x300109)
            Else
                SetConst(LVar1, 0x300108)
            EndIf
            SetConst(LVar0, 1)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300109)
                ExecWait(Ref(EVS_Enemy_SpinSmashHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300109)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300108)
                ExecWait(Ref(EVS_Enemy_SpinSmashHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300108)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(47)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_cleft_UprightAnims))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x300108)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x300108)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x300107)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_cleft_UprightAnims))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x300108)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x300108)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 2)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(EnableActorGlow, ACTOR_SELF, 0)
                Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
                Call(SetActorVar, ACTOR_SELF, 0, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_cleft_UprightAnims))
            EndIf
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar1, 0x300103)
            Else
                SetConst(LVar1, 0x300102)
            EndIf
            SetConst(LVar0, 1)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(27)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x300118)
            EndIf
            Wait(10)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                Add(LVar0, -3)
                Add(LVar1, 10)
            Else
                Add(LVar0, -8)
                Add(LVar1, 27)
            EndIf
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(20)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar1, 0x300103)
            Else
                SetConst(LVar1, 0x300102)
            EndIf
            SetConst(LVar0, 1)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300109)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300109)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300108)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300108)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300102)
                ExecWait(Ref(EVS_Enemy_Recover))
            EndIf
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300103)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300107)
                SetConst(LVar2, 0x300108)
                ExecWait(Ref(EVS_Enemy_ScareAway))
                Return
            EndIf
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x30010F)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x30010F)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300108)
            EndIf
            ExecWait(Ref(EVS_Enemy_BlowAway))
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
EvtScript TTYD64_arn_hyper_paragoomba_EVS_Attack_ChargedDive = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Call(UseBattleCamPreset, 14)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 20)
        Wait(20)
        Call(PlaySoundAtActor, ACTOR_SELF, 728)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 10)
        Call(PlayEffect_impl, 107, 6, LVar0, LVar1, LVar2, Float(1.0), 45, 0, 0, 0, 0, 0, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 2, 0x280202)
        Wait(30)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 20)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 20, 0, 0, 0)
        Call(SetActorVar, ACTOR_SELF, 0, 1)
        Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_arn_hyper_paragoomba_ChargedFlyingAnims))
        Call(TTYD64_AddCharge, ACTOR_SELF, 6)
        Call(SetPartEventBits, ACTOR_SELF, 2, 0x400000, 1)
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Return
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(MoveBattleCamOver, 30)
    Loop(20)
        Call(SetActorDispOffset, ACTOR_SELF, 1, 0, 0)
        Wait(1)
        Call(SetActorDispOffset, ACTOR_SELF, -1, 0, 0)
        Wait(1)
    EndLoop
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8416)
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 705)
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, -60)
            Thread
                Set(LVar0, -60)
                Loop(60)
                    Add(LVar0, 19)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 15, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.009765625))
            Call(SetActorSpeed, ACTOR_SELF, Float(15.0))
            Call(JumpToGoal, ACTOR_SELF, 0, 0, 0, 0)
            Call(UseBattleCamPreset, 1)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -60, 0, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2998046875))
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(AddGoalPos, ACTOR_SELF, -200, 0, 0)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 2, 0x400000, 0)
            Thread
                Set(LVar0, 0)
                Loop(30)
                    Add(LVar0, 24)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(SetActorPos, ACTOR_SELF, 300, 0, 0)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(AddGoalPos, ACTOR_SELF, 30, 0, 0)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 2, 0x280204)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 11)
            Call(SetAnimation, ACTOR_SELF, 2, 0x280201)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_arn_hyper_paragoomba_FlyingAnims))
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, -70)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.009765625))
    Call(SetActorSpeed, ACTOR_SELF, Float(15.0))
    Call(JumpToGoal, ACTOR_SELF, 0, 0, 0, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                Set(LVar0, -70)
                Loop(60)
                    Add(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Set(LVar1, 0)
            Sub(LVar0, 70)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 0, 0)
            Sub(LVar0, 60)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 0, 0)
            Wait(20)
            Call(YieldTurn)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 2, 0x400000, 0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(SetAnimation, ACTOR_SELF, 2, 0x280204)
            ExecWait(b_area_arn_hyper_paragoomba_EVS_ReturnHome)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_arn_hyper_paragoomba_FlyingAnims))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_tubba_blubba_EVS_Attack_BodySlam = {
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamDist, 150)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Set(LVar1, 0x6B0006)
    ExecWait(b_area_arn_tubba_blubba_EVS_DummyCheck)
    Call(SetAnimation, ACTOR_SELF, 1, LVar1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 70, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6B000A)
    Wait(8)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6B000B)
    Call(SetActorSounds, ACTOR_SELF, 2, 999, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Wait(12)
                Call(SetAnimation, ACTOR_SELF, 1, 0x6B000C)
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
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Wait(8)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6B000E)
            Wait(4)
            ExecWait(b_area_arn_tubba_blubba_EVS_ReturnHome)
            Return
        EndCaseGroup
        CaseDefault
            Thread
                Wait(9)
                Call(SetAnimation, ACTOR_SELF, 1, 0x6B000C)
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
    EndSwitch
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar5)
    IfNotFlag(LVar5, 0x80000)
        Call(SetDamageSource, 24)
        Call(PlaySoundAtActor, ACTOR_SELF, 8426)
    EndIf
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0, 0, 6, 32)
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamDist, 200)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(MoveBattleCamOver, 30)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(GetStatusFlags, ACTOR_SELF, LVar5)
            IfFlag(LVar5, 0x80000)
                Goto(1)
            EndIf
            Call(GetBattleFlags, LVar0)
            IfNotFlag(LVar0, (-0x7FFFFFFF - 1))
                Call(GetOwnerTarget, LVar3, 0)
                Call(GetStatusFlags, LVar3, LVar0)
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
            Call(YieldTurn)
            ExecWait(b_area_arn_tubba_blubba_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_paragoomba_EVS_Attack_Headbonk = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260203)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260204)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 10)
            Set(LVar1, 10)
            Add(LVar2, 3)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_arn_hyper_paragoomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260204)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260208)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 5, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 7, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260205)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260204)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Thread
                Wait(4)
                Set(LVar0, 180)
                Loop(4)
                    Sub(LVar0, 45)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetAnimation, ACTOR_SELF, 1, 0x260204)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260207)
            Wait(5)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_arn_hyper_paragoomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260204)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x26020B)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Wait(1)
    EndSwitch
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(1)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
            Wait(3)
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260203)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_goomba_EVS_Attack_Headbonk = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260203)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260204)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 10)
            Set(LVar1, 10)
            Add(LVar2, 3)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_arn_hyper_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260204)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260208)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 5, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 7, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260205)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260204)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Thread
                Wait(4)
                Set(LVar0, 180)
                Loop(4)
                    Sub(LVar0, 45)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetAnimation, ACTOR_SELF, 1, 0x260204)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260207)
            Wait(5)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_arn_hyper_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260204)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x26020B)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Wait(1)
    EndSwitch
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(1)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
            Wait(3)
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260203)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_cleft_EVS_Move_Charge = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Call(UseBattleCamPreset, 14)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 20)
        Wait(20)
        Call(PlaySoundAtActor, ACTOR_SELF, 728)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 10)
        Call(PlayEffect_impl, 107, 6, LVar0, LVar1, LVar2, Float(1.0), 45, 0, 0, 0, 0, 0, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x300104)
        Wait(30)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 20)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
        Call(b_area_arn_hyper_cleft_StartRumbleWithParams, 200, 10)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(1.5))
        EndThread
        Call(PlaySoundAtActor, ACTOR_SELF, 729)
        Call(PlayEffect_impl, 6, 4, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(1.0))
        EndThread
        Call(SetActorVar, ACTOR_SELF, 0, 2)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_cleft_HyperAnims))
        Call(TTYD64_AddCharge, ACTOR_SELF, 5)
        Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 1)
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Return
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(MoveBattleCamOver, 30)
    Loop(20)
        Call(SetActorDispOffset, ACTOR_SELF, 1, 0, 0)
        Wait(1)
        Call(SetActorDispOffset, ACTOR_SELF, -1, 0, 0)
        Wait(1)
    EndLoop
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 730)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 3, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Loop(0)
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Add(LVar0, 30)
                    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
                    IfGt(LVar0, LVar3)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                Call(UseBattleCamPreset, 1)
                IfEq(LVarA, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
                Wait(15)
                Call(UseBattleCamPreset, 2)
            EndThread
            Thread
                Loop(30)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(PlayEffect_impl, 7, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                    Wait(1)
                EndLoop
            EndThread
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 15, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300111)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -200, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(12.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Wait(15)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorPos, ACTOR_SELF, 300, 0, 0)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300107)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300102)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_cleft_UprightAnims))
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Loop(25)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 7, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(1)
        EndLoop
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x300111)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(12.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                Set(LVar0, 0)
                Loop(60)
                    Add(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 30, 0, 1, 0)
            Sub(LVar0, 40)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Wait(20)
            Call(YieldTurn)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300107)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300102)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_cleft_UprightAnims))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_goomba_EVS_Move_Charge = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Call(UseBattleCamPreset, 14)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 20)
        Wait(20)
        Call(PlaySoundAtActor, ACTOR_SELF, 728)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 10)
        Call(PlayEffect_impl, 107, 6, LVar0, LVar1, LVar2, Float(1.0), 45, 0, 0, 0, 0, 0, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x260203)
        Wait(30)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 20)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
        Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 8413)
        Call(b_area_arn_hyper_goomba_StartRumbleWithParams, 128, 10)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(0.5))
        EndThread
        Call(SetActorVar, ACTOR_SELF, 0, 1)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_goomba_HyperAnims))
        Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
        Call(TTYD64_AddCharge, ACTOR_SELF, 6)
        Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 1)
        Wait(2)
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Return
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Loop(20)
        Call(SetActorDispOffset, ACTOR_SELF, 1, 0, 0)
        Wait(1)
        Call(SetActorDispOffset, ACTOR_SELF, -1, 0, 0)
        Wait(1)
    EndLoop
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Loop(0)
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Add(LVar0, 30)
                    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
                    IfGt(LVar0, LVar3)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                Call(UseBattleCamPreset, 1)
                IfEq(LVarA, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
                Wait(15)
                Call(UseBattleCamPreset, 2)
            EndThread
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 15, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 80)
            Call(SetActorSounds, ACTOR_SELF, 2, 271, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -200, 0, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.009765625))
            Call(SetActorSpeed, ACTOR_SELF, Float(15.0))
            Call(JumpToGoal, ACTOR_SELF, 0, 0, 1, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorPos, ACTOR_SELF, LVar0, 0, LVar2)
            Wait(20)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(YieldTurn)
            Call(SetActorPos, ACTOR_SELF, 300, 0, 0)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260203)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedAnims_80227C08))
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorSounds, ACTOR_SELF, 2, 271, 0)
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 80)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.009765625))
    Call(SetActorSpeed, ACTOR_SELF, Float(15.0))
    Call(JumpToGoal, ACTOR_SELF, 0, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
                Set(LVar0, 80)
                Loop(60)
                    Add(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(UseBattleCamPreset, 2)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Set(LVar1, 0)
            Sub(LVar0, 50)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 30, 0, 1, 0)
            Sub(LVar0, 40)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Wait(10)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260203)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedAnims_80227C08))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_paragoomba_EVS_Downed_Move_Charge = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Call(UseBattleCamPreset, 14)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 20)
        Wait(20)
        Call(PlaySoundAtActor, ACTOR_SELF, 728)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 10)
        Call(PlayEffect_impl, 107, 6, LVar0, LVar1, LVar2, Float(1.0), 45, 0, 0, 0, 0, 0, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x260203)
        Wait(30)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 20)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
        Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 8413)
        Call(b_area_arn_hyper_paragoomba_StartRumbleWithParams, 128, 10)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(0.5))
        EndThread
        Call(SetActorVar, ACTOR_SELF, 0, 1)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedChargedAnims))
        Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
        Call(TTYD64_AddCharge, ACTOR_SELF, 6)
        Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 1)
        Wait(2)
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Return
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Loop(20)
        Call(SetActorDispOffset, ACTOR_SELF, 1, 0, 0)
        Wait(1)
        Call(SetActorDispOffset, ACTOR_SELF, -1, 0, 0)
        Wait(1)
    EndLoop
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Loop(0)
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Add(LVar0, 30)
                    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
                    IfGt(LVar0, LVar3)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                Call(UseBattleCamPreset, 1)
                IfEq(LVarA, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
                Wait(15)
                Call(UseBattleCamPreset, 2)
            EndThread
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 15, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 80)
            Call(SetActorSounds, ACTOR_SELF, 2, 271, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -200, 0, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.009765625))
            Call(SetActorSpeed, ACTOR_SELF, Float(15.0))
            Call(JumpToGoal, ACTOR_SELF, 0, 0, 1, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorPos, ACTOR_SELF, LVar0, 0, LVar2)
            Wait(20)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(YieldTurn)
            Call(SetActorPos, ACTOR_SELF, 300, 0, 0)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260203)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedAnims))
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorSounds, ACTOR_SELF, 2, 271, 0)
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 80)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.009765625))
    Call(SetActorSpeed, ACTOR_SELF, Float(15.0))
    Call(JumpToGoal, ACTOR_SELF, 0, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
                Set(LVar0, 80)
                Loop(60)
                    Add(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(UseBattleCamPreset, 2)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Set(LVar1, 0)
            Sub(LVar0, 50)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 30, 0, 1, 0)
            Sub(LVar0, 40)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Wait(10)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260203)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedAnims))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_goomba_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260205)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260209)
            SetConst(LVar2, 0x26020A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260209)
            SetConst(LVar2, 0x26020A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26020A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260205)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260205)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260206)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedAnims_80227C08))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26020E)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260205)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260207)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedAnims_80227C08))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26020E)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260206)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(EnableActorGlow, ACTOR_SELF, 0)
                Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
                Call(SetActorVar, ACTOR_SELF, 0, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedAnims_80227C08))
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260201)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260201)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260205)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260206)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260203)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260201)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260203)
            SetConst(LVar2, 0x260205)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260203)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260205)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_paragoomba_EVS_Downed_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260205)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260209)
            SetConst(LVar2, 0x26020A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260209)
            SetConst(LVar2, 0x26020A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26020A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260205)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260205)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260206)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedAnims))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26020E)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260205)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260207)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedAnims))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26020E)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260206)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(EnableActorGlow, ACTOR_SELF, 0)
                Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
                Call(SetActorVar, ACTOR_SELF, 0, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedAnims))
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260201)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260201)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260205)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260206)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260203)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260201)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260203)
            SetConst(LVar2, 0x260205)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260203)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260205)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_cleft_EVS_Attack_Tackle = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(MoveBattleCamOver, 30)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(10)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(5)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x300110)
    Wait(10)
    Call(GetOwnerTarget, LVar3, 0)
    Call(SetTargetActor, ACTOR_SELF, LVar3)
    Call(SetAnimation, ACTOR_SELF, 1, 0x300111)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, -5)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x300100)
    Wait(8)
    Call(PlaySoundAtActor, ACTOR_SELF, 8401)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 3, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            IfEq(LVarA, 5)
                Thread
                    Wait(10)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndThread
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x300111)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 100)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 45)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300108)
            Wait(15)
            Wait(8)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300107)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300102)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x300111)
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 3, 32)
    Call(SetAnimation, ACTOR_SELF, 1, 0x300102)
    Call(UseBattleCamPreset, 2)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 15)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.400390625))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300102)
            Wait(5)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300107)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300102)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_paragoomba_EVS_Attack_SkyDive = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x280204)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(UseBattleCamPreset, 66)
            Call(SetBattleCamDist, 300)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(SetBattleCamTargetingModes, -1, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8416)
            Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280205)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 705)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Sub(LVar0, 80)
            Set(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280205)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
            Thread
                Loop(4)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8415)
                    Wait(4)
                EndLoop
            EndThread
            Call(SetAnimation, ACTOR_SELF, 2, 0x280202)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Call(SetAnimationRate, ACTOR_SELF, 2, Float(3.0))
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(10)
            Call(SetAnimationRate, ACTOR_SELF, 2, Float(1.0))
            Call(UseBattleCamPreset, 2)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 2, 0x280204)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(b_area_arn_hyper_paragoomba_EVS_ReturnHome)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseDefault
            Wait(10)
            Call(UseBattleCamPreset, 66)
            Call(SetBattleCamDist, 300)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(SetBattleCamTargetingModes, -1, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8416)
            Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280205)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 705)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280205)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    EndSwitch
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280204)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Wait(5)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 2, 0x280204)
            ExecWait(b_area_arn_hyper_paragoomba_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_paragoomba_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280206)
            ExecWait(Ref(EVS_Enemy_Hit))
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(GetEncounterTrigger, LVar0)
                IfEq(LVar0, 4)
                    ExecWait(TTYD64_arn_hyper_paragoomba_EVS_KnockDown)
                EndIf
            EndIf
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28020D)
            SetConst(LVar2, 0x28020E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28020D)
            SetConst(LVar2, 0x28020E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28020E)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(12)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280206)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_arn_hyper_paragoomba_EVS_KnockDown)
        CaseEq(15)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28020D)
            SetConst(LVar2, 0x28020E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_arn_hyper_paragoomba_EVS_KnockDown)
        CaseEq(47)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 2, 0x400000, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_arn_hyper_paragoomba_FlyingAnims))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28020F)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280206)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(SetAnimation, ACTOR_SELF, 2, 0x28020C)
            ExecWait(b_area_arn_hyper_paragoomba_EVS_ReturnHome)
        CaseEq(38)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetPartEventBits, ACTOR_SELF, 2, 0x400000, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_arn_hyper_paragoomba_FlyingAnims))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28020F)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280207)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(EnableActorGlow, ACTOR_SELF, 0)
                Call(SetPartEventBits, ACTOR_SELF, 2, 0x400000, 0)
                Call(SetActorVar, ACTOR_SELF, 0, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_arn_hyper_paragoomba_FlyingAnims))
            EndIf
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280201)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280201)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280206)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280207)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            Call(SetAnimation, ACTOR_SELF, 2, 0x280204)
            ExecWait(b_area_arn_hyper_paragoomba_EVS_ReturnHome)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280201)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280204)
            SetConst(LVar2, 0x280206)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280204)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280206)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_tubbas_heart_EVS_Attack_DarkSwarm = {
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(SetTargetActor, ACTOR_SELF, 256)
    Else
        Call(SetTargetActor, ACTOR_SELF, 0)
    EndIf
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, 85, 50, 0)
    Call(SetBattleCamDist, 280)
    Call(SetBattleCamOffsetY, 0)
    Call(MoveBattleCamOver, 20)
    Wait(20)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6C000C)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar1, 16)
    Else
        Add(LVar1, 6)
    EndIf
    Call(PlayEffect_impl, 19, 0, LVar0, LVar1, LVar2, Float(1.0), 45, 0, 0, 0, 0, 0, 0, 0)
    Wait(60)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6C000B)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 18, 0, 1, 0)
    EndThread
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Sub(LVar0, 1)
    Call(SetActorVar, ACTOR_SELF, 1, LVar0)
    IfEq(LVar0, 0)
        Call(EnableActorGlow, ACTOR_SELF, 0)
        Call(GetActorVar, ACTOR_SELF, 4, LVar0)
        Call(RemoveEffect, LVar0)
        Call(SetActorVar, ACTOR_SELF, 4, 0)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_tubbas_heart_DefaultAnims))
    EndIf
    Call(GetOwnerTarget, LVar3, 0)
    Call(PlaySound, 8441)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Add(LVar1, 5)
            Call(PlayEffect_impl, 102, 1, LVar0, LVar1, LVar2, Float(1.0), 200, 0, 0, 0, 0, 0, 0, 0)
            Wait(145)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            Else
            EndIf
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 15, 0)
            Return
        EndCaseGroup
    EndSwitch
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Add(LVar1, 5)
    Call(PlayEffect_impl, 102, 0, LVar0, LVar1, LVar2, Float(1.0), 200, 0, 0, 0, 0, 0, 0, 0)
    Thread
        Wait(160)
        Call(PlaySound, 8444)
    EndThread
    Call(GetOwnerTarget, LVar3, 0)
    Call(UseIdleAnimation, LVar3, 0)
    IfEq(LVar3, 0)
        Call(SetAnimation, 0, 0, 0x1002B)
    EndIf
    Wait(30)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 300)
    Call(SetBattleCamOffsetY, 35)
    Call(MoveBattleCamOver, 50)
    Wait(56)
    Call(PlaySoundAtActor, LVar3, 987)
    Switch(LVar3)
        CaseEq(0)
            Call(UseIdleAnimation, 0, 0)
            Call(SetAnimation, 0, 0, 0x3000C)
        CaseEq(256)
            Call(UseIdleAnimation, 256, 0)
            Set(LVar0, 4)
            Exec(TTYD64_SetPartnerAnimation_Battle)
    EndSwitch
    Wait(37)
    Call(PlaySoundAtActor, LVar3, 987)
    Wait(22)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Call(PlaySoundAtActor, LVar3, 8443)
    Call(UseIdleAnimation, LVar3, 1)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 6, 32)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_tubbas_heart_EVS_Attack_Leap = {
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6C0003)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 45)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 40)
    Set(LVar1, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetAnimation, ACTOR_SELF, 1, 0x6C0001)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6C0016)
    Wait(5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6C0015)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Sub(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x6C0003)
            ExecWait(TTYD64_arn_tubbas_heart_EVS_ReturnHome)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
    EndSwitch
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 6, 32)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(UseBattleCamPreset, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6C0001)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(1)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Add(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Wait(8)
            IfEq(LVarF, 10)
                Return
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6C0003)
            ExecWait(TTYD64_arn_tubbas_heart_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_tubba_blubba_EVS_Attack_SlamFist = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamDist, 150)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Set(LVar1, 0x6B0006)
    ExecWait(b_area_arn_tubba_blubba_EVS_DummyCheck)
    Call(SetAnimation, ACTOR_SELF, 1, LVar1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar5)
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
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 37, 0, LVar0, 0, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(30)
            Set(LVar1, 0x6B0001)
            ExecWait(b_area_arn_tubba_blubba_EVS_DummyCheck)
            Call(SetAnimation, ACTOR_SELF, 1, LVar1)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            ExecWait(b_area_arn_tubba_blubba_EVS_ReturnHome)
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
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0, 0, 4, 32)
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamDist, 200)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(MoveBattleCamOver, 30)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(30)
            Set(LVar1, 0x6B0001)
            ExecWait(b_area_arn_tubba_blubba_EVS_DummyCheck)
            Call(SetAnimation, ACTOR_SELF, 1, LVar1)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(YieldTurn)
            ExecWait(b_area_arn_tubba_blubba_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_paragoomba_EVS_KnockDown = {
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetPartFlags, ACTOR_SELF, 2, 0x20005)
    Call(SetPartFlags, ACTOR_SELF, 3, 0x120004)
    Call(SetPartFlags, ACTOR_SELF, 4, 0x120004)
    Call(SetPartFlags, ACTOR_SELF, 1, 0x800004)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(SetPartDispOffset, ACTOR_SELF, 3, -9, 7, -2)
    Call(SetPartPos, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
    Call(SetPartDispOffset, ACTOR_SELF, 4, 11, 7, -2)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    IfEq(LVar0, 15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x26020A)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x260205)
    EndIf
    Call(SetActorSounds, ACTOR_SELF, 2, 769, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(b_area_arn_hyper_paragoomba_StartRumbleWithParams, 100, 10)
    Thread
        Call(ShakeCam, 1, 0, 5, Float(0.2998046875))
    EndThread
    Call(ResetActorSounds, ACTOR_SELF, 2)
    Call(GetLastEvent, ACTOR_SELF, LVar3)
    IfEq(LVar3, 15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x260205)
        Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Add(LVar4, 10)
        Add(LVar5, 5)
        Call(PlayEffect_impl, 39, 0, LVar3, LVar4, LVar5, Float(1.0), 10, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Loop(10)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
        Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 1)
        Wait(1)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
        Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 0)
        Wait(1)
    EndLoop
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 1)
    Call(GetIndexFromHome, ACTOR_SELF, LVar0)
    Mod(LVar0, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVar0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260201)
    Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_arn_hyper_paragoomba_DownedStatusTable))
    Call(SetActorType, ACTOR_SELF, 27)
    ExecWait(TTYD64_arn_hyper_paragoomba_EVS_KnockDown_Init)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_tubbas_heart_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    IfNe(LVar0, 6)
        Call(GetActorVar, ACTOR_SELF, 2, LVar0)
        IfNotFlag(LVar0, 1)
            Call(GetCurrentPartnerID, LVar0)
            IfEq(LVar0, 9)
                Call(EnableBattleStatusBar, 0)
                BitwiseOrConst(LVar0, 3)
                Call(SetActorVar, ACTOR_SELF, 2, LVar0)
                Call(UseBattleCamPreset, 14)
                Call(BattleCamTargetActor, ACTOR_SELF)
                Call(MoveBattleCamOver, 40)
                Wait(40)
                Call(ActorSpeak, 0xE00C3, ACTOR_SELF, 1, 0x6C000B, 0x6C0001)
                Call(UseBattleCamPreset, 14)
                Call(BattleCamTargetActor, 256)
                Call(MoveBattleCamOver, 25)
                Wait(25)
                Call(UseIdleAnimation, 256, 0)
                Call(SetAnimation, 256, 1, 0xD0004)
                Call(ActorSpeak, 0xE00C4, 256, 1, 0xD0004, 0xD0001)
                Call(SetAnimation, 256, 1, 0xD000F)
                Call(EndActorSpeech, 256, 1, -1, -1)
                Call(UseBattleCamPreset, 2)
                Call(UseIdleAnimation, 256, 1)
                Call(MoveBattleCamOver, 30)
                Call(GetActorVar, ACTOR_SELF, 0, LVar0)
                IfEq(LVar0, 0)
                    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
                    IfNe(LVar0, 0)
                        Call(EnableBattleStatusBar, 1)
                    EndIf
                Else
                    Call(EnableBattleStatusBar, 1)
                EndIf
            EndIf
        EndIf
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            IfEq(LVar0, 0)
                Call(SetActorVar, ACTOR_SELF, 3, 1)
                Call(UseBattleCamPreset, 14)
                Call(BattleCamTargetActor, ACTOR_SELF)
                Call(MoveBattleCamOver, 40)
                Wait(40)
                Call(ActorSpeak, 0xE00C5, ACTOR_SELF, 1, 0x6C000B, 0x6C0001)
            EndIf
            ExecWait(TTYD64_arn_tubbas_heart_EVS_Move_Charge)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfFlag(LVar0, 2)
                Call(EnableBattleStatusBar, 1)
            EndIf
        CaseEq(1)
            ExecWait(TTYD64_arn_tubbas_heart_EVS_Attack_DarkSwarm)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            IfEq(LVar0, 0)
                Call(GetActorVar, ACTOR_SELF, 5, LVar1)
                Add(LVar1, 1)
                Call(SetActorVar, ACTOR_SELF, 5, LVar1)
                IfGe(LVar1, 2)
                    Call(SetActorVar, ACTOR_SELF, 0, 2)
                Else
                    Call(SetActorVar, ACTOR_SELF, 0, 0)
                EndIf
            EndIf
        CaseEq(2)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            ExecWait(TTYD64_arn_tubbas_heart_EVS_Attack_Leap)
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    BitwiseAndConst(LVar0, -3)
    Call(SetActorVar, ACTOR_SELF, 2, LVar0)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_cleft_EVS_TryGettingUp = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
    Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x300103)
    Wait(20)
    Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x300105)
    Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    IfGt(LVar0, 0)
        Sub(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 1, LVar0)
    Else
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x300103)
        Thread
            Wait(3)
            Loop(5)
                Add(LVar0, 36)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                Wait(1)
            EndLoop
        EndThread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar1, 6)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2998046875))
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
        Call(b_area_arn_hyper_cleft_StartRumbleWithParams, 200, 10)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(1.0))
        EndThread
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
        Call(SetActorPos, ACTOR_SELF, LVar0, 0, LVar2)
        Call(SetActorVar, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x300102)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_cleft_UprightAnims))
        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_arn_hyper_cleft_UprightDefenseTable))
        Call(SetTargetOffset, ACTOR_SELF, 1, 0, 22)
        Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, -10)
        Call(SetPartEventBits, ACTOR_SELF, 1, 16, 1)
        Wait(1)
        Call(b_area_arn_hyper_cleft_SetSpinSmashable, 1)
        Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_tubbas_heart_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            ExecWait(b_area_arn_tubbas_heart_EVS_SelectAnimation)
            SetConst(LVar0, 1)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(56)
        CaseOrEq(14)
        CaseOrEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x6C0010)
            SetConst(LVar2, 0x6C0011)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        EndCaseGroup
        CaseEq(11)
            ExecWait(b_area_arn_tubbas_heart_EVS_SelectAnimation)
            SetConst(LVar0, 1)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseOrEq(47)
        CaseOrEq(38)
            ExecWait(b_area_arn_tubbas_heart_EVS_SelectAnimation)
            SetConst(LVar0, 1)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            ExecWait(b_area_arn_tubbas_heart_EVS_SelectAnimation)
            SetConst(LVar0, 1)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(SetAnimation, ACTOR_SELF, 1, 0x6C0003)
            ExecWait(TTYD64_arn_tubbas_heart_EVS_ReturnHome)
        EndCaseGroup
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            Set(LVar1, 0x6C0001)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            IfNe(LVar0, 0)
                Set(LVar1, 0x6C000B)
            EndIf
            SetConst(LVar0, 1)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseOrEq(32)
            ExecWait(b_area_arn_tubbas_heart_EVS_SelectAnimation)
            SetConst(LVar0, 1)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(33)
            ExecWait(b_area_arn_tubbas_heart_EVS_SelectAnimation)
            SetConst(LVar0, 1)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(42)
        CaseEq(44)
        CaseEq(53)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6C0003)
            ExecWait(TTYD64_arn_tubbas_heart_EVS_ReturnHome)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x6C0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseDefault
    EndSwitch
    Call(GetActorHP, ACTOR_SELF, LVar0)
    IfLe(LVar0, 5)
        ExecWait(b_area_arn_tubbas_heart_EVS_FleeFromBattle)
        Return
    Else
        Call(UseIdleAnimation, ACTOR_SELF, 1)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_tubbas_heart_EVS_Move_Charge = {
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, 85, 50, 0)
    Call(SetBattleCamDist, 280)
    Call(SetBattleCamOffsetY, 0)
    Call(MoveBattleCamOver, 40)
    Wait(40)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6C000B)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVar4)
    IfNotFlag(LVar4, 0x80000)
        Add(LVar1, 15)
        SetF(LVar3, Float(1.0))
    Else
        Add(LVar1, 6)
        SetF(LVar3, Float(0.400390625))
    EndIf
    Call(PlayEffect_impl, 71, 1, LVar0, LVar1, LVar2, LVar3, 60, 0, 0, 0, 0, 0, 0, 0)
    Call(PlayEffect_impl, 107, 6, LVar0, LVar1, LVar2, LVar3, 60, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8439)
    Wait(60)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 1)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVar4)
    IfNotFlag(LVar4, 0x80000)
        Add(LVar1, 15)
        SetF(LVar3, Float(1.0))
    Else
        Add(LVar1, 6)
        SetF(LVar3, Float(0.400390625))
    EndIf
    Call(PlayEffect_impl, 107, 3, LVar0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 4, LVarF)
    Call(TTYD64_AddCharge, ACTOR_SELF, 6)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_tubbas_heart_ChargedAnims))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_cleft_EVS_FlipOver = {
    Call(SetActorVar, ACTOR_SELF, 0, 1)
    Call(SetActorVar, ACTOR_SELF, 1, 2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x300107)
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
    Thread
        Set(LVar0, 0)
        Loop(5)
            Add(LVar0, -36)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2998046875))
    Sub(LVar1, 6)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
    Call(b_area_arn_hyper_cleft_StartRumbleWithParams, 200, 10)
    Thread
        Call(ShakeCam, 1, 0, 5, Float(1.0))
    EndThread
    Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 40, 8, Float(0.0), 20, 0, 0, 0, 0, 0)
    Call(SetActorPos, ACTOR_SELF, LVar0, 0, LVar2)
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x300103)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_cleft_ToppledAnims))
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_arn_hyper_cleft_ToppledDefenseTable))
    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 15)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, -7)
    Call(SetPartEventBits, ACTOR_SELF, 1, 16, 0)
    Call(b_area_arn_hyper_cleft_SetSpinSmashable, 0)
    Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(EnableActorGlow, ACTOR_SELF, 0)
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_paragoomba_EVS_Downed_Idle = {
    Label(10)
    Call(RandInt, 80, LVar0)
    Add(LVar0, 80)
    Loop(LVar0)
        Label(0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(0)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedAnims))
    Loop(20)
        Label(1)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedAnims))
    Loop(80)
        Label(2)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(2)
        EndIf
        Wait(1)
    EndLoop
    Goto(10)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_goomba_EVS_Idle = {
    Label(10)
    Call(RandInt, 80, LVar0)
    Add(LVar0, 80)
    Loop(LVar0)
        Label(0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(0)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_goomba_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedAnims_80227C08))
    Loop(20)
        Label(1)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_goomba_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_arn_hyper_paragoomba_DownedAnims_80227C08))
    Loop(80)
        Label(2)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(2)
        EndIf
        Wait(1)
    EndLoop
    Goto(10)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_paragoomba_EVS_Idle = {
    Label(10)
    Call(RandInt, 80, LVar0)
    Add(LVar0, 80)
    Loop(LVar0)
        Label(0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(0)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(0.599609375))
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_arn_hyper_paragoomba_FlyingShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, -5, 0)
    Loop(20)
        Label(1)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(0.599609375))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, -5, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_arn_hyper_paragoomba_FlyingAnims))
    Loop(40)
        Label(2)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(2)
        EndIf
        Wait(1)
    EndLoop
    Goto(10)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_cleft_EVS_TakeTurn = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetBattleVar, 1, 1)
        ExecWait(TTYD64_arn_hyper_cleft_EVS_Attack_Tackle)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_arn_hyper_cleft_EVS_TryGettingUp)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 2)
        ExecWait(TTYD64_arn_hyper_cleft_EVS_Move_Charge)
        Return
    EndIf
    Call(GetBattleVar, 1, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfEq(LVar0, 0)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 750)
                    Call(SetBattleVar, 1, 2)
                    ExecWait(TTYD64_arn_hyper_cleft_EVS_Move_Charge)
                Else
                    Call(SetBattleVar, 1, 1)
                    ExecWait(TTYD64_arn_hyper_cleft_EVS_Attack_Tackle)
                EndIf
            Else
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 500)
                    Call(SetBattleVar, 1, 2)
                    ExecWait(TTYD64_arn_hyper_cleft_EVS_Move_Charge)
                Else
                    Call(SetBattleVar, 1, 1)
                    ExecWait(TTYD64_arn_hyper_cleft_EVS_Attack_Tackle)
                EndIf
            EndIf
        CaseEq(1)
            ExecWait(TTYD64_arn_hyper_cleft_EVS_Attack_Tackle)
            Return
        CaseEq(2)
            ExecWait(TTYD64_arn_hyper_cleft_EVS_Move_Charge)
            Return
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_goomba_EVS_TakeTurn = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetBattleVar, 1, 1)
        ExecWait(TTYD64_arn_hyper_goomba_EVS_Attack_Headbonk)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_arn_hyper_goomba_EVS_Move_Charge)
        Return
    EndIf
    Call(GetBattleVar, 1, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            IfEq(LVar0, 0)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 750)
                    Call(SetBattleVar, 1, 2)
                    ExecWait(TTYD64_arn_hyper_goomba_EVS_Move_Charge)
                Else
                    Call(SetBattleVar, 1, 1)
                    ExecWait(TTYD64_arn_hyper_goomba_EVS_Attack_Headbonk)
                EndIf
            Else
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 500)
                    Call(SetBattleVar, 1, 2)
                    ExecWait(TTYD64_arn_hyper_goomba_EVS_Move_Charge)
                Else
                    Call(SetBattleVar, 1, 1)
                    ExecWait(TTYD64_arn_hyper_goomba_EVS_Attack_Headbonk)
                EndIf
            EndIf
        CaseEq(1)
            ExecWait(TTYD64_arn_hyper_goomba_EVS_Attack_Headbonk)
        CaseEq(2)
            ExecWait(TTYD64_arn_hyper_goomba_EVS_Move_Charge)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_paragoomba_EVS_Downed_TakeTurn = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetBattleVar, 1, 1)
        ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Attack_Headbonk)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Downed_Move_Charge)
        Return
    EndIf
    Call(GetBattleVar, 1, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            IfEq(LVar0, 0)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 750)
                    Call(SetBattleVar, 1, 2)
                    ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Downed_Move_Charge)
                Else
                    Call(SetBattleVar, 1, 1)
                    ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Attack_Headbonk)
                EndIf
            Else
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 500)
                    Call(SetBattleVar, 1, 2)
                    ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Downed_Move_Charge)
                Else
                    Call(SetBattleVar, 1, 1)
                    ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Attack_Headbonk)
                EndIf
            EndIf
        CaseEq(1)
            ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Attack_Headbonk)
        CaseEq(2)
            ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Downed_Move_Charge)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_paragoomba_EVS_Flying_TakeTurn = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetBattleVar, 1, 1)
        ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Attack_SkyDive)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Attack_ChargedDive)
        Return
    EndIf
    Call(GetBattleVar, 1, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            IfEq(LVar0, 0)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 750)
                    Call(SetBattleVar, 1, 2)
                    ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Attack_ChargedDive)
                Else
                    Call(SetBattleVar, 1, 1)
                    ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Attack_SkyDive)
                EndIf
            Else
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 500)
                    Call(SetBattleVar, 1, 2)
                    ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Attack_ChargedDive)
                Else
                    Call(SetBattleVar, 1, 1)
                    ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Attack_SkyDive)
                EndIf
            EndIf
        CaseEq(1)
            ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Attack_SkyDive)
        CaseEq(2)
            ExecWait(TTYD64_arn_hyper_paragoomba_EVS_Attack_ChargedDive)
    EndSwitch
    Return
    End
};
// clang-format on

Battle TTYD64_arn_Formations[] = {
    { .name = "\317\244\321\374\257\352\334\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_arn_Formation_00,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    { .name = "\317\244\321\374\257\352\334\374x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_arn_Formation_01,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    { .name = "\317\244\321\374\257\352\334\374x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_arn_Formation_02,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    { .name = "\317\244\321\374\257\352\334\374x2,\317\244\321\374\321\277\257\352\334\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_arn_Formation_03,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    { .name = "\317\244\321\374\257\352\334\374x3,\317\244\321\374\321\277\257\352\334\374",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_arn_Formation_04,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    { .name = "\317\244\321\374\257\352\334\374x2,\317\244\321\374\321\277\257\352\334\374,"
              "\317\244\321\374\257\352\334\374",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_arn_Formation_05,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    { .name = "\317\244\321\374\321\277\257\352\334\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_arn_Formation_06,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    { .name = "\317\244\321\374\321\277\257\352\334\374x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_arn_Formation_07,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    { .name = "\317\244\321\374\321\277\257\352\334\374x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_arn_Formation_08,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    { .name = "\317\244\321\374\321\277\257\352\334\374x4",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_arn_Formation_09,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    { .name = "\317\244\321\374\267\363\250\342\363",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_arn_Formation_0A,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    { .name = "\317\244\321\374\267\363\250\342\363x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_arn_Formation_0B,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    { .name = "\317\244\321\374\267\363\250\342\363x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_arn_Formation_0C,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    { .name = "\317\244\321\374\267\363\250\342\363,\317\244\321\374\257\352\334\374x2",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_arn_Formation_0D,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    { .name = "\317\244\321\374\267\363\250\342\363x2,\317\244\321\374\257\352\334\374x2",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_arn_Formation_0E,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    { .name = "\311\254\334\363W\223^F",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_arn_Formation_0F,
      .stage = &b_area_arn_arn_06,
      .onBattleStart = NULL },
    { .name = "\311\254\334\363",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_arn_Formation_10,
      .stage = &b_area_arn_arn_01,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_arn_hyper_paragoomba_EVS_KnockDown_Init = {
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_arn_hyper_paragoomba_EVS_Downed_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_arn_hyper_paragoomba_EVS_Downed_HandleEvent))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_arn_hyper_paragoomba_EVS_Downed_TakeTurn))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_arn_hyper_paragoomba_EVS_HandlePhase))
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 1)
            Call(SetPartEventBits, ACTOR_SELF, 2, 0x400000, 0)
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Call(SetActorVar, ACTOR_SELF, 1, LVar0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_tubbas_heart_EVS_Init = {
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_arn_tubbas_heart_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_arn_tubbas_heart_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_arn_tubbas_heart_EVS_HandleEvent))
    Call(SetPartTargetFlagBits, ACTOR_SELF, 2, 2, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_tubbas_heart_EVS_ReturnHome = {
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 45)
    Set(LVar1, 0)
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetGoalToHome, ACTOR_SELF)
    Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6C0001)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Return
    End
};
// clang-format on

s32 TTYD64_arn_hyper_paragoomba_DownedStatusTable[] = {
    1,  0, 2,  0, 6,  80, 9,  100, 7,  100, 4,  80, 3,  100, 11, 100, 5,  100, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,   36, 0,   35, 0,  33, 0,   38, 0,   39, 0,   41, 0,  0,
};

s32 TTYD64_arn_hyper_cleft_StatusTable[] = {
    1,  0, 2,  0,  6,  40, 9,  50, 7,  50, 4,  50, 3,  0, 11, 50, 5,  50, 10, 90, 8, 90,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0,  39, 0,  41, 0,  0,
};

s32 TTYD64_arn_hyper_paragoomba_FlyingStatusTable[] = {
    1,  0, 2,  0, 6,  80, 9,  80, 7,  100, 4,  90, 3,  0, 11, 80, 5,  100, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 1,   35, 0,  33, 0, 38, 0,  39, 0,   41, 0,  0,
};

s32 TTYD64_arn_hyper_goomba_StatusTable[] = {
    1,  0, 2,  0, 6,  80, 9,  100, 7,  100, 4,  80, 3,  100, 11, 100, 5,  100, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,   36, 0,   35, 0,  33, 0,   38, 0,   39, 0,   41, 0,  0,
};

// clang-format off
EvtScript TTYD64_arn_tubba_blubba_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 60)
        ExecWait(TTYD64_arn_tubba_blubba_EVS_Attack_SlamFist)
    Else
        ExecWait(TTYD64_arn_tubba_blubba_EVS_Attack_BodySlam)
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_cleft_EVS_Init = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_arn_hyper_cleft_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_arn_hyper_cleft_EVS_HandleEvent))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_arn_hyper_cleft_EVS_TakeTurn))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_arn_hyper_cleft_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_arn_hyper_paragoomba_EVS_Init = {
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_arn_hyper_paragoomba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_arn_hyper_paragoomba_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_arn_hyper_paragoomba_EVS_Flying_HandlePhase))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_arn_hyper_paragoomba_EVS_Flying_TakeTurn))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_arn_hyper_paragoomba_ActorParts[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 22 },
        .opacity = 255,
        .idleAnimations = TTYD64_arn_hyper_paragoomba_DownedAnims,
        .defenseTable = b_area_arn_hyper_paragoomba_DownedDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_arn_hyper_paragoomba_FlyingAnims,
        .defenseTable = b_area_arn_hyper_paragoomba_FlyingDefense,
        .eventFlags = 0x4000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -16, 24 },
        .opacity = 255,
        .idleAnimations = b_area_arn_hyper_paragoomba_LeftWingAnims,
        .defenseTable = b_area_arn_hyper_paragoomba_DownedDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -16, 24 },
        .opacity = 255,
        .idleAnimations = b_area_arn_hyper_paragoomba_RightWingAnims,
        .defenseTable = b_area_arn_hyper_paragoomba_DownedDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_arn_hyper_paragoomba_EVS_Init_80227010 = {
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_arn_hyper_goomba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_arn_hyper_goomba_EVS_HandleEvent))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_arn_hyper_goomba_EVS_TakeTurn))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_arn_hyper_goomba_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_arn_Formation_0E[] = {
    { .actor = &TTYD64_arn_hyper_cleft,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
    { .actor = &TTYD64_arn_hyper_cleft,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
};

FormationRow TTYD64_arn_Formation_04[] = {
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_arn_hyper_paragoomba,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
};

FormationRow TTYD64_arn_Formation_05[] = {
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_arn_hyper_paragoomba,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
};

FormationRow TTYD64_arn_Formation_09[] = {
    { .actor = &TTYD64_arn_hyper_paragoomba,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
    { .actor = &TTYD64_arn_hyper_paragoomba,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
    { .actor = &TTYD64_arn_hyper_paragoomba,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
    { .actor = &TTYD64_arn_hyper_paragoomba,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
};

// clang-format off
EvtScript TTYD64_arn_tubba_blubba_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_arn_tubba_blubba_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_arn_tubba_blubba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_arn_tubba_blubba_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Exec(b_area_arn_tubba_blubba_EVS_PlayFootstepQuaking)
    Return
    End
};
// clang-format on

s32 TTYD64_arn_tubbas_heart_ChargedAnims[] = {
    1, 0x6C000B, 7, 0x6C0000, 6, 0x6C0004, 9, 0x6C000B, 8, 0x6C0000, 11, 0x6C0000,
    5, 0x6C0000, 5, 0x6C0000, 4, 0x6C000D, 4, 0x6C000D, 3, 0x6C000A, 0,
};

s32 TTYD64_arn_tubbas_heart_DefaultAnims[] = {
    1, 0x6C0001, 7, 0x6C0000, 6, 0x6C0004, 9, 0x6C0001, 8, 0x6C0000, 11, 0x6C0000,
    5, 0x6C0000, 5, 0x6C0000, 4, 0x6C000D, 4, 0x6C000D, 3, 0x6C000A, 0,
};

FormationRow TTYD64_arn_Formation_0D[] = {
    { .actor = &TTYD64_arn_hyper_cleft,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
};

FormationRow TTYD64_arn_Formation_0C[] = {
    { .actor = &TTYD64_arn_hyper_cleft,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
    { .actor = &TTYD64_arn_hyper_cleft,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
    { .actor = &TTYD64_arn_hyper_cleft,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
};

FormationRow TTYD64_arn_Formation_02[] = {
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
};

FormationRow TTYD64_arn_Formation_03[] = {
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_arn_hyper_paragoomba,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
};

FormationRow TTYD64_arn_Formation_08[] = {
    { .actor = &TTYD64_arn_hyper_paragoomba,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
    { .actor = &TTYD64_arn_hyper_paragoomba,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
    { .actor = &TTYD64_arn_hyper_paragoomba,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
};

s32 TTYD64_arn_tubba_blubba_DefaultAnims[] = {
    1,        0x6B0001, 7,        0x6B0000, 6,        0x6B0018, 9,        0x6B0001, 8,        0x6B0000, 11,
    0x6B0000, 5,        0x6B0000, 5,        0x6B0000, 4,        0x6B0018, 3,        0x6B0000, 0,
};

s32 TTYD64_arn_hyper_paragoomba_DownedChargedAnims[] = {
    1,  0x260208, 7, 0x260200, 6, 0x260208, 9, 0x260208, 8, 0x260200,
    11, 0x260208, 5, 0x260200, 4, 0x260207, 3, 0x260207, 0,
};

s32 TTYD64_arn_hyper_goomba_ShuffleAnims[] = {
    1,  0x260203, 7, 0x260200, 6, 0x260208, 9, 0x260201, 8, 0x260200,
    11, 0x260203, 5, 0x260200, 4, 0x260207, 3, 0x260207, 0,
};

s32 TTYD64_arn_hyper_goomba_HyperAnims[] = {
    1,  0x260208, 7, 0x260200, 6, 0x260208, 9, 0x260208, 8, 0x260200,
    11, 0x260208, 5, 0x260200, 4, 0x260207, 3, 0x260207, 0,
};

s32 TTYD64_arn_hyper_cleft_HyperAnims[] = {
    1,  0x300104, 7, 0x300100, 6, 0x30010C, 9, 0x300104, 8, 0x300100,
    11, 0x300104, 5, 0x300100, 4, 0x30010E, 3, 0x30010E, 0,
};

s32 TTYD64_arn_hyper_paragoomba_DownedAnims[] = {
    1,  0x260201, 7, 0x260200, 6, 0x260208, 9, 0x260201, 8, 0x260200,
    11, 0x260201, 5, 0x260200, 4, 0x260207, 3, 0x260207, 0,
};

s32 TTYD64_arn_hyper_cleft_ToppledAnims[] = {
    1,  0x300105, 7, 0x300101, 6, 0x30010D, 9, 0x300105, 8, 0x300101,
    11, 0x300105, 5, 0x300101, 4, 0x30010F, 3, 0x30010F, 0,
};

s32 TTYD64_arn_hyper_paragoomba_DownedAnims_80227C08[] = {
    1,  0x260201, 7, 0x260200, 6, 0x260208, 9, 0x260201, 8, 0x260200,
    11, 0x260201, 5, 0x260200, 4, 0x260207, 3, 0x260207, 0,
};

s32 TTYD64_arn_hyper_paragoomba_DownedShuffleAnims[] = {
    1,  0x260203, 7, 0x260200, 6, 0x260208, 9, 0x260201, 8, 0x260200,
    11, 0x260203, 5, 0x260200, 4, 0x260207, 3, 0x260207, 0,
};

s32 TTYD64_arn_hyper_paragoomba_ChargedFlyingAnims[] = {
    1,  0x280202, 7, 0x280200, 6, 0x28020B, 9, 0x280202, 8, 0x280200,
    11, 0x280202, 5, 0x280200, 4, 0x28020C, 3, 0x28020C, 0,
};

s32 TTYD64_arn_hyper_cleft_UprightAnims[] = {
    1,  0x300102, 7, 0x300100, 6, 0x30010C, 9, 0x300102, 8, 0x300100,
    11, 0x300102, 5, 0x300100, 4, 0x30010E, 3, 0x30010E, 0,
};

s32 TTYD64_arn_hyper_paragoomba_FlyingAnims[] = {
    1,  0x280201, 7, 0x280200, 6, 0x28020B, 9, 0x280201, 8, 0x280200,
    11, 0x280201, 5, 0x280200, 4, 0x28020C, 3, 0x28020C, 0,
};

s32 TTYD64_arn_hyper_paragoomba_FlyingShuffleAnims[] = {
    1,  0x280204, 7, 0x280200, 6, 0x28020B, 9, 0x280201, 8, 0x280200,
    11, 0x280204, 5, 0x280200, 4, 0x28020C, 3, 0x28020C, 0,
};

ActorPartBlueprint TTYD64_arn_tubbas_heart_ActorParts[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_arn_tubbas_heart_DefaultAnims,
        .defenseTable = b_area_arn_tubbas_heart_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x80800001,
        .index = 2,
        .posOffset = { 0, 54, 0 },
        .targetOffset = { 0, -30 },
        .opacity = 255,
        .idleAnimations = TTYD64_arn_tubbas_heart_DefaultAnims,
        .defenseTable = b_area_arn_tubbas_heart_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

StageListRow TTYD64_arn_Stages[] = {
    { .name = "arn_01", .stage = &b_area_arn_arn_01 },         { .name = "arn_02", .stage = &b_area_arn_arn_02 },
    { .name = "arn_03", .stage = &b_area_arn_arn_03 },         { .name = "arn_04", .stage = &b_area_arn_arn_04 },
    { .name = "arn_05", .stage = &b_area_arn_arn_05 },         { .name = "arn_06", .stage = &b_area_arn_arn_06 },
    { .name = "arn_22", .stage = &TTYD64_arn_Stage_80228030 }, {},
};

FormationRow TTYD64_arn_Formation_0B[] = {
    { .actor = &TTYD64_arn_hyper_cleft,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
    { .actor = &TTYD64_arn_hyper_cleft,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
};

FormationRow TTYD64_arn_Formation_01[] = {
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
};

FormationRow TTYD64_arn_Formation_07[] = {
    { .actor = &TTYD64_arn_hyper_paragoomba,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
    { .actor = &TTYD64_arn_hyper_paragoomba,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
};

Stage TTYD64_arn_Stage_80228030 = {
    .texture = "arn_tex",
    .shape = "arn_bt07_shape",
    .hit = "arn_bt07_hit",
    .preBattle = &b_area_arn_arn_05_EVS_PreBattle,
    .postBattle = &b_area_arn_arn_05_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = TTYD64_arn_FgModels_80228760,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_arn_tubbas_heart = {
    .flags = 0x0,
    .maxHP = 50,
    .type = 0xA5,
    .level = 0,
    .partCount = 2,
    .partsData = TTYD64_arn_tubbas_heart_ActorParts,
    .initScript = &TTYD64_arn_tubbas_heart_EVS_Init,
    .statusTable = b_area_arn_tubbas_heart_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 30, 30 },
    .healthBarOffset = { 5, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_arn_hyper_cleft = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x1D,
    .level = 15,
    .partCount = 1,
    .partsData = TTYD64_arn_hyper_cleft_ActorParts,
    .initScript = &TTYD64_arn_hyper_cleft_EVS_Init,
    .statusTable = TTYD64_arn_hyper_cleft_StatusTable,
    .escapeChance = 70,
    .airLiftChance = 30,
    .hurricaneChance = 30,
    .spookChance = 30,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 2,
    .size = { 44, 36 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_arn_tubba_blubba = {
    .flags = 0x0,
    .maxHP = 10,
    .type = 0xA3,
    .level = 70,
    .partCount = 1,
    .partsData = TTYD64_arn_tubba_blubba_ActorParts,
    .initScript = &TTYD64_arn_tubba_blubba_EVS_Init,
    .statusTable = b_area_arn_tubba_blubba_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 110, 100 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -33, 78 },
    .statusTextOffset = { 10, 75 },
};

ActorBlueprint TTYD64_arn_hyper_goomba = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x1B,
    .level = 12,
    .partCount = 1,
    .partsData = TTYD64_arn_hyper_goomba_ActorParts,
    .initScript = &TTYD64_arn_hyper_paragoomba_EVS_Init_80227010,
    .statusTable = TTYD64_arn_hyper_goomba_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 90,
    .hurricaneChance = 90,
    .spookChance = 80,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 24, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_arn_hyper_paragoomba = {
    .flags = 0x200,
    .maxHP = 8,
    .type = 0x1C,
    .level = 12,
    .partCount = 4,
    .partsData = TTYD64_arn_hyper_paragoomba_ActorParts,
    .initScript = &TTYD64_arn_hyper_paragoomba_EVS_Init,
    .statusTable = TTYD64_arn_hyper_paragoomba_FlyingStatusTable,
    .escapeChance = 50,
    .airLiftChance = 95,
    .hurricaneChance = 95,
    .spookChance = 80,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 36, 26 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorPartBlueprint TTYD64_arn_tubba_blubba_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -15, 75 },
        .opacity = 255,
        .idleAnimations = TTYD64_arn_tubba_blubba_DefaultAnims,
        .defenseTable = b_area_arn_tubba_blubba_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_arn_hyper_goomba_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 22 },
        .opacity = 255,
        .idleAnimations = TTYD64_arn_hyper_paragoomba_DownedAnims_80227C08,
        .defenseTable = b_area_arn_hyper_paragoomba_DownedDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_arn_hyper_cleft_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 22 },
        .opacity = 255,
        .idleAnimations = TTYD64_arn_hyper_cleft_UprightAnims,
        .defenseTable = b_area_arn_hyper_cleft_UprightDefenseTable,
        .eventFlags = 0x10,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_arn_Formation_0A[] = {
    { .actor = &TTYD64_arn_hyper_cleft,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERCLEFT },
};

FormationRow TTYD64_arn_Formation_0F[] = {
    { .actor = &TTYD64_arn_tubbas_heart,
      .home = { .vec = &b_area_arn_vector3D_802280C0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_arn_Formation_10[] = {
    { .actor = &TTYD64_arn_tubba_blubba,
      .home = { .vec = &b_area_arn_vector3D_802280E8 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_arn_Formation_00[] = {
    { .actor = &TTYD64_arn_hyper_goomba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERGOOMBA },
};

FormationRow TTYD64_arn_Formation_06[] = {
    { .actor = &TTYD64_arn_hyper_paragoomba,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HYPERPARAGOOMBA },
};

s32 TTYD64_arn_FgModels_80228760[] = {
    16,
    0,
};

void TTYD64_InstallBattles_arn(void) {
    Mod_SetBattleList("TTYD64", 14, TTYD64_arn_Formations);
    Mod_SetStageList("TTYD64", 14, TTYD64_arn_Stages);
}
