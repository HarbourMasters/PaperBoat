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
API_CALLABLE(action_command_whirlwind_init);
API_CALLABLE(action_command_whirlwind_start);
API_CALLABLE(b_area_flo2_flo_03_CosInterpMinMax);
API_CALLABLE(b_area_flo2_huff_n_puff_Atan2);
API_CALLABLE(b_area_flo2_huff_n_puff_CosInterpMinMax);
API_CALLABLE(b_area_flo2_huff_n_puff_FindPlaceForTuffPuff);
API_CALLABLE(b_area_flo2_huff_n_puff_HuffPuffBreath);
API_CALLABLE(b_area_flo2_huff_n_puff_MakeSnakingStatic);
API_CALLABLE(b_area_flo2_huff_n_puff_SetBackgroundAlpha);
API_CALLABLE(b_area_flo2_huff_n_puff_SetSnakingStaticPos);
API_CALLABLE(b_area_flo2_huff_n_puff_SetTuffPuffPos);
API_CALLABLE(b_area_flo2_huff_n_puff_StartRumbleWithParams);
API_CALLABLE(b_area_flo2_huff_n_puff_UnkBackgroundFunc3);
API_CALLABLE(b_area_flo2_huff_n_puff_UpdateLerp);
API_CALLABLE(b_area_flo2_tuff_puff_CosInterpMinMax);
extern Stage b_area_flo2_flo_01;
extern Stage b_area_flo2_flo_01b;
extern Stage b_area_flo2_flo_01c;
extern Stage b_area_flo2_flo_02;
extern Stage b_area_flo2_flo_02b;
extern Stage b_area_flo2_flo_02c;
extern EvtScript b_area_flo2_flo_03_EVS_PostBattle;
extern s32 b_area_flo2_flo_03_ForegroundVineModels[];
extern EvtScript b_area_flo2_flo_03_MakeSun;
extern u8 b_area_flo2_flo_03_VineModels[];
extern Stage b_area_flo2_flo_04;
extern Stage b_area_flo2_flo_05;
extern Stage b_area_flo2_flo_06;
extern s32 b_area_flo2_huff_n_puff_ChargedArmAnims[];
extern s32 b_area_flo2_huff_n_puff_ChargedBodyAnims[];
extern s32 b_area_flo2_huff_n_puff_ChargedFaceAnims[];
extern s32 b_area_flo2_huff_n_puff_DefenseTable[];
extern s32 b_area_flo2_huff_n_puff_DummyAnims[];
extern EvtScript b_area_flo2_huff_n_puff_EVS_Dialogue_Concerned;
extern EvtScript b_area_flo2_huff_n_puff_EVS_Dialogue_FullPower;
extern EvtScript b_area_flo2_huff_n_puff_EVS_Dialogue_PummelPermission;
extern EvtScript b_area_flo2_huff_n_puff_EVS_HandlePhase;
extern EvtScript b_area_flo2_huff_n_puff_EVS_HuffNPuff_BurnDeath;
extern EvtScript b_area_flo2_huff_n_puff_EVS_HuffNPuff_Death;
extern EvtScript b_area_flo2_huff_n_puff_EVS_HuffNPuff_NoDamage;
extern EvtScript b_area_flo2_huff_n_puff_EVS_IncreaseWobble;
extern EvtScript b_area_flo2_huff_n_puff_EVS_RuffPuff_Inhale;
extern EvtScript b_area_flo2_huff_n_puff_EVS_UpdateChargedJitter;
extern EvtScript b_area_flo2_huff_n_puff_EVS_UpdateSize;
extern u8 b_area_flo2_huff_n_puff_RuffPuffDataBuffer[];
extern s32 b_area_flo2_huff_n_puff_StatusTable[];
extern Vec3i b_area_flo2_huff_n_puff_SummonPos;
extern Vec3i b_area_flo2_huff_n_puff_pos;
extern s32 b_area_flo2_monty_mole_boss_DefenseTable[];
extern EvtScript b_area_flo2_monty_mole_boss_EVS_HandleEvent;
extern EvtScript b_area_flo2_monty_mole_boss_EVS_Idle;
extern s32 b_area_flo2_monty_mole_boss_RockAnims[];
extern s32 b_area_flo2_spike_DefenseTable[];
extern EvtScript b_area_flo2_spike_EVS_HandleEvent;
extern EvtScript b_area_flo2_spike_EVS_Idle;
extern EvtScript b_area_flo2_spike_EVS_ReturnHome;
extern s32 b_area_flo2_spike_SpinyBallAnims[];
extern s32 b_area_flo2_spike_StatusTable[];
extern s32 b_area_flo2_tuff_puff_DefenseTable[];
extern EvtScript b_area_flo2_tuff_puff_EVS_HandleEvent;
extern EvtScript b_area_flo2_tuff_puff_EVS_HandlePhase;
extern EvtScript b_area_flo2_tuff_puff_EVS_TakeTurn;
extern s32 b_area_flo2_tuff_puff_StatusTable[];
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_TuffPuffSwarm_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_GroupBodySlam_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_HurricaneBreath_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_LargeThunderstorm_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_HealOrSlam_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_BodySlam_19;
extern EvtScript TTYD64_imp_19_Spike_Script_80231FBC_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_Thunderstorm_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_ShedTuffPuffs_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_GroupBodySlam_Everyonefalls;
extern EvtScript TTYD64_imp_19_MontyMole_Script_TakeTurn_802311BC_19;
extern EvtScript TTYD64_flo2_Script_BeforeBattle_802349B8;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_TakeTurn_8021D2B8_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_80228004_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_HandleEvent_8021BA6C_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_ChargeLargeThunder_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_ChargeThunder_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_Init_8022F780_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_Idle_8021A0E4_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_Idle_8022FA10_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_8021B2C0_19;
extern EvtScript TTYD64_flo2_Script_802347B8;
extern EvtScript TTYD64_flo2_Script_802345A0;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_8021AD3C_19;
extern EvtScript TTYD64_imp_19_HuffNPuff_Script_Init_80219BC4_19;
extern s32 TTYD64_imp_19_MontyMole_StatusTable_8023066C_19[];
extern ActorPartBlueprint TTYD64_imp_19_HuffNPuff_PartsTable_80219B0C_19[];
extern Battle TTYD64_flo2_FormationTable[];
extern FormationRow TTYD64_flo2_Formation_04[];
extern ActorPartBlueprint TTYD64_imp_19_MontyMole_PartsTable_80230718_19[];
extern EvtScript TTYD64_imp_19_MontyMole_Script_Init_802309C0_19;
extern s32 TTYD64_imp_19_HuffNPuff_IdleAnimations_802198F0_19[];
extern s32 TTYD64_imp_19_HuffNPuff_IdleAnimations_8021994C_19[];
extern s32 TTYD64_imp_19_HuffNPuff_IdleAnimations_8022F580_19[];
extern s32 TTYD64_imp_19_HuffNPuff_IdleAnimations_8022F5DC_19[];
extern s32 TTYD64_imp_19_HuffNPuff_IdleAnimations_802199A8_19[];
extern StageListRow TTYD64_flo2_StageTable[];
extern FormationRow TTYD64_flo2_Formation_03[];
extern EvtScript TTYD64_imp_19_Spike_Script_Init_80231990_19;
extern s32 TTYD64_imp_19_Spike_IdleAnimations_80231810_19[];
extern s32 TTYD64_imp_19_MontyMole_IdleAnimations_802307AC_19[];
extern ActorPartBlueprint TTYD64_imp_19_Spike_PartsTable_80231920_19[];
extern ActorPartBlueprint TTYD64_imp_19_HuffNPuff_PartsTable_8022F710_19[];
extern FormationRow TTYD64_flo2_Formation_02[];
extern Stage TTYD64_flo2_Stage_80234FAC;
extern ActorBlueprint TTYD64_imp_19_Spike_19_Spike;
extern ActorBlueprint TTYD64_imp_19_MontyMole_19_MontyMole;
extern ActorBlueprint TTYD64_imp_19_HuffNPuff_19_HuffNPuff;
extern ActorBlueprint TTYD64_imp_19_HuffNPuff_TuffPuff_19;
extern FormationRow TTYD64_imp_19_HuffNPuff_SpecialFormation_8021A354_19[];
extern FormationRow TTYD64_flo2_Formation_00[];
extern FormationRow TTYD64_flo2_Formation_01[];
extern FormationRow TTYD64_flo2_Formation_05[];
extern EvtScript TTYD64_imp_19_Spike_Script_TakeTurn_802329E4_19;
extern FormationRow TTYD64_imp_19_HuffNPuff_SpecialFormation_8021A370_19[];
API_CALLABLE(TTYD64_imp_19_HuffNPuff_Function_802185D4_19);

