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
#include "port/romhack/specific/TTYD64/battles_a/battles_a.h"

API_CALLABLE(ActorExists);
API_CALLABLE(ActorSpeak);
API_CALLABLE(AddActorDecoration);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BattleCamTargetActorPart);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FallPartTo);
API_CALLABLE(FlyPartTo);
API_CALLABLE(ForceHomePos);
API_CALLABLE(FreezeBattleState);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartOffset);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToHome);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartSize);
API_CALLABLE(SetTargetActor);
API_CALLABLE(ShakeCam);
API_CALLABLE(SpawnFallingRock);
API_CALLABLE(StartRumble);
API_CALLABLE(StopSound);
API_CALLABLE(SummonEnemy);
API_CALLABLE(TranslateModel);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
API_CALLABLE(b_area_isk_part_2_chain_chomp_ChompChainInit);
extern Vec3i b_area_isk_part_2_BossPos;
extern ActorPartBlueprint b_area_isk_part_2_chain_chomp_ActorParts[];
extern EvtScript b_area_isk_part_2_chain_chomp_EVS_Chomp_HopHome;
extern EvtScript b_area_isk_part_2_chain_chomp_EVS_HandleEvent;
extern EvtScript b_area_isk_part_2_chain_chomp_EVS_Idle;
extern EvtScript b_area_isk_part_2_chain_chomp_EVS_UpdateChain;
extern s32 b_area_isk_part_2_chain_chomp_StatusTable[];
extern Stage b_area_isk_part_2_isk_01;
extern ActorPartBlueprint b_area_isk_part_2_tutankoopa_ActorParts[];
extern EvtScript b_area_isk_part_2_tutankoopa_EVS_GetBackUp;
extern EvtScript b_area_isk_part_2_tutankoopa_EVS_HandleEvent;
extern EvtScript b_area_isk_part_2_tutankoopa_EVS_HandlePhase;
extern EvtScript b_area_isk_part_2_tutankoopa_EVS_Idle;
extern EvtScript b_area_isk_part_2_tutankoopa_EVS_LevitateToHomePos;
extern EvtScript b_area_isk_part_2_tutankoopa_EVS_SummonedChompHop;
extern s32 b_area_isk_part_2_tutankoopa_StatusTable[];
extern Vec3i b_area_isk_part_2_tutankoopa_SummonedChompPos;
extern ActorBlueprint TTYD64_isk_part_2_chain_chomp;
extern EvtScript TTYD64_isk_part_2_chain_chomp_EVS_Init;
extern EvtScript TTYD64_isk_part_2_chain_chomp_EVS_TakeTurn;
extern ActorBlueprint TTYD64_isk_part_2_tutankoopa;
extern EvtScript TTYD64_isk_part_2_tutankoopa_EVS_Init;
extern EvtScript TTYD64_isk_part_2_tutankoopa_EVS_TakeTurn;
extern EvtScript TTYD64_isk_part_2_tutankoopa_EVS_DropDebris_Players;
extern EvtScript TTYD64_isk_part_2_tutankoopa_EVS_Attack_DropDebris;
extern EvtScript TTYD64_isk_part_2_tutankoopa_EVS_Move_SummonChomp;
extern EvtScript TTYD64_isk_part_2_tutankoopa_EVS_Attack_ThrowShell;
extern EvtScript TTYD64_isk_part_2_tutankoopa_EVS_DropDebris_Self;
extern FormationRow TTYD64_isk_part_2_tutankoopa_SummonedChomp[];
extern FormationRow TTYD64_isk_part_2_Formation_00[];
extern Battle TTYD64_isk_part_2_Formations[];

