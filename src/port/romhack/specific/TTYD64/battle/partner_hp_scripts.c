#include "port/romhack/specific/TTYD64/partner_hp_internal.h"

API_CALLABLE(ConsumeLifeShroom);
API_CALLABLE(GiveRefund);
API_CALLABLE(GiveRefundCleanup);
API_CALLABLE(LifeShroomRevealWorld);
API_CALLABLE(LifeShroomShroudWorld);
API_CALLABLE(RestorePreDefeatState);
API_CALLABLE(SetItemAsLifeShroom);
API_CALLABLE(WorldItem_ConsumeItem);
API_CALLABLE(WorldItem_GetItemProperties);
API_CALLABLE(WorldItem_PauseTime);
API_CALLABLE(WorldItem_RestoreFP);
API_CALLABLE(WorldItem_RestoreHP);
API_CALLABLE(WorldItem_ShowFPGain);
API_CALLABLE(WorldItem_ShowHPGain);
API_CALLABLE(WorldItem_ShowUseSparkles);
API_CALLABLE(WorldItem_UnpauseTime);
API_CALLABLE(func_80261388);
EvtScript TTYD64_UseItem_Init;
EvtScript TTYD64_UseItem_ShowItem;
EvtScript TTYD64_UseItem_Eat;
EvtScript TTYD64_UseItem_Drink;
EvtScript TTYD64_DoPartnerSpikeContact;
EvtScript TTYD64_DoPartnerBurnContact;
EvtScript TTYD64_PartnerDies;
EvtScript TTYD64_UseLifeShroom_Actor;
EvtScript TTYD64_ph_UseLifeShroom;
EvtScript TTYD64_Script_SwapHeroesPositions_MoveMarioUpfront;
EvtScript TTYD64_Script_SHP_MMU_MovePartner;
EvtScript TTYD64_PartnerRunAway;
EvtScript TTYD64_BattleScript_EatItem;
EvtScript TTYD64_BattleScript_DrinkItem;
EvtScript TTYD64_BattleScript_GoBackToHome_HealingItem;
EvtScript TTYD64_BattleScript_GoBackToHome_Item;
EvtScript TTYD64_Items_RestoreHeroeTurn;
EvtScript TTYD64_SetPartnerAnimation_Battle;
EvtScript TTYD64_ph_EVS_World_UseItem;
EvtScript TTYD64_ph_EVS_Partner_SpikeContact;
EvtScript TTYD64_ph_EVS_Partner_BurnContact;
EvtScript TTYD64_ph_EVS_UseLifeShroom;
EvtScript TTYD64_ph_EVS_Partner_RunAway;

// clang-format off
EvtScript TTYD64_UseItem_Init = {
    SetGroup(0)
    Call(DisablePlayerInput, 1)
    Call(GetPartnerInUse, LVar0)
    IfNe(LVar0, 0)
        Call(InterruptUsePartner)
        Wait(20)
    EndIf
    Call(WorldItem_PauseTime)
    Call(WorldItem_GetItemProperties, LVarA)
    ExecWait(TTYD64_UseItem_ShowItem)
    IfEq(LVarD, 0)
        ExecWait(TTYD64_UseItem_Eat)
    Else
        ExecWait(TTYD64_UseItem_Drink)
    EndIf
    IfEq(LVarF, 1)
        Call(TTYD64_GetHealBoxTarget, LVar3)
        Switch(LVar3)
            CaseEq(0)
                Call(SetPlayerAnimation, 65565)
            CaseEq(1)
                Set(LVar0, 4)
                Set(LVar1, 0)
                Exec(TTYD64_SetPartnerAnimation)
            CaseGt(1)
        EndSwitch
    EndIf
    IfGt(LVarB, 0)
        Call(TTYD64_GetHealBoxTarget, LVar3)
        IfEq(LVar3, 1)
            Call(GetNpcPos, -4, LVar0, LVar1, LVar2)
            Call(GetCurrentPartnerID, LVar3)
            Switch(LVar3)
                CaseOrEq(6)
                CaseOrEq(9)
                    Add(LVar1, -10)
            EndSwitch
        Else
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
        EndIf
        Add(LVar0, 0)
        Add(LVar1, 35)
        Call(WorldItem_ShowHPGain, LVar0, LVar1, LVar2, LVarB)
    EndIf
    IfGt(LVarC, 0)
        Call(TTYD64_GetHealBoxTarget, LVar3)
        IfEq(LVar3, 1)
            Call(GetNpcPos, -4, LVar0, LVar1, LVar2)
            Call(GetCurrentPartnerID, LVar3)
            Switch(LVar3)
                CaseOrEq(6)
                CaseOrEq(9)
                    Add(LVar1, -10)
            EndSwitch
        Else
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
        EndIf
        Add(LVar0, 20)
        Add(LVar1, 25)
        Call(WorldItem_ShowFPGain, LVar0, LVar1, LVar2, LVarC)
    EndIf
    Call(TTYD64_GetHealBoxTarget, LVar3)
    IfEq(LVar3, 1)
        Call(GetNpcPos, -4, LVar0, LVar1, LVar2)
        Call(GetCurrentPartnerID, LVar3)
        Switch(LVar3)
            CaseOrEq(6)
            CaseOrEq(9)
                Add(LVar1, -10)
        EndSwitch
    Else
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
    EndIf
    Add(LVar1, 25)
    Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, LVarB)
    IfNe(LVarB, 0)
        Call(TTYD64_GetHealBoxTarget, LVar3)
        IfEq(LVar3, 0)
            Call(WorldItem_RestoreHP, LVarB)
        Else
            Call(TTYD64_ph_ReadPtrByte, (Bytecode) TTYD64_HealingBox_PartnersOrder, LVar3, LVar4)
            Switch(LVar4)
                CaseEq(1)
                    Set(LVar0, (Bytecode) &TTYD64_PartnerHPRecords[1])
                CaseEq(2)
                    Set(LVar0, (Bytecode) &TTYD64_PartnerHPRecords[2])
                CaseEq(3)
                    Set(LVar0, (Bytecode) &TTYD64_PartnerHPRecords[3])
                CaseEq(4)
                    Set(LVar0, (Bytecode) &TTYD64_PartnerHPRecords[4])
                CaseEq(5)
                    Set(LVar0, (Bytecode) &TTYD64_PartnerHPRecords[9])
                CaseEq(6)
                    Set(LVar0, (Bytecode) &TTYD64_PartnerHPRecords[6])
                CaseEq(7)
                    Set(LVar0, (Bytecode) &TTYD64_PartnerHPRecords[7])
                CaseEq(8)
                    Set(LVar0, (Bytecode) &TTYD64_PartnerHPRecords[8])
            EndSwitch
            Call(TTYD64_ph_ReadPtrByte, LVar0, 1, LVar1)
            Call(TTYD64_ph_ReadPtrByte, LVar0, 2, LVar2)
            Add(LVar1, LVarB)
            IfGt(LVar1, LVar2)
                Set(LVar1, LVar2)
            EndIf
            Call(TTYD64_ph_WritePtrByte, LVar0, 1, LVar1)
        EndIf
    EndIf
    IfNe(LVarC, 0)
        Call(WorldItem_RestoreFP, LVarC)
    EndIf
    IfEq(LVarF, 0)
        Call(TTYD64_GetHealBoxTarget, LVar3)
        IfEq(LVar3, 1)
            Wait(10)
            Set(LVar0, 5)
            Set(LVar1, 0)
            Exec(TTYD64_SetPartnerAnimation)
            Call(SetPlayerAnimation, 65586)
            Wait(30)
        Else
            Wait(10)
            Call(SetPlayerAnimation, 65586)
            Wait(30)
        EndIf
    Else
        Wait(30)
    EndIf
    Call(TTYD64_GetHealBoxTarget, LVar3)
    IfEq(LVar3, 1)
        Call(GetNpcPos, -4, LVar0, LVar1, LVar2)
        Call(GetCurrentPartnerID, LVar3)
        Switch(LVar3)
            CaseOrEq(6)
            CaseOrEq(9)
                Add(LVar1, -10)
        EndSwitch
    Else
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
    EndIf
    Call(ShowRecoveryShimmer, LVar0, LVar1, LVar2, LVarB)
    Call(SetPlayerAnimation, 65538)
    Call(TTYD64_GetHealBoxTarget, LVar3)
    IfEq(LVar3, 1)
        Call(EnablePartnerAI)
    EndIf
    Wait(20)
    Call(WorldItem_ConsumeItem)
    Call(DisablePlayerInput, 0)
    Call(WorldItem_UnpauseTime)
    Return
    End
};

