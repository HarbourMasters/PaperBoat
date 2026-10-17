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

API_CALLABLE(action_command_stop_leech_init);
API_CALLABLE(action_command_stop_leech_start);
API_CALLABLE(b_area_pra3_duplighost_GetPartnerAndLevel);
API_CALLABLE(b_area_pra3_goombario_clone_ActorJumpToPos);
API_CALLABLE(b_area_pra3_goombario_clone_CalculateTattleCamBoomLength);
API_CALLABLE(b_area_pra3_goombario_clone_CloseTattleWindow);
API_CALLABLE(b_area_pra3_goombario_clone_OpenTattleWindow);
API_CALLABLE(b_area_pra3_goombario_clone_UnkFunc62);
API_CALLABLE(b_area_pra3_gray_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_pra3_gray_magikoopa_ShrinkActor);
API_CALLABLE(b_area_pra3_kooper_clone_UnkActorPosFunc);
API_CALLABLE(b_area_pra3_red_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_pra3_red_magikoopa_ShrinkActor);
API_CALLABLE(b_area_pra3_swoopula_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_pra3_swoopula_SpawnDrainHealthContinueFX);
API_CALLABLE(b_area_pra3_swoopula_SpawnDrainHealthStartFX);
API_CALLABLE(b_area_pra3_watt_clone_SetBackgroundAlpha);
API_CALLABLE(b_area_pra3_watt_clone_UnkBackgroundFunc3);
API_CALLABLE(b_area_pra3_watt_clone_WattFXSetActive);
API_CALLABLE(b_area_pra3_watt_clone_WattFXSetBouncing);
API_CALLABLE(b_area_pra3_watt_clone_WattFXSetEffect);
extern Vec3i b_area_pra3_DuplighostSummonPos;
extern EvtScript b_area_pra3_EVS_Duplighost_OnDeath;
extern s32 b_area_pra3_bombette_clone_DefenseTable[];
extern EvtScript b_area_pra3_bombette_clone_EVS_Init;
extern s32 b_area_pra3_bow_clone_DefenseTable[];
extern EvtScript b_area_pra3_bow_clone_EVS_Idle;
extern s32 b_area_pra3_duplighost_DefenseTable[];
extern EvtScript b_area_pra3_duplighost_EVS_HandleEvent;
extern EvtScript b_area_pra3_duplighost_EVS_HandlePhase;
extern EvtScript b_area_pra3_duplighost_EVS_Idle;
extern EvtScript b_area_pra3_duplighost_EVS_ReturnHome;
extern s32 b_area_pra3_duplighost_FlailingAnims[];
extern s32 b_area_pra3_duplighost_RunAnims[];
extern s32 b_area_pra3_duplighost_StatusTable[];
extern s32 b_area_pra3_goombario_clone_DefenseTable[];
extern EvtScript b_area_pra3_goombario_clone_EVS_ApproachPlayer;
extern EvtScript b_area_pra3_goombario_clone_EVS_CalculateJumpTime;
extern EvtScript b_area_pra3_goombario_clone_EVS_HeadbonkFollowthrough;
extern EvtScript b_area_pra3_goombario_clone_EVS_Idle;
extern s32 b_area_pra3_gray_magikoopa_DefenseTable[];
extern EvtScript b_area_pra3_gray_magikoopa_EVS_Flee;
extern EvtScript b_area_pra3_gray_magikoopa_EVS_HandleEvent;
extern EvtScript b_area_pra3_gray_magikoopa_EVS_Idle;
extern EvtScript b_area_pra3_kooper_clone_EVS_Idle;
extern u8 b_area_pra3_kooper_clone_FlipPosOffsets[];
extern s32 b_area_pra3_kooper_clone_ToppledDefenseTable[];
extern s32 b_area_pra3_kooper_clone_UprightDefenseTable[];
extern s32 b_area_pra3_lakilester_clone_DefenseTable[];
extern EvtScript b_area_pra3_lakilester_clone_EVS_Idle;
extern EvtScript b_area_pra3_lakilester_clone_EVS_TakeTurn;
extern s32 b_area_pra3_lakilester_clone_SpinyAnims[];
extern s32 b_area_pra3_parakarry_clone_DefenseTable[];
extern EvtScript b_area_pra3_parakarry_clone_EVS_Idle;
extern EvtScript b_area_pra3_parakarry_clone_EVS_TakeTurn;
extern Stage b_area_pra3_pra_01;
extern s32 b_area_pra3_red_magikoopa_DefenseTable[];
extern EvtScript b_area_pra3_red_magikoopa_EVS_Flee;
extern EvtScript b_area_pra3_red_magikoopa_EVS_HandleEvent;
extern EvtScript b_area_pra3_red_magikoopa_EVS_Idle;
extern s32 b_area_pra3_sushie_clone_DefenseTable[];
extern EvtScript b_area_pra3_sushie_clone_EVS_Idle;
extern s32 b_area_pra3_swoopula_DefenseTable[];
extern EvtScript b_area_pra3_swoopula_EVS_Idle;
extern s32 b_area_pra3_swoopula_StatusTable[];
extern s32 b_area_pra3_watt_clone_DefenseTable[];
extern EvtScript b_area_pra3_watt_clone_EVS_HandleEvent;
extern EvtScript b_area_pra3_watt_clone_EVS_Idle;
extern s32 b_area_pra3_white_clubba_DefenseTable[];
extern EvtScript b_area_pra3_white_clubba_EVS_HandleEvent;
extern EvtScript b_area_pra3_white_clubba_EVS_Idle;
extern s32 b_area_pra3_white_clubba_StatusTable[];
extern EvtScript TTYD64_imp_21_Swoopula_Script_8021CB94_1C;
extern EvtScript TTYD64_imp_21_Swoopula_Script_TakeTurn_8021E7B4_1C;
extern EvtScript TTYD64_imp_21_Duplighost_Script_TakeTurn_80223F84_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_TakeTurn_8021E3F4_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_TakeTurn_80221CFC_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_8021C8E4_21;
extern EvtScript TTYD64_imp_21_WhiteClubba_Script_TakeTurn_8022B7FC_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_HandleEvent_8021DA98_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_TakeTurn_80222FD0_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_CopyPartner_21;
extern EvtScript TTYD64_imp_21_Swoopula_Script_HandleEvent_8021C414_1C;
extern EvtScript TTYD64_imp_21_RMagikoopa_Script_TakeTurn_8022E6A0_21;
extern EvtScript TTYD64_imp_21_GRYMagikoopa_Script_TakeTurn_80231360_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_8021B178_21;
extern EvtScript TTYD64_imp_21_RMagikoopa_Script_RMagikoopa_WandStrike_21;
extern EvtScript TTYD64_imp_21_GRYMagikoopa_Script_GRYMagikoopa_WandStrike_21;
extern EvtScript TTYD64_imp_21_RMagikoopa_Script_RMagikoopa_ShapeSpell_21;
extern EvtScript TTYD64_imp_21_GRYMagikoopa_Script_GRYMagikoopa_ShapeSpell_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_HandleEvent_802207E0_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_HandleEvent_802253DC_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_LungeAttack_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_HandleEvent_8022176C_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_HandleEvent_8021BD20_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_HandleEvent_80223A14_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_8021ACB4_21;
extern EvtScript TTYD64_imp_21_Swoopula_Script_8021BC30_1C;
extern EvtScript TTYD64_imp_21_Duplighost_Script_8021B804_21;
extern EvtScript TTYD64_imp_21_Swoopula_Script_8021C0B4_1C;
extern EvtScript TTYD64_imp_21_Duplighost_Script_8021D370_21;
extern EvtScript TTYD64_imp_21_Swoopula_Script_8021BA70_1C;
extern EvtScript TTYD64_imp_21_Duplighost_Script_TakeTurn_80226CC0_21;
extern Battle TTYD64_pra3_FormationTable[];
extern s32 TTYD64_imp_21_GRYMagikoopa_StatusTable_8022EDF8_21[];
extern s32 TTYD64_imp_21_Duplighost_StatusTable_802215F4_21[];
extern s32 TTYD64_imp_21_Duplighost_StatusTable_8021BBCC_21[];
extern s32 TTYD64_imp_21_Duplighost_StatusTable_8021D7AC_21[];
extern s32 TTYD64_imp_21_Duplighost_StatusTable_80220668_21[];
extern s32 TTYD64_imp_21_Duplighost_StatusTable_80225264_21[];
extern s32 TTYD64_imp_21_Duplighost_StatusTable_802229CC_21[];
extern s32 TTYD64_imp_21_Duplighost_StatusTable_8021F408_21[];
extern s32 TTYD64_imp_21_Duplighost_StatusTable_802238C0_21[];
extern s32 TTYD64_imp_21_RMagikoopa_StatusTable_8022C138_21[];
extern EvtScript TTYD64_imp_21_RMagikoopa_Script_Init_8022E558_21;
extern EvtScript TTYD64_imp_21_GRYMagikoopa_Script_Init_80231218_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_Init_8021D8A4_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_Init_8021A078_21;
extern FormationRow TTYD64_pra3_Formation_0A[];
extern FormationRow TTYD64_pra3_Formation_04[];
extern EvtScript TTYD64_imp_21_Swoopula_Script_Init_8021B9FC_1C;
extern EvtScript TTYD64_imp_21_Duplighost_Script_TakeTurn_8021D684_21;
extern FormationRow TTYD64_pra3_Formation_0B[];
extern FormationRow TTYD64_pra3_Formation_00[];
extern FormationRow TTYD64_pra3_Formation_05[];
extern FormationRow TTYD64_pra3_Formation_03[];
extern FormationRow TTYD64_pra3_Formation_08[];
extern FormationRow TTYD64_pra3_Formation_09[];
extern FormationRow TTYD64_pra3_Formation_06[];
extern s32 TTYD64_imp_21_Duplighost_IdleAnimations_8021D748_21[];
extern s32 TTYD64_imp_21_Duplighost_IdleAnimations_8022159C_21[];
extern s32 TTYD64_imp_21_Duplighost_IdleAnimations_8021BB74_21[];
extern s32 TTYD64_imp_21_Duplighost_IdleAnimations_80219F10_21[];
extern s32 TTYD64_imp_21_Swoopula_IdleAnimations_8021B964_1C[];
extern s32 TTYD64_imp_21_WhiteClubba_IdleAnimations_8022B130_21[];
extern EvtScript TTYD64_imp_21_Duplighost_Script_Init_80222AE8_21;
extern s32 TTYD64_imp_21_Duplighost_IdleAnimations_80225200_21[];
extern EvtScript TTYD64_imp_21_WhiteClubba_Script_Init_8022B290_21;
extern s32 TTYD64_imp_21_Duplighost_IdleAnimations_80223868_21[];
extern EvtScript TTYD64_imp_21_Duplighost_Script_Init_8021BCC4_21;
extern s32 TTYD64_imp_21_Duplighost_IdleAnimations_8021D6FC_21[];
extern s32 TTYD64_imp_21_Duplighost_IdleAnimations_80220610_21[];
extern s32 TTYD64_imp_21_Duplighost_IdleAnimations_8021F3B0_21[];
extern s32 TTYD64_imp_21_Duplighost_IdleAnimations_8022296C_21[];
extern EvtScript TTYD64_imp_21_Duplighost_Script_Init_80225380_21;
extern EvtScript TTYD64_imp_21_Duplighost_Script_Init_80221710_21;
extern s32 TTYD64_imp_21_GRYMagikoopa_IdleAnimations_8022F030_21[];
extern EvtScript TTYD64_imp_21_Duplighost_Script_Init_80220784_21;
extern s32 TTYD64_imp_21_Swoopula_IdleAnimations_8021B9B0_1C[];
extern s32 TTYD64_imp_21_RMagikoopa_IdleAnimations_8022C370_21[];
extern EvtScript TTYD64_imp_21_Duplighost_Script_Init_802239B8_21;
extern ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_802216A0_21[];
extern ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_80222A78_21[];
extern ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_80225310_21[];
extern ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_80220714_21[];
extern FormationRow TTYD64_pra3_Formation_02[];
extern FormationRow TTYD64_pra3_Formation_07[];
extern ActorBlueprint TTYD64_imp_21_Duplighost_GhostParakarry_21;
extern ActorBlueprint TTYD64_imp_21_Duplighost_GhostWatt_21;
extern ActorBlueprint TTYD64_imp_21_Duplighost_GhostBow_21;
extern ActorBlueprint TTYD64_imp_21_Duplighost_GhostSushie_21;
extern ActorBlueprint TTYD64_imp_21_GRYMagikoopa_21_GRYMagikoopa;
extern ActorBlueprint TTYD64_imp_21_Duplighost_GhostBombette_21;
extern ActorBlueprint TTYD64_imp_21_Duplighost_21_Duplighost;
extern ActorBlueprint TTYD64_imp_21_Duplighost_GhostLakilester_21;
extern ActorBlueprint TTYD64_imp_21_Swoopula_21_Swoopula;
extern ActorBlueprint TTYD64_imp_21_WhiteClubba_21_WhiteClubba;
extern ActorBlueprint TTYD64_imp_21_Duplighost_GhostKooper_21;
extern ActorBlueprint TTYD64_imp_21_Duplighost_GhostGoombario_21;
extern ActorBlueprint TTYD64_imp_21_RMagikoopa_21_RMagikoopa;
extern ActorPartBlueprint TTYD64_imp_21_GRYMagikoopa_PartsTable_8022EF50_21[];
extern ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_8021A02C_21[];
extern ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_8022396C_21[];
extern ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_8021D858_21[];
extern ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_8021BC78_21[];
extern ActorPartBlueprint TTYD64_imp_21_WhiteClubba_PartsTable_8022B244_21[];
extern ActorPartBlueprint TTYD64_imp_21_RMagikoopa_PartsTable_8022C290_21[];
extern ActorPartBlueprint TTYD64_imp_21_Swoopula_PartsTable_8021B918_1C[];
extern ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_8021F4B4_21[];
extern FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_80222950_21[];
extern FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_80226484_21[];
extern FormationRow TTYD64_pra3_Formation_01[];
extern FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_8022384C_21[];
extern FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_80221580_21[];
extern FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_802205F4_21[];
extern FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_8021D6E0_21[];
extern FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_8021F394_21[];
extern FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_802251E4_21[];
extern Vec3i TTYD64_pra3_Vector3D_802324A0;
extern Vec3i TTYD64_pra3_Vector3D_802324AC;
extern Vec3i TTYD64_pra3_Vector3D_802324B8;
API_CALLABLE(TTYD64_imp_21_Duplighost_Function_80219524_21);

