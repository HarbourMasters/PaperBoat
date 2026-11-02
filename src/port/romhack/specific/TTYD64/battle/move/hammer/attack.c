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

extern EvtScript battle_move_hammer_attack_EVS_HammerSupport_SmashApproach;
extern EvtScript battle_move_hammer_attack_EVS_UseBerserker_Impl;
extern EvtScript battle_move_hammer_attack_EVS_FirstStrike;
extern EvtScript battle_move_hammer_attack_EVS_UseMove_Impl;
extern EvtScript battle_move_hammer_attack_EVS_HammerSupport_ReturnHome_SmashSuccess;
extern EvtScript battle_move_hammer_attack_EVS_HammerSupport_BasicRaiseDelay;
extern EvtScript battle_move_hammer_attack_EVS_HammerSupport_ReturnHome_SmashMiss;
extern EvtScript battle_move_hammer_attack_EVS_HammerSupport_SuperRaiseDelay;
extern EvtScript battle_move_hammer_attack_EVS_HammerSupport_UltraRaiseDelay;
extern EvtScript battle_move_hammer_attack_EVS_UseMove;
API_CALLABLE(AddGoalPos);
API_CALLABLE(CheckButtonDown);
API_CALLABLE(EnablePlayerBlur);
API_CALLABLE(GetActionCommandMode);
API_CALLABLE(GetActionProgress);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetBattlePhase);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetMashActionQuality);
API_CALLABLE(GetMenuSelection);
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
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(ShakeCam);
API_CALLABLE(StartRumble);
API_CALLABLE(TTYD64_Player_AC_802A9000);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(action_command_hammer_start);
API_CALLABLE(battle_move_hammer_attack_IsBerserkerEquipped);
API_CALLABLE(battle_move_hammer_attack_ShouldMovesAutoSucceed);
API_CALLABLE(func_802693F0);
EvtScript TTYD64_battle_move_hammer_attack_EVS_802A10A4;
EvtScript TTYD64_battle_move_hammer_attack_EVS_HammerSupport_ReturnHome_SmashSuccess;
EvtScript TTYD64_battle_move_hammer_attack_EVS_802A1B40;
EvtScript TTYD64_battle_move_hammer_attack_EVS_802A21DC;
EvtScript TTYD64_battle_move_hammer_attack_EVS_UseMove_Impl;
EvtScript TTYD64_battle_move_hammer_attack_EVS_FirstStrike;
EvtScript TTYD64_battle_move_hammer_attack_EVS_802A36B8;
EvtScript TTYD64_battle_move_hammer_attack_EVS_802A3AC8;
EvtScript TTYD64_battle_move_hammer_attack_EVS_UseBerserker_Impl;
EvtScript TTYD64_battle_move_hammer_attack_EVS_802A42E4;
EvtScript TTYD64_battle_move_hammer_attack_EVS_HammerSupport_SmashApproach;

// clang-format off
EvtScript TTYD64_battle_move_hammer_attack_EVS_802A10A4 = {
    Add(LVarD, 6)
    Thread
        Wait(30)
        Call(TTYD64_StylishSetCount, 0)
        Exec(TTYD64_Script_InitTracker)
    EndThread
    Return
    End
};

EvtScript TTYD64_battle_move_hammer_attack_EVS_HammerSupport_ReturnHome_SmashSuccess = {
    Call(PlayerYieldTurn)
    Call(UseBattleCamPreset, 4)
    Call(MoveBattleCamOver, 5)
    Call(func_802693F0)
    Jump(TTYD64_battle_move_hammer_attack_EVS_802A1B40)
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

EvtScript TTYD64_battle_move_hammer_attack_EVS_802A1B40 = {
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
                Call(SetAnimation, ACTOR_PLAYER, 0, 65567)
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
            Call(SetActorJumpGravity, ACTOR_PLAYER, Float(0.7998))
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
            Call(SetJumpAnimations, ACTOR_SELF, 0, 65567, 65567, 65567)
            Call(PlayerHopToGoal, 15, 0, 2)
            Call(SetActorRotationOffset, ACTOR_PLAYER, 0, 0, 0)
            Label(2)
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
                Wait(15)
                BreakLoop
            EndIf
        EndIf
        Wait(1)
    EndLoop
    Label(0)
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Wait(17)
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

EvtScript TTYD64_battle_move_hammer_attack_EVS_802A21DC = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Exec(TTYD64_battle_move_hammer_attack_EVS_802A3AC8)
    ExecWait(TTYD64_battle_move_hammer_attack_EVS_HammerSupport_SmashApproach)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    ExecWait(battle_move_hammer_attack_EVS_HammerSupport_UltraRaiseDelay)
    Call(PlayerTestEnemy, LVar0, 64, 0, 0, 0, 16)
    Call(UseBattleCamPreset, 43)
    Call(SetBattleCamOffsetY, 8)
    Call(GetBattlePhase, LVar0)
    IfNe(LVar0, 1)
        Call(InitTargetIterator)
    EndIf
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196636)
    Wait(4)
    Call(battle_move_hammer_attack_IsBerserkerEquipped)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196637)
        Call(battle_move_hammer_attack_ShouldMovesAutoSucceed)
        IfEq(LVar0, 0)
            Loop(45)
                Wait(1)
                Call(CheckButtonDown, 262144, LVar0)
                IfNe(LVar0, 0)
                    BreakLoop
                EndIf
            EndLoop
        EndIf
        ExecGetTID(TTYD64_battle_move_hammer_attack_EVS_802A10A4, 0)
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

