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

extern s32 b_area_kmr_part_1_goomba_DefenseTable[];
extern EvtScript b_area_kmr_part_1_kmr_02_EVS_PostBattle;
extern s32 b_area_kmr_part_3_egg_jr_troopa_DefenseTable[];
extern EvtScript b_area_omo3_hammer_bro_EVS_Idle;
API_CALLABLE(AddGoalPos);
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
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetDist2D);
API_CALLABLE(GetEnemyMaxHP);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPlayerHP);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlaySoundAtPart);
API_CALLABLE(RandInt);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetAnimationRate);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartRotation);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
extern ActorBlueprint TTYD64_imp_18_WMagikoopa_18_WMagikoopa;
extern s32 TTYD64_imp_18_WMagikoopa_IdleAnimations_80223D70_18[];
extern ActorPartBlueprint TTYD64_imp_18_WMagikoopa_PartsTable_80223C90_18[];
extern EvtScript TTYD64_imp_18_WMagikoopa_Script_HealAll_18;
extern EvtScript TTYD64_imp_18_WMagikoopa_Script_HealOne_18;
extern EvtScript TTYD64_imp_18_WMagikoopa_Script_Init_80225F58_18;
extern EvtScript TTYD64_imp_18_WMagikoopa_Script_TakeTurn_802274E4_18;
extern EvtScript TTYD64_imp_18_WMagikoopa_Script_WMagikoopa_ShapeSpell_18;
extern EvtScript TTYD64_imp_18_WMagikoopa_Script_WMagikoopa_WandStrike_18;
extern s32 TTYD64_imp_18_WMagikoopa_StatusTable_80223B38_18[];
extern ActorBlueprint TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa;
extern s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A1F0_1A[];
extern s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A23C_1A[];
extern s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A288_1A[];
extern s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A2D4_1A[];
extern s32 TTYD64_imp_1A_DarkKoopa_IdleAnimations_8021A320_1A[];
extern ActorPartBlueprint TTYD64_imp_1A_DarkKoopa_PartsTable_8021A1A4_1A[];
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_8021CB70_1A;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_DarkKoopa_DizzyAttack;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_DarkKoopa_ShellAttack;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_HandleEvent_8021AE4C_1A;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_Idle_8021A5E4_1A;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_Init_8021A36C_1A;
extern EvtScript TTYD64_imp_1A_DarkKoopa_Script_TakeTurn_8021D014_1A;
extern ActorBlueprint TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa;
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D450_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D49C_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D4E8_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F1F0_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F23C_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F288_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F2D4_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F320_1A[];
extern ActorPartBlueprint TTYD64_imp_1A_DarkParatroopa_PartsTable_8021D3BC_1A[];
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_8021EC2C_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_8021F36C_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_80221B70_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_DarkParatroopa_DizzyAttack;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Darkparatroopa_ShellAttack;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_HandleEvent_8021DA3C_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_HandleEvent_8021FE4C_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Idle_8021D6AC_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Idle_8021F5E4_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Init_8021D55C_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_TakeTurn_8021E174_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_TakeTurn_80222014_1A;
extern ActorBlueprint TTYD64_imp_1F_GRNMagikoopa_1F_GRNMagikoopa;
extern s32 TTYD64_imp_1F_GRNMagikoopa_IdleAnimations_802224F0_1F[];
extern ActorPartBlueprint TTYD64_imp_1F_GRNMagikoopa_PartsTable_80222410_1F[];
extern EvtScript TTYD64_imp_1F_GRNMagikoopa_Script_GRNMagikoopa_ShapeSpell_1F;
extern EvtScript TTYD64_imp_1F_GRNMagikoopa_Script_GRNMagikoopa_WandStrike_1F;
extern EvtScript TTYD64_imp_1F_GRNMagikoopa_Script_Init_802246D8_1F;
extern EvtScript TTYD64_imp_1F_GRNMagikoopa_Script_TakeTurn_80224820_1F;
extern s32 TTYD64_imp_1F_GRNMagikoopa_StatusTable_802222B8_1F[];
extern ActorBlueprint TTYD64_imp_1F_RMagikoopa_1F_RMagikoopa;
extern s32 TTYD64_imp_1F_RMagikoopa_IdleAnimations_8021F830_1F[];
extern ActorPartBlueprint TTYD64_imp_1F_RMagikoopa_PartsTable_8021F750_1F[];
extern EvtScript TTYD64_imp_1F_RMagikoopa_Script_Init_80221A18_1F;
extern EvtScript TTYD64_imp_1F_RMagikoopa_Script_RMagikoopa_ShapeSpell_1F;
extern EvtScript TTYD64_imp_1F_RMagikoopa_Script_RMagikoopa_WandStrike_1F;
extern EvtScript TTYD64_imp_1F_RMagikoopa_Script_TakeTurn_80221B60_1F;
extern ActorPartBlueprint TTYD64_omo3_hammer_bro_ActorParts[];
extern s32 TTYD64_omo3_hammer_bro_DefaultAnims[];
extern EvtScript TTYD64_omo3_hammer_bro_EVS_Attack_HammerSurge;
extern EvtScript TTYD64_omo3_hammer_bro_EVS_Attack_HammerThrow;
extern EvtScript TTYD64_omo3_hammer_bro_EVS_HammerSurge_Hit;
extern EvtScript TTYD64_omo3_hammer_bro_EVS_HammerSurge_Miss;
extern EvtScript TTYD64_omo3_hammer_bro_EVS_Init;
extern EvtScript TTYD64_omo3_hammer_bro_EVS_TakeTurn;
extern s32 TTYD64_omo3_hammer_bro_StatusTable[];
extern EvtScript TTYD64_imp_BoomerangBros_Script_ThrowBoomerang;
extern EvtScript TTYD64_imp_DarkCraw_Script_HandleEvent_DarkCraw;
extern EvtScript TTYD64_imp_DarkCraw_Script_Attack_SpearCharge;
extern EvtScript TTYD64_imp_BoomerangBros_Script_HandleEvent_8021E860_BoomerangBros_3D;
extern EvtScript TTYD64_imp_FireBros_Script_HandleEvent_8021E860_FireBros_3D;
extern EvtScript TTYD64_imp_FireBros_Script_ThrowFireBall;
extern EvtScript TTYD64_imp_DarkCraw_Script_Attack_SpearThrow;
extern EvtScript TTYD64_imp_FireBros_Script_FireBros_MultiFireBallAttack_Six;
extern EvtScript TTYD64_imp_FireBros_Script_FireBros_MultiFireBallAttack_Two;
extern EvtScript TTYD64_imp_BoomerangBros_Script_BoomerangBros_MultiBoomerangAttack;
extern EvtScript TTYD64_imp_FireBros_Script_FireBros_SingleFireBallAttack;
extern EvtScript TTYD64_imp_BoomerangBros_Script_BoomerangBros_SingleBoomerangAttack;
extern EvtScript TTYD64_imp_FireBros_Script_TakeTurn_8022028C_FireBros_3D;
extern s32 TTYD64_imp_BoomerangBros_StatusTable_8021E4F4_BoomerangBros_3D[];
extern s32 TTYD64_imp_FireBros_StatusTable_8021E4F4_FireBros_3D[];
extern EvtScript TTYD64_imp_BoomerangBros_Script_TakeTurn_8022028C_BoomerangBros_3D;
extern s32 TTYD64_imp_DarkCraw_StatusTable_DarkCraw[];
extern ActorPartBlueprint TTYD64_imp_FireBros_PartsTable_8021E5A0_FireBros_3D[];
extern ActorPartBlueprint TTYD64_imp_BoomerangBros_PartsTable_8021E5A0_BoomerangBros_3D[];
extern EvtScript TTYD64_imp_BoomerangBros_Script_Init_8021E6A0_BoomerangBros_3D;
extern Battle TTYD64_tyd_part_3_FormationTable[];
extern EvtScript TTYD64_imp_FireBros_Script_Init_8021E6A0_FireBros_3D;
extern EvtScript TTYD64_imp_DarkCraw_Script_TakeTurn_DarkCraw;
extern FormationRow TTYD64_tyd_part_3_Formation_00[];
extern FormationRow TTYD64_tyd_part_3_Formation_01[];
extern FormationRow TTYD64_tyd_part_3_Formation_02[];
extern EvtScript TTYD64_tyd_part_3_Script_BeforeBattle;
extern s32 TTYD64_imp_BoomerangBros_IdleAnimations_8021E490_BoomerangBros_3D[];
extern s32 TTYD64_imp_FireBros_IdleAnimations_8021E490_FireBros_3D[];
extern s32 TTYD64_imp_DarkCraw_IdleAnimations_DarkCraw[];
extern ActorPartBlueprint TTYD64_imp_DarkCraw_PartsTable_DarkCraw[];
extern EvtScript TTYD64_imp_DarkCraw_Script_Init_DarkCraw;
extern s32 TTYD64_imp_DarkCraw_IntTable_SpearRotation[];
extern ActorBlueprint TTYD64_imp_DarkCraw_3D_DarkCraw;
extern ActorBlueprint TTYD64_imp_FireBros_3D_FireBros;
extern Stage TTYD64_tyd_part_3_Stage_GlitzPit;
extern ActorBlueprint TTYD64_tyd_part_3_imp_12_HammerBros_12_HammerBros;
extern ActorBlueprint TTYD64_imp_BoomerangBros_3D_BoomerangBros;
extern FormationRow TTYD64_tyd_part_3_Formation_03[];
extern StageListRow TTYD64_tyd_part_3_StageTable[];
extern s32 TTYD64_imp_FireBros_IdleAnimations_8021E4DC_FireBros_3D[];
extern s32 TTYD64_imp_BoomerangBros_IdleAnimations_8021E4DC_BoomerangBros_3D[];
extern s32 TTYD64_imp_DarkCraw_IdleAnimations_Spear[];

