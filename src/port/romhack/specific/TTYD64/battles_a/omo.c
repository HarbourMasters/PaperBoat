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
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(ClampAngleFloat);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyPartTo);
API_CALLABLE(FlyToGoal);
API_CALLABLE(ForceHomePos);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetInstigatorValue);
API_CALLABLE(GetLastDamage);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartOffset);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToCurrent);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HideHealthBar);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(JumpWithBounce);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(ResetActorSounds);
API_CALLABLE(ResetAllActorSounds);
API_CALLABLE(RotateModel);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorType);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartFlags);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartRotation);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetPartTargetFlagBits);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTargetActor);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowMessageBox);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(WasStatusInflicted);
API_CALLABLE(YieldTurn);
API_CALLABLE(b_area_omo_medi_guy_MediGuySpriteRotationFunc);
API_CALLABLE(b_area_omo_sky_guy_StartRumbleWithParams);
API_CALLABLE(b_area_omo_spy_guy_CheckPlayerCanLoseCommand);
API_CALLABLE(b_area_omo_spy_guy_DisableRandomAbility);
API_CALLABLE(b_area_omo_spy_guy_GetItemEntityPosition);
API_CALLABLE(b_area_omo_spy_guy_ItemEntityJumpToPos);
API_CALLABLE(b_area_omo_spy_guy_StartRumbleWithParams);
API_CALLABLE(func_8026E914);
extern s32 b_area_omo_anti_guy_DefenseTable[];
extern EvtScript b_area_omo_anti_guy_EVS_HandleEvent;
extern EvtScript b_area_omo_anti_guy_EVS_Idle;
extern EvtScript b_area_omo_anti_guy_EVS_ReturnHome;
extern s32 b_area_omo_anti_guy_StatusTable[];
extern EvtScript b_area_omo_blue_shy_guy_EVS_HandleEvent;
extern EvtScript b_area_omo_blue_shy_guy_EVS_ReturnHome;
extern EvtScript b_area_omo_green_shy_guy_EVS_HandleEvent;
extern EvtScript b_area_omo_green_shy_guy_EVS_Idle;
extern EvtScript b_area_omo_green_shy_guy_EVS_ReturnHome;
extern EvtScript b_area_omo_groove_guy_EVS_CountActiveSummoners;
extern EvtScript b_area_omo_groove_guy_EVS_GetAvailableColumn;
extern EvtScript b_area_omo_groove_guy_EVS_HandleEvent;
extern EvtScript b_area_omo_groove_guy_EVS_Idle;
extern EvtScript b_area_omo_groove_guy_EVS_PerformSummonDance;
extern EvtScript b_area_omo_groove_guy_EVS_ReturnHome;
extern Vec3i b_area_omo_groove_guy_SummonPos;
extern s32 b_area_omo_medi_guy_DefenseTable[];
extern EvtScript b_area_omo_medi_guy_EVS_FindInjuredActor;
extern EvtScript b_area_omo_medi_guy_EVS_HandleEvent;
extern EvtScript b_area_omo_medi_guy_EVS_Idle;
extern EvtScript b_area_omo_medi_guy_EVS_Move_HealOne;
extern EvtScript b_area_omo_medi_guy_EVS_ReturnHome;
extern s32 b_area_omo_medi_guy_StatusTable[];
extern EvtScript b_area_omo_omo_01_EVS_PostBattle;
extern EvtScript b_area_omo_omo_01_EVS_UpdateRockingHorse;
extern Stage b_area_omo_omo_02;
extern Stage b_area_omo_omo_03;
extern Stage b_area_omo_omo_03b;
extern Stage b_area_omo_omo_04;
extern Stage b_area_omo_omo_05;
extern Stage b_area_omo_omo_05b;
extern Stage b_area_omo_omo_06;
extern Stage b_area_omo_omo_07;
extern EvtScript b_area_omo_pink_shy_guy_EVS_HandleEvent;
extern EvtScript b_area_omo_pink_shy_guy_EVS_ReturnHome;
extern s32 b_area_omo_pyro_guy_DefenseTable[];
extern EvtScript b_area_omo_pyro_guy_EVS_HandleEvent;
extern EvtScript b_area_omo_pyro_guy_EVS_Idle;
extern EvtScript b_area_omo_pyro_guy_EVS_ReturnHome;
extern s32 b_area_omo_pyro_guy_StatusTable[];
extern s32 b_area_omo_red_shy_guy_DefenseTable[];
extern EvtScript b_area_omo_red_shy_guy_EVS_HandleEvent;
extern EvtScript b_area_omo_red_shy_guy_EVS_Idle;
extern EvtScript b_area_omo_red_shy_guy_EVS_ReturnHome;
extern EvtScript b_area_omo_sky_guy_EVS_Flying_Idle;
extern EvtScript b_area_omo_sky_guy_EVS_Ground_HandleEvent;
extern EvtScript b_area_omo_sky_guy_EVS_Ground_Idle;
extern EvtScript b_area_omo_sky_guy_EVS_Ground_ReturnHome;
extern EvtScript b_area_omo_sky_guy_EVS_KillActor;
extern EvtScript b_area_omo_sky_guy_EVS_ResetAnimations;
extern EvtScript b_area_omo_sky_guy_EVS_StretchBalloons;
extern s32 b_area_omo_sky_guy_FlyingDefense[];
extern s32 b_area_omo_sky_guy_GroundDefense[];
extern s32 b_area_omo_sky_guy_StoneAnims[];
extern s32 b_area_omo_spy_guy_DefenseTable[];
extern EvtScript b_area_omo_spy_guy_EVS_Idle;
extern s32 b_area_omo_spy_guy_StoneAnims[];
extern EvtScript b_area_omo_yellow_shy_guy_EVS_HandleEvent;
extern EvtScript b_area_omo_yellow_shy_guy_EVS_ReturnHome;
extern EvtScript TTYD64_omo_anti_guy_EVS_Attack_Vault;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Vault;
extern EvtScript TTYD64_omo_red_shy_guy_EVS_Attack_Vault;
extern EvtScript TTYD64_omo_sky_guy_EVS_Attack_Vault;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Vault_8021AF70;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Vault_8021BB4C;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Vault_8021C728;
extern EvtScript TTYD64_omo_spy_guy_EVS_Attack_Mallet;
extern EvtScript TTYD64_omo_medi_guy_EVS_Attack_Swoop;
extern EvtScript TTYD64_omo_sky_guy_EVS_Flying_TakeTurn;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Tackle;
extern EvtScript TTYD64_omo_red_shy_guy_EVS_Attack_Tackle;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Tackle_80220DF8;
extern EvtScript TTYD64_omo_anti_guy_EVS_Attack_Tackle;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Tackle_80221C40;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Tackle_80222364;
extern EvtScript TTYD64_omo_sky_guy_EVS_Attack_Tackle;
extern EvtScript TTYD64_omo_pyro_guy_EVS_TakeTurn;
extern EvtScript TTYD64_omo_groove_guy_EVS_Attack_SleepySpin;
extern EvtScript TTYD64_omo_groove_guy_EVS_Attack_Tackle;
extern EvtScript TTYD64_omo_spy_guy_EVS_HandleEvent;
extern EvtScript TTYD64_omo_sky_guy_EVS_Flying_HandleEvent;
extern EvtScript TTYD64_omo_spy_guy_EVS_Attack_Slingshot;
extern EvtScript TTYD64_omo_sky_guy_EVS_PopBalloons;
extern EvtScript TTYD64_omo_spy_guy_EVS_TrySwitchWeapon;
extern EvtScript TTYD64_omo_groove_guy_EVS_SummonGrooveGuy;
extern EvtScript TTYD64_omo_groove_guy_EVS_TakeTurn;
extern EvtScript TTYD64_omo_spy_guy_EVS_ManageItemMotion;
extern EvtScript TTYD64_omo_groove_guy_EVS_SummonMediGuy;
extern EvtScript TTYD64_omo_groove_guy_EVS_SummonShyGuy;
extern EvtScript TTYD64_omo_sky_guy_EVS_Flying_Init;
extern EvtScript TTYD64_omo_omo_01_EVS_PreBattle;
extern EvtScript TTYD64_omo_spy_guy_EVS_Init;
extern EvtScript TTYD64_omo_spy_guy_EVS_TakeTurn;
extern EvtScript TTYD64_omo_groove_guy_EVS_RandomSummon;
extern EvtScript TTYD64_omo_medi_guy_EVS_Init;
extern EvtScript TTYD64_omo_medi_guy_EVS_TakeTurn;
extern EvtScript TTYD64_omo_groove_guy_EVS_Init;
extern EvtScript TTYD64_omo_anti_guy_EVS_TakeTurn;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_TakeTurn;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_TakeTurn_8022EEF8;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_TakeTurn_8022EF54;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_TakeTurn_8022EFB0;
extern EvtScript TTYD64_omo_red_shy_guy_EVS_TakeTurn;
extern EvtScript TTYD64_omo_sky_guy_EVS_Ground_TakeTurn;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_Init;
extern EvtScript TTYD64_omo_red_shy_guy_EVS_Init;
extern EvtScript TTYD64_omo_pyro_guy_EVS_Init;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_Init_8022FD20;
extern EvtScript TTYD64_omo_anti_guy_EVS_Init;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_Init_8022FE04;
extern EvtScript TTYD64_omo_green_shy_guy_EVS_Init_8022FE50;
extern Stage TTYD64_omo_omo_01;
extern ActorBlueprint TTYD64_omo_medi_guy;
extern ActorBlueprint TTYD64_omo_green_shy_guy;
extern ActorBlueprint TTYD64_omo_green_shy_guy_80230554;
extern ActorBlueprint TTYD64_omo_groove_guy;
extern ActorBlueprint TTYD64_omo_pyro_guy;
extern ActorBlueprint TTYD64_omo_green_shy_guy_80230644;
extern ActorBlueprint TTYD64_omo_anti_guy;
extern ActorBlueprint TTYD64_omo_red_shy_guy;
extern ActorBlueprint TTYD64_omo_green_shy_guy_802306BC;
extern ActorBlueprint TTYD64_omo_spy_guy;
extern ActorBlueprint TTYD64_omo_sky_guy;
extern Battle TTYD64_omo_Formations[];
extern ActorPartBlueprint TTYD64_omo_sky_guy_ActorParts[];
extern s32 TTYD64_omo_groove_guy_StatusTable[];
extern s32 TTYD64_omo_red_shy_guy_StatusTable[];
extern s32 TTYD64_omo_green_shy_guy_StatusTable[];
extern s32 TTYD64_omo_sky_guy_FlyingStatusTable[];
extern s32 TTYD64_omo_green_shy_guy_StatusTable_8022DFB8[];
extern s32 TTYD64_omo_green_shy_guy_StatusTable_8022E064[];
extern s32 TTYD64_omo_spy_guy_StatusTable[];
extern s32 TTYD64_omo_green_shy_guy_StatusTable_8022E1BC[];
extern FormationRow TTYD64_omo_Formation_0B[];
extern FormationRow TTYD64_omo_Formation_13[];
extern FormationRow TTYD64_omo_Formation_19[];
extern FormationRow TTYD64_omo_Formation_09[];
extern FormationRow TTYD64_omo_Formation_1A[];
extern FormationRow TTYD64_omo_Formation_1B[];
extern FormationRow TTYD64_omo_Formation_23[];
extern FormationRow TTYD64_omo_Formation_20[];
extern FormationRow TTYD64_omo_Formation_29[];
extern FormationRow TTYD64_omo_Formation_0A[];
extern FormationRow TTYD64_omo_Formation_0C[];
extern FormationRow TTYD64_omo_Formation_0F[];
extern FormationRow TTYD64_omo_Formation_11[];
extern FormationRow TTYD64_omo_Formation_12[];
extern FormationRow TTYD64_omo_Formation_14[];
extern FormationRow TTYD64_omo_Formation_18[];
extern FormationRow TTYD64_omo_Formation_03[];
extern FormationRow TTYD64_omo_Formation_08[];
extern FormationRow TTYD64_omo_Formation_06[];
extern FormationRow TTYD64_omo_Formation_07[];
extern FormationRow TTYD64_omo_Formation_2B[];
extern FormationRow TTYD64_omo_Formation_2A[];
extern FormationRow TTYD64_omo_Formation_1F[];
extern FormationRow TTYD64_omo_Formation_1D[];
extern FormationRow TTYD64_omo_Formation_22[];
extern FormationRow TTYD64_omo_Formation_21[];
extern FormationRow TTYD64_omo_Formation_26[];
extern FormationRow TTYD64_omo_Formation_27[];
extern FormationRow TTYD64_omo_Formation_24[];
extern FormationRow TTYD64_omo_Formation_28[];
extern StageListRow TTYD64_omo_Stages[];
extern s32 TTYD64_omo_green_shy_guy_DefaultAnims[];
extern s32 TTYD64_omo_red_shy_guy_DefaultAnims[];
extern s32 TTYD64_omo_sky_guy_YellowBalloonAnims[];
extern s32 TTYD64_omo_spy_guy_SlingshotAnims[];
extern s32 TTYD64_omo_sky_guy_RedBalloonAnims[];
extern s32 TTYD64_omo_yellow_shy_guy_DefaultAnims[];
extern s32 TTYD64_omo_sky_guy_DefaultAnims[];
extern s32 TTYD64_omo_medi_guy_DefaultAnims[];
extern s32 TTYD64_omo_pink_shy_guy_DefaultAnims[];
extern s32 TTYD64_omo_blue_shy_guy_DefaultAnims[];
extern s32 TTYD64_omo_spy_guy_MalletAnims[];
extern s32 TTYD64_omo_groove_guy_DefaultAnims[];
extern s32 TTYD64_omo_sky_guy_GroundAnims[];
extern s32 TTYD64_omo_sky_guy_BlueBalloonAnims[];
extern s32 TTYD64_omo_pyro_guy_DefaultAnims[];
extern s32 TTYD64_omo_anti_guy_DefaultAnims[];
extern ActorPartBlueprint TTYD64_omo_spy_guy_ActorParts[];
extern FormationRow TTYD64_omo_Formation_0D[];
extern FormationRow TTYD64_omo_Formation_0E[];
extern FormationRow TTYD64_omo_Formation_10[];
extern FormationRow TTYD64_omo_Formation_15[];
extern FormationRow TTYD64_omo_Formation_16[];
extern FormationRow TTYD64_omo_Formation_17[];
extern FormationRow TTYD64_omo_Formation_00[];
extern FormationRow TTYD64_omo_Formation_01[];
extern FormationRow TTYD64_omo_Formation_04[];
extern FormationRow TTYD64_omo_Formation_05[];
extern FormationRow TTYD64_omo_Formation_02[];
extern FormationRow TTYD64_omo_Formation_1E[];
extern FormationRow TTYD64_omo_Formation_1C[];
extern FormationRow TTYD64_omo_Formation_25[];
extern ActorPartBlueprint TTYD64_omo_green_shy_guy_ActorParts[];
extern ActorPartBlueprint TTYD64_omo_groove_guy_ActorParts[];
extern ActorPartBlueprint TTYD64_omo_green_shy_guy_ActorParts_80230818[];
extern ActorPartBlueprint TTYD64_omo_medi_guy_ActorParts[];
extern ActorPartBlueprint TTYD64_omo_red_shy_guy_ActorParts[];
extern ActorPartBlueprint TTYD64_omo_pyro_guy_ActorParts[];
extern ActorPartBlueprint TTYD64_omo_green_shy_guy_ActorParts_802308A8[];
extern ActorPartBlueprint TTYD64_omo_green_shy_guy_ActorParts_802308CC[];
extern ActorPartBlueprint TTYD64_omo_anti_guy_ActorParts[];
extern FormationRow TTYD64_omo_groove_guy_GrooveGuyFormation[];
extern FormationRow TTYD64_omo_Formation_2C[];
extern FormationRow TTYD64_omo_groove_guy_MediGuyFormation[];
extern FormationRow TTYD64_omo_groove_guy_ShyGuyFormation[];

