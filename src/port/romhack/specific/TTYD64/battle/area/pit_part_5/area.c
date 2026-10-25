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
#include "port/romhack/specific/TTYD64/battle/area/battles_new.h"

extern EvtScript b_area_kmr_part_1_kmr_02_EVS_PostBattle;
extern EvtScript b_area_kmr_part_3_kpa_13_EVS_PreBattle;
extern EvtScript b_area_omo_groove_guy_EVS_CountActiveSummoners;
extern EvtScript b_area_omo_groove_guy_EVS_GetAvailableColumn;
extern EvtScript b_area_omo_groove_guy_EVS_HandleEvent;
extern EvtScript b_area_omo_groove_guy_EVS_Idle;
extern EvtScript b_area_omo_groove_guy_EVS_PerformSummonDance;
extern Vec3i b_area_omo_groove_guy_SummonPos;
extern s32 b_area_omo_medi_guy_StatusTable[];
extern s32 b_area_omo_pyro_guy_StatusTable[];
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(ForceHomePos);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToHome);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
extern ActorBlueprint TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa;
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D450_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D49C_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021D4E8_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F1F0_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F23C_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F288_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F2D4_1A[];
extern s32 TTYD64_imp_1A_DarkParatroopa_IdleAnimations_8021F320_1A[];
extern ActorPartBlueprint TTYD64_imp_1A_DarkParatroopa_PartsTable_8021D3BC_1A[];
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_8021EC2C_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_8021F36C_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_80221B70_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_DarkParatroopa_DizzyAttack;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Darkparatroopa_ShellAttack;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_HandleEvent_8021DA3C_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_HandleEvent_8021FE4C_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Idle_8021D6AC_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Idle_8021F5E4_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_Init_8021D55C_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_TakeTurn_8021E174_1A;
extern EvtScript TTYD64_imp_1A_DarkParatroopa_Script_TakeTurn_80222014_1A;
extern ActorPartBlueprint TTYD64_omo_groove_guy_ActorParts[];
extern s32 TTYD64_omo_groove_guy_DefaultAnims[];
extern EvtScript TTYD64_omo_groove_guy_EVS_Attack_SleepySpin;
extern EvtScript TTYD64_omo_groove_guy_EVS_Attack_Tackle;
extern s32 TTYD64_omo_groove_guy_StatusTable[];
extern ActorPartBlueprint TTYD64_omo_medi_guy_ActorParts[];
extern s32 TTYD64_omo_medi_guy_DefaultAnims[];
extern EvtScript TTYD64_omo_medi_guy_EVS_Attack_Swoop;
extern EvtScript TTYD64_omo_medi_guy_EVS_Init;
extern EvtScript TTYD64_omo_medi_guy_EVS_TakeTurn;
extern ActorPartBlueprint TTYD64_omo_pyro_guy_ActorParts[];
extern s32 TTYD64_omo_pyro_guy_DefaultAnims[];
extern EvtScript TTYD64_omo_pyro_guy_EVS_Init;
extern EvtScript TTYD64_omo_pyro_guy_EVS_TakeTurn;
extern ActorPartBlueprint TTYD64_omo_red_shy_guy_ActorParts[];
extern s32 TTYD64_omo_red_shy_guy_DefaultAnims[];
extern EvtScript TTYD64_omo_red_shy_guy_EVS_Attack_Tackle;
extern EvtScript TTYD64_omo_red_shy_guy_EVS_Attack_Vault;
extern EvtScript TTYD64_omo_red_shy_guy_EVS_Init;
extern EvtScript TTYD64_omo_red_shy_guy_EVS_TakeTurn;
extern s32 TTYD64_omo_red_shy_guy_StatusTable[];
extern ActorPartBlueprint TTYD64_omo_spy_guy_ActorParts[];
extern EvtScript TTYD64_omo_spy_guy_EVS_Attack_Mallet;
extern EvtScript TTYD64_omo_spy_guy_EVS_Attack_Slingshot;
extern EvtScript TTYD64_omo_spy_guy_EVS_HandleEvent;
extern EvtScript TTYD64_omo_spy_guy_EVS_Init;
extern EvtScript TTYD64_omo_spy_guy_EVS_ManageItemMotion;
extern EvtScript TTYD64_omo_spy_guy_EVS_TakeTurn;
extern EvtScript TTYD64_omo_spy_guy_EVS_TrySwitchWeapon;
extern s32 TTYD64_omo_spy_guy_MalletAnims[];
extern s32 TTYD64_omo_spy_guy_SlingshotAnims[];
extern s32 TTYD64_omo_spy_guy_StatusTable[];
extern EvtScript TTYD64_pit_part_5_imp_10_GrooveGuy_Script_80226DEC_10;
extern EvtScript TTYD64_pit_part_5_imp_10_GrooveGuy_Script_TakeTurn_80226338_10;
extern EvtScript TTYD64_pit_part_5_imp_10_GrooveGuy_Script_802271A0_10;
extern EvtScript TTYD64_pit_part_5_imp_10_GrooveGuy_Script_80226C00_10;
extern Battle TTYD64_pit_part_5_FormationTable[];
extern EvtScript TTYD64_pit_part_5_imp_10_GrooveGuy_Script_RandomSummon_10;
extern EvtScript TTYD64_pit_part_5_Script_BeforeBattle_Pit;
extern FormationRow TTYD64_pit_part_5_Formation_Pit45_2[];
extern FormationRow TTYD64_pit_part_5_Formation_Pit45_3[];
extern FormationRow TTYD64_pit_part_5_Formation_Pit42_47_3[];
extern FormationRow TTYD64_pit_part_5_Formation_Pit43_48_3[];
extern FormationRow TTYD64_pit_part_5_Formation_Pit44_49_2[];
extern FormationRow TTYD64_pit_part_5_Formation_Pit44_49_3[];
extern FormationRow TTYD64_pit_part_5_Formation_Pit41_46_3[];
extern EvtScript TTYD64_pit_part_5_imp_10_GrooveGuy_Script_Init_80224B38_10;
extern FormationRow TTYD64_pit_part_5_Formation_Pit43_48_1[];
extern FormationRow TTYD64_pit_part_5_Formation_Pit43_48_2[];
extern FormationRow TTYD64_pit_part_5_Formation_Pit41_46_2[];
extern FormationRow TTYD64_pit_part_5_Formation_Pit41_46_1[];
extern FormationRow TTYD64_pit_part_5_Formation_Pit45_1[];
extern FormationRow TTYD64_pit_part_5_Formation_Pit42_47_1[];
extern FormationRow TTYD64_pit_part_5_Formation_Pit42_47_2[];
extern FormationRow TTYD64_pit_part_5_Formation_Pit44_49_1[];
extern ActorBlueprint TTYD64_pit_part_5_imp_10_MediGuy_10_MediGuy;
extern Stage TTYD64_pit_part_5_Stage_Pit1;
extern Stage TTYD64_pit_part_5_Stage_Pit2;
extern ActorBlueprint TTYD64_pit_part_5_imp_10_ShyGuy_RED_10_ShyGuy_RED;
extern ActorBlueprint TTYD64_pit_part_5_imp_10_GrooveGuy_10_GrooveGuy;
extern ActorBlueprint TTYD64_pit_part_5_imp_10_SpyGuy_10_SpyGuy;
extern ActorBlueprint TTYD64_pit_part_5_imp_10_PyroGuy_10_PyroGuy;
extern FormationRow TTYD64_pit_part_5_imp_10_GrooveGuy_SpecialFormation_802273E0_10[];
extern FormationRow TTYD64_pit_part_5_imp_10_GrooveGuy_SpecialFormation_802273C4_10[];
extern FormationRow TTYD64_pit_part_5_imp_10_GrooveGuy_SpecialFormation_802273A8_10[];
extern StageListRow TTYD64_pit_part_5_StageTable[];