API_CALLABLE(TTYD64_imp_21_Duplighost_Function_80219524_21) {
    s32 partnerID = evt_get_variable(script, *script->ptrReadPos);
    Actor* actor = get_actor(script->owner1.actorID);
    FormationRow* formation = NULL;

    switch (partnerID) {
        case PARTNER_GOOMBARIO:
            formation = TTYD64_imp_21_Duplighost_SpecialFormation_8021D6E0_21;
            break;
        case PARTNER_KOOPER:
            formation = TTYD64_imp_21_Duplighost_SpecialFormation_8021F394_21;
            break;
        case PARTNER_BOMBETTE:
            formation = TTYD64_imp_21_Duplighost_SpecialFormation_802205F4_21;
            break;
        case PARTNER_PARAKARRY:
            formation = TTYD64_imp_21_Duplighost_SpecialFormation_80221580_21;
            break;
        case PARTNER_BOW:
            formation = TTYD64_imp_21_Duplighost_SpecialFormation_80222950_21;
            break;
        case PARTNER_WATT:
            formation = TTYD64_imp_21_Duplighost_SpecialFormation_8022384C_21;
            break;
        case PARTNER_SUSHIE:
            formation = TTYD64_imp_21_Duplighost_SpecialFormation_802251E4_21;
            break;
        case PARTNER_LAKILESTER:
            formation = TTYD64_imp_21_Duplighost_SpecialFormation_80226484_21;
            break;
    }

    formation->priority = actor->turnPriority;

    return ApiStatus_DONE2;
}

