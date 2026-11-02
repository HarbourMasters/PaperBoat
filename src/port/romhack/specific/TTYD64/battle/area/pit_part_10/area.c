#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_drop_tables.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/battle/area/battles_new.h"

API_CALLABLE(action_command_stop_leech_init);
API_CALLABLE(action_command_stop_leech_start);
API_CALLABLE(b_area_flo_ruff_puff_CosInterpMinMax);
API_CALLABLE(b_area_hos_ember_PlayLavaBubbleFlightSound);
API_CALLABLE(b_area_kpa_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_kpa_magikoopa_ShrinkActor);
API_CALLABLE(b_area_tik3_swoopula_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_tik3_swoopula_SpawnDrainHealthContinueFX);
API_CALLABLE(b_area_tik3_swoopula_SpawnDrainHealthStartFX);
extern s32 b_area_flo_ruff_puff_DefenseTable[];
extern EvtScript b_area_hos_ember_EVS_GetAvailableColumn;
extern EvtScript b_area_hos_ember_EVS_Idle;
extern EvtScript b_area_hos_magikoopa_EVS_Flee;
extern EvtScript b_area_kmr_part_1_kmr_02_EVS_PostBattle;
extern EvtScript b_area_kmr_part_3_kpa_13_EVS_PreBattle;
extern s32 b_area_kpa_magikoopa_CloneStatusTable[];
extern EvtScript b_area_kpa_magikoopa_EVS_Clone_Init;
extern EvtScript b_area_kpa_magikoopa_EVS_FlyingClone_Init;
extern EvtScript b_area_kpa_magikoopa_EVS_GetAvailableColumn;
extern EvtScript b_area_kpa_magikoopa_EVS_HandlePhase;
extern EvtScript b_area_kpa_magikoopa_EVS_Idle;
extern EvtScript b_area_kpa_magikoopa_EVS_RemoveClone;
extern s32 b_area_kpa_magikoopa_FlyingCloneStatusTable[];
extern Vec3i b_area_kpa_magikoopa_SummonPos;
extern Vec3i b_area_mac_Lee_SummonPos;
extern s32 b_area_tik3_swoopula_DefenseTable[];
extern EvtScript b_area_tik3_swoopula_EVS_Idle;
API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddActorVar);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(CountTargets);
API_CALLABLE(CreateHomeTargetList);
API_CALLABLE(ElectrifyActor);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyPartTo);
API_CALLABLE(FlyToGoal);
API_CALLABLE(ForceHomePos);
API_CALLABLE(FreezeBattleState);
API_CALLABLE(GetActorAttackBoost);
API_CALLABLE(GetActorDefenseBoost);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetBattleVar);
API_CALLABLE(GetDist2D);
API_CALLABLE(GetDistanceToGoal);
API_CALLABLE(GetEnemyMaxHP);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetIndexFromHome);
API_CALLABLE(GetIndexFromPos);
API_CALLABLE(GetLastDamage);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetMashActionQuality);
API_CALLABLE(GetOriginalActorType);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartPos);
API_CALLABLE(GetPlayerHP);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToCurrent);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HealActor);
API_CALLABLE(HideHealthBar);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(InterruptLeechActionCommand);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(JumpWithBounce);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(ResetActorSounds);
API_CALLABLE(SetActorDispOffset);
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
API_CALLABLE(SetAnimationRate);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetBattleVar);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetEnemyHP);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetPartAlpha);
API_CALLABLE(SetPartDispOffset);
API_CALLABLE(SetPartEventBits);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetProjectileTargetOffset);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTargetActor);
API_CALLABLE(SetTargetOffset);
API_CALLABLE(SetupMashMeter);
API_CALLABLE(ShowActionHud);
API_CALLABLE(ShowMessageBox);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(VanishActor);
API_CALLABLE(WaitForBuffDone);
API_CALLABLE(YieldTurn);
extern ActorBlueprint TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee;
extern s32 TTYD64_imp_18_AmazyDayzee_IdleAnimations_80221544_18[];
extern ActorPartBlueprint TTYD64_imp_18_AmazyDayzee_PartsTable_802214F8_18[];
extern EvtScript TTYD64_imp_18_AmazyDayzee_Script_Amazy_Sing_18;
extern EvtScript TTYD64_imp_18_AmazyDayzee_Script_Init_80221590_18;
extern EvtScript TTYD64_imp_18_AmazyDayzee_Script_TakeTurn_80222500_18;
extern EvtScript TTYD64_imp_Swampire_Script_8021CB94_1C;
extern EvtScript TTYD64_imp_Swampire_Script_TakeTurn_8021E7B4_1C;
extern EvtScript TTYD64_imp_DarkMagikoopa_Script_TakeTurn_8022B784_22;
extern EvtScript TTYD64_imp_DarkMagikoopa_Script_ShapeSpell_22;
extern EvtScript TTYD64_imp_PoisonPuff_Script_RuffPuff_TackleAttack;
extern EvtScript TTYD64_imp_DarkMagikoopa_Script_Electrify_22;
extern EvtScript TTYD64_imp_Swampire_Script_HandleEvent_8021C414_1C;
extern EvtScript TTYD64_imp_DarkMagikoopa_Script_BoostDefense_22;
extern EvtScript TTYD64_imp_DarkMagikoopa_Script_BoostAttack_22;
extern EvtScript TTYD64_imp_DarkMagikoopa_Script_Vanish_22;
extern EvtScript TTYD64_imp_DarkMagikoopa_Script_HandleEvent_80226338_22;
extern EvtScript TTYD64_imp_DarkMagikoopa_Script_MakeCopy_22;
extern EvtScript TTYD64_imp_DarkEmber_Script_Ember_TackleAttack_0;
extern EvtScript TTYD64_imp_DarkMagikoopa_Script_HealAll_22;
extern EvtScript TTYD64_imp_DarkEmber_Script_FireBall_22;
extern EvtScript TTYD64_imp_PoisonPuff_Script_RuffPuff_PoisonBreath;
extern EvtScript TTYD64_imp_DarkEmber_Script_Ember_TackleAttack_1;
extern EvtScript TTYD64_imp_DarkEmber_Script_HandleEvent_8021B8BC_22;
extern EvtScript TTYD64_imp_DarkMagikoopa_Script_HealOne_22;
extern EvtScript TTYD64_imp_PoisonPuff_Script_HandleEvent_80222898_18;
extern EvtScript TTYD64_imp_Swampire_Script_8021BC30_1C;
extern EvtScript TTYD64_imp_DarkEmber_Script_Ember_SpitFlames;
extern EvtScript TTYD64_imp_Swampire_Script_8021C0B4_1C;
extern EvtScript TTYD64_imp_DarkEmber_Script_Split_22;
extern EvtScript TTYD64_imp_DarkEmber_Script_Ember_SpitFlames_DamageActor;
extern EvtScript TTYD64_imp_DarkEmber_Script_TakeTurn_8021D284_22;
extern EvtScript TTYD64_imp_DarkEmber_Script_Ember_SpitFlames_LittleFlames_FlyToGoal;
extern EvtScript TTYD64_imp_DarkEmber_Script_Init_8021AEB4_22;
extern EvtScript TTYD64_imp_DarkMagikoopa_Script_Init_80225D60_22;
extern EvtScript TTYD64_imp_Swampire_Script_8021BA70_1C;
extern Battle TTYD64_pit_part_10_FormationTable[];
extern EvtScript TTYD64_imp_PoisonPuff_Script_Idle_8022273C_18;
extern ActorPartBlueprint TTYD64_imp_DarkEmber_PartsTable_8021AD80_22[];
extern EvtScript TTYD64_pit_part_10_Script_BeforeBattle_Pit;
extern s32 TTYD64_imp_DarkMagikoopa_StatusTable_80224F38_22[];
extern s32 TTYD64_imp_DarkEmber_StatusTable_8021ACD4_22[];
extern s32 TTYD64_imp_Swampire_StatusTable_8021B86C_1C[];
extern s32 TTYD64_imp_PoisonPuff_StatusTable_802225F8_18[];
extern EvtScript TTYD64_imp_DarkEmber_Script_8021B2FC_22;
extern FormationRow TTYD64_pit_part_10_Formation_Pit94_99_3[];
extern EvtScript TTYD64_imp_PoisonPuff_Script_80222820_18;
extern FormationRow TTYD64_pit_part_10_Formation_Pit93_98_2[];
extern FormationRow TTYD64_pit_part_10_Formation_Pit93_98_3[];
extern FormationRow TTYD64_pit_part_10_Formation_Pit95_3[];
extern FormationRow TTYD64_pit_part_10_Formation_Pit91_96_3[];
extern FormationRow TTYD64_pit_part_10_Formation_Pit94_99_2[];
extern FormationRow TTYD64_pit_part_10_Formation_Pit92_97_2[];
extern FormationRow TTYD64_pit_part_10_Formation_Pit92_97_3[];
extern FormationRow TTYD64_pit_part_10_Formation_Pit92_97_1[];
extern EvtScript TTYD64_imp_Swampire_Script_Init_8021B9FC_1C;
extern EvtScript TTYD64_imp_DarkEmber_Script_Ember_SpitFlames_LittleFlames;
extern EvtScript TTYD64_imp_PoisonPuff_Script_TakeTurn_80222DE8_18;
extern FormationRow TTYD64_pit_part_10_Formation_Pit93_98_1[];
extern FormationRow TTYD64_pit_part_10_Formation_Pit95_1[];
extern FormationRow TTYD64_pit_part_10_Formation_Pit95_2[];
extern FormationRow TTYD64_pit_part_10_Formation_Pit91_96_1[];
extern FormationRow TTYD64_pit_part_10_Formation_Pit91_96_2[];
extern FormationRow TTYD64_pit_part_10_Formation_Pit94_99_1[];
extern EvtScript TTYD64_imp_PoisonPuff_Script_Init_802226F0_18;
extern s32 TTYD64_imp_DarkMagikoopa_IdleAnimations_802251BC_22[];
extern s32 TTYD64_imp_Swampire_IdleAnimations_8021B964_1C[];
extern s32 TTYD64_imp_DarkMagikoopa_IdleAnimations_80225170_22[];
extern s32 TTYD64_imp_Swampire_IdleAnimations_8021B9B0_1C[];
extern s32 TTYD64_imp_DarkEmber_IdleAnimations_8021AE5C_22[];
extern s32 TTYD64_imp_PoisonPuff_IdleAnimations_802225A0_18[];
extern ActorBlueprint TTYD64_imp_DarkMagikoopa_FlyingMagiclone_22;
extern Stage TTYD64_pit_part_10_Stage_Pit1;
extern Stage TTYD64_pit_part_10_Stage_Pit2;
extern ActorBlueprint TTYD64_imp_Swampire_Swampire;
extern ActorBlueprint TTYD64_imp_DarkEmber_DarkEmber;
extern ActorBlueprint TTYD64_imp_DarkMagikoopa_DarkMagikoopa;
extern ActorBlueprint TTYD64_imp_PoisonPuff_PoisonPuff;
extern ActorBlueprint TTYD64_imp_DarkMagikoopa_Magiclone_22;
extern s32 TTYD64_imp_DarkEmber_DefenseTable_8021ACB0_22[];
extern ActorPartBlueprint TTYD64_imp_DarkMagikoopa_PartsTable_802292A8_22[];
extern ActorPartBlueprint TTYD64_imp_DarkMagikoopa_PartsTable_80225090_22[];
extern ActorPartBlueprint TTYD64_imp_PoisonPuff_PartsTable_802226A4_18[];
extern ActorPartBlueprint TTYD64_imp_DarkMagikoopa_PartsTable_80229284_22[];
extern ActorPartBlueprint TTYD64_imp_Swampire_PartsTable_8021B918_1C[];
extern FormationRow TTYD64_imp_DarkMagikoopa_SpecialFormation_80229344_22[];
extern FormationRow TTYD64_imp_DarkMagikoopa_SpecialFormation_80229328_22[];
extern FormationRow TTYD64_imp_DarkEmber_SpecialFormation_8021B5A0_22[];
extern StageListRow TTYD64_pit_part_10_StageTable[];
extern s32 TTYD64_imp_DarkMagikoopa_DefenseTable_80224F20_22[];
extern s32 TTYD64_imp_DarkMagikoopa_DefenseTable_80229114_22[];
extern s32 TTYD64_imp_DarkMagikoopa_DefenseTable_80229120_22[];
extern s32 TTYD64_imp_DarkEmber_IdleAnimations_8021AEA8_22[];
extern s32 TTYD64_imp_DarkEmber_IdleAnimations_FireBall[];

