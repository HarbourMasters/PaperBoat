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
API_CALLABLE(DispatchEvent);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyToGoal);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetEncounterTrigger);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetIndexFromHome);
API_CALLABLE(GetLastDamage);
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
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActorDecoration);
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
API_CALLABLE(SetDamageSource);
API_CALLABLE(SetDefenseTable);
API_CALLABLE(SetEnemyHP);
API_CALLABLE(SetEnemyTargetOffset);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetIdleGoal);
API_CALLABLE(SetPartDispOffset);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartFlags);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartSize);
API_CALLABLE(SetPartYaw);
API_CALLABLE(SetProjectileTargetOffset);
API_CALLABLE(SetStatusTable);
API_CALLABLE(SetTargetActor);
API_CALLABLE(SetTargetOffset);
API_CALLABLE(ShakeCam);
API_CALLABLE(StopSound);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseBattleCamPresetImmediately);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
API_CALLABLE(b_area_nok_downed_goomba_CalculateArcsinDeg);
API_CALLABLE(b_area_nok_fuzzy_SpawnDrainHealthContinueFX);
API_CALLABLE(b_area_nok_fuzzy_SpawnDrainHealthStartFX);
API_CALLABLE(b_area_nok_goomba_CalculateArcsinDeg);
API_CALLABLE(b_area_nok_kent_c_koopa_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_nok_kent_c_koopa_StartRumbleWithParams);
API_CALLABLE(b_area_nok_paratroopa_StartRumbleWithParams);
API_CALLABLE(b_area_nok_spiked_goomba_CalculateArcsinDeg);
API_CALLABLE(func_8027D434);
extern s32 b_area_nok_fuzzy_DefenseTable[];
extern EvtScript b_area_nok_fuzzy_EVS_Idle;
extern s32 b_area_nok_fuzzy_StatusTable[];
extern s32 b_area_nok_goomba_DefenseTable[];
extern s32 b_area_nok_goomba_StatusTable[];
extern s32 b_area_nok_kent_c_koopa_CoinAnims[];
extern EvtScript b_area_nok_kent_c_koopa_EVS_HandleEvent;
extern EvtScript b_area_nok_kent_c_koopa_EVS_HandlePhase;
extern EvtScript b_area_nok_kent_c_koopa_EVS_Idle;
extern EvtScript b_area_nok_kent_c_koopa_EVS_KentC_GoHome;
extern s32 b_area_nok_kent_c_koopa_FlippedDefense[];
extern s32 b_area_nok_kent_c_koopa_FlippedTailDefense[];
extern s32 b_area_nok_kent_c_koopa_NormalDefense[];
extern s32 b_area_nok_kent_c_koopa_StatusTable[];
extern EvtScript b_area_nok_koopa_troopa_EVS_UpdateTargetOffsets;
extern u8 b_area_nok_koopa_troopa_FlipPosOffsets[];
extern s32 b_area_nok_koopa_troopa_FlippedDefense[];
extern s32 b_area_nok_koopa_troopa_StatusTable[];
extern Stage b_area_nok_nok_02;
extern s32 b_area_nok_paragoomba_DownedStatusTable[];
extern EvtScript b_area_nok_paragoomba_EVS_Paragoomba_GoHome;
extern s32 b_area_nok_paragoomba_FlyingDefense[];
extern s32 b_area_nok_paragoomba_FlyingStatusTable[];
extern s32 b_area_nok_paragoomba_LeftWingAnims[];
extern s32 b_area_nok_paragoomba_RightWingAnims[];
extern s32 b_area_nok_paratroopa_DownedDefense[];
extern s32 b_area_nok_paratroopa_DownedStatusTable[];
extern EvtScript b_area_nok_paratroopa_EVS_Downed_UpdateTargetOffsets;
extern EvtScript b_area_nok_paratroopa_EVS_FlyHome;
extern EvtScript b_area_nok_paratroopa_EVS_Flying_HandlePhase;
extern EvtScript b_area_nok_paratroopa_EVS_Flying_UpdateTargetOffsets;
extern u8 b_area_nok_paratroopa_FlipPosOffsets[];
extern s32 b_area_nok_paratroopa_FlippedDefense[];
extern s32 b_area_nok_paratroopa_FlyingDefense[];
extern s32 b_area_nok_paratroopa_FlyingStatusTable[];
extern s32 b_area_nok_spiked_goomba_StatusTable[];
extern EvtScript TTYD64_nok_fuzzy_EVS_TakeTurn;
extern EvtScript TTYD64_nok_kent_c_koopa_EVS_Attack_ShellToss;
extern EvtScript TTYD64_nok_spiked_goomba_EVS_TakeTurn;
extern EvtScript TTYD64_nok_paratroopa_EVS_Downed_TakeTurn;
extern EvtScript TTYD64_nok_koopa_troopa_EVS_TakeTurn;
extern EvtScript TTYD64_nok_downed_goomba_EVS_TakeTurn;
extern EvtScript TTYD64_nok_goomba_EVS_TakeTurn;
extern EvtScript TTYD64_nok_kent_c_koopa_EVS_Attack_HeavyStomp;
extern EvtScript TTYD64_nok_koopa_troopa_EVS_HandleEvent;
extern EvtScript TTYD64_nok_paratroopa_EVS_Downed_HandleEvent;
extern EvtScript TTYD64_nok_paratroopa_EVS_Flying_TakeTurn;
extern EvtScript TTYD64_nok_paragoomba_EVS_TakeTurn;
extern EvtScript TTYD64_nok_spiked_goomba_EVS_HandleEvent;
extern EvtScript TTYD64_nok_kent_c_koopa_EVS_TakeTurn;
extern EvtScript TTYD64_nok_paratroopa_EVS_Flying_HandleEvent;
extern EvtScript TTYD64_nok_downed_goomba_EVS_HandleEvent;
extern EvtScript TTYD64_nok_goomba_EVS_HandleEvent;
extern EvtScript TTYD64_nok_fuzzy_EVS_HandleEvent;
extern EvtScript TTYD64_nok_paragoomba_EVS_HandleEvent;
extern EvtScript TTYD64_nok_paratroopa_EVS_KnockDown;
extern EvtScript TTYD64_nok_paragoomba_EVS_KnockDown;
extern EvtScript TTYD64_nok_koopa_troopa_EVS_Idle;
extern EvtScript TTYD64_nok_paratroopa_EVS_Downed_Idle;
extern EvtScript TTYD64_nok_paratroopa_EVS_Flying_Idle;
extern EvtScript TTYD64_nok_goomba_EVS_Idle;
extern EvtScript TTYD64_nok_downed_goomba_EVS_Idle;
extern EvtScript TTYD64_nok_spiked_goomba_EVS_Idle;
extern EvtScript TTYD64_nok_paragoomba_EVS_Idle;
extern EvtScript TTYD64_nok_kent_c_koopa_EVS_Init;
extern EvtScript TTYD64_nok_paratroopa_EVS_Flying_Init;
extern EvtScript TTYD64_nok_paratroopa_EVS_Downed_Init;
extern EvtScript TTYD64_nok_koopa_troopa_EVS_Init;
extern EvtScript TTYD64_nok_goomba_EVS_Init;
extern EvtScript TTYD64_nok_fuzzy_EVS_Init;
extern EvtScript TTYD64_nok_downed_goomba_EVS_Init;
extern EvtScript TTYD64_nok_fuzzy_EVS_Init_8022B3D0;
extern EvtScript TTYD64_nok_fuzzy_EVS_Init_8022B6C8;
extern ActorBlueprint TTYD64_nok_koopa_troopa;
extern ActorBlueprint TTYD64_nok_spiked_goomba;
extern ActorBlueprint TTYD64_nok_paragoomba;
extern ActorBlueprint TTYD64_nok_goomba;
extern ActorBlueprint TTYD64_nok_fuzzy;
extern ActorBlueprint TTYD64_nok_paratroopa;
extern ActorBlueprint TTYD64_nok_kent_c_koopa;
extern Battle TTYD64_nok_Formations[];
extern ActorPartBlueprint TTYD64_nok_kent_c_koopa_ActorParts[];
extern ActorPartBlueprint TTYD64_nok_paragoomba_ActorParts[];
extern FormationRow TTYD64_nok_Formation_10[];
extern FormationRow TTYD64_nok_Formation_14[];
extern FormationRow TTYD64_nok_Formation_17[];
extern FormationRow TTYD64_nok_Formation_07[];
extern ActorPartBlueprint TTYD64_nok_paratroopa_ActorParts[];
extern FormationRow TTYD64_nok_Formation_0A[];
extern FormationRow TTYD64_nok_Formation_0D[];
extern FormationRow TTYD64_nok_Formation_0E[];
extern FormationRow TTYD64_nok_Formation_0C[];
extern FormationRow TTYD64_nok_Formation_0F[];
extern FormationRow TTYD64_nok_Formation_13[];
extern FormationRow TTYD64_nok_Formation_05[];
extern FormationRow TTYD64_nok_Formation_06[];
extern s32 TTYD64_nok_paratroopa_DownedAnims[];
extern s32 TTYD64_nok_koopa_troopa_FlippedAnims[];
extern s32 TTYD64_nok_paratroopa_DownedFlippedAnims[];
extern s32 TTYD64_nok_paragoomba_DefaultAnims[];
extern s32 TTYD64_nok_spiked_goomba_DefaultAnims[];
extern s32 TTYD64_nok_spiked_goomba_ShuffleAnims[];
extern s32 TTYD64_nok_goomba_ShuffleAnims[];
extern s32 TTYD64_nok_fuzzy_DefaultAnims[];
extern s32 TTYD64_nok_goomba_DefaultAnims[];
extern s32 TTYD64_nok_kent_c_koopa_DefaultAnims[];
extern s32 TTYD64_nok_paratroopa_FlyingShuffleAnims[];
extern s32 TTYD64_nok_paratroopa_DownedShuffleAnims[];
extern s32 TTYD64_nok_downed_goomba_ShuffleAnims[];
extern s32 TTYD64_nok_paratroopa_WingAnims[];
extern s32 TTYD64_nok_paratroopa_FlyingAnims[];
extern s32 TTYD64_nok_paratroopa_DownedAnims_8022B630[];
extern s32 TTYD64_nok_downed_goomba_DefaultAnims[];
extern s32 TTYD64_nok_paragoomba_ShuffleAnims[];
extern s32 TTYD64_nok_koopa_troopa_ShuffleAnims[];
extern FormationRow TTYD64_nok_Formation_0B[];
extern FormationRow TTYD64_nok_Formation_11[];
extern FormationRow TTYD64_nok_Formation_12[];
extern FormationRow TTYD64_nok_Formation_16[];
extern FormationRow TTYD64_nok_Formation_00[];
extern FormationRow TTYD64_nok_Formation_01[];
extern FormationRow TTYD64_nok_Formation_04[];
extern FormationRow TTYD64_nok_Formation_02[];
extern FormationRow TTYD64_nok_Formation_03[];
extern FormationRow TTYD64_nok_Formation_08[];
extern FormationRow TTYD64_nok_Formation_09[];
extern ActorPartBlueprint TTYD64_nok_goomba_ActorParts[];
extern ActorPartBlueprint TTYD64_nok_koopa_troopa_ActorParts[];
extern ActorPartBlueprint TTYD64_nok_spiked_goomba_ActorParts[];
extern ActorPartBlueprint TTYD64_nok_fuzzy_ActorParts[];
extern FormationRow TTYD64_nok_Formation_15[];
extern FormationRow TTYD64_nok_Formation_18[];

