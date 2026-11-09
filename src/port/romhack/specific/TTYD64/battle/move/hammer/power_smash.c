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

extern EvtScript battle_move_power_smash_EVS_UseMove;
extern EvtScript battle_move_power_smash_EVS_UseUltraHammer;
extern EvtScript battle_move_power_smash_EVS_UseSuperHammer;
extern EvtScript battle_move_power_smash_EVS_UseBasicHammer;
extern EvtScript battle_move_power_smash_EVS_HammerSupport_ReturnHome_SmashSuccess;
extern EvtScript battle_move_power_smash_EVS_HammerSupport_BasicRaiseDelay;
extern EvtScript battle_move_power_smash_EVS_HammerSupport_SmashApproach;
extern EvtScript battle_move_power_smash_EVS_HammerSupport_SuperRaiseDelay;
extern EvtScript battle_move_power_smash_EVS_HammerSupport_UltraRaiseDelay;
extern EvtScript battle_move_power_smash_EVS_UseMove_Impl;
API_CALLABLE(AddGoalPos);
API_CALLABLE(CheckButtonDown);
API_CALLABLE(EnablePlayerBlur);
API_CALLABLE(GetActionCommandMode);
API_CALLABLE(GetActionProgress);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetSmashActionQuality);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlaySoundAtActor);
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
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(ShowActionHud);
API_CALLABLE(TTYD64_Player_AC_802A9000);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(action_command_hammer_start);
API_CALLABLE(battle_move_power_smash_IsBerserkerEquipped);
API_CALLABLE(battle_move_power_smash_ShouldMovesAutoSucceed);
API_CALLABLE(func_802693F0);
EvtScript TTYD64_battle_move_power_smash_EVS_HammerSupport_ReturnHome_SmashSuccess;
EvtScript TTYD64_battle_move_power_smash_EVS_UseBasicHammer;
EvtScript TTYD64_battle_move_power_smash_EVS_UseSuperHammer;
EvtScript TTYD64_battle_move_power_smash_EVS_UseUltraHammer;
EvtScript TTYD64_battle_move_power_smash_EVS_802A3044;
EvtScript TTYD64_battle_move_power_smash_EVS_802A355C;
EvtScript TTYD64_battle_move_power_smash_EVS_UseMove;
EvtScript TTYD64_battle_move_power_smash_EVS_802A45CC;

// clang-format off
EvtScript TTYD64_battle_move_power_smash_EVS_HammerSupport_ReturnHome_SmashSuccess = {
    Call(PlayerYieldTurn)
    Call(UseBattleCamPreset, 4)
    Call(MoveBattleCamOver, 5)
    Jump(TTYD64_battle_move_power_smash_EVS_802A355C)
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

EvtScript TTYD64_battle_move_power_smash_EVS_UseBasicHammer = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Exec(TTYD64_battle_move_power_smash_EVS_802A45CC)
    ExecWait(battle_move_power_smash_EVS_HammerSupport_SmashApproach)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    ExecWait(battle_move_power_smash_EVS_HammerSupport_BasicRaiseDelay)
    Call(PlayerTestEnemy, LVar0, 64, 0, 0, 0, 16)
    Call(UseBattleCamPreset, 43)
    Call(SetBattleCamOffsetY, 8)
    Call(InitTargetIterator)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196622)
    Wait(4)
    Call(battle_move_power_smash_IsBerserkerEquipped)
    IfNe(LVar0, 0)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196623)
        Call(GetActionCommandMode, LVar0)
        IfLt(LVar0, 2)
            Call(battle_move_power_smash_ShouldMovesAutoSucceed)
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
        ExecGetTID(TTYD64_battle_move_power_smash_EVS_802A3044, 0)
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