// clang-format off
EvtScript TTYD64_omo_anti_guy_EVS_Attack_Vault = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0509)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0503)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 80)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
    Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0504)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0509)
            Thread
                Wait(12)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B050A)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0505)
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
            SetConst(LVar1, 0x3B0504)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0501)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0509)
    Thread
        Wait(9)
        Call(SetAnimation, ACTOR_SELF, 1, 0x3B050A)
    EndThread
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(JumpToGoal, ACTOR_SELF, 18, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 12, 32)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0509)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0507)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0510)
            Wait(10)
            Call(PlaySoundAtActor, ACTOR_SELF, 8387)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 50)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0511)
            Else
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0513)
            EndIf
            Wait(25)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Label(2)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3B0504)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0501)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Vault = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0309)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0303)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 80)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
    Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0304)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0309)
            Thread
                Wait(12)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B030A)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0305)
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
            SetConst(LVar1, 0x3B0304)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0301)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0309)
    Thread
        Wait(9)
        Call(SetAnimation, ACTOR_SELF, 1, 0x3B030A)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0309)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0307)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0310)
            Wait(10)
            Call(PlaySoundAtActor, ACTOR_SELF, 8387)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 50)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0311)
            Else
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0313)
            EndIf
            Wait(25)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Label(2)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3B0304)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0301)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_red_shy_guy_EVS_Attack_Vault = {
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
EvtScript TTYD64_omo_sky_guy_EVS_Attack_Vault = {
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
EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Vault_8021AF70 = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0409)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0403)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 80)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
    Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0404)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0409)
            Thread
                Wait(12)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B040A)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0405)
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
            SetConst(LVar1, 0x3B0404)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0401)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0409)
    Thread
        Wait(9)
        Call(SetAnimation, ACTOR_SELF, 1, 0x3B040A)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0409)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0407)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0410)
            Wait(10)
            Call(PlaySoundAtActor, ACTOR_SELF, 8387)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 50)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0411)
            Else
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0413)
            EndIf
            Wait(25)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Label(2)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3B0404)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0401)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Vault_8021BB4C = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0209)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0203)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 80)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
    Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0204)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0209)
            Thread
                Wait(12)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B020A)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0205)
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
            SetConst(LVar1, 0x3B0204)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0201)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0209)
    Thread
        Wait(9)
        Call(SetAnimation, ACTOR_SELF, 1, 0x3B020A)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0209)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0207)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0210)
            Wait(10)
            Call(PlaySoundAtActor, ACTOR_SELF, 8387)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 50)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0211)
            Else
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0213)
            EndIf
            Wait(25)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Label(2)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3B0204)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0201)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Vault_8021C728 = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0109)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0103)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 80)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
    Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0104)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0109)
            Thread
                Wait(12)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B010A)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0105)
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
            SetConst(LVar1, 0x3B0104)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0101)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0109)
    Thread
        Wait(9)
        Call(SetAnimation, ACTOR_SELF, 1, 0x3B010A)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0109)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0107)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0110)
            Wait(10)
            Call(PlaySoundAtActor, ACTOR_SELF, 8387)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 50)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0111)
            Else
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0113)
            EndIf
            Wait(25)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Label(2)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3B0104)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0101)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_spy_guy_EVS_Attack_Mallet = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3F0007)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 70, 0, 0)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
    Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3F0007)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar1)
    IfNotFlag(LVar1, 0x80000)
        Call(AddGoalPos, ACTOR_SELF, 20, 0, 0)
    EndIf
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3F0003)
    Wait(10)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Thread
        Wait(4)
        Call(PlaySoundAtActor, ACTOR_SELF, 807)
    EndThread
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3F000A)
            Wait(6)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3F0007)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x3F000A)
    Wait(5)
    Wait(2)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Set(LFlag0, 0)
            Call(GetBattleFlags, LVar0)
            IfNotFlag(LVar0, (-0x7FFFFFFF - 1))
                Call(b_area_omo_spy_guy_CheckPlayerCanLoseCommand, LVar0)
                IfNe(LVar0, -1)
                    Set(LFlag0, 1)
                EndIf
            EndIf
            Call(GetOwnerTarget, LVar6, 0)
            Call(GetLastDamage, LVar6, LVar0)
            IfLe(LVar0, 0)
                Wait(20)
                Goto(100)
            EndIf
            Call(GetStatusFlags, ACTOR_SELF, LVar1)
            IfFlag(LVar1, 0x80000)
                Wait(20)
                Goto(100)
            EndIf
            Call(GetStatusFlags, LVar6, LVar1)
            IfFlag(LVar1, 0x40100000)
                Wait(20)
                Goto(100)
            EndIf
            IfEq(LFlag0, 1)
                Call(SetActorVar, ACTOR_SELF, 0, 1)
                Exec(TTYD64_omo_spy_guy_EVS_ManageItemMotion)
                Wait(8)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3F0007)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar0, 70)
                Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(RunToGoal, ACTOR_SELF, 0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3F0003)
                Label(0)
                Call(GetActorVar, ACTOR_SELF, 0, LVar0)
                IfNe(LVar0, 0)
                    Wait(1)
                    Goto(0)
                EndIf
                Call(SetAnimation, ACTOR_SELF, 1, 0x3F0007)
                Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                Call(b_area_omo_spy_guy_GetItemEntityPosition, LVar0, LVar1, LVar2, LVar3)
                Add(LVar1, 20)
                Sub(LVar3, 2)
                Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
                Call(SetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
                Call(RunToGoal, ACTOR_SELF, 0, 0)
                Thread
                    Wait(5)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8412)
                    Call(b_area_omo_spy_guy_StartRumbleWithParams, 200, 10)
                EndThread
                Call(SetAnimation, ACTOR_SELF, 1, 0x3F0009)
                Wait(5)
                Call(SetActorVar, ACTOR_SELF, 0, 2)
                Sub(LVar1, 7)
                Call(PlayEffect_impl, 67, 0, LVar1, LVar2, LVar3, Float(1.0), 0, 0, 0, 0, 0, 0, 0, 0)
                Wait(40)
            Else
                Wait(8)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3F0007)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar0, 70)
                Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(RunToGoal, ACTOR_SELF, 0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3F0003)
                Wait(10)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 10)
                Call(PlayEffect_impl, 16, 2, 0, LVar0, LVar1, LVar2, 25, -45, 20, 0, 0, 0, 0, 0)
                Wait(20)
            EndIf
            Label(100)
            Call(UseBattleCamPreset, 2)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3F0007)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_medi_guy_EVS_Attack_Swoop = {
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
                    Call(b_area_omo_medi_guy_MediGuySpriteRotationFunc, LVar0, LVar1, 15, 60, Float(30.0))
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
            ExecWait(b_area_omo_medi_guy_EVS_ReturnHome)
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
            ExecWait(b_area_omo_medi_guy_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_sky_guy_EVS_Flying_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 743)
    Call(SetAnimation, ACTOR_SELF, 2, 0x3D0008)
    Wait(12)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Add(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 6, 0x3D000B)
    Wait(12)
    Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 744)
    Call(SetPartSounds, ACTOR_SELF, 6, 2, 0, 0)
    Call(GetOwnerTarget, LVar3, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 3, 32)
    Switch(LVar0)
        CaseEq(6)
            Call(SetTargetActor, ACTOR_SELF, LVar3)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 120)
            Set(LVar1, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(12.0))
            Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
            Call(JumpPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
            ExecWait(b_area_omo_sky_guy_EVS_ResetAnimations)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        CaseEq(5)
            Call(SetTargetActor, ACTOR_SELF, LVar3)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Set(LVar1, -5)
            Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(14.0))
            Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
            Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 30, 0)
            Call(SetAnimation, ACTOR_SELF, 2, 0x3D0007)
            Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Sub(LVar0, 65)
            Set(LVar1, -5)
            Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(6.0))
            Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
            Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 15, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
            ExecWait(b_area_omo_sky_guy_EVS_ResetAnimations)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
    EndSwitch
    Call(GetOwnerTarget, LVar3, 0)
    Call(SetTargetActor, ACTOR_SELF, LVar3)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(14.0))
    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
    Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 15, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000000, 0, 0, 3, 32)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Sub(LVar0, 55)
            Set(LVar1, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(6.0))
            Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.099609375))
            Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 25, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(4.0))
            Sub(LVar0, 20)
            Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 21, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
        EndCaseGroup
    EndSwitch
    ExecWait(b_area_omo_sky_guy_EVS_ResetAnimations)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Tackle = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0303)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0304)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0305)
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
            SetConst(LVar1, 0x3B0304)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0301)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0304)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0305)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0301)
    Wait(8)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    ExecWait(b_area_omo_pink_shy_guy_EVS_ReturnHome)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_red_shy_guy_EVS_Attack_Tackle = {
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
    ExecWait(b_area_omo_red_shy_guy_EVS_ReturnHome)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Tackle_80220DF8 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0103)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0104)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0105)
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
            SetConst(LVar1, 0x3B0104)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0101)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0104)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0105)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0101)
    Wait(8)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    ExecWait(b_area_omo_blue_shy_guy_EVS_ReturnHome)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_anti_guy_EVS_Attack_Tackle = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0503)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0504)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0505)
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
            SetConst(LVar1, 0x3B0504)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0501)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0504)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0505)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 10, 32)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 15)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0501)
    Wait(8)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    ExecWait(b_area_omo_anti_guy_EVS_ReturnHome)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Tackle_80221C40 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0203)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0204)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0205)
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
            SetConst(LVar1, 0x3B0204)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0201)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0204)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0205)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0201)
    Wait(8)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    ExecWait(b_area_omo_green_shy_guy_EVS_ReturnHome)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_green_shy_guy_EVS_Attack_Tackle_80222364 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0403)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0404)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0405)
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
            SetConst(LVar1, 0x3B0404)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0401)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0404)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0405)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0401)
    Wait(8)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    ExecWait(b_area_omo_yellow_shy_guy_EVS_ReturnHome)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_sky_guy_EVS_Attack_Tackle = {
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
    ExecWait(b_area_omo_sky_guy_EVS_Ground_ReturnHome)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_pyro_guy_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3E0003)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 70)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
    Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3E0004)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetActorSounds, ACTOR_SELF, 2, 751, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3E0005)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
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
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            ExecWait(b_area_omo_pyro_guy_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 751)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3E0005)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 2, 0, 0, 4, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(UseBattleCamPreset, 2)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3E0001)
            Wait(8)
            Call(YieldTurn)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_omo_pyro_guy_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_groove_guy_EVS_Attack_SleepySpin = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
    Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3C0010)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 738)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3C000C)
    Set(LVar0, 0)
    Loop(30)
        Add(LVar0, 48)
        Mod(LVar0, 360)
        Call(SetActorYaw, ACTOR_SELF, LVar0)
        Wait(1)
    EndLoop
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 32)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3C000B)
            Wait(20)
            IfEq(LVar0, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_omo_groove_guy_EVS_ReturnHome)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x40000000, 0, -0x7FFBFDCE, 0, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(WasStatusInflicted, ACTOR_SELF, LVar0)
            IfEq(LVar0, 1)
                Thread
                    Set(LVar0, 0)
                    Call(GetOwnerTarget, LVar1, 0)
                    Loop(30)
                        Add(LVar0, 48)
                        Mod(LVar0, 360)
                        Call(SetActorYaw, LVar1, LVar0)
                        Wait(1)
                    EndLoop
                    Call(SetActorYaw, LVar1, 0)
                EndThread
            EndIf
            Call(PlaySoundAtActor, ACTOR_SELF, 739)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3C000B)
            Set(LVar0, 0)
            Loop(15)
                Add(LVar0, 24)
                Mod(LVar0, 360)
                Call(SetActorYaw, ACTOR_SELF, LVar0)
                Wait(1)
            EndLoop
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3C000C)
            Call(UseBattleCamPreset, 2)
            Call(PlaySoundAtActor, ACTOR_SELF, 740)
            Thread
                Set(LVar0, 0)
                Loop(20)
                    Add(LVar0, 72)
                    Mod(LVar0, 360)
                    Call(SetActorYaw, ACTOR_SELF, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorYaw, ACTOR_SELF, LVar0)
            EndThread
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3C000A)
            Wait(25)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_omo_groove_guy_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_groove_guy_EVS_Attack_Tackle = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3C0004)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x3C0010)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
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
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_omo_groove_guy_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x3C0010)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(UseBattleCamPreset, 2)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3C0001)
            Wait(8)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_omo_groove_guy_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_spy_guy_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3F000B)
            ExecWait(Ref(EVS_Enemy_Hit))
            Call(SetActorVar, ACTOR_SELF, 3, 1)
        CaseEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3F000B)
            ExecWait(Ref(EVS_Enemy_Hit))
            Call(SetActorVar, ACTOR_SELF, 3, 1)
            ExecWait(TTYD64_omo_spy_guy_EVS_TrySwitchWeapon)
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3F000D)
            SetConst(LVar2, 0x3F000E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Call(SetActorVar, ACTOR_SELF, 3, 1)
            ExecWait(TTYD64_omo_spy_guy_EVS_TrySwitchWeapon)
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3F000D)
            SetConst(LVar2, 0x3F000E)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3F000E)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3F000B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            Call(SetActorVar, ACTOR_SELF, 3, 1)
            ExecWait(TTYD64_omo_spy_guy_EVS_TrySwitchWeapon)
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3F000B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3F000C)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 2, LVar1)
            IfEq(LVar1, 0)
                SetConst(LVar1, 0x3F0002)
            Else
                SetConst(LVar1, 0x3F0003)
            EndIf
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 2, LVar1)
            IfEq(LVar1, 0)
                SetConst(LVar1, 0x3F0002)
            Else
                SetConst(LVar1, 0x3F0003)
            EndIf
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            ExecWait(TTYD64_omo_spy_guy_EVS_TrySwitchWeapon)
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3F000B)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3F000C)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 2, LVar1)
            IfEq(LVar1, 0)
                SetConst(LVar1, 0x3F0002)
            Else
                SetConst(LVar1, 0x3F0003)
            EndIf
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 2, LVar1)
            IfEq(LVar1, 0)
                SetConst(LVar1, 0x3F0006)
            Else
                SetConst(LVar1, 0x3F0007)
            EndIf
            SetConst(LVar2, 0x3F0011)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 2, LVar1)
            IfEq(LVar1, 0)
                SetConst(LVar1, 0x3F0006)
            Else
                SetConst(LVar1, 0x3F0007)
            EndIf
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 2, LVar1)
            IfEq(LVar1, 0)
                SetConst(LVar1, 0x3F0006)
            Else
                SetConst(LVar1, 0x3F0007)
            EndIf
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_sky_guy_EVS_Flying_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Call(func_8026E914, LVar0, LVar1)
            IfGe(LVar1, 3)
                ExecWait(b_area_omo_sky_guy_EVS_StretchBalloons)
            Else
                SetConst(LVar0, 2)
                SetConst(LVar1, 0x3D0006)
                ExecWait(Ref(EVS_Enemy_Hit))
            EndIf
        CaseEq(10)
            Call(func_8026E914, LVar0, LVar1)
            IfGe(LVar1, 3)
                ExecWait(b_area_omo_sky_guy_EVS_StretchBalloons)
                ExecWait(TTYD64_omo_sky_guy_EVS_PopBalloons)
            Else
                SetConst(LVar0, 2)
                SetConst(LVar1, 0x3D0006)
                ExecWait(Ref(EVS_Enemy_Hit))
            EndIf
        CaseEq(14)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x3D0009)
            SetConst(LVar2, 0x3D000A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x3D0009)
            SetConst(LVar2, 0x3D000A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x3D000A)
            ExecWait(b_area_omo_sky_guy_EVS_KillActor)
            Return
        CaseEq(23)
            Call(func_8026E914, LVar0, LVar1)
            IfGe(LVar1, 3)
                ExecWait(b_area_omo_sky_guy_EVS_StretchBalloons)
            Else
                SetConst(LVar0, 2)
                SetConst(LVar1, 0x3D0001)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseOrEq(25)
        CaseOrEq(31)
            Call(func_8026E914, LVar0, LVar1)
            IfGe(LVar1, 3)
                ExecWait(b_area_omo_sky_guy_EVS_StretchBalloons)
            Else
                SetConst(LVar0, 2)
                SetConst(LVar1, 0x3D0001)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x3D0006)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x3D0006)
            ExecWait(b_area_omo_sky_guy_EVS_KillActor)
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(SetAnimation, ACTOR_SELF, 2, 0x3D0003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 2, 0x3D0001)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x3D0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 0x100000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 4, 0x100000, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 5, 0x100000, 0)
            Call(SetAnimation, ACTOR_SELF, 3, 0x3D001F)
            Call(SetAnimation, ACTOR_SELF, 4, 0x3D001E)
            Call(SetAnimation, ACTOR_SELF, 5, 0x3D0020)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x3D0003)
            SetConst(LVar2, 0x3D0006)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x3D0003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x3D0007)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    ExecWait(b_area_omo_sky_guy_EVS_ResetAnimations)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_spy_guy_EVS_Attack_Slingshot = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 743)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3F0015)
    Wait(12)
    Wait(12)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3F0016)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Add(LVar1, 10)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 2, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 744)
    Call(SetPartSounds, ACTOR_SELF, 2, 2, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Loop(0)
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetPartOffset, ACTOR_SELF, 2, LVar3, LVar4, LVar5)
                    IfGt(LVar0, LVar3)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                IfEq(LVarA, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -100, 0, 0)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(14.0))
            Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.001953125))
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(15)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(GetOwnerTarget, LVar2, 0)
    Call(SetTargetActor, ACTOR_SELF, LVar2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(14.0))
    Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.001953125))
    Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, 1)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(GetPartOffset, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
            Sub(LVar0, 100)
            Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.7001953125))
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, 0, LVar2, 30, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
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
EvtScript TTYD64_omo_sky_guy_EVS_PopBalloons = {
    Call(GetLastElement, LVar0)
    Set(LVar0, 0x10000)
    IfFlag(LVar0, 0x14202)
        Call(HideHealthBar, ACTOR_SELF)
        Thread
            Wait(20)
            Call(PlaySoundAtActor, ACTOR_SELF, 737)
        EndThread
        Call(SetAnimation, ACTOR_SELF, 3, 0x3D002E)
        Call(SetAnimation, ACTOR_SELF, 4, 0x3D002D)
        Call(SetAnimation, ACTOR_SELF, 5, 0x3D002F)
        Wait(30)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 0x20001, 1)
        Call(SetPartFlagBits, ACTOR_SELF, 4, 0x20001, 1)
        Call(SetPartFlagBits, ACTOR_SELF, 5, 0x20001, 1)
        Call(SetActorVar, ACTOR_SELF, 8, 2)
        Wait(15)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetAnimation, ACTOR_SELF, 2, 0x3D0000)
        Call(PlaySoundAtActor, ACTOR_SELF, 611)
        Call(PlayEffect_impl, 16, 2, 0, LVar0, LVar1, LVar2, 24, 0, 25, 0, 0, 0, 0, 0)
        Wait(25)
        Call(SetAnimation, ACTOR_SELF, 2, 0x3D0006)
        Wait(30)
        Call(SetAnimation, ACTOR_SELF, 2, 0x3D0006)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 0)
        Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorSounds, ACTOR_SELF, 2, 769, 0)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
        Call(b_area_omo_sky_guy_StartRumbleWithParams, 120, 10)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(0.5))
        EndThread
        Call(PlaySoundAtActor, ACTOR_SELF, 8420)
        Call(ResetActorSounds, ACTOR_SELF, 2)
        Call(SetPartFlags, ACTOR_SELF, 2, 0x20005)
        Call(SetPartFlags, ACTOR_SELF, 1, 0x800004)
        Call(SetAnimation, ACTOR_SELF, 1, 0x3B0012)
        Call(PlayEffect_impl, 6, 3, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(40)
        Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
        Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo_sky_guy_EVS_Ground_TakeTurn))
        Call(BindIdle, ACTOR_SELF, Ref(b_area_omo_sky_guy_EVS_Ground_Idle))
        Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo_sky_guy_EVS_Ground_HandleEvent))
        Call(SetActorType, ACTOR_SELF, 31)
        Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
        Call(HPBarToHome, ACTOR_SELF)
        Call(ResetAllActorSounds, ACTOR_SELF)
    Else
        ExecWait(b_area_omo_sky_guy_EVS_StretchBalloons)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_spy_guy_EVS_TrySwitchWeapon = {
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(GetLastDamage, ACTOR_SELF, LVar0)
    IfEq(LVar0, 0)
        Call(SetActorVar, ACTOR_SELF, 3, 0)
        Return
    EndIf
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x35D000)
        Call(SetActorVar, ACTOR_SELF, 3, 0)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3F0002)
        CaseEq(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3F0003)
    EndSwitch
    Label(0)
    Call(GetBattleFlags, LVar0)
    IfFlag(LVar0, 256)
        Wait(1)
        Goto(0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo_spy_guy_MalletAnims))
            Call(SetAnimation, ACTOR_SELF, 1, 0x3F0017)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3F0019)
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3F0003)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 2, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo_spy_guy_SlingshotAnims))
            Call(SetAnimation, ACTOR_SELF, 1, 0x3F0018)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3F001A)
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3F0002)
    EndSwitch
    Wait(10)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_groove_guy_EVS_SummonGrooveGuy = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    ExecWait(b_area_omo_groove_guy_EVS_PerformSummonDance)
    Call(UseBattleCamPreset, 3)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SummonEnemy, Ref(TTYD64_omo_groove_guy_GrooveGuyFormation), 0)
    Set(LVarB, LVar0)
    Call(SetAnimation, LVarB, 1, 0x3C000C)
    Call(SetGoalToIndex, LVarB, LVarA)
    Call(GetGoalPos, LVarB, LVar3, LVar4, LVar5)
    Add(LVar3, 200)
    Call(SetActorPos, LVarB, LVar3, LVar4, LVar5)
    Thread
        Set(LVar6, 0)
        Loop(50)
            Add(LVar6, 30)
            Mod(LVar6, 360)
            Call(SetActorYaw, LVarB, LVar6)
            Wait(1)
        EndLoop
        Call(SetActorYaw, LVarB, 0)
    EndThread
    Call(SetActorSounds, LVarB, 0, 0, 0)
    Thread
        Loop(2)
            Call(PlaySoundAtActor, LVarB, 738)
            Wait(25)
        EndLoop
    EndThread
    Call(SetActorSpeed, LVarB, Float(4.0))
    Call(RunToGoal, LVarB, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8435)
    Call(SetAnimation, LVarB, 1, 0x3C000A)
    Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
    Call(ForceHomePos, LVarB, LVar0, LVar1, LVar2)
    Wait(25)
    Call(SetAnimation, LVarB, 1, 0x3C0001)
    Call(HPBarToHome, LVarB)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetActorVar, LVarB, 0, 1)
        CaseEq(1)
            Call(SetActorVar, LVarB, 0, 2)
    EndSwitch
    Return
    End
};
// clang-format on

