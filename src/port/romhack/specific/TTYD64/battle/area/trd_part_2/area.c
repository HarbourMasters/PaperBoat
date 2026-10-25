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
API_CALLABLE(ActorSpeak);
API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(CreateCurrentPosTargetList);
API_CALLABLE(EnableActorBlur);
API_CALLABLE(EnableBattleStatusBar);
API_CALLABLE(EnableGroup);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FallToGoal);
API_CALLABLE(ForceHomePos);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags);
API_CALLABLE(GetEnemyMaxHP);
API_CALLABLE(GetHomePos);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartPos);
API_CALLABLE(GetPartRotation);
API_CALLABLE(GetPlayerHP);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HideHealthBar);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(ResetActorSounds);
API_CALLABLE(RotateGroup);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorSize);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorType);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetCamBGColor);
API_CALLABLE(SetDefenseTable);
API_CALLABLE(SetEnemyHP);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetModelFlags);
API_CALLABLE(SetOwnerID);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartRotation);
API_CALLABLE(SetPartRotationOffset);
API_CALLABLE(SetPartTargetFlagBits);
API_CALLABLE(SetSpriteShading);
API_CALLABLE(SetTargetOffset);
API_CALLABLE(ShakeCam);
API_CALLABLE(TranslateGroup);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(b_area_trd_part_2_black_ninja_koopa_GetLastActorEventType);
API_CALLABLE(b_area_trd_part_2_black_ninja_koopa_GetTowerFallPosition);
API_CALLABLE(b_area_trd_part_2_black_ninja_koopa_SpawnSpinEffect);
API_CALLABLE(b_area_trd_part_2_black_ninja_koopa_StartRumbleWithParams);
API_CALLABLE(b_area_trd_part_2_fake_bowser_PlayKoopaBrosSong);
API_CALLABLE(b_area_trd_part_2_fake_bowser_SetModelTintMode);
API_CALLABLE(b_area_trd_part_2_fake_bowser_SetModelTintParams);
API_CALLABLE(b_area_trd_part_2_fake_bowser_StartRumbleWithParams);
API_CALLABLE(b_area_trd_part_2_green_ninja_koopa_GetLastActorEventType);
API_CALLABLE(b_area_trd_part_2_green_ninja_koopa_GetTowerFallPosition);
API_CALLABLE(b_area_trd_part_2_green_ninja_koopa_SpawnSpinEffect);
API_CALLABLE(b_area_trd_part_2_green_ninja_koopa_StartRumbleWithParams);
API_CALLABLE(b_area_trd_part_2_red_ninja_koopa_GetLastActorEventType);
API_CALLABLE(b_area_trd_part_2_red_ninja_koopa_GetTowerFallPosition);
API_CALLABLE(b_area_trd_part_2_red_ninja_koopa_SpawnSpinEffect);
API_CALLABLE(b_area_trd_part_2_red_ninja_koopa_StartRumbleWithParams);
API_CALLABLE(b_area_trd_part_2_yellow_ninja_koopa_GetLastActorEventType);
API_CALLABLE(b_area_trd_part_2_yellow_ninja_koopa_GetTowerFallPosition);
API_CALLABLE(b_area_trd_part_2_yellow_ninja_koopa_SpawnSpinEffect);
API_CALLABLE(b_area_trd_part_2_yellow_ninja_koopa_StartRumbleWithParams);
extern u8 FakeBowserAnimState[];
extern ActorBlueprint b_area_trd_part_2_black_ninja_koopa;
extern s32 b_area_trd_part_2_black_ninja_koopa_BasicHurtAnims[];
extern s32 b_area_trd_part_2_black_ninja_koopa_BasicToppledAnims[];
extern s32 b_area_trd_part_2_black_ninja_koopa_DefaultAnims[];
extern s32 b_area_trd_part_2_black_ninja_koopa_DefaultDefense[];
extern s32 b_area_trd_part_2_black_ninja_koopa_TippingAnims[];
extern s32 b_area_trd_part_2_black_ninja_koopa_ToppledAnims[];
extern s32 b_area_trd_part_2_black_ninja_koopa_ToppledDefense[];
extern s32 b_area_trd_part_2_black_ninja_koopa_TowerAnims[];
extern ActorPartBlueprint b_area_trd_part_2_fake_bowser_ActorParts[];
extern u8 b_area_trd_part_2_fake_bowser_BowserModels[];
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_BlockArm;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathBackWheels;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathBody;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathFeet;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathFrontWheels;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathLeftArm;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathMain;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathRightArm;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathShell;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathTail;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_HurtBody;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_HurtHead;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_IdleBody;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_IdleFeet;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_IdleHead;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_MoveBody;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_MoveFeet;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_MoveHead;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_MoveWheels;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_StrikeArm;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_StrikeBody;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_AnimBowser_StrikeFeet;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_BuildTowerWithKoopa;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_FakeBowser_HandlePhase;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_KoopaBros_HandlePhase;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_KoopaBros_Idle;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_SpawnDamageFX;
extern EvtScript b_area_trd_part_2_fake_bowser_EVS_UpdateTowerWithKoopa;
extern s32 b_area_trd_part_2_fake_bowser_StatusTable[];
extern ActorBlueprint b_area_trd_part_2_green_ninja_koopa;
extern s32 b_area_trd_part_2_green_ninja_koopa_BasicHurtAnims[];
extern s32 b_area_trd_part_2_green_ninja_koopa_BasicToppledAnims[];
extern s32 b_area_trd_part_2_green_ninja_koopa_DefaultAnims[];
extern s32 b_area_trd_part_2_green_ninja_koopa_DefaultDefense[];
extern s32 b_area_trd_part_2_green_ninja_koopa_TippingAnims[];
extern s32 b_area_trd_part_2_green_ninja_koopa_ToppledAnims[];
extern s32 b_area_trd_part_2_green_ninja_koopa_ToppledDefense[];
extern s32 b_area_trd_part_2_green_ninja_koopa_TowerAnims[];
extern ActorBlueprint b_area_trd_part_2_red_ninja_koopa;
extern s32 b_area_trd_part_2_red_ninja_koopa_BasicHurtAnims[];
extern s32 b_area_trd_part_2_red_ninja_koopa_BasicToppledAnims[];
extern s32 b_area_trd_part_2_red_ninja_koopa_DefaultAnims[];
extern s32 b_area_trd_part_2_red_ninja_koopa_DefaultDefense[];
extern s32 b_area_trd_part_2_red_ninja_koopa_TippingAnims[];
extern s32 b_area_trd_part_2_red_ninja_koopa_ToppledAnims[];
extern s32 b_area_trd_part_2_red_ninja_koopa_ToppledDefense[];
extern s32 b_area_trd_part_2_red_ninja_koopa_TowerAnims[];
extern EvtScript b_area_trd_part_2_trd_00_EVS_PostBattle;
extern s32 b_area_trd_part_2_trd_00_ForegroundModels[];
extern Stage b_area_trd_part_2_trd_01;
extern Stage b_area_trd_part_2_trd_02;
extern Stage b_area_trd_part_2_trd_02b;
extern Stage b_area_trd_part_2_trd_03;
extern Stage b_area_trd_part_2_trd_04;
extern Stage b_area_trd_part_2_trd_05;
extern Stage b_area_trd_part_2_trd_05b;
extern Stage b_area_trd_part_2_trd_05c;
extern Stage b_area_trd_part_2_trd_05d;
extern Stage b_area_trd_part_2_trd_05e;
extern Stage b_area_trd_part_2_trd_05f;
extern ActorBlueprint b_area_trd_part_2_yellow_ninja_koopa;
extern s32 b_area_trd_part_2_yellow_ninja_koopa_BasicHurtAnims[];
extern s32 b_area_trd_part_2_yellow_ninja_koopa_BasicToppledAnims[];
extern s32 b_area_trd_part_2_yellow_ninja_koopa_DefaultAnims[];
extern s32 b_area_trd_part_2_yellow_ninja_koopa_DefaultDefense[];
extern s32 b_area_trd_part_2_yellow_ninja_koopa_TippingAnims[];
extern s32 b_area_trd_part_2_yellow_ninja_koopa_ToppledAnims[];
extern s32 b_area_trd_part_2_yellow_ninja_koopa_ToppledDefense[];
extern s32 b_area_trd_part_2_yellow_ninja_koopa_TowerAnims[];
extern ActorBlueprint TTYD64_trd_part_2_fake_bowser;
extern EvtScript TTYD64_trd_part_2_fake_bowser_EVS_Init;
extern EvtScript TTYD64_trd_part_2_fake_bowser_EVS_FakeBowser_Idle;
extern EvtScript TTYD64_trd_part_2_fake_bowser_EVS_FakeBowser_HandleEvent;
extern EvtScript TTYD64_trd_part_2_fake_bowser_EVS_KoopaBrosEnter;
extern EvtScript TTYD64_trd_part_2_fake_bowser_EVS_TryFormingTower;
extern EvtScript TTYD64_trd_part_2_fake_bowser_EVS_TryJoiningTower;
extern EvtScript TTYD64_trd_part_2_fake_bowser_EVS_Broadcast_TowerUnstable;
extern EvtScript TTYD64_trd_part_2_fake_bowser_EVS_Broadcast_ToppleHit;
extern EvtScript TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros;
extern EvtScript TTYD64_trd_part_2_fake_bowser_EVS_KoopaBros_HandleEvent;
extern EvtScript TTYD64_trd_part_2_fake_bowser_EVS_KoopaBros_TakeTurn;
extern EvtScript TTYD64_trd_part_2_red_ninja_koopa_HandleCommand;
extern EvtScript TTYD64_trd_part_2_yellow_ninja_koopa_HandleCommand;
extern EvtScript TTYD64_trd_part_2_black_ninja_koopa_HandleCommand;
extern EvtScript TTYD64_trd_part_2_green_ninja_koopa_HandleCommand;
extern Stage TTYD64_trd_part_2_trd_00;
extern EvtScript TTYD64_trd_part_2_trd_00_EVS_PreBattle;
extern EvtScript TTYD64_trd_part_2_fake_bowser_EVS_FakeBowser_TakeTurn;
extern EvtScript TTYD64_trd_part_2_EVS_8041DF10;
extern FormationRow TTYD64_trd_part_2_Formation_00[];
extern Battle TTYD64_trd_part_2_Formations[];
extern StageListRow TTYD64_trd_part_2_Stages[];