API_CALLABLE(TTYD64_imp_19_HuffNPuff_Function_802185D4_19) {
    s32* actorID = &script->owner1.actorID;
    TTYD64_imp_19_HuffNPuff_SpecialFormation_8021A354_19[0].priority = get_actor(*actorID)->turnPriority;
    TTYD64_imp_19_HuffNPuff_SpecialFormation_8021A370_19[0].priority = get_actor(*actorID)->turnPriority;
    return ApiStatus_DONE2;
}

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_TuffPuffSwarm_19 = {
    UseArray(Ref(b_area_flo2_huff_n_puff_RuffPuffDataBuffer))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfFlag(LVar0, 16)
        Thread
            Call(GetActorPos, ArrayVar(4), LVar1, LVar2, LVar3)
            Add(LVar2, 15)
            Call(SetGoalPos, ArrayVar(4), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(4), 20, 0, 0)
            Wait(3)
        EndThread
    EndIf
    IfFlag(LVar0, 512)
        Thread
            Call(GetActorPos, ArrayVar(9), LVar1, LVar2, LVar3)
            Add(LVar2, 15)
            Call(SetGoalPos, ArrayVar(9), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(9), 20, 0, 0)
            Wait(3)
        EndThread
    EndIf
    IfFlag(LVar0, 8)
        Thread
            Call(GetActorPos, ArrayVar(3), LVar1, LVar2, LVar3)
            Add(LVar2, 15)
            Call(SetGoalPos, ArrayVar(3), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(3), 20, 0, 0)
            Wait(3)
        EndThread
    EndIf
    IfFlag(LVar0, 32)
        Thread
            Call(GetActorPos, ArrayVar(5), LVar1, LVar2, LVar3)
            Add(LVar2, 15)
            Call(SetGoalPos, ArrayVar(5), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(5), 20, 0, 0)
            Wait(3)
        EndThread
    EndIf
    IfFlag(LVar0, 2)
        Thread
            Call(GetActorPos, ArrayVar(1), LVar1, LVar2, LVar3)
            Add(LVar2, 15)
            Call(SetGoalPos, ArrayVar(1), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(1), 20, 0, 0)
            Wait(3)
        EndThread
    EndIf
    IfFlag(LVar0, 1)
        Thread
            Call(GetActorPos, ArrayVar(0), LVar1, LVar2, LVar3)
            Add(LVar2, 15)
            Call(SetGoalPos, ArrayVar(0), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(0), 20, 0, 0)
            Wait(3)
        EndThread
    EndIf
    IfFlag(LVar0, 256)
        Thread
            Call(GetActorPos, ArrayVar(8), LVar1, LVar2, LVar3)
            Add(LVar2, 15)
            Call(SetGoalPos, ArrayVar(8), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(8), 20, 0, 0)
            Wait(3)
        EndThread
    EndIf
    IfFlag(LVar0, 4)
        Thread
            Call(GetActorPos, ArrayVar(2), LVar1, LVar2, LVar3)
            Add(LVar2, 15)
            Call(SetGoalPos, ArrayVar(2), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(2), 20, 0, 0)
            Wait(3)
        EndThread
    EndIf
    IfFlag(LVar0, 128)
        Thread
            Call(GetActorPos, ArrayVar(7), LVar1, LVar2, LVar3)
            Add(LVar2, 15)
            Call(SetGoalPos, ArrayVar(7), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(7), 20, 0, 0)
            Wait(3)
        EndThread
    EndIf
    IfFlag(LVar0, 64)
        Thread
            Call(GetActorPos, ArrayVar(6), LVar1, LVar2, LVar3)
            Add(LVar2, 15)
            Call(SetGoalPos, ArrayVar(6), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(6), 20, 0, 0)
            Wait(3)
        EndThread
    EndIf
    Wait(20)
    Set(LVarA, 0)
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfFlag(LVar0, 1)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 2)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 4)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 8)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 16)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 32)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 64)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 128)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 256)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 512)
        Add(LVarA, 1)
    EndIf
    SetF(LVarB, Float(360.0))
    DivF(LVarB, LVarA)
    Thread
        Wait(10)
        Call(UseBattleCamPreset, 19)
        Call(GetOwnerTarget, LVar3, 0)
        Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 300)
        Call(SetBattleCamOffsetY, 35)
        Call(MoveBattleCamOver, 60)
    EndThread
    Set(LVarA, 0)
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfFlag(LVar0, 16)
        Call(UseIdleAnimation, ArrayVar(4), 0)
        Call(SetPartAlpha, ArrayVar(4), 1, 254)
        Call(GetActorVar, ArrayVar(4), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(4), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(4), 1, 0x4C000B)
        EndIf
        Thread
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar1, LVar2, LVar3)
            MulF(LVarB, LVarA)
            AddF(LVarB, Float(100.0))
            Call(AddVectorPolar, LVar1, LVar3, Float(20.0), LVarB)
            Call(RandInt, 20, LVar4)
            Sub(LVar4, 10)
            Add(LVar4, 19)
            Add(LVar2, LVar4)
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(4), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(4), 982)
            EndIf
            Call(SetGoalPos, ArrayVar(4), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(4), 30, -10, 11)
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar4, LVar5, LVar6)
            IfLt(LVar1, LVar4)
                Call(SetActorYaw, ArrayVar(4), 180)
            EndIf
        EndThread
        Add(LVarA, 1)
        Wait(4)
    EndIf
    IfFlag(LVar0, 512)
        Call(UseIdleAnimation, ArrayVar(9), 0)
        Call(SetPartAlpha, ArrayVar(9), 1, 254)
        Call(GetActorVar, ArrayVar(9), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(9), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(9), 1, 0x4C000B)
        EndIf
        Thread
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar1, LVar2, LVar3)
            MulF(LVarB, LVarA)
            AddF(LVarB, Float(100.0))
            Call(AddVectorPolar, LVar1, LVar3, Float(20.0), LVarB)
            Call(RandInt, 20, LVar4)
            Sub(LVar4, 10)
            Add(LVar4, 19)
            Add(LVar2, LVar4)
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(9), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(9), 982)
            EndIf
            Call(SetGoalPos, ArrayVar(9), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(9), 30, -10, 11)
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar4, LVar5, LVar6)
            IfLt(LVar1, LVar4)
                Call(SetActorYaw, ArrayVar(9), 180)
            EndIf
        EndThread
        Add(LVarA, 1)
        Wait(4)
    EndIf
    IfFlag(LVar0, 8)
        Call(UseIdleAnimation, ArrayVar(3), 0)
        Call(SetPartAlpha, ArrayVar(3), 1, 254)
        Call(GetActorVar, ArrayVar(3), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(3), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(3), 1, 0x4C000B)
        EndIf
        Thread
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar1, LVar2, LVar3)
            MulF(LVarB, LVarA)
            AddF(LVarB, Float(100.0))
            Call(AddVectorPolar, LVar1, LVar3, Float(20.0), LVarB)
            Call(RandInt, 20, LVar4)
            Sub(LVar4, 10)
            Add(LVar4, 19)
            Add(LVar2, LVar4)
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(3), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(3), 982)
            EndIf
            Call(SetGoalPos, ArrayVar(3), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(3), 30, -10, 11)
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar4, LVar5, LVar6)
            IfLt(LVar1, LVar4)
                Call(SetActorYaw, ArrayVar(3), 180)
            EndIf
        EndThread
        Add(LVarA, 1)
        Wait(4)
    EndIf
    IfFlag(LVar0, 32)
        Call(UseIdleAnimation, ArrayVar(5), 0)
        Call(SetPartAlpha, ArrayVar(5), 1, 254)
        Call(GetActorVar, ArrayVar(5), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(5), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(5), 1, 0x4C000B)
        EndIf
        Thread
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar1, LVar2, LVar3)
            MulF(LVarB, LVarA)
            AddF(LVarB, Float(100.0))
            Call(AddVectorPolar, LVar1, LVar3, Float(20.0), LVarB)
            Call(RandInt, 20, LVar4)
            Sub(LVar4, 10)
            Add(LVar4, 19)
            Add(LVar2, LVar4)
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(5), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(5), 982)
            EndIf
            Call(SetGoalPos, ArrayVar(5), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(5), 30, -10, 11)
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar4, LVar5, LVar6)
            IfLt(LVar1, LVar4)
                Call(SetActorYaw, ArrayVar(5), 180)
            EndIf
        EndThread
        Add(LVarA, 1)
        Wait(4)
    EndIf
    IfFlag(LVar0, 2)
        Call(UseIdleAnimation, ArrayVar(1), 0)
        Call(SetPartAlpha, ArrayVar(1), 1, 254)
        Call(GetActorVar, ArrayVar(1), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(1), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(1), 1, 0x4C000B)
        EndIf
        Thread
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar1, LVar2, LVar3)
            MulF(LVarB, LVarA)
            AddF(LVarB, Float(100.0))
            Call(AddVectorPolar, LVar1, LVar3, Float(20.0), LVarB)
            Call(RandInt, 20, LVar4)
            Sub(LVar4, 10)
            Add(LVar4, 19)
            Add(LVar2, LVar4)
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(1), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(1), 982)
            EndIf
            Call(SetGoalPos, ArrayVar(1), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(1), 30, -10, 11)
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar4, LVar5, LVar6)
            IfLt(LVar1, LVar4)
                Call(SetActorYaw, ArrayVar(1), 180)
            EndIf
        EndThread
        Add(LVarA, 1)
        Wait(4)
    EndIf
    IfFlag(LVar0, 1)
        Call(UseIdleAnimation, ArrayVar(0), 0)
        Call(SetPartAlpha, ArrayVar(0), 1, 254)
        Call(GetActorVar, ArrayVar(0), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(0), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(0), 1, 0x4C000B)
        EndIf
        Thread
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar1, LVar2, LVar3)
            MulF(LVarB, LVarA)
            AddF(LVarB, Float(100.0))
            Call(AddVectorPolar, LVar1, LVar3, Float(20.0), LVarB)
            Call(RandInt, 20, LVar4)
            Sub(LVar4, 10)
            Add(LVar4, 19)
            Add(LVar2, LVar4)
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(0), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(0), 982)
            EndIf
            Call(SetGoalPos, ArrayVar(0), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(0), 30, -10, 11)
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar4, LVar5, LVar6)
            IfLt(LVar1, LVar4)
                Call(SetActorYaw, ArrayVar(0), 180)
            EndIf
        EndThread
        Add(LVarA, 1)
        Wait(4)
    EndIf
    IfFlag(LVar0, 256)
        Call(UseIdleAnimation, ArrayVar(8), 0)
        Call(SetPartAlpha, ArrayVar(8), 1, 254)
        Call(GetActorVar, ArrayVar(8), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(8), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(8), 1, 0x4C000B)
        EndIf
        Thread
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar1, LVar2, LVar3)
            MulF(LVarB, LVarA)
            AddF(LVarB, Float(100.0))
            Call(AddVectorPolar, LVar1, LVar3, Float(20.0), LVarB)
            Call(RandInt, 20, LVar4)
            Sub(LVar4, 10)
            Add(LVar4, 19)
            Add(LVar2, LVar4)
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(8), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(8), 982)
            EndIf
            Call(SetGoalPos, ArrayVar(8), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(8), 30, -10, 11)
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar4, LVar5, LVar6)
            IfLt(LVar1, LVar4)
                Call(SetActorYaw, ArrayVar(8), 180)
            EndIf
        EndThread
        Add(LVarA, 1)
        Wait(4)
    EndIf
    IfFlag(LVar0, 4)
        Call(UseIdleAnimation, ArrayVar(2), 0)
        Call(SetPartAlpha, ArrayVar(2), 1, 254)
        Call(GetActorVar, ArrayVar(2), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(2), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(2), 1, 0x4C000B)
        EndIf
        Thread
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar1, LVar2, LVar3)
            MulF(LVarB, LVarA)
            AddF(LVarB, Float(100.0))
            Call(AddVectorPolar, LVar1, LVar3, Float(20.0), LVarB)
            Call(RandInt, 20, LVar4)
            Sub(LVar4, 10)
            Add(LVar4, 19)
            Add(LVar2, LVar4)
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(2), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(2), 982)
            EndIf
            Call(SetGoalPos, ArrayVar(2), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(2), 30, -10, 11)
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar4, LVar5, LVar6)
            IfLt(LVar1, LVar4)
                Call(SetActorYaw, ArrayVar(2), 180)
            EndIf
        EndThread
        Add(LVarA, 1)
        Wait(4)
    EndIf
    IfFlag(LVar0, 128)
        Call(UseIdleAnimation, ArrayVar(7), 0)
        Call(SetPartAlpha, ArrayVar(7), 1, 254)
        Call(GetActorVar, ArrayVar(7), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(7), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(7), 1, 0x4C000B)
        EndIf
        Thread
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar1, LVar2, LVar3)
            MulF(LVarB, LVarA)
            AddF(LVarB, Float(100.0))
            Call(AddVectorPolar, LVar1, LVar3, Float(20.0), LVarB)
            Call(RandInt, 20, LVar4)
            Sub(LVar4, 10)
            Add(LVar4, 19)
            Add(LVar2, LVar4)
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(7), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(7), 982)
            EndIf
            Call(SetGoalPos, ArrayVar(7), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(7), 30, -10, 11)
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar4, LVar5, LVar6)
            IfLt(LVar1, LVar4)
                Call(SetActorYaw, ArrayVar(7), 180)
            EndIf
        EndThread
        Add(LVarA, 1)
        Wait(4)
    EndIf
    IfFlag(LVar0, 64)
        Call(UseIdleAnimation, ArrayVar(6), 0)
        Call(SetPartAlpha, ArrayVar(6), 1, 254)
        Call(GetActorVar, ArrayVar(6), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(6), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(6), 1, 0x4C000B)
        EndIf
        Thread
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar1, LVar2, LVar3)
            MulF(LVarB, LVarA)
            AddF(LVarB, Float(100.0))
            Call(AddVectorPolar, LVar1, LVar3, Float(20.0), LVarB)
            Call(RandInt, 20, LVar4)
            Sub(LVar4, 10)
            Add(LVar4, 19)
            Add(LVar2, LVar4)
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(6), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(6), 982)
            EndIf
            Call(SetGoalPos, ArrayVar(6), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(6), 30, -10, 11)
            Call(GetOwnerTarget, LVar8, 0)
            Call(GetActorPos, LVar8, LVar4, LVar5, LVar6)
            IfLt(LVar1, LVar4)
                Call(SetActorYaw, ArrayVar(6), 180)
            EndIf
        EndThread
        Add(LVarA, 1)
        Wait(4)
    EndIf
    Wait(30)
    Call(UseBattleCamPreset, 1)
    Set(LVar9, 0)
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfFlag(LVar0, 1)
        Add(LVar9, 1)
    EndIf
    IfFlag(LVar0, 2)
        Add(LVar9, 1)
    EndIf
    IfFlag(LVar0, 4)
        Add(LVar9, 1)
    EndIf
    IfFlag(LVar0, 8)
        Add(LVar9, 1)
    EndIf
    IfFlag(LVar0, 16)
        Add(LVar9, 1)
    EndIf
    IfFlag(LVar0, 32)
        Add(LVar9, 1)
    EndIf
    IfFlag(LVar0, 64)
        Add(LVar9, 1)
    EndIf
    IfFlag(LVar0, 128)
        Add(LVar9, 1)
    EndIf
    IfFlag(LVar0, 256)
        Add(LVar9, 1)
    EndIf
    IfFlag(LVar0, 512)
        Add(LVar9, 1)
    EndIf
    Set(LVarA, 30)
    Sub(LVarA, LVar9)
    Set(LVar3, 0)
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfFlag(LVar0, 1)
        Set(LVar1, ArrayVar(0))
        Set(LVar2, LVarA)
        ExecGetTID(TTYD64_imp_19_HuffNPuff_Script_80228004_19, ArrayVar(10))
        Add(LVar3, 1)
    EndIf
    IfFlag(LVar0, 2)
        Set(LVar1, ArrayVar(1))
        Set(LVar2, LVarA)
        ExecGetTID(TTYD64_imp_19_HuffNPuff_Script_80228004_19, ArrayVar(11))
        Add(LVar3, 1)
    EndIf
    IfFlag(LVar0, 4)
        Set(LVar1, ArrayVar(2))
        Set(LVar2, LVarA)
        ExecGetTID(TTYD64_imp_19_HuffNPuff_Script_80228004_19, ArrayVar(12))
        Add(LVar3, 1)
    EndIf
    IfFlag(LVar0, 8)
        Set(LVar1, ArrayVar(3))
        Set(LVar2, LVarA)
        ExecGetTID(TTYD64_imp_19_HuffNPuff_Script_80228004_19, ArrayVar(13))
        Add(LVar3, 1)
    EndIf
    IfFlag(LVar0, 16)
        Set(LVar1, ArrayVar(4))
        Set(LVar2, LVarA)
        ExecGetTID(TTYD64_imp_19_HuffNPuff_Script_80228004_19, ArrayVar(14))
        Add(LVar3, 1)
    EndIf
    IfFlag(LVar0, 32)
        Set(LVar1, ArrayVar(5))
        Set(LVar2, LVarA)
        ExecGetTID(TTYD64_imp_19_HuffNPuff_Script_80228004_19, ArrayVar(15))
        Add(LVar3, 1)
    EndIf
    IfFlag(LVar0, 64)
        Set(LVar1, ArrayVar(6))
        Set(LVar2, LVarA)
        ExecGetTID(TTYD64_imp_19_HuffNPuff_Script_80228004_19, ArrayVar(16))
        Add(LVar3, 1)
    EndIf
    IfFlag(LVar0, 128)
        Set(LVar1, ArrayVar(7))
        Set(LVar2, LVarA)
        ExecGetTID(TTYD64_imp_19_HuffNPuff_Script_80228004_19, ArrayVar(17))
        Add(LVar3, 1)
    EndIf
    IfFlag(LVar0, 256)
        Set(LVar1, ArrayVar(8))
        Set(LVar2, LVarA)
        ExecGetTID(TTYD64_imp_19_HuffNPuff_Script_80228004_19, ArrayVar(18))
        Add(LVar3, 1)
    EndIf
    IfFlag(LVar0, 512)
        Set(LVar1, ArrayVar(9))
        Set(LVar2, LVarA)
        ExecGetTID(TTYD64_imp_19_HuffNPuff_Script_80228004_19, ArrayVar(19))
        Add(LVar3, 1)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Label(0)
            Call(GetActorVar, 512, 0, LVar0)
            IfNotFlag(LVar0, 4)
                Wait(1)
                Goto(0)
            EndIf
            Call(GetActorVar, 512, 0, LVar0)
            BitwiseAndConst(LVar0, -5)
            Call(SetActorVar, 512, 0, LVar0)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfFlag(LVar0, 1)
                KillThread(ArrayVar(10))
                Call(GetActorVar, ArrayVar(0), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(0), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(0), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(0), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(0), Float(1.0))
                    Call(SetGoalPos, ArrayVar(0), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(0), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 2)
                KillThread(ArrayVar(11))
                Call(GetActorVar, ArrayVar(1), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(1), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(1), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(1), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(1), Float(1.0))
                    Call(SetGoalPos, ArrayVar(1), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(1), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 4)
                KillThread(ArrayVar(12))
                Call(GetActorVar, ArrayVar(2), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(2), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(2), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(2), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(2), Float(1.0))
                    Call(SetGoalPos, ArrayVar(2), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(2), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 8)
                KillThread(ArrayVar(13))
                Call(GetActorVar, ArrayVar(3), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(3), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(3), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(3), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(3), Float(1.0))
                    Call(SetGoalPos, ArrayVar(3), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(3), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 16)
                KillThread(ArrayVar(14))
                Call(GetActorVar, ArrayVar(4), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(4), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(4), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(4), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(4), Float(1.0))
                    Call(SetGoalPos, ArrayVar(4), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(4), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 32)
                KillThread(ArrayVar(15))
                Call(GetActorVar, ArrayVar(5), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(5), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(5), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(5), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(5), Float(1.0))
                    Call(SetGoalPos, ArrayVar(5), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(5), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 64)
                KillThread(ArrayVar(16))
                Call(GetActorVar, ArrayVar(6), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(6), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(6), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(6), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(6), Float(1.0))
                    Call(SetGoalPos, ArrayVar(6), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(6), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 128)
                KillThread(ArrayVar(17))
                Call(GetActorVar, ArrayVar(7), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(7), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(7), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(7), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(7), Float(1.0))
                    Call(SetGoalPos, ArrayVar(7), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(7), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 256)
                KillThread(ArrayVar(18))
                Call(GetActorVar, ArrayVar(8), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(8), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(8), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(8), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(8), Float(1.0))
                    Call(SetGoalPos, ArrayVar(8), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(8), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 512)
                KillThread(ArrayVar(19))
                Call(GetActorVar, ArrayVar(9), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(9), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(9), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(9), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(9), Float(1.0))
                    Call(SetGoalPos, ArrayVar(9), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(9), 20, 0, 0, 0)
                EndThread
            EndIf
            Wait(15)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(20)
            Set(LVarA, 0)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfFlag(LVar0, 16)
                Call(GetActorVar, ArrayVar(4), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(4), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(4), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(4), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(4), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(4), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(4))
                    Call(FlyToGoal, ArrayVar(4), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(4), 1, 255)
                    Call(SetActorYaw, ArrayVar(4), 0)
                    Call(GetActorVar, ArrayVar(4), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(4), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(4), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 512)
                Call(GetActorVar, ArrayVar(9), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(9), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(9), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(9), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(9), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(9), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(9))
                    Call(FlyToGoal, ArrayVar(9), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(9), 1, 255)
                    Call(SetActorYaw, ArrayVar(9), 0)
                    Call(GetActorVar, ArrayVar(9), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(9), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(9), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 8)
                Call(GetActorVar, ArrayVar(3), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(3), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(3), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(3), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(3), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(3), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(3))
                    Call(FlyToGoal, ArrayVar(3), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(3), 1, 255)
                    Call(SetActorYaw, ArrayVar(3), 0)
                    Call(GetActorVar, ArrayVar(3), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(3), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(3), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 32)
                Call(GetActorVar, ArrayVar(5), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(5), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(5), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(5), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(5), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(5), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(5))
                    Call(FlyToGoal, ArrayVar(5), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(5), 1, 255)
                    Call(SetActorYaw, ArrayVar(5), 0)
                    Call(GetActorVar, ArrayVar(5), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(5), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(5), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 2)
                Call(GetActorVar, ArrayVar(1), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(1), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(1), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(1), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(1), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(1), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(1))
                    Call(FlyToGoal, ArrayVar(1), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(1), 1, 255)
                    Call(SetActorYaw, ArrayVar(1), 0)
                    Call(GetActorVar, ArrayVar(1), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(1), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(1), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 1)
                Call(GetActorVar, ArrayVar(0), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(0), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(0), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(0), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(0), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(0), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(0))
                    Call(FlyToGoal, ArrayVar(0), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(0), 1, 255)
                    Call(SetActorYaw, ArrayVar(0), 0)
                    Call(GetActorVar, ArrayVar(0), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(0), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(0), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 256)
                Call(GetActorVar, ArrayVar(8), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(8), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(8), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(8), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(8), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(8), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(8))
                    Call(FlyToGoal, ArrayVar(8), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(8), 1, 255)
                    Call(SetActorYaw, ArrayVar(8), 0)
                    Call(GetActorVar, ArrayVar(8), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(8), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(8), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 4)
                Call(GetActorVar, ArrayVar(2), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(2), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(2), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(2), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(2), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(2), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(2))
                    Call(FlyToGoal, ArrayVar(2), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(2), 1, 255)
                    Call(SetActorYaw, ArrayVar(2), 0)
                    Call(GetActorVar, ArrayVar(2), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(2), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(2), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 128)
                Call(GetActorVar, ArrayVar(7), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(7), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(7), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(7), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(7), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(7), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(7))
                    Call(FlyToGoal, ArrayVar(7), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(7), 1, 255)
                    Call(SetActorYaw, ArrayVar(7), 0)
                    Call(GetActorVar, ArrayVar(7), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(7), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(7), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 64)
                Call(GetActorVar, ArrayVar(6), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(6), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(6), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(6), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(6), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(6), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(6))
                    Call(FlyToGoal, ArrayVar(6), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(6), 1, 255)
                    Call(SetActorYaw, ArrayVar(6), 0)
                    Call(GetActorVar, ArrayVar(6), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(6), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(6), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            Wait(50)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetStatusFlags, LVar3, LVar1)
    IfFlag(LVar1, 0x100000)
        Wait(10)
        Set(LVar3, 0)
        Loop(0)
            Call(GetActorVar, 512, 0, LVar0)
            IfFlag(LVar0, 4)
                Call(GetActorVar, 512, 0, LVar0)
                BitwiseAndConst(LVar0, -5)
                Call(SetActorVar, 512, 0, LVar0)
                Wait(2)
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(EnemyDamageTarget, ACTOR_SELF, LVarA, 0x18000000, 0, 0, 1, 64)
                Add(LVar3, 1)
            EndIf
            IfGt(LVar3, 1)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    Else
        Call(ShowMessageBox, 49, 180)
        Call(ShowActionHud, 1)
        Call(LoadActionCommand, 6)
        Call(action_command_stop_leech_init)
        Call(SetupMashMeter, 1, 25, 0, 0, 0, 0)
        Wait(10)
        Call(SetBattleFlagBits, 0x4000, 0)
        Call(action_command_stop_leech_start, 0, 0x7FFF, 3)
        Set(LVarB, LVarA)
        Div(LVarB, 2)
        Wait(LVarB)
        Set(LVarD, 0)
        Loop(0)
            Call(GetActorVar, 512, 0, LVar0)
            IfFlag(LVar0, 4)
                Call(GetActorVar, 512, 0, LVar0)
                BitwiseAndConst(LVar0, -5)
                Call(SetActorVar, 512, 0, LVar0)
                Wait(2)
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(EnemyDamageTarget, ACTOR_SELF, LVarA, 0x1A000000, 0, 0, 2, 32)
                Add(LVarD, 1)
            EndIf
            Call(GetMashActionQuality, LVar0)
            IfEq(LVar0, 1)
                BreakLoop
            EndIf
            Call(GetOwnerTarget, LVar1, 0)
            Call(GetLastDamage, LVar1, LVar0)
            IfEq(LVar0, 0)
                IfGt(LVarD, 1)
                    Call(InterruptLeechActionCommand)
                    BreakLoop
                EndIf
            EndIf
            Call(GetOwnerTarget, LVar1, 0)
            IfEq(LVar1, 0)
                Call(GetPlayerHP, LVar0)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar0)
            EndIf
            IfEq(LVar0, 0)
                Call(InterruptLeechActionCommand)
                BreakLoop
            EndIf
            IfGe(LVarD, 20)
                Call(InterruptLeechActionCommand)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Call(InterruptLeechActionCommand)
    EndIf
    Switch(LVarA)
        CaseOrEq(0)
        CaseOrEq(1)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfFlag(LVar0, 1)
                KillThread(ArrayVar(10))
                Call(GetActorVar, ArrayVar(0), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(0), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(0), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(0), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(0), Float(1.0))
                    Call(SetGoalPos, ArrayVar(0), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(0), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 2)
                KillThread(ArrayVar(11))
                Call(GetActorVar, ArrayVar(1), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(1), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(1), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(1), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(1), Float(1.0))
                    Call(SetGoalPos, ArrayVar(1), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(1), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 4)
                KillThread(ArrayVar(12))
                Call(GetActorVar, ArrayVar(2), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(2), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(2), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(2), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(2), Float(1.0))
                    Call(SetGoalPos, ArrayVar(2), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(2), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 8)
                KillThread(ArrayVar(13))
                Call(GetActorVar, ArrayVar(3), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(3), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(3), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(3), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(3), Float(1.0))
                    Call(SetGoalPos, ArrayVar(3), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(3), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 16)
                KillThread(ArrayVar(14))
                Call(GetActorVar, ArrayVar(4), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(4), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(4), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(4), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(4), Float(1.0))
                    Call(SetGoalPos, ArrayVar(4), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(4), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 32)
                KillThread(ArrayVar(15))
                Call(GetActorVar, ArrayVar(5), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(5), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(5), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(5), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(5), Float(1.0))
                    Call(SetGoalPos, ArrayVar(5), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(5), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 64)
                KillThread(ArrayVar(16))
                Call(GetActorVar, ArrayVar(6), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(6), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(6), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(6), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(6), Float(1.0))
                    Call(SetGoalPos, ArrayVar(6), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(6), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 128)
                KillThread(ArrayVar(17))
                Call(GetActorVar, ArrayVar(7), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(7), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(7), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(7), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(7), Float(1.0))
                    Call(SetGoalPos, ArrayVar(7), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(7), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 256)
                KillThread(ArrayVar(18))
                Call(GetActorVar, ArrayVar(8), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(8), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(8), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(8), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(8), Float(1.0))
                    Call(SetGoalPos, ArrayVar(8), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(8), 20, 0, 0, 0)
                EndThread
            EndIf
            IfFlag(LVar0, 512)
                KillThread(ArrayVar(19))
                Call(GetActorVar, ArrayVar(9), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(9), 1, 0x4C0012)
                Else
                    Call(SetAnimation, ArrayVar(9), 1, 0x4C0013)
                EndIf
                Thread
                    Call(GetOwnerTarget, LVar3, 0)
                    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                    Call(GetActorPos, ArrayVar(9), LVar3, LVar4, LVar5)
                    Call(b_area_flo2_huff_n_puff_Atan2, LVar6, LVar0, LVar2, LVar3, LVar5)
                    DivF(LVar6, Float(2.0))
                    AddF(LVar6, Float(90.0))
                    Call(AddVectorPolar, LVar0, LVar1, Float(70.0), LVar6)
                    Call(SetActorJumpGravity, ArrayVar(9), Float(1.0))
                    Call(SetGoalPos, ArrayVar(9), LVar0, LVar1, LVar2)
                    Call(JumpToGoal, ArrayVar(9), 20, 0, 0, 0)
                EndThread
            EndIf
            Call(GetOwnerTarget, LVar7, 0)
            IfEq(LVar7, 0)
                Call(GetPlayerHP, LVar0)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar0)
            EndIf
            IfNe(LVar0, 0)
                Call(UseIdleAnimation, LVar7, 0)
                Wait(1)
                Call(GetStatusFlags, LVar7, LVar0)
                IfNotFlag(LVar0, 0x100000)
                    Thread
                        Set(LVar0, 0)
                        Loop(20)
                            Add(LVar0, 54)
                            Mod(LVar0, 360)
                            Call(SetActorYaw, LVar7, LVar0)
                            Wait(1)
                        EndLoop
                        Call(SetActorYaw, LVar7, 0)
                    EndThread
                    Call(SetActorJumpGravity, LVar7, Float(1.5))
                    Call(GetActorPos, LVar7, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, LVar7, LVar0, LVar1, LVar2)
                    IfEq(LVar7, 0)
                        Call(SetJumpAnimations, 0, 0, 0x10007, 0x10007, 0x10009)
                        Call(PlayerHopToGoal, 15, 0, 0)
                    Else
                        Set(LVar0, 9)
                        Exec(TTYD64_SetPartnerAnimation_Battle)
                        Call(SetActorDispOffset, LVar7, 0, 0, 0)
                        Call(JumpToGoal, LVar7, 15, 0, 0, 1)
                        Set(LVar0, 0)
                        Exec(TTYD64_SetPartnerAnimation_Battle)
                    EndIf
                Else
                    Wait(20)
                EndIf
                Call(UseIdleAnimation, LVar7, 1)
            Else
                Wait(20)
            EndIf
            Wait(15)
            Set(LVarA, 0)
            Call(GetActorVar, ACTOR_SELF, 2, LVar0)
            IfFlag(LVar0, 16)
                Call(GetActorVar, ArrayVar(4), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(4), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(4), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(4), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(4), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(4), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(4))
                    Call(FlyToGoal, ArrayVar(4), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(4), 1, 255)
                    Call(SetActorYaw, ArrayVar(4), 0)
                    Call(GetActorVar, ArrayVar(4), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(4), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(4), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 512)
                Call(GetActorVar, ArrayVar(9), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(9), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(9), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(9), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(9), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(9), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(9))
                    Call(FlyToGoal, ArrayVar(9), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(9), 1, 255)
                    Call(SetActorYaw, ArrayVar(9), 0)
                    Call(GetActorVar, ArrayVar(9), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(9), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(9), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 8)
                Call(GetActorVar, ArrayVar(3), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(3), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(3), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(3), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(3), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(3), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(3))
                    Call(FlyToGoal, ArrayVar(3), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(3), 1, 255)
                    Call(SetActorYaw, ArrayVar(3), 0)
                    Call(GetActorVar, ArrayVar(3), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(3), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(3), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 32)
                Call(GetActorVar, ArrayVar(5), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(5), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(5), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(5), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(5), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(5), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(5))
                    Call(FlyToGoal, ArrayVar(5), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(5), 1, 255)
                    Call(SetActorYaw, ArrayVar(5), 0)
                    Call(GetActorVar, ArrayVar(5), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(5), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(5), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 2)
                Call(GetActorVar, ArrayVar(1), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(1), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(1), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(1), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(1), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(1), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(1))
                    Call(FlyToGoal, ArrayVar(1), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(1), 1, 255)
                    Call(SetActorYaw, ArrayVar(1), 0)
                    Call(GetActorVar, ArrayVar(1), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(1), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(1), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 1)
                Call(GetActorVar, ArrayVar(0), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(0), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(0), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(0), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(0), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(0), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(0))
                    Call(FlyToGoal, ArrayVar(0), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(0), 1, 255)
                    Call(SetActorYaw, ArrayVar(0), 0)
                    Call(GetActorVar, ArrayVar(0), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(0), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(0), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 256)
                Call(GetActorVar, ArrayVar(8), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(8), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(8), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(8), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(8), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(8), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(8))
                    Call(FlyToGoal, ArrayVar(8), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(8), 1, 255)
                    Call(SetActorYaw, ArrayVar(8), 0)
                    Call(GetActorVar, ArrayVar(8), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(8), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(8), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 4)
                Call(GetActorVar, ArrayVar(2), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(2), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(2), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(2), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(2), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(2), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(2))
                    Call(FlyToGoal, ArrayVar(2), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(2), 1, 255)
                    Call(SetActorYaw, ArrayVar(2), 0)
                    Call(GetActorVar, ArrayVar(2), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(2), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(2), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 128)
                Call(GetActorVar, ArrayVar(7), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(7), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(7), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(7), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(7), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(7), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(7))
                    Call(FlyToGoal, ArrayVar(7), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(7), 1, 255)
                    Call(SetActorYaw, ArrayVar(7), 0)
                    Call(GetActorVar, ArrayVar(7), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(7), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(7), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            IfFlag(LVar0, 64)
                Call(GetActorVar, ArrayVar(6), 0, LVar1)
                IfEq(LVar1, 0)
                    Call(SetAnimation, ArrayVar(6), 1, 0x4C0006)
                Else
                    Call(SetAnimation, ArrayVar(6), 1, 0x4C0007)
                EndIf
                Thread
                    Call(SetActorVar, ArrayVar(6), 2, 0)
                    Mod(LVarA, 2)
                    IfEq(LVarA, 0)
                        Call(PlaySoundAtActor, ArrayVar(6), 981)
                    Else
                        Call(PlaySoundAtActor, ArrayVar(6), 982)
                    EndIf
                    Call(SetGoalToHome, ArrayVar(6))
                    Call(FlyToGoal, ArrayVar(6), 30, 10, 11)
                    Call(SetPartAlpha, ArrayVar(6), 1, 255)
                    Call(SetActorYaw, ArrayVar(6), 0)
                    Call(GetActorVar, ArrayVar(6), 0, LVar1)
                    IfEq(LVar1, 0)
                        Call(SetAnimation, ArrayVar(6), 1, 0x4C0002)
                    Else
                        Call(SetAnimation, ArrayVar(6), 1, 0x4C0003)
                    EndIf
                EndThread
                Add(LVarA, 1)
                Wait(4)
            EndIf
            Wait(50)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_GroupBodySlam_19 = {
    UseArray(Ref(b_area_flo2_huff_n_puff_RuffPuffDataBuffer))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 400)
    Call(SetBattleCamOffsetY, 5)
    Call(MoveBattleCamOver, 30)
    Wait(30)
    Call(PlaySoundAtActor, ACTOR_SELF, 947)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7C001A)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7C001B)
    Call(SetAnimation, ACTOR_SELF, 3, 0x7C001C)
    Wait(8)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7C001D)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7C001E)
    Call(SetAnimation, ACTOR_SELF, 3, 0x7C001F)
    Call(PlaySoundAtActor, ACTOR_SELF, 8374)
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    Call(GetActorVar, ACTOR_SELF, 7, LVar1)
    Set(LVarF, 0)
    Loop(20)
        Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.2998046875), 10, 0, 0)
        Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.7001953125), 10, 0, 0)
        MulF(LVar2, LVar0)
        MulF(LVar3, LVar1)
        Call(SetActorVar, ACTOR_SELF, 6, LVar2)
        Call(SetActorVar, ACTOR_SELF, 7, LVar3)
        Add(LVarF, 1)
        Wait(1)
    EndLoop
    Call(PlaySoundAtActor, ACTOR_SELF, 8374)
    Loop(20)
        Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.2001953125), 10, 0, 0)
        Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.7998046875), 10, 0, 0)
        MulF(LVar2, LVar0)
        MulF(LVar3, LVar1)
        Call(SetActorVar, ACTOR_SELF, 6, LVar2)
        Call(SetActorVar, ACTOR_SELF, 7, LVar3)
        Add(LVarF, 1)
        Wait(1)
    EndLoop
    Call(SetActorVar, ACTOR_SELF, 6, LVar0)
    Call(SetActorVar, ACTOR_SELF, 7, LVar1)
    Set(LVar9, 0)
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Add(LVarB, 150)
    IfFlag(LVar0, 16)
        Call(UseIdleAnimation, ArrayVar(4), 0)
        Call(GetActorVar, ArrayVar(4), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(4), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(4), 1, 0x4C000B)
        EndIf
        Thread
            Mod(LVar9, 2)
            IfEq(LVar9, 0)
                Call(PlaySoundAtActor, ArrayVar(4), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(4), 982)
            EndIf
            Call(GetActorPos, ArrayVar(4), LVarD, LVarE, LVarF)
            Call(SetGoalPos, ArrayVar(4), LVarA, LVarB, LVarF)
            Call(FlyToGoal, ArrayVar(4), 20, 10, 1)
            Set(LVarD, LVarA)
            Set(LVarE, LVarC)
            Set(LVarF, 4)
            Mul(LVarF, 36)
            Add(LVarF, -90)
            Call(AddVectorPolar, LVarD, LVarE, Float(60.0), LVarF)
            Call(SetActorPos, ArrayVar(4), LVarD, LVarB, LVarE)
        EndThread
        Add(LVar9, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 512)
        Call(UseIdleAnimation, ArrayVar(9), 0)
        Call(GetActorVar, ArrayVar(9), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(9), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(9), 1, 0x4C000B)
        EndIf
        Thread
            Mod(LVar9, 2)
            IfEq(LVar9, 0)
                Call(PlaySoundAtActor, ArrayVar(9), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(9), 982)
            EndIf
            Call(GetActorPos, ArrayVar(9), LVarD, LVarE, LVarF)
            Call(SetGoalPos, ArrayVar(9), LVarA, LVarB, LVarF)
            Call(FlyToGoal, ArrayVar(9), 20, 10, 1)
            Set(LVarD, LVarA)
            Set(LVarE, LVarC)
            Set(LVarF, 9)
            Mul(LVarF, 36)
            Add(LVarF, -90)
            Call(AddVectorPolar, LVarD, LVarE, Float(60.0), LVarF)
            Call(SetActorPos, ArrayVar(9), LVarD, LVarB, LVarE)
        EndThread
        Add(LVar9, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 8)
        Call(UseIdleAnimation, ArrayVar(3), 0)
        Call(GetActorVar, ArrayVar(3), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(3), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(3), 1, 0x4C000B)
        EndIf
        Thread
            Mod(LVar9, 2)
            IfEq(LVar9, 0)
                Call(PlaySoundAtActor, ArrayVar(3), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(3), 982)
            EndIf
            Call(GetActorPos, ArrayVar(3), LVarD, LVarE, LVarF)
            Call(SetGoalPos, ArrayVar(3), LVarA, LVarB, LVarF)
            Call(FlyToGoal, ArrayVar(3), 20, 10, 1)
            Set(LVarD, LVarA)
            Set(LVarE, LVarC)
            Set(LVarF, 3)
            Mul(LVarF, 36)
            Add(LVarF, -90)
            Call(AddVectorPolar, LVarD, LVarE, Float(60.0), LVarF)
            Call(SetActorPos, ArrayVar(3), LVarD, LVarB, LVarE)
        EndThread
        Add(LVar9, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 32)
        Call(UseIdleAnimation, ArrayVar(5), 0)
        Call(GetActorVar, ArrayVar(5), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(5), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(5), 1, 0x4C000B)
        EndIf
        Thread
            Mod(LVar9, 2)
            IfEq(LVar9, 0)
                Call(PlaySoundAtActor, ArrayVar(5), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(5), 982)
            EndIf
            Call(GetActorPos, ArrayVar(5), LVarD, LVarE, LVarF)
            Call(SetGoalPos, ArrayVar(5), LVarA, LVarB, LVarF)
            Call(FlyToGoal, ArrayVar(5), 20, 10, 1)
            Set(LVarD, LVarA)
            Set(LVarE, LVarC)
            Set(LVarF, 5)
            Mul(LVarF, 36)
            Add(LVarF, -90)
            Call(AddVectorPolar, LVarD, LVarE, Float(60.0), LVarF)
            Call(SetActorPos, ArrayVar(5), LVarD, LVarB, LVarE)
        EndThread
        Add(LVar9, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 2)
        Call(UseIdleAnimation, ArrayVar(1), 0)
        Call(GetActorVar, ArrayVar(1), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(1), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(1), 1, 0x4C000B)
        EndIf
        Thread
            Mod(LVar9, 2)
            IfEq(LVar9, 0)
                Call(PlaySoundAtActor, ArrayVar(1), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(1), 982)
            EndIf
            Call(GetActorPos, ArrayVar(1), LVarD, LVarE, LVarF)
            Call(SetGoalPos, ArrayVar(1), LVarA, LVarB, LVarF)
            Call(FlyToGoal, ArrayVar(1), 20, 10, 1)
            Set(LVarD, LVarA)
            Set(LVarE, LVarC)
            Set(LVarF, 1)
            Mul(LVarF, 36)
            Add(LVarF, -90)
            Call(AddVectorPolar, LVarD, LVarE, Float(60.0), LVarF)
            Call(SetActorPos, ArrayVar(1), LVarD, LVarB, LVarE)
        EndThread
        Add(LVar9, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 1)
        Call(UseIdleAnimation, ArrayVar(0), 0)
        Call(GetActorVar, ArrayVar(0), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(0), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(0), 1, 0x4C000B)
        EndIf
        Thread
            Mod(LVar9, 2)
            IfEq(LVar9, 0)
                Call(PlaySoundAtActor, ArrayVar(0), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(0), 982)
            EndIf
            Call(GetActorPos, ArrayVar(0), LVarD, LVarE, LVarF)
            Call(SetGoalPos, ArrayVar(0), LVarA, LVarB, LVarF)
            Call(FlyToGoal, ArrayVar(0), 20, 10, 1)
            Set(LVarD, LVarA)
            Set(LVarE, LVarC)
            Set(LVarF, 0)
            Mul(LVarF, 36)
            Add(LVarF, -90)
            Call(AddVectorPolar, LVarD, LVarE, Float(60.0), LVarF)
            Call(SetActorPos, ArrayVar(0), LVarD, LVarB, LVarE)
        EndThread
        Add(LVar9, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 256)
        Call(UseIdleAnimation, ArrayVar(8), 0)
        Call(GetActorVar, ArrayVar(8), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(8), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(8), 1, 0x4C000B)
        EndIf
        Thread
            Mod(LVar9, 2)
            IfEq(LVar9, 0)
                Call(PlaySoundAtActor, ArrayVar(8), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(8), 982)
            EndIf
            Call(GetActorPos, ArrayVar(8), LVarD, LVarE, LVarF)
            Call(SetGoalPos, ArrayVar(8), LVarA, LVarB, LVarF)
            Call(FlyToGoal, ArrayVar(8), 20, 10, 1)
            Set(LVarD, LVarA)
            Set(LVarE, LVarC)
            Set(LVarF, 8)
            Mul(LVarF, 36)
            Add(LVarF, -90)
            Call(AddVectorPolar, LVarD, LVarE, Float(60.0), LVarF)
            Call(SetActorPos, ArrayVar(8), LVarD, LVarB, LVarE)
        EndThread
        Add(LVar9, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 4)
        Call(UseIdleAnimation, ArrayVar(2), 0)
        Call(GetActorVar, ArrayVar(2), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(2), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(2), 1, 0x4C000B)
        EndIf
        Thread
            Mod(LVar9, 2)
            IfEq(LVar9, 0)
                Call(PlaySoundAtActor, ArrayVar(2), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(2), 982)
            EndIf
            Call(GetActorPos, ArrayVar(2), LVarD, LVarE, LVarF)
            Call(SetGoalPos, ArrayVar(2), LVarA, LVarB, LVarF)
            Call(FlyToGoal, ArrayVar(2), 20, 10, 1)
            Set(LVarD, LVarA)
            Set(LVarE, LVarC)
            Set(LVarF, 2)
            Mul(LVarF, 36)
            Add(LVarF, -90)
            Call(AddVectorPolar, LVarD, LVarE, Float(60.0), LVarF)
            Call(SetActorPos, ArrayVar(2), LVarD, LVarB, LVarE)
        EndThread
        Add(LVar9, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 128)
        Call(UseIdleAnimation, ArrayVar(7), 0)
        Call(GetActorVar, ArrayVar(7), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(7), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(7), 1, 0x4C000B)
        EndIf
        Thread
            Mod(LVar9, 2)
            IfEq(LVar9, 0)
                Call(PlaySoundAtActor, ArrayVar(7), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(7), 982)
            EndIf
            Call(GetActorPos, ArrayVar(7), LVarD, LVarE, LVarF)
            Call(SetGoalPos, ArrayVar(7), LVarA, LVarB, LVarF)
            Call(FlyToGoal, ArrayVar(7), 20, 10, 1)
            Set(LVarD, LVarA)
            Set(LVarE, LVarC)
            Set(LVarF, 7)
            Mul(LVarF, 36)
            Add(LVarF, -90)
            Call(AddVectorPolar, LVarD, LVarE, Float(60.0), LVarF)
            Call(SetActorPos, ArrayVar(7), LVarD, LVarB, LVarE)
        EndThread
        Add(LVar9, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 64)
        Call(UseIdleAnimation, ArrayVar(6), 0)
        Call(GetActorVar, ArrayVar(6), 0, LVar1)
        IfEq(LVar1, 0)
            Call(SetAnimation, ArrayVar(6), 1, 0x4C0009)
        Else
            Call(SetAnimation, ArrayVar(6), 1, 0x4C000B)
        EndIf
        Thread
            Mod(LVar9, 2)
            IfEq(LVar9, 0)
                Call(PlaySoundAtActor, ArrayVar(6), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(6), 982)
            EndIf
            Call(GetActorPos, ArrayVar(6), LVarD, LVarE, LVarF)
            Call(SetGoalPos, ArrayVar(6), LVarA, LVarB, LVarF)
            Call(FlyToGoal, ArrayVar(6), 20, 10, 1)
            Set(LVarD, LVarA)
            Set(LVarE, LVarC)
            Set(LVarF, 6)
            Mul(LVarF, 36)
            Add(LVarF, -90)
            Call(AddVectorPolar, LVarD, LVarE, Float(60.0), LVarF)
            Call(SetActorPos, ArrayVar(6), LVarD, LVarB, LVarE)
        EndThread
        Add(LVar9, 1)
        Wait(8)
    EndIf
    Wait(20)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Call(FlyToGoal, ACTOR_SELF, 30, 10, 1)
    Wait(75)
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfFlag(LVar0, 1)
        Thread
            Call(GetActorPos, ArrayVar(0), LVar1, LVar2, LVar3)
            Call(GetActorVar, ArrayVar(0), 0, LVar4)
            IfEq(LVar4, 0)
                Set(LVar2, 10)
            Else
                Set(LVar2, 14)
            EndIf
            Call(SetActorSounds, ArrayVar(0), 1, 0, 0)
            Call(SetGoalPos, ArrayVar(0), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(0), 20, 0, 2)
            Call(ResetActorSounds, ArrayVar(0), 1)
        EndThread
    EndIf
    IfFlag(LVar0, 2)
        Thread
            Call(GetActorPos, ArrayVar(1), LVar1, LVar2, LVar3)
            Call(GetActorVar, ArrayVar(1), 0, LVar4)
            IfEq(LVar4, 0)
                Set(LVar2, 10)
            Else
                Set(LVar2, 14)
            EndIf
            Call(SetActorSounds, ArrayVar(1), 1, 0, 0)
            Call(SetGoalPos, ArrayVar(1), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(1), 20, 0, 2)
            Call(ResetActorSounds, ArrayVar(1), 1)
        EndThread
    EndIf
    IfFlag(LVar0, 4)
        Thread
            Call(GetActorPos, ArrayVar(2), LVar1, LVar2, LVar3)
            Call(GetActorVar, ArrayVar(2), 0, LVar4)
            IfEq(LVar4, 0)
                Set(LVar2, 10)
            Else
                Set(LVar2, 14)
            EndIf
            Call(SetActorSounds, ArrayVar(2), 1, 0, 0)
            Call(SetGoalPos, ArrayVar(2), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(2), 20, 0, 2)
            Call(ResetActorSounds, ArrayVar(2), 1)
        EndThread
    EndIf
    IfFlag(LVar0, 8)
        Thread
            Call(GetActorPos, ArrayVar(3), LVar1, LVar2, LVar3)
            Call(GetActorVar, ArrayVar(3), 0, LVar4)
            IfEq(LVar4, 0)
                Set(LVar2, 10)
            Else
                Set(LVar2, 14)
            EndIf
            Call(SetActorSounds, ArrayVar(3), 1, 0, 0)
            Call(SetGoalPos, ArrayVar(3), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(3), 20, 0, 2)
            Call(ResetActorSounds, ArrayVar(3), 1)
        EndThread
    EndIf
    IfFlag(LVar0, 16)
        Thread
            Call(GetActorPos, ArrayVar(4), LVar1, LVar2, LVar3)
            Call(GetActorVar, ArrayVar(4), 0, LVar4)
            IfEq(LVar4, 0)
                Set(LVar2, 10)
            Else
                Set(LVar2, 14)
            EndIf
            Call(SetActorSounds, ArrayVar(4), 1, 0, 0)
            Call(SetGoalPos, ArrayVar(4), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(4), 20, 0, 2)
            Call(ResetActorSounds, ArrayVar(4), 1)
        EndThread
    EndIf
    IfFlag(LVar0, 32)
        Thread
            Call(GetActorPos, ArrayVar(5), LVar1, LVar2, LVar3)
            Call(GetActorVar, ArrayVar(5), 0, LVar4)
            IfEq(LVar4, 0)
                Set(LVar2, 10)
            Else
                Set(LVar2, 14)
            EndIf
            Call(SetActorSounds, ArrayVar(5), 1, 0, 0)
            Call(SetGoalPos, ArrayVar(5), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(5), 20, 0, 2)
            Call(ResetActorSounds, ArrayVar(5), 1)
        EndThread
    EndIf
    IfFlag(LVar0, 64)
        Thread
            Call(GetActorPos, ArrayVar(6), LVar1, LVar2, LVar3)
            Call(GetActorVar, ArrayVar(6), 0, LVar4)
            IfEq(LVar4, 0)
                Set(LVar2, 10)
            Else
                Set(LVar2, 14)
            EndIf
            Call(SetActorSounds, ArrayVar(6), 1, 0, 0)
            Call(SetGoalPos, ArrayVar(6), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(6), 20, 0, 2)
            Call(ResetActorSounds, ArrayVar(6), 1)
        EndThread
    EndIf
    IfFlag(LVar0, 128)
        Thread
            Call(GetActorPos, ArrayVar(7), LVar1, LVar2, LVar3)
            Call(GetActorVar, ArrayVar(7), 0, LVar4)
            IfEq(LVar4, 0)
                Set(LVar2, 10)
            Else
                Set(LVar2, 14)
            EndIf
            Call(SetActorSounds, ArrayVar(7), 1, 0, 0)
            Call(SetGoalPos, ArrayVar(7), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(7), 20, 0, 2)
            Call(ResetActorSounds, ArrayVar(7), 1)
        EndThread
    EndIf
    IfFlag(LVar0, 256)
        Thread
            Call(GetActorPos, ArrayVar(8), LVar1, LVar2, LVar3)
            Call(GetActorVar, ArrayVar(8), 0, LVar4)
            IfEq(LVar4, 0)
                Set(LVar2, 10)
            Else
                Set(LVar2, 14)
            EndIf
            Call(SetActorSounds, ArrayVar(8), 1, 0, 0)
            Call(SetGoalPos, ArrayVar(8), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(8), 20, 0, 2)
            Call(ResetActorSounds, ArrayVar(8), 1)
        EndThread
    EndIf
    IfFlag(LVar0, 512)
        Thread
            Call(GetActorPos, ArrayVar(9), LVar1, LVar2, LVar3)
            Call(GetActorVar, ArrayVar(9), 0, LVar4)
            IfEq(LVar4, 0)
                Set(LVar2, 10)
            Else
                Set(LVar2, 14)
            EndIf
            Call(SetActorSounds, ArrayVar(9), 1, 0, 0)
            Call(SetGoalPos, ArrayVar(9), LVar1, LVar2, LVar3)
            Call(FlyToGoal, ArrayVar(9), 20, 0, 2)
            Call(ResetActorSounds, ArrayVar(9), 1)
        EndThread
    EndIf
    Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
    Thread
        Wait(3)
        Call(PlaySoundAtActor, ACTOR_SELF, 8425)
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Call(GetActorVar, ACTOR_SELF, 7, LVar4)
    Mul(LVar4, 95)
    Div(LVar4, 200)
    Call(SetGoalPos, ACTOR_SELF, LVar1, LVar4, LVar3)
    Call(FlyToGoal, ACTOR_SELF, 20, 0, 2)
    Call(ResetActorSounds, ACTOR_SELF, 1)
    Call(PlaySoundAtActor, ACTOR_SELF, 8426)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(PlayEffect_impl, 37, 3, LVar0, 0, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Thread
        Call(PlayEffect_impl, 29, 1, LVar1, LVar4, LVar3, 60, 8, 0, 30, 0, 0, 0, 0, 0)
        Wait(2)
        Call(PlayEffect_impl, 29, 1, LVar1, LVar4, LVar3, 60, 8, 33, 30, 0, 0, 0, 0, 0)
        Wait(2)
        Call(PlayEffect_impl, 29, 1, LVar1, LVar4, LVar3, 60, 8, 66, 30, 0, 0, 0, 0, 0)
    EndThread
    Thread
        Call(ShakeCam, 1, 0, 20, Float(1.0))
    EndThread
    Thread
        Call(GetActorVar, ACTOR_SELF, 6, LVar0)
        Call(GetActorVar, ACTOR_SELF, 7, LVar1)
        Set(LVarF, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 8375)
        Loop(20)
            Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.5), 10, 0, 0)
            Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.5), 10, 0, 0)
            MulF(LVar2, LVar0)
            MulF(LVar3, LVar1)
            Call(SetActorVar, ACTOR_SELF, 6, LVar2)
            Call(SetActorVar, ACTOR_SELF, 7, LVar3)
            Add(LVarF, 1)
            Wait(1)
        EndLoop
        Call(PlaySoundAtActor, ACTOR_SELF, 8375)
        Loop(20)
            Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.2001953125), 10, 0, 0)
            Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.7998046875), 10, 0, 0)
            MulF(LVar2, LVar0)
            MulF(LVar3, LVar1)
            Call(SetActorVar, ACTOR_SELF, 6, LVar2)
            Call(SetActorVar, ACTOR_SELF, 7, LVar3)
            Add(LVarF, 1)
            Wait(1)
        EndLoop
        Call(SetActorVar, ACTOR_SELF, 6, LVar0)
        Call(SetActorVar, ACTOR_SELF, 7, LVar1)
    EndThread
    Thread
        Loop(40)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetActorVar, ACTOR_SELF, 7, LVar3)
            Mul(LVar3, 95)
            Div(LVar3, 200)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar3, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfFlag(LVar0, 1)
        Thread
            Call(GetActorVar, ArrayVar(0), 3, LVar0)
            Call(GetActorVar, ArrayVar(0), 4, LVar1)
            Set(LVarF, 0)
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.5), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.5), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(0), 3, LVar2)
                Call(SetActorVar, ArrayVar(0), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.2001953125), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.7998046875), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(0), 3, LVar2)
                Call(SetActorVar, ArrayVar(0), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Call(SetActorVar, ArrayVar(0), 3, LVar0)
            Call(SetActorVar, ArrayVar(0), 4, LVar1)
        EndThread
        Thread
            Loop(40)
                Call(GetActorPos, ArrayVar(0), LVar0, LVar1, LVar2)
                Call(GetActorVar, ArrayVar(0), 4, LVar3)
                Call(GetActorVar, ArrayVar(0), 0, LVar4)
                IfEq(LVar4, 0)
                    Mul(LVar3, 20)
                Else
                    Mul(LVar3, 28)
                EndIf
                Div(LVar3, 200)
                Call(SetActorPos, ArrayVar(0), LVar0, LVar3, LVar2)
                Wait(1)
            EndLoop
        EndThread
    EndIf
    IfFlag(LVar0, 2)
        Thread
            Call(GetActorVar, ArrayVar(1), 3, LVar0)
            Call(GetActorVar, ArrayVar(1), 4, LVar1)
            Set(LVarF, 0)
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.5), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.5), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(1), 3, LVar2)
                Call(SetActorVar, ArrayVar(1), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.2001953125), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.7998046875), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(1), 3, LVar2)
                Call(SetActorVar, ArrayVar(1), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Call(SetActorVar, ArrayVar(1), 3, LVar0)
            Call(SetActorVar, ArrayVar(1), 4, LVar1)
        EndThread
        Thread
            Loop(40)
                Call(GetActorPos, ArrayVar(1), LVar0, LVar1, LVar2)
                Call(GetActorVar, ArrayVar(1), 4, LVar3)
                Call(GetActorVar, ArrayVar(1), 0, LVar4)
                IfEq(LVar4, 0)
                    Mul(LVar3, 20)
                Else
                    Mul(LVar3, 28)
                EndIf
                Div(LVar3, 200)
                Call(SetActorPos, ArrayVar(1), LVar0, LVar3, LVar2)
                Wait(1)
            EndLoop
        EndThread
    EndIf
    IfFlag(LVar0, 4)
        Thread
            Call(GetActorVar, ArrayVar(2), 3, LVar0)
            Call(GetActorVar, ArrayVar(2), 4, LVar1)
            Set(LVarF, 0)
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.5), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.5), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(2), 3, LVar2)
                Call(SetActorVar, ArrayVar(2), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.2001953125), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.7998046875), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(2), 3, LVar2)
                Call(SetActorVar, ArrayVar(2), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Call(SetActorVar, ArrayVar(2), 3, LVar0)
            Call(SetActorVar, ArrayVar(2), 4, LVar1)
        EndThread
        Thread
            Loop(40)
                Call(GetActorPos, ArrayVar(2), LVar0, LVar1, LVar2)
                Call(GetActorVar, ArrayVar(2), 4, LVar3)
                Call(GetActorVar, ArrayVar(2), 0, LVar4)
                IfEq(LVar4, 0)
                    Mul(LVar3, 20)
                Else
                    Mul(LVar3, 28)
                EndIf
                Div(LVar3, 200)
                Call(SetActorPos, ArrayVar(2), LVar0, LVar3, LVar2)
                Wait(1)
            EndLoop
        EndThread
    EndIf
    IfFlag(LVar0, 8)
        Thread
            Call(GetActorVar, ArrayVar(3), 3, LVar0)
            Call(GetActorVar, ArrayVar(3), 4, LVar1)
            Set(LVarF, 0)
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.5), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.5), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(3), 3, LVar2)
                Call(SetActorVar, ArrayVar(3), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.2001953125), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.7998046875), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(3), 3, LVar2)
                Call(SetActorVar, ArrayVar(3), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Call(SetActorVar, ArrayVar(3), 3, LVar0)
            Call(SetActorVar, ArrayVar(3), 4, LVar1)
        EndThread
        Thread
            Loop(40)
                Call(GetActorPos, ArrayVar(3), LVar0, LVar1, LVar2)
                Call(GetActorVar, ArrayVar(3), 4, LVar3)
                Call(GetActorVar, ArrayVar(3), 0, LVar4)
                IfEq(LVar4, 0)
                    Mul(LVar3, 20)
                Else
                    Mul(LVar3, 28)
                EndIf
                Div(LVar3, 200)
                Call(SetActorPos, ArrayVar(3), LVar0, LVar3, LVar2)
                Wait(1)
            EndLoop
        EndThread
    EndIf
    IfFlag(LVar0, 16)
        Thread
            Call(GetActorVar, ArrayVar(4), 3, LVar0)
            Call(GetActorVar, ArrayVar(4), 4, LVar1)
            Set(LVarF, 0)
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.5), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.5), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(4), 3, LVar2)
                Call(SetActorVar, ArrayVar(4), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.2001953125), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.7998046875), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(4), 3, LVar2)
                Call(SetActorVar, ArrayVar(4), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Call(SetActorVar, ArrayVar(4), 3, LVar0)
            Call(SetActorVar, ArrayVar(4), 4, LVar1)
        EndThread
        Thread
            Loop(40)
                Call(GetActorPos, ArrayVar(4), LVar0, LVar1, LVar2)
                Call(GetActorVar, ArrayVar(4), 4, LVar3)
                Call(GetActorVar, ArrayVar(4), 0, LVar4)
                IfEq(LVar4, 0)
                    Mul(LVar3, 20)
                Else
                    Mul(LVar3, 28)
                EndIf
                Div(LVar3, 200)
                Call(SetActorPos, ArrayVar(4), LVar0, LVar3, LVar2)
                Wait(1)
            EndLoop
        EndThread
    EndIf
    IfFlag(LVar0, 32)
        Thread
            Call(GetActorVar, ArrayVar(5), 3, LVar0)
            Call(GetActorVar, ArrayVar(5), 4, LVar1)
            Set(LVarF, 0)
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.5), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.5), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(5), 3, LVar2)
                Call(SetActorVar, ArrayVar(5), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.2001953125), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.7998046875), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(5), 3, LVar2)
                Call(SetActorVar, ArrayVar(5), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Call(SetActorVar, ArrayVar(5), 3, LVar0)
            Call(SetActorVar, ArrayVar(5), 4, LVar1)
        EndThread
        Thread
            Loop(40)
                Call(GetActorPos, ArrayVar(5), LVar0, LVar1, LVar2)
                Call(GetActorVar, ArrayVar(5), 4, LVar3)
                Call(GetActorVar, ArrayVar(5), 0, LVar4)
                IfEq(LVar4, 0)
                    Mul(LVar3, 20)
                Else
                    Mul(LVar3, 28)
                EndIf
                Div(LVar3, 200)
                Call(SetActorPos, ArrayVar(5), LVar0, LVar3, LVar2)
                Wait(1)
            EndLoop
        EndThread
    EndIf
    IfFlag(LVar0, 64)
        Thread
            Call(GetActorVar, ArrayVar(6), 3, LVar0)
            Call(GetActorVar, ArrayVar(6), 4, LVar1)
            Set(LVarF, 0)
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.5), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.5), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(6), 3, LVar2)
                Call(SetActorVar, ArrayVar(6), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.2001953125), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.7998046875), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(6), 3, LVar2)
                Call(SetActorVar, ArrayVar(6), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Call(SetActorVar, ArrayVar(6), 3, LVar0)
            Call(SetActorVar, ArrayVar(6), 4, LVar1)
        EndThread
        Thread
            Loop(40)
                Call(GetActorPos, ArrayVar(6), LVar0, LVar1, LVar2)
                Call(GetActorVar, ArrayVar(6), 4, LVar3)
                Call(GetActorVar, ArrayVar(6), 0, LVar4)
                IfEq(LVar4, 0)
                    Mul(LVar3, 20)
                Else
                    Mul(LVar3, 28)
                EndIf
                Div(LVar3, 200)
                Call(SetActorPos, ArrayVar(6), LVar0, LVar3, LVar2)
                Wait(1)
            EndLoop
        EndThread
    EndIf
    IfFlag(LVar0, 128)
        Thread
            Call(GetActorVar, ArrayVar(7), 3, LVar0)
            Call(GetActorVar, ArrayVar(7), 4, LVar1)
            Set(LVarF, 0)
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.5), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.5), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(7), 3, LVar2)
                Call(SetActorVar, ArrayVar(7), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.2001953125), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.7998046875), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(7), 3, LVar2)
                Call(SetActorVar, ArrayVar(7), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Call(SetActorVar, ArrayVar(7), 3, LVar0)
            Call(SetActorVar, ArrayVar(7), 4, LVar1)
        EndThread
        Thread
            Loop(40)
                Call(GetActorPos, ArrayVar(7), LVar0, LVar1, LVar2)
                Call(GetActorVar, ArrayVar(7), 4, LVar3)
                Call(GetActorVar, ArrayVar(7), 0, LVar4)
                IfEq(LVar4, 0)
                    Mul(LVar3, 20)
                Else
                    Mul(LVar3, 28)
                EndIf
                Div(LVar3, 200)
                Call(SetActorPos, ArrayVar(7), LVar0, LVar3, LVar2)
                Wait(1)
            EndLoop
        EndThread
    EndIf
    IfFlag(LVar0, 256)
        Thread
            Call(GetActorVar, ArrayVar(8), 3, LVar0)
            Call(GetActorVar, ArrayVar(8), 4, LVar1)
            Set(LVarF, 0)
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.5), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.5), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(8), 3, LVar2)
                Call(SetActorVar, ArrayVar(8), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.2001953125), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.7998046875), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(8), 3, LVar2)
                Call(SetActorVar, ArrayVar(8), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Call(SetActorVar, ArrayVar(8), 3, LVar0)
            Call(SetActorVar, ArrayVar(8), 4, LVar1)
        EndThread
        Thread
            Loop(40)
                Call(GetActorPos, ArrayVar(8), LVar0, LVar1, LVar2)
                Call(GetActorVar, ArrayVar(8), 4, LVar3)
                Call(GetActorVar, ArrayVar(8), 0, LVar4)
                IfEq(LVar4, 0)
                    Mul(LVar3, 20)
                Else
                    Mul(LVar3, 28)
                EndIf
                Div(LVar3, 200)
                Call(SetActorPos, ArrayVar(8), LVar0, LVar3, LVar2)
                Wait(1)
            EndLoop
        EndThread
    EndIf
    IfFlag(LVar0, 512)
        Thread
            Call(GetActorVar, ArrayVar(9), 3, LVar0)
            Call(GetActorVar, ArrayVar(9), 4, LVar1)
            Set(LVarF, 0)
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.5), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.5), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(9), 3, LVar2)
                Call(SetActorVar, ArrayVar(9), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Loop(20)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar2, Float(1.0), Float(1.2001953125), 10, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar3, Float(1.0), Float(0.7998046875), 10, 0, 0)
                MulF(LVar2, LVar0)
                MulF(LVar3, LVar1)
                Call(SetActorVar, ArrayVar(9), 3, LVar2)
                Call(SetActorVar, ArrayVar(9), 4, LVar3)
                Add(LVarF, 1)
                Wait(1)
            EndLoop
            Call(SetActorVar, ArrayVar(9), 3, LVar0)
            Call(SetActorVar, ArrayVar(9), 4, LVar1)
        EndThread
        Thread
            Loop(40)
                Call(GetActorPos, ArrayVar(9), LVar0, LVar1, LVar2)
                Call(GetActorVar, ArrayVar(9), 4, LVar3)
                Call(GetActorVar, ArrayVar(9), 0, LVar4)
                IfEq(LVar4, 0)
                    Mul(LVar3, 20)
                Else
                    Mul(LVar3, 28)
                EndIf
                Div(LVar3, 200)
                Call(SetActorPos, ArrayVar(9), LVar0, LVar3, LVar2)
                Wait(1)
            EndLoop
        EndThread
    EndIf
    Set(LVarA, 5)
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfFlag(LVar0, 1)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 2)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 4)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 8)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 16)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 32)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 64)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 128)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 256)
        Add(LVarA, 1)
    EndIf
    IfFlag(LVar0, 512)
        Add(LVarA, 1)
    EndIf
    Wait(2)
    Call(GetOwnerTarget, LVar1, 0)
    IfEq(LVar1, 256)
        Call(GetCurrentPartnerID, LVar0)
        Switch(LVar0)
            CaseOrEq(1)
            CaseOrEq(2)
            CaseOrEq(3)
            CaseOrEq(7)
            EndCaseGroup
            CaseDefault
                Set(LVar0, 6)
                Goto(0)
        EndSwitch
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Label(0)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVar0, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000800, 0, 0, LVarA, 32)
    EndSwitch
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(GetOwnerTarget, LVar1, 0)
    IfEq(LVar1, 256)
        Call(GetCurrentPartnerID, LVar0)
        Switch(LVar0)
            CaseOrEq(1)
            CaseOrEq(2)
            CaseOrEq(3)
            CaseOrEq(7)
            EndCaseGroup
            CaseDefault
                Set(LVar0, 6)
                Goto(1)
        EndSwitch
        IfEq(LVar0, 0)
            Set(LVar0, 6)
            Goto(1)
        EndIf
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Label(1)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVar0, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000800, 0, 0, LVarA, 32)
    EndSwitch
    ExecWait(TTYD64_imp_19_HuffNPuff_Script_GroupBodySlam_Everyonefalls)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_HurricaneBreath_19 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7C001A)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7C001B)
    Call(SetAnimation, ACTOR_SELF, 3, 0x7C001C)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetActorVar, ACTOR_SELF, 6, LVar3)
    Call(GetActorVar, ACTOR_SELF, 7, LVar4)
    MulF(LVar3, Float(-13.0))
    MulF(LVar4, Float(0.0))
    DivF(LVar3, Float(100.0))
    DivF(LVar4, Float(100.0))
    Add(LVar0, LVar3)
    Add(LVar1, LVar4)
    Call(PlayEffect_impl, 110, 1, LVar0, LVar1, LVar2, Float(190.0), Float(-1.0), Float(1.5), 100, 0, 0, 0, 0, 0)
    Call(b_area_flo2_huff_n_puff_StartRumbleWithParams, 80, 150)
    Thread
        Call(ShakeCam, 1, 0, 75, Float(0.2998046875))
    EndThread
    Thread
        Call(GetActorVar, ACTOR_SELF, 6, LVar2)
        Set(LVar3, LVar2)
        Add(LVar3, 25)
        Call(MakeLerp, LVar2, LVar3, 90, 11)
        Label(0)
        Call(UpdateLerp)
        Call(SetActorVar, ACTOR_SELF, 6, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
    EndThread
    Thread
        Call(GetActorVar, ACTOR_SELF, 7, LVar2)
        Set(LVar3, LVar2)
        Add(LVar3, 25)
        Call(MakeLerp, LVar2, LVar3, 90, 11)
        Label(1)
        Call(UpdateLerp)
        Call(SetActorVar, ACTOR_SELF, 7, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(1)
        EndIf
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, 944)
    Thread
        Wait(15)
        Call(PlaySoundAtActor, ACTOR_SELF, 998)
    EndThread
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 20)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 300)
    Call(SetBattleCamOffsetY, 20)
    Call(MoveBattleCamOver, 180)
    Wait(90)
    Call(StopSound, 944)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7C001D)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7C001D)
    Call(SetAnimation, ACTOR_SELF, 3, 0x7C001E)
    Wait(60)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7C0020)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7C0021)
    Call(SetAnimation, ACTOR_SELF, 3, 0x7C0022)
    Call(PlaySoundAtActor, ACTOR_SELF, 861)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 15)
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfLe(LVar0, 0)
        Call(GetStatusFlags, 0, LVar0)
    Else
        Call(GetStatusFlags, 0, LVar0)
        IfFlag(LVar0, 0x100000)
            Call(GetStatusFlags, 256, LVar0)
            IfNotFlag(LVar0, 0x100000)
                Set(LVar0, 0)
            EndIf
        Else
            Set(LVar0, 0)
        EndIf
    EndIf
    IfNotFlag(LVar0, 0x100000)
        Call(ShowMessageBox, 49, 180)
        Call(ShowActionHud, 1)
        Call(LoadActionCommand, 5)
        Call(action_command_whirlwind_init, 0)
        Call(SetupMashMeter, 5, 20, 40, 60, 80, 100)
        Wait(10)
        Call(SetBattleFlagBits, 0x4000, 0)
        Call(action_command_whirlwind_start, 0, 200, 3)
        Thread
            Call(GetActorVar, ACTOR_SELF, 6, LVar2)
            Set(LVar3, LVar2)
            Sub(LVar3, 25)
            Call(MakeLerp, LVar2, LVar3, 200, 2)
            Label(4)
            Call(UpdateLerp)
            Call(SetActorVar, ACTOR_SELF, 6, LVar0)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(4)
            EndIf
        EndThread
        Thread
            Call(GetActorVar, ACTOR_SELF, 7, LVar2)
            Set(LVar3, LVar2)
            Sub(LVar3, 25)
            Call(MakeLerp, LVar2, LVar3, 200, 2)
            Label(5)
            Call(UpdateLerp)
            Call(SetActorVar, ACTOR_SELF, 7, LVar0)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(5)
            EndIf
        EndThread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetActorVar, ACTOR_SELF, 6, LVar3)
        Call(GetActorVar, ACTOR_SELF, 7, LVar4)
        MulF(LVar3, Float(-20.0))
        MulF(LVar4, Float(-20.0))
        DivF(LVar3, Float(100.0))
        DivF(LVar4, Float(100.0))
        Add(LVar0, LVar3)
        Add(LVar1, LVar4)
        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, Float(190.0), Float(1.5), Float(1.0), 200, 0, 0, 0, 0, 0)
        Call(b_area_flo2_huff_n_puff_StartRumbleWithParams, 100, 350)
        Thread
            Call(ShakeCam, 1, 0, 175, Float(0.2998046875))
        EndThread
        Thread
            Loop(25)
                Call(RandInt, 150, LVar3)
                Call(RandInt, 100, LVar4)
                Add(LVar3, 50)
                SetF(LVar4, Float(5.0))
                Call(RandInt, 4, LVar5)
                AddF(LVar4, LVar5)
                DivF(LVar4, Float(10.0))
                SetF(LVar5, Float(100.0))
                Call(RandInt, 40, LVar6)
                AddF(LVar5, LVar6)
                DivF(LVar5, Float(10.0))
                Call(PlayEffect_impl, 116, 0, 200, LVar3, 5, -200, LVar4, 5, LVar5, LVar4, 0, 0, 0, 0)
                Call(RandInt, 5, LVar0)
                Add(LVar0, 5)
                Wait(LVar0)
            EndLoop
        EndThread
        Call(MakeLerp, 0, 7200, 200, 11)
        Label(10)
        Call(UpdateLerp)
        Call(TTYD64_GetPartnerHP_API, LVar2)
        IfGt(LVar2, 0)
            Call(SetActorYaw, 256, LVar0)
        EndIf
        Call(SetActorYaw, 0, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(10)
        EndIf
        Call(GetActionProgress, LVar1)
    Else
        Thread
            Call(GetActorVar, ACTOR_SELF, 6, LVar2)
            Set(LVar3, LVar2)
            Sub(LVar3, 25)
            Call(MakeLerp, LVar2, LVar3, 100, 2)
            Label(6)
            Call(UpdateLerp)
            Call(SetActorVar, ACTOR_SELF, 6, LVar0)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(6)
            EndIf
        EndThread
        Thread
            Call(GetActorVar, ACTOR_SELF, 7, LVar2)
            Set(LVar3, LVar2)
            Sub(LVar3, 25)
            Call(MakeLerp, LVar2, LVar3, 100, 2)
            Label(7)
            Call(UpdateLerp)
            Call(SetActorVar, ACTOR_SELF, 7, LVar0)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(7)
            EndIf
        EndThread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetActorVar, ACTOR_SELF, 6, LVar3)
        Call(GetActorVar, ACTOR_SELF, 7, LVar4)
        MulF(LVar3, Float(-20.0))
        MulF(LVar4, Float(-20.0))
        DivF(LVar3, Float(100.0))
        DivF(LVar4, Float(100.0))
        Add(LVar0, LVar3)
        Add(LVar1, LVar4)
        Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, Float(190.0), Float(1.5), Float(1.0), 100, 0, 0, 0, 0, 0)
        Call(b_area_flo2_huff_n_puff_StartRumbleWithParams, 100, 200)
        Thread
            Call(ShakeCam, 1, 0, 100, Float(0.2998046875))
        EndThread
        Thread
            Loop(15)
                Call(RandInt, 150, LVar3)
                Call(RandInt, 100, LVar4)
                Add(LVar3, 50)
                SetF(LVar4, Float(5.0))
                Call(RandInt, 4, LVar5)
                AddF(LVar4, LVar5)
                DivF(LVar4, Float(10.0))
                SetF(LVar5, Float(100.0))
                Call(RandInt, 40, LVar6)
                AddF(LVar5, LVar6)
                DivF(LVar5, Float(10.0))
                Call(PlayEffect_impl, 116, 0, 200, LVar3, 5, -200, LVar4, 5, LVar5, LVar4, 0, 0, 0, 0)
                Call(RandInt, 5, LVar0)
                Add(LVar0, 5)
                Wait(LVar0)
            EndLoop
        EndThread
        Wait(110)
        Set(LVar1, 0)
    EndIf
    Call(StopSound, 861)
    Wait(2)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0x10000000, 0, 1, 32)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Switch(LVar1)
                CaseEq(0)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 7, 32)
                CaseEq(1)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 6, 32)
                CaseEq(2)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 5, 32)
                CaseEq(3)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 4, 32)
                CaseEq(4)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
                CaseDefault
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 2, 32)
            EndSwitch
    EndSwitch
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0x10000000, 0, 1, 32)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Switch(LVar1)
                CaseEq(0)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 7, 32)
                CaseEq(1)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 6, 32)
                CaseEq(2)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 5, 32)
                CaseEq(3)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 4, 32)
                CaseEq(4)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
                CaseDefault
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 2, 32)
            EndSwitch
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x7C0001)
            Call(SetAnimation, ACTOR_SELF, 2, 0x7C0002)
            Call(SetAnimation, ACTOR_SELF, 3, 0x7C0003)
            Wait(20)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_LargeThunderstorm_19 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(AddBattleCamDist, -100)
    Call(SetBattleCamOffsetY, 50)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(b_area_flo2_huff_n_puff_StartRumbleWithParams, 70, 80)
    Thread
        Call(ShakeCam, 1, 0, 40, Float(0.2998046875))
    EndThread
    Thread
        Call(b_area_flo2_huff_n_puff_UnkBackgroundFunc3)
        Call(MakeLerp, 0, 200, 40, 0)
        Label(0)
        Call(UpdateLerp)
        Call(b_area_flo2_huff_n_puff_SetBackgroundAlpha, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
    EndThread
    Thread
        Loop(40)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetActorVar, ACTOR_SELF, 5, LVarA)
            Call(b_area_flo2_huff_n_puff_SetSnakingStaticPos, LVarA, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    Call(GetActorVar, ACTOR_SELF, 6, LVar1)
    SetF(LVar2, Float(72.5))
    SetF(LVar3, Float(67.5))
    MulF(LVar2, LVar0)
    MulF(LVar3, LVar1)
    DivF(LVar2, Float(100.0))
    DivF(LVar3, Float(100.0))
    Call(AddGoalPos, ACTOR_SELF, 0, LVar3, 0)
    Call(AddGoalPos, ACTOR_SELF, 20, 40, 0)
    Call(FlyToGoal, ACTOR_SELF, 40, -20, 11)
    Wait(30)
    Call(GetActorVar, ACTOR_SELF, 4, LVarA)
    KillThread(LVarA)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    Call(RemoveEffect, LVar0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_19_HuffNPuff_IdleAnimations_802198F0_19))
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_imp_19_HuffNPuff_IdleAnimations_8021994C_19))
    Call(SetIdleAnimations, ACTOR_SELF, 3, Ref(TTYD64_imp_19_HuffNPuff_IdleAnimations_802199A8_19))
    Call(SetAnimation, ACTOR_SELF, 1, 0x7C000E)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7C000F)
    Call(SetAnimation, ACTOR_SELF, 3, 0x7C0010)
    Call(SetPartEventBits, ACTOR_SELF, 1, 128, 0)
    Thread
        Wait(20)
        Call(MakeLerp, 200, 0, 30, 0)
        Label(1)
        Call(UpdateLerp)
        Call(b_area_flo2_huff_n_puff_SetBackgroundAlpha, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(1)
        EndIf
    EndThread
    Call(StopSound, 860)
    Call(PlaySoundAtActor, ACTOR_SELF, 859)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseEq(5)
            Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
            Sub(LVarC, 10)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVarD, LVarE, LVarF)
            Sub(LVarD, 100)
            Call(PlayEffect_impl, 94, 0, LVarA, LVarB, LVarC, LVarD, 0, LVarF, Float(1.5), 20, 0, 0, 0, 0)
            Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x7C0004)
            Call(SetAnimation, ACTOR_SELF, 2, 0x7C0005)
            Call(SetAnimation, ACTOR_SELF, 3, 0x7C0006)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 40, -20, 11)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        CaseEq(6)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar2, 10)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetOwnerTarget, LVar7, 0)
            Call(GetActorPos, LVar7, LVar3, LVar4, LVar5)
            Sub(LVar3, 4)
            Add(LVar4, 10)
            Add(LVar5, 1)
            Thread
                Call(GetActorVar, ACTOR_SELF, 6, LVar6)
                SetF(LVar7, Float(0.7255859375))
                SetF(LVar8, Float(0.2421875))
                MulF(LVar7, LVar6)
                MulF(LVar8, LVar6)
                SubF(LVar0, LVar7)
                SetF(LVar9, LVar8)
                MulF(LVar9, 3)
                AddF(LVar9, LVar0)
                Call(PlayEffect_impl, 94, 0, LVar9, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.2001953125), 10, 0, 0, 0, 0)
                Wait(3)
                SetF(LVar9, LVar8)
                MulF(LVar9, 1)
                AddF(LVar9, LVar0)
                Call(PlayEffect_impl, 94, 0, LVar9, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.2001953125), 10, 0, 0, 0, 0)
                Wait(3)
                SetF(LVar9, LVar8)
                MulF(LVar9, 4)
                AddF(LVar9, LVar0)
                Call(PlayEffect_impl, 94, 0, LVar9, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.2001953125), 10, 0, 0, 0, 0)
                Wait(3)
                SetF(LVar9, LVar8)
                MulF(LVar9, 2)
                AddF(LVar9, LVar0)
                Call(PlayEffect_impl, 94, 0, LVar9, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.2001953125), 10, 0, 0, 0, 0)
                Wait(3)
                SetF(LVar9, LVar8)
                MulF(LVar9, 5)
                AddF(LVar9, LVar0)
                Call(PlayEffect_impl, 94, 0, LVar9, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.2001953125), 10, 0, 0, 0, 0)
            EndThread
            Wait(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x7C0004)
            Call(SetAnimation, ACTOR_SELF, 2, 0x7C0005)
            Call(SetAnimation, ACTOR_SELF, 3, 0x7C0006)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 40, -20, 11)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
    EndSwitch
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar2, 10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetOwnerTarget, LVar7, 0)
    Call(GetActorPos, LVar7, LVar3, LVar4, LVar5)
    Sub(LVar3, 4)
    Add(LVar4, 10)
    Add(LVar5, 1)
    Thread
        Call(GetActorVar, ACTOR_SELF, 6, LVar6)
        SetF(LVar7, Float(0.7255859375))
        SetF(LVar8, Float(0.2421875))
        MulF(LVar7, LVar6)
        MulF(LVar8, LVar6)
        SubF(LVar0, LVar7)
        SetF(LVar9, LVar8)
        MulF(LVar9, 3)
        AddF(LVar9, LVar0)
        Call(PlayEffect_impl, 94, 0, LVar9, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.2001953125), 10, 0, 0, 0, 0)
        Wait(3)
        SetF(LVar9, LVar8)
        MulF(LVar9, 1)
        AddF(LVar9, LVar0)
        Call(PlayEffect_impl, 94, 0, LVar9, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.2001953125), 10, 0, 0, 0, 0)
        Wait(3)
        SetF(LVar9, LVar8)
        MulF(LVar9, 4)
        AddF(LVar9, LVar0)
        Call(PlayEffect_impl, 94, 0, LVar9, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.2001953125), 10, 0, 0, 0, 0)
        Wait(3)
        SetF(LVar9, LVar8)
        MulF(LVar9, 2)
        AddF(LVar9, LVar0)
        Call(PlayEffect_impl, 94, 0, LVar9, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.2001953125), 10, 0, 0, 0, 0)
        Wait(3)
        SetF(LVar9, LVar8)
        MulF(LVar9, 5)
        AddF(LVar9, LVar0)
        Call(PlayEffect_impl, 94, 0, LVar9, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.2001953125), 10, 0, 0, 0, 0)
    EndThread
    Wait(2)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000020, 0, 0, 10, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(30)
            Call(SetAnimation, ACTOR_SELF, 1, 0x7C0001)
            Call(SetAnimation, ACTOR_SELF, 2, 0x7C0002)
            Call(SetAnimation, ACTOR_SELF, 3, 0x7C0003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 40, -20, 11)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_HealOrSlam_19 = {
    UseArray(Ref(b_area_flo2_huff_n_puff_RuffPuffDataBuffer))
    Call(GetActorVar, ACTOR_SELF, 2, LVar9)
    IfEq(LVar9, 0)
        ExecWait(TTYD64_imp_19_HuffNPuff_Script_BodySlam_19)
        Return
    EndIf
    Set(LVarA, 0)
    IfFlag(LVar9, 1)
        Call(GetActorVar, ArrayVar(0), 5, LVarB)
        Add(LVarA, LVarB)
    EndIf
    IfFlag(LVar9, 2)
        Call(GetActorVar, ArrayVar(1), 5, LVarB)
        Add(LVarA, LVarB)
    EndIf
    IfFlag(LVar9, 4)
        Call(GetActorVar, ArrayVar(2), 5, LVarB)
        Add(LVarA, LVarB)
    EndIf
    IfFlag(LVar9, 8)
        Call(GetActorVar, ArrayVar(3), 5, LVarB)
        Add(LVarA, LVarB)
    EndIf
    IfFlag(LVar9, 16)
        Call(GetActorVar, ArrayVar(4), 5, LVarB)
        Add(LVarA, LVarB)
    EndIf
    IfFlag(LVar9, 32)
        Call(GetActorVar, ArrayVar(5), 5, LVarB)
        Add(LVarA, LVarB)
    EndIf
    IfFlag(LVar9, 64)
        Call(GetActorVar, ArrayVar(6), 5, LVarB)
        Add(LVarA, LVarB)
    EndIf
    IfFlag(LVar9, 128)
        Call(GetActorVar, ArrayVar(7), 5, LVarB)
        Add(LVarA, LVarB)
    EndIf
    IfFlag(LVar9, 256)
        Call(GetActorVar, ArrayVar(8), 5, LVarB)
        Add(LVarA, LVarB)
    EndIf
    IfFlag(LVar9, 512)
        Call(GetActorVar, ArrayVar(9), 5, LVarB)
        Add(LVarA, LVarB)
    EndIf
    Call(GetActorVar, 512, 0, LVar0)
    IfFlag(LVar0, 1)
        IfLe(LVarA, 2)
            Call(RandInt, 100, LVarB)
            IfLt(LVarB, 50)
                ExecWait(TTYD64_imp_19_HuffNPuff_Script_BodySlam_19)
                Return
            EndIf
        EndIf
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 944)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7C001A)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7C001B)
    Call(SetAnimation, ACTOR_SELF, 3, 0x7C001C)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, -13)
    Add(LVar1, 0)
    Add(LVar2, 0)
    Call(b_area_flo2_huff_n_puff_HuffPuffBreath, 0, LVar0, LVar1, LVar2, Float(180.0), Float(-1.0), Float(1.2001953125), 0, LVar8)
    Call(b_area_flo2_huff_n_puff_StartRumbleWithParams, 80, 220)
    Thread
        Call(ShakeCam, 1, 0, 110, Float(0.2998046875))
    EndThread
    Wait(20)
    Call(PlaySoundAtActor, ACTOR_SELF, 998)
    Set(LVar1, 0)
    IfFlag(LVar9, 16)
        Set(LVar0, ArrayVar(4))
        ExecGetTID(b_area_flo2_huff_n_puff_EVS_RuffPuff_Inhale, LVar7)
        Add(LVar1, 1)
        Wait(5)
    EndIf
    IfFlag(LVar9, 512)
        Set(LVar0, ArrayVar(9))
        ExecGetTID(b_area_flo2_huff_n_puff_EVS_RuffPuff_Inhale, LVar7)
        Add(LVar1, 1)
        Wait(5)
    EndIf
    IfFlag(LVar9, 8)
        Set(LVar0, ArrayVar(3))
        ExecGetTID(b_area_flo2_huff_n_puff_EVS_RuffPuff_Inhale, LVar7)
        Add(LVar1, 1)
        Wait(5)
    EndIf
    IfFlag(LVar9, 32)
        Set(LVar0, ArrayVar(5))
        ExecGetTID(b_area_flo2_huff_n_puff_EVS_RuffPuff_Inhale, LVar7)
        Add(LVar1, 1)
        Wait(5)
    EndIf
    IfFlag(LVar9, 2)
        Set(LVar0, ArrayVar(1))
        ExecGetTID(b_area_flo2_huff_n_puff_EVS_RuffPuff_Inhale, LVar7)
        Add(LVar1, 1)
        Wait(5)
    EndIf
    IfFlag(LVar9, 1)
        Set(LVar0, ArrayVar(0))
        ExecGetTID(b_area_flo2_huff_n_puff_EVS_RuffPuff_Inhale, LVar7)
        Add(LVar1, 1)
        Wait(5)
    EndIf
    IfFlag(LVar9, 256)
        Set(LVar0, ArrayVar(8))
        ExecGetTID(b_area_flo2_huff_n_puff_EVS_RuffPuff_Inhale, LVar7)
        Add(LVar1, 1)
        Wait(5)
    EndIf
    IfFlag(LVar9, 4)
        Set(LVar0, ArrayVar(2))
        ExecGetTID(b_area_flo2_huff_n_puff_EVS_RuffPuff_Inhale, LVar7)
        Add(LVar1, 1)
        Wait(5)
    EndIf
    IfFlag(LVar9, 128)
        Set(LVar0, ArrayVar(7))
        ExecGetTID(b_area_flo2_huff_n_puff_EVS_RuffPuff_Inhale, LVar7)
        Add(LVar1, 1)
        Wait(5)
    EndIf
    IfFlag(LVar9, 64)
        Set(LVar0, ArrayVar(6))
        ExecGetTID(b_area_flo2_huff_n_puff_EVS_RuffPuff_Inhale, LVar7)
        Add(LVar1, 1)
        Wait(5)
    EndIf
    Label(0)
    IsThreadRunning(LVar7, LVar0)
    Wait(1)
    IfEq(LVar0, 1)
        Goto(0)
    EndIf
    Call(RemoveEffect, LVar8)
    Call(StopSound, 944)
    Call(StopSound, 998)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7C0017)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7C0018)
    Call(SetAnimation, ACTOR_SELF, 3, 0x7C0019)
    Thread
        Wait(5)
        Call(PlaySoundAtActor, ACTOR_SELF, 8301)
        Call(PlaySoundAtActor, ACTOR_SELF, 532)
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetActorVar, ACTOR_SELF, 6, LVar3)
    Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0)
    Add(LVar0, 20)
    Call(PlayEffect_impl, 64, 0, LVar0, LVar1, LVar2, LVarA, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(GetActorHP, ACTOR_SELF, LVarB)
    Add(LVarB, LVarA)
    Call(SetEnemyHP, ACTOR_SELF, LVarB)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(GetActorVar, 512, 0, LVar0)
    BitwiseOrConst(LVar0, 1)
    Call(SetActorVar, 512, 0, LVar0)
    Wait(30)
    Call(UseBattleCamPreset, 2)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_BodySlam_19 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(AddBattleCamDist, -200)
    Call(SetBattleCamOffsetY, -30)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    Call(GetActorVar, ACTOR_SELF, 7, LVar1)
    SetF(LVar2, Float(62.5))
    SetF(LVar3, Float(47.5))
    MulF(LVar2, LVar0)
    MulF(LVar3, LVar1)
    DivF(LVar2, Float(100.0))
    DivF(LVar3, Float(100.0))
    Call(AddGoalPos, ACTOR_SELF, LVar2, LVar3, 0)
    Call(AddGoalPos, ACTOR_SELF, 0, 20, 0)
    Call(FlyToGoal, ACTOR_SELF, 40, -20, 11)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, 999)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(UseBattleCamPreset, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x7C000B)
            Call(SetAnimation, ACTOR_SELF, 2, 0x7C000C)
            Call(SetAnimation, ACTOR_SELF, 3, 0x7C000D)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar5, LVar6, LVar7)
            Call(SetGoalPos, ACTOR_SELF, LVar5, LVar3, LVar7)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 0, 0)
            Thread
                Call(ShakeCam, 1, 0, 10, Float(0.7998046875))
            EndThread
            IfEq(LVar0, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x7C0004)
            Call(SetAnimation, ACTOR_SELF, 2, 0x7C0005)
            Call(SetAnimation, ACTOR_SELF, 3, 0x7C0006)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
            Call(AddGoalPos, ACTOR_SELF, -80, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 25, 0, 0, 0)
            Thread
                Call(ShakeCam, 1, 0, 8, Float(0.599609375))
            EndThread
            Call(AddGoalPos, ACTOR_SELF, -50, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 0, 0)
            Thread
                Call(ShakeCam, 1, 0, 6, Float(0.400390625))
            EndThread
            Call(AddGoalPos, ACTOR_SELF, -30, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 0, 0)
            Thread
                Call(ShakeCam, 1, 0, 4, Float(0.2001953125))
            EndThread
            Call(AddGoalPos, ACTOR_SELF, -20, 0, 0)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
            Wait(30)
            Call(SetAnimation, ACTOR_SELF, 1, 0x7C0001)
            Call(SetAnimation, ACTOR_SELF, 2, 0x7C0002)
            Call(SetAnimation, ACTOR_SELF, 3, 0x7C0003)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 80, -20, 11)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x7C000B)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7C000C)
    Call(SetAnimation, ACTOR_SELF, 3, 0x7C000D)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 0, LVar3, 5)
    Call(AddGoalPos, ACTOR_SELF, 0, -30, 0)
    Call(JumpToGoal, ACTOR_SELF, 20, 0, 0, 0)
    Call(SetDamageSource, 24)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
    Mul(LVar0, 100)
    Div(LVar0, LVar1)
    Switch(LVar0)
        CaseLe(20)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 8, 0, 5, 32)
        CaseLe(40)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 8, 0, 5, 32)
        CaseLe(60)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 8, 0, 5, 32)
        CaseLe(80)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 8, 0, 5, 32)
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 8, 0, 5, 32)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Thread
                Call(ShakeCam, 1, 0, 20, Float(1.0))
            EndThread
            Call(UseBattleCamPreset, 2)
            Call(GetBattleFlags, LVar0)
            IfNotFlag(LVar0, (-0x7FFFFFFF - 1))
                Call(GetOwnerTarget, LVar3, 0)
                Call(GetStatusFlags, LVar3, LVar0)
                IfNotFlag(LVar0, 0x100000)
                    Thread
                        Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
                        Add(LVar1, 10)
                        Wait(55)
                        Call(PlayEffect_impl, 10, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                    EndThread
                EndIf
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(AddGoalPos, ACTOR_SELF, 30, 0, 0)
            Call(JumpWithBounce, ACTOR_SELF, 20, Float(4.0))
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x7C0001)
            Call(SetAnimation, ACTOR_SELF, 2, 0x7C0002)
            Call(SetAnimation, ACTOR_SELF, 3, 0x7C0003)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(FlyToGoal, ACTOR_SELF, 40, -20, 11)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_Spike_Script_80231FBC_19 = {
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
        Call(SetPartScale, ACTOR_SELF, 2, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Else
        Add(LVar0, -3)
        Add(LVar1, 10)
        Add(LVar2, 5)
        Call(SetPartScale, ACTOR_SELF, 2, Float(1.0), Float(1.0), Float(1.0))
    EndIf
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Wait(1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x100014)
    Call(SetAnimation, ACTOR_SELF, 1, 0x10000F)
    Loop(4)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            AddF(LVar1, Float(2.400390625))
        Else
            Add(LVar1, 6)
        EndIf
        Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
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
            Call(SetPartDispOffset, ACTOR_SELF, 2, 1, 0, 0)
            Wait(1)
            Call(SetActorDispOffset, ACTOR_SELF, -1, 0, 0)
            Call(SetPartDispOffset, ACTOR_SELF, 2, -1, 0, 0)
            Wait(1)
        EndLoop
        Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
        Call(SetPartDispOffset, ACTOR_SELF, 2, 0, 0, 0)
    EndThread
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x100010)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x100011)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x100012)
    Wait(3)
    Call(PlaySoundAtPart, ACTOR_SELF, 2, 710)
    Call(SetPartSounds, ACTOR_SELF, 2, 2, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 2, 0x100015)
            Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(1.5))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(RandInt, 100, LVar3)
            Sub(LVar3, 50)
            Add(LVar0, LVar3)
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, 0, LVar2, 20, 1)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Thread
                Add(LVar0, -50)
                Call(JumpPartTo, ACTOR_SELF, 2, LVar0, 0, LVar2, 15, 1)
                Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            EndThread
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(b_area_flo2_spike_EVS_ReturnHome)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 2, 0x100015)
    Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(1.5))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 20, 1)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Thread
        Add(LVar0, -50)
        Call(JumpPartTo, ACTOR_SELF, 2, LVar0, 0, LVar2, 15, 1)
        Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
    EndThread
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 4, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(15)
            Call(YieldTurn)
            ExecWait(b_area_flo2_spike_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_Thunderstorm_19 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 400)
    Call(SetBattleCamOffsetY, 5)
    Call(MoveBattleCamOver, 60)
    Call(b_area_flo2_huff_n_puff_StartRumbleWithParams, 70, 100)
    Thread
        Call(ShakeCam, 1, 0, 100, Float(0.2998046875))
    EndThread
    Call(b_area_flo2_huff_n_puff_UnkBackgroundFunc3)
    Call(MakeLerp, 0, 200, 60, 0)
    Label(0)
    Call(UpdateLerp)
    Call(b_area_flo2_huff_n_puff_SetBackgroundAlpha, LVar0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    Wait(20)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Call(GetActorVar, ACTOR_SELF, 4, LVarA)
    KillThread(LVarA)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    Call(RemoveEffect, LVar0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_19_HuffNPuff_IdleAnimations_802198F0_19))
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_imp_19_HuffNPuff_IdleAnimations_8021994C_19))
    Call(SetIdleAnimations, ACTOR_SELF, 3, Ref(TTYD64_imp_19_HuffNPuff_IdleAnimations_802199A8_19))
    Call(SetAnimation, ACTOR_SELF, 1, 0x7C000E)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7C000F)
    Call(SetAnimation, ACTOR_SELF, 3, 0x7C0010)
    Call(SetPartEventBits, ACTOR_SELF, 1, 128, 0)
    Thread
        Wait(20)
        Call(MakeLerp, 200, 0, 30, 0)
        Label(1)
        Call(UpdateLerp)
        Call(b_area_flo2_huff_n_puff_SetBackgroundAlpha, LVar0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(1)
        EndIf
    EndThread
    Call(StopSound, 860)
    Call(PlaySoundAtActor, ACTOR_SELF, 979)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar2, 10)
    Set(LVar3, LVar0)
    Sub(LVar3, 30)
    Call(PlayEffect_impl, 94, 0, LVar0, LVar1, LVar2, LVar3, 1, LVar2, Float(3.0), 30, 0, 0, 0, 0)
    Wait(5)
    Call(b_area_flo2_huff_n_puff_StartRumbleWithParams, 256, 30)
    Thread
        Call(ShakeCam, 1, 0, 10, Float(5.0))
        Call(ShakeCam, 1, 0, 10, Float(3.0))
        Call(ShakeCam, 1, 0, 10, Float(4.0))
    EndThread
    SetF(LVar6, Float(0.0))
    Loop(10)
        Set(LVar4, LVar3)
        Set(LVar5, LVar2)
        AddF(LVar6, Float(36.0))
        Call(AddVectorPolar, LVar4, LVar5, Float(300.0), LVar6)
        Call(PlayEffect_impl, 94, 0, LVar3, 1, LVar2, LVar4, 1, LVar5, Float(4.0), 30, 0, 0, 0, 0)
    EndLoop
    Wait(10)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVar0, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(TTYD64_GetPartnerHP_API, LVar0)
            IfLe(LVar0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x7C0004)
                Call(SetAnimation, ACTOR_SELF, 2, 0x7C0005)
                Call(SetAnimation, ACTOR_SELF, 3, 0x7C0006)
                Wait(20)
                Call(UseIdleAnimation, ACTOR_SELF, 1)
                Return
            EndIf
        EndCaseGroup
        CaseDefault
            Wait(2)
            Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000800, 0, 0, 12, 32)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(2)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(GetLastDamage, LVar1, LVar0)
                    IfGt(LVar0, 0)
                        Call(GetActorVar, 512, 0, LVar0)
                        BitwiseOrConst(LVar0, 8)
                        Call(SetActorVar, 512, 0, LVar0)
                    EndIf
                    Call(TTYD64_GetPartnerHP_API, LVar0)
                    IfLe(LVar0, 0)
                        Wait(20)
                    EndIf
                EndCaseGroup
            EndSwitch
    EndSwitch
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVar0, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(TTYD64_GetPartnerHP_API, LVar0)
            IfGt(LVar0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x7C0004)
                Call(SetAnimation, ACTOR_SELF, 2, 0x7C0005)
                Call(SetAnimation, ACTOR_SELF, 3, 0x7C0006)
                Wait(20)
                Call(UseIdleAnimation, ACTOR_SELF, 1)
                Return
            EndIf
        EndCaseGroup
        CaseDefault
            Wait(2)
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000800, 0, 0, 12, 32)
            Switch(LVar0)
                CaseOrEq(0)
                CaseOrEq(2)
                    Call(GetOwnerTarget, LVar1, 0)
                    Call(GetLastDamage, LVar1, LVar0)
                    IfGt(LVar0, 0)
                        Call(GetActorVar, 512, 0, LVar0)
                        BitwiseOrConst(LVar0, 8)
                        Call(SetActorVar, 512, 0, LVar0)
                    EndIf
                    Wait(20)
                EndCaseGroup
            EndSwitch
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_ShedTuffPuffs_19 = {
    UseArray(Ref(b_area_flo2_huff_n_puff_RuffPuffDataBuffer))
    Call(GetLastDamage, ACTOR_SELF, LVar9)
    IfLe(LVar9, 0)
        Return
    EndIf
    Call(GetBattleFlags, LVar0)
    IfFlag(LVar0, 576)
        IfGt(LVar9, 8)
            Set(LVar9, 8)
        EndIf
    Else
        IfGt(LVar9, 4)
            Set(LVar9, 4)
        EndIf
    EndIf
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(32)
        CaseOrEq(36)
            Return
        EndCaseGroup
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    Call(GetLastDamage, ACTOR_SELF, LVar8)
    Mul(LVar8, 1)
    Sub(LVar0, LVar8)
    IfLt(LVar0, 50)
        Set(LVar0, 50)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 6, LVar0)
    Call(GetActorVar, ACTOR_SELF, 7, LVar0)
    Call(GetLastDamage, ACTOR_SELF, LVar8)
    Mul(LVar8, 1)
    Sub(LVar0, LVar8)
    IfLt(LVar0, 50)
        Set(LVar0, 50)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 7, LVar0)
    ExecWait(b_area_flo2_huff_n_puff_EVS_UpdateSize)
    Set(LVarA, 0)
    Call(GetBattleFlags, LVar0)
    IfFlag(LVar0, 576)
        Set(LVar0, LVar9)
        IfGt(LVar0, 1)
            Set(LVarA, LVar0)
            Div(LVarA, 2)
            Set(LVar9, LVar0)
            Mod(LVar9, 2)
            Add(LVar9, LVarA)
        EndIf
    EndIf
    Loop(LVar9)
        Call(TTYD64_imp_19_HuffNPuff_Function_802185D4_19)
        IfGt(LVarA, 0)
            Sub(LVarA, 1)
            Call(SummonEnemy, Ref(TTYD64_imp_19_HuffNPuff_SpecialFormation_8021A370_19), 0)
            Call(SetActorVar, LVar0, 5, 2)
        Else
            Call(SummonEnemy, Ref(TTYD64_imp_19_HuffNPuff_SpecialFormation_8021A354_19), 0)
            Call(SetActorVar, LVar0, 5, 1)
        EndIf
        Call(GetActorVar, ACTOR_SELF, 2, LVar1)
        Call(b_area_flo2_huff_n_puff_FindPlaceForTuffPuff, LVar1, LVar2)
        Switch(LVar2)
            CaseEq(1)
                BitwiseOrConst(LVar1, 1)
                Set(LVar2, 0)
                Set(ArrayVar(0), LVar0)
            CaseEq(2)
                BitwiseOrConst(LVar1, 2)
                Set(LVar2, 1)
                Set(ArrayVar(1), LVar0)
            CaseEq(4)
                BitwiseOrConst(LVar1, 4)
                Set(LVar2, 2)
                Set(ArrayVar(2), LVar0)
            CaseEq(8)
                BitwiseOrConst(LVar1, 8)
                Set(LVar2, 3)
                Set(ArrayVar(3), LVar0)
            CaseEq(16)
                BitwiseOrConst(LVar1, 16)
                Set(LVar2, 4)
                Set(ArrayVar(4), LVar0)
            CaseEq(32)
                BitwiseOrConst(LVar1, 32)
                Set(LVar2, 5)
                Set(ArrayVar(5), LVar0)
            CaseEq(64)
                BitwiseOrConst(LVar1, 64)
                Set(LVar2, 6)
                Set(ArrayVar(6), LVar0)
            CaseEq(128)
                BitwiseOrConst(LVar1, 128)
                Set(LVar2, 7)
                Set(ArrayVar(7), LVar0)
            CaseEq(256)
                BitwiseOrConst(LVar1, 256)
                Set(LVar2, 8)
                Set(ArrayVar(8), LVar0)
            CaseEq(512)
                BitwiseOrConst(LVar1, 512)
                Set(LVar2, 9)
                Set(ArrayVar(9), LVar0)
            CaseDefault
                Set(LVar2, -1)
        EndSwitch
        Call(SetActorVar, ACTOR_SELF, 2, LVar1)
        Call(PlaySoundAtActor, LVar0, 980)
        Thread
            Set(LVar3, LVar0)
            Call(MakeLerp, 150, 255, 15, 1)
            Label(123)
            Call(UpdateLerp)
            Call(SetPartAlpha, LVar3, 1, LVar0)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(123)
            EndIf
            Call(SetPartAlpha, LVar3, 1, 255)
        EndThread
        IfNe(LVar2, -1)
            Call(CopyStatusEffects, ACTOR_SELF, LVar0)
            Call(CopyBuffs, ACTOR_SELF, LVar0)
            Call(SetActorVar, LVar0, 1, LVar2)
            Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Call(SetActorPos, LVar0, LVar3, LVar4, LVar5)
            Add(LVar3, -5)
            Add(LVar4, 0)
            Add(LVar5, 0)
            Mul(LVar2, 36)
            Add(LVar2, 0)
            Call(b_area_flo2_huff_n_puff_SetTuffPuffPos, LVar3, LVar4, LVar5, LVar2, Float(0.0), Float(50.0))
            Thread
                Call(SetActorJumpGravity, LVar0, Float(0.7998046875))
                Call(SetGoalPos, LVar0, LVar3, LVar4, LVar5)
                Call(JumpToGoal, LVar0, 30, 0, 0, 0)
                Call(ForceHomePos, LVar0, LVar3, LVar4, LVar5)
                Call(HPBarToHome, LVar0)
            EndThread
        Else
            Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
            Call(SetActorPos, LVar0, LVar3, LVar4, LVar5)
            Call(RandInt, 200, LVar6)
            Sub(LVar6, 100)
            Add(LVar3, LVar6)
            Add(LVar5, 10)
            Thread
                Call(SetActorJumpGravity, LVar0, Float(0.7998046875))
                Call(SetGoalPos, LVar0, LVar3, -30, LVar5)
                Call(JumpToGoal, LVar0, 40, 0, 0, 0)
                Call(RemoveActor, LVar0)
            EndThread
        EndIf
    EndLoop
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_GroupBodySlam_Everyonefalls = {
    Wait(50)
    Set(LVarA, 0)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(FlyToGoal, ACTOR_SELF, 20, -10, 11)
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfFlag(LVar0, 16)
        Thread
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(4), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(4), 982)
            EndIf
            Call(SetGoalToHome, ArrayVar(4))
            Call(FlyToGoal, ArrayVar(4), 20, -10, 11)
        EndThread
        Add(LVarA, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 512)
        Thread
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(9), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(9), 982)
            EndIf
            Call(SetGoalToHome, ArrayVar(9))
            Call(FlyToGoal, ArrayVar(9), 20, -10, 11)
        EndThread
        Add(LVarA, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 8)
        Thread
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(3), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(3), 982)
            EndIf
            Call(SetGoalToHome, ArrayVar(3))
            Call(FlyToGoal, ArrayVar(3), 20, -10, 11)
        EndThread
        Add(LVarA, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 32)
        Thread
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(5), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(5), 982)
            EndIf
            Call(SetGoalToHome, ArrayVar(5))
            Call(FlyToGoal, ArrayVar(5), 20, -10, 11)
        EndThread
        Add(LVarA, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 2)
        Thread
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(1), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(1), 982)
            EndIf
            Call(SetGoalToHome, ArrayVar(1))
            Call(FlyToGoal, ArrayVar(1), 20, -10, 11)
        EndThread
        Add(LVarA, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 1)
        Thread
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(0), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(0), 982)
            EndIf
            Call(SetGoalToHome, ArrayVar(0))
            Call(FlyToGoal, ArrayVar(0), 20, -10, 11)
        EndThread
        Add(LVarA, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 256)
        Thread
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(8), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(8), 982)
            EndIf
            Call(SetGoalToHome, ArrayVar(8))
            Call(FlyToGoal, ArrayVar(8), 20, -10, 11)
        EndThread
        Add(LVarA, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 4)
        Thread
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(2), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(2), 982)
            EndIf
            Call(SetGoalToHome, ArrayVar(2))
            Call(FlyToGoal, ArrayVar(2), 20, -10, 11)
        EndThread
        Add(LVarA, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 128)
        Thread
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(7), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(7), 982)
            EndIf
            Call(SetGoalToHome, ArrayVar(7))
            Call(FlyToGoal, ArrayVar(7), 20, -10, 11)
        EndThread
        Add(LVarA, 1)
        Wait(8)
    EndIf
    IfFlag(LVar0, 64)
        Thread
            Mod(LVarA, 2)
            IfEq(LVarA, 0)
                Call(PlaySoundAtActor, ArrayVar(6), 981)
            Else
                Call(PlaySoundAtActor, ArrayVar(6), 982)
            EndIf
            Call(SetGoalToHome, ArrayVar(6))
            Call(FlyToGoal, ArrayVar(6), 20, -10, 11)
        EndThread
        Add(LVarA, 1)
        Wait(8)
    EndIf
    Wait(20)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_MontyMole_Script_TakeTurn_802311BC_19 = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x2F0104)
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
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 3, 32)
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
            Call(SetAnimation, ACTOR_SELF, 3, 0x2F010F)
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
    Call(SetAnimation, ACTOR_SELF, 3, 0x2F010F)
    Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 0, 20, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 3, 32)
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
EvtScript TTYD64_flo2_Script_BeforeBattle_802349B8 = {
    Call(SetSpriteShading, -1)
    Call(SetCamBGColor, 1, 0, 0, 0)
    Set(LVar0, Ref(b_area_flo2_flo_03_VineModels))
    Exec(TTYD64_flo2_Script_802345A0)
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
            Exec(TTYD64_flo2_Script_802347B8)
            Add(LVarE, 1)
            IfGe(LVarE, 16)
                Set(LVarE, 0)
            EndIf
            Wait(10)
        EndLoop
    EndThread
    ExecWait(b_area_flo2_flo_03_MakeSun)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_TakeTurn_8021D2B8_19 = {
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseOrEq(4)
        CaseOrEq(8)
        CaseOrEq(11)
        EndCaseGroup
        CaseDefault
            Call(GetActorHP, ACTOR_SELF, LVar0)
            IfLe(LVar0, 5)
                Call(SetActorVar, ACTOR_SELF, 1, 12)
            EndIf
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseEq(3)
            Call(GetActorVar, 512, 0, LVar0)
            IfNotFlag(LVar0, 32)
                Call(GetActorVar, 512, 0, LVar0)
                BitwiseOrConst(LVar0, 32)
                Call(SetActorVar, 512, 0, LVar0)
                ExecWait(b_area_flo2_huff_n_puff_EVS_Dialogue_FullPower)
            EndIf
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfNe(LVar0, 0)
        Call(GetActorVar, 512, 0, LVar0)
        IfNotFlag(LVar0, 16)
            Call(GetActorVar, 512, 0, LVar0)
            BitwiseOrConst(LVar0, 16)
            Call(SetActorVar, 512, 0, LVar0)
            ExecWait(b_area_flo2_huff_n_puff_EVS_Dialogue_PummelPermission)
        EndIf
        ExecWait(TTYD64_imp_19_HuffNPuff_Script_TuffPuffSwarm_19)
    EndIf
    Call(GetOwnerTarget, LVar1, 0)
    IfEq(LVar1, 0)
        Call(GetPlayerHP, LVar0)
    Else
        Call(TTYD64_GetPartnerHP_API, LVar0)
    EndIf
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseEq(12)
            Call(GetActorVar, 512, 0, LVar0)
            IfNotFlag(LVar0, 128)
                Call(GetActorVar, 512, 0, LVar0)
                BitwiseOrConst(LVar0, 128)
                Call(SetActorVar, 512, 0, LVar0)
                ExecWait(b_area_flo2_huff_n_puff_EVS_Dialogue_Concerned)
            EndIf
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_HealOrSlam_19)
            Call(SetActorVar, ACTOR_SELF, 1, 1)
        CaseEq(1)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_HurricaneBreath_19)
            Call(SetActorVar, ACTOR_SELF, 1, 2)
        CaseEq(2)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_HealOrSlam_19)
            Call(SetActorVar, ACTOR_SELF, 1, 3)
        CaseEq(3)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_ChargeThunder_19)
            Call(SetActorVar, ACTOR_SELF, 1, 4)
        CaseEq(4)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_Thunderstorm_19)
            Call(SetActorVar, ACTOR_SELF, 1, 5)
        CaseEq(5)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_HealOrSlam_19)
            Call(SetActorVar, ACTOR_SELF, 1, 6)
        CaseEq(6)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_HurricaneBreath_19)
            Call(SetActorVar, ACTOR_SELF, 1, 7)
        CaseEq(7)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_ChargeLargeThunder_19)
            Call(SetActorVar, ACTOR_SELF, 1, 8)
        CaseEq(8)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_LargeThunderstorm_19)
            Call(SetActorVar, ACTOR_SELF, 1, 9)
        CaseEq(9)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_HealOrSlam_19)
            Call(SetActorVar, ACTOR_SELF, 1, 10)
        CaseEq(10)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_ChargeThunder_19)
            Call(SetActorVar, ACTOR_SELF, 1, 11)
        CaseEq(11)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_Thunderstorm_19)
            Call(SetActorVar, ACTOR_SELF, 1, 0)
        CaseEq(12)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_GroupBodySlam_19)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_80228004_19 = {
    IfEq(LVar3, 0)
        Set(LFlag0, 1)
    EndIf
    Set(LVarA, LVar1)
    Set(LVarB, LVar2)
    Div(LVarB, 2)
    Add(LVarB, 1)
    Call(SetOwnerID, LVar1)
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 500)
        Call(SetActorVar, ACTOR_SELF, 2, 1)
    Else
        Call(SetActorVar, ACTOR_SELF, 2, 2)
    EndIf
    Call(TTYD64_GetActorPointer, 512, LVar3)
    Call(TTYD64_ReadPtrField, LVar3, TTYD64_F_ACTOR_428_2U, LVar3)
    Call(SetTargetActor, LVar1, LVar3)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(GetDist2D, LVarD, LVar0, LVar2, LVar3, LVar5)
    Call(b_area_flo2_huff_n_puff_Atan2, LVarE, LVar0, LVar2, LVar3, LVar5)
    Set(LVarF, 0)
    Loop(0)
        Call(PlaySoundAtActor, ACTOR_SELF, 987)
        Set(LVarF, 0)
        Set(LVarC, LVarB)
        Add(LVarC, LVarB)
        Set(LVar9, LVarC)
        Loop(LVarC)
            Call(b_area_flo2_huff_n_puff_UpdateLerp, 5, Float(100.0), Float(40.0), LVarF, LVar9, LVar0)
            MulF(LVar0, LVarD)
            DivF(LVar0, Float(100.0))
            Call(GetOwnerTarget, LVar4, 0)
            Call(GetActorPos, LVar4, LVar1, LVar2, LVar3)
            Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
            Call(AddVectorPolar, LVar1, LVar3, LVar0, LVarE)
            Call(SetActorPos, ACTOR_SELF, LVar1, LVar5, LVar3)
            Add(LVarF, 1)
            Wait(1)
        EndLoop
        Wait(5)
        IfEq(LFlag0, 1)
            Call(GetActorVar, 512, 0, LVar0)
            BitwiseOrConst(LVar0, 4)
            Call(SetActorVar, 512, 0, LVar0)
        EndIf
        Set(LVarF, 0)
        Set(LVarC, LVarB)
        Loop(LVarC)
            Call(b_area_flo2_huff_n_puff_UpdateLerp, 6, Float(40.0), Float(100.0), LVarF, LVarB, LVar0)
            MulF(LVar0, LVarD)
            DivF(LVar0, Float(100.0))
            Call(GetOwnerTarget, LVar4, 0)
            Call(GetActorPos, LVar4, LVar1, LVar2, LVar3)
            Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
            Call(AddVectorPolar, LVar1, LVar3, LVar0, LVarE)
            Call(SetActorPos, ACTOR_SELF, LVar1, LVar5, LVar3)
            Add(LVarF, 1)
            Wait(1)
        EndLoop
        Wait(10)
    EndLoop
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_HandleEvent_8021BA6C_19 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            ExecWait(b_area_flo2_huff_n_puff_EVS_IncreaseWobble)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_8021AD3C_19)
        CaseEq(10)
            ExecWait(b_area_flo2_huff_n_puff_EVS_IncreaseWobble)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_8021AD3C_19)
            Call(GetActorVar, 512, 0, LVar0)
            BitwiseAndConst(LVar0, -3)
            Call(SetActorVar, 512, 0, LVar0)
            Call(SetActorVar, ACTOR_SELF, 3, 0)
        CaseEq(14)
            ExecWait(b_area_flo2_huff_n_puff_EVS_IncreaseWobble)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_8021B2C0_19)
            Call(GetActorVar, 512, 0, LVar0)
            BitwiseAndConst(LVar0, -3)
            Call(SetActorVar, 512, 0, LVar0)
            Call(SetActorVar, ACTOR_SELF, 3, 0)
        CaseEq(36)
            ExecWait(b_area_flo2_huff_n_puff_EVS_IncreaseWobble)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_8021B2C0_19)
            ExecWait(b_area_flo2_huff_n_puff_EVS_HuffNPuff_BurnDeath)
            Return
        CaseEq(23)
            ExecWait(b_area_flo2_huff_n_puff_EVS_HuffNPuff_NoDamage)
        CaseEq(25)
            ExecWait(b_area_flo2_huff_n_puff_EVS_HuffNPuff_NoDamage)
            Call(GetActorVar, 512, 0, LVar0)
            BitwiseAndConst(LVar0, -3)
            Call(SetActorVar, 512, 0, LVar0)
        CaseEq(32)
            ExecWait(b_area_flo2_huff_n_puff_EVS_IncreaseWobble)
            ExecWait(TTYD64_imp_19_HuffNPuff_Script_8021AD3C_19)
            ExecWait(b_area_flo2_huff_n_puff_EVS_HuffNPuff_Death)
            Return
        CaseEq(58)
            ExecWait(b_area_flo2_huff_n_puff_EVS_IncreaseWobble)
        CaseEq(31)
            ExecWait(b_area_flo2_huff_n_puff_EVS_HuffNPuff_NoDamage)
            Call(GetActorVar, 512, 0, LVar0)
            BitwiseAndConst(LVar0, -3)
            Call(SetActorVar, 512, 0, LVar0)
            Call(SetActorVar, ACTOR_SELF, 3, 0)
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_ChargeLargeThunder_19 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    ExecGetTID(b_area_flo2_huff_n_puff_EVS_UpdateChargedJitter, LVarA)
    Call(SetActorVar, ACTOR_SELF, 4, LVarA)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 400)
    Call(SetBattleCamOffsetY, 5)
    Call(MoveBattleCamOver, 60)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7C0011)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7C0012)
    Call(SetAnimation, ACTOR_SELF, 3, 0x7C0013)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_flo2_huff_n_puff_ChargedBodyAnims))
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(b_area_flo2_huff_n_puff_ChargedFaceAnims))
    Call(SetIdleAnimations, ACTOR_SELF, 3, Ref(b_area_flo2_huff_n_puff_ChargedArmAnims))
    Call(SetPartEventBits, ACTOR_SELF, 1, 128, 1)
    Call(PlaySoundAtActor, ACTOR_SELF, 860)
    Call(b_area_flo2_huff_n_puff_StartRumbleWithParams, 70, 120)
    Thread
        Call(ShakeCam, 1, 0, 60, Float(0.2998046875))
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetActorVar, ACTOR_SELF, 6, LVar3)
    DivF(LVar3, Float(100.0))
    Call(b_area_flo2_huff_n_puff_MakeSnakingStatic, LVar0, LVar1, LVar2, LVar3)
    Call(SetActorVar, ACTOR_SELF, 5, LVar0)
    Wait(60)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Wait(30)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_ChargeThunder_19 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    ExecGetTID(b_area_flo2_huff_n_puff_EVS_UpdateChargedJitter, LVarA)
    Call(SetActorVar, ACTOR_SELF, 4, LVarA)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 400)
    Call(SetBattleCamOffsetY, 5)
    Call(MoveBattleCamOver, 60)
    Call(SetAnimation, ACTOR_SELF, 1, 0x7C0011)
    Call(SetAnimation, ACTOR_SELF, 2, 0x7C0012)
    Call(SetAnimation, ACTOR_SELF, 3, 0x7C0013)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_flo2_huff_n_puff_ChargedBodyAnims))
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(b_area_flo2_huff_n_puff_ChargedFaceAnims))
    Call(SetIdleAnimations, ACTOR_SELF, 3, Ref(b_area_flo2_huff_n_puff_ChargedArmAnims))
    Call(SetPartEventBits, ACTOR_SELF, 1, 128, 1)
    Call(PlaySoundAtActor, ACTOR_SELF, 860)
    Call(b_area_flo2_huff_n_puff_StartRumbleWithParams, 70, 120)
    Thread
        Call(ShakeCam, 1, 0, 60, Float(0.2998046875))
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetActorVar, ACTOR_SELF, 6, LVar3)
    DivF(LVar3, Float(100.0))
    Call(b_area_flo2_huff_n_puff_MakeSnakingStatic, LVar0, LVar1, LVar2, LVar3)
    Call(SetActorVar, ACTOR_SELF, 5, LVar0)
    Wait(60)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Wait(30)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_Init_8022F780_19 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(b_area_flo2_tuff_puff_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_19_HuffNPuff_Script_Idle_8022FA10_19))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_flo2_tuff_puff_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_flo2_tuff_puff_EVS_HandlePhase))
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -9)
        Call(SetProjectileTargetOffset, ACTOR_SELF, 2, -1, -9)
        Call(SetTargetOffset, ACTOR_SELF, 1, -1, 9)
        Call(SetTargetOffset, ACTOR_SELF, 2, -1, -41)
        Call(SetActorSize, ACTOR_SELF, 20, 25)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_19_HuffNPuff_IdleAnimations_8022F580_19))
        Call(SetAnimation, ACTOR_SELF, 1, 0x4C0002)
        Call(SetActorVar, ACTOR_SELF, 0, 0)
    Else
        Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -8, -13)
        Call(SetProjectileTargetOffset, ACTOR_SELF, 2, -8, -13)
        Call(SetTargetOffset, ACTOR_SELF, 1, 1, 14)
        Call(SetTargetOffset, ACTOR_SELF, 2, 1, -36)
        Call(SetActorSize, ACTOR_SELF, 28, 35)
        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_imp_19_HuffNPuff_IdleAnimations_8022F5DC_19))
        Call(SetAnimation, ACTOR_SELF, 1, 0x4C0003)
        Call(SetActorVar, ACTOR_SELF, 0, 1)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 100)
    Call(SetActorVar, ACTOR_SELF, 4, 100)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_Idle_8021A0E4_19 = {
    Set(LVarF, 0)
    Loop(0)
        Call(GetActorVar, ACTOR_SELF, 3, LVarA)
        Switch(LVarA)
            CaseEq(0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar0, Float(0.9697265625), Float(1.0302734375), 15, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar1, Float(1.0302734375), Float(0.9697265625), 15, 0, 0)
                Add(LVarF, 1)
            CaseEq(1)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar0, Float(0.9501953125), Float(1.0498046875), 15, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar1, Float(1.0498046875), Float(0.9501953125), 15, 0, 0)
                Add(LVarF, 3)
            CaseEq(2)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar0, Float(0.900390625), Float(1.099609375), 15, 0, 0)
                Call(b_area_flo2_huff_n_puff_CosInterpMinMax, LVarF, LVar1, Float(1.099609375), Float(0.900390625), 15, 0, 0)
                Add(LVarF, 5)
        EndSwitch
        Call(GetActorVar, ACTOR_SELF, 6, LVar2)
        Call(GetActorVar, ACTOR_SELF, 7, LVar3)
        DivF(LVar2, Float(100.0))
        DivF(LVar3, Float(100.0))
        MulF(LVar1, LVar2)
        MulF(LVar0, LVar3)
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

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_Idle_8022FA10_19 = {
    Set(LVarF, 0)
    Loop(0)
        Call(GetActorVar, ACTOR_SELF, 2, LVarA)
        Switch(LVarA)
            CaseEq(0)
                Call(b_area_flo2_tuff_puff_CosInterpMinMax, LVarF, LVar0, Float(0.9697265625), Float(1.0302734375), 15, 0, 0)
                Call(b_area_flo2_tuff_puff_CosInterpMinMax, LVarF, LVar1, Float(1.0302734375), Float(0.9697265625), 15, 0, 0)
                Add(LVarF, 1)
            CaseEq(1)
                Call(b_area_flo2_tuff_puff_CosInterpMinMax, LVarF, LVar0, Float(0.9501953125), Float(1.0498046875), 15, 0, 0)
                Call(b_area_flo2_tuff_puff_CosInterpMinMax, LVarF, LVar1, Float(1.0498046875), Float(0.9501953125), 15, 0, 0)
                Add(LVarF, 3)
            CaseEq(2)
                Call(b_area_flo2_tuff_puff_CosInterpMinMax, LVarF, LVar0, Float(0.900390625), Float(1.099609375), 15, 0, 0)
                Call(b_area_flo2_tuff_puff_CosInterpMinMax, LVarF, LVar1, Float(1.099609375), Float(0.900390625), 15, 0, 0)
                Add(LVarF, 5)
        EndSwitch
        Call(GetActorVar, ACTOR_SELF, 3, LVar2)
        Call(GetActorVar, ACTOR_SELF, 4, LVar3)
        DivF(LVar2, Float(100.0))
        DivF(LVar3, Float(100.0))
        MulF(LVar1, LVar2)
        MulF(LVar0, LVar3)
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

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_8021B2C0_19 = {
    ExecWait(TTYD64_imp_19_HuffNPuff_Script_ShedTuffPuffs_19)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseOrEq(4)
        CaseOrEq(8)
        CaseOrEq(11)
            SetConst(LVar2, 0x7C0011)
            SetConst(LVar3, 0x7C0012)
            SetConst(LVar4, 0x7C0013)
        EndCaseGroup
        CaseDefault
            SetConst(LVar2, 0x7C0023)
            SetConst(LVar3, 0x7C0024)
            SetConst(LVar4, 0x7C0025)
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 2, LVar3)
    Call(SetAnimation, ACTOR_SELF, 3, LVar4)
    Wait(20)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseOrEq(4)
        CaseOrEq(8)
        CaseOrEq(11)
            SetConst(LVar2, 0x7C0011)
            SetConst(LVar3, 0x7C0012)
            SetConst(LVar4, 0x7C0013)
        EndCaseGroup
        CaseDefault
            SetConst(LVar2, 0x7C0026)
            SetConst(LVar3, 0x7C0027)
            SetConst(LVar4, 0x7C0028)
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 2, LVar3)
    Call(SetAnimation, ACTOR_SELF, 3, LVar4)
    Wait(10)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_flo2_Script_802347B8 = {
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
        Call(b_area_flo2_flo_03_CosInterpMinMax, LVarE, LVarA, Float(0.0), Float(0.203125), 15, 0, 0)
        AddF(LVar8, LVarA)
        SetF(LVar9, LVar7)
        Call(b_area_flo2_flo_03_CosInterpMinMax, LVarE, LVarA, Float(0.0), Float(0.203125), 20, 0, 90)
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
EvtScript TTYD64_flo2_Script_802345A0 = {
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
EvtScript TTYD64_imp_19_HuffNPuff_Script_8021AD3C_19 = {
    ExecWait(TTYD64_imp_19_HuffNPuff_Script_ShedTuffPuffs_19)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseOrEq(4)
        CaseOrEq(8)
        CaseOrEq(11)
            SetConst(LVar2, 0x7C0011)
            SetConst(LVar3, 0x7C0012)
            SetConst(LVar4, 0x7C0013)
        EndCaseGroup
        CaseDefault
            SetConst(LVar2, 0x7C0007)
            SetConst(LVar3, 0x7C0008)
            SetConst(LVar4, 0x7C0009)
    EndSwitch
    Thread
        Set(LVar0, 1)
        Set(LVar1, LVar2)
        ExecWait(Ref(EVS_Enemy_Hit))
    EndThread
    Thread
        Set(LVar0, 2)
        Set(LVar1, LVar3)
        ExecWait(Ref(EVS_Enemy_Hit))
    EndThread
    Thread
        Set(LVar0, 3)
        Set(LVar1, LVar4)
        ExecWait(Ref(EVS_Enemy_Hit))
    EndThread
    Wait(30)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_imp_19_HuffNPuff_Script_Init_80219BC4_19 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_19_HuffNPuff_Script_TakeTurn_8021D2B8_19))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_imp_19_HuffNPuff_Script_Idle_8021A0E4_19))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_imp_19_HuffNPuff_Script_HandleEvent_8021BA6C_19))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_flo2_huff_n_puff_EVS_HandlePhase))
    Call(SetActorVar, 512, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 100)
    Call(SetActorVar, ACTOR_SELF, 7, 100)
    ExecWait(b_area_flo2_huff_n_puff_EVS_UpdateSize)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_19_MontyMole_StatusTable_8023066C_19[] = {
    1,  0, 2,  0, 6,  60, 9,  80, 7,  100, 4,  90, 3,  0, 11, 10, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, -1,  35, 0,  33, 0, 38, 1,  39, 0,  41, 0,  0,
};