// clang-format off
EvtScript TTYD64_imp_21_Swoopula_Script_8021CB94_1C = {
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
            ExecWait(TTYD64_imp_21_Swoopula_Script_8021BA70_1C)
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
                Call(b_area_pra3_swoopula_SpawnDrainHealthStartFX, LVar0, LVar1, LVar2, LVar3)
                Thread
                    Wait(15)
                    Call(PlaySoundAtActor, ACTOR_SELF, 604)
                    Call(b_area_pra3_swoopula_SpawnDrainHealthContinueFX, LVar0, LVar1, LVar2, LVar3)
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
    ExecWait(TTYD64_imp_21_Swoopula_Script_8021BA70_1C)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_21_Swoopula_Script_TakeTurn_8021E7B4_1C = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_21_Swoopula_Script_8021CB94_1C)
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
            ExecWait(TTYD64_imp_21_Swoopula_Script_8021BA70_1C)
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
                Call(b_area_pra3_swoopula_SpawnDrainHealthStartFX, LVar0, LVar1, LVar2, LVar3)
                Thread
                    Wait(15)
                    Call(PlaySoundAtActor, ACTOR_SELF, 604)
                    Call(b_area_pra3_swoopula_SpawnDrainHealthContinueFX, LVar0, LVar1, LVar2, LVar3)
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
    ExecWait(TTYD64_imp_21_Swoopula_Script_8021BA70_1C)
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
EvtScript TTYD64_imp_21_Duplighost_Script_TakeTurn_80223F84_21 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 70, 0, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, LVar0)
    Div(LVar3, Float(3.0))
    Set(LVarA, LVar3)
    IfLt(LVarA, 0)
        Mul(LVarA, -1)
    EndIf
    Call(MoveBattleCamOver, LVarA)
    Call(SetAnimation, ACTOR_SELF, 1, 0xF0003)
    Call(RunToGoal, ACTOR_SELF, LVarA, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xF0001)
    Wait(10)
    Call(UseBattleCamPreset, 8)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(AddBattleCamDist, -50)
    Call(MoveBattleCamOver, 30)
    Call(SetBattleCamTargetingModes, 1, 1, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0xF0004)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0xF0008)
    Wait(15)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(SetAnimation, ACTOR_SELF, 1, 0xF0005)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
                Set(LVar0, 0)
                Loop(10)
                    Add(LVar0, 36)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 20)
            EndThread
            Thread
                Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                Switch(LVar0)
                    CaseEq(0)
                        Wait(13)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
                    CaseEq(1)
                        Wait(13)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0498046875), Float(1.0498046875), Float(1.0498046875))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.099609375), Float(1.099609375), Float(1.099609375))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.150390625), Float(1.150390625), Float(1.150390625))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.2001953125), Float(1.2001953125), Float(1.2001953125))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.25), Float(1.25), Float(1.25))
                    CaseEq(2)
                        Wait(13)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.099609375), Float(1.099609375), Float(1.099609375))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.2001953125), Float(1.2001953125), Float(1.2001953125))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.2998046875), Float(1.2998046875), Float(1.2998046875))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.400390625), Float(1.400390625), Float(1.400390625))
                        Wait(1)
                        Call(SetPartScale, ACTOR_SELF, 1, Float(1.5), Float(1.5), Float(1.5))
                EndSwitch
            EndThread
            Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8244)
            Call(SetGoalToTarget, ACTOR_SELF)
            Thread
                Call(SetAnimation, ACTOR_SELF, 1, 0xF0005)
                Wait(10)
                Call(SetAnimation, ACTOR_SELF, 1, 0xF0006)
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xF0007)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
            Call(LandJump, ACTOR_SELF)
            Call(PlaySoundAtActor, ACTOR_SELF, 666)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(AddGoalPos, ACTOR_SELF, -15, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 666)
            Call(AddGoalPos, ACTOR_SELF, -10, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 666)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0xF0003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Call(SetAnimation, ACTOR_SELF, 1, 0xF0005)
    Thread
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
        Set(LVar0, 0)
        Loop(10)
            Add(LVar0, 36)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 20)
    EndThread
    Thread
        Call(GetActorVar, ACTOR_SELF, 1, LVar0)
        Switch(LVar0)
            CaseEq(0)
                Wait(13)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.099609375), Float(1.099609375), Float(1.099609375))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.099609375), Float(1.099609375), Float(1.099609375))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.2001953125), Float(1.2001953125), Float(1.2001953125))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.2001953125), Float(1.2001953125), Float(1.2001953125))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.2998046875), Float(1.2998046875), Float(1.2998046875))
            CaseEq(1)
                Wait(13)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.150390625), Float(1.150390625), Float(1.150390625))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.2001953125), Float(1.2001953125), Float(1.2001953125))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.349609375), Float(1.349609375), Float(1.349609375))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.400390625), Float(1.400390625), Float(1.400390625))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.5498046875), Float(1.5498046875), Float(1.5498046875))
            CaseEq(2)
                Wait(13)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.2001953125), Float(1.2001953125), Float(1.2001953125))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.2998046875), Float(1.2998046875), Float(1.2998046875))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.5), Float(1.5), Float(1.5))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.599609375), Float(1.599609375), Float(1.599609375))
                Wait(1)
                Call(SetPartScale, ACTOR_SELF, 1, Float(1.7998046875), Float(1.7998046875), Float(1.7998046875))
        EndSwitch
    EndThread
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8244)
    Call(SetGoalToTarget, ACTOR_SELF)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0xF0005)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, 1, 0xF0006)
    EndThread
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xF0007)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
    Thread
        Wait(3)
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
    EndThread
    Call(GetActorVar, ACTOR_SELF, 1, LVarA)
    Switch(LVarA)
        CaseEq(0)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 3, 32)
        CaseEq(1)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 4, 32)
        CaseEq(2)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 5, 32)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0xF0006)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 60)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 666)
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 666)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 666)
            Add(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 666)
            Call(SetAnimation, ACTOR_SELF, 1, 0xF0001)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0xF0003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
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
EvtScript TTYD64_imp_21_Duplighost_Script_TakeTurn_8021E3F4_21 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    IfEq(LVar0, 1)
        Call(GetActorVar, ACTOR_SELF, 4, LVar0)
        Sub(LVar0, 1)
        IfGt(LVar0, 0)
            Call(SetActorVar, ACTOR_SELF, 4, LVar0)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
            Wait(30)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
        Else
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
            Wait(20)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA0019)
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
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA0004)
            Call(SetActorVar, ACTOR_SELF, 3, 0)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_pra3_kooper_clone_UprightDefenseTable))
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_21_Duplighost_IdleAnimations_8021D6FC_21))
            Call(SetTargetOffset, ACTOR_SELF, 1, -2, 38)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -3, -9)
        EndIf
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Return
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0xA000E)
    Call(PlaySoundAtActor, ACTOR_SELF, 0)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0xA000A)
    Call(PlaySoundAtActor, ACTOR_SELF, 8204)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 75)
    Call(SetBattleCamTargetingModes, 1, 1, 1)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Set(LVar0, 10)
        CaseEq(1)
            Set(LVar0, 20)
        CaseEq(2)
            Set(LVar0, 30)
    EndSwitch
    Set(LVar9, 0)
    Loop(LVar0)
        Add(LVar9, 1)
        Switch(LVar9)
            CaseLt(20)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA000A)
                Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
            CaseEq(20)
                Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseLt(40)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA000B)
                Call(SetActorSpeed, ACTOR_SELF, Float(12.0))
            CaseEq(40)
                Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseLt(50)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA000C)
                Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
            CaseEq(50)
                Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            CaseLt(60)
                Call(SetAnimation, ACTOR_SELF, 1, 0xA000D)
                Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            CaseEq(60)
                Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        EndSwitch
        Wait(1)
    EndLoop
    Call(PlaySoundAtActor, ACTOR_SELF, 8202)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 15)
    Call(AddActorDecoration, ACTOR_SELF, 0, 0, 5)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Call(b_area_pra3_kooper_clone_UnkActorPosFunc)
                Call(RemoveActorDecoration, ACTOR_SELF, 0, 0)
            EndThread
            Wait(4)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA0009)
            Call(SetActorRotationOffset, ACTOR_SELF, -8, 0, 0)
            Set(LVar0, 0)
            Loop(2)
                Add(LVar0, 30)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                Wait(1)
            EndLoop
            Wait(5)
            Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
            Call(PlayEffect_impl, 29, 1, LVar4, LVar5, LVar6, 16, 4, 0, 10, 0, 0, 0, 0, 0)
            Loop(5)
                Add(LVar0, -12)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                Wait(1)
            EndLoop
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 2)
            Wait(2)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, -2)
            Wait(2)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA000F)
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA0006)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.5))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(RemoveActorDecoration, ACTOR_SELF, 0, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 2, 32)
        CaseEq(1)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 3, 32)
        CaseEq(2)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 5, 32)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 8)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 60)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Add(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA000F)
            Wait(15)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA0006)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.5))
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
EvtScript TTYD64_imp_21_Duplighost_Script_TakeTurn_80221CFC_21 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 195)
    Thread
        Set(LVar0, 200)
        Loop(20)
            Sub(LVar0, 10)
            Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Wait(10)
    Call(UseBattleCamPreset, 1)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0xD0003)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Call(AddGoalPos, ACTOR_SELF, 4, -4, 0)
        Else
            Call(AddGoalPos, ACTOR_SELF, 10, -10, 0)
        EndIf
        Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
        Call(SetAnimation, ACTOR_SELF, 1, 0xD0001)
    EndThread
    Wait(15)
    Call(UseBattleCamPreset, 15)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 193)
    Set(LVar0, 55)
    Loop(20)
        Add(LVar0, 10)
        Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_SELF, 1, 255)
    Call(SetAnimation, ACTOR_SELF, 1, 0xD0005)
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(15)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(UseBattleCamPreset, 2)
            Call(SetPartScale, ACTOR_SELF, 1, Float(1.400390625), Float(1.400390625), Float(1.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0007)
            Wait(2)
            Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
            Set(LVar0, 0)
            Loop(20)
                Add(LVar0, -45)
                Call(SetActorYaw, ACTOR_SELF, LVar0)
                Wait(1)
            EndLoop
            Call(SetActorYaw, ACTOR_SELF, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0xD001A)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 3)
            Wait(30)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0001)
            Wait(10)
            Call(PlaySoundAtActor, ACTOR_SELF, 195)
            Thread
                Set(LVar0, 200)
                Loop(20)
                    Sub(LVar0, 10)
                    Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0003)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0001)
            Call(PlaySoundAtActor, ACTOR_SELF, 193)
            Call(YieldTurn)
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
    Set(LVarA, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar8)
    Switch(LVar8)
        CaseEq(0)
            Set(LVar8, 4)
        CaseEq(1)
            Set(LVar8, 5)
        CaseEq(2)
            Set(LVar8, 6)
    EndSwitch
    Set(LVar7, LVar8)
    Loop(LVar7)
        Call(PlaySoundAtActor, ACTOR_SELF, 8217)
        Add(LVarA, 1)
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.400390625), Float(1.400390625), Float(1.0))
        IfEq(LFlag0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0007)
            Set(LFlag0, 1)
            IfEq(LVarA, LVar8)
                Call(SetDamageSource, 12)
            Else
                Call(SetDamageSource, 10)
            EndIf
        Else
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0008)
            Set(LFlag0, 0)
            IfEq(LVarA, LVar8)
                Call(SetDamageSource, 13)
            Else
                Call(SetDamageSource, 11)
            EndIf
        EndIf
        Wait(2)
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
        Thread
            Call(ShakeCam, 1, 0, 2, Float(0.5))
            Call(ShakeCam, 1, 0, 2, Float(1.5))
            Call(ShakeCam, 1, 0, 1, Float(0.5))
            Call(ShakeCam, 1, 0, 1, Float(0.2001953125))
        EndThread
        Call(GetActorVar, ACTOR_SELF, 1, LVar9)
        Switch(LVar9)
            CaseEq(0)
                Wait(2)
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8192, 0, 0, 1, 16)
            CaseEq(1)
                Wait(2)
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8192, 0, 0, 1, 16)
            CaseEq(2)
                Wait(2)
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8192, 0, 0, 1, 16)
        EndSwitch
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 1, 0xD0001)
        Call(GetActorHP, 0, LVar1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(10)
            Call(PlaySoundAtActor, ACTOR_SELF, 195)
            Thread
                Set(LVar0, 200)
                Loop(20)
                    Sub(LVar0, 10)
                    Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Wait(10)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0003)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Call(SetAnimation, ACTOR_SELF, 1, 0xD0001)
            Call(PlaySoundAtActor, ACTOR_SELF, 193)
            Call(YieldTurn)
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
EvtScript TTYD64_imp_21_Duplighost_Script_8021C8E4_21 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    ExecWait(b_area_pra3_goombario_clone_EVS_ApproachPlayer)
    ExecWait(b_area_pra3_goombario_clone_EVS_CalculateJumpTime)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        SetF(LVar0, Float(7.2001953125))
        SetF(LVar1, Float(7.599609375))
        SetF(LVar1, Float(3.599609375))
    Else
        Set(LVar0, 18)
        Set(LVar1, 19)
        Set(LVar2, 9)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x90007)
    Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, LVar1, 0)
    Wait(1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x90006)
    Call(SetActorDispOffset, ACTOR_SELF, 0, LVar2, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 0, 0, 5)
    Call(SetJumpAnimations, ACTOR_SELF, 1, 0x90006, 0x90006, 0x90006)
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8205)
    Call(b_area_pra3_goombario_clone_UnkFunc62, LVarA, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetJumpAnimations, ACTOR_SELF, 1, 0x90006, 0x90006, 0x90006)
            Call(b_area_pra3_goombario_clone_ActorJumpToPos)
            Thread
                Call(ShakeCam, 1, 0, 5, Float(1.0))
            EndThread
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(20)
            Call(YieldTurn)
            ExecWait(b_area_pra3_goombario_clone_EVS_HeadbonkFollowthrough)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    ChildThread
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.099609375), Float(0.7998046875), Float(1.0))
        Wait(1)
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.2998046875), Float(0.5), Float(1.0))
        Wait(1)
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
    EndChildThread
    Wait(1)
    Wait(2)
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8320, 0, 0, 1, 16)
        CaseEq(1)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8320, 0, 0, 2, 16)
        CaseEq(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8320, 0, 0, 3, 16)
    EndSwitch
    Call(GetActorHP, 0, LVar0)
    IfEq(LVar0, 0)
        Goto(100)
    EndIf
    Set(LVarA, 24)
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Thread
                Wait(4)
                Set(LVar0, 0)
                Loop(6)
                    Add(LVar0, 30)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetJumpAnimations, ACTOR_SELF, 1, 0x90006, 0x90006, 0x90006)
            Call(PlaySoundAtActor, ACTOR_SELF, 641)
            Call(b_area_pra3_goombario_clone_UnkFunc62, LVarA, 3)
        CaseEq(1)
            Thread
                Wait(4)
                Set(LVar0, 0)
                Loop(6)
                    Add(LVar0, 30)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnableActorBlur, ACTOR_SELF, 1)
            Call(SetJumpAnimations, ACTOR_SELF, 1, 0x90006, 0x90006, 0x90006)
            Call(PlaySoundAtActor, ACTOR_SELF, 641)
            Call(b_area_pra3_goombario_clone_UnkFunc62, LVarA, 3)
            Call(EnableActorBlur, ACTOR_SELF, 0)
        CaseEq(2)
            Thread
                Wait(4)
                Set(LVar0, 0)
                Loop(6)
                    Add(LVar0, 30)
                    Call(SetActorRotation, ACTOR_SELF, 0, -0xEE6B280, LVar0)
                    Wait(1)
                EndLoop
                Call(SetAnimation, ACTOR_SELF, 1, 0x90006)
            EndThread
            Thread
                Set(LVar0, 0)
                Loop(LVarA)
                    Add(LVar0, 133)
                    Call(SetActorRotation, ACTOR_SELF, -0xEE6B280, LVar0, -0xEE6B280)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnableActorBlur, ACTOR_SELF, 1)
            Call(SetJumpAnimations, ACTOR_SELF, 1, 0x90006, 0x90006, 0x90006)
            Call(PlaySoundAtActor, ACTOR_SELF, 641)
            Call(b_area_pra3_goombario_clone_UnkFunc62, LVarA, 3)
            Call(EnableActorBlur, ACTOR_SELF, 0)
    EndSwitch
    ChildThread
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.099609375), Float(0.7998046875), Float(1.0))
        Wait(1)
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.2998046875), Float(0.5), Float(1.0))
        Wait(1)
        Call(SetPartScale, ACTOR_SELF, 1, Float(1.0), Float(1.0), Float(1.0))
    EndChildThread
    Wait(1)
    Wait(2)
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8320, 0, 0, 1, 32)
        CaseEq(1)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8320, 0, 0, 2, 32)
        CaseEq(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 8320, 0, 0, 3, 32)
    EndSwitch
    Label(100)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(YieldTurn)
            ExecWait(b_area_pra3_goombario_clone_EVS_HeadbonkFollowthrough)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_21_WhiteClubba_Script_TakeTurn_8022B7FC_21 = {
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
EvtScript TTYD64_imp_21_Duplighost_Script_HandleEvent_8021DA98_21 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Call(GetLastElement, LVar1)
            IfFlag(LVar1, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA0011)
                ExecWait(TTYD64_imp_21_Duplighost_Script_8021ACB4_21)
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA0011)
                ExecWait(Ref(EVS_Enemy_Hit))
            EndIf
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0012)
            SetConst(LVar2, 0xA0013)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0012)
            SetConst(LVar2, 0xA0013)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0013)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0011)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0011)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0011)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 3, 1)
            Call(SetActorVar, ACTOR_SELF, 4, 1)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_pra3_kooper_clone_ToppledDefenseTable))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_21_Duplighost_IdleAnimations_8021D748_21))
            Call(SetTargetOffset, ACTOR_SELF, 1, 5, 15)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, -6)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA0011)
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
            UseBuf(Ref(b_area_pra3_kooper_clone_FlipPosOffsets))
            Loop(22)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xA0019)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0xA0004)
                CaseEq(1)
                    Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0xA0019)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0011)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0011)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            IfEq(LVar0, 1)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA0019)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xA0004)
                ExecWait(Ref(EVS_Enemy_Recover))
            EndIf
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0006)
            SetConst(LVar2, 0xA0011)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0xA0006)
                CaseEq(1)
                    Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0xA0019)
            EndSwitch
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(GetStatusFlags, ACTOR_SELF, LVar0)
                    IfNotFlag(LVar0, 0x35D000)
                        IfFlag(LVar0, 0x80000)
                            Call(SetActorDispOffset, ACTOR_SELF, 0, 1, 0)
                        Else
                            Call(SetActorDispOffset, ACTOR_SELF, 0, 3, 0)
                        EndIf
                    EndIf
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0xA0011)
                CaseEq(1)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0xA0019)
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
EvtScript TTYD64_imp_21_Duplighost_Script_TakeTurn_80222FD0_21 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 350)
    Call(SetBattleCamOffsetY, 40)
    Call(MoveBattleCamOver, 80)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0xE0003)
    Call(b_area_pra3_watt_clone_WattFXSetEffect, 1)
    Call(AddGoalPos, ACTOR_SELF, 15, -10, 5)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
    Call(SetAnimation, ACTOR_SELF, 1, 0xE0001)
    Call(b_area_pra3_watt_clone_WattFXSetEffect, 0)
    Wait(5)
    Call(b_area_pra3_watt_clone_WattFXSetBouncing, 0)
    Call(AddGoalPos, ACTOR_SELF, 25, 20, 0)
    Call(FlyToGoal, ACTOR_SELF, 15, -20, 10)
    Call(SetAnimation, ACTOR_SELF, 1, 0xE0005)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(FlyToGoal, ACTOR_SELF, 5, 0, 10)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Wait(5)
                Call(SetAnimation, ACTOR_SELF, 1, 0xE0001)
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -40, 10, 0)
            Call(FlyToGoal, ACTOR_SELF, 10, -20, 4)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(b_area_pra3_watt_clone_WattFXSetActive, 1)
            Call(b_area_pra3_watt_clone_WattFXSetBouncing, 1)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0xE0003)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Call(SetAnimation, ACTOR_SELF, 1, 0xE0001)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(b_area_pra3_watt_clone_WattFXSetActive, 0)
    Set(LVarA, 40)
    Call(AddBattleCamDist, -75)
    Call(MoveBattleCamOver, LVarA)
    Call(SetBattleCamTargetingModes, 0, 0, 1)
    Call(PlaySoundAtActor, ACTOR_SELF, 649)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 4)
        Call(PlayEffect_impl, 51, 8, LVar0, LVar1, LVar2, Float(0.51953125), LVarA, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 12)
        Call(PlayEffect_impl, 51, 8, LVar0, LVar1, LVar2, Float(1.2998046875), LVarA, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Call(b_area_pra3_watt_clone_UnkBackgroundFunc3)
    Set(LVar9, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xE0006)
    Loop(LVarA)
        Add(LVar9, 3)
        IfGt(LVar9, 200)
            Set(LVar9, 200)
        EndIf
        Call(b_area_pra3_watt_clone_SetBackgroundAlpha, LVar9)
        Wait(1)
    EndLoop
    Call(SetAnimation, ACTOR_SELF, 1, 0xE0001)
    Call(SetActorPaletteEffect, ACTOR_SELF, 1, 9)
    Call(AddBattleCamDist, 75)
    Call(MoveBattleCamOver, 5)
    Thread
        Wait(2)
        Call(b_area_pra3_watt_clone_SetBackgroundAlpha, 0)
    EndThread
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000020, 0xFFFF, 0, 3, 32)
        CaseEq(1)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000020, 0xFFFF, 0, 4, 32)
        CaseEq(2)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000020, 0xFFFF, 0, 5, 32)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(b_area_pra3_watt_clone_WattFXSetActive, 1)
            Call(b_area_pra3_watt_clone_WattFXSetBouncing, 1)
            Call(AddGoalPos, ACTOR_SELF, 25, 10, 0)
            Call(FlyToGoal, ACTOR_SELF, 15, -10, 10)
            Wait(15)
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0xE0003)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Call(SetAnimation, ACTOR_SELF, 1, 0xE0001)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_21_Duplighost_Script_CopyPartner_21 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_SELF, 8376)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4E0006)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar1, 8)
        SetF(LVar3, Float(0.400390625))
    Else
        Add(LVar1, 20)
        SetF(LVar3, Float(1.0))
    EndIf
    Call(PlayEffect_impl, 19, 1, LVar0, LVar1, LVar2, LVar3, 40, 0, 0, 0, 0, 0, 0, 0)
    Call(b_area_pra3_watt_clone_UnkBackgroundFunc3)
    Call(MakeLerp, 0, 200, 20, 0)
    Label(0)
    Call(UpdateLerp)
    Call(b_area_pra3_watt_clone_SetBackgroundAlpha, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    Wait(10)
    Call(b_area_pra3_duplighost_GetPartnerAndLevel, LVar5, LVar6)
    Call(TTYD64_imp_21_Duplighost_Function_80219524_21, LVar5)
    Switch(LVar5)
        CaseEq(1)
            Call(SummonEnemy, Ref(TTYD64_imp_21_Duplighost_SpecialFormation_8021D6E0_21), 0)
        CaseEq(2)
            Call(SummonEnemy, Ref(TTYD64_imp_21_Duplighost_SpecialFormation_8021F394_21), 0)
        CaseEq(3)
            Call(SummonEnemy, Ref(TTYD64_imp_21_Duplighost_SpecialFormation_802205F4_21), 0)
        CaseEq(4)
            Call(SummonEnemy, Ref(TTYD64_imp_21_Duplighost_SpecialFormation_80221580_21), 0)
        CaseEq(9)
            Call(SummonEnemy, Ref(TTYD64_imp_21_Duplighost_SpecialFormation_80222950_21), 0)
        CaseEq(6)
            Call(SummonEnemy, Ref(TTYD64_imp_21_Duplighost_SpecialFormation_8022384C_21), 0)
        CaseEq(7)
            Call(SummonEnemy, Ref(TTYD64_imp_21_Duplighost_SpecialFormation_802251E4_21), 0)
        CaseEq(8)
            Call(SummonEnemy, Ref(TTYD64_imp_21_Duplighost_SpecialFormation_80226484_21), 0)
    EndSwitch
    Set(LVarA, LVar0)
    Call(CopyStatusEffects, ACTOR_SELF, LVarA)
    Call(SetBattleVar, 3, LVar5)
    Call(PlaySoundAtActor, ACTOR_SELF, 717)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 3)
        Add(LVar2, 5)
        Loop(3)
            Call(PlayEffect_impl, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(3)
        EndLoop
    EndThread
    Wait(5)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20001, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x800000, 0)
    Call(SetActorFlagBits, ACTOR_SELF, 0x400004, 1)
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(SetEnemyHP, LVarA, LVar0)
    Call(CopyBuffs, ACTOR_SELF, LVarA)
    Call(GetOwnerID, LVar0)
    Call(SetActorVar, LVarA, 0, LVar0)
    Call(SetActorVar, LVarA, 1, LVar6)
    Wait(20)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Thread
        Call(MakeLerp, 200, 0, 20, 0)
        Label(1)
        Call(UpdateLerp)
        Call(b_area_pra3_watt_clone_SetBackgroundAlpha, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(1)
        EndIf
    EndThread
    Call(SetActorSounds, LVarA, 2, 0, 0)
    Switch(LVar5)
        CaseEq(8)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, LVarA, Float(0.009765625))
            Call(SetGoalPos, LVarA, LVar0, 10, LVar2)
            Call(JumpToGoal, LVarA, 10, 0, 0, 0)
            Wait(10)
        CaseOrEq(6)
        CaseOrEq(9)
        CaseOrEq(4)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, LVarA, Float(0.009765625))
            Call(SetGoalPos, LVarA, LVar0, 30, LVar2)
            Call(JumpToGoal, LVarA, 20, 0, 0, 0)
        EndCaseGroup
    EndSwitch
    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(ForceHomePos, LVarA, LVar0, LVar1, LVar2)
    Call(HPBarToHome, LVarA)
    Call(ResetActorSounds, LVarA, 2)
    Wait(20)
    Call(SetActorPos, ACTOR_SELF, 0, -1000, 0)
    Call(ForceHomePos, ACTOR_SELF, 0, -1000, 0)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_21_Swoopula_Script_HandleEvent_8021C414_1C = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_21_Swoopula_Script_8021BC30_1C)
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
                ExecWait(TTYD64_imp_21_Swoopula_Script_8021C0B4_1C)
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
                ExecWait(TTYD64_imp_21_Swoopula_Script_8021C0B4_1C)
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
            ExecWait(TTYD64_imp_21_Swoopula_Script_8021BA70_1C)
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
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_21_Swoopula_IdleAnimations_8021B9B0_1C))
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(TTYD64_imp_21_Swoopula_Script_8021BA70_1C)
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
EvtScript TTYD64_imp_21_RMagikoopa_Script_TakeTurn_8022E6A0_21 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_pra3_red_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
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
        ExecWait(b_area_pra3_red_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        ExecWait(TTYD64_imp_21_RMagikoopa_Script_RMagikoopa_ShapeSpell_21)
    Else
        ExecWait(TTYD64_imp_21_RMagikoopa_Script_RMagikoopa_WandStrike_21)
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
EvtScript TTYD64_imp_21_GRYMagikoopa_Script_TakeTurn_80231360_21 = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_pra3_gray_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
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
        ExecWait(b_area_pra3_gray_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        ExecWait(TTYD64_imp_21_GRYMagikoopa_Script_GRYMagikoopa_ShapeSpell_21)
    Else
        ExecWait(TTYD64_imp_21_GRYMagikoopa_Script_GRYMagikoopa_WandStrike_21)
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
EvtScript TTYD64_imp_21_Duplighost_Script_8021B178_21 = {
    Set(LVar9, LVar0)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(GetActorPos, ACTOR_SELF, LVar2, LVar3, LVar4)
    Add(LVar2, 10)
    Add(LVar3, 10)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    ExecWait(Ref(EVS_Enemy_ShockHit))
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    Call(UseIdleAnimation, LVarA, 0)
    Call(HideHealthBar, LVarA)
    Call(CopyStatusEffects, ACTOR_SELF, LVarA)
    Call(PlaySoundAtActor, ACTOR_SELF, 717)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 3)
        Add(LVar2, 5)
        Loop(3)
            Call(PlayEffect_impl, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(3)
        EndLoop
    EndThread
    Wait(5)
    Call(GetActorHP, ACTOR_SELF, LVarB)
    Call(SetEnemyHP, LVarA, LVarB)
    Call(CopyBuffs, ACTOR_SELF, LVarA)
    Call(GetActorPos, ACTOR_SELF, LVarB, LVarC, LVarD)
    Call(SetActorPos, LVarA, LVarB, LVarC, LVarD)
    Call(SetPartFlagBits, LVarA, 1, 0x800000, 1)
    Call(SetPartFlagBits, LVarA, 1, 0x20001, 0)
    Call(SetActorFlagBits, LVarA, 0x400004, 0)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
    Call(SetActorVar, LVarA, 8, 3)
    Call(SetPartFlagBits, ACTOR_SELF, LVar9, 1, 1)
    Call(SetIdleAnimations, LVarA, 1, Ref(b_area_pra3_duplighost_FlailingAnims))
    Call(SetAnimation, LVarA, 1, 0x4E000A)
    Wait(15)
    Call(UseBattleCamPreset, 2)
    Call(SetActorJumpGravity, LVarA, Float(0.5))
    Call(GetActorPos, LVarA, LVarB, LVarC, LVarD)
    Add(LVarB, 30)
    Set(LVarC, 0)
    Call(SetGoalPos, LVarA, LVarB, LVarC, LVarD)
    Call(JumpToGoal, LVarA, 15, 0, 1, 0)
    Add(LVarB, 20)
    Call(SetGoalPos, LVarA, LVarB, LVarC, LVarD)
    Call(JumpToGoal, LVarA, 10, 0, 1, 0)
    Add(LVarB, 10)
    Call(SetGoalPos, LVarA, LVarB, LVarC, LVarD)
    Call(JumpToGoal, LVarA, 5, 0, 1, 0)
    Wait(20)
    Call(AddActorDecoration, LVarA, 1, 0, 2)
    Call(SetActorYaw, LVarA, 180)
    Call(SetIdleAnimations, LVarA, 1, Ref(b_area_pra3_duplighost_RunAnims))
    Call(SetAnimation, LVarA, 1, 0x4E0004)
    Call(SetActorSpeed, LVarA, Float(8.0))
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVarB, LVarC, LVarD)
    Call(SetGoalPos, LVarA, LVarB, 0, LVarD)
    Call(RunToGoal, LVarA, 0, 0)
    Call(SetAnimation, LVarA, 1, 0x4E0002)
    Call(SetActorYaw, LVarA, 0)
    Call(RemoveActorDecoration, LVarA, 1, 0)
    Call(SetIdleAnimations, LVarA, 1, Ref(TTYD64_imp_21_Duplighost_IdleAnimations_80219F10_21))
    Call(ForceHomePos, LVarA, LVarB, 0, LVarD)
    Call(HPBarToHome, LVarA)
    Call(SetActorPos, ACTOR_SELF, 0, -1000, 0)
    Call(ForceHomePos, ACTOR_SELF, 0, -1000, 0)
    Call(HPBarToHome, ACTOR_SELF)
    Call(RemoveActor, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_21_RMagikoopa_Script_RMagikoopa_WandStrike_21 = {
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
EvtScript TTYD64_imp_21_GRYMagikoopa_Script_GRYMagikoopa_WandStrike_21 = {
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
EvtScript TTYD64_imp_21_RMagikoopa_Script_RMagikoopa_ShapeSpell_21 = {
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
            Call(b_area_pra3_red_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
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
    Call(b_area_pra3_red_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
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
EvtScript TTYD64_imp_21_GRYMagikoopa_Script_GRYMagikoopa_ShapeSpell_21 = {
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
            Call(b_area_pra3_gray_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
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
    Call(b_area_pra3_gray_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
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
EvtScript TTYD64_imp_21_Duplighost_Script_HandleEvent_802207E0_21 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Call(GetLastElement, LVar1)
            IfFlag(LVar1, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xC000E)
                ExecWait(TTYD64_imp_21_Duplighost_Script_8021ACB4_21)
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xC000E)
                ExecWait(Ref(EVS_Enemy_Hit))
            EndIf
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000F)
            SetConst(LVar2, 0xC0010)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000F)
            SetConst(LVar2, 0xC0010)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC0010)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
            ExecWait(TTYD64_imp_21_Duplighost_Script_8021B178_21)
            Return
        CaseEq(38)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000D)
            Set(LVar2, 22)
            ExecWait(TTYD64_imp_21_Duplighost_Script_8021B804_21)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC0001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC0003)
            SetConst(LVar2, 0xC000E)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC0003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                IfFlag(LVar0, 0x80000)
                    Call(SetActorDispOffset, ACTOR_SELF, 0, 1, 0)
                Else
                    Call(SetActorDispOffset, ACTOR_SELF, 0, 3, 0)
                EndIf
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000E)
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
EvtScript TTYD64_imp_21_Duplighost_Script_HandleEvent_802253DC_21 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Call(GetLastElement, LVar1)
            IfFlag(LVar1, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x10000A)
                ExecWait(TTYD64_imp_21_Duplighost_Script_8021ACB4_21)
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x10000A)
                ExecWait(Ref(EVS_Enemy_Hit))
            EndIf
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x10000C)
            SetConst(LVar2, 0x10000D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x10000C)
            SetConst(LVar2, 0x10000D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x10000D)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x10000A)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x10000A)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x10000B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x10000A)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x10000A)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(SetAnimation, ACTOR_SELF, 1, 0x100003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
        CaseEq(38)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x10000A)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x10000B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x100001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x10000A)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x10000B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x100001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x100003)
            SetConst(LVar2, 0x10000A)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x100003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x10000A)
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
EvtScript TTYD64_imp_21_Duplighost_Script_LungeAttack_21 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4E0007)
    Wait(20)
    Call(SetActorSounds, ACTOR_SELF, 2, 715, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(UseBattleCamPreset, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4E0008)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -100, 0, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
            Call(JumpToGoal, ACTOR_SELF, 17, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(10)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorPos, ACTOR_SELF, LVar0, 0, LVar2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4E0002)
            Call(ResetActorSounds, ACTOR_SELF, 2)
            Wait(15)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(b_area_pra3_duplighost_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x4E0008)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Call(AddGoalPos, ACTOR_SELF, Float(4.0), Float(-6.0), 0)
    Else
        Call(AddGoalPos, ACTOR_SELF, 10, -15, 0)
    EndIf
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2998046875))
    Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 4, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(ResetActorSounds, ACTOR_SELF, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4E0009)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Wait(10)
            Call(YieldTurn)
            ExecWait(b_area_pra3_duplighost_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_21_Duplighost_Script_HandleEvent_8022176C_21 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Call(GetLastElement, LVar1)
            IfFlag(LVar1, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xD0015)
                ExecWait(TTYD64_imp_21_Duplighost_Script_8021ACB4_21)
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xD0015)
                ExecWait(Ref(EVS_Enemy_Hit))
            EndIf
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0018)
            SetConst(LVar2, 0xD0019)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0018)
            SetConst(LVar2, 0xD0019)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0019)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(UseBattleCamPreset, 2)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(TTYD64_imp_21_Duplighost_Script_8021B178_21)
            Return
        CaseEq(38)
            Call(UseBattleCamPreset, 2)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            Set(LVar2, 14)
            ExecWait(TTYD64_imp_21_Duplighost_Script_8021B804_21)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0003)
            SetConst(LVar2, 0xD0015)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
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
EvtScript TTYD64_imp_21_Duplighost_Script_HandleEvent_8021BD20_21 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Call(GetLastElement, LVar1)
            IfFlag(LVar1, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x9000A)
                ExecWait(TTYD64_imp_21_Duplighost_Script_8021ACB4_21)
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x9000A)
                ExecWait(Ref(EVS_Enemy_Hit))
            EndIf
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000B)
            SetConst(LVar2, 0x9000C)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000B)
            SetConst(LVar2, 0x9000C)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000C)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(TTYD64_imp_21_Duplighost_Script_8021B178_21)
            Return
        CaseEq(38)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            Set(LVar2, 12)
            ExecWait(TTYD64_imp_21_Duplighost_Script_8021B804_21)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x90001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x90001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x90003)
            SetConst(LVar2, 0x9000A)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x90003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
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
EvtScript TTYD64_imp_21_Duplighost_Script_HandleEvent_80223A14_21 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Call(GetLastElement, LVar1)
            IfFlag(LVar1, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xF000D)
                ExecWait(TTYD64_imp_21_Duplighost_Script_8021ACB4_21)
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0xF000D)
                ExecWait(Ref(EVS_Enemy_Hit))
            EndIf
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000E)
            SetConst(LVar2, 0xF000F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000E)
            SetConst(LVar2, 0xF000F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000F)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(TTYD64_imp_21_Duplighost_Script_8021B178_21)
            Return
        CaseEq(38)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            Set(LVar2, 20)
            ExecWait(TTYD64_imp_21_Duplighost_Script_8021B804_21)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF0001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            ExecWait(b_area_pra3_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF0001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF0003)
            SetConst(LVar2, 0xF000D)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF0003)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
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
EvtScript TTYD64_imp_21_Duplighost_Script_8021ACB4_21 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, LVar0, LVar1)
    Wait(30)
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    Call(UseIdleAnimation, LVarA, 0)
    Call(HideHealthBar, LVarA)
    Call(CopyStatusEffects, ACTOR_SELF, LVarA)
    Call(PlaySoundAtActor, ACTOR_SELF, 717)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 3)
        Add(LVar2, 5)
        Loop(3)
            Call(PlayEffect_impl, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(3)
        EndLoop
    EndThread
    Wait(5)
    Call(GetActorHP, ACTOR_SELF, LVarB)
    Call(SetEnemyHP, LVarA, LVarB)
    Call(CopyBuffs, ACTOR_SELF, LVarA)
    Call(GetActorPos, ACTOR_SELF, LVarB, LVarC, LVarD)
    Call(SetActorPos, LVarA, LVarB, LVarC, LVarD)
    Call(SetPartFlagBits, LVarA, 1, 0x800000, 1)
    Call(SetPartFlagBits, LVarA, 1, 0x20001, 0)
    Call(SetActorFlagBits, LVarA, 0x400004, 0)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
    Call(SetActorVar, LVarA, 8, 2)
    Call(SetPartFlagBits, ACTOR_SELF, LVar0, 1, 1)
    Call(SetIdleAnimations, LVarA, 1, Ref(b_area_pra3_duplighost_FlailingAnims))
    Call(SetAnimation, LVarA, 1, 0x4E000A)
    Wait(30)
    Call(UseBattleCamPreset, 2)
    Call(GetActorPos, LVarA, LVarB, LVarC, LVarD)
    IfGt(LVarC, 0)
        Set(LVarC, 0)
        Call(SetActorJumpGravity, LVarA, Float(0.5))
        Call(SetActorSounds, LVarA, 2, 769, 0)
        Call(SetGoalPos, LVarA, LVarB, LVarC, LVarD)
        Call(JumpToGoal, LVarA, 15, 0, 1, 0)
        Call(ResetActorSounds, LVarA, 2)
        Call(SetGoalPos, LVarA, LVarB, LVarC, LVarD)
        Call(JumpToGoal, LVarA, 10, 0, 1, 0)
        Call(SetGoalPos, LVarA, LVarB, LVarC, LVarD)
        Call(JumpToGoal, LVarA, 5, 0, 1, 0)
    EndIf
    Call(ForceHomePos, LVarA, LVarB, LVarC, LVarD)
    Call(HPBarToHome, LVarA)
    Call(SetIdleAnimations, LVarA, 1, Ref(TTYD64_imp_21_Duplighost_IdleAnimations_80219F10_21))
    Call(SetAnimation, LVarA, 1, 0x4E0002)
    Call(SetActorPos, ACTOR_SELF, 0, -1000, 0)
    Call(ForceHomePos, ACTOR_SELF, 0, -1000, 0)
    Call(HPBarToHome, ACTOR_SELF)
    Call(RemoveActor, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_21_Swoopula_Script_8021BC30_1C = {
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
            ExecWait(TTYD64_imp_21_Swoopula_Script_8021BA70_1C)
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
EvtScript TTYD64_imp_21_Duplighost_Script_8021B804_21 = {
    Call(HideHealthBar, ACTOR_SELF)
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Set(LVarC, LVar2)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, LVarA, LVarB)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 15)
    Add(LVar1, 10)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.099609375))
    Call(SetAnimation, ACTOR_SELF, LVarA, LVarB)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 0, 0)
    Set(LVar0, LVarA)
    Set(LVar1, LVarB)
    ExecWait(Ref(EVS_Enemy_ShockHit))
    Call(UseBattleCamPreset, 2)
    Thread
        Call(SetActorRotationOffset, ACTOR_SELF, 0, LVarC, 0)
        Set(LVar0, 0)
        Loop(15)
            Add(LVar0, -48)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 60)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Add(LVar0, 20)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Add(LVar0, 10)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_21_Swoopula_Script_8021C0B4_1C = {
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
    Call(b_area_pra3_swoopula_SetAbsoluteStatusOffsets, -10, 20, 10, 20)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_21_Swoopula_IdleAnimations_8021B9B0_1C))
    Call(SetActorFlagBits, ACTOR_SELF, 512, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_21_Duplighost_Script_8021D370_21 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Wait(10)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetBattleFlagBits, 4, 1)
    Call(b_area_pra3_goombario_clone_OpenTattleWindow, LVar5)
    Wait(12)
    Call(EnableBattleStatusBar, 0)
    Call(SetCamEnabled, 2, 1)
    Call(SetCamNoDraw, 2, 0)
    Call(SetCamPerspective, 2, 6, 25, 16, 1024)
    Call(SetCamViewport, 2, 37, 95, 138, 99)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 8)
    Set(LVar1, 0)
    Call(b_area_pra3_goombario_clone_CalculateTattleCamBoomLength)
    Wait(1)
    Call(SetCamLookTarget, 2, LVar0, LVar1, LVar2)
    Call(SetInterpCamParams, 2, 0, LVar3, 100, 4)
    Wait(2)
    Call(PlaySoundAtActor, ACTOR_SELF, 642)
    Call(SetCamNoDraw, 2, 1)
    Wait(10)
    Call(ActorSpeak, 0x1C0092, ACTOR_SELF, 1, 0x9000F, 0x90001)
    Call(b_area_pra3_goombario_clone_CloseTattleWindow, LVar5)
    Wait(12)
    Call(SetCamEnabled, 2, 0)
    Wait(32)
    Call(EnableBattleStatusBar, 1)
    Call(UseBattleCamPreset, 2)
    Call(SetBattleFlagBits, 4, 0)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_21_Swoopula_Script_8021BA70_1C = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x340102)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 0, -24, 0)
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 11)
            Call(SetActorFlagBits, ACTOR_SELF, 2048, 1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_21_Swoopula_IdleAnimations_8021B964_1C))
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

