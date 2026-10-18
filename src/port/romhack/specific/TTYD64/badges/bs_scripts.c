#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "badges_internal.h"
#include "../include/ttyd64_api.h"
#include "../include/ttyd64_symbols.h"
#include "../include/ttyd64_rawmem.h"

extern EvtScript EVS_ExecuteMarioAction;
extern EvtScript EVS_MerleeAttackBonus;
extern EvtScript EVS_MerleeDefenseBonus;
extern EvtScript EVS_MerleeExpBonus;
extern EvtScript EVS_PlayerDies;
extern EvtScript EVS_PlayerFirstStrike;
extern EvtScript EVS_PlayerHappy;
extern EvtScript EVS_Player_Celebrate;
extern EvtScript EVS_RunAwayFail;
extern EvtScript EVS_RunAwayNoCommand;
extern EvtScript EVS_RunAwayStart;
extern EvtScript EVS_StartDefend;
extern EvtScript EVS_UseLifeShroom;

API_CALLABLE(PlayParalyzeHitFX);
API_CALLABLE(func_80260E38);
API_CALLABLE(func_80260E5C);
API_CALLABLE(DetermineAutoRunAwaySuccess);
API_CALLABLE(SetFledBattleFlag);
API_CALLABLE(SpawnTurnEndFX);
API_CALLABLE(RemoveTurnEndFX);

// clang-format off
EvtScript TTYD64_Script_Defend = {
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetOwnerID, LVar0)
    IfLt(LVar0, 0x200)
        IfEq(LVar0, 0x100)
            Call(SetBattleFlagBits2, 8, 1)
            Set(LVar0, 0)
            Exec(Ref(TTYD64_SetPartnerAnimation_Battle))
        EndIf
        Thread
            Call(GetActorRotation, ACTOR_SELF, LVar0, LVar1, LVar2)
            Set(LVar3, 0xF)
            Loop(LVar3)
                Add(LVar1, 0x36)
                IfGt(LVar1, 0x168)
                    Set(LVar1, 0)
                EndIf
                Call(SetActorRotation, ACTOR_SELF, LVar0, LVar1, LVar2)
                IfEq(LVar3, 2)
                    Call(GetOwnerID, LVar0)
                    Switch(LVar0)
                        CaseEq(0)
                            Call(SetAnimation, 0, 0, 0x10014)
                        CaseEq(0x100)
                            Call(SetBattleFlagBits2, 0x10, 1)
                            Set(LVar0, 6)
                            Exec(Ref(TTYD64_SetPartnerAnimation_Battle))
                    EndSwitch
                EndIf
                Wait(1)
            EndLoop
            Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
        EndThread
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 0xF)
    Call(PlaySoundAtActor, ACTOR_SELF, 0x208F)
    Wait(0xD)
    Call(GetOwnerID, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(TTYD64_ReadField, TTYD64_F_EXTRAACTORDATA_EVERYONE_E_1U, LVar0)
            Add(LVar0, 1)
            Call(TTYD64_WriteField, TTYD64_F_EXTRAACTORDATA_EVERYONE_E_1U, LVar0)
        CaseEq(0x100)
            Call(TTYD64_GetPartnerExtraBattleData_API, 0xE, LVar0)
            Add(LVar0, 1)
            Call(TTYD64_SetPartnerExtraBattleData_API, 0xE, LVar0)
        CaseDefault
            Call(TTYD64_BoostDefense, ACTOR_SELF, 1, 2)
    EndSwitch
    Call(GetOwnerID, LVar0)
    IfLt(LVar0, 0x200)
        Call(ShowMessageBox, 0x108, 0x3C)
        Call(WaitForMessageBoxDone)
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};

EvtScript TTYD64_Script_Dispatch_DefendORCharge = {
    Call(GetMenuSelection, 0, 0, LVar0)
    IfEq(LVar0, 0)
        ExecWait(Ref(TTYD64_Script_Defend))
    Else
        ExecWait(Ref(TTYD64_Script_ChargeCommand))
    EndIf
    Return
    End
};

