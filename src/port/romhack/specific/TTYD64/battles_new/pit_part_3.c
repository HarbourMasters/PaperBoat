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
#include "battles_new.h"

extern s32 b_area_isk_part_1_stone_chomp_StatusTable[];
extern EvtScript b_area_kmr_part_1_kmr_02_EVS_PostBattle;
extern EvtScript b_area_kmr_part_3_kpa_13_EVS_PreBattle;
extern EvtScript b_area_mim_forest_fuzzy_EVS_CountSummoners;
extern EvtScript b_area_mim_forest_fuzzy_EVS_GetAvailableSpawnPos;
extern EvtScript b_area_mim_forest_fuzzy_EVS_Idle;
extern Vec3i b_area_mim_forest_fuzzy_SummonPos;
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(ForceHomePos);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(HPBarToHome);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
extern ActorBlueprint TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba;
extern s32 TTYD64_imp_1A_SpikedGloomba_IdleAnimations_80223CE4_1A[];
extern s32 TTYD64_imp_1A_SpikedGloomba_IdleAnimations_80223D30_1A[];
extern ActorPartBlueprint TTYD64_imp_1A_SpikedGloomba_PartsTable_80223C98_1A[];
extern EvtScript TTYD64_imp_1A_SpikedGloomba_Script_HandleEvent_802240A4_1A;
extern EvtScript TTYD64_imp_1A_SpikedGloomba_Script_Idle_80223DC8_1A;
extern EvtScript TTYD64_imp_1A_SpikedGloomba_Script_Init_80223D7C_1A;
extern EvtScript TTYD64_imp_1A_SpikedGloomba_Script_TakeTurn_802249EC_1A;
extern ActorPartBlueprint TTYD64_isk_part_1_buzzy_beetle_ActorParts[];
extern s32 TTYD64_isk_part_1_buzzy_beetle_CeilingAnims[];
extern EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_FallFromCeiling;
extern EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_HandleEvent_Ceiling;
extern EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_HandleEvent_Ground;
extern EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_Init;
extern EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_TakeTurn_Ceiling;
extern EvtScript TTYD64_isk_part_1_buzzy_beetle_EVS_TakeTurn_Ground;
extern s32 TTYD64_isk_part_1_buzzy_beetle_GroundAnims[];
extern s32 TTYD64_isk_part_1_buzzy_beetle_StatusTable[];
extern s32 TTYD64_isk_part_1_buzzy_beetle_ToppledAnims[];
extern ActorPartBlueprint TTYD64_isk_part_1_stone_chomp_ActorParts[];
extern s32 TTYD64_isk_part_1_stone_chomp_BasicAnims[];
extern s32 TTYD64_isk_part_1_stone_chomp_BiteAnims[];
extern EvtScript TTYD64_isk_part_1_stone_chomp_EVS_HandleEvent;
extern EvtScript TTYD64_isk_part_1_stone_chomp_EVS_Idle;
extern EvtScript TTYD64_isk_part_1_stone_chomp_EVS_Init;
extern EvtScript TTYD64_isk_part_1_stone_chomp_EVS_TakeTurn;
extern s32 TTYD64_isk_part_1_stone_chomp_QuickBiteAnims[];
extern s32 TTYD64_isk_part_1_stone_chomp_SlowBiteAnims[];
extern ActorPartBlueprint TTYD64_mim_forest_fuzzy_ActorParts[];
extern s32 TTYD64_mim_forest_fuzzy_DefaultAnims[];
extern EvtScript TTYD64_mim_forest_fuzzy_EVS_Attack_Leech;
extern EvtScript TTYD64_mim_forest_fuzzy_EVS_HandleEvent;
extern s32 TTYD64_mim_forest_fuzzy_StatusTable[];
extern ActorPartBlueprint TTYD64_mim_piranha_plant_ActorParts[];
extern s32 TTYD64_mim_piranha_plant_DefaultAnims[];
extern EvtScript TTYD64_mim_piranha_plant_EVS_Init;
extern EvtScript TTYD64_mim_piranha_plant_EVS_TakeTurn;
extern s32 TTYD64_mim_piranha_plant_StatusTable[];
extern EvtScript TTYD64_pit_part_3_imp_0D_ForestFuzzy_Script_80218C48_0D;
extern EvtScript TTYD64_pit_part_3_imp_0D_ForestFuzzy_Script_TakeTurn_8021A61C_0D;
extern Battle TTYD64_pit_part_3_FormationTable[];
extern EvtScript TTYD64_pit_part_3_Script_BeforeBattle_Pit;
extern FormationRow TTYD64_pit_part_3_Formation_Pit21_26_2[];
extern FormationRow TTYD64_pit_part_3_Formation_Pit21_26_3[];
extern FormationRow TTYD64_pit_part_3_Formation_Pit22_27_3[];
extern FormationRow TTYD64_pit_part_3_Formation_Pit22_27_2[];
extern FormationRow TTYD64_pit_part_3_Formation_Pit25_3[];
extern FormationRow TTYD64_pit_part_3_Formation_Pit24_29_3[];
extern FormationRow TTYD64_pit_part_3_Formation_Pit25_2[];
extern FormationRow TTYD64_pit_part_3_Formation_Pit23_28_2[];
extern FormationRow TTYD64_pit_part_3_Formation_Pit23_28_3[];
extern EvtScript TTYD64_pit_part_3_imp_0D_ForestFuzzy_Script_Init_80218510_0D;
extern FormationRow TTYD64_pit_part_3_Formation_Pit21_26_1[];
extern FormationRow TTYD64_pit_part_3_Formation_Pit24_29_2[];
extern FormationRow TTYD64_pit_part_3_Formation_Pit25_1[];
extern FormationRow TTYD64_pit_part_3_Formation_Pit22_27_1[];
extern FormationRow TTYD64_pit_part_3_Formation_Pit24_29_1[];
extern FormationRow TTYD64_pit_part_3_Formation_Pit23_28_1[];
extern ActorBlueprint TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy;
extern ActorBlueprint TTYD64_pit_part_3_imp_0B_StoneChomp_0B_StoneChomp;
extern Stage TTYD64_pit_part_3_Stage_Pit1;
extern Stage TTYD64_pit_part_3_Stage_Pit2;
extern ActorBlueprint TTYD64_pit_part_3_imp_0D_ForestFuzzy_ForestFuzzy_0D;
extern ActorBlueprint TTYD64_pit_part_3_imp_0B_BuzzyBeetle_0B_BuzzyBeetle;
extern ActorBlueprint TTYD64_pit_part_3_imp_0D_PiranhaPlant_0D_PiranhaPlant;
extern FormationRow TTYD64_pit_part_3_imp_0D_ForestFuzzy_SpecialFormation_8021A800_0D[];
extern StageListRow TTYD64_pit_part_3_StageTable[];

