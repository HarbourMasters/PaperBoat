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

API_CALLABLE(AddActorDecoration);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(CountTargets);
API_CALLABLE(CreateHomeTargetList);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyToGoal);
API_CALLABLE(FreezeBattleState);
API_CALLABLE(GetActorDefenseBoost);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetEnemyMaxHP);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetOriginalActorType);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HealActor);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetAnimationRate);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetPartAlpha);
API_CALLABLE(SetTargetActor);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(WaitForBuffDone);
API_CALLABLE(YieldTurn);
API_CALLABLE(b_area_jan2_putrid_piranha_UnkEffect6FFunc);
API_CALLABLE(b_area_jan2_white_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_jan2_white_magikoopa_GetActorDefense);
API_CALLABLE(b_area_jan2_white_magikoopa_GetBootsHammerLevel);
API_CALLABLE(b_area_jan2_white_magikoopa_ShrinkActor);
extern Stage b_area_jan2_jan_01;
extern s32 b_area_jan2_putrid_piranha_DefenseTable[];
extern EvtScript b_area_jan2_putrid_piranha_EVS_HandleEvent;
extern EvtScript b_area_jan2_putrid_piranha_EVS_Idle;
extern EvtScript b_area_jan2_putrid_piranha_EVS_ReturnHome;
extern s32 b_area_jan2_putrid_piranha_StatusTable[];
extern s32 b_area_jan2_white_magikoopa_DefenseTable_80223B20[];
extern EvtScript b_area_jan2_white_magikoopa_EVS_Flee;
extern EvtScript b_area_jan2_white_magikoopa_EVS_HandleEvent_Ground;
extern EvtScript b_area_jan2_white_magikoopa_EVS_Idle;
extern EvtScript TTYD64_jan2_white_magikoopa_EVS_Move_HealOne;
extern EvtScript TTYD64_jan2_putrid_piranha_EVS_Attack_Bite;
extern EvtScript TTYD64_jan2_white_magikoopa_EVS_Move_HealAll;
extern EvtScript TTYD64_jan2_white_magikoopa_EVS_Attack_WandStrike;
extern EvtScript TTYD64_jan2_white_magikoopa_EVS_Attack_MagicBlast;
extern EvtScript TTYD64_jan2_putrid_piranha_EVS_Attack_BadBreath;
extern EvtScript TTYD64_jan2_white_magikoopa_EVS_TakeTurn;
extern EvtScript TTYD64_jan2_putrid_piranha_EVS_TakeTurn;
extern EvtScript TTYD64_jan2_white_magikoopa_EVS_Init_Ground;
extern EvtScript TTYD64_jan2_putrid_piranha_EVS_Init;
extern ActorBlueprint TTYD64_jan2_putrid_piranha;
extern ActorBlueprint TTYD64_jan2_white_magikoopa;
extern s32 TTYD64_jan2_white_magikoopa_StatusTable_Ground[];
extern FormationRow TTYD64_jan2_Formation_03[];
extern Battle TTYD64_jan2_Formations[];
extern FormationRow TTYD64_jan2_Formation_02[];
extern s32 TTYD64_jan2_putrid_piranha_DefaultAnims[];
extern s32 TTYD64_jan2_white_magikoopa_IdleAnimations_80223D70[];
extern FormationRow TTYD64_jan2_Formation_01[];
extern ActorPartBlueprint TTYD64_jan2_putrid_piranha_ActorParts[];
extern ActorPartBlueprint TTYD64_jan2_white_magikoopa_GroundParts[];
extern FormationRow TTYD64_jan2_Formation_00[];

