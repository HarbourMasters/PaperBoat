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
#include "model.h"

API_CALLABLE(ActorExists);
API_CALLABLE(ActorSpeak);
API_CALLABLE(AddActorDecoration);
API_CALLABLE(AddBattleCamDist);
API_CALLABLE(AddGoalPos);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(BindHandleEvent);
API_CALLABLE(BindHandlePhase);
API_CALLABLE(BindIdle);
API_CALLABLE(BindTakeTurn);
API_CALLABLE(EnableIdleScript);
API_CALLABLE(EnemyDamageTarget);
API_CALLABLE(EnemyTestTarget);
API_CALLABLE(FallPartTo);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorVar);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetLastElement);
API_CALLABLE(GetLastEvent);
API_CALLABLE(GetPartOffset);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(HPBarToHome);
API_CALLABLE(IdleRunToGoal);
API_CALLABLE(JumpPartTo);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlaySoundAtModel);
API_CALLABLE(PlaySoundAtPart);
API_CALLABLE(RandInt);
API_CALLABLE(RemoveActorDecoration);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorDispOffset);
API_CALLABLE(SetActorIdleSpeed);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorVar);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetAnimationRate);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetBattleCamTargetingModes);
API_CALLABLE(SetEnemyHP);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetIdleAnimations);
API_CALLABLE(SetIdleGoal);
API_CALLABLE(SetOwnerTarget);
API_CALLABLE(SetPartFlagBits);
API_CALLABLE(SetPartJumpGravity);
API_CALLABLE(SetPartMoveSpeed);
API_CALLABLE(SetPartPos);
API_CALLABLE(SetPartScale);
API_CALLABLE(SetPartTargetFlagBits);
API_CALLABLE(SetTargetActor);
API_CALLABLE(ShakeCam);
API_CALLABLE(StartRumble);
API_CALLABLE(TranslateModel);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(YieldTurn);
API_CALLABLE(b_area_kmr_part_2_blue_goomba_2_CalculateArcsinDeg);
API_CALLABLE(b_area_kmr_part_2_blue_goomba_2_ReduceLevel);
extern Vec3i b_area_kmr_part_2_BlueBossPos;
extern Vec3i b_area_kmr_part_2_BlueMinibossPos;
extern Vec3i b_area_kmr_part_2_KingBossPos;
extern Vec3i b_area_kmr_part_2_RedBossPos;
extern Vec3i b_area_kmr_part_2_RedMinibossPos;
extern Vec3i b_area_kmr_part_2_TreeBossPos;
extern EvtScript b_area_kmr_part_2_blue_goomba_1_EVS_GoombaBros_Death;
extern s32 b_area_kmr_part_2_blue_goomba_2_DefenseTable[];
extern s32 b_area_kmr_part_2_blue_goomba_2_StatusTable[];
extern s32 b_area_kmr_part_2_goomba_king_DefenseTable[];
extern EvtScript b_area_kmr_part_2_goomba_king_EVS_HandleEvent;
extern EvtScript b_area_kmr_part_2_goomba_king_EVS_HandlePhase;
extern EvtScript b_area_kmr_part_2_goomba_king_EVS_ShakeScreenWhileWalking;
extern s32 b_area_kmr_part_2_goomba_king_StatusTable[];
extern ActorPartBlueprint b_area_kmr_part_2_goomnut_tree_ActorParts[];
extern EvtScript b_area_kmr_part_2_goomnut_tree_EVS_Idle;
extern EvtScript b_area_kmr_part_2_goomnut_tree_EVS_TakeTurn;
extern s32 b_area_kmr_part_2_goomnut_tree_StatusTable[];
extern u8 b_area_kmr_part_2_goomnut_tree_Tree[];
extern Stage b_area_kmr_part_2_kmr_03;
extern Stage b_area_kmr_part_2_kmr_06;
extern EvtScript b_area_kmr_part_2_red_goomba_1_EVS_GoombaBros_Death;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_TakeTurn;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_TakeTurn_80218D08;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_TakeTurn_80219A10;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_TakeTurn_8021A718;
extern EvtScript TTYD64_kmr_part_2_goomba_king_EVS_Attack_GroundStomp;
extern EvtScript TTYD64_kmr_part_2_goomnut_tree_EVS_DropNutOnGoombas;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_HandleEvent_8021CD6C;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_HandleEvent_8021D42C;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_HandleEvent_8021DAEC;
extern EvtScript TTYD64_kmr_part_2_goomba_king_EVS_Attack_SpinSwipe;
extern EvtScript TTYD64_kmr_part_2_goomnut_tree_EVS_ShakeTree;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Idle;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Idle_80220350;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Idle_8022062C;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Idle_80220908;
extern EvtScript TTYD64_kmr_part_2_goomba_king_EVS_Idle;
extern EvtScript TTYD64_kmr_part_2_goomnut_tree_EVS_Init;
extern EvtScript TTYD64_kmr_part_2_goomnut_tree_EVS_HandleEvent;
extern EvtScript TTYD64_kmr_part_2_goomba_king_EVS_TakeTurn;
extern EvtScript TTYD64_kmr_part_2_goomba_king_EVS_Init;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_1_EVS_TakeTurn;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_1_EVS_Init;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_Inner;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_Inner_80223C40;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Init;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_Inner_80223E54;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_Inner_80223F38;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_80224094;
extern EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_802240D0;
extern EvtScript TTYD64_kmr_part_2_goomnut_tree_EVS_TriggerTreeShake;
extern ActorBlueprint TTYD64_kmr_part_2_goomba_king;
extern ActorBlueprint TTYD64_kmr_part_2_blue_goomba_2;
extern ActorBlueprint TTYD64_kmr_part_2_blue_goomba_2_802242E8;
extern ActorBlueprint TTYD64_kmr_part_2_red_goomba_2;
extern ActorBlueprint TTYD64_kmr_part_2_red_goomba_2_80224338;
extern ActorBlueprint TTYD64_kmr_part_2_goomnut_tree;
extern FormationRow TTYD64_kmr_part_2_Formation_01[];
extern s32 TTYD64_kmr_part_2_blue_goomba_2_ShuffleAnims[];
extern s32 TTYD64_kmr_part_2_red_goomba_2_ShuffleAnims[];
extern s32 TTYD64_kmr_part_2_blue_goomba_2_DefaultAnims[];
extern s32 TTYD64_kmr_part_2_red_goomba_2_DefaultAnims[];
extern s32 TTYD64_kmr_part_2_blue_goomba_2_ShuffleAnims_80223DBC[];
extern s32 TTYD64_kmr_part_2_red_goomba_2_ShuffleAnims_80223E08[];
extern s32 TTYD64_kmr_part_2_red_goomba_2_DefaultAnims_80223EA0[];
extern s32 TTYD64_kmr_part_2_blue_goomba_2_DefaultAnims_80223EEC[];
extern ActorPartBlueprint TTYD64_kmr_part_2_goomba_king_ActorParts[];
extern s32 TTYD64_kmr_part_2_goomba_king_DefaultAnims[];
extern s32 TTYD64_kmr_part_2_goomba_king_ShuffleAnims[];
extern Battle TTYD64_kmr_part_2_Formations[];
extern FormationRow TTYD64_kmr_part_2_Formation_00[];
extern ActorPartBlueprint TTYD64_kmr_part_2_blue_goomba_2_ActorParts[];
extern ActorPartBlueprint TTYD64_kmr_part_2_blue_goomba_2_ActorParts_8022444C[];
extern ActorPartBlueprint TTYD64_kmr_part_2_blue_goomba_2_ActorParts_80224470[];
extern ActorPartBlueprint TTYD64_kmr_part_2_blue_goomba_2_ActorParts_80224494[];

