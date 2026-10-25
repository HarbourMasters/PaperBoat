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

API_CALLABLE(TTYD64_imp_BigBandit_Function_GetAmountOfItems);
API_CALLABLE(TTYD64_imp_BigBandit_Function_GetFreeItemSlots);
API_CALLABLE(TTYD64_imp_BigBandit_Function_GetItemByIndex);
API_CALLABLE(TTYD64_imp_BigBandit_Function_UpdateItemPos);
API_CALLABLE(TTYD64_imp_FlowerFuzzy_Function_UpdateBGColor_Darker);
API_CALLABLE(b_area_omo2_general_guy_FadeBackgroundLighten);
API_CALLABLE(b_area_omo3_fuzzy_SpawnDrainHealthContinueFX);
API_CALLABLE(b_area_omo3_fuzzy_SpawnDrainHealthStartFX);
API_CALLABLE(battle_item_thunder_bolt_SpawnLightningFX);
extern s32 b_area_kmr_part_1_goomba_StatusTable[];
extern EvtScript b_area_kmr_part_1_kmr_02_EVS_PostBattle;
extern EvtScript b_area_kmr_part_3_kpa_13_EVS_PreBattle;
extern Vec3i b_area_mac_Lee_SummonPos;
extern EvtScript b_area_mim_forest_fuzzy_EVS_CountSummoners;
extern EvtScript b_area_mim_forest_fuzzy_EVS_GetAvailableSpawnPos;
extern EvtScript b_area_mim_forest_fuzzy_EVS_Idle;
extern Vec3i b_area_mim_forest_fuzzy_SummonPos;
extern s32 b_area_nok_fuzzy_StatusTable[];
extern s32 b_area_omo3_fuzzy_DefenseTable[];
extern EvtScript b_area_omo3_fuzzy_EVS_Idle;
extern s32 b_area_omo3_fuzzy_StatusTable[];
extern s32 b_area_sbk_bandit_CoinAnims[];
extern FormationRow b_area_sbk_bandit_CoinFormation[];
extern ActorPartBlueprint b_area_sbk_bandit_CoinParts[];
extern s32 b_area_sbk_bandit_DefenseTable[];
extern u8 b_area_sbk_bandit_DropCoinScript[];
extern EvtScript b_area_sbk_bandit_EVS_Dummy;
extern EvtScript b_area_sbk_bandit_EVS_Init_Coin;
extern s32 b_area_sbk_bandit_StatusTable[];
extern EvtScript b_area_sbk_pokey_EVS_CountSummonerPokeys;
extern EvtScript b_area_sbk_pokey_EVS_FindValidSummonPosition;
extern EvtScript b_area_sbk_pokey_EVS_Idle;
extern Vec3i b_area_sbk_pokey_SummonPos;
API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddCoin);
API_CALLABLE(AddGoalPos);
API_CALLABLE(AddItem);
API_CALLABLE(AddVectorPolar);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(EnableActorBlur);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnableModel);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyPartTo);
API_CALLABLE(ForceHomePos);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetItemPower);
API_CALLABLE(GetLastDamage);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartOffset);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HideHealthBar);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActor);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(RemoveItem);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(ResetAllActorSounds);
API_CALLABLE(RunToGoal);
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
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetEnemyHP);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTargetActor);
API_CALLABLE(ShakeCam);
API_CALLABLE(StartRumble);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
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
extern ActorBlueprint TTYD64_imp_DarkPuff_DarkPuff;
extern s32 TTYD64_imp_DarkPuff_IdleAnimations_802225A0_3B[];
extern ActorPartBlueprint TTYD64_imp_DarkPuff_PartsTable_802226A4_3B[];
extern EvtScript TTYD64_imp_DarkPuff_Script_80222820_3B;
extern EvtScript TTYD64_imp_DarkPuff_Script_DarkPuff_Static;
extern EvtScript TTYD64_imp_DarkPuff_Script_DarkPuff_TackleAttack;
extern EvtScript TTYD64_imp_DarkPuff_Script_DarkPuff_ThunderAttack;
extern EvtScript TTYD64_imp_DarkPuff_Script_HandleEvent_80222898_3B;
extern EvtScript TTYD64_imp_DarkPuff_Script_Idle_8022273C_3B;
extern EvtScript TTYD64_imp_DarkPuff_Script_Init_802226F0_3B;
extern EvtScript TTYD64_imp_DarkPuff_Script_TakeTurn_80222DE8_3B;
extern s32 TTYD64_imp_DarkPuff_StatusTable_802225F8_3B[];
extern s32 TTYD64_imp_PalePiranha_IdleAnimations_8021D330_0D[];
extern ActorBlueprint TTYD64_imp_PalePiranha_PalePiranha;
extern ActorPartBlueprint TTYD64_imp_PalePiranha_PartsTable_8021D44C_0D[];
extern EvtScript TTYD64_imp_PalePiranha_Script_8021D4F4_0D;
extern EvtScript TTYD64_imp_PalePiranha_Script_HandleEvent_8021D60C_0D;
extern EvtScript TTYD64_imp_PalePiranha_Script_Init_8021D498_0D;
extern EvtScript TTYD64_imp_PalePiranha_Script_TakeTurn_8021DCD4_0D;
extern s32 TTYD64_imp_PalePiranha_StatusTable_8021D3A0_0D[];
extern ActorBlueprint TTYD64_imp_Pider_3B_Pider;
extern s32 TTYD64_imp_Pider_IdleAnimations_Pider[];
extern s32 TTYD64_imp_Pider_IdleAnimations_Rock[];
extern ActorPartBlueprint TTYD64_imp_Pider_PartsTable_Pider[];
extern EvtScript TTYD64_imp_Pider_Script_HandleEvent_Pider;
extern EvtScript TTYD64_imp_Pider_Script_Init_Pider;
extern EvtScript TTYD64_imp_Pider_Script_NextTurn_Pider;
extern EvtScript TTYD64_imp_Pider_Script_TakeTurn_Pider;
extern s32 TTYD64_imp_Pider_StatusTable_Pider[];
extern ActorPartBlueprint TTYD64_kmr_part_1_goomba_ActorParts[];
extern s32 TTYD64_kmr_part_1_goomba_DefaultAnims[];
extern EvtScript TTYD64_kmr_part_1_goomba_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_1_goomba_EVS_Idle;
extern EvtScript TTYD64_kmr_part_1_goomba_EVS_Init;
extern EvtScript TTYD64_kmr_part_1_goomba_EVS_TakeTurn;
extern s32 TTYD64_kmr_part_1_goomba_ShuffleAnims[];
extern ActorPartBlueprint TTYD64_mim_forest_fuzzy_ActorParts[];
extern s32 TTYD64_mim_forest_fuzzy_DefaultAnims[];
extern EvtScript TTYD64_mim_forest_fuzzy_EVS_Attack_Leech;
extern EvtScript TTYD64_mim_forest_fuzzy_EVS_HandleEvent;
extern s32 TTYD64_mim_forest_fuzzy_StatusTable[];
extern ActorPartBlueprint TTYD64_nok_fuzzy_ActorParts[];
extern s32 TTYD64_nok_fuzzy_DefaultAnims[];
extern EvtScript TTYD64_nok_fuzzy_EVS_HandleEvent;
extern EvtScript TTYD64_nok_fuzzy_EVS_Init_8022B3D0;
extern EvtScript TTYD64_nok_fuzzy_EVS_TakeTurn;
extern ActorPartBlueprint TTYD64_sbk_bandit_ActorParts[];
extern s32 TTYD64_sbk_bandit_DefaultAnims[];
extern EvtScript TTYD64_sbk_bandit_EVS_TakeTurn;
extern s32 TTYD64_sbk_bandit_HoldingAnims[];
extern ActorPartBlueprint TTYD64_sbk_pokey_ActorParts[];
extern EvtScript TTYD64_sbk_pokey_EVS_Attack_GroundSmash;
extern EvtScript TTYD64_sbk_pokey_EVS_Attack_SinglePartLeap;
extern EvtScript TTYD64_sbk_pokey_EVS_DecrementSize;
extern EvtScript TTYD64_sbk_pokey_EVS_HandleEvent;
extern EvtScript TTYD64_sbk_pokey_EVS_KnockPartAway;
extern EvtScript TTYD64_sbk_pokey_EVS_Pokey_Hit;
extern EvtScript TTYD64_sbk_pokey_EVS_Pokey_ScareAway;
extern EvtScript TTYD64_sbk_pokey_EVS_Pokey_SpinSmashHit;
extern s32 TTYD64_sbk_pokey_FourPartAnims[];
extern s32 TTYD64_sbk_pokey_OnePartAnims[];
extern s32 TTYD64_sbk_pokey_StatusTable[];
extern s32 TTYD64_sbk_pokey_ThreePartAnims[];
extern s32 TTYD64_sbk_pokey_TwoPartAnims[];
extern EvtScript TTYD64_imp_FlowerFuzzy_Script_TakeTurn_8021FF30_12;
extern EvtScript TTYD64_tyd_part_2_imp_0A_Pokey_Script_TakeTurn_8021A018_0A;
extern EvtScript TTYD64_imp_BigBandit_Script_Bandit_GetItemBack;
extern EvtScript TTYD64_tyd_part_2_imp_0A_BanditA_Script_HandleEvent_8021DF88_0A;
extern EvtScript TTYD64_imp_BigBandit_Script_HandleEvent_8021DF88_3C;
extern EvtScript TTYD64_imp_BigBandit_Script_TakeTurn_8021E900_3C;
extern EvtScript TTYD64_tyd_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack;
extern EvtScript TTYD64_tyd_part_2_imp_0A_Pokey_Script_Pokey_SummonPokey_0A;
extern EvtScript TTYD64_imp_BigBandit_Script_Steal_Coin;
extern EvtScript TTYD64_imp_BigBandit_Script_Steal_Item;
extern EvtScript TTYD64_imp_FlowerFuzzy_Script_HandleEvent_8021F8CC_12;
extern EvtScript TTYD64_tyd_part_2_imp_0D_ForestFuzzy_Script_80218C48_0D;
extern EvtScript TTYD64_imp_FlowerFuzzy_Script_Attack_Thunder;
extern EvtScript TTYD64_tyd_part_2_imp_0D_ForestFuzzy_Script_TakeTurn_8021A61C_0D;
extern EvtScript TTYD64_tyd_part_2_imp_0A_Pokey_Script_Init_80218534_0A;
extern EvtScript TTYD64_imp_BigBandit_Script_Init_8021D750_3C;
extern s32 TTYD64_imp_BigBandit_StatusTable_8021D5C0_3C[];
extern Battle TTYD64_tyd_part_2_FormationTable[];
extern FormationRow TTYD64_tyd_part_2_Formation_00[];
extern FormationRow TTYD64_tyd_part_2_Formation_02[];
extern EvtScript TTYD64_tyd_part_2_imp_0D_ForestFuzzy_Script_Init_80218510_0D;
extern EvtScript TTYD64_tyd_part_2_imp_0A_BanditA_Script_Init_8021D750_0A;
extern FormationRow TTYD64_tyd_part_2_Formation_01[];
extern FormationRow TTYD64_tyd_part_2_Formation_04[];
extern FormationRow TTYD64_tyd_part_2_Formation_05[];
extern FormationRow TTYD64_tyd_part_2_Formation_03[];
extern EvtScript TTYD64_tyd_part_2_Script_BeforeBattle;
extern s32 TTYD64_imp_BigBandit_IdleAnimations_8021D55C_3C[];
extern s32 TTYD64_imp_FlowerFuzzy_IdleAnimations_8021F824_12[];
extern s32 TTYD64_imp_BigBandit_IdleAnimations_8021D510_3C[];
extern EvtScript TTYD64_imp_FlowerFuzzy_Script_Init_8021F870_12;
extern ActorPartBlueprint TTYD64_imp_BigBandit_PartsTable_8021D66C_3C[];
extern ActorBlueprint TTYD64_tyd_part_2_imp_0A_BanditA_0A_BanditA;
extern ActorBlueprint TTYD64_tyd_part_2_imp_0E_HyperCleft_0E_HyperCleft;
extern ActorBlueprint TTYD64_tyd_part_2_imp_0A_Pokey_Pokey_0A;
extern ActorBlueprint TTYD64_tyd_part_2_imp_05_Fuzzy_05_Fuzzy;
extern ActorBlueprint TTYD64_tyd_part_2_imp_0D_ForestFuzzy_0D_ForestFuzzy;
extern Stage TTYD64_tyd_part_2_Stage_GlitzPit;
extern Stage TTYD64_tyd_part_2_Stage_GlitzPit_Web;
extern ActorBlueprint TTYD64_tyd_part_2_imp_0A_Pokey_0A_Pokey;
extern ActorBlueprint TTYD64_tyd_part_2_imp_00_Goomba_00_Goomba;
extern ActorBlueprint TTYD64_tyd_part_2_imp_0D_ForestFuzzy_ForestFuzzy_0D;
extern ActorBlueprint TTYD64_imp_BigBandit_3C_BigBandit;
extern ActorBlueprint TTYD64_imp_BigBandit_BanditB_3C;
extern ActorBlueprint TTYD64_imp_FlowerFuzzy_3C_FlowerFuzzy;
extern ActorPartBlueprint TTYD64_imp_FlowerFuzzy_PartsTable_8021F7D8_12[];
extern FormationRow TTYD64_imp_BigBandit_SpecialFormation_8021D734_3C[];
extern FormationRow TTYD64_tyd_part_2_imp_0D_ForestFuzzy_SpecialFormation_8021A800_0D[];
extern FormationRow TTYD64_tyd_part_2_imp_0A_Pokey_SpecialFormation_8021AE10_0A[];
extern StageListRow TTYD64_tyd_part_2_StageTable[];

