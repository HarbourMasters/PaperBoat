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
#include "battles_new.h"

API_CALLABLE(TTYD64_TexturePan_Complex);
API_CALLABLE(TTYD64_TexturePan_Simple);
API_CALLABLE(b_area_flo_ruff_puff_CosInterpMinMax);
API_CALLABLE(battle_item_thunder_bolt_SpawnLightningFX);
extern s32 b_area_flo_lakitu_DefenseTable[];
extern s32 b_area_kmr_part_1_goomba_DefenseTable[];
extern s32 b_area_kmr_part_1_goomba_StatusTable[];
extern EvtScript b_area_kmr_part_1_kmr_02_EVS_PostBattle;
extern s32 b_area_kmr_part_1_paragoomba_FlyingStatusTable[];
extern s32 b_area_kmr_part_1_spiked_goomba_StatusTable[];
extern s32 b_area_kmr_part_3_egg_jr_troopa_DefenseTable[];
extern EvtScript b_area_kmr_part_3_kpa_13_EVS_PreBattle;
extern s32 b_area_kzn_lava_bubble_StatusTable[];
extern s32 b_area_mim_piranha_plant_DefenseTable[];
extern EvtScript b_area_mim_piranha_plant_EVS_Idle;
API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(ClearStatusEffects);
API_CALLABLE(CreateHomeTargetList);
API_CALLABLE(ElectrifyActor);
API_CALLABLE(EnableActorBlur);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyPartTo);
API_CALLABLE(FlyToGoal);
API_CALLABLE(FreezeBattleState);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetAnimation);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetHomePos);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPlayerHP);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToCurrent);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HideHealthBar);
API_CALLABLE(IdleRunToGoal);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(JumpToGoal);
API_CALLABLE(JumpWithBounce);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlayParalyzeHitFX);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlaySoundAtPart);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActor);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorIdleSpeed);
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
API_CALLABLE(SetAnimationRate);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetIdleGoal);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartRotation);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTargetActor);
API_CALLABLE(SetTexPanner);
API_CALLABLE(ShakeCam);
API_CALLABLE(StartRumble);
API_CALLABLE(StopSound);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(WaitForBuffDone);
API_CALLABLE(YieldTurn);
extern ActorPartBlueprint TTYD64_arn_hyper_cleft_ActorParts[];
extern EvtScript TTYD64_arn_hyper_cleft_EVS_Attack_Tackle;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_FlipOver;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_HandleEvent;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_Init;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_Move_Charge;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_TakeTurn;
extern EvtScript TTYD64_arn_hyper_cleft_EVS_TryGettingUp;
extern s32 TTYD64_arn_hyper_cleft_HyperAnims[];
extern s32 TTYD64_arn_hyper_cleft_StatusTable[];
extern s32 TTYD64_arn_hyper_cleft_ToppledAnims[];
extern s32 TTYD64_arn_hyper_cleft_UprightAnims[];
extern ActorBlueprint TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee;
extern s32 TTYD64_imp_18_AmazyDayzee_IdleAnimations_80221544_18[];
extern ActorPartBlueprint TTYD64_imp_18_AmazyDayzee_PartsTable_802214F8_18[];
extern EvtScript TTYD64_imp_18_AmazyDayzee_Script_Amazy_Sing_18;
extern EvtScript TTYD64_imp_18_AmazyDayzee_Script_Init_80221590_18;
extern EvtScript TTYD64_imp_18_AmazyDayzee_Script_TakeTurn_80222500_18;
extern ActorBlueprint TTYD64_imp_18_RuffPuff_18_RuffPuff;
extern s32 TTYD64_imp_18_RuffPuff_IdleAnimations_802225A0_18[];
extern ActorPartBlueprint TTYD64_imp_18_RuffPuff_PartsTable_802226A4_18[];
extern EvtScript TTYD64_imp_18_RuffPuff_Script_Idle_8022273C_18;
extern EvtScript TTYD64_imp_18_RuffPuff_Script_Init_802226F0_18;
extern EvtScript TTYD64_imp_18_RuffPuff_Script_RuffPuff_Static;
extern EvtScript TTYD64_imp_18_RuffPuff_Script_RuffPuff_TackleAttack;
extern EvtScript TTYD64_imp_18_RuffPuff_Script_RuffPuff_ThunderAttack;
extern EvtScript TTYD64_imp_18_RuffPuff_Script_TakeTurn_80222DE8_18;
extern s32 TTYD64_imp_18_RuffPuff_StatusTable_802225F8_18[];
extern s32 TTYD64_kmr_part_1_downed_goomba_DefaultAnims[];
extern EvtScript TTYD64_kmr_part_1_downed_goomba_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_1_downed_goomba_EVS_Idle;
extern EvtScript TTYD64_kmr_part_1_downed_goomba_EVS_Init;
extern EvtScript TTYD64_kmr_part_1_downed_goomba_EVS_TakeTurn;
extern s32 TTYD64_kmr_part_1_downed_goomba_ShuffleAnims[];
extern ActorPartBlueprint TTYD64_kmr_part_1_goomba_ActorParts[];
extern s32 TTYD64_kmr_part_1_goomba_DefaultAnims[];
extern EvtScript TTYD64_kmr_part_1_goomba_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_1_goomba_EVS_Idle;
extern EvtScript TTYD64_kmr_part_1_goomba_EVS_Init;
extern EvtScript TTYD64_kmr_part_1_goomba_EVS_TakeTurn;
extern s32 TTYD64_kmr_part_1_goomba_ShuffleAnims[];
extern ActorPartBlueprint TTYD64_kmr_part_1_paragoomba_ActorParts[];
extern s32 TTYD64_kmr_part_1_paragoomba_DefaultAnims[];
extern EvtScript TTYD64_kmr_part_1_paragoomba_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_1_paragoomba_EVS_Idle;
extern EvtScript TTYD64_kmr_part_1_paragoomba_EVS_KnockDown;
extern EvtScript TTYD64_kmr_part_1_paragoomba_EVS_TakeTurn;
extern s32 TTYD64_kmr_part_1_paragoomba_ShuffleAnims[];
extern ActorPartBlueprint TTYD64_kmr_part_1_spiked_goomba_ActorParts[];
extern s32 TTYD64_kmr_part_1_spiked_goomba_DefaultAnims[];
extern EvtScript TTYD64_kmr_part_1_spiked_goomba_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_1_spiked_goomba_EVS_Idle;
extern EvtScript TTYD64_kmr_part_1_spiked_goomba_EVS_Init;
extern EvtScript TTYD64_kmr_part_1_spiked_goomba_EVS_Init_8021FCA4;
extern EvtScript TTYD64_kmr_part_1_spiked_goomba_EVS_TakeTurn;
extern s32 TTYD64_kmr_part_1_spiked_goomba_ShuffleAnims[];
extern s32 TTYD64_kzn_Anims_8022ACD8[];
extern EvtScript TTYD64_kzn_EVS_8021FDC8;
extern EvtScript TTYD64_kzn_EVS_80224BAC;
extern ActorPartBlueprint TTYD64_kzn_lava_bubble_ActorParts[];
extern s32 TTYD64_kzn_lava_bubble_DefaultAnims[];
extern EvtScript TTYD64_kzn_lava_bubble_EVS_Attack_ShootPartner;
extern EvtScript TTYD64_kzn_lava_bubble_EVS_Init;
extern EvtScript TTYD64_kzn_lava_bubble_EVS_ShootFire;
extern EvtScript TTYD64_kzn_lava_bubble_EVS_ShootFire_Impl;
extern EvtScript TTYD64_kzn_lava_bubble_EVS_TakeTurn;
extern EvtScript TTYD64_kzn_putrid_piranha_EVS_Attack_Bite_80220414;
extern EvtScript TTYD64_imp_BulkyBobomb_Script_HandleEvent_BulkyBobomb;
extern EvtScript TTYD64_imp_Pider_Script_TakeTurn_Pider;
extern EvtScript TTYD64_imp_DarkPuff_Script_DarkPuff_TackleAttack;
extern EvtScript TTYD64_imp_BulkyBobomb_Script_TakeTurn_BulkyBobomb;
extern EvtScript TTYD64_imp_PalePiranha_Script_TakeTurn_8021DCD4_0D;
extern EvtScript TTYD64_imp_PalePiranha_Script_HandleEvent_8021D60C_0D;
extern EvtScript TTYD64_imp_DarkPuff_Script_DarkPuff_ThunderAttack;
extern EvtScript TTYD64_imp_Pider_Script_HandleEvent_Pider;
extern EvtScript TTYD64_imp_Gus_Script_HandleEvent_Gus;
extern EvtScript TTYD64_imp_DarkPuff_Script_HandleEvent_80222898_3B;
extern EvtScript TTYD64_imp_Gus_Script_Attack_SpearCharge;
extern EvtScript TTYD64_imp_Gus_Script_Attack_SpearThrow;
extern EvtScript TTYD64_imp_BulkyBobomb_Script_Attack_Explosion_HurtAllTargets;
extern EvtScript TTYD64_imp_Pider_Script_NextTurn_Pider;
extern EvtScript TTYD64_imp_BulkyBobomb_Script_Idle_BulkyBobomb;
extern EvtScript TTYD64_tyd_part_1_Script_SetupTexturePan;
extern EvtScript TTYD64_imp_DarkPuff_Script_DarkPuff_Static;
extern EvtScript TTYD64_imp_BulkyBobomb_Script_ExplosionFX;
extern EvtScript TTYD64_imp_Pider_Script_Init_Pider;
extern EvtScript TTYD64_imp_PalePiranha_Script_8021D4F4_0D;
extern EvtScript TTYD64_imp_DarkPuff_Script_Idle_8022273C_3B;
extern Battle TTYD64_tyd_part_1_FormationTable[];
extern s32 TTYD64_imp_PalePiranha_StatusTable_8021D3A0_0D[];
extern s32 TTYD64_imp_DarkPuff_StatusTable_802225F8_3B[];
extern EvtScript TTYD64_imp_DarkPuff_Script_TakeTurn_80222DE8_3B;
extern EvtScript TTYD64_tyd_part_1_Script_TexturePan_Update;
extern EvtScript TTYD64_tyd_part_1_Script_BeforeBattle_tyd02;
extern s32 TTYD64_imp_Pider_StatusTable_Pider[];
extern s32 TTYD64_imp_BulkyBobomb_StatusTable_BulkyBobomb[];
extern s32 TTYD64_imp_Gus_StatusTable_Gus[];
extern EvtScript TTYD64_imp_DarkPuff_Script_80222820_3B;
extern FormationRow TTYD64_tyd_part_1_Formation_tyd_01_1[];
extern FormationRow TTYD64_tyd_part_1_Formation_tyd_05_1[];
extern FormationRow TTYD64_tyd_part_1_Formation_tyd_05_2[];
extern EvtScript TTYD64_imp_Gus_Script_TakeTurn_Gus;
extern FormationRow TTYD64_tyd_part_1_Formation_tyd_02_1[];
extern FormationRow TTYD64_tyd_part_1_Formation_tyd_04[];
extern s32 TTYD64_imp_BulkyBobomb_IdleAnimations_BulkyBobomb_5[];
extern s32 TTYD64_imp_BulkyBobomb_IdleAnimations_BulkyBobomb_4[];
extern s32 TTYD64_imp_BulkyBobomb_IdleAnimations_BulkyBobomb_3[];
extern s32 TTYD64_imp_BulkyBobomb_IdleAnimations_BulkyBobomb_2[];
extern s32 TTYD64_imp_BulkyBobomb_IdleAnimations_BulkyBobomb_1[];
extern s32 TTYD64_imp_Gus_IdleAnimations_Gus[];
extern s32 TTYD64_imp_Pider_IdleAnimations_Pider[];
extern s32 TTYD64_imp_PalePiranha_IdleAnimations_8021D330_0D[];
extern EvtScript TTYD64_imp_BulkyBobomb_Script_Init_BulkyBobomb;
extern EvtScript TTYD64_imp_DarkPuff_Script_Init_802226F0_3B;
extern EvtScript TTYD64_imp_PalePiranha_Script_Init_8021D498_0D;
extern ActorPartBlueprint TTYD64_imp_Pider_PartsTable_Pider[];
extern ActorPartBlueprint TTYD64_imp_Gus_PartsTable_Gus[];
extern s32 TTYD64_imp_DarkPuff_IdleAnimations_802225A0_3B[];
extern FormationRow TTYD64_tyd_part_1_Formation_tyd_02_2[];
extern FormationRow TTYD64_tyd_part_1_Formation_tyd_01_2[];
extern FormationRow TTYD64_tyd_part_1_Formation_tyd_01_3[];
extern FormationRow TTYD64_tyd_part_1_Formation_tyd_06[];
extern StageListRow TTYD64_tyd_part_1_StageTable[];
extern EvtScript TTYD64_imp_Gus_Script_Init_Gus;
extern s32 TTYD64_imp_Gus_IntTable_SpearRotation[];
extern Stage TTYD64_tyd_part_1_Stage_GreatTree;
extern ActorBlueprint TTYD64_imp_Pider_3B_Pider;
extern Stage TTYD64_tyd_part_1_Stage_PiratesGrotto;
extern ActorBlueprint TTYD64_tyd_part_1_imp_0E_HyperCleft_0E_HyperCleft;
extern Stage TTYD64_tyd_part_1_Stage_RiversideStation;
extern ActorBlueprint TTYD64_imp_BulkyBobomb_3B_BulkyBobomb;
extern ActorBlueprint TTYD64_tyd_part_1_imp_16_LavaBubble_16_LavaBubble;
extern ActorBlueprint TTYD64_imp_PalePiranha_PalePiranha;
extern Stage TTYD64_tyd_part_1_Stage_Rogueport;
extern ActorBlueprint TTYD64_imp_Gus_3B_Gus;
extern ActorBlueprint TTYD64_imp_DarkPuff_DarkPuff;
extern ActorBlueprint TTYD64_tyd_part_1_imp_00_Goomba_00_Goomba;
extern Stage TTYD64_tyd_part_1_Stage_TwilightTrail;
extern ActorBlueprint TTYD64_tyd_part_1_imp_00_SpikedGoomba_00_SpikedGoomba;
extern ActorBlueprint TTYD64_tyd_part_1_imp_00_Paragoomba_00_Paragoomba;
extern Stage TTYD64_tyd_part_1_Stage_PetalMeadows;
extern ActorPartBlueprint TTYD64_imp_PalePiranha_PartsTable_8021D44C_0D[];
extern ActorPartBlueprint TTYD64_imp_DarkPuff_PartsTable_802226A4_3B[];
extern ActorPartBlueprint TTYD64_imp_BulkyBobomb_PartsTable_BulkyBobomb[];
extern FormationRow TTYD64_tyd_part_1_Formation_tyd_00[];
extern s32 TTYD64_imp_Pider_IdleAnimations_Rock[];
extern s32 TTYD64_imp_Gus_IdleAnimations_Spear[];

