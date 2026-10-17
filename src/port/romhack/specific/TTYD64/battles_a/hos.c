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

API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddActorVar);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(CountTargets);
API_CALLABLE(CreateHomeTargetList);
API_CALLABLE(ElectrifyActor);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyPartTo);
API_CALLABLE(FlyToGoal);
API_CALLABLE(ForceHomePos);
API_CALLABLE(FreezeBattleState);
API_CALLABLE(GetActionCommandMode);
API_CALLABLE(GetActorAttackBoost);
API_CALLABLE(GetActorDefenseBoost);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattleFlags2);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetBattleVar);
API_CALLABLE(GetDist2D);
API_CALLABLE(GetDistanceToGoal);
API_CALLABLE(GetEnemyMaxHP);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetIndexFromHome);
API_CALLABLE(GetIndexFromPos);
API_CALLABLE(GetLastDamage);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOriginalActorType);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartPos);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToCurrent);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HealActor);
API_CALLABLE(HideHealthBar);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(InterruptActionCommand);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(ResetActorSounds);
API_CALLABLE(ResetAllActorSounds);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActionCommandMode);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorType);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetBattleVar);
API_CALLABLE(SetDamageSource);
API_CALLABLE(SetEnemyHP);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetPartAlpha);
API_CALLABLE(SetPartDispOffset);
API_CALLABLE(SetPartEventBits);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetStatusTable);
API_CALLABLE(SetTargetActor);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowActionHud);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(VanishActor);
API_CALLABLE(WaitForBuffDone);
API_CALLABLE(YieldTurn);
API_CALLABLE(action_command_jump_init);
API_CALLABLE(action_command_jump_start);
API_CALLABLE(b_area_hos_ember_PlayLavaBubbleFlightSound);
API_CALLABLE(b_area_hos_magikoopa_CheckMagikoopaCastTarget);
API_CALLABLE(b_area_hos_magikoopa_SetAbsoluteStatusOffsets);
API_CALLABLE(b_area_hos_magikoopa_ShrinkActor);
API_CALLABLE(b_area_hos_magikoopa_StartRumbleWithParams);
extern s32 b_area_hos_ember_DefenseTable[];
extern EvtScript b_area_hos_ember_EVS_FlyHome;
extern EvtScript b_area_hos_ember_EVS_GetAvailableColumn;
extern EvtScript b_area_hos_ember_EVS_Idle;
extern s32 b_area_hos_ember_ProjectileAnims[];
extern s32 b_area_hos_ember_StatusTable[];
extern Vec3i b_area_hos_ember_SummonPos;
extern s32 b_area_hos_goombario_tutor_DefenseTable[];
extern EvtScript b_area_hos_goombario_tutor_EVS_HandleEvent;
extern EvtScript b_area_hos_goombario_tutor_EVS_Idle;
extern EvtScript b_area_hos_goombario_tutor_EVS_ManageTutorial;
extern s32 b_area_hos_goombario_tutor_StatusTable[];
extern Stage b_area_hos_hos_01;
extern Stage b_area_hos_hos_02;
extern s32 b_area_hos_magikoopa_BroomAnims[];
extern EvtScript b_area_hos_magikoopa_EVS_Flee;
extern EvtScript b_area_hos_magikoopa_EVS_FlyingClone_Init;
extern EvtScript b_area_hos_magikoopa_EVS_GetAvailableColumn;
extern EvtScript b_area_hos_magikoopa_EVS_HandleEvent;
extern EvtScript b_area_hos_magikoopa_EVS_Idle;
extern EvtScript b_area_hos_magikoopa_EVS_KnockDownCheck;
extern EvtScript b_area_hos_magikoopa_EVS_RemoveClone;
extern s32 b_area_hos_magikoopa_FlyingCloneDefense[];
extern s32 b_area_hos_magikoopa_FlyingCloneStatusTable[];
extern s32 b_area_hos_magikoopa_FlyingDefense[];
extern s32 b_area_hos_magikoopa_FlyingStatusTable[];
extern s32 b_area_hos_magikoopa_StatusTable[];
extern Vec3i b_area_hos_magikoopa_SummonPos;
extern EvtScript TTYD64_hos_magikoopa_EVS_TakeTurn;
extern EvtScript TTYD64_hos_magikoopa_EVS_Attack_MagicBlast;
extern EvtScript TTYD64_hos_magikoopa_EVS_Flying_HandleEvent;
extern EvtScript TTYD64_hos_goombario_tutor_EVS_TakeTurn;
extern EvtScript TTYD64_hos_magikoopa_EVS_Move_TryElectrify;
extern EvtScript TTYD64_hos_magikoopa_EVS_Move_TryBoostAttack;
extern EvtScript TTYD64_hos_magikoopa_EVS_Move_TryBoostDefense;
extern EvtScript TTYD64_hos_magikoopa_EVS_Move_TryTransparent;
extern EvtScript TTYD64_hos_magikoopa_EVS_Move_MakeClone;
extern EvtScript TTYD64_hos_ember_EVS_Attack_AirSweep;
extern EvtScript TTYD64_hos_magikoopa_EVS_Move_HealAll;
extern EvtScript TTYD64_hos_EVS_802202B8;
extern EvtScript TTYD64_hos_magikoopa_EVS_KnockDown;
extern EvtScript TTYD64_hos_ember_EVS_Attack_Tackle;
extern EvtScript TTYD64_hos_ember_EVS_HandleEvent;
extern EvtScript TTYD64_hos_magikoopa_EVS_Move_HealOne;
extern EvtScript TTYD64_hos_ember_EVS_Attack_ShootPartner;
extern EvtScript TTYD64_hos_ember_EVS_TrySplit;
extern EvtScript TTYD64_hos_EVS_8022384C;
extern EvtScript TTYD64_hos_ember_EVS_TakeTurn;
extern EvtScript TTYD64_hos_ember_EVS_ShootFire_Impl;
extern EvtScript TTYD64_hos_ember_EVS_Init;
extern EvtScript TTYD64_hos_magikoopa_EVS_Flying_Init;
extern EvtScript TTYD64_hos_goombario_tutor_EVS_Init;
extern EvtScript TTYD64_hos_ember_EVS_ShootFire;
extern ActorBlueprint TTYD64_hos_magikoopa_clone_flying;
extern ActorBlueprint TTYD64_hos_magikoopa_clone;
extern ActorBlueprint TTYD64_hos_ember;
extern ActorBlueprint TTYD64_hos_goombario_tutor;
extern ActorBlueprint TTYD64_hos_magikoopa_flying;
extern ActorBlueprint TTYD64_hos_ember_802265DC;
extern ActorPartBlueprint TTYD64_hos_ember_ActorParts[];
extern ActorPartBlueprint TTYD64_hos_magikoopa_FlyingParts[];
extern Battle TTYD64_hos_Formations[];
extern FormationRow TTYD64_hos_Formation_02[];
extern s32 TTYD64_hos_magikoopa_GroundAnims[];
extern s32 TTYD64_hos_goombario_tutor_DefaultAnims[];
extern s32 TTYD64_hos_ember_DefaultAnims[];
extern s32 TTYD64_hos_magikoopa_FlyingAnims[];
extern FormationRow TTYD64_hos_Formation_01[];
extern ActorPartBlueprint TTYD64_hos_goombario_tutor_ActorParts[];
extern ActorPartBlueprint TTYD64_hos_magikoopa_FlyingCloneParts[];
extern ActorPartBlueprint TTYD64_hos_magikoopa_CloneParts[];
extern FormationRow TTYD64_hos_ember_SummonFormation[];
extern FormationRow TTYD64_hos_magikoopa_FlyingCloneFormation[];
extern FormationRow TTYD64_hos_Formation_00[];
extern FormationRow TTYD64_hos_Formation_03[];
extern FormationRow TTYD64_hos_magikoopa_CloneFormation[];
extern s32 TTYD64_hos_Anims_8022695C[];