// clang-format off
EvtScript TTYD64_jan2_white_magikoopa_EVS_Move_HealOne = {
    Set(LVar8, 0)
    Set(LVar9, 9999)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetActorHP, LVar0, LVar2)
    Call(b_area_jan2_white_magikoopa_GetBootsHammerLevel, LVar3, LVar4)
    IfGt(LVar3, LVar4)
        Set(LVar3, LVar4)
    EndIf
    Call(b_area_jan2_white_magikoopa_GetActorDefense, LVar0, LVar1, LVar5)
    Call(GetActorDefenseBoost, LVar0, LVar6)
    Add(LVar5, LVar6)
    Sub(LVar3, LVar5)
    Sub(LVar2, LVar3)
    Call(b_area_jan2_white_magikoopa_CheckMagikoopaCastTarget, LVar0, LVarA)
    IfEq(LVarA, 0)
        Call(GetEnemyMaxHP, LVar0, LVarA)
        Call(GetActorHP, LVar0, LVarB)
        IfNe(LVarA, LVarB)
            IfLt(LVar2, LVar9)
                Set(LVar8, LVar0)
                Set(LVar9, LVar2)
            Else
                IfEq(LVar2, LVar9)
                    IfLt(LVar0, LVar8)
                        Set(LVar8, LVar0)
                        Set(LVar9, LVar2)
                    EndIf
                EndIf
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfNe(LVar8, 0)
        Goto(100)
    EndIf
    Set(LVar8, 0)
    Set(LVar9, 9999)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(1)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetActorHP, LVar0, LVar2)
    Call(b_area_jan2_white_magikoopa_GetBootsHammerLevel, LVar3, LVar4)
    IfGt(LVar3, LVar4)
        Set(LVar3, LVar4)
    EndIf
    Call(b_area_jan2_white_magikoopa_GetActorDefense, LVar0, LVar1, LVar5)
    Call(GetActorDefenseBoost, LVar0, LVar6)
    Add(LVar5, LVar6)
    Sub(LVar3, LVar5)
    Sub(LVar2, LVar4)
    Set(LFlag0, 0)
    Call(GetOriginalActorType, LVar0, LVarA)
    IfEq(LVarA, 71)
        Call(GetActorVar, LVar0, 8, LVarA)
        IfEq(LVarA, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetOwnerID, LVarA)
    IfNe(LVarA, LVar0)
        IfEq(LFlag0, 0)
            Call(GetEnemyMaxHP, LVar0, LVarA)
            Call(GetActorHP, LVar0, LVarB)
            IfNe(LVarA, LVarB)
                IfLt(LVar2, LVar9)
                    Set(LVar8, LVar0)
                    Set(LVar9, LVar2)
                Else
                    IfEq(LVar2, LVar9)
                        IfLt(LVar0, LVar8)
                            Set(LVar8, LVar0)
                            Set(LVar9, LVar2)
                        EndIf
                    EndIf
                EndIf
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(1)
    EndIf
    IfNe(LVar8, 0)
        Goto(100)
    EndIf
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(2)
    Call(GetOwnerTarget, LVar0, LVar1)
    Set(LFlag0, 0)
    Call(GetOriginalActorType, LVar0, LVarA)
    IfEq(LVarA, 71)
        Call(GetActorVar, LVar0, 8, LVarA)
        IfEq(LVarA, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetOwnerID, LVarA)
    IfNe(LVarA, LVar0)
        IfEq(LFlag0, 0)
            Call(GetEnemyMaxHP, LVar0, LVarA)
            Call(GetActorHP, LVar0, LVarB)
            IfNe(LVarA, LVarB)
                Set(LVar8, LVar0)
                Goto(100)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(2)
    EndIf
    Call(GetEnemyMaxHP, ACTOR_SELF, LVarA)
    Call(GetActorHP, ACTOR_SELF, LVarB)
    IfNe(LVarA, LVarB)
        Set(LVar8, -127)
        Goto(100)
    EndIf
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(3)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOwnerID, LVarA)
    IfNe(LVarA, LVar0)
        Call(GetActorFlags, ACTOR_SELF, LVar0)
        IfFlag(LVar0, 512)
            ExecWait(TTYD64_jan2_white_magikoopa_EVS_Attack_MagicBlast)
        Else
            ExecWait(TTYD64_jan2_white_magikoopa_EVS_Attack_WandStrike)
        EndIf
        Return
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(3)
    EndIf
    ExecWait(b_area_jan2_white_magikoopa_EVS_Flee)
    Return
    Label(100)
    Call(RandInt, 1000, LVar0)
    IfGt(LVar0, 750)
        Call(GetActorFlags, ACTOR_SELF, LVar0)
        IfFlag(LVar0, 512)
            ExecWait(TTYD64_jan2_white_magikoopa_EVS_Attack_MagicBlast)
        Else
            ExecWait(TTYD64_jan2_white_magikoopa_EVS_Attack_WandStrike)
        EndIf
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560302)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570302)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x560301)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570301)
    EndIf
    Wait(5)
    Thread
        Wait(5)
        Call(PlaySoundAtActor, LVar8, 8301)
        Call(PlaySoundAtActor, LVar8, 532)
        Wait(30)
        Call(PlaySoundAtActor, LVar8, 604)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(HealActor, LVar8, 8, 0)
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
EvtScript TTYD64_jan2_putrid_piranha_EVS_Attack_Bite = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x360018)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x360017)
        Wait(8)
    Else
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x360003)
        Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
        Call(SetAnimation, ACTOR_SELF, 1, 0x360003)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x360001)
    EndIf
    Thread
        Wait(8)
        Call(PlaySoundAtActor, ACTOR_SELF, 8414)
    EndThread
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x360005)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x360006)
            Wait(6)
            Call(SetAnimation, ACTOR_SELF, 1, 0x360007)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(14)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(YieldTurn)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
                Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
                Call(PlaySoundAtActor, ACTOR_SELF, 802)
                Call(SetAnimation, ACTOR_SELF, 1, 0x360018)
                Wait(10)
                Call(SetGoalToHome, ACTOR_SELF)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(PlaySoundAtActor, ACTOR_SELF, 801)
                Call(SetAnimation, ACTOR_SELF, 1, 0x360017)
                Wait(10)
                Call(SetActorFlagBits, ACTOR_SELF, 4, 0)
            Else
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
                Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
                Call(SetActorYaw, ACTOR_SELF, 180)
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                ExecWait(b_area_jan2_putrid_piranha_EVS_ReturnHome)
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x360005)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x360006)
    Wait(1)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 3, 32)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x360007)
            Wait(20)
            Call(YieldTurn)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
                Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
                Call(PlaySoundAtActor, ACTOR_SELF, 802)
                Call(SetAnimation, ACTOR_SELF, 1, 0x360018)
                Wait(10)
                Call(SetGoalToHome, ACTOR_SELF)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(PlaySoundAtActor, ACTOR_SELF, 801)
                Call(SetAnimation, ACTOR_SELF, 1, 0x360017)
                Wait(10)
                Call(SetActorFlagBits, ACTOR_SELF, 4, 0)
            Else
                Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
                ExecWait(b_area_jan2_putrid_piranha_EVS_ReturnHome)
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
EvtScript TTYD64_jan2_white_magikoopa_EVS_Move_HealAll = {
    Call(RandInt, 1000, LVar0)
    IfGt(LVar0, 750)
        Call(GetActorFlags, ACTOR_SELF, LVar0)
        IfFlag(LVar0, 512)
            ExecWait(TTYD64_jan2_white_magikoopa_EVS_Attack_MagicBlast)
        Else
            ExecWait(TTYD64_jan2_white_magikoopa_EVS_Attack_WandStrike)
        EndIf
        Return
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560302)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570302)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x560301)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570301)
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
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan2_white_magikoopa_EVS_Attack_WandStrike = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 731)
    Thread
        Call(SetAnimation, ACTOR_SELF, 1, 0x560302)
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x560303)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x560301)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x560301)
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
EvtScript TTYD64_jan2_white_magikoopa_EVS_Attack_MagicBlast = {
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
    Call(SetAnimation, ACTOR_SELF, 2, 0x570302)
    Wait(30)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8405)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570303)
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
            Call(b_area_jan2_white_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 25)
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
    Call(SetAnimation, ACTOR_SELF, 2, 0x570303)
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
    Call(b_area_jan2_white_magikoopa_ShrinkActor, LVar0, LVar1, LVar5, LVar3, LVar4, LVar5, 20)
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
EvtScript TTYD64_jan2_putrid_piranha_EVS_Attack_BadBreath = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x360003)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x360003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 16)
    Else
        Add(LVar0, 40)
    EndIf
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x360001)
    Call(SetAnimation, ACTOR_SELF, 1, 0x360008)
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
    Call(b_area_jan2_putrid_piranha_UnkEffect6FFunc, LVar2, LVar0, LVar1, LVar2, LVar3, 30, 120, 0, 120)
    Wait(1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x360009)
    Wait(5)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x36000A)
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
            ExecWait(b_area_jan2_putrid_piranha_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0xFFFF, -0x7FFDFC9C, 2, 32)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x36000A)
            Wait(20)
            Call(YieldTurn)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_jan2_putrid_piranha_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_jan2_white_magikoopa_EVS_TakeTurn = {
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_jan2_white_magikoopa_EVS_Flee)
        Return
    EndIf
    Set(LVarA, 0)
    Set(LVarB, 0)
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
        Call(GetActorHP, LVar0, LVar2)
        Call(GetEnemyMaxHP, LVar0, LVar3)
        IfNe(LVar2, LVar3)
            Add(LVarA, 1)
        EndIf
        Add(LVarB, 1)
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Mul(LVarA, 100)
    Div(LVarA, LVarB)
    Switch(LVarA)
        CaseGe(60)
            ExecWait(TTYD64_jan2_white_magikoopa_EVS_Move_HealAll)
        CaseEq(0)
            Call(GetActorFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 512)
                ExecWait(TTYD64_jan2_white_magikoopa_EVS_Attack_MagicBlast)
            Else
                ExecWait(TTYD64_jan2_white_magikoopa_EVS_Attack_WandStrike)
            EndIf
        CaseDefault
            ExecWait(TTYD64_jan2_white_magikoopa_EVS_Move_HealOne)
    EndSwitch
    Return
    End
};
// clang-format on