// clang-format off
EvtScript TTYD64_imp_BoomerangBros_Script_ThrowBoomerang = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetPartPos, ACTOR_SELF, LVar8, 0, 50, 0)
        Call(SetPartFlagBits, ACTOR_SELF, LVar8, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x5A031D)
        Goto(100)
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 23)
    Add(LVar1, 23)
    Sub(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, LVar8, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A031D)
    Wait(8)
    Call(SetPartFlagBits, ACTOR_SELF, LVar8, 1, 0)
    Label(100)
    Thread
        Wait(15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x5A0303)
    EndThread
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, LVar8, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Else
        Call(SetPartScale, ACTOR_SELF, LVar8, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(SetPartSounds, ACTOR_SELF, LVar8, 2, 0, 0)
    Call(PlaySoundAtPart, ACTOR_SELF, LVar8, 719)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 100)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar8, Float(10.5))
    Call(SetPartJumpGravity, ACTOR_SELF, LVar8, Float(0.099609375))
    Thread
        Wait(12)
        Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
        Switch(LVarA)
            CaseOrEq(6)
            CaseOrEq(5)
                IfEq(LVarA, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
            EndCaseGroup
            CaseDefault
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, LVar9, 32)
        EndSwitch
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
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
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, LVar9, 32)
        EndSwitch
    EndThread
    Call(FlyPartTo, ACTOR_SELF, LVar8, LVar0, LVar1, LVar2, 0, -11, 10)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 23)
    Add(LVar1, 23)
    Sub(LVar2, 2)
    Thread
        Wait(6)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetOwnerTarget, LVar3, 0)
        IfEq(LVar3, 0)
            Call(GetPlayerHP, LVar3)
        Else
            Call(TTYD64_GetPartnerHP_API, LVar3)
        EndIf
        IfGt(LVar3, 0)
            Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
            Switch(LVarA)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarA, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                EndCaseGroup
                CaseDefault
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, LVar9, 32)
            EndSwitch
        EndIf
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
        Call(GetOwnerTarget, LVar3, 0)
        IfEq(LVar3, 0)
            Call(GetPlayerHP, LVar3)
        Else
            Call(TTYD64_GetPartnerHP_API, LVar3)
        EndIf
        IfGt(LVar3, 0)
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
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, LVar9, 32)
            EndSwitch
        EndIf
    EndThread
    Call(FlyPartTo, ACTOR_SELF, LVar8, LVar0, LVar1, LVar2, 0, 11, 10)
    Call(SetPartFlagBits, ACTOR_SELF, LVar8, 1, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A0321)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A0303)
    Wait(20)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkCraw_Script_HandleEvent_DarkCraw = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0108)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0109)
            SetConst(LVar2, 0xEA0109)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0109)
            SetConst(LVar2, 0xEA0109)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0109)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0108)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0108)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0108)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0108)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0108)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0102)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0101)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0108)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0108)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0101)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0108)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0108)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0101)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0102)
            SetConst(LVar2, 0xEA0108)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0108)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xEA0108)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0xEA0101)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkCraw_Script_Attack_SpearCharge = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0xEA0106)
    Wait(8)
    Call(SetAnimation, ACTOR_SELF, 1, 0xEA0107)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0102)
            Call(YieldTurn)
            Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0101)
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
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0xFFFF, 0, 6, 32)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0103)
            Call(PlaySoundAtActor, ACTOR_SELF, 8767)
            Wait(20)
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0xEA0101)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_BoomerangBros_Script_HandleEvent_8021E860_BoomerangBros_3D = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A031B)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A031B)
            SetConst(LVar2, 0x5A0310)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A031B)
            SetConst(LVar2, 0x5A0310)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0310)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A031B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A031B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A031B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0315)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x5A0317)
                Wait(10)
            EndIf
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A031B)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A031B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0303)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0307)
            SetConst(LVar2, 0x5A031B)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0307)
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
            SetConst(LVar1, 0x5A031B)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0303)
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
EvtScript TTYD64_imp_FireBros_Script_HandleEvent_8021E860_FireBros_3D = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A021B)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A021B)
            SetConst(LVar2, 0x5A0210)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A021B)
            SetConst(LVar2, 0x5A0210)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0210)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A021B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A021B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A021B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0215)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x5A0217)
                Wait(10)
            EndIf
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A021B)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A021B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0203)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0207)
            SetConst(LVar2, 0x5A021B)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0207)
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
            SetConst(LVar1, 0x5A021B)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x5A0203)
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
EvtScript TTYD64_imp_FireBros_Script_ThrowFireBall = {
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetPartPos, ACTOR_SELF, LVar8, 0, 50, 0)
        Call(SetPartFlagBits, ACTOR_SELF, LVar8, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x5A021D)
        Goto(100)
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 23)
    Add(LVar1, 23)
    Sub(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, LVar8, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A021D)
    Thread
        Wait(13)
        Call(SetAnimation, ACTOR_SELF, 1, 0x5A0203)
    EndThread
    Wait(6)
    Call(SetPartFlagBits, ACTOR_SELF, LVar8, 1, 0)
    Label(100)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, LVar8, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Else
        Call(SetPartScale, ACTOR_SELF, LVar8, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(SetPartSounds, ACTOR_SELF, LVar8, 2, 0, 0)
    Call(PlaySoundAtPart, ACTOR_SELF, LVar8, 751)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, 0)
    Call(GetDist2D, LVar3, LVar0, LVar1, LVar3, LVar4)
    Div(LVar3, 2)
    Add(LVar0, LVar3)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar8, Float(8.0))
    Call(SetPartJumpGravity, ACTOR_SELF, LVar8, Float(1.0))
    Call(JumpPartTo, ACTOR_SELF, LVar8, LVar0, 0, LVar2, 0, 1)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpPartTo, ACTOR_SELF, LVar8, LVar0, LVar1, LVar2, 0, 1)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000002, 0, 0, LVar9, 32)
    EndSwitch
    Call(SetPartFlagBits, ACTOR_SELF, LVar8, 1, 1)
    Wait(20)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkCraw_Script_Attack_SpearThrow = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0xEA0104)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0xEA0105)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 30)
    Add(LVar1, 54)
    Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, 61)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Thread
        UseBuf(Ref(TTYD64_imp_DarkCraw_IntTable_SpearRotation))
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
    Call(SetAnimation, ACTOR_SELF, 2, 0xEA010C)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(FlyPartTo, ACTOR_SELF, 2, LVar0, 0, LVar2, 0, 20, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0101)
            Wait(25)
            Return
        EndCaseGroup
    EndSwitch
    Call(FlyPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, 20, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0xEA0101)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0xFFFF, 0, 6, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0103)
            Call(PlaySoundAtActor, ACTOR_SELF, 8767)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0xEA0101)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FireBros_Script_FireBros_MultiFireBallAttack_Six = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    EndIf
    Set(LVar8, 2)
    Set(LVar9, 1)
    Exec(TTYD64_imp_FireBros_Script_ThrowFireBall)
    Wait(20)
    Set(LVar8, 3)
    Set(LVar9, 1)
    Exec(TTYD64_imp_FireBros_Script_ThrowFireBall)
    Wait(20)
    Set(LVar8, 2)
    Set(LVar9, 1)
    Exec(TTYD64_imp_FireBros_Script_ThrowFireBall)
    Wait(20)
    Set(LVar8, 3)
    Set(LVar9, 1)
    Exec(TTYD64_imp_FireBros_Script_ThrowFireBall)
    Wait(20)
    Set(LVar8, 2)
    Set(LVar9, 1)
    Exec(TTYD64_imp_FireBros_Script_ThrowFireBall)
    Wait(20)
    Set(LVar8, 3)
    Set(LVar9, 1)
    ExecWait(TTYD64_imp_FireBros_Script_ThrowFireBall)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A0203)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FireBros_Script_FireBros_MultiFireBallAttack_Two = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    EndIf
    Set(LVar8, 2)
    Set(LVar9, 2)
    Exec(TTYD64_imp_FireBros_Script_ThrowFireBall)
    Wait(20)
    Set(LVar8, 3)
    Set(LVar9, 2)
    ExecWait(TTYD64_imp_FireBros_Script_ThrowFireBall)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A0203)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_BoomerangBros_Script_BoomerangBros_MultiBoomerangAttack = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    EndIf
    Set(LVar8, 2)
    Set(LVar9, 1)
    Exec(TTYD64_imp_BoomerangBros_Script_ThrowBoomerang)
    Wait(35)
    Set(LVar8, 3)
    Set(LVar9, 1)
    ExecWait(TTYD64_imp_BoomerangBros_Script_ThrowBoomerang)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FireBros_Script_FireBros_SingleFireBallAttack = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    EndIf
    Set(LVar8, 2)
    Set(LVar9, 3)
    ExecWait(TTYD64_imp_FireBros_Script_ThrowFireBall)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A0203)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_BoomerangBros_Script_BoomerangBros_SingleBoomerangAttack = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    EndIf
    Set(LVar8, 2)
    Set(LVar9, 2)
    ExecWait(TTYD64_imp_BoomerangBros_Script_ThrowBoomerang)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_FireBros_Script_TakeTurn_8022028C_FireBros_3D = {
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
    MulF(LVar0, Float(100.0))
    DivF(LVar0, LVar1)
    Switch(LVar0)
        CaseGt(70)
            ExecWait(TTYD64_imp_FireBros_Script_FireBros_SingleFireBallAttack)
        CaseGt(34)
            ExecWait(TTYD64_imp_FireBros_Script_FireBros_MultiFireBallAttack_Two)
        CaseDefault
            ExecWait(TTYD64_imp_FireBros_Script_FireBros_MultiFireBallAttack_Six)
    EndSwitch
    Return
    End
};
// clang-format on