static void TTYD64_kmr_part_2_goomnut_tree_foliage_setup_shear_mtx(Matrix4f mtx, f32 scale, f32 xAmount, f32 zAmount) {
    guMtxIdentF(mtx);
    mtx[1][0] = scale * xAmount;
    mtx[1][1] = 1.0f;
    mtx[1][2] = scale * zAmount;
}

static API_CALLABLE(TTYD64_kmr_part_2_goomnut_tree_TransformFoliage) {
    Bytecode* args = script->ptrReadPos;
    s32 modelListIndex = get_model_list_index_from_tree_index(evt_get_variable(script, *args++));
    f32 scale = evt_get_float_variable(script, *args++);
    f32 dx = evt_get_float_variable(script, *args++);
    f32 dy = evt_get_float_variable(script, *args++);
    f32 dz = evt_get_float_variable(script, *args++);
    Model* model = get_model_from_list_index(modelListIndex);
    Matrix4f mtx;

    if (!(model->flags & MODEL_FLAG_HAS_TRANSFORM)) {
        guTranslateF(model->userTransformMtx, 0.0f, dy, 0.0f);
        TTYD64_kmr_part_2_goomnut_tree_foliage_setup_shear_mtx(mtx, scale, dx, dz);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        guTranslateF(mtx, 0.0f, -dy, 0.0f);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        model->flags |= (MODEL_FLAG_HAS_TRANSFORM | MODEL_FLAG_MATRIX_DIRTY);
    } else {
        guTranslateF(mtx, 0.0f, dy, 0.0f);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        TTYD64_kmr_part_2_goomnut_tree_foliage_setup_shear_mtx(mtx, scale, dx, dz);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
        guTranslateF(mtx, 0.0f, -dy, 0.0f);
        guMtxCatF(mtx, model->userTransformMtx, model->userTransformMtx);
    }

    return ApiStatus_DONE2;
}

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_TakeTurn = {
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
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x620106)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x620102)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x620108)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 10)
            Set(LVar1, 10)
            Add(LVar2, 3)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_kmr_part_2_blue_goomba_2_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x620108)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x62010D)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 5, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 7, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620109)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620108)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Thread
                Wait(4)
                Set(LVar0, 180)
                Loop(4)
                    Sub(LVar0, 45)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetAnimation, ACTOR_SELF, 1, 0x620108)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x62010C)
            Wait(5)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620102)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_kmr_part_2_blue_goomba_2_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x620108)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620108)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Wait(1)
    EndSwitch
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(1)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620102)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x620102)
            Wait(3)
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x620106)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_TakeTurn_80218D08 = {
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
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x620006)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x620002)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x620008)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 10)
            Set(LVar1, 10)
            Add(LVar2, 3)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_kmr_part_2_blue_goomba_2_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x620008)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x62000D)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 5, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 7, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620009)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620008)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Thread
                Wait(4)
                Set(LVar0, 180)
                Loop(4)
                    Sub(LVar0, 45)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetAnimation, ACTOR_SELF, 1, 0x620008)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x62000C)
            Wait(5)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620002)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_kmr_part_2_blue_goomba_2_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x620008)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620008)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Wait(1)
    EndSwitch
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(1)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620002)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x620002)
            Wait(3)
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x620006)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_TakeTurn_80219A10 = {
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
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x620006)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x620002)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x620008)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 10)
            Set(LVar1, 10)
            Add(LVar2, 3)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_kmr_part_2_blue_goomba_2_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x620008)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x62000D)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 5, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 7, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620009)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620008)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Thread
                Wait(4)
                Set(LVar0, 180)
                Loop(4)
                    Sub(LVar0, 45)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetAnimation, ACTOR_SELF, 1, 0x620008)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x62000C)
            Wait(5)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620002)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_kmr_part_2_blue_goomba_2_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x620008)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620008)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Wait(1)
    EndSwitch
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(1)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620002)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x620002)
            Wait(3)
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x620006)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_TakeTurn_8021A718 = {
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
    Call(SetBattleCamTargetingModes, -1, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x620106)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    Call(SetActorSpeed, ACTOR_SELF, Float(6.0))
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x620102)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -1, 0)
    Wait(1)
    Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
    Wait(5)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x620108)
    Call(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, 16)
    Switch(LVar0)
        CaseOrEq(6)
        CaseOrEq(5)
            Set(LVarA, LVar0)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Sub(LVar0, 10)
            Set(LVar1, 10)
            Add(LVar2, 3)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_kmr_part_2_blue_goomba_2_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x620108)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x62010D)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 5, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, -2, 0)
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Call(SetActorDispOffset, ACTOR_SELF, 0, 7, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620109)
            Wait(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Wait(5)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620108)
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Set(LVar1, 0)
            Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(2.0))
            Thread
                Wait(4)
                Set(LVar0, 180)
                Loop(4)
                    Sub(LVar0, 45)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Wait(1)
                EndLoop
                Call(SetAnimation, ACTOR_SELF, 1, 0x620108)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 15, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x62010C)
            Wait(5)
            Call(UseBattleCamPreset, 2)
            Call(YieldTurn)
            Call(SetActorYaw, ACTOR_SELF, 180)
            Call(AddActorDecoration, ACTOR_SELF, 1, 0, 2)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(SetActorYaw, ACTOR_SELF, 0)
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620102)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(RemoveActorDecoration, ACTOR_SELF, 1, 0)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
        CaseDefault
            Call(SetGoalToTarget, ACTOR_SELF)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.2001953125))
            Thread
                Call(GetActorPos, ACTOR_SELF, LVar1, LVar2, LVar0)
                Set(LVar0, 0)
                Loop(16)
                    Call(GetActorPos, ACTOR_SELF, LVar4, LVar5, LVar6)
                    Call(b_area_kmr_part_2_blue_goomba_2_CalculateArcsinDeg, LVar1, LVar2, LVar4, LVar5, LVar0)
                    Call(SetActorRotation, ACTOR_SELF, 0, 0, LVar0)
                    Set(LVar1, LVar4)
                    Set(LVar2, LVar5)
                    Set(LVar3, LVar6)
                    Wait(1)
                EndLoop
            EndThread
            Thread
                Wait(6)
                Call(SetAnimation, ACTOR_SELF, 1, 0x620108)
            EndThread
            Call(JumpToGoal, ACTOR_SELF, 16, 0, 1, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620108)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.2998046875), Float(0.5), Float(1.0))
            Wait(1)
    EndSwitch
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 128, 0, 0, 1, 32)
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Call(UseBattleCamPreset, 2)
            Call(SetActorScale, ACTOR_SELF, Float(1.099609375), Float(0.7998046875), Float(1.0))
            Wait(1)
            Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
            Wait(1)
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
            Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620102)
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
            Call(SetAnimation, ACTOR_SELF, 1, 0x620102)
            Wait(3)
            Call(YieldTurn)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x620106)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_goomba_king_EVS_Attack_GroundStomp = {
    Call(UseBattleCamPreset, 15)
    Call(BattleCamTargetActor, ACTOR_SELF)
    Call(MoveBattleCamOver, 40)
    Wait(15)
    Call(SetBattleCamTargetingModes, 0, 1, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x630009)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.7998046875))
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(JumpToGoal, ACTOR_SELF, 20, 0, 1, 0)
    Call(PlaySoundAtActor, ACTOR_SELF, 8372)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Call(SetAnimation, ACTOR_SELF, 1, 0x630000)
    Thread
        Call(StartRumble, 11)
        Call(GetStatusFlags, ACTOR_SELF, LVar0)
        IfNotFlag(LVar0, 0x80000)
            Call(ShakeCam, 1, 0, 10, Float(4.0))
        EndIf
        Call(SetAnimation, ACTOR_SELF, 1, 0x630001)
        Call(PlayEffect_impl, 20, 0, -80, 125, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 20, 0, -15, 135, 0, 85, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 20, 0, 100, 103, 0, 70, 0, 0, 0, 0, 0, 0, 0, 0)
    EndThread
    Thread
        Wait(12)
        Call(PlaySoundAtPart, 515, 3, 769)
    EndThread
    Thread
        Wait(10)
        Call(SetPartJumpGravity, 515, 3, Float(1.5))
        Call(GetPartOffset, 515, 3, LVar0, LVar1, LVar2)
        Call(FallPartTo, 515, 3, LVar0, 35, LVar2, 14)
        Sub(LVar0, 12)
        Call(JumpPartTo, 515, 3, LVar0, 10, LVar2, 10, 1)
        Sub(LVar0, 7)
        Call(JumpPartTo, 515, 3, LVar0, 10, LVar2, 7, 1)
        Loop(20)
            Call(SetPartFlagBits, 515, 3, 1, 0)
            Wait(1)
            Call(SetPartFlagBits, 515, 3, 1, 1)
            Wait(1)
        EndLoop
    EndThread
    Thread
        Wait(5)
        Call(PlaySoundAtPart, 515, 4, 769)
    EndThread
    Thread
        Wait(3)
        Call(SetPartJumpGravity, 515, 4, Float(1.5))
        Call(GetPartOffset, 515, 4, LVar0, LVar1, LVar2)
        Call(FallPartTo, 515, 4, LVar0, 10, LVar2, 15)
        Sub(LVar0, 12)
        Call(JumpPartTo, 515, 4, LVar0, 10, LVar2, 10, 1)
        Sub(LVar0, 7)
        Call(JumpPartTo, 515, 4, LVar0, 10, LVar2, 7, 1)
        Loop(20)
            Call(SetPartFlagBits, 515, 4, 1, 0)
            Wait(1)
            Call(SetPartFlagBits, 515, 4, 1, 1)
            Wait(1)
        EndLoop
    EndThread
    Thread
        Wait(17)
        Call(PlaySoundAtPart, 515, 5, 769)
    EndThread
    Thread
        Wait(15)
        Call(SetPartJumpGravity, 515, 5, Float(1.5))
        Call(GetPartOffset, 515, 5, LVar0, LVar1, LVar2)
        Call(FallPartTo, 515, 5, LVar0, 10, LVar2, 17)
        Add(LVar0, 12)
        Call(JumpPartTo, 515, 5, LVar0, 10, LVar2, 10, 1)
        Add(LVar0, 7)
        Call(JumpPartTo, 515, 5, LVar0, 10, LVar2, 7, 1)
        Loop(20)
            Call(SetPartFlagBits, 515, 5, 1, 0)
            Wait(1)
            Call(SetPartFlagBits, 515, 5, 1, 1)
            Wait(1)
        EndLoop
    EndThread
    Thread
        Wait(15)
        Call(TTYD64_SetTargetActorInTheBack, ACTOR_SELF)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 2, 16)
        Switch(LVarA)
            CaseOrEq(6)
            CaseOrEq(5)
                IfEq(LVarA, 5)
                    Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
                EndIf
            EndCaseGroup
            CaseDefault
                Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 2, 32)
        EndSwitch
    EndThread
    Wait(24)
    Wait(2)
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 2, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
        EndCaseGroup
        CaseDefault
            Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0xFFFF, 0, 2, 32)
    EndSwitch
    Switch(LVar0)
        CaseEq(10)
            Return
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_goomnut_tree_EVS_DropNutOnGoombas = {
    Call(PlayEffect_impl, 20, 0, -25, 120, 0, 90, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(GetActorVar, ACTOR_SELF, 5, LVar0)
    IfNe(LVar0, 0)
        Return
    EndIf
    Call(UseBattleCamPreset, 15)
    Call(BattleCamTargetActor, 512)
    Wait(20)
    Call(SetActorVar, ACTOR_SELF, 5, 1)
    Call(ActorExists, 512, LVar0)
    IfEq(LVar0, 0)
        Call(SetGoalPos, ACTOR_SELF, 10, 0, 10)
        Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
        Call(PlaySoundAtPart, ACTOR_SELF, 2, 769)
        Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.7998046875))
        Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(4.0))
        Call(FallPartTo, ACTOR_SELF, 2, 10, 20, 10, 20)
        Call(JumpPartTo, ACTOR_SELF, 2, 30, 20, 10, 10, 1)
        Call(JumpPartTo, ACTOR_SELF, 2, 40, 20, 10, 5, 1)
        Loop(20)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
            Wait(1)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Wait(1)
        EndLoop
        Return
    EndIf
    Call(PlaySoundAtPart, ACTOR_SELF, 2, 769)
    Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.7998046875))
    Call(SetPartMoveSpeed, ACTOR_SELF, 2, Float(4.0))
    Call(GetStatusFlags, 512, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(FallPartTo, ACTOR_SELF, 2, 10, 80, 10, 10)
    Else
        Call(FallPartTo, ACTOR_SELF, 2, 10, 32, 10, 10)
    EndIf
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 30)
    Call(SetOwnerTarget, 512, 2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 3, 32)
    Call(ActorExists, 513, LVar0)
    IfEq(LVar0, 0)
        Call(GetPartOffset, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
        Add(LVar0, 65)
        Set(LVar1, 20)
        Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.7001953125))
        Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 20, 1)
        Add(LVar0, 12)
        Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 8, 1)
        Loop(20)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
            Wait(1)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Wait(1)
        EndLoop
        Return
    EndIf
    Call(GetActorPos, 513, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, 513, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar1, 50)
    Else
        Add(LVar1, 20)
    EndIf
    Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.7001953125))
    Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 20, 1)
    Call(SetOwnerTarget, 513, 1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 3, 32)
    Call(ActorExists, 514, LVar0)
    IfEq(LVar0, 0)
        Call(GetPartOffset, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
        Add(LVar0, 35)
        Set(LVar1, 20)
        Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.7001953125))
        Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 20, 1)
        Add(LVar0, 12)
        Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 8, 1)
        Loop(20)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
            Wait(1)
            Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
            Wait(1)
        EndLoop
        Return
    EndIf
    Call(GetActorPos, 514, LVar0, LVar1, LVar2)
    Call(GetStatusFlags, 514, LVar3)
    IfNotFlag(LVar3, 0x80000)
        Add(LVar1, 50)
    Else
        Add(LVar1, 20)
    EndIf
    Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.7001953125))
    Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 20, 1)
    Call(SetOwnerTarget, 514, 1)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, 0x8000000, 0, 0, 3, 32)
    Call(GetPartOffset, ACTOR_SELF, 2, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Set(LVar1, 20)
    Call(SetPartJumpGravity, ACTOR_SELF, 2, Float(0.7001953125))
    Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 20, 1)
    Add(LVar0, 12)
    Call(JumpPartTo, ACTOR_SELF, 2, LVar0, LVar1, LVar2, 8, 1)
    Loop(20)
        Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 0)
        Wait(1)
        Call(SetPartFlagBits, ACTOR_SELF, 2, 1, 1)
        Wait(1)
    EndLoop
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x62000E)
            SetConst(LVar2, 0x62000F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x62000E)
            SetConst(LVar2, 0x62000F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x62000F)
            ExecWait(b_area_kmr_part_2_red_goomba_1_EVS_GoombaBros_Death)
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(b_area_kmr_part_2_red_goomba_1_EVS_GoombaBros_Death)
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x62000C)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620002)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(b_area_kmr_part_2_red_goomba_1_EVS_GoombaBros_Death)
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620002)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(b_area_kmr_part_2_red_goomba_1_EVS_GoombaBros_Death)
            Return
        CaseEq(53)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x620006)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620002)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620006)
            SetConst(LVar2, 0x620009)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620006)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x620002)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_HandleEvent_8021CD6C = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x62000E)
            SetConst(LVar2, 0x62000F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x62000E)
            SetConst(LVar2, 0x62000F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x62000F)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x62000C)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620002)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620002)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x620006)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620002)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620006)
            SetConst(LVar2, 0x620009)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620006)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620009)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x620002)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_HandleEvent_8021D42C = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x62010E)
            SetConst(LVar2, 0x62010F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x62010E)
            SetConst(LVar2, 0x62010F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x62010F)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x62010C)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620102)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620102)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_Death))
            Return
        CaseEq(53)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x620106)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620102)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620106)
            SetConst(LVar2, 0x620109)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620106)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x620102)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_HandleEvent_8021DAEC = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorScale, ACTOR_SELF, Float(1.0), Float(1.0), Float(1.0))
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_Hit))
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x62010E)
            SetConst(LVar2, 0x62010F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
        CaseEq(36)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x62010E)
            SetConst(LVar2, 0x62010F)
            ExecWait(Ref(EVS_Enemy_BurnHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x62010F)
            ExecWait(b_area_kmr_part_2_blue_goomba_1_EVS_GoombaBros_Death)
            Return
        CaseEq(11)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
        CaseEq(33)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_SpinSmashHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(b_area_kmr_part_2_blue_goomba_1_EVS_GoombaBros_Death)
            Return
        CaseEq(47)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_Knockback))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x62010C)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(8.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Wait(5)
            Call(SetAnimation, ACTOR_SELF, 1, 0x620102)
            Call(SetActorJumpGravity, ACTOR_SELF, Float(1.599609375))
            Call(JumpToGoal, ACTOR_SELF, 5, 0, 1, 0)
        CaseEq(38)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_ShockHit))
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(b_area_kmr_part_2_blue_goomba_1_EVS_GoombaBros_Death)
            Return
        CaseEq(19)
        CaseOrEq(23)
        CaseOrEq(25)
        CaseOrEq(31)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620102)
            ExecWait(Ref(EVS_Enemy_NoDamageHit))
        EndCaseGroup
        CaseEq(32)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_Hit))
            Wait(10)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(b_area_kmr_part_2_blue_goomba_1_EVS_GoombaBros_Death)
            Return
        CaseEq(53)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(2.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x620106)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimationRate, ACTOR_SELF, 1, Float(1.0))
            Call(HPBarToHome, ACTOR_SELF)
        CaseEq(49)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620102)
            ExecWait(Ref(EVS_Enemy_Recover))
        CaseEq(57)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620106)
            SetConst(LVar2, 0x620109)
            ExecWait(Ref(EVS_Enemy_ScareAway))
            Return
        CaseEq(58)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620106)
            ExecWait(Ref(EVS_Enemy_AirLift))
        CaseEq(22)
            SetConst(LVar0, 1)
            SetConst(LVar1, 0x620109)
            ExecWait(Ref(EVS_Enemy_BlowAway))
            Return
        CaseDefault
    EndSwitch
    Call(SetAnimation, ACTOR_SELF, 1, 0x620102)
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_goomba_king_EVS_Attack_SpinSwipe = {
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(UseBattleCamPreset, 63)
        Call(AddBattleCamDist, -100)
        Call(SetBattleCamOffsetY, 20)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 30)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    Else
        Call(UseBattleCamPreset, 63)
        Call(AddBattleCamDist, -100)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 20)
        Call(SetBattleCamTargetingModes, -1, 1, 0)
    EndIf
    Call(TTYD64_SetTargetActorInFront, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, 32, 0, 0)
    Else
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(AddGoalPos, ACTOR_SELF, 12, 0, 0)
    EndIf
    Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
    Call(SetAnimation, ACTOR_SELF, 1, 0x630004)
    Call(RunToGoal, ACTOR_SELF, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x630001)
    Wait(8)
    Thread
        Call(PlaySoundAtActor, ACTOR_SELF, 8429)
        Wait(10)
        Call(PlaySoundAtActor, ACTOR_SELF, 8429)
    EndThread
    Call(SetAnimation, ACTOR_SELF, 1, 0x630005)
    Set(LVar0, 0)
    Loop(20)
        Add(LVar0, 18)
        Call(SetActorYaw, ACTOR_SELF, LVar0)
        Wait(1)
    EndLoop
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, 0, 0, 2, 16)
    Switch(LVarA)
        CaseOrEq(6)
        CaseOrEq(5)
            IfEq(LVarA, 5)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, (-0x7FFFFFFF - 1), 0, 0, 0)
            EndIf
            Call(SetAnimation, ACTOR_SELF, 1, 0x630007)
            Set(LVar0, 0)
            Loop(20)
                Add(LVar0, 18)
                Call(SetActorYaw, ACTOR_SELF, LVar0)
                Wait(1)
            EndLoop
            Call(SetActorYaw, ACTOR_SELF, 0)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x630001)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x630004)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x630001)
            Call(EnableIdleScript, ACTOR_SELF, 1)
            Call(UseIdleAnimation, ACTOR_SELF, 1)
            Return
        EndCaseGroup
    EndSwitch
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVarA, 0, 0, 0, 1, 32)
    Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
    Call(SetActorYaw, ACTOR_SELF, 0)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetAnimation, ACTOR_SELF, 1, 0x630001)
    Switch(LVarA)
        CaseDefault
            Wait(20)
            Call(SetAnimation, ACTOR_SELF, 1, 0x630001)
            Call(SetGoalToHome, ACTOR_SELF)
            Call(SetActorSpeed, ACTOR_SELF, Float(3.0))
            Call(SetAnimation, ACTOR_SELF, 1, 0x630004)
            Call(RunToGoal, ACTOR_SELF, 0, 0)
            Call(SetAnimation, ACTOR_SELF, 1, 0x630001)
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_goomnut_tree_EVS_ShakeTree = {
    SetTimescale(Float(2.0))
    UseBuf(LVar0)
    BufRead4(LVar1, LVar2, LVar3, LVar4)
    BufRead1(LVar5)
    Call(GetActorPos, 0, LVar6, LVarF, LVar8)
    Call(PlaySound, 357)
    Call(PlaySound, 358)
    Thread
        Set(LFlag0, 0)
        IfNe(LVar1, 0)
            Wait(1)
            Loop(5)
                UseBuf(LVar1)
                BufRead1(LVar2)
                Loop(LVar2)
                    BufRead1(LVar3)
                    Call(TTYD64_kmr_part_2_goomnut_tree_TransformFoliage, LVar3, Float(0.099609375), Float(0.2001953125), LVarF, 0)
                    IfEq(LFlag0, 0)
                        Set(LFlag0, 1)
                        Call(PlaySoundAtModel, LVar3, 358, 0)
                    EndIf
                EndLoop
                Wait(1)
                UseBuf(LVar1)
                BufRead1(LVar2)
                Loop(LVar2)
                    BufRead1(LVar3)
                    Call(TTYD64_kmr_part_2_goomnut_tree_TransformFoliage, LVar3, Float(0.099609375), Float(-0.2001953125), LVarF, 0)
                EndLoop
                Wait(1)
            EndLoop
            UseBuf(LVar1)
            BufRead1(LVar2)
            Loop(LVar2)
                BufRead1(LVar3)
                Call(TranslateModel, LVar3, 0, 0, 0)
            EndLoop
            Wait(1)
        EndIf
    EndThread
    Thread
        Set(LFlag0, 0)
        IfNe(LVar2, 0)
            Loop(5)
                UseBuf(LVar2)
                BufRead1(LVar3)
                Loop(LVar3)
                    BufRead1(LVar4)
                    Call(TTYD64_kmr_part_2_goomnut_tree_TransformFoliage, LVar4, Float(0.099609375), Float(0.2001953125), LVarF, 0)
                    IfEq(LFlag0, 0)
                        Set(LFlag0, 1)
                        Call(PlaySoundAtModel, LVar4, 357, 0)
                    EndIf
                EndLoop
                Wait(1)
                UseBuf(LVar2)
                BufRead1(LVar3)
                Loop(LVar3)
                    BufRead1(LVar4)
                    Call(TTYD64_kmr_part_2_goomnut_tree_TransformFoliage, LVar4, Float(0.099609375), Float(-0.2001953125), LVarF, 0)
                EndLoop
                Wait(1)
            EndLoop
            UseBuf(LVar2)
            BufRead1(LVar3)
            Loop(LVar3)
                BufRead1(LVar4)
                Call(TranslateModel, LVar4, 0, 0, 0)
            EndLoop
            Wait(1)
        EndIf
    EndThread
    Thread
        IfNe(LVar4, 0)
            UseBuf(LVar4)
            BufRead1(LVar5)
            Loop(LVar5)
                BufRead3(LVar6, LVar7, LVar8)
                Call(PlayEffect_impl, 20, 0, LVar6, LVar7, LVar8, 100, 0, 0, 0, 0, 0, 0, 0, 0)
            EndLoop
        EndIf
    EndThread
    Wait(15)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Idle = {
    Label(10)
    Call(RandInt, 80, LVar0)
    Add(LVar0, 80)
    Loop(LVar0)
        Label(0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(0)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_blue_goomba_2_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_blue_goomba_2_DefaultAnims_80223EEC))
    Loop(20)
        Label(1)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_blue_goomba_2_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_blue_goomba_2_DefaultAnims_80223EEC))
    Loop(80)
        Label(2)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
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
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Idle_80220350 = {
    Label(10)
    Call(RandInt, 80, LVar0)
    Add(LVar0, 80)
    Loop(LVar0)
        Label(0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(0)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_red_goomba_2_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_red_goomba_2_DefaultAnims_80223EA0))
    Loop(20)
        Label(1)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_red_goomba_2_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_red_goomba_2_DefaultAnims_80223EA0))
    Loop(80)
        Label(2)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
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
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Idle_8022062C = {
    Label(10)
    Call(RandInt, 80, LVar0)
    Add(LVar0, 80)
    Loop(LVar0)
        Label(0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(0)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_red_goomba_2_ShuffleAnims_80223E08))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_red_goomba_2_DefaultAnims))
    Loop(20)
        Label(1)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_red_goomba_2_ShuffleAnims_80223E08))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_red_goomba_2_DefaultAnims))
    Loop(80)
        Label(2)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
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
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Idle_80220908 = {
    Label(10)
    Call(RandInt, 80, LVar0)
    Add(LVar0, 80)
    Loop(LVar0)
        Label(0)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(0)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_blue_goomba_2_ShuffleAnims_80223DBC))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_blue_goomba_2_DefaultAnims))
    Loop(20)
        Label(1)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
        IfFlag(LVar1, 0x35D000)
            Wait(1)
            Goto(1)
        EndIf
        Wait(1)
    EndLoop
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_blue_goomba_2_ShuffleAnims_80223DBC))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_blue_goomba_2_DefaultAnims))
    Loop(80)
        Label(2)
        Call(GetStatusFlags, ACTOR_SELF, LVar1)
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
EvtScript TTYD64_kmr_part_2_goomba_king_EVS_Idle = {
    Label(0)
    Call(RandInt, 80, LVar0)
    Add(LVar0, 80)
    Wait(LVar0)
    Label(1)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x35D000)
        Wait(1)
        Goto(1)
    EndIf
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar0, 5)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_goomba_king_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_goomba_king_DefaultAnims))
    Wait(20)
    Label(2)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, 0x35D000)
        Wait(1)
        Goto(2)
    EndIf
    Call(SetGoalToHome, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorIdleSpeed, ACTOR_SELF, Float(1.0))
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_goomba_king_ShuffleAnims))
    Call(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(IdleRunToGoal, ACTOR_SELF, 0)
    Call(SetIdleAnimations, ACTOR_SELF, 1, Ref(TTYD64_kmr_part_2_goomba_king_DefaultAnims))
    Wait(80)
    Goto(0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_goomnut_tree_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(b_area_kmr_part_2_goomnut_tree_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(b_area_kmr_part_2_goomnut_tree_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kmr_part_2_goomnut_tree_EVS_HandleEvent))
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 4, 0)
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 1)
    Call(SetPartPos, ACTOR_SELF, 2, 10, 140, 10)
    Call(SetPartPos, ACTOR_SELF, 3, -95, 140, 10)
    Call(SetPartPos, ACTOR_SELF, 4, -115, 130, 0)
    Call(SetPartPos, ACTOR_SELF, 5, -65, 118, 5)
    Call(SetPartScale, ACTOR_SELF, 3, Float(0.5), Float(0.5), Float(1.0))
    Call(SetPartScale, ACTOR_SELF, 4, Float(0.5), Float(0.5), Float(1.0))
    Call(SetPartScale, ACTOR_SELF, 5, Float(0.5), Float(0.5), Float(1.0))
    Call(SetPartTargetFlagBits, ACTOR_SELF, 1, 4, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_goomnut_tree_EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(GetLastElement, LVarE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseOrEq(9)
        CaseOrEq(23)
            ExecWait(TTYD64_kmr_part_2_goomnut_tree_EVS_TriggerTreeShake)
        EndCaseGroup
        CaseOrEq(10)
        CaseOrEq(25)
            ExecWait(TTYD64_kmr_part_2_goomnut_tree_EVS_TriggerTreeShake)
            ExecWait(TTYD64_kmr_part_2_goomnut_tree_EVS_DropNutOnGoombas)
        EndCaseGroup
        CaseEq(11)
            ExecWait(TTYD64_kmr_part_2_goomnut_tree_EVS_TriggerTreeShake)
            ExecWait(TTYD64_kmr_part_2_goomnut_tree_EVS_DropNutOnGoombas)
        CaseEq(32)
            ExecWait(TTYD64_kmr_part_2_goomnut_tree_EVS_TriggerTreeShake)
        CaseEq(33)
            ExecWait(TTYD64_kmr_part_2_goomnut_tree_EVS_TriggerTreeShake)
        CaseEq(42)
        CaseEq(47)
        CaseEq(53)
        CaseDefault
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, 1)
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_goomba_king_EVS_TakeTurn = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(EnableIdleScript, ACTOR_SELF, 0)
    Call(SetActorDispOffset, ACTOR_SELF, 0, 0, 0)
    Call(SetTargetActor, ACTOR_SELF, 0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, 0x80000)
        Call(GetActorVar, 515, 6, LVar0)
        IfNe(LVar0, 0)
            Call(RandInt, 100, LVar1)
            IfLt(LVar1, 60)
                Sub(LVar0, 1)
                Call(SetActorVar, 515, 6, LVar0)
                ExecWait(TTYD64_kmr_part_2_goomba_king_EVS_Attack_GroundStomp)
                Return
            EndIf
        EndIf
    EndIf
    ExecWait(TTYD64_kmr_part_2_goomba_king_EVS_Attack_SpinSwipe)
    Return
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_goomba_king_EVS_Init = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_2_goomba_king_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_kmr_part_2_goomba_king_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(b_area_kmr_part_2_goomba_king_EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(b_area_kmr_part_2_goomba_king_EVS_HandlePhase))
    ExecGetTID(b_area_kmr_part_2_goomba_king_EVS_ShakeScreenWhileWalking, LVar0)
    Call(SetActorVar, ACTOR_SELF, 4, LVar0)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(SetActorVar, ACTOR_SELF, 2, 0)
    Call(SetActorVar, ACTOR_SELF, 3, 0)
    Call(SetActorVar, ACTOR_SELF, 5, 0)
    Call(SetActorVar, ACTOR_SELF, 6, 0)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_1_EVS_TakeTurn = {
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    IfEq(LVar0, 0)
        Call(UseBattleCamPreset, 14)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 30)
        Wait(30)
        Call(SetActorVar, ACTOR_SELF, 0, 1)
        Call(ActorSpeak, 0xB00BF, ACTOR_SELF, 1, -1, -1)
    EndIf
    ExecWait(TTYD64_kmr_part_2_blue_goomba_2_EVS_TakeTurn)
    Return
    End
};
// clang-format on

