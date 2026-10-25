#include "port/romhack/specific/TTYD64/battle/battle_items_internal.h"

API_CALLABLE(PlayFreezeHitParticleFX);
API_CALLABLE(PlayParalyzeHitFX);
API_CALLABLE(PlayPoisonHitFX);
EvtScript TTYD64_NewItemsScripts_GetNewScript;
EvtScript TTYD64_bi_UseItem_StatusItem_SingleTarget;
EvtScript TTYD64_bi_UseItem_StatusItem_MultiTarget;
EvtScript TTYD64_bi_UseItem_OffensiveItem_SingleTarget;
EvtScript TTYD64_bi_UseItem_OffensiveItem_MultiTarget;
EvtScript TTYD64_bi_UseItem_StrangeCake;
EvtScript TTYD64_bi_Script_RandomEffect_Static;
EvtScript TTYD64_bi_Script_RandomEffect_Invicible;
EvtScript TTYD64_bi_Script_RandomEffect_Sleep;

// clang-format off
EvtScript TTYD64_NewItemsScripts_GetNewScript = {
    Switch(LVar9)
        CaseOrEq(398)
        CaseOrEq(405)
        CaseOrEq(417)
        CaseOrEq(419)
        CaseOrEq(408)
        CaseOrEq(415)
        CaseOrEq(416)
        CaseOrEq(425)
        CaseOrEq(427)
        CaseOrEq(429)
        CaseOrEq(430)
        CaseOrEq(431)
        CaseOrEq(438)
        CaseOrEq(442)
        CaseOrEq(445)
        CaseOrEq(447)
        CaseOrEq(421)
        CaseOrEq(452)
            ExecWait(TTYD64_bi_UseItem_StatusItem_SingleTarget)
            Set(LVar7, 1)
        EndCaseGroup
        CaseOrEq(412)
        CaseOrEq(413)
        CaseOrEq(418)
            ExecWait(TTYD64_bi_UseItem_StatusItem_MultiTarget)
            Set(LVar7, 1)
        EndCaseGroup
        CaseOrEq(409)
        CaseOrEq(424)
        CaseOrEq(426)
        CaseOrEq(451)
            ExecWait(TTYD64_bi_UseItem_OffensiveItem_SingleTarget)
            Set(LVar7, 1)
        EndCaseGroup
        CaseOrEq(400)
        CaseOrEq(410)
            ExecWait(TTYD64_bi_UseItem_OffensiveItem_MultiTarget)
            Set(LVar7, 1)
        EndCaseGroup
        CaseOrEq(436)
        CaseOrEq(441)
            ExecWait(TTYD64_bi_UseItem_StrangeCake)
            Set(LVar7, 1)
        EndCaseGroup
        CaseDefault
            Set(LVar7, 0)
    EndSwitch
    Return
    End
};

