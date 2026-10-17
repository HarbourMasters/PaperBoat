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

extern EvtScript battle_move_auto_multibounce_EVS_UseMove;
API_CALLABLE(AddBattleCamOffsetY);
API_CALLABLE(AfflictActor);
API_CALLABLE(CheckButtonDown);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(CreateNpc);
API_CALLABLE(DeleteNpc);
API_CALLABLE(EnablePlayerBlur);
API_CALLABLE(GetActionCommandMode);
API_CALLABLE(GetActionProgress);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorRotation);
API_CALLABLE(GetDist2D);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetMashActionQuality);
API_CALLABLE(GetNpcPos);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetPlayerActionQuality);
API_CALLABLE(GetSmashActionQuality);
API_CALLABLE(GetTargetListLength);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(LoadActionCommand);
API_CALLABLE(MakeLerp);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(NpcFlyTo);
API_CALLABLE(NpcJump1);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerDamageEnemy);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(PlayerTestEnemy);
API_CALLABLE(PlayerYieldTurn);
API_CALLABLE(SetActionCommandMode);
API_CALLABLE(SetActionProgress);
API_CALLABLE(SetActorRotation);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetDamageSource);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToHome);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetNpcImgFXParams);
API_CALLABLE(SetNpcJumpscale);
API_CALLABLE(SetNpcPos);
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
EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A1000;
EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A1130;
EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A1BF0;
EvtScript TTYD64_battle_move_auto_multibounce_EVS_UseMove;
EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A2E34;
EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A34EC;
EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A39D0;
EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A3CAC;
EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A3D88;
EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A40BC;

