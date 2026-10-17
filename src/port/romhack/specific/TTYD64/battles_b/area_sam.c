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

API_CALLABLE(b_area_sam_bombette_clone_UnkActorPosFunc);
API_CALLABLE(b_area_sam_duplighost_GetPartnerAndLevel);
API_CALLABLE(b_area_sam_frost_piranha_UnkEffect6FFunc);
API_CALLABLE(b_area_sam_goombario_clone_ActorJumpToPos);
API_CALLABLE(b_area_sam_goombario_clone_CalculateTattleCamBoomLength);
API_CALLABLE(b_area_sam_goombario_clone_CloseTattleWindow);
API_CALLABLE(b_area_sam_goombario_clone_OpenTattleWindow);
API_CALLABLE(b_area_sam_goombario_clone_UnkFunc62);
API_CALLABLE(b_area_sam_gray_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_sam_gray_magikoopa_ShrinkActor);
API_CALLABLE(b_area_sam_kooper_clone_UnkActorPosFunc);
API_CALLABLE(b_area_sam_watt_clone_SetBackgroundAlpha);
API_CALLABLE(b_area_sam_watt_clone_UnkBackgroundFunc3);
API_CALLABLE(b_area_sam_watt_clone_WattFXSetActive);
API_CALLABLE(b_area_sam_watt_clone_WattFXSetBouncing);
API_CALLABLE(b_area_sam_watt_clone_WattFXSetEffect);
extern Vec3i b_area_sam_DuplighostSummonPos;
extern EvtScript b_area_sam_EVS_Duplighost_OnDeath;
extern s32 b_area_sam_bombette_clone_DefenseTable[];
extern EvtScript b_area_sam_bombette_clone_EVS_HandleEvent;
extern EvtScript b_area_sam_bombette_clone_EVS_Idle;
extern s32 b_area_sam_bow_clone_DefenseTable[];
extern EvtScript b_area_sam_bow_clone_EVS_Idle;
extern s32 b_area_sam_duplighost_DefenseTable[];
extern EvtScript b_area_sam_duplighost_EVS_HandleEvent;
extern EvtScript b_area_sam_duplighost_EVS_HandlePhase;
extern EvtScript b_area_sam_duplighost_EVS_Idle;
extern EvtScript b_area_sam_duplighost_EVS_ReturnHome;
extern s32 b_area_sam_duplighost_FlailingAnims[];
extern s32 b_area_sam_duplighost_RunAnims[];
extern s32 b_area_sam_duplighost_StatusTable[];
extern s32 b_area_sam_frost_piranha_DefenseTable[];
extern EvtScript b_area_sam_frost_piranha_EVS_HandleEvent;
extern EvtScript b_area_sam_frost_piranha_EVS_Idle;
extern EvtScript b_area_sam_frost_piranha_EVS_ReturnHome;
extern s32 b_area_sam_frost_piranha_StatusTable[];
extern s32 b_area_sam_goombario_clone_DefenseTable[];
extern EvtScript b_area_sam_goombario_clone_EVS_CalculateJumpTime;
extern EvtScript b_area_sam_goombario_clone_EVS_HeadbonkFollowthrough;
extern EvtScript b_area_sam_goombario_clone_EVS_Idle;
extern s32 b_area_sam_gray_magikoopa_DefenseTable[];
extern EvtScript b_area_sam_gray_magikoopa_EVS_Flee;
extern EvtScript b_area_sam_gray_magikoopa_EVS_HandleEvent;
extern EvtScript b_area_sam_gray_magikoopa_EVS_Idle;
extern s32 b_area_sam_gulpit_BigRockAnims[];
extern s32 b_area_sam_gulpit_DefenseTable[];
extern EvtScript b_area_sam_gulpit_EVS_HandleEvent;
extern EvtScript b_area_sam_gulpit_EVS_Idle;
extern EvtScript b_area_sam_gulpit_EVS_ReturnHome;
extern s32 b_area_sam_gulpit_SmallRockAnims[];
extern s32 b_area_sam_gulpit_StatusTable[];
extern ActorBlueprint b_area_sam_gulpit_rocks;
extern EvtScript b_area_sam_kooper_clone_EVS_Idle;
extern u8 b_area_sam_kooper_clone_FlipPosOffsets[];
extern s32 b_area_sam_kooper_clone_ToppledDefenseTable[];
extern s32 b_area_sam_kooper_clone_UprightDefenseTable[];
extern s32 b_area_sam_lakilester_clone_DefenseTable[];
extern EvtScript b_area_sam_lakilester_clone_EVS_Idle;
extern s32 b_area_sam_lakilester_clone_SpinyAnims[];
extern s32 b_area_sam_parakarry_clone_DefenseTable[];
extern EvtScript b_area_sam_parakarry_clone_EVS_Idle;
extern u8 b_area_sam_pos_rocks_1[];
extern u8 b_area_sam_pos_rocks_2[];
extern u8 b_area_sam_pos_rocks_3[];
extern u8 b_area_sam_pos_rocks_4[];
extern u8 b_area_sam_pos_rocks_5[];
extern u8 b_area_sam_pos_rocks_6[];
extern u8 b_area_sam_pos_rocks_7[];
extern u8 b_area_sam_pos_rocks_8[];
extern Stage b_area_sam_sam_01;
extern s32 b_area_sam_sushie_clone_DefenseTable[];
extern EvtScript b_area_sam_sushie_clone_EVS_Idle;
extern s32 b_area_sam_watt_clone_DefenseTable[];
extern EvtScript b_area_sam_watt_clone_EVS_HandleEvent;
extern EvtScript b_area_sam_watt_clone_EVS_Idle;
extern s32 b_area_sam_white_clubba_DefenseTable[];
extern EvtScript b_area_sam_white_clubba_EVS_HandleEvent;
extern EvtScript b_area_sam_white_clubba_EVS_Idle;
extern s32 b_area_sam_white_clubba_StatusTable[];
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80224F04_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_8021F374_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80222C7C_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80226924_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Goombario_Headbonk_1D;
extern EvtScript TTYD64_imp_1D_FrostPiranha_Script_8022B3AC_1D;
extern EvtScript TTYD64_imp_1D_WhiteClubba_Script_TakeTurn_8022A18C_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_8021EA18_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80223F50_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80220CA0_1D;
extern EvtScript TTYD64_imp_1D_Gulpit_Script_8022898C_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_CopyPartner_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_80221D54_1D;
extern EvtScript TTYD64_imp_1D_GRYMagikoopa_Script_TakeTurn_8022E890_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_8021C0F8_1D;
extern EvtScript TTYD64_imp_1D_GRYMagikoopa_Script_GRYMagikoopa_WandStrike_1D;
extern EvtScript TTYD64_imp_1D_GRYMagikoopa_Script_GRYMagikoopa_ShapeSpell_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_80221760_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_8022635C_1D;
extern EvtScript TTYD64_imp_1D_FrostPiranha_Script_8022BD44_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_LungeAttack_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_802226EC_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_8021CCA0_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_80224994_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_8021BC34_1D;
extern EvtScript TTYD64_imp_1D_Gulpit_Script_80228518_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_8021C784_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Goombario_Tattle_1D;
extern EvtScript TTYD64_imp_1D_Gulpit_Script_TakeTurn_802291B4_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80227C40_1D;
extern Battle TTYD64_sam_FormationTable[];
extern EvtScript TTYD64_imp_1D_Duplighost_Script_8021D698_1D;
extern EvtScript TTYD64_imp_1D_FrostPiranha_Script_TakeTurn_8022B2D4_1D;
extern FormationRow TTYD64_sam_Formation_0A[];
extern FormationRow TTYD64_sam_Formation_05[];
extern FormationRow TTYD64_sam_Formation_04[];
extern FormationRow TTYD64_sam_Formation_02[];
extern FormationRow TTYD64_sam_Formation_03[];
extern FormationRow TTYD64_sam_Formation_08[];
extern FormationRow TTYD64_sam_Formation_09[];
extern FormationRow TTYD64_sam_Formation_01[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_80224840_1D[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_8021E72C_1D[];
extern s32 TTYD64_imp_1D_GRYMagikoopa_StatusTable_8022C328_1D[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_80220388_1D[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_80222574_1D[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_8022394C_1D[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_8021CB4C_1D[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_802215E8_1D[];
extern s32 TTYD64_imp_1D_Duplighost_StatusTable_802261E4_1D[];
extern EvtScript TTYD64_imp_1D_GRYMagikoopa_Script_Init_8022E748_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_8021E824_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_8021AFF8_1D;
extern FormationRow TTYD64_sam_Formation_0D[];
extern FormationRow TTYD64_sam_Formation_0C[];
extern FormationRow TTYD64_sam_Formation_07[];
extern ActorPartBlueprint TTYD64_imp_1D_Gulpit_PartsTable_80227EEC_1D[];
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_8021E604_1D;
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_8021AE90_1D[];
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80220480_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80224938_1D;
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_8021E67C_1D[];
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80226300_1D;
extern s32 TTYD64_imp_1D_FrostPiranha_IdleAnimations_8022AAB0_1D[];
extern s32 TTYD64_imp_1D_GRYMagikoopa_IdleAnimations_8022C560_1D[];
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_8021CAF4_1D[];
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_80221590_1D[];
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_80226180_1D[];
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_80220330_1D[];
extern s32 TTYD64_imp_1D_WhiteClubba_IdleAnimations_80229AC0_1D[];
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_8021E6C8_1D[];
extern EvtScript TTYD64_imp_1D_Gulpit_Script_Init_80227F80_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_8021CC44_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80221704_1D;
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_802238EC_1D[];
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_8022251C_1D[];
extern s32 TTYD64_imp_1D_Gulpit_IdleAnimations_80227DD0_1D[];
extern EvtScript TTYD64_imp_1D_WhiteClubba_Script_Init_80229C20_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80222690_1D;
extern EvtScript TTYD64_imp_1D_FrostPiranha_Script_Init_8022AC10_1D;
extern EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80223A68_1D;
extern s32 TTYD64_imp_1D_Duplighost_IdleAnimations_802247E8_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_802239F8_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_80221694_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_80226290_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_80222620_1D[];
extern FormationRow TTYD64_sam_Formation_0B[];
extern FormationRow TTYD64_sam_Formation_00[];
extern FormationRow TTYD64_sam_Formation_06[];
extern ActorBlueprint TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostBow_1D;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostParakarry_1D;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostSushie_1D;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostBombette_1D;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostWatt_1D;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostLakilester_1D;
extern ActorBlueprint TTYD64_imp_1D_WhiteClubba_1D_WhiteClubba;
extern ActorBlueprint TTYD64_imp_1D_GRYMagikoopa_1D_GRYMagikoopa;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostKooper_1D;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_GhostGoombario_1D;
extern ActorBlueprint TTYD64_imp_1D_Duplighost_1D_Duplighost;
extern ActorBlueprint TTYD64_imp_1D_Gulpit_1D_Gulpit;
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_8021AFAC_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_8021E7D8_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_GRYMagikoopa_PartsTable_8022C480_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_WhiteClubba_PartsTable_80229BD4_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_802248EC_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_80220434_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_FrostPiranha_PartsTable_8022ABC4_1D[];
extern ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_8021CBF8_1D[];
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_80221574_1D[];
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_802247CC_1D[];
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_8021E660_1D[];
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_802238D0_1D[];
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_80220314_1D[];
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_80226164_1D[];
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_80222500_1D[];
extern FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_80227404_1D[];
extern EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_802224E4_1D;
extern Vec3i TTYD64_sam_Vector3D_80230694;
extern Vec3i TTYD64_sam_Vector3D_80230778;
extern Vec3i TTYD64_sam_Vector3D_802306F4;
extern Vec3i TTYD64_sam_Vector3D_80230784;
extern Vec3i TTYD64_sam_Vector3D_80230670;
extern Vec3i TTYD64_sam_Vector3D_8023079C;
extern Vec3i TTYD64_sam_Vector3D_8023067C;
extern Vec3i TTYD64_sam_Vector3D_80230688;
extern Vec3i TTYD64_sam_Vector3D_80230730;
extern Vec3i TTYD64_sam_Vector3D_802306AC;
extern Vec3i TTYD64_sam_Vector3D_8023073C;
extern Vec3i TTYD64_sam_Vector3D_802307D8;
extern Vec3i TTYD64_sam_Vector3D_802306B8;
extern Vec3i TTYD64_sam_Vector3D_80230748;
extern Vec3i TTYD64_sam_Vector3D_802306C4;
extern Vec3i TTYD64_sam_Vector3D_802307E4;
extern Vec3i TTYD64_sam_Vector3D_802307F0;
extern Vec3i TTYD64_sam_Vector3D_802306D0;
extern Vec3i TTYD64_sam_Vector3D_80230760;
extern Vec3i TTYD64_sam_Vector3D_802307FC;
extern Vec3i TTYD64_sam_Vector3D_8023076C;
extern Vec3i TTYD64_sam_Vector3D_802306E8;
extern Vec3i TTYD64_sam_Vector3D_80230814;
extern Vec3i TTYD64_sam_Vector3D_80230700;
extern Vec3i TTYD64_sam_Vector3D_80230820;
extern Vec3i TTYD64_sam_Vector3D_8023082C;
extern Vec3i TTYD64_sam_Vector3D_8023070C;
extern Vec3i TTYD64_sam_Vector3D_802307A8;
extern Vec3i TTYD64_sam_Vector3D_802307B4;
extern Vec3i TTYD64_sam_Vector3D_80230724;
extern Vec3i TTYD64_sam_Vector3D_802307C0;
API_CALLABLE(TTYD64_imp_1D_Duplighost_Function_80219524_1D);

API_CALLABLE(TTYD64_imp_1D_Duplighost_Function_80219524_1D) {
    s32 partnerID = evt_get_variable(script, *script->ptrReadPos);
    Actor* actor = get_actor(script->owner1.actorID);
    FormationRow* formation = NULL;

    switch (partnerID) {
        case PARTNER_GOOMBARIO:
            formation = TTYD64_imp_1D_Duplighost_SpecialFormation_8021E660_1D;
            break;
        case PARTNER_KOOPER:
            formation = TTYD64_imp_1D_Duplighost_SpecialFormation_80220314_1D;
            break;
        case PARTNER_BOMBETTE:
            formation = TTYD64_imp_1D_Duplighost_SpecialFormation_80221574_1D;
            break;
        case PARTNER_PARAKARRY:
            formation = TTYD64_imp_1D_Duplighost_SpecialFormation_80222500_1D;
            break;
        case PARTNER_BOW:
            formation = TTYD64_imp_1D_Duplighost_SpecialFormation_802238D0_1D;
            break;
        case PARTNER_WATT:
            formation = TTYD64_imp_1D_Duplighost_SpecialFormation_802247CC_1D;
            break;
        case PARTNER_SUSHIE:
            formation = TTYD64_imp_1D_Duplighost_SpecialFormation_80226164_1D;
            break;
        case PARTNER_LAKILESTER:
            formation = TTYD64_imp_1D_Duplighost_SpecialFormation_80227404_1D;
            break;
    }

    formation->priority = actor->turnPriority;

    return ApiStatus_DONE2;
}

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80224F04_1D = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
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
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 3, 32)
        CaseEq(1)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 4, 32)
        CaseEq(2)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 5, 32)
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
EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_8021F374_1D = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
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
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_sam_kooper_clone_UprightDefenseTable))
            Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1D_Duplighost_IdleAnimations_8021E67C_1D))
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
                Call(b_area_sam_kooper_clone_UnkActorPosFunc)
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
EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80222C7C_1D = {
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
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
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
        Call(GetOwnerTarget, LVar2, 0)
        IfEq(LVar2, 0)
            Call(GetActorHP, LVar2, LVar1)
        Else
            Call(TTYD64_GetPartnerHP_API, LVar1)
        EndIf
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
EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80226924_1D = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x100003)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, 20, 30, LVar2)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x100001)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, -1)
        Add(LVar1, 4)
        Add(LVar2, 2)
        Call(SetPartScale, ACTOR_SELF, 3, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Else
        Add(LVar0, -3)
        Add(LVar1, 10)
        Add(LVar2, 5)
        Call(SetPartScale, ACTOR_SELF, 3, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Wait(1)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 3, 0x100014)
    Call(SetAnimation, ACTOR_SELF, 1, 0x10000F)
    Loop(4)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            AddF(LVar1, Float(2.400390625))
        Else
            Add(LVar1, 6)
        EndIf
        Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, -3)
        Add(LVar1, 16)
        Add(LVar2, 2)
        SetF(LVar3, Float(0.400390625))
    Else
        Add(LVar0, -8)
        Add(LVar1, 40)
        Add(LVar2, 5)
        SetF(LVar3, Float(1.0))
    EndIf
    Call(PlayEffect_impl, 107, 0, LVar0, LVar1, LVar2, LVar3, 30, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 709)
    Thread
        Loop(15)
            Call(SetActorDispOffset, ACTOR_SELF, 1, 0, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 3, 1, 0, 0)
            Wait(1)
            Call(SetActorDispOffset, ACTOR_SELF, -1, 0, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 3, -1, 0, 0)
            Wait(1)
        EndLoop
        Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
        Call(SetPartDispOffset, ACTOR_SELF, 3, 0, 0, 0)
    EndThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x100010)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x100011)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x100012)
    Wait(3)
    Call(SetPartSounds, ACTOR_SELF, 3, 2, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8219)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 3, 0x100015)
            Call(SetPartJumpGravity, ACTOR_SELF, 3, Float(1.5))
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(RandInt, 100, LVar3)
            Sub(LVar3, 50)
            Add(LVar0, LVar3)
            Call(JumpPartTo, ACTOR_SELF, 3, LVar0, 0, LVar2, 20, 1)
            Thread
                Add(LVar0, -50)
                Call(JumpPartTo, ACTOR_SELF, 3, LVar0, 0, LVar2, 15, 1)
                Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
            EndThread
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 60)
            Call(SetAnimation, ACTOR_SELF, 1, 0x100003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 3, 0x100015)
    Call(SetPartJumpGravity, ACTOR_SELF, 3, Float(1.5))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 20, 1)
    Thread
        Add(LVar0, -50)
        Call(JumpPartTo, ACTOR_SELF, 3, LVar0, 0, LVar2, 15, 1)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    EndThread
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
        CaseEq(1)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 4, 32)
        CaseEq(2)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 5, 32)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(15)
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 8)
            Call(SetAnimation, ACTOR_SELF, 1, 0x100003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_Goombario_Headbonk_1D = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    ExecWait(TTYD64_imp_1D_Duplighost_Script_8021D698_1D)
    ExecWait(b_area_sam_goombario_clone_EVS_CalculateJumpTime)
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
    Call(b_area_sam_goombario_clone_UnkFunc62, LVarA, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetJumpAnimations, ACTOR_SELF, 1, 0x90006, 0x90006, 0x90006)
            Call(b_area_sam_goombario_clone_ActorJumpToPos)
            Thread
                Call(ShakeCam, 1, 0, 5, Float(1.0))
            EndThread
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(20)
            Call(YieldTurn)
            ExecWait(b_area_sam_goombario_clone_EVS_HeadbonkFollowthrough)
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
    Call(GetOwnerTarget, LVarA, 0)
    IfEq(LVarA, 0)
        Call(GetActorHP, 0, LVar0)
    Else
        Call(TTYD64_GetPartnerHP_API, LVar0)
    EndIf
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
            Call(b_area_sam_goombario_clone_UnkFunc62, LVarA, 3)
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
            Call(b_area_sam_goombario_clone_UnkFunc62, LVarA, 3)
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
            Call(b_area_sam_goombario_clone_UnkFunc62, LVarA, 3)
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
            ExecWait(b_area_sam_goombario_clone_EVS_HeadbonkFollowthrough)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_FrostPiranha_Script_8022B3AC_1D = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x360118)
        Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
        Wait(8)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 27)
        Set(LVar1, 0)
        Set(LVar3, LVar0)
        Set(LVar4, LVar1)
        Set(LVar5, LVar2)
        Call(GetOwnerTarget, LVar9, 0)
        Call(GetActorPos, LVar9, LVar6, LVar7, LVar8)
        Add(LVar3, LVar6)
        Add(LVar4, LVar7)
        Add(LVar5, LVar8)
        Div(LVar3, 2)
        Div(LVar4, 2)
        Div(LVar5, 2)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, LVar3, LVar4, LVar5)
        Call(SetBattleCamDist, 300)
        Call(SetBattleCamOffsetY, 40)
        Wait(20)
        Call(PlaySoundAtActor, ACTOR_SELF, 801)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetActorFlagBits, ACTOR_SELF, 4, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x360117)
        Wait(8)
    Else
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x360103)
        Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
        Call(SetAnimation, ACTOR_SELF, 1, 0x360103)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Add(LVar0, 10)
        Else
            Add(LVar0, 27)
        EndIf
        Set(LVar1, 0)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(RunToGoal, ACTOR_SELF, 0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x360101)
    EndIf
    Thread
        Wait(8)
        Call(PlaySoundAtActor, ACTOR_SELF, 8414)
    EndThread
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x360105)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x360106)
            Wait(6)
            Call(SetAnimation, ACTOR_SELF, 1, 0x360107)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(14)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
                Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
                Call(PlaySoundAtActor, ACTOR_SELF, 802)
                Call(SetAnimation, ACTOR_SELF, 1, 0x360118)
                Wait(10)
                Call(SetGoalToHome, ACTOR_SELF)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(PlaySoundAtActor, ACTOR_SELF, 801)
                Call(SetAnimation, ACTOR_SELF, 1, 0x360117)
                Wait(10)
                Call(SetActorFlagBits, ACTOR_SELF, 4, 0)
            Else
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
                Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
                Call(SetActorYaw, ACTOR_SELF, 180)
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                ExecWait(b_area_sam_frost_piranha_EVS_ReturnHome)
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x360105)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x360106)
    Wait(1)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 5, 32)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x360107)
            Wait(20)
            Call(YieldTurn)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
                Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
                Call(PlaySoundAtActor, ACTOR_SELF, 802)
                Call(SetAnimation, ACTOR_SELF, 1, 0x360118)
                Wait(10)
                Call(SetGoalToHome, ACTOR_SELF)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(PlaySoundAtActor, ACTOR_SELF, 801)
                Call(SetAnimation, ACTOR_SELF, 1, 0x360117)
                Wait(10)
                Call(SetActorFlagBits, ACTOR_SELF, 4, 0)
            Else
                Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
                ExecWait(b_area_sam_frost_piranha_EVS_ReturnHome)
            EndIf
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_WhiteClubba_Script_TakeTurn_8022A18C_1D = {
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
EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_8021EA18_1D = {
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
                ExecWait(TTYD64_imp_1D_Duplighost_Script_8021BC34_1D)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0013)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xA0011)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_sam_kooper_clone_ToppledDefenseTable))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_1D_Duplighost_IdleAnimations_8021E6C8_1D))
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
            UseBuf(Ref(b_area_sam_kooper_clone_FlipPosOffsets))
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80223F50_1D = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 19)
    Call(RandInt, 100, LVar3)
    IfLt(LVar3, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 350)
    Call(SetBattleCamOffsetY, 40)
    Call(MoveBattleCamOver, 80)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetTargetActor, ACTOR_SELF, LVar3)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0xE0003)
    Call(b_area_sam_watt_clone_WattFXSetEffect, 1)
    Call(AddGoalPos, ACTOR_SELF, 15, -10, 5)
    Call(FlyToGoal, ACTOR_SELF, 30, 0, 10)
    Call(SetAnimation, ACTOR_SELF, 1, 0xE0001)
    Call(b_area_sam_watt_clone_WattFXSetEffect, 0)
    Wait(5)
    Call(b_area_sam_watt_clone_WattFXSetBouncing, 0)
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
            Call(b_area_sam_watt_clone_WattFXSetActive, 1)
            Call(b_area_sam_watt_clone_WattFXSetBouncing, 1)
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
    Call(b_area_sam_watt_clone_WattFXSetActive, 0)
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
    Call(b_area_sam_watt_clone_UnkBackgroundFunc3)
    Set(LVar9, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xE0006)
    Loop(LVarA)
        Add(LVar9, 3)
        IfGt(LVar9, 200)
            Set(LVar9, 200)
        EndIf
        Call(b_area_sam_watt_clone_SetBackgroundAlpha, LVar9)
        Wait(1)
    EndLoop
    Call(SetAnimation, ACTOR_SELF, 1, 0xE0001)
    Call(SetActorPaletteEffect, ACTOR_SELF, 1, 9)
    Call(AddBattleCamDist, 75)
    Call(MoveBattleCamOver, 5)
    Thread
        Wait(2)
        Call(b_area_sam_watt_clone_SetBackgroundAlpha, 0)
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
            Call(b_area_sam_watt_clone_WattFXSetActive, 1)
            Call(b_area_sam_watt_clone_WattFXSetBouncing, 1)
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
EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80220CA0_1D = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Wait(10)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 40, 0, 0)
    Call(MoveBattleCamOver, 30)
    Call(SetAnimation, ACTOR_SELF, 1, 0xB0008)
    Call(RunToGoal, ACTOR_SELF, 30, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xB0004)
    Call(SetAnimation, ACTOR_SELF, 1, 0xB000F)
    Wait(15)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8224)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -10, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0010)
            Call(RunToGoal, ACTOR_SELF, 5, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0004)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 15, 0)
                Set(LVar0, 0)
                Loop(10)
                    Add(LVar0, 72)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(AddGoalPos, ACTOR_SELF, -60, 0, 0)
            Call(RunToGoal, ACTOR_SELF, 10, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0004)
            Thread
                Call(b_area_sam_bombette_clone_UnkActorPosFunc)
            EndThread
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0008)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Set(LVarA, LVar0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0xB0010)
    Call(RunToGoal, ACTOR_SELF, 4, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
        CaseEq(1)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 3, 32)
        CaseEq(2)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 5, 32)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0004)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 8)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0011)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB000E)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0011)
            Add(LVar0, 40)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB000E)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0011)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB000E)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0011)
            Add(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB000E)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0004)
            Wait(8)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0xB0008)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
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
EvtScript TTYD64_imp_1D_Gulpit_Script_8022898C_1D = {
    Set(LVarA, LVar0)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Sub(LVar2, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x520002)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x520001)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 8430)
    Call(GetActorVar, LVarA, 0, LVar0)
    Set(LVarB, LVar0)
    Switch(LVarB)
        CaseEq(0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x520005)
            Wait(3)
            Call(RemoveActor, LVarA)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x520006)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0x520007)
            Set(LVarA, 2)
        CaseEq(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x520008)
            Wait(3)
            Call(RemoveActor, LVarA)
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x520009)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 1, 0x52000A)
            Set(LVarA, 3)
    EndSwitch
    Call(SetPartSounds, ACTOR_SELF, LVarA, 2, 985, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVar9, LVar0)
            Call(UseBattleCamPreset, 2)
            Call(SetPartFlagBits, ACTOR_SELF, LVarA, 1, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Add(LVar2, 2)
            Call(SetPartPos, ACTOR_SELF, LVarA, LVar0, LVar1, LVar2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -100, 0, 5)
            Call(SetPartMoveSpeed, ACTOR_SELF, LVarA, Float(14.0))
            Call(SetPartJumpGravity, ACTOR_SELF, LVarA, Float(0.009765625))
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpPartTo, ACTOR_SELF, LVarA, LVar0, LVar1, LVar2, 0, 1)
            Call(SetPartFlagBits, ACTOR_SELF, LVarA, 1, 1)
            IfEq(LVar9, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(YieldTurn)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(b_area_sam_gulpit_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetPartFlagBits, ACTOR_SELF, LVarA, 1, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Add(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, LVarA, LVar0, LVar1, LVar2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVarA, Float(14.0))
    Call(SetPartJumpGravity, ACTOR_SELF, LVarA, Float(0.009765625))
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpPartTo, ACTOR_SELF, LVarA, LVar0, LVar1, LVar2, 0, 1)
    Switch(LVarA)
        CaseEq(2)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 7, 32)
        CaseEq(3)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 5, 32)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x520001)
            Call(GetPartOffset, ACTOR_SELF, LVarA, LVar0, LVar1, LVar2)
            Add(LVar0, -100)
            Call(SetPartJumpGravity, ACTOR_SELF, LVarA, Float(1.0))
            Call(JumpPartTo, ACTOR_SELF, LVarA, LVar0, LVar1, LVar2, 25, 1)
            Call(SetPartFlagBits, ACTOR_SELF, LVarA, 1, 1)
            Wait(10)
            Call(YieldTurn)
            ExecWait(b_area_sam_gulpit_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_CopyPartner_1D = {
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
    Call(b_area_sam_watt_clone_UnkBackgroundFunc3)
    Call(MakeLerp, 0, 200, 20, 0)
    Label(0)
    Call(UpdateLerp)
    Call(b_area_sam_watt_clone_SetBackgroundAlpha, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    Wait(10)
    Call(b_area_sam_duplighost_GetPartnerAndLevel, LVar5, LVar6)
    Call(TTYD64_imp_1D_Duplighost_Function_80219524_1D, LVar5)
    Switch(LVar5)
        CaseEq(1)
            Call(SummonEnemy, Ref(TTYD64_imp_1D_Duplighost_SpecialFormation_8021E660_1D), 0)
        CaseEq(2)
            Call(SummonEnemy, Ref(TTYD64_imp_1D_Duplighost_SpecialFormation_80220314_1D), 0)
        CaseEq(3)
            Call(SummonEnemy, Ref(TTYD64_imp_1D_Duplighost_SpecialFormation_80221574_1D), 0)
        CaseEq(4)
            Call(SummonEnemy, Ref(TTYD64_imp_1D_Duplighost_SpecialFormation_80222500_1D), 0)
        CaseEq(9)
            Call(SummonEnemy, Ref(TTYD64_imp_1D_Duplighost_SpecialFormation_802238D0_1D), 0)
        CaseEq(6)
            Call(SummonEnemy, Ref(TTYD64_imp_1D_Duplighost_SpecialFormation_802247CC_1D), 0)
        CaseEq(7)
            Call(SummonEnemy, Ref(TTYD64_imp_1D_Duplighost_SpecialFormation_80226164_1D), 0)
        CaseEq(8)
            Call(SummonEnemy, Ref(TTYD64_imp_1D_Duplighost_SpecialFormation_80227404_1D), 0)
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
        Call(b_area_sam_watt_clone_SetBackgroundAlpha, LVar0)
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
EvtScript TTYD64_imp_1D_Duplighost_Script_80221D54_1D = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0xC0003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 20, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 10)
    Call(SetAnimation, ACTOR_SELF, 1, 0xC0000)
    Wait(3)
    Call(UseBattleCamPresetImmediately, 1)
    Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8196)
    Call(SetAnimation, ACTOR_SELF, 1, 0xC0014)
    Call(AddGoalPos, ACTOR_SELF, 0, 10, 0)
    Call(FlyToGoal, ACTOR_SELF, 5, 0, 0)
    Wait(2)
    Thread
        Wait(3)
        Call(SetAnimation, ACTOR_SELF, 1, 0xC0004)
    EndThread
    Call(AddGoalPos, ACTOR_SELF, 40, 15, 0)
    Call(FlyToGoal, ACTOR_SELF, 20, -20, 6)
    Call(PlaySoundAtActor, ACTOR_SELF, 8197)
    Call(EnableActorBlur, ACTOR_SELF, 1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0xC0005)
    Call(FlyToGoal, ACTOR_SELF, 5, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Wait(5)
                Call(SetAnimation, ACTOR_SELF, 1, 0xC0001)
            EndThread
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -40, 10, 0)
            Call(FlyToGoal, ACTOR_SELF, 10, -20, 4)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(20)
            Call(EnableActorBlur, ACTOR_SELF, 0)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xC0003)
            Call(FlyToGoal, ACTOR_SELF, 0, -5, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(EnableActorBlur, ACTOR_SELF, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0xC0006)
    Wait(1)
    Call(GetActorVar, ACTOR_SELF, 1, LVar9)
    Switch(LVar9)
        CaseEq(0)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 2, 32)
        CaseEq(1)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 3, 32)
        CaseEq(2)
            Wait(2)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 5, 32)
    EndSwitch
    Call(PlaySound, 0)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0xC0005)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
            Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0xC0000)
            Thread
                Wait(4)
                Call(SetAnimation, ACTOR_SELF, 1, 0xC0003)
            EndThread
            Call(AddGoalPos, ACTOR_SELF, 30, 0, 0)
            Call(JumpWithBounce, ACTOR_SELF, 10, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xC0001)
            Wait(6)
            Call(YieldTurn)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0xC0003)
            Call(FlyToGoal, ACTOR_SELF, 0, -5, 0)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_GRYMagikoopa_Script_TakeTurn_8022E890_1D = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_sam_gray_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
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
        ExecWait(b_area_sam_gray_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        ExecWait(TTYD64_imp_1D_GRYMagikoopa_Script_GRYMagikoopa_ShapeSpell_1D)
    Else
        ExecWait(TTYD64_imp_1D_GRYMagikoopa_Script_GRYMagikoopa_WandStrike_1D)
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
EvtScript TTYD64_imp_1D_Duplighost_Script_8021C0F8_1D = {
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
    Call(SetIdleAnimations, LVarA, 1, Ref(b_area_sam_duplighost_FlailingAnims))
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
    Call(SetIdleAnimations, LVarA, 1, Ref(b_area_sam_duplighost_RunAnims))
    Call(SetAnimation, LVarA, 1, 0x4E0004)
    Call(SetActorSpeed, LVarA, Float(8.0))
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVarB, LVarC, LVarD)
    Call(SetGoalPos, LVarA, LVarB, 0, LVarD)
    Call(RunToGoal, LVarA, 0, 0)
    Call(SetAnimation, LVarA, 1, 0x4E0002)
    Call(SetActorYaw, LVarA, 0)
    Call(RemoveActorDecoration, LVarA, 1, 0)
    Call(SetIdleAnimations, LVarA, 1, Ref(TTYD64_imp_1D_Duplighost_IdleAnimations_8021AE90_1D))
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
EvtScript TTYD64_imp_1D_GRYMagikoopa_Script_GRYMagikoopa_WandStrike_1D = {
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
EvtScript TTYD64_imp_1D_GRYMagikoopa_Script_GRYMagikoopa_ShapeSpell_1D = {
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
            Call(b_area_sam_gray_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
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
    Call(b_area_sam_gray_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
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
EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_80221760_1D = {
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
                ExecWait(TTYD64_imp_1D_Duplighost_Script_8021BC34_1D)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
            ExecWait(TTYD64_imp_1D_Duplighost_Script_8021C0F8_1D)
            Return
        CaseEq(38)
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xC000D)
            Set(LVar2, 22)
            ExecWait(TTYD64_imp_1D_Duplighost_Script_8021C784_1D)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_8022635C_1D = {
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
                ExecWait(TTYD64_imp_1D_Duplighost_Script_8021BC34_1D)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
EvtScript TTYD64_imp_1D_FrostPiranha_Script_8022BD44_1D = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x360103)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x360103)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 20)
    Else
        Add(LVar0, 50)
    EndIf
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x360101)
    Call(SetAnimation, ACTOR_SELF, 1, 0x36010B)
    Wait(11)
    Call(PlaySoundAtActor, ACTOR_SELF, 939)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 12)
        Set(LVar1, 5)
        SetF(LVar3, Float(0.400390625))
    Else
        Add(LVar0, 32)
        Set(LVar1, 13)
        SetF(LVar3, Float(1.0))
    EndIf
    Call(b_area_sam_frost_piranha_UnkEffect6FFunc, LVar2, LVar0, LVar1, LVar2, LVar3, 30, 120, 0, 120)
    Wait(1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x36010C)
    Wait(5)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 8, 0x4000, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x36010D)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(14)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(b_area_sam_frost_piranha_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x40000008, 0xFFFF, 0x42FE, 0, 32)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x36010D)
            Wait(20)
            Call(YieldTurn)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_sam_frost_piranha_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_LungeAttack_1D = {
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
            ExecWait(b_area_sam_duplighost_EVS_ReturnHome)
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
            ExecWait(b_area_sam_duplighost_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_802226EC_1D = {
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
                ExecWait(TTYD64_imp_1D_Duplighost_Script_8021BC34_1D)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
            ExecWait(TTYD64_imp_1D_Duplighost_Script_8021C0F8_1D)
            Return
        CaseEq(38)
            Call(UseBattleCamPreset, 2)
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xD0015)
            Set(LVar2, 14)
            ExecWait(TTYD64_imp_1D_Duplighost_Script_8021C784_1D)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_8021CCA0_1D = {
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
                ExecWait(TTYD64_imp_1D_Duplighost_Script_8021BC34_1D)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
            ExecWait(TTYD64_imp_1D_Duplighost_Script_8021C0F8_1D)
            Return
        CaseEq(38)
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x9000A)
            Set(LVar2, 12)
            ExecWait(TTYD64_imp_1D_Duplighost_Script_8021C784_1D)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
EvtScript TTYD64_imp_1D_Duplighost_Script_HandleEvent_80224994_1D = {
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
                ExecWait(TTYD64_imp_1D_Duplighost_Script_8021BC34_1D)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
            ExecWait(TTYD64_imp_1D_Duplighost_Script_8021C0F8_1D)
            Return
        CaseEq(38)
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0xF000D)
            Set(LVar2, 20)
            ExecWait(TTYD64_imp_1D_Duplighost_Script_8021C784_1D)
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
            ExecWait(b_area_sam_EVS_Duplighost_OnDeath)
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
EvtScript TTYD64_imp_1D_Duplighost_Script_8021BC34_1D = {
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
    Call(SetIdleAnimations, LVarA, 1, Ref(b_area_sam_duplighost_FlailingAnims))
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
    Call(SetIdleAnimations, LVarA, 1, Ref(TTYD64_imp_1D_Duplighost_IdleAnimations_8021AE90_1D))
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
EvtScript TTYD64_imp_1D_Gulpit_Script_80228518_1D = {
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
        Add(LVar0, 80)
        Set(LVar1, 0)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x520003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(AddGoalPos, ACTOR_SELF, 10, 0, 0)
    Else
        Call(AddGoalPos, ACTOR_SELF, 20, 0, 0)
    EndIf
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x520001)
    Wait(10)
    Thread
        Wait(3)
        Call(PlaySoundAtActor, ACTOR_SELF, 8430)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x520004)
    Wait(9)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(b_area_sam_gulpit_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Call(YieldTurn)
            ExecWait(b_area_sam_gulpit_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_8021C784_1D = {
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
EvtScript TTYD64_imp_1D_Duplighost_Script_Goombario_Tattle_1D = {
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
    Call(b_area_sam_goombario_clone_OpenTattleWindow, LVar5)
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
    Call(b_area_sam_goombario_clone_CalculateTattleCamBoomLength)
    Wait(1)
    Call(SetCamLookTarget, 2, LVar0, LVar1, LVar2)
    Call(SetInterpCamParams, 2, 0, LVar3, 100, 4)
    Wait(2)
    Call(PlaySoundAtActor, ACTOR_SELF, 642)
    Call(SetCamNoDraw, 2, 1)
    Wait(10)
    Call(ActorSpeak, 0x1C0092, ACTOR_SELF, 1, 0x9000F, 0x90001)
    Call(b_area_sam_goombario_clone_CloseTattleWindow, LVar5)
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
EvtScript TTYD64_imp_1D_Gulpit_Script_TakeTurn_802291B4_1D = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_1D_Gulpit_Script_80228518_1D)
        Return
    EndIf
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        ExecWait(TTYD64_imp_1D_Gulpit_Script_80228518_1D)
        Return
    EndIf
    Set(LVarA, 0)
    Call(CreateHomeTargetList, 0x10002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar2)
    IfEq(LVar2, 55)
        Add(LVarA, 1)
        Switch(LVarA)
            CaseEq(1)
                Set(LVarB, LVar0)
            CaseEq(2)
                Set(LVarC, LVar0)
            CaseEq(3)
                Set(LVarD, LVar0)
        EndSwitch
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Switch(LVarA)
        CaseEq(0)
            ExecWait(TTYD64_imp_1D_Gulpit_Script_80228518_1D)
        CaseEq(1)
            Set(LVar0, LVarB)
            ExecWait(TTYD64_imp_1D_Gulpit_Script_8022898C_1D)
        CaseEq(2)
            Call(RandInt, 1, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Set(LVar0, LVarB)
                CaseEq(1)
                    Set(LVar0, LVarC)
            EndSwitch
            ExecWait(TTYD64_imp_1D_Gulpit_Script_8022898C_1D)
        CaseGe(3)
            Call(RandInt, 2, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Set(LVar0, LVarB)
                CaseEq(1)
                    Set(LVar0, LVarC)
                CaseEq(2)
                    Set(LVar0, LVarD)
            EndSwitch
            ExecWait(TTYD64_imp_1D_Gulpit_Script_8022898C_1D)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_80227C40_1D = {
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
                    ExecWait(TTYD64_imp_1D_Duplighost_Script_CopyPartner_1D)
                Else
                    Call(GetBattleVar, 3, LVar0)
                    Call(b_area_sam_duplighost_GetPartnerAndLevel, LVar1, LVar2)
                    IfEq(LVar0, LVar1)
                        ExecWait(TTYD64_imp_1D_Duplighost_Script_CopyPartner_1D)
                    Else
                        ExecWait(TTYD64_imp_1D_Duplighost_Script_LungeAttack_1D)
                    EndIf
                EndIf
            Else
                ExecWait(TTYD64_imp_1D_Duplighost_Script_LungeAttack_1D)
            EndIf
        CaseEq(1)
        CaseEq(2)
            ExecWait(TTYD64_imp_1D_Duplighost_Script_LungeAttack_1D)
        CaseEq(3)
    EndSwitch
    Return
    End
};
// clang-format on

Battle TTYD64_sam_FormationTable[] = {
    { .name = "\320\261\320\261x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_sam_Formation_00,
      .stage = &b_area_sam_sam_01,
      .onBattleStart = NULL },
    { .name = "\264\303\257\363x2",
      .formationSize = 7,
      .formation = (Formation*) TTYD64_sam_Formation_01,
      .stage = &b_area_sam_sam_01,
      .onBattleStart = NULL },
    { .name = "\264\303\257\363x3",
      .formationSize = 8,
      .formation = (Formation*) TTYD64_sam_Formation_02,
      .stage = &b_area_sam_sam_01,
      .onBattleStart = NULL },
    { .name = "\264\303\257\363x2,\242\244\271\321\303\257\363",
      .formationSize = 8,
      .formation = (Formation*) TTYD64_sam_Formation_03,
      .stage = &b_area_sam_sam_01,
      .onBattleStart = NULL },
    { .name = "\264\303\257\363,\242\244\271\321\303\257\363,\264\303\257\363",
      .formationSize = 8,
      .formation = (Formation*) TTYD64_sam_Formation_04,
      .stage = &b_area_sam_sam_01,
      .onBattleStart = NULL },
    { .name = "\264\303\257\363,\242\244\271\321\303\257\363,\264\303\257\363,\242\244\271\321\303\257\363",
      .formationSize = 9,
      .formation = (Formation*) TTYD64_sam_Formation_05,
      .stage = &b_area_sam_sam_01,
      .onBattleStart = NULL },
    { .name = "\242\244\271\321\303\257\363x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_sam_Formation_06,
      .stage = &b_area_sam_sam_01,
      .onBattleStart = NULL },
    { .name = "\242\244\271\321\303\257\363x\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_sam_Formation_07,
      .stage = &b_area_sam_sam_01,
      .onBattleStart = NULL },
    { .name = "\242\244\271\321\303\257\363x\022,\264\303\257\363",
      .formationSize = 8,
      .formation = (Formation*) TTYD64_sam_Formation_08,
      .stage = &b_area_sam_sam_01,
      .onBattleStart = NULL },
    { .name = "\242\244\271\321\303\257\363,\264\303\257\363,\242\244\271\321\303\257\363",
      .formationSize = 8,
      .formation = (Formation*) TTYD64_sam_Formation_09,
      .stage = &b_area_sam_sam_01,
      .onBattleStart = NULL },
    { .name = "\242\244\271\321\303\257\363,\264\303\257\363,\242\244\271\321\303\257\363,\264\303\257\363",
      .formationSize = 9,
      .formation = (Formation*) TTYD64_sam_Formation_0A,
      .stage = &b_area_sam_sam_01,
      .onBattleStart = NULL },
    { .name = "\333\357\244\310\254\334\363x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_sam_Formation_0B,
      .stage = &b_area_sam_sam_01,
      .onBattleStart = NULL },
    { .name = "\333\357\244\310\254\334\363,\321\303\257\363,\254\334\363,\321\303\257\363",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_sam_Formation_0C,
      .stage = &b_area_sam_sam_01,
      .onBattleStart = NULL },
    { .name = "\333\357\244\310\254\334\363,\321\303\257\363,\254\334\363,\260\354\244\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_sam_Formation_0D,
      .stage = &b_area_sam_sam_01,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_8021D698_1D = {
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
    Call(AddGoalPos, ACTOR_SELF, 70, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x90003)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x90001)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_FrostPiranha_Script_TakeTurn_8022B2D4_1D = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_imp_1D_FrostPiranha_Script_8022B3AC_1D)
        Return
    EndIf
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetOwnerTarget, LVar1, 0)
    Call(GetStatusFlags, LVar1, LVar0)
    IfFlag(LVar0, 0x4000)
        ExecWait(TTYD64_imp_1D_FrostPiranha_Script_8022B3AC_1D)
        Return
    EndIf
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 250)
        ExecWait(TTYD64_imp_1D_FrostPiranha_Script_8022BD44_1D)
    Else
        ExecWait(TTYD64_imp_1D_FrostPiranha_Script_8022B3AC_1D)
    EndIf
    Return
    End
};
// clang-format on

FormationRow TTYD64_sam_Formation_0A[] = {
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_80230814 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_80230820 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_8023082C },
      .priority = 7,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = (void*) (((u8*) &b_area_sam_pos_rocks_8 + 0x24)) },
      .priority = 6,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = (void*) (((u8*) &b_area_sam_pos_rocks_8 + 0x30)) },
      .priority = 5,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_sam_Formation_05[] = {
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 0 },
      .priority = 20,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 1 },
      .priority = 19,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 2 },
      .priority = 18,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 3 },
      .priority = 17,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_80230760 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_8023076C },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_80230778 },
      .priority = 7,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_80230784 },
      .priority = 6,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = (void*) (((u8*) &b_area_sam_pos_rocks_5 + 0x30)) },
      .priority = 5,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_sam_Formation_04[] = {
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 0 },
      .priority = 20,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 1 },
      .priority = 19,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 2 },
      .priority = 18,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_80230724 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_80230730 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_8023073C },
      .priority = 7,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_80230748 },
      .priority = 6,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = (void*) (((u8*) &b_area_sam_pos_rocks_4 + 0x30)) },
      .priority = 5,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_sam_Formation_02[] = {
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 0 },
      .priority = 20,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 1 },
      .priority = 19,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 2 },
      .priority = 18,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_802306AC },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_802306B8 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_802306C4 },
      .priority = 7,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_802306D0 },
      .priority = 6,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = (void*) (((u8*) &b_area_sam_pos_rocks_2 + 0x30)) },
      .priority = 5,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_sam_Formation_03[] = {
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 0 },
      .priority = 20,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 1 },
      .priority = 19,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 2 },
      .priority = 18,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_802306E8 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_802306F4 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_80230700 },
      .priority = 7,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_8023070C },
      .priority = 6,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = (void*) (((u8*) &b_area_sam_pos_rocks_3 + 0x30)) },
      .priority = 5,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_sam_Formation_08[] = {
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_8023079C },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_802307A8 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_802307B4 },
      .priority = 7,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_802307C0 },
      .priority = 6,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = (void*) (((u8*) &b_area_sam_pos_rocks_6 + 0x30)) },
      .priority = 5,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_sam_Formation_09[] = {
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_802307D8 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_802307E4 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_802307F0 },
      .priority = 7,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_802307FC },
      .priority = 6,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = (void*) (((u8*) &b_area_sam_pos_rocks_7 + 0x30)) },
      .priority = 5,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_sam_Formation_01[] = {
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 1 },
      .priority = 20,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &TTYD64_imp_1D_Gulpit_1D_Gulpit,
      .home = { .index = 2 },
      .priority = 19,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GULPIT },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_80230670 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_8023067C },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_80230688 },
      .priority = 7,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = &TTYD64_sam_Vector3D_80230694 },
      .priority = 6,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_sam_gulpit_rocks,
      .home = { .vec = (void*) (((u8*) &b_area_sam_pos_rocks_1 + 0x30)) },
      .priority = 5,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