EvtScript TTYD64_bi_UseItem_StatusItem_SingleTarget = {
    Call(TTYD64_GetItemFlags, LVar9, LVar1, LVar2)
    IfFlag(LVar1, 128)
        IfFlag(LVar1, 256)
            ExecWait(TTYD64_BattleScript_DrinkItem)
        Else
            ExecWait(TTYD64_BattleScript_EatItem)
        EndIf
    EndIf
    Call(GetOwnerID, LVar0)
    IfLt(LVar0, 512)
        Call(InitTargetIterator)
    EndIf
    Call(GetOwnerTarget, LVar4, 0)
    Set(LVarF, 0)
    Call(GetStatusFlags, LVar4, LVar0)
    IfFlag(LVar0, 3526656)
        Set(LVarF, 1)
    EndIf
    Switch(LVar9)
        CaseEq(398)
            IfEq(LVarF, 0)
                Switch(LVar4)
                    CaseEq(0)
                        Call(SetAnimation, 0, 0, 65586)
                    CaseEq(256)
                        Set(LVar0, 5)
                        Exec(TTYD64_SetPartnerAnimation_Battle)
                    CaseDefault
                EndSwitch
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar0, 15)
            Add(LVar1, 35)
            Set(LVarF, 6)
            Call(PlayEffect_impl, 86, 6, LVar0, LVar1, LVar2, Float(1.5), 60, 0, 0, 0, 0, 0, 0, 0)
            Call(GetItemPower, LVar9, LVar5, 0)
            Call(TTYD64_GetEffectData, LVarF, LVar0)
            Call(TTYD64_WritePtrField, LVar0, TTYD64_F_STATCHANGEFXDATA_20_4U, LVar5)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar1, 15)
            Add(LVar2, 2)
            Call(PlayEffect_impl, 49, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Call(PlaySoundAtActor, LVar4, 8335)
            Wait(20)
            Call(TTYD64_AddDefenseBoost, LVar4, LVar5, 3)
            Call(ShowMessageBox, 257, 60)
            Call(WaitForMessageBoxDone)
        CaseEq(417)
            IfEq(LVarF, 0)
                Switch(LVar4)
                    CaseEq(0)
                        Call(SetAnimation, 0, 0, 65586)
                    CaseEq(256)
                        Set(LVar0, 5)
                        Exec(TTYD64_SetPartnerAnimation_Battle)
                    CaseDefault
                EndSwitch
            EndIf
            Call(UseBattleCamPreset, 2)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar0, 15)
            Add(LVar1, 35)
            Set(LVarF, 6)
            Call(PlayEffect_impl, 86, 0, LVar0, LVar1, LVar2, Float(1.5), 60, 0, 0, 0, 0, 0, 0, 0)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar1, 15)
            Add(LVar2, 2)
            Call(PlayParalyzeHitFX)
            Call(PlaySoundAtActor, LVar4, 8334)
            Call(GetItemPower, LVar9, LVar5, 0)
            Call(TTYD64_GetEffectData, LVarF, LVar0)
            Call(TTYD64_WritePtrField, LVar0, TTYD64_F_STATCHANGEFXDATA_20_4U, LVar5)
            Call(TTYD64_AddAttackBoost, LVar4, LVar5, 3)
            Call(TTYD64_MakeActorGiant, LVar4)
            Wait(20)
            Call(ShowMessageBox, 258, 60)
            Call(WaitForMessageBoxDone)
        CaseOrEq(419)
        CaseOrEq(405)
        CaseOrEq(425)
        CaseOrEq(438)
            IfEq(LVarF, 0)
                Switch(LVar4)
                    CaseEq(0)
                        Call(SetAnimation, 0, 0, 65586)
                    CaseEq(256)
                        Set(LVar0, 5)
                        Exec(TTYD64_SetPartnerAnimation_Battle)
                    CaseDefault
                EndSwitch
            EndIf
            IfEq(LVar9, 425)
                Call(GetOwnerID, LVar0)
                IfEq(LVar4, LVar0)
                    Wait(20)
                    Call(UseBattleCamPreset, 2)
                    ExecWait(TTYD64_BattleScript_GoBackToHome_HealingItem)
                    IfEq(LVar4, 0)
                        Call(DispatchEventPlayer, 25)
                    Else
                        Call(DispatchEvent, LVar4, 25)
                    EndIf
                    Wait(20)
                    Return
                EndIf
            EndIf
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Add(LVar2, 2)
            Call(PlayEffect_impl, 34, 0, LVar0, LVar1, LVar2, -54, 37, 12, 20, 0, 0, 0, 0, 0)
            Call(PlaySoundAtActor, LVar4, 8277)
            Wait(20)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Call(ShowRecoveryShimmer, LVar0, LVar1, LVar2, LVarB)
            Call(UseBattleCamPreset, 2)
            Call(GetItemPower, LVar9, LVar5, LVar6)
            Switch(LVar9)
                CaseOrEq(419)
                CaseOrEq(425)
                    Call(TTYD64_SetActorExtraData, LVar4, 9, LVar6)
                    Call(TTYD64_SetActorExtraData, LVar4, 8, LVar5)
                    Call(WaitForMessageBoxDone)
                    Call(ShowMessageBox, 259, 60)
                    Call(WaitForMessageBoxDone)
                EndCaseGroup
                CaseOrEq(405)
                    Call(TTYD64_SetActorExtraData, LVar4, 11, LVar6)
                    Call(TTYD64_SetActorExtraData, LVar4, 10, LVar5)
                    Call(GetOwnerID, LVar0)
                    IfLt(LVar0, 512)
                        Call(WaitForMessageBoxDone)
                        Call(ShowMessageBox, 260, 60)
                        Call(WaitForMessageBoxDone)
                    EndIf
                EndCaseGroup
                CaseOrEq(438)
                    Call(TTYD64_SetActorExtraData, LVar4, 9, 3)
                    Call(TTYD64_SetActorExtraData, LVar4, 8, 2)
                    IfGe(LVar4, 512)
                        Call(TTYD64_HealActor, LVar4, LVar5)
                    Else
                        Call(TTYD64_Heal_PlayerTeam, LVar4, LVar5)
                    EndIf
                    Call(SpawnRecoverHeartFX, LVar0, LVar1, LVar2, LVar5)
                    Call(PlaySoundAtActor, LVar4, 8301)
                    Call(WaitForMessageBoxDone)
                    Call(ShowMessageBox, 259, 60)
                    Call(WaitForMessageBoxDone)
                EndCaseGroup
            EndSwitch
        EndCaseGroup
        CaseOrEq(408)
        CaseOrEq(447)
            IfEq(LVarF, 0)
                Switch(LVar4)
                    CaseEq(0)
                        Call(SetAnimation, 0, 0, 65586)
                    CaseEq(256)
                        Set(LVar0, 5)
                        Exec(TTYD64_SetPartnerAnimation_Battle)
                    CaseDefault
                EndSwitch
            EndIf
            Switch(LVar9)
                CaseEq(447)
                    Call(GetItemPower, LVar9, LVar5, LVar6)
                    IfGe(LVar4, 512)
                        Call(TTYD64_HealActor, LVar4, LVar5)
                    Else
                        Call(TTYD64_Heal_PlayerTeam, LVar4, LVar5)
                    EndIf
                    Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
                    Call(SpawnRecoverHeartFX, LVar0, LVar1, LVar2, LVar5)
                    Call(ShowRecoveryShimmer, LVar0, LVar1, LVar2, LVar5)
                    Call(PlaySoundAtActor, LVar4, 8301)
                    Add(LVar1, 25)
                    Call(SpawnRecoverFlowerFX, LVar0, LVar1, LVar2, LVar6)
                    IfLt(LVar4, 512)
                        Call(TTYD64_RecoverFP, LVar6)
                    EndIf
            EndSwitch
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar1, 15)
            Add(LVar2, 2)
            Call(PlayParalyzeHitFX)
            Call(PlaySound, 8334)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Add(LVar1, 5)
            Add(LVar2, 1)
            Call(PlayEffect_impl, 86, 0, LVar0, LVar1, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
            Call(GetItemPower, LVar9, LVar5, 0)
            Switch(LVar9)
                CaseEq(447)
                    Set(LVar5, 1)
            EndSwitch
            Call(TTYD64_GetActorExtraData, LVar4, 15, LVar6)
            Add(LVar6, LVar5)
            IfGt(LVar6, 255)
                Set(LVar6, 255)
            EndIf
            Call(TTYD64_SetActorExtraData, LVar4, 15, LVar6)
            Wait(22)
            Call(UseBattleCamPreset, 2)
            Call(ShowMessageBox, 71, 60)
            Call(WaitForMessageBoxDone)
        EndCaseGroup
        CaseEq(415)
            IfGe(LVar4, 512)
                Return
            EndIf
            IfEq(LVarF, 0)
                Switch(LVar4)
                    CaseEq(0)
                        Call(SetAnimation, 0, 0, 65538)
                    CaseEq(256)
                        Set(LVar0, 0)
                        Exec(TTYD64_SetPartnerAnimation_Battle)
                EndSwitch
            EndIf
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Sub(LVar0, 37)
            Add(LVar1, 60)
            Add(LVar2, 2)
            Call(PlayEffect_impl, 64, 0, LVar0, LVar1, LVar2, LVar5, 0, 0, 0, 0, 0, 0, 0, 0)
            Call(TTYD64_ReadPtrField, LVarF, TTYD64_F_EFFECTINSTANCE_C_4U, LVar3)
            Set(LVarB, LVarF)
            Call(GetOwnerTarget, LVar6, 0)
            IfEq(LVar6, 0)
                Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_2_1U, LVar5)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar5)
            EndIf
            Call(TTYD64_WritePtrField, LVar3, TTYD64_F_RECOVERFXDATA_40_4U, LVar5)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar0, 37)
            Add(LVar1, 60)
            Add(LVar2, -2)
            Call(PlayEffect_impl, 64, 1, LVar0, LVar1, LVar2, LVar5, 0, 0, 0, 0, 0, 0, 0, 0)
            Call(TTYD64_ReadPtrField, LVarF, TTYD64_F_EFFECTINSTANCE_C_4U, LVar4)
            Set(LVarC, LVarF)
            Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_5_1U, LVar5)
            Call(TTYD64_WritePtrField, LVar4, TTYD64_F_RECOVERFXDATA_40_4U, LVar5)
            Set(LVarE, 0)
            ChildThread
                Loop(0)
                    Call(TTYD64_WritePtrField, LVar3, TTYD64_F_RECOVERFXDATA_2C_4U, 28)
                    Call(TTYD64_WritePtrField, LVar3, TTYD64_F_RECOVERFXDATA_5C_4U, 0)
                    Call(TTYD64_WritePtrField, LVar4, TTYD64_F_RECOVERFXDATA_2C_4U, 28)
                    Call(TTYD64_WritePtrField, LVar4, TTYD64_F_RECOVERFXDATA_5C_4U, 0)
                    IfEq(LVarE, 1)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
            EndChildThread
            Call(TTYD64_WritePtrField, LVar3, TTYD64_F_RECOVERFXDATA_70_4U, 0)
            Call(TTYD64_WritePtrField, LVar4, TTYD64_F_RECOVERFXDATA_70_4U, 0)
            Loop(0)
                Call(TTYD64_ReadPtrField, LVar3, TTYD64_F_RECOVERFXDATA_70_4U, LVar5)
                Add(LVar5, 16)
                IfGt(LVar5, 255)
                    Call(TTYD64_WritePtrField, LVar3, TTYD64_F_RECOVERFXDATA_70_4U, 255)
                    Call(TTYD64_WritePtrField, LVar4, TTYD64_F_RECOVERFXDATA_70_4U, 255)
                    BreakLoop
                EndIf
                Call(TTYD64_WritePtrField, LVar3, TTYD64_F_RECOVERFXDATA_70_4U, LVar5)
                Call(TTYD64_WritePtrField, LVar4, TTYD64_F_RECOVERFXDATA_70_4U, LVar5)
                Wait(1)
            EndLoop
            Wait(15)
            Set(LVar7, 15)
            Set(LVar8, LVar7)
            Loop(LVar7)
                Call(TTYD64_ReadPtrField, LVar3, TTYD64_F_RECOVERFXDATA_4_4F, LVar5)
                AddF(LVar5, 5)
                Call(TTYD64_WritePtrField, LVar3, TTYD64_F_RECOVERFXDATA_4_4F, LVar5)
                Call(TTYD64_ReadPtrField, LVar4, TTYD64_F_RECOVERFXDATA_4_4F, LVar5)
                SubF(LVar5, 5)
                Call(TTYD64_WritePtrField, LVar4, TTYD64_F_RECOVERFXDATA_4_4F, LVar5)
                IfEq(LVar7, 7)
                    Call(TTYD64_ReadPtrField, LVar3, TTYD64_F_RECOVERFXDATA_40_4U, LVar8)
                    Call(TTYD64_ReadPtrField, LVar4, TTYD64_F_RECOVERFXDATA_40_4U, LVar9)
                    Call(TTYD64_WritePtrField, LVar3, TTYD64_F_RECOVERFXDATA_40_4U, LVar9)
                    Call(TTYD64_WritePtrField, LVar4, TTYD64_F_RECOVERFXDATA_40_4U, LVar8)
                    Call(PlaySound, 15)
                EndIf
                Wait(1)
            EndLoop
            Wait(10)
            Loop(0)
                Call(TTYD64_ReadPtrField, LVar3, TTYD64_F_RECOVERFXDATA_70_4U, LVar5)
                Sub(LVar5, 16)
                IfLe(LVar5, 0)
                    Set(LVarE, 1)
                    Call(RemoveEffect, LVarB)
                    Call(RemoveEffect, LVarC)
                    BreakLoop
                EndIf
                Call(TTYD64_WritePtrField, LVar3, TTYD64_F_RECOVERFXDATA_70_4U, LVar5)
                Call(TTYD64_WritePtrField, LVar4, TTYD64_F_RECOVERFXDATA_70_4U, LVar5)
                Wait(1)
            EndLoop
            Call(GetOwnerTarget, LVar0, 0)
            IfEq(LVar0, 0)
                Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_2_1U, LVar1)
            Else
                Call(TTYD64_GetPartnerHP_API, LVar1)
            EndIf
            Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_5_1U, LVar2)
            IfEq(LVar0, 0)
                Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_3_1U, LVar3)
                IfGt(LVar2, LVar3)
                    Set(LVar2, LVar3)
                EndIf
                Call(TTYD64_WriteField, TTYD64_F_GPLAYERDATA_2_1U, LVar2)
                Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_6_1U, LVar3)
                IfGt(LVar1, LVar3)
                    Set(LVar1, LVar3)
                EndIf
                Call(TTYD64_WriteField, TTYD64_F_GPLAYERDATA_5_1U, LVar1)
            Else
                Call(TTYD64_GetPartnerData_API, LVar4)
                Call(TTYD64_ReadPtrField, LVar4, TTYD64_F_PARTNERDATA_6_1U, LVar3)
                IfGt(LVar2, LVar3)
                    Set(LVar2, LVar3)
                EndIf
                Call(TTYD64_WritePtrField, LVar4, TTYD64_F_PARTNERDATA_5_1U, LVar2)
                Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_6_1U, LVar3)
                IfGt(LVar1, LVar3)
                    Set(LVar1, LVar3)
                EndIf
                Call(TTYD64_WriteField, TTYD64_F_GPLAYERDATA_5_1U, LVar1)
            EndIf
            Wait(15)
            Call(UseBattleCamPreset, 2)
        CaseEq(416)
            Call(UseBattleCamPreset, 2)
            Switch(LVar4)
                CaseEq(0)
                    Call(GetPlayerHP, LVar2)
                    Call(TTYD64_ReadField, TTYD64_F_GPLAYERDATA_3_1U, LVar3)
                CaseEq(256)
                    Call(TTYD64_GetPartnerHP_API, LVar2)
                    Call(TTYD64_GetPartnerData_API, LVar3)
                    Call(TTYD64_ReadPtrField, LVar3, TTYD64_F_PARTNERDATA_6_1U, LVar3)
                CaseDefault
                    Call(GetActorHP, LVar4, LVar2)
                    Call(GetEnemyMaxHP, LVar4, LVar3)
            EndSwitch
            Call(RandInt, 100, LVar0)
            IfLt(LVar0, 80)
                Set(LVarC, LVar2)
                Div(LVar2, 2)
                IfLe(LVar2, 0)
                    Set(LVar2, 1)
                EndIf
                Sub(LVarC, LVar2)
                Thread
                    IfEq(LVar4, 0)
                        Call(DispatchDamagePlayerEvent, LVar2, 10)
                    Else
                        Call(DispatchDamageEvent, LVar4, LVar2, 10)
                    EndIf
                EndThread
                Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
                Add(LVar1, 15)
                Add(LVar2, 2)
                Call(PlayPoisonHitFX)
                Call(GetItemPower, LVar9, LVar5, LVar6)
                Call(TTYD64_Function_TryToInflictStatus, LVar4, 9, LVar5)
                Call(TTYD64_UpdateKOStatus)
                IfGt(LVarC, 0)
                    IfLt(LVar4, 512)
                        Call(ShowMessageBox, 13, 60)
                        Call(WaitForMessageBoxDone)
                    EndIf
                EndIf
            Else
                IfGe(LVar4, 512)
                    Call(TTYD64_HealActor, LVar4, LVar3)
                Else
                    Call(TTYD64_Heal_PlayerTeam, LVar4, LVar3)
                EndIf
                Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
                Call(SpawnRecoverHeartFX, LVar0, LVar1, LVar2, LVar3)
                Call(ShowRecoveryShimmer, LVar0, LVar1, LVar2, LVar3)
                Call(PlaySoundAtActor, LVar4, 8301)
                IfEq(LVarF, 0)
                    Switch(LVar4)
                        CaseEq(0)
                            Call(SetAnimation, 0, 0, 65586)
                        CaseEq(256)
                            Set(LVar0, 5)
                            Exec(TTYD64_SetPartnerAnimation_Battle)
                    EndSwitch
                EndIf
                Wait(30)
                IfEq(LVarF, 0)
                    Switch(LVar4)
                        CaseEq(0)
                            Call(SetAnimation, 0, 0, 65538)
                        CaseEq(256)
                            Set(LVar0, 0)
                            Exec(TTYD64_SetPartnerAnimation_Battle)
                    EndSwitch
                EndIf
                Wait(2)
            EndIf
            Wait(15)
            Call(UseBattleCamPreset, 2)
        CaseOrEq(427)
        CaseOrEq(429)
        CaseOrEq(446)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Call(GetItemPower, LVar9, LVar5, LVar6)
            Add(LVar0, 0)
            Add(LVar1, 35)
            Switch(LVar9)
                CaseOrEq(427)
                CaseOrEq(429)
                    Call(SpawnRecoverFlowerFX, LVar0, LVar1, LVar2, LVar6)
                    IfLt(LVar4, 512)
                        Call(TTYD64_RecoverFP, LVar6)
                    EndIf
                EndCaseGroup
                CaseEq(446)
                    Call(SpawnRecoverHeartFX, LVar0, LVar1, LVar2, LVar6)
                    IfGe(LVar4, 512)
                        Call(TTYD64_HealActor, LVar4, LVar5)
                    Else
                        Call(TTYD64_Heal_PlayerTeam, LVar4, LVar5)
                    EndIf
            EndSwitch
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar1, 25)
            Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, LVar6)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(GetOwnerTarget, LVar0, 0)
            Call(GetOwnerID, LVar1)
            IfNe(LVar0, LVar1)
                Call(UseIdleAnimation, LVar0, 0)
            EndIf
            Call(GetStatusFlags, LVar0, LVar1)
            IfNotFlag(LVar1, 3526656)
                Switch(LVar0)
                    CaseEq(0)
                        Call(SetAnimation, 0, 0, 65586)
                        Wait(30)
                        Call(SetAnimation, 0, 0, 65538)
                    CaseEq(256)
                        Set(LVar0, 5)
                        Exec(TTYD64_SetPartnerAnimation_Battle)
                        Wait(30)
                        Set(LVar0, 0)
                        Exec(TTYD64_SetPartnerAnimation_Battle)
                    CaseDefault
                        Wait(30)
                EndSwitch
            EndIf
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Call(ShowRecoveryShimmer, LVar0, LVar1, LVar2, LVar6)
            Call(GetOwnerID, LVar0)
            IfLt(LVar0, 512)
                Call(InitTargetIterator)
            EndIf
            Call(TTYD64_bi_Function_ClearDebuffs, LVar4)
            Wait(20)
        EndCaseGroup
        CaseEq(430)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Call(GetItemPower, LVar9, LVar5, LVar6)
            Add(LVar0, 0)
            Add(LVar1, 35)
            Call(SpawnRecoverFlowerFX, LVar0, LVar1, LVar2, LVar6)
            IfLt(LVar4, 512)
                Call(TTYD64_RecoverFP, LVar6)
            EndIf
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar1, 25)
            Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, LVar6)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(GetOwnerTarget, LVar0, 0)
            Call(GetOwnerID, LVar1)
            IfNe(LVar0, LVar1)
                Call(UseIdleAnimation, LVar0, 0)
            EndIf
            Call(GetStatusFlags, LVar0, LVar1)
            IfNotFlag(LVar1, 3526656)
                Switch(LVar0)
                    CaseEq(0)
                        Call(SetAnimation, 0, 0, 65586)
                        Wait(30)
                        Call(SetAnimation, 0, 0, 65538)
                    CaseEq(256)
                        Set(LVar0, 5)
                        Exec(TTYD64_SetPartnerAnimation_Battle)
                        Wait(30)
                        Set(LVar0, 0)
                        Exec(TTYD64_SetPartnerAnimation_Battle)
                    CaseDefault
                        Wait(30)
                EndSwitch
            EndIf
            Call(PlaySoundAtActor, LVar4, 8454)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar0, 15)
            Add(LVar1, 35)
            Set(LVar2, 6)
            Call(PlayEffect_impl, 86, 6, LVar0, LVar1, LVar2, Float(1.5), 60, 0, 0, 0, 0, 0, 0, 0)
            Call(TTYD64_GetEffectData, LVarF, LVar0)
            Call(TTYD64_WritePtrField, LVar0, TTYD64_F_STATCHANGEFXDATA_20_4U, LVar5)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar1, 15)
            Add(LVar2, 2)
            Call(TTYD64_GetEffectData, LVarF, LVar7)
            Call(TTYD64_WritePtrField, LVar7, TTYD64_F_STATCHANGEFXDATA_1C_4U, 3)
            Call(PlayEffect_impl, 49, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Call(ShowRecoveryShimmer, LVar0, LVar1, LVar2, LVar6)
            Call(GetOwnerID, LVar0)
            IfLt(LVar0, 512)
                Call(InitTargetIterator)
            EndIf
            Mul(LVar5, -1)
            Call(TTYD64_AddDefenseBoost, LVar4, LVar5, 3)
            Wait(20)
        CaseOrEq(431)
        CaseOrEq(452)
        CaseOrEq(445)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Call(GetItemPower, LVar9, LVar5, LVar6)
            Add(LVar0, 0)
            Add(LVar1, 35)
            Switch(LVar9)
                CaseOrEq(431)
                CaseOrEq(452)
                    Call(SpawnRecoverFlowerFX, LVar0, LVar1, LVar2, LVar6)
                    IfLt(LVar4, 512)
                        Call(TTYD64_RecoverFP, LVar6)
                    EndIf
                EndCaseGroup
                CaseEq(445)
                    Call(SpawnRecoverHeartFX, LVar0, LVar1, LVar2, LVar5)
                    IfGe(LVar4, 512)
                        Call(TTYD64_HealActor, LVar4, LVar5)
                    Else
                        Call(TTYD64_Heal_PlayerTeam, LVar4, LVar5)
                    EndIf
            EndSwitch
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar1, 25)
            Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, LVar6)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Call(GetOwnerTarget, LVar0, 0)
            Call(GetOwnerID, LVar1)
            IfNe(LVar0, LVar1)
                Call(UseIdleAnimation, LVar0, 0)
            EndIf
            Call(GetStatusFlags, LVar0, LVar1)
            IfNotFlag(LVar1, 3526656)
                Switch(LVar0)
                    CaseEq(0)
                        Call(SetAnimation, 0, 0, 65586)
                        Wait(30)
                        Call(SetAnimation, 0, 0, 65538)
                    CaseEq(256)
                        Set(LVar0, 5)
                        Exec(TTYD64_SetPartnerAnimation_Battle)
                        Wait(30)
                        Set(LVar0, 0)
                        Exec(TTYD64_SetPartnerAnimation_Battle)
                    CaseDefault
                        Wait(30)
                EndSwitch
            EndIf
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Call(ShowRecoveryShimmer, LVar0, LVar1, LVar2, LVar6)
            Call(GetOwnerID, LVar0)
            IfLt(LVar0, 512)
                Call(InitTargetIterator)
            EndIf
            Call(RandInt, 100, LVar0)
            IfEq(LVar9, 445)
                Set(LVar0, 0)
            EndIf
            IfLe(LVar0, 30)
                Call(TTYD64_Function_TryToInflictStatus, LVar4, 7, 2)
                Call(GetStatusFlags, LVar4, LVar0)
                IfFlag(LVar0, 16384)
                    Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
                    Call(TTYD64_GetActorPointer, LVar4, LVar3)
                    Call(PlayFreezeHitParticleFX)
                    IfLt(LVar4, 512)
                        Call(ShowMessageBox, 12, 60)
                        Call(WaitForMessageBoxDone)
                    EndIf
                EndIf
            EndIf
            Wait(20)
        EndCaseGroup
        CaseEq(442)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar1, 20)
            Add(LVar2, 2)
            Call(PlayEffect_impl, 34, 0, LVar0, LVar1, LVar2, -54, 37, 12, 20, 0, 0, 0, 0, 0)
            Call(PlaySoundAtActor, LVar4, 8277)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Call(ShowRecoveryShimmer, LVar0, LVar1, LVar2, LVarB)
            Call(UseBattleCamPreset, 2)
            Call(GetItemPower, LVar9, LVar5, LVar6)
            Call(TTYD64_SetActorExtraData, LVar4, 9, LVar6)
            Call(TTYD64_SetActorExtraData, LVar4, 8, LVar5)
            Wait(20)
            Call(PlaySoundAtActor, LVar4, 8454)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar0, 15)
            Add(LVar1, 35)
            Set(LVar2, 6)
            Call(PlayEffect_impl, 86, 6, LVar0, LVar1, LVar2, Float(1.5), 60, 0, 0, 0, 0, 0, 0, 0)
            Call(TTYD64_GetEffectData, LVarF, LVar0)
            Call(TTYD64_WritePtrField, LVar0, TTYD64_F_STATCHANGEFXDATA_20_4U, LVar5)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar1, 15)
            Add(LVar2, 2)
            Call(TTYD64_GetEffectData, LVarF, LVar7)
            Call(TTYD64_WritePtrField, LVar7, TTYD64_F_STATCHANGEFXDATA_1C_4U, 3)
            Call(PlayEffect_impl, 49, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Call(ShowRecoveryShimmer, LVar0, LVar1, LVar2, LVar6)
            Call(GetOwnerID, LVar0)
            IfLt(LVar0, 512)
                Call(InitTargetIterator)
            EndIf
            Mul(LVar5, -1)
            Call(TTYD64_AddDefenseBoost, LVar4, LVar5, 3)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Call(GetOwnerTarget, LVar0, 0)
            Call(GetOwnerID, LVar1)
            IfNe(LVar0, LVar1)
                Call(UseIdleAnimation, LVar0, 0)
            EndIf
            Call(GetStatusFlags, LVar0, LVar1)
            IfNotFlag(LVar1, 3526656)
                Switch(LVar0)
                    CaseEq(0)
                        Call(SetAnimation, 0, 0, 65586)
                        Wait(30)
                        Call(SetAnimation, 0, 0, 65538)
                    CaseEq(256)
                        Set(LVar0, 5)
                        Exec(TTYD64_SetPartnerAnimation_Battle)
                        Wait(30)
                        Set(LVar0, 0)
                        Exec(TTYD64_SetPartnerAnimation_Battle)
                    CaseDefault
                        Wait(30)
                EndSwitch
            EndIf
            Wait(20)
        CaseEq(421)
            ExecWait(TTYD64_BattleScript_GoBackToHome_HealingItem)
            Thread
                Wait(10)
                Call(PlaySoundAtActor, LVar4, 736)
            EndThread
            Wait(30)
            Call(GetOwnerTarget, LVar4, 0)
            IfLt(LVar4, 512)
                IfEq(LVar4, 0)
                    Call(TTYD64_WriteField, TTYD64_F_GPLAYERDATA_2_1U, 1)
                Else
                    Call(TTYD64_GetPartnerHP_API, LVar0)
                    IfGt(LVar0, 0)
                        Call(TTYD64_GetPartnerData_API, LVar1)
                        Call(TTYD64_WritePtrField, LVar1, TTYD64_F_PARTNERDATA_5_1U, 1)
                    EndIf
                EndIf
                Call(FullyRestoreSP)
                Call(TTYD64_WriteField, TTYD64_F_GPLAYERDATA_5_1U, 0)
            Else
                Call(SetEnemyHP, LVar4, 1)
            EndIf
            IfLt(LVar4, 512)
                IfEq(LVar4, 0)
                    Thread
                        Call(DispatchDamagePlayerEvent, 0, 10)
                    EndThread
                Else
                    Call(TTYD64_GetPartnerHP_API, LVar0)
                    IfGt(LVar0, 0)
                        Thread
                            Call(DispatchDamageEvent, 256, 0, 10)
                        EndThread
                    EndIf
                EndIf
            Else
                Call(DispatchDamageEvent, LVar4, 0, 10)
            EndIf
            Return
    EndSwitch
    ExecWait(TTYD64_BattleScript_GoBackToHome_HealingItem)
    Return
    End
};