ActorPartBlueprint TTYD64_imp_19_HuffNPuff_PartsTable_80219B0C_19[] = {
    {
        .flags = 0x800028,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -10, 40 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_19_HuffNPuff_IdleAnimations_802198F0_19,
        .defenseTable = b_area_flo2_huff_n_puff_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -15, -50 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_19_HuffNPuff_IdleAnimations_8021994C_19,
        .defenseTable = b_area_flo2_huff_n_puff_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20000,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_19_HuffNPuff_IdleAnimations_802199A8_19,
        .defenseTable = b_area_flo2_huff_n_puff_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_flo2_huff_n_puff_DummyAnims,
        .defenseTable = b_area_flo2_huff_n_puff_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

Battle TTYD64_flo2_FormationTable[] = {
    { .name = "\252\272\342\374\363",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_flo2_Formation_00,
      .stage = &b_area_flo2_flo_04,
      .onBattleStart = NULL },
    { .name = "\325\351\357\374\301\347\355\327\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_flo2_Formation_01,
      .stage = &b_area_flo2_flo_01,
      .onBattleStart = NULL },
    { .name = "\325\351\357\374\301\347\355\327\374x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_flo2_Formation_02,
      .stage = &b_area_flo2_flo_01,
      .onBattleStart = NULL },
    { .name = "\325\351\357\374\301\347\355\327\374x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_flo2_Formation_03,
      .stage = &b_area_flo2_flo_01,
      .onBattleStart = NULL },
    { .name = "\325\351\357\374\301\347\355\327\374x\024",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_flo2_Formation_04,
      .stage = &b_area_flo2_flo_01,
      .onBattleStart = NULL },
    { .name = "\270\347\312\265\363\037",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_flo2_Formation_05,
      .stage = &b_area_flo2_flo_01,
      .onBattleStart = NULL },
    {},
};

FormationRow TTYD64_flo2_Formation_04[] = {
    { .actor = &TTYD64_imp_19_MontyMole_19_MontyMole,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_imp_19_MontyMole_19_MontyMole,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_imp_19_MontyMole_19_MontyMole,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_imp_19_MontyMole_19_MontyMole,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
};

ActorPartBlueprint TTYD64_imp_19_MontyMole_PartsTable_80230718_19[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 16 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_19_MontyMole_IdleAnimations_802307AC_19,
        .defenseTable = b_area_flo2_monty_mole_boss_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -7 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x80800001,
        .index = 2,
        .posOffset = { 0, 0, -15 },
        .targetOffset = { 0, 16 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_19_MontyMole_IdleAnimations_802307AC_19,
        .defenseTable = b_area_flo2_monty_mole_boss_DefenseTable,
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
        .idleAnimations = b_area_flo2_monty_mole_boss_RockAnims,
        .defenseTable = b_area_flo2_monty_mole_boss_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_imp_19_MontyMole_Script_Init_802309C0_19 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_19_MontyMole_Script_TakeTurn_802311BC_19))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_flo2_monty_mole_boss_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_flo2_monty_mole_boss_EVS_HandleEvent))
    Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
    Return
    End
};
// clang-format on