// clang-format off
EvtScript TTYD64_imp_FlowerFuzzy_Script_TakeTurn_8021FF30_12 = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfGe(LVar0, 4)
        ExecWait(TTYD64_imp_FlowerFuzzy_Script_Attack_Thunder)
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
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 50)
        Set(LVar1, 0)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Goto(100)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0203)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0201)
    Label(100)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0204)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0205)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 11, 0, 1, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0209)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0203)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0205)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0207)
    Wait(21)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0200)
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
    Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_5_1U, LVar5)
    IfEq(LVar5, 0)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 3, 32)
    Else
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 3, 32)
        Call(TTYD64_ReadField, TTYD64_F_GBATTLESTATUS_180_2U, LVar6)
        Call(GetOwnerTarget, LVar1, 0)
        Call(TTYD64_Heal_PlayerTeam, LVar1, LVar6)
        Set(LVar2, LVar5)
        Sub(LVar2, LVar6)
        IfLt(LVar2, 0)
            Set(LVar2, 0)
        EndIf
        IfLt(LVar5, LVar6)
            Set(LVar5, LVar6)
        EndIf
        Call(TTYD64_WriteField, TTYD64_F_GPLAYERDATA_5_1U, LVar2)
        Call(GetActorVar, ACTOR_SELF, 0, LVar1)
        Add(LVar1, LVar6)
        Call(SetActorVar, ACTOR_SELF, 0, LVar1)
        Set(LVar0, 0)
    EndIf
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0201)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            IfEq(LVar5, 0)
                Call(GetOwnerTarget, LVar0, 0)
                Call(GetLastDamage, LVar0, LVar3)
            Else
                Set(LVar3, LVar6)
            EndIf
            IfNe(LVar3, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8301)
                Call(PlaySoundAtActor, ACTOR_SELF, 532)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 10)
                Call(b_area_omo3_fuzzy_SpawnDrainHealthStartFX, LVar0, LVar1, LVar2, LVar3)
                Thread
                    Wait(15)
                    Call(PlaySoundAtActor, ACTOR_SELF, 604)
                    Call(b_area_omo3_fuzzy_SpawnDrainHealthContinueFX, LVar0, LVar1, LVar2, LVar3)
                EndThread
                Add(LVar0, 20)
                Add(LVar1, 20)
                IfEq(LVar5, 0)
                    Set(LVar4, 0)
                Else
                    Set(LVar4, 1)
                EndIf
                Call(PlayEffect_impl, 64, LVar4, LVar0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0)
                IfEq(LVar5, 0)
                    Call(GetActorHP, ACTOR_SELF, LVar0)
                    Add(LVar0, LVar3)
                    Call(SetEnemyHP, ACTOR_SELF, LVar0)
                Else
                EndIf
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0203)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            ExecWait(Ref(EVS_Enemy_HopToPos))
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0201)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_tyd_part_2_imp_0A_Pokey_Script_TakeTurn_8021A018_0A = {
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
                    ExecWait(TTYD64_tyd_part_2_imp_0A_Pokey_Script_Pokey_SummonPokey_0A)
                    Return
                EndIf
            CaseEq(2)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 200)
                    ExecWait(TTYD64_tyd_part_2_imp_0A_Pokey_Script_Pokey_SummonPokey_0A)
                    Return
                EndIf
            CaseEq(3)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 100)
                    ExecWait(TTYD64_tyd_part_2_imp_0A_Pokey_Script_Pokey_SummonPokey_0A)
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
EvtScript TTYD64_imp_BigBandit_Script_Bandit_GetItemBack = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
        CaseEq(1)
            Call(GetActorVar, ACTOR_SELF, 2, LVar9)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_BigBandit_IdleAnimations_8021D510_3C))
            Call(SetPartFlagBits, ACTOR_SELF, 2, 0x100000, 0)
            Call(SummonEnemy, Ref(TTYD64_imp_BigBandit_SpecialFormation_8021D734_3C), 0)
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
                    Call(AddItem, LVar0, 0)
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
EvtScript TTYD64_tyd_part_2_imp_0A_BanditA_Script_HandleEvent_8021DF88_0A = {
    UseArray(Ref(b_area_sbk_bandit_DropCoinScript))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            ExecGetTID(TTYD64_tyd_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_tyd_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_tyd_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_tyd_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_tyd_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_tyd_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_tyd_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_tyd_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_tyd_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
EvtScript TTYD64_imp_BigBandit_Script_HandleEvent_8021DF88_3C = {
    UseArray(Ref(b_area_sbk_bandit_DropCoinScript))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            ExecGetTID(TTYD64_imp_BigBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320209)
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
            ExecGetTID(TTYD64_imp_BigBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320209)
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
            ExecGetTID(TTYD64_imp_BigBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x32020A)
            SetConst(LVar2, 0x32020B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        CaseEq(36)
            ExecGetTID(TTYD64_imp_BigBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x32020A)
            SetConst(LVar2, 0x32020B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x32020B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            ExecGetTID(TTYD64_imp_BigBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320209)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        CaseEq(33)
            ExecGetTID(TTYD64_imp_BigBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320209)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            Loop(0)
                IsThreadRunning(ArrayVar(0), LVar0)
                IfEq(LVar0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320209)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320209)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320209)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320207)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320209)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320209)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar1, 0x320201)
                CaseEq(1)
                    SetConst(LVar1, 0x320202)
            EndSwitch
            SetConst(LVar0, 1)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseOrEq(32)
        CaseOrEq(37)
            ExecGetTID(TTYD64_imp_BigBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320209)
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
            SetConst(LVar1, 0x320209)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        EndCaseGroup
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320201)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            ExecGetTID(TTYD64_imp_BigBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320207)
            SetConst(LVar2, 0x320209)
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
            ExecGetTID(TTYD64_imp_BigBandit_Script_Bandit_GetItemBack, ArrayVar(0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x320209)
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
            SetConst(LVar1, 0x320209)
            SetConst(LVar2, 0x40000)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x320201)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_BigBandit_Script_TakeTurn_8021E900_3C = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorYaw, ACTOR_SELF, 180)
        Call(SetAnimation, ACTOR_SELF, 1, 0x320208)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x320207)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
        Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x320201)
        Wait(6)
    EndIf
    Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x320205)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x32020D)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x320207)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320201)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x32020D)
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
            IfLt(LVar0, 30)
                ExecWait(TTYD64_imp_BigBandit_Script_Steal_Coin)
            Else
                Call(TTYD64_imp_BigBandit_Function_GetFreeItemSlots)
                IfEq(LVar0, 0)
                    ExecWait(TTYD64_imp_BigBandit_Script_Steal_Coin)
                Else
                    ExecWait(TTYD64_imp_BigBandit_Script_Steal_Item)
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
EvtScript TTYD64_tyd_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack = {
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
EvtScript TTYD64_tyd_part_2_imp_0A_Pokey_Script_Pokey_SummonPokey_0A = {
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
    Call(SummonEnemy, Ref(TTYD64_tyd_part_2_imp_0A_Pokey_SpecialFormation_8021AE10_0A), 0)
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
EvtScript TTYD64_imp_BigBandit_Script_Steal_Coin = {
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x320201)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320207)
        CaseEq(1)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x32020E)
            Wait(20)
            Call(PlaySoundAtActor, ACTOR_SELF, 8387)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320210)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320207)
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
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_BigBandit_IdleAnimations_8021D55C_3C))
            Call(SetAnimation, ACTOR_SELF, 1, 0x32020E)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
            Wait(7)
            Call(SetAnimation, ACTOR_SELF, 1, 0x32020F)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320208)
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
EvtScript TTYD64_imp_BigBandit_Script_Steal_Item = {
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
    Call(TTYD64_imp_BigBandit_Function_GetAmountOfItems)
    Set(LVar1, LVar0)
    Sub(LVar1, 1)
    Call(RandInt, LVar1, LVar1)
    Call(TTYD64_imp_BigBandit_Function_GetItemByIndex, LVar1, LVar1)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x320201)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320207)
        CaseEq(1)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x32020E)
            Wait(20)
            Call(PlaySoundAtActor, ACTOR_SELF, 8387)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320210)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320207)
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
            Add(LVarA, 30)
            Set(LVarB, 0)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Call(RemoveItem, LVar0, 0)
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
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_BigBandit_IdleAnimations_8021D55C_3C))
            Call(SetAnimation, ACTOR_SELF, 1, 0x32020E)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(SetActorVar, ACTOR_SELF, 2, 2)
            Wait(7)
            Call(SetAnimation, ACTOR_SELF, 1, 0x32020F)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320208)
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
EvtScript TTYD64_imp_FlowerFuzzy_Script_HandleEvent_8021F8CC_12 = {
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
                SetConst(LVar1, 0x2B0213)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0208)
            EndIf
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0210)
            SetConst(LVar2, 0x2B0212)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0210)
            SetConst(LVar2, 0x2B0212)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0212)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0208)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0208)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0208)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0213)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0213)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0203)
            ExecWait(Ref(EVS_Enemy_HopHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0213)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0208)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0201)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            Call(GetLastElement, LVar0)
            IfFlag(LVar0, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0213)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0213)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0208)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0208)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0201)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0203)
            SetConst(LVar2, 0x2B0209)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0203)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0203)
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
EvtScript TTYD64_tyd_part_2_imp_0D_ForestFuzzy_Script_80218C48_0D = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B010D)
    Wait(130)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0102)
    Call(SummonEnemy, Ref(TTYD64_tyd_part_2_imp_0D_ForestFuzzy_SpecialFormation_8021A800_0D), 0)
    Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Call(SetActorPos, LVar0, LVar1, LVar2, LVar3)
    Call(SetGoalToIndex, LVar0, LVarA)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x2B0102)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
        Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
        Call(SetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
        Call(JumpToGoal, ACTOR_SELF, 14, 0, 1, 0)
    EndThread
    Wait(1)
    Call(SetAnimation, LVar0, 1, 0x2B0102)
    Call(SetActorJumpGravity, LVar0, Float(1.400390625))
    Call(JumpToGoal, LVar0, 14, 0, 1, 0)
    Call(GetActorPos, LVar0, LVar1, LVar2, LVar3)
    Call(ForceHomePos, LVar0, LVar1, LVar2, LVar3)
    Call(HPBarToHome, LVar0)
    Call(SetAnimation, LVar0, 1, 0x2B0101)
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
EvtScript TTYD64_imp_FlowerFuzzy_Script_Attack_Thunder = {
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Sub(LVar0, 4)
    Call(SetActorVar, ACTOR_SELF, 0, LVar0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    ChildThread
        Wait(5)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 20)
    EndChildThread
    Call(TTYD64_imp_FlowerFuzzy_Function_UpdateBGColor_Darker)
    Call(PlaySound, 869)
    Wait(10)
    Label(0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x18000000, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVar0, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Goto(1)
        EndCaseGroup
    EndSwitch
    Call(battle_item_thunder_bolt_SpawnLightningFX)
    Wait(5)
    Call(StartRumble, 10)
    Call(ShakeCam, 1, 0, 5, Float(1.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetItemPower, 130, LVar0, LVar1)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000020, 0, 0, 3, 32)
    Label(1)
    Wait(5)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(TTYD64_GetPartnerHP_API, LVar1)
    IfLe(LVar1, 0)
        Set(LVar0, 256)
    EndIf
    IfNe(LVar0, 256)
        Call(SetTargetActor, ACTOR_SELF, 256)
        Goto(0)
    EndIf
    Wait(30)
    Call(b_area_omo2_general_guy_FadeBackgroundLighten)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_tyd_part_2_imp_0D_ForestFuzzy_Script_TakeTurn_8021A61C_0D = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_mim_forest_fuzzy_EVS_Attack_Leech)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 2)
        ExecWait(TTYD64_mim_forest_fuzzy_EVS_Attack_Leech)
        Return
    EndIf
    ExecWait(b_area_mim_forest_fuzzy_EVS_GetAvailableSpawnPos)
    IfEq(LVarA, -1)
        ExecWait(TTYD64_mim_forest_fuzzy_EVS_Attack_Leech)
        Return
    EndIf
    ExecWait(b_area_mim_forest_fuzzy_EVS_CountSummoners)
    Switch(LVar9)
        CaseEq(1)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 300)
                ExecWait(TTYD64_tyd_part_2_imp_0D_ForestFuzzy_Script_80218C48_0D)
                Return
            EndIf
        CaseEq(2)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 150)
                ExecWait(TTYD64_tyd_part_2_imp_0D_ForestFuzzy_Script_80218C48_0D)
                Return
            EndIf
        CaseEq(3)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 100)
                ExecWait(TTYD64_tyd_part_2_imp_0D_ForestFuzzy_Script_80218C48_0D)
                Return
            EndIf
    EndSwitch
    ExecWait(TTYD64_mim_forest_fuzzy_EVS_Attack_Leech)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_tyd_part_2_imp_0A_Pokey_Script_Init_80218534_0A = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_tyd_part_2_imp_0A_Pokey_Script_TakeTurn_8021A018_0A))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sbk_pokey_EVS_Idle))
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

