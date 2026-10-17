#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_drop_tables.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/battles_a/battles_a.h"

API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(CreateHomeTargetList);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyToGoal);
API_CALLABLE(ForceHomePos);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetEncounterTrigger);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetIndexFromHome);
API_CALLABLE(GetIndexFromPos);
API_CALLABLE(GetLastDamage);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetMashActionQuality);
API_CALLABLE(GetOriginalActorType);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartOffset);
API_CALLABLE(GetPlayerHP);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(GetTargetListLength);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HideHealthBar);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(InterruptLeechActionCommand);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(JumpWithBounce);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(MakeLerp);
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
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorType);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetDarknessMode);
API_CALLABLE(SetDefenseTable);
API_CALLABLE(SetEnemyHP);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetPartEventBits);
API_CALLABLE(SetPartEventFlags);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartFlags);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartRotation);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetPartYaw);
API_CALLABLE(SetProjectileTargetOffset);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetStatusTable);
API_CALLABLE(SetTargetOffset);
API_CALLABLE(SetupMashMeter);
API_CALLABLE(ShowActionHud);
API_CALLABLE(ShowMessageBox);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
API_CALLABLE(action_command_stop_leech_init);
API_CALLABLE(action_command_stop_leech_start);
API_CALLABLE(b_area_jan_jungle_fuzzy_SpawnDrainHealthContinueFX);
API_CALLABLE(b_area_jan_jungle_fuzzy_SpawnDrainHealthStartFX);
API_CALLABLE(b_area_jan_medi_guy_MediGuySpriteRotationFunc);
API_CALLABLE(b_area_jan_spike_top_SetAbsoluteStatusOffsets);
extern EvtScript b_area_jan_hurt_plant_EVS_HandleEvent;
extern EvtScript b_area_jan_hurt_plant_EVS_Idle;
extern EvtScript b_area_jan_hurt_plant_EVS_ReturnHome;
extern Stage b_area_jan_jan_00;
extern Stage b_area_jan_jan_01;
extern Stage b_area_jan_jan_01b;
extern Stage b_area_jan_jan_02;
extern Stage b_area_jan_jan_03;
extern Stage b_area_jan_jan_03b;
extern Stage b_area_jan_jan_04;
extern Stage b_area_jan_jan_04b;
extern EvtScript b_area_jan_jan_04b_EVS_PostBattle;
extern EvtScript b_area_jan_jungle_fuzzy_EVS_CountActiveSummoners;
extern EvtScript b_area_jan_jungle_fuzzy_EVS_GetAvailableColumn;
extern Vec3i b_area_jan_jungle_fuzzy_SummonPos;
extern s32 b_area_jan_m_bush_DefenseTable[];
extern EvtScript b_area_jan_m_bush_EVS_HandleEvent;
extern EvtScript b_area_jan_m_bush_EVS_Idle;
extern EvtScript b_area_jan_m_bush_EVS_ReturnHome;
extern EvtScript b_area_jan_medi_guy_EVS_FindInjuredActor;
extern EvtScript b_area_jan_medi_guy_EVS_HandleEvent;
extern EvtScript b_area_jan_medi_guy_EVS_Idle;
extern EvtScript b_area_jan_medi_guy_EVS_Move_HealOne;
extern EvtScript b_area_jan_medi_guy_EVS_ReturnHome;
extern s32 b_area_jan_medi_guy_StatusTable[];
extern EvtScript b_area_jan_spear_guy_EVS_CountActiveSummoners;
extern EvtScript b_area_jan_spear_guy_EVS_GetAvailableColumn;
extern EvtScript b_area_jan_spear_guy_EVS_HandleEvent;
extern EvtScript b_area_jan_spear_guy_EVS_ReturnHome;
extern EvtScript b_area_jan_spear_guy_EVS_ShyGuy_HandleEvent;
extern EvtScript b_area_jan_spear_guy_EVS_ShyGuy_Idle;
extern EvtScript b_area_jan_spear_guy_EVS_ShyGuy_ReturnHome;
extern s32 b_area_jan_spear_guy_GrassSkirtAnims[];
extern s32 b_area_jan_spear_guy_ShyGuyDefense[];
extern s32 b_area_jan_spear_guy_SpearAnims[];
extern Vec3i b_area_jan_spear_guy_SummonPos;
extern EvtScript b_area_jan_spike_top_EVS_CheckToppleAnim;
extern EvtScript b_area_jan_spike_top_EVS_Idle;
extern EvtScript b_area_jan_spike_top_FlipPosOffsets;
extern s32 b_area_jan_spike_top_StatusTable[];
extern s32 b_area_jan_spike_top_ToppledDefense[];
extern s32 b_area_jan_spike_top_UprightDefense[];
extern EvtScript TTYD64_jan_jungle_fuzzy_EVS_Attack_Leech;
extern EvtScript TTYD64_jan_spike_top_EVS_HandleEvent;
extern EvtScript TTYD64_jan_spear_guy_EVS_Attack_Vault;
extern EvtScript TTYD64_jan_spear_guy_EVS_Attack_ThrowSpear;
extern EvtScript TTYD64_jan_spike_top_EVS_Ceiling_TakeTurn;
extern EvtScript TTYD64_jan_spike_top_EVS_TakeTurn;
extern EvtScript TTYD64_jan_spear_guy_EVS_Move_SummonBackup;
extern EvtScript TTYD64_jan_medi_guy_EVS_Attack_Swoop;
extern EvtScript TTYD64_jan_spear_guy_EVS_Attack_Tackle;
extern EvtScript TTYD64_jan_jungle_fuzzy_EVS_HandleEvent;
extern EvtScript TTYD64_jan_hurt_plant_EVS_TakeTurn;
extern EvtScript TTYD64_jan_m_bush_EVS_TakeTurn;
extern EvtScript TTYD64_jan_spear_guy_EVS_Attack_SpearStab;
extern EvtScript TTYD64_jan_spike_top_EVS_Ceiling_HandleEvent;
extern EvtScript TTYD64_jan_spike_top_EVS_FallFromCeiling;
extern EvtScript TTYD64_jan_jungle_fuzzy_EVS_Move_Divide;
extern EvtScript TTYD64_jan_spear_guy_EVS_BecomeShyGuy;
extern EvtScript TTYD64_jan_spear_guy_EVS_TakeTurn;
extern EvtScript TTYD64_jan_jungle_fuzzy_EVS_TakeTurn;
extern EvtScript TTYD64_jan_spike_top_EVS_Init;
extern EvtScript TTYD64_jan_spear_guy_EVS_Init;
extern EvtScript TTYD64_jan_spear_guy_EVS_Idle;
extern EvtScript TTYD64_jan_spear_guy_EVS_SwitchSpearStance;
extern EvtScript TTYD64_jan_spear_guy_EVS_UpdateSpearStance;
extern EvtScript TTYD64_jan_medi_guy_EVS_Init;
extern EvtScript TTYD64_jan_medi_guy_EVS_TakeTurn;
extern EvtScript TTYD64_jan_jungle_fuzzy_EVS_Init;
extern EvtScript TTYD64_jan_spear_guy_EVS_ShyGuy_TakeTurn;
extern EvtScript TTYD64_jan_EVS_8022844C;
extern EvtScript TTYD64_jan_spear_guy_EVS_ShyGuy_Init;
extern EvtScript TTYD64_jan_m_bush_EVS_Init;
extern EvtScript TTYD64_jan_m_bush_EVS_Init_80228790;
extern EvtScript TTYD64_jan_spear_guy_EVS_HandlePhase;
extern ActorBlueprint TTYD64_jan_jungle_fuzzy;
extern ActorBlueprint TTYD64_jan_m_bush;
extern ActorBlueprint TTYD64_jan_spike_top;
extern ActorBlueprint TTYD64_jan_jungle_fuzzy_80228A74;
extern ActorBlueprint TTYD64_jan_spear_guy;
extern ActorBlueprint TTYD64_jan_medi_guy;
extern ActorBlueprint TTYD64_jan_spear_guy_80228B64;
extern Stage TTYD64_jan_Stage_80228BB4;
extern ActorBlueprint TTYD64_jan_hurt_plant;
extern Battle TTYD64_jan_Formations[];
extern s32 TTYD64_jan_m_bush_StatusTable[];
extern s32 TTYD64_jan_m_bush_StatusTable_8022756C[];
extern s32 TTYD64_jan_jungle_fuzzy_StatusTable[];
extern s32 TTYD64_jan_spear_guy_ShyGuyStatusTable[];
extern s32 TTYD64_jan_spear_guy_SpearGuyStatusTable[];
extern ActorPartBlueprint TTYD64_jan_spear_guy_ActorParts[];
extern FormationRow TTYD64_jan_Formation_0C[];
extern FormationRow TTYD64_jan_Formation_10[];
extern FormationRow TTYD64_jan_Formation_03[];
extern FormationRow TTYD64_jan_Formation_06[];
extern FormationRow TTYD64_jan_Formation_0D[];
extern FormationRow TTYD64_jan_Formation_0B[];
extern FormationRow TTYD64_jan_Formation_0F[];
extern FormationRow TTYD64_jan_Formation_01[];
extern FormationRow TTYD64_jan_Formation_04[];
extern FormationRow TTYD64_jan_Formation_05[];
extern FormationRow TTYD64_jan_Formation_09[];
extern FormationRow TTYD64_jan_Formation_07[];
extern StageListRow TTYD64_jan_Stages[];
extern s32 TTYD64_jan_spear_guy_ShyGuyAnims[];
extern s32 TTYD64_jan_spike_top_CeilingAnims[];
extern s32 TTYD64_jan_m_bush_DefaultAnims[];
extern s32 TTYD64_jan_hurt_plant_DefaultAnims[];
extern s32 TTYD64_jan_spear_guy_SpearForwardAnims[];
extern s32 TTYD64_jan_medi_guy_DefaultAnims[];
extern s32 TTYD64_jan_spear_guy_SpearUpwardAnims[];
extern s32 TTYD64_jan_spike_top_GroundAnims[];
extern s32 TTYD64_jan_jungle_fuzzy_DefaultAnims[];
extern s32 TTYD64_jan_spike_top_ToppledAnims[];
extern FormationRow TTYD64_jan_Formation_0A[];
extern FormationRow TTYD64_jan_Formation_0E[];
extern FormationRow TTYD64_jan_Formation_00[];
extern FormationRow TTYD64_jan_Formation_02[];
extern FormationRow TTYD64_jan_Formation_08[];
extern ActorPartBlueprint TTYD64_jan_spike_top_ActorParts[];
extern ActorPartBlueprint TTYD64_jan_jungle_fuzzy_ActorParts[];
extern ActorPartBlueprint TTYD64_jan_m_bush_ActorParts[];
extern ActorPartBlueprint TTYD64_jan_medi_guy_ActorParts[];
extern ActorPartBlueprint TTYD64_jan_hurt_plant_ActorParts[];
extern FormationRow TTYD64_jan_spear_guy_UpwardSpearFormation[];
extern FormationRow TTYD64_jan_jungle_fuzzy_SummonFormation[];
extern FormationRow TTYD64_jan_spear_guy_ForwardSpearFormation[];

