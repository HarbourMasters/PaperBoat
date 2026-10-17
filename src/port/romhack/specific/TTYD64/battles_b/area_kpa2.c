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
#include "battles_b.h"
#include "battles_b_imports.h"

API_CALLABLE(b_area_kpa2_final_bowser_1_FadeBackgroundDarken);
API_CALLABLE(b_area_kpa2_final_bowser_1_FadeBackgroundLighten);
API_CALLABLE(b_area_kpa2_final_bowser_1_GetJumpHammerCharge);
API_CALLABLE(b_area_kpa2_final_bowser_1_GetPlayerHpPercent);
API_CALLABLE(b_area_kpa2_final_bowser_1_RemoveChillOut);
API_CALLABLE(b_area_kpa2_final_bowser_1_SetBowserFireBreathScales);
API_CALLABLE(b_area_kpa2_final_bowser_1_StarRodAppearEffect);
API_CALLABLE(b_area_kpa2_final_bowser_1_StarRodPowerUpEffect);
API_CALLABLE(b_area_kpa2_final_bowser_1_StartRumbleWithParams);
API_CALLABLE(b_area_kpa2_final_bowser_1_UnkLightningBoltFxFunc1);
API_CALLABLE(b_area_kpa2_final_bowser_2_FadeBackgroundDarken);
API_CALLABLE(b_area_kpa2_final_bowser_2_FadeBackgroundLighten);
API_CALLABLE(b_area_kpa2_final_bowser_2_GetJumpHammerCharge);
API_CALLABLE(b_area_kpa2_final_bowser_2_MakeLightningBolts);
API_CALLABLE(b_area_kpa2_final_bowser_2_RemoveChillOut);
API_CALLABLE(b_area_kpa2_final_bowser_2_SetBowserFireBreathScales);
API_CALLABLE(b_area_kpa2_final_bowser_2_StarRodAppearEffect);
API_CALLABLE(b_area_kpa2_final_bowser_2_StarRodPowerUpEffect);
API_CALLABLE(b_area_kpa2_final_bowser_2_UnkLightningBoltFxFunc1);
API_CALLABLE(b_area_kpa2_hallway_bowser_FadeBackgroundDarken);
API_CALLABLE(b_area_kpa2_hallway_bowser_FadeBackgroundLighten);
API_CALLABLE(b_area_kpa2_hallway_bowser_GetJumpHammerCharge);
API_CALLABLE(b_area_kpa2_hallway_bowser_GetPlayerHpPercent);
API_CALLABLE(b_area_kpa2_hallway_bowser_RemoveChillOut);
API_CALLABLE(b_area_kpa2_hallway_bowser_SetBowserFireBreathScales);
API_CALLABLE(b_area_kpa2_hallway_bowser_StarRodAppearEffect);
API_CALLABLE(b_area_kpa2_hallway_bowser_StarRodPowerUpEffect);
API_CALLABLE(b_area_kpa2_hallway_bowser_StartRumbleWithParams);
API_CALLABLE(b_area_kpa2_intro_bowser_FadeBackgroundDarken);
API_CALLABLE(b_area_kpa2_intro_bowser_FadeBackgroundLighten);
API_CALLABLE(b_area_kpa2_intro_bowser_RemoveChillOut);
API_CALLABLE(b_area_kpa2_intro_bowser_SetBowserFireBreathScales);
API_CALLABLE(b_area_kpa2_intro_bowser_StarRodAppearEffect);
API_CALLABLE(b_area_kpa2_intro_bowser_StarRodPowerUpEffect);
API_CALLABLE(b_area_kpa2_intro_bowser_StartRumbleWithParams);
API_CALLABLE(b_area_kpa2_unused_bowser_FadeBackgroundDarken);
API_CALLABLE(b_area_kpa2_unused_bowser_FadeBackgroundLighten);
extern Vec3i b_area_kpa2_bowser_pos;
extern s32 b_area_kpa2_final_bowser_1_BoostedDefense[];
extern s32 b_area_kpa2_final_bowser_1_BoostedStatusTable[];
extern EvtScript b_area_kpa2_final_bowser_1_EVS_AnimateImgFX;
extern EvtScript b_area_kpa2_final_bowser_1_EVS_AttackMissed;
extern EvtScript b_area_kpa2_final_bowser_1_EVS_Attack_BodySlam;
extern EvtScript b_area_kpa2_final_bowser_1_EVS_Hit;
extern EvtScript b_area_kpa2_final_bowser_1_EVS_Idle;
extern EvtScript b_area_kpa2_final_bowser_1_EVS_NoDamageHit;
extern EvtScript b_area_kpa2_final_bowser_1_EVS_ReturnHome;
extern EvtScript b_area_kpa2_final_bowser_1_EVS_ShockReaction;
extern s32 b_area_kpa2_final_bowser_1_NormalDefense[];
extern s32 b_area_kpa2_final_bowser_1_StatusTable[];
extern s32 b_area_kpa2_final_bowser_2_BoostedDefense[];
extern s32 b_area_kpa2_final_bowser_2_BoostedStatusTable[];
extern EvtScript b_area_kpa2_final_bowser_2_EVS_AnimateImgFX;
extern EvtScript b_area_kpa2_final_bowser_2_EVS_AttackMissed;
extern EvtScript b_area_kpa2_final_bowser_2_EVS_HandlePhase;
extern EvtScript b_area_kpa2_final_bowser_2_EVS_Hit;
extern EvtScript b_area_kpa2_final_bowser_2_EVS_Hit_Inner;
extern EvtScript b_area_kpa2_final_bowser_2_EVS_Idle;
extern EvtScript b_area_kpa2_final_bowser_2_EVS_NoDamageHit;
extern EvtScript b_area_kpa2_final_bowser_2_EVS_ShockReaction;
extern s32 b_area_kpa2_final_bowser_2_NormalDefense[];
extern s32 b_area_kpa2_final_bowser_2_StatusTable[];
extern s32 b_area_kpa2_hallway_bowser_BoostedDefense[];
extern s32 b_area_kpa2_hallway_bowser_BoostedStatusTable[];
extern EvtScript b_area_kpa2_hallway_bowser_EVS_AnimateImgFX;
extern EvtScript b_area_kpa2_hallway_bowser_EVS_AttackMissed;
extern EvtScript b_area_kpa2_hallway_bowser_EVS_Attack_BodySlam;
extern EvtScript b_area_kpa2_hallway_bowser_EVS_BasicHit;
extern EvtScript b_area_kpa2_hallway_bowser_EVS_Death;
extern EvtScript b_area_kpa2_hallway_bowser_EVS_HandlePhase;
extern EvtScript b_area_kpa2_hallway_bowser_EVS_Hit;
extern EvtScript b_area_kpa2_hallway_bowser_EVS_Idle;
extern EvtScript b_area_kpa2_hallway_bowser_EVS_NoDamageHit;
extern EvtScript b_area_kpa2_hallway_bowser_EVS_ReturnHome;
extern EvtScript b_area_kpa2_hallway_bowser_EVS_ShockReaction;
extern s32 b_area_kpa2_hallway_bowser_NormalDefense[];
extern s32 b_area_kpa2_hallway_bowser_StatusTable[];
extern s32 b_area_kpa2_intro_bowser_BoostedDefense[];
extern s32 b_area_kpa2_intro_bowser_BoostedStatusTable[];
extern s32 b_area_kpa2_intro_bowser_DefenseTable[];
extern EvtScript b_area_kpa2_intro_bowser_EVS_AnimateImgFX;
extern EvtScript b_area_kpa2_intro_bowser_EVS_HandlePhase;
extern EvtScript b_area_kpa2_intro_bowser_EVS_Idle;
extern EvtScript b_area_kpa2_intro_bowser_EVS_OnHit;
extern EvtScript b_area_kpa2_intro_bowser_EVS_ReturnHome;
extern s32 b_area_kpa2_intro_bowser_StatusTable[];
extern Stage b_area_kpa2_kkj_01;
extern Stage b_area_kpa2_kkj_02;
extern Stage b_area_kpa2_kpa_01;
extern s32 b_area_kpa2_unused_bowser_DefenseTable[];
extern EvtScript b_area_kpa2_unused_bowser_EVS_HandleEvent;
extern EvtScript b_area_kpa2_unused_bowser_EVS_Idle;
extern EvtScript b_area_kpa2_unused_bowser_EVS_Recover;
extern EvtScript b_area_kpa2_unused_bowser_EVS_ReturnHome;
extern s32 b_area_kpa2_unused_bowser_StatusTable[];
extern EvtScript TTYD64_imp_23_Bowser1_Script_Shockwave1_23;
extern EvtScript TTYD64_imp_23_Bowser3_Script_Shockwave3_23;
extern EvtScript TTYD64_imp_23_Bowser2_Script_Shockwave2_23;
extern EvtScript TTYD64_imp_23_Bowser1_Script_HandleEvent_80221B18_23;
extern EvtScript TTYD64_imp_23_Bowser3_Script_HandleEvent_8022DF74_23;
extern EvtScript TTYD64_imp_23_Bowser3_Script_8022E93C_23;
extern EvtScript TTYD64_imp_23_Bowser2_Script_FireBreath2_23;
extern EvtScript TTYD64_imp_23_Bowser3_Script_FireBreath3_23;
extern EvtScript TTYD64_imp_23_Bowser2_Script_HandleEvent_80227AD0_23;
extern EvtScript TTYD64_imp_23_Bowser1_Script_FireBreath1_23;
extern EvtScript TTYD64_imp_23_Bowser3_Script_Thunderbolt3_23;
extern EvtScript TTYD64_imp_23_Bowser2_Script_Thunderbolt2_23;
extern EvtScript TTYD64_imp_23_UnusedBowser_Script_8021E93C_23;
extern EvtScript TTYD64_imp_23_IntroBowser_Script_80220990_23;
extern EvtScript TTYD64_imp_23_Bowser1_Script_80222E48_23;
extern EvtScript TTYD64_imp_23_Bowser2_Script_80228678_23;
extern EvtScript TTYD64_imp_23_Bowser3_Script_8022F4A4_23;
extern EvtScript TTYD64_imp_23_UnusedBowser_Script_8021DEB0_23;
extern EvtScript TTYD64_imp_23_Bowser1_Script_80226F08_23;
extern EvtScript TTYD64_imp_23_Bowser3_Script_80233408_23;
extern EvtScript TTYD64_imp_23_Bowser2_Script_8022C79C_23;
extern EvtScript TTYD64_imp_23_UnusedBowser_Script_8021E504_23;
extern EvtScript TTYD64_imp_23_Bowser2_Script_80229650_23;
extern EvtScript TTYD64_imp_23_Bowser1_Script_80223E20_23;
extern EvtScript TTYD64_imp_23_Bowser1_Script_HealSelf1_23;
extern EvtScript TTYD64_imp_23_Bowser2_Script_HealSelf2_23;
extern EvtScript TTYD64_imp_23_Bowser3_Script_HealSelf3_23;
extern EvtScript TTYD64_imp_23_Bowser1_Script_ClawSwipe1_23;
extern EvtScript TTYD64_imp_23_Bowser3_Script_ClawSwipe3_23;
extern EvtScript TTYD64_imp_23_Bowser2_Script_ClawSwipe2_23;
extern EvtScript TTYD64_imp_23_IntroBowser_Script_IntroFireBreath_23;
extern EvtScript TTYD64_imp_23_Bowser3_Script_UseMove3_23;
extern EvtScript TTYD64_imp_23_UnusedBowser_Script_8021DAFC_23;
extern EvtScript TTYD64_imp_23_IntroBowser_Script_IntroClawSwipe_23;
extern EvtScript TTYD64_imp_23_IntroBowser_Script_HandleEvent_8021F800_23;
extern EvtScript TTYD64_imp_23_IntroBowser_Script_IntroUseStarRod_23;
extern EvtScript TTYD64_imp_23_Bowser3_Script_Init_8022D6A0_23;
extern EvtScript TTYD64_imp_23_Bowser2_Script_80229BD0_23;
extern EvtScript TTYD64_imp_23_Bowser1_Script_80224380_23;
extern EvtScript TTYD64_imp_23_Bowser3_Script_8023083C_23;
extern EvtScript TTYD64_imp_23_Bowser2_Script_Init_80227770_23;
extern EvtScript TTYD64_imp_23_UnusedBowser_Script_TakeTurn_8021D880_23;
extern EvtScript TTYD64_imp_23_Bowser1_Script_Init_802216C0_23;
extern EvtScript TTYD64_imp_23_IntroBowser_Script_Init_8021F3D0_23;
extern EvtScript TTYD64_imp_23_IntroBowser_Script_TakeTurn_8021FC14_23;
extern EvtScript TTYD64_imp_23_Bowser1_Script_UseStarRod1_23;
extern EvtScript TTYD64_imp_23_Bowser1_Script_80224570_23;
extern EvtScript TTYD64_imp_23_Bowser2_Script_80229DC0_23;
extern EvtScript TTYD64_imp_23_Bowser3_Script_80230A2C_23;
extern EvtScript TTYD64_imp_23_UnusedBowser_Script_8021DA28_23;
extern EvtScript TTYD64_imp_23_UnusedBowser_Script_Init_8021D438_23;
extern Battle TTYD64_kpa2_FormationTable[];
extern EvtScript TTYD64_imp_23_Bowser1_Script_TakeTurn_80222B48_23;
extern s32 TTYD64_imp_23_IntroBowser_IdleAnimations_8021F1C0_23[];
extern s32 TTYD64_imp_23_Bowser2_IdleAnimations_80227560_23[];
extern s32 TTYD64_imp_23_Bowser1_IdleAnimations_802214B0_23[];
extern s32 TTYD64_imp_23_UnusedBowser_IdleAnimations_8021D2E0_23[];
extern s32 TTYD64_imp_23_Bowser3_IdleAnimations_8022D490_23[];
extern EvtScript TTYD64_imp_23_Bowser3_Script_TakeTurn_8022F2BC_23;
extern EvtScript TTYD64_imp_23_Bowser2_Script_TakeTurn_80228490_23;
extern EvtScript TTYD64_imp_23_Bowser2_Script_802284D4_23;
extern EvtScript TTYD64_imp_23_Bowser3_Script_8022F300_23;
extern ActorBlueprint TTYD64_imp_23_UnusedBowser_23_UnusedBowser;
extern ActorBlueprint TTYD64_imp_23_Bowser2_23_Bowser2;
extern ActorBlueprint TTYD64_imp_23_Bowser3_23_Bowser3;
extern ActorBlueprint TTYD64_imp_23_Bowser1_23_Bowser1;
extern ActorBlueprint TTYD64_imp_23_IntroBowser_23_IntroBowser;
extern ActorPartBlueprint TTYD64_imp_23_IntroBowser_PartsTable_8021F384_23[];
extern ActorPartBlueprint TTYD64_imp_23_Bowser2_PartsTable_80227724_23[];
extern ActorPartBlueprint TTYD64_imp_23_Bowser1_PartsTable_80221674_23[];
extern ActorPartBlueprint TTYD64_imp_23_Bowser3_PartsTable_8022D654_23[];
extern ActorPartBlueprint TTYD64_imp_23_UnusedBowser_PartsTable_8021D3EC_23[];
extern FormationRow TTYD64_kpa2_Formation_00[];
extern FormationRow TTYD64_kpa2_Formation_01[];
extern FormationRow TTYD64_kpa2_Formation_04[];
extern FormationRow TTYD64_kpa2_Formation_02[];
extern FormationRow TTYD64_kpa2_Formation_03[];

