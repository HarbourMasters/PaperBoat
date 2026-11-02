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

extern EvtScript b_area_isk_part_1_pokey_mummy_EVS_Idle;
extern s32 b_area_iwa_cleft_StatusTable[];
extern EvtScript b_area_iwa_monty_mole_EVS_HandleEvent;
extern EvtScript b_area_iwa_monty_mole_EVS_Idle;
extern s32 b_area_iwa_monty_mole_StatusTable[];
extern EvtScript b_area_kmr_part_1_kmr_02_EVS_PostBattle;
extern EvtScript b_area_kmr_part_3_kpa_13_EVS_PreBattle;
extern FormationRow b_area_sbk_bandit_CoinFormation[];
extern u8 b_area_sbk_bandit_DropCoinScript[];
extern s32 b_area_sbk_bandit_StatusTable[];
extern EvtScript b_area_sbk_pokey_EVS_Idle;
API_CALLABLE(AddCoin);
API_CALLABLE(AddVectorPolar);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(EnableActorBlur);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyPartTo);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartOffset);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToHome);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActor);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetGoalPos);
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
extern ActorBlueprint TTYD64_imp_1A_Paragloomba_1A_Paragloomba;
extern s32 TTYD64_imp_1A_Paragloomba_IdleAnimations_80225938_1A[];
extern s32 TTYD64_imp_1A_Paragloomba_IdleAnimations_80225984_1A[];
extern s32 TTYD64_imp_1A_Paragloomba_IdleAnimations_802270FC_1A[];
extern s32 TTYD64_imp_1A_Paragloomba_IdleAnimations_80227148_1A[];
extern ActorPartBlueprint TTYD64_imp_1A_Paragloomba_PartsTable_80225880_1A[];
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_80226B74_1A;
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_80227194_1A;
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_HandleEvent_80225D68_1A;
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_HandleEvent_802274BC_1A;
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_Idle_80225A34_1A;
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_Idle_802271E0_1A;
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_Init_802259E8_1A;
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_TakeTurn_8022635C_1A;
extern EvtScript TTYD64_imp_1A_Paragloomba_Script_TakeTurn_80227CE8_1A;
extern EvtScript TTYD64_isk_part_1_EVS_8021D150;
extern EvtScript TTYD64_isk_part_1_EVS_802230D4;
extern EvtScript TTYD64_isk_part_1_EVS_80223E64;
extern Vec3i TTYD64_isk_part_1_Pos_802265EC;
extern ActorPartBlueprint TTYD64_isk_part_1_pokey_mummy_ActorParts[];
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_Attack_SinglePartLeap;
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_DecrementSize;
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_HandleEvent;
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_KnockPartAway;
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_Hit;
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_ScareAway;
extern EvtScript TTYD64_isk_part_1_pokey_mummy_EVS_Pokey_SpinSmashHit;
extern s32 TTYD64_isk_part_1_pokey_mummy_FourPartAnims[];
extern s32 TTYD64_isk_part_1_pokey_mummy_OnePartAnims[];
extern s32 TTYD64_isk_part_1_pokey_mummy_StatusTable[];
extern s32 TTYD64_isk_part_1_pokey_mummy_ThreePartAnims[];
extern s32 TTYD64_isk_part_1_pokey_mummy_TwoPartAnims[];
extern ActorPartBlueprint TTYD64_iwa_cleft_ActorParts[];
extern EvtScript TTYD64_iwa_cleft_EVS_Attack_Tackle;
extern EvtScript TTYD64_iwa_cleft_EVS_FlipOver;
extern EvtScript TTYD64_iwa_cleft_EVS_HandleEvent;
extern EvtScript TTYD64_iwa_cleft_EVS_Init;
extern EvtScript TTYD64_iwa_cleft_EVS_TakeTurn;
extern EvtScript TTYD64_iwa_cleft_EVS_TryGettingUp;
extern s32 TTYD64_iwa_cleft_ToppledAnims[];
extern s32 TTYD64_iwa_cleft_UprightAnims[];
extern ActorPartBlueprint TTYD64_iwa_monty_mole_ActorParts[];
extern s32 TTYD64_iwa_monty_mole_DefaultAnims[];
extern EvtScript TTYD64_iwa_monty_mole_EVS_TakeTurn;
extern ActorPartBlueprint TTYD64_sbk_bandit_ActorParts[];
extern s32 TTYD64_sbk_bandit_DefaultAnims[];
extern EvtScript TTYD64_sbk_bandit_EVS_TakeTurn;
extern s32 TTYD64_sbk_bandit_HoldingAnims[];
extern EvtScript TTYD64_pit_part_2_imp_0B_PokeyMummy_Script_TakeTurn_8021A018_0B;
extern EvtScript TTYD64_pit_part_2_imp_0A_BanditA_Script_HandleEvent_8021DF88_0A;
extern EvtScript TTYD64_pit_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack;
extern EvtScript TTYD64_pit_part_2_imp_0B_PokeyMummy_Script_PokeyMummy_SummonPokeyMummy_0B;
extern EvtScript TTYD64_pit_part_2_imp_0B_PokeyMummy_Script_Init_80218534_0B;
extern Battle TTYD64_pit_part_2_FormationTable[];
extern EvtScript TTYD64_pit_part_2_Script_BeforeBattle_Pit;
extern FormationRow TTYD64_pit_part_2_Formation_Pit12_17_3[];
extern FormationRow TTYD64_pit_part_2_Formation_Pit15_2[];
extern FormationRow TTYD64_pit_part_2_Formation_Pit15_3[];
extern FormationRow TTYD64_pit_part_2_Formation_Pit13_18_3[];
extern FormationRow TTYD64_pit_part_2_Formation_Pit13_18_2[];
extern EvtScript TTYD64_pit_part_2_imp_09_MontyMole_Script_Init_8021A7B0_09;
extern EvtScript TTYD64_pit_part_2_imp_0A_BanditA_Script_Init_8021D750_0A;
extern FormationRow TTYD64_pit_part_2_Formation_Pit12_17_2[];
extern FormationRow TTYD64_pit_part_2_Formation_Pit11_16_3[];
extern FormationRow TTYD64_pit_part_2_Formation_Pit11_16_2[];
extern FormationRow TTYD64_pit_part_2_Formation_Pit14_19_2[];
extern FormationRow TTYD64_pit_part_2_Formation_Pit14_19_3[];
extern FormationRow TTYD64_pit_part_2_Formation_Pit12_17_1[];
extern FormationRow TTYD64_pit_part_2_Formation_Pit11_16_1[];
extern FormationRow TTYD64_pit_part_2_Formation_Pit15_1[];
extern FormationRow TTYD64_pit_part_2_Formation_Pit13_18_1[];
extern FormationRow TTYD64_pit_part_2_Formation_Pit14_19_1[];
extern ActorBlueprint TTYD64_pit_part_2_imp_0B_PokeyMummy_PokeyMummy_0B;
extern ActorBlueprint TTYD64_pit_part_2_imp_0A_BanditA_0A_BanditA;
extern ActorBlueprint TTYD64_pit_part_2_imp_09_Cleft_09_Cleft;
extern ActorBlueprint TTYD64_pit_part_2_imp_0B_PokeyMummy_0B_PokeyMummy;
extern Stage TTYD64_pit_part_2_Stage_Pit1;
extern Stage TTYD64_pit_part_2_Stage_Pit2;
extern ActorBlueprint TTYD64_pit_part_2_imp_09_MontyMole_09_MontyMole;
extern FormationRow TTYD64_pit_part_2_imp_0B_PokeyMummy_SpecialFormation_8021AE10_0B[];
extern StageListRow TTYD64_pit_part_2_StageTable[];

