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

API_CALLABLE(ActorExists);
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
API_CALLABLE(FallToGoal);
API_CALLABLE(FlyPartTo);
API_CALLABLE(FlyToGoal);
API_CALLABLE(ForceHomePos);
API_CALLABLE(FreezeBattleState);
API_CALLABLE(GetActionProgress);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetAnimation);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetCurrentPartnerID);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetMashActionQuality);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartAnimNotify);
API_CALLABLE(GetPartOffset);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToHome);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PartnerIsFlying);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlaySoundAtPart);
API_CALLABLE(PlayerFallToGoal);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(ResetActorSounds);
API_CALLABLE(ResetAllActorSounds);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetAnimationRate);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetDefenseTable);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(SetMessageBoxDuration);
API_CALLABLE(SetPartEventBits);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartRotation);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetProjectileTargetOffset);
API_CALLABLE(SetTargetActor);
API_CALLABLE(SetTargetOffset);
API_CALLABLE(SetupMashMeter);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowActionHud);
API_CALLABLE(ShowMessageBox);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseBattleCamPresetImmediately);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
API_CALLABLE(action_command_break_free_init);
API_CALLABLE(action_command_break_free_start);
API_CALLABLE(action_command_whirlwind_init);
API_CALLABLE(action_command_whirlwind_start);
API_CALLABLE(b_area_iwa_buzzar_StartRumbleWithParams);
API_CALLABLE(b_area_iwa_cleft_SetSpinSmashable);
API_CALLABLE(b_area_iwa_cleft_StartRumbleWithParams);
extern Vec3i b_area_iwa_BossPos;
extern s32 b_area_iwa_buzzar_DefenseTable[];
extern EvtScript b_area_iwa_buzzar_EVS_FlyToHome;
extern EvtScript b_area_iwa_buzzar_EVS_FlyToHome_GrappleFail;
extern EvtScript b_area_iwa_buzzar_EVS_HandleEvent;
extern EvtScript b_area_iwa_buzzar_EVS_HandlePhase;
extern EvtScript b_area_iwa_buzzar_EVS_Idle;
extern s32 b_area_iwa_buzzar_FeatherAnims[];
extern s32 b_area_iwa_buzzar_StatusTable[];
extern EvtScript b_area_iwa_cleft_EVS_Idle;
extern s32 b_area_iwa_cleft_StatusTable[];
extern s32 b_area_iwa_cleft_ToppledDefenseTable[];
extern s32 b_area_iwa_cleft_UprightDefenseTable[];
extern EvtScript b_area_iwa_iwa_01_EVS_PostBattle;
extern EvtScript b_area_iwa_iwa_01_EVS_PreBattle;
extern s32 b_area_iwa_iwa_01_ForegroundModels[];
extern Vec3i b_area_iwa_iwa_01_WhackaPos;
extern Stage b_area_iwa_iwa_01b;
extern Stage b_area_iwa_iwa_02;
extern s32 b_area_iwa_monty_mole_DefenseTable[];
extern EvtScript b_area_iwa_monty_mole_EVS_HandleEvent;
extern EvtScript b_area_iwa_monty_mole_EVS_Idle;
extern s32 b_area_iwa_monty_mole_RockAnims[];
extern s32 b_area_iwa_monty_mole_StatusTable[];
extern s32 b_area_iwa_whacka_DefenseTable[];
extern EvtScript b_area_iwa_whacka_EVS_Init;
extern s32 b_area_iwa_whacka_StatusTable[];
extern EvtScript TTYD64_iwa_buzzar_EVS_Attack_GrappleDrop;
extern EvtScript TTYD64_iwa_buzzar_EVS_Attack_FeatherFling;
extern EvtScript TTYD64_iwa_buzzar_EVS_Attack_WindBlast;
extern EvtScript TTYD64_iwa_cleft_EVS_HandleEvent;
extern EvtScript TTYD64_iwa_cleft_EVS_Attack_Tackle;
extern EvtScript TTYD64_iwa_buzzar_EVS_Attack_ClawSwipe;
extern EvtScript TTYD64_iwa_monty_mole_EVS_TakeTurn;
extern EvtScript TTYD64_iwa_cleft_EVS_TryGettingUp;
extern EvtScript TTYD64_iwa_cleft_EVS_FlipOver;
extern EvtScript TTYD64_iwa_buzzar_EVS_LiftMario;
extern EvtScript TTYD64_iwa_buzzar_EVS_TakeTurn;
extern EvtScript TTYD64_iwa_EVS_8021FEEC;
extern EvtScript TTYD64_iwa_buzzar_EVS_Init;
extern EvtScript TTYD64_iwa_cleft_EVS_Init;
extern EvtScript TTYD64_iwa_monty_mole_EVS_Init;
extern EvtScript TTYD64_iwa_cleft_EVS_TakeTurn;
extern ActorBlueprint TTYD64_iwa_whacka;
extern ActorBlueprint TTYD64_iwa_whacka_802216D8;
extern ActorBlueprint TTYD64_iwa_cleft;
extern ActorBlueprint TTYD64_iwa_buzzar;
extern Stage TTYD64_iwa_iwa_01;
extern ActorBlueprint TTYD64_iwa_monty_mole;
extern Battle TTYD64_iwa_Formations[];
extern ActorPartBlueprint TTYD64_iwa_buzzar_ActorParts[];
extern FormationRow TTYD64_iwa_Formation_08[];
extern ActorPartBlueprint TTYD64_iwa_monty_mole_ActorParts[];
extern FormationRow TTYD64_iwa_Formation_0A[];
extern FormationRow TTYD64_iwa_Formation_0D[];
extern FormationRow TTYD64_iwa_Formation_0B[];
extern FormationRow TTYD64_iwa_Formation_04[];
extern FormationRow TTYD64_iwa_Formation_02[];
extern FormationRow TTYD64_iwa_Formation_07[];
extern s32 TTYD64_iwa_cleft_UprightAnims[];
extern s32 TTYD64_iwa_whacka_DefaultAnims[];
extern s32 TTYD64_iwa_monty_mole_DefaultAnims[];
extern s32 TTYD64_iwa_whacka_DefaultAnims_8022136C[];
extern s32 TTYD64_iwa_cleft_ToppledAnims[];
extern s32 TTYD64_iwa_buzzar_DefaultAnims[];
extern FormationRow TTYD64_iwa_Formation_01[];
extern FormationRow TTYD64_iwa_Formation_03[];
extern FormationRow TTYD64_iwa_Formation_09[];
extern FormationRow TTYD64_iwa_Formation_06[];
extern ActorPartBlueprint TTYD64_iwa_whacka_ActorParts[];
extern ActorPartBlueprint TTYD64_iwa_whacka_ActorParts_80221814[];
extern ActorPartBlueprint TTYD64_iwa_cleft_ActorParts[];
extern StageListRow TTYD64_iwa_Stages[];
extern FormationRow TTYD64_iwa_iwa_01_WhackaFormation[];
extern FormationRow TTYD64_iwa_Formation_0C[];
extern FormationRow TTYD64_iwa_Formation_00[];
extern FormationRow TTYD64_iwa_Formation_05[];