// clang-format off
EvtScript TTYD64_imp_BulkyBobomb_Script_HandleEvent_BulkyBobomb = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            SetConst(LVar0, 1)
            Switch(LVarA)
                CaseEq(0)
                    SetConst(LVar1, 0xEC000D)
                CaseEq(1)
                    SetConst(LVar1, 0xEC000E)
                CaseEq(2)
                    SetConst(LVar1, 0xEC000F)
                CaseEq(3)
                    SetConst(LVar1, 0xEC0010)
                CaseEq(4)
                    SetConst(LVar1, 0xEC0011)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            Call(GetLastElement, LVarE)
            IfFlag(LVarE, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xEC0014)
                SetConst(LVar2, 0xEC0015)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                Wait(10)
                ExecWait(TTYD64_imp_BulkyBobomb_Script_ExplosionFX)
                ExecWait(TTYD64_imp_BulkyBobomb_Script_Attack_Explosion_HurtAllTargets)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xEC000C)
                Set(LVar2, -0x3039)
                ExecWait(Ref(EVS_Enemy_Death))
                Return
            Else
                SetConst(LVar0, 1)
                Switch(LVarA)
                    CaseEq(0)
                        SetConst(LVar1, 0xEC000D)
                    CaseEq(1)
                        SetConst(LVar1, 0xEC000E)
                    CaseEq(2)
                        SetConst(LVar1, 0xEC000F)
                    CaseEq(3)
                        SetConst(LVar1, 0xEC0010)
                    CaseEq(4)
                        SetConst(LVar1, 0xEC0011)
                EndSwitch
                ExecWait(Ref(EVS_Enemy_Hit))
            EndIf
        EndCaseGroup
        CaseOrEq(14)
        CaseOrEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEC0014)
            SetConst(LVar2, 0xEC0015)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Wait(10)
            ExecWait(TTYD64_imp_BulkyBobomb_Script_ExplosionFX)
            ExecWait(TTYD64_imp_BulkyBobomb_Script_Attack_Explosion_HurtAllTargets)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEC000C)
            Set(LVar2, -0x3039)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        EndCaseGroup
        CaseEq(11)
            SetConst(LVar0, 1)
            Switch(LVarA)
                CaseEq(0)
                    SetConst(LVar1, 0xEC000D)
                CaseEq(1)
                    SetConst(LVar1, 0xEC000E)
                CaseEq(2)
                    SetConst(LVar1, 0xEC000F)
                CaseEq(3)
                    SetConst(LVar1, 0xEC0010)
                CaseEq(4)
                    SetConst(LVar1, 0xEC0011)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            Switch(LVarA)
                CaseEq(0)
                    SetConst(LVar1, 0xEC000D)
                CaseEq(1)
                    SetConst(LVar1, 0xEC000E)
                CaseEq(2)
                    SetConst(LVar1, 0xEC000F)
                CaseEq(3)
                    SetConst(LVar1, 0xEC0010)
                CaseEq(4)
                    SetConst(LVar1, 0xEC0011)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            Switch(LVarA)
                CaseEq(0)
                    SetConst(LVar1, 0xEC000D)
                CaseEq(1)
                    SetConst(LVar1, 0xEC000E)
                CaseEq(2)
                    SetConst(LVar1, 0xEC000F)
                CaseEq(3)
                    SetConst(LVar1, 0xEC0010)
                CaseEq(4)
                    SetConst(LVar1, 0xEC0011)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            Switch(LVarA)
                CaseEq(0)
                    SetConst(LVar1, 0xEC000D)
                CaseEq(1)
                    SetConst(LVar1, 0xEC000E)
                CaseEq(2)
                    SetConst(LVar1, 0xEC000F)
                CaseEq(3)
                    SetConst(LVar1, 0xEC0010)
                CaseEq(4)
                    SetConst(LVar1, 0xEC0011)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            Switch(LVarA)
                CaseEq(0)
                    SetConst(LVar1, 0xEC000D)
                CaseEq(1)
                    SetConst(LVar1, 0xEC000E)
                CaseEq(2)
                    SetConst(LVar1, 0xEC000F)
                CaseEq(3)
                    SetConst(LVar1, 0xEC0010)
                CaseEq(4)
                    SetConst(LVar1, 0xEC0011)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xEC0013)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEC0001)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            Switch(LVarA)
                CaseEq(0)
                    SetConst(LVar1, 0xEC000D)
                CaseEq(1)
                    SetConst(LVar1, 0xEC000E)
                CaseEq(2)
                    SetConst(LVar1, 0xEC000F)
                CaseEq(3)
                    SetConst(LVar1, 0xEC0010)
                CaseEq(4)
                    SetConst(LVar1, 0xEC0011)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            Switch(LVarA)
                CaseEq(0)
                    SetConst(LVar1, 0xEC000D)
                CaseEq(1)
                    SetConst(LVar1, 0xEC000E)
                CaseEq(2)
                    SetConst(LVar1, 0xEC000F)
                CaseEq(3)
                    SetConst(LVar1, 0xEC0010)
                CaseEq(4)
                    SetConst(LVar1, 0xEC0011)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEC0001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            Call(GetLastElement, LVarE)
            IfFlag(LVarE, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xEC0014)
                SetConst(LVar2, 0xEC0015)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                Wait(10)
                ExecWait(TTYD64_imp_BulkyBobomb_Script_ExplosionFX)
                ExecWait(TTYD64_imp_BulkyBobomb_Script_Attack_Explosion_HurtAllTargets)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xEC000C)
                Set(LVar2, -0x3039)
                ExecWait(Ref(EVS_Enemy_Death))
                Return
            Else
                SetConst(LVar0, 1)
                Switch(LVarA)
                    CaseEq(0)
                        SetConst(LVar1, 0xEC000D)
                    CaseEq(1)
                        SetConst(LVar1, 0xEC000E)
                    CaseEq(2)
                        SetConst(LVar1, 0xEC000F)
                    CaseEq(3)
                        SetConst(LVar1, 0xEC0010)
                    CaseEq(4)
                        SetConst(LVar1, 0xEC0011)
                EndSwitch
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                Switch(LVarA)
                    CaseEq(0)
                        SetConst(LVar1, 0xEC000D)
                    CaseEq(1)
                        SetConst(LVar1, 0xEC000E)
                    CaseEq(2)
                        SetConst(LVar1, 0xEC000F)
                    CaseEq(3)
                        SetConst(LVar1, 0xEC0010)
                    CaseEq(4)
                        SetConst(LVar1, 0xEC0011)
                EndSwitch
                ExecWait(Ref(EVS_Enemy_Death))
                Return
            EndIf
        CaseEq(34)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEC0014)
            SetConst(LVar2, 0xEC0015)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Wait(10)
            ExecWait(TTYD64_imp_BulkyBobomb_Script_ExplosionFX)
            ExecWait(TTYD64_imp_BulkyBobomb_Script_Attack_Explosion_HurtAllTargets)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEC000C)
            Set(LVar2, -0x3039)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEC0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEC0013)
            Switch(LVarA)
                CaseEq(0)
                    SetConst(LVar2, 0xEC000D)
                CaseEq(1)
                    SetConst(LVar2, 0xEC000E)
                CaseEq(2)
                    SetConst(LVar2, 0xEC000F)
                CaseEq(3)
                    SetConst(LVar2, 0xEC0010)
                CaseEq(4)
                    SetConst(LVar2, 0xEC0011)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            Switch(LVarA)
                CaseEq(0)
                    SetConst(LVar1, 0xEC000D)
                CaseEq(1)
                    SetConst(LVar1, 0xEC000E)
                CaseEq(2)
                    SetConst(LVar1, 0xEC000F)
                CaseEq(3)
                    SetConst(LVar1, 0xEC0010)
                CaseEq(4)
                    SetConst(LVar1, 0xEC0011)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            Switch(LVarA)
                CaseEq(0)
                    SetConst(LVar1, 0xEC000D)
                CaseEq(1)
                    SetConst(LVar1, 0xEC000E)
                CaseEq(2)
                    SetConst(LVar1, 0xEC000F)
                CaseEq(3)
                    SetConst(LVar1, 0xEC0010)
                CaseEq(4)
                    SetConst(LVar1, 0xEC0011)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0xEC0001)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_Pider_Script_TakeTurn_Pider = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 60)
        Call(SetActorVar, ACTOR_SELF, 0, 0)
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
        Call(SetAnimation, ACTOR_SELF, 1, 0xEB0004)
    Else
        Call(SetActorVar, ACTOR_SELF, 0, 1)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetAnimation, ACTOR_SELF, 1, 0xEB0005)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 50)
        IfEq(LVarA, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEB0004)
            Call(PlaySoundAtActor, ACTOR_SELF, 725)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEB0005)
            Call(PlaySoundAtActor, ACTOR_SELF, 725)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEB0004)
            Call(PlaySoundAtActor, ACTOR_SELF, 725)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEB0005)
            Call(PlaySoundAtActor, ACTOR_SELF, 725)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEB0004)
        Else
            Call(SetAnimation, ACTOR_SELF, 1, 0xEB0005)
            Call(PlaySoundAtActor, ACTOR_SELF, 725)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEB0004)
            Call(PlaySoundAtActor, ACTOR_SELF, 725)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEB0005)
            Call(PlaySoundAtActor, ACTOR_SELF, 725)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEB0004)
            Call(PlaySoundAtActor, ACTOR_SELF, 725)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEB0005)
        EndIf
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 725)
    Call(SetActorVar, ACTOR_SELF, 1, 1)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 50)
        Set(LVar9, 2)
        Set(LVarD, 1)
    Else
        Set(LVar9, 1)
        Set(LVarD, 3)
    EndIf
    Loop(LVarD)
        Call(GetActorVar, ACTOR_SELF, 0, LVarA)
        Call(GetAnimation, ACTOR_SELF, 1, LVar7)
        IfEq(LVarA, 0)
            Call(GetActorVar, ACTOR_SELF, 1, LVar3)
            IfEq(LVar3, 0)
                Call(RandInt, 100, LVar3)
                IfLt(LVar3, 60)
                    Call(SetActorVar, ACTOR_SELF, 0, 0)
                    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
                    Call(SetAnimation, ACTOR_SELF, 1, 0xEB0004)
                Else
                    Call(SetActorVar, ACTOR_SELF, 0, 1)
                    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                    Call(SetAnimation, ACTOR_SELF, 1, 0xEB0005)
                EndIf
            Else
                Call(SetActorVar, ACTOR_SELF, 0, 0)
                Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
                Call(SetAnimation, ACTOR_SELF, 1, 0xEB0004)
            EndIf
        Else
            Call(GetActorVar, ACTOR_SELF, 1, LVar3)
            IfEq(LVar3, 0)
                Call(RandInt, 100, LVar3)
                IfLt(LVar3, 60)
                    Call(SetActorVar, ACTOR_SELF, 0, 1)
                    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                    Call(SetAnimation, ACTOR_SELF, 1, 0xEB0005)
                Else
                    Call(SetActorVar, ACTOR_SELF, 0, 0)
                    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
                    Call(SetAnimation, ACTOR_SELF, 1, 0xEB0004)
                EndIf
            Else
                Call(SetActorVar, ACTOR_SELF, 0, 1)
                Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                Call(SetAnimation, ACTOR_SELF, 1, 0xEB0005)
            EndIf
        EndIf
        Call(GetAnimation, ACTOR_SELF, 1, LVar0)
        IfNe(LVar0, LVar7)
            Call(PlaySoundAtActor, ACTOR_SELF, 725)
        EndIf
        Wait(10)
        Call(GetActorVar, ACTOR_SELF, 0, LVar3)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        IfEq(LVar3, 0)
            Sub(LVar0, 18)
            Add(LVar1, 4)
        Else
            Sub(LVar0, 19)
            Add(LVar1, 29)
        EndIf
        Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
        Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
        Call(PlaySoundAtPart, ACTOR_SELF, 2, 1000)
        Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(12.0))
        Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.099609375))
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(SetActorVar, ACTOR_SELF, 1, 0)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetAnimation, ACTOR_SELF, 2, 0xEB000A)
        Call(EnemyTestTarget, ACTOR_SELF, LVar3, 0, 0, 1, 16)
        Switch(LVar3)
            CaseOrEq(6)
            CaseOrEq(5)
                IfEq(LVar3, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
                Set(LVar1, 0)
            EndCaseGroup
        EndSwitch
        Call(FlyPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, 20, 0)
        Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
        Wait(1)
        Switch(LVar3)
            CaseOrEq(6)
            CaseOrEq(5)
            EndCaseGroup
            CaseDefault
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0xFFFF, 0, LVar9, 32)
        EndSwitch
        Call(GetOwnerTarget, LVar0, 0)
        IfEq(LVar0, 0)
            Call(GetPlayerHP, LVar0)
        Else
            Call(TTYD64_GetPartnerHP_API, LVar0)
        EndIf
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkPuff_Script_DarkPuff_TackleAttack = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0204)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 11)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0201)
    Wait(5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0205)
    Wait(5)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                SetF(LVar0, Float(0.0))
                Loop(15)
                    AddF(LVar0, Float(12.0))
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(AddGoalPos, ACTOR_SELF, -10, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                SetF(LVar0, Float(180.0))
                Loop(10)
                    AddF(LVar0, Float(18.0))
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(AddGoalPos, ACTOR_SELF, -30, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(AddGoalPos, ACTOR_SELF, -20, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(AddGoalPos, ACTOR_SELF, -10, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(TTYD64_imp_DarkPuff_Script_80222820_3B)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 13, 0)
        SetF(LVar0, Float(0.0))
        Loop(8)
            AddF(LVar0, Float(22.5))
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
    Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0xFFFF, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                SetF(LVar0, Float(180.0))
                Loop(10)
                    SubF(LVar0, Float(22.5))
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 30, 0, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(JumpWithBounce, ACTOR_SELF, 10, Float(5.0))
            Wait(10)
            Call(YieldTurn)
            ExecWait(TTYD64_imp_DarkPuff_Script_80222820_3B)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_BulkyBobomb_Script_TakeTurn_BulkyBobomb = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEC0006)
            Call(PlaySoundAtActor, ACTOR_SELF, 8396)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEC0002)
            Call(PlaySound, 647)
            Wait(10)
            Call(StopSound, 647)
            Wait(20)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_BulkyBobomb_IdleAnimations_BulkyBobomb_2))
            Call(SetActorVar, ACTOR_SELF, 0, 1)
        CaseEq(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEC0009)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEC0007)
            Call(PlaySoundAtActor, ACTOR_SELF, 8396)
            Wait(15)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 15)
            Add(LVar1, 35)
            Set(LVarF, 6)
            Call(PlayEffect_impl, 86, 6, LVar0, LVar1, LVar2, Float(1.5), 60, 0, 0, 0, 0, 0, 0, 0)
            Call(TTYD64_GetEffectData, LVarF, LVar0)
            Call(TTYD64_WritePtrField, LVar0, TTYD64_F_STATCHANGEFXDATA_20_4U, 3)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 15)
            Add(LVar2, 2)
            Call(PlayEffect_impl, 49, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8335)
            Wait(20)
            Call(TTYD64_AddDefenseBoost, ACTOR_SELF, 3, 3)
            Wait(20)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_BulkyBobomb_IdleAnimations_BulkyBobomb_3))
            Call(SetActorVar, ACTOR_SELF, 0, 2)
        CaseEq(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEC000A)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEC0008)
            Call(PlaySoundAtActor, ACTOR_SELF, 8396)
            Wait(15)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 15)
            Add(LVar1, 35)
            Set(LVarF, 6)
            Call(PlayEffect_impl, 86, 0, LVar0, LVar1, LVar2, Float(1.5), 60, 0, 0, 0, 0, 0, 0, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 15)
            Add(LVar2, 2)
            Call(PlayParalyzeHitFX)
            Call(PlaySoundAtActor, ACTOR_SELF, 8334)
            Call(TTYD64_GetEffectData, LVarF, LVar0)
            Call(TTYD64_WritePtrField, LVar0, TTYD64_F_STATCHANGEFXDATA_20_4U, 3)
            Call(TTYD64_AddAttackBoost, ACTOR_SELF, 3, 3)
            Wait(20)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_BulkyBobomb_IdleAnimations_BulkyBobomb_4))
            Call(SetActorVar, ACTOR_SELF, 0, 3)
        CaseEq(3)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEC000B)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEC0017)
            Call(PlaySoundAtActor, ACTOR_SELF, 8396)
            Wait(15)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 15)
            Add(LVar2, 2)
            Call(PlayParalyzeHitFX)
            Call(PlaySound, 8334)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Add(LVar1, 5)
            Add(LVar2, 1)
            Call(PlayEffect_impl, 86, 2, LVar0, LVar1, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
            Call(TTYD64_GetActorExtraData, ACTOR_SELF, 15, LVar6)
            Add(LVar6, 3)
            IfGt(LVar6, 255)
                Set(LVar6, 255)
            EndIf
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 15, LVar6)
            Wait(22)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_BulkyBobomb_IdleAnimations_BulkyBobomb_5))
            Call(SetActorVar, ACTOR_SELF, 0, 4)
        CaseEq(4)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEC000C)
            Wait(20)
            ExecWait(TTYD64_imp_BulkyBobomb_Script_ExplosionFX)
            ExecWait(TTYD64_imp_BulkyBobomb_Script_Attack_Explosion_HurtAllTargets)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEC000C)
            Set(LVar2, -0x3039)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_PalePiranha_Script_TakeTurn_8021DCD4_0D = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x370104)
        Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(MoveBattleCamOver, 1)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 20)
        Set(LVar1, 0)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Wait(15)
        Goto(123)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 802)
    Call(SetAnimation, ACTOR_SELF, 1, 0x370104)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
    Wait(8)
    Call(UseBattleCamPreset, 19)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Set(LVar1, 0)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 350)
    Call(SetBattleCamOffsetY, 45)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(MoveBattleCamOver, 20)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVar5)
    IfFlag(LVar5, 0x80000)
        Add(LVar0, 8)
        Add(LVar0, -3)
    Else
        Add(LVar0, 20)
    EndIf
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 20, 0, 0, 0)
    Label(123)
    Call(PlaySoundAtActor, ACTOR_SELF, 801)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x370103)
    Wait(8)
    Call(SetAnimation, ACTOR_SELF, 1, 0x370105)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(GetStatusFlags, ACTOR_SELF, LVar5)
            IfNotFlag(LVar5, 0x80000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x370106)
                Wait(2)
            EndIf
            Thread
                Wait(6)
                Call(PlaySoundAtActor, ACTOR_SELF, 8414)
            EndThread
            Call(SetAnimation, ACTOR_SELF, 1, 0x370107)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x370108)
            Wait(2)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            ExecWait(TTYD64_imp_PalePiranha_Script_8021D4F4_0D)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x370106)
    Wait(2)
    Thread
        Wait(6)
        Call(PlaySoundAtActor, ACTOR_SELF, 8414)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x370107)
    Wait(10)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x370108)
            Wait(15)
            Call(YieldTurn)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(TTYD64_imp_PalePiranha_Script_8021D4F4_0D)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_PalePiranha_Script_HandleEvent_8021D60C_0D = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x370109)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x37010A)
            SetConst(LVar2, 0x37010B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x37010A)
            SetConst(LVar2, 0x37010B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x37010B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x370109)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x370109)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x370109)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x370109)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            ExecWait(TTYD64_imp_PalePiranha_Script_8021D4F4_0D)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x370109)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x370109)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x370101)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(27)
            Thread
                Wait(10)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfFlag(LVar3, 0x80000)
                    Add(LVar0, 0)
                    Add(LVar1, 14)
                Else
                    Add(LVar0, 0)
                    Add(LVar1, 35)
                EndIf
                Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
                Wait(20)
            EndThread
            Loop(40)
                Call(SetAnimation, ACTOR_SELF, 1, 0x370101)
                Wait(1)
                Call(SetAnimation, ACTOR_SELF, 1, 0x370106)
                Wait(1)
            EndLoop
            Call(SetAnimation, ACTOR_SELF, 1, 0x370101)
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x370109)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x370109)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x370101)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x370109)
            ExecWait(Ref(EVS_Enemy_Hit))
            Call(PlaySoundAtActor, ACTOR_SELF, 802)
            Call(SetAnimation, ACTOR_SELF, 1, 0x370104)
            Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
            Wait(8)
            Call(HideHealthBar, ACTOR_SELF)
            Call(UseIdleAnimation, ACTOR_SELF, 0)
            Call(RemoveActor, ACTOR_SELF)
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x370109)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x370109)
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
EvtScript TTYD64_imp_DarkPuff_Script_DarkPuff_ThunderAttack = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7D0202)
    Wait(5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    Call(PlaySoundAtActor, ACTOR_SELF, 891)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Add(LVar1, 13)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.5), 29, 0, 0, 0, 0, 0, 0, 0)
        Else
            Add(LVar1, 13)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.7998046875), 29, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Add(LVar1, 13)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.5), 29, 0, 0, 0, 0, 0, 0, 0)
        Else
            Add(LVar1, 13)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.7998046875), 29, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D020E)
    Thread
        Wait(15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7D0201)
    EndThread
    Call(ClearStatusEffects, ACTOR_SELF)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Label(0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Call(battle_item_thunder_bolt_SpawnLightningFX)
            Wait(5)
            Call(StartRumble, 10)
            Call(ShakeCam, 1, 0, 5, Float(1.0))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000020, 0, 0, 2, 32)
    EndSwitch
    Call(TTYD64_GetMarioPos, LVar0)
    Call(GetOwnerTarget, LVar1, 0)
    IfEq(LVar0, 0)
        IfEq(LVar1, 0)
            Wait(1)
            Goto(1)
        EndIf
    Else
        IfEq(LVar1, 256)
            Wait(1)
            Goto(1)
        EndIf
    EndIf
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(GetOwnerTarget, LVar0, 0)
    IfEq(LVar0, 256)
        Call(TTYD64_GetPartnerHP_API, LVar1)
        IfGt(LVar1, 0)
            Wait(1)
            Goto(0)
        EndIf
    Else
        Goto(0)
    EndIf
    Label(1)
    Wait(10)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_Pider_Script_HandleEvent_Pider = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0006)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0007)
            SetConst(LVar2, 0xEB0007)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0007)
            SetConst(LVar2, 0xEB0007)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0007)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0006)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0006)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0006)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0006)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xEB0001)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEB0001)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0006)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0006)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0001)
            SetConst(LVar2, 0xEB0006)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0006)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEB0006)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0xEB0001)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_Gus_Script_HandleEvent_Gus = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0008)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0009)
            SetConst(LVar2, 0xEA0009)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0009)
            SetConst(LVar2, 0xEA0009)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0009)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0008)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0008)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0008)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0008)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0008)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0002)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0001)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0008)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0008)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0008)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0008)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0002)
            SetConst(LVar2, 0xEA0008)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0008)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0008)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0xEA0001)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkPuff_Script_HandleEvent_80222898_3B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0206)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0207)
            SetConst(LVar2, 0x7D0208)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0207)
            SetConst(LVar2, 0x7D0208)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0208)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0206)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0206)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0206)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0206)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0206)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(TTYD64_imp_DarkPuff_Script_80222820_3B)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0206)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0206)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0201)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0206)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0206)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(TTYD64_imp_DarkPuff_Script_80222820_3B)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0201)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0204)
            SetConst(LVar2, 0x7D0206)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0204)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0204)
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
EvtScript TTYD64_imp_Gus_Script_Attack_SpearCharge = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0xEA0006)
    Wait(8)
    Call(SetAnimation, ACTOR_SELF, 1, 0xEA0007)
    Wait(20)
    Call(PlaySoundAtActor, ACTOR_SELF, 8203)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -60, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0002)
            Call(YieldTurn)
            Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0001)
            Wait(15)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 28, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0xFFFF, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Add(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Add(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(EnableActorBlur, ACTOR_SELF, 0)
            Call(YieldTurn)
            Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0003)
            Call(PlaySoundAtActor, ACTOR_SELF, 8767)
            Wait(20)
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0xEA0001)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_Gus_Script_Attack_SpearThrow = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0xEA0004)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0xEA0005)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 30)
    Add(LVar1, 54)
    Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, 61)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Thread
        UseBuf(Ref(TTYD64_imp_Gus_IntTable_SpearRotation))
        Loop(11)
            BufRead1(LVar0)
            Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(PlaySoundAtPart, ACTOR_SELF, 2, 1000)
    Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(15.0))
    Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.099609375))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 2, 0xEA000C)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(FlyPartTo, ACTOR_SELF, 2, LVar0, 0, LVar2, 0, 20, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0001)
            Wait(25)
            Return
        EndCaseGroup
    EndSwitch
    Call(FlyPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, 20, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0xEA0001)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0xFFFF, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0003)
            Call(PlaySoundAtActor, ACTOR_SELF, 8767)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0001)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_BulkyBobomb_Script_Attack_Explosion_HurtAllTargets = {
    Call(CreateHomeTargetList, 264)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000200, 0, 0, 2, 32)
            Wait(2)
        EndCaseGroup
    EndSwitch
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(1)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOwnerID, LVar2)
    IfEq(LVar0, LVar2)
        Goto(2)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000200, 0, 0, 2, 32)
            Wait(2)
        EndCaseGroup
    EndSwitch
    Label(2)
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(1)
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Wait(10)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_Pider_Script_NextTurn_Pider = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 10)
        Call(UseIdleAnimation, ACTOR_SELF, 0)
        Call(EnableIdleScript, ACTOR_SELF, 0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Return
        EndIf
        Call(GetActorVar, ACTOR_SELF, 2, LVar0)
        IfEq(LVar0, 0)
            Call(GetHomePos, ACTOR_SELF, LVar0, 0, LVar1)
            Set(LVar1, 65)
            Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
        Else
            Call(GetHomePos, ACTOR_SELF, LVar0, 0, LVar1)
            Set(LVar1, 9)
            Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorVar, ACTOR_SELF, 2, 0)
        EndIf
        Call(PlaySoundAtActor, ACTOR_SELF, 813)
        Call(GetActorPos, ACTOR_SELF, 0, LVar6, 0)
        Call(GetHomePos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Call(MakeLerp, LVar6, LVar4, 15, 4)
        Loop(0)
            Call(UpdateLerp)
            Call(SetActorPos, ACTOR_SELF, LVar3, LVar0, LVar5)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Call(HPBarToHome, ACTOR_SELF)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_BulkyBobomb_Script_Idle_BulkyBobomb = {
    Label(10)
    Call(GetStatusFlags, ACTOR_SELF, LVar1)
    IfFlag(LVar1, 0x35D000)
        Wait(1)
        Goto(10)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfNe(LVar0, 4)
        Wait(1)
        Goto(10)
    EndIf
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 15)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.7998046875))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Label(1)
    Call(GetStatusFlags, ACTOR_SELF, LVar1)
    IfFlag(LVar1, 0x35D000)
        Wait(1)
        Goto(1)
    EndIf
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 15)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.7998046875))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Label(2)
    Call(GetStatusFlags, ACTOR_SELF, LVar1)
    IfFlag(LVar1, 0x35D000)
        Wait(1)
        Goto(2)
    EndIf
    Goto(10)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_tyd_part_1_Script_SetupTexturePan = {
    Call(SetTexPanner, 10, 0)
    Call(SetTexPanner, 21, 1)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 120)
        Set(LVar2, 0)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 0)
        Set(LVar6, 0)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_tyd_part_1_Script_TexturePan_Update)
    EndThread
    Thread
        Set(LVar0, 1)
        Set(LVar1, 0)
        Set(LVar2, 200)
        Set(LVar3, 0)
        Set(LVar4, 0)
        Set(LVar5, 0)
        Set(LVar6, 0)
        Set(LVar7, 0)
        Set(LVar8, 0)
        Set(LVar9, 0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Exec(TTYD64_tyd_part_1_Script_TexturePan_Update)
    EndThread
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkPuff_Script_DarkPuff_Static = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7D0205)
    Wait(5)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    Thread
        Wait(10)
        Loop(4)
            Call(PlaySoundAtActor, ACTOR_SELF, 978)
            Call(RandInt, 3, LVar0)
            Add(LVar0, 3)
            Wait(LVar0)
        EndLoop
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(ElectrifyActor, ACTOR_SELF, 99)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0201)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_BulkyBobomb_Script_ExplosionFX = {
    Call(StartRumble, 11)
    Thread
        Call(ShakeCam, 1, 0, 2, Float(0.75))
        Call(ShakeCam, 1, 0, 5, Float(3.0))
        Call(ShakeCam, 1, 0, 10, Float(4.5))
        Call(ShakeCam, 1, 0, 5, Float(3.0))
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, 2)
    Call(PlayEffect_impl, 23, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Add(LVar1, 20)
    Add(LVar2, 2)
    Call(PlayEffect_impl, 25, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8310)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_Pider_Script_Init_Pider = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_Pider_Script_TakeTurn_Pider))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_Pider_Script_HandleEvent_Pider))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_imp_Pider_Script_NextTurn_Pider))
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 50)
        Call(GetHomePos, ACTOR_SELF, LVar0, 0, LVar1)
        Set(LVar1, 65)
        Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorVar, ACTOR_SELF, 2, 1)
    Else
        Call(GetHomePos, ACTOR_SELF, LVar0, 0, LVar1)
        Set(LVar1, 9)
        Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorVar, ACTOR_SELF, 2, 0)
    EndIf
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_PalePiranha_Script_8021D4F4_0D = {
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
    Call(PlaySoundAtActor, ACTOR_SELF, 802)
    Call(SetAnimation, ACTOR_SELF, 1, 0x370104)
    Wait(10)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(PlaySoundAtActor, ACTOR_SELF, 801)
    Call(SetAnimation, ACTOR_SELF, 1, 0x370103)
    Wait(10)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkPuff_Script_Idle_8022273C_3B = {
    Set(LVarF, 0)
    Loop(0)
        Call(b_area_flo_ruff_puff_CosInterpMinMax, LVarF, LVar0, Float(0.9697265625), Float(1.0302734375), 15, 0, 0)
        Call(b_area_flo_ruff_puff_CosInterpMinMax, LVarF, LVar1, Float(1.0302734375), Float(0.9697265625), 15, 0, 0)
        Add(LVarF, 1)
        Call(SetActorScale, ACTOR_SELF, LVar1, LVar0, Float(1.0))
        IfGe(LVarF, 30)
            Set(LVarF, 0)
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};
// clang-format on

Battle TTYD64_tyd_part_1_FormationTable[] = {
    { .name = NULL,
      .formationSize = 1,
      .formation = (Formation*) TTYD64_tyd_part_1_Formation_tyd_00,
      .stage = &TTYD64_tyd_part_1_Stage_Rogueport,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_tyd_part_1_Formation_tyd_01_1,
      .stage = &TTYD64_tyd_part_1_Stage_PetalMeadows,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_tyd_part_1_Formation_tyd_01_2,
      .stage = &TTYD64_tyd_part_1_Stage_PetalMeadows,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_tyd_part_1_Formation_tyd_01_3,
      .stage = &TTYD64_tyd_part_1_Stage_PetalMeadows,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tyd_part_1_Formation_tyd_02_1,
      .stage = &TTYD64_tyd_part_1_Stage_GreatTree,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_tyd_part_1_Formation_tyd_02_2,
      .stage = &TTYD64_tyd_part_1_Stage_GreatTree,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tyd_part_1_Formation_tyd_04,
      .stage = &TTYD64_tyd_part_1_Stage_TwilightTrail,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_tyd_part_1_Formation_tyd_05_1,
      .stage = &TTYD64_tyd_part_1_Stage_PiratesGrotto,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_tyd_part_1_Formation_tyd_05_2,
      .stage = &TTYD64_tyd_part_1_Stage_PiratesGrotto,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_tyd_part_1_Formation_tyd_06,
      .stage = &TTYD64_tyd_part_1_Stage_RiversideStation,
      .onBattleStart = NULL },
    {},
};

s32 TTYD64_imp_PalePiranha_StatusTable_8021D3A0_0D[] = {
    1,  0, 2,  0, 6,  100, 9,  100, 7,  80, 4,  60, 3,  0, 11, 90, 5,  90, 10, 95, 8, 90,
    31, 0, 32, 1, 37, 0,   34, 0,   36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, 0,  0,
};

s32 TTYD64_imp_DarkPuff_StatusTable_802225F8_3B[] = {
    1,  0, 2,  0, 6,  95, 9,  100, 7,  100, 4,  100, 3,  0, 11, 95, 5,  95, 10, 95, 8, 95,
    31, 0, 32, 0, 37, 0,  34, 0,   36, 0,   35, 0,   33, 0, 38, 0,  39, 0,  41, -1, 0,
};

// clang-format off
EvtScript TTYD64_imp_DarkPuff_Script_TakeTurn_80222DE8_3B = {
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 8192)
        ExecWait(TTYD64_imp_DarkPuff_Script_DarkPuff_ThunderAttack)
        Return
    EndIf
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 60)
        ExecWait(TTYD64_imp_DarkPuff_Script_DarkPuff_TackleAttack)
    Else
        ExecWait(TTYD64_imp_DarkPuff_Script_DarkPuff_Static)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_tyd_part_1_Script_TexturePan_Update = {
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
// clang-format on

// clang-format off
EvtScript TTYD64_tyd_part_1_Script_BeforeBattle_tyd02 = {
    Call(SetSpriteShading, -1)
    Call(SetCamBGColor, 1, 0, 0, 0)
    Call(TTYD64_GetCurrentBattleID, LVar0)
    IfNe(LVar0, 0x3B04)
        Call(EnableGroup, 34, 0)
    EndIf
    Exec(TTYD64_tyd_part_1_Script_SetupTexturePan)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_Pider_StatusTable_Pider[] = {
    1,  0, 6,  90, 9,  100, 7,  90, 4,  50, 11, 90, 5,  90, 10, 90, 8, 90,
    32, 0, 37, 0,  34, 0,   36, 0,  33, 0,  38, 0,  39, 0,  41, 0,  0,
};

s32 TTYD64_imp_BulkyBobomb_StatusTable_BulkyBobomb[] = {
    1,  0, 6,  90, 9,  100, 7,  100, 4,  70, 11, 75, 5,  75, 10, 80, 8, 75,
    32, 0, 37, 0,  34, 0,   36, 0,   33, 0,  38, 0,  39, 0,  41, 0,  0,
};

s32 TTYD64_imp_Gus_StatusTable_Gus[] = {
    1,  0, 6,  90, 9,  100, 7,  70, 4,  80, 11, 70, 5,  80, 10, 90, 8, 80,
    32, 0, 37, 0,  34, 0,   36, 0,  33, 0,  38, 0,  39, 0,  41, 0,  0,
};

// clang-format off
EvtScript TTYD64_imp_DarkPuff_Script_80222820_3B = {
    Call(UseBattleCamPreset, 2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0204)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetGoalToHome, ACTOR_SELF)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 11)
    Return
    End
};
// clang-format on

