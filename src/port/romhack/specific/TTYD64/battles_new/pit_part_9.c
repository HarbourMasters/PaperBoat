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

extern s32 b_area_iwa_monty_mole_DefenseTable[];
extern EvtScript b_area_iwa_monty_mole_EVS_Hole_Init;
extern EvtScript b_area_iwa_monty_mole_EVS_Idle;
extern s32 b_area_iwa_monty_mole_StatusTable[];
extern Vec3i b_area_iwa_monty_mole_SummonPos;
extern EvtScript b_area_kmr_part_1_kmr_02_EVS_PostBattle;
extern EvtScript b_area_kmr_part_3_kpa_13_EVS_PreBattle;
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyPartTo);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlaySoundAtPart);
API_CALLABLE(RandInt);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetAnimationRate);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTargetActor);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
extern ActorBlueprint TTYD64_imp_22_DryBones_22_DryBones;
extern s32 TTYD64_imp_22_DryBones_IdleAnimations_8021CA20_22[];
extern ActorPartBlueprint TTYD64_imp_22_DryBones_PartsTable_8021CC14_22[];
extern EvtScript TTYD64_imp_22_DryBones_Script_DryBones_MultiBoneAttack_22;
extern EvtScript TTYD64_imp_22_DryBones_Script_DryBones_Summon_22;
extern EvtScript TTYD64_imp_22_DryBones_Script_DryBones_ThrowBone;
extern EvtScript TTYD64_imp_22_DryBones_Script_DryBones_ThrowBone_Miss;
extern EvtScript TTYD64_imp_22_DryBones_Script_GetNextOpenColumn_22;
extern EvtScript TTYD64_imp_22_DryBones_Script_Init_8021CC84_22;
extern EvtScript TTYD64_imp_22_DryBones_Script_RotateBone_MultiAttack_22;
extern EvtScript TTYD64_imp_22_DryBones_Script_RotateBone_Part4_22;
extern EvtScript TTYD64_imp_22_DryBones_Script_TakeTurn_8021DB48_22;
extern FormationRow TTYD64_imp_22_DryBones_SpecialFormation_DryBones_22[];
extern ActorBlueprint TTYD64_imp_22_HammerBros_22_HammerBros;
extern s32 TTYD64_imp_22_HammerBros_IdleAnimations_8021E490_22[];
extern ActorPartBlueprint TTYD64_imp_22_HammerBros_PartsTable_8021E5A0_22[];
extern EvtScript TTYD64_imp_22_HammerBros_Script_8021F5EC_22;
extern EvtScript TTYD64_imp_22_HammerBros_Script_8021F838_22;
extern EvtScript TTYD64_imp_22_HammerBros_Script_HammerBros_MultiHammerAttack;
extern EvtScript TTYD64_imp_22_HammerBros_Script_HammerBros_SingleHammerAttack;
extern EvtScript TTYD64_imp_22_HammerBros_Script_Init_8021E6A0_22;
extern EvtScript TTYD64_imp_22_HammerBros_Script_TakeTurn_8022028C_22;
extern s32 TTYD64_imp_22_HammerBros_StatusTable_8021E4F4_22[];
extern ActorBlueprint TTYD64_imp_22_Koopatrol_22_Koopatrol;
extern s32 TTYD64_imp_22_Koopatrol_IdleAnimations_802280F0_12[];
extern s32 TTYD64_imp_22_Koopatrol_IdleAnimations_8022813C_12[];
extern s32 TTYD64_imp_22_Koopatrol_IdleAnimations_80228188_12[];
extern s32 TTYD64_imp_22_Koopatrol_IdleAnimations_802281D4_12[];
extern s32 TTYD64_imp_22_Koopatrol_IdleAnimations_Koopatrol_Hide_12[];
extern ActorBlueprint TTYD64_imp_22_Koopatrol_Koopatrol_12;
extern ActorPartBlueprint TTYD64_imp_22_Koopatrol_PartsTable_8022839C_12[];
extern EvtScript TTYD64_imp_22_Koopatrol_Script_HandleEvent_80228C44_12;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Idle_8022875C_12;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Init_802283E8_12;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_ChargeAttack_12;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_Hide_12;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_PowerShell_12;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_ShellToss_12;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_Summon_12;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_Unhide_12;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_TakeTurn_8022C454_12;
extern FormationRow TTYD64_imp_22_Koopatrol_SpecialFormation_8022BBC8_12[];
extern s32 TTYD64_imp_22_Koopatrol_StatusTable_80228254_12[];
extern EvtScript TTYD64_imp_DarkMontyMole_Script_HandleEvent_8021A824_09;
extern EvtScript TTYD64_imp_DarkMontyMole_Script_TakeTurn_8021AFAC_09;
extern Battle TTYD64_pit_part_9_FormationTable[];
extern EvtScript TTYD64_pit_part_9_Script_BeforeBattle_Pit;
extern EvtScript TTYD64_imp_DarkMontyMole_Script_8021A6FC_09;
extern FormationRow TTYD64_pit_part_9_Formation_Pit83_88_3[];
extern FormationRow TTYD64_pit_part_9_Formation_Pit82_87_3[];
extern FormationRow TTYD64_pit_part_9_Formation_Pit84_89_3[];
extern FormationRow TTYD64_pit_part_9_Formation_Pit84_89_2[];
extern ActorPartBlueprint TTYD64_imp_DarkMontyMole_PartsTable_8021A508_09[];
extern EvtScript TTYD64_imp_DarkMontyMole_Script_Init_8021A7B0_09;
extern FormationRow TTYD64_pit_part_9_Formation_Pit83_88_1[];
extern FormationRow TTYD64_pit_part_9_Formation_Pit83_88_2[];
extern FormationRow TTYD64_pit_part_9_Formation_Pit82_87_2[];
extern FormationRow TTYD64_pit_part_9_Formation_Pit81_86_2[];
extern FormationRow TTYD64_pit_part_9_Formation_Pit84_89_1[];
extern FormationRow TTYD64_pit_part_9_Formation_Pit81_86_3[];
extern FormationRow TTYD64_pit_part_9_Formation_Pit81_86_1[];
extern FormationRow TTYD64_pit_part_9_Formation_Pit85_3[];
extern FormationRow TTYD64_pit_part_9_Formation_Pit85_2[];
extern FormationRow TTYD64_pit_part_9_Formation_Pit85_1[];
extern s32 TTYD64_imp_DarkMontyMole_IdleAnimations_8021A59C_09[];
extern FormationRow TTYD64_pit_part_9_Formation_Pit82_87_1[];
extern ActorBlueprint TTYD64_imp_DarkMontyMole_EmptyMoleHole_09;
extern Stage TTYD64_pit_part_9_Stage_Pit1;
extern Stage TTYD64_pit_part_9_Stage_Pit2;
extern ActorBlueprint TTYD64_imp_DarkMontyMole_DarkMontyMole;
extern ActorPartBlueprint TTYD64_imp_DarkMontyMole_PartsTable_8021A60C_09[];
extern FormationRow TTYD64_imp_DarkMontyMole_SpecialFormation_8021A6C4_09[];
extern FormationRow TTYD64_imp_DarkMontyMole_SpecialFormation_8021A6E0_09[];
extern StageListRow TTYD64_pit_part_9_StageTable[];
extern s32 TTYD64_imp_DarkMontyMole_IdleAnimations_8021A5F4_09[];
extern s32 TTYD64_imp_DarkMontyMole_IdleAnimations_8021A5E8_09[];

