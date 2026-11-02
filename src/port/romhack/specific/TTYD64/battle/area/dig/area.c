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
#include "port/romhack/specific/TTYD64/battle/area/battles_b.h"
#include "port/romhack/specific/TTYD64/battle/area/battles_b_imports.h"

API_CALLABLE(b_area_dig_fuzzy_SpawnDrainHealthContinueFX);
API_CALLABLE(b_area_dig_fuzzy_SpawnDrainHealthStartFX);
API_CALLABLE(b_area_dig_pokey_SetAbsoluteStatusOffsets);
extern s32 b_area_dig_bandit_CoinAnims[];
extern FormationRow b_area_dig_bandit_CoinFormation[];
extern s32 b_area_dig_bandit_DefenseTable[];
extern u8 b_area_dig_bandit_DropCoinScript[];
extern EvtScript b_area_dig_bandit_EVS_Idle;
extern s32 b_area_dig_bandit_StatusTable[];
extern Stage b_area_dig_dgb_05;
extern EvtScript b_area_dig_dig_01_script;
extern EvtScript b_area_dig_dig_02_script;
extern EvtScript b_area_dig_dig_03_script;
extern EvtScript b_area_dig_dig_04_script;
extern EvtScript b_area_dig_dig_05_script;
extern s32 b_area_dig_fuzzy_DefenseTable[];
extern EvtScript b_area_dig_fuzzy_EVS_Idle;
extern s32 b_area_dig_fuzzy_StatusTable[];
extern Stage b_area_dig_iwa_01b;
extern s32 b_area_dig_monty_mole_DefenseTable[];
extern EvtScript b_area_dig_monty_mole_EVS_HandleEvent;
extern EvtScript b_area_dig_monty_mole_EVS_Idle;
extern s32 b_area_dig_monty_mole_RockAnims[];
extern s32 b_area_dig_monty_mole_StatusTable[];
extern Stage b_area_dig_nok_04;
extern Stage b_area_dig_omo_04;
extern s32 b_area_dig_pokey_DefenseTable[];
extern EvtScript b_area_dig_pokey_EVS_CountSummonerPokeys;
extern EvtScript b_area_dig_pokey_EVS_FindValidSummonPosition;
extern EvtScript b_area_dig_pokey_EVS_HitReactionBounce;
extern EvtScript b_area_dig_pokey_EVS_Idle;
extern Vec3i b_area_dig_pokey_SummonPos;
extern s32 b_area_dig_pokey_ThrownPartAnims[];
extern s32 b_area_dig_red_shy_guy_DefenseTable[];
extern EvtScript b_area_dig_red_shy_guy_EVS_HandleEvent;
extern EvtScript b_area_dig_red_shy_guy_EVS_Idle;
extern EvtScript b_area_dig_red_shy_guy_EVS_ReturnHome;
extern Stage b_area_dig_sbk_02;
extern s32 b_area_dig_tubba_blubba_DefenseTable[];
extern EvtScript b_area_dig_tubba_blubba_EVS_HandleEvent;
extern EvtScript b_area_dig_tubba_blubba_EVS_HandlePhase;
extern EvtScript b_area_dig_tubba_blubba_EVS_Idle;
extern EvtScript b_area_dig_tubba_blubba_EVS_PlayFootstepQuaking;
extern EvtScript b_area_dig_tubba_blubba_EVS_ReturnHome;
extern s32 b_area_dig_tubba_blubba_StatusTable[];
extern EvtScript TTYD64_imp_27_Fuzzy_Script_TakeTurn_8021B230_27;
extern EvtScript TTYD64_imp_27_BanditA_Script_TakeTurn_80222950_27;
extern EvtScript TTYD64_imp_27_Pokey_Script_HandleEvent_802186C0_0A;
extern EvtScript TTYD64_imp_27_TubbaBlubba_Script_8022614C_27;
extern EvtScript TTYD64_imp_27_ShyGuy_Script_8022468C_27;
extern EvtScript TTYD64_imp_27_Pokey_Script_TakeTurn_8021A018_0A;
extern EvtScript TTYD64_imp_27_Pokey_Script_802193B8_0A;
extern EvtScript TTYD64_imp_27_Pokey_Script_8021B590_0A;
extern EvtScript TTYD64_imp_27_BanditA_Script_HandleEvent_80221FD8_27;
extern EvtScript TTYD64_imp_27_BanditA_Script_Bandit_GetCoinBack;
extern EvtScript TTYD64_imp_27_Pokey_Script_8021AE2C_0A;
extern EvtScript TTYD64_imp_27_ShyGuy_Script_80223F64_27;
extern EvtScript TTYD64_imp_27_MontyMole_Script_TakeTurn_802278AC_27;
extern EvtScript TTYD64_imp_27_Fuzzy_Script_HandleEvent_8021ABCC_27;
extern EvtScript TTYD64_imp_27_TubbaBlubba_Script_TakeTurn_802256A0_27;
extern EvtScript TTYD64_imp_27_Pokey_Script_8021C07C_0A;
extern EvtScript TTYD64_imp_27_Pokey_Script_8021CCAC_0A;
extern EvtScript TTYD64_imp_27_Pokey_Script_8021C860_0A;
extern EvtScript TTYD64_imp_27_Pokey_Script_8021D184_0A;
extern EvtScript TTYD64_imp_27_Pokey_Script_Init_80218534_0A;
extern EvtScript TTYD64_imp_27_Pokey_Script_8021BF50_0A;
extern ActorPartBlueprint TTYD64_imp_27_Pokey_PartsTable_80218338_0A[];
extern EvtScript TTYD64_imp_27_TubbaBlubba_Script_Init_802253D0_27;
extern s32 TTYD64_imp_27_ShyGuy_StatusTable_80223784_27[];
extern s32 TTYD64_imp_27_Pokey_StatusTable_8021828C_0A[];
extern Battle TTYD64_dig_FormationTable[];
extern FormationRow TTYD64_dig_Formation_00[];
extern FormationRow TTYD64_dig_Formation_03[];
extern ActorPartBlueprint TTYD64_imp_27_MontyMole_PartsTable_80226E08_27[];
extern EvtScript TTYD64_imp_27_BanditA_Script_Init_802217A0_27;
extern EvtScript TTYD64_imp_27_MontyMole_Script_Init_802270B0_27;
extern EvtScript TTYD64_imp_27_ShyGuy_Script_TakeTurn_80225214_27;
extern s32 TTYD64_imp_27_TubbaBlubba_IdleAnimations_80225270_27[];
extern FormationRow TTYD64_dig_Formation_01[];
extern FormationRow TTYD64_dig_Formation_02[];
extern EvtScript TTYD64_imp_27_ShyGuy_Script_Init_802238C8_27;
extern s32 TTYD64_imp_27_MontyMole_IdleAnimations_80226E9C_27[];
extern s32 TTYD64_imp_27_BanditA_IdleAnimations_80221560_27[];
extern s32 TTYD64_imp_27_ShyGuy_IdleAnimations_8022387C_27[];
extern s32 TTYD64_imp_27_BanditA_IdleAnimations_802215AC_27[];
extern s32 TTYD64_imp_27_Fuzzy_IdleAnimations_8021AB24_27[];
extern EvtScript TTYD64_imp_27_Fuzzy_Script_Init_8021AB70_27;
extern ActorPartBlueprint TTYD64_imp_27_BanditA_PartsTable_802216BC_27[];
extern s32 TTYD64_imp_27_Pokey_IdleAnimations_80218474_0A[];
extern s32 TTYD64_imp_27_Pokey_IdleAnimations_802184EC_0A[];
extern s32 TTYD64_imp_27_Pokey_IdleAnimations_80218438_0A[];
extern s32 TTYD64_imp_27_Pokey_IdleAnimations_802184B0_0A[];
extern ActorBlueprint TTYD64_imp_27_Pokey_27_Pokey;
extern ActorBlueprint TTYD64_imp_27_Fuzzy_27_Fuzzy;
extern ActorBlueprint TTYD64_imp_27_Pokey_Pokey_0A;
extern ActorBlueprint TTYD64_imp_27_MontyMole_27_MontyMole;
extern ActorBlueprint TTYD64_imp_27_TubbaBlubba_27_TubbaBlubba;
extern ActorBlueprint TTYD64_imp_27_ShyGuy_27_ShyGuy;
extern ActorBlueprint TTYD64_imp_27_BanditA_27_BanditA;
extern ActorPartBlueprint TTYD64_imp_27_ShyGuy_PartsTable_80223830_27[];
extern ActorPartBlueprint TTYD64_imp_27_Fuzzy_PartsTable_8021AAD8_27[];
extern ActorPartBlueprint TTYD64_imp_27_TubbaBlubba_PartsTable_80225384_27[];
extern FormationRow TTYD64_dig_Formation_04[];
extern FormationRow TTYD64_imp_27_Pokey_SpecialFormation_8021AE10_0A[];

