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

extern EvtScript battle_move_earthquake_jump_EVS_UseMove;
API_CALLABLE(AddGoalPos);
API_CALLABLE(CancelablePlayerRunToGoal);
API_CALLABLE(CheckButtonPress);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(EnablePlayerBlur);
API_CALLABLE(FlyToGoal);
API_CALLABLE(GetActionProgress);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorRotation);
API_CALLABLE(GetAnimation);
API_CALLABLE(GetDistanceToGoal);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetHomePos);
API_CALLABLE(GetJumpActionQuality);
API_CALLABLE(GetMashActionQuality);
API_CALLABLE(GetPlayerActionQuality);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(InterruptActionCommand);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PartnerYieldTurn);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerBasicJumpToGoal);
API_CALLABLE(PlayerDamageEnemy);
API_CALLABLE(PlayerHopToGoal);
API_CALLABLE(PlayerLandJump);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(PlayerTestEnemy);
API_CALLABLE(PlayerYieldTurn);
API_CALLABLE(RandInt);
API_CALLABLE(SetActionResult);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorSounds);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleFlagBits);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToFirstTarget);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(SetupMashMeter);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowActionHud);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(action_command_jump_init);
API_CALLABLE(action_command_jump_start);
API_CALLABLE(action_command_tidal_wave_init);
API_CALLABLE(action_command_tidal_wave_start);
API_CALLABLE(battle_move_jump_attack_CalcJumpReboundTime);
API_CALLABLE(battle_partner_sushie_SetScaleTidalWaveCharge);
API_CALLABLE(func_802693F0);
EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A1000;
EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A1140;
EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A1F40;
EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A212C;
EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A22A0;
EvtScript TTYD64_battle_move_earthquake_jump_EVS_UseMove;
EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A264C;
EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A2C4C;
EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A2EC8;
EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A2F70;

// clang-format off
EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A1000 = {
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(GetGoalPos, ACTOR_PLAYER, LVar6, LVar7, LVar8)
    Call(GetActorPos, ACTOR_PLAYER, LVar7, LVar8, LVar9)
    IfGt(LVar6, LVar7)
        Sub(LVar6, LVar7)
    Else
        Sub(LVar7, LVar6)
        Set(LVar6, LVar7)
    EndIf
    Sub(LVar6, 20)
    DivF(LVar6, Float(10.5889))
    AddF(LVar6, 15)
    Set(LVarA, LVar6)
    Return
    End
};

EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A1140 = {
    Call(ShowActionHud, 1)
    Call(TTYD64_GetStackBoost, 376, 1, LVarD, 0)
    Exec(TTYD64_Script_NukeTracker)
    ExecWait(TTYD64_battle_move_earthquake_jump_EVS_802A22A0)
    Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_1_1U, LVar1)
    Switch(LVar1)
        CaseEq(0)
            Add(LVarD, 1)
        CaseEq(1)
            Add(LVarD, 2)
        CaseGe(2)
            Add(LVarD, 3)
    EndSwitch
    Exec(TTYD64_Script_NukeTracker)
    Call(PlayerTestEnemy, LVar0, 128, 0, 0, LVarD, 0)
    IfEq(LVar0, 6)
        ExecWait(TTYD64_battle_move_earthquake_jump_EVS_802A2C4C)
        Return
    EndIf
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, (Bytecode) (s32) 0x8000134B, LVarD, 80)
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
            Call(PlayerDamageEnemy, LVar0, 128, 0, (Bytecode) (s32) 0x8000134B, LVarD, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_move_earthquake_jump_EVS_802A1F40)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
        EndCaseGroup
    EndSwitch
    ChildThread
        Call(UseBattleCamPreset, 27)
        Wait(5)
        Call(UseBattleCamPreset, 35)
    EndChildThread
    Call(GetJumpActionQuality, LVarF)
    Call(InterruptActionCommand)
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Call(action_command_jump_init)
    Call(ShowActionHud, 0)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Thread
        Call(GetActorRotation, 0, LVar0, LVar1, LVar2)
        Call(TTYD64_SetMoveScratch, TTYD64_MSI_EARTHQUAKE_JUMP, TTYD64_MS_FLAG, 1)
        Loop(10)
            Sub(LVar1, 20)
            IfLt(LVar1, -360)
                Set(LVar1, 0)
            EndIf
            Call(SetActorRotation, ACTOR_PLAYER, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
        Loop(70)
            Sub(LVar1, 50)
            IfLt(LVar1, -360)
                Set(LVar1, 0)
            EndIf
            Call(SetActorRotation, ACTOR_PLAYER, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
        Call(PlaySound, 8227)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, 40)
        Sub(LVar1, 15)
        Call(RandInt, 30, LVar3)
        Sub(LVar1, LVar3)
        Call(PlayEffect_impl, 103, 0, LVar0, LVar1, LVar2, Float(3.0), 42, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, -30)
        Add(LVar1, 15)
        Call(RandInt, 20, LVar3)
        Add(LVar1, LVar3)
        Call(PlayEffect_impl, 103, 0, LVar0, LVar1, LVar2, Float(2.0), 42, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Add(LVar0, -20)
        Add(LVar1, -40)
        Call(RandInt, 10, LVar3)
        Sub(LVar0, LVar3)
        Call(PlayEffect_impl, 103, 0, LVar0, LVar1, LVar2, Float(2.0), 42, 0, 0, 0, 0, 0, 0, 0)
        Call(GetActorRotation, 0, LVar0, LVar1, LVar2)
        Loop(30)
            Sub(LVar1, 50)
            IfLt(LVar1, -360)
                Set(LVar1, 0)
            EndIf
            Call(SetActorRotation, ACTOR_PLAYER, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
        Loop(0)
            Sub(LVar1, 10)
            IfLt(LVar1, -330)
                Call(SetActorRotation, ACTOR_PLAYER, LVar0, LVar1, LVar2)
                BreakLoop
            EndIf
            Call(SetActorRotation, ACTOR_PLAYER, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
        Loop(0)
            Sub(LVar1, 5)
            IfLe(LVar1, -360)
                Set(LVar1, 0)
                Call(SetActorRotation, ACTOR_PLAYER, LVar0, LVar1, LVar2)
                Call(TTYD64_SetMoveScratch, TTYD64_MSI_EARTHQUAKE_JUMP, TTYD64_MS_FLAG, 0)
                BreakLoop
            EndIf
            Call(SetActorRotation, ACTOR_PLAYER, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
    EndThread
    Call(GetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65543)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(5.0))
    Call(FlyToGoal, ACTOR_PLAYER, 0, 0, 0)
    Wait(1)
    Call(SetActorSounds, ACTOR_PLAYER, 3, 346, 0)
    Call(SetActionResult, LVarF)
    Call(TTYD64_SetTornadoJumpHud, 1)
    Call(LoadActionCommand, ACTION_COMMAND_TIDAL_WAVE)
    Call(action_command_tidal_wave_init)
    Call(SetupMashMeter, 5, 20, 30, 60, 80, 100)
    Call(action_command_tidal_wave_start, 0, 100, 3)
    Loop(100)
        Call(GetActionProgress, LVar0)
        Call(battle_partner_sushie_SetScaleTidalWaveCharge)
        Wait(1)
    EndLoop
    Call(TTYD64_SetTornadoJumpHud, 0)
    Loop(0)
        Call(TTYD64_GetMoveScratch, TTYD64_MSI_EARTHQUAKE_JUMP, TTYD64_MS_FLAG, LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(GetMashActionQuality, LVar0)
    Set(LVarD, LVar0)
    Call(TTYD64_WriteField, TTYD64_F_GBATTLESTATUS_81_1U, 1)
    Exec(TTYD64_Script_InitTracker)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 5)
    Wait(15)
    Call(InitTargetIterator)
    Call(ChooseNextTarget, -1, 0)
    Loop(0)
        Call(SetGoalToTarget, ACTOR_SELF)
        Call(PlayerTestEnemy, LVar0, 0, 20, 0, 2, 16)
        IfEq(LVar0, 6)
            Goto(10)
        EndIf
        Switch(LVarD)
            CaseGe(1)
                Call(PlayerDamageEnemy, LVar0, 939524096, 0, 0, LVarD, 112)
            CaseDefault
                Call(PlayerDamageEnemy, LVar0, 939524096, 0, 0, LVarD, 48)
        EndSwitch
        Wait(5)
        Label(10)
        Call(ChooseNextTarget, 0, LVar0)
        IfEq(LVar0, -1)
            BreakLoop
        EndIf
    EndLoop
    Call(PartnerYieldTurn)
    Call(GetActorPos, ACTOR_SELF, LVar0, 0, LVar2)
    Call(GetHomePos, ACTOR_SELF, 0, LVar1, 0)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Thread
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Wait(1)
            Goto(0)
        EndIf
        Loop(3)
            Call(GetAnimation, ACTOR_SELF, 0, LVar0)
            Switch(LVar0)
                CaseOrEq(65538)
                CaseOrEq(65545)
                    BreakLoop
                EndCaseGroup
            EndSwitch
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 0)
                ExecWait(TTYD64_Script_TimingTutor)
            Else
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Label(0)
        Call(TTYD64_StylishDisarm)
    EndThread
    Call(SetAnimation, ACTOR_PLAYER, 0, 65544)
    Call(FlyToGoal, ACTOR_PLAYER, 0, 0, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65545)
    ExecWait(TTYD64_battle_move_earthquake_jump_EVS_802A264C)
    ExecWait(TTYD64_battle_move_earthquake_jump_EVS_802A2EC8)
    Return
    End
};

EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A1F40 = {
    Call(PlayerYieldTurn)
    Call(SetBattleFlagBits, BS_FLAGS1_EXECUTING_MOVE, 0)
    Call(UseBattleCamPreset, 29)
    Call(func_802693F0)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Set(LVar1, 0)
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 65545)
    Call(SetActorJumpGravity, ACTOR_PLAYER, Float(1.0))
    Call(battle_move_jump_attack_CalcJumpReboundTime)
    Call(PlayerHopToGoal, LVar0, 0, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65545)
    Wait(1)
    Call(AddGoalPos, ACTOR_PLAYER, -20, 0, 0)
    Call(PlayerHopToGoal, 6, 0, 2)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65545)
    Wait(2)
    Call(EnablePlayerBlur, -1)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Return
    End
};

EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A212C = {
    Call(SetGoalToFirstTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(GetGoalPos, ACTOR_PLAYER, LVar3, LVar4, LVar5)
    Sub(LVar3, Float(70.0))
    IfLt(LVar0, LVar3)
        Set(LVar3, LVar0)
    EndIf
    Call(SetGoalPos, ACTOR_PLAYER, LVar3, LVar4, LVar5)
    Call(UseBattleCamPreset, 26)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(5.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(CancelablePlayerRunToGoal, 0, LVar0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    ExecWait(TTYD64_battle_move_earthquake_jump_EVS_802A2F70)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65542)
    Return
    End
};

EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A22A0 = {
    Call(LoadActionCommand, ACTION_COMMAND_JUMP)
    Call(action_command_jump_init)
    ExecWait(TTYD64_battle_move_earthquake_jump_EVS_802A212C)
    ExecWait(TTYD64_battle_move_earthquake_jump_EVS_802A1000)
    Call(action_command_jump_start, LVarA, 3)
    Call(UseBattleCamPreset, 34)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 65543, 65544, 196608)
    Call(PlayerBasicJumpToGoal, LVarA, 0)
    Return
    End
};

EvtScript TTYD64_battle_move_earthquake_jump_EVS_UseMove = {
    ExecWait(TTYD64_battle_move_earthquake_jump_EVS_802A1140)
    Return
    End
};

EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A264C = {
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 0)
        Wait(4)
        Goto(0)
    EndIf
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishAddCount, LVar0)
        Set(LVarA, 0)
        ExecWait(TTYD64_Script_DoStylishFX)
        Call(TTYD64_SetMoveScratch, TTYD64_MSI_EARTHQUAKE_JUMP, TTYD64_MS_FLAG, 0)
        Thread
            Call(SetActorRotationOffset, ACTOR_PLAYER, 0, 16, 0)
            Loop(0)
                Call(GetActorRotation, 0, LVar0, LVar1, LVar2)
                Add(LVar2, 45)
                IfGt(LVar2, 360)
                    Set(LVar2, 0)
                EndIf
                Call(SetActorRotation, ACTOR_PLAYER, LVar0, LVar1, LVar2)
                Call(TTYD64_GetMoveScratch, TTYD64_MSI_EARTHQUAKE_JUMP, TTYD64_MS_FLAG, LVar0)
                IfEq(LVar0, 1)
                    Call(SetActorRotation, ACTOR_PLAYER, 0, 0, 0)
                    Call(SetActorRotationOffset, ACTOR_PLAYER, 0, 0, 0)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        EndThread
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Call(SetAnimation, ACTOR_PLAYER, 0, 65557)
        Call(SetActorSpeed, ACTOR_PLAYER, Float(5.0))
        Call(SetGoalToHome, ACTOR_SELF)
        Thread
            Wait(1)
            Exec(TTYD64_Script_InitTracker)
            Loop(0)
                Call(GetDistanceToGoal, ACTOR_SELF, LVar0)
                IfLe(LVar0, 40)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                Wait(1)
                Goto(1)
            EndIf
            Loop(3)
                Call(GetAnimation, ACTOR_SELF, 0, LVar0)
                IfNe(LVar0, 65557)
                    BreakLoop
                EndIf
                Call(TTYD64_StylishPressed, LVar0)
                IfEq(LVar0, 0)
                    ExecWait(TTYD64_Script_TimingTutor)
                Else
                    Wait(1)
                    Goto(2)
                EndIf
                Wait(1)
            EndLoop
            Label(1)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Label(2)
        EndThread
        Call(FlyToGoal, ACTOR_SELF, 0, 0, 0)
        Call(TTYD64_SetMoveScratch, TTYD64_MSI_EARTHQUAKE_JUMP, TTYD64_MS_FLAG, 1)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishAddCount, LVar0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65567)
            Wait(35)
        Else
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
            Wait(12)
        EndIf
    EndIf
    Label(0)
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Return
    End
};

EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A2C4C = {
    Call(SetJumpAnimations, ACTOR_PLAYER, 0, 0, 0, 65548)
    Call(PlayerLandJump)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65548)
    Wait(2)
    ChildThread
        Call(ShakeCam, 1, 0, 5, Float(1.0))
    EndChildThread
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_TRIP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65584)
    Wait(10)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65585)
    Wait(20)
    Call(SetBattleFlagBits, BS_FLAGS1_EXECUTING_MOVE, 0)
    Call(UseBattleCamPreset, 3)
    Call(func_802693F0)
    Call(EnablePlayerBlur, -1)
    Call(PlayerYieldTurn)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Return
    End
};

EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A2EC8 = {
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Wait(5)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Call(UseBattleCamPreset, 2)
    Return
    End
};

EvtScript TTYD64_battle_move_earthquake_jump_EVS_802A2F70 = {
    Call(SetAnimation, ACTOR_PLAYER, 0, 65542)
    Loop(5)
        Call(CheckButtonPress, 32768, LVar0)
        IfEq(LVar0, 1)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_earthquake_jump(void) {
    Mod_ReplaceScript(
        "TTYD64", &battle_move_earthquake_jump_EVS_UseMove, &TTYD64_battle_move_earthquake_jump_EVS_UseMove
    );
}
