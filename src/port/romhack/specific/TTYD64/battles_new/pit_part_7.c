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

extern s32 b_area_flo_lakitu_DefenseTable[];
extern EvtScript b_area_flo_lakitu_EVS_Idle;
extern Vec3i b_area_flo_lakitu_SummonPos;
extern EvtScript b_area_flo_spiny_EVS_CheckToppleAnim;
extern EvtScript b_area_flo_spiny_EVS_Idle;
extern u8 b_area_flo_spiny_FlipPosOffsets[];
extern s32 b_area_flo_spiny_ToppledDefense[];
extern EvtScript b_area_kmr_part_1_kmr_02_EVS_PostBattle;
extern EvtScript b_area_kmr_part_3_kpa_13_EVS_PreBattle;
API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(CopyStatusEffects);
API_CALLABLE(CreateHomeTargetList);
API_CALLABLE(EnableActorBlur);
API_CALLABLE(EnableActorGlow);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyToGoal);
API_CALLABLE(ForceHomePos);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetIndexFromHome);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOriginalActorType);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartEventFlags);
API_CALLABLE(GetPartOffset);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToCurrent);
API_CALLABLE(HPBarToHome);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlaySoundAtPart);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActorDecoration);
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
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetDefenseTable);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetPartEventBits);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartRotation);
API_CALLABLE(SetPartRotationOffset);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTargetActor);
API_CALLABLE(SetTargetOffset);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
extern ActorBlueprint TTYD64_imp_18_Bzzap_18_Bzzap;
extern s32 TTYD64_imp_18_Bzzap_IdleAnimations_8021E930_18[];
extern ActorPartBlueprint TTYD64_imp_18_Bzzap_PartsTable_8021EA34_18[];
extern EvtScript TTYD64_imp_18_Bzzap_Script_Init_8021EB34_18;
extern EvtScript TTYD64_imp_18_Bzzap_Script_Sting_18;
extern EvtScript TTYD64_imp_18_Bzzap_Script_Swarm_18;
extern EvtScript TTYD64_imp_18_Bzzap_Script_Swarm_TinyBee_FlyToTarget;
extern EvtScript TTYD64_imp_18_Bzzap_Script_TakeTurn_8022139C_18;
extern s32 TTYD64_imp_18_Bzzap_StatusTable_8021E988_18[];
extern ActorBlueprint TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee;
extern s32 TTYD64_imp_18_CrazeeDayzee_IdleAnimations_8021D8A4_18[];
extern ActorPartBlueprint TTYD64_imp_18_CrazeeDayzee_PartsTable_8021D858_18[];
extern EvtScript TTYD64_imp_18_CrazeeDayzee_Script_Crazee_Sing_18;
extern EvtScript TTYD64_imp_18_CrazeeDayzee_Script_Init_8021D8F0_18;
extern EvtScript TTYD64_imp_18_CrazeeDayzee_Script_TakeTurn_8021E7BC_18;
extern s32 TTYD64_imp_18_CrazeeDayzee_StatusTable_8021D7AC_18[];
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
extern ActorBlueprint TTYD64_imp_1A_SpikeTop_1A_SpikeTop;
extern s32 TTYD64_imp_1A_SpikeTop_IdleAnimations_8022BA60_1A[];
extern s32 TTYD64_imp_1A_SpikeTop_IdleAnimations_8022BAAC_1A[];
extern s32 TTYD64_imp_1A_SpikeTop_IdleAnimations_8022BAF8_1A[];
extern ActorPartBlueprint TTYD64_imp_1A_SpikeTop_PartsTable_8022BA14_1A[];
extern EvtScript TTYD64_imp_1A_SpikeTop_Script_8022BD1C_1A;
extern EvtScript TTYD64_imp_1A_SpikeTop_Script_HandleEvent_8022C150_1A;
extern EvtScript TTYD64_imp_1A_SpikeTop_Script_HandleEvent_8022C6A8_1A;
extern EvtScript TTYD64_imp_1A_SpikeTop_Script_Init_8022BB3C_1A;
extern EvtScript TTYD64_imp_1A_SpikeTop_Script_TakeTurn_8022D444_1A;
extern EvtScript TTYD64_imp_1A_SpikeTop_Script_TakeTurn_8022DEFC_1A;
extern EvtScript TTYD64_imp_SkyBlueSpiny_Script_TakeTurn_8021CDC0_18;
extern EvtScript TTYD64_imp_SkyBlueSpiny_Script_HandleEvent_8021C2F4_18;
extern EvtScript TTYD64_imp_DarkLakitu_Script_ThrowSpint_18;
extern EvtScript TTYD64_imp_DarkLakitu_Script_SummonSpiny_18;
extern EvtScript TTYD64_imp_DarkLakitu_Script_HandleEvent_8021A16C_18;
extern EvtScript TTYD64_imp_DarkLakitu_Script_GetSpacesFree_18;
extern EvtScript TTYD64_imp_DarkLakitu_Script_Lakitu_PullOffSpiny;
extern EvtScript TTYD64_imp_DarkLakitu_Script_Lakitu_Charge;
extern EvtScript TTYD64_imp_SkyBlueSpiny_Script_Spiny_Charge;
extern EvtScript TTYD64_imp_DarkLakitu_Script_GetFirstOpenColumn_18;
extern EvtScript TTYD64_imp_DarkLakitu_Script_Lakitu_SpinyFallOff;
extern Battle TTYD64_pit_part_7_FormationTable[];
extern EvtScript TTYD64_imp_DarkLakitu_Script_CountActiveSummoners_18;
extern EvtScript TTYD64_imp_DarkLakitu_Script_Lakitu_TryToPullSpiny;
extern EvtScript TTYD64_imp_SkyBlueSpiny_Script_8021C134_18;
extern EvtScript TTYD64_imp_DarkLakitu_Script_TakeTurn_8021BD2C_18;
extern EvtScript TTYD64_pit_part_7_Script_BeforeBattle_Pit;
extern s32 TTYD64_imp_DarkLakitu_StatusTable_80219F38_18[];
extern s32 TTYD64_imp_SkyBlueSpiny_StatusTable_8021BF8C_18[];
extern EvtScript TTYD64_imp_SkyBlueSpiny_Script_Init_8021C0A8_18;
extern EvtScript TTYD64_imp_DarkLakitu_Script_8021A0EC_18;
extern FormationRow TTYD64_pit_part_7_Formation_Pit64_69_3[];
extern FormationRow TTYD64_pit_part_7_Formation_Pit62_67_3[];
extern FormationRow TTYD64_pit_part_7_Formation_Pit65_3[];
extern ActorPartBlueprint TTYD64_imp_DarkLakitu_PartsTable_80219FE4_18[];
extern EvtScript TTYD64_imp_DarkLakitu_Script_Init_8021A078_18;
extern FormationRow TTYD64_pit_part_7_Formation_Pit61_66_3[];
extern FormationRow TTYD64_pit_part_7_Formation_Pit61_66_2[];
extern FormationRow TTYD64_pit_part_7_Formation_Pit64_69_2[];
extern FormationRow TTYD64_pit_part_7_Formation_Pit62_67_2[];
extern FormationRow TTYD64_pit_part_7_Formation_Pit63_68_2[];
extern FormationRow TTYD64_pit_part_7_Formation_Pit63_68_3[];
extern FormationRow TTYD64_pit_part_7_Formation_Pit63_68_1[];
extern FormationRow TTYD64_pit_part_7_Formation_Pit65_2[];
extern s32 TTYD64_imp_DarkLakitu_IdleAnimations_Lakitu_HoldingSpiny[];
extern s32 TTYD64_imp_SkyBlueSpiny_IdleAnimations_8021BED0_18[];
extern s32 TTYD64_imp_DarkLakitu_IdleAnimations_80219EC0_18[];
extern s32 TTYD64_imp_SkyBlueSpiny_IdleAnimations_8021BF1C_18[];
extern ActorPartBlueprint TTYD64_imp_SkyBlueSpiny_PartsTable_8021C038_18[];
extern FormationRow TTYD64_pit_part_7_Formation_Pit61_66_1[];
extern FormationRow TTYD64_pit_part_7_Formation_Pit64_69_1[];
extern FormationRow TTYD64_pit_part_7_Formation_SkyBlueSpiny[];
extern FormationRow TTYD64_pit_part_7_Formation_Pit62_67_1[];
extern FormationRow TTYD64_pit_part_7_Formation_Pit65_1[];
extern ActorBlueprint TTYD64_imp_SkyBlueSpiny_SkyBlueSpiny;
extern Stage TTYD64_pit_part_7_Stage_Pit1;
extern Stage TTYD64_pit_part_7_Stage_Pit2;
extern ActorBlueprint TTYD64_imp_DarkLakitu_DarkLakitu;
extern FormationRow TTYD64_imp_DarkLakitu_SpecialFormation_8021B028_18[];
extern StageListRow TTYD64_pit_part_7_StageTable[];
extern s32 TTYD64_imp_DarkLakitu_IdleAnimations_80219F0C_18[];
extern s32 TTYD64_imp_SkyBlueSpiny_IdleAnimations_Ball_18[];
extern s32 TTYD64_imp_SkyBlueSpiny_DefenseTable_8021BF74_18[];
extern s32 TTYD64_imp_DarkLakitu_IdleAnimations_80219F18_18[];
extern s32 TTYD64_imp_SkyBlueSpiny_DefenseTable_Ball_18[];
extern Vec3i TTYD64_pit_part_7_Bzzap03;
extern s32 TTYD64_imp_SkyBlueSpiny_IdleAnimations_8021BF68_18[];
extern Vec3i TTYD64_pit_part_7_Bzzap00;
extern Vec3i TTYD64_pit_part_7_Bzzap02;
extern Vec3i TTYD64_pit_part_7_Bzzap01;

