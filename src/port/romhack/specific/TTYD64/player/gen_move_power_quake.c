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
#include "port/romhack/specific/TTYD64/player/player_internal.h"

extern EvtScript battle_move_power_quake_EVS_UseMove;
extern EvtScript battle_move_power_quake_EVS_UseMove_Impl;
extern EvtScript battle_move_power_quake_EVS_Hammer_UseUltraQuake;
extern EvtScript battle_move_power_quake_EVS_Hammer_UseSuperQuake;
extern EvtScript battle_move_power_quake_EVS_Hammer_UseBasicQuake;
extern EvtScript battle_move_power_quake_EVS_HammerSupport_BasicRaiseDelay;
extern EvtScript battle_move_power_quake_EVS_HammerSupport_QuakeApproach;
extern EvtScript battle_move_power_quake_EVS_HammerSupport_ReturnHome_Quake;
extern EvtScript battle_move_power_quake_EVS_HammerSupport_SuperRaiseDelay;
extern EvtScript battle_move_power_quake_EVS_HammerSupport_UltraRaiseDelay;
API_CALLABLE(AddBattleCamDist);
API_CALLABLE(AddGoalPos);
API_CALLABLE(CheckButtonDown);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(GetActionProgress);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetPlayerActionQuality);
API_CALLABLE(GetSmashActionQuality);
API_CALLABLE(GetTargetListLength);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerDamageEnemy);
API_CALLABLE(PlayerTestEnemy);
API_CALLABLE(SetActionProgress);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(ShakeCam);
API_CALLABLE(ShowActionHud);
API_CALLABLE(StartRumble);
API_CALLABLE(TTYD64_Player_AC_802A9000);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(action_command_hammer_start);
API_CALLABLE(battle_move_power_quake_ShouldMovesAutoSucceed);
EvtScript TTYD64_battle_move_power_quake_EVS_Hammer_UseBasicQuake;
EvtScript TTYD64_battle_move_power_quake_EVS_Hammer_UseSuperQuake;
EvtScript TTYD64_battle_move_power_quake_EVS_Hammer_UseUltraQuake;
EvtScript TTYD64_battle_move_power_quake_EVS_802A3044;
EvtScript TTYD64_battle_move_power_quake_EVS_802A30E8;
EvtScript TTYD64_battle_move_power_quake_EVS_UseMove_Impl;
EvtScript TTYD64_battle_move_power_quake_EVS_802A3B9C;
EvtScript TTYD64_battle_move_power_quake_EVS_UseMove;
EvtScript TTYD64_battle_move_power_quake_EVS_802A3E78;

// clang-format off
EvtScript TTYD64_battle_move_power_quake_EVS_Hammer_UseBasicQuake = {
    Call(ChooseNextTarget, 10, LVar0)
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Exec(TTYD64_battle_move_power_quake_EVS_802A30E8)
    ExecWait(battle_move_power_quake_EVS_HammerSupport_QuakeApproach)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    ExecWait(battle_move_power_quake_EVS_HammerSupport_BasicRaiseDelay)
    Call(UseBattleCamPreset, 43)
    Call(AddBattleCamDist, 80)
    Call(InitTargetIterator)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196622)
    Wait(8)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196623)
    Call(battle_move_power_quake_ShouldMovesAutoSucceed)
    IfEq(LVar0, 0)
        Loop(45)
            Wait(1)
            Call(CheckButtonDown, 262144, LVar0)
            IfNe(LVar0, 0)
                BreakLoop
            EndIf
        EndLoop
    EndIf
    ExecGetTID(TTYD64_battle_move_power_quake_EVS_802A3E78, 0)
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
    Wait(1)
    Call(GetSmashActionQuality, LVar0)
    IfEq(LVar0, 0)
        Goto(0)
    EndIf
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8469)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196625)
    Wait(3)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196626)
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8472)
    Return
    End
};

EvtScript TTYD64_battle_move_power_quake_EVS_Hammer_UseSuperQuake = {
    Call(ChooseNextTarget, 10, LVar0)
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Exec(TTYD64_battle_move_power_quake_EVS_802A30E8)
    ExecWait(battle_move_power_quake_EVS_HammerSupport_QuakeApproach)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    ExecWait(battle_move_power_quake_EVS_HammerSupport_SuperRaiseDelay)
    Call(UseBattleCamPreset, 43)
    Call(AddBattleCamDist, 80)
    Call(InitTargetIterator)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196629)
    Wait(8)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196630)
    Call(battle_move_power_quake_ShouldMovesAutoSucceed)
    IfEq(LVar0, 0)
        Loop(45)
            Wait(1)
            Call(CheckButtonDown, 262144, LVar0)
            IfNe(LVar0, 0)
                BreakLoop
            EndIf
        EndLoop
    EndIf
    ExecGetTID(TTYD64_battle_move_power_quake_EVS_802A3E78, 0)
    Call(action_command_hammer_start, 0, LVarD, 3)
    Loop(60)
        Wait(1)
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
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8470)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196632)
    Wait(3)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196633)
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8473)
    Return
    End
};

