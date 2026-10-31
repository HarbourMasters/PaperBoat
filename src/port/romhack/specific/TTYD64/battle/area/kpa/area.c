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

API_CALLABLE(b_area_kpa_bony_beetle_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_kpa_ember_PlayLavaBubbleFlightSound);
API_CALLABLE(b_area_kpa_koopatrol_StartRumbleWithParams);
API_CALLABLE(b_area_kpa_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_kpa_magikoopa_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_kpa_magikoopa_ShrinkActor);
API_CALLABLE(b_area_kpa_magikoopa_StartRumbleWithParams);
extern s32 b_area_dgb_tubba_blubba_DefenseTable[];
extern Vec3i b_area_kpa_Formation_1D_pos1;
extern Vec3i b_area_kpa_Formation_1D_pos2;
extern Vec3i b_area_kpa_Formation_1D_pos3;
extern Vec3i b_area_kpa_Formation_1D_pos4;
extern s32 b_area_kpa_bony_beetle_DefenseTable[];
extern EvtScript b_area_kpa_bony_beetle_EVS_Idle;
extern u8 b_area_kpa_bony_beetle_FlipPosOffsets[];
extern s32 b_area_kpa_bony_beetle_ToppledDefenseTable[];
extern s32 b_area_kpa_dry_bones_BoneAnims[];
extern s32 b_area_kpa_dry_bones_DefenseTable[];
extern EvtScript b_area_kpa_dry_bones_EVS_HandleEvent;
extern EvtScript b_area_kpa_dry_bones_EVS_HandlePhase;
extern EvtScript b_area_kpa_dry_bones_EVS_Idle;
extern EvtScript b_area_kpa_dry_bones_EVS_SpinBone;
extern s32 b_area_kpa_dry_bones_StatusTable[];
extern s32 b_area_kpa_ember_DefenseTable[];
extern EvtScript b_area_kpa_ember_EVS_FlyHome;
extern EvtScript b_area_kpa_ember_EVS_GetAvailableColumn;
extern EvtScript b_area_kpa_ember_EVS_Idle;
extern s32 b_area_kpa_ember_ProjectileAnims[];
extern s32 b_area_kpa_ember_StatusTable[];
extern Vec3i b_area_kpa_ember_SummonPos;
extern s32 b_area_kpa_hammer_bro_DefenseTable[];
extern EvtScript b_area_kpa_hammer_bro_EVS_HandleEvent;
extern EvtScript b_area_kpa_hammer_bro_EVS_Idle;
extern s32 b_area_kpa_hammer_bro_HammerAnims[];
extern s32 b_area_kpa_koopatrol_ChargedDefense[];
extern s32 b_area_kpa_koopatrol_ChargedStatusTable[];
extern s32 b_area_kpa_koopatrol_DefenseTable[];
extern EvtScript b_area_kpa_koopatrol_EVS_CountActiveSummoners;
extern EvtScript b_area_kpa_koopatrol_EVS_GetAvailableColumn;
extern EvtScript b_area_kpa_koopatrol_EVS_HandlePhase;
extern EvtScript b_area_kpa_koopatrol_EVS_UpdateOffsets;
extern u8 b_area_kpa_koopatrol_FlipPosOffsets[];
extern Vec3i b_area_kpa_koopatrol_SummonPos;
extern s32 b_area_kpa_koopatrol_ToppledDefense[];
extern Stage b_area_kpa_kpa_01;
extern s32 b_area_kpa_magikoopa_BroomAnims[];
extern s32 b_area_kpa_magikoopa_CloneStatusTable[];
extern EvtScript b_area_kpa_magikoopa_EVS_Clone_Init;
extern EvtScript b_area_kpa_magikoopa_EVS_Flee;
extern EvtScript b_area_kpa_magikoopa_EVS_FlyingClone_Init;
extern EvtScript b_area_kpa_magikoopa_EVS_GetAvailableColumn;
extern EvtScript b_area_kpa_magikoopa_EVS_HandleEvent;
extern EvtScript b_area_kpa_magikoopa_EVS_HandlePhase;
extern EvtScript b_area_kpa_magikoopa_EVS_Idle;
extern EvtScript b_area_kpa_magikoopa_EVS_KnockDownCheck;
extern EvtScript b_area_kpa_magikoopa_EVS_RemoveClone;
extern s32 b_area_kpa_magikoopa_FlyingCloneStatusTable[];
extern s32 b_area_kpa_magikoopa_StatusTable[];
extern Vec3i b_area_kpa_magikoopa_SummonPos;
extern Vec3i b_area_mac_Lee_SummonPos;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_HandleEvent_80228C44_12;
extern EvtScript TTYD64_imp_22_BonyBeetle_Script_Tackle_Spikes_22;
extern EvtScript TTYD64_imp_22_Magikoopa_Script_TakeTurn_8022B784_22;
extern EvtScript TTYD64_imp_22_Magikoopa_Script_ShapeSpell_22;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_ChargeAttack_12;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_ShellToss_12;
extern EvtScript TTYD64_imp_22_DryBones_Script_TakeTurn_8021DB48_22;
extern EvtScript TTYD64_imp_22_HammerBros_Script_HammerBros_SingleHammerAttack;
extern EvtScript TTYD64_imp_22_HammerBros_Script_HammerBros_MultiHammerAttack;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_TakeTurn_8022C454_12;
extern EvtScript TTYD64_imp_22_Magikoopa_Script_HandleEvent_80226A50_22;
extern EvtScript TTYD64_imp_22_BonyBeetle_Script_8021A060_22;
extern EvtScript TTYD64_imp_22_BonyBeetle_Script_Tackle_22;
extern EvtScript TTYD64_imp_22_Magikoopa_Script_Electrify_22;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_PowerShell_12;
extern EvtScript TTYD64_imp_22_Magikoopa_Script_BoostDefense_22;
extern EvtScript TTYD64_imp_22_Magikoopa_Script_BoostAttack_22;
extern EvtScript TTYD64_imp_22_Magikoopa_Script_Vanish_22;
extern EvtScript TTYD64_imp_22_Magikoopa_Script_MakeCopy_22;
extern EvtScript TTYD64_imp_22_Ember_Script_Ember_TackleAttack_0;
extern EvtScript TTYD64_imp_22_BonyBeetle_Script_802191FC_22;
extern EvtScript TTYD64_imp_22_Magikoopa_Script_HealAll_22;
extern EvtScript TTYD64_imp_22_Ember_Script_FireBall_22;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_Summon_12;
extern EvtScript TTYD64_imp_22_Magikoopa_Script_802254F0_22;
extern EvtScript TTYD64_imp_22_Ember_Script_Ember_TackleAttack_1;
extern EvtScript TTYD64_imp_22_Ember_Script_HandleEvent_8021B8BC_22;
extern EvtScript TTYD64_imp_22_Magikoopa_Script_HealOne_22;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Idle_8022875C_12;
extern EvtScript TTYD64_imp_22_DryBones_Script_DryBones_Summon_22;
extern EvtScript TTYD64_imp_22_DryBones_Script_DryBones_MultiBoneAttack_22;
extern EvtScript TTYD64_imp_22_BonyBeetle_Script_8021C234_22;
extern EvtScript TTYD64_imp_22_BonyBeetle_Script_8021BA6C_22;
extern Battle TTYD64_kpa_FormationTable[];
extern EvtScript TTYD64_imp_22_Ember_Script_Ember_SpitFlames;
extern EvtScript TTYD64_imp_22_DryBones_Script_GetNextOpenColumn_22;
extern EvtScript TTYD64_imp_22_Ember_Script_Split_22;
extern EvtScript TTYD64_imp_22_BonyBeetle_Script_Init_80218A70_22;
extern EvtScript TTYD64_imp_22_BonyBeetle_Script_FlipOver_Spikes_22;
extern EvtScript TTYD64_imp_22_Ember_Script_Ember_SpitFlames_DamageActor;
extern EvtScript TTYD64_imp_22_BonyBeetle_Script_FlipOver_22;
extern EvtScript TTYD64_imp_22_Ember_Script_TakeTurn_8021D284_22;
extern EvtScript TTYD64_imp_22_HammerBros_Script_8021F5EC_22;
extern EvtScript TTYD64_imp_22_Ember_Script_Ember_SpitFlames_LittleFlames_FlyToGoal;
extern EvtScript TTYD64_imp_22_DryBones_Script_DryBones_ThrowBone;
extern EvtScript TTYD64_imp_22_BonyBeetle_Script_80218EE8_22;
extern EvtScript TTYD64_imp_22_HammerBros_Script_8021F838_22;
extern EvtScript TTYD64_imp_22_DryBones_Script_DryBones_ThrowBone_Miss;
extern EvtScript TTYD64_imp_22_Ember_Script_Init_8021AEB4_22;
extern EvtScript TTYD64_imp_22_Magikoopa_Script_Init_80225D60_22;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_Hide_12;
extern EvtScript TTYD64_imp_22_Magikoopa_Script_Init_80225F20_22;
extern EvtScript TTYD64_imp_22_BonyBeetle_Script_HandleEvent_80218D7C_22;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Init_802283E8_12;
extern EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_Unhide_12;
extern ActorPartBlueprint TTYD64_imp_22_HammerBros_PartsTable_8021E5A0_22[];
extern ActorPartBlueprint TTYD64_imp_22_Ember_PartsTable_8021AD80_22[];
extern EvtScript TTYD64_imp_22_DryBones_Script_RotateBone_MultiAttack_22;
extern ActorPartBlueprint TTYD64_imp_22_DryBones_PartsTable_8021CC14_22[];
extern s32 TTYD64_imp_22_Magikoopa_StatusTable_80224FE4_22[];
extern s32 TTYD64_imp_22_BonyBeetle_StatusTable_80218978_22[];
extern s32 TTYD64_imp_22_Koopatrol_StatusTable_80228254_12[];
extern s32 TTYD64_imp_22_HammerBros_StatusTable_8021E4F4_22[];
extern EvtScript TTYD64_imp_22_BonyBeetle_Script_TakeTurn_80219110_22;
extern EvtScript TTYD64_imp_22_HammerBros_Script_TakeTurn_8022028C_22;
extern EvtScript TTYD64_imp_22_DryBones_Script_RotateBone_Part4_22;
extern EvtScript TTYD64_imp_22_DryBones_Script_Init_8021CC84_22;
extern FormationRow TTYD64_kpa_Formation_0A[];
extern FormationRow TTYD64_kpa_Formation_0E[];
extern FormationRow TTYD64_kpa_Formation_16[];
extern FormationRow TTYD64_kpa_Formation_14[];
extern FormationRow TTYD64_kpa_Formation_05[];
extern FormationRow TTYD64_kpa_Formation_09[];
extern FormationRow TTYD64_kpa_Formation_06[];
extern FormationRow TTYD64_kpa_Formation_2A[];
extern FormationRow TTYD64_kpa_Formation_2F[];
extern FormationRow TTYD64_kpa_Formation_2D[];
extern FormationRow TTYD64_kpa_Formation_32[];
extern FormationRow TTYD64_kpa_Formation_37[];
extern FormationRow TTYD64_kpa_Formation_1A[];
extern FormationRow TTYD64_kpa_Formation_1E[];
extern FormationRow TTYD64_kpa_Formation_1C[];
extern FormationRow TTYD64_kpa_Formation_1D[];
extern FormationRow TTYD64_kpa_Formation_24[];
extern FormationRow TTYD64_kpa_Formation_25[];
extern FormationRow TTYD64_kpa_Formation_29[];
extern ActorPartBlueprint TTYD64_imp_22_Magikoopa_PartsTable_802250B4_22[];
extern EvtScript TTYD64_imp_22_HammerBros_Script_Init_8021E6A0_22;
extern EvtScript TTYD64_imp_22_Ember_Script_Ember_SpitFlames_LittleFlames;
extern FormationRow TTYD64_kpa_Formation_0D[];
extern FormationRow TTYD64_kpa_Formation_0B[];
extern FormationRow TTYD64_kpa_Formation_0C[];
extern FormationRow TTYD64_kpa_Formation_12[];
extern FormationRow TTYD64_kpa_Formation_10[];
extern FormationRow TTYD64_kpa_Formation_15[];
extern FormationRow TTYD64_kpa_Formation_13[];
extern FormationRow TTYD64_kpa_Formation_19[];
extern FormationRow TTYD64_kpa_Formation_01[];
extern FormationRow TTYD64_kpa_Formation_04[];
extern FormationRow TTYD64_kpa_Formation_02[];
extern FormationRow TTYD64_kpa_Formation_03[];
extern FormationRow TTYD64_kpa_Formation_08[];
extern FormationRow TTYD64_kpa_Formation_2B[];
extern FormationRow TTYD64_kpa_Formation_2C[];
extern FormationRow TTYD64_kpa_Formation_2E[];
extern FormationRow TTYD64_kpa_Formation_33[];
extern FormationRow TTYD64_kpa_Formation_31[];
extern FormationRow TTYD64_kpa_Formation_35[];
extern FormationRow TTYD64_kpa_Formation_36[];
extern FormationRow TTYD64_kpa_Formation_22[];
extern FormationRow TTYD64_kpa_Formation_23[];
extern FormationRow TTYD64_kpa_Formation_20[];
extern FormationRow TTYD64_kpa_Formation_21[];
extern FormationRow TTYD64_kpa_Formation_27[];
extern FormationRow TTYD64_kpa_Formation_28[];
extern s32 TTYD64_imp_22_Ember_IdleAnimations_8021AE5C_22[];
extern s32 TTYD64_imp_22_BonyBeetle_IdleAnimations_802188C8_22[];
extern s32 TTYD64_imp_22_DryBones_IdleAnimations_8021CA20_22[];
extern s32 TTYD64_imp_22_Koopatrol_IdleAnimations_802281D4_12[];
extern s32 TTYD64_imp_22_HammerBros_IdleAnimations_8021E490_22[];
extern s32 TTYD64_imp_22_Koopatrol_IdleAnimations_8022813C_12[];
extern s32 TTYD64_imp_22_Magikoopa_IdleAnimations_80225170_22[];
extern s32 TTYD64_imp_22_Koopatrol_IdleAnimations_802280F0_12[];
extern s32 TTYD64_imp_22_BonyBeetle_IdleAnimations_80218830_22[];
extern s32 TTYD64_imp_22_Koopatrol_IdleAnimations_80228188_12[];
extern s32 TTYD64_imp_22_BonyBeetle_IdleAnimations_8021887C_22[];
extern s32 TTYD64_imp_22_Magikoopa_IdleAnimations_802251BC_22[];
extern s32 TTYD64_imp_22_BonyBeetle_IdleAnimations_80218914_22[];
extern FormationRow TTYD64_kpa_Formation_0F[];
extern FormationRow TTYD64_kpa_Formation_11[];
extern FormationRow TTYD64_kpa_Formation_18[];
extern FormationRow TTYD64_kpa_Formation_00[];
extern FormationRow TTYD64_kpa_Formation_07[];
extern FormationRow TTYD64_kpa_Formation_30[];
extern FormationRow TTYD64_kpa_Formation_34[];
extern FormationRow TTYD64_kpa_Formation_1B[];
extern FormationRow TTYD64_kpa_Formation_1F[];
extern FormationRow TTYD64_kpa_Formation_26[];
extern ActorBlueprint TTYD64_imp_22_Magikoopa_22_Magikoopa;
extern ActorBlueprint TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa;
extern ActorBlueprint TTYD64_imp_22_Magikoopa_FlyingMagiclone_22;
extern ActorBlueprint TTYD64_imp_22_DryBones_22_DryBones;
extern ActorBlueprint TTYD64_imp_22_Magikoopa_Magiclone_22;
extern ActorBlueprint TTYD64_imp_22_Koopatrol_Koopatrol_12;
extern ActorBlueprint TTYD64_imp_22_Koopatrol_22_Koopatrol;
extern ActorBlueprint TTYD64_imp_22_Ember_22_Ember;
extern ActorBlueprint TTYD64_imp_22_Ember_Ember_22;
extern ActorBlueprint TTYD64_imp_22_BonyBeetle_22_BonyBeetle;
extern ActorBlueprint TTYD64_imp_22_HammerBros_22_HammerBros;
extern ActorPartBlueprint TTYD64_imp_22_Magikoopa_PartsTable_80225090_22[];
extern ActorPartBlueprint TTYD64_imp_22_Koopatrol_PartsTable_8022839C_12[];
extern ActorPartBlueprint TTYD64_imp_22_Magikoopa_PartsTable_802292A8_22[];
extern ActorPartBlueprint TTYD64_imp_22_Magikoopa_PartsTable_80229284_22[];
extern ActorPartBlueprint TTYD64_imp_22_BonyBeetle_PartsTable_80218A24_22[];
extern FormationRow TTYD64_imp_22_Magikoopa_SpecialFormation_80229328_22[];
extern FormationRow TTYD64_imp_22_DryBones_SpecialFormation_DryBones_22[];
extern FormationRow TTYD64_imp_22_Koopatrol_SpecialFormation_8022BBC8_12[];
extern FormationRow TTYD64_imp_22_Magikoopa_SpecialFormation_80229344_22[];
extern FormationRow TTYD64_kpa_Formation_17[];
extern FormationRow TTYD64_imp_22_Ember_SpecialFormation_8021B5A0_22[];
extern s32 TTYD64_imp_22_Magikoopa_DefenseTable_80229120_22[];
extern s32 TTYD64_imp_22_Ember_IdleAnimations_FireBall[];
extern s32 TTYD64_imp_22_Magikoopa_DefenseTable_80224F20_22[];
extern s32 TTYD64_imp_22_Koopatrol_IdleAnimations_Koopatrol_Hide_12[];
extern s32 TTYD64_imp_22_Magikoopa_DefenseTable_80229114_22[];
extern s32 TTYD64_imp_22_Magikoopa_DefenseTable_80224F2C_22[];

