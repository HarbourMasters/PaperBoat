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

API_CALLABLE(TTYD64_imp_BadgeBandit_Function_ActivateBadge);
API_CALLABLE(TTYD64_imp_BadgeBandit_Function_RemoveAndUnequipBadge);
API_CALLABLE(TTYD64_imp_BadgeBandit_Function_UpdateBadgePos);
extern s32 b_area_jan2_putrid_piranha_StatusTable[];
extern EvtScript b_area_jan_jungle_fuzzy_EVS_CountActiveSummoners;
extern EvtScript b_area_jan_jungle_fuzzy_EVS_GetAvailableColumn;
extern EvtScript b_area_jan_jungle_fuzzy_EVS_Idle;
extern Vec3i b_area_jan_jungle_fuzzy_SummonPos;
extern EvtScript b_area_jan_spear_guy_EVS_CountActiveSummoners;
extern EvtScript b_area_jan_spear_guy_EVS_GetAvailableColumn;
extern EvtScript b_area_jan_spear_guy_EVS_HandleEvent;
extern Vec3i b_area_jan_spear_guy_SummonPos;
extern EvtScript b_area_kmr_part_1_kmr_02_EVS_PostBattle;
extern EvtScript b_area_kmr_part_3_kpa_13_EVS_PreBattle;
extern s32 b_area_kzn_lava_bubble_StatusTable[];
extern s32 b_area_sbk_bandit_CoinAnims[];
extern ActorPartBlueprint b_area_sbk_bandit_CoinParts[];
extern Vec3i b_area_sbk_bandit_CoinPos;
extern s32 b_area_sbk_bandit_DefenseTable[];
extern u8 b_area_sbk_bandit_DropCoinScript[];
extern EvtScript b_area_sbk_bandit_EVS_Dummy;
extern EvtScript b_area_sbk_bandit_EVS_Init_Coin;
API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddCoin);
API_CALLABLE(AddGoalPos);
API_CALLABLE(AddVectorPolar);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(CreateHomeTargetList);
API_CALLABLE(EnableActorBlur);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(ForceHomePos);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetEncounterTrigger);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetIndexFromHome);
API_CALLABLE(GetLastDamage);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOriginalActorType);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartOffset);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(GetTargetListLength);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HideHealthBar);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActor);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(ResetAllActorSounds);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorDispOffset);
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
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetPartEventBits);
API_CALLABLE(SetPartEventFlags);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTargetActor);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
extern ActorPartBlueprint TTYD64_jan2_putrid_piranha_ActorParts[];
extern s32 TTYD64_jan2_putrid_piranha_DefaultAnims[];
extern EvtScript TTYD64_jan2_putrid_piranha_EVS_Attack_BadBreath;
extern EvtScript TTYD64_jan2_putrid_piranha_EVS_Attack_Bite;
extern EvtScript TTYD64_jan2_putrid_piranha_EVS_Init;
extern EvtScript TTYD64_jan2_putrid_piranha_EVS_TakeTurn;
extern ActorPartBlueprint TTYD64_jan_jungle_fuzzy_ActorParts[];
extern s32 TTYD64_jan_jungle_fuzzy_DefaultAnims[];
extern EvtScript TTYD64_jan_jungle_fuzzy_EVS_Attack_Leech;
extern EvtScript TTYD64_jan_jungle_fuzzy_EVS_HandleEvent;
extern s32 TTYD64_jan_jungle_fuzzy_StatusTable[];
extern ActorPartBlueprint TTYD64_jan_spear_guy_ActorParts[];
extern EvtScript TTYD64_jan_spear_guy_EVS_Attack_SpearStab;
extern EvtScript TTYD64_jan_spear_guy_EVS_Attack_Tackle;
extern EvtScript TTYD64_jan_spear_guy_EVS_Attack_ThrowSpear;
extern EvtScript TTYD64_jan_spear_guy_EVS_Attack_Vault;
extern EvtScript TTYD64_jan_spear_guy_EVS_BecomeShyGuy;
extern EvtScript TTYD64_jan_spear_guy_EVS_HandlePhase;
extern EvtScript TTYD64_jan_spear_guy_EVS_Idle;
extern EvtScript TTYD64_jan_spear_guy_EVS_ShyGuy_Init;
extern EvtScript TTYD64_jan_spear_guy_EVS_ShyGuy_TakeTurn;
extern EvtScript TTYD64_jan_spear_guy_EVS_SwitchSpearStance;
extern EvtScript TTYD64_jan_spear_guy_EVS_UpdateSpearStance;
extern s32 TTYD64_jan_spear_guy_ShyGuyAnims[];
extern s32 TTYD64_jan_spear_guy_ShyGuyStatusTable[];
extern s32 TTYD64_jan_spear_guy_SpearForwardAnims[];
extern s32 TTYD64_jan_spear_guy_SpearGuyStatusTable[];
extern s32 TTYD64_jan_spear_guy_SpearUpwardAnims[];
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
extern EvtScript TTYD64_imp_BadgeBandit_Script_Bandit_GetItemBack;
extern EvtScript TTYD64_pit_part_6_imp_14_SpearGuy_Script_SummonBackup_14;
extern EvtScript TTYD64_imp_BadgeBandit_Script_HandleEvent_8021DF88_0A;
extern EvtScript TTYD64_imp_BadgeBandit_Script_TakeTurn_8021E900_0A;
extern EvtScript TTYD64_imp_BadgeBandit_Script_Steal_Badge;
extern EvtScript TTYD64_imp_BadgeBandit_Script_Steal_Coin;
extern EvtScript TTYD64_pit_part_6_imp_14_JungleFuzzy_Script_Divide_14;
extern EvtScript TTYD64_pit_part_6_imp_14_SpearGuy_Script_TakeTurn_8021BCB4_14;
extern EvtScript TTYD64_pit_part_6_imp_14_JungleFuzzy_Script_TakeTurn_80221628_14;
extern EvtScript TTYD64_pit_part_6_imp_14_SpearGuy_Script_Init_80218980_14;
extern Battle TTYD64_pit_part_6_FormationTable[];
extern EvtScript TTYD64_imp_BadgeBandit_Script_Init_8021D750_0A;
extern EvtScript TTYD64_pit_part_6_Script_BeforeBattle_Pit;
extern s32 TTYD64_imp_BadgeBandit_StatusTable_8021D5C0_0A[];
extern FormationRow TTYD64_pit_part_6_Formation_Pit52_57_3[];
extern FormationRow TTYD64_pit_part_6_Formation_Pit55_3[];
extern FormationRow TTYD64_pit_part_6_Formation_Pit53_58_3[];
extern EvtScript TTYD64_pit_part_6_imp_14_JungleFuzzy_Script_Init_8021EB28_14;
extern FormationRow TTYD64_pit_part_6_Formation_Pit52_57_2[];
extern FormationRow TTYD64_pit_part_6_Formation_Pit55_2[];
extern FormationRow TTYD64_pit_part_6_Formation_Pit55_1[];
extern FormationRow TTYD64_pit_part_6_Formation_Pit51_56_2[];
extern FormationRow TTYD64_pit_part_6_Formation_Pit54_59_1[];
extern FormationRow TTYD64_pit_part_6_Formation_Pit51_56_3[];
extern FormationRow TTYD64_pit_part_6_Formation_Pit54_59_3[];
extern FormationRow TTYD64_pit_part_6_Formation_Pit51_56_1[];
extern FormationRow TTYD64_pit_part_6_Formation_Pit54_59_2[];
extern FormationRow TTYD64_pit_part_6_Formation_Pit53_58_1[];
extern FormationRow TTYD64_pit_part_6_Formation_Pit53_58_2[];
extern s32 TTYD64_imp_BadgeBandit_IdleAnimations_8021D55C_0A[];
extern s32 TTYD64_imp_BadgeBandit_IdleAnimations_8021D510_0A[];
extern ActorPartBlueprint TTYD64_imp_BadgeBandit_PartsTable_8021D66C_0A[];
extern FormationRow TTYD64_pit_part_6_Formation_Pit52_57_1[];
extern ActorBlueprint TTYD64_pit_part_6_imp_14_JungleFuzzy_14_JungleFuzzy;
extern ActorBlueprint TTYD64_pit_part_6_imp_15_PutridPiranha_15_PutridPiranha;
extern Stage TTYD64_pit_part_6_Stage_Pit1;
extern Stage TTYD64_pit_part_6_Stage_Pit2;
extern ActorBlueprint TTYD64_pit_part_6_imp_14_SpearGuy_14_SpearGuy;
extern ActorBlueprint TTYD64_pit_part_6_imp_14_JungleFuzzy_JungleFuzzy_14;
extern ActorBlueprint TTYD64_imp_BadgeBandit_BadgeBandit;
extern ActorBlueprint TTYD64_pit_part_6_imp_14_SpearGuy_SpearGuy_14;
extern ActorBlueprint TTYD64_imp_BadgeBandit_BanditB_0A;
extern ActorBlueprint TTYD64_pit_part_6_imp_16_LavaBubble_16_LavaBubble;
extern FormationRow TTYD64_pit_part_6_imp_14_SpearGuy_SpecialFormation_8021A8DC_14[];
extern FormationRow TTYD64_imp_BadgeBandit_SpecialFormation_8021D734_0A[];
extern FormationRow TTYD64_pit_part_6_imp_14_JungleFuzzy_SpecialFormation_8022180C_14[];
extern FormationRow TTYD64_pit_part_6_imp_14_SpearGuy_SpecialFormation_8021A8C0_14[];
extern StageListRow TTYD64_pit_part_6_StageTable[];
API_CALLABLE(TTYD64_BattlesNew_ReadN64PlayerBadge);