s32 TTYD64_imp_1D_Duplighost_StatusTable_80224840_1D[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_1D_Duplighost_StatusTable_8021E72C_1D[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_1D_GRYMagikoopa_StatusTable_8022C328_1D[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  75, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

s32 TTYD64_imp_1D_Duplighost_StatusTable_80220388_1D[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_1D_Duplighost_StatusTable_80222574_1D[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_1D_Duplighost_StatusTable_8022394C_1D[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_1D_Duplighost_StatusTable_8021CB4C_1D[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_1D_Duplighost_StatusTable_802215E8_1D[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

s32 TTYD64_imp_1D_Duplighost_StatusTable_802261E4_1D[] = {
    1,  0, 2,  0,  6,  60, 9,  70, 7,  50, 4,  75, 3,  0, 11, 0, 5,  75, 10, 75, 8, 80,
    31, 0, 32, -1, 37, 0,  34, 0,  36, -1, 35, 0,  33, 0, 38, 0, 39, 0,  41, -1, 0,
};

// clang-format off
EvtScript TTYD64_imp_1D_GRYMagikoopa_Script_Init_8022E748_1D = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam_gray_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1D_GRYMagikoopa_Script_TakeTurn_8022E890_1D))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_sam_gray_magikoopa_EVS_HandleEvent))
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
EvtScript TTYD64_imp_1D_Duplighost_Script_Init_8021E824_1D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1D_Duplighost_Script_TakeTurn_8021F374_1D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam_kooper_clone_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1D_Duplighost_Script_HandleEvent_8021EA18_1D))
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_Init_8021AFF8_1D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1D_Duplighost_Script_TakeTurn_80227C40_1D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam_duplighost_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_sam_duplighost_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_sam_duplighost_EVS_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_sam_Formation_0D[] = {
    { .actor = &TTYD64_imp_1D_WhiteClubba_1D_WhiteClubba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_WhiteClubba_1D_WhiteClubba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1D_GRYMagikoopa_1D_GRYMagikoopa,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_sam_Formation_0C[] = {
    { .actor = &TTYD64_imp_1D_WhiteClubba_1D_WhiteClubba,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_WhiteClubba_1D_WhiteClubba,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
};

FormationRow TTYD64_sam_Formation_07[] = {
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
};

ActorPartBlueprint TTYD64_imp_1D_Gulpit_PartsTable_80227EEC_1D[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -7, 48 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1D_Gulpit_IdleAnimations_80227DD0_1D,
        .defenseTable = b_area_sam_gulpit_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -3, -23 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_sam_gulpit_BigRockAnims,
        .defenseTable = b_area_sam_gulpit_DefenseTable,
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
        .idleAnimations = b_area_sam_gulpit_SmallRockAnims,
        .defenseTable = b_area_sam_gulpit_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_8021E604_1D = {
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 10)
        ExecWait(TTYD64_imp_1D_Duplighost_Script_Goombario_Tattle_1D)
    Else
        ExecWait(TTYD64_imp_1D_Duplighost_Script_Goombario_Headbonk_1D)
    EndIf
    Return
    End
};
// clang-format on

s32 TTYD64_imp_1D_Duplighost_IdleAnimations_8021AE90_1D[] = {
    1,  0x4E0002, 7, 0x4E0000, 6, 0x4E000D, 9, 0x4E0002, 8, 0x4E0000,
    11, 0x4E0002, 5, 0x4E0000, 4, 0x4E000E, 3, 0x4E000E, 0,
};

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80220480_1D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1D_Duplighost_Script_TakeTurn_80220CA0_1D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam_bombette_clone_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_sam_bombette_clone_EVS_HandleEvent))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80224938_1D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1D_Duplighost_Script_TakeTurn_80224F04_1D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam_sushie_clone_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1D_Duplighost_Script_HandleEvent_80224994_1D))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_1D_Duplighost_IdleAnimations_8021E67C_1D[] = {
    1, 0xA0004, 7, 0xA0000, 6, 0xA0000, 9, 0xA0004, 8, 0xA0000, 11, 0xA0004, 5, 0xA0000, 4, 0xA001C, 3, 0xA001C, 0,
};

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80226300_1D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1D_Duplighost_Script_TakeTurn_80226924_1D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam_lakilester_clone_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1D_Duplighost_Script_HandleEvent_8022635C_1D))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_1D_FrostPiranha_IdleAnimations_8022AAB0_1D[] = {
    1,  0x360101, 7, 0x360100, 6, 0x360100, 9, 0x360101, 8, 0x360100,
    11, 0x360100, 5, 0x360100, 5, 0x360100, 4, 0x36010F, 0,
};

