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

API_CALLABLE(b_area_flo_bzzap_AddVecXZ);
API_CALLABLE(b_area_flo_flo_03_CosInterpMinMax);
API_CALLABLE(b_area_flo_green_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_flo_green_magikoopa_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_flo_green_magikoopa_ShrinkActor);
API_CALLABLE(b_area_flo_green_magikoopa_StartRumbleWithParams);
API_CALLABLE(b_area_flo_medi_guy_MediGuySpriteRotationFunc);
API_CALLABLE(b_area_flo_red_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_flo_red_magikoopa_ShrinkActor);
API_CALLABLE(b_area_flo_ruff_puff_CosInterpMinMax);
API_CALLABLE(b_area_flo_white_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_flo_white_magikoopa_GetActorDefense);
API_CALLABLE(b_area_flo_white_magikoopa_GetBootsHammerLevel);
API_CALLABLE(b_area_flo_white_magikoopa_ShrinkActor);
API_CALLABLE(b_area_flo_yellow_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_flo_yellow_magikoopa_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_flo_yellow_magikoopa_ShrinkActor);
API_CALLABLE(b_area_flo_yellow_magikoopa_StartRumbleWithParams);
API_CALLABLE(battle_item_thunder_bolt_SpawnLightningFX);
extern s32 b_area_dgb_tubba_blubba_DefenseTable[];
extern s32 b_area_flo_amazy_dayzee_DefenseTable[];
extern EvtScript b_area_flo_amazy_dayzee_EVS_HandleEvent;
extern EvtScript b_area_flo_amazy_dayzee_EVS_Idle;
extern EvtScript b_area_flo_amazy_dayzee_EVS_Move_Flee;
extern EvtScript b_area_flo_amazy_dayzee_EVS_ReturnHome;
extern s32 b_area_flo_amazy_dayzee_StatusTable[];
extern s32 b_area_flo_bzzap_DefenseTable[];
extern EvtScript b_area_flo_bzzap_EVS_HandleEvent;
extern EvtScript b_area_flo_bzzap_EVS_Idle;
extern EvtScript b_area_flo_bzzap_EVS_ReturnHome;
extern s32 b_area_flo_crazee_dayzee_DefenseTable[];
extern EvtScript b_area_flo_crazee_dayzee_EVS_HandleEvent;
extern EvtScript b_area_flo_crazee_dayzee_EVS_Idle;
extern EvtScript b_area_flo_crazee_dayzee_EVS_Move_Flee;
extern EvtScript b_area_flo_crazee_dayzee_EVS_ReturnHome;
extern Stage b_area_flo_flo_01;
extern Stage b_area_flo_flo_01b;
extern Stage b_area_flo_flo_01c;
extern Stage b_area_flo_flo_02;
extern Stage b_area_flo_flo_02b;
extern Stage b_area_flo_flo_02c;
extern EvtScript b_area_flo_flo_03_EVS_PostBattle;
extern s32 b_area_flo_flo_03_ForegroundVineModels[];
extern EvtScript b_area_flo_flo_03_MakeSun;
extern u8 b_area_flo_flo_03_VineModels[];
extern Stage b_area_flo_flo_04;
extern Stage b_area_flo_flo_05;
extern Stage b_area_flo_flo_06;
extern EvtScript b_area_flo_flo_06_EVS_PostBattle;
extern s32 b_area_flo_green_magikoopa_BroomAnims[];
extern EvtScript b_area_flo_green_magikoopa_EVS_Flee;
extern EvtScript b_area_flo_green_magikoopa_EVS_HandleEvent;
extern EvtScript b_area_flo_green_magikoopa_EVS_Idle;
extern EvtScript b_area_flo_green_magikoopa_EVS_KnockDownCheck;
extern s32 b_area_flo_green_magikoopa_FlyingDefense[];
extern s32 b_area_flo_lakitu_DefenseTable[];
extern EvtScript b_area_flo_lakitu_EVS_CountActiveSummoners;
extern EvtScript b_area_flo_lakitu_EVS_Idle;
extern EvtScript b_area_flo_lakitu_EVS_ReturnHome;
extern s32 b_area_flo_lakitu_SpinyAnims[];
extern Vec3i b_area_flo_lakitu_SummonPos;
extern s32 b_area_flo_medi_guy_DefenseTable[];
extern EvtScript b_area_flo_medi_guy_EVS_FindInjuredActor;
extern EvtScript b_area_flo_medi_guy_EVS_HandleEvent;
extern EvtScript b_area_flo_medi_guy_EVS_Idle;
extern EvtScript b_area_flo_medi_guy_EVS_Move_HealOne;
extern EvtScript b_area_flo_medi_guy_EVS_ReturnHome;
extern s32 b_area_flo_medi_guy_StatusTable[];
extern s32 b_area_flo_red_magikoopa_DefenseTable[];
extern EvtScript b_area_flo_red_magikoopa_EVS_Flee;
extern EvtScript b_area_flo_red_magikoopa_EVS_HandleEvent;
extern EvtScript b_area_flo_red_magikoopa_EVS_Idle;
extern s32 b_area_flo_ruff_puff_DefenseTable[];
extern EvtScript b_area_flo_ruff_puff_EVS_HandleEvent;
extern EvtScript b_area_flo_ruff_puff_EVS_ReturnHome;
extern EvtScript b_area_flo_spiny_EVS_CheckToppleAnim;
extern EvtScript b_area_flo_spiny_EVS_Idle;
extern EvtScript b_area_flo_spiny_EVS_ReturnHome;
extern u8 b_area_flo_spiny_FlipPosOffsets[];
extern s32 b_area_flo_spiny_SpinyBallAnims[];
extern s32 b_area_flo_spiny_ToppledDefense[];
extern s32 b_area_flo_spiny_UprightDefense[];
extern s32 b_area_flo_white_magikoopa_DefenseTable_80223B20[];
extern EvtScript b_area_flo_white_magikoopa_EVS_Flee;
extern EvtScript b_area_flo_white_magikoopa_EVS_HandleEvent_Ground;
extern EvtScript b_area_flo_white_magikoopa_EVS_Idle;
extern s32 b_area_flo_yellow_magikoopa_BroomAnims[];
extern s32 b_area_flo_yellow_magikoopa_DefenseTable[];
extern EvtScript b_area_flo_yellow_magikoopa_EVS_Flee;
extern EvtScript b_area_flo_yellow_magikoopa_EVS_HandleEvent;
extern EvtScript b_area_flo_yellow_magikoopa_EVS_Idle;
extern EvtScript b_area_flo_yellow_magikoopa_EVS_KnockDownCheck;
extern s32 b_area_flo_yellow_magikoopa_FlyingDefense[];
extern EvtScript b_area_hos_ember_EVS_GetAvailableColumn;
extern EvtScript b_area_kmr_part_3_kpa_13_EVS_PreBattle;
extern EvtScript TTYD64_imp_18_Bzzap_Script_Swarm_18;
extern EvtScript TTYD64_imp_18_WMagikoopa_Script_HealOne_18;
extern EvtScript TTYD64_imp_18_Spiny_Script_HandleEvent_8021C2F4_18;
extern EvtScript TTYD64_imp_18_Spiny_Script_TakeTurn_8021CDC0_18;
extern EvtScript TTYD64_imp_18_Lakitu_Script_ThrowSpint_18;
extern EvtScript TTYD64_imp_18_MediGuy_Script_FlyingAttack_18;
extern EvtScript TTYD64_imp_18_RuffPuff_Script_RuffPuff_TackleAttack;
extern EvtScript TTYD64_imp_18_YMagikoopa_Script_TakeTurn_80230700_18;
extern EvtScript TTYD64_imp_18_RMagikoopa_Script_TakeTurn_802233E0_18;
extern EvtScript TTYD64_imp_18_GRNMagikoopa_Script_TakeTurn_80229DE0_18;
extern EvtScript TTYD64_imp_18_CrazeeDayzee_Script_Crazee_Sing_18;
extern EvtScript TTYD64_imp_18_Lakitu_Script_SummonSpiny_18;
extern EvtScript TTYD64_imp_18_WMagikoopa_Script_HealAll_18;
extern EvtScript TTYD64_imp_18_AmazyDayzee_Script_Amazy_Sing_18;
extern EvtScript TTYD64_imp_18_YMagikoopa_Script_YMagikoopa_WandStrike_18;
extern EvtScript TTYD64_imp_18_RMagikoopa_Script_RMagikoopa_WandStrike_18;
extern EvtScript TTYD64_imp_18_WMagikoopa_Script_WMagikoopa_WandStrike_18;
extern EvtScript TTYD64_imp_18_GRNMagikoopa_Script_GRNMagikoopa_WandStrike_18;
extern EvtScript TTYD64_imp_18_YMagikoopa_Script_HandleEvent_8022F0A4_18;
extern EvtScript TTYD64_imp_18_GRNMagikoopa_Script_HandleEvent_80228784_18;
extern EvtScript TTYD64_imp_18_RMagikoopa_Script_RMagikoopa_ShapeSpell_18;
extern EvtScript TTYD64_imp_18_YMagikoopa_Script_YMagikoopa_ShapeSpell_18;
extern EvtScript TTYD64_imp_18_GRNMagikoopa_Script_GRNMagikoopa_ShapeSpell_18;
extern EvtScript TTYD64_imp_18_WMagikoopa_Script_WMagikoopa_ShapeSpell_18;
extern EvtScript TTYD64_imp_18_RuffPuff_Script_RuffPuff_ThunderAttack;
extern EvtScript TTYD64_imp_18_Lakitu_Script_HandleEvent_8021A16C_18;
extern EvtScript TTYD64_imp_18_YMagikoopa_Script_8022EAA8_18;
extern EvtScript TTYD64_imp_18_GRNMagikoopa_Script_80228188_18;
extern EvtScript TTYD64_flo_Script_BeforeBattle_80232E48;
extern EvtScript TTYD64_imp_18_Bzzap_Script_Sting_18;
extern EvtScript TTYD64_imp_18_Bzzap_Script_Swarm_TinyBee_FlyToTarget;
extern Battle TTYD64_flo_FormationTable[];
extern EvtScript TTYD64_imp_18_Lakitu_Script_GetSpacesFree_18;
extern EvtScript TTYD64_imp_18_WMagikoopa_Script_TakeTurn_802274E4_18;
extern EvtScript TTYD64_imp_18_Lakitu_Script_Lakitu_PullOffSpiny;
extern EvtScript TTYD64_imp_18_RuffPuff_Script_RuffPuff_Static;
extern EvtScript TTYD64_flo_Script_80232C48;
extern EvtScript TTYD64_imp_18_Lakitu_Script_Lakitu_SpinyFallOff;
extern EvtScript TTYD64_flo_Script_80232A30;
extern EvtScript TTYD64_imp_18_CrazeeDayzee_Script_TakeTurn_8021E7BC_18;
extern EvtScript TTYD64_imp_18_Lakitu_Script_Lakitu_TryToPullSpiny;
extern EvtScript TTYD64_imp_18_Bzzap_Script_Init_8021EB34_18;
extern EvtScript TTYD64_imp_18_RuffPuff_Script_Idle_8022273C_18;
extern ActorPartBlueprint TTYD64_imp_18_Bzzap_PartsTable_8021EA34_18[];
extern s32 TTYD64_imp_18_GRNMagikoopa_StatusTable_80227878_18[];
extern s32 TTYD64_imp_18_YMagikoopa_StatusTable_8022E244_18[];
extern s32 TTYD64_imp_18_GRNMagikoopa_StatusTable_80227924_18[];
extern s32 TTYD64_imp_18_YMagikoopa_StatusTable_8022E198_18[];
extern s32 TTYD64_imp_18_Lakitu_StatusTable_80219F38_18[];
extern s32 TTYD64_imp_18_Spiny_StatusTable_8021BF8C_18[];
extern s32 TTYD64_imp_18_RuffPuff_StatusTable_802225F8_18[];
extern s32 TTYD64_imp_18_WMagikoopa_StatusTable_80223B38_18[];
extern s32 TTYD64_imp_18_RMagikoopa_StatusTable_80220E78_18[];
extern s32 TTYD64_imp_18_CrazeeDayzee_StatusTable_8021D7AC_18[];
extern s32 TTYD64_imp_18_Bzzap_StatusTable_8021E988_18[];
extern EvtScript TTYD64_imp_18_MediGuy_Script_Init_80223728_18;
extern EvtScript TTYD64_imp_18_YMagikoopa_Script_Init_802305B8_18;
extern EvtScript TTYD64_imp_18_GRNMagikoopa_Script_Init_80229D3C_18;
extern EvtScript TTYD64_imp_18_RMagikoopa_Script_Init_80223298_18;
extern EvtScript TTYD64_imp_18_YMagikoopa_Script_Init_8023065C_18;
extern EvtScript TTYD64_imp_18_AmazyDayzee_Script_TakeTurn_80222500_18;
extern EvtScript TTYD64_imp_18_RuffPuff_Script_TakeTurn_80222DE8_18;
extern EvtScript TTYD64_imp_18_Bzzap_Script_TakeTurn_8022139C_18;
extern EvtScript TTYD64_imp_18_MediGuy_Script_TakeTurn_80224B0C_18;
extern EvtScript TTYD64_imp_18_Spiny_Script_Init_8021C0A8_18;
extern FormationRow TTYD64_flo_Formation_0B[];
extern FormationRow TTYD64_flo_Formation_12[];
extern FormationRow TTYD64_flo_Formation_04[];
extern FormationRow TTYD64_flo_Formation_08[];
extern FormationRow TTYD64_flo_Formation_07[];
extern FormationRow TTYD64_flo_Formation_1E[];
extern FormationRow TTYD64_flo_Formation_20[];
extern FormationRow TTYD64_flo_Formation_25[];
extern ActorPartBlueprint TTYD64_imp_18_Lakitu_PartsTable_80219FE4_18[];
extern ActorPartBlueprint TTYD64_imp_18_YMagikoopa_PartsTable_8022E314_18[];
extern EvtScript TTYD64_imp_18_Lakitu_Script_TakeTurn_8021BD2C_18;
extern ActorPartBlueprint TTYD64_imp_18_GRNMagikoopa_PartsTable_802279F4_18[];
extern EvtScript TTYD64_imp_18_WMagikoopa_Script_Init_80225F58_18;
extern EvtScript TTYD64_imp_18_Lakitu_Script_Init_8021A078_18;
extern StageListRow TTYD64_flo_StageTable[];
extern FormationRow TTYD64_flo_Formation_0A[];
extern FormationRow TTYD64_flo_Formation_0D[];
extern FormationRow TTYD64_flo_Formation_0E[];
extern FormationRow TTYD64_flo_Formation_11[];
extern FormationRow TTYD64_flo_Formation_15[];
extern FormationRow TTYD64_flo_Formation_16[];
extern FormationRow TTYD64_flo_Formation_14[];
extern FormationRow TTYD64_flo_Formation_19[];
extern FormationRow TTYD64_flo_Formation_18[];
extern FormationRow TTYD64_flo_Formation_01[];
extern FormationRow TTYD64_flo_Formation_03[];
extern FormationRow TTYD64_flo_Formation_09[];
extern FormationRow TTYD64_flo_Formation_1B[];
extern FormationRow TTYD64_flo_Formation_1D[];
extern FormationRow TTYD64_flo_Formation_22[];
extern FormationRow TTYD64_flo_Formation_23[];
extern FormationRow TTYD64_flo_Formation_24[];
extern s32 TTYD64_imp_18_WMagikoopa_IdleAnimations_80223D70_18[];
extern EvtScript TTYD64_imp_18_CrazeeDayzee_Script_Init_8021D8F0_18;
extern s32 TTYD64_imp_18_CrazeeDayzee_IdleAnimations_8021D8A4_18[];
extern s32 TTYD64_imp_18_Bzzap_IdleAnimations_8021E930_18[];
extern s32 TTYD64_imp_18_GRNMagikoopa_IdleAnimations_80227AFC_18[];
extern EvtScript TTYD64_imp_18_RuffPuff_Script_Init_802226F0_18;
extern EvtScript TTYD64_imp_18_AmazyDayzee_Script_Init_80221590_18;
extern s32 TTYD64_imp_18_Lakitu_IdleAnimations_Lakitu_HoldingSpiny[];
extern s32 TTYD64_imp_18_RMagikoopa_IdleAnimations_802210B0_18[];
extern s32 TTYD64_imp_18_Lakitu_IdleAnimations_80219EC0_18[];
extern s32 TTYD64_imp_18_GRNMagikoopa_IdleAnimations_80227AB0_18[];
extern s32 TTYD64_imp_18_Spiny_IdleAnimations_8021BED0_18[];
extern s32 TTYD64_imp_18_YMagikoopa_IdleAnimations_8022E41C_18[];
extern s32 TTYD64_imp_18_YMagikoopa_IdleAnimations_8022E3D0_18[];
extern s32 TTYD64_imp_18_Spiny_IdleAnimations_8021BF1C_18[];
extern s32 TTYD64_imp_18_AmazyDayzee_IdleAnimations_80221544_18[];
extern s32 TTYD64_imp_18_MediGuy_IdleAnimations_802235D0_18[];
extern ActorPartBlueprint TTYD64_imp_18_Spiny_PartsTable_8021C038_18[];
extern s32 TTYD64_imp_18_RuffPuff_IdleAnimations_802225A0_18[];
extern FormationRow TTYD64_flo_Formation_0C[];
extern FormationRow TTYD64_flo_Formation_10[];
extern FormationRow TTYD64_flo_Formation_13[];
extern FormationRow TTYD64_flo_Formation_17[];
extern FormationRow TTYD64_flo_Formation_00[];
extern FormationRow TTYD64_flo_Formation_05[];
extern FormationRow TTYD64_flo_Formation_02[];
extern FormationRow TTYD64_flo_Formation_06[];
extern FormationRow TTYD64_flo_Formation_1A[];
extern FormationRow TTYD64_flo_Formation_1F[];
extern FormationRow TTYD64_flo_Formation_21[];
extern ActorBlueprint TTYD64_imp_18_YMagikoopa_18_YMagikoopa;
extern ActorBlueprint TTYD64_imp_18_Spiny_18_Spiny;
extern ActorBlueprint TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee;
extern ActorBlueprint TTYD64_imp_18_YMagikoopa_18_FlyingYMagikoopa;
extern Stage TTYD64_flo_Stage_Well;
extern ActorBlueprint TTYD64_imp_18_Lakitu_18_Lakitu;
extern ActorBlueprint TTYD64_imp_18_MediGuy_18_MediGuy;
extern ActorBlueprint TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee;
extern ActorBlueprint TTYD64_imp_18_RMagikoopa_18_RMagikoopa;
extern ActorBlueprint TTYD64_imp_18_WMagikoopa_18_WMagikoopa;
extern ActorBlueprint TTYD64_imp_18_Bzzap_18_Bzzap;
extern Stage TTYD64_flo_Stage_8023343C;
extern ActorBlueprint TTYD64_imp_18_RuffPuff_18_RuffPuff;
extern ActorBlueprint TTYD64_imp_18_GRNMagikoopa_18_FlyingGRNMagikoopa;
extern ActorPartBlueprint TTYD64_imp_18_RuffPuff_PartsTable_802226A4_18[];
extern ActorPartBlueprint TTYD64_imp_18_YMagikoopa_PartsTable_8022E2F0_18[];
extern ActorPartBlueprint TTYD64_imp_18_AmazyDayzee_PartsTable_802214F8_18[];
extern ActorPartBlueprint TTYD64_imp_18_WMagikoopa_PartsTable_80223C90_18[];
extern ActorPartBlueprint TTYD64_imp_18_MediGuy_PartsTable_802236DC_18[];
extern ActorPartBlueprint TTYD64_imp_18_RMagikoopa_PartsTable_80220FD0_18[];
extern ActorPartBlueprint TTYD64_imp_18_CrazeeDayzee_PartsTable_8021D858_18[];
extern FormationRow TTYD64_imp_18_Lakitu_SpecialFormation_8021B028_18[];
extern FormationRow TTYD64_flo_Formation_0F[];
extern FormationRow TTYD64_flo_Formation_1C[];
extern s32 TTYD64_imp_18_Spiny_IdleAnimations_Ball_18[];
extern s32 TTYD64_imp_18_Lakitu_IdleAnimations_80219F0C_18[];