FormationRow TTYD64_trd_part_2_Formation_00[] = {
    { .actor = &b_area_trd_part_2_green_ninja_koopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_trd_part_2_yellow_ninja_koopa,
      .home = { .index = 0 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_trd_part_2_black_ninja_koopa,
      .home = { .index = 0 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &b_area_trd_part_2_red_ninja_koopa,
      .home = { .index = 0 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_trd_part_2_fake_bowser,
      .home = { .index = 3 },
      .priority = 6,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

Battle TTYD64_trd_part_2_Formations[] = {
    { .name = "\203m\203R\203u\203\215\203X",
      .formationSize = 5,
      .formation = (Formation*) TTYD64_trd_part_2_Formation_00,
      .stage = &TTYD64_trd_part_2_trd_00,
      .onBattleStart = NULL },
    {},
};

StageListRow TTYD64_trd_part_2_Stages[] = {
    { .name = "trd_00", .stage = &TTYD64_trd_part_2_trd_00 },
    { .name = "trd_01", .stage = &b_area_trd_part_2_trd_01 },
    { .name = "trd_02", .stage = &b_area_trd_part_2_trd_02 },
    { .name = "trd_02b", .stage = &b_area_trd_part_2_trd_02b },
    { .name = "trd_03", .stage = &b_area_trd_part_2_trd_03 },
    { .name = "trd_04", .stage = &b_area_trd_part_2_trd_04 },
    { .name = "trd_05", .stage = &b_area_trd_part_2_trd_05 },
    { .name = "trd_05b", .stage = &b_area_trd_part_2_trd_05b },
    { .name = "trd_05c", .stage = &b_area_trd_part_2_trd_05c },
    { .name = "trd_05d", .stage = &b_area_trd_part_2_trd_05d },
    { .name = "trd_05e", .stage = &b_area_trd_part_2_trd_05e },
    { .name = "trd_05f", .stage = &b_area_trd_part_2_trd_05f },
    {},
};

ActorBlueprint TTYD64_trd_part_2_fake_bowser = {
    .flags = 0x4,
    .maxHP = 10,
    .type = 0x99,
    .level = 0,
    .partCount = 11,
    .partsData = b_area_trd_part_2_fake_bowser_ActorParts,
    .initScript = &TTYD64_trd_part_2_fake_bowser_EVS_Init,
    .statusTable = b_area_trd_part_2_fake_bowser_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 90,
    .coinReward = 0,
    .size = { -71, 125 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

// clang-format off
EvtScript TTYD64_trd_part_2_fake_bowser_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_trd_part_2_fake_bowser_EVS_FakeBowser_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_trd_part_2_fake_bowser_EVS_FakeBowser_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_trd_part_2_fake_bowser_EVS_FakeBowser_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_trd_part_2_fake_bowser_EVS_FakeBowser_HandlePhase))
    UseArray(Ref(FakeBowserAnimState))
    Call(SetActorVar, 516, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Set(ArrayVar(0), 0)
    Call(SetActorPos, ACTOR_SELF, 96, 0, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Call(SetPartTargetFlagBits, ACTOR_SELF, 2, 4, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_fake_bowser_EVS_FakeBowser_Idle = {
    UseArray(Ref(FakeBowserAnimState))
    Set(LVarA, 0)
    Label(0)
    Set(LVar0, ArrayVar(0))
    Switch(LVar0)
        CaseEq(0)
            Set(ArrayVar(0), 1)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_IdleBody)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_IdleFeet)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_IdleHead)
        CaseEq(1)
        CaseEq(2)
            Set(ArrayVar(0), 3)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_HurtBody)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_HurtHead)
        CaseEq(3)
        CaseEq(4)
            Set(ArrayVar(0), 5)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_MoveBody)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_MoveFeet)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_MoveHead)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_MoveWheels)
        CaseEq(5)
        CaseEq(6)
            Set(ArrayVar(0), 7)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_StrikeBody)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_StrikeFeet)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_StrikeArm)
        CaseEq(7)
        CaseEq(8)
            Call(PlaySoundAtActor, ACTOR_SELF, 949)
            Set(ArrayVar(0), 9)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathMain)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathBody)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathShell)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathLeftArm)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathRightArm)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathTail)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathFrontWheels)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathBackWheels)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_DeathFeet)
            Exec(TTYD64_trd_part_2_fake_bowser_EVS_KoopaBrosEnter)
        CaseEq(9)
        CaseEq(10)
            Set(ArrayVar(0), 11)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_StrikeBody)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_StrikeFeet)
            Exec(b_area_trd_part_2_fake_bowser_EVS_AnimBowser_BlockArm)
        CaseEq(11)
    EndSwitch
    Call(GetPartPos, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 24, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
    Call(RotateGroup, 24, LVar0, 1, 0, 0)
    Call(RotateGroup, 24, LVar1, 0, 1, 0)
    Call(RotateGroup, 24, LVar2, 0, 0, 1)
    Call(SetModelFlags, 15, 64, 1)
    Call(SetModelFlags, 16, 64, 1)
    Call(SetModelFlags, 17, 64, 1)
    Call(SetModelFlags, 18, 64, 1)
    Call(SetModelFlags, 19, 64, 1)
    Call(SetModelFlags, 20, 64, 1)
    Call(SetModelFlags, 21, 64, 1)
    Call(SetModelFlags, 22, 64, 1)
    Call(SetModelFlags, 23, 64, 1)
    Call(GetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 34, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(RotateGroup, 34, LVar0, 1, 0, 0)
    Call(RotateGroup, 34, LVar1, 0, 1, 0)
    Call(RotateGroup, 34, LVar2, 0, 0, 1)
    Call(SetModelFlags, 31, 64, 1)
    Call(SetModelFlags, 32, 64, 1)
    Call(SetModelFlags, 33, 64, 1)
    Call(GetPartPos, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 30, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 4, LVar0, LVar1, LVar2)
    Call(RotateGroup, 30, LVar0, 1, 0, 0)
    Call(RotateGroup, 30, LVar1, 0, 1, 0)
    Call(RotateGroup, 30, LVar2, 0, 0, 1)
    Call(SetModelFlags, 25, 64, 1)
    Call(SetModelFlags, 26, 64, 1)
    Call(SetModelFlags, 27, 64, 1)
    Call(SetModelFlags, 28, 64, 1)
    Call(SetModelFlags, 29, 64, 1)
    Call(GetPartPos, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 14, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 6, LVar0, LVar1, LVar2)
    Call(RotateGroup, 14, LVar0, 1, 0, 0)
    Call(RotateGroup, 14, LVar1, 0, 1, 0)
    Call(RotateGroup, 14, LVar2, 0, 0, 1)
    Call(SetModelFlags, 11, 64, 1)
    Call(SetModelFlags, 12, 64, 1)
    Call(SetModelFlags, 13, 64, 1)
    Call(GetPartPos, ACTOR_SELF, 7, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 10, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 7, LVar0, LVar1, LVar2)
    Call(RotateGroup, 10, LVar0, 1, 0, 0)
    Call(RotateGroup, 10, LVar1, 0, 1, 0)
    Call(RotateGroup, 10, LVar2, 0, 0, 1)
    Call(SetModelFlags, 9, 64, 1)
    Set(LVar0, ArrayVar(0))
    IfEq(LVar0, 9)
        Call(GetPartPos, ACTOR_SELF, 8, LVar0, LVar1, LVar2)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 0)
    EndIf
    Call(SetPartPos, ACTOR_SELF, 8, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 44, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 8, LVar0, LVar1, LVar2)
    Call(RotateGroup, 44, LVar0, 1, 0, 0)
    Call(RotateGroup, 44, LVar1, 0, 1, 0)
    Call(RotateGroup, 44, LVar2, 0, 0, 1)
    Call(SetModelFlags, 43, 64, 1)
    Set(LVar0, ArrayVar(0))
    IfEq(LVar0, 9)
        Call(GetPartPos, ACTOR_SELF, 9, LVar0, LVar1, LVar2)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 0)
    EndIf
    Call(SetPartPos, ACTOR_SELF, 9, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 46, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 9, LVar0, LVar1, LVar2)
    Call(RotateGroup, 46, LVar0, 1, 0, 0)
    Call(RotateGroup, 46, LVar1, 0, 1, 0)
    Call(RotateGroup, 46, LVar2, 0, 0, 1)
    Call(SetModelFlags, 45, 64, 1)
    Call(GetPartPos, ACTOR_SELF, 11, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 38, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 11, LVar0, LVar1, LVar2)
    Call(RotateGroup, 38, LVar0, 1, 0, 0)
    Call(RotateGroup, 38, LVar1, 0, 1, 0)
    Call(RotateGroup, 38, LVar2, 0, 0, 1)
    Call(SetModelFlags, 35, 64, 1)
    Call(SetModelFlags, 36, 64, 1)
    Call(SetModelFlags, 37, 64, 1)
    Call(GetPartPos, ACTOR_SELF, 10, LVar0, LVar1, LVar2)
    Call(TranslateGroup, 42, LVar0, LVar1, LVar2)
    Call(GetPartRotation, ACTOR_SELF, 10, LVar0, LVar1, LVar2)
    Call(RotateGroup, 42, LVar0, 1, 0, 0)
    Call(RotateGroup, 42, LVar1, 0, 1, 0)
    Call(RotateGroup, 42, LVar2, 0, 0, 1)
    Call(SetModelFlags, 39, 64, 1)
    Call(SetModelFlags, 40, 64, 1)
    Call(SetModelFlags, 41, 64, 1)
    Call(GetActorVar, 516, 0, LVar0)
    IfNotFlag(LVar0, 2)
        Call(GetActorHP, ACTOR_SELF, LVar0)
        Call(GetEnemyMaxHP, ACTOR_SELF, LVar1)
        Mul(LVar0, 100)
        Div(LVar0, LVar1)
        Switch(LVar0)
            CaseEq(0)
            CaseLt(20)
                IfGt(LVarA, 20)
                    Exec(b_area_trd_part_2_fake_bowser_EVS_SpawnDamageFX)
                    Set(LVarA, 0)
                EndIf
            CaseLt(40)
                IfGt(LVarA, 40)
                    Exec(b_area_trd_part_2_fake_bowser_EVS_SpawnDamageFX)
                    Set(LVarA, 0)
                EndIf
            CaseLt(60)
                IfGt(LVarA, 60)
                    Exec(b_area_trd_part_2_fake_bowser_EVS_SpawnDamageFX)
                    Set(LVarA, 0)
                EndIf
            CaseLt(80)
                IfGt(LVarA, 80)
                    Exec(b_area_trd_part_2_fake_bowser_EVS_SpawnDamageFX)
                    Set(LVarA, 0)
                EndIf
        EndSwitch
        Add(LVarA, 1)
    EndIf
    Wait(1)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_fake_bowser_EVS_FakeBowser_HandleEvent = {
    UseArray(Ref(FakeBowserAnimState))
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Set(ArrayVar(0), 2)
            Wait(20)
            Set(ArrayVar(0), 0)
        CaseEq(10)
            Set(ArrayVar(0), 2)
            Wait(20)
            Set(ArrayVar(0), 0)
        CaseOrEq(23)
        CaseOrEq(25)
            Set(ArrayVar(0), 2)
            Wait(20)
            Set(ArrayVar(0), 0)
        EndCaseGroup
        CaseOrEq(32)
        CaseOrEq(36)
            Call(HideHealthBar, ACTOR_SELF)
            IfEq(LVar0, 36)
                Call(b_area_trd_part_2_fake_bowser_SetModelTintMode, 0, Ref(b_area_trd_part_2_fake_bowser_BowserModels), 3)
                Call(b_area_trd_part_2_fake_bowser_SetModelTintParams, 3, 35, 35, 35, 0, 0, 0, 0, 0, 0)
            EndIf
            Set(ArrayVar(0), 2)
            Wait(20)
            IfEq(LVar0, 36)
                Call(b_area_trd_part_2_fake_bowser_SetModelTintMode, 0, Ref(b_area_trd_part_2_fake_bowser_BowserModels), 0)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(GetActorSize, ACTOR_SELF, LVar3, LVar4)
                DivF(LVar3, Float(2.0))
                AddF(LVar1, LVar3)
                AddF(LVar2, Float(5.0))
                DivF(LVar3, Float(10.0))
                Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
                Wait(5)
                Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
            EndIf
            Call(ActorSpeak, 0xC0106, ACTOR_SELF, 1, -1, -1)
            Wait(30)
            Set(ArrayVar(0), 8)
            Label(20)
            Call(GetActorVar, 516, 0, LVar0)
            Wait(1)
            IfNotFlag(LVar0, 1)
                Goto(20)
            EndIf
            Wait(20)
            ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_TryFormingTower)
            Call(GetEnemyMaxHP, ACTOR_SELF, LVar0)
            Call(SetEnemyHP, ACTOR_SELF, LVar0)
            Return
        EndCaseGroup
        CaseOrEq(44)
        CaseOrEq(14)
            Call(b_area_trd_part_2_fake_bowser_SetModelTintMode, 0, Ref(b_area_trd_part_2_fake_bowser_BowserModels), 3)
            Call(b_area_trd_part_2_fake_bowser_SetModelTintParams, 3, 35, 35, 35, 0, 0, 0, 0, 0, 0)
            Set(ArrayVar(0), 2)
            Wait(20)
            Set(ArrayVar(0), 0)
            Call(b_area_trd_part_2_fake_bowser_SetModelTintMode, 0, Ref(b_area_trd_part_2_fake_bowser_BowserModels), 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetActorSize, ACTOR_SELF, LVar3, LVar4)
            DivF(LVar3, Float(2.0))
            AddF(LVar1, LVar3)
            AddF(LVar2, Float(5.0))
            DivF(LVar3, Float(10.0))
            Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
            Wait(5)
            Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
        EndCaseGroup
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_fake_bowser_EVS_KoopaBrosEnter = {
    Call(UseIdleAnimation, 512, 0)
    Call(EnableIdleScript, 512, 0)
    Call(SetActorPos, 512, 100, 0, 10)
    Call(SetAnimation, 512, 1, 0x66031C)
    Thread
        Call(SetActorJumpGravity, 512, Float(0.400390625))
        Call(SetActorSounds, 512, 2, 0, 0)
        Call(SetGoalPos, 512, -300, 250, 0)
        Call(JumpToGoal, 512, 50, 0, 1, 0)
    EndThread
    Call(UseIdleAnimation, 513, 0)
    Call(EnableIdleScript, 513, 0)
    Call(SetActorPos, 513, 100, 0, 10)
    Call(SetAnimation, 513, 1, 0x66021C)
    Thread
        Call(SetActorJumpGravity, 513, Float(0.400390625))
        Call(SetActorSounds, 513, 2, 0, 0)
        Call(SetGoalPos, 513, -200, 250, 0)
        Call(JumpToGoal, 513, 50, 0, 1, 0)
    EndThread
    Call(UseIdleAnimation, 514, 0)
    Call(EnableIdleScript, 514, 0)
    Call(SetActorPos, 514, 100, 0, 10)
    Call(SetAnimation, 514, 1, 0x66001C)
    Thread
        Call(SetActorJumpGravity, 514, Float(0.400390625))
        Call(SetActorSounds, 514, 2, 0, 0)
        Call(SetGoalPos, 514, 0, 250, 0)
        Call(JumpToGoal, 514, 50, 0, 1, 0)
    EndThread
    Call(UseIdleAnimation, 515, 0)
    Call(EnableIdleScript, 515, 0)
    Call(SetActorPos, 515, 100, 0, 10)
    Call(SetAnimation, 515, 1, 0x66011C)
    Thread
        Call(SetActorJumpGravity, 515, Float(0.400390625))
        Call(SetActorSounds, 515, 2, 0, 0)
        Call(SetGoalPos, 515, 150, 250, 0)
        Call(JumpToGoal, 515, 50, 0, 1, 0)
    EndThread
    Wait(100)
    Wait(100)
    Call(EnableGroup, 24, 0)
    Call(EnableGroup, 14, 0)
    Call(EnableGroup, 10, 0)
    Call(EnableGroup, 34, 0)
    Call(EnableGroup, 30, 0)
    Call(EnableGroup, 44, 0)
    Call(EnableGroup, 46, 0)
    Call(EnableGroup, 38, 0)
    Call(EnableGroup, 42, 0)
    Thread
        Wait(23)
        Call(PlaySoundAtActor, 512, 769)
        Wait(5)
        Call(PlaySoundAtActor, 513, 769)
        Wait(5)
        Call(PlaySoundAtActor, 514, 769)
        Wait(5)
        Call(PlaySoundAtActor, 515, 769)
    EndThread
    Thread
        Call(SetAnimation, 512, 1, 0x660312)
        Call(SetActorPos, 512, 20, 250, 0)
        Call(SetGoalPos, 512, 20, 0, 0)
        Call(SetActorJumpGravity, 512, Float(1.5))
        Call(SetActorSounds, 512, 2, 0, 0)
        Call(FallToGoal, 512, 30)
        Call(PlaySoundAtActor, 512, 1001)
        Call(ResetActorSounds, 512, 2)
        Call(ForceHomePos, 512, 20, 0, 0)
        Call(SetAnimation, 512, 1, 0x660305)
    EndThread
    Thread
        Wait(5)
        Call(SetAnimation, 513, 1, 0x660212)
        Call(SetActorPos, 513, 60, 250, -5)
        Call(SetGoalPos, 513, 60, 0, -5)
        Call(SetActorJumpGravity, 513, Float(1.5))
        Call(SetActorSounds, 513, 2, 0, 0)
        Call(FallToGoal, 513, 30)
        Call(PlaySoundAtActor, 513, 1001)
        Call(ResetActorSounds, 513, 2)
        Call(ForceHomePos, 513, 60, 0, -5)
        Call(SetAnimation, 513, 1, 0x660205)
    EndThread
    Thread
        Wait(10)
        Call(SetAnimation, 514, 1, 0x660012)
        Call(SetActorPos, 514, 100, 250, -10)
        Call(SetGoalPos, 514, 100, 0, -10)
        Call(SetActorJumpGravity, 514, Float(1.5))
        Call(SetActorSounds, 514, 2, 0, 0)
        Call(FallToGoal, 514, 30)
        Call(PlaySoundAtActor, 514, 1001)
        Call(ResetActorSounds, 514, 2)
        Call(ForceHomePos, 514, 100, 0, -10)
        Call(SetAnimation, 514, 1, 0x660005)
    EndThread
    Thread
        Wait(15)
        Call(SetAnimation, 515, 1, 0x660112)
        Call(SetActorPos, 515, 140, 250, -15)
        Call(SetGoalPos, 515, 140, 0, -15)
        Call(SetActorJumpGravity, 515, Float(1.5))
        Call(SetActorSounds, 515, 2, 0, 0)
        Call(FallToGoal, 515, 30)
        Call(PlaySoundAtActor, 515, 1001)
        Call(ResetActorSounds, 515, 2)
        Call(ForceHomePos, 515, 140, 0, -15)
        Call(SetAnimation, 515, 1, 0x660105)
    EndThread
    Wait(30)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, 70, 46, 0)
    Call(SetBattleCamOffsetY, 0)
    Call(SetBattleCamDist, 292)
    Call(MoveBattleCamOver, 20)
    Wait(28)
    Call(SetAnimation, 512, 1, 0x66031A)
    Wait(5)
    Call(GetActorPos, 512, LVar0, LVar1, LVar2)
    Add(LVar0, 7)
    Add(LVar1, 28)
    Add(LVar2, 5)
    Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, 512, 8435)
    Call(SetAnimation, 513, 1, 0x66021A)
    Wait(5)
    Call(GetActorPos, 513, LVar0, LVar1, LVar2)
    Add(LVar0, 7)
    Add(LVar1, 28)
    Add(LVar2, 5)
    Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, 513, 8435)
    Call(SetAnimation, 514, 1, 0x66001A)
    Wait(5)
    Call(GetActorPos, 514, LVar0, LVar1, LVar2)
    Add(LVar0, 7)
    Add(LVar1, 28)
    Add(LVar2, 5)
    Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, 514, 8435)
    Call(SetAnimation, 515, 1, 0x66011A)
    Wait(5)
    Call(GetActorPos, 515, LVar0, LVar1, LVar2)
    Add(LVar0, 7)
    Add(LVar1, 28)
    Add(LVar2, 5)
    Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, 515, 8435)
    Wait(30)
    Call(b_area_trd_part_2_fake_bowser_PlayKoopaBrosSong)
    Call(ActorSpeak, 0xC0107, 513, 1, -1, -1)
    Call(SetActorFlagBits, ACTOR_SELF, 0x440000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x800000, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x800000, 1)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_trd_part_2_fake_bowser_EVS_KoopaBros_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_trd_part_2_fake_bowser_EVS_KoopaBros_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_trd_part_2_fake_bowser_EVS_KoopaBros_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_trd_part_2_fake_bowser_EVS_KoopaBros_HandlePhase))
    Call(SetActorFlagBits, 512, 0x40000, 0)
    Call(SetPartFlagBits, 512, 1, 0x20000, 0)
    Call(HPBarToHome, 512)
    Call(SetAnimation, 512, 1, 0x660304)
    Call(SetActorFlagBits, 513, 0x40000, 0)
    Call(SetPartFlagBits, 513, 1, 0x20000, 0)
    Call(HPBarToHome, 513)
    Call(SetAnimation, 513, 1, 0x660204)
    Call(SetActorFlagBits, 514, 0x40000, 0)
    Call(SetPartFlagBits, 514, 1, 0x20000, 0)
    Call(HPBarToHome, 514)
    Call(SetAnimation, 514, 1, 0x660004)
    Call(SetActorFlagBits, 515, 0x40000, 0)
    Call(SetPartFlagBits, 515, 1, 0x20000, 0)
    Call(HPBarToHome, 515)
    Call(SetAnimation, 515, 1, 0x660104)
    Call(SetActorVar, ACTOR_SELF, 1, 3)
    Call(GetActorVar, 516, 0, LVar0)
    BitwiseOrConst(LVar0, 1)
    Call(SetActorVar, 516, 0, LVar0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_fake_bowser_EVS_TryFormingTower = {
    Set(LVarA, 0)
    Call(CreateCurrentPosTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetActorVar, LVar0, 1, LVar1)
    IfEq(LVar1, 0)
        Call(GetStatusFlags, LVar0, LVar1)
        IfEq(LVar1, 0)
            IfEq(LVarA, 0)
                Call(SetActorVar, ACTOR_SELF, 4, LVar0)
            EndIf
            Add(LVarA, 1)
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Switch(LVarA)
        CaseEq(0)
            Return
        CaseEq(1)
            Call(GetActorVar, 516, 0, LVar0)
            BitwiseOrConst(LVar0, 512)
            Call(SetActorVar, 516, 0, LVar0)
            Return
    EndSwitch
    Call(SetActorVar, ACTOR_SELF, 3, LVarA)
    Set(LFlag0, 0)
    Set(LVarB, LVarA)
    Sub(LVarB, 1)
    Call(CreateCurrentPosTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(1)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetActorVar, LVar0, 1, LVar1)
    IfEq(LVar1, 0)
        Call(GetStatusFlags, LVar0, LVar1)
        IfEq(LVar1, 0)
            Set(LVar1, LVarA)
            Set(LVar2, LVarB)
            Exec(b_area_trd_part_2_fake_bowser_EVS_BuildTowerWithKoopa)
            Sub(LVarB, 1)
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(1)
    EndIf
    Call(EnableBattleStatusBar, 0)
    Label(2)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Wait(1)
    IfEq(LVar0, 3)
        Goto(2)
    EndIf
    Call(EnableBattleStatusBar, 1)
    Call(SetActorFlagBits, ACTOR_SELF, 0x2000000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20000, 0)
    Set(LVar0, LVarA)
    Mul(LVar0, 18)
    Add(LVar0, 20)
    Call(SetTargetOffset, ACTOR_SELF, 2, -4, LVar0)
    Call(SetActorSize, ACTOR_SELF, LVar0, 45)
    Call(SetActorType, ACTOR_SELF, 154)
    Call(GetActorVar, ACTOR_SELF, 4, LVar1)
    Call(GetActorPos, LVar1, LVar2, LVar3, LVar4)
    Call(SetActorPos, ACTOR_SELF, LVar2, LVar3, LVar4)
    Set(LVarA, 0)
    ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros)
    Call(SetActorVar, ACTOR_SELF, 1, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_fake_bowser_EVS_TryJoiningTower = {
    Set(LVarA, 0)
    Call(CreateCurrentPosTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetActorVar, LVar0, 1, LVar1)
    IfEq(LVar1, 0)
        Call(GetStatusFlags, LVar0, LVar1)
        IfEq(LVar1, 0)
            Add(LVarA, 1)
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfEq(LVarA, 0)
        Return
    EndIf
    Set(LVar3, LVarA)
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    Add(LVarA, LVar0)
    Call(SetActorVar, ACTOR_SELF, 3, LVarA)
    Call(GetActorVar, 516, 0, LVar0)
    BitwiseAndConst(LVar0, -257)
    Call(SetActorVar, 516, 0, LVar0)
    Set(LVar0, 512)
    Loop(4)
        Call(ActorExists, LVar0, LVar1)
        IfEq(LVar1, 1)
            Call(GetActorVar, LVar0, 1, LVar2)
            IfEq(LVar2, 3)
                Set(LVar1, LVarA)
                Set(LVar2, -1)
                Exec(b_area_trd_part_2_fake_bowser_EVS_UpdateTowerWithKoopa)
                BreakLoop
            EndIf
        EndIf
        Add(LVar0, 1)
    EndLoop
    Set(LVar2, 0)
    Call(CreateCurrentPosTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(1)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetActorVar, LVar0, 1, LVar8)
    IfEq(LVar8, 0)
        Set(LVar1, LVarA)
        Exec(b_area_trd_part_2_fake_bowser_EVS_UpdateTowerWithKoopa)
        Add(LVar2, 1)
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(1)
    EndIf
    Call(EnableBattleStatusBar, 0)
    Label(2)
    Call(GetActorVar, 516, 0, LVar0)
    IfNotFlag(LVar0, 256)
        Wait(1)
        Goto(2)
    EndIf
    Call(EnableBattleStatusBar, 1)
    Call(SetActorFlagBits, ACTOR_SELF, 0x2000000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20000, 0)
    Set(LVar0, LVarA)
    Mul(LVar0, 18)
    Add(LVar0, 20)
    Call(SetTargetOffset, ACTOR_SELF, 2, -4, LVar0)
    Call(SetActorSize, ACTOR_SELF, LVar0, 45)
    Call(SetActorType, ACTOR_SELF, 154)
    Call(GetActorVar, ACTOR_SELF, 4, LVar1)
    Call(GetActorPos, LVar1, LVar2, LVar3, LVar4)
    Call(SetActorPos, ACTOR_SELF, LVar2, LVar3, LVar4)
    Set(LVarA, 0)
    ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros)
    Call(SetActorVar, ACTOR_SELF, 1, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_fake_bowser_EVS_Broadcast_TowerUnstable = {
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    IfEq(LVar0, 2)
        Return
    EndIf
    Call(GetActorVar, 516, 0, LVar0)
    BitwiseOrConst(LVar0, 16)
    Call(SetActorVar, 516, 0, LVar0)
    Call(SetActorVar, ACTOR_SELF, 1, 2)
    Set(LVarA, 1)
    ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros)
    Call(GetActorVar, ACTOR_SELF, 3, LVarA)
    Set(LVar0, LVarA)
    Mul(LVar0, 18)
    Add(LVar0, 5)
    Call(SetTargetOffset, ACTOR_SELF, 2, -4, LVar0)
    Call(SetActorSize, ACTOR_SELF, LVar0, 45)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_fake_bowser_EVS_Broadcast_ToppleHit = {
    Call(SetActorVar, ACTOR_SELF, 1, 3)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    IfNe(LVar0, 14)
        Set(LVarA, 5)
    Else
        Set(LVarA, 6)
    EndIf
    ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros)
    Call(SetActorFlagBits, ACTOR_SELF, 0x400000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20000, 1)
    Call(GetActorVar, 516, 0, LVar0)
    BitwiseAndConst(LVar0, -17)
    Call(SetActorVar, 516, 0, LVar0)
    Call(GetActorVar, 516, 0, LVar0)
    BitwiseAndConst(LVar0, -33)
    Call(SetActorVar, 516, 0, LVar0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros = {
    Call(ActorExists, 512, LVar0)
    IfEq(LVar0, 1)
        ExecGetTID(TTYD64_trd_part_2_green_ninja_koopa_HandleCommand, LVar1)
    EndIf
    Call(ActorExists, 513, LVar0)
    IfEq(LVar0, 1)
        ExecGetTID(TTYD64_trd_part_2_yellow_ninja_koopa_HandleCommand, LVar1)
    EndIf
    Call(ActorExists, 514, LVar0)
    IfEq(LVar0, 1)
        ExecGetTID(TTYD64_trd_part_2_black_ninja_koopa_HandleCommand, LVar1)
    EndIf
    Call(ActorExists, 515, LVar0)
    IfEq(LVar0, 1)
        ExecGetTID(TTYD64_trd_part_2_red_ninja_koopa_HandleCommand, LVar1)
    EndIf
    Label(0)
    IsThreadRunning(LVar1, LVar0)
    IfEq(LVar0, 1)
        Wait(1)
        Goto(0)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_fake_bowser_EVS_KoopaBros_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Call(GetBattleFlags, LVar0)
            IfFlag(LVar0, 0x80000)
                Call(GetActorVar, 516, 0, LVar0)
                BitwiseOrConst(LVar0, 128)
                Call(SetActorVar, 516, 0, LVar0)
            Else
                Call(GetActorVar, 516, 0, LVar0)
                BitwiseOrConst(LVar0, 64)
                Call(SetActorVar, 516, 0, LVar0)
            EndIf
            Set(LVarA, 2)
            ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros)
            Wait(30)
            Call(GetLastElement, LVar0)
            IfFlag(LVar0, 544)
                Call(GetActorVar, 516, 0, LVar0)
                BitwiseOrConst(LVar0, 64)
                Call(SetActorVar, 516, 0, LVar0)
                Call(GetActorVar, 516, 0, LVar0)
                BitwiseOrConst(LVar0, 128)
                Call(SetActorVar, 516, 0, LVar0)
            EndIf
            ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_Broadcast_TowerUnstable)
        CaseEq(10)
            Call(GetBattleFlags, LVar0)
            IfFlag(LVar0, 0x80000)
                Call(GetActorVar, 516, 0, LVar0)
                BitwiseOrConst(LVar0, 128)
                Call(SetActorVar, 516, 0, LVar0)
            Else
                Call(GetActorVar, 516, 0, LVar0)
                BitwiseOrConst(LVar0, 64)
                Call(SetActorVar, 516, 0, LVar0)
            EndIf
            Call(GetLastElement, LVar0)
            IfFlag(LVar0, 544)
                Call(GetActorVar, 516, 0, LVar0)
                BitwiseOrConst(LVar0, 64)
                Call(SetActorVar, 516, 0, LVar0)
                Call(GetActorVar, 516, 0, LVar0)
                BitwiseOrConst(LVar0, 128)
                Call(SetActorVar, 516, 0, LVar0)
            EndIf
            Call(GetActorVar, 516, 0, LVar0)
            IfFlag(LVar0, 64)
                IfFlag(LVar0, 128)
                    ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_Broadcast_ToppleHit)
                    Wait(20)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
                EndIf
            EndIf
            Set(LVarA, 2)
            ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros)
            Wait(30)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            IfNe(LVar0, 2)
                ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_Broadcast_TowerUnstable)
            EndIf
            Call(GetActorVar, 516, 0, LVar0)
            IfFlag(LVar0, 16)
                IfNotFlag(LVar0, 32)
                    Call(GetActorVar, ACTOR_SELF, 4, LVar0)
                    Call(ActorSpeak, 0xC0109, LVar0, 1, -1, -1)
                    Call(GetActorVar, 516, 0, LVar0)
                    BitwiseOrConst(LVar0, 32)
                    Call(SetActorVar, 516, 0, LVar0)
                    Wait(20)
                EndIf
            EndIf
        CaseEq(14)
            Call(GetBattleFlags, LVar0)
            IfFlag(LVar0, 0x80000)
                Call(GetActorVar, 516, 0, LVar0)
                BitwiseOrConst(LVar0, 128)
                Call(SetActorVar, 516, 0, LVar0)
            Else
                Call(GetActorVar, 516, 0, LVar0)
                BitwiseOrConst(LVar0, 64)
                Call(SetActorVar, 516, 0, LVar0)
            EndIf
            Call(GetLastElement, LVar0)
            IfFlag(LVar0, 544)
                Call(GetActorVar, 516, 0, LVar0)
                BitwiseOrConst(LVar0, 64)
                Call(SetActorVar, 516, 0, LVar0)
                Call(GetActorVar, 516, 0, LVar0)
                BitwiseOrConst(LVar0, 128)
                Call(SetActorVar, 516, 0, LVar0)
            EndIf
            Call(GetActorVar, 516, 0, LVar0)
            IfFlag(LVar0, 64)
                IfFlag(LVar0, 128)
                    ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_Broadcast_ToppleHit)
                    Wait(20)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
                EndIf
            EndIf
            Set(LVarA, 3)
            ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros)
            Wait(30)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            IfNe(LVar0, 2)
                ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_Broadcast_TowerUnstable)
            EndIf
            Call(GetActorVar, 516, 0, LVar0)
            IfFlag(LVar0, 16)
                IfNotFlag(LVar0, 32)
                    Call(GetActorVar, ACTOR_SELF, 4, LVar0)
                    Call(ActorSpeak, 0xC0109, LVar0, 1, -1, -1)
                    Call(GetActorVar, 516, 0, LVar0)
                    BitwiseOrConst(LVar0, 32)
                    Call(SetActorVar, 516, 0, LVar0)
                    Wait(20)
                EndIf
            EndIf
        CaseEq(23)
            Set(LVarA, 4)
            ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros)
        CaseEq(25)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            IfEq(LVar0, 2)
                Call(GetActorVar, 516, 0, LVar0)
                BitwiseOrConst(LVar0, 64)
                Call(SetActorVar, 516, 0, LVar0)
                Call(GetActorVar, 516, 0, LVar0)
                BitwiseOrConst(LVar0, 128)
                Call(SetActorVar, 516, 0, LVar0)
            EndIf
            Call(GetActorVar, 516, 0, LVar0)
            IfFlag(LVar0, 64)
                IfFlag(LVar0, 128)
                    ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_Broadcast_ToppleHit)
                    Wait(20)
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Return
                EndIf
            EndIf
            Set(LVarA, 4)
            ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros)
            Call(GetActorVar, 516, 0, LVar0)
            IfFlag(LVar0, 16)
                IfNotFlag(LVar0, 32)
                    Call(GetActorVar, ACTOR_SELF, 4, LVar0)
                    Call(ActorSpeak, 0xC0109, LVar0, 1, -1, -1)
                    Call(GetActorVar, 516, 0, LVar0)
                    BitwiseOrConst(LVar0, 32)
                    Call(SetActorVar, 516, 0, LVar0)
                    Wait(20)
                EndIf
            EndIf
        CaseOrEq(32)
        CaseOrEq(36)
        EndCaseGroup
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_fake_bowser_EVS_KoopaBros_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseEq(0)
        CaseEq(1)
        CaseEq(2)
            Wait(30)
            Call(SetActorVar, ACTOR_SELF, 1, 1)
            Set(LVarA, 0)
            ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros)
            Call(GetActorVar, 516, 0, LVar0)
            BitwiseAndConst(LVar0, -17)
            Call(SetActorVar, 516, 0, LVar0)
            Call(GetActorVar, 516, 0, LVar0)
            BitwiseAndConst(LVar0, -33)
            Call(SetActorVar, 516, 0, LVar0)
            Call(GetActorVar, ACTOR_SELF, 3, LVarA)
            Set(LVar0, LVarA)
            Mul(LVar0, 18)
            Add(LVar0, 20)
            Call(SetTargetOffset, ACTOR_SELF, 2, -4, LVar0)
            Call(SetActorSize, ACTOR_SELF, LVar0, 45)
        CaseEq(3)
    EndSwitch
    Set(LVar0, 512)
    Loop(4)
        Call(ActorExists, LVar0, LVar1)
        IfEq(LVar1, 1)
            Call(GetStatusFlags, LVar0, LVar1)
            IfEq(LVar1, 0)
                Call(GetActorVar, LVar0, 1, LVar1)
                IfEq(LVar1, 1)
                    Set(LFlag0, 1)
                    BreakLoop
                EndIf
            EndIf
        EndIf
        Add(LVar0, 1)
    EndLoop
    IfEq(LFlag0, 1)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamTarget, 90, 0, 0)
        Call(SetBattleCamDist, 350)
        Call(SetBattleCamOffsetY, 40)
        Call(MoveBattleCamOver, 15)
        Wait(15)
    EndIf
    Set(LVarA, 9)
    ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Switch(LVar0)
        CaseEq(1)
            ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_TryJoiningTower)
        CaseDefault
            ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_TryFormingTower)
    EndSwitch
    Call(GetActorVar, 516, 0, LVar0)
    IfFlag(LVar0, 512)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 15)
        Set(LVarA, 8)
        ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros)
        Label(123)
        Call(GetActorVar, 516, 0, LVar0)
        IfFlag(LVar0, 512)
            Wait(1)
            Goto(123)
        EndIf
        Set(LVarA, 10)
        ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros)
        Wait(5)
        Return
    EndIf
    Set(LVarA, 10)
    ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros)
    Wait(5)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    IfEq(LVar0, 3)
        Return
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(GetActorVar, 516, 0, LVar0)
    IfNotFlag(LVar0, 4)
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        Switch(LVar0)
            CaseEq(512)
                Call(ActorSpeak, 0xC0108, LVar0, 1, 0x660314, 0x660304)
            CaseEq(513)
                Call(ActorSpeak, 0xC0108, LVar0, 1, 0x660214, 0x660204)
            CaseEq(514)
                Call(ActorSpeak, 0xC0108, LVar0, 1, 0x660014, 0x660004)
            CaseEq(515)
                Call(ActorSpeak, 0xC0108, LVar0, 1, 0x660114, 0x660104)
        EndSwitch
        Call(GetActorVar, 516, 0, LVar0)
        BitwiseOrConst(LVar0, 4)
        Call(SetActorVar, 516, 0, LVar0)
    EndIf
    Set(LVarA, 7)
    ExecWait(TTYD64_trd_part_2_fake_bowser_EVS_BroadcastToKoopaBros)
    Label(10)
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    Wait(1)
    IfNe(LVar0, 0)
        Goto(10)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 1, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_red_ninja_koopa_HandleCommand = {
    Call(SetOwnerID, 515)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNe(LVar0, 0)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Switch(LVarA)
        CaseEq(0)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(3)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_DefaultAnims))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660104)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_TowerAnims))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660105)
                EndCaseGroup
            EndSwitch
        CaseEq(1)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Wait(5)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_TippingAnims))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66010D)
                EndCaseGroup
            EndSwitch
        CaseEq(2)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x66010B)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Call(GetActorVar, 516, 0, LVar0)
                    BitwiseAndConst(LVar0, 192)
                    IfNe(LVar0, 192)
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_TippingAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66010D)
                    Else
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_BasicHurtAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66010A)
                    EndIf
                EndCaseGroup
            EndSwitch
        CaseEq(3)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Call(b_area_trd_part_2_red_ninja_koopa_GetLastActorEventType, 14)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x66010E)
                    SetConst(LVar2, -1)
                    ExecWait(Ref(EVS_Enemy_BurnHit))
                    Call(GetActorVar, 516, 0, LVar0)
                    BitwiseAndConst(LVar0, 192)
                    IfNe(LVar0, 192)
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_TippingAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66010D)
                    Else
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_BasicHurtAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66010A)
                    EndIf
                EndCaseGroup
            EndSwitch
        CaseEq(4)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(3)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x660108)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660109)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x66011F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660120)
                EndCaseGroup
            EndSwitch
            Wait(15)
        CaseEq(5)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Set(LFlag0, 0)
                    IfEq(LVar0, 3)
                        Set(LFlag0, 1)
                    EndIf
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
                    Call(b_area_trd_part_2_red_ninja_koopa_GetTowerFallPosition, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66010A)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_BasicHurtAnims))
                    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
                    IfEq(LFlag0, 1)
                        Call(b_area_trd_part_2_red_ninja_koopa_StartRumbleWithParams, 256, 5)
                        Thread
                            Call(ShakeCam, 1, 0, 5, Float(0.7998046875))
                        EndThread
                    EndIf
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66010C)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_BasicToppledAnims))
                    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
                    Call(SetActorFlagBits, ACTOR_SELF, 0x40000, 0)
                    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20000, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(HPBarToHome, ACTOR_SELF)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_ToppledAnims))
                    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_ToppledDefense))
                    Call(SetActorVar, ACTOR_SELF, 1, 1)
                    Call(SetActorVar, ACTOR_SELF, 2, 2)
                    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 18)
                EndCaseGroup
            EndSwitch
        CaseEq(6)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Set(LFlag0, 0)
                    IfEq(LVar0, 3)
                        Set(LFlag0, 1)
                    EndIf
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
                    Call(b_area_trd_part_2_red_ninja_koopa_GetTowerFallPosition, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66010E)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_BasicHurtAnims))
                    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
                    IfEq(LFlag0, 1)
                        Call(b_area_trd_part_2_red_ninja_koopa_StartRumbleWithParams, 256, 5)
                        Thread
                            Call(ShakeCam, 1, 0, 5, Float(0.7998046875))
                        EndThread
                    EndIf
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(GetActorSize, ACTOR_SELF, LVar3, LVar4)
                    DivF(LVar3, Float(2.0))
                    AddF(LVar1, LVar3)
                    AddF(LVar2, Float(5.0))
                    DivF(LVar3, Float(10.0))
                    Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66010C)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_BasicToppledAnims))
                    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
                    Call(SetActorFlagBits, ACTOR_SELF, 0x40000, 0)
                    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20000, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(HPBarToHome, ACTOR_SELF)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_ToppledAnims))
                    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_ToppledDefense))
                    Call(SetActorVar, ACTOR_SELF, 1, 1)
                    Call(SetActorVar, ACTOR_SELF, 2, 2)
                    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 18)
                EndCaseGroup
            EndSwitch
        CaseEq(9)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(1)
                    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
                    Sub(LVar0, 1)
                    IfGt(LVar0, 0)
                        Call(SetActorVar, ACTOR_SELF, 2, LVar0)
                        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                        Wait(20)
                        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                    Else
                        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                        Wait(12)
                        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                        Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
                        Call(PlaySoundAtActor, ACTOR_SELF, 8321)
                        Thread
                            Set(LVar0, 0)
                            Call(SetActorRotationOffset, ACTOR_SELF, 0, 18, 0)
                            Loop(4)
                                Add(LVar0, 22)
                                Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                                Wait(1)
                            EndLoop
                        EndThread
                        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                        Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
                        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                        Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
                        Call(PlaySoundAtActor, ACTOR_SELF, 8378)
                        Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                        Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                        Call(SetTargetOffset, ACTOR_SELF, 1, -5, 36)
                        Call(SetActorVar, ACTOR_SELF, 1, 2)
                        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_DefaultDefense))
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_red_ninja_koopa_DefaultAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x660104)
                        Call(ResetActorSounds, ACTOR_SELF, 2)
                    EndIf
                CaseDefault
                    Wait(20)
            EndSwitch
        CaseEq(10)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(2)
                    Call(SetActorVar, ACTOR_SELF, 1, 0)
            EndSwitch
        CaseEq(7)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(3)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660108)
                    Wait(10)
                    Call(GetActorVar, 516, 3, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(PlaySoundAtActor, ACTOR_SELF, 854)
                        CaseEq(3)
                            Call(PlaySoundAtActor, ACTOR_SELF, 853)
                        CaseEq(2)
                            Call(PlaySoundAtActor, ACTOR_SELF, 852)
                    EndSwitch
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660107)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_red_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 60)
                    Wait(60)
                    ExecWait(TTYD64_trd_part_2_EVS_8041DF10)
                    Call(UseBattleCamPreset, 2)
                    Call(PlaySoundAtActor, ACTOR_SELF, 892)
                    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 1)
                    Call(GetActorVar, 516, 3, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(SetActorSpeed, ACTOR_SELF, Float(13.0))
                        CaseEq(3)
                            Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
                        CaseEq(2)
                            Call(SetActorSpeed, ACTOR_SELF, Float(15.0))
                    EndSwitch
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, -160, LVar1, LVar2)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(ResetActorSounds, ACTOR_SELF, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 0)
                    Thread
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 15, 0)
                        Set(LVar0, 0)
                        Loop(40)
                            Sub(LVar0, 45)
                            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar0)
                            Wait(1)
                        EndLoop
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 0, 0)
                        Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 0)
                    EndThread
                    Call(GetActorVar, 516, 4, LVar1)
                    Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                    Set(LVar4, 15)
                    Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                    Call(GetActorVar, 516, 3, LVarB)
                    Set(LVar0, LVarB)
                    Sub(LVar0, 1)
                    Mul(LVar0, 18)
                    Switch(LVarB)
                        CaseEq(4)
                            Call(AddGoalPos, ACTOR_SELF, 0, LVar0, -10)
                        CaseEq(3)
                            Call(AddGoalPos, ACTOR_SELF, 0, LVar0, -7)
                        CaseEq(2)
                            Call(AddGoalPos, ACTOR_SELF, 0, LVar0, -4)
                    EndSwitch
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
                    Call(JumpToGoal, ACTOR_SELF, 40, 0, 1, 0)
                    Call(GetActorVar, 516, 3, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_red_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 60)
                            Wait(60)
                        CaseEq(3)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_red_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 50)
                            Wait(50)
                        CaseEq(2)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_red_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 40)
                            Wait(40)
                    EndSwitch
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660109)
                    Wait(10)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8435)
                    Call(SetActorYaw, ACTOR_SELF, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66011B)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Sub(LVar0, 22)
                    Add(LVar1, 19)
                    Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660104)
                    Wait(20)
                    Call(SetActorVar, 516, 1, 0)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66011F)
                    Wait(10)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660107)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_red_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 60)
                    Wait(60)
                    Call(EnableActorBlur, ACTOR_SELF, 1)
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
                        CaseEq(5)
                            Call(SetActorSpeed, ACTOR_SELF, Float(15.0))
                        CaseEq(6)
                            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
                    EndSwitch
                    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, -160, LVar1, LVar2)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(ResetActorSounds, ACTOR_SELF, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 0)
                    Thread
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 15, 0)
                        Set(LVar0, 0)
                        Loop(40)
                            Sub(LVar0, 45)
                            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar0)
                            Wait(1)
                        EndLoop
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 0, 0)
                        Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 0)
                    EndThread
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(GetActorVar, 516, 4, LVar1)
                            Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                            Set(LVar4, 15)
                            Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                            Call(AddGoalPos, ACTOR_SELF, 0, 36, -7)
                        CaseEq(5)
                            Call(GetActorVar, 516, 4, LVar1)
                            Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                            Set(LVar4, 15)
                            Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                            Call(AddGoalPos, ACTOR_SELF, 0, 18, -4)
                        CaseEq(6)
                            Call(GetActorVar, 516, 4, LVar1)
                            Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                            Set(LVar4, 15)
                            Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                            Call(AddGoalPos, ACTOR_SELF, 0, 0, 0)
                    EndSwitch
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
                    Call(JumpToGoal, ACTOR_SELF, 40, 0, 1, 0)
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_red_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 50)
                            Wait(50)
                        CaseEq(5)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_red_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 40)
                            Wait(40)
                        CaseEq(6)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_red_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 30)
                            Wait(30)
                    EndSwitch
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660120)
                    Wait(10)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660105)
                    Wait(30)
                EndCaseGroup
            EndSwitch
        CaseEq(8)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(GetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Set(LVar2, 15)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660103)
                    Call(RunToGoal, ACTOR_SELF, 10, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66011F)
                    Wait(10)
                    Call(PlaySoundAtActor, ACTOR_SELF, 851)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660107)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_red_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 30)
                    Wait(30)
                    Thread
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 16)
                        Switch(LVar0)
                            CaseEq(5)
                                Wait(20)
                                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                                Return
                            CaseEq(6)
                                Return
                        EndSwitch
                        Label(0)
                        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                        Call(GetOwnerTarget, LVar1, 0)
                        Call(GetActorPos, LVar1, LVar3, LVar4, LVar5)
                        IfGt(LVar0, LVar3)
                            Wait(1)
                            Goto(0)
                        EndIf
                        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
                        Call(SetGoalToTarget, ACTOR_SELF)
                        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 1, 32)
                    EndThread
                    Call(UseBattleCamPreset, 2)
                    Call(PlaySoundAtActor, ACTOR_SELF, 892)
                    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 1)
                    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, -160, LVar1, LVar2)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(ResetActorSounds, ACTOR_SELF, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 0)
                    Thread
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 15, 0)
                        Set(LVar0, 0)
                        Loop(40)
                            Sub(LVar0, 45)
                            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar0)
                            Wait(1)
                        EndLoop
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 0, 0)
                        Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 0)
                    EndThread
                    Call(GetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Set(LVar2, 15)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
                    Call(JumpToGoal, ACTOR_SELF, 40, 0, 1, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_red_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 30)
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660109)
                    Wait(10)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8435)
                    Call(SetActorYaw, ACTOR_SELF, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66011B)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Sub(LVar0, 22)
                    Add(LVar1, 19)
                    Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660103)
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 10, 0)
                    Call(GetActorVar, 516, 0, LVar0)
                    BitwiseAndConst(LVar0, -513)
                    Call(SetActorVar, 516, 0, LVar0)
            EndSwitch
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_yellow_ninja_koopa_HandleCommand = {
    Call(SetOwnerID, 513)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNe(LVar0, 0)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Switch(LVarA)
        CaseEq(0)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(3)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_DefaultAnims))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660204)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_TowerAnims))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660205)
                EndCaseGroup
            EndSwitch
        CaseEq(1)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Wait(5)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_TippingAnims))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66020D)
                EndCaseGroup
            EndSwitch
        CaseEq(2)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x66020B)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Call(GetActorVar, 516, 0, LVar0)
                    BitwiseAndConst(LVar0, 192)
                    IfNe(LVar0, 192)
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_TippingAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66020D)
                    Else
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_BasicHurtAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66020A)
                    EndIf
                EndCaseGroup
            EndSwitch
        CaseEq(3)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Call(b_area_trd_part_2_yellow_ninja_koopa_GetLastActorEventType, 14)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x66020E)
                    SetConst(LVar2, -1)
                    ExecWait(Ref(EVS_Enemy_BurnHit))
                    Call(GetActorVar, 516, 0, LVar0)
                    BitwiseAndConst(LVar0, 192)
                    IfNe(LVar0, 192)
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_TippingAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66020D)
                    Else
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_BasicHurtAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66020A)
                    EndIf
                EndCaseGroup
            EndSwitch
        CaseEq(4)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(3)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x660208)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660209)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x66021F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660220)
                EndCaseGroup
            EndSwitch
            Wait(15)
        CaseEq(5)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Set(LFlag0, 0)
                    IfEq(LVar0, 3)
                        Set(LFlag0, 1)
                    EndIf
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
                    Call(b_area_trd_part_2_yellow_ninja_koopa_GetTowerFallPosition, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66020A)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_BasicHurtAnims))
                    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
                    IfEq(LFlag0, 1)
                        Call(b_area_trd_part_2_yellow_ninja_koopa_StartRumbleWithParams, 256, 5)
                        Thread
                            Call(ShakeCam, 1, 0, 5, Float(0.7998046875))
                        EndThread
                    EndIf
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66020C)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_BasicToppledAnims))
                    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
                    Call(SetActorFlagBits, ACTOR_SELF, 0x40000, 0)
                    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20000, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(HPBarToHome, ACTOR_SELF)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_ToppledAnims))
                    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_ToppledDefense))
                    Call(SetActorVar, ACTOR_SELF, 1, 1)
                    Call(SetActorVar, ACTOR_SELF, 2, 2)
                    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 18)
                EndCaseGroup
            EndSwitch
        CaseEq(6)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Set(LFlag0, 0)
                    IfEq(LVar0, 3)
                        Set(LFlag0, 1)
                    EndIf
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
                    Call(b_area_trd_part_2_yellow_ninja_koopa_GetTowerFallPosition, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66020E)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_BasicHurtAnims))
                    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
                    IfEq(LFlag0, 1)
                        Call(b_area_trd_part_2_yellow_ninja_koopa_StartRumbleWithParams, 256, 5)
                        Thread
                            Call(ShakeCam, 1, 0, 5, Float(0.7998046875))
                        EndThread
                    EndIf
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(GetActorSize, ACTOR_SELF, LVar3, LVar4)
                    DivF(LVar3, Float(2.0))
                    AddF(LVar1, LVar3)
                    AddF(LVar2, Float(5.0))
                    DivF(LVar3, Float(10.0))
                    Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66020C)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_BasicToppledAnims))
                    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
                    Call(SetActorFlagBits, ACTOR_SELF, 0x40000, 0)
                    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20000, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(HPBarToHome, ACTOR_SELF)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_ToppledAnims))
                    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_ToppledDefense))
                    Call(SetActorVar, ACTOR_SELF, 1, 1)
                    Call(SetActorVar, ACTOR_SELF, 2, 2)
                    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 18)
                EndCaseGroup
            EndSwitch
        CaseEq(9)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(1)
                    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
                    Sub(LVar0, 1)
                    IfGt(LVar0, 0)
                        Call(SetActorVar, ACTOR_SELF, 2, LVar0)
                        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                        Wait(20)
                        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                    Else
                        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                        Wait(12)
                        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                        Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
                        Call(PlaySoundAtActor, ACTOR_SELF, 8321)
                        Thread
                            Set(LVar0, 0)
                            Call(SetActorRotationOffset, ACTOR_SELF, 0, 18, 0)
                            Loop(4)
                                Add(LVar0, 22)
                                Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                                Wait(1)
                            EndLoop
                        EndThread
                        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                        Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
                        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                        Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
                        Call(PlaySoundAtActor, ACTOR_SELF, 8378)
                        Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                        Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                        Call(SetTargetOffset, ACTOR_SELF, 1, -5, 36)
                        Call(SetActorVar, ACTOR_SELF, 1, 2)
                        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_DefaultDefense))
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_yellow_ninja_koopa_DefaultAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x660204)
                        Call(ResetActorSounds, ACTOR_SELF, 2)
                    EndIf
                CaseDefault
                    Wait(20)
            EndSwitch
        CaseEq(10)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(2)
                    Call(SetActorVar, ACTOR_SELF, 1, 0)
            EndSwitch
        CaseEq(7)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(3)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660208)
                    Wait(10)
                    Call(GetActorVar, 516, 3, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(PlaySoundAtActor, ACTOR_SELF, 854)
                        CaseEq(3)
                            Call(PlaySoundAtActor, ACTOR_SELF, 853)
                        CaseEq(2)
                            Call(PlaySoundAtActor, ACTOR_SELF, 852)
                    EndSwitch
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660207)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_yellow_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 60)
                    Wait(60)
                    ExecWait(TTYD64_trd_part_2_EVS_8041DF10)
                    Call(UseBattleCamPreset, 2)
                    Call(PlaySoundAtActor, ACTOR_SELF, 892)
                    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 1)
                    Call(GetActorVar, 516, 3, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(SetActorSpeed, ACTOR_SELF, Float(13.0))
                        CaseEq(3)
                            Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
                        CaseEq(2)
                            Call(SetActorSpeed, ACTOR_SELF, Float(15.0))
                    EndSwitch
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, -160, LVar1, LVar2)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(ResetActorSounds, ACTOR_SELF, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 0)
                    Thread
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 15, 0)
                        Set(LVar0, 0)
                        Loop(40)
                            Sub(LVar0, 45)
                            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar0)
                            Wait(1)
                        EndLoop
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 0, 0)
                        Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 0)
                    EndThread
                    Call(GetActorVar, 516, 4, LVar1)
                    Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                    Set(LVar4, 15)
                    Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                    Call(GetActorVar, 516, 3, LVarB)
                    Set(LVar0, LVarB)
                    Sub(LVar0, 1)
                    Mul(LVar0, 18)
                    Switch(LVarB)
                        CaseEq(4)
                            Call(AddGoalPos, ACTOR_SELF, 0, LVar0, -10)
                        CaseEq(3)
                            Call(AddGoalPos, ACTOR_SELF, 0, LVar0, -7)
                        CaseEq(2)
                            Call(AddGoalPos, ACTOR_SELF, 0, LVar0, -4)
                    EndSwitch
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
                    Call(JumpToGoal, ACTOR_SELF, 40, 0, 1, 0)
                    Call(GetActorVar, 516, 3, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_yellow_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 60)
                            Wait(60)
                        CaseEq(3)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_yellow_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 50)
                            Wait(50)
                        CaseEq(2)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_yellow_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 40)
                            Wait(40)
                    EndSwitch
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660209)
                    Wait(10)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8435)
                    Call(SetActorYaw, ACTOR_SELF, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66021B)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Sub(LVar0, 22)
                    Add(LVar1, 19)
                    Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660204)
                    Wait(20)
                    Call(SetActorVar, 516, 1, 0)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66021F)
                    Wait(10)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660207)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_yellow_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 60)
                    Wait(60)
                    Call(EnableActorBlur, ACTOR_SELF, 1)
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
                        CaseEq(5)
                            Call(SetActorSpeed, ACTOR_SELF, Float(15.0))
                        CaseEq(6)
                            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
                    EndSwitch
                    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, -160, LVar1, LVar2)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(ResetActorSounds, ACTOR_SELF, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 0)
                    Thread
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 15, 0)
                        Set(LVar0, 0)
                        Loop(40)
                            Sub(LVar0, 45)
                            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar0)
                            Wait(1)
                        EndLoop
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 0, 0)
                        Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 0)
                    EndThread
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(GetActorVar, 516, 4, LVar1)
                            Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                            Set(LVar4, 15)
                            Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                            Call(AddGoalPos, ACTOR_SELF, 0, 36, -7)
                        CaseEq(5)
                            Call(GetActorVar, 516, 4, LVar1)
                            Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                            Set(LVar4, 15)
                            Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                            Call(AddGoalPos, ACTOR_SELF, 0, 18, -4)
                        CaseEq(6)
                            Call(GetActorVar, 516, 4, LVar1)
                            Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                            Set(LVar4, 15)
                            Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                            Call(AddGoalPos, ACTOR_SELF, 0, 0, 0)
                    EndSwitch
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
                    Call(JumpToGoal, ACTOR_SELF, 40, 0, 1, 0)
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_yellow_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 50)
                            Wait(50)
                        CaseEq(5)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_yellow_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 40)
                            Wait(40)
                        CaseEq(6)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_yellow_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 30)
                            Wait(30)
                    EndSwitch
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660220)
                    Wait(10)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660205)
                    Wait(30)
                EndCaseGroup
            EndSwitch
        CaseEq(8)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(GetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Set(LVar2, 15)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660203)
                    Call(RunToGoal, ACTOR_SELF, 10, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66021F)
                    Wait(10)
                    Call(PlaySoundAtActor, ACTOR_SELF, 851)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660207)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_yellow_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 30)
                    Wait(30)
                    Thread
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 16)
                        Switch(LVar0)
                            CaseEq(5)
                                Wait(20)
                                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                                Return
                            CaseEq(6)
                                Return
                        EndSwitch
                        Label(0)
                        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                        Call(GetOwnerTarget, LVar1, 0)
                        Call(GetActorPos, LVar1, LVar3, LVar4, LVar5)
                        IfGt(LVar0, LVar3)
                            Wait(1)
                            Goto(0)
                        EndIf
                        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
                        Call(SetGoalToTarget, ACTOR_SELF)
                        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 1, 32)
                    EndThread
                    Call(UseBattleCamPreset, 2)
                    Call(PlaySoundAtActor, ACTOR_SELF, 892)
                    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 1)
                    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, -160, LVar1, LVar2)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(ResetActorSounds, ACTOR_SELF, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 0)
                    Thread
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 15, 0)
                        Set(LVar0, 0)
                        Loop(40)
                            Sub(LVar0, 45)
                            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar0)
                            Wait(1)
                        EndLoop
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 0, 0)
                        Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 0)
                    EndThread
                    Call(GetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Set(LVar2, 15)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
                    Call(JumpToGoal, ACTOR_SELF, 40, 0, 1, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_yellow_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 30)
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660209)
                    Wait(10)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8435)
                    Call(SetActorYaw, ACTOR_SELF, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66021B)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Sub(LVar0, 22)
                    Add(LVar1, 19)
                    Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660203)
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 10, 0)
                    Call(GetActorVar, 516, 0, LVar0)
                    BitwiseAndConst(LVar0, -513)
                    Call(SetActorVar, 516, 0, LVar0)
            EndSwitch
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_black_ninja_koopa_HandleCommand = {
    Call(SetOwnerID, 514)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNe(LVar0, 0)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Switch(LVarA)
        CaseEq(0)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(3)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_DefaultAnims))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660004)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_TowerAnims))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660005)
                EndCaseGroup
            EndSwitch
        CaseEq(1)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Wait(5)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_TippingAnims))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66000D)
                EndCaseGroup
            EndSwitch
        CaseEq(2)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x66000B)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Call(GetActorVar, 516, 0, LVar0)
                    BitwiseAndConst(LVar0, 192)
                    IfNe(LVar0, 192)
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_TippingAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66000D)
                    Else
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_BasicHurtAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66000A)
                    EndIf
                EndCaseGroup
            EndSwitch
        CaseEq(3)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Call(b_area_trd_part_2_black_ninja_koopa_GetLastActorEventType, 14)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x66000E)
                    SetConst(LVar2, -1)
                    ExecWait(Ref(EVS_Enemy_BurnHit))
                    Call(GetActorVar, 516, 0, LVar0)
                    BitwiseAndConst(LVar0, 192)
                    IfNe(LVar0, 192)
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_TippingAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66000D)
                    Else
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_BasicHurtAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66000A)
                    EndIf
                EndCaseGroup
            EndSwitch
        CaseEq(4)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(3)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x660008)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660009)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x66001F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660020)
                EndCaseGroup
            EndSwitch
            Wait(15)
        CaseEq(5)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Set(LFlag0, 0)
                    IfEq(LVar0, 3)
                        Set(LFlag0, 1)
                    EndIf
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
                    Call(b_area_trd_part_2_black_ninja_koopa_GetTowerFallPosition, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66000A)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_BasicHurtAnims))
                    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
                    IfEq(LFlag0, 1)
                        Call(b_area_trd_part_2_black_ninja_koopa_StartRumbleWithParams, 256, 5)
                        Thread
                            Call(ShakeCam, 1, 0, 5, Float(0.7998046875))
                        EndThread
                    EndIf
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66000C)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_BasicToppledAnims))
                    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
                    Call(SetActorFlagBits, ACTOR_SELF, 0x40000, 0)
                    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20000, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(HPBarToHome, ACTOR_SELF)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_ToppledAnims))
                    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_ToppledDefense))
                    Call(SetActorVar, ACTOR_SELF, 1, 1)
                    Call(SetActorVar, ACTOR_SELF, 2, 2)
                    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 18)
                EndCaseGroup
            EndSwitch
        CaseEq(6)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Set(LFlag0, 0)
                    IfEq(LVar0, 3)
                        Set(LFlag0, 1)
                    EndIf
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
                    Call(b_area_trd_part_2_black_ninja_koopa_GetTowerFallPosition, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66000E)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_BasicHurtAnims))
                    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
                    IfEq(LFlag0, 1)
                        Call(b_area_trd_part_2_black_ninja_koopa_StartRumbleWithParams, 256, 5)
                        Thread
                            Call(ShakeCam, 1, 0, 5, Float(0.7998046875))
                        EndThread
                    EndIf
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(GetActorSize, ACTOR_SELF, LVar3, LVar4)
                    DivF(LVar3, Float(2.0))
                    AddF(LVar1, LVar3)
                    AddF(LVar2, Float(5.0))
                    DivF(LVar3, Float(10.0))
                    Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66000C)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_BasicToppledAnims))
                    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
                    Call(SetActorFlagBits, ACTOR_SELF, 0x40000, 0)
                    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20000, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(HPBarToHome, ACTOR_SELF)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_ToppledAnims))
                    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_ToppledDefense))
                    Call(SetActorVar, ACTOR_SELF, 1, 1)
                    Call(SetActorVar, ACTOR_SELF, 2, 2)
                    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 18)
                EndCaseGroup
            EndSwitch
        CaseEq(9)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(1)
                    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
                    Sub(LVar0, 1)
                    IfGt(LVar0, 0)
                        Call(SetActorVar, ACTOR_SELF, 2, LVar0)
                        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                        Wait(20)
                        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                    Else
                        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                        Wait(12)
                        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                        Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
                        Call(PlaySoundAtActor, ACTOR_SELF, 8321)
                        Thread
                            Set(LVar0, 0)
                            Call(SetActorRotationOffset, ACTOR_SELF, 0, 18, 0)
                            Loop(4)
                                Add(LVar0, 22)
                                Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                                Wait(1)
                            EndLoop
                        EndThread
                        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                        Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
                        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                        Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
                        Call(PlaySoundAtActor, ACTOR_SELF, 8378)
                        Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                        Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                        Call(SetTargetOffset, ACTOR_SELF, 1, -5, 36)
                        Call(SetActorVar, ACTOR_SELF, 1, 2)
                        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_DefaultDefense))
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_black_ninja_koopa_DefaultAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x660004)
                        Call(ResetActorSounds, ACTOR_SELF, 2)
                    EndIf
                CaseDefault
                    Wait(20)
            EndSwitch
        CaseEq(10)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(2)
                    Call(SetActorVar, ACTOR_SELF, 1, 0)
            EndSwitch
        CaseEq(7)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(3)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660008)
                    Wait(10)
                    Call(GetActorVar, 516, 3, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(PlaySoundAtActor, ACTOR_SELF, 854)
                        CaseEq(3)
                            Call(PlaySoundAtActor, ACTOR_SELF, 853)
                        CaseEq(2)
                            Call(PlaySoundAtActor, ACTOR_SELF, 852)
                    EndSwitch
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660007)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_black_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 60)
                    Wait(60)
                    ExecWait(TTYD64_trd_part_2_EVS_8041DF10)
                    Call(UseBattleCamPreset, 2)
                    Call(PlaySoundAtActor, ACTOR_SELF, 892)
                    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 1)
                    Call(GetActorVar, 516, 3, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(SetActorSpeed, ACTOR_SELF, Float(13.0))
                        CaseEq(3)
                            Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
                        CaseEq(2)
                            Call(SetActorSpeed, ACTOR_SELF, Float(15.0))
                    EndSwitch
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, -160, LVar1, LVar2)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(ResetActorSounds, ACTOR_SELF, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 0)
                    Thread
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 15, 0)
                        Set(LVar0, 0)
                        Loop(40)
                            Sub(LVar0, 45)
                            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar0)
                            Wait(1)
                        EndLoop
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 0, 0)
                        Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 0)
                    EndThread
                    Call(GetActorVar, 516, 4, LVar1)
                    Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                    Set(LVar4, 15)
                    Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                    Call(GetActorVar, 516, 3, LVarB)
                    Set(LVar0, LVarB)
                    Sub(LVar0, 1)
                    Mul(LVar0, 18)
                    Switch(LVarB)
                        CaseEq(4)
                            Call(AddGoalPos, ACTOR_SELF, 0, LVar0, -10)
                        CaseEq(3)
                            Call(AddGoalPos, ACTOR_SELF, 0, LVar0, -7)
                        CaseEq(2)
                            Call(AddGoalPos, ACTOR_SELF, 0, LVar0, -4)
                    EndSwitch
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
                    Call(JumpToGoal, ACTOR_SELF, 40, 0, 1, 0)
                    Call(GetActorVar, 516, 3, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_black_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 60)
                            Wait(60)
                        CaseEq(3)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_black_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 50)
                            Wait(50)
                        CaseEq(2)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_black_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 40)
                            Wait(40)
                    EndSwitch
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660009)
                    Wait(10)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8435)
                    Call(SetActorYaw, ACTOR_SELF, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66001B)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Sub(LVar0, 22)
                    Add(LVar1, 19)
                    Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660004)
                    Wait(20)
                    Call(SetActorVar, 516, 1, 0)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66001F)
                    Wait(10)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660007)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_black_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 60)
                    Wait(60)
                    Call(EnableActorBlur, ACTOR_SELF, 1)
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
                        CaseEq(5)
                            Call(SetActorSpeed, ACTOR_SELF, Float(15.0))
                        CaseEq(6)
                            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
                    EndSwitch
                    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, -160, LVar1, LVar2)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(ResetActorSounds, ACTOR_SELF, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 0)
                    Thread
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 15, 0)
                        Set(LVar0, 0)
                        Loop(40)
                            Sub(LVar0, 45)
                            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar0)
                            Wait(1)
                        EndLoop
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 0, 0)
                        Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 0)
                    EndThread
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(GetActorVar, 516, 4, LVar1)
                            Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                            Set(LVar4, 15)
                            Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                            Call(AddGoalPos, ACTOR_SELF, 0, 36, -7)
                        CaseEq(5)
                            Call(GetActorVar, 516, 4, LVar1)
                            Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                            Set(LVar4, 15)
                            Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                            Call(AddGoalPos, ACTOR_SELF, 0, 18, -4)
                        CaseEq(6)
                            Call(GetActorVar, 516, 4, LVar1)
                            Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                            Set(LVar4, 15)
                            Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                            Call(AddGoalPos, ACTOR_SELF, 0, 0, 0)
                    EndSwitch
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
                    Call(JumpToGoal, ACTOR_SELF, 40, 0, 1, 0)
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_black_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 50)
                            Wait(50)
                        CaseEq(5)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_black_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 40)
                            Wait(40)
                        CaseEq(6)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_black_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 30)
                            Wait(30)
                    EndSwitch
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660020)
                    Wait(10)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660005)
                    Wait(30)
                EndCaseGroup
            EndSwitch
        CaseEq(8)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(GetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Set(LVar2, 15)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660003)
                    Call(RunToGoal, ACTOR_SELF, 10, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66001F)
                    Wait(10)
                    Call(PlaySoundAtActor, ACTOR_SELF, 851)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660007)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_black_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 30)
                    Wait(30)
                    Thread
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 16)
                        Switch(LVar0)
                            CaseEq(5)
                                Wait(20)
                                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                                Return
                            CaseEq(6)
                                Return
                        EndSwitch
                        Label(0)
                        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                        Call(GetOwnerTarget, LVar1, 0)
                        Call(GetActorPos, LVar1, LVar3, LVar4, LVar5)
                        IfGt(LVar0, LVar3)
                            Wait(1)
                            Goto(0)
                        EndIf
                        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
                        Call(SetGoalToTarget, ACTOR_SELF)
                        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 1, 32)
                    EndThread
                    Call(UseBattleCamPreset, 2)
                    Call(PlaySoundAtActor, ACTOR_SELF, 892)
                    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 1)
                    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, -160, LVar1, LVar2)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(ResetActorSounds, ACTOR_SELF, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 0)
                    Thread
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 15, 0)
                        Set(LVar0, 0)
                        Loop(40)
                            Sub(LVar0, 45)
                            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar0)
                            Wait(1)
                        EndLoop
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 0, 0)
                        Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 0)
                    EndThread
                    Call(GetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Set(LVar2, 15)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
                    Call(JumpToGoal, ACTOR_SELF, 40, 0, 1, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_black_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 30)
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660009)
                    Wait(10)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8435)
                    Call(SetActorYaw, ACTOR_SELF, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66001B)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Sub(LVar0, 22)
                    Add(LVar1, 19)
                    Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660003)
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 10, 0)
                    Call(GetActorVar, 516, 0, LVar0)
                    BitwiseAndConst(LVar0, -513)
                    Call(SetActorVar, 516, 0, LVar0)
            EndSwitch
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_green_ninja_koopa_HandleCommand = {
    Call(SetOwnerID, 512)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNe(LVar0, 0)
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Switch(LVarA)
        CaseEq(0)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(3)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_DefaultAnims))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660304)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_TowerAnims))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660305)
                EndCaseGroup
            EndSwitch
        CaseEq(1)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Wait(5)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_TippingAnims))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66030D)
                EndCaseGroup
            EndSwitch
        CaseEq(2)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x66030B)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Call(GetActorVar, 516, 0, LVar0)
                    BitwiseAndConst(LVar0, 192)
                    IfNe(LVar0, 192)
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_TippingAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66030D)
                    Else
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_BasicHurtAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66030A)
                    EndIf
                EndCaseGroup
            EndSwitch
        CaseEq(3)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Call(b_area_trd_part_2_green_ninja_koopa_GetLastActorEventType, 14)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x66030E)
                    SetConst(LVar2, -1)
                    ExecWait(Ref(EVS_Enemy_BurnHit))
                    Call(GetActorVar, 516, 0, LVar0)
                    BitwiseAndConst(LVar0, 192)
                    IfNe(LVar0, 192)
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_TippingAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66030D)
                    Else
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_BasicHurtAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x66030A)
                    EndIf
                EndCaseGroup
            EndSwitch
        CaseEq(4)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(3)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x660308)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660309)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x66031F)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660320)
                EndCaseGroup
            EndSwitch
            Wait(15)
        CaseEq(5)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Set(LFlag0, 0)
                    IfEq(LVar0, 3)
                        Set(LFlag0, 1)
                    EndIf
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
                    Call(b_area_trd_part_2_green_ninja_koopa_GetTowerFallPosition, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66030A)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_BasicHurtAnims))
                    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
                    IfEq(LFlag0, 1)
                        Call(b_area_trd_part_2_green_ninja_koopa_StartRumbleWithParams, 256, 5)
                        Thread
                            Call(ShakeCam, 1, 0, 5, Float(0.7998046875))
                        EndThread
                    EndIf
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66030C)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_BasicToppledAnims))
                    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
                    Call(SetActorFlagBits, ACTOR_SELF, 0x40000, 0)
                    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20000, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(HPBarToHome, ACTOR_SELF)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_ToppledAnims))
                    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_ToppledDefense))
                    Call(SetActorVar, ACTOR_SELF, 1, 1)
                    Call(SetActorVar, ACTOR_SELF, 2, 2)
                    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 18)
                EndCaseGroup
            EndSwitch
        CaseEq(6)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseOrEq(3)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Set(LFlag0, 0)
                    IfEq(LVar0, 3)
                        Set(LFlag0, 1)
                    EndIf
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
                    Call(b_area_trd_part_2_green_ninja_koopa_GetTowerFallPosition, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66030E)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_BasicHurtAnims))
                    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
                    IfEq(LFlag0, 1)
                        Call(b_area_trd_part_2_green_ninja_koopa_StartRumbleWithParams, 256, 5)
                        Thread
                            Call(ShakeCam, 1, 0, 5, Float(0.7998046875))
                        EndThread
                    EndIf
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(GetActorSize, ACTOR_SELF, LVar3, LVar4)
                    DivF(LVar3, Float(2.0))
                    AddF(LVar1, LVar3)
                    AddF(LVar2, Float(5.0))
                    DivF(LVar3, Float(10.0))
                    Call(PlayEffect_impl, 39, 0, LVar0, LVar1, LVar2, LVar3, 10, 0, 0, 0, 0, 0, 0, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66030C)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_BasicToppledAnims))
                    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
                    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
                    Call(SetActorFlagBits, ACTOR_SELF, 0x40000, 0)
                    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20000, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(HPBarToHome, ACTOR_SELF)
                    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_ToppledAnims))
                    Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_ToppledDefense))
                    Call(SetActorVar, ACTOR_SELF, 1, 1)
                    Call(SetActorVar, ACTOR_SELF, 2, 2)
                    Call(SetTargetOffset, ACTOR_SELF, 1, 0, 18)
                EndCaseGroup
            EndSwitch
        CaseEq(9)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(1)
                    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
                    Sub(LVar0, 1)
                    IfGt(LVar0, 0)
                        Call(SetActorVar, ACTOR_SELF, 2, LVar0)
                        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                        Wait(20)
                        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                    Else
                        Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                        Wait(12)
                        Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                        Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
                        Call(PlaySoundAtActor, ACTOR_SELF, 8321)
                        Thread
                            Set(LVar0, 0)
                            Call(SetActorRotationOffset, ACTOR_SELF, 0, 18, 0)
                            Loop(4)
                                Add(LVar0, 22)
                                Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                                Wait(1)
                            EndLoop
                        EndThread
                        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                        Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
                        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                        Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
                        Call(PlaySoundAtActor, ACTOR_SELF, 8378)
                        Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                        Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                        Call(SetTargetOffset, ACTOR_SELF, 1, -5, 36)
                        Call(SetActorVar, ACTOR_SELF, 1, 2)
                        Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_DefaultDefense))
                        Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(b_area_trd_part_2_green_ninja_koopa_DefaultAnims))
                        Call(SetAnimation, ACTOR_SELF, 1, 0x660304)
                        Call(ResetActorSounds, ACTOR_SELF, 2)
                    EndIf
                CaseDefault
                    Wait(20)
            EndSwitch
        CaseEq(10)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(2)
                    Call(SetActorVar, ACTOR_SELF, 1, 0)
            EndSwitch
        CaseEq(7)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(3)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660308)
                    Wait(10)
                    Call(GetActorVar, 516, 3, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(PlaySoundAtActor, ACTOR_SELF, 854)
                        CaseEq(3)
                            Call(PlaySoundAtActor, ACTOR_SELF, 853)
                        CaseEq(2)
                            Call(PlaySoundAtActor, ACTOR_SELF, 852)
                    EndSwitch
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660307)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_green_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 60)
                    Wait(60)
                    ExecWait(TTYD64_trd_part_2_EVS_8041DF10)
                    Call(UseBattleCamPreset, 2)
                    Call(PlaySoundAtActor, ACTOR_SELF, 892)
                    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 1)
                    Call(GetActorVar, 516, 3, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(SetActorSpeed, ACTOR_SELF, Float(13.0))
                        CaseEq(3)
                            Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
                        CaseEq(2)
                            Call(SetActorSpeed, ACTOR_SELF, Float(15.0))
                    EndSwitch
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, -160, LVar1, LVar2)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(ResetActorSounds, ACTOR_SELF, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 0)
                    Thread
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 15, 0)
                        Set(LVar0, 0)
                        Loop(40)
                            Sub(LVar0, 45)
                            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar0)
                            Wait(1)
                        EndLoop
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 0, 0)
                        Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 0)
                    EndThread
                    Call(GetActorVar, 516, 4, LVar1)
                    Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                    Set(LVar4, 15)
                    Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                    Call(GetActorVar, 516, 3, LVarB)
                    Set(LVar0, LVarB)
                    Sub(LVar0, 1)
                    Mul(LVar0, 18)
                    Switch(LVarB)
                        CaseEq(4)
                            Call(AddGoalPos, ACTOR_SELF, 0, LVar0, -10)
                        CaseEq(3)
                            Call(AddGoalPos, ACTOR_SELF, 0, LVar0, -7)
                        CaseEq(2)
                            Call(AddGoalPos, ACTOR_SELF, 0, LVar0, -4)
                    EndSwitch
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
                    Call(JumpToGoal, ACTOR_SELF, 40, 0, 1, 0)
                    Call(GetActorVar, 516, 3, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_green_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 60)
                            Wait(60)
                        CaseEq(3)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_green_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 50)
                            Wait(50)
                        CaseEq(2)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_green_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 40)
                            Wait(40)
                    EndSwitch
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660309)
                    Wait(10)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8435)
                    Call(SetActorYaw, ACTOR_SELF, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66031B)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Sub(LVar0, 22)
                    Add(LVar1, 19)
                    Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660304)
                    Wait(20)
                    Call(SetActorVar, 516, 1, 0)
                CaseOrEq(4)
                CaseOrEq(5)
                CaseOrEq(6)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66031F)
                    Wait(10)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660307)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_green_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 60)
                    Wait(60)
                    Call(EnableActorBlur, ACTOR_SELF, 1)
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(SetActorSpeed, ACTOR_SELF, Float(14.0))
                        CaseEq(5)
                            Call(SetActorSpeed, ACTOR_SELF, Float(15.0))
                        CaseEq(6)
                            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
                    EndSwitch
                    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, -160, LVar1, LVar2)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(ResetActorSounds, ACTOR_SELF, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 0)
                    Thread
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 15, 0)
                        Set(LVar0, 0)
                        Loop(40)
                            Sub(LVar0, 45)
                            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar0)
                            Wait(1)
                        EndLoop
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 0, 0)
                        Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 0)
                    EndThread
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(GetActorVar, 516, 4, LVar1)
                            Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                            Set(LVar4, 15)
                            Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                            Call(AddGoalPos, ACTOR_SELF, 0, 36, -7)
                        CaseEq(5)
                            Call(GetActorVar, 516, 4, LVar1)
                            Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                            Set(LVar4, 15)
                            Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                            Call(AddGoalPos, ACTOR_SELF, 0, 18, -4)
                        CaseEq(6)
                            Call(GetActorVar, 516, 4, LVar1)
                            Call(GetHomePos, LVar1, LVar2, LVar3, LVar4)
                            Set(LVar4, 15)
                            Call(SetGoalPos, ACTOR_SELF, LVar2, LVar3, LVar4)
                            Call(AddGoalPos, ACTOR_SELF, 0, 0, 0)
                    EndSwitch
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
                    Call(JumpToGoal, ACTOR_SELF, 40, 0, 1, 0)
                    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
                    Switch(LVar0)
                        CaseEq(4)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_green_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 50)
                            Wait(50)
                        CaseEq(5)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_green_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 40)
                            Wait(40)
                        CaseEq(6)
                            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                            Call(b_area_trd_part_2_green_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 30)
                            Wait(30)
                    EndSwitch
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660320)
                    Wait(10)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660305)
                    Wait(30)
                EndCaseGroup
            EndSwitch
        CaseEq(8)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            Switch(LVar0)
                CaseEq(0)
                    Call(GetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Set(LVar2, 15)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660303)
                    Call(RunToGoal, ACTOR_SELF, 10, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66031F)
                    Wait(10)
                    Call(PlaySoundAtActor, ACTOR_SELF, 851)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660307)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_green_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 30)
                    Wait(30)
                    Thread
                        Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 16)
                        Switch(LVar0)
                            CaseEq(5)
                                Wait(20)
                                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                                Return
                            CaseEq(6)
                                Return
                        EndSwitch
                        Label(0)
                        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                        Call(GetOwnerTarget, LVar1, 0)
                        Call(GetActorPos, LVar1, LVar3, LVar4, LVar5)
                        IfGt(LVar0, LVar3)
                            Wait(1)
                            Goto(0)
                        EndIf
                        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
                        Call(SetGoalToTarget, ACTOR_SELF)
                        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 1, 32)
                    EndThread
                    Call(UseBattleCamPreset, 2)
                    Call(PlaySoundAtActor, ACTOR_SELF, 892)
                    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 1)
                    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetGoalPos, ACTOR_SELF, -160, LVar1, LVar2)
                    Call(RunToGoal, ACTOR_SELF, 0, 0)
                    Call(ResetActorSounds, ACTOR_SELF, 0)
                    Call(EnableActorBlur, ACTOR_SELF, 0)
                    Thread
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 15, 0)
                        Set(LVar0, 0)
                        Loop(40)
                            Sub(LVar0, 45)
                            Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, LVar0)
                            Wait(1)
                        EndLoop
                        Call(SetPartRotationOffset, ACTOR_SELF, 1, 0, 0, 0)
                        Call(SetPartRotation, ACTOR_SELF, 1, 0, 0, 0)
                    EndThread
                    Call(GetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Set(LVar2, 15)
                    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
                    Call(JumpToGoal, ACTOR_SELF, 40, 0, 1, 0)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Call(b_area_trd_part_2_green_ninja_koopa_SpawnSpinEffect, LVar0, LVar1, LVar2, 30)
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660309)
                    Wait(10)
                    Call(PlaySoundAtActor, ACTOR_SELF, 8435)
                    Call(SetActorYaw, ACTOR_SELF, 0)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x66031B)
                    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                    Sub(LVar0, 22)
                    Add(LVar1, 19)
                    Call(PlayEffect_impl, 26, 0, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
                    Wait(30)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x660303)
                    Call(SetGoalToHome, ACTOR_SELF)
                    Call(RunToGoal, ACTOR_SELF, 10, 0)
                    Call(GetActorVar, 516, 0, LVar0)
                    BitwiseAndConst(LVar0, -513)
                    Call(SetActorVar, 516, 0, LVar0)
            EndSwitch
    EndSwitch
    Return
    End
};
// clang-format on