// clang-format off
EvtScript TTYD64_nok_fuzzy_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
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
        Goto(100)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0001)
    Label(100)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0004)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 9, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 8, 0)
    Wait(5)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 5)
            Set(LVar1, 0)
            Sub(LVar2, 5)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0005)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 11, 0, 1, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0009)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 15)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Wait(4)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            ExecWait(Ref(EVS_Enemy_HopToPos))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseEq(7)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 8192)
                Set(LFlag0, 0)
            Else
                Set(LFlag0, 1)
            EndIf
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -3, -12, -15)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0005)
    Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
    IfEq(LFlag0, 1)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 0, 32)
        Return
    EndIf
    Wait(10)
    Call(GetOwnerTarget, LVar0, 0)
    Switch(LVar0)
        CaseEq(0)
            Call(UseIdleAnimation, 0, 0)
            Call(SetAnimation, 0, 0, 0x3000C)
        CaseEq(256)
            Call(UseIdleAnimation, 256, 0)
            Set(LVar0, 4)
            Exec(TTYD64_SetPartnerAnimation_Battle)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 992)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0007)
    Wait(21)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0000)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 330)
    Call(PlaySoundAtActor, ACTOR_SELF, 992)
    Call(SetActorDispOffset, ACTOR_SELF, -3, -2, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
    Wait(2)
    Call(SetActorScale, ACTOR_SELF, Float(0.599609375), Float(1.599609375), Float(1.0))
    Wait(10)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 1, 32)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0001)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(GetOwnerTarget, LVar0, 0)
            Call(GetLastDamage, LVar0, LVar3)
            IfNe(LVar3, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8301)
                Call(PlaySoundAtActor, ACTOR_SELF, 532)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 10)
                Call(b_area_nok_fuzzy_SpawnDrainHealthStartFX, LVar0, LVar1, LVar2, LVar3)
                Thread
                    Wait(15)
                    Call(PlaySoundAtActor, ACTOR_SELF, 604)
                    Call(b_area_nok_fuzzy_SpawnDrainHealthContinueFX, LVar0, LVar1, LVar2, LVar3)
                EndThread
                Add(LVar0, 20)
                Add(LVar1, 20)
                Call(PlayEffect_impl, 64, 0, LVar0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0)
                Call(GetActorHP, ACTOR_SELF, LVar0)
                Add(LVar0, LVar3)
                Call(SetEnemyHP, ACTOR_SELF, LVar0)
            EndIf
            Thread
                Call(SetActorScale, ACTOR_SELF, Float(1.599609375), Float(0.599609375), Float(1.0))
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 330)
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 300)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 270)
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(0.7001953125), Float(1.0))
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 240)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 210)
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 180)
                Wait(2)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(0.7001953125), Float(1.0))
                Wait(2)
                Call(SetActorScale, ACTOR_SELF, Float(1.2001953125), Float(0.5), Float(1.0))
            EndThread
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetActorScale, ACTOR_SELF, Float(1.400390625), Float(0.2001953125), Float(1.0))
            Wait(1)
            Thread
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(1.2001953125), Float(0.5), Float(1.0))
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 150)
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 120)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 90)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 60)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(5)
            Call(YieldTurn)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            ExecWait(Ref(EVS_Enemy_HopToPos))
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0001)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_kent_c_koopa_EVS_Attack_ShellToss = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 14)
    Call(SetBattleCamDist, 200)
    Call(SetBattleCamOffsetY, 20)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 25)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x47000B)
    Wait(10)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 4)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(3)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(2)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
    EndThread
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 880)
    Call(SetAnimation, ACTOR_SELF, 1, 0x47000A)
    Wait(10)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 3, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarB, 0, 0, 3, 16)
            Switch(LVarB)
                CaseEq(6)
                    Call(UseBattleCamPreset, 2)
                    Call(MoveBattleCamOver, 30)
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Sub(LVar0, 40)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
                    Call(SetGoalPos, ACTOR_SELF, -240, 0, LVar2)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetActorPos, ACTOR_SELF, 240, 0, LVar2)
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(ResetAllActorSounds, ACTOR_SELF)
                    Call(StopSound, 880)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x47000C)
                    Wait(8)
                    Call(YieldTurn)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x470001)
                    Call(EnableIdleScript, ACTOR_SELF, 1)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
                CaseDefault
                    Call(GetOwnerTarget, LVar1, 0)
                    IfEq(LVar1, 0)
                        Call(GetStatusFlags, LVar1, LVar0)
                        IfNotFlag(LVar0, 0x435D000)
                            Call(UseIdleAnimation, 0, 0)
                            Call(SetAnimation, 0, 0, 0x1002B)
                        EndIf
                    EndIf
                    Call(UseBattleCamPreset, 19)
                    Call(SetBattleCamTarget, -25, 60, 0)
                    Call(SetBattleCamDist, 460)
                    Call(SetBattleCamOffsetY, 0)
                    Call(MoveBattleCamOver, 50)
                    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(GetStatusFlags, ACTOR_SELF, LVar3)
                    IfNotFlag(LVar3, 0x80000)
                        Add(LVar0, 32)
                    Else
                        Add(LVar0, 12)
                    EndIf
                    Set(LVar1, 0)
                    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    IfEq(LVarA, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    Set(LVarA, 1)
            EndSwitch
        EndCaseGroup
        CaseDefault
            Call(UseBattleCamPreset, 19)
            Call(SetBattleCamTarget, -25, 60, 0)
            Call(SetBattleCamDist, 460)
            Call(SetBattleCamOffsetY, 0)
            Call(MoveBattleCamOver, 50)
            Call(GetOwnerTarget, LVar1, 0)
            IfEq(LVar1, 0)
                Call(UseIdleAnimation, 0, 0)
                Call(GetStatusFlags, 0, LVar0)
                IfNotFlag(LVar0, 0x435D000)
                    Call(SetAnimation, 0, 0, 0x1002B)
                EndIf
            EndIf
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfNotFlag(LVar3, 0x80000)
                Add(LVar0, 32)
            Else
                Add(LVar0, 12)
            EndIf
            Set(LVar1, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetOwnerTarget, LVar1, 0)
            Call(GetStatusFlags, ACTOR_SELF, LVarE)
            IfNotFlag(LVarE, 0x80000)
                IfEq(LVar1, 0)
                    Call(SetDamageSource, 24)
                EndIf
            EndIf
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0xFFFF, 0, 3, 32)
            Set(LVarA, 0)
            IfNotFlag(LVarE, 0x80000)
                Call(GetBattleFlags, LVar0)
                IfNotFlag(LVar0, (-0x7FFFFFFF - 1))
                    Call(GetOwnerTarget, LVar1, 0)
                    IfEq(LVar1, 0)
                        Call(GetStatusFlags, 0, LVar0)
                        IfNotFlag(LVar0, 0x100000)
                            Call(TTYD64_GetPartnerHP_API, LVar1)
                            IfGt(LVar1, 0)
                                Set(LVarA, 1)
                            EndIf
                        EndIf
                    Else
                        Set(LVarA, 1)
                    EndIf
                EndIf
            EndIf
    EndSwitch
    IfNe(LVarA, 0)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 32)
        Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
        Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetOwnerTarget, LVar1, 0)
        IfEq(LVar1, 0)
            Call(SetDamageSource, 25)
        EndIf
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 3, 32)
        Call(GetBattleFlags, LVar0)
        IfNotFlag(LVar0, (-0x7FFFFFFF - 1))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, -240, 0, LVar2)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(SetActorPos, ACTOR_SELF, 240, 0, LVar2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(StopSound, 880)
            Call(SetAnimation, ACTOR_SELF, 1, 0x47000C)
            Wait(8)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0x470001)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        Else
            Call(UseBattleCamPreset, 19)
            Call(SetBattleCamTarget, -45, 60, 0)
            Call(SetBattleCamDist, 460)
            Call(SetBattleCamOffsetY, 0)
            Call(MoveBattleCamOver, 30)
        EndIf
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
    Thread
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfNotFlag(LVar3, 0x80000)
            Call(b_area_nok_kent_c_koopa_StartRumbleWithParams, 80, 14)
            Call(ShakeCam, 1, 0, 1, Float(0.5))
        EndIf
    EndThread
    Add(LVar0, 16)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
    Thread
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfNotFlag(LVar3, 0x80000)
            Call(b_area_nok_kent_c_koopa_StartRumbleWithParams, 80, 14)
            Call(ShakeCam, 1, 0, 1, Float(0.5))
        EndIf
    EndThread
    Add(LVar0, 10)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
    Thread
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfNotFlag(LVar3, 0x80000)
            Call(b_area_nok_kent_c_koopa_StartRumbleWithParams, 80, 14)
            Call(ShakeCam, 1, 0, 1, Float(0.5))
        EndIf
    EndThread
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(StopSound, 880)
    Call(SetAnimation, ACTOR_SELF, 1, 0x47000C)
    Wait(8)
    Call(YieldTurn)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    SetConst(LVar0, 1)
    SetConst(LVar1, 0x470004)
    ExecWait(Ref(EVS_Enemy_ReturnHome))
    Call(SetAnimation, ACTOR_SELF, 1, 0x470001)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_spiked_goomba_EVS_TakeTurn = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x270003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x270001)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x270004)
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
                    Call(b_area_nok_spiked_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x270004)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x27000A)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 5, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 7, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x270006)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x270004)
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
                Call(SetAnimation, ACTOR_SELF, 1, 0x270004)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x270009)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x270001)
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
                    Call(b_area_nok_spiked_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x270004)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x270004)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x270001)
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
            Call(GetOwnerTarget, LVar1, 0)
            Call(GetLastDamage, LVar1, LVar0)
            IfGt(LVar0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x27000B)
                Wait(15)
            Else
                Call(SetAnimation, ACTOR_SELF, 1, 0x270001)
                Wait(3)
            EndIf
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x270003)
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
EvtScript TTYD64_nok_paratroopa_EVS_Downed_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290106)
    Else
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        IfEq(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 9, LVar0)
            Sub(LVar0, 1)
            IfGt(LVar0, 0)
                Call(SetActorVar, ACTOR_SELF, 9, LVar0)
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
                Wait(30)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Else
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
                Wait(20)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8321)
                Call(SetAnimation, ACTOR_SELF, 1, 0x29010F)
                Set(LVar0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
                ChildThread
                    Loop(5)
                        Add(LVar0, 15)
                        Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                        Wait(1)
                    EndLoop
                EndChildThread
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
                Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8378)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x290101)
                Call(SetActorVar, ACTOR_SELF, 8, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_paratroopa_DownedAnims_8022B630))
                Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_nok_paratroopa_DownedDefense))
                Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
                Call(SetTargetOffset, ACTOR_SELF, 1, -4, 32)
                Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -4)
                Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
                Call(ResetActorSounds, ACTOR_SELF, 2)
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndIf
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290107)
        Wait(10)
        ChildThread
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 4)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            Wait(3)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            Wait(2)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        EndChildThread
        Call(PlaySoundAtActor, ACTOR_SELF, 8225)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290106)
        Wait(10)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -40, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(UseBattleCamPreset, 5)
                Call(SetBattleCamDist, 300)
                Call(SetBattleCamOffsetY, 20)
                Call(MoveBattleCamOver, 10)
                Call(SetBattleCamTargetingModes, -1, 1, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x290108)
            Wait(8)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Wait(4)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x290115)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290116)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290117)
            Wait(6)
            Sub(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290117)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290101)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetPartYaw, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x290108)
            Wait(8)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x290104)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x290101)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_koopa_troopa_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290106)
    Else
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        IfEq(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 9, LVar0)
            Sub(LVar0, 1)
            IfGt(LVar0, 0)
                Call(SetActorVar, ACTOR_SELF, 9, LVar0)
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
                Wait(30)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Else
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
                Wait(20)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8321)
                Call(SetAnimation, ACTOR_SELF, 1, 0x29010F)
                Set(LVar0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
                ChildThread
                    Loop(5)
                        Add(LVar0, 15)
                        Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                        Wait(1)
                    EndLoop
                EndChildThread
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
                Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8378)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x290101)
                Call(SetActorVar, ACTOR_SELF, 8, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_paratroopa_DownedAnims))
                Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_nok_paratroopa_DownedDefense))
                Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
                Call(SetTargetOffset, ACTOR_SELF, 1, -4, 32)
                Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -4)
                Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
                Call(ResetActorSounds, ACTOR_SELF, 2)
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndIf
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290107)
        Wait(10)
        ChildThread
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 4)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            Wait(3)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            Wait(2)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        EndChildThread
        Call(PlaySoundAtActor, ACTOR_SELF, 8225)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290106)
        Wait(10)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -40, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(UseBattleCamPreset, 5)
                Call(SetBattleCamDist, 300)
                Call(SetBattleCamOffsetY, 20)
                Call(MoveBattleCamOver, 10)
                Call(SetBattleCamTargetingModes, -1, 1, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x290108)
            Wait(8)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Wait(4)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x290115)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290116)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290117)
            Wait(6)
            Sub(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290117)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290101)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetPartYaw, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x290108)
            Wait(8)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x290104)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x290101)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_downed_goomba_EVS_TakeTurn = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x260003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
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
                    Call(b_area_nok_downed_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260008)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 5, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 7, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260005)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
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
                Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260007)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
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
                    Call(b_area_nok_downed_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x26000B)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Wait(1)
    EndSwitch
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 1, 32)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
            Wait(3)
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260003)
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
EvtScript TTYD64_nok_goomba_EVS_TakeTurn = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x260003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
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
                    Call(b_area_nok_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260008)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 5, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 7, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260005)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
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
                Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260007)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
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
                    Call(b_area_nok_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x260004)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x26000B)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Wait(1)
    EndSwitch
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 1, 32)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
            Wait(3)
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260003)
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
EvtScript TTYD64_nok_kent_c_koopa_EVS_Attack_HeavyStomp = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamDist, 280)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x470003)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x470001)
    Wait(8)
    Call(PlaySoundAtActor, ACTOR_SELF, 999)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x470006)
            Thread
                Wait(7)
                Call(SetAnimation, ACTOR_SELF, 1, 0x470007)
                Wait(4)
                Call(SetAnimation, ACTOR_SELF, 1, 0x470008)
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8428)
            Thread
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfNotFlag(LVar3, 0x80000)
                    Call(b_area_nok_kent_c_koopa_StartRumbleWithParams, 80, 14)
                    Call(ShakeCam, 1, 0, 1, Float(0.5))
                EndIf
            EndThread
            Sub(LVar0, 15)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8428)
            Thread
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfNotFlag(LVar3, 0x80000)
                    Call(b_area_nok_kent_c_koopa_StartRumbleWithParams, 80, 14)
                    Call(ShakeCam, 1, 0, 1, Float(0.5))
                EndIf
            EndThread
            Call(SetAnimation, ACTOR_SELF, 1, 0x470001)
            Sub(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8428)
            Thread
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfNotFlag(LVar3, 0x80000)
                    Call(b_area_nok_kent_c_koopa_StartRumbleWithParams, 80, 14)
                    Call(ShakeCam, 1, 0, 1, Float(0.5))
                EndIf
            EndThread
            Wait(8)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Set(LVar3, 0)
            Loop(12)
                Add(LVar3, 15)
                Call(SetActorYaw, ACTOR_SELF, LVar3)
                Wait(1)
            EndLoop
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x470004)
            Call(SetPartYaw, ACTOR_SELF, 1, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x470001)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Set(LVar3, 180)
            Loop(15)
                Sub(LVar3, 12)
                Call(SetActorYaw, ACTOR_SELF, LVar3)
                Wait(1)
            EndLoop
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x470006)
    Thread
        Wait(5)
        Call(SetAnimation, ACTOR_SELF, 1, 0x470007)
        Wait(2)
        Call(SetAnimation, ACTOR_SELF, 1, 0x470008)
    EndThread
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2998046875))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(JumpToGoal, ACTOR_SELF, 14, 0, 1, 0)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetOwnerTarget, LVar1, 0)
    IfEq(LVar1, 0)
        Call(GetStatusFlags, ACTOR_SELF, LVarF)
        IfNotFlag(LVarF, 0x80000)
            Call(SetDamageSource, 24)
        EndIf
    EndIf
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 128, 0xFFFF, 0, 10, 32)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 30)
            Call(GetBattleFlags, LVar0)
            IfNotFlag(LVar0, (-0x7FFFFFFF - 1))
                Call(GetOwnerTarget, LVar1, 0)
                Call(GetStatusFlags, LVar1, LVar0)
                IfNotFlag(LVar0, 0x100000)
                    Call(GetStatusFlags, ACTOR_SELF, LVarE)
                    IfNotFlag(LVarE, 0x80000)
                        Call(LandJump, ACTOR_SELF)
                        Call(PlaySoundAtActor, ACTOR_SELF, 8428)
                    EndIf
                EndIf
            EndIf
            Thread
                Call(b_area_nok_kent_c_koopa_StartRumbleWithParams, 80, 14)
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfNotFlag(LVar3, 0x80000)
                    Call(b_area_nok_kent_c_koopa_StartRumbleWithParams, 80, 14)
                    Call(ShakeCam, 1, 0, 1, Float(0.5))
                EndIf
            EndThread
            Thread
                Wait(5)
                Call(SetAnimation, ACTOR_SELF, 1, 0x470006)
            EndThread
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8428)
            Thread
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfNotFlag(LVar3, 0x80000)
                    Call(b_area_nok_kent_c_koopa_StartRumbleWithParams, 80, 14)
                    Call(ShakeCam, 1, 0, 1, Float(0.5))
                EndIf
            EndThread
            Call(SetAnimation, ACTOR_SELF, 1, 0x470001)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8428)
            Thread
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfNotFlag(LVar3, 0x80000)
                    Call(b_area_nok_kent_c_koopa_StartRumbleWithParams, 80, 14)
                    Call(ShakeCam, 1, 0, 1, Float(0.5))
                EndIf
            EndThread
            Wait(8)
            IfEq(LVarF, 10)
                Return
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            ExecWait(b_area_nok_kent_c_koopa_EVS_KentC_GoHome)
        CaseEq(3)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_koopa_troopa_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010C)
            SetConst(LVar2, 0x29010D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010C)
            SetConst(LVar2, 0x29010D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010D)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 8, 1)
            Call(SetActorVar, ACTOR_SELF, 9, 2)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_nok_koopa_troopa_FlippedDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_koopa_troopa_FlippedAnims))
            Call(SetTargetOffset, ACTOR_SELF, 1, -5, 15)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, 0)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x29010B)
            Call(GetStatusFlags, ACTOR_SELF, LVarA)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            ChildThread
                Wait(4)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -60)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -75)
                Wait(1)
            EndChildThread
            UseBuf(Ref(b_area_nok_koopa_troopa_FlipPosOffsets))
            Loop(22)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x29010F)
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x290104)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290107)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(GetStatusFlags, ACTOR_SELF, LVar0)
                IfNotFlag(LVar0, 0x35D000)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x290108)
                    Wait(10)
                EndIf
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290104)
                ExecWait(Ref(EVS_Enemy_ReturnHome))
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290101)
                ExecWait(Ref(EVS_Enemy_Recover))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290104)
                SetConst(LVar2, 0x29010B)
                ExecWait(Ref(EVS_Enemy_ScareAway))
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290117)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
            EndIf
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290117)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
            EndIf
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290101)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_paratroopa_EVS_Downed_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010C)
            SetConst(LVar2, 0x29010D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010C)
            SetConst(LVar2, 0x29010D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010D)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 8, 1)
            Call(SetActorVar, ACTOR_SELF, 9, 2)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_nok_paratroopa_FlippedDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_paratroopa_DownedFlippedAnims))
            Call(SetTargetOffset, ACTOR_SELF, 1, -5, 15)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, 0)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x29010B)
            Call(GetStatusFlags, ACTOR_SELF, LVarA)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            ChildThread
                Wait(4)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -60)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -75)
                Wait(1)
            EndChildThread
            UseBuf(Ref(b_area_nok_paratroopa_FlipPosOffsets))
            Loop(22)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x29010F)
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x290104)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290107)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(GetStatusFlags, ACTOR_SELF, LVar0)
                IfNotFlag(LVar0, 0x35D000)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x290108)
                    Wait(10)
                EndIf
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290104)
                ExecWait(Ref(EVS_Enemy_ReturnHome))
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290101)
                ExecWait(Ref(EVS_Enemy_Recover))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290104)
                SetConst(LVar2, 0x29010B)
                ExecWait(Ref(EVS_Enemy_ScareAway))
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290117)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
            EndIf
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290117)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
            EndIf
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290101)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_paratroopa_EVS_Flying_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVar1, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 5)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetTargetActor, ACTOR_SELF, LVar1)
    Call(SetAnimation, ACTOR_SELF, 2, 0x2A0103)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 40, 30, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -16, 0)
    Call(UseBattleCamPresetImmediately, 1)
    Wait(5)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8416)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 2, 0x2A0104)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(AddGoalPos, ACTOR_SELF, 6, 6, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
            Wait(6)
            Call(PlaySoundAtActor, ACTOR_SELF, 705)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(GetOwnerTarget, LVar3, 0)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Sub(LVar0, 25)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x2A010C)
            Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(4.0))
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
                Set(LVar0, 0)
                Loop(8)
                    Add(LVar0, 90)
                    IfGe(LVar0, 360)
                        Sub(LVar0, 360)
                    EndIf
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, -10, 0)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x2A0107)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x2A0107)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 30)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(b_area_nok_paratroopa_EVS_FlyHome)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 8416)
    Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x2A0104)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(AddGoalPos, ACTOR_SELF, 6, 6, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
    Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
    Wait(6)
    Call(PlaySoundAtActor, ACTOR_SELF, 705)
    Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
    Call(SetAnimation, ACTOR_SELF, 2, 0x2A010C)
    Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 40, 30, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x2A010D)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
                Set(LVar0, 0)
                Loop(12)
                    Sub(LVar0, 90)
                    IfLt(LVar0, 0)
                        Add(LVar0, 360)
                    EndIf
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, -10, 0)
                Call(SetAnimation, ACTOR_SELF, 2, 0x2A0101)
            EndThread
            Call(FlyToGoal, ACTOR_SELF, 0, 30, 0)
            Wait(10)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            ExecWait(b_area_nok_paratroopa_EVS_FlyHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_paragoomba_EVS_TakeTurn = {
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
    Call(SetAnimation, ACTOR_SELF, 2, 0x280004)
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
            Call(SetAnimation, ACTOR_SELF, 2, 0x280005)
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
            Call(SetAnimation, ACTOR_SELF, 2, 0x280005)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
            Thread
                Loop(4)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8415)
                    Wait(4)
                EndLoop
            EndThread
            Call(SetAnimation, ACTOR_SELF, 2, 0x280002)
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
            Call(SetAnimation, ACTOR_SELF, 2, 0x280004)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(b_area_nok_paragoomba_EVS_Paragoomba_GoHome)
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
            Call(SetAnimation, ACTOR_SELF, 2, 0x280005)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 705)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280005)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    EndSwitch
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x280004)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Wait(5)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 2, 0x280004)
            ExecWait(b_area_nok_paragoomba_EVS_Paragoomba_GoHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_spiked_goomba_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270006)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270007)
            SetConst(LVar2, 0x270008)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270007)
            SetConst(LVar2, 0x270008)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270008)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270006)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270006)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270005)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x27000C)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270006)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x270009)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x270001)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x27000C)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270005)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270006)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270005)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x270003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270003)
            SetConst(LVar2, 0x270006)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x270006)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(27)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x27000B)
            EndIf
            Wait(10)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                Add(LVar1, 10)
            Else
                Add(LVar1, 26)
            EndIf
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(20)
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x270001)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_kent_c_koopa_EVS_TakeTurn = {
    Call(SetActorVar, ACTOR_SELF, 4, 2)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 0)
        Call(EnableIdleScript, ACTOR_SELF, 0)
        Call(UseBattleCamPreset, 14)
        Call(SetBattleCamDist, 200)
        Call(SetBattleCamOffsetY, 20)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 25)
        Call(GetActorVar, ACTOR_SELF, 2, LVar0)
        Sub(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 2, LVar0)
        IfGt(LVar0, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 36)
            Add(LVar1, 18)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
            Loop(5)
                Call(PlayEffect_impl, 40, 1, LVar0, LVar1, LVar2, 1, 225, 10, 0, 0, 0, 0, 0, 0)
                Wait(5)
            EndLoop
            Wait(30)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        Else
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 36)
            Add(LVar1, 18)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
            Loop(5)
                Call(PlayEffect_impl, 40, 1, LVar0, LVar1, LVar2, 1, 225, 10, 0, 0, 0, 0, 0, 0)
                Wait(5)
            EndLoop
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
            Wait(30)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 15)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x470019)
            Thread
                Wait(3)
                Call(GetStatusFlags, ACTOR_SELF, LVar0)
                IfNotFlag(LVar0, 0x80000)
                    Call(SetActorRotationOffset, ACTOR_SELF, 0, 27, 0)
                Else
                    Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
                EndIf
                Set(LVar0, 0)
                Loop(5)
                    Add(LVar0, 36)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfNotFlag(LVar3, 0x80000)
                Call(b_area_nok_kent_c_koopa_StartRumbleWithParams, 80, 14)
                Call(ShakeCam, 1, 0, 2, Float(0.5))
            EndIf
            Wait(3)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x47000C)
            Wait(10)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_nok_kent_c_koopa_NormalDefense))
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
            Call(SetEnemyTargetOffset, ACTOR_SELF, 1, 0, 60)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x20000, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x800000, 0)
            Call(SetPartFlags, ACTOR_SELF, 2, 0x20004)
            Call(SetPartFlags, ACTOR_SELF, 1, 0x800004)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_kent_c_koopa_DefaultAnims))
            Call(b_area_nok_kent_c_koopa_SetAbsoluteStatusOffsets, -26, 38, 2, 63)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetActorVar, ACTOR_SELF, 1, 0x47001C)
        EndIf
    EndIf
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 50)
        Call(GetStatusFlags, 256, LVar0)
        IfNotFlag(LVar0, 0x1000000)
            ExecWait(TTYD64_nok_kent_c_koopa_EVS_Attack_ShellToss)
        Else
            ExecWait(TTYD64_nok_kent_c_koopa_EVS_Attack_HeavyStomp)
        EndIf
    Else
        ExecWait(TTYD64_nok_kent_c_koopa_EVS_Attack_HeavyStomp)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_paratroopa_EVS_Flying_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_Hit))
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(GetEncounterTrigger, LVar0)
                IfEq(LVar0, 4)
                    ExecWait(TTYD64_nok_paratroopa_EVS_KnockDown)
                EndIf
            EndIf
        CaseEq(11)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0106)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(14)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0108)
            SetConst(LVar2, 0x2A0109)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0108)
            SetConst(LVar2, 0x2A0109)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0109)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(12)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_nok_paratroopa_EVS_KnockDown)
        CaseEq(15)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2A0108)
            SetConst(LVar1, 0x2A0109)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_nok_paratroopa_EVS_KnockDown)
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2A0106)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(b_area_nok_paratroopa_EVS_FlyHome)
        CaseEq(38)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0106)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A010B)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A010B)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(GetEncounterTrigger, LVar0)
                IfEq(LVar0, 4)
                    ExecWait(TTYD64_nok_paratroopa_EVS_KnockDown)
                EndIf
            EndIf
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0106)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(b_area_nok_paratroopa_EVS_FlyHome)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0101)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0103)
            SetConst(LVar2, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0103)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
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
EvtScript TTYD64_nok_downed_goomba_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260009)
            SetConst(LVar2, 0x26000A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260009)
            SetConst(LVar2, 0x26000A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26000A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26000E)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260007)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26000E)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260003)
            SetConst(LVar2, 0x260005)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_goomba_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260009)
            SetConst(LVar2, 0x26000A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260009)
            SetConst(LVar2, 0x26000A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26000A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26000E)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260007)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x26000E)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x260003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260003)
            SetConst(LVar2, 0x260005)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x260005)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_fuzzy_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Call(GetLastElement, LVar0)
            IfFlag(LVar0, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0013)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0008)
            EndIf
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0010)
            SetConst(LVar2, 0x2B0012)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0010)
            SetConst(LVar2, 0x2B0012)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0012)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0008)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0008)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0008)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0013)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0013)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0003)
            ExecWait(Ref(EVS_Enemy_HopHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0013)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0008)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            Call(GetLastElement, LVar0)
            IfFlag(LVar0, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0013)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0013)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0008)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0008)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0003)
            SetConst(LVar2, 0x2B0009)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0003)
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
EvtScript TTYD64_nok_paragoomba_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280006)
            ExecWait(Ref(EVS_Enemy_Hit))
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(GetEncounterTrigger, LVar0)
                IfEq(LVar0, 4)
                    ExecWait(TTYD64_nok_paragoomba_EVS_KnockDown)
                EndIf
            EndIf
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000D)
            SetConst(LVar2, 0x28000E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000D)
            SetConst(LVar2, 0x28000E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000E)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(12)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280006)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_nok_paragoomba_EVS_KnockDown)
        CaseEq(15)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000D)
            SetConst(LVar2, 0x28000E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_nok_paragoomba_EVS_KnockDown)
        CaseEq(47)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000F)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280006)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(SetAnimation, ACTOR_SELF, 2, 0x28000C)
            ExecWait(b_area_nok_paragoomba_EVS_Paragoomba_GoHome)
        CaseEq(38)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000F)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280007)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280006)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280007)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            Call(SetAnimation, ACTOR_SELF, 2, 0x280004)
            ExecWait(b_area_nok_paragoomba_EVS_Paragoomba_GoHome)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280004)
            SetConst(LVar2, 0x280006)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280004)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280006)
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
EvtScript TTYD64_nok_paratroopa_EVS_KnockDown = {
    Call(SetPartDispOffset, ACTOR_SELF, 2, 0, 0, 0)
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetPartFlags, ACTOR_SELF, 2, 0x20005)
    Call(SetPartFlags, ACTOR_SELF, 3, 0x120004)
    Call(SetPartFlags, ACTOR_SELF, 1, 0x800004)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 8)
    Sub(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x29010B)
    Call(SetActorSounds, ACTOR_SELF, 2, 769, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfEq(LVarA, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 0)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
        Call(b_area_nok_paratroopa_StartRumbleWithParams, 128, 7)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(0.2998046875))
        EndThread
        Call(ResetActorSounds, ACTOR_SELF, 2)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        Loop(10)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
            Wait(1)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
            Wait(1)
        EndLoop
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 0)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
        Thread
            Loop(10)
                Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
                Wait(1)
                Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
                Wait(1)
            EndLoop
            Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
        EndThread
        Call(b_area_nok_paratroopa_StartRumbleWithParams, 150, 7)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(0.2998046875))
        EndThread
        Call(ResetActorSounds, ACTOR_SELF, 2)
    EndIf
    Call(GetIndexFromHome, ACTOR_SELF, LVar0)
    Mod(LVar0, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVar0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x290101)
    Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_nok_paratroopa_DownedStatusTable))
    Call(BindHandlePhase, ACTOR_SELF, 0)
    ExecWait(TTYD64_nok_paratroopa_EVS_Downed_Init)
    Call(SetActorType, ACTOR_SELF, 11)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(ResetAllActorSounds, ACTOR_SELF)
    IfNe(LVarA, 0)
        Call(DispatchEvent, ACTOR_SELF, 13)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_paragoomba_EVS_KnockDown = {
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x26000A)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x260005)
    EndIf
    Call(SetActorSounds, ACTOR_SELF, 2, 769, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(b_area_nok_paratroopa_StartRumbleWithParams, 100, 10)
    Thread
        Call(ShakeCam, 1, 0, 5, Float(0.2998046875))
    EndThread
    Call(ResetActorSounds, ACTOR_SELF, 2)
    Call(GetLastEvent, ACTOR_SELF, LVar3)
    IfEq(LVar3, 15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x260005)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x260001)
    Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_nok_paragoomba_DownedStatusTable))
    Call(SetActorType, ACTOR_SELF, 7)
    ExecWait(TTYD64_nok_downed_goomba_EVS_Init)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_koopa_troopa_EVS_Idle = {
    Label(0)
    Call(RandInt, 80, LVarA)
    Add(LVarA, 80)
    Loop(LVarA)
        Label(1)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_nok_koopa_troopa_EVS_UpdateTargetOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(1)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_koopa_troopa_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_paratroopa_DownedAnims))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_koopa_troopa_FlippedAnims))
    EndSwitch
    Loop(20)
        Label(2)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_nok_koopa_troopa_EVS_UpdateTargetOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(2)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(2)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_koopa_troopa_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_paratroopa_DownedAnims))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_koopa_troopa_FlippedAnims))
    EndSwitch
    Loop(80)
        Label(3)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_nok_koopa_troopa_EVS_UpdateTargetOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(3)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(3)
        EndIf
        Wait(1)
    EndLoop
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_paratroopa_EVS_Downed_Idle = {
    Label(0)
    Call(RandInt, 80, LVarA)
    Add(LVarA, 80)
    Loop(LVarA)
        Label(1)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_nok_paratroopa_EVS_Downed_UpdateTargetOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(1)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_paratroopa_DownedShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_paratroopa_DownedAnims_8022B630))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_paratroopa_DownedFlippedAnims))
    EndSwitch
    Loop(20)
        Label(2)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_nok_paratroopa_EVS_Downed_UpdateTargetOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(2)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(2)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_paratroopa_DownedShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_paratroopa_DownedAnims_8022B630))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_paratroopa_DownedFlippedAnims))
    EndSwitch
    Loop(80)
        Label(3)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_nok_paratroopa_EVS_Downed_UpdateTargetOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(3)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(3)
        EndIf
        Wait(1)
    EndLoop
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_paratroopa_EVS_Flying_Idle = {
    Label(10)
    Call(RandInt, 80, LVar0)
    Add(LVar0, 80)
    Loop(LVar0)
        Label(0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_nok_paratroopa_EVS_Flying_UpdateTargetOffsets)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(0)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(0.599609375))
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_nok_paratroopa_FlyingShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, -5, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_paratroopa_FlyingAnims))
    Loop(20)
        Label(1)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_nok_paratroopa_EVS_Flying_UpdateTargetOffsets)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(0.599609375))
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_nok_paratroopa_FlyingShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, -5, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_nok_paratroopa_FlyingAnims))
    Loop(40)
        Label(2)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_nok_paratroopa_EVS_Flying_UpdateTargetOffsets)
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
EvtScript TTYD64_nok_goomba_EVS_Idle = {
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_goomba_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_goomba_DefaultAnims))
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_goomba_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_goomba_DefaultAnims))
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
EvtScript TTYD64_nok_downed_goomba_EVS_Idle = {
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_downed_goomba_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_downed_goomba_DefaultAnims))
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_downed_goomba_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_downed_goomba_DefaultAnims))
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
EvtScript TTYD64_nok_spiked_goomba_EVS_Idle = {
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_spiked_goomba_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_spiked_goomba_DefaultAnims))
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_spiked_goomba_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_nok_spiked_goomba_DefaultAnims))
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
EvtScript TTYD64_nok_paragoomba_EVS_Idle = {
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
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_nok_paragoomba_ShuffleAnims))
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
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_nok_paragoomba_DefaultAnims))
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