// clang-format off
EvtScript TTYD64_imp_Swampire_Script_8021CB94_1C = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x340202)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
        Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Else
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x340202)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
        Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
        Call(FlyToGoal, ACTOR_SELF, 0, -4, 0)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 2, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340206)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340206)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(10.0))
            Wait(15)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(TTYD64_imp_Swampire_Script_8021BA70_1C)
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
    Wait(10)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340206)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -4, -8, -15)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340206)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    IfEq(LFlag0, 1)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 0, 32)
        Return
    EndIf
    Call(GetOwnerTarget, LVar1, 0)
    Call(GetStatusFlags, LVar1, LVar0)
    IfFlag(LVar0, 0x100000)
        Wait(10)
        Loop(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340202)
            Wait(21)
            Loop(2)
                Call(PlaySoundAtActor, ACTOR_SELF, 992)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Wait(1)
            EndLoop
            Wait(5)
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
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 6, 32)
            Wait(30)
        EndLoop
    Else
        Call(ShowMessageBox, 49, 0x7FFF)
        Call(ShowActionHud, 1)
        Call(LoadActionCommand, 6)
        Call(action_command_stop_leech_init)
        Call(SetupMashMeter, 1, 30, 0, 0, 0, 0)
        Wait(10)
        Call(SetBattleFlagBits, 0x4000, 0)
        Call(action_command_stop_leech_start, 0, 0x7FFF, 3)
        Set(LVarD, 0)
        Loop(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340202)
            Set(LFlag0, 0)
            Loop(21)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(GetOwnerTarget, LVar1, 0)
            Switch(LVar1)
                CaseEq(0)
                    Call(UseIdleAnimation, 0, 0)
                    Call(SetAnimation, 0, 0, 0x3000C)
                CaseEq(256)
                    Call(UseIdleAnimation, 256, 0)
                    Set(LVar0, 4)
                    Exec(TTYD64_SetPartnerAnimation_Battle)
            EndSwitch
            Loop(2)
                Call(PlaySoundAtActor, ACTOR_SELF, 992)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Set(LFlag0, 0)
                Loop(1)
                    Call(GetMashActionQuality, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LFlag0, 1)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
            EndLoop
            IfEq(LFlag0, 1)
                BreakLoop
            EndIf
            Set(LFlag0, 0)
            Loop(5)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(PlaySoundAtActor, ACTOR_SELF, 992)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
            Set(LFlag0, 0)
            Loop(2)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.599609375), Float(1.599609375), Float(1.0))
            Set(LFlag0, 0)
            Loop(10)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Set(LFlag0, 0)
            Loop(2)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(GetOwnerTarget, LVar1, 0)
            Call(UseIdleAnimation, LVar1, 1)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0xA000000, 0, 0, 6, 32)
            Call(GetLastDamage, LVar1, LVar3)
            IfNe(LVar3, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8301)
                Call(PlaySoundAtActor, ACTOR_SELF, 532)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 15)
                Call(b_area_tik3_swoopula_SpawnDrainHealthStartFX, LVar0, LVar1, LVar2, LVar3)
                Thread
                    Wait(15)
                    Call(PlaySoundAtActor, ACTOR_SELF, 604)
                    Call(b_area_tik3_swoopula_SpawnDrainHealthContinueFX, LVar0, LVar1, LVar2, LVar3)
                EndThread
                Add(LVar0, 20)
                Add(LVar1, 20)
                Call(PlayEffect_impl, 64, 0, LVar0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0)
                Call(GetActorHP, ACTOR_SELF, LVar0)
                Add(LVar0, LVar3)
                Call(SetEnemyHP, ACTOR_SELF, LVar0)
            Else
                Add(LVarD, 1)
                IfGt(LVarD, 1)
                    Call(InterruptLeechActionCommand)
                    BreakLoop
                EndIf
            EndIf
            Call(GetOwnerTarget, LVar2, 0)
            IfEq(LVar2, 0)
                Call(GetPlayerHP, LVar1)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar1)
            EndIf
            IfEq(LVar1, 0)
                Call(InterruptLeechActionCommand)
                BreakLoop
            EndIf
            Set(LFlag0, 0)
            Loop(30)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                BreakLoop
            EndIf
        EndLoop
        Call(InterruptLeechActionCommand)
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340202)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    Wait(10)
    Call(YieldTurn)
    ExecWait(TTYD64_imp_Swampire_Script_8021BA70_1C)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_Swampire_Script_TakeTurn_8021E7B4_1C = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_Swampire_Script_8021CB94_1C)
        Return
    EndIf
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x340202)
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 24)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 2, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340206)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(AddGoalPos, ACTOR_SELF, -50, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340206)
            Call(FlyToGoal, ACTOR_SELF, 0, -40, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(10.0))
            Wait(15)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(TTYD64_imp_Swampire_Script_8021BA70_1C)
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
    Wait(10)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340206)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -4, -8, -15)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340206)
    Call(FlyToGoal, ACTOR_SELF, 0, -40, 0)
    IfEq(LFlag0, 1)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 0, 32)
        Return
    EndIf
    Call(GetOwnerTarget, LVar1, 0)
    Call(GetStatusFlags, LVar1, LVar0)
    IfFlag(LVar0, 0x100000)
        Wait(10)
        Loop(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340202)
            Wait(21)
            Loop(2)
                Call(PlaySoundAtActor, ACTOR_SELF, 992)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Wait(1)
            EndLoop
            Wait(5)
            Call(PlaySoundAtActor, ACTOR_SELF, 992)
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
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 6, 32)
            Wait(30)
        EndLoop
    Else
        Call(ShowMessageBox, 49, 0x7FFF)
        Call(ShowActionHud, 1)
        Call(LoadActionCommand, 6)
        Call(action_command_stop_leech_init)
        Call(SetupMashMeter, 1, 30, 0, 0, 0, 0)
        Wait(10)
        Call(SetBattleFlagBits, 0x4000, 0)
        Call(action_command_stop_leech_start, 0, 0x7FFF, 3)
        Set(LVarD, 0)
        Loop(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340202)
            Set(LFlag0, 0)
            Loop(21)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(GetOwnerTarget, LVar1, 0)
            Switch(LVar1)
                CaseEq(0)
                    Call(UseIdleAnimation, 0, 0)
                    Call(SetAnimation, 0, 0, 0x3000C)
                CaseEq(256)
                    Call(UseIdleAnimation, 256, 0)
                    Set(LVar0, 4)
                    Exec(TTYD64_SetPartnerAnimation_Battle)
            EndSwitch
            Call(PlaySoundAtActor, ACTOR_SELF, 992)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
            Set(LFlag0, 0)
            Loop(1)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
            Set(LFlag0, 0)
            Loop(2)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(0.599609375), Float(1.599609375), Float(1.0))
            Set(LFlag0, 0)
            Loop(10)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Set(LFlag0, 0)
            Loop(2)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(GetOwnerTarget, LVar1, 0)
            Call(UseIdleAnimation, LVar1, 1)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0xA000000, 0, 0, 6, 32)
            Call(GetLastDamage, LVar1, LVar3)
            IfNe(LVar3, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8301)
                Call(PlaySoundAtActor, ACTOR_SELF, 532)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 15)
                Call(b_area_tik3_swoopula_SpawnDrainHealthStartFX, LVar0, LVar1, LVar2, LVar3)
                Thread
                    Wait(15)
                    Call(PlaySoundAtActor, ACTOR_SELF, 604)
                    Call(b_area_tik3_swoopula_SpawnDrainHealthContinueFX, LVar0, LVar1, LVar2, LVar3)
                EndThread
                Add(LVar0, 20)
                Add(LVar1, 20)
                Call(PlayEffect_impl, 64, 0, LVar0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0)
                Call(GetActorHP, ACTOR_SELF, LVar0)
                Add(LVar0, LVar3)
                Call(SetEnemyHP, ACTOR_SELF, LVar0)
            Else
                Add(LVarD, 1)
                IfGt(LVarD, 1)
                    Call(InterruptLeechActionCommand)
                    BreakLoop
                EndIf
            EndIf
            Call(GetOwnerTarget, LVar2, 0)
            IfEq(LVar2, 0)
                Call(GetPlayerHP, LVar1)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar1)
            EndIf
            IfEq(LVar1, 0)
                Call(InterruptLeechActionCommand)
                BreakLoop
            EndIf
            Set(LFlag0, 0)
            Loop(35)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                BreakLoop
            EndIf
        EndLoop
        Call(InterruptLeechActionCommand)
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340202)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    Wait(10)
    Call(YieldTurn)
    ExecWait(TTYD64_imp_Swampire_Script_8021BA70_1C)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkMagikoopa_Script_TakeTurn_8022B784_22 = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_DarkMagikoopa_Script_ShapeSpell_22)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 10, LVar0)
    IfEq(LVar0, 1)
        Goto(20)
    EndIf
    Set(LVarA, 0)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Set(LFlag0, 0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar1)
    IfEq(LVar1, 71)
        Call(GetActorVar, LVar0, 8, LVar1)
        IfEq(LVar1, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetActorHP, LVar0, LVar2)
    Call(GetEnemyMaxHP, LVar0, LVar3)
    MulF(LVar2, Float(100.0))
    DivF(LVar2, LVar3)
    IfEq(LFlag0, 0)
        IfLe(LVar2, 25)
            Call(RandInt, 99, LVar4)
            Add(LVar4, 1)
            IfLt(LVar4, 75)
                Add(LVarA, 1)
                Set(LVarB, LVar0)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfGt(LVarA, 0)
        Goto(10)
    EndIf
    Set(LVarA, 0)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(1)
    Set(LFlag0, 0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar1)
    IfEq(LVar1, 71)
        Call(GetActorVar, LVar0, 8, LVar1)
        IfEq(LVar1, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetActorHP, LVar0, LVar2)
    Call(GetEnemyMaxHP, LVar0, LVar3)
    MulF(LVar2, Float(100.0))
    DivF(LVar2, LVar3)
    IfEq(LFlag0, 0)
        IfLe(LVar2, 20)
            Call(RandInt, 99, LVar4)
            Add(LVar4, 1)
            IfLt(LVar4, 80)
                Add(LVarA, 1)
                Set(LVarB, LVar0)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(1)
    EndIf
    IfGt(LVarA, 0)
        Goto(10)
    EndIf
    Set(LVarA, 0)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(2)
    Set(LFlag0, 0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar1)
    IfEq(LVar1, 71)
        Call(GetActorVar, LVar0, 8, LVar1)
        IfEq(LVar1, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetActorHP, LVar0, LVar2)
    Call(GetEnemyMaxHP, LVar0, LVar3)
    MulF(LVar2, Float(100.0))
    DivF(LVar2, LVar3)
    IfEq(LFlag0, 0)
        IfLe(LVar2, 15)
            Call(RandInt, 99, LVar4)
            Add(LVar4, 1)
            IfLt(LVar4, 100)
                Add(LVarA, 1)
                Set(LVarB, LVar0)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(2)
    EndIf
    IfGt(LVarA, 0)
        Goto(10)
    EndIf
    Goto(20)
    Label(10)
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_hos_magikoopa_EVS_Flee)
        Return
    EndIf
    IfEq(LVarA, 1)
        Call(GetActorVar, ACTOR_SELF, 4, LVar0)
        IfLt(LVar0, 2)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 500)
                ExecWait(TTYD64_imp_DarkMagikoopa_Script_HealOne_22)
                Return
            EndIf
        Else
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            IfLt(LVar0, 2)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 500)
                    ExecWait(TTYD64_imp_DarkMagikoopa_Script_HealAll_22)
                    Return
                EndIf
            EndIf
        EndIf
    Else
        Call(GetActorVar, ACTOR_SELF, 3, LVar0)
        IfLt(LVar0, 2)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 500)
                ExecWait(TTYD64_imp_DarkMagikoopa_Script_HealAll_22)
                Return
            EndIf
        Else
            Call(GetActorVar, ACTOR_SELF, 4, LVar0)
            IfLt(LVar0, 2)
                SetF(LVar9, Float(100.0))
                Call(CreateHomeTargetList, 0x8002)
                Call(InitTargetIterator)
                Label(11)
                Set(LFlag0, 0)
                Call(GetOwnerTarget, LVar0, LVar1)
                Call(GetOriginalActorType, LVar0, LVar1)
                IfEq(LVar1, 71)
                    Call(GetActorVar, LVar0, 8, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                    EndIf
                EndIf
                Call(GetActorHP, LVar0, LVar2)
                Call(GetEnemyMaxHP, LVar0, LVar3)
                MulF(LVar2, Float(100.0))
                DivF(LVar2, LVar3)
                IfEq(LFlag0, 0)
                    IfLe(LVar2, LVar9)
                        SetF(LVar9, LVar2)
                        Set(LVarB, LVar0)
                    EndIf
                EndIf
                Call(ChooseNextTarget, 0, LVar0)
                IfNe(LVar0, -1)
                    Goto(11)
                EndIf
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 500)
                    ExecWait(TTYD64_imp_DarkMagikoopa_Script_HealOne_22)
                    Return
                EndIf
            EndIf
        EndIf
    EndIf
    Label(20)
    Set(LVarA, 10)
    Set(LVarB, 10)
    Set(LVarC, 10)
    Set(LVarD, 10)
    Set(LVarE, 10)
    Set(LVarF, 10)
    Call(GetActorVar, ACTOR_SELF, 10, LVar0)
    IfEq(LVar0, 1)
        Set(LVarA, 100)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Set(LVarD, 0)
        Set(LVarE, 0)
        Set(LVarF, 0)
        Goto(123)
    Else
        ExecWait(b_area_kpa_magikoopa_EVS_GetAvailableColumn)
        IfEq(LVar0, -1)
            Set(LVarB, 0)
        EndIf
    EndIf
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNe(LVar0, 0)
        Set(LVarB, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 11, LVar0)
    Switch(LVar0)
        CaseEq(4)
            Call(GetActorVar, ACTOR_SELF, 5, LVar1)
            IfLt(LVar1, 3)
                Call(RandInt, 99, LVar0)
                Add(LVar0, 1)
                IfLe(LVar0, 50)
                    Set(LVarA, 0)
                    Set(LVarB, 0)
                    Set(LVarC, 100)
                    Set(LVarD, 0)
                    Set(LVarE, 0)
                    Set(LVarF, 0)
                EndIf
            EndIf
        CaseEq(5)
            Call(GetActorVar, ACTOR_SELF, 6, LVar1)
            IfLt(LVar1, 3)
                Call(RandInt, 99, LVar0)
                Add(LVar0, 1)
                IfLe(LVar0, 50)
                    Set(LVarA, 0)
                    Set(LVarB, 0)
                    Set(LVarC, 0)
                    Set(LVarD, 100)
                    Set(LVarE, 0)
                    Set(LVarF, 0)
                EndIf
            EndIf
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    IfGe(LVar0, 3)
        Set(LVarC, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    IfGe(LVar0, 3)
        Set(LVarD, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 7, LVar0)
    IfGe(LVar0, 3)
        Set(LVarE, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfGe(LVar0, 3)
        Set(LVarF, 0)
    EndIf
    Label(123)
    Set(LVar9, 0)
    Add(LVar9, LVarA)
    Add(LVar9, LVarB)
    Add(LVar9, LVarC)
    Add(LVar9, LVarD)
    Add(LVar9, LVarE)
    Add(LVar9, LVarF)
    Sub(LVar9, 1)
    Call(RandInt, LVar9, LVar0)
    Add(LVar0, 1)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_imp_DarkMagikoopa_Script_ShapeSpell_22)
        Return
    EndIf
    Add(LVarA, LVarB)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_imp_DarkMagikoopa_Script_MakeCopy_22)
        Return
    EndIf
    Add(LVarA, LVarC)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_imp_DarkMagikoopa_Script_BoostAttack_22)
        Return
    EndIf
    Add(LVarA, LVarD)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_imp_DarkMagikoopa_Script_BoostDefense_22)
        Return
    EndIf
    Add(LVarA, LVarE)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_imp_DarkMagikoopa_Script_Electrify_22)
        Return
    EndIf
    ExecWait(TTYD64_imp_DarkMagikoopa_Script_Vanish_22)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkMagikoopa_Script_ShapeSpell_22 = {
    Call(SetActorVar, ACTOR_SELF, 11, 2)
    Set(LFlag0, 0)
    Set(LFlag1, 0)
    Call(GetActorVar, ACTOR_SELF, 10, LVar0)
    IfEq(LVar0, 1)
        Set(LFlag0, 1)
        Call(GetActorVar, ACTOR_SELF, 9, LVarA)
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        Set(LFlag1, 1)
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    IfEq(LFlag0, 1)
        Call(UseIdleAnimation, LVarA, 0)
    EndIf
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    Else
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 10)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    IfEq(LFlag1, 0)
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x560602)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 17)
            Add(LVar1, 33)
            Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 1, 0x560602)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 13)
        Else
            Sub(LVar0, 17)
            Add(LVar1, 33)
        EndIf
        Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    Else
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x570602)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 2, 0x570602)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
        EndIf
        Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Wait(30)
    Call(EnemyTestTarget, ACTOR_SELF, LVar9, 0, 0, 1, 16)
    Switch(LVar9)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LFlag0, 1)
                Call(PlaySoundAtActor, LVarA, 8405)
            EndIf
            Call(PlaySoundAtActor, ACTOR_SELF, 8405)
            IfEq(LFlag1, 0)
                IfEq(LFlag0, 1)
                    Call(SetAnimation, LVarA, 1, 0x560603)
                EndIf
                Call(SetAnimation, ACTOR_SELF, 1, 0x560603)
            Else
                IfEq(LFlag0, 1)
                    Call(SetAnimation, LVarA, 1, 0x570603)
                EndIf
                Call(SetAnimation, ACTOR_SELF, 2, 0x570603)
            EndIf
            Wait(5)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
            Sub(LVar4, 50)
            Set(LVar5, 0)
            IfEq(LFlag1, 0)
                IfEq(LFlag0, 1)
                    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                    Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
                EndIf
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfFlag(LVar3, 0x80000)
                    Sub(LVar0, 8)
                    Add(LVar1, 8)
                Else
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                EndIf
                Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
            Else
                IfEq(LFlag0, 1)
                    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                    Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
                EndIf
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfFlag(LVar3, 0x80000)
                    Sub(LVar0, 8)
                    Add(LVar1, 8)
                Else
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                EndIf
                Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
            EndIf
            Wait(50)
            IfEq(LVar9, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(YieldTurn)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            IfEq(LFlag0, 1)
                Call(UseIdleAnimation, LVarA, 1)
            EndIf
            Return
        EndCaseGroup
    EndSwitch
    IfEq(LFlag0, 1)
        Call(PlaySoundAtActor, LVarA, 8405)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8405)
    IfEq(LFlag1, 0)
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x560603)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 1, 0x560603)
    Else
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x570603)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 2, 0x570603)
    EndIf
    Wait(5)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
    IfEq(LFlag1, 0)
        IfEq(LFlag0, 1)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Add(LVar1, 20)
            Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
        EndIf
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 8)
            Add(LVar1, 8)
        Else
            Sub(LVar0, 20)
            Add(LVar1, 20)
        EndIf
        Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
    Else
        IfEq(LFlag0, 1)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Add(LVar1, 20)
            Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
        EndIf
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 8)
            Add(LVar1, 8)
        Else
            Sub(LVar0, 20)
            Add(LVar1, 20)
        EndIf
        Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
    EndIf
    Wait(18)
    IfEq(LFlag0, 1)
        Wait(2)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 7, 32)
    Else
        Wait(2)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 7, 32)
    EndIf
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(20)
            Call(YieldTurn)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    IfEq(LFlag0, 1)
        Call(UseIdleAnimation, LVarA, 1)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_PoisonPuff_Script_RuffPuff_TackleAttack = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0104)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 11)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0101)
    Wait(5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0105)
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
            ExecWait(TTYD64_imp_PoisonPuff_Script_80222820_18)
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
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0xFFFF, -0x7FFDFC9C, 8, 32)
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
            ExecWait(TTYD64_imp_PoisonPuff_Script_80222820_18)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkMagikoopa_Script_Electrify_22 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_kpa_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
        IfEq(LVar3, 0)
            Call(GetStatusFlags, LVar0, LVar4)
            IfNotFlag(LVar4, 0x4002000)
                Set(LVar8, LVar0)
                Call(SetBattleVar, 2, LVar1)
                Goto(100)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfEq(LFlag0, 0)
        Set(LFlag0, 1)
        Call(SetBattleVar, 2, -1)
        Goto(10)
    EndIf
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_hos_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_imp_DarkMagikoopa_Script_ShapeSpell_22)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 6)
    Call(AddActorVar, ACTOR_SELF, 7, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560602)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570602)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 752)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560601)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570601)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Loop(4)
            Call(PlaySoundAtActor, LVar8, 978)
            Call(RandInt, 3, LVar0)
            Add(LVar0, 3)
            Wait(LVar0)
        EndLoop
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(ElectrifyActor, LVar8, 3)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_Swampire_Script_HandleEvent_8021C414_1C = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_Swampire_Script_8021BC30_1C)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340215)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34020E)
                ExecWait(Ref(EVS_Enemy_Hit))
            EndIf
        CaseEq(10)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340215)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34020E)
                ExecWait(Ref(EVS_Enemy_Hit))
                ExecWait(TTYD64_imp_Swampire_Script_8021C0B4_1C)
            EndIf
        CaseEq(14)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340217)
                SetConst(LVar2, 0x340218)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340211)
                SetConst(LVar2, 0x340212)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                ExecWait(TTYD64_imp_Swampire_Script_8021C0B4_1C)
            EndIf
        CaseEq(36)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340217)
                SetConst(LVar2, 0x340218)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340218)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340211)
                SetConst(LVar2, 0x340212)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340212)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(47)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340215)
            ExecWait(Ref(EVS_Enemy_ShockHit_Impl))
            Call(UseBattleCamPreset, 2)
            ExecWait(TTYD64_imp_Swampire_Script_8021BA70_1C)
        CaseEq(38)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340215)
            ExecWait(Ref(EVS_Enemy_ShockHit_Impl))
            Thread
                Wait(30)
                Call(UseBattleCamPreset, 2)
            EndThread
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340215)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x34020C)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340215)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340215)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34020E)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34020E)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(56)
            Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_Swampire_IdleAnimations_8021B9B0_1C))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340202)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(TTYD64_imp_Swampire_Script_8021BA70_1C)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 1)
            Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, -24, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340202)
            SetConst(LVar2, 0x340215)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkMagikoopa_Script_BoostDefense_22 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_kpa_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
        IfEq(LVar3, 0)
            Call(GetActorDefenseBoost, LVar0, LVar4)
            IfLt(LVar4, 3)
                Set(LVar8, LVar0)
                Call(SetBattleVar, 2, LVar1)
                Goto(100)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfEq(LFlag0, 0)
        Set(LFlag0, 1)
        Call(SetBattleVar, 2, -1)
        Goto(10)
    EndIf
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_hos_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_imp_DarkMagikoopa_Script_ShapeSpell_22)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 5)
    Call(AddActorVar, ACTOR_SELF, 6, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560602)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570602)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560601)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570601)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Call(PlaySoundAtActor, LVar8, 733)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(TTYD64_BoostDefense, LVar8, 1, 3)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkMagikoopa_Script_BoostAttack_22 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_kpa_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
        IfEq(LVar3, 0)
            Call(GetActorAttackBoost, LVar0, LVar4)
            IfLt(LVar4, 3)
                Set(LVar8, LVar0)
                Call(SetBattleVar, 2, LVar1)
                Goto(100)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfEq(LFlag0, 0)
        Set(LFlag0, 1)
        Call(SetBattleVar, 2, -1)
        Goto(10)
    EndIf
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_hos_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_imp_DarkMagikoopa_Script_ShapeSpell_22)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 4)
    Call(AddActorVar, ACTOR_SELF, 5, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560602)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570602)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560601)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570601)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Call(PlaySoundAtActor, LVar8, 733)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(TTYD64_BoostAttack, LVar8, 1, 3)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkMagikoopa_Script_Vanish_22 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_kpa_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
        IfEq(LVar3, 0)
            Call(GetStatusFlags, LVar0, LVar4)
            IfNotFlag(LVar4, 0x4002000)
                Set(LVar8, LVar0)
                Call(SetBattleVar, 2, LVar1)
                Goto(100)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfEq(LFlag0, 0)
        Set(LFlag0, 1)
        Call(SetBattleVar, 2, -1)
        Goto(10)
    EndIf
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_hos_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_imp_DarkMagikoopa_Script_ShapeSpell_22)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 7)
    Call(AddActorVar, ACTOR_SELF, 8, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560602)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570602)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560601)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570601)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Call(PlaySoundAtActor, LVar8, 731)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(VanishActor, LVar8, 2)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkMagikoopa_Script_HandleEvent_80226338_22 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetPartAlpha, ACTOR_SELF, 1, 255)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            BitwiseOrConst(LVar0, 1)
            Call(SetActorVar, ACTOR_SELF, 0, LVar0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560604)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseOrEq(10)
        CaseOrEq(61)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560604)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560605)
            SetConst(LVar2, 0x560606)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560605)
            SetConst(LVar2, 0x560606)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560606)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560604)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560604)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560604)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560601)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560601)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfFlag(LVar0, 1)
                ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
                Return
            EndIf
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNe(LVar0, 0)
                ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
            EndIf
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560604)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560604)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560601)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560604)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560602)
            ExecWait(b_area_hos_magikoopa_EVS_Flee)
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560602)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                IfFlag(LVar0, 0x80000)
                    Call(SetPartDispOffset, ACTOR_SELF, 1, 0, 2, 0)
                Else
                    Call(SetPartDispOffset, ACTOR_SELF, 1, -4, 5, 0)
                EndIf
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560604)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560601)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(19)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x560604)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkMagikoopa_Script_MakeCopy_22 = {
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_hos_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(SetActorVar, ACTOR_SELF, 10, 1)
    Call(SetActorVar, ACTOR_SELF, 11, 3)
    Set(LFlag0, 0)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        Set(LFlag0, 1)
    EndIf
    IfEq(LFlag0, 0)
        Call(SummonEnemy, Ref(TTYD64_imp_DarkMagikoopa_SpecialFormation_80229328_22), 0)
    Else
        Call(SummonEnemy, Ref(TTYD64_imp_DarkMagikoopa_SpecialFormation_80229344_22), 0)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 9, LVar0)
    Set(LVarA, LVar0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(EnableIdleScript, LVarA, 0)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(UseIdleAnimation, LVarA, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 25)
    Wait(25)
    Call(PlaySoundAtActor, ACTOR_SELF, 8406)
    IfEq(LFlag0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560602)
        Call(SetAnimation, LVarA, 1, 0x560602)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 23)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570602)
        Call(SetAnimation, LVarA, 1, 0x570602)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 23)
    EndIf
    Call(PlayEffect_impl, 107, 1, LVar0, LVar1, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
    Wait(10)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(EnableIdleScript, LVar9, 1)
    Wait(30)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, -3)
    Call(SetActorPos, LVarA, LVar0, LVar1, LVar2)
    Set(LVar9, LVarA)
    Wait(15)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Call(PlaySoundAtActor, ACTOR_SELF, 8407)
    Call(PlaySoundAtActor, LVar9, 8407)
    Call(SetPartFlagBits, LVar9, 1, 0x800000, 0)
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 500)
        Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
        ExecWait(b_area_kpa_magikoopa_EVS_GetAvailableColumn)
        Call(SetGoalToIndex, ACTOR_SELF, LVar0)
        Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
    Else
        Call(SetActorSpeed, LVar9, Float(2.0))
        ExecWait(b_area_kpa_magikoopa_EVS_GetAvailableColumn)
        Call(SetGoalToIndex, LVar9, LVar0)
        Call(FlyToGoal, LVar9, 0, 0, 0)
    EndIf
    Call(SetPartFlagBits, LVar9, 1, 0x800000, 1)
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(SetEnemyHP, LVar9, LVar0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Call(GetActorPos, LVar9, LVar0, LVar1, LVar2)
    Call(ForceHomePos, LVar9, LVar0, LVar1, LVar2)
    Call(HPBarToHome, LVar9)
    IfEq(LFlag0, 0)
        Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 1)
    Else
        Call(SetPartEventBits, ACTOR_SELF, 2, 0x400000, 1)
    EndIf
    IfEq(LFlag0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560601)
        Call(SetAnimation, LVar9, 1, 0x560601)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570601)
        Call(SetAnimation, LVar9, 1, 0x570601)
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Call(UseIdleAnimation, LVar9, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkEmber_Script_Ember_TackleAttack_0 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460403)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 30, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Thread
        Call(b_area_hos_ember_PlayLavaBubbleFlightSound)
    EndThread
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 11)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 719)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x460404)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
            Call(ResetActorSounds, ACTOR_SELF, 2)
            Call(PlaySoundAtActor, ACTOR_SELF, 751)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Add(LVar2, 2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x460404)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(30)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(TTYD64_imp_DarkEmber_Script_8021B2FC_22)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Wait(5)
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 719)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0x460404)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
    Call(ResetActorSounds, ACTOR_SELF, 2)
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Set(LVarC, LVar2)
    Call(PlaySoundAtActor, ACTOR_SELF, 751)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, 2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 2, 0, 0, 6, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            Wait(20)
            ExecWait(TTYD64_imp_DarkEmber_Script_8021B2FC_22)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkMagikoopa_Script_HealAll_22 = {
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 1)
    Call(AddActorVar, ACTOR_SELF, 3, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560602)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570602)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560601)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570601)
    EndIf
    Wait(5)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Set(LFlag0, 0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar1)
    IfEq(LVar1, 71)
        Call(GetActorVar, LVar0, 8, LVar1)
        IfEq(LVar1, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    IfEq(LFlag0, 0)
        Thread
            Wait(5)
            Call(PlaySoundAtActor, LVar0, 8301)
            Call(PlaySoundAtActor, LVar0, 532)
            Wait(30)
            Call(PlaySoundAtActor, LVar0, 604)
        EndThread
        Thread
            Call(FreezeBattleState, 1)
            Call(HealActor, LVar0, 6, 1)
            Call(FreezeBattleState, 0)
        EndThread
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Call(WaitForBuffDone)
    Wait(1)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkEmber_Script_FireBall_22 = {
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
    Call(GetOwnerTarget, LVarA, 0)
    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460401)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460405)
    Wait(30)
    Call(PlaySoundAtActor, ACTOR_SELF, 720)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460406)
    Thread
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 1, 0x460401)
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Add(LVar1, 4)
    Add(LVar2, 2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(TTYD64_GetMarioPos, LVar0)
    IfEq(LVar0, 0)
        Set(LVarB, 256)
    Else
        Set(LVarB, 0)
    EndIf
    Call(GetGoalPos, LVarB, LVar3, LVar4, LVar5)
    Add(LVar3, 55)
    Sub(LVar4, 6)
    Add(LVar5, 2)
    Set(LVar6, 6)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.5), Float(0.5), Float(0.5))
    Else
        Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.7998046875), Float(0.7998046875), Float(0.7998046875))
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Add(LVar1, 4)
    Add(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, LVar6, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 0)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(6.0))
    Call(SetPartJumpGravity, ACTOR_SELF, LVar6, Float(0.009765625))
    Call(SetPartSounds, ACTOR_SELF, LVar6, 2, 720, 0)
    Call(FlyPartTo, ACTOR_SELF, LVar6, LVar3, LVar1, LVar5, 0, 0, 4)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(4.0))
    Call(GetPartPos, ACTOR_SELF, LVar6, LVar3, LVar4, LVar5)
    Add(LVar3, 40)
    Call(FlyPartTo, ACTOR_SELF, LVar6, LVar3, LVar1, LVar5, 0, 0, 4)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(5.0))
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(FlyPartTo, ACTOR_SELF, LVar6, LVar3, LVar1, LVar5, 0, 0, 3)
    Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 1)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000002, 0, 0, 6, 32)
    EndSwitch
    Wait(20)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            ExecWait(TTYD64_imp_DarkEmber_Script_8021B2FC_22)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_PoisonPuff_Script_RuffPuff_PoisonBreath = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0104)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 11)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0101)
    Wait(5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D010E)
    Wait(5)
    Call(TTYD64_SetPoisonDrive, 1)
    Call(TTYD64_SetFireBreathTint, 1)
    Call(MoveBattleCamOver, 55)
    Wait(15)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 30)
    Add(LVar1, 13)
    Add(LVar2, 10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 120)
    Set(LVar4, 20)
    Call(PlayEffect_impl, 55, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, 2, 7, 24, 0, 0, 0)
    Thread
        Call(PlaySound, 957)
        Wait(18)
        Call(PlaySound, 1981)
    EndThread
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Wait(2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x8000002, 0xFFFF, -0x7FFDFC9C, 10, 32)
            Switch(LVarF)
                CaseOrEq(0)
                CaseOrEq(2)
                CaseOrEq(10)
                EndCaseGroup
            EndSwitch
    EndSwitch
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x7D0101)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 11)
            Wait(10)
            Call(TTYD64_SetPoisonDrive, 0)
            Call(TTYD64_SetFireBreathTint, 0)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x8000002, 0xFFFF, -0x7FFDFC9C, 10, 32)
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0101)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 11)
    Wait(10)
    Call(TTYD64_SetPoisonDrive, 0)
    Call(TTYD64_SetFireBreathTint, 0)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkEmber_Script_Ember_TackleAttack_1 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460403)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Set(LVar1, 5)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Thread
        Call(b_area_hos_ember_PlayLavaBubbleFlightSound)
    EndThread
    Call(FlyToGoal, ACTOR_SELF, 0, 0, 11)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460401)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x460404)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 0)
            Add(LVar2, 1)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Sub(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Sub(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 3, 0, 1, 0)
            Wait(14)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(TTYD64_imp_DarkEmber_Script_8021B2FC_22)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x460404)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, 1)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 130, 0, 0, 6, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Set(LVar0, 1)
            Set(LVar1, 0x460404)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Wait(5)
            ExecWait(TTYD64_imp_DarkEmber_Script_8021B2FC_22)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkEmber_Script_HandleEvent_8021B8BC_22 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Exec(TTYD64_imp_DarkEmber_Script_Split_22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460407)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            Exec(TTYD64_imp_DarkEmber_Script_Split_22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460408)
            SetConst(LVar2, 0x460409)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460408)
            SetConst(LVar2, 0x460409)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460409)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            Exec(TTYD64_imp_DarkEmber_Script_Split_22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460407)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460407)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460407)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(PlaySoundAtActor, ACTOR_SELF, 1881)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460407)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460407)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(TTYD64_imp_DarkEmber_Script_8021B2FC_22)
        CaseEq(38)
            Call(PlaySoundAtActor, ACTOR_SELF, 1881)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460407)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460407)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
        CaseOrEq(28)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460401)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460407)
            ExecWait(Ref(EVS_Enemy_Hit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460407)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(TTYD64_imp_DarkEmber_Script_8021B2FC_22)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460401)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460403)
            SetConst(LVar2, 0x460407)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460403)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460403)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(61)
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkMagikoopa_Script_HealOne_22 = {
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 0)
    Call(AddActorVar, ACTOR_SELF, 4, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560602)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570602)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560601)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570601)
    EndIf
    Wait(5)
    Thread
        Wait(5)
        Call(PlaySoundAtActor, LVarB, 8301)
        Call(PlaySoundAtActor, LVarB, 532)
        Wait(30)
        Call(PlaySoundAtActor, LVarB, 604)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(HealActor, LVarB, 10, 0)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_PoisonPuff_Script_HandleEvent_80222898_18 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0106)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0107)
            SetConst(LVar2, 0x7D0108)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0107)
            SetConst(LVar2, 0x7D0108)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0108)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0106)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0106)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0106)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0106)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0106)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(TTYD64_imp_PoisonPuff_Script_80222820_18)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0106)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0106)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0101)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0106)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0106)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(TTYD64_imp_PoisonPuff_Script_80222820_18)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0101)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0104)
            SetConst(LVar2, 0x7D0106)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0104)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x7D0104)
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
EvtScript TTYD64_imp_Swampire_Script_8021BC30_1C = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340215)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340217)
            SetConst(LVar2, 0x340218)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340217)
            SetConst(LVar2, 0x340218)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340218)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340215)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Call(UseBattleCamPreset, 2)
            ExecWait(TTYD64_imp_Swampire_Script_8021BA70_1C)
        CaseEq(38)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340215)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Thread
                Wait(30)
                Call(UseBattleCamPreset, 2)
            EndThread
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340215)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340202)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340215)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340215)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340202)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340202)
            SetConst(LVar2, 0x340215)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340202)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340215)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkEmber_Script_Ember_SpitFlames = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 256)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(TTYD64_GetMarioPos, LVar0)
    IfEq(LVar0, 0)
        Set(LVarA, 256)
    Else
        Set(LVarA, 0)
    EndIf
    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfEq(LVarA, 1)
        Add(LVar0, 100)
        Set(LVar1, 5)
    Else
        Add(LVar0, 30)
        Set(LVar1, 50)
    EndIf
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460403)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Thread
        Call(b_area_hos_ember_PlayLavaBubbleFlightSound)
    EndThread
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 11)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460401)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460405)
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460406)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Add(LVar1, 4)
    Add(LVar2, 2)
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfLe(LVar0, 0)
        Call(SetTargetActor, ACTOR_SELF, 0)
    Else
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar4, 6)
    Add(LVar5, 2)
    ExecWait(TTYD64_imp_DarkEmber_Script_Ember_SpitFlames_LittleFlames)
    Wait(20)
    Switch(LVar9)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_imp_DarkEmber_Script_8021B2FC_22)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_Swampire_Script_8021C0B4_1C = {
    Call(HideHealthBar, ACTOR_SELF)
    Call(GetLastDamage, ACTOR_SELF, LVar0)
    IfLe(LVar0, 0)
        Return
    EndIf
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x340202)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 24)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfEq(LVarA, -1)
        Call(SetHomePos, ACTOR_SELF, LVar0, 45, LVar2)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalToHome, ACTOR_SELF)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 0, 0)
        Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
    Else
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalPos, ACTOR_SELF, LVar0, 45, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 0, 0)
        Call(GetIndexFromPos, ACTOR_SELF, LVarA)
        Mod(LVarA, 4)
        Add(LVarA, 4)
        Call(SetGoalToIndex, ACTOR_SELF, LVarA)
        Call(GetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
        Call(SetHomePos, ACTOR_SELF, LVarA, LVarB, LVarC)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalToHome, ACTOR_SELF)
        Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
    EndIf
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, -10)
    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 22)
    Call(b_area_tik3_swoopula_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_Swampire_IdleAnimations_8021B9B0_1C))
    Call(SetActorFlagBits, ACTOR_SELF, 512, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkEmber_Script_Split_22 = {
    Call(GetLastDamage, ACTOR_SELF, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(GetActorHP, ACTOR_SELF, LVar0)
    IfLe(LVar0, 0)
        Return
    EndIf
    Call(GetLastElement, LVar0)
    IfFlag(LVar0, 0x20000000)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    IfGe(LVar0, 2)
        Return
    EndIf
    ExecWait(b_area_hos_ember_EVS_GetAvailableColumn)
    Switch(LVarA)
        CaseOrEq(0)
        CaseOrEq(1)
        CaseOrEq(2)
        CaseOrEq(3)
            Call(SummonEnemy, Ref(TTYD64_imp_DarkEmber_SpecialFormation_8021B5A0_22), 0)
            Call(SetActorVar, LVar0, 2, 1)
            Call(GetActorHP, ACTOR_SELF, LVarB)
            Call(SetEnemyHP, LVar0, LVarB)
            Call(GetActorPos, ACTOR_SELF, LVarB, LVarC, LVarD)
            Call(SetActorPos, LVar0, LVarB, LVarC, LVarD)
            Call(SetGoalToIndex, LVar0, LVarA)
            Call(GetGoalPos, LVar0, LVarB, LVarC, LVarD)
            Call(SetHomePos, LVar0, LVarB, LVarC, LVarD)
            Call(SetActorJumpGravity, LVar0, Float(1.2001953125))
            Call(JumpToGoal, LVar0, 20, 0, 1, 0)
            Call(HPBarToHome, LVar0)
            Call(GetActorVar, ACTOR_SELF, 1, LVar1)
            Switch(LVar1)
                CaseEq(0)
                    Call(SetActorVar, LVar0, 1, 1)
                CaseEq(1)
                    Call(SetActorVar, LVar0, 1, 2)
            EndSwitch
            Call(SetActorVar, ACTOR_SELF, 1, 3)
            Call(SetActorVar, LVar0, 2, 0)
        EndCaseGroup
        CaseDefault
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkEmber_Script_Ember_SpitFlames_DamageActor = {
    Loop(0)
        Call(GetPartPos, ACTOR_SELF, LVar6, LVar1, 0, LVar2)
        Call(TTYD64_GetMarioPos, LVar0)
        IfEq(LVar0, 0)
            Set(LVar0, 256)
        Else
            Set(LVar0, 0)
        EndIf
        Call(GetActorPos, LVar0, LVar3, 0, LVar4)
        Call(GetDist2D, LVar0, LVar1, LVar2, LVar3, LVar4)
        IfLe(LVar0, 12)
            Call(GetOwnerTarget, LVar5, 0)
            Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVar9, 0, 0, 1, 16)
            Switch(LVar9)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarA, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar9, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    BreakLoop
            EndSwitch
            Call(EnemyDamageTarget, ACTOR_SELF, LVar9, 0x10000002, 0, 0, 8, 32)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVar9, 0, 0, 1, 16)
    Switch(LVar9)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar9, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVar9, 0x10000002, 0, 0, 8, 32)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkEmber_Script_TakeTurn_8021D284_22 = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Switch(LVar0)
            CaseEq(1)
                ExecWait(TTYD64_imp_DarkEmber_Script_Ember_TackleAttack_1)
            CaseEq(0)
                ExecWait(TTYD64_imp_DarkEmber_Script_Ember_TackleAttack_0)
        EndSwitch
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(1)
            Call(GetStatusFlags, 256, LVar0)
            IfFlag(LVar0, 0x1000000)
                Call(RandInt, 99, LVar0)
                IfLt(LVar0, 49)
                    ExecWait(TTYD64_imp_DarkEmber_Script_FireBall_22)
                Else
                    ExecWait(TTYD64_imp_DarkEmber_Script_Ember_TackleAttack_1)
                EndIf
            Else
                Call(RandInt, 1000, LVar0)
                IfLe(LVar0, 300)
                    ExecWait(TTYD64_imp_DarkEmber_Script_Ember_SpitFlames)
                Else
                    Call(RandInt, 99, LVar0)
                    IfLt(LVar0, 49)
                        ExecWait(TTYD64_imp_DarkEmber_Script_FireBall_22)
                    Else
                        ExecWait(TTYD64_imp_DarkEmber_Script_Ember_TackleAttack_1)
                    EndIf
                EndIf
            EndIf
        CaseEq(0)
            Call(GetStatusFlags, 256, LVar0)
            IfFlag(LVar0, 0x1000000)
                ExecWait(TTYD64_imp_DarkEmber_Script_Ember_TackleAttack_0)
            Else
                Call(RandInt, 1000, LVar0)
                IfLe(LVar0, 300)
                    ExecWait(TTYD64_imp_DarkEmber_Script_Ember_SpitFlames)
                Else
                    ExecWait(TTYD64_imp_DarkEmber_Script_Ember_TackleAttack_0)
                EndIf
            EndIf
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkEmber_Script_Ember_SpitFlames_LittleFlames_FlyToGoal = {
    Set(LVar6, 2)
    Set(LVar7, 4)
    Loop(LVar7)
        Thread
            Call(GetStatusFlags, ACTOR_SELF, LVarA)
            IfFlag(LVarA, 0x80000)
                Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.2001953125), Float(0.2001953125), Float(0.2001953125))
            Else
                Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.5), Float(0.5), Float(0.5))
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 5)
            Add(LVar1, 4)
            Add(LVar2, 2)
            Call(SetPartPos, ACTOR_SELF, LVar6, LVar0, LVar1, LVar2)
            Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(8.0))
            Call(SetPartJumpGravity, ACTOR_SELF, LVar6, Float(0.009765625))
            Call(SetPartSounds, ACTOR_SELF, LVar6, 2, 720, 0)
            IfEq(LVar7, 4)
                Call(TTYD64_GetPartnerHP_API, LVar8)
                IfGt(LVar8, 0)
                    Exec(TTYD64_imp_DarkEmber_Script_Ember_SpitFlames_DamageActor)
                EndIf
            EndIf
            Call(JumpPartTo, ACTOR_SELF, LVar6, LVar3, LVar4, LVar5, 0, 0)
            Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 1)
        EndThread
        Wait(3)
        Add(LVar6, 1)
    EndLoop
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkEmber_Script_Init_8021AEB4_22 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_DarkEmber_Script_TakeTurn_8021D284_22))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_hos_ember_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_DarkEmber_Script_HandleEvent_8021B8BC_22))
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
    EndSwitch
    Call(SetPartScale, ACTOR_SELF, 2, Float(0.5), Float(0.5), Float(0.5))
    Call(SetPartScale, ACTOR_SELF, 3, Float(0.5), Float(0.5), Float(0.5))
    Call(SetPartScale, ACTOR_SELF, 4, Float(0.5), Float(0.5), Float(0.5))
    Call(SetPartScale, ACTOR_SELF, 5, Float(0.5), Float(0.5), Float(0.5))
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 5)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkMagikoopa_Script_Init_80225D60_22 = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_DarkMagikoopa_Script_TakeTurn_8022B784_22))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_DarkMagikoopa_Script_HandleEvent_80226338_22))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kpa_magikoopa_EVS_HandlePhase))
    Call(GetBattleVar, 2, LVar0)
    IfEq(LVar0, 0)
        Call(SetBattleVar, 2, -1)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 0)
    Call(SetActorVar, ACTOR_SELF, 7, 0)
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(SetActorVar, ACTOR_SELF, 9, -1)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, -1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_Swampire_Script_8021BA70_1C = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340202)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 0, -24, 0)
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 11)
            Call(SetActorFlagBits, ACTOR_SELF, 2048, 1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_Swampire_IdleAnimations_8021B964_1C))
            Call(SetAnimation, ACTOR_SELF, 1, 0x34020C)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 24)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340202)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 11)
    EndSwitch
    Return
    End
};
// clang-format on

