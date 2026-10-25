#include "common.h"
#include "script_api/battle.h"
#include "effects.h"
#include "entity.h"
#include "battle/battle.h"
#include "port/Engine.h"
#include "port/modding/Mod.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_api.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_symbols.h"
#include "port/romhack/specific/TTYD64/include/ttyd64_rawmem.h"
#include "port/romhack/specific/TTYD64/battle/player_internal.h"

extern EvtScript battle_move_jump_charge_1_EVS_UseMove;
API_CALLABLE(GetActorPos);
API_CALLABLE(IsMessageBoxDisplayed);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerHopToGoal);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(ShowMessageBox);
API_CALLABLE(ShowVariableMessageBox);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(battle_move_jump_charge_1_GetChargeMessage);
API_CALLABLE(battle_move_jump_charge_1_IsJumpMaxCharged);
API_CALLABLE(battle_move_jump_charge_1_UnkMoveFunc2);
API_CALLABLE(battle_move_jump_charge_1_func_802A1108_74D678);
EvtScript TTYD64_battle_move_jump_charge_1_EVS_UseMove;
EvtScript TTYD64_battle_move_jump_charge_1_EVS_802A2B28;
EvtScript TTYD64_battle_move_jump_charge_1_EVS_802A2EA0;
EvtScript TTYD64_battle_move_jump_charge_1_EVS_802A31F0;

// clang-format off
EvtScript TTYD64_battle_move_jump_charge_1_EVS_UseMove = {
    ExecGetTID(TTYD64_battle_move_jump_charge_1_EVS_802A31F0, 0)
    Wait(10)
    ChildThread
        Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_PLAYER_CHARGE)
        Wait(8)
        Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_PLAYER_CHARGE)
        Wait(8)
    EndChildThread
    Call(SetAnimation, ACTOR_PLAYER, 0, 65568)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(battle_move_jump_charge_1_UnkMoveFunc2, LVar0, LVar1, LVar2, Float(1.2))
    Wait(3)
    Call(battle_move_jump_charge_1_UnkMoveFunc2, LVar0, LVar1, LVar2, Float(0.7998))
    Wait(30)
    ExecGetTID(TTYD64_battle_move_jump_charge_1_EVS_802A2EA0, 0)
    Call(MoveBattleCamOver, 5)
    Call(battle_move_jump_charge_1_IsJumpMaxCharged)
    IfEq(LVar0, 0)
        Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Add(LVar0, 10)
        Add(LVar1, 25)
        Add(LVar2, 5)
        Call(battle_move_jump_charge_1_func_802A1108_74D678, LVar0, LVar1, LVar2)
        Call(PlaySoundAtActor, ACTOR_PLAYER, 8335)
        ExecWait(TTYD64_battle_move_jump_charge_1_EVS_802A2B28)
    Else
        Call(ShowMessageBox, 8, 60)
    EndIf
    Label(0)
    Wait(1)
    Call(IsMessageBoxDisplayed, LVar0)
    IfEq(LVar0, 1)
        Goto(0)
    EndIf
    Call(UseIdleAnimation, ACTOR_PLAYER, false)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Return
    End
};

EvtScript TTYD64_battle_move_jump_charge_1_EVS_802A2B28 = {
    Wait(4)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_LONG_PLAYER_JUMP)
    Call(SetActorJumpGravity, ACTOR_PLAYER, Float(1.0))
    Call(SetActorSpeed, ACTOR_PLAYER, Float(1.0))
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 65545)
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Thread
        Wait(8)
        Exec(TTYD64_Script_InitTracker)
        Loop(5)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                Call(TTYD64_StylishDisarm)
                Call(TTYD64_StylishConsume)
                Goto(0)
            EndIf
            Wait(1)
        EndLoop
        Loop(2)
            ExecWait(TTYD64_Script_TimingTutor)
            Call(TTYD64_StylishPressed, LVar0)
            Wait(1)
        EndLoop
        Label(0)
    EndThread
    Call(PlayerHopToGoal, 20, 0, 0)
    Label(1)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 0)
        Wait(1)
        Goto(2)
    EndIf
    IfEq(LVar0, 1)
        Call(TTYD64_StylishAddCount, LVar0)
        Call(TTYD64_WriteField, TTYD64_F_GACTIONCOMMANDSTATUS_60_1U, 0)
        Set(LVarA, 0)
        ExecWait(TTYD64_Script_DoStylishFX)
        Call(SetAnimation, ACTOR_PLAYER, 0, 65586)
        Wait(20)
    EndIf
    Label(2)
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65545)
    Call(battle_move_jump_charge_1_GetChargeMessage)
    Call(ShowVariableMessageBox, LVar0, 60, 2)
    Return
    End
};

EvtScript TTYD64_battle_move_jump_charge_1_EVS_802A2EA0 = {
    Call(UseBattleCamPreset, 2)
    Exec(TTYD64_Script_InitTracker)
    Wait(5)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Return
    EndIf
    Loop(2)
        ExecWait(TTYD64_Script_TimingTutor)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Call(TTYD64_StylishAddCount, LVar0)
            Call(TTYD64_WriteField, TTYD64_F_GACTIONCOMMANDSTATUS_60_1U, 0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            SetTimescale(Float(3.0))
            Loop(3)
                Call(MakeLerp, 0, -180, 3, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, ACTOR_PLAYER, 0, LVar0, 0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
                Call(MakeLerp, -180, 0, 3, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, ACTOR_PLAYER, 0, LVar0, 0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
            EndLoop
            SetTimescale(Float(1.0))
            Call(SetActorRotation, ACTOR_PLAYER, 0, 0, 0)
            Return
        EndIf
        Wait(1)
    EndLoop
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Return
    End
};

EvtScript TTYD64_battle_move_jump_charge_1_EVS_802A31F0 = {
    Call(UseBattleCamPreset, 32)
    Exec(TTYD64_Script_NukeTracker)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_jump_charge_1(void) {
    Mod_ReplaceScript("TTYD64", &battle_move_jump_charge_1_EVS_UseMove, &TTYD64_battle_move_jump_charge_1_EVS_UseMove);
}