// clang-format off
EvtScript TTYD64_jan_jungle_fuzzy_EVS_Attack_Leech = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
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
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0303)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0301)
    Label(100)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0304)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 9, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 8, 0)
    Wait(5)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 2, 16)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0305)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 11, 0, 1, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0309)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0303)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0305)
    Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
    IfEq(LFlag0, 1)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 0, 32)
        Return
    EndIf
    Call(GetOwnerTarget, LVar2, 0)
    Call(GetStatusFlags, LVar2, LVar1)
    IfFlag(LVar1, 0x100000)
        Wait(10)
        Loop(2)
            Call(PlaySoundAtActor, ACTOR_SELF, 992)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0307)
            Wait(21)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0300)
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
            Call(EnemyDamageTarget, ACTOR_SELF, LVarA, 0x8000000, 0, 0, 2, 32)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 8, 0)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0305)
            Wait(30)
        EndLoop
    Else
        Call(ShowMessageBox, 49, 0x7FFF)
        Call(ShowActionHud, 1)
        Call(LoadActionCommand, 6)
        Call(action_command_stop_leech_init)
        Call(SetupMashMeter, 1, 23, 0, 0, 0, 0)
        Wait(10)
        Call(SetBattleFlagBits, 0x4000, 0)
        Call(action_command_stop_leech_start, 0, 0x7FFF, 3)
        Set(LVarD, 0)
        Loop(5)
            Call(GetOwnerTarget, LVar4, 0)
            Switch(LVar4)
                CaseEq(0)
                    Call(UseIdleAnimation, 0, 0)
                    Call(SetAnimation, 0, 0, 0x3000C)
                CaseEq(256)
                    Call(UseIdleAnimation, 256, 0)
                    Set(LVar0, 4)
                    Exec(TTYD64_SetPartnerAnimation_Battle)
            EndSwitch
            Call(PlaySoundAtActor, ACTOR_SELF, 992)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0307)
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
                Call(UseIdleAnimation, LVar4, 1)
                BreakLoop
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0300)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 330)
            Call(PlaySoundAtActor, ACTOR_SELF, 992)
            Call(SetActorDispOffset, ACTOR_SELF, -3, -2, 0)
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
                Call(UseIdleAnimation, LVar4, 1)
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
                Call(UseIdleAnimation, LVar4, 1)
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
                Call(UseIdleAnimation, LVar4, 1)
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
                Call(UseIdleAnimation, LVar4, 1)
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
                Call(UseIdleAnimation, LVar4, 1)
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
                Call(UseIdleAnimation, LVar4, 1)
                BreakLoop
            EndIf
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
                Call(UseIdleAnimation, LVar4, 1)
                BreakLoop
            EndIf
            Call(UseIdleAnimation, LVar4, 1)
            Call(EnemyDamageTarget, ACTOR_SELF, LVarA, 0xA000000, 0, 0, 2, 32)
            Call(GetLastDamage, LVar4, LVar3)
            IfNe(LVar3, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8301)
                Call(PlaySoundAtActor, ACTOR_SELF, 532)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 10)
                Call(b_area_jan_jungle_fuzzy_SpawnDrainHealthStartFX, LVar0, LVar1, LVar2, LVar3)
                Thread
                    Wait(15)
                    Call(PlaySoundAtActor, ACTOR_SELF, 604)
                    Call(b_area_jan_jungle_fuzzy_SpawnDrainHealthContinueFX, LVar0, LVar1, LVar2, LVar3)
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
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 8, 0)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0305)
            Call(GetOwnerTarget, LVar4, 0)
            IfEq(LVar4, 0)
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
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
        Call(SetActorDispOffset, ACTOR_SELF, 0, 8, 0)
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
        Call(SetAnimation, ACTOR_SELF, 1, 0x2B0305)
    EndIf
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0301)
    Call(UseBattleCamPreset, 2)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0303)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0301)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_spike_top_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_jan_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfNe(LVar0, 2)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0016)
                SetConst(LVar2, 0x4D0017)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0018)
                SetConst(LVar2, 0x4D0018)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            EndIf
        CaseEq(36)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfNe(LVar0, 2)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0016)
                SetConst(LVar2, 0x4D0017)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0017)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0018)
                SetConst(LVar2, 0x4D0018)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0018)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_jan_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 8, 2)
            Call(SetTargetOffset, ACTOR_SELF, 1, 1, 20)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -3, -8)
            Call(SetActorVar, ACTOR_SELF, 9, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_jan_spike_top_ToppledDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_jan_spike_top_ToppledAnims))
            Call(SetPartEventBits, ACTOR_SELF, 1, 16, 0)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0013)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            Thread
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -45)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -90)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -135)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -180)
                Wait(1)
            EndThread
            UseBuf(Ref(b_area_jan_spike_top_FlipPosOffsets))
            Loop(19)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0015)
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0008)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D000B)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(SetAnimation, ACTOR_SELF, 1, 0x4D000E)
                Wait(8)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0005)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(25)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D000B)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(SetAnimation, ACTOR_SELF, 1, 0x4D000C)
                Wait(8)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0005)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(27)
            Wait(10)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                Add(LVar1, 9)
            Else
                Add(LVar1, 24)
            EndIf
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(20)
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_jan_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_jan_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_jan_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            SetConst(LVar2, 0x4D0015)
            ExecWait(b_area_jan_spike_top_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0003)
                ExecWait(Ref(EVS_Enemy_Recover))
            EndIf
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0008)
                SetConst(LVar2, 0x4D0013)
                ExecWait(Ref(EVS_Enemy_ScareAway))
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0005)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0008)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0005)
            EndIf
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(SetActorDispOffset, ACTOR_SELF, 7, 0, 0)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0013)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0015)
            EndIf
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D000B)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(SetAnimation, ACTOR_SELF, 1, 0x4D000C)
                Wait(8)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4D0005)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_spear_guy_EVS_Attack_Vault = {
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
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 3, 32)
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
EvtScript TTYD64_jan_spear_guy_EVS_Attack_ThrowSpear = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(SetAnimation, ACTOR_SELF, 2, 0x420006)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 200)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x420015)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Sub(LVar0, 100)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Sub(LVar0, 70)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 3, Float(0.400390625), Float(0.400390625), Float(0.400390625))
        Call(SetPartScale, ACTOR_SELF, 4, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Else
        Call(SetPartScale, ACTOR_SELF, 3, Float(1.0), Float(1.0), Float(1.0))
        Call(SetPartScale, ACTOR_SELF, 4, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 2, 0x420011)
            Wait(5)
            Thread
                Call(SetAnimation, ACTOR_SELF, 2, 0x420017)
                Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Sub(LVar0, 20)
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                Sub(LVar0, 10)
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
                Call(SetAnimation, ACTOR_SELF, 2, 0x420012)
            EndThread
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetPartPos, ACTOR_SELF, 3, LVar0, 20, LVar2)
            Call(SetPartRotation, ACTOR_SELF, 3, 0, 0, -30)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
            Thread
                Call(MakeLerp, -30, 45, 20, 0)
                Label(0)
                Call(UpdateLerp)
                Call(SetPartRotation, ACTOR_SELF, 3, 0, 0, LVar0)
                Wait(1)
                IfEq(LVar1, 1)
                    Goto(0)
                EndIf
            EndThread
            Call(PlaySoundAtPart, ACTOR_SELF, 3, 778)
            Call(SetPartSounds, ACTOR_SELF, 3, 2, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 10)
            Add(LVar2, 2)
            Call(SetPartJumpGravity, ACTOR_SELF, 3, Float(0.7001953125))
            Call(JumpPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 20, 1)
            Wait(10)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Wait(10)
            ExecWait(TTYD64_jan_spear_guy_EVS_BecomeShyGuy)
            Call(YieldTurn)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 2, 0x420011)
    Wait(5)
    Thread
        Call(SetAnimation, ACTOR_SELF, 2, 0x420017)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 20)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
        Sub(LVar0, 10)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 2, 0x420012)
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, 20, LVar2)
    Call(SetPartRotation, ACTOR_SELF, 3, 0, 0, -30)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
    Thread
        Call(MakeLerp, -30, 45, 20, 0)
        Label(0)
        Call(UpdateLerp)
        Call(SetPartRotation, ACTOR_SELF, 3, 0, 0, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
    EndThread
    Call(PlaySoundAtPart, ACTOR_SELF, 3, 778)
    Call(SetPartSounds, ACTOR_SELF, 3, 2, 0, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar2, 2)
    Call(SetPartJumpGravity, ACTOR_SELF, 3, Float(0.7001953125))
    Call(JumpPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 20, 1)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
    Wait(3)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    Wait(20)
    ExecWait(TTYD64_jan_spear_guy_EVS_BecomeShyGuy)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_spike_top_EVS_Ceiling_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 24)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
    Call(b_area_jan_spike_top_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_jan_spike_top_EVS_TakeTurn))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_jan_spike_top_EVS_HandleEvent))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_jan_spike_top_GroundAnims))
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
    Call(GetIndexFromPos, ACTOR_SELF, LVar0)
    Mod(LVar0, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVar0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar4, LVar2)
        Call(SetAnimation, ACTOR_SELF, 1, 0x4D0001)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x4D0009)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar4, LVar2)
        Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x4D0001)
        Wait(8)
    EndIf
    Call(SetActorSounds, ACTOR_SELF, 2, 769, 0)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 5)
        Call(SetBattleCamDist, 430)
        Call(SetBattleCamOffsetY, 20)
        Call(MoveBattleCamOver, 10)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 4, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(SetPartYaw, ACTOR_SELF, 1, 180)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0015)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar1, 24)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(ResetAllActorSounds, ACTOR_SELF)
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Thread
                Wait(5)
                Call(SetAnimation, ACTOR_SELF, 1, 0x4D0000)
            EndThread
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(8)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0008)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0003)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4D0015)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 24)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, LVar4)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 4, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Thread
                Wait(5)
                Call(SetAnimation, ACTOR_SELF, 1, 0x4D0000)
            EndThread
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(8)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0008)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0003)
        EndCaseGroup
    EndSwitch
    Label(10)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_spike_top_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 2)
        Call(GetActorVar, ACTOR_SELF, 9, LVar0)
        Sub(LVar0, 1)
        IfGt(LVar0, 0)
            Call(SetActorVar, ACTOR_SELF, 9, LVar0)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(UseBattleCamPreset, 2)
        Else
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(20)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0005)
            SetConst(LVar2, 0x4D0003)
            ExecWait(Ref(EVS_Enemy_FlipBackUp))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetActorVar, ACTOR_SELF, 8, 1)
            Call(SetTargetOffset, ACTOR_SELF, 1, 0, 24)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_jan_spike_top_UprightDefense))
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_jan_spike_top_GroundAnims))
            Call(BindIdle, ACTOR_SELF, Ref(b_area_jan_spike_top_EVS_Idle))
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 16, 1)
        EndIf
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Return
    EndIf
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4D000B)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4D000F)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(10)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(5)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 8225)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4D000A)
    Wait(20)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 3, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
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
            Call(AddGoalPos, ACTOR_SELF, -150, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Wait(15)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 200)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D000C)
            Wait(10)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0003)
            Wait(8)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0008)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x4D0003)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_spear_guy_EVS_Move_SummonBackup = {
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
        Call(SummonEnemy, Ref(TTYD64_jan_spear_guy_ForwardSpearFormation), 0)
    Else
        Call(SummonEnemy, Ref(TTYD64_jan_spear_guy_UpwardSpearFormation), 0)
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
EvtScript TTYD64_jan_medi_guy_EVS_Attack_Swoop = {
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
    Thread
        SetF(LVar0, Float(0.0))
        Loop(15)
            AddF(LVar0, Float(2.0))
            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x400003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 12)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(10)
            Call(PlaySoundAtActor, ACTOR_SELF, 760)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x400005)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 761)
            Thread
                Wait(5)
                Set(LVar0, 0)
                Loop(60)
                    Call(b_area_jan_medi_guy_MediGuySpriteRotationFunc, LVar0, LVar1, 15, 60, Float(30.0))
                    Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar1)
                    Add(LVar0, 1)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Add(LVar2, 1)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x400005)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(30)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
            ExecWait(b_area_jan_medi_guy_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 760)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0x400005)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Set(LVarC, LVar2)
    Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 761)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, 1)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x400005)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(UseBattleCamPreset, 2)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpWithBounce, ACTOR_SELF, 10, Float(2.0))
            Wait(20)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_jan_medi_guy_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_spear_guy_EVS_Attack_Tackle = {
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
    ExecWait(b_area_jan_spear_guy_EVS_ShyGuy_ReturnHome)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_jungle_fuzzy_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Call(GetLastElement, LVar0)
            IfFlag(LVar0, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0313)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0308)
            EndIf
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0310)
            SetConst(LVar2, 0x2B0312)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0310)
            SetConst(LVar2, 0x2B0312)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0312)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0308)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0308)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0308)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0313)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0313)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0303)
            ExecWait(Ref(EVS_Enemy_HopHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0313)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0313)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0301)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            Call(GetLastElement, LVar0)
            IfFlag(LVar0, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0313)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0313)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0308)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0308)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0301)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0303)
            SetConst(LVar2, 0x2B0309)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0303)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0303)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0301)
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
EvtScript TTYD64_jan_hurt_plant_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x440004)
        Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(MoveBattleCamOver, 1)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 27)
        Set(LVar1, 0)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Wait(15)
        Goto(123)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 802)
    Call(SetAnimation, ACTOR_SELF, 1, 0x440004)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
    Wait(8)
    Call(UseBattleCamPreset, 19)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 27)
    Set(LVar1, 0)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 350)
    Call(SetBattleCamOffsetY, 45)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(MoveBattleCamOver, 20)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 27)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
    Label(123)
    Call(PlaySoundAtActor, ACTOR_SELF, 801)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x440003)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x440005)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 708)
    Call(SetAnimation, ACTOR_SELF, 1, 0x440006)
    Wait(6)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x440007)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            ExecWait(b_area_jan_hurt_plant_EVS_ReturnHome)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(GetOwnerTarget, LVar1, 0)
    Call(GetStatusFlags, LVar1, LVar0)
    IfFlag(LVar0, 0x20000)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Else
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, -0x7FFDFC9C, 2, 32)
    EndIf
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x440007)
            Wait(5)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_jan_hurt_plant_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_m_bush_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x450004)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetActorSounds, ACTOR_SELF, 2, 8393, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x450006)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Sub(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0x450002)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_jan_m_bush_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x450006)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, -0x7FFDFDE7, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x450002)
            Wait(8)
            Call(YieldTurn)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_jan_m_bush_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_spear_guy_EVS_Attack_SpearStab = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x420006)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 10)
    Else
        Add(LVar0, 25)
    EndIf
    Set(LVar1, 0)
    Add(LVar2, 1)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x420004)
    Wait(5)
    Call(SetAnimation, ACTOR_SELF, 2, 0x42001A)
    Wait(15)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySoundAtActor, ACTOR_SELF, 777)
            Call(SetAnimation, ACTOR_SELF, 2, 0x42001B)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Sub(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(15)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            ExecWait(b_area_jan_spear_guy_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 777)
    Call(SetAnimation, ACTOR_SELF, 2, 0x42001B)
    Wait(5)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(20)
            ExecWait(b_area_jan_spear_guy_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_spike_top_EVS_Ceiling_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_jan_spike_top_EVS_FallFromCeiling)
        CaseEq(13)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_jan_spike_top_EVS_FallFromCeiling)
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0019)
            SetConst(LVar2, 0x4D001A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_jan_spike_top_EVS_FallFromCeiling)
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0019)
            SetConst(LVar2, 0x4D001A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D001A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0008)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0013)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D000D)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D000D)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Wait(2)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x200000)
                ExecWait(TTYD64_jan_spike_top_EVS_FallFromCeiling)
            EndIf
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 1)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4D0009)
            SetConst(LVar2, 0x4D0014)
            ExecWait(Ref(EVS_Enemy_ScareAway))
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
EvtScript TTYD64_jan_spike_top_EVS_FallFromCeiling = {
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 2)
    Call(SetTargetOffset, ACTOR_SELF, 1, 1, 20)
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -3, -8)
    Call(b_area_jan_spike_top_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_jan_spike_top_EVS_TakeTurn))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_jan_spike_top_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 9, 1)
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_jan_spike_top_ToppledDefense))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_jan_spike_top_ToppledAnims))
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(SetPartEventBits, ACTOR_SELF, 1, 16, 0)
    Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
    Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4D0015)
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 24)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetActorSounds, ACTOR_SELF, 2, 769, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(GetIndexFromPos, ACTOR_SELF, LVarA)
    Mod(LVarA, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVarA)
    Call(GetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(SetHomePos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Set(LVarD, LVarA)
    Set(LVarE, LVarB)
    Set(LVarF, LVarC)
    Sub(LVarD, LVar0)
    Sub(LVarE, LVar1)
    Sub(LVarF, LVar2)
    Div(LVarD, 2)
    Div(LVarE, 2)
    Div(LVarF, 2)
    Add(LVar0, LVarD)
    Add(LVar1, LVarE)
    Add(LVar2, LVarF)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4D0005)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_jungle_fuzzy_EVS_Move_Divide = {
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
    Call(SummonEnemy, Ref(TTYD64_jan_jungle_fuzzy_SummonFormation), 0)
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
EvtScript TTYD64_jan_spear_guy_EVS_BecomeShyGuy = {
    Call(SetActorVar, ACTOR_SELF, 0, 2)
    Wait(10)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 2, 0x420013)
    Wait(5)
    Call(SetAnimation, ACTOR_SELF, 2, 0x420018)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 10)
    Add(LVar1, 15)
    Sub(LVar2, 1)
    Call(SetPartPos, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 0)
    Call(SetPartJumpGravity, ACTOR_SELF, 4, Float(0.5))
    Add(LVar0, 50)
    Sub(LVar2, 30)
    Thread
        Loop(15)
            Call(SetPartRotation, ACTOR_SELF, 4, 0, 0, 10)
            Wait(1)
            Call(SetPartRotation, ACTOR_SELF, 4, 0, 0, -10)
            Wait(1)
        EndLoop
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 8301)
    Thread
        Loop(10)
            Call(GetPartOffset, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 17, 3, LVar0, LVar1, LVar2, 5, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(3)
        EndLoop
    EndThread
    Call(PlaySoundAtPart, ACTOR_SELF, 4, 764)
    Call(SetPartSounds, ACTOR_SELF, 4, 2, 0, 0)
    Call(JumpPartTo, ACTOR_SELF, 4, LVar0, 0, LVar2, 30, 1)
    Wait(5)
    Call(SetPartFlags, ACTOR_SELF, 2, 0x22005)
    Call(SetPartFlags, ACTOR_SELF, 1, 0x800004)
    Call(SetPartFlags, ACTOR_SELF, 3, 0x22005)
    Call(SetPartFlags, ACTOR_SELF, 4, 0x22005)
    ExecWait(TTYD64_jan_spear_guy_EVS_ShyGuy_Init)
    Call(SetActorType, ACTOR_SELF, 31)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_jan_spear_guy_ShyGuyStatusTable))
    Call(HPBarToHome, ACTOR_SELF)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_spear_guy_EVS_TakeTurn = {
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
                        ExecWait(TTYD64_jan_spear_guy_EVS_Move_SummonBackup)
                        Return
                    EndIf
                CaseEq(2)
                    Call(RandInt, 1000, LVar0)
                    IfLt(LVar0, 150)
                        ExecWait(TTYD64_jan_spear_guy_EVS_Move_SummonBackup)
                        Return
                    EndIf
                CaseEq(3)
                    Call(RandInt, 1000, LVar0)
                    IfLt(LVar0, 100)
                        ExecWait(TTYD64_jan_spear_guy_EVS_Move_SummonBackup)
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
EvtScript TTYD64_jan_jungle_fuzzy_EVS_TakeTurn = {
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
                ExecWait(TTYD64_jan_jungle_fuzzy_EVS_Move_Divide)
                Return
            EndIf
        CaseEq(2)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 150)
                ExecWait(TTYD64_jan_jungle_fuzzy_EVS_Move_Divide)
                Return
            EndIf
        CaseEq(3)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 70)
                ExecWait(TTYD64_jan_jungle_fuzzy_EVS_Move_Divide)
                Return
            EndIf
    EndSwitch
    ExecWait(TTYD64_jan_jungle_fuzzy_EVS_Attack_Leech)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_spike_top_EVS_Init = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_jan_spike_top_EVS_Idle))
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 8, 0)
        Call(b_area_jan_spike_top_SetAbsoluteStatusOffsets, -10, 0, 10, 0)
        Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_jan_spike_top_EVS_Ceiling_TakeTurn))
        Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_jan_spike_top_EVS_Ceiling_HandleEvent))
        Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 0)
    Else
        Call(SetActorVar, ACTOR_SELF, 8, 1)
        Call(SetTargetOffset, ACTOR_SELF, 1, 0, 24)
        Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
        Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_jan_spike_top_EVS_TakeTurn))
        Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_jan_spike_top_EVS_HandleEvent))
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_jan_spike_top_GroundAnims))
        Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
        Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
    EndIf
    Call(HPBarToHome, ACTOR_SELF)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_spear_guy_EVS_Init = {
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
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_jan_spear_guy_EVS_TakeTurn))
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