Battle TTYD64_pit_part_10_FormationTable[] = {
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_10_Formation_Pit91_96_1,
      .stage = &TTYD64_pit_part_10_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_10_Formation_Pit91_96_2,
      .stage = &TTYD64_pit_part_10_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_10_Formation_Pit91_96_3,
      .stage = &TTYD64_pit_part_10_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_10_Formation_Pit92_97_1,
      .stage = &TTYD64_pit_part_10_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_10_Formation_Pit92_97_2,
      .stage = &TTYD64_pit_part_10_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_10_Formation_Pit92_97_3,
      .stage = &TTYD64_pit_part_10_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_10_Formation_Pit93_98_1,
      .stage = &TTYD64_pit_part_10_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_10_Formation_Pit93_98_2,
      .stage = &TTYD64_pit_part_10_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_10_Formation_Pit93_98_3,
      .stage = &TTYD64_pit_part_10_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_10_Formation_Pit94_99_1,
      .stage = &TTYD64_pit_part_10_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_10_Formation_Pit94_99_2,
      .stage = &TTYD64_pit_part_10_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 5,
      .formation = (Formation*) TTYD64_pit_part_10_Formation_Pit94_99_3,
      .stage = &TTYD64_pit_part_10_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_10_Formation_Pit95_1,
      .stage = &TTYD64_pit_part_10_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_10_Formation_Pit95_2,
      .stage = &TTYD64_pit_part_10_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_10_Formation_Pit95_3,
      .stage = &TTYD64_pit_part_10_Stage_Pit1,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_imp_PoisonPuff_Script_Idle_8022273C_18 = {
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

ActorPartBlueprint TTYD64_imp_DarkEmber_PartsTable_8021AD80_22[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 25 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkEmber_IdleAnimations_8021AE5C_22,
        .defenseTable = TTYD64_imp_DarkEmber_DefenseTable_8021ACB0_22,
        .eventFlags = 0x2,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -3, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkEmber_IdleAnimations_8021AEA8_22,
        .defenseTable = TTYD64_imp_DarkEmber_DefenseTable_8021ACB0_22,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkEmber_IdleAnimations_8021AEA8_22,
        .defenseTable = TTYD64_imp_DarkEmber_DefenseTable_8021ACB0_22,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkEmber_IdleAnimations_8021AEA8_22,
        .defenseTable = TTYD64_imp_DarkEmber_DefenseTable_8021ACB0_22,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkEmber_IdleAnimations_8021AEA8_22,
        .defenseTable = TTYD64_imp_DarkEmber_DefenseTable_8021ACB0_22,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 6,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkEmber_IdleAnimations_FireBall,
        .defenseTable = TTYD64_imp_DarkEmber_DefenseTable_8021ACB0_22,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_pit_part_10_Script_BeforeBattle_Pit = {
    Call(EnableGroup, 26, 0)
    Switch(AreaByte(0))
        CaseGe(80)
            Call(EnableGroup, 25, 1)
        CaseGe(50)
            Call(EnableGroup, 19, 1)
        CaseDefault
            Call(EnableGroup, 13, 1)
    EndSwitch
    Call(SetSpriteShading, -1)
    Call(SetCamBGColor, 1, 0, 0, 0)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_DarkMagikoopa_StatusTable_80224F38_22[] = {
    1,  0, 2,  0,  6,  10, 9,  100, 7,  0,  4,  90, 3,  0, 11, 50, 5,  55, 10, 60, 8, 50,
    31, 0, 32, -1, 37, 0,  34, 0,   36, -1, 35, 0,  33, 0, 38, -1, 39, -1, 41, -2, 0,
};

s32 TTYD64_imp_DarkEmber_StatusTable_8021ACD4_22[] = {
    1,  0, 2,  0, 6,  10, 9,  100, 7,  0, 4,  90, 3,  0, 11, 50, 5,  55, 10, 60, 8, 50,
    31, 0, 32, 0, 37, 0,  34, 0,   36, 1, 35, 0,  33, 0, 38, 0,  39, 0,  41, 0,  0,
};

s32 TTYD64_imp_Swampire_StatusTable_8021B86C_1C[] = {
    1,  0, 2,  0, 6,  50, 9,  100, 7,  50, 4,  90, 3,  0, 11, 80, 5,  55, 10, 90, 8, 55,
    31, 0, 32, 0, 37, 0,  34, 0,   36, 1,  35, 0,  33, 0, 38, 1,  39, 0,  41, 0,  0,
};

s32 TTYD64_imp_PoisonPuff_StatusTable_802225F8_18[] = {
    1,  0, 2,  0, 6,  50, 9,  90, 7,  70, 4,  100, 3,  0, 11, 70, 5,  40, 10, 75, 8, 80,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,   33, 0, 38, 0,  39, 0,  41, -1, 0,
};

// clang-format off
EvtScript TTYD64_imp_DarkEmber_Script_8021B2FC_22 = {
    Call(SetAnimation, ACTOR_SELF, 1, 0x460403)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Thread
        Call(b_area_hos_ember_PlayLavaBubbleFlightSound)
    EndThread
    Call(FlyToGoal, ACTOR_SELF, 0, 1, 11)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460401)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pit_part_10_Formation_Pit94_99_3[] = {
    { .actor = &TTYD64_imp_Swampire_Swampire,
      .home = { .index = 4 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWAMPIRE },
    { .actor = &TTYD64_imp_Swampire_Swampire,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWAMPIRE },
    { .actor = &TTYD64_imp_Swampire_Swampire,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWAMPIRE },
    { .actor = &TTYD64_imp_Swampire_Swampire,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWAMPIRE },
    { .actor = &TTYD64_imp_Swampire_Swampire,
      .home = { .index = 11 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWAMPIRE },
};

// clang-format off
EvtScript TTYD64_imp_PoisonPuff_Script_80222820_18 = {
    Call(UseBattleCamPreset, 2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0104)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetGoalToHome, ACTOR_SELF)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 11)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pit_part_10_Formation_Pit93_98_2[] = {
    { .actor = &TTYD64_imp_DarkEmber_DarkEmber,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKEMBER },
    { .actor = &TTYD64_imp_DarkEmber_DarkEmber,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKEMBER },
    { .actor = &TTYD64_imp_DarkEmber_DarkEmber,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKEMBER },
    { .actor = &TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_AMAZYDAYZEE },
};

FormationRow TTYD64_pit_part_10_Formation_Pit93_98_3[] = {
    { .actor = &TTYD64_imp_DarkEmber_DarkEmber,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKEMBER },
    { .actor = &TTYD64_imp_DarkEmber_DarkEmber,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKEMBER },
    { .actor = &TTYD64_imp_DarkEmber_DarkEmber,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKEMBER },
    { .actor = &TTYD64_imp_DarkEmber_DarkEmber,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKEMBER },
};

FormationRow TTYD64_pit_part_10_Formation_Pit95_3[] = {
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
};

FormationRow TTYD64_pit_part_10_Formation_Pit91_96_3[] = {
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
};

FormationRow TTYD64_pit_part_10_Formation_Pit94_99_2[] = {
    { .actor = &TTYD64_imp_Swampire_Swampire,
      .home = { .index = 4 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWAMPIRE },
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
    { .actor = &TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_AMAZYDAYZEE },
    { .actor = &TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_AMAZYDAYZEE },
};

FormationRow TTYD64_pit_part_10_Formation_Pit92_97_2[] = {
    { .actor = &TTYD64_imp_PoisonPuff_PoisonPuff,
      .home = { .index = 4 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POISONPUFF },
    { .actor = &TTYD64_imp_PoisonPuff_PoisonPuff,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POISONPUFF },
    { .actor = &TTYD64_imp_PoisonPuff_PoisonPuff,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POISONPUFF },
    { .actor = &TTYD64_imp_DarkEmber_DarkEmber,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKEMBER },
};

FormationRow TTYD64_pit_part_10_Formation_Pit92_97_3[] = {
    { .actor = &TTYD64_imp_PoisonPuff_PoisonPuff,
      .home = { .index = 4 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POISONPUFF },
    { .actor = &TTYD64_imp_PoisonPuff_PoisonPuff,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POISONPUFF },
    { .actor = &TTYD64_imp_PoisonPuff_PoisonPuff,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POISONPUFF },
    { .actor = &TTYD64_imp_PoisonPuff_PoisonPuff,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POISONPUFF },
};

FormationRow TTYD64_pit_part_10_Formation_Pit92_97_1[] = {
    { .actor = &TTYD64_imp_PoisonPuff_PoisonPuff,
      .home = { .index = 4 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POISONPUFF },
    { .actor = &TTYD64_imp_Swampire_Swampire,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWAMPIRE },
    { .actor = &TTYD64_imp_PoisonPuff_PoisonPuff,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POISONPUFF },
    { .actor = &TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_AMAZYDAYZEE },
};

// clang-format off
EvtScript TTYD64_imp_Swampire_Script_Init_8021B9FC_1C = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_Swampire_Script_TakeTurn_8021E7B4_1C))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_tik3_swoopula_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_Swampire_Script_HandleEvent_8021C414_1C))
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkEmber_Script_Ember_SpitFlames_LittleFlames = {
    Exec(TTYD64_imp_DarkEmber_Script_Ember_SpitFlames_LittleFlames_FlyToGoal)
    Call(GetDistanceToGoal, ACTOR_SELF, LVar0)
    DivF(LVar0, Float(8.0))
    Add(LVar0, 1)
    Wait(LVar0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_PoisonPuff_Script_TakeTurn_80222DE8_18 = {
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 70)
        ExecWait(TTYD64_imp_PoisonPuff_Script_RuffPuff_TackleAttack)
    Else
        ExecWait(TTYD64_imp_PoisonPuff_Script_RuffPuff_PoisonBreath)
    EndIf
    Return
    End
};
// clang-format on

FormationRow TTYD64_pit_part_10_Formation_Pit93_98_1[] = {
    { .actor = &TTYD64_imp_DarkEmber_DarkEmber,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKEMBER },
    { .actor = &TTYD64_imp_DarkEmber_DarkEmber,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKEMBER },
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
};

FormationRow TTYD64_pit_part_10_Formation_Pit95_1[] = {
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
    { .actor = &TTYD64_imp_Swampire_Swampire,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWAMPIRE },
};

FormationRow TTYD64_pit_part_10_Formation_Pit95_2[] = {
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
    { .actor = &TTYD64_imp_PoisonPuff_PoisonPuff,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POISONPUFF },
    { .actor = &TTYD64_imp_PoisonPuff_PoisonPuff,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POISONPUFF },
};

FormationRow TTYD64_pit_part_10_Formation_Pit91_96_1[] = {
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
    { .actor = &TTYD64_imp_Swampire_Swampire,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWAMPIRE },
};

FormationRow TTYD64_pit_part_10_Formation_Pit91_96_2[] = {
    { .actor = &TTYD64_imp_DarkMagikoopa_DarkMagikoopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMAGIKOOPA },
    { .actor = &TTYD64_imp_PoisonPuff_PoisonPuff,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POISONPUFF },
    { .actor = &TTYD64_imp_PoisonPuff_PoisonPuff,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POISONPUFF },
};

FormationRow TTYD64_pit_part_10_Formation_Pit94_99_1[] = {
    { .actor = &TTYD64_imp_Swampire_Swampire,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWAMPIRE },
    { .actor = &TTYD64_imp_PoisonPuff_PoisonPuff,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POISONPUFF },
    { .actor = &TTYD64_imp_PoisonPuff_PoisonPuff,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POISONPUFF },
};

// clang-format off
EvtScript TTYD64_imp_PoisonPuff_Script_Init_802226F0_18 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_PoisonPuff_Script_TakeTurn_80222DE8_18))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_PoisonPuff_Script_Idle_8022273C_18))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_PoisonPuff_Script_HandleEvent_80222898_18))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_DarkMagikoopa_IdleAnimations_802251BC_22[] = {
    1,  0x570601, 7, 0x570600, 6, 0x570608, 9, 0x570601, 8, 0x570600,
    11, 0x570601, 5, 0x570600, 4, 0x570607, 3, 0x570607, 0,
};

