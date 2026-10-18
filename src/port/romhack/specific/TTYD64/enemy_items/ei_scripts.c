#include "common.h"
#include "effects.h"
#include "battle/battle.h"
#include "script_api/battle.h"
#include "port/Engine.h"
#include "enemy_items_internal.h"

extern EvtScript EVS_Enemy_DeathWithoutRemove;
extern EvtScript EVS_ForceNextTarget;

API_CALLABLE(PlayParalyzeHitFX);

// clang-format off
EvtScript TTYD64_DoReturnPostageHit = {
    Switch(LVar3)
        CaseEq(0)
            Call(SetAnimation, LVar3, 0, 0x10017)
        CaseEq(0x100)
            Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_12_1U, LVar0)
            Switch(LVar0)
                CaseEq(1)
                    Call(SetAnimation, LVar3, -1, 0x9000A)
                CaseEq(2)
                    Call(SetAnimation, LVar3, -1, 0xA0011)
                CaseEq(3)
                    Call(SetAnimation, LVar3, -1, 0xB0012)
                CaseEq(4)
                    Call(SetAnimation, LVar3, -1, 0xC000E)
                CaseEq(9)
                    Call(SetAnimation, LVar3, -1, 0xD0015)
                CaseEq(6)
                    Call(SetAnimation, LVar3, -1, 0xE000C)
                CaseEq(7)
                    Call(SetAnimation, LVar3, -1, 0xF0010)
                CaseEq(8)
                    Call(SetAnimation, LVar3, -1, 0x10000A)
            EndSwitch
    EndSwitch
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Add(LVar1, 0xD)
    Call(PlayEffect_impl, 0x43, 0, LVar0, LVar1, LVar2, Float(0.7001953125), 0, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, LVar3, 0xE9)
    Call(GetActorPos, LVar3, LVar0, LVar1, LVar2)
    Loop(2)
        Sub(LVar1, 2)
        Call(SetActorPos, LVar3, LVar0, LVar1, LVar2)
        Wait(5)
        Add(LVar1, 2)
        Call(SetActorPos, LVar3, LVar0, LVar1, LVar2)
        Wait(5)
    EndLoop
    Return
    End
};

EvtScript TTYD64_Script_ReturnPostage_HurtMario = {
    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
    Call(TTYD64_GetLastAttackDamage, LVar3)
    IfLe(LVar3, 0)
        Return
    EndIf
    Call(PlayEffect_impl, 0x1E, 0, LVar0, LVar1, LVar2, 0xA, 0x32, LVar3, 0, 0, 0, 0, 0, 0)
    Call(TTYD64_GetEffect, LVarF, LVarE)
    Set(LVar4, LVar3)
    Mul(LVar4, -1)
    Call(TTYD64_Heal_PlayerTeam, 0, LVar4)
    Call(GetAnimation, 0, 0, LVar4)
    SetGroup(0)
    SuspendGroup(2)
    Set(LVar3, 0)
    ExecWait(Ref(TTYD64_DoReturnPostageHit))
    ResumeGroup(2)
    Call(SetAnimation, 0, 0, LVar4)
    Thread
        Wait(0x14)
        Call(RemoveEffect, LVarE)
    EndThread
    Return
    End
};

EvtScript TTYD64_Script_ReturnPostage_HurtPartner = {
    Call(GetActorPos, 0x100, LVar0, LVar1, LVar2)
    Call(TTYD64_GetLastAttackDamage, LVar3)
    IfLe(LVar3, 0)
        Return
    EndIf
    Call(PlayEffect_impl, 0x1E, 0, LVar0, LVar1, LVar2, 0xA, 0x32, LVar3, 0, 0, 0, 0, 0, 0)
    Call(TTYD64_GetEffect, LVarF, LVarE)
    Set(LVar4, LVar3)
    Mul(LVar4, -1)
    Call(TTYD64_Heal_PlayerTeam, 0x100, LVar4)
    Call(GetAnimation, 0x100, -1, LVar4)
    SetGroup(0)
    SuspendGroup(2)
    Set(LVar3, 0x100)
    ExecWait(Ref(TTYD64_DoReturnPostageHit))
    ResumeGroup(2)
    Call(SetAnimation, 0x100, -1, LVar4)
    Thread
        Wait(0x14)
        Call(RemoveEffect, LVarE)
    EndThread
    Call(TTYD64_EI_UpdateKoStatus)
    Return
    End
};

