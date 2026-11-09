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
API_CALLABLE(AddActorVar);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(DropStarPoints);
API_CALLABLE(EnableBattleStatusBar);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FallToGoal);
API_CALLABLE(FlyToGoal);
API_CALLABLE(ForceHomePos);
API_CALLABLE(FreezeBattleState);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetDamageSource);
API_CALLABLE(GetEncounterTrigger);
API_CALLABLE(GetEnemyMaxHP);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetIndexFromHome);
API_CALLABLE(GetLastDamage);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToCurrent);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HealActor);
API_CALLABLE(HideHealthBar);
API_CALLABLE(IdleFlyToGoal);
API_CALLABLE(IdleRunToGoal);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
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
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetEnemyHP);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHPBarOffset);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetIdleGoal);
API_CALLABLE(SetPartDispOffset);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartFlags);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartRotation);
API_CALLABLE(SetPartRotationOffset);
API_CALLABLE(SetStatusTable);
API_CALLABLE(SetTargetActor);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowHealthBar);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
API_CALLABLE(b_area_kmr_part_3_downed_goomba_CalculateArcsinDeg);
API_CALLABLE(b_area_kmr_part_3_downed_goomba_tutorial_CalculateArcsinDeg);
API_CALLABLE(b_area_kmr_part_3_final_jr_troopa_CalculateArcsinDeg);
API_CALLABLE(b_area_kmr_part_3_final_jr_troopa_SetBackgroundAlpha);
API_CALLABLE(b_area_kmr_part_3_final_jr_troopa_UnkBackgroundFunc3);
API_CALLABLE(b_area_kmr_part_3_paragoomba_StartRumbleWithParams);
API_CALLABLE(b_area_kmr_part_3_spiked_para_jr_troopa_FreePointerHudElem);
API_CALLABLE(b_area_kmr_part_3_spiked_para_jr_troopa_ShowPointerHudElem);
API_CALLABLE(b_area_kmr_part_3_tutorial_paragoomba_StartRumbleWithParams);
API_CALLABLE(b_area_kmr_part_3_tutorial_spiked_goomba_CalculateArcsinDeg);
extern s32 b_area_kmr_part_3_egg_jr_troopa_DefenseTable[];
extern EvtScript b_area_kmr_part_3_egg_jr_troopa_EVS_HandleEvent;
extern EvtScript b_area_kmr_part_3_egg_jr_troopa_EVS_HandlePhase;
extern EvtScript b_area_kmr_part_3_egg_jr_troopa_EVS_Idle;
extern EvtScript b_area_kmr_part_3_egg_jr_troopa_EVS_ReenterEgg;
extern s32 b_area_kmr_part_3_egg_jr_troopa_StatusTable[];
extern s32 b_area_kmr_part_3_final_jr_troopa_BaseDefenseTable[];
extern s32 b_area_kmr_part_3_final_jr_troopa_BaseStatusTable[];
extern s32 b_area_kmr_part_3_final_jr_troopa_DefeatedAnims[];
extern EvtScript b_area_kmr_part_3_final_jr_troopa_EVS_Cam_FocusOnJrTroopa;
extern EvtScript b_area_kmr_part_3_final_jr_troopa_EVS_Cam_ResetFocus;
extern EvtScript b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims;
extern EvtScript b_area_kmr_part_3_final_jr_troopa_EVS_HandlePhase;
extern EvtScript b_area_kmr_part_3_final_jr_troopa_EVS_Idle;
extern EvtScript b_area_kmr_part_3_final_jr_troopa_EVS_JrTroopa_BaseDeath;
extern EvtScript b_area_kmr_part_3_final_jr_troopa_EVS_ReturnHome;
extern EvtScript b_area_kmr_part_3_final_jr_troopa_EVS_SetupFearReaction;
extern EvtScript b_area_kmr_part_3_final_jr_troopa_EVS_TransformFX;
extern EvtScript b_area_kmr_part_3_final_jr_troopa_EVS_Transform_Flying;
extern EvtScript b_area_kmr_part_3_final_jr_troopa_EVS_TryFearReaction;
extern s32 b_area_kmr_part_3_final_jr_troopa_FlyingDefenseTable[];
extern s32 b_area_kmr_part_3_final_jr_troopa_MageDefenseTable[];
extern s32 b_area_kmr_part_3_final_jr_troopa_MageStatusTable[];
extern s32 b_area_kmr_part_3_jr_troopa_DefenseTable[];
extern EvtScript b_area_kmr_part_3_jr_troopa_EVS_Cam_FocusOnGoompa;
extern EvtScript b_area_kmr_part_3_jr_troopa_EVS_Cam_FocusOnJrTroopa;
extern EvtScript b_area_kmr_part_3_jr_troopa_EVS_JrTroopa_Death;
extern s32 b_area_kmr_part_3_jr_troopa_StatusTable[];
extern Stage b_area_kmr_part_3_kmr_03;
extern Stage b_area_kmr_part_3_kmr_05b;
extern Stage b_area_kmr_part_3_kpa_13;
extern Stage b_area_kmr_part_3_mac_01;
extern s32 b_area_kmr_part_3_mage_jr_troopa_DefenseTable[];
extern EvtScript b_area_kmr_part_3_mage_jr_troopa_EVS_Cam_FocusOnJrTroopa;
extern EvtScript b_area_kmr_part_3_mage_jr_troopa_EVS_Cam_ResetFocus;
extern EvtScript b_area_kmr_part_3_mage_jr_troopa_EVS_HandlePhase;
extern EvtScript b_area_kmr_part_3_mage_jr_troopa_EVS_Idle;
extern EvtScript b_area_kmr_part_3_mage_jr_troopa_EVS_JrTroopa_Death;
extern EvtScript b_area_kmr_part_3_mage_jr_troopa_EVS_SetupFearReaction;
extern EvtScript b_area_kmr_part_3_mage_jr_troopa_EVS_TryFearReaction;
extern s32 b_area_kmr_part_3_mage_jr_troopa_StatusTable[];
extern Stage b_area_kmr_part_3_mim_01;
extern Stage b_area_kmr_part_3_nok_01;
extern s32 b_area_kmr_part_3_para_jr_troopa_DefeatedAnims[];
extern s32 b_area_kmr_part_3_para_jr_troopa_DefenseTable[];
extern EvtScript b_area_kmr_part_3_para_jr_troopa_EVS_Cam_FocusOnJrTroopa;
extern EvtScript b_area_kmr_part_3_para_jr_troopa_EVS_Cam_ResetFocus;
extern EvtScript b_area_kmr_part_3_para_jr_troopa_EVS_HandlePhase;
extern EvtScript b_area_kmr_part_3_para_jr_troopa_EVS_Idle;
extern EvtScript b_area_kmr_part_3_para_jr_troopa_EVS_SetupFearReaction;
extern EvtScript b_area_kmr_part_3_para_jr_troopa_EVS_TryFearReaction;
extern s32 b_area_kmr_part_3_para_jr_troopa_StatusTable[];
extern s32 b_area_kmr_part_3_paragoomba_DownedStatusTable[];
extern EvtScript b_area_kmr_part_3_paragoomba_EVS_Paragoomba_GoHome;
extern Stage b_area_kmr_part_3_sam_01;
extern s32 b_area_kmr_part_3_spiked_para_jr_troopa_DefeatedAnims[];
extern s32 b_area_kmr_part_3_spiked_para_jr_troopa_DefenseTable[];
extern EvtScript b_area_kmr_part_3_spiked_para_jr_troopa_EVS_Cam_FocusOnJrTroopa;
extern EvtScript b_area_kmr_part_3_spiked_para_jr_troopa_EVS_Cam_ResetFocus;
extern EvtScript b_area_kmr_part_3_spiked_para_jr_troopa_EVS_Idle;
extern EvtScript b_area_kmr_part_3_spiked_para_jr_troopa_EVS_SetupFearReaction;
extern EvtScript b_area_kmr_part_3_spiked_para_jr_troopa_EVS_SetupHitReaction;
extern EvtScript b_area_kmr_part_3_spiked_para_jr_troopa_EVS_Transform;
extern EvtScript b_area_kmr_part_3_spiked_para_jr_troopa_EVS_TryFearReaction;
extern EvtScript b_area_kmr_part_3_spiked_para_jr_troopa_EVS_TryHitReaction;
extern s32 b_area_kmr_part_3_spiked_para_jr_troopa_StatusTable[];
extern s32 b_area_kmr_part_3_spiked_para_jr_troopa_WindedAnims[];
extern s32 b_area_kmr_part_3_tutorial_paragoomba_DownedDefense[];
extern s32 b_area_kmr_part_3_tutorial_paragoomba_DownedStatusTable[];
extern EvtScript b_area_kmr_part_3_tutorial_paragoomba_EVS_HandlePhase;
extern EvtScript b_area_kmr_part_3_tutorial_paragoomba_EVS_Paragoomba_GoHome;
extern s32 b_area_kmr_part_3_tutorial_paragoomba_FlyingDefense[];
extern s32 b_area_kmr_part_3_tutorial_paragoomba_FlyingStatusTable[];
extern s32 b_area_kmr_part_3_tutorial_paragoomba_LeftWingAnims[];
extern s32 b_area_kmr_part_3_tutorial_paragoomba_RightWingAnims[];
extern EvtScript b_area_kmr_part_3_tutorial_spiked_goomba_EVS_HandlePhase;
extern s32 b_area_kmr_part_3_tutorial_spiked_goomba_StatusTable[];
extern EvtScript TTYD64_kmr_part_3_tutorial_spiked_goomba_EVS_TakeTurn;
extern EvtScript TTYD64_kmr_part_3_downed_goomba_tutorial_EVS_TakeTurn;
extern EvtScript TTYD64_kmr_part_3_downed_goomba_EVS_TakeTurn;
extern EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_Leap;
extern EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_SpikeDive;
extern EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_LightningBolt;
extern EvtScript TTYD64_kmr_part_3_jr_troopa_EVS_TakeTurn;
extern EvtScript TTYD64_kmr_part_3_tutorial_paragoomba_EVS_TakeTurn;
extern EvtScript TTYD64_kmr_part_3_paragoomba_EVS_TakeTurn;
extern EvtScript TTYD64_kmr_part_3_egg_jr_troopa_EVS_TakeTurn;
extern EvtScript TTYD64_kmr_part_3_para_jr_troopa_EVS_TakeTurn;
extern EvtScript TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_TakeTurn;
extern EvtScript TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_3_tutorial_spiked_goomba_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_MagicSpell;
extern EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_Swoop;
extern EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_JrTroopa_Death;
extern EvtScript TTYD64_kmr_part_3_mage_jr_troopa_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_3_mage_jr_troopa_EVS_TakeTurn;
extern EvtScript TTYD64_kmr_part_3_downed_goomba_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_3_downed_goomba_tutorial_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_3_para_jr_troopa_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_3_jr_troopa_EVS_HandlePhase;
extern EvtScript TTYD64_kmr_part_3_paragoomba_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_3_tutorial_paragoomba_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_3_tutorial_paragoomba_EVS_KnockDown;
extern EvtScript TTYD64_kmr_part_3_paragoomba_EVS_KnockDown;
extern EvtScript TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_HandlePhase;
extern EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Move_HealSelf;
extern EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_TakeTurn;
extern EvtScript TTYD64_kmr_part_3_jr_troopa_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_3_para_jr_troopa_EVS_JrTroopa_Death;
extern EvtScript TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_JrTroopa_Death;
extern EvtScript TTYD64_kmr_part_3_tutorial_spiked_goomba_EVS_Idle;
extern EvtScript TTYD64_kmr_part_3_downed_goomba_tutorial_EVS_Idle;
extern EvtScript TTYD64_kmr_part_3_downed_goomba_EVS_Idle;
extern EvtScript TTYD64_kmr_part_3_tutorial_paragoomba_EVS_Idle;
extern EvtScript TTYD64_kmr_part_3_paragoomba_EVS_Idle;
extern EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Transform_Mage;
extern EvtScript TTYD64_kmr_part_3_para_jr_troopa_EVS_JrTroopa_FlyHome;
extern EvtScript TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_JrTroopa_FlyHome;
extern EvtScript TTYD64_kmr_part_3_jr_troopa_EVS_Init;
extern EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Init;
extern EvtScript TTYD64_kmr_part_3_mage_jr_troopa_EVS_Init;
extern EvtScript TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_Init;
extern EvtScript TTYD64_kmr_part_3_egg_jr_troopa_EVS_Init;
extern EvtScript TTYD64_kmr_part_3_para_jr_troopa_EVS_Init;
extern EvtScript TTYD64_kmr_part_3_tutorial_paragoomba_EVS_Init_Tutorial;
extern EvtScript TTYD64_kmr_part_3_tutorial_paragoomba_EVS_Init_Tutorial_802334C4;
extern EvtScript TTYD64_kmr_part_3_paragoomba_EVS_Init;
extern EvtScript TTYD64_kmr_part_3_downed_goomba_EVS_Init;
extern EvtScript TTYD64_kmr_part_3_downed_goomba_tutorial_EVS_Init;
extern ActorBlueprint TTYD64_kmr_part_3_egg_jr_troopa;
extern ActorBlueprint TTYD64_kmr_part_3_para_jr_troopa;
extern ActorBlueprint TTYD64_kmr_part_3_jr_troopa;
extern ActorBlueprint TTYD64_kmr_part_3_final_jr_troopa;
extern ActorBlueprint TTYD64_kmr_part_3_spiked_para_jr_troopa;
extern ActorBlueprint TTYD64_kmr_part_3_mage_jr_troopa;
extern ActorBlueprint TTYD64_kmr_part_3_tutorial_paragoomba;
extern ActorBlueprint TTYD64_kmr_part_3_tutorial_paragoomba_80234300;
extern ActorBlueprint TTYD64_kmr_part_3_tutorial_spiked_goomba;
extern Battle TTYD64_kmr_part_3_Formations[];
extern ActorPartBlueprint TTYD64_kmr_part_3_tutorial_paragoomba_ActorParts[];
extern ActorPartBlueprint TTYD64_kmr_part_3_tutorial_paragoomba_ActorParts_80232EFC[];
extern ActorPartBlueprint TTYD64_kmr_part_3_final_jr_troopa_ActorParts[];
extern s32 TTYD64_kmr_part_3_downed_goomba_tutorial_ShuffleAnims[];
extern s32 TTYD64_kmr_part_3_tutorial_paragoomba_ShuffleAnims[];
extern s32 TTYD64_kmr_part_3_downed_goomba_ShuffleAnims[];
extern s32 TTYD64_kmr_part_3_tutorial_spiked_goomba_ShuffleAnims[];
extern s32 TTYD64_kmr_part_3_downed_goomba_tutorial_DefaultAnims[];
extern s32 TTYD64_kmr_part_3_downed_goomba_tutorial_DefaultAnims_80233844[];
extern s32 TTYD64_kmr_part_3_tutorial_paragoomba_DefaultAnims[];
extern s32 TTYD64_kmr_part_3_tutorial_paragoomba_DefaultAnims_802338DC[];
extern s32 TTYD64_kmr_part_3_paragoomba_ShuffleAnims[];
extern s32 TTYD64_kmr_part_3_tutorial_spiked_goomba_DefaultAnims[];
extern ActorPartBlueprint TTYD64_kmr_part_3_para_jr_troopa_ActorParts[];
extern ActorPartBlueprint TTYD64_kmr_part_3_mage_jr_troopa_ActorParts[];
extern ActorPartBlueprint TTYD64_kmr_part_3_spiked_para_jr_troopa_ActorParts[];
extern s32 TTYD64_kmr_part_3_mage_jr_troopa_MageAnims[];
extern s32 TTYD64_kmr_part_3_mage_jr_troopa_BaseAnims[];
extern s32 TTYD64_kmr_part_3_para_jr_troopa_BaseAnims[];
extern s32 TTYD64_kmr_part_3_spiked_para_jr_troopa_DefaultAnims[];
extern s32 TTYD64_kmr_part_3_para_jr_troopa_FlyingAnims[];
extern s32 TTYD64_kmr_part_3_jr_troopa_DefaultAnims[];
extern s32 TTYD64_kmr_part_3_egg_jr_troopa_DefaultAnims[];
extern FormationRow TTYD64_kmr_part_3_Formation_01[];
extern s32 TTYD64_kmr_part_3_final_jr_troopa_MageAnims[];
extern s32 TTYD64_kmr_part_3_final_jr_troopa_FlyingAnims[];
extern s32 TTYD64_kmr_part_3_final_jr_troopa_BaseAnims[];
extern ActorPartBlueprint TTYD64_kmr_part_3_tutorial_spiked_goomba_ActorParts[];
extern ActorPartBlueprint TTYD64_kmr_part_3_egg_jr_troopa_ActorParts[];
extern ActorPartBlueprint TTYD64_kmr_part_3_jr_troopa_ActorParts[];
extern FormationRow TTYD64_kmr_part_3_Formation_00[];
extern FormationRow TTYD64_kmr_part_3_Formation_04[];
extern FormationRow TTYD64_kmr_part_3_Formation_05[];
extern FormationRow TTYD64_kmr_part_3_Formation_02[];
extern FormationRow TTYD64_kmr_part_3_Formation_03[];
extern FormationRow TTYD64_kmr_part_3_Formation_06[];
extern FormationRow TTYD64_kmr_part_3_Formation_07[];