Battle TTYD64_omo_Formations[] = {
    { .name = "BKx\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo_Formation_00,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "BJx\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo_Formation_01,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "MD\215x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo_Formation_02,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "MD\215x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_03,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\202\202x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo_Formation_04,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\177i\212x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo_Formation_05,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "BK,KDuOx\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_06,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "BJ,\300\363\267\363\260,KDuO",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_07,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "MD\215,\263\336\363\311,KDuO",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_08,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "MD\215,\177i\212,BK,BJ",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_omo_Formation_09,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\202\202,\325\241\244\242,KDuO",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_0A,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\202\202,\300\363\267\363\260,KDuOx\022",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_omo_Formation_0B,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\177i\212,\320\353\374\363,KDuO",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_0C,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\320\353\374\363x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo_Formation_0D,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\320\353\374\363,MD\215",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo_Formation_0E,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\320\353\374\363x\022,MD\215",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_0F,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\320\353\374\363,KDuO",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo_Formation_10,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\320\353\374\363x\022,\263\336\363\311",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_11,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\320\353\374\363,\177i\212,KDuO",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_12,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\320\353\374\363,\177i\212,KDuOx\022",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_omo_Formation_13,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\320\353\374\363,\300\363\267\363\260,KDuO",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_14,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\263\336\363\311x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo_Formation_15,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\263\336\363\311,\325\241\244\242",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo_Formation_16,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\263\336\363\311,KDuO",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo_Formation_17,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\263\336\363\311x\022,KDuO",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_18,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\263\336\363\311x\023,KDuO",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_omo_Formation_19,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\263\336\363\311x\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_omo_Formation_1A,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\263\336\363\311,\325\241\244\242,\300\363\267\363\260,KDuO",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_omo_Formation_1B,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\325\241\244\242x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo_Formation_1C,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\325\241\244\242x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_1D,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\325\241\244\242,KDuO",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo_Formation_1E,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\325\241\244\242x\022,KDuO",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_1F,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\325\241\244\242x\022,KDuOx\022",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_omo_Formation_20,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\325\241\244\242,\300\363\267\363\260,\325\241\244\242",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_21,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\325\241\244\242,\263\336\363\311,\300\363\267\363\260",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_22,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\325\241\244\242,\300\363\267\363\260,KDuOx2",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_omo_Formation_23,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\325\241\244\242x2,\263\336\363\311",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_24,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\300\363\267\363\260x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_omo_Formation_25,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\300\363\267\363\260x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_26,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\300\363\267\363\260,KDuOx\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_27,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\300\363\267\363\260x\022,KDuO",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_28,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\300\363\267\363\260x\022,KDuOx\022",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_omo_Formation_29,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\300\363\267\363\260x\022,\325\241\244\242\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_2A,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\300\363\267\363\260,BJ,\320\353\374\363",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo_Formation_2B,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    { .name = "\326\351\303\257",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_omo_Formation_2C,
      .stage = &b_area_omo_omo_04,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_omo_groove_guy_EVS_TakeTurn = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 2)
        Call(RandInt, 100, LVar0)
        IfLt(LVar0, 60)
            Call(GetStatusFlags, 0, LVar0)
            IfFlag(LVar0, 0x40000)
                ExecWait(TTYD64_omo_groove_guy_EVS_Attack_Tackle)
            Else
                ExecWait(TTYD64_omo_groove_guy_EVS_Attack_SleepySpin)
            EndIf
        Else
            ExecWait(TTYD64_omo_groove_guy_EVS_Attack_Tackle)
        EndIf
        Return
    EndIf
    ExecWait(b_area_omo_groove_guy_EVS_GetAvailableColumn)
    IfEq(LVarA, -1)
        Call(RandInt, 100, LVar0)
        IfLt(LVar0, 60)
            Call(GetStatusFlags, 0, LVar0)
            IfFlag(LVar0, 0x40000)
                ExecWait(TTYD64_omo_groove_guy_EVS_Attack_Tackle)
            Else
                ExecWait(TTYD64_omo_groove_guy_EVS_Attack_SleepySpin)
            EndIf
        Else
            ExecWait(TTYD64_omo_groove_guy_EVS_Attack_Tackle)
        EndIf
        Return
    EndIf
    ExecWait(b_area_omo_groove_guy_EVS_CountActiveSummoners)
    Switch(LVar9)
        CaseEq(1)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 300)
                ExecWait(TTYD64_omo_groove_guy_EVS_RandomSummon)
                Return
            EndIf
        CaseEq(2)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 150)
                ExecWait(TTYD64_omo_groove_guy_EVS_RandomSummon)
                Return
            EndIf
        CaseEq(3)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 100)
                ExecWait(TTYD64_omo_groove_guy_EVS_RandomSummon)
                Return
            EndIf
    EndSwitch
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 60)
        Call(GetStatusFlags, 0, LVar0)
        IfFlag(LVar0, 0x40000)
            ExecWait(TTYD64_omo_groove_guy_EVS_Attack_Tackle)
        Else
            ExecWait(TTYD64_omo_groove_guy_EVS_Attack_SleepySpin)
        EndIf
    Else
        ExecWait(TTYD64_omo_groove_guy_EVS_Attack_Tackle)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_spy_guy_EVS_ManageItemMotion = {
    Label(0)
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    Switch(LVarA)
        CaseEq(0)
        CaseEq(1)
            Call(GetOwnerTarget, LVar6, 0)
            Call(GetActorPos, LVar6, LVar1, LVar2, LVar3)
            Set(LVar2, 0)
            Sub(LVar3, 1)
            Call(b_area_omo_spy_guy_DisableRandomAbility, LVar4, LVar5)
            Call(MakeItemEntity, LVar4, LVar1, LVar2, LVar3, 1, 0)
            Call(SetActorVar, ACTOR_SELF, 1, LVar0)
            Add(LVar1, 30)
            Call(b_area_omo_spy_guy_ItemEntityJumpToPos, LVar0, LVar1, LVar2, LVar3, 20, Float(1.0))
            Add(LVar1, 20)
            Call(b_area_omo_spy_guy_ItemEntityJumpToPos, LVar0, LVar1, LVar2, LVar3, 10, Float(1.0))
            Add(LVar1, 10)
            Call(b_area_omo_spy_guy_ItemEntityJumpToPos, LVar0, LVar1, LVar2, LVar3, 5, Float(1.0))
            Call(SetActorVar, ACTOR_SELF, 0, 0)
        CaseEq(2)
            Call(ShowMessageBox, LVar5, 60)
            Sub(LVar1, 150)
            Call(b_area_omo_spy_guy_ItemEntityJumpToPos, LVar0, LVar1, LVar2, LVar3, 30, Float(1.0))
            Call(RemoveItemEntity, LVar0)
            Call(SetActorVar, ACTOR_SELF, 0, 3)
            Return
    EndSwitch
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_groove_guy_EVS_SummonMediGuy = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    ExecWait(b_area_omo_groove_guy_EVS_PerformSummonDance)
    Call(SummonEnemy, Ref(TTYD64_omo_groove_guy_MediGuyFormation), 0)
    Set(LVarB, LVar0)
    Call(SetAnimation, LVarB, 1, 0x400005)
    Add(LVarA, 4)
    Call(SetGoalToIndex, LVarB, LVarA)
    Call(GetGoalPos, LVarB, LVar3, LVar4, LVar5)
    Set(LVar0, 200)
    Set(LVar1, LVar4)
    Set(LVar2, LVar5)
    Call(SetActorPos, LVarB, LVar0, LVar1, LVar2)
    Call(SetActorSounds, LVarB, 0, 896, 0)
    Call(UseBattleCamPreset, 3)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetActorSpeed, LVarB, Float(4.0))
    Call(RunToGoal, LVarB, 0, 0)
    Call(SetAnimation, LVarB, 1, 0x400001)
    Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
    Call(ForceHomePos, LVarB, LVar0, LVar1, LVar2)
    Call(HPBarToHome, LVarB)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_groove_guy_EVS_SummonShyGuy = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    ExecWait(b_area_omo_groove_guy_EVS_PerformSummonDance)
    Call(SummonEnemy, Ref(TTYD64_omo_groove_guy_ShyGuyFormation), 0)
    Set(LVarB, LVar0)
    Set(LVar0, 200)
    Set(LVar1, 0)
    Set(LVar2, 0)
    Call(SetActorPos, LVarB, LVar0, LVar1, LVar2)
    Call(SetAnimation, LVarB, 1, 0x3B0004)
    Call(UseBattleCamPreset, 3)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetGoalToIndex, LVarB, LVarA)
    Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
    Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
    Call(SetActorSpeed, LVarB, Float(4.0))
    Call(RunToGoal, LVarB, 0, 0)
    Call(SetAnimation, LVarB, 1, 0x3B0001)
    Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
    Call(ForceHomePos, LVarB, LVar0, LVar1, LVar2)
    Call(HPBarToHome, LVarB)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_sky_guy_EVS_Flying_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo_sky_guy_EVS_Flying_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo_sky_guy_EVS_Flying_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_omo_sky_guy_EVS_Flying_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 0x100001, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 4, 0x100001, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 5, 0x100001, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 5)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetPartTargetFlagBits, ACTOR_SELF, 3, 4, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_omo_01_EVS_PreBattle = {
    Call(SetSpriteShading, -1)
    Call(SetCamBGColor, 1, 0, 0, 0)
    Thread
        SetF(LVar0, Float(0.0))
        SetF(LVar1, Float(0.0))
        Loop(0)
            Call(RotateModel, 23, LVar1, 0, 0, 1)
            Call(RotateModel, 21, LVar0, 0, 0, 1)
            SubF(LVar0, Float(0.599609375))
            SubF(LVar1, Float(7.2001953125))
            Call(ClampAngleFloat, LVar0)
            Call(ClampAngleFloat, LVar1)
            Wait(1)
        EndLoop
    EndThread
    Exec(b_area_omo_omo_01_EVS_UpdateRockingHorse)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_spy_guy_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo_spy_guy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo_spy_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_omo_spy_guy_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 2, 1)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(GetInstigatorValue, ACTOR_SELF, LVar0)
    IfNe(LVar0, 0)
        Call(SetActorVar, ACTOR_SELF, 2, 0)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo_spy_guy_SlingshotAnims))
        Call(SetAnimation, ACTOR_SELF, 1, 0x3F0002)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_spy_guy_EVS_TakeTurn = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 2, 0)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo_spy_guy_SlingshotAnims))
        Call(SetAnimation, ACTOR_SELF, 1, 0x3F0002)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_omo_spy_guy_EVS_Attack_Slingshot)
        CaseEq(1)
            ExecWait(TTYD64_omo_spy_guy_EVS_Attack_Mallet)
    EndSwitch
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_omo_sky_guy_ActorParts[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo_sky_guy_GroundAnims,
        .defenseTable = b_area_omo_sky_guy_GroundDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo_sky_guy_DefaultAnims,
        .defenseTable = b_area_omo_sky_guy_FlyingDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x100003,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 50 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo_sky_guy_YellowBalloonAnims,
        .defenseTable = b_area_omo_sky_guy_FlyingDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0x29007E,
    },
    {
        .flags = 0x122003,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo_sky_guy_RedBalloonAnims,
        .defenseTable = b_area_omo_sky_guy_FlyingDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x122003,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo_sky_guy_BlueBalloonAnims,
        .defenseTable = b_area_omo_sky_guy_FlyingDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 6,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = b_area_omo_sky_guy_StoneAnims,
        .defenseTable = b_area_omo_sky_guy_FlyingDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_omo_groove_guy_EVS_RandomSummon = {
    Call(UseBattleCamPreset, 11)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(RandInt, 2, LVar1)
    Switch(LVar1)
        CaseEq(0)
            ExecWait(TTYD64_omo_groove_guy_EVS_SummonShyGuy)
        CaseEq(1)
            ExecWait(TTYD64_omo_groove_guy_EVS_SummonGrooveGuy)
        CaseEq(2)
            ExecWait(TTYD64_omo_groove_guy_EVS_SummonMediGuy)
    EndSwitch
    Call(UseBattleCamPreset, 2)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo_groove_guy_DefaultAnims))
    Return
    End
};
// clang-format on