// clang-format off
EvtScript TTYD64_imp_21_Duplighost_Script_TakeTurn_80226CC0_21 = {
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 600)
                Call(GetBattleVar, 0, LVar0)
                IfNotFlag(LVar0, 4)
                    Call(GetBattleVar, 0, LVar0)
                    BitwiseOrConst(LVar0, 4)
                    Call(SetBattleVar, 0, LVar0)
                    ExecWait(TTYD64_imp_21_Duplighost_Script_CopyPartner_21)
                Else
                    Call(GetBattleVar, 3, LVar0)
                    Call(b_area_pra3_duplighost_GetPartnerAndLevel, LVar1, LVar2)
                    IfEq(LVar0, LVar1)
                        ExecWait(TTYD64_imp_21_Duplighost_Script_CopyPartner_21)
                    Else
                        ExecWait(TTYD64_imp_21_Duplighost_Script_LungeAttack_21)
                    EndIf
                EndIf
            Else
                ExecWait(TTYD64_imp_21_Duplighost_Script_LungeAttack_21)
            EndIf
        CaseEq(1)
        CaseEq(2)
            ExecWait(TTYD64_imp_21_Duplighost_Script_LungeAttack_21)
        CaseEq(3)
    EndSwitch
    Return
    End
};
// clang-format on