Battle TTYD64_nok_Formations[] = {
    { .name = "\257\352\334\374x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_nok_Formation_00,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\257\352\334\374,\310\262\257\352\334\374",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_nok_Formation_01,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\321\277\257\352\334\374x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_nok_Formation_02,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\310\262\257\352\334\374\001\321\277\257\352\334\374",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_nok_Formation_03,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\310\262\257\352\334\374x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_nok_Formation_04,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\310\262\257\352\334\374\001\257\352\334\374x2",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_nok_Formation_05,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\310\262\257\352\334\374x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_nok_Formation_06,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\310\262\257\352\334\374x\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_nok_Formation_07,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263\001\257\352\334\374",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_nok_Formation_08,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_nok_Formation_09,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_nok_Formation_0A,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263\001\310\262\257\352\334\374",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_nok_Formation_0B,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263x2\001\310\262\257\352",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_nok_Formation_0C,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263\001\310\262\257\352\334\374x2",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_nok_Formation_0D,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263\001\321\277\257\352\334\374x2",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_nok_Formation_0E,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263\001\310\262\257\352\334\374,\321\277\257\352\334\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_nok_Formation_0F,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263x2\001\310\262\257\352\334\374,\321\277\257\352\334\374",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_nok_Formation_10,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\321\277\321\277x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_nok_Formation_11,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\321\277\321\277\001\316\263\316\263",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_nok_Formation_12,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\321\277\321\277\001\316\263\316\263\001\310\262\257\352\334\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_nok_Formation_13,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\321\277\321\277\001\316\263\316\263\001\310\262\257\352\334\374x2",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_nok_Formation_14,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\301\347\355\334\363",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_nok_Formation_15,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\301\347\355\334\363x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_nok_Formation_16,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\301\347\355\334\363x4",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_nok_Formation_17,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    { .name = "\274\313\316\263\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_nok_Formation_18,
      .stage = &b_area_nok_nok_02,
      .onBattleStart = NULL },
    {},
};

ActorPartBlueprint TTYD64_nok_kent_c_koopa_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 60 },
        .opacity = 255,
        .idleAnimations = TTYD64_nok_kent_c_koopa_DefaultAnims,
        .defenseTable = b_area_nok_kent_c_koopa_NormalDefense,
        .eventFlags = 0x1000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 2,
        .posOffset = { 12, 61, 0 },
        .targetOffset = { 0, -20 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_nok_kent_c_koopa_FlippedDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 3,
        .posOffset = { 45, 0, 0 },
        .targetOffset = { -70, 26 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_nok_kent_c_koopa_FlippedTailDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120003,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_nok_kent_c_koopa_CoinAnims,
        .defenseTable = b_area_nok_kent_c_koopa_FlippedTailDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120003,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_nok_kent_c_koopa_CoinAnims,
        .defenseTable = b_area_nok_kent_c_koopa_FlippedTailDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120003,
        .index = 6,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_nok_kent_c_koopa_CoinAnims,
        .defenseTable = b_area_nok_kent_c_koopa_FlippedTailDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120003,
        .index = 7,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_nok_kent_c_koopa_CoinAnims,
        .defenseTable = b_area_nok_kent_c_koopa_FlippedTailDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120003,
        .index = 8,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_nok_kent_c_koopa_CoinAnims,
        .defenseTable = b_area_nok_kent_c_koopa_FlippedTailDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120003,
        .index = 9,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_nok_kent_c_koopa_CoinAnims,
        .defenseTable = b_area_nok_kent_c_koopa_FlippedTailDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_nok_kent_c_koopa_EVS_Init = {
    Call(func_8027D434, ACTOR_SELF, 3, 70)
    Call(SetPartSize, ACTOR_SELF, 3, 30, 30)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_nok_kent_c_koopa_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_nok_kent_c_koopa_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_nok_kent_c_koopa_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_nok_kent_c_koopa_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0x47001C)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 20)
    Call(SetActorVar, ACTOR_SELF, 4, 2)
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_nok_paragoomba_ActorParts[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_nok_downed_goomba_DefaultAnims,
        .defenseTable = b_area_nok_fuzzy_DefenseTable,
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
        .idleAnimations = TTYD64_nok_paragoomba_DefaultAnims,
        .defenseTable = b_area_nok_paragoomba_FlyingDefense,
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
        .idleAnimations = b_area_nok_paragoomba_LeftWingAnims,
        .defenseTable = b_area_nok_fuzzy_DefenseTable,
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
        .idleAnimations = b_area_nok_paragoomba_RightWingAnims,
        .defenseTable = b_area_nok_fuzzy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_nok_paratroopa_EVS_Flying_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_nok_paratroopa_EVS_Flying_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_nok_paratroopa_EVS_Flying_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_nok_paratroopa_EVS_Flying_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_nok_paratroopa_EVS_Flying_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_nok_Formation_10[] = {
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
    { .actor = &TTYD64_nok_paragoomba,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGOOMBA },
};

FormationRow TTYD64_nok_Formation_14[] = {
    { .actor = &TTYD64_nok_paratroopa,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
};

FormationRow TTYD64_nok_Formation_17[] = {
    { .actor = &TTYD64_nok_fuzzy, .home = { .index = 0 }, .priority = 10, .var0 = 0, .var1 = 0, .var2 = 0, .var3 = 0 },
    { .actor = &TTYD64_nok_fuzzy, .home = { .index = 1 }, .priority = 9, .var0 = 0, .var1 = 0, .var2 = 0, .var3 = 0 },
    { .actor = &TTYD64_nok_fuzzy, .home = { .index = 2 }, .priority = 8, .var0 = 0, .var1 = 0, .var2 = 0, .var3 = 0 },
    { .actor = &TTYD64_nok_fuzzy, .home = { .index = 3 }, .priority = 7, .var0 = 0, .var1 = 0, .var2 = 0, .var3 = 0 },
};

FormationRow TTYD64_nok_Formation_07[] = {
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
};

ActorPartBlueprint TTYD64_nok_paratroopa_ActorParts[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 36 },
        .opacity = 255,
        .idleAnimations = TTYD64_nok_paratroopa_DownedAnims_8022B630,
        .defenseTable = b_area_nok_paratroopa_DownedDefense,
        .eventFlags = 0x1000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -7 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -4, 36 },
        .opacity = 255,
        .idleAnimations = TTYD64_nok_paratroopa_FlyingAnims,
        .defenseTable = b_area_nok_paratroopa_FlyingDefense,
        .eventFlags = 0x4000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 2, -14 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_nok_paratroopa_WingAnims,
        .defenseTable = b_area_nok_paratroopa_DownedDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_nok_paratroopa_EVS_Downed_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_nok_paratroopa_EVS_Downed_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_nok_paratroopa_EVS_Downed_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_nok_paratroopa_EVS_Downed_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_koopa_troopa_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_nok_koopa_troopa_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_nok_koopa_troopa_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_nok_koopa_troopa_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_nok_Formation_0A[] = {
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
};

FormationRow TTYD64_nok_Formation_0D[] = {
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
};

FormationRow TTYD64_nok_Formation_0E[] = {
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_nok_paragoomba,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGOOMBA },
    { .actor = &TTYD64_nok_paragoomba,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGOOMBA },
};

FormationRow TTYD64_nok_Formation_0C[] = {
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
};

FormationRow TTYD64_nok_Formation_0F[] = {
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
    { .actor = &TTYD64_nok_paragoomba,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGOOMBA },
};

FormationRow TTYD64_nok_Formation_13[] = {
    { .actor = &TTYD64_nok_paratroopa,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
};

FormationRow TTYD64_nok_Formation_05[] = {
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
    { .actor = &TTYD64_nok_goomba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GOOMBA },
    { .actor = &TTYD64_nok_goomba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GOOMBA },
};

FormationRow TTYD64_nok_Formation_06[] = {
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
};

s32 TTYD64_nok_paratroopa_DownedAnims[] = {
    1,  0x290101, 7, 0x290100, 6, 0x290111, 9, 0x290101, 8, 0x290100,
    11, 0x290101, 5, 0x290100, 4, 0x290113, 3, 0x290113, 0,
};

s32 TTYD64_nok_koopa_troopa_FlippedAnims[] = {
    1,  0x29010F, 7, 0x290110, 6, 0x290112, 9, 0x29010F, 8, 0x290110,
    11, 0x29010F, 5, 0x290110, 4, 0x290114, 3, 0x290114, 0,
};

s32 TTYD64_nok_paratroopa_DownedFlippedAnims[] = {
    1,  0x29010F, 7, 0x290110, 6, 0x290112, 9, 0x29010F, 8, 0x290110,
    11, 0x29010F, 5, 0x290110, 4, 0x290114, 3, 0x290114, 0,
};

s32 TTYD64_nok_paragoomba_DefaultAnims[] = {
    1,  0x280001, 7, 0x280000, 6, 0x28000B, 9, 0x280001, 8, 0x280000,
    11, 0x280001, 5, 0x280000, 4, 0x28000C, 3, 0x28000C, 0,
};

// clang-format off
EvtScript TTYD64_nok_goomba_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_nok_goomba_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_nok_goomba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_nok_goomba_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_nok_spiked_goomba_DefaultAnims[] = {
    1,  0x270001, 7, 0x270000, 6, 0x27000A, 9, 0x270001, 8, 0x270000,
    11, 0x270001, 5, 0x270000, 4, 0x270009, 3, 0x270009, 0,
};

// clang-format off
EvtScript TTYD64_nok_fuzzy_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_nok_spiked_goomba_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_nok_spiked_goomba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_nok_spiked_goomba_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_nok_spiked_goomba_ShuffleAnims[] = {
    1,  0x270003, 7, 0x270000, 6, 0x27000A, 9, 0x270001, 8, 0x270000,
    11, 0x270003, 5, 0x270000, 4, 0x270009, 3, 0x270009, 0,
};

s32 TTYD64_nok_goomba_ShuffleAnims[] = {
    1,  0x260003, 7, 0x260000, 6, 0x260008, 9, 0x260001, 8, 0x260000,
    11, 0x260003, 5, 0x260000, 4, 0x260007, 3, 0x260007, 0,
};

s32 TTYD64_nok_fuzzy_DefaultAnims[] = {
    1,  0x2B0001, 7, 0x2B0000, 6, 0x2B000E, 9, 0x2B0001, 8, 0x2B0000,
    11, 0x2B0001, 5, 0x2B0000, 4, 0x2B000F, 3, 0x2B000F, 0,
};

// clang-format off
EvtScript TTYD64_nok_downed_goomba_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_nok_downed_goomba_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_nok_downed_goomba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_nok_downed_goomba_EVS_HandleEvent))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_nok_fuzzy_EVS_Init_8022B3D0 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_nok_fuzzy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_nok_fuzzy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_nok_fuzzy_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_nok_goomba_DefaultAnims[] = {
    1,  0x260001, 7, 0x260000, 6, 0x260008, 9, 0x260001, 8, 0x260000,
    11, 0x260001, 5, 0x260000, 4, 0x260007, 3, 0x260007, 0,
};