s32 TTYD64_omo_groove_guy_StatusTable[] = {
    1,  0, 2,  0, 6,  70, 9,  50, 7,  70, 4,  50, 3,  100, 11, 50, 5,  90, 10, 75, 8, 80,
    31, 0, 32, 0, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0,   38, 1,  39, 0,  41, 0,  0,
};

s32 TTYD64_omo_red_shy_guy_StatusTable[] = {
    1,  0, 2,  0, 6,  70, 9,  50, 7,  70, 4,  90, 3,  100, 11, 50, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0,   38, 1,  39, 0,  41, 0,  0,
};

s32 TTYD64_omo_green_shy_guy_StatusTable[] = {
    1,  0, 2,  0, 6,  70, 9,  50, 7,  70, 4,  90, 3,  100, 11, 50, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0,   38, 1,  39, 0,  41, 0,  0,
};

s32 TTYD64_omo_sky_guy_FlyingStatusTable[] = {
    1,  0, 2,  0, 6,  70, 9,  50, 7,  70, 4,  90, 3,  100, 11, 50, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 1,  35, 0,  33, 0,   38, 1,  39, 0,  41, 0,  0,
};

s32 TTYD64_omo_green_shy_guy_StatusTable_8022DFB8[] = {
    1,  0, 2,  0, 6,  70, 9,  50, 7,  70, 4,  90, 3,  100, 11, 50, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0,   38, 1,  39, 0,  41, 0,  0,
};