// clang-format off
EvtScript TTYD64_imp_18_Bzzap_Script_Swarm_18 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVarD, 0)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetPartSounds, ACTOR_SELF, 2, 1, 0, 0)
    Call(SetPartSounds, ACTOR_SELF, 3, 1, 0, 0)
    Call(SetPartSounds, ACTOR_SELF, 4, 1, 0, 0)
    Call(SetPartSounds, ACTOR_SELF, 5, 1, 0, 0)
    Call(SetPartSounds, ACTOR_SELF, 6, 1, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8396)
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4B0005)
    Wait(40)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4B0001)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(PlaySound, 856)
    Set(LVar0, 2)
    ExecGetTID(TTYD64_imp_18_Bzzap_Script_Swarm_TinyBee_FlyToTarget, LVarA)
    Wait(11)
    Set(LVar0, 3)
    Exec(TTYD64_imp_18_Bzzap_Script_Swarm_TinyBee_FlyToTarget)
    Wait(11)
    Set(LVar0, 4)
    Exec(TTYD64_imp_18_Bzzap_Script_Swarm_TinyBee_FlyToTarget)
    Wait(11)
    Set(LVar0, 5)
    Exec(TTYD64_imp_18_Bzzap_Script_Swarm_TinyBee_FlyToTarget)
    Wait(11)
    Set(LVar0, 6)
    Exec(TTYD64_imp_18_Bzzap_Script_Swarm_TinyBee_FlyToTarget)
    Label(0)
    IsThreadRunning(LVarA, LVar0)
    Wait(1)
    IfEq(LVar0, 1)
        Goto(0)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Call(PlaySoundAtPart, ACTOR_SELF, 2, 8395)
                Call(SetAnimation, ACTOR_SELF, 2, 0x4B0004)
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(AddGoalPos, ACTOR_SELF, -30, -20, 1)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(3.0))
                Call(FlyPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, -10, 0)
                Call(SetAnimation, ACTOR_SELF, 2, 0x4B0003)
                Call(SetPartYaw, ACTOR_SELF, 2, 180)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 100)
                Add(LVar2, 100)
                Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
                Call(FlyPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, 10, 0)
                Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
                Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            EndThread
            Wait(11)
            Thread
                Call(PlaySoundAtPart, ACTOR_SELF, 3, 8395)
                Call(SetAnimation, ACTOR_SELF, 3, 0x4B0004)
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(AddGoalPos, ACTOR_SELF, -30, -20, 1)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetPartMoveSpeed, ACTOR_SELF, 3, Float(3.0))
                Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 0, -10, 0)
                Call(SetAnimation, ACTOR_SELF, 3, 0x4B0003)
                Call(SetPartYaw, ACTOR_SELF, 3, 180)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 100)
                Add(LVar2, 100)
                Call(AddActorDecoration, ACTOR_SELF, 3, 0, 2)
                Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 0, 10, 0)
                Call(RemoveActorDecoration, ACTOR_SELF, 3, 0)
                Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
            EndThread
            Wait(11)
            Thread
                Call(PlaySoundAtPart, ACTOR_SELF, 4, 8395)
                Call(SetAnimation, ACTOR_SELF, 4, 0x4B0004)
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(AddGoalPos, ACTOR_SELF, -30, -20, 1)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetPartMoveSpeed, ACTOR_SELF, 4, Float(3.0))
                Call(FlyPartTo, ACTOR_SELF, 4, LVar0, LVar1, LVar2, 0, -10, 0)
                Call(SetAnimation, ACTOR_SELF, 4, 0x4B0003)
                Call(SetPartYaw, ACTOR_SELF, 4, 180)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 100)
                Add(LVar2, 100)
                Call(AddActorDecoration, ACTOR_SELF, 4, 0, 2)
                Call(FlyPartTo, ACTOR_SELF, 4, LVar0, LVar1, LVar2, 0, 10, 0)
                Call(RemoveActorDecoration, ACTOR_SELF, 4, 0)
                Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 1)
            EndThread
            Wait(11)
            Thread
                Call(PlaySoundAtPart, ACTOR_SELF, 5, 8395)
                Call(SetAnimation, ACTOR_SELF, 5, 0x4B0004)
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(AddGoalPos, ACTOR_SELF, -30, -20, 1)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetPartMoveSpeed, ACTOR_SELF, 5, Float(3.0))
                Call(FlyPartTo, ACTOR_SELF, 5, LVar0, LVar1, LVar2, 0, -10, 0)
                Call(SetAnimation, ACTOR_SELF, 5, 0x4B0003)
                Call(SetPartYaw, ACTOR_SELF, 5, 180)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 100)
                Add(LVar2, 100)
                Call(AddActorDecoration, ACTOR_SELF, 5, 0, 2)
                Call(FlyPartTo, ACTOR_SELF, 5, LVar0, LVar1, LVar2, 0, 10, 0)
                Call(RemoveActorDecoration, ACTOR_SELF, 5, 0)
                Call(SetPartFlagBits, ACTOR_SELF, 5, 1, 1)
            EndThread
            Wait(11)
            Thread
                Call(PlaySoundAtPart, ACTOR_SELF, 6, 8395)
                Call(SetAnimation, ACTOR_SELF, 6, 0x4B0004)
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(AddGoalPos, ACTOR_SELF, -30, -20, 1)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(3.0))
                Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, -10, 0)
                Call(SetAnimation, ACTOR_SELF, 6, 0x4B0003)
                Call(SetPartYaw, ACTOR_SELF, 6, 180)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 100)
                Add(LVar2, 100)
                Call(AddActorDecoration, ACTOR_SELF, 6, 0, 2)
                Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 10, 0)
                Call(RemoveActorDecoration, ACTOR_SELF, 6, 0)
                Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
            EndThread
            Wait(11)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(30)
            Call(UseBattleCamPreset, 2)
            Wait(30)
            Call(StopSound, 856)
            Call(YieldTurn)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Call(PlaySoundAtPart, ACTOR_SELF, 2, 8395)
        Call(SetAnimation, ACTOR_SELF, 2, 0x4B0004)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, -10, -10, 1)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(3.0))
        Call(FlyPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, -10, 0)
        Wait(2)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 1, 16)
        Call(SetAnimation, ACTOR_SELF, 2, 0x4B0003)
        Call(SetPartYaw, ACTOR_SELF, 2, 180)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 100)
        Add(LVar2, 100)
        Call(FlyPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, 10, 0)
        Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
    EndThread
    Wait(11)
    Thread
        Call(PlaySoundAtPart, ACTOR_SELF, 3, 8395)
        Call(SetAnimation, ACTOR_SELF, 3, 0x4B0004)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, -10, -10, 1)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetPartMoveSpeed, ACTOR_SELF, 3, Float(3.0))
        Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 0, -10, 0)
        Wait(2)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 1, 64)
        Call(SetAnimation, ACTOR_SELF, 3, 0x4B0003)
        Call(SetPartYaw, ACTOR_SELF, 3, 180)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 100)
        Add(LVar2, 100)
        Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 0, 10, 0)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    EndThread
    Wait(11)
    Thread
        Call(PlaySoundAtPart, ACTOR_SELF, 4, 8395)
        Call(SetAnimation, ACTOR_SELF, 4, 0x4B0004)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, -10, -10, 1)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetPartMoveSpeed, ACTOR_SELF, 4, Float(3.0))
        Call(FlyPartTo, ACTOR_SELF, 4, LVar0, LVar1, LVar2, 0, -10, 0)
        Wait(2)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 1, 64)
        Call(SetAnimation, ACTOR_SELF, 4, 0x4B0003)
        Call(SetPartYaw, ACTOR_SELF, 4, 180)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 100)
        Add(LVar2, 100)
        Call(FlyPartTo, ACTOR_SELF, 4, LVar0, LVar1, LVar2, 0, 10, 0)
        Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 1)
    EndThread
    Wait(11)
    Thread
        Call(PlaySoundAtPart, ACTOR_SELF, 5, 8395)
        Call(SetAnimation, ACTOR_SELF, 5, 0x4B0004)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, -10, -10, 1)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetPartMoveSpeed, ACTOR_SELF, 5, Float(3.0))
        Call(FlyPartTo, ACTOR_SELF, 5, LVar0, LVar1, LVar2, 0, -10, 0)
        Wait(2)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 1, 64)
        Call(SetAnimation, ACTOR_SELF, 5, 0x4B0003)
        Call(SetPartYaw, ACTOR_SELF, 5, 180)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 100)
        Add(LVar2, 100)
        Call(FlyPartTo, ACTOR_SELF, 5, LVar0, LVar1, LVar2, 0, 10, 0)
        Call(SetPartFlagBits, ACTOR_SELF, 5, 1, 1)
    EndThread
    Wait(11)
    Wait(1)
    Call(PlaySoundAtPart, ACTOR_SELF, 6, 8395)
    Call(SetAnimation, ACTOR_SELF, 6, 0x4B0004)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -10, -10, 1)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(3.0))
    Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, -10, 0)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetAnimation, ACTOR_SELF, 6, 0x4B0003)
            Call(SetPartYaw, ACTOR_SELF, 6, 180)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 100)
            Add(LVar2, 100)
            Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 10, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
            Call(StopSound, 856)
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
EvtScript TTYD64_imp_18_WMagikoopa_Script_HealOne_18 = {
    Set(LVar8, 0)
    Set(LVar9, 9999)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetActorHP, LVar0, LVar2)
    Call(b_area_flo_white_magikoopa_GetBootsHammerLevel, LVar3, LVar4)
    IfGt(LVar3, LVar4)
        Set(LVar3, LVar4)
    EndIf
    Call(b_area_flo_white_magikoopa_GetActorDefense, LVar0, LVar1, LVar5)
    Call(GetActorDefenseBoost, LVar0, LVar6)
    Add(LVar5, LVar6)
    Sub(LVar3, LVar5)
    Sub(LVar2, LVar3)
    Call(b_area_flo_white_magikoopa_CheckMagikoopaCastTarget, LVar0, LVarA)
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
    Call(b_area_flo_white_magikoopa_GetBootsHammerLevel, LVar3, LVar4)
    IfGt(LVar3, LVar4)
        Set(LVar3, LVar4)
    EndIf
    Call(b_area_flo_white_magikoopa_GetActorDefense, LVar0, LVar1, LVar5)
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
            ExecWait(TTYD64_imp_18_WMagikoopa_Script_WMagikoopa_ShapeSpell_18)
        Else
            ExecWait(TTYD64_imp_18_WMagikoopa_Script_WMagikoopa_WandStrike_18)
        EndIf
        Return
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(3)
    EndIf
    ExecWait(b_area_flo_white_magikoopa_EVS_Flee)
    Return
    Label(100)
    Call(RandInt, 1000, LVar0)
    IfGt(LVar0, 750)
        Call(GetActorFlags, ACTOR_SELF, LVar0)
        IfFlag(LVar0, 512)
            ExecWait(TTYD64_imp_18_WMagikoopa_Script_WMagikoopa_ShapeSpell_18)
        Else
            ExecWait(TTYD64_imp_18_WMagikoopa_Script_WMagikoopa_WandStrike_18)
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
EvtScript TTYD64_imp_18_Spiny_Script_HandleEvent_8021C2F4_18 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0009)
            SetConst(LVar2, 0x4A000A)
            ExecWait(b_area_flo_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfNe(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A000B)
                SetConst(LVar2, 0x4A000C)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A000D)
                SetConst(LVar2, 0x4A000E)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            EndIf
        CaseEq(36)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfNe(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A000B)
                SetConst(LVar2, 0x4A000C)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A000C)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A000D)
                SetConst(LVar2, 0x4A000E)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A000E)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0009)
            SetConst(LVar2, 0x4A000A)
            ExecWait(b_area_flo_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0009)
            SetConst(LVar2, 0x4A000A)
            ExecWait(b_area_flo_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0009)
            SetConst(LVar2, 0x4A000A)
            ExecWait(b_area_flo_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(13)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfGt(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x4A0018)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(EnableIdleScript, ACTOR_SELF, 1)
                Call(UseIdleAnimation, ACTOR_SELF, 1)
                Return
            EndIf
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                Call(SetAnimation, ACTOR_SELF, 1, 0x4A000A)
            Else
                Call(SetAnimation, ACTOR_SELF, 1, 0x4A0016)
            EndIf
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(SetActorVar, ACTOR_SELF, 1, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_flo_spiny_ToppledDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_18_Spiny_IdleAnimations_8021BF1C_18))
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
                SetConst(LVar1, 0x4A0018)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(EnableIdleScript, ACTOR_SELF, 1)
                Call(UseIdleAnimation, ACTOR_SELF, 1)
                Return
            EndIf
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0006)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x4A0007)
                    Wait(10)
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0002)
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
            SetConst(LVar1, 0x4A0009)
            SetConst(LVar2, 0x4A000A)
            ExecWait(b_area_flo_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0009)
            SetConst(LVar2, 0x4A000A)
            ExecWait(b_area_flo_spiny_EVS_CheckToppleAnim)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0001)
                    ExecWait(Ref(EVS_Enemy_Recover))
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0002)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndSwitch
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0004)
                    SetConst(LVar2, 0x4A0009)
                    ExecWait(Ref(EVS_Enemy_ScareAway))
                    Return
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0002)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndSwitch
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0004)
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0002)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0004)
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x4A0002)
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
EvtScript TTYD64_imp_18_Spiny_Script_TakeTurn_8021CDC0_18 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(GetActorVar, ACTOR_SELF, 1, LVar0)
        Sub(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 1, LVar0)
        IfGt(LVar0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4A0014)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
        Else
            Call(SetAnimation, ACTOR_SELF, 1, 0x4A0014)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Wait(20)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x4A0002)
            SetConst(LVar2, 0x4A0001)
            ExecWait(Ref(EVS_Enemy_FlipBackUp))
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_flo_spiny_UprightDefense))
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_18_Spiny_IdleAnimations_8021BED0_18))
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x200000, 1)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
        EndIf
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfGt(LVar0, 0)
        Call(SetActorVar, ACTOR_SELF, 2, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x4A001A)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x4A0001)
        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_flo_spiny_UprightDefense))
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_18_Spiny_IdleAnimations_8021BED0_18))
        Return
    Else
        Call(GetBattlePhase, LVar0)
        IfNe(LVar0, 1)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 30)
                Call(SetActorVar, ACTOR_SELF, 2, 1)
                Call(SetAnimation, ACTOR_SELF, 1, 0x4A0019)
                Wait(20)
                Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_dgb_tubba_blubba_DefenseTable))
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_18_Spiny_IdleAnimations_Ball_18))
                Return
            EndIf
        EndIf
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, 1, 0x4A0019)
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 1, 0x4A0018)
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
    Call(SetAnimation, ACTOR_SELF, 2, 0x49000C)
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
            ExecWait(b_area_flo_spiny_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 4, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetAnimation, ACTOR_SELF, 2, 0x49000B)
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
            ExecWait(b_area_flo_spiny_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableActorBlur, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_Lakitu_Script_ThrowSpint_18 = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x490003)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, -20, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x490001)
    Call(SetAnimation, ACTOR_SELF, 2, 0x49020B)
    Call(SetAnimation, ACTOR_SELF, 1, 0x490012)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x490013)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x490015)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x490001)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 2, 0x49020C)
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
            ExecWait(b_area_flo_lakitu_EVS_ReturnHome)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
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
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
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
            ExecWait(b_area_flo_lakitu_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    ExecWait(TTYD64_imp_18_Lakitu_Script_Lakitu_TryToPullSpiny)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_MediGuy_Script_FlyingAttack_18 = {
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
                    Call(b_area_flo_medi_guy_MediGuySpriteRotationFunc, LVar0, LVar1, 15, 60, Float(30.0))
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
            ExecWait(b_area_flo_medi_guy_EVS_ReturnHome)
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
            ExecWait(b_area_flo_medi_guy_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_RuffPuff_Script_RuffPuff_TackleAttack = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0004)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 11)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0001)
    Wait(5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0005)
    Wait(5)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                SetF(LVar0, Float(0.0))
                Loop(15)
                    AddF(LVar0, Float(12.0))
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(AddGoalPos, ACTOR_SELF, -10, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                SetF(LVar0, Float(180.0))
                Loop(10)
                    AddF(LVar0, Float(18.0))
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(AddGoalPos, ACTOR_SELF, -30, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(AddGoalPos, ACTOR_SELF, -20, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(AddGoalPos, ACTOR_SELF, -10, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(b_area_flo_ruff_puff_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 13, 0)
        SetF(LVar0, Float(0.0))
        Loop(8)
            AddF(LVar0, Float(22.5))
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
    Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0xFFFF, 0, 4, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                SetF(LVar0, Float(180.0))
                Loop(10)
                    SubF(LVar0, Float(22.5))
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 30, 0, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(JumpWithBounce, ACTOR_SELF, 10, Float(5.0))
            Wait(10)
            Call(YieldTurn)
            ExecWait(b_area_flo_ruff_puff_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_YMagikoopa_Script_TakeTurn_80230700_18 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_flo_yellow_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
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
        ExecWait(b_area_flo_yellow_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        ExecWait(TTYD64_imp_18_YMagikoopa_Script_YMagikoopa_ShapeSpell_18)
    Else
        ExecWait(TTYD64_imp_18_YMagikoopa_Script_YMagikoopa_WandStrike_18)
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
EvtScript TTYD64_imp_18_RMagikoopa_Script_TakeTurn_802233E0_18 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_flo_red_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
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
        ExecWait(b_area_flo_red_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        ExecWait(TTYD64_imp_18_RMagikoopa_Script_RMagikoopa_ShapeSpell_18)
    Else
        ExecWait(TTYD64_imp_18_RMagikoopa_Script_RMagikoopa_WandStrike_18)
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
        Call(TTYD64_BoostAttack, LVar8, 1, 3)
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
EvtScript TTYD64_imp_18_GRNMagikoopa_Script_TakeTurn_80229DE0_18 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_flo_green_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
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
        ExecWait(b_area_flo_green_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        ExecWait(TTYD64_imp_18_GRNMagikoopa_Script_GRNMagikoopa_ShapeSpell_18)
    Else
        ExecWait(TTYD64_imp_18_GRNMagikoopa_Script_GRNMagikoopa_WandStrike_18)
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
EvtScript TTYD64_imp_18_CrazeeDayzee_Script_Crazee_Sing_18 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorPos, ACTOR_SELF, -20, LVar1, LVar2)
    Else
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(MoveBattleCamOver, 70)
        Set(LFlag0, 0)
        Label(0)
        IfEq(LFlag0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x48000E)
            Set(LFlag0, 1)
        Else
            Call(SetAnimation, ACTOR_SELF, 1, 0x48000F)
            Set(LFlag0, 0)
        EndIf
        Wait(1)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 20)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
        IfGt(LVar0, 0)
            Goto(0)
        EndIf
        IfEq(LFlag0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x48000E)
            Set(LFlag0, 1)
        Else
            Call(SetAnimation, ACTOR_SELF, 1, 0x48000F)
            Set(LFlag0, 0)
        EndIf
        Wait(1)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
        Call(SetGoalPos, ACTOR_SELF, -35, 0, 10)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x480001)
    Wait(10)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x480006)
        Wait(40)
        Call(SetAnimation, ACTOR_SELF, 1, 0x480007)
    EndThread
    Wait(20)
    Call(PlaySoundAtActor, ACTOR_SELF, 727)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 25)
    Add(LVar2, 2)
    Loop(13)
        Call(RandInt, 30, LVar3)
        Sub(LVar3, 15)
        Add(LVar3, LVar0)
        Call(PlayEffect_impl, 38, 1, LVar3, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(10)
    EndLoop
    Call(SetAnimation, ACTOR_SELF, 1, 0x480001)
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x18000000, 0, -0x7FFFECEC, 4, 32)
    EndSwitch
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0, 0, 1, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarF, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 10)
            Wait(20)
            Call(YieldTurn)
            ExecWait(b_area_flo_crazee_dayzee_EVS_ReturnHome)
            Return
        EndCaseGroup
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x18000000, 0, -0x7FFFECEC, 4, 32)
    EndSwitch
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 10)
            Wait(20)
            Call(YieldTurn)
            ExecWait(b_area_flo_crazee_dayzee_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_Lakitu_Script_SummonSpiny_18 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SummonEnemy, Ref(TTYD64_imp_18_Lakitu_SpecialFormation_8021B028_18), 0)
    Call(CopyStatusEffects, ACTOR_SELF, LVar0)
    Set(LVarB, LVar0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Wait(10)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x490015)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x490001)
    EndThread
    Call(UseBattleCamPreset, 2)
    Call(PlaySoundAtPart, ACTOR_SELF, 2, 8402)
    Call(SetPartSounds, ACTOR_SELF, 2, 2, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x49020C)
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
    Call(SetAnimation, LVarB, 1, 0x4A0001)
    Wait(20)
    Call(SetAnimation, LVarB, 1, 0x4A0004)
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
    Call(SetAnimation, LVarB, 1, 0x4A0001)
    Call(SetActorYaw, LVarB, 0)
    Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
    Call(ForceHomePos, LVarB, LVar0, LVar1, LVar2)
    Call(HPBarToHome, LVarB)
    Call(SetPartEventBits, ACTOR_SELF, -1, 0x200000, 0)
    Call(SetTargetOffset, ACTOR_SELF, -1, -5, 35)
    Call(SetIdleAnimations, ACTOR_SELF, -1, Ref(TTYD64_imp_18_Lakitu_IdleAnimations_80219EC0_18))
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_WMagikoopa_Script_HealAll_18 = {
    Call(RandInt, 1000, LVar0)
    IfGt(LVar0, 750)
        Call(GetActorFlags, ACTOR_SELF, LVar0)
        IfFlag(LVar0, 512)
            ExecWait(TTYD64_imp_18_WMagikoopa_Script_WMagikoopa_ShapeSpell_18)
        Else
            ExecWait(TTYD64_imp_18_WMagikoopa_Script_WMagikoopa_WandStrike_18)
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
EvtScript TTYD64_imp_18_AmazyDayzee_Script_Amazy_Sing_18 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorPos, ACTOR_SELF, -20, LVar1, LVar2)
    Else
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(MoveBattleCamOver, 70)
        Set(LFlag0, 0)
        Label(0)
        IfEq(LFlag0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x48010E)
            Set(LFlag0, 1)
        Else
            Call(SetAnimation, ACTOR_SELF, 1, 0x48010F)
            Set(LFlag0, 0)
        EndIf
        Wait(1)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 20)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
        IfGt(LVar0, 0)
            Goto(0)
        EndIf
        IfEq(LFlag0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x48010E)
            Set(LFlag0, 1)
        Else
            Call(SetAnimation, ACTOR_SELF, 1, 0x48010F)
            Set(LFlag0, 0)
        EndIf
        Wait(1)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
        Call(SetGoalPos, ACTOR_SELF, -35, 0, 10)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x480101)
    Wait(10)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x480106)
        Wait(40)
        Call(SetAnimation, ACTOR_SELF, 1, 0x480107)
    EndThread
    Wait(20)
    Call(PlaySoundAtActor, ACTOR_SELF, 727)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 25)
    Add(LVar2, 2)
    Loop(13)
        Call(RandInt, 30, LVar3)
        Sub(LVar3, 15)
        Add(LVar3, LVar0)
        Call(PlayEffect_impl, 38, 1, LVar3, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(10)
    EndLoop
    Call(SetAnimation, ACTOR_SELF, 1, 0x480101)
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x18000000, 0, -0x7FFFECF1, 20, 32)
    EndSwitch
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, 0, 0, 1, 16)
    Switch(LVarF)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarF, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x18000000, 0, -0x7FFFECF1, 20, 32)
    EndSwitch
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 10)
            Wait(20)
            Call(YieldTurn)
            ExecWait(b_area_flo_amazy_dayzee_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_YMagikoopa_Script_YMagikoopa_WandStrike_18 = {
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
EvtScript TTYD64_imp_18_RMagikoopa_Script_RMagikoopa_WandStrike_18 = {
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
EvtScript TTYD64_imp_18_WMagikoopa_Script_WMagikoopa_WandStrike_18 = {
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
EvtScript TTYD64_imp_18_GRNMagikoopa_Script_GRNMagikoopa_WandStrike_18 = {
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
EvtScript TTYD64_imp_18_YMagikoopa_Script_HandleEvent_8022F0A4_18 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            ExecWait(b_area_flo_yellow_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570204)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseOrEq(10)
        CaseOrEq(12)
            ExecWait(b_area_flo_yellow_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570204)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_imp_18_YMagikoopa_Script_8022EAA8_18)
        EndCaseGroup
        CaseOrEq(14)
        CaseOrEq(15)
            ExecWait(b_area_flo_yellow_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570205)
            SetConst(LVar2, 0x570206)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_imp_18_YMagikoopa_Script_8022EAA8_18)
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
            ExecWait(b_area_flo_yellow_magikoopa_EVS_Flee)
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
EvtScript TTYD64_imp_18_GRNMagikoopa_Script_HandleEvent_80228784_18 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            ExecWait(b_area_flo_green_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570404)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseOrEq(10)
        CaseOrEq(12)
            ExecWait(b_area_flo_green_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570404)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_imp_18_GRNMagikoopa_Script_80228188_18)
        EndCaseGroup
        CaseOrEq(14)
        CaseOrEq(15)
            ExecWait(b_area_flo_green_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570405)
            SetConst(LVar2, 0x570406)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_imp_18_GRNMagikoopa_Script_80228188_18)
        EndCaseGroup
        CaseEq(36)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570405)
            SetConst(LVar2, 0x570406)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570406)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570404)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570404)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570404)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570401)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570404)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570404)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570401)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570401)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570401)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570404)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570402)
            ExecWait(b_area_flo_green_magikoopa_EVS_Flee)
            Return
        CaseEq(58)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570402)
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
            SetConst(LVar1, 0x570404)
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
EvtScript TTYD64_imp_18_RMagikoopa_Script_RMagikoopa_ShapeSpell_18 = {
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
            Call(b_area_flo_red_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
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
    Call(b_area_flo_red_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
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
EvtScript TTYD64_imp_18_YMagikoopa_Script_YMagikoopa_ShapeSpell_18 = {
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
            Call(b_area_flo_yellow_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
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
    Call(b_area_flo_yellow_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
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
EvtScript TTYD64_imp_18_GRNMagikoopa_Script_GRNMagikoopa_ShapeSpell_18 = {
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
            Call(b_area_flo_green_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
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
    Call(b_area_flo_green_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
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
EvtScript TTYD64_imp_18_WMagikoopa_Script_WMagikoopa_ShapeSpell_18 = {
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
            Call(b_area_flo_white_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
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
    Call(b_area_flo_white_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
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
EvtScript TTYD64_imp_18_RuffPuff_Script_RuffPuff_ThunderAttack = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7D0002)
    Wait(5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    Call(PlaySoundAtActor, ACTOR_SELF, 891)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Add(LVar1, 13)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.5), 29, 0, 0, 0, 0, 0, 0, 0)
        Else
            Add(LVar1, 13)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.7998046875), 29, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Add(LVar1, 13)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.5), 29, 0, 0, 0, 0, 0, 0, 0)
        Else
            Add(LVar1, 13)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.7998046875), 29, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D000E)
    Thread
        Wait(15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x7D0001)
    EndThread
    Call(ClearStatusEffects, ACTOR_SELF)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Label(0)
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
            Call(battle_item_thunder_bolt_SpawnLightningFX)
            Wait(5)
            Call(StartRumble, 10)
            Call(ShakeCam, 1, 0, 5, Float(1.0))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000020, 0, 0, 4, 32)
    EndSwitch
    Call(TTYD64_GetMarioPos, LVar0)
    Call(GetOwnerTarget, LVar1, 0)
    IfEq(LVar0, 0)
        IfEq(LVar1, 0)
            Wait(1)
            Goto(1)
        EndIf
    Else
        IfEq(LVar1, 256)
            Wait(1)
            Goto(1)
        EndIf
    EndIf
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(GetOwnerTarget, LVar0, 0)
    IfEq(LVar0, 256)
        Call(TTYD64_GetPartnerHP_API, LVar1)
        IfGt(LVar1, 0)
            Wait(1)
            Goto(0)
        EndIf
    Else
        Goto(0)
    EndIf
    Label(1)
    Wait(10)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_Lakitu_Script_HandleEvent_8021A16C_18 = {
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
                Exec(TTYD64_imp_18_Lakitu_Script_Lakitu_SpinyFallOff)
            EndIf
        EndCaseGroup
    EndSwitch
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490004)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490005)
            SetConst(LVar2, 0x490006)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490005)
            SetConst(LVar2, 0x490006)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490004)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490004)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490004)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490004)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490004)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(b_area_flo_lakitu_EVS_ReturnHome)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490004)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490004)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490004)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490004)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(b_area_flo_lakitu_EVS_ReturnHome)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490003)
            SetConst(LVar2, 0x490004)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490004)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x490004)
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
EvtScript TTYD64_imp_18_YMagikoopa_Script_8022EAA8_18 = {
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
    Call(b_area_flo_yellow_magikoopa_StartRumbleWithParams, 150, 10)
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
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_flo_yellow_magikoopa_EVS_HandleEvent))
    Call(SetActorType, ACTOR_SELF, 85)
    Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_imp_18_YMagikoopa_StatusTable_8022E198_18))
    Call(b_area_flo_yellow_magikoopa_SetAbsoluteStatusOffsets, -10, 20, 10, 32)
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
EvtScript TTYD64_imp_18_GRNMagikoopa_Script_80228188_18 = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560404)
        Goto(0)
    EndIf
    Call(GetLastElement, LVar0)
    IfFlag(LVar0, 1024)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560404)
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
    Call(b_area_flo_green_magikoopa_StartRumbleWithParams, 150, 10)
    Thread
        Call(ShakeCam, 1, 0, 5, Float(0.7001953125))
    EndThread
    Call(GetLastEvent, ACTOR_SELF, LVar3)
    IfEq(LVar3, 15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560404)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x560401)
    Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_flo_green_magikoopa_EVS_HandleEvent))
    Call(SetActorType, ACTOR_SELF, 83)
    Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_imp_18_GRNMagikoopa_StatusTable_80227878_18))
    Call(b_area_flo_green_magikoopa_SetAbsoluteStatusOffsets, -10, 20, 10, 32)
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
EvtScript TTYD64_flo_Script_BeforeBattle_80232E48 = {
    Call(SetSpriteShading, -1)
    Call(SetCamBGColor, 1, 0, 0, 0)
    Set(LVar0, Ref(b_area_flo_flo_03_VineModels))
    Exec(TTYD64_flo_Script_80232A30)
    Call(SetTexPanner, 36, 1)
    Call(SetTexPanner, 37, 2)
    Call(SetTexPanner, 38, 3)
    Call(SetTexPanner, 39, 4)
    Call(SetTexPanner, 40, 5)
    Call(SetTexPanner, 41, 6)
    Call(SetTexPanner, 42, 7)
    Thread
        Set(LVarE, 1)
        Set(LVarF, 0)
        Loop(0)
            AddF(LVarF, LVarE)
            IfGe(LVarF, 1080)
                Set(LVarF, 0)
            EndIf
            Set(LVar0, LVarF)
            Div(LVar0, 9)
            Mod(LVar0, 2)
            Mul(LVar0, 0x4000)
            Set(LVar1, LVarF)
            Div(LVar1, 4)
            Mod(LVar1, 2)
            Mul(LVar1, 0x4000)
            Set(LVar2, LVarF)
            Div(LVar2, 5)
            Mod(LVar2, 2)
            Mul(LVar2, 0x4000)
            Set(LVar3, LVarF)
            Div(LVar3, 6)
            Mod(LVar3, 2)
            Mul(LVar3, 0x4000)
            Set(LVar4, LVarF)
            Div(LVar4, 2)
            Mod(LVar4, 2)
            Mul(LVar4, 0x4000)
            Set(LVar5, LVarF)
            Div(LVar5, 8)
            Mod(LVar5, 2)
            Mul(LVar5, 0x4000)
            Set(LVar6, LVarF)
            Div(LVar6, 8)
            Mod(LVar6, 2)
            Mul(LVar6, 0x8000)
            Call(SetTexPanOffset, 1, 0, LVar0, 0)
            Call(SetTexPanOffset, 2, 0, LVar1, 0)
            Call(SetTexPanOffset, 3, 0, LVar2, 0)
            Call(SetTexPanOffset, 4, 0, LVar3, 0)
            Call(SetTexPanOffset, 5, 0, LVar4, 0)
            Call(SetTexPanOffset, 6, 0, LVar5, 0)
            Call(SetTexPanOffset, 7, 0, LVar6, 0)
            Wait(1)
        EndLoop
    EndThread
    Thread
        Set(LVar0, 0)
        Loop(16)
            Set(LVar1, LVar0)
            Add(LVar1, 0x2710)
            Add(LVar0, 1)
            Call(CloneModel, 44, LVar1)
            Call(EnableModel, LVar1, 0)
        EndLoop
        Call(EnableModel, 44, 0)
        Set(LVarE, 0)
        Loop(0)
            SetF(LVar0, Float(106.0))
            SetF(LVar1, Float(94.0))
            SetF(LVar2, Float(-91.0))
            Call(RandInt, 100, LVar3)
            AddF(LVar3, -50)
            DivF(LVar3, Float(200.0))
            SetF(LVar4, Float(1.0))
            SetF(LVar5, 0)
            SetF(LVar6, Float(0.296875))
            SetF(LVar7, Float(0.296875))
            Set(LVarF, LVarE)
            Add(LVarF, 0x2710)
            Exec(TTYD64_flo_Script_80232C48)
            Add(LVarE, 1)
            IfGe(LVarE, 16)
                Set(LVarE, 0)
            EndIf
            Wait(10)
        EndLoop
    EndThread
    ExecWait(b_area_flo_flo_03_MakeSun)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_Bzzap_Script_Sting_18 = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x4B0003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 52, 10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 12)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Add(LVar2, 1)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
            Wait(5)
            Call(PlaySoundAtActor, ACTOR_SELF, 8394)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4B0004)
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(b_area_flo_bzzap_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Add(LVar2, 1)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8394)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4B0004)
    Wait(6)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, -0x7FFDFCD8, 6, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(20)
            Call(YieldTurn)
            ExecWait(b_area_flo_bzzap_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_Bzzap_Script_Swarm_TinyBee_FlyToTarget = {
    Set(LVar9, LVar0)
    Call(SetPartYaw, ACTOR_SELF, LVar9, 0)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Add(LVarA, 200)
    Add(LVarB, 100)
    Call(SetPartPos, ACTOR_SELF, LVar9, LVarA, LVarB, LVarC)
    Call(SetPartFlagBits, ACTOR_SELF, LVar9, 1, 0)
    Call(SetAnimation, ACTOR_SELF, LVar9, 0x4B0003)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Add(LVarB, 50)
    Sub(LVarC, 30)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar9, Float(6.0))
    Call(SetPartJumpGravity, ACTOR_SELF, LVar9, Float(1.0))
    Call(FlyPartTo, ACTOR_SELF, LVar9, LVarA, LVarB, LVarC, 0, -10, 0)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(GetPartOffset, ACTOR_SELF, LVar9, LVar6, LVar7, LVar8)
    Call(MakeLerp, 90, 450, 50, 0)
    Label(0)
    Call(UpdateLerp)
    Call(b_area_flo_bzzap_AddVecXZ, LVar3, LVar5, 30, LVar0, LVar6, LVar8)
    Call(SetPartPos, ACTOR_SELF, LVar9, LVar6, LVar7, LVar8)
    IfGt(LVar3, LVar6)
        Call(SetPartYaw, ACTOR_SELF, LVar9, 180)
    Else
        Call(SetPartYaw, ACTOR_SELF, LVar9, 0)
    EndIf
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    Call(GetOwnerTarget, LVarD, 0)
    Call(SetPartYaw, ACTOR_SELF, LVar9, 0)
    IfEq(LVar9, 2)
        Call(UseBattleCamPreset, 8)
        Call(SetBattleCamDist, 400)
        Call(SetBattleCamOffsetY, 30)
        Call(BattleCamTargetActor, LVarD)
        Call(MoveBattleCamOver, 60)
    EndIf
    Call(SetAnimation, ACTOR_SELF, LVar9, 0x4B0003)
    Call(GetActorPos, LVarD, LVarA, LVarB, LVarC)
    Add(LVarB, 30)
    Add(LVarC, 30)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar9, Float(6.0))
    Call(SetPartJumpGravity, ACTOR_SELF, LVar9, Float(1.0))
    Call(FlyPartTo, ACTOR_SELF, LVar9, LVarA, LVarB, LVarC, 0, -10, 0)
    Call(GetActorPos, LVarD, LVar3, LVar4, LVar5)
    Call(GetPartOffset, ACTOR_SELF, LVar9, LVar6, LVar7, LVar8)
    Call(MakeLerp, -90, -720, 100, 0)
    Label(1)
    Call(UpdateLerp)
    Call(b_area_flo_bzzap_AddVecXZ, LVar3, LVar5, 30, LVar0, LVar6, LVar8)
    Call(SetPartPos, ACTOR_SELF, LVar9, LVar6, LVar7, LVar8)
    IfGt(LVar3, LVar6)
        Call(SetPartYaw, ACTOR_SELF, LVar9, 180)
    Else
        Call(SetPartYaw, ACTOR_SELF, LVar9, 0)
    EndIf
    Wait(1)
    IfEq(LVar1, 1)
        Goto(1)
    EndIf
    Return
    End
};
// clang-format on