// clang-format off
EvtScript TTYD64_imp_DarkMontyMole_Script_HandleEvent_8021A824_09 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastElement, LVarE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            IfFlag(LVarE, 64)
                ChildThread
                    Wait(8)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x2F0207)
                EndChildThread
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2F0206)
                ExecWait(Ref(EVS_Enemy_Hit))
                Call(SetAnimation, ACTOR_SELF, 1, 0x2F0208)
                Wait(10)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2F0205)
                ExecWait(Ref(EVS_Enemy_Hit))
            EndIf
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2F020A)
            SetConst(LVar2, 0x2F020B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2F020A)
            SetConst(LVar2, 0x2F020B)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_imp_DarkMontyMole_Script_8021A6FC_09)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2F020C)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            Call(GetLastElement, LVar0)
            IfFlag(LVar0, 64)
                Call(PlaySoundAtActor, ACTOR_SELF, 802)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
                Call(SetAnimation, ACTOR_SELF, 1, 0x2F0211)
                Wait(80)
                Call(PlaySoundAtActor, ACTOR_SELF, 801)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
                Call(SetAnimation, ACTOR_SELF, 1, 0x2F0210)
                Wait(20)
                Call(SetAnimation, ACTOR_SELF, 1, 0x2F0214)
                Wait(20)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2F0201)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2F0205)
            ExecWait(Ref(EVS_Enemy_Hit))
            Call(SetAnimation, ACTOR_SELF, 1, 0x2F0206)
            Wait(10)
            ExecWait(TTYD64_imp_DarkMontyMole_Script_8021A6FC_09)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2F0209)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2F0206)
            Wait(8)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2F0207)
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2F0208)
            Wait(8)
        CaseEq(57)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2F0206)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2F0207)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2F0208)
            Wait(15)
            Call(SetActorFlagBits, ACTOR_SELF, 0x404000, 1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_DarkMontyMole_IdleAnimations_8021A5F4_09))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2F0205)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            ExecWait(TTYD64_imp_DarkMontyMole_Script_8021A6FC_09)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x35D000)
                Call(SetActorDispOffset, ACTOR_SELF, 0, -5, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x2F0219)
            Else
                IfFlag(LVar0, 0x80000)
                    Call(SetActorDispOffset, ACTOR_SELF, 0, -9, 0)
                Else
                    Call(SetActorDispOffset, ACTOR_SELF, 0, -23, 0)
                EndIf
                Call(SetAnimation, ACTOR_SELF, 1, 0x2F0209)
            EndIf
            Wait(1000)
            Return
        CaseEq(31)
            Call(PlaySoundAtActor, ACTOR_SELF, 802)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x2F0211)
            Wait(40)
            Call(PlaySoundAtActor, ACTOR_SELF, 801)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x2F0210)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2F0214)
            Wait(20)
        CaseEq(61)
            ExecWait(TTYD64_imp_DarkMontyMole_Script_8021A6FC_09)
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkMontyMole_Script_TakeTurn_8021AFAC_09 = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x2F0204)
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
            Call(SetAnimation, ACTOR_SELF, 3, 0x2F020F)
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
    Call(SetAnimation, ACTOR_SELF, 3, 0x2F020F)
    Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 0, 20, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 6, 32)
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

