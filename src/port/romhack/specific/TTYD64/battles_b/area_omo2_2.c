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

API_CALLABLE(b_area_omo2_2_stilt_guy_SetActorLevelToZero);
extern ActorBlueprint b_area_omo2_2_stilt_guy;
extern ActorPartBlueprint b_area_omo2_2_stilt_guy_ActorParts[];
extern EvtScript b_area_omo2_2_stilt_guy_EVS_Death;
extern EvtScript b_area_omo2_2_stilt_guy_EVS_Idle;
extern EvtScript b_area_omo2_2_stilt_guy_EVS_RegisterComboHit;
extern EvtScript b_area_omo2_2_stilt_guy_EVS_RegisterHit;
extern EvtScript b_area_omo2_2_stilt_guy_EVS_ReturnHome;
extern EvtScript b_area_omo2_2_stilt_guy_EVS_ShyGuy_HandleEvent;
extern EvtScript b_area_omo2_2_stilt_guy_EVS_ShyGuy_Idle;
extern EvtScript b_area_omo2_2_stilt_guy_EVS_ShyGuy_ReturnHome;
extern s32 b_area_omo2_2_stilt_guy_StatusTable[];
extern ActorBlueprint TTYD64_omo2_2_StiltGuy;
extern EvtScript TTYD64_omo2_2_Script_Init_80231440;
extern EvtScript TTYD64_omo2_2_Script_HandleEvent_8023239C;
extern EvtScript TTYD64_omo2_2_Script_TakeTurn_80232C78;
extern EvtScript TTYD64_omo2_2_Script_80232C94;
extern EvtScript TTYD64_omo2_2_Script_802333A4;
extern EvtScript TTYD64_omo2_2_Script_80234580;
extern EvtScript TTYD64_omo2_2_Script_TakeTurn_80235830;
extern EvtScript TTYD64_omo2_2_Script_80234CA8;

ActorBlueprint TTYD64_omo2_2_StiltGuy = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0xA6,
    .level = 0,
    .partCount = 8,
    .partsData = b_area_omo2_2_stilt_guy_ActorParts,
    .initScript = &TTYD64_omo2_2_Script_Init_80231440,
    .statusTable = b_area_omo2_2_stilt_guy_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 30, 75 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 70 },
    .statusTextOffset = { 10, 65 },
};