ActorBlueprint TTYD64_isk_part_2_chain_chomp = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0xA2,
    .level = 14,
    .partCount = 10,
    .partsData = b_area_isk_part_2_chain_chomp_ActorParts,
    .initScript = &TTYD64_isk_part_2_chain_chomp_EVS_Init,
    .statusTable = b_area_isk_part_2_chain_chomp_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 95,
    .coinReward = 0,
    .size = { 56, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

// clang-format off
EvtScript TTYD64_isk_part_2_chain_chomp_EVS_Init = {
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_isk_part_2_chain_chomp_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_isk_part_2_chain_chomp_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_isk_part_2_chain_chomp_EVS_HandleEvent))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Set(LVar0, 3)
    Loop(8)
        Call(SetPartSize, ACTOR_SELF, LVar0, 16, 16)
        Add(LVar0, 1)
    EndLoop
    Call(b_area_isk_part_2_chain_chomp_ChompChainInit)
    Exec(b_area_isk_part_2_chain_chomp_EVS_UpdateChain)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_2_chain_chomp_EVS_TakeTurn = {
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Add(LVar0, 45)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8290)
    Thread
        Call(GetStatusFlags, ACTOR_SELF, LVar0)
        IfNotFlag(LVar0, 0x80000)
            Call(ShakeCam, 1, 0, 1, Float(0.5))
        EndIf
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x690005)
    Wait(15)
    Call(PlaySoundAtActor, ACTOR_SELF, 271)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySound, 271)
            Call(SetAnimation, ACTOR_SELF, 1, 0x690001)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8290)
            Thread
                Call(GetStatusFlags, ACTOR_SELF, LVar0)
                IfNotFlag(LVar0, 0x80000)
                    Call(ShakeCam, 1, 0, 1, Float(0.5))
                EndIf
            EndThread
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 25)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8290)
            Thread
                Call(GetStatusFlags, ACTOR_SELF, LVar0)
                IfNotFlag(LVar0, 0x80000)
                    Call(ShakeCam, 1, 0, 1, Float(0.5))
                EndIf
            EndThread
            Sub(LVar0, 15)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8290)
            Thread
                Call(GetStatusFlags, ACTOR_SELF, LVar0)
                IfNotFlag(LVar0, 0x80000)
                    Call(ShakeCam, 1, 0, 1, Float(0.5))
                EndIf
            EndThread
            Call(SetAnimation, ACTOR_SELF, 1, 0x690004)
            Wait(20)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x690001)
            ExecWait(b_area_isk_part_2_chain_chomp_EVS_Chomp_HopHome)
            Call(SetAnimation, ACTOR_SELF, 1, 0x690001)
            Call(HPBarToHome, ACTOR_SELF)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(SetActorVar, ACTOR_SELF, 8, 0)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x690001)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Add(LVar0, 4)
    Else
        Add(LVar0, 10)
    EndIf
    Set(LVar1, 27)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.2001953125))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Wait(2)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarF, 0, 0, 0, 3, 32)
    Switch(LVarF)
        CaseDefault
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x690004)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8290)
            Thread
                Call(GetStatusFlags, ACTOR_SELF, LVar0)
                IfNotFlag(LVar0, 0x80000)
                    Call(ShakeCam, 1, 0, 1, Float(0.5))
                EndIf
            EndThread
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8290)
            Thread
                Call(GetStatusFlags, ACTOR_SELF, LVar0)
                IfNotFlag(LVar0, 0x80000)
                    Call(ShakeCam, 1, 0, 1, Float(0.5))
                EndIf
            EndThread
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8290)
            Thread
                Call(GetStatusFlags, ACTOR_SELF, LVar0)
                IfNotFlag(LVar0, 0x80000)
                    Call(ShakeCam, 1, 0, 1, Float(0.5))
                EndIf
            EndThread
            Sub(LVar0, 10)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8290)
            Thread
                Call(GetStatusFlags, ACTOR_SELF, LVar0)
                IfNotFlag(LVar0, 0x80000)
                    Call(ShakeCam, 1, 0, 1, Float(0.5))
                EndIf
            EndThread
            Call(SetAnimation, ACTOR_SELF, 1, 0x690001)
            Wait(8)
            Call(UseBattleCamPreset, 2)
            IfEq(LVarF, 10)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetPartPos, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
                Return
            EndIf
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x690001)
            ExecWait(b_area_isk_part_2_chain_chomp_EVS_Chomp_HopHome)
            Call(SetAnimation, ACTOR_SELF, 1, 0x690001)
    EndSwitch
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(HPBarToHome, ACTOR_SELF)
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