// clang-format off
EvtScript TTYD64_imp_27_Fuzzy_Script_TakeTurn_8021B230_27 = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0001)
    Label(100)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0004)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0005)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 11, 0, 1, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0009)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0003)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0005)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0007)
    Wait(21)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0000)
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
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 1, 32)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0001)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(GetOwnerTarget, LVar0, 0)
            Call(GetLastDamage, LVar0, LVar3)
            IfNe(LVar3, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8301)
                Call(PlaySoundAtActor, ACTOR_SELF, 532)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 10)
                Call(b_area_dig_fuzzy_SpawnDrainHealthStartFX, LVar0, LVar1, LVar2, LVar3)
                Thread
                    Wait(15)
                    Call(PlaySoundAtActor, ACTOR_SELF, 604)
                    Call(b_area_dig_fuzzy_SpawnDrainHealthContinueFX, LVar0, LVar1, LVar2, LVar3)
                EndThread
                Add(LVar0, 20)
                Add(LVar1, 20)
                Call(PlayEffect_impl, 64, 0, LVar0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0)
                Call(GetActorHP, ACTOR_SELF, LVar0)
                Add(LVar0, LVar3)
                Call(SetEnemyHP, ACTOR_SELF, LVar0)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            ExecWait(Ref(EVS_Enemy_HopToPos))
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0001)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_27_BanditA_Script_TakeTurn_80222950_27 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorYaw, ACTOR_SELF, 180)
        Call(SetAnimation, ACTOR_SELF, 1, 0x320008)
        Wait(30)
        Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
        Call(SetGoalPos, ACTOR_SELF, 300, 0, 0)
        Call(RunToGoal, ACTOR_SELF, 0, 0)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x320007)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
        Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x320001)
        Wait(6)
    EndIf
    Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x320005)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x32000D)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x320007)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x320001)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x32000D)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(GetOwnerTarget, LVar3, 0)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
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
                    Call(SetAnimation, ACTOR_SELF, 1, 0x320001)
                    Wait(20)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x320007)
                CaseEq(1)
                    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Add(LVar0, 30)
                    Set(LVar1, 0)
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x32000E)
                    Wait(20)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8387)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x320010)
                    Wait(20)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x320007)
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
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_27_BanditA_IdleAnimations_802215AC_27))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x32000E)
                    Call(SetActorVar, ACTOR_SELF, 0, 1)
                    Wait(7)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x32000F)
                    Wait(20)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x320008)
            EndSwitch
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_27_Pokey_Script_HandleEvent_802186C0_0A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x80000)
                SetConst(LVar0, 1)
                Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 3)
                    SetConst(LVar0, 1)
                    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                    ExecWait(Ref(EVS_Enemy_Hit))
                Else
                    Call(GetDamageSource, LVar0)
                    Switch(LVar0)
                        CaseOrEq(6)
                        CaseOrEq(7)
                        CaseOrEq(9)
                            ExecWait(TTYD64_imp_27_Pokey_Script_8021CCAC_0A)
                        EndCaseGroup
                        CaseDefault
                            SetConst(LVar0, 1)
                            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                            ExecWait(Ref(EVS_Enemy_Hit))
                    EndSwitch
                EndIf
            EndIf
        CaseEq(32)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x80000)
                SetConst(LVar0, 1)
                Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
            Else
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 3)
                    SetConst(LVar0, 1)
                    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Wait(10)
                Else
                    Call(GetDamageSource, LVar0)
                    Switch(LVar0)
                        CaseOrEq(6)
                        CaseOrEq(7)
                        CaseOrEq(9)
                            ExecWait(TTYD64_imp_27_Pokey_Script_8021CCAC_0A)
                        EndCaseGroup
                        CaseDefault
                            SetConst(LVar0, 1)
                            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                            ExecWait(Ref(EVS_Enemy_Hit))
                            Wait(10)
                    EndSwitch
                EndIf
            EndIf
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(14)
            Call(GetActorVar, ACTOR_SELF, 6, LVar1)
            Call(GetActorVar, ACTOR_SELF, 7, LVar2)
            SetConst(LVar0, 1)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 3)
                    ExecWait(Ref(EVS_Enemy_BurnHit))
                Else
                    Call(GetDamageSource, LVarA)
                    Switch(LVarA)
                        CaseOrEq(6)
                        CaseOrEq(7)
                        CaseOrEq(9)
                            ExecWait(TTYD64_imp_27_Pokey_Script_8021CCAC_0A)
                        EndCaseGroup
                        CaseDefault
                            ExecWait(Ref(EVS_Enemy_BurnHit))
                    EndSwitch
                EndIf
            EndIf
        CaseOrEq(36)
            Call(GetActorVar, ACTOR_SELF, 6, LVar1)
            Call(GetActorVar, ACTOR_SELF, 7, LVar2)
            SetConst(LVar0, 1)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                Call(GetActorVar, ACTOR_SELF, 0, LVarA)
                IfEq(LVarA, 3)
                    ExecWait(Ref(EVS_Enemy_BurnHit))
                Else
                    Call(GetDamageSource, LVarA)
                    Switch(LVarA)
                        CaseOrEq(6)
                        CaseOrEq(7)
                        CaseOrEq(9)
                            ExecWait(TTYD64_imp_27_Pokey_Script_8021CCAC_0A)
                        EndCaseGroup
                        CaseDefault
                            ExecWait(Ref(EVS_Enemy_BurnHit))
                    EndSwitch
                EndIf
            EndIf
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 7, LVar1)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            ExecWait(TTYD64_imp_27_Pokey_Script_8021BF50_0A)
        CaseEq(33)
            ExecWait(TTYD64_imp_27_Pokey_Script_8021BF50_0A)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(17)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                SetConst(LVar0, 1)
                Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                ExecWait(TTYD64_imp_27_Pokey_Script_8021CCAC_0A)
            EndIf
        CaseEq(37)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                SetConst(LVar0, 1)
                Call(GetActorVar, ACTOR_SELF, 3, LVar1)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                ExecWait(TTYD64_imp_27_Pokey_Script_8021CCAC_0A)
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, -1)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Call(GetActorVar, ACTOR_SELF, 2, LVar1)
            Call(SetAnimation, ACTOR_SELF, 1, LVar1)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            ExecWait(Ref(EVS_Enemy_HopToPos))
        CaseEq(38)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 1, LVar1)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(27)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Set(LVar0, 0)
                    Set(LVar1, 77)
                    SetConst(LVar2, 0x310021)
                CaseEq(1)
                    Set(LVar0, 0)
                    Set(LVar1, 59)
                    SetConst(LVar2, 0x310022)
                CaseEq(2)
                    Set(LVar0, 0)
                    Set(LVar1, 41)
                    SetConst(LVar2, 0x310023)
                CaseEq(3)
                    Set(LVar0, 0)
                    Set(LVar1, 23)
                    SetConst(LVar2, 0x310024)
            EndSwitch
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfNotFlag(LVar3, 4096)
                Call(SetAnimation, ACTOR_SELF, 1, LVar2)
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Call(GetStatusFlags, ACTOR_SELF, LVar6)
            IfFlag(LVar6, 0x80000)
                MulF(LVar0, Float(0.400390625))
                MulF(LVar1, Float(0.400390625))
            EndIf
            AddF(LVar3, LVar0)
            AddF(LVar4, LVar1)
            Call(PlayEffect_impl, 26, 0, LVar3, LVar4, LVar5, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(30)
        CaseEq(49)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 1, LVar1)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            ExecWait(TTYD64_imp_27_Pokey_Script_8021D184_0A)
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
EvtScript TTYD64_imp_27_TubbaBlubba_Script_8022614C_27 = {
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamDist, 180)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6B0007)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 70, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6B000F)
    Wait(8)
    Call(SetAnimation, ACTOR_SELF, 1, 0x6B0010)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Wait(12)
                Call(SetAnimation, ACTOR_SELF, 1, 0x6B0011)
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 15)
            Set(LVar1, 0)
            Add(LVar2, 5)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(PlaySound, 994)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 23, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8426)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6B0012)
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 60, 8, 10, 20, 0, 0, 0, 0, 0)
            EndThread
            Thread
                Call(ShakeCam, 1, 0, 5, Float(3.0))
            EndThread
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 0)
            Add(LVar2, 5)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(ShakeCam, 1, 0, 5, Float(3.0))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 60, 8, 10, 20, 0, 0, 0, 0, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Wait(8)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6B0013)
            Wait(4)
            ExecWait(b_area_dig_tubba_blubba_EVS_ReturnHome)
            Return
        EndCaseGroup
        CaseDefault
            Thread
                Wait(12)
                Call(SetAnimation, ACTOR_SELF, 1, 0x6B0011)
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(PlaySound, 994)
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
    EndSwitch
    Wait(2)
    Call(PlaySoundAtActor, ACTOR_SELF, 8426)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar5)
    IfNotFlag(LVar5, 0x80000)
        Call(SetDamageSource, 24)
        Call(PlaySoundAtActor, ACTOR_SELF, 8426)
    EndIf
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 6, 32)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(GetStatusFlags, ACTOR_SELF, LVar5)
            IfFlag(LVar5, 0x80000)
                Goto(1)
            EndIf
            Call(GetBattleFlags, LVar0)
            IfNotFlag(LVar0, (-0x7FFFFFFF - 1))
                Call(GetStatusFlags, 0, LVar0)
                IfNotFlag(LVar0, 0x100000)
                    Call(LandJump, ACTOR_SELF)
                Else
                    Goto(1)
                EndIf
            Else
                Goto(1)
            EndIf
            Label(0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 37, 0, LVar0, 0, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6B000D)
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 60, 8, 10, 20, 0, 0, 0, 0, 0)
            EndThread
            Thread
                Call(ShakeCam, 1, 0, 5, Float(3.0))
            EndThread
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 0)
            Add(LVar2, 5)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(ShakeCam, 1, 0, 5, Float(3.0))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 60, 8, 10, 20, 0, 0, 0, 0, 0)
            Goto(2)
            Label(1)
            Call(GetStatusFlags, ACTOR_SELF, LVar5)
            IfNotFlag(LVar5, 0x80000)
                Wait(3)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(PlayEffect_impl, 37, 1, LVar0, 0, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                Call(ShakeCam, 1, 0, 5, Float(3.0))
            EndIf
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Thread
                Wait(8)
                Call(SetAnimation, ACTOR_SELF, 1, 0x6B000E)
            EndThread
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            IfNotFlag(LVar5, 0x80000)
                Call(ShakeCam, 1, 0, 5, Float(3.0))
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 60, 8, 10, 20, 0, 0, 0, 0, 0)
                Wait(8)
            EndIf
            Label(2)
            IfEq(LVarF, 10)
                Return
            EndIf
            Call(YieldTurn)
            ExecWait(b_area_dig_tubba_blubba_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_27_ShyGuy_Script_8022468C_27 = {
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
    Call(PlaySoundAtActor, ACTOR_SELF, 564)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0009)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0003)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 80)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
    Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0004)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Sub(LVar0, 40)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0009)
            Thread
                Wait(12)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B000A)
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 10)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 24, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0005)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Sub(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 15)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3B0004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0001)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0009)
    Thread
        Wait(9)
        Call(SetAnimation, ACTOR_SELF, 1, 0x3B000A)
    EndThread
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(JumpToGoal, ACTOR_SELF, 18, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 15)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 14, 0)
                Set(LVar3, 0)
                Loop(20)
                    Sub(LVar3, 30)
                    IfLt(LVar3, 0)
                        Add(LVar3, 360)
                    EndIf
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar3)
                    Wait(1)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(GetBattleFlags, LVar0)
            IfFlag(LVar0, (-0x7FFFFFFF - 1))
                Goto(1)
            EndIf
            Call(GetOwnerTarget, LVar2, 0)
            Call(GetLastDamage, LVar2, LVar0)
            IfEq(LVar0, 0)
                Goto(1)
            EndIf
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 841)
            Call(PlaySoundAtActor, ACTOR_SELF, 1865)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0009)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0007)
            Wait(15)
            Goto(2)
            Label(1)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8420)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0010)
            Wait(10)
            Call(PlaySoundAtActor, ACTOR_SELF, 8387)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 50)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0011)
            Else
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0013)
            EndIf
            Wait(25)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Label(2)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3B0004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0001)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_27_Pokey_Script_TakeTurn_8021A018_0A = {
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfEq(LVarA, 3)
        ExecWait(TTYD64_imp_27_Pokey_Script_8021B590_0A)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 9, LVar0)
    IfEq(LVar0, 0)
        Call(GetActorVar, ACTOR_SELF, 10, LVar0)
        IfEq(LVar0, 2)
            Goto(123)
        EndIf
        ExecWait(b_area_dig_pokey_EVS_FindValidSummonPosition)
        IfEq(LVarE, -1)
            Goto(123)
        EndIf
        ExecWait(b_area_dig_pokey_EVS_CountSummonerPokeys)
        Switch(LVar9)
            CaseEq(1)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 400)
                    ExecWait(TTYD64_imp_27_Pokey_Script_8021AE2C_0A)
                    Return
                EndIf
            CaseEq(2)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 200)
                    ExecWait(TTYD64_imp_27_Pokey_Script_8021AE2C_0A)
                    Return
                EndIf
            CaseEq(3)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 100)
                    ExecWait(TTYD64_imp_27_Pokey_Script_8021AE2C_0A)
                    Return
                EndIf
        EndSwitch
    EndIf
    Label(123)
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 500)
        ExecWait(TTYD64_imp_27_Pokey_Script_802193B8_0A)
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
    ExecWait(TTYD64_imp_27_Pokey_Script_8021C07C_0A)
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
EvtScript TTYD64_imp_27_Pokey_Script_802193B8_0A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Call(AddGoalPos, ACTOR_SELF, 60, 0, 0)
            Else
                Call(AddGoalPos, ACTOR_SELF, 24, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x310008)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310004)
        CaseEq(1)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Call(AddGoalPos, ACTOR_SELF, 40, 0, 0)
            Else
                Call(AddGoalPos, ACTOR_SELF, 16, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x310009)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310005)
        CaseEq(2)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x80000)
                Call(AddGoalPos, ACTOR_SELF, 20, 0, 0)
            Else
                Call(AddGoalPos, ACTOR_SELF, 8, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x31000A)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310006)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 834)
    Call(MakeLerp, 0, -40, 20, 10)
    Label(0)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    ChildThread
        Wait(3)
        Call(PlaySoundAtActor, ACTOR_SELF, 749)
    EndChildThread
    Call(MakeLerp, -40, 90, 5, 1)
    Label(3)
    Call(UpdateLerp)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(3)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 0, 32)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(MakeLerp, 90, 0, 5, 0)
            Label(4)
            Call(UpdateLerp)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(4)
            EndIf
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310008)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310004)
                CaseEq(1)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310009)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310005)
                CaseEq(2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x31000A)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310006)
            EndSwitch
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Set(LVar1, 2)
        CaseEq(1)
            Set(LVar1, 2)
        CaseDefault
            Set(LVar1, 2)
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, -0x7FFDFD00, LVar1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(MakeLerp, 90, 0, 10, 0)
            Label(5)
            Call(UpdateLerp)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(5)
            EndIf
            Call(YieldTurn)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310008)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310004)
                CaseEq(1)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310009)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310005)
                CaseEq(2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x31000A)
                    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x310006)
            EndSwitch
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_27_Pokey_Script_8021B590_0A = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorSounds, ACTOR_SELF, 0, 748, 748)
    Call(SetActorSounds, ACTOR_SELF, 2, 748, 0)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0x31000B)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetAnimation, ACTOR_SELF, 1, 0x310007)
    Wait(4)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(4)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x31000B)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 2, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 5)
            Set(LVar1, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.099609375))
            ChildThread
                Wait(2)
                Set(LVar0, 0)
                Loop(5)
                    Add(LVar0, 30)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndChildThread
            Call(JumpToGoal, ACTOR_SELF, 22, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
            ChildThread
                Wait(2)
                Set(LVar0, 180)
                Loop(6)
                    Add(LVar0, 30)
                    IfEq(LVar0, 360)
                        Set(LVar0, 0)
                    EndIf
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            EndChildThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x31000B)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            ExecWait(Ref(EVS_Enemy_HopToPos))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x310007)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.099609375))
    ChildThread
        Wait(2)
        Set(LVar0, 0)
        Loop(5)
            Add(LVar0, 30)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndChildThread
    Call(JumpToGoal, ACTOR_SELF, 18, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, -0x7FFDFD00, 4, 32)
    Call(SetAnimation, ACTOR_SELF, 1, 0x310007)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x310007)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x31000B)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            ExecWait(Ref(EVS_Enemy_HopToPos))
            Call(SetAnimation, ACTOR_SELF, 1, 0x310007)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_27_BanditA_Script_HandleEvent_80221FD8_27 = {
    UseArray(Ref(b_area_dig_bandit_DropCoinScript))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            ExecGetTID(TTYD64_imp_27_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_imp_27_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_imp_27_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_imp_27_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_imp_27_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_imp_27_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_imp_27_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_imp_27_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
            ExecGetTID(TTYD64_imp_27_BanditA_Script_Bandit_GetCoinBack, ArrayVar(0))
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
EvtScript TTYD64_imp_27_BanditA_Script_Bandit_GetCoinBack = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_27_BanditA_IdleAnimations_80221560_27))
            Call(SetPartFlagBits, ACTOR_SELF, 2, 0x100000, 0)
            Call(SummonEnemy, Ref(b_area_dig_bandit_CoinFormation), 0)
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
EvtScript TTYD64_imp_27_Pokey_Script_8021AE2C_0A = {
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
    Call(SummonEnemy, Ref(TTYD64_imp_27_Pokey_SpecialFormation_8021AE10_0A), 0)
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
EvtScript TTYD64_imp_27_ShyGuy_Script_80223F64_27 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0003)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetActorSounds, ACTOR_SELF, 2, 751, 0)
            Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
            Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0004)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0005)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(ResetAllActorSounds, ACTOR_SELF)
            Sub(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3B0004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0001)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Wait(3)
        Call(PlaySoundAtActor, ACTOR_SELF, 751)
    EndThread
    Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
    Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0004)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0005)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 15)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0001)
    Wait(8)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    ExecWait(b_area_dig_red_shy_guy_EVS_ReturnHome)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_27_MontyMole_Script_TakeTurn_802278AC_27 = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x2F0004)
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
            Call(SetAnimation, ACTOR_SELF, 3, 0x2F000F)
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
    Call(SetAnimation, ACTOR_SELF, 3, 0x2F000F)
    Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 0, 20, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 2, 32)
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

