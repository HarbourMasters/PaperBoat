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
#include "port/romhack/specific/TTYD64/battle/area/battles_a.h"

API_CALLABLE(ActorExists);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(CancelEnemyTurn);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnableModel);
API_CALLABLE(EndActorSpeech);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyPartTo);
API_CALLABLE(ForceHomePos);
API_CALLABLE(FreezeBattleState);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetCurrentPartnerID);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetModelCenter);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToHome);
API_CALLABLE(JumpPartTo);
API_CALLABLE(LoadAnimatedModel);
API_CALLABLE(LoadBattleSection);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlayModelAnimation);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlaySoundAtPart);
API_CALLABLE(RandInt);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimatedModelRootPosition);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetDarknessMode);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartTargetFlagBits);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTargetActor);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(b_area_omo2_general_guy_FadeBackgroundDarken);
API_CALLABLE(b_area_omo2_general_guy_FadeBackgroundLighten);
extern u8 AS_ToyTank_CloseHatch[];
extern u8 AS_ToyTank_Idle[];
extern u8 AS_ToyTank_OpenHatch[];
extern ActorBlueprint b_area_omo2_1_shy_squad;
extern ActorBlueprint b_area_omo2_2_stilt_guy;
extern ActorBlueprint b_area_omo2_3_shy_stack;
extern ActorBlueprint b_area_omo2_4_signal_guy;
extern ActorPartBlueprint b_area_omo2_general_guy_ActorParts[];
extern EvtScript b_area_omo2_general_guy_EVS_HandleEvent;
extern EvtScript b_area_omo2_general_guy_EVS_HandlePhase;
extern EvtScript b_area_omo2_general_guy_EVS_Idle;
extern FormationRow b_area_omo2_general_guy_ShySquadFormation[];
extern s32 b_area_omo2_general_guy_StatusTable[];
extern ActorBlueprint b_area_omo2_light_bulb;
extern s32 b_area_omo2_light_bulb_StatusTable[];
extern EvtScript b_area_omo2_omo_07_EVS_PostBattle;
extern ActorPartBlueprint b_area_omo2_toy_tank_ActorParts[];
extern EvtScript b_area_omo2_toy_tank_EVS_BeginWave_ShyStacks;
extern EvtScript b_area_omo2_toy_tank_EVS_BeginWave_StiltGuys;
extern EvtScript b_area_omo2_toy_tank_EVS_BeginWave_Tank;
extern EvtScript b_area_omo2_toy_tank_EVS_HandleEvent;
extern EvtScript b_area_omo2_toy_tank_EVS_Idle;
extern EvtScript b_area_omo2_toy_tank_EVS_IncrementWavesDefeated;
extern EvtScript b_area_omo2_toy_tank_EVS_ManageDarkness;
extern EvtScript b_area_omo2_toy_tank_EVS_TakeTurn;
extern FormationRow b_area_omo2_toy_tank_LeftShyStackFormation[];
extern FormationRow b_area_omo2_toy_tank_LeftStiltGuyFormation[];
extern FormationRow b_area_omo2_toy_tank_RightShyStackFormation[];
extern FormationRow b_area_omo2_toy_tank_RightStiltGuyFormation[];
extern FormationRow b_area_omo2_toy_tank_SignalGuyFormation[];
extern Vec3i b_area_omo2_toy_tank_SummonPos;
extern u8 toy_tank_model[];
extern ActorBlueprint TTYD64_omo2_general_guy;
extern EvtScript TTYD64_omo2_general_guy_EVS_Init;
extern EvtScript TTYD64_omo2_general_guy_EVS_TakeTurn;
extern ActorBlueprint TTYD64_omo2_toy_tank;
extern EvtScript TTYD64_omo2_toy_tank_EVS_Init;
extern EvtScript TTYD64_omo2_toy_tank_EVS_ManageTroopWaves;
extern EvtScript TTYD64_omo2_toy_tank_EVS_BeginWave_ShySquadRedux;
extern Stage TTYD64_omo2_omo_07;
extern EvtScript TTYD64_omo2_omo_07_EVS_PreBattle;
extern EvtScript TTYD64_omo2_general_guy_EVS_Attack_ThrowBomb;
extern EvtScript TTYD64_omo2_general_guy_EVS_Attack_ShootLightning;
extern FormationRow TTYD64_omo2_toy_tank_ShySquadReduxFormation[];
extern FormationRow TTYD64_omo2_Formation_01[];
extern Battle TTYD64_omo2_Formations[];
extern StageListRow TTYD64_omo2_Stages[];

