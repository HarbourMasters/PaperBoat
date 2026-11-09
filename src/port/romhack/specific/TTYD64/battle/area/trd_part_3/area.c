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

API_CALLABLE(ActorSpeak);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(EnableActorBlur);
API_CALLABLE(FlyToGoal);
API_CALLABLE(GetBattleState);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetBattleFlagBits2);
API_CALLABLE(SetBattleMenuEnabledFlags);
API_CALLABLE(SetBattleState);
API_CALLABLE(SetEnabledStarPowers);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetPartAlpha);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(WaitForState);
API_CALLABLE(b_area_trd_part_3_eldstar_ClearPlayerMenuSelections);
API_CALLABLE(b_area_trd_part_3_eldstar_StartBlinkingSP);
API_CALLABLE(b_area_trd_part_3_eldstar_StopBlinkingSP);
API_CALLABLE(b_area_trd_part_3_eldstar_func_80218170_4CF320);
extern ActorPartBlueprint b_area_trd_part_3_eldstar_ActorParts[];
extern EvtScript b_area_trd_part_3_eldstar_EVS_HandleEvent;
extern EvtScript b_area_trd_part_3_eldstar_EVS_Idle;
extern EvtScript b_area_trd_part_3_eldstar_EVS_TakeTurn;
extern s32 b_area_trd_part_3_eldstar_StatusTable[];
extern Stage b_area_trd_part_3_nok_01;
extern EvtScript TTYD64_trd_part_3_eldstar_EVS_ManageTutorial;
extern EvtScript TTYD64_trd_part_3_eldstar_EVS_Init;
extern ActorBlueprint TTYD64_trd_part_3_eldstar;
extern Battle TTYD64_trd_part_3_Formations[];
extern FormationRow TTYD64_trd_part_3_Formation_00[];