// clang-format off
EvtScript TTYD64_imp_27_Fuzzy_Script_HandleEvent_8021ABCC_27 = {
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
                SetConst(LVar1, 0x2B0013)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0008)
            EndIf
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0010)
            SetConst(LVar2, 0x2B0012)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0010)
            SetConst(LVar2, 0x2B0012)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0012)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0008)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0008)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0008)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0013)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0013)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0003)
            ExecWait(Ref(EVS_Enemy_HopHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0013)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0008)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            Call(GetLastElement, LVar0)
            IfFlag(LVar0, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0013)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0013)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0008)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0008)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0003)
            SetConst(LVar2, 0x2B0009)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0003)
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
EvtScript TTYD64_imp_27_TubbaBlubba_Script_TakeTurn_802256A0_27 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    IfEq(LVar0, 6)
        Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetAnimation, ACTOR_SELF, 1, 0x6B0007)
        Call(SetGoalPos, ACTOR_SELF, 0, 0, 0)
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x6B0001)
        Wait(30)
        Set(LVar0, 0)
        Loop(12)
            Add(LVar0, 15)
            Call(SetActorYaw, ACTOR_SELF, LVar0)
            Wait(1)
        EndLoop
        Wait(10)
        Set(LVar0, 180)
        Loop(12)
            Sub(LVar0, 15)
            Call(SetActorYaw, ACTOR_SELF, LVar0)
            Wait(1)
        EndLoop
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x6B0002)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 80)
        Call(PlayEffect_impl, 16, 2, 0, LVar0, LVar1, LVar2, 30, 315, 30, 0, 0, 0, 0, 0)
        Wait(40)
        Call(SetAnimation, ACTOR_SELF, 1, 0x6B0001)
        Set(LVar0, 0)
        Loop(15)
            Add(LVar0, 12)
            Call(SetActorYaw, ACTOR_SELF, LVar0)
            Wait(1)
        EndLoop
        Call(SetAnimation, ACTOR_SELF, 1, 0x6B0006)
        Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar0, 220)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(GetActorVar, ACTOR_SELF, 2, LVar0)
        KillThread(LVar0)
        Call(SetActorFlagBits, ACTOR_SELF, 0x400000, 1)
        Call(SetBattleFlagBits, 0x60000, 1)
        Call(SetEndBattleFadeOutRate, 10)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    IfEq(LVar0, 1)
        Call(EnableBattleStatusBar, 0)
        Call(SetActorVar, ACTOR_SELF, 1, 2)
        Call(ActorSpeak, 0xE0103, ACTOR_SELF, 1, 0x6B0009, 0x6B0002)
        Thread
            Call(SetAnimation, ACTOR_SELF, 1, 0x6B0015)
            Wait(4)
            Call(SetAnimation, ACTOR_SELF, 1, 0x6B0016)
            Wait(15)
        EndThread
        Call(EndActorSpeech, ACTOR_SELF, 1, -1, -1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x6B0001)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 15)
        Wait(15)
        Call(EnableBattleStatusBar, 1)
    EndIf
    ExecWait(TTYD64_imp_27_TubbaBlubba_Script_8022614C_27)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_27_Pokey_Script_8021C07C_0A = {
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    Switch(LVarA)
        CaseEq(0)
            Call(SetActorVar, ACTOR_SELF, 1, 0x310005)
            Call(SetActorVar, ACTOR_SELF, 2, 0x310009)
            Call(SetActorVar, ACTOR_SELF, 3, 0x31000D)
            Call(SetActorVar, ACTOR_SELF, 4, 0x310012)
            Call(SetActorVar, ACTOR_SELF, 5, 0x310013)
            Call(SetActorVar, ACTOR_SELF, 6, 0x31001A)
            Call(SetActorVar, ACTOR_SELF, 7, 0x31001B)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_27_Pokey_IdleAnimations_80218474_0A))
            Call(SetPartFlagBits, ACTOR_SELF, 2, 0x800000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20000, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x20000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x800000, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(SetActorSize, ACTOR_SELF, 62, -0xEE6B280)
            Call(SetPartSize, ACTOR_SELF, 1, 62, -0xEE6B280)
            Call(b_area_dig_pokey_SetAbsoluteStatusOffsets, -15, 55, 10, 45)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 1, 0x310006)
            Call(SetActorVar, ACTOR_SELF, 2, 0x31000A)
            Call(SetActorVar, ACTOR_SELF, 3, 0x31000E)
            Call(SetActorVar, ACTOR_SELF, 4, 0x310014)
            Call(SetActorVar, ACTOR_SELF, 5, 0x310015)
            Call(SetActorVar, ACTOR_SELF, 6, 0x31001C)
            Call(SetActorVar, ACTOR_SELF, 7, 0x31001D)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_27_Pokey_IdleAnimations_802184B0_0A))
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x800000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x20000, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x20000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x800000, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 2)
            Call(SetActorSize, ACTOR_SELF, 44, -0xEE6B280)
            Call(SetPartSize, ACTOR_SELF, 1, 44, -0xEE6B280)
            Call(b_area_dig_pokey_SetAbsoluteStatusOffsets, -15, 35, 10, 25)
        CaseEq(2)
            Call(SetActorVar, ACTOR_SELF, 1, 0x310007)
            Call(SetActorVar, ACTOR_SELF, 2, 0x31000B)
            Call(SetActorVar, ACTOR_SELF, 3, 0x31000F)
            Call(SetActorVar, ACTOR_SELF, 6, 0x31001E)
            Call(SetActorVar, ACTOR_SELF, 7, 0x31001F)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_27_Pokey_IdleAnimations_802184EC_0A))
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x800000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x20000, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 5, 0x20000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 5, 0x800000, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 3)
            Call(SetActorSize, ACTOR_SELF, 26, -0xEE6B280)
            Call(SetPartSize, ACTOR_SELF, 1, 26, -0xEE6B280)
            Call(b_area_dig_pokey_SetAbsoluteStatusOffsets, -15, 15, 10, 5)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_27_Pokey_Script_8021CCAC_0A = {
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 6, Float(1.0), Float(1.0), Float(1.0))
    Else
        Call(SetPartScale, ACTOR_SELF, 6, Float(0.400390625), Float(0.400390625), Float(1.0))
    EndIf
    ExecWait(TTYD64_imp_27_Pokey_Script_8021C07C_0A)
    SetConst(LVar0, 1)
    Call(GetLastEvent, ACTOR_SELF, LVar1)
    Switch(LVar1)
        CaseOrEq(14)
        CaseOrEq(36)
            Call(SetAnimation, ACTOR_SELF, 6, 0x310020)
            Call(GetActorVar, ACTOR_SELF, 6, LVar1)
        EndCaseGroup
        CaseDefault
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    ChildThread
        Wait(4)
        ExecWait(b_area_dig_pokey_EVS_HitReactionBounce)
    EndChildThread
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfNe(LVarA, 3)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
        Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
        Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(6.0))
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 30)
        Set(LVar1, 0)
        Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 10, 18, 0)
        Add(LVar0, 20)
        Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 8, 10, 0)
        Loop(20)
            Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
            Wait(1)
            Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
            Wait(1)
        EndLoop
        Call(SetPartFlagBits, ACTOR_SELF, 6, 0x20000, 1)
        Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
    Else
        Wait(30)
    EndIf
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(14)
            Call(GetActorVar, ACTOR_SELF, 7, LVar1)
            Call(SetAnimation, ACTOR_SELF, 1, LVar1)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetActorSize, ACTOR_SELF, LVar3, LVar4)
            Div(LVar3, 2)
            Add(LVar1, LVar3)
            Add(LVar2, 5)
            DivF(LVar3, Float(10.0))
            Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
        CaseEq(36)
            Call(GetActorVar, ACTOR_SELF, 7, LVar1)
            Call(SetAnimation, ACTOR_SELF, 1, LVar1)
            Wait(10)
        CaseDefault
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_27_Pokey_Script_8021C860_0A = {
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 6, Float(1.0), Float(1.0), Float(1.0))
    Else
        Call(SetPartScale, ACTOR_SELF, 6, Float(0.400390625), Float(0.400390625), Float(1.0))
    EndIf
    ExecWait(TTYD64_imp_27_Pokey_Script_8021C07C_0A)
    SetConst(LVar0, 1)
    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    ChildThread
        Wait(4)
        ExecWait(b_area_dig_pokey_EVS_HitReactionBounce)
    EndChildThread
    Call(CreateHomeTargetList, 0x18004)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerID, LVar1)
    Call(GetOwnerTarget, LVar0, LVar9)
    IfNe(LVar1, LVar0)
        Call(ChooseNextTarget, 0, LVar0)
        Goto(0)
    EndIf
    Label(1)
    Add(LVarF, 1)
    Call(ChooseNextTarget, 0, LVar0)
    IfEq(LVar0, -1)
        Goto(10)
    EndIf
    Call(GetOwnerTarget, LVar0, LVar9)
    Call(GetActorFlags, LVar0, LVar1)
    IfFlag(LVar1, 0x4000)
        Goto(1)
    EndIf
    Call(GetOwnerID, LVar0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
    Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(7.0))
    Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 1)
    ChildThread
        Call(ShakeCam, 1, 0, 2, Float(1.0))
    EndChildThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(DispatchDamageEvent, LVar0, 1, 17)
    Goto(1)
    Label(10)
    Call(UseBattleCamPreset, 3)
    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
    Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(6.0))
    Call(JumpPartTo, ACTOR_SELF, 6, 296, 0, 0, 0, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 6, 0x20000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_27_Pokey_Script_8021D184_0A = {
    SetConst(LVar0, 1)
    Call(GetActorVar, ACTOR_SELF, 3, LVar1)
    Call(UseBattleCamPreset, 2)
    Call(GetActorFlags, ACTOR_SELF, LVar9)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.0498046875))
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Set(LVarD, LVarB)
    Add(LVarD, 40)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarD, LVarC)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    Wait(20)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(FallToGoal, ACTOR_SELF, 10)
    Wait(20)
    Call(SetActorYaw, ACTOR_SELF, 180)
    Wait(5)
    Call(SetActorVar, ACTOR_SELF, 0, LVar2)
    Switch(LVar2)
        CaseEq(0)
            Set(LVar2, 96)
            Set(LVar6, 4)
        CaseEq(1)
            Set(LVar2, 72)
            Set(LVar6, 3)
        CaseEq(2)
            Set(LVar2, 48)
            Set(LVar6, 2)
        CaseDefault
            Set(LVar2, 24)
            Set(LVar6, 1)
    EndSwitch
    ChildThread
        Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
        Loop(LVar6)
            Call(PlayEffect_impl, 37, 2, LVarA, 0, LVarC, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(10)
        EndLoop
    EndChildThread
    Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar4, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
    Wait(8)
    Call(HideHealthBar, ACTOR_SELF)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(RemoveActor, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_27_Pokey_Script_Init_80218534_0A = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_27_Pokey_Script_TakeTurn_8021A018_0A))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_dig_pokey_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_27_Pokey_Script_HandleEvent_802186C0_0A))
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
EvtScript TTYD64_imp_27_Pokey_Script_8021BF50_0A = {
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        SetConst(LVar0, 1)
        Call(GetActorVar, ACTOR_SELF, 3, LVar1)
        ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    Switch(LVarA)
        CaseEq(0)
            ExecWait(TTYD64_imp_27_Pokey_Script_8021C860_0A)
        CaseEq(1)
            ExecWait(TTYD64_imp_27_Pokey_Script_8021C860_0A)
        CaseEq(2)
            ExecWait(TTYD64_imp_27_Pokey_Script_8021C860_0A)
        CaseEq(3)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 3, LVar1)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
    EndSwitch
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_imp_27_Pokey_PartsTable_80218338_0A[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_27_Pokey_IdleAnimations_80218438_0A,
        .defenseTable = b_area_dig_pokey_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 72 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_dig_pokey_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 54 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_dig_pokey_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 36 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_dig_pokey_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 16 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_dig_pokey_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 6,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_dig_pokey_ThrownPartAnims,
        .defenseTable = b_area_dig_pokey_DefenseTable,
        .eventFlags = 0x200010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_imp_27_TubbaBlubba_Script_Init_802253D0_27 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_27_TubbaBlubba_Script_TakeTurn_802256A0_27))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_dig_tubba_blubba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_dig_tubba_blubba_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_dig_tubba_blubba_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    ExecGetTID(b_area_dig_tubba_blubba_EVS_PlayFootstepQuaking, LVar0)
    Call(SetActorVar, ACTOR_SELF, 2, LVar0)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_27_ShyGuy_StatusTable_80223784_27[] = {
    1,  0, 2,  0, 6,  70, 9,  50, 7,  70, 4,  90, 3,  100, 11, 50, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0,   38, 1,  39, 0,  41, 0,  0,
};