EvtScript TTYD64_bi_UseItem_StatusItem_MultiTarget = {
    Call(GetOwnerID, LVar0)
    IfLt(LVar0, 512)
        Call(InitTargetIterator)
    EndIf
    Switch(LVar9)
        CaseOrEq(412)
        CaseOrEq(413)
            Call(UseBattleCamPreset, 2)
            Label(0)
            Call(SetGoalToTarget, -127)
            Call(ItemCheckHit, LVar0, 268435456, 0, LVar0, 0)
            IfEq(LVar0, 6)
                Goto(1)
            EndIf
            Wait(1)
            Call(SetGoalToTarget, -127)
            Call(GetOwnerTarget, LVar4, LVar6)
            Call(GetItemPower, LVar9, LVar5, 0)
            Mul(LVar5, -1)
            Switch(LVar9)
                CaseEq(412)
                    Call(TTYD64_AddAttackBoost, LVar4, LVar5, 3)
                    Call(TTYD64_MakeActorTiny, LVar4)
                CaseEq(413)
                    Call(TTYD64_Function_GetActorDefense, LVar4, LVar6, 1, LVar7)
                    IfGt(LVar7, 0)
                        IfGe(LVar7, 3)
                            Set(LVar5, -3)
                        Else
                            Set(LVar5, LVar7)
                            Mul(LVar5, -1)
                        EndIf
                        Call(TTYD64_AddDefenseBoost, LVar4, LVar5, 3)
                    Else
                        Set(LVar5, 0)
                    EndIf
            EndSwitch
            Call(PlaySoundAtActor, LVar4, 8454)
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar0, 15)
            Add(LVar1, 35)
            Set(LVar2, 6)
            Set(LVar6, 86)
            Switch(LVar9)
                CaseEq(412)
                    Set(LVar7, 3)
                CaseEq(413)
                    Set(LVar7, 6)
            EndSwitch
            IfNe(LVar5, 0)
                Call(PlayEffect_impl, LVar6, LVar7, LVar0, LVar1, LVar2, Float(1.5), 60, 0, 0, 0, 0, 0, 0, 0)
                Call(TTYD64_GetEffectData, LVarF, LVar0)
                Call(TTYD64_WritePtrField, LVar0, TTYD64_F_STATCHANGEFXDATA_20_4U, LVar5)
            EndIf
            Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
            Add(LVar1, 15)
            Add(LVar2, 2)
            Switch(LVar9)
                CaseEq(412)
                    Call(PlayParalyzeHitFX)
                CaseEq(413)
                    IfNe(LVar5, 0)
                        Call(TTYD64_GetEffectData, LVarF, LVar6)
                        Call(TTYD64_WritePtrField, LVar6, TTYD64_F_EFFECT_DATA_1C_4U, 3)
                        Call(PlayEffect_impl, 49, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                    EndIf
            EndSwitch
            Label(1)
            Wait(5)
            Call(GetOwnerID, LVar2)
            IfGe(LVar2, 512)
                Call(GetOwnerTarget, LVar0, LVar1)
                Call(TTYD64_GetPartnerHP_API, LVar1)
                IfLe(LVar1, 0)
                    Set(LVar0, 256)
                EndIf
                IfNe(LVar0, 256)
                    Call(SetTargetActor, -127, 256)
                    Goto(0)
                EndIf
            Else
                Call(ChooseNextTarget, 0, LVar0)
                IfNe(LVar0, -1)
                    Goto(0)
                EndIf
            EndIf
            Call(GetOwnerTarget, LVar7, 0)
            Call(GetOwnerID, LVar4)
            IfNe(LVar7, LVar4)
                Call(UseIdleAnimation, LVar7, 0)
            EndIf
            Switch(LVar7)
                CaseEq(0)
                    Call(SetAnimation, 0, 0, 65538)
                CaseEq(256)
                    Set(LVar0, 0)
                    Exec(TTYD64_SetPartnerAnimation_Battle)
                CaseDefault
            EndSwitch
            Wait(30)
            Switch(LVar9)
                CaseEq(412)
                    Call(ShowMessageBox, 266, 60)
                    Call(WaitForMessageBoxDone)
                CaseEq(413)
                    Call(ShowMessageBox, 265, 60)
                    Call(WaitForMessageBoxDone)
            EndSwitch
        EndCaseGroup
        CaseEq(418)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 25)
            Wait(30)
            Label(2)
            Call(SetGoalToTarget, -127)
            Call(ItemCheckHit, LVar0, 268435456, 0, LVar0, 0)
            IfEq(LVar0, 6)
                Goto(3)
            EndIf
            Call(SetGoalToTarget, -127)
            Call(GetItemPower, 418, LVar0, LVar1)
            Call(MakeStatusField, LVar0, 262144, 100, LVar0)
            Call(ItemAfflictEnemy, LVar0, 1342177280, LVar0, 0, 32)
            Call(RandInt, 100, LVar0)
            IfLe(LVar0, 50)
                Call(GetOwnerTarget, LVar0, 0)
                Call(TTYD64_Function_TryToInflictStatus, LVar0, 4, 3)
            EndIf
            Label(3)
            Call(GetOwnerID, LVar2)
            IfGe(LVar2, 512)
                Call(GetOwnerTarget, LVar0, LVar1)
                Call(TTYD64_GetPartnerHP_API, LVar1)
                IfLe(LVar1, 0)
                    Set(LVar0, 256)
                EndIf
                IfNe(LVar0, 256)
                    Call(SetTargetActor, -127, 256)
                    Goto(2)
                EndIf
            Else
                Call(ChooseNextTarget, 0, LVar0)
                IfNe(LVar0, -1)
                    Goto(2)
                EndIf
            EndIf
            Call(GetOwnerTarget, LVar7, 0)
            Call(GetOwnerID, LVar4)
            IfNe(LVar7, LVar4)
                Call(UseIdleAnimation, LVar7, 0)
            EndIf
            Switch(LVar7)
                CaseEq(0)
                    Call(SetAnimation, 0, 0, 65538)
                CaseEq(256)
                    Set(LVar0, 0)
                    Exec(TTYD64_SetPartnerAnimation_Battle)
                CaseDefault
            EndSwitch
            Wait(30)
    EndSwitch
    ExecWait(TTYD64_BattleScript_GoBackToHome_Item)
    Return
    End
};

