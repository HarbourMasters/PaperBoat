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

extern EvtScript battle_item_hustle_drink_EVS_UseItem;
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(PlayEffect_impl);
API_CALLABLE(PlaySoundAtActor);
API_CALLABLE(PlayerRunToGoal);
API_CALLABLE(RemoveItemEntity);
API_CALLABLE(RunToGoal);
API_CALLABLE(SetActorScale);
API_CALLABLE(SetActorSpeed);
API_CALLABLE(SetAnimation);
API_CALLABLE(SetGoalPos);
API_CALLABLE(ShowStartRecoveryShimmer);
API_CALLABLE(TTYD64_Player_Refund);
API_CALLABLE(TTYD64_Player_Refund_FreeIcons);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(battle_item_hustle_drink_func_802A123C_72619C);
API_CALLABLE(battle_item_hustle_drink_func_802A12C4_726224);
EvtScript TTYD64_battle_item_hustle_drink_EVS_802A1000;
EvtScript TTYD64_battle_item_hustle_drink_EVS_UseItem;
EvtScript TTYD64_battle_item_hustle_drink_EVS_802A18B8;

// clang-format off
EvtScript TTYD64_battle_item_hustle_drink_EVS_802A1000 = {
    SetConst(LVarA, 145)
    ExecWait(TTYD64_battle_item_hustle_drink_EVS_802A18B8)
    ExecWait(TTYD64_BattleScript_DrinkItem)
    Call(GetOwnerTarget, LVar7, 0)
    Switch(LVar7)
        CaseEq(0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65574)
        CaseEq(256)
        CaseDefault
    EndSwitch
    Call(GetActorPos, LVar7, LVar0, LVar1, LVar2)
    Add(LVar1, 25)
    Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, 5)
    Call(battle_item_hustle_drink_func_802A12C4_726224)
    Call(battle_item_hustle_drink_func_802A123C_72619C)
    Call(GetActorPos, LVar7, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(UseBattleCamPreset, 13)
    Call(BattleCamTargetActor, LVar7)
    Call(MoveBattleCamOver, 20)
    Call(PlaySoundAtActor, LVar7, SOUND_SMALL_GLASS_BREAK)
    Thread
        Loop(2)
            Call(SetActorScale, LVar7, Float(1.0), Float(1.0), Float(1.0))
            Wait(1)
            Call(SetActorScale, LVar7, Float(1.0996), Float(1.0), Float(1.0))
            Wait(1)
            Call(SetActorScale, LVar7, Float(1.2), Float(0.95), Float(1.0))
            Wait(1)
            Call(SetActorScale, LVar7, Float(1.2998), Float(0.9), Float(1.0))
            Wait(1)
            Call(SetActorScale, LVar7, Float(1.3496), Float(0.8496), Float(1.0))
            Wait(1)
            Call(SetActorScale, LVar7, Float(1.3799), Float(0.7998), Float(1.0))
            Wait(1)
            Call(SetActorScale, LVar7, Float(1.4), Float(0.7998), Float(1.0))
            Wait(1)
            Call(SetActorScale, LVar7, Float(1.2998), Float(0.8496), Float(1.0))
            Wait(1)
            Call(SetActorScale, LVar7, Float(1.2), Float(0.9), Float(1.0))
            Wait(1)
            Call(SetActorScale, LVar7, Float(1.0996), Float(0.95), Float(1.0))
            Wait(1)
        EndLoop
        Call(SetActorScale, LVar7, Float(1.0), Float(1.0), Float(1.0))
        Wait(1)
        Call(SetActorScale, LVar7, Float(1.0996), Float(1.0), Float(1.0))
        Wait(1)
        Call(SetActorScale, LVar7, Float(1.2), Float(0.95), Float(1.0))
        Wait(1)
        Call(SetActorScale, LVar7, Float(1.2998), Float(0.9), Float(1.0))
        Wait(1)
        Call(SetActorScale, LVar7, Float(1.3496), Float(0.8496), Float(1.0))
        Wait(1)
        Call(SetActorScale, LVar7, Float(1.3799), Float(0.7998), Float(1.0))
        Wait(1)
        Call(SetActorScale, LVar7, Float(1.4), Float(0.7998), Float(1.0))
        Wait(1)
        Call(PlaySoundAtActor, LVar7, 8334)
        Call(SetActorScale, LVar7, Float(0.9), Float(1.2998), Float(1.0))
        Wait(1)
        Call(SetActorScale, LVar7, Float(0.9), Float(1.2), Float(1.0))
        Wait(1)
        Call(SetActorScale, LVar7, Float(0.95), Float(1.0996), Float(1.0))
        Wait(1)
        Call(SetActorScale, LVar7, Float(1.0), Float(1.0), Float(1.0))
        Wait(1)
        Call(SetAnimation, LVar7, 0, 65538)
    EndThread
    Loop(10)
        Call(PlaySoundAtActor, LVar7, SOUND_SMALL_GLASS_BREAK)
        Call(PlayEffect_impl, 6, 0, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Call(PlayEffect_impl, 6, 1, LVar0, LVar1, LVar2, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        Wait(4)
    EndLoop
    Wait(10)
    Call(GetOwnerTarget, LVar7, 0)
    Switch(LVar7)
        CaseEq(0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
        CaseEq(256)
            Set(LVar0, 2)
            Exec(TTYD64_SetPartnerAnimation_Battle)
        CaseDefault
    EndSwitch
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Wait(20)
    ExecWait(TTYD64_BattleScript_GoBackToHome_HealingItem)
    Return
    End
};

EvtScript TTYD64_battle_item_hustle_drink_EVS_UseItem = {
    Jump(TTYD64_battle_item_hustle_drink_EVS_802A1000)
    Return
    End
};

EvtScript TTYD64_battle_item_hustle_drink_EVS_802A18B8 = {
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

void TTYD64_Player_Install_item_hustle_drink(void) {
    Mod_ReplaceScript("TTYD64", &battle_item_hustle_drink_EVS_UseItem, &TTYD64_battle_item_hustle_drink_EVS_UseItem);
}