// clang-format off
EvtScript TTYD64_imp_22_Koopatrol_Script_HandleEvent_80228C44_12 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_Hit))
                EndCaseGroup
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590006)
                    ExecWait(Ref(EVS_Enemy_Hit))
            EndSwitch
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x59000C)
            SetConst(LVar2, 0x59000D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x59000C)
            SetConst(LVar2, 0x59000D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x59000D)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_SpinSmashHit))
                EndCaseGroup
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590006)
                    ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            EndSwitch
        CaseEq(33)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_SpinSmashHit))
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_Death))
                EndCaseGroup
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590006)
                    ExecWait(Ref(EVS_Enemy_SpinSmashHit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
                    Wait(5)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_Death))
            EndSwitch
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            Call(SetActorVar, ACTOR_SELF, 3, 0)
            Call(SetActorVar, ACTOR_SELF, 9, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa_koopatrol_ToppledDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_Koopatrol_IdleAnimations_80228188_12))
            Call(SetTargetOffset, ACTOR_SELF, 1, -5, 15)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 16, 0)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x59000B)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            Thread
                Wait(4)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -60)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -75)
                Wait(1)
            EndThread
            UseBuf(Ref(b_area_kpa_koopatrol_FlipPosOffsets))
            Loop(22)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x59000F)
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x59000B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x59000B)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x590004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x59000B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x59000B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 2)
                Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_imp_22_Koopatrol_StatusTable_80228254_12))
                Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa_koopatrol_DefenseTable))
                Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
                Call(SetActorVar, ACTOR_SELF, 0, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_Koopatrol_IdleAnimations_802280F0_12))
                Call(GetStatusFlags, ACTOR_SELF, LVarA)
                IfNotFlag(LVarA, 0x18000000)
                    Call(EnableActorGlow, ACTOR_SELF, 0)
                EndIf
                Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x590008)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseOrEq(23)
        CaseOrEq(25)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590007)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(GetStatusFlags, ACTOR_SELF, LVar0)
                    IfNotFlag(LVar0, 0x35D000)
                        Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
                        Wait(10)
                    EndIf
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                CaseEq(2)
                    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
                    IfEq(LVar0, 1)
                        SetConst(LVar0, 1)
                        SetConst(LVar1, 0x590005)
                    Else
                        SetConst(LVar0, 1)
                        SetConst(LVar1, 0x590006)
                    EndIf
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndSwitch
        EndCaseGroup
        CaseEq(27)
            Wait(10)
            Set(LFlag0, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                Add(LVar1, 16)
                Set(LFlag0, 1)
            EndIf
            IfFlag(LVar3, 0x40000)
                Add(LVar0, -14)
                Add(LVar1, 20)
                Set(LFlag0, 1)
            EndIf
            IfFlag(LVar3, 4096)
                Add(LVar0, -14)
                Add(LVar1, 20)
                Set(LFlag0, 1)
            EndIf
            Call(GetActorVar, ACTOR_SELF, 0, LVarA)
            IfEq(LVarA, 2)
                Add(LVar1, 23)
                Set(LFlag0, 1)
            EndIf
            IfEq(LFlag0, 0)
                Add(LVar1, 42)
            EndIf
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(20)
        CaseEq(32)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Wait(10)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_Death))
                    Return
                EndCaseGroup
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590006)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
                    Wait(5)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_Death))
                    Return
            EndSwitch
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590001)
                    ExecWait(Ref(EVS_Enemy_Recover))
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590006)
                    ExecWait(Ref(EVS_Enemy_Recover))
            EndSwitch
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590004)
                    SetConst(LVar2, 0x59000B)
                    ExecWait(Ref(EVS_Enemy_ScareAway))
                    Return
                EndCaseGroup
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndSwitch
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590016)
                    ExecWait(Ref(EVS_Enemy_AirLift))
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
                    ExecWait(Ref(EVS_Enemy_AirLift))
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
                    ExecWait(Ref(EVS_Enemy_AirLift))
            EndSwitch
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590016)
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x590001)
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
                CaseEq(2)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x59000F)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_BonyBeetle_Script_Tackle_Spikes_22 = {
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
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x550017)
        Wait(10)
        Goto(100)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x550011)
    Wait(10)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(10)
        Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 32, 6, 0, 10, 0, 0, 0, 0, 0)
        Wait(5)
        Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 32, 8, 0, 10, 0, 0, 0, 0, 0)
        Wait(5)
        Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 32, 10, 0, 10, 0, 0, 0, 0, 0)
        Wait(5)
        Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 32, 12, 0, 10, 0, 0, 0, 0, 0)
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 8225)
    Call(SetAnimation, ACTOR_SELF, 1, 0x550017)
    Wait(15)
    Label(100)
    Thread
        Loop(20)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 7, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(1)
        EndLoop
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 5, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(TTYD64_GetMarioPos, LVar0)
            IfEq(LVar0, 0)
                Set(LVar0, 256)
            Else
                Set(LVar0, 0)
            EndIf
            Call(GetActorPos, LVar0, LVar1, LVar2, LVar3)
            Call(SetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
            Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(24.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(UseBattleCamPreset, 1)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                Set(LVar0, 0)
                Loop(10)
                    Add(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                Set(LVar0, 180)
                Loop(15)
                    Add(LVar0, 12)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                Set(LVar0, 0)
                Loop(10)
                    Add(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Sub(LVar0, 40)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                Set(LVar0, 180)
                Loop(5)
                    Add(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Wait(5)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55000F)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(TTYD64_GetMarioPos, LVar0)
    IfEq(LVar0, 0)
        Set(LVar0, 256)
    Else
        Set(LVar0, 0)
    EndIf
    Call(GetActorPos, LVar0, LVar1, LVar2, LVar3)
    Call(SetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(24.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Thread
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
        Set(LVar0, 0)
        Loop(10)
            Add(LVar0, 18)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 5, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                Set(LVar0, 180)
                Loop(15)
                    Add(LVar0, 12)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                Set(LVar0, 0)
                Loop(10)
                    Add(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Sub(LVar0, 40)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                Set(LVar0, 180)
                Loop(5)
                    Add(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Wait(5)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x550013)
            Wait(5)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55000F)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorYaw, ACTOR_SELF, 0)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Magikoopa_Script_TakeTurn_8022B784_22 = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_22_Magikoopa_Script_ShapeSpell_22)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 10, LVar0)
    IfEq(LVar0, 1)
        Goto(20)
    EndIf
    Set(LVarA, 0)
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
    Call(GetActorHP, LVar0, LVar2)
    Call(GetEnemyMaxHP, LVar0, LVar3)
    MulF(LVar2, Float(100.0))
    DivF(LVar2, LVar3)
    IfEq(LFlag0, 0)
        IfLe(LVar2, 25)
            Call(RandInt, 99, LVar4)
            Add(LVar4, 1)
            IfLt(LVar4, 75)
                Add(LVarA, 1)
                Set(LVarB, LVar0)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfGt(LVarA, 0)
        Goto(10)
    EndIf
    Set(LVarA, 0)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(1)
    Set(LFlag0, 0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar1)
    IfEq(LVar1, 71)
        Call(GetActorVar, LVar0, 8, LVar1)
        IfEq(LVar1, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetActorHP, LVar0, LVar2)
    Call(GetEnemyMaxHP, LVar0, LVar3)
    MulF(LVar2, Float(100.0))
    DivF(LVar2, LVar3)
    IfEq(LFlag0, 0)
        IfLe(LVar2, 20)
            Call(RandInt, 99, LVar4)
            Add(LVar4, 1)
            IfLt(LVar4, 80)
                Add(LVarA, 1)
                Set(LVarB, LVar0)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(1)
    EndIf
    IfGt(LVarA, 0)
        Goto(10)
    EndIf
    Set(LVarA, 0)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(2)
    Set(LFlag0, 0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar1)
    IfEq(LVar1, 71)
        Call(GetActorVar, LVar0, 8, LVar1)
        IfEq(LVar1, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetActorHP, LVar0, LVar2)
    Call(GetEnemyMaxHP, LVar0, LVar3)
    MulF(LVar2, Float(100.0))
    DivF(LVar2, LVar3)
    IfEq(LFlag0, 0)
        IfLe(LVar2, 15)
            Call(RandInt, 99, LVar4)
            Add(LVar4, 1)
            IfLt(LVar4, 100)
                Add(LVarA, 1)
                Set(LVarB, LVar0)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(2)
    EndIf
    IfGt(LVarA, 0)
        Goto(10)
    EndIf
    Goto(20)
    Label(10)
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_kpa_magikoopa_EVS_Flee)
        Return
    EndIf
    IfEq(LVarA, 1)
        Call(GetActorVar, ACTOR_SELF, 4, LVar0)
        IfLt(LVar0, 2)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 500)
                ExecWait(TTYD64_imp_22_Magikoopa_Script_HealOne_22)
                Return
            EndIf
        Else
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            IfLt(LVar0, 2)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 500)
                    ExecWait(TTYD64_imp_22_Magikoopa_Script_HealAll_22)
                    Return
                EndIf
            EndIf
        EndIf
    Else
        Call(GetActorVar, ACTOR_SELF, 3, LVar0)
        IfLt(LVar0, 2)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 500)
                ExecWait(TTYD64_imp_22_Magikoopa_Script_HealAll_22)
                Return
            EndIf
        Else
            Call(GetActorVar, ACTOR_SELF, 4, LVar0)
            IfLt(LVar0, 2)
                SetF(LVar9, Float(100.0))
                Call(CreateHomeTargetList, 0x8002)
                Call(InitTargetIterator)
                Label(11)
                Set(LFlag0, 0)
                Call(GetOwnerTarget, LVar0, LVar1)
                Call(GetOriginalActorType, LVar0, LVar1)
                IfEq(LVar1, 71)
                    Call(GetActorVar, LVar0, 8, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                    EndIf
                EndIf
                Call(GetActorHP, LVar0, LVar2)
                Call(GetEnemyMaxHP, LVar0, LVar3)
                MulF(LVar2, Float(100.0))
                DivF(LVar2, LVar3)
                IfEq(LFlag0, 0)
                    IfLe(LVar2, LVar9)
                        SetF(LVar9, LVar2)
                        Set(LVarB, LVar0)
                    EndIf
                EndIf
                Call(ChooseNextTarget, 0, LVar0)
                IfNe(LVar0, -1)
                    Goto(11)
                EndIf
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 500)
                    ExecWait(TTYD64_imp_22_Magikoopa_Script_HealOne_22)
                    Return
                EndIf
            EndIf
        EndIf
    EndIf
    Label(20)
    Set(LVarA, 10)
    Set(LVarB, 10)
    Set(LVarC, 10)
    Set(LVarD, 10)
    Set(LVarE, 10)
    Set(LVarF, 10)
    Call(GetActorVar, ACTOR_SELF, 10, LVar0)
    IfEq(LVar0, 1)
        Set(LVarA, 100)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Set(LVarD, 0)
        Set(LVarE, 0)
        Set(LVarF, 0)
        Goto(123)
    Else
        ExecWait(b_area_kpa_magikoopa_EVS_GetAvailableColumn)
        IfEq(LVar0, -1)
            Set(LVarB, 0)
        EndIf
    EndIf
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNe(LVar0, 0)
        Set(LVarB, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 11, LVar0)
    Switch(LVar0)
        CaseEq(4)
            Call(GetActorVar, ACTOR_SELF, 5, LVar1)
            IfLt(LVar1, 3)
                Call(RandInt, 99, LVar0)
                Add(LVar0, 1)
                IfLe(LVar0, 50)
                    Set(LVarA, 0)
                    Set(LVarB, 0)
                    Set(LVarC, 100)
                    Set(LVarD, 0)
                    Set(LVarE, 0)
                    Set(LVarF, 0)
                EndIf
            EndIf
        CaseEq(5)
            Call(GetActorVar, ACTOR_SELF, 6, LVar1)
            IfLt(LVar1, 3)
                Call(RandInt, 99, LVar0)
                Add(LVar0, 1)
                IfLe(LVar0, 50)
                    Set(LVarA, 0)
                    Set(LVarB, 0)
                    Set(LVarC, 0)
                    Set(LVarD, 100)
                    Set(LVarE, 0)
                    Set(LVarF, 0)
                EndIf
            EndIf
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    IfGe(LVar0, 3)
        Set(LVarC, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    IfGe(LVar0, 3)
        Set(LVarD, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 7, LVar0)
    IfGe(LVar0, 3)
        Set(LVarE, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfGe(LVar0, 3)
        Set(LVarF, 0)
    EndIf
    Label(123)
    Set(LVar9, 0)
    Add(LVar9, LVarA)
    Add(LVar9, LVarB)
    Add(LVar9, LVarC)
    Add(LVar9, LVarD)
    Add(LVar9, LVarE)
    Add(LVar9, LVarF)
    Sub(LVar9, 1)
    Call(RandInt, LVar9, LVar0)
    Add(LVar0, 1)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_imp_22_Magikoopa_Script_ShapeSpell_22)
        Return
    EndIf
    Add(LVarA, LVarB)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_imp_22_Magikoopa_Script_MakeCopy_22)
        Return
    EndIf
    Add(LVarA, LVarC)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_imp_22_Magikoopa_Script_BoostAttack_22)
        Return
    EndIf
    Add(LVarA, LVarD)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_imp_22_Magikoopa_Script_BoostDefense_22)
        Return
    EndIf
    Add(LVarA, LVarE)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_imp_22_Magikoopa_Script_Electrify_22)
        Return
    EndIf
    ExecWait(TTYD64_imp_22_Magikoopa_Script_Vanish_22)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Magikoopa_Script_ShapeSpell_22 = {
    Call(SetActorVar, ACTOR_SELF, 11, 2)
    Set(LFlag0, 0)
    Set(LFlag1, 0)
    Call(GetActorVar, ACTOR_SELF, 10, LVar0)
    IfEq(LVar0, 1)
        Set(LFlag0, 1)
        Call(GetActorVar, ACTOR_SELF, 9, LVarA)
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        Set(LFlag1, 1)
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    IfEq(LFlag0, 1)
        Call(UseIdleAnimation, LVarA, 0)
    EndIf
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
    IfEq(LFlag1, 0)
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x560002)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 17)
            Add(LVar1, 33)
            Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 13)
        Else
            Sub(LVar0, 17)
            Add(LVar1, 33)
        EndIf
        Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    Else
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x570002)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
        EndIf
        Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Wait(30)
    Call(EnemyTestTarget, ACTOR_SELF, LVar9, 0, 0, 1, 16)
    Switch(LVar9)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LFlag0, 1)
                Call(PlaySoundAtActor, LVarA, 8405)
            EndIf
            Call(PlaySoundAtActor, ACTOR_SELF, 8405)
            IfEq(LFlag1, 0)
                IfEq(LFlag0, 1)
                    Call(SetAnimation, LVarA, 1, 0x560003)
                EndIf
                Call(SetAnimation, ACTOR_SELF, 1, 0x560003)
            Else
                IfEq(LFlag0, 1)
                    Call(SetAnimation, LVarA, 1, 0x570003)
                EndIf
                Call(SetAnimation, ACTOR_SELF, 2, 0x570003)
            EndIf
            Wait(5)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
            Sub(LVar4, 50)
            Set(LVar5, 0)
            IfEq(LFlag1, 0)
                IfEq(LFlag0, 1)
                    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                    Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
                EndIf
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfFlag(LVar3, 0x80000)
                    Sub(LVar0, 8)
                    Add(LVar1, 8)
                Else
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                EndIf
                Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
            Else
                IfEq(LFlag0, 1)
                    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                    Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
                EndIf
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfFlag(LVar3, 0x80000)
                    Sub(LVar0, 8)
                    Add(LVar1, 8)
                Else
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                EndIf
                Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
            EndIf
            Wait(50)
            IfEq(LVar9, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(YieldTurn)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            IfEq(LFlag0, 1)
                Call(UseIdleAnimation, LVarA, 1)
            EndIf
            Return
        EndCaseGroup
    EndSwitch
    IfEq(LFlag0, 1)
        Call(PlaySoundAtActor, LVarA, 8405)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8405)
    IfEq(LFlag1, 0)
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x560003)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 1, 0x560003)
    Else
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x570003)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 2, 0x570003)
    EndIf
    Wait(5)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
    IfEq(LFlag1, 0)
        IfEq(LFlag0, 1)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Add(LVar1, 20)
            Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
        EndIf
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 8)
            Add(LVar1, 8)
        Else
            Sub(LVar0, 20)
            Add(LVar1, 20)
        EndIf
        Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
    Else
        IfEq(LFlag0, 1)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Add(LVar1, 20)
            Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
        EndIf
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 8)
            Add(LVar1, 8)
        Else
            Sub(LVar0, 20)
            Add(LVar1, 20)
        EndIf
        Call(b_area_kpa_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
    EndIf
    Wait(18)
    IfEq(LFlag0, 1)
        Wait(2)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 6, 32)
    Else
        Wait(2)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 6, 32)
    EndIf
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(20)
            Call(YieldTurn)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    IfEq(LFlag0, 1)
        Call(UseIdleAnimation, LVarA, 1)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_ChargeAttack_12 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_Unhide_12)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Call(RandInt, 100, LVar0)
        IfLt(LVar0, 50)
            ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_Hide_12)
            Return
        EndIf
        Call(UseBattleCamPreset, 14)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 20)
        Call(PlaySoundAtActor, ACTOR_SELF, 728)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 10)
        Call(PlayEffect_impl, 107, 6, LVar0, LVar1, LVar2, Float(1.0), 45, 0, 0, 0, 0, 0, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590015)
        Wait(30)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 20)
        Thread
            Wait(8)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590007)
        EndThread
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 8378)
        Call(b_area_kpa_koopatrol_StartRumbleWithParams, 128, 10)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(0.5))
        EndThread
        Call(SetAnimation, ACTOR_SELF, 1, 0x590006)
        Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kpa_koopatrol_ChargedStatusTable))
        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa_koopatrol_ChargedDefense))
        Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 0)
        Call(SetActorVar, ACTOR_SELF, 0, 2)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_Koopatrol_IdleAnimations_802281D4_12))
        Call(TTYD64_AddCharge, ACTOR_SELF, 6)
        Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 1)
        Wait(10)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Return
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Loop(20)
        Call(SetActorDispOffset, ACTOR_SELF, 1, 0, 0)
        Wait(1)
        Call(SetActorDispOffset, ACTOR_SELF, -1, 0, 0)
        Wait(1)
    EndLoop
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 892)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 4, 16)
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
            Thread
                Loop(30)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(PlayEffect_impl, 7, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -200, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Wait(15)
            Call(GetStatusFlags, ACTOR_SELF, LVarA)
            IfNotFlag(LVarA, 0x18000000)
                Call(EnableActorGlow, ACTOR_SELF, 0)
            EndIf
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorPos, ACTOR_SELF, 300, 0, 0)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_imp_22_Koopatrol_StatusTable_80228254_12))
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa_koopatrol_DefenseTable))
            Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_Koopatrol_IdleAnimations_802280F0_12))
            Wait(10)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 15, 0)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Loop(30)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 7, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(1)
        EndLoop
    EndThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarA, 0, 0xFFFF, 0, 4, 32)
    Switch(LVarA)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 16, 0)
                Set(LVar0, 0)
                Loop(60)
                    Add(LVar0, 18)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 30, 0, 1, 0)
            Sub(LVar0, 40)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Wait(20)
            Call(YieldTurn)
            Call(GetStatusFlags, ACTOR_SELF, LVarA)
            IfNotFlag(LVarA, 0x18000000)
                Call(EnableActorGlow, ACTOR_SELF, 0)
            EndIf
            Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorPos, ACTOR_SELF, 300, 0, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x590004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x590001)
            Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_imp_22_Koopatrol_StatusTable_80228254_12))
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa_koopatrol_DefenseTable))
            Call(SetPartEventBits, ACTOR_SELF, 1, 4096, 1)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_Koopatrol_IdleAnimations_802280F0_12))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_ShellToss_12 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590006)
    Else
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        IfEq(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 9, LVar0)
            Sub(LVar0, 1)
            IfGt(LVar0, 0)
                Call(SetActorVar, ACTOR_SELF, 9, LVar0)
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
                Wait(15)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Else
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
                Wait(10)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8321)
                Call(SetAnimation, ACTOR_SELF, 1, 0x59000F)
                Set(LVar0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
                Thread
                    Loop(5)
                        Add(LVar0, 15)
                        Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                        Wait(1)
                    EndLoop
                EndThread
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
                Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8378)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x590001)
                Call(SetActorVar, ACTOR_SELF, 0, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_Koopatrol_IdleAnimations_802280F0_12))
                Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa_koopatrol_DefenseTable))
                Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
                Call(SetTargetOffset, ACTOR_SELF, 1, -4, 32)
                Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -4)
                Call(SetPartEventBits, ACTOR_SELF, 1, 16, 1)
                Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndIf
        Call(RandInt, 100, LVar0)
        IfLt(LVar0, 40)
            ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_PowerShell_12)
            Return
        EndIf
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590007)
        Wait(10)
        Thread
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 4)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            Wait(3)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            Wait(2)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        EndThread
        Call(PlaySoundAtActor, ACTOR_SELF, 8225)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590006)
        Wait(10)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 4, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -40, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(UseBattleCamPreset, 5)
                Call(SetBattleCamDist, 300)
                Call(SetBattleCamOffsetY, 20)
                Call(MoveBattleCamOver, 10)
                Call(SetBattleCamTargetingModes, -1, 1, 0)
            EndIf
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
            Wait(8)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Wait(4)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590016)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590016)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590016)
            Wait(6)
            Sub(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590016)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590001)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetPartYaw, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
            Wait(8)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x590004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x590001)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_DryBones_Script_TakeTurn_8021DB48_22 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 1)
    EndIf
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x530006)
        Goto(100)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 1)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Sub(LVar0, 1)
        IfEq(LVar0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 724)
            Call(SetAnimation, ACTOR_SELF, 1, 0x530009)
            Wait(10)
            Call(PlaySoundAtActor, ACTOR_SELF, 723)
            Call(SetAnimation, ACTOR_SELF, 1, 0x53000A)
            Wait(20)
            Call(SetActorVar, ACTOR_SELF, 8, 0)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_DryBones_IdleAnimations_8021CA20_22))
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa_dry_bones_DefenseTable))
            Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kpa_dry_bones_StatusTable))
            Call(SetPartFlagBits, ACTOR_SELF, 1, 8192, 0)
            Call(SetTargetOffset, ACTOR_SELF, 1, -8, 30)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -10)
            Call(GetEnemyMaxHP, ACTOR_SELF, LVar0)
            Call(SetEnemyHP, ACTOR_SELF, LVar0)
        Else
            Call(PlaySoundAtActor, ACTOR_SELF, 724)
            Call(SetAnimation, ACTOR_SELF, 1, 0x530009)
            Wait(10)
            Call(SetActorVar, ACTOR_SELF, 0, LVar0)
        EndIf
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Return
    EndIf
    ExecWait(TTYD64_imp_22_DryBones_Script_GetNextOpenColumn_22)
    IfNe(LVarA, -1)
        Call(RandInt, 100, LVar0)
        IfLt(LVar0, 30)
            ExecWait(TTYD64_imp_22_DryBones_Script_DryBones_Summon_22)
            Return
        EndIf
    EndIf
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        ExecWait(TTYD64_imp_22_DryBones_Script_DryBones_MultiBoneAttack_22)
        Return
    EndIf
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x530005)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x530006)
    Thread
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 1, 0x530002)
    EndThread
    Label(100)
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
            Set(LVarF, LVar0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
            Wait(1)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
            Call(PlaySoundAtPart, ACTOR_SELF, 2, 721)
            Call(SetPartSounds, ACTOR_SELF, 2, 0, 0, 0)
            Call(SetPartSounds, ACTOR_SELF, 2, 2, 0, 0)
            ExecGetTID(b_area_kpa_dry_bones_EVS_SpinBone, LVarA)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 100)
            Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(12.0))
            Call(RunPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            KillThread(LVarA)
            IfEq(LVarF, 5)
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
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Wait(1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Call(PlaySoundAtPart, ACTOR_SELF, 2, 721)
    Call(SetPartSounds, ACTOR_SELF, 2, 0, 0, 0)
    Call(SetPartSounds, ACTOR_SELF, 2, 2, 0, 0)
    ExecGetTID(b_area_kpa_dry_bones_EVS_SpinBone, LVarA)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(12.0))
    Call(RunPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 5, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(GetPartOffset, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
            Sub(LVar0, 100)
            Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.7001953125))
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, 0, LVar2, 30, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            KillThread(LVarA)
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
EvtScript TTYD64_imp_22_HammerBros_Script_HammerBros_SingleHammerAttack = {
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x5A000C)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A000C)
    Wait(8)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Label(100)
    Thread
        Wait(15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x5A0002)
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
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 5, 32)
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
EvtScript TTYD64_imp_22_HammerBros_Script_HammerBros_MultiHammerAttack = {
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
            Exec(TTYD64_imp_22_HammerBros_Script_8021F5EC_22)
            Wait(5)
            Set(LVar0, 3)
            Exec(TTYD64_imp_22_HammerBros_Script_8021F5EC_22)
            Wait(5)
            Set(LVar0, 4)
            Exec(TTYD64_imp_22_HammerBros_Script_8021F5EC_22)
            Wait(5)
            Set(LVar0, 5)
            Exec(TTYD64_imp_22_HammerBros_Script_8021F5EC_22)
            Wait(5)
            Set(LVar0, 6)
            Exec(TTYD64_imp_22_HammerBros_Script_8021F5EC_22)
            Wait(5)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x5A0002)
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
        Exec(TTYD64_imp_22_HammerBros_Script_8021F838_22)
        Wait(5)
        Set(LVar0, 3)
        Exec(TTYD64_imp_22_HammerBros_Script_8021F838_22)
        Wait(5)
        Set(LVar0, 4)
        Exec(TTYD64_imp_22_HammerBros_Script_8021F838_22)
        Wait(5)
        Set(LVar0, 5)
        Exec(TTYD64_imp_22_HammerBros_Script_8021F838_22)
        Wait(5)
        Set(LVar0, 6)
        Exec(TTYD64_imp_22_HammerBros_Script_8021F838_22)
    EndThread
    Wait(21)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 2, 16)
    Wait(5)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 2, 64)
    Wait(5)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 2, 64)
    Wait(5)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A0002)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 2, 64)
    Wait(5)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 2, 32)
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
EvtScript TTYD64_imp_22_Koopatrol_Script_TakeTurn_8022C454_12 = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetBattleVar, 1, 1)
        ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ShellToss_12)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(GetBattleVar, 1, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseOrEq(0)
                        CaseOrEq(1)
                            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
                            Switch(LVar0)
                                CaseEq(0)
                                    Call(GetBattleVar, 4, LVar1)
                                CaseEq(1)
                                    Call(GetBattleVar, 5, LVar1)
                                CaseEq(2)
                                    Call(GetBattleVar, 6, LVar1)
                                CaseEq(3)
                                    Call(GetBattleVar, 7, LVar1)
                            EndSwitch
                            IfGe(LVar1, 2)
                                Call(RandInt, 1000, LVar0)
                                IfLt(LVar0, 300)
                                    Call(SetBattleVar, 1, 2)
                                    ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ChargeAttack_12)
                                Else
                                    Call(SetBattleVar, 1, 1)
                                    ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ShellToss_12)
                                EndIf
                                Return
                            EndIf
                        EndCaseGroup
                        CaseEq(2)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 300)
                                Call(SetBattleVar, 1, 2)
                                ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ChargeAttack_12)
                            Else
                                Call(SetBattleVar, 1, 1)
                                ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ShellToss_12)
                            EndIf
                            Return
                    EndSwitch
                    ExecWait(b_area_kpa_koopatrol_EVS_GetAvailableColumn)
                    IfEq(LVarA, -1)
                        Call(RandInt, 1000, LVar0)
                        IfLt(LVar0, 300)
                            Call(SetBattleVar, 1, 2)
                            ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ChargeAttack_12)
                        Else
                            Call(SetBattleVar, 1, 1)
                            ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ShellToss_12)
                        EndIf
                        Return
                    EndIf
                    ExecWait(b_area_kpa_koopatrol_EVS_CountActiveSummoners)
                    Switch(LVar9)
                        CaseEq(1)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 400)
                                Call(SetBattleVar, 1, 1)
                                ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_Summon_12)
                                Return
                            EndIf
                        CaseEq(2)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 200)
                                Call(SetBattleVar, 1, 1)
                                ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_Summon_12)
                                Return
                            EndIf
                        CaseEq(3)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 100)
                                Call(SetBattleVar, 1, 1)
                                ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_Summon_12)
                                Return
                            EndIf
                    EndSwitch
                    Call(RandInt, 1000, LVar0)
                    IfLt(LVar0, 300)
                        Call(SetBattleVar, 1, 2)
                        ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ChargeAttack_12)
                    Else
                        Call(SetBattleVar, 1, 1)
                        ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ShellToss_12)
                    EndIf
                CaseEq(1)
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseOrEq(0)
                        CaseOrEq(1)
                            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
                            Switch(LVar0)
                                CaseEq(0)
                                    Call(GetBattleVar, 4, LVar1)
                                CaseEq(1)
                                    Call(GetBattleVar, 5, LVar1)
                                CaseEq(2)
                                    Call(GetBattleVar, 6, LVar1)
                                CaseEq(3)
                                    Call(GetBattleVar, 7, LVar1)
                            EndSwitch
                            IfGe(LVar1, 2)
                                Call(RandInt, 1000, LVar0)
                                IfLt(LVar0, 300)
                                    Call(SetBattleVar, 1, 2)
                                    ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ChargeAttack_12)
                                Else
                                    Call(SetBattleVar, 1, 1)
                                    ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ShellToss_12)
                                EndIf
                                Return
                            EndIf
                        EndCaseGroup
                        CaseEq(2)
                            ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ShellToss_12)
                            Return
                    EndSwitch
                    ExecWait(b_area_kpa_koopatrol_EVS_GetAvailableColumn)
                    IfEq(LVarA, -1)
                        ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ShellToss_12)
                        Return
                    EndIf
                    ExecWait(b_area_kpa_koopatrol_EVS_CountActiveSummoners)
                    Switch(LVar9)
                        CaseEq(1)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 400)
                                ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_Summon_12)
                                Return
                            EndIf
                        CaseEq(2)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 200)
                                ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_Summon_12)
                                Return
                            EndIf
                        CaseEq(3)
                            Call(RandInt, 1000, LVar0)
                            IfLt(LVar0, 100)
                                ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_Summon_12)
                                Return
                            EndIf
                    EndSwitch
                    ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ShellToss_12)
                CaseEq(2)
                    ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ChargeAttack_12)
            EndSwitch
        CaseEq(1)
            Call(SetBattleVar, 1, 1)
            ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ShellToss_12)
        CaseEq(2)
            ExecWait(TTYD64_imp_22_Koopatrol_Script_Koopatrol_ChargeAttack_12)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Magikoopa_Script_HandleEvent_80226A50_22 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetPartAlpha, ACTOR_SELF, 2, 255)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            BitwiseOrConst(LVar0, 1)
            Call(SetActorVar, ACTOR_SELF, 0, LVar0)
            ExecWait(b_area_kpa_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseOrEq(10)
        CaseOrEq(12)
            ExecWait(b_area_kpa_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
            ExecWait(TTYD64_imp_22_Magikoopa_Script_802254F0_22)
        EndCaseGroup
        CaseEq(61)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
        CaseOrEq(14)
        CaseOrEq(15)
            ExecWait(b_area_kpa_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570005)
            SetConst(LVar2, 0x570006)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
            ExecWait(TTYD64_imp_22_Magikoopa_Script_802254F0_22)
        EndCaseGroup
        CaseEq(36)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570005)
            SetConst(LVar2, 0x570006)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
        CaseEq(33)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(25)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfFlag(LVar0, 1)
                ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
                Return
            EndIf
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNe(LVar0, 0)
                ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
            EndIf
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570004)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
            ExecWait(b_area_kpa_magikoopa_EVS_Flee)
            Return
        CaseEq(58)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570002)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                IfFlag(LVar0, 0x80000)
                    Call(SetPartDispOffset, ACTOR_SELF, 2, -3, 0, 0)
                Else
                    Call(SetPartDispOffset, ACTOR_SELF, 2, -15, 0, 0)
                EndIf
            EndIf
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(19)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_kpa_magikoopa_EVS_RemoveClone)
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_BonyBeetle_Script_8021A060_22 = {
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550019)
            ExecWait(Ref(EVS_Enemy_Hit))
            Call(SetActorVar, ACTOR_SELF, 1, 1)
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550020)
            SetConst(LVar2, 0x550021)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Call(SetActorVar, ACTOR_SELF, 1, 1)
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550020)
            SetConst(LVar2, 0x550021)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550021)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550019)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            Call(SetActorVar, ACTOR_SELF, 1, 1)
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550019)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550019)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 8, 3)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, -8)
            Call(SetTargetOffset, ACTOR_SELF, 1, -3, 21)
            Call(SetActorVar, ACTOR_SELF, 9, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa_bony_beetle_ToppledDefenseTable))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_BonyBeetle_IdleAnimations_80218914_22))
            Call(SetPartEventBits, ACTOR_SELF, 1, 16, 0)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x550009)
            UseBuf(Ref(b_area_kpa_bony_beetle_FlipPosOffsets))
            Loop(20)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Wait(20)
        CaseEq(47)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550019)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550019)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55000F)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550011)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Wait(20)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x550013)
            EndIf
            Wait(10)
        EndCaseGroup
        CaseEq(27)
            Wait(10)
            Set(LFlag0, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetStatusFlags, ACTOR_SELF, LVar3)
            IfFlag(LVar3, 0x80000)
                Add(LVar0, -3)
                Add(LVar1, 10)
                Set(LFlag0, 1)
            EndIf
            IfFlag(LVar3, 0x40000)
                Add(LVar0, 0)
                Add(LVar1, 26)
                Set(LFlag0, 1)
            EndIf
            IfEq(LFlag0, 0)
                Add(LVar0, -8)
                Add(LVar1, 26)
            EndIf
            Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(20)
        CaseEq(38)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550019)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550019)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550019)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550019)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550005)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55000F)
            SetConst(LVar2, 0x550019)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseDefault
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_BonyBeetle_Script_Tackle_22 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x550016)
        Goto(100)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x550010)
    Wait(10)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(10)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(5)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 8225)
    Call(SetAnimation, ACTOR_SELF, 1, 0x550016)
    Wait(15)
    Label(100)
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 3, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 40)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x550012)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x55000E)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x550004)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
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
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0x550012)
            Wait(5)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55000E)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x550004)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Magikoopa_Script_Electrify_22 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_kpa_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
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
        ExecWait(b_area_kpa_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_imp_22_Magikoopa_Script_ShapeSpell_22)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 6)
    Call(AddActorVar, ACTOR_SELF, 7, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
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
EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_PowerShell_12 = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590007)
    Wait(10)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 4)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(3)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        Wait(2)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 8225)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590006)
    Wait(10)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 4, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(UseBattleCamPreset, 2)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, -300)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Thread
                Wait(15)
                Call(PlaySound, 8225)
            EndThread
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 500)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
            Wait(15)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(UseBattleCamPreset, 2)
    Thread
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyTestTarget, ACTOR_SELF, LVarB, 0, 0, 4, 16)
        Switch(LVarB)
            CaseOrEq(6)
            CaseOrEq(5)
                IfEq(LVarB, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
            EndCaseGroup
            CaseDefault
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 4, 32)
        EndSwitch
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
    EndThread
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 4, 32)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, -300)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Thread
        Wait(15)
        Call(PlaySound, 8225)
    EndThread
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 500)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
    Wait(15)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Magikoopa_Script_BoostDefense_22 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_kpa_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
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
        ExecWait(b_area_kpa_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_imp_22_Magikoopa_Script_ShapeSpell_22)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 5)
    Call(AddActorVar, ACTOR_SELF, 6, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
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
EvtScript TTYD64_imp_22_Magikoopa_Script_BoostAttack_22 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_kpa_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
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
        ExecWait(b_area_kpa_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_imp_22_Magikoopa_Script_ShapeSpell_22)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 4)
    Call(AddActorVar, ACTOR_SELF, 5, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
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
EvtScript TTYD64_imp_22_Magikoopa_Script_Vanish_22 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_kpa_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
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
        ExecWait(b_area_kpa_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_imp_22_Magikoopa_Script_ShapeSpell_22)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 7)
    Call(AddActorVar, ACTOR_SELF, 8, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
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
EvtScript TTYD64_imp_22_Magikoopa_Script_MakeCopy_22 = {
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_kpa_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(SetActorVar, ACTOR_SELF, 10, 1)
    Call(SetActorVar, ACTOR_SELF, 11, 3)
    Set(LFlag0, 0)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        Set(LFlag0, 1)
    EndIf
    IfEq(LFlag0, 0)
        Call(SummonEnemy, Ref(TTYD64_imp_22_Magikoopa_SpecialFormation_80229328_22), 0)
    Else
        Call(SummonEnemy, Ref(TTYD64_imp_22_Magikoopa_SpecialFormation_80229344_22), 0)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 9, LVar0)
    Set(LVarA, LVar0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(EnableIdleScript, LVarA, 0)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(UseIdleAnimation, LVarA, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 25)
    Wait(25)
    Call(PlaySoundAtActor, ACTOR_SELF, 8406)
    IfEq(LFlag0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
        Call(SetAnimation, LVarA, 1, 0x560002)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 23)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
        Call(SetAnimation, LVarA, 1, 0x570002)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 23)
    EndIf
    Call(PlayEffect_impl, 107, 1, LVar0, LVar1, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
    Wait(10)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(EnableIdleScript, LVar9, 1)
    Wait(30)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, -3)
    Call(SetActorPos, LVarA, LVar0, LVar1, LVar2)
    Set(LVar9, LVarA)
    Wait(15)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Call(PlaySoundAtActor, ACTOR_SELF, 8407)
    Call(PlaySoundAtActor, LVar9, 8407)
    Call(SetPartFlagBits, LVar9, 1, 0x800000, 0)
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 500)
        Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
        ExecWait(b_area_kpa_magikoopa_EVS_GetAvailableColumn)
        Call(SetGoalToIndex, ACTOR_SELF, LVar0)
        Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
    Else
        Call(SetActorSpeed, LVar9, Float(2.0))
        ExecWait(b_area_kpa_magikoopa_EVS_GetAvailableColumn)
        Call(SetGoalToIndex, LVar9, LVar0)
        Call(FlyToGoal, LVar9, 0, 0, 0)
    EndIf
    Call(SetPartFlagBits, LVar9, 1, 0x800000, 1)
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(SetEnemyHP, LVar9, LVar0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Call(GetActorPos, LVar9, LVar0, LVar1, LVar2)
    Call(ForceHomePos, LVar9, LVar0, LVar1, LVar2)
    Call(HPBarToHome, LVar9)
    IfEq(LFlag0, 0)
        Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 1)
    Else
        Call(SetPartEventBits, ACTOR_SELF, 2, 0x400000, 1)
    EndIf
    IfEq(LFlag0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
        Call(SetAnimation, LVar9, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
        Call(SetAnimation, LVar9, 1, 0x570001)
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Call(UseIdleAnimation, LVar9, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Ember_Script_Ember_TackleAttack_0 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460103)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 30, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Thread
        Call(b_area_kpa_ember_PlayLavaBubbleFlightSound)
    EndThread
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 11)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 719)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x460104)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
            Call(ResetActorSounds, ACTOR_SELF, 2)
            Call(PlaySoundAtActor, ACTOR_SELF, 751)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Add(LVar2, 2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x460104)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(30)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(b_area_kpa_ember_EVS_FlyHome)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Wait(5)
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 719)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0x460104)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
    Call(ResetActorSounds, ACTOR_SELF, 2)
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Set(LVarC, LVar2)
    Call(PlaySoundAtActor, ACTOR_SELF, 751)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, 2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 2, 0, 0, 4, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            Wait(20)
            ExecWait(b_area_kpa_ember_EVS_FlyHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_BonyBeetle_Script_802191FC_22 = {
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550018)
            ExecWait(Ref(EVS_Enemy_Hit))
            Call(SetActorVar, ACTOR_SELF, 1, 1)
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001E)
            SetConst(LVar2, 0x55001F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Call(SetActorVar, ACTOR_SELF, 1, 1)
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001E)
            SetConst(LVar2, 0x55001F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001F)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550018)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            Call(SetActorVar, ACTOR_SELF, 1, 1)
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550018)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550018)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 8, 2)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, -8)
            Call(SetTargetOffset, ACTOR_SELF, 1, -3, 21)
            Call(SetActorVar, ACTOR_SELF, 9, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa_bony_beetle_ToppledDefenseTable))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_BonyBeetle_IdleAnimations_802188C8_22))
            Call(SetPartEventBits, ACTOR_SELF, 1, 16, 0)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x550008)
            UseBuf(Ref(b_area_kpa_bony_beetle_FlipPosOffsets))
            Loop(20)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Wait(20)
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550018)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550018)
            ExecWait(Ref(EVS_Enemy_Knockback))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55000E)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550010)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Wait(20)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x550012)
                Wait(10)
            EndIf
        EndCaseGroup
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550018)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550018)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550018)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550018)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550004)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55000E)
            SetConst(LVar2, 0x550018)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55000E)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550018)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Magikoopa_Script_HealAll_22 = {
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 1)
    Call(AddActorVar, ACTOR_SELF, 3, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
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
    Call(MoveBattleCamOver, 10)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Ember_Script_FireBall_22 = {
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
    Call(GetOwnerTarget, LVarA, 0)
    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460101)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460105)
    Wait(30)
    Call(PlaySoundAtActor, ACTOR_SELF, 720)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460106)
    Thread
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 1, 0x460101)
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Add(LVar1, 4)
    Add(LVar2, 2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(TTYD64_GetMarioPos, LVar0)
    IfEq(LVar0, 0)
        Set(LVarB, 256)
    Else
        Set(LVarB, 0)
    EndIf
    Call(GetGoalPos, LVarB, LVar3, LVar4, LVar5)
    Add(LVar3, 55)
    Sub(LVar4, 6)
    Add(LVar5, 2)
    Set(LVar6, 6)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.5), Float(0.5), Float(0.5))
    Else
        Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.7998046875), Float(0.7998046875), Float(0.7998046875))
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Add(LVar1, 4)
    Add(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, LVar6, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 0)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(6.0))
    Call(SetPartJumpGravity, ACTOR_SELF, LVar6, Float(0.009765625))
    Call(SetPartSounds, ACTOR_SELF, LVar6, 2, 720, 0)
    Call(FlyPartTo, ACTOR_SELF, LVar6, LVar3, LVar1, LVar5, 0, 0, 4)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(4.0))
    Call(GetPartPos, ACTOR_SELF, LVar6, LVar3, LVar4, LVar5)
    Add(LVar3, 40)
    Call(FlyPartTo, ACTOR_SELF, LVar6, LVar3, LVar1, LVar5, 0, 0, 4)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(5.0))
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(FlyPartTo, ACTOR_SELF, LVar6, LVar3, LVar1, LVar5, 0, 0, 3)
    Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 1)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000002, 0, 0, 3, 32)
    EndSwitch
    Wait(20)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            ExecWait(b_area_kpa_ember_EVS_FlyHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_Summon_12 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(PlaySoundAtActor, ACTOR_SELF, 741)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590002)
    Wait(20)
    Loop(2)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590002)
        Wait(8)
        Call(PlaySoundAtActor, ACTOR_SELF, 741)
        Call(SetActorYaw, ACTOR_SELF, 180)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590009)
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590002)
        Wait(8)
        Call(PlaySoundAtActor, ACTOR_SELF, 741)
        Call(SetActorYaw, ACTOR_SELF, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590009)
        Wait(8)
    EndLoop
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 15)
    Thread
        Wait(8)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 8301)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x590016)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
    Call(SummonEnemy, Ref(TTYD64_imp_22_Koopatrol_SpecialFormation_8022BBC8_12), 0)
    Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Add(LVar1, 200)
    Call(SetActorPos, LVar0, LVar1, LVar2, LVar3)
    Call(SetGoalToIndex, LVar0, LVarA)
    Call(PlaySoundAtActor, LVar0, 8403)
    Call(SetActorSounds, LVar0, 0, 0, 0)
    Call(SetAnimation, LVar0, 1, 0x590006)
    Call(SetActorSpeed, LVar0, Float(6.0))
    Call(RunToGoal, LVar0, 0, 0)
    Call(SetAnimation, LVar0, 1, 0x590008)
    Wait(10)
    Call(SetAnimation, LVar0, 1, 0x590001)
    Call(GetActorPos, LVar0, LVar1, LVar2, LVar3)
    Call(ForceHomePos, LVar0, LVar1, LVar2, LVar3)
    Call(HPBarToHome, LVar0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar1)
    Switch(LVar1)
        CaseEq(0)
            Call(SetActorVar, LVar0, 1, 1)
        CaseEq(1)
            Call(SetActorVar, LVar0, 1, 2)
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 2, LVar1)
    Call(SetActorVar, LVar0, 2, LVar1)
    Switch(LVar1)
        CaseEq(0)
            Call(GetBattleVar, 4, LVar0)
            Add(LVar0, 1)
            Call(SetBattleVar, 4, LVar0)
        CaseEq(1)
            Call(GetBattleVar, 5, LVar0)
            Add(LVar0, 1)
            Call(SetBattleVar, 5, LVar0)
        CaseEq(2)
            Call(GetBattleVar, 6, LVar0)
            Add(LVar0, 1)
            Call(SetBattleVar, 6, LVar0)
        CaseEq(3)
            Call(GetBattleVar, 7, LVar0)
            Add(LVar0, 1)
            Call(SetBattleVar, 7, LVar0)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Magikoopa_Script_802254F0_22 = {
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560004)
        Goto(0)
    EndIf
    Call(GetLastElement, LVar0)
    IfFlag(LVar0, 1024)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560004)
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
    Call(b_area_kpa_magikoopa_StartRumbleWithParams, 150, 10)
    Thread
        Call(ShakeCam, 1, 0, 5, Float(0.7001953125))
    EndThread
    Call(GetLastEvent, ACTOR_SELF, LVar3)
    IfEq(LVar3, 15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560004)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kpa_magikoopa_EVS_HandleEvent))
    Call(SetActorType, ACTOR_SELF, 77)
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kpa_magikoopa_StatusTable))
    Call(b_area_kpa_magikoopa_SetAbsoluteStatusOffsets, -10, 20, 10, 32)
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
EvtScript TTYD64_imp_22_Ember_Script_Ember_TackleAttack_1 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460103)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Set(LVar1, 5)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Thread
        Call(b_area_kpa_ember_PlayLavaBubbleFlightSound)
    EndThread
    Call(FlyToGoal, ACTOR_SELF, 0, 0, 11)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460101)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x460104)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 0)
            Add(LVar2, 1)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Sub(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Sub(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 3, 0, 1, 0)
            Wait(14)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(b_area_kpa_ember_EVS_FlyHome)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x460104)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, 1)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 130, 0, 0, 4, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Set(LVar0, 1)
            Set(LVar1, 0x460104)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Wait(5)
            ExecWait(b_area_kpa_ember_EVS_FlyHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Ember_Script_HandleEvent_8021B8BC_22 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Exec(TTYD64_imp_22_Ember_Script_Split_22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            Exec(TTYD64_imp_22_Ember_Script_Split_22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460108)
            SetConst(LVar2, 0x460109)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460108)
            SetConst(LVar2, 0x460109)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460109)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            Exec(TTYD64_imp_22_Ember_Script_Split_22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(PlaySoundAtActor, ACTOR_SELF, 1881)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(b_area_kpa_ember_EVS_FlyHome)
        CaseEq(38)
            Call(PlaySoundAtActor, ACTOR_SELF, 1881)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
        CaseOrEq(28)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460101)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_Hit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(b_area_kpa_ember_EVS_FlyHome)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460101)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460103)
            SetConst(LVar2, 0x460107)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460103)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460103)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(61)
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Magikoopa_Script_HealOne_22 = {
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 0)
    Call(AddActorVar, ACTOR_SELF, 4, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
    EndIf
    Wait(5)
    Thread
        Wait(5)
        Call(PlaySoundAtActor, LVarB, 8301)
        Call(PlaySoundAtActor, LVarB, 532)
        Wait(30)
        Call(PlaySoundAtActor, LVarB, 604)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(HealActor, LVarB, 8, 0)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Koopatrol_Script_Idle_8022875C_12 = {
    Label(0)
    Call(RandInt, 80, LVarA)
    Add(LVarA, 80)
    Loop(LVarA)
        Label(1)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        Call(GetActorVar, ACTOR_SELF, 3, LVar2)
        ExecWait(b_area_kpa_koopatrol_EVS_UpdateOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(1)
        EndIf
        IfFlag(LVar1, 0x235D000)
            Wait(1)
            Goto(1)
        EndIf
        IfEq(LVar2, 1)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_Koopatrol_IdleAnimations_8022813C_12))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_Koopatrol_IdleAnimations_802280F0_12))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_Koopatrol_IdleAnimations_80228188_12))
    EndSwitch
    Loop(20)
        Label(2)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        Call(GetActorVar, ACTOR_SELF, 3, LVar2)
        ExecWait(b_area_kpa_koopatrol_EVS_UpdateOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(2)
        EndIf
        IfFlag(LVar1, 0x235D000)
            Wait(1)
            Goto(2)
        EndIf
        IfEq(LVar2, 1)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_Koopatrol_IdleAnimations_8022813C_12))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_Koopatrol_IdleAnimations_802280F0_12))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_Koopatrol_IdleAnimations_80228188_12))
    EndSwitch
    Loop(80)
        Label(3)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        Call(GetActorVar, ACTOR_SELF, 3, LVar2)
        ExecWait(b_area_kpa_koopatrol_EVS_UpdateOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(3)
        EndIf
        IfFlag(LVar1, 0x235D000)
            Wait(1)
            Goto(3)
        EndIf
        IfEq(LVar2, 1)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_DryBones_Script_DryBones_Summon_22 = {
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 3, 0x530010)
    Call(SetAnimation, ACTOR_SELF, 4, 0x53000F)
    Call(SetGoalToIndex, ACTOR_SELF, LVarA)
    Call(UseBattleCamPreset, 2)
    Call(GetIndexFromHome, ACTOR_SELF, LVar0)
    IfLt(LVar0, LVarA)
        Call(SetActorYaw, ACTOR_SELF, -180)
    EndIf
    ExecGetTID(TTYD64_imp_22_DryBones_Script_RotateBone_Part4_22, LVarB)
    Set(LVar3, 6)
    Loop(LVar3)
        Call(SetAnimation, ACTOR_SELF, 1, 0x530005)
        Wait(5)
        Call(SetAnimation, ACTOR_SELF, 1, 0x530006)
        Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 0)
        Call(PlaySoundAtPart, ACTOR_SELF, 4, 721)
        Call(SetPartSounds, ACTOR_SELF, 4, 2, 0, 0)
        Call(SetPartJumpGravity, ACTOR_SELF, 4, Float(1.599609375))
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpPartTo, ACTOR_SELF, 4, LVar0, 0, LVar2, 12, 1)
        Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetPartPos, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
        Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 1)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
        Switch(LVar3)
            CaseEq(6)
                Call(SetAnimation, ACTOR_SELF, 3, 0x530010)
            CaseEq(5)
                Call(SetAnimation, ACTOR_SELF, 3, 0x530011)
            CaseEq(4)
                Call(SetAnimation, ACTOR_SELF, 3, 0x530012)
            CaseEq(3)
                Call(SetAnimation, ACTOR_SELF, 3, 0x530013)
            CaseEq(2)
                Call(SetAnimation, ACTOR_SELF, 3, 0x530014)
            CaseEq(1)
                Call(SetAnimation, ACTOR_SELF, 3, 0x530001)
        EndSwitch
    EndLoop
    KillThread(LVarB)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x530002)
    Call(SetAnimation, ACTOR_SELF, 3, 0x530009)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 3, 0x53000A)
    Wait(6)
    Call(SetAnimation, ACTOR_SELF, 3, 0x530002)
    Call(SummonEnemy, Ref(TTYD64_imp_22_DryBones_SpecialFormation_DryBones_22), 0)
    Call(CopyStatusEffects, ACTOR_SELF, LVar0)
    Set(LVarB, LVar0)
    Call(SetGoalToIndex, LVarB, LVarA)
    Call(GetGoalPos, LVarB, LVar0, LVar1, LVar2)
    Call(SetActorPos, LVarB, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    Call(SetAnimation, LVarB, 1, 0x530002)
    Call(SetActorYaw, LVarB, 0)
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
EvtScript TTYD64_imp_22_DryBones_Script_DryBones_MultiBoneAttack_22 = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x530005)
    Wait(15)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 2, Float(0.400390625), Float(0.400390625), Float(0.400390625))
        Call(SetPartScale, ACTOR_SELF, 4, Float(0.400390625), Float(0.400390625), Float(0.400390625))
        Call(SetPartScale, ACTOR_SELF, 5, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Else
        Call(SetPartScale, ACTOR_SELF, 2, Float(1.0), Float(1.0), Float(1.0))
        Call(SetPartScale, ACTOR_SELF, 4, Float(1.0), Float(1.0), Float(1.0))
        Call(SetPartScale, ACTOR_SELF, 5, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Set(LVar0, 2)
            Exec(TTYD64_imp_22_DryBones_Script_DryBones_ThrowBone_Miss)
            Wait(15)
            Set(LVar0, 4)
            Exec(TTYD64_imp_22_DryBones_Script_DryBones_ThrowBone_Miss)
            Wait(15)
            Set(LVar0, 5)
            Exec(TTYD64_imp_22_DryBones_Script_DryBones_ThrowBone_Miss)
            Wait(15)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x530002)
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
        Exec(TTYD64_imp_22_DryBones_Script_DryBones_ThrowBone)
        Wait(15)
        Set(LVar0, 4)
        Exec(TTYD64_imp_22_DryBones_Script_DryBones_ThrowBone)
        Wait(15)
        Set(LVar0, 5)
        Exec(TTYD64_imp_22_DryBones_Script_DryBones_ThrowBone)
        Wait(15)
    EndThread
    Wait(28)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 16)
    Wait(15)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 64)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x530002)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 64)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
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
EvtScript TTYD64_imp_22_BonyBeetle_Script_8021C234_22 = {
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001B)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550024)
            SetConst(LVar2, 0x550025)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550024)
            SetConst(LVar2, 0x550025)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550025)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 8, 3)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, -8)
            Call(SetTargetOffset, ACTOR_SELF, 1, -3, 21)
            Call(b_area_kpa_bony_beetle_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
            Call(SetActorVar, ACTOR_SELF, 9, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa_bony_beetle_ToppledDefenseTable))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_BonyBeetle_IdleAnimations_80218914_22))
            Call(SetAnimation, ACTOR_SELF, 1, 0x55001B)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            UseBuf(Ref(b_area_kpa_bony_beetle_FlipPosOffsets))
            Loop(20)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Wait(20)
        CaseOrEq(57)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550007)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001B)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550007)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550007)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001B)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_BonyBeetle_Script_8021BA6C_22 = {
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001A)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550022)
            SetConst(LVar2, 0x550023)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550022)
            SetConst(LVar2, 0x550023)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550023)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001A)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001A)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 8, 2)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, -8)
            Call(SetTargetOffset, ACTOR_SELF, 1, -3, 21)
            Call(b_area_kpa_bony_beetle_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
            Call(SetActorVar, ACTOR_SELF, 9, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa_bony_beetle_ToppledDefenseTable))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_BonyBeetle_IdleAnimations_802188C8_22))
            Call(SetAnimation, ACTOR_SELF, 1, 0x55001A)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            UseBuf(Ref(b_area_kpa_bony_beetle_FlipPosOffsets))
            Loop(20)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Wait(20)
        CaseOrEq(57)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550006)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001A)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001A)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550006)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x550006)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x55001A)
            ExecWait(Ref(EVS_Enemy_BlowAway))
    EndSwitch
    Return
    End
};
// clang-format on