s32 TTYD64_imp_BoomerangBros_StatusTable_8021E4F4_BoomerangBros_3D[] = {
    1,  0, 2,  0,  6,  80, 9,  100, 7,  70, 4,  70, 3,  0, 11, 80, 5,  80, 10, 80, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,   36, -1, 35, 0,  33, 0, 38, 0,  39, 0,  41, -2, 0,
};

s32 TTYD64_imp_FireBros_StatusTable_8021E4F4_FireBros_3D[] = {
    1,  0, 2,  0,  6,  80, 9,  100, 7,  70, 4,  70, 3,  0, 11, 80, 5,  80, 10, 80, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,   36, -1, 35, 0,  33, 0, 38, 0,  39, 0,  41, -2, 0,
};

// clang-format off
EvtScript TTYD64_imp_BoomerangBros_Script_TakeTurn_8022028C_BoomerangBros_3D = {
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
    MulF(LVar0, Float(100.0))
    DivF(LVar0, LVar1)
    IfGt(LVar0, 34)
        ExecWait(TTYD64_imp_BoomerangBros_Script_BoomerangBros_SingleBoomerangAttack)
    Else
        ExecWait(TTYD64_imp_BoomerangBros_Script_BoomerangBros_MultiBoomerangAttack)
    EndIf
    Return
    End
};
// clang-format on

