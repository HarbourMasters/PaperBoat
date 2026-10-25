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

extern EvtScript b_area_kmr_part_1_kmr_02_EVS_PostBattle;
extern EvtScript b_area_kmr_part_3_kpa_13_EVS_PreBattle;
extern s32 b_area_kpa_hammer_bro_DefenseTable[];
extern EvtScript b_area_kpa_hammer_bro_EVS_Idle;
extern ActorBlueprint b_area_sam_gulpit_rocks;
API_CALLABLE(AddActorDecoration);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetEnemyMaxHP);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetPartOffset);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(JumpPartTo);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlaySoundAtPart);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetAnimationRate);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartRotation);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
extern ActorBlueprint TTYD64_imp_18_Lakitu_18_Lakitu;
extern s32 TTYD64_imp_18_Lakitu_IdleAnimations_80219EC0_18[];
extern s32 TTYD64_imp_18_Lakitu_IdleAnimations_80219F0C_18[];
extern s32 TTYD64_imp_18_Lakitu_IdleAnimations_Lakitu_HoldingSpiny[];
extern ActorPartBlueprint TTYD64_imp_18_Lakitu_PartsTable_80219FE4_18[];
extern EvtScript TTYD64_imp_18_Lakitu_Script_GetSpacesFree_18;
extern EvtScript TTYD64_imp_18_Lakitu_Script_HandleEvent_8021A16C_18;
extern EvtScript TTYD64_imp_18_Lakitu_Script_Init_8021A078_18;
extern EvtScript TTYD64_imp_18_Lakitu_Script_Lakitu_PullOffSpiny;
extern EvtScript TTYD64_imp_18_Lakitu_Script_Lakitu_SpinyFallOff;
extern EvtScript TTYD64_imp_18_Lakitu_Script_Lakitu_TryToPullSpiny;
extern EvtScript TTYD64_imp_18_Lakitu_Script_SummonSpiny_18;
extern EvtScript TTYD64_imp_18_Lakitu_Script_TakeTurn_8021BD2C_18;
extern EvtScript TTYD64_imp_18_Lakitu_Script_ThrowSpint_18;
extern FormationRow TTYD64_imp_18_Lakitu_SpecialFormation_8021B028_18[];
extern s32 TTYD64_imp_18_Lakitu_StatusTable_80219F38_18[];
extern ActorBlueprint TTYD64_imp_18_Spiny_18_Spiny;
extern s32 TTYD64_imp_18_Spiny_IdleAnimations_8021BED0_18[];
extern s32 TTYD64_imp_18_Spiny_IdleAnimations_8021BF1C_18[];
extern s32 TTYD64_imp_18_Spiny_IdleAnimations_Ball_18[];
extern ActorPartBlueprint TTYD64_imp_18_Spiny_PartsTable_8021C038_18[];
extern EvtScript TTYD64_imp_18_Spiny_Script_HandleEvent_8021C2F4_18;
extern EvtScript TTYD64_imp_18_Spiny_Script_Init_8021C0A8_18;
extern EvtScript TTYD64_imp_18_Spiny_Script_TakeTurn_8021CDC0_18;
extern s32 TTYD64_imp_18_Spiny_StatusTable_8021BF8C_18[];
extern ActorBlueprint TTYD64_imp_1D_Duplighost_1D_Duplighost;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostBombette_1D;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostBow_1D;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostGoombario_1D;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostKooper_1D;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostLakilester_1D;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostParakarry_1D;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostSushie_1D;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostWatt_1D;
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_8021AE90_1D[];
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_8021CAF4_1D[];
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_8021E67C_1D[];
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_8021E6C8_1D[];
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_80220330_1D[];
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_80221590_1D[];
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_8022251C_1D[];
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_802238EC_1D[];
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_802247E8_1D[];
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_80226180_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_8021AFAC_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_8021CBF8_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_8021E7D8_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_80220434_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_80221694_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_80222620_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_802239F8_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_802248EC_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_80226290_1D[];
extern EvtScript TTYD64_imp_1D_Duplighost_Script_8021BC34_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_8021C0F8_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_8021C784_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_8021D698_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_80221D54_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_CopyPartner_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Goombario_Headbonk_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Goombario_Tattle_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_8021CCA0_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_8021EA18_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_80221760_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_802226EC_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_80224994_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_8022635C_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_8021AFF8_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_8021CC44_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_8021E824_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80220480_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80221704_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80222690_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80223A68_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80224938_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80226300_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_LungeAttack_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_8021E604_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_8021F374_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80220CA0_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_802224E4_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80222C7C_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80223F50_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80224F04_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80226924_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80227C40_1D;
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_8021E660_1D[];
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_80220314_1D[];
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_80221574_1D[];
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_80222500_1D[];
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_802238D0_1D[];
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_802247CC_1D[];
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_80226164_1D[];
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_80227404_1D[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_8021CB4C_1D[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_8021E72C_1D[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_80220388_1D[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_802215E8_1D[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_80222574_1D[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_8022394C_1D[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_80224840_1D[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_802261E4_1D[];
extern ActorBlueprint TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha;
extern s32 TTYD64_imp_1D_FrostPiranha_IdleAnimations_8022AAB0_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_FrostPiranha_PartsTable_8022ABC4_1D[];
extern EvtScript TTYD64_imp_1D_FrostPiranha_Script_8022B3AC_1D;
extern EvtScript TTYD64_imp_1D_FrostPiranha_Script_8022BD44_1D;
extern EvtScript TTYD64_imp_1D_FrostPiranha_Script_Init_8022AC10_1D;
extern EvtScript TTYD64_imp_1D_FrostPiranha_Script_TakeTurn_8022B2D4_1D;
extern ActorBlueprint TTYD64_imp_1D_Gulpit_1D_Gulpit;
extern s32 TTYD64_imp_1D_Gulpit_IdleAnimations_80227DD0_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Gulpit_PartsTable_80227EEC_1D[];
extern EvtScript TTYD64_imp_1D_Gulpit_Script_80228518_1D;
extern EvtScript TTYD64_imp_1D_Gulpit_Script_8022898C_1D;
extern EvtScript TTYD64_imp_1D_Gulpit_Script_Init_80227F80_1D;
extern EvtScript TTYD64_imp_1D_Gulpit_Script_TakeTurn_802291B4_1D;
extern EvtScript TTYD64_imp_DarkHammerBros_Script_HammerBros_SingleHammerAttack;
extern EvtScript TTYD64_imp_DarkHammerBros_Script_HammerBros_MultiHammerAttack;
extern EvtScript TTYD64_imp_DarkHammerBros_Script_HandleEvent_8021E860_22;
extern EvtScript TTYD64_imp_DarkHammerBros_Script_8021F5EC_22;
extern EvtScript TTYD64_imp_DarkHammerBros_Script_8021F838_22;
extern Battle TTYD64_pit_part_8_FormationTable[];
extern ActorPartBlueprint TTYD64_imp_DarkHammerBros_PartsTable_8021E5A0_22[];
extern FormationRow TTYD64_pit_part_8_Formation_Pit73_78_1[];
extern FormationRow TTYD64_pit_part_8_Formation_Pit73_78_3[];
extern FormationRow TTYD64_pit_part_8_Formation_Pit73_78_2[];
extern EvtScript TTYD64_pit_part_8_Script_BeforeBattle_Pit;
extern s32 TTYD64_imp_DarkHammerBros_StatusTable_8021E4F4_22[];
extern EvtScript TTYD64_imp_DarkHammerBros_Script_TakeTurn_8022028C_22;
extern FormationRow TTYD64_pit_part_8_Formation_Pit75_3[];
extern FormationRow TTYD64_pit_part_8_Formation_Pit74_79_2[];
extern FormationRow TTYD64_pit_part_8_Formation_Pit74_79_3[];
extern FormationRow TTYD64_pit_part_8_Formation_Pit74_79_1[];
extern EvtScript TTYD64_imp_DarkHammerBros_Script_Init_8021E6A0_22;
extern FormationRow TTYD64_pit_part_8_Formation_Pit75_2[];
extern FormationRow TTYD64_pit_part_8_Formation_Pit75_1[];
extern FormationRow TTYD64_pit_part_8_Formation_Pit71_76_3[];
extern FormationRow TTYD64_pit_part_8_Formation_Pit71_76_2[];
extern FormationRow TTYD64_pit_part_8_Formation_Pit71_76_1[];
extern FormationRow TTYD64_pit_part_8_Formation_Pit72_77_1[];
extern FormationRow TTYD64_pit_part_8_Formation_Pit72_77_2[];
extern FormationRow TTYD64_pit_part_8_Formation_Pit72_77_3[];
extern s32 TTYD64_imp_DarkHammerBros_IdleAnimations_8021E490_22[];
extern FormationRow TTYD64_pit_part_8_Formation_Spiny[];
extern Stage TTYD64_pit_part_8_Stage_Pit1;
extern Stage TTYD64_pit_part_8_Stage_Pit2;
extern ActorBlueprint TTYD64_imp_DarkHammerBros_DarkHammerBros;
extern StageListRow TTYD64_pit_part_8_StageTable[];
extern s32 TTYD64_imp_DarkHammerBros_IdleAnimations_8021E4DC_22[];

// clang-format off
EvtScript TTYD64_imp_DarkHammerBros_Script_HammerBros_SingleHammerAttack = {
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
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    EndIf
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ChildThread
            Set(LVar0, 0)
            Label(0)
            Add(LVar0, 20)
            Mod(LVar0, 360)
            Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, LVar0)
            Wait(1)
            Goto(0)
        EndChildThread
        Call(SetPartPos, ACTOR_SELF, 2, 0, 50, 0)
        Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x5A010C)
        Goto(100)
    EndIf
    ChildThread
        Set(LVar0, 0)
        Label(0)
        Add(LVar0, 20)
        Mod(LVar0, 360)
        Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, LVar0)
        Wait(1)
        Goto(0)
    EndChildThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 23)
    Add(LVar1, 23)
    Sub(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A010C)
    Wait(8)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Label(100)
    Thread
        Wait(15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x5A0102)
    EndThread
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 2, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Else
        Call(SetPartScale, ACTOR_SELF, 2, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetPartSounds, ACTOR_SELF, 2, 2, 0, 0)
            Call(PlaySoundAtPart, ACTOR_SELF, 2, 745)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 10)
            Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(1.2998046875))
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 15, 1)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Sub(LVar0, 40)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 15, 1)
            Sub(LVar0, 30)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 10, 1)
            Sub(LVar0, 20)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 5, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Wait(15)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(20)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetPartSounds, ACTOR_SELF, 2, 2, 0, 0)
    Call(PlaySoundAtPart, ACTOR_SELF, 2, 745)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(1.2998046875))
    Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 15, 1)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 6, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Exec(TTYD64_Script_TryToShrinkTarget)
            Call(GetPartOffset, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Set(LVar1, 10)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 20, 1)
            Sub(LVar0, 30)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 10, 1)
            Sub(LVar0, 20)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 5, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Wait(20)
            Call(YieldTurn)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkHammerBros_Script_HammerBros_MultiHammerAttack = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Thread
        Set(LVar0, 0)
        Loop(100)
            Add(LVar0, 20)
            Mod(LVar0, 360)
            Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, LVar0)
            Call(SetPartRotation, ACTOR_SELF, 3, 0, 0, LVar0)
            Call(SetPartRotation, ACTOR_SELF, 4, 0, 0, LVar0)
            Call(SetPartRotation, ACTOR_SELF, 5, 0, 0, LVar0)
            Call(SetPartRotation, ACTOR_SELF, 6, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 23)
    Add(LVar1, 23)
    Sub(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 2, Float(0.400390625), Float(0.400390625), Float(0.400390625))
        Call(SetPartScale, ACTOR_SELF, 3, Float(0.400390625), Float(0.400390625), Float(0.400390625))
        Call(SetPartScale, ACTOR_SELF, 4, Float(0.400390625), Float(0.400390625), Float(0.400390625))
        Call(SetPartScale, ACTOR_SELF, 5, Float(0.400390625), Float(0.400390625), Float(0.400390625))
        Call(SetPartScale, ACTOR_SELF, 6, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Else
        Call(SetPartScale, ACTOR_SELF, 2, Float(1.0), Float(1.0), Float(1.0))
        Call(SetPartScale, ACTOR_SELF, 3, Float(1.0), Float(1.0), Float(1.0))
        Call(SetPartScale, ACTOR_SELF, 4, Float(1.0), Float(1.0), Float(1.0))
        Call(SetPartScale, ACTOR_SELF, 5, Float(1.0), Float(1.0), Float(1.0))
        Call(SetPartScale, ACTOR_SELF, 6, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Set(LVar0, 2)
            Exec(TTYD64_imp_DarkHammerBros_Script_8021F5EC_22)
            Wait(5)
            Set(LVar0, 3)
            Exec(TTYD64_imp_DarkHammerBros_Script_8021F5EC_22)
            Wait(5)
            Set(LVar0, 4)
            Exec(TTYD64_imp_DarkHammerBros_Script_8021F5EC_22)
            Wait(5)
            Set(LVar0, 5)
            Exec(TTYD64_imp_DarkHammerBros_Script_8021F5EC_22)
            Wait(5)
            Set(LVar0, 6)
            Exec(TTYD64_imp_DarkHammerBros_Script_8021F5EC_22)
            Wait(5)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x5A0102)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(20)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Set(LVar0, 2)
        Exec(TTYD64_imp_DarkHammerBros_Script_8021F838_22)
        Wait(5)
        Set(LVar0, 3)
        Exec(TTYD64_imp_DarkHammerBros_Script_8021F838_22)
        Wait(5)
        Set(LVar0, 4)
        Exec(TTYD64_imp_DarkHammerBros_Script_8021F838_22)
        Wait(5)
        Set(LVar0, 5)
        Exec(TTYD64_imp_DarkHammerBros_Script_8021F838_22)
        Wait(5)
        Set(LVar0, 6)
        Exec(TTYD64_imp_DarkHammerBros_Script_8021F838_22)
    EndThread
    Wait(21)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 3, 64)
    Wait(5)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 3, 64)
    Wait(5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A0102)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 3, 64)
    Wait(5)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Exec(TTYD64_Script_TryToShrinkTarget)
            Wait(20)
            Call(YieldTurn)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkHammerBros_Script_HandleEvent_8021E860_22 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A010E)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A010F)
            SetConst(LVar2, 0x5A0110)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A010F)
            SetConst(LVar2, 0x5A0110)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0110)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A010E)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A010E)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A010E)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0115)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x5A0117)
                Wait(10)
            EndIf
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A010E)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A010E)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0102)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0107)
            SetConst(LVar2, 0x5A010E)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0107)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                IfFlag(LVar0, 0x80000)
                    Call(SetActorDispOffset, ACTOR_SELF, -2, 1, 0)
                Else
                    Call(SetActorDispOffset, ACTOR_SELF, -5, 3, 0)
                EndIf
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A010E)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0102)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkHammerBros_Script_8021F5EC_22 = {
    Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A0102)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A010C)
    Wait(4)
    Call(SetPartFlagBits, ACTOR_SELF, LVar0, 1, 0)
    Call(SetPartSounds, ACTOR_SELF, LVar0, 2, 0, 0)
    Call(PlaySoundAtPart, ACTOR_SELF, LVar0, 745)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Set(LVar2, 10)
    Call(RandInt, 60, LVar4)
    Set(LVar5, 30)
    Sub(LVar5, LVar4)
    Add(LVar1, LVar5)
    Call(SetPartJumpGravity, ACTOR_SELF, LVar0, Float(1.2998046875))
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 15, 1)
    Sub(LVar1, 50)
    Set(LVar2, 10)
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 20, 1)
    Sub(LVar1, 30)
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 10, 1)
    Sub(LVar1, 20)
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 5, 1)
    Call(SetPartFlagBits, ACTOR_SELF, LVar0, 1, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkHammerBros_Script_8021F838_22 = {
    Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A0102)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A010C)
    Wait(4)
    Call(SetPartFlagBits, ACTOR_SELF, LVar0, 1, 0)
    Call(SetPartSounds, ACTOR_SELF, LVar0, 2, 0, 0)
    Call(PlaySoundAtPart, ACTOR_SELF, LVar0, 745)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Call(SetPartJumpGravity, ACTOR_SELF, LVar0, Float(1.2998046875))
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 15, 1)
    Sub(LVar1, 50)
    Set(LVar2, 10)
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 20, 1)
    Sub(LVar1, 30)
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 10, 1)
    Sub(LVar1, 20)
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 5, 1)
    Call(SetPartFlagBits, ACTOR_SELF, LVar0, 1, 1)
    Return
    End
};
// clang-format on