Battle TTYD64_pra3_FormationTable[] = {
    { .name = "\320\265\320\265\301\345\353\353x\022,\320\261\320\261",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pra3_Formation_00,
      .stage = &b_area_pra3_pra_01,
      .onBattleStart = NULL },
    { .name = "\320\261\320\261",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_pra3_Formation_01,
      .stage = &b_area_pra3_pra_01,
      .onBattleStart = NULL },
    { .name = "\320\261\320\261x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pra3_Formation_02,
      .stage = &b_area_pra3_pra_01,
      .onBattleStart = NULL },
    { .name = "\320\261\320\261x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pra3_Formation_03,
      .stage = &b_area_pra3_pra_01,
      .onBattleStart = NULL },
    { .name = "\320\261\320\261x4",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pra3_Formation_04,
      .stage = &b_area_pra3_pra_01,
      .onBattleStart = NULL },
    { .name = "\320\261\320\261x\022,\320\265\320\265\301\345\353\353",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pra3_Formation_05,
      .stage = &b_area_pra3_pra_01,
      .onBattleStart = NULL },
    { .name = "\320\261\320\261,\320\265\320\265\301\345\353\353,\320\261\320\261",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pra3_Formation_06,
      .stage = &b_area_pra3_pra_01,
      .onBattleStart = NULL },
    { .name = "\320\261\320\261,\354\303\311\253\341\303\257",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pra3_Formation_07,
      .stage = &b_area_pra3_pra_01,
      .onBattleStart = NULL },
    { .name = "\320\261\320\261x\022,\354\303\311\253\341\303\257",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pra3_Formation_08,
      .stage = &b_area_pra3_pra_01,
      .onBattleStart = NULL },
    { .name = "\320\261\320\261,\333\357\244\310\254\334\363,\320\261\320\261",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pra3_Formation_09,
      .stage = &b_area_pra3_pra_01,
      .onBattleStart = NULL },
    { .name = "\320\261\320\261x\022,\260\354\244\253\341\303\257,\354\303\311\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pra3_Formation_0A,
      .stage = &b_area_pra3_pra_01,
      .onBattleStart = NULL },
    { .name = "\333\357\244\310\254\334\363x\022,\320\261\320\261",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pra3_Formation_0B,
      .stage = &b_area_pra3_pra_01,
      .onBattleStart = NULL },
    {},
};