s32 TTYD64_jan2_white_magikoopa_StatusTable_Ground[] = {
    1,  0, 2,  0, 6,  50, 9,  50, 7,  50, 4,  75, 3,  0, 11, 50, 5,  75, 10, 80, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, -1, 0,
};

// clang-format off
EvtScript TTYD64_jan2_putrid_piranha_EVS_TakeTurn = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_jan2_putrid_piranha_EVS_Attack_Bite)
        Return
    EndIf
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 70)
        ExecWait(TTYD64_jan2_putrid_piranha_EVS_Attack_BadBreath)
    Else
        ExecWait(TTYD64_jan2_putrid_piranha_EVS_Attack_Bite)
    EndIf
    Return
    End
};
// clang-format on

FormationRow TTYD64_jan2_Formation_03[] = {
    { .actor = &TTYD64_jan2_putrid_piranha,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_jan2_putrid_piranha,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_jan2_putrid_piranha,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_jan2_white_magikoopa,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

// clang-format off
EvtScript TTYD64_jan2_white_magikoopa_EVS_Init_Ground = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_jan2_white_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_jan2_white_magikoopa_EVS_TakeTurn))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_jan2_white_magikoopa_EVS_HandleEvent_Ground))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

Battle TTYD64_jan2_Formations[] = {
    { .name = "\335\244\272\363\321\303\257\363",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_jan2_Formation_00,
      .stage = &b_area_jan2_jan_01,
      .onBattleStart = NULL },
    { .name = "\335\244\272\363\321\303\257\363x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_jan2_Formation_01,
      .stage = &b_area_jan2_jan_01,
      .onBattleStart = NULL },
    { .name = "\335\244\272\363\321\303\257\363x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_jan2_Formation_02,
      .stage = &b_area_jan2_jan_01,
      .onBattleStart = NULL },
    { .name = "\335\244\272\363\321\303\257\363x\023,\333\357\244\310\253\341\303\257",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_jan2_Formation_03,
      .stage = &b_area_jan2_jan_01,
      .onBattleStart = NULL },
    {},
};