Stage TTYD64_trd_part_2_trd_00 = {
    .texture = "trd_tex",
    .shape = "trd_bt00_shape",
    .hit = "trd_bt00_hit",
    .preBattle = &TTYD64_trd_part_2_trd_00_EVS_PreBattle,
    .postBattle = &b_area_trd_part_2_trd_00_EVS_PostBattle,
    .bg = NULL,
    .foregroundModelList = b_area_trd_part_2_trd_00_ForegroundModels,
    .stageEnemyCount = 0,
    .stageFormation = NULL,
    .stageEnemyChance = 0,
};

// clang-format off
EvtScript TTYD64_trd_part_2_trd_00_EVS_PreBattle = {
    Call(SetSpriteShading, -1)
    Call(SetCamBGColor, 1, 0, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_fake_bowser_EVS_FakeBowser_TakeTurn = {
    Set(LVar0, Ref(FakeBowserAnimState))
    UseArray(LVar0)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Thread
        Loop(4)
            Call(b_area_trd_part_2_fake_bowser_StartRumbleWithParams, 256, 3)
            Wait(5)
        EndLoop
    EndThread
    Set(ArrayVar(0), 4)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 70, 0, 0)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Set(ArrayVar(0), 0)
    Thread
        Call(PlaySoundAtActor, ACTOR_SELF, 8445)
        Wait(22)
        Call(PlaySoundAtActor, ACTOR_SELF, 8446)
    EndThread
    Set(ArrayVar(0), 6)
    Wait(24)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVar0, 5)
                Thread
                    Wait(15)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndThread
            EndIf
            Wait(8)
            Thread
                Loop(4)
                    Call(b_area_trd_part_2_fake_bowser_StartRumbleWithParams, 256, 5)
                    Wait(8)
                EndLoop
            EndThread
            Set(ArrayVar(0), 4)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Set(ArrayVar(0), 0)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0xFFFF, 0, 1, 64)
    Call(GetBattleFlags, LVar0)
    IfFlag(LVar0, (-0x7FFFFFFF - 1))
        Call(GetOwnerTarget, LVar0, 0)
        IfEq(LVar0, 0)
            Call(GetPlayerHP, LVar0)
        Else
            Call(TTYD64_GetPartnerHP_API, LVar0)
        EndIf
        IfNe(LVar0, 0)
            Set(ArrayVar(0), 10)
        EndIf
    EndIf
    Wait(18)
    Thread
        Loop(4)
            Call(b_area_trd_part_2_fake_bowser_StartRumbleWithParams, 256, 5)
            Wait(8)
        EndLoop
    EndThread
    Set(ArrayVar(0), 4)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Set(ArrayVar(0), 0)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Call(GetOwnerTarget, LVar0, 0)
    IfEq(LVar0, 0)
        Call(GetPlayerHP, LVar0)
    Else
        Call(TTYD64_GetPartnerHP_API, LVar0)
    EndIf
    IfLe(LVar0, 0)
        Return
    EndIf
    Call(EnableBattleStatusBar, 0)
    Call(UseBattleCamPreset, 19)
    Call(SetBattleCamTarget, 28, 75, -101)
    Call(SetBattleCamOffsetY, 0)
    Call(SetBattleCamDist, 500)
    Call(MoveBattleCamOver, 20)
    Wait(15)
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(ActorSpeak, 0xC00FE, ACTOR_SELF, 1, -1, -1)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
        CaseEq(1)
            Call(ActorSpeak, 0xC00FF, ACTOR_SELF, 1, -1, -1)
            Call(SetActorVar, ACTOR_SELF, 2, 2)
        CaseEq(2)
            Call(ActorSpeak, 0xC0100, ACTOR_SELF, 1, -1, -1)
            Call(UseBattleCamPreset, 19)
            Call(SetBattleCamTarget, 85, 81, 0)
            Call(SetBattleCamOffsetY, 0)
            Call(SetBattleCamDist, 249)
            Call(MoveBattleCamOver, 10)
            Wait(10)
            Call(ActorSpeak, 0xC0101, ACTOR_SELF, 1, -1, -1)
            Wait(10)
            Call(ActorSpeak, 0xC0102, ACTOR_SELF, 1, -1, -1)
            Call(SetActorVar, ACTOR_SELF, 2, 3)
        CaseEq(3)
            Call(ActorSpeak, 0xC0103, ACTOR_SELF, 1, -1, -1)
            Call(UseBattleCamPreset, 19)
            Call(SetBattleCamTarget, 85, 81, 0)
            Call(SetBattleCamOffsetY, 0)
            Call(SetBattleCamDist, 249)
            Call(MoveBattleCamOver, 10)
            Wait(10)
            Call(ActorSpeak, 0xC0104, ACTOR_SELF, 1, -1, -1)
            Wait(10)
            Call(ActorSpeak, 0xC0105, ACTOR_SELF, 1, -1, -1)
            Call(SetActorVar, ACTOR_SELF, 2, 1)
    EndSwitch
    Call(EnableBattleStatusBar, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_2_EVS_8041DF10 = {
    Thread
        Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 16)
        Switch(LVar0)
            CaseEq(5)
                Wait(20)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                Call(TTYD64_GetPartnerHP_API, LVar0)
                IfLe(LVar0, 0)
                    Return
                EndIf
            CaseEq(6)
                Call(TTYD64_GetPartnerHP_API, LVar0)
                IfLe(LVar0, 0)
                    Return
                EndIf
        EndSwitch
        Call(GetActorVar, 516, 4, LVarA)
        Label(0)
        Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
        Call(GetOwnerTarget, LVar1, 0)
        Call(GetActorPos, LVar1, LVar3, LVar4, LVar5)
        IfGt(LVar0, LVar3)
            Wait(1)
            Goto(0)
        EndIf
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetActorVar, 516, 3, LVar1)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, LVar1, 32)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 16)
        Switch(LVar0)
            CaseOrEq(5)
            CaseOrEq(6)
                IfEq(LVar0, 6)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
            EndCaseGroup
            CaseDefault
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, LVar1, 32)
        EndSwitch
    EndThread
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Return
    End
};
// clang-format on

void TTYD64_InstallBattles_trd_part_2(void) {
    Mod_SetBattleList("TTYD64", 7, TTYD64_trd_part_2_Formations);
    Mod_SetStageList("TTYD64", 7, TTYD64_trd_part_2_Stages);
}
