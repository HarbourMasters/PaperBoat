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

API_CALLABLE(action_command_stop_leech_init);
API_CALLABLE(action_command_stop_leech_start);
API_CALLABLE(b_area_pra_gray_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_pra_gray_magikoopa_ShrinkActor);
API_CALLABLE(b_area_pra_green_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_pra_green_magikoopa_ShrinkActor);
API_CALLABLE(b_area_pra_red_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_pra_red_magikoopa_ShrinkActor);
API_CALLABLE(b_area_pra_swoopula_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_pra_swoopula_SpawnDrainHealthContinueFX);
API_CALLABLE(b_area_pra_swoopula_SpawnDrainHealthStartFX);
API_CALLABLE(b_area_pra_white_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_pra_white_magikoopa_GetActorDefense);
API_CALLABLE(b_area_pra_white_magikoopa_GetBootsHammerLevel);
API_CALLABLE(b_area_pra_white_magikoopa_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_pra_white_magikoopa_ShrinkActor);
API_CALLABLE(b_area_pra_white_magikoopa_StartRumbleWithParams);
API_CALLABLE(b_area_pra_yellow_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_pra_yellow_magikoopa_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_pra_yellow_magikoopa_ShrinkActor);
API_CALLABLE(b_area_pra_yellow_magikoopa_StartRumbleWithParams);
extern s32 b_area_pra_albino_dino_DefenseTable[];
extern EvtScript b_area_pra_albino_dino_EVS_AddWalkQuakeFX;
extern EvtScript b_area_pra_albino_dino_EVS_HandleEvent;
extern EvtScript b_area_pra_albino_dino_EVS_Idle;
extern EvtScript b_area_pra_albino_dino_EVS_ReturnHome;
extern s32 b_area_pra_albino_dino_StatusTable[];
extern s32 b_area_pra_gray_magikoopa_DefenseTable[];
extern EvtScript b_area_pra_gray_magikoopa_EVS_Flee;
extern EvtScript b_area_pra_gray_magikoopa_EVS_HandleEvent;
extern EvtScript b_area_pra_gray_magikoopa_EVS_Idle;
extern s32 b_area_pra_green_magikoopa_DefenseTable[];
extern EvtScript b_area_pra_green_magikoopa_EVS_Flee;
extern EvtScript b_area_pra_green_magikoopa_EVS_HandleEvent;
extern EvtScript b_area_pra_green_magikoopa_EVS_Idle;
extern Vec3i b_area_pra_pos_magikoopa;
extern u8 b_area_pra_pos_swoopula_2[];
extern u8 b_area_pra_pos_swoopula_3[];
extern Stage b_area_pra_pra_01;
extern s32 b_area_pra_red_magikoopa_DefenseTable[];
extern EvtScript b_area_pra_red_magikoopa_EVS_Flee;
extern EvtScript b_area_pra_red_magikoopa_EVS_HandleEvent;
extern EvtScript b_area_pra_red_magikoopa_EVS_Idle;
extern s32 b_area_pra_red_magikoopa_StatusTable[];
extern s32 b_area_pra_swoopula_DefenseTable[];
extern EvtScript b_area_pra_swoopula_EVS_Idle;
extern s32 b_area_pra_swoopula_StatusTable[];
extern s32 b_area_pra_white_clubba_DefenseTable[];
extern EvtScript b_area_pra_white_clubba_EVS_HandleEvent;
extern EvtScript b_area_pra_white_clubba_EVS_Idle;
extern s32 b_area_pra_white_clubba_StatusTable[];
extern s32 b_area_pra_white_magikoopa_DefenseTable_80223B20[];
extern s32 b_area_pra_white_magikoopa_DefenseTable_80223B2C[];
extern EvtScript b_area_pra_white_magikoopa_EVS_Flee;
extern EvtScript b_area_pra_white_magikoopa_EVS_HandleEvent_Ground;
extern EvtScript b_area_pra_white_magikoopa_EVS_Idle;
extern EvtScript b_area_pra_white_magikoopa_EVS_KnockDownCheck;
extern s32 b_area_pra_white_magikoopa_IdleAnimations_80223E08[];
extern s32 b_area_pra_yellow_magikoopa_BroomAnims[];
extern s32 b_area_pra_yellow_magikoopa_DefenseTable[];
extern EvtScript b_area_pra_yellow_magikoopa_EVS_Flee;
extern EvtScript b_area_pra_yellow_magikoopa_EVS_HandleEvent;
extern EvtScript b_area_pra_yellow_magikoopa_EVS_Idle;
extern EvtScript b_area_pra_yellow_magikoopa_EVS_KnockDownCheck;
extern s32 b_area_pra_yellow_magikoopa_FlyingDefense[];
extern EvtScript TTYD64_imp_1F_Swoopula_Script_8021CB94_1C;
extern EvtScript TTYD64_imp_1F_Swoopula_Script_TakeTurn_8021E7B4_1C;
extern EvtScript TTYD64_imp_1F_WMagikoopa_Script_HealOne_1F;
extern EvtScript TTYD64_imp_1F_WhiteClubba_Script_TakeTurn_8021ECBC_1F;
extern EvtScript TTYD64_imp_1F_YMagikoopa_Script_TakeTurn_802274E0_1F;
extern EvtScript TTYD64_imp_1F_Swoopula_Script_HandleEvent_8021C414_1C;
extern EvtScript TTYD64_imp_1F_GRNMagikoopa_Script_TakeTurn_80224820_1F;
extern EvtScript TTYD64_imp_1F_RMagikoopa_Script_TakeTurn_80221B60_1F;
extern EvtScript TTYD64_imp_1F_GRYMagikoopa_Script_TakeTurn_8022A1F0_1F;
extern EvtScript TTYD64_imp_1F_WMagikoopa_Script_HealAll_1F;
extern EvtScript TTYD64_imp_1F_YMagikoopa_Script_YMagikoopa_WandStrike_1F;
extern EvtScript TTYD64_imp_1F_RMagikoopa_Script_RMagikoopa_WandStrike_1F;
extern EvtScript TTYD64_imp_1F_GRYMagikoopa_Script_GRYMagikoopa_WandStrike_1F;
extern EvtScript TTYD64_imp_1F_GRNMagikoopa_Script_GRNMagikoopa_WandStrike_1F;
extern EvtScript TTYD64_imp_1F_WMagikoopa_Script_WMagikoopa_WandStrike_1F;
extern EvtScript TTYD64_imp_1F_WMagikoopa_Script_HandleEvent_8022B854_1F;
extern EvtScript TTYD64_imp_1F_YMagikoopa_Script_HandleEvent_80225E84_1F;
extern EvtScript TTYD64_imp_1F_RMagikoopa_Script_RMagikoopa_ShapeSpell_1F;
extern EvtScript TTYD64_imp_1F_YMagikoopa_Script_YMagikoopa_ShapeSpell_1F;
extern EvtScript TTYD64_imp_1F_GRYMagikoopa_Script_GRYMagikoopa_ShapeSpell_1F;
extern EvtScript TTYD64_imp_1F_GRNMagikoopa_Script_GRNMagikoopa_ShapeSpell_1F;
extern EvtScript TTYD64_imp_1F_WMagikoopa_Script_WMagikoopa_ShapeSpell_1F;
extern EvtScript TTYD64_imp_1F_YMagikoopa_Script_80225888_1F;
extern EvtScript TTYD64_imp_1F_WMagikoopa_Script_8022B258_1F;
extern EvtScript TTYD64_imp_1F_AlbinoDino_Script_TakeTurn_8021E070_1F;
extern EvtScript TTYD64_imp_1F_Swoopula_Script_8021BC30_1C;
extern EvtScript TTYD64_imp_1F_Swoopula_Script_8021C0B4_1C;
extern EvtScript TTYD64_imp_1F_WMagikoopa_Script_TakeTurn_8022E2F4_1F;
extern EvtScript TTYD64_imp_1F_Swoopula_Script_8021BA70_1C;
extern Battle TTYD64_pra_FormationTable[];
extern s32 TTYD64_imp_1F_YMagikoopa_StatusTable_80224F78_1F[];
extern s32 TTYD64_imp_1F_GRYMagikoopa_StatusTable_80227C88_1F[];
extern s32 TTYD64_imp_1F_WMagikoopa_StatusTable_8022A948_1F[];
extern s32 TTYD64_imp_1F_WMagikoopa_StatusTable_8022A9F4_1F[];
extern s32 TTYD64_imp_1F_GRNMagikoopa_StatusTable_802222B8_1F[];
extern s32 TTYD64_imp_1F_YMagikoopa_StatusTable_80225024_1F[];
extern EvtScript TTYD64_imp_1F_GRNMagikoopa_Script_Init_802246D8_1F;
extern EvtScript TTYD64_imp_1F_YMagikoopa_Script_Init_80227398_1F;
extern EvtScript TTYD64_imp_1F_YMagikoopa_Script_Init_8022743C_1F;
extern EvtScript TTYD64_imp_1F_GRYMagikoopa_Script_Init_8022A0A8_1F;
extern EvtScript TTYD64_imp_1F_RMagikoopa_Script_Init_80221A18_1F;
extern FormationRow TTYD64_pra_Formation_0A[];
extern FormationRow TTYD64_pra_Formation_0D[];
extern FormationRow TTYD64_pra_Formation_0C[];
extern FormationRow TTYD64_pra_Formation_02[];
extern FormationRow TTYD64_pra_Formation_03[];
extern ActorPartBlueprint TTYD64_imp_1F_YMagikoopa_PartsTable_802250F4_1F[];
extern ActorPartBlueprint TTYD64_imp_1F_WMagikoopa_PartsTable_8022AAC4_1F[];
extern EvtScript TTYD64_imp_1F_WMagikoopa_Script_Init_8022CD68_1F;
extern EvtScript TTYD64_imp_1F_WMagikoopa_Script_Init_8022CDCC_1F;
extern EvtScript TTYD64_imp_1F_Swoopula_Script_Init_8021B9FC_1C;
extern FormationRow TTYD64_pra_Formation_01[];
extern FormationRow TTYD64_pra_Formation_08[];
extern FormationRow TTYD64_pra_Formation_09[];
extern FormationRow TTYD64_pra_Formation_06[];
extern FormationRow TTYD64_pra_Formation_07[];
extern s32 TTYD64_imp_1F_GRYMagikoopa_IdleAnimations_80227EC0_1F[];
extern s32 TTYD64_imp_1F_WMagikoopa_IdleAnimations_8022ABCC_1F[];
extern s32 TTYD64_imp_1F_Swoopula_IdleAnimations_8021B964_1C[];
extern EvtScript TTYD64_imp_1F_WhiteClubba_Script_Init_8021E750_1F;
extern EvtScript TTYD64_imp_1F_AlbinoDino_Script_Init_8021D968_1F;
extern s32 TTYD64_imp_1F_GRNMagikoopa_IdleAnimations_802224F0_1F[];
extern s32 TTYD64_imp_1F_RMagikoopa_IdleAnimations_8021F830_1F[];
extern s32 TTYD64_imp_1F_WMagikoopa_IdleAnimations_8022AB80_1F[];
extern s32 TTYD64_imp_1F_YMagikoopa_IdleAnimations_802251B0_1F[];
extern s32 TTYD64_imp_1F_AlbinoDino_IdleAnimations_8021D810_1F[];
extern s32 TTYD64_imp_1F_Swoopula_IdleAnimations_8021B9B0_1C[];
extern s32 TTYD64_imp_1F_WhiteClubba_IdleAnimations_8021E5F0_1F[];
extern s32 TTYD64_imp_1F_YMagikoopa_IdleAnimations_802251FC_1F[];
extern FormationRow TTYD64_pra_Formation_0B[];
extern FormationRow TTYD64_pra_Formation_00[];
extern FormationRow TTYD64_pra_Formation_05[];
extern ActorBlueprint TTYD64_imp_1F_GRYMagikoopa_1F_GRYMagikoopa;
extern ActorBlueprint TTYD64_imp_1F_WMagikoopa_1F_WMagikoopa;
extern ActorBlueprint TTYD64_imp_1F_AlbinoDino_1F_AlbinoDino;
extern ActorBlueprint TTYD64_imp_1F_YMagikoopa_1F_FlyingYMagikoopa;
extern ActorBlueprint TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba;
extern ActorBlueprint TTYD64_imp_1F_Swoopula_1F_Swoopula;
extern ActorBlueprint TTYD64_imp_1F_YMagikoopa_1F_YMagikoopa;
extern ActorBlueprint TTYD64_imp_1F_RMagikoopa_1F_RMagikoopa;
extern ActorBlueprint TTYD64_imp_1F_GRNMagikoopa_1F_GRNMagikoopa;
extern ActorBlueprint TTYD64_imp_1F_WMagikoopa_1F_FlyingWMagikoopa;
extern ActorPartBlueprint TTYD64_imp_1F_YMagikoopa_PartsTable_802250D0_1F[];
extern ActorPartBlueprint TTYD64_imp_1F_RMagikoopa_PartsTable_8021F750_1F[];
extern ActorPartBlueprint TTYD64_imp_1F_AlbinoDino_PartsTable_8021D91C_1F[];
extern ActorPartBlueprint TTYD64_imp_1F_WMagikoopa_PartsTable_8022AAA0_1F[];
extern ActorPartBlueprint TTYD64_imp_1F_GRYMagikoopa_PartsTable_80227DE0_1F[];
extern ActorPartBlueprint TTYD64_imp_1F_WhiteClubba_PartsTable_8021E704_1F[];
extern ActorPartBlueprint TTYD64_imp_1F_GRNMagikoopa_PartsTable_80222410_1F[];
extern ActorPartBlueprint TTYD64_imp_1F_Swoopula_PartsTable_8021B918_1C[];
extern FormationRow TTYD64_pra_Formation_0E[];
extern FormationRow TTYD64_pra_Formation_04[];
extern Vec3i TTYD64_pra_Vector3D_8022F064;
extern Vec3i TTYD64_pra_Vector3D_8022F0F8;
extern Vec3i TTYD64_pra_Vector3D_8022F058;
extern Vec3i TTYD64_pra_Vector3D_8022F0EC;
extern Vec3i TTYD64_pra_Vector3D_8022F04C;
extern Vec3i TTYD64_pra_Vector3D_8022EF9C;
extern Vec3i TTYD64_pra_Vector3D_8022EF90;
extern Vec3i TTYD64_pra_Vector3D_8022EFA8;

