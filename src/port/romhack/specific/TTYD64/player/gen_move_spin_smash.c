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

extern EvtScript battle_move_spin_smash_EVS_UseMove;
extern EvtScript battle_move_spin_smash_EVS_UseMoveUltra_Impl;
extern EvtScript battle_move_spin_smash_EVS_UseMoveSuper_Impl;
extern EvtScript battle_move_spin_smash_EVS_UseMoveBasic_Impl;
extern EvtScript battle_move_spin_smash_EVS_HammerSupport_SmashApproach;
extern EvtScript battle_move_spin_smash_EVS_HammerSupport_ReturnHome_Quake;
extern EvtScript battle_move_spin_smash_EVS_HammerSupport_ReturnHome_SmashMiss;
API_CALLABLE(AddGoalPos);
API_CALLABLE(CheckButtonDown);
API_CALLABLE(GetActionProgress);
API_CALLABLE(GetActorRotation);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetPlayerActionQuality);
API_CALLABLE(GetSmashActionQuality);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(MakeLerp);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerDamageEnemy);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(PlayerTestEnemy);
API_CALLABLE(SetActionProgress);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetActorYaw);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetDamageSource);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(ShowActionHud);
API_CALLABLE(StartRumble);
API_CALLABLE(UpdateLerp);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(action_command_hammer_init);
API_CALLABLE(action_command_hammer_start);
API_CALLABLE(battle_move_spin_smash_ShouldMovesAutoSucceed);
API_CALLABLE(func_802A1000_737890);
API_CALLABLE(func_802A1074_737904);
EvtScript TTYD64_battle_move_spin_smash_EVS_HammerSupport_SmashApproach;
EvtScript TTYD64_battle_move_spin_smash_EVS_802A3124;
EvtScript TTYD64_battle_move_spin_smash_EVS_UseMoveBasic_Impl;
EvtScript TTYD64_battle_move_spin_smash_EVS_UseMoveSuper_Impl;
EvtScript TTYD64_battle_move_spin_smash_EVS_UseMoveUltra_Impl;
EvtScript TTYD64_battle_move_spin_smash_EVS_802A4638;
EvtScript TTYD64_battle_move_spin_smash_EVS_UseMove;
EvtScript TTYD64_battle_move_spin_smash_EVS_802A4A28;