s32 TTYD64_imp_1D_GRYMagikoopa_IdleAnimations_8022C560_1D[] = {
    1,  0x560501, 7, 0x560500, 6, 0x560508, 9, 0x560501, 8, 0x560500,
    11, 0x560501, 5, 0x560500, 4, 0x560507, 3, 0x560507, 0,
};

s32 TTYD64_imp_1D_Duplighost_IdleAnimations_8021CAF4_1D[] = {
    1, 0x90001, 7, 0x90000, 6, 0x90000, 9, 0x90001, 8, 0x90000, 11, 0x90001, 5, 0x90000, 4, 0x90014, 3, 0x90014, 0,
};

s32 TTYD64_imp_1D_Duplighost_IdleAnimations_80221590_1D[] = {
    1, 0xC0001, 7, 0xC0000, 6, 0xC0000, 9, 0xC0001, 8, 0xC0000, 11, 0xC0001, 5, 0xC0000, 4, 0xC0001, 3, 0xC0001, 0,
};

s32 TTYD64_imp_1D_Duplighost_IdleAnimations_80226180_1D[] = {
    1,  0x100001, 7, 0x100000, 6, 0x100000, 9, 0x100001, 8, 0x100000,
    11, 0x100001, 5, 0x100000, 4, 0x100008, 3, 0x100001, 0,
};