// clang-format off
EvtScript TTYD64_pit_part_3_imp_0D_ForestFuzzy_Script_80218C48_0D = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B010D)
    Wait(130)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0102)
    Call(SummonEnemy, Ref(TTYD64_pit_part_3_imp_0D_ForestFuzzy_SpecialFormation_8021A800_0D), 0)
    Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
    Call(SetActorPos, LVar0, LVar1, LVar2, LVar3)
    Call(SetGoalToIndex, LVar0, LVarA)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x2B0102)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(1.400390625))
        Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
        Call(SetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
        Call(JumpToGoal, ACTOR_SELF, 14, 0, 1, 0)
    EndThread
    Wait(1)
    Call(SetAnimation, LVar0, 1, 0x2B0102)
    Call(SetActorJumpGravity, LVar0, Float(1.400390625))
    Call(JumpToGoal, LVar0, 14, 0, 1, 0)
    Call(GetActorPos, LVar0, LVar1, LVar2, LVar3)
    Call(ForceHomePos, LVar0, LVar1, LVar2, LVar3)
    Call(HPBarToHome, LVar0)
    Call(SetAnimation, LVar0, 1, 0x2B0101)
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
EvtScript TTYD64_pit_part_3_imp_0D_ForestFuzzy_Script_TakeTurn_8021A61C_0D = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_mim_forest_fuzzy_EVS_Attack_Leech)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 2)
        ExecWait(TTYD64_mim_forest_fuzzy_EVS_Attack_Leech)
        Return
    EndIf
    ExecWait(b_area_mim_forest_fuzzy_EVS_GetAvailableSpawnPos)
    IfEq(LVarA, -1)
        ExecWait(TTYD64_mim_forest_fuzzy_EVS_Attack_Leech)
        Return
    EndIf
    ExecWait(b_area_mim_forest_fuzzy_EVS_CountSummoners)
    Switch(LVar9)
        CaseEq(1)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 300)
                ExecWait(TTYD64_pit_part_3_imp_0D_ForestFuzzy_Script_80218C48_0D)
                Return
            EndIf
        CaseEq(2)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 150)
                ExecWait(TTYD64_pit_part_3_imp_0D_ForestFuzzy_Script_80218C48_0D)
                Return
            EndIf
        CaseEq(3)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 100)
                ExecWait(TTYD64_pit_part_3_imp_0D_ForestFuzzy_Script_80218C48_0D)
                Return
            EndIf
    EndSwitch
    ExecWait(TTYD64_mim_forest_fuzzy_EVS_Attack_Leech)
    Return
    End
};
// clang-format on