s32 TTYD64_imp_Swampire_IdleAnimations_8021B964_1C[] = {
    1,  0x34020C, 7, 0x34020B, 6, 0x34020F, 9, 0x34020C, 8, 0x34020B,
    11, 0x34020C, 5, 0x34020B, 4, 0x340210, 3, 0x340210, 0,
};

s32 TTYD64_imp_DarkMagikoopa_IdleAnimations_80225170_22[] = {
    1,  0x560601, 7, 0x560600, 6, 0x560608, 9, 0x560601, 8, 0x560600,
    11, 0x560601, 5, 0x560600, 4, 0x560607, 3, 0x560607, 0,
};

s32 TTYD64_imp_Swampire_IdleAnimations_8021B9B0_1C[] = {
    1,  0x340202, 7, 0x340201, 6, 0x340213, 9, 0x340202, 8, 0x340201,
    11, 0x340202, 5, 0x340201, 4, 0x340214, 3, 0x340214, 0,
};

s32 TTYD64_imp_DarkEmber_IdleAnimations_8021AE5C_22[] = {
    1,  0x460401, 7, 0x460400, 6, 0x460401, 9, 0x460401, 8, 0x460400,
    11, 0x460401, 5, 0x460400, 4, 0x46040A, 3, 0x46040A, 0,
};

