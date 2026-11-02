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

extern EvtScript battle_item_strange_cake_EVS_UseItem;
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetGoalPos);
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
API_CALLABLE(SetGoalToTarget);
API_CALLABLE(ShowMessageBox);
API_CALLABLE(ShowRecoveryShimmer);
API_CALLABLE(ShowStartRecoveryShimmer);
API_CALLABLE(TTYD64_Player_Refund);
API_CALLABLE(TTYD64_Player_Refund_FreeIcons);
API_CALLABLE(TTYD64_Player_item30_KookyCookie_Heal_Enemies);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(UseIdleAnimation);
API_CALLABLE(WaitForMessageBoxDone);
API_CALLABLE(battle_item_food_SpawnFlowerRecoveryFX);
API_CALLABLE(battle_item_strange_cake_func_802A13E4_7316E4);
API_CALLABLE(battle_item_strange_cake_func_802A1A8C_731D8C);
API_CALLABLE(battle_item_super_soda_AddFP);
EvtScript TTYD64_battle_item_strange_cake_EVS_802A1000;
EvtScript TTYD64_battle_item_strange_cake_EVS_802A1CA8;
EvtScript TTYD64_battle_item_strange_cake_EVS_UseItem;
EvtScript TTYD64_battle_item_strange_cake_EVS_802A288C;
EvtScript TTYD64_battle_item_strange_cake_EVS_802A3254;
EvtScript TTYD64_battle_item_strange_cake_EVS_802A33C0;

// clang-format off
EvtScript TTYD64_battle_item_strange_cake_EVS_802A1000 = {
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    IfEq(LVar1, 211)
        SetConst(LVarA, 211)
        Call(GetOwnerID, LVar2)
        IfLt(LVar2, 512)
            Set(LVar1, 0)
            Call(InitTargetIterator)
        Else
            Set(LVar1, 1)
        EndIf
        ExecWait(TTYD64_battle_item_strange_cake_EVS_802A288C)
        ExecWait(TTYD64_BattleScript_EatItem)
        Call(GetOwnerTarget, LVar4, 0)
        IfLt(LVar4, 512)
            Call(battle_item_strange_cake_func_802A1A8C_731D8C)
        Else
            Call(TTYD64_Player_item30_KookyCookie_Heal_Enemies)
        EndIf
        Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
        Add(LVar0, 20)
        Add(LVar1, 25)
        Call(battle_item_food_SpawnFlowerRecoveryFX, LVar0, LVar1, LVar2, LVar3)
        Call(GetActorPos, LVar4, LVar0, LVar1, LVar2)
        Add(LVar1, 25)
        Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, LVar3)
        Call(GetOwnerTarget, LVar0, 0)
        IfLt(LVar0, 512)
            Call(battle_item_super_soda_AddFP, LVar3)
        EndIf
        Wait(10)
        Call(GetOwnerTarget, LVar0, 0)
        Call(GetOwnerID, LVar1)
        IfNe(LVar0, LVar1)
            Call(UseIdleAnimation, LVar0, false)
        EndIf
        Call(GetOwnerTarget, LVar4, 0)
        Call(GetStatusFlags, LVar4, LVar0)
        IfNotFlag(LVar0, 3526656)
            Switch(LVar0)
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
        Call(GetOwnerTarget, LVar0, 0)
        Call(GetStatusFlags, LVar0, LVar1)
        IfNotFlag(LVar1, 3526656)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
                    Wait(20)
                    Call(SetAnimation, ACTOR_PLAYER, 0, 65567)
                CaseEq(256)
                    Set(LVar0, 0)
                    Exec(TTYD64_SetPartnerAnimation_Battle)
                    Wait(20)
                    Set(LVar0, 7)
                    Exec(TTYD64_SetPartnerAnimation_Battle)
                CaseDefault
                    Wait(20)
            EndSwitch
        EndIf
    Else
        SetConst(LVarA, 210)
        Call(GetOwnerID, LVar2)
        IfLt(LVar2, 512)
            Set(LVar1, 0)
            Call(InitTargetIterator)
        Else
            Set(LVar1, 1)
        EndIf
        ExecWait(TTYD64_battle_item_strange_cake_EVS_802A288C)
        ExecWait(TTYD64_BattleScript_EatItem)
        Call(GetOwnerTarget, LVar0, 0)
        Call(GetOwnerID, LVar1)
        IfNe(LVar0, LVar1)
            Call(UseIdleAnimation, LVar0, false)
        EndIf
        Call(GetStatusFlags, LVar0, LVar1)
        IfNotFlag(LVar1, 3526656)
            Switch(LVar0)
                CaseEq(0)
                    Call(SetAnimation, ACTOR_PLAYER, 0, 65567)
                CaseEq(256)
                    Set(LVar0, 7)
                    Exec(TTYD64_SetPartnerAnimation_Battle)
                CaseDefault
                    Wait(20)
            EndSwitch
        EndIf
    EndIf
    Wait(10)
    Thread
        Wait(220)
        Call(PlaySoundAtActor, ACTOR_SELF, SOUND_DING)
    EndThread
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_MYSTERY_REEL)
    Call(battle_item_strange_cake_func_802A13E4_7316E4)
    Wait(2)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(TTYD64_battle_item_strange_cake_EVS_802A1CA8)
        CaseEq(1)
            ExecWait(TTYD64_battle_item_strange_cake_EVS_802A3254)
        CaseEq(2)
            ExecWait(TTYD64_battle_item_strange_cake_EVS_802A33C0)
    EndSwitch
    ExecWait(TTYD64_BattleScript_GoBackToHome_HealingItem)
    Return
    End
};

EvtScript TTYD64_battle_item_strange_cake_EVS_802A1CA8 = {
    Call(GetOwnerTarget, LVar4, 0)
    Switch(LVar4)
        CaseEq(0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
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

EvtScript TTYD64_battle_item_strange_cake_EVS_UseItem = {
    Jump(TTYD64_battle_item_strange_cake_EVS_802A1000)
    Return
    End
};

EvtScript TTYD64_battle_item_strange_cake_EVS_802A288C = {
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

EvtScript TTYD64_battle_item_strange_cake_EVS_802A3254 = {
    Call(GetOwnerTarget, LVar4, 0)
    Switch(LVar4)
        CaseEq(0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
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

EvtScript TTYD64_battle_item_strange_cake_EVS_802A33C0 = {
    Call(GetOwnerTarget, LVar4, 0)
    Switch(LVar4)
        CaseEq(0)
            Call(SetAnimation, ACTOR_PLAYER, 0, 196612)
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

void TTYD64_Player_Install_item_strange_cake(void) {
    Mod_ReplaceScript("TTYD64", &battle_item_strange_cake_EVS_UseItem, &TTYD64_battle_item_strange_cake_EVS_UseItem);
}
