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
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(CopyBuffs);
API_CALLABLE(CopyStatusEffects);
API_CALLABLE(DispatchEvent);
API_CALLABLE(EnableActorPaletteEffects);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FlyToGoal);
API_CALLABLE(ForceHomePos);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetDamageSource);
API_CALLABLE(GetEncounterTrigger);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetIndexFromHome);
API_CALLABLE(GetLastDamage);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToCurrent);
API_CALLABLE(HPBarToHome);
API_CALLABLE(HideHealthBar);
API_CALLABLE(IdleFlyToGoal);
API_CALLABLE(IdleRunToGoal);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlayLoopingSoundAtActor);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActor);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(ResetActorSounds);
API_CALLABLE(ResetAllActorSounds);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorFlagBits);
API_CALLABLE(SetActorIdleSpeed);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorPaletteEffect);
API_CALLABLE(SetActorPaletteSwapParams);
API_CALLABLE(SetActorPos);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorType);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetAnimationRate);
API_CALLABLE(SetBattleCamDist);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetDefenseTable);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToIndex);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetHomePos);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetIdleGoal);
API_CALLABLE(SetPartDispOffset);
API_CALLABLE(SetPartEventBits);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartFlags);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartYaw);
API_CALLABLE(SetProjectileTargetOffset);
API_CALLABLE(SetStatusTable);
API_CALLABLE(SetTargetActor);
API_CALLABLE(SetTargetOffset);
API_CALLABLE(ShakeCam);
API_CALLABLE(StartRumble);
API_CALLABLE(StopLoopingSoundAtActor);
API_CALLABLE(SummonEnemy);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseBattleCamPresetImmediately);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
API_CALLABLE(b_area_trd_part_1_paratroopa_StartRumbleWithParams);
extern Vec3i b_area_trd_part_1_BlasterPos1;
extern Vec3i b_area_trd_part_1_BlasterPos2;
extern Vec3i b_area_trd_part_1_BlasterPos3;
extern s32 b_area_trd_part_1_bill_blaster_DefenseTable[];
extern EvtScript b_area_trd_part_1_bill_blaster_EVS_HandleEvent;
extern EvtScript b_area_trd_part_1_bill_blaster_EVS_Idle;
extern EvtScript b_area_trd_part_1_bill_blaster_EVS_Move_CheckForBullet;
extern s32 b_area_trd_part_1_bill_blaster_StatusTable[];
extern Vec3i b_area_trd_part_1_bill_blaster_SummonPos;
extern s32 b_area_trd_part_1_bob_omb_DefenseTable[];
extern EvtScript b_area_trd_part_1_bob_omb_EVS_Cleanup;
extern EvtScript b_area_trd_part_1_bob_omb_EVS_Explode;
extern EvtScript b_area_trd_part_1_bob_omb_EVS_Idle;
extern s32 b_area_trd_part_1_bob_omb_IgnitedStatusTable[];
extern s32 b_area_trd_part_1_bob_omb_StatusTable[];
extern s32 b_area_trd_part_1_bullet_bill_DefenseTable[];
extern EvtScript b_area_trd_part_1_bullet_bill_EVS_HandleEvent;
extern EvtScript b_area_trd_part_1_bullet_bill_EVS_Idle;
extern EvtScript b_area_trd_part_1_bullet_bill_EVS_MakeExplosionFX;
extern s32 b_area_trd_part_1_bullet_bill_StatusTable[];
extern EvtScript b_area_trd_part_1_koopa_troopa_EVS_UpdateTargetOffsets;
extern EvtScript b_area_trd_part_1_koopa_troopa_FlipPosOffsets;
extern s32 b_area_trd_part_1_koopa_troopa_FlippedDefense[];
extern s32 b_area_trd_part_1_koopa_troopa_StatusTable[];
extern s32 b_area_trd_part_1_paratroopa_DownedDefense[];
extern s32 b_area_trd_part_1_paratroopa_DownedStatusTable[];
extern EvtScript b_area_trd_part_1_paratroopa_EVS_Downed_UpdateTargetOffsets;
extern EvtScript b_area_trd_part_1_paratroopa_EVS_FlyHome;
extern EvtScript b_area_trd_part_1_paratroopa_EVS_Flying_HandlePhase;
extern EvtScript b_area_trd_part_1_paratroopa_EVS_Flying_UpdateTargetOffsets;
extern u8 b_area_trd_part_1_paratroopa_FlipPosOffsets[];
extern s32 b_area_trd_part_1_paratroopa_FlippedDefense[];
extern s32 b_area_trd_part_1_paratroopa_FlyingDefense[];
extern s32 b_area_trd_part_1_paratroopa_FlyingStatusTable[];
extern Stage b_area_trd_part_1_trd_01;
extern EvtScript TTYD64_trd_part_1_paratroopa_EVS_Downed_TakeTurn;
extern EvtScript TTYD64_trd_part_1_koopa_troopa_EVS_TakeTurn;
extern EvtScript TTYD64_trd_part_1_paratroopa_EVS_Downed_HandleEvent;
extern EvtScript TTYD64_trd_part_1_koopa_troopa_EVS_HandleEvent;
extern EvtScript TTYD64_trd_part_1_paratroopa_EVS_Flying_TakeTurn;
extern EvtScript TTYD64_trd_part_1_bob_omb_EVS_Attack_Tackle;
extern EvtScript TTYD64_trd_part_1_bob_omb_EVS_HandleEvent;
extern EvtScript TTYD64_trd_part_1_paratroopa_EVS_Flying_HandleEvent;
extern EvtScript TTYD64_trd_part_1_bob_omb_EVS_HandleEvent_Ignited;
extern EvtScript TTYD64_trd_part_1_paratroopa_EVS_KnockDown;
extern EvtScript TTYD64_trd_part_1_bob_omb_EVS_Attack_Blast;
extern EvtScript TTYD64_trd_part_1_koopa_troopa_EVS_Idle;
extern EvtScript TTYD64_trd_part_1_paratroopa_EVS_Downed_Idle;
extern EvtScript TTYD64_trd_part_1_bullet_bill_EVS_TakeTurn;
extern EvtScript TTYD64_trd_part_1_paratroopa_EVS_Flying_Idle;
extern EvtScript TTYD64_trd_part_1_bullet_bill_EVS_Init;
extern EvtScript TTYD64_trd_part_1_bob_omb_EVS_Ignite;
extern EvtScript TTYD64_trd_part_1_bill_blaster_EVS_Move_FireBullet;
extern EvtScript TTYD64_trd_part_1_bob_omb_EVS_Defuse;
extern EvtScript TTYD64_trd_part_1_bill_blaster_EVS_TakeTurn;
extern EvtScript TTYD64_trd_part_1_bob_omb_EVS_TakeTurn;
extern EvtScript TTYD64_trd_part_1_paratroopa_EVS_Flying_Init;
extern EvtScript TTYD64_trd_part_1_paratroopa_EVS_Flying_Init_8022662C;
extern EvtScript TTYD64_trd_part_1_bill_blaster_EVS_Init;
extern EvtScript TTYD64_trd_part_1_paratroopa_EVS_Downed_Init;
extern EvtScript TTYD64_trd_part_1_koopa_troopa_EVS_Init;
extern ActorBlueprint TTYD64_trd_part_1_bob_omb;
extern ActorBlueprint TTYD64_trd_part_1_bullet_bill;
extern ActorBlueprint TTYD64_trd_part_1_koopa_troopa;
extern ActorBlueprint TTYD64_trd_part_1_bullet_bill_80227894;
extern ActorBlueprint TTYD64_trd_part_1_paratroopa;
extern ActorBlueprint TTYD64_trd_part_1_bill_blaster;
extern Battle TTYD64_trd_part_1_Formations[];
extern FormationRow TTYD64_trd_part_1_Formation_0E[];
extern FormationRow TTYD64_trd_part_1_Formation_0C[];
extern FormationRow TTYD64_trd_part_1_Formation_12[];
extern FormationRow TTYD64_trd_part_1_Formation_05[];
extern FormationRow TTYD64_trd_part_1_Formation_07[];
extern ActorPartBlueprint TTYD64_trd_part_1_paratroopa_ActorParts[];
extern FormationRow TTYD64_trd_part_1_Formation_0D[];
extern FormationRow TTYD64_trd_part_1_Formation_0B[];
extern FormationRow TTYD64_trd_part_1_Formation_11[];
extern FormationRow TTYD64_trd_part_1_Formation_15[];
extern FormationRow TTYD64_trd_part_1_Formation_16[];
extern FormationRow TTYD64_trd_part_1_Formation_14[];
extern FormationRow TTYD64_trd_part_1_Formation_17[];
extern FormationRow TTYD64_trd_part_1_Formation_04[];
extern FormationRow TTYD64_trd_part_1_Formation_02[];
extern FormationRow TTYD64_trd_part_1_Formation_09[];
extern FormationRow TTYD64_trd_part_1_Formation_06[];
extern FormationRow TTYD64_trd_part_1_Formation_1A[];
extern s32 TTYD64_trd_part_1_paratroopa_DownedFlippedAnims[];
extern s32 TTYD64_trd_part_1_bob_omb_IgnitedAnims[];
extern s32 TTYD64_trd_part_1_paratroopa_FlyingShuffleAnims[];
extern s32 TTYD64_trd_part_1_paratroopa_DownedShuffleAnims[];
extern s32 TTYD64_trd_part_1_koopa_troopa_FlippedAnims[];
extern s32 TTYD64_trd_part_1_paratroopa_DownedAnims[];
extern s32 TTYD64_trd_part_1_paratroopa_WingAnims[];
extern s32 TTYD64_trd_part_1_koopa_troopa_ShuffleAnims[];
extern s32 TTYD64_trd_part_1_paratroopa_DownedAnims_80227358[];
extern s32 TTYD64_trd_part_1_bob_omb_DefaultAnims[];
extern s32 TTYD64_trd_part_1_paratroopa_FlyingAnims[];
extern ActorPartBlueprint TTYD64_trd_part_1_bill_blaster_ActorParts[];
extern FormationRow TTYD64_trd_part_1_Formation_0A[];
extern FormationRow TTYD64_trd_part_1_Formation_10[];
extern FormationRow TTYD64_trd_part_1_Formation_13[];
extern FormationRow TTYD64_trd_part_1_Formation_18[];
extern FormationRow TTYD64_trd_part_1_Formation_01[];
extern FormationRow TTYD64_trd_part_1_Formation_03[];
extern FormationRow TTYD64_trd_part_1_Formation_08[];
extern ActorPartBlueprint TTYD64_trd_part_1_bullet_bill_ActorParts[];
extern s32 TTYD64_trd_part_1_bullet_bill_DefaultAnims[];
extern ActorPartBlueprint TTYD64_trd_part_1_bob_omb_ActorParts[];
extern ActorPartBlueprint TTYD64_trd_part_1_koopa_troopa_ActorParts[];
extern s32 TTYD64_trd_part_1_bill_blaster_DefaultAnims[];
extern FormationRow TTYD64_trd_part_1_bill_blaster_BulletFormation[];
extern FormationRow TTYD64_trd_part_1_Formation_0F[];
extern FormationRow TTYD64_trd_part_1_Formation_19[];
extern FormationRow TTYD64_trd_part_1_Formation_00[];