s32 TTYD64_imp_27_Pokey_StatusTable_8021828C_0A[] = {
    1,  0, 2,  0, 6,  90, 9,  0, 7,  90, 4,  90, 3,  0, 11, 0, 5,  100, 10, 90, 8, 100,
    31, 0, 32, 0, 37, 0,  34, 0, 36, 0,  35, 0,  33, 0, 38, 0, 39, 0,   41, 0,  0,
};

Battle TTYD64_dig_FormationTable[] = {
    { .name = "\300\244\270\247\271\310\020\021",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_dig_Formation_00,
      .stage = &b_area_dig_nok_04,
      .onBattleStart = &b_area_dig_dig_01_script },
    { .name = "\300\244\270\247\271\310\020\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_dig_Formation_01,
      .stage = &b_area_dig_iwa_01b,
      .onBattleStart = &b_area_dig_dig_02_script },
    { .name = "\300\244\270\247\271\310\020\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_dig_Formation_02,
      .stage = &b_area_dig_sbk_02,
      .onBattleStart = &b_area_dig_dig_03_script },
    { .name = "\300\244\270\247\271\310\020\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_dig_Formation_03,
      .stage = &b_area_dig_omo_04,
      .onBattleStart = &b_area_dig_dig_04_script },
    { .name = "\300\244\270\247\271\310\020\025",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_dig_Formation_04,
      .stage = &b_area_dig_dgb_05,
      .onBattleStart = &b_area_dig_dig_05_script },
    {},
};

