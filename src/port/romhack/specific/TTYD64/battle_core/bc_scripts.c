#include "bc_internal.h"
#include "port/romhack/specific/TTYD64/battle_core/bc_natives.h"

API_CALLABLE(ForceDisablePlayerBlurImmediately);
API_CALLABLE(PlayParalyzeHitFX);
API_CALLABLE(TryPlayerLucky);
API_CALLABLE(action_command_squirt_init);
API_CALLABLE(action_command_squirt_start);
extern EvtScript EVS_Player_ComplexHit;
extern EvtScript EVS_Player_NoDamageHit;
extern EvtScript EVS_Player_SimpleHit;
EvtScript TTYD64_Script_MakeEffect;
EvtScript TTYD64_Script_TryToShrinkTarget;
EvtScript TTYD64_Script_Goombario_HandleEvent_Immune;
EvtScript TTYD64_Script_Goombario_Init_Ponder;
EvtScript TTYD64_Script_Ponder_GoBackToHome;
EvtScript TTYD64_Script_Ponder_Stylish;
EvtScript TTYD64_Script_Tattle_DoStylish;
EvtScript TTYD64_Script_Goombario_Multibonk_GetAmountToDeal;
EvtScript TTYD64_Script_Kooper_FirstStrike_GetMoveData;
EvtScript TTYD64_bc_EVS_Enemy_ShockHit;
EvtScript TTYD64_DoShockHit;
EvtScript TTYD64_UpdateHealthBarPos;
EvtScript TTYD64_bc_EVS_Player_HandleEvent;
EvtScript TTYD64_HandleEvent_Player;
EvtScript TTYD64_DoSuperguard;
EvtScript TTYD64_Script_DoStylish_Multibonk;
EvtScript TTYD64_Script_DoStylish_DizzyShell;
EvtScript TTYD64_Script_ShellToss_GoBackToHome_Succeed;
EvtScript TTYD64_Script_Bomb_DoStylish;
EvtScript TTYD64_Script_Slam_DoStylish;
EvtScript TTYD64_Script_TydalWave_GoBackToHome;
EvtScript TTYD64_Script_BellyFlop_GoBackToHome_Succeed;
EvtScript TTYD64_Script_DoStylishFX;
EvtScript TTYD64_Script_InitTracker;
EvtScript TTYD64_Script_NukeTracker;
EvtScript TTYD64_Script_TimingTutor;