Battle TTYD64_pit_part_8_FormationTable[] = {
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Pit71_76_1,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Pit71_76_2,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Pit71_76_3,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Pit72_77_1,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Pit72_77_2,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Pit72_77_3,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 7,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Pit73_78_1,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 7,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Pit73_78_2,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 7,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Pit73_78_3,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Pit74_79_1,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Pit74_79_2,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Pit74_79_3,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Pit75_1,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Pit75_2,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Pit75_3,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_8_Formation_Spiny,
      .stage = &TTYD64_pit_part_8_Stage_Pit1,
      .onBattleStart = NULL },
    {},
};

ActorPartBlueprint TTYD64_imp_DarkHammerBros_PartsTable_8021E5A0_22[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -3, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkHammerBros_IdleAnimations_8021E490_22,
        .defenseTable = b_area_kpa_hammer_bro_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -3, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkHammerBros_IdleAnimations_8021E4DC_22,
        .defenseTable = b_area_kpa_hammer_bro_DefenseTable,
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
        .idleAnimations = TTYD64_imp_DarkHammerBros_IdleAnimations_8021E4DC_22,
        .defenseTable = b_area_kpa_hammer_bro_DefenseTable,
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
        .idleAnimations = TTYD64_imp_DarkHammerBros_IdleAnimations_8021E4DC_22,
        .defenseTable = b_area_kpa_hammer_bro_DefenseTable,
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
        .idleAnimations = TTYD64_imp_DarkHammerBros_IdleAnimations_8021E4DC_22,
        .defenseTable = b_area_kpa_hammer_bro_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 6,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkHammerBros_IdleAnimations_8021E4DC_22,
        .defenseTable = b_area_kpa_hammer_bro_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_pit_part_8_Formation_Pit73_78_1[] = {
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_Duplighost_1D_Duplighost,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .index = 16 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .index = 16 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .index = 16 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pit_part_8_Formation_Pit73_78_3[] = {
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .index = 16 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .index = 16 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .index = 16 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pit_part_8_Formation_Pit73_78_2[] = {
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_DarkHammerBros_DarkHammerBros,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKHAMMERBROS },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .index = 16 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .index = 16 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .index = 16 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

// clang-format off
EvtScript TTYD64_pit_part_8_Script_BeforeBattle_Pit = {
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

s32 TTYD64_imp_DarkHammerBros_StatusTable_8021E4F4_22[] = {
    1,  0, 2,  0,  6,  50, 9,  100, 7,  50, 4,  70, 3,  0, 11, 80, 5,  70, 10, 70, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,   36, -1, 35, 0,  33, 0, 38, 0,  39, 0,  41, -2, 0,
};

// clang-format off
EvtScript TTYD64_imp_DarkHammerBros_Script_TakeTurn_8022028C_22 = {
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
    MulF(LVar0, Float(100.0))
    DivF(LVar0, LVar1)
    IfGt(LVar0, 34)
        ExecWait(TTYD64_imp_DarkHammerBros_Script_HammerBros_SingleHammerAttack)
    Else
        ExecWait(TTYD64_imp_DarkHammerBros_Script_HammerBros_MultiHammerAttack)
    EndIf
    Return
    End
};
// clang-format on

FormationRow TTYD64_pit_part_8_Formation_Pit75_3[] = {
    { .actor = &TTYD64_imp_1D_Duplighost_1D_Duplighost,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_1D_Duplighost_1D_Duplighost,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_1D_Duplighost_1D_Duplighost,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_1D_Duplighost_1D_Duplighost,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
};

FormationRow TTYD64_pit_part_8_Formation_Pit74_79_2[] = {
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
};

FormationRow TTYD64_pit_part_8_Formation_Pit74_79_3[] = {
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
};

FormationRow TTYD64_pit_part_8_Formation_Pit74_79_1[] = {
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_DarkHammerBros_DarkHammerBros,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKHAMMERBROS },
    { .actor = &TTYD64_imp_DarkHammerBros_DarkHammerBros,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKHAMMERBROS },
};

// clang-format off
EvtScript TTYD64_imp_DarkHammerBros_Script_Init_8021E6A0_22 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_DarkHammerBros_Script_TakeTurn_8022028C_22))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa_hammer_bro_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_DarkHammerBros_Script_HandleEvent_8021E860_22))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pit_part_8_Formation_Pit75_2[] = {
    { .actor = &TTYD64_imp_1D_Duplighost_1D_Duplighost,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_1D_Duplighost_1D_Duplighost,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_DarkHammerBros_DarkHammerBros,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKHAMMERBROS },
};