// clang-format off
EvtScript TTYD64_iwa_buzzar_EVS_Attack_GrappleDrop = {
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
    Call(SetBattleCamDist, 240)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 45, 55, 0)
    Call(GetAnimation, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseOrEq(0x670001)
        CaseOrEq(0x670002)
        CaseOrEq(0x67000D)
        CaseOrEq(0x670016)
        CaseOrEq(0x670017)
            Loop(0)
                Call(GetPartAnimNotify, ACTOR_SELF, 1, LVar0)
                IfEq(LVar0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x670002)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 10)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 4, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(10)
            Call(UseBattleCamPreset, 66)
            Call(SetBattleCamDist, 240)
            Call(SetBattleCamOffsetY, -10)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(PlaySoundAtActor, ACTOR_SELF, 8433)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8434)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -45, -20, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x670018)
            Call(FlyToGoal, ACTOR_SELF, 12, -12, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x670001)
            Wait(10)
            Call(UseBattleCamPreset, 2)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            ExecWait(b_area_iwa_buzzar_EVS_FlyToHome_GrappleFail)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseEq(8)
            Call(UseBattleCamPreset, 66)
            Call(SetBattleCamDist, 240)
            Call(SetBattleCamOffsetY, -10)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(PlaySoundAtActor, ACTOR_SELF, 8433)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8434)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -15, -10, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x670018)
            Call(FlyToGoal, ACTOR_SELF, 8, -5, 0)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 4, 32)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 40, 10, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(GetAnimation, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(0x670001)
                CaseOrEq(0x670002)
                CaseOrEq(0x67000D)
                CaseOrEq(0x670016)
                CaseOrEq(0x670017)
                    Loop(0)
                        Call(GetPartAnimNotify, ACTOR_SELF, 1, LVar0)
                        IfEq(LVar0, 1)
                            BreakLoop
                        EndIf
                        Wait(1)
                    EndLoop
                EndCaseGroup
            EndSwitch
            Call(ResetActorSounds, ACTOR_SELF, 1)
            Call(SetActorSounds, ACTOR_SELF, 5, -14, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x670002)
            Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            ExecWait(b_area_iwa_buzzar_EVS_FlyToHome)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        CaseDefault
    EndSwitch
    Wait(10)
    Call(UseBattleCamPresetImmediately, 19)
    Call(SetBattleCamDist, 360)
    Call(MoveBattleCamOver, 30)
    Thread
        Wait(5)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamDist, 360)
        Call(GetOwnerTarget, LVar3, 0)
        Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
        Set(LVar1, 27)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(MoveBattleCamOver, 20)
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 8433)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8434)
    Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -15, -10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x670018)
    Call(FlyToGoal, ACTOR_SELF, 8, -5, 0)
    IfEq(LVarA, 7)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 4, 32)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8437)
    Call(SetAnimation, ACTOR_SELF, 1, 0x670016)
    Call(b_area_iwa_buzzar_StartRumbleWithParams, 180, 20)
    Call(GetOwnerTarget, LVar3, 0)
    Call(UseIdleAnimation, LVar3, 0)
    Switch(LVar3)
        CaseEq(0)
            Call(SetAnimation, 0, 0, 0x1002B)
        CaseEq(256)
            Set(LVar0, 4)
            Exec(TTYD64_SetPartnerAnimation_Battle)
    EndSwitch
    Call(ShowMessageBox, 64, 90)
    Thread
        Loop(90)
            Call(SetMessageBoxDuration, 99)
            Wait(1)
        EndLoop
        Call(SetMessageBoxDuration, 0)
    EndThread
    Wait(20)
    Call(LoadActionCommand, 4)
    Call(action_command_break_free_init)
    Call(SetupMashMeter, 1, 30, 0, 0, 0, 0)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x670017)
    Call(UseBattleCamPreset, 66)
    Call(SetBattleCamDist, 240)
    Call(SetBattleCamOffsetY, -10)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 60)
    Call(SetBattleFlagBits, 0x4000, 0)
    Call(ShowActionHud, 1)
    Call(action_command_break_free_start, 0, 60, 30, 3)
    ExecGetTID(TTYD64_iwa_buzzar_EVS_LiftMario, LVarA)
    Wait(62)
    Call(GetMashActionQuality, LVar0)
    IfGt(LVar0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x670001)
        Wait(2)
        KillThread(LVarA)
        Call(GetOwnerTarget, LVar3, 0)
        Call(SetJumpAnimations, LVar3, 0, 0x10007, 0x10007, 0x10009)
        Call(SetActorSpeed, LVar3, Float(5.0))
        Call(SetActorJumpGravity, LVar3, Float(1.7998046875))
        Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
        Set(LVar1, 0)
        Call(SetGoalPos, LVar3, LVar0, LVar1, LVar2)
        IfEq(LVar3, 0)
            Call(PlayerFallToGoal, 15)
        Else
            Call(FallToGoal, LVar3, 15)
        EndIf
        Wait(8)
        Call(GetOwnerTarget, LVar3, 0)
        Switch(LVar3)
            CaseEq(0)
                Call(SetAnimation, 0, 0, 0x10002)
            CaseEq(256)
                Set(LVar0, 0)
                Exec(TTYD64_SetPartnerAnimation_Battle)
                Call(PartnerIsFlying, LVar0)
                IfEq(LVar0, 0)
                    Call(GetCurrentPartnerID, LVar4)
                    Call(GetActorPos, 256, LVar0, LVar1, LVar2)
                    Switch(LVar4)
                        CaseEq(6)
                            Add(LVar1, 23)
                        CaseEq(4)
                            Add(LVar1, 27)
                        CaseDefault
                            Add(LVar1, 14)
                    EndSwitch
                    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
                    Call(FlyToGoal, 256, 6, 0, 0)
                EndIf
        EndSwitch
        Call(UseIdleAnimation, LVar3, 1)
        Wait(8)
        Call(UseBattleCamPreset, 2)
        ExecWait(b_area_iwa_buzzar_EVS_FlyToHome_GrappleFail)
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Return
    EndIf
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamDist, 360)
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Set(LVar1, 50)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(MoveBattleCamOver, 200)
    Wait(39)
    Wait(10)
    Call(SetJumpAnimations, LVar3, 0, 0x1001B, 0x1001B, 0x1001B)
    Call(SetActorSpeed, LVar3, Float(5.0))
    Call(SetActorJumpGravity, LVar3, Float(1.2001953125))
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetGoalPos, LVar3, LVar0, LVar1, LVar2)
    IfEq(LVar3, 0)
        Call(PlayerFallToGoal, 24)
    Else
        Call(FallToGoal, LVar3, 24)
        Exec(TTYD64_iwa_EVS_8021FEEC)
    EndIf
    Call(UseIdleAnimation, LVar3, 1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 4, 32)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(GetAnimation, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(0x670001)
                CaseOrEq(0x670002)
                CaseOrEq(0x67000D)
                CaseOrEq(0x670016)
                CaseOrEq(0x670017)
                    Loop(0)
                        Call(GetPartAnimNotify, ACTOR_SELF, 1, LVar0)
                        IfEq(LVar0, 1)
                            BreakLoop
                        EndIf
                        Wait(1)
                    EndLoop
                EndCaseGroup
            EndSwitch
            Call(ResetActorSounds, ACTOR_SELF, 1)
            Call(SetActorSounds, ACTOR_SELF, 5, -14, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x670002)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            ExecWait(b_area_iwa_buzzar_EVS_FlyToHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_iwa_buzzar_EVS_Attack_FeatherFling = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 5)
    Call(SetBattleCamDist, 180)
    Call(SetBattleCamOffsetY, 0)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 40)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 90, 35, 0)
    Call(GetAnimation, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseOrEq(0x670001)
        CaseOrEq(0x670002)
        CaseOrEq(0x67000D)
        CaseOrEq(0x670016)
        CaseOrEq(0x670017)
            Loop(0)
                Call(GetPartAnimNotify, ACTOR_SELF, 1, LVar0)
                IfEq(LVar0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x670002)
    Call(FlyToGoal, ACTOR_SELF, 0, -15, 10)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, -30)
    Add(LVar1, 25)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, -30)
    Add(LVar1, 35)
    Call(SetPartPos, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, -20)
    Add(LVar1, 25)
    Call(SetPartPos, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x67000E)
    Wait(15)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 24)
    Add(LVar1, 24)
    Call(PlayEffect_impl, 109, 0, LVar0, LVar1, LVar2, Float(0.599609375), 0, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8435)
    Wait(10)
    Call(SetPartSounds, ACTOR_SELF, 3, 1, 0, 0)
    Call(SetPartSounds, ACTOR_SELF, 4, 1, 0, 0)
    Call(SetPartSounds, ACTOR_SELF, 5, 1, 0, 0)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Thread
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x670001)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x670010)
    Call(SetPartRotation, ACTOR_SELF, 3, 0, 0, -45)
    Call(SetPartRotation, ACTOR_SELF, 4, 0, 0, -45)
    Call(SetPartRotation, ACTOR_SELF, 5, 0, 0, -45)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 3, 0x670014)
    Call(SetAnimation, ACTOR_SELF, 4, 0x670014)
    Call(SetAnimation, ACTOR_SELF, 5, 0x670014)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 5, 1, 0)
    Call(SetPartMoveSpeed, ACTOR_SELF, 3, Float(6.0))
    Call(SetPartJumpGravity, ACTOR_SELF, 3, Float(0.099609375))
    Call(SetPartMoveSpeed, ACTOR_SELF, 4, Float(6.0))
    Call(SetPartJumpGravity, ACTOR_SELF, 4, Float(0.099609375))
    Call(SetPartMoveSpeed, ACTOR_SELF, 5, Float(6.0))
    Call(SetPartJumpGravity, ACTOR_SELF, 5, Float(0.099609375))
    Call(PlaySoundAtActor, ACTOR_SELF, 8436)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 2, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Thread
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(RandInt, 10, LVar3)
                Sub(LVar3, 30)
                Add(LVar0, LVar3)
                Call(FlyPartTo, ACTOR_SELF, 4, LVar0, 5, LVar2, 9, 0, 0)
                Call(SetAnimation, ACTOR_SELF, 4, 0x670015)
            EndThread
            Thread
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(RandInt, 10, LVar3)
                Sub(LVar3, 40)
                Add(LVar0, LVar3)
                Call(FlyPartTo, ACTOR_SELF, 5, LVar0, 5, LVar2, 9, 0, 0)
                Call(SetAnimation, ACTOR_SELF, 5, 0x670015)
            EndThread
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(FlyPartTo, ACTOR_SELF, 3, LVar0, 5, LVar2, 9, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 3, 0x670015)
            Thread
                Wait(10)
                Call(SetAnimation, ACTOR_SELF, 3, 0x670014)
                Call(SetAnimation, ACTOR_SELF, 4, 0x670014)
                Call(SetAnimation, ACTOR_SELF, 5, 0x670014)
                Wait(20)
                Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
                Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 1)
                Call(SetPartFlagBits, ACTOR_SELF, 5, 1, 1)
            EndThread
            Wait(10)
            Call(SetBattleCamTargetingModes, 0, 1, 0)
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            ExecWait(b_area_iwa_buzzar_EVS_FlyToHome)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseDefault
    EndSwitch
    Call(SetBattleCamTargetingModes, 0, 1, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Thread
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(RandInt, 10, LVar3)
        Sub(LVar3, 10)
        Add(LVar1, LVar3)
        Call(FlyPartTo, ACTOR_SELF, 4, LVar0, LVar1, LVar2, 6, 0, 0)
    EndThread
    Thread
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(RandInt, 10, LVar3)
        Add(LVar3, 10)
        Add(LVar1, LVar3)
        Call(FlyPartTo, ACTOR_SELF, 5, LVar0, LVar1, LVar2, 6, 0, 0)
    EndThread
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 6, 0, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 2, 32)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseDefault
            Thread
                Call(SetPartRotation, ACTOR_SELF, 4, 0, 45, 90)
                Call(GetPartOffset, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
                Sub(LVar0, 40)
                Set(LVar1, 2)
                Call(SetPartJumpGravity, ACTOR_SELF, 4, Float(1.5))
                Call(JumpPartTo, ACTOR_SELF, 4, LVar0, LVar1, LVar2, 10, 1)
                Call(SetPartRotation, ACTOR_SELF, 4, 0, 80, 90)
                Wait(8)
                Loop(15)
                    Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 0)
                    Wait(1)
                    Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 1)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Call(SetPartRotation, ACTOR_SELF, 5, 0, 45, -90)
                Call(GetPartOffset, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
                Add(LVar0, 20)
                Set(LVar1, 4)
                Call(SetPartJumpGravity, ACTOR_SELF, 5, Float(1.5))
                Call(JumpPartTo, ACTOR_SELF, 5, LVar0, LVar1, LVar2, 10, 1)
                Call(SetPartRotation, ACTOR_SELF, 5, 0, 90, -90)
                Wait(8)
                Loop(15)
                    Call(SetPartFlagBits, ACTOR_SELF, 5, 1, 0)
                    Wait(1)
                    Call(SetPartFlagBits, ACTOR_SELF, 5, 1, 1)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Call(SetPartRotation, ACTOR_SELF, 3, 0, 45, -90)
                Call(GetPartOffset, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
                Sub(LVar0, 5)
                Set(LVar1, 4)
                Call(SetPartJumpGravity, ACTOR_SELF, 3, Float(1.5))
                Call(JumpPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 10, 1)
                Call(SetPartRotation, ACTOR_SELF, 3, 0, 90, -90)
                Wait(8)
                Loop(15)
                    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
                    Wait(1)
                    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
                    Wait(1)
                EndLoop
            EndThread
            Wait(30)
            Call(YieldTurn)
            ExecWait(b_area_iwa_buzzar_EVS_FlyToHome)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_iwa_buzzar_EVS_Attack_WindBlast = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 13)
    Call(SetBattleCamDist, 180)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 120)
    Call(SetActorSpeed, ACTOR_SELF, Float(1.0))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, 70, LVar2)
    Call(GetAnimation, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseOrEq(0x670001)
        CaseOrEq(0x670002)
        CaseOrEq(0x67000D)
        CaseOrEq(0x670016)
        CaseOrEq(0x670017)
            Loop(0)
                Call(GetPartAnimNotify, ACTOR_SELF, 1, LVar0)
                IfEq(LVar0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x670002)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 10)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0x10000000, 0, 1, 32)
    Switch(LVarA)
        CaseEq(6)
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0x10000000, 0, 1, 32)
            Switch(LVarA)
                CaseEq(6)
                    Call(SetTargetActor, ACTOR_SELF, 0)
                    Wait(8)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x670011)
                    Wait(15)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x670013)
                    Wait(6)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8432)
                    Call(UseBattleCamPreset, 2)
                    Call(MoveBattleCamOver, 50)
                    Thread
                        Call(ShakeCam, 1, 0, 90, Float(0.5))
                    EndThread
                    Call(b_area_iwa_buzzar_StartRumbleWithParams, 70, 100)
                    Thread
                        Loop(20)
                            Call(SetGoalToTarget, ACTOR_SELF)
                            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Add(LVar0, 10)
                            Call(PlayEffect_impl, 43, 2, LVar0, 10, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                            Wait(3)
                        EndLoop
                    EndThread
                    Wait(60)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x670001)
                    IfEq(LVarA, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    Wait(25)
                    ExecWait(b_area_iwa_buzzar_EVS_FlyToHome)
                    Return
                CaseDefault
                    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                    Call(ShowMessageBox, 65, 90)
                    Call(ShowActionHud, 1)
                    Call(LoadActionCommand, 5)
                    Call(action_command_whirlwind_init, 1)
                    Call(SetupMashMeter, 3, 40, 70, 100, 0, 0)
                    Wait(8)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x670011)
                    Wait(15)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x670013)
                    Wait(6)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8432)
                    Call(SetBattleFlagBits, 0x4000, 0)
                    Call(action_command_whirlwind_start, 0, 88, 3)
                    Call(UseBattleCamPreset, 19)
                    Call(SetBattleCamTarget, -25, 60, 0)
                    Call(SetBattleCamDist, 460)
                    Call(SetBattleCamOffsetY, 0)
                    Call(MoveBattleCamOver, 50)
                    Call(b_area_iwa_buzzar_StartRumbleWithParams, 70, 130)
                    Thread
                        Loop(30)
                            Call(SetGoalToTarget, ACTOR_SELF)
                            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Add(LVar0, 10)
                            Call(PlayEffect_impl, 43, 2, LVar0, 10, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                            Wait(3)
                        EndLoop
                    EndThread
                    Thread
                        Call(ShakeCam, 1, 0, 90, Float(0.5))
                    EndThread
                    Call(GetOwnerTarget, LVar3, 0)
                    IfEq(LVar3, 256)
                        Call(TTYD64_GetPartnerHP_API, LVar0)
                    Else
                        Set(LVar0, 1)
                    EndIf
                    IfGt(LVar0, 0)
                        Thread
                            Call(UseIdleAnimation, LVar3, 0)
                            Set(LVar0, 0)
                            Set(LVar1, 3)
                            Loop(93)
                                Call(SetActorYaw, LVar3, LVar0)
                                Add(LVar0, LVar1)
                                Add(LVar1, 1)
                                Wait(1)
                            EndLoop
                            Call(SetActorYaw, LVar3, 0)
                        EndThread
                    EndIf
                    Wait(90)
                    Call(GetActionProgress, LVar1)
                    Call(GetOwnerTarget, LVar3, 0)
                    IfEq(LVar3, 256)
                        Call(TTYD64_GetPartnerHP_API, LVar0)
                    Else
                        Set(LVar0, 1)
                    EndIf
                    IfGt(LVar0, 0)
                        Wait(3)
                        Call(UseIdleAnimation, LVar3, 1)
                        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                        Call(SetGoalToTarget, ACTOR_SELF)
                        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x2000000, 0xFFFF, 0, LVar1, 32)
                    EndIf
                    Call(SetAnimation, ACTOR_SELF, 1, 0x670001)
                    Wait(25)
                    Call(UseBattleCamPreset, 2)
                    Call(MoveBattleCamOver, 20)
                    ExecWait(b_area_iwa_buzzar_EVS_FlyToHome)
                    Return
            EndSwitch
        CaseDefault
    EndSwitch
    Call(ShowMessageBox, 65, 90)
    Call(ShowActionHud, 1)
    Call(LoadActionCommand, 5)
    Call(action_command_whirlwind_init, 1)
    Call(SetupMashMeter, 3, 40, 70, 100, 0, 0)
    Wait(8)
    Call(SetAnimation, ACTOR_SELF, 1, 0x670011)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x670013)
    Wait(6)
    Call(PlaySoundAtActor, ACTOR_SELF, 8432)
    Call(SetBattleFlagBits, 0x4000, 0)
    Call(action_command_whirlwind_start, 0, 88, 3)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, -25, 60, 0)
    Call(SetBattleCamDist, 460)
    Call(SetBattleCamOffsetY, 0)
    Call(MoveBattleCamOver, 50)
    Call(b_area_iwa_buzzar_StartRumbleWithParams, 70, 130)
    Thread
        Loop(30)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 10)
            Call(PlayEffect_impl, 43, 2, LVar0, 10, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(3)
        EndLoop
    EndThread
    Thread
        Call(ShakeCam, 1, 0, 90, Float(0.5))
    EndThread
    Call(GetStatusFlags, 0, LVar1)
    IfNotFlag(LVar1, 0x100000)
        Thread
            Call(UseIdleAnimation, 0, 0)
            Call(SetAnimation, 0, 0, 0x1002E)
            Set(LVar0, 0)
            Set(LVar1, 3)
            Loop(90)
                Call(SetActorYaw, 0, LVar0)
                Add(LVar0, LVar1)
                Add(LVar1, 1)
                Wait(1)
            EndLoop
            Call(SetActorYaw, 0, 0)
        EndThread
    EndIf
    Call(ActorExists, 256, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_GetPartnerHP_API, LVar0)
        IfGt(LVar0, 0)
            Thread
                Call(UseIdleAnimation, 256, 0)
                Set(LVar0, 0)
                Set(LVar1, 3)
                Loop(93)
                    Call(SetActorYaw, 256, LVar0)
                    Add(LVar0, LVar1)
                    Add(LVar1, 1)
                    Wait(1)
                EndLoop
                Call(SetActorYaw, 256, 0)
            EndThread
        EndIf
    EndIf
    Call(FreezeBattleState, 1)
    Wait(90)
    Call(GetActionProgress, LVar1)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x2000000, 0xFFFF, 0, LVar1, 32)
    Call(GetOwnerTarget, LVar3, 0)
    IfEq(LVar3, 256)
        Call(TTYD64_GetPartnerHP_API, LVar0)
    Else
        Set(LVar0, 1)
    EndIf
    IfGt(LVar0, 0)
        Wait(3)
        Call(UseIdleAnimation, 256, 1)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x2000000, 0xFFFF, 0, LVar1, 32)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x670001)
    Wait(25)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    ExecWait(b_area_iwa_buzzar_EVS_FlyToHome)
    Call(FreezeBattleState, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_iwa_cleft_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Call(GetLastElement, LVar0)
            Switch(LVar0)
                CaseFlag(512)
                    ExecWait(TTYD64_iwa_cleft_EVS_FlipOver)
                CaseDefault
                    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
                    IfEq(LVar0, 1)
                        SetConst(LVar1, 0x300009)
                    Else
                        SetConst(LVar1, 0x300008)
                    EndIf
                    SetConst(LVar0, 1)
                    ExecWait(Ref(EVS_Enemy_Hit))
            EndSwitch
        EndCaseGroup
        CaseEq(14)
            Call(GetLastElement, LVar0)
            Switch(LVar0)
                CaseFlag(512)
                    ExecWait(TTYD64_iwa_cleft_EVS_FlipOver)
                CaseDefault
                    Call(SetPartEventBits, ACTOR_SELF, 1, 512, 1)
                    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
                    IfEq(LVar0, 1)
                        SetConst(LVar0, 1)
                        SetConst(LVar1, 0x300009)
                        SetConst(LVar2, -1)
                        ExecWait(Ref(EVS_Enemy_BurnHit))
                    Else
                        SetConst(LVar0, 1)
                        SetConst(LVar1, 0x300008)
                        SetConst(LVar2, -1)
                        ExecWait(Ref(EVS_Enemy_BurnHit))
                    EndIf
                    Call(SetPartEventBits, ACTOR_SELF, 1, 512, 0)
            EndSwitch
        CaseEq(36)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300009)
                SetConst(LVar2, -1)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300009)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300008)
                SetConst(LVar2, -1)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300008)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(11)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar1, 0x300009)
            Else
                SetConst(LVar1, 0x300008)
            EndIf
            SetConst(LVar0, 1)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300009)
                ExecWait(Ref(EVS_Enemy_SpinSmashHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300009)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300008)
                ExecWait(Ref(EVS_Enemy_SpinSmashHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300008)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x300008)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x300008)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x300007)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x300008)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x300008)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseEq(27)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x300018)
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
                SetConst(LVar1, 0x300003)
            Else
                SetConst(LVar1, 0x300002)
            EndIf
            SetConst(LVar0, 1)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300009)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300009)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300008)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300008)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300002)
                ExecWait(Ref(EVS_Enemy_Recover))
            EndIf
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300003)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300007)
                SetConst(LVar2, 0x300008)
                ExecWait(Ref(EVS_Enemy_ScareAway))
                Return
            EndIf
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x30000F)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x30000F)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x300008)
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
EvtScript TTYD64_iwa_cleft_EVS_Attack_Tackle = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x300010)
    Wait(10)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x300011)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, -5)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x300000)
    Wait(8)
    Call(PlaySoundAtActor, ACTOR_SELF, 8401)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 2, 16)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x300011)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 100)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 45)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300008)
            Wait(15)
            Wait(8)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300007)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300002)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x300011)
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Call(SetAnimation, ACTOR_SELF, 1, 0x300002)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x300002)
            Wait(5)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300007)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x300002)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_iwa_buzzar_EVS_Attack_ClawSwipe = {
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
    Call(SetBattleCamDist, 240)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 60, 15, 0)
    Call(GetAnimation, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseOrEq(0x670001)
        CaseOrEq(0x670002)
        CaseOrEq(0x67000D)
        CaseOrEq(0x670016)
        CaseOrEq(0x670017)
            Loop(0)
                Call(GetPartAnimNotify, ACTOR_SELF, 1, LVar0)
                IfEq(LVar0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x670002)
    Call(FlyToGoal, ACTOR_SELF, 0, -15, 10)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 3, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(PlaySoundAtActor, ACTOR_SELF, 8433)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8434)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -45, -20, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x670018)
            Call(FlyToGoal, ACTOR_SELF, 12, -12, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x670001)
            Wait(10)
            Call(UseBattleCamPreset, 2)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            ExecWait(b_area_iwa_buzzar_EVS_FlyToHome)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 8433)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8434)
    Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -5, -10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x670018)
    Call(FlyToGoal, ACTOR_SELF, 8, 0, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 3, 32)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(GetAnimation, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(0x670001)
                CaseOrEq(0x670002)
                CaseOrEq(0x67000D)
                CaseOrEq(0x670016)
                CaseOrEq(0x670017)
                    Loop(0)
                        Call(GetPartAnimNotify, ACTOR_SELF, 1, LVar0)
                        IfEq(LVar0, 1)
                            BreakLoop
                        EndIf
                        Wait(1)
                    EndLoop
                EndCaseGroup
            EndSwitch
            Call(ResetActorSounds, ACTOR_SELF, 1)
            Call(SetActorSounds, ACTOR_SELF, 5, -14, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x670002)
            Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            ExecWait(b_area_iwa_buzzar_EVS_FlyToHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_iwa_monty_mole_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVarB, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    EndIf
    ChildThread
        Call(PlaySoundAtActor, ACTOR_SELF, 802)
        Wait(20)
        Call(PlaySoundAtActor, ACTOR_SELF, 801)
    EndChildThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x2F0004)
    Wait(37)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Wait(1)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 3, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Else
        Call(SetPartScale, ACTOR_SELF, 3, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(PlaySoundAtPart, ACTOR_SELF, 3, 1000)
    Call(SetPartSounds, ACTOR_SELF, 3, 1, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetTargetActor, ACTOR_SELF, LVarB)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 100)
            Set(LVar1, -5)
            Call(SetPartMoveSpeed, ACTOR_SELF, 3, Float(12.0))
            Call(SetPartJumpGravity, ACTOR_SELF, 3, Float(0.099609375))
            Call(SetAnimation, ACTOR_SELF, 3, 0x2F000F)
            Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 0, 30, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(YieldTurn)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetTargetActor, ACTOR_SELF, LVarB)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartMoveSpeed, ACTOR_SELF, 3, Float(12.0))
    Call(SetPartJumpGravity, ACTOR_SELF, 3, Float(0.099609375))
    Call(SetAnimation, ACTOR_SELF, 3, 0x2F000F)
    Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 0, 20, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(GetOwnerTarget, LVar3, 0)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Sub(LVar0, 55)
            Set(LVar1, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, 3, Float(6.0))
            Call(SetPartJumpGravity, ACTOR_SELF, 3, Float(0.099609375))
            Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 0, 25, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, 3, Float(4.0))
            Sub(LVar0, 20)
            Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 0, 21, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_iwa_cleft_EVS_TryGettingUp = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
    Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x300003)
    Wait(20)
    Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x300005)
    Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    IfGt(LVar0, 0)
        Sub(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 1, LVar0)
    Else
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x300003)
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
        Call(b_area_iwa_cleft_StartRumbleWithParams, 200, 10)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(1.0))
        EndThread
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
        Call(SetActorPos, ACTOR_SELF, LVar0, 0, LVar2)
        Call(SetActorVar, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x300002)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_iwa_cleft_UprightAnims))
        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_iwa_cleft_UprightDefenseTable))
        Call(SetTargetOffset, ACTOR_SELF, 1, 0, 22)
        Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, -10)
        Call(SetPartEventBits, ACTOR_SELF, 1, 16, 1)
        Wait(1)
        Call(b_area_iwa_cleft_SetSpinSmashable, 1)
        Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_iwa_cleft_EVS_FlipOver = {
    Call(SetActorVar, ACTOR_SELF, 0, 1)
    Call(SetActorVar, ACTOR_SELF, 1, 2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x300007)
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
    Call(b_area_iwa_cleft_StartRumbleWithParams, 200, 10)
    Thread
        Call(ShakeCam, 1, 0, 5, Float(1.0))
    EndThread
    Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 40, 8, Float(0.0), 20, 0, 0, 0, 0, 0)
    Call(SetActorPos, ACTOR_SELF, LVar0, 0, LVar2)
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x300003)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_iwa_cleft_ToppledAnims))
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_iwa_cleft_ToppledDefenseTable))
    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 15)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, -7)
    Call(SetPartEventBits, ACTOR_SELF, 1, 16, 0)
    Call(b_area_iwa_cleft_SetSpinSmashable, 0)
    Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_iwa_buzzar_EVS_LiftMario = {
    Call(GetAnimation, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseOrEq(0x670001)
        CaseOrEq(0x670002)
        CaseOrEq(0x67000D)
        CaseOrEq(0x670016)
        CaseOrEq(0x670017)
            Loop(0)
                Call(GetPartAnimNotify, ACTOR_SELF, 1, LVar0)
                IfEq(LVar0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        EndCaseGroup
    EndSwitch
    Call(ResetActorSounds, ACTOR_SELF, 1)
    Call(SetActorSounds, ACTOR_SELF, 5, -8, 0)
    ChildThread
        Loop(0)
            Call(b_area_iwa_buzzar_StartRumbleWithParams, 100, 10)
            Wait(10)
        EndLoop
    EndChildThread
    ChildThread
        Call(GetOwnerTarget, LVar3, 0)
        Call(SetActorSpeed, LVar3, Float(5.0))
        Call(SetActorJumpGravity, LVar3, Float(0.099609375))
        Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
        Add(LVar1, 180)
        Call(SetGoalPos, LVar3, LVar0, LVar1, LVar2)
        Call(FlyToGoal, LVar3, 99, 0, 0)
    EndChildThread
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.099609375))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 180)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 99, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_iwa_buzzar_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetActorVar, ACTOR_SELF, 0, 2)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            ExecWait(TTYD64_iwa_buzzar_EVS_Attack_WindBlast)
        CaseEq(2)
            Call(SetActorVar, ACTOR_SELF, 0, 3)
            ExecWait(TTYD64_iwa_buzzar_EVS_Attack_ClawSwipe)
        CaseEq(4)
            Call(SetActorVar, ACTOR_SELF, 0, 5)
            ExecWait(TTYD64_iwa_buzzar_EVS_Attack_FeatherFling)
        CaseDefault
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 5)
                Set(LVar0, 0)
            Else
                Add(LVar0, 1)
            EndIf
            Call(SetActorVar, ACTOR_SELF, 0, LVar0)
            ExecWait(TTYD64_iwa_buzzar_EVS_Attack_GrappleDrop)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_iwa_EVS_8021FEEC = {
    Call(GetOwnerTarget, LVar3, 0)
    IfEq(LVar3, 256)
        Call(PartnerIsFlying, LVar0)
        IfEq(LVar0, 0)
            Set(LVar0, 4)
            Exec(TTYD64_SetPartnerAnimation_Battle)
            Call(GetCurrentPartnerID, LVar4)
            Call(GetActorPos, 256, LVar0, LVar1, LVar2)
            Switch(LVar4)
                CaseEq(6)
                    Add(LVar1, 23)
                CaseEq(4)
                    Add(LVar1, 27)
                CaseDefault
                    Add(LVar1, 17)
            EndSwitch
            Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
            Call(FlyToGoal, 256, 6, 0, 0)
        EndIf
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_iwa_buzzar_EVS_Init = {
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_iwa_buzzar_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_iwa_buzzar_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_iwa_buzzar_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_iwa_buzzar_EVS_HandlePhase))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 40)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