// clang-format off
EvtScript TTYD64_kmr_part_3_tutorial_spiked_goomba_EVS_TakeTurn = {
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
                    Call(b_area_kmr_part_3_tutorial_spiked_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
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
                    Call(b_area_kmr_part_3_tutorial_spiked_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
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
EvtScript TTYD64_kmr_part_3_downed_goomba_tutorial_EVS_TakeTurn = {
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
                    Call(b_area_kmr_part_3_downed_goomba_tutorial_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
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
                    Call(b_area_kmr_part_3_downed_goomba_tutorial_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
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
EvtScript TTYD64_kmr_part_3_downed_goomba_EVS_TakeTurn = {
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
                    Call(b_area_kmr_part_3_downed_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
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
                    Call(b_area_kmr_part_3_downed_goomba_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
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
EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_Leap = {
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
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x210009)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar0, 20)
    Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0, 0, 8, 16)
    Switch(LVarF)
        CaseEq(5)
            Thread
                Call(SetAnimation, ACTOR_SELF, 1, 0x21000A)
                Wait(5)
                Call(SetAnimation, ACTOR_SELF, 1, 0x21000C)
            EndThread
            Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210021)
            Thread
                Wait(3)
                Call(SetAnimation, ACTOR_SELF, 1, 0x210014)
            EndThread
            Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
            Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(FlyToGoal, ACTOR_SELF, 16, 0, 5)
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(SetAnimation, ACTOR_SELF, 1, 0x21000B)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        CaseEq(6)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210009)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 50)
            Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetActorSounds, ACTOR_SELF, 2, 8418, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x21000E)
            Wait(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x21000F)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 10)
            Set(LVar1, 0)
            Add(LVar2, 3)
            Thread
                Wait(8)
                Call(SetAnimation, ACTOR_SELF, 1, 0x210010)
            EndThread
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 18, 0, 1, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210024)
            Sub(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Sub(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(UseBattleCamPreset, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210009)
            Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x210009)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetActorSounds, ACTOR_SELF, 2, 8418, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x21000E)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
    Call(SetAnimation, ACTOR_SELF, 1, 0x21000F)
    Thread
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 1, 0x210010)
    EndThread
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 128, 0, 0, 8, 32)
    Call(ResetAllActorSounds, ACTOR_SELF)
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
    Sub(LVar0, 10)
    Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
    Wait(8)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x210009)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_SpikeDive = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Wait(20)
    Call(PlaySoundAtActor, ACTOR_SELF, 767)
    Call(SetAnimation, ACTOR_SELF, 2, 0x230011)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 2, 0x230005)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 705)
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0, 0, 6, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            Thread
                Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
                Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Sub(LVar0, 10)
                Set(LVar1, 12)
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            EndThread
            Set(LVar0, 0)
            Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
            Loop(20)
                Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                Call(b_area_kmr_part_3_final_jr_troopa_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, LVar0)
                Set(LVar1, LVar4)
                Set(LVar2, LVar5)
                Set(LVar3, LVar6)
                Wait(1)
            EndLoop
            IfEq(LVarF, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(ResetAllActorSounds, ACTOR_SELF)
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
                Sub(LVar1, 40)
                Set(LVar2, 10)
                Call(SetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
                Call(JumpToGoal, ACTOR_SELF, 14, 0, 1, 0)
            EndThread
            Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
            Loop(14)
                Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                Call(b_area_kmr_part_3_final_jr_troopa_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                Set(LVar7, LVar0)
                Add(LVar7, 180)
                Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, LVar7)
                Set(LVar1, LVar4)
                Set(LVar2, LVar5)
                Set(LVar3, LVar6)
                Wait(1)
            EndLoop
            Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, 0)
            Call(SetPartRotationOffset, ACTOR_SELF, 2, 0, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 980)
            Call(SetAnimation, ACTOR_SELF, 2, 0x230012)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 2, 0x230007)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 0, -5, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseDefault
    EndSwitch
    Call(SetPartRotationOffset, ACTOR_SELF, 2, 0, 12, 0)
    Thread
        Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
    EndThread
    Set(LVar0, 0)
    Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Loop(20)
        Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
        Call(b_area_kmr_part_3_final_jr_troopa_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
        Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, LVar0)
        Set(LVar1, LVar4)
        Set(LVar2, LVar5)
        Set(LVar3, LVar6)
        Wait(1)
    EndLoop
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0, 0, 9, 32)
    Call(UseBattleCamPreset, 2)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
        Add(LVar1, 40)
        Call(SetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
        Call(JumpToGoal, ACTOR_SELF, 14, 0, 1, 0)
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Loop(14)
        Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
        Call(b_area_kmr_part_3_final_jr_troopa_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
        Set(LVar7, LVar0)
        Add(LVar7, 180)
        Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, LVar7)
        Set(LVar1, LVar4)
        Set(LVar2, LVar5)
        Set(LVar3, LVar6)
        Wait(1)
    EndLoop
    Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, 0)
    Call(SetPartRotationOffset, ACTOR_SELF, 2, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 980)
    Call(SetAnimation, ACTOR_SELF, 2, 0x230012)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 2, 0x230007)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetGoalToHome, ACTOR_SELF)
    Call(FlyToGoal, ACTOR_SELF, 0, -5, 0)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_LightningBolt = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 3, 0x240006)
    Wait(8)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Set(LVar3, 0)
        Set(LVar4, 36)
        SetF(LVar5, Float(1.0))
    Else
        Set(LVar3, 0)
        Set(LVar4, 14)
        SetF(LVar5, MapFlag(-1999590))
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, LVar3)
    Add(LVar1, LVar4)
    Call(PlayEffect_impl, 19, 0, LVar0, LVar1, LVar2, LVar5, 30, 0, 0, 0, 0, 0, 0, 0)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 60)
    Wait(30)
    Call(PlaySoundAtActor, ACTOR_SELF, 998)
    Call(SetAnimation, ACTOR_SELF, 3, 0x240007)
    Call(b_area_kmr_part_3_final_jr_troopa_UnkBackgroundFunc3)
    Call(MakeLerp, 0, 200, 60, 10)
    Label(0)
    Call(UpdateLerp)
    Call(b_area_kmr_part_3_final_jr_troopa_SetBackgroundAlpha, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    Call(GetOwnerTarget, LVarA, 0)
    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(RandInt, 40, LVar1)
    Add(LVar0, LVar1)
    Add(LVar0, 50)
    Set(LVar1, 200)
    Call(PlaySoundAtActor, ACTOR_SELF, 870)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0x10000000, 0, 1, 16)
    Switch(LVarA)
        CaseEq(6)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar3, 0, LVar5)
            Call(PlayEffect_impl, 94, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.0), 18, 0, 0, 0, 0)
            Wait(20)
            Call(MakeLerp, 200, 0, 60, 0)
            Label(2)
            Call(UpdateLerp)
            Call(b_area_kmr_part_3_final_jr_troopa_SetBackgroundAlpha, LVar0)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(2)
            EndIf
            Wait(20)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        CaseEq(5)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(RandInt, 40, LVar1)
            Sub(LVar0, LVar1)
            Set(LVar1, 200)
            Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Call(PlayEffect_impl, 94, 0, LVar0, LVar1, LVar2, LVar3, 0, LVar5, Float(1.0), 18, 0, 0, 0, 0)
            Thread
                Wait(10)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 12)
                Call(PlayEffect_impl, 62, 0, LVar0, LVar1, LVar2, Float(3.0), 30, 0, 0, 0, 0, 0, 0, 0)
                Call(SetAnimation, ACTOR_SELF, 3, 0x240008)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Wait(40)
                Sub(LVar0, 7)
                Add(LVar1, 14)
                Add(LVar2, 4)
                Call(PlayEffect_impl, 7, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                Wait(20)
                Call(SetAnimation, ACTOR_SELF, 3, 0x240002)
            EndThread
            Wait(20)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(MakeLerp, 200, 0, 60, 0)
            Label(2)
            Call(UpdateLerp)
            Call(b_area_kmr_part_3_final_jr_troopa_SetBackgroundAlpha, LVar0)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(2)
            EndIf
            Wait(20)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, 0, LVar5)
    Call(PlayEffect_impl, 94, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.0), 18, 0, 0, 0, 0)
    Wait(14)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000030, 0, 0x10000, 9, 32)
    Call(UseBattleCamPreset, 2)
    Call(MakeLerp, 200, 0, 60, 0)
    Label(2)
    Call(UpdateLerp)
    Call(b_area_kmr_part_3_final_jr_troopa_SetBackgroundAlpha, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(2)
    EndIf
    Wait(20)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_jr_troopa_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(AddActorVar, ACTOR_SELF, 0, 1)
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
    Sub(LVar1, LVar0)
    IfEq(LVar1, 3)
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        IfEq(LVar0, 0)
            Call(SetActorVar, ACTOR_SELF, 5, 1)
            ExecWait(b_area_kmr_part_3_jr_troopa_EVS_Cam_FocusOnJrTroopa)
            Call(MoveBattleCamOver, 20)
            Wait(20)
            Call(UseIdleAnimation, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 0)
            Call(ActorSpeak, 0xB00B1, ACTOR_SELF, 1, 0x210016, 0x210003)
        EndIf
    EndIf
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x210009)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x21000E)
    Call(SetActorSounds, ACTOR_SELF, 2, 8418, 0)
    Call(GetActorVar, ACTOR_SELF, 4, LVar1)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, LVar1, 16)
    Switch(LVar0)
        CaseEq(6)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Add(LVar0, 30)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Sub(LVar0, 10)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
            Wait(8)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x210009)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
            Return
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
    Thread
        Wait(3)
        Call(SetAnimation, ACTOR_SELF, 1, 0x21000F)
        Wait(5)
        Call(SetAnimation, ACTOR_SELF, 1, 0x210010)
    EndThread
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Wait(2)
    Call(GetActorVar, ACTOR_SELF, 4, LVar1)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, LVar1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(ResetAllActorSounds, ACTOR_SELF)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
            Wait(10)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x210009)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_tutorial_paragoomba_EVS_TakeTurn = {
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
            ExecWait(b_area_kmr_part_3_tutorial_paragoomba_EVS_Paragoomba_GoHome)
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
            ExecWait(b_area_kmr_part_3_tutorial_paragoomba_EVS_Paragoomba_GoHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_paragoomba_EVS_TakeTurn = {
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
            ExecWait(b_area_kmr_part_3_paragoomba_EVS_Paragoomba_GoHome)
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
            ExecWait(b_area_kmr_part_3_paragoomba_EVS_Paragoomba_GoHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_egg_jr_troopa_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 980)
    Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
    Wait(20)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x210009)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x21000E)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 2, 16)
    Switch(LVarA)
        CaseOrEq(5)
        CaseOrEq(6)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x21000F)
            Thread
                Wait(8)
                Call(SetAnimation, ACTOR_SELF, 1, 0x210010)
            EndThread
            Call(GetOwnerTarget, LVar1, 0)
            Call(GetActorPos, LVar1, LVar0, LVar1, LVar2)
            Set(LVar1, 0)
            Add(LVar2, 5)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(2)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 25)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x21000B)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            ExecWait(b_area_kmr_part_3_egg_jr_troopa_EVS_ReenterEgg)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
    Thread
        Wait(3)
        Call(SetAnimation, ACTOR_SELF, 1, 0x21000F)
        Wait(5)
        Call(SetAnimation, ACTOR_SELF, 1, 0x210010)
    EndThread
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 2, 32)
    Switch(LVar0)
        CaseDefault
            Call(UseBattleCamPreset, 2)
            Call(ResetAllActorSounds, ACTOR_SELF)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
            Wait(10)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x210009)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
            ExecWait(b_area_kmr_part_3_egg_jr_troopa_EVS_ReenterEgg)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_para_jr_troopa_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVarA, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetTargetActor, ACTOR_SELF, LVarA)
    Call(SetAnimation, ACTOR_SELF, 1, 0x250005)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 5, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(10)
            Call(UseBattleCamPreset, 66)
            Call(SetBattleCamTargetingModes, -1, 1, 0)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(SetActorSounds, ACTOR_SELF, 2, 8416, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x250005)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 705)
            Call(SetGoalToTarget, ACTOR_SELF)
            Sub(LVar0, 80)
            Set(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x250006)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x250005)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x250002)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Return
        EndCaseGroup
        CaseDefault
            Wait(10)
            Call(UseBattleCamPreset, 66)
            Call(SetBattleCamTargetingModes, -1, 1, 0)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(SetActorSounds, ACTOR_SELF, 2, 8416, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x250005)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 705)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x250006)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    EndSwitch
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 5, 32)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x250005)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            Wait(10)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0x250005)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x250002)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVarA, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetTargetActor, ACTOR_SELF, LVarA)
    Call(SetAnimation, ACTOR_SELF, 1, 0x230007)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 6, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(10)
            Call(UseBattleCamPreset, 66)
            Call(SetBattleCamTargetingModes, -1, 1, 0)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(SetActorSounds, ACTOR_SELF, 2, 8416, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x230007)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 705)
            Call(SetGoalToTarget, ACTOR_SELF)
            Sub(LVar0, 80)
            Set(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x230008)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x230007)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x230003)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Return
        EndCaseGroup
        CaseDefault
            Wait(10)
            Call(UseBattleCamPreset, 66)
            Call(SetBattleCamTargetingModes, -1, 1, 0)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(SetActorSounds, ACTOR_SELF, 2, 8416, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x230007)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 705)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x230008)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    EndSwitch
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 6, 32)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x230007)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            Wait(10)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0x230007)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x230003)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_SetupHitReaction)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x230009)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_SetupHitReaction)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x230009)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_TryHitReaction)
            ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_SetupFearReaction)
            ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_TryFearReaction)
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x230009)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x230009)
            ExecWait(TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseEq(14)
            ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_SetupHitReaction)
            Set(LVar0, 1)
            Set(LVar1, 0x23000A)
            Set(LVar2, 0x23000B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_TryHitReaction)
        CaseEq(36)
            ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_SetupHitReaction)
            Set(LVar0, 1)
            Set(LVar1, 0x23000A)
            Set(LVar2, 0x23000B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x23000B)
            ExecWait(TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseEq(11)
            ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_SetupHitReaction)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x230009)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_TryHitReaction)
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x230009)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x230009)
            ExecWait(TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x230009)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x230009)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_JrTroopa_FlyHome)
            Call(SetAnimation, ACTOR_SELF, 1, 0x230003)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x230009)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x230009)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x230000)
            ExecWait(TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x230003)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_SetupFearReaction)
            ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_TryFearReaction)
        EndCaseGroup
        CaseEq(27)
            Wait(10)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            Switch(LVar3)
                CaseFlag(0x41000)
                    Add(LVar0, -13)
                    Add(LVar1, 37)
                CaseFlag(0x80000)
                    Add(LVar0, -1)
                    Add(LVar1, 14)
                CaseDefault
                    Add(LVar0, -4)
                    Add(LVar1, 37)
            EndSwitch
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(20)
        CaseEq(58)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x230010)
                Wait(1000)
            EndIf
        CaseEq(31)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x230010)
                Wait(20)
                ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_Cam_FocusOnJrTroopa)
                Call(ActorSpeak, 0x1D019B, ACTOR_SELF, 1, 0x23000F, 0x23000F)
                ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_Cam_ResetFocus)
            EndIf
        CaseEq(42)
            Call(SetAnimation, ACTOR_SELF, 1, 0x230009)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x230007)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x230003)
        CaseEq(53)
            ExecWait(TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_JrTroopa_FlyHome)
            Call(SetAnimation, ACTOR_SELF, 1, 0x230003)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x230003)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_tutorial_spiked_goomba_EVS_HandleEvent = {
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
EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_MagicSpell = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(SetAnimation, ACTOR_SELF, 3, 0x240006)
    Wait(8)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Set(LVar3, 0)
        Set(LVar4, 36)
        SetF(LVar5, Float(1.0))
    Else
        Set(LVar3, 0)
        Set(LVar4, 14)
        SetF(LVar5, MapFlag(-1999590))
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, LVar3)
    Add(LVar1, LVar4)
    Call(PlayEffect_impl, 19, 0, LVar0, LVar1, LVar2, LVar5, 30, 0, 0, 0, 0, 0, 0, 0)
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, 3, 0x240007)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0x10000000, 0, 1, 16)
    Switch(LVarA)
        CaseEq(6)
            Call(PlaySoundAtActor, ACTOR_SELF, 8405)
            Call(GetOwnerTarget, LVar1, 0)
            Call(GetActorPos, LVar1, LVar3, LVar4, LVar5)
            Sub(LVar3, 120)
            Add(LVar4, 20)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Set(LVar6, -8)
                Set(LVar7, 20)
                SetF(LVar8, Float(1.0))
            Else
                Set(LVar6, -3)
                Set(LVar7, 8)
                SetF(LVar8, MapFlag(-1999590))
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, LVar6)
            Add(LVar1, LVar7)
            Call(PlayEffect_impl, 18, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, 30, 0, 0, 0, 0, 0)
            Wait(35)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        CaseEq(5)
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 12)
                Call(PlayEffect_impl, 62, 0, LVar0, LVar1, LVar2, Float(3.0), 30, 0, 0, 0, 0, 0, 0, 0)
                Call(SetAnimation, ACTOR_SELF, 3, 0x240008)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Wait(40)
                Sub(LVar0, 7)
                Add(LVar1, 14)
                Add(LVar2, 4)
                Call(PlayEffect_impl, 7, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                Wait(20)
                Call(SetAnimation, ACTOR_SELF, 3, 0x240002)
            EndThread
            Wait(20)
            Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            Wait(40)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 8405)
    Call(GetOwnerTarget, LVar1, 0)
    Call(GetActorPos, LVar1, LVar3, LVar4, LVar5)
    Add(LVar4, 20)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Set(LVar6, -8)
        Set(LVar7, 20)
        SetF(LVar8, Float(1.0))
    Else
        Set(LVar6, -3)
        Set(LVar7, 8)
        SetF(LVar8, MapFlag(-1999590))
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, LVar6)
    Add(LVar1, LVar7)
    Call(PlayEffect_impl, 18, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, 15, 0, 0, 0, 0, 0)
    Wait(15)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 8, 32)
    Call(UseBattleCamPreset, 2)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_Swoop = {
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
    Call(SetAnimation, ACTOR_SELF, 2, 0x230007)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 6, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(10)
            Call(UseBattleCamPreset, 66)
            Call(SetBattleCamTargetingModes, -1, 1, 0)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(SetActorSounds, ACTOR_SELF, 2, 8416, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 2, 0x230007)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 705)
            Call(SetGoalToTarget, ACTOR_SELF)
            Sub(LVar0, 80)
            Set(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x230008)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 2, 0x230007)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 2, 0x230003)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Return
        EndCaseGroup
        CaseDefault
    EndSwitch
    Wait(10)
    Call(UseBattleCamPreset, 66)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetActorSounds, ACTOR_SELF, 2, 8416, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetAnimation, ACTOR_SELF, 2, 0x230007)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 705)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 2, 0x230008)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 8, 32)
    Call(UseBattleCamPreset, 2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetAnimation, ACTOR_SELF, 2, 0x230007)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    Wait(10)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(YieldTurn)
    Call(SetAnimation, ACTOR_SELF, 2, 0x230007)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(FlyToGoal, ACTOR_SELF, 0, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x230003)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVarA)
    Switch(LVarA)
        CaseEq(9)
            Set(LVar1, 0)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            Set(LVar1, 0)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_SetupFearReaction)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_TryFearReaction)
        CaseEq(32)
            Set(LVar1, 0)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            ExecWait(TTYD64_kmr_part_3_final_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseEq(14)
            Set(LVar1, 1)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            Set(LVar1, 1)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Wait(10)
            ExecWait(TTYD64_kmr_part_3_final_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseEq(11)
            Set(LVar1, 0)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            Set(LVar1, 0)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            ExecWait(TTYD64_kmr_part_3_final_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseEq(47)
            Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, 0)
            Call(SetPartRotationOffset, ACTOR_SELF, 2, 0, 0, 0)
            Set(LVar1, 0)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Set(LVar1, 0)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_ReturnHome)
        CaseEq(38)
            Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, 0)
            Call(SetPartRotationOffset, ACTOR_SELF, 2, 0, 0, 0)
            Set(LVar1, 0)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Set(LVar1, 0)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(TTYD64_kmr_part_3_final_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseEq(23)
            Set(LVar1, 5)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(25)
            Set(LVar1, 5)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_SetupFearReaction)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_TryFearReaction)
        CaseEq(27)
            Wait(10)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            Switch(LVar3)
                CaseFlag(0x41000)
                    Add(LVar0, -13)
                    Add(LVar1, 37)
                CaseFlag(0x80000)
                    Add(LVar0, -1)
                    Add(LVar1, 14)
                CaseDefault
                    Add(LVar0, -4)
                    Add(LVar1, 37)
            EndSwitch
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(20)
        CaseEq(58)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Set(LVar1, 2)
                ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
                Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
                Wait(1000)
            EndIf
        CaseEq(31)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Set(LVar1, 5)
                ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
                Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
                Wait(20)
                ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_Cam_FocusOnJrTroopa)
                Set(LVar1, 3)
                ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
                Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
                Call(ActorSpeak, 0x1D019B, ACTOR_SELF, LVar0, -1, -1)
                ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_Cam_ResetFocus)
            EndIf
        CaseEq(42)
            Set(LVar1, 0)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(53)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_ReturnHome)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x210003)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_JrTroopa_Death = {
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    Switch(LVar0)
        CaseEq(2)
            Call(UseBattleCamPreset, 2)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            IfEq(LVar1, 0)
                Goto(0)
            EndIf
            Call(PlaySoundAtActor, ACTOR_SELF, 769)
            Call(HideHealthBar, ACTOR_SELF)
            Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Call(FallToGoal, ACTOR_SELF, 10)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
            Call(ShowHealthBar, ACTOR_SELF)
            Label(0)
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 10)
                Add(LVar2, 10)
                Loop(3)
                    Call(PlayEffect_impl, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                    Wait(3)
                EndLoop
            EndThread
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 1, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210015)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 5)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Wait(15)
            Call(PlaySound, 997)
            Call(DropStarPoints, ACTOR_SELF)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(UseBattleCamPreset, 14)
            Call(SetBattleCamDist, 260)
            Call(SetBattleCamOffsetY, 15)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(MoveBattleCamOver, 30)
            Call(PlaySoundAtActor, ACTOR_SELF, 8421)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210014)
            Wait(60)
            Call(SetActorFlagBits, ACTOR_SELF, 0x400000, 1)
            Return
        CaseEq(3)
            Call(HideHealthBar, ACTOR_SELF)
            Call(UseIdleAnimation, ACTOR_SELF, 0)
            Call(GetDamageSource, LVar5)
            Switch(LVar5)
                CaseOrEq(10)
                CaseOrEq(14)
                CaseOrEq(12)
                CaseOrEq(16)
                CaseOrEq(11)
                CaseOrEq(15)
                CaseOrEq(13)
                CaseOrEq(17)
                CaseOrEq(2)
                EndCaseGroup
                CaseDefault
                    Set(LVar2, 0)
                    Loop(24)
                        Call(SetActorYaw, ACTOR_SELF, LVar2)
                        Add(LVar2, 30)
                        Wait(1)
                    EndLoop
                    Call(SetActorYaw, ACTOR_SELF, 0)
            EndSwitch
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 10)
                Add(LVar2, 10)
                Loop(3)
                    Call(PlayEffect_impl, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                    Wait(3)
                EndLoop
            EndThread
            Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 1, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210015)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 5)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Wait(15)
            Call(PlaySound, 997)
            Call(DropStarPoints, ACTOR_SELF)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(UseBattleCamPreset, 14)
            Call(SetBattleCamDist, 260)
            Call(SetBattleCamOffsetY, 15)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(MoveBattleCamOver, 30)
            Call(PlaySoundAtActor, ACTOR_SELF, 8421)
            Call(SetAnimation, ACTOR_SELF, 1, 0x210014)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_kmr_part_3_final_jr_troopa_DefeatedAnims))
            Wait(60)
            Call(SetActorFlagBits, ACTOR_SELF, 0x400000, 1)
            Return
        CaseDefault
            Set(LVar1, 0)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_GetFormAnims)
            ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_JrTroopa_BaseDeath)
            Return
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_mage_jr_troopa_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240009)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240009)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_kmr_part_3_mage_jr_troopa_EVS_SetupFearReaction)
            ExecWait(b_area_kmr_part_3_mage_jr_troopa_EVS_TryFearReaction)
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240009)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240000)
            ExecWait(b_area_kmr_part_3_mage_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseEq(14)
            Set(LVar0, 1)
            Set(LVar1, 0x24000A)
            Set(LVar2, 0x24000B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            Set(LVar0, 1)
            Set(LVar1, 0x24000A)
            Set(LVar2, 0x24000B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x24000B)
            ExecWait(b_area_kmr_part_3_mage_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240009)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240009)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240009)
            ExecWait(b_area_kmr_part_3_mage_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240009)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240009)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240005)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240009)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240009)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240000)
            ExecWait(b_area_kmr_part_3_mage_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240002)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            ExecWait(b_area_kmr_part_3_mage_jr_troopa_EVS_SetupFearReaction)
            ExecWait(b_area_kmr_part_3_mage_jr_troopa_EVS_TryFearReaction)
        EndCaseGroup
        CaseEq(58)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x24000F)
                Wait(1000)
            EndIf
        CaseEq(31)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x24000F)
                Wait(20)
                ExecWait(b_area_kmr_part_3_mage_jr_troopa_EVS_Cam_FocusOnJrTroopa)
                Call(ActorSpeak, 0x1D019B, ACTOR_SELF, 1, 0x24000E, 0x240003)
                Call(SetAnimation, ACTOR_SELF, 1, 0x240002)
                ExecWait(b_area_kmr_part_3_mage_jr_troopa_EVS_Cam_ResetFocus)
            EndIf
        CaseEq(42)
            Call(SetAnimation, ACTOR_SELF, 1, 0x240009)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x240005)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x240002)
        CaseEq(53)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240002)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x240002)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_mage_jr_troopa_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x240006)
    Wait(8)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Set(LVar3, 0)
        Set(LVar4, 36)
        SetF(LVar5, Float(1.0))
    Else
        Set(LVar3, 0)
        Set(LVar4, 14)
        SetF(LVar5, Float(0.400390625))
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, LVar3)
    Add(LVar1, LVar4)
    Call(PlayEffect_impl, 19, 0, LVar0, LVar1, LVar2, LVar5, 30, 0, 0, 0, 0, 0, 0, 0)
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x240007)
    Call(UseBattleCamPreset, 2)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0x10000000, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(PlaySoundAtActor, ACTOR_SELF, 8405)
            Call(GetOwnerTarget, LVar1, 0)
            Call(GetActorPos, LVar1, LVar3, LVar4, LVar5)
            Sub(LVar3, 120)
            Add(LVar4, 20)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Set(LVar6, -8)
                Set(LVar7, 20)
                SetF(LVar8, Float(1.0))
            Else
                Set(LVar6, -3)
                Set(LVar7, 8)
                SetF(LVar8, Float(0.400390625))
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, LVar6)
            Add(LVar1, LVar7)
            Call(PlayEffect_impl, 18, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, 30, 0, 0, 0, 0, 0)
            Wait(35)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 8405)
    Call(GetOwnerTarget, LVar1, 0)
    Call(GetActorPos, LVar1, LVar3, LVar4, LVar5)
    Add(LVar4, 20)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Set(LVar6, -8)
        Set(LVar7, 20)
        SetF(LVar8, Float(1.0))
    Else
        Set(LVar6, -3)
        Set(LVar7, 8)
        SetF(LVar8, Float(0.400390625))
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, LVar6)
    Add(LVar1, LVar7)
    Call(PlayEffect_impl, 18, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, 15, 0, 0, 0, 0, 0)
    Wait(15)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 8, 32)
    Switch(LVar0)
        CaseEq(0)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            IfEq(LVar0, 0)
                Call(GetOwnerTarget, LVar0, 0)
                Call(GetLastDamage, LVar0, LVar1)
                IfNe(LVar1, 0)
                    Call(SetActorVar, ACTOR_SELF, 1, 1)
                EndIf
            EndIf
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_downed_goomba_EVS_HandleEvent = {
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
EvtScript TTYD64_kmr_part_3_downed_goomba_tutorial_EVS_HandleEvent = {
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
EvtScript TTYD64_kmr_part_3_para_jr_troopa_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250007)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_kmr_part_3_para_jr_troopa_EVS_SetupFearReaction)
            ExecWait(b_area_kmr_part_3_para_jr_troopa_EVS_TryFearReaction)
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250007)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250007)
            ExecWait(TTYD64_kmr_part_3_para_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseEq(14)
            Set(LVar0, 1)
            Set(LVar1, 0x250008)
            Set(LVar2, 0x250009)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            Set(LVar0, 1)
            Set(LVar1, 0x250008)
            Set(LVar2, 0x250009)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250009)
            ExecWait(TTYD64_kmr_part_3_para_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250007)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250007)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250007)
            ExecWait(TTYD64_kmr_part_3_para_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250007)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250007)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(TTYD64_kmr_part_3_para_jr_troopa_EVS_JrTroopa_FlyHome)
            Call(SetAnimation, ACTOR_SELF, 1, 0x250002)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250007)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250007)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250002)
            ExecWait(TTYD64_kmr_part_3_para_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseEq(23)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250002)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250002)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            ExecWait(b_area_kmr_part_3_para_jr_troopa_EVS_SetupFearReaction)
            ExecWait(b_area_kmr_part_3_para_jr_troopa_EVS_TryFearReaction)
        CaseEq(42)
            Call(SetAnimation, ACTOR_SELF, 1, 0x250007)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x250005)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x250002)
        CaseEq(58)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x25000D)
                Wait(1000)
            EndIf
        CaseEq(31)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x25000D)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                ExecWait(b_area_kmr_part_3_para_jr_troopa_EVS_Cam_FocusOnJrTroopa)
                Call(ActorSpeak, 0x1D019B, ACTOR_SELF, 1, 0x25000C, 0x25000C)
                ExecWait(b_area_kmr_part_3_para_jr_troopa_EVS_Cam_ResetFocus)
            EndIf
        CaseEq(53)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250002)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x250002)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_jr_troopa_EVS_HandlePhase = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(10)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            IfEq(LVar0, 0)
                Call(SetActorVar, ACTOR_SELF, 1, 1)
                Wait(15)
                Call(EnableBattleStatusBar, 0)
                Call(SetAnimation, 0, 0, 0x10002)
                Thread
                    Set(LVar1, 0)
                    Wait(8)
                    Loop(5)
                        Wait(1)
                        Sub(LVar1, 36)
                        Call(SetActorYaw, 0, LVar1)
                    EndLoop
                EndThread
                Call(SetAnimation, ACTOR_SELF, 1, 0x21002B)
                Call(ActorSpeak, 0xB00AF, 256, 0, 0x9D0008, 0x9D0001)
                Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
                Call(SetAnimation, 0, 0, 0x10029)
                Wait(10)
                Thread
                    Set(LVar1, 180)
                    Wait(4)
                    Loop(5)
                        Wait(1)
                        Add(LVar1, 36)
                        Call(SetActorYaw, 0, LVar1)
                    EndLoop
                EndThread
                Wait(10)
                Call(EnableBattleStatusBar, 1)
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 4)
            EndIf
        CaseEq(12)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfEq(LVar0, 1)
                Call(SetActorVar, ACTOR_SELF, 2, 2)
                ExecWait(b_area_kmr_part_3_jr_troopa_EVS_Cam_FocusOnGoompa)
                Call(UseIdleAnimation, 0, 0)
                Call(SetAnimation, 0, 0, 0x10002)
                Thread
                    Set(LVar1, 0)
                    Loop(5)
                        Wait(1)
                        Sub(LVar1, 36)
                        Call(SetActorYaw, 0, LVar1)
                    EndLoop
                EndThread
                Call(UseIdleAnimation, 256, 0)
                Call(ActorSpeak, 0xB00B0, 256, 0, 0x9D0008, 0x9D0001)
                Call(UseIdleAnimation, 256, 1)
                Call(SetAnimation, 0, 0, 0x10032)
                Wait(20)
                Call(SetActorYaw, 0, 0)
                Wait(4)
                Call(UseIdleAnimation, 0, 1)
            EndIf
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            IfEq(LVar0, 0)
                Call(GetActorHP, ACTOR_SELF, LVar0)
                IfLe(LVar0, 1)
                    Call(SetActorVar, ACTOR_SELF, 3, 1)
                    Call(UseIdleAnimation, 256, 0)
                    Call(ActorSpeak, 0xB00B2, 256, 0, 0x9D0008, 0x9D0001)
                    Call(UseIdleAnimation, 256, 1)
                    ExecWait(b_area_kmr_part_3_jr_troopa_EVS_Cam_FocusOnJrTroopa)
                    Call(ActorSpeak, 0xB00B3, ACTOR_SELF, 1, 0x210016, 0x210003)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8377)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x21000B)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Add(LVar1, 16)
                    Call(PlayEffect_impl, 19, 0, LVar0, LVar1, LVar2, 1, 30, 0, 0, 0, 0, 0, 0, 0)
                    Call(PlayEffect_impl, 19, 1, LVar0, LVar1, LVar2, 1, 30, 0, 0, 0, 0, 0, 0, 0)
                    Wait(30)
                    Wait(20)
                    Call(SetActorVar, ACTOR_SELF, 4, 2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x210003)
                    Wait(20)
                EndIf
            EndIf
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_paragoomba_EVS_HandleEvent = {
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
                    ExecWait(TTYD64_kmr_part_3_paragoomba_EVS_KnockDown)
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
            ExecWait(TTYD64_kmr_part_3_paragoomba_EVS_KnockDown)
        CaseEq(15)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000D)
            SetConst(LVar2, 0x28000E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_kmr_part_3_paragoomba_EVS_KnockDown)
        CaseEq(47)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000F)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280006)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(SetAnimation, ACTOR_SELF, 2, 0x28000C)
            ExecWait(b_area_kmr_part_3_paragoomba_EVS_Paragoomba_GoHome)
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
            ExecWait(b_area_kmr_part_3_paragoomba_EVS_Paragoomba_GoHome)
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
EvtScript TTYD64_kmr_part_3_tutorial_paragoomba_EVS_HandleEvent = {
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
                    ExecWait(TTYD64_kmr_part_3_tutorial_paragoomba_EVS_KnockDown)
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
            ExecWait(TTYD64_kmr_part_3_tutorial_paragoomba_EVS_KnockDown)
        CaseEq(15)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000D)
            SetConst(LVar2, 0x28000E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_kmr_part_3_tutorial_paragoomba_EVS_KnockDown)
        CaseEq(47)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x28000F)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x280006)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(SetAnimation, ACTOR_SELF, 2, 0x28000C)
            ExecWait(b_area_kmr_part_3_tutorial_paragoomba_EVS_Paragoomba_GoHome)
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
            ExecWait(b_area_kmr_part_3_tutorial_paragoomba_EVS_Paragoomba_GoHome)
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
EvtScript TTYD64_kmr_part_3_tutorial_paragoomba_EVS_KnockDown = {
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
    Call(b_area_kmr_part_3_tutorial_paragoomba_StartRumbleWithParams, 100, 10)
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
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kmr_part_3_tutorial_paragoomba_DownedStatusTable))
    Call(SetActorType, ACTOR_SELF, 7)
    ExecWait(TTYD64_kmr_part_3_downed_goomba_tutorial_EVS_Init)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_paragoomba_EVS_KnockDown = {
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
    Call(b_area_kmr_part_3_paragoomba_StartRumbleWithParams, 100, 10)
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
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kmr_part_3_paragoomba_DownedStatusTable))
    Call(SetActorType, ACTOR_SELF, 7)
    ExecWait(TTYD64_kmr_part_3_downed_goomba_EVS_Init)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_HandlePhase = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(10)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 0)
                Call(SetActorVar, ACTOR_SELF, 0, 1)
                Wait(15)
                Call(UseBattleCamPreset, 14)
                Call(BattleCamTargetActor, ACTOR_SELF)
                Call(SetBattleCamOffsetY, 35)
                Call(MoveBattleCamOver, 30)
                Wait(20)
                Call(ActorSpeak, 0x700B8, ACTOR_SELF, 2, 0x210005, 0x210005)
                Wait(10)
                Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
                Call(SetHPBarOffset, ACTOR_SELF, -20, 40)
                Call(ShowHealthBar, ACTOR_SELF)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Set(LVar0, 115)
                Set(LVar1, 150)
                Call(b_area_kmr_part_3_spiked_para_jr_troopa_ShowPointerHudElem, LVar0, LVar1, LVarA)
                Wait(10)
                Call(GetEnemyMaxHP, ACTOR_SELF, LVar0)
                Set(LVar1, LVar0)
                Div(LVar1, 2)
                Label(0)
                Sub(LVar0, 1)
                Call(SetEnemyHP, ACTOR_SELF, LVar0)
                Wait(1)
                IfGt(LVar0, LVar1)
                    Goto(0)
                EndIf
                Call(SetAnimation, ACTOR_SELF, 2, 0x210013)
                Wait(15)
                Loop(2)
                    Call(SetActorFlagBits, ACTOR_SELF, 4096, 0)
                    Wait(15)
                    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
                    Wait(15)
                EndLoop
                Call(ActorSpeak, 0x700B9, ACTOR_SELF, 2, 0x210013, 0x210013)
                Call(SetActorFlagBits, ACTOR_SELF, 4096, 0)
                Call(b_area_kmr_part_3_spiked_para_jr_troopa_FreePointerHudElem, LVarA)
                Call(HideHealthBar, ACTOR_SELF)
                Call(SetHPBarOffset, ACTOR_SELF, 0, 0)
                Call(SetAnimation, ACTOR_SELF, 2, 0x210005)
                Wait(25)
                Call(ActorSpeak, 0x700BA, ACTOR_SELF, 2, 0x210016, 0x210003)
                Wait(10)
                ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_Transform)
                Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
                Call(SetPartFlagBits, ACTOR_SELF, 1, 1, 0)
                Wait(20)
                Call(SetGoalToHome, ACTOR_SELF)
                Call(AddGoalPos, ACTOR_SELF, 40, 80, 0)
                Call(FlyToGoal, ACTOR_SELF, 30, 0, 0)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(HPBarToHome, ACTOR_SELF)
                Wait(10)
                Call(ActorSpeak, 0x700BB, ACTOR_SELF, 1, 0x23000F, 0x230003)
                Wait(10)
                ExecWait(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_Cam_ResetFocus)
            EndIf
        CaseEq(12)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Move_HealSelf = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, 3, 0x240006)
    Wait(8)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Set(LVar3, 0)
        Set(LVar4, 36)
        SetF(LVar5, Float(1.0))
    Else
        Set(LVar3, 0)
        Set(LVar4, 14)
        SetF(LVar5, MapFlag(-1999590))
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, LVar3)
    Add(LVar1, LVar4)
    Call(PlayEffect_impl, 19, 0, LVar0, LVar1, LVar2, LVar5, 30, 0, 0, 0, 0, 0, 0, 0)
    Wait(30)
    Call(PlaySoundAtActor, ACTOR_SELF, 760)
    Call(PlaySoundAtActor, ACTOR_SELF, 532)
    Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Add(LVar2, 50)
    Call(PlayEffect_impl, 17, 1, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(PlayEffect_impl, 64, 2, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, 3, 0x240002)
    Wait(10)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar0)
    Mul(LVar0, 17)
    Div(LVar0, 100)
    Thread
        Wait(5)
        Call(PlaySoundAtActor, ACTOR_SELF, 8301)
        Call(PlaySoundAtActor, ACTOR_SELF, 532)
        Wait(30)
        Call(PlaySoundAtActor, ACTOR_SELF, 604)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(HealActor, ACTOR_SELF, LVar0, 0)
        Call(FreezeBattleState, 0)
    EndThread
    Wait(30)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_TakeTurn = {
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    IfNe(LVar0, 3)
        Call(GetActorHP, ACTOR_SELF, LVar1)
        Call(GetEnemyMaxHP, ACTOR_SELF, LVar2)
        Mul(LVar1, 100)
        Div(LVar1, LVar2)
        IfEq(LVar0, 1)
            IfLt(LVar1, 65)
                ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_Transform_Flying)
            EndIf
        Else
            IfLt(LVar1, 35)
                ExecWait(TTYD64_kmr_part_3_final_jr_troopa_EVS_Transform_Mage)
            EndIf
        EndIf
    EndIf
    Call(GetActorHP, ACTOR_SELF, LVar0)
    IfLt(LVar0, 15)
        Call(GetActorVar, ACTOR_SELF, 2, LVar0)
        IfNotFlag(LVar0, 2)
            BitwiseOrConst(LVar0, 2)
            Call(SetActorVar, ACTOR_SELF, 2, LVar0)
            Call(UseBattleCamPreset, 14)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(MoveBattleCamOver, 20)
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            Switch(LVar0)
                CaseEq(2)
                    Call(SetAnimation, ACTOR_SELF, 2, 0x23000F)
                CaseEq(3)
                    Call(SetAnimation, ACTOR_SELF, 3, 0x24000E)
                CaseDefault
                    Call(SetAnimation, ACTOR_SELF, 1, 0x210016)
            EndSwitch
            Call(ActorSpeak, 0x130060, ACTOR_SELF, 1, -1, -1)
        EndIf
    EndIf
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    Switch(LVar0)
        CaseEq(2)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 50)
                ExecWait(TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_Swoop)
            Else
                ExecWait(TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_SpikeDive)
            EndIf
        CaseEq(3)
            Call(RandInt, 100, LVar0)
            Switch(LVar0)
                CaseLt(60)
                    ExecWait(TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_MagicSpell)
                CaseLt(80)
                    ExecWait(TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_LightningBolt)
                CaseDefault
                    Call(GetActorHP, ACTOR_SELF, LVar0)
                    Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
                    IfNe(LVar0, LVar1)
                        Call(GetActorVar, ACTOR_SELF, 4, LVar2)
                        IfGt(LVar2, 0)
                            Sub(LVar2, 1)
                            Call(SetActorVar, ACTOR_SELF, 4, LVar2)
                            ExecWait(TTYD64_kmr_part_3_final_jr_troopa_EVS_Move_HealSelf)
                        Else
                            ExecWait(TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_MagicSpell)
                        EndIf
                    Else
                        ExecWait(TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_MagicSpell)
                    EndIf
            EndSwitch
        CaseDefault
            ExecWait(TTYD64_kmr_part_3_final_jr_troopa_EVS_Attack_Leap)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_jr_troopa_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfEq(LVar0, 0)
        Call(GetLastDamage, ACTOR_SELF, LVar1)
        IfNe(LVar1, 0)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
        EndIf
    EndIf
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x210011)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x210011)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x210013)
            ExecWait(b_area_kmr_part_3_jr_troopa_EVS_JrTroopa_Death)
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x210003)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x210011)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x210011)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x210009)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x210011)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x210011)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x210013)
            ExecWait(b_area_kmr_part_3_jr_troopa_EVS_JrTroopa_Death)
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
EvtScript TTYD64_kmr_part_3_para_jr_troopa_EVS_JrTroopa_Death = {
    Call(UseBattleCamPreset, 2)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfEq(LVar1, 0)
        Goto(0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 769)
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
    Call(FallToGoal, ACTOR_SELF, 10)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
    Call(HPBarToCurrent, ACTOR_SELF)
    Call(ShowHealthBar, ACTOR_SELF)
    Label(0)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 10)
        Add(LVar2, 10)
        Loop(3)
            Call(PlayEffect_impl, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(3)
        EndLoop
    EndThread
    Call(SetPartFlagBits, ACTOR_SELF, 1, 1, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x210015)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_SELF, 997)
    Call(DropStarPoints, ACTOR_SELF)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(SetBattleCamDist, 260)
    Call(SetBattleCamOffsetY, 15)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Call(PlaySoundAtActor, ACTOR_SELF, 8421)
    Call(SetAnimation, ACTOR_SELF, 2, 0x210014)
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(b_area_kmr_part_3_para_jr_troopa_DefeatedAnims))
    Wait(60)
    Call(SetActorFlagBits, ACTOR_SELF, 0x400000, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_JrTroopa_Death = {
    Call(UseBattleCamPreset, 2)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfEq(LVar1, 0)
        Goto(0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 769)
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
    Call(FallToGoal, ACTOR_SELF, 10)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
    Call(HPBarToCurrent, ACTOR_SELF)
    Call(ShowHealthBar, ACTOR_SELF)
    Label(0)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 10)
        Add(LVar2, 10)
        Loop(3)
            Call(PlayEffect_impl, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(3)
        EndLoop
    EndThread
    Call(SetPartFlagBits, ACTOR_SELF, 1, 1, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x210015)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Wait(15)
    Call(PlaySound, 997)
    Call(DropStarPoints, ACTOR_SELF)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(SetBattleCamDist, 260)
    Call(SetBattleCamOffsetY, 15)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Call(PlaySoundAtActor, ACTOR_SELF, 8421)
    Call(SetAnimation, ACTOR_SELF, 2, 0x210014)
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(b_area_kmr_part_3_spiked_para_jr_troopa_DefeatedAnims))
    Wait(60)
    Call(SetActorFlagBits, ACTOR_SELF, 0x400000, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_tutorial_spiked_goomba_EVS_Idle = {
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_3_tutorial_spiked_goomba_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_3_tutorial_spiked_goomba_DefaultAnims))
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_3_tutorial_spiked_goomba_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_3_tutorial_spiked_goomba_DefaultAnims))
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
EvtScript TTYD64_kmr_part_3_downed_goomba_tutorial_EVS_Idle = {
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_3_downed_goomba_tutorial_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_3_downed_goomba_tutorial_DefaultAnims_80233844))
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_3_downed_goomba_tutorial_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_3_downed_goomba_tutorial_DefaultAnims_80233844))
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
EvtScript TTYD64_kmr_part_3_downed_goomba_EVS_Idle = {
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_3_downed_goomba_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_3_downed_goomba_tutorial_DefaultAnims))
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
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_3_downed_goomba_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_3_downed_goomba_tutorial_DefaultAnims))
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
EvtScript TTYD64_kmr_part_3_tutorial_paragoomba_EVS_Idle = {
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
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_kmr_part_3_tutorial_paragoomba_ShuffleAnims))
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
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_kmr_part_3_tutorial_paragoomba_DefaultAnims_802338DC))
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
EvtScript TTYD64_kmr_part_3_paragoomba_EVS_Idle = {
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
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_kmr_part_3_paragoomba_ShuffleAnims))
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
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_kmr_part_3_tutorial_paragoomba_DefaultAnims))
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
EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Transform_Mage = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(ActorSpeak, 0x13005F, ACTOR_SELF, 2, 0x23000F, 0x23000F)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 120)
    ExecWait(b_area_kmr_part_3_final_jr_troopa_EVS_TransformFX)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20001, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x800000, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 0x20001, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 0x800000, 1)
    Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 20)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FallToGoal, ACTOR_SELF, 10)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 3, 3)
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kmr_part_3_final_jr_troopa_MageStatusTable))
    Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_para_jr_troopa_EVS_JrTroopa_FlyHome = {
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x250005)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar4, LVar1)
    MulF(LVar4, Float(0.2998046875))
    Call(FlyToGoal, ACTOR_SELF, 0, LVar4, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_JrTroopa_FlyHome = {
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x230007)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar4, LVar1)
    MulF(LVar4, Float(0.2998046875))
    Call(FlyToGoal, ACTOR_SELF, 0, LVar4, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_jr_troopa_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_3_jr_troopa_EVS_TakeTurn))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kmr_part_3_jr_troopa_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_kmr_part_3_jr_troopa_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 2)
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_final_jr_troopa_EVS_Init = {
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 1)
    Call(SetActorVar, ACTOR_SELF, 4, 5)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_3_final_jr_troopa_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kmr_part_3_final_jr_troopa_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kmr_part_3_final_jr_troopa_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kmr_part_3_final_jr_troopa_EVS_HandlePhase))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_mage_jr_troopa_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_3_mage_jr_troopa_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kmr_part_3_mage_jr_troopa_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kmr_part_3_mage_jr_troopa_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kmr_part_3_mage_jr_troopa_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Return
    End
};
// clang-format on