static API_CALLABLE(TTYD64_trd_part_1_bill_blaster_SetBulletInitVars) {
    TTYD64_trd_part_1_bill_blaster_BulletFormation[0].var0 = true;
    TTYD64_trd_part_1_bill_blaster_BulletFormation[0].var1 = script->owner1.actorID;

    return ApiStatus_DONE2;
}

// clang-format off
EvtScript TTYD64_trd_part_1_paratroopa_EVS_Downed_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290106)
    Else
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        IfEq(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 9, LVar0)
            Sub(LVar0, 1)
            IfGt(LVar0, 0)
                Call(SetActorVar, ACTOR_SELF, 9, LVar0)
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
                Wait(30)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Else
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
                Wait(20)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8321)
                Call(SetAnimation, ACTOR_SELF, 1, 0x29010F)
                Set(LVar0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
                ChildThread
                    Loop(5)
                        Add(LVar0, 15)
                        Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                        Wait(1)
                    EndLoop
                EndChildThread
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
                Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8378)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x290101)
                Call(SetActorVar, ACTOR_SELF, 8, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_paratroopa_DownedAnims))
                Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_1_paratroopa_DownedDefense))
                Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
                Call(SetTargetOffset, ACTOR_SELF, 1, -4, 32)
                Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -4)
                Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
                Call(ResetActorSounds, ACTOR_SELF, 2)
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndIf
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290107)
        Wait(10)
        ChildThread
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 4)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            Wait(3)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            Wait(2)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        EndChildThread
        Call(PlaySoundAtActor, ACTOR_SELF, 8225)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290106)
        Wait(10)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -40, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(UseBattleCamPreset, 5)
                Call(SetBattleCamDist, 300)
                Call(SetBattleCamOffsetY, 20)
                Call(MoveBattleCamOver, 10)
                Call(SetBattleCamTargetingModes, -1, 1, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x290108)
            Wait(8)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Wait(4)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x290115)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290116)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290117)
            Wait(6)
            Sub(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290117)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290101)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetPartYaw, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x290108)
            Wait(8)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x290104)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x290101)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_koopa_troopa_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetBattlePhase, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290106)
    Else
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        IfEq(LVar0, 1)
            Call(GetActorVar, ACTOR_SELF, 9, LVar0)
            Sub(LVar0, 1)
            IfGt(LVar0, 0)
                Call(SetActorVar, ACTOR_SELF, 9, LVar0)
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
                Wait(30)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Else
                Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(3.0))
                Wait(20)
                Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
                Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
                Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8321)
                Call(SetAnimation, ACTOR_SELF, 1, 0x29010F)
                Set(LVar0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
                ChildThread
                    Loop(5)
                        Add(LVar0, 15)
                        Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                        Wait(1)
                    EndLoop
                EndChildThread
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
                Call(JumpToGoal, ACTOR_SELF, 8, 0, 1, 0)
                Call(PlaySoundAtActor, ACTOR_SELF, 8378)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
                Call(SetAnimation, ACTOR_SELF, 1, 0x290101)
                Call(SetActorVar, ACTOR_SELF, 8, 0)
                Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_paratroopa_DownedAnims_80227358))
                Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_1_paratroopa_DownedDefense))
                Call(TTYD64_SetActorExtraData, ACTOR_SELF, 12, 0)
                Call(SetTargetOffset, ACTOR_SELF, 1, -4, 32)
                Call(SetProjectileTargetOffset, ACTOR_SELF, 1, -1, -4)
                Call(SetActorFlagBits, ACTOR_SELF, 1024, 0)
                Call(ResetActorSounds, ACTOR_SELF, 2)
            EndIf
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndIf
        Call(UseBattleCamPreset, 63)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Wait(10)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290107)
        Wait(10)
        ChildThread
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 4)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            Wait(3)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
            Wait(2)
            Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 32, 4, 0, 10, 0, 0, 0, 0, 0)
        EndChildThread
        Call(PlaySoundAtActor, ACTOR_SELF, 8225)
        Call(SetAnimation, ACTOR_SELF, 1, 0x290106)
        Wait(10)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_SELF, 8403)
    Call(SetActorSounds, ACTOR_SELF, 0, 0, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, -40, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(UseBattleCamPreset, 5)
                Call(SetBattleCamDist, 300)
                Call(SetBattleCamOffsetY, 20)
                Call(MoveBattleCamOver, 10)
                Call(SetBattleCamTargetingModes, -1, 1, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x290108)
            Wait(8)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Wait(4)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x290115)
            Wait(1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290116)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290117)
            Wait(6)
            Sub(LVar1, 20)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290117)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x290101)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetPartYaw, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(16.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(ResetAllActorSounds, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x290108)
            Wait(8)
            Call(YieldTurn)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x290104)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetAnimation, ACTOR_SELF, 1, 0x290101)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_paratroopa_EVS_Downed_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010C)
            SetConst(LVar2, 0x29010D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010C)
            SetConst(LVar2, 0x29010D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010D)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 8, 1)
            Call(SetActorVar, ACTOR_SELF, 9, 2)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_1_paratroopa_FlippedDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_paratroopa_DownedFlippedAnims))
            Call(SetTargetOffset, ACTOR_SELF, 1, -5, 15)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, 0)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x29010B)
            Call(GetStatusFlags, ACTOR_SELF, LVarA)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            ChildThread
                Wait(4)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -60)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -75)
                Wait(1)
            EndChildThread
            UseBuf(Ref(b_area_trd_part_1_paratroopa_FlipPosOffsets))
            Loop(22)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x29010F)
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x290104)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290107)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(GetStatusFlags, ACTOR_SELF, LVar0)
                IfNotFlag(LVar0, 0x35D000)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x290108)
                    Wait(10)
                EndIf
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290104)
                ExecWait(Ref(EVS_Enemy_ReturnHome))
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290101)
                ExecWait(Ref(EVS_Enemy_Recover))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290104)
                SetConst(LVar2, 0x29010B)
                ExecWait(Ref(EVS_Enemy_ScareAway))
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290117)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
            EndIf
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290117)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
            EndIf
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290101)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_koopa_troopa_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010C)
            SetConst(LVar2, 0x29010D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010C)
            SetConst(LVar2, 0x29010D)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010D)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(13)
            Call(SetActorVar, ACTOR_SELF, 8, 1)
            Call(SetActorVar, ACTOR_SELF, 9, 2)
            Call(SetDefenseTable, ACTOR_SELF, 1, Ref(b_area_trd_part_1_koopa_troopa_FlippedDefense))
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_koopa_troopa_FlippedAnims))
            Call(SetTargetOffset, ACTOR_SELF, 1, -5, 15)
            Call(SetProjectileTargetOffset, ACTOR_SELF, 1, 0, 0)
            Call(SetActorFlagBits, ACTOR_SELF, 1024, 1)
            Call(SetAnimation, ACTOR_SELF, 1, 0x29010B)
            Call(GetStatusFlags, ACTOR_SELF, LVarA)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 12, 0)
            ChildThread
                Wait(4)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -30)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -60)
                Wait(1)
                Call(SetActorRotation, ACTOR_SELF, 0, 0, -75)
                Wait(1)
            EndChildThread
            UseBuf(Ref(b_area_trd_part_1_koopa_troopa_FlipPosOffsets))
            Loop(22)
                BufRead1(LVar0)
                Call(SetActorDispOffset, ACTOR_SELF, 0, LVar0, 0)
                Wait(1)
            EndLoop
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x29010F)
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x290104)
            ExecWait(Ref(EVS_Enemy_ReturnHome))
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(23)
        CaseOrEq(25)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290107)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
                Call(GetStatusFlags, ACTOR_SELF, LVar0)
                IfNotFlag(LVar0, 0x35D000)
                    Call(SetAnimation, ACTOR_SELF, 1, 0x290108)
                    Wait(10)
                EndIf
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x29010B)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290104)
                ExecWait(Ref(EVS_Enemy_ReturnHome))
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290101)
                ExecWait(Ref(EVS_Enemy_Recover))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(57)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290104)
                SetConst(LVar2, 0x29010B)
                ExecWait(Ref(EVS_Enemy_ScareAway))
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
        CaseEq(58)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290117)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
            EndIf
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290117)
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
            EndIf
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(31)
            Call(GetActorVar, ACTOR_SELF, 8, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x290101)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x29010F)
                ExecWait(Ref(EVS_Enemy_NoDamageHit))
            EndIf
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_paratroopa_EVS_Flying_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 30)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVar1, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 5)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetTargetActor, ACTOR_SELF, LVar1)
    Call(SetAnimation, ACTOR_SELF, 2, 0x2A0103)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 40, 30, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(7.0))
    Call(FlyToGoal, ACTOR_SELF, 0, -16, 0)
    Call(UseBattleCamPresetImmediately, 1)
    Wait(5)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(PlaySoundAtActor, ACTOR_SELF, 8416)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 2, 0x2A0104)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(AddGoalPos, ACTOR_SELF, 6, 6, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
            Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
            Wait(6)
            Call(PlaySoundAtActor, ACTOR_SELF, 705)
            Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
            Call(GetOwnerTarget, LVar3, 0)
            Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
            Sub(LVar0, 25)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x2A010C)
            Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(4.0))
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
                Set(LVar0, 0)
                Loop(8)
                    Add(LVar0, 90)
                    IfGe(LVar0, 360)
                        Sub(LVar0, 360)
                    EndIf
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, -10, 0)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x2A0107)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x2A0107)
            Call(JumpToGoal, ACTOR_SELF, 6, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar1, 30)
            Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Wait(20)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            Call(AddActorDecoration, ACTOR_SELF, 2, 0, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            ExecWait(b_area_trd_part_1_paratroopa_EVS_FlyHome)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 2, 0)
            Call(EnableIdleScript, ACTOR_SELF, -1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_SELF, 8416)
    Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 2, 0x2A0104)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(AddGoalPos, ACTOR_SELF, 6, 6, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
    Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
    Wait(6)
    Call(PlaySoundAtActor, ACTOR_SELF, 705)
    Call(SetActorSounds, ACTOR_SELF, 1, 0, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorSpeed, ACTOR_SELF, Float(10.0))
    Call(SetAnimation, ACTOR_SELF, 2, 0x2A010C)
    Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 2, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 40, 30, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
            Call(SetAnimation, ACTOR_SELF, 2, 0x2A010D)
            Thread
                Call(SetActorRotationOffset, ACTOR_SELF, 0, 10, 0)
                Set(LVar0, 0)
                Loop(12)
                    Sub(LVar0, 90)
                    IfLt(LVar0, 0)
                        Add(LVar0, 360)
                    EndIf
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
                Call(SetActorRotationOffset, ACTOR_SELF, 0, -10, 0)
                Call(SetAnimation, ACTOR_SELF, 2, 0x2A0101)
            EndThread
            Call(FlyToGoal, ACTOR_SELF, 0, 30, 0)
            Wait(10)
            Call(YieldTurn)
            Call(ResetAllActorSounds, ACTOR_SELF)
            ExecWait(b_area_trd_part_1_paratroopa_EVS_FlyHome)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_bob_omb_EVS_Attack_Tackle = {
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 40)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
    Else
        Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    EndIf
    Call(GetOwnerTarget, LVar1, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetTargetActor, ACTOR_SELF, LVar1)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2C0006)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2C0002)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2C0006)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 5)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.099609375))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2C001C)
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
            Wait(8)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(YieldTurn)
            Call(UseBattleCamPreset, 2)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2C0006)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2C0002)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(SetActorYaw, ACTOR_SELF, 0)
            Return
        EndCaseGroup
        CaseEq(7)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.099609375))
            Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2C0014)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(GetActorSize, ACTOR_SELF, LVar3, LVar4)
            Call(PlayEffect_impl, 74, 0, LVar0, LVar1, LVar2, LVar4, LVar3, 0, 0, 0, 0, 0, 0, 0)
            Call(PlaySoundAtActor, ACTOR_SELF, 891)
            Wait(20)
            ExecWait(b_area_trd_part_1_bob_omb_EVS_Explode)
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 512, 0, 0, 3, 32)
            Return
    EndSwitch
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(1.099609375))
    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 1, 32)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2C0002)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
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
            Wait(4)
            Call(YieldTurn)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2C0006)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2C0002)
        EndCaseGroup
    EndSwitch
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_bob_omb_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Call(GetLastDamage, ACTOR_SELF, LVar0)
            IfNe(LVar0, 0)
                Call(SetActorVar, ACTOR_SELF, 0, 1)
            EndIf
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C000E)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            Call(GetLastElement, LVarE)
            IfFlag(LVarE, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2C0010)
                SetConst(LVar2, 0x2C0011)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                ExecWait(b_area_trd_part_1_bob_omb_EVS_Explode)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2C0011)
                Set(LVar2, -0x3039)
                ExecWait(Ref(EVS_Enemy_Death))
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2C000E)
                ExecWait(Ref(EVS_Enemy_Hit))
                Call(GetLastDamage, ACTOR_SELF, LVar0)
                IfNe(LVar0, 0)
                    ExecWait(TTYD64_trd_part_1_bob_omb_EVS_Ignite)
                EndIf
            EndIf
        CaseOrEq(14)
        CaseOrEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C0010)
            SetConst(LVar2, 0x2C0011)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_trd_part_1_bob_omb_EVS_Explode)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C0011)
            Set(LVar2, -0x3039)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        EndCaseGroup
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C000E)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            Call(GetLastDamage, ACTOR_SELF, LVar0)
            IfNe(LVar0, 0)
                ExecWait(TTYD64_trd_part_1_bob_omb_EVS_Ignite)
            EndIf
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C000E)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            ExecWait(b_area_trd_part_1_bob_omb_EVS_Cleanup)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C000E)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(47)
        CaseOrEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C0010)
            Set(LVar2, -0x3039)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C0002)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C0002)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Call(GetActorVar, ACTOR_SELF, 0, LVar0)
            IfEq(LVar0, 1)
                ExecWait(TTYD64_trd_part_1_bob_omb_EVS_Ignite)
            EndIf
        EndCaseGroup
        CaseEq(32)
            Call(GetLastElement, LVarE)
            IfFlag(LVarE, 32)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2C0010)
                SetConst(LVar2, 0x2C0011)
                ExecWait(Ref(EVS_Enemy_BurnHit))
                ExecWait(b_area_trd_part_1_bob_omb_EVS_Explode)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2C0011)
                Set(LVar2, -0x3039)
                ExecWait(Ref(EVS_Enemy_Death))
                Return
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2C000E)
                ExecWait(Ref(EVS_Enemy_Hit))
                Wait(10)
                ExecWait(b_area_trd_part_1_bob_omb_EVS_Cleanup)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2C000E)
                ExecWait(Ref(EVS_Enemy_Death))
            EndIf
            Return
        CaseEq(34)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C0010)
            SetConst(LVar2, 0x2C0011)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(b_area_trd_part_1_bob_omb_EVS_Explode)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C0011)
            Set(LVar2, -0x3039)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C0002)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C0006)
            SetConst(LVar2, 0x2C000E)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C001C)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C001C)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_paratroopa_EVS_Flying_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_Hit))
        CaseEq(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_Hit))
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(GetEncounterTrigger, LVar0)
                IfEq(LVar0, 4)
                    ExecWait(TTYD64_trd_part_1_paratroopa_EVS_KnockDown)
                EndIf
            EndIf
        CaseEq(11)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0106)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(14)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0108)
            SetConst(LVar2, 0x2A0109)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0108)
            SetConst(LVar2, 0x2A0109)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0109)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(12)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_Hit))
            ExecWait(TTYD64_trd_part_1_paratroopa_EVS_KnockDown)
        CaseEq(15)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2A0108)
            SetConst(LVar1, 0x2A0109)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            ExecWait(TTYD64_trd_part_1_paratroopa_EVS_KnockDown)
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2A0106)
            ExecWait(Ref(EVS_Enemy_Knockback))
            ExecWait(b_area_trd_part_1_paratroopa_EVS_FlyHome)
        CaseEq(38)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0106)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(23)
            Call(SetActorVar, ACTOR_SELF, 0, 1)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A010B)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A010B)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
            Call(GetBattlePhase, LVar0)
            IfEq(LVar0, 1)
                Call(GetEncounterTrigger, LVar0)
                IfEq(LVar0, 4)
                    ExecWait(TTYD64_trd_part_1_paratroopa_EVS_KnockDown)
                EndIf
            EndIf
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0106)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(56)
            Call(SetActorPos, ACTOR_SELF, 20, 0, 0)
            Call(HPBarToCurrent, ACTOR_SELF)
        CaseEq(53)
            ExecWait(b_area_trd_part_1_paratroopa_EVS_FlyHome)
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0101)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0103)
            SetConst(LVar2, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0103)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 2)
            SetConst(LVar1, 0x2A0107)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, -1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_bob_omb_EVS_HandleEvent_Ignited = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(9)
            Call(GetLastElement, LVarE)
            IfFlag(LVarE, 4)
                ExecWait(TTYD64_trd_part_1_bob_omb_EVS_Defuse)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2C000E)
                ExecWait(Ref(EVS_Enemy_Hit))
            Else
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2C000F)
                ExecWait(Ref(EVS_Enemy_Hit))
            EndIf
        CaseEq(10)
            Call(GetLastElement, LVarE)
            Switch(LVarE)
                CaseFlag(4)
                    ExecWait(TTYD64_trd_part_1_bob_omb_EVS_Defuse)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x2C000E)
                    ExecWait(Ref(EVS_Enemy_Hit))
                CaseFlag(32)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x2C0010)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    ExecWait(b_area_trd_part_1_bob_omb_EVS_Explode)
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x2C0011)
                    Set(LVar2, -0x3039)
                    ExecWait(Ref(EVS_Enemy_Death))
                    Return
                CaseDefault
                    SetConst(LVar0, 1)
                    SetConst(LVar1, 0x2C000F)
                    ExecWait(Ref(EVS_Enemy_Hit))
                    Call(GetLastDamage, ACTOR_SELF, LVar0)
                    IfGt(LVar0, 0)
                        ExecWait(b_area_trd_part_1_bob_omb_EVS_Explode)
                        SetConst(LVar0, 1)
                        SetConst(LVar1, 0x2C0011)
                        Set(LVar2, -0x3039)
                        ExecWait(Ref(EVS_Enemy_Death))
                        Return
                    EndIf
            EndSwitch
        CaseOrEq(14)
        CaseOrEq(36)
        CaseOrEq(11)
        CaseOrEq(33)
        CaseOrEq(34)
            ExecWait(b_area_trd_part_1_bob_omb_EVS_Explode)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C0011)
            Set(LVar2, -0x3039)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        EndCaseGroup
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C0003)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            Call(GetLastElement, LVarE)
            IfFlag(LVarE, 4)
                ExecWait(TTYD64_trd_part_1_bob_omb_EVS_Defuse)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2C000E)
            Else
                ExecWait(b_area_trd_part_1_bob_omb_EVS_Explode)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2C0011)
                Set(LVar2, -0x3039)
            EndIf
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseOrEq(47)
        CaseOrEq(38)
            ExecWait(b_area_trd_part_1_bob_omb_EVS_Explode)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C0011)
            Set(LVar2, -0x3039)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        EndCaseGroup
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C0003)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            ExecWait(b_area_trd_part_1_bob_omb_EVS_Cleanup)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C0006)
            SetConst(LVar2, 0x2C000E)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x2C001D)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            Call(GetDamageSource, LVar0)
            IfEq(LVar0, 20)
                ExecWait(TTYD64_trd_part_1_bob_omb_EVS_Defuse)
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2C001C)
            Else
                ChildThread
                    Wait(100)
                    ExecWait(b_area_trd_part_1_bob_omb_EVS_Explode)
                EndChildThread
                SetConst(LVar0, 1)
                SetConst(LVar1, 0x2C001D)
            EndIf
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseEq(61)
            ExecWait(TTYD64_trd_part_1_bob_omb_EVS_Defuse)
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_paratroopa_EVS_KnockDown = {
    Call(SetPartDispOffset, ACTOR_SELF, 2, 0, 0, 0)
    Call(HideHealthBar, ACTOR_SELF)
    Call(SetPartFlags, ACTOR_SELF, 2, 0x20005)
    Call(SetPartFlags, ACTOR_SELF, 3, 0x120004)
    Call(SetPartFlags, ACTOR_SELF, 1, 0x800004)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 8)
    Sub(LVar2, 2)
    Call(SetPartPos, ACTOR_SELF, 3, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x29010B)
    Call(SetActorSounds, ACTOR_SELF, 2, 769, 0)
    Call(GetActorVar, ACTOR_SELF, 0, LVarA)
    IfEq(LVarA, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 0)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
        Call(b_area_trd_part_1_paratroopa_StartRumbleWithParams, 128, 7)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(0.2998046875))
        EndThread
        Call(ResetActorSounds, ACTOR_SELF, 2)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 10, 0, 1, 0)
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        Loop(10)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
            Wait(1)
            Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
            Wait(1)
        EndLoop
        Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
    Else
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar1, 0)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
        Thread
            Loop(10)
                Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
                Wait(1)
                Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 0)
                Wait(1)
            EndLoop
            Call(SetPartFlagBits, ACTOR_SELF, 3, 1, 1)
        EndThread
        Call(b_area_trd_part_1_paratroopa_StartRumbleWithParams, 150, 7)
        Thread
            Call(ShakeCam, 1, 0, 5, Float(0.2998046875))
        EndThread
        Call(ResetActorSounds, ACTOR_SELF, 2)
    EndIf
    Call(GetIndexFromHome, ACTOR_SELF, LVar0)
    Mod(LVar0, 4)
    Call(SetGoalToIndex, ACTOR_SELF, LVar0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_SELF, 1, 0x290101)
    Call(SetActorFlagBits, ACTOR_SELF, 512, 0)
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_trd_part_1_paratroopa_DownedStatusTable))
    Call(BindHandlePhase, ACTOR_SELF, 0)
    ExecWait(TTYD64_trd_part_1_paratroopa_EVS_Downed_Init)
    Call(SetActorType, ACTOR_SELF, 11)
    Call(SetActorFlagBits, ACTOR_SELF, 4096, 1)
    Call(HPBarToHome, ACTOR_SELF)
    Call(ResetAllActorSounds, ACTOR_SELF)
    IfNe(LVarA, 0)
        Call(DispatchEvent, ACTOR_SELF, 13)
    EndIf
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_bob_omb_EVS_Attack_Blast = {
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(PlayLoopingSoundAtActor, ACTOR_SELF, 0, -0x7FFFFFFF)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2C0007)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(AddGoalPos, ACTOR_SELF, 80, 0, 0)
            Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetActorRotationOffset, ACTOR_SELF, -1, 14, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 90)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2C0007)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(3.0))
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 30)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(UseBattleCamPreset, 2)
            ExecWait(b_area_trd_part_1_bob_omb_EVS_Explode)
            Call(SetAnimation, ACTOR_SELF, 1, 0x2C0011)
            Wait(10)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(10)
            Call(SetActorRotationOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            SetConst(LVar0, 1)
            SetConst(LVar1, -1)
            Set(LVar2, -0x3039)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        EndCaseGroup
    EndSwitch
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2C0007)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 10, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(5.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2C0014)
    Wait(15)
    Set(LVarA, 1)
    ExecWait(b_area_trd_part_1_bob_omb_EVS_Explode)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2C0011)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x10000200, 0, 0, 3, 32)
    Call(UseBattleCamPreset, 2)
    Wait(15)
    SetConst(LVar0, 1)
    SetConst(LVar1, 0x2C0011)
    Set(LVar2, -0x3039)
    ExecWait(Ref(EVS_Enemy_Death))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_koopa_troopa_EVS_Idle = {
    Label(0)
    Call(RandInt, 80, LVarA)
    Add(LVarA, 80)
    Loop(LVarA)
        Label(1)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_trd_part_1_koopa_troopa_EVS_UpdateTargetOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(1)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_koopa_troopa_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_paratroopa_DownedAnims_80227358))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_koopa_troopa_FlippedAnims))
    EndSwitch
    Loop(20)
        Label(2)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_trd_part_1_koopa_troopa_EVS_UpdateTargetOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(2)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(2)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_koopa_troopa_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_paratroopa_DownedAnims_80227358))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_koopa_troopa_FlippedAnims))
    EndSwitch
    Loop(80)
        Label(3)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_trd_part_1_koopa_troopa_EVS_UpdateTargetOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(3)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(3)
        EndIf
        Wait(1)
    EndLoop
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_paratroopa_EVS_Downed_Idle = {
    Label(0)
    Call(RandInt, 80, LVarA)
    Add(LVarA, 80)
    Loop(LVarA)
        Label(1)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_trd_part_1_paratroopa_EVS_Downed_UpdateTargetOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(1)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_paratroopa_DownedShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_paratroopa_DownedAnims))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_paratroopa_DownedFlippedAnims))
    EndSwitch
    Loop(20)
        Label(2)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_trd_part_1_paratroopa_EVS_Downed_UpdateTargetOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(2)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(2)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_paratroopa_DownedShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_paratroopa_DownedAnims))
        CaseEq(1)
            Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_paratroopa_DownedFlippedAnims))
    EndSwitch
    Loop(80)
        Label(3)
        Call(GetActorVar, ACTOR_SELF, 8, LVar0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_trd_part_1_paratroopa_EVS_Downed_UpdateTargetOffsets)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(3)
        EndIf
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(3)
        EndIf
        Wait(1)
    EndLoop
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_bullet_bill_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(UseBattleCamPreset, 63)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2D0004)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(15)
    Call(UseBattleCamPresetImmediately, 19)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 2, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Set(LVar3, LVar1)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Set(LVar1, LVar3)
            Sub(LVar0, 90)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(0.009765625))
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(JumpToGoal, ACTOR_SELF, 18, 0, 1, 0)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(HideHealthBar, ACTOR_SELF)
            Call(UseIdleAnimation, ACTOR_SELF, 0)
            Call(RemoveActor, ACTOR_SELF)
            Return
        EndCaseGroup
    EndSwitch
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar3, LVar1)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar1, LVar3)
    Add(LVar0, 10)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.009765625))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 12, 0, 1, 0)
    ExecWait(b_area_trd_part_1_bullet_bill_EVS_MakeExplosionFX)
    Call(SetGoalToTarget, ACTOR_SELF)
    Wait(2)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 2, 32)
    Call(UseBattleCamPreset, 2)
    Call(YieldTurn)
    SetConst(LVar0, 1)
    SetConst(LVar1, 0x2D0007)
    Set(LVar2, -0x3039)
    ExecWait(Ref(EVS_Enemy_Death))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_paratroopa_EVS_Flying_Idle = {
    Label(10)
    Call(RandInt, 80, LVar0)
    Add(LVar0, 80)
    Loop(LVar0)
        Label(0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_trd_part_1_paratroopa_EVS_Flying_UpdateTargetOffsets)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(0)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(0.599609375))
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_trd_part_1_paratroopa_FlyingShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, -5, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_paratroopa_FlyingAnims))
    Loop(20)
        Label(1)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_trd_part_1_paratroopa_EVS_Flying_UpdateTargetOffsets)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(0.599609375))
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_trd_part_1_paratroopa_FlyingShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleFlyToGoal, ACTOR_SELF, 0, -5, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 2, Ref(TTYD64_trd_part_1_paratroopa_FlyingAnims))
    Loop(40)
        Label(2)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        ExecWait(b_area_trd_part_1_paratroopa_EVS_Flying_UpdateTargetOffsets)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(2)
        EndIf
        Wait(1)
    EndLoop
    Goto(10)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_bullet_bill_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_trd_part_1_bullet_bill_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_trd_part_1_bullet_bill_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_trd_part_1_bullet_bill_EVS_HandleEvent))
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar1, 16)
        Call(SetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(ForceHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(HPBarToHome, ACTOR_SELF)
    Else
        Call(GetActorVar, ACTOR_SELF, 1, LVar0)
        Call(GetActorPos, LVar0, LVar1, LVar2, LVar3)
        Call(GetStatusFlags, LVar0, LVar4)
        IfFlag(LVar4, 0x80000)
            Set(LVar5, -13)
            Set(LVar6, 4)
        Else
            Set(LVar5, -33)
            Set(LVar6, 11)
        EndIf
        Add(LVar1, LVar5)
        Add(LVar2, LVar6)
        Call(SetActorPos, ACTOR_SELF, LVar1, LVar2, LVar3)
        Call(CopyStatusEffects, LVar0, ACTOR_SELF)
        Call(CopyBuffs, LVar0, ACTOR_SELF)
        Call(SetActorSounds, ACTOR_SELF, 2, 0, 0)
        Call(GetActorPos, LVar0, LVar1, LVarB, LVarC)
        Sub(LVar1, 90)
        Call(SetActorJumpGravity, ACTOR_SELF, Float(0.009765625))
        Call(SetAnimation, ACTOR_SELF, 1, 0x2D0003)
        Call(SetGoalPos, ACTOR_SELF, LVar1, LVar2, LVar3)
        Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        Call(SetAnimation, ACTOR_SELF, 1, 0x2D0001)
        Call(ForceHomePos, ACTOR_SELF, LVar1, LVar2, LVar3)
        Call(HPBarToHome, ACTOR_SELF)
    EndIf
    Return
    End
};
// clang-format on

Battle TTYD64_trd_part_1_Formations[] = {
    { .name = "\316\263\316\263",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_00,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263x2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_01,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263x3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_02,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263,\334\340xD",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_03,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263,\334\340xDx2",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_04,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263,\334\340xDx3",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_05,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263x2,\334\340xD",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_06,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263x2,\334\340xDx2",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_07,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\321\277\321\277x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_08,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\321\277\321\277x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_09,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\321\277\321\277,\316\263\316\263",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_0A,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\321\277\321\277,\316\263\316\263,\321\277\321\277",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_0B,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\321\277\321\277,\316\263\316\263,\321\277\321\277,\316\263\316\263",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_0C,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\321\277\321\277,\334\340\330\244x\022",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_0D,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\321\277\321\277,\334\340\330\244x\023",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_0E,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\334\340xD",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_0F,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\334\340xDx2",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_10,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\334\340xDx3",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_11,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\334\340xDx4",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_12,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\334\340xD,\316\263\316\263",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_13,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\334\340xDx2,\316\263\316\263",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_14,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\334\340xD,\316\263\316\263x2",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_15,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\316\263\316\263,\334\340xDx2",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_16,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\255\351\374_D{Fx\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_17,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\255\351\374x\022",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_18,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\255\351\374",
      .formationSize = 1,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_19,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    { .name = "\255\351\374x\023",
      .formationSize = 3,
      .formation = (Formation*) TTYD64_trd_part_1_Formation_1A,
      .stage = &b_area_trd_part_1_trd_01,
      .onBattleStart = NULL },
    {},
};

// clang-format off
EvtScript TTYD64_trd_part_1_bob_omb_EVS_Ignite = {
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x35D000)
        Return
    EndIf
    Label(0)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_bob_omb_IgnitedAnims))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_trd_part_1_bob_omb_EVS_HandleEvent_Ignited))
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x8000, 1)
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_trd_part_1_bob_omb_IgnitedStatusTable))
    Call(PlayLoopingSoundAtActor, ACTOR_SELF, 0, -0x7FFFFFFF)
    Call(SetAnimation, ACTOR_SELF, 1, 0x2C0005)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, 0, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
    Call(EnableActorPaletteEffects, ACTOR_SELF, 1, 1)
    Call(SetActorPaletteSwapParams, ACTOR_SELF, 1, 0, 2, 0, 10, 0, 10, 0, 0)
    Call(SetActorPaletteEffect, ACTOR_SELF, 1, 15)
    Wait(3)
    Call(StopLoopingSoundAtActor, ACTOR_SELF, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_bill_blaster_EVS_Move_FireBullet = {
    Call(SetAnimation, ACTOR_SELF, 1, 0x2E0002)
    Wait(13)
    Thread
        Call(ShakeCam, 1, 0, 10, Float(1.0))
    EndThread
    Call(StartRumble, 9)
    Call(PlaySoundAtActor, ACTOR_SELF, 712)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 33)
    Add(LVar1, 19)
    Add(LVar2, 3)
    Call(PlayEffect_impl, 0, LVar0, LVar1, LVar2, 2, 5, 0, 2, 0, 0, 0, 0, 0, 0)
    Call(PlayEffect_impl, 0, LVar0, LVar1, LVar2, 2, 5, 2, 2, 0, 0, 0, 0, 0, 0)
    Wait(2)
    Call(TTYD64_trd_part_1_bill_blaster_SetBulletInitVars)
    Call(SummonEnemy, Ref(TTYD64_trd_part_1_bill_blaster_BulletFormation), 0)
    Call(SetActorVar, ACTOR_SELF, 0, LVar0)
    Call(SetActorVar, ACTOR_SELF, 8, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_bob_omb_EVS_Defuse = {
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_trd_part_1_bob_omb_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_trd_part_1_bob_omb_DefaultAnims))
    Call(SetPartEventBits, ACTOR_SELF, 1, 0x8000, 0)
    Call(SetStatusTable, ACTOR_SELF, Ref(b_area_trd_part_1_bob_omb_StatusTable))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar2, 2)
    Call(PlayEffect_impl, 6, 3, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(StopLoopingSoundAtActor, ACTOR_SELF, 0)
    Call(EnableActorPaletteEffects, ACTOR_SELF, 1, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_bill_blaster_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_trd_part_1_bill_blaster_EVS_Move_FireBullet)
        CaseEq(1)
            ExecWait(b_area_trd_part_1_bill_blaster_EVS_Move_CheckForBullet)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_bob_omb_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetActorVar, ACTOR_SELF, 8, LVar0)
    IfEq(LVar0, 0)
        ExecWait(TTYD64_trd_part_1_bob_omb_EVS_Attack_Tackle)
    Else
        ExecWait(TTYD64_trd_part_1_bob_omb_EVS_Attack_Blast)
        Return
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_paratroopa_EVS_Flying_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_trd_part_1_bob_omb_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_trd_part_1_bob_omb_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_trd_part_1_bob_omb_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_paratroopa_EVS_Flying_Init_8022662C = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_trd_part_1_paratroopa_EVS_Flying_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_trd_part_1_paratroopa_EVS_Flying_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_trd_part_1_paratroopa_EVS_Flying_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_trd_part_1_paratroopa_EVS_Flying_HandlePhase))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_trd_part_1_Formation_0E[] = {
    { .actor = &TTYD64_trd_part_1_paratroopa,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 3 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
};

FormationRow TTYD64_trd_part_1_Formation_0C[] = {
    { .actor = &TTYD64_trd_part_1_paratroopa,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_trd_part_1_paratroopa,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
};

FormationRow TTYD64_trd_part_1_Formation_12[] = {
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
};

FormationRow TTYD64_trd_part_1_Formation_05[] = {
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
};

FormationRow TTYD64_trd_part_1_Formation_07[] = {
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 3 },
      .priority = 7,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
};

ActorPartBlueprint TTYD64_trd_part_1_paratroopa_ActorParts[] = {
    {
        .flags = 0x20001,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 36 },
        .opacity = 255,
        .idleAnimations = TTYD64_trd_part_1_paratroopa_DownedAnims,
        .defenseTable = b_area_trd_part_1_paratroopa_DownedDefense,
        .eventFlags = 0x1000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -7 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800000,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -4, 36 },
        .opacity = 255,
        .idleAnimations = TTYD64_trd_part_1_paratroopa_FlyingAnims,
        .defenseTable = b_area_trd_part_1_paratroopa_FlyingDefense,
        .eventFlags = 0x4000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 2, -14 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x20001,
        .index = 3,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 32 },
        .opacity = 255,
        .idleAnimations = TTYD64_trd_part_1_paratroopa_WingAnims,
        .defenseTable = b_area_trd_part_1_paratroopa_DownedDefense,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -10 },
        .overrideNameMsg = 0,
    },
};