EvtScript TTYD64_Script_ChargeCommand = {
    Call(GetOwnerID, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(TTYD64_bs_IsBadgeActivated_Stack_API, 0x16D, LVarE)
        CaseEq(0x100)
            Call(TTYD64_bs_IsBadgeActivated_Stack_API, 0x17D, LVarE)
        CaseDefault
            Set(LVarE, 1)
    EndSwitch
    IfLt(LVar0, 0x200)
        Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_5_1U, LVar0)
        Sub(LVar0, LVarE)
        IfLt(LVar0, 0)
            Set(LVar0, 0)
        EndIf
        Call(TTYD64_WriteField, TTYD64_F_GPLAYERDATA_5_1U, LVar0)
        Call(TTYD64_GetGlitzChallenge, LVar0)
        IfEq(LVar0, 0xF)
            Call(TTYD64_SetGlitzStatus, -1)
        EndIf
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 0)
    Call(GetOwnerID, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetBattleFlagBits2, 8, 1)
            Call(SetAnimation, 0, 0, 0x10005)
        CaseEq(0x100)
            Call(SetBattleFlagBits2, 0x10, 1)
            Set(LVar0, 2)
            Exec(Ref(TTYD64_SetPartnerAnimation_Battle))
        CaseDefault
    EndSwitch
    Call(GetOwnerID, LVar0)
    IfLt(LVar0, 0x200)
        Wait(0x14)
        Call(GetActorRotation, ACTOR_SELF, LVar0, LVar1, LVar2)
        Set(LVar3, 0x14)
        Loop(LVar3)
            Sub(LVar1, 0x24)
            IfLt(LVar1, -360)
                Set(LVar1, 0)
            EndIf
            Call(SetActorRotation, ACTOR_SELF, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
        Call(SetActorRotation, ACTOR_SELF, 0, 0, 0)
        Wait(0xF)
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Add(LVar1, 0xF)
    Add(LVar2, 2)
    Call(PlaySoundAtActor, ACTOR_SELF, 0x208F)
    Call(PlayEffect_impl, 0x52, 7, LVar0, LVar1, LVar2, Float(1.0), 0x23, 0, 0, 0, 0, 0, 0, 0)
    Wait(0x23)
    Call(PlayParalyzeHitFX)
    Call(PlaySound, 0x208E)
    Add(LVar0, 0x14)
    Add(LVar1, 5)
    Add(LVar2, 1)
    Call(PlayEffect_impl, 0x56, 9, LVar0, LVar1, LVar2, Float(1.0), 0x1E, 0, 0, 0, 0, 0, 0, 0)
    Call(TTYD64_GetEffectData, LVarF, LVar0)
    Set(LVar1, LVarE)
    Add(LVar1, 1)
    Call(TTYD64_WritePtrField, LVar0, TTYD64_F_STATCHANGEFXDATA_20_4U, LVar1)
    Call(GetOwnerID, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Call(SetAnimation, 0, 0, 0x10002)
            Call(SetAnimation, 0, 0, 0x10032)
        CaseEq(0x100)
            Set(LVar0, 5)
            Exec(Ref(TTYD64_SetPartnerAnimation_Battle))
        CaseDefault
    EndSwitch
    IfGt(LVarE, 1)
        Set(LVar0, LVarE)
        Add(LVar0, 1)
    Else
        Set(LVar0, 2)
    EndIf
    Call(TTYD64_GetActorPointer, ACTOR_SELF, LVar2)
    Call(TTYD64_ReadPtrField, LVar2, TTYD64_F_ACTOR_192_2U, LVar2)
    Call(TTYD64_GetActorExtraData, LVar2, 0xF, LVar1)
    Add(LVar1, LVar0)
    Call(TTYD64_SetActorExtraData, LVar2, 0xF, LVar1)
    Wait(0x1E)
    Call(GetOwnerID, LVar0)
    IfLt(LVar0, 0x200)
        Call(ShowMessageBox, 0x47, 0x3C)
        Call(WaitForMessageBoxDone)
    EndIf
    Call(UseIdleAnimation, ACTOR_SELF, 1)
    Return
    End
};

EvtScript TTYD64_Script_Dispatch_BattleState19 = {
    ExecGetTID(Ref(TTYD64_Script_Dispatch_DefendORCharge), LVar0)
    Call(TTYD64_SetDefendThread, LVar0)
    Return
    End
};

EvtScript TTYD64_RunAwayStart_Animationless = {
    Call(SetBattleFlagBits, 0x100000, 0)
    Call(ShowActionHud, 1)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Call(LoadActionCommand, 3)
    Call(action_command_flee_init, LVar0)
    Call(SetupMashMeter, 1, 0x64, 0, 0, 0, 0)
    Call(func_80260E38)
    Wait(1)
    Wait(1)
    Wait(1)
    Wait(1)
    Wait(1)
    Wait(5)
    Call(action_command_flee_start, 0, 0x3C, 3)
    Call(func_80260E5C)
    Wait(5)
    Wait(2)
    Wait(5)
    Wait(2)
    Wait(2)
    Wait(5)
    Wait(2)
    Wait(5)
    Wait(0xF)
    Wait(0x1E)
    Call(GetSmashActionQuality, LVar0)
    Call(DetermineAutoRunAwaySuccess)
    IfEq(LVar0, 1)
        Call(SetFledBattleFlag)
        Call(PlaySoundAtActor, 0, 0x15E)
        Wait(5)
    Else
        Loop(0xA)
            Wait(1)
        EndLoop
        Wait(0xF)
        Wait(0x14)
        Wait(5)
        Call(UseBattleCamPreset, 2)
        Wait(0xA)
    EndIf
    Return
    End
};

EvtScript TTYD64_PlayerScriptDispatcher = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(Ref(EVS_ExecuteMarioAction))
        CaseEq(1)
            ExecWait(Ref(EVS_PlayerFirstStrike))
        CaseEq(5)
            ExecWait(Ref(EVS_Player_Celebrate))
        CaseEq(3)
            ExecWait(Ref(EVS_RunAwayStart))
        CaseEq(7)
            Call(GetStatusFlags, 0, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                ExecWait(Ref(EVS_RunAwayFail))
            EndIf
        CaseEq(4)
            Call(GetStatusFlags, 0, LVar0)
            IfNotFlag(LVar0, 0x35D000)
                ExecWait(Ref(EVS_PlayerDies))
            EndIf
        CaseEq(8)
            ExecWait(Ref(EVS_UseLifeShroom))
        CaseEq(6)
            ExecWait(Ref(EVS_StartDefend))
        CaseEq(0x14)
            ExecWait(Ref(EVS_MerleeAttackBonus))
        CaseEq(0x15)
            ExecWait(Ref(EVS_MerleeDefenseBonus))
        CaseEq(0x16)
            ExecWait(Ref(EVS_MerleeExpBonus))
        CaseEq(0x1E)
            Call(TTYD64_bs_SplitHappyFP)
            ExecWait(Ref(EVS_PlayerHappy))
    EndSwitch
    Return
    End
};

EvtScript TTYD64_RunAwayStart = {
    Call(GetStatusFlags, 0, LVar5)
    IfFlag(LVar5, 0x35D000)
        ExecWait(Ref(TTYD64_RunAwayStart_Animationless))
        Return
    EndIf
    Call(UseIdleAnimation, 0, 0)
    Call(GetActionCommandMode, LVar2)
    IfEq(LVar2, 0)
        ExecWait(Ref(EVS_RunAwayNoCommand))
        Call(UseIdleAnimation, 0, 1)
        Return
    EndIf
    Call(ShowActionHud, 1)
    Call(GetActorVar, ACTOR_SELF, 0, LVar0)
    Call(LoadActionCommand, 3)
    Call(action_command_flee_init, LVar0)
    Call(SetupMashMeter, 1, 0x64, 0, 0, 0, 0)
    Call(func_80260E38)
    Call(SetAnimation, 0, 0, 0x50000)
    Call(PlaySoundAtActor, 0, 0x15D)
    Call(SetActorYaw, 0, 0x1E)
    Wait(1)
    Call(SetActorYaw, 0, 0x3C)
    Wait(1)
    Call(SetActorYaw, 0, 0x5A)
    Wait(1)
    Call(SetActorYaw, 0, 0x78)
    Wait(1)
    Call(SetActorYaw, 0, 0x96)
    Wait(1)
    Call(SetActorYaw, 0, 0xB4)
    Wait(5)
    Call(action_command_flee_start, 0, 0x3C, 3)
    Call(func_80260E5C)
    Wait(5)
    Call(AddActorPos, 0, 2, 0, 0)
    Wait(2)
    Call(AddActorPos, 0, 2, 0, 0)
    Wait(5)
    Call(AddActorPos, 0, 2, 0, 0)
    Wait(2)
    Call(AddActorPos, 0, 2, 0, 0)
    Wait(2)
    Call(AddActorPos, 0, 2, 0, 0)
    Wait(5)
    Call(AddActorPos, 0, 2, 0, 0)
    Wait(2)
    Call(AddActorPos, 0, 2, 0, 0)
    Wait(5)
    Call(AddActorPos, 0, 2, 0, 0)
    Wait(0xF)
    Wait(0x1E)
    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, 0, Float(1.7998046875))
    Call(SetJumpAnimations, 0, 0, 0x10007, 0x10008, 0x10009)
    Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
    Call(PlayerHopToGoal, 8, 0, 0)
    Call(GetSmashActionQuality, LVar0)
    Call(DetermineAutoRunAwaySuccess)
    IfEq(LVar0, 1)
        Call(SetFledBattleFlag)
        Call(PlaySoundAtActor, 0, 0x15E)
        Call(SetGoalPos, 0, -240, 0, 0xA)
        Call(SetActorSpeed, 0, Float(16.0))
        Call(PlayerRunToGoal, 0)
        Wait(5)
    Else
        ChildThread
            Call(ShakeCam, 1, 0, 5, Float(1.0))
        EndChildThread
        Call(SetAnimation, 0, 0, 0x30001)
        Call(PlaySoundAtActor, 0, 0x162)
        Call(SetGoalPos, 0, -100, 0, 0xA)
        Call(SetActorSpeed, 0, Float(10.0))
        Call(PlayerRunToGoal, 0)
        Set(LVar3, 6)
        Call(GetActorPos, 0, LVar0, LVar1, LVar2)
        ChildThread
            Loop(2)
                Call(GetActorPos, 0, LVar0, LVar1, LVar2)
                Call(PlayEffect_impl, 6, 1, LVar0, LVar1, LVar2, Float(1.0), 0, 0, 0, 0, 0, 0, 0, 0)
                Wait(5)
            EndLoop
        EndChildThread
        Loop(0xA)
            Sub(LVar0, LVar3)
            Sub(LVar3, 1)
            IfLt(LVar3, 1)
                Set(LVar3, 1)
            EndIf
            Call(SetActorPos, 0, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
        Wait(0xF)
        Call(PlaySoundAtActor, 0, 0x172)
        Call(SetAnimation, 0, 0, 0x10030)
        Wait(0x14)
        Call(SetAnimation, 0, 0, 0x10031)
        ChildThread
            Wait(7)
            Loop(2)
                Call(GetActorPos, 0, LVar0, LVar1, LVar2)
                Sub(LVar0, 8)
                Add(LVar1, 0xE)
                Add(LVar2, 5)
                Call(PlayEffect_impl, 7, 0, LVar0, LVar1, LVar2, Float(1.0), Float(1.0), 0, 0, 0, 0, 0, 0, 0)
                Wait(5)
            EndLoop
        EndChildThread
        Wait(5)
        Call(UseBattleCamPreset, 2)
        Wait(0xA)
    EndIf
    Call(UseIdleAnimation, 0, 1)
    Return
    End
};

EvtScript TTYD64_Script_ReturnPostage_HurtEnemy = {
    Call(TTYD64_ReadField, TTYD64_F_GBATTLESTATUS_1A8_2U, LVar5)
    Call(TTYD64_GetActorPointer, LVar5, LVar6)
    Call(GetActorPos, LVar5, LVar0, LVar1, LVar2)
    Call(TTYD64_GetLastAttackDamage, LVar3)
    IfLe(LVar3, 0)
        Return
    EndIf
    Call(PlayEffect_impl, 0x1E, 0, LVar0, LVar1, LVar2, 0xA, -50, LVar3, 0, 0, 0, 0, 0, 0)
    Call(TTYD64_GetEffect, LVarF, LVarE)
    Set(LVar4, LVar3)
    Mul(LVar4, -1)
    Call(GetActorHP, LVar5, LVar0)
    Add(LVar0, LVar4)
    IfLt(LVar0, 0)
        Set(LVar0, 0)
    EndIf
    Call(SetEnemyHP, LVar5, LVar0)
    Thread
        Wait(0x14)
        Call(RemoveEffect, LVarE)
    EndThread
    Return
    End
};

EvtScript TTYD64_PartnerHappy = {
    Call(TTYD64_SetPartnerHappyActive, 1)
    Thread
        Loop(0)
            Call(TTYD64_WriteField, TTYD64_F_BATTLESTATUSUPDATEDELAY_0_4U, 0x23)
            Call(TTYD64_GetPartnerHappyActive, LVar0)
            IfEq(LVar0, 0)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
    EndThread
    Call(SetBattleFlagBits2, 0x10, 1)
    Call(UseIdleAnimation, 0x100, 0)
    Call(UseBattleCamPresetWait, 2)
    Set(LVar0, 4)
    Set(LVar1, LVarA)
    Add(LVar1, LVarB)
    Add(LVar1, LVar8)
    IfGt(LVar1, 0)
        Set(LVar0, 5)
    EndIf
    Exec(Ref(TTYD64_SetPartnerAnimation_Battle))
    Call(GetActorPos, 0x100, LVar0, LVar1, LVar2)
    Call(SpawnTurnEndFX, LVar0, LVar1, LVar2)
    Add(LVar0, 0)
    Add(LVar1, 0x23)
    Set(LVar3, LVarA)
    Add(LVar3, LVarB)
    IfNe(LVar3, 0)
        Call(SpawnRecoverHeartFX, LVar0, LVar1, LVar2, LVar3)
    EndIf
    Set(LVar3, LVarA)
    Add(LVar3, LVarB)
    Call(GetActorPos, 0x100, LVar0, LVar1, LVar2)
    Add(LVar1, 0x19)
    Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, LVar3)
    Call(TTYD64_SetPartnerHappyActive, 0)
    Call(TTYD64_Heal_PlayerTeam, 0x100, LVar3)
    Wait(0x1E)
    Set(LVar0, 0)
    Exec(Ref(TTYD64_SetPartnerAnimation_Battle))
    Call(RemoveTurnEndFX)
    Call(UseIdleAnimation, 0x100, 1)
    Call(SetBattleFlagBits2, 0x10, 0)
    Return
    End
};