s32 TTYD64_imp_PoisonPuff_IdleAnimations_802225A0_18[] = {
    1, 0x7D0101, 7, 0x7D0100, 6, 0x7D0109, 9, 0x7D0101, 8, 0x7D0100, 11, 0x7D0101, 5, 0x7D0100, 4, 0x7D010B, 0,
};

ActorBlueprint TTYD64_imp_DarkMagikoopa_FlyingMagiclone_22 = {
    .flags = 0x200200,
    .maxHP = 7,
    .type = 0x50,
    .level = 26,
    .partCount = 1,
    .partsData = TTYD64_imp_DarkMagikoopa_PartsTable_802292A8_22,
    .initScript = &b_area_kpa_magikoopa_EVS_FlyingClone_Init,
    .statusTable = b_area_kpa_magikoopa_FlyingCloneStatusTable,
    .escapeChance = 40,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 2,
    .size = { 48, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -25, 20 },
    .statusTextOffset = { 1, 34 },
};

Stage TTYD64_pit_part_10_Stage_Pit1 = {
    .texture = "tik_tex",
    .shape = "pit_bt01_shape",
    .hit = "pit_bt01_hit",
    .preBattle = &TTYD64_pit_part_10_Script_BeforeBattle_Pit,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

Stage TTYD64_pit_part_10_Stage_Pit2 = {
    .texture = "tik_tex",
    .shape = "pit_bt02_shape",
    .hit = "pit_bt02_hit",
    .preBattle = &b_area_kmr_part_3_kpa_13_EVS_PreBattle,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_imp_Swampire_Swampire = {
    .flags = 0x200,
    .maxHP = 20,
    .type = 0x64,
    .level = 29,
    .partCount = 1,
    .partsData = TTYD64_imp_Swampire_PartsTable_8021B918_1C,
    .initScript = &TTYD64_imp_Swampire_Script_Init_8021B9FC_1C,
    .statusTable = TTYD64_imp_Swampire_StatusTable_8021B86C_1C,
    .escapeChance = 50,
    .airLiftChance = 75,
    .hurricaneChance = 50,
    .spookChance = 90,
    .upAndAwayChance = 20,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 1,
    .size = { 31, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, -20 },
    .statusTextOffset = { 10, -20 },
};

ActorBlueprint TTYD64_imp_DarkEmber_DarkEmber = {
    .flags = 0x200,
    .maxHP = 12,
    .type = 0x63,
    .level = 29,
    .partCount = 6,
    .partsData = TTYD64_imp_DarkEmber_PartsTable_8021AD80_22,
    .initScript = &TTYD64_imp_DarkEmber_Script_Init_8021AEB4_22,
    .statusTable = TTYD64_imp_DarkEmber_StatusTable_8021ACD4_22,
    .escapeChance = 50,
    .airLiftChance = 80,
    .hurricaneChance = 30,
    .spookChance = 40,
    .upAndAwayChance = 90,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 33, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_DarkMagikoopa_DarkMagikoopa = {
    .flags = 0x0,
    .maxHP = 10,
    .type = 0x62,
    .level = 29,
    .partCount = 1,
    .partsData = TTYD64_imp_DarkMagikoopa_PartsTable_80225090_22,
    .initScript = &TTYD64_imp_DarkMagikoopa_Script_Init_80225D60_22,
    .statusTable = TTYD64_imp_DarkMagikoopa_StatusTable_80224F38_22,
    .escapeChance = 50,
    .airLiftChance = 80,
    .hurricaneChance = 30,
    .spookChance = 40,
    .upAndAwayChance = 90,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 36, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 32 },
};

ActorBlueprint TTYD64_imp_PoisonPuff_PoisonPuff = {
    .flags = 0x200,
    .maxHP = 15,
    .type = 0x5D,
    .level = 34,
    .partCount = 1,
    .partsData = TTYD64_imp_PoisonPuff_PartsTable_802226A4_18,
    .initScript = &TTYD64_imp_PoisonPuff_Script_Init_802226F0_18,
    .statusTable = TTYD64_imp_PoisonPuff_StatusTable_802225F8_18,
    .escapeChance = 50,
    .airLiftChance = 90,
    .hurricaneChance = 90,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 32, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_DarkMagikoopa_Magiclone_22 = {
    .flags = 0x200000,
    .maxHP = 7,
    .type = 0x4F,
    .level = 26,
    .partCount = 1,
    .partsData = TTYD64_imp_DarkMagikoopa_PartsTable_80229284_22,
    .initScript = &b_area_kpa_magikoopa_EVS_Clone_Init,
    .statusTable = b_area_kpa_magikoopa_CloneStatusTable,
    .escapeChance = 40,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 36, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 32 },
};

s32 TTYD64_imp_DarkEmber_DefenseTable_8021ACB0_22[] = {
    1, 0, 3, -1, 4, -1, 2, 99, 0,
};

ActorPartBlueprint TTYD64_imp_DarkMagikoopa_PartsTable_802292A8_22[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -10, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkMagikoopa_IdleAnimations_802251BC_22,
        .defenseTable = TTYD64_imp_DarkMagikoopa_DefenseTable_80229120_22,
        .eventFlags = 0x20,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_DarkMagikoopa_PartsTable_80225090_22[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkMagikoopa_IdleAnimations_80225170_22,
        .defenseTable = TTYD64_imp_DarkMagikoopa_DefenseTable_80224F20_22,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_PoisonPuff_PartsTable_802226A4_18[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 26 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_PoisonPuff_IdleAnimations_802225A0_18,
        .defenseTable = b_area_flo_ruff_puff_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -13 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_DarkMagikoopa_PartsTable_80229284_22[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkMagikoopa_IdleAnimations_80225170_22,
        .defenseTable = TTYD64_imp_DarkMagikoopa_DefenseTable_80229114_22,
        .eventFlags = 0x20,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_Swampire_PartsTable_8021B918_1C[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 19 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_Swampire_IdleAnimations_8021B9B0_1C,
        .defenseTable = b_area_tik3_swoopula_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -2, -8 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_imp_DarkMagikoopa_SpecialFormation_80229344_22[] = {
    { .actor = &TTYD64_imp_DarkMagikoopa_FlyingMagiclone_22,
      .home = { .vec = &b_area_kpa_magikoopa_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_DarkMagikoopa_SpecialFormation_80229328_22[] = {
    { .actor = &TTYD64_imp_DarkMagikoopa_Magiclone_22,
      .home = { .vec = &b_area_kpa_magikoopa_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_DarkEmber_SpecialFormation_8021B5A0_22[] = {
    { .actor = &TTYD64_imp_DarkEmber_DarkEmber,
      .home = { .vec = &b_area_mac_Lee_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

StageListRow TTYD64_pit_part_10_StageTable[] = {
    { .name = "pit_01", .stage = &TTYD64_pit_part_10_Stage_Pit1 },
    { .name = "pit_12", .stage = &TTYD64_pit_part_10_Stage_Pit2 },
    {},
};

s32 TTYD64_imp_DarkMagikoopa_DefenseTable_80224F20_22[] = {
    1,
    2,
    0,
};

s32 TTYD64_imp_DarkMagikoopa_DefenseTable_80229114_22[] = {
    1,
    2,
    0,
};

s32 TTYD64_imp_DarkMagikoopa_DefenseTable_80229120_22[] = {
    1,
    2,
    0,
};

s32 TTYD64_imp_DarkEmber_IdleAnimations_8021AEA8_22[] = {
    1,
    0x460401,
    0,
};

s32 TTYD64_imp_DarkEmber_IdleAnimations_FireBall[] = {
    1,
    0x46040C,
    0,
};

void TTYD64_InstallBattles_pit_part_10(void) {
    Mod_SetBattleList("TTYD64", 0x39, TTYD64_pit_part_10_FormationTable);
    Mod_SetStageList("TTYD64", 0x39, TTYD64_pit_part_10_StageTable);
}
