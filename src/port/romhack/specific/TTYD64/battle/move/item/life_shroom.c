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

extern EvtScript battle_item_life_shroom_EVS_UseItem;
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetMenuSelection);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetGoalPos);
API_CALLABLE(ShowRecoveryShimmer);
API_CALLABLE(ShowStartRecoveryShimmer);
API_CALLABLE(TTYD64_Player_Refund);
API_CALLABLE(TTYD64_Player_Refund_FreeIcons);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(battle_item_food_SpawnHeartRecoveryFX);
API_CALLABLE(battle_item_life_shroom_func_802A1484_72E9B4);
EvtScript TTYD64_battle_item_life_shroom_EVS_802A1538;
EvtScript TTYD64_battle_item_life_shroom_EVS_UseItem;
EvtScript TTYD64_battle_item_life_shroom_EVS_802A1FE8;

// clang-format off
EvtScript TTYD64_battle_item_life_shroom_EVS_802A1538 = {
    Set(LVarF, LVar1)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Set(LVarA, LVar1)
    Call(battle_item_life_shroom_func_802A1484_72E9B4, LVarA)
    Call(InitTargetIterator)
    SetConst(LVarA, 149)
    Set(LVar1, LVarF)
    ExecWait(TTYD64_battle_item_life_shroom_EVS_802A1FE8)
    ExecWait(TTYD64_BattleScript_EatItem)
    Call(TTYD64_ReadField, TTYD64_F_GITEMTABLE_12BB_1U, LVar3)
    Call(GetOwnerTarget, LVar7, 0)
    IfGe(LVar7, 512)
        Call(TTYD64_HealActor, LVar7, LVar3)
    Else
        Call(TTYD64_Heal_PlayerTeam, LVar7, LVar3)
    EndIf
    Call(GetOwnerTarget, LVar7, 0)
    Call(GetActorPos, LVar7, LVar0, LVar1, LVar2)
    Add(LVar0, 0)
    Add(LVar1, 35)
    Call(battle_item_food_SpawnHeartRecoveryFX, LVar0, LVar1, LVar2, LVar3)
    Call(GetActorPos, LVar7, LVar0, LVar1, LVar2)
    Add(LVar1, 25)
    Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, LVar3)
    Wait(10)
    Call(GetOwnerID, LVar4)
    IfNe(LVar7, LVar4)
        Call(UseIdleAnimation, LVar7, false)
    EndIf
    Call(GetStatusFlags, LVar7, LVar0)
    IfNotFlag(LVar0, 3526656)
        Switch(LVar7)
            CaseEq(0)
                Call(SetAnimation, ACTOR_PLAYER, 0, 65586)
            CaseEq(256)
                Set(LVar0, 5)
                Exec(TTYD64_SetPartnerAnimation_Battle)
            CaseDefault
        EndSwitch
    EndIf
    Wait(30)
    Call(GetOwnerID, LVar4)
    IfNe(LVar7, LVar4)
        Call(UseIdleAnimation, LVar7, true)
    EndIf
    Call(GetActorPos, LVar7, LVar0, LVar1, LVar2)
    Call(ShowRecoveryShimmer, LVar0, LVar1, LVar2, LVar3)
    Call(GetOwnerTarget, LVar7, 0)
    Call(GetOwnerID, LVar4)
    IfNe(LVar7, LVar4)
        Call(UseIdleAnimation, LVar7, false)
    EndIf
    Call(GetStatusFlags, LVar7, LVar0)
    IfNotFlag(LVar0, 3526656)
        Switch(LVar7)
            CaseEq(0)
                Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
            CaseEq(256)
                Set(LVar0, 0)
                Exec(TTYD64_SetPartnerAnimation_Battle)
            CaseDefault
        EndSwitch
    EndIf
    Wait(20)
    ExecWait(TTYD64_BattleScript_GoBackToHome_HealingItem)
    Return
    End
};

EvtScript TTYD64_battle_item_life_shroom_EVS_UseItem = {
    Jump(TTYD64_battle_item_life_shroom_EVS_802A1538)
    Return
    End
};

EvtScript TTYD64_battle_item_life_shroom_EVS_802A1FE8 = {
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
    Call(UseBattleCamPreset, 14)
    Call(GetOwnerTarget, LVar7, 0)
    Call(BattleCamTargetActor, LVar7)
    Call(MoveBattleCamOver, 15)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_item_life_shroom(void) {
    Mod_ReplaceScript("TTYD64", &battle_item_life_shroom_EVS_UseItem, &TTYD64_battle_item_life_shroom_EVS_UseItem);
}