Battle TTYD64_flo_FormationTable[] = {
    { .name = "\270\345\262\340x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_flo_Formation_00,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\270\345\262\340x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_01,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\270\345\262\340,\257\342\257\342\374\363",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_flo_Formation_02,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\270\345\262\340,\317\303\301\374x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_03,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\270\345\262\340,\317\303\301\374,\270\345\262\340,\317\303\301\374",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_flo_Formation_04,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\270\345\262\340,\321\363\270\374",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_flo_Formation_05,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\270\345\262\340,\310\262\276\374",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_flo_Formation_06,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\270\345\262\340x\022,\310\262\276\374x\022",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_flo_Formation_07,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\270\345\262\340x\023,\310\262\276\374",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_flo_Formation_08,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\270\345\262\340x\022,\333\357\244\310\253\341\303\257",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_09,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\270\345\262\340x\022,\354\303\311\253\341\303\257",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_0A,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\270\345\262\340x\023,\244\250\355\374\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_flo_Formation_0B,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\310\262\276\374x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_flo_Formation_0C,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\310\262\276\374x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_0D,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\310\262\276\374,\321\363\270\374U\223,KDuO\330\244\333\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_0E,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\321\363\270\374U\223",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_flo_Formation_0F,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\321\363\270\374U\223x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_flo_Formation_10,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\321\363\270\374U\223x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_11,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\321\363\270\374U\223x4",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_flo_Formation_12,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\321\363\270\374U\223,\317\303\301\374",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_flo_Formation_13,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\321\363\270\374U\223,\317\303\301\374x2",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_14,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\321\363\270\374U\223x2,\317\303\301\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_15,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\321\363\270\374U\223x2,M\211\201O\321\363\270\374U\223",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_16,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\317\303\301\374x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_flo_Formation_17,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\317\303\301\374x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_18,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\317\303\301\374x2,\260\352\374\363\253\341\303\257\010]\211\011",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_19,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\317\303\301\374,\257\342\257\342\374\363",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_flo_Formation_1A,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\317\303\301\374,\257\342\257\342\374\363,\317\303\301\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_1B,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "M\211\201O\321\363\270\374U\223",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_flo_Formation_1C,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "M\211\201O\321\363\270\374U\223,\317\303\301\374x2",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_1D,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "M\211\201O\321\363\270\374U\223x\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_flo_Formation_1E,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\257\342\257\342\374\363x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_flo_Formation_1F,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\257\342\257\342\374\363x4",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_flo_Formation_20,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\257\342\257\342\374\363,\270\345\262\340",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_flo_Formation_21,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\257\342\257\342\374\363x\022,\317\303\301\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_22,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\257\342\257\342\374\363x\022,\321\363\270\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_23,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\257\342\257\342\374\363x\022,\244\250\355\374\253\341\303\257\010]\211\011",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo_Formation_24,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    { .name = "\257\342\257\342\374\363x\022,\244\250\355\374\253\341\303\257\010]\211\011",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_flo_Formation_25,
      .stage = &b_area_flo_flo_01,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_imp_18_Lakitu_Script_GetSpacesFree_18 = {
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
EvtScript TTYD64_imp_18_WMagikoopa_Script_TakeTurn_802274E4_18 = {
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_flo_white_magikoopa_EVS_Flee)
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
            ExecWait(TTYD64_imp_18_WMagikoopa_Script_HealAll_18)
        CaseEq(0)
            Call(GetActorFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 512)
                ExecWait(TTYD64_imp_18_WMagikoopa_Script_WMagikoopa_ShapeSpell_18)
            Else
                ExecWait(TTYD64_imp_18_WMagikoopa_Script_WMagikoopa_WandStrike_18)
            EndIf
        CaseDefault
            ExecWait(TTYD64_imp_18_WMagikoopa_Script_HealOne_18)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_Lakitu_Script_Lakitu_PullOffSpiny = {
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x49020B)
    Call(SetAnimation, ACTOR_SELF, 1, 0x490012)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x490013)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x490017)
    Call(SetPartEventBits, ACTOR_SELF, -1, 0x200000, 1)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Add(LVar0, 1)
    Call(SetActorVar, ACTOR_SELF, 0, LVar0)
    Call(SetIdleAnimations, ACTOR_SELF, -1, Ref(TTYD64_imp_18_Lakitu_IdleAnimations_Lakitu_HoldingSpiny))
    Call(SetTargetOffset, ACTOR_SELF, -1, -5, 50)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_RuffPuff_Script_RuffPuff_Static = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7D0005)
    Wait(5)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    Thread
        Wait(10)
        Loop(4)
            Call(PlaySoundAtActor, ACTOR_SELF, 978)
            Call(RandInt, 3, LVar0)
            Add(LVar0, 3)
            Wait(LVar0)
        EndLoop
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(ElectrifyActor, ACTOR_SELF, 99)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7D0001)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_flo_Script_80232C48 = {
    Call(EnableModel, LVarF, 1)
    Set(LVarE, 159)
    Loop(LVarE)
        AddF(LVar3, 0)
        AddF(LVar4, Float(0.0))
        SetF(LVar5, Float(0.009765625))
        AddF(LVar0, LVar3)
        AddF(LVar1, LVar4)
        AddF(LVar2, LVar5)
        MulF(LVar6, Float(1.009765625))
        AddF(LVar7, Float(0.009765625))
        SetF(LVar8, LVar6)
        Call(b_area_flo_flo_03_CosInterpMinMax, LVarE, LVarA, Float(0.0), Float(0.203125), 15, 0, 0)
        AddF(LVar8, LVarA)
        SetF(LVar9, LVar7)
        Call(b_area_flo_flo_03_CosInterpMinMax, LVarE, LVarA, Float(0.0), Float(0.203125), 20, 0, 90)
        AddF(LVar9, LVarA)
        SetF(LVarA, LVar0)
        MulF(LVarA, Float(10.0))
        Call(TranslateModel, LVarF, LVar0, LVar1, LVar2)
        Call(ScaleModel, LVarF, LVar8, LVar9, 1)
        Call(RotateModel, LVarF, LVarA, 0, 0, 1)
        Wait(1)
    EndLoop
    Call(EnableModel, LVarF, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_Lakitu_Script_Lakitu_SpinyFallOff = {
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
    Call(SetIdleAnimations, ACTOR_SELF, -1, Ref(TTYD64_imp_18_Lakitu_IdleAnimations_80219EC0_18))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_flo_Script_80232A30 = {
    Set(LVarA, LVar0)
    UseBuf(LVarA)
    Loop(0)
        BufRead1(LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
        Call(SetTexPanner, LVar0, 14)
        BufRead1(LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
        Call(SetTexPanner, LVar0, 15)
    EndLoop
    Set(LVar0, 0)
    Set(LVar1, 0)
    Label(0)
    Label(0)
    Add(LVar0, -140)
    IfLt(LVar0, 0)
        Add(LVar0, 0x10000)
    EndIf
    Call(SetTexPanOffset, 14, 0, LVar0, 0)
    Add(LVar1, -200)
    IfLt(LVar1, 0)
        Add(LVar1, 0x10000)
    EndIf
    Call(SetTexPanOffset, 15, 0, LVar1, 0)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_CrazeeDayzee_Script_TakeTurn_8021E7BC_18 = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_18_CrazeeDayzee_Script_Crazee_Sing_18)
        Return
    EndIf
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(RandInt, 100, LVar1)
    Switch(LVar0)
        CaseEq(1)
            IfLt(LVar1, 80)
                ExecWait(b_area_flo_crazee_dayzee_EVS_Move_Flee)
                Return
            EndIf
        CaseEq(2)
            IfLt(LVar1, 40)
                ExecWait(b_area_flo_crazee_dayzee_EVS_Move_Flee)
                Return
            EndIf
        CaseEq(3)
            IfLt(LVar1, 20)
                ExecWait(b_area_flo_crazee_dayzee_EVS_Move_Flee)
                Return
            EndIf
        CaseEq(4)
            IfLt(LVar1, 10)
                ExecWait(b_area_flo_crazee_dayzee_EVS_Move_Flee)
                Return
            EndIf
    EndSwitch
    ExecWait(TTYD64_imp_18_CrazeeDayzee_Script_Crazee_Sing_18)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_Lakitu_Script_Lakitu_TryToPullSpiny = {
    ExecWait(TTYD64_imp_18_Lakitu_Script_GetSpacesFree_18)
    IfEq(LVarB, 0)
        Return
    EndIf
    ExecWait(b_area_flo_lakitu_EVS_CountActiveSummoners)
    Switch(LVar9)
        CaseEq(1)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 700)
                ExecWait(TTYD64_imp_18_Lakitu_Script_Lakitu_PullOffSpiny)
            EndIf
        CaseEq(2)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 600)
                ExecWait(TTYD64_imp_18_Lakitu_Script_Lakitu_PullOffSpiny)
            EndIf
        CaseEq(3)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 500)
                ExecWait(TTYD64_imp_18_Lakitu_Script_Lakitu_PullOffSpiny)
            EndIf
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_Bzzap_Script_Init_8021EB34_18 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_18_Bzzap_Script_TakeTurn_8022139C_18))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_flo_bzzap_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_flo_bzzap_EVS_HandleEvent))
    Call(SetPartScale, ACTOR_SELF, 2, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Call(SetPartScale, ACTOR_SELF, 3, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Call(SetPartScale, ACTOR_SELF, 4, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Call(SetPartScale, ACTOR_SELF, 5, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Call(SetPartScale, ACTOR_SELF, 6, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_RuffPuff_Script_Idle_8022273C_18 = {
    Set(LVarF, 0)
    Loop(0)
        Call(b_area_flo_ruff_puff_CosInterpMinMax, LVarF, LVar0, Float(0.9697265625), Float(1.0302734375), 15, 0, 0)
        Call(b_area_flo_ruff_puff_CosInterpMinMax, LVarF, LVar1, Float(1.0302734375), Float(0.9697265625), 15, 0, 0)
        Add(LVarF, 1)
        Call(SetActorScale, ACTOR_SELF, LVar1, LVar0, Float(1.0))
        IfGe(LVarF, 30)
            Set(LVarF, 0)
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_imp_18_Bzzap_PartsTable_8021EA34_18[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -7, 33 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_Bzzap_IdleAnimations_8021E930_18,
        .defenseTable = b_area_flo_bzzap_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 2, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_Bzzap_IdleAnimations_8021E930_18,
        .defenseTable = b_area_flo_bzzap_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -5 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_Bzzap_IdleAnimations_8021E930_18,
        .defenseTable = b_area_flo_bzzap_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -5 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_Bzzap_IdleAnimations_8021E930_18,
        .defenseTable = b_area_flo_bzzap_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -5 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_Bzzap_IdleAnimations_8021E930_18,
        .defenseTable = b_area_flo_bzzap_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -5 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 6,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_Bzzap_IdleAnimations_8021E930_18,
        .defenseTable = b_area_flo_bzzap_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -5 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_imp_18_GRNMagikoopa_StatusTable_80227878_18[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  75, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_imp_18_YMagikoopa_StatusTable_8022E244_18[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  100, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,   33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_imp_18_GRNMagikoopa_StatusTable_80227924_18[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  100, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,   33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_imp_18_YMagikoopa_StatusTable_8022E198_18[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  75, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_imp_18_Lakitu_StatusTable_80219F38_18[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  100, 3,  0, 11, 50, 5,  50, 10, 75, 8, 80,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 1,  35, 0,   33, 0, 38, -1, 39, 0,  41, 0,  0,
};

s32 TTYD64_imp_18_Spiny_StatusTable_8021BF8C_18[] = {
    1,  0, 2,  0, 6,  60, 9,  50, 7,  75, 4,  75, 3,  0, 11, 50, 5,  75, 10, 75, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, 0,  0,
};

s32 TTYD64_imp_18_RuffPuff_StatusTable_802225F8_18[] = {
    1,  0, 2,  0, 6,  50, 9,  90, 7,  70, 4,  100, 3,  0, 11, 70, 5,  40, 10, 75, 8, 80,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,   33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_imp_18_WMagikoopa_StatusTable_80223B38_18[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  75, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_imp_18_RMagikoopa_StatusTable_80220E78_18[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  75, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_imp_18_CrazeeDayzee_StatusTable_8021D7AC_18[] = {
    1,  0, 2,  0, 6,  95, 9,  50, 7,  60, 4,  30, 3,  0, 11, 50, 5,  30, 10, 30, 8, 30,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 1,  39, 0,  41, 0,  0,
};

s32 TTYD64_imp_18_Bzzap_StatusTable_8021E988_18[] = {
    1,  0, 2,  0, 6,  60, 9,  50, 7,  80, 4,  100, 3,  0, 11, 0, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 1,  35, 0,   33, 0, 38, 0, 39, 0,  41, 0,  0,
};

// clang-format off
EvtScript TTYD64_imp_18_MediGuy_Script_Init_80223728_18 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_18_MediGuy_Script_TakeTurn_80224B0C_18))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_flo_medi_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_flo_medi_guy_EVS_HandleEvent))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar1, 5)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_YMagikoopa_Script_Init_802305B8_18 = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_flo_yellow_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_18_YMagikoopa_Script_TakeTurn_80230700_18))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_flo_yellow_magikoopa_EVS_HandleEvent))
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
EvtScript TTYD64_imp_18_GRNMagikoopa_Script_Init_80229D3C_18 = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_flo_green_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_18_GRNMagikoopa_Script_TakeTurn_80229DE0_18))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_18_GRNMagikoopa_Script_HandleEvent_80228784_18))
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
EvtScript TTYD64_imp_18_RMagikoopa_Script_Init_80223298_18 = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_flo_red_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_18_RMagikoopa_Script_TakeTurn_802233E0_18))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_flo_red_magikoopa_EVS_HandleEvent))
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
EvtScript TTYD64_imp_18_YMagikoopa_Script_Init_8023065C_18 = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_flo_yellow_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_18_YMagikoopa_Script_TakeTurn_80230700_18))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_18_YMagikoopa_Script_HandleEvent_8022F0A4_18))
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
EvtScript TTYD64_imp_18_AmazyDayzee_Script_TakeTurn_80222500_18 = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_18_AmazyDayzee_Script_Amazy_Sing_18)
        Return
    EndIf
    Call(RandInt, 1000, LVar0)
    Switch(LVar0)
        CaseLt(850)
            ExecWait(b_area_flo_amazy_dayzee_EVS_Move_Flee)
        CaseDefault
            ExecWait(TTYD64_imp_18_AmazyDayzee_Script_Amazy_Sing_18)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_RuffPuff_Script_TakeTurn_80222DE8_18 = {
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 8192)
        ExecWait(TTYD64_imp_18_RuffPuff_Script_RuffPuff_ThunderAttack)
        Return
    EndIf
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 60)
        ExecWait(TTYD64_imp_18_RuffPuff_Script_RuffPuff_TackleAttack)
    Else
        ExecWait(TTYD64_imp_18_RuffPuff_Script_RuffPuff_Static)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_Bzzap_Script_TakeTurn_8022139C_18 = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_18_Bzzap_Script_Sting_18)
        Return
    EndIf
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 500)
        ExecWait(TTYD64_imp_18_Bzzap_Script_Sting_18)
    Else
        ExecWait(TTYD64_imp_18_Bzzap_Script_Swarm_18)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_MediGuy_Script_TakeTurn_80224B0C_18 = {
    ExecWait(b_area_flo_medi_guy_EVS_FindInjuredActor)
    IfEq(LVar0, -1)
        ExecWait(TTYD64_imp_18_MediGuy_Script_FlyingAttack_18)
    Else
        Call(RandInt, 1000, LVarA)
        IfLt(LVarA, 600)
            ExecWait(b_area_flo_medi_guy_EVS_Move_HealOne)
        Else
            ExecWait(TTYD64_imp_18_MediGuy_Script_FlyingAttack_18)
        EndIf
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_Spiny_Script_Init_8021C0A8_18 = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_flo_spiny_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_18_Spiny_Script_TakeTurn_8021CDC0_18))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_18_Spiny_Script_HandleEvent_8021C2F4_18))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_flo_Formation_0B[] = {
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_YMagikoopa_18_YMagikoopa,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_flo_Formation_12[] = {
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
};

FormationRow TTYD64_flo_Formation_04[] = {
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
};

FormationRow TTYD64_flo_Formation_08[] = {
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Spiny_18_Spiny,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
};

FormationRow TTYD64_flo_Formation_07[] = {
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Spiny_18_Spiny,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
    { .actor = &TTYD64_imp_18_Spiny_18_Spiny,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
};

FormationRow TTYD64_flo_Formation_1E[] = {
    { .actor = &TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_AMAZYDAYZEE },
    { .actor = &TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_AMAZYDAYZEE },
    { .actor = &TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_AMAZYDAYZEE },
    { .actor = &TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_AMAZYDAYZEE },
};

FormationRow TTYD64_flo_Formation_20[] = {
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
};

FormationRow TTYD64_flo_Formation_25[] = {
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

ActorPartBlueprint TTYD64_imp_18_Lakitu_PartsTable_80219FE4_18[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -5, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_Lakitu_IdleAnimations_80219EC0_18,
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
        .idleAnimations = TTYD64_imp_18_Lakitu_IdleAnimations_80219F0C_18,
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
        .idleAnimations = b_area_flo_lakitu_SpinyAnims,
        .defenseTable = b_area_flo_lakitu_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_18_YMagikoopa_PartsTable_8022E314_18[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_YMagikoopa_IdleAnimations_8022E3D0_18,
        .defenseTable = b_area_flo_yellow_magikoopa_FlyingDefense,
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
        .idleAnimations = TTYD64_imp_18_YMagikoopa_IdleAnimations_8022E41C_18,
        .defenseTable = b_area_flo_yellow_magikoopa_FlyingDefense,
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
        .idleAnimations = b_area_flo_yellow_magikoopa_BroomAnims,
        .defenseTable = b_area_flo_yellow_magikoopa_FlyingDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_imp_18_Lakitu_Script_TakeTurn_8021BD2C_18 = {
    Call(GetPartEventFlags, ACTOR_SELF, -1, LVar0)
    IfFlag(LVar0, 0x200000)
        ExecWait(b_area_hos_ember_EVS_GetAvailableColumn)
        ExecWait(TTYD64_imp_18_Lakitu_Script_SummonSpiny_18)
        Return
    EndIf
    ExecWait(TTYD64_imp_18_Lakitu_Script_ThrowSpint_18)
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_imp_18_GRNMagikoopa_PartsTable_802279F4_18[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_GRNMagikoopa_IdleAnimations_80227AB0_18,
        .defenseTable = b_area_flo_green_magikoopa_FlyingDefense,
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
        .idleAnimations = TTYD64_imp_18_GRNMagikoopa_IdleAnimations_80227AFC_18,
        .defenseTable = b_area_flo_green_magikoopa_FlyingDefense,
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
        .idleAnimations = b_area_flo_green_magikoopa_BroomAnims,
        .defenseTable = b_area_flo_green_magikoopa_FlyingDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_imp_18_WMagikoopa_Script_Init_80225F58_18 = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_flo_white_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_18_WMagikoopa_Script_TakeTurn_802274E4_18))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_flo_white_magikoopa_EVS_HandleEvent_Ground))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_Lakitu_Script_Init_8021A078_18 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_18_Lakitu_Script_TakeTurn_8021BD2C_18))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_flo_lakitu_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_18_Lakitu_Script_HandleEvent_8021A16C_18))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