EvtScript TTYD64_bi_UseItem_OffensiveItem_SingleTarget = {
    Call(GetOwnerID, LVar0)
    IfLt(LVar0, 512)
        Call(InitTargetIterator)
    EndIf
    Switch(LVar9)
        CaseEq(409)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 25)
            Call(GetOwnerID, LVar7)
            Call(SetGoalToTarget, LVar7)
            Call(ItemCheckHit, LVar0, 268435456, 0, LVar0, 0)
            IfEq(LVar0, 6)
                Wait(30)
                ExecWait(TTYD64_BattleScript_GoBackToHome_Item)
                Return
            EndIf
            Loop(2)
                Call(PlaySound, 992)
                Wait(10)
            EndLoop
            Call(GetItemPower, 409, LVar1, 0)
            Call(ItemDamageEnemy, 0, 436207616, 0, LVar1, 32)
            Call(GetActorPos, LVar7, LVar2, LVar3, LVar4)
            Switch(LVar7)
                CaseEq(0)
                    Call(SetAnimation, 0, 0, 65538)
                    Call(TTYD64_Heal_PlayerTeam, LVar7, LVar1)
                CaseEq(256)
                    Set(LVar0, 0)
                    Exec(TTYD64_SetPartnerAnimation_Battle)
                    Call(TTYD64_Heal_PlayerTeam, LVar7, LVar1)
                CaseDefault
                    Call(TTYD64_HealActor, LVar7, LVar1)
            EndSwitch
            Call(PlaySoundAtActor, LVar7, 8301)
            Call(SpawnRecoverHeartFX, LVar2, LVar3, LVar4, LVar1)
            Wait(30)
        CaseOrEq(424)
        CaseOrEq(426)
        CaseOrEq(451)
            Call(GetOwnerID, LVar7)
            Switch(LVar7)
                CaseEq(0)
                    Call(UseBattleCamPreset, 3)
                    Call(MoveBattleCamOver, 15)
                    Call(SetAnimation, 0, 0, 65558)
                CaseEq(256)
                    Call(UseBattleCamPreset, 3)
                    Call(MoveBattleCamOver, 15)
                    Call(GetCurrentPartnerID, LVar0)
                    IfEq(LVar0, 8)
                        Call(SetAnimation, 256, 0, 1048594)
                    EndIf
                CaseDefault
                    Call(UseBattleCamPreset, 2)
                    Call(MoveBattleCamOver, 15)
            EndSwitch
            Call(PlaySound, 1018)
            Wait(3)
            Switch(LVar9)
                CaseEq(424)
                    Call(CreateVirtualEntity, LVarA, (Bytecode) TTYD64_bi_EntityModelScript_CoconutBomb)
                CaseEq(426)
                    Call(CreateVirtualEntity, LVarA, (Bytecode) TTYD64_bi_EntityModelScript_CourageMeal)
                CaseEq(451)
                    Call(CreateVirtualEntity, LVarA, (Bytecode) TTYD64_bi_EntityModelScript_Dynamite)
            EndSwitch
            Call(GetActorPos, -127, LVar0, LVar1, LVar2)
            Add(LVar0, 20)
            Add(LVar1, 42)
            Add(LVar2, 5)
            Call(SetVirtualEntityPosition, LVarA, LVar0, LVar1, LVar2)
            Call(GetOwnerID, LVar0)
            IfLt(LVar0, 512)
                Call(InitTargetIterator)
            EndIf
            Call(SetGoalToTarget, -127)
            Call(GetGoalPos, -127, LVar0, LVar1, LVar2)
            IfEq(LVar9, 451)
                Set(LVar0, 71)
                Set(LVar1, 0)
                Set(LVar2, -5)
            EndIf
            Thread
                Set(LVar0, 0)
                Loop(18)
                    Add(LVar0, 60)
                    Call(SetVirtualEntityRotation, LVarA, 0, 0, LVar0)
                    Wait(1)
                EndLoop
            EndThread
            Call(SetVirtualEntityJumpGravity, LVarA, Float(1.0))
            Add(LVar2, 5)
            Call(VirtualEntityJumpTo, LVarA, LVar0, LVar1, LVar2, 18)
            Call(DeleteVirtualEntity, LVarA)
            Call(PlaySound, 8208)
            Call(TTYD64_bi_Function_802A123C_Projectile, LVar0, LVar1, LVar2)
            Thread
                Call(StartRumble, 5)
                Call(ShakeCam, 1, 0, 2, Float(0.75))
                Call(ShakeCam, 1, 0, 5, Float(1.5))
                Call(ShakeCam, 1, 0, 4, Float(1.2001953125))
                Call(ShakeCam, 1, 0, 2, Float(0.4501953125))
            EndThread
            Switch(LVar9)
                CaseOrEq(424)
                CaseOrEq(426)
                    Call(ItemCheckHit, LVar0, 268435456, 0, LVar0, 0)
                    IfEq(LVar0, 6)
                        Wait(1)
                        Goto(0)
                    EndIf
                EndCaseGroup
                CaseEq(451)
                    Call(CreateNpc, 48, 11141133)
                    Call(SetNpcPos, 48, 71, 0, -5)
                    Call(SetNpcScale, 48, Float(3.0), Float(3.0), Float(3.0))
                    Call(SetNpcImgFXParams, 48, 7, 0, 0, 0, 0)
                    Thread
                        Call(GetNpcPos, 48, LVar0, LVar1, LVar2)
                        Sub(LVar0, 0)
                        Sub(LVar1, 96)
                        Sub(LVar2, 3)
                        Call(PlayEffect_impl, 32, 1, LVar0, LVar1, LVar2, Float(3.2001953125), 0, 0, 0, 0, 0, 0, 0, 0)
                        Call(TTYD64_GetEffect, LVarF, LVarE)
                        Set(LVar1, 0)
                        Loop(10)
                            Add(LVar1, 24)
                            Call(SetNpcImgFXParams, 48, 7, LVar1, 0, 0, 0)
                            Wait(1)
                        EndLoop
                        Call(SetNpcImgFXParams, 48, 7, 255, 0, 0, 0)
                        Wait(5)
                        Call(GetNpcPos, 48, LVar0, LVar1, LVar2)
                        Add(LVar1, 35)
                        Call(PlayEffect_impl, 25, 2, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                        Call(PlaySound, 8216)
                        Wait(20)
                        Call(RemoveEffect, LVarE)
                        Set(LVar1, 255)
                        Loop(10)
                            Sub(LVar1, 24)
                            Call(SetNpcImgFXParams, 48, 7, LVar1, 0, 0, 0)
                            Wait(1)
                        EndLoop
                        Call(SetNpcImgFXParams, 48, 7, 0, 0, 0, 0)
                        Call(DeleteNpc, 48)
                    EndThread
                    Wait(15)
                    Label(1)
                    Call(SetGoalToTarget, -127)
                    Call(ItemCheckHit, LVar0, 268435456, 0, LVar0, 0)
                    IfEq(LVar0, 6)
                        Goto(2)
                    EndIf
                    Call(SetGoalToTarget, -127)
                    Call(GetItemPower, LVar9, LVar0, LVar1)
                    Call(ItemDamageEnemy, LVar0, 973079040, 0, LVar0, 32)
                    Label(2)
                    Call(GetOwnerID, LVar2)
                    IfGe(LVar2, 512)
                        Call(GetOwnerTarget, LVar0, LVar1)
                        Call(TTYD64_GetPartnerHP_API, LVar1)
                        IfLe(LVar1, 0)
                            Set(LVar0, 256)
                        EndIf
                        IfNe(LVar0, 256)
                            Call(SetTargetActor, -127, 256)
                            Goto(1)
                        EndIf
                    Else
                        Call(ChooseNextTarget, 0, LVar0)
                        IfNe(LVar0, -1)
                            Goto(1)
                        EndIf
                    EndIf
                    Call(GetOwnerTarget, LVar7, 0)
                    Call(GetOwnerID, LVar4)
                    IfNe(LVar7, LVar4)
                        Call(UseIdleAnimation, LVar7, 0)
                    EndIf
                    Switch(LVar7)
                        CaseEq(0)
                            Call(SetAnimation, 0, 0, 65538)
                        CaseEq(256)
                            Set(LVar0, 0)
                            Exec(TTYD64_SetPartnerAnimation_Battle)
                        CaseDefault
                    EndSwitch
                    Wait(30)
                    Goto(0)
            EndSwitch
            Call(GetItemPower, LVar9, LVar0, LVar1)
            Switch(LVar9)
                CaseEq(426)
                    Call(ItemDamageEnemy, LVar0, 436207616, 0, LVar0, 32)
                CaseDefault
                    Call(ItemDamageEnemy, LVar0, 436208130, 0, LVar0, 32)
            EndSwitch
            Label(0)
        EndCaseGroup
    EndSwitch
    ExecWait(TTYD64_BattleScript_GoBackToHome_Item)
    Return
    End
};