s32 TTYD64_nok_kent_c_koopa_DefaultAnims[] = {
    1,  0x470001, 7, 0x470000, 6, 0x470013, 9, 0x470001, 8, 0x470000,
    11, 0x470000, 5, 0x470000, 4, 0x470014, 3, 0x470000, 0,
};

s32 TTYD64_nok_paratroopa_FlyingShuffleAnims[] = {
    1,  0x2A0101, 7, 0x2A0100, 6, 0x2A0112, 9, 0x2A0100, 8, 0x2A0100,
    11, 0x2A0101, 5, 0x2A0100, 4, 0x2A0113, 3, 0x2A0113, 0,
};

s32 TTYD64_nok_paratroopa_DownedShuffleAnims[] = {
    1,  0x290103, 7, 0x290100, 6, 0x290111, 9, 0x290103, 8, 0x290100,
    11, 0x290103, 5, 0x290100, 4, 0x290113, 3, 0x290113, 0,
};

s32 TTYD64_nok_downed_goomba_ShuffleAnims[] = {
    1,  0x260003, 7, 0x260000, 6, 0x260008, 9, 0x260001, 8, 0x260000,
    11, 0x260003, 5, 0x260000, 4, 0x260007, 3, 0x260007, 0,
};

s32 TTYD64_nok_paratroopa_WingAnims[] = {
    1,  0x2A010F, 7, 0x2A0100, 6, 0x2A0112, 9, 0x2A0100, 8, 0x2A0100,
    11, 0x2A010F, 5, 0x2A0100, 4, 0x2A0113, 3, 0x2A0113, 0,
};