FormationRow TTYD64_dig_Formation_00[] = {
    { .actor = &TTYD64_imp_27_Fuzzy_27_Fuzzy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
    { .actor = &TTYD64_imp_27_Fuzzy_27_Fuzzy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
    { .actor = &TTYD64_imp_27_Fuzzy_27_Fuzzy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
    { .actor = &TTYD64_imp_27_Fuzzy_27_Fuzzy,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FUZZY },
};

FormationRow TTYD64_dig_Formation_03[] = {
    { .actor = &TTYD64_imp_27_ShyGuy_27_ShyGuy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_imp_27_ShyGuy_27_ShyGuy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_imp_27_ShyGuy_27_ShyGuy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_imp_27_ShyGuy_27_ShyGuy,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
};

ActorPartBlueprint TTYD64_imp_27_MontyMole_PartsTable_80226E08_27[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 16 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_27_MontyMole_IdleAnimations_80226E9C_27,
        .defenseTable = b_area_dig_monty_mole_DefenseTable,
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
        .idleAnimations = TTYD64_imp_27_MontyMole_IdleAnimations_80226E9C_27,
        .defenseTable = b_area_dig_monty_mole_DefenseTable,
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
        .idleAnimations = b_area_dig_monty_mole_RockAnims,
        .defenseTable = b_area_dig_monty_mole_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_imp_27_BanditA_Script_Init_802217A0_27 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_27_BanditA_Script_TakeTurn_80222950_27))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_dig_bandit_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_27_BanditA_Script_HandleEvent_80221FD8_27))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_27_MontyMole_Script_Init_802270B0_27 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_27_MontyMole_Script_TakeTurn_802278AC_27))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_dig_monty_mole_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_dig_monty_mole_EVS_HandleEvent))
    Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_27_ShyGuy_Script_TakeTurn_80225214_27 = {
    Call(RandInt, 1, LVar0)
    IfEq(LVar0, 0)
        ExecWait(TTYD64_imp_27_ShyGuy_Script_80223F64_27)
    Else
        ExecWait(TTYD64_imp_27_ShyGuy_Script_8022468C_27)
    EndIf
    Return
    End
};
// clang-format on

