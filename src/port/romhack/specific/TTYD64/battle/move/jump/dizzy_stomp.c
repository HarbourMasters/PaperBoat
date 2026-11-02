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

extern EvtScript battle_move_dizzy_stomp_EVS_UseMove;
API_CALLABLE(AddGoalPos);
API_CALLABLE(CheckButtonDown);
API_CALLABLE(EnablePlayerBlur);
API_CALLABLE(GetActionCommandMode);
API_CALLABLE(GetActionProgress);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetPlayerActionQuality);
API_CALLABLE(GetSmashActionQuality);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerDamageEnemy);
API_CALLABLE(PlayerHopToGoal);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(PlayerTestEnemy);
API_CALLABLE(PlayerYieldTurn);
API_CALLABLE(SetActionCommandMode);
API_CALLABLE(SetActionProgress);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorRotationOffset);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetBattleCamOffsetY);
API_CALLABLE(SetDamageSource);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowActionHud);
API_CALLABLE(StartRumble);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(action_command_hammer_init);
API_CALLABLE(action_command_hammer_start);
API_CALLABLE(battle_move_hammer_charge_1_IsBerserkerEquipped);
API_CALLABLE(battle_move_hammer_charge_1_ShouldMovesAutoSucceed);
API_CALLABLE(func_802693F0);
EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A1000;
EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A1E60;
EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A2368;
EvtScript TTYD64_battle_move_dizzy_stomp_EVS_UseMove;
EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A261C;
EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A2C98;
EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A30C8;
EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A34F8;
EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A367C;
EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A3800;
EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A38EC;
EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A39D4;
EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A3AB0;