// clang-format off
EvtScript TTYD64_pit_part_5_imp_10_GrooveGuy_Script_80226DEC_10 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    ExecWait(b_area_omo_groove_guy_EVS_PerformSummonDance)
    Call(UseBattleCamPreset, 3)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SummonEnemy, Ref(TTYD64_pit_part_5_imp_10_GrooveGuy_SpecialFormation_802273C4_10), 0)
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

// clang-format off
EvtScript TTYD64_pit_part_5_imp_10_GrooveGuy_Script_TakeTurn_80226338_10 = {
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
                ExecWait(TTYD64_pit_part_5_imp_10_GrooveGuy_Script_RandomSummon_10)
                Return
            EndIf
        CaseEq(2)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 150)
                ExecWait(TTYD64_pit_part_5_imp_10_GrooveGuy_Script_RandomSummon_10)
                Return
            EndIf
        CaseEq(3)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 100)
                ExecWait(TTYD64_pit_part_5_imp_10_GrooveGuy_Script_RandomSummon_10)
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
EvtScript TTYD64_pit_part_5_imp_10_GrooveGuy_Script_802271A0_10 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    ExecWait(b_area_omo_groove_guy_EVS_PerformSummonDance)
    Call(SummonEnemy, Ref(TTYD64_pit_part_5_imp_10_GrooveGuy_SpecialFormation_802273E0_10), 0)
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
EvtScript TTYD64_pit_part_5_imp_10_GrooveGuy_Script_80226C00_10 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    ExecWait(b_area_omo_groove_guy_EVS_PerformSummonDance)
    Call(SummonEnemy, Ref(TTYD64_pit_part_5_imp_10_GrooveGuy_SpecialFormation_802273A8_10), 0)
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