EvtScript TTYD64_bi_UseItem_OffensiveItem_MultiTarget = {
    Call(GetOwnerID, LVar0)
    IfLt(LVar0, 512)
        Call(InitTargetIterator)
    EndIf
    Switch(LVar9)
        CaseEq(400)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 25)
            Call(StartRumble, 4)
            Call(PlaySoundAtActor, -127, 96)
            Call(ShakeCam, 1, 0, 5, Float(0.2001953125))
            Thread
                Call(GetActorPos, 0, LVar0, LVar1, LVar2)
                Add(LVar1, 150)
                Call(PlayEffect_impl, 21, 1, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
                Wait(3)
                Add(LVar0, 34)
                Call(PlayEffect_impl, 21, 1, LVar0, LVar1, LVar2, 25, 0, 0, 0, 0, 0, 0, 0, 0)
                Wait(6)
                Add(LVar0, 34)
                Call(PlayEffect_impl, 21, 1, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
                Wait(4)
                Add(LVar0, 34)
                Call(PlayEffect_impl, 21, 1, LVar0, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0)
                Wait(7)
                Add(LVar0, 50)
                Call(PlayEffect_impl, 21, 1, LVar0, LVar1, LVar2, 15, 0, 0, 0, 0, 0, 0, 0, 0)
                Wait(3)
                Add(LVar0, 34)
                Call(PlayEffect_impl, 21, 1, LVar0, LVar1, LVar2, 25, 0, 0, 0, 0, 0, 0, 0, 0)
                Wait(6)
                Add(LVar0, 34)
                Call(PlayEffect_impl, 21, 1, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
                Wait(4)
                Add(LVar0, 34)
                Call(PlayEffect_impl, 21, 1, LVar0, LVar1, LVar2, 25, 0, 0, 0, 0, 0, 0, 0, 0)
                Wait(7)
                Add(LVar0, 50)
                Call(PlayEffect_impl, 21, 1, LVar0, LVar1, LVar2, 20, 0, 0, 0, 0, 0, 0, 0, 0)
            EndThread
            Call(ShakeCam, 1, 0, 5, Float(0.400390625))
            Call(ShakeCam, 1, 0, 10, Float(0.599609375))
            Call(ShakeCam, 1, 0, 15, Float(2.0))
            Call(StopSound, 96)
            Call(PlaySoundAtActor, -127, 221)
            Thread
                Call(StartRumble, 4)
                Call(ShakeCam, 1, 0, 2, Float(1.0))
                Call(ShakeCam, 1, 0, 2, Float(3.0))
                Call(ShakeCam, 1, 0, 2, Float(6.0))
                Call(ShakeCam, 1, 0, 2, Float(5.0))
                Call(ShakeCam, 1, 0, 2, Float(4.0))
                Call(ShakeCam, 1, 0, 2, Float(3.0))
                Call(ShakeCam, 1, 0, 2, Float(2.0))
                Call(ShakeCam, 1, 0, 2, Float(1.0))
                Call(ShakeCam, 1, 0, 2, Float(0.5))
                Call(ShakeCam, 1, 0, 2, Float(0.2001953125))
            EndThread
            Label(0)
            Call(SetGoalToTarget, -127)
            Call(ItemCheckHit, LVar0, 268435456, 0, LVar0, 0)
            IfEq(LVar0, 6)
                Goto(1)
            EndIf
            Call(SetGoalToTarget, -127)
            Call(GetItemPower, 400, LVar0, LVar1)
            Call(ItemDamageEnemy, LVar0, 973080576, 0, LVar0, 32)
            Label(1)
            Call(GetOwnerID, LVar2)
            IfGe(LVar2, 512)
                Call(GetOwnerTarget, LVar0, LVar1)
                Call(TTYD64_GetPartnerHP_API, LVar1)
                IfLe(LVar1, 0)
                    Set(LVar0, 256)
                EndIf
                IfNe(LVar0, 256)
                    Call(SetTargetActor, -127, 256)
                    Goto(0)
                EndIf
            Else
                Call(ChooseNextTarget, 0, LVar0)
                IfNe(LVar0, -1)
                    Goto(0)
                EndIf
            EndIf
            Call(GetOwnerTarget, LVar7, 0)
            Call(GetOwnerID, LVar4)
            IfNe(LVar7, LVar4)
                Call(UseIdleAnimation, LVar7, 0)
            EndIf
            Switch(LVar7)
                CaseEq(0)
                    Call(SetAnimation, 0, 0, 65538)
                CaseEq(256)
                    Set(LVar0, 0)
                    Exec(TTYD64_SetPartnerAnimation_Battle)
                CaseDefault
            EndSwitch
            Wait(30)
        CaseEq(410)
            Call(PlaySoundAtActor, -127, 861)
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 25)
            Thread
                Call(GetOwnerID, LVar3)
                Set(LVar6, 0)
                Loop(17)
                    IfEq(LVar6, 0)
                        Call(GetActorPos, LVar3, LVar4, 0, 0)
                    EndIf
                    Add(LVar6, 1)
                    IfEq(LVar6, 6)
                        Set(LVar6, 0)
                    EndIf
                    IfGe(LVar3, 512)
                        Sub(LVar4, 30)
                    Else
                        Add(LVar4, 30)
                    EndIf
                    Set(LVar1, 40)
                    Call(RandInt, 25, LVar5)
                    Call(RandInt, 1, LVar2)
                    IfEq(LVar1, 1)
                        Mul(LVar5, -1)
                    EndIf
                    Add(LVar1, LVar5)
                    Call(RandInt, 50, LVar2)
                    Sub(LVar2, 25)
                    Call(PlayEffect_impl, 14, LVar4, LVar1, LVar2, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                    Wait(2)
                EndLoop
            EndThread
            Call(GetOwnerID, LVar3)
            IfGe(LVar3, 512)
                SetF(LVar3, Float(180.0))
            Else
                Set(LVar3, 0)
            EndIf
            Call(GetActorPos, -127, LVar0, LVar1, LVar2)
            Set(LVar1, 25)
            Call(PlayEffect_impl, 110, 0, LVar0, LVar1, LVar2, LVar3, Float(2.0), Float(1.0), 60, 0, 0, 0, 0, 0)
            Call(TTYD64_bi_Function_IceStorm_ChangeBreathColor, LVarF)
            Call(TTYD64_bi_Function_IceStorm_Rumble, 70, 100)
            Thread
                Call(ShakeCam, 1, 0, 50, Float(0.2998046875))
            EndThread
            Wait(60)
            Call(StopSound, 861)
            Label(2)
            Call(SetGoalToTarget, -127)
            Call(ItemCheckHit, LVar0, 268435464, 0, LVar0, 0)
            IfEq(LVar0, 6)
                Goto(3)
            EndIf
            Call(SetGoalToTarget, -127)
            Call(GetItemPower, 410, LVar0, LVar1)
            Call(ItemDamageEnemy, LVar0, 973078536, 0, LVar0, 32)
            Call(RandInt, 100, LVar0)
            IfLe(LVar0, 50)
                Call(GetOwnerTarget, LVar0, 0)
                Call(TTYD64_Function_TryToInflictStatus, LVar0, 7, 3)
            EndIf
            Label(3)
            Call(GetOwnerID, LVar2)
            IfGe(LVar2, 512)
                Call(GetOwnerTarget, LVar0, LVar1)
                Call(TTYD64_GetPartnerHP_API, LVar1)
                IfLe(LVar1, 0)
                    Set(LVar0, 256)
                EndIf
                IfNe(LVar0, 256)
                    Call(SetTargetActor, -127, 256)
                    Goto(2)
                EndIf
            Else
                Call(ChooseNextTarget, 0, LVar0)
                IfNe(LVar0, -1)
                    Goto(2)
                EndIf
            EndIf
            Call(GetOwnerTarget, LVar7, 0)
            Call(GetOwnerID, LVar4)
            IfNe(LVar7, LVar4)
                Call(UseIdleAnimation, LVar7, 0)
            EndIf
            Switch(LVar7)
                CaseEq(0)
                    Call(SetAnimation, 0, 0, 65538)
                CaseEq(256)
                    Set(LVar0, 0)
                    Exec(TTYD64_SetPartnerAnimation_Battle)
                CaseDefault
            EndSwitch
            Wait(30)
    EndSwitch
    ExecWait(TTYD64_BattleScript_GoBackToHome_Item)
    Return
    End
};

EvtScript TTYD64_bi_UseItem_StrangeCake = {
    Call(GetOwnerID, LVar0)
    IfLt(LVar0, 512)
        Call(InitTargetIterator)
    EndIf
    Call(GetOwnerTarget, LVar4, 0)
    Set(LVarF, 0)
    Call(GetStatusFlags, LVar4, LVar0)
    IfFlag(LVar0, 3526656)
        Set(LVarF, 1)
    EndIf
    Wait(10)
    Thread
        Wait(220)
        Call(PlaySoundAtActor, -127, 1011)
    EndThread
    Call(PlaySoundAtActor, -127, 872)
    Call(battle_item_strange_cake_func_802A13E4_7316E4)
    Wait(2)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_bi_Script_RandomEffect_Static)
        CaseEq(1)
            ExecWait(TTYD64_bi_Script_RandomEffect_Invicible)
        CaseEq(2)
            ExecWait(TTYD64_bi_Script_RandomEffect_Sleep)
    EndSwitch
    ExecWait(TTYD64_BattleScript_GoBackToHome_HealingItem)
    Return
    End
};

EvtScript TTYD64_bi_Script_RandomEffect_Static = {
    Call(GetOwnerTarget, LVar4, 0)
    Switch(LVar4)
        CaseEq(0)
            Call(SetAnimation, 0, 0, 65538)
        CaseEq(256)
            Set(LVar0, 0)
            Exec(TTYD64_SetPartnerAnimation_Battle)
        CaseDefault
    EndSwitch
    Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
    Call(TTYD64_Function_InflictStatus, LVar4, 11, 3)
    IfEq(LVar4, 0)
        Wait(20)
        Call(ShowMessageBox, 16, 60)
        Call(WaitForMessageBoxDone)
    Else
        Wait(30)
    EndIf
    Return
    End
};

EvtScript TTYD64_bi_Script_RandomEffect_Invicible = {
    Call(GetOwnerTarget, LVar4, 0)
    Switch(LVar4)
        CaseEq(0)
            Call(SetAnimation, 0, 0, 65538)
        CaseEq(256)
            Set(LVar0, 0)
            Exec(TTYD64_SetPartnerAnimation_Battle)
        CaseDefault
    EndSwitch
    Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(PlayEffect_impl, 51, 6, LVar0, LVar1, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
    Call(TTYD64_Function_InflictStatus, LVar4, 14, 3)
    IfEq(LVar4, 0)
        Wait(20)
        Call(ShowMessageBox, 17, 60)
        Call(WaitForMessageBoxDone)
    Else
        Wait(30)
    EndIf
    Return
    End
};

EvtScript TTYD64_bi_Script_RandomEffect_Sleep = {
    Call(GetOwnerTarget, LVar4, 0)
    Switch(LVar4)
        CaseEq(0)
            Call(SetAnimation, 0, 0, 196612)
        CaseEq(256)
        CaseDefault
    EndSwitch
    Call(SetGoalToTarget, LVar4)
    Call(GetGoalPos, LVar4, LVar0, LVar1, LVar2)
    Exec(EVS_PlaySleepHitFX)
    Call(TTYD64_Function_TryToInflictStatus, LVar4, 6, 3)
    IfEq(LVar4, 0)
        Wait(20)
        Call(ShowMessageBox, 11, 60)
        Call(WaitForMessageBoxDone)
    Else
        Wait(30)
    EndIf
    Return
    End
};
// clang-format on