ActorBlueprint TTYD64_omo2_general_guy = {
    .flags = 0x40000,
    .maxHP = 10,
    .type = 0xA9,
    .level = 73,
    .partCount = 2,
    .partsData = b_area_omo2_general_guy_ActorParts,
    .initScript = &TTYD64_omo2_general_guy_EVS_Init,
    .statusTable = b_area_omo2_general_guy_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 30, 30 },
    .healthBarOffset = { 20, -3 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

// clang-format off
EvtScript TTYD64_omo2_general_guy_EVS_Init = {
    Call(SetActorPos, ACTOR_SELF, 200, 0, 0)
    Call(ForceHomePos, ACTOR_SELF, 200, 0, 0)
    Call(HPBarToHome, ACTOR_SELF)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo2_general_guy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo2_general_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo2_general_guy_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_omo2_general_guy_EVS_HandlePhase))
    Call(SetAnimation, ACTOR_SELF, 1, 0x760002)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(LoadBattleSection, 41)
    Call(SummonEnemy, Ref(b_area_omo2_general_guy_ShySquadFormation), 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_general_guy_EVS_TakeTurn = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(ActorExists, 514, LVar0)
    IfNe(LVar0, 0)
        Call(GetStatusFlags, 256, LVar0)
        IfNotFlag(LVar0, 0x1000000)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 60)
                ExecWait(TTYD64_omo2_general_guy_EVS_Attack_ShootLightning)
                Return
            EndIf
        EndIf
    EndIf
    ExecWait(TTYD64_omo2_general_guy_EVS_Attack_ThrowBomb)
    Return
    End
};
// clang-format on