Battle TTYD64_pit_part_9_FormationTable[] = {
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_9_Formation_Pit81_86_1,
      .stage = &TTYD64_pit_part_9_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_9_Formation_Pit81_86_2,
      .stage = &TTYD64_pit_part_9_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_9_Formation_Pit81_86_3,
      .stage = &TTYD64_pit_part_9_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_9_Formation_Pit82_87_1,
      .stage = &TTYD64_pit_part_9_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_9_Formation_Pit82_87_2,
      .stage = &TTYD64_pit_part_9_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_9_Formation_Pit82_87_3,
      .stage = &TTYD64_pit_part_9_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_9_Formation_Pit83_88_1,
      .stage = &TTYD64_pit_part_9_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_9_Formation_Pit83_88_2,
      .stage = &TTYD64_pit_part_9_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_9_Formation_Pit83_88_3,
      .stage = &TTYD64_pit_part_9_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_9_Formation_Pit84_89_1,
      .stage = &TTYD64_pit_part_9_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_9_Formation_Pit84_89_2,
      .stage = &TTYD64_pit_part_9_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_9_Formation_Pit84_89_3,
      .stage = &TTYD64_pit_part_9_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_9_Formation_Pit85_1,
      .stage = &TTYD64_pit_part_9_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_9_Formation_Pit85_2,
      .stage = &TTYD64_pit_part_9_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_9_Formation_Pit85_3,
      .stage = &TTYD64_pit_part_9_Stage_Pit1,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_pit_part_9_Script_BeforeBattle_Pit = {
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

// clang-format off
EvtScript TTYD64_imp_DarkMontyMole_Script_8021A6FC_09 = {
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SummonEnemy, Ref(TTYD64_imp_DarkMontyMole_SpecialFormation_8021A6E0_09), 0)
    Else
        Call(SummonEnemy, Ref(TTYD64_imp_DarkMontyMole_SpecialFormation_8021A6C4_09), 0)
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Sub(LVar3, 1)
    Call(SetActorPos, LVar0, LVar1, LVar2, LVar3)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pit_part_9_Formation_Pit83_88_3[] = {
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
};

FormationRow TTYD64_pit_part_9_Formation_Pit82_87_3[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
};

FormationRow TTYD64_pit_part_9_Formation_Pit84_89_3[] = {
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
};

FormationRow TTYD64_pit_part_9_Formation_Pit84_89_2[] = {
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
};

ActorPartBlueprint TTYD64_imp_DarkMontyMole_PartsTable_8021A508_09[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 16 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkMontyMole_IdleAnimations_8021A59C_09,
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
        .idleAnimations = TTYD64_imp_DarkMontyMole_IdleAnimations_8021A59C_09,
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
        .idleAnimations = TTYD64_imp_DarkMontyMole_IdleAnimations_8021A5E8_09,
        .defenseTable = b_area_iwa_monty_mole_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_imp_DarkMontyMole_Script_Init_8021A7B0_09 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_DarkMontyMole_Script_TakeTurn_8021AFAC_09))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_iwa_monty_mole_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_DarkMontyMole_Script_HandleEvent_8021A824_09))
    Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pit_part_9_Formation_Pit83_88_1[] = {
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_pit_part_9_Formation_Pit83_88_2[] = {
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
};

FormationRow TTYD64_pit_part_9_Formation_Pit82_87_2[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
};

FormationRow TTYD64_pit_part_9_Formation_Pit81_86_2[] = {
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_pit_part_9_Formation_Pit84_89_1[] = {
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
};

FormationRow TTYD64_pit_part_9_Formation_Pit81_86_3[] = {
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
};

FormationRow TTYD64_pit_part_9_Formation_Pit81_86_1[] = {
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
};

FormationRow TTYD64_pit_part_9_Formation_Pit85_3[] = {
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
};

FormationRow TTYD64_pit_part_9_Formation_Pit85_2[] = {
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_pit_part_9_Formation_Pit85_1[] = {
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
    { .actor = &TTYD64_imp_DarkMontyMole_DarkMontyMole,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKMONTYMOLE },
};

s32 TTYD64_imp_DarkMontyMole_IdleAnimations_8021A59C_09[] = {
    1,  0x2F0201, 7, 0x2F0200, 6, 0x2F0214, 9, 0x2F0201, 8, 0x2F0200,
    11, 0x2F0201, 5, 0x2F0200, 4, 0x2F0214, 3, 0x2F0214, 0,
};

FormationRow TTYD64_pit_part_9_Formation_Pit82_87_1[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

ActorBlueprint TTYD64_imp_DarkMontyMole_EmptyMoleHole_09 = {
    .flags = 0x640004,
    .maxHP = 5,
    .type = 0x6B,
    .level = 9,
    .partCount = 1,
    .partsData = TTYD64_imp_DarkMontyMole_PartsTable_8021A60C_09,
    .initScript = &b_area_iwa_monty_mole_EVS_Hole_Init,
    .statusTable = NULL,
    .escapeChance = 80,
    .airLiftChance = 0,
    .hurricaneChance = 80,
    .spookChance = 80,
    .upAndAwayChance = 90,
    .spinSmashReq = 4,
    .powerBounceChance = 90,
    .coinReward = 2,
    .size = { 32, 18 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

Stage TTYD64_pit_part_9_Stage_Pit1 = {
    .texture = "tik_tex",
    .shape = "pit_bt01_shape",
    .hit = "pit_bt01_hit",
    .preBattle = &TTYD64_pit_part_9_Script_BeforeBattle_Pit,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

Stage TTYD64_pit_part_9_Stage_Pit2 = {
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

ActorBlueprint TTYD64_imp_DarkMontyMole_DarkMontyMole = {
    .flags = 0x0,
    .maxHP = 10,
    .type = 0x61,
    .level = 29,
    .partCount = 3,
    .partsData = TTYD64_imp_DarkMontyMole_PartsTable_8021A508_09,
    .initScript = &TTYD64_imp_DarkMontyMole_Script_Init_8021A7B0_09,
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

ActorPartBlueprint TTYD64_imp_DarkMontyMole_PartsTable_8021A60C_09[] = {
    {
        .flags = 0x22000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkMontyMole_IdleAnimations_8021A5F4_09,
        .defenseTable = NULL,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_imp_DarkMontyMole_SpecialFormation_8021A6C4_09[] = {
    { .actor = &TTYD64_imp_DarkMontyMole_EmptyMoleHole_09,
      .home = { .vec = &b_area_iwa_monty_mole_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_DarkMontyMole_SpecialFormation_8021A6E0_09[] = {
    { .actor = &TTYD64_imp_DarkMontyMole_EmptyMoleHole_09,
      .home = { .vec = &b_area_iwa_monty_mole_SummonPos },
      .priority = 0,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

StageListRow TTYD64_pit_part_9_StageTable[] = {
    { .name = "pit_01", .stage = &TTYD64_pit_part_9_Stage_Pit1 },
    { .name = "pit_12", .stage = &TTYD64_pit_part_9_Stage_Pit2 },
    {},
};

s32 TTYD64_imp_DarkMontyMole_IdleAnimations_8021A5F4_09[] = {
    1,
    0x2F0212,
    0,
};

s32 TTYD64_imp_DarkMontyMole_IdleAnimations_8021A5E8_09[] = {
    1,
    0x2F020F,
    0,
};

void TTYD64_InstallBattles_pit_part_9(void) {
    Mod_SetBattleList("TTYD64", 0x38, TTYD64_pit_part_9_FormationTable);
    Mod_SetStageList("TTYD64", 0x38, TTYD64_pit_part_9_StageTable);
}