// clang-format off
EvtScript TTYD64_Script_MakeEffect = {
    Call(PlayEffect_impl, LVar0, LVar1, 0, -4096, 0, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
    Call(TTYD64_GetEffect, LVarF, LVar6)
    Call(TTYD64_WritePtrField, LVar2, TTYD64_F_TTYD64_DEBUFFSCOUNTERS_FXPOINTERS_0_4U, LVar6)
    Call(TTYD64_ReadPtrField, LVar6, TTYD64_F_EFFECTINSTANCE_C_4U, LVar6)
    Switch(LVar3)
        CaseOrEq(0)
        CaseOrEq(1)
            IfLt(LVar4, 0)
                IfEq(LVar3, 0)
                    Set(LVar7, 3)
                Else
                    Set(LVar7, 1)
                EndIf
                Call(TTYD64_WritePtrField, LVar5, TTYD64_F_TTYD64_DEBUFFSCOUNTERS_DATA_0_1U, 1)
            Else
                IfEq(LVar3, 0)
                    Set(LVar7, 2)
                Else
                    Set(LVar7, 0)
                EndIf
            EndIf
            Call(TTYD64_WritePtrField, LVar6, TTYD64_F_EFFECT_DATA_1C_4U, LVar7)
            Call(TTYD64_WritePtrField, LVar6, TTYD64_F_EFFECT_DATA_20_4U, LVar4)
        EndCaseGroup
        CaseOrEq(2)
        CaseOrEq(3)
            IfLt(LVar4, 0)
                Call(TTYD64_WritePtrField, LVar5, TTYD64_F_TTYD64_DEBUFFSCOUNTERS_DATA_0_1U, 1)
            EndIf
            Call(TTYD64_WritePtrField, LVar6, TTYD64_F_EFFECT_DATA_40_4U, LVar4)
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript TTYD64_Script_TryToShrinkTarget = {
    Call(GetBattleFlags, LVar0)
    IfFlag(LVar0, -2147483648)
        Return
    EndIf
    Call(RandInt, 100, LVar0)
    IfLt(LVar0, 50)
        Call(GetOwnerTarget, LVar4, 0)
        Switch(LVar4)
            CaseEq(0)
                Call(GetPlayerHP, LVar0)
            CaseEq(256)
                Call(TTYD64_GetPartnerHP_API, LVar0)
            CaseDefault
                Call(GetActorHP, LVar4, LVar0)
        EndSwitch
        IfEq(LVar0, 0)
            Return
        EndIf
        Call(TTYD64_AddAttackBoost, LVar4, -1, 4)
        Call(TTYD64_MakeActorTiny, LVar4)
        Call(PlaySoundAtActor, LVar4, 8454)
        Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
        Add(LVar0, 15)
        Add(LVar1, 35)
        Set(LVar2, 6)
        Call(PlayEffect_impl, 86, 3, LVar0, LVar1, LVar2, Float(1.5), 60, 0, 0, 0, 0, 0, 0, 0)
        Call(TTYD64_GetEffectData, LVarF, LVar0)
        Call(TTYD64_WritePtrField, LVar0, TTYD64_F_STATCHANGEFXDATA_20_4U, -1)
        Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
        Add(LVar1, 15)
        Add(LVar2, 2)
        Call(PlayParalyzeHitFX)
    EndIf
    Return
    End
};

EvtScript TTYD64_Script_Goombario_HandleEvent_Immune = {
    Call(PlaySoundAtActor, 256, 8332)
    Call(TTYD64_GetPartnerExtraBattleData_API, 14, LVar0)
    IfEq(LVar0, 0)
        SetConst(LVar0, 1)
        SetConst(LVar1, 589824)
    Else
        SetConst(LVar0, 1)
        SetConst(LVar1, 589838)
    EndIf
    ExecWait(EVS_Partner_NoDamageHit)
    Return
    End
};

EvtScript TTYD64_Script_Goombario_Init_Ponder = {
    Exec(TTYD64_Script_NukeTracker)
    Call(UseBattleCamPreset, 14)
    Call(BattleCamTargetActor, 0)
    Call(MoveBattleCamOver, 15)
    Call(LoadActionCommand, 15)
    Call(action_command_squirt_init)
    Call(SetupMashMeter, 2, 80, 100, 0, 0, 0)
    Call(GetActorPos, -127, LVar0, LVar1, LVar2)
    Call(PlayEffect_impl, 16, 4, 0, LVar0, LVar1, LVar2, 24, 0, 25, 0, 0, 0, 0, 0)
    Wait(10)
    Call(SetAnimation, 256, -1, 589843)
    Call(action_command_squirt_start, 0, 64, 3)
    Loop(61)
        Wait(1)
    EndLoop
    Call(GetActionProgress, LVar0)
    Switch(LVar0)
        CaseGt(80)
            Call(PlaySoundAtActor, -127, 610)
            Call(GetActorPos, -127, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 16, 0, 0, LVar0, LVar1, LVar2, 24, 0, 25, 0, 0, 0, 0, 0)
            Call(SetAnimation, 256, -1, 589828)
            Wait(25)
        CaseDefault
            Call(GetActorPos, -127, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 16, 3, 0, LVar0, LVar1, LVar2, 24, 0, 25, 0, 0, 0, 0, 0)
            Call(SetAnimation, 256, -1, 589846)
            Wait(25)
            ExecWait(TTYD64_Script_Ponder_GoBackToHome)
            Return
    EndSwitch
    Call(GetStatusFlags, 0, LVar5)
    IfNotFlag(LVar5, 3526656)
        Call(TTYD64_TestBattleFlags2, BS_FLAGS2_PLAYER_TURN_USED, LVar0)
        IfEq(LVar0, 1)
            Set(LVarC, 1)
            Call(SetBattleFlagBits2, BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER, 1)
        Else
            Set(LVarC, 0)
        EndIf
        Call(UseIdleAnimation, 0, 0)
    EndIf
    Call(SetAnimation, 256, -1, 589826)
    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
    Add(LVar0, 35)
    Add(LVar2, 2)
    Call(SetGoalPos, -127, LVar0, LVar1, LVar2)
    Call(SetActorSpeed, -127, Float(4.0))
    Call(RunToGoal, -127, 0, 1)
    Call(MakeLerp, 0, -180, 3, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(SetActorRotation, -127, 0, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(SetAnimation, 256, -1, 589839)
    Wait(10)
    Exec(TTYD64_Script_InitTracker)
    IfNotFlag(LVar5, 3526656)
        Call(UseIdleAnimation, 0, 0)
        Call(RandInt, 4, LVar0)
        Switch(LVar0)
            CaseEq(0)
                Call(SetAnimation, 0, 0, 65569)
            CaseEq(1)
                Call(SetAnimation, 0, 0, 65538)
            CaseEq(2)
                Call(SetAnimation, 0, 0, 65571)
            CaseEq(3)
                Call(SetAnimation, 0, 0, 65567)
            CaseEq(4)
                Call(SetAnimation, 0, 0, 65542)
        EndSwitch
    EndIf
    Wait(20)
    IfNotFlag(LVar5, 3526656)
        Call(SetAnimation, 0, 0, 65576)
    EndIf
    Call(PlaySoundAtActor, -127, 610)
    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
    Add(LVar1, 15)
    Call(PlayEffect_impl, 16, 0, 0, LVar0, LVar1, LVar2, 24, 0, 25, 0, 0, 0, 0, 0)
    Wait(30)
    Call(SetAnimation, 256, -1, 589825)
    Exec(TTYD64_Script_Ponder_Stylish)
    IfNotFlag(LVar5, 3526656)
        Call(SetAnimation, 0, 0, 65577)
    EndIf
    Wait(25)
    IfNotFlag(LVar5, 3526656)
        Call(SetAnimation, 0, 0, 65586)
    EndIf
    Call(TTYD64_TestBattleFlags2, BS_FLAGS2_PLAYER_TURN_USED, LVar0)
    IfEq(LVar0, 1)
        Call(SetBattleFlagBits2, BS_FLAGS2_PLAYER_TURN_USED, 0)
    Else
        Call(TTYD64_WriteField, TTYD64_F_GBATTLESTATUS_8B_1U, 1)
    EndIf
    Call(MakeLerp, -180, 0, 3, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(SetActorRotation, -127, 0, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    ExecWait(TTYD64_Script_Ponder_GoBackToHome)
    Call(ShowMessageBox, 262, 60)
    Call(WaitForMessageBoxDone)
    Call(UseIdleAnimation, 0, 1)
    IfEq(LVarC, 1)
        Call(SetBattleFlagBits2, BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER, 0)
    EndIf
    Return
    End
};

EvtScript TTYD64_Script_Ponder_GoBackToHome = {
    Call(UseBattleCamPreset, 2)
    Call(SetGoalToHome, 256)
    Call(SetActorSpeed, 256, Float(4.0))
    Call(SetActorJumpGravity, 256, Float(1.7998046875))
    Call(SetAnimation, 256, -1, 589827)
    Call(RunToGoal, 256, 0)
    Call(SetAnimation, 256, -1, 589825)
    Return
    End
};

EvtScript TTYD64_Script_Ponder_Stylish = {
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Wait(1)
        Goto(0)
    EndIf
    Loop(5)
        ExecWait(TTYD64_Script_TimingTutor)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Call(TTYD64_StylishAddCount, LVar0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            Call(SetAnimation, 256, -1, 589840)
            Wait(15)
            Call(SetAnimation, 256, -1, 589825)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Return
        EndIf
        Wait(1)
    EndLoop
    Label(0)
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Return
    End
};

EvtScript TTYD64_Script_Tattle_DoStylish = {
    Thread
        ExecWait(TTYD64_Script_NukeTracker)
        Exec(TTYD64_Script_InitTracker)
        Loop(2)
            ExecWait(TTYD64_Script_TimingTutor)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                Call(TTYD64_StylishDisarm)
                Call(TTYD64_StylishConsume)
                Call(TTYD64_StylishAddCount, LVar0)
                Set(LVarA, 0)
                ExecWait(TTYD64_Script_DoStylishFX)
                Call(SetAnimation, 256, -1, 589840)
                Wait(15)
                Call(SetAnimation, 256, -1, 589825)
                Call(TTYD64_StylishDisarm)
                Call(TTYD64_StylishConsume)
                Return
            EndIf
            Wait(1)
        EndLoop
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
    EndThread
    Return
    End
};

EvtScript TTYD64_Script_Goombario_Multibonk_GetAmountToDeal = {
    Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_1D_1U, LVar0)
    IfEq(LVar0, 2)
        Set(LVar0, 3)
    Else
        Set(LVar0, 2)
    EndIf
    Return
    End
};

EvtScript TTYD64_Script_Kooper_FirstStrike_GetMoveData = {
    Call(GetActorLevel, 256, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(TTYD64_WriteField, TTYD64_F_GBATTLESTATUS_17C_2U, 137)
            Call(SetDamageSource, 6)
            Set(LVarF, 2)
            Set(LVarE, 1)
        CaseEq(1)
            Call(TTYD64_WriteField, TTYD64_F_GBATTLESTATUS_17C_2U, 138)
            Call(SetDamageSource, 6)
            Set(LVarF, 3)
            Set(LVarE, 2)
        CaseEq(2)
            Call(TTYD64_WriteField, TTYD64_F_GBATTLESTATUS_17C_2U, 139)
            Call(SetDamageSource, 6)
            Set(LVarF, 5)
            Set(LVarE, 3)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_bc_EVS_Enemy_ShockHit = {
    ExecWait(TTYD64_DoShockHit)
    Return
    End
};

EvtScript TTYD64_DoShockHit = {
    Call(SetActorRotationOffset, -127, 0, 0, 0)
    Call(SetActorRotation, -127, 0, 0, 0)
    Call(SetActorDispOffset, -127, 0, 0, 0)
    Call(TTYD64_ReadField, TTYD64_F_SUPERGUARD_BYTEFLAG_0_1U, LVar6)
    IfEq(LVar6, 1)
        Call(TTYD64_WriteField, TTYD64_F_SUPERGUARD_BYTEFLAG_0_1U, 0)
        Exec(TTYD64_UpdateHealthBarPos)
        Return
    EndIf
    ExecWait(EVS_Enemy_ShockHit_Impl)
    Return
    End
};

EvtScript TTYD64_UpdateHealthBarPos = {
    Call(HideHealthBar, -127)
    Call(HPBarToCurrent, -127)
    Call(ShowHealthBar, -127)
    Wait(21)
    Call(HideHealthBar, -127)
    Call(HPBarToHome, -127)
    Call(GetLastEvent, -127, LVar0)
    IfNe(LVar0, 38)
        Call(UseBattleCamPreset, 2)
    EndIf
    Return
    End
};

EvtScript TTYD64_bc_EVS_Player_HandleEvent = {
    Jump(TTYD64_HandleEvent_Player)
    Return
    End
};

EvtScript TTYD64_HandleEvent_Player = {
    Call(GetLastEvent, 0, LVarF)
    Switch(LVarF)
        CaseNe(50)
            Call(UseIdleAnimation, 0, 0)
    EndSwitch
    Call(InterruptActionCommand)
    Call(SetBattleFlagBits, 256, 0)
    Call(func_802693F0)
    Call(ForceDisablePlayerBlurImmediately)
    Call(GetLastEvent, 0, LVarF)
    Switch(LVarF)
        CaseOrEq(42)
        CaseOrEq(39)
            Call(SetActorRotation, -127, 0, 0, 0)
            Call(UseBattleCamPreset, 30)
            Call(GetGoalPos, 0, LVar0, LVar1, LVar2)
            Sub(LVar0, 60)
            Add(LVar1, 40)
            Call(SetActorJumpGravity, 0, Float(0.099609375))
            Call(SetJumpAnimations, 0, 0, 65562, 65562, 65562)
            Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
            Call(PlayerHopToGoal, 5, 0, 1)
            SetConst(LVar1, 65562)
            Set(LVar2, 0)
            ExecWait(EVS_Player_SimpleHit)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToHome, 0)
            Call(GetGoalPos, 0, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, 0, Float(1.400390625))
            Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
            Call(PlayerHopToGoal, 10, 0, 2)
            Sub(LVar0, 20)
            Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
            Call(PlayerHopToGoal, 7, 0, 2)
            Sub(LVar0, 10)
            Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
            Call(PlayerHopToGoal, 4, 0, 2)
            IfEq(LVarF, 39)
                Return
            EndIf
        EndCaseGroup
        CaseOrEq(44)
        CaseOrEq(36)
            Call(SetActorRotation, -127, 0, 0, 0)
            Call(UseBattleCamPreset, 31)
            Call(GetGoalPos, 0, LVar0, LVar1, LVar2)
            Sub(LVar0, 60)
            Add(LVar1, 40)
            Call(SetActorJumpGravity, 0, Float(0.099609375))
            Call(SetJumpAnimations, 0, 0, 327683, 327683, 327683)
            Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
            Call(PlayerHopToGoal, 5, 0, 1)
            ChildThread
                Call(GetActorPos, 0, LVar5, LVar6, LVar7)
                Add(LVar5, 5)
                Add(LVar6, 4)
                Add(LVar7, 5)
                Call(PlayEffect_impl, 36, 0, LVar5, LVar6, LVar7, Float(1.5), 15, 0, 0, 0, 0, 0, 0, 0)
                Wait(2)
                Call(GetActorPos, 0, LVar5, LVar6, LVar7)
                Add(LVar5, -5)
                Add(LVar6, 18)
                Add(LVar7, 5)
                Call(PlayEffect_impl, 36, 0, LVar5, LVar6, LVar7, Float(1.5), 15, 0, 0, 0, 0, 0, 0, 0)
            EndChildThread
            SetConst(LVar1, 327683)
            Set(LVar2, 0)
            ExecWait(EVS_Player_SimpleHit)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToHome, 0)
            Call(GetGoalPos, 0, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, 0, Float(1.400390625))
            Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
            Call(PlayerHopToGoal, 10, 0, 2)
            Sub(LVar0, 20)
            Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
            Call(PlayerHopToGoal, 7, 0, 2)
            Sub(LVar0, 10)
            Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
            Call(PlayerHopToGoal, 4, 0, 2)
            IfEq(LVarF, 36)
                Return
            EndIf
        EndCaseGroup
        CaseOrEq(47)
        CaseOrEq(38)
            Call(SetActorRotation, -127, 0, 0, 0)
            Call(UseBattleCamPreset, 31)
            Call(GetGoalPos, 0, LVar0, LVar1, LVar2)
            Sub(LVar0, 60)
            Add(LVar1, 40)
            Call(SetActorJumpGravity, 0, Float(0.099609375))
            Call(SetJumpAnimations, 0, 0, 65562, 65562, 65562)
            Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
            Call(PlayerHopToGoal, 5, 0, 1)
            Call(ShowShockEffect, -127)
            SetConst(LVar1, 65562)
            Set(LVar2, 0)
            ExecWait(EVS_Player_SimpleHit)
            Call(UseBattleCamPreset, 2)
            Call(SetGoalToHome, 0)
            Call(GetGoalPos, 0, LVar0, LVar1, LVar2)
            Add(LVar0, 30)
            Set(LVar1, 0)
            Call(SetActorJumpGravity, 0, Float(1.400390625))
            Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
            Call(PlayerHopToGoal, 10, 0, 2)
            Sub(LVar0, 20)
            Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
            Call(PlayerHopToGoal, 7, 0, 2)
            Sub(LVar0, 10)
            Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
            Call(PlayerHopToGoal, 4, 0, 2)
            IfEq(LVarF, 38)
                Return
            EndIf
        EndCaseGroup
        CaseEq(55)
            Call(TryPlayerLucky)
            IfEq(LVar0, 0)
                Call(SetAnimation, 0, 0, 196617)
                Wait(30)
                Call(SetAnimation, 0, 0, 65538)
            Else
                Wait(30)
            EndIf
        CaseEq(49)
            Call(SetActorJumpGravity, 0, Float(1.7998046875))
            Call(SetJumpAnimations, 0, 0, 65543, 65544, 65545)
            Call(GetActorPos, 0, LVar0, LVar1, LVar2)
            Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
            Call(PlayerHopToGoal, 15, 0, 0)
            Call(SetAnimation, 0, 0, 65538)
            Call(SetGoalToHome, 0)
            Call(SetActorSpeed, 0, Float(4.0))
            Call(SetAnimation, 0, 0, 65541)
            Call(PlayerRunToGoal, 0)
            Call(SetAnimation, 0, 0, 65538)
        CaseEq(50)
            Wait(10)
            Call(UseIdleAnimation, 0, 0)
            Call(SetActorJumpGravity, 0, Float(1.7998046875))
            Call(SetJumpAnimations, 0, 0, 65543, 65544, 65545)
            Call(GetActorPos, 0, LVar0, LVar1, LVar2)
            Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
            Call(PlayerHopToGoal, 15, 0, 0)
            Call(SetAnimation, 0, 0, 65538)
            Call(SetGoalToHome, 0)
            Call(SetActorSpeed, 0, Float(4.0))
            Call(SetAnimation, 0, 0, 65541)
            Call(PlayerRunToGoal, 0)
            Call(SetAnimation, 0, 0, 65538)
        CaseOrEq(9)
        CaseOrEq(10)
            SetConst(LVar1, 65559)
            Set(LVar2, 0)
            ExecWait(EVS_Player_ComplexHit)
            Call(SetAnimation, 0, 0, 65538)
        EndCaseGroup
        CaseOrEq(23)
        CaseOrEq(25)
            Call(PlaySoundAtActor, 0, 8332)
            Call(TTYD64_ReadField, TTYD64_F_EXTRAACTORDATA_EVERYONE_E_1U, LVar0)
            IfEq(LVar0, 0)
                SetConst(LVar1, 65538)
            Else
                SetConst(LVar1, 65557)
            EndIf
            ExecWait(EVS_Player_NoDamageHit)
        EndCaseGroup
        CaseOrEq(24)
        CaseOrEq(26)
            Call(PlaySoundAtActor, 0, 8332)
            SetConst(LVar0, 1)
            SetConst(LVar1, 65556)
            ExecWait(EVS_Player_NoDamageHit)
            Wait(10)
        EndCaseGroup
        CaseEq(14)
            SetConst(LVar1, 327683)
            Set(LVar2, 0)
            ExecWait(EVS_Player_SimpleHit)
            Call(SetAnimation, 0, 0, 65538)
        CaseEq(41)
            SetConst(LVar1, 327683)
            Set(LVar2, 0)
            ExecWait(EVS_Player_SimpleHit)
            Call(SetAnimation, 0, 0, 65538)
            Return
        CaseEq(32)
            SetConst(LVar1, 65559)
            Set(LVar2, 0)
            ExecWait(EVS_Player_SimpleHit)
            Return
        CaseEq(52)
            Call(SetActorJumpGravity, 0, Float(1.7998046875))
            Call(GetActorPos, 0, LVar7, LVar8, LVar9)
            Call(SetJumpAnimations, 0, 0, 65543, 65544, 65542)
            Call(SetGoalPos, 0, LVar7, LVar8, LVar9)
            Call(PlayerHopToGoal, 15, 0, 0)
            Call(SetAnimation, 0, 0, 65542)
        CaseEq(TTYD64_EVENT_SUPERGUARD)
            Set(LVar0, 0)
            Set(LVar1, 65552)
            ExecWait(TTYD64_DoSuperguard)
        CaseDefault
    EndSwitch
    Call(UseIdleAnimation, -127, 1)
    Return
    End
};

EvtScript TTYD64_DoSuperguard = {
    Call(SetAnimation, -127, LVar0, LVar1)
    Call(PlaySoundAtActor, -127, 567)
    Call(TTYD64_bc_PlayTextPopup, 3)
    Loop(2)
        Call(MakeLerp, 0, 360, 3, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(SetActorRotation, -127, 0, LVar0, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndLoop
    Call(MakeLerp, 0, 180, 4, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(SetActorRotation, -127, 0, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(MakeLerp, -180, 0, 7, 0)
    Loop(0)
        Call(UpdateLerp)
        Call(SetActorRotation, -127, 0, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(SetActorRotation, -127, 0, 0, 0)
    Wait(5)
    Return
    End
};

EvtScript TTYD64_Script_DoStylish_Multibonk = {
    Wait(2)
    Call(SetActorSpeed, 256, Float(8.0))
    Call(SetAnimation, 256, -1, 589827)
    Call(SetGoalToHome, -127)
    Call(GetGoalPos, -127, LVar0, LVar1, LVar2)
    Add(LVar0, 10)
    Call(SetGoalPos, -127, LVar0, LVar1, LVar2)
    Call(GetMenuSelection, 0, 0, LVar0)
    IfEq(LVar0, 136)
        Call(TTYD64_ReadField, TTYD64_F_GBATTLESTATUS_198_1U, LVar0)
        IfNe(LVar0, 0)
            Exec(TTYD64_Script_InitTracker)
            Thread
                Loop(0)
                    Call(GetDistanceToGoal, -127, LVarA)
                    IfLt(LVarA, 70)
                        Call(TTYD64_StylishPressed, LVar0)
                        IfEq(LVar0, 1)
                            Call(TTYD64_StylishDisarm)
                            Call(TTYD64_StylishConsume)
                            Goto(0)
                        Else
                            BreakLoop
                        EndIf
                    EndIf
                    Wait(1)
                EndLoop
                Loop(2)
                    ExecWait(TTYD64_Script_TimingTutor)
                    Call(TTYD64_StylishPressed, LVar0)
                    IfEq(LVar0, 1)
                        Call(TTYD64_StylishDisarm)
                        Call(TTYD64_StylishAddCount, LVar0)
                        Set(LVarA, 0)
                        ExecWait(TTYD64_Script_DoStylishFX)
                        Wait(1)
                        Goto(0)
                    EndIf
                    Wait(1)
                EndLoop
                Call(TTYD64_StylishDisarm)
                Call(TTYD64_StylishConsume)
                Label(0)
            EndThread
        EndIf
    EndIf
    Call(RunToGoal, 256, 0)
    Call(SetGoalToHome, -127)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(SetActorSpeed, 256, Float(1.0))
        Call(SetActorJumpGravity, -127, Float(1.5))
        Thread
            Call(MakeLerp, 0, 180, 3, 0)
            Loop(0)
                Call(UpdateLerp)
                Call(SetActorRotation, -127, 0, LVar0, 0)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
            Call(MakeLerp, -180, 0, 3, 0)
            Loop(0)
                Call(UpdateLerp)
                Call(SetActorRotation, -127, 0, LVar0, 0)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
            Call(SetActorRotation, -127, 0, 0, 0)
        EndThread
        Call(JumpToGoal, -127, 9, 0, 1, 1)
    Else
        Call(RunToGoal, 256, 0)
    EndIf
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Call(SetAnimation, 256, -1, 589825)
    Return
    End
};

EvtScript TTYD64_Script_DoStylish_DizzyShell = {
    Exec(TTYD64_Script_InitTracker)
    Wait(5)
    Call(TTYD64_StylishPressed, LVar0)
    Call(GetActionProgress, LVar1)
    IfLt(LVar1, 85)
        Set(LVar0, 1)
    EndIf
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Wait(1)
        Goto(0)
    EndIf
    Loop(4)
        ExecWait(TTYD64_Script_TimingTutor)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Call(TTYD64_StylishAddCount, LVar0)
            Call(TTYD64_WriteField, TTYD64_F_GACTIONCOMMANDSTATUS_60_1U, 0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            Call(SetActorSpeed, 256, Float(7.0))
            Call(GetActorPos, -127, LVar0, LVar1, LVar2)
            Exec(TTYD64_Script_InitTracker)
            Thread
                Wait(6)
                Call(TTYD64_StylishPressed, LVar0)
                IfEq(LVar0, 1)
                    Call(TTYD64_StylishDisarm)
                    Call(TTYD64_StylishConsume)
                    Wait(1)
                    Goto(1)
                EndIf
                Loop(2)
                    ExecWait(TTYD64_Script_TimingTutor)
                    Call(TTYD64_StylishPressed, LVar0)
                    IfEq(LVar0, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                Label(1)
            EndThread
            Call(PlaySound, 644)
            Sub(LVar0, 25)
            Call(SetGoalPos, -127, LVar0, LVar1, LVar2)
            Call(RunToGoal, 256, 0, 1)
            Add(LVar0, 25)
            Call(SetGoalPos, -127, LVar0, LVar1, LVar2)
            Call(RunToGoal, 256, 0, 1)
            Sub(LVar0, 25)
            Call(SetGoalPos, -127, LVar0, LVar1, LVar2)
            Call(RunToGoal, 256, 0, 1)
            Add(LVar0, 25)
            Call(SetGoalPos, -127, LVar0, LVar1, LVar2)
            Call(RunToGoal, 256, 0, 1)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                Call(TTYD64_StylishDisarm)
                Call(TTYD64_StylishConsume)
                Call(TTYD64_StylishAddCount, LVar0)
                Call(GetMenuSelection, 0, 0, LVar0)
                Call(TTYD64_WriteField, TTYD64_F_GACTIONCOMMANDSTATUS_60_1U, 0)
                Set(LVarA, 0)
                ExecWait(TTYD64_Script_DoStylishFX)
                Call(SetGoalToHome, -127)
                Call(PlaySoundAtActor, -127, 8205)
                Call(SetActorRotationOffset, -127, 0, 15, 0)
                Thread
                    SetTimescale(Float(3.0))
                    Loop(3)
                        Call(MakeLerp, 0, 180, 5, 0)
                        Loop(0)
                            Call(UpdateLerp)
                            Call(SetActorRotation, -127, 0, 0, LVar0)
                            Wait(1)
                            IfEq(LVar1, 0)
                                BreakLoop
                            EndIf
                        EndLoop
                        Call(MakeLerp, -180, 0, 5, 0)
                        Loop(0)
                            Call(UpdateLerp)
                            Call(SetActorRotation, -127, 0, 0, LVar0)
                            Wait(1)
                            IfEq(LVar1, 0)
                                BreakLoop
                            EndIf
                        EndLoop
                    EndLoop
                    SetTimescale(Float(1.0))
                    Call(SetActorRotationOffset, -127, 0, 0, 0)
                    Call(SetActorRotation, -127, 0, 0, 0)
                EndThread
                Call(SetActorJumpGravity, -127, Float(0.7998046875))
                Call(SetActorDispOffset, -127, 0, -4, 0)
                Call(JumpToGoal, -127, 19, 0, 0, 1)
                Call(SetActorDispOffset, -127, 0, 0, 0)
                Wait(1)
                Goto(2)
            EndIf
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Label(0)
    Call(SetActorSpeed, -127, Float(1.0))
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Label(2)
    Call(PartnerYieldTurn)
    Call(SetAnimation, 256, -1, 655375)
    Wait(15)
    Call(SetAnimation, 256, -1, 655364)
    Call(SetGoalToHome, 256)
    Call(SetActorSpeed, 256, Float(7.0))
    Call(SetAnimation, 256, -1, 655366)
    Call(RunToGoal, 256, 0)
    Call(SetAnimation, 256, -1, 655364)
    Return
    End
};

EvtScript TTYD64_Script_ShellToss_GoBackToHome_Succeed = {
    Call(ResetActorSounds, 256, 0)
    Thread
        Call(UseBattleCamPreset, 4)
        Wait(30)
        Call(UseBattleCamPreset, 2)
    EndThread
    Call(PartnerYieldTurn)
    Call(GetActorPos, 256, LVar0, LVar1, LVar2)
    Sub(LVar0, 60)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, 256, Float(1.400390625))
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Thread
        Exec(TTYD64_Script_InitTracker)
        Wait(5)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Wait(1)
            Goto(0)
        EndIf
        Loop(4)
            ExecWait(TTYD64_Script_TimingTutor)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                Call(TTYD64_StylishDisarm)
                Call(TTYD64_StylishConsume)
                Call(TTYD64_StylishAddCount, LVar0)
                Call(TTYD64_WriteField, TTYD64_F_GACTIONCOMMANDSTATUS_60_1U, 0)
                Set(LVarA, 0)
                ExecWait(TTYD64_Script_DoStylishFX)
                SetTimescale(Float(1.5))
                Call(SetActorRotationOffset, -127, 0, 15, 0)
                Loop(3)
                    Call(MakeLerp, 0, -180, 3, 0)
                    Loop(0)
                        Call(UpdateLerp)
                        Call(SetActorRotation, -127, LVar0, 0, -90)
                        Wait(1)
                        IfEq(LVar1, 0)
                            BreakLoop
                        EndIf
                    EndLoop
                    Call(MakeLerp, -180, 0, 3, 0)
                    Loop(0)
                        Call(UpdateLerp)
                        Call(SetActorRotation, -127, LVar0, 0, -90)
                        Wait(1)
                        IfEq(LVar1, 0)
                            BreakLoop
                        EndIf
                    EndLoop
                EndLoop
                SetTimescale(Float(1.0))
                Call(SetActorRotationOffset, -127, 0, 0, 0)
                Call(SetActorRotation, -127, 0, 0, 0)
                Wait(1)
                Goto(0)
            EndIf
            Wait(1)
        EndLoop
        Label(1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Label(0)
    EndThread
    Call(JumpToGoal, 256, 20, 0, 1, 0)
    Sub(LVar0, 30)
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Call(JumpToGoal, 256, 8, 0, 0, 1)
    Exec(TTYD64_Script_InitTracker)
    Sub(LVar0, 20)
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Call(JumpToGoal, 256, 6, 0, 0, 1)
    Sub(LVar0, 10)
    Call(JumpToGoal, 256, 4, 0, 0, 1)
    Call(SetGoalToHome, 256)
    Wait(2)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Wait(1)
        Goto(2)
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
            Call(SetActorRotationOffset, -127, 0, 15, 0)
            Thread
                SetTimescale(Float(3.0))
                Loop(3)
                    Call(MakeLerp, 0, 180, 5, 0)
                    Loop(0)
                        Call(UpdateLerp)
                        Call(SetActorRotation, -127, 0, 0, LVar0)
                        Wait(1)
                        IfEq(LVar1, 0)
                            BreakLoop
                        EndIf
                    EndLoop
                    Call(MakeLerp, -180, 0, 5, 0)
                    Loop(0)
                        Call(UpdateLerp)
                        Call(SetActorRotation, -127, 0, 0, LVar0)
                        Wait(1)
                        IfEq(LVar1, 0)
                            BreakLoop
                        EndIf
                    EndLoop
                EndLoop
                SetTimescale(Float(1.0))
                Call(SetActorRotationOffset, -127, 0, 0, 0)
                Call(SetActorRotation, -127, 0, 0, 0)
            EndThread
            Call(SetActorJumpGravity, -127, Float(0.7998046875))
            Call(SetActorDispOffset, -127, 0, -4, 0)
            Call(JumpToGoal, -127, 19, 0, 0, 1)
            Call(SetActorDispOffset, -127, 0, 0, 0)
            Wait(5)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Label(2)
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Call(SetAnimation, 256, -1, 655375)
    Wait(4)
    Call(SetActorSpeed, 256, Float(7.0))
    Call(SetAnimation, 256, -1, 655366)
    Call(RunToGoal, 256, 0)
    Call(SetAnimation, 256, -1, 655364)
    Return
    End
};

EvtScript TTYD64_Script_Bomb_DoStylish = {
    Call(PartnerYieldTurn)
    Call(SetGoalToHome, -127)
    Call(GetGoalPos, -127, LVar0, LVar1, LVar2)
    Add(LVar0, 25)
    Add(LVar1, 200)
    Call(SetActorPos, -127, LVar0, LVar1, LVar2)
    Call(SetGoalToHome, -127)
    Call(SetActorSpeed, -127, Float(4.0))
    Call(SetActorJumpGravity, -127, Float(0.599609375))
    Call(SetAnimation, -127, -1, 720923)
    Call(GetGoalPos, -127, LVar0, LVar1, LVar2)
    Add(LVar1, 60)
    Call(SetGoalPos, -127, LVar0, LVar1, LVar2)
    Thread
        Wait(20)
        Call(GetActorRotation, -127, 0, 0, LVar0)
        Loop(0)
            Call(SetActorRotation, -127, 0, 0, LVar0)
            Add(LVar0, 33)
            Call(GetActorPos, -127, 0, LVar1, 0)
            Call(GetActorPos, 0, 0, LVar2, 0)
            IfLe(LVar1, LVar2)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Call(SetActorRotation, -127, 0, 0, 0)
    EndThread
    Thread
        Exec(TTYD64_Script_InitTracker)
        Wait(16)
        Call(TTYD64_StylishPressed, LVar0)
        Call(GetActionProgress, LVar1)
        IfNe(LVar1, 100)
            Set(LVar0, 1)
        EndIf
        IfEq(LVar0, 1)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Wait(1)
            Goto(0)
        EndIf
        Loop(2)
            ExecWait(TTYD64_Script_TimingTutor)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Label(0)
    EndThread
    Call(JumpToGoal, -127, 20, 0, 0, 0)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Label(1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Call(TTYD64_StylishAddCount, LVar0)
        Call(GetMenuSelection, 0, 0, LVar0)
        Call(TTYD64_WriteField, TTYD64_F_GACTIONCOMMANDSTATUS_60_1U, 0)
        Call(TTYD64_StylishGetCount, LVar0)
        IfGt(LVar0, 3)
            Set(LVarA, 1)
        Else
            Set(LVarA, 0)
        EndIf
        ExecWait(TTYD64_Script_DoStylishFX)
        Call(GetActorPos, -127, LVar0, LVar1, LVar2)
        Call(PlaySound, 8214)
        Set(LVar3, LVar2)
        Sub(LVar3, 10)
        Set(LVar4, LVar1)
        Sub(LVar4, 13)
        Call(TTYD64_Function_ExplotionFX, LVar0, LVar4, LVar3)
        Thread
            Call(ShakeCam, 1, 0, 2, Float(0.5))
            Call(ShakeCam, 1, 0, 5, Float(2.0))
            Call(ShakeCam, 1, 0, 10, Float(3.0))
            Call(ShakeCam, 1, 0, 5, Float(2.0))
            Call(ShakeCam, 1, 0, 3, Float(1.5))
            Call(ShakeCam, 1, 0, 4, Float(0.80078125))
            Call(ShakeCam, 1, 0, 6, Float(0.30078125))
            Call(ShakeCam, 1, 0, 8, Float(0.1005859375))
        EndThread
        Call(SetGoalPos, -127, LVar0, LVar1, LVar2)
        Call(SetActorJumpGravity, 256, Float(1.400390625))
        Thread
            Exec(TTYD64_Script_InitTracker)
            Wait(4)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                Call(TTYD64_StylishDisarm)
                Call(TTYD64_StylishConsume)
                Wait(1)
                Goto(2)
            EndIf
            Loop(2)
                ExecWait(TTYD64_Script_TimingTutor)
                Call(TTYD64_StylishPressed, LVar0)
                IfEq(LVar0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            Label(2)
        EndThread
        Call(JumpToGoal, 256, 20, 0, 0, 0)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Wait(1)
            Goto(1)
        EndIf
    EndIf
    Call(SetActorJumpGravity, -127, Float(0.0))
    Call(SetGoalToHome, -127)
    Call(JumpToGoal, -127, 6, 0, 1, 0)
    Call(SetAnimation, -127, -1, 720900)
    Return
    End
};

EvtScript TTYD64_Script_Slam_DoStylish = {
    Call(UseBattleCamPreset, 4)
    Call(MoveBattleCamOver, 10)
    Call(SetAnimation, 256, -1, 720913)
    Call(GetGoalPos, 256, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Add(LVar1, 60)
    Call(SetActorJumpGravity, 256, Float(0.7998046875))
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Thread
        Exec(TTYD64_Script_InitTracker)
        Wait(15)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Wait(1)
            Goto(0)
        EndIf
        Loop(4)
            ExecWait(TTYD64_Script_TimingTutor)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Label(0)
    EndThread
    Call(JumpToGoal, 256, 25, 0, 0, 0)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(TTYD64_StylishDisarm)
        Call(TTYD64_StylishConsume)
        Call(TTYD64_StylishAddCount, LVar0)
        Call(TTYD64_WriteField, TTYD64_F_GACTIONCOMMANDSTATUS_60_1U, 0)
        Set(LVarA, 0)
        ExecWait(TTYD64_Script_DoStylishFX)
        Call(GetActorPos, -127, LVar0, LVar1, LVar2)
        Call(PlaySound, 8214)
        Set(LVar3, LVar2)
        Sub(LVar3, 2)
        Call(TTYD64_Function_ExplotionFX, LVar0, LVar1, LVar3)
        Thread
            Call(ShakeCam, 1, 0, 2, Float(0.5))
            Call(ShakeCam, 1, 0, 5, Float(2.0))
            Call(ShakeCam, 1, 0, 10, Float(3.0))
            Call(ShakeCam, 1, 0, 5, Float(2.0))
            Call(ShakeCam, 1, 0, 3, Float(1.5))
            Call(ShakeCam, 1, 0, 4, Float(0.80078125))
            Call(ShakeCam, 1, 0, 6, Float(0.30078125))
            Call(ShakeCam, 1, 0, 8, Float(0.1005859375))
        EndThread
        Sub(LVar0, 60)
        Call(SetGoalPos, -127, LVar0, LVar1, LVar2)
        Call(SetActorJumpGravity, 256, Float(1.400390625))
        Call(SetAnimation, 256, -1, 720906)
        Thread
            SetTimescale(Float(3.0))
            Loop(8)
                Call(MakeLerp, 0, -180, 3, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, -127, 0, LVar0, 0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
                Call(MakeLerp, -180, 0, 3, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, -127, 0, LVar0, 0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
            EndLoop
            SetTimescale(Float(1.0))
            Call(SetActorRotation, -127, 0, 0, 0)
        EndThread
        Thread
            Exec(TTYD64_Script_InitTracker)
            Wait(4)
            Call(TTYD64_StylishPressed, LVar0)
            IfEq(LVar0, 1)
                Call(TTYD64_StylishDisarm)
                Call(TTYD64_StylishConsume)
                Wait(1)
                Goto(1)
            EndIf
            Loop(2)
                ExecWait(TTYD64_Script_TimingTutor)
                Call(TTYD64_StylishPressed, LVar0)
                IfEq(LVar0, 1)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            Label(1)
        EndThread
        Call(JumpToGoal, 256, 15, 0, 0, 0)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 1)
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
            Call(TTYD64_StylishAddCount, LVar0)
            Call(TTYD64_WriteField, TTYD64_F_GACTIONCOMMANDSTATUS_60_1U, 0)
            Set(LVarA, 0)
            ExecWait(TTYD64_Script_DoStylishFX)
            Call(GetActorPos, -127, LVar0, LVar1, LVar2)
            Call(PlaySound, 8214)
            Set(LVar3, LVar2)
            Sub(LVar3, 2)
            Call(TTYD64_Function_ExplotionFX, LVar0, LVar1, LVar3)
            Thread
                Call(ShakeCam, 1, 0, 2, Float(0.5))
                Call(ShakeCam, 1, 0, 5, Float(2.0))
                Call(ShakeCam, 1, 0, 10, Float(3.0))
                Call(ShakeCam, 1, 0, 5, Float(2.0))
                Call(ShakeCam, 1, 0, 3, Float(1.5))
                Call(ShakeCam, 1, 0, 4, Float(0.80078125))
                Call(ShakeCam, 1, 0, 6, Float(0.30078125))
                Call(ShakeCam, 1, 0, 8, Float(0.1005859375))
            EndThread
            Call(SetGoalToHome, -127)
            Call(SetActorJumpGravity, 256, Float(1.400390625))
            Call(SetAnimation, 256, -1, 720906)
            Thread
                SetTimescale(Float(3.0))
                Loop(6)
                    Call(MakeLerp, 0, -180, 3, 0)
                    Loop(0)
                        Call(UpdateLerp)
                        Call(SetActorRotation, -127, 0, LVar0, 0)
                        Wait(1)
                        IfEq(LVar1, 0)
                            BreakLoop
                        EndIf
                    EndLoop
                    Call(MakeLerp, -180, 0, 3, 0)
                    Loop(0)
                        Call(UpdateLerp)
                        Call(SetActorRotation, -127, 0, LVar0, 0)
                        Wait(1)
                        IfEq(LVar1, 0)
                            BreakLoop
                        EndIf
                    EndLoop
                EndLoop
                SetTimescale(Float(1.0))
                Call(SetActorRotation, -127, 0, 0, 0)
            EndThread
            Call(JumpToGoal, 256, 15, 0, 0, 0)
        EndIf
    EndIf
    Call(GetActorPos, -127, LVar0, LVar1, LVar2)
    Sub(LVar0, 8)
    Call(GetActorPos, 0, 0, LVar1, 0)
    Sub(LVar1, 2)
    Call(SetGoalPos, -127, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, 256, Float(0.0))
    Call(SetAnimation, 256, -1, 720910)
    Call(JumpToGoal, 256, 8, 0, 0, 0)
    Call(SetActorJumpGravity, 256, Float(1.400390625))
    Call(SetAnimation, 256, -1, 720910)
    Wait(1)
    Call(TTYD64_StylishGetCount, LVar3)
    IfLt(LVar3, 2)
        Call(SetAnimation, 256, -1, 720913)
        Sub(LVar0, 30)
        Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
        Call(JumpToGoal, 256, 8, 0, 1, 0)
        Call(SetAnimation, 256, -1, 720910)
        Wait(1)
        Call(SetAnimation, 256, -1, 720913)
        Sub(LVar0, 20)
        Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
        Call(JumpToGoal, 256, 6, 0, 1, 0)
        Call(SetAnimation, 256, -1, 720910)
        Wait(1)
        Call(SetAnimation, 256, -1, 720913)
        Sub(LVar0, 10)
        Call(JumpToGoal, 256, 4, 0, 1, 0)
        Call(SetAnimation, 256, -1, 720910)
        Wait(1)
    Else
        Wait(10)
    EndIf
    Call(SetAnimation, 256, -1, 720900)
    Wait(8)
    Call(ResetActorSounds, 256, 0)
    Call(SetGoalToHome, 256)
    Call(SetActorSpeed, 256, Float(5.0))
    Call(SetAnimation, 256, -1, 720904)
    Call(RunToGoal, 256, 0)
    Call(SetAnimation, 256, -1, 720900)
    Return
    End
};

EvtScript TTYD64_Script_TydalWave_GoBackToHome = {
    Thread
        Wait(10)
        Call(TTYD64_StylishPressed, LVar1)
        IfEq(LVar1, 0)
            Loop(4)
                ExecWait(TTYD64_Script_TimingTutor)
                Call(TTYD64_StylishPressed, LVar1)
                IfEq(LVar1, 1)
                    Call(TTYD64_StylishDisarm)
                    Call(TTYD64_StylishAddCount, LVar1)
                    Set(LVarA, 0)
                    ExecWait(TTYD64_Script_DoStylishFX)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        Else
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
        EndIf
    EndIf
    EndThread
    Call(JumpToGoal, 256, 20, 0, 1, 0)
    Call(TTYD64_StylishPressed, LVar1)
    IfEq(LVar1, 1)
    Call(PlaySoundAtActor, -127, 8244)
    Thread
        Call(SetActorRotationOffset, -127, 0, 12, 0)
        SetTimescale(Float(3.0))
        Call(MakeLerp, 0, -180, 8, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(SetActorRotation, -127, 0, 0, LVar0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(MakeLerp, 180, 0, 8, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(SetActorRotation, -127, 0, 0, LVar0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        SetTimescale(Float(1.0))
        Call(SetActorRotation, -127, 0, 0, 0)
        Call(SetActorRotationOffset, -127, 0, 9, 0)
    EndThread
    Call(GetActorPos, -127, LVar0, LVar1, LVar2)
    Call(SetGoalPos, -127, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, -127, Float(1.2001953125))
    Call(JumpToGoal, -127, 20, 0, 0, 0)
    EndIf
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Call(JumpToGoal, 256, 10, 0, 1, 0)
    Return
    End
};

EvtScript TTYD64_Script_BellyFlop_GoBackToHome_Succeed = {
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Thread
            Call(SetActorRotationOffset, -127, 0, 12, 0)
            SetTimescale(Float(3.0))
            Loop(6)
                Call(MakeLerp, 0, -180, 3, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, -127, 0, 0, LVar0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
                Call(MakeLerp, -180, 0, 3, 0)
                Loop(0)
                    Call(UpdateLerp)
                    Call(SetActorRotation, -127, 0, 0, LVar0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
            EndLoop
            SetTimescale(Float(1.0))
            Call(SetActorRotation, -127, 0, 0, 0)
            Call(SetActorRotationOffset, -127, 0, 9, 0)
        EndThread
    EndIf
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Exec(TTYD64_Script_InitTracker)
    Call(PartnerYieldTurn)
    Call(UseBattleCamPreset, 4)
    Call(SetAnimation, 256, -1, 983046)
    Call(GetActorPos, 256, LVar0, LVar1, LVar2)
    Sub(LVar0, 60)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, 256, Float(1.400390625))
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Call(JumpToGoal, 256, 20, 0, 1, 0)
    Sub(LVar0, 30)
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Call(JumpToGoal, 256, 8, 0, 1, 0)
    Sub(LVar0, 20)
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Thread
        Wait(2)
        Call(TTYD64_StylishPressed, LVar0)
        IfEq(LVar0, 0)
            Loop(4)
                ExecWait(TTYD64_Script_TimingTutor)
                Call(TTYD64_StylishPressed, LVar0)
                IfEq(LVar0, 1)
                    Call(TTYD64_StylishDisarm)
                    Call(TTYD64_StylishAddCount, LVar0)
                    Set(LVarA, 0)
                    ExecWait(TTYD64_Script_DoStylishFX)
                    Wait(1)
                    Goto(0)
                EndIf
                Wait(1)
            EndLoop
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
        Else
            Call(TTYD64_StylishDisarm)
            Call(TTYD64_StylishConsume)
        EndIf
        Label(0)
    EndThread
    Call(JumpToGoal, 256, 6, 0, 1, 0)
    Sub(LVar0, 10)
    Call(JumpToGoal, 256, 4, 0, 1, 0)
    Call(TTYD64_StylishPressed, LVar0)
    IfEq(LVar0, 1)
        Call(SetAnimation, 256, -1, 983057)
        Wait(25)
    EndIf
    Call(TTYD64_StylishDisarm)
    Call(TTYD64_StylishConsume)
    Call(SetAnimation, 256, -1, 983041)
    Wait(15)
    Call(SetGoalToHome, 256)
    Call(SetActorSpeed, 256, Float(6.0))
    Call(SetAnimation, 256, -1, 983043)
    Call(RunToGoal, 256, 0)
    Call(SetAnimation, 256, -1, 983041)
    Return
    End
};

EvtScript TTYD64_Script_DoStylishFX = {
    IfEq(TTYD64_ModFlag(TTYD64_MF_Flag_DisableFanfare), 0)
        Call(PlaySound, 138)
    EndIf
    Call(GetActorPos, -127, LVar0, LVar1, LVar2)
    Set(LVar4, LVar0)
    Set(LVar3, LVar2)
    Sub(LVar4, 20)
    Sub(LVar3, 5)
    Add(LVar1, 20)
    Call(TTYD64_StylishGetCount, LVar5)
    Switch(LVar5)
        CaseLe(1)
            Call(PlayEffect_impl, 72, 0, LVar4, LVar1, LVar3, 7, 20)
        CaseEq(2)
            Call(PlayEffect_impl, 72, 1, LVar4, LVar1, LVar3, 7, 20)
        CaseGe(3)
            Call(PlayEffect_impl, 72, 2, LVar4, LVar1, LVar3, 7, 20)
    EndSwitch
    Switch(LVar5)
        CaseLe(1)
            Call(PlaySound, 593)
        CaseEq(2)
            Call(PlaySound, 594)
        CaseEq(3)
            Call(PlaySound, 595)
        CaseEq(4)
            Call(PlaySound, 596)
        CaseEq(5)
            Call(PlaySound, 597)
        CaseEq(6)
            Call(PlaySound, 598)
        CaseGe(7)
            Call(PlaySound, 599)
    EndSwitch
    IfEq(LVarA, 1)
        Return
    EndIf
    Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_28E_1U, LVar3)
    IfNe(LVar3, 0)
        Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_290_2U, LVar4)
        Set(LVar5, LVar4)
        Add(LVar4, 32)
        Switch(LVar3)
            CaseEq(1)
                IfGe(LVar4, 256)
                    Set(LVar4, 256)
                EndIf
            CaseEq(2)
                IfGe(LVar4, 512)
                    Set(LVar4, 512)
                EndIf
            CaseEq(3)
                IfGe(LVar4, 768)
                    Set(LVar4, 768)
                EndIf
            CaseEq(4)
                IfGe(LVar4, 1024)
                    Set(LVar4, 1024)
                EndIf
            CaseEq(5)
                IfGe(LVar4, 1280)
                    Set(LVar4, 1280)
                EndIf
            CaseEq(6)
                IfGe(LVar4, 1536)
                    Set(LVar4, 1536)
                EndIf
            CaseEq(7)
                IfGe(LVar4, 1792)
                    Set(LVar4, 1792)
                EndIf
        EndSwitch
        IfNe(LVar4, LVar5)
            Call(PlayEffect_impl, 17, 0, LVar0, LVar1, LVar2, 20)
        EndIf
        Call(TTYD64_WriteField, TTYD64_F_GPLAYERDATA_290_2U, LVar4)
    EndIf
    Return
    End
};

EvtScript TTYD64_Script_InitTracker = {
    Call(TTYD64_StylishArm)
    Return
    End
};

EvtScript TTYD64_Script_NukeTracker = {
    Call(TTYD64_StylishReset)
    Return
    End
};

EvtScript TTYD64_Script_TimingTutor = {
    Set(LVar0, 301)
    ExecWait(TTYD64_IsBadgeEquipped_Script)
    IfEq(TTYD64_ModFlag(TTYD64_MF_Flag_StylishTutorial), 1)
        Set(LVar0, 1)
    EndIf
    IfEq(LVar0, 1)
        Call(GetActorPos, -127, LVar0, LVar1, LVar2)
        Add(LVar1, 18)
        Call(PlayEffect_impl, 16, 0, 0, LVar0, LVar1, LVar2, 16, 85, 3)
    EndIf
    Return
    End
};
// clang-format on