s32 TTYD64_imp_19_HuffNPuff_IdleAnimations_802198F0_19[] = {
    1, 0x7C0001, 7, 0x7C0001, 6, 0x7C0001, 9, 0x7C0001, 8, 0x7C0001, 11, 0x7C0001,
    5, 0x7C0001, 5, 0x7C0001, 4, 0x7C0001, 4, 0x7C0001, 3, 0x7C0001, 0,
};

s32 TTYD64_imp_19_HuffNPuff_IdleAnimations_8021994C_19[] = {
    1, 0x7C0002, 7, 0x7C0002, 6, 0x7C0002, 9, 0x7C0002, 8, 0x7C0002, 11, 0x7C0002,
    5, 0x7C0002, 5, 0x7C0002, 4, 0x7C0002, 4, 0x7C0002, 3, 0x7C0002, 0,
};

s32 TTYD64_imp_19_HuffNPuff_IdleAnimations_8022F580_19[] = {
    1, 0x4C0002, 7, 0x4C0000, 6, 0x4C0002, 9, 0x4C0002, 8, 0x4C0000, 11, 0x4C0002,
    5, 0x4C0002, 5, 0x4C0000, 4, 0x4C0002, 4, 0x4C0002, 3, 0x4C0002, 0,
};

s32 TTYD64_imp_19_HuffNPuff_IdleAnimations_8022F5DC_19[] = {
    1, 0x4C0003, 7, 0x4C0001, 6, 0x4C0003, 9, 0x4C0003, 8, 0x4C0001, 11, 0x4C0003,
    5, 0x4C0003, 5, 0x4C0001, 4, 0x4C0003, 4, 0x4C0003, 3, 0x4C0003, 0,
};