s32 TTYD64_imp_1D_Duplighost_IdleAnimations_80220330_1D[] = {
    1, 0xB0004, 7, 0xB0000, 6, 0xB0000, 9, 0xB0004, 8, 0xB0000, 11, 0xB0004, 5, 0xB0000, 4, 0xB001E, 3, 0xB001E, 0,
};

s32 TTYD64_imp_1D_WhiteClubba_IdleAnimations_80229AC0_1D[] = {
    1,  0x3A0101, 7, 0x3A0100, 6, 0x3A0103, 9, 0x3A0101, 8, 0x3A0100,
    11, 0x3A0101, 5, 0x3A0100, 4, 0x3A0105, 3, 0x3A0105, 0,
};

s32 TTYD64_imp_1D_Duplighost_IdleAnimations_8021E6C8_1D[] = {
    1, 0xA0019, 7, 0xA0003, 6, 0xA0003, 9, 0xA0019, 8, 0xA0003, 11, 0xA0019, 5, 0xA0003, 4, 0xA0019, 3, 0xA0019, 0,
};

// clang-format off
EvtScript TTYD64_imp_1D_Gulpit_Script_Init_80227F80_1D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1D_Gulpit_Script_TakeTurn_802291B4_1D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam_gulpit_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_sam_gulpit_EVS_HandleEvent))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_Init_8021CC44_1D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1D_Duplighost_Script_TakeTurn_8021E604_1D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam_goombario_clone_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1D_Duplighost_Script_HandleEvent_8021CCA0_1D))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80221704_1D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1D_Duplighost_Script_TakeTurn_802224E4_1D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam_parakarry_clone_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1D_Duplighost_Script_HandleEvent_80221760_1D))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_1D_Duplighost_IdleAnimations_802238EC_1D[] = {
    1, 0xE0001, 7, 0xE0000, 6, 0xE0000, 9, 0xE0001, 8, 0xE0000, 11, 0xE0001, 5, 0xE0000, 4, 0xE000F, 3, 0xE000F, 0,
};