// clang-format off
EvtScript TTYD64_jan_spear_guy_EVS_Idle = {
    Label(0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 0x49000)
                Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_jan_spear_guy_SpearUpwardAnims))
                Call(SetPartEventBits, ACTOR_SELF, 2, 16, 1)
                Call(SetPartEventBits, ACTOR_SELF, 2, 0x10000, 0)
            Else
                Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_jan_spear_guy_SpearForwardAnims))
                Call(SetPartEventBits, ACTOR_SELF, 2, 16, 0)
                Call(SetPartEventBits, ACTOR_SELF, 2, 0x10000, 1)
            EndIf
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_jan_spear_guy_SpearUpwardAnims))
            Call(SetPartEventBits, ACTOR_SELF, 2, 16, 1)
            Call(SetPartEventBits, ACTOR_SELF, 2, 0x10000, 0)
    EndSwitch
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_spear_guy_EVS_SwitchSpearStance = {
    Call(GetIndexFromHome, ACTOR_SELF, LVarA)
    Set(LFlag0, 0)
    Call(CreateHomeTargetList, 0x8004)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    IfLt(LVar1, LVarA)
        Set(LFlag0, 1)
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfEq(LFlag0, 1)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        IfEq(LVar0, 0)
            Set(LVar0, 1)
            ExecWait(TTYD64_jan_spear_guy_EVS_UpdateSpearStance)
        EndIf
    Else
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        IfEq(LVar0, 1)
            Set(LVar0, 0)
            ExecWait(TTYD64_jan_spear_guy_EVS_UpdateSpearStance)
        EndIf
    EndIf
    Return
    End
};
// clang-format on