EvtScript TTYD64_Script_Dispatch_ReturnPostage_Mario = {
    ExecWait(Ref(TTYD64_Script_ReturnPostage_HurtMario))
    Return
    End
};

EvtScript TTYD64_Script_Dispatch_ReturnPostage_Partner = {
    ExecWait(Ref(TTYD64_Script_ReturnPostage_HurtPartner))
    Return
    End
};

EvtScript TTYD64_Script_ApplyDebuff_Attack = {
    Call(GetBattleFlags, LVar0)
    IfFlag(LVar0, -2147483648)
        Return
    EndIf
    Call(GetOwnerTarget, LVar4, 0)
    Set(LVarC, 3)
    Call(TTYD64_AddAttackBoost, LVar4, -1, LVarC)
    Call(TTYD64_MakeActorTiny, LVar4)
    Call(PlaySoundAtActor, LVar4, 0x2106)
    Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
    Sub(LVar0, 0xF)
    Add(LVar1, 0x23)
    Set(LVar2, 6)
    Call(PlayEffect_impl, 0x56, 3, LVar0, LVar1, LVar2, Float(1.5), 0x3C, 0, 0, 0, 0, 0, 0, 0)
    Call(TTYD64_GetEffectData, LVarF, LVar0)
    Call(TTYD64_WritePtrField, LVar0, TTYD64_F_STATCHANGEFXDATA_20_4U, -1)
    Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
    Add(LVar1, 0xF)
    Add(LVar2, 2)
    Call(PlayParalyzeHitFX)
    Return
    End
};

