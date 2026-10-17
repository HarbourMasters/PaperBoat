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
#include "port/romhack/specific/TTYD64/player/player_internal.h"

extern EvtScript battle_item_stop_watch_EVS_UseItem;
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetItemPower);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(ItemAfflictEnemy);
API_CALLABLE(ItemCheckHit);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MakeStatusField);
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
API_CALLABLE(SetTargetActor);
API_CALLABLE(TTYD64_Player_Refund);
API_CALLABLE(TTYD64_Player_Refund_FreeIcons);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(battle_item_fire_flower_FadeBackgroundDarken);
API_CALLABLE(battle_item_fire_flower_FadeBackgroundLighten);
EvtScript TTYD64_battle_item_stop_watch_EVS_802A1000;
EvtScript TTYD64_battle_item_stop_watch_EVS_802A14D8;
EvtScript TTYD64_battle_item_stop_watch_EVS_UseItem;

// clang-format off
EvtScript TTYD64_battle_item_stop_watch_EVS_802A1000 = {
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

EvtScript TTYD64_battle_item_stop_watch_EVS_802A14D8 = {
    SetConst(LVarA, 146)
    ExecWait(TTYD64_battle_item_stop_watch_EVS_802A1000)
    Thread
        Wait(5)
        Call(UseBattleCamPreset, 2)
        Call(MoveBattleCamOver, 20)
    EndThread
    Call(battle_item_fire_flower_FadeBackgroundDarken)
    Call(PlayEffect_impl, 98, 0, 0, 0, 0, Float(1.0), 200, 0, 0, 0, 0, 0, 0, 0)
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_TIME_OUT)
    Wait(200)
    Call(GetOwnerID, LVar2)
    IfLt(LVar2, 512)
        Call(UseBattleCamPreset, 3)
        Call(MoveBattleCamOver, 20)
        Call(InitTargetIterator)
    EndIf
    Label(0)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(ItemCheckHit, LVar0, 268435456, 0, LVar0, 0)
    IfEq(LVar0, 6)
        Goto(1)
    EndIf
    Call(GetItemPower, 146, LVar0, LVar1)
    Call(MakeStatusField, LVar0, 2097152, 100, LVar0)
    Call(ItemAfflictEnemy, LVar0, 1342177280, LVar0, 0, 32)
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
            Call(SetTargetActor, ACTOR_SELF, ACTOR_PARTNER)
            Goto(0)
        EndIf
    Else
        Call(ChooseNextTarget, 0, LVar0)
        IfNe(LVar0, -1)
            Goto(0)
        EndIf
    EndIf
    Call(battle_item_fire_flower_FadeBackgroundLighten)
    ExecWait(TTYD64_BattleScript_GoBackToHome_Item)
    Return
    End
};

EvtScript TTYD64_battle_item_stop_watch_EVS_UseItem = {
    Jump(TTYD64_battle_item_stop_watch_EVS_802A14D8)
    Return
    End
};

// clang-format on

void TTYD64_Player_Install_item_stop_watch(void) {
    Mod_ReplaceScript("TTYD64", &battle_item_stop_watch_EVS_UseItem, &TTYD64_battle_item_stop_watch_EVS_UseItem);
}