// clang-format off
EvtScript TTYD64_imp_1F_Swoopula_Script_8021CB94_1C = {
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
        Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Else
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
        Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
        Call(FlyToGoal, ACTOR_SELF, 0, -4, 0)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 2, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(10.0))
            Wait(15)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(TTYD64_imp_1F_Swoopula_Script_8021BA70_1C)
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
    Wait(10)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -4, -8, -15)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    IfEq(LFlag0, 1)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 0, 32)
        Return
    EndIf
    Call(GetOwnerTarget, LVar1, 0)
    Call(GetStatusFlags, LVar1, LVar0)
    IfFlag(LVar0, 0x100000)
        Wait(10)
        Loop(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
            Wait(21)
            Loop(2)
                Call(PlaySoundAtActor, ACTOR_SELF, 992)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Wait(1)
            EndLoop
            Wait(5)
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
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 2, 32)
            Wait(30)
        EndLoop
    Else
        Call(ShowMessageBox, 49, 0x7FFF)
        Call(ShowActionHud, 1)
        Call(LoadActionCommand, 6)
        Call(action_command_stop_leech_init)
        Call(SetupMashMeter, 1, 30, 0, 0, 0, 0)
        Wait(10)
        Call(SetBattleFlagBits, 0x4000, 0)
        Call(action_command_stop_leech_start, 0, 0x7FFF, 3)
        Set(LVarD, 0)
        Loop(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(GetOwnerTarget, LVar1, 0)
            Switch(LVar1)
                CaseEq(0)
                    Call(UseIdleAnimation, 0, 0)
                    Call(SetAnimation, 0, 0, 0x3000C)
                CaseEq(256)
                    Call(UseIdleAnimation, 256, 0)
                    Set(LVar0, 4)
                    Exec(TTYD64_SetPartnerAnimation_Battle)
            EndSwitch
            Loop(2)
                Call(PlaySoundAtActor, ACTOR_SELF, 992)
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
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
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
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
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
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
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
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
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
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
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
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
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
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
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
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
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
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(UseIdleAnimation, LVar1, 1)
                    BreakLoop
                EndIf
            EndLoop
            IfEq(LFlag0, 1)
                BreakLoop
            EndIf
            Set(LFlag0, 0)
            Loop(5)
                Call(GetMashActionQuality, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            IfEq(LFlag0, 1)
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(PlaySoundAtActor, ACTOR_SELF, 992)
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(GetOwnerTarget, LVar1, 0)
            Call(UseIdleAnimation, LVar1, 1)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0xA000000, 0, 0, 2, 32)
            Call(GetLastDamage, LVar1, LVar3)
            IfNe(LVar3, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8301)
                Call(PlaySoundAtActor, ACTOR_SELF, 532)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 15)
                Call(b_area_pra_swoopula_SpawnDrainHealthStartFX, LVar0, LVar1, LVar2, LVar3)
                Thread
                    Wait(15)
                    Call(PlaySoundAtActor, ACTOR_SELF, 604)
                    Call(b_area_pra_swoopula_SpawnDrainHealthContinueFX, LVar0, LVar1, LVar2, LVar3)
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
            Call(GetOwnerTarget, LVar2, 0)
            IfEq(LVar2, 0)
                Call(GetPlayerHP, LVar1)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar1)
            EndIf
            IfEq(LVar1, 0)
                Call(InterruptLeechActionCommand)
                BreakLoop
            EndIf
            Set(LFlag0, 0)
            Loop(30)
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
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    Wait(10)
    Call(YieldTurn)
    ExecWait(TTYD64_imp_1F_Swoopula_Script_8021BA70_1C)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_Swoopula_Script_TakeTurn_8021E7B4_1C = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_1F_Swoopula_Script_8021CB94_1C)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 24)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 2, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(AddGoalPos, ACTOR_SELF, -50, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
            Call(FlyToGoal, ACTOR_SELF, 0, -40, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(10.0))
            Wait(15)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(TTYD64_imp_1F_Swoopula_Script_8021BA70_1C)
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
    Wait(10)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -4, -8, -15)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340106)
    Call(FlyToGoal, ACTOR_SELF, 0, -40, 0)
    IfEq(LFlag0, 1)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 0, 32)
        Return
    EndIf
    Call(GetOwnerTarget, LVar1, 0)
    Call(GetStatusFlags, LVar1, LVar0)
    IfFlag(LVar0, 0x100000)
        Wait(10)
        Loop(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
            Wait(21)
            Loop(2)
                Call(PlaySoundAtActor, ACTOR_SELF, 992)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
                Wait(1)
                Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
                Wait(1)
            EndLoop
            Wait(5)
            Call(PlaySoundAtActor, ACTOR_SELF, 992)
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
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 2, 32)
            Wait(30)
        EndLoop
    Else
        Call(ShowMessageBox, 49, 0x7FFF)
        Call(ShowActionHud, 1)
        Call(LoadActionCommand, 6)
        Call(action_command_stop_leech_init)
        Call(SetupMashMeter, 1, 30, 0, 0, 0, 0)
        Wait(10)
        Call(SetBattleFlagBits, 0x4000, 0)
        Call(action_command_stop_leech_start, 0, 0x7FFF, 3)
        Set(LVarD, 0)
        Loop(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(GetOwnerTarget, LVar1, 0)
            Switch(LVar1)
                CaseEq(0)
                    Call(UseIdleAnimation, 0, 0)
                    Call(SetAnimation, 0, 0, 0x3000C)
                CaseEq(256)
                    Call(UseIdleAnimation, 256, 0)
                    Set(LVar0, 4)
                    Exec(TTYD64_SetPartnerAnimation_Battle)
            EndSwitch
            Call(PlaySoundAtActor, ACTOR_SELF, 992)
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
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
                Call(GetOwnerTarget, LVar1, 0)
                Call(UseIdleAnimation, LVar1, 1)
                BreakLoop
            EndIf
            Call(GetOwnerTarget, LVar1, 0)
            Call(UseIdleAnimation, LVar1, 1)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0xA000000, 0, 0, 2, 32)
            Call(GetLastDamage, LVar1, LVar3)
            IfNe(LVar3, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8301)
                Call(PlaySoundAtActor, ACTOR_SELF, 532)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 15)
                Call(b_area_pra_swoopula_SpawnDrainHealthStartFX, LVar0, LVar1, LVar2, LVar3)
                Thread
                    Wait(15)
                    Call(PlaySoundAtActor, ACTOR_SELF, 604)
                    Call(b_area_pra_swoopula_SpawnDrainHealthContinueFX, LVar0, LVar1, LVar2, LVar3)
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
            Call(GetOwnerTarget, LVar2, 0)
            IfEq(LVar2, 0)
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
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
    Wait(10)
    Call(YieldTurn)
    ExecWait(TTYD64_imp_1F_Swoopula_Script_8021BA70_1C)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_WMagikoopa_Script_HealOne_1F = {
    Set(LVar8, 0)
    Set(LVar9, 9999)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetActorHP, LVar0, LVar2)
    Call(b_area_pra_white_magikoopa_GetBootsHammerLevel, LVar3, LVar4)
    IfGt(LVar3, LVar4)
        Set(LVar3, LVar4)
    EndIf
    Call(b_area_pra_white_magikoopa_GetActorDefense, LVar0, LVar1, LVar5)
    Call(GetActorDefenseBoost, LVar0, LVar6)
    Add(LVar5, LVar6)
    Sub(LVar3, LVar5)
    Sub(LVar2, LVar3)
    Call(b_area_pra_white_magikoopa_CheckMagikoopaCastTarget, LVar0, LVarA)
    IfEq(LVarA, 0)
        Call(GetEnemyMaxHP, LVar0, LVarA)
        Call(GetActorHP, LVar0, LVarB)
        IfNe(LVarA, LVarB)
            IfLt(LVar2, LVar9)
                Set(LVar8, LVar0)
                Set(LVar9, LVar2)
            Else
                IfEq(LVar2, LVar9)
                    IfLt(LVar0, LVar8)
                        Set(LVar8, LVar0)
                        Set(LVar9, LVar2)
                    EndIf
                EndIf
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfNe(LVar8, 0)
        Goto(100)
    EndIf
    Set(LVar8, 0)
    Set(LVar9, 9999)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(1)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetActorHP, LVar0, LVar2)
    Call(b_area_pra_white_magikoopa_GetBootsHammerLevel, LVar3, LVar4)
    IfGt(LVar3, LVar4)
        Set(LVar3, LVar4)
    EndIf
    Call(b_area_pra_white_magikoopa_GetActorDefense, LVar0, LVar1, LVar5)
    Call(GetActorDefenseBoost, LVar0, LVar6)
    Add(LVar5, LVar6)
    Sub(LVar3, LVar5)
    Sub(LVar2, LVar4)
    Set(LFlag0, 0)
    Call(GetOriginalActorType, LVar0, LVarA)
    IfEq(LVarA, 71)
        Call(GetActorVar, LVar0, 8, LVarA)
        IfEq(LVarA, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetOwnerID, LVarA)
    IfNe(LVarA, LVar0)
        IfEq(LFlag0, 0)
            Call(GetEnemyMaxHP, LVar0, LVarA)
            Call(GetActorHP, LVar0, LVarB)
            IfNe(LVarA, LVarB)
                IfLt(LVar2, LVar9)
                    Set(LVar8, LVar0)
                    Set(LVar9, LVar2)
                Else
                    IfEq(LVar2, LVar9)
                        IfLt(LVar0, LVar8)
                            Set(LVar8, LVar0)
                            Set(LVar9, LVar2)
                        EndIf
                    EndIf
                EndIf
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(1)
    EndIf
    IfNe(LVar8, 0)
        Goto(100)
    EndIf
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(2)
    Call(GetOwnerTarget, LVar0, LVar1)
    Set(LFlag0, 0)
    Call(GetOriginalActorType, LVar0, LVarA)
    IfEq(LVarA, 71)
        Call(GetActorVar, LVar0, 8, LVarA)
        IfEq(LVarA, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetOwnerID, LVarA)
    IfNe(LVarA, LVar0)
        IfEq(LFlag0, 0)
            Call(GetEnemyMaxHP, LVar0, LVarA)
            Call(GetActorHP, LVar0, LVarB)
            IfNe(LVarA, LVarB)
                Set(LVar8, LVar0)
                Goto(100)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(2)
    EndIf
    Call(GetEnemyMaxHP, ACTOR_SELF, LVarA)
    Call(GetActorHP, ACTOR_SELF, LVarB)
    IfNe(LVarA, LVarB)
        Set(LVar8, -127)
        Goto(100)
    EndIf
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(3)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOwnerID, LVarA)
    IfNe(LVarA, LVar0)
        Call(GetActorFlags, ACTOR_SELF, LVar0)
        IfFlag(LVar0, 512)
            ExecWait(TTYD64_imp_1F_WMagikoopa_Script_WMagikoopa_ShapeSpell_1F)
        Else
            ExecWait(TTYD64_imp_1F_WMagikoopa_Script_WMagikoopa_WandStrike_1F)
        EndIf
        Return
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(3)
    EndIf
    ExecWait(b_area_pra_white_magikoopa_EVS_Flee)
    Return
    Label(100)
    Call(RandInt, 1000, LVar0)
    IfGt(LVar0, 750)
        Call(GetActorFlags, ACTOR_SELF, LVar0)
        IfFlag(LVar0, 512)
            ExecWait(TTYD64_imp_1F_WMagikoopa_Script_WMagikoopa_ShapeSpell_1F)
        Else
            ExecWait(TTYD64_imp_1F_WMagikoopa_Script_WMagikoopa_WandStrike_1F)
        EndIf
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560302)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570302)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560301)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570301)
    EndIf
    Wait(5)
    Thread
        Wait(5)
        Call(PlaySoundAtActor, LVar8, 8301)
        Call(PlaySoundAtActor, LVar8, 532)
        Wait(30)
        Call(PlaySoundAtActor, LVar8, 604)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(HealActor, LVar8, 8, 0)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_WhiteClubba_Script_TakeTurn_8021ECBC_1F = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 27)
        Set(LVar1, 0)
        Sub(LVar2, 6)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Wait(15)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x3A0102)
        Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetStatusFlags, ACTOR_SELF, LVar0)
        IfNotFlag(LVar0, 0x80000)
            Call(AddGoalPos, ACTOR_SELF, 27, 0, -6)
        Else
            Call(AddGoalPos, ACTOR_SELF, 10, 0, -6)
        EndIf
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x3A0101)
        Wait(10)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(PlaySoundAtActor, ACTOR_SELF, 8389)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3A0108)
            Wait(20)
            IfEq(LVar0, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                Wait(20)
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3A0102)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Goto(40)
    EndIf
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
    MulF(LVar0, Float(100.0))
    DivF(LVar0, LVar1)
    IfLt(LVar0, 30)
        Goto(50)
    EndIf
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 25)
        Goto(50)
    EndIf
    Label(40)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3A0109)
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_SELF, 8389)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3A010A)
    Wait(2)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 5, 32)
    Thread
        Call(ShakeCam, 1, 0, 10, Float(1.5))
    EndThread
    Goto(100)
    Label(50)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3A0109)
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_SELF, 8389)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3A010A)
    Wait(2)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 2, 16)
    Thread
        Call(ShakeCam, 1, 0, 10, Float(1.5))
    EndThread
    Call(GetOwnerTarget, LVar1, 0)
    IfEq(LVar1, 0)
        Call(GetActorHP, 0, LVar0)
    Else
        Call(TTYD64_GetPartnerHP_API, LVar0)
    EndIf
    IfEq(LVar0, 0)
        Goto(100)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x3A0109)
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_SELF, 8389)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3A010A)
    Wait(2)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 2, 64)
    Thread
        Call(ShakeCam, 1, 0, 10, Float(1.5))
    EndThread
    Call(GetOwnerTarget, LVar1, 0)
    IfEq(LVar1, 0)
        Call(GetActorHP, 0, LVar0)
    Else
        Call(TTYD64_GetPartnerHP_API, LVar0)
    EndIf
    IfEq(LVar0, 0)
        Goto(100)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x3A0109)
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_SELF, 8389)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3A010A)
    Wait(2)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 2, 32)
    Thread
        Call(ShakeCam, 1, 0, 10, Float(1.5))
    EndThread
    Label(100)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(19)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3A0102)
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
EvtScript TTYD64_imp_1F_YMagikoopa_Script_TakeTurn_802274E0_1F = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_pra_yellow_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
        IfEq(LVar3, 0)
            Call(GetStatusFlags, LVar0, LVar4)
            IfNotFlag(LVar4, 0x4002000)
                Set(LVar8, LVar0)
                Call(SetBattleVar, 2, LVar1)
                Goto(100)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfEq(LFlag0, 0)
        Set(LFlag0, 1)
        Call(SetBattleVar, 2, -1)
        Goto(10)
    EndIf
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_pra_yellow_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        ExecWait(TTYD64_imp_1F_YMagikoopa_Script_YMagikoopa_ShapeSpell_1F)
    Else
        ExecWait(TTYD64_imp_1F_YMagikoopa_Script_YMagikoopa_WandStrike_1F)
    EndIf
    Return
    Label(100)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560202)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570202)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 752)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560201)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570201)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Loop(4)
            Call(PlaySoundAtActor, LVar8, 978)
            Call(RandInt, 3, LVar0)
            Add(LVar0, 3)
            Wait(LVar0)
        EndLoop
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(ElectrifyActor, LVar8, 3)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_Swoopula_Script_HandleEvent_8021C414_1C = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_1F_Swoopula_Script_8021BC30_1C)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340115)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34010E)
                ExecWait(Ref(EVS_Enemy_Hit))
            EndIf
        CaseEq(10)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340115)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34010E)
                ExecWait(Ref(EVS_Enemy_Hit))
                ExecWait(TTYD64_imp_1F_Swoopula_Script_8021C0B4_1C)
            EndIf
        CaseEq(14)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340117)
                SetConst(LVar2, 0x340118)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340111)
                SetConst(LVar2, 0x340112)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                ExecWait(TTYD64_imp_1F_Swoopula_Script_8021C0B4_1C)
            EndIf
        CaseEq(36)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340117)
                SetConst(LVar2, 0x340118)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340118)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340111)
                SetConst(LVar2, 0x340112)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340112)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(47)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_ShockHit_Impl))
            Call(UseBattleCamPreset, 2)
            ExecWait(TTYD64_imp_1F_Swoopula_Script_8021BA70_1C)
        CaseEq(38)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_ShockHit_Impl))
            Thread
                Wait(30)
                Call(UseBattleCamPreset, 2)
            EndThread
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x34010C)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340115)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x340115)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34010E)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x34010E)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(56)
            Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1F_Swoopula_IdleAnimations_8021B9B0_1C))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(TTYD64_imp_1F_Swoopula_Script_8021BA70_1C)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 1)
            Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, -24, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340102)
            SetConst(LVar2, 0x340115)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_GRNMagikoopa_Script_TakeTurn_80224820_1F = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_pra_green_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
        IfEq(LVar3, 0)
            Call(GetActorDefenseBoost, LVar0, LVar4)
            IfLt(LVar4, 3)
                Set(LVar8, LVar0)
                Call(SetBattleVar, 2, LVar1)
                Goto(100)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfEq(LFlag0, 0)
        Set(LFlag0, 1)
        Call(SetBattleVar, 2, -1)
        Goto(10)
    EndIf
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_pra_green_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        ExecWait(TTYD64_imp_1F_GRNMagikoopa_Script_GRNMagikoopa_ShapeSpell_1F)
    Else
        ExecWait(TTYD64_imp_1F_GRNMagikoopa_Script_GRNMagikoopa_WandStrike_1F)
    EndIf
    Return
    Label(100)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560402)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570402)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560401)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570401)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Call(PlaySoundAtActor, LVar8, 733)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(TTYD64_BoostDefense, LVar8, 1, 3)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_RMagikoopa_Script_TakeTurn_80221B60_1F = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_pra_red_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
        IfEq(LVar3, 0)
            Call(GetActorAttackBoost, LVar0, LVar4)
            IfLt(LVar4, 3)
                Set(LVar8, LVar0)
                Call(SetBattleVar, 2, LVar1)
                Goto(100)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfEq(LFlag0, 0)
        Set(LFlag0, 1)
        Call(SetBattleVar, 2, -1)
        Goto(10)
    EndIf
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_pra_red_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        ExecWait(TTYD64_imp_1F_RMagikoopa_Script_RMagikoopa_ShapeSpell_1F)
    Else
        ExecWait(TTYD64_imp_1F_RMagikoopa_Script_RMagikoopa_WandStrike_1F)
    EndIf
    Return
    Label(100)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560102)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570102)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560101)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570101)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Call(PlaySoundAtActor, LVar8, 733)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(TTYD64_BoostAttack, LVar8, 1, 2)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_GRYMagikoopa_Script_TakeTurn_8022A1F0_1F = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_pra_gray_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
        IfEq(LVar3, 0)
            Call(GetStatusFlags, LVar0, LVar4)
            IfNotFlag(LVar4, 0x4002000)
                Set(LVar8, LVar0)
                Call(SetBattleVar, 2, LVar1)
                Goto(100)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfEq(LFlag0, 0)
        Set(LFlag0, 1)
        Call(SetBattleVar, 2, -1)
        Goto(10)
    EndIf
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_pra_gray_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        ExecWait(TTYD64_imp_1F_GRYMagikoopa_Script_GRYMagikoopa_ShapeSpell_1F)
    Else
        ExecWait(TTYD64_imp_1F_GRYMagikoopa_Script_GRYMagikoopa_WandStrike_1F)
    EndIf
    Return
    Label(100)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560502)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570502)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560501)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570501)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Call(PlaySoundAtActor, LVar8, 731)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(VanishActor, LVar8, 2)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_WMagikoopa_Script_HealAll_1F = {
    Call(RandInt, 1000, LVar0)
    IfGt(LVar0, 750)
        Call(GetActorFlags, ACTOR_SELF, LVar0)
        IfFlag(LVar0, 512)
            ExecWait(TTYD64_imp_1F_WMagikoopa_Script_WMagikoopa_ShapeSpell_1F)
        Else
            ExecWait(TTYD64_imp_1F_WMagikoopa_Script_WMagikoopa_WandStrike_1F)
        EndIf
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560302)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570302)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 7, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560301)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570301)
    EndIf
    Wait(5)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Set(LFlag0, 0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar1)
    IfEq(LVar1, 71)
        Call(GetActorVar, LVar0, 8, LVar1)
        IfEq(LVar1, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    IfEq(LFlag0, 0)
        Thread
            Wait(5)
            Call(PlaySoundAtActor, LVar0, 8301)
            Call(PlaySoundAtActor, LVar0, 532)
            Wait(30)
            Call(PlaySoundAtActor, LVar0, 604)
        EndThread
        Thread
            Call(FreezeBattleState, 1)
            Call(HealActor, LVar0, 4, 1)
            Call(FreezeBattleState, 0)
        EndThread
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Call(WaitForBuffDone)
    Wait(1)
    Call(UseBattleCamPreset, 2)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_YMagikoopa_Script_YMagikoopa_WandStrike_1F = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 731)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x560202)
        Set(LVar0, 200)
        Loop(20)
            Sub(LVar0, 10)
            Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 5)
    Else
        Add(LVar0, 25)
    EndIf
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
    Set(LVar0, 55)
    Loop(20)
        Add(LVar0, 10)
        Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_SELF, 1, 255)
    Call(SetAnimation, ACTOR_SELF, 1, 0x560203)
    Wait(11)
    Call(PlaySoundAtActor, ACTOR_SELF, 732)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(UseBattleCamPreset, 2)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560201)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560201)
            Call(FlyToGoal, ACTOR_SELF, 20, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_RMagikoopa_Script_RMagikoopa_WandStrike_1F = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 731)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x560102)
        Set(LVar0, 200)
        Loop(20)
            Sub(LVar0, 10)
            Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 5)
    Else
        Add(LVar0, 25)
    EndIf
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
    Set(LVar0, 55)
    Loop(20)
        Add(LVar0, 10)
        Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_SELF, 1, 255)
    Call(SetAnimation, ACTOR_SELF, 1, 0x560103)
    Wait(11)
    Call(PlaySoundAtActor, ACTOR_SELF, 732)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(UseBattleCamPreset, 2)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560101)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560101)
            Call(FlyToGoal, ACTOR_SELF, 20, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_GRYMagikoopa_Script_GRYMagikoopa_WandStrike_1F = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 731)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x560502)
        Set(LVar0, 200)
        Loop(20)
            Sub(LVar0, 10)
            Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 5)
    Else
        Add(LVar0, 25)
    EndIf
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
    Set(LVar0, 55)
    Loop(20)
        Add(LVar0, 10)
        Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_SELF, 1, 255)
    Call(SetAnimation, ACTOR_SELF, 1, 0x560503)
    Wait(11)
    Call(PlaySoundAtActor, ACTOR_SELF, 732)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(UseBattleCamPreset, 2)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560501)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560501)
            Call(FlyToGoal, ACTOR_SELF, 20, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_GRNMagikoopa_Script_GRNMagikoopa_WandStrike_1F = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 731)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x560402)
        Set(LVar0, 200)
        Loop(20)
            Sub(LVar0, 10)
            Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 5)
    Else
        Add(LVar0, 25)
    EndIf
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
    Set(LVar0, 55)
    Loop(20)
        Add(LVar0, 10)
        Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_SELF, 1, 255)
    Call(SetAnimation, ACTOR_SELF, 1, 0x560403)
    Wait(11)
    Call(PlaySoundAtActor, ACTOR_SELF, 732)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(UseBattleCamPreset, 2)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560401)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560401)
            Call(FlyToGoal, ACTOR_SELF, 20, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_WMagikoopa_Script_WMagikoopa_WandStrike_1F = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 731)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x560302)
        Set(LVar0, 200)
        Loop(20)
            Sub(LVar0, 10)
            Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 5)
    Else
        Add(LVar0, 25)
    EndIf
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
    Set(LVar0, 55)
    Loop(20)
        Add(LVar0, 10)
        Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_SELF, 1, 255)
    Call(SetAnimation, ACTOR_SELF, 1, 0x560303)
    Wait(11)
    Call(PlaySoundAtActor, ACTOR_SELF, 732)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(UseBattleCamPreset, 2)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560301)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Set(LVar0, 200)
            Loop(20)
                Sub(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x560301)
            Call(FlyToGoal, ACTOR_SELF, 20, 0, 10)
            Set(LVar0, 55)
            Loop(20)
                Add(LVar0, 10)
                Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, ACTOR_SELF, 1, 255)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_WMagikoopa_Script_HandleEvent_8022B854_1F = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            ExecWait(b_area_pra_white_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseOrEq(10)
        CaseOrEq(12)
            ExecWait(b_area_pra_white_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_imp_1F_WMagikoopa_Script_8022B258_1F)
        EndCaseGroup
        CaseOrEq(14)
        CaseOrEq(15)
            ExecWait(b_area_pra_white_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570305)
            SetConst(LVar2, 0x570306)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_imp_1F_WMagikoopa_Script_8022B258_1F)
        EndCaseGroup
        CaseEq(36)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570305)
            SetConst(LVar2, 0x570306)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570306)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570301)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570301)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570301)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570301)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570304)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570302)
            ExecWait(b_area_pra_white_magikoopa_EVS_Flee)
            Return
        CaseEq(58)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570302)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                IfFlag(LVar0, 0x80000)
                    Call(SetPartDispOffset, ACTOR_SELF, 2, -3, 0, 0)
                Else
                    Call(SetPartDispOffset, ACTOR_SELF, 2, -15, 0, 0)
                EndIf
            EndIf
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570304)
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
EvtScript TTYD64_imp_1F_YMagikoopa_Script_HandleEvent_80225E84_1F = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            ExecWait(b_area_pra_yellow_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570204)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseOrEq(10)
        CaseOrEq(12)
            ExecWait(b_area_pra_yellow_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570204)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_imp_1F_YMagikoopa_Script_80225888_1F)
        EndCaseGroup
        CaseOrEq(14)
        CaseOrEq(15)
            ExecWait(b_area_pra_yellow_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570205)
            SetConst(LVar2, 0x570206)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_imp_1F_YMagikoopa_Script_80225888_1F)
        EndCaseGroup
        CaseEq(36)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570205)
            SetConst(LVar2, 0x570206)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570206)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570204)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570204)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570204)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570201)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570204)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570204)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570201)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570201)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570201)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570204)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570202)
            ExecWait(b_area_pra_yellow_magikoopa_EVS_Flee)
            Return
        CaseEq(58)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570202)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                IfFlag(LVar0, 0x80000)
                    Call(SetPartDispOffset, ACTOR_SELF, 2, -3, 0, 0)
                Else
                    Call(SetPartDispOffset, ACTOR_SELF, 2, -15, 0, 0)
                EndIf
            EndIf
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570204)
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
EvtScript TTYD64_imp_1F_RMagikoopa_Script_RMagikoopa_ShapeSpell_1F = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    Else
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 10)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 12)
        Add(LVar1, 14)
    Else
        Sub(LVar0, 30)
        Add(LVar1, 36)
    EndIf
    Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570102)
    Wait(30)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8405)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570103)
            Wait(5)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar9)
            IfFlag(LVar9, 0x80000)
                Sub(LVar0, 8)
                Add(LVar1, 8)
            Else
                Sub(LVar0, 20)
                Add(LVar1, 20)
            EndIf
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Sub(LVar3, 50)
            Set(LVar4, 0)
            Call(b_area_pra_red_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
            Wait(50)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(14)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 8405)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570103)
    Wait(5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 8)
        Add(LVar1, 8)
    Else
        Sub(LVar0, 20)
        Add(LVar1, 20)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 10)
    Call(b_area_pra_red_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
    Wait(18)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(19)
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
EvtScript TTYD64_imp_1F_YMagikoopa_Script_YMagikoopa_ShapeSpell_1F = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    Else
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 10)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 12)
        Add(LVar1, 14)
    Else
        Sub(LVar0, 30)
        Add(LVar1, 36)
    EndIf
    Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570202)
    Wait(30)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8405)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570203)
            Wait(5)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar9)
            IfFlag(LVar9, 0x80000)
                Sub(LVar0, 8)
                Add(LVar1, 8)
            Else
                Sub(LVar0, 20)
                Add(LVar1, 20)
            EndIf
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Sub(LVar3, 50)
            Set(LVar4, 0)
            Call(b_area_pra_yellow_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
            Wait(50)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(14)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 8405)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570203)
    Wait(5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 8)
        Add(LVar1, 8)
    Else
        Sub(LVar0, 20)
        Add(LVar1, 20)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 10)
    Call(b_area_pra_yellow_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
    Wait(18)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(19)
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
EvtScript TTYD64_imp_1F_GRYMagikoopa_Script_GRYMagikoopa_ShapeSpell_1F = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    Else
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 10)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 12)
        Add(LVar1, 14)
    Else
        Sub(LVar0, 30)
        Add(LVar1, 36)
    EndIf
    Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570502)
    Wait(30)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8405)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570503)
            Wait(5)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar9)
            IfFlag(LVar9, 0x80000)
                Sub(LVar0, 8)
                Add(LVar1, 8)
            Else
                Sub(LVar0, 20)
                Add(LVar1, 20)
            EndIf
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Sub(LVar3, 50)
            Set(LVar4, 0)
            Call(b_area_pra_gray_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
            Wait(50)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(14)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 8405)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570503)
    Wait(5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 8)
        Add(LVar1, 8)
    Else
        Sub(LVar0, 20)
        Add(LVar1, 20)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 10)
    Call(b_area_pra_gray_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
    Wait(18)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(19)
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
EvtScript TTYD64_imp_1F_GRNMagikoopa_Script_GRNMagikoopa_ShapeSpell_1F = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    Else
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 10)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 12)
        Add(LVar1, 14)
    Else
        Sub(LVar0, 30)
        Add(LVar1, 36)
    EndIf
    Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570402)
    Wait(30)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8405)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570403)
            Wait(5)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar9)
            IfFlag(LVar9, 0x80000)
                Sub(LVar0, 8)
                Add(LVar1, 8)
            Else
                Sub(LVar0, 20)
                Add(LVar1, 20)
            EndIf
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Sub(LVar3, 50)
            Set(LVar4, 0)
            Call(b_area_pra_green_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
            Wait(50)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(14)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 8405)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570403)
    Wait(5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 8)
        Add(LVar1, 8)
    Else
        Sub(LVar0, 20)
        Add(LVar1, 20)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 10)
    Call(b_area_pra_green_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
    Wait(18)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(19)
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
EvtScript TTYD64_imp_1F_WMagikoopa_Script_WMagikoopa_ShapeSpell_1F = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    Else
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 10)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8404)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 12)
        Add(LVar1, 14)
    Else
        Sub(LVar0, 30)
        Add(LVar1, 36)
    EndIf
    Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570302)
    Wait(30)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8405)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570303)
            Wait(5)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar9)
            IfFlag(LVar9, 0x80000)
                Sub(LVar0, 8)
                Add(LVar1, 8)
            Else
                Sub(LVar0, 20)
                Add(LVar1, 20)
            EndIf
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Sub(LVar3, 50)
            Set(LVar4, 0)
            Call(b_area_pra_white_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
            Wait(50)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(14)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 8405)
    Call(SetAnimation, ACTOR_SELF, 2, 0x570303)
    Wait(5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Sub(LVar0, 8)
        Add(LVar1, 8)
    Else
        Sub(LVar0, 20)
        Add(LVar1, 20)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 10)
    Call(b_area_pra_white_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
    Wait(18)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(19)
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
EvtScript TTYD64_imp_1F_YMagikoopa_Script_80225888_1F = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560204)
        Goto(0)
    EndIf
    Call(GetLastElement, LVar0)
    IfFlag(LVar0, 1024)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560204)
        Goto(0)
    EndIf
    Return
    Label(0)
    Call(HideHealthBar, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 3, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    EndIf
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x800000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20001, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20001, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x800000, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 0x100000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar2, 1)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(PlaySoundAtActor, ACTOR_SELF, 769)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(b_area_pra_yellow_magikoopa_StartRumbleWithParams, 150, 10)
    Thread
        Call(ShakeCam, 1, 0, 5, Float(0.7001953125))
    EndThread
    Call(GetLastEvent, ACTOR_SELF, LVar3)
    IfEq(LVar3, 15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560204)
        Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Add(LVar4, 10)
        Add(LVar5, 5)
        Call(PlayEffect_impl, 39, 0, LVar3, LVar4, LVar5, Float(1.0), 10, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Loop(20)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
        Wait(1)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
        Wait(1)
    EndLoop
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x560201)
    Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_pra_yellow_magikoopa_EVS_HandleEvent))
    Call(SetActorType, ACTOR_SELF, 85)
    Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_imp_1F_YMagikoopa_StatusTable_80224F78_1F))
    Call(b_area_pra_yellow_magikoopa_SetAbsoluteStatusOffsets, -10, 20, 10, 32)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(GetIndexFromPos, ACTOR_SELF, LVar0)
    Mod(LVar0, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVar0)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_WMagikoopa_Script_8022B258_1F = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560304)
        Goto(0)
    EndIf
    Call(GetLastElement, LVar0)
    IfFlag(LVar0, 1024)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560304)
        Goto(0)
    EndIf
    Return
    Label(0)
    Call(HideHealthBar, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 3, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    EndIf
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x800000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20001, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20001, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x800000, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 0x100000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar2, 1)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(PlaySoundAtActor, ACTOR_SELF, 769)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(b_area_pra_white_magikoopa_StartRumbleWithParams, 150, 10)
    Thread
        Call(ShakeCam, 1, 0, 5, Float(0.7001953125))
    EndThread
    Call(GetLastEvent, ACTOR_SELF, LVar3)
    IfEq(LVar3, 15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560304)
        Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Add(LVar4, 10)
        Add(LVar5, 5)
        Call(PlayEffect_impl, 39, 0, LVar3, LVar4, LVar5, Float(1.0), 10, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Loop(20)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
        Wait(1)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
        Wait(1)
    EndLoop
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x560301)
    Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_pra_white_magikoopa_EVS_HandleEvent_Ground))
    Call(SetActorType, ACTOR_SELF, 89)
    Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_imp_1F_WMagikoopa_StatusTable_8022A948_1F))
    Call(b_area_pra_white_magikoopa_SetAbsoluteStatusOffsets, -10, 20, 10, 32)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(GetIndexFromPos, ACTOR_SELF, LVar0)
    Mod(LVar0, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVar0)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_AlbinoDino_Script_TakeTurn_8021E070_1F = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    ExecGetTID(b_area_pra_albino_dino_EVS_AddWalkQuakeFX, LVar9)
    Thread
        Loop(3)
            Call(PlaySoundAtActor, ACTOR_SELF, 779)
            Wait(4)
            Call(PlaySoundAtActor, ACTOR_SELF, 765)
            Wait(4)
        EndLoop
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x4F0005)
    Wait(20)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0, 0, 1, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            Thread
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(AddGoalPos, ACTOR_SELF, -100, 0, 0)
                Call(SetActorSpeed, ACTOR_SELF, Float(12.0))
                Call(RunToGoal, ACTOR_SELF, 0, 0)
                KillThread(LVar9)
            EndThread
            Call(UseBattleCamPreset, 2)
            Wait(30)
            IfEq(LVarF, 5)
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(40)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(b_area_pra_albino_dino_EVS_ReturnHome)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Call(AddGoalPos, ACTOR_SELF, 12, 0, 0)
    Else
        Call(AddGoalPos, ACTOR_SELF, 30, 0, 0)
    EndIf
    Call(SetActorSpeed, ACTOR_SELF, Float(12.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Thread
        Call(ShakeCam, 1, 0, 4, Float(1.5))
    EndThread
    KillThread(LVar9)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0, 24, 4, 32)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 765)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4F0003)
            Call(ShakeCam, 1, 0, 3, Float(1.0))
            Wait(10)
            Call(YieldTurn)
            ExecWait(b_area_pra_albino_dino_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_Swoopula_Script_8021BC30_1C = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340117)
            SetConst(LVar2, 0x340118)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340117)
            SetConst(LVar2, 0x340118)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340118)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Call(UseBattleCamPreset, 2)
            ExecWait(TTYD64_imp_1F_Swoopula_Script_8021BA70_1C)
        CaseEq(38)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Thread
                Wait(30)
                Call(UseBattleCamPreset, 2)
            EndThread
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340102)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340102)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340102)
            SetConst(LVar2, 0x340115)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340102)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x340115)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_Swoopula_Script_8021C0B4_1C = {
    Call(HideHealthBar, ACTOR_SELF)
    Call(GetLastDamage, ACTOR_SELF, LVar0)
    IfLe(LVar0, 0)
        Return
    EndIf
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 24)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfEq(LVarA, -1)
        Call(SetHomePos, ACTOR_SELF, LVar0, 45, LVar2)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalToHome, ACTOR_SELF)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 0, 0)
        Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
    Else
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalPos, ACTOR_SELF, LVar0, 45, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 0, 0)
        Call(GetIndexFromPos, ACTOR_SELF, LVarA)
        Mod(LVarA, 4)
        Add(LVarA, 4)
        Call(SetGoalToIndex, ACTOR_SELF, LVarA)
        Call(GetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
        Call(SetHomePos, ACTOR_SELF, LVarA, LVarB, LVarC)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalToHome, ACTOR_SELF)
        Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
    EndIf
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, -10)
    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 22)
    Call(b_area_pra_swoopula_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1F_Swoopula_IdleAnimations_8021B9B0_1C))
    Call(SetActorFlagBits, ACTOR_SELF, 512, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_WMagikoopa_Script_TakeTurn_8022E2F4_1F = {
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_pra_white_magikoopa_EVS_Flee)
        Return
    EndIf
    Set(LVarA, 0)
    Set(LVarB, 0)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Set(LFlag0, 0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar1)
    IfEq(LVar1, 71)
        Call(GetActorVar, LVar0, 8, LVar1)
        IfEq(LVar1, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    IfEq(LFlag0, 0)
        Call(GetActorHP, LVar0, LVar2)
        Call(GetEnemyMaxHP, LVar0, LVar3)
        IfNe(LVar2, LVar3)
            Add(LVarA, 1)
        EndIf
        Add(LVarB, 1)
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Mul(LVarA, 100)
    Div(LVarA, LVarB)
    Switch(LVarA)
        CaseGe(60)
            ExecWait(TTYD64_imp_1F_WMagikoopa_Script_HealAll_1F)
        CaseEq(0)
            Call(GetActorFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 512)
                ExecWait(TTYD64_imp_1F_WMagikoopa_Script_WMagikoopa_ShapeSpell_1F)
            Else
                ExecWait(TTYD64_imp_1F_WMagikoopa_Script_WMagikoopa_WandStrike_1F)
            EndIf
        CaseDefault
            ExecWait(TTYD64_imp_1F_WMagikoopa_Script_HealOne_1F)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_Swoopula_Script_8021BA70_1C = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 0, -24, 0)
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 11)
            Call(SetActorFlagBits, ACTOR_SELF, 2048, 1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1F_Swoopula_IdleAnimations_8021B964_1C))
            Call(SetAnimation, ACTOR_SELF, 1, 0x34010C)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 24)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 11)
    EndSwitch
    Return
    End
};
// clang-format on