// clang-format off
EvtScript TTYD64_pit_part_2_imp_0B_PokeyMummy_Script_TakeTurn_8021A018_0B = {
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfEq(LVarA, 3)
        ExecWait(TTYD64_isk_part_1_EVS_8021D150)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 9, LVar0)
    IfEq(LVar0, 0)
        Call(GetActorVar, ACTOR_SELF, 10, LVar0)
        IfEq(LVar0, 2)
            Goto(123)
        EndIf
        ExecWait(TTYD64_isk_part_1_EVS_802230D4)
        IfEq(LVarE, -1)
            Goto(123)
        EndIf
        ExecWait(TTYD64_isk_part_1_EVS_80223E64)
        Switch(LVar9)
            CaseEq(1)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 400)
                    ExecWait(TTYD64_pit_part_2_imp_0B_PokeyMummy_Script_PokeyMummy_SummonPokeyMummy_0B)
                    Return
                EndIf
            CaseEq(2)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 200)
                    ExecWait(TTYD64_pit_part_2_imp_0B_PokeyMummy_Script_PokeyMummy_SummonPokeyMummy_0B)
                    Return
                EndIf
            CaseEq(3)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 100)
                    ExecWait(TTYD64_pit_part_2_imp_0B_PokeyMummy_Script_PokeyMummy_SummonPokeyMummy_0B)
                    Return
                EndIf
        EndSwitch
    EndIf
    Label(123)
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 500)
        ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_Attack_SinglePartLeap)
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
        Call(SetAnimation, ACTOR_SELF, 6, 0x310116)
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
    ExecWait(TTYD64_isk_part_1_pokey_mummy_EVS_DecrementSize)
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
            Call(SetAnimation, ACTOR_SELF, 6, 0x310116)
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
    Call(SetAnimation, ACTOR_SELF, 6, 0x310116)
    Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 1)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, -0x7FFDFCD8, 3, 32)
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
EvtScript TTYD64_pit_part_2_imp_0A_BanditA_Script_HandleEvent_8021DF88_0A = {
    UseArray(Ref(b_area_sbk_bandit_DropCoinScript))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            ExecGetTID(TTYD64_pit_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_pit_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_pit_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_pit_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_pit_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_pit_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_pit_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_pit_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_pit_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
EvtScript TTYD64_pit_part_2_imp_0A_BanditA_Script_Bandit_GetCoinBack = {
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
EvtScript TTYD64_pit_part_2_imp_0B_PokeyMummy_Script_PokeyMummy_SummonPokeyMummy_0B = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x310104)
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
    Call(SummonEnemy, Ref(TTYD64_pit_part_2_imp_0B_PokeyMummy_SpecialFormation_8021AE10_0B), 0)
    Set(LVarB, LVar0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Sub(LVar1, 80)
    Call(SetActorPos, LVarB, LVar0, LVar1, LVar2)
    ChildThread
        Call(PlayEffect_impl, 37, 2, LVar0, 0, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(UseIdleAnimation, LVarB, 0)
        Call(SetAnimation, LVarB, 1, 0x31010C)
        Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
        Call(SetActorJumpGravity, LVarB, Float(1.2001953125))
        Call(SetGoalPos, LVarB, LVar0, 0, LVar2)
        Call(JumpToGoal, LVarB, 20, 0, 1, 0)
        Wait(20)
        Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
        Call(SetAnimation, LVarB, 1, 0x310104)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x310104)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_pit_part_2_imp_0B_PokeyMummy_Script_Init_80218534_0B = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_pit_part_2_imp_0B_PokeyMummy_Script_TakeTurn_8021A018_0B))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_isk_part_1_pokey_mummy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_isk_part_1_pokey_mummy_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Call(SetActorVar, ACTOR_SELF, 9, LVar0)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0x310104)
    Call(SetActorVar, ACTOR_SELF, 2, 0x310108)
    Call(SetActorVar, ACTOR_SELF, 3, 0x31010C)
    Call(SetActorVar, ACTOR_SELF, 4, 0x310110)
    Call(SetActorVar, ACTOR_SELF, 5, 0x310111)
    Call(SetActorVar, ACTOR_SELF, 6, 0x310118)
    Call(SetActorVar, ACTOR_SELF, 7, 0x310119)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

