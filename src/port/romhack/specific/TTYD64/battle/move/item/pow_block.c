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

extern EvtScript battle_item_pow_block_EVS_UseItem;
API_CALLABLE(TTYD64_ApplyShrinkFromOwner);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetItemPower);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(ItemCheckHit);
API_CALLABLE(ItemDamageEnemy);
API_CALLABLE(JumpToGoal);
API_CALLABLE(MakeEntity);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerHopToGoal);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorJumpGravity);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetDamageSource);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetJumpAnimations);
API_CALLABLE(SetTargetActor);
API_CALLABLE(ShakeCam);
API_CALLABLE(StartRumble);
API_CALLABLE(TTYD64_Player_Refund);
API_CALLABLE(TTYD64_Player_Refund_FreeIcons);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(battle_item_pow_block_AdjustPOWBlockEntityScale);
API_CALLABLE(battle_item_pow_block_DeletePOWBlockEntity);
API_CALLABLE(battle_item_pow_block_ForceTriggerPOWBlockEntity);
EvtScript TTYD64_battle_item_pow_block_EVS_802A1000;
EvtScript TTYD64_battle_item_pow_block_EVS_UseItem;
EvtScript TTYD64_battle_item_pow_block_EVS_802A1978;

// clang-format off
EvtScript TTYD64_battle_item_pow_block_EVS_802A1000 = {
    Call(GetOwnerID, LVar7)
    IfEq(LVar1, 0)
        Call(UseBattleCamPreset, 69)
        Wait(10)
        Call(PlaySoundAtActor, LVar7, 8333)
        Switch(LVar7)
            CaseEq(0)
                Call(SetAnimation, LVar7, 0, 65567)
            CaseEq(256)
                Set(LVar0, 7)
                Exec(TTYD64_SetPartnerAnimation_Battle)
            CaseDefault
        EndSwitch
        Call(GetActorPos, LVar7, LVar0, LVar1, LVar2)
        Add(LVar0, 10)
        Call(SetActorSpeed, LVar7, Float(4.0))
        Call(SetGoalPos, LVar7, LVar0, LVar1, LVar2)
        Switch(LVar7)
            CaseEq(0)
                Call(PlayerRunToGoal, 0)
            CaseEq(256)
                Call(RunToGoal, LVar7, 0, false)
        EndSwitch
        Add(LVar1, 45)
        Set(LVar3, LVar1)
        Add(LVar3, 10)
        Add(LVar3, 2)
        Call(PlayEffect_impl, 51, 1, LVar0, LVar3, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
        Call(MakeItemEntity, LVarA, LVar0, LVar1, LVar2, 1, 0)
        Set(LVarA, LVar0)
        Call(TTYD64_Player_Refund)
        Wait(LVar0)
        Wait(15)
        Call(TTYD64_Player_Refund_FreeIcons)
        Call(RemoveItemEntity, LVarA)
    Else
        Call(UseBattleCamPreset, 15)
        Call(BattleCamTargetActor, ACTOR_SELF)
        Call(MoveBattleCamOver, 15)
        Call(PlaySoundAtActor, LVar7, 8333)
        Switch(LVar7)
            CaseEq(0)
                Call(SetAnimation, LVar7, 0, 65567)
            CaseEq(256)
                Set(LVar0, 7)
                Exec(TTYD64_SetPartnerAnimation_Battle)
            CaseDefault
        EndSwitch
        Wait(4)
        Call(GetActorPos, LVar7, LVar0, LVar1, LVar2)
        IfGe(LVar7, 512)
            Call(GetActorFlags, LVar7, LVar3)
            IfFlag(LVar3, 2048)
                Call(GetActorSize, LVar7, 0, LVar3)
                Sub(LVar1, LVar3)
            EndIf
        EndIf
        Add(LVar1, 45)
        Set(LVar3, LVar1)
        Add(LVar3, 10)
        Add(LVar3, 2)
        Call(PlayEffect_impl, 51, 1, LVar0, LVar3, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
        Call(MakeItemEntity, LVarA, LVar0, LVar1, LVar2, 1, 0)
        Set(LVarA, LVar0)
        Wait(15)
        Call(RemoveItemEntity, LVarA)
    EndIf
    Call(GetOwnerID, LVar7)
    IfEq(LVar7, 256)
        Set(LVar0, 0)
        Exec(TTYD64_SetPartnerAnimation_Battle)
    EndIf
    Return
    End
};

EvtScript TTYD64_battle_item_pow_block_EVS_UseItem = {
    Jump(TTYD64_battle_item_pow_block_EVS_802A1978)
    Return
    End
};

EvtScript TTYD64_battle_item_pow_block_EVS_802A1978 = {
    SetConst(LVarA, 144)
    ExecWait(TTYD64_battle_item_pow_block_EVS_802A1000)
    Wait(10)
    Call(GetActorPos, ACTOR_SELF, LVar2, LVar3, LVar4)
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseOrEq(0)
        CaseOrEq(256)
            Add(LVar2, 37)
            Add(LVar3, 60)
        EndCaseGroup
        CaseDefault
            Add(LVar2, -37)
            Add(LVar3, 60)
    EndSwitch
    Set(LVar5, LVar2)
    Set(LVar6, LVar3)
    Call(MakeEntity, Ref(Entity_PowBlock), LVar2, LVar3, 0, 0, MAKE_ENTITY_END)
    Set(LVarA, LVar0)
    Call(battle_item_pow_block_AdjustPOWBlockEntityScale)
    Call(PlayEffect_impl, 7, 2, LVar2, LVar3, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseOrEq(0)
        CaseOrEq(256)
            Add(LVar5, 10)
        EndCaseGroup
        CaseDefault
            Add(LVar5, -10)
    EndSwitch
    Add(LVar6, 5)
    Call(PlayEffect_impl, 7, 2, LVar5, LVar6, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(PlayEffect_impl, 7, 2, LVar2, LVar3, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Set(LVar5, LVar2)
    Set(LVar6, LVar3)
    Add(LVar6, -5)
    Call(PlayEffect_impl, 7, 2, LVar2, LVar6, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseEq(0)
            Call(SetAnimation, ACTOR_SELF, 0, 65538)
        CaseEq(256)
            Set(LVar0, 0)
            Exec(TTYD64_SetPartnerAnimation_Battle)
        CaseDefault
    EndSwitch
    Wait(20)
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Thread
        Wait(15)
        Call(PlaySoundAtActor, ACTOR_SELF, SOUND_HIT_BLOCK)
        Call(battle_item_pow_block_ForceTriggerPOWBlockEntity)
        Call(PlayEffect_impl, 7, 2, LVar2, LVar3, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Set(LVar5, LVar2)
        Set(LVar6, LVar3)
        Call(GetOwnerID, LVar7)
        Switch(LVar7)
            CaseOrEq(0)
            CaseOrEq(256)
                Add(LVar5, 10)
            EndCaseGroup
            CaseDefault
                Add(LVar5, -10)
        EndSwitch
        Add(LVar6, 5)
        Call(PlayEffect_impl, 7, 2, LVar5, LVar6, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 7, 2, LVar2, LVar3, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Set(LVar6, LVar3)
        Add(LVar6, -15)
        Call(PlayEffect_impl, 7, 2, LVar2, LVar6, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(StartRumble, 4)
        Call(ShakeCam, 1, 0, 2, Float(1.0))
        Call(ShakeCam, 1, 0, 2, Float(3.0))
        Call(ShakeCam, 1, 0, 2, Float(6.0))
        Call(ShakeCam, 1, 0, 2, Float(5.0))
        Call(ShakeCam, 1, 0, 2, Float(4.0))
        Call(PlaySoundAtActor, ACTOR_SELF, 8240)
        Call(ShakeCam, 1, 0, 2, Float(3.0))
        Call(ShakeCam, 1, 0, 2, Float(2.0))
        Call(ShakeCam, 1, 0, 2, Float(1.0))
        Call(ShakeCam, 1, 0, 2, Float(0.5))
        Call(ShakeCam, 1, 0, 2, Float(0.2))
    EndThread
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetOwnerID, LVar7)
    IfLt(LVar7, 512)
        Add(LVar0, 30)
    Else
        Add(LVar0, -30)
    EndIf
    Call(SetActorSpeed, ACTOR_SELF, Float(4.0))
    Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseEq(0)
            Call(SetAnimation, ACTOR_SELF, 0, 65541)
            Call(PlayerRunToGoal, 0)
            Call(SetJumpAnimations, ACTOR_SELF, 0, 65543, 65544, 65545)
        CaseEq(256)
            Set(LVar0, 1)
            Exec(TTYD64_SetPartnerAnimation_Battle)
            Call(RunToGoal, ACTOR_SELF, 0, false)
        CaseDefault
            Call(RunToGoal, ACTOR_SELF, 0, false)
    EndSwitch
    Wait(5)
    Call(SetActorJumpGravity, ACTOR_SELF, Float(0.5996))
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseEq(0)
            Call(PlayerHopToGoal, 20, 0, 0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
            Call(UseBattleCamPreset, 3)
            Call(MoveBattleCamOver, 20)
            Call(InitTargetIterator)
        CaseEq(256)
            Set(LVar0, 0)
            Exec(TTYD64_SetPartnerAnimation_Battle)
            Call(JumpToGoal, ACTOR_SELF, 15, false, true, false)
            Call(UseBattleCamPreset, 3)
            Call(MoveBattleCamOver, 20)
            Call(InitTargetIterator)
        CaseDefault
            Call(JumpToGoal, ACTOR_SELF, 15, false, true, false)
    EndSwitch
    Label(0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(ItemCheckHit, LVar0, 268435456, 0, LVar0, 0)
    IfEq(LVar0, 6)
        Goto(1)
    EndIf
    Call(GetItemPower, 144, LVar3, LVar4)
    Call(TTYD64_ApplyShrinkFromOwner, LVar3)
    Call(SetDamageSource, 22)
    Call(ItemDamageEnemy, LVar0, 973079552, 0, LVar3, 32)
    Label(1)
    Call(GetOwnerID, LVar2)
    IfGe(LVar2, 512)
        Call(GetOwnerTarget, LVar0, LVar1)
        Call(TTYD64_GetPartnerHP_API, LVar1)
        IfLe(LVar1, 0)
            Set(LVar0, 256)
        EndIf
        IfNe(LVar0, 256)
            Call(SetTargetActor, ACTOR_SELF, ACTOR_PARTNER)
            Goto(0)
        EndIf
    Else
        Call(ChooseNextTarget, 0, LVar0)
        IfNe(LVar0, -1)
            Goto(0)
        EndIf
    EndIf
    Call(GetActorPos, ACTOR_SELF, LVar2, LVar3, LVar4)
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseOrEq(0)
        CaseOrEq(256)
            Add(LVar2, 37)
        EndCaseGroup
        CaseDefault
            Add(LVar2, -37)
    EndSwitch
    Add(LVar3, 60)
    Set(LVar5, LVar2)
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseOrEq(0)
        CaseOrEq(256)
            Add(LVar5, -30)
        EndCaseGroup
        CaseDefault
            Add(LVar5, 30)
    EndSwitch
    Call(PlayEffect_impl, 7, 2, LVar5, LVar3, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Set(LVar5, LVar2)
    Set(LVar6, LVar3)
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseOrEq(0)
        CaseOrEq(256)
            Add(LVar5, -20)
        EndCaseGroup
        CaseDefault
            Add(LVar5, 20)
    EndSwitch
    Add(LVar6, 5)
    Call(PlayEffect_impl, 7, 2, LVar5, LVar6, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Set(LVar5, LVar2)
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseOrEq(0)
        CaseOrEq(256)
            Add(LVar5, -30)
        EndCaseGroup
        CaseDefault
            Add(LVar5, 30)
    EndSwitch
    Call(PlayEffect_impl, 7, 2, LVar5, LVar3, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Set(LVar5, LVar2)
    Set(LVar6, LVar3)
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseOrEq(0)
        CaseOrEq(256)
            Add(LVar5, -30)
        EndCaseGroup
        CaseDefault
            Add(LVar5, 30)
    EndSwitch
    Add(LVar6, -5)
    Call(PlayEffect_impl, 7, 2, LVar5, LVar6, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    Call(battle_item_pow_block_DeletePOWBlockEntity)
    Wait(30)
    ExecWait(TTYD64_BattleScript_GoBackToHome_Item)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_item_pow_block(void) {
    Mod_ReplaceScript("TTYD64", &battle_item_pow_block_EVS_UseItem, &TTYD64_battle_item_pow_block_EVS_UseItem);
}