// clang-format off
EvtScript TTYD64_imp_SkyBlueSpiny_Script_TakeTurn_8021CDC0_18 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(GetActorVar, ACTOR_SELF, 1, LVar0)
        Sub(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 1, LVar0)
        IfGt(LVar0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4A0114)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
        Else
            Call(SetAnimation, ACTOR_SELF, 1, 0x4A0114)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(20)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0102)
            SetConst(LVar2, 0x4A0101)
            ExecWait(Ref(EVS_Enemy_FlipBackUp))
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(TTYD64_imp_SkyBlueSpiny_DefenseTable_8021BF74_18))
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_SkyBlueSpiny_IdleAnimations_8021BED0_18))
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x200000, 1)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
        EndIf
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    IfEq(LVar0, 0)
        Call(GetActorVar, ACTOR_SELF, 2, LVar0)
        IfGt(LVar0, 0)
            Call(SetActorVar, ACTOR_SELF, 2, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4A011A)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4A0101)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(TTYD64_imp_SkyBlueSpiny_DefenseTable_8021BF74_18))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_SkyBlueSpiny_IdleAnimations_8021BED0_18))
            Return
        Else
            Call(GetBattlePhase, LVar0)
            IfNe(LVar0, 1)
                Call(RandInt, 100, LVar0)
                IfLt(LVar0, 30)
                    Call(SetActorVar, ACTOR_SELF, 2, 1)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x4A0119)
                    Wait(20)
                    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(TTYD64_imp_SkyBlueSpiny_DefenseTable_Ball_18))
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_SkyBlueSpiny_IdleAnimations_Ball_18))
                    Return
                EndIf
            EndIf
        EndIf
    EndIf
    Call(RandInt, 100, LVar0)
    IfLe(LVar0, 30)
        Call(GetActorVar, ACTOR_SELF, 3, LVar0)
        IfEq(LVar0, 0)
            ExecWait(TTYD64_imp_SkyBlueSpiny_Script_Spiny_Charge)
            Return
        EndIf
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, 1, 0x4A0119)
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 1, 0x4A0118)
        Wait(10)
    Else
        Wait(20)
    EndIf
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(10)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(5)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
    EndThread
    Call(EnableActorBlur, ACTOR_SELF, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 1, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x49030C)
    Wait(10)
    Call(PlaySoundAtPart, ACTOR_SELF, 2, 711)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(SetPartSounds, ACTOR_SELF, 2, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 4, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
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
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -200, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(EnableActorBlur, ACTOR_SELF, 0)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(TTYD64_imp_SkyBlueSpiny_Script_8021C134_18)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 6, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetAnimation, ACTOR_SELF, 2, 0x49030B)
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
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(TTYD64_imp_SkyBlueSpiny_Script_8021C134_18)
        EndCaseGroup
    EndSwitch
    Call(EnableActorBlur, ACTOR_SELF, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(EnableActorGlow, ACTOR_SELF, 0)
    Call(TTYD64_SetActorExtraData, ACTOR_SELF, 15, 0)
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_SkyBlueSpiny_Script_HandleEvent_8021C2F4_18 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0109)
            SetConst(LVar2, 0x4A010A)
            ExecWait(b_area_flo_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfNe(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A010B)
                SetConst(LVar2, 0x4A010C)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A010D)
                SetConst(LVar2, 0x4A010E)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            EndIf
        CaseEq(36)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfNe(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A010B)
                SetConst(LVar2, 0x4A010C)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A010C)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A010D)
                SetConst(LVar2, 0x4A010E)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A010E)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0109)
            SetConst(LVar2, 0x4A010A)
            ExecWait(b_area_flo_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0109)
            SetConst(LVar2, 0x4A010A)
            ExecWait(b_area_flo_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0109)
            SetConst(LVar2, 0x4A010A)
            ExecWait(b_area_flo_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(13)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfGt(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A0118)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(EnableIdleScript, ACTOR_SELF, 1)
                Call(UseIdleAnimation, ACTOR_SELF, 1)
                Return
            EndIf
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                Call(SetAnimation, ACTOR_SELF, 1, 0x4A010A)
            Else
                Call(SetAnimation, ACTOR_SELF, 1, 0x4A0116)
            EndIf
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(SetActorVar, ACTOR_SELF, 1, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_flo_spiny_ToppledDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_SkyBlueSpiny_IdleAnimations_8021BF1C_18))
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x200000, 0)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            UseBuf(Ref(b_area_flo_spiny_FlipPosOffsets))
            Loop(19)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Wait(20)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfGt(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A0118)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(EnableIdleScript, ACTOR_SELF, 1)
                Call(UseIdleAnimation, ACTOR_SELF, 1)
                Return
            EndIf
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0106)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x4A0107)
                    Wait(10)
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0102)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndSwitch
        EndCaseGroup
        CaseEq(27)
            Wait(10)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar0, 0x80000)
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 0)
                    Add(LVar0, 0)
                EndIf
                Add(LVar1, 8)
            Else
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 0)
                    Add(LVar0, -1)
                EndIf
                Add(LVar1, 22)
            EndIf
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(20)
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0109)
            SetConst(LVar2, 0x4A010A)
            ExecWait(b_area_flo_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0109)
            SetConst(LVar2, 0x4A010A)
            ExecWait(b_area_flo_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0101)
                    ExecWait(Ref(EVS_Enemy_Recover))
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0102)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndSwitch
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0104)
                    SetConst(LVar2, 0x4A0109)
                    ExecWait(Ref(EVS_Enemy_ScareAway))
                    Return
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0102)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndSwitch
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0104)
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0102)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0104)
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0102)
            EndSwitch
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
EvtScript TTYD64_imp_DarkLakitu_Script_ThrowSpint_18 = {
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
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x490103)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, -20, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x490101)
    Call(SetAnimation, ACTOR_SELF, 2, 0x49030B)
    Call(SetAnimation, ACTOR_SELF, 1, 0x490112)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x490113)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, -3)
        Add(LVar1, 16)
        Add(LVar2, 2)
        Call(PlayEffect_impl, 107, 0, LVar0, LVar1, LVar2, Float(0.400390625), 10, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 12)
        Add(LVar2, 0)
        Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
        Call(SetPartScale, ACTOR_SELF, 2, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, -8)
        Add(LVar1, 40)
        Add(LVar2, 5)
        Call(PlayEffect_impl, 107, 0, LVar0, LVar1, LVar2, Float(1.0), 10, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 30)
        Add(LVar2, 2)
        Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
        Call(SetPartScale, ACTOR_SELF, 2, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Wait(10)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x490115)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x490101)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 2, 0x49030C)
    Call(PlaySoundAtPart, ACTOR_SELF, 2, 8402)
    Call(SetPartSounds, ACTOR_SELF, 2, 2, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(1.0))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 40)
            Set(LVar1, 0)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, 0, LVar2, 20, 1)
            Sub(LVar0, 30)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, 0, LVar2, 10, 1)
            Sub(LVar0, 20)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, 0, LVar2, 5, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Wait(20)
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(TTYD64_imp_DarkLakitu_Script_8021A0EC_18)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 15, 0)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetActorVar, ACTOR_SELF, 1, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(1.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 20, 1)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 5, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Thread
                Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(1.0))
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Sub(LVar0, 40)
                Call(JumpPartTo, ACTOR_SELF, 2, LVar0, 0, LVar2, 20, 1)
                Sub(LVar0, 30)
                Call(JumpPartTo, ACTOR_SELF, 2, LVar0, 0, LVar2, 10, 1)
                Sub(LVar0, 20)
                Call(JumpPartTo, ACTOR_SELF, 2, LVar0, 0, LVar2, 5, 1)
                Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            EndThread
            Wait(20)
            Call(YieldTurn)
            ExecWait(TTYD64_imp_DarkLakitu_Script_8021A0EC_18)
        EndCaseGroup
    EndSwitch
    Call(TTYD64_SetActorExtraData, ACTOR_SELF, 15, 0)
    Call(EnableActorGlow, ACTOR_SELF, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
    ExecWait(TTYD64_imp_DarkLakitu_Script_Lakitu_TryToPullSpiny)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkLakitu_Script_SummonSpiny_18 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SummonEnemy, Ref(TTYD64_imp_DarkLakitu_SpecialFormation_8021B028_18), 0)
    Call(CopyStatusEffects, ACTOR_SELF, LVar0)
    Set(LVarB, LVar0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Wait(10)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x490115)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x490101)
    EndThread
    Call(UseBattleCamPreset, 2)
    Call(PlaySoundAtPart, ACTOR_SELF, 2, 8402)
    Call(SetPartSounds, ACTOR_SELF, 2, 2, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x49030C)
    Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(1.599609375))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Call(JumpPartTo, ACTOR_SELF, 2, LVar0, 0, LVar2, 12, 1)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, 0, LVar2)
    Sub(LVar0, 30)
    Thread
        Call(SetPartRotationOffset, ACTOR_SELF, 3, 0, 16, 0)
        Set(LVar0, 0)
        Set(LVar1, 0)
        Set(LFlag0, 0)
        Loop(12)
            Add(LVar0, 30)
            Call(SetPartRotation, ACTOR_SELF, 3, 0, 0, LVar0)
            Add(LVar1, 1)
            IfGe(LVar1, 6)
                IfEq(LFlag0, 1)
                    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
                    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
                    Set(LFlag0, 0)
                Else
                    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
                    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
                    Set(LFlag0, 1)
                EndIf
            EndIf
            Wait(1)
        EndLoop
    EndThread
    Thread
        Call(SetPartJumpGravity, ACTOR_SELF, 3, Float(1.2998046875))
        Call(JumpPartTo, ACTOR_SELF, 3, LVar0, 0, LVar2, 12, 1)
    EndThread
    Wait(1)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(1.2998046875))
    Call(JumpPartTo, ACTOR_SELF, 2, LVar0, 0, LVar2, 12, 1)
    Call(PlayEffect_impl, 6, 1, LVar0, 0, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(GetPartOffset, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Call(SetActorPos, LVarB, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    Call(SetAnimation, LVarB, 1, 0x4A0101)
    Wait(20)
    Call(SetAnimation, LVarB, 1, 0x4A0104)
    Call(SetGoalToIndex, LVarB, LVarA)
    Call(GetGoalPos, LVarB, LVar0, LVar1, LVar2)
    Call(GetActorPos, LVarB, LVar3, LVar4, LVar5)
    IfLt(LVar0, LVar3)
        Call(SetActorYaw, LVarB, 0)
    Else
        Call(SetActorYaw, LVarB, 180)
    EndIf
    Call(SetActorSpeed, LVarB, Float(4.0))
    Call(RunToGoal, LVarB, 0, 0)
    Call(SetAnimation, LVarB, 1, 0x4A0101)
    Call(SetActorYaw, LVarB, 0)
    Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
    Call(ForceHomePos, LVarB, LVar0, LVar1, LVar2)
    Call(HPBarToHome, LVarB)
    Call(SetPartEventBits, ACTOR_SELF, -1, 0x200000, 0)
    Call(SetTargetOffset, ACTOR_SELF, -1, -5, 35)
    Call(SetIdleAnimations, ACTOR_SELF, -1, Ref(TTYD64_imp_DarkLakitu_IdleAnimations_80219EC0_18))
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkLakitu_Script_HandleEvent_8021A16C_18 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
        CaseOrEq(14)
        CaseOrEq(36)
        CaseOrEq(11)
        CaseOrEq(33)
        CaseOrEq(47)
        CaseOrEq(38)
        CaseOrEq(32)
            Call(GetPartEventFlags, ACTOR_SELF, -1, LVar0)
            IfFlag(LVar0, 0x200000)
                Exec(TTYD64_imp_DarkLakitu_Script_Lakitu_SpinyFallOff)
            EndIf
        EndCaseGroup
    EndSwitch
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490104)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490105)
            SetConst(LVar2, 0x490106)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490105)
            SetConst(LVar2, 0x490106)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490106)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490104)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490104)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490104)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490104)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490104)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(TTYD64_imp_DarkLakitu_Script_8021A0EC_18)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490104)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490104)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
            Call(EnableActorGlow, ACTOR_SELF, 0)
            Call(SetActorVar, ACTOR_SELF, 1, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490101)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490104)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490104)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(TTYD64_imp_DarkLakitu_Script_8021A0EC_18)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490101)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490103)
            SetConst(LVar2, 0x490104)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490104)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490104)
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
EvtScript TTYD64_imp_DarkLakitu_Script_GetSpacesFree_18 = {
    Set(LVarB, 0)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar5)
    Call(GetIndexFromHome, LVar0, LVar5)
    Mod(LVar5, 4)
    Switch(LVar5)
        CaseEq(0)
            Set(LFlag1, 1)
        CaseEq(1)
            Set(LFlag2, 1)
        CaseEq(2)
            Set(LFlag3, 1)
        CaseEq(3)
            Set(LFlag4, 1)
    EndSwitch
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfEq(LFlag1, 0)
        Add(LVarB, 1)
    EndIf
    IfEq(LFlag2, 0)
        Add(LVarB, 1)
    EndIf
    IfEq(LFlag3, 0)
        Add(LVarB, 1)
    EndIf
    IfEq(LFlag4, 0)
        Add(LVarB, 1)
    EndIf
    Label(1)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar2)
    Switch(LVar2)
        CaseEq(46)
            Call(GetPartEventFlags, LVar0, -1, LVar1)
            IfFlag(LVar1, 0x200000)
                IfGt(LVarB, 0)
                    Sub(LVarB, 1)
                EndIf
            EndIf
    EndSwitch
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(1)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkLakitu_Script_Lakitu_PullOffSpiny = {
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x49030B)
    Call(SetAnimation, ACTOR_SELF, 1, 0x490112)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x490113)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 12)
        Add(LVar2, 0)
        Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
        Call(SetPartScale, ACTOR_SELF, 2, Float(0.400390625), Float(0.400390625), Float(0.400390625))
        Call(SetPartScale, ACTOR_SELF, 3, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 30)
        Add(LVar2, 2)
        Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
        Call(SetPartScale, ACTOR_SELF, 2, Float(1.0), Float(1.0), Float(1.0))
        Call(SetPartScale, ACTOR_SELF, 3, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x490018)
    Call(SetPartEventBits, ACTOR_SELF, -1, 0x200000, 1)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Add(LVar0, 1)
    Call(SetActorVar, ACTOR_SELF, 0, LVar0)
    Call(SetIdleAnimations, ACTOR_SELF, -1, Ref(TTYD64_imp_DarkLakitu_IdleAnimations_Lakitu_HoldingSpiny))
    Call(SetTargetOffset, ACTOR_SELF, -1, -5, 50)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkLakitu_Script_Lakitu_Charge = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Wait(20)
    Call(PlaySoundAtActor, ACTOR_SELF, 728)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 10)
    Call(PlayEffect_impl, 107, 6, LVar0, LVar1, LVar2, Float(1.0), 45, 0, 0, 0, 0, 0, 0, 0)
    Wait(30)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8413)
    Call(SetActorVar, ACTOR_SELF, 1, 1)
    Call(EnableActorGlow, ACTOR_SELF, 1)
    Call(TTYD64_AddCharge, ACTOR_SELF, 5)
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 1)
    Wait(2)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_SkyBlueSpiny_Script_Spiny_Charge = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Wait(20)
    Call(PlaySoundAtActor, ACTOR_SELF, 728)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 10)
    Call(PlayEffect_impl, 107, 6, LVar0, LVar1, LVar2, Float(1.0), 45, 0, 0, 0, 0, 0, 0, 0)
    Wait(30)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8413)
    Call(SetActorVar, ACTOR_SELF, 3, 1)
    Call(EnableActorGlow, ACTOR_SELF, 1)
    Call(TTYD64_AddCharge, ACTOR_SELF, 6)
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 1)
    Wait(2)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkLakitu_Script_GetFirstOpenColumn_18 = {
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar5)
    Call(GetIndexFromHome, LVar0, LVar5)
    Mod(LVar5, 4)
    Switch(LVar5)
        CaseEq(0)
            Set(LFlag1, 1)
        CaseEq(1)
            Set(LFlag2, 1)
        CaseEq(2)
            Set(LFlag3, 1)
        CaseEq(3)
            Set(LFlag4, 1)
    EndSwitch
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfEq(LFlag1, 0)
        Set(LVarA, 0)
        Return
    EndIf
    IfEq(LFlag2, 0)
        Set(LVarA, 1)
        Return
    EndIf
    IfEq(LFlag3, 0)
        Set(LVarA, 2)
        Return
    EndIf
    IfEq(LFlag4, 0)
        Set(LVarA, 3)
        Return
    EndIf
    Set(LVarA, -1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkLakitu_Script_Lakitu_SpinyFallOff = {
    Call(SetPartEventBits, ACTOR_SELF, -1, 0x200000, 0)
    Call(SetTargetOffset, ACTOR_SELF, -1, -5, 35)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 705)
    Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(1.5))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar3, 25)
    Call(RandInt, 30, LVar1)
    Add(LVar3, LVar1)
    Call(RandInt, 100, LVar1)
    IfLt(LVar1, 50)
        Mul(LVar3, -1)
    EndIf
    Add(LVar0, LVar3)
    Call(SetGoalPos, ACTOR_SELF, LVar0, -50, LVar2)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 20, 1)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
    Call(SetIdleAnimations, ACTOR_SELF, -1, Ref(TTYD64_imp_DarkLakitu_IdleAnimations_80219EC0_18))
    Return
    End
};
// clang-format on

