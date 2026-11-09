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
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyPartTo);
API_CALLABLE(FlyToGoal);
API_CALLABLE(ForceHomePos);
API_CALLABLE(GetActorHP);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastDamage);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPartOffset);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToHome);
API_CALLABLE(InterruptLeechActionCommand);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlaySoundAtPart);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTarget);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetEnemyHP);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartSounds);
API_CALLABLE(SetPartYaw);
API_CALLABLE(StopSound);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
API_CALLABLE(b_area_mim_bzzap_AddVecXZ);
API_CALLABLE(b_area_mim_forest_fuzzy_SpawnDrainHealthContinueFX);
API_CALLABLE(b_area_mim_forest_fuzzy_SpawnDrainHealthStartFX);
extern s32 b_area_mim_bzzap_DefenseTable[];
extern EvtScript b_area_mim_bzzap_EVS_HandleEvent;
extern EvtScript b_area_mim_bzzap_EVS_Idle;
extern EvtScript b_area_mim_bzzap_EVS_ReturnHome;
extern EvtScript b_area_mim_forest_fuzzy_EVS_CountSummoners;
extern EvtScript b_area_mim_forest_fuzzy_EVS_GetAvailableSpawnPos;
extern Vec3i b_area_mim_forest_fuzzy_SummonPos;
extern Stage b_area_mim_mim_01;
extern s32 b_area_mim_piranha_plant_DefenseTable[];
extern EvtScript b_area_mim_piranha_plant_EVS_HandleEvent;
extern EvtScript b_area_mim_piranha_plant_EVS_Idle;
extern EvtScript b_area_mim_piranha_plant_EVS_ReturnHome;
extern EvtScript TTYD64_mim_bzzap_EVS_Attack_CallSwarm;
extern EvtScript TTYD64_mim_forest_fuzzy_EVS_Attack_Leech;
extern EvtScript TTYD64_mim_piranha_plant_EVS_TakeTurn;
extern EvtScript TTYD64_mim_forest_fuzzy_EVS_HandleEvent;
extern EvtScript TTYD64_mim_bzzap_EVS_Attack_Sting;
extern EvtScript TTYD64_mim_bzzap_EVS_SummonSwarmPart;
extern EvtScript TTYD64_mim_forest_fuzzy_EVS_Move_Clone;
extern EvtScript TTYD64_mim_forest_fuzzy_EVS_TakeTurn;
extern EvtScript TTYD64_mim_bzzap_EVS_Init;
extern EvtScript TTYD64_mim_bzzap_EVS_TakeTurn;
extern EvtScript TTYD64_mim_forest_fuzzy_EVS_Init;
extern EvtScript TTYD64_mim_piranha_plant_EVS_Init;
extern ActorBlueprint TTYD64_mim_forest_fuzzy;
extern ActorBlueprint TTYD64_mim_bzzap;
extern ActorBlueprint TTYD64_mim_forest_fuzzy_8021EC2C;
extern ActorBlueprint TTYD64_mim_piranha_plant;
extern Battle TTYD64_mim_Formations[];
extern ActorPartBlueprint TTYD64_mim_bzzap_ActorParts[];
extern s32 TTYD64_mim_forest_fuzzy_StatusTable[];
extern s32 TTYD64_mim_bzzap_StatusTable[];
extern s32 TTYD64_mim_piranha_plant_StatusTable[];
extern FormationRow TTYD64_mim_Formation_0B[];
extern FormationRow TTYD64_mim_Formation_05[];
extern FormationRow TTYD64_mim_Formation_02[];
extern FormationRow TTYD64_mim_Formation_06[];
extern FormationRow TTYD64_mim_Formation_07[];
extern FormationRow TTYD64_mim_Formation_0A[];
extern FormationRow TTYD64_mim_Formation_0D[];
extern FormationRow TTYD64_mim_Formation_0E[];
extern FormationRow TTYD64_mim_Formation_0F[];
extern FormationRow TTYD64_mim_Formation_11[];
extern FormationRow TTYD64_mim_Formation_01[];
extern FormationRow TTYD64_mim_Formation_04[];
extern s32 TTYD64_mim_forest_fuzzy_DefaultAnims[];
extern s32 TTYD64_mim_bzzap_DefaultAnims[];
extern s32 TTYD64_mim_piranha_plant_DefaultAnims[];
extern FormationRow TTYD64_mim_Formation_0C[];
extern FormationRow TTYD64_mim_Formation_10[];
extern FormationRow TTYD64_mim_Formation_00[];
extern FormationRow TTYD64_mim_Formation_03[];
extern FormationRow TTYD64_mim_Formation_09[];
extern ActorPartBlueprint TTYD64_mim_forest_fuzzy_ActorParts[];
extern ActorPartBlueprint TTYD64_mim_piranha_plant_ActorParts[];
extern FormationRow TTYD64_mim_Formation_08[];
extern FormationRow TTYD64_mim_forest_fuzzy_CloneFormation[];