s32 TTYD64_imp_DarkCraw_StatusTable_DarkCraw[] = {
    1,  0, 6,  90, 9,  100, 7,  70, 4,  80, 11, 70, 5,  80, 10, 95, 8, 80,
    32, 0, 37, 0,  34, 0,   36, 0,  33, 0,  38, 0,  39, 0,  41, 0,  0,
};

ActorPartBlueprint TTYD64_imp_FireBros_PartsTable_8021E5A0_FireBros_3D[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -3, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_FireBros_IdleAnimations_8021E490_FireBros_3D,
        .defenseTable = b_area_kmr_part_3_egg_jr_troopa_DefenseTable,
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
        .idleAnimations = TTYD64_imp_FireBros_IdleAnimations_8021E4DC_FireBros_3D,
        .defenseTable = b_area_kmr_part_3_egg_jr_troopa_DefenseTable,
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
        .idleAnimations = TTYD64_imp_FireBros_IdleAnimations_8021E4DC_FireBros_3D,
        .defenseTable = b_area_kmr_part_3_egg_jr_troopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_BoomerangBros_PartsTable_8021E5A0_BoomerangBros_3D[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -3, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_BoomerangBros_IdleAnimations_8021E490_BoomerangBros_3D,
        .defenseTable = b_area_kmr_part_3_egg_jr_troopa_DefenseTable,
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
        .idleAnimations = TTYD64_imp_BoomerangBros_IdleAnimations_8021E4DC_BoomerangBros_3D,
        .defenseTable = b_area_kmr_part_3_egg_jr_troopa_DefenseTable,
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
        .idleAnimations = TTYD64_imp_BoomerangBros_IdleAnimations_8021E4DC_BoomerangBros_3D,
        .defenseTable = b_area_kmr_part_3_egg_jr_troopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_imp_BoomerangBros_Script_Init_8021E6A0_BoomerangBros_3D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_BoomerangBros_Script_TakeTurn_8022028C_BoomerangBros_3D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo3_hammer_bro_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_BoomerangBros_Script_HandleEvent_8021E860_BoomerangBros_3D))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