// clang-format off
EvtScript TTYD64_imp_BigBandit_Script_Init_8021D750_3C = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_BigBandit_Script_TakeTurn_8021E900_3C))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sbk_bandit_EVS_Dummy))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_BigBandit_Script_HandleEvent_8021DF88_3C))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, -1)
    Thread
        Call(TTYD64_imp_BigBandit_Function_UpdateItemPos)
    EndThread
    Return
    End
};
// clang-format on

s32 TTYD64_imp_BigBandit_StatusTable_8021D5C0_3C[] = {
    1,  0, 2,  0, 6,  80, 9,  100, 7,  50, 4,  50, 3,  50, 11, 30, 5,  70, 10, 90, 8, 70,
    31, 0, 32, 0, 37, 0,  34, 0,   36, 0,  35, 0,  33, 0,  38, 1,  39, 0,  41, 0,  0,
};

Battle TTYD64_tyd_part_2_FormationTable[] = {
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_tyd_part_2_Formation_00,
      .stage = &TTYD64_tyd_part_2_Stage_GlitzPit,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tyd_part_2_Formation_01,
      .stage = &TTYD64_tyd_part_2_Stage_GlitzPit,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_tyd_part_2_Formation_02,
      .stage = &TTYD64_tyd_part_2_Stage_GlitzPit,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tyd_part_2_Formation_03,
      .stage = &TTYD64_tyd_part_2_Stage_GlitzPit,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tyd_part_2_Formation_04,
      .stage = &TTYD64_tyd_part_2_Stage_GlitzPit_Web,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tyd_part_2_Formation_05,
      .stage = &TTYD64_tyd_part_2_Stage_GlitzPit,
      .onBattleStart = NULL },
    {},
};