FormationRow TTYD64_kmr_part_2_Formation_01[] = {
    { .actor = &TTYD64_kmr_part_2_goomba_king,
      .home = { .vec = &b_area_kmr_part_2_KingBossPos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_kmr_part_2_red_goomba_2,
      .home = { .vec = &b_area_kmr_part_2_RedBossPos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_kmr_part_2_blue_goomba_2_802242E8,
      .home = { .vec = &b_area_kmr_part_2_BlueBossPos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_kmr_part_2_goomnut_tree,
      .home = { .vec = &b_area_kmr_part_2_TreeBossPos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_1_EVS_Init = {
    ExecWait(TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_Inner_80223F38)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_2_blue_goomba_1_EVS_TakeTurn))
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_Inner = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_2_blue_goomba_2_EVS_TakeTurn_80219A10))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_kmr_part_2_blue_goomba_2_EVS_Idle_8022062C))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kmr_part_2_blue_goomba_2_EVS_HandleEvent))
    Return
    End
};
// clang-format on

s32 TTYD64_kmr_part_2_blue_goomba_2_ShuffleAnims[] = {
    1,  0x620106, 7, 0x620100, 6, 0x62010D, 9, 0x620102, 8, 0x620100,
    11, 0x620106, 5, 0x620100, 4, 0x62010C, 3, 0x62010C, 0,
};

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_Inner_80223C40 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_2_blue_goomba_2_EVS_TakeTurn_8021A718))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_kmr_part_2_blue_goomba_2_EVS_Idle_80220908))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kmr_part_2_blue_goomba_2_EVS_HandleEvent_8021D42C))
    Return
    End
};
// clang-format on