Battle TTYD64_pit_part_5_FormationTable[] = {
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_5_Formation_Pit41_46_1,
      .stage = &TTYD64_pit_part_5_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_5_Formation_Pit41_46_2,
      .stage = &TTYD64_pit_part_5_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_5_Formation_Pit41_46_3,
      .stage = &TTYD64_pit_part_5_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_5_Formation_Pit42_47_1,
      .stage = &TTYD64_pit_part_5_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_5_Formation_Pit42_47_2,
      .stage = &TTYD64_pit_part_5_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_5_Formation_Pit42_47_3,
      .stage = &TTYD64_pit_part_5_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_5_Formation_Pit43_48_1,
      .stage = &TTYD64_pit_part_5_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_5_Formation_Pit43_48_2,
      .stage = &TTYD64_pit_part_5_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_5_Formation_Pit43_48_3,
      .stage = &TTYD64_pit_part_5_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_5_Formation_Pit44_49_1,
      .stage = &TTYD64_pit_part_5_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_5_Formation_Pit44_49_2,
      .stage = &TTYD64_pit_part_5_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_5_Formation_Pit44_49_3,
      .stage = &TTYD64_pit_part_5_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_5_Formation_Pit45_1,
      .stage = &TTYD64_pit_part_5_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_5_Formation_Pit45_2,
      .stage = &TTYD64_pit_part_5_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_5_Formation_Pit45_3,
      .stage = &TTYD64_pit_part_5_Stage_Pit1,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_pit_part_5_imp_10_GrooveGuy_Script_RandomSummon_10 = {
    Call(UseBattleCamPreset, 11)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(RandInt, 2, LVar1)
    Switch(LVar1)
        CaseEq(0)
            ExecWait(TTYD64_pit_part_5_imp_10_GrooveGuy_Script_80226C00_10)
        CaseEq(1)
            ExecWait(TTYD64_pit_part_5_imp_10_GrooveGuy_Script_80226DEC_10)
        CaseEq(2)
            ExecWait(TTYD64_pit_part_5_imp_10_GrooveGuy_Script_802271A0_10)
    EndSwitch
    Call(UseBattleCamPreset, 2)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_omo_groove_guy_DefaultAnims))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_pit_part_5_Script_BeforeBattle_Pit = {
    Call(EnableGroup, 26, 0)
    Switch(AreaByte(0))
        CaseGe(80)
            Call(EnableGroup, 25, 1)
        CaseGe(50)
            Call(EnableGroup, 19, 1)
        CaseDefault
            Call(EnableGroup, 13, 1)
    EndSwitch
    Call(SetSpriteShading, -1)
    Call(SetCamBGColor, 1, 0, 0, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pit_part_5_Formation_Pit45_2[] = {
    { .actor = &TTYD64_pit_part_5_imp_10_PyroGuy_10_PyroGuy,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_PyroGuy_10_PyroGuy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_GrooveGuy_10_GrooveGuy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_GrooveGuy_10_GrooveGuy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
};

FormationRow TTYD64_pit_part_5_Formation_Pit45_3[] = {
    { .actor = &TTYD64_pit_part_5_imp_10_PyroGuy_10_PyroGuy,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_PyroGuy_10_PyroGuy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_PyroGuy_10_PyroGuy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_PyroGuy_10_PyroGuy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
};

FormationRow TTYD64_pit_part_5_Formation_Pit42_47_3[] = {
    { .actor = &TTYD64_pit_part_5_imp_10_ShyGuy_RED_10_ShyGuy_RED,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_ShyGuy_RED_10_ShyGuy_RED,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_ShyGuy_RED_10_ShyGuy_RED,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_ShyGuy_RED_10_ShyGuy_RED,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
};

FormationRow TTYD64_pit_part_5_Formation_Pit43_48_3[] = {
    { .actor = &TTYD64_pit_part_5_imp_10_GrooveGuy_10_GrooveGuy,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_SpyGuy_10_SpyGuy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_GrooveGuy_10_GrooveGuy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_SpyGuy_10_SpyGuy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
};

FormationRow TTYD64_pit_part_5_Formation_Pit44_49_2[] = {
    { .actor = &TTYD64_pit_part_5_imp_10_SpyGuy_10_SpyGuy,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_PyroGuy_10_PyroGuy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_SpyGuy_10_SpyGuy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_PyroGuy_10_PyroGuy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
};

FormationRow TTYD64_pit_part_5_Formation_Pit44_49_3[] = {
    { .actor = &TTYD64_pit_part_5_imp_10_SpyGuy_10_SpyGuy,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_SpyGuy_10_SpyGuy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_SpyGuy_10_SpyGuy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_SpyGuy_10_SpyGuy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
};

FormationRow TTYD64_pit_part_5_Formation_Pit41_46_3[] = {
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 4 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
};

// clang-format off
EvtScript TTYD64_pit_part_5_imp_10_GrooveGuy_Script_Init_80224B38_10 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_pit_part_5_imp_10_GrooveGuy_Script_TakeTurn_80226338_10))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo_groove_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo_groove_guy_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pit_part_5_Formation_Pit43_48_1[] = {
    { .actor = &TTYD64_pit_part_5_imp_10_GrooveGuy_10_GrooveGuy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_GrooveGuy_10_GrooveGuy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_GrooveGuy_10_GrooveGuy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
};

FormationRow TTYD64_pit_part_5_Formation_Pit43_48_2[] = {
    { .actor = &TTYD64_pit_part_5_imp_10_GrooveGuy_10_GrooveGuy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_GrooveGuy_10_GrooveGuy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_GROOVEGUY },
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 7 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
};

FormationRow TTYD64_pit_part_5_Formation_Pit41_46_2[] = {
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
    { .actor = &TTYD64_pit_part_5_imp_10_ShyGuy_RED_10_ShyGuy_RED,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
};

FormationRow TTYD64_pit_part_5_Formation_Pit41_46_1[] = {
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 5 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
    { .actor = &TTYD64_pit_part_5_imp_10_SpyGuy_10_SpyGuy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
};

FormationRow TTYD64_pit_part_5_Formation_Pit45_1[] = {
    { .actor = &TTYD64_pit_part_5_imp_10_PyroGuy_10_PyroGuy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_PyroGuy_10_PyroGuy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PYROGUY },
};

FormationRow TTYD64_pit_part_5_Formation_Pit42_47_1[] = {
    { .actor = &TTYD64_pit_part_5_imp_10_ShyGuy_RED_10_ShyGuy_RED,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_ShyGuy_RED_10_ShyGuy_RED,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
};

FormationRow TTYD64_pit_part_5_Formation_Pit42_47_2[] = {
    { .actor = &TTYD64_pit_part_5_imp_10_ShyGuy_RED_10_ShyGuy_RED,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SHYGUY },
    { .actor = &TTYD64_pit_part_5_imp_10_SpyGuy_10_SpyGuy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
};

FormationRow TTYD64_pit_part_5_Formation_Pit44_49_1[] = {
    { .actor = &TTYD64_pit_part_5_imp_10_SpyGuy_10_SpyGuy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPYGUY },
    { .actor = &TTYD64_imp_1A_DarkParatroopa_1A_DarkParatroopa,
      .home = { .index = 6 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_DARKPARATROOPA },
};

ActorBlueprint TTYD64_pit_part_5_imp_10_MediGuy_10_MediGuy = {
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

Stage TTYD64_pit_part_5_Stage_Pit1 = {
    .texture = "tik_tex",
    .shape = "pit_bt01_shape",
    .hit = "pit_bt01_hit",
    .preBattle = &TTYD64_pit_part_5_Script_BeforeBattle_Pit,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

Stage TTYD64_pit_part_5_Stage_Pit2 = {
    .texture = "tik_tex",
    .shape = "pit_bt02_shape",
    .hit = "pit_bt02_hit",
    .preBattle = &b_area_kmr_part_3_kpa_13_EVS_PreBattle,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

ActorBlueprint TTYD64_pit_part_5_imp_10_ShyGuy_RED_10_ShyGuy_RED = {
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

ActorBlueprint TTYD64_pit_part_5_imp_10_GrooveGuy_10_GrooveGuy = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x20,
    .level = 15,
    .partCount = 1,
    .partsData = TTYD64_omo_groove_guy_ActorParts,
    .initScript = &TTYD64_pit_part_5_imp_10_GrooveGuy_Script_Init_80224B38_10,
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

ActorBlueprint TTYD64_pit_part_5_imp_10_SpyGuy_10_SpyGuy = {
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

ActorBlueprint TTYD64_pit_part_5_imp_10_PyroGuy_10_PyroGuy = {
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

FormationRow TTYD64_pit_part_5_imp_10_GrooveGuy_SpecialFormation_802273E0_10[] = {
    { .actor = &TTYD64_pit_part_5_imp_10_MediGuy_10_MediGuy,
      .home = { .vec = &b_area_omo_groove_guy_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pit_part_5_imp_10_GrooveGuy_SpecialFormation_802273C4_10[] = {
    { .actor = &TTYD64_pit_part_5_imp_10_GrooveGuy_10_GrooveGuy,
      .home = { .vec = &b_area_omo_groove_guy_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_pit_part_5_imp_10_GrooveGuy_SpecialFormation_802273A8_10[] = {
    { .actor = &TTYD64_pit_part_5_imp_10_ShyGuy_RED_10_ShyGuy_RED,
      .home = { .vec = &b_area_omo_groove_guy_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

StageListRow TTYD64_pit_part_5_StageTable[] = {
    { .name = "pit_01", .stage = &TTYD64_pit_part_5_Stage_Pit1 },
    { .name = "pit_12", .stage = &TTYD64_pit_part_5_Stage_Pit2 },
    {},
};

void TTYD64_InstallBattles_pit_part_5(void) {
    Mod_SetBattleList("TTYD64", 0x34, TTYD64_pit_part_5_FormationTable);
    Mod_SetStageList("TTYD64", 0x34, TTYD64_pit_part_5_StageTable);
}