Battle TTYD64_kpa_FormationTable[] = {
    { .name = "\333\315\341\303\310x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kpa_Formation_00,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\333\315\341\303\310x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_01,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\333\315\341\303\310,\253\355\363x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_02,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\333\315\341\303\310x\022,\253\355\363",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_03,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\333\315\341\303\310x\022,\253\341\303\257",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_04,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\333\315\341\303\310x\023,\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_05,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\333\315\341\303\310,\253\355\363,\333\315\341\303\310,\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_06,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\355\363x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kpa_Formation_07,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\355\363x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_08,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\355\363x\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_09,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\355\363,\250\353\342\271x\023",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_0A,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\355\363x\022,\253\341\303\257",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_0B,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\355\363,\310\262\316\263x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_0C,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\355\363x\022,\333\315\341\303\310",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_0D,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\355\363x\022,\333\315\341\303\310x\022",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_0E,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\317\363\336\374\326\355\271x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kpa_Formation_0F,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\317\363\336\374\326\355\271x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_10,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\317\363\336\374\326\355\271,\310\262\316\263",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kpa_Formation_11,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\317\363\336\374\326\355\271x\022,\310\262\316\263",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_12,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\317\363\336\374\326\355\271,\310\262\316\263x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_13,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\317\363\336\374\326\355\271,\253\355\363,\317\363\363\336\374\326\355\271,\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_14,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\317\363\336\374\326\355\271x\022,OFa\205F\253\341\303\257",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_15,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\317\363\336\374\326\355\271x\023,OFa\205F\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_16,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_kpa_Formation_17,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kpa_Formation_18,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_19,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263x\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_1A,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263,\317\363\336\374\326\355\271",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kpa_Formation_1B,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263,\317\363\336\374\326\355\271,\310\262\316\263,\317\363\336\374\326\355\271",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_1C,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263x\023,\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_1D,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263x\022,\253\341\303\257x\022",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_1E,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263,\333\315\341\303\310",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kpa_Formation_1F,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263x\022,\333\315\341\303\310",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_20,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263,\333\315\341\303\310x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_21,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263,\333\315\341\303\310,\310\262\316\263",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_22,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263,\253\355\363x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_23,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263x\022,\253\341\303\257,OFa\205F\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_24,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\310\262\316\263,\253\341\303\257,\310\262\316\263,\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_25,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\341\303\257x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kpa_Formation_26,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\341\303\257x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_27,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\341\303\257,OFa\205F\253\341\303\257x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_28,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\341\303\257x\022,OFa\205F\253\341\303\257x\022",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_29,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\341\303\257,\310\262\316\263x\023",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_2A,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\341\303\257x\022,\253\355\363",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_2B,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\341\303\257,\333\315\341\303\310,\253\341\303\257",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_2C,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\341\303\257,\333\315\341\303\310x\022,\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_2D,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\341\303\257x\022,OFa\205F\253\341\303\257",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_2E,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "\253\341\303\257,\310\262\316\263,\253\341\303\257,\310\262\316\263",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_2F,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "OFa\205F\253\341\303\257x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kpa_Formation_30,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "OFa\205F\253\341\303\257x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_31,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "OFa\205F\253\341\303\257,\253\341\303\257,OFa\205F\253\341\303\257,\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_32,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "OFa\205F\253\341\303\257,\310\262\316\263x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_33,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "OFa\205F\253\341\303\257,\317\363\336\374\326\355\271",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kpa_Formation_34,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "OFa\205F\253\341\303\257,\253\355\363x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_35,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "OFa\205F\253\341\303\257,\310\262\316\263,OFa\205F\253\341\303\257",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_kpa_Formation_36,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    { .name = "OFa\205F\253\341\303\257,\317\363\336\374\326\355\271x\022,OFa\205F\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kpa_Formation_37,
      .stage = &b_area_kpa_kpa_01,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_imp_22_Ember_Script_Ember_SpitFlames = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 256)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(TTYD64_GetMarioPos, LVar0)
    IfEq(LVar0, 0)
        Set(LVarA, 256)
    Else
        Set(LVarA, 0)
    EndIf
    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfEq(LVarA, 1)
        Add(LVar0, 100)
        Set(LVar1, 5)
    Else
        Add(LVar0, 30)
        Set(LVar1, 50)
    EndIf
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460103)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Thread
        Call(b_area_kpa_ember_PlayLavaBubbleFlightSound)
    EndThread
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 11)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460101)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460105)
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460106)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Add(LVar1, 4)
    Add(LVar2, 2)
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfLe(LVar0, 0)
        Call(SetTargetActor, ACTOR_SELF, 0)
    Else
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar4, 6)
    Add(LVar5, 2)
    ExecWait(TTYD64_imp_22_Ember_Script_Ember_SpitFlames_LittleFlames)
    Wait(20)
    Switch(LVar9)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(b_area_kpa_ember_EVS_FlyHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_DryBones_Script_GetNextOpenColumn_22 = {
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, 0)
    Call(GetIndexFromHome, LVar0, LVar5)
    Call(GetIndexFromHome, ACTOR_SELF, LVar6)
    Mod(LVar5, 4)
    Set(LVar1, LVar6)
    IfNe(LVar1, 0)
        Sub(LVar1, 1)
        IfEq(LVar1, LVar5)
            Set(LFlag1, 1)
            Goto(1)
        EndIf
    Else
        Set(LFlag1, 1)
        Goto(1)
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(1)
    Call(GetOwnerTarget, LVar0, 0)
    Call(GetIndexFromHome, LVar0, LVar5)
    Call(GetIndexFromHome, ACTOR_SELF, LVar6)
    Mod(LVar5, 4)
    Set(LVar2, LVar6)
    IfLt(LVar2, 3)
        Add(LVar2, 1)
        IfEq(LVar2, LVar5)
            Set(LFlag2, 1)
            Goto(2)
        EndIf
    Else
        Set(LFlag2, 1)
        Goto(2)
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(1)
    EndIf
    Label(2)
    IfEq(LFlag1, 0)
        Call(GetIndexFromHome, ACTOR_SELF, LVar6)
        Sub(LVar6, 1)
        Set(LVarA, LVar6)
        Return
    EndIf
    IfEq(LFlag2, 0)
        Call(GetIndexFromHome, ACTOR_SELF, LVar6)
        Add(LVar6, 1)
        Set(LVarA, LVar6)
        Return
    EndIf
    Set(LVarA, -1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Ember_Script_Split_22 = {
    Call(GetLastDamage, ACTOR_SELF, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(GetActorHP, ACTOR_SELF, LVar0)
    IfLe(LVar0, 0)
        Return
    EndIf
    Call(GetLastElement, LVar0)
    IfFlag(LVar0, 0x20000000)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    IfGe(LVar0, 2)
        Return
    EndIf
    ExecWait(b_area_kpa_ember_EVS_GetAvailableColumn)
    Switch(LVarA)
        CaseOrEq(0)
        CaseOrEq(1)
        CaseOrEq(2)
        CaseOrEq(3)
            Call(SummonEnemy, Ref(TTYD64_imp_22_Ember_SpecialFormation_8021B5A0_22), 0)
            Call(SetActorVar, LVar0, 2, 1)
            Call(GetActorHP, ACTOR_SELF, LVarB)
            Call(SetEnemyHP, LVar0, LVarB)
            Call(GetActorPos, ACTOR_SELF, LVarB, LVarC, LVarD)
            Call(SetActorPos, LVar0, LVarB, LVarC, LVarD)
            Call(SetGoalToIndex, LVar0, LVarA)
            Call(GetGoalPos, LVar0, LVarB, LVarC, LVarD)
            Call(SetHomePos, LVar0, LVarB, LVarC, LVarD)
            Call(SetActorJumpGravity, LVar0, Float(1.2001953125))
            Call(JumpToGoal, LVar0, 20, 0, 1, 0)
            Call(HPBarToHome, LVar0)
            Call(GetActorVar, ACTOR_SELF, 1, LVar1)
            Switch(LVar1)
                CaseEq(0)
                    Call(SetActorVar, LVar0, 1, 1)
                CaseEq(1)
                    Call(SetActorVar, LVar0, 1, 2)
            EndSwitch
            Call(SetActorVar, ACTOR_SELF, 1, 3)
            Call(SetActorVar, LVar0, 2, 0)
        EndCaseGroup
        CaseDefault
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_BonyBeetle_Script_Init_80218A70_22 = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Call(GetInstigatorValue, ACTOR_SELF, LVar1)
    IfEq(LVar0, 1)
        IfEq(LVar1, 1)
            Call(SetActorVar, ACTOR_SELF, 8, 1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_BonyBeetle_IdleAnimations_8021887C_22))
            Call(SetPartEventBits, ACTOR_SELF, 1, 16, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x550005)
        Else
            Call(SetActorVar, ACTOR_SELF, 8, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_BonyBeetle_IdleAnimations_80218830_22))
            Call(SetPartEventBits, ACTOR_SELF, 1, 16, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x550004)
        EndIf
    Else
        Call(RandInt, 1000, LVar0)
        IfLt(LVar0, 500)
            Call(SetActorVar, ACTOR_SELF, 8, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_BonyBeetle_IdleAnimations_80218830_22))
            Call(SetPartEventBits, ACTOR_SELF, 1, 16, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x550004)
        Else
            Call(SetActorVar, ACTOR_SELF, 8, 1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_BonyBeetle_IdleAnimations_8021887C_22))
            Call(SetPartEventBits, ACTOR_SELF, 1, 16, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x550005)
        EndIf
    EndIf
    Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, -8)
    Call(SetTargetOffset, ACTOR_SELF, 1, -3, 21)
    Call(SetActorFlagBits, ACTOR_SELF, 2048, 0)
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa_bony_beetle_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_22_BonyBeetle_Script_HandleEvent_80218D7C_22))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_22_BonyBeetle_Script_TakeTurn_80219110_22))
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_BonyBeetle_Script_FlipOver_Spikes_22 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 9, LVar0)
    Sub(LVar0, 1)
    IfGt(LVar0, 0)
        Call(SetActorVar, ACTOR_SELF, 9, LVar0)
        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
        Call(SetAnimation, ACTOR_SELF, 1, 0x55001D)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x550007)
        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
    Else
        Call(UseBattleCamPreset, 15)
        Call(SetBattleCamDist, 350)
        Call(SetBattleCamOffsetY, 20)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
        Call(SetAnimation, ACTOR_SELF, 1, 0x55001D)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x550007)
        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x55000B)
        Wait(20)
        Call(SetActorYaw, ACTOR_SELF, 0)
        Call(SetActorVar, ACTOR_SELF, 8, 1)
        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa_bony_beetle_DefenseTable))
        Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_BonyBeetle_IdleAnimations_8021887C_22))
        Call(SetPartEventBits, ACTOR_SELF, 1, 16, 1)
        Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Ember_Script_Ember_SpitFlames_DamageActor = {
    Loop(0)
        Call(GetPartPos, ACTOR_SELF, LVar6, LVar1, 0, LVar2)
        Call(TTYD64_GetMarioPos, LVar0)
        IfEq(LVar0, 0)
            Set(LVar0, 256)
        Else
            Set(LVar0, 0)
        EndIf
        Call(GetActorPos, LVar0, LVar3, 0, LVar4)
        Call(GetDist2D, LVar0, LVar1, LVar2, LVar3, LVar4)
        IfLe(LVar0, 12)
            Call(GetOwnerTarget, LVar5, 0)
            Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVar9, 0, 0, 1, 16)
            Switch(LVar9)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarA, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar9, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    BreakLoop
            EndSwitch
            Call(EnemyDamageTarget, ACTOR_SELF, LVar9, 0x10000002, 0, 0, 3, 32)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVar9, 0, 0, 1, 16)
    Switch(LVar9)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar9, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVar9, 0x10000002, 0, 0, 3, 32)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_BonyBeetle_Script_FlipOver_22 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 9, LVar0)
    Sub(LVar0, 1)
    IfGt(LVar0, 0)
        Call(SetActorVar, ACTOR_SELF, 9, LVar0)
        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
        Call(SetAnimation, ACTOR_SELF, 1, 0x55001C)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x550006)
        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
    Else
        Call(UseBattleCamPreset, 15)
        Call(SetBattleCamDist, 350)
        Call(SetBattleCamOffsetY, 20)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
        Call(SetAnimation, ACTOR_SELF, 1, 0x55001C)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x550006)
        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x55000A)
        Wait(20)
        Call(SetActorYaw, ACTOR_SELF, 0)
        Call(SetActorVar, ACTOR_SELF, 8, 0)
        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa_bony_beetle_DefenseTable))
        Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_BonyBeetle_IdleAnimations_80218830_22))
        Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Ember_Script_TakeTurn_8021D284_22 = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Switch(LVar0)
            CaseEq(1)
                ExecWait(TTYD64_imp_22_Ember_Script_Ember_TackleAttack_1)
            CaseEq(0)
                ExecWait(TTYD64_imp_22_Ember_Script_Ember_TackleAttack_0)
        EndSwitch
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(1)
            Call(GetStatusFlags, 256, LVar0)
            IfFlag(LVar0, 0x1000000)
                Call(RandInt, 99, LVar0)
                IfLt(LVar0, 49)
                    ExecWait(TTYD64_imp_22_Ember_Script_FireBall_22)
                Else
                    ExecWait(TTYD64_imp_22_Ember_Script_Ember_TackleAttack_1)
                EndIf
            Else
                Call(RandInt, 1000, LVar0)
                IfLe(LVar0, 300)
                    ExecWait(TTYD64_imp_22_Ember_Script_Ember_SpitFlames)
                Else
                    Call(RandInt, 99, LVar0)
                    IfLt(LVar0, 49)
                        ExecWait(TTYD64_imp_22_Ember_Script_FireBall_22)
                    Else
                        ExecWait(TTYD64_imp_22_Ember_Script_Ember_TackleAttack_1)
                    EndIf
                EndIf
            EndIf
        CaseEq(0)
            Call(GetStatusFlags, 256, LVar0)
            IfFlag(LVar0, 0x1000000)
                ExecWait(TTYD64_imp_22_Ember_Script_Ember_TackleAttack_0)
            Else
                Call(RandInt, 1000, LVar0)
                IfLe(LVar0, 300)
                    ExecWait(TTYD64_imp_22_Ember_Script_Ember_SpitFlames)
                Else
                    ExecWait(TTYD64_imp_22_Ember_Script_Ember_TackleAttack_0)
                EndIf
            EndIf
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_HammerBros_Script_8021F5EC_22 = {
    Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A0002)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A000C)
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
EvtScript TTYD64_imp_22_Ember_Script_Ember_SpitFlames_LittleFlames_FlyToGoal = {
    Set(LVar6, 2)
    Set(LVar7, 4)
    Loop(LVar7)
        Thread
            Call(GetStatusFlags, ACTOR_SELF, LVarA)
            IfFlag(LVarA, 0x80000)
                Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.2001953125), Float(0.2001953125), Float(0.2001953125))
            Else
                Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.5), Float(0.5), Float(0.5))
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 5)
            Add(LVar1, 4)
            Add(LVar2, 2)
            Call(SetPartPos, ACTOR_SELF, LVar6, LVar0, LVar1, LVar2)
            Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(8.0))
            Call(SetPartJumpGravity, ACTOR_SELF, LVar6, Float(0.009765625))
            Call(SetPartSounds, ACTOR_SELF, LVar6, 2, 720, 0)
            IfEq(LVar7, 4)
                Call(TTYD64_GetPartnerHP_API, LVar8)
                IfGt(LVar8, 0)
                    Exec(TTYD64_imp_22_Ember_Script_Ember_SpitFlames_DamageActor)
                EndIf
            EndIf
            Call(JumpPartTo, ACTOR_SELF, LVar6, LVar3, LVar4, LVar5, 0, 0)
            Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 1)
        EndThread
        Wait(3)
        Add(LVar6, 1)
    EndLoop
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_DryBones_Script_DryBones_ThrowBone = {
    Call(SetAnimation, ACTOR_SELF, 1, 0x530005)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x530006)
    Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Add(LVar2, 20)
    Call(SetPartPos, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3)
    Wait(1)
    Call(SetPartFlagBits, ACTOR_SELF, LVar0, 1, 0)
    Call(PlaySoundAtPart, ACTOR_SELF, LVar0, 721)
    Call(SetPartSounds, ACTOR_SELF, LVar0, 0, 0, 0)
    Call(SetPartSounds, ACTOR_SELF, LVar0, 2, 0, 0)
    ExecGetTID(TTYD64_imp_22_DryBones_Script_RotateBone_MultiAttack_22, LVarA)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Add(LVar2, 20)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar0, Float(12.0))
    Call(RunPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 0)
    Call(GetPartOffset, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3)
    Sub(LVar1, 100)
    Call(SetPartJumpGravity, ACTOR_SELF, LVar0, Float(0.7001953125))
    Call(JumpPartTo, ACTOR_SELF, LVar0, LVar1, 0, LVar3, 30, 1)
    Call(SetPartFlagBits, ACTOR_SELF, LVar0, 1, 1)
    KillThread(LVarA)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_BonyBeetle_Script_80218EE8_22 = {
    Call(GetLastDamage, ACTOR_SELF, LVar0)
    IfLe(LVar0, 0)
        Return
    EndIf
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x35D000)
        Return
    EndIf
    Label(0)
    Call(GetBattleFlags, LVarA)
    IfFlag(LVarA, 256)
        Wait(1)
        Goto(0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8398)
            Call(SetActorVar, ACTOR_SELF, 8, 1)
            Call(SetPartEventBits, ACTOR_SELF, 1, 16, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x55002E)
            Wait(25)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_BonyBeetle_IdleAnimations_8021887C_22))
        CaseEq(1)
            Call(PlaySoundAtActor, ACTOR_SELF, 8399)
            Call(SetActorVar, ACTOR_SELF, 8, 0)
            Call(SetPartEventBits, ACTOR_SELF, 1, 16, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x55002F)
            Wait(25)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_BonyBeetle_IdleAnimations_80218830_22))
        CaseEq(2)
        CaseEq(3)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_HammerBros_Script_8021F838_22 = {
    Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A0002)
    Call(SetAnimation, ACTOR_SELF, 1, 0x5A000C)
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