// clang-format off
EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A1000 = {
    Call(PlayerYieldTurn)
    Call(UseBattleCamPreset, 2)
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

EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A1130 = {
    Exec(TTYD64_Script_NukeTracker)
    Call(ShowActionHud, 1)
    Call(SetDamageSource, 3)
    Set(LVarD, 30)
    Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_1_1U, LVar1)
    Switch(LVar1)
        CaseEq(0)
            Set(LVarE, 1)
            Set(LVarF, 2)
        CaseEq(1)
            Set(LVarE, 3)
            Set(LVarF, 4)
        CaseGe(2)
            Set(LVarE, 4)
            Set(LVarF, 5)
    EndSwitch
    ExecGetTID(TTYD64_battle_move_auto_multibounce_EVS_802A34EC, LVar0)
    Call(TTYD64_SetMoveScratch, TTYD64_MSI_AUTO_MULTIBOUNCE, TTYD64_MS_THREAD, LVar0)
    ExecWait(TTYD64_battle_move_auto_multibounce_EVS_802A1BF0)
    Call(TTYD64_GetMoveScratch, TTYD64_MSI_AUTO_MULTIBOUNCE, TTYD64_MS_THREAD, LVar0)
    KillThread(LVar0)
    Call(TTYD64_GetMoveScratch, TTYD64_MSI_AUTO_MULTIBOUNCE, TTYD64_MS_RESULT, LVar0)
    IfEq(LVar0, 1)
        ExecWait(TTYD64_battle_move_auto_multibounce_EVS_802A3D88)
        ExecWait(TTYD64_battle_move_auto_multibounce_EVS_802A1000)
        Return
    EndIf
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_SPIKE_THROW_SPINY)
    Call(GetMashActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_1_1U, LVar1)
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
                CaseGe(2)
                    Call(StartRumble, 9)
                    Thread
                        Call(ShakeCam, 1, 0, 10, Float(1.9))
                    EndThread
            EndSwitch
        CaseDefault
            Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_1_1U, LVar1)
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
                CaseGe(2)
                    Call(StartRumble, 9)
                    Thread
                        Call(ShakeCam, 1, 0, 2, Float(1.9))
                    EndThread
            EndSwitch
    EndSwitch
    Call(UseBattleCamPreset, 29)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(SetNpcJumpscale, 101, Float(1.7998))
    Call(NpcJump1, 101, LVar0, 0, LVar2, 17)
    Wait(1)
    Call(DeleteNpc, 101)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HIT_SILENT)
    Set(LVar9, 0)
    Call(InitTargetIterator)
    Label(10)
    Call(SetGoalToTarget, ACTOR_PLAYER)
    Call(TTYD64_SetPoisonDrive, 1)
    Call(TTYD64_GetActorPointer, 0, LVar0)
    Call(TTYD64_ReadPtrField, LVar0, TTYD64_F_ACTOR_425_1U, LVar1)
    IfEq(LVar1, 0)
        Call(GetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 36, 0, LVar0, 0, LVar2, Float(0.5), 15, 0, 0, 0, 0, 0, 0, 0)
    Else
        Call(GetGoalPos, ACTOR_PLAYER, LVar3, LVar4, LVar5)
        Call(ChooseNextTarget, 1, 0)
        Call(SetGoalToTarget, ACTOR_PLAYER)
        Call(GetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Call(ChooseNextTarget, 0, 0)
        Call(SetGoalToTarget, ACTOR_PLAYER)
        Call(GetDist2D, LVar6, LVar0, LVar1, LVar3, LVar4)
        Div(LVar6, 9)
        Sub(LVar6, 2)
        Loop(LVar6)
            IfEq(LVar6, 0)
                BreakLoop
            EndIf
            Add(LVar0, 9)
            Call(PlaySound, SOUND_OBK_CHECK_CABINET)
            Call(PlayEffect_impl, 36, 0, LVar0, 0, LVar5, Float(0.5), 15, 0, 0, 0, 0, 0, 0, 0)
            Wait(3)
        EndLoop
        Call(GetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 36, 0, LVar0, 0, LVar2, Float(0.5), 15, 0, 0, 0, 0, 0, 0, 0)
    EndIf
    Call(PlayerTestEnemy, LVar0, 2097152, 29, 0, 0, 16)
    IfEq(LVar0, 6)
        Goto(11)
    EndIf
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(0)
            Call(PlayerDamageEnemy, LVar0, 438304770, 25, 0, LVarF, 112)
            Call(GetOwnerTarget, LVar1, 0)
            Call(TTYD64_GetStackBoost, 375, 2, LVar2, 0)
            Add(LVar2, LVarF)
            Add(LVar2, 1)
            IfGt(LVar2, 9)
                Set(LVar2, 9)
            EndIf
            Call(AfflictActor, LVar1, 9, LVar2)
        CaseDefault
            Call(PlayerDamageEnemy, LVar0, 438304770, 25, 0, LVarE, 48)
            Call(GetOwnerTarget, LVar1, 0)
            Call(TTYD64_GetStackBoost, 375, 2, LVar2, 0)
            Add(LVar2, LVarE)
            Add(LVar2, 1)
            IfGt(LVar2, 9)
                Set(LVar2, 9)
            EndIf
            Call(AfflictActor, LVar1, 9, LVar2)
    EndSwitch
    IfGt(LVarF, 1)
        Sub(LVarF, 1)
        Sub(LVarE, 1)
    EndIf
    Label(11)
    Call(ChooseNextTarget, 0, LVar1)
    Add(LVar9, 1)
    Call(GetTargetListLength, LVar1)
    IfLt(LVar9, LVar1)
        Goto(10)
    EndIf
    Call(SetAnimation, ACTOR_SELF, 0, 65538)
    Switch(LVar0)
        CaseOrEq(1)
        CaseOrEq(3)
            ExecWait(TTYD64_battle_move_auto_multibounce_EVS_802A1000)
        EndCaseGroup
        CaseOrEq(0)
        CaseOrEq(2)
            ExecWait(TTYD64_battle_move_auto_multibounce_EVS_802A3CAC)
        EndCaseGroup
    EndSwitch
    Call(TTYD64_SetPoisonDrive, 0)
    Return
    End
};

EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A1BF0 = {
    Call(LoadActionCommand, ACTION_COMMAND_SMASH)
    Call(action_command_hammer_init)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(5.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
    Call(PlayerRunToGoal, 0)
    Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_1_1U, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262145)
            Wait(7)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262146)
        CaseEq(1)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262151)
            Wait(7)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262152)
        CaseGe(2)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262157)
            Wait(7)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262158)
    EndSwitch
    Call(InitTargetIterator)
    ExecWait(TTYD64_battle_move_auto_multibounce_EVS_802A39D0)
    Call(PlayerTestEnemy, LVar0, 64, 0, 0, 0, 16)
    Call(UseBattleCamPreset, 12)
    Call(AddBattleCamOffsetY, -22)
    Call(InitTargetIterator)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_HAMMER_WINDUP)
    Wait(4)
    Call(battle_move_hammer_charge_1_IsBerserkerEquipped)
    IfEq(LVar0, 1)
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
        Call(action_command_hammer_start, 0, LVarD, 3)
        Call(SetActionProgress, 0)
        Set(LVar1, 0)
        Loop(30)
            Wait(1)
            Call(GetActionProgress, LVar0)
            IfNe(LVar0, 0)
                IfNe(LVar1, 1)
                    Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_1_1U, LVar2)
                    Switch(LVar2)
                        CaseEq(0)
                            Call(SetAnimation, ACTOR_PLAYER, 0, 262147)
                        CaseEq(1)
                            Call(SetAnimation, ACTOR_PLAYER, 0, 262153)
                        CaseGe(2)
                            Call(SetAnimation, ACTOR_PLAYER, 0, 262159)
                    EndSwitch
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
        Sub(LVar1, 10)
        Wait(LVar1)
        Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_1_1U, LVar2)
        Switch(LVar2)
            CaseEq(0)
                Call(SetAnimation, ACTOR_PLAYER, 0, 262147)
            CaseEq(1)
                Call(SetAnimation, ACTOR_PLAYER, 0, 262153)
            CaseGe(2)
                Call(SetAnimation, ACTOR_PLAYER, 0, 262159)
        EndSwitch
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
    Call(TTYD64_StylishSetCount, 0)
    Exec(TTYD64_Script_InitTracker)
    Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_1_1U, LVar2)
    Switch(LVar2)
        CaseEq(0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262148)
        CaseEq(1)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262154)
        CaseGe(2)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262160)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8471)
    Wait(3)
    Switch(LVar2)
        CaseEq(0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262149)
        CaseEq(1)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262155)
        CaseGe(2)
            Call(SetAnimation, ACTOR_PLAYER, 0, 262161)
    EndSwitch
    Exec(TTYD64_battle_move_auto_multibounce_EVS_802A2E34)
    Call(PlaySoundAtActor, ACTOR_PLAYER, 8474)
    Return
    End
};

EvtScript TTYD64_battle_move_auto_multibounce_EVS_UseMove = {
    ExecWait(TTYD64_battle_move_auto_multibounce_EVS_802A40BC)
    Return
    End
};

EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A2E34 = {
    Call(TTYD64_GetMoveScratch, TTYD64_MSI_AUTO_MULTIBOUNCE, TTYD64_MS_RESULT, LVar0)
    IfEq(LVar0, 1)
        Return
    EndIf
    Wait(3)
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
    Return
    End
};

EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A34EC = {
    Call(TTYD64_SetMoveScratch, TTYD64_MSI_AUTO_MULTIBOUNCE, TTYD64_MS_RESULT, 1)
    Wait(25)
    Call(CreateNpc, 101, 13893890)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 40)
    Add(LVar1, 105)
    Call(SetNpcPos, 101, LVar0, LVar1, LVar2)
    Call(GetNpcPos, 101, LVar0, 0, 0)
    Call(GetActorPos, ACTOR_PLAYER, 0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(NpcFlyTo, 101, LVar0, LVar1, LVar2, 25, 0, 0)
    Call(TTYD64_SetMoveScratch, TTYD64_MSI_AUTO_MULTIBOUNCE, TTYD64_MS_RESULT, 0)
    Call(GetNpcPos, 101, LVar0, 0, 0)
    Call(GetActorPos, ACTOR_PLAYER, 0, LVar1, LVar2)
    Call(NpcFlyTo, 101, LVar0, LVar1, LVar2, 10, 0, 0)
    Call(TTYD64_SetMoveScratch, TTYD64_MSI_AUTO_MULTIBOUNCE, TTYD64_MS_FLAG, 1)
    Call(TTYD64_SetMoveScratch, TTYD64_MSI_AUTO_MULTIBOUNCE, TTYD64_MS_RESULT, 1)
    Return
    End
};

EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A39D0 = {
    Set(LVar1, 0)
    Loop(10)
        Call(CheckButtonDown, 262144, LVar0)
        IfEq(LVar0, 1)
            BreakLoop
        EndIf
        Wait(1)
        Add(LVar1, 1)
    EndLoop
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

EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A3CAC = {
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

EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A3D88 = {
    Set(LVar0, 255)
    Loop(0)
        Add(LVar0, -31)
        IfLe(LVar0, 0)
            Set(LVar0, 0)
            Call(SetNpcImgFXParams, 101, 7, LVar0, 0, 0, 0)
            BreakLoop
        EndIf
        Call(SetNpcImgFXParams, 101, 7, LVar0, 0, 0, 0)
        Wait(1)
    EndLoop
    Call(DeleteNpc, 101)
    Return
    End
};

EvtScript TTYD64_battle_move_auto_multibounce_EVS_802A40BC = {
    ExecWait(TTYD64_battle_move_auto_multibounce_EVS_802A1130)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_move_auto_multibounce(void) {
    Mod_ReplaceScript(
        "TTYD64", &battle_move_auto_multibounce_EVS_UseMove, &TTYD64_battle_move_auto_multibounce_EVS_UseMove
    );
}