ActorBlueprint TTYD64_isk_part_2_tutankoopa = {
    .flags = 0x0,
    .maxHP = 30,
    .type = 0xA1,
    .level = 55,
    .partCount = 8,
    .partsData = b_area_isk_part_2_tutankoopa_ActorParts,
    .initScript = &TTYD64_isk_part_2_tutankoopa_EVS_Init,
    .statusTable = b_area_isk_part_2_tutankoopa_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 70,
    .coinReward = 0,
    .size = { 56, 45 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 35 },
    .statusTextOffset = { 10, 35 },
};

// clang-format off
EvtScript TTYD64_isk_part_2_tutankoopa_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_isk_part_2_tutankoopa_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_isk_part_2_tutankoopa_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_isk_part_2_tutankoopa_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_isk_part_2_tutankoopa_EVS_HandlePhase))
    Call(HPBarToHome, ACTOR_SELF)
    Call(ForceHomePos, ACTOR_SELF, 97, 70, 15)
    Call(SetPartPos, ACTOR_SELF, 3, 70, 70, 3)
    Call(SetPartPos, ACTOR_SELF, 4, 80, 70, -7)
    Call(SetPartPos, ACTOR_SELF, 5, 60, 70, -7)
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 3)
    Call(SetActorVar, ACTOR_SELF, 6, 0)
    Call(SetActorVar, ACTOR_SELF, 7, 0)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 0)
    Call(SetActorVar, ACTOR_SELF, 12, 0)
    Call(SetActorVar, ACTOR_SELF, 13, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_2_tutankoopa_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Label(0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 0)
        Call(ActorExists, 513, LVar0)
        IfEq(LVar0, 0)
            Call(GetActorVar, ACTOR_SELF, 12, LVar0)
            IfEq(LVar0, 0)
                ExecWait(TTYD64_isk_part_2_tutankoopa_EVS_Move_SummonChomp)
                Call(EnableIdleScript, ACTOR_SELF, 1)
                Call(UseIdleAnimation, ACTOR_SELF, 1)
                Return
            Else
                Sub(LVar0, 1)
                Call(SetActorVar, ACTOR_SELF, 12, LVar0)
            EndIf
        EndIf
        Call(GetStatusFlags, ACTOR_SELF, LVar0)
        IfFlag(LVar0, 0x80000)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
        EndIf
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Switch(LVar0)
            CaseEq(0)
                Call(GetActorVar, ACTOR_SELF, 2, LVar0)
                IfEq(LVar0, 0)
                    ExecWait(TTYD64_isk_part_2_tutankoopa_EVS_Attack_DropDebris)
                    Call(SetActorVar, ACTOR_SELF, 0, 1)
                Else
                    Call(GetStatusFlags, ACTOR_SELF, LVar0)
                    IfNotFlag(LVar0, 0x80000)
                        ExecWait(TTYD64_isk_part_2_tutankoopa_EVS_Attack_ThrowShell)
                        Call(SetActorVar, ACTOR_SELF, 0, 1)
                    Else
                        ExecWait(TTYD64_isk_part_2_tutankoopa_EVS_Attack_DropDebris)
                        Call(SetActorVar, ACTOR_SELF, 0, 0)
                    EndIf
                EndIf
            CaseDefault
                Call(SetActorVar, ACTOR_SELF, 0, 0)
                ExecWait(TTYD64_isk_part_2_tutankoopa_EVS_Attack_DropDebris)
        EndSwitch
        Call(EnableIdleScript, ACTOR_SELF, 1)
        Call(UseIdleAnimation, ACTOR_SELF, 1)
        Return
    Else
        Call(SetActorVar, ACTOR_SELF, 7, 0)
        Call(SetActorVar, ACTOR_SELF, 1, 0)
        ExecWait(b_area_isk_part_2_tutankoopa_EVS_GetBackUp)
        ExecWait(b_area_isk_part_2_tutankoopa_EVS_LevitateToHomePos)
        Goto(0)
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_2_tutankoopa_EVS_DropDebris_Players = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Thread
                Loop(6)
                    Call(RandInt, 120, LVar0)
                    Sub(LVar0, 150)
                    Call(RandInt, 90, LVar1)
                    Sub(LVar0, 40)
                    Call(PlaySound, 8427)
                    Call(SpawnFallingRock, LVar0, 0, LVar1)
                    Call(RandInt, 5, LVar0)
                    Add(LVar0, 5)
                    Wait(LVar0)
                EndLoop
            EndThread
            Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVarB, 0, 0, 1, 16)
            Switch(LVarB)
                CaseEq(6)
                    Return
                CaseDefault
                    Call(FreezeBattleState, 1)
                    Thread
                        Call(PlaySound, 8427)
                        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
                        Call(SetGoalToTarget, ACTOR_SELF)
                        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                        Sub(LVar0, 5)
                        Set(LVar1, 0)
                        Set(LVar3, 170)
                        Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar3, LVar2)
                        Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
                        Call(SetAnimation, ACTOR_SELF, 6, 0x680016)
                        Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(8.0))
                        Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.2998046875))
                        Call(FallPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 20)
                        Call(SetAnimation, ACTOR_SELF, 6, 0x680017)
                        IfEq(LVarA, 5)
                            Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                        EndIf
                    EndThread
                    Wait(25)
                    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(GetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Sub(LVar4, 5)
                    Add(LVar5, 5)
                    Set(LVar7, 170)
                    Call(SetPartPos, ACTOR_SELF, 7, LVar4, LVar7, LVar6)
                    Call(SetPartFlagBits, ACTOR_SELF, 7, 1, 0)
                    Call(SetAnimation, ACTOR_SELF, 7, 0x680016)
                    Call(PlaySound, 8427)
                    Call(SetPartMoveSpeed, ACTOR_SELF, 7, Float(8.0))
                    Call(SetPartJumpGravity, ACTOR_SELF, 7, Float(0.2998046875))
                    Call(FallPartTo, ACTOR_SELF, 7, LVar4, LVar5, LVar6, 20)
                    Call(SetAnimation, ACTOR_SELF, 6, 0x680017)
                    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
                    Call(SetGoalToTarget, ACTOR_SELF)
                    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 2, 32)
                    Wait(20)
                    Call(SetPartFlagBits, ACTOR_SELF, 7, 1, 1)
                    Call(FreezeBattleState, 0)
                    Return
            EndSwitch
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Loop(6)
            Call(RandInt, 120, LVar0)
            Sub(LVar0, 150)
            Call(RandInt, 90, LVar1)
            Sub(LVar0, 40)
            Call(PlaySound, 8427)
            Call(SpawnFallingRock, LVar0, 0, LVar1)
            Call(RandInt, 5, LVar0)
            Add(LVar0, 5)
            Wait(LVar0)
        EndLoop
    EndThread
    Call(FreezeBattleState, 1)
    Thread
        Wait(25)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
        Sub(LVar4, 5)
        Add(LVar5, 5)
        Set(LVar7, 170)
        Call(SetPartPos, ACTOR_SELF, 7, LVar4, LVar7, LVar6)
        Call(SetPartFlagBits, ACTOR_SELF, 7, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 7, 0x680016)
        Call(PlaySound, 8427)
        Call(SetPartMoveSpeed, ACTOR_SELF, 7, Float(8.0))
        Call(SetPartJumpGravity, ACTOR_SELF, 7, Float(0.2998046875))
        Call(FallPartTo, ACTOR_SELF, 7, LVar4, LVar5, LVar6, 20)
        Call(SetAnimation, ACTOR_SELF, 6, 0x680017)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(EnemyTestTarget, ACTOR_SELF, LVarB, 0, 0, 1, 16)
        Switch(LVarB)
            CaseOrEq(6)
            CaseOrEq(5)
                IfEq(LVarB, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
            EndCaseGroup
            CaseDefault
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 2, 32)
        EndSwitch
        Wait(20)
        Call(SetPartFlagBits, ACTOR_SELF, 7, 1, 1)
        Call(FreezeBattleState, 0)
    EndThread
    Call(PlaySound, 8427)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Add(LVar1, 5)
    Set(LVar3, 170)
    Call(SetPartPos, ACTOR_SELF, 6, LVar0, LVar3, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 6, 0x680016)
    Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(8.0))
    Call(SetPartJumpGravity, ACTOR_SELF, 6, Float(0.2998046875))
    Call(FallPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 20)
    Call(SetAnimation, ACTOR_SELF, 6, 0x680017)
    Wait(2)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000000, 0, 0, 2, 32)
    Wait(19)
    Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
    IfEq(LVar0, 10)
        Return
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_2_tutankoopa_EVS_Attack_DropDebris = {
    Call(UseBattleCamPreset, 15)
    Call(SetBattleCamDist, 350)
    Call(SetBattleCamOffsetY, 0)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 40)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    IfEq(LVar0, 0)
        Call(UseBattleCamPreset, 13)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 20)
        Wait(20)
        Call(ActorSpeak, 0xD00E5, ACTOR_SELF, 1, 0x680003, 0x680003)
        Call(UseBattleCamPreset, 2)
        Call(UseBattleCamPreset, 2)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8417)
    Call(SetAnimation, ACTOR_SELF, 1, 0x680003)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(PlayEffect_impl, 113, 0, LVar0, LVar1, LVar2, Float(1.0), 45, 0, 0, 0, 0, 0, 0, 0)
    Wait(30)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 70)
    Call(PlaySound, 8423)
    Call(PlayEffect_impl, 77, 0, 0, 60, 0, Float(0.2001953125), 0, Float(1.400390625), 255, Float(0.099609375), 150, 0, 0, 0)
    Wait(15)
    Call(GetStatusFlags, 0, LVar0)
    IfNotFlag(LVar0, 0x435D000)
        Call(UseIdleAnimation, 0, 0)
        Call(SetAnimation, 0, 0, 0x1002B)
        Wait(49)
        Call(PlaySound, 8425)
        Wait(5)
        Call(SetAnimation, ACTOR_SELF, 1, 0x680005)
        Wait(8)
        Call(TTYD64_GetPartnerHP_API, LVar0)
        IfGt(LVar0, 0)
            Call(UseIdleAnimation, 256, 0)
            Set(LVar0, 6)
            Exec(TTYD64_SetPartnerAnimation_Battle)
        EndIf
        Call(SetAnimation, 0, 0, 0x10014)
        Wait(5)
        Call(StartRumble, 10)
        Call(PlaySound, 8426)
        Call(ShakeCam, 1, 0, 5, Float(4.0))
        Wait(20)
        Call(TTYD64_GetPartnerHP_API, LVar0)
        IfGt(LVar0, 0)
            Set(LVar0, 0)
            Exec(TTYD64_SetPartnerAnimation_Battle)
        EndIf
        Call(SetAnimation, 0, 0, 0x10028)
        Call(GetActorPos, 0, LVar0, LVar1, LVar2)
        Add(LVar1, 20)
        Call(PlayEffect_impl, 16, 2, 0, LVar0, LVar1, LVar2, 20, 315, 30, 0, 0, 0, 0, 0)
        Call(PlaySound, 8424)
        Call(TTYD64_GetPartnerHP_API, LVar0)
        IfGt(LVar0, 0)
            Call(GetActorPos, 256, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(PlayEffect_impl, 16, 2, 0, LVar0, LVar1, LVar2, 20, 315, 30, 0, 0, 0, 0, 0)
        EndIf
    Else
        Wait(50)
        Call(PlaySound, 8425)
        Wait(18)
        Call(StartRumble, 10)
        Call(PlaySound, 8426)
        Wait(20)
        Call(PlaySound, 8424)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetActorVar, ACTOR_SELF, 6, 1)
            ExecWait(TTYD64_isk_part_2_tutankoopa_EVS_DropDebris_Players)
        CaseEq(1)
            Call(GetActorHP, ACTOR_SELF, LVar0)
            Call(SetActorVar, ACTOR_SELF, 6, 2)
            IfGt(LVar0, 2)
                ExecWait(TTYD64_isk_part_2_tutankoopa_EVS_DropDebris_Self)
            Else
                ExecWait(TTYD64_isk_part_2_tutankoopa_EVS_DropDebris_Players)
            EndIf
        CaseDefault
            Call(RandInt, 2, LVar0)
            IfEq(LVar0, 0)
                Call(GetActorHP, ACTOR_SELF, LVar0)
                IfGt(LVar0, 2)
                    ExecWait(TTYD64_isk_part_2_tutankoopa_EVS_DropDebris_Self)
                Else
                    ExecWait(TTYD64_isk_part_2_tutankoopa_EVS_DropDebris_Players)
                EndIf
            Else
                ExecWait(TTYD64_isk_part_2_tutankoopa_EVS_DropDebris_Players)
            EndIf
    EndSwitch
    Return
    End
};
// clang-format on

