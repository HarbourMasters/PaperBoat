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

extern EvtScript battle_item_fire_flower_EVS_UseItem;
API_CALLABLE(BattleCamTargetActor);
API_CALLABLE(ChooseNextTarget);
API_CALLABLE(GetActorFlags);
API_CALLABLE(GetActorPos);
API_CALLABLE(GetActorSize);
API_CALLABLE(GetGoalPos);
API_CALLABLE(GetItemPower);
API_CALLABLE(GetOwnerID);
API_CALLABLE(GetOwnerTarget);
API_CALLABLE(InitTargetIterator);
API_CALLABLE(ItemCheckHit);
API_CALLABLE(ItemDamageEnemy);
API_CALLABLE(MakeItemEntity);
API_CALLABLE(MoveBattleCamOver);
API_CALLABLE(MultiplyByActorScale);
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
API_CALLABLE(SetTargetActor);
API_CALLABLE(TTYD64_Player_Refund);
API_CALLABLE(TTYD64_Player_Refund_FreeIcons);
API_CALLABLE(UseBattleCamPreset);
API_CALLABLE(battle_item_fire_flower_FadeBackgroundDarken);
API_CALLABLE(battle_item_fire_flower_FadeBackgroundLighten);
EvtScript TTYD64_battle_item_fire_flower_EVS_802A1000;
EvtScript TTYD64_battle_item_fire_flower_EVS_UseItem;
EvtScript TTYD64_battle_item_fire_flower_EVS_802A19D8;

// clang-format off
EvtScript TTYD64_battle_item_fire_flower_EVS_802A1000 = {
    SetConst(LVarA, 128)
    ExecWait(TTYD64_battle_item_fire_flower_EVS_802A19D8)
    Call(GetOwnerID, LVar7)
    Switch(LVar7)
        CaseEq(0)
            Call(PlaySound, SOUND_PLANT_FIRE_FLOWER)
            Call(SetAnimation, ACTOR_PLAYER, 0, 65566)
            Call(battle_item_fire_flower_FadeBackgroundDarken)
        CaseEq(256)
            Call(PlaySound, SOUND_PLANT_FIRE_FLOWER)
            Call(battle_item_fire_flower_FadeBackgroundDarken)
        CaseDefault
    EndSwitch
    Thread
        Wait(50)
        Call(GetOwnerID, LVar7)
        Switch(LVar7)
            CaseEq(0)
                Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
                Wait(35)
            CaseEq(256)
                Set(LVar0, 0)
                Exec(TTYD64_SetPartnerAnimation_Battle)
                Wait(35)
            CaseDefault
        EndSwitch
    EndThread
    Call(UseBattleCamPreset, 2)
    Call(MoveBattleCamOver, 20)
    Wait(10)
    Call(GetActorPos, ACTOR_SELF, LVar3, 0, LVar5)
    Call(GetOwnerID, LVar7)
    IfLt(LVar7, 512)
        Set(LVar0, 40)
    Else
        Set(LVar0, -40)
    EndIf
    Call(MultiplyByActorScale, LVar0)
    Add(LVar3, LVar0)
    Thread
        Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Sub(LVar0, 10)
        Call(SetActorSpeed, ACTOR_SELF, Float(2.0))
        Call(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        Call(GetOwnerID, LVar7)
        Switch(LVar7)
            CaseEq(0)
                Call(SetAnimation, ACTOR_PLAYER, 0, 65541)
                Call(PlayerRunToGoal, 0)
                Call(SetAnimation, ACTOR_PLAYER, 0, 65538)
            CaseEq(256)
                Set(LVar0, 3)
                Exec(TTYD64_SetPartnerAnimation_Battle)
                Call(RunToGoal, ACTOR_SELF, 0, false)
                Set(LVar0, 0)
                Exec(TTYD64_SetPartnerAnimation_Battle)
            CaseDefault
        EndSwitch
    EndThread
    Thread
        IfLt(LVar7, 512)
            Call(PlayEffect_impl, 63, 0, LVar3, 0, LVar5, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            Wait(25)
            Loop(12)
                Wait(1)
                Call(PlaySound, 8236)
                Wait(2)
                Call(PlaySound, 8237)
                Wait(1)
            EndLoop
        EndIf
    EndThread
    IfLt(LVar7, 512)
        Wait(80)
    Else
        Wait(20)
    EndIf
    Call(GetOwnerID, LVar1)
    IfLt(LVar1, 512)
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
    Call(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    Call(GetItemPower, 128, LVar0, LVar1)
    Call(ItemDamageEnemy, LVar0, 436207618, 0, LVar0, 32)
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
    IfLt(LVar2, 512)
        Call(battle_item_fire_flower_FadeBackgroundLighten)
    EndIf
    Wait(30)
    ExecWait(TTYD64_BattleScript_GoBackToHome_Item)
    Return
    End
};

EvtScript TTYD64_battle_item_fire_flower_EVS_UseItem = {
    Jump(TTYD64_battle_item_fire_flower_EVS_802A1000)
    Return
    End
};

EvtScript TTYD64_battle_item_fire_flower_EVS_802A19D8 = {
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

// clang-format on

void TTYD64_Player_Install_item_fire_flower(void) {
    Mod_ReplaceScript("TTYD64", &battle_item_fire_flower_EVS_UseItem, &TTYD64_battle_item_fire_flower_EVS_UseItem);
}