Battle TTYD64_pit_part_7_FormationTable[] = {
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_Pit61_66_1,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_Pit61_66_2,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_Pit61_66_3,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_Pit62_67_1,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_Pit62_67_2,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_Pit62_67_3,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_Pit63_68_1,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_Pit63_68_2,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_Pit63_68_3,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_Pit64_69_1,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_Pit64_69_2,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_Pit64_69_3,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_Pit65_1,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_Pit65_2,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_Pit65_3,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_7_Formation_SkyBlueSpiny,
      .stage = &TTYD64_pit_part_7_Stage_Pit1,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_imp_DarkLakitu_Script_CountActiveSummoners_18 = {
    Set(LVar9, 0)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar2)
    Switch(LVar2)
        CaseOrEq(46)
        CaseOrEq(94)
            Call(GetStatusFlags, LVar0, LVar3)
            IfNotFlag(LVar3, 0x35D000)
                Call(GetActorVar, LVar0, 0, LVar3)
                IfLt(LVar3, 3)
                    Add(LVar9, 1)
                EndIf
            EndIf
        EndCaseGroup
    EndSwitch
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkLakitu_Script_Lakitu_TryToPullSpiny = {
    ExecWait(TTYD64_imp_DarkLakitu_Script_GetSpacesFree_18)
    IfEq(LVarB, 0)
        Return
    EndIf
    ExecWait(TTYD64_imp_DarkLakitu_Script_CountActiveSummoners_18)
    Switch(LVar9)
        CaseEq(1)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 700)
                ExecWait(TTYD64_imp_DarkLakitu_Script_Lakitu_PullOffSpiny)
            EndIf
        CaseEq(2)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 600)
                ExecWait(TTYD64_imp_DarkLakitu_Script_Lakitu_PullOffSpiny)
            EndIf
        CaseEq(3)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 500)
                ExecWait(TTYD64_imp_DarkLakitu_Script_Lakitu_PullOffSpiny)
            EndIf
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_SkyBlueSpiny_Script_8021C134_18 = {
    Call(SetAnimation, ACTOR_SELF, 2, 0x49030C)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 1, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 1, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4A011A)
    Wait(8)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4A0101)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkLakitu_Script_TakeTurn_8021BD2C_18 = {
    Call(GetPartEventFlags, ACTOR_SELF, -1, LVar0)
    IfFlag(LVar0, 0x200000)
        ExecWait(TTYD64_imp_DarkLakitu_Script_GetFirstOpenColumn_18)
        ExecWait(TTYD64_imp_DarkLakitu_Script_SummonSpiny_18)
        Return
    EndIf
    Call(RandInt, 100, LVar0)
    IfLe(LVar0, 30)
        Call(GetActorVar, ACTOR_SELF, 1, LVar0)
        IfEq(LVar0, 1)
            ExecWait(TTYD64_imp_DarkLakitu_Script_ThrowSpint_18)
        Else
            ExecWait(TTYD64_imp_DarkLakitu_Script_Lakitu_Charge)
        EndIf
    Else
        ExecWait(TTYD64_imp_DarkLakitu_Script_ThrowSpint_18)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_pit_part_7_Script_BeforeBattle_Pit = {
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

s32 TTYD64_imp_DarkLakitu_StatusTable_80219F38_18[] = {
    1,  0, 2,  0, 6,  60, 9,  100, 7,  80, 4,  95, 3,  0, 11, 50, 5,  50, 10, 75, 8, 70,
    31, 0, 32, 0, 37, 0,  34, 0,   36, 1,  35, 0,  33, 0, 38, -1, 39, 0,  41, 0,  0,
};

s32 TTYD64_imp_SkyBlueSpiny_StatusTable_8021BF8C_18[] = {
    1,  0, 2,  0, 6,  60, 9,  100, 7,  50, 4,  60, 3,  0, 11, 50, 5,  75, 10, 75, 8, 70,
    31, 0, 32, 0, 37, 0,  34, 0,   36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, 0,  0,
};

// clang-format off
EvtScript TTYD64_imp_SkyBlueSpiny_Script_Init_8021C0A8_18 = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_flo_spiny_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_SkyBlueSpiny_Script_TakeTurn_8021CDC0_18))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_SkyBlueSpiny_Script_HandleEvent_8021C2F4_18))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkLakitu_Script_8021A0EC_18 = {
    Call(SetAnimation, ACTOR_SELF, 1, 0x490103)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
    Call(FlyToGoal, ACTOR_SELF, 0, 0, 11)
    Call(SetAnimation, ACTOR_SELF, 1, 0x490101)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pit_part_7_Formation_Pit64_69_3[] = {
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .vec = &TTYD64_pit_part_7_Bzzap00 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .vec = &TTYD64_pit_part_7_Bzzap01 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .vec = &TTYD64_pit_part_7_Bzzap02 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .vec = &TTYD64_pit_part_7_Bzzap03 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
};

FormationRow TTYD64_pit_part_7_Formation_Pit62_67_3[] = {
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
};

FormationRow TTYD64_pit_part_7_Formation_Pit65_3[] = {
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 4 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
};

ActorPartBlueprint TTYD64_imp_DarkLakitu_PartsTable_80219FE4_18[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -5, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkLakitu_IdleAnimations_80219EC0_18,
        .defenseTable = b_area_flo_lakitu_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -13 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkLakitu_IdleAnimations_80219F0C_18,
        .defenseTable = b_area_flo_lakitu_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkLakitu_IdleAnimations_80219F18_18,
        .defenseTable = b_area_flo_lakitu_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_imp_DarkLakitu_Script_Init_8021A078_18 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_DarkLakitu_Script_TakeTurn_8021BD2C_18))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_flo_lakitu_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_DarkLakitu_Script_HandleEvent_8021A16C_18))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pit_part_7_Formation_Pit61_66_3[] = {
    { .actor = &TTYD64_imp_DarkLakitu_DarkLakitu,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKLAKITU },
    { .actor = &TTYD64_imp_DarkLakitu_DarkLakitu,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKLAKITU },
    { .actor = &TTYD64_imp_DarkLakitu_DarkLakitu,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKLAKITU },
};