ActorBlueprint TTYD64_omo2_toy_tank = {
    .flags = 0x40004,
    .maxHP = 30,
    .type = 0xAA,
    .level = 0,
    .partCount = 3,
    .partsData = b_area_omo2_toy_tank_ActorParts,
    .initScript = &TTYD64_omo2_toy_tank_EVS_Init,
    .statusTable = b_area_omo2_light_bulb_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 48, 78 },
    .healthBarOffset = { 20, -3 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

// clang-format off
EvtScript TTYD64_omo2_toy_tank_EVS_Init = {
    Call(SetActorVar, ACTOR_SELF, 0, 1)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 1)
    Call(SetActorVar, ACTOR_SELF, 7, 0)
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(SetActorVar, ACTOR_SELF, 9, 0)
    Call(SetActorDispOffset, 512, 0, 7, 0)
    Call(SetActorPos, ACTOR_SELF, 85, 0, 0)
    Call(SetHomePos, ACTOR_SELF, 85, 0, 0)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetPartPos, ACTOR_SELF, 2, 85, 30, 0)
    Call(SetPartPos, ACTOR_SELF, 3, 80, 0, 0)
    Call(LoadAnimatedModel, 0, Ref(toy_tank_model))
    Call(PlayModelAnimation, 0, Ref(AS_ToyTank_Idle))
    Call(EnableModel, 62, 0)
    Call(SetAnimatedModelRootPosition, 0, 200, 0, 0)
    Call(SetPartTargetFlagBits, ACTOR_SELF, 3, 1, 1)
    Call(GetModelCenter, 39)
    Call(PlayEffect_impl, 60, 2, LVar0, LVar1, LVar2, Float(1.0), LVar5, 0, 0, 0, 0, 0, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 5, LVar5)
    Call(BindTakeTurn, ACTOR_SELF, Ref(b_area_omo2_toy_tank_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo2_toy_tank_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo2_toy_tank_EVS_HandleEvent))
    Exec(TTYD64_omo2_toy_tank_EVS_ManageTroopWaves)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_toy_tank_EVS_ManageTroopWaves = {
    Label(0)
    Call(ActorExists, 513, LVar0)
    IfEq(LVar0, 0)
        Goto(99)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 1, 2)
        Call(CancelEnemyTurn, 1)
        ExecWait(b_area_omo2_toy_tank_EVS_IncrementWavesDefeated)
        ExecWait(b_area_omo2_toy_tank_EVS_BeginWave_StiltGuys)
    Else
        Wait(1)
        Goto(0)
    EndIf
    Label(1)
    Call(ActorExists, 513, LVar0)
    IfEq(LVar0, 0)
        Goto(99)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfEq(LVar0, 2)
        Call(SetActorVar, ACTOR_SELF, 2, 3)
        Call(CancelEnemyTurn, 1)
        ExecWait(b_area_omo2_toy_tank_EVS_IncrementWavesDefeated)
        ExecWait(b_area_omo2_toy_tank_EVS_BeginWave_ShyStacks)
    Else
        Wait(1)
        Goto(1)
    EndIf
    Label(2)
    Call(ActorExists, 513, LVar0)
    IfEq(LVar0, 0)
        Goto(99)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    IfNe(LVar0, 2)
        Wait(1)
        Goto(2)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 4, 2)
    Call(CancelEnemyTurn, 1)
    Call(SetActorVar, 512, 2, 8)
    ExecWait(b_area_omo2_toy_tank_EVS_BeginWave_Tank)
    Goto(99)
    Label(3)
    Call(ActorExists, 513, LVar0)
    IfEq(LVar0, 0)
        Goto(99)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfNe(LVar0, 2)
        Wait(1)
        Goto(3)
    EndIf
    Call(GetCurrentPartnerID, LVar0)
    IfEq(LVar0, 6)
        Call(SetActorVar, ACTOR_SELF, 2, 3)
        Call(SetActorVar, ACTOR_SELF, 3, 0)
        Call(CancelEnemyTurn, 1)
        ExecWait(b_area_omo2_toy_tank_EVS_IncrementWavesDefeated)
        ExecWait(b_area_omo2_toy_tank_EVS_BeginWave_ShyStacks)
        Wait(1)
        Goto(2)
    Else
        Call(SetActorVar, ACTOR_SELF, 3, 3)
        Call(SetActorVar, ACTOR_SELF, 2, 3)
        Call(CancelEnemyTurn, 1)
        Call(SetActorVar, 512, 2, 7)
        ExecWait(TTYD64_omo2_toy_tank_EVS_BeginWave_ShySquadRedux)
        Wait(1)
        Goto(10)
    EndIf
    Label(10)
    Call(ActorExists, 513, LVar0)
    IfEq(LVar0, 0)
        Goto(99)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 4, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, 4, 2)
        Call(CancelEnemyTurn, 1)
        Call(SetActorVar, 512, 2, 8)
        ExecWait(b_area_omo2_toy_tank_EVS_BeginWave_Tank)
    EndIf
    Wait(1)
    Goto(10)
    Label(99)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_toy_tank_EVS_BeginWave_ShySquadRedux = {
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Wait(30)
    Call(SetActorYaw, 512, 180)
    Call(SetAnimation, 512, 1, 0x760003)
    Call(SetActorVar, ACTOR_SELF, 6, 0)
    Wait(10)
    Call(SetDarknessMode, 1)
    Call(SetActorVar, ACTOR_SELF, 7, 1)
    Exec(b_area_omo2_toy_tank_EVS_ManageDarkness)
    Wait(30)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, 512)
    Call(MoveBattleCamOver, 40)
    Wait(20)
    Call(SetBattleCamTargetingModes, 0, 1, 0)
    Call(EndActorSpeech, 512, 1, -1, -1)
    Call(SetAnimation, 512, 1, 0x760002)
    Call(SetActorYaw, 512, 0)
    Wait(20)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Wait(30)
    Call(SetAnimation, 512, 1, 0x760002)
    Call(LoadBattleSection, 45)
    Call(SummonEnemy, Ref(TTYD64_omo2_toy_tank_ShySquadReduxFormation), 1)
    Wait(155)
    Call(UseBattleCamPreset, 14)
    Call(SetBattleCamDist, 350)
    Call(BattleCamTargetActor, 512)
    Call(MoveBattleCamOver, 40)
    Wait(40)
    Call(SetAnimation, 512, 1, 0x760003)
    Call(EndActorSpeech, 512, 1, -1, -1)
    Call(UseBattleCamPreset, 14)
    Call(SetBattleCamDist, 300)
    Call(BattleCamTargetActor, 515)
    Call(MoveBattleCamOver, 30)
    Wait(20)
    Set(LVar0, 2)
    Loop(15)
        Call(RandInt, 3, LVar1)
        Switch(LVar1)
            CaseEq(0)
                Set(LVar1, 0x780008)
            CaseEq(1)
                Set(LVar1, 0x780009)
            CaseEq(2)
                Set(LVar1, 0x78000A)
            CaseDefault
                Set(LVar1, 0x780006)
        EndSwitch
        Call(SetAnimation, 515, LVar0, LVar1)
        Add(LVar0, 1)
    EndLoop
    Call(SetAnimation, 512, 1, 0x760004)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Wait(20)
    Call(SetAnimation, 512, 1, 0x760002)
    Set(LVar0, 2)
    Loop(15)
        Call(SetAnimation, 515, LVar0, 0x780001)
        Add(LVar0, 1)
    EndLoop
    Call(FreezeBattleState, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_omo2_toy_tank_ShySquadReduxFormation[] = {
    { .actor = NULL,
      .home = { .vec = &b_area_omo2_toy_tank_SummonPos },
      .priority = 95,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

Stage TTYD64_omo2_omo_07 = {
    .texture = "omo_tex",
    .shape = "omo_bt07_shape",
    .hit = "omo_bt07_hit",
    .preBattle = &TTYD64_omo2_omo_07_EVS_PreBattle,
    .postBattle = &b_area_omo2_omo_07_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = NULL,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

FormationRow TTYD64_omo2_Formation_01[] = {
    { .actor = &TTYD64_omo2_general_guy,
      .home = { .index = 2 },
      .priority = 70,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_omo2_toy_tank,
      .home = { .index = 1 },
      .priority = 80,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_omo2_light_bulb,
      .home = { .index = 7 },
      .priority = 90,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

Battle TTYD64_omo2_Formations[] = {
    { .name = "\202\265\202\345\202\244\202\256\202\361\203w\203C\203z\201[",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_omo2_Formation_01,
      .stage = &TTYD64_omo2_omo_07,
      .onBattleStart = NULL },
    {},
};

StageListRow TTYD64_omo2_Stages[] = {
    { .name = "omo_07", .stage = &TTYD64_omo2_omo_07 },
    {},
};

// clang-format off
EvtScript TTYD64_omo2_omo_07_EVS_PreBattle = {
    Call(SetSpriteShading, -1)
    Call(SetCamBGColor, 1, 0, 0, 0)
    Call(TTYD64_BattlesA_WriteFormationActor, Ref(b_area_omo2_general_guy_ShySquadFormation), Ref(b_area_omo2_1_shy_squad))
    Call(TTYD64_BattlesA_WriteFormationActor, Ref(b_area_omo2_toy_tank_SignalGuyFormation), Ref(b_area_omo2_4_signal_guy))
    Call(TTYD64_BattlesA_WriteFormationActor, Ref(b_area_omo2_toy_tank_LeftShyStackFormation), Ref(b_area_omo2_3_shy_stack))
    Call(TTYD64_BattlesA_WriteFormationActor, Ref(b_area_omo2_toy_tank_RightShyStackFormation), Ref(b_area_omo2_3_shy_stack))
    Call(TTYD64_BattlesA_WriteFormationActor, Ref(b_area_omo2_toy_tank_LeftStiltGuyFormation), Ref(b_area_omo2_2_stilt_guy))
    Call(TTYD64_BattlesA_WriteFormationActor, Ref(b_area_omo2_toy_tank_RightStiltGuyFormation), Ref(b_area_omo2_2_stilt_guy))
    Call(TTYD64_BattlesA_WriteFormationActor, Ref(TTYD64_omo2_toy_tank_ShySquadReduxFormation), 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_general_guy_EVS_Attack_ThrowBomb = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(SetTargetActor, ACTOR_SELF, 256)
    Else
        Call(SetTargetActor, ACTOR_SELF, 0)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 15)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 30)
    Thread
        Wait(35)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 30)
    EndThread
    Wait(5)
    Call(PlaySoundAtPart, 512, 1, 8298)
    Call(SetAnimation, 512, 1, 0x76000B)
    Call(SetPartFlagBits, 512, 1, 1, 0)
    Set(LVar0, Ref(AS_ToyTank_OpenHatch))
    Call(PlayModelAnimation, 0, LVar0)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x76000B)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 8)
    Add(LVar1, 27)
    Sub(LVar2, 4)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 2, 0x770000)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Wait(15)
    Call(SetAnimation, ACTOR_SELF, 1, 0x76000A)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
    Wait(6)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 8)
    Add(LVar1, 20)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 2, 0x770001)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 4, 32)
    Switch(LVar0)
        CaseEq(6)
            Call(PlaySoundAtPart, 512, 2, 761)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 120)
            Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(12.0))
            Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.099609375))
            Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Call(SetAnimation, 512, 1, 0x760002)
            Call(SetPartFlagBits, 512, 1, 1, 1)
            Set(LVar0, Ref(AS_ToyTank_CloseHatch))
            Call(PlayModelAnimation, 0, LVar0)
            Call(PlaySoundAtPart, 512, 1, 8299)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        CaseEq(5)
            Call(PlaySoundAtPart, 512, 2, 761)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Set(LVar1, -5)
            Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(14.0))
            Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.099609375))
            Call(FlyPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, 30, 0)
            Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            Call(UseBattleCamPreset, 2)
            Call(GetOwnerTarget, LVar3, 0)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Sub(LVar0, 65)
            Set(LVar1, -5)
            Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(6.0))
            Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.099609375))
            Call(FlyPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, 15, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Call(SetAnimation, 512, 1, 0x760002)
            Call(SetPartFlagBits, 512, 1, 1, 1)
            Set(LVar0, Ref(AS_ToyTank_CloseHatch))
            Call(PlayModelAnimation, 0, LVar0)
            Call(PlaySoundAtPart, 512, 1, 8299)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
    EndSwitch
    Call(PlaySoundAtPart, 512, 2, 761)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(14.0))
    Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.099609375))
    Call(FlyPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, 15, 0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(PlayEffect_impl, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtPart, ACTOR_SELF, 2, 8310)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000200, 0, 0, 4, 32)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x760002)
            Wait(30)
            IfEq(LVarF, 10)
                Call(SetAnimation, 512, 1, 0x760002)
                Call(SetPartFlagBits, 512, 1, 1, 1)
                Set(LVar0, Ref(AS_ToyTank_CloseHatch))
                Call(PlayModelAnimation, 0, LVar0)
                Call(PlaySoundAtPart, 512, 1, 8299)
                Return
            EndIf
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, 512, 1, 0x760002)
    Call(SetPartFlagBits, 512, 1, 1, 1)
    Set(LVar0, Ref(AS_ToyTank_CloseHatch))
    Call(PlayModelAnimation, 0, LVar0)
    Call(PlaySoundAtPart, 512, 1, 8299)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_general_guy_EVS_Attack_ShootLightning = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 19)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 320)
    Call(SetBattleCamOffsetY, 30)
    Call(MoveBattleCamOver, 40)
    Wait(40)
    Call(PlaySoundAtPart, 512, 1, 8298)
    Call(SetAnimation, 512, 1, 0x76000B)
    Call(SetPartFlagBits, 512, 1, 1, 0)
    Set(LVar0, Ref(AS_ToyTank_OpenHatch))
    Call(PlayModelAnimation, 0, LVar0)
    Wait(10)
    Call(GetActorVar, 513, 7, LVar0)
    IfNe(LVar0, 0)
        Call(SetDarknessMode, 2)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x760003)
    Wait(20)
    Call(SetActorVar, 513, 6, 1)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Thread
        Call(b_area_omo2_general_guy_FadeBackgroundDarken)
    EndThread
    Call(GetModelCenter, 39)
    Thread
        Loop(4)
            Call(PlaySoundAtActor, LVar8, 978)
            Call(RandInt, 3, LVar0)
            Add(LVar0, 3)
            Wait(LVar0)
        EndLoop
    EndThread
    Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(1.0), 40, 0, 0, 0, 0, 0, 0, 0)
    Wait(40)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x10000020, 0, 5, 32)
    Switch(LVar0)
        CaseOrEq(5)
        CaseOrEq(6)
            IfEq(LVar0, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
            Call(GetModelCenter, 39)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar3, 0, LVar5)
            Call(PlaySound, 8297)
            Call(PlayEffect_impl, 94, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.0), 18, 0, 0, 0, 0)
            Wait(12)
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x10000020, 0, 2, 32)
            Switch(LVar0)
                CaseOrEq(5)
                CaseOrEq(6)
                    IfEq(LVar0, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    Call(SetActorVar, 513, 6, 0)
                    Wait(20)
                EndCaseGroup
                CaseDefault
                    Call(GetModelCenter, 39)
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
                    Call(PlaySound, 8297)
                    Call(PlayEffect_impl, 94, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.0), 18, 0, 0, 0, 0)
                    Call(SetActorVar, 513, 6, 0)
                    Wait(12)
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000020, 0, 0, 5, 32)
            EndSwitch
            Call(GetActorVar, 513, 7, LVar0)
            IfNe(LVar0, 0)
                Call(SetDarknessMode, 3)
            EndIf
            Call(b_area_omo2_general_guy_FadeBackgroundLighten)
            Call(SetAnimation, 512, 1, 0x760002)
            Call(SetPartFlagBits, 512, 1, 1, 1)
            Set(LVar0, Ref(AS_ToyTank_CloseHatch))
            Call(PlayModelAnimation, 0, LVar0)
            Call(PlaySoundAtPart, 512, 1, 8299)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetModelCenter, 39)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(PlaySound, 8297)
    Call(PlayEffect_impl, 94, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.0), 18, 0, 0, 0, 0)
    Wait(12)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000020, 0, 0, 5, 32)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x760002)
            IfEq(LVarF, 10)
                Call(SetActorVar, 513, 6, 0)
                Wait(30)
                Call(SetAnimation, 512, 1, 0x760002)
                Call(SetPartFlagBits, 512, 1, 1, 1)
                Set(LVar0, Ref(AS_ToyTank_CloseHatch))
                Call(PlayModelAnimation, 0, LVar0)
                Call(PlaySoundAtPart, 512, 1, 8299)
                Return
            EndIf
        EndCaseGroup
    EndSwitch
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(GetModelCenter, 39)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(PlaySound, 8297)
    Call(PlayEffect_impl, 94, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.0), 18, 0, 0, 0, 0)
    Call(SetActorVar, 513, 6, 0)
    Wait(12)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
    Switch(LVarF)
        CaseOrEq(5)
        CaseOrEq(6)
            IfEq(LVarF, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarF, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0x10000020, 0, 0, 5, 32)
    EndSwitch
    Call(GetActorVar, 513, 7, LVar0)
    IfNe(LVar0, 0)
        Call(SetDarknessMode, 3)
    EndIf
    Call(b_area_omo2_general_guy_FadeBackgroundLighten)
    Call(SetAnimation, 512, 1, 0x760002)
    Call(SetPartFlagBits, 512, 1, 1, 1)
    Set(LVar0, Ref(AS_ToyTank_CloseHatch))
    Call(PlayModelAnimation, 0, LVar0)
    Call(PlaySoundAtPart, 512, 1, 8299)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

void TTYD64_InstallBattles_omo2(void) {
    Mod_SetBattleList("TTYD64", 17, TTYD64_omo2_Formations);
    Mod_SetStageList("TTYD64", 17, TTYD64_omo2_Stages);
}