// clang-format off
EvtScript TTYD64_hos_magikoopa_EVS_TakeTurn = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_hos_magikoopa_EVS_Attack_MagicBlast)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 10, LVar0)
    IfEq(LVar0, 1)
        Goto(20)
    EndIf
    Set(LVarA, 0)
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
    Call(GetActorHP, LVar0, LVar2)
    Call(GetEnemyMaxHP, LVar0, LVar3)
    MulF(LVar2, Float(100.0))
    DivF(LVar2, LVar3)
    IfEq(LFlag0, 0)
        IfLe(LVar2, 0)
            Call(RandInt, 99, LVar4)
            Add(LVar4, 1)
            IfLt(LVar4, 0)
                Add(LVarA, 1)
                Set(LVarB, LVar0)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    IfGt(LVarA, 0)
        Goto(10)
    EndIf
    Set(LVarA, 0)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(1)
    Set(LFlag0, 0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar1)
    IfEq(LVar1, 71)
        Call(GetActorVar, LVar0, 8, LVar1)
        IfEq(LVar1, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetActorHP, LVar0, LVar2)
    Call(GetEnemyMaxHP, LVar0, LVar3)
    MulF(LVar2, Float(100.0))
    DivF(LVar2, LVar3)
    IfEq(LFlag0, 0)
        IfLe(LVar2, 0)
            Call(RandInt, 99, LVar4)
            Add(LVar4, 1)
            IfLt(LVar4, 0)
                Add(LVarA, 1)
                Set(LVarB, LVar0)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(1)
    EndIf
    IfGt(LVarA, 0)
        Goto(10)
    EndIf
    Set(LVarA, 0)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(2)
    Set(LFlag0, 0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetOriginalActorType, LVar0, LVar1)
    IfEq(LVar1, 71)
        Call(GetActorVar, LVar0, 8, LVar1)
        IfEq(LVar1, 1)
            Set(LFlag0, 1)
        EndIf
    EndIf
    Call(GetActorHP, LVar0, LVar2)
    Call(GetEnemyMaxHP, LVar0, LVar3)
    MulF(LVar2, Float(100.0))
    DivF(LVar2, LVar3)
    IfEq(LFlag0, 0)
        IfLe(LVar2, 0)
            Call(RandInt, 99, LVar4)
            Add(LVar4, 1)
            IfLt(LVar4, 0)
                Add(LVarA, 1)
                Set(LVarB, LVar0)
            EndIf
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(2)
    EndIf
    IfGt(LVarA, 0)
        Goto(10)
    EndIf
    Goto(20)
    Label(10)
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_hos_magikoopa_EVS_Flee)
        Return
    EndIf
    IfEq(LVarA, 1)
        Call(GetActorVar, ACTOR_SELF, 4, LVar0)
        IfLt(LVar0, 0)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 0)
                ExecWait(TTYD64_hos_magikoopa_EVS_Move_HealOne)
                Return
            EndIf
        Else
            Call(GetActorVar, ACTOR_SELF, 3, LVar0)
            IfLt(LVar0, 0)
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 0)
                    ExecWait(TTYD64_hos_magikoopa_EVS_Move_HealAll)
                    Return
                EndIf
            EndIf
        EndIf
    Else
        Call(GetActorVar, ACTOR_SELF, 3, LVar0)
        IfLt(LVar0, 0)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 0)
                ExecWait(TTYD64_hos_magikoopa_EVS_Move_HealAll)
                Return
            EndIf
        Else
            Call(GetActorVar, ACTOR_SELF, 4, LVar0)
            IfLt(LVar0, 0)
                SetF(LVar9, Float(100.0))
                Call(CreateHomeTargetList, 0x8002)
                Call(InitTargetIterator)
                Label(11)
                Set(LFlag0, 0)
                Call(GetOwnerTarget, LVar0, LVar1)
                Call(GetOriginalActorType, LVar0, LVar1)
                IfEq(LVar1, 71)
                    Call(GetActorVar, LVar0, 8, LVar1)
                    IfEq(LVar1, 1)
                        Set(LFlag0, 1)
                    EndIf
                EndIf
                Call(GetActorHP, LVar0, LVar2)
                Call(GetEnemyMaxHP, LVar0, LVar3)
                MulF(LVar2, Float(100.0))
                DivF(LVar2, LVar3)
                IfEq(LFlag0, 0)
                    IfLe(LVar2, LVar9)
                        SetF(LVar9, LVar2)
                        Set(LVarB, LVar0)
                    EndIf
                EndIf
                Call(ChooseNextTarget, 0, LVar0)
                IfNe(LVar0, -1)
                    Goto(11)
                EndIf
                Call(RandInt, 1000, LVar0)
                IfLt(LVar0, 0)
                    ExecWait(TTYD64_hos_magikoopa_EVS_Move_HealOne)
                    Return
                EndIf
            EndIf
        EndIf
    EndIf
    Label(20)
    Set(LVarA, 100)
    Set(LVarB, 0)
    Set(LVarC, 0)
    Set(LVarD, 0)
    Set(LVarE, 0)
    Set(LVarF, 0)
    Call(GetActorVar, ACTOR_SELF, 10, LVar0)
    IfEq(LVar0, 1)
        Set(LVarA, 100)
        Set(LVarB, 0)
        Set(LVarC, 0)
        Set(LVarD, 0)
        Set(LVarE, 0)
        Set(LVarF, 0)
        Goto(123)
    Else
        ExecWait(b_area_hos_magikoopa_EVS_GetAvailableColumn)
        IfEq(LVar0, -1)
            Set(LVarB, 0)
        EndIf
    EndIf
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNe(LVar0, 0)
        Set(LVarB, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 11, LVar0)
    Switch(LVar0)
        CaseEq(4)
            Call(GetActorVar, ACTOR_SELF, 5, LVar1)
            IfLt(LVar1, 0)
                Call(RandInt, 99, LVar0)
                Add(LVar0, 1)
                IfLe(LVar0, 0)
                    Set(LVarA, 0)
                    Set(LVarB, 0)
                    Set(LVarC, 100)
                    Set(LVarD, 0)
                    Set(LVarE, 0)
                    Set(LVarF, 0)
                EndIf
            EndIf
        CaseEq(5)
            Call(GetActorVar, ACTOR_SELF, 6, LVar1)
            IfLt(LVar1, 0)
                Call(RandInt, 99, LVar0)
                Add(LVar0, 1)
                IfLe(LVar0, 0)
                    Set(LVarA, 0)
                    Set(LVarB, 0)
                    Set(LVarC, 0)
                    Set(LVarD, 100)
                    Set(LVarE, 0)
                    Set(LVarF, 0)
                EndIf
            EndIf
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    IfGe(LVar0, 0)
        Set(LVarC, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 6, LVar0)
    IfGe(LVar0, 0)
        Set(LVarD, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 7, LVar0)
    IfGe(LVar0, 0)
        Set(LVarE, 0)
    EndIf
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfGe(LVar0, 0)
        Set(LVarF, 0)
    EndIf
    Label(123)
    Set(LVar9, 0)
    Add(LVar9, LVarA)
    Add(LVar9, LVarB)
    Add(LVar9, LVarC)
    Add(LVar9, LVarD)
    Add(LVar9, LVarE)
    Add(LVar9, LVarF)
    Sub(LVar9, 1)
    Call(RandInt, LVar9, LVar0)
    Add(LVar0, 1)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_hos_magikoopa_EVS_Attack_MagicBlast)
        Return
    EndIf
    Add(LVarA, LVarB)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_hos_magikoopa_EVS_Move_MakeClone)
        Return
    EndIf
    Add(LVarA, LVarC)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_hos_magikoopa_EVS_Move_TryBoostAttack)
        Return
    EndIf
    Add(LVarA, LVarD)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_hos_magikoopa_EVS_Move_TryBoostDefense)
        Return
    EndIf
    Add(LVarA, LVarE)
    IfLe(LVar0, LVarA)
        ExecWait(TTYD64_hos_magikoopa_EVS_Move_TryElectrify)
        Return
    EndIf
    ExecWait(TTYD64_hos_magikoopa_EVS_Move_TryTransparent)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_magikoopa_EVS_Attack_MagicBlast = {
    Call(SetActorVar, ACTOR_SELF, 11, 2)
    Set(LFlag0, 0)
    Set(LFlag1, 0)
    Call(GetActorVar, ACTOR_SELF, 10, LVar0)
    IfEq(LVar0, 1)
        Set(LFlag0, 1)
        Call(GetActorVar, ACTOR_SELF, 9, LVarA)
    EndIf
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        Set(LFlag1, 1)
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    IfEq(LFlag0, 1)
        Call(UseIdleAnimation, LVarA, 0)
    EndIf
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
    IfEq(LFlag1, 0)
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x560002)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 17)
            Add(LVar1, 33)
            Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 13)
        Else
            Sub(LVar0, 17)
            Add(LVar1, 33)
        EndIf
        Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    Else
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x570002)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
        EndIf
        Call(PlayEffect_impl, 71, 0, LVar0, LVar1, LVar2, Float(0.5), 30, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Wait(30)
    Call(EnemyTestTarget, ACTOR_SELF, LVar9, 0, 0, 1, 16)
    Switch(LVar9)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LFlag0, 1)
                Call(PlaySoundAtActor, LVarA, 8405)
            EndIf
            Call(PlaySoundAtActor, ACTOR_SELF, 8405)
            IfEq(LFlag1, 0)
                IfEq(LFlag0, 1)
                    Call(SetAnimation, LVarA, 1, 0x560003)
                EndIf
                Call(SetAnimation, ACTOR_SELF, 1, 0x560003)
            Else
                IfEq(LFlag0, 1)
                    Call(SetAnimation, LVarA, 1, 0x570003)
                EndIf
                Call(SetAnimation, ACTOR_SELF, 2, 0x570003)
            EndIf
            Wait(5)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
            Sub(LVar4, 50)
            Set(LVar5, 0)
            IfEq(LFlag1, 0)
                IfEq(LFlag0, 1)
                    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                    Call(b_area_hos_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
                EndIf
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfFlag(LVar3, 0x80000)
                    Sub(LVar0, 8)
                    Add(LVar1, 8)
                Else
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                EndIf
                Call(b_area_hos_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
            Else
                IfEq(LFlag0, 1)
                    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                    Call(b_area_hos_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
                EndIf
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(GetStatusFlags, ACTOR_SELF, LVar3)
                IfFlag(LVar3, 0x80000)
                    Sub(LVar0, 8)
                    Add(LVar1, 8)
                Else
                    Sub(LVar0, 20)
                    Add(LVar1, 20)
                EndIf
                Call(b_area_hos_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 30)
            EndIf
            Wait(50)
            IfEq(LVar9, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(YieldTurn)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            IfEq(LFlag0, 1)
                Call(UseIdleAnimation, LVarA, 1)
            EndIf
            Return
        EndCaseGroup
    EndSwitch
    IfEq(LFlag0, 1)
        Call(PlaySoundAtActor, LVarA, 8405)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8405)
    IfEq(LFlag1, 0)
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x560003)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 1, 0x560003)
    Else
        IfEq(LFlag0, 1)
            Call(SetAnimation, LVarA, 1, 0x570003)
        EndIf
        Call(SetAnimation, ACTOR_SELF, 2, 0x570003)
    EndIf
    Wait(5)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar4, LVar5, LVar6)
    IfEq(LFlag1, 0)
        IfEq(LFlag0, 1)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Add(LVar1, 20)
            Call(b_area_hos_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
        EndIf
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 8)
            Add(LVar1, 8)
        Else
            Sub(LVar0, 20)
            Add(LVar1, 20)
        EndIf
        Call(b_area_hos_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
    Else
        IfEq(LFlag0, 1)
            Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Add(LVar1, 20)
            Call(b_area_hos_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
        EndIf
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVar3)
        IfFlag(LVar3, 0x80000)
            Sub(LVar0, 8)
            Add(LVar1, 8)
        Else
            Sub(LVar0, 20)
            Add(LVar1, 20)
        EndIf
        Call(b_area_hos_magikoopa_ShrinkActor, LVar0, LVar1, LVar6, LVar4, LVar5, LVar6, 20)
    EndIf
    Wait(18)
    IfEq(LFlag0, 1)
        Wait(2)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 0, 32)
    Else
        Wait(2)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000010, 0, 0, 3, 32)
    EndIf
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(20)
            Call(YieldTurn)
        EndCaseGroup
    EndSwitch
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    IfEq(LFlag0, 1)
        Call(UseIdleAnimation, LVarA, 1)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_magikoopa_EVS_Flying_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetPartAlpha, ACTOR_SELF, 2, 255)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            BitwiseOrConst(LVar0, 1)
            Call(SetActorVar, ACTOR_SELF, 0, LVar0)
            ExecWait(b_area_hos_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseOrEq(10)
        CaseOrEq(12)
            ExecWait(b_area_hos_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_hos_magikoopa_EVS_RemoveClone)
            ExecWait(TTYD64_hos_magikoopa_EVS_KnockDown)
        EndCaseGroup
        CaseEq(61)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_hos_magikoopa_EVS_RemoveClone)
        CaseOrEq(14)
        CaseOrEq(15)
            ExecWait(b_area_hos_magikoopa_EVS_KnockDownCheck)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570005)
            SetConst(LVar2, 0x570006)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_hos_magikoopa_EVS_RemoveClone)
            ExecWait(TTYD64_hos_magikoopa_EVS_KnockDown)
        EndCaseGroup
        CaseEq(36)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570005)
            SetConst(LVar2, 0x570006)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_hos_magikoopa_EVS_RemoveClone)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570006)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            ExecWait(b_area_hos_magikoopa_EVS_RemoveClone)
        CaseEq(33)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            ExecWait(b_area_hos_magikoopa_EVS_RemoveClone)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(25)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfFlag(LVar0, 1)
                ExecWait(b_area_hos_magikoopa_EVS_RemoveClone)
                Return
            EndIf
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNe(LVar0, 0)
                ExecWait(b_area_hos_magikoopa_EVS_RemoveClone)
            EndIf
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_hos_magikoopa_EVS_RemoveClone)
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570001)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            ExecWait(b_area_hos_magikoopa_EVS_RemoveClone)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570004)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.5))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Wait(15)
            Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
            ExecWait(b_area_hos_magikoopa_EVS_Flee)
            Return
        CaseEq(58)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570002)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            ExecWait(b_area_hos_magikoopa_EVS_RemoveClone)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                IfFlag(LVar0, 0x80000)
                    Call(SetPartDispOffset, ACTOR_SELF, 2, -3, 0, 0)
                Else
                    Call(SetPartDispOffset, ACTOR_SELF, 2, -15, 0, 0)
                EndIf
            EndIf
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570001)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseEq(19)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x570004)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(b_area_hos_magikoopa_EVS_RemoveClone)
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_goombario_tutor_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 63)
    Call(SetBattleCamDist, 400)
    Call(SetBattleCamOffsetY, 40)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x90003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x90001)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x90006)
    Call(UseBattleCamPreset, 66)
    Call(SetBattleCamDist, 400)
    Call(SetBattleCamOffsetY, 40)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -10, 0, 0)
    Call(GetBattleFlags2, LVar0)
    IfFlag(LVar0, 512)
        Call(AddGoalPos, ACTOR_SELF, 5, 10, 0)
    EndIf
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.099609375))
    Thread
        Wait(4)
        Set(LVar0, 0)
        Loop(4)
            Add(LVar0, 45)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Call(SetAnimation, ACTOR_SELF, 1, 0x90006)
    EndThread
    Thread
        Call(LoadActionCommand, 1)
        Call(action_command_jump_init)
        Call(ShowActionHud, 1)
        Wait(10)
        Call(action_command_jump_start, 12, 3)
    EndThread
    Call(PlaySound, 994)
    Call(JumpToGoal, ACTOR_SELF, 22, 0, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x90006)
    Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
    Wait(1)
    Call(GetActionCommandMode, LVar0)
    IfEq(LVar0, 2)
        Call(SetActionCommandMode, 3)
        Loop(0)
            Call(GetActionCommandMode, LVar0)
            IfLt(LVar0, 2)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 1)
        Call(SetDamageSource, 5)
    EndIf
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x80000, 0, 0, 1, 32)
    Call(InterruptActionCommand)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(0)
        CaseOrEq(2)
        CaseOrEq(10)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(1)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x90001)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 40)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Add(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
            Add(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Sub(LVar0, 10)
            Call(JumpToGoal, ACTOR_SELF, 4, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x90001)
            Wait(8)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0x90001)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x90003)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x90001)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_magikoopa_EVS_Move_TryElectrify = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_hos_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
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
        ExecWait(b_area_hos_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_hos_magikoopa_EVS_Attack_MagicBlast)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 6)
    Call(AddActorVar, ACTOR_SELF, 7, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
    EndIf
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 752)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 6)
            Add(LVar1, 12)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Loop(4)
            Call(PlaySoundAtActor, LVar8, 978)
            Call(RandInt, 3, LVar0)
            Add(LVar0, 3)
            Wait(LVar0)
        EndLoop
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(ElectrifyActor, LVar8, 0)
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
EvtScript TTYD64_hos_magikoopa_EVS_Move_TryBoostAttack = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_hos_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
        IfEq(LVar3, 0)
            Call(GetActorAttackBoost, LVar0, LVar4)
            IfLt(LVar4, 0)
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
        ExecWait(b_area_hos_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_hos_magikoopa_EVS_Attack_MagicBlast)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 4)
    Call(AddActorVar, ACTOR_SELF, 5, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Call(PlaySoundAtActor, LVar8, 733)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(TTYD64_BoostAttack, LVar8, 0, 3)
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
EvtScript TTYD64_hos_magikoopa_EVS_Move_TryBoostDefense = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_hos_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
        IfEq(LVar3, 0)
            Call(GetActorDefenseBoost, LVar0, LVar4)
            IfLt(LVar4, 0)
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
        ExecWait(b_area_hos_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_hos_magikoopa_EVS_Attack_MagicBlast)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 5)
    Call(AddActorVar, ACTOR_SELF, 6, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 16)
            Add(LVar1, 31)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetStatusFlags, ACTOR_SELF, LVarA)
        IfFlag(LVarA, 0x80000)
            Sub(LVar0, 12)
            Add(LVar1, 14)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.1201171875), 30, 0, 0, 0, 0, 0, 0, 0)
        Else
            Sub(LVar0, 30)
            Add(LVar1, 36)
            Sub(LVar2, 2)
            Call(PlayEffect_impl, 51, 5, LVar0, LVar1, LVar2, Float(0.2998046875), 30, 0, 0, 0, 0, 0, 0, 0)
        EndIf
    EndIf
    Wait(30)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Call(PlaySoundAtActor, LVar8, 733)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(TTYD64_BoostDefense, LVar8, 0, 3)
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
EvtScript TTYD64_hos_magikoopa_EVS_Move_TryTransparent = {
    Set(LFlag0, 0)
    Label(10)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(GetIndexFromHome, LVar0, LVar1)
    Call(GetBattleVar, 2, LVar2)
    IfGt(LVar1, LVar2)
        Call(b_area_hos_magikoopa_CheckMagikoopaCastTarget, LVar0, LVar3)
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
        ExecWait(b_area_hos_magikoopa_EVS_Flee)
        Return
    EndIf
    ExecWait(TTYD64_hos_magikoopa_EVS_Attack_MagicBlast)
    Return
    Label(100)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 7)
    Call(AddActorVar, ACTOR_SELF, 8, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
    EndIf
    Wait(5)
    Thread
        Wait(10)
        Call(PlaySoundAtActor, LVar8, 731)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(VanishActor, LVar8, 0)
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
EvtScript TTYD64_hos_magikoopa_EVS_Move_MakeClone = {
    Call(CountTargets, ACTOR_SELF, 0x8002, LVar0)
    IfEq(LVar0, 1)
        ExecWait(b_area_hos_magikoopa_EVS_Flee)
        Return
    EndIf
    Call(SetActorVar, ACTOR_SELF, 10, 1)
    Call(SetActorVar, ACTOR_SELF, 11, 3)
    Set(LFlag0, 0)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 512)
        Set(LFlag0, 1)
    EndIf
    IfEq(LFlag0, 0)
        Call(SummonEnemy, Ref(TTYD64_hos_magikoopa_CloneFormation), 0)
    Else
        Call(SummonEnemy, Ref(TTYD64_hos_magikoopa_FlyingCloneFormation), 0)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 9, LVar0)
    Set(LVarA, LVar0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(EnableIdleScript, LVarA, 0)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(UseIdleAnimation, LVarA, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 25)
    Wait(25)
    Call(PlaySoundAtActor, ACTOR_SELF, 8406)
    IfEq(LFlag0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
        Call(SetAnimation, LVarA, 1, 0x560002)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 23)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
        Call(SetAnimation, LVarA, 1, 0x570002)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 23)
    EndIf
    Call(PlayEffect_impl, 107, 1, LVar0, LVar1, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
    Wait(10)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(EnableIdleScript, LVar9, 1)
    Wait(30)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, -3)
    Call(SetActorPos, LVarA, LVar0, LVar1, LVar2)
    Set(LVar9, LVarA)
    Wait(15)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Call(PlaySoundAtActor, ACTOR_SELF, 8407)
    Call(PlaySoundAtActor, LVar9, 8407)
    Call(SetPartFlagBits, LVar9, 1, 0x800000, 0)
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 500)
        Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
        ExecWait(b_area_hos_magikoopa_EVS_GetAvailableColumn)
        Call(SetGoalToIndex, ACTOR_SELF, LVar0)
        Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
    Else
        Call(SetActorSpeed, LVar9, Float(2.0))
        ExecWait(b_area_hos_magikoopa_EVS_GetAvailableColumn)
        Call(SetGoalToIndex, LVar9, LVar0)
        Call(FlyToGoal, LVar9, 0, 0, 0)
    EndIf
    Call(SetPartFlagBits, LVar9, 1, 0x800000, 1)
    Call(GetActorHP, ACTOR_SELF, LVar0)
    Call(SetEnemyHP, LVar9, LVar0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Call(GetActorPos, LVar9, LVar0, LVar1, LVar2)
    Call(ForceHomePos, LVar9, LVar0, LVar1, LVar2)
    Call(HPBarToHome, LVar9)
    IfEq(LFlag0, 0)
        Call(SetPartEventBits, ACTOR_SELF, 1, 0x400000, 1)
    Else
        Call(SetPartEventBits, ACTOR_SELF, 2, 0x400000, 1)
    EndIf
    IfEq(LFlag0, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
        Call(SetAnimation, LVar9, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
        Call(SetAnimation, LVar9, 1, 0x570001)
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Call(UseIdleAnimation, LVar9, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_ember_EVS_Attack_AirSweep = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460103)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 30, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Thread
        Call(b_area_hos_ember_PlayLavaBubbleFlightSound)
    EndThread
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 11)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 719)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            Call(SetAnimation, ACTOR_SELF, 1, 0x460104)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
            Call(ResetActorSounds, ACTOR_SELF, 2)
            Call(PlaySoundAtActor, ACTOR_SELF, 751)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Add(LVar2, 2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x460104)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(30)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(b_area_hos_ember_EVS_FlyHome)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Wait(5)
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 719)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetAnimation, ACTOR_SELF, 1, 0x460104)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 0, 0)
    Call(ResetActorSounds, ACTOR_SELF, 2)
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Set(LVarC, LVar2)
    Call(PlaySoundAtActor, ACTOR_SELF, 751)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, 2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 2, 0, 0, 4, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalPos, ACTOR_SELF, LVarA, LVarB, LVarC)
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 0)
            Wait(20)
            ExecWait(b_area_hos_ember_EVS_FlyHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_magikoopa_EVS_Move_HealAll = {
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 1)
    Call(AddActorVar, ACTOR_SELF, 3, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
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
            Call(HealActor, LVar0, 0, 1)
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
    Call(MoveBattleCamOver, 10)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_EVS_802202B8 = {
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
    Call(GetOwnerTarget, LVarA, 0)
    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460101)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460105)
    Wait(30)
    Call(PlaySoundAtActor, ACTOR_SELF, 720)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460106)
    Thread
        Wait(8)
        Call(SetAnimation, ACTOR_SELF, 1, 0x460101)
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Add(LVar1, 4)
    Add(LVar2, 2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(TTYD64_GetMarioPos, LVar0)
    IfEq(LVar0, 0)
        Set(LVarB, 256)
    Else
        Set(LVarB, 0)
    EndIf
    Call(GetGoalPos, LVarB, LVar3, LVar4, LVar5)
    Add(LVar3, 55)
    Sub(LVar4, 6)
    Add(LVar5, 2)
    Set(LVar6, 6)
    Call(GetStatusFlags, ACTOR_SELF, LVarA)
    IfFlag(LVarA, 0x80000)
        Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.5), Float(0.5), Float(0.5))
    Else
        Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.7998046875), Float(0.7998046875), Float(0.7998046875))
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Add(LVar1, 4)
    Add(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, LVar6, LVar0, LVar1, LVar2)
    Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 0)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(6.0))
    Call(SetPartJumpGravity, ACTOR_SELF, LVar6, Float(0.009765625))
    Call(SetPartSounds, ACTOR_SELF, LVar6, 2, 720, 0)
    Call(FlyPartTo, ACTOR_SELF, LVar6, LVar3, LVar1, LVar5, 0, 0, 4)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(4.0))
    Call(GetPartPos, ACTOR_SELF, LVar6, LVar3, LVar4, LVar5)
    Add(LVar3, 40)
    Call(FlyPartTo, ACTOR_SELF, LVar6, LVar3, LVar1, LVar5, 0, 0, 4)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(5.0))
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(FlyPartTo, ACTOR_SELF, LVar6, LVar3, LVar1, LVar5, 0, 0, 3)
    Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 1)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x18000002, 0, 0, 3, 32)
    EndSwitch
    Wait(20)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            ExecWait(b_area_hos_ember_EVS_FlyHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_magikoopa_EVS_KnockDown = {
    Call(GetActorVar, ACTOR_SELF, 2, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560004)
        Goto(0)
    EndIf
    Call(GetLastElement, LVar0)
    IfFlag(LVar0, 1024)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560004)
        Goto(0)
    EndIf
    Return
    Label(0)
    Call(HideHealthBar, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x80000)
        Call(SetPartScale, ACTOR_SELF, 3, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    EndIf
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x800000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 1, 0x20001, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x20001, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 2, 0x800000, 0)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 0x100000, 1)
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar2, 1)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(PlaySoundAtActor, ACTOR_SELF, 769)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
    Call(b_area_hos_magikoopa_StartRumbleWithParams, 150, 10)
    Thread
        Call(ShakeCam, 1, 0, 5, Float(0.7001953125))
    EndThread
    Call(GetLastEvent, ACTOR_SELF, LVar3)
    IfEq(LVar3, 15)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560004)
        Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        Add(LVar4, 10)
        Add(LVar5, 5)
        Call(PlayEffect_impl, 39, 0, LVar3, LVar4, LVar5, Float(1.0), 10, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Loop(20)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
        Wait(1)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
        Wait(1)
    EndLoop
    Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_hos_magikoopa_EVS_HandleEvent))
    Call(SetActorType, ACTOR_SELF, 149)
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_hos_magikoopa_StatusTable))
    Call(b_area_hos_magikoopa_SetAbsoluteStatusOffsets, -10, 20, 10, 32)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Call(GetIndexFromPos, ACTOR_SELF, LVar0)
    Mod(LVar0, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVar0)
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_ember_EVS_Attack_Tackle = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460103)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Set(LVar1, 5)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Thread
        Call(b_area_hos_ember_PlayLavaBubbleFlightSound)
    EndThread
    Call(FlyToGoal, ACTOR_SELF, 0, 0, 11)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460101)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x460104)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Set(LVar1, 0)
            Add(LVar2, 1)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVarA, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
            Sub(LVar0, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Sub(LVar0, 10)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 3, 0, 1, 0)
            Wait(14)
            Call(UseBattleCamPreset, 2)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(b_area_hos_ember_EVS_FlyHome)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x460104)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, 1)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 130, 0, 0, 4, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Set(LVar0, 1)
            Set(LVar1, 0x460104)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Wait(5)
            ExecWait(b_area_hos_ember_EVS_FlyHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_ember_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Exec(TTYD64_hos_ember_EVS_TrySplit)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            Exec(TTYD64_hos_ember_EVS_TrySplit)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460108)
            SetConst(LVar2, 0x460109)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460108)
            SetConst(LVar2, 0x460109)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460109)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            Exec(TTYD64_hos_ember_EVS_TrySplit)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(PlaySoundAtActor, ACTOR_SELF, 1881)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(b_area_hos_ember_EVS_FlyHome)
        CaseEq(38)
            Call(PlaySoundAtActor, ACTOR_SELF, 1881)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
        CaseOrEq(28)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460101)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_Hit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460107)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(b_area_hos_ember_EVS_FlyHome)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460101)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460103)
            SetConst(LVar2, 0x460107)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460103)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x460103)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(61)
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_magikoopa_EVS_Move_HealOne = {
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, 0)
    Call(AddActorVar, ACTOR_SELF, 4, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 15)
    Wait(15)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 512)
        Call(SetAnimation, ACTOR_SELF, 1, 0x560002)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570002)
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
        Call(SetAnimation, ACTOR_SELF, 1, 0x560001)
    Else
        Call(SetAnimation, ACTOR_SELF, 2, 0x570001)
    EndIf
    Wait(5)
    Thread
        Wait(5)
        Call(PlaySoundAtActor, LVarB, 8301)
        Call(PlaySoundAtActor, LVarB, 532)
        Wait(30)
        Call(PlaySoundAtActor, LVarB, 604)
    EndThread
    Thread
        Call(FreezeBattleState, 1)
        Call(HealActor, LVarB, 0, 0)
        Call(FreezeBattleState, 0)
    EndThread
    Call(WaitForBuffDone)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 10)
    Wait(10)
    Call(YieldTurn)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_ember_EVS_Attack_ShootPartner = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetTargetActor, ACTOR_SELF, 256)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(TTYD64_GetMarioPos, LVar0)
    IfEq(LVar0, 0)
        Set(LVarA, 256)
    Else
        Set(LVarA, 0)
    EndIf
    Call(GetActorPos, LVarA, LVar0, LVar1, LVar2)
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfEq(LVarA, 1)
        Add(LVar0, 100)
        Set(LVar1, 5)
    Else
        Add(LVar0, 30)
        Set(LVar1, 50)
    EndIf
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460103)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Thread
        Call(b_area_hos_ember_PlayLavaBubbleFlightSound)
    EndThread
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 11)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460101)
    Wait(10)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460105)
    Wait(30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x460106)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Add(LVar1, 4)
    Add(LVar2, 2)
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfLe(LVar0, 0)
        Call(SetTargetActor, ACTOR_SELF, 0)
    Else
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar4, 6)
    Add(LVar5, 2)
    ExecWait(TTYD64_hos_ember_EVS_ShootFire)
    Wait(20)
    Switch(LVar9)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(b_area_hos_ember_EVS_FlyHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_ember_EVS_TrySplit = {
    Call(GetLastDamage, ACTOR_SELF, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(GetActorHP, ACTOR_SELF, LVar0)
    IfLe(LVar0, 0)
        Return
    EndIf
    Call(GetLastElement, LVar0)
    IfFlag(LVar0, 0x20000000)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 1, LVar0)
    IfGe(LVar0, 2)
        Return
    EndIf
    ExecWait(b_area_hos_ember_EVS_GetAvailableColumn)
    Switch(LVarA)
        CaseOrEq(0)
        CaseOrEq(1)
        CaseOrEq(2)
        CaseOrEq(3)
            Call(SummonEnemy, Ref(TTYD64_hos_ember_SummonFormation), 0)
            Call(SetActorVar, LVar0, 2, 1)
            Call(GetActorHP, ACTOR_SELF, LVarB)
            Call(SetEnemyHP, LVar0, LVarB)
            Call(GetActorPos, ACTOR_SELF, LVarB, LVarC, LVarD)
            Call(SetActorPos, LVar0, LVarB, LVarC, LVarD)
            Call(SetGoalToIndex, LVar0, LVarA)
            Call(GetGoalPos, LVar0, LVarB, LVarC, LVarD)
            Call(SetHomePos, LVar0, LVarB, LVarC, LVarD)
            Call(SetActorJumpGravity, LVar0, Float(1.2001953125))
            Call(JumpToGoal, LVar0, 20, 0, 1, 0)
            Call(HPBarToHome, LVar0)
            Call(GetActorVar, ACTOR_SELF, 1, LVar1)
            Switch(LVar1)
                CaseEq(0)
                    Call(SetActorVar, LVar0, 1, 1)
                CaseEq(1)
                    Call(SetActorVar, LVar0, 1, 2)
            EndSwitch
            Call(SetActorVar, ACTOR_SELF, 1, 3)
            Call(SetActorVar, LVar0, 2, 0)
        EndCaseGroup
        CaseDefault
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_EVS_8022384C = {
    Loop(0)
        Call(GetPartPos, ACTOR_SELF, LVar6, LVar1, 0, LVar2)
        Call(TTYD64_GetMarioPos, LVar0)
        IfEq(LVar0, 0)
            Set(LVar0, 256)
        Else
            Set(LVar0, 0)
        EndIf
        Call(GetActorPos, LVar0, LVar3, 0, LVar4)
        Call(GetDist2D, LVar0, LVar1, LVar2, LVar3, LVar4)
        IfLe(LVar0, 12)
            Call(GetOwnerTarget, LVar5, 0)
            Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(EnemyTestTarget, ACTOR_SELF, LVar9, 0, 0, 1, 16)
            Switch(LVar9)
                CaseOrEq(6)
                CaseOrEq(5)
                    IfEq(LVarA, 5)
                        Call(EnemyTestTarget, ACTOR_SELF, LVar9, (-0x7FFFFFFF - 1), 0, 0, 0)
                    EndIf
                    BreakLoop
            EndSwitch
            Call(EnemyDamageTarget, ACTOR_SELF, LVar9, 0x10000002, 0, 0, 3, 32)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVar9, 0, 0, 1, 16)
    Switch(LVar9)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar9, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVar9, 0x10000002, 0, 0, 3, 32)
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_ember_EVS_TakeTurn = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(GetActorVar, ACTOR_SELF, 0, LVar0)
        Switch(LVar0)
            CaseEq(1)
                ExecWait(TTYD64_hos_ember_EVS_Attack_Tackle)
            CaseEq(0)
                ExecWait(TTYD64_hos_ember_EVS_Attack_AirSweep)
        EndSwitch
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(1)
            Call(GetStatusFlags, 256, LVar0)
            IfFlag(LVar0, 0x1000000)
                Call(RandInt, 99, LVar0)
                IfLt(LVar0, 49)
                    ExecWait(TTYD64_hos_EVS_802202B8)
                Else
                    ExecWait(TTYD64_hos_ember_EVS_Attack_Tackle)
                EndIf
            Else
                Call(RandInt, 1000, LVar0)
                IfLe(LVar0, 300)
                    ExecWait(TTYD64_hos_ember_EVS_Attack_ShootPartner)
                Else
                    Call(RandInt, 99, LVar0)
                    IfLt(LVar0, 49)
                        ExecWait(TTYD64_hos_EVS_802202B8)
                    Else
                        ExecWait(TTYD64_hos_ember_EVS_Attack_Tackle)
                    EndIf
                EndIf
            EndIf
        CaseEq(0)
            Call(GetStatusFlags, 256, LVar0)
            IfFlag(LVar0, 0x1000000)
                ExecWait(TTYD64_hos_ember_EVS_Attack_AirSweep)
            Else
                Call(RandInt, 1000, LVar0)
                IfLe(LVar0, 300)
                    ExecWait(TTYD64_hos_ember_EVS_Attack_ShootPartner)
                Else
                    ExecWait(TTYD64_hos_ember_EVS_Attack_AirSweep)
                EndIf
            EndIf
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_ember_EVS_ShootFire_Impl = {
    Set(LVar6, 2)
    Set(LVar7, 4)
    Loop(LVar7)
        Thread
            Call(GetStatusFlags, ACTOR_SELF, LVarA)
            IfFlag(LVarA, 0x80000)
                Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.2001953125), Float(0.2001953125), Float(0.2001953125))
            Else
                Call(SetPartScale, ACTOR_SELF, LVar6, Float(0.5), Float(0.5), Float(0.5))
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 5)
            Add(LVar1, 4)
            Add(LVar2, 2)
            Call(SetPartPos, ACTOR_SELF, LVar6, LVar0, LVar1, LVar2)
            Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 0)
            Call(SetPartMoveSpeed, ACTOR_SELF, LVar6, Float(8.0))
            Call(SetPartJumpGravity, ACTOR_SELF, LVar6, Float(0.009765625))
            Call(SetPartSounds, ACTOR_SELF, LVar6, 2, 720, 0)
            IfEq(LVar7, 4)
                Call(TTYD64_GetPartnerHP_API, LVar8)
                IfGt(LVar8, 0)
                    Exec(TTYD64_hos_EVS_8022384C)
                EndIf
            EndIf
            Call(JumpPartTo, ACTOR_SELF, LVar6, LVar3, LVar4, LVar5, 0, 0)
            Call(SetPartFlagBits, ACTOR_SELF, LVar6, 1, 1)
        EndThread
        Wait(3)
        Add(LVar6, 1)
    EndLoop
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_ember_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_hos_ember_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_hos_ember_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_hos_ember_EVS_HandleEvent))
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
        CaseEq(1)
            Call(SetActorVar, ACTOR_SELF, 0, 0)
    EndSwitch
    Call(SetPartScale, ACTOR_SELF, 2, Float(0.5), Float(0.5), Float(0.5))
    Call(SetPartScale, ACTOR_SELF, 3, Float(0.5), Float(0.5), Float(0.5))
    Call(SetPartScale, ACTOR_SELF, 4, Float(0.5), Float(0.5), Float(0.5))
    Call(SetPartScale, ACTOR_SELF, 5, Float(0.5), Float(0.5), Float(0.5))
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 5)
    Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(HPBarToHome, ACTOR_SELF)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_hos_magikoopa_EVS_Flying_Init = {
    Call(BindIdle, ACTOR_SELF, Ref(b_area_hos_magikoopa_EVS_Idle))
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_hos_magikoopa_EVS_TakeTurn))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_hos_magikoopa_EVS_Flying_HandleEvent))
    Call(GetBattleVar, 2, LVar0)
    IfEq(LVar0, 0)
        Call(SetBattleVar, 2, -1)
    EndIf
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 0)
    Call(SetActorVar, ACTOR_SELF, 7, 0)
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(SetActorVar, ACTOR_SELF, 9, -1)
    Call(SetActorVar, ACTOR_SELF, 10, 0)
    Call(SetActorVar, ACTOR_SELF, 11, -1)
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_hos_ember_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 25 },
        .opacity = 255,
        .idleAnimations = TTYD64_hos_ember_DefaultAnims,
        .defenseTable = b_area_hos_ember_DefenseTable,
        .eventFlags = 0x2,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -3, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = b_area_hos_ember_ProjectileAnims,
        .defenseTable = b_area_hos_ember_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = b_area_hos_ember_ProjectileAnims,
        .defenseTable = b_area_hos_ember_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = b_area_hos_ember_ProjectileAnims,
        .defenseTable = b_area_hos_ember_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = b_area_hos_ember_ProjectileAnims,
        .defenseTable = b_area_hos_ember_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 6,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_hos_Anims_8022695C,
        .defenseTable = b_area_hos_ember_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -10 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_hos_goombario_tutor_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_hos_goombario_tutor_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_hos_goombario_tutor_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_hos_goombario_tutor_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 0, 1)
    Exec(b_area_hos_goombario_tutor_EVS_ManageTutorial)
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_hos_magikoopa_FlyingParts[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_hos_magikoopa_GroundAnims,
        .defenseTable = b_area_hos_magikoopa_FlyingDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -10, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_hos_magikoopa_FlyingAnims,
        .defenseTable = b_area_hos_magikoopa_FlyingDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 0 },
        .opacity = 255,
        .idleAnimations = b_area_hos_magikoopa_BroomAnims,
        .defenseTable = b_area_hos_magikoopa_FlyingDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