Battle TTYD64_iwa_Formations[] = {
    { .name = "\267\363\250\342\363",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_iwa_Formation_00,
      .stage = &TTYD64_iwa_iwa_01,
      .onBattleStart = NULL },
    { .name = "\267\363\250\342\363x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_iwa_Formation_01,
      .stage = &TTYD64_iwa_iwa_01,
      .onBattleStart = NULL },
    { .name = "\267\363\250\342\363x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_iwa_Formation_02,
      .stage = &TTYD64_iwa_iwa_01,
      .onBattleStart = NULL },
    { .name = "\267\363\250\342\363,\301\347\355\327\374",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_iwa_Formation_03,
      .stage = &TTYD64_iwa_iwa_01,
      .onBattleStart = NULL },
    { .name = "\267\363\250\342\363,\301\347\355\327\374x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_iwa_Formation_04,
      .stage = &TTYD64_iwa_iwa_01,
      .onBattleStart = NULL },
    { .name = "\301\347\355\327\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_iwa_Formation_05,
      .stage = &TTYD64_iwa_iwa_01,
      .onBattleStart = NULL },
    { .name = "\301\347\355\327\374x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_iwa_Formation_06,
      .stage = &TTYD64_iwa_iwa_01,
      .onBattleStart = NULL },
    { .name = "\301\347\355\327\374x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_iwa_Formation_07,
      .stage = &TTYD64_iwa_iwa_01,
      .onBattleStart = NULL },
    { .name = "\301\347\355\327\374x\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_iwa_Formation_08,
      .stage = &TTYD64_iwa_iwa_01,
      .onBattleStart = NULL },
    { .name = "\301\347\355\327\374,\267\363\250\342\363",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_iwa_Formation_09,
      .stage = &TTYD64_iwa_iwa_01,
      .onBattleStart = NULL },
    { .name = "\301\347\355\327\374x\022,\267\363\250\342\363",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_iwa_Formation_0A,
      .stage = &TTYD64_iwa_iwa_01,
      .onBattleStart = NULL },
    { .name = "\301\347\355\327\374,\267\363\250\342\363,\301\347\355\327\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_iwa_Formation_0B,
      .stage = &TTYD64_iwa_iwa_01,
      .onBattleStart = NULL },
    { .name = "\262\374\317\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_iwa_Formation_0C,
      .stage = &b_area_iwa_iwa_02,
      .onBattleStart = NULL },
    { .name = "\263\326\355\363",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_iwa_Formation_0D,
      .stage = &b_area_iwa_iwa_02,
      .onBattleStart = NULL },
    {},
};