FormationRow TTYD64_tyd_part_1_Formation_tyd_01_1[] = {
    { .actor = &TTYD64_tyd_part_1_imp_00_Goomba_00_Goomba,
      .home = { .index = 0 },
      .priority = 4,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GOOMBA },
    { .actor = &TTYD64_tyd_part_1_imp_00_Goomba_00_Goomba,
      .home = { .index = 1 },
      .priority = 3,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GOOMBA },
    { .actor = &TTYD64_tyd_part_1_imp_00_Goomba_00_Goomba,
      .home = { .index = 2 },
      .priority = 2,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GOOMBA },
    { .actor = &TTYD64_tyd_part_1_imp_00_Goomba_00_Goomba,
      .home = { .index = 3 },
      .priority = 1,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GOOMBA },
};

FormationRow TTYD64_tyd_part_1_Formation_tyd_05_1[] = {
    { .actor = &TTYD64_tyd_part_1_imp_16_LavaBubble_16_LavaBubble,
      .home = { .index = 0 },
      .priority = 6,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_tyd_part_1_imp_16_LavaBubble_16_LavaBubble,
      .home = { .index = 1 },
      .priority = 5,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_tyd_part_1_imp_16_LavaBubble_16_LavaBubble,
      .home = { .index = 2 },
      .priority = 4,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_tyd_part_1_imp_16_LavaBubble_16_LavaBubble,
      .home = { .index = 3 },
      .priority = 3,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
};

FormationRow TTYD64_tyd_part_1_Formation_tyd_05_2[] = {
    { .actor = &TTYD64_imp_BulkyBobomb_3B_BulkyBobomb,
      .home = { .index = 0 },
      .priority = 6,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_BulkyBobomb_3B_BulkyBobomb,
      .home = { .index = 1 },
      .priority = 5,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_BulkyBobomb_3B_BulkyBobomb,
      .home = { .index = 2 },
      .priority = 4,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_BulkyBobomb_3B_BulkyBobomb,
      .home = { .index = 3 },
      .priority = 3,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

// clang-format off
EvtScript TTYD64_imp_Gus_Script_TakeTurn_Gus = {
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 50)
        ExecWait(TTYD64_imp_Gus_Script_Attack_SpearThrow)
    Else
        ExecWait(TTYD64_imp_Gus_Script_Attack_SpearCharge)
    EndIf
    Return
    End
};
// clang-format on

FormationRow TTYD64_tyd_part_1_Formation_tyd_02_1[] = {
    { .actor = &TTYD64_imp_DarkPuff_DarkPuff,
      .home = { .index = 1 },
      .priority = 3,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_Pider_3B_Pider,
      .home = { .index = 6 },
      .priority = 2,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_Pider_3B_Pider,
      .home = { .index = 7 },
      .priority = 1,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_tyd_part_1_Formation_tyd_04[] = {
    { .actor = &TTYD64_tyd_part_1_imp_0E_HyperCleft_0E_HyperCleft,
      .home = { .index = 1 },
      .priority = 6,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_tyd_part_1_imp_0E_HyperCleft_0E_HyperCleft,
      .home = { .index = 2 },
      .priority = 5,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee,
      .home = { .index = 3 },
      .priority = 4,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

s32 TTYD64_imp_BulkyBobomb_IdleAnimations_BulkyBobomb_5[] = {
    1,  0xEC0005, 7, 0xEC0000, 6, 0xEC0015, 9, 0xEC0001, 8, 0xEC0000,
    11, 0xEC0000, 5, 0xEC0000, 4, 0xEC0015, 3, 0xEC0000, 0,
};

s32 TTYD64_imp_BulkyBobomb_IdleAnimations_BulkyBobomb_4[] = {
    1,  0xEC0004, 7, 0xEC0000, 6, 0xEC0015, 9, 0xEC0001, 8, 0xEC0000,
    11, 0xEC0000, 5, 0xEC0000, 4, 0xEC0015, 3, 0xEC0000, 0,
};

s32 TTYD64_imp_BulkyBobomb_IdleAnimations_BulkyBobomb_3[] = {
    1,  0xEC0003, 7, 0xEC0000, 6, 0xEC0015, 9, 0xEC0001, 8, 0xEC0000,
    11, 0xEC0000, 5, 0xEC0000, 4, 0xEC0015, 3, 0xEC0000, 0,
};

s32 TTYD64_imp_BulkyBobomb_IdleAnimations_BulkyBobomb_2[] = {
    1,  0xEC0002, 7, 0xEC0000, 6, 0xEC0015, 9, 0xEC0001, 8, 0xEC0000,
    11, 0xEC0000, 5, 0xEC0000, 4, 0xEC0015, 3, 0xEC0000, 0,
};

s32 TTYD64_imp_BulkyBobomb_IdleAnimations_BulkyBobomb_1[] = {
    1,  0xEC0001, 7, 0xEC0000, 6, 0xEC0015, 9, 0xEC0001, 8, 0xEC0000,
    11, 0xEC0000, 5, 0xEC0000, 4, 0xEC0015, 3, 0xEC0000, 0,
};

s32 TTYD64_imp_Gus_IdleAnimations_Gus[] = {
    1,  0xEA0001, 7, 0xEA0000, 6, 0xEA000A, 9, 0xEA000D, 8, 0xEA0000,
    11, 0xEA0000, 5, 0xEA0000, 4, 0xEA000B, 3, 0xEA0000, 0,
};

s32 TTYD64_imp_Pider_IdleAnimations_Pider[] = {
    1,  0xEB0001, 7, 0xEB0006, 6, 0xEB0008, 9, 0xEB0008, 8, 0xEB0000,
    11, 0xEB0000, 5, 0xEB0000, 4, 0xEB0009, 3, 0xEB0000, 0,
};

s32 TTYD64_imp_PalePiranha_IdleAnimations_8021D330_0D[] = {
    1,  0x370101, 7, 0x370100, 6, 0x370100, 9, 0x370101, 8, 0x370100,
    11, 0x370101, 5, 0x370100, 4, 0x370101, 3, 0x370101, 0,
};

// clang-format off
EvtScript TTYD64_imp_BulkyBobomb_Script_Init_BulkyBobomb = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_BulkyBobomb_Script_TakeTurn_BulkyBobomb))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_BulkyBobomb_Script_HandleEvent_BulkyBobomb))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_BulkyBobomb_Script_Idle_BulkyBobomb))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkPuff_Script_Init_802226F0_3B = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_DarkPuff_Script_TakeTurn_80222DE8_3B))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_DarkPuff_Script_Idle_8022273C_3B))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_DarkPuff_Script_HandleEvent_80222898_3B))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_PalePiranha_Script_Init_8021D498_0D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_PalePiranha_Script_TakeTurn_8021DCD4_0D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mim_piranha_plant_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_PalePiranha_Script_HandleEvent_8021D60C_0D))
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_imp_Pider_PartsTable_Pider[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 39 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_Pider_IdleAnimations_Pider,
        .defenseTable = b_area_kmr_part_1_goomba_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -4 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_Pider_IdleAnimations_Rock,
        .defenseTable = b_area_kmr_part_1_goomba_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_Gus_PartsTable_Gus[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -7, 37 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_Gus_IdleAnimations_Gus,
        .defenseTable = b_area_kmr_part_1_goomba_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 5, -16 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_Gus_IdleAnimations_Spear,
        .defenseTable = b_area_kmr_part_1_goomba_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_imp_DarkPuff_IdleAnimations_802225A0_3B[] = {
    1, 0x7D0201, 7, 0x7D0200, 6, 0x7D0209, 9, 0x7D0201, 8, 0x7D0200, 11, 0x7D0201, 5, 0x7D0200, 4, 0x7D020B, 0,
};

FormationRow TTYD64_tyd_part_1_Formation_tyd_02_2[] = {
    { .actor = &TTYD64_imp_PalePiranha_PalePiranha,
      .home = { .index = 1 },
      .priority = 3,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_PalePiranha_PalePiranha,
      .home = { .index = 2 },
      .priority = 2,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_tyd_part_1_Formation_tyd_01_2[] = {
    { .actor = &TTYD64_tyd_part_1_imp_00_Paragoomba_00_Paragoomba,
      .home = { .index = 5 },
      .priority = 4,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGOOMBA },
    { .actor = &TTYD64_tyd_part_1_imp_00_Paragoomba_00_Paragoomba,
      .home = { .index = 6 },
      .priority = 3,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGOOMBA },
};

FormationRow TTYD64_tyd_part_1_Formation_tyd_01_3[] = {
    { .actor = &TTYD64_tyd_part_1_imp_00_SpikedGoomba_00_SpikedGoomba,
      .home = { .index = 1 },
      .priority = 4,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
    { .actor = &TTYD64_tyd_part_1_imp_00_SpikedGoomba_00_SpikedGoomba,
      .home = { .index = 2 },
      .priority = 3,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGOOMBA },
};

FormationRow TTYD64_tyd_part_1_Formation_tyd_06[] = {
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 5 },
      .priority = 6,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 6 },
      .priority = 5,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
};

StageListRow TTYD64_tyd_part_1_StageTable[] = {
    { .name = "tyd_00", .stage = &TTYD64_tyd_part_1_Stage_Rogueport },
    { .name = "tyd_01", .stage = &TTYD64_tyd_part_1_Stage_PetalMeadows },
    { .name = "tyd_02", .stage = &TTYD64_tyd_part_1_Stage_GreatTree },
    { .name = "tyd_04", .stage = &TTYD64_tyd_part_1_Stage_TwilightTrail },
    { .name = "tyd_05", .stage = &TTYD64_tyd_part_1_Stage_PiratesGrotto },
    { .name = "tyd_06", .stage = &TTYD64_tyd_part_1_Stage_RiversideStation },
    {},
};

// clang-format off
EvtScript TTYD64_imp_Gus_Script_Init_Gus = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_Gus_Script_TakeTurn_Gus))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_Gus_Script_HandleEvent_Gus))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_Gus_IntTable_SpearRotation[] = {
    62, 68, 72, 76, 80, 84, 90, 90, 94, 101, 107,
};

