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

extern EvtScript battle_item_electro_pop_EVS_UseItem;
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetItemPower);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(GetStatusFlags);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySound);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetGoalPos);
API_CALLABLE(ShowMessageBox);
API_CALLABLE(ShowRecoveryShimmer);
API_CALLABLE(ShowStartRecoveryShimmer);
API_CALLABLE(TTYD64_Player_Refund);
API_CALLABLE(TTYD64_Player_Refund_FreeIcons);
API_CALLABLE(TTYD64_Player_item29_ElectroPop_Heal_Enemies);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(WaitForMessageBoxDone);
API_CALLABLE(battle_item_electro_pop_AddFP);
API_CALLABLE(battle_item_electro_pop_func_802A14F0_730A90);
API_CALLABLE(battle_item_food_SpawnFlowerRecoveryFX);
EvtScript TTYD64_battle_item_electro_pop_EVS_802A149C;
EvtScript TTYD64_battle_item_electro_pop_EVS_UseItem;
EvtScript TTYD64_battle_item_electro_pop_EVS_802A1B18;

// clang-format off
EvtScript TTYD64_battle_item_electro_pop_EVS_802A149C = {
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

EvtScript TTYD64_battle_item_electro_pop_EVS_UseItem = {
    Jump(TTYD64_battle_item_electro_pop_EVS_802A1B18)
    Return
    End
};

EvtScript TTYD64_battle_item_electro_pop_EVS_802A1B18 = {
    SetConst(LVarA, 204)
    ExecWait(TTYD64_battle_item_electro_pop_EVS_802A149C)
    ExecWait(TTYD64_BattleScript_EatItem)
    Call(GetOwnerID, LVar0)
    IfLt(LVar0, 512)
        Call(InitTargetIterator)
    EndIf
    Call(GetOwnerTarget, LVar4, 0)
    Call(GetOwnerID, LVar0)
    IfNe(LVar4, LVar0)
        Call(UseIdleAnimation, LVar4, false)
    EndIf
    Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(PlayEffect_impl, 87, 0, LVar0, LVar1, LVar2, Float(1.0), 30, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySound, SOUND_VOLT_SHROOM_APPLY)
    Call(GetItemPower, 139, LVar0, LVar1)
    Call(TTYD64_Function_InflictStatus, LVar4, 11, LVar0)
    Wait(40)
    Call(GetOwnerID, LVar5)
    IfLt(LVar5, 512)
        Call(battle_item_electro_pop_func_802A14F0_730A90)
    Else
        Call(TTYD64_Player_item29_ElectroPop_Heal_Enemies)
    EndIf
    Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Add(LVar1, 25)
    Call(battle_item_food_SpawnFlowerRecoveryFX, LVar0, LVar1, LVar2, LVar3)
    Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
    Add(LVar1, 25)
    Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, LVar3)
    Call(GetOwnerID, LVar0)
    IfLt(LVar0, 512)
        Call(battle_item_electro_pop_AddFP, LVar3)
    EndIf
    Wait(10)
    Call(GetStatusFlags, LVar4, LVar0)
    IfNotFlag(LVar0, 3526656)
        Switch(LVar4)
            CaseEq(0)
                Call(SetAnimation, ACTOR_PLAYER, 0, 65586)
            CaseEq(256)
                Set(LVar0, 5)
                Exec(TTYD64_SetPartnerAnimation_Battle)
            CaseDefault
        EndSwitch
    EndIf
    Wait(30)
    Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
    Call(ShowRecoveryShimmer, LVar0, LVar1, LVar2, LVar3)
    Call(GetStatusFlags, LVar4, LVar0)
    IfNotFlag(LVar0, 3526656)
        Switch(LVar4)
            CaseEq(0)
                Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
                Wait(20)
                Call(ShowMessageBox, 16, 60)
                Call(WaitForMessageBoxDone)
            CaseEq(256)
                Set(LVar0, 0)
                Exec(TTYD64_SetPartnerAnimation_Battle)
                Wait(30)
            CaseDefault
                Wait(30)
        EndSwitch
    EndIf
    ExecWait(TTYD64_BattleScript_GoBackToHome_HealingItem)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_item_electro_pop(void) {
    Mod_ReplaceScript("TTYD64", &battle_item_electro_pop_EVS_UseItem, &TTYD64_battle_item_electro_pop_EVS_UseItem);
}