Battle TTYD64_kmr_part_3_Formations[] = {
    { .name = "\310\262\257\352\334\374\010\354\257\301\343\374\011",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_kmr_part_3_Formation_00,
      .stage = &b_area_kmr_part_3_kmr_03,
      .onBattleStart = NULL },
    { .name = "\321\277\257\352\334\374\010\354\257\301\343\374\011",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kmr_part_3_Formation_01,
      .stage = &b_area_kmr_part_3_kmr_03,
      .onBattleStart = NULL },
    { .name = "\263\357\303\321\021",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_kmr_part_3_Formation_02,
      .stage = &b_area_kmr_part_3_kmr_05b,
      .onBattleStart = NULL },
    { .name = "\263\357\303\321\022",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_kmr_part_3_Formation_03,
      .stage = &b_area_kmr_part_3_nok_01,
      .onBattleStart = NULL },
    { .name = "\263\357\303\321\024",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_kmr_part_3_Formation_04,
      .stage = &b_area_kmr_part_3_mim_01,
      .onBattleStart = NULL },
    { .name = "\263\357\303\321\025",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_kmr_part_3_Formation_05,
      .stage = &b_area_kmr_part_3_mac_01,
      .onBattleStart = NULL },
    { .name = "\263\357\303\321\026",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_kmr_part_3_Formation_06,
      .stage = &b_area_kmr_part_3_sam_01,
      .onBattleStart = NULL },
    { .name = "\263\357\303\321\027",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_kmr_part_3_Formation_07,
      .stage = &b_area_kmr_part_3_kpa_13,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kmr_part_3_spiked_para_jr_troopa_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_kmr_part_3_tutorial_paragoomba_ActorParts[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_3_downed_goomba_tutorial_DefaultAnims_80233844,
        .defenseTable = b_area_kmr_part_3_tutorial_paragoomba_DownedDefense,
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
        .idleAnimations = TTYD64_kmr_part_3_tutorial_paragoomba_DefaultAnims_802338DC,
        .defenseTable = b_area_kmr_part_3_tutorial_paragoomba_FlyingDefense,
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
        .idleAnimations = b_area_kmr_part_3_tutorial_paragoomba_LeftWingAnims,
        .defenseTable = b_area_kmr_part_3_tutorial_paragoomba_DownedDefense,
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
        .idleAnimations = b_area_kmr_part_3_tutorial_paragoomba_RightWingAnims,
        .defenseTable = b_area_kmr_part_3_tutorial_paragoomba_DownedDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_kmr_part_3_tutorial_paragoomba_ActorParts_80232EFC[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_3_downed_goomba_tutorial_DefaultAnims,
        .defenseTable = b_area_kmr_part_3_tutorial_paragoomba_DownedDefense,
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
        .idleAnimations = TTYD64_kmr_part_3_tutorial_paragoomba_DefaultAnims,
        .defenseTable = b_area_kmr_part_3_tutorial_paragoomba_FlyingDefense,
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
        .idleAnimations = b_area_kmr_part_3_tutorial_paragoomba_LeftWingAnims,
        .defenseTable = b_area_kmr_part_3_tutorial_paragoomba_DownedDefense,
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
        .idleAnimations = b_area_kmr_part_3_tutorial_paragoomba_RightWingAnims,
        .defenseTable = b_area_kmr_part_3_tutorial_paragoomba_DownedDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_kmr_part_3_egg_jr_troopa_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_3_egg_jr_troopa_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kmr_part_3_egg_jr_troopa_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kmr_part_3_egg_jr_troopa_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kmr_part_3_egg_jr_troopa_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_para_jr_troopa_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_3_para_jr_troopa_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kmr_part_3_para_jr_troopa_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kmr_part_3_para_jr_troopa_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kmr_part_3_para_jr_troopa_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_kmr_part_3_final_jr_troopa_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 26 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_3_final_jr_troopa_BaseAnims,
        .defenseTable = b_area_kmr_part_3_final_jr_troopa_BaseDefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -2, -6 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -5, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_3_final_jr_troopa_FlyingAnims,
        .defenseTable = b_area_kmr_part_3_final_jr_troopa_FlyingDefenseTable,
        .eventFlags = 0x10,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -11 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 28 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_3_final_jr_troopa_MageAnims,
        .defenseTable = b_area_kmr_part_3_final_jr_troopa_MageDefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -2, -7 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_kmr_part_3_tutorial_paragoomba_EVS_Init_Tutorial = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_3_tutorial_paragoomba_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_kmr_part_3_tutorial_paragoomba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kmr_part_3_tutorial_paragoomba_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kmr_part_3_tutorial_paragoomba_EVS_HandlePhase))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_tutorial_paragoomba_EVS_Init_Tutorial_802334C4 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_3_tutorial_spiked_goomba_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_kmr_part_3_tutorial_spiked_goomba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kmr_part_3_tutorial_spiked_goomba_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kmr_part_3_tutorial_spiked_goomba_EVS_HandlePhase))
    Return
    End
};
// clang-format on