StageListRow TTYD64_flo_StageTable[] = {
    { .name = "flo_01", .stage = &b_area_flo_flo_01 },         { .name = "flo_01b", .stage = &b_area_flo_flo_01b },
    { .name = "flo_01c", .stage = &b_area_flo_flo_01c },       { .name = "flo_02", .stage = &b_area_flo_flo_02 },
    { .name = "flo_02b", .stage = &b_area_flo_flo_02b },       { .name = "flo_02c", .stage = &b_area_flo_flo_02c },
    { .name = "flo_03", .stage = &TTYD64_flo_Stage_8023343C }, { .name = "flo_04", .stage = &b_area_flo_flo_04 },
    { .name = "flo_05", .stage = &b_area_flo_flo_05 },         { .name = "flo_06", .stage = &b_area_flo_flo_06 },
    { .name = "flo_28", .stage = &TTYD64_flo_Stage_Well },     {},
};

FormationRow TTYD64_flo_Formation_0A[] = {
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_RMagikoopa_18_RMagikoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_flo_Formation_0D[] = {
    { .actor = &TTYD64_imp_18_Spiny_18_Spiny,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
    { .actor = &TTYD64_imp_18_Spiny_18_Spiny,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
    { .actor = &TTYD64_imp_18_Spiny_18_Spiny,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
};

FormationRow TTYD64_flo_Formation_0E[] = {
    { .actor = &TTYD64_imp_18_Spiny_18_Spiny,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_MediGuy_18_MediGuy,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MEDIGUY },
};

FormationRow TTYD64_flo_Formation_11[] = {
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
};

FormationRow TTYD64_flo_Formation_15[] = {
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
};

FormationRow TTYD64_flo_Formation_16[] = {
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_AMAZYDAYZEE },
};

FormationRow TTYD64_flo_Formation_14[] = {
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
};

FormationRow TTYD64_flo_Formation_19[] = {
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_GRNMagikoopa_18_FlyingGRNMagikoopa,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_flo_Formation_18[] = {
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
};

FormationRow TTYD64_flo_Formation_01[] = {
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
};

FormationRow TTYD64_flo_Formation_03[] = {
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
};

FormationRow TTYD64_flo_Formation_09[] = {
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_WMagikoopa_18_WMagikoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_flo_Formation_1B[] = {
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
};

FormationRow TTYD64_flo_Formation_1D[] = {
    { .actor = &TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_AMAZYDAYZEE },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
};

FormationRow TTYD64_flo_Formation_22[] = {
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
};

FormationRow TTYD64_flo_Formation_23[] = {
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
};

FormationRow TTYD64_flo_Formation_24[] = {
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_YMagikoopa_18_FlyingYMagikoopa,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

s32 TTYD64_imp_18_WMagikoopa_IdleAnimations_80223D70_18[] = {
    1,  0x560301, 7, 0x560300, 6, 0x560308, 9, 0x560301, 8, 0x560300,
    11, 0x560301, 5, 0x560300, 4, 0x560307, 3, 0x560307, 0,
};

// clang-format off
EvtScript TTYD64_imp_18_CrazeeDayzee_Script_Init_8021D8F0_18 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_18_CrazeeDayzee_Script_TakeTurn_8021E7BC_18))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_flo_crazee_dayzee_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_flo_crazee_dayzee_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_18_CrazeeDayzee_IdleAnimations_8021D8A4_18[] = {
    1,  0x480001, 7, 0x480000, 6, 0x48000C, 9, 0x480001, 8, 0x480000,
    11, 0x480001, 5, 0x480000, 4, 0x48000B, 3, 0x48000B, 0,
};

s32 TTYD64_imp_18_Bzzap_IdleAnimations_8021E930_18[] = {
    1,  0x4B0001, 7, 0x4B0000, 6, 0x4B0009, 9, 0x4B0001, 8, 0x4B0000,
    11, 0x4B0001, 5, 0x4B0000, 4, 0x4B000A, 3, 0x4B000A, 0,
};

s32 TTYD64_imp_18_GRNMagikoopa_IdleAnimations_80227AFC_18[] = {
    1,  0x570401, 7, 0x570400, 6, 0x570408, 9, 0x570401, 8, 0x570400,
    11, 0x570401, 5, 0x570400, 4, 0x570407, 3, 0x570407, 0,
};

// clang-format off
EvtScript TTYD64_imp_18_RuffPuff_Script_Init_802226F0_18 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_18_RuffPuff_Script_TakeTurn_80222DE8_18))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_18_RuffPuff_Script_Idle_8022273C_18))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_flo_ruff_puff_EVS_HandleEvent))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_18_AmazyDayzee_Script_Init_80221590_18 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_18_AmazyDayzee_Script_TakeTurn_80222500_18))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_flo_amazy_dayzee_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_flo_amazy_dayzee_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_18_Lakitu_IdleAnimations_Lakitu_HoldingSpiny[] = {
    1,  0x490017, 7, 0x490000, 6, 0x490008, 9, 0x490001, 8, 0x490000,
    11, 0x490001, 5, 0x490000, 4, 0x490009, 3, 0x490009, 0,
};