ActorPartBlueprint TTYD64_iwa_buzzar_ActorParts[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -20, 60 },
        .opacity = 255,
        .idleAnimations = TTYD64_iwa_buzzar_DefaultAnims,
        .defenseTable = b_area_iwa_buzzar_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800001,
        .index = 2,
        .posOffset = { 0, 31, 0 },
        .targetOffset = { -14, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_iwa_buzzar_DefaultAnims,
        .defenseTable = b_area_iwa_buzzar_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -14 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_iwa_buzzar_FeatherAnims,
        .defenseTable = b_area_iwa_buzzar_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_iwa_buzzar_FeatherAnims,
        .defenseTable = b_area_iwa_buzzar_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_iwa_buzzar_FeatherAnims,
        .defenseTable = b_area_iwa_buzzar_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_iwa_Formation_08[] = {
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
};

ActorPartBlueprint TTYD64_iwa_monty_mole_ActorParts[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 16 },
        .opacity = 255,
        .idleAnimations = TTYD64_iwa_monty_mole_DefaultAnims,
        .defenseTable = b_area_iwa_monty_mole_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -7 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x80800001,
        .index = 2,
        .posOffset = { 0, 0, -15 },
        .targetOffset = { -2, 12 },
        .opacity = 255,
        .idleAnimations = TTYD64_iwa_monty_mole_DefaultAnims,
        .defenseTable = b_area_iwa_monty_mole_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -7 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_iwa_monty_mole_RockAnims,
        .defenseTable = b_area_iwa_monty_mole_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_iwa_cleft_EVS_Init = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_iwa_cleft_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_iwa_cleft_EVS_TakeTurn))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_iwa_cleft_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_iwa_monty_mole_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_iwa_monty_mole_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_iwa_monty_mole_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_iwa_monty_mole_EVS_HandleEvent))
    Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_iwa_cleft_EVS_TakeTurn = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_iwa_cleft_EVS_TryGettingUp)
    Else
        ExecWait(TTYD64_iwa_cleft_EVS_Attack_Tackle)
    EndIf
    Return
    End
};
// clang-format on