FormationRow TTYD64_pit_part_7_Formation_Pit61_66_2[] = {
    { .actor = &TTYD64_imp_DarkLakitu_DarkLakitu,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKLAKITU },
    { .actor = &TTYD64_imp_DarkLakitu_DarkLakitu,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKLAKITU },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
};

FormationRow TTYD64_pit_part_7_Formation_Pit64_69_2[] = {
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .vec = &TTYD64_pit_part_7_Bzzap01 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_DarkLakitu_DarkLakitu,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKLAKITU },
    { .actor = &TTYD64_imp_DarkLakitu_DarkLakitu,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKLAKITU },
};

FormationRow TTYD64_pit_part_7_Formation_Pit62_67_2[] = {
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .vec = &TTYD64_pit_part_7_Bzzap02 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .vec = &TTYD64_pit_part_7_Bzzap03 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
};

FormationRow TTYD64_pit_part_7_Formation_Pit63_68_2[] = {
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
};

FormationRow TTYD64_pit_part_7_Formation_Pit63_68_3[] = {
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
};

FormationRow TTYD64_pit_part_7_Formation_Pit63_68_1[] = {
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
};

FormationRow TTYD64_pit_part_7_Formation_Pit65_2[] = {
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
};

s32 TTYD64_imp_DarkLakitu_IdleAnimations_Lakitu_HoldingSpiny[] = {
    1,  0x490018, 7, 0x490100, 6, 0x490108, 9, 0x490101, 8, 0x490100,
    11, 0x490101, 5, 0x490100, 4, 0x490109, 3, 0x490109, 0,
};