EvtScript TTYD64_UseItem_ShowItem = {
    SetGroup(0)
    Call(TTYD64_GetHealBoxTarget, LVar3)
    Call(TTYD64_ph_ReadPtrByte, (Bytecode) TTYD64_HealingBox_PartnersOrder, LVar3, LVar4)
    IfEq(LVar3, 1)
        Set(LVar0, 5)
        Set(LVar1, 0)
        Call(DisablePartnerAI, 0)
        Exec(TTYD64_SetPartnerAnimation)
        Call(GetNpcPos, -4, LVar0, LVar1, LVar2)
    Else
        Call(SetPlayerAnimation, 65567)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
    EndIf
    Add(LVar1, 45)
    Call(MakeItemEntity, LVarA, LVar0, LVar1, LVar2, 1, 0)
    Set(LVarA, LVar0)
    Wait(15)
    IfEq(LVar3, 1)
        Call(GetNpcPos, -4, LVar0, LVar1, LVar2)
    Else
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
    EndIf
    Add(LVar1, 20)
    Call(WorldItem_ShowUseSparkles, LVar0, LVar1, LVar2)
    Call(RemoveItemEntity, LVarA)
    Return
    End
};

EvtScript TTYD64_UseItem_Eat = {
    Call(TTYD64_GetHealBoxTarget, LVar3)
    IfGt(LVar3, 1)
        Return
    EndIf
    Thread
        Loop(4)
            Call(PlaySound, 8341)
            Wait(10)
        EndLoop
    EndThread
    IfEq(LVar3, 0)
        Call(SetPlayerAnimation, 65564)
    Else
        Set(LVar0, 3)
        Set(LVar1, 0)
        Exec(TTYD64_SetPartnerAnimation)
    EndIf
    Wait(45)
    Return
    End
};

EvtScript TTYD64_UseItem_Drink = {
    Call(TTYD64_GetHealBoxTarget, LVar3)
    IfGt(LVar3, 1)
        Return
    EndIf
    Thread
        Loop(4)
            Call(PlaySound, 8341)
            Wait(10)
        EndLoop
    EndThread
    IfEq(LVar3, 0)
        Call(SetPlayerAnimation, 65573)
    Else
        Set(LVar0, 3)
        Set(LVar1, 0)
        Exec(TTYD64_SetPartnerAnimation)
    EndIf
    Wait(45)
    Return
    End
};

EvtScript TTYD64_DoPartnerSpikeContact = {
    Set(LVarA, LVar1)
    Set(LVarB, LVar2)
    Call(SetActorRotation, -127, 0, 0, 0)
    Call(SetActorScale, -127, Float(1.0), Float(1.0), Float(1.0))
    Call(SetActorDispOffset, -127, 0, 0, 0)
    Call(UseBattleCamPreset, 61)
    Call(SetAnimation, 256, -1, LVarA)
    Call(GetGoalPos, 256, LVar0, LVar1, LVar2)
    Sub(LVar0, 60)
    Add(LVar1, 40)
    Call(SetActorJumpGravity, 256, Float(0.099609375))
    Call(SetJumpAnimations, 256, 0, LVarA, LVarA, LVarA)
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Call(JumpToGoal, 256, 5, 0, 0, 0)
    Set(LVar1, LVarA)
    Set(LVar2, 0)
    ExecWait(EVS_Partner_Hit)
    Call(UseBattleCamPreset, 2)
    ChildThread
        Call(SetActorRotationOffset, 256, 0, LVarB, 0)
        Set(LVar0, 0)
        Loop(15)
            Add(LVar0, 48)
            Call(SetActorRotation, 256, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorRotationOffset, 256, 0, 0, 0)
    EndChildThread
    Call(SetGoalToHome, 256)
    Call(GetGoalPos, 256, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, 256, Float(1.400390625))
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Call(JumpToGoal, 256, 15, 0, 1, 0)
    Sub(LVar0, 20)
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Call(JumpToGoal, 256, 10, 0, 1, 0)
    Call(GetHomePos, 256, LVar0, LVar1, LVar2)
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Call(JumpToGoal, 256, 4, 0, 1, 0)
    Return
    End
};