s32 TTYD64_kmr_part_2_red_goomba_2_ShuffleAnims[] = {
    1,  0x620006, 7, 0x620000, 6, 0x62000D, 9, 0x620002, 8, 0x620000,
    11, 0x620006, 5, 0x620000, 4, 0x62000C, 3, 0x62000C, 0,
};

s32 TTYD64_kmr_part_2_blue_goomba_2_DefaultAnims[] = {
    1,  0x620102, 7, 0x620100, 6, 0x62010D, 9, 0x620102, 8, 0x620100,
    11, 0x620102, 5, 0x620100, 4, 0x62010C, 3, 0x62010C, 0,
};

s32 TTYD64_kmr_part_2_red_goomba_2_DefaultAnims[] = {
    1,  0x620002, 7, 0x620000, 6, 0x62000D, 9, 0x620002, 8, 0x620000,
    11, 0x620002, 5, 0x620000, 4, 0x62000C, 3, 0x62000C, 0,
};

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Init = {
    ExecWait(TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_Inner)
    Call(SetActorVar, ACTOR_SELF, 0, 0)
    Call(SetActorVar, ACTOR_SELF, 1, 0)
    Return
    End
};
// clang-format on

s32 TTYD64_kmr_part_2_blue_goomba_2_ShuffleAnims_80223DBC[] = {
    1,  0x620106, 7, 0x620100, 6, 0x62010D, 9, 0x620102, 8, 0x620100,
    11, 0x620106, 5, 0x620100, 4, 0x62010C, 3, 0x62010C, 0,
};