Battle TTYD64_pra_FormationTable[] = {
    { .name = "\320\265\320\265\301\345\353\353x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pra_Formation_00,
      .stage = &b_area_pra_pra_01,
      .onBattleStart = NULL },
    { .name = "\320\265\320\265\301\345\353\353x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pra_Formation_01,
      .stage = &b_area_pra_pra_01,
      .onBattleStart = NULL },
    { .name = "\320\265\320\265\301\345\353\353x4",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pra_Formation_02,
      .stage = &b_area_pra_pra_01,
      .onBattleStart = NULL },
    { .name = "\320\265\320\265\301\345\353\353x3,\244\250\355\374\253\341\303\257\010]\211\011",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pra_Formation_03,
      .stage = &b_area_pra_pra_01,
      .onBattleStart = NULL },
    { .name = "\333\357\244\310\254\334\363",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_pra_Formation_04,
      .stage = &b_area_pra_pra_01,
      .onBattleStart = NULL },
    { .name = "\333\357\244\310\254\334\363x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pra_Formation_05,
      .stage = &b_area_pra_pra_01,
      .onBattleStart = NULL },
    { .name = "\333\357\244\310\254\334\363x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pra_Formation_06,
      .stage = &b_area_pra_pra_01,
      .onBattleStart = NULL },
    { .name = "\333\357\244\310\254\334\363x\022,\320\265\320\265\301\345\353\353",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pra_Formation_07,
      .stage = &b_area_pra_pra_01,
      .onBattleStart = NULL },
    { .name = "\333\357\244\310\254\334\363x\022,\244\250\355\374\253\341\303\257",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pra_Formation_08,
      .stage = &b_area_pra_pra_01,
      .onBattleStart = NULL },
    { .name = "\333\357\244\310\254\334\363x\022,\333\357\244\310\253\341\303\257",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pra_Formation_09,
      .stage = &b_area_pra_pra_01,
      .onBattleStart = NULL },
    { .name = "\333\357\244\310\254\334\363x\022,\333\357\244\310\253\341\303\257,\354\303\311\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pra_Formation_0A,
      .stage = &b_area_pra_pra_01,
      .onBattleStart = NULL },
    { .name = "\333\357\244\310\254\334\363,\260\354\244\253\341\303\257",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pra_Formation_0B,
      .stage = &b_area_pra_pra_01,
      .onBattleStart = NULL },
    { .name = "\333\357\244\310\254\334\363x\023,\260\352\374\363\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pra_Formation_0C,
      .stage = &b_area_pra_pra_01,
      .onBattleStart = NULL },
    { .name = "\333\357\244\310\254\334\363x\022,\260\352\374\363\253\341\303\257,\333\357\244\310\253\341\303\257\010]"
              "\211\011",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pra_Formation_0D,
      .stage = &b_area_pra_pra_01,
      .onBattleStart = NULL },
    { .name = "\273\255\276\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_pra_Formation_0E,
      .stage = &b_area_pra_pra_01,
      .onBattleStart = NULL },
    {},
};