s32 TTYD64_nok_paratroopa_FlyingAnims[] = {
    1,  0x2A0101, 7, 0x2A0100, 6, 0x2A0112, 9, 0x2A0100, 8, 0x2A0100,
    11, 0x2A0101, 5, 0x2A0100, 4, 0x2A0113, 3, 0x2A0113, 0,
};

s32 TTYD64_nok_paratroopa_DownedAnims_8022B630[] = {
    1,  0x290101, 7, 0x290100, 6, 0x290111, 9, 0x290101, 8, 0x290100,
    11, 0x290101, 5, 0x290100, 4, 0x290113, 3, 0x290113, 0,
};

s32 TTYD64_nok_downed_goomba_DefaultAnims[] = {
    1,  0x260001, 7, 0x260000, 6, 0x260008, 9, 0x260001, 8, 0x260000,
    11, 0x260001, 5, 0x260000, 4, 0x260007, 3, 0x260007, 0,
};

// clang-format off
EvtScript TTYD64_nok_fuzzy_EVS_Init_8022B6C8 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_nok_paragoomba_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_nok_paragoomba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_nok_paragoomba_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_nok_paragoomba_ShuffleAnims[] = {
    1,  0x280004, 7, 0x280000, 6, 0x28000B, 9, 0x280001, 8, 0x280000,
    11, 0x280004, 5, 0x280000, 4, 0x28000C, 3, 0x28000C, 0,
};