s32 TTYD64_kmr_part_2_red_goomba_2_ShuffleAnims_80223E08[] = {
    1,  0x620006, 7, 0x620000, 6, 0x62000D, 9, 0x620002, 8, 0x620000,
    11, 0x620006, 5, 0x620000, 4, 0x62000C, 3, 0x62000C, 0,
};

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_Inner_80223E54 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_2_blue_goomba_2_EVS_TakeTurn_80218D08))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_kmr_part_2_blue_goomba_2_EVS_Idle_80220350))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kmr_part_2_blue_goomba_2_EVS_HandleEvent_8021CD6C))
    Return
    End
};
// clang-format on

s32 TTYD64_kmr_part_2_red_goomba_2_DefaultAnims_80223EA0[] = {
    1,  0x620002, 7, 0x620000, 6, 0x62000D, 9, 0x620002, 8, 0x620000,
    11, 0x620002, 5, 0x620000, 4, 0x62000C, 3, 0x62000C, 0,
};

s32 TTYD64_kmr_part_2_blue_goomba_2_DefaultAnims_80223EEC[] = {
    1,  0x620102, 7, 0x620100, 6, 0x62010D, 9, 0x620102, 8, 0x620100,
    11, 0x620102, 5, 0x620100, 4, 0x62010C, 3, 0x62010C, 0,
};

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_Inner_80223F38 = {
    Call(BindTakeTurn, ACTOR_SELF, Ref(TTYD64_kmr_part_2_blue_goomba_2_EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(TTYD64_kmr_part_2_blue_goomba_2_EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(TTYD64_kmr_part_2_blue_goomba_2_EVS_HandleEvent_8021DAEC))
    Return
    End
};
// clang-format on

ActorPartBlueprint TTYD64_kmr_part_2_goomba_king_ActorParts[] = {
    {
        .flags = 0x20020,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -25, 15 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_2_goomba_king_DefaultAnims,
        .defenseTable = b_area_kmr_part_2_goomba_king_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
    {
        .flags = 0x800020,
        .index = 2,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 80 },
        .opacity = 255,
        .idleAnimations = NULL,
        .defenseTable = b_area_kmr_part_2_goomba_king_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, 0 },
        .overrideNameMsg = 0,
    },
};

s32 TTYD64_kmr_part_2_goomba_king_DefaultAnims[] = {
    1, 0x630001, 7, 0x630000, 6, 0x630008, 9, 0x630000, 8, 0x630000, 11, 0x630000, 5, 0x630000, 4, 0x630007, 0,
};

s32 TTYD64_kmr_part_2_goomba_king_ShuffleAnims[] = {
    1, 0x630004, 7, 0x630000, 6, 0x630008, 9, 0x630000, 8, 0x630000, 11, 0x630000, 5, 0x630000, 4, 0x630007, 0,
};

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_80224094 = {
    ExecWait(TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_Inner_80223E54)
    Call(SetEnemyHP, ACTOR_SELF, 2)
    Call(b_area_kmr_part_2_blue_goomba_2_ReduceLevel)
    Return
    End
};
// clang-format on

// clang-format off
EvtScript TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_802240D0 = {
    ExecWait(TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_Inner_80223C40)
    Call(SetEnemyHP, ACTOR_SELF, 2)
    Call(b_area_kmr_part_2_blue_goomba_2_ReduceLevel)
    Return
    End
};
// clang-format on

Battle TTYD64_kmr_part_2_Formations[] = {
    { .name = "\257\352\354\303\311,\257\352\326\353\374",
      .formationSize = 2,
      .formation = (Formation*) TTYD64_kmr_part_2_Formation_00,
      .stage = &b_area_kmr_part_2_kmr_03,
      .onBattleStart = NULL },
    { .name = "\257\352\255\363\260,\257\352\354\303\311,\257\352\326\353\374",
      .formationSize = 4,
      .formation = (Formation*) TTYD64_kmr_part_2_Formation_01,
      .stage = &b_area_kmr_part_2_kmr_06,
      .onBattleStart = NULL },
    {},
};

FormationRow TTYD64_kmr_part_2_Formation_00[] = {
    { .actor = &TTYD64_kmr_part_2_blue_goomba_2,
      .home = { .vec = &b_area_kmr_part_2_BlueMinibossPos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
    { .actor = &TTYD64_kmr_part_2_red_goomba_2_80224338,
      .home = { .vec = &b_area_kmr_part_2_RedMinibossPos },
      .priority = 10,
      .var0 = 0,
      .var1 = 0,
      .var2 = 0,
      .var3 = 0 },
};

// clang-format off
EvtScript TTYD64_kmr_part_2_goomnut_tree_EVS_TriggerTreeShake = {
    Set(LVar0, Ref(b_area_kmr_part_2_goomnut_tree_Tree))
    ExecWait(TTYD64_kmr_part_2_goomnut_tree_EVS_ShakeTree)
    Return
    End
};
// clang-format on

ActorBlueprint TTYD64_kmr_part_2_goomba_king = {
    .flags = 0x0,
    .maxHP = 10,
    .type = 0x92,
    .level = 49,
    .partCount = 2,
    .partsData = TTYD64_kmr_part_2_goomba_king_ActorParts,
    .initScript = &TTYD64_kmr_part_2_goomba_king_EVS_Init,
    .statusTable = b_area_kmr_part_2_goomba_king_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 56, 80 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -6, 38 },
    .statusTextOffset = { 12, 75 },
};

ActorBlueprint TTYD64_kmr_part_2_blue_goomba_2 = {
    .flags = 0x0,
    .maxHP = 6,
    .type = 0x90,
    .level = 20,
    .partCount = 1,
    .partsData = TTYD64_kmr_part_2_blue_goomba_2_ActorParts_8022444C,
    .initScript = &TTYD64_kmr_part_2_blue_goomba_1_EVS_Init,
    .statusTable = b_area_kmr_part_2_blue_goomba_2_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 32, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 8, 25 },
};

ActorBlueprint TTYD64_kmr_part_2_blue_goomba_2_802242E8 = {
    .flags = 0x0,
    .maxHP = 6,
    .type = 0x90,
    .level = 20,
    .partCount = 1,
    .partsData = TTYD64_kmr_part_2_blue_goomba_2_ActorParts_80224494,
    .initScript = &TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_802240D0,
    .statusTable = b_area_kmr_part_2_blue_goomba_2_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 32, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 8, 25 },
};