s32 TTYD64_imp_18_RMagikoopa_IdleAnimations_802210B0_18[] = {
    1,  0x560101, 7, 0x560100, 6, 0x560108, 9, 0x560101, 8, 0x560100,
    11, 0x560101, 5, 0x560100, 4, 0x560107, 3, 0x560107, 0,
};

s32 TTYD64_imp_18_Lakitu_IdleAnimations_80219EC0_18[] = {
    1,  0x490001, 7, 0x490000, 6, 0x490008, 9, 0x490001, 8, 0x490000,
    11, 0x490001, 5, 0x490000, 4, 0x490009, 3, 0x490009, 0,
};

s32 TTYD64_imp_18_GRNMagikoopa_IdleAnimations_80227AB0_18[] = {
    1,  0x560401, 7, 0x560400, 6, 0x560408, 9, 0x560401, 8, 0x560400,
    11, 0x560401, 5, 0x560400, 4, 0x560407, 3, 0x560407, 0,
};

s32 TTYD64_imp_18_Spiny_IdleAnimations_8021BED0_18[] = {
    1,  0x4A0001, 7, 0x4A0000, 6, 0x4A0010, 9, 0x4A0001, 8, 0x4A0000,
    11, 0x4A0001, 5, 0x4A0000, 4, 0x4A0012, 3, 0x4A0012, 0,
};