s32 TTYD64_imp_1F_YMagikoopa_StatusTable_80224F78_1F[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  75, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_imp_1F_GRYMagikoopa_StatusTable_80227C88_1F[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  75, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_imp_1F_WMagikoopa_StatusTable_8022A948_1F[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  75, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_imp_1F_WMagikoopa_StatusTable_8022A9F4_1F[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  100, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,   33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_imp_1F_GRNMagikoopa_StatusTable_802222B8_1F[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  75, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_imp_1F_YMagikoopa_StatusTable_80225024_1F[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  100, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,   33, 0, 38, 0,  39, 0,  41, -1, 0,
};

// clang-format off
EvtScript TTYD64_imp_1F_GRNMagikoopa_Script_Init_802246D8_1F = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra_green_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1F_GRNMagikoopa_Script_TakeTurn_80224820_1F))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_pra_green_magikoopa_EVS_HandleEvent))
    Call(GetBattleVar, 2, LVar0)
    IfEq(LVar0, 0)
        Call(SetBattleVar, 2, -1)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_YMagikoopa_Script_Init_80227398_1F = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra_yellow_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1F_YMagikoopa_Script_TakeTurn_802274E0_1F))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_pra_yellow_magikoopa_EVS_HandleEvent))
    Call(GetBattleVar, 2, LVar0)
    IfEq(LVar0, 0)
        Call(SetBattleVar, 2, -1)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_YMagikoopa_Script_Init_8022743C_1F = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra_yellow_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1F_YMagikoopa_Script_TakeTurn_802274E0_1F))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1F_YMagikoopa_Script_HandleEvent_80225E84_1F))
    Call(GetBattleVar, 2, LVar0)
    IfEq(LVar0, 0)
        Call(SetBattleVar, 2, -1)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_GRYMagikoopa_Script_Init_8022A0A8_1F = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra_gray_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1F_GRYMagikoopa_Script_TakeTurn_8022A1F0_1F))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_pra_gray_magikoopa_EVS_HandleEvent))
    Call(GetBattleVar, 2, LVar0)
    IfEq(LVar0, 0)
        Call(SetBattleVar, 2, -1)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_RMagikoopa_Script_Init_80221A18_1F = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra_red_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1F_RMagikoopa_Script_TakeTurn_80221B60_1F))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_pra_red_magikoopa_EVS_HandleEvent))
    Call(GetBattleVar, 2, LVar0)
    IfEq(LVar0, 0)
        Call(SetBattleVar, 2, -1)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pra_Formation_0A[] = {
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_WMagikoopa_1F_WMagikoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_1F_RMagikoopa_1F_RMagikoopa,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pra_Formation_0D[] = {
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_GRNMagikoopa_1F_GRNMagikoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_1F_WMagikoopa_1F_FlyingWMagikoopa,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pra_Formation_0C[] = {
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_GRNMagikoopa_1F_GRNMagikoopa,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pra_Formation_02[] = {
    { .actor = &TTYD64_imp_1F_Swoopula_1F_Swoopula,
      .home = { .vec = &TTYD64_pra_Vector3D_8022F04C },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
    { .actor = &TTYD64_imp_1F_Swoopula_1F_Swoopula,
      .home = { .vec = &TTYD64_pra_Vector3D_8022F058 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
    { .actor = &TTYD64_imp_1F_Swoopula_1F_Swoopula,
      .home = { .vec = &TTYD64_pra_Vector3D_8022F064 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
    { .actor = &TTYD64_imp_1F_Swoopula_1F_Swoopula,
      .home = { .vec = (void*) (((u8*) &b_area_pra_pos_swoopula_2 + 0x24)) },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
};

FormationRow TTYD64_pra_Formation_03[] = {
    { .actor = &TTYD64_imp_1F_Swoopula_1F_Swoopula,
      .home = { .vec = &TTYD64_pra_Vector3D_8022F0EC },
      .priority = 10,
      .var0 = -1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
    { .actor = &TTYD64_imp_1F_Swoopula_1F_Swoopula,
      .home = { .vec = &TTYD64_pra_Vector3D_8022F0F8 },
      .priority = 9,
      .var0 = -1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
    { .actor = &TTYD64_imp_1F_Swoopula_1F_Swoopula,
      .home = { .vec = (void*) (((u8*) &b_area_pra_pos_swoopula_3 + 0x18)) },
      .priority = 8,
      .var0 = -1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
    { .actor = &TTYD64_imp_1F_YMagikoopa_1F_FlyingYMagikoopa,
      .home = { .vec = &b_area_pra_pos_magikoopa },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

ActorPartBlueprint TTYD64_imp_1F_YMagikoopa_PartsTable_802250F4_1F[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1F_YMagikoopa_IdleAnimations_802251B0_1F,
        .defenseTable = b_area_pra_yellow_magikoopa_FlyingDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -10, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1F_YMagikoopa_IdleAnimations_802251FC_1F,
        .defenseTable = b_area_pra_yellow_magikoopa_FlyingDefense,
        .eventFlags = 0x800000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_pra_yellow_magikoopa_BroomAnims,
        .defenseTable = b_area_pra_yellow_magikoopa_FlyingDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1F_WMagikoopa_PartsTable_8022AAC4_1F[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1F_WMagikoopa_IdleAnimations_8022AB80_1F,
        .defenseTable = b_area_pra_white_magikoopa_DefenseTable_80223B2C,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -10, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1F_WMagikoopa_IdleAnimations_8022ABCC_1F,
        .defenseTable = b_area_pra_white_magikoopa_DefenseTable_80223B2C,
        .eventFlags = 0x800000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_pra_white_magikoopa_IdleAnimations_80223E08,
        .defenseTable = b_area_pra_white_magikoopa_DefenseTable_80223B2C,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_imp_1F_WMagikoopa_Script_Init_8022CD68_1F = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra_white_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1F_WMagikoopa_Script_TakeTurn_8022E2F4_1F))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_pra_white_magikoopa_EVS_HandleEvent_Ground))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_WMagikoopa_Script_Init_8022CDCC_1F = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra_white_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1F_WMagikoopa_Script_TakeTurn_8022E2F4_1F))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1F_WMagikoopa_Script_HandleEvent_8022B854_1F))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_Swoopula_Script_Init_8021B9FC_1C = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1F_Swoopula_Script_TakeTurn_8021E7B4_1C))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra_swoopula_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1F_Swoopula_Script_HandleEvent_8021C414_1C))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pra_Formation_01[] = {
    { .actor = &TTYD64_imp_1F_Swoopula_1F_Swoopula,
      .home = { .vec = &TTYD64_pra_Vector3D_8022EF90 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
    { .actor = &TTYD64_imp_1F_Swoopula_1F_Swoopula,
      .home = { .vec = &TTYD64_pra_Vector3D_8022EF9C },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
    { .actor = &TTYD64_imp_1F_Swoopula_1F_Swoopula,
      .home = { .vec = &TTYD64_pra_Vector3D_8022EFA8 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
};

FormationRow TTYD64_pra_Formation_08[] = {
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_YMagikoopa_1F_YMagikoopa,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pra_Formation_09[] = {
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_WMagikoopa_1F_WMagikoopa,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pra_Formation_06[] = {
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
};

FormationRow TTYD64_pra_Formation_07[] = {
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_Swoopula_1F_Swoopula,
      .home = { .vec = &TTYD64_pra_Vector3D_8022EFA8 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
};

s32 TTYD64_imp_1F_GRYMagikoopa_IdleAnimations_80227EC0_1F[] = {
    1,  0x560501, 7, 0x560500, 6, 0x560508, 9, 0x560501, 8, 0x560500,
    11, 0x560501, 5, 0x560500, 4, 0x560507, 3, 0x560507, 0,
};

s32 TTYD64_imp_1F_WMagikoopa_IdleAnimations_8022ABCC_1F[] = {
    1,  0x570301, 7, 0x570300, 6, 0x570308, 9, 0x570301, 8, 0x570300,
    11, 0x570301, 5, 0x570300, 4, 0x570307, 3, 0x570307, 0,
};

s32 TTYD64_imp_1F_Swoopula_IdleAnimations_8021B964_1C[] = {
    1,  0x34010C, 7, 0x34010B, 6, 0x34010F, 9, 0x34010C, 8, 0x34010B,
    11, 0x34010C, 5, 0x34010B, 4, 0x340110, 3, 0x340110, 0,
};

// clang-format off
EvtScript TTYD64_imp_1F_WhiteClubba_Script_Init_8021E750_1F = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1F_WhiteClubba_Script_TakeTurn_8021ECBC_1F))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra_white_clubba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_pra_white_clubba_EVS_HandleEvent))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1F_AlbinoDino_Script_Init_8021D968_1F = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1F_AlbinoDino_Script_TakeTurn_8021E070_1F))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra_albino_dino_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_pra_albino_dino_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_1F_GRNMagikoopa_IdleAnimations_802224F0_1F[] = {
    1,  0x560401, 7, 0x560400, 6, 0x560408, 9, 0x560401, 8, 0x560400,
    11, 0x560401, 5, 0x560400, 4, 0x560407, 3, 0x560407, 0,
};

s32 TTYD64_imp_1F_RMagikoopa_IdleAnimations_8021F830_1F[] = {
    1,  0x560101, 7, 0x560100, 6, 0x560108, 9, 0x560101, 8, 0x560100,
    11, 0x560101, 5, 0x560100, 4, 0x560107, 3, 0x560107, 0,
};

s32 TTYD64_imp_1F_WMagikoopa_IdleAnimations_8022AB80_1F[] = {
    1,  0x560301, 7, 0x560300, 6, 0x560308, 9, 0x560301, 8, 0x560300,
    11, 0x560301, 5, 0x560300, 4, 0x560307, 3, 0x560307, 0,
};

s32 TTYD64_imp_1F_YMagikoopa_IdleAnimations_802251B0_1F[] = {
    1,  0x560201, 7, 0x560200, 6, 0x560208, 9, 0x560201, 8, 0x560200,
    11, 0x560201, 5, 0x560200, 4, 0x560207, 3, 0x560207, 0,
};

s32 TTYD64_imp_1F_AlbinoDino_IdleAnimations_8021D810_1F[] = {
    1,  0x4F0003, 7, 0x4F0000, 6, 0x4F0003, 9, 0x4F0003, 8, 0x4F0000,
    11, 0x4F0003, 5, 0x4F0000, 4, 0x4F0000, 3, 0x4F0000, 0,
};

s32 TTYD64_imp_1F_Swoopula_IdleAnimations_8021B9B0_1C[] = {
    1,  0x340102, 7, 0x340101, 6, 0x340113, 9, 0x340102, 8, 0x340101,
    11, 0x340102, 5, 0x340101, 4, 0x340114, 3, 0x340114, 0,
};

s32 TTYD64_imp_1F_WhiteClubba_IdleAnimations_8021E5F0_1F[] = {
    1,  0x3A0101, 7, 0x3A0100, 6, 0x3A0103, 9, 0x3A0101, 8, 0x3A0100,
    11, 0x3A0101, 5, 0x3A0100, 4, 0x3A0105, 3, 0x3A0105, 0,
};

s32 TTYD64_imp_1F_YMagikoopa_IdleAnimations_802251FC_1F[] = {
    1,  0x570201, 7, 0x570200, 6, 0x570208, 9, 0x570201, 8, 0x570200,
    11, 0x570201, 5, 0x570200, 4, 0x570207, 3, 0x570207, 0,
};

FormationRow TTYD64_pra_Formation_0B[] = {
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_GRYMagikoopa_1F_GRYMagikoopa,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pra_Formation_00[] = {
    { .actor = &TTYD64_imp_1F_Swoopula_1F_Swoopula,
      .home = { .vec = &TTYD64_pra_Vector3D_8022EF9C },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
    { .actor = &TTYD64_imp_1F_Swoopula_1F_Swoopula,
      .home = { .vec = &TTYD64_pra_Vector3D_8022EFA8 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
};

FormationRow TTYD64_pra_Formation_05[] = {
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
};

ActorBlueprint TTYD64_imp_1F_GRYMagikoopa_1F_GRYMagikoopa = {
    .flags = 0x0,
    .maxHP = 11,
    .type = 0x57,
    .level = 21,
    .partCount = 1,
    .partsData = TTYD64_imp_1F_GRYMagikoopa_PartsTable_80227DE0_1F,
    .initScript = &TTYD64_imp_1F_GRYMagikoopa_Script_Init_8022A0A8_1F,
    .statusTable = TTYD64_imp_1F_GRYMagikoopa_StatusTable_80227C88_1F,
    .escapeChance = 40,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 2,
    .size = { 36, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 32 },
};

ActorBlueprint TTYD64_imp_1F_WMagikoopa_1F_WMagikoopa = {
    .flags = 0x0,
    .maxHP = 11,
    .type = 0x59,
    .level = 21,
    .partCount = 1,
    .partsData = TTYD64_imp_1F_WMagikoopa_PartsTable_8022AAA0_1F,
    .initScript = &TTYD64_imp_1F_WMagikoopa_Script_Init_8022CD68_1F,
    .statusTable = TTYD64_imp_1F_WMagikoopa_StatusTable_8022A948_1F,
    .escapeChance = 40,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 36, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 32 },
};

ActorBlueprint TTYD64_imp_1F_AlbinoDino_1F_AlbinoDino = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x44,
    .level = 23,
    .partCount = 1,
    .partsData = TTYD64_imp_1F_AlbinoDino_PartsTable_8021D91C_1F,
    .initScript = &TTYD64_imp_1F_AlbinoDino_Script_Init_8021D968_1F,
    .statusTable = b_area_pra_albino_dino_StatusTable,
    .escapeChance = 40,
    .airLiftChance = 15,
    .hurricaneChance = 10,
    .spookChance = 25,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 64, 56 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -22, 24 },
    .statusTextOffset = { 11, 40 },
};

ActorBlueprint TTYD64_imp_1F_YMagikoopa_1F_FlyingYMagikoopa = {
    .flags = 0x200,
    .maxHP = 11,
    .type = 0x56,
    .level = 21,
    .partCount = 3,
    .partsData = TTYD64_imp_1F_YMagikoopa_PartsTable_802250F4_1F,
    .initScript = &TTYD64_imp_1F_YMagikoopa_Script_Init_8022743C_1F,
    .statusTable = TTYD64_imp_1F_YMagikoopa_StatusTable_80225024_1F,
    .escapeChance = 40,
    .airLiftChance = 95,
    .hurricaneChance = 75,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 48, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -25, 20 },
    .statusTextOffset = { 1, 34 },
};

ActorBlueprint TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba = {
    .flags = 0x0,
    .maxHP = 12,
    .type = 0x38,
    .level = 23,
    .partCount = 1,
    .partsData = TTYD64_imp_1F_WhiteClubba_PartsTable_8021E704_1F,
    .initScript = &TTYD64_imp_1F_WhiteClubba_Script_Init_8021E750_1F,
    .statusTable = b_area_pra_white_clubba_StatusTable,
    .escapeChance = 50,
    .airLiftChance = 50,
    .hurricaneChance = 60,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 42, 42 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 35 },
};

ActorBlueprint TTYD64_imp_1F_Swoopula_1F_Swoopula = {
    .flags = 0x800,
    .maxHP = 8,
    .type = 0x3A,
    .level = 22,
    .partCount = 1,
    .partsData = TTYD64_imp_1F_Swoopula_PartsTable_8021B918_1C,
    .initScript = &TTYD64_imp_1F_Swoopula_Script_Init_8021B9FC_1C,
    .statusTable = b_area_pra_swoopula_StatusTable,
    .escapeChance = 30,
    .airLiftChance = 95,
    .hurricaneChance = 95,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 1,
    .size = { 31, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, -20 },
    .statusTextOffset = { 10, -20 },
};

ActorBlueprint TTYD64_imp_1F_YMagikoopa_1F_YMagikoopa = {
    .flags = 0x0,
    .maxHP = 11,
    .type = 0x55,
    .level = 21,
    .partCount = 1,
    .partsData = TTYD64_imp_1F_YMagikoopa_PartsTable_802250D0_1F,
    .initScript = &TTYD64_imp_1F_YMagikoopa_Script_Init_80227398_1F,
    .statusTable = TTYD64_imp_1F_YMagikoopa_StatusTable_80224F78_1F,
    .escapeChance = 40,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 36, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 32 },
};

ActorBlueprint TTYD64_imp_1F_RMagikoopa_1F_RMagikoopa = {
    .flags = 0x0,
    .maxHP = 11,
    .type = 0x51,
    .level = 21,
    .partCount = 1,
    .partsData = TTYD64_imp_1F_RMagikoopa_PartsTable_8021F750_1F,
    .initScript = &TTYD64_imp_1F_RMagikoopa_Script_Init_80221A18_1F,
    .statusTable = b_area_pra_red_magikoopa_StatusTable,
    .escapeChance = 40,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 36, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 32 },
};

ActorBlueprint TTYD64_imp_1F_GRNMagikoopa_1F_GRNMagikoopa = {
    .flags = 0x0,
    .maxHP = 11,
    .type = 0x53,
    .level = 21,
    .partCount = 1,
    .partsData = TTYD64_imp_1F_GRNMagikoopa_PartsTable_80222410_1F,
    .initScript = &TTYD64_imp_1F_GRNMagikoopa_Script_Init_802246D8_1F,
    .statusTable = TTYD64_imp_1F_GRNMagikoopa_StatusTable_802222B8_1F,
    .escapeChance = 40,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 2,
    .size = { 36, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 32 },
};

ActorBlueprint TTYD64_imp_1F_WMagikoopa_1F_FlyingWMagikoopa = {
    .flags = 0x200,
    .maxHP = 11,
    .type = 0x5A,
    .level = 21,
    .partCount = 3,
    .partsData = TTYD64_imp_1F_WMagikoopa_PartsTable_8022AAC4_1F,
    .initScript = &TTYD64_imp_1F_WMagikoopa_Script_Init_8022CDCC_1F,
    .statusTable = TTYD64_imp_1F_WMagikoopa_StatusTable_8022A9F4_1F,
    .escapeChance = 40,
    .airLiftChance = 95,
    .hurricaneChance = 75,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 48, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -25, 20 },
    .statusTextOffset = { 1, 34 },
};

ActorPartBlueprint TTYD64_imp_1F_YMagikoopa_PartsTable_802250D0_1F[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1F_YMagikoopa_IdleAnimations_802251B0_1F,
        .defenseTable = b_area_pra_yellow_magikoopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1F_RMagikoopa_PartsTable_8021F750_1F[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1F_RMagikoopa_IdleAnimations_8021F830_1F,
        .defenseTable = b_area_pra_red_magikoopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1F_AlbinoDino_PartsTable_8021D91C_1F[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -9, 46 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1F_AlbinoDino_IdleAnimations_8021D810_1F,
        .defenseTable = b_area_pra_albino_dino_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -6, -17 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1F_WMagikoopa_PartsTable_8022AAA0_1F[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1F_WMagikoopa_IdleAnimations_8022AB80_1F,
        .defenseTable = b_area_pra_white_magikoopa_DefenseTable_80223B20,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1F_GRYMagikoopa_PartsTable_80227DE0_1F[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1F_GRYMagikoopa_IdleAnimations_80227EC0_1F,
        .defenseTable = b_area_pra_gray_magikoopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1F_WhiteClubba_PartsTable_8021E704_1F[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -12, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1F_WhiteClubba_IdleAnimations_8021E5F0_1F,
        .defenseTable = b_area_pra_white_clubba_DefenseTable,
        .eventFlags = 0x8,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 8, -3 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1F_GRNMagikoopa_PartsTable_80222410_1F[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1F_GRNMagikoopa_IdleAnimations_802224F0_1F,
        .defenseTable = b_area_pra_green_magikoopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1F_Swoopula_PartsTable_8021B918_1C[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 29 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1F_Swoopula_IdleAnimations_8021B964_1C,
        .defenseTable = b_area_pra_swoopula_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 1, 15 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_pra_Formation_0E[] = {
    { .actor = &TTYD64_imp_1F_AlbinoDino_1F_AlbinoDino,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pra_Formation_04[] = {
    { .actor = &TTYD64_imp_1F_WhiteClubba_1F_WhiteClubba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
};

Vec3i TTYD64_pra_Vector3D_8022F064 = { 80, 133, -25 };

Vec3i TTYD64_pra_Vector3D_8022F0F8 = { 40, 133, -25 };

Vec3i TTYD64_pra_Vector3D_8022F058 = { 40, 133, -25 };

Vec3i TTYD64_pra_Vector3D_8022F0EC = { 0, 133, -25 };

Vec3i TTYD64_pra_Vector3D_8022F04C = { 0, 133, -25 };

Vec3i TTYD64_pra_Vector3D_8022EF9C = { 55, 133, -25 };

Vec3i TTYD64_pra_Vector3D_8022EF90 = { 15, 133, -25 };

Vec3i TTYD64_pra_Vector3D_8022EFA8 = { 95, 133, -25 };

void TTYD64_InstallBattles_pra(void) {
    Mod_SetBattleList("TTYD64", 0x1F, TTYD64_pra_FormationTable);
}
