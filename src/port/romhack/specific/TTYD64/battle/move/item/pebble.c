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

extern EvtScript battle_item_pebble_EVS_UseItem;
extern s32 battle_item_pebble_modelCommandList[];
API_CALLABLE(TTYD64_ApplyShrinkFromOwner);
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(CreateVirtualEntity);
API_CALLABLE(DeleteVirtualEntity);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetCurrentPartnerID);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetItemPower);
API_CALLABLE(GetOwnerID);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(ItemDamageEnemy);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(MultiplyByActorScale);
API_CALLABLE(MultiplyVec3ByActorScale);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetGoalPos);
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(SetVirtualEntityJumpGravity);
API_CALLABLE(SetVirtualEntityPosition);
API_CALLABLE(SetVirtualEntityRotation);
API_CALLABLE(SetVirtualEntityScale);
API_CALLABLE(TTYD64_Player_Refund);
API_CALLABLE(TTYD64_Player_Refund_FreeIcons);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(VirtualEntityJumpTo);
EvtScript TTYD64_battle_item_pebble_EVS_802A1000;
EvtScript TTYD64_battle_item_pebble_EVS_UseItem;
EvtScript TTYD64_battle_item_pebble_EVS_802A1B88;

// clang-format off
EvtScript TTYD64_battle_item_pebble_EVS_802A1000 = {
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

EvtScript TTYD64_battle_item_pebble_EVS_UseItem = {
    Jump(TTYD64_battle_item_pebble_EVS_802A1B88)
    Return
    End
};

EvtScript TTYD64_battle_item_pebble_EVS_802A1B88 = {
    SetConst(LVarA, 133)
    ExecWait(TTYD64_battle_item_pebble_EVS_802A1000)
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseEq(0)
            Call(UseBattleCamPreset, 3)
            Call(MoveBattleCamOver, 15)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65558)
        CaseEq(256)
            Call(UseBattleCamPreset, 3)
            Call(MoveBattleCamOver, 15)
            Call(GetCurrentPartnerID, LVar0)
            IfEq(LVar0, 8)
                Call(SetAnimation, ACTOR_PARTNER, 0, 1048594)
            EndIf
        CaseDefault
            Call(UseBattleCamPreset, 2)
            Call(MoveBattleCamOver, 15)
    EndSwitch
    Call(PlaySound, SOUND_THROW)
    Wait(3)
    Call(CreateVirtualEntity, LVarA, Ref(battle_item_pebble_modelCommandList))
    SetF(LVar0, Float(1.0))
    Call(MultiplyByActorScale, LVar0)
    Call(SetVirtualEntityScale, LVarA, LVar0, LVar0, LVar0)
    Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Set(LVar3, 20)
    Set(LVar4, 42)
    Set(LVar5, 5)
    Call(MultiplyVec3ByActorScale, LVar3, LVar4, LVar5)
    Add(LVar0, LVar3)
    Add(LVar1, LVar4)
    Add(LVar2, LVar5)
    Call(SetVirtualEntityPosition, LVarA, LVar0, LVar1, LVar2)
    Call(GetOwnerID, LVar0)
    IfLt(LVar0, 512)
        Call(InitTargetIterator)
    EndIf
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Thread
        Set(LVar0, 0)
        Loop(18)
            Add(LVar0, -60)
            Call(SetVirtualEntityRotation, LVarA, 0, 0, LVar0)
            Wait(1)
        EndLoop
    EndThread
    Call(SetVirtualEntityJumpGravity, LVarA, Float(0.7998))
    Add(LVar2, 5)
    Call(VirtualEntityJumpTo, LVarA, LVar0, LVar1, LVar2, 18)
    Call(GetItemPower, 133, LVar3, LVar4)
    Call(TTYD64_ApplyShrinkFromOwner, LVar3)
    Call(ItemDamageEnemy, LVar9, 436207616, 0, LVar3, 32)
    Add(LVar0, 60)
    Add(LVar1, 0)
    Call(VirtualEntityJumpTo, LVarA, LVar0, LVar1, LVar2, 16)
    Call(DeleteVirtualEntity, LVarA)
    ExecWait(TTYD64_BattleScript_GoBackToHome_Item)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_item_pebble(void) {
    Mod_ReplaceScript("TTYD64", &battle_item_pebble_EVS_UseItem, &TTYD64_battle_item_pebble_EVS_UseItem);
}