s32 TTYD64_imp_SkyBlueSpiny_IdleAnimations_8021BED0_18[] = {
    1,  0x4A0101, 7, 0x4A0100, 6, 0x4A0110, 9, 0x4A0101, 8, 0x4A0100,
    11, 0x4A0101, 5, 0x4A0100, 4, 0x4A0112, 3, 0x4A0112, 0,
};

s32 TTYD64_imp_DarkLakitu_IdleAnimations_80219EC0_18[] = {
    1,  0x490101, 7, 0x490100, 6, 0x490108, 9, 0x490101, 8, 0x490100,
    11, 0x490101, 5, 0x490100, 4, 0x490109, 3, 0x490109, 0,
};

s32 TTYD64_imp_SkyBlueSpiny_IdleAnimations_8021BF1C_18[] = {
    1,  0x4A0102, 7, 0x4A0115, 6, 0x4A0111, 9, 0x4A0102, 8, 0x4A0115,
    11, 0x4A0102, 5, 0x4A0115, 4, 0x4A0113, 3, 0x4A0113, 0,
};

ActorPartBlueprint TTYD64_imp_SkyBlueSpiny_PartsTable_8021C038_18[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_SkyBlueSpiny_IdleAnimations_8021BED0_18,
        .defenseTable = TTYD64_imp_SkyBlueSpiny_DefenseTable_8021BF74_18,
        .eventFlags = 0x201000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -4 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_SkyBlueSpiny_IdleAnimations_8021BF68_18,
        .defenseTable = TTYD64_imp_SkyBlueSpiny_DefenseTable_8021BF74_18,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_pit_part_7_Formation_Pit61_66_1[] = {
    { .actor = &TTYD64_imp_DarkLakitu_DarkLakitu,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKLAKITU },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
};

FormationRow TTYD64_pit_part_7_Formation_Pit64_69_1[] = {
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .vec = &TTYD64_pit_part_7_Bzzap01 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
};

FormationRow TTYD64_pit_part_7_Formation_SkyBlueSpiny[] = {
    { .actor = &TTYD64_imp_SkyBlueSpiny_SkyBlueSpiny,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SKYBLUESPINY },
    { .actor = &TTYD64_imp_SkyBlueSpiny_SkyBlueSpiny,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SKYBLUESPINY },
};

FormationRow TTYD64_pit_part_7_Formation_Pit62_67_1[] = {
    { .actor = &TTYD64_imp_1A_SpikeTop_1A_SpikeTop,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
};

FormationRow TTYD64_pit_part_7_Formation_Pit65_1[] = {
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_DarkLakitu_DarkLakitu,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKLAKITU },
};

ActorBlueprint TTYD64_imp_SkyBlueSpiny_SkyBlueSpiny = {
    .flags = 0x0,
    .maxHP = 6,
    .type = 0x5F,
    .level = 22,
    .partCount = 2,
    .partsData = TTYD64_imp_SkyBlueSpiny_PartsTable_8021C038_18,
    .initScript = &TTYD64_imp_SkyBlueSpiny_Script_Init_8021C0A8_18,
    .statusTable = TTYD64_imp_SkyBlueSpiny_StatusTable_8021BF8C_18,
    .escapeChance = 50,
    .airLiftChance = 75,
    .hurricaneChance = 80,
    .spookChance = 60,
    .upAndAwayChance = 50,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 24, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

Stage TTYD64_pit_part_7_Stage_Pit1 = {
    .texture = "tik_tex",
    .shape = "pit_bt01_shape",
    .hit = "pit_bt01_hit",
    .preBattle = &TTYD64_pit_part_7_Script_BeforeBattle_Pit,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

Stage TTYD64_pit_part_7_Stage_Pit2 = {
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

ActorBlueprint TTYD64_imp_DarkLakitu_DarkLakitu = {
    .flags = 0x200,
    .maxHP = 13,
    .type = 0x5E,
    .level = 20,
    .partCount = 3,
    .partsData = TTYD64_imp_DarkLakitu_PartsTable_80219FE4_18,
    .initScript = &TTYD64_imp_DarkLakitu_Script_Init_8021A078_18,
    .statusTable = TTYD64_imp_DarkLakitu_StatusTable_80219F38_18,
    .escapeChance = 50,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 50,
    .upAndAwayChance = 50,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 2,
    .size = { 32, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -11, 20 },
    .statusTextOffset = { 10, 34 },
};

FormationRow TTYD64_imp_DarkLakitu_SpecialFormation_8021B028_18[] = {
    { .actor = &TTYD64_imp_SkyBlueSpiny_SkyBlueSpiny,
      .home = { .vec = &b_area_flo_lakitu_SummonPos },
      .priority = 100,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

StageListRow TTYD64_pit_part_7_StageTable[] = {
    { .name = "pit_01", .stage = &TTYD64_pit_part_7_Stage_Pit1 },
    { .name = "pit_12", .stage = &TTYD64_pit_part_7_Stage_Pit2 },
    {},
};

s32 TTYD64_imp_DarkLakitu_IdleAnimations_80219F0C_18[] = {
    1,
    0x49030B,
    0,
};

s32 TTYD64_imp_SkyBlueSpiny_IdleAnimations_Ball_18[] = {
    1,
    0x4A0118,
    0,
};

s32 TTYD64_imp_SkyBlueSpiny_DefenseTable_8021BF74_18[] = {
    1,
    4,
    0,
};

s32 TTYD64_imp_DarkLakitu_IdleAnimations_80219F18_18[] = {
    1,
    0x4A0101,
    0,
};

s32 TTYD64_imp_SkyBlueSpiny_DefenseTable_Ball_18[] = {
    1,
    99,
    0,
};

Vec3i TTYD64_pit_part_7_Bzzap03 = { 125, 18, 25 };

s32 TTYD64_imp_SkyBlueSpiny_IdleAnimations_8021BF68_18[] = {
    1,
    0x49030B,
    0,
};

Vec3i TTYD64_pit_part_7_Bzzap00 = { 5, 18, -20 };

Vec3i TTYD64_pit_part_7_Bzzap02 = { 85, 18, 10 };

Vec3i TTYD64_pit_part_7_Bzzap01 = { 45, 18, -5 };

void TTYD64_InstallBattles_pit_part_7(void) {
    Mod_SetBattleList("TTYD64", 0x36, TTYD64_pit_part_7_FormationTable);
    Mod_SetStageList("TTYD64", 0x36, TTYD64_pit_part_7_StageTable);
}