EvtScript TTYD64_Script_ApplyDebuff_Defense = {
    Call(GetBattleFlags, LVar0)
    IfFlag(LVar0, -2147483648)
        Return
    EndIf
    Call(GetOwnerTarget, LVar4, 0)
    Set(LVarC, 3)
    Call(TTYD64_AddDefenseBoost, LVar4, -3, LVarC)
    Call(PlaySoundAtActor, LVar4, 0x2106)
    Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
    Add(LVar0, 0xF)
    Add(LVar1, 0x23)
    Set(LVar2, 6)
    Call(PlayEffect_impl, 0x56, 6, LVar0, LVar1, LVar2, Float(1.5), 0x3C, 0, 0, 0, 0, 0, 0, 0)
    Call(TTYD64_GetEffectData, LVarF, LVar0)
    Call(TTYD64_WritePtrField, LVar0, TTYD64_F_STATCHANGEFXDATA_20_4U, -3)
    Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
    Add(LVar1, 0xF)
    Add(LVar2, 2)
    Call(TTYD64_GetEffectData, LVarF, LVar6)
    Call(TTYD64_WritePtrField, LVar6, TTYD64_F_STATCHANGEFXDATA_1C_4U, 3)
    Call(PlayEffect_impl, 0x31, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Return
    End
};

EvtScript TTYD64_EnemyUseCharge = {
    Call(GetActorAttackBoost, ACTOR_SELF, LVar0)
    IfEq(LVar0, 0)
        Set(LVar1, 0x46)
    Else
        Set(LVar1, 0x14)
    EndIf
    Call(RandInt, 0x64, LVar0)
    IfLt(LVar0, LVar1)
        ExecWait(Ref(TTYD64_Script_ChargeCommand))
    Else
        Call(TTYD64_GetWrappedTakeTurn, LVar0)
        ExecWait(LVar0)
        Return
    EndIf
    Return
    End
};

EvtScript TTYD64_ForceNextTarget = {
    Call(GetOwnerID, LVarA)
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(0)
    Call(GetOwnerTarget, LVar0, LVar1)
    IfNe(LVar0, LVarA)
        Call(GetOriginalActorType, LVar0, LVar2)
        IfNe(LVar2, 0x47)
            Return
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(0)
    EndIf
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(1)
    Call(GetOwnerTarget, LVar0, LVar1)
    IfNe(LVar0, LVarA)
        Call(GetActorVar, LVar0, 8, LVar3)
        IfNe(LVar3, 1)
            Return
        EndIf
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(1)
    EndIf
    Call(CreateHomeTargetList, 0x8002)
    Call(InitTargetIterator)
    Label(2)
    Call(GetOwnerTarget, LVar0, LVar1)
    Call(TTYD64_GetActorPointer, LVar0, LVar1)
    Call(TTYD64_GetHeldItem, LVar1, LVar1)
    IfNe(LVar1, 0x95)
        Call(SetActorFlagBits, LVar0, 0x600000, 1)
    EndIf
    Call(ChooseNextTarget, 0, LVar0)
    IfNe(LVar0, -1)
        Goto(2)
    EndIf
    Return
    End
};

EvtScript TTYD64_DoDeath = {
    ExecWait(Ref(EVS_Enemy_DeathWithoutRemove))
    Call(UseBattleCamPreset, 2)
    ExecWait(Ref(EVS_ForceNextTarget))
    Call(TTYD64_GetActorPointer, ACTOR_SELF, LVar0)
    Call(TTYD64_GetHeldItem, LVar0, LVar1)
    Call(TTYD64_HasHeldItem, LVar0, LVar2)
    IfNe(LVar2, 0)
        Call(TTYD64_GetHeldItemEntity, LVar0, LVar2)
        Call(RemoveItemEntity, LVar2)
        Call(TTYD64_ClearHeldItem, LVar0)
        IfEq(LVar1, 0x95)
            ExecWait(Ref(TTYD64_UseLifeShroom_Actor))
            Return
        EndIf
    EndIf
    Call(TTYD64_Function_DeleteData_EnemyItemDropTable_SelfActor)
    Call(RemoveActor, ACTOR_SELF)
    Return
    End
};

EvtScript TTYD64_EnemyUseItem = {
    Call(TTYD64_GetActorPointer, ACTOR_SELF, LVar0)
    Call(TTYD64_GetHeldItem, LVar0, LVar1)
    IfEq(LVar1, 0x95)
        Call(TTYD64_GetWrappedTakeTurn, LVar0)
        ExecWait(LVar0)
        Return
    EndIf
    Call(GetActorHP, ACTOR_SELF, LVar2)
    IfEq(LVar2, 0)
        Call(TTYD64_GetWrappedTakeTurn, LVar0)
        ExecWait(LVar0)
        Return
    EndIf
    Call(TTYD64_GetActorExtraData, ACTOR_SELF, 0xC, LVar2)
    IfNe(LVar2, 0)
        Call(TTYD64_GetWrappedTakeTurn, LVar0)
        ExecWait(LVar0)
        Return
    EndIf
    Call(CreateHomeTargetList, 0)
    Call(TTYD64_GetItemFlags, LVar1, LVar2, LVar3)
    IfFlag(LVar3, 8)
        Call(GetOwnerID, LVar4)
        Set(LVarA, LVar4)
        Call(GetActorHP, LVar4, LVarB)
        Call(GetEnemyMaxHP, LVar4, LVarC)
        Set(LVar5, LVarC)
        Sub(LVar5, LVarB)
        IfLt(LVar5, 1)
            Set(LVarB, 0xFFFFFF)
            Set(LVarC, 0xFFFFFF)
        EndIf
        Label(0)
        Call(GetActorHP, LVar4, LVar5)
        Call(GetEnemyMaxHP, LVar4, LVar6)
        IfLt(LVar5, LVarB)
            Set(LVar7, LVar6)
            Sub(LVar7, LVar5)
            IfGe(LVar7, 1)
                Set(LVarA, LVar4)
                Set(LVarB, LVar5)
                Set(LVarC, LVar6)
            EndIf
        EndIf
        Call(ChooseNextTarget, 0, LVar4)
        IfNe(LVar4, -1)
            Call(GetOwnerTarget, LVar4, 0)
            Goto(0)
        EndIf
        Set(LVar7, LVarC)
        Sub(LVar7, LVarB)
        IfEq(LVarC, 0xFFFFFF)
            Set(LVar7, 0)
        EndIf
        Switch(LVar1)
            CaseOrEq(0x88)
            CaseOrEq(0xCC)
            CaseOrEq(0x97)
            CaseOrEq(0xD2)
            CaseOrEq(0x8B)
            CaseOrEq(0x18E)
            CaseOrEq(0x195)
            CaseOrEq(0x198)
            CaseOrEq(0x19F)
            CaseOrEq(0x1A1)
            CaseOrEq(0x1A3)
                Set(LVar7, 1)
            EndCaseGroup
        EndSwitch
        IfLt(LVar7, 1)
            Call(TTYD64_GetWrappedTakeTurn, LVar0)
            ExecWait(LVar0)
            Return
        EndIf
        Call(SetTargetActor, ACTOR_SELF, LVarA)
        Wait(1)
        Goto(1)
    Else
        IfFlag(LVar3, 1)
            Call(RandInt, 0x64, LVar2)
            IfLe(LVar2, 0x32)
                Call(SetTargetActor, ACTOR_SELF, 0)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar2)
                IfGt(LVar2, 0)
                    Call(SetTargetActor, ACTOR_SELF, 0x100)
                Else
                    Call(SetTargetActor, ACTOR_SELF, 0)
                EndIf
            EndIf
        Else
            Call(SetTargetActor, ACTOR_SELF, 0)
        EndIf
    EndIf
    Call(RandInt, 0x64, LVar2)
    IfGe(LVar2, 0x3C)
        Call(TTYD64_GetWrappedTakeTurn, LVar0)
        ExecWait(LVar0)
        Return
    EndIf
    Label(1)
    Call(TTYD64_GetHeldItemEntity, LVar0, LVar2)
    Call(RemoveItemEntity, LVar2)
    Call(TTYD64_SetActorItemData, ACTOR_SELF, 0)
    Call(TTYD64_WriteField, TTYD64_F_GBATTLESTATUS_17A_2U, LVar1)
    Call(TTYD64_WriteField, TTYD64_F_GBATTLESTATUS_17C_2U, 0)
    Call(TTYD64_LoadItemScriptEnemy)
    ExecWait(LVar0)
    Return
    End
};