ActorBlueprint TTYD64_kmr_part_2_red_goomba_2 = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x91,
    .level = 20,
    .partCount = 1,
    .partsData = TTYD64_kmr_part_2_blue_goomba_2_ActorParts_80224470,
    .initScript = &TTYD64_kmr_part_2_blue_goomba_2_EVS_Init_80224094,
    .statusTable = b_area_kmr_part_2_blue_goomba_2_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 32, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 8, 25 },
};

ActorBlueprint TTYD64_kmr_part_2_red_goomba_2_80224338 = {
    .flags = 0x0,
    .maxHP = 7,
    .type = 0x91,
    .level = 20,
    .partCount = 1,
    .partsData = TTYD64_kmr_part_2_blue_goomba_2_ActorParts,
    .initScript = &TTYD64_kmr_part_2_blue_goomba_2_EVS_Init,
    .statusTable = b_area_kmr_part_2_blue_goomba_2_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 0,
    .powerBounceChance = 80,
    .coinReward = 0,
    .size = { 32, 32 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 8, 25 },
};

ActorBlueprint TTYD64_kmr_part_2_goomnut_tree = {
    .flags = 0x2004004,
    .maxHP = 255,
    .type = 0x93,
    .level = 1,
    .partCount = 5,
    .partsData = b_area_kmr_part_2_goomnut_tree_ActorParts,
    .initScript = &TTYD64_kmr_part_2_goomnut_tree_EVS_Init,
    .statusTable = b_area_kmr_part_2_goomnut_tree_StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 0,
    .coinReward = 0,
    .size = { 0, 0 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { 0, 0 },
    .statusTextOffset = { 0, 0 },
};

ActorPartBlueprint TTYD64_kmr_part_2_blue_goomba_2_ActorParts[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_2_red_goomba_2_DefaultAnims,
        .defenseTable = b_area_kmr_part_2_blue_goomba_2_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -3 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_kmr_part_2_blue_goomba_2_ActorParts_8022444C[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_2_blue_goomba_2_DefaultAnims_80223EEC,
        .defenseTable = b_area_kmr_part_2_blue_goomba_2_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -3 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_kmr_part_2_blue_goomba_2_ActorParts_80224470[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_2_red_goomba_2_DefaultAnims_80223EA0,
        .defenseTable = b_area_kmr_part_2_blue_goomba_2_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -3 },
        .overrideNameMsg = 0,
    },
};

ActorPartBlueprint TTYD64_kmr_part_2_blue_goomba_2_ActorParts_80224494[] = {
    {
        .flags = 0x800000,
        .index = 1,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = TTYD64_kmr_part_2_blue_goomba_2_DefaultAnims,
        .defenseTable = b_area_kmr_part_2_blue_goomba_2_DefenseTable,
        .eventFlags = 0x0,
        .elementImmunityFlags = 0x0,
        .projectileTargetOffset = { 0, -3 },
        .overrideNameMsg = 0,
    },
};

void TTYD64_InstallBattles_kmr_part_2(void) {
    Mod_SetBattleList("TTYD64", 1, TTYD64_kmr_part_2_Formations);
}