s32 TTYD64_imp_27_TubbaBlubba_IdleAnimations_80225270_27[] = {
    1, 0x6B0002, 7, 0x6B0000, 6, 0x6B0000, 9, 0x6B0002, 8, 0x6B0000, 11, 0x6B0000,
    5, 0x6B0000, 5, 0x6B0000, 4, 0x6B0000, 4, 0x6B0000, 3, 0x6B0000, 0,
};

FormationRow TTYD64_dig_Formation_01[] = {
    { .actor = &TTYD64_imp_27_MontyMole_27_MontyMole,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_imp_27_MontyMole_27_MontyMole,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_imp_27_MontyMole_27_MontyMole,
      .home = { .index = 3 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
};

FormationRow TTYD64_dig_Formation_02[] = {
    { .actor = &TTYD64_imp_27_Pokey_27_Pokey,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
    { .actor = &TTYD64_imp_27_BanditA_27_BanditA,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BANDIT },
    { .actor = &TTYD64_imp_27_Pokey_27_Pokey,
      .home = { .index = 3 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_POKEY },
};

// clang-format off
EvtScript TTYD64_imp_27_ShyGuy_Script_Init_802238C8_27 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_27_ShyGuy_Script_TakeTurn_80225214_27))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_dig_red_shy_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_dig_red_shy_guy_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_27_MontyMole_IdleAnimations_80226E9C_27[] = {
    1,  0x2F0001, 7, 0x2F0000, 6, 0x2F0014, 9, 0x2F0001, 8, 0x2F0000,
    11, 0x2F0001, 5, 0x2F0000, 4, 0x2F0014, 3, 0x2F0014, 0,
};

s32 TTYD64_imp_27_BanditA_IdleAnimations_80221560_27[] = {
    1,  0x320001, 7, 0x320000, 6, 0x320010, 9, 0x320001, 8, 0x320000,
    11, 0x320001, 5, 0x320000, 4, 0x320011, 3, 0x320011, 0,
};

s32 TTYD64_imp_27_ShyGuy_IdleAnimations_8022387C_27[] = {
    1,  0x3B0001, 7, 0x3B0000, 6, 0x3B0012, 9, 0x3B0001, 8, 0x3B0000,
    11, 0x3B0001, 5, 0x3B0000, 4, 0x3B0013, 3, 0x3B0013, 0,
};

s32 TTYD64_imp_27_BanditA_IdleAnimations_802215AC_27[] = {
    1,  0x320002, 7, 0x320004, 6, 0x320010, 9, 0x320002, 8, 0x320004,
    11, 0x320002, 5, 0x320004, 4, 0x320011, 3, 0x320011, 0,
};

s32 TTYD64_imp_27_Fuzzy_IdleAnimations_8021AB24_27[] = {
    1,  0x2B0001, 7, 0x2B0000, 6, 0x2B000E, 9, 0x2B0001, 8, 0x2B0000,
    11, 0x2B0001, 5, 0x2B0000, 4, 0x2B000F, 3, 0x2B000F, 0,
};

// clang-format off
EvtScript TTYD64_imp_27_Fuzzy_Script_Init_8021AB70_27 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_27_Fuzzy_Script_TakeTurn_8021B230_27))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_dig_fuzzy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_27_Fuzzy_Script_HandleEvent_8021ABCC_27))
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_imp_27_BanditA_PartsTable_802216BC_27[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 28 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_27_BanditA_IdleAnimations_80221560_27,
        .defenseTable = b_area_dig_bandit_DefenseTable,
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
        .idleAnimations = b_area_dig_bandit_CoinAnims,
        .defenseTable = b_area_dig_bandit_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_imp_27_Pokey_IdleAnimations_80218474_0A[] = {
    1, 0x310005, 7, 0x310001, 6, 0x310026, 8, 0x310001, 5, 0x310001, 4, 0x310022, 3, 0x310022, 0,
};

s32 TTYD64_imp_27_Pokey_IdleAnimations_802184EC_0A[] = {
    1, 0x310007, 7, 0x310003, 6, 0x310028, 8, 0x310003, 5, 0x310003, 4, 0x310024, 3, 0x310024, 0,
};

s32 TTYD64_imp_27_Pokey_IdleAnimations_80218438_0A[] = {
    1, 0x310004, 7, 0x310000, 6, 0x310025, 8, 0x310000, 5, 0x310000, 4, 0x310021, 3, 0x310021, 0,
};

s32 TTYD64_imp_27_Pokey_IdleAnimations_802184B0_0A[] = {
    1, 0x310006, 7, 0x310002, 6, 0x310027, 8, 0x310002, 5, 0x310002, 4, 0x310023, 3, 0x310023, 0,
};

ActorBlueprint TTYD64_imp_27_Pokey_27_Pokey = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x14,
    .level = 9,
    .partCount = 6,
    .partsData = TTYD64_imp_27_Pokey_PartsTable_80218338_0A,
    .initScript = &TTYD64_imp_27_Pokey_Script_Init_80218534_0A,
    .statusTable = TTYD64_imp_27_Pokey_StatusTable_8021828C_0A,
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

ActorBlueprint TTYD64_imp_27_Fuzzy_27_Fuzzy = {
    .flags = 0x0,
    .maxHP = 3,
    .type = 0x0A,
    .level = 6,
    .partCount = 1,
    .partsData = TTYD64_imp_27_Fuzzy_PartsTable_8021AAD8_27,
    .initScript = &TTYD64_imp_27_Fuzzy_Script_Init_8021AB70_27,
    .statusTable = b_area_dig_fuzzy_StatusTable,
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

ActorBlueprint TTYD64_imp_27_Pokey_Pokey_0A = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x14,
    .level = 9,
    .partCount = 6,
    .partsData = TTYD64_imp_27_Pokey_PartsTable_80218338_0A,
    .initScript = &TTYD64_imp_27_Pokey_Script_Init_80218534_0A,
    .statusTable = TTYD64_imp_27_Pokey_StatusTable_8021828C_0A,
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

ActorBlueprint TTYD64_imp_27_MontyMole_27_MontyMole = {
    .flags = 0x0,
    .maxHP = 3,
    .type = 0x12,
    .level = 8,
    .partCount = 3,
    .partsData = TTYD64_imp_27_MontyMole_PartsTable_80226E08_27,
    .initScript = &TTYD64_imp_27_MontyMole_Script_Init_802270B0_27,
    .statusTable = b_area_dig_monty_mole_StatusTable,
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

ActorBlueprint TTYD64_imp_27_TubbaBlubba_27_TubbaBlubba = {
    .flags = 0x0,
    .maxHP = 10,
    .type = 0xA3,
    .level = 70,
    .partCount = 1,
    .partsData = TTYD64_imp_27_TubbaBlubba_PartsTable_80225384_27,
    .initScript = &TTYD64_imp_27_TubbaBlubba_Script_Init_802253D0_27,
    .statusTable = b_area_dig_tubba_blubba_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 110, 100 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -33, 78 },
    .statusTextOffset = { 10, 75 },
};

ActorBlueprint TTYD64_imp_27_ShyGuy_27_ShyGuy = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x1F,
    .level = 14,
    .partCount = 1,
    .partsData = TTYD64_imp_27_ShyGuy_PartsTable_80223830_27,
    .initScript = &TTYD64_imp_27_ShyGuy_Script_Init_802238C8_27,
    .statusTable = TTYD64_imp_27_ShyGuy_StatusTable_80223784_27,
    .escapeChance = 60,
    .airLiftChance = 85,
    .hurricaneChance = 80,
    .spookChance = 80,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 28, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_27_BanditA_27_BanditA = {
    .flags = 0x0,
    .maxHP = 5,
    .type = 0x13,
    .level = 9,
    .partCount = 2,
    .partsData = TTYD64_imp_27_BanditA_PartsTable_802216BC_27,
    .initScript = &TTYD64_imp_27_BanditA_Script_Init_802217A0_27,
    .statusTable = b_area_dig_bandit_StatusTable,
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

ActorPartBlueprint TTYD64_imp_27_ShyGuy_PartsTable_80223830_27[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_27_ShyGuy_IdleAnimations_8022387C_27,
        .defenseTable = b_area_dig_red_shy_guy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_27_Fuzzy_PartsTable_8021AAD8_27[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_27_Fuzzy_IdleAnimations_8021AB24_27,
        .defenseTable = b_area_dig_fuzzy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_27_TubbaBlubba_PartsTable_80225384_27[] = {
    {
        .flags = 0x802000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -15, 75 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_27_TubbaBlubba_IdleAnimations_80225270_27,
        .defenseTable = b_area_dig_tubba_blubba_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_dig_Formation_04[] = {
    { .actor = &TTYD64_imp_27_TubbaBlubba_27_TubbaBlubba,
      .home = { .index = 2 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_27_Pokey_SpecialFormation_8021AE10_0A[] = {
    { .actor = &TTYD64_imp_27_Pokey_Pokey_0A,
      .home = { .vec = &b_area_dig_pokey_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

void TTYD64_InstallBattles_dig(void) {
    Mod_SetBattleList("TTYD64", 0x27, TTYD64_dig_FormationTable);
}