EvtScript TTYD64_PlayerHappy = {
    Call(UseIdleAnimation, 0, 0)
    Call(UseBattleCamPresetWait, 2)
    Set(LVar0, 0x10003)
    Set(LVar1, LVarA)
    Add(LVar1, LVarB)
    Add(LVar1, LVar8)
    IfGt(LVar1, 0)
        Set(LVar0, 0x10032)
    EndIf
    Set(LVar1, LVarC)
    Add(LVar1, LVarD)
    Add(LVar1, LVar9)
    IfGt(LVar1, 0)
        Set(LVar0, 0x10032)
    EndIf
    Call(SetAnimation, 0, 0, LVar0)
    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
    Call(SpawnTurnEndFX, LVar0, LVar1, LVar2)
    Add(LVar0, 0)
    Add(LVar1, 0x23)
    Set(LVar3, LVarA)
    Add(LVar3, LVarB)
    IfNe(LVar3, 0)
        Call(SpawnRecoverHeartFX, LVar0, LVar1, LVar2, LVar3)
    EndIf
    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
    Add(LVar0, 0x14)
    Add(LVar1, 0x19)
    Set(LVar3, LVarC)
    Add(LVar3, LVarD)
    IfNe(LVar3, 0)
        Call(SpawnRecoverFlowerFX, LVar0, LVar1, LVar2, LVar3)
    EndIf
    Set(LVar3, LVarA)
    Add(LVar3, LVarB)
    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
    Add(LVar1, 0x19)
    Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, LVar3)
    Wait(0xA)
    Set(LVar0, LVarA)
    Add(LVar0, LVarB)
    Call(TTYD64_Heal_PlayerTeam, 0, LVar0)
    Set(LVar0, LVarC)
    Add(LVar0, LVarD)
    Call(TTYD64_RecoverFP, LVar0)
    Wait(0x1E)
    Call(SetAnimation, ACTOR_SELF, 0, 0x10002)
    Call(RemoveTurnEndFX)
    Call(UseIdleAnimation, 0, 1)
    Return
    End
};

