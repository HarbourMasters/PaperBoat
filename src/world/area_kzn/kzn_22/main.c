#include "kzn_22.h"

#include "world/common/atomic/TexturePan.inc.c"

EvtScript N(EVS_ExitWalk_kzn_20_1) = EVT_EXIT_WALK_FIXED(60, kzn_22_ENTRY_0, "kzn_20", kzn_20_ENTRY_1);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(N(EVS_ExitWalk_kzn_20_1), TRIGGER_FLOOR_TOUCH, COLLIDER_deili1, 1, 0)
    Return
    End
};

EvtScript N(EVS_StartTexPanners) = {
    // lava surface #1
    Call(SetTexPanner, MODEL_yu, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_yu1, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(   0,  700,  200, -300)
        TEX_PAN_PARAMS_FREQ(   1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    // lava surface #2
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP( -700,  700,  200, -300)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    // lava river
    Call(SetTexPanner, MODEL_yougan1_1, TEX_PANNER_6)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_6)
        TEX_PAN_PARAMS_STEP( -1100,    0,  300,  500)
        TEX_PAN_PARAMS_FREQ(     1,    0,    1,    1)
        TEX_PAN_PARAMS_INIT(     0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    // lava fall
    Call(SetTexPanner, MODEL_yougan2_2, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP( 300, -500,    0,    0)
        TEX_PAN_PARAMS_FREQ(   1,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    // smoke
    Call(SetTexPanner, MODEL_kem1, TEX_PANNER_3)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP( -200,    0,  600, -400)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Call(SetTexPanner, MODEL_kem2, TEX_PANNER_4)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_4)
        TEX_PAN_PARAMS_STEP( 500,    0,    0, -400)
        TEX_PAN_PARAMS_FREQ(   1,    0,    0,    1)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};

EvtScript N(EVS_InterruptPartnersInLava) = {
    Loop(0)
        Loop(0)
            Wait(1)
            Call(GetModelCenter, MODEL_yu)
            Call(GetPlayerPos, LVar0, LVar3, LVar2)
            IfLt(LVar3, LVar1)
                BreakLoop
            EndIf
        EndLoop
        Call(GetCurrentPartnerID, LVar1)
        IfNe(LVar1, PARTNER_LAKILESTER)
            Call(InterruptUsePartner)
            Call(SetPlayerActionState, ACTION_STATE_HIT_LAVA)
            Wait(30)
        EndIf
    EndLoop
    Return
    End
};

API_CALLABLE(N(GetFloorCollider1)) {
    Bytecode* args = script->ptrReadPos;
    s32 outVar = *args++;

    evt_set_variable(script, outVar, gCollisionStatus.curFloor);
    return ApiStatus_DONE2;
}

EvtScript N(EVS_UpdateLavaLevel) = {
    SetGroup(EVT_GROUP_NOT_BATTLE)
    Call(EnableModel, MODEL_yu, false)
    Call(ParentColliderToModel, COLLIDER_o591, MODEL_yu)
    SetF(LVar4, Float(0.0))
    SetF(LVar5, Float(0.0))
    Set(LVarA, 0)
    Label(10)
        Call(UpdateColliderTransform, COLLIDER_o591)
        Switch(LVarA)
            CaseEq(0)
                // state 0: wait for player to stand on one of the steps
                Call(N(GetFloorCollider1), LVar0)
                IfEq(LVar0, COLLIDER_o357)
                    Exec(N(EVS_InterruptPartnersInLava))
                    Call(EnableModel, MODEL_yu, true)
                    Call(EnableModel, MODEL_yu1, false)
                    // start lava flowing toward the left
                    Call(SetTexPanner, MODEL_yu1, TEX_PANNER_2)
                    Call(SetTexPanner, MODEL_yu, TEX_PANNER_2)
                    Set(LVarA, 10) // set state to 10
                EndIf
            CaseEq(10)
                // state 10: raise the lava level
                IfLt(LVar4, 140)
                    Set(LVar5, Float(1.5))
                Else
                    IfEq(AF_KZN22_FlewAway, false)
                        Set(LVar5, Float(0.0))
                    Else
                        IfLt(LVar4, 285)
                            Set(LVar5, Float(2.8))
                        Else
                            Set(LVar5, Float(0.0))
                            Set(LVarA, -1)
                        EndIf
                    EndIf
                EndIf
        EndSwitch
        AddF(LVar4, LVar5)
        Call(TranslateModel, MODEL_yu, 0, LVar4, 0)
        Wait(1)
        Goto(10)
    Return
    End
};

LavaReset N(SafeFloorColliders)[] = {
    { .colliderID = COLLIDER_o582, .pos = { 200.0, 150.0, 180.0 }},
    { .colliderID = COLLIDER_o357, .pos = { 200.0, 150.0, 180.0 }},
    { .colliderID = NO_COLLIDER }
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_MT_LAVALAVA)
    Call(SetSpriteShading, SHADING_KZN_22)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Set(LVar0, N(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Wait(1)
    Exec(N(EVS_SetupMusic))
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o591, SURFACE_TYPE_LAVA)
    Thread
        Call(ResetFromLava, Ref(N(SafeFloorColliders)))
    EndThread
    Exec(N(EVS_StartTexPanners))
    Exec(N(EVS_UpdateLavaLevel))
    Return
    End
};