s32 TTYD64_imp_21_GRYMagikoopa_StatusTable_8022EDF8_21[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  75, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_imp_21_Duplighost_StatusTable_802215F4_21[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_21_Duplighost_StatusTable_8021BBCC_21[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_21_Duplighost_StatusTable_8021D7AC_21[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_21_Duplighost_StatusTable_80220668_21[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_21_Duplighost_StatusTable_80225264_21[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_21_Duplighost_StatusTable_802229CC_21[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_21_Duplighost_StatusTable_8021F408_21[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_21_Duplighost_StatusTable_802238C0_21[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_21_RMagikoopa_StatusTable_8022C138_21[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  75, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

// clang-format off
EvtScript TTYD64_imp_21_RMagikoopa_Script_Init_8022E558_21 = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra3_red_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_21_RMagikoopa_Script_TakeTurn_8022E6A0_21))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_pra3_red_magikoopa_EVS_HandleEvent))
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
EvtScript TTYD64_imp_21_GRYMagikoopa_Script_Init_80231218_21 = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra3_gray_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_21_GRYMagikoopa_Script_TakeTurn_80231360_21))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_pra3_gray_magikoopa_EVS_HandleEvent))
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
EvtScript TTYD64_imp_21_Duplighost_Script_Init_8021D8A4_21 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_21_Duplighost_Script_TakeTurn_8021E3F4_21))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra3_kooper_clone_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_21_Duplighost_Script_HandleEvent_8021DA98_21))
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_21_Duplighost_Script_Init_8021A078_21 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_21_Duplighost_Script_TakeTurn_80226CC0_21))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra3_duplighost_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_pra3_duplighost_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_pra3_duplighost_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pra3_Formation_0A[] = {
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_21_GRYMagikoopa_21_GRYMagikoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_imp_21_RMagikoopa_21_RMagikoopa,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pra3_Formation_04[] = {
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
};

// clang-format off
EvtScript TTYD64_imp_21_Swoopula_Script_Init_8021B9FC_1C = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_21_Swoopula_Script_TakeTurn_8021E7B4_1C))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra3_swoopula_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_21_Swoopula_Script_HandleEvent_8021C414_1C))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_21_Duplighost_Script_TakeTurn_8021D684_21 = {
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 10)
        ExecWait(TTYD64_imp_21_Duplighost_Script_8021D370_21)
    Else
        ExecWait(TTYD64_imp_21_Duplighost_Script_8021C8E4_21)
    EndIf
    Return
    End
};
// clang-format on