Battle TTYD64_jan_Formations[] = {
    { .name = "\344\352\300\363\265\374x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_jan_Formation_00,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "\344\352\300\363\265\374x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_jan_Formation_01,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "\344\352\300\363\265\374,\310\355\324\253\353",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_jan_Formation_02,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "\344\352\300\363\265\374,\310\355\324\253\353x\023",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_jan_Formation_03,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "\344\352\300\363\265\374,\310\355\324\253\353x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_jan_Formation_04,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "\344\352\300\363\265\374,\310\355\324\253\353,\344\352\300\363\265\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_jan_Formation_05,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "\344\352\300\363\265\374,\310\355\324\253\353,\344\352\300\363\265\374,\310\355\324\253\353",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_jan_Formation_06,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "\344\352\300\363\265\374,KDuO\330\244\333\374,\310\262\341\303\310",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_jan_Formation_07,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "\324\355\352\363]F`~Wx2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_jan_Formation_08,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "\324\355\352\363]F`~Wx3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_jan_Formation_09,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "\310\355\324\253\353x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_jan_Formation_0A,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "\310\355\324\253\353x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_jan_Formation_0B,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "\310\355\324\253\353x4",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_jan_Formation_0C,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "\310\355\324\253\353,\344\352\300\363\265\374,\310\355\324\253\353",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_jan_Formation_0D,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "N_D]Fx2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_jan_Formation_0E,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "N_D]Fx3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_jan_Formation_0F,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = "N_D]Fx4",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_jan_Formation_10,
      .stage = &b_area_jan_jan_01,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_jan_Formation_0A,
      .stage = &TTYD64_jan_Stage_80228BB4,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_jan_spear_guy_EVS_UpdateSpearStance = {
    Switch(LVar0)
        CaseEq(2)
        CaseEq(0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_jan_spear_guy_SpearForwardAnims))
            Call(SetPartEventFlags, ACTOR_SELF, 2, 0x10000)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_jan_spear_guy_SpearUpwardAnims))
            Call(SetPartEventFlags, ACTOR_SELF, 2, 16)
    EndSwitch
    Return
    End
};
// clang-format on

s32 TTYD64_jan_m_bush_StatusTable[] = {
    1,  0, 2,  0, 6,  95, 9,  50, 7,  60, 4,  50, 3,  0, 11, 50, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0,  39, 0,  41, 0,  0,
};

s32 TTYD64_jan_m_bush_StatusTable_8022756C[] = {
    1,  0, 2,  0, 6,  95, 9,  50, 7,  60, 4,  50, 3,  0, 11, 50, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0,  39, 0,  41, 0,  0,
};

s32 TTYD64_jan_jungle_fuzzy_StatusTable[] = {
    1,  0, 2,  0,  6,  95, 9,  50, 7,  70, 4,  90, 3,  0, 11, 70, 5,  75, 10, 75, 8, 90,
    31, 0, 32, -1, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, 0,  0,
};

s32 TTYD64_jan_spear_guy_ShyGuyStatusTable[] = {
    1,  0, 2,  0, 6,  70, 9,  50, 7,  70, 4,  90, 3,  100, 11, 50, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0,   38, 1,  39, 0,  41, 0,  0,
};

s32 TTYD64_jan_spear_guy_SpearGuyStatusTable[] = {
    1,  0, 2,  0, 6,  70, 9,  50, 7,  70, 4,  90, 3,  100, 11, 50, 5,  90, 10, 75, 8, 80,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0,   38, 1,  39, 0,  41, 0,  0,
};

// clang-format off
EvtScript TTYD64_jan_medi_guy_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_jan_medi_guy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_jan_medi_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_jan_medi_guy_EVS_HandleEvent))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 5)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_medi_guy_EVS_TakeTurn = {
    ExecWait(b_area_jan_medi_guy_EVS_FindInjuredActor)
    IfEq(LVar0, -1)
        ExecWait(TTYD64_jan_medi_guy_EVS_Attack_Swoop)
    Else
        Call(RandInt, 1000, LVarA)
        IfLt(LVarA, 600)
            ExecWait(b_area_jan_medi_guy_EVS_Move_HealOne)
        Else
            ExecWait(TTYD64_jan_medi_guy_EVS_Attack_Swoop)
        EndIf
    EndIf
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_jan_spear_guy_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 22 },
        .opacity = 255,
        .idleAnimations = TTYD64_jan_spear_guy_SpearForwardAnims,
        .defenseTable = b_area_jan_m_bush_DefenseTable,
        .eventFlags = 0x10000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -3, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x22001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_jan_spear_guy_ShyGuyAnims,
        .defenseTable = b_area_jan_spear_guy_ShyGuyDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x122001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_jan_spear_guy_SpearAnims,
        .defenseTable = b_area_jan_spear_guy_ShyGuyDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x122001,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_jan_spear_guy_GrassSkirtAnims,
        .defenseTable = b_area_jan_spear_guy_ShyGuyDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_jan_Formation_0C[] = {
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
};

FormationRow TTYD64_jan_Formation_10[] = {
    { .actor = &TTYD64_jan_m_bush,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MBUSH },
    { .actor = &TTYD64_jan_m_bush,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MBUSH },
    { .actor = &TTYD64_jan_m_bush,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MBUSH },
    { .actor = &TTYD64_jan_m_bush,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MBUSH },
};

FormationRow TTYD64_jan_Formation_03[] = {
    { .actor = &TTYD64_jan_spear_guy_80228B64,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
};

FormationRow TTYD64_jan_Formation_06[] = {
    { .actor = &TTYD64_jan_spear_guy_80228B64,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_jan_spear_guy_80228B64,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
};

// clang-format off
EvtScript TTYD64_jan_jungle_fuzzy_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_jan_jungle_fuzzy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_jan_m_bush_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_jan_jungle_fuzzy_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_spear_guy_EVS_ShyGuy_TakeTurn = {
    Call(RandInt, 1, LVar0)
    IfEq(LVar0, 0)
        ExecWait(TTYD64_jan_spear_guy_EVS_Attack_Tackle)
    Else
        ExecWait(TTYD64_jan_spear_guy_EVS_Attack_Vault)
    EndIf
    Return
    End
};
// clang-format on

FormationRow TTYD64_jan_Formation_0D[] = {
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_jan_spear_guy_80228B64,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
};

FormationRow TTYD64_jan_Formation_0B[] = {
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
};

FormationRow TTYD64_jan_Formation_0F[] = {
    { .actor = &TTYD64_jan_m_bush,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MBUSH },
    { .actor = &TTYD64_jan_m_bush,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MBUSH },
    { .actor = &TTYD64_jan_m_bush,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MBUSH },
};

FormationRow TTYD64_jan_Formation_01[] = {
    { .actor = &TTYD64_jan_spear_guy_80228B64,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_jan_spear_guy_80228B64,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_jan_spear_guy_80228B64,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
};

FormationRow TTYD64_jan_Formation_04[] = {
    { .actor = &TTYD64_jan_spear_guy_80228B64,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
};

FormationRow TTYD64_jan_Formation_05[] = {
    { .actor = &TTYD64_jan_spear_guy_80228B64,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_jan_spear_guy_80228B64,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
};

FormationRow TTYD64_jan_Formation_09[] = {
    { .actor = &TTYD64_jan_hurt_plant,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HURTPLANT },
    { .actor = &TTYD64_jan_hurt_plant,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HURTPLANT },
    { .actor = &TTYD64_jan_hurt_plant,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HURTPLANT },
};

FormationRow TTYD64_jan_Formation_07[] = {
    { .actor = &TTYD64_jan_spear_guy_80228B64,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_jan_medi_guy,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
    { .actor = &TTYD64_jan_spike_top,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKETOP },
};

StageListRow TTYD64_jan_Stages[] = {
    { .name = "jan_00", .stage = &b_area_jan_jan_00 },         { .name = "jan_01", .stage = &b_area_jan_jan_01 },
    { .name = "jan_01b", .stage = &b_area_jan_jan_01b },       { .name = "jan_02", .stage = &b_area_jan_jan_02 },
    { .name = "jan_03", .stage = &b_area_jan_jan_03 },         { .name = "jan_03b", .stage = &b_area_jan_jan_03b },
    { .name = "jan_04", .stage = &b_area_jan_jan_04 },         { .name = "jan_04b", .stage = &b_area_jan_jan_04b },
    { .name = "jan_24", .stage = &TTYD64_jan_Stage_80228BB4 }, {},
};

s32 TTYD64_jan_spear_guy_ShyGuyAnims[] = {
    1,  0x3B0001, 7, 0x3B0000, 6, 0x3B0012, 9, 0x3B0001, 8, 0x3B0000,
    11, 0x3B0001, 5, 0x3B0000, 4, 0x3B0013, 3, 0x3B0013, 0,
};

s32 TTYD64_jan_spike_top_CeilingAnims[] = {
    1,  0x4D0004, 7, 0x4D0001, 6, 0x4D001C, 9, 0x4D0004, 8, 0x4D0001,
    11, 0x4D0004, 5, 0x4D0001, 4, 0x4D001F, 3, 0x4D001F, 0,
};

// clang-format off
EvtScript TTYD64_jan_EVS_8022844C = {
    Call(SetSpriteShading, -1)
    Call(SetCamBGColor, 1, 0, 0, 0)
    Call(SetDarknessMode, 1)
    Return
    End
};
// clang-format on

s32 TTYD64_jan_m_bush_DefaultAnims[] = {
    1,  0x450002, 7, 0x450001, 6, 0x450008, 9, 0x450002, 8, 0x450001,
    11, 0x450002, 5, 0x450001, 4, 0x450009, 3, 0x450009, 0,
};

s32 TTYD64_jan_hurt_plant_DefaultAnims[] = {
    1,  0x440002, 7, 0x440000, 6, 0x44000C, 9, 0x440002, 8, 0x440000,
    11, 0x440002, 5, 0x440000, 4, 0x440009, 3, 0x440009, 0,
};

s32 TTYD64_jan_spear_guy_SpearForwardAnims[] = {
    1,  0x420004, 7, 0x420002, 6, 0x42000D, 9, 0x42000F, 8, 0x420002,
    11, 0x420004, 5, 0x420002, 4, 0x42000F, 3, 0x42000F, 0,
};

s32 TTYD64_jan_medi_guy_DefaultAnims[] = {
    1,  0x400001, 7, 0x400000, 6, 0x400004, 9, 0x400001, 8, 0x400000,
    11, 0x400001, 5, 0x400000, 4, 0x40000A, 3, 0x40000A, 0,
};

s32 TTYD64_jan_spear_guy_SpearUpwardAnims[] = {
    1,  0x420003, 7, 0x42000D, 6, 0x42000D, 9, 0x42000F, 8, 0x420001,
    11, 0x420003, 5, 0x420001, 4, 0x42000F, 3, 0x42000F, 0,
};

s32 TTYD64_jan_spike_top_GroundAnims[] = {
    1,  0x4D0003, 7, 0x4D0000, 6, 0x4D001B, 9, 0x4D0003, 8, 0x4D0000,
    11, 0x4D0003, 5, 0x4D0000, 4, 0x4D001E, 3, 0x4D001E, 0,
};

// clang-format off
EvtScript TTYD64_jan_spear_guy_EVS_ShyGuy_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_jan_spear_guy_EVS_ShyGuy_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_jan_spear_guy_EVS_ShyGuy_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_jan_spear_guy_EVS_ShyGuy_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_jan_jungle_fuzzy_DefaultAnims[] = {
    1,  0x2B0301, 7, 0x2B0300, 6, 0x2B030E, 9, 0x2B0301, 8, 0x2B0300,
    11, 0x2B0301, 5, 0x2B0300, 4, 0x2B030F, 3, 0x2B030F, 0,
};

// clang-format off
EvtScript TTYD64_jan_m_bush_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_jan_hurt_plant_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_jan_hurt_plant_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_jan_hurt_plant_EVS_HandleEvent))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan_m_bush_EVS_Init_80228790 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_jan_m_bush_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_jan_m_bush_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_jan_m_bush_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_jan_spike_top_ToppledAnims[] = {
    1, 0x4D0005, 7, 0x4D0002, 6, 0x4D001D, 9, 0x4D0005, 8, 0x4D0002, 11, 0x4D0005, 4, 0x4D0020, 3, 0x4D0020, 0,
};

// clang-format off
EvtScript TTYD64_jan_spear_guy_EVS_HandlePhase = {
    Call(BindHandlePhase, ACTOR_SELF, 0)
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_jan_spear_guy_EVS_Idle))
    Return
    End
};
// clang-format on

FormationRow TTYD64_jan_Formation_0A[] = {
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
};

FormationRow TTYD64_jan_Formation_0E[] = {
    { .actor = &TTYD64_jan_m_bush,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MBUSH },
    { .actor = &TTYD64_jan_m_bush,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MBUSH },
};

FormationRow TTYD64_jan_Formation_00[] = {
    { .actor = &TTYD64_jan_spear_guy_80228B64,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_jan_spear_guy_80228B64,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
};

FormationRow TTYD64_jan_Formation_02[] = {
    { .actor = &TTYD64_jan_spear_guy_80228B64,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPEARGUY },
    { .actor = &TTYD64_jan_jungle_fuzzy,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_JUNGLEFUZZY },
};

FormationRow TTYD64_jan_Formation_08[] = {
    { .actor = &TTYD64_jan_hurt_plant,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HURTPLANT },
    { .actor = &TTYD64_jan_hurt_plant,
      .home = { .index = 2 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HURTPLANT },
};

ActorBlueprint TTYD64_jan_jungle_fuzzy = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x29,
    .level = 16,
    .partCount = 1,
    .partsData = TTYD64_jan_jungle_fuzzy_ActorParts,
    .initScript = &TTYD64_jan_jungle_fuzzy_EVS_Init,
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

ActorBlueprint TTYD64_jan_m_bush = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x27,
    .level = 16,
    .partCount = 1,
    .partsData = TTYD64_jan_m_bush_ActorParts,
    .initScript = &TTYD64_jan_m_bush_EVS_Init_80228790,
    .statusTable = TTYD64_jan_m_bush_StatusTable,
    .escapeChance = 70,
    .airLiftChance = 85,
    .hurricaneChance = 80,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 1,
    .size = { 32, 30 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_jan_spike_top = {
    .flags = 0x800,
    .maxHP = 5,
    .type = 0x2C,
    .level = 17,
    .partCount = 1,
    .partsData = TTYD64_jan_spike_top_ActorParts,
    .initScript = &TTYD64_jan_spike_top_EVS_Init,
    .statusTable = b_area_jan_spike_top_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 70,
    .hurricaneChance = 65,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 24, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -8, 16 },
    .statusTextOffset = { 8, 13 },
};

ActorBlueprint TTYD64_jan_jungle_fuzzy_80228A74 = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x29,
    .level = 16,
    .partCount = 1,
    .partsData = TTYD64_jan_jungle_fuzzy_ActorParts,
    .initScript = &TTYD64_jan_jungle_fuzzy_EVS_Init,
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

ActorBlueprint TTYD64_jan_spear_guy = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x2A,
    .level = 16,
    .partCount = 4,
    .partsData = TTYD64_jan_spear_guy_ActorParts,
    .initScript = &TTYD64_jan_spear_guy_EVS_Init,
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

ActorBlueprint TTYD64_jan_medi_guy = {
    .flags = 0x200,
    .maxHP = 7,
    .type = 0x22,
    .level = 14,
    .partCount = 1,
    .partsData = TTYD64_jan_medi_guy_ActorParts,
    .initScript = &TTYD64_jan_medi_guy_EVS_Init,
    .statusTable = b_area_jan_medi_guy_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 90,
    .hurricaneChance = 95,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 2,
    .size = { 24, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 12, 31 },
};

ActorBlueprint TTYD64_jan_spear_guy_80228B64 = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x2A,
    .level = 16,
    .partCount = 4,
    .partsData = TTYD64_jan_spear_guy_ActorParts,
    .initScript = &TTYD64_jan_spear_guy_EVS_Init,
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

Stage TTYD64_jan_Stage_80228BB4 = {
    .texture = "jan_tex",
    .shape = "jan_bt05_shape",
    .hit = "jan_bt05_hit",
    .preBattle = &TTYD64_jan_EVS_8022844C,
    .postBattle = &b_area_jan_jan_04b_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_jan_hurt_plant = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x26,
    .level = 16,
    .partCount = 1,
    .partsData = TTYD64_jan_hurt_plant_ActorParts,
    .initScript = &TTYD64_jan_m_bush_EVS_Init,
    .statusTable = TTYD64_jan_m_bush_StatusTable_8022756C,
    .escapeChance = 70,
    .airLiftChance = 20,
    .hurricaneChance = 20,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 1,
    .size = { 40, 35 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -18, 23 },
    .statusTextOffset = { 1, 20 },
};

ActorPartBlueprint TTYD64_jan_spike_top_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_jan_spike_top_CeilingAnims,
        .defenseTable = b_area_jan_spike_top_UprightDefense,
        .eventFlags = 0x1010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 14 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_jan_jungle_fuzzy_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_jan_jungle_fuzzy_DefaultAnims,
        .defenseTable = b_area_jan_m_bush_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_jan_m_bush_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 22 },
        .opacity = 255,
        .idleAnimations = TTYD64_jan_m_bush_DefaultAnims,
        .defenseTable = b_area_jan_m_bush_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_jan_medi_guy_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 38 },
        .opacity = 255,
        .idleAnimations = TTYD64_jan_medi_guy_DefaultAnims,
        .defenseTable = b_area_jan_spear_guy_ShyGuyDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -5 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_jan_hurt_plant_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -10, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_jan_hurt_plant_DefaultAnims,
        .defenseTable = b_area_jan_m_bush_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -8, -5 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_jan_spear_guy_UpwardSpearFormation[] = {
    { .actor = &TTYD64_jan_spear_guy,
      .home = { .vec = &b_area_jan_spear_guy_SummonPos },
      .priority = 100,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_jan_jungle_fuzzy_SummonFormation[] = {
    { .actor = &TTYD64_jan_jungle_fuzzy_80228A74,
      .home = { .vec = &b_area_jan_jungle_fuzzy_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_jan_spear_guy_ForwardSpearFormation[] = {
    { .actor = &TTYD64_jan_spear_guy,
      .home = { .vec = &b_area_jan_spear_guy_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

void TTYD64_InstallBattles_jan(void) {
    Mod_SetBattleList("TTYD64", 20, TTYD64_jan_Formations);
    Mod_SetStageList("TTYD64", 20, TTYD64_jan_Stages);
}