EvtScript TTYD64_battle_move_hammer_attack_EVS_UseMove_Impl = {
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            ExecWait(TTYD64_battle_move_hammer_attack_EVS_802A42E4)
        CaseEq(1)
            ExecWait(TTYD64_battle_move_hammer_attack_EVS_802A36B8)
        CaseEq(2)
            ExecWait(TTYD64_battle_move_hammer_attack_EVS_802A21DC)
    EndSwitch
    Call(GetMashActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar1)
                CaseEq(0)
                    Call(StartRumble, 7)
                    Thread
                        Call(ShakeCam, 1, 0, 10, Float(1.2998))
                    EndThread
                CaseEq(1)
                    Call(StartRumble, 8)
                    Thread
                        Call(ShakeCam, 1, 0, 10, Float(1.5996))
                    EndThread
                CaseEq(2)
                    Call(StartRumble, 9)
                    Thread
                        Call(ShakeCam, 1, 0, 10, Float(1.9))
                    EndThread
            EndSwitch
        CaseDefault
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar1)
                CaseEq(0)
                    Call(StartRumble, 7)
                    Thread
                        Call(ShakeCam, 1, 0, 2, Float(1.2998))
                    EndThread
                CaseEq(1)
                    Call(StartRumble, 8)
                    Thread
                        Call(ShakeCam, 1, 0, 2, Float(1.5996))
                    EndThread
                CaseEq(2)
                    Call(StartRumble, 9)
                    Thread
                        Call(ShakeCam, 1, 0, 2, Float(1.9))
                    EndThread
            EndSwitch
    EndSwitch
    Call(UseBattleCamPreset, 44)
    Wait(1)
    Call(PlayerTestEnemy, LVar0, 64, 25, 0, 0, 16)
    IfEq(LVar0, 6)
        ExecWait(battle_move_hammer_attack_EVS_HammerSupport_ReturnHome_SmashMiss)
        Return
    EndIf
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar1)
                CaseEq(0)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_NORMAL)
                CaseEq(1)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_SILENT)
                CaseEq(2)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_SILENT)
            EndSwitch
            Call(PlayerDamageEnemy, LVar0, 64, 25, 0, LVarF, 112)
        CaseDefault
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar1)
                CaseEq(0)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_NORMAL)
                CaseEq(1)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_SILENT)
                CaseEq(2)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_SILENT)
            EndSwitch
            Call(PlayerDamageEnemy, LVar0, 64, 25, 0, LVarE, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(1)
        CaseOrEq(3)
            ExecWait(TTYD64_battle_move_hammer_attack_EVS_HammerSupport_ReturnHome_SmashSuccess)
        EndCaseGroup
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(battle_move_hammer_attack_EVS_HammerSupport_ReturnHome_SmashMiss)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_move_hammer_attack_EVS_FirstStrike = {
    ExecWait(battle_move_hammer_attack_EVS_UseMove)
    Return
    End
};

EvtScript TTYD64_battle_move_hammer_attack_EVS_802A36B8 = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Exec(TTYD64_battle_move_hammer_attack_EVS_802A3AC8)
    ExecWait(TTYD64_battle_move_hammer_attack_EVS_HammerSupport_SmashApproach)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    ExecWait(battle_move_hammer_attack_EVS_HammerSupport_SuperRaiseDelay)
    Call(PlayerTestEnemy, LVar0, 64, 0, 0, 0, 16)
    Call(UseBattleCamPreset, 43)
    Call(SetBattleCamOffsetY, 8)
    Call(GetBattlePhase, LVar0)
    IfNe(LVar0, 1)
        Call(InitTargetIterator)
    EndIf
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196629)
    Wait(4)
    Call(battle_move_hammer_attack_IsBerserkerEquipped)
    IfEq(LVar0, 1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196630)
        Call(battle_move_hammer_attack_ShouldMovesAutoSucceed)
        IfEq(LVar0, 0)
            Loop(45)
                Wait(1)
                Call(CheckButtonDown, 262144, LVar0)
                IfNe(LVar0, 0)
                    BreakLoop
                EndIf
            EndLoop
        EndIf
        ExecGetTID(TTYD64_battle_move_hammer_attack_EVS_802A10A4, 0)
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