FormationRow TTYD64_isk_part_2_tutankoopa_SummonedChomp[] = {
    { .actor = &TTYD64_isk_part_2_chain_chomp,
      .home = { .vec = &b_area_isk_part_2_tutankoopa_SummonedChompPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

// clang-format off
EvtScript TTYD64_isk_part_2_tutankoopa_EVS_Move_SummonChomp = {
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    Call(GetActorVar, ACTOR_SELF, 3, LVar0)
    IfEq(LVar0, 0)
        Call(UseBattleCamPreset, 13)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 20)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x680003)
        Call(ActorSpeak, 0xD00E6, ACTOR_SELF, 1, 0x680003, 0x680003)
    Else
        Call(UseBattleCamPreset, 13)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 20)
        Wait(20)
        Call(SetAnimation, ACTOR_SELF, 1, 0x680003)
        Call(ActorSpeak, 0xD00E7, ACTOR_SELF, 1, 0x680003, 0x680003)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x680001)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 0)
        Call(UseBattleCamPreset, 13)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(SetBattleCamDist, 225)
        Call(SetBattleCamOffsetY, -30)
        Call(MoveBattleCamOver, 40)
    Else
        Call(UseBattleCamPreset, 13)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(SetBattleCamDist, 200)
        Call(SetBattleCamOffsetY, 35)
        Call(MoveBattleCamOver, 40)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Thread
        Label(0)
        Call(StartRumble, 1)
        Call(ShakeCam, 1, 0, 2, Float(0.5))
        Wait(1)
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        IfLt(LVar0, 60)
            Goto(0)
        EndIf
    EndThread
    Call(PlaySound, 619)
    Label(10)
    Call(GetActorVar, ACTOR_SELF, 5, LVarD)
    Call(TranslateModel, 31, 0, LVarD, 0)
    Add(LVarD, 1)
    Call(SetActorVar, ACTOR_SELF, 5, LVarD)
    Wait(1)
    IfLt(LVarD, 60)
        Goto(10)
    EndIf
    Call(StopSound, 619)
    Wait(10)
    Call(SummonEnemy, Ref(TTYD64_isk_part_2_tutankoopa_SummonedChomp), 0)
    Set(LVarB, LVar0)
    Set(LVar0, 165)
    Set(LVar1, 0)
    Set(LVar2, -30)
    Call(SetActorPos, LVarB, LVar0, LVar1, LVar2)
    Call(SetActorDispOffset, LVarB, 0, 0, 0)
    Call(UseIdleAnimation, LVarB, 0)
    Call(EnableIdleScript, LVarB, 0)
    Call(SetAnimation, LVarB, 1, 0x690005)
    Call(SetActorSpeed, LVarB, Float(6.0))
    Call(SetActorJumpGravity, LVarB, Float(0.80078125))
    Set(LVar0, 90)
    Set(LVar1, 0)
    Set(LVar2, -30)
    Set(LVar3, 8)
    Set(LVar4, 30)
    ExecWait(b_area_isk_part_2_tutankoopa_EVS_SummonedChompHop)
    Call(GetActorVar, ACTOR_SELF, 3, LVar5)
    IfEq(LVar5, 0)
        Call(UseBattleCamPreset, 19)
        Call(SetBattleCamDist, 160)
        Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
        Set(LVar1, 60)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(MoveBattleCamOver, 8)
        Loop(3)
            Call(UseBattleCamPreset, 19)
            Call(SetBattleCamDist, 150)
            Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
            Call(MoveBattleCamOver, 5)
            Wait(4)
            Call(PlaySoundAtActor, ACTOR_SELF, 8289)
            Call(UseBattleCamPreset, 19)
            Call(SetBattleCamDist, 200)
            Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
            Call(MoveBattleCamOver, 5)
            Wait(4)
        EndLoop
    Else
        Wait(8)
        Call(SetGoalPos, LVarB, LVar0, LVar1, LVar2)
        Call(JumpToGoal, LVarB, 8, 0, 1, 0)
        Thread
            Call(ShakeCam, 1, 0, 1, Float(0.5))
        EndThread
        Call(SetGoalPos, LVarB, LVar0, LVar1, LVar2)
        Call(JumpToGoal, LVarB, 8, 0, 1, 0)
        Thread
            Call(ShakeCam, 1, 0, 1, Float(0.5))
        EndThread
        Wait(8)
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Call(SetActorSpeed, LVarB, Float(3.0))
    Call(SetActorJumpGravity, LVarB, Float(0.80078125))
    Set(LVar0, 20)
    Set(LVar1, 0)
    Set(LVar2, 20)
    Set(LVar3, 8)
    Set(LVar4, 20)
    ExecWait(b_area_isk_part_2_tutankoopa_EVS_SummonedChompHop)
    Call(GetActorPos, LVarB, LVar0, LVar1, LVar2)
    Call(ForceHomePos, LVarB, LVar0, LVar1, LVar2)
    Call(SetPartPos, LVarB, 2, LVar0, LVar1, LVar2)
    Call(HPBarToHome, LVarB)
    Call(SetActorSpeed, LVarB, Float(6.0))
    Call(SetActorJumpGravity, LVarB, Float(0.80078125))
    Call(EnableIdleScript, LVarB, 1)
    Call(UseIdleAnimation, LVarB, 1)
    Call(SetActorVar, ACTOR_SELF, 5, 60)
    Thread
        Label(40)
        Call(StartRumble, 1)
        Call(ShakeCam, 1, 0, 2, Float(0.5))
        Wait(1)
        Call(GetActorVar, ACTOR_SELF, 5, LVar0)
        IfNe(LVar0, 0)
            Goto(40)
        EndIf
    EndThread
    Call(PlaySound, 619)
    Label(50)
    Call(GetActorVar, ACTOR_SELF, 5, LVarD)
    Call(TranslateModel, 31, 0, LVarD, 0)
    Sub(LVarD, 1)
    Call(SetActorVar, ACTOR_SELF, 5, LVarD)
    Wait(1)
    IfGt(LVarD, 0)
        Goto(50)
    EndIf
    Call(StopSound, 619)
    Call(PlaySound, 620)
    Call(ShakeCam, 1, 0, 4, Float(0.5))
    Call(SetActorVar, ACTOR_SELF, 3, 1)
    Return
    End
};
// clang-format on