s32 TTYD64_nok_koopa_troopa_ShuffleAnims[] = {
    1,  0x290103, 7, 0x290100, 6, 0x290111, 9, 0x290103, 8, 0x290100,
    11, 0x290103, 5, 0x290100, 4, 0x290113, 3, 0x290113, 0,
};

FormationRow TTYD64_nok_Formation_0B[] = {
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
};

FormationRow TTYD64_nok_Formation_11[] = {
    { .actor = &TTYD64_nok_paratroopa,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_nok_paratroopa,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
};

FormationRow TTYD64_nok_Formation_12[] = {
    { .actor = &TTYD64_nok_paratroopa,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
};

FormationRow TTYD64_nok_Formation_16[] = {
    { .actor = &TTYD64_nok_fuzzy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
    { .actor = &TTYD64_nok_fuzzy,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
};

FormationRow TTYD64_nok_Formation_00[] = {
    { .actor = &TTYD64_nok_goomba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GOOMBA },
    { .actor = &TTYD64_nok_goomba,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GOOMBA },
};

FormationRow TTYD64_nok_Formation_01[] = {
    { .actor = &TTYD64_nok_goomba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GOOMBA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
};

FormationRow TTYD64_nok_Formation_04[] = {
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
};

FormationRow TTYD64_nok_Formation_02[] = {
    { .actor = &TTYD64_nok_paragoomba,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGOOMBA },
    { .actor = &TTYD64_nok_paragoomba,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGOOMBA },
};

FormationRow TTYD64_nok_Formation_03[] = {
    { .actor = &TTYD64_nok_spiked_goomba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
    { .actor = &TTYD64_nok_paragoomba,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGOOMBA },
};

FormationRow TTYD64_nok_Formation_08[] = {
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_nok_goomba,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GOOMBA },
};

FormationRow TTYD64_nok_Formation_09[] = {
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_nok_koopa_troopa,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
};

ActorBlueprint TTYD64_nok_koopa_troopa = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x0B,
    .level = 6,
    .partCount = 1,
    .partsData = TTYD64_nok_koopa_troopa_ActorParts,
    .initScript = &TTYD64_nok_koopa_troopa_EVS_Init,
    .statusTable = b_area_nok_koopa_troopa_StatusTable,
    .escapeChance = 70,
    .airLiftChance = 90,
    .hurricaneChance = 90,
    .spookChance = 90,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 28, 36 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 32 },
    .statusTextOffset = { 5, 32 },
};

ActorBlueprint TTYD64_nok_spiked_goomba = {
    .flags = 0x0,
    .maxHP = 2,
    .type = 0x09,
    .level = 6,
    .partCount = 1,
    .partsData = TTYD64_nok_spiked_goomba_ActorParts,
    .initScript = &TTYD64_nok_fuzzy_EVS_Init,
    .statusTable = b_area_nok_spiked_goomba_StatusTable,
    .escapeChance = 90,
    .airLiftChance = 95,
    .hurricaneChance = 90,
    .spookChance = 100,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 24, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_nok_paragoomba = {
    .flags = 0x200,
    .maxHP = 2,
    .type = 0x08,
    .level = 6,
    .partCount = 4,
    .partsData = TTYD64_nok_paragoomba_ActorParts,
    .initScript = &TTYD64_nok_fuzzy_EVS_Init_8022B6C8,
    .statusTable = b_area_nok_paragoomba_FlyingStatusTable,
    .escapeChance = 90,
    .airLiftChance = 100,
    .hurricaneChance = 100,
    .spookChance = 100,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 36, 26 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_nok_goomba = {
    .flags = 0x0,
    .maxHP = 2,
    .type = 0x07,
    .level = 5,
    .partCount = 1,
    .partsData = TTYD64_nok_goomba_ActorParts,
    .initScript = &TTYD64_nok_goomba_EVS_Init,
    .statusTable = b_area_nok_goomba_StatusTable,
    .escapeChance = 90,
    .airLiftChance = 100,
    .hurricaneChance = 90,
    .spookChance = 100,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 24, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_nok_fuzzy = {
    .flags = 0x0,
    .maxHP = 3,
    .type = 0x0A,
    .level = 6,
    .partCount = 1,
    .partsData = TTYD64_nok_fuzzy_ActorParts,
    .initScript = &TTYD64_nok_fuzzy_EVS_Init_8022B3D0,
    .statusTable = b_area_nok_fuzzy_StatusTable,
    .escapeChance = 50,
    .airLiftChance = 95,
    .hurricaneChance = 95,
    .spookChance = 95,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 33, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_nok_paratroopa = {
    .flags = 0x200,
    .maxHP = 4,
    .type = 0x0C,
    .level = 6,
    .partCount = 3,
    .partsData = TTYD64_nok_paratroopa_ActorParts,
    .initScript = &TTYD64_nok_paratroopa_EVS_Flying_Init,
    .statusTable = b_area_nok_paratroopa_FlyingStatusTable,
    .escapeChance = 60,
    .airLiftChance = 95,
    .hurricaneChance = 100,
    .spookChance = 90,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 50, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 29 },
    .statusTextOffset = { 8, 30 },
};

ActorBlueprint TTYD64_nok_kent_c_koopa = {
    .flags = 0x0,
    .maxHP = 70,
    .type = 0xB9,
    .level = 55,
    .partCount = 9,
    .partsData = TTYD64_nok_kent_c_koopa_ActorParts,
    .initScript = &TTYD64_nok_kent_c_koopa_EVS_Init,
    .statusTable = b_area_nok_kent_c_koopa_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 70,
    .coinReward = 0,
    .size = { 90, 70 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -26, 38 },
    .statusTextOffset = { 2, 63 },
};

ActorPartBlueprint TTYD64_nok_goomba_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_nok_goomba_DefaultAnims,
        .defenseTable = b_area_nok_goomba_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_nok_koopa_troopa_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 36 },
        .opacity = 255,
        .idleAnimations = TTYD64_nok_paratroopa_DownedAnims,
        .defenseTable = b_area_nok_paratroopa_DownedDefense,
        .eventFlags = 0x1000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -7 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_nok_spiked_goomba_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_nok_spiked_goomba_DefaultAnims,
        .defenseTable = b_area_nok_paragoomba_FlyingDefense,
        .eventFlags = 0x10,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_nok_fuzzy_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_nok_fuzzy_DefaultAnims,
        .defenseTable = b_area_nok_fuzzy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_nok_Formation_15[] = {
    { .actor = &TTYD64_nok_fuzzy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
};

FormationRow TTYD64_nok_Formation_18[] = {
    { .actor = &TTYD64_nok_kent_c_koopa,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

void TTYD64_InstallBattles_nok(void) {
    Mod_SetBattleList("TTYD64", 5, TTYD64_nok_Formations);
}