// clang-format off
EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A1000 = {
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Wait(1)
        Goto(0)
    EndIf
    Loop(3)
        ExecWait(TTYD64_Script_TimingTutor)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Call(TTYD64_StylishAddCount, LVar0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
            Sub(LVar0, 25)
            Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
            Call(SetActorRotationOffset, ACTOR_PLAYER, 0, 22, 0)
            Thread
                Call(MakeLerp, 0, 180, 7, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, ACTOR_PLAYER, 0, 0, LVar0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
                Call(MakeLerp, -180, 0, 7, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, ACTOR_PLAYER, 0, 0, LVar0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
                Call(SetActorRotation, ACTOR_PLAYER, 0, 0, 0)
            EndThread
            Call(SetActorJumpGravity, ACTOR_PLAYER, Float(1.0))
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
            Thread
                Exec(TTYD64_Script_InitTracker)
                Loop(8)
                    Call(TTYD64_StylishPressed, LVar0)
                    IfEq(LVar0, 1)
                        Call(TTYD64_StylishDisarm)
                        Call(TTYD64_StylishConsume)
                        Goto(1)
                    EndIf
                    Wait(1)
                EndLoop
                Loop(3)
                    ExecWait(TTYD64_Script_TimingTutor)
                    Call(TTYD64_StylishPressed, LVar0)
                    Wait(1)
                EndLoop
                Label(1)
            EndThread
            Call(SetJumpAnimations, ACTOR_SELF, 0, 65538, 65538, 65538)
            Call(PlayerHopToGoal, 15, 0, 2)
            Call(SetActorRotationOffset, ACTOR_PLAYER, 0, 0, 0)
            Label(2)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 0)
                Wait(1)
                Goto(0)
            EndIf
            IfEq(LVar0, 1)
                Call(TTYD64_StylishDisarm)
                Call(TTYD64_StylishConsume)
                Call(TTYD64_StylishAddCount, LVar0)
                Set(LVarA, 0)
                ExecWait(TTYD64_Script_DoStylishFX)
                Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
                Sub(LVar0, 30)
                Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
                Call(SetActorRotationOffset, ACTOR_PLAYER, 0, 22, 0)
                SetTimescale(Float(1.0996))
                Thread
                    Call(MakeLerp, 0, 180, 7, 0)
                    Loop(0)
                        Call(UpdateLerp)
                        Call(SetActorRotation, ACTOR_PLAYER, 0, 0, LVar0)
                        Wait(1)
                        IfEq(LVar1, 0)
                            BreakLoop
                        EndIf
                    EndLoop
                    Call(MakeLerp, -180, 0, 7, 0)
                    Loop(0)
                        Call(UpdateLerp)
                        Call(SetActorRotation, ACTOR_PLAYER, 0, 0, LVar0)
                        Wait(1)
                        IfEq(LVar1, 0)
                            BreakLoop
                        EndIf
                    EndLoop
                    Call(SetActorRotation, ACTOR_PLAYER, 0, 0, 0)
                EndThread
                Call(SetActorJumpGravity, ACTOR_PLAYER, Float(1.0))
                Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
                Thread
                    Wait(6)
                    Exec(TTYD64_Script_InitTracker)
                    Loop(9)
                        Call(TTYD64_StylishPressed, LVar0)
                        IfEq(LVar0, 1)
                            Call(TTYD64_StylishDisarm)
                            Call(TTYD64_StylishConsume)
                            Goto(3)
                        EndIf
                        Wait(1)
                    EndLoop
                    Loop(2)
                        ExecWait(TTYD64_Script_TimingTutor)
                        Call(TTYD64_StylishPressed, LVar0)
                        Wait(1)
                    EndLoop
                    Label(3)
                EndThread
                Call(PlayerHopToGoal, 20, 0, 2)
                Call(SetActorRotationOffset, ACTOR_PLAYER, 0, 0, 0)
                SetTimescale(Float(1.0))
                Label(4)
                Call(TTYD64_StylishPressed, LVar0)
                IfEq(LVar0, 0)
                    Wait(1)
                    Goto(0)
                EndIf
                IfEq(LVar0, 1)
                    Call(TTYD64_StylishDisarm)
                    Call(TTYD64_StylishConsume)
                    Call(TTYD64_StylishAddCount, LVar0)
                    Set(LVarA, 0)
                    ExecWait(TTYD64_Script_DoStylishFX)
                    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
                    Sub(LVar0, 35)
                    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
                    Call(SetActorRotationOffset, ACTOR_PLAYER, 0, 22, 0)
                    SetTimescale(Float(1.2998))
                    Thread
                        Call(MakeLerp, 0, 180, 10, 0)
                        Loop(0)
                            Call(UpdateLerp)
                            Call(SetActorRotation, ACTOR_PLAYER, LVar0, 0, LVar0)
                            Wait(1)
                            IfEq(LVar1, 0)
                                BreakLoop
                            EndIf
                        EndLoop
                        Call(MakeLerp, -180, 0, 10, 0)
                        Loop(0)
                            Call(UpdateLerp)
                            Call(SetActorRotation, ACTOR_PLAYER, LVar0, 0, LVar0)
                            Wait(1)
                            IfEq(LVar1, 0)
                                BreakLoop
                            EndIf
                        EndLoop
                        Call(SetActorRotation, ACTOR_PLAYER, 0, 0, 0)
                    EndThread
                    Call(SetActorJumpGravity, ACTOR_PLAYER, Float(0.7998))
                    Call(SetAnimation, ACTOR_PLAYER, 0, 65581)
                    Thread
                        Wait(13)
                        Exec(TTYD64_Script_InitTracker)
                        Loop(9)
                            Call(TTYD64_StylishPressed, LVar0)
                            IfEq(LVar0, 1)
                                Call(TTYD64_StylishDisarm)
                                Call(TTYD64_StylishConsume)
                                Goto(5)
                            EndIf
                            Wait(1)
                        EndLoop
                        Loop(2)
                            ExecWait(TTYD64_Script_TimingTutor)
                            Call(TTYD64_StylishPressed, LVar0)
                            Wait(1)
                        EndLoop
                        Label(5)
                    EndThread
                    Call(PlayerHopToGoal, 30, 0, 2)
                    Call(SetActorRotationOffset, ACTOR_PLAYER, 0, 0, 0)
                    SetTimescale(Float(1.0))
                    Label(6)
                    Call(TTYD64_StylishPressed, LVar0)
                    IfEq(LVar0, 0)
                        Wait(1)
                        Goto(0)
                    EndIf
                    IfEq(LVar0, 1)
                        Call(TTYD64_StylishAddCount, LVar0)
                        Set(LVarA, 0)
                        ExecWait(TTYD64_Script_DoStylishFX)
                        Call(SetAnimation, ACTOR_PLAYER, 0, 65586)
                        BreakLoop
                        Wait(15)
                    EndIf
                EndIf
            EndIf
        EndIf
        Wait(1)
    EndLoop
    Label(0)
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Return
    End
};

EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A1E60 = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Call(action_command_hammer_init)
    ExecWait(TTYD64_battle_move_dizzy_stomp_EVS_802A3AB0)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    ExecWait(TTYD64_battle_move_dizzy_stomp_EVS_802A2368)
    Call(PlayerTestEnemy, LVar0, 64, 0, 0, 0, 16)
    Call(UseBattleCamPreset, 43)
    Call(SetBattleCamOffsetY, 8)
    Call(InitTargetIterator)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196622)
    Wait(4)
    Call(battle_move_hammer_charge_1_IsBerserkerEquipped)
    IfNe(LVar0, 0)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196623)
        Call(GetActionCommandMode, LVar0)
        IfLt(LVar0, 2)
            Call(battle_move_hammer_charge_1_ShouldMovesAutoSucceed)
            IfEq(LVar0, 0)
                Loop(45)
                    Wait(1)
                    Call(CheckButtonDown, 262144, LVar0)
                    IfNe(LVar0, 0)
                        BreakLoop
                    EndIf
                EndLoop
            EndIf
        EndIf
        Add(LVarD, 6)
        Thread
            Wait(30)
            Call(TTYD64_StylishSetCount, 0)
            Exec(TTYD64_Script_InitTracker)
        EndThread
        Call(action_command_hammer_start, 0, LVarD, 3)
        Call(SetActionProgress, 0)
        Set(LVar1, 0)
        Loop(30)
            Wait(1)
            Call(GetActionProgress, LVar0)
            IfNe(LVar0, 0)
                IfNe(LVar1, 1)
                    Call(SetAnimation, ACTOR_PLAYER, 0, 196624)
                    Set(LVar1, 1)
                EndIf
            EndIf
            Call(CheckButtonDown, 262144, LVar0)
            IfEq(LVar0, 0)
                BreakLoop
            EndIf
        EndLoop
        Label(0)
        Call(GetActionCommandMode, LVar0)
        IfLt(LVar0, 2)
            Wait(1)
            Call(GetSmashActionQuality, LVar0)
            IfEq(LVar0, 0)
                Goto(0)
            EndIf
        EndIf
    Else
        Call(action_command_hammer_start, 0, LVar1, 3)
        Call(SetActionProgress, 0)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196623)
        Sub(LVar1, 10)
        Wait(LVar1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196624)
        Wait(5)
    EndIf
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
    Call(SetAnimation, ACTOR_PLAYER, 0, 196625)
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8469)
    Wait(3)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196626)
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8472)
    Return
    End
};

EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A2368 = {
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    Set(LVar1, 0)
    Loop(10)
        Call(CheckButtonDown, 262144, LVar0)
        IfEq(LVar0, 1)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
            BreakLoop
        EndIf
        Wait(1)
        Add(LVar1, 1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196621)
    EndLoop
    Call(SetAnimation, ACTOR_PLAYER, 0, 196621)
    Switch(LVar1)
        CaseLt(3)
            Wait(4)
        CaseLt(5)
            Wait(3)
        CaseLt(7)
            Wait(2)
        CaseLt(9)
            Wait(1)
        CaseLt(11)
            Wait(0)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_move_dizzy_stomp_EVS_UseMove = {
    ExecWait(TTYD64_battle_move_dizzy_stomp_EVS_802A261C)
    Return
    End
};

EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A261C = {
    Call(ShowActionHud, 1)
    Call(SetDamageSource, 3)
    Call(TTYD64_GetStackBoost, 378, 1, LVarE, LVarF)
    Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_1_1U, LVar1)
    Switch(LVar1)
        CaseEq(0)
            Set(LVarD, 50)
            Add(LVarE, 1)
            Add(LVarF, 2)
        CaseEq(1)
            Set(LVarD, 50)
            Add(LVarE, 2)
            Add(LVarF, 4)
        CaseGe(2)
            Set(LVarD, 50)
            Add(LVarE, 3)
            Add(LVarF, 6)
    EndSwitch
    Exec(TTYD64_Script_NukeTracker)
    Switch(LVar1)
        CaseEq(0)
            ExecWait(TTYD64_battle_move_dizzy_stomp_EVS_802A1E60)
        CaseEq(1)
            ExecWait(TTYD64_battle_move_dizzy_stomp_EVS_802A30C8)
        CaseEq(2)
            ExecWait(TTYD64_battle_move_dizzy_stomp_EVS_802A2C98)
    EndSwitch
    Call(PlayerTestEnemy, LVar0, 64, 25, 0, LVar9, 16)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_1_1U, LVar1)
            Switch(LVar1)
                CaseEq(0)
                    Call(StartRumble, 8)
                    Thread
                        Call(ShakeCam, 1, 0, 10, Float(1.2998))
                    EndThread
                CaseEq(1)
                    Call(StartRumble, 9)
                    Thread
                        Call(ShakeCam, 1, 0, 10, Float(1.5996))
                    EndThread
                CaseEq(2)
                    Call(StartRumble, 10)
                    Thread
                        Call(ShakeCam, 1, 0, 10, Float(1.9))
                    EndThread
            EndSwitch
        CaseDefault
            Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_1_1U, LVar1)
            Switch(LVar1)
                CaseEq(0)
                    Call(StartRumble, 8)
                    Thread
                        Call(ShakeCam, 1, 0, 2, Float(1.2998))
                    EndThread
                CaseEq(1)
                    Call(StartRumble, 9)
                    Thread
                        Call(ShakeCam, 1, 0, 2, Float(1.5996))
                    EndThread
                CaseEq(2)
                    Call(StartRumble, 10)
                    Thread
                        Call(ShakeCam, 1, 0, 2, Float(1.9))
                    EndThread
            EndSwitch
    EndSwitch
    Call(GetPlayerActionQuality, LVar0)
    IfGt(LVar0, 0)
        Call(UseBattleCamPreset, 44)
        Call(MoveBattleCamOver, 5)
    Else
        Call(UseBattleCamPreset, 44)
        Call(MoveBattleCamOver, 50)
    EndIf
    Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_1_1U, LVar1)
    Switch(LVar1)
        CaseEq(0)
            Call(PlaySoundAtActor, ACTOR_PLAYER, 8458)
        CaseEq(1)
            Call(PlaySoundAtActor, ACTOR_PLAYER, 8459)
        CaseEq(2)
            Call(PlaySoundAtActor, ACTOR_PLAYER, 8460)
    EndSwitch
    Call(PlayerTestEnemy, LVar0, 64, 25, 0, 0, 16)
    IfEq(LVar0, 6)
        ExecWait(TTYD64_battle_move_dizzy_stomp_EVS_802A39D4)
        Return
    EndIf
    Call(GetPlayerActionQuality, LVarA)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(PlayerDamageEnemy, LVar0, 64, 25, (Bytecode) (s32) 0x80040364, LVarF, 112)
        CaseDefault
            Call(PlayerDamageEnemy, LVar0, 64, 25, (Bytecode) (s32) 0x8004034B, LVarE, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(1)
        CaseOrEq(3)
            ExecWait(TTYD64_battle_move_dizzy_stomp_EVS_802A38EC)
        EndCaseGroup
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_move_dizzy_stomp_EVS_802A3800)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A2C98 = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Call(action_command_hammer_init)
    ExecWait(TTYD64_battle_move_dizzy_stomp_EVS_802A3AB0)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    ExecWait(TTYD64_battle_move_dizzy_stomp_EVS_802A367C)
    Call(PlayerTestEnemy, LVar0, 64, 0, 0, 0, 16)
    Call(UseBattleCamPreset, 43)
    Call(SetBattleCamOffsetY, 8)
    Call(InitTargetIterator)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196636)
    Wait(4)
    Call(battle_move_hammer_charge_1_IsBerserkerEquipped)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196637)
        Call(battle_move_hammer_charge_1_ShouldMovesAutoSucceed)
        IfEq(LVar0, 0)
            Loop(45)
                Wait(1)
                Call(CheckButtonDown, 262144, LVar0)
                IfNe(LVar0, 0)
                    BreakLoop
                EndIf
            EndLoop
        EndIf
        Add(LVarD, 6)
        Thread
            Wait(30)
            Call(TTYD64_StylishSetCount, 0)
            Exec(TTYD64_Script_InitTracker)
        EndThread
        Call(action_command_hammer_start, 0, LVarD, 3)
        Call(SetActionProgress, 0)
        Set(LVar1, 0)
        Loop(30)
            Wait(1)
            Call(GetActionProgress, LVar0)
            IfNe(LVar0, 0)
                IfNe(LVar1, 1)
                    Call(SetAnimation, ACTOR_PLAYER, 0, 196638)
                    Set(LVar1, 1)
                EndIf
            EndIf
            Call(CheckButtonDown, 262144, LVar0)
            IfEq(LVar0, 0)
                BreakLoop
            EndIf
        EndLoop
        Label(0)
        Wait(1)
        Call(GetSmashActionQuality, LVar0)
        IfEq(LVar0, 0)
            Goto(0)
        EndIf
    Else
        Call(action_command_hammer_start, 0, LVar1, 3)
        Call(SetActionProgress, 0)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196637)
        Sub(LVar1, 10)
        Wait(LVar1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196638)
        Wait(5)
    EndIf
    Call(SetAnimation, ACTOR_PLAYER, 0, 196639)
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8471)
    Wait(3)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196640)
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8474)
    Return
    End
};

EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A30C8 = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Call(action_command_hammer_init)
    ExecWait(TTYD64_battle_move_dizzy_stomp_EVS_802A3AB0)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    ExecWait(TTYD64_battle_move_dizzy_stomp_EVS_802A34F8)
    Call(PlayerTestEnemy, LVar0, 64, 0, 0, 0, 16)
    Call(UseBattleCamPreset, 43)
    Call(SetBattleCamOffsetY, 8)
    Call(InitTargetIterator)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196629)
    Wait(4)
    Call(battle_move_hammer_charge_1_IsBerserkerEquipped)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196630)
        Call(battle_move_hammer_charge_1_ShouldMovesAutoSucceed)
        IfEq(LVar0, 0)
            Loop(45)
                Wait(1)
                Call(CheckButtonDown, 262144, LVar0)
                IfNe(LVar0, 0)
                    BreakLoop
                EndIf
            EndLoop
        EndIf
        Add(LVarD, 6)
        Thread
            Wait(30)
            Call(TTYD64_StylishSetCount, 0)
            Exec(TTYD64_Script_InitTracker)
        EndThread
        Call(action_command_hammer_start, 0, LVarD, 3)
        Call(SetActionProgress, 0)
        Set(LVar1, 0)
        Loop(30)
            Wait(1)
            Call(GetActionProgress, LVar0)
            IfNe(LVar0, 0)
                IfNe(LVar1, 1)
                    Call(SetAnimation, ACTOR_PLAYER, 0, 196631)
                    Set(LVar1, 1)
                EndIf
            EndIf
            Call(CheckButtonDown, 262144, LVar0)
            IfEq(LVar0, 0)
                BreakLoop
            EndIf
        EndLoop
        Label(0)
        Wait(1)
        Call(GetSmashActionQuality, LVar0)
        IfEq(LVar0, 0)
            Goto(0)
        EndIf
    Else
        Call(action_command_hammer_start, 0, LVar1, 3)
        Call(SetActionProgress, 0)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196630)
        Sub(LVar1, 10)
        Wait(LVar1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196631)
        Wait(5)
    EndIf
    Call(SetAnimation, ACTOR_PLAYER, 0, 196632)
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8470)
    Wait(3)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196633)
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8473)
    Return
    End
};

EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A34F8 = {
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    Set(LVar1, 0)
    Loop(10)
        Call(CheckButtonDown, 262144, LVar0)
        IfEq(LVar0, 1)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
            BreakLoop
        EndIf
        Wait(1)
        Add(LVar1, 1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196628)
    EndLoop
    Call(SetAnimation, ACTOR_PLAYER, 0, 196628)
    Switch(LVar1)
        CaseLt(3)
            Wait(4)
        CaseLt(5)
            Wait(3)
        CaseLt(7)
            Wait(2)
        CaseLt(9)
            Wait(1)
        CaseLt(11)
            Wait(0)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A367C = {
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    Set(LVar1, 0)
    Loop(10)
        Call(CheckButtonDown, 262144, LVar0)
        IfEq(LVar0, 1)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
            BreakLoop
        EndIf
        Wait(1)
        Add(LVar1, 1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196635)
    EndLoop
    Call(SetAnimation, ACTOR_PLAYER, 0, 196635)
    Switch(LVar1)
        CaseLt(3)
            Wait(4)
        CaseLt(5)
            Wait(3)
        CaseLt(7)
            Wait(2)
        CaseLt(9)
            Wait(1)
        CaseLt(11)
            Wait(0)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A3800 = {
    Call(PlayerYieldTurn)
    Call(UseBattleCamPreset, 4)
    Call(MoveBattleCamOver, 5)
    Call(func_802693F0)
    Wait(20)
    Call(EnablePlayerBlur, -1)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Wait(5)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Return
    End
};

EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A38EC = {
    Call(PlayerYieldTurn)
    Call(UseBattleCamPreset, 29)
    Call(func_802693F0)
    ExecWait(TTYD64_battle_move_dizzy_stomp_EVS_802A1000)
    Wait(20)
    Call(EnablePlayerBlur, -1)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Wait(5)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Return
    End
};

EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A39D4 = {
    Call(PlayerYieldTurn)
    Call(UseBattleCamPreset, 29)
    Call(func_802693F0)
    Wait(20)
    Call(EnablePlayerBlur, -1)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Wait(5)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Return
    End
};

EvtScript TTYD64_battle_move_dizzy_stomp_EVS_802A3AB0 = {
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 32)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(UseBattleCamPreset, 26)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(5.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_dizzy_stomp(void) {
    Mod_ReplaceScript("TTYD64", &battle_move_dizzy_stomp_EVS_UseMove, &TTYD64_battle_move_dizzy_stomp_EVS_UseMove);
}