// clang-format off
EvtScript TTYD64_trd_part_3_eldstar_EVS_ManageTutorial = {
    Call(SetBattleFlagBits, 0x2000000, 1)
    Call(b_area_trd_part_3_eldstar_ClearPlayerMenuSelections)
    Call(WaitForState, 13)
    Call(SetAnimation, 0, 0, 0x10002)
    Wait(15)
    Call(UseIdleAnimation, 0, 0)
    Call(ActorSpeak, 0xC0114, ACTOR_SELF, 1, 0x120002, 0x120001)
    Thread
        Call(EnableActorBlur, ACTOR_SELF, 1)
        Call(SetGoalPos, ACTOR_SELF, -46, 100, 0)
        Call(FlyToGoal, ACTOR_SELF, 20, 0, 10)
        Call(EnableActorBlur, ACTOR_SELF, 0)
        Call(SetAnimation, 0, 0, 0x1002A)
    EndThread
    Wait(10)
    Call(b_area_trd_part_3_eldstar_StartBlinkingSP)
    Wait(120)
    Call(b_area_trd_part_3_eldstar_StopBlinkingSP)
    Call(SetAnimation, 0, 0, 0x10002)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(EnableActorBlur, ACTOR_SELF, 1)
    Call(FlyToGoal, ACTOR_SELF, 20, 0, 10)
    Call(EnableActorBlur, ACTOR_SELF, 0)
    Call(ActorSpeak, 0xC0115, ACTOR_SELF, 1, 0x120002, 0x120001)
    Wait(10)
    Call(SetAnimation, 0, 0, 0x1002A)
    Call(b_area_trd_part_3_eldstar_StartBlinkingSP)
    Wait(120)
    Call(b_area_trd_part_3_eldstar_StopBlinkingSP)
    Call(SetAnimation, 0, 0, 0x10002)
    Call(ActorSpeak, 0xC0116, ACTOR_SELF, 1, 0x120002, 0x120001)
    Wait(10)
    Call(SetBattleMenuEnabledFlags, 256)
    Call(SetEnabledStarPowers, 2)
    Call(WaitForState, 18)
    Set(LVar0, 255)
    Loop(10)
        Sub(LVar0, 25)
        IfLt(LVar0, 0)
            Set(LVar0, 0)
        EndIf
        Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_SELF, 1, 0)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
    Thread
        Call(b_area_trd_part_3_eldstar_func_80218170_4CF320)
    EndThread
    Call(WaitForState, 22)
    Set(LVar0, 0)
    Loop(10)
        Add(LVar0, 25)
        IfGt(LVar0, 255)
            Set(LVar0, 255)
        EndIf
        Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_SELF, 1, 255)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 0)
    Call(ActorSpeak, 0xC0117, ACTOR_SELF, 1, 0x120002, 0x120001)
    Wait(10)
    Call(UseIdleAnimation, 0, 0)
    Call(SetAnimation, 0, 0, 0x1002A)
    Call(b_area_trd_part_3_eldstar_StartBlinkingSP)
    Wait(120)
    Call(b_area_trd_part_3_eldstar_StopBlinkingSP)
    Call(SetAnimation, 0, 0, 0x10002)
    Call(ActorSpeak, 0xC0118, ACTOR_SELF, 1, 0x120002, 0x120001)
    Wait(10)
    Call(SetBattleState, 6)
    Call(WaitForState, 5)
    Wait(20)
    Call(ActorSpeak, 0xC0119, ACTOR_SELF, 1, 0x120002, 0x120001)
    Wait(10)
    Call(UseIdleAnimation, 0, 0)
    Thread
        Call(EnableActorBlur, ACTOR_SELF, 1)
        Call(SetGoalPos, ACTOR_SELF, -46, 100, 0)
        Call(FlyToGoal, ACTOR_SELF, 20, 0, 10)
        Call(EnableActorBlur, ACTOR_SELF, 0)
        Call(SetAnimation, 0, 0, 0x1002A)
    EndThread
    Wait(10)
    Call(SetAnimation, 0, 0, 0x1002A)
    Call(b_area_trd_part_3_eldstar_StartBlinkingSP)
    Wait(120)
    Call(b_area_trd_part_3_eldstar_StopBlinkingSP)
    Call(SetAnimation, 0, 0, 0x10002)
    Call(SetAnimation, 0, 0, 0x10002)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(EnableActorBlur, ACTOR_SELF, 1)
    Call(FlyToGoal, ACTOR_SELF, 20, 0, 10)
    Call(EnableActorBlur, ACTOR_SELF, 0)
    Call(ActorSpeak, 0xC011A, ACTOR_SELF, 1, 0x120002, 0x120001)
    Wait(10)
    Call(ActorSpeak, 0xC011B, ACTOR_SELF, 1, 0x120002, 0x120001)
    Wait(10)
    Call(SetBattleMenuEnabledFlags, 128)
    Call(SetBattleFlagBits, 0x2000000, 0)
    Call(SetBattleFlagBits2, 32, 0)
    Call(b_area_trd_part_3_eldstar_ClearPlayerMenuSelections)
    Thread
        Loop(0)
            Call(SetBattleFlagBits2, 4, 1)
            Call(GetBattleState, LVar0)
            IfEq(LVar0, 18)
                Call(SetBattleFlagBits2, 4, 0)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndThread
    Call(WaitForState, 18)
    Set(LVar0, 255)
    Loop(10)
        Sub(LVar0, 25)
        IfLt(LVar0, 0)
            Set(LVar0, 0)
        EndIf
        Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_SELF, 1, 0)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
    Thread
        Call(b_area_trd_part_3_eldstar_func_80218170_4CF320)
    EndThread
    Call(WaitForState, 22)
    Set(LVar0, 0)
    Loop(10)
        Add(LVar0, 25)
        IfGt(LVar0, 255)
            Set(LVar0, 255)
        EndIf
        Call(SetPartAlpha, ACTOR_SELF, 1, LVar0)
        Wait(1)
    EndLoop
    Call(SetPartAlpha, ACTOR_SELF, 1, 255)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 0)
    Call(ActorSpeak, 0xC011C, ACTOR_SELF, 1, 0x120002, 0x120001)
    Wait(10)
    Call(UseIdleAnimation, 0, 0)
    Call(SetAnimation, 0, 0, 0x1002A)
    Call(b_area_trd_part_3_eldstar_StartBlinkingSP)
    Wait(120)
    Call(b_area_trd_part_3_eldstar_StopBlinkingSP)
    Call(SetAnimation, 0, 0, 0x10002)
    Call(ActorSpeak, 0xC011D, ACTOR_SELF, 1, 0x120002, 0x120001)
    Call(WaitForState, 0)
    Call(SetBattleState, 30)
    Wait(0x2710)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_3_eldstar_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(b_area_trd_part_3_eldstar_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_trd_part_3_eldstar_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_trd_part_3_eldstar_EVS_HandleEvent))
    Exec(TTYD64_trd_part_3_eldstar_EVS_ManageTutorial)
    Return
    End
};
// clang-format on

ActorBlueprint TTYD64_trd_part_3_eldstar = {
    .flags = 0x240000,
    .maxHP = 99,
    .type = 0x9F,
    .level = 99,
    .partCount = 1,
    .partsData = b_area_trd_part_3_eldstar_ActorParts,
    .initScript = &TTYD64_trd_part_3_eldstar_EVS_Init,
    .statusTable = b_area_trd_part_3_eldstar_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 0,
    .size = { 24, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

Battle TTYD64_trd_part_3_Formations[] = {
    { .name = "{Wn[D \354\257\301\343\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_trd_part_3_Formation_00,
      .stage = &b_area_trd_part_3_nok_01,
      .onBattleStart = NULL },
    {},
};

FormationRow TTYD64_trd_part_3_Formation_00[] = {
    { .actor = &TTYD64_trd_part_3_eldstar,
      .home = { .index = 6 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

void TTYD64_InstallBattles_trd_part_3(void) {
    Mod_SetBattleList("TTYD64", 8, TTYD64_trd_part_3_Formations);
}