// clang-format off
EvtScript TTYD64_trd_part_1_bill_blaster_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_trd_part_1_bill_blaster_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_trd_part_1_bill_blaster_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_trd_part_1_bill_blaster_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_paratroopa_EVS_Downed_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_trd_part_1_paratroopa_EVS_Downed_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_trd_part_1_paratroopa_EVS_Downed_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_trd_part_1_paratroopa_EVS_Downed_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_trd_part_1_koopa_troopa_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_trd_part_1_koopa_troopa_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_trd_part_1_koopa_troopa_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_trd_part_1_koopa_troopa_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 8, 0)
    Return
    End
};
// clang-format on

FormationRow TTYD64_trd_part_1_Formation_0D[] = {
    { .actor = &TTYD64_trd_part_1_paratroopa,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
};

FormationRow TTYD64_trd_part_1_Formation_0B[] = {
    { .actor = &TTYD64_trd_part_1_paratroopa,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_trd_part_1_paratroopa,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
};

FormationRow TTYD64_trd_part_1_Formation_11[] = {
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
};

FormationRow TTYD64_trd_part_1_Formation_15[] = {
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
};

FormationRow TTYD64_trd_part_1_Formation_16[] = {
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
};

FormationRow TTYD64_trd_part_1_Formation_14[] = {
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
};

FormationRow TTYD64_trd_part_1_Formation_17[] = {
    { .actor = &TTYD64_trd_part_1_bill_blaster,
      .home = { .vec = &b_area_trd_part_1_BlasterPos1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BILLBLASTER },
    { .actor = &TTYD64_trd_part_1_bill_blaster,
      .home = { .vec = &b_area_trd_part_1_BlasterPos2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BILLBLASTER },
    { .actor = &TTYD64_trd_part_1_bill_blaster,
      .home = { .vec = &b_area_trd_part_1_BlasterPos3 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BILLBLASTER },
};

FormationRow TTYD64_trd_part_1_Formation_04[] = {
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
};

FormationRow TTYD64_trd_part_1_Formation_02[] = {
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
};

FormationRow TTYD64_trd_part_1_Formation_09[] = {
    { .actor = &TTYD64_trd_part_1_paratroopa,
      .home = { .index = 4 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_trd_part_1_paratroopa,
      .home = { .index = 5 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_trd_part_1_paratroopa,
      .home = { .index = 6 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
};

FormationRow TTYD64_trd_part_1_Formation_06[] = {
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
};

FormationRow TTYD64_trd_part_1_Formation_1A[] = {
    { .actor = &TTYD64_trd_part_1_bullet_bill_80227894,
      .home = { .index = 0 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_trd_part_1_bullet_bill_80227894,
      .home = { .index = 1 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_trd_part_1_bullet_bill_80227894,
      .home = { .index = 2 },
      .priority = 8,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

s32 TTYD64_trd_part_1_paratroopa_DownedFlippedAnims[] = {
    1,  0x29010F, 7, 0x290110, 6, 0x290112, 9, 0x29010F, 8, 0x290110,
    11, 0x29010F, 5, 0x290110, 4, 0x290114, 3, 0x290114, 0,
};

s32 TTYD64_trd_part_1_bob_omb_IgnitedAnims[] = {
    1,  0x2C0005, 7, 0x2C0001, 6, 0x2C0018, 9, 0x2C0005, 8, 0x2C0001,
    11, 0x2C0003, 5, 0x2C0001, 4, 0x2C001D, 3, 0x2C001D, 0,
};

s32 TTYD64_trd_part_1_paratroopa_FlyingShuffleAnims[] = {
    1,  0x2A0101, 7, 0x2A0100, 6, 0x2A0112, 9, 0x2A0100, 8, 0x2A0100,
    11, 0x2A0101, 5, 0x2A0100, 4, 0x2A0113, 3, 0x2A0113, 0,
};

s32 TTYD64_trd_part_1_paratroopa_DownedShuffleAnims[] = {
    1,  0x290103, 7, 0x290100, 6, 0x290111, 9, 0x290103, 8, 0x290100,
    11, 0x290103, 5, 0x290100, 4, 0x290113, 3, 0x290113, 0,
};

s32 TTYD64_trd_part_1_koopa_troopa_FlippedAnims[] = {
    1,  0x29010F, 7, 0x290110, 6, 0x290112, 9, 0x29010F, 8, 0x290110,
    11, 0x29010F, 5, 0x290110, 4, 0x290114, 3, 0x290114, 0,
};

s32 TTYD64_trd_part_1_paratroopa_DownedAnims[] = {
    1,  0x290101, 7, 0x290100, 6, 0x290111, 9, 0x290101, 8, 0x290100,
    11, 0x290101, 5, 0x290100, 4, 0x290113, 3, 0x290113, 0,
};

s32 TTYD64_trd_part_1_paratroopa_WingAnims[] = {
    1,  0x2A010F, 7, 0x2A0100, 6, 0x2A0112, 9, 0x2A0100, 8, 0x2A0100,
    11, 0x2A010F, 5, 0x2A0100, 4, 0x2A0113, 3, 0x2A0113, 0,
};

s32 TTYD64_trd_part_1_koopa_troopa_ShuffleAnims[] = {
    1,  0x290103, 7, 0x290100, 6, 0x290111, 9, 0x290103, 8, 0x290100,
    11, 0x290103, 5, 0x290100, 4, 0x290113, 3, 0x290113, 0,
};

s32 TTYD64_trd_part_1_paratroopa_DownedAnims_80227358[] = {
    1,  0x290101, 7, 0x290100, 6, 0x290111, 9, 0x290101, 8, 0x290100,
    11, 0x290101, 5, 0x290100, 4, 0x290113, 3, 0x290113, 0,
};

s32 TTYD64_trd_part_1_bob_omb_DefaultAnims[] = {
    1,  0x2C0002, 7, 0x2C0000, 6, 0x2C0018, 9, 0x2C0004, 8, 0x2C0000,
    11, 0x2C0002, 5, 0x2C0000, 4, 0x2C001C, 3, 0x2C001C, 0,
};

s32 TTYD64_trd_part_1_paratroopa_FlyingAnims[] = {
    1,  0x2A0101, 7, 0x2A0100, 6, 0x2A0112, 9, 0x2A0100, 8, 0x2A0100,
    11, 0x2A0101, 5, 0x2A0100, 4, 0x2A0113, 3, 0x2A0113, 0,
};

ActorPartBlueprint TTYD64_trd_part_1_bill_blaster_ActorParts[] = {
    {
        .flags = 0x20000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -6, 29 },
        .opacity = 255,
        .idleAnimations = TTYD64_trd_part_1_bill_blaster_DefaultAnims,
        .defenseTable = b_area_trd_part_1_bill_blaster_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -9 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x80800001,
        .index = 2,
        .posOffset = { 100, 0, 0 },
        .targetOffset = { -106, 29 },
        .opacity = 255,
        .idleAnimations = TTYD64_trd_part_1_bill_blaster_DefaultAnims,
        .defenseTable = b_area_trd_part_1_bill_blaster_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -9 },
        .overrideNameMsg = 0,
    },
};

FormationRow TTYD64_trd_part_1_Formation_0A[] = {
    { .actor = &TTYD64_trd_part_1_paratroopa,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
};

FormationRow TTYD64_trd_part_1_Formation_10[] = {
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
};

FormationRow TTYD64_trd_part_1_Formation_13[] = {
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
};

FormationRow TTYD64_trd_part_1_Formation_18[] = {
    { .actor = &TTYD64_trd_part_1_bullet_bill_80227894,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_trd_part_1_bullet_bill_80227894,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_trd_part_1_Formation_01[] = {
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
};

FormationRow TTYD64_trd_part_1_Formation_03[] = {
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 2 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
};

FormationRow TTYD64_trd_part_1_Formation_08[] = {
    { .actor = &TTYD64_trd_part_1_paratroopa,
      .home = { .index = 5 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
    { .actor = &TTYD64_trd_part_1_paratroopa,
      .home = { .index = 6 },
      .priority = 9,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_PARATROOPA },
};

ActorBlueprint TTYD64_trd_part_1_bob_omb = {
    .flags = 0x0,
    .maxHP = 3,
    .type = 0x0D,
    .level = 6,
    .partCount = 1,
    .partsData = TTYD64_trd_part_1_bob_omb_ActorParts,
    .initScript = &TTYD64_trd_part_1_paratroopa_EVS_Flying_Init,
    .statusTable = b_area_trd_part_1_bob_omb_StatusTable,
    .escapeChance = 70,
    .airLiftChance = 90,
    .hurricaneChance = 90,
    .spookChance = 90,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 34, 35 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_trd_part_1_bullet_bill = {
    .flags = 0x200,
    .maxHP = 2,
    .type = 0x0F,
    .level = 5,
    .partCount = 1,
    .partsData = TTYD64_trd_part_1_bullet_bill_ActorParts,
    .initScript = &TTYD64_trd_part_1_bullet_bill_EVS_Init,
    .statusTable = b_area_trd_part_1_bullet_bill_StatusTable,
    .escapeChance = 50,
    .airLiftChance = 100,
    .hurricaneChance = 100,
    .spookChance = 0,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 0,
    .size = { 28, 22 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_trd_part_1_koopa_troopa = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x0B,
    .level = 6,
    .partCount = 1,
    .partsData = TTYD64_trd_part_1_koopa_troopa_ActorParts,
    .initScript = &TTYD64_trd_part_1_koopa_troopa_EVS_Init,
    .statusTable = b_area_trd_part_1_koopa_troopa_StatusTable,
    .escapeChance = 70,
    .airLiftChance = 90,
    .hurricaneChance = 90,
    .spookChance = 90,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 28, 36 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -15, 32 },
    .statusTextOffset = { 5, 32 },
};

ActorBlueprint TTYD64_trd_part_1_bullet_bill_80227894 = {
    .flags = 0x200,
    .maxHP = 2,
    .type = 0x0F,
    .level = 5,
    .partCount = 1,
    .partsData = TTYD64_trd_part_1_bullet_bill_ActorParts,
    .initScript = &TTYD64_trd_part_1_bullet_bill_EVS_Init,
    .statusTable = b_area_trd_part_1_bullet_bill_StatusTable,
    .escapeChance = 50,
    .airLiftChance = 100,
    .hurricaneChance = 100,
    .spookChance = 0,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 85,
    .coinReward = 0,
    .size = { 28, 22 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

ActorBlueprint TTYD64_trd_part_1_paratroopa = {
    .flags = 0x200,
    .maxHP = 4,
    .type = 0x0C,
    .level = 6,
    .partCount = 3,
    .partsData = TTYD64_trd_part_1_paratroopa_ActorParts,
    .initScript = &TTYD64_trd_part_1_paratroopa_EVS_Flying_Init_8022662C,
    .statusTable = b_area_trd_part_1_paratroopa_FlyingStatusTable,
    .escapeChance = 60,
    .airLiftChance = 95,
    .hurricaneChance = 100,
    .spookChance = 90,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 90,
    .coinReward = 1,
    .size = { 50, 38 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 29 },
    .statusTextOffset = { 8, 30 },
};

ActorBlueprint TTYD64_trd_part_1_bill_blaster = {
    .flags = 0x0,
    .maxHP = 4,
    .type = 0x10,
    .level = 10,
    .partCount = 2,
    .partsData = TTYD64_trd_part_1_bill_blaster_ActorParts,
    .initScript = &TTYD64_trd_part_1_bill_blaster_EVS_Init,
    .statusTable = b_area_trd_part_1_bill_blaster_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 20,
    .hurricaneChance = 15,
    .spookChance = 0,
    .upAndAwayChance = 95,
    .spinSmashReq = 4,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 55, 32 },
    .healthBarOffset = { 8, 0 },
    .statusIconOffset = { -24, 20 },
    .statusTextOffset = { 5, 25 },
};

ActorPartBlueprint TTYD64_trd_part_1_bullet_bill_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 16 },
        .opacity = 255,
        .idleAnimations = TTYD64_trd_part_1_bullet_bill_DefaultAnims,
        .defenseTable = b_area_trd_part_1_bullet_bill_DefenseTable,
        .eventFlags = 0x400,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -6 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_trd_part_1_bullet_bill_DefaultAnims[] = {
    1, 0x2D0001, 7, 0x2D0000, 8, 0x2D0000, 5, 0x2D0000, 0,
};

ActorPartBlueprint TTYD64_trd_part_1_bob_omb_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_trd_part_1_bob_omb_DefaultAnims,
        .defenseTable = b_area_trd_part_1_bob_omb_DefenseTable,
        .eventFlags = 0x200,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -9 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_trd_part_1_koopa_troopa_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -2, 36 },
        .opacity = 255,
        .idleAnimations = TTYD64_trd_part_1_paratroopa_DownedAnims_80227358,
        .defenseTable = b_area_trd_part_1_paratroopa_DownedDefense,
        .eventFlags = 0x1000,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -7 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_trd_part_1_bill_blaster_DefaultAnims[] = {
    1, 0x2E0001, 7, 0x2E0000, 8, 0x2E0000, 5, 0x2E0000, 0,
};

FormationRow TTYD64_trd_part_1_bill_blaster_BulletFormation[] = {
    { .actor = &TTYD64_trd_part_1_bullet_bill,
      .home = { .vec = &b_area_trd_part_1_bill_blaster_SummonPos },
      .priority = 100,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_trd_part_1_Formation_0F[] = {
    { .actor = &TTYD64_trd_part_1_bob_omb,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_BOBOMB },
};

FormationRow TTYD64_trd_part_1_Formation_19[] = {
    { .actor = &TTYD64_trd_part_1_bullet_bill_80227894,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

FormationRow TTYD64_trd_part_1_Formation_00[] = {
    { .actor = &TTYD64_trd_part_1_koopa_troopa,
      .home = { .index = 1 },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = TTYD64_DROP_KOOPATROOPA },
};

void TTYD64_InstallBattles_trd_part_1(void) {
    Mod_SetBattleList("TTYD64", 6, TTYD64_trd_part_1_Formations);
}