Battle TTYD64_pit_part_2_FormationTable[] = {
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_2_Formation_Pit11_16_1,
      .stage = &TTYD64_pit_part_2_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_2_Formation_Pit11_16_2,
      .stage = &TTYD64_pit_part_2_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_2_Formation_Pit11_16_3,
      .stage = &TTYD64_pit_part_2_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_2_Formation_Pit12_17_1,
      .stage = &TTYD64_pit_part_2_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_2_Formation_Pit12_17_2,
      .stage = &TTYD64_pit_part_2_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_2_Formation_Pit12_17_3,
      .stage = &TTYD64_pit_part_2_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_2_Formation_Pit13_18_1,
      .stage = &TTYD64_pit_part_2_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_2_Formation_Pit13_18_2,
      .stage = &TTYD64_pit_part_2_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_2_Formation_Pit13_18_3,
      .stage = &TTYD64_pit_part_2_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_2_Formation_Pit14_19_1,
      .stage = &TTYD64_pit_part_2_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_2_Formation_Pit14_19_2,
      .stage = &TTYD64_pit_part_2_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_2_Formation_Pit14_19_3,
      .stage = &TTYD64_pit_part_2_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_2_Formation_Pit15_1,
      .stage = &TTYD64_pit_part_2_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_2_Formation_Pit15_2,
      .stage = &TTYD64_pit_part_2_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_2_Formation_Pit15_3,
      .stage = &TTYD64_pit_part_2_Stage_Pit1,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_pit_part_2_Script_BeforeBattle_Pit = {
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

FormationRow TTYD64_pit_part_2_Formation_Pit12_17_3[] = {
    { .actor = &TTYD64_pit_part_2_imp_09_MontyMole_09_MontyMole,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_pit_part_2_imp_09_MontyMole_09_MontyMole,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_pit_part_2_imp_09_MontyMole_09_MontyMole,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_pit_part_2_imp_09_MontyMole_09_MontyMole,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
};

FormationRow TTYD64_pit_part_2_Formation_Pit15_2[] = {
    { .actor = &TTYD64_pit_part_2_imp_0B_PokeyMummy_0B_PokeyMummy,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_pit_part_2_imp_09_MontyMole_09_MontyMole,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_pit_part_2_imp_0B_PokeyMummy_0B_PokeyMummy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_pit_part_2_imp_09_MontyMole_09_MontyMole,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
};

FormationRow TTYD64_pit_part_2_Formation_Pit15_3[] = {
    { .actor = &TTYD64_pit_part_2_imp_0B_PokeyMummy_0B_PokeyMummy,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_pit_part_2_imp_0B_PokeyMummy_0B_PokeyMummy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_pit_part_2_imp_0B_PokeyMummy_0B_PokeyMummy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_pit_part_2_imp_0B_PokeyMummy_0B_PokeyMummy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
};

FormationRow TTYD64_pit_part_2_Formation_Pit13_18_3[] = {
    { .actor = &TTYD64_pit_part_2_imp_09_Cleft_09_Cleft,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
    { .actor = &TTYD64_pit_part_2_imp_09_Cleft_09_Cleft,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
    { .actor = &TTYD64_pit_part_2_imp_09_Cleft_09_Cleft,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
    { .actor = &TTYD64_pit_part_2_imp_09_Cleft_09_Cleft,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
};

FormationRow TTYD64_pit_part_2_Formation_Pit13_18_2[] = {
    { .actor = &TTYD64_pit_part_2_imp_09_Cleft_09_Cleft,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
    { .actor = &TTYD64_pit_part_2_imp_09_MontyMole_09_MontyMole,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_pit_part_2_imp_09_MontyMole_09_MontyMole,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_pit_part_2_imp_09_Cleft_09_Cleft,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
};

// clang-format off
EvtScript TTYD64_pit_part_2_imp_09_MontyMole_Script_Init_8021A7B0_09 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_iwa_monty_mole_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_iwa_monty_mole_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_iwa_monty_mole_EVS_HandleEvent))
    Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_pit_part_2_imp_0A_BanditA_Script_Init_8021D750_0A = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_sbk_bandit_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sbk_pokey_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_pit_part_2_imp_0A_BanditA_Script_HandleEvent_8021DF88_0A))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pit_part_2_Formation_Pit12_17_2[] = {
    { .actor = &TTYD64_pit_part_2_imp_09_MontyMole_09_MontyMole,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_pit_part_2_imp_0B_PokeyMummy_0B_PokeyMummy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_pit_part_2_imp_0A_BanditA_0A_BanditA,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
};

FormationRow TTYD64_pit_part_2_Formation_Pit11_16_3[] = {
    { .actor = &TTYD64_imp_1A_Paragloomba_1A_Paragloomba,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGLOOMBA },
    { .actor = &TTYD64_pit_part_2_imp_09_MontyMole_09_MontyMole,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_pit_part_2_imp_09_MontyMole_09_MontyMole,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
};

FormationRow TTYD64_pit_part_2_Formation_Pit11_16_2[] = {
    { .actor = &TTYD64_imp_1A_Paragloomba_1A_Paragloomba,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGLOOMBA },
    { .actor = &TTYD64_pit_part_2_imp_0B_PokeyMummy_0B_PokeyMummy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_pit_part_2_imp_0B_PokeyMummy_0B_PokeyMummy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
};

FormationRow TTYD64_pit_part_2_Formation_Pit14_19_2[] = {
    { .actor = &TTYD64_pit_part_2_imp_0A_BanditA_0A_BanditA,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_pit_part_2_imp_0B_PokeyMummy_0B_PokeyMummy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_pit_part_2_imp_0A_BanditA_0A_BanditA,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
};

FormationRow TTYD64_pit_part_2_Formation_Pit14_19_3[] = {
    { .actor = &TTYD64_pit_part_2_imp_0A_BanditA_0A_BanditA,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_pit_part_2_imp_0A_BanditA_0A_BanditA,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_pit_part_2_imp_0A_BanditA_0A_BanditA,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
};

FormationRow TTYD64_pit_part_2_Formation_Pit12_17_1[] = {
    { .actor = &TTYD64_pit_part_2_imp_09_MontyMole_09_MontyMole,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_imp_1A_Paragloomba_1A_Paragloomba,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGLOOMBA },
};

FormationRow TTYD64_pit_part_2_Formation_Pit11_16_1[] = {
    { .actor = &TTYD64_imp_1A_Paragloomba_1A_Paragloomba,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGLOOMBA },
    { .actor = &TTYD64_imp_1A_Paragloomba_1A_Paragloomba,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGLOOMBA },
};

FormationRow TTYD64_pit_part_2_Formation_Pit15_1[] = {
    { .actor = &TTYD64_pit_part_2_imp_0B_PokeyMummy_0B_PokeyMummy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
    { .actor = &TTYD64_imp_1A_Paragloomba_1A_Paragloomba,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGLOOMBA },
};

FormationRow TTYD64_pit_part_2_Formation_Pit13_18_1[] = {
    { .actor = &TTYD64_pit_part_2_imp_09_Cleft_09_Cleft,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CLEFT },
    { .actor = &TTYD64_pit_part_2_imp_0B_PokeyMummy_0B_PokeyMummy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEYMUMMY },
};

FormationRow TTYD64_pit_part_2_Formation_Pit14_19_1[] = {
    { .actor = &TTYD64_pit_part_2_imp_0A_BanditA_0A_BanditA,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_imp_1A_Paragloomba_1A_Paragloomba,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARAGLOOMBA },
};

ActorBlueprint TTYD64_pit_part_2_imp_0B_PokeyMummy_PokeyMummy_0B = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x15,
    .level = 10,
    .partCount = 6,
    .partsData = TTYD64_isk_part_1_pokey_mummy_ActorParts,
    .initScript = &TTYD64_pit_part_2_imp_0B_PokeyMummy_Script_Init_80218534_0B,
    .statusTable = TTYD64_isk_part_1_pokey_mummy_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 90,
    .hurricaneChance = 85,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 1,
    .size = { 24, 80 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 75 },
    .statusTextOffset = { 10, 65 },
};

ActorBlueprint TTYD64_pit_part_2_imp_0A_BanditA_0A_BanditA = {
    .flags = 0x0,
    .maxHP = 5,
    .type = 0x13,
    .level = 9,
    .partCount = 2,
    .partsData = TTYD64_sbk_bandit_ActorParts,
    .initScript = &TTYD64_pit_part_2_imp_0A_BanditA_Script_Init_8021D750_0A,
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

ActorBlueprint TTYD64_pit_part_2_imp_09_Cleft_09_Cleft = {
    .flags = 0x0,
    .maxHP = 2,
    .type = 0x11,
    .level = 10,
    .partCount = 1,
    .partsData = TTYD64_iwa_cleft_ActorParts,
    .initScript = &TTYD64_iwa_cleft_EVS_Init,
    .statusTable = b_area_iwa_cleft_StatusTable,
    .escapeChance = 80,
    .airLiftChance = 40,
    .hurricaneChance = 40,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 2,
    .size = { 44, 36 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_pit_part_2_imp_0B_PokeyMummy_0B_PokeyMummy = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x15,
    .level = 10,
    .partCount = 6,
    .partsData = TTYD64_isk_part_1_pokey_mummy_ActorParts,
    .initScript = &TTYD64_pit_part_2_imp_0B_PokeyMummy_Script_Init_80218534_0B,
    .statusTable = TTYD64_isk_part_1_pokey_mummy_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 90,
    .hurricaneChance = 85,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 1,
    .size = { 24, 80 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 75 },
    .statusTextOffset = { 10, 65 },
};

Stage TTYD64_pit_part_2_Stage_Pit1 = {
    .texture = "tik_tex",
    .shape = "pit_bt01_shape",
    .hit = "pit_bt01_hit",
    .preBattle = &TTYD64_pit_part_2_Script_BeforeBattle_Pit,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

Stage TTYD64_pit_part_2_Stage_Pit2 = {
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

ActorBlueprint TTYD64_pit_part_2_imp_09_MontyMole_09_MontyMole = {
    .flags = 0x0,
    .maxHP = 3,
    .type = 0x12,
    .level = 8,
    .partCount = 3,
    .partsData = TTYD64_iwa_monty_mole_ActorParts,
    .initScript = &TTYD64_pit_part_2_imp_09_MontyMole_Script_Init_8021A7B0_09,
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

FormationRow TTYD64_pit_part_2_imp_0B_PokeyMummy_SpecialFormation_8021AE10_0B[] = {
    { .actor = &TTYD64_pit_part_2_imp_0B_PokeyMummy_PokeyMummy_0B,
      .home = { .vec = &TTYD64_isk_part_1_Pos_802265EC },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

StageListRow TTYD64_pit_part_2_StageTable[] = {
    { .name = "pit_01", .stage = &TTYD64_pit_part_2_Stage_Pit1 },
    { .name = "pit_12", .stage = &TTYD64_pit_part_2_Stage_Pit2 },
    {},
};

void TTYD64_InstallBattles_pit_part_2(void) {
    Mod_SetBattleList("TTYD64", 0x31, TTYD64_pit_part_2_FormationTable);
    Mod_SetStageList("TTYD64", 0x31, TTYD64_pit_part_2_StageTable);
}