// clang-format off
EvtScript TTYD64_imp_22_DryBones_Script_DryBones_ThrowBone_Miss = {
    Call(SetAnimation, ACTOR_SELF, 1, 0x530005)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x530006)
    Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Add(LVar2, 20)
    Call(SetPartPos, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3)
    Wait(1)
    Call(SetPartFlagBits, ACTOR_SELF, LVar0, 1, 0)
    Call(PlaySoundAtPart, ACTOR_SELF, LVar0, 721)
    Call(SetPartSounds, ACTOR_SELF, LVar0, 0, 0, 0)
    Call(SetPartSounds, ACTOR_SELF, LVar0, 2, 0, 0)
    ExecGetTID(TTYD64_imp_22_DryBones_Script_RotateBone_MultiAttack_22, LVarA)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Sub(LVar1, 100)
    Add(LVar2, 20)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar0, Float(12.0))
    Call(RunPartTo, ACTOR_SELF, LVar0, LVar1, LVar2, LVar3, 0)
    Call(SetPartFlagBits, ACTOR_SELF, LVar0, 1, 1)
    KillThread(LVarA)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Ember_Script_Init_8021AEB4_22 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_22_Ember_Script_TakeTurn_8021D284_22))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa_ember_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_22_Ember_Script_HandleEvent_8021B8BC_22))
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
    EndSwitch
    Call(SetPartScale, ACTOR_SELF, 2, Float(0.5), Float(0.5), Float(0.5))
    Call(SetPartScale, ACTOR_SELF, 3, Float(0.5), Float(0.5), Float(0.5))
    Call(SetPartScale, ACTOR_SELF, 4, Float(0.5), Float(0.5), Float(0.5))
    Call(SetPartScale, ACTOR_SELF, 5, Float(0.5), Float(0.5), Float(0.5))
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 5)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Magikoopa_Script_Init_80225D60_22 = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_22_Magikoopa_Script_TakeTurn_8022B784_22))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kpa_magikoopa_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kpa_magikoopa_EVS_HandlePhase))
    Call(GetBattleVar, 2, LVar0)
    IfEq(LVar0, 0)
        Call(SetBattleVar, 2, -1)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 0)
    Call(SetActorVar, ACTOR_SELF, 7, 0)
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(SetActorVar, ACTOR_SELF, 9, -1)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, -1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_Hide_12 = {
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Thread
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 1, 0x590007)
    EndThread
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_kpa_koopatrol_ChargedStatusTable))
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_dgb_tubba_blubba_DefenseTable))
    Call(SetActorVar, ACTOR_SELF, 0, 2)
    Call(SetActorVar, ACTOR_SELF, 3, 1)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_Koopatrol_IdleAnimations_Koopatrol_Hide_12))
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 1)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590005)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Magikoopa_Script_Init_80225F20_22 = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_22_Magikoopa_Script_TakeTurn_8022B784_22))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_22_Magikoopa_Script_HandleEvent_80226A50_22))
    Call(GetBattleVar, 2, LVar0)
    IfEq(LVar0, 0)
        Call(SetBattleVar, 2, -1)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 0)
    Call(SetActorVar, ACTOR_SELF, 7, 0)
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(SetActorVar, ACTOR_SELF, 9, -1)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, -1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_BonyBeetle_Script_HandleEvent_80218D7C_22 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_imp_22_BonyBeetle_Script_802191FC_22)
        CaseEq(1)
            ExecWait(TTYD64_imp_22_BonyBeetle_Script_8021A060_22)
        CaseEq(2)
            ExecWait(TTYD64_imp_22_BonyBeetle_Script_8021BA6C_22)
        CaseEq(3)
            ExecWait(TTYD64_imp_22_BonyBeetle_Script_8021C234_22)
    EndSwitch
    Call(ActorExists, ACTOR_SELF, LVar0)
    IfEq(LVar0, 1)
        Call(GetActorVar, ACTOR_SELF, 1, LVar0)
        IfEq(LVar0, 1)
            ExecWait(TTYD64_imp_22_BonyBeetle_Script_80218EE8_22)
            Call(SetActorVar, ACTOR_SELF, 1, 0)
        EndIf
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Koopatrol_Script_Init_802283E8_12 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_22_Koopatrol_Script_TakeTurn_8022C454_12))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_22_Koopatrol_Script_Idle_8022875C_12))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_22_Koopatrol_Script_HandleEvent_80228C44_12))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kpa_koopatrol_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(GetIndexFromHome, ACTOR_SELF, LVar0)
    Call(SetActorVar, ACTOR_SELF, 2, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetBattleVar, 4, 0)
        CaseEq(1)
            Call(SetBattleVar, 5, 0)
        CaseEq(2)
            Call(SetBattleVar, 6, 0)
        CaseEq(3)
            Call(SetBattleVar, 7, 0)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Koopatrol_Script_Koopatrol_Unhide_12 = {
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590008)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x590001)
    Call(SetStatusTable, ACTOR_SELF, Ref(TTYD64_imp_22_Koopatrol_StatusTable_80228254_12))
    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_kpa_koopatrol_DefenseTable))
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 0)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_22_Koopatrol_IdleAnimations_802280F0_12))
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_imp_22_HammerBros_PartsTable_8021E5A0_22[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -3, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_22_HammerBros_IdleAnimations_8021E490_22,
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
        .idleAnimations = b_area_kpa_hammer_bro_HammerAnims,
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
        .idleAnimations = b_area_kpa_hammer_bro_HammerAnims,
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
        .idleAnimations = b_area_kpa_hammer_bro_HammerAnims,
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
        .idleAnimations = b_area_kpa_hammer_bro_HammerAnims,
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
        .idleAnimations = b_area_kpa_hammer_bro_HammerAnims,
        .defenseTable = b_area_kpa_hammer_bro_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_22_Ember_PartsTable_8021AD80_22[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 25 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_22_Ember_IdleAnimations_8021AE5C_22,
        .defenseTable = b_area_kpa_ember_DefenseTable,
        .eventFlags = 0x2,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -3, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = b_area_kpa_ember_ProjectileAnims,
        .defenseTable = b_area_kpa_ember_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = b_area_kpa_ember_ProjectileAnims,
        .defenseTable = b_area_kpa_ember_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = b_area_kpa_ember_ProjectileAnims,
        .defenseTable = b_area_kpa_ember_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = b_area_kpa_ember_ProjectileAnims,
        .defenseTable = b_area_kpa_ember_DefenseTable,
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
        .idleAnimations = TTYD64_imp_22_Ember_IdleAnimations_FireBall,
        .defenseTable = b_area_kpa_ember_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_imp_22_DryBones_Script_RotateBone_MultiAttack_22 = {
    Set(LVar0, 0)
    Label(0)
    Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, LVar0)
    Call(SetPartRotation, ACTOR_SELF, 4, 0, 0, LVar0)
    Call(SetPartRotation, ACTOR_SELF, 5, 0, 0, LVar0)
    Add(LVar0, 60)
    Mod(LVar0, 360)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_imp_22_DryBones_PartsTable_8021CC14_22[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -8, 30 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_22_DryBones_IdleAnimations_8021CA20_22,
        .defenseTable = b_area_kpa_dry_bones_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_kpa_dry_bones_BoneAnims,
        .defenseTable = b_area_kpa_dry_bones_DefenseTable,
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
        .idleAnimations = b_area_kpa_dry_bones_BoneAnims,
        .defenseTable = b_area_kpa_dry_bones_DefenseTable,
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
        .idleAnimations = b_area_kpa_dry_bones_BoneAnims,
        .defenseTable = b_area_kpa_dry_bones_DefenseTable,
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
        .idleAnimations = b_area_kpa_dry_bones_BoneAnims,
        .defenseTable = b_area_kpa_dry_bones_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_imp_22_Magikoopa_StatusTable_80224FE4_22[] = {
    1,  0, 2,  0,  6,  40, 9,  50, 7,  50, 4,  100, 3,  0, 11, 50, 5,  75, 10, 60, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,   33, 0, 38, -1, 39, -1, 41, -2, 0,
};

s32 TTYD64_imp_22_BonyBeetle_StatusTable_80218978_22[] = {
    1,  0, 2,  0,  6,  60, 9,  50, 7,  60, 4,  75, 3,  0, 11, 50, 5,  75, 10, 75, 8, 85,
    31, 0, 32, -1, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, -1, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_22_Koopatrol_StatusTable_80228254_12[] = {
    1,  0, 2,  0,  6,  50, 9,  60, 7,  60, 4,  75, 3,  0, 11, 80, 5,  75, 10, 70, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_imp_22_HammerBros_StatusTable_8021E4F4_22[] = {
    1,  0, 2,  0,  6,  50, 9,  60, 7,  50, 4,  70, 3,  0, 11, 80, 5,  70, 10, 70, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0,  39, 0,  41, -2, 0,
};

// clang-format off
EvtScript TTYD64_imp_22_BonyBeetle_Script_TakeTurn_80219110_22 = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_imp_22_BonyBeetle_Script_Tackle_22)
        CaseEq(1)
            ExecWait(TTYD64_imp_22_BonyBeetle_Script_Tackle_Spikes_22)
        CaseEq(2)
            ExecWait(TTYD64_imp_22_BonyBeetle_Script_FlipOver_22)
        CaseEq(3)
            ExecWait(TTYD64_imp_22_BonyBeetle_Script_FlipOver_Spikes_22)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_HammerBros_Script_TakeTurn_8022028C_22 = {
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
    MulF(LVar0, Float(100.0))
    DivF(LVar0, LVar1)
    IfGt(LVar0, 34)
        ExecWait(TTYD64_imp_22_HammerBros_Script_HammerBros_SingleHammerAttack)
    Else
        ExecWait(TTYD64_imp_22_HammerBros_Script_HammerBros_MultiHammerAttack)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_DryBones_Script_RotateBone_Part4_22 = {
    Set(LVar0, 0)
    Label(0)
    Call(SetPartRotation, ACTOR_SELF, 4, 0, 0, LVar0)
    Add(LVar0, 60)
    Mod(LVar0, 360)
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_DryBones_Script_Init_8021CC84_22 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_22_DryBones_Script_TakeTurn_8021DB48_22))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa_dry_bones_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kpa_dry_bones_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kpa_dry_bones_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_kpa_Formation_0A[] = {
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_Ember_22_Ember,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_EMBER },
    { .actor = &TTYD64_imp_22_Ember_22_Ember,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_EMBER },
    { .actor = &TTYD64_imp_22_Ember_22_Ember,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_EMBER },
};

FormationRow TTYD64_kpa_Formation_0E[] = {
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
};

FormationRow TTYD64_kpa_Formation_16[] = {
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 7 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_14[] = {
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 3 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_05[] = {
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_09[] = {
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
};

FormationRow TTYD64_kpa_Formation_06[] = {
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_2A[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_kpa_Formation_2F[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_kpa_Formation_2D[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_32[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_37[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_1A[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_kpa_Formation_1E[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_1C[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
};

FormationRow TTYD64_kpa_Formation_1D[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .vec = &b_area_kpa_Formation_1D_pos1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .vec = &b_area_kpa_Formation_1D_pos2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .vec = &b_area_kpa_Formation_1D_pos3 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .vec = &b_area_kpa_Formation_1D_pos4 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_24[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_25[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_29[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 7 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

ActorPartBlueprint TTYD64_imp_22_Magikoopa_PartsTable_802250B4_22[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_22_Magikoopa_IdleAnimations_80225170_22,
        .defenseTable = TTYD64_imp_22_Magikoopa_DefenseTable_80224F2C_22,
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
        .idleAnimations = TTYD64_imp_22_Magikoopa_IdleAnimations_802251BC_22,
        .defenseTable = TTYD64_imp_22_Magikoopa_DefenseTable_80224F2C_22,
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
        .idleAnimations = b_area_kpa_magikoopa_BroomAnims,
        .defenseTable = TTYD64_imp_22_Magikoopa_DefenseTable_80224F2C_22,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_imp_22_HammerBros_Script_Init_8021E6A0_22 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_22_HammerBros_Script_TakeTurn_8022028C_22))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kpa_hammer_bro_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kpa_hammer_bro_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_22_Ember_Script_Ember_SpitFlames_LittleFlames = {
    Exec(TTYD64_imp_22_Ember_Script_Ember_SpitFlames_LittleFlames_FlyToGoal)
    Call(GetDistanceToGoal, ACTOR_SELF, LVar0)
    DivF(LVar0, Float(8.0))
    Add(LVar0, 1)
    Wait(LVar0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_kpa_Formation_0D[] = {
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
};

FormationRow TTYD64_kpa_Formation_0B[] = {
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_0C[] = {
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_kpa_Formation_12[] = {
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_kpa_Formation_10[] = {
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
};

FormationRow TTYD64_kpa_Formation_15[] = {
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_13[] = {
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_kpa_Formation_19[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_kpa_Formation_01[] = {
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
};

FormationRow TTYD64_kpa_Formation_04[] = {
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_02[] = {
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
};

FormationRow TTYD64_kpa_Formation_03[] = {
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
};

FormationRow TTYD64_kpa_Formation_08[] = {
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
};

FormationRow TTYD64_kpa_Formation_2B[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
};

FormationRow TTYD64_kpa_Formation_2C[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_2E[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_33[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_kpa_Formation_31[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_35[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
};

FormationRow TTYD64_kpa_Formation_36[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_22[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_kpa_Formation_23[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
};

FormationRow TTYD64_kpa_Formation_20[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
};

FormationRow TTYD64_kpa_Formation_21[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
};

FormationRow TTYD64_kpa_Formation_27[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_28[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

s32 TTYD64_imp_22_Ember_IdleAnimations_8021AE5C_22[] = {
    1,  0x460101, 7, 0x460100, 6, 0x460101, 9, 0x460101, 8, 0x460100,
    11, 0x460101, 5, 0x460100, 4, 0x46010A, 3, 0x46010A, 0,
};

s32 TTYD64_imp_22_BonyBeetle_IdleAnimations_802188C8_22[] = {
    1,  0x550006, 7, 0x550002, 6, 0x55002C, 9, 0x550006, 8, 0x550002,
    11, 0x550006, 5, 0x550002, 4, 0x550028, 3, 0x550028, 0,
};

s32 TTYD64_imp_22_DryBones_IdleAnimations_8021CA20_22[] = {
    1,  0x530002, 7, 0x530000, 6, 0x53000E, 9, 0x530002, 8, 0x530000,
    11, 0x530002, 5, 0x530000, 4, 0x53000D, 3, 0x53000D, 0,
};

s32 TTYD64_imp_22_Koopatrol_IdleAnimations_802281D4_12[] = {
    1,  0x590006, 7, 0x590006, 6, 0x590006, 9, 0x590006, 8, 0x590006,
    11, 0x590006, 5, 0x590006, 4, 0x590006, 3, 0x590006, 0,
};

s32 TTYD64_imp_22_HammerBros_IdleAnimations_8021E490_22[] = {
    1,  0x5A0002, 7, 0x5A0000, 6, 0x5A0011, 9, 0x5A0002, 8, 0x5A0000,
    11, 0x5A0002, 5, 0x5A0000, 4, 0x5A0012, 3, 0x5A0012, 0,
};

s32 TTYD64_imp_22_Koopatrol_IdleAnimations_8022813C_12[] = {
    1,  0x590003, 7, 0x590000, 6, 0x590011, 9, 0x590003, 8, 0x590000,
    11, 0x590003, 5, 0x590000, 4, 0x590013, 3, 0x590013, 0,
};

s32 TTYD64_imp_22_Magikoopa_IdleAnimations_80225170_22[] = {
    1,  0x560001, 7, 0x560000, 6, 0x560008, 9, 0x560001, 8, 0x560000,
    11, 0x560001, 5, 0x560000, 4, 0x560007, 3, 0x560007, 0,
};

s32 TTYD64_imp_22_Koopatrol_IdleAnimations_802280F0_12[] = {
    1,  0x590001, 7, 0x590000, 6, 0x590011, 9, 0x590001, 8, 0x590000,
    11, 0x590001, 5, 0x590000, 4, 0x590013, 3, 0x590013, 0,
};

s32 TTYD64_imp_22_BonyBeetle_IdleAnimations_80218830_22[] = {
    1,  0x550004, 7, 0x550000, 6, 0x55002A, 9, 0x550004, 8, 0x550000,
    11, 0x550004, 5, 0x550000, 4, 0x550026, 3, 0x550026, 0,
};

s32 TTYD64_imp_22_Koopatrol_IdleAnimations_80228188_12[] = {
    1,  0x59000F, 7, 0x590010, 6, 0x590012, 9, 0x59000F, 8, 0x590010,
    11, 0x59000F, 5, 0x590010, 4, 0x590014, 3, 0x590014, 0,
};

s32 TTYD64_imp_22_BonyBeetle_IdleAnimations_8021887C_22[] = {
    1,  0x550005, 7, 0x550001, 6, 0x55002B, 9, 0x550005, 8, 0x550001,
    11, 0x550005, 5, 0x550001, 4, 0x550027, 3, 0x550027, 0,
};

s32 TTYD64_imp_22_Magikoopa_IdleAnimations_802251BC_22[] = {
    1,  0x570001, 7, 0x570000, 6, 0x570008, 9, 0x570001, 8, 0x570000,
    11, 0x570001, 5, 0x570000, 4, 0x570007, 3, 0x570007, 0,
};

s32 TTYD64_imp_22_BonyBeetle_IdleAnimations_80218914_22[] = {
    1,  0x550007, 7, 0x550003, 6, 0x55002D, 9, 0x550007, 8, 0x550003,
    11, 0x550007, 5, 0x550003, 4, 0x550029, 3, 0x550029, 0,
};

FormationRow TTYD64_kpa_Formation_0F[] = {
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
};

FormationRow TTYD64_kpa_Formation_11[] = {
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_kpa_Formation_18[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_kpa_Formation_00[] = {
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
};

FormationRow TTYD64_kpa_Formation_07[] = {
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DRYBONES },
};

FormationRow TTYD64_kpa_Formation_30[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

FormationRow TTYD64_kpa_Formation_34[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
};

FormationRow TTYD64_kpa_Formation_1B[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_HammerBros_22_HammerBros,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_HAMMERBROS },
};

FormationRow TTYD64_kpa_Formation_1F[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
    { .actor = &TTYD64_imp_22_BonyBeetle_22_BonyBeetle,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BONYBEETLE },
};

FormationRow TTYD64_kpa_Formation_26[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
    { .actor = &TTYD64_imp_22_Magikoopa_22_Magikoopa,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MAGIKOOPA },
};

ActorBlueprint TTYD64_imp_22_Magikoopa_22_Magikoopa = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x4D,
    .level = 26,
    .partCount = 1,
    .partsData = TTYD64_imp_22_Magikoopa_PartsTable_80225090_22,
    .initScript = &TTYD64_imp_22_Magikoopa_Script_Init_80225D60_22,
    .statusTable = b_area_kpa_magikoopa_StatusTable,
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

ActorBlueprint TTYD64_imp_22_Magikoopa_22_FlyingMagikoopa = {
    .flags = 0x200,
    .maxHP = 7,
    .type = 0x4E,
    .level = 26,
    .partCount = 3,
    .partsData = TTYD64_imp_22_Magikoopa_PartsTable_802250B4_22,
    .initScript = &TTYD64_imp_22_Magikoopa_Script_Init_80225F20_22,
    .statusTable = TTYD64_imp_22_Magikoopa_StatusTable_80224FE4_22,
    .escapeChance = 40,
    .airLiftChance = 85,
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

ActorBlueprint TTYD64_imp_22_Magikoopa_FlyingMagiclone_22 = {
    .flags = 0x200200,
    .maxHP = 7,
    .type = 0x50,
    .level = 26,
    .partCount = 1,
    .partsData = TTYD64_imp_22_Magikoopa_PartsTable_802292A8_22,
    .initScript = &b_area_kpa_magikoopa_EVS_FlyingClone_Init,
    .statusTable = b_area_kpa_magikoopa_FlyingCloneStatusTable,
    .escapeChance = 40,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 2,
    .size = { 48, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -25, 20 },
    .statusTextOffset = { 1, 34 },
};

ActorBlueprint TTYD64_imp_22_DryBones_22_DryBones = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x47,
    .level = 30,
    .partCount = 5,
    .partsData = TTYD64_imp_22_DryBones_PartsTable_8021CC14_22,
    .initScript = &TTYD64_imp_22_DryBones_Script_Init_8021CC84_22,
    .statusTable = b_area_kpa_dry_bones_StatusTable,
    .escapeChance = 50,
    .airLiftChance = 75,
    .hurricaneChance = 70,
    .spookChance = 10,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 1,
    .size = { 28, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 15 },
    .statusTextOffset = { 3, 27 },
};

ActorBlueprint TTYD64_imp_22_Magikoopa_Magiclone_22 = {
    .flags = 0x200000,
    .maxHP = 7,
    .type = 0x4F,
    .level = 26,
    .partCount = 1,
    .partsData = TTYD64_imp_22_Magikoopa_PartsTable_80229284_22,
    .initScript = &b_area_kpa_magikoopa_EVS_Clone_Init,
    .statusTable = b_area_kpa_magikoopa_CloneStatusTable,
    .escapeChance = 40,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 36, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 32 },
};

ActorBlueprint TTYD64_imp_22_Koopatrol_Koopatrol_12 = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x4C,
    .level = 25,
    .partCount = 1,
    .partsData = TTYD64_imp_22_Koopatrol_PartsTable_8022839C_12,
    .initScript = &TTYD64_imp_22_Koopatrol_Script_Init_802283E8_12,
    .statusTable = TTYD64_imp_22_Koopatrol_StatusTable_80228254_12,
    .escapeChance = 50,
    .airLiftChance = 75,
    .hurricaneChance = 65,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 2,
    .size = { 32, 42 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 32 },
    .statusTextOffset = { 5, 32 },
};

ActorBlueprint TTYD64_imp_22_Koopatrol_22_Koopatrol = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x4C,
    .level = 25,
    .partCount = 1,
    .partsData = TTYD64_imp_22_Koopatrol_PartsTable_8022839C_12,
    .initScript = &TTYD64_imp_22_Koopatrol_Script_Init_802283E8_12,
    .statusTable = TTYD64_imp_22_Koopatrol_StatusTable_80228254_12,
    .escapeChance = 50,
    .airLiftChance = 75,
    .hurricaneChance = 65,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 2,
    .size = { 32, 42 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 32 },
    .statusTextOffset = { 5, 32 },
};

ActorBlueprint TTYD64_imp_22_Ember_22_Ember = {
    .flags = 0x200,
    .maxHP = 10,
    .type = 0x45,
    .level = 24,
    .partCount = 6,
    .partsData = TTYD64_imp_22_Ember_PartsTable_8021AD80_22,
    .initScript = &TTYD64_imp_22_Ember_Script_Init_8021AEB4_22,
    .statusTable = b_area_kpa_ember_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 80,
    .hurricaneChance = 75,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 33, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_22_Ember_Ember_22 = {
    .flags = 0x200,
    .maxHP = 10,
    .type = 0x45,
    .level = 24,
    .partCount = 6,
    .partsData = TTYD64_imp_22_Ember_PartsTable_8021AD80_22,
    .initScript = &TTYD64_imp_22_Ember_Script_Init_8021AEB4_22,
    .statusTable = b_area_kpa_ember_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 80,
    .hurricaneChance = 75,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 33, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_22_BonyBeetle_22_BonyBeetle = {
    .flags = 0x0,
    .maxHP = 8,
    .type = 0x46,
    .level = 25,
    .partCount = 1,
    .partsData = TTYD64_imp_22_BonyBeetle_PartsTable_80218A24_22,
    .initScript = &TTYD64_imp_22_BonyBeetle_Script_Init_80218A70_22,
    .statusTable = TTYD64_imp_22_BonyBeetle_StatusTable_80218978_22,
    .escapeChance = 50,
    .airLiftChance = 70,
    .hurricaneChance = 60,
    .spookChance = 60,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 27, 27 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_22_HammerBros_22_HammerBros = {
    .flags = 0x0,
    .maxHP = 12,
    .type = 0x4B,
    .level = 27,
    .partCount = 6,
    .partsData = TTYD64_imp_22_HammerBros_PartsTable_8021E5A0_22,
    .initScript = &TTYD64_imp_22_HammerBros_Script_Init_8021E6A0_22,
    .statusTable = TTYD64_imp_22_HammerBros_StatusTable_8021E4F4_22,
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

ActorPartBlueprint TTYD64_imp_22_Magikoopa_PartsTable_80225090_22[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_22_Magikoopa_IdleAnimations_80225170_22,
        .defenseTable = TTYD64_imp_22_Magikoopa_DefenseTable_80224F20_22,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_22_Koopatrol_PartsTable_8022839C_12[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_22_Koopatrol_IdleAnimations_802280F0_12,
        .defenseTable = b_area_kpa_koopatrol_DefenseTable,
        .eventFlags = 0x1010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_22_Magikoopa_PartsTable_802292A8_22[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -10, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_22_Magikoopa_IdleAnimations_802251BC_22,
        .defenseTable = TTYD64_imp_22_Magikoopa_DefenseTable_80229120_22,
        .eventFlags = 0x20,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_22_Magikoopa_PartsTable_80229284_22[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_22_Magikoopa_IdleAnimations_80225170_22,
        .defenseTable = TTYD64_imp_22_Magikoopa_DefenseTable_80229114_22,
        .eventFlags = 0x20,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_22_BonyBeetle_PartsTable_80218A24_22[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -3, 21 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_22_BonyBeetle_IdleAnimations_8021887C_22,
        .defenseTable = b_area_kpa_bony_beetle_DefenseTable,
        .eventFlags = 0x1010,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_imp_22_Magikoopa_SpecialFormation_80229328_22[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_Magiclone_22,
      .home = { .vec = &b_area_kpa_magikoopa_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_22_DryBones_SpecialFormation_DryBones_22[] = {
    { .actor = &TTYD64_imp_22_DryBones_22_DryBones,
      .home = { .vec = &b_area_mac_Lee_SummonPos },
      .priority = 100,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_22_Koopatrol_SpecialFormation_8022BBC8_12[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_Koopatrol_12,
      .home = { .vec = &b_area_kpa_koopatrol_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_22_Magikoopa_SpecialFormation_80229344_22[] = {
    { .actor = &TTYD64_imp_22_Magikoopa_FlyingMagiclone_22,
      .home = { .vec = &b_area_kpa_magikoopa_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_kpa_Formation_17[] = {
    { .actor = &TTYD64_imp_22_Koopatrol_22_Koopatrol,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROL },
};

FormationRow TTYD64_imp_22_Ember_SpecialFormation_8021B5A0_22[] = {
    { .actor = &TTYD64_imp_22_Ember_Ember_22,
      .home = { .vec = &b_area_kpa_ember_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

s32 TTYD64_imp_22_Magikoopa_DefenseTable_80229120_22[] = {
    1,
    2,
    0,
};

s32 TTYD64_imp_22_Ember_IdleAnimations_FireBall[] = {
    1,
    0x46010C,
    0,
};

s32 TTYD64_imp_22_Magikoopa_DefenseTable_80224F20_22[] = {
    1,
    2,
    0,
};

s32 TTYD64_imp_22_Koopatrol_IdleAnimations_Koopatrol_Hide_12[] = {
    1,
    0x590005,
    0,
};

s32 TTYD64_imp_22_Magikoopa_DefenseTable_80229114_22[] = {
    1,
    2,
    0,
};

s32 TTYD64_imp_22_Magikoopa_DefenseTable_80224F2C_22[] = {
    1,
    2,
    0,
};

void TTYD64_InstallBattles_kpa(void) {
    Mod_SetBattleList("TTYD64", 0x22, TTYD64_kpa_FormationTable);
}