EvtScript TTYD64_DoPartnerBurnContact = {
    Set(LVarA, LVar1)
    Set(LVarB, LVar2)
    Set(LVarC, LVar3)
    Call(SetActorRotation, -127, 0, 0, 0)
    Call(SetActorScale, -127, Float(1.0), Float(1.0), Float(1.0))
    Call(SetActorDispOffset, -127, 0, 0, 0)
    Call(UseBattleCamPreset, 62)
    Call(SetAnimation, 256, -1, LVarA)
    Call(GetGoalPos, 256, LVar0, LVar1, LVar2)
    Sub(LVar0, 60)
    Add(LVar1, 40)
    Call(SetActorJumpGravity, 256, Float(0.099609375))
    Call(SetJumpAnimations, 256, 0, LVarA, LVarA, LVarA)
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Call(JumpToGoal, 256, 5, 0, 0, 0)
    Set(LVar1, LVarA)
    Set(LVar2, LVarC)
    ExecWait(EVS_Partner_BurnHit)
    Call(UseBattleCamPreset, 2)
    ChildThread
        Call(SetActorRotationOffset, 256, 0, LVarB, 0)
        Set(LVar0, 0)
        Loop(15)
            Add(LVar0, 48)
            Call(SetActorRotation, 256, 0, 0, LVar0)
            Wait(1)
        EndLoop
        Call(SetActorRotationOffset, 256, 0, 0, 0)
    EndChildThread
    Call(SetGoalToHome, 256)
    Call(GetGoalPos, 256, LVar0, LVar1, LVar2)
    Add(LVar0, 30)
    Set(LVar1, 0)
    Call(SetActorJumpGravity, 256, Float(1.400390625))
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Call(JumpToGoal, 256, 15, 0, 1, 0)
    Sub(LVar0, 20)
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Call(JumpToGoal, 256, 10, 0, 1, 0)
    Call(GetHomePos, 256, LVar0, LVar1, LVar2)
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Call(JumpToGoal, 256, 4, 0, 1, 0)
    Return
    End
};