// clang-format off
EvtScript TTYD64_imp_BadgeBandit_Script_Bandit_GetItemBack = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
        CaseEq(1)
            Call(GetActorVar, ACTOR_SELF, 2, LVar9)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_BadgeBandit_IdleAnimations_8021D510_0A))
            Call(SetPartFlagBits, ACTOR_SELF, 2, 0x100000, 0)
            Call(SummonEnemy, Ref(TTYD64_imp_BadgeBandit_SpecialFormation_8021D734_0A), 0)
            Set(LVarA, LVar0)
            IfEq(LVar9, 2)
                Call(SetActorFlagBits, LVarA, 1, 1)
                Thread
                    Loop(0)
                        Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
                        Sub(LVar0, 85)
                        Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
                        Wait(1)
                        Call(GetActorVar, ACTOR_SELF, 4, LVar0)
                        IfEq(LVar0, -1)
                            BreakLoop
                        EndIf
                    EndLoop
                EndThread
            EndIf
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
            IfEq(LVar9, 1)
                Call(PlaySoundAtActor, LVarA, 530)
            EndIf
            Call(AddVectorPolar, LVar1, LVar3, Float(20.0), LVar0)
            Call(SetGoalPos, LVarA, LVar1, 0, LVar3)
            Call(JumpToGoal, LVarA, 10, 0, 1, 0)
            IfEq(LVar9, 1)
                Call(PlaySoundAtActor, LVarA, 530)
            EndIf
            Call(AddVectorPolar, LVar1, LVar3, Float(10.0), LVar0)
            Call(SetGoalPos, LVarA, LVar1, 0, LVar3)
            Call(JumpToGoal, LVarA, 5, 0, 1, 0)
            IfEq(LVar9, 1)
                Call(PlaySoundAtActor, LVarA, 530)
            EndIf
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
                    IfEq(LVar9, 1)
                        Call(PlaySoundAtActor, LVarA, 530)
                    EndIf
                Else
                    Set(LVar4, LVar3)
                    Add(LVar3, 30)
                    Call(SetGoalPos, LVarA, LVar3, LVar1, LVar2)
                    Call(JumpToGoal, LVarA, 0, 0, 1, 0)
                    IfEq(LVar9, 1)
                        Call(PlaySoundAtActor, LVarA, 530)
                    EndIf
                EndIf
            Else
                Set(LVar4, LVar3)
                Sub(LVar4, LVar0)
                IfLt(LVar4, 30)
                    Call(SetGoalPos, LVarA, LVar0, LVar1, LVar2)
                    Call(JumpToGoal, LVarA, 5, 0, 1, 0)
                    IfEq(LVar9, 1)
                        Call(PlaySoundAtActor, LVarA, 530)
                    EndIf
                Else
                    Sub(LVar3, 30)
                    Call(SetGoalPos, LVarA, LVar3, LVar1, LVar2)
                    Call(JumpToGoal, LVarA, 0, 0, 1, 0)
                    IfEq(LVar9, 1)
                        Call(PlaySoundAtActor, LVarA, 530)
                    EndIf
                EndIf
            EndIf
            Goto(5)
            Label(10)
            Call(EnableActorBlur, LVarA, 1)
            Call(SetTargetActor, LVarA, 0)
            Call(SetGoalToTarget, LVarA)
            Call(JumpToGoal, LVarA, 15, 0, 0, 0)
            Call(GetGoalPos, LVarA, LVar0, LVar1, LVar2)
            Switch(LVar9)
                CaseEq(1)
                    Call(PlayEffect_impl, 73, 0, LVar0, LVar1, LVar2, Float(1.0), 0, 0, 0, 0, 0, 0, 0, 0)
                    Call(PlaySoundAtActor, LVarA, 529)
                    Call(GetActorVar, LVarA, 1, LVar0)
                    Call(AddCoin, LVar0)
                CaseEq(2)
                    Call(PlayEffect_impl, 73, 0, LVar0, LVar1, LVar2, Float(1.0), 0, 0, 0, 0, 0, 0, 0, 0)
                    Call(GetActorVar, LVarA, 1, LVar0)
                    Call(TTYD64_BattlesNew_AddBadge, LVar0, 0)
                    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                    IfEq(LVar1, 1)
                        Call(TTYD64_imp_BadgeBandit_Function_ActivateBadge, LVar0)
                    EndIf
                    Call(GetActorVar, ACTOR_SELF, 4, LVar0)
                    Call(SetActorVar, ACTOR_SELF, 4, -1)
                    Call(RemoveItemEntity, LVar0)
            EndSwitch
            Call(SetActorVar, ACTOR_SELF, 2, 0)
            Call(SetActorVar, ACTOR_SELF, 3, 0)
            Call(RemoveActor, LVarA)
    EndSwitch
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetPartOffset, ACTOR_SELF, 2, 0, LVar3, 0)
    Add(LVar1, LVar3)
    Call(SetPartPos, ACTOR_SELF, 2, 0, LVar1, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_pit_part_6_imp_14_SpearGuy_Script_SummonBackup_14 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(UseBattleCamPreset, 1)
    Call(SetAnimation, ACTOR_SELF, 2, 0x420005)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Thread
        Wait(5)
        Call(PlaySoundAtActor, ACTOR_SELF, 762)
        Wait(15)
        Call(PlaySoundAtActor, ACTOR_SELF, 763)
    EndThread
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 10)
    Call(SetAnimation, ACTOR_SELF, 2, 0x420005)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x420010)
    Wait(25)
    Thread
        Wait(5)
        Call(PlaySoundAtActor, ACTOR_SELF, 762)
        Wait(15)
        Call(PlaySoundAtActor, ACTOR_SELF, 763)
    EndThread
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Call(SetAnimation, ACTOR_SELF, 2, 0x420005)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x420010)
    Wait(30)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 10)
    Call(SetAnimation, ACTOR_SELF, 2, 0x420005)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 15)
    Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8301)
    Call(SetAnimation, ACTOR_SELF, 2, 0x42000E)
    Wait(20)
    Call(GetOriginalActorType, ACTOR_SELF, LVar0)
    Call(CreateHomeTargetList, 0x8004)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar1, LVar2)
    Call(GetOriginalActorType, LVar1, LVar2)
    IfEq(LVar0, LVar2)
        Call(SetAnimation, LVar1, 2, 0x420004)
        Call(GetIndexFromHome, LVar1, LVar3)
        IfLt(LVarA, LVar3)
            Call(GetActorVar, LVar1, 0, LVar4)
            IfEq(LVar4, 0)
                Call(SetActorVar, LVar1, 0, 1)
                Call(SetIdleAnimations, LVar1, 2, Ref(TTYD64_jan_spear_guy_SpearUpwardAnims))
                Call(SetPartEventFlags, LVar1, 2, 16)
                Call(SetAnimation, LVar1, 2, 0x420003)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar1)
    IfNe(LVar1, -1)
        Goto(0)
    EndIf
    Set(LFlag0, 0)
    Call(CreateHomeTargetList, 0x8004)
    Call(InitTargetIterator)
    Label(1)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    IfLt(LVar1, LVarA)
        Set(LFlag0, 1)
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(1)
    EndIf
    IfEq(LFlag0, 0)
        Call(SummonEnemy, Ref(TTYD64_pit_part_6_imp_14_SpearGuy_SpecialFormation_8021A8C0_14), 0)
    Else
        Call(SummonEnemy, Ref(TTYD64_pit_part_6_imp_14_SpearGuy_SpecialFormation_8021A8DC_14), 0)
    EndIf
    Set(LVarB, LVar0)
    Call(UseBattleCamPreset, 2)
    Call(SetAnimation, LVarB, 2, 0x420010)
    Call(SetGoalToIndex, LVarB, LVarA)
    Call(GetGoalPos, LVarB, LVar0, LVar1, LVar2)
    Add(LVar0, 220)
    Call(SetActorPos, LVarB, LVar0, 0, 0)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Thread
        Call(PlaySoundAtActor, ACTOR_SELF, 762)
        Wait(15)
        Call(PlaySoundAtActor, ACTOR_SELF, 762)
        Wait(15)
        Call(PlaySoundAtActor, ACTOR_SELF, 763)
        Wait(15)
        Call(PlaySoundAtActor, ACTOR_SELF, 763)
        Wait(15)
    EndThread
    Call(SetActorSpeed, LVarB, Float(4.0))
    Call(RunToGoal, LVarB, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(PlaySoundAtActor, ACTOR_SELF, 8301)
    Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
    Add(LVar1, 15)
    Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(SetAnimation, LVarB, 2, 0x42000E)
    Wait(20)
    IfEq(LFlag0, 0)
        Call(SetAnimation, LVarB, 2, 0x420004)
    Else
        Call(SetAnimation, LVarB, 2, 0x420003)
    EndIf
    Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
    Call(ForceHomePos, LVarB, LVar0, LVar1, LVar2)
    Call(HPBarToHome, LVarB)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetActorVar, LVarB, 1, 1)
        CaseEq(1)
            Call(SetActorVar, LVarB, 1, 2)
    EndSwitch
    Call(SetActorVar, ACTOR_SELF, 1, 3)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_BadgeBandit_Script_HandleEvent_8021DF88_0A = {
    UseArray(Ref(b_area_sbk_bandit_DropCoinScript))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            ExecGetTID(TTYD64_imp_BadgeBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320109)
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
            ExecGetTID(TTYD64_imp_BadgeBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320109)
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
            ExecGetTID(TTYD64_imp_BadgeBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x32010A)
            SetConst(LVar2, 0x32010B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        CaseEq(36)
            ExecGetTID(TTYD64_imp_BadgeBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x32010A)
            SetConst(LVar2, 0x32010B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x32010B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            ExecGetTID(TTYD64_imp_BadgeBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320109)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        CaseEq(33)
            ExecGetTID(TTYD64_imp_BadgeBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320109)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320109)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320109)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320109)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320107)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320109)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320109)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar1, 0x320101)
                CaseEq(1)
                    SetConst(LVar1, 0x320102)
            EndSwitch
            SetConst(LVar0, 1)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseOrEq(32)
        CaseOrEq(37)
            ExecGetTID(TTYD64_imp_BadgeBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320109)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320109)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        EndCaseGroup
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320101)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            ExecGetTID(TTYD64_imp_BadgeBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320107)
            SetConst(LVar2, 0x320109)
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
            ExecGetTID(TTYD64_imp_BadgeBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320109)
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
            SetConst(LVar1, 0x320109)
            SetConst(LVar2, 0x40000)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x320101)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_BadgeBandit_Script_TakeTurn_8021E900_0A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorYaw, ACTOR_SELF, 180)
        Call(SetAnimation, ACTOR_SELF, 1, 0x320108)
        Wait(30)
        Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
        Call(SetGoalPos, ACTOR_SELF, 300, 0, 0)
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(GetActorVar, ACTOR_SELF, 2, LVar0)
        IfEq(LVar0, 2)
            Call(SetActorVar, ACTOR_SELF, 2, 0)
            Call(GetActorVar, ACTOR_SELF, 4, LVar0)
            Call(SetActorVar, ACTOR_SELF, 4, -1)
            Call(RemoveItemEntity, LVar0)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Call(TTYD64_Function_AddBadgeToSoldInventory, LVar0)
        EndIf
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x320107)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
        Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x320101)
        Wait(6)
    EndIf
    Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x320105)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x32010D)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x320107)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320101)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x32010D)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(GetOwnerTarget, LVar3, 0)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 5, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 60)
                ExecWait(TTYD64_imp_BadgeBandit_Script_Steal_Coin)
            Else
                Call(TTYD64_Function_GetPlayerBadgesAmount, LVar0)
                IfEq(LVar0, 0)
                    ExecWait(TTYD64_imp_BadgeBandit_Script_Steal_Coin)
                Else
                    ExecWait(TTYD64_imp_BadgeBandit_Script_Steal_Badge)
                EndIf
            EndIf
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_BadgeBandit_Script_Steal_Badge = {
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
    Call(TTYD64_Function_GetPlayerBadgesAmount, LVar1)
    Sub(LVar1, 1)
    Call(RandInt, LVar1, LVar1)
    Set(LVar3, -0x7FEF0CBC)
    Set(LVar2, 2)
    Mul(LVar2, LVar1)
    Add(LVar3, LVar2)
    Call(TTYD64_BattlesNew_ReadN64PlayerBadge, LVar3, LVar1)
    Call(SetActorVar, ACTOR_SELF, 1, LVar1)
    Set(LVar0, 2)
    Label(10)
    Switch(LVar0)
        CaseEq(0)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320101)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320107)
        CaseEq(1)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x32010E)
            Wait(20)
            Call(PlaySoundAtActor, ACTOR_SELF, 8387)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320110)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320107)
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
            Add(LVarA, 30)
            Set(LVarB, 0)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Call(TTYD64_imp_BadgeBandit_Function_RemoveAndUnequipBadge, LVar0, LVar1)
            IfEq(LVar1, 1)
                Call(SetActorVar, ACTOR_SELF, 3, 1)
            EndIf
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Call(MakeItemEntity, LVar0, 0, -1000, 0, 1, 0)
            Call(SetActorVar, ACTOR_SELF, 4, LVar0)
            Thread
                Call(SetPartFlagBits, ACTOR_SELF, 2, 0x100000, 1)
                Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
                Call(GetOwnerTarget, LVar3, 0)
                Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
                Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(1.0))
                Add(LVarB, 30)
                Call(JumpPartTo, ACTOR_SELF, 2, LVarA, LVarB, LVarC, 22, 1)
                Call(SetPartFlagBits, ACTOR_SELF, 2, 0x100000, 0)
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_BadgeBandit_IdleAnimations_8021D55C_0A))
            Call(SetAnimation, ACTOR_SELF, 1, 0x32010E)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(SetActorVar, ACTOR_SELF, 2, 2)
            Wait(7)
            Call(SetAnimation, ACTOR_SELF, 1, 0x32010F)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320108)
    EndSwitch
    Call(UseBattleCamPreset, 2)
    Call(YieldTurn)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_BadgeBandit_Script_Steal_Coin = {
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x320101)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320107)
        CaseEq(1)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x32010E)
            Wait(20)
            Call(PlaySoundAtActor, ACTOR_SELF, 8387)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320110)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320107)
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
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_BadgeBandit_IdleAnimations_8021D55C_0A))
            Call(SetAnimation, ACTOR_SELF, 1, 0x32010E)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
            Wait(7)
            Call(SetAnimation, ACTOR_SELF, 1, 0x32010F)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320108)
    EndSwitch
    Call(UseBattleCamPreset, 2)
    Call(YieldTurn)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_pit_part_6_imp_14_JungleFuzzy_Script_Divide_14 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 330)
    Call(SetBattleCamOffsetY, 30)
    Call(MoveBattleCamOver, 20)
    Wait(20)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(UseBattleCamPreset, 1)
    Thread
        Wait(30)
        Call(PlaySoundAtActor, ACTOR_SELF, 8302)
        Wait(30)
        Loop(4)
            Call(PlaySoundAtActor, ACTOR_SELF, 8303)
            Wait(11)
        EndLoop
        Call(PlaySoundAtActor, ACTOR_SELF, 8304)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B030D)
    Wait(130)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0302)
    Call(SummonEnemy, Ref(TTYD64_pit_part_6_imp_14_JungleFuzzy_SpecialFormation_8022180C_14), 0)
    Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Call(SetActorPos, LVar0, LVar1, LVar2, LVar3)
    Call(SetGoalToIndex, LVar0, LVarA)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x2B0302)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
        Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
        Call(SetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
        Call(JumpToGoal, ACTOR_SELF, 14, 0, 1, 0)
    EndThread
    Wait(1)
    Call(SetAnimation, LVar0, 1, 0x2B0302)
    Call(SetActorJumpGravity, LVar0, Float(1.400390625))
    Call(JumpToGoal, LVar0, 14, 0, 1, 0)
    Call(GetActorPos, LVar0, LVar1, LVar2, LVar3)
    Call(ForceHomePos, LVar0, LVar1, LVar2, LVar3)
    Call(HPBarToHome, LVar0)
    Call(SetAnimation, LVar0, 1, 0x2B0301)
    Call(GetActorVar, ACTOR_SELF, 0, LVar1)
    Switch(LVar1)
        CaseEq(0)
            Call(SetActorVar, LVar0, 0, 1)
        CaseEq(1)
            Call(SetActorVar, LVar0, 0, 2)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_pit_part_6_imp_14_SpearGuy_Script_TakeTurn_8021BCB4_14 = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_jan_spear_guy_EVS_Attack_SpearStab)
        ExecWait(TTYD64_jan_spear_guy_EVS_SwitchSpearStance)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(1)
            ExecWait(b_area_jan_spear_guy_EVS_GetAvailableColumn)
            IfEq(LVarA, -1)
                ExecWait(TTYD64_jan_spear_guy_EVS_Attack_SpearStab)
                ExecWait(TTYD64_jan_spear_guy_EVS_SwitchSpearStance)
                Return
            EndIf
            ExecWait(b_area_jan_spear_guy_EVS_CountActiveSummoners)
            Switch(LVar9)
                CaseEq(1)
                    Call(RandInt, 1000, LVar0)
                    IfLt(LVar0, 300)
                        ExecWait(TTYD64_pit_part_6_imp_14_SpearGuy_Script_SummonBackup_14)
                        Return
                    EndIf
                CaseEq(2)
                    Call(RandInt, 1000, LVar0)
                    IfLt(LVar0, 150)
                        ExecWait(TTYD64_pit_part_6_imp_14_SpearGuy_Script_SummonBackup_14)
                        Return
                    EndIf
                CaseEq(3)
                    Call(RandInt, 1000, LVar0)
                    IfLt(LVar0, 100)
                        ExecWait(TTYD64_pit_part_6_imp_14_SpearGuy_Script_SummonBackup_14)
                        Return
                    EndIf
            EndSwitch
            ExecWait(TTYD64_jan_spear_guy_EVS_Attack_SpearStab)
            ExecWait(TTYD64_jan_spear_guy_EVS_SwitchSpearStance)
        EndCaseGroup
        CaseEq(2)
            Call(CreateHomeTargetList, 0x8002)
            Call(GetTargetListLength, LVar0)
            IfEq(LVar0, 1)
                ExecWait(TTYD64_jan_spear_guy_EVS_Attack_ThrowSpear)
                Return
            EndIf
            ExecWait(TTYD64_jan_spear_guy_EVS_Attack_SpearStab)
            ExecWait(TTYD64_jan_spear_guy_EVS_SwitchSpearStance)
        CaseEq(3)
            ExecWait(TTYD64_jan_spear_guy_EVS_Attack_ThrowSpear)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_pit_part_6_imp_14_JungleFuzzy_Script_TakeTurn_80221628_14 = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_jan_jungle_fuzzy_EVS_Attack_Leech)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 2)
        ExecWait(TTYD64_jan_jungle_fuzzy_EVS_Attack_Leech)
        Return
    EndIf
    ExecWait(b_area_jan_jungle_fuzzy_EVS_GetAvailableColumn)
    IfEq(LVarA, -1)
        ExecWait(TTYD64_jan_jungle_fuzzy_EVS_Attack_Leech)
        Return
    EndIf
    ExecWait(b_area_jan_jungle_fuzzy_EVS_CountActiveSummoners)
    Switch(LVar9)
        CaseEq(1)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 400)
                ExecWait(TTYD64_pit_part_6_imp_14_JungleFuzzy_Script_Divide_14)
                Return
            EndIf
        CaseEq(2)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 150)
                ExecWait(TTYD64_pit_part_6_imp_14_JungleFuzzy_Script_Divide_14)
                Return
            EndIf
        CaseEq(3)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 70)
                ExecWait(TTYD64_pit_part_6_imp_14_JungleFuzzy_Script_Divide_14)
                Return
            EndIf
    EndSwitch
    ExecWait(TTYD64_jan_jungle_fuzzy_EVS_Attack_Leech)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_pit_part_6_imp_14_SpearGuy_Script_Init_80218980_14 = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_jan_spear_guy_EVS_UpdateSpearStance)
            Call(SetAnimation, ACTOR_SELF, 2, 0x420004)
        CaseEq(1)
            ExecWait(TTYD64_jan_spear_guy_EVS_UpdateSpearStance)
            Call(SetPartEventFlags, ACTOR_SELF, 2, 16)
            Call(SetAnimation, ACTOR_SELF, 2, 0x420003)
    EndSwitch
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_pit_part_6_imp_14_SpearGuy_Script_TakeTurn_8021BCB4_14))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_jan_spear_guy_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(TTYD64_jan_spear_guy_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(GetEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseEq(2)
        CaseOrEq(4)
        CaseOrEq(6)
            Call(SetPartEventBits, ACTOR_SELF, 2, 0x10000, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_jan_spear_guy_SpearUpwardAnims))
            Call(SetAnimation, ACTOR_SELF, 2, 0x420003)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

Battle TTYD64_pit_part_6_FormationTable[] = {
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_6_Formation_Pit51_56_1,
      .stage = &TTYD64_pit_part_6_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_6_Formation_Pit51_56_2,
      .stage = &TTYD64_pit_part_6_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_6_Formation_Pit51_56_3,
      .stage = &TTYD64_pit_part_6_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_6_Formation_Pit52_57_1,
      .stage = &TTYD64_pit_part_6_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_6_Formation_Pit52_57_2,
      .stage = &TTYD64_pit_part_6_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_6_Formation_Pit52_57_3,
      .stage = &TTYD64_pit_part_6_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_6_Formation_Pit53_58_1,
      .stage = &TTYD64_pit_part_6_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_6_Formation_Pit53_58_2,
      .stage = &TTYD64_pit_part_6_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_6_Formation_Pit53_58_3,
      .stage = &TTYD64_pit_part_6_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_6_Formation_Pit54_59_1,
      .stage = &TTYD64_pit_part_6_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_6_Formation_Pit54_59_2,
      .stage = &TTYD64_pit_part_6_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_6_Formation_Pit54_59_3,
      .stage = &TTYD64_pit_part_6_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_6_Formation_Pit55_1,
      .stage = &TTYD64_pit_part_6_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_6_Formation_Pit55_2,
      .stage = &TTYD64_pit_part_6_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_6_Formation_Pit55_3,
      .stage = &TTYD64_pit_part_6_Stage_Pit1,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_imp_BadgeBandit_Script_Init_8021D750_0A = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_BadgeBandit_Script_TakeTurn_8021E900_0A))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sbk_bandit_EVS_Dummy))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_BadgeBandit_Script_HandleEvent_8021DF88_0A))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, -1)
    Thread
        Call(TTYD64_imp_BadgeBandit_Function_UpdateBadgePos)
    EndThread
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_pit_part_6_Script_BeforeBattle_Pit = {
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

s32 TTYD64_imp_BadgeBandit_StatusTable_8021D5C0_0A[] = {
    1,  0, 2,  0, 6,  80, 9,  100, 7,  50, 4,  50, 3,  50, 11, 30, 5,  70, 10, 90, 8, 70,
    31, 0, 32, 0, 37, 0,  34, 0,   36, 0,  35, 0,  33, 0,  38, 1,  39, 0,  41, 0,  0,
};

FormationRow TTYD64_pit_part_6_Formation_Pit52_57_3[] = {
    { .actor = &TTYD64_pit_part_6_imp_14_JungleFuzzy_14_JungleFuzzy,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_pit_part_6_imp_14_JungleFuzzy_14_JungleFuzzy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_pit_part_6_imp_14_JungleFuzzy_14_JungleFuzzy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_pit_part_6_imp_14_JungleFuzzy_14_JungleFuzzy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
};

FormationRow TTYD64_pit_part_6_Formation_Pit55_3[] = {
    { .actor = &TTYD64_pit_part_6_imp_16_LavaBubble_16_LavaBubble,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_pit_part_6_imp_16_LavaBubble_16_LavaBubble,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_pit_part_6_imp_16_LavaBubble_16_LavaBubble,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_pit_part_6_imp_16_LavaBubble_16_LavaBubble,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
};

FormationRow TTYD64_pit_part_6_Formation_Pit53_58_3[] = {
    { .actor = &TTYD64_pit_part_6_imp_14_SpearGuy_14_SpearGuy,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_pit_part_6_imp_14_SpearGuy_14_SpearGuy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_pit_part_6_imp_14_SpearGuy_14_SpearGuy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_pit_part_6_imp_14_SpearGuy_14_SpearGuy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
};

// clang-format off
EvtScript TTYD64_pit_part_6_imp_14_JungleFuzzy_Script_Init_8021EB28_14 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_pit_part_6_imp_14_JungleFuzzy_Script_TakeTurn_80221628_14))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_jan_jungle_fuzzy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_jan_jungle_fuzzy_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pit_part_6_Formation_Pit52_57_2[] = {
    { .actor = &TTYD64_pit_part_6_imp_14_JungleFuzzy_14_JungleFuzzy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_pit_part_6_imp_14_SpearGuy_14_SpearGuy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_pit_part_6_imp_14_JungleFuzzy_14_JungleFuzzy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
};

FormationRow TTYD64_pit_part_6_Formation_Pit55_2[] = {
    { .actor = &TTYD64_pit_part_6_imp_16_LavaBubble_16_LavaBubble,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_pit_part_6_imp_15_PutridPiranha_15_PutridPiranha,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_pit_part_6_imp_15_PutridPiranha_15_PutridPiranha,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
};

FormationRow TTYD64_pit_part_6_Formation_Pit55_1[] = {
    { .actor = &TTYD64_pit_part_6_imp_16_LavaBubble_16_LavaBubble,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
    { .actor = &TTYD64_pit_part_6_imp_14_SpearGuy_14_SpearGuy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_pit_part_6_imp_14_SpearGuy_14_SpearGuy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
};

FormationRow TTYD64_pit_part_6_Formation_Pit51_56_2[] = {
    { .actor = &TTYD64_imp_BadgeBandit_BadgeBandit,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BADGEBANDIT },
    { .actor = &TTYD64_imp_BadgeBandit_BadgeBandit,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BADGEBANDIT },
    { .actor = &TTYD64_pit_part_6_imp_14_JungleFuzzy_14_JungleFuzzy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
};

FormationRow TTYD64_pit_part_6_Formation_Pit54_59_1[] = {
    { .actor = &TTYD64_pit_part_6_imp_15_PutridPiranha_15_PutridPiranha,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_pit_part_6_imp_14_SpearGuy_14_SpearGuy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_pit_part_6_imp_15_PutridPiranha_15_PutridPiranha,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
};

FormationRow TTYD64_pit_part_6_Formation_Pit51_56_3[] = {
    { .actor = &TTYD64_imp_BadgeBandit_BadgeBandit,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BADGEBANDIT },
    { .actor = &TTYD64_imp_BadgeBandit_BadgeBandit,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BADGEBANDIT },
    { .actor = &TTYD64_imp_BadgeBandit_BadgeBandit,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BADGEBANDIT },
};

FormationRow TTYD64_pit_part_6_Formation_Pit54_59_3[] = {
    { .actor = &TTYD64_pit_part_6_imp_15_PutridPiranha_15_PutridPiranha,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_pit_part_6_imp_15_PutridPiranha_15_PutridPiranha,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_pit_part_6_imp_15_PutridPiranha_15_PutridPiranha,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
};

FormationRow TTYD64_pit_part_6_Formation_Pit51_56_1[] = {
    { .actor = &TTYD64_imp_BadgeBandit_BadgeBandit,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BADGEBANDIT },
    { .actor = &TTYD64_imp_BadgeBandit_BadgeBandit,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BADGEBANDIT },
    { .actor = &TTYD64_pit_part_6_imp_14_SpearGuy_14_SpearGuy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
};

FormationRow TTYD64_pit_part_6_Formation_Pit54_59_2[] = {
    { .actor = &TTYD64_pit_part_6_imp_15_PutridPiranha_15_PutridPiranha,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_pit_part_6_imp_14_JungleFuzzy_14_JungleFuzzy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_pit_part_6_imp_14_JungleFuzzy_14_JungleFuzzy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
};

FormationRow TTYD64_pit_part_6_Formation_Pit53_58_1[] = {
    { .actor = &TTYD64_pit_part_6_imp_14_SpearGuy_14_SpearGuy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_imp_BadgeBandit_BadgeBandit,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BADGEBANDIT },
    { .actor = &TTYD64_pit_part_6_imp_14_SpearGuy_14_SpearGuy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
};

FormationRow TTYD64_pit_part_6_Formation_Pit53_58_2[] = {
    { .actor = &TTYD64_pit_part_6_imp_14_SpearGuy_14_SpearGuy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_pit_part_6_imp_14_SpearGuy_14_SpearGuy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_pit_part_6_imp_15_PutridPiranha_15_PutridPiranha,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
};

s32 TTYD64_imp_BadgeBandit_IdleAnimations_8021D55C_0A[] = {
    1,  0x320102, 7, 0x320104, 6, 0x320110, 9, 0x320102, 8, 0x320104,
    11, 0x320102, 5, 0x320104, 4, 0x320111, 3, 0x320111, 0,
};

s32 TTYD64_imp_BadgeBandit_IdleAnimations_8021D510_0A[] = {
    1,  0x320101, 7, 0x320100, 6, 0x320110, 9, 0x320101, 8, 0x320100,
    11, 0x320101, 5, 0x320100, 4, 0x320111, 3, 0x320111, 0,
};

ActorPartBlueprint TTYD64_imp_BadgeBandit_PartsTable_8021D66C_0A[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 28 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_BadgeBandit_IdleAnimations_8021D510_0A,
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

FormationRow TTYD64_pit_part_6_Formation_Pit52_57_1[] = {
    { .actor = &TTYD64_pit_part_6_imp_14_JungleFuzzy_14_JungleFuzzy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_pit_part_6_imp_16_LavaBubble_16_LavaBubble,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAVABUBBLE },
};

ActorBlueprint TTYD64_pit_part_6_imp_14_JungleFuzzy_14_JungleFuzzy = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x29,
    .level = 16,
    .partCount = 1,
    .partsData = TTYD64_jan_jungle_fuzzy_ActorParts,
    .initScript = &TTYD64_pit_part_6_imp_14_JungleFuzzy_Script_Init_8021EB28_14,
    .statusTable = TTYD64_jan_jungle_fuzzy_StatusTable,
    .escapeChance = 30,
    .airLiftChance = 85,
    .hurricaneChance = 80,
    .spookChance = 75,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 33, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_pit_part_6_imp_15_PutridPiranha_15_PutridPiranha = {
    .flags = 0x0,
    .maxHP = 12,
    .type = 0x2D,
    .level = 17,
    .partCount = 1,
    .partsData = TTYD64_jan2_putrid_piranha_ActorParts,
    .initScript = &TTYD64_jan2_putrid_piranha_EVS_Init,
    .statusTable = b_area_jan2_putrid_piranha_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 20,
    .hurricaneChance = 20,
    .spookChance = 30,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 1,
    .size = { 60, 52 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -22, 32 },
    .statusTextOffset = { 1, 44 },
};

Stage TTYD64_pit_part_6_Stage_Pit1 = {
    .texture = "tik_tex",
    .shape = "pit_bt01_shape",
    .hit = "pit_bt01_hit",
    .preBattle = &TTYD64_pit_part_6_Script_BeforeBattle_Pit,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

Stage TTYD64_pit_part_6_Stage_Pit2 = {
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

ActorBlueprint TTYD64_pit_part_6_imp_14_SpearGuy_14_SpearGuy = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x2A,
    .level = 16,
    .partCount = 4,
    .partsData = TTYD64_jan_spear_guy_ActorParts,
    .initScript = &TTYD64_pit_part_6_imp_14_SpearGuy_Script_Init_80218980_14,
    .statusTable = TTYD64_jan_spear_guy_SpearGuyStatusTable,
    .escapeChance = 50,
    .airLiftChance = 85,
    .hurricaneChance = 80,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 2,
    .size = { 24, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_pit_part_6_imp_14_JungleFuzzy_JungleFuzzy_14 = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x29,
    .level = 16,
    .partCount = 1,
    .partsData = TTYD64_jan_jungle_fuzzy_ActorParts,
    .initScript = &TTYD64_pit_part_6_imp_14_JungleFuzzy_Script_Init_8021EB28_14,
    .statusTable = TTYD64_jan_jungle_fuzzy_StatusTable,
    .escapeChance = 30,
    .airLiftChance = 85,
    .hurricaneChance = 80,
    .spookChance = 75,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 33, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_BadgeBandit_BadgeBandit = {
    .flags = 0x0,
    .maxHP = 12,
    .type = 0x5C,
    .level = 20,
    .partCount = 2,
    .partsData = TTYD64_imp_BadgeBandit_PartsTable_8021D66C_0A,
    .initScript = &TTYD64_imp_BadgeBandit_Script_Init_8021D750_0A,
    .statusTable = TTYD64_imp_BadgeBandit_StatusTable_8021D5C0_0A,
    .escapeChance = 40,
    .airLiftChance = 60,
    .hurricaneChance = 60,
    .spookChance = 70,
    .upAndAwayChance = 60,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 1,
    .size = { 26, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 25 },
    .statusTextOffset = { 10, 25 },
};

ActorBlueprint TTYD64_pit_part_6_imp_14_SpearGuy_SpearGuy_14 = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x2A,
    .level = 16,
    .partCount = 4,
    .partsData = TTYD64_jan_spear_guy_ActorParts,
    .initScript = &TTYD64_pit_part_6_imp_14_SpearGuy_Script_Init_80218980_14,
    .statusTable = TTYD64_jan_spear_guy_SpearGuyStatusTable,
    .escapeChance = 50,
    .airLiftChance = 85,
    .hurricaneChance = 80,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 2,
    .size = { 24, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_BadgeBandit_BanditB_0A = {
    .flags = 0x600000,
    .maxHP = 5,
    .type = 0x13,
    .level = 9,
    .partCount = 1,
    .partsData = b_area_sbk_bandit_CoinParts,
    .initScript = &b_area_sbk_bandit_EVS_Init_Coin,
    .statusTable = TTYD64_imp_BadgeBandit_StatusTable_8021D5C0_0A,
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

ActorBlueprint TTYD64_pit_part_6_imp_16_LavaBubble_16_LavaBubble = {
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

FormationRow TTYD64_pit_part_6_imp_14_SpearGuy_SpecialFormation_8021A8DC_14[] = {
    { .actor = &TTYD64_pit_part_6_imp_14_SpearGuy_SpearGuy_14,
      .home = { .vec = &b_area_jan_spear_guy_SummonPos },
      .priority = 100,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_BadgeBandit_SpecialFormation_8021D734_0A[] = {
    { .actor = &TTYD64_imp_BadgeBandit_BanditB_0A,
      .home = { .vec = &b_area_sbk_bandit_CoinPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pit_part_6_imp_14_JungleFuzzy_SpecialFormation_8022180C_14[] = {
    { .actor = &TTYD64_pit_part_6_imp_14_JungleFuzzy_JungleFuzzy_14,
      .home = { .vec = &b_area_jan_jungle_fuzzy_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pit_part_6_imp_14_SpearGuy_SpecialFormation_8021A8C0_14[] = {
    { .actor = &TTYD64_pit_part_6_imp_14_SpearGuy_SpearGuy_14,
      .home = { .vec = &b_area_jan_spear_guy_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

StageListRow TTYD64_pit_part_6_StageTable[] = {
    { .name = "pit_01", .stage = &TTYD64_pit_part_6_Stage_Pit1 },
    { .name = "pit_12", .stage = &TTYD64_pit_part_6_Stage_Pit2 },
    {},
};

void TTYD64_InstallBattles_pit_part_6(void) {
    Mod_SetBattleList("TTYD64", 0x35, TTYD64_pit_part_6_FormationTable);
    Mod_SetStageList("TTYD64", 0x35, TTYD64_pit_part_6_StageTable);
}