s32 TTYD64_imp_18_YMagikoopa_IdleAnimations_8022E41C_18[] = {
    1,  0x570201, 7, 0x570200, 6, 0x570208, 9, 0x570201, 8, 0x570200,
    11, 0x570201, 5, 0x570200, 4, 0x570207, 3, 0x570207, 0,
};

s32 TTYD64_imp_18_YMagikoopa_IdleAnimations_8022E3D0_18[] = {
    1,  0x560201, 7, 0x560200, 6, 0x560208, 9, 0x560201, 8, 0x560200,
    11, 0x560201, 5, 0x560200, 4, 0x560207, 3, 0x560207, 0,
};

s32 TTYD64_imp_18_Spiny_IdleAnimations_8021BF1C_18[] = {
    1,  0x4A0002, 7, 0x4A0015, 6, 0x4A0011, 9, 0x4A0002, 8, 0x4A0015,
    11, 0x4A0002, 5, 0x4A0015, 4, 0x4A0013, 3, 0x4A0013, 0,
};

s32 TTYD64_imp_18_AmazyDayzee_IdleAnimations_80221544_18[] = {
    1,  0x480101, 7, 0x480100, 6, 0x48010C, 9, 0x480101, 8, 0x480100,
    11, 0x480101, 5, 0x480100, 4, 0x48010B, 3, 0x48010B, 0,
};