EvtScript TTYD64_battle_move_hammer_attack_EVS_802A3AC8 = {
    Call(TTYD64_Player_AC_802A9000)
    Exec(TTYD64_Script_NukeTracker)
    Return
    End
};

EvtScript TTYD64_battle_move_hammer_attack_EVS_UseBerserker_Impl = {
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            ExecWait(TTYD64_battle_move_hammer_attack_EVS_802A42E4)
        CaseEq(1)
            ExecWait(TTYD64_battle_move_hammer_attack_EVS_802A36B8)
        CaseEq(2)
            ExecWait(TTYD64_battle_move_hammer_attack_EVS_802A21DC)
    EndSwitch
    Call(PlayerTestEnemy, LVar0, 64, 25, 0, LVar9, 16)
    IfEq(LVar0, 6)
        Call(GetMenuSelection, LVar0, LVar1, LVar2)
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
        Call(UseBattleCamPreset, 44)
        ExecWait(battle_move_hammer_attack_EVS_HammerSupport_ReturnHome_SmashMiss)
        Return
    EndIf
    Call(GetMashActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
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
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
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
    Call(UseBattleCamPreset, 44)
    Wait(1)
    Call(PlayerTestEnemy, LVar0, 64, 25, 0, 0, 16)
    IfEq(LVar0, 6)
        ExecWait(battle_move_hammer_attack_EVS_HammerSupport_ReturnHome_SmashMiss)
        Return
    EndIf
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar1)
                CaseEq(0)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_NORMAL)
                CaseEq(1)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_SILENT)
                CaseEq(2)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_SILENT)
            EndSwitch
            Call(PlayerDamageEnemy, LVar0, 64, 25, 0, LVarF, 112)
        CaseDefault
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar1)
                CaseEq(0)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_NORMAL)
                CaseEq(1)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_SILENT)
                CaseEq(2)
                    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_SILENT)
            EndSwitch
            Call(PlayerDamageEnemy, LVar0, 64, 25, 0, LVarE, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(1)
        CaseOrEq(3)
            ExecWait(TTYD64_battle_move_hammer_attack_EVS_HammerSupport_ReturnHome_SmashSuccess)
        EndCaseGroup
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(battle_move_hammer_attack_EVS_HammerSupport_ReturnHome_SmashMiss)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_move_hammer_attack_EVS_802A42E4 = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Exec(TTYD64_battle_move_hammer_attack_EVS_802A3AC8)
    ExecWait(TTYD64_battle_move_hammer_attack_EVS_HammerSupport_SmashApproach)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    ExecWait(battle_move_hammer_attack_EVS_HammerSupport_BasicRaiseDelay)
    Call(PlayerTestEnemy, LVar0, 64, 0, 0, 0, 16)
    Call(UseBattleCamPreset, 43)
    Call(SetBattleCamOffsetY, 8)
    Call(GetBattlePhase, LVar0)
    IfNe(LVar0, 1)
        Call(InitTargetIterator)
    EndIf
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196622)
    Wait(4)
    Call(battle_move_hammer_attack_IsBerserkerEquipped)
    IfNe(LVar0, 0)
        Call(SetAnimation, ACTOR_PLAYER, 0, 196623)
        Call(GetActionCommandMode, LVar0)
        IfLt(LVar0, 2)
            Call(battle_move_hammer_attack_ShouldMovesAutoSucceed)
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
        ExecGetTID(TTYD64_battle_move_hammer_attack_EVS_802A10A4, 0)
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

EvtScript TTYD64_battle_move_hammer_attack_EVS_HammerSupport_SmashApproach = {
    Call(GetBattlePhase, LVar0)
    IfNe(LVar0, 1)
        Call(InitTargetIterator)
    EndIf
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

void TTYD64_Player_Install_move_hammer_attack(void) {
    Mod_ReplaceScript(
        "TTYD64", &battle_move_hammer_attack_EVS_HammerSupport_ReturnHome_SmashSuccess,
        &TTYD64_battle_move_hammer_attack_EVS_HammerSupport_ReturnHome_SmashSuccess
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_hammer_attack_EVS_UseMove_Impl, &TTYD64_battle_move_hammer_attack_EVS_UseMove_Impl
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_hammer_attack_EVS_FirstStrike, &TTYD64_battle_move_hammer_attack_EVS_FirstStrike
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_hammer_attack_EVS_UseBerserker_Impl,
        &TTYD64_battle_move_hammer_attack_EVS_UseBerserker_Impl
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_hammer_attack_EVS_HammerSupport_SmashApproach,
        &TTYD64_battle_move_hammer_attack_EVS_HammerSupport_SmashApproach
    );
}