// clang-format off
EvtScript TTYD64_mim_bzzap_EVS_Attack_CallSwarm = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVarD, 0)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetPartSounds, ACTOR_SELF, 2, 1, 0, 0)
    Call(SetPartSounds, ACTOR_SELF, 3, 1, 0, 0)
    Call(SetPartSounds, ACTOR_SELF, 4, 1, 0, 0)
    Call(SetPartSounds, ACTOR_SELF, 5, 1, 0, 0)
    Call(SetPartSounds, ACTOR_SELF, 6, 1, 0, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8396)
    Call(SetActorYaw, ACTOR_SELF, 180)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4B0005)
    Wait(40)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4B0001)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(PlaySound, 856)
    Set(LVar0, 2)
    ExecGetTID(TTYD64_mim_bzzap_EVS_SummonSwarmPart, LVarA)
    Wait(11)
    Set(LVar0, 3)
    Exec(TTYD64_mim_bzzap_EVS_SummonSwarmPart)
    Wait(11)
    Set(LVar0, 4)
    Exec(TTYD64_mim_bzzap_EVS_SummonSwarmPart)
    Wait(11)
    Set(LVar0, 5)
    Exec(TTYD64_mim_bzzap_EVS_SummonSwarmPart)
    Wait(11)
    Set(LVar0, 6)
    Exec(TTYD64_mim_bzzap_EVS_SummonSwarmPart)
    Label(0)
    IsThreadRunning(LVarA, LVar0)
    Wait(1)
    IfEq(LVar0, 1)
        Goto(0)
    EndIf
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Thread
                Call(PlaySoundAtPart, ACTOR_SELF, 2, 8395)
                Call(SetAnimation, ACTOR_SELF, 2, 0x4B0004)
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(AddGoalPos, ACTOR_SELF, -30, -20, 1)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(3.0))
                Call(FlyPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, -10, 0)
                Call(SetAnimation, ACTOR_SELF, 2, 0x4B0003)
                Call(SetPartYaw, ACTOR_SELF, 2, 180)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 100)
                Add(LVar2, 100)
                Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
                Call(FlyPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, 10, 0)
                Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
                Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            EndThread
            Wait(11)
            Thread
                Call(PlaySoundAtPart, ACTOR_SELF, 3, 8395)
                Call(SetAnimation, ACTOR_SELF, 3, 0x4B0004)
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(AddGoalPos, ACTOR_SELF, -30, -20, 1)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetPartMoveSpeed, ACTOR_SELF, 3, Float(3.0))
                Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 0, -10, 0)
                Call(SetAnimation, ACTOR_SELF, 3, 0x4B0003)
                Call(SetPartYaw, ACTOR_SELF, 3, 180)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 100)
                Add(LVar2, 100)
                Call(AddActorDecoration, ACTOR_SELF, 3, 0, 2)
                Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 0, 10, 0)
                Call(RemoveActorDecoration, ACTOR_SELF, 3, 0)
                Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
            EndThread
            Wait(11)
            Thread
                Call(PlaySoundAtPart, ACTOR_SELF, 4, 8395)
                Call(SetAnimation, ACTOR_SELF, 4, 0x4B0004)
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(AddGoalPos, ACTOR_SELF, -30, -20, 1)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetPartMoveSpeed, ACTOR_SELF, 4, Float(3.0))
                Call(FlyPartTo, ACTOR_SELF, 4, LVar0, LVar1, LVar2, 0, -10, 0)
                Call(SetAnimation, ACTOR_SELF, 4, 0x4B0003)
                Call(SetPartYaw, ACTOR_SELF, 4, 180)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 100)
                Add(LVar2, 100)
                Call(AddActorDecoration, ACTOR_SELF, 4, 0, 2)
                Call(FlyPartTo, ACTOR_SELF, 4, LVar0, LVar1, LVar2, 0, 10, 0)
                Call(RemoveActorDecoration, ACTOR_SELF, 4, 0)
                Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 1)
            EndThread
            Wait(11)
            Thread
                Call(PlaySoundAtPart, ACTOR_SELF, 5, 8395)
                Call(SetAnimation, ACTOR_SELF, 5, 0x4B0004)
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(AddGoalPos, ACTOR_SELF, -30, -20, 1)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetPartMoveSpeed, ACTOR_SELF, 5, Float(3.0))
                Call(FlyPartTo, ACTOR_SELF, 5, LVar0, LVar1, LVar2, 0, -10, 0)
                Call(SetAnimation, ACTOR_SELF, 5, 0x4B0003)
                Call(SetPartYaw, ACTOR_SELF, 5, 180)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 100)
                Add(LVar2, 100)
                Call(AddActorDecoration, ACTOR_SELF, 5, 0, 2)
                Call(FlyPartTo, ACTOR_SELF, 5, LVar0, LVar1, LVar2, 0, 10, 0)
                Call(RemoveActorDecoration, ACTOR_SELF, 5, 0)
                Call(SetPartFlagBits, ACTOR_SELF, 5, 1, 1)
            EndThread
            Wait(11)
            Thread
                Call(PlaySoundAtPart, ACTOR_SELF, 6, 8395)
                Call(SetAnimation, ACTOR_SELF, 6, 0x4B0004)
                Call(SetGoalToTarget, ACTOR_SELF)
                Call(AddGoalPos, ACTOR_SELF, -30, -20, 1)
                Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(3.0))
                Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, -10, 0)
                Call(SetAnimation, ACTOR_SELF, 6, 0x4B0003)
                Call(SetPartYaw, ACTOR_SELF, 6, 180)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Add(LVar1, 100)
                Add(LVar2, 100)
                Call(AddActorDecoration, ACTOR_SELF, 6, 0, 2)
                Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 10, 0)
                Call(RemoveActorDecoration, ACTOR_SELF, 6, 0)
                Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
            EndThread
            Wait(11)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(30)
            Call(UseBattleCamPreset, 2)
            Wait(30)
            Call(StopSound, 856)
            Call(YieldTurn)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Thread
        Call(PlaySoundAtPart, ACTOR_SELF, 2, 8395)
        Call(SetAnimation, ACTOR_SELF, 2, 0x4B0004)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, -10, -10, 1)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(3.0))
        Call(FlyPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, -10, 0)
        Wait(2)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 1, 16)
        Call(SetAnimation, ACTOR_SELF, 2, 0x4B0003)
        Call(SetPartYaw, ACTOR_SELF, 2, 180)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 100)
        Add(LVar2, 100)
        Call(FlyPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 0, 10, 0)
        Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
    EndThread
    Wait(11)
    Thread
        Call(PlaySoundAtPart, ACTOR_SELF, 3, 8395)
        Call(SetAnimation, ACTOR_SELF, 3, 0x4B0004)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, -10, -10, 1)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetPartMoveSpeed, ACTOR_SELF, 3, Float(3.0))
        Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 0, -10, 0)
        Wait(2)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 1, 64)
        Call(SetAnimation, ACTOR_SELF, 3, 0x4B0003)
        Call(SetPartYaw, ACTOR_SELF, 3, 180)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 100)
        Add(LVar2, 100)
        Call(FlyPartTo, ACTOR_SELF, 3, LVar0, LVar1, LVar2, 0, 10, 0)
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    EndThread
    Wait(11)
    Thread
        Call(PlaySoundAtPart, ACTOR_SELF, 4, 8395)
        Call(SetAnimation, ACTOR_SELF, 4, 0x4B0004)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, -10, -10, 1)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetPartMoveSpeed, ACTOR_SELF, 4, Float(3.0))
        Call(FlyPartTo, ACTOR_SELF, 4, LVar0, LVar1, LVar2, 0, -10, 0)
        Wait(2)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 1, 64)
        Call(SetAnimation, ACTOR_SELF, 4, 0x4B0003)
        Call(SetPartYaw, ACTOR_SELF, 4, 180)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 100)
        Add(LVar2, 100)
        Call(FlyPartTo, ACTOR_SELF, 4, LVar0, LVar1, LVar2, 0, 10, 0)
        Call(SetPartFlagBits, ACTOR_SELF, 4, 1, 1)
    EndThread
    Wait(11)
    Thread
        Call(PlaySoundAtPart, ACTOR_SELF, 5, 8395)
        Call(SetAnimation, ACTOR_SELF, 5, 0x4B0004)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, -10, -10, 1)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(SetPartMoveSpeed, ACTOR_SELF, 5, Float(3.0))
        Call(FlyPartTo, ACTOR_SELF, 5, LVar0, LVar1, LVar2, 0, -10, 0)
        Wait(2)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 1, 64)
        Call(SetAnimation, ACTOR_SELF, 5, 0x4B0003)
        Call(SetPartYaw, ACTOR_SELF, 5, 180)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 100)
        Add(LVar2, 100)
        Call(FlyPartTo, ACTOR_SELF, 5, LVar0, LVar1, LVar2, 0, 10, 0)
        Call(SetPartFlagBits, ACTOR_SELF, 5, 1, 1)
    EndThread
    Wait(11)
    Wait(1)
    Call(PlaySoundAtPart, ACTOR_SELF, 6, 8395)
    Call(SetAnimation, ACTOR_SELF, 6, 0x4B0004)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -10, -10, 1)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetPartMoveSpeed, ACTOR_SELF, 6, Float(3.0))
    Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, -10, 0)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10002000, 0, 0, 1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetAnimation, ACTOR_SELF, 6, 0x4B0003)
            Call(SetPartYaw, ACTOR_SELF, 6, 180)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 100)
            Add(LVar2, 100)
            Call(FlyPartTo, ACTOR_SELF, 6, LVar0, LVar1, LVar2, 0, 10, 0)
            Call(SetPartFlagBits, ACTOR_SELF, 6, 1, 1)
            Call(StopSound, 856)
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
EvtScript TTYD64_mim_forest_fuzzy_EVS_Attack_Leech = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 50)
        Set(LVar1, 0)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Goto(100)
    EndIf
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0103)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 50)
    Set(LVar1, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0101)
    Label(100)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 10, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0104)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 9, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 8, 0)
    Wait(5)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 5)
            Set(LVar1, 0)
            Sub(LVar2, 5)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0105)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 11, 0, 1, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0109)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 20)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 15)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Wait(4)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2B0103)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
            ExecWait(Ref(EVS_Enemy_HopToPos))
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseEq(7)
            Call(GetStatusFlags, ACTOR_SELF, LVar0)
            IfFlag(LVar0, 8192)
                Set(LFlag0, 0)
            Else
                Set(LFlag0, 1)
            EndIf
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, -3, -12, -15)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0105)
    Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
    IfEq(LFlag0, 1)
        Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 0, 32)
        Return
    EndIf
    Wait(10)
    Call(UseIdleAnimation, LVar4, 0)
    Call(GetOwnerTarget, LVar4, 0)
    Switch(LVar4)
        CaseEq(0)
            Call(UseIdleAnimation, 0, 0)
            Call(SetAnimation, 0, 0, 0x3000C)
        CaseEq(256)
            Call(UseIdleAnimation, 256, 0)
            Set(LVar0, 4)
            Exec(TTYD64_SetPartnerAnimation_Battle)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 992)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0107)
    Wait(21)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0100)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 330)
    Call(PlaySoundAtActor, ACTOR_SELF, 992)
    Call(SetActorDispOffset, ACTOR_SELF, -3, -2, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(0.900390625), Float(1.2001953125), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(0.7998046875), Float(1.2998046875), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
    Wait(1)
    Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
    Wait(2)
    Call(SetActorScale, ACTOR_SELF, Float(0.599609375), Float(1.599609375), Float(1.0))
    Wait(10)
    Wait(2)
    Call(UseIdleAnimation, LVar4, 1)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarA, 0x8000000, 0, 0, 1, 32)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0101)
    Call(UseBattleCamPreset, 2)
    Call(GetLastDamage, LVar4, LVar3)
    IfNe(LVar3, 0)
        Call(PlaySoundAtActor, ACTOR_SELF, 8301)
        Call(PlaySoundAtActor, ACTOR_SELF, 532)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 10)
        Call(b_area_mim_forest_fuzzy_SpawnDrainHealthStartFX, LVar0, LVar1, LVar2, LVar3)
        Thread
            Wait(15)
            Call(PlaySoundAtActor, ACTOR_SELF, 604)
            Call(b_area_mim_forest_fuzzy_SpawnDrainHealthContinueFX, LVar0, LVar1, LVar2, LVar3)
        EndThread
        Add(LVar0, 20)
        Add(LVar1, 20)
        Call(PlayEffect_impl, 64, 0, LVar0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorHP, ACTOR_SELF, LVar0)
        Add(LVar0, LVar3)
        Call(SetEnemyHP, ACTOR_SELF, LVar0)
    EndIf
    Thread
        Call(SetActorScale, ACTOR_SELF, Float(1.599609375), Float(0.599609375), Float(1.0))
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
        Wait(1)
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 330)
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.5), Float(1.0))
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 300)
        Wait(1)
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 270)
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(0.7001953125), Float(1.0))
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 240)
        Wait(1)
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 210)
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(0.7001953125), Float(1.400390625), Float(1.0))
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 180)
        Wait(2)
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(0.7001953125), Float(1.0))
        Wait(2)
        Call(SetActorScale, ACTOR_SELF, Float(1.2001953125), Float(0.5), Float(1.0))
    EndThread
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 40)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.400390625), Float(0.2001953125), Float(1.0))
    Wait(1)
    Thread
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(1.2001953125), Float(0.5), Float(1.0))
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 150)
        Wait(1)
        Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 120)
        Wait(1)
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 90)
        Wait(1)
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 60)
        Wait(1)
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 30)
        Wait(1)
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
        Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
    EndThread
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
    Wait(5)
    Call(YieldTurn)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0103)
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.7998046875))
    ExecWait(Ref(EVS_Enemy_HopToPos))
    Call(SetAnimation, ACTOR_SELF, 1, 0x2B0101)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mim_piranha_plant_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x370004)
        Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
        Call(MoveBattleCamOver, 1)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 20)
        Set(LVar1, 0)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Wait(15)
        Goto(123)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 802)
    Call(SetAnimation, ACTOR_SELF, 1, 0x370004)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 1)
    Wait(8)
    Call(UseBattleCamPreset, 19)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Set(LVar1, 0)
    Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
    Call(SetBattleCamDist, 350)
    Call(SetBattleCamOffsetY, 45)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(MoveBattleCamOver, 20)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, ACTOR_SELF, LVar5)
    IfFlag(LVar5, 0x80000)
        Add(LVar0, 8)
        Add(LVar0, -3)
    Else
        Add(LVar0, 20)
    EndIf
    Set(LVar1, 0)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.0))
    Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 20, 0, 0, 0)
    Label(123)
    Call(PlaySoundAtActor, ACTOR_SELF, 801)
    Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorFlagBits, ACTOR_SELF, 4, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x370003)
    Wait(8)
    Call(SetAnimation, ACTOR_SELF, 1, 0x370005)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(GetStatusFlags, ACTOR_SELF, LVar5)
            IfNotFlag(LVar5, 0x80000)
                Call(SetAnimation, ACTOR_SELF, 1, 0x370006)
                Wait(2)
            EndIf
            Thread
                Wait(6)
                Call(PlaySoundAtActor, ACTOR_SELF, 8414)
            EndThread
            Call(SetAnimation, ACTOR_SELF, 1, 0x370007)
            Wait(10)
            Call(SetAnimation, ACTOR_SELF, 1, 0x370008)
            Wait(2)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            ExecWait(b_area_mim_piranha_plant_EVS_ReturnHome)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x370006)
    Wait(2)
    Thread
        Wait(6)
        Call(PlaySoundAtActor, ACTOR_SELF, 8414)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x370007)
    Wait(10)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, 3, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x370008)
            Wait(15)
            Call(YieldTurn)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            ExecWait(b_area_mim_piranha_plant_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mim_forest_fuzzy_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            Call(GetLastElement, LVar0)
            IfFlag(LVar0, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0113)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0108)
            EndIf
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0110)
            SetConst(LVar2, 0x2B0112)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0110)
            SetConst(LVar2, 0x2B0112)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0112)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0108)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0108)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0108)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0113)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0113)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0103)
            ExecWait(Ref(EVS_Enemy_HopHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            Call(InterruptLeechActionCommand)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0113)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0113)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0101)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            Call(GetLastElement, LVar0)
            IfFlag(LVar0, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0113)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0113)
                ExecWait(Ref(EVS_Enemy_Death))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0108)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2B0108)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0101)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0103)
            SetConst(LVar2, 0x2B0109)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0103)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0103)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2B0101)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mim_bzzap_EVS_Attack_Sting = {
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
    Call(SetAnimation, ACTOR_SELF, 1, 0x4B0003)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 52, 10, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -4, 12)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Wait(10)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Add(LVar2, 1)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
            Wait(5)
            Call(PlaySoundAtActor, ACTOR_SELF, 8394)
            Call(SetAnimation, ACTOR_SELF, 1, 0x4B0004)
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(15)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            ExecWait(b_area_mim_bzzap_EVS_ReturnHome)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Wait(10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Add(LVar2, 1)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -10, 4)
    Wait(5)
    Call(PlaySoundAtActor, ACTOR_SELF, 8394)
    Call(SetAnimation, ACTOR_SELF, 1, 0x4B0004)
    Wait(6)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, -0x7FFDFCD8, 6, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Wait(20)
            Call(YieldTurn)
            ExecWait(b_area_mim_bzzap_EVS_ReturnHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mim_bzzap_EVS_SummonSwarmPart = {
    Set(LVar9, LVar0)
    Call(SetPartYaw, ACTOR_SELF, LVar9, 0)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Add(LVarA, 200)
    Add(LVarB, 100)
    Call(SetPartPos, ACTOR_SELF, LVar9, LVarA, LVarB, LVarC)
    Call(SetPartFlagBits, ACTOR_SELF, LVar9, 1, 0)
    Call(SetAnimation, ACTOR_SELF, LVar9, 0x4B0003)
    Call(GetActorPos, ACTOR_SELF, LVarA, LVarB, LVarC)
    Add(LVarB, 50)
    Sub(LVarC, 30)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar9, Float(6.0))
    Call(SetPartJumpGravity, ACTOR_SELF, LVar9, Float(1.0))
    Call(FlyPartTo, ACTOR_SELF, LVar9, LVarA, LVarB, LVarC, 0, -10, 0)
    Call(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Call(GetPartOffset, ACTOR_SELF, LVar9, LVar6, LVar7, LVar8)
    Call(MakeLerp, 90, 450, 50, 0)
    Label(0)
    Call(UpdateLerp)
    Call(b_area_mim_bzzap_AddVecXZ, LVar3, LVar5, 30, LVar0, LVar6, LVar8)
    Call(SetPartPos, ACTOR_SELF, LVar9, LVar6, LVar7, LVar8)
    IfGt(LVar3, LVar6)
        Call(SetPartYaw, ACTOR_SELF, LVar9, 180)
    Else
        Call(SetPartYaw, ACTOR_SELF, LVar9, 0)
    EndIf
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    Call(GetOwnerTarget, LVarD, 0)
    Call(SetPartYaw, ACTOR_SELF, LVar9, 0)
    IfEq(LVar9, 2)
        Call(UseBattleCamPreset, 8)
        Call(SetBattleCamDist, 400)
        Call(SetBattleCamOffsetY, 30)
        Call(BattleCamTargetActor, LVarD)
        Call(MoveBattleCamOver, 60)
    EndIf
    Call(SetAnimation, ACTOR_SELF, LVar9, 0x4B0003)
    Call(GetActorPos, LVarD, LVarA, LVarB, LVarC)
    Add(LVarB, 30)
    Add(LVarC, 30)
    Call(SetPartMoveSpeed, ACTOR_SELF, LVar9, Float(6.0))
    Call(SetPartJumpGravity, ACTOR_SELF, LVar9, Float(1.0))
    Call(FlyPartTo, ACTOR_SELF, LVar9, LVarA, LVarB, LVarC, 0, -10, 0)
    Call(GetActorPos, LVarD, LVar3, LVar4, LVar5)
    Call(GetPartOffset, ACTOR_SELF, LVar9, LVar6, LVar7, LVar8)
    Call(MakeLerp, -90, -720, 100, 0)
    Label(1)
    Call(UpdateLerp)
    Call(b_area_mim_bzzap_AddVecXZ, LVar3, LVar5, 30, LVar0, LVar6, LVar8)
    Call(SetPartPos, ACTOR_SELF, LVar9, LVar6, LVar7, LVar8)
    IfGt(LVar3, LVar6)
        Call(SetPartYaw, ACTOR_SELF, LVar9, 180)
    Else
        Call(SetPartYaw, ACTOR_SELF, LVar9, 0)
    EndIf
    Wait(1)
    IfEq(LVar1, 1)
        Goto(1)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_mim_forest_fuzzy_EVS_Move_Clone = {
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
    Call(SummonEnemy, Ref(TTYD64_mim_forest_fuzzy_CloneFormation), 0)
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
EvtScript TTYD64_mim_forest_fuzzy_EVS_TakeTurn = {
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
                ExecWait(TTYD64_mim_forest_fuzzy_EVS_Move_Clone)
                Return
            EndIf
        CaseEq(2)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 150)
                ExecWait(TTYD64_mim_forest_fuzzy_EVS_Move_Clone)
                Return
            EndIf
        CaseEq(3)
            Call(RandInt, 1000, LVar0)
            IfLt(LVar0, 100)
                ExecWait(TTYD64_mim_forest_fuzzy_EVS_Move_Clone)
                Return
            EndIf
    EndSwitch
    ExecWait(TTYD64_mim_forest_fuzzy_EVS_Attack_Leech)
    Return
    End
};
// clang-format on

Battle TTYD64_mim_Formations[] = {
    { .name = "\260\352\374\363\301\347\355\334\363x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_mim_Formation_00,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\260\352\374\363\301\347\355\334\363x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_mim_Formation_01,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\260\352\374\363\301\347\355\334\363x4",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_mim_Formation_02,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\260\352\374\363\301\347\355\334\363,\321\303\257\363\325\351\357\374",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_mim_Formation_03,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\260\352\374\363\301\347\355\334\363x2,\321\303\257\363\325\351\357\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_mim_Formation_04,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\260\352\374\363\301\347\355\334\363x2,\321\303\257\363\325\351\357\374x2",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_mim_Formation_05,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\260\352\374\363\301\347\355\334\363x3,\321\303\257\363\325\351\357\374",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_mim_Formation_06,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\260\352\374\363\301\347\355\334\363,\321\303\257\363\325\351\357\374,"
              "\260\352\374\363\301\347\355\334\363,\321\303\257\363\325\351\357\374",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_mim_Formation_07,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\321\303\257\363\325\351\357\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_mim_Formation_08,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\321\303\257\363\325\351\357\374x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_mim_Formation_09,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\321\303\257\363\325\351\357\374x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_mim_Formation_0A,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\321\303\257\363\325\351\357\374x4",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_mim_Formation_0B,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\321\303\257\363\325\351\357\374,\260\352\374\363\301\347\355\334\363",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_mim_Formation_0C,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\321\303\257\363\325\351\357\374x2,\260\352\374\363\301\347\355\334\363",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_mim_Formation_0D,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\321\303\257\363\325\351\357\374,\260\352\374\363\301\347\355\334\363x2",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_mim_Formation_0E,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\321\303\257\363\325\351\357\374,\260\352\374\363\301\347\355\334\363,\321\303\257\363\325\351\357\374",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_mim_Formation_0F,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\317\303\301\374x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_mim_Formation_10,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    { .name = "\317\303\301\374x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_mim_Formation_11,
      .stage = &b_area_mim_mim_01,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_mim_bzzap_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mim_bzzap_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mim_bzzap_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_mim_bzzap_EVS_HandleEvent))
    Call(SetPartScale, ACTOR_SELF, 2, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Call(SetPartScale, ACTOR_SELF, 3, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Call(SetPartScale, ACTOR_SELF, 4, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Call(SetPartScale, ACTOR_SELF, 5, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Call(SetPartScale, ACTOR_SELF, 6, Float(0.400390625), Float(0.400390625), Float(0.400390625))
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_mim_bzzap_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -7, 33 },
        .opacity = 255,
        .idleAnimations = TTYD64_mim_bzzap_DefaultAnims,
        .defenseTable = b_area_mim_bzzap_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 2, -10 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_mim_bzzap_DefaultAnims,
        .defenseTable = b_area_mim_bzzap_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -5 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_mim_bzzap_DefaultAnims,
        .defenseTable = b_area_mim_bzzap_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -5 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 4,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_mim_bzzap_DefaultAnims,
        .defenseTable = b_area_mim_bzzap_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -5 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 5,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_mim_bzzap_DefaultAnims,
        .defenseTable = b_area_mim_bzzap_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -5 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x120001,
        .index = 6,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_mim_bzzap_DefaultAnims,
        .defenseTable = b_area_mim_bzzap_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { -1, -5 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_mim_forest_fuzzy_StatusTable[] = {
    1,  0, 2,  0,  6,  95, 9,  90, 7,  70, 4,  90, 3,  0, 11, 70, 5,  75, 10, 75, 8, 90,
    31, 0, 32, -1, 37, 0,  34, 0,  36, 0,  35, 0,  33, 0, 38, 0,  39, 0,  41, 0,  0,
};

s32 TTYD64_mim_bzzap_StatusTable[] = {
    1,  0, 2,  0, 6,  60, 9,  50, 7,  80, 4,  100, 3,  0, 11, 0, 5,  90, 10, 75, 8, 90,
    31, 0, 32, 0, 37, 0,  34, 0,  36, 1,  35, 0,   33, 0, 38, 0, 39, 0,  41, 0,  0,
};

s32 TTYD64_mim_piranha_plant_StatusTable[] = {
    1,  0, 2,  0, 6,  95, 9,  0, 7,  80, 4,  50, 3,  0, 11, 0, 5,  100, 10, 80, 8, 90,
    31, 0, 32, 1, 37, 0,  34, 0, 36, 0,  35, 0,  33, 0, 38, 0, 39, 0,   41, 0,  0,
};

// clang-format off
EvtScript TTYD64_mim_bzzap_EVS_TakeTurn = {
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_mim_bzzap_EVS_Attack_Sting)
        Return
    EndIf
    Call(RandInt, 1000, LVar0)
    IfLt(LVar0, 500)
        ExecWait(TTYD64_mim_bzzap_EVS_Attack_Sting)
    Else
        ExecWait(TTYD64_mim_bzzap_EVS_Attack_CallSwarm)
    EndIf
    Return
    End
};
// clang-format on

FormationRow TTYD64_mim_Formation_0B[] = {
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
};

FormationRow TTYD64_mim_Formation_05[] = {
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
};

FormationRow TTYD64_mim_Formation_02[] = {
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
};

FormationRow TTYD64_mim_Formation_06[] = {
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
};

FormationRow TTYD64_mim_Formation_07[] = {
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
};

// clang-format off
EvtScript TTYD64_mim_forest_fuzzy_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mim_forest_fuzzy_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mim_piranha_plant_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_mim_forest_fuzzy_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_mim_Formation_0A[] = {
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
};

FormationRow TTYD64_mim_Formation_0D[] = {
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
};

FormationRow TTYD64_mim_Formation_0E[] = {
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
};

FormationRow TTYD64_mim_Formation_0F[] = {
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
};

FormationRow TTYD64_mim_Formation_11[] = {
    { .actor = &TTYD64_mim_bzzap,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_mim_bzzap,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_mim_bzzap,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
};

FormationRow TTYD64_mim_Formation_01[] = {
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
};

FormationRow TTYD64_mim_Formation_04[] = {
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
};

s32 TTYD64_mim_forest_fuzzy_DefaultAnims[] = {
    1,  0x2B0101, 7, 0x2B0100, 6, 0x2B010E, 9, 0x2B0101, 8, 0x2B0100,
    11, 0x2B0101, 5, 0x2B0100, 4, 0x2B010F, 3, 0x2B010F, 0,
};

s32 TTYD64_mim_bzzap_DefaultAnims[] = {
    1,  0x4B0001, 7, 0x4B0000, 6, 0x4B0009, 9, 0x4B0001, 8, 0x4B0000,
    11, 0x4B0001, 5, 0x4B0000, 4, 0x4B000A, 3, 0x4B000A, 0,
};

s32 TTYD64_mim_piranha_plant_DefaultAnims[] = {
    1,  0x370001, 7, 0x370000, 6, 0x370000, 9, 0x370001, 8, 0x370000,
    11, 0x370001, 5, 0x370000, 4, 0x370001, 3, 0x370001, 0,
};

// clang-format off
EvtScript TTYD64_mim_piranha_plant_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_mim_piranha_plant_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_mim_piranha_plant_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_mim_piranha_plant_EVS_HandleEvent))
    Return
    End
};
// clang-format on

FormationRow TTYD64_mim_Formation_0C[] = {
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
};

FormationRow TTYD64_mim_Formation_10[] = {
    { .actor = &TTYD64_mim_bzzap,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
    { .actor = &TTYD64_mim_bzzap,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BZZAP },
};

FormationRow TTYD64_mim_Formation_00[] = {
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
};

FormationRow TTYD64_mim_Formation_03[] = {
    { .actor = &TTYD64_mim_forest_fuzzy,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_FORESTFUZZY },
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
};

FormationRow TTYD64_mim_Formation_09[] = {
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
};

ActorBlueprint TTYD64_mim_forest_fuzzy = {
    .flags = 0x0,
    .maxHP = 6,
    .type = 0x1A,
    .level = 11,
    .partCount = 1,
    .partsData = TTYD64_mim_forest_fuzzy_ActorParts,
    .initScript = &TTYD64_mim_forest_fuzzy_EVS_Init,
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

ActorBlueprint TTYD64_mim_bzzap = {
    .flags = 0x200,
    .maxHP = 3,
    .type = 0x31,
    .level = 19,
    .partCount = 6,
    .partsData = TTYD64_mim_bzzap_ActorParts,
    .initScript = &TTYD64_mim_bzzap_EVS_Init,
    .statusTable = TTYD64_mim_bzzap_StatusTable,
    .escapeChance = 40,
    .airLiftChance = 95,
    .hurricaneChance = 95,
    .spookChance = 70,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 38, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_mim_forest_fuzzy_8021EC2C = {
    .flags = 0x0,
    .maxHP = 6,
    .type = 0x1A,
    .level = 11,
    .partCount = 1,
    .partsData = TTYD64_mim_forest_fuzzy_ActorParts,
    .initScript = &TTYD64_mim_forest_fuzzy_EVS_Init,
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

ActorBlueprint TTYD64_mim_piranha_plant = {
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

ActorPartBlueprint TTYD64_mim_forest_fuzzy_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = TTYD64_mim_forest_fuzzy_DefaultAnims,
        .defenseTable = b_area_mim_piranha_plant_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_mim_piranha_plant_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 35 },
        .opacity = 255,
        .idleAnimations = TTYD64_mim_piranha_plant_DefaultAnims,
        .defenseTable = b_area_mim_piranha_plant_DefenseTable,
        .eventFlags = 0x10,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_mim_Formation_08[] = {
    { .actor = &TTYD64_mim_piranha_plant,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PIRANHAPLANT },
};

FormationRow TTYD64_mim_forest_fuzzy_CloneFormation[] = {
    { .actor = &TTYD64_mim_forest_fuzzy_8021EC2C,
      .home = { .vec = &b_area_mim_forest_fuzzy_SummonPos },
      .priority = 0,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

void TTYD64_InstallBattles_mim(void) {
    Mod_SetBattleList("TTYD64", 13, TTYD64_mim_Formations);
}