FormationRow TTYD64_isk_part_2_Formation_00[] = {
    { .actor = &TTYD64_isk_part_2_tutankoopa,
      .home = { .vec = &b_area_isk_part_2_BossPos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

Battle TTYD64_isk_part_2_Formations[] = {
    { .name = "\203J\201[\203\201\203\223\201@\203\217\203\223\203\217\203\223",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_isk_part_2_Formation_00,
      .stage = &b_area_isk_part_2_isk_01,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_isk_part_2_tutankoopa_EVS_Attack_ThrowShell = {
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    Switch(LVar0)
        CaseEq(1)
            Set(LVar9, 5)
        CaseEq(2)
            Set(LVar9, 4)
        CaseEq(3)
            Set(LVar9, 3)
        CaseDefault
            Return
    EndSwitch
    Sub(LVar0, 1)
    Call(SetActorVar, ACTOR_SELF, 2, LVar0)
    Call(UseBattleCamPreset, 15)
    Call(SetBattleCamDist, 320)
    Call(SetBattleCamOffsetY, 0)
    Call(BattleCamTargetActorPart, ACTOR_SELF, LVar9)
    Call(SetAnimation, ACTOR_SELF, 1, 0x680002)
    Call(GetPartOffset, ACTOR_SELF, LVar9, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Sub(LVar2, 3)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(RunToGoal, ACTOR_SELF, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x680001)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x680004)
    Wait(7)
    Call(GetPartOffset, ACTOR_SELF, LVar9, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Add(LVar1, 40)
    Call(SetPartJumpGravity, ACTOR_SELF, LVar9, Float(0.7998046875))
    Call(JumpPartTo, ACTOR_SELF, LVar9, LVar0, LVar1, LVar2, 5, 1)
    Wait(8)
    Call(SetAnimation, ACTOR_SELF, LVar9, 0x330005)
    Call(PlaySoundAtActor, ACTOR_SELF, 761)
    Call(UseBattleCamPreset, 2)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 1, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x680005)
            Call(SetPartMoveSpeed, ACTOR_SELF, LVar9, Float(14.0))
            Call(SetPartJumpGravity, ACTOR_SELF, LVar9, Float(0.2001953125))
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 50)
            Set(LVar1, -5)
            Call(FlyPartTo, ACTOR_SELF, LVar9, LVar0, LVar1, LVar2, 0, 30, 0)
            Call(UseBattleCamPreset, 2)
            Call(GetOwnerTarget, LVar3, 0)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Sub(LVar0, 65)
            Set(LVar1, -5)
            Call(SetPartMoveSpeed, ACTOR_SELF, LVar9, Float(6.0))
            Call(SetPartJumpGravity, ACTOR_SELF, LVar9, Float(0.099609375))
            Call(FlyPartTo, ACTOR_SELF, LVar9, LVar0, LVar1, LVar2, 0, 15, 0)
            Call(SetPartFlagBits, ACTOR_SELF, LVar9, 1, 1)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x680002)
            Call(RunToGoal, ACTOR_SELF, 10, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x680001)
            Return
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x680005)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar9, Float(14.0))
    Call(SetPartJumpGravity, ACTOR_SELF, LVar9, Float(0.2001953125))
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartJumpGravity, ACTOR_SELF, LVar9, Float(0.2001953125))
    Call(FlyPartTo, ACTOR_SELF, LVar9, LVar0, LVar1, LVar2, 0, 30, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar8, 0x10000000, 0, 0, 3, 32)
    Call(UseBattleCamPreset, 2)
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Sub(LVar0, 55)
    Set(LVar1, 0)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar9, Float(6.0))
    Call(SetPartJumpGravity, ACTOR_SELF, LVar9, Float(0.099609375))
    Call(FlyPartTo, ACTOR_SELF, LVar9, LVar0, LVar1, LVar2, 0, 25, 0)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar9, Float(4.0))
    Sub(LVar0, 20)
    Call(FlyPartTo, ACTOR_SELF, LVar9, LVar0, LVar1, LVar2, 0, 21, 0)
    Call(SetPartFlagBits, ACTOR_SELF, LVar9, 1, 1)
    Wait(19)
    IfEq(LVar8, 10)
        Return
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(YieldTurn)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x680002)
    Call(RunToGoal, ACTOR_SELF, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x680001)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_isk_part_2_tutankoopa_EVS_DropDebris_Self = {
    Call(SetTargetActor, ACTOR_SELF, 512)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar3, 170)
    Call(SetPartPos, ACTOR_SELF, 8, LVar0, LVar3, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, 8, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 8, 0x680016)
    Call(PlaySound, 8427)
    Call(SetPartMoveSpeed, ACTOR_SELF, 8, Float(8.0))
    Call(SetPartJumpGravity, ACTOR_SELF, 8, Float(0.2998046875))
    Call(FallPartTo, ACTOR_SELF, 8, LVar0, LVar1, LVar2, 20)
    Thread
        Loop(20)
            Call(SetPartFlagBits, ACTOR_SELF, 8, 1, 0)
            Wait(1)
            Call(SetPartFlagBits, ACTOR_SELF, 8, 1, 1)
            Wait(1)
        EndLoop
    EndThread
    Call(GetStatusFlags, 0, LVar0)
    IfNotFlag(LVar0, 0x35D000)
        Call(SetAnimation, 0, 0, 0x10032)
    EndIf
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfGt(LVar0, 0)
        Call(GetStatusFlags, 256, LVar0)
        IfNotFlag(LVar0, 0x35D000)
            Set(LVar0, 5)
            Exec(TTYD64_SetPartnerAnimation_Battle)
        EndIf
    EndIf
    Call(SetActorVar, ACTOR_SELF, 13, 1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 2, 32)
    Return
    End
};
// clang-format on

void TTYD64_InstallBattles_isk_part_2(void) {
    Mod_SetBattleList("TTYD64", 12, TTYD64_isk_part_2_Formations);
}