Stage TTYD64_tyd_part_1_Stage_GreatTree = {
    .texture = "tst_tex",
    .shape = "tyd_bt03_shape",
    .hit = "tyd_bt03_hit",
    .preBattle = &TTYD64_tyd_part_1_Script_BeforeBattle_tyd02,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_imp_Pider_3B_Pider = {
    .flags = 0x0,
    .maxHP = 5,
    .type = 0x66,
    .level = 13,
    .partCount = 2,
    .partsData = TTYD64_imp_Pider_PartsTable_Pider,
    .initScript = &TTYD64_imp_Pider_Script_Init_Pider,
    .statusTable = TTYD64_imp_Pider_StatusTable_Pider,
    .escapeChance = 70,
    .airLiftChance = 70,
    .hurricaneChance = 100,
    .spookChance = 0,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 0,
    .size = { 36, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 32 },
};

Stage TTYD64_tyd_part_1_Stage_PiratesGrotto = {
    .texture = "kzn_tex",
    .shape = "tyd_bt05_shape",
    .hit = "tyd_bt05_hit",
    .preBattle = &b_area_kmr_part_3_kpa_13_EVS_PreBattle,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_tyd_part_1_imp_0E_HyperCleft_0E_HyperCleft = {
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

Stage TTYD64_tyd_part_1_Stage_RiversideStation = {
    .texture = "flo_tex",
    .shape = "tyd_bt06_shape",
    .hit = "tyd_bt06_hit",
    .preBattle = &b_area_kmr_part_3_kpa_13_EVS_PreBattle,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_imp_BulkyBobomb_3B_BulkyBobomb = {
    .flags = 0x0,
    .maxHP = 6,
    .type = 0x67,
    .level = 17,
    .partCount = 1,
    .partsData = TTYD64_imp_BulkyBobomb_PartsTable_BulkyBobomb,
    .initScript = &TTYD64_imp_BulkyBobomb_Script_Init_BulkyBobomb,
    .statusTable = TTYD64_imp_BulkyBobomb_StatusTable_BulkyBobomb,
    .escapeChance = 40,
    .airLiftChance = 20,
    .hurricaneChance = 80,
    .spookChance = 75,
    .upAndAwayChance = 95,
    .spinSmashReq = 4,
    .powerBounceChance = 100,
    .coinReward = 0,
    .size = { 56, 80 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -6, 38 },
    .statusTextOffset = { 12, 47 },
};

ActorBlueprint TTYD64_tyd_part_1_imp_16_LavaBubble_16_LavaBubble = {
    .flags = 0x200,
    .maxHP = 9,
    .type = 0x2B,
    .level = 17,
    .partCount = 6,
    .partsData = TTYD64_kzn_lava_bubble_ActorParts,
    .initScript = &TTYD64_kzn_lava_bubble_EVS_Init,
    .statusTable = b_area_kzn_lava_bubble_StatusTable,
    .escapeChance = 50,
    .airLiftChance = 90,
    .hurricaneChance = 85,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 1,
    .size = { 33, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_PalePiranha_PalePiranha = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x6A,
    .level = 10,
    .partCount = 1,
    .partsData = TTYD64_imp_PalePiranha_PartsTable_8021D44C_0D,
    .initScript = &TTYD64_imp_PalePiranha_Script_Init_8021D498_0D,
    .statusTable = TTYD64_imp_PalePiranha_StatusTable_8021D3A0_0D,
    .escapeChance = 60,
    .airLiftChance = 60,
    .hurricaneChance = 30,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 38, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -7, 33 },
    .statusTextOffset = { 10, 33 },
};

Stage TTYD64_tyd_part_1_Stage_Rogueport = {
    .texture = "tst_tex",
    .shape = "tyd_bt01_shape",
    .hit = "tyd_bt01_hit",
    .preBattle = &b_area_kmr_part_3_kpa_13_EVS_PreBattle,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_imp_Gus_3B_Gus = {
    .flags = 0x0,
    .maxHP = 20,
    .type = 0x65,
    .level = 55,
    .partCount = 2,
    .partsData = TTYD64_imp_Gus_PartsTable_Gus,
    .initScript = &TTYD64_imp_Gus_Script_Init_Gus,
    .statusTable = TTYD64_imp_Gus_StatusTable_Gus,
    .escapeChance = 100,
    .airLiftChance = 60,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 50,
    .spinSmashReq = 0,
    .powerBounceChance = 70,
    .coinReward = 0,
    .size = { 36, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 32 },
};

ActorBlueprint TTYD64_imp_DarkPuff_DarkPuff = {
    .flags = 0x200,
    .maxHP = 3,
    .type = 0x69,
    .level = 9,
    .partCount = 1,
    .partsData = TTYD64_imp_DarkPuff_PartsTable_802226A4_3B,
    .initScript = &TTYD64_imp_DarkPuff_Script_Init_802226F0_3B,
    .statusTable = TTYD64_imp_DarkPuff_StatusTable_802225F8_3B,
    .escapeChance = 60,
    .airLiftChance = 100,
    .hurricaneChance = 90,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 2,
    .size = { 32, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_tyd_part_1_imp_00_Goomba_00_Goomba = {
    .flags = 0x0,
    .maxHP = 2,
    .type = 0x07,
    .level = 5,
    .partCount = 1,
    .partsData = TTYD64_kmr_part_1_goomba_ActorParts,
    .initScript = &TTYD64_kmr_part_1_goomba_EVS_Init,
    .statusTable = b_area_kmr_part_1_goomba_StatusTable,
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

Stage TTYD64_tyd_part_1_Stage_TwilightTrail = {
    .texture = "mim_tex",
    .shape = "mim_bt01_shape",
    .hit = "mim_bt01_hit",
    .preBattle = &b_area_kmr_part_3_kpa_13_EVS_PreBattle,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_tyd_part_1_imp_00_SpikedGoomba_00_SpikedGoomba = {
    .flags = 0x0,
    .maxHP = 2,
    .type = 0x09,
    .level = 6,
    .partCount = 1,
    .partsData = TTYD64_kmr_part_1_spiked_goomba_ActorParts,
    .initScript = &TTYD64_kmr_part_1_spiked_goomba_EVS_Init,
    .statusTable = b_area_kmr_part_1_spiked_goomba_StatusTable,
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

ActorBlueprint TTYD64_tyd_part_1_imp_00_Paragoomba_00_Paragoomba = {
    .flags = 0x200,
    .maxHP = 2,
    .type = 0x08,
    .level = 6,
    .partCount = 4,
    .partsData = TTYD64_kmr_part_1_paragoomba_ActorParts,
    .initScript = &TTYD64_kmr_part_1_spiked_goomba_EVS_Init_8021FCA4,
    .statusTable = b_area_kmr_part_1_paragoomba_FlyingStatusTable,
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

Stage TTYD64_tyd_part_1_Stage_PetalMeadows = {
    .texture = "tst_tex",
    .shape = "tyd_bt02_shape",
    .hit = "tyd_bt02_hit",
    .preBattle = &b_area_kmr_part_3_kpa_13_EVS_PreBattle,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = "kmr_bg",
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorPartBlueprint TTYD64_imp_PalePiranha_PartsTable_8021D44C_0D[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_PalePiranha_IdleAnimations_8021D330_0D,
        .defenseTable = b_area_mim_piranha_plant_DefenseTable,
        .eventFlags = 0x10,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_DarkPuff_PartsTable_802226A4_3B[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 26 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkPuff_IdleAnimations_802225A0_3B,
        .defenseTable = b_area_flo_lakitu_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -13 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_BulkyBobomb_PartsTable_BulkyBobomb[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 52 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_BulkyBobomb_IdleAnimations_BulkyBobomb_1,
        .defenseTable = b_area_kmr_part_3_egg_jr_troopa_DefenseTable,
        .eventFlags = 0x200,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -20 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_tyd_part_1_Formation_tyd_00[] = {
    { .actor = &TTYD64_imp_Gus_3B_Gus,
      .home = { .index = 2 },
      .priority = 6,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

s32 TTYD64_imp_Pider_IdleAnimations_Rock[] = {
    1,
    0xEB000A,
    0,
};

s32 TTYD64_imp_Gus_IdleAnimations_Spear[] = {
    1,
    0xEA000C,
    0,
};

void TTYD64_InstallBattles_tyd_part_1(void) {
    Mod_SetBattleList("TTYD64", 0x3B, TTYD64_tyd_part_1_FormationTable);
    Mod_SetStageList("TTYD64", 0x3B, TTYD64_tyd_part_1_StageTable);
}