s32 TTYD64_kmr_part_3_downed_goomba_tutorial_ShuffleAnims[] = {
    1,  0x260003, 7, 0x260000, 6, 0x260008, 9, 0x260001, 8, 0x260000,
    11, 0x260003, 5, 0x260000, 4, 0x260007, 3, 0x260007, 0,
};

s32 TTYD64_kmr_part_3_tutorial_paragoomba_ShuffleAnims[] = {
    1,  0x280004, 7, 0x280000, 6, 0x28000B, 9, 0x280001, 8, 0x280000,
    11, 0x280004, 5, 0x280000, 4, 0x28000C, 3, 0x28000C, 0,
};

s32 TTYD64_kmr_part_3_downed_goomba_ShuffleAnims[] = {
    1,  0x260003, 7, 0x260000, 6, 0x260008, 9, 0x260001, 8, 0x260000,
    11, 0x260003, 5, 0x260000, 4, 0x260007, 3, 0x260007, 0,
};

s32 TTYD64_kmr_part_3_tutorial_spiked_goomba_ShuffleAnims[] = {
    1,  0x270003, 7, 0x270000, 6, 0x27000A, 9, 0x270001, 8, 0x270000,
    11, 0x270003, 5, 0x270000, 4, 0x270009, 3, 0x270009, 0,
};