s32 TTYD64_imp_19_HuffNPuff_IdleAnimations_802199A8_19[] = {
    1, 0x7C0003, 7, 0x7C0003, 6, 0x7C0003, 9, 0x7C0003, 8, 0x7C0003, 11, 0x7C0003,
    5, 0x7C0003, 5, 0x7C0003, 4, 0x7C0003, 4, 0x7C0003, 3, 0x7C0003, 0,
};

StageListRow TTYD64_flo2_StageTable[] = {
    { .name = "flo_01", .stage = &b_area_flo2_flo_01 },
    { .name = "flo_01b", .stage = &b_area_flo2_flo_01b },
    { .name = "flo_01c", .stage = &b_area_flo2_flo_01c },
    { .name = "flo_02", .stage = &b_area_flo2_flo_02 },
    { .name = "flo_02b", .stage = &b_area_flo2_flo_02b },
    { .name = "flo_02c", .stage = &b_area_flo2_flo_02c },
    { .name = "flo_03", .stage = &TTYD64_flo2_Stage_80234FAC },
    { .name = "flo_04", .stage = &b_area_flo2_flo_04 },
    { .name = "flo_05", .stage = &b_area_flo2_flo_05 },
    { .name = "flo_06", .stage = &b_area_flo2_flo_06 },
    {},
};