// clang-format off
EvtScript TTYD64_omo2_2_Script_Init_80231440 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo2_2_Script_TakeTurn_80232C78))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo2_2_stilt_guy_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_omo2_2_Script_HandleEvent_8023239C))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetPartTargetFlagBits, ACTOR_SELF, 4, 1, 1)
    Call(SetPartSize, ACTOR_SELF, 1, 24, 30)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetPartRotationOffset, ACTOR_SELF, 8, 0, 13, 0)
    Call(SetPartRotationOffset, ACTOR_SELF, 7, 0, 13, 0)
    Call(SetPartRotationOffset, ACTOR_SELF, 6, 0, 13, 0)
    Call(SetPartRotationOffset, ACTOR_SELF, 5, 0, 13, 0)
    Thread
        Set(LVar0, 90)
        Set(LVar1, 270)
        Loop(5)
            Loop(2)
                Label(0)
                Call(SetPartRotation, ACTOR_SELF, 8, LVar1, 0, 0)
                Wait(1)
                Sub(LVar1, LVar0)
                IfGe(LVar1, -90)
                    Goto(0)
                EndIf
                Add(LVar1, 360)
            EndLoop
            Sub(LVar0, 15)
        EndLoop
        Call(SetPartRotation, ACTOR_SELF, 8, -90, 0, 0)
    EndThread
    Thread
        Call(SetPartJumpGravity, ACTOR_SELF, 8, Float(0.6005859375))
        Call(SetAnimation, ACTOR_SELF, 8, 0x710003)
        Call(GetActorPos, 512, LVar0, LVar1, LVar2)
        Call(GetActorVar, ACTOR_SELF, 0, LVar1)
        IfEq(LVar1, 0)
            Set(LVar0, 10)
            Call(PlaySound, 773)
        Else
            Set(LVar0, 50)
            Call(PlaySound, 774)
        EndIf
        Sub(LVar2, 13)
        Call(SetPartPos, ACTOR_SELF, 8, LVar0, 200, LVar2)
        Call(SetActorPos, ACTOR_SELF, LVar0, 200, LVar2)
        Call(SetAnimation, 512, 1, 0x760002)
        Call(SetAnimation, 512, 1, 0x76000A)
        Call(PlaySoundAtPart, 512, 1, 917)
        Call(SetPartFlagBits, ACTOR_SELF, 8, 1, 0)
        Call(FallPartTo, ACTOR_SELF, 8, LVar0, -9, LVar2, 80)
    EndThread
    Thread
        Wait(15)
        Set(LVar0, 90)
        Set(LVar1, 450)
        Loop(5)
            Loop(2)
                Label(1)
                Call(SetPartRotation, ACTOR_SELF, 7, LVar1, 0, 0)
                Wait(1)
                Sub(LVar1, LVar0)
                IfGe(LVar1, 90)
                    Goto(1)
                EndIf
                Add(LVar1, 360)
            EndLoop
            Sub(LVar0, 15)
        EndLoop
        Call(SetPartRotation, ACTOR_SELF, 7, 90, 0, 0)
    EndThread
    Thread
        Call(SetPartJumpGravity, ACTOR_SELF, 7, Float(0.6005859375))
        Call(SetAnimation, ACTOR_SELF, 7, 0x710002)
        Call(GetActorPos, 512, LVar0, LVar1, LVar2)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        IfEq(LVar0, 0)
            Set(LVar0, 10)
        Else
            Set(LVar0, 50)
        EndIf
        Sub(LVar2, 13)
        Call(SetPartPos, ACTOR_SELF, 7, LVar0, 200, LVar2)
        Wait(15)
        Call(SetPartFlagBits, ACTOR_SELF, 7, 1, 0)
        Call(FallPartTo, ACTOR_SELF, 7, LVar0, -9, LVar2, 80)
    EndThread
    Thread
        Wait(30)
        Set(LVar0, 90)
        Set(LVar1, 270)
        Loop(5)
            Loop(2)
                Label(2)
                Call(SetPartRotation, ACTOR_SELF, 6, LVar1, 0, 0)
                Wait(1)
                Sub(LVar1, LVar0)
                IfGe(LVar1, -90)
                    Goto(2)
                EndIf
                Add(LVar1, 360)
            EndLoop
            Sub(LVar0, 15)
        EndLoop
        Call(SetPartRotation, ACTOR_SELF, 6, -90, 0, 0)
    EndThread
    Thread
        Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.6005859375))
        Call(SetAnimation, ACTOR_SELF, 6, 0x710001)
        Call(GetActorPos, 512, LVar0, LVar1, LVar2)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        IfEq(LVar0, 0)
            Set(LVar0, 10)
        Else
            Set(LVar0, 50)
        EndIf
        Sub(LVar2, 13)
        Call(SetPartPos, ACTOR_SELF, 6, LVar0, 200, LVar2)
        Wait(30)
        Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
        Call(FallPartTo, ACTOR_SELF, 6, LVar0, -9, LVar2, 80)
    EndThread
    Thread
        Wait(45)
        Set(LVar0, 90)
        Set(LVar1, 450)
        Loop(5)
            Loop(2)
                Label(3)
                Call(SetPartRotation, ACTOR_SELF, 5, LVar1, 0, 0)
                Wait(1)
                Sub(LVar1, LVar0)
                IfGe(LVar1, 90)
                    Goto(3)
                EndIf
                Add(LVar1, 360)
            EndLoop
            Sub(LVar0, 15)
        EndLoop
        Call(SetPartRotation, ACTOR_SELF, 5, 90, 0, 0)
    EndThread
    Thread
        Call(SetPartJumpGravity, ACTOR_SELF, 5, Float(0.6005859375))
        Call(SetAnimation, ACTOR_SELF, 5, 0x710000)
        Call(GetActorPos, 512, LVar0, LVar1, LVar2)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        IfEq(LVar0, 0)
            Set(LVar0, 10)
        Else
            Set(LVar0, 50)
        EndIf
        Sub(LVar2, 13)
        Call(SetPartPos, ACTOR_SELF, 5, LVar0, 200, LVar2)
        Wait(45)
        Call(SetPartFlagBits, ACTOR_SELF, 5, 1, 0)
        Call(FallPartTo, ACTOR_SELF, 5, LVar0, -9, LVar2, 80)
        Wait(15)
        Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
        Call(SetPartFlagBits, ACTOR_SELF, 7, 1, 1)
        Call(SetPartFlagBits, ACTOR_SELF, 8, 1, 1)
        Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
        Call(GetPartOffset, ACTOR_SELF, 8, LVar0, LVar1, LVar2)
        Add(LVar2, 13)
        Call(ForceHomePos, ACTOR_SELF, LVar0, 0, LVar2)
        Call(SetPartPos, ACTOR_SELF, 5, LVar0, 0, LVar2)
        Call(GetPartOffset, ACTOR_SELF, 5, LVar0, LVar1, LVar2)
        Call(SetPartPos, ACTOR_SELF, 5, LVar0, 0, LVar2)
        Call(SetPartRotation, ACTOR_SELF, 5, 0, 0, 0)
        Call(SetPartRotationOffset, ACTOR_SELF, 8, 0, 0, 0)
        Call(SetPartRotationOffset, ACTOR_SELF, 7, 0, 0, 0)
        Call(SetPartRotationOffset, ACTOR_SELF, 6, 0, 0, 0)
        Call(SetPartRotationOffset, ACTOR_SELF, 5, 0, 0, 0)
        Call(PlaySoundAtPart, ACTOR_SELF, 5, 8293)
        Call(SetAnimation, ACTOR_SELF, 5, 0x710005)
        Call(EnableActorPaletteEffects, ACTOR_SELF, 5, 1)
        Call(SetActorPaletteSwapParams, ACTOR_SELF, 5, 1, 0, 0, 36, 0, 255, 0, 0)
        Call(SetActorPaletteEffect, ACTOR_SELF, 5, 16)
        Wait(18)
        Call(EnableActorPaletteEffects, ACTOR_SELF, 5, 0)
        Call(SetAnimation, ACTOR_SELF, 5, 0x710004)
        Wait(5)
        Loop(20)
            Call(SetPartFlagBits, ACTOR_SELF, 5, 1, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Wait(1)
            Call(SetPartFlagBits, ACTOR_SELF, 5, 1, 1)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
            Wait(1)
        EndLoop
        Call(HPBarToHome, ACTOR_SELF)
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        IfEq(LVar0, 1)
            Call(SetActorVar, 513, 1, 3)
        Else
        EndIf
    EndThread
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_2_Script_HandleEvent_8023239C = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetLastElement, LVarF)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(56)
        CaseEq(9)
            ExecWait(b_area_omo2_2_stilt_guy_EVS_RegisterComboHit)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x700006)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(23)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x700006)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseOrEq(25)
        CaseOrEq(10)
        CaseOrEq(11)
        CaseOrEq(17)
            Call(GetBattleFlags, LVar2)
            IfFlag(LVar2, 0x80000)
                Call(GetMenuSelection, LVar0, LVar1, LVar2)
                IfEq(LVar2, 183)
                    Set(LVar0, 2)
                    Set(LVar1, 0x700001)
                    ExecWait(Ref(EVS_Enemy_NoDamageHit))
                    Call(UseIdleAnimation, ACTOR_SELF, 1)
                    Call(SetActorVar, ACTOR_SELF, 1, 0)
                    Return
                EndIf
            EndIf
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x700006)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_omo2_2_stilt_guy_EVS_RegisterHit)
            Call(GetActorVar, ACTOR_SELF, 1, LVar0)
            IfNe(LVar0, 0)
                ExecWait(TTYD64_omo2_2_Script_802333A4)
            EndIf
            Call(SetActorVar, ACTOR_SELF, 1, 0)
        EndCaseGroup
        CaseEq(58)
            Call(SetAnimation, ACTOR_SELF, 2, 0x700006)
            Wait(1000)
        CaseEq(31)
            Set(LVar0, 2)
            Set(LVar1, 0x700001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(14)
            Call(GetDamageSource, LVar0)
            IfNe(LVar0, 9)
                Set(LVar0, 2)
                Set(LVar1, 0x700009)
                Set(LVar2, 0x70000A)
                ExecWait(Ref(EVS_Enemy_BurnHit))
            Else
                Set(LVar0, 2)
                Set(LVar1, 0x700009)
                Set(LVar2, 0x70000A)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                ExecWait(TTYD64_omo2_2_Script_802333A4)
            EndIf
        CaseEq(36)
            Set(LVar0, 2)
            Set(LVar1, 0x700009)
            Set(LVar2, 0x70000A)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x70000A)
            ExecWait(b_area_omo2_2_stilt_guy_EVS_Death)
            Return
        CaseEq(33)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x700006)
            ExecWait(Ref(EVS_Enemy_Hit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x700007)
            ExecWait(b_area_omo2_2_stilt_guy_EVS_Death)
            Return
        CaseEq(47)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x700006)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            ExecWait(b_area_omo2_2_stilt_guy_EVS_ReturnHome)
        CaseEq(38)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x700006)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x700007)
            ExecWait(b_area_omo2_2_stilt_guy_EVS_Death)
            Return
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x700006)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x700007)
            ExecWait(b_area_omo2_2_stilt_guy_EVS_Death)
            Return
        CaseEq(53)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            ExecWait(b_area_omo2_2_stilt_guy_EVS_ReturnHome)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x700001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(48)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x700006)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(1000)
        CaseEq(57)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x700003)
            SetConst(LVar2, 0x700003)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_2_Script_TakeTurn_80232C78 = {
    ExecWait(TTYD64_omo2_2_Script_80232C94)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_2_Script_80232C94 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamOffsetY, 40)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x700003)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x700004)
    Wait(8)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Wait(9)
                Call(SetAnimation, ACTOR_SELF, 2, 0x700004)
            EndThread
            Call(SetAnimation, ACTOR_SELF, 2, 0x700005)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 15)
            Set(LVar1, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(PlaySoundAtActor, ACTOR_SELF, 751)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 18, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8294)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 25)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8294)
            Wait(15)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_omo2_2_stilt_guy_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 2, 0x700004)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 2, 0x700005)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
    Call(PlaySoundAtActor, ACTOR_SELF, 751)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 8, 0, 4, 32)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(UseBattleCamPreset, 2)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8294)
            Call(SetAnimation, ACTOR_SELF, 2, 0x700001)
            Wait(8)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_omo2_2_stilt_guy_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_2_Script_802333A4 = {
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Call(SetPartFlags, ACTOR_SELF, 1, 0x800004)
    Call(SetPartFlags, ACTOR_SELF, 3, 0x20005)
    Call(SetPartFlags, ACTOR_SELF, 4, 0x20005)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B000C)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar1, 50)
    Else
        Add(LVar1, 20)
    EndIf
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Thread
        Wait(6)
        Call(PlaySoundAtPart, ACTOR_SELF, 2, 8295)
    EndThread
    Thread
        Call(SetAnimation, ACTOR_SELF, 2, 0x700008)
        Set(LVar0, 0)
        Loop(15)
            Add(LVar0, 6)
            Call(SetPartRotation, ACTOR_SELF, 2, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Call(SetPartFlags, ACTOR_SELF, 2, 0x20005)
    EndThread
    Call(PlaySoundAtPart, ACTOR_SELF, 2, 769)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
    Call(RandInt, 100, LVar1)
    IfLt(LVar1, 50)
        Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
        Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
    Else
        Call(SetAnimation, ACTOR_SELF, 1, 0x3B0010)
        Wait(10)
    EndIf
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_omo2_2_Script_TakeTurn_80235830))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_omo2_2_stilt_guy_EVS_ShyGuy_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_omo2_2_stilt_guy_EVS_ShyGuy_HandleEvent))
    Call(SetActorType, ACTOR_SELF, 31)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(GetActorSize, ACTOR_SELF, LVar0, LVar1)
    Call(SetActorSize, ACTOR_SELF, 24, LVar1)
    Call(b_area_omo2_2_stilt_guy_SetActorLevelToZero)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_2_Script_80234580 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0003)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetActorSounds, ACTOR_SELF, 2, 751, 0)
            Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
            Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0004)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0005)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(ResetAllActorSounds, ACTOR_SELF)
            Sub(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3B0004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0001)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Wait(3)
        Call(PlaySoundAtActor, ACTOR_SELF, 751)
    EndThread
    Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
    Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0004)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0005)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 2, 32)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 15)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0001)
    Wait(8)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    ExecWait(b_area_omo2_2_stilt_guy_EVS_ShyGuy_ReturnHome)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_2_Script_TakeTurn_80235830 = {
    Call(RandInt, 1, LVar0)
    IfEq(LVar0, 0)
        ExecWait(TTYD64_omo2_2_Script_80234580)
    Else
        ExecWait(TTYD64_omo2_2_Script_80234CA8)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_omo2_2_Script_80234CA8 = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 20)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 564)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0009)
    Wait(20)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0003)
    Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 80)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetActorSounds, ACTOR_SELF, 0, 8378, 948)
    Call(SetActorSounds, ACTOR_SELF, 4, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0004)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Sub(LVar0, 40)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0009)
            Thread
                Wait(12)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B000A)
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 10)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 24, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0005)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Sub(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 15)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3B0004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0001)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x3B0009)
    Thread
        Wait(9)
        Call(SetAnimation, ACTOR_SELF, 1, 0x3B000A)
    EndThread
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(JumpToGoal, ACTOR_SELF, 18, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 15)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 14, 0)
                Set(LVar3, 0)
                Loop(20)
                    Sub(LVar3, 30)
                    IfLt(LVar3, 0)
                        Add(LVar3, 360)
                    EndIf
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar3)
                    Wait(1)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            EndThread
            Call(GetBattleFlags, LVar0)
            IfFlag(LVar0, (-0x7FFFFFFF - 1))
                Goto(1)
            EndIf
            Call(GetOwnerTarget, LVar2, 0)
            Call(GetLastDamage, LVar2, LVar0)
            IfEq(LVar0, 0)
                Goto(1)
            EndIf
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 841)
            Call(PlaySoundAtActor, ACTOR_SELF, 1865)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0009)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0007)
            Wait(15)
            Goto(2)
            Label(1)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8420)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0010)
            Wait(10)
            Call(PlaySoundAtActor, ACTOR_SELF, 8387)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 50)
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0011)
            Else
                Call(SetAnimation, ACTOR_SELF, 1, 0x3B0013)
            EndIf
            Wait(25)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Label(2)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x3B0004)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x3B0001)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

void TTYD64_InstallBattles_omo2_2(void) {
    Mod_ReplaceActorBlueprint("TTYD64", &b_area_omo2_2_stilt_guy, &TTYD64_omo2_2_StiltGuy);
}