FormationRow TTYD64_pit_part_8_Formation_Pit75_1[] = {
    { .actor = &TTYD64_imp_1D_Duplighost_1D_Duplighost,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
};

FormationRow TTYD64_pit_part_8_Formation_Pit71_76_3[] = {
    { .actor = &TTYD64_imp_DarkHammerBros_DarkHammerBros,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKHAMMERBROS },
    { .actor = &TTYD64_imp_DarkHammerBros_DarkHammerBros,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKHAMMERBROS },
    { .actor = &TTYD64_imp_DarkHammerBros_DarkHammerBros,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKHAMMERBROS },
};

FormationRow TTYD64_pit_part_8_Formation_Pit71_76_2[] = {
    { .actor = &TTYD64_imp_DarkHammerBros_DarkHammerBros,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKHAMMERBROS },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_DarkHammerBros_DarkHammerBros,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKHAMMERBROS },
};

FormationRow TTYD64_pit_part_8_Formation_Pit71_76_1[] = {
    { .actor = &TTYD64_imp_DarkHammerBros_DarkHammerBros,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKHAMMERBROS },
    { .actor = &TTYD64_imp_1D_Duplighost_1D_Duplighost,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_1D_Duplighost_1D_Duplighost,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
};

FormationRow TTYD64_pit_part_8_Formation_Pit72_77_1[] = {
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_1D_Duplighost_1D_Duplighost,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_1D_Duplighost_1D_Duplighost,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
};

FormationRow TTYD64_pit_part_8_Formation_Pit72_77_2[] = {
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_1D_Duplighost_1D_Duplighost,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
};

FormationRow TTYD64_pit_part_8_Formation_Pit72_77_3[] = {
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
};

s32 TTYD64_imp_DarkHammerBros_IdleAnimations_8021E490_22[] = {
    1,  0x5A0102, 7, 0x5A0100, 6, 0x5A0111, 9, 0x5A0102, 8, 0x5A0100,
    11, 0x5A0102, 5, 0x5A0100, 4, 0x5A0112, 3, 0x5A0112, 0,
};

FormationRow TTYD64_pit_part_8_Formation_Spiny[] = {
    { .actor = &TTYD64_imp_18_Spiny_18_Spiny,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
    { .actor = &TTYD64_imp_18_Spiny_18_Spiny,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
};

Stage TTYD64_pit_part_8_Stage_Pit1 = {
    .texture = "tik_tex",
    .shape = "pit_bt01_shape",
    .hit = "pit_bt01_hit",
    .preBattle = &TTYD64_pit_part_8_Script_BeforeBattle_Pit,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

Stage TTYD64_pit_part_8_Stage_Pit2 = {
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

ActorBlueprint TTYD64_imp_DarkHammerBros_DarkHammerBros = {
    .flags = 0x0,
    .maxHP = 14,
    .type = 0x60,
    .level = 27,
    .partCount = 6,
    .partsData = TTYD64_imp_DarkHammerBros_PartsTable_8021E5A0_22,
    .initScript = &TTYD64_imp_DarkHammerBros_Script_Init_8021E6A0_22,
    .statusTable = TTYD64_imp_DarkHammerBros_StatusTable_8021E4F4_22,
    .escapeChance = 30,
    .airLiftChance = 75,
    .hurricaneChance = 40,
    .spookChance = 40,
    .upAndAwayChance = 70,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 28, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 35 },
};

StageListRow TTYD64_pit_part_8_StageTable[] = {
    { .name = "pit_01", .stage = &TTYD64_pit_part_8_Stage_Pit1 },
    { .name = "pit_12", .stage = &TTYD64_pit_part_8_Stage_Pit2 },
    {},
};

s32 TTYD64_imp_DarkHammerBros_IdleAnimations_8021E4DC_22[] = {
    1,
    0x5A010D,
    0,
};

void TTYD64_InstallBattles_pit_part_8(void) {
    Mod_SetBattleList("TTYD64", 0x37, TTYD64_pit_part_8_FormationTable);
    Mod_SetStageList("TTYD64", 0x37, TTYD64_pit_part_8_StageTable);
}