FormationRow TTYD64_iwa_Formation_0A[] = {
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_iwa_cleft,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
};

FormationRow TTYD64_iwa_Formation_0D[] = {
    { .actor = &TTYD64_iwa_cleft,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_iwa_whacka, .home = { .index = 2 }, .priority = 8, .var0 = 0, .var1 = 0, .var2 = 0, .var3 = 0 },
};

FormationRow TTYD64_iwa_Formation_0B[] = {
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_iwa_cleft,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
};

FormationRow TTYD64_iwa_Formation_04[] = {
    { .actor = &TTYD64_iwa_cleft,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
};

FormationRow TTYD64_iwa_Formation_02[] = {
    { .actor = &TTYD64_iwa_cleft,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
    { .actor = &TTYD64_iwa_cleft,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
    { .actor = &TTYD64_iwa_cleft,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
};

FormationRow TTYD64_iwa_Formation_07[] = {
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
};

s32 TTYD64_iwa_cleft_UprightAnims[] = {
    1,  0x300002, 7, 0x300000, 6, 0x30000C, 9, 0x300002, 8, 0x300000,
    11, 0x300002, 5, 0x300000, 4, 0x30000E, 3, 0x30000E, 0,
};

s32 TTYD64_iwa_whacka_DefaultAnims[] = {
    1,  0x920001, 7, 0x920000, 6, 0x920001, 9, 0x920001, 8, 0x920000,
    11, 0x920001, 5, 0x920000, 4, 0x920001, 3, 0x920001, 0,
};

s32 TTYD64_iwa_monty_mole_DefaultAnims[] = {
    1,  0x2F0001, 7, 0x2F0000, 6, 0x2F0014, 9, 0x2F0001, 8, 0x2F0000,
    11, 0x2F0001, 5, 0x2F0000, 4, 0x2F0014, 3, 0x2F0014, 0,
};

s32 TTYD64_iwa_whacka_DefaultAnims_8022136C[] = {
    1,  0x920001, 7, 0x920000, 6, 0x920001, 9, 0x920001, 8, 0x920000,
    11, 0x920001, 5, 0x920000, 4, 0x920001, 3, 0x920001, 0,
};

s32 TTYD64_iwa_cleft_ToppledAnims[] = {
    1,  0x300005, 7, 0x300001, 6, 0x30000D, 9, 0x300005, 8, 0x300001,
    11, 0x300005, 5, 0x300001, 4, 0x30000F, 3, 0x30000F, 0,
};

s32 TTYD64_iwa_buzzar_DefaultAnims[] = {
    1, 0x670001, 7, 0x670000, 6, 0x670019, 8, 0x670000, 11, 0x67000C, 5, 0x67000C, 4, 0x67000C, 10, 0x670001, 0,
};

FormationRow TTYD64_iwa_Formation_01[] = {
    { .actor = &TTYD64_iwa_cleft,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
    { .actor = &TTYD64_iwa_cleft,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
};

FormationRow TTYD64_iwa_Formation_03[] = {
    { .actor = &TTYD64_iwa_cleft,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
};

FormationRow TTYD64_iwa_Formation_09[] = {
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_iwa_cleft,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
};

FormationRow TTYD64_iwa_Formation_06[] = {
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
};

ActorBlueprint TTYD64_iwa_whacka = {
    .flags = 0x40004,
    .maxHP = 99,
    .type = 0xD0,
    .level = 0,
    .partCount = 1,
    .partsData = TTYD64_iwa_whacka_ActorParts,
    .initScript = &b_area_iwa_whacka_EVS_Init,
    .statusTable = b_area_iwa_whacka_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 50,
    .coinReward = 0,
    .size = { 47, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -20, 40 },
    .statusTextOffset = { 10, 30 },
};

ActorBlueprint TTYD64_iwa_whacka_802216D8 = {
    .flags = 0x40004,
    .maxHP = 99,
    .type = 0xD0,
    .level = 0,
    .partCount = 1,
    .partsData = TTYD64_iwa_whacka_ActorParts_80221814,
    .initScript = &b_area_iwa_whacka_EVS_Init,
    .statusTable = b_area_iwa_whacka_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 50,
    .coinReward = 0,
    .size = { 47, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -20, 40 },
    .statusTextOffset = { 10, 30 },
};

ActorBlueprint TTYD64_iwa_cleft = {
    .flags = 0x0,
    .maxHP = 2,
    .type = 0x11,
    .level = 10,
    .partCount = 1,
    .partsData = TTYD64_iwa_cleft_ActorParts,
    .initScript = &TTYD64_iwa_cleft_EVS_Init,
    .statusTable = b_area_iwa_cleft_StatusTable,
    .escapeChance = 80,
    .airLiftChance = 40,
    .hurricaneChance = 40,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 2,
    .size = { 44, 36 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_iwa_buzzar = {
    .flags = 0x200,
    .maxHP = 40,
    .type = 0xA0,
    .level = 35,
    .partCount = 5,
    .partsData = TTYD64_iwa_buzzar_ActorParts,
    .initScript = &TTYD64_iwa_buzzar_EVS_Init,
    .statusTable = b_area_iwa_buzzar_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 78, 74 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -35, 65 },
    .statusTextOffset = { 1, 58 },
};

Stage TTYD64_iwa_iwa_01 = {
    .texture = "iwa_tex",
    .shape = "iwa_bt01_shape",
    .hit = "iwa_bt01_hit",
    .preBattle = &b_area_iwa_iwa_01_EVS_PreBattle,
    .postBattle = &b_area_iwa_iwa_01_EVS_PostBattle,
    .bg = "iwa_bg",
    .foregroundModelList = b_area_iwa_iwa_01_ForegroundModels,
    .stageEnemyCount = 1,
    .stageFormation = (Formation*) TTYD64_iwa_iwa_01_WhackaFormation,
    .stageEnemyChance = 512,
};

ActorBlueprint TTYD64_iwa_monty_mole = {
    .flags = 0x0,
    .maxHP = 3,
    .type = 0x12,
    .level = 8,
    .partCount = 3,
    .partsData = TTYD64_iwa_monty_mole_ActorParts,
    .initScript = &TTYD64_iwa_monty_mole_EVS_Init,
    .statusTable = b_area_iwa_monty_mole_StatusTable,
    .escapeChance = 80,
    .airLiftChance = 70,
    .hurricaneChance = 50,
    .spookChance = 85,
    .upAndAwayChance = 95,
    .spinSmashReq = 4,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 34, 18 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorPartBlueprint TTYD64_iwa_whacka_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 30 },
        .opacity = 255,
        .idleAnimations = TTYD64_iwa_whacka_DefaultAnims,
        .defenseTable = b_area_iwa_whacka_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -5 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_iwa_whacka_ActorParts_80221814[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 30 },
        .opacity = 255,
        .idleAnimations = TTYD64_iwa_whacka_DefaultAnims_8022136C,
        .defenseTable = b_area_iwa_whacka_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -5 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_iwa_cleft_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 22 },
        .opacity = 255,
        .idleAnimations = TTYD64_iwa_cleft_UprightAnims,
        .defenseTable = b_area_iwa_cleft_UprightDefenseTable,
        .eventFlags = 0x10,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

StageListRow TTYD64_iwa_Stages[] = {
    { .name = "iwa_01", .stage = &TTYD64_iwa_iwa_01 },
    { .name = "iwa_01b", .stage = &b_area_iwa_iwa_01b },
    { .name = "iwa_02", .stage = &b_area_iwa_iwa_02 },
    {},
};

FormationRow TTYD64_iwa_iwa_01_WhackaFormation[] = {
    { .actor = &TTYD64_iwa_whacka_802216D8,
      .home = { .vec = &b_area_iwa_iwa_01_WhackaPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_iwa_Formation_0C[] = {
    { .actor = &TTYD64_iwa_buzzar,
      .home = { .vec = &b_area_iwa_BossPos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_iwa_Formation_00[] = {
    { .actor = &TTYD64_iwa_cleft,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
};

FormationRow TTYD64_iwa_Formation_05[] = {
    { .actor = &TTYD64_iwa_monty_mole,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
};

void TTYD64_InstallBattles_iwa(void) {
    Mod_SetBattleList("TTYD64", 9, TTYD64_iwa_Formations);
    Mod_SetStageList("TTYD64", 9, TTYD64_iwa_Stages);
}