FormationRow TTYD64_flo2_Formation_03[] = {
    { .actor = &TTYD64_imp_19_MontyMole_19_MontyMole,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_imp_19_MontyMole_19_MontyMole,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_imp_19_MontyMole_19_MontyMole,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
};

// clang-format off
EvtScript TTYD64_imp_19_Spike_Script_Init_80231990_19 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_imp_19_Spike_Script_TakeTurn_802329E4_19))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_flo2_spike_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_flo2_spike_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_imp_19_Spike_IdleAnimations_80231810_19[] = {
    1,  0x100001, 7, 0x100000, 6, 0x10001A, 9, 0x100001, 8, 0x100000,
    11, 0x100001, 5, 0x100000, 4, 0x100008, 3, 0x100001, 0,
};

s32 TTYD64_imp_19_MontyMole_IdleAnimations_802307AC_19[] = {
    1,  0x2F0101, 7, 0x2F0100, 6, 0x2F0114, 9, 0x2F0101, 8, 0x2F0100,
    11, 0x2F0101, 5, 0x2F0100, 4, 0x2F0114, 3, 0x2F0114, 0,
};

ActorPartBlueprint TTYD64_imp_19_Spike_PartsTable_80231920_19[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -5, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_19_Spike_IdleAnimations_80231810_19,
        .defenseTable = b_area_flo2_spike_DefenseTable,
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
        .idleAnimations = b_area_flo2_spike_SpinyBallAnims,
        .defenseTable = b_area_flo2_spike_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_imp_19_HuffNPuff_PartsTable_8022F710_19[] = {
    {
        .flags = 0x20022,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = TTYD64_imp_19_HuffNPuff_IdleAnimations_8022F580_19,
        .defenseTable = b_area_flo2_tuff_puff_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x80800023,
        .index = 2,
        .posOffset = { 0, 50, 0 },
        .targetOffset = { 0, -50 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_flo2_tuff_puff_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_flo2_Formation_02[] = {
    { .actor = &TTYD64_imp_19_MontyMole_19_MontyMole,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
    { .actor = &TTYD64_imp_19_MontyMole_19_MontyMole,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
};

Stage TTYD64_flo2_Stage_80234FAC = {
    .texture = "flo_tex",
    .shape = "flo_bt03_shape",
    .hit = "flo_bt03_hit",
    .preBattle = &TTYD64_flo2_Script_BeforeBattle_802349B8,
    .postBattle = &b_area_flo2_flo_03_EVS_PostBattle,
    .bg = "fla_bg",
    .foregroundModelList = b_area_flo2_flo_03_ForegroundVineModels,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_imp_19_Spike_19_Spike = {
    .flags = 0x200,
    .maxHP = 50,
    .type = 0x35,
    .level = 40,
    .partCount = 2,
    .partsData = TTYD64_imp_19_Spike_PartsTable_80231920_19,
    .initScript = &TTYD64_imp_19_Spike_Script_Init_80231990_19,
    .statusTable = b_area_flo2_spike_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 32, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -14, 20 },
    .statusTextOffset = { 6, 32 },
};

ActorBlueprint TTYD64_imp_19_MontyMole_19_MontyMole = {
    .flags = 0x0,
    .maxHP = 12,
    .type = 0x30,
    .level = 19,
    .partCount = 3,
    .partsData = TTYD64_imp_19_MontyMole_PartsTable_80230718_19,
    .initScript = &TTYD64_imp_19_MontyMole_Script_Init_802309C0_19,
    .statusTable = TTYD64_imp_19_MontyMole_StatusTable_8023066C_19,
    .escapeChance = 50,
    .airLiftChance = 55,
    .hurricaneChance = 40,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 4,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 34, 18 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_19_HuffNPuff_19_HuffNPuff = {
    .flags = 0x8200,
    .maxHP = 60,
    .type = 0xBA,
    .level = 80,
    .partCount = 4,
    .partsData = TTYD64_imp_19_HuffNPuff_PartsTable_80219B0C_19,
    .initScript = &TTYD64_imp_19_HuffNPuff_Script_Init_80219BC4_19,
    .statusTable = b_area_flo2_huff_n_puff_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 70,
    .coinReward = 0,
    .size = { 125, 95 },
    .healthBarOffset = { -17, -31 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_imp_19_HuffNPuff_TuffPuff_19 = {
    .flags = 0x208200,
    .maxHP = 1,
    .type = 0xBB,
    .level = 0,
    .partCount = 2,
    .partsData = TTYD64_imp_19_HuffNPuff_PartsTable_8022F710_19,
    .initScript = &TTYD64_imp_19_HuffNPuff_Script_Init_8022F780_19,
    .statusTable = b_area_flo2_tuff_puff_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { 24, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 0 },
    .statusTextOffset = { 10, 10 },
};

FormationRow TTYD64_imp_19_HuffNPuff_SpecialFormation_8021A354_19[] = {
    { .actor = &TTYD64_imp_19_HuffNPuff_TuffPuff_19,
      .home = { .vec = &b_area_flo2_huff_n_puff_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_flo2_Formation_00[] = {
    { .actor = &TTYD64_imp_19_HuffNPuff_19_HuffNPuff,
      .home = { .vec = &b_area_flo2_huff_n_puff_pos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_flo2_Formation_01[] = {
    { .actor = &TTYD64_imp_19_MontyMole_19_MontyMole,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_MONTYMOLE },
};

FormationRow TTYD64_flo2_Formation_05[] = {
    { .actor = &TTYD64_imp_19_Spike_19_Spike,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

// clang-format off
EvtScript TTYD64_imp_19_Spike_Script_TakeTurn_802329E4_19 = {
    ExecWait(TTYD64_imp_19_Spike_Script_80231FBC_19)
    Return
    End
};
// clang-format on

FormationRow TTYD64_imp_19_HuffNPuff_SpecialFormation_8021A370_19[] = {
    { .actor = &TTYD64_imp_19_HuffNPuff_TuffPuff_19,
      .home = { .vec = &b_area_flo2_huff_n_puff_SummonPos },
      .priority = 0,
      .var0 = 1,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

void TTYD64_InstallBattles_flo2(void) {
    Mod_SetBattleList("TTYD64", 0x19, TTYD64_flo2_FormationTable);
    Mod_SetStageList("TTYD64", 0x19, TTYD64_flo2_StageTable);
}