// clang-format off
EvtScript TTYD64_kmr_part_3_paragoomba_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_3_paragoomba_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_kmr_part_3_paragoomba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kmr_part_3_paragoomba_EVS_HandleEvent))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_3_downed_goomba_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_3_downed_goomba_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_kmr_part_3_downed_goomba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kmr_part_3_downed_goomba_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_kmr_part_3_downed_goomba_tutorial_DefaultAnims[] = {
    1,  0x260001, 7, 0x260000, 6, 0x260008, 9, 0x260001, 8, 0x260000,
    11, 0x260001, 5, 0x260000, 4, 0x260007, 3, 0x260007, 0,
};

s32 TTYD64_kmr_part_3_downed_goomba_tutorial_DefaultAnims_80233844[] = {
    1,  0x260001, 7, 0x260000, 6, 0x260008, 9, 0x260001, 8, 0x260000,
    11, 0x260001, 5, 0x260000, 4, 0x260007, 3, 0x260007, 0,
};

s32 TTYD64_kmr_part_3_tutorial_paragoomba_DefaultAnims[] = {
    1,  0x280001, 7, 0x280000, 6, 0x28000B, 9, 0x280001, 8, 0x280000,
    11, 0x280001, 5, 0x280000, 4, 0x28000C, 3, 0x28000C, 0,
};