// clang-format off
EvtScript TTYD64_battle_move_spin_smash_EVS_HammerSupport_SmashApproach = {
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Sub(LVar0, 32)
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    ExecGetTID(TTYD64_battle_move_spin_smash_EVS_802A4A28, 0)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(5.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Return
    End
};

EvtScript TTYD64_battle_move_spin_smash_EVS_802A3124 = {
    Set(LVar1, 0)
    Thread
        Wait(30)
        Call(TTYD64_StylishSetCount, 0)
        Exec(TTYD64_Script_InitTracker)
    EndThread
    Return
    End
};

EvtScript TTYD64_battle_move_spin_smash_EVS_UseMoveBasic_Impl = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Call(action_command_hammer_init)
    Call(InitTargetIterator)
    ExecWait(TTYD64_battle_move_spin_smash_EVS_HammerSupport_SmashApproach)
    Set(LVar1, 0)
    Loop(10)
        Call(CheckButtonDown, 262144, LVar0)
        IfEq(LVar0, 1)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
            BreakLoop
        EndIf
        Wait(1)
        Add(LVar1, 1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 262144)
    EndLoop
    Call(SetAnimation, ACTOR_PLAYER, 0, 262144)
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
    Call(PlayerTestEnemy, LVar0, 64, 25, 0, LVar9, 16)
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    Call(UseBattleCamPreset, 43)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 262145)
    Wait(8)
    Call(SetAnimation, ACTOR_PLAYER, 0, 262146)
    Call(battle_move_spin_smash_ShouldMovesAutoSucceed)
    IfEq(LVar0, 0)
        Loop(45)
            Wait(1)
            Call(CheckButtonDown, 262144, LVar0)
            IfNe(LVar0, 0)
                BreakLoop
            EndIf
        EndLoop
    EndIf
    Call(action_command_hammer_start, 0, LVarD, 3)
    Call(SetActionProgress, 0)
    ExecWait(TTYD64_battle_move_spin_smash_EVS_802A3124)
    Loop(30)
        Wait(1)
        Call(GetActionProgress, LVar0)
        IfNe(LVar0, 0)
            IfNe(LVar1, 1)
                Call(SetAnimation, ACTOR_PLAYER, 0, 262147)
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
    Call(SetAnimation, ACTOR_PLAYER, 0, 262148)
    Wait(3)
    Call(SetAnimation, ACTOR_PLAYER, 0, 262149)
    Wait(3)
    Call(UseBattleCamPreset, 46)
    Call(StartRumble, 7)
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8478)
    Call(PlayerTestEnemy, LVar0, 64, 25, 0, 0, 16)
    IfEq(LVar0, 6)
        Wait(10)
        Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
        Wait(25)
        ExecWait(battle_move_spin_smash_EVS_HammerSupport_ReturnHome_SmashMiss)
        Return
    EndIf
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(func_802A1000_737890)
            Call(PlayerDamageEnemy, LVar0, 603979840, 25, 0, LVarF, 112)
        CaseDefault
            Call(func_802A1074_737904)
            Call(PlayerDamageEnemy, LVar0, 603979840, 25, 0, LVarE, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(10)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
            ExecWait(battle_move_spin_smash_EVS_HammerSupport_ReturnHome_Quake)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
        EndCaseGroup
    EndSwitch
    Thread
        Set(LVar0, 0)
        Loop(10)
            Add(LVar0, 18)
            Call(SetActorYaw, ACTOR_PLAYER, LVar0)
            Wait(1)
        EndLoop
    EndThread
    ExecWait(TTYD64_battle_move_spin_smash_EVS_802A4638)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Call(SetActorYaw, ACTOR_PLAYER, 0)
    ExecWait(battle_move_spin_smash_EVS_HammerSupport_ReturnHome_Quake)
    Return
    End
};

EvtScript TTYD64_battle_move_spin_smash_EVS_UseMoveSuper_Impl = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Call(action_command_hammer_init)
    Call(InitTargetIterator)
    ExecWait(TTYD64_battle_move_spin_smash_EVS_HammerSupport_SmashApproach)
    Set(LVar1, 0)
    Loop(10)
        Call(CheckButtonDown, 262144, LVar0)
        IfEq(LVar0, 1)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
            BreakLoop
        EndIf
        Wait(1)
        Add(LVar1, 1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 262150)
    EndLoop
    Call(SetAnimation, ACTOR_PLAYER, 0, 262150)
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
    Call(InitTargetIterator)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(AddGoalPos, ACTOR_PLAYER, 0, 0, 0)
    Call(UseBattleCamPreset, 43)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 262151)
    Wait(8)
    Call(SetAnimation, ACTOR_PLAYER, 0, 262152)
    Call(battle_move_spin_smash_ShouldMovesAutoSucceed)
    IfEq(LVar0, 0)
        Loop(45)
            Wait(1)
            Call(CheckButtonDown, 262144, LVar0)
            IfNe(LVar0, 0)
                BreakLoop
            EndIf
        EndLoop
    EndIf
    Call(action_command_hammer_start, 0, LVarD, 3)
    Call(SetActionProgress, 0)
    ExecWait(TTYD64_battle_move_spin_smash_EVS_802A3124)
    Loop(30)
        Wait(1)
        Call(GetActionProgress, LVar0)
        IfNe(LVar0, 0)
            IfNe(LVar1, 1)
                Call(SetAnimation, ACTOR_PLAYER, 0, 262153)
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
    Call(SetAnimation, ACTOR_PLAYER, 0, 262154)
    Wait(3)
    Call(SetAnimation, ACTOR_PLAYER, 0, 262155)
    Wait(3)
    Call(UseBattleCamPreset, 46)
    Call(StartRumble, 8)
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8479)
    Call(PlayerTestEnemy, LVar0, 64, 25, 0, 0, 16)
    IfEq(LVar0, 6)
        Wait(10)
        Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
        Wait(25)
        ExecWait(battle_move_spin_smash_EVS_HammerSupport_ReturnHome_SmashMiss)
        Return
    EndIf
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(func_802A1000_737890)
            Call(PlayerDamageEnemy, LVar0, 603979840, 25, 0, LVarF, 112)
        CaseDefault
            Call(func_802A1074_737904)
            Call(PlayerDamageEnemy, LVar0, 603979840, 25, 0, LVarE, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(10)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
            ExecWait(battle_move_spin_smash_EVS_HammerSupport_ReturnHome_Quake)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
        EndCaseGroup
    EndSwitch
    Thread
        Set(LVar0, 0)
        Loop(10)
            Add(LVar0, 18)
            Call(SetActorYaw, ACTOR_PLAYER, LVar0)
            Wait(1)
        EndLoop
    EndThread
    ExecWait(TTYD64_battle_move_spin_smash_EVS_802A4638)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Call(SetActorYaw, ACTOR_PLAYER, 0)
    ExecWait(battle_move_spin_smash_EVS_HammerSupport_ReturnHome_Quake)
    Return
    End
};