FormationRow TTYD64_tyd_part_2_Formation_00[] = {
    { .actor = &TTYD64_tyd_part_2_imp_00_Goomba_00_Goomba,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_tyd_part_2_imp_00_Goomba_00_Goomba,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_tyd_part_2_imp_00_Goomba_00_Goomba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_tyd_part_2_imp_00_Goomba_00_Goomba,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_tyd_part_2_Formation_02[] = {
    { .actor = &TTYD64_tyd_part_2_imp_0A_BanditA_0A_BanditA,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_tyd_part_2_imp_0A_BanditA_0A_BanditA,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_BigBandit_3C_BigBandit,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_BigBandit_3C_BigBandit,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

// clang-format off
EvtScript TTYD64_tyd_part_2_imp_0D_ForestFuzzy_Script_Init_80218510_0D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_tyd_part_2_imp_0D_ForestFuzzy_Script_TakeTurn_8021A61C_0D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mim_forest_fuzzy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mim_forest_fuzzy_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_tyd_part_2_imp_0A_BanditA_Script_Init_8021D750_0A = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_sbk_bandit_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sbk_pokey_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_tyd_part_2_imp_0A_BanditA_Script_HandleEvent_8021DF88_0A))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_tyd_part_2_Formation_01[] = {
    { .actor = &TTYD64_tyd_part_2_imp_0A_Pokey_0A_Pokey,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_tyd_part_2_imp_0A_Pokey_0A_Pokey,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_tyd_part_2_imp_0A_Pokey_0A_Pokey,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_tyd_part_2_Formation_04[] = {
    { .actor = &TTYD64_imp_DarkPuff_DarkPuff,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_PalePiranha_PalePiranha,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_Pider_3B_Pider,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_tyd_part_2_Formation_05[] = {
    { .actor = &TTYD64_tyd_part_2_imp_05_Fuzzy_05_Fuzzy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_tyd_part_2_imp_0D_ForestFuzzy_0D_ForestFuzzy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_FlowerFuzzy_3C_FlowerFuzzy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_tyd_part_2_Formation_03[] = {
    { .actor = &TTYD64_tyd_part_2_imp_0E_HyperCleft_0E_HyperCleft,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_tyd_part_2_imp_0E_HyperCleft_0E_HyperCleft,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_tyd_part_2_imp_0E_HyperCleft_0E_HyperCleft,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

// clang-format off
EvtScript TTYD64_tyd_part_2_Script_BeforeBattle = {
    Call(SetSpriteShading, -1)
    Call(SetCamBGColor, 1, 0, 0, 0)
    Call(EnableModel, 59, 0)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_BigBandit_IdleAnimations_8021D55C_3C[] = {
    1,  0x320202, 7, 0x320204, 6, 0x320210, 9, 0x320202, 8, 0x320204,
    11, 0x320202, 5, 0x320204, 4, 0x320211, 3, 0x320211, 0,
};

s32 TTYD64_imp_FlowerFuzzy_IdleAnimations_8021F824_12[] = {
    1,  0x2B0201, 7, 0x2B0200, 6, 0x2B020E, 9, 0x2B0201, 8, 0x2B0200,
    11, 0x2B0201, 5, 0x2B0200, 4, 0x2B020F, 3, 0x2B020F, 0,
};

s32 TTYD64_imp_BigBandit_IdleAnimations_8021D510_3C[] = {
    1,  0x320201, 7, 0x320200, 6, 0x320210, 9, 0x320201, 8, 0x320200,
    11, 0x320201, 5, 0x320200, 4, 0x320211, 3, 0x320211, 0,
};

// clang-format off
EvtScript TTYD64_imp_FlowerFuzzy_Script_Init_8021F870_12 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_FlowerFuzzy_Script_TakeTurn_8021FF30_12))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo3_fuzzy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_FlowerFuzzy_Script_HandleEvent_8021F8CC_12))
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_imp_BigBandit_PartsTable_8021D66C_3C[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 28 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_BigBandit_IdleAnimations_8021D510_3C,
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

ActorBlueprint TTYD64_tyd_part_2_imp_0A_BanditA_0A_BanditA = {
    .flags = 0x0,
    .maxHP = 5,
    .type = 0x13,
    .level = 9,
    .partCount = 2,
    .partsData = TTYD64_sbk_bandit_ActorParts,
    .initScript = &TTYD64_tyd_part_2_imp_0A_BanditA_Script_Init_8021D750_0A,
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

ActorBlueprint TTYD64_tyd_part_2_imp_0E_HyperCleft_0E_HyperCleft = {
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

ActorBlueprint TTYD64_tyd_part_2_imp_0A_Pokey_Pokey_0A = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x14,
    .level = 9,
    .partCount = 6,
    .partsData = TTYD64_sbk_pokey_ActorParts,
    .initScript = &TTYD64_tyd_part_2_imp_0A_Pokey_Script_Init_80218534_0A,
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

ActorBlueprint TTYD64_tyd_part_2_imp_05_Fuzzy_05_Fuzzy = {
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

ActorBlueprint TTYD64_tyd_part_2_imp_0D_ForestFuzzy_0D_ForestFuzzy = {
    .flags = 0x0,
    .maxHP = 6,
    .type = 0x1A,
    .level = 11,
    .partCount = 1,
    .partsData = TTYD64_mim_forest_fuzzy_ActorParts,
    .initScript = &TTYD64_tyd_part_2_imp_0D_ForestFuzzy_Script_Init_80218510_0D,
    .statusTable = TTYD64_mim_forest_fuzzy_StatusTable,
    .escapeChance = 40,
    .airLiftChance = 90,
    .hurricaneChance = 90,
    .spookChance = 85,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 33, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

Stage TTYD64_tyd_part_2_Stage_GlitzPit = {
    .texture = "tst_tex",
    .shape = "tyd_bt04_shape",
    .hit = "tyd_bt04_hit",
    .preBattle = &TTYD64_tyd_part_2_Script_BeforeBattle,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

Stage TTYD64_tyd_part_2_Stage_GlitzPit_Web = {
    .texture = "tst_tex",
    .shape = "tyd_bt04_shape",
    .hit = "tyd_bt04_hit",
    .preBattle = &b_area_kmr_part_3_kpa_13_EVS_PreBattle,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_tyd_part_2_imp_0A_Pokey_0A_Pokey = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x14,
    .level = 9,
    .partCount = 6,
    .partsData = TTYD64_sbk_pokey_ActorParts,
    .initScript = &TTYD64_tyd_part_2_imp_0A_Pokey_Script_Init_80218534_0A,
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

ActorBlueprint TTYD64_tyd_part_2_imp_00_Goomba_00_Goomba = {
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

ActorBlueprint TTYD64_tyd_part_2_imp_0D_ForestFuzzy_ForestFuzzy_0D = {
    .flags = 0x0,
    .maxHP = 6,
    .type = 0x1A,
    .level = 11,
    .partCount = 1,
    .partsData = TTYD64_mim_forest_fuzzy_ActorParts,
    .initScript = &TTYD64_tyd_part_2_imp_0D_ForestFuzzy_Script_Init_80218510_0D,
    .statusTable = TTYD64_mim_forest_fuzzy_StatusTable,
    .escapeChance = 40,
    .airLiftChance = 90,
    .hurricaneChance = 90,
    .spookChance = 85,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 33, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_BigBandit_3C_BigBandit = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x79,
    .level = 15,
    .partCount = 2,
    .partsData = TTYD64_imp_BigBandit_PartsTable_8021D66C_3C,
    .initScript = &TTYD64_imp_BigBandit_Script_Init_8021D750_3C,
    .statusTable = TTYD64_imp_BigBandit_StatusTable_8021D5C0_3C,
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

ActorBlueprint TTYD64_imp_BigBandit_BanditB_3C = {
    .flags = 0x600000,
    .maxHP = 5,
    .type = 0x13,
    .level = 9,
    .partCount = 1,
    .partsData = b_area_sbk_bandit_CoinParts,
    .initScript = &b_area_sbk_bandit_EVS_Init_Coin,
    .statusTable = TTYD64_imp_BigBandit_StatusTable_8021D5C0_3C,
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

ActorBlueprint TTYD64_imp_FlowerFuzzy_3C_FlowerFuzzy = {
    .flags = 0x0,
    .maxHP = 6,
    .type = 0x6D,
    .level = 13,
    .partCount = 1,
    .partsData = TTYD64_imp_FlowerFuzzy_PartsTable_8021F7D8_12,
    .initScript = &TTYD64_imp_FlowerFuzzy_Script_Init_8021F870_12,
    .statusTable = b_area_omo3_fuzzy_StatusTable,
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

ActorPartBlueprint TTYD64_imp_FlowerFuzzy_PartsTable_8021F7D8_12[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_FlowerFuzzy_IdleAnimations_8021F824_12,
        .defenseTable = b_area_omo3_fuzzy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_imp_BigBandit_SpecialFormation_8021D734_3C[] = {
    { .actor = &TTYD64_imp_BigBandit_BanditB_3C,
      .home = { .vec = &b_area_mac_Lee_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_tyd_part_2_imp_0D_ForestFuzzy_SpecialFormation_8021A800_0D[] = {
    { .actor = &TTYD64_tyd_part_2_imp_0D_ForestFuzzy_ForestFuzzy_0D,
      .home = { .vec = &b_area_mim_forest_fuzzy_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_tyd_part_2_imp_0A_Pokey_SpecialFormation_8021AE10_0A[] = {
    { .actor = &TTYD64_tyd_part_2_imp_0A_Pokey_Pokey_0A,
      .home = { .vec = &b_area_sbk_pokey_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

StageListRow TTYD64_tyd_part_2_StageTable[] = {
    { .name = "tyd_03", .stage = &TTYD64_tyd_part_2_Stage_GlitzPit },
    {},
};

void TTYD64_InstallBattles_tyd_part_2(void) {
    Mod_SetBattleList("TTYD64", 0x3C, TTYD64_tyd_part_2_FormationTable);
    Mod_SetStageList("TTYD64", 0x3C, TTYD64_tyd_part_2_StageTable);
}