FormationRow TTYD64_jan2_Formation_02[] = {
    { .actor = &TTYD64_jan2_putrid_piranha,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_jan2_putrid_piranha,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_jan2_putrid_piranha,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
};

s32 TTYD64_jan2_putrid_piranha_DefaultAnims[] = {
    1,  0x360001, 7, 0x360000, 6, 0x360000, 9, 0x360001, 8, 0x360000,
    11, 0x360000, 5, 0x360000, 5, 0x360000, 4, 0x36000F, 0,
};

s32 TTYD64_jan2_white_magikoopa_IdleAnimations_80223D70[] = {
    1,  0x560301, 7, 0x560300, 6, 0x560308, 9, 0x560301, 8, 0x560300,
    11, 0x560301, 5, 0x560300, 4, 0x560307, 3, 0x560307, 0,
};

// clang-format off
EvtScript TTYD64_jan2_putrid_piranha_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_jan2_putrid_piranha_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_jan2_putrid_piranha_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_jan2_putrid_piranha_EVS_HandleEvent))
    Return
    End
};
// clang-format on

FormationRow TTYD64_jan2_Formation_01[] = {
    { .actor = &TTYD64_jan2_putrid_piranha,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
    { .actor = &TTYD64_jan2_putrid_piranha,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
};

ActorBlueprint TTYD64_jan2_putrid_piranha = {
    .flags = 0x0,
    .maxHP = 12,
    .type = 0x2D,
    .level = 17,
    .partCount = 1,
    .partsData = TTYD64_jan2_putrid_piranha_ActorParts,
    .initScript = &TTYD64_jan2_putrid_piranha_EVS_Init,
    .statusTable = b_area_jan2_putrid_piranha_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 20,
    .hurricaneChance = 20,
    .spookChance = 30,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 1,
    .size = { 60, 52 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -22, 32 },
    .statusTextOffset = { 1, 44 },
};

ActorBlueprint TTYD64_jan2_white_magikoopa = {
    .flags = 0x0,
    .maxHP = 11,
    .type = 0x59,
    .level = 21,
    .partCount = 1,
    .partsData = TTYD64_jan2_white_magikoopa_GroundParts,
    .initScript = &TTYD64_jan2_white_magikoopa_EVS_Init_Ground,
    .statusTable = TTYD64_jan2_white_magikoopa_StatusTable_Ground,
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

ActorPartBlueprint TTYD64_jan2_putrid_piranha_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -15, 50 },
        .opacity = 255,
        .idleAnimations = TTYD64_jan2_putrid_piranha_DefaultAnims,
        .defenseTable = b_area_jan2_putrid_piranha_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 3, -14 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_jan2_white_magikoopa_GroundParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_jan2_white_magikoopa_IdleAnimations_80223D70,
        .defenseTable = b_area_jan2_white_magikoopa_DefenseTable_80223B20,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_jan2_Formation_00[] = {
    { .actor = &TTYD64_jan2_putrid_piranha,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PUTRIDPIRANHA },
};

void TTYD64_InstallBattles_jan2(void) {
    Mod_SetBattleList("TTYD64", 21, TTYD64_jan2_Formations);
}