// clang-format off
EvtScript TTYD64_imp_23_Bowser1_Script_Shockwave1_23 = {
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 24)
        Add(LVar1, 65)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 420)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 40)
    Else
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 9)
        Add(LVar1, 26)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 250)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 40)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000F)
    Wait(10)
    Call(b_area_kpa2_hallway_bowser_FadeBackgroundDarken)
    Call(PlaySoundAtActor, ACTOR_SELF, 8481)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 15)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 90, LVar2, Float(1.0), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 90, LVar2, Float(1.0), LVarE, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 6)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 36, LVar2, Float(0.400390625), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 36, LVar2, Float(0.400390625), LVarE, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Wait(25)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, -45, 60, 0)
    Call(SetBattleCamDist, 530)
    Call(SetBattleCamOffsetY, 0)
    Call(MoveBattleCamOver, 80)
    Wait(10)
    Call(RemoveEffect, LVarF)
    Call(RemoveEffect, LVarE)
    Call(PlaySoundAtActor, ACTOR_SELF, 8482)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 13)
        Set(LVar1, 55)
        Call(PlayEffect_impl, 57, 0, LVar0, LVar1, LVar2, Float(1.0), 60, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 5)
        Set(LVar1, 22)
        Call(PlayEffect_impl, 57, 0, LVar0, LVar1, LVar2, Float(1.0), 60, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Thread
        Call(b_area_kpa2_hallway_bowser_FadeBackgroundLighten)
    EndThread
    Wait(8)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarB, 0, 0, 1, 16)
            Switch(LVarB)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarB, 5)
                        IfEq(LVarA, 5)
                            ExecWait(b_area_kpa2_hallway_bowser_EVS_AttackMissed)
                            Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                        EndIf
                    EndIf
                    Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
                    Wait(30)
                    Return
                EndCaseGroup
                CaseDefault
                    Wait(2)
                    Wait(2)
                    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                    Call(SetGoalToTarget, ACTOR_SELF)
                    IfFlag(LVar0, 0x40000)
                        Set(LVar1, 4)
                    Else
                        Set(LVar1, 4)
                    EndIf
                    Call(GetOwnerTarget, LVar0, 0)
                    IfEq(LVar0, 0)
                        Call(RemovePlayerBuffs, 0xFFFFFFF)
                    Else
                        Call(ClearStatusEffects, 256)
                        Call(RemovePlayerBuffs, 0x10000)
                    EndIf
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 272, 0xFFFF, 0, LVar1, 32)
                    IfNe(LVarA, 5)
                        Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
                    EndIf
                    Wait(30)
                    Return
            EndSwitch
        EndCaseGroup
        CaseDefault
    EndSwitch
    Call(FreezeBattleState, 1)
    Thread
        Wait(4)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        IfFlag(LVar0, 0x40000)
            Set(LVar1, 4)
        Else
            Set(LVar1, 4)
        EndIf
        Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
        Switch(LVarA)
            CaseOrEq(6)
            CaseOrEq(5)
                IfEq(LVarA, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
            EndCaseGroup
            CaseDefault
                Call(GetOwnerTarget, LVar2, 0)
                IfEq(LVar2, 0)
                    Call(RemovePlayerBuffs, 0xFFFFFFF)
                Else
                    Call(ClearStatusEffects, 256)
                    Call(RemovePlayerBuffs, 0x10000)
                EndIf
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 272, 0xFFFF, 0, LVar1, 32)
        EndSwitch
        Call(FreezeBattleState, 0)
    EndThread
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    IfFlag(LVar0, 0x40000)
        Set(LVar1, 4)
    Else
        Set(LVar1, 4)
    EndIf
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 272, 0xFFFF, 0, LVar1, 32)
    Call(RemovePlayerBuffs, 0xFFFFFFF)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
            Wait(15)
            IfEq(LVarF, 10)
                Return
            EndIf
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser3_Script_Shockwave3_23 = {
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 24)
        Add(LVar1, 97)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 420)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 40)
    Else
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 9)
        Add(LVar1, 39)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 375)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 40)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000F)
    Wait(10)
    Call(b_area_kpa2_final_bowser_2_FadeBackgroundDarken)
    Call(PlaySoundAtActor, ACTOR_SELF, 8481)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 22)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 90, LVar2, Float(1.0), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 90, LVar2, Float(1.0), LVarE, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 9)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 36, LVar2, Float(0.400390625), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 36, LVar2, Float(0.400390625), LVarE, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Wait(25)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, -45, 60, 0)
    Call(SetBattleCamDist, 530)
    Call(SetBattleCamOffsetY, 0)
    Call(MoveBattleCamOver, 80)
    Wait(10)
    Call(RemoveEffect, LVarF)
    Call(RemoveEffect, LVarE)
    Call(PlaySoundAtActor, ACTOR_SELF, 8482)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 19)
        Set(LVar1, 55)
        Call(PlayEffect_impl, 57, 0, LVar0, LVar1, LVar2, Float(1.0), 60, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 7)
        Set(LVar1, 22)
        Call(PlayEffect_impl, 57, 0, LVar0, LVar1, LVar2, Float(1.0), 60, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Thread
        Call(b_area_kpa2_final_bowser_2_FadeBackgroundLighten)
    EndThread
    Wait(8)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarB, 0, 0, 1, 16)
            Switch(LVarB)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarB, 5)
                        IfEq(LVarA, 5)
                            ExecWait(b_area_kpa2_final_bowser_2_EVS_AttackMissed)
                            Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                        EndIf
                    EndIf
                    Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
                    Wait(30)
                    Return
                EndCaseGroup
                CaseDefault
                    Wait(2)
                    Wait(2)
                    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                    Call(SetGoalToTarget, ACTOR_SELF)
                    IfFlag(LVar0, 0x40000)
                        Set(LVar1, 6)
                    Else
                        Set(LVar1, 6)
                    EndIf
                    Call(GetOwnerTarget, LVar0, 0)
                    IfEq(LVar0, 0)
                        Call(RemovePlayerBuffs, 0xFFFFFFF)
                    Else
                        Call(ClearStatusEffects, 256)
                        Call(RemovePlayerBuffs, 0x10000)
                    EndIf
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x2080110, 0xFFFF, 0, LVar1, 32)
                    IfNe(LVarA, 5)
                        Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
                    EndIf
                    Wait(30)
                    Return
            EndSwitch
        EndCaseGroup
        CaseDefault
    EndSwitch
    Call(FreezeBattleState, 1)
    Thread
        Wait(4)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        IfFlag(LVar0, 0x40000)
            Set(LVar1, 6)
        Else
            Set(LVar1, 6)
        EndIf
        Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
        Switch(LVarA)
            CaseOrEq(6)
            CaseOrEq(5)
                IfEq(LVarA, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
            EndCaseGroup
            CaseDefault
                Call(GetOwnerTarget, LVar2, 0)
                IfEq(LVar2, 0)
                    Call(RemovePlayerBuffs, 0xFFFFFFF)
                Else
                    Call(ClearStatusEffects, 256)
                    Call(RemovePlayerBuffs, 0x10000)
                EndIf
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x2080110, 0xFFFF, 0, LVar1, 32)
        EndSwitch
        Call(FreezeBattleState, 0)
    EndThread
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    IfFlag(LVar0, 0x40000)
        Set(LVar1, 6)
    Else
        Set(LVar1, 6)
    EndIf
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x2080110, 0xFFFF, 0, LVar1, 32)
    Call(RemovePlayerBuffs, 0xFFFFFFF)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
            Wait(15)
            IfEq(LVarF, 10)
                Return
            EndIf
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser2_Script_Shockwave2_23 = {
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 24)
        Add(LVar1, 65)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 420)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 40)
    Else
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 9)
        Add(LVar1, 26)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 250)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 40)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000F)
    Wait(10)
    Call(b_area_kpa2_hallway_bowser_FadeBackgroundDarken)
    Call(PlaySoundAtActor, ACTOR_SELF, 8481)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 15)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 90, LVar2, Float(1.0), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 90, LVar2, Float(1.0), LVarE, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 6)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 36, LVar2, Float(0.400390625), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 36, LVar2, Float(0.400390625), LVarE, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Wait(25)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, -45, 60, 0)
    Call(SetBattleCamDist, 530)
    Call(SetBattleCamOffsetY, 0)
    Call(MoveBattleCamOver, 80)
    Wait(10)
    Call(RemoveEffect, LVarF)
    Call(RemoveEffect, LVarE)
    Call(PlaySoundAtActor, ACTOR_SELF, 8482)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 13)
        Set(LVar1, 55)
        Call(PlayEffect_impl, 57, 0, LVar0, LVar1, LVar2, Float(1.0), 60, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 5)
        Set(LVar1, 22)
        Call(PlayEffect_impl, 57, 0, LVar0, LVar1, LVar2, Float(1.0), 60, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Thread
        Call(b_area_kpa2_hallway_bowser_FadeBackgroundLighten)
    EndThread
    Wait(8)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarB, 0, 0, 1, 16)
            Switch(LVarB)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarB, 5)
                        IfEq(LVarA, 5)
                            ExecWait(b_area_kpa2_hallway_bowser_EVS_AttackMissed)
                            Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                        EndIf
                    EndIf
                    Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
                    Wait(30)
                    Return
                EndCaseGroup
                CaseDefault
                    Wait(2)
                    Wait(2)
                    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                    Call(SetGoalToTarget, ACTOR_SELF)
                    IfFlag(LVar0, 0x40000)
                        Set(LVar1, 6)
                    Else
                        Set(LVar1, 6)
                    EndIf
                    Call(GetOwnerTarget, LVar0, 0)
                    IfEq(LVar0, 0)
                        Call(RemovePlayerBuffs, 0xFFFFFFF)
                    Else
                        Call(ClearStatusEffects, 256)
                        Call(RemovePlayerBuffs, 0x10000)
                    EndIf
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x2000110, 0xFFFF, 0, LVar1, 32)
                    IfNe(LVarA, 5)
                        Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
                    EndIf
                    Wait(30)
                    Return
            EndSwitch
        EndCaseGroup
        CaseDefault
    EndSwitch
    Call(FreezeBattleState, 1)
    Thread
        Wait(4)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        IfFlag(LVar0, 0x40000)
            Set(LVar1, 6)
        Else
            Set(LVar1, 6)
        EndIf
        Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
        Switch(LVarA)
            CaseOrEq(6)
            CaseOrEq(5)
                IfEq(LVarA, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
            EndCaseGroup
            CaseDefault
                Call(GetOwnerTarget, LVar2, 0)
                IfEq(LVar2, 0)
                    Call(RemovePlayerBuffs, 0xFFFFFFF)
                Else
                    Call(ClearStatusEffects, 256)
                    Call(RemovePlayerBuffs, 0x10000)
                EndIf
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x2000110, 0xFFFF, 0, LVar1, 32)
        EndSwitch
        Call(FreezeBattleState, 0)
    EndThread
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    IfFlag(LVar0, 0x40000)
        Set(LVar1, 6)
    Else
        Set(LVar1, 6)
    EndIf
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x2000110, 0xFFFF, 0, LVar1, 32)
    Call(RemovePlayerBuffs, 0xFFFFFFF)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
            Wait(15)
            IfEq(LVarF, 10)
                Return
            EndIf
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser1_Script_HandleEvent_80221B18_23 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetLastElement, LVarE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(56)
        CaseEq(9)
            Set(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_Hit)
            Return
        CaseEq(10)
            Set(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_BasicHit)
            Return
        CaseEq(32)
            SetConst(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_Hit)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_Death)
            Return
        CaseEq(14)
            Set(LVar0, 1)
            Set(LVar1, 0x810020)
            Set(LVar2, 0x810021)
            ExecWait(TTYD64_imp_23_Bowser1_Script_80226F08_23)
            Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
            IfNotFlag(LVar0, 0x40000)
                Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                IfFlag(LVar0, 4)
                    IfNotFlag(LVar0, 8)
                        BitwiseOrConst(LVar0, 8)
                        Call(SetActorVar, ACTOR_SELF, 1, LVar0)
                        Call(GetStatusFlags, ACTOR_SELF, LVar0)
                        IfNotFlag(LVar0, 0x351000)
                            Call(UseBattleCamPreset, 13)
                            Call(BattleCamTargetActor, ACTOR_SELF)
                            Call(MoveBattleCamOver, 30)
                            Call(ActorSpeak, 0x130077, ACTOR_SELF, 1, 0x81000B, 0x81000B)
                        EndIf
                    EndIf
                EndIf
            EndIf
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        CaseEq(36)
            Set(LVar0, 1)
            Set(LVar1, 0x810020)
            Set(LVar2, 0x810021)
            ExecWait(TTYD64_imp_23_Bowser1_Script_80226F08_23)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x810021)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_Death)
            Return
        CaseEq(11)
            Set(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_BasicHit)
            Return
        CaseEq(33)
            SetConst(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_Hit)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_Death)
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_ShockReaction)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Set(LVar1, 0x810003)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_ReturnHome)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_ShockReaction)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_Death)
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            Call(GetDamageSource, LVar2)
            Switch(LVar2)
                CaseOrEq(18)
                CaseOrEq(21)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x810007)
                    Wait(30)
                EndCaseGroup
                CaseDefault
                    Set(LVar1, 0x810007)
                    ExecWait(b_area_kpa2_hallway_bowser_EVS_NoDamageHit)
            EndSwitch
        EndCaseGroup
        CaseEq(31)
            SetConst(LVar0, 1)
            Set(LVar1, 0x810002)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(27)
        CaseEq(53)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x810012)
            ExecWait(Ref(EVS_Enemy_Recover))
            Call(SetAnimation, ACTOR_SELF, 1, 0x810014)
            Call(ShakeCam, 1, 0, 4, Float(3.0))
        CaseEq(48)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(1000)
        CaseEq(63)
            Call(b_area_kpa2_hallway_bowser_FadeBackgroundLighten)
        CaseEq(19)
            Call(FreezeBattleCam, 1)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 1)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfNotFlag(LVar3, 0x80000)
                Set(LVar3, 50)
                Set(LVar4, 40)
            Else
                Set(LVar3, 20)
                Set(LVar4, 16)
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, LVar3)
            Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 50, 0, 0, 0, 0, 0, 0, 0, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, LVar4)
            Call(PlayEffect_impl, 56, 1, LVar0, LVar1, LVar2, Float(0.7001953125), 30, 0, 0, 0, 0, 0, 0, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x40000, 0)
            Call(SetActorVar, ACTOR_SELF, 3, 0)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa2_hallway_bowser_NormalDefense))
            Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kpa2_hallway_bowser_StatusTable))
            Set(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_Hit)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            IfNotFlag(LVar0, 2)
                BitwiseOrConst(LVar0, 2)
                BitwiseOrConst(LVar0, 4)
                Call(SetActorVar, ACTOR_SELF, 1, LVar0)
                Call(UseBattleCamPreset, 13)
                Call(BattleCamTargetActor, ACTOR_SELF)
                Call(MoveBattleCamOver, 30)
                Call(ActorSpeak, 0x130075, ACTOR_SELF, 1, 0x81000D, 0x81000D)
                Call(SetAnimation, ACTOR_SELF, 1, 0x810001)
                Loop(2)
                    Set(LVar0, 0)
                    Loop(10)
                        Add(LVar0, 18)
                        Call(SetActorYaw, ACTOR_SELF, LVar0)
                        Wait(1)
                    EndLoop
                    Wait(5)
                    Set(LVar0, 180)
                    Loop(10)
                        Sub(LVar0, 18)
                        Call(SetActorYaw, ACTOR_SELF, LVar0)
                        Wait(1)
                    EndLoop
                    Call(SetActorYaw, ACTOR_SELF, 0)
                    Wait(5)
                EndLoop
                Wait(20)
                Call(ActorSpeak, 0x130076, ACTOR_SELF, 1, 0x81000D, 0x81000D)
                Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
            EndIf
            Call(FreezeBattleCam, 0)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 30)
            Wait(30)
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser3_Script_HandleEvent_8022DF74_23 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetLastElement, LVarE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(56)
        CaseOrEq(9)
        CaseOrEq(10)
            Set(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_final_bowser_2_EVS_Hit)
            Return
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(Ref(EVS_Enemy_Hit))
            SetConst(LVar1, 0x81000D)
            ExecWait(TTYD64_imp_23_Bowser3_Script_8022E93C_23)
            Return
        CaseEq(14)
            Set(LVar0, 1)
            Set(LVar1, 0x810020)
            Set(LVar2, 0x810021)
            ExecWait(TTYD64_imp_23_Bowser3_Script_80233408_23)
        CaseEq(36)
            Set(LVar0, 1)
            Set(LVar1, 0x810020)
            Set(LVar2, 0x810021)
            ExecWait(TTYD64_imp_23_Bowser3_Script_80233408_23)
            SetConst(LVar1, 0x810021)
            ExecWait(TTYD64_imp_23_Bowser3_Script_8022E93C_23)
            Return
        CaseEq(11)
            Set(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_final_bowser_2_EVS_Hit)
            Return
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(Ref(EVS_Enemy_Hit))
            SetConst(LVar1, 0x81000D)
            ExecWait(TTYD64_imp_23_Bowser3_Script_8022E93C_23)
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_final_bowser_2_EVS_ShockReaction)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Set(LVar1, 0x810003)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_ReturnHome)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_final_bowser_2_EVS_ShockReaction)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(TTYD64_imp_23_Bowser3_Script_8022E93C_23)
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            Call(GetDamageSource, LVar2)
            Switch(LVar2)
                CaseOrEq(18)
                CaseOrEq(21)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x810007)
                    Wait(30)
                EndCaseGroup
                CaseDefault
                    Set(LVar1, 0x810007)
                    ExecWait(b_area_kpa2_final_bowser_2_EVS_NoDamageHit)
            EndSwitch
        EndCaseGroup
        CaseEq(31)
            SetConst(LVar0, 1)
            Set(LVar1, 0x810002)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(27)
        CaseEq(53)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x810012)
            ExecWait(Ref(EVS_Enemy_Recover))
            Call(SetAnimation, ACTOR_SELF, 1, 0x810014)
            Call(ShakeCam, 1, 0, 4, Float(3.0))
        CaseEq(63)
            Call(b_area_kpa2_final_bowser_2_FadeBackgroundLighten)
        CaseEq(48)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(1000)
        CaseEq(29)
            Set(LVar1, 0x810002)
            ExecWait(b_area_kpa2_final_bowser_2_EVS_NoDamageHit)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
            Call(SetActorFlagBits, ACTOR_SELF, 0x400000, 1)
            Call(SetBattleFlagBits, 0x60000, 1)
            Call(SetEndBattleFadeOutRate, 10)
            Return
        CaseEq(20)
            Call(FreezeBattleCam, 1)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 1)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfNotFlag(LVar3, 0x80000)
                Set(LVar3, 75)
                Set(LVar4, 60)
            Else
                Set(LVar3, 30)
                Set(LVar4, 24)
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, LVar3)
            Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 75, 0, 0, 0, 0, 0, 0, 0, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, LVar4)
            Call(PlayEffect_impl, 56, 1, LVar0, LVar1, LVar2, Float(1.0498046875), 50, 0, 0, 0, 0, 0, 0, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x80000, 0)
            Call(SetActorVar, ACTOR_SELF, 3, 0)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa2_final_bowser_2_NormalDefense))
            Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kpa2_final_bowser_2_StatusTable))
            Set(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_final_bowser_2_EVS_Hit_Inner)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            IfNotFlag(LVar0, 32)
                BitwiseOrConst(LVar0, 32)
                Call(SetActorVar, ACTOR_SELF, 1, LVar0)
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfNotFlag(LVar3, 0x80000)
                    Set(LVar3, 90)
                Else
                    Set(LVar3, 36)
                EndIf
                Call(UseBattleCamPreset, 19)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Sub(LVar0, 15)
                Add(LVar1, LVar3)
                Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
                Call(SetBattleCamDist, 420)
                Call(SetBattleCamOffsetY, 0)
                Call(MoveBattleCamOver, 30)
                Call(ActorSpeak, 0x1300A7, ACTOR_SELF, 1, 0x81000D, 0x81000D)
                Call(UseBattleCamPreset, 2)
                Call(MoveBattleCamOver, 45)
            EndIf
            Call(FreezeBattleCam, 0)
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser3_Script_8022E93C_23 = {
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x80000, 0)
    Call(RemoveActorDecoration, ACTOR_SELF, 1, 1)
    Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
    Wait(14)
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000E)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 15)
        Add(LVar1, 67)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 420)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 15)
    Else
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 6)
        Add(LVar1, 27)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 420)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 15)
    EndIf
    Wait(30)
    Call(PlaySoundAtActor, ACTOR_SELF, 8488)
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000D)
    Thread
        Call(MakeLerp, 0, 80, 8, 4)
        Set(LVar2, 0)
        Label(0)
        Call(UpdateLerp)
        Label(1)
        IfGe(LVar2, LVar0)
            Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Call(GetActorScale, ACTOR_SELF, LVar6, LVar6, LVar7)
            Call(b_area_kpa2_final_bowser_2_MakeLightningBolts, LVar3, LVar4, LVar5, LVar6)
            IfEq(LVar1, 1)
                Goto(0)
            EndIf
        Else
            Wait(1)
            Add(LVar2, 1)
            Goto(1)
        EndIf
    EndThread
    Wait(20)
    Thread
        Wait(30)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfNotFlag(LVarA, 0x80000)
            Add(LVar1, 60)
        Else
            Add(LVar1, 24)
        EndIf
        Call(PlayEffect_impl, 56, 1, LVar0, LVar1, LVar2, Float(1.0498046875), 50, 0, 0, 0, 0, 0, 0, 0)
        Set(LVar1, 50)
        IfGt(LVar1, 0)
            SetF(LVar0, Float(1.5))
            Loop(LVar1)
                SubF(LVar0, Float(0.009765625))
                Call(SetActorScale, ACTOR_SELF, LVar0, LVar0, Float(1.0))
                Wait(1)
            EndLoop
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
        EndIf
    EndThread
    Call(EnableActorBlur, ACTOR_SELF, 1)
    Call(MakeLerp, 0, 6480, 100, 10)
    Label(2)
    Call(UpdateLerp)
    Mod(LVar0, 360)
    Call(SetActorYaw, ACTOR_SELF, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(2)
    EndIf
    Call(EnableActorBlur, ACTOR_SELF, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000E)
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_SELF, 8489)
    Call(SetAnimation, ACTOR_SELF, 1, 0x81001C)
    Thread
        Call(b_area_kpa2_final_bowser_1_StartRumbleWithParams, 180, 16)
        Call(ShakeCam, 1, 0, 4, Float(3.0))
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(PlayEffect_impl, 6, 4, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(SetPartScale, ACTOR_SELF, 1, Float(1.099609375), Float(0.9296875), Float(1.0))
    Wait(1)
    Call(SetPartScale, ACTOR_SELF, 1, Float(1.2001953125), Float(0.849609375), Float(1.0))
    Wait(1)
    Call(SetPartScale, ACTOR_SELF, 1, Float(1.25), Float(0.7998046875), Float(1.0))
    Wait(1)
    Call(SetPartScale, ACTOR_SELF, 1, Float(1.2998046875), Float(0.75), Float(1.0))
    Wait(1)
    Call(SetPartScale, ACTOR_SELF, 1, Float(1.2001953125), Float(0.8701171875), Float(1.0))
    Wait(1)
    Call(SetPartScale, ACTOR_SELF, 1, Float(1.099609375), Float(0.919921875), Float(1.0))
    Wait(1)
    Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
    Wait(30)
    Call(SetActorSize, ACTOR_SELF, 52, 115)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 15)
        Add(LVar1, 45)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 300)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 40)
    Else
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 6)
        Add(LVar1, 18)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 300)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 40)
    EndIf
    Call(ActorSpeak, 0x1300A9, ACTOR_SELF, 1, 0x81001D, 0x81001C)
    Call(SetActorFlagBits, ACTOR_SELF, 0x400000, 1)
    Call(SetBattleFlagBits, 0x60000, 1)
    Call(SetEndBattleFadeOutRate, 20)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser2_Script_FireBreath2_23 = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 30)
        Add(LVar1, 81)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 400)
        Call(MoveBattleCamOver, 40)
    Else
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 30)
        Add(LVar1, 56)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 350)
        Call(MoveBattleCamOver, 40)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x810016)
    Wait(35)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810017)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 55)
    Wait(10)
    Call(GetPartEventFlags, ACTOR_SELF, 1, LVar3)
    Call(GetStatusFlags, ACTOR_SELF, LVar4)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfFlag(LVar3, 0x80000)
        IfNotFlag(LVar4, 0x80000)
            Sub(LVar0, 70)
            Add(LVar1, 35)
        Else
            Sub(LVar0, 28)
            Add(LVar1, 14)
        EndIf
    Else
        IfNotFlag(LVar4, 0x80000)
            Sub(LVar0, 75)
            Add(LVar1, 49)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 19)
        EndIf
    EndIf
    Add(LVar2, 10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 40)
    Set(LVar4, 20)
    Call(GetPartEventFlags, ACTOR_SELF, 1, LVar6)
    IfFlag(LVar6, 0x80000)
        Call(PlayEffect_impl, 55, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, 50, 1, 24, 0, 0, 0)
    Else
        Call(GetStatusFlags, ACTOR_SELF, LVar7)
        IfNotFlag(LVar7, 0x80000)
            Add(LVar0, 15)
        Else
            Add(LVar0, 6)
        EndIf
        Sub(LVar3, 10)
        Call(PlayEffect_impl, 55, 2, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, 50, 1, 24, 0, 0, 0)
        Call(b_area_kpa2_final_bowser_1_SetBowserFireBreathScales, LVarF)
    EndIf
    Thread
        Call(b_area_kpa2_final_bowser_1_StartRumbleWithParams, 50, 148)
        Call(PlaySound, 957)
        Wait(70)
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
            Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
            IfFlag(LVar0, 0x80000)
                Set(LVar0, 20)
            Else
                Set(LVar0, 10)
            EndIf
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x8000002, 0xFFFF, 0, LVar0, 32)
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
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810018)
            Wait(30)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810019)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
            Wait(30)
            Call(GetOwnerTarget, LVar0, 0)
            IfEq(LVar0, 0)
                ExecWait(b_area_kpa2_hallway_bowser_EVS_AttackMissed)
            EndIf
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(30)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
            IfFlag(LVar0, 0x80000)
                Set(LVar0, 20)
            Else
                Set(LVar0, 10)
            EndIf
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x8000002, 0xFFFF, 0, LVar0, 32)
            Switch(LVarF)
                CaseOrEq(0)
                CaseOrEq(2)
                CaseOrEq(10)
                    IfEq(LVarF, 10)
                        Return
                    EndIf
                EndCaseGroup
            EndSwitch
    EndSwitch
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810018)
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810019)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
    Wait(30)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser3_Script_FireBreath3_23 = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 30)
        Add(LVar1, 81)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 400)
        Call(MoveBattleCamOver, 40)
    Else
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 30)
        Add(LVar1, 56)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 350)
        Call(MoveBattleCamOver, 40)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x810016)
    Wait(35)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810017)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 55)
    Wait(10)
    Call(GetPartEventFlags, ACTOR_SELF, 1, LVar3)
    Call(GetStatusFlags, ACTOR_SELF, LVar4)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfFlag(LVar3, 0x80000)
        IfNotFlag(LVar4, 0x80000)
            Sub(LVar0, 70)
            Add(LVar1, 35)
        Else
            Sub(LVar0, 28)
            Add(LVar1, 14)
        EndIf
    Else
        IfNotFlag(LVar4, 0x80000)
            Sub(LVar0, 75)
            Add(LVar1, 49)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 19)
        EndIf
    EndIf
    Add(LVar2, 10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 40)
    Set(LVar4, 20)
    Call(GetPartEventFlags, ACTOR_SELF, 1, LVar6)
    IfFlag(LVar6, 0x80000)
        Call(PlayEffect_impl, 55, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, 50, 1, 24, 0, 0, 0)
    Else
        Call(GetStatusFlags, ACTOR_SELF, LVar7)
        IfNotFlag(LVar7, 0x80000)
            Add(LVar0, 15)
        Else
            Add(LVar0, 6)
        EndIf
        Sub(LVar3, 10)
        Call(PlayEffect_impl, 55, 2, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, 50, 1, 24, 0, 0, 0)
        Call(b_area_kpa2_final_bowser_2_SetBowserFireBreathScales, LVarF)
    EndIf
    Thread
        Call(b_area_kpa2_final_bowser_1_StartRumbleWithParams, 50, 148)
        Call(PlaySound, 957)
        Wait(70)
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
            Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
            IfFlag(LVar0, 0x80000)
                Set(LVar0, 20)
            Else
                Set(LVar0, 10)
            EndIf
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x8000002, 0xFFFF, 0, LVar0, 32)
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
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810018)
            Wait(30)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810019)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
            Wait(30)
            Call(GetOwnerTarget, LVar0, 0)
            IfEq(LVar0, 0)
                ExecWait(b_area_kpa2_final_bowser_2_EVS_AttackMissed)
            EndIf
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(30)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
            IfFlag(LVar0, 0x80000)
                Set(LVar0, 20)
            Else
                Set(LVar0, 10)
            EndIf
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x8000002, 0xFFFF, 0, LVar0, 32)
            Switch(LVarF)
                CaseOrEq(0)
                CaseOrEq(2)
                CaseOrEq(10)
                    IfEq(LVarF, 10)
                        Return
                    EndIf
                EndCaseGroup
            EndSwitch
    EndSwitch
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810018)
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810019)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
    Wait(30)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser2_Script_HandleEvent_80227AD0_23 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetLastElement, LVarE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(56)
        CaseOrEq(9)
        CaseOrEq(10)
            Set(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_Hit)
            Return
        EndCaseGroup
        CaseEq(14)
            Set(LVar0, 1)
            Set(LVar1, 0x810020)
            Set(LVar2, 0x810021)
            ExecWait(TTYD64_imp_23_Bowser2_Script_8022C79C_23)
        CaseEq(36)
            Set(LVar0, 1)
            Set(LVar1, 0x810020)
            Set(LVar2, 0x810021)
            ExecWait(TTYD64_imp_23_Bowser2_Script_8022C79C_23)
            Return
        CaseEq(11)
            Set(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_Hit)
            Return
        CaseEq(33)
            SetConst(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_Hit)
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_ShockReaction)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Set(LVar1, 0x810003)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_ReturnHome)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_ShockReaction)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Set(LVar1, 0x810003)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_ReturnHome)
        CaseOrEq(23)
        CaseOrEq(25)
            Call(GetDamageSource, LVar2)
            Switch(LVar2)
                CaseOrEq(18)
                CaseOrEq(21)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x810007)
                    Wait(30)
                EndCaseGroup
                CaseDefault
                    Set(LVar1, 0x810007)
                    ExecWait(b_area_kpa2_final_bowser_1_EVS_NoDamageHit)
            EndSwitch
        EndCaseGroup
        CaseEq(31)
            SetConst(LVar0, 1)
            Set(LVar1, 0x810002)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(27)
        CaseEq(32)
            SetConst(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_Hit)
            Return
        CaseEq(53)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x810012)
            ExecWait(Ref(EVS_Enemy_Recover))
            Call(SetAnimation, ACTOR_SELF, 1, 0x810014)
            Call(ShakeCam, 1, 0, 4, Float(3.0))
        CaseEq(63)
            Call(b_area_kpa2_final_bowser_1_FadeBackgroundLighten)
        CaseEq(48)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(1000)
        CaseEq(29)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfNotFlag(LVar3, 0x80000)
                Set(LVar3, 60)
                Set(LVar4, 97)
            Else
                Set(LVar3, 24)
                Set(LVar4, 39)
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, LVar3)
            Call(PlayEffect_impl, 82, 4, LVar0, LVar1, LVar2, Float(1.5), 20, 0, 0, 0, 0, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810008)
            Wait(30)
            Call(UseBattleCamPreset, 19)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 15)
            Add(LVar1, LVar4)
            Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
            Call(SetBattleCamDist, 420)
            Call(SetBattleCamOffsetY, 0)
            Call(MoveBattleCamOver, 30)
            Wait(30)
            Call(ActorSpeak, 0x130085, ACTOR_SELF, 1, 0x810007, 0x810007)
            Call(UseBattleCamPreset, 14)
            Call(BattleCamTargetActor, 0)
            Call(MoveBattleCamOver, 20)
            Wait(20)
            Call(GetCurrentPartnerID, LVar0)
            Switch(LVar0)
                CaseEq(2)
                    Call(ActorSpeak, 0x130087, 256, 0, -1, -1)
                CaseEq(3)
                    Call(ActorSpeak, 0x130088, 256, 0, -1, -1)
                CaseEq(4)
                    Call(ActorSpeak, 0x130089, 256, 0, -1, -1)
                CaseEq(9)
                    Call(ActorSpeak, 0x13008A, 256, 0, -1, -1)
                CaseEq(6)
                    Call(ActorSpeak, 0x13008B, 256, 0, -1, -1)
                CaseEq(7)
                    Call(ActorSpeak, 0x13008C, 256, 0, -1, -1)
                CaseEq(8)
                    Call(ActorSpeak, 0x13008D, 256, 0, -1, -1)
                CaseDefault
                    Call(ActorSpeak, 0x130086, 256, 0, -1, -1)
            EndSwitch
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 30)
            Call(GetActorHP, ACTOR_SELF, GameByte(394))
            Call(SetActorFlagBits, ACTOR_SELF, 0x400000, 1)
            Call(SetBattleFlagBits, 0x60000, 1)
            Call(SetEndBattleFadeOutRate, 20)
            Return
        CaseEq(20)
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser1_Script_FireBreath1_23 = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 30)
        Add(LVar1, 65)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 400)
        Call(MoveBattleCamOver, 40)
    Else
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 30)
        Add(LVar1, 45)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 350)
        Call(MoveBattleCamOver, 40)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x810016)
    Wait(35)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810017)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 55)
    Wait(10)
    Call(GetPartEventFlags, ACTOR_SELF, 1, LVar3)
    Call(GetStatusFlags, ACTOR_SELF, LVar4)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfFlag(LVar3, 0x40000)
        IfNotFlag(LVar4, 0x80000)
            Sub(LVar0, 70)
            Add(LVar1, 35)
        Else
            Sub(LVar0, 28)
            Add(LVar1, 14)
        EndIf
    Else
        IfNotFlag(LVar4, 0x80000)
            Sub(LVar0, 50)
            Add(LVar1, 33)
        Else
            Sub(LVar0, 20)
            Add(LVar1, 13)
        EndIf
    EndIf
    Add(LVar2, 10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 40)
    Set(LVar4, 20)
    Call(GetPartEventFlags, ACTOR_SELF, 1, LVar6)
    IfFlag(LVar6, 0x40000)
        Call(PlayEffect_impl, 55, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, 50, 1, 24, 0, 0, 0)
    Else
        Call(PlayEffect_impl, 55, 2, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, 50, 1, 24, 0, 0, 0)
        Call(b_area_kpa2_hallway_bowser_SetBowserFireBreathScales, LVarF)
    EndIf
    Thread
        Call(b_area_kpa2_hallway_bowser_StartRumbleWithParams, 50, 148)
        Call(PlaySound, 957)
        Wait(70)
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
            Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
            IfFlag(LVar0, 0x40000)
                Set(LVar0, 16)
            Else
                Set(LVar0, 8)
            EndIf
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x8000002, 0xFFFF, 0, LVar0, 32)
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
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810018)
            Wait(30)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810019)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
            Wait(30)
            Call(GetOwnerTarget, LVar0, 0)
            IfEq(LVar0, 0)
                ExecWait(b_area_kpa2_hallway_bowser_EVS_AttackMissed)
            EndIf
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(30)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
            IfFlag(LVar0, 0x40000)
                Set(LVar0, 16)
            Else
                Set(LVar0, 8)
            EndIf
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x8000002, 0xFFFF, 0, LVar0, 32)
            Switch(LVarF)
                CaseOrEq(0)
                CaseOrEq(2)
                CaseOrEq(10)
                    IfEq(LVarF, 10)
                        Return
                    EndIf
                EndCaseGroup
            EndSwitch
    EndSwitch
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810018)
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810019)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
    Wait(30)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser3_Script_Thunderbolt3_23 = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 13)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Call(PlaySoundAtActor, ACTOR_SELF, 1007)
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000F)
    Call(b_area_kpa2_final_bowser_2_FadeBackgroundDarken)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 54)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 107, 2, LVar0, LVar1, LVar2, Float(1.5), 50, 0, 0, 0, 0, 0, 0, 0)
        Wait(50)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 22)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 135, LVar2, Float(1.5), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 8481)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 135, LVar2, Float(1.5), LVarE, 0, 0, 0, 0, 0, 0, 0)
        Wait(30)
        Call(RemoveEffect, LVarF)
        Call(RemoveEffect, LVarE)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 21)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 107, 2, LVar0, LVar1, LVar2, Float(0.599609375), 50, 0, 0, 0, 0, 0, 0, 0)
        Wait(50)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 9)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 54, LVar2, Float(0.599609375), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 8481)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 54, LVar2, Float(0.599609375), LVarE, 0, 0, 0, 0, 0, 0, 0)
        Wait(30)
        Call(RemoveEffect, LVarF)
        Call(RemoveEffect, LVarE)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8487)
    Call(SetGoalToTarget, ACTOR_SELF)
    Thread
        Call(TTYD64_GetPartnerHP_API, LVar0)
        IfGt(LVar0, 0)
            Call(AddGoalPos, ACTOR_SELF, -23, 0, 0)
        EndIf
        Call(GetGoalPos, ACTOR_SELF, LVar0, 0, LVar1)
        Call(b_area_kpa2_final_bowser_2_UnkLightningBoltFxFunc1, LVar0, LVar1)
    EndThread
    Wait(5)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
            IfFlag(LVar0, 0x80000)
                Set(LVar0, 20)
                Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000020, 0, 0, LVar0, 32)
            Else
                Set(LVar0, 10)
                Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000020, 0, 0, LVar0, 32)
            EndIf
            Switch(LVarF)
                CaseOrEq(0)
                CaseOrEq(2)
                CaseOrEq(10)
                    IfEq(LVarF, 10)
                        Wait(30)
                        Call(b_area_kpa2_final_bowser_2_FadeBackgroundLighten)
                        Return
                    EndIf
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
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
            IfFlag(LVar0, 0x80000)
                Set(LVar0, 20)
                Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000020, 0, 0, LVar0, 32)
            Else
                Set(LVar0, 10)
                Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000020, 0, 0, LVar0, 32)
            EndIf
            Switch(LVarF)
                CaseOrEq(0)
                CaseOrEq(2)
                CaseOrEq(10)
                EndCaseGroup
            EndSwitch
    EndSwitch
    Wait(30)
    Call(b_area_kpa2_final_bowser_2_FadeBackgroundLighten)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Set(LVar1, 0x810003)
    ExecWait(b_area_kpa2_final_bowser_1_EVS_ReturnHome)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser2_Script_Thunderbolt2_23 = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 13)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Call(PlaySoundAtActor, ACTOR_SELF, 1007)
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000F)
    Call(b_area_kpa2_final_bowser_1_FadeBackgroundDarken)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 54)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 107, 2, LVar0, LVar1, LVar2, Float(1.5), 50, 0, 0, 0, 0, 0, 0, 0)
        Wait(50)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 22)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 135, LVar2, Float(1.5), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 8481)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 135, LVar2, Float(1.5), LVarE, 0, 0, 0, 0, 0, 0, 0)
        Wait(30)
        Call(RemoveEffect, LVarF)
        Call(RemoveEffect, LVarE)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 21)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 107, 2, LVar0, LVar1, LVar2, Float(0.599609375), 50, 0, 0, 0, 0, 0, 0, 0)
        Wait(50)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 9)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 54, LVar2, Float(0.599609375), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 8481)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 54, LVar2, Float(0.599609375), LVarE, 0, 0, 0, 0, 0, 0, 0)
        Wait(30)
        Call(RemoveEffect, LVarF)
        Call(RemoveEffect, LVarE)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8487)
    Call(SetGoalToTarget, ACTOR_SELF)
    Thread
        Call(TTYD64_GetPartnerHP_API, LVar0)
        IfGt(LVar0, 0)
            Call(AddGoalPos, ACTOR_SELF, -23, 0, 0)
        EndIf
        Call(GetGoalPos, ACTOR_SELF, LVar0, 0, LVar1)
        Call(b_area_kpa2_final_bowser_1_UnkLightningBoltFxFunc1, LVar0, LVar1)
    EndThread
    Wait(5)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
            IfFlag(LVar0, 0x80000)
                Set(LVar0, 20)
                Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000020, 0, 0, LVar0, 32)
            Else
                Set(LVar0, 10)
                Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000020, 0, 0, LVar0, 32)
            EndIf
            Switch(LVarF)
                CaseOrEq(0)
                CaseOrEq(2)
                CaseOrEq(10)
                    IfEq(LVarF, 10)
                        Wait(30)
                        Call(b_area_kpa2_final_bowser_1_FadeBackgroundLighten)
                        Return
                    EndIf
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
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
            IfFlag(LVar0, 0x80000)
                Set(LVar0, 20)
                Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000020, 0, 0, LVar0, 32)
            Else
                Set(LVar0, 10)
                Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000020, 0, 0, LVar0, 32)
            EndIf
            Switch(LVarF)
                CaseOrEq(0)
                CaseOrEq(2)
                CaseOrEq(10)
                EndCaseGroup
            EndSwitch
    EndSwitch
    Wait(30)
    Call(b_area_kpa2_final_bowser_1_FadeBackgroundLighten)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Set(LVar1, 0x810003)
    ExecWait(b_area_kpa2_final_bowser_1_EVS_ReturnHome)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_UnusedBowser_Script_8021E93C_23 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 13)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000F)
    Wait(10)
    Call(b_area_kpa2_unused_bowser_FadeBackgroundDarken)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 15)
    Sub(LVar2, 3)
    Call(PlayEffect_impl, 53, 2, LVar0, 90, LVar2, Float(1.0), LVarF, 0, 0, 0, 0, 0, 0, 0)
    Sub(LVar2, 3)
    Call(PlayEffect_impl, 60, 2, LVar0, 90, LVar2, Float(1.0), LVarE, 0, 0, 0, 0, 0, 0, 0)
    Wait(16)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 45)
    Wait(19)
    Call(RemoveEffect, LVarF)
    Call(RemoveEffect, LVarE)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 13)
    Set(LVar1, 55)
    Call(PlayEffect_impl, 57, 0, LVar0, LVar1, LVar2, Float(1.0), 60, 0, 0, 0, 0, 0, 0, 0)
    Thread
        Call(b_area_kpa2_unused_bowser_FadeBackgroundLighten)
    EndThread
    Wait(8)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(FreezeBattleState, 1)
            Thread
                Wait(2)
                Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                Call(EnemyTestTarget, ACTOR_SELF, LVarB, 0, 0, 1, 16)
                Switch(LVarB)
                    CaseOrEq(6)
                    CaseOrEq(5)
                        IfEq(LVarB, 5)
                            Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                        EndIf
                    EndCaseGroup
                    CaseDefault
                        Call(GetOwnerTarget, LVar0, 0)
                        IfEq(LVar0, 0)
                            Call(RemovePlayerBuffs, 0xFFFFFFF)
                        Else
                            Call(ClearStatusEffects, 256)
                            Call(RemovePlayerBuffs, 0x10000)
                        EndIf
                        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 272, 0, 0, 4, 32)
                EndSwitch
                Call(FreezeBattleState, 0)
            EndThread
            Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
            Wait(15)
            ExecWait(b_area_kpa2_unused_bowser_EVS_Recover)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(30)
            Return
        EndCaseGroup
        CaseDefault
    EndSwitch
    Call(FreezeBattleState, 1)
    Thread
        Wait(2)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
        Switch(LVarA)
            CaseOrEq(6)
            CaseOrEq(5)
                IfEq(LVarA, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
            EndCaseGroup
            CaseDefault
                Call(GetOwnerTarget, LVar0, 0)
                IfEq(LVar0, 0)
                    Call(RemovePlayerBuffs, 0xFFFFFFF)
                Else
                    Call(ClearStatusEffects, 256)
                    Call(RemovePlayerBuffs, 0x10000)
                EndIf
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 272, 0, 0, 4, 32)
        EndSwitch
        Call(FreezeBattleState, 0)
    EndThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetOwnerTarget, LVar0, 0)
    IfEq(LVar0, 0)
        Call(RemovePlayerBuffs, 0xFFFFFFF)
    Else
        Call(ClearStatusEffects, 256)
        Call(RemovePlayerBuffs, 0x10000)
    EndIf
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 272, 0, 0x20000, 4, 32)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
            Wait(15)
            ExecWait(b_area_kpa2_unused_bowser_EVS_Recover)
            IfEq(LVarF, 10)
                Return
            EndIf
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_IntroBowser_Script_80220990_23 = {
    Call(b_area_kpa2_intro_bowser_FadeBackgroundDarken)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar0, 15)
        Add(LVar1, 90)
        Thread
            Call(PlaySoundAtActor, ACTOR_SELF, 8483)
            Add(LVar2, 10)
            Call(b_area_kpa2_intro_bowser_StarRodAppearEffect, LVar0, LVar1, LVar2, Float(2.5), Float(0.0498046875))
        EndThread
    Else
        Add(LVar0, 6)
        Add(LVar1, 36)
        Thread
            Call(PlaySoundAtActor, ACTOR_SELF, 8483)
            Add(LVar2, 10)
            Call(b_area_kpa2_intro_bowser_StarRodAppearEffect, LVar0, LVar1, LVar2, Float(2.5), Float(0.01953125))
        EndThread
    EndIf
    Wait(65)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar0, 15)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 90, LVar2, Float(1.0), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 60, 2, LVar0, 90, LVar2, Float(1.0), LVarE, 0, 0, 0, 0, 0, 0, 0)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 90, LVar2, Float(1.0), LVarD, 0, 0, 0, 0, 0, 0, 0)
    Else
        Add(LVar0, 6)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 36, LVar2, Float(0.400390625), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 60, 2, LVar0, 36, LVar2, Float(0.400390625), LVarE, 0, 0, 0, 0, 0, 0, 0)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 36, LVar2, Float(0.400390625), LVarD, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8481)
    Wait(30)
    Call(RemoveEffect, LVarF)
    Call(RemoveEffect, LVarE)
    Call(RemoveEffect, LVarD)
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x40000, 1)
    Call(AddActorDecoration, ACTOR_SELF, 1, 1, 11)
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa2_intro_bowser_BoostedDefense))
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kpa2_intro_bowser_BoostedStatusTable))
    Call(b_area_kpa2_intro_bowser_RemoveChillOut)
    Wait(3)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 40)
        Add(LVar2, 12)
        Call(PlayEffect_impl, 34, 3, LVar0, LVar1, LVar2, 70, 80, 25, 60, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 16)
        Add(LVar2, 12)
        Call(PlayEffect_impl, 34, 3, LVar0, LVar1, LVar2, 28, 32, 10, 60, 0, 0, 0, 0, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8485)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(b_area_kpa2_intro_bowser_StarRodPowerUpEffect, LVar0, LVar1, LVar2, Float(0.7998046875))
    EndThread
    Wait(75)
    Thread
        Call(b_area_kpa2_intro_bowser_FadeBackgroundLighten)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x810008)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar1, 40)
    Else
        Add(LVar1, 16)
    EndIf
    Call(PlayEffect_impl, 82, 4, LVar0, LVar1, LVar2, Float(1.0), 15, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8484)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 15)
    Add(LVar1, 65)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 400)
    Call(SetBattleCamOffsetY, 0)
    Call(MoveBattleCamOver, 32)
    Wait(32)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser1_Script_80222E48_23 = {
    Call(b_area_kpa2_hallway_bowser_FadeBackgroundDarken)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar0, 15)
        Add(LVar1, 90)
        Thread
            Call(PlaySoundAtActor, ACTOR_SELF, 8483)
            Add(LVar2, 10)
            Call(b_area_kpa2_hallway_bowser_StarRodAppearEffect, LVar0, LVar1, LVar2, Float(2.5), Float(0.0498046875))
        EndThread
    Else
        Add(LVar0, 6)
        Add(LVar1, 36)
        Thread
            Call(PlaySoundAtActor, ACTOR_SELF, 8483)
            Add(LVar2, 10)
            Call(b_area_kpa2_hallway_bowser_StarRodAppearEffect, LVar0, LVar1, LVar2, Float(2.5), Float(0.01953125))
        EndThread
    EndIf
    Wait(65)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar0, 15)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 90, LVar2, Float(1.0), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 60, 2, LVar0, 90, LVar2, Float(1.0), LVarE, 0, 0, 0, 0, 0, 0, 0)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 90, LVar2, Float(1.0), LVarD, 0, 0, 0, 0, 0, 0, 0)
    Else
        Add(LVar0, 6)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 36, LVar2, Float(0.400390625), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 60, 2, LVar0, 36, LVar2, Float(0.400390625), LVarE, 0, 0, 0, 0, 0, 0, 0)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 36, LVar2, Float(0.400390625), LVarD, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8481)
    Wait(30)
    Call(RemoveEffect, LVarF)
    Call(RemoveEffect, LVarE)
    Call(RemoveEffect, LVarD)
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x40000, 1)
    Call(AddActorDecoration, ACTOR_SELF, 1, 1, 11)
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa2_hallway_bowser_BoostedDefense))
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kpa2_hallway_bowser_BoostedStatusTable))
    Call(b_area_kpa2_hallway_bowser_RemoveChillOut)
    Wait(3)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 40)
        Add(LVar2, 12)
        Call(PlayEffect_impl, 34, 3, LVar0, LVar1, LVar2, 70, 80, 25, 60, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 16)
        Add(LVar2, 12)
        Call(PlayEffect_impl, 34, 3, LVar0, LVar1, LVar2, 28, 32, 10, 60, 0, 0, 0, 0, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8485)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(b_area_kpa2_hallway_bowser_StarRodPowerUpEffect, LVar0, LVar1, LVar2, Float(0.7998046875))
    EndThread
    Wait(75)
    Thread
        Call(b_area_kpa2_hallway_bowser_FadeBackgroundLighten)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x810008)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar1, 40)
    Else
        Add(LVar1, 16)
    EndIf
    Call(PlayEffect_impl, 82, 4, LVar0, LVar1, LVar2, Float(1.0), 15, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8484)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 39)
    Wait(30)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser2_Script_80228678_23 = {
    Call(b_area_kpa2_final_bowser_1_FadeBackgroundDarken)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar0, 22)
        Add(LVar1, 135)
        Thread
            Call(PlaySoundAtActor, ACTOR_SELF, 8483)
            Add(LVar2, 10)
            Call(b_area_kpa2_final_bowser_1_StarRodAppearEffect, LVar0, LVar1, LVar2, Float(2.5), Float(0.0751953125))
        EndThread
    Else
        Add(LVar0, 9)
        Add(LVar1, 54)
        Thread
            Call(PlaySoundAtActor, ACTOR_SELF, 8483)
            Add(LVar2, 10)
            Call(b_area_kpa2_final_bowser_1_StarRodAppearEffect, LVar0, LVar1, LVar2, Float(2.5), Float(0.0302734375))
        EndThread
    EndIf
    Wait(65)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar0, 22)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 135, LVar2, Float(1.5), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 60, 2, LVar0, 135, LVar2, Float(1.0), LVarE, 0, 0, 0, 0, 0, 0, 0)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 135, LVar2, Float(1.5), LVarD, 0, 0, 0, 0, 0, 0, 0)
    Else
        Add(LVar0, 9)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 54, LVar2, Float(0.599609375), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 60, 2, LVar0, 54, LVar2, Float(0.400390625), LVarE, 0, 0, 0, 0, 0, 0, 0)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 54, LVar2, Float(0.599609375), LVarD, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8481)
    Wait(30)
    Call(RemoveEffect, LVarF)
    Call(RemoveEffect, LVarE)
    Call(RemoveEffect, LVarD)
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x80000, 1)
    Call(AddActorDecoration, ACTOR_SELF, 1, 1, 11)
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa2_final_bowser_1_BoostedDefense))
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kpa2_final_bowser_1_BoostedStatusTable))
    Call(b_area_kpa2_final_bowser_1_RemoveChillOut)
    Wait(3)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 60)
        Add(LVar2, 12)
        Call(PlayEffect_impl, 34, 3, LVar0, LVar1, LVar2, 105, 120, 37, 60, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 24)
        Add(LVar2, 12)
        Call(PlayEffect_impl, 34, 3, LVar0, LVar1, LVar2, 42, 48, 15, 60, 0, 0, 0, 0, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8485)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(b_area_kpa2_final_bowser_1_StarRodPowerUpEffect, LVar0, LVar1, LVar2, Float(1.2001953125))
    EndThread
    Wait(75)
    Thread
        Call(b_area_kpa2_final_bowser_1_FadeBackgroundLighten)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x810008)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar1, 60)
    Else
        Add(LVar1, 24)
    EndIf
    Call(PlayEffect_impl, 82, 4, LVar0, LVar1, LVar2, Float(1.5), 15, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8484)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 39)
    Wait(30)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser3_Script_8022F4A4_23 = {
    Call(b_area_kpa2_final_bowser_2_FadeBackgroundDarken)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar0, 22)
        Add(LVar1, 135)
        Thread
            Call(PlaySoundAtActor, ACTOR_SELF, 8483)
            Add(LVar2, 10)
            Call(b_area_kpa2_final_bowser_2_StarRodAppearEffect, LVar0, LVar1, LVar2, Float(2.5), Float(0.0751953125))
        EndThread
    Else
        Add(LVar0, 9)
        Add(LVar1, 54)
        Thread
            Call(PlaySoundAtActor, ACTOR_SELF, 8483)
            Add(LVar2, 10)
            Call(b_area_kpa2_final_bowser_2_StarRodAppearEffect, LVar0, LVar1, LVar2, Float(2.5), Float(0.0302734375))
        EndThread
    EndIf
    Wait(65)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar0, 22)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 135, LVar2, Float(1.5), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 60, 2, LVar0, 135, LVar2, Float(1.0), LVarE, 0, 0, 0, 0, 0, 0, 0)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 135, LVar2, Float(1.5), LVarD, 0, 0, 0, 0, 0, 0, 0)
    Else
        Add(LVar0, 9)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 53, 2, LVar0, 54, LVar2, Float(0.599609375), LVarF, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 60, 2, LVar0, 54, LVar2, Float(0.400390625), LVarE, 0, 0, 0, 0, 0, 0, 0)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 60, 2, LVar0, 54, LVar2, Float(0.599609375), LVarD, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8481)
    Wait(30)
    Call(RemoveEffect, LVarF)
    Call(RemoveEffect, LVarE)
    Call(RemoveEffect, LVarD)
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x80000, 1)
    Call(AddActorDecoration, ACTOR_SELF, 1, 1, 11)
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa2_final_bowser_2_BoostedDefense))
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kpa2_final_bowser_2_BoostedStatusTable))
    Call(b_area_kpa2_final_bowser_2_RemoveChillOut)
    Wait(3)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 60)
        Add(LVar2, 12)
        Call(PlayEffect_impl, 34, 3, LVar0, LVar1, LVar2, 105, 120, 37, 60, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 24)
        Add(LVar2, 12)
        Call(PlayEffect_impl, 34, 3, LVar0, LVar1, LVar2, 42, 48, 15, 60, 0, 0, 0, 0, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8485)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(b_area_kpa2_final_bowser_2_StarRodPowerUpEffect, LVar0, LVar1, LVar2, Float(1.2001953125))
    EndThread
    Wait(75)
    Thread
        Call(b_area_kpa2_final_bowser_2_FadeBackgroundLighten)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x810008)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar1, 60)
    Else
        Add(LVar1, 24)
    EndIf
    Call(PlayEffect_impl, 82, 4, LVar0, LVar1, LVar2, Float(1.5), 15, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8484)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 39)
    Wait(30)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_UnusedBowser_Script_8021DEB0_23 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamDist, 150)
    Call(SetBattleCamOffsetY, 0)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 40)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 80, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810011)
    Wait(3)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810012)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 28, 0, 1, 0)
            Thread
                Call(ShakeCam, 1, 0, 4, Float(3.0))
            EndThread
            Sub(LVar0, 35)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 14, 0, 1, 0)
            Thread
                Call(ShakeCam, 1, 0, 4, Float(2.0))
            EndThread
            Call(SetAnimation, ACTOR_SELF, 1, 0x810014)
            Wait(3)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
            Wait(25)
            Call(UseBattleCamPreset, 2)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
            Set(LVar1, 0x810003)
            ExecWait(b_area_kpa2_unused_bowser_EVS_ReturnHome)
            Return
        EndCaseGroup
        CaseDefault
    EndSwitch
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(JumpToGoal, ACTOR_SELF, 24, 0, 1, 0)
    Thread
        Call(ShakeCam, 1, 0, 4, Float(3.0))
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x810013)
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    Mul(LVar0, 6)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 128, 0, 0, LVar0, 32)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 18, 0, 1, 0)
            Thread
                Call(ShakeCam, 1, 0, 4, Float(3.0))
            EndThread
            Call(SetAnimation, ACTOR_SELF, 1, 0x810014)
            Wait(3)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
            Wait(20)
            IfEq(LVarF, 10)
                Return
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
            Set(LVar1, 0x810003)
            ExecWait(b_area_kpa2_unused_bowser_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser1_Script_80226F08_23 = {
    Call(GetLastEvent, ACTOR_SELF, LVar3)
    IfEq(LVar3, 36)
        Call(RemoveActorDecoration, ACTOR_SELF, 1, 1)
        Call(SetPartEventBits, ACTOR_SELF, 1, 0x40000, 0)
    EndIf
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    Call(GetDamageSource, LVar3)
    Switch(LVar3)
        CaseEq(9)
            Call(GetOriginalActorType, ACTOR_SELF, LVar7)
            Switch(LVar7)
                CaseOrEq(18)
                CaseOrEq(48)
                EndCaseGroup
                CaseDefault
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.009765625))
                    Add(LVar5, 55)
                    Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(JumpToGoal, ACTOR_SELF, 8, 0, 0, 0)
            EndSwitch
            Set(LVar7, 0)
            Loop(30)
                Add(LVar7, 48)
                Call(SetActorYaw, ACTOR_SELF, LVar7)
                Wait(1)
            EndLoop
            Call(GetOriginalActorType, ACTOR_SELF, LVar7)
            Switch(LVar7)
                CaseOrEq(18)
                CaseOrEq(48)
                    Wait(30)
                EndCaseGroup
                CaseDefault
                    Sub(LVar5, 55)
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
                    IfEq(LVar5, 0)
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
                    Else
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 15, 0, 0, 0)
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 5, 0, 0, 0)
                    EndIf
            EndSwitch
        CaseDefault
            Wait(20)
    EndSwitch
    IfNe(LVar2, -1)
        Call(SetAnimation, ACTOR_SELF, LVar0, LVar2)
    EndIf
    Wait(10)
    Call(GetLastEvent, ACTOR_SELF, LVar1)
    Switch(LVar1)
        CaseEq(14)
            Call(GetPartEventFlags, ACTOR_SELF, LVar0, LVar1)
            IfNotFlag(LVar1, 514)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(GetActorSize, ACTOR_SELF, LVar3, LVar4)
                Call(GetStatusFlags, ACTOR_SELF, LVar5)
                IfFlag(LVar5, 0x80000)
                    MulF(LVar3, Float(0.400390625))
                    MulF(LVar4, Float(0.400390625))
                EndIf
                DivF(LVar3, Float(2.0))
                Call(GetActorFlags, ACTOR_SELF, LVar5)
                IfFlag(LVar5, 2048)
                    SubF(LVar1, LVar3)
                Else
                    AddF(LVar1, LVar3)
                EndIf
                AddF(LVar2, Float(5.0))
                DivF(LVar3, Float(10.0))
                Call(GetStatusFlags, ACTOR_SELF, LVar5)
                IfFlag(LVar5, 0x80000)
                    MulF(LVar3, Float(0.400390625))
                    IfLt(LVar3, 1)
                        SetF(LVar3, Float(1.0))
                    EndIf
                EndIf
                Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
            EndIf
        CaseEq(36)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser3_Script_80233408_23 = {
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    Call(GetDamageSource, LVar3)
    Switch(LVar3)
        CaseEq(9)
            Call(GetOriginalActorType, ACTOR_SELF, LVar7)
            Switch(LVar7)
                CaseOrEq(18)
                CaseOrEq(48)
                EndCaseGroup
                CaseDefault
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.009765625))
                    Add(LVar5, 55)
                    Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(JumpToGoal, ACTOR_SELF, 8, 0, 0, 0)
            EndSwitch
            Set(LVar7, 0)
            Loop(30)
                Add(LVar7, 48)
                Call(SetActorYaw, ACTOR_SELF, LVar7)
                Wait(1)
            EndLoop
            Call(GetOriginalActorType, ACTOR_SELF, LVar7)
            Switch(LVar7)
                CaseOrEq(18)
                CaseOrEq(48)
                    Wait(30)
                EndCaseGroup
                CaseDefault
                    Sub(LVar5, 55)
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
                    IfEq(LVar5, 0)
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
                    Else
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 15, 0, 0, 0)
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 5, 0, 0, 0)
                    EndIf
            EndSwitch
        CaseDefault
            Wait(20)
    EndSwitch
    IfNe(LVar2, -1)
        Call(SetAnimation, ACTOR_SELF, LVar0, LVar2)
    EndIf
    Wait(10)
    Call(GetLastEvent, ACTOR_SELF, LVar1)
    Switch(LVar1)
        CaseEq(14)
            Call(GetPartEventFlags, ACTOR_SELF, LVar0, LVar1)
            IfNotFlag(LVar1, 514)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(GetActorSize, ACTOR_SELF, LVar3, LVar4)
                Call(GetStatusFlags, ACTOR_SELF, LVar5)
                IfFlag(LVar5, 0x80000)
                    MulF(LVar3, Float(0.400390625))
                    MulF(LVar4, Float(0.400390625))
                EndIf
                DivF(LVar3, Float(2.0))
                Call(GetActorFlags, ACTOR_SELF, LVar5)
                IfFlag(LVar5, 2048)
                    SubF(LVar1, LVar3)
                Else
                    AddF(LVar1, LVar3)
                EndIf
                AddF(LVar2, Float(5.0))
                DivF(LVar3, Float(10.0))
                Call(GetStatusFlags, ACTOR_SELF, LVar5)
                IfFlag(LVar5, 0x80000)
                    MulF(LVar3, Float(0.400390625))
                    IfLt(LVar3, 1)
                        SetF(LVar3, Float(1.0))
                    EndIf
                EndIf
                Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
            EndIf
        CaseEq(36)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser2_Script_8022C79C_23 = {
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    Call(GetDamageSource, LVar3)
    Switch(LVar3)
        CaseEq(9)
            Call(GetOriginalActorType, ACTOR_SELF, LVar7)
            Switch(LVar7)
                CaseOrEq(18)
                CaseOrEq(48)
                EndCaseGroup
                CaseDefault
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.009765625))
                    Add(LVar5, 55)
                    Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(JumpToGoal, ACTOR_SELF, 8, 0, 0, 0)
            EndSwitch
            Set(LVar7, 0)
            Loop(30)
                Add(LVar7, 48)
                Call(SetActorYaw, ACTOR_SELF, LVar7)
                Wait(1)
            EndLoop
            Call(GetOriginalActorType, ACTOR_SELF, LVar7)
            Switch(LVar7)
                CaseOrEq(18)
                CaseOrEq(48)
                    Wait(30)
                EndCaseGroup
                CaseDefault
                    Sub(LVar5, 55)
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
                    IfEq(LVar5, 0)
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
                    Else
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 15, 0, 0, 0)
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
                        Call(SetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                        Call(JumpToGoal, ACTOR_SELF, 5, 0, 0, 0)
                    EndIf
            EndSwitch
        CaseDefault
            Wait(20)
    EndSwitch
    IfNe(LVar2, -1)
        Call(SetAnimation, ACTOR_SELF, LVar0, LVar2)
    EndIf
    Wait(10)
    Call(GetLastEvent, ACTOR_SELF, LVar1)
    Switch(LVar1)
        CaseEq(14)
            Call(GetPartEventFlags, ACTOR_SELF, LVar0, LVar1)
            IfNotFlag(LVar1, 514)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(GetActorSize, ACTOR_SELF, LVar3, LVar4)
                Call(GetStatusFlags, ACTOR_SELF, LVar5)
                IfFlag(LVar5, 0x80000)
                    MulF(LVar3, Float(0.400390625))
                    MulF(LVar4, Float(0.400390625))
                EndIf
                DivF(LVar3, Float(2.0))
                Call(GetActorFlags, ACTOR_SELF, LVar5)
                IfFlag(LVar5, 2048)
                    SubF(LVar1, LVar3)
                Else
                    AddF(LVar1, LVar3)
                EndIf
                AddF(LVar2, Float(5.0))
                DivF(LVar3, Float(10.0))
                Call(GetStatusFlags, ACTOR_SELF, LVar5)
                IfFlag(LVar5, 0x80000)
                    MulF(LVar3, Float(0.400390625))
                    IfLt(LVar3, 1)
                        SetF(LVar3, Float(1.0))
                    EndIf
                EndIf
                Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
            EndIf
        CaseEq(36)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_UnusedBowser_Script_8021E504_23 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamDist, 150)
    Call(SetBattleCamOffsetY, 0)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 40)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810016)
    Wait(35)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810017)
    Wait(10)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 70)
    Add(LVar1, 35)
    Add(LVar2, 10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 40)
    Set(LVar4, 20)
    Call(PlayEffect_impl, 55, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, 50, 1, 24, 0, 0, 0)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 100)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810018)
    Wait(30)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            Mul(LVar0, 8)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x8000002, 0xFFFF, 0, LVar0, 32)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x810019)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
            Wait(30)
            Call(GetOwnerTarget, LVar0, 0)
            IfEq(LVar0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x81000C)
            EndIf
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(30)
            Return
        EndCaseGroup
        CaseDefault
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            Mul(LVar0, 8)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x8000002, 0xFFFF, 0, LVar0, 32)
            Switch(LVarF)
                CaseOrEq(0)
                CaseOrEq(2)
                CaseOrEq(10)
                    IfEq(LVarF, 10)
                        Return
                    EndIf
                EndCaseGroup
            EndSwitch
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x810019)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
    Wait(30)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser2_Script_80229650_23 = {
    Call(AddActorVar, ACTOR_SELF, 0, 1)
    Call(AddActorVar, ACTOR_SELF, 4, 1)
    Call(AddActorVar, ACTOR_SELF, 5, 1)
    Call(AddActorVar, ACTOR_SELF, 2, 1)
    Call(AddActorVar, ACTOR_SELF, 3, 1)
    Call(AddActorVar, ACTOR_SELF, 6, 1)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 2)
        Call(GetStatusFlags, ACTOR_SELF, LVar0)
        IfNotFlag(LVar0, 0x80000)
            Call(UseBattleCamPreset, 19)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 15)
            Add(LVar1, 90)
            Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
            Call(SetBattleCamDist, 420)
            Call(SetBattleCamOffsetY, 0)
            Call(MoveBattleCamOver, 30)
        Else
            Call(UseBattleCamPreset, 19)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 6)
            Add(LVar1, 36)
            Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
            Call(SetBattleCamDist, 420)
            Call(SetBattleCamOffsetY, 0)
            Call(MoveBattleCamOver, 30)
        EndIf
        Call(ActorSpeak, 0x130084, ACTOR_SELF, 1, 0x810007, 0x810007)
        ExecWait(TTYD64_imp_23_Bowser2_Script_802284D4_23)
        Return
    EndIf
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
    Mul(LVar0, 100)
    Div(LVar0, LVar1)
    Call(b_area_kpa2_final_bowser_1_GetPlayerHpPercent, LVar2)
    Sub(LVar2, LVar0)
    IfGt(LVar2, 25)
        Call(GetActorVar, ACTOR_SELF, 7, LVar0)
        IfNe(LVar0, 0)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 75)
                Call(GetActorVar, ACTOR_SELF, 6, LVar0)
                IfGt(LVar0, 1)
                    Call(SetActorVar, ACTOR_SELF, 6, 0)
                    ExecWait(TTYD64_imp_23_Bowser2_Script_HealSelf2_23)
                    Return
                Else
                    Call(RandInt, 100, LVar0)
                    IfLt(LVar0, 0)
                        Call(SetActorVar, ACTOR_SELF, 6, 0)
                        ExecWait(TTYD64_imp_23_Bowser2_Script_HealSelf2_23)
                        Return
                    EndIf
                EndIf
            EndIf
        EndIf
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfGt(LVar0, 1)
        Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
        IfNotFlag(LVar0, 0x80000)
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            Switch(LVar0)
                CaseEq(1)
                    Set(LVar0, 0)
                CaseEq(2)
                    Set(LVar0, 0)
                CaseEq(3)
                    Set(LVar0, 15)
                CaseDefault
                    Set(LVar0, 75)
            EndSwitch
            Call(RandInt, 100, LVar1)
            IfLt(LVar1, LVar0)
                ExecWait(TTYD64_imp_23_Bowser2_Script_802284D4_23)
                Return
            EndIf
        EndIf
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfLt(LVar0, 3)
        ExecWait(TTYD64_imp_23_Bowser2_Script_80229DC0_23)
        Return
    EndIf
    ExecWait(TTYD64_imp_23_Bowser2_Script_80229BD0_23)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser1_Script_80223E20_23 = {
    Call(AddActorVar, ACTOR_SELF, 0, 1)
    Call(AddActorVar, ACTOR_SELF, 4, 1)
    Call(AddActorVar, ACTOR_SELF, 5, 1)
    Call(AddActorVar, ACTOR_SELF, 2, 1)
    Call(AddActorVar, ACTOR_SELF, 3, 1)
    Call(AddActorVar, ACTOR_SELF, 6, 1)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 2)
        Call(GetStatusFlags, ACTOR_SELF, LVar0)
        IfNotFlag(LVar0, 0x80000)
            Call(UseBattleCamPreset, 19)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 15)
            Add(LVar1, 60)
            Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
            Call(SetBattleCamDist, 420)
            Call(SetBattleCamOffsetY, 0)
            Call(MoveBattleCamOver, 30)
        Else
            Call(UseBattleCamPreset, 19)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 6)
            Add(LVar1, 24)
            Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
            Call(SetBattleCamDist, 420)
            Call(SetBattleCamOffsetY, 0)
            Call(MoveBattleCamOver, 30)
        EndIf
        ExecWait(TTYD64_imp_23_Bowser1_Script_UseStarRod1_23)
        Return
    EndIf
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
    Mul(LVar0, 100)
    Div(LVar0, LVar1)
    Call(b_area_kpa2_hallway_bowser_GetPlayerHpPercent, LVar2)
    Sub(LVar2, LVar0)
    IfGt(LVar2, 30)
        Call(GetActorVar, ACTOR_SELF, 7, LVar0)
        IfNe(LVar0, 0)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 80)
                Call(GetActorVar, ACTOR_SELF, 6, LVar0)
                IfGt(LVar0, 1)
                    Call(SetActorVar, ACTOR_SELF, 6, 0)
                    ExecWait(TTYD64_imp_23_Bowser1_Script_HealSelf1_23)
                    Return
                Else
                    Call(RandInt, 100, LVar0)
                    IfLt(LVar0, 0)
                        Call(SetActorVar, ACTOR_SELF, 6, 0)
                        ExecWait(TTYD64_imp_23_Bowser1_Script_HealSelf1_23)
                        Return
                    EndIf
                EndIf
            EndIf
        EndIf
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfGt(LVar0, 1)
        Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
        IfNotFlag(LVar0, 0x40000)
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            Switch(LVar0)
                CaseEq(1)
                    Set(LVar0, 0)
                CaseEq(2)
                    Set(LVar0, 20)
                CaseEq(3)
                    Set(LVar0, 30)
                CaseDefault
                    Set(LVar0, 100)
            EndSwitch
            Call(RandInt, 100, LVar1)
            IfLt(LVar1, LVar0)
                ExecWait(TTYD64_imp_23_Bowser1_Script_UseStarRod1_23)
                Return
            EndIf
        EndIf
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfLt(LVar0, 3)
        ExecWait(TTYD64_imp_23_Bowser1_Script_80224570_23)
        Return
    EndIf
    ExecWait(TTYD64_imp_23_Bowser1_Script_80224380_23)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser1_Script_HealSelf1_23 = {
    Call(GetActorVar, ACTOR_SELF, 7, LVar0)
    Sub(LVar0, 1)
    Call(SetActorVar, ACTOR_SELF, 7, LVar0)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 15)
        Add(LVar1, 65)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 420)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 40)
    Else
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 6)
        Add(LVar1, 26)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 294)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 40)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000F)
    Call(b_area_kpa2_hallway_bowser_FadeBackgroundDarken)
    Call(PlaySoundAtActor, ACTOR_SELF, 8486)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 15)
        Add(LVar1, 90)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 107, 2, LVar0, LVar1, LVar2, Float(1.0), 50, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 15)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 51, 5, LVar0, 90, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 6)
        Add(LVar1, 36)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 107, 2, LVar0, LVar1, LVar2, Float(0.400390625), 50, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 6)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 51, 5, LVar0, 36, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Wait(30)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar0)
    Mul(LVar0, 40)
    Div(LVar0, 100)
    Thread
        Wait(5)
        Call(PlaySoundAtActor, ACTOR_SELF, 8301)
        Call(PlaySoundAtActor, ACTOR_SELF, 532)
        Wait(30)
        Call(PlaySoundAtActor, ACTOR_SELF, 604)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(HealActor, ACTOR_SELF, LVar0, 0)
        Call(FreezeBattleState, 0)
    EndThread
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser2_Script_HealSelf2_23 = {
    Call(GetActorVar, ACTOR_SELF, 7, LVar0)
    Sub(LVar0, 1)
    Call(SetActorVar, ACTOR_SELF, 7, LVar0)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 15)
        Add(LVar1, 97)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 420)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 40)
    Else
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 6)
        Add(LVar1, 39)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 294)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 40)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000F)
    Call(b_area_kpa2_final_bowser_1_FadeBackgroundDarken)
    Call(PlaySoundAtActor, ACTOR_SELF, 8486)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 22)
        Add(LVar1, 135)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 107, 2, LVar0, LVar1, LVar2, Float(1.5), 50, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 22)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 51, 5, LVar0, 135, LVar2, Float(0.4501953125), 30, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 9)
        Add(LVar1, 54)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 107, 2, LVar0, LVar1, LVar2, Float(0.599609375), 50, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 9)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 51, 5, LVar0, 54, LVar2, Float(0.1796875), 30, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Wait(30)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar0)
    Mul(LVar0, 31)
    Div(LVar0, 100)
    Thread
        Wait(5)
        Call(PlaySoundAtActor, ACTOR_SELF, 8301)
        Call(PlaySoundAtActor, ACTOR_SELF, 532)
        Wait(30)
        Call(PlaySoundAtActor, ACTOR_SELF, 604)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(HealActor, ACTOR_SELF, LVar0, 0)
        Call(FreezeBattleState, 0)
    EndThread
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser3_Script_HealSelf3_23 = {
    Call(GetActorVar, ACTOR_SELF, 7, LVar0)
    Sub(LVar0, 1)
    Call(SetActorVar, ACTOR_SELF, 7, LVar0)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 15)
        Add(LVar1, 97)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 420)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 40)
    Else
        Call(UseBattleCamPreset, 19)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 6)
        Add(LVar1, 39)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 294)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 40)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000F)
    Call(b_area_kpa2_final_bowser_2_FadeBackgroundDarken)
    Call(PlaySoundAtActor, ACTOR_SELF, 8486)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 22)
        Add(LVar1, 135)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 107, 2, LVar0, LVar1, LVar2, Float(1.5), 50, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 22)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 51, 5, LVar0, 135, LVar2, Float(0.4501953125), 30, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 9)
        Add(LVar1, 54)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 107, 2, LVar0, LVar1, LVar2, Float(0.599609375), 50, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 9)
        Sub(LVar2, 3)
        Call(PlayEffect_impl, 51, 5, LVar0, 54, LVar2, Float(0.1796875), 30, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Wait(30)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar0)
    Mul(LVar0, 31)
    Div(LVar0, 100)
    Thread
        Wait(5)
        Call(PlaySoundAtActor, ACTOR_SELF, 8301)
        Call(PlaySoundAtActor, ACTOR_SELF, 532)
        Wait(30)
        Call(PlaySoundAtActor, ACTOR_SELF, 604)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(HealActor, ACTOR_SELF, LVar0, 0)
        Call(FreezeBattleState, 0)
    EndThread
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser1_Script_ClawSwipe1_23 = {
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(UseBattleCamPreset, 63)
        Call(SetBattleCamDist, 200)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 40)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    Else
        Call(UseBattleCamPreset, 63)
        Call(SetBattleCamDist, 160)
        Call(SetBattleCamOffsetY, 5)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 40)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x810003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(AddGoalPos, ACTOR_SELF, 40, 0, 0)
    Else
        Call(AddGoalPos, ACTOR_SELF, 16, 0, 0)
    EndIf
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810009)
    Wait(25)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810015)
    Call(PlaySoundAtActor, ACTOR_SELF, 862)
    Wait(3)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_AttackMissed)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                Wait(30)
            Else
                Wait(30)
            EndIf
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Set(LVar1, 0x810003)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_ReturnHome)
            Return
        EndCaseGroup
        CaseDefault
    EndSwitch
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
    IfFlag(LVar0, 0x40000)
        Set(LVar0, 12)
        Call(SetDamageSource, 12)
        Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0, -0x7FFDFC9C, LVar0, 32)
    Else
        Set(LVar0, 6)
        Call(SetDamageSource, 12)
        Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0, -0x7FFDFC9C, LVar0, 32)
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Wait(30)
            IfEq(LVarF, 10)
                Return
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Set(LVar1, 0x810003)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser3_Script_ClawSwipe3_23 = {
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(UseBattleCamPreset, 63)
        Call(SetBattleCamDist, 200)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 40)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    Else
        Call(UseBattleCamPreset, 63)
        Call(SetBattleCamDist, 160)
        Call(SetBattleCamOffsetY, 5)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 40)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x810003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(AddGoalPos, ACTOR_SELF, 60, 0, 0)
    Else
        Call(AddGoalPos, ACTOR_SELF, 24, 0, 0)
    EndIf
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810009)
    Wait(25)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810015)
    Call(PlaySoundAtActor, ACTOR_SELF, 862)
    Wait(3)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            ExecWait(b_area_kpa2_final_bowser_2_EVS_AttackMissed)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                Wait(30)
            Else
                Wait(30)
            EndIf
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Set(LVar1, 0x810003)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_ReturnHome)
            Return
        EndCaseGroup
        CaseDefault
    EndSwitch
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
    IfFlag(LVar0, 0x80000)
        Set(LVar0, 16)
        Call(SetDamageSource, 12)
        Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0, -0x7FFDFC9C, LVar0, 32)
    Else
        Set(LVar0, 8)
        Call(SetDamageSource, 12)
        Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0, -0x7FFDFC9C, LVar0, 32)
    EndIf
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Wait(30)
            IfEq(LVarF, 10)
                Return
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Set(LVar1, 0x810003)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser2_Script_ClawSwipe2_23 = {
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(UseBattleCamPreset, 63)
        Call(SetBattleCamDist, 200)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 40)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    Else
        Call(UseBattleCamPreset, 63)
        Call(SetBattleCamDist, 160)
        Call(SetBattleCamOffsetY, 5)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 40)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x810003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(AddGoalPos, ACTOR_SELF, 60, 0, 0)
    Else
        Call(AddGoalPos, ACTOR_SELF, 24, 0, 0)
    EndIf
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810009)
    Wait(25)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810015)
    Call(PlaySoundAtActor, ACTOR_SELF, 862)
    Wait(3)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_AttackMissed)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                Wait(30)
            Else
                Wait(30)
            EndIf
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Set(LVar1, 0x810003)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_ReturnHome)
            Return
        EndCaseGroup
        CaseDefault
    EndSwitch
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
    IfFlag(LVar0, 0x80000)
        Set(LVar0, 16)
        Call(SetDamageSource, 12)
        Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0, -0x7FFDFC9C, LVar0, 32)
    Else
        Set(LVar0, 8)
        Call(SetDamageSource, 12)
        Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0, -0x7FFDFC9C, LVar0, 32)
    EndIf
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Wait(30)
            IfEq(LVarF, 10)
                Return
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Set(LVar1, 0x810003)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_IntroBowser_Script_IntroFireBreath_23 = {
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 30)
    Add(LVar1, 65)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 400)
    Call(SetBattleCamOffsetY, 0)
    Call(MoveBattleCamOver, 40)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810016)
    Wait(35)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810017)
    Wait(10)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 50)
    Add(LVar1, 33)
    Add(LVar2, 10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 40)
    Set(LVar4, 20)
    Call(PlayEffect_impl, 55, 2, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, 50, 1, 24, 0, 0, 0)
    Call(b_area_kpa2_intro_bowser_SetBowserFireBreathScales, LVarF)
    Thread
        Call(b_area_kpa2_intro_bowser_StartRumbleWithParams, 50, 148)
        Call(PlaySound, 957)
        Wait(70)
        Call(PlaySound, 1981)
    EndThread
    Call(SetNpcAnimation, 0, 0xD60007)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 55)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810018)
    Wait(30)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0xA000002, 0xFFFF, 0, 10, 32)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Thread
                Call(SetAnimation, ACTOR_SELF, 1, 0x810019)
                Wait(15)
                Call(SetAnimation, ACTOR_SELF, 1, 0x810002)
            EndThread
            Wait(60)
            Call(SetNpcAnimation, 0, 0xD60006)
            Loop(68)
                Call(GetAnimation, 0, 0, LVar0)
                IfEq(LVar0, 0x10018)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            Call(SetNpcAnimation, 0, 0xD6000A)
            Wait(30)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser3_Script_UseMove3_23 = {
    Call(AddActorVar, ACTOR_SELF, 0, 1)
    Call(AddActorVar, ACTOR_SELF, 4, 1)
    Call(AddActorVar, ACTOR_SELF, 5, 1)
    Call(AddActorVar, ACTOR_SELF, 2, 1)
    Call(AddActorVar, ACTOR_SELF, 3, 1)
    Call(AddActorVar, ACTOR_SELF, 6, 1)
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
    Mul(LVar0, 100)
    Div(LVar0, LVar1)
    Call(b_area_kpa2_hallway_bowser_GetPlayerHpPercent, LVar2)
    Sub(LVar2, LVar0)
    IfGt(LVar2, 25)
        Call(GetActorVar, ACTOR_SELF, 7, LVar0)
        IfNe(LVar0, 0)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 75)
                Call(GetActorVar, ACTOR_SELF, 6, LVar0)
                IfGt(LVar0, 1)
                    Call(SetActorVar, ACTOR_SELF, 6, 0)
                    ExecWait(TTYD64_imp_23_Bowser3_Script_HealSelf3_23)
                    Return
                Else
                    Call(RandInt, 100, LVar0)
                    IfLt(LVar0, 0)
                        Call(SetActorVar, ACTOR_SELF, 6, 0)
                        ExecWait(TTYD64_imp_23_Bowser3_Script_HealSelf3_23)
                        Return
                    EndIf
                EndIf
            EndIf
        EndIf
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfGt(LVar0, 1)
        Call(GetPartEventFlags, ACTOR_SELF, 1, LVar0)
        IfNotFlag(LVar0, 0x80000)
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            Switch(LVar0)
                CaseEq(1)
                    Set(LVar0, 0)
                CaseEq(2)
                    Set(LVar0, 0)
                CaseEq(3)
                    Set(LVar0, 15)
                CaseDefault
                    Set(LVar0, 75)
            EndSwitch
            Call(RandInt, 100, LVar1)
            IfLt(LVar1, LVar0)
                ExecWait(TTYD64_imp_23_Bowser3_Script_8022F300_23)
                Return
            EndIf
        EndIf
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfLt(LVar0, 3)
        ExecWait(TTYD64_imp_23_Bowser3_Script_80230A2C_23)
        Return
    EndIf
    ExecWait(TTYD64_imp_23_Bowser3_Script_8023083C_23)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_UnusedBowser_Script_8021DAFC_23 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamDist, 150)
    Call(SetBattleCamOffsetY, 0)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 40)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 40, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810009)
    Wait(25)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810015)
    Wait(3)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x81000C)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                Wait(50)
            Else
                Wait(30)
            EndIf
            Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
            Set(LVar1, 0x810003)
            ExecWait(b_area_kpa2_unused_bowser_EVS_ReturnHome)
            Return
        EndCaseGroup
        CaseDefault
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    Mul(LVar0, 6)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000000, 0, 0, LVar0, 32)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Wait(30)
            Call(SetAnimation, ACTOR_SELF, 1, 0x810007)
            Wait(45)
            IfEq(LVarF, 10)
                Return
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
            Set(LVar1, 0x810003)
            ExecWait(b_area_kpa2_unused_bowser_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_IntroBowser_Script_IntroClawSwipe_23 = {
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamDist, 200)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 40)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 40, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810009)
    Wait(25)
    Call(SetAnimation, ACTOR_SELF, 1, 0x810015)
    Call(PlaySoundAtActor, ACTOR_SELF, 862)
    Wait(3)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 0, LVar1)
    IfLt(LVar1, 3)
        Set(LVar0, 1)
        Call(SetDamageSource, 12)
        Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x12000000, 0, 0, LVar0, 32)
    Else
        Set(LVar0, 3)
        Call(SetDamageSource, 12)
        Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x12000000, 0, 0, LVar0, 32)
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Thread
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        IfGe(LVar0, 3)
            Call(SetNpcAnimation, 0, 0xD60007)
        Else
            Call(SetNpcAnimation, 0, 0xD60006)
        EndIf
        Wait(45)
        Call(SetNpcAnimation, 0, 0xD60004)
    EndThread
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Wait(30)
            IfEq(LVarF, 10)
                Return
            EndIf
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Set(LVar1, 0x810003)
            ExecWait(b_area_kpa2_intro_bowser_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_IntroBowser_Script_HandleEvent_8021F800_23 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetLastElement, LVarE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(56)
        CaseOrEq(9)
        CaseOrEq(10)
            Set(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_intro_bowser_EVS_OnHit)
        EndCaseGroup
        CaseEq(14)
            Set(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_intro_bowser_EVS_OnHit)
        CaseOrEq(36)
            Call(SetEnemyHP, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseEq(11)
            Set(LVar1, 0x81000D)
            ExecWait(b_area_kpa2_intro_bowser_EVS_OnHit)
        CaseEq(33)
            Call(SetEnemyHP, ACTOR_SELF, 1)
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(Ref(EVS_Enemy_ShockHit))
        CaseEq(38)
            Call(SetEnemyHP, ACTOR_SELF, 1)
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            Set(LVar1, 0x810002)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 3)
                Call(ActorSpeak, 91, ACTOR_SELF, 1, 0x810005, 0x810002)
            EndIf
        EndCaseGroup
        CaseEq(27)
        CaseEq(32)
            Call(SetEnemyHP, ACTOR_SELF, 1)
            Return
        CaseEq(53)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x810012)
            ExecWait(Ref(EVS_Enemy_Recover))
            Call(SetAnimation, ACTOR_SELF, 1, 0x810014)
            Call(ShakeCam, 1, 0, 4, Float(3.0))
        CaseEq(48)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x81000D)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(1000)
        CaseDefault
            SetConst(LVar1, 0x81000D)
            Call(SetAnimation, ACTOR_SELF, 1, LVar1)
            Wait(20)
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_IntroBowser_Script_IntroUseStarRod_23 = {
    Call(UseBattleCamPreset, 13)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Wait(30)
    Call(ActorSpeak, 88, ACTOR_SELF, 1, 0x810005, 0x810002)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 15)
    Add(LVar1, 65)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 320)
    Call(SetBattleCamOffsetY, 0)
    Call(MoveBattleCamOver, 20)
    Wait(20)
    Thread
        Wait(2)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 20)
        Add(LVar1, 90)
        Call(PlayEffect_impl, 34, 3, LVar0, LVar1, LVar2, 30, 30, 7, 30, 0, 0, 0, 0, 0)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000F)
    Wait(30)
    Call(ActorSpeak, 89, ACTOR_SELF, 1, 0x81001F, 0x81001E)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000F)
    ExecWait(TTYD64_imp_23_IntroBowser_Script_80220990_23)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 15)
    Add(LVar1, 65)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 320)
    Call(SetBattleCamOffsetY, 0)
    Call(MoveBattleCamOver, 25)
    Call(ActorSpeak, 90, ACTOR_SELF, 1, 0x810009, 0x810001)
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa2_intro_bowser_BoostedDefense))
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kpa2_intro_bowser_BoostedStatusTable))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser3_Script_Init_8022D6A0_23 = {
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 3)
    Call(SetActorVar, ACTOR_SELF, 5, 3)
    Call(SetActorVar, ACTOR_SELF, 9, 0)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 0)
    Call(SetActorVar, ACTOR_SELF, 7, 3)
    Call(SetActorVar, ACTOR_SELF, 14, 0)
    Call(TTYD64_ReadField, TTYD64_F_GCURRENTSAVEFILE_123A_1U, LVar0)
    Call(SetEnemyHP, ACTOR_SELF, LVar0)
    IfLt(LVar0, 1)
        Call(SetEnemyHP, ACTOR_SELF, 1)
    EndIf
    Call(SetActorScale, ACTOR_SELF, Float(1.5), Float(1.5), Float(1.0))
    Call(ModifyActorDecoration, ACTOR_SELF, 1, 1, 150, 0, 0, 0)
    Exec(b_area_kpa2_final_bowser_2_EVS_AnimateImgFX)
    Call(ModifyActorDecoration, ACTOR_SELF, 1, 0, 150, 150, 0, 0)
    Call(AddActorDecoration, ACTOR_SELF, 1, 0, 10)
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x80000, 1)
    Call(AddActorDecoration, ACTOR_SELF, 1, 1, 11)
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa2_final_bowser_2_BoostedDefense))
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kpa2_final_bowser_2_BoostedStatusTable))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_23_Bowser3_Script_TakeTurn_8022F2BC_23))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa2_final_bowser_2_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_23_Bowser3_Script_HandleEvent_8022DF74_23))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kpa2_final_bowser_2_EVS_HandlePhase))
    Call(SetBattleFlagBits2, 0x2000000, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser2_Script_80229BD0_23 = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfLe(LVar0, 3)
        ExecWait(TTYD64_imp_23_Bowser2_Script_80229DC0_23)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfGe(LVar0, 6)
        Call(RandInt, 30, LVar0)
        IfLt(LVar0, 20)
            ExecWait(TTYD64_imp_23_Bowser2_Script_Shockwave2_23)
        Else
            ExecWait(TTYD64_imp_23_Bowser2_Script_Thunderbolt2_23)
        EndIf
        Return
    EndIf
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 75)
        Call(b_area_kpa2_final_bowser_1_GetJumpHammerCharge, LVar0, LVar1)
        IfGt(LVar0, 0)
            ExecWait(TTYD64_imp_23_Bowser2_Script_Shockwave2_23)
            Return
        EndIf
        IfGt(LVar1, 0)
            ExecWait(TTYD64_imp_23_Bowser2_Script_Shockwave2_23)
            Return
        EndIf
    EndIf
    Call(RandInt, 110, LVar0)
    IfLt(LVar0, 30)
        IfLt(LVar0, 20)
            ExecWait(TTYD64_imp_23_Bowser2_Script_Shockwave2_23)
        Else
            ExecWait(TTYD64_imp_23_Bowser2_Script_Thunderbolt2_23)
        EndIf
        Return
    EndIf
    ExecWait(TTYD64_imp_23_Bowser2_Script_80229DC0_23)
    Return
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser1_Script_80224380_23 = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfLe(LVar0, 3)
        ExecWait(TTYD64_imp_23_Bowser1_Script_80224570_23)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfGe(LVar0, 6)
        Call(RandInt, 20, LVar0)
        IfLt(LVar0, 20)
            ExecWait(TTYD64_imp_23_Bowser1_Script_Shockwave1_23)
        Else
            ExecWait(TTYD64_imp_23_Bowser1_Script_Shockwave1_23)
        EndIf
        Return
    EndIf
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 75)
        Call(b_area_kpa2_hallway_bowser_GetJumpHammerCharge, LVar0, LVar1)
        IfGt(LVar0, 0)
            ExecWait(TTYD64_imp_23_Bowser1_Script_Shockwave1_23)
            Return
        EndIf
        IfGt(LVar1, 0)
            ExecWait(TTYD64_imp_23_Bowser1_Script_Shockwave1_23)
            Return
        EndIf
    EndIf
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 20)
        IfLt(LVar0, 20)
            ExecWait(TTYD64_imp_23_Bowser1_Script_Shockwave1_23)
        Else
            ExecWait(TTYD64_imp_23_Bowser1_Script_Shockwave1_23)
        EndIf
        Return
    EndIf
    ExecWait(TTYD64_imp_23_Bowser1_Script_80224570_23)
    Return
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser3_Script_8023083C_23 = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfLe(LVar0, 3)
        ExecWait(TTYD64_imp_23_Bowser3_Script_80230A2C_23)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfGe(LVar0, 6)
        Call(RandInt, 30, LVar0)
        IfLt(LVar0, 20)
            ExecWait(TTYD64_imp_23_Bowser3_Script_Shockwave3_23)
        Else
            ExecWait(TTYD64_imp_23_Bowser3_Script_Thunderbolt3_23)
        EndIf
        Return
    EndIf
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 75)
        Call(b_area_kpa2_final_bowser_2_GetJumpHammerCharge, LVar0, LVar1)
        IfGt(LVar0, 0)
            ExecWait(TTYD64_imp_23_Bowser3_Script_Shockwave3_23)
            Return
        EndIf
        IfGt(LVar1, 0)
            ExecWait(TTYD64_imp_23_Bowser3_Script_Shockwave3_23)
            Return
        EndIf
    EndIf
    Call(RandInt, 110, LVar0)
    IfLt(LVar0, 30)
        IfLt(LVar0, 20)
            ExecWait(TTYD64_imp_23_Bowser3_Script_Shockwave3_23)
        Else
            ExecWait(TTYD64_imp_23_Bowser3_Script_Thunderbolt3_23)
        EndIf
        Return
    EndIf
    ExecWait(TTYD64_imp_23_Bowser3_Script_80230A2C_23)
    Return
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser2_Script_Init_80227770_23 = {
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 3)
    Call(SetActorVar, ACTOR_SELF, 5, 3)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 0)
    Call(SetActorVar, ACTOR_SELF, 7, 3)
    Call(SetActorVar, ACTOR_SELF, 14, 0)
    Call(SetActorVar, ACTOR_SELF, 9, 0)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.5), Float(1.5), Float(1.0))
    Call(ModifyActorDecoration, ACTOR_SELF, 1, 1, 150, 0, 0, 0)
    Exec(b_area_kpa2_final_bowser_1_EVS_AnimateImgFX)
    Call(ModifyActorDecoration, ACTOR_SELF, 1, 0, 150, 150, 0, 0)
    Call(AddActorDecoration, ACTOR_SELF, 1, 0, 10)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_23_Bowser2_Script_TakeTurn_80228490_23))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa2_final_bowser_1_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_23_Bowser2_Script_HandleEvent_80227AD0_23))
    Call(SetBattleFlagBits2, 0x2000400, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_UnusedBowser_Script_TakeTurn_8021D880_23 = {
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Add(LVar0, 1)
    IfLt(LVar0, 5)
        Call(SetActorVar, ACTOR_SELF, 1, LVar0)
        Call(SetActorVar, ACTOR_SELF, 2, 5)
        ExecWait(TTYD64_imp_23_UnusedBowser_Script_8021DA28_23)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    Add(LVar0, 1)
    Call(SetActorVar, ACTOR_SELF, 2, LVar0)
    IfLt(LVar0, 4)
        ExecWait(TTYD64_imp_23_UnusedBowser_Script_8021DA28_23)
        Return
    EndIf
    IfGt(LVar0, 6)
        Call(SetActorVar, ACTOR_SELF, 2, 0)
        ExecWait(TTYD64_imp_23_UnusedBowser_Script_8021E93C_23)
        Return
    EndIf
    Call(GetActorHP, ACTOR_SELF, LVar0)
    IfLt(LVar0, 8)
        Call(SetActorVar, ACTOR_SELF, 2, 0)
        ExecWait(TTYD64_imp_23_UnusedBowser_Script_8021E93C_23)
        Return
    EndIf
    ExecWait(TTYD64_imp_23_UnusedBowser_Script_8021DA28_23)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser1_Script_Init_802216C0_23 = {
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 3)
    Call(SetActorVar, ACTOR_SELF, 5, 3)
    Call(SetActorVar, ACTOR_SELF, 9, 0)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 0)
    Call(SetActorVar, ACTOR_SELF, 7, 1)
    Call(SetActorVar, ACTOR_SELF, 14, 0)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_23_Bowser1_Script_TakeTurn_80222B48_23))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa2_hallway_bowser_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_23_Bowser1_Script_HandleEvent_80221B18_23))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kpa2_hallway_bowser_EVS_HandlePhase))
    Call(ModifyActorDecoration, ACTOR_SELF, 1, 1, 100, 0, 0, 0)
    Exec(b_area_kpa2_hallway_bowser_EVS_AnimateImgFX)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_IntroBowser_Script_Init_8021F3D0_23 = {
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 14, 0)
    Call(SetBattleMenuEnabledFlags, 1)
    Call(CreateNpc, 0, 0xD60004)
    Call(SetNpcYaw, 0, 90)
    Call(SetNpcPos, 0, -130, 0, -12)
    Call(EnableNpcShadow, 0, 1)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_23_IntroBowser_Script_TakeTurn_8021FC14_23))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa2_intro_bowser_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_23_IntroBowser_Script_HandleEvent_8021F800_23))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kpa2_intro_bowser_EVS_HandlePhase))
    Call(ModifyActorDecoration, ACTOR_SELF, 1, 1, 100, 0, 0, 0)
    Exec(b_area_kpa2_intro_bowser_EVS_AnimateImgFX)
    Call(SetBattleFlagBits, 0x800000, 1)
    Call(SetBattleFlagBits2, 0x2000000, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_IntroBowser_Script_TakeTurn_8021FC14_23 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Add(LVar0, 1)
    Call(SetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseLt(3)
            ExecWait(TTYD64_imp_23_IntroBowser_Script_IntroClawSwipe_23)
        CaseEq(3)
            ExecWait(TTYD64_imp_23_IntroBowser_Script_IntroUseStarRod_23)
            ExecWait(TTYD64_imp_23_IntroBowser_Script_IntroClawSwipe_23)
        CaseEq(4)
            ExecWait(TTYD64_imp_23_IntroBowser_Script_IntroClawSwipe_23)
        CaseEq(5)
            Call(UseBattleCamPreset, 13)
            Call(BattleCamTargetActor, ACTOR_SELF)
            Call(MoveBattleCamOver, 30)
            Wait(30)
            Call(ActorSpeak, 92, ACTOR_SELF, 1, 0x810005, 0x810002)
            ExecWait(TTYD64_imp_23_IntroBowser_Script_IntroFireBreath_23)
            Call(SetActorVar, ACTOR_SELF, 0, 4)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser1_Script_UseStarRod1_23 = {
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    IfNotFlag(LVar0, 64)
        BitwiseOrConst(LVar0, 64)
        Call(SetActorVar, ACTOR_SELF, 1, LVar0)
        Call(UseBattleCamPreset, 13)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 20)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x81000F)
        Wait(5)
        Call(ActorSpeak, 0x130074, ACTOR_SELF, 1, 0x81001F, 0x81001E)
        Call(SetAnimation, ACTOR_SELF, 1, 0x810010)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x81000F)
    EndIf
    Wait(2)
    ExecWait(TTYD64_imp_23_Bowser1_Script_80222E48_23)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser1_Script_80224570_23 = {
    Call(RandInt, 80, LVar0)
    IfLt(LVar0, 20)
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        IfGe(LVar0, 2)
            ExecWait(b_area_kpa2_hallway_bowser_EVS_Attack_BodySlam)
            Return
        EndIf
    EndIf
    Call(RandInt, 60, LVar0)
    IfLt(LVar0, 20)
        Call(GetActorVar, ACTOR_SELF, 4, LVar0)
        IfGe(LVar0, 2)
            ExecWait(TTYD64_imp_23_Bowser1_Script_ClawSwipe1_23)
            Return
        EndIf
    EndIf
    ExecWait(TTYD64_imp_23_Bowser1_Script_FireBreath1_23)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser2_Script_80229DC0_23 = {
    Call(RandInt, 80, LVar0)
    IfLt(LVar0, 20)
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        IfGe(LVar0, 2)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_Attack_BodySlam)
            Return
        EndIf
    EndIf
    Call(RandInt, 60, LVar0)
    IfLt(LVar0, 20)
        Call(GetActorVar, ACTOR_SELF, 4, LVar0)
        IfGe(LVar0, 2)
            ExecWait(TTYD64_imp_23_Bowser2_Script_ClawSwipe2_23)
            Return
        EndIf
    EndIf
    ExecWait(TTYD64_imp_23_Bowser2_Script_FireBreath2_23)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser3_Script_80230A2C_23 = {
    Call(RandInt, 80, LVar0)
    IfLt(LVar0, 20)
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        IfGe(LVar0, 2)
            ExecWait(b_area_kpa2_final_bowser_1_EVS_Attack_BodySlam)
            Return
        EndIf
    EndIf
    Call(RandInt, 60, LVar0)
    IfLt(LVar0, 20)
        Call(GetActorVar, ACTOR_SELF, 4, LVar0)
        IfGe(LVar0, 2)
            ExecWait(TTYD64_imp_23_Bowser3_Script_ClawSwipe3_23)
            Return
        EndIf
    EndIf
    ExecWait(TTYD64_imp_23_Bowser3_Script_FireBreath3_23)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_UnusedBowser_Script_8021DA28_23 = {
    Call(GetStatusFlags, 0, LVar0)
    IfFlag(LVar0, 8192)
        ExecWait(TTYD64_imp_23_UnusedBowser_Script_8021E504_23)
        Return
    EndIf
    Call(RandInt, 2, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_imp_23_UnusedBowser_Script_8021DAFC_23)
            Return
        CaseEq(1)
            ExecWait(TTYD64_imp_23_UnusedBowser_Script_8021DEB0_23)
            Return
        CaseDefault
            ExecWait(TTYD64_imp_23_UnusedBowser_Script_8021E504_23)
            Return
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_UnusedBowser_Script_Init_8021D438_23 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_23_UnusedBowser_Script_TakeTurn_8021D880_23))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa2_unused_bowser_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kpa2_unused_bowser_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 1)
    Return
    End
};
// clang-format on