FormationRow TTYD64_pra3_Formation_0B[] = {
    { .actor = &TTYD64_imp_21_WhiteClubba_21_WhiteClubba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_21_WhiteClubba_21_WhiteClubba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
};

FormationRow TTYD64_pra3_Formation_00[] = {
    { .actor = &TTYD64_imp_21_Swoopula_21_Swoopula,
      .home = { .vec = &TTYD64_pra3_Vector3D_802324A0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
    { .actor = &TTYD64_imp_21_Swoopula_21_Swoopula,
      .home = { .vec = &TTYD64_pra3_Vector3D_802324AC },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
};

FormationRow TTYD64_pra3_Formation_05[] = {
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_21_Swoopula_21_Swoopula,
      .home = { .vec = &TTYD64_pra3_Vector3D_802324B8 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
};

FormationRow TTYD64_pra3_Formation_03[] = {
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
};

FormationRow TTYD64_pra3_Formation_08[] = {
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_21_RMagikoopa_21_RMagikoopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pra3_Formation_09[] = {
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_21_WhiteClubba_21_WhiteClubba,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
};

FormationRow TTYD64_pra3_Formation_06[] = {
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_21_Swoopula_21_Swoopula,
      .home = { .vec = &TTYD64_pra3_Vector3D_802324AC },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SWOOPULA },
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
};

s32 TTYD64_imp_21_Duplighost_IdleAnimations_8021D748_21[] = {
    1, 0xA0019, 7, 0xA0003, 6, 0xA0003, 9, 0xA0019, 8, 0xA0003, 11, 0xA0019, 5, 0xA0003, 4, 0xA0019, 3, 0xA0019, 0,
};

s32 TTYD64_imp_21_Duplighost_IdleAnimations_8022159C_21[] = {
    1, 0xD0001, 7, 0xD0000, 6, 0xD0000, 9, 0xD0001, 8, 0xD0000, 11, 0xD0001, 5, 0xD0000, 4, 0xD001A, 3, 0xD001A, 0,
};

s32 TTYD64_imp_21_Duplighost_IdleAnimations_8021BB74_21[] = {
    1, 0x90001, 7, 0x90000, 6, 0x90000, 9, 0x90001, 8, 0x90000, 11, 0x90001, 5, 0x90000, 4, 0x90014, 3, 0x90014, 0,
};

s32 TTYD64_imp_21_Duplighost_IdleAnimations_80219F10_21[] = {
    1,  0x4E0002, 7, 0x4E0000, 6, 0x4E000D, 9, 0x4E0002, 8, 0x4E0000,
    11, 0x4E0002, 5, 0x4E0000, 4, 0x4E000E, 3, 0x4E000E, 0,
};

s32 TTYD64_imp_21_Swoopula_IdleAnimations_8021B964_1C[] = {
    1,  0x34010C, 7, 0x34010B, 6, 0x34010F, 9, 0x34010C, 8, 0x34010B,
    11, 0x34010C, 5, 0x34010B, 4, 0x340110, 3, 0x340110, 0,
};

s32 TTYD64_imp_21_WhiteClubba_IdleAnimations_8022B130_21[] = {
    1,  0x3A0101, 7, 0x3A0100, 6, 0x3A0103, 9, 0x3A0101, 8, 0x3A0100,
    11, 0x3A0101, 5, 0x3A0100, 4, 0x3A0105, 3, 0x3A0105, 0,
};

// clang-format off
EvtScript TTYD64_imp_21_Duplighost_Script_Init_80222AE8_21 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_21_Duplighost_Script_TakeTurn_80222FD0_21))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra3_watt_clone_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_pra3_watt_clone_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_21_Duplighost_IdleAnimations_80225200_21[] = {
    1,  0x100001, 7, 0x100000, 6, 0x100000, 9, 0x100001, 8, 0x100000,
    11, 0x100001, 5, 0x100000, 4, 0x100008, 3, 0x100001, 0,
};

// clang-format off
EvtScript TTYD64_imp_21_WhiteClubba_Script_Init_8022B290_21 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_21_WhiteClubba_Script_TakeTurn_8022B7FC_21))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra3_white_clubba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_pra3_white_clubba_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_21_Duplighost_IdleAnimations_80223868_21[] = {
    1, 0xF0001, 7, 0xF0000, 6, 0xF0000, 9, 0xF0001, 8, 0xF0000, 11, 0xF0001, 5, 0xF0000, 4, 0xF0010, 3, 0xF0010, 0,
};

// clang-format off
EvtScript TTYD64_imp_21_Duplighost_Script_Init_8021BCC4_21 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_21_Duplighost_Script_TakeTurn_8021D684_21))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra3_goombario_clone_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_21_Duplighost_Script_HandleEvent_8021BD20_21))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_21_Duplighost_IdleAnimations_8021D6FC_21[] = {
    1, 0xA0004, 7, 0xA0000, 6, 0xA0000, 9, 0xA0004, 8, 0xA0000, 11, 0xA0004, 5, 0xA0000, 4, 0xA001C, 3, 0xA001C, 0,
};

s32 TTYD64_imp_21_Duplighost_IdleAnimations_80220610_21[] = {
    1, 0xC0001, 7, 0xC0000, 6, 0xC0000, 9, 0xC0001, 8, 0xC0000, 11, 0xC0001, 5, 0xC0000, 4, 0xC0001, 3, 0xC0001, 0,
};

s32 TTYD64_imp_21_Duplighost_IdleAnimations_8021F3B0_21[] = {
    1, 0xB0004, 7, 0xB0000, 6, 0xB0000, 9, 0xB0004, 8, 0xB0000, 11, 0xB0004, 5, 0xB0000, 4, 0xB001E, 3, 0xB001E, 0,
};

s32 TTYD64_imp_21_Duplighost_IdleAnimations_8022296C_21[] = {
    1, 0xE0001, 7, 0xE0000, 6, 0xE0000, 9, 0xE0001, 8, 0xE0000, 11, 0xE0001, 5, 0xE0000, 4, 0xE000F, 3, 0xE000F, 0,
};

// clang-format off
EvtScript TTYD64_imp_21_Duplighost_Script_Init_80225380_21 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(b_area_pra3_lakilester_clone_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra3_lakilester_clone_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_21_Duplighost_Script_HandleEvent_802253DC_21))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_21_Duplighost_Script_Init_80221710_21 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_21_Duplighost_Script_TakeTurn_80221CFC_21))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra3_bow_clone_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_21_Duplighost_Script_HandleEvent_8022176C_21))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_21_GRYMagikoopa_IdleAnimations_8022F030_21[] = {
    1,  0x560501, 7, 0x560500, 6, 0x560508, 9, 0x560501, 8, 0x560500,
    11, 0x560501, 5, 0x560500, 4, 0x560507, 3, 0x560507, 0,
};

// clang-format off
EvtScript TTYD64_imp_21_Duplighost_Script_Init_80220784_21 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(b_area_pra3_parakarry_clone_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra3_parakarry_clone_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_21_Duplighost_Script_HandleEvent_802207E0_21))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_21_Swoopula_IdleAnimations_8021B9B0_1C[] = {
    1,  0x340102, 7, 0x340101, 6, 0x340113, 9, 0x340102, 8, 0x340101,
    11, 0x340102, 5, 0x340101, 4, 0x340114, 3, 0x340114, 0,
};

s32 TTYD64_imp_21_RMagikoopa_IdleAnimations_8022C370_21[] = {
    1,  0x560101, 7, 0x560100, 6, 0x560108, 9, 0x560101, 8, 0x560100,
    11, 0x560101, 5, 0x560100, 4, 0x560107, 3, 0x560107, 0,
};