s32 TTYD64_omo_green_shy_guy_StatusTable_8022E064[] = {
    1,  0, 2,  0, 6,  70, 9,  50, 7,  70, 4,  90, 3,  100, 11, 50, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0,   38, 1,  39, 0,  41, 0,  0,
};

s32 TTYD64_omo_spy_guy_StatusTable[] = {
    1,  0, 2,  0, 6,  70, 9,  50, 7,  70, 4,  80, 3,  100, 11, 0, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0,   38, 1, 39, 0,  41, 0,  0,
};

s32 TTYD64_omo_green_shy_guy_StatusTable_8022E1BC[] = {
    1,  0, 2,  0, 6,  70, 9,  50, 7,  70, 4,  90, 3,  100, 11, 50, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0,   38, 1,  39, 0,  41, 0,  0,
};

// clang-format off
EvtScript TTYD64_omo_medi_guy_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo_medi_guy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo_medi_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo_medi_guy_EVS_HandleEvent))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 5)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_medi_guy_EVS_TakeTurn = {
    ExecWait(b_area_omo_medi_guy_EVS_FindInjuredActor)
    IfEq(LVar0, -1)
        ExecWait(TTYD64_omo_medi_guy_EVS_Attack_Swoop)
    Else
        Call(RandInt, 1000, LVarA)
        IfLt(LVarA, 600)
            ExecWait(b_area_omo_medi_guy_EVS_Move_HealOne)
        Else
            ExecWait(TTYD64_omo_medi_guy_EVS_Attack_Swoop)
        EndIf
    EndIf
    Return
    End
};
// clang-format on