Battle TTYD64_pit_part_3_FormationTable[] = {
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_3_Formation_Pit21_26_1,
      .stage = &TTYD64_pit_part_3_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_3_Formation_Pit21_26_2,
      .stage = &TTYD64_pit_part_3_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_3_Formation_Pit21_26_3,
      .stage = &TTYD64_pit_part_3_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_3_Formation_Pit22_27_1,
      .stage = &TTYD64_pit_part_3_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_3_Formation_Pit22_27_2,
      .stage = &TTYD64_pit_part_3_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_3_Formation_Pit22_27_3,
      .stage = &TTYD64_pit_part_3_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_3_Formation_Pit23_28_1,
      .stage = &TTYD64_pit_part_3_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_3_Formation_Pit23_28_2,
      .stage = &TTYD64_pit_part_3_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_3_Formation_Pit23_28_3,
      .stage = &TTYD64_pit_part_3_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 2,
      .formation = (Formation*) TTYD64_pit_part_3_Formation_Pit24_29_1,
      .stage = &TTYD64_pit_part_3_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_3_Formation_Pit24_29_2,
      .stage = &TTYD64_pit_part_3_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_3_Formation_Pit24_29_3,
      .stage = &TTYD64_pit_part_3_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 3,
      .formation = (Formation*) TTYD64_pit_part_3_Formation_Pit25_1,
      .stage = &TTYD64_pit_part_3_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_3_Formation_Pit25_2,
      .stage = &TTYD64_pit_part_3_Stage_Pit1,
      .onBattleStart = NULL },
    { .name = NULL,
      .formationSize = 4,
      .formation = (Formation*) TTYD64_pit_part_3_Formation_Pit25_3,
      .stage = &TTYD64_pit_part_3_Stage_Pit1,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_pit_part_3_Script_BeforeBattle_Pit = {
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

FormationRow TTYD64_pit_part_3_Formation_Pit21_26_2[] = {
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
    { .actor = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
};

FormationRow TTYD64_pit_part_3_Formation_Pit21_26_3[] = {
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
    { .actor = &TTYD64_pit_part_3_imp_0D_PiranhaPlant_0D_PiranhaPlant,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_pit_part_3_imp_0B_BuzzyBeetle_0B_BuzzyBeetle,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
};

FormationRow TTYD64_pit_part_3_Formation_Pit22_27_3[] = {
    { .actor = &TTYD64_pit_part_3_imp_0B_BuzzyBeetle_0B_BuzzyBeetle,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_pit_part_3_imp_0B_BuzzyBeetle_0B_BuzzyBeetle,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_pit_part_3_imp_0B_BuzzyBeetle_0B_BuzzyBeetle,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_pit_part_3_imp_0B_BuzzyBeetle_0B_BuzzyBeetle,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
};

FormationRow TTYD64_pit_part_3_Formation_Pit22_27_2[] = {
    { .actor = &TTYD64_pit_part_3_imp_0B_BuzzyBeetle_0B_BuzzyBeetle,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_pit_part_3_imp_0B_BuzzyBeetle_0B_BuzzyBeetle,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
};

FormationRow TTYD64_pit_part_3_Formation_Pit25_3[] = {
    { .actor = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
};

FormationRow TTYD64_pit_part_3_Formation_Pit24_29_3[] = {
    { .actor = &TTYD64_pit_part_3_imp_0D_PiranhaPlant_0D_PiranhaPlant,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_pit_part_3_imp_0D_PiranhaPlant_0D_PiranhaPlant,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_pit_part_3_imp_0D_PiranhaPlant_0D_PiranhaPlant,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_pit_part_3_imp_0D_PiranhaPlant_0D_PiranhaPlant,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
};

FormationRow TTYD64_pit_part_3_Formation_Pit25_2[] = {
    { .actor = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_pit_part_3_imp_0B_BuzzyBeetle_0B_BuzzyBeetle,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_pit_part_3_imp_0B_BuzzyBeetle_0B_BuzzyBeetle,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
};

FormationRow TTYD64_pit_part_3_Formation_Pit23_28_2[] = {
    { .actor = &TTYD64_pit_part_3_imp_0B_StoneChomp_0B_StoneChomp,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_STONECHOMP },
    { .actor = &TTYD64_pit_part_3_imp_0D_PiranhaPlant_0D_PiranhaPlant,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_pit_part_3_imp_0D_PiranhaPlant_0D_PiranhaPlant,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_pit_part_3_imp_0B_StoneChomp_0B_StoneChomp,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_STONECHOMP },
};

FormationRow TTYD64_pit_part_3_Formation_Pit23_28_3[] = {
    { .actor = &TTYD64_pit_part_3_imp_0B_StoneChomp_0B_StoneChomp,
      .home = { .index = 0 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_STONECHOMP },
    { .actor = &TTYD64_pit_part_3_imp_0B_StoneChomp_0B_StoneChomp,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_STONECHOMP },
    { .actor = &TTYD64_pit_part_3_imp_0B_StoneChomp_0B_StoneChomp,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_STONECHOMP },
    { .actor = &TTYD64_pit_part_3_imp_0B_StoneChomp_0B_StoneChomp,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_STONECHOMP },
};

// clang-format off
EvtScript TTYD64_pit_part_3_imp_0D_ForestFuzzy_Script_Init_80218510_0D = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_pit_part_3_imp_0D_ForestFuzzy_Script_TakeTurn_8021A61C_0D))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mim_forest_fuzzy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mim_forest_fuzzy_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_pit_part_3_Formation_Pit21_26_1[] = {
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
    { .actor = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
};

FormationRow TTYD64_pit_part_3_Formation_Pit24_29_2[] = {
    { .actor = &TTYD64_pit_part_3_imp_0D_PiranhaPlant_0D_PiranhaPlant,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_pit_part_3_imp_0D_PiranhaPlant_0D_PiranhaPlant,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
};

FormationRow TTYD64_pit_part_3_Formation_Pit25_1[] = {
    { .actor = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 3 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
};

FormationRow TTYD64_pit_part_3_Formation_Pit22_27_1[] = {
    { .actor = &TTYD64_pit_part_3_imp_0B_BuzzyBeetle_0B_BuzzyBeetle,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BUZZYBEETLE },
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
};

FormationRow TTYD64_pit_part_3_Formation_Pit24_29_1[] = {
    { .actor = &TTYD64_pit_part_3_imp_0D_PiranhaPlant_0D_PiranhaPlant,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
};

FormationRow TTYD64_pit_part_3_Formation_Pit23_28_1[] = {
    { .actor = &TTYD64_pit_part_3_imp_0B_StoneChomp_0B_StoneChomp,
      .home = { .index = 1 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_STONECHOMP },
    { .actor = &TTYD64_imp_1A_SpikedGloomba_1A_SpikedGloomba,
      .home = { .index = 2 },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_SPIKEDGLOOMBA },
};

ActorBlueprint TTYD64_pit_part_3_imp_0D_ForestFuzzy_0D_ForestFuzzy = {
    .flags = 0x0,
    .maxHP = 6,
    .type = 0x1A,
    .level = 11,
    .partCount = 1,
    .partsData = TTYD64_mim_forest_fuzzy_ActorParts,
    .initScript = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_Script_Init_80218510_0D,
    .statusTable = TTYD64_mim_forest_fuzzy_StatusTable,
    .escapeChance = 40,
    .airLiftChance = 90,
    .hurricaneChance = 90,
    .spookChance = 85,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 33, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_pit_part_3_imp_0B_StoneChomp_0B_StoneChomp = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x18,
    .level = 14,
    .partCount = 10,
    .partsData = TTYD64_isk_part_1_stone_chomp_ActorParts,
    .initScript = &TTYD64_isk_part_1_stone_chomp_EVS_Init,
    .statusTable = b_area_isk_part_1_stone_chomp_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 25,
    .hurricaneChance = 25,
    .spookChance = 0,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 5,
    .size = { 56, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

Stage TTYD64_pit_part_3_Stage_Pit1 = {
    .texture = "tik_tex",
    .shape = "pit_bt01_shape",
    .hit = "pit_bt01_hit",
    .preBattle = &TTYD64_pit_part_3_Script_BeforeBattle_Pit,
    .postBattle = &b_area_kmr_part_1_kmr_02_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

Stage TTYD64_pit_part_3_Stage_Pit2 = {
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

ActorBlueprint TTYD64_pit_part_3_imp_0D_ForestFuzzy_ForestFuzzy_0D = {
    .flags = 0x0,
    .maxHP = 6,
    .type = 0x1A,
    .level = 11,
    .partCount = 1,
    .partsData = TTYD64_mim_forest_fuzzy_ActorParts,
    .initScript = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_Script_Init_80218510_0D,
    .statusTable = TTYD64_mim_forest_fuzzy_StatusTable,
    .escapeChance = 40,
    .airLiftChance = 90,
    .hurricaneChance = 90,
    .spookChance = 85,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 33, 28 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_pit_part_3_imp_0B_BuzzyBeetle_0B_BuzzyBeetle = {
    .flags = 0x800,
    .maxHP = 3,
    .type = 0x17,
    .level = 10,
    .partCount = 1,
    .partsData = TTYD64_isk_part_1_buzzy_beetle_ActorParts,
    .initScript = &TTYD64_isk_part_1_buzzy_beetle_EVS_Init,
    .statusTable = TTYD64_isk_part_1_buzzy_beetle_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 75,
    .hurricaneChance = 75,
    .spookChance = 75,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 22, 18 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -8, 16 },
    .statusTextOffset = { 8, 13 },
};

ActorBlueprint TTYD64_pit_part_3_imp_0D_PiranhaPlant_0D_PiranhaPlant = {
    .flags = 0x0,
    .maxHP = 5,
    .type = 0x19,
    .level = 11,
    .partCount = 1,
    .partsData = TTYD64_mim_piranha_plant_ActorParts,
    .initScript = &TTYD64_mim_piranha_plant_EVS_Init,
    .statusTable = TTYD64_mim_piranha_plant_StatusTable,
    .escapeChance = 70,
    .airLiftChance = 20,
    .hurricaneChance = 20,
    .spookChance = 40,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 38, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -7, 33 },
    .statusTextOffset = { 10, 33 },
};

FormationRow TTYD64_pit_part_3_imp_0D_ForestFuzzy_SpecialFormation_8021A800_0D[] = {
    { .actor = &TTYD64_pit_part_3_imp_0D_ForestFuzzy_ForestFuzzy_0D,
      .home = { .vec = &b_area_mim_forest_fuzzy_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

StageListRow TTYD64_pit_part_3_StageTable[] = {
    { .name = "pit_01", .stage = &TTYD64_pit_part_3_Stage_Pit1 },
    { .name = "pit_12", .stage = &TTYD64_pit_part_3_Stage_Pit2 },
    {},
};

void TTYD64_InstallBattles_pit_part_3(void) {
    Mod_SetBattleList("TTYD64", 0x32, TTYD64_pit_part_3_FormationTable);
    Mod_SetStageList("TTYD64", 0x32, TTYD64_pit_part_3_StageTable);
}