EvtScript TTYD64_Script_BattleCondition_ShowWarning = {
    Loop(0)
        Call(GetBattlePhase, LVar0)
        IfEq(LVar0, 0xA)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(RandInt, 0xF, LVar0)
    Call(TTYD64_SetGlitzChallenge, LVar0)
    Switch(LVar0)
        CaseEq(0)
            Set(LVar4, 0x10B)
            Set(LVar5, -1)
        CaseEq(1)
            Set(LVar4, 0x10C)
            Set(LVar5, 1)
        CaseEq(2)
            Set(LVar4, 0x10D)
            Set(LVar5, 1)
        CaseEq(3)
            Set(LVar4, 0x10E)
            Set(LVar5, 1)
        CaseEq(4)
            Set(LVar4, 0x10F)
            Set(LVar5, 1)
        CaseEq(5)
            Set(LVar4, 0x110)
            Set(LVar5, -1)
        CaseEq(6)
            Set(LVar4, 0x111)
            Set(LVar5, -1)
        CaseEq(7)
            Set(LVar4, 0x112)
            Set(LVar5, 1)
        CaseEq(8)
            Set(LVar4, 0x113)
            Set(LVar5, 1)
        CaseEq(9)
            Set(LVar4, 0x114)
            Set(LVar5, -1)
        CaseEq(0xA)
            Set(LVar4, 0x115)
            Set(LVar5, -1)
        CaseEq(0xB)
            Set(LVar4, 0x116)
            Set(LVar5, 1)
        CaseEq(0xC)
            Set(LVar4, 0x117)
            Set(LVar5, 1)
        CaseEq(0xD)
            Set(LVar4, 0x118)
            Set(LVar5, 1)
        CaseEq(0xE)
            Set(LVar4, 0x119)
            Set(LVar5, 1)
        CaseEq(0xF)
            Set(LVar4, 0x11A)
            Set(LVar5, 1)
    EndSwitch
    Call(WaitForState, 0xD)
    Call(ShowMessageBox, LVar4, 0x3C)
    Call(WaitForMessageBoxDone)
    Call(WaitForState, 0)
    Call(TTYD64_SetGlitzStatus, LVar5)
    Return
    End
};

EvtScript TTYD64_Script_Init_BattleCondition = {
    Exec(Ref(TTYD64_Script_BattleCondition_ShowWarning))
    Return
    End
};

EvtScript TTYD64_EVS_Enemy_Death_Patch = {
    ExecWait(Ref(TTYD64_DoDeath))
    Return
    End
};

EvtScript TTYD64_EVS_ForceNextTarget_Patch = {
    ExecWait(Ref(TTYD64_ForceNextTarget))
    Return
    End
};
// clang-format on