Battle TTYD64_hos_Formations[] = {
    { .name = "\257\352\252\010!#\330\353\327\011",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_hos_Formation_00,
      .stage = &b_area_hos_hos_02,
      .onBattleStart = NULL },
    { .name = "\250\353\342\271x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_hos_Formation_01,
      .stage = &b_area_hos_hos_01,
      .onBattleStart = NULL },
    { .name = "\250\353\342\271x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_hos_Formation_02,
      .stage = &b_area_hos_hos_01,
      .onBattleStart = NULL },
    { .name = "\253\341\303\257\010!#\330\353\327T\011",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_hos_Formation_03,
      .stage = &b_area_hos_hos_02,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_hos_ember_EVS_ShootFire = {
    Exec(TTYD64_hos_ember_EVS_ShootFire_Impl)
    Call(GetDistanceToGoal, ACTOR_SELF, LVar0)
    DivF(LVar0, Float(8.0))
    Add(LVar0, 1)
    Wait(LVar0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_hos_Formation_02[] = {
    { .actor = &TTYD64_hos_ember,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_EMBER },
    { .actor = &TTYD64_hos_ember,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_EMBER },
    { .actor = &TTYD64_hos_ember,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_EMBER },
};

s32 TTYD64_hos_magikoopa_GroundAnims[] = {
    1,  0x560001, 7, 0x560000, 6, 0x560008, 9, 0x560001, 8, 0x560000,
    11, 0x560001, 5, 0x560000, 4, 0x560007, 3, 0x560007, 0,
};

s32 TTYD64_hos_goombario_tutor_DefaultAnims[] = {
    1, 0x90001, 7, 0x90000, 6, 0x90000, 9, 0x90001, 8, 0x90000, 11, 0x90000, 5, 0x90000, 4, 0x90000, 4, 0x90000, 0,
};

s32 TTYD64_hos_ember_DefaultAnims[] = {
    1,  0x460101, 7, 0x460100, 6, 0x460101, 9, 0x460101, 8, 0x460100,
    11, 0x460101, 5, 0x460100, 4, 0x46010A, 3, 0x46010A, 0,
};

s32 TTYD64_hos_magikoopa_FlyingAnims[] = {
    1,  0x570001, 7, 0x570000, 6, 0x570008, 9, 0x570001, 8, 0x570000,
    11, 0x570001, 5, 0x570000, 4, 0x570007, 3, 0x570007, 0,
};

FormationRow TTYD64_hos_Formation_01[] = {
    { .actor = &TTYD64_hos_ember,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_EMBER },
    { .actor = &TTYD64_hos_ember,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_EMBER },
};

ActorBlueprint TTYD64_hos_magikoopa_clone_flying = {
    .flags = 0x200200,
    .maxHP = 11,
    .type = 0x50,
    .level = 26,
    .partCount = 1,
    .partsData = TTYD64_hos_magikoopa_FlyingCloneParts,
    .initScript = &b_area_hos_magikoopa_EVS_FlyingClone_Init,
    .statusTable = b_area_hos_magikoopa_FlyingCloneStatusTable,
    .escapeChance = 40,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 2,
    .size = { 48, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -25, 20 },
    .statusTextOffset = { 1, 34 },
};

ActorBlueprint TTYD64_hos_magikoopa_clone = {
    .flags = 0x200000,
    .maxHP = 11,
    .type = 0x4F,
    .level = 26,
    .partCount = 1,
    .partsData = TTYD64_hos_magikoopa_CloneParts,
    .initScript = &b_area_hos_magikoopa_EVS_FlyingClone_Init,
    .statusTable = b_area_hos_magikoopa_FlyingCloneStatusTable,
    .escapeChance = 40,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 75,
    .coinReward = 0,
    .size = { 36, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 32 },
};

ActorBlueprint TTYD64_hos_ember = {
    .flags = 0x200,
    .maxHP = 10,
    .type = 0x45,
    .level = 24,
    .partCount = 6,
    .partsData = TTYD64_hos_ember_ActorParts,
    .initScript = &TTYD64_hos_ember_EVS_Init,
    .statusTable = b_area_hos_ember_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 80,
    .hurricaneChance = 75,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 33, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_hos_goombario_tutor = {
    .flags = 0x40000,
    .maxHP = 99,
    .type = 0x94,
    .level = 99,
    .partCount = 1,
    .partsData = TTYD64_hos_goombario_tutor_ActorParts,
    .initScript = &TTYD64_hos_goombario_tutor_EVS_Init,
    .statusTable = b_area_hos_goombario_tutor_StatusTable,
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

ActorBlueprint TTYD64_hos_magikoopa_flying = {
    .flags = 0x200,
    .maxHP = 8,
    .type = 0x96,
    .level = 32,
    .partCount = 3,
    .partsData = TTYD64_hos_magikoopa_FlyingParts,
    .initScript = &TTYD64_hos_magikoopa_EVS_Flying_Init,
    .statusTable = b_area_hos_magikoopa_FlyingStatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 100,
    .coinReward = 0,
    .size = { 48, 40 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_hos_ember_802265DC = {
    .flags = 0x200,
    .maxHP = 10,
    .type = 0x45,
    .level = 24,
    .partCount = 6,
    .partsData = TTYD64_hos_ember_ActorParts,
    .initScript = &TTYD64_hos_ember_EVS_Init,
    .statusTable = b_area_hos_ember_StatusTable,
    .escapeChance = 60,
    .airLiftChance = 80,
    .hurricaneChance = 75,
    .spookChance = 50,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 2,
    .size = { 33, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorPartBlueprint TTYD64_hos_goombario_tutor_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -4, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_hos_goombario_tutor_DefaultAnims,
        .defenseTable = b_area_hos_goombario_tutor_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_hos_magikoopa_FlyingCloneParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -10, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_hos_magikoopa_FlyingAnims,
        .defenseTable = b_area_hos_magikoopa_FlyingCloneDefense,
        .eventFlags = 0x20,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -8 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_hos_magikoopa_CloneParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 2, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_hos_magikoopa_GroundAnims,
        .defenseTable = b_area_hos_magikoopa_FlyingCloneDefense,
        .eventFlags = 0x20,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -5, -12 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_hos_ember_SummonFormation[] = {
    { .actor = &TTYD64_hos_ember_802265DC,
      .home = { .vec = &b_area_hos_ember_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_hos_magikoopa_FlyingCloneFormation[] = {
    { .actor = &TTYD64_hos_magikoopa_clone_flying,
      .home = { .vec = &b_area_hos_magikoopa_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_hos_Formation_00[] = {
    { .actor = &TTYD64_hos_goombario_tutor,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_hos_Formation_03[] = {
    { .actor = &TTYD64_hos_magikoopa_flying,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_hos_magikoopa_CloneFormation[] = {
    { .actor = &TTYD64_hos_magikoopa_clone,
      .home = { .vec = &b_area_hos_magikoopa_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

s32 TTYD64_hos_Anims_8022695C[] = {
    1,
    0x46010C,
    0,
};

void TTYD64_InstallBattles_hos(void) {
    Mod_SetBattleList("TTYD64", 4, TTYD64_hos_Formations);
}