EvtScript TTYD64_PartnerDies = {
    Call(TTYD64_ClearPartnerExtraData_API)
    Call(TTYD64_ClearPartnerStatusData_API)
    Call(SetAnimation, -127, LVar0, LVar1)
    Wait(20)
    Call(GetActorPos, -127, LVar0, LVar1, LVar2)
    IfNe(LVar1, 0)
        Call(GetCurrentPartnerID, LVar0)
        Switch(LVar0)
            CaseEq(4)
                SetConst(LVar1, 786445)
            CaseEq(9)
                SetConst(LVar1, 851989)
            CaseEq(6)
                SetConst(LVar1, 917516)
            CaseEq(8)
                SetConst(LVar1, 1048586)
        EndSwitch
        Set(LVarA, LVar1)
        Call(SetAnimation, 256, -1, LVarA)
        Call(GetActorPos, 256, LVar0, LVar1, LVar2)
        Set(LVar1, 3)
        Call(SetActorJumpGravity, 256, Float(1.0))
        Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
        Call(JumpToGoal, 256, 10, 0, 1, 0)
        Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
        Call(JumpToGoal, 256, 8, 0, 1, 0)
        Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
        Call(JumpToGoal, 256, 5, 0, 1, 0)
        Wait(8)
        Call(GetActorPos, 256, LVar0, LVar1, LVar2)
        Call(PlayEffect_impl, 6, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Else
        Wait(20)
    EndIf
    Call(TTYD64_GetMarioPos, LVar0)
    IfEq(LVar0, 0)
        Call(FindItem, 149, LVar0)
        IfEq(LVar0, -1)
            ExecWait(TTYD64_Script_SwapHeroesPositions_MoveMarioUpfront)
        EndIf
    EndIf
    Call(SetBattleFlagBits2, BS_FLAGS2_PARTNER_TURN_USED, 1)
    Call(SetBattleFlagBits2, BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER, 0)
    Set(LVar0, 8)
    Exec(TTYD64_SetPartnerAnimation_Battle)
    Wait(10)
    Thread
        Wait(5)
        Call(PlaySound, 1019)
    EndThread
    Call(MakeLerp, 0, 86, 10, 12)
    Loop(0)
        Call(UpdateLerp)
        Call(SetActorRotation, -127, LVar0, 0, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(GetActorPos, -127, LVar0, LVar1, LVar2)
    Call(SetHomePos, -127, LVar0, LVar1, LVar2)
    Call(PlayEffect_impl, 46, 0, LVar0, LVar1, LVar2, 0, 10, 0, 0, 0, 0, 0, 0, 0)
    Wait(15)
    Call(FindItem, 149, LVar0)
    IfNe(LVar0, -1)
        ExecWait(TTYD64_UseLifeShroom_Actor)
    EndIf
    Return
    End
};

EvtScript TTYD64_UseLifeShroom_Actor = {
    Call(UseIdleAnimation, -127, 0)
    Call(LifeShroomShroudWorld)
    Call(GetActorPos, -127, LVar0, LVar1, LVar2)
    Call(MakeItemEntity, 149, LVar0, LVar1, LVar2, 1, 0)
    Set(LVarA, LVar0)
    Call(GetActorPos, -127, LVar0, LVar1, LVar2)
    AddF(LVar1, Float(30.0))
    Call(SetItemPos, LVarA, LVar0, LVar1, LVar2)
    Wait(1)
    Set(LVar3, LVar0)
    Set(LVar4, LVar1)
    Set(LVar5, LVar2)
    Call(SetItemAsLifeShroom)
    Call(GetOwnerTarget, LVar0, 0)
    IfLt(LVar0, 512)
        Call(GiveRefund)
        IfGt(LVar0, 0)
            Wait(LVar0)
            Wait(15)
            Call(GiveRefundCleanup)
        EndIf
    EndIf
    Call(PlaySoundAtActor, -127, 882)
    Add(LVar4, 15)
    Call(PlayEffect_impl, 107, 3, LVar3, LVar4, LVar5, Float(1.0), 0, 0, 0, 0, 0, 0, 0, 0)
    Set(LVar0, LVarF)
    Loop(3)
        Call(SetItemFlags, LVarA, 64, 1)
        Wait(2)
        Call(SetItemFlags, LVarA, 64, 0)
        Wait(6)
    EndLoop
    Call(RemoveEffect, LVar0)
    Call(RemoveItemEntity, LVarA)
    Call(PlaySoundAtActor, -127, 8277)
    Call(PlayEffect_impl, 34, 1, LVar3, LVar4, LVar5, 70, 70, 10, 20, 0, 0, 0, 0, 0)
    Wait(20)
    Call(PlaySoundAtActor, -127, 883)
    Call(GetActorPos, -127, LVar0, LVar1, LVar2)
    Call(PlayEffect_impl, 34, 2, LVar0, LVar1, LVar2, 50, 20, 32, 30, 0, 0, 0, 0, 0)
    Wait(25)
    Call(PlayEffect_impl, 34, 2, LVar0, LVar1, LVar2, 30, 50, 32, 30, 0, 0, 0, 0, 0)
    ChildThread
        Call(SetActorDispOffset, -127, 1, 0, 0)
        Wait(4)
        Call(SetActorDispOffset, -127, -1, 0, 0)
        Wait(4)
        Call(SetActorDispOffset, -127, 1, 0, 0)
        Wait(2)
        Call(SetActorDispOffset, -127, -1, 0, 0)
        Wait(2)
        Loop(7)
            Call(SetActorDispOffset, -127, 1, 0, 0)
            Wait(1)
            Call(SetActorDispOffset, -127, -1, 0, 0)
            Wait(1)
        EndLoop
    EndChildThread
    Wait(26)
    ChildThread
        Call(LifeShroomRevealWorld)
    EndChildThread
    Call(PlaySoundAtActor, -127, 884)
    Call(SetActorRotation, -127, 0, 0, 0)
    Call(SetActorYaw, -127, 0)
    Call(GetOwnerID, LVar3)
    IfEq(LVar3, 256)
        Call(RemoveItem, 149, 0)
    EndIf
    Call(GetActorPos, -127, LVar0, LVar1, LVar2)
    Add(LVar1, 25)
    Call(SpawnRecoverHeartFX, LVar0, LVar1, LVar2, 10)
    Call(FreezeBattleCam, 0)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 15)
    ChildThread
        Wait(20)
        Loop(5)
            Wait(2)
            Call(GetActorPos, -127, LVar0, LVar1, LVar2)
            Add(LVar1, 5)
            Call(PlayEffect_impl, 114, 2, LVar0, LVar1, LVar2, 20, 20, Float(1.0), 10, 50, 0, 0, 0, 0)
        EndLoop
    EndChildThread
    Call(PlaySoundAtActor, -127, 352)
    Call(SetActorJumpGravity, -127, Float(1.0))
    Call(SetActorSpeed, -127, Float(1.0))
    Call(GetOwnerID, LVar3)
    IfEq(LVar3, 256)
        Call(SetBattleFlagBits2, 4, 0)
        Call(SetBattleFlagBits2, 16, 1)
        Call(TTYD64_Heal_PlayerTeam, -127, 10)
    Else
        Call(TTYD64_HealActor, -127, 10)
    EndIf
    Call(GetActorPos, -127, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetGoalPos, -127, LVar0, LVar1, LVar2)
    Call(GetActorPos, -127, LVar0, LVar1, LVar2)
    Call(GetOwnerID, LVar3)
    IfEq(LVar3, 256)
        Call(GetCurrentPartnerID, LVar3)
        Switch(LVar3)
            CaseEq(4)
                Set(LVar1, 4)
            CaseEq(9)
                Set(LVar1, 9)
            CaseEq(6)
                Set(LVar1, 11)
            CaseEq(8)
                Set(LVar1, 4)
        EndSwitch
        Call(GetPlayerHP, LVar3)
        IfEq(LVar3, 0)
            Thread
                Call(TTYD64_Heal_PlayerTeam, 0, 10)
                Call(UseIdleAnimation, 0, 0)
                Call(SetActorJumpGravity, 0, Float(1.0))
                Call(SetActorSpeed, 0, Float(1.0))
                Call(GetActorPos, 0, LVar0, LVar1, LVar2)
                Set(LVar1, 0)
                Call(SetJumpAnimations, 0, 0, 65543, 65544, 65545)
                Set(LVar3, LVar1)
                Add(LVar3, 25)
                Call(SpawnRecoverHeartFX, LVar0, LVar3, LVar2, 10)
                Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
                Call(PlayerHopToGoal, 20, 0, 0)
                Call(SetAnimation, 0, 0, 65545)
                Call(SetActorSpeed, 0, Float(1.0))
                Call(SetActorJumpGravity, 0, Float(0.7998046875))
                Call(SetActorDispOffset, 0, 0, 0, 0)
                Call(SetActorRotationOffset, 0, 0, 0, 0)
                Call(SetActorRotation, 0, 0, 0, 0)
                Call(SetAnimation, 0, 0, 65538)
                Call(UseIdleAnimation, 0, 1)
            EndThread
            ChildThread
                Loop(5)
                    Wait(2)
                    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
                    Add(LVar1, 5)
                    Call(PlayEffect_impl, 114, 2, LVar0, LVar1, LVar2, 20, 20, Float(1.0), 10, 50, 0, 0, 0, 0)
                EndLoop
            EndChildThread
        EndIf
    EndIf
    Call(SetGoalPos, -127, LVar0, LVar1, LVar2)
    Call(GetOwnerID, LVar3)
    IfEq(LVar3, 256)
        Set(LVar0, 9)
        Exec(TTYD64_SetPartnerAnimation_Battle)
    EndIf
    Call(SetActorJumpGravity, -127, Float(0.7998046875))
    Call(SetActorDispOffset, -127, 0, 0, 0)
    Call(JumpToGoal, -127, 20, 0, 0, 1)
    Call(GetOwnerID, LVar3)
    IfEq(LVar3, 256)
        Set(LVar0, 0)
        Exec(TTYD64_SetPartnerAnimation_Battle)
    EndIf
    Call(SetActorRotationOffset, -127, 0, 0, 0)
    Call(SetActorDispOffset, -127, 0, 0, 0)
    Call(SetActorRotation, -127, 0, 0, 0)
    Wait(5)
    Call(UseIdleAnimation, -127, 1)
    Wait(20)
    Return
    End
};

EvtScript TTYD64_ph_UseLifeShroom = {
    Call(UseIdleAnimation, 0, 0)
    ChildThread
        Call(func_80261388)
        IfEq(LVar0, 1)
            Call(DispatchEvent, 256, 64)
            Call(SetActorFlagBits, 256, 4, 1)
            Set(LVar0, 255)
            Loop(10)
                Sub(LVar0, 25)
                IfLt(LVar0, 0)
                    Set(LVar0, 0)
                EndIf
                Call(SetPartAlpha, 256, -1, LVar0)
                Wait(1)
            EndLoop
            Call(SetPartAlpha, 256, -1, 0)
        EndIf
    EndChildThread
    Call(LifeShroomShroudWorld)
    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
    Call(MakeItemEntity, 149, LVar0, LVar1, LVar2, 1, 0)
    Set(LVarA, LVar0)
    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
    Set(LVar3, 30)
    Set(LVar4, 16)
    Loop(LVar3)
        Add(LVar4, 8)
        IfGt(LVar4, 255)
            Set(LVar4, 255)
        EndIf
        AddF(LVar1, Float(1.0))
        Call(SetItemPos, LVarA, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Set(LVar3, LVar0)
    Set(LVar4, LVar1)
    Set(LVar5, LVar2)
    Call(SetItemAsLifeShroom)
    Call(GiveRefund)
    IfGt(LVar0, 0)
        Wait(LVar0)
        Wait(15)
        Call(GiveRefundCleanup)
    EndIf
    Call(PlaySoundAtActor, 0, 882)
    Add(LVar4, 15)
    Call(PlayEffect_impl, 107, 3, LVar3, LVar4, LVar5, Float(1.0), 0, 0, 0, 0, 0, 0, 0, 0)
    Set(LVar0, LVarF)
    Loop(4)
        Call(SetItemFlags, LVarA, 64, 1)
        Wait(2)
        Call(SetItemFlags, LVarA, 64, 0)
        Wait(8)
    EndLoop
    Call(RemoveEffect, LVar0)
    Call(RemoveItemEntity, LVarA)
    Call(PlaySoundAtActor, 0, 8277)
    Call(PlayEffect_impl, 34, 1, LVar3, LVar4, LVar5, 70, 70, 10, 20, 0, 0, 0, 0, 0)
    Wait(20)
    Call(PlaySoundAtActor, 0, 883)
    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
    Call(PlayEffect_impl, 34, 2, LVar0, LVar1, LVar2, 50, 20, 32, 30, 0, 0, 0, 0, 0)
    Wait(40)
    Call(PlayEffect_impl, 34, 2, LVar0, LVar1, LVar2, 30, 50, 32, 30, 0, 0, 0, 0, 0)
    ChildThread
        Loop(3)
            Call(SetActorDispOffset, 0, 1, 0, 0)
            Wait(4)
            Call(SetActorDispOffset, 0, -1, 0, 0)
            Wait(4)
        EndLoop
        Loop(3)
            Call(SetActorDispOffset, 0, 1, 0, 0)
            Wait(2)
            Call(SetActorDispOffset, 0, -1, 0, 0)
            Wait(2)
        EndLoop
        Loop(7)
            Call(SetActorDispOffset, 0, 1, 0, 0)
            Wait(1)
            Call(SetActorDispOffset, 0, -1, 0, 0)
            Wait(1)
        EndLoop
    EndChildThread
    Wait(50)
    ChildThread
        Call(LifeShroomRevealWorld)
    EndChildThread
    Call(PlaySoundAtActor, 0, 884)
    Call(SetActorRotation, 0, 0, 0, 0)
    Call(SetActorYaw, -127, 0)
    Call(ConsumeLifeShroom)
    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
    Add(LVar1, 25)
    Call(PlayEffect_impl, 64, 0, LVar0, LVar1, LVar2, LVar3, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(FreezeBattleCam, 0)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 15)
    ChildThread
        Call(func_80261388)
        IfEq(LVar0, 1)
            Call(SetActorFlagBits, 256, 4, 0)
            Set(LVar0, 0)
            Loop(10)
                Add(LVar0, 25)
                IfGt(LVar0, 255)
                    Set(LVar0, 255)
                EndIf
                Call(SetPartAlpha, 256, -1, LVar0)
                Wait(1)
            EndLoop
            Call(DispatchEvent, 256, 65)
            Call(SetPartAlpha, 256, -1, 255)
        EndIf
    EndChildThread
    ChildThread
        Loop(5)
            Wait(2)
            Call(GetActorPos, 0, LVar0, LVar1, LVar2)
            Call(PlayEffect_impl, 114, 2, LVar0, LVar1, LVar2, 20, 20, Float(1.0), 10, 50, 0, 0, 0, 0)
        EndLoop
    EndChildThread
    Call(PlaySoundAtActor, 0, 352)
    Call(SetActorJumpGravity, 0, Float(1.0))
    Call(SetActorSpeed, 0, Float(1.0))
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfEq(LVar0, 0)
        Call(SetBattleFlagBits2, 4, 0)
        Call(SetBattleFlagBits2, 16, 1)
        Call(UseIdleAnimation, 256, 0)
        Call(TTYD64_Heal_PlayerTeam, 256, 10)
        Thread
            Call(UseIdleAnimation, 256, 0)
            Call(GetActorPos, 256, LVar0, LVar1, LVar2)
            Set(LVar3, LVar1)
            Add(LVar3, 25)
            Call(SpawnRecoverHeartFX, LVar0, LVar3, LVar2, 10)
            Call(GetCurrentPartnerID, LVar3)
            Switch(LVar3)
                CaseEq(4)
                    Set(LVar1, 4)
                CaseEq(9)
                    Set(LVar1, 9)
                CaseEq(6)
                    Set(LVar1, 11)
                CaseEq(8)
                    Set(LVar1, 4)
            EndSwitch
            Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
            Set(LVar0, 9)
            Exec(TTYD64_SetPartnerAnimation_Battle)
            Call(SetActorSpeed, 0, Float(1.0))
            Call(SetActorJumpGravity, 256, Float(0.7998046875))
            Call(SetActorDispOffset, 256, 0, 0, 0)
            Call(JumpToGoal, 256, 20, 0, 0, 1)
            Call(GetOwnerID, LVar3)
            IfEq(LVar3, 256)
                Set(LVar0, 0)
                Exec(TTYD64_SetPartnerAnimation_Battle)
            EndIf
            Call(SetActorDispOffset, 256, 0, 0, 0)
            Call(SetActorRotationOffset, 256, 0, 0, 0)
            Call(SetActorRotation, 256, 0, 0, 0)
            Call(UseIdleAnimation, 256, 1)
        EndThread
        ChildThread
            Loop(5)
                Wait(2)
                Call(GetActorPos, 256, LVar0, LVar1, LVar2)
                Add(LVar1, 5)
                Call(PlayEffect_impl, 114, 2, LVar0, LVar1, LVar2, 20, 20, Float(1.0), 10, 50, 0, 0, 0, 0)
            EndLoop
        EndChildThread
    EndIf
    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
    Set(LVar1, 0)
    Call(SetJumpAnimations, 0, 0, 65543, 65544, 65545)
    Call(SetGoalPos, 0, LVar0, LVar1, LVar2)
    Call(PlayerHopToGoal, 20, 0, 0)
    Call(SetAnimation, 0, 0, 65545)
    Wait(4)
    Call(SetAnimation, 0, 0, 65538)
    Wait(10)
    Call(UseIdleAnimation, 0, 1)
    Call(RestorePreDefeatState)
    Return
    End
};

EvtScript TTYD64_Script_SwapHeroesPositions_MoveMarioUpfront = {
    Call(TTYD64_SetMarioInFront, 1)
    Set(LVar0, -1027735552)
    Call(TTYD64_WriteField, TTYD64_F_GBATTLESTATUS_PLAYERACTOR_138_4U, LVar0)
    Call(TTYD64_WriteField, TTYD64_F_GBATTLESTATUS_PLAYERACTOR_140_4U, 0)
    Call(GetActorPos, 0, LVar0, LVar1, LVar2)
    Add(LVar0, 35)
    Call(SetGoalPos, 0, LVar0, LVar1, 0)
    Call(GetActorPos, 256, LVar0, LVar1, LVar2)
    Add(LVar0, -35)
    Call(SetGoalPos, 256, LVar0, LVar1, -10)
    Exec(TTYD64_Script_SHP_MMU_MovePartner)
    Thread
        Call(MakeLerp, 180, 0, 4, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(SetActorRotation, 0, 0, LVar0, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Call(RunToGoal, 0, 4, 0)
    Return
    End
};

EvtScript TTYD64_Script_SHP_MMU_MovePartner = {
    Thread
        Call(MakeLerp, 180, 0, 4, 0)
        Loop(0)
            Call(UpdateLerp)
            Call(SetActorRotation, 256, 0, LVar0, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Call(RunToGoal, 256, 4, 0)
    Return
    End
};

EvtScript TTYD64_PartnerRunAway = {
    Call(TTYD64_GetPartnerHP_API, LVar0)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(UseIdleAnimation, 256, 0)
    Call(SetActorYaw, -127, 180)
    Call(SetAnimation, -127, LVar0, LVar1)
    Wait(10)
    Call(GetActorPos, -127, LVar0, LVar1, LVar2)
    Call(SetActorJumpGravity, -127, Float(1.2001953125))
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Call(JumpToGoal, 256, 10, 0, 1, 0)
    Call(SetGoalPos, 256, LVar0, LVar1, LVar2)
    Call(JumpToGoal, 256, 10, 0, 1, 0)
    Wait(5)
    Call(SetActorSpeed, -127, Float(12.0))
    Call(SetGoalPos, 256, -250, 0, 0)
    Call(RunToGoal, 256, 0, 0)
    Call(UseIdleAnimation, 256, 1)
    Return
    End
};

EvtScript TTYD64_BattleScript_EatItem = {
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetStatusFlags, LVar3, LVar0)
    IfFlag(LVar0, 3526656)
        Return
    EndIf
    IfEq(LVar3, 0)
        Call(TTYD64_StashTurnUsed, ACTOR_CLASS_PLAYER, LVar0)
        Thread
            Loop(4)
                Call(PlaySoundAtActor, 0, 8341)
                Wait(10)
            EndLoop
        EndThread
        Call(GetOwnerID, LVar4)
        IfNe(LVar3, LVar4)
            Call(UseIdleAnimation, LVar3, 0)
        EndIf
        Call(SetAnimation, 0, 0, 65564)
        Wait(45)
        Call(GetOwnerID, LVar4)
        IfNe(LVar3, LVar4)
            Call(UseIdleAnimation, LVar3, 1)
        EndIf
    Else
        IfEq(LVar3, 256)
            Call(TTYD64_StashTurnUsed, ACTOR_CLASS_PARTNER, LVar0)
        EndIf
        Wait(5)
    EndIf
    Return
    End
};

EvtScript TTYD64_BattleScript_DrinkItem = {
    Call(GetOwnerTarget, LVar3, 0)
    Call(GetStatusFlags, LVar3, LVar0)
    IfFlag(LVar0, 3526656)
        Return
    EndIf
    IfEq(LVar3, 0)
        Call(TTYD64_StashTurnUsed, ACTOR_CLASS_PLAYER, LVar0)
        Thread
            Loop(4)
                Call(PlaySoundAtActor, 0, 8341)
                Wait(10)
            EndLoop
        EndThread
        Call(GetOwnerID, LVar4)
        IfNe(LVar3, LVar4)
            Call(UseIdleAnimation, LVar3, 0)
        EndIf
        Call(SetAnimation, 0, 0, 65573)
        Wait(45)
        Call(GetOwnerID, LVar4)
        IfNe(LVar3, LVar4)
            Call(UseIdleAnimation, LVar3, 1)
        EndIf
    Else
        IfEq(LVar3, 256)
            Call(TTYD64_StashTurnUsed, ACTOR_CLASS_PARTNER, LVar0)
        EndIf
        Wait(5)
    EndIf
    Return
    End
};

EvtScript TTYD64_BattleScript_GoBackToHome_HealingItem = {
    ExecWait(TTYD64_Items_RestoreHeroeTurn)
    Call(GetOwnerTarget, LVar7, 0)
    Call(GetOwnerID, LVar4)
    IfNe(LVar7, LVar4)
        Call(UseIdleAnimation, LVar7, 1)
    EndIf
    Call(GetOwnerID, LVar7)
    Call(UseIdleAnimation, LVar7, 0)
    Call(SetGoalToHome, LVar7)
    Call(SetActorSpeed, LVar7, Float(8.0))
    Switch(LVar7)
        CaseEq(0)
            Call(SetAnimation, LVar7, 0, 65541)
            Call(PlayerRunToGoal, 0)
            Call(SetAnimation, LVar7, 0, 65538)
        CaseEq(256)
            Set(LVar0, 2)
            Exec(TTYD64_SetPartnerAnimation_Battle)
            Call(RunToGoal, LVar7, 0, 0)
            Set(LVar0, 0)
            Exec(TTYD64_SetPartnerAnimation_Battle)
        CaseDefault
            Call(RunToGoal, LVar7, 0, 0)
    EndSwitch
    Call(UseBattleCamPreset, 2)
    Call(UseIdleAnimation, LVar7, 1)
    Return
    End
};

EvtScript TTYD64_BattleScript_GoBackToHome_Item = {
    ExecWait(TTYD64_Items_RestoreHeroeTurn)
    Call(GetOwnerID, LVar7)
    Call(UseIdleAnimation, LVar7, 0)
    Call(SetGoalToHome, LVar7)
    Call(SetActorSpeed, LVar7, Float(8.0))
    Switch(LVar7)
        CaseEq(0)
            Call(SetAnimation, LVar7, 0, 65541)
            Call(PlayerRunToGoal, 0)
            Call(SetAnimation, LVar7, 0, 65538)
        CaseEq(256)
            Set(LVar0, 2)
            Exec(TTYD64_SetPartnerAnimation_Battle)
            Call(RunToGoal, LVar7, 0, 0)
            Set(LVar0, 0)
            Exec(TTYD64_SetPartnerAnimation_Battle)
        CaseDefault
            Call(RunToGoal, LVar7, 0, 0)
    EndSwitch
    Call(UseBattleCamPreset, 2)
    Call(UseIdleAnimation, LVar7, 1)
    Return
    End
};

EvtScript TTYD64_Items_RestoreHeroeTurn = {
    Call(TTYD64_RestoreTurnUsed, ACTOR_CLASS_PLAYER, LVar0)
    Call(TTYD64_RestoreTurnUsed, ACTOR_CLASS_PARTNER, LVar0)
    Return
    End
};

EvtScript TTYD64_SetPartnerAnimation_Battle = {
    Call(GetCurrentPartnerID, LVar2)
    Switch(LVar2)
        CaseEq(1)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, 256, 0, 589825)
                CaseEq(1)
                    Call(SetAnimation, 256, 0, 589826)
                CaseEq(2)
                    Call(SetAnimation, 256, 0, 589827)
                CaseEq(3)
                    Call(SetAnimation, 256, 0, 589839)
                CaseEq(4)
                    Call(SetAnimation, 256, 0, 589844)
                CaseEq(5)
                    Call(SetAnimation, 256, 0, 589840)
                CaseEq(6)
                    Call(SetAnimation, 256, 0, 589838)
                CaseEq(7)
                    Call(SetAnimation, 256, 0, 589828)
                CaseEq(8)
                    Call(SetAnimation, 256, 0, 589824)
                CaseEq(9)
                    Call(SetAnimation, 256, 0, 589828)
            EndSwitch
        CaseEq(2)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, 256, 0, 655364)
                CaseEq(1)
                    Call(SetAnimation, 256, 0, 655365)
                CaseEq(2)
                    Call(SetAnimation, 256, 0, 655366)
                CaseEq(3)
                    Call(SetAnimation, 256, 0, 655380)
                CaseEq(4)
                    Call(SetAnimation, 256, 0, 655377)
                CaseEq(5)
                    Call(SetAnimation, 256, 0, 655382)
                CaseEq(6)
                    Call(SetAnimation, 256, 0, 655376)
                CaseEq(7)
                    Call(SetAnimation, 256, 0, 655389)
                CaseEq(8)
                    Call(SetAnimation, 256, 0, 655360)
                CaseEq(9)
                    Call(SetAnimation, 256, 0, 655367)
            EndSwitch
        CaseEq(3)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, 256, 0, 720900)
                CaseEq(1)
                    Call(SetAnimation, 256, 0, 720902)
                CaseEq(2)
                    Call(SetAnimation, 256, 0, 720904)
                CaseEq(3)
                    Call(SetAnimation, 256, 0, 720919)
                CaseEq(4)
                    Call(SetAnimation, 256, 0, 720914)
                CaseEq(5)
                    Call(SetAnimation, 256, 0, 720920)
                CaseEq(6)
                    Call(SetAnimation, 256, 0, 720910)
                CaseEq(7)
                    Call(SetAnimation, 256, 0, 720906)
                CaseEq(8)
                    Call(SetAnimation, 256, 0, 720896)
                CaseEq(9)
                    Call(SetAnimation, 256, 0, 720906)
            EndSwitch
        CaseEq(4)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, 256, 0, 786433)
                CaseEq(1)
                    Call(SetAnimation, 256, 0, 786434)
                CaseEq(2)
                    Call(SetAnimation, 256, 0, 786435)
                CaseEq(3)
                    Call(SetAnimation, 256, 0, 786450)
                CaseEq(4)
                    Call(SetAnimation, 256, 0, 786446)
                CaseEq(5)
                    Call(SetAnimation, 256, 0, 786451)
                CaseEq(6)
                    Call(SetAnimation, 256, 0, 786444)
                CaseEq(7)
                    Call(SetAnimation, 256, 0, 786458)
                CaseEq(8)
                    Call(SetAnimation, 256, 0, 786432)
                CaseEq(9)
                    Call(SetAnimation, 256, 0, 786433)
            EndSwitch
        CaseEq(9)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, 256, 0, 851969)
                CaseEq(1)
                    Call(SetAnimation, 256, 0, 851970)
                CaseEq(2)
                    Call(SetAnimation, 256, 0, 851971)
                CaseEq(3)
                    Call(SetAnimation, 256, 0, 851972)
                CaseEq(4)
                    Call(SetAnimation, 256, 0, 851989)
                CaseEq(5)
                    Call(SetAnimation, 256, 0, 851984)
                CaseEq(6)
                    Call(SetAnimation, 256, 0, 851995)
                CaseEq(7)
                    Call(SetAnimation, 256, 0, 851984)
                CaseEq(8)
                    Call(SetAnimation, 256, 0, 851968)
                CaseEq(9)
                    Call(SetAnimation, 256, 0, 851969)
            EndSwitch
        CaseEq(6)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, 256, 0, 917505)
                CaseEq(1)
                    Call(SetAnimation, 256, 0, 917506)
                CaseEq(2)
                    Call(SetAnimation, 256, 0, 917507)
                CaseEq(3)
                    Call(SetAnimation, 256, 0, 917508)
                CaseEq(4)
                    Call(SetAnimation, 256, 0, 917516)
                CaseEq(5)
                    Call(SetAnimation, 256, 0, 917512)
                CaseEq(6)
                    Call(SetAnimation, 256, 0, 917523)
                CaseEq(7)
                    Call(SetAnimation, 256, 0, 917515)
                CaseEq(8)
                    Call(SetAnimation, 256, 0, 917504)
                CaseEq(9)
                    Call(SetAnimation, 256, 0, 917505)
            EndSwitch
        CaseEq(7)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, 256, 0, 983041)
                CaseEq(1)
                    Call(SetAnimation, 256, 0, 983042)
                CaseEq(2)
                    Call(SetAnimation, 256, 0, 983043)
                CaseEq(3)
                    Call(SetAnimation, 256, 0, 983040)
                CaseEq(4)
                    Call(SetAnimation, 256, 0, 983056)
                CaseEq(5)
                    Call(SetAnimation, 256, 0, 983057)
                CaseEq(6)
                    Call(SetAnimation, 256, 0, 983060)
                CaseEq(7)
                    Call(SetAnimation, 256, 0, 983058)
                CaseEq(8)
                    Call(SetAnimation, 256, 0, 983040)
                CaseEq(9)
                    Call(SetAnimation, 256, 0, 983045)
            EndSwitch
        CaseEq(8)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, 256, 0, 1048577)
                CaseEq(1)
                    Call(SetAnimation, 256, 0, 1048578)
                CaseEq(2)
                    Call(SetAnimation, 256, 0, 1048579)
                CaseEq(3)
                    Call(SetAnimation, 256, 0, 1048576)
                CaseEq(4)
                    Call(SetAnimation, 256, 0, 1048584)
                CaseEq(5)
                    Call(SetAnimation, 256, 0, 1048583)
                CaseEq(6)
                    Call(SetAnimation, 256, 0, 1048602)
                CaseEq(7)
                    Call(SetAnimation, 256, 0, 1048600)
                CaseEq(8)
                    Call(SetAnimation, 256, 0, 1048576)
                CaseEq(9)
                    Call(SetAnimation, 256, 0, 1048577)
            EndSwitch
    EndSwitch
    Return
    End
};

EvtScript TTYD64_ph_EVS_World_UseItem = {
    Jump(TTYD64_UseItem_Init)
    Return
    End
};

EvtScript TTYD64_ph_EVS_Partner_SpikeContact = {
    ExecWait(TTYD64_DoPartnerSpikeContact)
    Return
    End
};

EvtScript TTYD64_ph_EVS_Partner_BurnContact = {
    ExecWait(TTYD64_DoPartnerBurnContact)
    Return
    End
};

EvtScript TTYD64_ph_EVS_UseLifeShroom = {
    ExecWait(TTYD64_ph_UseLifeShroom)
    Return
    End
};

EvtScript TTYD64_ph_EVS_Partner_RunAway = {
    ExecWait(TTYD64_PartnerRunAway)
    Return
    End
};
// clang-format on