FormationRow TTYD64_omo_Formation_0B[] = {
    { .actor = &TTYD64_omo_green_shy_guy_802306BC,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_13[] = {
    { .actor = &TTYD64_omo_sky_guy,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SKYGUY },
    { .actor = &TTYD64_omo_green_shy_guy_80230644,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_19[] = {
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_09[] = {
    { .actor = &TTYD64_omo_green_shy_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_green_shy_guy_80230644,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_red_shy_guy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_green_shy_guy_80230554,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
};

FormationRow TTYD64_omo_Formation_1A[] = {
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
};

FormationRow TTYD64_omo_Formation_1B[] = {
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_23[] = {
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_20[] = {
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_29[] = {
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

// clang-format off
EvtScript TTYD64_omo_groove_guy_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo_groove_guy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo_groove_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo_groove_guy_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_anti_guy_EVS_TakeTurn = {
    Call(RandInt, 1, LVar0)
    IfEq(LVar0, 0)
        ExecWait(TTYD64_omo_anti_guy_EVS_Attack_Tackle)
    Else
        ExecWait(TTYD64_omo_anti_guy_EVS_Attack_Vault)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_green_shy_guy_EVS_TakeTurn = {
    Call(RandInt, 1, LVar0)
    IfEq(LVar0, 0)
        ExecWait(TTYD64_omo_green_shy_guy_EVS_Attack_Tackle_80221C40)
    Else
        ExecWait(TTYD64_omo_green_shy_guy_EVS_Attack_Vault_8021BB4C)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_green_shy_guy_EVS_TakeTurn_8022EEF8 = {
    Call(RandInt, 1, LVar0)
    IfEq(LVar0, 0)
        ExecWait(TTYD64_omo_green_shy_guy_EVS_Attack_Tackle)
    Else
        ExecWait(TTYD64_omo_green_shy_guy_EVS_Attack_Vault)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_green_shy_guy_EVS_TakeTurn_8022EF54 = {
    Call(RandInt, 1, LVar0)
    IfEq(LVar0, 0)
        ExecWait(TTYD64_omo_green_shy_guy_EVS_Attack_Tackle_80222364)
    Else
        ExecWait(TTYD64_omo_green_shy_guy_EVS_Attack_Vault_8021AF70)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_green_shy_guy_EVS_TakeTurn_8022EFB0 = {
    Call(RandInt, 1, LVar0)
    IfEq(LVar0, 0)
        ExecWait(TTYD64_omo_green_shy_guy_EVS_Attack_Tackle_80220DF8)
    Else
        ExecWait(TTYD64_omo_green_shy_guy_EVS_Attack_Vault_8021C728)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_red_shy_guy_EVS_TakeTurn = {
    Call(RandInt, 1, LVar0)
    IfEq(LVar0, 0)
        ExecWait(TTYD64_omo_red_shy_guy_EVS_Attack_Tackle)
    Else
        ExecWait(TTYD64_omo_red_shy_guy_EVS_Attack_Vault)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_sky_guy_EVS_Ground_TakeTurn = {
    Call(RandInt, 1, LVar0)
    IfEq(LVar0, 0)
        ExecWait(TTYD64_omo_sky_guy_EVS_Attack_Tackle)
    Else
        ExecWait(TTYD64_omo_sky_guy_EVS_Attack_Vault)
    EndIf
    Return
    End
};
// clang-format on

FormationRow TTYD64_omo_Formation_0A[] = {
    { .actor = &TTYD64_omo_green_shy_guy_802306BC,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_0C[] = {
    { .actor = &TTYD64_omo_green_shy_guy_80230644,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_sky_guy,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SKYGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_0F[] = {
    { .actor = &TTYD64_omo_sky_guy,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SKYGUY },
    { .actor = &TTYD64_omo_sky_guy,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SKYGUY },
    { .actor = &TTYD64_omo_green_shy_guy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
};

FormationRow TTYD64_omo_Formation_11[] = {
    { .actor = &TTYD64_omo_sky_guy,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SKYGUY },
    { .actor = &TTYD64_omo_sky_guy,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SKYGUY },
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
};

FormationRow TTYD64_omo_Formation_12[] = {
    { .actor = &TTYD64_omo_sky_guy,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SKYGUY },
    { .actor = &TTYD64_omo_green_shy_guy_80230644,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_14[] = {
    { .actor = &TTYD64_omo_sky_guy,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SKYGUY },
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_18[] = {
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_03[] = {
    { .actor = &TTYD64_omo_green_shy_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_green_shy_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_green_shy_guy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
};

FormationRow TTYD64_omo_Formation_08[] = {
    { .actor = &TTYD64_omo_green_shy_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_06[] = {
    { .actor = &TTYD64_omo_red_shy_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_07[] = {
    { .actor = &TTYD64_omo_green_shy_guy_80230554,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_2B[] = {
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_green_shy_guy_80230554,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_sky_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SKYGUY },
};

FormationRow TTYD64_omo_Formation_2A[] = {
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
};

FormationRow TTYD64_omo_Formation_1F[] = {
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_1D[] = {
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
};

FormationRow TTYD64_omo_Formation_22[] = {
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
};

FormationRow TTYD64_omo_Formation_21[] = {
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
};

FormationRow TTYD64_omo_Formation_26[] = {
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
};

FormationRow TTYD64_omo_Formation_27[] = {
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_24[] = {
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
};

FormationRow TTYD64_omo_Formation_28[] = {
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

StageListRow TTYD64_omo_Stages[] = {
    { .name = "omo_01", .stage = &TTYD64_omo_omo_01 },   { .name = "omo_02", .stage = &b_area_omo_omo_02 },
    { .name = "omo_03", .stage = &b_area_omo_omo_03 },   { .name = "omo_03b", .stage = &b_area_omo_omo_03b },
    { .name = "omo_04", .stage = &b_area_omo_omo_04 },   { .name = "omo_05", .stage = &b_area_omo_omo_05 },
    { .name = "omo_05b", .stage = &b_area_omo_omo_05b }, { .name = "omo_06", .stage = &b_area_omo_omo_06 },
    { .name = "omo_07", .stage = &b_area_omo_omo_07 },   {},
};

s32 TTYD64_omo_green_shy_guy_DefaultAnims[] = {
    1,  0x3B0201, 7, 0x3B0200, 6, 0x3B0212, 9, 0x3B0201, 8, 0x3B0200,
    11, 0x3B0201, 5, 0x3B0200, 4, 0x3B0213, 3, 0x3B0213, 0,
};

s32 TTYD64_omo_red_shy_guy_DefaultAnims[] = {
    1,  0x3B0001, 7, 0x3B0000, 6, 0x3B0012, 9, 0x3B0001, 8, 0x3B0000,
    11, 0x3B0001, 5, 0x3B0000, 4, 0x3B0013, 3, 0x3B0013, 0,
};

// clang-format off
EvtScript TTYD64_omo_green_shy_guy_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo_green_shy_guy_EVS_TakeTurn_8022EF54))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo_green_shy_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo_yellow_shy_guy_EVS_HandleEvent))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_red_shy_guy_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo_red_shy_guy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo_red_shy_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo_red_shy_guy_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_omo_sky_guy_YellowBalloonAnims[] = {
    1,  0x3D0010, 7, 0x3D000D, 6, 0x3D0019, 9, 0x3D0010, 8, 0x3D000D,
    11, 0x3D0010, 5, 0x3D000D, 4, 0x3D0010, 3, 0x3D0010, 0,
};

s32 TTYD64_omo_spy_guy_SlingshotAnims[] = {
    1,  0x3F0002, 7, 0x3F0000, 6, 0x3F000F, 9, 0x3F0002, 8, 0x3F0000,
    11, 0x3F0002, 5, 0x3F0000, 4, 0x3F0012, 3, 0x3F0012, 0,
};

s32 TTYD64_omo_sky_guy_RedBalloonAnims[] = {
    1,  0x3D000F, 7, 0x3D000C, 6, 0x3D0018, 9, 0x3D000F, 8, 0x3D000C,
    11, 0x3D000F, 5, 0x3D000C, 4, 0x3D000F, 3, 0x3D000F, 0,
};

// clang-format off
EvtScript TTYD64_omo_pyro_guy_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo_pyro_guy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo_pyro_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo_pyro_guy_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_omo_yellow_shy_guy_DefaultAnims[] = {
    1,  0x3B0401, 7, 0x3B0400, 6, 0x3B0412, 9, 0x3B0401, 8, 0x3B0400,
    11, 0x3B0401, 5, 0x3B0400, 4, 0x3B0413, 3, 0x3B0413, 0,
};

s32 TTYD64_omo_sky_guy_DefaultAnims[] = {
    1,  0x3D0001, 7, 0x3D0000, 6, 0x3D0004, 9, 0x3D0001, 8, 0x3D0000,
    11, 0x3D0001, 5, 0x3D0000, 4, 0x3D0005, 3, 0x3D0005, 0,
};

s32 TTYD64_omo_medi_guy_DefaultAnims[] = {
    1,  0x400001, 7, 0x400000, 6, 0x400004, 9, 0x400001, 8, 0x400000,
    11, 0x400001, 5, 0x400000, 4, 0x40000A, 3, 0x40000A, 0,
};

s32 TTYD64_omo_pink_shy_guy_DefaultAnims[] = {
    1,  0x3B0301, 7, 0x3B0300, 6, 0x3B0312, 9, 0x3B0301, 8, 0x3B0300,
    11, 0x3B0301, 5, 0x3B0300, 4, 0x3B0313, 3, 0x3B0313, 0,
};

s32 TTYD64_omo_blue_shy_guy_DefaultAnims[] = {
    1,  0x3B0101, 7, 0x3B0100, 6, 0x3B0112, 9, 0x3B0101, 8, 0x3B0100,
    11, 0x3B0101, 5, 0x3B0100, 4, 0x3B0113, 3, 0x3B0113, 0,
};

s32 TTYD64_omo_spy_guy_MalletAnims[] = {
    1,  0x3F0003, 7, 0x3F0001, 6, 0x3F000F, 9, 0x3F0003, 8, 0x3F0001,
    11, 0x3F0003, 5, 0x3F0001, 4, 0x3F0012, 3, 0x3F0012, 0,
};

// clang-format off
EvtScript TTYD64_omo_green_shy_guy_EVS_Init_8022FD20 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo_green_shy_guy_EVS_TakeTurn_8022EEF8))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo_green_shy_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo_pink_shy_guy_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_omo_groove_guy_DefaultAnims[] = {
    1,  0x3C0001, 7, 0x3C0000, 6, 0x3C0006, 9, 0x3C0001, 8, 0x3C0000,
    11, 0x3C0001, 5, 0x3C0000, 4, 0x3C0007, 3, 0x3C0007, 0,
};

// clang-format off
EvtScript TTYD64_omo_anti_guy_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo_anti_guy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo_anti_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo_anti_guy_EVS_HandleEvent))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_green_shy_guy_EVS_Init_8022FE04 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo_green_shy_guy_EVS_TakeTurn_8022EFB0))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo_green_shy_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo_blue_shy_guy_EVS_HandleEvent))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo_green_shy_guy_EVS_Init_8022FE50 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo_green_shy_guy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo_green_shy_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo_green_shy_guy_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_omo_sky_guy_GroundAnims[] = {
    1,  0x3B0001, 7, 0x3B0000, 6, 0x3B0012, 9, 0x3B0001, 8, 0x3B0000,
    11, 0x3B0001, 5, 0x3B0000, 4, 0x3B0013, 3, 0x3B0013, 0,
};

s32 TTYD64_omo_sky_guy_BlueBalloonAnims[] = {
    1,  0x3D0011, 7, 0x3D000E, 6, 0x3D001A, 9, 0x3D0011, 8, 0x3D000E,
    11, 0x3D0011, 5, 0x3D000E, 4, 0x3D0011, 3, 0x3D0011, 0,
};

s32 TTYD64_omo_pyro_guy_DefaultAnims[] = {
    1,  0x3E0001, 7, 0x3E0000, 6, 0x3E0007, 9, 0x3E0001, 8, 0x3E0000,
    11, 0x3E0001, 5, 0x3E0000, 4, 0x3E0008, 3, 0x3E0008, 0,
};

s32 TTYD64_omo_anti_guy_DefaultAnims[] = {
    1,  0x3B0501, 7, 0x3B0500, 6, 0x3B0512, 9, 0x3B0501, 8, 0x3B0500,
    11, 0x3B0501, 5, 0x3B0500, 4, 0x3B0513, 3, 0x3B0513, 0,
};

ActorPartBlueprint TTYD64_omo_spy_guy_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 30 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo_spy_guy_MalletAnims,
        .defenseTable = b_area_omo_spy_guy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -13 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = b_area_omo_spy_guy_StoneAnims,
        .defenseTable = b_area_omo_spy_guy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_omo_Formation_0D[] = {
    { .actor = &TTYD64_omo_sky_guy,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SKYGUY },
    { .actor = &TTYD64_omo_sky_guy,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SKYGUY },
};

FormationRow TTYD64_omo_Formation_0E[] = {
    { .actor = &TTYD64_omo_sky_guy,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SKYGUY },
    { .actor = &TTYD64_omo_green_shy_guy,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
};

FormationRow TTYD64_omo_Formation_10[] = {
    { .actor = &TTYD64_omo_sky_guy,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SKYGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_15[] = {
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
};

FormationRow TTYD64_omo_Formation_16[] = {
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
};

FormationRow TTYD64_omo_Formation_17[] = {
    { .actor = &TTYD64_omo_spy_guy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_00[] = {
    { .actor = &TTYD64_omo_red_shy_guy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_red_shy_guy,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
};

FormationRow TTYD64_omo_Formation_01[] = {
    { .actor = &TTYD64_omo_green_shy_guy_80230554,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_green_shy_guy_80230554,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
};

FormationRow TTYD64_omo_Formation_04[] = {
    { .actor = &TTYD64_omo_green_shy_guy_802306BC,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_green_shy_guy_802306BC,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
};

FormationRow TTYD64_omo_Formation_05[] = {
    { .actor = &TTYD64_omo_green_shy_guy_80230644,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_green_shy_guy_80230644,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
};

FormationRow TTYD64_omo_Formation_02[] = {
    { .actor = &TTYD64_omo_green_shy_guy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_omo_green_shy_guy,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
};

FormationRow TTYD64_omo_Formation_1E[] = {
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_omo_Formation_1C[] = {
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_omo_pyro_guy,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
};

FormationRow TTYD64_omo_Formation_25[] = {
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
};

Stage TTYD64_omo_omo_01 = {
    .texture = "omo_tex",
    .shape = "omo_bt01_shape",
    .hit = "omo_bt01_hit",
    .preBattle = &TTYD64_omo_omo_01_EVS_PreBattle,
    .postBattle = &b_area_omo_omo_01_EVS_PostBattle,
    .bg = "omo_bg",
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_omo_medi_guy = {
    .flags = 0x200,
    .maxHP = 7,
    .type = 0x22,
    .level = 14,
    .partCount = 1,
    .partsData = TTYD64_omo_medi_guy_ActorParts,
    .initScript = &TTYD64_omo_medi_guy_EVS_Init,
    .statusTable = b_area_omo_medi_guy_StatusTable,
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

ActorBlueprint TTYD64_omo_green_shy_guy = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x1F,
    .level = 14,
    .partCount = 1,
    .partsData = TTYD64_omo_green_shy_guy_ActorParts_802308A8,
    .initScript = &TTYD64_omo_green_shy_guy_EVS_Init,
    .statusTable = TTYD64_omo_green_shy_guy_StatusTable_8022E1BC,
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

ActorBlueprint TTYD64_omo_green_shy_guy_80230554 = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x1F,
    .level = 14,
    .partCount = 1,
    .partsData = TTYD64_omo_green_shy_guy_ActorParts_802308CC,
    .initScript = &TTYD64_omo_green_shy_guy_EVS_Init_8022FE04,
    .statusTable = TTYD64_omo_green_shy_guy_StatusTable_8022E064,
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

ActorBlueprint TTYD64_omo_groove_guy = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x20,
    .level = 15,
    .partCount = 1,
    .partsData = TTYD64_omo_groove_guy_ActorParts,
    .initScript = &TTYD64_omo_groove_guy_EVS_Init,
    .statusTable = TTYD64_omo_groove_guy_StatusTable,
    .escapeChance = 50,
    .airLiftChance = 85,
    .hurricaneChance = 80,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 28, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_omo_pyro_guy = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x23,
    .level = 15,
    .partCount = 1,
    .partsData = TTYD64_omo_pyro_guy_ActorParts,
    .initScript = &TTYD64_omo_pyro_guy_EVS_Init,
    .statusTable = b_area_omo_pyro_guy_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 85,
    .hurricaneChance = 80,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 1,
    .size = { 28, 36 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_omo_green_shy_guy_80230644 = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x1F,
    .level = 14,
    .partCount = 1,
    .partsData = TTYD64_omo_green_shy_guy_ActorParts,
    .initScript = &TTYD64_omo_green_shy_guy_EVS_Init_8022FE50,
    .statusTable = TTYD64_omo_green_shy_guy_StatusTable,
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

ActorBlueprint TTYD64_omo_anti_guy = {
    .flags = 0x0,
    .maxHP = 50,
    .type = 0xAF,
    .level = 42,
    .partCount = 1,
    .partsData = TTYD64_omo_anti_guy_ActorParts,
    .initScript = &TTYD64_omo_anti_guy_EVS_Init,
    .statusTable = b_area_omo_anti_guy_StatusTable,
    .escapeChance = 50,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 30, 30 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_omo_red_shy_guy = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x1F,
    .level = 14,
    .partCount = 1,
    .partsData = TTYD64_omo_red_shy_guy_ActorParts,
    .initScript = &TTYD64_omo_red_shy_guy_EVS_Init,
    .statusTable = TTYD64_omo_red_shy_guy_StatusTable,
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

ActorBlueprint TTYD64_omo_green_shy_guy_802306BC = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x1F,
    .level = 14,
    .partCount = 1,
    .partsData = TTYD64_omo_green_shy_guy_ActorParts_80230818,
    .initScript = &TTYD64_omo_green_shy_guy_EVS_Init_8022FD20,
    .statusTable = TTYD64_omo_green_shy_guy_StatusTable_8022DFB8,
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

ActorBlueprint TTYD64_omo_spy_guy = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x24,
    .level = 15,
    .partCount = 2,
    .partsData = TTYD64_omo_spy_guy_ActorParts,
    .initScript = &TTYD64_omo_spy_guy_EVS_Init,
    .statusTable = TTYD64_omo_spy_guy_StatusTable,
    .escapeChance = 50,
    .airLiftChance = 85,
    .hurricaneChance = 80,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 1,
    .size = { 32, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_omo_sky_guy = {
    .flags = 0x200,
    .maxHP = 7,
    .type = 0x21,
    .level = 14,
    .partCount = 6,
    .partsData = TTYD64_omo_sky_guy_ActorParts,
    .initScript = &TTYD64_omo_sky_guy_EVS_Flying_Init,
    .statusTable = TTYD64_omo_sky_guy_FlyingStatusTable,
    .escapeChance = 50,
    .airLiftChance = 90,
    .hurricaneChance = 90,
    .spookChance = 80,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 28, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorPartBlueprint TTYD64_omo_green_shy_guy_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo_green_shy_guy_DefaultAnims,
        .defenseTable = b_area_omo_sky_guy_GroundDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_omo_groove_guy_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo_groove_guy_DefaultAnims,
        .defenseTable = b_area_omo_spy_guy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_omo_green_shy_guy_ActorParts_80230818[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo_pink_shy_guy_DefaultAnims,
        .defenseTable = b_area_omo_spy_guy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_omo_medi_guy_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 38 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo_medi_guy_DefaultAnims,
        .defenseTable = b_area_omo_medi_guy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -5 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_omo_red_shy_guy_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo_red_shy_guy_DefaultAnims,
        .defenseTable = b_area_omo_red_shy_guy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_omo_pyro_guy_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo_pyro_guy_DefaultAnims,
        .defenseTable = b_area_omo_pyro_guy_DefenseTable,
        .eventFlags = 0x2,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_omo_green_shy_guy_ActorParts_802308A8[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo_yellow_shy_guy_DefaultAnims,
        .defenseTable = b_area_omo_spy_guy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_omo_green_shy_guy_ActorParts_802308CC[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo_blue_shy_guy_DefaultAnims,
        .defenseTable = b_area_omo_sky_guy_FlyingDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_omo_anti_guy_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_omo_anti_guy_DefaultAnims,
        .defenseTable = b_area_omo_anti_guy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_omo_groove_guy_GrooveGuyFormation[] = {
    { .actor = &TTYD64_omo_groove_guy,
      .home = { .vec = &b_area_omo_groove_guy_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_omo_Formation_2C[] = {
    { .actor = &TTYD64_omo_anti_guy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_omo_groove_guy_MediGuyFormation[] = {
    { .actor = &TTYD64_omo_medi_guy,
      .home = { .vec = &b_area_omo_groove_guy_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_omo_groove_guy_ShyGuyFormation[] = {
    { .actor = &TTYD64_omo_red_shy_guy,
      .home = { .vec = &b_area_omo_groove_guy_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

void TTYD64_InstallBattles_omo(void) {
    Mod_SetBattleList("TTYD64", 16, TTYD64_omo_Formations);
    Mod_SetStageList("TTYD64", 16, TTYD64_omo_Stages);
}