EvtScript TTYD64_battle_move_power_quake_EVS_Hammer_UseUltraQuake = {
    Call(ChooseNextTarget, 10, LVar0)
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Exec(TTYD64_battle_move_power_quake_EVS_802A30E8)
    ExecWait(battle_move_power_quake_EVS_HammerSupport_QuakeApproach)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    ExecWait(battle_move_power_quake_EVS_HammerSupport_UltraRaiseDelay)
    Call(UseBattleCamPreset, 43)
    Call(AddBattleCamDist, 80)
    Call(InitTargetIterator)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196636)
    Wait(8)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196637)
    Call(battle_move_power_quake_ShouldMovesAutoSucceed)
    IfEq(LVar0, 0)
        Loop(45)
            Wait(1)
            Call(CheckButtonDown, 262144, LVar0)
            IfNe(LVar0, 0)
                BreakLoop
            EndIf
        EndLoop
    EndIf
    ExecGetTID(TTYD64_battle_move_power_quake_EVS_802A3E78, 0)
    Call(action_command_hammer_start, 0, LVarD, 3)
    Loop(60)
        Wait(1)
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
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8471)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196639)
    Wait(3)
    Call(SetAnimation, ACTOR_PLAYER, 0, 196640)
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8474)
    Return
    End
};

EvtScript TTYD64_battle_move_power_quake_EVS_802A3044 = {
    Thread
        Wait(10)
        Call(TTYD64_StylishGetCount, LVar0)
        IfEq(LVar0, 0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
        EndIf
    EndThread
    Wait(10)
    ExecWait(battle_move_power_quake_EVS_HammerSupport_ReturnHome_Quake)
    Call(UseBattleCamPreset, 2)
    Return
    End
};

EvtScript TTYD64_battle_move_power_quake_EVS_802A30E8 = {
    Call(TTYD64_Player_AC_802A9000)
    Exec(TTYD64_Script_NukeTracker)
    Return
    End
};

EvtScript TTYD64_battle_move_power_quake_EVS_UseMove_Impl = {
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            ExecWait(TTYD64_battle_move_power_quake_EVS_Hammer_UseBasicQuake)
        CaseEq(1)
            ExecWait(TTYD64_battle_move_power_quake_EVS_Hammer_UseSuperQuake)
        CaseEq(2)
            ExecWait(TTYD64_battle_move_power_quake_EVS_Hammer_UseUltraQuake)
    EndSwitch
    Thread
        Wait(8)
        Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Add(LVar0, 24)
        Add(LVar1, 10)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 60, 8, 0, 30, 0, 0, 0, 0, 0)
        Wait(2)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 60, 8, 33, 30, 0, 0, 0, 0, 0)
        Wait(2)
        Call(PlayEffect_impl, 29, 1, LVar0, LVar1, LVar2, 60, 8, 66, 30, 0, 0, 0, 0, 0)
    EndThread
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(StartRumble, 10)
            Thread
                Call(ShakeCam, 1, 0, 2, Float(0.24))
                Call(ShakeCam, 1, 0, 5, Float(1.2))
                Call(ShakeCam, 1, 0, 10, Float(2.4))
                Call(ShakeCam, 1, 0, 5, Float(1.2))
                Call(ShakeCam, 1, 0, 3, Float(0.8398))
                Call(ShakeCam, 1, 0, 4, Float(0.48))
                Call(ShakeCam, 1, 0, 6, Float(0.12))
                Call(ShakeCam, 1, 0, 4, Float(0.0596))
            EndThread
            Thread
                Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
                Add(LVar0, 24)
                ExecGetTID(TTYD64_battle_move_power_quake_EVS_802A3B9C, 0)
                Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 72, 8, 0, 30, 0, 0, 0, 0, 0)
                Wait(5)
                Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 72, 8, 24, 30, 0, 0, 0, 0, 0)
                Wait(5)
                Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 72, 8, 48, 30, 0, 0, 0, 0, 0)
                Wait(5)
                Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 72, 8, 72, 30, 0, 0, 0, 0, 0)
            EndThread
        CaseDefault
            Call(StartRumble, 10)
            Thread
                Call(ShakeCam, 1, 0, 2, Float(0.2))
                Call(ShakeCam, 1, 0, 5, Float(1.0))
                Call(ShakeCam, 1, 0, 10, Float(2.0))
                Call(ShakeCam, 1, 0, 5, Float(1.0))
                Call(ShakeCam, 1, 0, 3, Float(0.7))
                Call(ShakeCam, 1, 0, 4, Float(0.4))
                Call(ShakeCam, 1, 0, 6, Float(0.0996))
                Call(ShakeCam, 1, 0, 4, Float(0.0498))
            EndThread
            Thread
                Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
                Add(LVar0, 24)
                Add(LVar1, 10)
                Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 72, 8, 0, 30, 0, 0, 0, 0, 0)
                Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 72, 8, 24, 30, 0, 0, 0, 0, 0)
                Wait(6)
                Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 96, 8, 48, 30, 0, 0, 0, 0, 0)
                Call(PlayEffect_impl, 29, 0, LVar0, LVar1, LVar2, 96, 8, 72, 30, 0, 0, 0, 0, 0)
            EndThread
    EndSwitch
    Call(GetPlayerActionQuality, LVar0)
    IfGt(LVar0, 0)
        Call(UseBattleCamPreset, 46)
        Call(MoveBattleCamOver, 5)
    Else
        Call(UseBattleCamPreset, 46)
        Call(MoveBattleCamOver, 50)
    EndIf
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            Call(PlaySoundAtActor, ACTOR_PLAYER, 8475)
        CaseEq(1)
            Call(PlaySoundAtActor, ACTOR_PLAYER, 8476)
        CaseEq(2)
            Call(PlaySoundAtActor, ACTOR_PLAYER, 8477)
    EndSwitch
    Wait(10)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            Call(PlaySoundAtActor, ACTOR_PLAYER, 8472)
        CaseEq(1)
            Call(PlaySoundAtActor, ACTOR_PLAYER, 8473)
        CaseEq(2)
            Call(PlaySoundAtActor, ACTOR_PLAYER, 8474)
    EndSwitch
    Set(LVar9, 0)
    Call(InitTargetIterator)
    Label(10)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(PlayerTestEnemy, LVar0, 2097152, 29, 0, 0, 16)
    IfEq(LVar0, 6)
        Goto(11)
    EndIf
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(PlayerDamageEnemy, LVar0, 941623296, 25, 0, LVarF, 112)
        CaseDefault
            Call(PlayerDamageEnemy, LVar0, 941623296, 25, 0, LVarE, 48)
    EndSwitch
    Label(11)
    Call(ChooseNextTarget, 0, LVar1)
    Add(LVar9, 1)
    Call(GetTargetListLength, LVar1)
    IfLt(LVar9, LVar1)
        Goto(10)
    EndIf
    Jump(TTYD64_battle_move_power_quake_EVS_802A3044)
    Thread
        Wait(10)
        Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    EndThread
    ExecWait(battle_move_power_quake_EVS_HammerSupport_ReturnHome_Quake)
    Call(UseBattleCamPreset, 2)
    Return
    End
};