// clang-format off
EvtScript TTYD64_imp_21_Duplighost_Script_Init_802239B8_21 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_21_Duplighost_Script_TakeTurn_80223F84_21))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_pra3_sushie_clone_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_21_Duplighost_Script_HandleEvent_80223A14_21))
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_802216A0_21[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_21_Duplighost_IdleAnimations_8022159C_21,
        .defenseTable = b_area_pra3_bow_clone_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x80800001,
        .index = 2,
        .posOffset = { 0, 50, 0 },
        .targetOffset = { 0, -26 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_pra3_bow_clone_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_80222A78_21[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -1, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_21_Duplighost_IdleAnimations_8022296C_21,
        .defenseTable = b_area_pra3_watt_clone_DefenseTable,
        .eventFlags = 0x80,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x80800001,
        .index = 2,
        .posOffset = { 0, 50, 0 },
        .targetOffset = { -1, -30 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_pra3_watt_clone_DefenseTable,
        .eventFlags = 0x80,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_80225310_21[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -3, 33 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_21_Duplighost_IdleAnimations_80225200_21,
        .defenseTable = b_area_pra3_lakilester_clone_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -2, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_pra3_lakilester_clone_SpinyAnims,
        .defenseTable = b_area_pra3_lakilester_clone_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_80220714_21[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -3, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_21_Duplighost_IdleAnimations_80220610_21,
        .defenseTable = b_area_pra3_parakarry_clone_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -16 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x80800001,
        .index = 2,
        .posOffset = { 0, 50, 0 },
        .targetOffset = { -3, -18 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_pra3_parakarry_clone_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -16 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_pra3_Formation_02[] = {
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
};

FormationRow TTYD64_pra3_Formation_07[] = {
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_21_RMagikoopa_21_RMagikoopa,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

ActorBlueprint TTYD64_imp_21_Duplighost_GhostParakarry_21 = {
    .flags = 0x200,
    .maxHP = 15,
    .type = 0x3F,
    .level = 23,
    .partCount = 2,
    .partsData = TTYD64_imp_21_Duplighost_PartsTable_80220714_21,
    .initScript = &TTYD64_imp_21_Duplighost_Script_Init_80220784_21,
    .statusTable = TTYD64_imp_21_Duplighost_StatusTable_80220668_21,
    .escapeChance = 50,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 2,
    .size = { 38, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_21_Duplighost_GhostWatt_21 = {
    .flags = 0x200,
    .maxHP = 15,
    .type = 0x41,
    .level = 23,
    .partCount = 2,
    .partsData = TTYD64_imp_21_Duplighost_PartsTable_80222A78_21,
    .initScript = &TTYD64_imp_21_Duplighost_Script_Init_80222AE8_21,
    .statusTable = TTYD64_imp_21_Duplighost_StatusTable_802229CC_21,
    .escapeChance = 50,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 2,
    .size = { 34, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_21_Duplighost_GhostBow_21 = {
    .flags = 0x200,
    .maxHP = 15,
    .type = 0x40,
    .level = 23,
    .partCount = 2,
    .partsData = TTYD64_imp_21_Duplighost_PartsTable_802216A0_21,
    .initScript = &TTYD64_imp_21_Duplighost_Script_Init_80221710_21,
    .statusTable = TTYD64_imp_21_Duplighost_StatusTable_802215F4_21,
    .escapeChance = 50,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 2,
    .size = { 36, 29 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_21_Duplighost_GhostSushie_21 = {
    .flags = 0x0,
    .maxHP = 15,
    .type = 0x42,
    .level = 23,
    .partCount = 1,
    .partsData = TTYD64_imp_21_Duplighost_PartsTable_8022396C_21,
    .initScript = &TTYD64_imp_21_Duplighost_Script_Init_802239B8_21,
    .statusTable = TTYD64_imp_21_Duplighost_StatusTable_802238C0_21,
    .escapeChance = 50,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 2,
    .size = { 37, 26 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_21_GRYMagikoopa_21_GRYMagikoopa = {
    .flags = 0x0,
    .maxHP = 11,
    .type = 0x57,
    .level = 21,
    .partCount = 1,
    .partsData = TTYD64_imp_21_GRYMagikoopa_PartsTable_8022EF50_21,
    .initScript = &TTYD64_imp_21_GRYMagikoopa_Script_Init_80231218_21,
    .statusTable = TTYD64_imp_21_GRYMagikoopa_StatusTable_8022EDF8_21,
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

ActorBlueprint TTYD64_imp_21_Duplighost_GhostBombette_21 = {
    .flags = 0x0,
    .maxHP = 15,
    .type = 0x3E,
    .level = 23,
    .partCount = 1,
    .partsData = TTYD64_imp_21_Duplighost_PartsTable_8021F4B4_21,
    .initScript = &b_area_pra3_bombette_clone_EVS_Init,
    .statusTable = TTYD64_imp_21_Duplighost_StatusTable_8021F408_21,
    .escapeChance = 50,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 2,
    .size = { 30, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_21_Duplighost_21_Duplighost = {
    .flags = 0x0,
    .maxHP = 15,
    .type = 0x3B,
    .level = 23,
    .partCount = 1,
    .partsData = TTYD64_imp_21_Duplighost_PartsTable_8021A02C_21,
    .initScript = &TTYD64_imp_21_Duplighost_Script_Init_8021A078_21,
    .statusTable = b_area_pra3_duplighost_StatusTable,
    .escapeChance = 50,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 2,
    .size = { 36, 36 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_21_Duplighost_GhostLakilester_21 = {
    .flags = 0x200,
    .maxHP = 15,
    .type = 0x43,
    .level = 23,
    .partCount = 2,
    .partsData = TTYD64_imp_21_Duplighost_PartsTable_80225310_21,
    .initScript = &TTYD64_imp_21_Duplighost_Script_Init_80225380_21,
    .statusTable = TTYD64_imp_21_Duplighost_StatusTable_80225264_21,
    .escapeChance = 50,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 2,
    .size = { 44, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_21_Swoopula_21_Swoopula = {
    .flags = 0x800,
    .maxHP = 8,
    .type = 0x3A,
    .level = 22,
    .partCount = 1,
    .partsData = TTYD64_imp_21_Swoopula_PartsTable_8021B918_1C,
    .initScript = &TTYD64_imp_21_Swoopula_Script_Init_8021B9FC_1C,
    .statusTable = b_area_pra3_swoopula_StatusTable,
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

ActorBlueprint TTYD64_imp_21_WhiteClubba_21_WhiteClubba = {
    .flags = 0x0,
    .maxHP = 12,
    .type = 0x38,
    .level = 23,
    .partCount = 1,
    .partsData = TTYD64_imp_21_WhiteClubba_PartsTable_8022B244_21,
    .initScript = &TTYD64_imp_21_WhiteClubba_Script_Init_8022B290_21,
    .statusTable = b_area_pra3_white_clubba_StatusTable,
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

ActorBlueprint TTYD64_imp_21_Duplighost_GhostKooper_21 = {
    .flags = 0x0,
    .maxHP = 15,
    .type = 0x3D,
    .level = 23,
    .partCount = 1,
    .partsData = TTYD64_imp_21_Duplighost_PartsTable_8021D858_21,
    .initScript = &TTYD64_imp_21_Duplighost_Script_Init_8021D8A4_21,
    .statusTable = TTYD64_imp_21_Duplighost_StatusTable_8021D7AC_21,
    .escapeChance = 50,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 2,
    .size = { 32, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_21_Duplighost_GhostGoombario_21 = {
    .flags = 0x0,
    .maxHP = 15,
    .type = 0x3C,
    .level = 23,
    .partCount = 1,
    .partsData = TTYD64_imp_21_Duplighost_PartsTable_8021BC78_21,
    .initScript = &TTYD64_imp_21_Duplighost_Script_Init_8021BCC4_21,
    .statusTable = TTYD64_imp_21_Duplighost_StatusTable_8021BBCC_21,
    .escapeChance = 50,
    .airLiftChance = 80,
    .hurricaneChance = 70,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 2,
    .size = { 29, 26 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_21_RMagikoopa_21_RMagikoopa = {
    .flags = 0x0,
    .maxHP = 11,
    .type = 0x51,
    .level = 21,
    .partCount = 1,
    .partsData = TTYD64_imp_21_RMagikoopa_PartsTable_8022C290_21,
    .initScript = &TTYD64_imp_21_RMagikoopa_Script_Init_8022E558_21,
    .statusTable = TTYD64_imp_21_RMagikoopa_StatusTable_8022C138_21,
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

ActorPartBlueprint TTYD64_imp_21_GRYMagikoopa_PartsTable_8022EF50_21[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_21_GRYMagikoopa_IdleAnimations_8022F030_21,
        .defenseTable = b_area_pra3_gray_magikoopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_8021A02C_21[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -5, 25 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_21_Duplighost_IdleAnimations_80219F10_21,
        .defenseTable = b_area_pra3_duplighost_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -2, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_8022396C_21[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_21_Duplighost_IdleAnimations_80223868_21,
        .defenseTable = b_area_pra3_sushie_clone_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_8021D858_21[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_21_Duplighost_IdleAnimations_8021D6FC_21,
        .defenseTable = b_area_pra3_kooper_clone_UprightDefenseTable,
        .eventFlags = 0x1000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -16 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_8021BC78_21[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_21_Duplighost_IdleAnimations_8021BB74_21,
        .defenseTable = b_area_pra3_goombario_clone_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -9 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_21_WhiteClubba_PartsTable_8022B244_21[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -12, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_21_WhiteClubba_IdleAnimations_8022B130_21,
        .defenseTable = b_area_pra3_white_clubba_DefenseTable,
        .eventFlags = 0x8,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 8, -3 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_21_RMagikoopa_PartsTable_8022C290_21[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_21_RMagikoopa_IdleAnimations_8022C370_21,
        .defenseTable = b_area_pra3_red_magikoopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_21_Swoopula_PartsTable_8021B918_1C[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 29 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_21_Swoopula_IdleAnimations_8021B964_1C,
        .defenseTable = b_area_pra3_swoopula_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 1, 15 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_21_Duplighost_PartsTable_8021F4B4_21[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 22 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_21_Duplighost_IdleAnimations_8021F3B0_21,
        .defenseTable = b_area_pra3_bombette_clone_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -2, -7 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_80222950_21[] = {
    { .actor = &TTYD64_imp_21_Duplighost_GhostBow_21,
      .home = { .vec = &b_area_pra3_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_80226484_21[] = {
    { .actor = &TTYD64_imp_21_Duplighost_GhostLakilester_21,
      .home = { .vec = &b_area_pra3_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pra3_Formation_01[] = {
    { .actor = &TTYD64_imp_21_Duplighost_21_Duplighost,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
};

FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_8022384C_21[] = {
    { .actor = &TTYD64_imp_21_Duplighost_GhostWatt_21,
      .home = { .vec = &b_area_pra3_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_80221580_21[] = {
    { .actor = &TTYD64_imp_21_Duplighost_GhostParakarry_21,
      .home = { .vec = &b_area_pra3_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_802205F4_21[] = {
    { .actor = &TTYD64_imp_21_Duplighost_GhostBombette_21,
      .home = { .vec = &b_area_pra3_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_8021D6E0_21[] = {
    { .actor = &TTYD64_imp_21_Duplighost_GhostGoombario_21,
      .home = { .vec = &b_area_pra3_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_8021F394_21[] = {
    { .actor = &TTYD64_imp_21_Duplighost_GhostKooper_21,
      .home = { .vec = &b_area_pra3_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_21_Duplighost_SpecialFormation_802251E4_21[] = {
    { .actor = &TTYD64_imp_21_Duplighost_GhostSushie_21,
      .home = { .vec = &b_area_pra3_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

Vec3i TTYD64_pra3_Vector3D_802324A0 = { 15, 133, -25 };

Vec3i TTYD64_pra3_Vector3D_802324AC = { 55, 133, -25 };

Vec3i TTYD64_pra3_Vector3D_802324B8 = { 95, 133, -25 };

void TTYD64_InstallBattles_pra3(void) {
    Mod_SetBattleList("TTYD64", 0x21, TTYD64_pra3_FormationTable);
}