s32 TTYD64_imp_18_MediGuy_IdleAnimations_802235D0_18[] = {
    1,  0x400001, 7, 0x400000, 6, 0x400004, 9, 0x400001, 8, 0x400000,
    11, 0x400001, 5, 0x400000, 4, 0x40000A, 3, 0x40000A, 0,
};

ActorPartBlueprint TTYD64_imp_18_Spiny_PartsTable_8021C038_18[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_Spiny_IdleAnimations_8021BED0_18,
        .defenseTable = b_area_flo_spiny_UprightDefense,
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
        .idleAnimations = b_area_flo_spiny_SpinyBallAnims,
        .defenseTable = b_area_flo_spiny_UprightDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_imp_18_RuffPuff_IdleAnimations_802225A0_18[] = {
    1, 0x7D0001, 7, 0x7D0000, 6, 0x7D0009, 9, 0x7D0001, 8, 0x7D0000, 11, 0x7D0001, 5, 0x7D0000, 4, 0x7D000B, 0,
};

FormationRow TTYD64_flo_Formation_0C[] = {
    { .actor = &TTYD64_imp_18_Spiny_18_Spiny,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
    { .actor = &TTYD64_imp_18_Spiny_18_Spiny,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
};

FormationRow TTYD64_flo_Formation_10[] = {
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
};

FormationRow TTYD64_flo_Formation_13[] = {
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
};

FormationRow TTYD64_flo_Formation_17[] = {
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
};

FormationRow TTYD64_flo_Formation_00[] = {
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
};

FormationRow TTYD64_flo_Formation_05[] = {
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
};

FormationRow TTYD64_flo_Formation_02[] = {
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
};

FormationRow TTYD64_flo_Formation_06[] = {
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
    { .actor = &TTYD64_imp_18_Spiny_18_Spiny,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPINY },
};

FormationRow TTYD64_flo_Formation_1A[] = {
    { .actor = &TTYD64_imp_18_Bzzap_18_Bzzap,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
};

FormationRow TTYD64_flo_Formation_1F[] = {
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
};

FormationRow TTYD64_flo_Formation_21[] = {
    { .actor = &TTYD64_imp_18_RuffPuff_18_RuffPuff,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_RUFFPUFF },
    { .actor = &TTYD64_imp_18_Lakitu_18_Lakitu,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_LAKITU },
};

ActorBlueprint TTYD64_imp_18_YMagikoopa_18_YMagikoopa = {
    .flags = 0x0,
    .maxHP = 11,
    .type = 0x55,
    .level = 21,
    .partCount = 1,
    .partsData = TTYD64_imp_18_YMagikoopa_PartsTable_8022E2F0_18,
    .initScript = &TTYD64_imp_18_YMagikoopa_Script_Init_802305B8_18,
    .statusTable = TTYD64_imp_18_YMagikoopa_StatusTable_8022E198_18,
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

ActorBlueprint TTYD64_imp_18_Spiny_18_Spiny = {
    .flags = 0x0,
    .maxHP = 5,
    .type = 0x2F,
    .level = 19,
    .partCount = 2,
    .partsData = TTYD64_imp_18_Spiny_PartsTable_8021C038_18,
    .initScript = &TTYD64_imp_18_Spiny_Script_Init_8021C0A8_18,
    .statusTable = TTYD64_imp_18_Spiny_StatusTable_8021BF8C_18,
    .escapeChance = 60,
    .airLiftChance = 75,
    .hurricaneChance = 75,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 24, 24 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x32,
    .level = 19,
    .partCount = 1,
    .partsData = TTYD64_imp_18_CrazeeDayzee_PartsTable_8021D858_18,
    .initScript = &TTYD64_imp_18_CrazeeDayzee_Script_Init_8021D8F0_18,
    .statusTable = TTYD64_imp_18_CrazeeDayzee_StatusTable_8021D7AC_18,
    .escapeChance = 50,
    .airLiftChance = 85,
    .hurricaneChance = 80,
    .spookChance = 100,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 2,
    .size = { 32, 34 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -14, 17 },
    .statusTextOffset = { 9, 25 },
};

ActorBlueprint TTYD64_imp_18_YMagikoopa_18_FlyingYMagikoopa = {
    .flags = 0x200,
    .maxHP = 11,
    .type = 0x56,
    .level = 21,
    .partCount = 3,
    .partsData = TTYD64_imp_18_YMagikoopa_PartsTable_8022E314_18,
    .initScript = &TTYD64_imp_18_YMagikoopa_Script_Init_8023065C_18,
    .statusTable = TTYD64_imp_18_YMagikoopa_StatusTable_8022E244_18,
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

Stage TTYD64_flo_Stage_Well = {
    .texture = "flo_tex",
    .shape = "flo_bt07_shape",
    .hit = "flo_bt07_hit",
    .preBattle = &b_area_kmr_part_3_kpa_13_EVS_PreBattle,
    .postBattle = &b_area_flo_flo_06_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_imp_18_Lakitu_18_Lakitu = {
    .flags = 0x200,
    .maxHP = 12,
    .type = 0x2E,
    .level = 20,
    .partCount = 3,
    .partsData = TTYD64_imp_18_Lakitu_PartsTable_80219FE4_18,
    .initScript = &TTYD64_imp_18_Lakitu_Script_Init_8021A078_18,
    .statusTable = TTYD64_imp_18_Lakitu_StatusTable_80219F38_18,
    .escapeChance = 40,
    .airLiftChance = 90,
    .hurricaneChance = 90,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 2,
    .size = { 32, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -11, 20 },
    .statusTextOffset = { 10, 34 },
};

ActorBlueprint TTYD64_imp_18_MediGuy_18_MediGuy = {
    .flags = 0x200,
    .maxHP = 7,
    .type = 0x22,
    .level = 14,
    .partCount = 1,
    .partsData = TTYD64_imp_18_MediGuy_PartsTable_802236DC_18,
    .initScript = &TTYD64_imp_18_MediGuy_Script_Init_80223728_18,
    .statusTable = b_area_flo_medi_guy_StatusTable,
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

ActorBlueprint TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee = {
    .flags = 0x0,
    .maxHP = 20,
    .type = 0x33,
    .level = 100,
    .partCount = 1,
    .partsData = TTYD64_imp_18_AmazyDayzee_PartsTable_802214F8_18,
    .initScript = &TTYD64_imp_18_AmazyDayzee_Script_Init_80221590_18,
    .statusTable = b_area_flo_amazy_dayzee_StatusTable,
    .escapeChance = 90,
    .airLiftChance = 85,
    .hurricaneChance = 80,
    .spookChance = 100,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 70,
    .coinReward = 5,
    .size = { 32, 34 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -14, 17 },
    .statusTextOffset = { 9, 25 },
};

ActorBlueprint TTYD64_imp_18_RMagikoopa_18_RMagikoopa = {
    .flags = 0x0,
    .maxHP = 11,
    .type = 0x51,
    .level = 21,
    .partCount = 1,
    .partsData = TTYD64_imp_18_RMagikoopa_PartsTable_80220FD0_18,
    .initScript = &TTYD64_imp_18_RMagikoopa_Script_Init_80223298_18,
    .statusTable = TTYD64_imp_18_RMagikoopa_StatusTable_80220E78_18,
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

ActorBlueprint TTYD64_imp_18_WMagikoopa_18_WMagikoopa = {
    .flags = 0x0,
    .maxHP = 11,
    .type = 0x59,
    .level = 21,
    .partCount = 1,
    .partsData = TTYD64_imp_18_WMagikoopa_PartsTable_80223C90_18,
    .initScript = &TTYD64_imp_18_WMagikoopa_Script_Init_80225F58_18,
    .statusTable = TTYD64_imp_18_WMagikoopa_StatusTable_80223B38_18,
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

ActorBlueprint TTYD64_imp_18_Bzzap_18_Bzzap = {
    .flags = 0x200,
    .maxHP = 3,
    .type = 0x31,
    .level = 19,
    .partCount = 6,
    .partsData = TTYD64_imp_18_Bzzap_PartsTable_8021EA34_18,
    .initScript = &TTYD64_imp_18_Bzzap_Script_Init_8021EB34_18,
    .statusTable = TTYD64_imp_18_Bzzap_StatusTable_8021E988_18,
    .escapeChance = 40,
    .airLiftChance = 95,
    .hurricaneChance = 95,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 38, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

Stage TTYD64_flo_Stage_8023343C = {
    .texture = "flo_tex",
    .shape = "flo_bt03_shape",
    .hit = "flo_bt03_hit",
    .preBattle = &TTYD64_flo_Script_BeforeBattle_80232E48,
    .postBattle = &b_area_flo_flo_03_EVS_PostBattle,
    .bg = "fla_bg",
    .foregroundModelList = b_area_flo_flo_03_ForegroundVineModels,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_imp_18_RuffPuff_18_RuffPuff = {
    .flags = 0x200,
    .maxHP = 10,
    .type = 0x34,
    .level = 19,
    .partCount = 1,
    .partsData = TTYD64_imp_18_RuffPuff_PartsTable_802226A4_18,
    .initScript = &TTYD64_imp_18_RuffPuff_Script_Init_802226F0_18,
    .statusTable = TTYD64_imp_18_RuffPuff_StatusTable_802225F8_18,
    .escapeChance = 50,
    .airLiftChance = 90,
    .hurricaneChance = 90,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 32, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_18_GRNMagikoopa_18_FlyingGRNMagikoopa = {
    .flags = 0x200,
    .maxHP = 11,
    .type = 0x54,
    .level = 21,
    .partCount = 3,
    .partsData = TTYD64_imp_18_GRNMagikoopa_PartsTable_802279F4_18,
    .initScript = &TTYD64_imp_18_GRNMagikoopa_Script_Init_80229D3C_18,
    .statusTable = TTYD64_imp_18_GRNMagikoopa_StatusTable_80227924_18,
    .escapeChance = 40,
    .airLiftChance = 95,
    .hurricaneChance = 75,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 2,
    .size = { 48, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -25, 20 },
    .statusTextOffset = { 1, 34 },
};

ActorPartBlueprint TTYD64_imp_18_RuffPuff_PartsTable_802226A4_18[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 26 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_RuffPuff_IdleAnimations_802225A0_18,
        .defenseTable = b_area_flo_ruff_puff_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -13 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_18_YMagikoopa_PartsTable_8022E2F0_18[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_YMagikoopa_IdleAnimations_8022E3D0_18,
        .defenseTable = b_area_flo_yellow_magikoopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_18_AmazyDayzee_PartsTable_802214F8_18[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 30 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_AmazyDayzee_IdleAnimations_80221544_18,
        .defenseTable = b_area_flo_amazy_dayzee_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_18_WMagikoopa_PartsTable_80223C90_18[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_WMagikoopa_IdleAnimations_80223D70_18,
        .defenseTable = b_area_flo_white_magikoopa_DefenseTable_80223B20,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_18_MediGuy_PartsTable_802236DC_18[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 38 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_MediGuy_IdleAnimations_802235D0_18,
        .defenseTable = b_area_flo_medi_guy_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -5 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_18_RMagikoopa_PartsTable_80220FD0_18[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_RMagikoopa_IdleAnimations_802210B0_18,
        .defenseTable = b_area_flo_red_magikoopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_18_CrazeeDayzee_PartsTable_8021D858_18[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 30 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_18_CrazeeDayzee_IdleAnimations_8021D8A4_18,
        .defenseTable = b_area_flo_crazee_dayzee_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_imp_18_Lakitu_SpecialFormation_8021B028_18[] = {
    { .actor = &TTYD64_imp_18_Spiny_18_Spiny,
      .home = { .vec = &b_area_flo_lakitu_SummonPos },
      .priority = 100,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_flo_Formation_0F[] = {
    { .actor = &TTYD64_imp_18_CrazeeDayzee_18_CrazeeDayzee,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_CRAZEEDAYZEE },
};

FormationRow TTYD64_flo_Formation_1C[] = {
    { .actor = &TTYD64_imp_18_AmazyDayzee_18_AmazyDayzee,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_AMAZYDAYZEE },
};

s32 TTYD64_imp_18_Spiny_IdleAnimations_Ball_18[] = {
    1,
    0x4A0018,
    0,
};

s32 TTYD64_imp_18_Lakitu_IdleAnimations_80219F0C_18[] = {
    1,
    0x49020B,
    0,
};

void TTYD64_InstallBattles_flo(void) {
    Mod_SetBattleList("TTYD64", 0x18, TTYD64_flo_FormationTable);
    Mod_SetStageList("TTYD64", 0x18, TTYD64_flo_StageTable);
}