EvtScript TTYD64_battle_move_power_quake_EVS_802A3B9C = {
    Thread
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(0)
        EndIf
        Loop(4)
            ExecWait(TTYD64_Script_TimingTutor)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                Call(TTYD64_StylishAddCount, LVar0)
                Set(LVarA, 0)
                ExecWait(TTYD64_Script_DoStylishFX)
                Call(SetAnimation, ACTOR_SELF, 0, 196617)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Label(0)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
    EndThread
    Return
    End
};

EvtScript TTYD64_battle_move_power_quake_EVS_UseMove = {
    Call(ShowActionHud, 1)
    Call(TTYD64_GetStackBoost, 279, 2, LVarE, LVarF)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            Set(LVarD, 80)
            Add(LVarE, 2)
            Add(LVarF, 4)
            ExecWait(TTYD64_battle_move_power_quake_EVS_UseMove_Impl)
        CaseEq(1)
            Set(LVarD, 80)
            Add(LVarE, 2)
            Add(LVarF, 4)
            ExecWait(TTYD64_battle_move_power_quake_EVS_UseMove_Impl)
        CaseEq(2)
            Set(LVarD, 80)
            Add(LVarE, 2)
            Add(LVarF, 4)
            ExecWait(TTYD64_battle_move_power_quake_EVS_UseMove_Impl)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_move_power_quake_EVS_802A3E78 = {
    Wait(45)
    Call(TTYD64_StylishSetCount, 0)
    Exec(TTYD64_Script_InitTracker)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_power_quake(void) {
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_quake_EVS_Hammer_UseBasicQuake,
        &TTYD64_battle_move_power_quake_EVS_Hammer_UseBasicQuake
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_quake_EVS_Hammer_UseSuperQuake,
        &TTYD64_battle_move_power_quake_EVS_Hammer_UseSuperQuake
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_quake_EVS_Hammer_UseUltraQuake,
        &TTYD64_battle_move_power_quake_EVS_Hammer_UseUltraQuake
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_power_quake_EVS_UseMove_Impl, &TTYD64_battle_move_power_quake_EVS_UseMove_Impl
    );
    Mod_ReplaceScript("TTYD64", &battle_move_power_quake_EVS_UseMove, &TTYD64_battle_move_power_quake_EVS_UseMove);
}