EvtScript TTYD64_battle_move_spin_smash_EVS_UseMoveUltra_Impl = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Call(action_command_hammer_init)
    Call(InitTargetIterator)
    ExecWait(TTYD64_battle_move_spin_smash_EVS_HammerSupport_SmashApproach)
    Set(LVar1, 0)
    Loop(10)
        Call(CheckButtonDown, 262144, LVar0)
        IfEq(LVar0, 1)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
            BreakLoop
        EndIf
        Wait(1)
        Add(LVar1, 1)
        Call(SetAnimation, ACTOR_PLAYER, 0, 262156)
    EndLoop
    Call(SetAnimation, ACTOR_PLAYER, 0, 262156)
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
    Call(InitTargetIterator)
    Call(UseBattleCamPreset, 43)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Call(SetAnimation, ACTOR_PLAYER, 0, 262157)
    Wait(8)
    Call(SetAnimation, ACTOR_PLAYER, 0, 262158)
    Call(battle_move_spin_smash_ShouldMovesAutoSucceed)
    IfEq(LVar0, 0)
        Loop(45)
            Wait(1)
            Call(CheckButtonDown, 262144, LVar0)
            IfNe(LVar0, 0)
                BreakLoop
            EndIf
        EndLoop
    EndIf
    Call(action_command_hammer_start, 0, LVarD, 3)
    Call(SetActionProgress, 0)
    ExecWait(TTYD64_battle_move_spin_smash_EVS_802A3124)
    Loop(30)
        Wait(1)
        Call(GetActionProgress, LVar0)
        IfNe(LVar0, 0)
            IfNe(LVar1, 1)
                Call(SetAnimation, ACTOR_PLAYER, 0, 262159)
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
    Call(SetAnimation, ACTOR_PLAYER, 0, 262160)
    Wait(3)
    Call(SetAnimation, ACTOR_PLAYER, 0, 262161)
    Wait(3)
    Call(UseBattleCamPreset, 46)
    Call(StartRumble, 9)
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8480)
    Call(PlayerTestEnemy, LVar0, 64, 25, 0, 0, 16)
    IfEq(LVar0, 6)
        Wait(10)
        Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
        Wait(25)
        ExecWait(battle_move_spin_smash_EVS_HammerSupport_ReturnHome_SmashMiss)
        Return
    EndIf
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(func_802A1000_737890)
            Call(PlayerDamageEnemy, LVar0, 603979840, 25, 0, LVarF, 112)
        CaseDefault
            Call(func_802A1074_737904)
            Call(PlayerDamageEnemy, LVar0, 603979840, 25, 0, LVarE, 48)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(0)
        CaseOrEq(2)
            Wait(10)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
            ExecWait(battle_move_spin_smash_EVS_HammerSupport_ReturnHome_Quake)
            Return
        EndCaseGroup
        CaseOrEq(1)
        CaseOrEq(3)
        EndCaseGroup
    EndSwitch
    Thread
        Set(LVar0, 0)
        Loop(10)
            Add(LVar0, 18)
            Call(SetActorYaw, ACTOR_PLAYER, LVar0)
            Wait(1)
        EndLoop
    EndThread
    ExecWait(TTYD64_battle_move_spin_smash_EVS_802A4638)
    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
    Call(SetActorYaw, ACTOR_PLAYER, 0)
    ExecWait(battle_move_spin_smash_EVS_HammerSupport_ReturnHome_Quake)
    Return
    End
};