EvtScript TTYD64_battle_move_power_smash_EVS_UseSuperHammer = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Exec(TTYD64_battle_move_power_smash_EVS_802A45CC)
    ExecWait(battle_move_power_smash_EVS_HammerSupport_SmashApproach)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    ExecWait(battle_move_power_smash_EVS_HammerSupport_SuperRaiseDelay)
    Call(PlayerTestEnemy, LVar0, 64, 0, 0, 0, 16)
    Call(UseBattleCamPreset, 43)
    Call(SetBattleCamOffsetY, 8)
    Call(InitTargetIterator)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196629)
    Wait(4)
    Call(battle_move_power_smash_IsBerserkerEquipped)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196630)
        Call(battle_move_power_smash_ShouldMovesAutoSucceed)
        IfEq(LVar0, 0)
            Loop(45)
                Wait(1)
                Call(CheckButtonDown, 262144, LVar0)
                IfNe(LVar0, 0)
                    BreakLoop
                EndIf
            EndLoop
        EndIf
        ExecGetTID(TTYD64_battle_move_power_smash_EVS_802A3044, 0)
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

EvtScript TTYD64_battle_move_power_smash_EVS_UseUltraHammer = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Exec(TTYD64_battle_move_power_smash_EVS_802A45CC)
    ExecWait(battle_move_power_smash_EVS_HammerSupport_SmashApproach)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    ExecWait(battle_move_power_smash_EVS_HammerSupport_UltraRaiseDelay)
    Call(PlayerTestEnemy, LVar0, 64, 0, 0, 0, 16)
    Call(UseBattleCamPreset, 43)
    Call(SetBattleCamOffsetY, 8)
    Call(InitTargetIterator)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196636)
    Wait(4)
    Call(battle_move_power_smash_IsBerserkerEquipped)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196637)
        Call(battle_move_power_smash_ShouldMovesAutoSucceed)
        IfEq(LVar0, 0)
            Loop(45)
                Wait(1)
                Call(CheckButtonDown, 262144, LVar0)
                IfNe(LVar0, 0)
                    BreakLoop
                EndIf
            EndLoop
        EndIf
        ExecGetTID(TTYD64_battle_move_power_smash_EVS_802A3044, 0)
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

EvtScript TTYD64_battle_move_power_smash_EVS_802A3044 = {
    Add(LVarD, 6)
    Thread
        Wait(30)
        Call(TTYD64_StylishSetCount, 0)
        Exec(TTYD64_Script_InitTracker)
    EndThread
    Return
    End
};

EvtScript TTYD64_battle_move_power_smash_EVS_802A355C = {
    Call(func_802693F0)
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

EvtScript TTYD64_battle_move_power_smash_EVS_UseMove = {
    Call(EnablePlayerBlur, 1)
    Call(ShowActionHud, 1)
    Call(TTYD64_GetStackBoost, 292, 1, LVarE, LVarF)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            Set(LVarD, 45)
            Add(LVarE, 3)
            Add(LVarF, 4)
            ExecWait(battle_move_power_smash_EVS_UseMove_Impl)
        CaseEq(1)
            Set(LVarD, 45)
            Add(LVarE, 4)
            Add(LVarF, 6)
            ExecWait(battle_move_power_smash_EVS_UseMove_Impl)
        CaseEq(2)
            Set(LVarD, 45)
            Add(LVarE, 5)
            Add(LVarF, 8)
            ExecWait(battle_move_power_smash_EVS_UseMove_Impl)
    EndSwitch
    Call(EnablePlayerBlur, 0)
    Return
    End
};

EvtScript TTYD64_battle_move_power_smash_EVS_802A45CC = {
    Call(TTYD64_Player_AC_802A9000)
    Exec(TTYD64_Script_NukeTracker)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_power_smash(void) {
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_smash_EVS_HammerSupport_ReturnHome_SmashSuccess,
        &TTYD64_battle_move_power_smash_EVS_HammerSupport_ReturnHome_SmashSuccess
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_smash_EVS_UseBasicHammer, &TTYD64_battle_move_power_smash_EVS_UseBasicHammer
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_smash_EVS_UseSuperHammer, &TTYD64_battle_move_power_smash_EVS_UseSuperHammer
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_smash_EVS_UseUltraHammer, &TTYD64_battle_move_power_smash_EVS_UseUltraHammer
    );
    Mod_ReplaceScript("TTYD64", &battle_move_power_smash_EVS_UseMove, &TTYD64_battle_move_power_smash_EVS_UseMove);
}