s32 TTYD64_kmr_part_3_tutorial_paragoomba_DefaultAnims_802338DC[] = {
    1,  0x280001, 7, 0x280000, 6, 0x28000B, 9, 0x280001, 8, 0x280000,
    11, 0x280001, 5, 0x280000, 4, 0x28000C, 3, 0x28000C, 0,
};

s32 TTYD64_kmr_part_3_paragoomba_ShuffleAnims[] = {
    1,  0x280004, 7, 0x280000, 6, 0x28000B, 9, 0x280001, 8, 0x280000,
    11, 0x280004, 5, 0x280000, 4, 0x28000C, 3, 0x28000C, 0,
};

s32 TTYD64_kmr_part_3_tutorial_spiked_goomba_DefaultAnims[] = {
    1,  0x270001, 7, 0x270000, 6, 0x27000A, 9, 0x270001, 8, 0x270000,
    11, 0x270001, 5, 0x270000, 4, 0x270009, 3, 0x270009, 0,
};

// clang-format off
EvtScript TTYD64_kmr_part_3_downed_goomba_tutorial_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_3_downed_goomba_tutorial_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_kmr_part_3_downed_goomba_tutorial_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kmr_part_3_downed_goomba_tutorial_EVS_HandleEvent))
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_kmr_part_3_para_jr_troopa_ActorParts[] = {
    {
        .flags = 0x800001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_3_para_jr_troopa_FlyingAnims,
        .defenseTable = b_area_kmr_part_3_para_jr_troopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -6 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 30 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_3_para_jr_troopa_BaseAnims,
        .defenseTable = b_area_kmr_part_3_para_jr_troopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_kmr_part_3_mage_jr_troopa_ActorParts[] = {
    {
        .flags = 0x800001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 28 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_3_mage_jr_troopa_MageAnims,
        .defenseTable = b_area_kmr_part_3_mage_jr_troopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -2, -7 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 30 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_3_mage_jr_troopa_BaseAnims,
        .defenseTable = b_area_kmr_part_3_mage_jr_troopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_kmr_part_3_spiked_para_jr_troopa_ActorParts[] = {
    {
        .flags = 0x800001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -5, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_3_spiked_para_jr_troopa_DefaultAnims,
        .defenseTable = b_area_kmr_part_3_spiked_para_jr_troopa_DefenseTable,
        .eventFlags = 0x10,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -11 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 30 },
        .opacity = 255,
        .idleAnimations = b_area_kmr_part_3_spiked_para_jr_troopa_WindedAnims,
        .defenseTable = b_area_kmr_part_3_spiked_para_jr_troopa_DefenseTable,
        .eventFlags = 0x10,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_kmr_part_3_mage_jr_troopa_MageAnims[] = {
    1, 0x240002, 6, 0x24000C, 7, 0x240000, 9, 0x240000, 8, 0x240000, 11, 0x240000, 5, 0x240000, 4, 0x24000D, 0,
};

s32 TTYD64_kmr_part_3_mage_jr_troopa_BaseAnims[] = {
    1, 0x210003, 6, 0x21001C, 7, 0x210000, 9, 0x210000, 8, 0x210000, 11, 0x210000, 5, 0x210000, 4, 0x21001D, 0,
};

s32 TTYD64_kmr_part_3_para_jr_troopa_BaseAnims[] = {
    1, 0x210003, 6, 0x21001C, 7, 0x210000, 9, 0x210000, 8, 0x210000, 11, 0x210000, 5, 0x210000, 4, 0x21001D, 0,
};

s32 TTYD64_kmr_part_3_spiked_para_jr_troopa_DefaultAnims[] = {
    1, 0x230003, 6, 0x23000D, 7, 0x230000, 9, 0x230000, 8, 0x230000, 11, 0x230000, 5, 0x230000, 4, 0x23000E, 0,
};

s32 TTYD64_kmr_part_3_para_jr_troopa_FlyingAnims[] = {
    1, 0x250002, 6, 0x25000A, 7, 0x250000, 9, 0x250000, 8, 0x250000, 11, 0x250000, 5, 0x250000, 4, 0x25000B, 0,
};

s32 TTYD64_kmr_part_3_jr_troopa_DefaultAnims[] = {
    1, 0x210003, 7, 0x210000, 6, 0x210000, 9, 0x210000, 8, 0x210000, 11, 0x210000, 5, 0x210000, 0,
};

s32 TTYD64_kmr_part_3_egg_jr_troopa_DefaultAnims[] = {
    1, 0x210003, 6, 0x21001C, 7, 0x210000, 9, 0x210000, 8, 0x210000, 11, 0x210000, 5, 0x210000, 0,
};

FormationRow TTYD64_kmr_part_3_Formation_01[] = {
    { .actor = &TTYD64_kmr_part_3_tutorial_paragoomba,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGOOMBA },
    { .actor = &TTYD64_kmr_part_3_tutorial_paragoomba_80234300,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGOOMBA },
};

s32 TTYD64_kmr_part_3_final_jr_troopa_MageAnims[] = {
    1, 0x240002, 6, 0x24000C, 7, 0x240000, 8, 0x240000, 5, 0x240000, 4, 0x24000D, 0,
};

s32 TTYD64_kmr_part_3_final_jr_troopa_FlyingAnims[] = {
    1, 0x230003, 6, 0x23000D, 7, 0x230000, 8, 0x230000, 5, 0x230000, 4, 0x23000E, 0,
};

s32 TTYD64_kmr_part_3_final_jr_troopa_BaseAnims[] = {
    1, 0x210003, 6, 0x21001C, 7, 0x210000, 8, 0x210000, 5, 0x210000, 4, 0x21001D, 0,
};

ActorBlueprint TTYD64_kmr_part_3_egg_jr_troopa = {
    .flags = 0x0,
    .maxHP = 15,
    .type = 0x89,
    .level = 44,
    .partCount = 1,
    .partsData = TTYD64_kmr_part_3_egg_jr_troopa_ActorParts,
    .initScript = &TTYD64_kmr_part_3_egg_jr_troopa_EVS_Init,
    .statusTable = b_area_kmr_part_3_egg_jr_troopa_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 32, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 30 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_kmr_part_3_para_jr_troopa = {
    .flags = 0x200,
    .maxHP = 40,
    .type = 0x8A,
    .level = 52,
    .partCount = 2,
    .partsData = TTYD64_kmr_part_3_para_jr_troopa_ActorParts,
    .initScript = &TTYD64_kmr_part_3_para_jr_troopa_EVS_Init,
    .statusTable = b_area_kmr_part_3_para_jr_troopa_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 60, 35 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -25, 35 },
    .statusTextOffset = { 10, 25 },
};

ActorBlueprint TTYD64_kmr_part_3_jr_troopa = {
    .flags = 0x0,
    .maxHP = 5,
    .type = 0x88,
    .level = 41,
    .partCount = 1,
    .partsData = TTYD64_kmr_part_3_jr_troopa_ActorParts,
    .initScript = &TTYD64_kmr_part_3_jr_troopa_EVS_Init,
    .statusTable = b_area_kmr_part_3_jr_troopa_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 24, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 30 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_kmr_part_3_final_jr_troopa = {
    .flags = 0x0,
    .maxHP = 60,
    .type = 0x8D,
    .level = 74,
    .partCount = 3,
    .partsData = TTYD64_kmr_part_3_final_jr_troopa_ActorParts,
    .initScript = &TTYD64_kmr_part_3_final_jr_troopa_EVS_Init,
    .statusTable = b_area_kmr_part_3_final_jr_troopa_BaseStatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 70,
    .coinReward = 0,
    .size = { 24, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -20, 35 },
    .statusTextOffset = { 10, 25 },
};

ActorBlueprint TTYD64_kmr_part_3_spiked_para_jr_troopa = {
    .flags = 0x200,
    .maxHP = 40,
    .type = 0x8B,
    .level = 59,
    .partCount = 2,
    .partsData = TTYD64_kmr_part_3_spiked_para_jr_troopa_ActorParts,
    .initScript = &TTYD64_kmr_part_3_spiked_para_jr_troopa_EVS_Init,
    .statusTable = b_area_kmr_part_3_spiked_para_jr_troopa_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 60, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -25, 35 },
    .statusTextOffset = { 10, 25 },
};

ActorBlueprint TTYD64_kmr_part_3_mage_jr_troopa = {
    .flags = 0x0,
    .maxHP = 50,
    .type = 0x8C,
    .level = 65,
    .partCount = 2,
    .partsData = TTYD64_kmr_part_3_mage_jr_troopa_ActorParts,
    .initScript = &TTYD64_kmr_part_3_mage_jr_troopa_EVS_Init,
    .statusTable = b_area_kmr_part_3_mage_jr_troopa_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 24, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -20, 35 },
    .statusTextOffset = { 10, 25 },
};

ActorBlueprint TTYD64_kmr_part_3_tutorial_paragoomba = {
    .flags = 0x200,
    .maxHP = 2,
    .type = 0x08,
    .level = 6,
    .partCount = 4,
    .partsData = TTYD64_kmr_part_3_tutorial_paragoomba_ActorParts_80232EFC,
    .initScript = &TTYD64_kmr_part_3_paragoomba_EVS_Init,
    .statusTable = b_area_kmr_part_3_tutorial_paragoomba_FlyingStatusTable,
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

ActorBlueprint TTYD64_kmr_part_3_tutorial_paragoomba_80234300 = {
    .flags = 0x200,
    .maxHP = 2,
    .type = 0x08,
    .level = 6,
    .partCount = 4,
    .partsData = TTYD64_kmr_part_3_tutorial_paragoomba_ActorParts,
    .initScript = &TTYD64_kmr_part_3_tutorial_paragoomba_EVS_Init_Tutorial,
    .statusTable = b_area_kmr_part_3_tutorial_paragoomba_FlyingStatusTable,
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

ActorBlueprint TTYD64_kmr_part_3_tutorial_spiked_goomba = {
    .flags = 0x0,
    .maxHP = 2,
    .type = 0x09,
    .level = 6,
    .partCount = 1,
    .partsData = TTYD64_kmr_part_3_tutorial_spiked_goomba_ActorParts,
    .initScript = &TTYD64_kmr_part_3_tutorial_paragoomba_EVS_Init_Tutorial_802334C4,
    .statusTable = b_area_kmr_part_3_tutorial_spiked_goomba_StatusTable,
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

ActorPartBlueprint TTYD64_kmr_part_3_tutorial_spiked_goomba_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_3_tutorial_spiked_goomba_DefaultAnims,
        .defenseTable = b_area_kmr_part_3_tutorial_paragoomba_DownedDefense,
        .eventFlags = 0x10,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_kmr_part_3_egg_jr_troopa_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -6, 18 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_3_egg_jr_troopa_DefaultAnims,
        .defenseTable = b_area_kmr_part_3_egg_jr_troopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 5, -4 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_kmr_part_3_jr_troopa_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 30 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_3_jr_troopa_DefaultAnims,
        .defenseTable = b_area_kmr_part_3_jr_troopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_kmr_part_3_Formation_00[] = {
    { .actor = &TTYD64_kmr_part_3_tutorial_spiked_goomba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
};

FormationRow TTYD64_kmr_part_3_Formation_04[] = {
    { .actor = &TTYD64_kmr_part_3_para_jr_troopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kmr_part_3_Formation_05[] = {
    { .actor = &TTYD64_kmr_part_3_spiked_para_jr_troopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kmr_part_3_Formation_02[] = {
    { .actor = &TTYD64_kmr_part_3_jr_troopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kmr_part_3_Formation_03[] = {
    { .actor = &TTYD64_kmr_part_3_egg_jr_troopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kmr_part_3_Formation_06[] = {
    { .actor = &TTYD64_kmr_part_3_mage_jr_troopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kmr_part_3_Formation_07[] = {
    { .actor = &TTYD64_kmr_part_3_final_jr_troopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

void TTYD64_InstallBattles_kmr_part_3(void) {
    Mod_SetBattleList("TTYD64", 2, TTYD64_kmr_part_3_Formations);
}