EvtScript TTYD64_battle_move_spin_smash_EVS_802A4638 = {
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Wait(1)
        Goto(0)
    EndIf
    Loop(2)
        ExecWait(TTYD64_Script_TimingTutor)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishAddCount, LVar0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            Loop(0)
                Call(GetActorRotation, -127, 0, LVar0, 0)
                IfEq(LVar0, 0)
                    Call(SetAnimation, ACTOR_SELF, 0, 65586)
                    Call(MakeLerp, -180, 0, 10, 6)
                    Loop(0)
                        Call(UpdateLerp)
                        Call(SetActorRotation, ACTOR_PLAYER, 0, LVar0, 0)
                        Wait(1)
                        IfEq(LVar1, 0)
                            BreakLoop
                        EndIf
                    EndLoop
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            Call(SetActorRotation, ACTOR_PLAYER, 0, 0, 0)
            Wait(12)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Label(0)
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Wait(8)
    Return
    End
};

EvtScript TTYD64_battle_move_spin_smash_EVS_UseMove = {
    Call(ShowActionHud, 1)
    Call(SetDamageSource, 2)
    Call(TTYD64_GetStackBoost, 224, 1, LVarE, LVarF)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            Set(LVarD, 60)
            Add(LVarE, 1)
            Add(LVarF, 2)
            ExecWait(TTYD64_battle_move_spin_smash_EVS_UseMoveBasic_Impl)
        CaseEq(1)
            Set(LVarD, 60)
            Add(LVarE, 2)
            Add(LVarF, 4)
            ExecWait(TTYD64_battle_move_spin_smash_EVS_UseMoveSuper_Impl)
        CaseEq(2)
            Set(LVarD, 60)
            Add(LVarE, 3)
            Add(LVarF, 6)
            ExecWait(TTYD64_battle_move_spin_smash_EVS_UseMoveUltra_Impl)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_battle_move_spin_smash_EVS_802A4A28 = {
    Call(UseBattleCamPreset, 26)
    Exec(TTYD64_Script_NukeTracker)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_spin_smash(void) {
    Mod_ReplaceScript(
        "TTYD64", &battle_move_spin_smash_EVS_HammerSupport_SmashApproach,
        &TTYD64_battle_move_spin_smash_EVS_HammerSupport_SmashApproach
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_spin_smash_EVS_UseMoveBasic_Impl, &TTYD64_battle_move_spin_smash_EVS_UseMoveBasic_Impl
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_spin_smash_EVS_UseMoveSuper_Impl, &TTYD64_battle_move_spin_smash_EVS_UseMoveSuper_Impl
    );
    Mod_ReplaceScript(
        "TTYD64", &battle_move_spin_smash_EVS_UseMoveUltra_Impl, &TTYD64_battle_move_spin_smash_EVS_UseMoveUltra_Impl
    );
    Mod_ReplaceScript("TTYD64", &battle_move_spin_smash_EVS_UseMove, &TTYD64_battle_move_spin_smash_EVS_UseMove);
}