Battle TTYD64_tyd_part_3_FormationTable[] = {
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tyd_part_3_Formation_00,
      .stage = &TTYD64_tyd_part_3_Stage_GlitzPit,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tyd_part_3_Formation_01,
      .stage = &TTYD64_tyd_part_3_Stage_GlitzPit,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_tyd_part_3_Formation_02,
      .stage = &TTYD64_tyd_part_3_Stage_GlitzPit,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 1,
      .formation = (Formation*) TTYD64_tyd_part_3_Formation_03,
      .stage = &TTYD64_tyd_part_3_Stage_GlitzPit,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_imp_FireBros_Script_Init_8021E6A0_FireBros_3D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_FireBros_Script_TakeTurn_8022028C_FireBros_3D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo3_hammer_bro_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_FireBros_Script_HandleEvent_8021E860_FireBros_3D))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_DarkCraw_Script_TakeTurn_DarkCraw = {
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 50)
        ExecWait(TTYD64_imp_DarkCraw_Script_Attack_SpearThrow)
    Else
        ExecWait(TTYD64_imp_DarkCraw_Script_Attack_SpearCharge)
    EndIf
    Return
    End
};
// clang-format on

FormationRow TTYD64_tyd_part_3_Formation_00[] = {
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_1A_DarkKoopa_1A_DarkKoopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_tyd_part_3_Formation_01[] = {
    { .actor = &TTYD64_imp_1F_RMagikoopa_1F_RMagikoopa,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_1F_GRNMagikoopa_1F_GRNMagikoopa,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_18_WMagikoopa_18_WMagikoopa,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_tyd_part_3_Formation_02[] = {
    { .actor = &TTYD64_tyd_part_3_imp_12_HammerBros_12_HammerBros,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_FireBros_3D_FireBros,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_BoomerangBros_3D_BoomerangBros,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

// clang-format off
EvtScript TTYD64_tyd_part_3_Script_BeforeBattle = {
    Call(SetSpriteShading, -1)
    Call(SetCamBGColor, 1, 0, 0, 0)
    Call(EnableModel, 59, 0)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_BoomerangBros_IdleAnimations_8021E490_BoomerangBros_3D[] = {
    1,  0x5A0303, 7, 0x5A0300, 6, 0x5A0311, 9, 0x5A0303, 8, 0x5A0300,
    11, 0x5A0303, 5, 0x5A0300, 4, 0x5A0312, 3, 0x5A0312, 0,
};

s32 TTYD64_imp_FireBros_IdleAnimations_8021E490_FireBros_3D[] = {
    1,  0x5A0203, 7, 0x5A0200, 6, 0x5A0211, 9, 0x5A0203, 8, 0x5A0200,
    11, 0x5A0203, 5, 0x5A0200, 4, 0x5A0212, 3, 0x5A0212, 0,
};

s32 TTYD64_imp_DarkCraw_IdleAnimations_DarkCraw[] = {
    1,  0xEA0101, 7, 0xEA0100, 6, 0xEA010A, 9, 0xEA010D, 8, 0xEA0100,
    11, 0xEA0100, 5, 0xEA0100, 4, 0xEA010B, 3, 0xEA0100, 0,
};

ActorPartBlueprint TTYD64_imp_DarkCraw_PartsTable_DarkCraw[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -7, 37 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_DarkCraw_IdleAnimations_DarkCraw,
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
        .idleAnimations = TTYD64_imp_DarkCraw_IdleAnimations_Spear,
        .defenseTable = b_area_kmr_part_1_goomba_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_imp_DarkCraw_Script_Init_DarkCraw = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_DarkCraw_Script_TakeTurn_DarkCraw))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_DarkCraw_Script_HandleEvent_DarkCraw))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_DarkCraw_IntTable_SpearRotation[] = {
    62, 68, 72, 76, 80, 84, 90, 90, 94, 101, 107,
};

ActorBlueprint TTYD64_imp_DarkCraw_3D_DarkCraw = {
    .flags = 0x0,
    .maxHP = 20,
    .type = 0x78,
    .level = 16,
    .partCount = 2,
    .partsData = TTYD64_imp_DarkCraw_PartsTable_DarkCraw,
    .initScript = &TTYD64_imp_DarkCraw_Script_Init_DarkCraw,
    .statusTable = TTYD64_imp_DarkCraw_StatusTable_DarkCraw,
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

ActorBlueprint TTYD64_imp_FireBros_3D_FireBros = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x68,
    .level = 13,
    .partCount = 3,
    .partsData = TTYD64_imp_FireBros_PartsTable_8021E5A0_FireBros_3D,
    .initScript = &TTYD64_imp_FireBros_Script_Init_8021E6A0_FireBros_3D,
    .statusTable = TTYD64_imp_FireBros_StatusTable_8021E4F4_FireBros_3D,
    .escapeChance = 50,
    .airLiftChance = 60,
    .hurricaneChance = 70,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 0,
    .size = { 28, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 35 },
};

Stage TTYD64_tyd_part_3_Stage_GlitzPit = {
    .texture = "tst_tex",
    .shape = "tyd_bt04_shape",
    .hit = "tyd_bt04_hit",
    .preBattle = &TTYD64_tyd_part_3_Script_BeforeBattle,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_tyd_part_3_imp_12_HammerBros_12_HammerBros = {
    .flags = 0x0,
    .maxHP = 12,
    .type = 0x4B,
    .level = 27,
    .partCount = 6,
    .partsData = TTYD64_omo3_hammer_bro_ActorParts,
    .initScript = &TTYD64_omo3_hammer_bro_EVS_Init,
    .statusTable = TTYD64_omo3_hammer_bro_StatusTable,
    .escapeChance = 30,
    .airLiftChance = 75,
    .hurricaneChance = 60,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 28, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 35 },
};

ActorBlueprint TTYD64_imp_BoomerangBros_3D_BoomerangBros = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x6C,
    .level = 13,
    .partCount = 3,
    .partsData = TTYD64_imp_BoomerangBros_PartsTable_8021E5A0_BoomerangBros_3D,
    .initScript = &TTYD64_imp_BoomerangBros_Script_Init_8021E6A0_BoomerangBros_3D,
    .statusTable = TTYD64_imp_BoomerangBros_StatusTable_8021E4F4_BoomerangBros_3D,
    .escapeChance = 50,
    .airLiftChance = 60,
    .hurricaneChance = 70,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 0,
    .size = { 28, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 35 },
};

FormationRow TTYD64_tyd_part_3_Formation_03[] = {
    { .actor = &TTYD64_imp_DarkCraw_3D_DarkCraw,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

StageListRow TTYD64_tyd_part_3_StageTable[] = {
    { .name = "tyd_03", .stage = &TTYD64_tyd_part_3_Stage_GlitzPit },
    {},
};

s32 TTYD64_imp_FireBros_IdleAnimations_8021E4DC_FireBros_3D[] = {
    1,
    0x5A0F20,
    0,
};

s32 TTYD64_imp_BoomerangBros_IdleAnimations_8021E4DC_BoomerangBros_3D[] = {
    1,
    0x5A0E1E,
    0,
};

s32 TTYD64_imp_DarkCraw_IdleAnimations_Spear[] = {
    1,
    0xEA010C,
    0,
};

void TTYD64_InstallBattles_tyd_part_3(void) {
    Mod_SetBattleList("TTYD64", 0x3D, TTYD64_tyd_part_3_FormationTable);
    Mod_SetStageList("TTYD64", 0x3D, TTYD64_tyd_part_3_StageTable);
}