EvtScript TTYD64_Script_DispatchActorHandleEvent = {
    Wait(3)
    SetGroup(0)
    SuspendGroup(2)
    ExecGetTID(LVar0, LVar1)
    Call(TTYD64_ReadField, TTYD64_F_GBATTLESTATUS_1A8_2U, LVar5)
    Call(GetLastEvent, LVar5, LVar4)
    Switch(LVar4)
        CaseEq(0xA)
            Exec(Ref(TTYD64_Script_ReturnPostage_HurtEnemy))
    EndSwitch
    Loop(0)
        IsThreadRunning(LVar1, LVar2)
        Wait(1)
        IfEq(LVar2, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(GetActorHP, LVar5, LVar4)
    IfEq(LVar4, 0)
        Call(DispatchEvent, LVar5, 0x20)
    EndIf
    ResumeGroup(2)
    Return
    End
};

EvtScript TTYD64_EVS_PlayerHappy_Patch = {
    ExecWait(Ref(TTYD64_PlayerHappy))
    Return
    End
};

EvtScript TTYD64_EVS_StartDefend_Patch = {
    ExecWait(Ref(TTYD64_Script_Dispatch_BattleState19))
    Return
    End
};

EvtScript TTYD64_EVS_Mario_HandlePhase_Patch = {
    ExecWait(Ref(TTYD64_PlayerScriptDispatcher))
    Return
    End
};

EvtScript TTYD64_EVS_RunAwayStart_Patch = {
    ExecWait(Ref(TTYD64_RunAwayStart))
    Return
    End
};
// clang-format on