Battle TTYD64_kpa2_FormationTable[] = {
    { .name = "\257\303\321",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_kpa2_Formation_00,
      .stage = &b_area_kpa2_kpa_01,
      .onBattleStart = NULL },
    { .name = "\257\303\321(\252\374\327\313\363\260)",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_kpa2_Formation_01,
      .stage = &b_area_kpa2_kkj_01,
      .onBattleStart = NULL },
    { .name = "\257\303\321(\351\271\310\320\310\353\021)",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_kpa2_Formation_02,
      .stage = &b_area_kpa2_kkj_01,
      .onBattleStart = NULL },
    { .name = "\257\303\321(\351\271\310\320\310\353\022)",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_kpa2_Formation_03,
      .stage = &b_area_kpa2_kkj_02,
      .onBattleStart = NULL },
    { .name = "\257\303\321(\351\271\310\320\310\353\023)",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_kpa2_Formation_04,
      .stage = &b_area_kpa2_kkj_02,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_imp_23_Bowser1_Script_TakeTurn_80222B48_23 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    ExecWait(TTYD64_imp_23_Bowser1_Script_80223E20_23)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_23_IntroBowser_IdleAnimations_8021F1C0_23[] = {
    1,        0x810002, 7,        0x810000, 6,        0x810002, 9,        0x810002, 8,        0x810000, 11,
    0x810000, 5,        0x810000, 5,        0x810000, 4,        0x810002, 4,        0x810002, 0,
};

s32 TTYD64_imp_23_Bowser2_IdleAnimations_80227560_23[] = {
    1,        0x810002, 7,        0x810000, 6,        0x810002, 9,        0x810002, 8,        0x810000, 11,
    0x810000, 5,        0x810000, 5,        0x810000, 4,        0x810002, 4,        0x810002, 0,
};

s32 TTYD64_imp_23_Bowser1_IdleAnimations_802214B0_23[] = {
    1,        0x810002, 7,        0x810000, 6,        0x810002, 9,        0x810002, 8,        0x810000, 11,
    0x810000, 5,        0x810000, 5,        0x810000, 4,        0x810002, 4,        0x810002, 0,
};

s32 TTYD64_imp_23_UnusedBowser_IdleAnimations_8021D2E0_23[] = {
    1,        0x810002, 7,        0x810000, 6,        0x810002, 9,        0x810002, 8,        0x810000, 11,
    0x810000, 5,        0x810000, 5,        0x810000, 4,        0x810002, 4,        0x810002, 0,
};

s32 TTYD64_imp_23_Bowser3_IdleAnimations_8022D490_23[] = {
    1,        0x810002, 7,        0x810000, 6,        0x810002, 9,        0x810002, 8,        0x810000, 11,
    0x810000, 5,        0x810000, 5,        0x810000, 4,        0x810002, 4,        0x810002, 0,
};

// clang-format off
EvtScript TTYD64_imp_23_Bowser3_Script_TakeTurn_8022F2BC_23 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    ExecWait(TTYD64_imp_23_Bowser3_Script_UseMove3_23)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser2_Script_TakeTurn_80228490_23 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    ExecWait(TTYD64_imp_23_Bowser2_Script_80229650_23)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser2_Script_802284D4_23 = {
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000F)
    ExecWait(TTYD64_imp_23_Bowser2_Script_80228678_23)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_23_Bowser3_Script_8022F300_23 = {
    Call(SetAnimation, ACTOR_SELF, 1, 0x81000F)
    ExecWait(TTYD64_imp_23_Bowser3_Script_8022F4A4_23)
    Return
    End
};
// clang-format on

ActorBlueprint TTYD64_imp_23_UnusedBowser_23_UnusedBowser = {
    .flags = 0x0,
    .maxHP = 50,
    .type = 0xC1,
    .level = 100,
    .partCount = 1,
    .partsData = TTYD64_imp_23_UnusedBowser_PartsTable_8021D3EC_23,
    .initScript = &TTYD64_imp_23_UnusedBowser_Script_Init_8021D438_23,
    .statusTable = b_area_kpa2_unused_bowser_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 65,
    .coinReward = 0,
    .size = { 80, 82 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -40, 67 },
    .statusTextOffset = { 10, 60 },
};

ActorBlueprint TTYD64_imp_23_Bowser2_23_Bowser2 = {
    .flags = 0x0,
    .maxHP = 99,
    .type = 0xC3,
    .level = 0,
    .partCount = 1,
    .partsData = TTYD64_imp_23_Bowser2_PartsTable_80227724_23,
    .initScript = &TTYD64_imp_23_Bowser2_Script_Init_80227770_23,
    .statusTable = b_area_kpa2_final_bowser_1_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 50,
    .coinReward = 0,
    .size = { 123, 119 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -53, 103 },
    .statusTextOffset = { 33, 92 },
};

ActorBlueprint TTYD64_imp_23_Bowser3_23_Bowser3 = {
    .flags = 0x0,
    .maxHP = 99,
    .type = 0xC5,
    .level = 0,
    .partCount = 1,
    .partsData = TTYD64_imp_23_Bowser3_PartsTable_8022D654_23,
    .initScript = &TTYD64_imp_23_Bowser3_Script_Init_8022D6A0_23,
    .statusTable = b_area_kpa2_final_bowser_2_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 60,
    .coinReward = 0,
    .size = { 123, 119 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -53, 103 },
    .statusTextOffset = { 33, 92 },
};

ActorBlueprint TTYD64_imp_23_Bowser1_23_Bowser1 = {
    .flags = 0x0,
    .maxHP = 50,
    .type = 0xC1,
    .level = 100,
    .partCount = 1,
    .partsData = TTYD64_imp_23_Bowser1_PartsTable_80221674_23,
    .initScript = &TTYD64_imp_23_Bowser1_Script_Init_802216C0_23,
    .statusTable = b_area_kpa2_hallway_bowser_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 65,
    .coinReward = 0,
    .size = { 80, 82 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -40, 67 },
    .statusTextOffset = { 10, 60 },
};

ActorBlueprint TTYD64_imp_23_IntroBowser_23_IntroBowser = {
    .flags = 0x0,
    .maxHP = 10,
    .type = 0xC0,
    .level = 0,
    .partCount = 1,
    .partsData = TTYD64_imp_23_IntroBowser_PartsTable_8021F384_23,
    .initScript = &TTYD64_imp_23_IntroBowser_Script_Init_8021F3D0_23,
    .statusTable = b_area_kpa2_intro_bowser_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 80, 82 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorPartBlueprint TTYD64_imp_23_IntroBowser_PartsTable_8021F384_23[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -18, 72 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_23_IntroBowser_IdleAnimations_8021F1C0_23,
        .defenseTable = b_area_kpa2_intro_bowser_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_23_Bowser2_PartsTable_80227724_23[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -27, 108 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_23_Bowser2_IdleAnimations_80227560_23,
        .defenseTable = b_area_kpa2_final_bowser_1_NormalDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_23_Bowser1_PartsTable_80221674_23[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -18, 72 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_23_Bowser1_IdleAnimations_802214B0_23,
        .defenseTable = b_area_kpa2_hallway_bowser_NormalDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_23_Bowser3_PartsTable_8022D654_23[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -27, 108 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_23_Bowser3_IdleAnimations_8022D490_23,
        .defenseTable = b_area_kpa2_final_bowser_2_NormalDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_23_UnusedBowser_PartsTable_8021D3EC_23[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -18, 72 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_23_UnusedBowser_IdleAnimations_8021D2E0_23,
        .defenseTable = b_area_kpa2_unused_bowser_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x2,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_kpa2_Formation_00[] = {
    { .actor = &TTYD64_imp_23_UnusedBowser_23_UnusedBowser,
      .home = { .index = 2 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kpa2_Formation_01[] = {
    { .actor = &TTYD64_imp_23_IntroBowser_23_IntroBowser,
      .home = { .index = 2 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kpa2_Formation_04[] = {
    { .actor = &TTYD64_imp_23_Bowser3_23_Bowser3,
      .home = { .vec = &b_area_kpa2_bowser_pos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kpa2_Formation_02[] = {
    { .actor = &TTYD64_imp_23_Bowser1_23_Bowser1,
      .home = { .index = 2 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kpa2_Formation_03[] = {
    { .actor = &TTYD64_imp_23_Bowser2_23_Bowser2,
      .home = { .vec = &b_area_kpa2_bowser_pos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

void TTYD64_InstallBattles_kpa2(void) {
    Mod_SetBattleList("TTYD64", 0x23, TTYD64_kpa2_FormationTable);
}