s32 TTYD64_imp_1D_Duplighost_IdleAnimations_8022251C_1D[] = {
    1, 0xD0001, 7, 0xD0000, 6, 0xD0000, 9, 0xD0001, 8, 0xD0000, 11, 0xD0001, 5, 0xD0000, 4, 0xD001A, 3, 0xD001A, 0,
};

s32 TTYD64_imp_1D_Gulpit_IdleAnimations_80227DD0_1D[] = {
    1,  0x520001, 7, 0x520000, 6, 0x52000F, 9, 0x520001, 8, 0x520000,
    11, 0x520001, 5, 0x520000, 4, 0x52000E, 3, 0x52000E, 0,
};

// clang-format off
EvtScript TTYD64_imp_1D_WhiteClubba_Script_Init_80229C20_1D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1D_WhiteClubba_Script_TakeTurn_8022A18C_1D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam_white_clubba_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_sam_white_clubba_EVS_HandleEvent))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80222690_1D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1D_Duplighost_Script_TakeTurn_80222C7C_1D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam_bow_clone_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_1D_Duplighost_Script_HandleEvent_802226EC_1D))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_FrostPiranha_Script_Init_8022AC10_1D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1D_FrostPiranha_Script_TakeTurn_8022B2D4_1D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam_frost_piranha_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_sam_frost_piranha_EVS_HandleEvent))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_Init_80223A68_1D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_1D_Duplighost_Script_TakeTurn_80223F50_1D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_sam_watt_clone_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_sam_watt_clone_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_1D_Duplighost_IdleAnimations_802247E8_1D[] = {
    1, 0xF0001, 7, 0xF0000, 6, 0xF0000, 9, 0xF0001, 8, 0xF0000, 11, 0xF0001, 5, 0xF0000, 4, 0xF0010, 3, 0xF0010, 0,
};

ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_802239F8_1D[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -1, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1D_Duplighost_IdleAnimations_802238EC_1D,
        .defenseTable = b_area_sam_watt_clone_DefenseTable,
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
        .defenseTable = b_area_sam_watt_clone_DefenseTable,
        .eventFlags = 0x80,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_80221694_1D[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -3, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1D_Duplighost_IdleAnimations_80221590_1D,
        .defenseTable = b_area_sam_parakarry_clone_DefenseTable,
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
        .defenseTable = b_area_sam_parakarry_clone_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -16 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_80226290_1D[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -3, 33 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1D_Duplighost_IdleAnimations_80226180_1D,
        .defenseTable = b_area_sam_lakilester_clone_DefenseTable,
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
        .idleAnimations = b_area_sam_lakilester_clone_SpinyAnims,
        .defenseTable = b_area_sam_lakilester_clone_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_80222620_1D[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1D_Duplighost_IdleAnimations_8022251C_1D,
        .defenseTable = b_area_sam_bow_clone_DefenseTable,
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
        .defenseTable = b_area_sam_bow_clone_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_sam_Formation_0B[] = {
    { .actor = &TTYD64_imp_1D_WhiteClubba_1D_WhiteClubba,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
    { .actor = &TTYD64_imp_1D_WhiteClubba_1D_WhiteClubba,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_WHITECLUBBA },
};

FormationRow TTYD64_sam_Formation_00[] = {
    { .actor = &TTYD64_imp_1D_Duplighost_1D_Duplighost,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
    { .actor = &TTYD64_imp_1D_Duplighost_1D_Duplighost,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DUPLIGHOST },
};

FormationRow TTYD64_sam_Formation_06[] = {
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
    { .actor = &TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FROSTPIRANHA },
};

ActorBlueprint TTYD64_imp_1D_FrostPiranha_1D_FrostPiranha = {
    .flags = 0x0,
    .maxHP = 10,
    .type = 0x39,
    .level = 22,
    .partCount = 1,
    .partsData = TTYD64_imp_1D_FrostPiranha_PartsTable_8022ABC4_1D,
    .initScript = &TTYD64_imp_1D_FrostPiranha_Script_Init_8022AC10_1D,
    .statusTable = b_area_sam_frost_piranha_StatusTable,
    .escapeChance = 70,
    .airLiftChance = 20,
    .hurricaneChance = 20,
    .spookChance = 20,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 60, 52 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -22, 32 },
    .statusTextOffset = { 1, 44 },
};

ActorBlueprint TTYD64_imp_1D_Duplighost_GhostBow_1D = {
    .flags = 0x200,
    .maxHP = 15,
    .type = 0x40,
    .level = 23,
    .partCount = 2,
    .partsData = TTYD64_imp_1D_Duplighost_PartsTable_80222620_1D,
    .initScript = &TTYD64_imp_1D_Duplighost_Script_Init_80222690_1D,
    .statusTable = TTYD64_imp_1D_Duplighost_StatusTable_80222574_1D,
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

ActorBlueprint TTYD64_imp_1D_Duplighost_GhostParakarry_1D = {
    .flags = 0x200,
    .maxHP = 15,
    .type = 0x3F,
    .level = 23,
    .partCount = 2,
    .partsData = TTYD64_imp_1D_Duplighost_PartsTable_80221694_1D,
    .initScript = &TTYD64_imp_1D_Duplighost_Script_Init_80221704_1D,
    .statusTable = TTYD64_imp_1D_Duplighost_StatusTable_802215E8_1D,
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

ActorBlueprint TTYD64_imp_1D_Duplighost_GhostSushie_1D = {
    .flags = 0x0,
    .maxHP = 15,
    .type = 0x42,
    .level = 23,
    .partCount = 1,
    .partsData = TTYD64_imp_1D_Duplighost_PartsTable_802248EC_1D,
    .initScript = &TTYD64_imp_1D_Duplighost_Script_Init_80224938_1D,
    .statusTable = TTYD64_imp_1D_Duplighost_StatusTable_80224840_1D,
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

ActorBlueprint TTYD64_imp_1D_Duplighost_GhostBombette_1D = {
    .flags = 0x0,
    .maxHP = 15,
    .type = 0x3E,
    .level = 23,
    .partCount = 1,
    .partsData = TTYD64_imp_1D_Duplighost_PartsTable_80220434_1D,
    .initScript = &TTYD64_imp_1D_Duplighost_Script_Init_80220480_1D,
    .statusTable = TTYD64_imp_1D_Duplighost_StatusTable_80220388_1D,
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

ActorBlueprint TTYD64_imp_1D_Duplighost_GhostWatt_1D = {
    .flags = 0x200,
    .maxHP = 15,
    .type = 0x41,
    .level = 23,
    .partCount = 2,
    .partsData = TTYD64_imp_1D_Duplighost_PartsTable_802239F8_1D,
    .initScript = &TTYD64_imp_1D_Duplighost_Script_Init_80223A68_1D,
    .statusTable = TTYD64_imp_1D_Duplighost_StatusTable_8022394C_1D,
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

ActorBlueprint TTYD64_imp_1D_Duplighost_GhostLakilester_1D = {
    .flags = 0x200,
    .maxHP = 15,
    .type = 0x43,
    .level = 23,
    .partCount = 2,
    .partsData = TTYD64_imp_1D_Duplighost_PartsTable_80226290_1D,
    .initScript = &TTYD64_imp_1D_Duplighost_Script_Init_80226300_1D,
    .statusTable = TTYD64_imp_1D_Duplighost_StatusTable_802261E4_1D,
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

ActorBlueprint TTYD64_imp_1D_WhiteClubba_1D_WhiteClubba = {
    .flags = 0x0,
    .maxHP = 12,
    .type = 0x38,
    .level = 23,
    .partCount = 1,
    .partsData = TTYD64_imp_1D_WhiteClubba_PartsTable_80229BD4_1D,
    .initScript = &TTYD64_imp_1D_WhiteClubba_Script_Init_80229C20_1D,
    .statusTable = b_area_sam_white_clubba_StatusTable,
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

ActorBlueprint TTYD64_imp_1D_GRYMagikoopa_1D_GRYMagikoopa = {
    .flags = 0x0,
    .maxHP = 11,
    .type = 0x57,
    .level = 21,
    .partCount = 1,
    .partsData = TTYD64_imp_1D_GRYMagikoopa_PartsTable_8022C480_1D,
    .initScript = &TTYD64_imp_1D_GRYMagikoopa_Script_Init_8022E748_1D,
    .statusTable = TTYD64_imp_1D_GRYMagikoopa_StatusTable_8022C328_1D,
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

ActorBlueprint TTYD64_imp_1D_Duplighost_GhostKooper_1D = {
    .flags = 0x0,
    .maxHP = 15,
    .type = 0x3D,
    .level = 23,
    .partCount = 1,
    .partsData = TTYD64_imp_1D_Duplighost_PartsTable_8021E7D8_1D,
    .initScript = &TTYD64_imp_1D_Duplighost_Script_Init_8021E824_1D,
    .statusTable = TTYD64_imp_1D_Duplighost_StatusTable_8021E72C_1D,
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

ActorBlueprint TTYD64_imp_1D_Duplighost_GhostGoombario_1D = {
    .flags = 0x0,
    .maxHP = 15,
    .type = 0x3C,
    .level = 23,
    .partCount = 1,
    .partsData = TTYD64_imp_1D_Duplighost_PartsTable_8021CBF8_1D,
    .initScript = &TTYD64_imp_1D_Duplighost_Script_Init_8021CC44_1D,
    .statusTable = TTYD64_imp_1D_Duplighost_StatusTable_8021CB4C_1D,
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

ActorBlueprint TTYD64_imp_1D_Duplighost_1D_Duplighost = {
    .flags = 0x0,
    .maxHP = 15,
    .type = 0x3B,
    .level = 23,
    .partCount = 1,
    .partsData = TTYD64_imp_1D_Duplighost_PartsTable_8021AFAC_1D,
    .initScript = &TTYD64_imp_1D_Duplighost_Script_Init_8021AFF8_1D,
    .statusTable = b_area_sam_duplighost_StatusTable,
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

ActorBlueprint TTYD64_imp_1D_Gulpit_1D_Gulpit = {
    .flags = 0x0,
    .maxHP = 12,
    .type = 0x36,
    .level = 22,
    .partCount = 3,
    .partsData = TTYD64_imp_1D_Gulpit_PartsTable_80227EEC_1D,
    .initScript = &TTYD64_imp_1D_Gulpit_Script_Init_80227F80_1D,
    .statusTable = b_area_sam_gulpit_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 50,
    .hurricaneChance = 50,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 53, 50 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -3, 37 },
    .statusTextOffset = { 10, 45 },
};

ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_8021AFAC_1D[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -5, 25 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1D_Duplighost_IdleAnimations_8021AE90_1D,
        .defenseTable = b_area_sam_duplighost_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -2, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_8021E7D8_1D[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1D_Duplighost_IdleAnimations_8021E67C_1D,
        .defenseTable = b_area_sam_kooper_clone_UprightDefenseTable,
        .eventFlags = 0x1000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -16 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1D_GRYMagikoopa_PartsTable_8022C480_1D[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1D_GRYMagikoopa_IdleAnimations_8022C560_1D,
        .defenseTable = b_area_sam_gray_magikoopa_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1D_WhiteClubba_PartsTable_80229BD4_1D[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -12, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1D_WhiteClubba_IdleAnimations_80229AC0_1D,
        .defenseTable = b_area_sam_white_clubba_DefenseTable,
        .eventFlags = 0x8,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 8, -3 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_802248EC_1D[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1D_Duplighost_IdleAnimations_802247E8_1D,
        .defenseTable = b_area_sam_sushie_clone_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -12 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_80220434_1D[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 22 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1D_Duplighost_IdleAnimations_80220330_1D,
        .defenseTable = b_area_sam_bombette_clone_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -2, -7 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1D_FrostPiranha_PartsTable_8022ABC4_1D[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -15, 50 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1D_FrostPiranha_IdleAnimations_8022AAB0_1D,
        .defenseTable = b_area_sam_frost_piranha_DefenseTable,
        .eventFlags = 0x8,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 3, -14 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_1D_Duplighost_PartsTable_8021CBF8_1D[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_1D_Duplighost_IdleAnimations_8021CAF4_1D,
        .defenseTable = b_area_sam_goombario_clone_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -9 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_80221574_1D[] = {
    { .actor = &TTYD64_imp_1D_Duplighost_GhostBombette_1D,
      .home = { .vec = &b_area_sam_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_802247CC_1D[] = {
    { .actor = &TTYD64_imp_1D_Duplighost_GhostWatt_1D,
      .home = { .vec = &b_area_sam_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_8021E660_1D[] = {
    { .actor = &TTYD64_imp_1D_Duplighost_GhostGoombario_1D,
      .home = { .vec = &b_area_sam_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_802238D0_1D[] = {
    { .actor = &TTYD64_imp_1D_Duplighost_GhostBow_1D,
      .home = { .vec = &b_area_sam_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_80220314_1D[] = {
    { .actor = &TTYD64_imp_1D_Duplighost_GhostKooper_1D,
      .home = { .vec = &b_area_sam_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_80226164_1D[] = {
    { .actor = &TTYD64_imp_1D_Duplighost_GhostSushie_1D,
      .home = { .vec = &b_area_sam_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_80222500_1D[] = {
    { .actor = &TTYD64_imp_1D_Duplighost_GhostParakarry_1D,
      .home = { .vec = &b_area_sam_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_imp_1D_Duplighost_SpecialFormation_80227404_1D[] = {
    { .actor = &TTYD64_imp_1D_Duplighost_GhostLakilester_1D,
      .home = { .vec = &b_area_sam_DuplighostSummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

// clang-format off
EvtScript TTYD64_imp_1D_Duplighost_Script_TakeTurn_802224E4_1D = {
    ExecWait(TTYD64_imp_1D_Duplighost_Script_80221D54_1D)
    Return
    End
};
// clang-format on

Vec3i TTYD64_sam_Vector3D_80230694 = { -7, 0, -48 };

Vec3i TTYD64_sam_Vector3D_80230778 = { -17, 0, -40 };

Vec3i TTYD64_sam_Vector3D_802306F4 = { -20, 0, -50 };

Vec3i TTYD64_sam_Vector3D_80230784 = { -7, 0, -48 };

Vec3i TTYD64_sam_Vector3D_80230670 = { -35, 0, -52 };

Vec3i TTYD64_sam_Vector3D_8023079C = { -35, 0, -52 };

Vec3i TTYD64_sam_Vector3D_8023067C = { -20, 0, -50 };

Vec3i TTYD64_sam_Vector3D_80230688 = { -17, 0, -40 };

Vec3i TTYD64_sam_Vector3D_80230730 = { -20, 0, -50 };

Vec3i TTYD64_sam_Vector3D_802306AC = { -35, 0, -52 };

Vec3i TTYD64_sam_Vector3D_8023073C = { -17, 0, -40 };

Vec3i TTYD64_sam_Vector3D_802307D8 = { -35, 0, -52 };

Vec3i TTYD64_sam_Vector3D_802306B8 = { -20, 0, -50 };

Vec3i TTYD64_sam_Vector3D_80230748 = { -7, 0, -48 };

Vec3i TTYD64_sam_Vector3D_802306C4 = { -17, 0, -40 };

Vec3i TTYD64_sam_Vector3D_802307E4 = { -20, 0, -50 };

Vec3i TTYD64_sam_Vector3D_802307F0 = { -17, 0, -40 };

Vec3i TTYD64_sam_Vector3D_802306D0 = { -7, 0, -48 };

Vec3i TTYD64_sam_Vector3D_80230760 = { -35, 0, -52 };

Vec3i TTYD64_sam_Vector3D_802307FC = { -7, 0, -48 };

Vec3i TTYD64_sam_Vector3D_8023076C = { -20, 0, -50 };

Vec3i TTYD64_sam_Vector3D_802306E8 = { -35, 0, -52 };

Vec3i TTYD64_sam_Vector3D_80230814 = { -35, 0, -52 };

Vec3i TTYD64_sam_Vector3D_80230700 = { -17, 0, -40 };

Vec3i TTYD64_sam_Vector3D_80230820 = { -20, 0, -50 };

Vec3i TTYD64_sam_Vector3D_8023082C = { -17, 0, -40 };

Vec3i TTYD64_sam_Vector3D_8023070C = { -7, 0, -48 };

Vec3i TTYD64_sam_Vector3D_802307A8 = { -20, 0, -50 };

Vec3i TTYD64_sam_Vector3D_802307B4 = { -17, 0, -40 };

Vec3i TTYD64_sam_Vector3D_80230724 = { -35, 0, -52 };

Vec3i TTYD64_sam_Vector3D_802307C0 = { -7, 0, -48 };

void TTYD64_InstallBattles_sam(void) {
    Mod_SetBattleList("TTYD64", 0x1D, TTYD64_sam_FormationTable);
}
